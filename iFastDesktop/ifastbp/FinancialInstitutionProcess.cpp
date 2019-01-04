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
// ^FILE   : FinancialInstitutionProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FinancialInstitutionProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "financialinstitutionprocess.hpp"
#include "financialinstitutionprocessincludes.h"
#include <bfcbo\bfobjiter.hpp>
#include <ifastcbo\financialinstitutionlistrepository.hpp>
#include <ifastcbo\financialinstitution.hpp>
#include <ifastcbo\financialinstitutionlist.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FINANCIAL_INSTITUTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FINANCIAL_INSTITUTION;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator<FinancialInstitutionProcess> processCreator (CMD_BPROC_FINANCIAL_INSTITUTION);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("FinancialInstitutionProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
FinancialInstitutionProcess::FinancialInstitutionProcess (
   GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command &rCommand) : 
   AbstractProcess (pGIC, pGIParent, rCommand), 
_rpChildGI (NULL),
_pFinancialInstitutionList (NULL),
_dstrFICategory (NULL_STRING),
_dstrFIType (NULL_STRING),
_dstrFICode (NULL_STRING),
_dstrFIName (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

   addContainer (IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, true, 
      BF::NullContainerId, true, I_("FinancialInstitutionList"));

   //fields for financial institution dialog
   //addFieldDetails (ifds::FITransitCode, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::Name, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::SwiftCode, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::RefNumber, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankIdNum, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankAddr1, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankAddr2, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankAddr3, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankAddr4, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankAddr5, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankContact, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankCountry, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankPostal, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankIdType, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::Telex, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::FaxNumber, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::PhoneNumber, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::ShortName, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::InstRole, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::CodePage, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::FIStatusCode, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::InstCategory, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::ProcessDate, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::Username, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::ModDate, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::ModUser, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   //the institution code label field
   addFieldDetails (ifds::InstCodeLabel, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
}

   //******************************************************************************
FinancialInstitutionProcess::~FinancialInstitutionProcess ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//************************************************************************************
SEVERITY FinancialInstitutionProcess::doInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   try
   {
      processParameters ();
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
bool FinancialInstitutionProcess::doMoreRecordsExist (GenericInterface *rpGICaller, 
   const BFContainerId &idSearch)
{
   return rpGICaller == NULL || _pFinancialInstitutionList == NULL ? false : 
          _pFinancialInstitutionList->doMoreRecordsExist ();
}

//******************************************************************************
E_COMMANDRETURN FinancialInstitutionProcess::doProcess ()
{  
   MAKEFRAME2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand (this, CMD_GUI_FINANCIAL_INSTITUTION, 
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
SEVERITY FinancialInstitutionProcess::doValidateAll (BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   if (_pFinancialInstitutionList)
   {
      _pFinancialInstitutionList->validateAll (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool FinancialInstitutionProcess::doModelessChildComplete (const Command &cmd)
{
   return cmd.getKey () == CMD_GUI_FINANCIAL_INSTITUTION;
}

//******************************************************************************
bool FinancialInstitutionProcess::doModelessSetFocus (GenericInterface *rpGICaller)
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
            //remove list
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

               iter.positionByKey (I_("FinancialInstitutionList"));
               if (!iter.end ())
               {
                  iter.removeObjectFromMap (true);
               }
            }
            setContainer (IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, NULL);
            bRtn = _rpChildGI->refresh (this, I_("ReloadParams"));
            bRtn = _rpChildGI->modelessSetFocus (rpGICaller);
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
SEVERITY FinancialInstitutionProcess::doSetField (const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, const DString& strValue,
   bool bFormatted)
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void FinancialInstitutionProcess::doGetField (const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, DString &strValueOut,
   bool bFormatted) const
{
   strValueOut = NULL_STRING;
}

//******************************************************************************
void *FinancialInstitutionProcess::getPtrForContainer (const BFContainerId& idContainer,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   void *ptr = NULL;
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   try
   {
      if (IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST == idContainer)
      {
         bool bSuccess = false;
         FinancialInstitutionListRepository 
            *pFinancialInstitutionListRepository = NULL;

         if (pDSTCWorkSession->getFinancialInstitutionListRepository (
            pFinancialInstitutionListRepository) <= WARNING &&
            pFinancialInstitutionListRepository)
         {
            if (_dstrFICategory.empty() && _dstrFIType.empty())
            {
               //check whether the name is empty and call different methods...
               bSuccess = (_dstrFIName.empty() ?
                  //this should return all records
                  pFinancialInstitutionListRepository-> 
                     getFinancialInstitutionList (
                        _pFinancialInstitutionList,
                        idDataGroup) <= WARNING :
                  //this should return all records that start with '_dstrFIName'
                  pFinancialInstitutionListRepository->
                     getFinancialInstitutionList (_dstrFIName,
                        _pFinancialInstitutionList, 
                        idDataGroup) <= WARNING) &&
                  _pFinancialInstitutionList;
            }
            else if (!_dstrFICategory.empty() && !_dstrFIType.empty())
            {
               bSuccess = pFinancialInstitutionListRepository-> 
                  getFinancialInstitutionList (_dstrFICategory,
                     _dstrFIType, _dstrFICode,
                     _pFinancialInstitutionList,
                     idDataGroup) <= WARNING &&
               _pFinancialInstitutionList;
            }
            if (bSuccess)
            {
               ptr = _pFinancialInstitutionList;
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
SEVERITY FinancialInstitutionProcess::processParameters ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   //tells us whether the caller is search or maintenance
   getParameter (I_("FICategory"), _dstrFICategory);
   getParameter (I_("FIType"), _dstrFIType);
   getParameter (I_("FICode"), _dstrFICode);
   getParameter (I_("FIName"), _dstrFIName);
   _dstrFICategory.stripAll().upperCase();
   _dstrFIType.stripAll().upperCase();
   _dstrFICode.stripAll().upperCase();
   _dstrFIName.stripAll().upperCase();
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FinancialInstitutionProcess.cpp-arc  $
// 
//    Rev 1.1   Oct 24 2003 17:18:28   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 04 2003 16:06:06   popescu
// Initial revision.
// 
 * 
 */
