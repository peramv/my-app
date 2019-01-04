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
// ^FILE   : AcctSplitComm.cpp
// ^AUTHOR : 
// ^DATE   : Aug 22, 2001
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AcctSplitComm
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
#include <ifastdataimpl\dse_dstc0175_vw.hpp>
#include "mfaccount.hpp"
#include "mgmtcooptions.hpp"

//******************************************************************************
namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AcctSplitComm" );
   const I_CHAR * const ACCT_SPLITCOMM_REP_LIST = I_( "AcctSplitCommRepList" );
   const I_CHAR * const YES = I_( "Y" );
}

//******************************************************************************
namespace CND
{  // Conditions used
   extern const long ERR_NEW_SPLIT_PERIOD_OVERLAPS;   
   extern const long ERR_ACCT_SPLIT_COMM_INVALID_DATE_RANGE;   
}

//******************************************************************************
namespace ifds
{   
   extern CLASS_IMPORT const BFDecimalFieldId CommAmount;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
	extern CLASS_IMPORT const BFDateFieldId FirstEffective;
}

//******************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags    
   { ifds::Active,        BFCBO::NONE,      0 }, 
   { ifds::EffectiveDate, BFCBO::NONE,      0 }, 
   { ifds::StopDate,      BFCBO::READ_ONLY, 0 }, 
};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
// Constructor
//******************************************************************************
AcctSplitComm::AcctSplitComm( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, _pLastActiveAcctSplitComm (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   // Registers fields to be used for storing data
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
}

//******************************************************************************
// Destructor
//******************************************************************************
AcctSplitComm::~AcctSplitComm()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _pLastActiveAcctSplitComm  = NULL;
}

