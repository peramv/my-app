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
//    AUTHOR : Aguila Amelia
//    DATE   : Jan 2005
//
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^CLASS    : InvDetlDeductionProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "mfcaninterprocparam.hpp"
#include "InvDetlDeductionProcess.hpp"
#include "InvDetlDeductionProcessIncludes.h"
#include <ifastcbo\TransactionList.hpp>
#include <ifastcbo\InvDetlDeductionList.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_INVENTORY_DETAIL_DEDUCTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INVENTORY_DETAIL_DEDUCTION;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< InvDetlDeductionProcess > processCreator( CMD_BPROC_INVENTORY_DETAIL_DEDUCTION );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("InvDetlDeductionProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   //field ids used	
   extern CLASS_IMPORT const BFTextFieldId InvDetlDeduction;   		
}

//******************************************************************************
//              Public Methods
//******************************************************************************
InvDetlDeductionProcess::InvDetlDeductionProcess( GenericInterfaceContainer* pGIC, 
														  GenericInterface* pGIParent, 
														  const Command& rCommand )
: AbstractProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL),
_pTransList(NULL),
_pInvDetlDeductList( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   
   addContainer( IFASTBP_PROC::TRANS_LIST, true);	
   
	addFieldDetails(ifds::TransId,      IFASTBP_PROC::TRANS_LIST );
	addFieldDetails(ifds::TransNum,     IFASTBP_PROC::TRANS_LIST );
	addFieldDetails(ifds::TransType,    IFASTBP_PROC::TRANS_LIST);
	addFieldDetails(ifds::TradeDate,    IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::SettleDate,   IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::GrossAmt,     IFASTBP_PROC::TRANS_LIST );
   addFieldDetails(ifds::Units,        IFASTBP_PROC::TRANS_LIST );

   addContainer( IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST, true,  IFASTBP_PROC::TRANS_LIST) ;			
	
   addFieldDetails(ifds::InvSummId,          IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );
   addFieldDetails(ifds::InvDetlId,          IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );
   addFieldDetails(ifds::DeductDesc,         IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );
   addFieldDetails(ifds::LSIFCode,           IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );
   addFieldDetails(ifds::ChargedAmount,      IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );
   addFieldDetails(ifds::DeductUnits,        IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );
   addFieldDetails(ifds::BasedOn,            IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );
   addFieldDetails(ifds::BasedOnValue,       IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );
   addFieldDetails(ifds::CalculatedAmount,   IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );

   addFieldDetails(ifds::InvDetlDeduction,   IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST );
   
   
}

//******************************************************************************
InvDetlDeductionProcess::~InvDetlDeductionProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;   
}

//************************************************************************************
SEVERITY InvDetlDeductionProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      processParameters();    
      
      DString dstrFundCode, dstrClassCode, dstrNumEntry, allFundsMode = I_("N"); // all blank/ irrelevant values in this case
      TransactionList* pTransactionList;

      DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
   
      pTransactionList = new TransactionList( *pDSTCWorkSession );
      if (pTransactionList->init ( _dstrAccount, dstrFundCode, dstrClassCode, 
                                 dstrNumEntry, allFundsMode, _dstrTransId ) <= WARNING &&
               pTransactionList != NULL )
      {
         _pTransList = pTransactionList;
      }

      const BFDataGroupId& idDataGroup = getDataGroupId();

      InvDetlDeductionList* pInvDetlDeductionList;

      pInvDetlDeductionList = new InvDetlDeductionList ( *pDSTCWorkSession);

      if (pInvDetlDeductionList->init(_dstrTransId, idDataGroup) <= WARNING &&
                              pInvDetlDeductionList != NULL )
      {
         _pInvDetlDeductList = pInvDetlDeductionList;
      }
         				
   }

   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }

   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN InvDetlDeductionProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      
      setParameter( INV_DETL_DEDUCT::ACCOUNT_NUMBER,     _dstrAccount );
		setParameter( INV_DETL_DEDUCT::SHAREHOLDER_NUMBER, _dstrShareholder );		    
      setParameter( INV_DETL_DEDUCT::TRANS_ID,           _dstrTransId );		    

      rtn = invokeCommand( this, 
			                  CMD_GUI_INVENTORY_DETAIL_DEDUCTION, 
                           PROC_NO_TYPE, 
									isModal(), 
									&_rpChildGI);
      
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
bool InvDetlDeductionProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  
	// This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      if( processParameters() <= WARNING )
      {
         if( isValidModelessInterface( _rpChildGI ) )
         {  
				// Only if child still exists            
				setContainer( IFASTBP_PROC::TRANS_LIST, NULL );
            			
				setParameter( INV_DETL_DEDUCT::ACCOUNT_NUMBER,     _dstrAccount );
				setParameter( INV_DETL_DEDUCT::SHAREHOLDER_NUMBER, _dstrShareholder );
            setParameter( INV_DETL_DEDUCT::TRANS_ID,           _dstrTransId );
				
            bRtn = _rpChildGI->refresh( this, I_("ReloadParams" ) );
            bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return bRtn;
}

//******************************************************************************
bool InvDetlDeductionProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_INVENTORY_DETAIL_DEDUCTION;
   return true;
}

//******************************************************************************
SEVERITY InvDetlDeductionProcess::performSearch(GenericInterface *rpGI, 
   const BFContainerId &idSearch, E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));

   try
   {
      if( _pInvDetlDeductList != NULL )
      {
         _pInvDetlDeductList->getMore();
      }		
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool InvDetlDeductionProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
															  const BFContainerId &idSearch )
{
   return (rpGICaller == NULL || _pInvDetlDeductList == NULL) ? false : _pInvDetlDeductList->doMoreRecordsExist();		
}

//******************************************************************************
void *InvDetlDeductionProcess::getPtrForContainer( const BFContainerId& idContainer,
																		    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   
	void *ptr = NULL;
      
   try
   {      		
		if ( IFASTBP_PROC::TRANS_LIST == idContainer )
		{			
			ptr = _pTransList;
		}
      else if (IFASTBP_PROC::INVENTORY_DETAIL_DEDUCTION_LIST == idContainer)
      {
         ptr = _pInvDetlDeductList;
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
SEVERITY InvDetlDeductionProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter( INV_DETL_DEDUCT::ACCOUNT_NUMBER,     _dstrAccount );
	getParameter( INV_DETL_DEDUCT::SHAREHOLDER_NUMBER, _dstrShareholder );
   getParameter( INV_DETL_DEDUCT::TRANS_ID,           _dstrTransId );
	
	_dstrAccount.stripAll();
	_dstrShareholder.stripAll();
   _dstrTransId.stripAll();
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool InvDetlDeductionProcess::doOk( GenericInterface *rpGICaller )
{		   
   return(true);
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/InvDetlDeductionProcess.cpp-arc  $
// 
//    Rev 1.2   Feb 21 2005 15:10:10   aguilaam
// PET1198_FN01: LSIF ReasonCode enhancement
// 
//    Rev 1.1   Feb 17 2005 13:14:46   aguilaam
// PET1198_FN01: LSIF Reason Code enhancement. 
// 
//    Rev 1.0   Jan 28 2005 14:33:42   aguilaam
// Initial revision.
// 
