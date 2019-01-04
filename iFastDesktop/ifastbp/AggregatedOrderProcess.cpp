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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AggregatedOrderProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 2 /11/2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AggregatedOrderProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "AggregatedOrderProcess.hpp"
#include <ifastcbo\AggregatedOrderlist.hpp>
#include <ifastcbo\AggregatedOrder.hpp>
#include <ifastcbo\PendingTradeList.hpp>
#include "AggregatedOrderProcessInclude.h"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include "confirmationprocessincludes.h"


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AGGREGATED_ORDER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AGGREGATED_ORDER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AggregatedOrderProcess > processCreator( CMD_BPROC_AGGREGATED_ORDER );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME					= I_( "AggregatedOrderProcess" );
	const I_CHAR * const PERFORMSEARCH           = I_( "performSearch" ); 
   const I_CHAR * const Y = I_( "Y" );
   const I_CHAR * const N = I_( "N" );
	const I_CHAR * const YES							= I_( "Y" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const OMNBUS;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFIntegerFieldId LossCount;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId Recalculate; 
   extern CLASS_IMPORT const BFTextFieldId Currency; 
	extern CLASS_IMPORT const BFTextFieldId AggrOrdRefreshed;
	extern CLASS_IMPORT const BFTextFieldId AllowEnableOk;
	extern CLASS_IMPORT const BFTextFieldId Recalculate;
	extern CLASS_IMPORT const BFNumericFieldId WarnMsgCode;
}
namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const AGGREGATED_ORDER_INFORMATION;
}
//******************************************************************************
//              Public Methods
//******************************************************************************
AggregatedOrderProcess::AggregatedOrderProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pAggregatedOrderList( NULL )
, _pPendingTradeList(NULL)
, _pFundDetailList(NULL)
, _rpChildGI( NULL )

