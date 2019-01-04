//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TradesTaxRateProcess.cpp
// ^AUTHOR : Yong Mei Feng
// ^DATE   : August 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TradesTaxRateProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\mgmtco.hpp>
#include "TradesTaxRateProcess.hpp"
#include <ifastcbo\trade.hpp>
#include "TradesTaxRateProcessincludes.h"
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfsessn\bfawdsession.hpp>
#include <bfcbo\bfobjiter.hpp>
#include <bfcbo/validationcontrol.hpp>
#include <ifastcbo/redemptionvalidation.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRADES_TAXRATE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADES_TAXRATE;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TradesTaxRateProcess > processCreator( CMD_BPROC_TRADES_TAXRATE );

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TradesTaxRateProcess" );   
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;   
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Taxable;
}

namespace TRADE_TAXRATE_PARAM
{
	const I_CHAR * const MAIN_LIST_KEY    = I_("MainListKey");
	const I_CHAR * const ACCOUNT_NUM      = I_("AccountNum");
	const I_CHAR * const TRANSACTION_TYPE = I_("TransType");

	extern const I_CHAR * const OVERRIDE_TAX     = I_("OverrideTax");
	extern const I_CHAR * const FED_TAX_RATE     = I_("FedTaxRate");
	extern const I_CHAR * const PROV_TAX_RATE    = I_("ProvTaxRate");

}

namespace TAX_TYPE_GROUPING
{
   const long TAX_RATE = 0x0001;
}
//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319TradesTaxRateProcess::TradesTaxRateProcess() : 
TradesTaxRateProcess::TradesTaxRateProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, _dstrAccontNum( NULL_STRING )
, _dstrTransactionType( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //add containers
   addContainer( IFASTBP_PROC::TRADES_LIST, true, BF::NullContainerId, true, I_( "Trade" ) );

   addFieldDetails( ifds::Taxable,			  IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::FedRate,          IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::ProvRate,         IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::TransRatePUDFed,  IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::TransRatePUDProv, IFASTBP_PROC::TRADES_LIST );
   addFieldDetails( ifds::OverrideTax,      IFASTBP_PROC::TRADES_LIST );
}

//******************************************************************************
TradesTaxRateProcess::~TradesTaxRateProcess()
{

   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;

}

