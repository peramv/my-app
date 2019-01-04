
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Pending Trade Details view.
 * For additional view information see <A HREF="../../../../viewspecs/PendingTradeDetails.doc">PendingTradeDetails.doc</A>.
 * 
 * @author RTS Generated
 */
public class PendingTradeDetailsView extends IFastView implements Serializable
{

   /**
    * BrokerCode member variable.
    */
   private String _BrokerCode = null;
   
   /**
    * BranchCode member variable.
    */
   private String _BranchCode = null;
   
   /**
    * SalesRepCode member variable.
    */
   private String _SlsrepCode = null;
   
   /**
    * Settlement Currency member variable.
    */
   private String _SettleCurrency = null;
   
   /**
    * Settlement Currency Name member variable.
    */
   private String _SettleCurrName = null;
   
   /**
    * Exchange Rate member variable.
    */
   private String _ExchRate = null;
   
   /**
    * Fee Amount or Percentage member variable.
    */
   private String _Fee = null;
   
   /**
    * Flat or Percentage member variable.
    */
   private Boolean _FlatPercent = null;
   
   /**
    * Fee Currency member variable.
    */
   private String _FeeCurrency = null;
   
   /**
    * Back End Load Fee member variable.
    */
   private Boolean _BELFee = null;
   
   /**
    * Adminstration Fee member variable.
    */
   private String _AdminFeeAmt = null;
   
   /**
    * Override DSC Code member variable.
    */
   private String _OverrideDSC = null;
   
   /**
    * Override DSC Descrption member variable.
    */
   private String _OverrideDSCDesc = null;
   
   /**
    * Override Amount member variable.
    */
   private String _OverrideAmt = null;
   
   /**
    * Override Tax member variable.
    */
   private Boolean _OverrideTax = null;
   
   /**
    * Federal Tax Rate member variable.
    */
   private String _FedTaxRate = null;
   
   /**
    * Federal Tax Percent/Flat member variable.
    */
   private String _FedTaxPUD = null;
   
   /**
    * Provincial Tax  Rate member variable.
    */
   private String _ProvTaxRate = null;
   
   /**
    * Provincial Tax Percent/Flat member variable.
    */
   private String _ProvTaxPUD = null;
   
   /**
    * Province of Sales member variable.
    */
   private String _ProvSales = null;
   
   /**
    * Name of Province of Sales member variable.
    */
   private String _ProvSalesName = null;
   
   /**
    * Deposit Type member variable.
    */
   private Integer _DepositType = null;
   
   /**
    * Deposit Type Description member variable.
    */
   private String _DepositTypeDesc = null;
   
   /**
    * Redemption Code member variable.
    */
   private String _RedCode = null;
   
   /**
    * Redemption Code Description member variable.
    */
   private String _RedCodeDesc = null;
   
   /**
    * Payment member variable.
    */
   private String _Payment = null;
   
   /**
    * Payment Type member variable.
    */
   private String _PayType = null;
   
   /**
    * Payment Type Description member variable.
    */
   private String _PayTypeDesc = null;
   
   /**
    * Address Code member variable.
    */
   private String _AddrCode = null;
   
   /**
    * Address Line 1 member variable.
    */
   private String _AddrLine = null;
   
   /**
    * Cheque Suppress Code member variable.
    */
   private String _ChqSupCode = null;
   
   /**
    * Cheque Suppress Code Description member variable.
    */
   private String _ChqSupCodeDesc = null;
   
   /**
    * Order Source member variable.
    */
   private String _OrderSource = null;
   
   /**
    * Order Source Description member variable.
    */
   private String _OrderSrcDesc = null;
   
   /**
    * Settlement Source member variable.
    */
   private String _SettleSource = null;
   
   /**
    * Settlement Source Description member variable.
    */
   private String _SettleSrcDesc = null;
   
   /**
    * Source of Fund member variable.
    */
   private String _SrcOfFund = null;
   
   /**
    * Source of Fund Description member variable.
    */
   private String _SrcOfFundDesc = null;
   
   /**
    * Source of Account member variable.
    */
   private String _SrcOfAccount = null;
   
   /**
    * Settlement Type member variable.
    */
   private String _SettleType = null;
   
   /**
    * Settlement Type Desc member variable.
    */
   private String _SettleTypeDesc = null;
   
   /**
    * Expected to Settle in Gross/Net member variable.
    */
   private String _ExpGNSettle = null;
   
   /**
    * Settlement By member variable.
    */
   private String _SettledBy = null;
   
   /**
    * Settlement By Description member variable.
    */
   private String _SettledByDesc = null;
   
   /**
    * Round Flag member variable.
    */
   private String _RoundFlag = null;
   
   /**
    * Round Flag Description member variable.
    */
   private String _RoundFlagDesc = null;
   
   /**
    * Credit Frequency for GIC purchase member variable.
    */
   private String _CreditFreq = null;
   
   /**
    * Credit Frequency Description member variable.
    */
   private String _CreditFreqDesc = null;
   
   /**
    * Extra Commission member variable.
    */
   private Boolean _ExtraCommission = null;
   
   /**
    * Certificate Required member variable.
    */
   private Boolean _CertRequired = null;
   
   /**
    * Certificate Issued member variable.
    */
   private Boolean _CertIssued = null;
   
   /**
    * Confirmation Required member variable.
    */
   private Boolean _ConfirmReq = null;
   
   /**
    * Show On Statement member variable.
    */
   private Boolean _OnStmt = null;
   
   /**
    * Tax/Contribution Receipt Issued member variable.
    */
   private Boolean _RecptIssued = null;
   
   /**
    * Exclude MFCS trade from MFCS settlemt member variable.
    */
   private Boolean _ExclMFCSSettle = null;
   
   /**
    * Guarantee Date for Seg Product member variable.
    */
   private Date _GuaranteeDate = null;
   
   /**
    * Maturity  Date for GIC purchase member variable.
    */
   private Date _MaturityDate = null;
   
   /**
    * GIC Interest Rate member variable.
    */
   private String _InterestRate = null;
   
   /**
    * Broker's Name member variable.
    */
   private String _BrokerName = null;
   
   /**
    * Branch's Name member variable.
    */
   private String _BranchName = null;
   
   /**
    * Salesrep's Name member variable.
    */
   private String _SlsrepName = null;
   
   /**
    * Salserep Alternate Name member variable.
    */
   private String _SlsrepAltName = null;
   
   /**
    * Deposit ID member variable.
    */
   private String _DepId = null;
   
   /**
    * Remarks Line 1 member variable.
    */
   private String _Remarks1 = null;
   
   /**
    * Remarks Line 2 member variable.
    */
   private String _Remarks2 = null;
   
   /**
    * Remarks Line 3 member variable.
    */
   private String _Remarks3 = null;
   
   /**
    * Reject Code member variable.
    */
   private String _RejCode = null;
   
   /**
    * Reject Code Description member variable.
    */
   private String _RejCodeDesc = null;
   
   /**
    * Accountable Code member variable.
    */
   private String _Accountable = null;
   
   /**
    * Accountable Code Description member variable.
    */
   private String _AcctableDesc = null;
   
   /**
    * Date Stamp member variable.
    */
   private Date _DateStamp = null;
   
   /**
    * Time Stamp member variable.
    */
   private String _TimeStamp = null;
   
   /**
    * Record Created On member variable.
    */
   private Date _ProcessDate = null;
   
   /**
    * Allocation Trade member variable.
    */
   private Boolean _Allocation = null;
   
   /**
    * Cansim Rate member variable.
    */
   private String _CansimRate = null;
   
   /**
    * Initial purchase - yes/no member variable.
    */
   private Boolean _InitPurch = null;
   
   /**
    * BackDated Reason Code member variable.
    */
   private String _BackDatedReason = null;
   
   /**
    * Split Commissions Exist member variable.
    */
   private Boolean _SplitComm = null;
   
   /**
    * Deal Date member variable.
    */
   private Date _DealDate = null;
   
   /**
    * Deal Time member variable.
    */
   private String _DealTime = null;
   
   /**
    * DSC Override Code member variable.
    */
   private String _DSCOverrideCode = null;
   
   /**
    * DSC Override Amount member variable.
    */
   private String _DSCOverrideAmt = null;
   
   /**
    * Account To member variable.
    */
   private String _AccountTo = null;
   
   /**
    * Fund To member variable.
    */
   private String _FundTo = null;
   
   /**
    * Class To Code member variable.
    */
   private String _ClassToCode = null;
   
   /**
    * Transaction Type member variable.
    */
   private String _rxTransType = null;
   
   /**
    * Fund From Code member variable.
    */
   private String _rxFundCode = null;
   
   /**
    * Class From Code member variable.
    */
   private String _rxClassCode = null;
   
   /**
    * Amount member variable.
    */
   private String _Amount = null;
   
   /**
    * Amount Type - dollars or percent member variable.
    */
   private String _AmountType = null;
   
   /**
    * Gross or Net member variable.
    */
   private String _GrossOrNet = null;
   
   /**
    * Use Entered Fee member variable.
    */
   private Boolean _UseEnteredFee = null;
   
   /**
    * Fee on In side of Exchange member variable.
    */
   private String _ExchInFee = null;
   
   /**
    * Fee on In side of Exchange is Flat (yes) Percentage (no) member variable.
    */
   private Boolean _ExchInFlatPercent = null;
   
   /**
    * Allow user to modify trade member variable.
    */
   private String _ModPerm = null;
   
   /**
    * Acct Owner's First Name member variable.
    */
   private String _FirstName = null;
   
   /**
    * Acct Owner's Last Name member variable.
    */
   private String _LastName = null;
   
   /**
    * Initial Purchase Description member variable.
    */
   private String _InitPurchDesc = null;
   
   /**
    * Confirm Required Description member variable.
    */
   private String _ConfirmReqDesc = null;
   
   /**
    * Receipt Issued Description member variable.
    */
   private String _RecptIssuedDesc = null;
   
   /**
    * Baycom Number member variable.
    */
   private String _Baycom = null;
   
   /**
    * Baycom Number of FundTo and ClassTo member variable.
    */
   private String _BaycomTo = null;
   
   /**
    * Bank Charge member variable.
    */
   private String _BankCharge = null;
   
   /**
    * Value Date member variable.
    */
   private Date _ValueDate = null;
   
   /**
    * Pay Method member variable.
    */
   private String _PayMethod = null;
   
   /**
    * ACH Processor member variable.
    */
   private String _ACHProcessor = null;
   
   /**
    * ToAccount Agency Code member variable.
    */
   private String _ToBrokerCode = null;
   
   /**
    * ToAccount Agent Code member variable.
    */
   private String _ToSlsRepCode = null;
   
   /**
    * Network ID for SWIFT/Vestima/ FundSettle trades member variable.
    */
   private String _NetworkID = null;
   
   /**
    * Babel Reference Number at trade level member variable.
    */
   private String _ExtTransNum = null;
   
   /**
    * Sender's Reference Number from MT502 member variable.
    */
   private String _SendRefNum = null;
   
   /**
    * Participant's Reference Number from MT502 member variable.
    */
   private String _PartRefNum = null;
   
   /**
    * Master Ref Number from MT502 member variable.
    */
   private String _MasterRefNum = null;
   
   /**
    * Exchange Out Fee member variable.
    */
   private String _ExchOutFee = null;
   
   /**
    * Exchange Out Flat/Prcnt member variable.
    */
   private Boolean _ExchOutFlatPrcnt = null;
   
   /**
    * Early PW/ShortTerm Transfer Fees member variable.
    */
   private Boolean _ChargeERSTTRFee = null;
   
   /**
    * Flag indicating if Withdrawal Fees are to be changed on Redemption member variable.
    */
   private Boolean _ChargeWDFee = null;
   
   /**
    * Mirror Transaction Number member variable.
    */
   private Integer _MirTransNum = null;
   
   /**
    * BorrowedFunds member variable.
    */
   private Boolean _BorrowedFunds = null;
   
   /**
    * Transaction Sequence member variable.
    */
   private Integer _TransSeq = null;
   
   /**
    * From Settle Location Code member variable.
    */
   private String _FrSettlLocCode = null;
   
   /**
    * From Delivery To member variable.
    */
   private String _FrDeliveryTo = null;
   
   /**
    * From Settlement Location Description member variable.
    */
   private String _FrSettlLocDescription = null;
   
   /**
    * From In Favour of member variable.
    */
   private String _FrInfavourOf = null;
   
   /**
    * From For Account member variable.
    */
   private String _FrForAccount = null;
   
   /**
    * From Clearing Method member variable.
    */
   private String _FrClearingMethod = null;
   
   /**
    * To Settle Location Code member variable.
    */
   private String _ToSettlLocCode = null;
   
   /**
    * To Delivery To member variable.
    */
   private String _ToFrDeliveryTo = null;
   
   /**
    * To Settlement Location Description member variable.
    */
   private String _ToSettlLocDescription = null;
   
   /**
    * To Infavour of member variable.
    */
   private String _ToInFavourOf = null;
   
   /**
    * To for Account member variable.
    */
   private String _ToForAccount = null;
   
   /**
    * To Clearing Method member variable.
    */
   private String _ToClearingMethod = null;
   
   /**
    * Exchange In Fee from New Money Transfer member variable.
    */
   private String _IFeeTo = null;
   
   /**
    * Charge ALD Fee member variable.
    */
   private String _ChargeADLFee = null;
   
   /**
    * LSIFCode member variable.
    */
   private String _LSIFCode = null;
   
   /**
    * Alternate Account member variable.
    */
   private String _AltAccount = null;
   
   /**
    * Other Reference Number member variable.
    */
   private String _RefNum = null;
   
   /**
    * Fund WKN member variable.
    */
   private String _FundWKN = null;
   
   /**
    * FundISIN member variable.
    */
   private String _FundISIN = null;
   
   /**
    * Fund To WKN member variable.
    */
   private String _FundToWKN = null;
   
   /**
    * Fund To ISIN member variable.
    */
   private String _FundToISIN = null;
   
   /**
    * Acquisition Fee Option member variable.
    */
   private String _AcqFeeOption = null;
   
   /**
    * SettleDate is Overriden member variable.
    */
   private Boolean _SettleDateOverriden = null;
   
   /**
    * From Settlement Instruction Code member variable.
    */
   private String _FrSettlInstrCode = null;
   
   /**
    * To Settlement Instruction Code member variable.
    */
   private String _ToSettlInstrCode = null;
   
   /**
    * Fund Broker member variable.
    */
   private String _FundBroker = null;
   
   /**
    * Aggregation Option member variable.
    */
   private String _AggrOption = null;
   
   /**
    * Broker Settlement Date member variable.
    */
   private Date _BrkSettlDate = null;
   
   /**
    * Other Confirm Type member variable.
    */
   private String _OtherConfirmType = null;
   
   /**
    * External Price member variable.
    */
   private String _ExternalPrice = null;
   
   /**
    * External Settlement Date member variable.
    */
   private Date _ExternalSettleDate = null;
   
   /**
    * External Settlement Amount member variable.
    */
   private String _ExternalSettleAmt = null;
   
   /**
    * ROA Amount member variable.
    */
   private String _ROAAmount = null;
   
   /**
    * Delivery Method member variable.
    */
   private String _DeliveryMethod = null;
   
   /**
    * Original transaction number member variable.
    */
   private Integer _AdjustForTransNum = null;
   
   /**
    * Transaction ID number member variable.
    */
   private String _TransId = null;
   
   /**
    * SplitComm Rebook TransID member variable.
    */
   private String _SplitCommRebookTransID = null;
   
   /**
    * Average cost per unit member variable.
    */
   private String _EUSDAvgCost = null;
   
   /**
    * TIS Average cost per unit member variable.
    */
   private String _EUSDAvgTIS = null;
   
   /**
    * Flag indicating if cost has been overriden member variable.
    */
   private Boolean _EUSDCostOverride = null;
   
   /**
    * Flag indicating if TIS has been overriden member variable.
    */
   private Boolean _EUSDTISOverride = null;
   
   /**
    * MCH File member variable.
    */
   private String _MCHFile = null;
   
   /**
    * Security Recon File member variable.
    */
   private String _SecReconFile = null;
   
   /**
    * Flag indication if the transaction is to be excluded from N$M file "In" Include, "Ex" exclude member variable.
    */
   private String _ESGSettle = null;
   
   /**
    * NSCC Control Number member variable.
    */
   private String _NSCControlNum = null;
   
