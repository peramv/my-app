//******************************************************************************
//
// COPYRIGHT:
//
//    Th* comput;
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : BrokerFeaturesSearchProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BrokerFeaturesSearchProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "brokerfeaturessearchprocess.hpp"
#include "brokerfeaturessearchprocessincludes.h"
#include <ifastcbo\fillsearchcriteria.hpp>
#include "searchprocessincludes.h"
#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PAY_TO_ENTITY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HISTORICAL_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PAYMENT_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_BROKER_FEATURES_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BROKER_FEATURES_SEARCH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BrokerFeaturesSearchProcess > processCreator(CMD_BPROC_BROKER_FEATURES_SEARCH);

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("BrokerFeaturesSearchProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace SEARCHTYPE
{
   extern CLASS_IMPORT I_CHAR * const BROKER_FEATURES;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const SLS;
   extern CLASS_IMPORT I_CHAR * const BRK;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
}

namespace PAY_TO
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

BrokerFeaturesSearchProcess::BrokerFeaturesSearchProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),  
_rpChildGI(NULL), 
_pFillSearchCriteria(NULL),
_initSearchCriteria(NULL_STRING),
_initSearchUsing(NULL_STRING),
_backgroundSearch(I_("N"))
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addContainer(IFASTBP_PROC::SEARCH_CRITERIA_FILLER, false, BF::NullContainerId, true);

   addFieldDetails(ifds::SearchCriteria, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchUsing, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchLabel1, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchLabel2, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchLabel3, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchFieldCriteria1, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchFieldCriteria2, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchFieldCriteria3, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::HowManySearchCriterias, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(IsSearchCriteria1Broker, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsSearchCriteria2Branch, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsSearchCriteria3SlsRep, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
}

//******************************************************************************
BrokerFeaturesSearchProcess::~BrokerFeaturesSearchProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;
   if (_pFillSearchCriteria)
   {
      delete _pFillSearchCriteria;
      _pFillSearchCriteria = NULL;
   }
}

//************************************************************************************
SEVERITY BrokerFeaturesSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      DSTCWorkSession *pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      _pFillSearchCriteria = new FillSearchCriteria(*pDSTCWorkSession);
      if (_pFillSearchCriteria->init(SEARCHTYPE::BROKER_FEATURES, 
         BF::HOST) <= WARNING)
      {
         setContainer(IFASTBP_PROC::SEARCH_CRITERIA_FILLER, _pFillSearchCriteria);
         //load the parameters for search if they exist
         getParameter(MFCAN_IP_PARAM::SEARCH_CRITERIA, _initSearchCriteria);
         getParameter(MFCAN_IP_PARAM::SEARCH_USING, _initSearchUsing);
         getParameter(MFCAN_IP_PARAM::BACKGROUND_SEARCH, _backgroundSearch);
         if (_initSearchCriteria != NULL_STRING)
         {
            _pFillSearchCriteria->setField(ifds::SearchCriteria, _initSearchCriteria, 
               getDataGroupId(), false);
         }
         if (_initSearchUsing != NULL_STRING)
         {
            _pFillSearchCriteria->setField(ifds::SearchUsing, _initSearchUsing, 
               getDataGroupId(), false);
         }
      }
   }
   catch(ConditionException& ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN BrokerFeaturesSearchProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(MFCAN_IP_PARAM::BACKGROUND_SEARCH, _backgroundSearch);
      rtn = invokeCommand(this, CMD_GUI_BROKER_FEATURES_SEARCH, 
            PROC_NO_TYPE, isModal(), &_rpChildGI);
   }
   catch(ConditionException &ce)
   {
      assert(0);
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
bool BrokerFeaturesSearchProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_BROKER_FEATURES_SEARCH);
}

