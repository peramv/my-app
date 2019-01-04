// Data Field Factory Function
// TIMBUK3: This file was generated by Timbuk3 - Version 2.4.1
// TIMBUK3: Generated on : Mon Aug 24 16:00:00 2015

#include "stdafx.h"




#include <bfdata/bfdatafield.hpp>
#include <bfdata/bfdataid.hpp>

namespace ifds
{
   extern const BFTextFieldId ShrFndBrkExist;
   extern const BFTextFieldId FrSettlInstrCode;
   extern const BFTextFieldId FrAcctSettlLocCode;
   extern const BFTextFieldId ToAcctSettlLocCode;
   extern const BFTextFieldId ToSettlInstrCode;
   extern const BFTextFieldId RqdRefresh;
   extern const BFTextFieldId rxOmnibusId;
   extern const BFTextFieldId rxFundBroker;
   extern const BFDateFieldId BrkSettlDate;
   extern const BFDecimalFieldId BrkSettlAmtUnits;
   extern const BFTextFieldId BrkSettlPUD;
   extern const BFDecimalFieldId AFTBenefit;
   extern const BFDecimalFieldId ExternCharge;
   extern const BFDecimalFieldId RebateRate;
   extern const BFTextFieldId rxOrdStatus;
   extern const BFDecimalFieldId NAV;
   extern const BFTextFieldId DeliveryTo;
   extern const BFTextFieldId ForAccount;
   extern const BFTextFieldId SettlInstrCode;
   extern const BFNumericFieldId ExtNtwkRef;
   extern const BFTextFieldId ExtNtwkType;
   extern const BFNumericFieldId AggrOrdId;
   extern const BFNumericFieldId AggrOrdVer;
   extern const BFTextFieldId ClrSettlMethod;
   extern const BFTextFieldId Recalculate;
   extern const BFTextFieldId RemarksAggr;
   extern const BFDataId DSTC0324_VW;
   extern const BFDataId DSTC0324_REQ;
   extern const BFTextFieldId RoutingRef;
   extern const BFTextFieldId rxRoutingRef;
   extern const BFDecimalFieldId OrigFeeRate;
   extern const BFTextFieldId FeeCharge;
   extern const BFTextFieldId OrigFeeCharge;
   extern const BFDataId DSTC0311_REQ;
   extern const BFDataId DSTC0311_VW;
   extern const BFDecimalFieldId ConditionRate;
   extern const BFDecimalFieldId ClntSettlAmt;
   extern const BFDecimalFieldId BrkSettlAmt;
   extern const BFDecimalFieldId TxnFee;
   extern const BFTextFieldId AggregatedOrderListHeading;
   extern const BFTextFieldId AggrOrderPendingTradeListHeading;
   extern const BFTextFieldId FundBrokerSearchCriteria;
   extern const BFTextFieldId FundBrokerUsing;
   extern const BFTextFieldId FundBrokerLabel;
   extern const BFTextFieldId FundBrokerSearchCriteriaNo;
   extern const BFTextFieldId FundBrokerIDType;
   extern const BFDataId DSTC0322_REQ;
   extern const BFDataId DSTC0322_VW;
   extern const BFTextFieldId SetFundToInvestr;
   extern const BFDataId DSTC0326_REQ;
   extern const BFDataId DSTC0326_VW;
   extern const BFDataId DSTC0326_VWRepeat_Record;
   extern const BFTextFieldId FundMgmtSettleInstrHeadingSet;
   extern const BFTextFieldId SettlementInstrCode;
   extern const BFTextFieldId DefaultSettlementInstr;
   extern const BFIntegerFieldId SettlementInstrVersion;
   extern const BFNumericFieldId SettlementInstrRid;
   extern const BFTextFieldId ClearingMethod;
   extern const BFDataId DSTC0317_REQ;
   extern const BFDataId DSTC0317_VW;
   extern const BFDataId DSTC0317_VWRepeat_Record;
   extern const BFDataId DSTC0318_REQ;
   extern const BFDataId DSTC0318_REQRepeat_Record;
   extern const BFDataId DSTC0318_VW;
   extern const BFTextFieldId SettlementInstrHeadingSet;
   extern const BFTextFieldId SettlementInstrDesc;
   extern const BFIntegerFieldId SettlementInstrID;
   extern const BFTextFieldId ShrFundBrokerHeading;
   extern const BFTextFieldId IsDefault;
   extern const BFIntegerFieldId FundBrokerEligID;
   extern const BFDataId DSTC0327_REQ;
   extern const BFDataId DSTC0327_VW;
   extern const BFDataId DSTC0327_VWRepeat_Record;
   extern const BFDataId DSTC0328_REQRepeat_Record;
   extern const BFDataId DSTC0328_REQ;
   extern const BFDataId DSTC0328_VW;
   extern const BFTextFieldId LocationLevel;
   extern const BFIntegerFieldId LossCount;
   extern const BFIntegerFieldId NewAggrOrdVer;
   extern const BFTextFieldId AggrPriceType;
   extern const BFTextFieldId AggregateSearchCriteria;
   extern const BFTextFieldId AggregateSearchUsing;
   extern const BFTextFieldId AggregateSearchCriteriaNo;
   extern const BFTextFieldId AggregateSearchLabel;
   extern const BFTextFieldId SearchLabel5;
   extern const BFTextFieldId SearchLabel6;
   extern const BFTextFieldId SearchLabel7;
   extern const BFTextFieldId SearchFieldCriteria5;
   extern const BFTextFieldId SearchFieldCriteria6;
   extern const BFTextFieldId SearchFieldCriteria7;
   extern const BFDataId DSTC0325_REQ;
   extern const BFDataId DSTC0325_VW;
   extern const BFDataId DSTC0321_REQ;
   extern const BFDataId DSTC0321_VW;
   extern const BFDataId DSTC0321_VWRepeat_Record;
   extern const BFTextFieldId FundBrokerName;
   extern const BFIntegerFieldId NumberOfTrade;
   extern const BFTextFieldId StatusPriceBrkSettlAmtUnits;
   extern const BFTextFieldId AllEntitys;
   extern const BFTextFieldId TaxEpost;
   extern const BFTextFieldId LetEpost;
   extern const BFTextFieldId CertEpost;
   extern const BFTextFieldId DivConfEpost;
   extern const BFTextFieldId DivChqEpost;
   extern const BFTextFieldId ContrEPost;
   extern const BFTextFieldId RegEpost;
   extern const BFTextFieldId AnnlRptsEpost;
   extern const BFTextFieldId ProspEpost;
   extern const BFTextFieldId BenEpost;
   extern const BFTextFieldId StmtEpost;
   extern const BFTextFieldId DupStmtEpost;
   extern const BFTextFieldId NFConfEpost;
   extern const BFTextFieldId TxnConfEpost;
   extern const BFTextFieldId DupConfEpost;
   extern const BFTextFieldId SemiAnnualEpost;
   extern const BFTextFieldId ContributionSuppress;
   extern const BFTextFieldId ContributionWaive;
   extern const BFTextFieldId ContributionMail;
   extern const BFTextFieldId ContributionFax;
   extern const BFTextFieldId ContributionCD;
   extern const BFTextFieldId ContributionEmail;
   extern const BFTextFieldId ContributionEpost;
   extern const BFTextFieldId ContributionAddr;
   extern const BFTextFieldId ContributionOnHold;
   extern const BFTextFieldId EPost;
   extern const BFTextFieldId RedCodeFlatPercentXEdit;
   extern const BFTextFieldId Changed;
   extern const BFTextFieldId TransModPerm;
   extern const BFTextFieldId TransFeesListHeadingSet;
   extern const BFTextFieldId PayMethodFileProc;
   extern const BFTextFieldId FromFundClass;
   extern const BFTextFieldId ToFundClass;
   extern const BFTextFieldId FundClassTradeType;
   extern const BFTextFieldId Type;
   extern const BFTextFieldId AllAmtTypes;
   extern const BFTextFieldId FundIDType;
   extern const BFTextFieldId FundIDValue;
   extern const BFTextFieldId FundBrkKVNum;
   extern const BFTextFieldId EntityAddressSearchUsing;
   extern const BFTextFieldId EntityAddressListHeading;
   extern const BFTextFieldId ValidNetworkType;
   extern const BFTextFieldId OtherConfirmType;
   extern const BFDecimalFieldId ExternalPrice;
   extern const BFDateFieldId ExternalSettleDate;
   extern const BFDecimalFieldId ExternalSettleAmt;
   extern const BFTextFieldId LossWarnMsg;
   extern const BFTextFieldId EntityAddrSrch;
   extern const BFTextFieldId ParticipantID;
   extern const BFTextFieldId NetworkTypeUpd;
   extern const BFTextFieldId AMSRebalanceUpdateable;
   extern const BFTextFieldId TrxnFee;
   extern const BFTextFieldId EntityAloneHeading;
   extern const BFDateFieldId TaxJurisDeff;
   extern const BFTextFieldId EUSDTaxOption;
   extern const BFTextFieldId UpdShrTaxJuris;
   extern const BFDecimalFieldId DiscountAmount;
   extern const BFDataId DSTC0329_VW;
   extern const BFDataId DSTC0329_REQ;
   extern const BFDataId DSTC0329_VWRepeat_Record;
   extern const BFNumericFieldId InvDetlId;
   extern const BFDecimalFieldId BasedOnValue;
   extern const BFDecimalFieldId ChargedAmount;
   extern const BFDataFieldProperties s_FldProp_ShrFndBrkExist;
   extern const BFDataFieldProperties s_FldProp_FrSettlInstrCode;
   extern const BFDataFieldProperties s_FldProp_FrAcctSettlLocCode;
   extern const BFDataFieldProperties s_FldProp_ToAcctSettlLocCode;
   extern const BFDataFieldProperties s_FldProp_ToSettlInstrCode;
   extern const BFDataFieldProperties s_FldProp_RqdRefresh;
   extern const BFDataFieldProperties s_FldProp_rxOmnibusId;
   extern const BFDataFieldProperties s_FldProp_rxFundBroker;
   extern const BFDataFieldProperties s_FldProp_BrkSettlDate;
   extern const BFDataFieldProperties s_FldProp_BrkSettlAmtUnits;
   extern const BFDataFieldProperties s_FldProp_BrkSettlPUD;
   extern const BFDataFieldProperties s_FldProp_AFTBenefit;
   extern const BFDataFieldProperties s_FldProp_ExternCharge;
   extern const BFDataFieldProperties s_FldProp_RebateRate;
   extern const BFDataFieldProperties s_FldProp_rxOrdStatus;
   extern const BFDataFieldProperties s_FldProp_NAV;
   extern const BFDataFieldProperties s_FldProp_DeliveryTo;
   extern const BFDataFieldProperties s_FldProp_ForAccount;
   extern const BFDataFieldProperties s_FldProp_SettlInstrCode;
   extern const BFDataFieldProperties s_FldProp_ExtNtwkRef;
   extern const BFDataFieldProperties s_FldProp_ExtNtwkType;
   extern const BFDataFieldProperties s_FldProp_AggrOrdId;
   extern const BFDataFieldProperties s_FldProp_AggrOrdVer;
   extern const BFDataFieldProperties s_FldProp_ClrSettlMethod;
   extern const BFDataFieldProperties s_FldProp_Recalculate;
   extern const BFDataFieldProperties s_FldProp_RemarksAggr;
   extern const BFDataFieldProperties s_FldProp_DSTC0324_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0324_REQ;
   extern const BFDataFieldProperties s_FldProp_RoutingRef;
   extern const BFDataFieldProperties s_FldProp_rxRoutingRef;
   extern const BFDataFieldProperties s_FldProp_OrigFeeRate;
   extern const BFDataFieldProperties s_FldProp_FeeCharge;
   extern const BFDataFieldProperties s_FldProp_OrigFeeCharge;
   extern const BFDataFieldProperties s_FldProp_DSTC0311_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0311_VW;
   extern const BFDataFieldProperties s_FldProp_ConditionRate;
   extern const BFDataFieldProperties s_FldProp_ClntSettlAmt;
   extern const BFDataFieldProperties s_FldProp_BrkSettlAmt;
   extern const BFDataFieldProperties s_FldProp_TxnFee;
   extern const BFDataFieldProperties s_FldProp_AggregatedOrderListHeading;
   extern const BFDataFieldProperties s_FldProp_AggrOrderPendingTradeListHeading;
   extern const BFDataFieldProperties s_FldProp_FundBrokerSearchCriteria;
   extern const BFDataFieldProperties s_FldProp_FundBrokerUsing;
   extern const BFDataFieldProperties s_FldProp_FundBrokerLabel;
   extern const BFDataFieldProperties s_FldProp_FundBrokerSearchCriteriaNo;
   extern const BFDataFieldProperties s_FldProp_FundBrokerIDType;
   extern const BFDataFieldProperties s_FldProp_DSTC0322_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0322_VW;
   extern const BFDataFieldProperties s_FldProp_SetFundToInvestr;
   extern const BFDataFieldProperties s_FldProp_DSTC0326_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0326_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0326_VWRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_FundMgmtSettleInstrHeadingSet;
   extern const BFDataFieldProperties s_FldProp_SettlementInstrCode;
   extern const BFDataFieldProperties s_FldProp_DefaultSettlementInstr;
   extern const BFDataFieldProperties s_FldProp_SettlementInstrVersion;
   extern const BFDataFieldProperties s_FldProp_SettlementInstrRid;
   extern const BFDataFieldProperties s_FldProp_ClearingMethod;
   extern const BFDataFieldProperties s_FldProp_DSTC0317_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0317_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0317_VWRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_DSTC0318_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0318_REQRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_DSTC0318_VW;
   extern const BFDataFieldProperties s_FldProp_SettlementInstrHeadingSet;
   extern const BFDataFieldProperties s_FldProp_SettlementInstrDesc;
   extern const BFDataFieldProperties s_FldProp_SettlementInstrID;
   extern const BFDataFieldProperties s_FldProp_ShrFundBrokerHeading;
   extern const BFDataFieldProperties s_FldProp_IsDefault;
   extern const BFDataFieldProperties s_FldProp_FundBrokerEligID;
   extern const BFDataFieldProperties s_FldProp_DSTC0327_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0327_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0327_VWRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_DSTC0328_REQRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_DSTC0328_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0328_VW;
   extern const BFDataFieldProperties s_FldProp_LocationLevel;
   extern const BFDataFieldProperties s_FldProp_LossCount;
   extern const BFDataFieldProperties s_FldProp_NewAggrOrdVer;
   extern const BFDataFieldProperties s_FldProp_AggrPriceType;
   extern const BFDataFieldProperties s_FldProp_AggregateSearchCriteria;
   extern const BFDataFieldProperties s_FldProp_AggregateSearchUsing;
   extern const BFDataFieldProperties s_FldProp_AggregateSearchCriteriaNo;
   extern const BFDataFieldProperties s_FldProp_AggregateSearchLabel;
   extern const BFDataFieldProperties s_FldProp_SearchLabel5;
   extern const BFDataFieldProperties s_FldProp_SearchLabel6;
   extern const BFDataFieldProperties s_FldProp_SearchLabel7;
   extern const BFDataFieldProperties s_FldProp_SearchFieldCriteria5;
   extern const BFDataFieldProperties s_FldProp_SearchFieldCriteria6;
   extern const BFDataFieldProperties s_FldProp_SearchFieldCriteria7;
   extern const BFDataFieldProperties s_FldProp_DSTC0325_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0325_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0321_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0321_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0321_VWRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_FundBrokerName;
   extern const BFDataFieldProperties s_FldProp_NumberOfTrade;
   extern const BFDataFieldProperties s_FldProp_StatusPriceBrkSettlAmtUnits;
   extern const BFDataFieldProperties s_FldProp_AllEntitys;
   extern const BFDataFieldProperties s_FldProp_TaxEpost;
   extern const BFDataFieldProperties s_FldProp_LetEpost;
   extern const BFDataFieldProperties s_FldProp_CertEpost;
   extern const BFDataFieldProperties s_FldProp_DivConfEpost;
   extern const BFDataFieldProperties s_FldProp_DivChqEpost;
   extern const BFDataFieldProperties s_FldProp_ContrEPost;
   extern const BFDataFieldProperties s_FldProp_RegEpost;
   extern const BFDataFieldProperties s_FldProp_AnnlRptsEpost;
   extern const BFDataFieldProperties s_FldProp_ProspEpost;
   extern const BFDataFieldProperties s_FldProp_BenEpost;
   extern const BFDataFieldProperties s_FldProp_StmtEpost;
   extern const BFDataFieldProperties s_FldProp_DupStmtEpost;
   extern const BFDataFieldProperties s_FldProp_NFConfEpost;
   extern const BFDataFieldProperties s_FldProp_TxnConfEpost;
   extern const BFDataFieldProperties s_FldProp_DupConfEpost;
   extern const BFDataFieldProperties s_FldProp_SemiAnnualEpost;
   extern const BFDataFieldProperties s_FldProp_ContributionSuppress;
   extern const BFDataFieldProperties s_FldProp_ContributionWaive;
   extern const BFDataFieldProperties s_FldProp_ContributionMail;
   extern const BFDataFieldProperties s_FldProp_ContributionFax;
   extern const BFDataFieldProperties s_FldProp_ContributionCD;
   extern const BFDataFieldProperties s_FldProp_ContributionEmail;
   extern const BFDataFieldProperties s_FldProp_ContributionEpost;
   extern const BFDataFieldProperties s_FldProp_ContributionAddr;
   extern const BFDataFieldProperties s_FldProp_ContributionOnHold;
   extern const BFDataFieldProperties s_FldProp_EPost;
   extern const BFDataFieldProperties s_FldProp_RedCodeFlatPercentXEdit;
   extern const BFDataFieldProperties s_FldProp_Changed;
   extern const BFDataFieldProperties s_FldProp_TransModPerm;
   extern const BFDataFieldProperties s_FldProp_TransFeesListHeadingSet;
   extern const BFDataFieldProperties s_FldProp_PayMethodFileProc;
   extern const BFDataFieldProperties s_FldProp_FromFundClass;
   extern const BFDataFieldProperties s_FldProp_ToFundClass;
   extern const BFDataFieldProperties s_FldProp_FundClassTradeType;
   extern const BFDataFieldProperties s_FldProp_Type;
   extern const BFDataFieldProperties s_FldProp_AllAmtTypes;
   extern const BFDataFieldProperties s_FldProp_FundIDType;
   extern const BFDataFieldProperties s_FldProp_FundIDValue;
   extern const BFDataFieldProperties s_FldProp_FundBrkKVNum;
   extern const BFDataFieldProperties s_FldProp_EntityAddressSearchUsing;
   extern const BFDataFieldProperties s_FldProp_EntityAddressListHeading;
   extern const BFDataFieldProperties s_FldProp_ValidNetworkType;
   extern const BFDataFieldProperties s_FldProp_OtherConfirmType;
   extern const BFDataFieldProperties s_FldProp_ExternalPrice;
   extern const BFDataFieldProperties s_FldProp_ExternalSettleDate;
   extern const BFDataFieldProperties s_FldProp_ExternalSettleAmt;
   extern const BFDataFieldProperties s_FldProp_LossWarnMsg;
   extern const BFDataFieldProperties s_FldProp_EntityAddrSrch;
   extern const BFDataFieldProperties s_FldProp_ParticipantID;
   extern const BFDataFieldProperties s_FldProp_NetworkTypeUpd;
   extern const BFDataFieldProperties s_FldProp_AMSRebalanceUpdateable;
   extern const BFDataFieldProperties s_FldProp_TrxnFee;
   extern const BFDataFieldProperties s_FldProp_EntityAloneHeading;
   extern const BFDataFieldProperties s_FldProp_TaxJurisDeff;
   extern const BFDataFieldProperties s_FldProp_EUSDTaxOption;
   extern const BFDataFieldProperties s_FldProp_UpdShrTaxJuris;
   extern const BFDataFieldProperties s_FldProp_DiscountAmount;
   extern const BFDataFieldProperties s_FldProp_DSTC0329_VW;
   extern const BFDataFieldProperties s_FldProp_DSTC0329_REQ;
   extern const BFDataFieldProperties s_FldProp_DSTC0329_VWRepeat_Record;
   extern const BFDataFieldProperties s_FldProp_InvDetlId;
   extern const BFDataFieldProperties s_FldProp_BasedOnValue;
   extern const BFDataFieldProperties s_FldProp_ChargedAmount;
   BFDataField* createField_24( const BFFieldId id )
   {
      BFDataField* pField = NULL;
      switch( id.getId() )
      {
         case 40004801: pField = new BFTextField_1( ShrFndBrkExist, &s_FldProp_ShrFndBrkExist ); break; 
         case 40004804: pField = new BFTextField_60( FrSettlInstrCode, &s_FldProp_FrSettlInstrCode ); break; 
         case 40004805: pField = new BFTextField_60( FrAcctSettlLocCode, &s_FldProp_FrAcctSettlLocCode ); break; 
         case 40004806: pField = new BFTextField_60( ToAcctSettlLocCode, &s_FldProp_ToAcctSettlLocCode ); break; 
         case 40004807: pField = new BFTextField_60( ToSettlInstrCode, &s_FldProp_ToSettlInstrCode ); break; 
         case 40004811: pField = new BFTextField_1( RqdRefresh, &s_FldProp_RqdRefresh ); break; 
         case 40004812: pField = new BFTextField_60( rxOmnibusId, &s_FldProp_rxOmnibusId ); break; 
         case 40004813: pField = new BFTextField_60( rxFundBroker, &s_FldProp_rxFundBroker ); break; 
         case 40004814: pField = new BFDateField( BrkSettlDate, &s_FldProp_BrkSettlDate ); break; 
         case 40004815: pField = new BFDecimalField( BrkSettlAmtUnits, &s_FldProp_BrkSettlAmtUnits ); break; 
         case 40004816: pField = new BFTextField_60( BrkSettlPUD, &s_FldProp_BrkSettlPUD ); break; 
         case 40004817: pField = new BFDecimalField( AFTBenefit, &s_FldProp_AFTBenefit ); break; 
         case 40004818: pField = new BFDecimalField( ExternCharge, &s_FldProp_ExternCharge ); break; 
         case 40004819: pField = new BFDecimalField( RebateRate, &s_FldProp_RebateRate ); break; 
         case 40004820: pField = new BFTextField_60( rxOrdStatus, &s_FldProp_rxOrdStatus ); break; 
         case 40004821: pField = new BFDecimalField( NAV, &s_FldProp_NAV ); break; 
         case 40004822: pField = new BFTextField_60( DeliveryTo, &s_FldProp_DeliveryTo ); break; 
         case 40004823: pField = new BFTextField_60( ForAccount, &s_FldProp_ForAccount ); break; 
         case 40004825: pField = new BFTextField_60( SettlInstrCode, &s_FldProp_SettlInstrCode ); break; 
         case 40004826: pField = new BFNumericField( ExtNtwkRef, &s_FldProp_ExtNtwkRef ); break; 
         case 40004827: pField = new BFTextField_60( ExtNtwkType, &s_FldProp_ExtNtwkType ); break; 
         case 40004828: pField = new BFNumericField( AggrOrdId, &s_FldProp_AggrOrdId ); break; 
         case 40004829: pField = new BFNumericField( AggrOrdVer, &s_FldProp_AggrOrdVer ); break; 
         case 40004830: pField = new BFTextField_60( ClrSettlMethod, &s_FldProp_ClrSettlMethod ); break; 
         case 40004832: pField = new BFTextField_1( Recalculate, &s_FldProp_Recalculate ); break; 
         case 40004833: pField = new BFTextField<180>( RemarksAggr, &s_FldProp_RemarksAggr ); break; 
         case 40004836: pField = new BFTextField_60( RoutingRef, &s_FldProp_RoutingRef ); break; 
         case 40004837: pField = new BFTextField_60( rxRoutingRef, &s_FldProp_rxRoutingRef ); break; 
         case 40004838: pField = new BFDecimalField( OrigFeeRate, &s_FldProp_OrigFeeRate ); break; 
         case 40004839: pField = new BFTextField_1( FeeCharge, &s_FldProp_FeeCharge ); break; 
         case 40004840: pField = new BFTextField_1( OrigFeeCharge, &s_FldProp_OrigFeeCharge ); break; 
         case 40004844: pField = new BFDecimalField( ConditionRate, &s_FldProp_ConditionRate ); break; 
         case 40004845: pField = new BFDecimalField( ClntSettlAmt, &s_FldProp_ClntSettlAmt ); break; 
         case 40004846: pField = new BFDecimalField( BrkSettlAmt, &s_FldProp_BrkSettlAmt ); break; 
         case 40004848: pField = new BFDecimalField( TxnFee, &s_FldProp_TxnFee ); break; 
         case 40004851: pField = new BFTextField_60( AggregatedOrderListHeading, &s_FldProp_AggregatedOrderListHeading ); break; 
         case 40004852: pField = new BFTextField_60( AggrOrderPendingTradeListHeading, &s_FldProp_AggrOrderPendingTradeListHeading ); break; 
         case 40004853: pField = new BFTextField_60( FundBrokerSearchCriteria, &s_FldProp_FundBrokerSearchCriteria ); break; 
         case 40004854: pField = new BFTextField_60( FundBrokerUsing, &s_FldProp_FundBrokerUsing ); break; 
         case 40004855: pField = new BFTextField_60( FundBrokerLabel, &s_FldProp_FundBrokerLabel ); break; 
         case 40004856: pField = new BFTextField_60( FundBrokerSearchCriteriaNo, &s_FldProp_FundBrokerSearchCriteriaNo ); break; 
         case 40004857: pField = new BFTextField_60( FundBrokerIDType, &s_FldProp_FundBrokerIDType ); break; 
         case 40004860: pField = new BFTextField_1( SetFundToInvestr, &s_FldProp_SetFundToInvestr ); break; 
         case 40004866: pField = new BFTextField_60( FundMgmtSettleInstrHeadingSet, &s_FldProp_FundMgmtSettleInstrHeadingSet ); break; 
         case 40004867: pField = new BFTextField<3>( SettlementInstrCode, &s_FldProp_SettlementInstrCode ); break; 
         case 40004869: pField = new BFTextField_1( DefaultSettlementInstr, &s_FldProp_DefaultSettlementInstr ); break; 
         case 40004873: pField = new BFIntegerField( SettlementInstrVersion, &s_FldProp_SettlementInstrVersion ); break; 
         case 40004874: pField = new BFNumericField( SettlementInstrRid, &s_FldProp_SettlementInstrRid ); break; 
         case 40004875: pField = new BFTextField_60( ClearingMethod, &s_FldProp_ClearingMethod ); break; 
         case 40004885: pField = new BFTextField_60( SettlementInstrHeadingSet, &s_FldProp_SettlementInstrHeadingSet ); break; 
         case 40004886: pField = new BFTextField_60( SettlementInstrDesc, &s_FldProp_SettlementInstrDesc ); break; 
         case 40004887: pField = new BFIntegerField( SettlementInstrID, &s_FldProp_SettlementInstrID ); break; 
         case 40004888: pField = new BFTextField_60( ShrFundBrokerHeading, &s_FldProp_ShrFundBrokerHeading ); break; 
         case 40004889: pField = new BFTextField_1( IsDefault, &s_FldProp_IsDefault ); break; 
         case 40004890: pField = new BFIntegerField( FundBrokerEligID, &s_FldProp_FundBrokerEligID ); break; 
         case 40004902: pField = new BFTextField_10( LocationLevel, &s_FldProp_LocationLevel ); break; 
         case 40004904: pField = new BFIntegerField( LossCount, &s_FldProp_LossCount ); break; 
         case 40004905: pField = new BFIntegerField( NewAggrOrdVer, &s_FldProp_NewAggrOrdVer ); break; 
         case 40004906: pField = new BFTextField_60( AggrPriceType, &s_FldProp_AggrPriceType ); break; 
         case 40004907: pField = new BFTextField_60( AggregateSearchCriteria, &s_FldProp_AggregateSearchCriteria ); break; 
         case 40004908: pField = new BFTextField_60( AggregateSearchUsing, &s_FldProp_AggregateSearchUsing ); break; 
         case 40004909: pField = new BFTextField_60( AggregateSearchCriteriaNo, &s_FldProp_AggregateSearchCriteriaNo ); break; 
         case 40004910: pField = new BFTextField_60( AggregateSearchLabel, &s_FldProp_AggregateSearchLabel ); break; 
         case 40004911: pField = new BFTextField_60( SearchLabel5, &s_FldProp_SearchLabel5 ); break; 
         case 40004912: pField = new BFTextField_60( SearchLabel6, &s_FldProp_SearchLabel6 ); break; 
         case 40004913: pField = new BFTextField_60( SearchLabel7, &s_FldProp_SearchLabel7 ); break; 
         case 40004914: pField = new BFTextField_60( SearchFieldCriteria5, &s_FldProp_SearchFieldCriteria5 ); break; 
         case 40004915: pField = new BFTextField_60( SearchFieldCriteria6, &s_FldProp_SearchFieldCriteria6 ); break; 
         case 40004916: pField = new BFTextField_60( SearchFieldCriteria7, &s_FldProp_SearchFieldCriteria7 ); break; 
         case 40004923: pField = new BFTextField_60( FundBrokerName, &s_FldProp_FundBrokerName ); break; 
         case 40004924: pField = new BFIntegerField( NumberOfTrade, &s_FldProp_NumberOfTrade ); break; 
         case 40004925: pField = new BFTextField_60( StatusPriceBrkSettlAmtUnits, &s_FldProp_StatusPriceBrkSettlAmtUnits ); break; 
         case 40004926: pField = new BFTextField_1( AllEntitys, &s_FldProp_AllEntitys ); break; 
         case 40004928: pField = new BFTextField_2( TaxEpost, &s_FldProp_TaxEpost ); break; 
         case 40004930: pField = new BFTextField_2( LetEpost, &s_FldProp_LetEpost ); break; 
         case 40004931: pField = new BFTextField_2( CertEpost, &s_FldProp_CertEpost ); break; 
         case 40004932: pField = new BFTextField_2( DivConfEpost, &s_FldProp_DivConfEpost ); break; 
         case 40004933: pField = new BFTextField_2( DivChqEpost, &s_FldProp_DivChqEpost ); break; 
         case 40004934: pField = new BFTextField_2( ContrEPost, &s_FldProp_ContrEPost ); break; 
         case 40004935: pField = new BFTextField_2( RegEpost, &s_FldProp_RegEpost ); break; 
         case 40004936: pField = new BFTextField_2( AnnlRptsEpost, &s_FldProp_AnnlRptsEpost ); break; 
         case 40004937: pField = new BFTextField_2( ProspEpost, &s_FldProp_ProspEpost ); break; 
         case 40004938: pField = new BFTextField_2( BenEpost, &s_FldProp_BenEpost ); break; 
         case 40004939: pField = new BFTextField_2( StmtEpost, &s_FldProp_StmtEpost ); break; 
         case 40004940: pField = new BFTextField_2( DupStmtEpost, &s_FldProp_DupStmtEpost ); break; 
         case 40004941: pField = new BFTextField_2( NFConfEpost, &s_FldProp_NFConfEpost ); break; 
         case 40004942: pField = new BFTextField_2( TxnConfEpost, &s_FldProp_TxnConfEpost ); break; 
         case 40004943: pField = new BFTextField_2( DupConfEpost, &s_FldProp_DupConfEpost ); break; 
         case 40004944: pField = new BFTextField_2( SemiAnnualEpost, &s_FldProp_SemiAnnualEpost ); break; 
         case 40004945: pField = new BFTextField_2( ContributionSuppress, &s_FldProp_ContributionSuppress ); break; 
         case 40004946: pField = new BFTextField_2( ContributionWaive, &s_FldProp_ContributionWaive ); break; 
         case 40004947: pField = new BFTextField_10( ContributionMail, &s_FldProp_ContributionMail ); break; 
         case 40004948: pField = new BFTextField_2( ContributionFax, &s_FldProp_ContributionFax ); break; 
         case 40004949: pField = new BFTextField_2( ContributionCD, &s_FldProp_ContributionCD ); break; 
         case 40004950: pField = new BFTextField_2( ContributionEmail, &s_FldProp_ContributionEmail ); break; 
         case 40004951: pField = new BFTextField_2( ContributionEpost, &s_FldProp_ContributionEpost ); break; 
         case 40004952: pField = new BFTextField<20>( ContributionAddr, &s_FldProp_ContributionAddr ); break; 
         case 40004953: pField = new BFTextField_2( ContributionOnHold, &s_FldProp_ContributionOnHold ); break; 
         case 40004954: pField = new BFTextField_2( EPost, &s_FldProp_EPost ); break; 
         case 40004955: pField = new BFTextField_1( RedCodeFlatPercentXEdit, &s_FldProp_RedCodeFlatPercentXEdit ); break; 
         case 40004956: pField = new BFTextField_10( Changed, &s_FldProp_Changed ); break; 
         case 40004958: pField = new BFTextField_1( TransModPerm, &s_FldProp_TransModPerm ); break; 
         case 40004959: pField = new BFTextField_60( TransFeesListHeadingSet, &s_FldProp_TransFeesListHeadingSet ); break; 
         case 40004960: pField = new BFTextField_60( PayMethodFileProc, &s_FldProp_PayMethodFileProc ); break; 
         case 40004961: pField = new BFTextField_60( FromFundClass, &s_FldProp_FromFundClass ); break; 
         case 40004962: pField = new BFTextField_60( ToFundClass, &s_FldProp_ToFundClass ); break; 
         case 40004963: pField = new BFTextField_60( FundClassTradeType, &s_FldProp_FundClassTradeType ); break; 
         case 40004964: pField = new BFTextField_10( Type, &s_FldProp_Type ); break; 
         case 40004965: pField = new BFTextField_60( AllAmtTypes, &s_FldProp_AllAmtTypes ); break; 
         case 40004966: pField = new BFTextField<20>( FundIDType, &s_FldProp_FundIDType ); break; 
         case 40004967: pField = new BFTextField<40>( FundIDValue, &s_FldProp_FundIDValue ); break; 
         case 40004968: pField = new BFTextField<40>( FundBrkKVNum, &s_FldProp_FundBrkKVNum ); break; 
         case 40004969: pField = new BFTextField_60( EntityAddressSearchUsing, &s_FldProp_EntityAddressSearchUsing ); break; 
         case 40004970: pField = new BFTextField_60( EntityAddressListHeading, &s_FldProp_EntityAddressListHeading ); break; 
         case 40004971: pField = new BFTextField_60( ValidNetworkType, &s_FldProp_ValidNetworkType ); break; 
         case 40004972: pField = new BFTextField_60( OtherConfirmType, &s_FldProp_OtherConfirmType ); break; 
         case 40004973: pField = new BFDecimalField( ExternalPrice, &s_FldProp_ExternalPrice ); break; 
         case 40004974: pField = new BFDateField( ExternalSettleDate, &s_FldProp_ExternalSettleDate ); break; 
         case 40004975: pField = new BFDecimalField( ExternalSettleAmt, &s_FldProp_ExternalSettleAmt ); break; 
         case 40004976: pField = new BFTextField_60( LossWarnMsg, &s_FldProp_LossWarnMsg ); break; 
         case 40004977: pField = new BFTextField_60( EntityAddrSrch, &s_FldProp_EntityAddrSrch ); break; 
         case 40004978: pField = new BFTextField_60( ParticipantID, &s_FldProp_ParticipantID ); break; 
         case 40004982: pField = new BFTextField_1( NetworkTypeUpd, &s_FldProp_NetworkTypeUpd ); break; 
         case 40004983: pField = new BFTextField_1( AMSRebalanceUpdateable, &s_FldProp_AMSRebalanceUpdateable ); break; 
         case 40004984: pField = new BFTextField_60( TrxnFee, &s_FldProp_TrxnFee ); break; 
         case 40004985: pField = new BFTextField_60( EntityAloneHeading, &s_FldProp_EntityAloneHeading ); break; 
         case 40004986: pField = new BFDateField( TaxJurisDeff, &s_FldProp_TaxJurisDeff ); break; 
         case 40004987: pField = new BFTextField<40>( EUSDTaxOption, &s_FldProp_EUSDTaxOption ); break; 
         case 40004988: pField = new BFTextField_2( UpdShrTaxJuris, &s_FldProp_UpdShrTaxJuris ); break; 
         case 40004990: pField = new BFDecimalField( DiscountAmount, &s_FldProp_DiscountAmount ); break; 
         case 40004998: pField = new BFNumericField( InvDetlId, &s_FldProp_InvDetlId ); break; 
         case 40004999: pField = new BFDecimalField( BasedOnValue, &s_FldProp_BasedOnValue ); break; 
      }
      return pField;
   }
}
