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
// ^FILE   : FinancialInstitutionSearchProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FinancialInstitutionSearchProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "financialinstitutionsearchprocess.hpp"
#include "financialinstitutionsearchprocessincludes.h"
#include <ifastcbo\financialinstitution.hpp>
#include <ifastcbo\financialinstitutiontransitlist.hpp>
#include <ifastcbo\financialinstitutionlist.hpp>
#include <ifastcbo\fillsearchcriteria.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FINANCIAL_INSTITUTION_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FINANCIAL_INSTITUTION_SEARCH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator<FinancialInstitutionSearchProcess> processCreator (CMD_BPROC_FINANCIAL_INSTITUTION_SEARCH);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("FinancialInstitutionSearchProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
FinancialInstitutionSearchProcess::FinancialInstitutionSearchProcess (
   GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command &rCommand) : 
   AbstractProcess (pGIC, pGIParent, rCommand), 
_rpChildGI (NULL),
_pFillSearchCriteria (NULL),
_pFinancialInstitutionList (NULL),
_pFinancialInstitutionTransitList (NULL),
_dstrFICategory (NULL_STRING),
_dstrFIType (NULL_STRING),
_dstrFICode (NULL_STRING),
_dstrFIName (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

   addContainer (IFASTBP_PROC::SEARCH_CRITERIA_FILLER, false, BF::NullContainerId, true);

   addFieldDetails (ifds::FillSearchType, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails (ifds::SearchCriteria, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails (ifds::SearchUsing, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails (ifds::SearchLabel1, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails (ifds::SearchLabel2, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails (ifds::SearchLabel3, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails (ifds::SearchFieldCriteria1, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails (ifds::SearchFieldCriteria2, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails (ifds::SearchFieldCriteria3, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);
   addFieldDetails (ifds::HowManySearchCriterias, IFASTBP_PROC::SEARCH_CRITERIA_FILLER);

   addContainer (IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, true, 
      BF::NullContainerId, true, I_("FinancialInstitutionList"));

   //fields for financial institution search dialog
   addFieldDetails (ifds::FITransitCode, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BranchName, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::Name, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankIdNum, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankAddr1, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankCountry, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
   addFieldDetails (ifds::BankIdType, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
}

//******************************************************************************
FinancialInstitutionSearchProcess::~FinancialInstitutionSearchProcess ()
{
   TRACE_DESTRUCTOR (CLASSNAME);

   if (_pFillSearchCriteria)
   {
      delete _pFillSearchCriteria;
      _pFillSearchCriteria = NULL;
   }
   if (_pFinancialInstitutionList)
   {
      delete _pFinancialInstitutionList;
      _pFinancialInstitutionList = NULL;
   }
   if (_pFinancialInstitutionTransitList)
   {
      delete _pFinancialInstitutionTransitList;
      _pFinancialInstitutionTransitList = NULL;
   }
}

//************************************************************************************
SEVERITY FinancialInstitutionSearchProcess::doInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   try
   {
      if (processParameters () <= WARNING) //initialize the search criteria
      {
         _pFillSearchCriteria = new FillSearchCriteria (*pDSTCWorkSession);
         if (_pFillSearchCriteria->init (SEARCH_TYPE::FI_FEATURES_F4, BF::HOST) <= WARNING)
         {			
            _pFillSearchCriteria->setField (ifds::SearchCriteria, 
               FI_SEARCH_CRITERIA::INSTITUTIONS_F4, BF::HOST, false);
            _pFillSearchCriteria->setField (ifds::SearchUsing, 
               FI_SEARCH_INSTITUTIONS_F4_USING::NAME, BF::HOST, false);
            //as defaults
            _pFillSearchCriteria->setField (ifds::SearchFieldCriteria1, 
               _dstrFICategory, BF::HOST, false);
            _pFillSearchCriteria->setField (ifds::SearchFieldCriteria2, 
               _dstrFIType, BF::HOST, false);
            setContainer (IFASTBP_PROC::SEARCH_CRITERIA_FILLER, _pFillSearchCriteria);
            if (FinancialInstitution::transit (_dstrFICategory))
            {
               //check whether we can find the institution name, if exists
               FinancialInstitutionList fiSearch (*pDSTCWorkSession);

               if (fiSearch.init (FinancialInstitution::getParentCategory (_dstrFICategory), 
                  _dstrFIType, _dstrFICode) <= WARNING)
               {
                  BFObjIter bfIter (fiSearch, getDataGroupId());
         
                  bfIter.begin ();
                  if (!bfIter.end ())
                  {
                     bfIter.getObject ()->getField (ifds::Name, 
                        _dstrFIName, getDataGroupId());
                  }
               }
            }
         }
      }
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
bool FinancialInstitutionSearchProcess::doMoreRecordsExist (GenericInterface *rpGICaller, 
   const BFContainerId &idSearch)
{
   return rpGICaller == NULL || _pFinancialInstitutionList == NULL ? false : 
            _pFinancialInstitutionList->doMoreRecordsExist () ||
         _pFinancialInstitutionTransitList == NULL ? false : 
            _pFinancialInstitutionTransitList->doMoreRecordsExist ();
}

//******************************************************************************
E_COMMANDRETURN FinancialInstitutionSearchProcess::doProcess ()
{  
   MAKEFRAME2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (I_("FICategory"), _dstrFICategory);
      setParameter (I_("FIName"), _dstrFIName);
      rtn = invokeCommand (this, CMD_GUI_FINANCIAL_INSTITUTION_SEARCH, 
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
bool FinancialInstitutionSearchProcess::doModelessChildComplete (const Command &cmd)
{
   return cmd.getKey () == CMD_GUI_FINANCIAL_INSTITUTION_SEARCH;
}

//******************************************************************************
SEVERITY FinancialInstitutionSearchProcess::performSearch (
   GenericInterface *rpGICaller, 
   const BFContainerId &idSearch, 
   E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));
   try
   {
      const BFDataGroupId &idDataGroup = getDataGroupId ();

      if (eSearchAction == SEARCH_START)
      {
         if (_pFillSearchCriteria && 
            _pFillSearchCriteria->validateAll (idDataGroup) <= WARNING)
         {
            DSTCWorkSession *pDSTCWorkSession = 
               dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
            bool bSuccess = false;

            //remove the pointer and clear the container
            if (_pFinancialInstitutionList)
            {
               delete _pFinancialInstitutionList;
               _pFinancialInstitutionList = NULL;
            }
            //remove the pointer and clear the container
            if (_pFinancialInstitutionTransitList)
            {
               delete _pFinancialInstitutionTransitList;
               _pFinancialInstitutionTransitList = NULL;
            }
            setContainer (IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, NULL);

            DString searchUsing,
               category, 
               type, 
               thirdValue;

            getField (this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
               ifds::SearchUsing, searchUsing, false);
            getField (this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
               ifds::SearchFieldCriteria1, category, false);
            getField (this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
               ifds::SearchFieldCriteria2, type, false);
            getField (this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
               ifds::SearchFieldCriteria3, thirdValue, false);
            if (searchUsing == FI_SEARCH_INSTITUTIONS_F4_USING::CODE)
            {
               if (FinancialInstitution::institution (category) )
               {		  
				  if ( FinancialInstitution::hasTransits(category, type) )
				     category = I_( "02" );

                  //search, data not found should not be ignored
                  _pFinancialInstitutionList = 
                     new FinancialInstitutionList (*pDSTCWorkSession, true);
                  bSuccess = _pFinancialInstitutionList->init (category, 
                     type, thirdValue) <= WARNING;				   
               }
               else if (FinancialInstitution::transit (category))
               {
                  _pFinancialInstitutionTransitList = 
                     new FinancialInstitutionTransitList (*pDSTCWorkSession, true);
                  bSuccess = _pFinancialInstitutionTransitList->init (
                     category, type, _dstrFICode, thirdValue) <= WARNING;
               }
            }
            else if (searchUsing == FI_SEARCH_INSTITUTIONS_F4_USING::NAME)
            {
               if (FinancialInstitution::institution (category))
               {
                  _pFinancialInstitutionList = 
                     new FinancialInstitutionList (*pDSTCWorkSession, true);
                  bSuccess = _pFinancialInstitutionList->initForNameCategoryType (
                     category, type, thirdValue) <= WARNING;
               }
               else if (FinancialInstitution::transit (category))
               {
                  _pFinancialInstitutionTransitList = 
                     new FinancialInstitutionTransitList (*pDSTCWorkSession, true);
                  if (_dstrFICode != NULL_STRING)
                  {
                     bSuccess = _pFinancialInstitutionTransitList->initForNameCategoryTypeInstitutionCode (
                        category, type, _dstrFICode, thirdValue) <= WARNING;
                  }
                  else
                  {
                     bSuccess = _pFinancialInstitutionTransitList->initForNameCategoryType (
                        category, type, thirdValue) <= WARNING;
                  }
               }
            }
            if (bSuccess)
            {
               if (_pFinancialInstitutionList)
               {
                  setContainer (IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
                     _pFinancialInstitutionList);
               }
               else if (_pFinancialInstitutionTransitList)
               {
                  setContainer (IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
                     _pFinancialInstitutionTransitList);
               }
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
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY FinancialInstitutionSearchProcess::processParameters ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   //tells us whether the caller is search or maintenance
   getParameter (I_("FICategory"), _dstrFICategory);
   getParameter (I_("FIType"), _dstrFIType);
   getParameter (I_("FICode"), _dstrFICode);
   _dstrFICategory.stripAll().upperCase();
   _dstrFIType.stripAll().upperCase();
   _dstrFICode.stripAll().upperCase();
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FinancialInstitutionSearchProcess.cpp-arc  $
// 
//    Rev 1.5   May 12 2005 11:56:08   porteanm
// Incident 265740 - Bank search.
// 
//    Rev 1.4   Nov 24 2004 19:12:28   hernando
// PTS10033887 - Pad Institution Number and Transit Number with zeros.
// 
//    Rev 1.3   Jan 20 2004 18:27:34   popescu
// PET 809, FN 13,
// part backing-out bank master, 
// display the bank name in the FinancialSearchDialog caption if searching for transits
// 
//    Rev 1.2   Jan 12 2004 17:55:08   popescu
// PTS 10020577, added F4 institution search and F4 transit search on banking instriuctions screen, for corresponding edit fields
// 
//    Rev 1.1   Oct 24 2003 17:18:50   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 04 2003 16:06:10   popescu
// Initial revision.
// 
 * 
 */