//******************************************************************************
// Creates the AcctSplitComm CBO based on the data passed in.
// @param   DString& dstrEffectiveDate - Effective Date of the current view Data
//             be added.
// @param   DString& dstrStopDate - Stop Date of the current view Data to be added
// @param   const Data& acctSplitCommData - point to one data set from view.
// @param   const Data& allData - pointer to data returned from the view.
// @param   bool bBaseDelete - Flag to detemine who deletes the CBO
// @returns SEVERITY passed from AcctSplitCommRepList or BFCBO severity.
//******************************************************************************
SEVERITY AcctSplitComm::init( DString& dstrEffectiveDate,
                              DString& dstrStopDate,
                              const BFData& acctSplitCommData,
                              const BFData& allData, 
                              bool bBaseDelete )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   // Call BFCBO attachDataObject
   attachDataObject( const_cast<BFData&>(acctSplitCommData), bBaseDelete );
   allFieldsReadOnly ( true, BF::HOST );
   DString dstrFinalStopDate, dstrCurrBusDate;
   DSTCommonFunctions::getFormat12319999Date(dstrFinalStopDate);
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, BF::HOST, false );
   if( //DSTCommonFunctions::CompareDates ( dstrStopDate, dstrFinalStopDate ) == DSTCommonFunctions::EQUAL &&
       DSTCommonFunctions::CompareDates ( dstrEffectiveDate, dstrCurrBusDate ) == DSTCommonFunctions::SECOND_EARLIER )
   {

      setFieldReadOnly ( ifds::EffectiveDate, BF::HOST, false );
   }

   // Pass the data from the view call to AcctSplitCommRepList for further processing
   AcctSplitCommRepList *pAcctSplitCommRepList = new AcctSplitCommRepList( *this );
   if( pAcctSplitCommRepList->init( dstrEffectiveDate, dstrStopDate, allData ) <= WARNING )
      setObject( pAcctSplitCommRepList, ACCT_SPLITCOMM_REP_LIST, OBJ_ACTIVITY_NONE, BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Retrives the Split Commission Rep List from the repository.   If the list is
// not found in the repository, create a new list.
// @param   AcctSplitCommRepList*& pAcctSplitCommRepList - pointer to Split Comm
//                                  Rep List
// @param   const BFDataGroupId& idDataGroup - The data group this cbo belongs to.
// @returns SEVERITY, in most cases NO_CONDITION or severity from BFCBO.                                   
//******************************************************************************
SEVERITY AcctSplitComm::getAcctSplitCommRepList ( AcctSplitCommRepList*& pAcctSplitCommRepList, 
                                                  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctSplitCommRepList" ) );

   pAcctSplitCommRepList = dynamic_cast<AcctSplitCommRepList *>( BFCBO::getObject( ACCT_SPLITCOMM_REP_LIST, idDataGroup ) );
   // If the list does not exist in the repository, we assume that there are no representative 
   // for the current date range.  Therefore we return an empty list and set it as added.
   if( !pAcctSplitCommRepList )
   {
      pAcctSplitCommRepList = new AcctSplitCommRepList( *this );            
      setObject( pAcctSplitCommRepList, ACCT_SPLITCOMM_REP_LIST, OBJ_ACTIVITY_ADDED, idDataGroup ); 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Field validation occurs here.
// @param   const BFFieldId& idField - Id of field to be validated.
// @param   const DString& strValue - Value of field to be validated
// @param   const BFDataGroupId& idDataGroup - the data group this cbo belongs to.
// @returns SEVERITY, 
//       SEVER_ERROR - ERR_START_DATE_LATE_THAN_STOP_DATE.
//******************************************************************************
SEVERITY AcctSplitComm::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );

   if( idField == ifds::EffectiveDate || idField == ifds::StopDate )
   {
      validateDateRange (idDataGroup);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//******************************************************************************

void AcctSplitComm::allFieldsReadOnly( bool benable, const BFDataGroupId& idDataGroup )
{
   const CLASS_FIELD_INFO* pClassFieldInfo = (const CLASS_FIELD_INFO *)&classFieldInfo;
   for( int i = 0; i < NUM_FIELDS; i++, pClassFieldInfo++ )
   {
      setFieldReadOnly ( pClassFieldInfo->m_fieldId, idDataGroup, benable );
   }   
}

//******************************************************************************
//******************************************************************************

SEVERITY AcctSplitComm::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
   if( idField == ifds::EffectiveDate || idField == ifds::StopDate || idField == ifds::Active )
   {
      // If the fields effective date and stop date is added or updated we need to
      // set each of the AcctSpltiCommRep CBOs to the same effective/stop date
      AcctSplitCommRepList* pAcctSplitCommRepList;
      if( getAcctSplitCommRepList ( pAcctSplitCommRepList, idDataGroup ) <= WARNING )
      {
         DString dstrValue;
         getField ( idField, dstrValue, idDataGroup );
         pAcctSplitCommRepList->setCBOFields ( idField, dstrValue, idDataGroup );
      }
      if( idField == ifds::EffectiveDate )
      {
         if ( ( _pLastActiveAcctSplitComm ) && ( _pLastActiveAcctSplitComm != this ) )
         {
            DString dstrEffectiveDate, dstrStopDate, dstrActive;
            getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
            DSTCommonFunctions::subtractDays ( dstrEffectiveDate, dstrStopDate, 1 );
            _pLastActiveAcctSplitComm->setField ( ifds::StopDate, dstrStopDate, idDataGroup, true, true );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//******************************************************************************
void AcctSplitComm::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString dstrStopDate, dstrDefaultStartDate, dstrAccountNum, dstrEndDate, dstrLastEffectiveDate;
   // Get the current business date
	
   //getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrDefaultStartDate, idDataGroup, false );
   // Get the stop date of 12/31/9999
   DSTCommonFunctions::getFormat12319999Date(dstrStopDate);

   // We will ask the parent for the last ActiveSplitComm

   AcctSplitCommList *pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> (getParent());
	MFAccount* pMFAccount = NULL;

   pAcctSplitCommList->getAccountNum ( dstrAccountNum );     
   getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount );
	if ( pMFAccount )
		pMFAccount->getField (ifds::FirstEffective, dstrDefaultStartDate, idDataGroup );

   _pLastActiveAcctSplitComm = pAcctSplitCommList->getLastActiveAcctSplitComm ();

   if( _pLastActiveAcctSplitComm )
   {
      _pLastActiveAcctSplitComm->getField ( ifds::EffectiveDate, dstrLastEffectiveDate, idDataGroup, false );
      if( DSTCommonFunctions::CompareDates ( dstrLastEffectiveDate, dstrDefaultStartDate ) == DSTCommonFunctions::FIRST_EARLIER )
      {
         setFieldNoValidate( ifds::EffectiveDate, dstrDefaultStartDate, idDataGroup, false, true, true, false );      
      }
      else
      {
         if( dstrLastEffectiveDate != NULL_STRING )
            DSTCommonFunctions::addDays ( dstrLastEffectiveDate, dstrDefaultStartDate, 1 );
         else
            dstrLastEffectiveDate = dstrDefaultStartDate;
         setFieldNoValidate( ifds::EffectiveDate, dstrDefaultStartDate, idDataGroup, false, true, true, false );
      }
      DSTCommonFunctions::subtractDays ( dstrDefaultStartDate, dstrEndDate, 1 );
      _pLastActiveAcctSplitComm->setField ( ifds::StopDate, dstrEndDate, idDataGroup, false, true, true );
   }
   else 
   {
	   if( pMFAccount && pMFAccount->isNew() )
	   {
			DString dstrConfiguration( I_( "HostMasks" ) );
			DString dstrKey( I_("D") ), Date;
			Date = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );
			Date.replace(Date.find(I_("MM")), 2, I_("01"));
			Date.replace(Date.find(I_("dd")), 2, I_("20"));
			Date.replace(Date.find(I_("yyyy")), 4, I_("1997"));
		    setFieldNoValidate( ifds::EffectiveDate, Date, idDataGroup, false, true, true );
	   }
	   else
	   {
		   setFieldNoValidate( ifds::EffectiveDate, dstrDefaultStartDate, BF::HOST, false, true, true );
	   }
   }
   setFieldNoValidate( ifds::StopDate, dstrStopDate, idDataGroup, false, true, true, false );
   setFieldReadOnly ( ifds::StopDate, idDataGroup, true );
   setFieldNoValidate( ifds::Active, YES, idDataGroup, false, true, false, false );
 //  MFAccount* pMFAccount = NULL;

   //pAcctSplitCommList->getAccountNum ( dstrAccountNum );     
   //getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount );
   if( pMFAccount && pMFAccount->isNew() )
      setNonDummyFlag();
}


//********************************************************************************
// This method validates all the date ranges and ensure the ranges are unique.
// @param   const BFDataGroupId& idDataGroup - Data group id.
// @returns - void but an error condition may be inserted in the condition frame
//********************************************************************************

void AcctSplitComm::validateDateRange (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateDateRanage" ) );

   DString dstrEffectiveDate, dstrStopDate, dstrEffectiveDate1, dstrStopDate1, dstrCurBusDate;
   DString dstrStrKey, dstrStrKey1;
   getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
   getField ( ifds::StopDate, dstrStopDate, idDataGroup );   

   if( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrStopDate ) == DSTCommonFunctions::SECOND_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NEW_SPLIT_PERIOD_OVERLAPS );                        
      return;
   }
   AcctSplitCommList *pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent() );
   BFObjIter iter( *pAcctSplitCommList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFAbstractCBO *pBFCBO;
   while( !iter.end() )
   {
      pBFCBO = iter.getObject();
      //dstrStrKey1 = iter.getStringKey ();
      if( !iter.isDummy() && pBFCBO && pBFCBO != this )
      {
         pBFCBO->getField(ifds::EffectiveDate, dstrEffectiveDate1, idDataGroup);
         pBFCBO->getField(ifds::StopDate, dstrStopDate1, idDataGroup);
         if( DSTCommonFunctions::CompareDates( dstrEffectiveDate1, dstrStopDate ) == DSTCommonFunctions::FIRST_EARLIER  &&
             DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrStopDate1 ) == DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILE( CND::ERR_NEW_SPLIT_PERIOD_OVERLAPS );                        
            return;
         }
      }
      ++iter;
   }
}

