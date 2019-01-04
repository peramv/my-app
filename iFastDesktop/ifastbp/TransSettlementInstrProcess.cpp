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
// ^FILE   : TransSettlementInstrProcess.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransSettlementInstrProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "transSettlementInstrprocess.hpp"
#include "transSettlementInstrprocessincludes.h"

#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\PendingTradeDetails.hpp>
#include <ifastcbo\PendingTradeList.hpp>
#include <ifastcbo\Trade.hpp>
#include <ifastcbo\TransactionDetails.hpp>
#include <ifastcbo\TransactionList.hpp>
#include <ifastcbo\TransSettlementInstr.hpp>
#include <ifastcbo\WorksessionTradesList.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SETTLEMENT_LOCATION_TRADE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SETTLEMENT_LOCATION_TRADE;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TransSettlementInstrProcess > processCreator( CMD_BPROC_SETTLEMENT_LOCATION_TRADE );

namespace CND
{   // Conditions used
    extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
    extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace
{
    // Trace literals
    const I_CHAR *CLASSNAME          = I_( "TransSettlementInstrProcess" );
    const I_CHAR *TRANSFER_IN_LIKE   = I_( "TI,TI04,TI08" );
    const I_CHAR *TRANSFER_OUT_LIKE  = I_( "TO,TO04,TO08" );
    const I_CHAR *PURCHASE_LIKE      = I_( "ED" );
    const I_CHAR *REDEMPTION_LIKE    = I_( "PW" );
}

namespace TRADE_VALIDATION_GROUP
{
   //Clearning method
   extern CLASS_IMPORT const long SETTLE_LOCATION; 
}

namespace TRANS_SETTLEMENT_LOCATION
{   
    //parameters
    extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT               = I_("FromAccount");	
    // what screen launched this process   
    extern IFASTBP_LINKAGE const I_CHAR * const FROM_SCREEN           = I_("FromScreen");
    // if it's from the Transaction History screen, is it History or Pending mode?
    // Y for Pending, N for History, blank if not from Transaction History	
    extern IFASTBP_LINKAGE const I_CHAR * const PENDING_HISTORY       = I_("PendingHistory");
    // List Item Key	
    extern IFASTBP_LINKAGE const I_CHAR * const MAIN_LIST_KEY         = I_("MainListKey");
    extern IFASTBP_LINKAGE const I_CHAR * const FROM_CLEARING_ACCOUNT = I_("FromClearingAccount");
    extern IFASTBP_LINKAGE const I_CHAR * const TO_CLEARING_ACCOUNT   = I_("ToClearingAccount");
    extern IFASTBP_LINKAGE const I_CHAR * const SIDE                  = I_("Side");
}

//******************************************************************************
//              Public Methods
//******************************************************************************
TransSettlementInstrProcess::TransSettlementInstrProcess( GenericInterfaceContainer* pGIC, 
                                                          GenericInterface* pGIParent, 
                                                          const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
//, _pFromTransSettleLoc(NULL )
//, _pToTransSettleLoc( NULL )
//,_blFromTransSettleLocCreated( false )
//,_blToTransSettleLocCreated( false )
,_blUpdateableLocation( false )
{
    TRACE_CONSTRUCTOR( CLASSNAME, "" );

    //Add containers
    addContainer( IFASTBP_PROC::ORIGINAL_TRADE_CBO,                 false, BF::NullContainerId,              true,  I_("Trade") );   
    /*addContainer( IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, false, IFASTBP_PROC::ORIGINAL_TRADE_CBO, true,   I_("FromTransSettlementInstr") );   */
    addContainer( IFASTBP_PROC::FROM_ACCOUNT_CBO,                   false, IFASTBP_PROC::ORIGINAL_TRADE_CBO, false,  I_("FromMFAccount") );   
    /*addContainer( IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO,   false, IFASTBP_PROC::ORIGINAL_TRADE_CBO, true,   I_("ToTransSettlementInstr") );   */
    addContainer( IFASTBP_PROC::TO_ACCOUNT_CBO,                     false, IFASTBP_PROC::ORIGINAL_TRADE_CBO, false,  I_("ToMFAccount") );   

    // Add fields
    addFieldDetails( ifds::TransNum,              IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::TradesTransType,       IFASTBP_PROC::ORIGINAL_TRADE_CBO );

    addFieldDetails( ifds::FrSettlLocCode,        IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrDeliveryTo,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrSettlLocDescription, IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrInFavourOf,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrForAccount,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrClearingMethod,      IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrSettlInstrCode,      IFASTBP_PROC::ORIGINAL_TRADE_CBO );
	addFieldDetails( ifds::FrCSDLocation,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );
	addFieldDetails( ifds::FrCSDAcctNum,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );

    addFieldDetails( ifds::ToSettlLocCode,        IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToDeliveryTo,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToSettlLocDescription, IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToInFavourOf,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToForAccount,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToClearingMethod,      IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToSettlInstrCode,      IFASTBP_PROC::ORIGINAL_TRADE_CBO );
	addFieldDetails( ifds::ToCSDLocation,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );
	addFieldDetails( ifds::ToCSDAcctNum,          IFASTBP_PROC::ORIGINAL_TRADE_CBO );

    //From Fields
    addFieldDetails( ifds::FrCashMsgType,                   IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrIntermediaryBank,              IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrReceivingBank,                 IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrBeneficiary,                   IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrSpecialInstructions,           IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrSettlementAccount,             IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::FrInternalSettlementAccount,     IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    //To Fields
    addFieldDetails( ifds::ToCashMsgType,                   IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToIntermediaryBank,              IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToReceivingBank,                 IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToBeneficiary,                   IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToSpecialInstructions,           IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToSettlementAccount,             IFASTBP_PROC::ORIGINAL_TRADE_CBO );
    addFieldDetails( ifds::ToInternalSettlementAccount,     IFASTBP_PROC::ORIGINAL_TRADE_CBO );

    addFieldDetails (IsClearingAcct,              IFASTBP_PROC::FROM_ACCOUNT_CBO, SUBCLASS_PROCESS );  
    addFieldDetails (IsClearingAcct,              IFASTBP_PROC::TO_ACCOUNT_CBO, SUBCLASS_PROCESS   );  
}

//******************************************************************************
TransSettlementInstrProcess::~TransSettlementInstrProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

/*	if ( _blFromTransSettleLocCreated && NULL != _pFromTransSettleLoc )
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
*/
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY TransSettlementInstrProcess::doInit()
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
        getParameter( TRANS_SETTLEMENT_LOCATION::SIDE,            _dstrSide );		
		
        //just to force initializing the container
        getCBOItem (IFASTBP_PROC::ORIGINAL_TRADE_CBO, idDataGroup);
        getCBOItem (IFASTBP_PROC::FROM_ACCOUNT_CBO, idDataGroup);
        getCBOItem (IFASTBP_PROC::TO_ACCOUNT_CBO, idDataGroup);

      /*
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
					_pFromTransSettleLoc = new TransSettlementInstr( *pDSTCWorkSession );
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
				  0 != _dstrToAccount.stripAll().length() )
			{
				MFAccount *pToAccount = dynamic_cast<MFAccount*>( getCBOItem( IFASTBP_PROC::TO_ACCOUNT_CBO, idDataGroup ) );			
				if ( NULL != pToAccount &&
				     pToAccount->isClearingAcount( idDataGroup ) &&
					  pToAccount->hasSettlementLocation( idDataGroup )	)
				{
					_pToTransSettleLoc = new TransSettlementInstr( *pDSTCWorkSession );
					_blToTransSettleLocCreated = true;			
					if ( _pToTransSettleLoc->init( false, 																		 
															 pTrade,
															 _dstrToAccount,
															 _dstrTransType,
															 _blUpdateableLocation,	
															 idDataGroup ) <= WARNING )
					{													   
						_dstrToClearingAccount = _dstrToAccount;
					}			
					else				
					{						
						delete _pToTransSettleLoc;
						_pToTransSettleLoc = NULL;
						_blToTransSettleLocCreated = false;			
					}															
				}						
			}		
		}*/
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
E_COMMANDRETURN TransSettlementInstrProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   
	try
   {
      setParameter( TRANS_SETTLEMENT_LOCATION::FROM_SCREEN,           _dstrFromScreen  );
      setParameter( TRANS_SETTLEMENT_LOCATION::PENDING_HISTORY,       _dstrPendingHist );
      setParameter( TRANS_SETTLEMENT_LOCATION::FROM_CLEARING_ACCOUNT, _dstrFromAccount );
      setParameter( TRANS_SETTLEMENT_LOCATION::TO_CLEARING_ACCOUNT,   _dstrToAccount   );
      setParameter( TRANS_SETTLEMENT_LOCATION::SIDE,                  _dstrSide        );

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
void *TransSettlementInstrProcess::getPtrForContainer( const BFContainerId& idContainer, 
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
							iterTradesList.getObject()->getField( ifds::AccountTo,       _dstrToAccount,   idDataGroup );
							
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
								PendingTradeDetails *pPendingTradeDetails =  
                           dynamic_cast <PendingTradeDetails*>(iterPendingTradesList.getObject());								
   							pPendingTradeList->getItem( _dstrMainListKey, idDataGroup );								
								if ( NULL != pPendingTradeDetails )
								{
									ptr = pPendingTradeDetails;

									pPendingTradeDetails->getField( ifds::TransType, _dstrTransType, idDataGroup );
									_dstrFromAccount = _dstrAccount;
									pPendingTradeDetails->getField( ifds::AccountTo, _dstrToAccount, idDataGroup );

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

								if ( DSTCommonFunctions::codeInList( _dstrTransType,TRANSFER_IN_LIKE ) ) // TI,TI04,TI08
								{
									_dstrFromAccount = dstrAccountTo;
									_dstrToAccount   = _dstrAccount;
								}
								else  // TO, ED, PW 								
								{
									_dstrFromAccount = _dstrAccount;
									_dstrToAccount   = dstrAccountTo;
								}

								_blUpdateableLocation = false;
							}
						}
					}
				}				
			}
		}
		/*else if( idContainer == IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO )
      {         			
			ptr = _pFromTransSettleLoc;
		}*/   
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
		/*else if( idContainer == IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO )
      {         			
			ptr = _pToTransSettleLoc;
		}*/      
		else if( idContainer == IFASTBP_PROC::TO_ACCOUNT_CBO )
      {    
			BFAbstractCBO* pTrade = dynamic_cast<BFAbstractCBO*>( getCBOItem( IFASTBP_PROC::ORIGINAL_TRADE_CBO, idDataGroup ) );		
			if ( NULL != pTrade )
			{				
				{								
					MFAccount *pMFAccount = NULL;					
					if ( pDSTCWorkSession->getMFAccount( idDataGroup, 
						                                  _dstrToAccount, 
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
bool TransSettlementInstrProcess::doModelessChildComplete( const Command &cmd )
{
// End when GUI ends   
   return( cmd.getKey() == CMD_GUI_SETTLEMENT_LOCATION_TRADE );
}

//******************************************************************************
bool TransSettlementInstrProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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
//      setContainer (IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, NULL);
//      setContainer (IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO,   NULL);
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
void TransSettlementInstrProcess::doGetField ( const GenericInterface *rpGICaller,
                                               const BFContainerId &idContainer,
                                               const BFFieldId &idField,
                                               const BFDataGroupId &idDataGroup, 
                                               DString &strValueOut,
                                               bool bFormatted
                                             ) const
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doGetField")
                         );

   strValueOut = NULL_STRING;
   if ( idContainer == IFASTBP_PROC::FROM_ACCOUNT_CBO ||
        idContainer == IFASTBP_PROC::TO_ACCOUNT_CBO
      )
   {
      if (idField == IsClearingAcct)
      {
         strValueOut = I_("N");
         BFAbstractCBO *rpPtrMFAccount = const_cast<TransSettlementInstrProcess*> (this)->
                                       getCBOItem ( idContainer, 
                                                      idDataGroup
                                                   );
         if (rpPtrMFAccount)
         {
            MFAccount *pMFAccount = dynamic_cast <MFAccount*> (rpPtrMFAccount);
            strValueOut = pMFAccount->isClearingAcount (idDataGroup) &&
                          pMFAccount->hasSettlementLocation (idDataGroup) ? I_("Y") : I_("N");
         }
      }
   }
}

//******************************************************************************
bool TransSettlementInstrProcess::doSend ( GenericInterface *rpGICaller,
                                           const I_CHAR  *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSEND);

   DString message (szMessage);
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   Trade *pTrade = 
      dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::ORIGINAL_TRADE_CBO, idDataGroup));
   
   //reset settle location values, only for new trades
   ////dont know why it should assert when the Settl Instr is called from trans history using the settl instr button?
   if (I_( "TradesDlg" ) == _dstrFromScreen && pTrade) 
   {
      if (message == I_("Cancel")) 
      {
         DString IsClearingAcctFrom,
            IsClearingAcctTo;

         assert (pTrade);
         getField ( this,
                  IFASTBP_PROC::FROM_ACCOUNT_CBO,
                  IsClearingAcct,
                  IsClearingAcctFrom,
                  false);
         getField ( this,
                  IFASTBP_PROC::TO_ACCOUNT_CBO,
                  IsClearingAcct,
                  IsClearingAcctTo,
                  false);
         if (IsClearingAcctFrom == I_("Y"))
         {
            pTrade->resetSettleLoc( idDataGroup );
         }
         if (IsClearingAcctTo == I_("Y"))
         {
            pTrade->resetSettleLoc( idDataGroup, false ); //to side
         }
      }
      else if (message == I_("Validate"))
      {
         pTrade->validateAll (idDataGroup, TRADE_VALIDATION_GROUP::SETTLE_LOCATION);
      }
   }
   // called from the tarns history do nothing and don't assert.
   else if (I_( "TransactionHistoryDlg" ) == _dstrFromScreen ) 
   {
     return GETCURRENTHIGHESTSEVERITY() <= WARNING;
   }
   else
   {
      assert (0);
   }
   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//*****************************************************************************
SEVERITY TransSettlementInstrProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
                                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOVALIDATEALL);
   Trade *pTrade = 
      dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::ORIGINAL_TRADE_CBO, idDataGroup));
   if (pTrade)
   {
//validate only the settle location group
      pTrade->validateAll (idDataGroup, TRADE_VALIDATION_GROUP::SETTLE_LOCATION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/TransSettlementInstrProcess.cpp-arc  $
// 
//    Rev 1.7   19 Dec 2008 13:14:28   popescu
// Incident 1514583 - Extraneous error msg when entering clearing method for transfer
// 
//    Rev 1.6   Jan 29 2008 13:24:42   daechach
// IN#1134569 - Cancel of Transfer out Trade not Allowed.
// 
//    Rev 1.5   Dec 10 2004 16:18:38   popescu
// PET 1117/56 few fixes for settl instr and trans fee list refresh
// 
//    Rev 1.4   Nov 29 2004 20:30:06   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.3   Nov 25 2004 14:58:40   popescu
// PET 1117/06, settle locations
// 
//    Rev 1.2   Nov 24 2004 21:35:28   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.1   Nov 19 2004 17:32:22   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0   Oct 14 2004 12:28:06   VADEANUM
// Initial revision.
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
