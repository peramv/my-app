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
// ^FILE   : PayToEntityProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : PayToEntityProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "PayToEntityProcess.hpp"
#include "PayToEntityProcessIncludes.h"
#include <ifastcbo\broker.hpp>
#include <ifastcbo\distributorrepository.hpp>
#include <ifastcbo\paytoentitylist.hpp>
#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PAY_TO_ENTITY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PAY_TO_ENTITY;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< PayToEntityProcess > processCreator(CMD_BPROC_PAY_TO_ENTITY);

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("PayToEntityProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const PYEN;
}

namespace ifds
{
   //field ids used   
 	extern CLASS_IMPORT const BFTextFieldId ClientName;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

PayToEntityProcess::PayToEntityProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),
 _rpChildGI(NULL),
 _dstrBrokerCode(NULL_STRING),
 _dstrSearchTypeMgmt(NULL_STRING),
 _pPayToEntityList(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   addContainer(IFASTBP_PROC::PAY_TO_ENTITY_LIST, true, BF::NullContainerId, true,
      I_("PayToEntityList"));
   addFieldDetails(ifds::BrokerCode, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::BrokerName, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::PaymentFor, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::PayToEntity, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::ProcessDate, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::Username, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::ModDate, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::ModUser, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::PayEntityId, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::CompanyCode, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::PayInstructExists, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(HasItemsByBrokerCode, IFASTBP_PROC::PAY_TO_ENTITY_LIST, SUBCLASS_PROCESS);
   addFieldDetails(BrokerActive, IFASTBP_PROC::PAY_TO_ENTITY_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::ClientName, IFASTBP_PROC::PAY_TO_ENTITY_LIST, SUBCLASS_PROCESS );
	addFieldDetails(ifds::EffectiveDate, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
   addFieldDetails(ifds::StopDate, IFASTBP_PROC::PAY_TO_ENTITY_LIST);
}

//******************************************************************************
PayToEntityProcess::~PayToEntityProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;
}

//************************************************************************************
SEVERITY PayToEntityProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      processParameters();
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
E_COMMANDRETURN PayToEntityProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      //pass to the dialog the broker code that called this process,
      //so the dialog list can filter it
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
		setParameter(MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, _dstrSearchTypeMgmt);
      rtn = invokeCommand(this, CMD_GUI_PAY_TO_ENTITY, 
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
void PayToEntityProcess::doGetField(const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, DString &strValueOut,
   bool bFormatted) const
{
   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   strValueOut = NULL_STRING;
   if (idField == HasItemsByBrokerCode)
   {
      BFData matchCriteria;

      matchCriteria.setElementValue(ifds::BrokerCode, _dstrBrokerCode, true);
      BFObjIter iter(*_pPayToEntityList, idDataGroup, 0, 
         BFObjIter::ITERTYPE::NON_DELETED);

      iter.positionOnNextMatch(matchCriteria, idDataGroup);
      strValueOut = iter.end() ? I_("N") : I_("Y");
   }
   else if (idField == BrokerActive)
   {
      Broker broker (*pDSTCWorkSession);
      DString brokerCode;

      const_cast <PayToEntityProcess*> (this)->
         getField (this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, 
         ifds::BrokerCode, brokerCode, false);
      bool bBrokerActive = brokerCode != NULL_STRING;

      if (bBrokerActive && broker.init (brokerCode, true) <= WARNING)
      {
         DString currBusDate;
         
         //check the effectiveness of the broker
         pDSTCWorkSession->getOption (
            ifds::CurrBusDate, currBusDate, idDataGroup, false);         
         bBrokerActive = 
            broker.checkEffective (currBusDate, idDataGroup) <= WARNING;
      }
      else if (bBrokerActive)
      {
         bBrokerActive = false;
      }
				
      strValueOut = bBrokerActive ? I_("Y") : I_("N");
   }
	else if ( idField == ifds::ClientName )
	{
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::ClientName, strValueOut, idDataGroup );
	}
}

//******************************************************************************
SEVERITY PayToEntityProcess::doValidateAll(BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   if (_pPayToEntityList)
   {
      _pPayToEntityList->validateAll(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PayToEntityProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      if (processParameters() <= WARNING)
      {
         if (isValidModelessInterface(_rpChildGI))
         {  // Only if child still exists
            setContainer(IFASTBP_PROC::PAY_TO_ENTITY_LIST, NULL);
            setParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
				setParameter(MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, _dstrSearchTypeMgmt);

            bRtn = _rpChildGI->refresh(this, I_("ReloadParams"));
            bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
         }
      }
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return bRtn;
}

//******************************************************************************
bool PayToEntityProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_PAY_TO_ENTITY;
}

//******************************************************************************
SEVERITY PayToEntityProcess::performSearch(GenericInterface *rpGI, 
   const BFContainerId &idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));

   try
   {
      if (_pPayToEntityList != NULL)
      {
         _pPayToEntityList->getMore();
      }
   }
   catch(ConditionException &ce)
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
bool PayToEntityProcess::doMoreRecordsExist(GenericInterface *rpGICaller,
   const BFContainerId &idSearch)
{
   return (rpGICaller == NULL || _pPayToEntityList == NULL) ? false : 
      _pPayToEntityList->doMoreRecordsExist();
}

//******************************************************************************
void *PayToEntityProcess::getPtrForContainer(const BFContainerId& idContainer,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   void *ptr = NULL;
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::PAY_TO_ENTITY_LIST == idContainer)
      {
         DistributorRepository *pDistributorRepository = NULL;

         if (pDSTCWorkSession->getDistributorRepository(
            pDistributorRepository) <= WARNING && pDistributorRepository)
         {
            if (pDistributorRepository->getPayToEntityList(_dstrBrokerCode, _dstrSearchTypeMgmt,
               _pPayToEntityList, getDataGroupId()) <= WARNING)
            {
               ptr = _pPayToEntityList;
            }
         }
      }
   }
   catch (ConditionException &)
   {
      throw;
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;
}