{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

	addContainer( IFASTBP_PROC::AGGREGATED_ORDER_LIST, true,//repeatable
									BF::NullContainerId, true //updatable
									);

	addContainer( IFASTBP_PROC::PENDING_TRADE, true,//repeatable
									IFASTBP_PROC::AGGREGATED_ORDER_LIST, false //un-updatable
									);
	 
	addFieldDetails( ifds::AggregateOption, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::OmnibusID, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::FundCode, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::ClassCode, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::AggrOrdId, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::FundWKN, IFASTBP_PROC::AGGREGATED_ORDER_LIST, SUBCLASS_PROCESS );
	addFieldDetails( ifds::FundISIN, IFASTBP_PROC::AGGREGATED_ORDER_LIST, SUBCLASS_PROCESS );
	addFieldDetails( ifds::Currency, IFASTBP_PROC::AGGREGATED_ORDER_LIST, SUBCLASS_PROCESS );
	addFieldDetails( ifds::AllowEnableOk, IFASTBP_PROC::AGGREGATED_ORDER_LIST, SUBCLASS_PROCESS );

	addFieldDetails( ifds::FundName, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::TransType, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::GroupCode, IFASTBP_PROC::AGGREGATED_ORDER_LIST);
	addFieldDetails( ifds::Amount, IFASTBP_PROC::AGGREGATED_ORDER_LIST);
	addFieldDetails( ifds::AmountType, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::TradeDate, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::BrkSettlDate, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::BrkSettlAmtUnits, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::BrkSettlPUD, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::AFTBenefit, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::Price, IFASTBP_PROC::AGGREGATED_ORDER_LIST);
	addFieldDetails( ifds::AggrPriceType, IFASTBP_PROC::AGGREGATED_ORDER_LIST);
	addFieldDetails( ifds::Commission, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::ExternCharge, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::RebateRate, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::OrdStatus, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::NAV, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::OfferPrice, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::DeliveryTo, IFASTBP_PROC::AGGREGATED_ORDER_LIST);
	addFieldDetails( ifds::ForAccount, IFASTBP_PROC::AGGREGATED_ORDER_LIST);
	addFieldDetails( ifds::InFavourOf, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::SettlInstrCode, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::SettleAccountNum, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::SettleLocationCode, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::ProcessTime, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::RemarksAggr, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::RoutingRef, IFASTBP_PROC::AGGREGATED_ORDER_LIST);
	addFieldDetails( ifds::RoutingType, IFASTBP_PROC::AGGREGATED_ORDER_LIST);
	addFieldDetails( ifds::ClrSettlMethod, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::BrokerName, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::Recalculate, IFASTBP_PROC::AGGREGATED_ORDER_LIST ); 
	addFieldDetails( ifds::AggrOrdRefreshed, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::WarnMsgCode, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::LossCount, IFASTBP_PROC::AGGREGATED_ORDER_LIST, SUBCLASS_PROCESS );
	addFieldDetails( ifds::SecRecFileIndicator, IFASTBP_PROC::AGGREGATED_ORDER_LIST );

	addFieldDetails( ifds::rxAcctNum, IFASTBP_PROC::PENDING_TRADE );
	addFieldDetails( ifds::TransNum, IFASTBP_PROC::PENDING_TRADE );
	addFieldDetails( ifds::Amount, IFASTBP_PROC::PENDING_TRADE );
	addFieldDetails( ifds::AmountType, IFASTBP_PROC::PENDING_TRADE );
	addFieldDetails( ifds::AcqFeeOption, IFASTBP_PROC::PENDING_TRADE);
	addFieldDetails( ifds::ConditionRate, IFASTBP_PROC::PENDING_TRADE);
	addFieldDetails( ifds::TxnFee, IFASTBP_PROC::PENDING_TRADE );
	addFieldDetails( ifds::ClntSettlAmt, IFASTBP_PROC::PENDING_TRADE );
	addFieldDetails( ifds::BrkSettlAmt, IFASTBP_PROC::PENDING_TRADE );
	addFieldDetails( ifds::GainOrLossAmt, IFASTBP_PROC::PENDING_TRADE );
	
		// Show Admin Dates support
	addFieldDetails(ifds::ModUser,           IFASTBP_PROC::AGGREGATED_ORDER_LIST );	
	addFieldDetails(ifds::ModDate,           IFASTBP_PROC::AGGREGATED_ORDER_LIST );	
	addFieldDetails(ifds::ProcessDate,       IFASTBP_PROC::AGGREGATED_ORDER_LIST );	
	addFieldDetails(ifds::Username,          IFASTBP_PROC::AGGREGATED_ORDER_LIST );	
    addFieldDetails(ifds::AggrDate,          IFASTBP_PROC::AGGREGATED_ORDER_LIST );	
    addFieldDetails(ifds::AggrTime,          IFASTBP_PROC::AGGREGATED_ORDER_LIST );	
    addFieldDetails( ifds::CashMsgType,               IFASTBP_PROC::AGGREGATED_ORDER_LIST  );
    addFieldDetails( ifds::IntermediaryBank,          IFASTBP_PROC::AGGREGATED_ORDER_LIST  );
    addFieldDetails( ifds::ReceivingBank,             IFASTBP_PROC::AGGREGATED_ORDER_LIST  );
    addFieldDetails( ifds::Beneficiary,               IFASTBP_PROC::AGGREGATED_ORDER_LIST  );
    addFieldDetails( ifds::SpecialInstructions,       IFASTBP_PROC::AGGREGATED_ORDER_LIST  );
    addFieldDetails( ifds::InternalSettlementAccount, IFASTBP_PROC::AGGREGATED_ORDER_LIST  );
	addFieldDetails( ifds::LastModfiedStatus, 		  IFASTBP_PROC::AGGREGATED_ORDER_LIST  );
	addFieldDetails( ifds::CancelRequestedUser, 	  IFASTBP_PROC::AGGREGATED_ORDER_LIST  );	
}

//******************************************************************************