//******************************************************************************
void BrokerFeaturesSearchProcess::doGetField(const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, DString &strValueOut,
   bool bFormatted) const
{
   strValueOut = NULL_STRING;
   if (idField == IsSearchCriteria1Broker)
   {
      strValueOut = _pFillSearchCriteria->isSearchCriteria1Broker(idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsSearchCriteria2Branch)
   {
      strValueOut = _pFillSearchCriteria->isSearchCriteria2Branch(idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsSearchCriteria3SlsRep)
   {
      strValueOut = _pFillSearchCriteria->isSearchCriteria3SlsRep(idDataGroup) ? 
         I_("Y") : I_("N");
   }
}

//******************************************************************************
SEVERITY BrokerFeaturesSearchProcess::performSearch(GenericInterface *rpGI, 
   const BFContainerId &idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));

   try
   {
      const BFDataGroupId &idDataGroup = getDataGroupId();

      if (eSearchAction == SEARCH_START)
      {
         if (_pFillSearchCriteria->validateAll(idDataGroup) <= WARNING)
         {
            E_COMMANDRETURN rtn = CMD_FAILURE;
            DString searchCriteria, 
               searchUsing;
            DString firstValue, 
               secondValue, 
               thirdValue;
            const I_CHAR* launchProcessId = NULL;

            getField(this, idSearch, 
               ifds::SearchCriteria, searchCriteria, false);
            getField(this, idSearch, 
               ifds::SearchUsing, searchUsing, false);
            getField(this, idSearch, 
               ifds::SearchFieldCriteria1, firstValue, false);
            getField(this, idSearch, 
               ifds::SearchFieldCriteria2, secondValue, false);
            getField(this, idSearch, 
               ifds::SearchFieldCriteria3, thirdValue, false);
            //call the appropriate processes
            if (searchCriteria == BF_SEARCH_CRITERIA::BANKING)
            {
               if (searchUsing == BF_SEARCH_BANKING_USING::BROKER)
               {
                  setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::BROKER);
                  setParameter(MFCAN_IP_PARAM::BROKER_CODE, firstValue);
               }
               else if (searchUsing == BF_SEARCH_BANKING_USING::BRANCH)
               {
                  setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::BRANCH);
                  setParameter(MFCAN_IP_PARAM::BROKER_CODE, firstValue);
                  setParameter(MFCAN_IP_PARAM::BRANCH_CODE, secondValue);
               }
               else if (searchUsing == BF_SEARCH_BANKING_USING::SLSREP)
               {
                  setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::SALESREP);
                  setParameter(MFCAN_IP_PARAM::BROKER_CODE, firstValue);
                  setParameter(MFCAN_IP_PARAM::BRANCH_CODE, secondValue);
                  setParameter(MFCAN_IP_PARAM::SALES_REP_CODE, thirdValue);
               }
               launchProcessId = CMD_BPROC_BANK_INSTRUCTIONS;
            }
            else if (searchCriteria == BF_SEARCH_CRITERIA::PAY_TO_ENTITY)
            {
               if (searchUsing == BF_SEARCH_PAY_TO_ENTITY_USING::BROKER)
               {
                  setParameter(MFCAN_IP_PARAM::BROKER_CODE, firstValue);
               }
               launchProcessId = CMD_BPROC_PAY_TO_ENTITY;
            }
            else if (searchCriteria == BF_SEARCH_CRITERIA::HISTORICAL_INFO)
            {
               DString tableId, 
                  keyStringIDI;

               if (searchUsing == BF_SEARCH_HISTORICAL_INFO_USING::BROKER)
               {
                  tableId = AUDITTYPE::BRK;
                  addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BROKER_CODE, 
                     firstValue);
               }
               else if (searchUsing == BF_SEARCH_HISTORICAL_INFO_USING::SLSREP)
               {
                  tableId = AUDITTYPE::SLS;
                  addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BROKER_CODE, 
                     firstValue);
                  addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BRANCH_CODE, 
                     secondValue);
                  addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::SALES_REP_CODE, 
                     thirdValue);
               }
               if (tableId != NULL_STRING)
               {
                  setParameter(MFCAN_IP_PARAM::TABLEID, tableId);
                  setParameter(MFCAN_IP_PARAM::KEYS, keyStringIDI);
                  setParameter(MFCAN_IP_PARAM::RECID, NULL_STRING);
                  //no updates, call it modal
                  rtn = invokeCommand(this, CMD_BPROC_HISTORICAL_INFO, 
                     getProcessType(), true, NULL);
               }
            }
            else if (searchCriteria == BF_SEARCH_CRITERIA::PAYMENT_INSTRUCTIONS)
            {
               if (searchUsing == BF_SEARCH_PAYMENT_INSTRUCTIONS_USING::BROKER)
               {
                  setParameter(MFCAN_IP_PARAM::BROKER_CODE, firstValue);
                  setParameter(I_("PayToEntity"), PAY_TO::BROKER);
               }
               else if (searchUsing == BF_SEARCH_PAYMENT_INSTRUCTIONS_USING::BRANCH)
               {
                  setParameter(MFCAN_IP_PARAM::BROKER_CODE, firstValue);
                  setParameter(MFCAN_IP_PARAM::BRANCH_CODE, secondValue);
                  setParameter(I_("PayToEntity"), PAY_TO::BRANCH);
               }
               else if (searchUsing == BF_SEARCH_PAYMENT_INSTRUCTIONS_USING::SLSREP)
               {
                  setParameter(MFCAN_IP_PARAM::BROKER_CODE, firstValue);
                  setParameter(MFCAN_IP_PARAM::BRANCH_CODE, secondValue);
                  setParameter(MFCAN_IP_PARAM::SALES_REP_CODE, thirdValue);
                  setParameter(I_("PayToEntity"), PAY_TO::SALESREP);
               }
               launchProcessId = CMD_BPROC_PAYMENT_INSTRUCTIONS;
            }
            if (launchProcessId != NULL)
            {
               //parent is this process, so we can destroy all the gui children,
               //if necessary
               rtn = invokeCommand(this, launchProcessId, 
                  getProcessType(), false, NULL);
            }
         }
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, 
         I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerFeaturesSearchProcess.cpp-arc  $
// 
//    Rev 1.4   Jul 10 2003 22:19:18   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.3   Jul 09 2003 21:55:34   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.2   Jul 02 2003 17:49:24   popescu
// work for payment instructions feature 
// 
//    Rev 1.1   Jul 01 2003 18:04:46   popescu
// Added the discard/cancel dialog if user clicks search again; changed the children processes to modeless, instead of modal
// 
//    Rev 1.0   Jun 27 2003 18:15:14   popescu
// Initial revision.
// 
 *
 */
