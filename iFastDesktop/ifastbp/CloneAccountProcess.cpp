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
// ^FILE   : CloneAccountProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2006
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : CloneAccountProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "cloneaccountprocess.hpp"
#include "cloneaccountprocessincludes.h"
#include "mfcaninterprocparam.hpp"

#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\cloneaccount.hpp>
#include <ifastcbo\mfaccount.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CLONE_ACCOUNT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_CLONE_ACCOUNT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< CloneAccountProcess > processCreator (CMD_BPROC_CLONE_ACCOUNT);

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "CloneAccountProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long ERR_NO_SLSREP_FOUND;
   extern CLASS_IMPORT const long ERR_NO_BRANCH_FOUND;
}


//******************************************************************************
//              Public Methods
//******************************************************************************
CloneAccountProcess::CloneAccountProcess ( GenericInterfaceContainer* pGIC, 
                                           GenericInterface* pGIParent, 
                                           const Command& rCommand ) : 
AbstractProcess (pGIC, pGIParent, rCommand),
_rpChildGI (NULL),
_pMFAccount (NULL),
_pCloneAccount (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   
   addContainer ( CLONE_ACCOUNT, 
                  false,  //non-repeatable
                  BF::NullContainerId,
                  true,  //updatable
                  I_("CloneAccount"));
	
   addFieldDetails ( ifds::BrokerCode,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::BranchCode,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::SlsrepCode,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::InterCode,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::InterAccount,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::AltAccount,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::EffectiveDate,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::AcctDesignation,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::TaxType,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::BrokerName,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::BranchName,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::SlsrepName,
                     CLONE_ACCOUNT);
   addFieldDetails ( ifds::CreateRep, 
                     CLONE_ACCOUNT);
   addFieldDetails ( ShouldAskForRep, 
                     CLONE_ACCOUNT,
                     SUBCLASS_PROCESS);
}

//******************************************************************************
CloneAccountProcess::~CloneAccountProcess()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   _rpChildGI = NULL;
}

//******************************************************************************
SEVERITY CloneAccountProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
      BFDataGroupId idDataGroup = getDataGroupId();

      getParameter (MFCAN_IP_PARAM::CALLER, _caller);
      getParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
      if (!_accountNum.empty ())
      {
//retrieve the mf account pointer
         if ( pDSTCWorkSession->getMFAccount ( idDataGroup, 
                                               _accountNum, 
                                               _pMFAccount, 
                                               I_ ("N"), 
                                               NULL_STRING, 
                                               true, 
                                               true) <= WARNING && 
              _pMFAccount)
         {
            if (pDSTCWorkSession->getCloneAccount (_accountNum, 
                                                   _pCloneAccount, 
                                                   idDataGroup) <= WARNING)
            {
               setContainer (CLONE_ACCOUNT, _pCloneAccount);
            }
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE (CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN CloneAccountProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (MFCAN_IP_PARAM::CALLER, _caller);
      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum);
      rtn = invokeCommand ( this, 
                            CMD_GUI_CLONE_ACCOUNT, 
                            PROC_NO_TYPE, 
                            isModal(), 
                            &_rpChildGI);
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE (CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
void CloneAccountProcess::doGetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      DString &strValueOut,
                                      bool bFormatted ) const
{  
   strValueOut = NULL_STRING;
   if (idContainer == CLONE_ACCOUNT)
   {
      if (idField == ShouldAskForRep)
      {
         BFAbstractCBO *rpPtr = const_cast<CloneAccountProcess*> (this)->
                              getCBOItem ( CLONE_ACCOUNT, 
                                           idDataGroup);
         
         if (rpPtr)
         {
            DString slsrepCode;

            rpPtr->getField (ifds::SlsrepCode, slsrepCode, idDataGroup, false);
            strValueOut = !slsrepCode.empty() &&
                        rpPtr->getErrorState (ifds::BrokerCode, idDataGroup) <= WARNING &&
                        rpPtr->getErrorState (ifds::BranchCode, idDataGroup) <= WARNING &&
                        rpPtr->getErrorState (ifds::SlsrepCode, idDataGroup) > WARNING ? I_("Y") : I_("N");
            if (strValueOut == I_("Y")) 
            {                     
               CONDITIONVECTOR conditions;
               
               if (rpPtr->getErrors (ifds::SlsrepCode, idDataGroup, conditions) > WARNING)
               {
                  CONDITIONVECTOR::iterator iter = conditions.begin();

                  while (iter != conditions.end())
                  {
                     if ((**iter).getCode() == CND::ERR_NO_SLSREP_FOUND ||
                         (**iter).getCode() == CND::ERR_NO_BRANCH_FOUND)
                     {
                        //if sales rep is not found, we can ask whether it should be created
                        break;
                     }
                     else
                     {
                        //other type of errors should not be used to create a new sales rep
                        strValueOut = I_("N");
                     }
                     ++iter;
                  }
               }
            }
         }            
      }
   }
}

//******************************************************************************
SEVERITY CloneAccountProcess::doSetField ( const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup,
                                           const DString& strValue,
                                           bool bFormatted)
{  
   return NO_CONDITION;
}

//******************************************************************************
void *CloneAccountProcess::getPtrForContainer ( const BFContainerId& idContainer, 
                                                const BFDataGroupId& idDataGroup)
{
   void *ptr = NULL;
   
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   assert (pDSTCWorkSession);

   if (pDSTCWorkSession)
   {
      try
      {
      }
      catch (ConditionException &)
      {
         throw;
      }
      catch( ... )
      {
         assert( 0 );
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                         CND::BP_ERR_UNKNOWN_EXCEPTION );
      }
   }
   return ptr;
}

//*****************************************************************************
bool CloneAccountProcess::doOk (GenericInterface *rpGICaller)
{
   return true;
}

//******************************************************************************
void CloneAccountProcess::doPostOk ( GenericInterface *rpGICaller, 
                                     bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));

	if (bSuccessFlag)
   {
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
      BFDataGroupId idDataGroup = getDataGroupId();
      DString newAccountNum;

      pDSTCWorkSession->getHostAccountNum (_accountNum, newAccountNum);
      newAccountNum.strip().stripLeading( '0' );
      if (!newAccountNum.empty())
      {
         AccountEntityXref *pAccountEntityXref (NULL);

         if (pDSTCWorkSession->getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
         {
            pAccountEntityXref->PopulateEntitiesList (idDataGroup, newAccountNum);
         }
      }
   }
}

//**********************************************************************
SEVERITY CloneAccountProcess::doValidateAll( BFAbstractCBO *rpWSD, 
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   if (_pCloneAccount)
   {
		_pCloneAccount->validateAll (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool CloneAccountProcess::doModelessChildComplete (const Command &cmd)
{
   // End when GUI ends
   return (cmd.getKey() == CMD_GUI_CLONE_ACCOUNT);
}

//******************************************************************************
bool CloneAccountProcess::doModelessSetFocus (GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   
   return true;
}

//******************************************************************************
bool CloneAccountProcess::setCommitDataGroupAsHost()
{
   return true;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CloneAccountProcess.cpp-arc  $
// 
//    Rev 1.3   Feb 27 2007 21:15:28   popescu
// Incident#  831221 - backed the code of Web Account Clone feature for CDN market
// 
//    Rev 1.2   Dec 19 2006 16:56:32   fengyong
// PET2282 FN01 - Add Clone Account web page
// 
//    Rev 1.1   Nov 10 2006 18:07:26   popescu
// PET 2281/FN 01
// 
//    Rev 1.0   Nov 08 2006 17:32:08   popescu
// Initial revision.
// Initial revision.
// 
 */
