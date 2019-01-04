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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransCancelProcess.cpp
// ^AUTHOR :  
// ^DATE   : 02/20/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransCancelProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "TransCancelProcess.hpp"
#include "TransCancelProcessincludes.h"
#include "confirmationprocessincludes.h"
#include <ifastcbo\TransCancellist.hpp>
#include <ifastcbo\TransCancel.hpp>
#include <ifastcbo\BulkCancellist.hpp>
#include <ifastcbo\BulkCancel.hpp>
#include <ifastcbo\mfaccount.hpp>

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0337_vw.hpp>
#include <ifastdataimpl\dse_dstc0339_vw.hpp>
#include <ifastdataimpl\dse_dstc0339_vwRepeat_Record.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRANS_CANCEL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANS_CANCEL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TransCancelProcess > processCreator( CMD_BPROC_TRANS_CANCEL );


namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "TransCancelProcess" );

   const I_CHAR *Y = I_( "Y" );
   const I_CHAR *N = I_( "N" );
   
   const I_CHAR *pTRANSNUM   = I_( "TransNum" );
   const I_CHAR *pFROMSCREEN = I_( "FromScr" );  
   const I_CHAR *pINDC       = I_( "INDC" );  
   const I_CHAR *pINDC90     = I_( "90" );  
   const I_CHAR *pINDC95     = I_( "95" ); 
//   const I_CHAR *ALLOW_REBOOK_TRANS_TYPE  = I_("ED,PW,TR,XR,AW,AF91,AFTR,RR,RP,TI,TO,EI,EO");  //Allow Rebook Trans type
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId      ReadOnly;
   extern CLASS_IMPORT const BFDecimalFieldId   Trace;
   extern CLASS_IMPORT const BFTextFieldId      XtraActive;
   extern CLASS_IMPORT const BFTextFieldId      IsSplitDilution;
   extern CLASS_IMPORT const BFTextFieldId      RecptIssued;
   extern CLASS_IMPORT const BFTextFieldId      CancelContribRcpt;
   extern CLASS_IMPORT const BFTextFieldId      ExcldRcptPrint;
   extern CLASS_IMPORT const BFTextFieldId      RetRcptToSender;
   extern CLASS_IMPORT const BFTextFieldId      CancelGrant;
   extern CLASS_IMPORT const BFTextFieldId      GrantExists;
   extern CLASS_IMPORT const BFTextFieldId      TrfResubmit;
   extern CLASS_IMPORT const BFTextFieldId      IsAGrantTrade;
   extern CLASS_IMPORT const BFTextFieldId      SettleBatch;      
   extern CLASS_IMPORT const BFTextFieldId      RefundOption;
   extern CLASS_IMPORT const BFTextFieldId      RefundPayType;
   extern CLASS_IMPORT const BFTextFieldId      rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId      rxClassCode;
}

namespace UAF
{
    extern CLASS_IMPORT I_CHAR * const TRADING_PURCHASE;
    extern CLASS_IMPORT I_CHAR * const TRADING_EXCHANGE;
    extern CLASS_IMPORT I_CHAR * const TRADING_REDEMPTION;
}

namespace MFCAN_IP_PARAM
{
   extern const I_CHAR * const CALLER;
}
namespace TRANSCANCEL
{
   const I_CHAR * const DISPLAY_REBOOK      = I_("DisplayRebook");
   const I_CHAR * const ACCOUNT_NUM         = I_("AccountNum");
   const I_CHAR * const CASH_DIV_PAID_AFTER = I_("CashDivPaidAfter");    
   const I_CHAR * const BULK_CANCEL         = I_("BulkCancel");   
   const I_CHAR * const TRADE_DATE          = I_("TradeDate");
   const I_CHAR * const FUND                = I_("Fund");
   const I_CHAR * const CLASS               = I_("Class");
   const I_CHAR * const TRANS_NUM           = I_("TransactionNum");
   const I_CHAR * const TRADE_ADJUST_ID     = I_("TradeAdjustId");	   
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REBOOK_ALLOWABLE_TRANS_TYPES;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
TransCancelProcess::TransCancelProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pTransCancellist( NULL )
, _pTransCancel( NULL )
, _pBulkCancellist( NULL )
, _pBulkCancel( NULL )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::TRANS_CANCEL, false, BF::NullContainerId, true, I_("TransCancel") );      
   //addContainer( IFASTBP_PROC::TRANS_DETAILS, false, BF::NullContainerId, false, I_( "TransactionDetails" ) );
	
