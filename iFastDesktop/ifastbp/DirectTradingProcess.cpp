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
//    Copyright 2002 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : DirectTradingProcess.cpp
// ^AUTHOR : 
// ^DATE   : May 24,2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : DirectTradingProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\bankinstructions.hpp>
//#include <ifastcbo\DirectTrading.hpp>
#include "DirectTradingprocess.hpp"
#include "DirectTradingprocessincludes.h"
//#include <ifastcbo\DirectTradingtrade.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\shareholder.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\DirectTradingBankInstructionsList.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DIRECT_TRADING;
extern IFASTBP_LINKAGE const I_CHAR* BANK_INSTRUCTIONS_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_DIRECT_TRADING;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< DirectTradingProcess > processCreator( CMD_BPROC_DIRECT_TRADING );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace DirectTrading_Para
{
   const I_CHAR * const ACCOUNT_NUM         = I_( "AccountNum" );
}

namespace 
{
   const I_CHAR * const CLASSNAME      = I_( "DirectTradingProcess" );
   const I_CHAR * const YES            = I_("Y");
   const I_CHAR * const NO             = I_("N");
}
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId HoldingTransitNo;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId TransitNo;
   extern CLASS_IMPORT const BFTextFieldId BankAcctNum;
   extern CLASS_IMPORT const BFTextFieldId BankIdValue;
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
   extern CLASS_IMPORT const BFTextFieldId DTAExist;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319DirectTradingProcess::DirectTradingProcess() : 
DirectTradingProcess::DirectTradingProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL ),_pDirectTrading(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addContainer( IFASTBP_PROC::DIRECT_TRADING_LIST,   true, BF::NullContainerId, true,I_("DirectTradingList") );
   addContainer( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,   true, BF::NullContainerId, true,I_("DTA_Bank_List") );
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, true, I_("Account") );

   addFieldDetails( ifds::DTAType,  IFASTBP_PROC::DIRECT_TRADING_LIST );
   addFieldDetails( ifds::HoldingTransitNo,   IFASTBP_PROC::DIRECT_TRADING_LIST );
   addFieldDetails( ifds::EffectiveDate,   IFASTBP_PROC::DIRECT_TRADING_LIST );
   addFieldDetails( ifds::StopDate,   IFASTBP_PROC::DIRECT_TRADING_LIST );
   addFieldDetails( ifds::ModDate,   IFASTBP_PROC::DIRECT_TRADING_LIST );
   addFieldDetails( ifds::ModUser,   IFASTBP_PROC::DIRECT_TRADING_LIST );
   addFieldDetails( ifds::ProcessDate,   IFASTBP_PROC::DIRECT_TRADING_LIST );
   addFieldDetails( ifds::Username,   IFASTBP_PROC::DIRECT_TRADING_LIST );

   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO );

   addFieldDetails( ifds::TransitNo, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::BankIdValue, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::BankAcctNum, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::BankAcctCurrency, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::AcctUseCode, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST );

}

//******************************************************************************
DirectTradingProcess::~DirectTradingProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
SEVERITY DirectTradingProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );
   SEVERITY sevRtn=NO_CONDITION;
   try
   {
	   getParameter( DirectTrading_Para::ACCOUNT_NUM, _dstrAccountNum );
	   _dstrAccountNum.strip().stripLeading('0');
   
	   DirectTradingList* pDirectTradingList;
	   const BFDataGroupId& idDataGroup = getDataGroupId();
	   if( _dstrAccountNum != NULL_STRING )
	   {
		   MFAccount* pMFAccount = NULL;

		   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
		   if( dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING )
		   {
			    pMFAccount->getField(ifds::ShrNum, _dstrShrNum, idDataGroup, false);
				if( pMFAccount->getDirectTradingList(pDirectTradingList,idDataGroup) <= WARNING )
				{
					setContainer( IFASTBP_PROC::DIRECT_TRADING_LIST, pDirectTradingList ); 
				}
		   }
		   
		   Shareholder * pShareholder;		 
           dstcWorkSession->getShareholder (idDataGroup, _dstrShrNum, pShareholder);

           DirectTradingBankInstructionsList *pDirectTradingBankInstructionsList = NULL;

           if (pShareholder)
           {
               if (pShareholder->getDirectTradingBankInstructionsList (
                  pDirectTradingBankInstructionsList, idDataGroup) <= WARNING && 
                  pDirectTradingBankInstructionsList)
               {
                  pDirectTradingBankInstructionsList->setField (ifds::AccountNum, 
                     _dstrAccountNum, idDataGroup, false);
                  setContainer( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, pDirectTradingBankInstructionsList );
               }
           }
	   }
	   else
	   {
		   //Add Condition 
	   }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool DirectTradingProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_BPROC_DIRECT_TRADING );
}