AggregatedOrderProcess::~AggregatedOrderProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME )
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AggregatedOrderProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
     processParameters();
	  DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	  if( pDSTCWorkSession->getAggregatedOrderList( _dstrFromDate, _dstrToDate, _dstrStatus,
			_dstrBrokerCode, _dstrFundCode, _dstrAggrOrderNum, _dstrRoutingRefNum,_dstrSearchType,
			_pAggregatedOrderList, getDataGroupId()) 
			<= WARNING && _pAggregatedOrderList )
      {
		  setContainer( IFASTBP_PROC::AGGREGATED_ORDER_LIST, _pAggregatedOrderList );
	  }
	}


   catch(ConditionException& ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************

E_COMMANDRETURN AggregatedOrderProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   // Set Parameters
   setParameter( I_("DisableMsg"), _DisableMsg );
	setParameter(AGGREGATE::AGGR_ORDER_NUMBER, _dstrAggrOrderNum);

   try
   {
      if( isXMLAPIContext() )
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
        
         bool bPermAggregatedOrder= hasReadPermission( UAF::AGGREGATED_ORDER_INFORMATION);
         if( bPermAggregatedOrder ) 
         {
            rtn = invokeCommand( this, CMD_GUI_AGGREGATED_ORDER, getProcessType(), isModal(), &_rpChildGI );
			}
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}


//******************************************************************************
bool AggregatedOrderProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;

   bool bRtn = false;
	try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      if( isValidModelessInterface( _rpChildGI ) )
      {  
			// Only if child still exists            
			setContainer( IFASTBP_PROC::AGGREGATED_ORDER_LIST, NULL );
         setContainer( IFASTBP_PROC::PENDING_TRADE, NULL );
			bRtn = _rpChildGI->refresh( this, I_("ReloadParams" ) );
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
      }
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
bool AggregatedOrderProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_AGGREGATED_ORDER  );
}

//******************************************************************************
bool AggregatedOrderProcess::doRefresh ( GenericInterface *rpGICaller, 
                                         const I_CHAR *szOriginalCommand)
{
   TRACE_METHOD (CLASSNAME, DOREFRESH);
//remove the pending trade list from the current aggregated order
   if (DString (szOriginalCommand) == I_("RefreshPendingTradeList"))
   {
      const BFDataGroupId &idDataGroup = getDataGroupId ();
      AggregatedOrder* rpAggregatedOrder = 
            dynamic_cast <AggregatedOrder*> (getCBOItem ( IFASTBP_PROC::AGGREGATED_ORDER_LIST, 
                                                          idDataGroup));
		rpAggregatedOrder->setField (ifds::Recalculate, YES, getDataGroupId(), false);
		rpAggregatedOrder->ForceToDoCalculation (getDataGroupId());
   }
   return _rpChildGI->refresh (this, NULL);

}
	
//******************************************************************************

void AggregatedOrderProcess::doGetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      DString &strValueOut,
                                      bool bFormatted
                                    ) const
{
	 MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );
	 DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	 DString dstrFundCode, dstrClassCode, currency;
    const_cast <AggregatedOrderProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::AGGREGATED_ORDER_LIST, 
                                                             ifds::FundCode, dstrFundCode, false);
    const_cast <AggregatedOrderProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::AGGREGATED_ORDER_LIST, 
                                                             ifds::ClassCode, dstrClassCode, false);
     
   if( idField == ifds::FundWKN )
   {

      pDSTCWorkSession->GetWKNNumber ( dstrFundCode, dstrClassCode, strValueOut );  
	}
	else if ( idField == ifds::FundISIN )
	{
		pDSTCWorkSession->GetISINNumber ( dstrFundCode,dstrClassCode, strValueOut );   
	}
	else if ( idField == ifds::Currency )
	{
		CurrencyClass::getFundCurrency( *pDSTCWorkSession, dstrFundCode, dstrClassCode, currency );
      currency.strip();
		strValueOut = currency;
	}
	else if ( idField == ifds::LossCount )
	{
      AggregatedOrder* rpAggregatedOrder = dynamic_cast <AggregatedOrder*> 
            (const_cast <AggregatedOrderProcess*> (this)->getCBOItem (IFASTBP_PROC::AGGREGATED_ORDER_LIST, idDataGroup));
         
		if (rpAggregatedOrder)
      {
         strValueOut = asString (rpAggregatedOrder->getNumberOfLossTrade(getDataGroupId ()));	
      }
	}

	else if ( idField == ifds::AllowEnableOk )
	{
		if( _pAggregatedOrderList != NULL )
		{
			if ( _pAggregatedOrderList->allowEnableOk (getDataGroupId()) )
				strValueOut  =  I_("Y");
			else
				strValueOut = I_("N");
		}
	}
}
//******************************************************************************
//******************************************************************************
void *AggregatedOrderProcess::getPtrForContainer( const BFContainerId &idContainer,
                                                  const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
	void *ptr = NULL;
	
	try
	{
 		if (IFASTBP_PROC::PENDING_TRADE == idContainer)
		{						
         AggregatedOrder* rpAggregatedOrder = dynamic_cast <AggregatedOrder*> 
               (getCBOItem (IFASTBP_PROC::AGGREGATED_ORDER_LIST, idDataGroup));
          
			if (rpAggregatedOrder)
         {
            PendingTradeList *pPendingTradeList = NULL;
            if ( rpAggregatedOrder->getPendingTradeList (pPendingTradeList, idDataGroup) <= WARNING &&
                 pPendingTradeList)
            {
               ptr = pPendingTradeList;
            }
         }
		}
	}
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch (...)
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
	return ptr;
}