// from list vw 337
   addFieldDetails( ifds::TransNum,					IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::RvCode,					IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::OnStmt,					IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::Accountable,				IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::ConfirmRequired,		IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::CancelCheque,			IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::Remarks1,					IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::Remarks2,					IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::Remarks3,					IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::TransType,				IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::TranStatus,				IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::VerifiedBy,				IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::ReadOnly,					IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::ModPermission,			IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::Batch,						IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::Trace,						IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::TradeDate,				IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::Fund,						IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::Class,						IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::Rebook,					IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::CancellationType,		IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::XtraActive,				IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::Username,					IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::TradeAdjustID,			IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::MCHFileIndicator,		IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::SecRecFileIndicator,	IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::RbkMCHFileIndicator,	IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::RbkSecRecFileIndicator,IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::ESGSettle,				IFASTBP_PROC::TRANS_CANCEL );
   
   addFieldDetails( ifds::IsSplitDilution, 		IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::RecptIssued,          IFASTBP_PROC::TRANS_CANCEL, SUBCLASS_PROCESS); 
   addFieldDetails( ifds::CancelContribRcpt,	   IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::ExcldRcptPrint,			IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::RetRcptToSender, 		IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::CancelGrant, 		   IFASTBP_PROC::TRANS_CANCEL );
   
   addFieldDetails( ifds::RefundOption,		   IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::RefundPayType,	   IFASTBP_PROC::TRANS_CANCEL );   
   addFieldDetails( ifds::EventReceiptDate,	   IFASTBP_PROC::TRANS_CANCEL );
   addFieldDetails( ifds::EventReceiptTime,	   IFASTBP_PROC::TRANS_CANCEL);
}

//******************************************************************************
TransCancelProcess::~TransCancelProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
void TransCancelProcess::doGetField(
                                    const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    DString &strValueOut,
                                    bool bFormatted ) const
{  

   if ( idField == ifds::RecptIssued ) {
      strValueOut = _dstrRecptIssued;
   }

/*
   if( idField == VERIFICATION )
   {
      DString dstrStatus;

      if( _pTransCancelation )
	  {
		  _pTransCancelation->getField(ifds::Status, dstrStatus, BF::HOST);
		  if( dstrStatus == VERIFYIED ) strValueOut = YES;
		  else strValueOut = NO;
	  }
   }
*/
}