void AcctSplitComm::set9999StopDate (const BFDataGroupId& idDataGroup)
{
   DString dstrStopDate;
   DSTCommonFunctions::getFormat12319999Date(dstrStopDate);
   setFieldNoValidate( ifds::StopDate, dstrStopDate, idDataGroup, false, true, true, true );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSplitComm.cpp-arc  $
// 
//    Rev 1.15   Apr 22 2005 14:04:36   Fengyong
// Incident #290689 - hard code 01/20/1997 as the effective date for new account's split commission.
// 
//    Rev 1.14   Nov 14 2004 14:25:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   Jul 14 2003 10:30:56   ZHANGCEL
// PTS 10017614 : Modify the Account level commrep "Add" mode to default the Effective Date to the First Effective Date in  MFAccount.
// 
//    Rev 1.12   Mar 21 2003 17:56:00   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Oct 29 2002 11:28:04   HSUCHIN
// sync up with release49 - 1.10
// 
//    Rev 1.10   Oct 09 2002 23:53:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.9   Aug 29 2002 12:54:56   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.8   Aug 13 2002 15:08:18   HSUCHIN
// bug fix for cancel from coa. 
// 
//    Rev 1.7   Aug 08 2002 15:14:34   HSUCHIN
// new error conditions, fixed date range validation and changed doinitwithdefault values to set the effective date to the next possible date not defined in the account level split commission
// 
//    Rev 1.6   05 Jun 2002 14:05:26   SMITHDAV
// Change occurances of
// DSTCommonFunctions::DATE_ORDER::EQUAL
// to DSTCommonFunctions::EQUAL.
// 
//    Rev 1.5   22 May 2002 18:26:18   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   16 Nov 2001 16:31:20   HSUCHIN
// bug fix for stop date of previous active record
// 
//    Rev 1.3   13 Sep 2001 10:20:08   HSUCHIN
// added validation conditions and bug fix to doinitwithdefaults
// 
//    Rev 1.2   03 Sep 2001 13:23:24   HSUCHIN
// new condition and validation rule
// 
//    Rev 1.1   29 Aug 2001 16:10:58   HSUCHIN
// added enhancements and validations
// 
//    Rev 1.0   23 Aug 2001 14:51:10   HSUCHIN
// Initial revision.
*/

