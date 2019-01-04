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
// ^FILE   : AcctSplitCommRepList.cpp
// ^AUTHOR : 
// ^DATE   : 22/08/2001
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AcctSplitCommRepList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0175_req.hpp>
#include <ifastdataimpl\dse_dstc0175_vw.hpp>
#include "mgmtco.hpp"
#include "acctsplitcommrep.hpp"
#include "acctsplitcommreplist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AcctSplitCommRepList" );   
}

namespace CND
{
   extern const long ERR_SPLIT_RENUNCIATION;
   extern const long ERR_IDENTICAL_SPLIT_COM;
   extern const long ERR_ONE_COMPENSATION_AGENT_IS_ALLOWED;
   extern const long WARN_ONE_COMPENSATION_AGENT_IS_ALLOWED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId SlsrepCode;
   extern CLASS_IMPORT const BFTextFieldId FundServBroker;
   extern CLASS_IMPORT const BFTextFieldId AgencyCode;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const ONE_COMPENSATION_AGENT_IS_ALLOWED;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNT_SPLITCOMM_LIST;
}

//******************************************************************************
// Constructor
//******************************************************************************
AcctSplitCommRepList::AcctSplitCommRepList( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   // Defines this CBO Class as a List
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************
AcctSplitCommRepList::~AcctSplitCommRepList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Initialization of the request object and makes a View call 175
// @param   const DString& dstrAccountNum - Account Number (Required)
// @param   const DString& dstrTrack - Track value (Not required)
// @param   const DString& dstrPageName - Page Name (Not required)
//******************************************************************************
SEVERITY AcctSplitCommRepList::init( const DString& dstrEffectiveDate,
                                     const DString& dstrStopDate,
                                     const BFData& allData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   int iRptCount = allData.getRepeatCount(); 
   DString dstrKey;
   DString t_dstrEffectiveDate;
   DString t_dstrStopDate;

   for( int i = 0; i < iRptCount; i++ )
   {
      const BFData& singleData = allData.getRepeat( i );
      t_dstrEffectiveDate = singleData.getElementValue( ifds::EffectiveDate );
      t_dstrStopDate = singleData.getElementValue( ifds::StopDate );      
      if( ( dstrEffectiveDate == t_dstrEffectiveDate ) && ( dstrStopDate == t_dstrStopDate ) )
      {
         AcctSplitCommRep *pAcctSplitCommRep = new AcctSplitCommRep ( *this );
         pAcctSplitCommRep->init ( singleData );
         getStrKey( dstrKey, &singleData );
         setObject( pAcctSplitCommRep, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST );         
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
// Creates a new AcctSplitCommRep CBO.
// @param   BFCBO*& pBase - BFCBO point to the new AcctSplitCommRep CBO
// @param   DString& strKey - key to access the new CBO
// @param   const BFDataGroupId& idDataGroup
//********************************************************************************
SEVERITY AcctSplitCommRepList::doCreateNewObject( BFCBO*& pBase, 
                                                  DString &strKey, 
                                                  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );   

   pBase = new AcctSplitCommRep ( *this );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
// Method which iterates through all the CBOs and set all matching fields with
// the value passed in.
// @param   const BFFieldId& idField
// @param   const DString dstrValue - value to be set, setField will make copy.
// @param   const BFDataGroupId& idDataGroup
//********************************************************************************
void AcctSplitCommRepList::setCBOFields ( const BFFieldId& idField, 
                                          const DString& dstrValue, 
                                          const BFDataGroupId& idDataGroup )
{
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   AcctSplitCommRep* pAcctSplitCommRep;
   while( !iter.end() )
   {
      pAcctSplitCommRep = static_cast <AcctSplitCommRep*>(iter.getObject());
      pAcctSplitCommRep->setField ( idField, dstrValue, idDataGroup, false );
      ++iter;
   }
}

//******************************************************************************
// This method calls calculates the total renunciation and returns it as a string.
// @param   const BFDataGroupId& idDataGroup
// @returns DString value of total renunciation.
//******************************************************************************
DString AcctSplitCommRepList::getTotalRenunciation( const BFDataGroupId& idDataGroup )
{
   DString dstrCommPrcnt;
   double dTotalCommPrcnt = 0.0;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   AcctSplitCommRep* pAcctSplitCommRep;
   while( !iter.end() )
   {
      pAcctSplitCommRep = static_cast <AcctSplitCommRep*>(iter.getObject());
      pAcctSplitCommRep->getField ( ifds::CommPrcnt, dstrCommPrcnt, idDataGroup, false );
      dTotalCommPrcnt += DSTCommonFunctions::convertToDouble ( dstrCommPrcnt );
      ++iter;
   }   
   return(DSTCommonFunctions::doubleToDString ( ifds::CommPrcnt, dTotalCommPrcnt - 100 ));
}

//********************************************************************************
// Validation method here checks for a unique combination of sales rep, broker and 
// branch.  It also checks the total renunciation amount to be zero.
// @param   const BFDataGroupId& idDataGroup
// @param   long lValidateGroup - Validation Group
// @returns SEVERITY based on the condition added to the frame.
//********************************************************************************
SEVERITY AcctSplitCommRepList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   std::set< DString > dupAcctSplitComm;
   DString dstrCommPrcnt, dstr, dstrCommLevel, dstrBrokerCode, dstrBranchCode, dstrSlsrepCode;
   double dTotalCommPrcnt = 0.0;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   AcctSplitCommRep* pAcctSplitCommRep;
   while( !iter.end() )
   {
      pAcctSplitCommRep = static_cast <AcctSplitCommRep*>(iter.getObject());
      pAcctSplitCommRep->getField ( ifds::CommPrcnt, dstrCommPrcnt, idDataGroup, false );
      dTotalCommPrcnt += DSTCommonFunctions::convertToDouble ( dstrCommPrcnt );
      pAcctSplitCommRep->getField( ifds::CommLevel, dstrCommLevel, idDataGroup );
      dstrCommLevel.strip().upperCase();
      pAcctSplitCommRep->getField( ifds::AgencyCode, dstrBrokerCode, idDataGroup ); 
      dstrBrokerCode.strip().upperCase();
      pAcctSplitCommRep->getField( ifds::BranchCode, dstrBranchCode, idDataGroup ); 
      dstrBranchCode.strip().upperCase();
      pAcctSplitCommRep->getField( ifds::AgentCode, dstrSlsrepCode, idDataGroup ); 
      dstrSlsrepCode.strip().upperCase();
      dstr = dstrCommLevel + dstrBrokerCode + dstrBranchCode + dstrSlsrepCode;
      if( !dupAcctSplitComm.insert(dstr).second )
      {
         ADDCONDITIONFROMFILE( CND::ERR_IDENTICAL_SPLIT_COM );
         return(GETCURRENTHIGHESTSEVERITY());
      }
      ++iter;
   }

   if( fabs( dTotalCommPrcnt - 100 ) > .01 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_SPLIT_RENUNCIATION )
   }

   validateMultipleFundServCommReps(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY AcctSplitCommRepList::validateMultipleFundServCommReps(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMultipleFundServCommReps" ) );

   int numFundServCommReps = 0;
   
   BFObjIter iterSplitCommRep( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   
   while( !iterSplitCommRep.end() )
   {
      AcctSplitCommRep *pAcctSplitCommRep = (AcctSplitCommRep*)iterSplitCommRep.getObject();
      DString dstrBrokerCode;
      pAcctSplitCommRep->getField(ifds::AgencyCode, dstrBrokerCode, idDataGroup);

      if(dstrBrokerCode.stripAll() != I_(""))
      {
         BrokerList* pBrokerList = NULL;
         if ( getWorkSession().getBrokerList (pBrokerList) <= WARNING && 
            pBrokerList)
         {   
            Broker *pBroker = NULL;

            if ( pBrokerList->getBroker (dstrBrokerCode, pBroker) <= WARNING && pBroker)
            {
               DString dstrFundServBroker;
               pBroker->getField(ifds::FundServBroker, dstrFundServBroker, idDataGroup);
               if(dstrFundServBroker.upperCase().stripAll() == I_("Y"))
                  numFundServCommReps++;
            }
         }
      }
      ++iterSplitCommRep;
   }

   // Incident #3287664 - Only one Compensation Agent is applicable for a FundServ broker
   //if(numFundServCommReps > 1)
   if(numFundServCommReps > 0 && iterSplitCommRep.getNumberOfItemsInList() > 1)
   {
      getErrMsg( IFASTERR::ONE_COMPENSATION_AGENT_IS_ALLOWED, 
                  CND::ERR_ONE_COMPENSATION_AGENT_IS_ALLOWED, 
                  CND::WARN_ONE_COMPENSATION_AGENT_IS_ALLOWED, 
                  idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSplitCommRepList.cpp-arc  $
// 
//    Rev 1.10   Mar 21 2003 17:56:16   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:53:58   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 12:54:58   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   Jul 18 2002 17:04:18   HSUCHIN
// PTS - 10009022 - bug fix for duplicate validation of sales rep. 
// 
//    Rev 1.6   22 May 2002 18:26:20   PURDYECH
// BFData Implementation
// 
//    Rev 1.5   23 Nov 2001 11:05:30   HSUCHIN
// validation decimal place check fix
// 
//    Rev 1.4   25 Sep 2001 15:10:52   HSUCHIN
// changed to way renunciation total is calculated
// 
//    Rev 1.3   13 Sep 2001 10:22:58   HSUCHIN
// minor code clean up and bug fix to deleteObject
// 
//    Rev 1.2   03 Sep 2001 13:21:06   HSUCHIN
// code cleanup
// 
//    Rev 1.1   29 Aug 2001 16:10:56   HSUCHIN
// added enhancements and validations
// 
//    Rev 1.0   23 Aug 2001 14:51:12   HSUCHIN
// Initial revision.
*/