//******************************************************************************
SEVERITY TransCancelProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( pTRANSNUM,                        _TransNum );
      getParameter( pFROMSCREEN,                      _FromScreen );
      getParameter( TRANSCANCEL::ACCOUNT_NUM,         accountNum_ );
      getParameter( TRANSCANCEL::CASH_DIV_PAID_AFTER, cashDivPaidAfter_ );
      getParameter( I_("TRANSTYPE"),                  transType_);
      getParameter( TRANSCANCEL::TRADE_ADJUST_ID,     _dstrTradeAdjustID );
      getParameter( I_("SWPSETTLEESGELIG"),           _dstrSWPSettleESGElig );
      getParameter( I_( "TransSettleDate" ),          _dstrTransSettleDate );
      getParameter( pINDC,                            _dstrINDC );
      getParameter (I_("GrantExists"),                _grantExists);

      getParameter( I_("RecptIssued"),                _dstrRecptIssued );
      getParameter( I_("TrfResubmit"),                _trfResubmit);
      getParameter( I_("IsAGrantTrade"),              _isAGrantTrade);
      getParameter( I_("TransactionId"),              _TransactionId);
      getParameter( I_("SettleBatch"),                _SettleBatch);

      _TransNum.stripAll();

      if ( 0 == _TransNum.asInteger() || 
          I_( "Transaction" ) == _FromScreen )
      {
         // From the Trade Search screen
         getParameter( TRANSCANCEL::BULK_CANCEL, _dstrBulkCancel );
         getParameter( TRANSCANCEL::TRADE_DATE,  _dstrTradeDate );
         getParameter( TRANSCANCEL::FUND,        _dstrFund );
         getParameter( TRANSCANCEL::CLASS,       _dstrClass );
         _dstrBulkCancel.stripAll().upperCase();

         if ( I_( "Transaction" ) != _FromScreen )
            getParameter( TRANSCANCEL::TRANS_NUM, _TransNum );		
      }

      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( NULL != pDSTCWorkSession )
      {
         if ( _dstrBulkCancel != I_( "Y" ))
         {
            if(pDSTCWorkSession->getTransCancellist( _pTransCancellist, 
                                                    _TransNum,
                                                    cashDivPaidAfter_, 
                                                    getDataGroupId(),
                                                    _dstrTradeDate,
                                                    _dstrFund,
                                                    _dstrClass,
                                                    I_( "" ),    // Search Type
                                                    I_( "" ),    // TransStatus
                                                    I_( "" ),    // AdjustType
                                                    _dstrTradeAdjustID,
                                                    _dstrTransSettleDate,
                                                    transType_
                                                    ) <= WARNING &&
                                                    NULL != _pTransCancellist )
	         {
	
	            _pTransCancellist->setField( ifds::AccountNum, accountNum_, getDataGroupId(), false );
	            _pTransCancellist->setField( ifds::TransId, _TransactionId, getDataGroupId(), false );   
				
				BFObjIter iter ( *_pTransCancellist, 
	                              getDataGroupId(), 
	                              false, 
	                              BFObjIter::ITERTYPE::NON_DELETED );
	            if (!iter.end ())
	            {
	               _pTransCancel = dynamic_cast <TransCancel*> (iter.getObject() );
	            }
	
	            if ( NULL != _pTransCancel )
	            {
	               _pTransCancel->setField( ifds::GrantExists, _grantExists, getDataGroupId(), false );
	               _pTransCancel->setField( ifds::TrfResubmit, _trfResubmit, getDataGroupId(), false );
	               _pTransCancel->setField( ifds::IsAGrantTrade, _isAGrantTrade, getDataGroupId(), false );
	               _pTransCancel->setField( ifds::SettleBatch, _SettleBatch, getDataGroupId(), false );  
				   
				   _pTransCancel->setField( ifds::rxFundCode, _dstrFund, getDataGroupId(), false ); 
				   _pTransCancel->setField( ifds::rxClassCode, _dstrClass, getDataGroupId(), false ); 
				   
				   setContainer( IFASTBP_PROC::TRANS_CANCEL, _pTransCancel );
               }
            }
         }
         else if ( pDSTCWorkSession->getBulkCancellist( _pBulkCancellist,
                                                        getDataGroupId(),
                                                        _dstrTradeDate,
                                                        _dstrFund,
                                                        _dstrClass,
                                                        0,     // Transnum should be 0 for bulk cancellation. More make sense.
                                                        _dstrTradeAdjustID ) <= WARNING &&
                                                        NULL != _pBulkCancellist )
         {

            BFObjIter iter ( *_pBulkCancellist, 
                             getDataGroupId(), 
                             false, 
                             BFObjIter::ITERTYPE::NON_DELETED );
            if (!iter.end ())
            {
               _pBulkCancel = dynamic_cast <BulkCancel*> (iter.getObject() );
            }

            if ( NULL != _pBulkCancel )
               setContainer( IFASTBP_PROC::TRANS_CANCEL, _pBulkCancel );
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool TransCancelProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_TRANS_CANCEL );
}

