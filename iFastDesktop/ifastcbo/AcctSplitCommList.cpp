//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//*****************************************************************************
//
// ^FILE   : AcctSplitCommList.cpp
// ^AUTHOR : 
// ^DATE   : 22/08/2001
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AcctSplitCommList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "acctsplitcomm.hpp"
#include "acctsplitcommlist.hpp"
#include "acctsplitcommreplist.hpp"
#include <ifastdataimpl\dse_dstc0175_req.hpp>
#include <ifastdataimpl\dse_dstc0175_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AcctSplitCommList" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
}

namespace CND
{
//   extern const long ERR_INDEX_DATE_RANGE_OVERLAP;
//   extern const long ERR_ACCT_SPLIT_COMM_INVALID_DATE_RANGE;
   extern const long ERR_ACCT_SPLIT_COMM_NO_ACTIVE_DATE_RANGE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNT_SPLITCOMM_LIST;
}

//******************************************************************************
// Constructor
//******************************************************************************
AcctSplitCommList::AcctSplitCommList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, _pLastActiveAcctSplitComm (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   // Defines this CBO Class as a List
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************
AcctSplitCommList::~AcctSplitCommList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Initialization of the request object and makes a View call 175
// @param   const DString& dstrAccountNum - Account Number (Required)
// @param   const DString& dstrTrack - Track value (Not required)
// @param   const DString& dstrPageName - Page Name (Not required)
// @return  SEVERITY - Error condition from DataBroker receive
//                     Error condition from AcctSplitComm init.
//                     Error condition from BFCBO.
//******************************************************************************
SEVERITY AcctSplitCommList::init( const DString& dstrAccountNum,
                                  const DString& dstrTrack,
                                  const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString  mgmtCoIdOut;   
   BFData   requestData(ifds::DSTC0175_REQ);
   BFData*  responseData = new BFData(ifds::DSTC0175_VW);
   _dstrAccountNum = dstrAccountNum;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ACCOUNT_SPLITCOMM_LIST, 
                                             requestData, *responseData, DSTCRequestor(getSecurity(), true) ) <= WARNING )
   {
      std::set< DString > dstrDateRange;
      int iRptCount = responseData->getRepeatCount();      
      for( int i = 0; i < iRptCount; i++ )
      {
         const BFData& repeatData = responseData->getRepeat(i);
         DString dstrEffectiveDate, dstrStopDate, dstrKey;         
         dstrEffectiveDate  = repeatData.getElementValue( ifds::EffectiveDate );
         dstrStopDate = repeatData.getElementValue ( ifds::StopDate );
         dstrKey = dstrEffectiveDate + dstrStopDate;
         if( dstrDateRange.insert( dstrKey ).second )
         {
            AcctSplitComm *pAcctSplitComm = new AcctSplitComm ( *this );
            pAcctSplitComm->init ( dstrEffectiveDate, dstrStopDate, repeatData, *responseData );
            //create a new object
            getStrKey(dstrKey, &repeatData);
            setObject( pAcctSplitComm, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST );        
         }
      }

   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Initialization of the request object
// @param   const DString& dstrAccountNum - Account Number (Required)
// @return  void
//******************************************************************************
void AcctSplitCommList::initNew( const DString& dstrAccountNum )
{   
   _dstrAccountNum = dstrAccountNum;
}

//********************************************************************************
// Returns the account number of the current work session's account
// This is currently used by AcctSplitCommRep to obtain default information 
// from the account;
// @param   DString& dstrAccountNum - Account number to be returned
// @return  void - dstrAccountNum is set to the account number set during init.
//********************************************************************************
void AcctSplitCommList::getAccountNum ( DString& dstrAccountNum )
{
   dstrAccountNum = _dstrAccountNum;
}

//********************************************************************************
// Creates a new AccountSplitComm CBO.
// @param   BFCBO*& pBase - BFCBO point to the new AccountSplitComm CBO
// @param   DString& strKey - Key to access the new CBO
// @param   const BFDataGroupId& idDataGroup - Data group id for new CBO.
// @return  SEVERITY - Error condition resulting from setField.
//********************************************************************************
SEVERITY AcctSplitCommList::doCreateNewObject( BFCBO *& pBase, 
                                               DString &strKey, 
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) ); 

   //Before we create a new account split commission, we need to mark the existing active
   //Account Level split commission inactive
   DString dstrCurrBusDate, dstrCurrStopDate, dstrStopDate, dstrActive, dstrEffectiveDate;
   AcctSplitComm* pAcctSplitComm;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
   DSTCommonFunctions::getFormat12319999Date(dstrStopDate);
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);      
   while( !iter.end() )
   {
      pAcctSplitComm = dynamic_cast <AcctSplitComm*>(iter.getObject());
      pAcctSplitComm->getField ( ifds::Active, dstrActive, idDataGroup, false );      
      pAcctSplitComm->getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
      pAcctSplitComm->getField ( ifds::StopDate, dstrCurrStopDate, idDataGroup, false );
      if( dstrActive == YES )// && !pAcctSplitComm->isNew() && 
      //DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrCurrBusDate ) == DSTCommonFunctions::FIRST_EARLIER )
      {
         pAcctSplitComm->setField ( ifds::Active, NO, idDataGroup );
      }
      if( DSTCommonFunctions::CompareDates( dstrCurrStopDate, dstrStopDate ) == DSTCommonFunctions::EQUAL )
         _pLastActiveAcctSplitComm = pAcctSplitComm;
      ++iter;
   }
   pBase = new AcctSplitComm ( *this );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
