//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
//    ^FILE   : HistoricalInfoSearchCriteria.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : Feb 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : HistoricalInfoSearchCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "HistoricalInfoSearchCriteria.hpp"
#include "FundClassRules.hpp"
#include "branchlist.hpp"
#include "agentlist.hpp"
#include "brokerlist.hpp"
#include "broker.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0237_vwrepeat_record.hpp>

namespace 
{
   const I_CHAR *  CLASSNAME = I_( "HistoricalInfoSearchCriteria" );
}


namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const FDE;
}

namespace ifds
{
   //field ids used
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId FundName;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId SalesRepCode;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId SalesRepName;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId HistoricalSearchInfo;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //  Field DD Id,        State Flags,       Group Flags 
   { ifds::FundCode, BFCBO::NONE, 0 }, 
   { ifds::ClassCode, BFCBO::NONE, 0 }, 
   { ifds::FundName, BFCBO::NONE, 0 }, 
   { ifds::BrokerCode,BFCBO::NONE, 0 }, 
   { ifds::BrokerName, BFCBO::NONE, 0 }, 
   { ifds::SalesRepCode, BFCBO::NONE, 0 }, 
   { ifds::SalesRepName, BFCBO::NONE, 0 }, 
   { ifds::BranchCode, BFCBO::NONE, 0 }, 
   { ifds::BranchName, BFCBO::NONE, 0 }, 
   { ifds::FundGroup, BFCBO::NONE, 0 }, 
   { ifds::HistoricalSearchInfo, BFCBO::NONE, 0 }, 
   //cross edits
   { ifds::FundClass,  BFCBO::IMMEDIATE_VALIDATION, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************
HistoricalInfoSearchCriteria::HistoricalInfoSearchCriteria(BFAbstractCBO &parent) 
: MFCanBFCbo(parent),
m_pFundClassRules(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   registerMemberData(NUM_FIELDS,
                      (const CLASS_FIELD_INFO *)&classFieldInfo,
                      0,
                      NULL);
   //fund class
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
   //compund date
   m_pFundClassRules = new FundClassRules(*this);
}

//******************************************************************************
HistoricalInfoSearchCriteria::~HistoricalInfoSearchCriteria()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (m_pFundClassRules != NULL) 
   {
      delete m_pFundClassRules;
   }
}

//******************************************************************************
SEVERITY HistoricalInfoSearchCriteria::init(const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   m_pFundClassRules->init();
   setFieldNoValidate(ifds::HistoricalSearchInfo, AUDITTYPE::FDE, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY HistoricalInfoSearchCriteria::doApplyRelatedChanges( 
   const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   setUpdatedFlag(idField, idDataGroup, false);
   if (idField == ifds::FundClass) 
   {
      DString dstrFundCode, dstrFundName;

      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      //retrieve the fund name
      getWorkSession().getFundName(dstrFundCode, dstrFundName);
      setField(ifds::FundName, dstrFundName, idDataGroup, false, true);
   } else if (idField == ifds::BrokerCode)
   {
      BrokerList *_pBrokerList;
      DString dstrBrokerName;
         
      if (getWorkSession().getBrokerList(_pBrokerList) <= WARNING)
      {
         Broker *_pBroker;
         DString dstrBrokerCode;

         getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
         if (_pBrokerList != NULL && 
               _pBrokerList->getBroker(dstrBrokerCode, _pBroker) <= WARNING) 
         {
            if (_pBroker != NULL)
            {
               _pBroker->getField(ifds::BrokerName, dstrBrokerName, idDataGroup, false);
            }
         }
      }
      setField(ifds::BrokerName, dstrBrokerName, idDataGroup, false, true);
   } else if (idField == ifds::SalesRepCode)
   {
      AgentList *_pAgentList;
      DString dstrBrokerCode, dstrBranchCode;
      DString dstrSalesRepName;
            
      getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
      getField(ifds::BranchCode, dstrBranchCode, idDataGroup, false);
      _pAgentList = new AgentList(getWorkSession());
      if(_pAgentList->init(dstrBrokerCode, dstrBranchCode, NULL_STRING))
      {
         DString dstrSalesRepCode;
         BFData tempData;
         BFObjIter iterAgent(*_pAgentList, idDataGroup);

         getField(ifds::SalesRepCode, dstrSalesRepCode, idDataGroup, false);
         tempData.setElementValue(ifds::Slsrep, dstrSalesRepCode, true, NULL);
         iterAgent.positionOnNextMatch(tempData, idDataGroup);
         if( !iterAgent.end() )
         {
            iterAgent.getObject()->getField(ifds::SlsrepName, dstrSalesRepName, idDataGroup);
         }
      }
      setField(ifds::SalesRepName, dstrSalesRepName, idDataGroup, false, true);

   } else if (idField == ifds::BranchCode)
   {
      BranchList *_pBranchList;
      DString dstrBrokerCode;
      DString dstrBranchName;

      getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
      _pBranchList = new BranchList(getWorkSession());

      if (_pBranchList->init(dstrBrokerCode, NULL_STRING) <= WARNING)
      {
         DString dstrBranchCode;
         BFData tempData;
         BFObjIter iterBranch(*_pBranchList, idDataGroup);

         getField(ifds::BranchCode, dstrBranchCode, idDataGroup, false);
         tempData.setElementValue(ifds::BranchCode, dstrBranchCode, true, NULL);
         iterBranch.positionOnNextMatch(tempData, idDataGroup);
         if( !iterBranch.end() )
         {
            iterBranch.getObject()->getField(ifds::BranchName, dstrBranchName, idDataGroup);
         }
      }
      setField(ifds::BranchName, dstrBranchName, idDataGroup, false, true);
   } else if (idField == ifds::HistoricalSearchInfo)
   {
      //clear all fields
      setFieldNoValidate(ifds::FundCode, NULL_STRING, idDataGroup, 
         true, true, true, false);
      setFieldNoValidate(ifds::ClassCode, NULL_STRING, idDataGroup, 
         true, true, true, false);
      setFieldNoValidate(ifds::FundName, NULL_STRING, idDataGroup, 
         true, true, true, false);
      setFieldNoValidate(ifds::BrokerCode, NULL_STRING, idDataGroup, 
         true, true, true, false);
      setFieldNoValidate(ifds::BrokerName, NULL_STRING, idDataGroup, 
         true, true, true, false);
      setFieldNoValidate(ifds::SalesRepCode, NULL_STRING, idDataGroup, 
         true, true, true, false);
      setFieldNoValidate(ifds::SalesRepName, NULL_STRING, idDataGroup, 
         true, true, true, false);
      setFieldNoValidate(ifds::BranchCode, NULL_STRING, idDataGroup, 
         true, true, true, false);
      setFieldNoValidate(ifds::BranchName, NULL_STRING, idDataGroup, 
         true, true, true, false);
      setFieldNoValidate(ifds::FundGroup, NULL_STRING, idDataGroup, 
         true, true, true, false);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalInfoSearchCriteria.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:44:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Mar 21 2003 18:13:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Feb 11 2003 15:22:20   popescu
// Bug fixes
// 
//    Rev 1.1   Feb 11 2003 14:41:52   popescu
// changes related to the Historical information for Broker and Sales rep, as well as displaying the names for them in the Historical Info Search dialog
// 
//    Rev 1.0   Feb 06 2003 11:54:22   popescu
// Initial revision.
 */