//******************************************************************************
bool TransCancelProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false; 

   DString TransNum,FromScreen;
   getParameter( pTRANSNUM,   TransNum);
   getParameter( pFROMSCREEN, FromScreen);
   if( TransNum != _TransNum )
   {
      _TransNum = TransNum;
   }

   // From the Trade Search screen
   getParameter( TRANSCANCEL::BULK_CANCEL,     _dstrBulkCancel );
   getParameter( TRANSCANCEL::TRADE_DATE,      _dstrTradeDate );
   getParameter( TRANSCANCEL::FUND,            _dstrFund );
   getParameter( TRANSCANCEL::CLASS,           _dstrClass );
   getParameter( TRANSCANCEL::TRADE_ADJUST_ID, _dstrTradeAdjustID );
   getParameter( I_("TransSettleDate"),        _dstrTransSettleDate );
   getParameter( I_("GrantExists"),            _grantExists);

   if( isValidModelessInterface( _rpChildGI ) )
   {  // Only if child still exists
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }

   return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN TransCancelProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( pTRANSNUM,   _TransNum );
      setParameter( pFROMSCREEN, _FromScreen );
      setParameter( TRANSCANCEL::CASH_DIV_PAID_AFTER, cashDivPaidAfter_);
      setParameter( TRANSCANCEL::BULK_CANCEL, _dstrBulkCancel );

      setParameter( TRANSCANCEL::TRADE_DATE,  _dstrTradeDate );
      setParameter( TRANSCANCEL::FUND,        _dstrFund );
      setParameter( TRANSCANCEL::CLASS,       _dstrClass );
      setParameter( I_("TRANSTYPE"),          transType_);
      setParameter( I_("SWPSETTLEESGELIG"),   _dstrSWPSettleESGElig );	  
      setParameter( I_( "TransSettleDate" ),  _dstrTransSettleDate );
      setParameter( I_("GrantExists"),                 _grantExists);

      rtn = invokeCommand( this, 
                           CMD_GUI_TRANS_CANCEL, 
                           getProcessType(),   // PROC_NO_TYPE
                           isModal(),
                           &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
SEVERITY TransCancelProcess::doSetField(
                                        const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& idField,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strValue,
                                        bool bFormatted
                                        )
{
   return(NO_CONDITION);
}

//******************************************************************************
void *TransCancelProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
bool TransCancelProcess::doOk(GenericInterface *rpGICaller)
{
   setParameter( CONFPROC::PARM_CALLED_FROM, I_("TxnCancel") );
   
   DString dispRebook = I_("N"),
      batch;
   if ( I_( "Y" ) == _dstrBulkCancel )
      dispRebook = I_( "N" );
   else
   {
		DString transtatus,
          taxType;
		
      getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TranStatus, transtatus, false);
      getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::Batch, batch, false);
   
		DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
		MFAccount* pMFAccount = NULL;		
		
      if ( dstcWorkSession->getMFAccount ( getDataGroupId() ,accountNum_, pMFAccount) <= WARNING &&
			  pMFAccount)
		{
			pMFAccount->getField (ifds::TaxType,taxType,getDataGroupId());
			taxType.strip().upperCase();          
		}

		bool bPermit = hasCreatePermission( UAF::TRADING_PURCHASE ) ||
					      hasCreatePermission( UAF::TRADING_EXCHANGE ) ||
					      hasCreatePermission( UAF::TRADING_REDEMPTION ); 

		bool isTaxTypeNotResp = taxType != I_("9") && taxType != I_("M"); // desktop does not support RESP account for rebook
		bool cancelVerified   = transtatus.strip() == I_("02")? true:false;
		bool bAllowTransType = DSTCommonFunctions::codeInList (transType_, TRADETYPE::REBOOK_ALLOWABLE_TRANS_TYPES);
		bool bNotICTTrade = _dstrINDC != pINDC90;
		/*
			Maturity trade is created by cycle when investment is matured with INDC 95, 
			So it cannot be rebook. Users will have to manual enter the trade to 
			direct fund/class as they want.
		*/
		bool bNotMatInstTrade = _dstrINDC != pINDC95;

		dispRebook = (bPermit && isTaxTypeNotResp && bNotICTTrade && cancelVerified && bAllowTransType && bNotMatInstTrade) ? I_("Y") : I_("N");  
   }

   setParameter (TRANSCANCEL::DISPLAY_REBOOK, dispRebook);
   setParameter (TRANSCANCEL::BULK_CANCEL, _dstrBulkCancel);
   setParameter (I_("Batch"), batch);

   return true;
}