   /**
    * Trade Pay Instruct Exists Y/N member variable.
    */
   private Boolean _TradePayInstrExist = null;
   
   /**
    * Payment Instruction Option member variable.
    */
   private String _PayInstructOption = null;
   
   /**
    * MF Payment member variable.
    */
   private String _MFPayment = null;
   
   /**
    * INDC member variable.
    */
   private String _INDC = null;
   
   /**
    * Modification Date member variable.
    */
   private Date _ModDate = null;
   
   /**
    * Modification User member variable.
    */
   private String _ModUser = null;
   
   /**
    * Receipt Status member variable.
    */
   private String _RecptStatus = null;
   
   /**
    * Name of the entity related somehow to the trade like former spouse entity member variable.
    */
   private String _LinkedEntityName = null;
   
   /**
    * ID of the entity related somehow to the trade member variable.
    */
   private String _LinkedEntityId = null;
   
   /**
    * Authorization member variable.
    */
   private String _Authorized = null;
   
   /**
    * Associated Transaction Id member variable.
    */
   private String _AssociatedTransId = null;
   
   /**
    * Grant Repayment Reason member variable.
    */
   private String _GrantRepayReason = null;
   
   /**
    * HRDC Reporting Required member variable.
    */
   private Boolean _NeedToReportHRDC = null;
   
   /**
    * Tax Year member variable.
    */
   private Integer _TaxYear = null;
   
   /**
    * Beneficiary Tainted member variable.
    */
   private Boolean _Tainted = null;
   
   /**
    * Year the overcontribution withdrawal to be applied member variable.
    */
   private Integer _OCRedYear = null;
   
   /**
    * Assisted Contribution Amount member variable.
    */
   private String _AssistedContrAmt = null;
   
   /**
    * Account Owner ID member variable.
    */
   private String _AcctOwnerID = null;
   
   /**
    * Account Owner Name member variable.
    */
   private String _AcctOwnerName = null;
   
   /**
    * Network Response Required member variable.
    */
   private String _NetworkRespRequired = null;
   
   /**
    * EAP CESG Paid member variable.
    */
   private String _EAPCESGPaid = null;
   
   /**
    * Interest Investment UUID member variable.
    */
   private String _IntInvestUUID = null;
   
   /**
    * Investment Number member variable.
    */
   private String _InvestmentNo = null;
   
   /**
    * Investment Status member variable.
    */
   private String _InvestStatus = null;
   
   /**
    * Interest Calculation Method member variable.
    */
   private String _IntCalcMthd = null;
   
   /**
    * Investment Type member variable.
    */
   private String _IntInvestType = null;
   
   /**
    * Term of Investment member variable.
    */
   private Integer _InvestTerm = null;
   
   /**
    * Interest Rate member variable.
    */
   private String _IntRate = null;
   
   /**
    * Maturity Date member variable.
    */
   private Date _GIMaturityDate = null;
   
   /**
    * Interest Credit Frequency member variable.
    */
   private String _IntCredFreq = null;
   
   /**
    * Last Interest Credit Date member variable.
    */
   private Date _LastIntCredDate = null;
   
   /**
    * Additional Amount member variable.
    */
   private String _AddlAmt = null;
   
   /**
    * Commission Reduction Rate member variable.
    */
   private String _CommRedRate = null;
   
   /**
    * Type of Interest Rate member variable.
    */
   private String _IntRateType = null;
   
   /**
    * Investment Id member variable.
    */
   private String _IntInvestId = null;
   
   /**
    * PF Crystalisation member variable.
    */
   private String _PFCrystalisation = null;
   
   /**
    * PendTrd Contract member variable.
    */
   private String _PendTrdContract = null;
   
   /**
    * Valuation Dt member variable.
    */
   private Date _ValuationDt = null;
   
   /**
    * Payment Info member variable.
    */
   private String _PaymentInfo = null;
   
   /**
    * Guarantee Override Flag member variable.
    */
   private String _GuaranteeOverride = null;
   
   /**
    * Redemption Order member variable.
    */
   private String _RedemOrder = null;
   
   /**
    * Right To Cancel member variable.
    */
   private String _RightToCancel = null;
   
   /**
    * RDR Advice member variable.
    */
   private String _RDRAdvice = null;
   
   /**
    * SDRT Reportable member variable.
    */
   private String _SDRTReportable = null;
   
   /**
    * Forced Rate Amount member variable.
    */
   private String _ForcedRateAmt = null;
   
   /**
    * PSD Advice Flag member variable.
    */
   private String _PSDAdvcFlg = null;
   
   /**
    * Pymt Routing Mthd member variable.
    */
   private String _PymtRoutingMthd = null;
   
   /**
    * Event Receipt Date member variable.
    */
   private Date _EventReceiptDate = null;
   
   /**
    * Event Receipt Time member variable.
    */
   private String _EventReceiptTime = null;
   
   /**
    * SourceOfTrade member variable.
    */
   private String _SourceOfTrade = null;
   
   /**
    * ChannelOfTrade member variable.
    */
   private String _ChannelOfTrade = null;
   
   /**
    * Platform member variable.
    */
   private String _Platform = null;
   
   /**
    * Settle Network member variable.
    */
   private String _SettleNetwork = null;
   
   /**
    * Delivery Network member variable.
    */
   private String _DeliveryNetwork = null;
   
   /**
    * Verified member variable.
    */
   private Boolean _Verified = null;
   
   /**
    * VerifiedBy member variable.
    */
   private String _VerifiedBy = null;
   
   /**
    * ToCashMsgType member variable.
    */
   private String _ToCashMsgType = null;
   
   /**
    * ToIntermediaryBank member variable.
    */
   private String _ToIntermediaryBank = null;
   
   /**
    * ToReceivingBank member variable.
    */
   private String _ToReceivingBank = null;
   
   /**
    * ToBeneficiary member variable.
    */
   private String _ToBeneficiary = null;
   
   /**
    * ToSpecialInstructions member variable.
    */
   private String _ToSpecialInstructions = null;
   
   /**
    * ToSettlementAccount member variable.
    */
   private String _ToSettlementAccount = null;
   
   /**
    * ToInternalSettlementAccount member variable.
    */
   private String _ToInternalSettlementAccount = null;
   
   /**
    * FrCashMsgType member variable.
    */
   private String _FrCashMsgType = null;
   
   /**
    * FrIntermediaryBank member variable.
    */
   private String _FrIntermediaryBank = null;
   
   /**
    * FrReceivingBank member variable.
    */
   private String _FrReceivingBank = null;
   
   /**
    * FrBeneficiary member variable.
    */
   private String _FrBeneficiary = null;
   
   /**
    * FrSpecialInstructions member variable.
    */
   private String _FrSpecialInstructions = null;
   
   /**
    * FrSettlementAccount member variable.
    */
   private String _FrSettlementAccount = null;
   
   /**
    * FrInternalSettlementAccount member variable.
    */
   private String _FrInternalSettlementAccount = null;
   
   /**
    * G1Units member variable.
    */
   private String _G1Units = null;
   
   /**
    * G2Units member variable.
    */
   private String _G2Units = null;
   
   /**
    * ExtAccountNum member variable.
    */
   private String _ExtAccountNum = null;
   
   /**
    * AggrType member variable.
    */
   private String _AggrType = null;
   
   /**
    * SrcOfFndsChk member variable.
    */
   private String _SrcOfFndsChk = null;
   

   /**
    * Constructs the PendingTradeDetailsView object.
    * 
    */
   public PendingTradeDetailsView()
   {
      super ( new PendingTradeDetailsRequest() );
   }

   /**
    * Constructs the PendingTradeDetailsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PendingTradeDetailsView( String hostEncoding )
   {
      super ( new PendingTradeDetailsRequest( hostEncoding ) );
   }

   /**
    * Gets the PendingTradeDetailsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PendingTradeDetailsRequest object.
    */
   public final PendingTradeDetailsRequest getRequest()
   {
      return (PendingTradeDetailsRequest)getIFastRequest();
   }
        
   /**
    * Gets the BrokerCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BrokerCode or null.
    */
   public final String getBrokerCode()
   {
      return _BrokerCode;
   }
	
   /**
    * Gets the BrokerCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BrokerCode or the specified default value.
    */
   public final String getBrokerCode( String defaultValue )
   {
      return _BrokerCode == null ? defaultValue : _BrokerCode;
   }
                  
   /**
    * Gets the BranchCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BranchCode or null.
    */
   public final String getBranchCode()
   {
      return _BranchCode;
   }
	
   /**
    * Gets the BranchCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BranchCode or the specified default value.
    */
   public final String getBranchCode( String defaultValue )
   {
      return _BranchCode == null ? defaultValue : _BranchCode;
   }
                  
   /**
    * Gets the SalesRepCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SalesRepCode or null.
    */
   public final String getSlsrepCode()
   {
      return _SlsrepCode;
   }
	
   /**
    * Gets the SalesRepCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SalesRepCode or the specified default value.
    */
   public final String getSlsrepCode( String defaultValue )
   {
      return _SlsrepCode == null ? defaultValue : _SlsrepCode;
   }
                  
   /**
    * Gets the Settlement Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement Currency or null.
    */
   public final String getSettleCurrency()
   {
      return _SettleCurrency;
   }
	
   /**
    * Gets the Settlement Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Currency or the specified default value.
    */
   public final String getSettleCurrency( String defaultValue )
   {
      return _SettleCurrency == null ? defaultValue : _SettleCurrency;
   }
                  
   /**
    * Gets the Settlement Currency Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement Currency Name or null.
    */
   public final String getSettleCurrName()
   {
      return _SettleCurrName;
   }
	
   /**
    * Gets the Settlement Currency Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Currency Name or the specified default value.
    */
   public final String getSettleCurrName( String defaultValue )
   {
      return _SettleCurrName == null ? defaultValue : _SettleCurrName;
   }
                  
   /**
    * Gets the Exchange Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Exchange Rate or null.
    */
   public final String getExchRate()
   {
      return _ExchRate;
   }
	
   /**
    * Gets the Exchange Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Rate or the specified default value.
    */
   public final String getExchRate( String defaultValue )
   {
      return _ExchRate == null ? defaultValue : _ExchRate;
   }
                  
   /**
    * Gets the Fee Amount or Percentage field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee Amount or Percentage or null.
    */
   public final String getFee()
   {
      return _Fee;
   }
	
   /**
    * Gets the Fee Amount or Percentage field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Amount or Percentage or the specified default value.
    */
   public final String getFee( String defaultValue )
   {
      return _Fee == null ? defaultValue : _Fee;
   }
                  
   /**
    * Gets the Flat or Percentage field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flat or Percentage or null.
    */
   public final Boolean getFlatPercent()
   {
      return _FlatPercent;
   }
	
   /**
    * Gets the Flat or Percentage field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flat or Percentage or the specified default value.
    */
   public final boolean getFlatPercent( boolean defaultValue )
   {
      return _FlatPercent == null ? defaultValue : _FlatPercent.booleanValue();
   }
                  
   /**
    * Gets the Fee Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee Currency or null.
    */
   public final String getFeeCurrency()
   {
      return _FeeCurrency;
   }
	
   /**
    * Gets the Fee Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Currency or the specified default value.
    */
   public final String getFeeCurrency( String defaultValue )
   {
      return _FeeCurrency == null ? defaultValue : _FeeCurrency;
   }
                  
   /**
    * Gets the Back End Load Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Back End Load Fee or null.
    */
   public final Boolean getBELFee()
   {
      return _BELFee;
   }
	
   /**
    * Gets the Back End Load Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back End Load Fee or the specified default value.
    */
   public final boolean getBELFee( boolean defaultValue )
   {
      return _BELFee == null ? defaultValue : _BELFee.booleanValue();
   }
                  
   /**
    * Gets the Adminstration Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Adminstration Fee or null.
    */
   public final String getAdminFeeAmt()
   {
      return _AdminFeeAmt;
   }
	
   /**
    * Gets the Adminstration Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Adminstration Fee or the specified default value.
    */
   public final String getAdminFeeAmt( String defaultValue )
   {
      return _AdminFeeAmt == null ? defaultValue : _AdminFeeAmt;
   }
                  
   /**
    * Gets the Override DSC Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Override DSC Code or null.
    */
   public final String getOverrideDSC()
   {
      return _OverrideDSC;
   }
	
   /**
    * Gets the Override DSC Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override DSC Code or the specified default value.
    */
   public final String getOverrideDSC( String defaultValue )
   {
      return _OverrideDSC == null ? defaultValue : _OverrideDSC;
   }
                  
   /**
    * Gets the Override DSC Descrption field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Override DSC Descrption or null.
    */
   public final String getOverrideDSCDesc()
   {
      return _OverrideDSCDesc;
   }
	
   /**
    * Gets the Override DSC Descrption field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override DSC Descrption or the specified default value.
    */
   public final String getOverrideDSCDesc( String defaultValue )
   {
      return _OverrideDSCDesc == null ? defaultValue : _OverrideDSCDesc;
   }
                  
   /**
    * Gets the Override Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Override Amount or null.
    */
   public final String getOverrideAmt()
   {
      return _OverrideAmt;
   }
	
   /**
    * Gets the Override Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Amount or the specified default value.
    */
   public final String getOverrideAmt( String defaultValue )
   {
      return _OverrideAmt == null ? defaultValue : _OverrideAmt;
   }
                  
   /**
    * Gets the Override Tax field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Override Tax or null.
    */
   public final Boolean getOverrideTax()
   {
      return _OverrideTax;
   }
	
   /**
    * Gets the Override Tax field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Tax or the specified default value.
    */
   public final boolean getOverrideTax( boolean defaultValue )
   {
      return _OverrideTax == null ? defaultValue : _OverrideTax.booleanValue();
   }
                  
   /**
    * Gets the Federal Tax Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Federal Tax Rate or null.
    */
   public final String getFedTaxRate()
   {
      return _FedTaxRate;
   }
	
   /**
    * Gets the Federal Tax Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax Rate or the specified default value.
    */
   public final String getFedTaxRate( String defaultValue )
   {
      return _FedTaxRate == null ? defaultValue : _FedTaxRate;
   }
                  
   /**
    * Gets the Federal Tax Percent/Flat field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Federal Tax Percent/Flat or null.
    */
   public final String getFedTaxPUD()
   {
      return _FedTaxPUD;
   }
	
   /**
    * Gets the Federal Tax Percent/Flat field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax Percent/Flat or the specified default value.
    */
   public final String getFedTaxPUD( String defaultValue )
   {
      return _FedTaxPUD == null ? defaultValue : _FedTaxPUD;
   }
                  
   /**
    * Gets the Provincial Tax  Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Provincial Tax  Rate or null.
    */
   public final String getProvTaxRate()
   {
      return _ProvTaxRate;
   }
	
   /**
    * Gets the Provincial Tax  Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax  Rate or the specified default value.
    */
   public final String getProvTaxRate( String defaultValue )
   {
      return _ProvTaxRate == null ? defaultValue : _ProvTaxRate;
   }
                  
   /**
    * Gets the Provincial Tax Percent/Flat field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Provincial Tax Percent/Flat or null.
    */
   public final String getProvTaxPUD()
   {
      return _ProvTaxPUD;
   }
	
   /**
    * Gets the Provincial Tax Percent/Flat field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax Percent/Flat or the specified default value.
    */
   public final String getProvTaxPUD( String defaultValue )
   {
      return _ProvTaxPUD == null ? defaultValue : _ProvTaxPUD;
   }
                  
   /**
    * Gets the Province of Sales field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Province of Sales or null.
    */
   public final String getProvSales()
   {
      return _ProvSales;
   }
	
   /**
    * Gets the Province of Sales field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Province of Sales or the specified default value.
    */
   public final String getProvSales( String defaultValue )
   {
      return _ProvSales == null ? defaultValue : _ProvSales;
   }
                  
   /**
    * Gets the Name of Province of Sales field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Name of Province of Sales or null.
    */
   public final String getProvSalesName()
   {
      return _ProvSalesName;
   }
	
   /**
    * Gets the Name of Province of Sales field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name of Province of Sales or the specified default value.
    */
   public final String getProvSalesName( String defaultValue )
   {
      return _ProvSalesName == null ? defaultValue : _ProvSalesName;
   }
                  
   /**
    * Gets the Deposit Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Deposit Type or null.
    */
   public final Integer getDepositType()
   {
      return _DepositType;
   }
	
