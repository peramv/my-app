//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : EntitySearchProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 23/06/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : EntitySearchProcess
//    This class does the cleanup of the singletons
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "entitysearchprocess.hpp"
#include <ifastcbo\accountentityxref.hpp>
#include "accdetailsprocessincludes.h"
#include <ifastcbo\entitysearchlist.hpp>
#include "entitysearchprocessincludes.h"
#include <ifastcbo\entity.hpp>
#include <ifastcbo\entityidslist.hpp>
#include "fillsearchcriteriaprocessincludes.h"
#include "tradesprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ENTITY_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACC_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY_SEARCH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< EntitySearchProcess > processCreator (CMD_BPROC_ENTITY_SEARCH);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_ ("EntitySearchProcess");
   const I_CHAR * const PERFORMSEARCH = I_ ("performSearch");
   const I_CHAR * Y = I_ ("Y");
   const I_CHAR * T = I_("T");
   const I_CHAR * N = I_ ("N");
}

namespace CND
{
   extern const long BP_NO_ACCESS_TO_ACCTDETAILS;
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long BP_WRN_MORE_THAN_ONE_RECORD_FOUND;
}

//user access function codes
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_DETAIL;
   extern CLASS_IMPORT I_CHAR * const ENTITY_MAINTANENCE;
}

namespace ENTSRCHLIT //entity search literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const SEARCH_CODE = I_ ("EntitySearchCode");
   extern IFASTBP_LINKAGE const I_CHAR * const FIRST_VALUE = I_ ("FirstValue");
   extern IFASTBP_LINKAGE const I_CHAR * const SECOND_VALUE = I_ ("SecondValue");
   //by default it will be an account search;
   //this parameter should be set to Y if we are looking at a entity search
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_SEARCH = I_ ("N");

   extern IFASTBP_LINKAGE const I_CHAR * const TRADE_SEARCH = I_ ("SearchTrade");

   //this parameter should be set to Y if we are doing an entity search during adding a new entity to the system
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_BACKGROUND_SEARCH = I_ ("BackgroundSearch");
   extern IFASTBP_LINKAGE const I_CHAR * const ALLENTITY = I_ ("AllEntity");
   extern IFASTBP_LINKAGE const I_CHAR * const WHERE_USED_CODE = I_ ("WhereUsedCode");
   extern IFASTBP_LINKAGE const I_CHAR * const EXACTSEARCH = I_ ("ExactSearch");
   extern IFASTBP_LINKAGE const I_CHAR * const NO_VERIFYSEARCH_IF_ONE_MATCH = I_ ("NoVerifySearchIfOneMatch");
   const I_CHAR * const FROM_SCR  = I_ ("FromScreen");
}

typedef struct entity_search_codes
{
   const I_CHAR* es_using_code;
   int es_cbo_type;
} ENTITY_SEARCH_CODES;

