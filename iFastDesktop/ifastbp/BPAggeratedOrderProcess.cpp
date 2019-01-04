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
//    Copyright 2005 by IFDS, Inc.
//
//******************************************************************************
//
// ^FILE   : BPAggregatedOrderProcess.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 01 /14/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BPAggregatedOrderProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "bpaggeratedorderprocess.hpp"
#include <ifastcbo\AggregatedOrder.hpp>
#include <ifastcbo\AggregatedOrderlist.hpp>
#include <ifastcbo\PendingTradeList.hpp>
#include "AggregatedOrderProcessInclude.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BPAGGREGATED_ORDER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BPAggregatedOrderProcess > processCreator( CMD_BPROC_BPAGGREGATED_ORDER );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME					= I_( "AggregatedOrderProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long BP_ERR_AGGREGATED_ORDER_NOT_FOUND;
   extern const long BP_ERR_MULTI_AGGREGATED_ORDER;

}


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFIntegerFieldId LossCount;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId Recalculate; 
   extern CLASS_IMPORT const BFTextFieldId Currency;
}
namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const AGGREGATED_ORDER_INFORMATION;
}
//******************************************************************************
//              Public Methods
//******************************************************************************
BPAggregatedOrderProcess::BPAggregatedOrderProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

	addContainer( IFASTBP_PROC::AGGREGATED_ORDER_LIST, true,//repeatable
									BF::NullContainerId, true //updatable
                           ,I_( "AggregatedOrder" )
									);
    
	addFieldDetails( ifds::AggregateOption, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::OmnibusID, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::FundCode, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::ClassCode, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
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
	addFieldDetails( ifds::FundIDType, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::FundIDValue, IFASTBP_PROC::AGGREGATED_ORDER_LIST );
	addFieldDetails( ifds::Currency, IFASTBP_PROC::AGGREGATED_ORDER_LIST );


	//addFieldDetails( ifds::NumberOfTrade, IFASTBP_PROC::AGGREGATED_ORDER_LIST, SUBCLASS_PROCESS);
	addFieldDetails(ifds::ModUser,           IFASTBP_PROC::AGGREGATED_ORDER_LIST );	
	addFieldDetails(ifds::ModDate,           IFASTBP_PROC::AGGREGATED_ORDER_LIST );	
	addFieldDetails(ifds::ProcessDate,       IFASTBP_PROC::AGGREGATED_ORDER_LIST );	
	addFieldDetails(ifds::Username,          IFASTBP_PROC::AGGREGATED_ORDER_LIST );		
}



//******************************************************************************

BPAggregatedOrderProcess::~BPAggregatedOrderProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME )
   
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY BPAggregatedOrderProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString netWorkId,fundBrkKvNum,fundIDType,fundIdValue,
           transType,amount,amountType,routingRef;
   getParameter(I_("NetWorkID"), netWorkId);
   getParameter(I_("FundBrkKvNum"), fundBrkKvNum);
   getParameter(I_("FundIDType"), fundIDType);
   getParameter(I_("FundIDValue"), fundIdValue);
   getParameter(I_("TransType"), transType);
   getParameter(I_("Amount"), amount);
   getParameter(I_("AmountType"), amountType);
   getParameter(I_("RoutingRef"), routingRef);
   transType.strip().upperCase();
   try
   {
      AggregatedOrderList*  pAggregatedOrderList = NULL;
      DString searchType = routingRef.strip().upperCase()==NULL_STRING?I_("KVNum"):I_("ROUTREF");
	      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( pDSTCWorkSession->getAggregatedOrderList( NULL_STRING, NULL_STRING, 
         NULL_STRING,
      NULL_STRING, NULL_STRING, NULL_STRING, routingRef,searchType,
      pAggregatedOrderList, getDataGroupId(),I_("N"),NULL_STRING,true,
      fundBrkKvNum,fundIDType,fundIdValue,amountType,amount,transType         
      )<= WARNING && pAggregatedOrderList )
      {
		  setContainer( IFASTBP_PROC::AGGREGATED_ORDER_LIST, pAggregatedOrderList );

        BFObjIter iter( *pAggregatedOrderList, BF::HOST );
        int iNum  = iter.getNumberOfItemsInList( );
        if(iNum > 1)
        {
			 ADDCONDITIONFROMFILE( CND::BP_ERR_MULTI_AGGREGATED_ORDER );        
        }
        else if( iNum <1 )
        {
			 ADDCONDITIONFROMFILE( CND::BP_ERR_AGGREGATED_ORDER_NOT_FOUND );        
        }
        else
        {
           // according to Winnie, the status should be set to PRICE_LOADED
           // the change here will make CBO dirty, the assumption is that API will be always update...
           iter.getObject()->setField(ifds::OrdStatus,I_( "04" ),getDataGroupId(),false);

         // correct result

        }
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
E_COMMANDRETURN BPAggregatedOrderProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_MODELESS_INPROCESS;
   return rtn;
}
//******************************************************************************
bool BPAggregatedOrderProcess::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{
   return false;
}
//*******************************************************************************
bool BPAggregatedOrderProcess::doOk( GenericInterface* rpGICaller )
{

    const DString* curKey = &( getFirstListItemKey( this,
                                                   IFASTBP_PROC::AGGREGATED_ORDER_LIST
                                                   ) );
   if(curKey )
   {

      AggregatedOrder* rpPtr = dynamic_cast<AggregatedOrder *>( 
                     getCBOItem( IFASTBP_PROC::AGGREGATED_ORDER_LIST, getDataGroupId() ) );
      if( rpPtr && rpPtr->isUpdatedForDataGroup( getDataGroupId() ) )
      {
         rpPtr->ForceToDoCalculation( getDataGroupId() );
         PendingTradeList* pTrade = NULL;
	      rpPtr->getPendingTradeList( pTrade, getDataGroupId());
         setField(this,ifds::OrdStatus, I_("05"), false);
         setField(this,ifds::Recalculate, I_("Y"), false);
      }
   }
   return true;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/*/ 

 */