   /**
    * Gets the Deposit Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deposit Type or the specified default value.
    */
   public final int getDepositType( int defaultValue )
   {
      return _DepositType == null ? defaultValue : _DepositType.intValue();
   }
                  
   /**
    * Gets the Deposit Type Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Deposit Type Description or null.
    */
   public final String getDepositTypeDesc()
   {
      return _DepositTypeDesc;
   }
	
   /**
    * Gets the Deposit Type Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deposit Type Description or the specified default value.
    */
   public final String getDepositTypeDesc( String defaultValue )
   {
      return _DepositTypeDesc == null ? defaultValue : _DepositTypeDesc;
   }
                  
   /**
    * Gets the Redemption Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemption Code or null.
    */
   public final String getRedCode()
   {
      return _RedCode;
   }
	
   /**
    * Gets the Redemption Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Code or the specified default value.
    */
   public final String getRedCode( String defaultValue )
   {
      return _RedCode == null ? defaultValue : _RedCode;
   }
                  
   /**
    * Gets the Redemption Code Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemption Code Description or null.
    */
   public final String getRedCodeDesc()
   {
      return _RedCodeDesc;
   }
	
   /**
    * Gets the Redemption Code Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Code Description or the specified default value.
    */
   public final String getRedCodeDesc( String defaultValue )
   {
      return _RedCodeDesc == null ? defaultValue : _RedCodeDesc;
   }
                  
   /**
    * Gets the Payment field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment or null.
    */
   public final String getPayment()
   {
      return _Payment;
   }
	
   /**
    * Gets the Payment field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment or the specified default value.
    */
   public final String getPayment( String defaultValue )
   {
      return _Payment == null ? defaultValue : _Payment;
   }
                  
   /**
    * Gets the Payment Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment Type or null.
    */
   public final String getPayType()
   {
      return _PayType;
   }
	
   /**
    * Gets the Payment Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Type or the specified default value.
    */
   public final String getPayType( String defaultValue )
   {
      return _PayType == null ? defaultValue : _PayType;
   }
                  
   /**
    * Gets the Payment Type Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment Type Description or null.
    */
   public final String getPayTypeDesc()
   {
      return _PayTypeDesc;
   }
	
   /**
    * Gets the Payment Type Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Type Description or the specified default value.
    */
   public final String getPayTypeDesc( String defaultValue )
   {
      return _PayTypeDesc == null ? defaultValue : _PayTypeDesc;
   }
                  
   /**
    * Gets the Address Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Code or null.
    */
   public final String getAddrCode()
   {
      return _AddrCode;
   }
	
   /**
    * Gets the Address Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code or the specified default value.
    */
   public final String getAddrCode( String defaultValue )
   {
      return _AddrCode == null ? defaultValue : _AddrCode;
   }
                  
   /**
    * Gets the Address Line 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Address Line 1 or null.
    */
   public final String getAddrLine()
   {
      return _AddrLine;
   }
	
   /**
    * Gets the Address Line 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line 1 or the specified default value.
    */
   public final String getAddrLine( String defaultValue )
   {
      return _AddrLine == null ? defaultValue : _AddrLine;
   }
                  
   /**
    * Gets the Cheque Suppress Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Cheque Suppress Code or null.
    */
   public final String getChqSupCode()
   {
      return _ChqSupCode;
   }
	
   /**
    * Gets the Cheque Suppress Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cheque Suppress Code or the specified default value.
    */
   public final String getChqSupCode( String defaultValue )
   {
      return _ChqSupCode == null ? defaultValue : _ChqSupCode;
   }
                  
   /**
    * Gets the Cheque Suppress Code Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Cheque Suppress Code Description or null.
    */
   public final String getChqSupCodeDesc()
   {
      return _ChqSupCodeDesc;
   }
	
   /**
    * Gets the Cheque Suppress Code Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cheque Suppress Code Description or the specified default value.
    */
   public final String getChqSupCodeDesc( String defaultValue )
   {
      return _ChqSupCodeDesc == null ? defaultValue : _ChqSupCodeDesc;
   }
                  
   /**
    * Gets the Order Source field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Order Source or null.
    */
   public final String getOrderSource()
   {
      return _OrderSource;
   }
	
   /**
    * Gets the Order Source field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Order Source or the specified default value.
    */
   public final String getOrderSource( String defaultValue )
   {
      return _OrderSource == null ? defaultValue : _OrderSource;
   }
                  
   /**
    * Gets the Order Source Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Order Source Description or null.
    */
   public final String getOrderSrcDesc()
   {
      return _OrderSrcDesc;
   }
	
   /**
    * Gets the Order Source Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Order Source Description or the specified default value.
    */
   public final String getOrderSrcDesc( String defaultValue )
   {
      return _OrderSrcDesc == null ? defaultValue : _OrderSrcDesc;
   }
                  
   /**
    * Gets the Settlement Source field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement Source or null.
    */
   public final String getSettleSource()
   {
      return _SettleSource;
   }
	
   /**
    * Gets the Settlement Source field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Source or the specified default value.
    */
   public final String getSettleSource( String defaultValue )
   {
      return _SettleSource == null ? defaultValue : _SettleSource;
   }
                  
   /**
    * Gets the Settlement Source Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement Source Description or null.
    */
   public final String getSettleSrcDesc()
   {
      return _SettleSrcDesc;
   }
	
   /**
    * Gets the Settlement Source Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Source Description or the specified default value.
    */
   public final String getSettleSrcDesc( String defaultValue )
   {
      return _SettleSrcDesc == null ? defaultValue : _SettleSrcDesc;
   }
                  
   /**
    * Gets the Source of Fund field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Source of Fund or null.
    */
   public final String getSrcOfFund()
   {
      return _SrcOfFund;
   }
	
   /**
    * Gets the Source of Fund field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of Fund or the specified default value.
    */
   public final String getSrcOfFund( String defaultValue )
   {
      return _SrcOfFund == null ? defaultValue : _SrcOfFund;
   }
                  
   /**
    * Gets the Source of Fund Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Source of Fund Description or null.
    */
   public final String getSrcOfFundDesc()
   {
      return _SrcOfFundDesc;
   }
	
   /**
    * Gets the Source of Fund Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of Fund Description or the specified default value.
    */
   public final String getSrcOfFundDesc( String defaultValue )
   {
      return _SrcOfFundDesc == null ? defaultValue : _SrcOfFundDesc;
   }
                  
   /**
    * Gets the Source of Account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Source of Account or null.
    */
   public final String getSrcOfAccount()
   {
      return _SrcOfAccount;
   }
	
   /**
    * Gets the Source of Account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of Account or the specified default value.
    */
   public final String getSrcOfAccount( String defaultValue )
   {
      return _SrcOfAccount == null ? defaultValue : _SrcOfAccount;
   }
                  
   /**
    * Gets the Settlement Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement Type or null.
    */
   public final String getSettleType()
   {
      return _SettleType;
   }
	
   /**
    * Gets the Settlement Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Type or the specified default value.
    */
   public final String getSettleType( String defaultValue )
   {
      return _SettleType == null ? defaultValue : _SettleType;
   }
                  
   /**
    * Gets the Settlement Type Desc field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement Type Desc or null.
    */
   public final String getSettleTypeDesc()
   {
      return _SettleTypeDesc;
   }
	
   /**
    * Gets the Settlement Type Desc field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Type Desc or the specified default value.
    */
   public final String getSettleTypeDesc( String defaultValue )
   {
      return _SettleTypeDesc == null ? defaultValue : _SettleTypeDesc;
   }
                  
   /**
    * Gets the Expected to Settle in Gross/Net field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Expected to Settle in Gross/Net or null.
    */
   public final String getExpGNSettle()
   {
      return _ExpGNSettle;
   }
	
   /**
    * Gets the Expected to Settle in Gross/Net field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Expected to Settle in Gross/Net or the specified default value.
    */
   public final String getExpGNSettle( String defaultValue )
   {
      return _ExpGNSettle == null ? defaultValue : _ExpGNSettle;
   }
                  
   /**
    * Gets the Settlement By field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement By or null.
    */
   public final String getSettledBy()
   {
      return _SettledBy;
   }
	
   /**
    * Gets the Settlement By field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement By or the specified default value.
    */
   public final String getSettledBy( String defaultValue )
   {
      return _SettledBy == null ? defaultValue : _SettledBy;
   }
                  
   /**
    * Gets the Settlement By Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settlement By Description or null.
    */
   public final String getSettledByDesc()
   {
      return _SettledByDesc;
   }
	
   /**
    * Gets the Settlement By Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement By Description or the specified default value.
    */
   public final String getSettledByDesc( String defaultValue )
   {
      return _SettledByDesc == null ? defaultValue : _SettledByDesc;
   }
                  
   /**
    * Gets the Round Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Round Flag or null.
    */
   public final String getRoundFlag()
   {
      return _RoundFlag;
   }
	
   /**
    * Gets the Round Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Round Flag or the specified default value.
    */
   public final String getRoundFlag( String defaultValue )
   {
      return _RoundFlag == null ? defaultValue : _RoundFlag;
   }
                  
   /**
    * Gets the Round Flag Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Round Flag Description or null.
    */
   public final String getRoundFlagDesc()
   {
      return _RoundFlagDesc;
   }
	
   /**
    * Gets the Round Flag Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Round Flag Description or the specified default value.
    */
   public final String getRoundFlagDesc( String defaultValue )
   {
      return _RoundFlagDesc == null ? defaultValue : _RoundFlagDesc;
   }
                  
   /**
    * Gets the Credit Frequency for GIC purchase field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Credit Frequency for GIC purchase or null.
    */
   public final String getCreditFreq()
   {
      return _CreditFreq;
   }
	
   /**
    * Gets the Credit Frequency for GIC purchase field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Frequency for GIC purchase or the specified default value.
    */
   public final String getCreditFreq( String defaultValue )
   {
      return _CreditFreq == null ? defaultValue : _CreditFreq;
   }
                  
   /**
    * Gets the Credit Frequency Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Credit Frequency Description or null.
    */
   public final String getCreditFreqDesc()
   {
      return _CreditFreqDesc;
   }
	
   /**
    * Gets the Credit Frequency Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Frequency Description or the specified default value.
    */
   public final String getCreditFreqDesc( String defaultValue )
   {
      return _CreditFreqDesc == null ? defaultValue : _CreditFreqDesc;
   }
                  
   /**
    * Gets the Extra Commission field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Extra Commission or null.
    */
   public final Boolean getExtraCommission()
   {
      return _ExtraCommission;
   }
	
   /**
    * Gets the Extra Commission field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission or the specified default value.
    */
   public final boolean getExtraCommission( boolean defaultValue )
   {
      return _ExtraCommission == null ? defaultValue : _ExtraCommission.booleanValue();
   }
                  
   /**
    * Gets the Certificate Required field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Certificate Required or null.
    */
   public final Boolean getCertRequired()
   {
      return _CertRequired;
   }
	
   /**
    * Gets the Certificate Required field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Certificate Required or the specified default value.
    */
   public final boolean getCertRequired( boolean defaultValue )
   {
      return _CertRequired == null ? defaultValue : _CertRequired.booleanValue();
   }
                  
   /**
    * Gets the Certificate Issued field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Certificate Issued or null.
    */
   public final Boolean getCertIssued()
   {
      return _CertIssued;
   }
	
   /**
    * Gets the Certificate Issued field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Certificate Issued or the specified default value.
    */
   public final boolean getCertIssued( boolean defaultValue )
   {
      return _CertIssued == null ? defaultValue : _CertIssued.booleanValue();
   }
                  
   /**
    * Gets the Confirmation Required field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Confirmation Required or null.
    */
   public final Boolean getConfirmReq()
   {
      return _ConfirmReq;
   }
	
   /**
    * Gets the Confirmation Required field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Confirmation Required or the specified default value.
    */
   public final boolean getConfirmReq( boolean defaultValue )
   {
      return _ConfirmReq == null ? defaultValue : _ConfirmReq.booleanValue();
   }
                  
   /**
    * Gets the Show On Statement field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Show On Statement or null.
    */
   public final Boolean getOnStmt()
   {
      return _OnStmt;
   }
	
   /**
    * Gets the Show On Statement field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Show On Statement or the specified default value.
    */
   public final boolean getOnStmt( boolean defaultValue )
   {
      return _OnStmt == null ? defaultValue : _OnStmt.booleanValue();
   }
                  
   /**
    * Gets the Tax/Contribution Receipt Issued field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax/Contribution Receipt Issued or null.
    */
   public final Boolean getRecptIssued()
   {
      return _RecptIssued;
   }
	
   /**
    * Gets the Tax/Contribution Receipt Issued field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax/Contribution Receipt Issued or the specified default value.
    */
   public final boolean getRecptIssued( boolean defaultValue )
   {
      return _RecptIssued == null ? defaultValue : _RecptIssued.booleanValue();
   }
                  
   /**
    * Gets the Exclude MFCS trade from MFCS settlemt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Exclude MFCS trade from MFCS settlemt or null.
    */
   public final Boolean getExclMFCSSettle()
   {
      return _ExclMFCSSettle;
   }
	
   /**
    * Gets the Exclude MFCS trade from MFCS settlemt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exclude MFCS trade from MFCS settlemt or the specified default value.
    */
   public final boolean getExclMFCSSettle( boolean defaultValue )
   {
      return _ExclMFCSSettle == null ? defaultValue : _ExclMFCSSettle.booleanValue();
   }
                  
   /**
    * Gets the Guarantee Date for Seg Product field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Guarantee Date for Seg Product or null.
    */
   public final Date getGuaranteeDate()
   {
      return _GuaranteeDate;
   }
	
   /**
    * Gets the Guarantee Date for Seg Product field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Date for Seg Product or the specified default value.
    */
   public final Date getGuaranteeDate( Date defaultValue )
   {
      return _GuaranteeDate == null ? defaultValue : _GuaranteeDate;
   }
                  
   /**
    * Gets the Maturity  Date for GIC purchase field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maturity  Date for GIC purchase or null.
    */
   public final Date getMaturityDate()
   {
      return _MaturityDate;
   }
	
   /**
    * Gets the Maturity  Date for GIC purchase field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity  Date for GIC purchase or the specified default value.
    */
   public final Date getMaturityDate( Date defaultValue )
   {
      return _MaturityDate == null ? defaultValue : _MaturityDate;
   }
                  
   /**
    * Gets the GIC Interest Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the GIC Interest Rate or null.
    */
   public final String getInterestRate()
   {
      return _InterestRate;
   }
	
   /**
    * Gets the GIC Interest Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GIC Interest Rate or the specified default value.
    */
   public final String getInterestRate( String defaultValue )
   {
      return _InterestRate == null ? defaultValue : _InterestRate;
   }
                  
   /**
    * Gets the Broker's Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker's Name or null.
    */
   public final String getBrokerName()
   {
      return _BrokerName;
   }
	
   /**
    * Gets the Broker's Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker's Name or the specified default value.
    */
   public final String getBrokerName( String defaultValue )
   {
      return _BrokerName == null ? defaultValue : _BrokerName;
   }
                  
   /**
    * Gets the Branch's Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Branch's Name or null.
    */
   public final String getBranchName()
   {
      return _BranchName;
   }
	
   /**
    * Gets the Branch's Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch's Name or the specified default value.
    */
   public final String getBranchName( String defaultValue )
   {
      return _BranchName == null ? defaultValue : _BranchName;
   }
                  
   /**
    * Gets the Salesrep's Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Salesrep's Name or null.
    */
   public final String getSlsrepName()
   {
      return _SlsrepName;
   }
	
   /**
    * Gets the Salesrep's Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salesrep's Name or the specified default value.
    */
   public final String getSlsrepName( String defaultValue )
   {
      return _SlsrepName == null ? defaultValue : _SlsrepName;
   }
                  
   /**
    * Gets the Salserep Alternate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Salserep Alternate Name or null.
    */
   public final String getSlsrepAltName()
   {
      return _SlsrepAltName;
   }
	
   /**
    * Gets the Salserep Alternate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salserep Alternate Name or the specified default value.
    */
   public final String getSlsrepAltName( String defaultValue )
   {
      return _SlsrepAltName == null ? defaultValue : _SlsrepAltName;
   }
                  
   /**
    * Gets the Deposit ID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Deposit ID or null.
    */
   public final String getDepId()
   {
      return _DepId;
   }
	
   /**
    * Gets the Deposit ID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deposit ID or the specified default value.
    */
   public final String getDepId( String defaultValue )
   {
      return _DepId == null ? defaultValue : _DepId;
   }
                  