static const ENTITY_SEARCH_CODES _entitySearchCodes[] = 
{
   //account search
   SEARCHACCOUNTUSING::ACCOUNT_NUMBER, ENTITYSEARCHTYPE::USING_ACCOUNT_NUM,
   SEARCHACCOUNTUSING::NAME, ENTITYSEARCHTYPE::USING_NAME,
   SEARCHACCOUNTUSING::TELEPHONE, ENTITYSEARCHTYPE::USING_TELEPHONE_NUM,
   SEARCHACCOUNTUSING::SOCIAL_INSURANCE_NUMBER, ENTITYSEARCHTYPE::USING_SIN,
   SEARCHACCOUNTUSING::CREDIT_CARD, ENTITYSEARCHTYPE::USING_CREDIT_CARD,
   SEARCHACCOUNTUSING::DRIVER_LICENSE, ENTITYSEARCHTYPE::USING_DRIVER_LICENSE,
   SEARCHACCOUNTUSING::PASSPORT, ENTITYSEARCHTYPE::USING_PASSPORT,
   SEARCHACCOUNTUSING::BIRTH_CERTIFICATE, ENTITYSEARCHTYPE::USING_BIRTH_CERTIFICATE,
   SEARCHACCOUNTUSING::NATIONAL_ID, ENTITYSEARCHTYPE::USING_NATIONAL_ID,
   SEARCHACCOUNTUSING::SOCIAL_SECURITY_INSURANCE_CARD, ENTITYSEARCHTYPE::USING_SOCIAL_SEC_INS_CARD,
   SEARCHACCOUNTUSING::SHAREHOLDER_NUMBER, ENTITYSEARCHTYPE::USING_SHAREHOLDER_NUM,
   SEARCHACCOUNTUSING::ALT_ACCOUNT_AND_BROKER_CODE, ENTITYSEARCHTYPE::USING_ALT_ACCT_BRK_CODE,
   SEARCHACCOUNTUSING::BROKER_CODE, ENTITYSEARCHTYPE::USING_BRK_CODE,
   SEARCHACCOUNTUSING::ID_OTHER, ENTITYSEARCHTYPE::USING_OTHER_ID,
   SEARCHACCOUNTUSING::BIRTH_NAME, ENTITYSEARCHTYPE::USING_BIRTH_NAME,
   SEARCHACCOUNTUSING::INTERMEDIARY_CODE, ENTITYSEARCHTYPE::USING_INTERMEDIARY,
   SEARCHACCOUNTUSING::OTHER_REFERENCE_NUMBER, ENTITYSEARCHTYPE::USING_OTHER_REFERENCE,
   SEARCHACCOUNTUSING::BUSINESSNO, ENTITYSEARCHTYPE::USING_BUSINESSNO,
   SEARCHACCOUNTUSING::CIF, ENTITYSEARCHTYPE::USING_CIF, 
   SEARCHACCOUNTUSING::ACCESS_ID, ENTITYSEARCHTYPE::USING_ACCESS_ID, 
   //MT535/MT536
   SEARCHACCOUNTUSING::CLEARING_ID, ENTITYSEARCHTYPE::USING_CLEARING_PLATFORM_ID, 
   SEARCHACCOUNTUSING::HOUSEHOLD, ENTITYSEARCHTYPE::USING_HOUSEHOLD, 
   SEARCHACCOUNTUSING::REGISTRATION_AGENT, ENTITYSEARCHTYPE::USING_REGISTRATION_AGENT, 
   SEARCHACCOUNTUSING::CPFB_NUMBER, ENTITYSEARCHTYPE::USING_CPFB_ACCNUM, 

   // trade search
   SEARCHTRADEUSING::ACCOUNT_NUMBER, ENTITYSEARCHTYPE::USING_ACCOUNT_NUM,
   SEARCHTRADEUSING::SHAREHOLDER_NUMBER, ENTITYSEARCHTYPE::USING_SHAREHOLDER_NUM,
   SEARCHTRADEUSING::ACOUNT_BROKER, ENTITYSEARCHTYPE::USING_ALT_ACCT_BRK_CODE,

   //entity search
   SEARCHENTITYUSING::ACCOUNT_NUMBER, ENTITYSEARCHTYPE::USING_ACCOUNT_NUM,
   SEARCHENTITYUSING::NAME, ENTITYSEARCHTYPE::USING_NAME,
   SEARCHENTITYUSING::BIRTH_CERTIFICATE, ENTITYSEARCHTYPE::USING_BIRTH_CERTIFICATE,
   SEARCHENTITYUSING::CREDIT_CARD, ENTITYSEARCHTYPE::USING_CREDIT_CARD,
   SEARCHENTITYUSING::DRIVER_LICENSE, ENTITYSEARCHTYPE::USING_DRIVER_LICENSE,
   SEARCHENTITYUSING::NATIONAL_ID, ENTITYSEARCHTYPE::USING_NATIONAL_ID,
   SEARCHENTITYUSING::PASSPORT, ENTITYSEARCHTYPE::USING_PASSPORT,
   SEARCHENTITYUSING::SOCIAL_INSURANCE_NUMBER, ENTITYSEARCHTYPE::USING_SIN,
   SEARCHENTITYUSING::SOCIAL_SECURITY_INSURANCE_CARD, ENTITYSEARCHTYPE::USING_SOCIAL_SEC_INS_CARD, 
   SEARCHENTITYUSING::CPFB_ACCT_NUM, ENTITYSEARCHTYPE::USING_CPFB_ACCNUM,
   SEARCHENTITYUSING::ACCOUNT_MANAGER_UNIQUE_ID, ENTITYSEARCHTYPE::USING_ACCOUNT_MANAGER_UNIQUE_ID,
   '\0', ENTITYSEARCHTYPE::NO_SEARCH,
};

