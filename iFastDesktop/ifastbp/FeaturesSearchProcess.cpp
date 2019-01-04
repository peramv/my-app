//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : FeaturesSearchProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FeaturesSearchProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "featuressearchprocess.hpp"
#include "featuressearchprocessincludes.h"
#include <ifastcbo\fillsearchcriteria.hpp>
#include "mfcaninterprocparam.hpp"
#include "FundSponsorFeeModelProcess.hpp"
#include "FundSponsorFeeModelProcessinclude.h"
#include "FundBrokerProcessinclude.h"
#include "AggregatedOrderProcessinclude.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PAY_TO_ENTITY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HISTORICAL_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PAYMENT_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FINANCIAL_INSTITUTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FEATURES_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FEATURES_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANSITS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DAILY_TRANSACTION_FEES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDSPONSOR_FEE_MODEL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_BROKER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AGGREGATED_ORDER;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FeaturesSearchProcess > processCreator(CMD_BPROC_FEATURES_SEARCH);

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("FeaturesSearchProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
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


namespace DAILY_TRANSACTIONS_FEES_CODE
{
   extern CLASS_EXPORT I_CHAR * const DAILY_TRANSACTIONS_FEES = I_("96");
   extern CLASS_EXPORT I_CHAR * const CLASS_EFF_HURDLE_RATE   = I_("201");
}


//******************************************************************************
//              Public Methods
//******************************************************************************

FeaturesSearchProcess::FeaturesSearchProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),  
_rpChildGI(NULL), 
_pFillSearchCriteria (NULL),
_searchType (NULL_STRING),
_initSearchCriteria (NULL_STRING),
_initSearchUsing (NULL_STRING),
_backgroundSearch (I_("N"))
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addContainer(IFASTBP_PROC::SEARCH_CRITERIA_FILLER, false, BF::NullContainerId, true);

   addFieldDetails(ifds::FillSearchType, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchCriteria, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchUsing, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchLabel1, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchLabel2, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchLabel3, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchLabel4, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
	addFieldDetails(ifds::SearchLabel5, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchLabel6, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchLabel7, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);

   addFieldDetails(ifds::SearchFieldCriteria1, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchFieldCriteria2, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchFieldCriteria3, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchFieldCriteria4, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
	addFieldDetails(ifds::SearchFieldCriteria5, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchFieldCriteria6, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(ifds::SearchFieldCriteria7, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);

   addFieldDetails(ifds::HowManySearchCriterias, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails(IsBFSearchCriteria1Broker, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsBFSearchCriteria2Branch, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsBFSearchCriteria3SlsRep, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsFISearchCriteria1Name, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsFISearchCriteria3Name, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsFISearchCriteria3Code, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsDTFSearchCriteria2Fund, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsDTFSearchCriteria3Class, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsFMSearchCriteriaFeeModel, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsFMSearchCriteriaSponsor, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsFMSearchCriteriaFundBrokerCode, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(IsFMSearchCriteriaFundBrokerName, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
	addFieldDetails(isFMSearchCriteriaAggregationTradeDate, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(isFMSearchCriteriaAggregationAggrOrdNo, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
	addFieldDetails(isFMSearchCriteriaAggregationRoutRefNo, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
   addFieldDetails(isFMSearchCriteriaAggregationStatus, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SUBCLASS_PROCESS);
}

//******************************************************************************
FeaturesSearchProcess::~FeaturesSearchProcess()
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
SEVERITY FeaturesSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      DSTCWorkSession *pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      getParameter (MFCAN_IP_PARAM::SEARCH_TYPE, _searchType);
      assert(_searchType != NULL_STRING); //just checking...
      _pFillSearchCriteria = new FillSearchCriteria(*pDSTCWorkSession);
      if (_pFillSearchCriteria->init (_searchType, BF::HOST) <= WARNING)
      {
         setContainer (IFASTBP_PROC::SEARCH_CRITERIA_FILLER, _pFillSearchCriteria);
         //load the parameters for search if they exist
         getParameter(MFCAN_IP_PARAM::SEARCH_CRITERIA, _initSearchCriteria);
         getParameter(MFCAN_IP_PARAM::SEARCH_USING, _initSearchUsing);
         getParameter(MFCAN_IP_PARAM::BACKGROUND_SEARCH, _backgroundSearch);
         if (_initSearchCriteria != NULL_STRING)
         {
            _pFillSearchCriteria->setField (ifds::SearchCriteria, _initSearchCriteria, 
               getDataGroupId(), false);
         }
         if (_initSearchUsing != NULL_STRING)
         {
            _pFillSearchCriteria->setField (ifds::SearchUsing, _initSearchUsing, 
               getDataGroupId(), false);
         }
      }
   }
   catch (ConditionException& ce)
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
E_COMMANDRETURN FeaturesSearchProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(MFCAN_IP_PARAM::BACKGROUND_SEARCH, _backgroundSearch);
      rtn = invokeCommand(this, CMD_GUI_FEATURES_SEARCH, 
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
bool FeaturesSearchProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_FEATURES_SEARCH);
}

//******************************************************************************
void FeaturesSearchProcess::doGetField(const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, DString &strValueOut,
   bool bFormatted) const
{
   strValueOut = NULL_STRING;
   if (idField == IsBFSearchCriteria1Broker)
   {
      strValueOut = _pFillSearchCriteria->isBFSearchCriteria1Broker (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsBFSearchCriteria2Branch)
   {
      strValueOut = _pFillSearchCriteria->isBFSearchCriteria2Branch (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsBFSearchCriteria3SlsRep)
   {
      strValueOut = _pFillSearchCriteria->isBFSearchCriteria3SlsRep (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsFISearchCriteria1Name)
   {
      strValueOut = _pFillSearchCriteria->isFISearchCriteria1Name (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsFISearchCriteria3Name)
   {
      strValueOut = _pFillSearchCriteria->isFISearchCriteria3Name (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsFISearchCriteria3Code)
   {
      strValueOut = _pFillSearchCriteria->isFISearchCriteria3Code (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsDTFSearchCriteria2Fund)
   {
      strValueOut = _pFillSearchCriteria->isDTFSearchCriteria2FundCode (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsDTFSearchCriteria3Class)
   {
      strValueOut = _pFillSearchCriteria->isDTFSearchCriteria3ClassCode (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsFMSearchCriteriaFeeModel)
   {
      strValueOut = _pFillSearchCriteria->isFMSearchCriteriaFeeModel (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsFMSearchCriteriaSponsor)
   {
      strValueOut = _pFillSearchCriteria->isFMSearchCriteriaSponsor (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsFMSearchCriteriaFundBrokerCode)
   {
      strValueOut = _pFillSearchCriteria->isFMSearchCriteriaFundBrokerCode (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == IsFMSearchCriteriaFundBrokerName)
   {
      strValueOut = _pFillSearchCriteria->isFMSearchCriteriaFundBrokerName (idDataGroup) ? 
         I_("Y") : I_("N");
   }

	else if (idField == isFMSearchCriteriaAggregationTradeDate)
   {
      strValueOut = _pFillSearchCriteria->isFMSearchCriteriaAggregationTradeDate (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == isFMSearchCriteriaAggregationAggrOrdNo)
   {
      strValueOut = _pFillSearchCriteria->isFMSearchCriteriaAggregationAggrOrdNo (idDataGroup) ? 
         I_("Y") : I_("N");
   }
	else if (idField == isFMSearchCriteriaAggregationRoutRefNo)
   {
      strValueOut = _pFillSearchCriteria->isFMSearchCriteriaAggregationRoutRefNo (idDataGroup) ? 
         I_("Y") : I_("N");
   }
   else if (idField == isFMSearchCriteriaAggregationStatus)
   {
      strValueOut = _pFillSearchCriteria->isFMSearchCriteriaAggregationStatus (idDataGroup) ? 
         I_("Y") : I_("N");
   }
}

//******************************************************************************
SEVERITY FeaturesSearchProcess::performSearch (GenericInterface *rpGI, 
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
               thirdValue,
               fourthValue,
					fifthValue,
					sixthValue,
					seventhValue;

            const I_CHAR* launchProcessId = NULL;

            getField (this, idSearch, 
               ifds::SearchCriteria, searchCriteria, false);
            getField (this, idSearch, 
               ifds::SearchUsing, searchUsing, false);
            getField (this, idSearch, 
               ifds::SearchFieldCriteria1, firstValue, false);
            getField (this, idSearch, 
               ifds::SearchFieldCriteria2, secondValue, false);
            getField (this, idSearch, 
               ifds::SearchFieldCriteria3, thirdValue, false);
            getField (this, idSearch, 
               ifds::SearchFieldCriteria4, fourthValue, false);
				getField (this, idSearch, 
               ifds::SearchFieldCriteria5, fifthValue, false);
				getField (this, idSearch, 
               ifds::SearchFieldCriteria6, sixthValue, false);
				getField (this, idSearch, 
               ifds::SearchFieldCriteria7, seventhValue, false);
				
            if (_searchType == SEARCH_TYPE::BROKER_FEATURES)
            {
               //call the appropriate processes
               if (searchCriteria == BF_SEARCH_CRITERIA::BANKING)
               {
                  if (searchUsing == BF_SEARCH_BANKING_USING::BROKER)
                  {
                     setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::BROKER);
                     setParameter(MFCAN_IP_PARAM::BROKER_CODE, secondValue);
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
                     setParameter(MFCAN_IP_PARAM::BROKER_CODE, secondValue);
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
                     addIDITagValue(keyStringIDI, I_("BROKER"), secondValue);
                  }
                  else if (searchUsing == BF_SEARCH_HISTORICAL_INFO_USING::SLSREP)
                  {
                     tableId = AUDITTYPE::SLS;
                     addIDITagValue(keyStringIDI, I_("BROKER"), firstValue);
                     addIDITagValue(keyStringIDI, I_("BRANCH"), secondValue);
                     addIDITagValue(keyStringIDI, I_("SALESREP"), thirdValue);
                  }
                  if (tableId != NULL_STRING)
                  {
                     setParameter(MFCAN_IP_PARAM::TABLEID, tableId);
                     setParameter(MFCAN_IP_PARAM::KEYS, keyStringIDI);
                     setParameter(MFCAN_IP_PARAM::RECID, NULL_STRING);
                     setParameter(I_("TYPE"), I_("SINGLE"));
                     //no updates, call it modal
                     rtn = invokeCommand(this, CMD_BPROC_HISTORICAL_INFO, 
                        getProcessType(), true, NULL);
                  }
               }
               else if (searchCriteria == BF_SEARCH_CRITERIA::PAYMENT_INSTRUCTIONS)
               {
                  if (searchUsing == BF_SEARCH_PAYMENT_INSTRUCTIONS_USING::BROKER)
                  {
                     setParameter(MFCAN_IP_PARAM::BROKER_CODE, secondValue);
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
            }
            else if (_searchType == SEARCH_TYPE::FI_FEATURES)
            {
               if (searchCriteria == FI_SEARCH_CRITERIA::INSTITUTIONS)
               {
                  if (searchUsing == FI_SEARCH_INSTITUTIONS_USING::NAME)
                  {
                     setParameter (I_("FIName"), firstValue);
                  }
                  else if (searchUsing == FI_SEARCH_INSTITUTIONS_USING::CODE)
                  {
                     setParameter (I_("FICategory"), firstValue);
                     setParameter (I_("FIType"), secondValue);
                     setParameter (I_("FICode"), thirdValue);
                  }
                  launchProcessId = CMD_BPROC_FINANCIAL_INSTITUTION;
               }
               else if (searchCriteria == FI_SEARCH_CRITERIA::TRANSITS)
               {
                  if (searchUsing == FI_SEARCH_TRANSITS_USING::NAME)
                  {
                     setParameter (I_("FITName"), firstValue);
                     setParameter (MFCAN_IP_PARAM::CALLER, I_("TransitsMaint"));
                  }
                  launchProcessId = CMD_BPROC_TRANSITS;
               }
            }           
            else if (_searchType == SEARCH_TYPE::DAILY_TRANSACTIONS_FEES)
            {
					// This is Search for Anti Dilution Levy and Class effective hurdle rate
               if ( DTF_SEARCH_CRITERIA::DAILY_TRANSACTIONS_FEES == searchCriteria || 
                    DTF_SEARCH_CRITERIA::CLASS_EFF_HURDLE_RATE == searchCriteria )
               {
                  setParameter (I_("RecordType"), firstValue);
                  DString dstrFeecode = NULL_STRING;
                  if( DTF_SEARCH_CRITERIA::DAILY_TRANSACTIONS_FEES == searchCriteria)
                      dstrFeecode =  DAILY_TRANSACTIONS_FEES_CODE::DAILY_TRANSACTIONS_FEES; // Anti Dilution Levy Fee
                  else if ( DTF_SEARCH_CRITERIA::CLASS_EFF_HURDLE_RATE == searchCriteria )
                       dstrFeecode =  DAILY_TRANSACTIONS_FEES_CODE::CLASS_EFF_HURDLE_RATE;
                  setParameter (I_("FeeCode"),    dstrFeecode );  
                  if (searchUsing == DTF_DAILY_TRANSACTIONS_FEES_USING::FUND_CLASS)
                  {
                     setParameter (I_("FundCode"), secondValue);
                     setParameter (I_("ClassCode"), thirdValue);
                  }
                  else if (searchUsing == DTF_DAILY_TRANSACTIONS_FEES_USING::EFFECTIVE_DATE)
                  {
                     setParameter (I_("EffectiveDate"), secondValue);
                  }
                  launchProcessId = CMD_BPROC_DAILY_TRANSACTION_FEES;
               }
            }
            else if (_searchType == SEARCH_TYPE::FUNSSPONSORFEEMODEL)
            {
               if(searchCriteria == FEEMODEL_SEARCH_CRITERIA::FUNDSPONSORMODEL)
	            {
                  setParameter( FUNDSPONSORFEEMODEL::FROM_SCR, FUNDSPONSORFEEMODEL::SYSTEM );
                  if (searchUsing == FEEMODEL_USING::FEEMODELCODE )
                  {
                     setParameter(FUNDSPONSORFEEMODEL::FEE_MODEL_CODE, secondValue);
                     setParameter(FUNDSPONSORFEEMODEL::SEARCHTYPE, FUNDSPONSORFEEMODEL::FEE_MODEL_CODE);                  
                  }
                  else if (searchUsing == FEEMODEL_USING::FUNDSPONSORCODE )
                  {
                     setParameter(FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE, firstValue);
                     setParameter(FUNDSPONSORFEEMODEL::SEARCHTYPE, FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE);                  
                  }
                  else
                  {
                     setParameter(FUNDSPONSORFEEMODEL::SEARCHTYPE, FUNDSPONSORFEEMODEL::ALL);
                  }
               }         
               
               launchProcessId = CMD_BPROC_FUNDSPONSOR_FEE_MODEL;
            }
            else if (_searchType == SEARCH_TYPE::FUNDBROKER)
            {
               if(searchCriteria == FUNDBROKER_SEARCH_CRITERIA::FUNDBROKER)
	            {
                  setParameter( FUNDBROKER::FROM_SCR, FUNDBROKER::SYSTEM );
                  if (searchUsing == FUNDBROKER_USING::FUNDBROKERCODE )
                  {
                     setParameter(FUNDBROKER::FUNDBROKER_CODE, secondValue);
                     setParameter(FUNDBROKER::SEARCHTYPE, FUNDBROKER::FUNDBROKER_CODE);                  
                  }
                  else if (searchUsing == FUNDBROKER_USING::FUNDBROKERNAME )
                  {
                     setParameter(FUNDBROKER::FUNDBROKER_NAME, secondValue);
                     setParameter(FUNDBROKER::SEARCHTYPE, FUNDBROKER::FUNDBROKER_NAME);                  
                  }
                  else
                  {
                     setParameter(FUNDBROKER::SEARCHTYPE, FUNDSPONSORFEEMODEL::ALL);
                  }
               }         
               
               launchProcessId = CMD_BPROC_FUND_BROKER;
            }

			else if (_searchType == SEARCH_TYPE::AGGREGATEDORDER)
            {
               if(searchCriteria == AGGREGATION_SEARCH_CRITERIA::AGGREGATION)
	            {
                  if (searchUsing == AGGREGATION_USING::TRADEDATE )
                  {
                     setParameter(AGGREGATE::FROM_DATE, firstValue);
							setParameter(AGGREGATE::TO_DATE,   secondValue);
							setParameter(AGGREGATE::STATUS, thirdValue);
							setParameter(AGGREGATE::FUND_BROKER_CODE, fourthValue);
							setParameter(AGGREGATE::FUND_CODE, fifthValue);
							setParameter(AGGREGATE::WKN, sixthValue);
							setParameter(AGGREGATE::ISIN, seventhValue);
                     setParameter(AGGREGATE::SEARCH_TYPE, AGGREGATE_SEARCHTYPE::BY_TRADE_DATE);                  
                  }
                  else if (searchUsing == AGGREGATION_USING::AGGRORDERNO )
                  {
                     setParameter(AGGREGATE::AGGR_ORDER_NUMBER, secondValue);
                     setParameter(AGGREGATE::SEARCH_TYPE, AGGREGATE_SEARCHTYPE::BY_AGGR_ORD_NUM);                  
                  }
				  else if (searchUsing == AGGREGATION_USING::ROUTINGREFNO )
                  {
                     setParameter(AGGREGATE::ROUTING_REF_NUMBER, secondValue);
                     setParameter(AGGREGATE::SEARCH_TYPE, AGGREGATE_SEARCHTYPE::BY_ROUT_REF_NUM);                  
                  }
				  else if (searchUsing == AGGREGATION_USING::STATUS )
                  {
                     setParameter(AGGREGATE::STATUS, firstValue);
							setParameter(AGGREGATE::FUND_BROKER_CODE, thirdValue);
                     setParameter(AGGREGATE::SEARCH_TYPE, AGGREGATE_SEARCHTYPE::BY_ORDER_STATUS);                  
                  }
               }         
               
               launchProcessId = CMD_BPROC_AGGREGATED_ORDER;
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeaturesSearchProcess.cpp-arc  $
// 
//    Rev 1.11   Dec 10 2004 13:55:10   Fengyong
// change fee model code selection from first value to the second value.
// 
//    Rev 1.10   Dec 09 2004 14:37:58   hernando
// PET910 - Corrected Broker only searches.  Corrected Historical Info look up.
// 
//    Rev 1.9   Nov 26 2004 19:09:20   Fengyong
// change fund broker code select from combo to edit box
// 
//    Rev 1.8   Nov 26 2004 14:43:22   zhangcel
// PET1117/FN8 -- Aggregated Order related changes
// 
//    Rev 1.7   Nov 05 2004 15:41:54   ZHANGCEL
// PET1117/08 Add sreaching logic for AggregatedOrder
// 
//    Rev 1.6   Oct 19 2004 14:37:48   FENGYONG
// PET1117 FN54 - Fund Broker Static
// 
//    Rev 1.5   Aug 10 2004 11:10:30   FENGYONG
// PET117 FN5 - Client Condition Fee
// 
//    Rev 1.4   Feb 10 2004 16:18:28   VADEANUM
// PET 859 FN23 - ADL - pass ADL Fee code.
// 
//    Rev 1.3   Feb 03 2004 16:26:38   VADEANUM
// PET 859 FN23 - ADL - removed Fee search param
// 
//    Rev 1.2   Jan 28 2004 21:34:58   popescu
// PET 859, FN 23, modified resources (dialogs and menu item) and coded for the features search dialog
// 
//    Rev 1.1   Oct 27 2003 19:48:18   popescu
// CIBC PET809, FN 13, added Transit Search by name
// 
//    Rev 1.0   Oct 04 2003 16:05:58   popescu
// Initial revision.
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
