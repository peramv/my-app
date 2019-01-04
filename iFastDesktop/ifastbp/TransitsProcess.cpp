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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TransitsProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransitsProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "transitsprocess.hpp"
#include "transitsprocessincludes.h"
#include <ifastcbo\financialinstitutionlistrepository.hpp>
#include <ifastcbo\financialinstitution.hpp>
#include <ifastcbo\financialinstitutiontransit.hpp>
#include <ifastcbo\financialinstitutionlist.hpp>
#include <ifastcbo\financialinstitutiontransitlist.hpp>
#include "mfcaninterprocparam.hpp"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRANSITS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANSITS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator<TransitsProcess> processCreator (CMD_BPROC_TRANSITS);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("TransitsProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
TransitsProcess::TransitsProcess (
   GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command &rCommand) : 
   AbstractProcess (pGIC, pGIParent, rCommand), 
_rpChildGI (NULL),
_pTransitsList (NULL),
_pFinancialInstitution (NULL),
_dstrFIListKey (NULL_STRING),
_dstrTransitName (NULL_STRING),
_dstrCaller (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

   addContainer (IFASTBP_PROC::FINANCIAL_INSTITUTION, false, 
      BF::NullContainerId, false, I_("FinancialInstitution"));

   addFieldDetails (ifds::Name, IFASTBP_PROC::FINANCIAL_INSTITUTION);
   addFieldDetails (ifds::InstCategory, IFASTBP_PROC::FINANCIAL_INSTITUTION);
   addFieldDetails (ifds::BankIdType, IFASTBP_PROC::FINANCIAL_INSTITUTION);
   addFieldDetails (ifds::BankIdNum, IFASTBP_PROC::FINANCIAL_INSTITUTION);

   addContainer (IFASTBP_PROC::TRANSITS_LIST, true, 
      BF::NullContainerId, true, I_("TransitsList"));
   addFieldDetails (ifds::InstCategory, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::FITransitCode, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankIdType, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankIdNum, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::Name, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankAddr1, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankAddr2, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankAddr3, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankAddr4, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankAddr5, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankCountry, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankContact, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::BankPostal, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::Telex, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::FaxNumber, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::PhoneNumber, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::ShortName, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::InstRole, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::FIStatusCode, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::ProcessDate, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::Username, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::ModDate, IFASTBP_PROC::TRANSITS_LIST);
   addFieldDetails (ifds::ModUser, IFASTBP_PROC::TRANSITS_LIST);
   //the institution code label field
   addFieldDetails (ifds::InstCodeLabel, IFASTBP_PROC::TRANSITS_LIST);
   //used when direct transit search
   addFieldDetails (InstCateg, IFASTBP_PROC::TRANSITS_LIST, 
      SUBCLASS_PROCESS);
   addFieldDetails (InstName, IFASTBP_PROC::TRANSITS_LIST, 
      SUBCLASS_PROCESS);
   addFieldDetails (IsSupport, BF::NullContainerId, 
      SUBCLASS_PROCESS);
}