//******************************************************************************
const int EntitySearchProcess::getEntitySearchCboType (const DString& usingCode)
{
   int cboType = ENTITYSEARCHTYPE::NO_SEARCH;

   for (int ndx = 0; _entitySearchCodes[ ndx ].es_cbo_type != ENTITYSEARCHTYPE::NO_SEARCH; ndx++)
   {
      if (_entitySearchCodes[ ndx ].es_using_code == usingCode)
      {
         cboType = _entitySearchCodes[ ndx ].es_cbo_type;
         break;
      }
   }
   return(cboType);
}

//******************************************************************************
//              Public Methods
//******************************************************************************

EntitySearchProcess::EntitySearchProcess  (GenericInterfaceContainer *pGIC, 
                                           GenericInterface *pGIParent, 
                                           const Command &rCommand)
: AbstractProcess (pGIC, pGIParent, rCommand)
, _pEntitySearchList (NULL)
, _entityID (NULL_STRING)
, _acctExsistencySearch(NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

   addContainer (IFASTBP_PROC::ENTITY_SEARCH_LIST, true, BF::NullContainerId);
   //although the entity ids list is not updatable we need to
   //add a row if there are no ids for an entity
   addContainer (IFASTBP_PROC::ENTITY_IDS_LIST, true, IFASTBP_PROC::ENTITY_SEARCH_LIST, true);

   addFieldDetails (ifds::AccountNum, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::LastName, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::FirstName, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::SIN, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::BirthDate, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::TaxType, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::TaxTypeDesc, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::HomePhone, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::EntityId, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::EntityType, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Address1, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Address2, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Address3, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Address4, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Address5, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::PostalCode, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::BirthLastName, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::BirthFirstName, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::MultipleReln, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Addr11Line1, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Addr11Line2, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Addr11Line3, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Addr11Line4, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::Addr11Line5, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::PostalCode11, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::AcctGroup, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::CompanyCode, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::RegistrationInfo, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::ValidRATaxType, IFASTBP_PROC::ENTITY_SEARCH_LIST);
   addFieldDetails (ifds::WrapAccount, IFASTBP_PROC::ENTITY_SEARCH_LIST, SUBCLASS_PROCESS);
//entity ids
   addFieldDetails (ifds::IdType, IFASTBP_PROC::ENTITY_IDS_LIST);
   addFieldDetails (ifds::IdValue, IFASTBP_PROC::ENTITY_IDS_LIST);
   addFieldDetails (ifds::IdDate, IFASTBP_PROC::ENTITY_IDS_LIST);
   addFieldDetails (ifds::IdTypeDesc, IFASTBP_PROC::ENTITY_IDS_LIST);
   addFieldDetails (ifds::IdStatus, IFASTBP_PROC::ENTITY_IDS_LIST);
   addFieldDetails( ifds::CountryOfIssue, IFASTBP_PROC::ENTITY_IDS_LIST);
   addFieldDetails( ifds::IdExpireDate, IFASTBP_PROC::ENTITY_IDS_LIST);
}

//******************************************************************************
EntitySearchProcess::~EntitySearchProcess()
{
   TRACE_DESTRUCTOR (CLASSNAME);

   if (_pEntitySearchList != NULL)
   {
      delete _pEntitySearchList;
      _pEntitySearchList = NULL;
   }
}