//******************************************************************************
bool DirectTradingProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN DirectTradingProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {

      setParameter( DirectTrading_Para::ACCOUNT_NUM, _dstrAccountNum );

	  if( !isXMLAPIContext() )
      {
		  rtn = invokeCommand( this, CMD_GUI_DIRECT_TRADING, getProcessType(), true,
                           &_rpChildGI );
	  }
	  else
	  {
		  rtn = CMD_MODELESS_INPROCESS;
	  }
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************

void DirectTradingProcess::doGetField(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted
                                  ) const
{
	/*
   if( idField == SETTL_PROC::PERMIT_INQ || idField == SETTL_PROC::PERMIT_UPDATE )
   {
      DirectTrading* pDirectTrading;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getDirectTrading(  pDirectTrading, getDataGroupId()    );
      if( pDirectTrading )
      {
         DString dstrSearchType;
         pDirectTrading->getField(ifds::SearchType,dstrSearchType,getDataGroupId(),false );
         dstrSearchType.strip();
         strValueOut = pDirectTrading->hasPermissionForSearchType(dstrSearchType,idField == SETTL_PROC::PERMIT_INQ )? YES:NO;
      }
   }
   else
   {
      assert(0);
   }*/
}
//**************************************************************************************
bool DirectTradingProcess::doOk(
                            GenericInterface *rpGICaller
                            )
{
   return(true);
}
//*****************************************************************************
SEVERITY  DirectTradingProcess:: doSetField(
                                        const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& idField,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strValue,
                                        bool bFormatted
                                        )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSetField" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
bool DirectTradingProcess::doSend(
                              GenericInterface *rpGICaller,
                              const I_CHAR *szMessage
                              ) 
{
/*
   DString dstrTag(szMessage);
   DString dstrFilter(NULL_STRING);
   if( dstrTag == DirectTrading_Para::DISPLAY_SETTLE_ONLY )
   {
      DString strSettle = asString( ifds::Settled.getId() );
      dstrFilter += strSettle;
      dstrFilter += I_( "=" );
      dstrFilter += I_("Y");
      setDataFilter( IFASTBP_PROC::DIRECT_TRADING_LIST, dstrFilter);
      return(true);
   }
   else if( dstrTag == DirectTrading_Para::DISPLAY_ALL )
   {
      clearDataFilter( IFASTBP_PROC::DIRECT_TRADING_LIST );
      return(true);
   }
*/
   return(false);
}

//******************************************************************************

void *DirectTradingProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   void *ptr = NULL;

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
      if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
         MFAccount *pMFAccount;
         if( dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING )
         {
            ptr = pMFAccount;
         }
      }
	  if( IFASTBP_PROC::BANK_INSTRUCTIONS_LIST == idContainer )
	  {
		   Shareholder * pShareholder;		 
           dstcWorkSession->getShareholder (idDataGroup, _dstrShrNum, pShareholder);

           DirectTradingBankInstructionsList 
               *pDirectTradingBankInstructionsList = NULL;

           if (pShareholder)
           {
               if (pShareholder->getDirectTradingBankInstructionsList (
                  pDirectTradingBankInstructionsList, idDataGroup) <= WARNING && 
                  pDirectTradingBankInstructionsList)
               {
                  pDirectTradingBankInstructionsList->setField (ifds::AccountNum, 
                     _dstrAccountNum, idDataGroup, false);
                  ptr = pDirectTradingBankInstructionsList;
               }
           }
	  }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
SEVERITY DirectTradingProcess::doValidateAll (BFAbstractCBO *rpWSD,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_ ("doValidateAll"));

   Shareholder * pShareholder;		 
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getShareholder (idDataGroup, _dstrShrNum, pShareholder);
   DirectTradingBankInstructionsList 
   *pDirectTradingBankInstructionsList = NULL;

   if (pShareholder)
   {
	   pShareholder->setField (ifds::DTAExist, YES, idDataGroup, false);
       if (pShareholder->getDirectTradingBankInstructionsList (
          pDirectTradingBankInstructionsList, idDataGroup) <= WARNING && 
          pDirectTradingBankInstructionsList)
       {
			pDirectTradingBankInstructionsList->validateAll (idDataGroup);
	   }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DirectTradingProcess.cpp-arc  $
// 
//    Rev 1.5   Dec 15 2003 13:47:32   popescu
// Change the datatype of the TransitNo field
// 
//    Rev 1.4   Oct 31 2003 14:48:40   FENGYONG
// set flag for the validation
// 
//    Rev 1.3   Oct 28 2003 10:35:08   FENGYONG
// Override dovalidateall 
// 
//    Rev 1.2   Oct 23 2003 17:49:28   FENGYONG
// Add field AcctUseCode
// 
//    Rev 1.1   Oct 16 2003 12:03:46   FENGYONG
// PET809 FN08 Direct trading enhancement
// 
//    Rev 1.0   Oct 07 2003 10:12:52   FENGYONG
// Initial Revision
 * 
 *
 */