   /**
    * Gets the Remarks Line 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Remarks Line 1 or null.
    */
   public final String getRemarks1()
   {
      return _Remarks1;
   }
	
   /**
    * Gets the Remarks Line 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 1 or the specified default value.
    */
   public final String getRemarks1( String defaultValue )
   {
      return _Remarks1 == null ? defaultValue : _Remarks1;
   }
                  
   /**
    * Gets the Remarks Line 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Remarks Line 2 or null.
    */
   public final String getRemarks2()
   {
      return _Remarks2;
   }
	
   /**
    * Gets the Remarks Line 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 2 or the specified default value.
    */
   public final String getRemarks2( String defaultValue )
   {
      return _Remarks2 == null ? defaultValue : _Remarks2;
   }
                  
   /**
    * Gets the Remarks Line 3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Remarks Line 3 or null.
    */
   public final String getRemarks3()
   {
      return _Remarks3;
   }
	
   /**
    * Gets the Remarks Line 3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks Line 3 or the specified default value.
    */
   public final String getRemarks3( String defaultValue )
   {
      return _Remarks3 == null ? defaultValue : _Remarks3;
   }
                  
   /**
    * Gets the Reject Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Reject Code or null.
    */
   public final String getRejCode()
   {
      return _RejCode;
   }
	
   /**
    * Gets the Reject Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reject Code or the specified default value.
    */
   public final String getRejCode( String defaultValue )
   {
      return _RejCode == null ? defaultValue : _RejCode;
   }
                  
   /**
    * Gets the Reject Code Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Reject Code Description or null.
    */
   public final String getRejCodeDesc()
   {
      return _RejCodeDesc;
   }
	
   /**
    * Gets the Reject Code Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reject Code Description or the specified default value.
    */
   public final String getRejCodeDesc( String defaultValue )
   {
      return _RejCodeDesc == null ? defaultValue : _RejCodeDesc;
   }
                  
   /**
    * Gets the Accountable Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Accountable Code or null.
    */
   public final String getAccountable()
   {
      return _Accountable;
   }
	
   /**
    * Gets the Accountable Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Accountable Code or the specified default value.
    */
   public final String getAccountable( String defaultValue )
   {
      return _Accountable == null ? defaultValue : _Accountable;
   }
                  
   /**
    * Gets the Accountable Code Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Accountable Code Description or null.
    */
   public final String getAcctableDesc()
   {
      return _AcctableDesc;
   }
	
   /**
    * Gets the Accountable Code Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Accountable Code Description or the specified default value.
    */
   public final String getAcctableDesc( String defaultValue )
   {
      return _AcctableDesc == null ? defaultValue : _AcctableDesc;
   }
                  
   /**
    * Gets the Date Stamp field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date Stamp or null.
    */
   public final Date getDateStamp()
   {
      return _DateStamp;
   }
	
   /**
    * Gets the Date Stamp field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date Stamp or the specified default value.
    */
   public final Date getDateStamp( Date defaultValue )
   {
      return _DateStamp == null ? defaultValue : _DateStamp;
   }
                  
   /**
    * Gets the Time Stamp field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Time Stamp or null.
    */
   public final String getTimeStamp()
   {
      return _TimeStamp;
   }
	
   /**
    * Gets the Time Stamp field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Time Stamp or the specified default value.
    */
   public final String getTimeStamp( String defaultValue )
   {
      return _TimeStamp == null ? defaultValue : _TimeStamp;
   }
                  
   /**
    * Gets the Record Created On field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Record Created On or null.
    */
   public final Date getProcessDate()
   {
      return _ProcessDate;
   }
	
   /**
    * Gets the Record Created On field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Created On or the specified default value.
    */
   public final Date getProcessDate( Date defaultValue )
   {
      return _ProcessDate == null ? defaultValue : _ProcessDate;
   }
                  
   /**
    * Gets the Allocation Trade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Allocation Trade or null.
    */
   public final Boolean getAllocation()
   {
      return _Allocation;
   }
	
   /**
    * Gets the Allocation Trade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allocation Trade or the specified default value.
    */
   public final boolean getAllocation( boolean defaultValue )
   {
      return _Allocation == null ? defaultValue : _Allocation.booleanValue();
   }
                  
   /**
    * Gets the Cansim Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Cansim Rate or null.
    */
   public final String getCansimRate()
   {
      return _CansimRate;
   }
	
   /**
    * Gets the Cansim Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cansim Rate or the specified default value.
    */
   public final String getCansimRate( String defaultValue )
   {
      return _CansimRate == null ? defaultValue : _CansimRate;
   }
                  
   /**
    * Gets the Initial purchase - yes/no field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Initial purchase - yes/no or null.
    */
   public final Boolean getInitPurch()
   {
      return _InitPurch;
   }
	
   /**
    * Gets the Initial purchase - yes/no field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Initial purchase - yes/no or the specified default value.
    */
   public final boolean getInitPurch( boolean defaultValue )
   {
      return _InitPurch == null ? defaultValue : _InitPurch.booleanValue();
   }
                  
   /**
    * Gets the BackDated Reason Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BackDated Reason Code or null.
    */
   public final String getBackDatedReason()
   {
      return _BackDatedReason;
   }
	
   /**
    * Gets the BackDated Reason Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BackDated Reason Code or the specified default value.
    */
   public final String getBackDatedReason( String defaultValue )
   {
      return _BackDatedReason == null ? defaultValue : _BackDatedReason;
   }
                  
   /**
    * Gets the Split Commissions Exist field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Split Commissions Exist or null.
    */
   public final Boolean getSplitComm()
   {
      return _SplitComm;
   }
	
   /**
    * Gets the Split Commissions Exist field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commissions Exist or the specified default value.
    */
   public final boolean getSplitComm( boolean defaultValue )
   {
      return _SplitComm == null ? defaultValue : _SplitComm.booleanValue();
   }
                  
   /**
    * Gets the Deal Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Deal Date or null.
    */
   public final Date getDealDate()
   {
      return _DealDate;
   }
	
   /**
    * Gets the Deal Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deal Date or the specified default value.
    */
   public final Date getDealDate( Date defaultValue )
   {
      return _DealDate == null ? defaultValue : _DealDate;
   }
                  
   /**
    * Gets the Deal Time field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Deal Time or null.
    */
   public final String getDealTime()
   {
      return _DealTime;
   }
	
   /**
    * Gets the Deal Time field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deal Time or the specified default value.
    */
   public final String getDealTime( String defaultValue )
   {
      return _DealTime == null ? defaultValue : _DealTime;
   }
                  
   /**
    * Gets the DSC Override Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DSC Override Code or null.
    */
   public final String getDSCOverrideCode()
   {
      return _DSCOverrideCode;
   }
	
   /**
    * Gets the DSC Override Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Override Code or the specified default value.
    */
   public final String getDSCOverrideCode( String defaultValue )
   {
      return _DSCOverrideCode == null ? defaultValue : _DSCOverrideCode;
   }
                  
   /**
    * Gets the DSC Override Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DSC Override Amount or null.
    */
   public final String getDSCOverrideAmt()
   {
      return _DSCOverrideAmt;
   }
	
   /**
    * Gets the DSC Override Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Override Amount or the specified default value.
    */
   public final String getDSCOverrideAmt( String defaultValue )
   {
      return _DSCOverrideAmt == null ? defaultValue : _DSCOverrideAmt;
   }
                  
   /**
    * Gets the Account To field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account To or null.
    */
   public final String getAccountTo()
   {
      return _AccountTo;
   }
	
   /**
    * Gets the Account To field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account To or the specified default value.
    */
   public final String getAccountTo( String defaultValue )
   {
      return _AccountTo == null ? defaultValue : _AccountTo;
   }
                  
   /**
    * Gets the Fund To field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund To or null.
    */
   public final String getFundTo()
   {
      return _FundTo;
   }
	
   /**
    * Gets the Fund To field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund To or the specified default value.
    */
   public final String getFundTo( String defaultValue )
   {
      return _FundTo == null ? defaultValue : _FundTo;
   }
                  
   /**
    * Gets the Class To Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Class To Code or null.
    */
   public final String getClassToCode()
   {
      return _ClassToCode;
   }
	
   /**
    * Gets the Class To Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class To Code or the specified default value.
    */
   public final String getClassToCode( String defaultValue )
   {
      return _ClassToCode == null ? defaultValue : _ClassToCode;
   }
                  
   /**
    * Gets the Transaction Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transaction Type or null.
    */
   public final String getrxTransType()
   {
      return _rxTransType;
   }
	
   /**
    * Gets the Transaction Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getrxTransType( String defaultValue )
   {
      return _rxTransType == null ? defaultValue : _rxTransType;
   }
                  
   /**
    * Gets the Fund From Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund From Code or null.
    */
   public final String getrxFundCode()
   {
      return _rxFundCode;
   }
	
   /**
    * Gets the Fund From Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund From Code or the specified default value.
    */
   public final String getrxFundCode( String defaultValue )
   {
      return _rxFundCode == null ? defaultValue : _rxFundCode;
   }
                  
   /**
    * Gets the Class From Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Class From Code or null.
    */
   public final String getrxClassCode()
   {
      return _rxClassCode;
   }
	
   /**
    * Gets the Class From Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class From Code or the specified default value.
    */
   public final String getrxClassCode( String defaultValue )
   {
      return _rxClassCode == null ? defaultValue : _rxClassCode;
   }
                  
   /**
    * Gets the Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Amount or null.
    */
   public final String getAmount()
   {
      return _Amount;
   }
	
   /**
    * Gets the Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( String defaultValue )
   {
      return _Amount == null ? defaultValue : _Amount;
   }
                  
   /**
    * Gets the Amount Type - dollars or percent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Amount Type - dollars or percent or null.
    */
   public final String getAmountType()
   {
      return _AmountType;
   }
	
   /**
    * Gets the Amount Type - dollars or percent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type - dollars or percent or the specified default value.
    */
   public final String getAmountType( String defaultValue )
   {
      return _AmountType == null ? defaultValue : _AmountType;
   }
                  
   /**
    * Gets the Gross or Net field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Gross or Net or null.
    */
   public final String getGrossOrNet()
   {
      return _GrossOrNet;
   }
	
   /**
    * Gets the Gross or Net field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross or Net or the specified default value.
    */
   public final String getGrossOrNet( String defaultValue )
   {
      return _GrossOrNet == null ? defaultValue : _GrossOrNet;
   }
                  
   /**
    * Gets the Use Entered Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Use Entered Fee or null.
    */
   public final Boolean getUseEnteredFee()
   {
      return _UseEnteredFee;
   }
	
   /**
    * Gets the Use Entered Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Use Entered Fee or the specified default value.
    */
   public final boolean getUseEnteredFee( boolean defaultValue )
   {
      return _UseEnteredFee == null ? defaultValue : _UseEnteredFee.booleanValue();
   }
                  
   /**
    * Gets the Fee on In side of Exchange field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee on In side of Exchange or null.
    */
   public final String getExchInFee()
   {
      return _ExchInFee;
   }
	
   /**
    * Gets the Fee on In side of Exchange field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee on In side of Exchange or the specified default value.
    */
   public final String getExchInFee( String defaultValue )
   {
      return _ExchInFee == null ? defaultValue : _ExchInFee;
   }
                  
   /**
    * Gets the Fee on In side of Exchange is Flat (yes) Percentage (no) field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee on In side of Exchange is Flat (yes) Percentage (no) or null.
    */
   public final Boolean getExchInFlatPercent()
   {
      return _ExchInFlatPercent;
   }
	
   /**
    * Gets the Fee on In side of Exchange is Flat (yes) Percentage (no) field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee on In side of Exchange is Flat (yes) Percentage (no) or the specified default value.
    */
   public final boolean getExchInFlatPercent( boolean defaultValue )
   {
      return _ExchInFlatPercent == null ? defaultValue : _ExchInFlatPercent.booleanValue();
   }
                  
   /**
    * Gets the Allow user to modify trade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Allow user to modify trade or null.
    */
   public final String getModPerm()
   {
      return _ModPerm;
   }
	
   /**
    * Gets the Allow user to modify trade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allow user to modify trade or the specified default value.
    */
   public final String getModPerm( String defaultValue )
   {
      return _ModPerm == null ? defaultValue : _ModPerm;
   }
                  
   /**
    * Gets the Acct Owner's First Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Acct Owner's First Name or null.
    */
   public final String getFirstName()
   {
      return _FirstName;
   }
	
   /**
    * Gets the Acct Owner's First Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct Owner's First Name or the specified default value.
    */
   public final String getFirstName( String defaultValue )
   {
      return _FirstName == null ? defaultValue : _FirstName;
   }
                  
   /**
    * Gets the Acct Owner's Last Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Acct Owner's Last Name or null.
    */
   public final String getLastName()
   {
      return _LastName;
   }
	
   /**
    * Gets the Acct Owner's Last Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct Owner's Last Name or the specified default value.
    */
   public final String getLastName( String defaultValue )
   {
      return _LastName == null ? defaultValue : _LastName;
   }
                  
   /**
    * Gets the Initial Purchase Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Initial Purchase Description or null.
    */
   public final String getInitPurchDesc()
   {
      return _InitPurchDesc;
   }
	
   /**
    * Gets the Initial Purchase Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Initial Purchase Description or the specified default value.
    */
   public final String getInitPurchDesc( String defaultValue )
   {
      return _InitPurchDesc == null ? defaultValue : _InitPurchDesc;
   }
                  
   /**
    * Gets the Confirm Required Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Confirm Required Description or null.
    */
   public final String getConfirmReqDesc()
   {
      return _ConfirmReqDesc;
   }
	
   /**
    * Gets the Confirm Required Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Confirm Required Description or the specified default value.
    */
   public final String getConfirmReqDesc( String defaultValue )
   {
      return _ConfirmReqDesc == null ? defaultValue : _ConfirmReqDesc;
   }
                  
   /**
    * Gets the Receipt Issued Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Receipt Issued Description or null.
    */
   public final String getRecptIssuedDesc()
   {
      return _RecptIssuedDesc;
   }
	
   /**
    * Gets the Receipt Issued Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Receipt Issued Description or the specified default value.
    */
   public final String getRecptIssuedDesc( String defaultValue )
   {
      return _RecptIssuedDesc == null ? defaultValue : _RecptIssuedDesc;
   }
                  
   /**
    * Gets the Baycom Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Baycom Number or null.
    */
   public final String getBaycom()
   {
      return _Baycom;
   }
	
   /**
    * Gets the Baycom Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom Number or the specified default value.
    */
   public final String getBaycom( String defaultValue )
   {
      return _Baycom == null ? defaultValue : _Baycom;
   }
                  
   /**
    * Gets the Baycom Number of FundTo and ClassTo field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Baycom Number of FundTo and ClassTo or null.
    */
   public final String getBaycomTo()
   {
      return _BaycomTo;
   }
	
   /**
    * Gets the Baycom Number of FundTo and ClassTo field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom Number of FundTo and ClassTo or the specified default value.
    */
   public final String getBaycomTo( String defaultValue )
   {
      return _BaycomTo == null ? defaultValue : _BaycomTo;
   }
                  
   /**
    * Gets the Bank Charge field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Charge or null.
    */
   public final String getBankCharge()
   {
      return _BankCharge;
   }
	
   /**
    * Gets the Bank Charge field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Charge or the specified default value.
    */
   public final String getBankCharge( String defaultValue )
   {
      return _BankCharge == null ? defaultValue : _BankCharge;
   }
                  
   /**
    * Gets the Value Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Value Date or null.
    */
   public final Date getValueDate()
   {
      return _ValueDate;
   }
	
   /**
    * Gets the Value Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Value Date or the specified default value.
    */
   public final Date getValueDate( Date defaultValue )
   {
      return _ValueDate == null ? defaultValue : _ValueDate;
   }
                  
   /**
    * Gets the Pay Method field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pay Method or null.
    */
   public final String getPayMethod()
   {
      return _PayMethod;
   }
	
   /**
    * Gets the Pay Method field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Method or the specified default value.
    */
   public final String getPayMethod( String defaultValue )
   {
      return _PayMethod == null ? defaultValue : _PayMethod;
   }
                  
   /**
    * Gets the ACH Processor field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ACH Processor or null.
    */
   public final String getACHProcessor()
   {
      return _ACHProcessor;
   }
	
   /**
    * Gets the ACH Processor field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACH Processor or the specified default value.
    */
   public final String getACHProcessor( String defaultValue )
   {
      return _ACHProcessor == null ? defaultValue : _ACHProcessor;
   }
                  