//******************************************************************************
SEVERITY EntitySearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      _pEntitySearchList = new EntitySearchList (*getBFWorkSession());

      DString firstValue, secondValue;
      bool searchForAllEntities;

      getParameter (ENTSRCHLIT::SEARCH_CODE, _searchCode);
      getParameter (ENTSRCHLIT::FIRST_VALUE, _firstValue);
      getParameter (ENTSRCHLIT::SECOND_VALUE, _secondValue);
      getParameter (ENTSRCHLIT::ENTITY_SEARCH, _entitySearch);
      getParameter (ENTSRCHLIT::TRADE_SEARCH, _tradeSearch);
      getParameter (ENTSRCHLIT::ALLENTITY, _allEntity);
      getParameter (ENTSRCHLIT::EXACTSEARCH, _exactSearch);
      getParameter (ENTSRCHLIT::FROM_SCR, _fromScreen);
      getParameter (I_("AcctExsistencySearch"),_acctExsistencySearch);
      Entity::bUsedByEntityAlone = _fromScreen == I_("EntityAlone") ? true: false;
      getParameter (ENTSRCHLIT::ENTITY_BACKGROUND_SEARCH, _entityBackgroundSearch);
      getParameter (ENTSRCHLIT::NO_VERIFYSEARCH_IF_ONE_MATCH, _noVerifySearchIfOneMatch);
      getParameter (I_("ShowSameEntityMultipleTimes"), _showSameEntityMultipleTimes);
      searchForAllEntities = _entityBackgroundSearch == Y || _entitySearch == Y;

      DString whereUsedCode;
      getParameter (ENTSRCHLIT::WHERE_USED_CODE, whereUsedCode);

      if (_exactSearch != Y) 
      {
         _exactSearch = N;
      }
      if (_allEntity != Y) 
      {
         _allEntity = N;
      }
      if (_noVerifySearchIfOneMatch != Y)
      {
         _noVerifySearchIfOneMatch = N;
      }
      //get first 25 records
      sevRtn = _pEntitySearchList->init  (getEntitySearchCboType (_searchCode), 
                                          _firstValue, 
                                          _secondValue, 
                                          searchForAllEntities, 
                                          _exactSearch, 
                                          _allEntity,
                                          whereUsedCode);

      if (sevRtn <= WARNING)
      {
         setContainer (IFASTBP_PROC::ENTITY_SEARCH_LIST, _pEntitySearchList);
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(sevRtn);
}


//******************************************************************************
bool EntitySearchProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOOK);

   getParameter (MFCAN_IP_PARAM::ENTITY_ID, _entityID);
   getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);

   return true;
}

