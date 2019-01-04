#pragma once



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
//
//******************************************************************************
//
// ^FILE   : AggregatedOrder.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 13/07/2004
//
// ^CLASS    : AggregatedOrder
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <srcprag.h>

class BFData;

class MgmtCoOptions;
class PendingTradeList;
class AggregatedOrderList;
class PendingTradeList;
class PendingTradeDetails;
class TradeSearchCriteria;
class FundFeeList;
class FundBrokerFeeList;
class FundMgmtSettlementInstrList;
class FundBrokerSettlementInstrList;
class DateValidation;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif



class IFASTCBO_LINKAGE AggregatedOrder : public MFCanBFCbo, private boost::noncopyable
{
public:
	AggregatedOrder( BFAbstractCBO &parent );
	virtual ~AggregatedOrder();
	SEVERITY init( const BFData& data ); 
	void doInitData( const BFDataGroupId& idDataGroup );

   SEVERITY doValidateField( const BFFieldId& idField,
                             const DString& strValue,
                             const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

   SEVERITY ForceToDoCalculation(const BFDataGroupId& idDataGroup );
	int getNumberOfLossTrade( const BFDataGroupId& idDataGroup );
  
	SEVERITY getAggregatedOrderPendingTrades ( PendingTradeList *pPendingTradesList,
                                              const DString &aggregatedOrderTradeDate,
                                              const BFDataGroupId &idDataGroup);

	SEVERITY getPendingTradeList( PendingTradeList *&pPendingList, const BFDataGroupId& idDataGroup);
	SEVERITY SetReadOnlyForUpdateingFields( const BFDataGroupId& idDataGroup, bool bReadOnly );
	SEVERITY SettlInstrCodeRelatedChanges(const BFDataGroupId& idDataGroup);
	SEVERITY PriceTypeRelatedChanges(const BFDataGroupId& idDataGroup);
	SEVERITY StatusRelatedChanges(const BFDataGroupId& idDataGroup);
	virtual void getField ( const BFFieldId &idField, 
                           DString &fieldValue, 
                           const BFDataGroupId &idDataGroup, 
                           bool formattedReturn = false
                         ) const;
   virtual SEVERITY setField ( const BFFieldId &idField, 
                               const DString &dstrValue,
                               const BFDataGroupId &idDataGroup, 
                               bool bFormatted = true, 
                               bool bSideEffect = false, 
                               bool bCheckCurrentValue = true);
   SEVERITY getDateValidation ( DateValidation *&pDateValidation, 
                                         const DString &validationType,
                                         const DString &tradeDate, 
                                         const BFDataGroupId &idDataGroup);
protected:
   // private member functions
   SEVERITY getFundFeeList(FundFeeList *&pFundFeeList, const DString feeCode, const BFDataGroupId& idDataGroup);
	
	SEVERITY validateStatusPriceBrkSettlAmtUnits( const BFDataGroupId& idDataGroup );
	SEVERITY ValidateOrdStatus( const DString& strValue, const BFDataGroupId& idDataGroup);
	SEVERITY validateAggrPriceType( const DString& strValue, const BFDataGroupId& idDataGroup);
	SEVERITY getFndMgmtSettlementInstrList(  FundMgmtSettlementInstrList *&pFundMgmtSettlementInstrList, 
																		    const BFDataGroupId& idDataGroup);
	SEVERITY getSettlementInstrList(  FundBrokerSettlementInstrList *&pSettlementInstrList, 
																		    const BFDataGroupId& idDataGroup);
	SEVERITY setSettleAccountNum( const BFDataGroupId& idDataGroup );
	SEVERITY setSttlLocationAndInstr( const BFDataGroupId& idDataGroup );
	virtual void doReset( const BFDataGroupId &idDataGroup );
	SEVERITY setDecimalForAmount( DString& strValue, const BFDataGroupId& idDataGroup );
	SEVERITY setDecimalForBrkSettlAmtUnits( DString& strValue,const BFDataGroupId& idDataGroup );
	SEVERITY setCuculatedFields(const BFDataGroupId& idDataGroup );
	SEVERITY CalculatBrkSettlAmt(const BFDataGroupId& idDataGroup, bool bRaiseError = false  );
private:
   SEVERITY matchingValues(const BFFieldId& idField,const DString& strValue,long lCondition,int iType);
   SEVERITY validateTradeDate (const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY setTradeDateOnEachPendingTrade ( PendingTradeList *pPendingList,
                                             PendingTradeDetails *pPendingTradeDetails,
                                             const DString &aggregatedOrderTradeDate, 
                                             const BFDataGroupId &idDataGroup);
	SEVERITY setSecRecFileIndicator(const BFDataGroupId& idDataGroup);
    void setSubstituteValueForOrderStatus( const BFDataGroupId &idDataGroup);
    bool isSetlLocationChanged( const BFDataGroupId& idDataGroup );
    bool isOrderAlreadyCancelled( const BFDataGroupId& idDataGroup );
    SEVERITY cancelRequestedStatusRelatedChanges(const BFDataGroupId& idDataGroup);

   AggregatedOrderList     *pList;
	int m_iNumberOfLossTrade;
	FundBrokerList *pFundBrokerList;
	DString _oldOrdStatus;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AggregatedOrder.hpp-arc  $
//
//   Rev 1.19   Jul 27 2011 11:01:24   wp040027
//PET P0186065 - Aggregated Amount Orders via Swift- Enable 'Orig Amt' field to allow user to enter broker confirmed amount
//
//   Rev 1.18   Jan 12 2006 15:21:16   zhengcon
//PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Aggregate Order
//
//   Rev 1.17   Oct 13 2005 12:39:28   AGUILAAM
//PET1286_FN01: additional fix
//
//   Rev 1.16   Aug 18 2005 16:49:36   fengyong
//Incident 379172 - call view 324 calculate settleAmt/Units
//
//   Rev 1.15   Aug 05 2005 14:17:00   Fengyong
//Incident 366368 - If settledate set to null then use T+2 as the settledate
//
//   Rev 1.14   May 30 2005 22:30:58   popescu
//Incident# 317930 - modified the getPendingTradeWithLoss method to also return the trades with errors whem trade date is set.
//
//   Rev 1.13   Apr 29 2005 11:15:14   popescu
//Incident 279739, no need for bFromAPI boolean.
//
//   Rev 1.12   Apr 25 2005 15:19:28   yingbaol
//Incident 279739, the version has not been saved???
//
//   Rev 1.11   Apr 25 2005 15:17:08   yingbaol
//Incident279739: add bFromAPI_ variable.
//
//   Rev 1.10   Apr 25 2005 15:14:34   yingbaol
//Incident279739: sync. up 1.7.1.1
//
//   Rev 1.9   Mar 23 2005 18:12:42   ZHANGCEL
//Incident #267769 -- Remove useless code and accelate the performance
//
//   Rev 1.8   Mar 10 2005 09:46:28   popescu
//PET 1190/04, trade date aggregated order update
//
//   Rev 1.7   Feb 03 2005 17:40:20   zhangcel
//Sync up to 1.5.1.1
//
//   Rev 1.6   Jan 26 2005 11:01:30   yingbaol
//PET1117 FN67 enhance Aggregate order for API
//
//   Rev 1.5   Dec 17 2004 12:38:10   zhangcel
//PET 1117 FN 08 -- Add three new function for the Amount decimal setting
//
//   Rev 1.4   Dec 15 2004 19:06:38   zhangcel
//PET1117 FN 08 -- More code enhancement
//
//   Rev 1.3   Dec 08 2004 17:17:52   popescu
//PET 1117/06, build the loss pending trades list
//
//   Rev 1.2   Dec 03 2004 17:06:26   zhangcel
//PET 1117 FN 08 -- More logic implemented
//
//   Rev 1.1   Nov 19 2004 14:11:38   zhangcel
//PET 1117 FN08 -- Bug fix for getPendingTradeList
//
//   Rev 1.0   Nov 18 2004 13:56:34   zhangcel
//Initial revision.
//
 */