   /**
    * Gets the ToAccount Agency Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ToAccount Agency Code or null.
    */
   public final String getToBrokerCode()
   {
      return _ToBrokerCode;
   }
	
   /**
    * Gets the ToAccount Agency Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToAccount Agency Code or the specified default value.
    */
   public final String getToBrokerCode( String defaultValue )
   {
      return _ToBrokerCode == null ? defaultValue : _ToBrokerCode;
   }
                  
   /**
    * Gets the ToAccount Agent Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ToAccount Agent Code or null.
    */
   public final String getToSlsRepCode()
   {
      return _ToSlsRepCode;
   }
	
   /**
    * Gets the ToAccount Agent Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToAccount Agent Code or the specified default value.
    */
   public final String getToSlsRepCode( String defaultValue )
   {
      return _ToSlsRepCode == null ? defaultValue : _ToSlsRepCode;
   }
                  
   /**
    * Gets the Network ID for SWIFT/Vestima/ FundSettle trades field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Network ID for SWIFT/Vestima/ FundSettle trades or null.
    */
   public final String getNetworkID()
   {
      return _NetworkID;
   }
	
   /**
    * Gets the Network ID for SWIFT/Vestima/ FundSettle trades field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Network ID for SWIFT/Vestima/ FundSettle trades or the specified default value.
    */
   public final String getNetworkID( String defaultValue )
   {
      return _NetworkID == null ? defaultValue : _NetworkID;
   }
                  
   /**
    * Gets the Babel Reference Number at trade level field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Babel Reference Number at trade level or null.
    */
   public final String getExtTransNum()
   {
      return _ExtTransNum;
   }
	
   /**
    * Gets the Babel Reference Number at trade level field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Babel Reference Number at trade level or the specified default value.
    */
   public final String getExtTransNum( String defaultValue )
   {
      return _ExtTransNum == null ? defaultValue : _ExtTransNum;
   }
                  
   /**
    * Gets the Sender's Reference Number from MT502 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Sender's Reference Number from MT502 or null.
    */
   public final String getSendRefNum()
   {
      return _SendRefNum;
   }
	
   /**
    * Gets the Sender's Reference Number from MT502 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sender's Reference Number from MT502 or the specified default value.
    */
   public final String getSendRefNum( String defaultValue )
   {
      return _SendRefNum == null ? defaultValue : _SendRefNum;
   }
                  
   /**
    * Gets the Participant's Reference Number from MT502 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Participant's Reference Number from MT502 or null.
    */
   public final String getPartRefNum()
   {
      return _PartRefNum;
   }
	
   /**
    * Gets the Participant's Reference Number from MT502 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Participant's Reference Number from MT502 or the specified default value.
    */
   public final String getPartRefNum( String defaultValue )
   {
      return _PartRefNum == null ? defaultValue : _PartRefNum;
   }
                  
   /**
    * Gets the Master Ref Number from MT502 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Master Ref Number from MT502 or null.
    */
   public final String getMasterRefNum()
   {
      return _MasterRefNum;
   }
	
   /**
    * Gets the Master Ref Number from MT502 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Master Ref Number from MT502 or the specified default value.
    */
   public final String getMasterRefNum( String defaultValue )
   {
      return _MasterRefNum == null ? defaultValue : _MasterRefNum;
   }
                  
   /**
    * Gets the Exchange Out Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Exchange Out Fee or null.
    */
   public final String getExchOutFee()
   {
      return _ExchOutFee;
   }
	
   /**
    * Gets the Exchange Out Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Out Fee or the specified default value.
    */
   public final String getExchOutFee( String defaultValue )
   {
      return _ExchOutFee == null ? defaultValue : _ExchOutFee;
   }
                  
   /**
    * Gets the Exchange Out Flat/Prcnt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Exchange Out Flat/Prcnt or null.
    */
   public final Boolean getExchOutFlatPrcnt()
   {
      return _ExchOutFlatPrcnt;
   }
	
   /**
    * Gets the Exchange Out Flat/Prcnt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Out Flat/Prcnt or the specified default value.
    */
   public final boolean getExchOutFlatPrcnt( boolean defaultValue )
   {
      return _ExchOutFlatPrcnt == null ? defaultValue : _ExchOutFlatPrcnt.booleanValue();
   }
                  
   /**
    * Gets the Early PW/ShortTerm Transfer Fees field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Early PW/ShortTerm Transfer Fees or null.
    */
   public final Boolean getChargeERSTTRFee()
   {
      return _ChargeERSTTRFee;
   }
	