//******************************************************************************
TransitsProcess::~TransitsProcess ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//************************************************************************************
SEVERITY TransitsProcess::doInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   try
   {
      processParameters ();
      setTransitListContainer();
   }
   catch (ConditionException& ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
bool TransitsProcess::doMoreRecordsExist (GenericInterface *rpGICaller, 
   const BFContainerId &idSearch)
{
   return rpGICaller == NULL || _pTransitsList == NULL ? false : 
          _pTransitsList->doMoreRecordsExist ();
}

//******************************************************************************
E_COMMANDRETURN TransitsProcess::doProcess ()
{  
   MAKEFRAME2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (MFCAN_IP_PARAM::CALLER, _dstrCaller);
      rtn = invokeCommand (this, CMD_GUI_TRANSITS, 
         getProcessType (), isModal (), &_rpChildGI);
   }
   catch (ConditionException &ce)
   {
      assert (0);
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
SEVERITY TransitsProcess::doValidateAll (BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   if (_pTransitsList)
   {
      _pTransitsList->validateAll (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
bool TransitsProcess::doModelessChildComplete (const Command &cmd)
{
   return cmd.getKey () == CMD_GUI_TRANSITS;
}

//******************************************************************************
bool TransitsProcess::doModelessSetFocus (GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert (_rpChildGI && isValidModelessInterface (_rpChildGI));
      if (processParameters () <= WARNING)
      {
         if (isValidModelessInterface (_rpChildGI))
         {  // Only if child still exists
            if (_dstrCaller == I_("TransitsMaint"))
            {
               DSTCWorkSession* pDSTCWorkSession = 
                  dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
               FinancialInstitutionListRepository 
                  *pFinancialInstitutionListRepository = NULL;

               if (pDSTCWorkSession->getFinancialInstitutionListRepository (
                  pFinancialInstitutionListRepository) <= WARNING &&
                  pFinancialInstitutionListRepository)
               {
                  BFObjIter iter (*pFinancialInstitutionListRepository, 
                     getDataGroupId ());

                  iter.positionByKey (I_("FinancialInstitutionTransitsList"));
                  if (!iter.end ())
                  {
                     iter.removeObjectFromMap (true);
                  }
               }
               setContainer (IFASTBP_PROC::TRANSITS_LIST, NULL);
               setContainer (IFASTBP_PROC::FINANCIAL_INSTITUTION, NULL);
               //only if direct transit search
               setTransitListContainer();
               setParameter (MFCAN_IP_PARAM::CALLER, _dstrCaller);
               bRtn = _rpChildGI->refresh (this, I_("ReloadParams"));
               bRtn = _rpChildGI->modelessSetFocus (rpGICaller);
            }
         }
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return bRtn;
}

//******************************************************************************
SEVERITY TransitsProcess::doSetField (const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, const DString& strValue,
   bool bFormatted)
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void TransitsProcess::doGetField (const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, DString &strValueOut,
   bool bFormatted) const
{
   strValueOut = NULL_STRING;
   if (_dstrCaller == I_("TransitsMaint") && 
      (idContainer == IFASTBP_PROC::TRANSITS_LIST && 
         (idField == InstCateg || idField == InstName)))
   {
      DSTCWorkSession* pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
      FinancialInstitutionTransit *pFinancialInstitutionTransit  =
         dynamic_cast<FinancialInstitutionTransit *>(
         const_cast <TransitsProcess*> (this)->
         getCBOItem(IFASTBP_PROC::TRANSITS_LIST, idDataGroup));

      if (pFinancialInstitutionTransit)
      {
         DString category,
            type,
            code;
   
         pFinancialInstitutionTransit->getField(ifds::InstCategory, 
            category, idDataGroup, false);
         pFinancialInstitutionTransit->getField(ifds::BankIdType, 
            type, idDataGroup, false);
         pFinancialInstitutionTransit->getField(ifds::BankIdNum, 
            code, idDataGroup, false);
         category = 
            FinancialInstitution::getParentCategory (category);
         
         if (!category.empty() && !type.empty() && !code.empty())
         {
            FinancialInstitutionList fiSearch (*pDSTCWorkSession);

            if (fiSearch.init (category, type, code) <= WARNING)
            {
               BFObjIter iter (fiSearch, idDataGroup, false, 
                  BFObjIter::ITERTYPE::NON_DELETED);

               if (!iter.end())
               {
                  if (idField == InstCateg)
                  {
                     iter.getObject()->getField(ifds::InstCategory, strValueOut, 
                        idDataGroup, bFormatted);
                  }
                  else if (idField == InstName)
                  {
                     iter.getObject()->getField(ifds::Name, strValueOut, 
                        idDataGroup, bFormatted);
                  }
               }
            }
         }
         else //the least we can do is to return the InstCatet field
         {
            if (idField == InstCateg && !category.empty())
            {
               strValueOut = category;
            }
         }
      }
   }
   else if (idField == IsSupport)
   {
      strValueOut = getProcessType() == PROC_SUPPORT ? I_("Y") : I_("N");
   }
}

//******************************************************************************
void *TransitsProcess::getPtrForContainer (const BFContainerId& idContainer,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   void *ptr = NULL;
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   try
   {
      FinancialInstitutionListRepository 
         *pFinancialInstitutionListRepository = NULL;

      if (pDSTCWorkSession->getFinancialInstitutionListRepository (
         pFinancialInstitutionListRepository) <= WARNING &&
         pFinancialInstitutionListRepository)
      {
         if (IFASTBP_PROC::FINANCIAL_INSTITUTION == idContainer)
         {
            assert( _dstrCaller != I_("TransitsMaint"));

            FinancialInstitutionList 
               *pFinancialInstitutionList = NULL;

            if (pFinancialInstitutionListRepository-> 
               getFinancialInstitutionList (pFinancialInstitutionList ,
                  idDataGroup) <= WARNING && pFinancialInstitutionList)
            {
               BFObjIter iter (*pFinancialInstitutionList, idDataGroup, false, 
                  BFObjIter::ITERTYPE::NON_DELETED);
      
               if (_dstrFIListKey != NULL_STRING)
               {
                  iter.positionByKey(_dstrFIListKey);
                  if (!iter.end())
                  {
                     _pFinancialInstitution = 
                        dynamic_cast<FinancialInstitution*>(iter.getObject());
                     ptr = _pFinancialInstitution;
                  }
               }
            }
         }
         else if (IFASTBP_PROC::TRANSITS_LIST == idContainer)
         {
            if (_dstrCaller != I_("TransitsMaint") && 
               _pFinancialInstitution)
            {
               DString category, 
                  type, 
                  code;

               _pFinancialInstitution->getField(ifds::InstCategory, category, 
                  idDataGroup, false);
               _pFinancialInstitution->getField(ifds::BankIdType, type, 
                  idDataGroup, false);
               _pFinancialInstitution->getField(ifds::BankIdNum, code, 
                  idDataGroup, false);
               if (category == FI_CATEGORY::BANK)
               {
                  category = FI_CATEGORY::BANK_TRANSIT;
               }
               else if (category == FI_CATEGORY::INSTITUTION)
               {
                  category = FI_CATEGORY::INSTITUTION_TRANSIT;
               }
               if (pFinancialInstitutionListRepository->getTransits (
                  category, type, code, _pTransitsList, 
                  idDataGroup) <= WARNING)
               {
                  ptr = _pTransitsList;
               }
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
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;

}

//******************************************************************************
SEVERITY TransitsProcess::processParameters ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter (I_("FITName"), _dstrTransitName);
   getParameter (MFCAN_IP_PARAM::CALLER, _dstrCaller);
   getParameter (MFCAN_IP_PARAM::LIST_KEY, _dstrFIListKey);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY TransitsProcess::setTransitListContainer()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_("setTransitListContainer"));

   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   //only in this case we allow to have the transit list container set directly,
   //otherwise 'getPtrForContainer' should be used
   if (_dstrCaller == I_("TransitsMaint"))
   {
      FinancialInstitutionListRepository 
         *pFinancialInstitutionListRepository = NULL;

      if (pDSTCWorkSession->getFinancialInstitutionListRepository (
         pFinancialInstitutionListRepository) <= WARNING &&
         pFinancialInstitutionListRepository)
      {
         bool bSuccess = (_dstrTransitName.empty() ?
            //this should return all records
            pFinancialInstitutionListRepository->getTransits (
               _pTransitsList, getDataGroupId()) <= WARNING :
               //this should return all records that start with the given name
            pFinancialInstitutionListRepository->getTransits (
               _dstrTransitName, _pTransitsList, getDataGroupId()) <= WARNING) &&
            _pTransitsList;
         if (bSuccess)
         {
            setContainer (IFASTBP_PROC::TRANSITS_LIST, _pTransitsList);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransitsProcess.cpp-arc  $
// 
//    Rev 1.2   Oct 27 2003 19:48:28   popescu
// CIBC PET809, FN 13, added Transit Search by name
// 
//    Rev 1.1   Oct 24 2003 17:19:00   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 04 2003 16:06:14   popescu
// Initial revision.
// 
 * 
 */