//****************************************************************************
void EntitySearchProcess::doGetField (const GenericInterface *rpGICaller,
                                      const BFContainerId &idContainer, 
                                      const BFFieldId &idField, 
                                      const BFDataGroupId &idDataGroup, 
                                      DString &strValueOut, 
                                      bool bFormatted) const
{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField"));
   strValueOut = NULL_STRING;

   if (_pEntitySearchList)
   {
      if (idField == ifds::WrapAccount)
      {
         DString dstrEntityId;
         const_cast< EntitySearchProcess * >(this)->
               getField(rpGICaller, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::EntityId, dstrEntityId);  

         BFObjIter iter(*_pEntitySearchList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

         for (iter.begin(); !iter.end(); ++iter)
         {
            DString dstrWrap, 
               dstrIterEntityId;

            iter.getObject()->getField (ifds::EntityId, dstrIterEntityId, idDataGroup);

            if (dstrEntityId == dstrIterEntityId)
            {
               iter.getObject()->getField (ifds::WrapAccount, dstrWrap, idDataGroup, false);
               iter.getObject()->getField (ifds::WrapAccount, strValueOut, idDataGroup, true);
               if (dstrWrap == I_("Y"))
               {
                  //since the requirement is to show Y if one account is Wrap, then break here
                  break;
               }
            }
         }
      }
   }
}

//******************************************************************************
E_COMMANDRETURN EntitySearchProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(ENTSRCHLIT::FROM_SCR, _fromScreen);
      int noOfEntities = getNumberOfItemsInList (this, IFASTBP_PROC::ENTITY_SEARCH_LIST);

      if  (noOfEntities > 1 || noOfEntities == 1  && _fromScreen == I_("EntityAlone") ||
          (_entityBackgroundSearch == Y && noOfEntities == 1 && _noVerifySearchIfOneMatch == N))
      {
        if (!isXMLAPIContext())
        {
         setParameter (I_("ShowSameEntityMultipleTimes"), _showSameEntityMultipleTimes);
         //invoke the verify search dialog
         rtn = invokeCommand (this, CMD_GUI_ENTITY_SEARCH, getProcessType(), true, NULL);
        }
        else if (noOfEntities > 1)
        {
            getFirstListItemKey (this, IFASTBP_PROC::ENTITY_SEARCH_LIST);        
            getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::AccountNum, _accountNum);         
            setParameter (ACCDETLIT::ACCOUNT_NUMBER_FIELD, _accountNum);

            DString errorMesssage;            
            addIDITagValue(errorMesssage, I_("AccountNum"), _accountNum);
            ADDCONDITIONFROMFILEIDI(CND::BP_WRN_MORE_THAN_ONE_RECORD_FOUND, errorMesssage.c_str());
            rtn = CMD_OK;
        }
      }
      else if (noOfEntities == 1)
      {
         getFirstListItemKey (this, IFASTBP_PROC::ENTITY_SEARCH_LIST);
         getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::EntityId, _entityID);
         getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::AccountNum, _accountNum);        
         setParameter (ACCDETLIT::ENTITY_ID_FIELD, _entityID);
         setParameter (ACCDETLIT::ACCOUNT_NUMBER_FIELD, _accountNum);
         rtn = CMD_OK;
      }
      //set the accountNum as well
      if (_tradeSearch != Y && _entitySearch != Y && rtn == CMD_OK && 
          getEntitySearchCboType (_searchCode) == ENTITYSEARCHTYPE::USING_ACCOUNT_NUM)
      {
         DString accountNbr;

         getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::AccountNum, accountNbr);
         setParameter (ACCDETLIT::ACCOUNT_NUMBER_FIELD, accountNbr);
      }
      //If the search for the AltAccountNum and BrokerCode, pass the value to the AccountDetail screen
      if (_tradeSearch != Y && _entitySearch != Y && rtn == CMD_OK && 
          getEntitySearchCboType (_searchCode) == ENTITYSEARCHTYPE::USING_ALT_ACCT_BRK_CODE)
      {
         setParameter (ACCDETLIT::ALT_ACCOUNT_NUM_FIELD, _firstValue);
         setParameter (ACCDETLIT::BROKER_CODE_FIELD, _secondValue);
      }
      if (rtn == CMD_OK)
      {
         DString home_phone;

         getField (this, IFASTBP_PROC::ENTITY_SEARCH_LIST, ifds::HomePhone, home_phone);
         setParameter (ACCDETLIT::PHONE_NUM_FIELD, home_phone.strip());
         setParameter (ENTSRCHLIT::SEARCH_CODE, _searchCode);
         //invoking either the account details or entity details business process
         //check first if the user has access
         if (_entitySearch != Y && _tradeSearch != Y) //accdetails search
         {
            if (hasReadPermission (UAF::ACCOUNT_DETAIL))
            {
               if (_entityBackgroundSearch == Y)
               {
                  DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
                  Entity *pEntity;
                  SEVERITY severity = dstcWorkSession->getEntity (BF::HOST, _entityID, pEntity);
                  if (severity <= WARNING)
                     setParameter (I_ ("EntityId"), _entityID);
                  else
                     rtn = CMD_FAILURE;
               }
               else if (_acctExsistencySearch == Y)
               {
                  setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
                  rtn = CMD_OK;
               }
               else
               {
                  //set the worksession process as a parent for AccDetails
                  setParameter (ACCDETLIT::ENTITY_ID_FIELD, _entityID);
                  if (!isXMLAPIContext())
                  {
                     rtn = invokeCommand (getParent(), CMD_BPROC_ACC_DETAILS, PROC_NO_TYPE, false, NULL);
                  }
               }
            }
            else
            {
               ADDCONDITIONFROMFILE (CND::BP_NO_ACCESS_TO_ACCTDETAILS);
               rtn = CMD_FAILURE;
            }
         }
         else if (_tradeSearch == Y) // trade seach
         {
            setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
            if (!isXMLAPIContext())
            {
               rtn = invokeCommand (getParent(), CMD_BPROC_TRADES, PROC_NO_TYPE, false, NULL);      
            }
         }
         else if (_entitySearch == Y)//entity search
         {
            if (hasReadPermission (UAF::ENTITY_MAINTANENCE))
            {
               //fixme,add the I_ ("EntityId") in a namespace that belongs to the entity
               setParameter (I_ ("EntityId"), _entityID);

               if (_entityBackgroundSearch == Y)
               {
                  DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
                  Entity *pEntity;
                  dstcWorkSession->getEntity (BF::HOST, _entityID, pEntity);
               }
               else
               {
                  setParameter (I_ ("AccountNum"), _accountNum);
                  if (!isXMLAPIContext())
                  {
                     //set the worksession process as a parent for Entity Process
                     rtn = invokeCommand (getParent(), CMD_BPROC_ENTITY, PROC_NO_TYPE, false, NULL);
                  }
               }
            }
            else
            {
               rtn = CMD_FAILURE;
            }
         }
      }
   }
   catch (ConditionException &ce)
   {
      assert (0);
      SETCONDITIONFROMEXCEPTION (ce);
      rtn = CMD_FAILURE;
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   //tell to the container to delete the search process
   if (rtn == CMD_MODELESS_INPROCESS)
   {
      rtn = CMD_OK;
   }
   return rtn;
}