//******************************************************************************
SEVERITY PayToEntityProcess::getHistoricalParameters(
   const BFContainerId& idContainer, BFFieldId &recordIdField, DString& tableId, DString& dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   
   if (idContainer == IFASTBP_PROC::PAY_TO_ENTITY_LIST)
   {
      DString keyStringIDI, dstrPayEntityId, dstrBrokerCode;
      recordIdField = ifds::NullFieldId;
      tableId = AUDITTYPE::PYEN;
      getField(this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, ifds::PayEntityId, dstrPayEntityId, false);
      getField(this, IFASTBP_PROC::PAY_TO_ENTITY_LIST, ifds::BrokerCode, dstrBrokerCode, false );
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode);
      addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::PAYENTITY_ID, dstrPayEntityId);
      dstrKeys = keyStringIDI;
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PayToEntityProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   _dstrBrokerCode = NULL_STRING;
   getParameter(MFCAN_IP_PARAM::BROKER_CODE, _dstrBrokerCode);
   _dstrBrokerCode.stripAll().upperCase();
	_dstrSearchTypeMgmt = NULL_STRING;
   getParameter(MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, _dstrSearchTypeMgmt);
   _dstrSearchTypeMgmt.stripAll().upperCase();
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY PayToEntityProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PayToEntityProcess.cpp-arc  $
// 
//    Rev 1.12   Aug 28 2006 15:38:38   ZHANGCEL
// PET2212 FN10 -- Added new fields for Netting Bulking Redemption and Distribution Payment
// 
//    Rev 1.11   Jul 31 2006 11:05:28   porteanm
// Incident 640733 - syncup - Disable the Delete button in Pay to Entity when PayInstructions already exist for PayEntity. Added PayInstructExists to view 258.
// 
//    Rev 1.10   Jul 27 2006 17:57:58   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.9   Mar 10 2004 13:18:32   HERNANDO
// PET965 FN11 - Added getHistoricalParameters.
// 
//    Rev 1.8   Mar 04 2004 17:48:42   popescu
// PTS 10027865, fixed crash in Pay to entity search for inactive brokers. Disabled 'Instructions' button in pay to entity dialog if broker is inactive/not effective
// 
//    Rev 1.7   Aug 20 2003 15:45:58   HERNANDO
// Use BrokerCode and PayEntityId as keys for getHistoricalParameters.
// 
//    Rev 1.6   Aug 19 2003 16:17:12   HERNANDO
// Added keys to getHistoricalParameters.
// 
//    Rev 1.5   Jul 31 2003 21:59:02   popescu
// Added support for PayType 'X' and support for Historical Info at the process level
// 
//    Rev 1.4   Jul 26 2003 19:39:02   popescu
// the refresh of the banking list didn't work properly in some cases, 
// 
//    Rev 1.3   Jul 23 2003 18:20:38   popescu
// Capitalized the parameters
// 
//    Rev 1.2   Jul 09 2003 21:56:44   popescu
// Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
// 
//    Rev 1.1   Jul 01 2003 18:08:04   popescu
// Clean-up the code, new business rules, set the broker name to the dialog caption, etc...
// 
//    Rev 1.0   Jun 27 2003 18:15:20   popescu
// Initial revision.
// 
 *
 */