//******************************************************************************
SEVERITY AggregatedOrderProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));
   _dstrBrokerCode = _dstrStatus = _dstrFundCode = _dstrSearchType =
   _dstrAggrOrderNum = _dstrRoutingRefNum = NULL_STRING;
   _DisableMsg = NULL_STRING;
   getParameter(AGGREGATE::FROM_DATE, _dstrFromDate);
   getParameter(AGGREGATE::TO_DATE, _dstrToDate);
   getParameter(AGGREGATE::STATUS, _dstrStatus);
   _dstrStatus.stripAll().upperCase();
   getParameter(AGGREGATE::FUND_BROKER_CODE, _dstrBrokerCode);
   _dstrBrokerCode.stripAll().upperCase();
   getParameter(AGGREGATE::FUND_CODE, _dstrFundCode);
   _dstrFundCode.stripAll().upperCase();
   getParameter(AGGREGATE::AGGR_ORDER_NUMBER, _dstrAggrOrderNum);
   _dstrAggrOrderNum.stripAll().upperCase();
   getParameter(AGGREGATE::ROUTING_REF_NUMBER, _dstrRoutingRefNum);
   _dstrRoutingRefNum.stripAll().upperCase();
   getParameter(AGGREGATE::SEARCH_TYPE, _dstrSearchType);
   _dstrSearchType.stripAll().upperCase();
   getParameter( I_("DisableMsg"), _DisableMsg );
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AggregatedOrderProcess::doMoreRecordsExist(GenericInterface *rpGICaller,
   const BFContainerId &idSearch)
{
   if( idSearch == IFASTBP_PROC::AGGREGATED_ORDER_LIST )
   {
      if( rpGICaller == NULL )
         return(false);
      return (_pAggregatedOrderList == NULL) ? false : _pAggregatedOrderList->doMoreRecordsExist();
   }

   if ( idSearch == IFASTBP_PROC::PENDING_TRADE )
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
      AggregatedOrder * pAggregatedOrder = 
         dynamic_cast <AggregatedOrder*> (getCBOItem( IFASTBP_PROC::AGGREGATED_ORDER_LIST, idDataGroup ));

      PendingTradeList *pPendingTradeList = NULL ;

      if( pAggregatedOrder )
      {
         if ( pAggregatedOrder->getPendingTradeList (pPendingTradeList, idDataGroup) <= WARNING &&
               pPendingTradeList)
         {
            return (rpGICaller == NULL || pPendingTradeList == NULL) ? 
               false : pPendingTradeList->doMoreRecordsExist();
         }
      }
   }

   return false;
}

//******************************************************************************
bool AggregatedOrderProcess::doSend( GenericInterface* rpGICaller,const I_CHAR* szMessage )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSend") );
   bool valRtn = true;
   DString dstr (szMessage);

   if (dstr == I_("CallView324") || dstr == I_( "ModifyTrade" ))
   {
      setContainer (IFASTBP_PROC::PENDING_TRADE, NULL);
      AggregatedOrder* rpAggregatedOrder = dynamic_cast <AggregatedOrder*> 
            (getCBOItem (IFASTBP_PROC::AGGREGATED_ORDER_LIST, getDataGroupId()));
         
		if (rpAggregatedOrder)
      {
         if (dstr == I_("CallView324"))
         {
            valRtn = rpAggregatedOrder->ForceToDoCalculation (getDataGroupId()) < WARNING;
         }
			else
         {
            valRtn = AbstractProcess::doSend (rpGICaller, szMessage);
         }
      }
	}
   else
   {
      valRtn = AbstractProcess::doSend (rpGICaller, szMessage);
   }	
   return valRtn;
}