//******************************************************************************
bool TransCancelProcess::doSend ( GenericInterface *rpGICaller, 
                                  const I_CHAR *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doSend"));
   
   DString message (szMessage);     

   if( I_("RefreshBulkRebook") == message )
   {
      if (_pBulkCancel)
      {         
            _pBulkCancel->restore( getDataGroupId() );       
      }
   }

   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransCancelProcess.cpp-arc  $
// 
//    Rev 1.35   Jul 19 2012 14:16:58   kitticha
// PETP0186477 FN05 IN3021492 - Cannot cancell trade in same tradedate, fund, class.
// 
//    Rev 1.34   May 07 2012 14:08:16   wp040027
// PETP0187485-CPF-Trade Cancellation
// 
//    Rev 1.33   Apr 05 2011 07:00:54   kitticha
// PETP0181067_FN00_IN2460780_Empire Autobatch Development on Cancelled SP and DC trades.
// 
//    Rev 1.32   Oct 29 2010 06:30:14   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.31   Jun 01 2010 23:28:40   dchatcha
// IN#2128812 - PETP0165541 FN 01 - Cancellation of processed transaction for RESP Accounts.
// 
//    Rev 1.30   Apr 14 2010 23:56:48   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.29   Jul 17 2009 14:15:08   jankovii
// IN 1724320 - ESG19 - ICT - rebooked ICT trade reported as CON 69 instead of CON6
// 
//    Rev 1.28   26 May 2009 17:10:36   popescu
// PET 159770 FN05 Auto Batching - set batch as parameter for reebook
// 
//    Rev 1.27   Dec 11 2007 15:48:18   wongsakw
// PET 2360 FN60 -- Automatically Cancel Contribution Reciept
// 
//    Rev 1.26   Nov 02 2007 11:27:40   jankovii
// IN #1057653 - trade cancellation using split diluton.
// 
//    Rev 1.25   Nov 14 2006 16:48:24   porteanm
// Incident 676881 - Pass TransType to 338 (TransCancel).
// 
//    Rev 1.24   Mar 10 2006 13:58:30   porteanm
// Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
// 
//    Rev 1.23   Mar 02 2006 17:31:24   ZHANGCEL
// PET1334 - FN01 -- ESG Settlement enhancement
// 
//    Rev 1.22   Jan 12 2006 16:12:58   zhengcon
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Trade Cancellation: Individual and rebook
// 
//    Rev 1.21   Dec 29 2005 13:15:42   porteanm
// Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class.
// 
//    Rev 1.20   Nov 27 2005 13:50:22   porteanm
// PET1286 FN01 - Bulk Cancellation - Rebook.
// 
//    Rev 1.19   Nov 26 2005 17:33:40   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.18   Nov 24 2005 16:21:24   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.17   Nov 23 2005 17:10:30   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.16   Nov 13 2005 15:38:00   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.15   Nov 12 2005 11:55:50   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.14   Nov 11 2005 17:17:22   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.13   Nov 10 2005 13:24:50   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.12   Nov 08 2005 19:20:46   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.11   Sep 15 2005 09:11:42   popescu
// Incident #398841 - activated the Rebook radio button for Rollovers (RP and RR) - fixed comp error
// 
//    Rev 1.10   Sep 15 2005 08:59:06   popescu
// Incident #398841 - activated the Rebook radio button for Rollovers (RP and RR)
// 
//    Rev 1.9   Jul 29 2005 14:55:34   Yingbaol
// Allow Transfer in/out exchange in/out for rebook
// 
//    Rev 1.8   Jul 20 2005 14:02:18   Yingbaol
// PET1235,FN01:fix refresh issue
// 
//    Rev 1.7   Jul 08 2005 09:38:26   Yingbaol
// PET1235,FN01:cancellation rebook
// 
//    Rev 1.6   Apr 01 2005 13:45:16   Fengyong
// Remove doValidateAll fundction
// 
//    Rev 1.5   Mar 16 2005 18:38:04   Fengyong
// PET1190FN05 - after restrore button clicked, do not allow modify
// 
//    Rev 1.4   Mar 16 2005 15:44:50   Fengyong
// PET1190 FN05 - change view 337 to repeatable
// 
//    Rev 1.3   Mar 09 2005 13:20:26   Fengyong
// PET1190 FN04 - Add Batch and Trace
// 
//    Rev 1.2   Mar 08 2005 19:41:32   Fengyong
// PET1190FN04 - Add DOOK
// 
//    Rev 1.1   Mar 07 2005 14:28:18   Fengyong
// PET1190FN04 - Add AccountableCode rules
 */
