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
//    Copyright 2003 International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TransSettLocProcess.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransSettLocProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "transsettlocprocess.hpp"
#include "transsettlocprocessincludes.h"

#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\PendingTradeDetails.hpp>
#include <ifastcbo\PendingTradeList.hpp>
#include <ifastcbo\Trade.hpp>
#include <ifastcbo\TransactionDetails.hpp>
#include <ifastcbo\TransactionList.hpp>
#include <ifastcbo\TransSettleLoc.hpp>
#include <ifastcbo\WorksessionTradesList.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SETTLEMENT_LOCATION_TRADE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SETTLEMENT_LOCATION_TRADE;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TransSettLocProcess > processCreator( CMD_BPROC_SETTLEMENT_LOCATION_TRADE );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
	extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "TransSettLocProcess" );  
}

//******************************************************************************
//              Public Methods
//******************************************************************************
TransSettLocProcess::TransSettLocProcess( GenericInterfaceContainer* pGIC, 
													   GenericInterface* pGIParent, 
														const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, _pFromTransSettleLoc(NULL )
, _pToTransSettleLoc( NULL )
,_blFromTransSettleLocCreated( false )
,_blToTransSettleLocCreated( false )
,_blUpdateableLocation( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

	//Add containers
	addContainer( IFASTBP_PROC::ORIGINAL_TRADE_CBO,                 false, BF::NullContainerId,              false,  I_("Trade") );   
   addContainer( IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, false, IFASTBP_PROC::ORIGINAL_TRADE_CBO, true,   I_("FromTransSettLoc") );   
	addContainer( IFASTBP_PROC::FROM_ACCOUNT_CBO,                   false, IFASTBP_PROC::ORIGINAL_TRADE_CBO, false,  I_("FromMFAccount") );   
	addContainer( IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO,   false, IFASTBP_PROC::ORIGINAL_TRADE_CBO, true,   I_("ToTransSettLoc") );   
	addContainer( IFASTBP_PROC::TO_ACCOUNT_CBO,                     false, IFASTBP_PROC::ORIGINAL_TRADE_CBO, false,  I_("ToMFAccount") );   

	// Add fields
	addFieldDetails( ifds::TransNum,              IFASTBP_PROC::ORIGINAL_TRADE_CBO );
	addFieldDetails( ifds::TradesTransType,       IFASTBP_PROC::ORIGINAL_TRADE_CBO );

	addFieldDetails( ifds::FrSettlLocCode,        IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::FrDeliveryTo,          IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::FrSettlLocDescription, IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::FrInFavourOf,          IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::FrForAccount,          IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::FrClearingMethod,      IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
    //From Fields
    addFieldDetails( ifds::FrCashMsgType,         IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::FrIntermediaryBank,    IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::FrReceivingBank,       IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::FrBeneficiary,         IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::FrSpecialInstructions, IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::FrSettlementAccount,   IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::FrInternalSettlementAccount, IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO);

	addFieldDetails( ifds::ToSettlLocCode,        IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::ToDeliveryTo,          IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::ToSettlLocDescription, IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::ToInFavourOf,          IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::ToForAccount,          IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
	addFieldDetails( ifds::ToClearingMethod,      IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
    //To Fields
    addFieldDetails( ifds::ToCashMsgType,         IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::ToIntermediaryBank,    IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::ToReceivingBank,       IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::ToBeneficiary,         IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::ToSpecialInstructions, IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::ToSettlementAccount,   IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
    addFieldDetails( ifds::ToInternalSettlementAccount, IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );

}

//******************************************************************************
TransSettLocProcess::~TransSettLocProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

	if ( _blFromTransSettleLocCreated && NULL != _pFromTransSettleLoc )
	{
		delete _pFromTransSettleLoc;
		_pFromTransSettleLoc = NULL;
		_blFromTransSettleLocCreated = false;
	}

	if ( _blToTransSettleLocCreated && NULL != _pToTransSettleLoc )
	{
		delete _pToTransSettleLoc;
		_pToTransSettleLoc = NULL;
		_blToTransSettleLocCreated = false;			
	}
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY TransSettLocProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   
   try
   {				
		const BFDataGroupId& idDataGroup = getDataGroupId();

		// for Transaction History only, both Pending and History		
		getParameter( TRANS_SETTLEMENT_LOCATION::ACCOUNT,         _dstrAccount );		
      // for all cases
		getParameter( TRANS_SETTLEMENT_LOCATION::FROM_SCREEN,     _dstrFromScreen );
		// for Transaction History only, indicating if Pending and History
		getParameter( TRANS_SETTLEMENT_LOCATION::PENDING_HISTORY, _dstrPendingHist );
		// for all cases
		getParameter( TRANS_SETTLEMENT_LOCATION::MAIN_LIST_KEY,   _dstrMainListKey );		
		
		DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
		BFAbstractCBO* pTrade = dynamic_cast<BFAbstractCBO*>( getCBOItem( IFASTBP_PROC::ORIGINAL_TRADE_CBO, idDataGroup ) );
		if ( NULL != pDSTCWorkSession && 
			  NULL != pTrade )
		{											
			// From side
			if ( 0 != _dstrFromAccount.stripAll().length() )
			{
				MFAccount *pFromAccount = dynamic_cast<MFAccount*>( getCBOItem( IFASTBP_PROC::FROM_ACCOUNT_CBO, idDataGroup ) );				
				if ( NULL != pFromAccount && 
					  pFromAccount->isClearingAcount( idDataGroup ) &&
					  pFromAccount->hasSettlementLocation( idDataGroup ) )
				{								
					_pFromTransSettleLoc = new TransSettleLoc( *pDSTCWorkSession );
					_blFromTransSettleLocCreated = true;				
					if ( _pFromTransSettleLoc->init( true, 																																				
																pTrade,
																_dstrFromAccount,
																_dstrTransType,
																_blUpdateableLocation,
																idDataGroup ) <= WARNING )
					{																		   
						_dstrFromClearingAccount = _dstrFromAccount;
					}			
					else		
					{
						delete _pFromTransSettleLoc;
						_pFromTransSettleLoc = NULL;	
						_blFromTransSettleLocCreated = false;				
					}					
				}									
			}				
				
			// 'To' side for Transfers			
			DString dstrApplicableTransType = I_( "AFTR,XR,EO,EI,ED,PW,TR,TO,TI" );			
			if ( dstrApplicableTransType.find( _dstrTransType.stripAll() ) != DString::npos &&				
				  0 != _dstrAccountTo.stripAll().length() )
			{
				MFAccount *pToAccount = dynamic_cast<MFAccount*>( getCBOItem( IFASTBP_PROC::TO_ACCOUNT_CBO, idDataGroup ) );			
				if ( NULL != pToAccount &&
				     pToAccount->isClearingAcount( idDataGroup ) &&
					  pToAccount->hasSettlementLocation( idDataGroup )	)
				{
					_pToTransSettleLoc = new TransSettleLoc( *pDSTCWorkSession );
					_blToTransSettleLocCreated = true;			
					if ( _pToTransSettleLoc->init( false, 																		 
															 pTrade,
															 _dstrAccountTo,
															 _dstrTransType,
															 _blUpdateableLocation,	
															 idDataGroup ) <= WARNING )
					{													   
						_dstrToClearingAccount = _dstrAccountTo;
					}			
					else				
					{						
						delete _pToTransSettleLoc;
						_pToTransSettleLoc = NULL;
						_blToTransSettleLocCreated = false;			
					}															
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
E_COMMANDRETURN TransSettLocProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   
	try
   {
		setParameter( TRANS_SETTLEMENT_LOCATION::FROM_SCREEN,           _dstrFromScreen );
		setParameter( TRANS_SETTLEMENT_LOCATION::PENDING_HISTORY,       _dstrPendingHist );
		setParameter( TRANS_SETTLEMENT_LOCATION::FROM_CLEARING_ACCOUNT, _dstrFromClearingAccount );
		setParameter( TRANS_SETTLEMENT_LOCATION::TO_CLEARING_ACCOUNT,   _dstrToClearingAccount );

      rtn = invokeCommand( this, 
			                  CMD_GUI_SETTLEMENT_LOCATION_TRADE, 
									getProcessType(),
                           isModal(), 
									&_rpChildGI );
   }
   catch( ConditionException &ce )
   {      
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {    
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   
	return(rtn);
}

//******************************************************************************
void *TransSettLocProcess::getPtrForContainer( const BFContainerId& idContainer, 
															  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;

   try
   {
		const BFDataGroupId& idDataGroup = getDataGroupId();
		DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

		if ( idContainer == IFASTBP_PROC::ORIGINAL_TRADE_CBO )
		{								
			if ( NULL != pDSTCWorkSession )
			{			
				// If new Trade
				if ( I_( "TradesDlg" ) == _dstrFromScreen )
				{
					WorksessionTradesList *pTradesList = NULL;
					if ( pDSTCWorkSession->getTradesList( pTradesList, idDataGroup) <= WARNING &&
						  NULL != pTradesList )
					{
						BFObjIter iterTradesList( *pTradesList, 
								                    idDataGroup, 
														  false, 
												        BFObjIter::ITERTYPE::NON_DELETED );

						iterTradesList.begin();
						if (iterTradesList.positionByKey( _dstrMainListKey ) )
						{
							ptr = dynamic_cast<Trade*>( iterTradesList.getObject() );	

							iterTradesList.getObject()->getField( ifds::TradesTransType, _dstrTransType,   idDataGroup );
							iterTradesList.getObject()->getField( ifds::AccountNum,      _dstrFromAccount, idDataGroup );
							iterTradesList.getObject()->getField( ifds::AccountTo,       _dstrAccountTo,   idDataGroup );
							
							_blUpdateableLocation = true;
						}
					}
				}
				// else if Pending Trade
				else if ( I_( "TransactionHistoryDlg" ) == _dstrFromScreen &&
					       I_( "Y" ) == _dstrPendingHist )
				{
					MFAccount *pMFAccount = NULL;
					if ( pDSTCWorkSession->getMFAccount( idDataGroup, 
						                                  _dstrAccount, 
																	 pMFAccount ) <= WARNING &&
						  NULL != pMFAccount )
					{
						PendingTradeList *pPendingTradeList = NULL;
						if ( pMFAccount->getPendingTradesList( pPendingTradeList, 
							                                    idDataGroup ) <= WARNING &&
                       NULL != pPendingTradeList )
						{							
							BFObjIter iterPendingTradesList( *pPendingTradeList, 
								                              idDataGroup, 
														            false, 
												                  BFObjIter::ITERTYPE::NON_DELETED );

							iterPendingTradesList.begin();
							if (iterPendingTradesList.positionByKey( _dstrMainListKey ) )
							{																												
								PendingTradeDetails *pPendingTradeDetails = static_cast<PendingTradeDetails*>(iterPendingTradesList.getObject());								
   							pPendingTradeList->getItem( _dstrMainListKey, idDataGroup );								
								if ( NULL != pPendingTradeDetails )
								{
									ptr = pPendingTradeDetails;

									pPendingTradeDetails->getField( ifds::TransType, _dstrTransType, idDataGroup );
									_dstrFromAccount = _dstrAccount;
									pPendingTradeDetails->getField( ifds::AccountTo, _dstrAccountTo, idDataGroup );

									_blUpdateableLocation = false;
								}
							}
						}
					}
					
				}
				// else if a Transaction History 
				else if ( I_( "TransactionHistoryDlg" ) == _dstrFromScreen &&
					       I_( "N" ) == _dstrPendingHist )
				{			
					MFAccount *pMFAccount = NULL;
					if ( pDSTCWorkSession->getMFAccount( idDataGroup, 
						                                  _dstrAccount, 
																	 pMFAccount ) <= WARNING &&
						  NULL != pMFAccount )
					{
						TransactionList *pTransactionHistoryList = NULL;						
						pMFAccount->getLastActiveTransactionHistoryList ( pTransactionHistoryList, 
							                                               idDataGroup );
						if ( NULL != pTransactionHistoryList )
						{
							TransactionDetails *pTransactionHistoryDetails = NULL; 
							pTransactionHistoryDetails = pTransactionHistoryList->getItem( _dstrMainListKey, idDataGroup );
							if ( NULL != pTransactionHistoryDetails )
							{
								ptr = pTransactionHistoryDetails;	
	
								pTransactionHistoryDetails->getField( ifds::TransType, _dstrTransType, idDataGroup );
								DString dstrAccountTo;
								pTransactionHistoryDetails->getField( ifds::TfrAcct,   dstrAccountTo, idDataGroup );

								if ( I_( "TI" ) == _dstrTransType )
								{
									_dstrFromAccount = dstrAccountTo;
									_dstrAccountTo   = _dstrAccount;
								}
								else  // TO, ED, PW 								
								{
									_dstrFromAccount = _dstrAccount;
									_dstrAccountTo   = dstrAccountTo;
								}

								_blUpdateableLocation = false;
							}
						}
					}
				}				
			}
		}
		else if( idContainer == IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO )
      {         			
			ptr = _pFromTransSettleLoc;
		}   
		else if( idContainer == IFASTBP_PROC::FROM_ACCOUNT_CBO )
      {    
			BFAbstractCBO* pTrade = dynamic_cast<BFAbstractCBO*>( getCBOItem( IFASTBP_PROC::ORIGINAL_TRADE_CBO, idDataGroup ) );		
			if ( NULL != pTrade )
			{				
				if ( NULL != pDSTCWorkSession && 0 != _dstrFromAccount.stripAll().length() )
				{								
					MFAccount *pMFAccount = NULL;						
					if ( pDSTCWorkSession->getMFAccount( idDataGroup, 
						                                  _dstrFromAccount, 
																	 pMFAccount, 
																	 I_("N"), 
																	 NULL_STRING, 
																	 true, 
																	 true) <= WARNING &&
					     NULL != pMFAccount )
					{
						ptr = pMFAccount;
					}					
				}
			}
		}   
		else if( idContainer == IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO )
      {         			
			ptr = _pToTransSettleLoc;
		}      
		else if( idContainer == IFASTBP_PROC::TO_ACCOUNT_CBO )
      {    
			BFAbstractCBO* pTrade = dynamic_cast<BFAbstractCBO*>( getCBOItem( IFASTBP_PROC::ORIGINAL_TRADE_CBO, idDataGroup ) );		
			if ( NULL != pTrade )
			{				
				{								
					MFAccount *pMFAccount = NULL;					
					if ( pDSTCWorkSession->getMFAccount( idDataGroup, 
						                                  _dstrAccountTo, 
																	 pMFAccount, 
																	 I_("N"), 
																	 NULL_STRING, 
																	 true, 
																	 true) <= WARNING &&
					     NULL != pMFAccount )
					{
						ptr = pMFAccount;
					}
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
bool TransSettLocProcess::doModelessChildComplete( const Command &cmd )
{
// End when GUI ends   
   return( cmd.getKey() == CMD_GUI_SETTLEMENT_LOCATION_TRADE );
}

//******************************************************************************
bool TransSettLocProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{      
	// This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

	bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface ( _rpChildGI ) );  
		
		// for Transaction History only, both Pending and History		
		getParameter( TRANS_SETTLEMENT_LOCATION::ACCOUNT,         _dstrAccount );		
      // for all cases
		getParameter( TRANS_SETTLEMENT_LOCATION::FROM_SCREEN,     _dstrFromScreen );
		// for Transaction History only, indicating if Pending and History
		getParameter( TRANS_SETTLEMENT_LOCATION::PENDING_HISTORY, _dstrPendingHist );
		// for all cases
		getParameter( TRANS_SETTLEMENT_LOCATION::MAIN_LIST_KEY,   _dstrMainListKey );		
      
      // reset all containers,
      setContainer (IFASTBP_PROC::TO_ACCOUNT_CBO,                     NULL);
      setContainer (IFASTBP_PROC::FROM_ACCOUNT_CBO,                   NULL);
      setContainer (IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, NULL);
      setContainer (IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO,   NULL);
      setContainer (IFASTBP_PROC::ORIGINAL_TRADE_CBO,                 NULL);
		      
		if ( isValidModelessInterface ( _rpChildGI ) )
      {  // Only if child still exists
			bRtn = _rpChildGI->refresh (this, NULL);
         bRtn = _rpChildGI->modelessSetFocus (rpGICaller);
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

   return(bRtn);
}

//******************************************************************************
bool TransSettLocProcess::doOk(GenericInterface *rpGICaller)
{  	
	MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_( "doOk" ) );

	bool blReturnFlag = true;

	// The update should happen only for new Trade (i.e. when from TradesDlg)
	if ( I_( "TradesDlg" ) == _dstrFromScreen )
	{		
		const BFDataGroupId& idDataGroup = getDataGroupId();
		Trade* pTrade = dynamic_cast<Trade*>( getCBOItem( IFASTBP_PROC::ORIGINAL_TRADE_CBO, idDataGroup ) );		

		if ( NULL != pTrade )
		{			
			if ( NULL != _pFromTransSettleLoc &&
				  _blFromTransSettleLocCreated )
			{								
				DString dstrValue;
				_pFromTransSettleLoc ->getField( ifds::FrSettlLocCode, dstrValue, idDataGroup );
				pTrade->setField( ifds::FrSettlLocCode, dstrValue, idDataGroup );				

				dstrValue = I_( "" );
				_pFromTransSettleLoc ->getField( ifds::FrClearingMethod, dstrValue, idDataGroup );
				pTrade->setField( ifds::FrClearingMethod, dstrValue, idDataGroup );

				dstrValue = I_( "" );
				_pFromTransSettleLoc ->getField( ifds::FrDeliveryTo, dstrValue, idDataGroup );
				pTrade->setField( ifds::FrDeliveryTo, dstrValue, idDataGroup );									
				
				dstrValue = I_( "" );
				_pFromTransSettleLoc ->getField( ifds::FrInFavourOf, dstrValue, idDataGroup );
				pTrade->setField( ifds::FrInFavourOf, dstrValue, idDataGroup );
				
				dstrValue = I_( "" );
				_pFromTransSettleLoc ->getField( ifds::FrForAccount, dstrValue, idDataGroup );
				pTrade->setField( ifds::FrForAccount, dstrValue, idDataGroup );		
			}

			if ( NULL != _pToTransSettleLoc && 
				  _blToTransSettleLocCreated )
			{
				DString dstrValue;
				_pToTransSettleLoc ->getField( ifds::ToSettlLocCode, dstrValue, idDataGroup );
				pTrade->setField( ifds::ToSettlLocCode, dstrValue, idDataGroup );

				dstrValue = I_( "" );
				_pToTransSettleLoc ->getField( ifds::ToClearingMethod, dstrValue, idDataGroup );
				pTrade->setField( ifds::ToClearingMethod, dstrValue, idDataGroup );

				dstrValue = I_( "" );
				_pToTransSettleLoc ->getField( ifds::ToDeliveryTo,    dstrValue, idDataGroup );
				pTrade->setField( ifds::ToDeliveryTo, dstrValue, idDataGroup );			
				
				dstrValue = I_( "" );
				_pToTransSettleLoc ->getField( ifds::ToInFavourOf, dstrValue, idDataGroup );
				pTrade->setField( ifds::ToInFavourOf, dstrValue, idDataGroup );
				
				dstrValue = I_( "" );
				_pToTransSettleLoc ->getField( ifds::ToForAccount, dstrValue, idDataGroup );
				pTrade->setField( ifds::ToForAccount, dstrValue, idDataGroup );		
			}										
			
			SEVERITY sevFrom = NO_SEVERITY, sevTo = NO_SEVERITY;
	  	   if ( _blFromTransSettleLocCreated && NULL != _pFromTransSettleLoc )
			{
				 sevFrom = _pFromTransSettleLoc->validateAll( idDataGroup );							
			}

			if ( _blToTransSettleLocCreated && NULL != _pToTransSettleLoc )
			{			
				sevTo = _pToTransSettleLoc->validateAll( idDataGroup ); 		
			}

			if ( sevFrom > WARNING || sevTo > WARNING )
				blReturnFlag = false;					
		}		
	}

   return blReturnFlag;
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/TransSettLocProcess.cpp-arc  $
// 
//    Rev 1.7   Feb 02 2004 16:12:24   VADEANUM
// PTS 10026748 - OK button not working in Release mode.
// 
//    Rev 1.6   Jan 22 2004 09:46:26   VADEANUM
// PTS 10026113 - Error sign showing for any field that is not valid.
// 
//    Rev 1.5   Jan 06 2004 16:53:04   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support - fixed wrong bracket.
// 
//    Rev 1.4   Jan 05 2004 15:36:10   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support.
// 
//    Rev 1.3   Dec 08 2003 12:34:52   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support.
// 
//    Rev 1.2   Nov 27 2003 13:23:50   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support.
// 
//    Rev 1.1   Nov 25 2003 11:53:42   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support.
// 
//    Rev 1.0   Nov 10 2003 15:23:54   VADEANUM
// Initial revision.
//