//******************************************************************************
SEVERITY AggregatedOrderProcess::performSearch( GenericInterface *rpGI, 
                                                const BFContainerId& idSearch, 
                                                E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;
   const BFDataGroupId& idDataGroup = getDataGroupId ();

   try
   {
      switch( eSearchAction )
      {
         case SEARCH_START:
         {
            if( idSearch == IFASTBP_PROC::AGGREGATED_ORDER_LIST )
            {
               if ( _pAggregatedOrderList != NULL )
               {
                  _pAggregatedOrderList = NULL;
               }

               setContainer(IFASTBP_PROC::AGGREGATED_ORDER_LIST, NULL);

               DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
               if( pDSTCWorkSession->getAggregatedOrderList( _dstrFromDate,
                                                             _dstrToDate,
                                                             _dstrStatus,
                                                             _dstrBrokerCode,
                                                             _dstrFundCode,
                                                             _dstrAggrOrderNum,
                                                             _dstrRoutingRefNum,
                                                             _dstrSearchType,
                                                             _pAggregatedOrderList,
                                                             getDataGroupId()) 
                  <= WARNING && _pAggregatedOrderList )
               {
                  setContainer( IFASTBP_PROC::AGGREGATED_ORDER_LIST, _pAggregatedOrderList );
               }
            }
            else if ( idSearch == IFASTBP_PROC::PENDING_TRADE )
            {
               AggregatedOrder * pAggregatedOrder =
                     dynamic_cast <AggregatedOrder*> (getCBOItem( IFASTBP_PROC::AGGREGATED_ORDER_LIST, idDataGroup ));

               if( pAggregatedOrder )
               {
                  PendingTradeList *pPendingTradeList = NULL;

                  if ( pAggregatedOrder->getPendingTradeList (pPendingTradeList, idDataGroup) <= WARNING &&
                        pPendingTradeList)
                  {

                     PendingTradeList *pOldContainer = NULL;
                     pOldContainer = 
                        (PendingTradeList*)( const_cast <AggregatedOrderProcess*> ( this ) )->getPtrForContainer(IFASTBP_PROC::PENDING_TRADE,idDataGroup );

                     if (pOldContainer != NULL)
                     {
                        setContainer(IFASTBP_PROC::PENDING_TRADE, NULL);
                     }

                     if( pPendingTradeList )
                     {
                        setContainer(IFASTBP_PROC::PENDING_TRADE, pPendingTradeList);
                     }
                  }
               }
            }
         }
         break;
         case SEARCH_NEXT_BLOCK:
         {
            if( idSearch == IFASTBP_PROC::AGGREGATED_ORDER_LIST )
            {
               if( _pAggregatedOrderList != NULL )
               {
                  sevRtn = _pAggregatedOrderList->getMore();
               }
            }
            else if ( idSearch == IFASTBP_PROC::PENDING_TRADE )
            {
               const BFDataGroupId& idDataGroup = getDataGroupId();
               AggregatedOrder * pAggregatedOrder = 
                  dynamic_cast <AggregatedOrder*> (getCBOItem( IFASTBP_PROC::AGGREGATED_ORDER_LIST, idDataGroup ));

               PendingTradeList *pPendingTradeList = NULL ;

               if( pAggregatedOrder )
               {
                  if ( pAggregatedOrder->getPendingTradeList (pPendingTradeList, idDataGroup) <= WARNING &&
                        pPendingTradeList)
                  {
                     sevRtn = pPendingTradeList->getMore();
                  }
               }
            }
         }
         default:
            break;
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, 
         PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************
bool AggregatedOrderProcess::doOk(GenericInterface *rpGICaller)
{
   setParameter( CONFPROC::PARM_CALLED_FROM, I_("AggregatedOrder") );
   return( true );
}

//******************************************************************************
SEVERITY AggregatedOrderProcess::getHistoricalParameters ( const BFContainerId &idContainer, 
                                                            BFFieldId &recordIdField, 
                                                            DString &tableId, 
                                                            DString &dstrKeys
                                                          ) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS
                         );

	recordIdField = ifds::AggrOrdId;
	tableId = AUDITTYPE::OMNBUS;
	dstrKeys = NULL_STRING;
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AggregatedOrderProcess::getHistoricalParameters ( const BFContainerId &idContainer, 
                                                            HISTORICAL_VECTOR &vectorHistorical
                                                          )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS
                         );
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AggregatedOrderProcess.cpp-arc  $
// 
//    Rev 1.25   Mar 05 2009 00:05:54   dchatcha
// IN 1395049 - Not returning all the pending trades, introduced 'More' button for pending trade part of Aggregated order screen.
// 
//    Rev 1.24   Jan 12 2006 15:39:30   zhengcon
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Aggregate Order
// 
//    Rev 1.23   Oct 05 2005 10:37:10   AGUILAAM
// PET1286_FN02_Verification of Aggregated Order Fund Price
// 
//    Rev 1.22   May 27 2005 15:45:16   ZHANGCEL
// Incident #297240 -- Set AGGR_ORDER_NUMBER paremeter to fix the problem launching AggregatedOrderDlg from Message screen
// 
//    Rev 1.21   May 04 2005 16:46:50   hernando
// Incident 303637 - Added parameter, DisableMsg.
// 
//    Rev 1.20   Apr 19 2005 14:51:04   ZHANGCEL
// Incident #288887 -- Add a new field WarnMsgCode to deal with the warning message issue.
// 
//    Rev 1.19   Mar 07 2005 11:08:24   ZHANGCEL
// Incident #258348 -- Refresh button should be disable when change variance severty from ERROR to WARNING
// 
//    Rev 1.18   Mar 04 2005 14:01:40   popescu
// Incident 248320, refresh the pending trades list for the current aggregated order
// 
//    Rev 1.17   Mar 03 2005 15:38:18   ZHANGCEL
// Magic #248320 -- When <Modify> button get hit, should force to refresh the backend date
// 
//    Rev 1.16   Feb 22 2005 15:13:36   ZHANGCEL
// Incident #248320 -- Disable <Refresh> button on Confirmation screen for AggaregatedOrder
// 
//    Rev 1.15   Feb 08 2005 18:32:18   zhangcel
// PTS 10038581 (Magic order #18337 ) -- Fix <OK>, <Cancel>,<Reset> button issue.
// 
//    Rev 1.14   Feb 02 2005 15:51:30   zhangcel
// PTS Ticket 10038398 -- fix crash when hit <Cancel> on Confirmation Screen
// 
//    Rev 1.13   Feb 02 2005 10:02:00   popescu
// PTS 10038398, put some fixes related to 'Cancel' the confirmation 
// 
//    Rev 1.12   Jan 27 2005 15:48:26   zhangcel
// PTS ticket 10038328 -- Pop up an error window after user tip <Refresh> button
// 
//    Rev 1.11   Jan 14 2005 15:10:02   zhangcel
// PET1117-FN08 -- Fix currency display issue
// 
//    Rev 1.10   Dec 22 2004 17:13:24   zhangcel
// PET1117 - FN 08 -- Added logic to refresh Pending Trade list when user click ModifyTrade button
// 
//    Rev 1.9   Dec 20 2004 14:46:28   zhangcel
// PET 1117 FN 08 -- PENDING_TRADE_LIST should not be updateable.
// 
//    Rev 1.7   Dec 15 2004 18:47:14   zhangcel
// PET 1117 - FN08 -- Code  clean up
// 
//    Rev 1.6   Dec 10 2004 13:57:00   zhangcel
// PET1117 FN8 -- Refresh PendingTrade list issue
// 
//    Rev 1.5   Dec 09 2004 17:57:00   zhangcel
// PET1117-FN08 -- More code for the enhancement
// 
//    Rev 1.4   Dec 08 2004 12:44:08   zhangcel
// PET1117-FN08 More code for the enhancement
// 
//    Rev 1.3   Dec 07 2004 09:50:54   zhangcel
// PET1117 - FN8 -- Added PerformeSearch 
// 
//    Rev 1.2   Dec 06 2004 11:39:52   zhangcel
// PET1117 FN8 -- More code for the enhancement
// 
//    Rev 1.1   Nov 26 2004 14:46:44   zhangcel
// PET1117/FN8 -- Aggregated Order related changes
// 
//    Rev 1.0   Nov 18 2004 17:21:46   zhangcel
// Initial revision.
// 

 */