   /**
    * Gets the Early PW/ShortTerm Transfer Fees field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Early PW/ShortTerm Transfer Fees or the specified default value.
    */
   public final boolean getChargeERSTTRFee( boolean defaultValue )
   {
      return _ChargeERSTTRFee == null ? defaultValue : _ChargeERSTTRFee.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if Withdrawal Fees are to be changed on Redemption field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if Withdrawal Fees are to be changed on Redemption or null.
    */
   public final Boolean getChargeWDFee()
   {
      return _ChargeWDFee;
   }
	
   /**
    * Gets the Flag indicating if Withdrawal Fees are to be changed on Redemption field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Withdrawal Fees are to be changed on Redemption or the specified default value.
    */
   public final boolean getChargeWDFee( boolean defaultValue )
   {
      return _ChargeWDFee == null ? defaultValue : _ChargeWDFee.booleanValue();
   }
                  
   /**
    * Gets the Mirror Transaction Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mirror Transaction Number or null.
    */
   public final Integer getMirTransNum()
   {
      return _MirTransNum;
   }
	
   /**
    * Gets the Mirror Transaction Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mirror Transaction Number or the specified default value.
    */
   public final int getMirTransNum( int defaultValue )
   {
      return _MirTransNum == null ? defaultValue : _MirTransNum.intValue();
   }
                  
   /**
    * Gets the BorrowedFunds field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BorrowedFunds or null.
    */
   public final Boolean getBorrowedFunds()
   {
      return _BorrowedFunds;
   }
	
   /**
    * Gets the BorrowedFunds field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BorrowedFunds or the specified default value.
    */
   public final boolean getBorrowedFunds( boolean defaultValue )
   {
      return _BorrowedFunds == null ? defaultValue : _BorrowedFunds.booleanValue();
   }
                  
   /**
    * Gets the Transaction Sequence field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transaction Sequence or null.
    */
   public final Integer getTransSeq()
   {
      return _TransSeq;
   }
	
   /**
    * Gets the Transaction Sequence field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Sequence or the specified default value.
    */
   public final int getTransSeq( int defaultValue )
   {
      return _TransSeq == null ? defaultValue : _TransSeq.intValue();
   }
                  
   /**
    * Gets the From Settle Location Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the From Settle Location Code or null.
    */
   public final String getFrSettlLocCode()
   {
      return _FrSettlLocCode;
   }
	
   /**
    * Gets the From Settle Location Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Settle Location Code or the specified default value.
    */
   public final String getFrSettlLocCode( String defaultValue )
   {
      return _FrSettlLocCode == null ? defaultValue : _FrSettlLocCode;
   }
                  
   /**
    * Gets the From Delivery To field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the From Delivery To or null.
    */
   public final String getFrDeliveryTo()
   {
      return _FrDeliveryTo;
   }
	
   /**
    * Gets the From Delivery To field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Delivery To or the specified default value.
    */
   public final String getFrDeliveryTo( String defaultValue )
   {
      return _FrDeliveryTo == null ? defaultValue : _FrDeliveryTo;
   }
                  
   /**
    * Gets the From Settlement Location Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the From Settlement Location Description or null.
    */
   public final String getFrSettlLocDescription()
   {
      return _FrSettlLocDescription;
   }
	
   /**
    * Gets the From Settlement Location Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Settlement Location Description or the specified default value.
    */
   public final String getFrSettlLocDescription( String defaultValue )
   {
      return _FrSettlLocDescription == null ? defaultValue : _FrSettlLocDescription;
   }
                  
   /**
    * Gets the From In Favour of field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the From In Favour of or null.
    */
   public final String getFrInfavourOf()
   {
      return _FrInfavourOf;
   }
	
   /**
    * Gets the From In Favour of field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From In Favour of or the specified default value.
    */
   public final String getFrInfavourOf( String defaultValue )
   {
      return _FrInfavourOf == null ? defaultValue : _FrInfavourOf;
   }
                  
   /**
    * Gets the From For Account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the From For Account or null.
    */
   public final String getFrForAccount()
   {
      return _FrForAccount;
   }
	
   /**
    * Gets the From For Account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From For Account or the specified default value.
    */
   public final String getFrForAccount( String defaultValue )
   {
      return _FrForAccount == null ? defaultValue : _FrForAccount;
   }
                  
   /**
    * Gets the From Clearing Method field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the From Clearing Method or null.
    */
   public final String getFrClearingMethod()
   {
      return _FrClearingMethod;
   }
	
   /**
    * Gets the From Clearing Method field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Clearing Method or the specified default value.
    */
   public final String getFrClearingMethod( String defaultValue )
   {
      return _FrClearingMethod == null ? defaultValue : _FrClearingMethod;
   }
                  
   /**
    * Gets the To Settle Location Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the To Settle Location Code or null.
    */
   public final String getToSettlLocCode()
   {
      return _ToSettlLocCode;
   }
	
   /**
    * Gets the To Settle Location Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Settle Location Code or the specified default value.
    */
   public final String getToSettlLocCode( String defaultValue )
   {
      return _ToSettlLocCode == null ? defaultValue : _ToSettlLocCode;
   }
                  
   /**
    * Gets the To Delivery To field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the To Delivery To or null.
    */
   public final String getToFrDeliveryTo()
   {
      return _ToFrDeliveryTo;
   }
	
   /**
    * Gets the To Delivery To field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Delivery To or the specified default value.
    */
   public final String getToFrDeliveryTo( String defaultValue )
   {
      return _ToFrDeliveryTo == null ? defaultValue : _ToFrDeliveryTo;
   }
                  
   /**
    * Gets the To Settlement Location Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the To Settlement Location Description or null.
    */
   public final String getToSettlLocDescription()
   {
      return _ToSettlLocDescription;
   }
	
   /**
    * Gets the To Settlement Location Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Settlement Location Description or the specified default value.
    */
   public final String getToSettlLocDescription( String defaultValue )
   {
      return _ToSettlLocDescription == null ? defaultValue : _ToSettlLocDescription;
   }
                  
   /**
    * Gets the To Infavour of field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the To Infavour of or null.
    */
   public final String getToInFavourOf()
   {
      return _ToInFavourOf;
   }
	
   /**
    * Gets the To Infavour of field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Infavour of or the specified default value.
    */
   public final String getToInFavourOf( String defaultValue )
   {
      return _ToInFavourOf == null ? defaultValue : _ToInFavourOf;
   }
                  
   /**
    * Gets the To for Account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the To for Account or null.
    */
   public final String getToForAccount()
   {
      return _ToForAccount;
   }
	
   /**
    * Gets the To for Account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To for Account or the specified default value.
    */
   public final String getToForAccount( String defaultValue )
   {
      return _ToForAccount == null ? defaultValue : _ToForAccount;
   }
                  
   /**
    * Gets the To Clearing Method field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the To Clearing Method or null.
    */
   public final String getToClearingMethod()
   {
      return _ToClearingMethod;
   }
	
   /**
    * Gets the To Clearing Method field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Clearing Method or the specified default value.
    */
   public final String getToClearingMethod( String defaultValue )
   {
      return _ToClearingMethod == null ? defaultValue : _ToClearingMethod;
   }
                  
   /**
    * Gets the Exchange In Fee from New Money Transfer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Exchange In Fee from New Money Transfer or null.
    */
   public final String getIFeeTo()
   {
      return _IFeeTo;
   }
	
   /**
    * Gets the Exchange In Fee from New Money Transfer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange In Fee from New Money Transfer or the specified default value.
    */
   public final String getIFeeTo( String defaultValue )
   {
      return _IFeeTo == null ? defaultValue : _IFeeTo;
   }
                  
   /**
    * Gets the Charge ALD Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Charge ALD Fee or null.
    */
   public final String getChargeADLFee()
   {
      return _ChargeADLFee;
   }
	
   /**
    * Gets the Charge ALD Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Charge ALD Fee or the specified default value.
    */
   public final String getChargeADLFee( String defaultValue )
   {
      return _ChargeADLFee == null ? defaultValue : _ChargeADLFee;
   }
                  
   /**
    * Gets the LSIFCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the LSIFCode or null.
    */
   public final String getLSIFCode()
   {
      return _LSIFCode;
   }
	
   /**
    * Gets the LSIFCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LSIFCode or the specified default value.
    */
   public final String getLSIFCode( String defaultValue )
   {
      return _LSIFCode == null ? defaultValue : _LSIFCode;
   }
                  
   /**
    * Gets the Alternate Account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Alternate Account or null.
    */
   public final String getAltAccount()
   {
      return _AltAccount;
   }
	
   /**
    * Gets the Alternate Account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alternate Account or the specified default value.
    */
   public final String getAltAccount( String defaultValue )
   {
      return _AltAccount == null ? defaultValue : _AltAccount;
   }
                  
   /**
    * Gets the Other Reference Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Other Reference Number or null.
    */
   public final String getRefNum()
   {
      return _RefNum;
   }
	
   /**
    * Gets the Other Reference Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other Reference Number or the specified default value.
    */
   public final String getRefNum( String defaultValue )
   {
      return _RefNum == null ? defaultValue : _RefNum;
   }
                  
   /**
    * Gets the Fund WKN field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund WKN or null.
    */
   public final String getFundWKN()
   {
      return _FundWKN;
   }
	
   /**
    * Gets the Fund WKN field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund WKN or the specified default value.
    */
   public final String getFundWKN( String defaultValue )
   {
      return _FundWKN == null ? defaultValue : _FundWKN;
   }
                  
   /**
    * Gets the FundISIN field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FundISIN or null.
    */
   public final String getFundISIN()
   {
      return _FundISIN;
   }
	
   /**
    * Gets the FundISIN field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundISIN or the specified default value.
    */
   public final String getFundISIN( String defaultValue )
   {
      return _FundISIN == null ? defaultValue : _FundISIN;
   }
                  
   /**
    * Gets the Fund To WKN field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund To WKN or null.
    */
   public final String getFundToWKN()
   {
      return _FundToWKN;
   }
	
   /**
    * Gets the Fund To WKN field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund To WKN or the specified default value.
    */
   public final String getFundToWKN( String defaultValue )
   {
      return _FundToWKN == null ? defaultValue : _FundToWKN;
   }
                  
   /**
    * Gets the Fund To ISIN field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund To ISIN or null.
    */
   public final String getFundToISIN()
   {
      return _FundToISIN;
   }
	
   /**
    * Gets the Fund To ISIN field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund To ISIN or the specified default value.
    */
   public final String getFundToISIN( String defaultValue )
   {
      return _FundToISIN == null ? defaultValue : _FundToISIN;
   }
                  
   /**
    * Gets the Acquisition Fee Option field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Acquisition Fee Option or null.
    */
   public final String getAcqFeeOption()
   {
      return _AcqFeeOption;
   }
	
   /**
    * Gets the Acquisition Fee Option field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Fee Option or the specified default value.
    */
   public final String getAcqFeeOption( String defaultValue )
   {
      return _AcqFeeOption == null ? defaultValue : _AcqFeeOption;
   }
                  
   /**
    * Gets the SettleDate is Overriden field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SettleDate is Overriden or null.
    */
   public final Boolean getSettleDateOverriden()
   {
      return _SettleDateOverriden;
   }
	
   /**
    * Gets the SettleDate is Overriden field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SettleDate is Overriden or the specified default value.
    */
   public final boolean getSettleDateOverriden( boolean defaultValue )
   {
      return _SettleDateOverriden == null ? defaultValue : _SettleDateOverriden.booleanValue();
   }
                  
   /**
    * Gets the From Settlement Instruction Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the From Settlement Instruction Code or null.
    */
   public final String getFrSettlInstrCode()
   {
      return _FrSettlInstrCode;
   }
	
   /**
    * Gets the From Settlement Instruction Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Settlement Instruction Code or the specified default value.
    */
   public final String getFrSettlInstrCode( String defaultValue )
   {
      return _FrSettlInstrCode == null ? defaultValue : _FrSettlInstrCode;
   }
                  
   /**
    * Gets the To Settlement Instruction Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the To Settlement Instruction Code or null.
    */
   public final String getToSettlInstrCode()
   {
      return _ToSettlInstrCode;
   }
	
   /**
    * Gets the To Settlement Instruction Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Settlement Instruction Code or the specified default value.
    */
   public final String getToSettlInstrCode( String defaultValue )
   {
      return _ToSettlInstrCode == null ? defaultValue : _ToSettlInstrCode;
   }
                  
   /**
    * Gets the Fund Broker field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund Broker or null.
    */
   public final String getFundBroker()
   {
      return _FundBroker;
   }
	
   /**
    * Gets the Fund Broker field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker or the specified default value.
    */
   public final String getFundBroker( String defaultValue )
   {
      return _FundBroker == null ? defaultValue : _FundBroker;
   }
                  
   /**
    * Gets the Aggregation Option field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Aggregation Option or null.
    */
   public final String getAggrOption()
   {
      return _AggrOption;
   }
	
   /**
    * Gets the Aggregation Option field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Aggregation Option or the specified default value.
    */
   public final String getAggrOption( String defaultValue )
   {
      return _AggrOption == null ? defaultValue : _AggrOption;
   }
                  
   /**
    * Gets the Broker Settlement Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Settlement Date or null.
    */
   public final Date getBrkSettlDate()
   {
      return _BrkSettlDate;
   }
	
   /**
    * Gets the Broker Settlement Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Settlement Date or the specified default value.
    */
   public final Date getBrkSettlDate( Date defaultValue )
   {
      return _BrkSettlDate == null ? defaultValue : _BrkSettlDate;
   }
                  
   /**
    * Gets the Other Confirm Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Other Confirm Type or null.
    */
   public final String getOtherConfirmType()
   {
      return _OtherConfirmType;
   }
	
   /**
    * Gets the Other Confirm Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other Confirm Type or the specified default value.
    */
   public final String getOtherConfirmType( String defaultValue )
   {
      return _OtherConfirmType == null ? defaultValue : _OtherConfirmType;
   }
                  
   /**
    * Gets the External Price field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the External Price or null.
    */
   public final String getExternalPrice()
   {
      return _ExternalPrice;
   }
	
   /**
    * Gets the External Price field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External Price or the specified default value.
    */
   public final String getExternalPrice( String defaultValue )
   {
      return _ExternalPrice == null ? defaultValue : _ExternalPrice;
   }
                  
   /**
    * Gets the External Settlement Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the External Settlement Date or null.
    */
   public final Date getExternalSettleDate()
   {
      return _ExternalSettleDate;
   }
	
   /**
    * Gets the External Settlement Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External Settlement Date or the specified default value.
    */
   public final Date getExternalSettleDate( Date defaultValue )
   {
      return _ExternalSettleDate == null ? defaultValue : _ExternalSettleDate;
   }
                  
   /**
    * Gets the External Settlement Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the External Settlement Amount or null.
    */
   public final String getExternalSettleAmt()
   {
      return _ExternalSettleAmt;
   }
	
   /**
    * Gets the External Settlement Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External Settlement Amount or the specified default value.
    */
   public final String getExternalSettleAmt( String defaultValue )
   {
      return _ExternalSettleAmt == null ? defaultValue : _ExternalSettleAmt;
   }
                  
   /**
    * Gets the ROA Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ROA Amount or null.
    */
   public final String getROAAmount()
   {
      return _ROAAmount;
   }
	
   /**
    * Gets the ROA Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ROA Amount or the specified default value.
    */
   public final String getROAAmount( String defaultValue )
   {
      return _ROAAmount == null ? defaultValue : _ROAAmount;
   }
                  
   /**
    * Gets the Delivery Method field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Delivery Method or null.
    */
   public final String getDeliveryMethod()
   {
      return _DeliveryMethod;
   }
	
   /**
    * Gets the Delivery Method field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery Method or the specified default value.
    */
   public final String getDeliveryMethod( String defaultValue )
   {
      return _DeliveryMethod == null ? defaultValue : _DeliveryMethod;
   }
                  
   /**
    * Gets the Original transaction number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Original transaction number or null.
    */
   public final Integer getAdjustForTransNum()
   {
      return _AdjustForTransNum;
   }
	
   /**
    * Gets the Original transaction number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original transaction number or the specified default value.
    */
   public final int getAdjustForTransNum( int defaultValue )
   {
      return _AdjustForTransNum == null ? defaultValue : _AdjustForTransNum.intValue();
   }
                  
   /**
    * Gets the Transaction ID number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transaction ID number or null.
    */
   public final String getTransId()
   {
      return _TransId;
   }
	
   /**
    * Gets the Transaction ID number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction ID number or the specified default value.
    */
   public final String getTransId( String defaultValue )
   {
      return _TransId == null ? defaultValue : _TransId;
   }
                  
   /**
    * Gets the SplitComm Rebook TransID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SplitComm Rebook TransID or null.
    */
   public final String getSplitCommRebookTransID()
   {
      return _SplitCommRebookTransID;
   }
	
   /**
    * Gets the SplitComm Rebook TransID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SplitComm Rebook TransID or the specified default value.
    */
   public final String getSplitCommRebookTransID( String defaultValue )
   {
      return _SplitCommRebookTransID == null ? defaultValue : _SplitCommRebookTransID;
   }
                  
   /**
    * Gets the Average cost per unit field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Average cost per unit or null.
    */
   public final String getEUSDAvgCost()
   {
      return _EUSDAvgCost;
   }
	
   /**
    * Gets the Average cost per unit field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Average cost per unit or the specified default value.
    */
   public final String getEUSDAvgCost( String defaultValue )
   {
      return _EUSDAvgCost == null ? defaultValue : _EUSDAvgCost;
   }
                  
   /**
    * Gets the TIS Average cost per unit field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TIS Average cost per unit or null.
    */
   public final String getEUSDAvgTIS()
   {
      return _EUSDAvgTIS;
   }
	
   /**
    * Gets the TIS Average cost per unit field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TIS Average cost per unit or the specified default value.
    */
   public final String getEUSDAvgTIS( String defaultValue )
   {
      return _EUSDAvgTIS == null ? defaultValue : _EUSDAvgTIS;
   }
                  
   /**
    * Gets the Flag indicating if cost has been overriden field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if cost has been overriden or null.
    */
   public final Boolean getEUSDCostOverride()
   {
      return _EUSDCostOverride;
   }
	
   /**
    * Gets the Flag indicating if cost has been overriden field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if cost has been overriden or the specified default value.
    */
   public final boolean getEUSDCostOverride( boolean defaultValue )
   {
      return _EUSDCostOverride == null ? defaultValue : _EUSDCostOverride.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if TIS has been overriden field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if TIS has been overriden or null.
    */
   public final Boolean getEUSDTISOverride()
   {
      return _EUSDTISOverride;
   }
	
   /**
    * Gets the Flag indicating if TIS has been overriden field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if TIS has been overriden or the specified default value.
    */
   public final boolean getEUSDTISOverride( boolean defaultValue )
   {
      return _EUSDTISOverride == null ? defaultValue : _EUSDTISOverride.booleanValue();
   }
                  
   /**
    * Gets the MCH File field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MCH File or null.
    */
   public final String getMCHFile()
   {
      return _MCHFile;
   }
	
   /**
    * Gets the MCH File field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MCH File or the specified default value.
    */
   public final String getMCHFile( String defaultValue )
   {
      return _MCHFile == null ? defaultValue : _MCHFile;
   }
                  
   /**
    * Gets the Security Recon File field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Security Recon File or null.
    */
   public final String getSecReconFile()
   {
      return _SecReconFile;
   }
	
   /**
    * Gets the Security Recon File field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Security Recon File or the specified default value.
    */
   public final String getSecReconFile( String defaultValue )
   {
      return _SecReconFile == null ? defaultValue : _SecReconFile;
   }
                  
   /**
    * Gets the Flag indication if the transaction is to be excluded from N$M file "In" Include, "Ex" exclude field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indication if the transaction is to be excluded from N$M file "In" Include, "Ex" exclude or null.
    */
   public final String getESGSettle()
   {
      return _ESGSettle;
   }
	
   /**
    * Gets the Flag indication if the transaction is to be excluded from N$M file "In" Include, "Ex" exclude field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indication if the transaction is to be excluded from N$M file "In" Include, "Ex" exclude or the specified default value.
    */
   public final String getESGSettle( String defaultValue )
   {
      return _ESGSettle == null ? defaultValue : _ESGSettle;
   }
                  
   /**
    * Gets the NSCC Control Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the NSCC Control Number or null.
    */
   public final String getNSCControlNum()
   {
      return _NSCControlNum;
   }
	
   /**
    * Gets the NSCC Control Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NSCC Control Number or the specified default value.
    */
   public final String getNSCControlNum( String defaultValue )
   {
      return _NSCControlNum == null ? defaultValue : _NSCControlNum;
   }
                  
   /**
    * Gets the Trade Pay Instruct Exists Y/N field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Trade Pay Instruct Exists Y/N or null.
    */
   public final Boolean getTradePayInstrExist()
   {
      return _TradePayInstrExist;
   }
	
   /**
    * Gets the Trade Pay Instruct Exists Y/N field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Pay Instruct Exists Y/N or the specified default value.
    */
   public final boolean getTradePayInstrExist( boolean defaultValue )
   {
      return _TradePayInstrExist == null ? defaultValue : _TradePayInstrExist.booleanValue();
   }
                  
   /**
    * Gets the Payment Instruction Option field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment Instruction Option or null.
    */
   public final String getPayInstructOption()
   {
      return _PayInstructOption;
   }
	
   /**
    * Gets the Payment Instruction Option field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Instruction Option or the specified default value.
    */
   public final String getPayInstructOption( String defaultValue )
   {
      return _PayInstructOption == null ? defaultValue : _PayInstructOption;
   }
                  
   /**
    * Gets the MF Payment field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MF Payment or null.
    */
   public final String getMFPayment()
   {
      return _MFPayment;
   }
	
   /**
    * Gets the MF Payment field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MF Payment or the specified default value.
    */
   public final String getMFPayment( String defaultValue )
   {
      return _MFPayment == null ? defaultValue : _MFPayment;
   }
                  
   /**
    * Gets the INDC field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the INDC or null.
    */
   public final String getINDC()
   {
      return _INDC;
   }
	
   /**
    * Gets the INDC field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the INDC or the specified default value.
    */
   public final String getINDC( String defaultValue )
   {
      return _INDC == null ? defaultValue : _INDC;
   }
                  
   /**
    * Gets the Modification Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Modification Date or null.
    */
   public final Date getModDate()
   {
      return _ModDate;
   }
	
   /**
    * Gets the Modification Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification Date or the specified default value.
    */
   public final Date getModDate( Date defaultValue )
   {
      return _ModDate == null ? defaultValue : _ModDate;
   }
                  
   /**
    * Gets the Modification User field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Modification User or null.
    */
   public final String getModUser()
   {
      return _ModUser;
   }
	
   /**
    * Gets the Modification User field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification User or the specified default value.
    */
   public final String getModUser( String defaultValue )
   {
      return _ModUser == null ? defaultValue : _ModUser;
   }
                  
   /**
    * Gets the Receipt Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Receipt Status or null.
    */
   public final String getRecptStatus()
   {
      return _RecptStatus;
   }
	
   /**
    * Gets the Receipt Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Receipt Status or the specified default value.
    */
   public final String getRecptStatus( String defaultValue )
   {
      return _RecptStatus == null ? defaultValue : _RecptStatus;
   }
                  
   /**
    * Gets the Name of the entity related somehow to the trade like former spouse entity field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Name of the entity related somehow to the trade like former spouse entity or null.
    */
   public final String getLinkedEntityName()
   {
      return _LinkedEntityName;
   }
	
   /**
    * Gets the Name of the entity related somehow to the trade like former spouse entity field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Name of the entity related somehow to the trade like former spouse entity or the specified default value.
    */
   public final String getLinkedEntityName( String defaultValue )
   {
      return _LinkedEntityName == null ? defaultValue : _LinkedEntityName;
   }
                  
   /**
    * Gets the ID of the entity related somehow to the trade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ID of the entity related somehow to the trade or null.
    */
   public final String getLinkedEntityId()
   {
      return _LinkedEntityId;
   }
	
   /**
    * Gets the ID of the entity related somehow to the trade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID of the entity related somehow to the trade or the specified default value.
    */
   public final String getLinkedEntityId( String defaultValue )
   {
      return _LinkedEntityId == null ? defaultValue : _LinkedEntityId;
   }
                  
   /**
    * Gets the Authorization field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Authorization or null.
    */
   public final String getAuthorized()
   {
      return _Authorized;
   }
	
   /**
    * Gets the Authorization field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Authorization or the specified default value.
    */
   public final String getAuthorized( String defaultValue )
   {
      return _Authorized == null ? defaultValue : _Authorized;
   }
                  
   /**
    * Gets the Associated Transaction Id field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associated Transaction Id or null.
    */
   public final String getAssociatedTransId()
   {
      return _AssociatedTransId;
   }
	
   /**
    * Gets the Associated Transaction Id field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associated Transaction Id or the specified default value.
    */
   public final String getAssociatedTransId( String defaultValue )
   {
      return _AssociatedTransId == null ? defaultValue : _AssociatedTransId;
   }
                  
   /**
    * Gets the Grant Repayment Reason field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Grant Repayment Reason or null.
    */
   public final String getGrantRepayReason()
   {
      return _GrantRepayReason;
   }
	
   /**
    * Gets the Grant Repayment Reason field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Grant Repayment Reason or the specified default value.
    */
   public final String getGrantRepayReason( String defaultValue )
   {
      return _GrantRepayReason == null ? defaultValue : _GrantRepayReason;
   }
                  
   /**
    * Gets the HRDC Reporting Required field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the HRDC Reporting Required or null.
    */
   public final Boolean getNeedToReportHRDC()
   {
      return _NeedToReportHRDC;
   }
	
   /**
    * Gets the HRDC Reporting Required field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the HRDC Reporting Required or the specified default value.
    */
   public final boolean getNeedToReportHRDC( boolean defaultValue )
   {
      return _NeedToReportHRDC == null ? defaultValue : _NeedToReportHRDC.booleanValue();
   }
                  
   /**
    * Gets the Tax Year field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Year or null.
    */
   public final Integer getTaxYear()
   {
      return _TaxYear;
   }
	
   /**
    * Gets the Tax Year field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Year or the specified default value.
    */
   public final int getTaxYear( int defaultValue )
   {
      return _TaxYear == null ? defaultValue : _TaxYear.intValue();
   }
                  
   /**
    * Gets the Beneficiary Tainted field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Beneficiary Tainted or null.
    */
   public final Boolean getTainted()
   {
      return _Tainted;
   }
	
   /**
    * Gets the Beneficiary Tainted field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Tainted or the specified default value.
    */
   public final boolean getTainted( boolean defaultValue )
   {
      return _Tainted == null ? defaultValue : _Tainted.booleanValue();
   }
                  
   /**
    * Gets the Year the overcontribution withdrawal to be applied field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Year the overcontribution withdrawal to be applied or null.
    */
   public final Integer getOCRedYear()
   {
      return _OCRedYear;
   }
	
   /**
    * Gets the Year the overcontribution withdrawal to be applied field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Year the overcontribution withdrawal to be applied or the specified default value.
    */
   public final int getOCRedYear( int defaultValue )
   {
      return _OCRedYear == null ? defaultValue : _OCRedYear.intValue();
   }
                  
   /**
    * Gets the Assisted Contribution Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Assisted Contribution Amount or null.
    */
   public final String getAssistedContrAmt()
   {
      return _AssistedContrAmt;
   }
	
   /**
    * Gets the Assisted Contribution Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Assisted Contribution Amount or the specified default value.
    */
   public final String getAssistedContrAmt( String defaultValue )
   {
      return _AssistedContrAmt == null ? defaultValue : _AssistedContrAmt;
   }
                  
   /**
    * Gets the Account Owner ID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Owner ID or null.
    */
   public final String getAcctOwnerID()
   {
      return _AcctOwnerID;
   }
	
   /**
    * Gets the Account Owner ID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Owner ID or the specified default value.
    */
   public final String getAcctOwnerID( String defaultValue )
   {
      return _AcctOwnerID == null ? defaultValue : _AcctOwnerID;
   }
                  
   /**
    * Gets the Account Owner Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Owner Name or null.
    */
   public final String getAcctOwnerName()
   {
      return _AcctOwnerName;
   }
	
   /**
    * Gets the Account Owner Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Owner Name or the specified default value.
    */
   public final String getAcctOwnerName( String defaultValue )
   {
      return _AcctOwnerName == null ? defaultValue : _AcctOwnerName;
   }
                  
   /**
    * Gets the Network Response Required field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Network Response Required or null.
    */
   public final String getNetworkRespRequired()
   {
      return _NetworkRespRequired;
   }
	
   /**
    * Gets the Network Response Required field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Network Response Required or the specified default value.
    */
   public final String getNetworkRespRequired( String defaultValue )
   {
      return _NetworkRespRequired == null ? defaultValue : _NetworkRespRequired;
   }
                  
   /**
    * Gets the EAP CESG Paid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EAP CESG Paid or null.
    */
   public final String getEAPCESGPaid()
   {
      return _EAPCESGPaid;
   }
	
   /**
    * Gets the EAP CESG Paid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EAP CESG Paid or the specified default value.
    */
   public final String getEAPCESGPaid( String defaultValue )
   {
      return _EAPCESGPaid == null ? defaultValue : _EAPCESGPaid;
   }
                  
   /**
    * Gets the Interest Investment UUID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Interest Investment UUID or null.
    */
   public final String getIntInvestUUID()
   {
      return _IntInvestUUID;
   }
	
   /**
    * Gets the Interest Investment UUID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interest Investment UUID or the specified default value.
    */
   public final String getIntInvestUUID( String defaultValue )
   {
      return _IntInvestUUID == null ? defaultValue : _IntInvestUUID;
   }
                  
   /**
    * Gets the Investment Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment Number or null.
    */
   public final String getInvestmentNo()
   {
      return _InvestmentNo;
   }
	
   /**
    * Gets the Investment Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Number or the specified default value.
    */
   public final String getInvestmentNo( String defaultValue )
   {
      return _InvestmentNo == null ? defaultValue : _InvestmentNo;
   }
                  
   /**
    * Gets the Investment Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment Status or null.
    */
   public final String getInvestStatus()
   {
      return _InvestStatus;
   }
	
   /**
    * Gets the Investment Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Status or the specified default value.
    */
   public final String getInvestStatus( String defaultValue )
   {
      return _InvestStatus == null ? defaultValue : _InvestStatus;
   }
                  
   /**
    * Gets the Interest Calculation Method field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Interest Calculation Method or null.
    */
   public final String getIntCalcMthd()
   {
      return _IntCalcMthd;
   }
	
   /**
    * Gets the Interest Calculation Method field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interest Calculation Method or the specified default value.
    */
   public final String getIntCalcMthd( String defaultValue )
   {
      return _IntCalcMthd == null ? defaultValue : _IntCalcMthd;
   }
                  
   /**
    * Gets the Investment Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment Type or null.
    */
   public final String getIntInvestType()
   {
      return _IntInvestType;
   }
	
   /**
    * Gets the Investment Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Type or the specified default value.
    */
   public final String getIntInvestType( String defaultValue )
   {
      return _IntInvestType == null ? defaultValue : _IntInvestType;
   }
                  
   /**
    * Gets the Term of Investment field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Term of Investment or null.
    */
   public final Integer getInvestTerm()
   {
      return _InvestTerm;
   }
	
   /**
    * Gets the Term of Investment field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Term of Investment or the specified default value.
    */
   public final int getInvestTerm( int defaultValue )
   {
      return _InvestTerm == null ? defaultValue : _InvestTerm.intValue();
   }
                  
   /**
    * Gets the Interest Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Interest Rate or null.
    */
   public final String getIntRate()
   {
      return _IntRate;
   }
	
   /**
    * Gets the Interest Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interest Rate or the specified default value.
    */
   public final String getIntRate( String defaultValue )
   {
      return _IntRate == null ? defaultValue : _IntRate;
   }
                  
   /**
    * Gets the Maturity Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maturity Date or null.
    */
   public final Date getGIMaturityDate()
   {
      return _GIMaturityDate;
   }
	
   /**
    * Gets the Maturity Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date or the specified default value.
    */
   public final Date getGIMaturityDate( Date defaultValue )
   {
      return _GIMaturityDate == null ? defaultValue : _GIMaturityDate;
   }
                  
   /**
    * Gets the Interest Credit Frequency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Interest Credit Frequency or null.
    */
   public final String getIntCredFreq()
   {
      return _IntCredFreq;
   }
	
   /**
    * Gets the Interest Credit Frequency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Interest Credit Frequency or the specified default value.
    */
   public final String getIntCredFreq( String defaultValue )
   {
      return _IntCredFreq == null ? defaultValue : _IntCredFreq;
   }
                  
   /**
    * Gets the Last Interest Credit Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Last Interest Credit Date or null.
    */
   public final Date getLastIntCredDate()
   {
      return _LastIntCredDate;
   }
	
   /**
    * Gets the Last Interest Credit Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Interest Credit Date or the specified default value.
    */
   public final Date getLastIntCredDate( Date defaultValue )
   {
      return _LastIntCredDate == null ? defaultValue : _LastIntCredDate;
   }
                  
   /**
    * Gets the Additional Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Additional Amount or null.
    */
   public final String getAddlAmt()
   {
      return _AddlAmt;
   }
	
   /**
    * Gets the Additional Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional Amount or the specified default value.
    */
   public final String getAddlAmt( String defaultValue )
   {
      return _AddlAmt == null ? defaultValue : _AddlAmt;
   }
                  
   /**
    * Gets the Commission Reduction Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commission Reduction Rate or null.
    */
   public final String getCommRedRate()
   {
      return _CommRedRate;
   }
	
   /**
    * Gets the Commission Reduction Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Reduction Rate or the specified default value.
    */
   public final String getCommRedRate( String defaultValue )
   {
      return _CommRedRate == null ? defaultValue : _CommRedRate;
   }
                  
   /**
    * Gets the Type of Interest Rate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Type of Interest Rate or null.
    */
   public final String getIntRateType()
   {
      return _IntRateType;
   }
	
   /**
    * Gets the Type of Interest Rate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Type of Interest Rate or the specified default value.
    */
   public final String getIntRateType( String defaultValue )
   {
      return _IntRateType == null ? defaultValue : _IntRateType;
   }
                  
   /**
    * Gets the Investment Id field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment Id or null.
    */
   public final String getIntInvestId()
   {
      return _IntInvestId;
   }
	
   /**
    * Gets the Investment Id field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Id or the specified default value.
    */
   public final String getIntInvestId( String defaultValue )
   {
      return _IntInvestId == null ? defaultValue : _IntInvestId;
   }
                  
   /**
    * Gets the PF Crystalisation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PF Crystalisation or null.
    */
   public final String getPFCrystalisation()
   {
      return _PFCrystalisation;
   }
	
   /**
    * Gets the PF Crystalisation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PF Crystalisation or the specified default value.
    */
   public final String getPFCrystalisation( String defaultValue )
   {
      return _PFCrystalisation == null ? defaultValue : _PFCrystalisation;
   }
                  
   /**
    * Gets the PendTrd Contract field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PendTrd Contract or null.
    */
   public final String getPendTrdContract()
   {
      return _PendTrdContract;
   }
	
   /**
    * Gets the PendTrd Contract field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PendTrd Contract or the specified default value.
    */
   public final String getPendTrdContract( String defaultValue )
   {
      return _PendTrdContract == null ? defaultValue : _PendTrdContract;
   }
                  
   /**
    * Gets the Valuation Dt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Valuation Dt or null.
    */
   public final Date getValuationDt()
   {
      return _ValuationDt;
   }
	
   /**
    * Gets the Valuation Dt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valuation Dt or the specified default value.
    */
   public final Date getValuationDt( Date defaultValue )
   {
      return _ValuationDt == null ? defaultValue : _ValuationDt;
   }
                  
   /**
    * Gets the Payment Info field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment Info or null.
    */
   public final String getPaymentInfo()
   {
      return _PaymentInfo;
   }
	
   /**
    * Gets the Payment Info field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Info or the specified default value.
    */
   public final String getPaymentInfo( String defaultValue )
   {
      return _PaymentInfo == null ? defaultValue : _PaymentInfo;
   }
                  
   /**
    * Gets the Guarantee Override Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Guarantee Override Flag or null.
    */
   public final String getGuaranteeOverride()
   {
      return _GuaranteeOverride;
   }
	
   /**
    * Gets the Guarantee Override Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Guarantee Override Flag or the specified default value.
    */
   public final String getGuaranteeOverride( String defaultValue )
   {
      return _GuaranteeOverride == null ? defaultValue : _GuaranteeOverride;
   }
                  
   /**
    * Gets the Redemption Order field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemption Order or null.
    */
   public final String getRedemOrder()
   {
      return _RedemOrder;
   }
	
   /**
    * Gets the Redemption Order field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Order or the specified default value.
    */
   public final String getRedemOrder( String defaultValue )
   {
      return _RedemOrder == null ? defaultValue : _RedemOrder;
   }
                  
   /**
    * Gets the Right To Cancel field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Right To Cancel or null.
    */
   public final String getRightToCancel()
   {
      return _RightToCancel;
   }
	
   /**
    * Gets the Right To Cancel field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Right To Cancel or the specified default value.
    */
   public final String getRightToCancel( String defaultValue )
   {
      return _RightToCancel == null ? defaultValue : _RightToCancel;
   }
                  
   /**
    * Gets the RDR Advice field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RDR Advice or null.
    */
   public final String getRDRAdvice()
   {
      return _RDRAdvice;
   }
	
   /**
    * Gets the RDR Advice field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RDR Advice or the specified default value.
    */
   public final String getRDRAdvice( String defaultValue )
   {
      return _RDRAdvice == null ? defaultValue : _RDRAdvice;
   }
                  
   /**
    * Gets the SDRT Reportable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SDRT Reportable or null.
    */
   public final String getSDRTReportable()
   {
      return _SDRTReportable;
   }
	
   /**
    * Gets the SDRT Reportable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SDRT Reportable or the specified default value.
    */
   public final String getSDRTReportable( String defaultValue )
   {
      return _SDRTReportable == null ? defaultValue : _SDRTReportable;
   }
                  
   /**
    * Gets the Forced Rate Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Forced Rate Amount or null.
    */
   public final String getForcedRateAmt()
   {
      return _ForcedRateAmt;
   }
	
   /**
    * Gets the Forced Rate Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Forced Rate Amount or the specified default value.
    */
   public final String getForcedRateAmt( String defaultValue )
   {
      return _ForcedRateAmt == null ? defaultValue : _ForcedRateAmt;
   }
                  
   /**
    * Gets the PSD Advice Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PSD Advice Flag or null.
    */
   public final String getPSDAdvcFlg()
   {
      return _PSDAdvcFlg;
   }
	
   /**
    * Gets the PSD Advice Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PSD Advice Flag or the specified default value.
    */
   public final String getPSDAdvcFlg( String defaultValue )
   {
      return _PSDAdvcFlg == null ? defaultValue : _PSDAdvcFlg;
   }
                  
   /**
    * Gets the Pymt Routing Mthd field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pymt Routing Mthd or null.
    */
   public final String getPymtRoutingMthd()
   {
      return _PymtRoutingMthd;
   }
	
   /**
    * Gets the Pymt Routing Mthd field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pymt Routing Mthd or the specified default value.
    */
   public final String getPymtRoutingMthd( String defaultValue )
   {
      return _PymtRoutingMthd == null ? defaultValue : _PymtRoutingMthd;
   }
                  
   /**
    * Gets the Event Receipt Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Event Receipt Date or null.
    */
   public final Date getEventReceiptDate()
   {
      return _EventReceiptDate;
   }
	
   /**
    * Gets the Event Receipt Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Receipt Date or the specified default value.
    */
   public final Date getEventReceiptDate( Date defaultValue )
   {
      return _EventReceiptDate == null ? defaultValue : _EventReceiptDate;
   }
                  
   /**
    * Gets the Event Receipt Time field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Event Receipt Time or null.
    */
   public final String getEventReceiptTime()
   {
      return _EventReceiptTime;
   }
	
   /**
    * Gets the Event Receipt Time field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Receipt Time or the specified default value.
    */
   public final String getEventReceiptTime( String defaultValue )
   {
      return _EventReceiptTime == null ? defaultValue : _EventReceiptTime;
   }
                  
   /**
    * Gets the SourceOfTrade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SourceOfTrade or null.
    */
   public final String getSourceOfTrade()
   {
      return _SourceOfTrade;
   }
	
   /**
    * Gets the SourceOfTrade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SourceOfTrade or the specified default value.
    */
   public final String getSourceOfTrade( String defaultValue )
   {
      return _SourceOfTrade == null ? defaultValue : _SourceOfTrade;
   }
                  
   /**
    * Gets the ChannelOfTrade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ChannelOfTrade or null.
    */
   public final String getChannelOfTrade()
   {
      return _ChannelOfTrade;
   }
	
   /**
    * Gets the ChannelOfTrade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ChannelOfTrade or the specified default value.
    */
   public final String getChannelOfTrade( String defaultValue )
   {
      return _ChannelOfTrade == null ? defaultValue : _ChannelOfTrade;
   }
                  
   /**
    * Gets the Platform field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Platform or null.
    */
   public final String getPlatform()
   {
      return _Platform;
   }
	
   /**
    * Gets the Platform field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Platform or the specified default value.
    */
   public final String getPlatform( String defaultValue )
   {
      return _Platform == null ? defaultValue : _Platform;
   }
                  
   /**
    * Gets the Settle Network field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Settle Network or null.
    */
   public final String getSettleNetwork()
   {
      return _SettleNetwork;
   }
	
   /**
    * Gets the Settle Network field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settle Network or the specified default value.
    */
   public final String getSettleNetwork( String defaultValue )
   {
      return _SettleNetwork == null ? defaultValue : _SettleNetwork;
   }
                  
   /**
    * Gets the Delivery Network field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Delivery Network or null.
    */
   public final String getDeliveryNetwork()
   {
      return _DeliveryNetwork;
   }
	
   /**
    * Gets the Delivery Network field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery Network or the specified default value.
    */
   public final String getDeliveryNetwork( String defaultValue )
   {
      return _DeliveryNetwork == null ? defaultValue : _DeliveryNetwork;
   }
                  
   /**
    * Gets the Verified field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Verified or null.
    */
   public final Boolean getVerified()
   {
      return _Verified;
   }
	
   /**
    * Gets the Verified field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Verified or the specified default value.
    */
   public final boolean getVerified( boolean defaultValue )
   {
      return _Verified == null ? defaultValue : _Verified.booleanValue();
   }
                  
   /**
    * Gets the VerifiedBy field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the VerifiedBy or null.
    */
   public final String getVerifiedBy()
   {
      return _VerifiedBy;
   }
	
   /**
    * Gets the VerifiedBy field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the VerifiedBy or the specified default value.
    */
   public final String getVerifiedBy( String defaultValue )
   {
      return _VerifiedBy == null ? defaultValue : _VerifiedBy;
   }
                  
   /**
    * Gets the ToCashMsgType field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ToCashMsgType or null.
    */
   public final String getToCashMsgType()
   {
      return _ToCashMsgType;
   }
	
   /**
    * Gets the ToCashMsgType field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToCashMsgType or the specified default value.
    */
   public final String getToCashMsgType( String defaultValue )
   {
      return _ToCashMsgType == null ? defaultValue : _ToCashMsgType;
   }
                  
   /**
    * Gets the ToIntermediaryBank field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ToIntermediaryBank or null.
    */
   public final String getToIntermediaryBank()
   {
      return _ToIntermediaryBank;
   }
	
   /**
    * Gets the ToIntermediaryBank field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToIntermediaryBank or the specified default value.
    */
   public final String getToIntermediaryBank( String defaultValue )
   {
      return _ToIntermediaryBank == null ? defaultValue : _ToIntermediaryBank;
   }
                  
   /**
    * Gets the ToReceivingBank field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ToReceivingBank or null.
    */
   public final String getToReceivingBank()
   {
      return _ToReceivingBank;
   }
	
   /**
    * Gets the ToReceivingBank field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToReceivingBank or the specified default value.
    */
   public final String getToReceivingBank( String defaultValue )
   {
      return _ToReceivingBank == null ? defaultValue : _ToReceivingBank;
   }
                  
   /**
    * Gets the ToBeneficiary field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ToBeneficiary or null.
    */
   public final String getToBeneficiary()
   {
      return _ToBeneficiary;
   }
	
   /**
    * Gets the ToBeneficiary field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToBeneficiary or the specified default value.
    */
   public final String getToBeneficiary( String defaultValue )
   {
      return _ToBeneficiary == null ? defaultValue : _ToBeneficiary;
   }
                  
   /**
    * Gets the ToSpecialInstructions field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ToSpecialInstructions or null.
    */
   public final String getToSpecialInstructions()
   {
      return _ToSpecialInstructions;
   }
	
   /**
    * Gets the ToSpecialInstructions field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToSpecialInstructions or the specified default value.
    */
   public final String getToSpecialInstructions( String defaultValue )
   {
      return _ToSpecialInstructions == null ? defaultValue : _ToSpecialInstructions;
   }
                  
   /**
    * Gets the ToSettlementAccount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ToSettlementAccount or null.
    */
   public final String getToSettlementAccount()
   {
      return _ToSettlementAccount;
   }
	
   /**
    * Gets the ToSettlementAccount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToSettlementAccount or the specified default value.
    */
   public final String getToSettlementAccount( String defaultValue )
   {
      return _ToSettlementAccount == null ? defaultValue : _ToSettlementAccount;
   }
                  
   /**
    * Gets the ToInternalSettlementAccount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ToInternalSettlementAccount or null.
    */
   public final String getToInternalSettlementAccount()
   {
      return _ToInternalSettlementAccount;
   }
	
   /**
    * Gets the ToInternalSettlementAccount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ToInternalSettlementAccount or the specified default value.
    */
   public final String getToInternalSettlementAccount( String defaultValue )
   {
      return _ToInternalSettlementAccount == null ? defaultValue : _ToInternalSettlementAccount;
   }
                  
   /**
    * Gets the FrCashMsgType field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FrCashMsgType or null.
    */
   public final String getFrCashMsgType()
   {
      return _FrCashMsgType;
   }
	
   /**
    * Gets the FrCashMsgType field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FrCashMsgType or the specified default value.
    */
   public final String getFrCashMsgType( String defaultValue )
   {
      return _FrCashMsgType == null ? defaultValue : _FrCashMsgType;
   }
                  
   /**
    * Gets the FrIntermediaryBank field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FrIntermediaryBank or null.
    */
   public final String getFrIntermediaryBank()
   {
      return _FrIntermediaryBank;
   }
	
   /**
    * Gets the FrIntermediaryBank field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FrIntermediaryBank or the specified default value.
    */
   public final String getFrIntermediaryBank( String defaultValue )
   {
      return _FrIntermediaryBank == null ? defaultValue : _FrIntermediaryBank;
   }
                  
   /**
    * Gets the FrReceivingBank field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FrReceivingBank or null.
    */
   public final String getFrReceivingBank()
   {
      return _FrReceivingBank;
   }
	
   /**
    * Gets the FrReceivingBank field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FrReceivingBank or the specified default value.
    */
   public final String getFrReceivingBank( String defaultValue )
   {
      return _FrReceivingBank == null ? defaultValue : _FrReceivingBank;
   }
                  
   /**
    * Gets the FrBeneficiary field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FrBeneficiary or null.
    */
   public final String getFrBeneficiary()
   {
      return _FrBeneficiary;
   }
	
   /**
    * Gets the FrBeneficiary field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FrBeneficiary or the specified default value.
    */
   public final String getFrBeneficiary( String defaultValue )
   {
      return _FrBeneficiary == null ? defaultValue : _FrBeneficiary;
   }
                  
   /**
    * Gets the FrSpecialInstructions field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FrSpecialInstructions or null.
    */
   public final String getFrSpecialInstructions()
   {
      return _FrSpecialInstructions;
   }
	
   /**
    * Gets the FrSpecialInstructions field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FrSpecialInstructions or the specified default value.
    */
   public final String getFrSpecialInstructions( String defaultValue )
   {
      return _FrSpecialInstructions == null ? defaultValue : _FrSpecialInstructions;
   }
                  
   /**
    * Gets the FrSettlementAccount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FrSettlementAccount or null.
    */
   public final String getFrSettlementAccount()
   {
      return _FrSettlementAccount;
   }
	
   /**
    * Gets the FrSettlementAccount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FrSettlementAccount or the specified default value.
    */
   public final String getFrSettlementAccount( String defaultValue )
   {
      return _FrSettlementAccount == null ? defaultValue : _FrSettlementAccount;
   }
                  
   /**
    * Gets the FrInternalSettlementAccount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FrInternalSettlementAccount or null.
    */
   public final String getFrInternalSettlementAccount()
   {
      return _FrInternalSettlementAccount;
   }
	
   /**
    * Gets the FrInternalSettlementAccount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FrInternalSettlementAccount or the specified default value.
    */
   public final String getFrInternalSettlementAccount( String defaultValue )
   {
      return _FrInternalSettlementAccount == null ? defaultValue : _FrInternalSettlementAccount;
   }
                  
   /**
    * Gets the G1Units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the G1Units or null.
    */
   public final String getG1Units()
   {
      return _G1Units;
   }
	
   /**
    * Gets the G1Units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the G1Units or the specified default value.
    */
   public final String getG1Units( String defaultValue )
   {
      return _G1Units == null ? defaultValue : _G1Units;
   }
                  
   /**
    * Gets the G2Units field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the G2Units or null.
    */
   public final String getG2Units()
   {
      return _G2Units;
   }
	
   /**
    * Gets the G2Units field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the G2Units or the specified default value.
    */
   public final String getG2Units( String defaultValue )
   {
      return _G2Units == null ? defaultValue : _G2Units;
   }
                  
   /**
    * Gets the ExtAccountNum field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ExtAccountNum or null.
    */
   public final String getExtAccountNum()
   {
      return _ExtAccountNum;
   }
	
   /**
    * Gets the ExtAccountNum field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ExtAccountNum or the specified default value.
    */
   public final String getExtAccountNum( String defaultValue )
   {
      return _ExtAccountNum == null ? defaultValue : _ExtAccountNum;
   }
                  
   /**
    * Gets the AggrType field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AggrType or null.
    */
   public final String getAggrType()
   {
      return _AggrType;
   }
	
   /**
    * Gets the AggrType field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AggrType or the specified default value.
    */
   public final String getAggrType( String defaultValue )
   {
      return _AggrType == null ? defaultValue : _AggrType;
   }
                  
   /**
    * Gets the SrcOfFndsChk field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SrcOfFndsChk or null.
    */
   public final String getSrcOfFndsChk()
   {
      return _SrcOfFndsChk;
   }
	
   /**
    * Gets the SrcOfFndsChk field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SrcOfFndsChk or the specified default value.
    */
   public final String getSrcOfFndsChk( String defaultValue )
   {
      return _SrcOfFndsChk == null ? defaultValue : _SrcOfFndsChk;
   }
                  
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      _BrokerCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _BranchCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _SlsrepCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettleCurrency = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettleCurrName = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExchRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _Fee = responseBuffer.decodeString(responseBuffer.getNextField());
      _FlatPercent = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _FeeCurrency = responseBuffer.decodeString(responseBuffer.getNextField());
      _BELFee = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AdminFeeAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _OverrideDSC = responseBuffer.decodeString(responseBuffer.getNextField());
      _OverrideDSCDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _OverrideAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _OverrideTax = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _FedTaxRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _FedTaxPUD = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProvTaxRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProvTaxPUD = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProvSales = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProvSalesName = responseBuffer.decodeString(responseBuffer.getNextField());
      _DepositType = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _DepositTypeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedCodeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _Payment = responseBuffer.decodeString(responseBuffer.getNextField());
      _PayType = responseBuffer.decodeString(responseBuffer.getNextField());
      _PayTypeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AddrLine = responseBuffer.decodeString(responseBuffer.getNextField());
      _ChqSupCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ChqSupCodeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _OrderSource = responseBuffer.decodeString(responseBuffer.getNextField());
      _OrderSrcDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettleSource = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettleSrcDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _SrcOfFund = responseBuffer.decodeString(responseBuffer.getNextField());
      _SrcOfFundDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _SrcOfAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettleType = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettleTypeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExpGNSettle = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettledBy = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettledByDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoundFlag = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoundFlagDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _CreditFreq = responseBuffer.decodeString(responseBuffer.getNextField());
      _CreditFreqDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExtraCommission = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CertRequired = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CertIssued = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ConfirmReq = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _OnStmt = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RecptIssued = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ExclMFCSSettle = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _GuaranteeDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _MaturityDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _InterestRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _BrokerName = responseBuffer.decodeString(responseBuffer.getNextField());
      _BranchName = responseBuffer.decodeString(responseBuffer.getNextField());
      _SlsrepName = responseBuffer.decodeString(responseBuffer.getNextField());
      _SlsrepAltName = responseBuffer.decodeString(responseBuffer.getNextField());
      _DepId = responseBuffer.decodeString(responseBuffer.getNextField());
      _Remarks1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _Remarks2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _Remarks3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RejCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _RejCodeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _Accountable = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctableDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _DateStamp = responseBuffer.decodeDate(responseBuffer.getNextField());
      _TimeStamp = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProcessDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _Allocation = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CansimRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _InitPurch = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BackDatedReason = responseBuffer.decodeString(responseBuffer.getNextField());
      _SplitComm = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DealDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _DealTime = responseBuffer.decodeString(responseBuffer.getNextField());
      _DSCOverrideCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _DSCOverrideAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _AccountTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _ClassToCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxTransType = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxFundCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _rxClassCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _Amount = responseBuffer.decodeString(responseBuffer.getNextField());
      _AmountType = responseBuffer.decodeString(responseBuffer.getNextField());
      _GrossOrNet = responseBuffer.decodeString(responseBuffer.getNextField());
      _UseEnteredFee = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ExchInFee = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExchInFlatPercent = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ModPerm = responseBuffer.decodeString(responseBuffer.getNextField());
      _FirstName = responseBuffer.decodeString(responseBuffer.getNextField());
      _LastName = responseBuffer.decodeString(responseBuffer.getNextField());
      _InitPurchDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _ConfirmReqDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _RecptIssuedDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _Baycom = responseBuffer.decodeString(responseBuffer.getNextField());
      _BaycomTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankCharge = responseBuffer.decodeString(responseBuffer.getNextField());
      _ValueDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _PayMethod = responseBuffer.decodeString(responseBuffer.getNextField());
      _ACHProcessor = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToBrokerCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToSlsRepCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _NetworkID = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExtTransNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _SendRefNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _PartRefNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _MasterRefNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExchOutFee = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExchOutFlatPrcnt = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ChargeERSTTRFee = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ChargeWDFee = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _MirTransNum = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _BorrowedFunds = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TransSeq = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _FrSettlLocCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrDeliveryTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrSettlLocDescription = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrInfavourOf = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrForAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrClearingMethod = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToSettlLocCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToFrDeliveryTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToSettlLocDescription = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToInFavourOf = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToForAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToClearingMethod = responseBuffer.decodeString(responseBuffer.getNextField());
      _IFeeTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _ChargeADLFee = responseBuffer.decodeString(responseBuffer.getNextField());
      _LSIFCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AltAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _RefNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundWKN = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundISIN = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundToWKN = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundToISIN = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcqFeeOption = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettleDateOverriden = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _FrSettlInstrCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToSettlInstrCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundBroker = responseBuffer.decodeString(responseBuffer.getNextField());
      _AggrOption = responseBuffer.decodeString(responseBuffer.getNextField());
      _BrkSettlDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _OtherConfirmType = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExternalPrice = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExternalSettleDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ExternalSettleAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _ROAAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _DeliveryMethod = responseBuffer.decodeString(responseBuffer.getNextField());
      _AdjustForTransNum = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _TransId = responseBuffer.decodeString(responseBuffer.getNextField());
      _SplitCommRebookTransID = responseBuffer.decodeString(responseBuffer.getNextField());
      _EUSDAvgCost = responseBuffer.decodeString(responseBuffer.getNextField());
      _EUSDAvgTIS = responseBuffer.decodeString(responseBuffer.getNextField());
      _EUSDCostOverride = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _EUSDTISOverride = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _MCHFile = responseBuffer.decodeString(responseBuffer.getNextField());
      _SecReconFile = responseBuffer.decodeString(responseBuffer.getNextField());
      _ESGSettle = responseBuffer.decodeString(responseBuffer.getNextField());
      _NSCControlNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _TradePayInstrExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PayInstructOption = responseBuffer.decodeString(responseBuffer.getNextField());
      _MFPayment = responseBuffer.decodeString(responseBuffer.getNextField());
      _INDC = responseBuffer.decodeString(responseBuffer.getNextField());
      _ModDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ModUser = responseBuffer.decodeString(responseBuffer.getNextField());
      _RecptStatus = responseBuffer.decodeString(responseBuffer.getNextField());
      _LinkedEntityName = responseBuffer.decodeString(responseBuffer.getNextField());
      _LinkedEntityId = responseBuffer.decodeString(responseBuffer.getNextField());
      _Authorized = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociatedTransId = responseBuffer.decodeString(responseBuffer.getNextField());
      _GrantRepayReason = responseBuffer.decodeString(responseBuffer.getNextField());
      _NeedToReportHRDC = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TaxYear = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _Tainted = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _OCRedYear = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _AssistedContrAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctOwnerID = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctOwnerName = responseBuffer.decodeString(responseBuffer.getNextField());
      _NetworkRespRequired = responseBuffer.decodeString(responseBuffer.getNextField());
      _EAPCESGPaid = responseBuffer.decodeString(responseBuffer.getNextField());
      _IntInvestUUID = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvestmentNo = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvestStatus = responseBuffer.decodeString(responseBuffer.getNextField());
      _IntCalcMthd = responseBuffer.decodeString(responseBuffer.getNextField());
      _IntInvestType = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvestTerm = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _IntRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _GIMaturityDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _IntCredFreq = responseBuffer.decodeString(responseBuffer.getNextField());
      _LastIntCredDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _AddlAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _CommRedRate = responseBuffer.decodeString(responseBuffer.getNextField());
      _IntRateType = responseBuffer.decodeString(responseBuffer.getNextField());
      _IntInvestId = responseBuffer.decodeString(responseBuffer.getNextField());
      _PFCrystalisation = responseBuffer.decodeString(responseBuffer.getNextField());
      _PendTrdContract = responseBuffer.decodeString(responseBuffer.getNextField());
      _ValuationDt = responseBuffer.decodeDate(responseBuffer.getNextField());
      _PaymentInfo = responseBuffer.decodeString(responseBuffer.getNextField());
      _GuaranteeOverride = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedemOrder = responseBuffer.decodeString(responseBuffer.getNextField());
      _RightToCancel = responseBuffer.decodeString(responseBuffer.getNextField());
      _RDRAdvice = responseBuffer.decodeString(responseBuffer.getNextField());
      _SDRTReportable = responseBuffer.decodeString(responseBuffer.getNextField());
      _ForcedRateAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _PSDAdvcFlg = responseBuffer.decodeString(responseBuffer.getNextField());
      _PymtRoutingMthd = responseBuffer.decodeString(responseBuffer.getNextField());
      _EventReceiptDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _EventReceiptTime = responseBuffer.decodeString(responseBuffer.getNextField());
      _SourceOfTrade = responseBuffer.decodeString(responseBuffer.getNextField());
      _ChannelOfTrade = responseBuffer.decodeString(responseBuffer.getNextField());
      _Platform = responseBuffer.decodeString(responseBuffer.getNextField());
      _SettleNetwork = responseBuffer.decodeString(responseBuffer.getNextField());
      _DeliveryNetwork = responseBuffer.decodeString(responseBuffer.getNextField());
      _Verified = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _VerifiedBy = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToCashMsgType = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToIntermediaryBank = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToReceivingBank = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToBeneficiary = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToSpecialInstructions = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToSettlementAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _ToInternalSettlementAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrCashMsgType = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrIntermediaryBank = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrReceivingBank = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrBeneficiary = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrSpecialInstructions = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrSettlementAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _FrInternalSettlementAccount = responseBuffer.decodeString(responseBuffer.getNextField());
      _G1Units = responseBuffer.decodeString(responseBuffer.getNextField());
      _G2Units = responseBuffer.decodeString(responseBuffer.getNextField());
      _ExtAccountNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _AggrType = responseBuffer.decodeString(responseBuffer.getNextField());
      _SrcOfFndsChk = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