//******************************************************************************
bool EntitySearchProcess::doMoreRecordsExist (GenericInterface *rpGICaller, 
                                              const BFContainerId& idSearch)
{
   return (_pEntitySearchList == NULL ? false : _pEntitySearchList->doMoreRecordsExist());
}

//******************************************************************************
SEVERITY EntitySearchProcess::performSearch (GenericInterface *rpGI, 
                                             const BFContainerId& idSearch, 
                                             E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH);
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if (_pEntitySearchList)
      {
         sevRtn = _pEntitySearchList->search();
         setContainer (IFASTBP_PROC::ENTITY_SEARCH_LIST, NULL);
         setContainer (IFASTBP_PROC::ENTITY_SEARCH_LIST, _pEntitySearchList);
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch  (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return sevRtn;
}

//******************************************************************************
bool EntitySearchProcess::doModelessChildComplete (const Command &cmd)
{
   return true;
}

//******************************************************************************
void* EntitySearchProcess::getPtrForContainer (const BFContainerId& idContainer, const BFDataGroupId& idDataGroup)
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::ENTITY_IDS_LIST == idContainer)
      {
         BFAbstractCBO *rpPtr = getCBOItem (IFASTBP_PROC::ENTITY_SEARCH_LIST, idDataGroup);

         if (rpPtr != NULL)
         {
            DString entityId;
            Entity* entity;

            rpPtr->getField (ifds::EntityId, entityId, idDataGroup);
            if (dstcWorkSession->getEntity (idDataGroup, entityId, entity) <= WARNING)
            {
               EntityIdsList* entityIds = NULL;

               if (entity->getEntityIdsList (entityIds, idDataGroup) <= WARNING)
               {
                  ptr = entityIds;
               }
            }
         }
      }
      else
      {
      }
   }
   catch (ConditionException &)
   {
      throw;
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(ptr);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntitySearchProcess.cpp-arc  $
 * 
 *    Rev 1.48   Jul 19 2012 12:06:16   dchatcha
 * P0179630 FN01 FATCA Project - Entity level.
 * 
 *    Rev 1.47   Apr 27 2012 16:34:48   if991250
 * CPF search for Reg agents
 * 
 *    Rev 1.46   Apr 27 2012 09:51:42   if991250
 * CPF - Account Setup & Settlement 
 * 
 *    Rev 1.45   Apr 16 2012 17:25:22   if991250
 * CPF Account Setup
 * 
 *    Rev 1.44   Apr 04 2012 20:26:36   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.43   Oct 27 2011 07:27:36   popescu
 * P0188902 - DYN Household Project - added new search criteria to look for accounts based on a household
 * 
 *    Rev 1.42   Dec 15 2008 02:23:24   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.41   22 Aug 2007 13:37:22   popescu
 * GAP 6 - search by CIF should return all the entities linked by CIF
 * 
 *    Rev 1.40   12 Jul 2007 18:41:06   popescu
 * GAP 6 - CIF - added two new search types on the main screen - by CIF and by AccessID
 * 
 *    Rev 1.39   06 Jul 2007 14:43:14   popescu
 * PET 2363 GAP 6 CIF
 * 
 *    Rev 1.38   27 Jun 2007 16:47:28   popescu
 * Incident# 929895 - enable search button and create a new entity if this is used.
 * 
 *    Rev 1.37   Apr 28 2005 15:21:08   Fengyong
 * #Incident299327 - Modify error 2114 to accept parameter
 * 
 *    Rev 1.36   Apr 14 2005 11:06:38   popescu
 * Incident #262507, Multiple a/c with same alternate a/c
 * 
 *    Rev 1.35   Mar 09 2005 16:07:52   yingbaol
 * PET1171,FN01:EU saving entity update
 * 
 *    Rev 1.34   Mar 09 2005 14:50:12   yingbaol
 * PEt 1171,FN01: EU Saving, fix exact match issue.
 * 
 *    Rev 1.33   Mar 09 2005 14:37:06   yingbaol
 * PET1171,FN01: EUSD entity search support
 * 
 *    Rev 1.32   Feb 10 2005 07:55:24   purdyech
 * PET910 - Fixed incorrect linkage for project-local Conditions.
 * 
 *    Rev 1.31   Feb 03 2005 13:30:16   Fengyong
 * PET1117 FN66 - Trade reconcile API
 * 
 *    Rev 1.30   Dec 20 2004 19:05:16   hernando
 * PTS10037068 - Added Registration Info.
 * 
 *    Rev 1.29   Dec 07 2004 02:44:54   popescu
 * PET 1117/56, verify search won't pop-up if alt acct/other ref # search returns one match
 * 
 *    Rev 1.28   Nov 07 2004 14:05:54   popescu
 * PET 1117/06, synch changes
 * 
 *    Rev 1.27   Nov 05 2004 16:25:42   FENGYONG
 * PET1117 FN54 Fund Broker Static : Add AllEntityField and ExactSearch 
 * 
 *    Rev 1.26   Jul 16 2003 15:51:26   FENGYONG
 * Add Account search using businessno
 * 
 *    Rev 1.25   Mar 21 2003 17:39:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.24   Feb 19 2003 10:54:36   popescu
 * minor fix, removed continue in a for loop
 * 
 *    Rev 1.23   Feb 18 2003 14:10:12   popescu
 * Fixed a display bug for the Wrap Account category
 * 
 *    Rev 1.22   Feb 17 2003 18:11:42   popescu
 * WrapAccount field bug fix
 * 
 *    Rev 1.21   Jan 27 2003 10:46:20   KOVACSRO
 * Changed SocialCode field into WrapAccount
 * 
 *    Rev 1.20   Dec 19 2002 13:19:50   sanchez
 * Add  addFieldDetails (ifds::AcctGroup, NTSRCHLIT::ENTITY_SEARCH_LIST);
 * 
 *    Rev 1.19   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.18   Oct 08 2002 11:54:14   HSUCHIN
 * PTS 10010112 - condition frame fix
 * 
 *    Rev 1.17   Sep 04 2002 15:45:44   PURDYECH
 * Condition, comment and formatting cleanup
 * 
 *    Rev 1.16   Aug 29 2002 16:44:52   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.15   Aug 29 2002 12:54:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   22 May 2002 18:24:14   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.13   27 Mar 2002 19:54:50   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.12   Mar 06 2002 17:17:58   HERNANDO
 * Added AcctGroup and CompanyCode to Entity Search List.
 * 
 *    Rev 1.11   Jan 15 2002 15:24:40   ZHANGCEL
 * Fixed the bug of RTS 10006741-- When searching account, entity highlighed is not the expected one
 * 
 *    Rev 1.10   25 Oct 2001 14:02:46   SMITHDAV
 * hasPermission changes...
 * 
 *    Rev 1.9   14 Jun 2001 11:58:02   SMITHDAV
 * Removed references to UserAccessProcess.
 * 
 *    Rev 1.8   03 May 2001 14:05:24   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   Mar 22 2001 09:59:00   YINGBAOL
 * implement searching other reference number
 * 
 *    Rev 1.6   15 Dec 2000 12:43:26   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.5   Sep 23 2000 15:45:40   YINGBAOL
 * pass account ot entity screen
 * 
 *    Rev 1.4   Aug 29 2000 15:16:24   YINGBAOL
 * add search account using intermediary code and account
 * 
 *    Rev 1.3   Aug 16 2000 15:00:52   YINGBAOL
 * implement fundction "search for Trade"
 * 
 *    Rev 1.2   Apr 04 2000 16:13:34   DT24433
 * changed to use hasPermission
 * 
 *    Rev 1.1   Mar 03 2000 12:11:08   POPESCUS
 * account search work
 * 
 *    Rev 1.0   Feb 15 2000 10:59:34   SMITHDAV
 * Initial revision.
// 
//    Rev 1.26   Feb 02 2000 16:03:16   VASILEAD
// Moved PopulateAccountOwner at AccDetailsProcess
// 
//    Rev 1.25   Jan 28 2000 12:27:04   POPESCUS
// fixes for more button
// 
//    Rev 1.24   Jan 26 2000 21:32:30   POPESCUS
// quick fix in ok2()
// 
//    Rev 1.23   Jan 23 2000 19:34:24   VASILEAD
// Reset functionality
// 
//    Rev 1.22   Jan 23 2000 16:44:42   VASILEAD
// Reset functionality
// 
//    Rev 1.21   Jan 21 2000 17:49:34   VASILEAD
// Refresh stuff
// 
//    Rev 1.20   Jan 16 2000 17:02:56   VASILEAD
// ?
// 
//    Rev 1.19   Jan 14 2000 14:01:02   VASILEAD
// Fix
// 
//    Rev 1.18   Jan 14 2000 09:10:20   POPESCUS
// updated VerifySearch to the new control model
// 
//    Rev 1.17   Jan 11 2000 14:35:44   VASILEAD
// Fixed entity background search
// 
//    Rev 1.16   Dec 15 1999 10:44:08   VASILEAD
// Implemented background search for Entity screen
// 
//    Rev 1.15   Dec 08 1999 18:33:36   POPESCUS
// more work to tighten up the XchgData object use
// 
//    Rev 1.14   Nov 20 1999 13:12:52   VASILEAD
// Worked on entity - account relationship
// 
//    Rev 1.13   Nov 18 1999 14:39:56   POPESCUS
// invoked entity process
// 
//    Rev 1.12   Nov 13 1999 19:42:38   VASILEAD
// Error handling
// 
//    Rev 1.11   Nov 09 1999 16:53:38   VASILEAD
// Changed to AccountEntityXref
// 
//    Rev 1.10   Oct 29 1999 12:38:34   DT24433
// changed to return CMD_FAILURE if commands invoked failed
// 
//    Rev 1.9   Oct 28 1999 19:03:04   DT24433
// changed from doOK to ok2 and removed getParent()-> in front of setParameter
// 
//    Rev 1.8   Oct 18 1999 15:33:28   POPESCUS
// Fixed small bug regarding stripping the account number when searching for entities
// 
//    Rev 1.7   Oct 18 1999 15:16:06   POPESCUS
// New search criterias
// 
//    Rev 1.6   Oct 18 1999 09:47:30   POPESCUS
// New search criterias
// 
//    Rev 1.5   Oct 05 1999 09:46:56   HUANGSHA
// Set focus on the selected entity if search for the AltAccount + BrokerCode
// 
//    Rev 1.4   Sep 16 1999 15:08:52   HSUCHIN
// defined the substitution list for the verify search view column headings.
// 
//    Rev 1.3   Sep 16 1999 11:20:38   VASILEAD
// Set the EntityId parameter for the AccDetailsProcess
// 
//    Rev 1.2   Aug 26 1999 09:54:08   DT24433
// changed getFieldFromCurrentListItem to getField
// 
//    Rev 1.1   Aug 17 1999 17:17:06   DT24433
// removed static FieldDetails array
// 
//    Rev 1.0   Jul 28 1999 13:16:46   POPESCUS
// Initial revision.
 *
*/