// When we delete a Account Level Split Commission Date Range, we need to restore
// the original active date range back to it's original data.   We know that the
// Stop date is 12/12/9999 and the Active field "Y".
// @param   const DString& strKey - key of deleted object.
// @param   const BFDataGroupId& idDataGroup - Data group id of deleted object.
// @param   bool bIsObjectDestroyed - Boolean indicating whether the object is marked
//                                    deleted or removed from system completely.
// @return  SEVERITY - Error condition resulting from setField.
//********************************************************************************
SEVERITY AcctSplitCommList::doDeleteObject ( const DString&  strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   DString dstrActive;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   iter.setKeyFilter( strKey );
   AcctSplitCommRepList *pAcctSplitCommRepList;
   AcctSplitComm* pAcctSplitComm = dynamic_cast <AcctSplitComm*> (iter.getObject());
   if( pAcctSplitComm )
   {
      pAcctSplitComm->getAcctSplitCommRepList ( pAcctSplitCommRepList, idDataGroup );
      if( pAcctSplitCommRepList )
      {
         BFObjIter iter1( *pAcctSplitCommRepList, idDataGroup, 0, BFObjIter::ITERTYPE::ALL);
         while( !iter1.end() )
         {
            iter1.deleteObject();            
         }
      }
   }

   if( _pLastActiveAcctSplitComm )
      _pLastActiveAcctSplitComm ->reset ( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
// This method will call validateDateRange to ensure all the date ranges entered
// are unique.
// @param   const BFDataGroupId& idDataGroup - Data group id.
// @param   long lValidateGroup - Validatation group id.
// @returns SEVERITY - Error condition from method validateDateRange
//********************************************************************************
SEVERITY AcctSplitCommList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   validateDateRange( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
// This method validates all the date ranges and ensure the ranges are unique.
// @param   const BFDataGroupId& idDataGroup - Data group id.
// @returns - void but an error condition may be inserted in the condition frame
//********************************************************************************

void AcctSplitCommList::validateDateRange (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateDateRanage" ) );

   DString dstrEffectiveDate, dstrStopDate, dstrEffectiveDate1, dstrStopDate1, dstrCurBusDate;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   bool bActiveDateRange = false;
   DString dstrActive;
   while( !iter.end() )
   {
      iter.getObject()->getField ( ifds::Active, dstrActive, idDataGroup );
      if( dstrActive == YES )
         bActiveDateRange = true;
      ++iter;
   }   
   if( !bActiveDateRange )
      ADDCONDITIONFROMFILE( CND::ERR_ACCT_SPLIT_COMM_NO_ACTIVE_DATE_RANGE );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSplitCommList.cpp-arc  $
// 
//    Rev 1.13   Mar 21 2003 17:56:04   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Oct 29 2002 11:32:24   HSUCHIN
// sync up with release 49 - 1.11
// 
//    Rev 1.11   Oct 09 2002 23:53:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.10   Aug 29 2002 12:54:58   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   Aug 08 2002 15:18:46   HSUCHIN
// changed validateall to only check active field and preliminary enhancement to doDeleteObject.
// 
//    Rev 1.8   Jul 05 2002 17:07:58   HSUCHIN
// bug fix for BFData impl.
// 
//    Rev 1.7   22 May 2002 18:26:18   PURDYECH
// BFData Implementation
// 
//    Rev 1.6   Feb 25 2002 18:55:08   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.5   16 Nov 2001 16:32:04   HSUCHIN
// added date range validation
// 
//    Rev 1.4   25 Sep 2001 15:09:30   HSUCHIN
// added dovalidate all
// 
//    Rev 1.3   13 Sep 2001 10:20:46   HSUCHIN
// bug fix to deleteObject to iter through all added items only
// 
//    Rev 1.2   03 Sep 2001 13:22:44   HSUCHIN
// bug fix and more enhancements
// 
//    Rev 1.1   29 Aug 2001 16:10:56   HSUCHIN
// added enhancements and validations
// 
//    Rev 1.0   23 Aug 2001 14:51:10   HSUCHIN
// Initial revision.
*/