//******************************************************************************
SEVERITY TradesTaxRateProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );
   SEVERITY sevRtn = NO_CONDITION;
   const BFDataGroupId& idDataGroup = getDataGroupId();

   try
   {
	   //currently this process only called from trade dialog,suppose know the current key .
	   //need override the key system for worksession tradelist, to get taxrate information for a specific key.
	   getParameter( TRADE_TAXRATE_PARAM::MAIN_LIST_KEY,    _dstrCurrentKey );
	   getParameter( TRADE_TAXRATE_PARAM::ACCOUNT_NUM,      _dstrAccontNum );	   
	   getParameter( TRADE_TAXRATE_PARAM::TRANSACTION_TYPE, _dstrTransactionType );
		_dstrAccontNum.strip();
	   _dstrTransactionType.strip().upperCase();
     	   
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      // call getTradesList with idDataGroup, not BF::HOST - PTS 
		if ( NULL != dstcWorkSession &&			
			  dstcWorkSession->getTradesList( _pTradesList,  // blCreate, Track and Activity are defaulted anyway in hpp
			                                  idDataGroup ) <= WARNING &&
			  NULL != _pTradesList )
      { 
			setContainer( IFASTBP_PROC::TRADES_LIST, _pTradesList );

			DString dstrOverrideTax, dstrFedTaxRate, dstrProvTaxRate;										
			getParameter( TRADE_TAXRATE_PARAM::OVERRIDE_TAX,  dstrOverrideTax );
			getParameter( TRADE_TAXRATE_PARAM::FED_TAX_RATE,  dstrFedTaxRate );		
			getParameter( TRADE_TAXRATE_PARAM::PROV_TAX_RATE, dstrProvTaxRate );	
			double dblFedTaxRate  = DSTCommonFunctions::convertToDouble( dstrFedTaxRate );				
  			double dblProvTaxRate = DSTCommonFunctions::convertToDouble( dstrProvTaxRate );
								
			if ( I_( "No" ) == dstrOverrideTax && 0 == dblFedTaxRate && 0 == dblProvTaxRate )
			{
				Trade *pTrade = dynamic_cast<Trade *>(( const_cast < TradesTaxRateProcess*>( this ) )->getCBOItem( IFASTBP_PROC::TRADES_LIST, idDataGroup ));
				if( NULL != pTrade )
				{				
					RedemptionValidation *pRedemptionValidation = NULL;
					if ( pTrade->getRedemptionValidation( pRedemptionValidation, idDataGroup ) <= WARNING &&
						  NULL != pRedemptionValidation )
					{
						pRedemptionValidation->getField( ifds::FedRate,  dstrFedTaxRate,  idDataGroup );
						pRedemptionValidation->getField( ifds::ProvRate, dstrProvTaxRate, idDataGroup );
					}

					pTrade->setField( ifds::FedRate,  dstrFedTaxRate,  idDataGroup, true );
					pTrade->setField( ifds::ProvRate, dstrProvTaxRate, idDataGroup, true );
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
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(sevRtn);
}

//******************************************************************************
E_COMMANDRETURN TradesTaxRateProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doProcess"));
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !bfutil::isServerContext()  )
      {
		   setCurrentListItem(this, IFASTBP_PROC::TRADES_LIST, _dstrCurrentKey);
         rtn = invokeCommand( this, 
				                  CMD_GUI_TRADES_TAXRATE, 
										getProcessType(), 
										isModal(),
                              &_rpChildGI );

         GETCURRENTHIGHESTSEVERITY();
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//**********************************************************************
void *TradesTaxRateProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;

   try
   {
      if( IFASTBP_PROC::TRADES_LIST == idContainer )
      {		
		      setCurrentListItem(this, IFASTBP_PROC::TRADES_LIST, _dstrCurrentKey);
            Trade * pCurrTrade = dynamic_cast < Trade *> (getCBOItem( IFASTBP_PROC::TRADES_LIST, idDataGroup ));
            if( !pCurrTrade )
               return(NULL);

            ptr = pCurrTrade;
      }
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
bool TradesTaxRateProcess::doSend( GenericInterface *rpGICaller, const I_CHAR * szMessage )
{
   bool valRtn = true;
   DString dstr(szMessage);
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   valRtn = AbstractProcess::doSend( rpGICaller, szMessage );

   return(valRtn );
}

//******************************************************************************
bool TradesTaxRateProcess::doOk( GenericInterface *rpGICaller )
{
   return(true);
}

//******************************************************************************

bool TradesTaxRateProcess::doCancel( GenericInterface * rpGICaller )
{
/*
	const BFDataGroupId& idDataGroup = getDataGroupId();
	setCurrentListItem(rpGICaller, IFASTBP_PROC::TRADES_LIST, _dstrCurrentKey);
    Trade * pCurrTrade = dynamic_cast < Trade *> (getCBOItem( IFASTBP_PROC::TRADES_LIST, idDataGroup ));
    if( pCurrTrade )
	{
		pCurrTrade->setField(ifds::FedRate, _oldFedRate, idDataGroup, false);
		pCurrTrade->setField(ifds::ProvRate, _oldProvRate, idDataGroup, false);
		pCurrTrade->setField(ifds::TransRatePUDFed, _oldTransRatePUDFed, idDataGroup, false);
		pCurrTrade->setField(ifds::TransRatePUDProv, _oldTransRatePUDProv, idDataGroup, false);
		pCurrTrade->setField(ifds::OverrideTax, _oldOverrideTax, idDataGroup, false);
	}
*/
   return(true);
}

//******************************************************************************
SEVERITY TradesTaxRateProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, OK2 );
   //   BFSessionManager *rpBSM = BFSessionManager::getInstance();
   //   WorkSessionDetails *rpWSD =
   //      rpBSM->getWorkSessionDetails( getWorkSessionID() );
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   const BFDataGroupId& idDataGroup = getDataGroupId();
   bool bSuccessFlag = false;
   bool bNeedRefresh = false;
   bool bUpdated = false;
   // Allow subclass override if need to do other things prior to any ok2
   //  processing
   bool bContinue = true;
   WorksessionTradesList* pTradesList;

   if( doOk( rpGICaller ) )
   {	  
      if( dstcWorkSession && dstcWorkSession->getTradesList(pTradesList, idDataGroup, false) <= WARNING )
      {  // Only if work session details exists
         if( pTradesList->isNew() || dstcWorkSession->isUpdatedForDataGroup( idDataGroup ) )
         {
            bUpdated = true;
            Trade * pCurrTrade = NULL;
			SEVERITY eRtn = NO_CONDITION;

			BFObjIter bfObjIter( *pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			bfObjIter.positionByKey( _dstrCurrentKey );
			if( !bfObjIter.end( ) )
			{
				pCurrTrade = dynamic_cast < Trade *> ( bfObjIter.getObject());
				eRtn = pCurrTrade->validateAll( idDataGroup, TAX_TYPE_GROUPING::TAX_RATE );
			}			            
			
            if( eRtn == WARNING && !bfutil::isServerContext() )
            {
               bContinue = rpGICaller->send( rpGICaller, I_( "WarningConfirm" ) );
            }
            if( bContinue )
            {
               if( eRtn < WARNING || ( eRtn == WARNING && getIgnoreWarningsOnOk2() ) ) //ConfirmationProcess doesn't get launched if we got a warning
               {
                  //and bIgnoreWarningsOnOk2_ is set to false
                  bSuccessFlag = true;
                  if( getProcessType() == PROC_SUPPORT ||
                     ( bfutil::isServerContext() && isModal() ) ||
                     ( !bfutil::isServerContext() && isModal() &&  getParent() && getParent()->isModal() ) )
                  {  // we should only do this commit if we are not about to confirm
                     //  and there should be a NON BF::HOST parent group to commit to
                     // Note that modal without parent will not commit here
                     if( !ValidationControl::get().isValidateOnly() )
                     {
                        if( dstcWorkSession->commitDataGroup( idDataGroup ) <= WARNING )
                        {  // Refresh other processes
                           bNeedRefresh = true;
                        }
                        else
                        {  // Commit failed
                           PROMOTECONDITIONS();
                           bSuccessFlag = false;
                        }
                     }
                  }
               }
               else if( bfutil::isServerContext() )
               {  // for gui, errors get picked up directly from CBO's ?
                  PROMOTECONDITIONS();
               }
            } // if bContinue
         }
         else
         {  // Nothing happened - make sure and remove any dummy entries added
            dstcWorkSession->deleteNonUpdatedAddedElements( idDataGroup );
            bSuccessFlag = true;
         }
      }
   }
   else
   {  // get doOK conditions, if any
      PROMOTECONDITIONS();
   }

   //no need to confirm and refresh if we've been used for support
   if( dstcWorkSession && bSuccessFlag && getProcessType() != PROC_SUPPORT )
   {
      if( ( bfutil::isServerContext() && !isModal() ) ||
         ( !bfutil::isServerContext() && (!getParent() || !getParent()->isModal() ) ) )
      {  // Possibly need confirmation if we are modeless, no parent, or our
         // parent is modeless
         BFCPSession *pSession = getSession();

         BFAwdSession *rpAwdSession = NULL;

         if( pSession != NULL )
         {
            rpAwdSession = pSession->getAwdSession();
         }

         if( bUpdated && !ValidationControl::get().isValidateOnly() /* || ( rpAwdSession && rpAwdSession->getProcessWork() ) */ )
         {
            // this will commit *our* datagroup (i.e. this->getDataGroupId() )
            if( CMD_OK != invokeCommand( this, CMD_BPROC_CONFIRMATION,
                                         PROC_NO_TYPE, true, NULL ) )
            {
               DString strOut;
               bSuccessFlag = false;
               PROMOTECONDITIONS();
               getParameter( I_( "TrxnsError" ), strOut );
               if( strOut == I_( "Y" ) )
               {  // Need to halt further activities in BaseMainDlg
                  rpGICaller->send( this, I_( "TrxnsError" ) );
               }
            }
            else
            {  // Force refresh for now - but not needed for all cases
               bNeedRefresh = true;

               // if we are in "server mode" then make sure
               // that all errors get reported.
               if( bfutil::isServerContext() )
               {
                  PROMOTECONDITIONS();
               }
            }
         }
      }
      if( bNeedRefresh )
      {
         getGIContainer()->refresh( this );
      }
   }

   // Allow subclass override if need to do things after ok processing
   doPostOk( rpGICaller, bSuccessFlag );
   if( bSuccessFlag )
   {
      return(NO_CONDITION);
   }
   return(SEVERE_ERROR);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/TradesTaxRateProcess.cpp-arc  $
// 
//    Rev 1.7   Jun 02 2004 14:13:08   VADEANUM
// PTS 10030905 - Fixed crash caused by calling TradesList at BH::HOST level instead of idDataGroup.
// 
//    Rev 1.6   Oct 19 2003 18:26:48   popescu
// fix link error
// 
//    Rev 1.5   Sep 24 2003 10:43:36   VADEANUM
// PTS 10021736 - Withholding Tax Default Rates.
// 
//    Rev 1.4   Sep 23 2003 12:38:02   VADEANUM
// PTS 10021736 - Withholding Tax Default Rates.
//
