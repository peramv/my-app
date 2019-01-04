
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Pending Transactions view.
 * For additional view information see <A HREF="../../../../viewspecs/PendTxnInq.doc">PendTxnInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PendTxnInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * TradeDate member array.
    */
   private Date[] _TradeDate = null;
   
   /**
    * SettleDate member array.
    */
   private Date[] _SettleDate = null;
   
   /**
    * TransType member array.
    */
   private String[] _TransType = null;
   
   /**
    * TransTypeDescription member array.
    */
   private String[] _TransTypeDesc = null;
   
   /**
    * Transaction Number member array.
    */
   private Integer[] _TransNum = null;
   
   /**
    * Account To member array.
    */
   private String[] _AccountTo = null;
   
   /**
    * Account To Name member array.
    */
   private String[] _AcctToName = null;
   
   /**
    * Fund To Code member array.
    */
   private String[] _FundTo = null;
   
   /**
    * Class To Code member array.
    */
   private String[] _ClassToCode = null;
   
   /**
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Amount Type Code member array.
    */
   private String[] _AmountType = null;
   
   /**
    * Amount Type Description member array.
    */
   private String[] _AmountTypeDesc = null;
   
   /**
    * Gross or Net member array.
    */
   private Boolean[] _GrossOrNet = null;
   
   /**
    * Order Type member array.
    */
   private Boolean[] _OrderType = null;
   
   /**
    * Wire Order Number member array.
    */
   private String[] _WireOrdNum = null;
   
   /**
    * Batch User member array.
    */
   private String[] _BatchUser = null;
   
   /**
    * Good Bad Code member array.
    */
   private String[] _GoodBad = null;
   
   /**
    * Pending Trade Record ID member array.
    */
   private Integer[] _PendingRid = null;
   
   /**
    * Settlement Currency member array.
    */
   private String[] _SettleCurrency = null;
   
   /**
    * Shareholder Number member array.
    */
   private String[] _ShrNum = null;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAccountNum = null;
   
   /**
    * Good Bad Description member array.
    */
   private String[] _GoodBadDesc = null;
   
   /**
    * Order Type Description member array.
    */
   private String[] _OrderTypeDesc = null;
   
   /**
    * AMS Trade member array.
    */
   private Boolean[] _AMSTrade = null;
   
   /**
    * Trade AMSCode member array.
    */
   private String[] _TradeAMSCode = null;
   
   /**
    * Transaction Fee member array.
    */
   private String[] _TxnFee = null;
   
   /**
    * Acq Fee Option member array.
    */
   private String[] _AcqFeeOption = null;
   
   /**
    * Fee member array.
    */
   private String[] _Fee = null;
   
   /**
    * FlatPercent member array.
    */
   private Boolean[] _FlatPercent = null;
   
   /**
    * Fee Currency member array.
    */
   private String[] _FeeCurrency = null;
   
   /**
    * BEL Fee member array.
    */
   private Boolean[] _BELFee = null;
   
   /**
    * Admin Fee Amount member array.
    */
   private String[] _AdminFeeAmt = null;
   
   /**
    * Is the fee user entered? member array.
    */
   private Boolean[] _UseEnteredFee = null;
   
   /**
    * Exchange In Fee member array.
    */
   private String[] _ExchInFee = null;
   
   /**
    * Exchange In Fee Flat/Percent member array.
    */
   private Boolean[] _ExchInFlatPercent = null;
   
   /**
    * Exchange Out Fee member array.
    */
   private String[] _ExchOutFee = null;
   
   /**
    * Exchange Out Fee Flat/Percent member array.
    */
   private Boolean[] _ExchOutFlatPrcnt = null;
   
   /**
    * ChargeERSTTRFee member array.
    */
   private Boolean[] _ChargeERSTTRFee = null;
   
   /**
    * ChargeWDFee member array.
    */
   private Boolean[] _ChargeWDFee = null;
   
   /**
    * Fee To member array.
    */
   private String[] _IFeeTo = null;
   
   /**
    * charge additional fee member array.
    */
   private String[] _ChargeADLFee = null;
   
   /**
    * Baycom number member array.
    */
   private String[] _Baycom = null;
   
   /**
    * Baycom to number member array.
    */
   private String[] _BaycomTo = null;
   
   /**
    * Fund ISIN member array.
    */
   private String[] _FundISIN = null;
   
   /**
    * Fund To ISIN member array.
    */
   private String[] _FundToISIN = null;
   
   /**
    * Fund Currency member array.
    */
   private String[] _FundCurrency = null;
   
   /**
    * System level latest NAV member array.
    */
   private String[] _SysNAV = null;
   
   /**
    * System level latest Exchange Rate member array.
    */
   private String[] _SysExchRate = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Broker Code member array.
    */
   private String[] _BrokerCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = null;
   
   /**
    * SlsRep Code member array.
    */
   private String[] _SlsRepCode = null;
   
   /**
    * Broker Name member array.
    */
   private String[] _BrokerName = null;
   
   /**
    * Branch Name member array.
    */
   private String[] _BranchName = null;
   
   /**
    * Sls Rep Name member array.
    */
   private String[] _SlsRepName = null;
   
   /**
    * To Broker Code member array.
    */
   private String[] _ToBrokerCode = null;
   
   /**
    * To Sls Rep Code member array.
    */
   private String[] _ToSlsRepCode = null;
   
   /**
    * Remarks line1 member array.
    */
   private String[] _Remarks1 = null;
   
   /**
    * Remarks line 2 member array.
    */
   private String[] _Remarks2 = null;
   
   /**
    * Remarks line 3 member array.
    */
   private String[] _Remarks3 = null;
   
   /**
    * Is it an initial purchase member array.
    */
   private Boolean[] _InitPurch = null;
   
   /**
    * Is the trade verified member array.
    */
   private Boolean[] _Verified = null;
   
   /**
    * Account holder first name member array.
    */
   private String[] _FirstName = null;
   
   /**
    * Account holder last name member array.
    */
   private String[] _LastName = null;
   
   /**
    * Network ID member array.
    */
   private String[] _NetworkId = null;
   
   /**
    * External Transaction Number member array.
    */
   private String[] _ExtTransNum = null;
   
   /**
    * Sender's Reference Number member array.
    */
   private String[] _SendRefNum = null;
   
   /**
    * Discount Rate member array.
    */
   private String[] _DiscountRate = null;
   
   /**
    * Transaction Id member array.
    */
   private String[] _TransId = null;
   
   /**
    * Exchange Rate member array.
    */
   private String[] _ExchRate = null;
   
   /**
    * Split Commission % for broker member array.
    */
   private String[] _BrokerCommPrcnt = null;
   
   /**
    * Split Commission Amt for broker member array.
    */
   private String[] _BrokerCommRate = null;
   
   /**
    * Split Commission % for branch member array.
    */
   private String[] _BranchCommPrcnt = null;
   
   /**
    * Split Commission Amt for branch member array.
    */
   private String[] _BranchCommRate = null;
   
   /**
    * Split Commission % for sls rep member array.
    */
   private String[] _SlsRepCommPrcnt = null;
   
   /**
    * Split Commission Amt for sls rep member array.
    */
   private String[] _SlsRepCommRate = null;
   
   /**
    * Split Commission % for mgmt company member array.
    */
   private String[] _MgmtCompCommPrcnt = null;
   
   /**
    * Split Commission Amt for mgmt company member array.
    */
   private String[] _MgmtCompCommRate = null;
   
   /**
    * Comm Prcnt total member array.
    */
   private String[] _TotalCommPrcnt = null;
   
   /**
    * Comm Amt total member array.
    */
   private String[] _TotalCommRate = null;
   
   /**
    * Bank ID member array.
    */
   private String[] _BankId = null;
   
   /**
    * Bank Type member array.
    */
   private String[] _BankType = null;
   
   /**
    * Bank ID number member array.
    */
   private String[] _BankIdNum = null;
   
   /**
    * Bank Country member array.
    */
   private String[] _BankCntry = null;
   
   /**
    * Bank Pstl member array.
    */
   private String[] _BankPstl = null;
   
   /**
    * Bank Address line 1 member array.
    */
   private String[] _BankAddr1 = null;
   
   /**
    * Bank Address line 2 member array.
    */
   private String[] _BankAddr2 = null;
   
   /**
    * Bank Address line 3 member array.
    */
   private String[] _BankAddr3 = null;
   
   /**
    * Bank Address line 4 member array.
    */
   private String[] _BankAddr4 = null;
   
   /**
    * Bank Address line 5 member array.
    */
   private String[] _BankAddr5 = null;
   
   /**
    * Institution Name member array.
    */
   private String[] _InstName = null;
   
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNum = null;
   
   /**
    * Bank Account Name member array.
    */
   private String[] _BankAcctName = null;
   
   /**
    * Correspondent Bank Id member array.
    */
   private String[] _CorrespBankId = null;
   
   /**
    * Correspondent Bank type member array.
    */
   private String[] _CorrespBankType = null;
   
   /**
    * Correspondent Bank Id Number member array.
    */
   private String[] _CorrespBankIdNum = null;
   
   /**
    * Correspondent Bank Country member array.
    */
   private String[] _CorrespBankCntry = null;
   
   /**
    * Correspondent Bank Postal Code member array.
    */
   private String[] _CorrespBankPstl = null;
   
   /**
    * Correspondent Bank Address Line 1 member array.
    */
   private String[] _CorrespBankAddr1 = null;
   
   /**
    * Correspondent Bank Address Line 2 member array.
    */
   private String[] _CorrespBankAddr2 = null;
   
   /**
    * Correspondent Bank Address Line 3 member array.
    */
   private String[] _CorrespBankAddr3 = null;
   
   /**
    * Correspondent Bank Address Line 4 member array.
    */
   private String[] _CorrespBankAddr4 = null;
   
   /**
    * Correspondent Bank Address Line 5 member array.
    */
   private String[] _CorrespBankAddr5 = null;
   
   /**
    * Correspondent Institution Name member array.
    */
   private String[] _CorrespInstName = null;
   
   /**
    * Credit Info Line1 member array.
    */
   private String[] _CreditInfoLine1 = null;
   
   /**
    * Credit Info Line2 member array.
    */
   private String[] _CreditInfoLine2 = null;
   
   /**
    * Pay Reason Line 1 member array.
    */
   private String[] _PayReason1 = null;
   
   /**
    * Pay Reason Line 2 member array.
    */
   private String[] _PayReason2 = null;
   
   /**
    * Condition Rate member array.
    */
   private String[] _ConditionRate = null;
   
   /**
    * Extra Commission member array.
    */
   private Boolean[] _ExtraCommission = null;
   
   /**
    * Override DSC member array.
    */
   private String[] _OverrideDSC = null;
   
   /**
    * Override DSC Desc member array.
    */
   private String[] _OverrideDSCDesc = null;
   
   /**
    * Override Amount member array.
    */
   private String[] _OverrideAmt = null;
   
   /**
    * Override Tax member array.
    */
   private Boolean[] _OverrideTax = null;
   
   /**
    * Federal Tax Rate member array.
    */
   private String[] _FedTaxRate = null;
   
   /**
    * Federal Tax PUD member array.
    */
   private String[] _FedTaxPUD = null;
   
   /**
    * Provincial Tax Rate member array.
    */
   private String[] _ProvTaxRate = null;
   
   /**
    * Provincial Tax PUD member array.
    */
   private String[] _ProvTaxPUD = null;
   
   /**
    * DSC Override Code member array.
    */
   private String[] _DSCOverridecode = null;
   
   /**
    * DSC Override Amount member array.
    */
   private String[] _DSCOverrideAmt = null;
   
   /**
    * ROA Amount member array.
    */
   private String[] _ROAAmount = null;
   
   /**
    * Payment Type member array.
    */
   private String[] _PayType = null;
   
   /**
    * Payment Type Desc member array.
    */
   private String[] _PayTypeDesc = null;
   
   /**
    * Settlement Currency Name member array.
    */
   private String[] _SettleCurrName = null;
   
   /**
    * Initial Purchase Desc member array.
    */
   private String[] _InitPurchDesc = null;
   
   /**
    * Rejection Code member array.
    */
   private String[] _RejCode = null;
   
   /**
    * Rejection Code Desc member array.
    */
   private String[] _RejCodeDesc = null;
   
   /**
    * Broker Commission Amount member array.
    */
   private String[] _BrokerCommAmt = null;
   
   /**
    * Branch Commission Amount member array.
    */
   private String[] _BranchCommAmt = null;
   
   /**
    * Sls Rep Commission Amount member array.
    */
   private String[] _SlsRepCommAmt = null;
   
   /**
    * Mgmt Comp Commission Amount member array.
    */
   private String[] _MgmtCompCommAmt = null;
   
   /**
    * Total Commission Amount member array.
    */
   private String[] _TotalCommAmt = null;
   
   /**
    * Indicates if view will return Pend, Proc or Both trades member array.
    */
   private String[] _rxRecordType = null;
   
   /**
    * Additional fee rate for proc trades member array.
    */
   private Integer[] _ADLFeePrcnt = null;
   
   /**
    * Additional fee amount for proc trades member array.
    */
   private String[] _ADLFeeAmt = null;
   
   /**
    * Environement Code member array.
    */
   private String[] _CompanyCode = null;
   
   /**
    * Processed trade units member array.
    */
   private String[] _Units = null;
   
   /**
    * Gross amount in fund currency for proc trade member array.
    */
   private String[] _GrossAmt = null;
   
   /**
    * Net amount in fund currency for proc trade member array.
    */
   private String[] _NetAmt = null;
   
   /**
    * Gross amount in settlement currency for proc trade member array.
    */
   private String[] _GrossAmtInSettleCurr = null;
   
   /**
    * Net amount in settlement currency for processed trade. member array.
    */
   private String[] _NetAmtInSettleCurr = null;
   
   /**
    * Flag indicating if trade is settled member array.
    */
   private Boolean[] _Settled = null;
   
   /**
    * Indicates if money out was full or partial money out. member array.
    */
   private String[] _FullPartial = null;
   
   /**
    * Full estimanted money out. member array.
    */
   private String[] _MktValue = null;
   
   /**
    * SettleDate of transfer/exchange in member array.
    */
   private Date[] _SettleInDate = null;
   
   /**
    * TUP - Traded unit position at the time the trade was entered member array.
    */
   private String[] _TUPUnits = null;
   
   /**
    * SUP - Settled units + marked settled units member array.
    */
   private String[] _SUPUnits = null;
   
   /**
    * TUP Tolerance % - Environment or fund level, whichever applies member array.
    */
   private String[] _TUPToleranceRate = null;
   
   /**
    * TUP tolerance units - Traded unit position X TUP Tolerance % member array.
    */
   private String[] _TUPToleranceUnits = null;
   
   /**
    * TUP Oversell – Unit amount member array.
    */
   private String[] _TUPOversellUnits = null;
   
   /**
    * SUP Oversell – Unit amount member array.
    */
   private String[] _SUPOversellUnits = null;
   
   /**
    * Registration Agent Code member array.
    */
   private String[] _RegAgentCode = null;
   
   /**
    * Account Tax Type member array.
    */
   private String[] _AccountTaxType = null;
   
   /**
    * Reference Code member array.
    */
   private String[] _RefCode = null;
   
   /**
    * RDR Trade Value member array.
    */
   private String[] _RDRTradeValue = null;
   
   /**
    * RDR Default Value member array.
    */
   private String[] _RDRDefaultValue = null;
   
   /**
    * Event Receipt Date member array.
    */
   private Date[] _EventReceiptDate = null;
   
   /**
    * Event Receipt Time member array.
    */
   private String[] _EventReceiptTime = null;
   
   /**
    * Dealer Action member array.
    */
   private Boolean[] _DealerAction = null;
   

   /**
    * Constructs the PendTxnInqView object.
    * 
    */
   public PendTxnInqView()
   {
      super ( new PendTxnInqRequest() );
   }

   /**
    * Constructs the PendTxnInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PendTxnInqView( String hostEncoding )
   {
      super ( new PendTxnInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PendTxnInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PendTxnInqRequest object.
    */
   public final PendTxnInqRequest getRequest()
   {
      return (PendTxnInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the TradeDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TradeDate or null.
    */
   public final Date getTradeDate( int index )
   {
      return _TradeDate[index];
   }
    
   /**
    * Gets the TradeDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TradeDate or the specified default value.
    */
   public final Date getTradeDate( int index, Date defaultValue )
   {
      return _TradeDate[index] == null ? defaultValue : _TradeDate[index];
   }
    
   /**
    * Gets the array of TradeDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TradeDate values.
    */
   public final Date[] getTradeDateArray()
   {
      return _TradeDate;
   }
    
   /**
    * Gets the SettleDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SettleDate or null.
    */
   public final Date getSettleDate( int index )
   {
      return _SettleDate[index];
   }
    
   /**
    * Gets the SettleDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SettleDate or the specified default value.
    */
   public final Date getSettleDate( int index, Date defaultValue )
   {
      return _SettleDate[index] == null ? defaultValue : _SettleDate[index];
   }
    
   /**
    * Gets the array of SettleDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SettleDate values.
    */
   public final Date[] getSettleDateArray()
   {
      return _SettleDate;
   }
    
   /**
    * Gets the TransType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransType or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the TransType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransType or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of TransType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransType values.
    */
   public final String[] getTransTypeArray()
   {
      return _TransType;
   }
    
   /**
    * Gets the TransTypeDescription field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransTypeDescription or null.
    */
   public final String getTransTypeDesc( int index )
   {
      return _TransTypeDesc[index];
   }
    
   /**
    * Gets the TransTypeDescription field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransTypeDescription or the specified default value.
    */
   public final String getTransTypeDesc( int index, String defaultValue )
   {
      return _TransTypeDesc[index] == null ? defaultValue : _TransTypeDesc[index];
   }
    
   /**
    * Gets the array of TransTypeDescription fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransTypeDescription values.
    */
   public final String[] getTransTypeDescArray()
   {
      return _TransTypeDesc;
   }
    
   /**
    * Gets the Transaction Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Number or null.
    */
   public final Integer getTransNum( int index )
   {
      return _TransNum[index];
   }
    
   /**
    * Gets the Transaction Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Number or the specified default value.
    */
   public final int getTransNum( int index, int defaultValue )
   {
      return _TransNum[index] == null ? defaultValue : _TransNum[index].intValue();
   }
    
   /**
    * Gets the array of Transaction Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Number values.
    */
   public final Integer[] getTransNumArray()
   {
      return _TransNum;
   }
    
   /**
    * Gets the Account To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account To or null.
    */
   public final String getAccountTo( int index )
   {
      return _AccountTo[index];
   }
    
   /**
    * Gets the Account To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account To or the specified default value.
    */
   public final String getAccountTo( int index, String defaultValue )
   {
      return _AccountTo[index] == null ? defaultValue : _AccountTo[index];
   }
    
   /**
    * Gets the array of Account To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account To values.
    */
   public final String[] getAccountToArray()
   {
      return _AccountTo;
   }
    
   /**
    * Gets the Account To Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account To Name or null.
    */
   public final String getAcctToName( int index )
   {
      return _AcctToName[index];
   }
    
   /**
    * Gets the Account To Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account To Name or the specified default value.
    */
   public final String getAcctToName( int index, String defaultValue )
   {
      return _AcctToName[index] == null ? defaultValue : _AcctToName[index];
   }
    
   /**
    * Gets the array of Account To Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account To Name values.
    */
   public final String[] getAcctToNameArray()
   {
      return _AcctToName;
   }
    
   /**
    * Gets the Fund To Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund To Code or null.
    */
   public final String getFundTo( int index )
   {
      return _FundTo[index];
   }
    
   /**
    * Gets the Fund To Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund To Code or the specified default value.
    */
   public final String getFundTo( int index, String defaultValue )
   {
      return _FundTo[index] == null ? defaultValue : _FundTo[index];
   }
    
   /**
    * Gets the array of Fund To Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund To Code values.
    */
   public final String[] getFundToArray()
   {
      return _FundTo;
   }
    
   /**
    * Gets the Class To Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class To Code or null.
    */
   public final String getClassToCode( int index )
   {
      return _ClassToCode[index];
   }
    
   /**
    * Gets the Class To Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class To Code or the specified default value.
    */
   public final String getClassToCode( int index, String defaultValue )
   {
      return _ClassToCode[index] == null ? defaultValue : _ClassToCode[index];
   }
    
   /**
    * Gets the array of Class To Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class To Code values.
    */
   public final String[] getClassToCodeArray()
   {
      return _ClassToCode;
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount or null.
    */
   public final String getAmount( int index )
   {
      return _Amount[index];
   }
    
   /**
    * Gets the Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount or the specified default value.
    */
   public final String getAmount( int index, String defaultValue )
   {
      return _Amount[index] == null ? defaultValue : _Amount[index];
   }
    
   /**
    * Gets the array of Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount values.
    */
   public final String[] getAmountArray()
   {
      return _Amount;
   }
    
   /**
    * Gets the Amount Type Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Type Code or null.
    */
   public final String getAmountType( int index )
   {
      return _AmountType[index];
   }
    
   /**
    * Gets the Amount Type Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type Code or the specified default value.
    */
   public final String getAmountType( int index, String defaultValue )
   {
      return _AmountType[index] == null ? defaultValue : _AmountType[index];
   }
    
   /**
    * Gets the array of Amount Type Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Type Code values.
    */
   public final String[] getAmountTypeArray()
   {
      return _AmountType;
   }
    
   /**
    * Gets the Amount Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Amount Type Description or null.
    */
   public final String getAmountTypeDesc( int index )
   {
      return _AmountTypeDesc[index];
   }
    
   /**
    * Gets the Amount Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Amount Type Description or the specified default value.
    */
   public final String getAmountTypeDesc( int index, String defaultValue )
   {
      return _AmountTypeDesc[index] == null ? defaultValue : _AmountTypeDesc[index];
   }
    
   /**
    * Gets the array of Amount Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Amount Type Description values.
    */
   public final String[] getAmountTypeDescArray()
   {
      return _AmountTypeDesc;
   }
    
   /**
    * Gets the Gross or Net field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross or Net or null.
    */
   public final Boolean getGrossOrNet( int index )
   {
      return _GrossOrNet[index];
   }
    
   /**
    * Gets the Gross or Net field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross or Net or the specified default value.
    */
   public final boolean getGrossOrNet( int index, boolean defaultValue )
   {
      return _GrossOrNet[index] == null ? defaultValue : _GrossOrNet[index].booleanValue();
   }
    
   /**
    * Gets the array of Gross or Net fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross or Net values.
    */
   public final Boolean[] getGrossOrNetArray()
   {
      return _GrossOrNet;
   }
    
   /**
    * Gets the Order Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Order Type or null.
    */
   public final Boolean getOrderType( int index )
   {
      return _OrderType[index];
   }
    
   /**
    * Gets the Order Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Order Type or the specified default value.
    */
   public final boolean getOrderType( int index, boolean defaultValue )
   {
      return _OrderType[index] == null ? defaultValue : _OrderType[index].booleanValue();
   }
    
   /**
    * Gets the array of Order Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Order Type values.
    */
   public final Boolean[] getOrderTypeArray()
   {
      return _OrderType;
   }
    
   /**
    * Gets the Wire Order Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Wire Order Number or null.
    */
   public final String getWireOrdNum( int index )
   {
      return _WireOrdNum[index];
   }
    
   /**
    * Gets the Wire Order Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wire Order Number or the specified default value.
    */
   public final String getWireOrdNum( int index, String defaultValue )
   {
      return _WireOrdNum[index] == null ? defaultValue : _WireOrdNum[index];
   }
    
   /**
    * Gets the array of Wire Order Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Wire Order Number values.
    */
   public final String[] getWireOrdNumArray()
   {
      return _WireOrdNum;
   }
    
   /**
    * Gets the Batch User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch User or null.
    */
   public final String getBatchUser( int index )
   {
      return _BatchUser[index];
   }
    
   /**
    * Gets the Batch User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch User or the specified default value.
    */
   public final String getBatchUser( int index, String defaultValue )
   {
      return _BatchUser[index] == null ? defaultValue : _BatchUser[index];
   }
    
   /**
    * Gets the array of Batch User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch User values.
    */
   public final String[] getBatchUserArray()
   {
      return _BatchUser;
   }
    
   /**
    * Gets the Good Bad Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Good Bad Code or null.
    */
   public final String getGoodBad( int index )
   {
      return _GoodBad[index];
   }
    
   /**
    * Gets the Good Bad Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Good Bad Code or the specified default value.
    */
   public final String getGoodBad( int index, String defaultValue )
   {
      return _GoodBad[index] == null ? defaultValue : _GoodBad[index];
   }
    
   /**
    * Gets the array of Good Bad Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Good Bad Code values.
    */
   public final String[] getGoodBadArray()
   {
      return _GoodBad;
   }
    
   /**
    * Gets the Pending Trade Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pending Trade Record ID or null.
    */
   public final Integer getPendingRid( int index )
   {
      return _PendingRid[index];
   }
    
   /**
    * Gets the Pending Trade Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pending Trade Record ID or the specified default value.
    */
   public final int getPendingRid( int index, int defaultValue )
   {
      return _PendingRid[index] == null ? defaultValue : _PendingRid[index].intValue();
   }
    
   /**
    * Gets the array of Pending Trade Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pending Trade Record ID values.
    */
   public final Integer[] getPendingRidArray()
   {
      return _PendingRid;
   }
    
   /**
    * Gets the Settlement Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Currency or null.
    */
   public final String getSettleCurrency( int index )
   {
      return _SettleCurrency[index];
   }
    
   /**
    * Gets the Settlement Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Currency or the specified default value.
    */
   public final String getSettleCurrency( int index, String defaultValue )
   {
      return _SettleCurrency[index] == null ? defaultValue : _SettleCurrency[index];
   }
    
   /**
    * Gets the array of Settlement Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Currency values.
    */
   public final String[] getSettleCurrencyArray()
   {
      return _SettleCurrency;
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Number or null.
    */
   public final String getShrNum( int index )
   {
      return _ShrNum[index];
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final String getShrNum( int index, String defaultValue )
   {
      return _ShrNum[index] == null ? defaultValue : _ShrNum[index];
   }
    
   /**
    * Gets the array of Shareholder Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Number values.
    */
   public final String[] getShrNumArray()
   {
      return _ShrNum;
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getrxAccountNum( int index )
   {
      return _rxAccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getrxAccountNum( int index, String defaultValue )
   {
      return _rxAccountNum[index] == null ? defaultValue : _rxAccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getrxAccountNumArray()
   {
      return _rxAccountNum;
   }
    
   /**
    * Gets the Good Bad Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Good Bad Description or null.
    */
   public final String getGoodBadDesc( int index )
   {
      return _GoodBadDesc[index];
   }
    
   /**
    * Gets the Good Bad Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Good Bad Description or the specified default value.
    */
   public final String getGoodBadDesc( int index, String defaultValue )
   {
      return _GoodBadDesc[index] == null ? defaultValue : _GoodBadDesc[index];
   }
    
   /**
    * Gets the array of Good Bad Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Good Bad Description values.
    */
   public final String[] getGoodBadDescArray()
   {
      return _GoodBadDesc;
   }
    
   /**
    * Gets the Order Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Order Type Description or null.
    */
   public final String getOrderTypeDesc( int index )
   {
      return _OrderTypeDesc[index];
   }
    
   /**
    * Gets the Order Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Order Type Description or the specified default value.
    */
   public final String getOrderTypeDesc( int index, String defaultValue )
   {
      return _OrderTypeDesc[index] == null ? defaultValue : _OrderTypeDesc[index];
   }
    
   /**
    * Gets the array of Order Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Order Type Description values.
    */
   public final String[] getOrderTypeDescArray()
   {
      return _OrderTypeDesc;
   }
    
   /**
    * Gets the AMS Trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AMS Trade or null.
    */
   public final Boolean getAMSTrade( int index )
   {
      return _AMSTrade[index];
   }
    
   /**
    * Gets the AMS Trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Trade or the specified default value.
    */
   public final boolean getAMSTrade( int index, boolean defaultValue )
   {
      return _AMSTrade[index] == null ? defaultValue : _AMSTrade[index].booleanValue();
   }
    
   /**
    * Gets the array of AMS Trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AMS Trade values.
    */
   public final Boolean[] getAMSTradeArray()
   {
      return _AMSTrade;
   }
    
   /**
    * Gets the Trade AMSCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade AMSCode or null.
    */
   public final String getTradeAMSCode( int index )
   {
      return _TradeAMSCode[index];
   }
    
   /**
    * Gets the Trade AMSCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade AMSCode or the specified default value.
    */
   public final String getTradeAMSCode( int index, String defaultValue )
   {
      return _TradeAMSCode[index] == null ? defaultValue : _TradeAMSCode[index];
   }
    
   /**
    * Gets the array of Trade AMSCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade AMSCode values.
    */
   public final String[] getTradeAMSCodeArray()
   {
      return _TradeAMSCode;
   }
    
   /**
    * Gets the Transaction Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Fee or null.
    */
   public final String getTxnFee( int index )
   {
      return _TxnFee[index];
   }
    
   /**
    * Gets the Transaction Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Fee or the specified default value.
    */
   public final String getTxnFee( int index, String defaultValue )
   {
      return _TxnFee[index] == null ? defaultValue : _TxnFee[index];
   }
    
   /**
    * Gets the array of Transaction Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Fee values.
    */
   public final String[] getTxnFeeArray()
   {
      return _TxnFee;
   }
    
   /**
    * Gets the Acq Fee Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acq Fee Option or null.
    */
   public final String getAcqFeeOption( int index )
   {
      return _AcqFeeOption[index];
   }
    
   /**
    * Gets the Acq Fee Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acq Fee Option or the specified default value.
    */
   public final String getAcqFeeOption( int index, String defaultValue )
   {
      return _AcqFeeOption[index] == null ? defaultValue : _AcqFeeOption[index];
   }
    
   /**
    * Gets the array of Acq Fee Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acq Fee Option values.
    */
   public final String[] getAcqFeeOptionArray()
   {
      return _AcqFeeOption;
   }
    
   /**
    * Gets the Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee or null.
    */
   public final String getFee( int index )
   {
      return _Fee[index];
   }
    
   /**
    * Gets the Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee or the specified default value.
    */
   public final String getFee( int index, String defaultValue )
   {
      return _Fee[index] == null ? defaultValue : _Fee[index];
   }
    
   /**
    * Gets the array of Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee values.
    */
   public final String[] getFeeArray()
   {
      return _Fee;
   }
    
   /**
    * Gets the FlatPercent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FlatPercent or null.
    */
   public final Boolean getFlatPercent( int index )
   {
      return _FlatPercent[index];
   }
    
   /**
    * Gets the FlatPercent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FlatPercent or the specified default value.
    */
   public final boolean getFlatPercent( int index, boolean defaultValue )
   {
      return _FlatPercent[index] == null ? defaultValue : _FlatPercent[index].booleanValue();
   }
    
   /**
    * Gets the array of FlatPercent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FlatPercent values.
    */
   public final Boolean[] getFlatPercentArray()
   {
      return _FlatPercent;
   }
    
   /**
    * Gets the Fee Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Currency or null.
    */
   public final String getFeeCurrency( int index )
   {
      return _FeeCurrency[index];
   }
    
   /**
    * Gets the Fee Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Currency or the specified default value.
    */
   public final String getFeeCurrency( int index, String defaultValue )
   {
      return _FeeCurrency[index] == null ? defaultValue : _FeeCurrency[index];
   }
    
   /**
    * Gets the array of Fee Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Currency values.
    */
   public final String[] getFeeCurrencyArray()
   {
      return _FeeCurrency;
   }
    
   /**
    * Gets the BEL Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BEL Fee or null.
    */
   public final Boolean getBELFee( int index )
   {
      return _BELFee[index];
   }
    
   /**
    * Gets the BEL Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BEL Fee or the specified default value.
    */
   public final boolean getBELFee( int index, boolean defaultValue )
   {
      return _BELFee[index] == null ? defaultValue : _BELFee[index].booleanValue();
   }
    
   /**
    * Gets the array of BEL Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BEL Fee values.
    */
   public final Boolean[] getBELFeeArray()
   {
      return _BELFee;
   }
    
   /**
    * Gets the Admin Fee Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Admin Fee Amount or null.
    */
   public final String getAdminFeeAmt( int index )
   {
      return _AdminFeeAmt[index];
   }
    
   /**
    * Gets the Admin Fee Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Admin Fee Amount or the specified default value.
    */
   public final String getAdminFeeAmt( int index, String defaultValue )
   {
      return _AdminFeeAmt[index] == null ? defaultValue : _AdminFeeAmt[index];
   }
    
   /**
    * Gets the array of Admin Fee Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Admin Fee Amount values.
    */
   public final String[] getAdminFeeAmtArray()
   {
      return _AdminFeeAmt;
   }
    
   /**
    * Gets the Is the fee user entered? field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is the fee user entered? or null.
    */
   public final Boolean getUseEnteredFee( int index )
   {
      return _UseEnteredFee[index];
   }
    
   /**
    * Gets the Is the fee user entered? field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is the fee user entered? or the specified default value.
    */
   public final boolean getUseEnteredFee( int index, boolean defaultValue )
   {
      return _UseEnteredFee[index] == null ? defaultValue : _UseEnteredFee[index].booleanValue();
   }
    
   /**
    * Gets the array of Is the fee user entered? fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is the fee user entered? values.
    */
   public final Boolean[] getUseEnteredFeeArray()
   {
      return _UseEnteredFee;
   }
    
   /**
    * Gets the Exchange In Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange In Fee or null.
    */
   public final String getExchInFee( int index )
   {
      return _ExchInFee[index];
   }
    
   /**
    * Gets the Exchange In Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange In Fee or the specified default value.
    */
   public final String getExchInFee( int index, String defaultValue )
   {
      return _ExchInFee[index] == null ? defaultValue : _ExchInFee[index];
   }
    
   /**
    * Gets the array of Exchange In Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange In Fee values.
    */
   public final String[] getExchInFeeArray()
   {
      return _ExchInFee;
   }
    
   /**
    * Gets the Exchange In Fee Flat/Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange In Fee Flat/Percent or null.
    */
   public final Boolean getExchInFlatPercent( int index )
   {
      return _ExchInFlatPercent[index];
   }
    
   /**
    * Gets the Exchange In Fee Flat/Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange In Fee Flat/Percent or the specified default value.
    */
   public final boolean getExchInFlatPercent( int index, boolean defaultValue )
   {
      return _ExchInFlatPercent[index] == null ? defaultValue : _ExchInFlatPercent[index].booleanValue();
   }
    
   /**
    * Gets the array of Exchange In Fee Flat/Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange In Fee Flat/Percent values.
    */
   public final Boolean[] getExchInFlatPercentArray()
   {
      return _ExchInFlatPercent;
   }
    
   /**
    * Gets the Exchange Out Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange Out Fee or null.
    */
   public final String getExchOutFee( int index )
   {
      return _ExchOutFee[index];
   }
    
   /**
    * Gets the Exchange Out Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Out Fee or the specified default value.
    */
   public final String getExchOutFee( int index, String defaultValue )
   {
      return _ExchOutFee[index] == null ? defaultValue : _ExchOutFee[index];
   }
    
   /**
    * Gets the array of Exchange Out Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange Out Fee values.
    */
   public final String[] getExchOutFeeArray()
   {
      return _ExchOutFee;
   }
    
   /**
    * Gets the Exchange Out Fee Flat/Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange Out Fee Flat/Percent or null.
    */
   public final Boolean getExchOutFlatPrcnt( int index )
   {
      return _ExchOutFlatPrcnt[index];
   }
    
   /**
    * Gets the Exchange Out Fee Flat/Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Out Fee Flat/Percent or the specified default value.
    */
   public final boolean getExchOutFlatPrcnt( int index, boolean defaultValue )
   {
      return _ExchOutFlatPrcnt[index] == null ? defaultValue : _ExchOutFlatPrcnt[index].booleanValue();
   }
    
   /**
    * Gets the array of Exchange Out Fee Flat/Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange Out Fee Flat/Percent values.
    */
   public final Boolean[] getExchOutFlatPrcntArray()
   {
      return _ExchOutFlatPrcnt;
   }
    
   /**
    * Gets the ChargeERSTTRFee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ChargeERSTTRFee or null.
    */
   public final Boolean getChargeERSTTRFee( int index )
   {
      return _ChargeERSTTRFee[index];
   }
    
   /**
    * Gets the ChargeERSTTRFee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ChargeERSTTRFee or the specified default value.
    */
   public final boolean getChargeERSTTRFee( int index, boolean defaultValue )
   {
      return _ChargeERSTTRFee[index] == null ? defaultValue : _ChargeERSTTRFee[index].booleanValue();
   }
    
   /**
    * Gets the array of ChargeERSTTRFee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ChargeERSTTRFee values.
    */
   public final Boolean[] getChargeERSTTRFeeArray()
   {
      return _ChargeERSTTRFee;
   }
    
   /**
    * Gets the ChargeWDFee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ChargeWDFee or null.
    */
   public final Boolean getChargeWDFee( int index )
   {
      return _ChargeWDFee[index];
   }
    
   /**
    * Gets the ChargeWDFee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ChargeWDFee or the specified default value.
    */
   public final boolean getChargeWDFee( int index, boolean defaultValue )
   {
      return _ChargeWDFee[index] == null ? defaultValue : _ChargeWDFee[index].booleanValue();
   }
    
   /**
    * Gets the array of ChargeWDFee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ChargeWDFee values.
    */
   public final Boolean[] getChargeWDFeeArray()
   {
      return _ChargeWDFee;
   }
    
   /**
    * Gets the Fee To field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee To or null.
    */
   public final String getIFeeTo( int index )
   {
      return _IFeeTo[index];
   }
    
   /**
    * Gets the Fee To field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee To or the specified default value.
    */
   public final String getIFeeTo( int index, String defaultValue )
   {
      return _IFeeTo[index] == null ? defaultValue : _IFeeTo[index];
   }
    
   /**
    * Gets the array of Fee To fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee To values.
    */
   public final String[] getIFeeToArray()
   {
      return _IFeeTo;
   }
    
   /**
    * Gets the charge additional fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the charge additional fee or null.
    */
   public final String getChargeADLFee( int index )
   {
      return _ChargeADLFee[index];
   }
    
   /**
    * Gets the charge additional fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the charge additional fee or the specified default value.
    */
   public final String getChargeADLFee( int index, String defaultValue )
   {
      return _ChargeADLFee[index] == null ? defaultValue : _ChargeADLFee[index];
   }
    
   /**
    * Gets the array of charge additional fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of charge additional fee values.
    */
   public final String[] getChargeADLFeeArray()
   {
      return _ChargeADLFee;
   }
    
   /**
    * Gets the Baycom number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Baycom number or null.
    */
   public final String getBaycom( int index )
   {
      return _Baycom[index];
   }
    
   /**
    * Gets the Baycom number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom number or the specified default value.
    */
   public final String getBaycom( int index, String defaultValue )
   {
      return _Baycom[index] == null ? defaultValue : _Baycom[index];
   }
    
   /**
    * Gets the array of Baycom number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Baycom number values.
    */
   public final String[] getBaycomArray()
   {
      return _Baycom;
   }
    
   /**
    * Gets the Baycom to number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Baycom to number or null.
    */
   public final String getBaycomTo( int index )
   {
      return _BaycomTo[index];
   }
    
   /**
    * Gets the Baycom to number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Baycom to number or the specified default value.
    */
   public final String getBaycomTo( int index, String defaultValue )
   {
      return _BaycomTo[index] == null ? defaultValue : _BaycomTo[index];
   }
    
   /**
    * Gets the array of Baycom to number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Baycom to number values.
    */
   public final String[] getBaycomToArray()
   {
      return _BaycomTo;
   }
    
   /**
    * Gets the Fund ISIN field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund ISIN or null.
    */
   public final String getFundISIN( int index )
   {
      return _FundISIN[index];
   }
    
   /**
    * Gets the Fund ISIN field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund ISIN or the specified default value.
    */
   public final String getFundISIN( int index, String defaultValue )
   {
      return _FundISIN[index] == null ? defaultValue : _FundISIN[index];
   }
    
   /**
    * Gets the array of Fund ISIN fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund ISIN values.
    */
   public final String[] getFundISINArray()
   {
      return _FundISIN;
   }
    
   /**
    * Gets the Fund To ISIN field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund To ISIN or null.
    */
   public final String getFundToISIN( int index )
   {
      return _FundToISIN[index];
   }
    
   /**
    * Gets the Fund To ISIN field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund To ISIN or the specified default value.
    */
   public final String getFundToISIN( int index, String defaultValue )
   {
      return _FundToISIN[index] == null ? defaultValue : _FundToISIN[index];
   }
    
   /**
    * Gets the array of Fund To ISIN fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund To ISIN values.
    */
   public final String[] getFundToISINArray()
   {
      return _FundToISIN;
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Currency or null.
    */
   public final String getFundCurrency( int index )
   {
      return _FundCurrency[index];
   }
    
   /**
    * Gets the Fund Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Currency or the specified default value.
    */
   public final String getFundCurrency( int index, String defaultValue )
   {
      return _FundCurrency[index] == null ? defaultValue : _FundCurrency[index];
   }
    
   /**
    * Gets the array of Fund Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Currency values.
    */
   public final String[] getFundCurrencyArray()
   {
      return _FundCurrency;
   }
    
   /**
    * Gets the System level latest NAV field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the System level latest NAV or null.
    */
   public final String getSysNAV( int index )
   {
      return _SysNAV[index];
   }
    
   /**
    * Gets the System level latest NAV field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the System level latest NAV or the specified default value.
    */
   public final String getSysNAV( int index, String defaultValue )
   {
      return _SysNAV[index] == null ? defaultValue : _SysNAV[index];
   }
    
   /**
    * Gets the array of System level latest NAV fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of System level latest NAV values.
    */
   public final String[] getSysNAVArray()
   {
      return _SysNAV;
   }
    
   /**
    * Gets the System level latest Exchange Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the System level latest Exchange Rate or null.
    */
   public final String getSysExchRate( int index )
   {
      return _SysExchRate[index];
   }
    
   /**
    * Gets the System level latest Exchange Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the System level latest Exchange Rate or the specified default value.
    */
   public final String getSysExchRate( int index, String defaultValue )
   {
      return _SysExchRate[index] == null ? defaultValue : _SysExchRate[index];
   }
    
   /**
    * Gets the array of System level latest Exchange Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of System level latest Exchange Rate values.
    */
   public final String[] getSysExchRateArray()
   {
      return _SysExchRate;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Code or null.
    */
   public final String getBrokerCode( int index )
   {
      return _BrokerCode[index];
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Code or the specified default value.
    */
   public final String getBrokerCode( int index, String defaultValue )
   {
      return _BrokerCode[index] == null ? defaultValue : _BrokerCode[index];
   }
    
   /**
    * Gets the array of Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Code values.
    */
   public final String[] getBrokerCodeArray()
   {
      return _BrokerCode;
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Code or null.
    */
   public final String getBranchCode( int index )
   {
      return _BranchCode[index];
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Code or the specified default value.
    */
   public final String getBranchCode( int index, String defaultValue )
   {
      return _BranchCode[index] == null ? defaultValue : _BranchCode[index];
   }
    
   /**
    * Gets the array of Branch Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Code values.
    */
   public final String[] getBranchCodeArray()
   {
      return _BranchCode;
   }
    
   /**
    * Gets the SlsRep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SlsRep Code or null.
    */
   public final String getSlsRepCode( int index )
   {
      return _SlsRepCode[index];
   }
    
   /**
    * Gets the SlsRep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SlsRep Code or the specified default value.
    */
   public final String getSlsRepCode( int index, String defaultValue )
   {
      return _SlsRepCode[index] == null ? defaultValue : _SlsRepCode[index];
   }
    
   /**
    * Gets the array of SlsRep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SlsRep Code values.
    */
   public final String[] getSlsRepCodeArray()
   {
      return _SlsRepCode;
   }
    
   /**
    * Gets the Broker Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Name or null.
    */
   public final String getBrokerName( int index )
   {
      return _BrokerName[index];
   }
    
   /**
    * Gets the Broker Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Name or the specified default value.
    */
   public final String getBrokerName( int index, String defaultValue )
   {
      return _BrokerName[index] == null ? defaultValue : _BrokerName[index];
   }
    
   /**
    * Gets the array of Broker Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Name values.
    */
   public final String[] getBrokerNameArray()
   {
      return _BrokerName;
   }
    
   /**
    * Gets the Branch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Name or null.
    */
   public final String getBranchName( int index )
   {
      return _BranchName[index];
   }
    
   /**
    * Gets the Branch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Name or the specified default value.
    */
   public final String getBranchName( int index, String defaultValue )
   {
      return _BranchName[index] == null ? defaultValue : _BranchName[index];
   }
    
   /**
    * Gets the array of Branch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Name values.
    */
   public final String[] getBranchNameArray()
   {
      return _BranchName;
   }
    
   /**
    * Gets the Sls Rep Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sls Rep Name or null.
    */
   public final String getSlsRepName( int index )
   {
      return _SlsRepName[index];
   }
    
   /**
    * Gets the Sls Rep Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sls Rep Name or the specified default value.
    */
   public final String getSlsRepName( int index, String defaultValue )
   {
      return _SlsRepName[index] == null ? defaultValue : _SlsRepName[index];
   }
    
   /**
    * Gets the array of Sls Rep Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sls Rep Name values.
    */
   public final String[] getSlsRepNameArray()
   {
      return _SlsRepName;
   }
    
   /**
    * Gets the To Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the To Broker Code or null.
    */
   public final String getToBrokerCode( int index )
   {
      return _ToBrokerCode[index];
   }
    
   /**
    * Gets the To Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Broker Code or the specified default value.
    */
   public final String getToBrokerCode( int index, String defaultValue )
   {
      return _ToBrokerCode[index] == null ? defaultValue : _ToBrokerCode[index];
   }
    
   /**
    * Gets the array of To Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of To Broker Code values.
    */
   public final String[] getToBrokerCodeArray()
   {
      return _ToBrokerCode;
   }
    
   /**
    * Gets the To Sls Rep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the To Sls Rep Code or null.
    */
   public final String getToSlsRepCode( int index )
   {
      return _ToSlsRepCode[index];
   }
    
   /**
    * Gets the To Sls Rep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Sls Rep Code or the specified default value.
    */
   public final String getToSlsRepCode( int index, String defaultValue )
   {
      return _ToSlsRepCode[index] == null ? defaultValue : _ToSlsRepCode[index];
   }
    
   /**
    * Gets the array of To Sls Rep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of To Sls Rep Code values.
    */
   public final String[] getToSlsRepCodeArray()
   {
      return _ToSlsRepCode;
   }
    
   /**
    * Gets the Remarks line1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line1 or null.
    */
   public final String getRemarks1( int index )
   {
      return _Remarks1[index];
   }
    
   /**
    * Gets the Remarks line1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line1 or the specified default value.
    */
   public final String getRemarks1( int index, String defaultValue )
   {
      return _Remarks1[index] == null ? defaultValue : _Remarks1[index];
   }
    
   /**
    * Gets the array of Remarks line1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line1 values.
    */
   public final String[] getRemarks1Array()
   {
      return _Remarks1;
   }
    
   /**
    * Gets the Remarks line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 2 or null.
    */
   public final String getRemarks2( int index )
   {
      return _Remarks2[index];
   }
    
   /**
    * Gets the Remarks line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 2 or the specified default value.
    */
   public final String getRemarks2( int index, String defaultValue )
   {
      return _Remarks2[index] == null ? defaultValue : _Remarks2[index];
   }
    
   /**
    * Gets the array of Remarks line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 2 values.
    */
   public final String[] getRemarks2Array()
   {
      return _Remarks2;
   }
    
   /**
    * Gets the Remarks line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks line 3 or null.
    */
   public final String getRemarks3( int index )
   {
      return _Remarks3[index];
   }
    
   /**
    * Gets the Remarks line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks line 3 or the specified default value.
    */
   public final String getRemarks3( int index, String defaultValue )
   {
      return _Remarks3[index] == null ? defaultValue : _Remarks3[index];
   }
    
   /**
    * Gets the array of Remarks line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks line 3 values.
    */
   public final String[] getRemarks3Array()
   {
      return _Remarks3;
   }
    
   /**
    * Gets the Is it an initial purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is it an initial purchase or null.
    */
   public final Boolean getInitPurch( int index )
   {
      return _InitPurch[index];
   }
    
   /**
    * Gets the Is it an initial purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is it an initial purchase or the specified default value.
    */
   public final boolean getInitPurch( int index, boolean defaultValue )
   {
      return _InitPurch[index] == null ? defaultValue : _InitPurch[index].booleanValue();
   }
    
   /**
    * Gets the array of Is it an initial purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is it an initial purchase values.
    */
   public final Boolean[] getInitPurchArray()
   {
      return _InitPurch;
   }
    
   /**
    * Gets the Is the trade verified field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is the trade verified or null.
    */
   public final Boolean getVerified( int index )
   {
      return _Verified[index];
   }
    
   /**
    * Gets the Is the trade verified field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is the trade verified or the specified default value.
    */
   public final boolean getVerified( int index, boolean defaultValue )
   {
      return _Verified[index] == null ? defaultValue : _Verified[index].booleanValue();
   }
    
   /**
    * Gets the array of Is the trade verified fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is the trade verified values.
    */
   public final Boolean[] getVerifiedArray()
   {
      return _Verified;
   }
    
   /**
    * Gets the Account holder first name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account holder first name or null.
    */
   public final String getFirstName( int index )
   {
      return _FirstName[index];
   }
    
   /**
    * Gets the Account holder first name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account holder first name or the specified default value.
    */
   public final String getFirstName( int index, String defaultValue )
   {
      return _FirstName[index] == null ? defaultValue : _FirstName[index];
   }
    
   /**
    * Gets the array of Account holder first name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account holder first name values.
    */
   public final String[] getFirstNameArray()
   {
      return _FirstName;
   }
    
   /**
    * Gets the Account holder last name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account holder last name or null.
    */
   public final String getLastName( int index )
   {
      return _LastName[index];
   }
    
   /**
    * Gets the Account holder last name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account holder last name or the specified default value.
    */
   public final String getLastName( int index, String defaultValue )
   {
      return _LastName[index] == null ? defaultValue : _LastName[index];
   }
    
   /**
    * Gets the array of Account holder last name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account holder last name values.
    */
   public final String[] getLastNameArray()
   {
      return _LastName;
   }
    
   /**
    * Gets the Network ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Network ID or null.
    */
   public final String getNetworkId( int index )
   {
      return _NetworkId[index];
   }
    
   /**
    * Gets the Network ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Network ID or the specified default value.
    */
   public final String getNetworkId( int index, String defaultValue )
   {
      return _NetworkId[index] == null ? defaultValue : _NetworkId[index];
   }
    
   /**
    * Gets the array of Network ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Network ID values.
    */
   public final String[] getNetworkIdArray()
   {
      return _NetworkId;
   }
    
   /**
    * Gets the External Transaction Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the External Transaction Number or null.
    */
   public final String getExtTransNum( int index )
   {
      return _ExtTransNum[index];
   }
    
   /**
    * Gets the External Transaction Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the External Transaction Number or the specified default value.
    */
   public final String getExtTransNum( int index, String defaultValue )
   {
      return _ExtTransNum[index] == null ? defaultValue : _ExtTransNum[index];
   }
    
   /**
    * Gets the array of External Transaction Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of External Transaction Number values.
    */
   public final String[] getExtTransNumArray()
   {
      return _ExtTransNum;
   }
    
   /**
    * Gets the Sender's Reference Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sender's Reference Number or null.
    */
   public final String getSendRefNum( int index )
   {
      return _SendRefNum[index];
   }
    
   /**
    * Gets the Sender's Reference Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sender's Reference Number or the specified default value.
    */
   public final String getSendRefNum( int index, String defaultValue )
   {
      return _SendRefNum[index] == null ? defaultValue : _SendRefNum[index];
   }
    
   /**
    * Gets the array of Sender's Reference Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sender's Reference Number values.
    */
   public final String[] getSendRefNumArray()
   {
      return _SendRefNum;
   }
    
   /**
    * Gets the Discount Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Discount Rate or null.
    */
   public final String getDiscountRate( int index )
   {
      return _DiscountRate[index];
   }
    
   /**
    * Gets the Discount Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Discount Rate or the specified default value.
    */
   public final String getDiscountRate( int index, String defaultValue )
   {
      return _DiscountRate[index] == null ? defaultValue : _DiscountRate[index];
   }
    
   /**
    * Gets the array of Discount Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Discount Rate values.
    */
   public final String[] getDiscountRateArray()
   {
      return _DiscountRate;
   }
    
   /**
    * Gets the Transaction Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Id or null.
    */
   public final String getTransId( int index )
   {
      return _TransId[index];
   }
    
   /**
    * Gets the Transaction Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Id or the specified default value.
    */
   public final String getTransId( int index, String defaultValue )
   {
      return _TransId[index] == null ? defaultValue : _TransId[index];
   }
    
   /**
    * Gets the array of Transaction Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Id values.
    */
   public final String[] getTransIdArray()
   {
      return _TransId;
   }
    
   /**
    * Gets the Exchange Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange Rate or null.
    */
   public final String getExchRate( int index )
   {
      return _ExchRate[index];
   }
    
   /**
    * Gets the Exchange Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Rate or the specified default value.
    */
   public final String getExchRate( int index, String defaultValue )
   {
      return _ExchRate[index] == null ? defaultValue : _ExchRate[index];
   }
    
   /**
    * Gets the array of Exchange Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange Rate values.
    */
   public final String[] getExchRateArray()
   {
      return _ExchRate;
   }
    
   /**
    * Gets the Split Commission % for broker field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission % for broker or null.
    */
   public final String getBrokerCommPrcnt( int index )
   {
      return _BrokerCommPrcnt[index];
   }
    
   /**
    * Gets the Split Commission % for broker field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission % for broker or the specified default value.
    */
   public final String getBrokerCommPrcnt( int index, String defaultValue )
   {
      return _BrokerCommPrcnt[index] == null ? defaultValue : _BrokerCommPrcnt[index];
   }
    
   /**
    * Gets the array of Split Commission % for broker fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission % for broker values.
    */
   public final String[] getBrokerCommPrcntArray()
   {
      return _BrokerCommPrcnt;
   }
    
   /**
    * Gets the Split Commission Amt for broker field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission Amt for broker or null.
    */
   public final String getBrokerCommRate( int index )
   {
      return _BrokerCommRate[index];
   }
    
   /**
    * Gets the Split Commission Amt for broker field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission Amt for broker or the specified default value.
    */
   public final String getBrokerCommRate( int index, String defaultValue )
   {
      return _BrokerCommRate[index] == null ? defaultValue : _BrokerCommRate[index];
   }
    
   /**
    * Gets the array of Split Commission Amt for broker fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission Amt for broker values.
    */
   public final String[] getBrokerCommRateArray()
   {
      return _BrokerCommRate;
   }
    
   /**
    * Gets the Split Commission % for branch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission % for branch or null.
    */
   public final String getBranchCommPrcnt( int index )
   {
      return _BranchCommPrcnt[index];
   }
    
   /**
    * Gets the Split Commission % for branch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission % for branch or the specified default value.
    */
   public final String getBranchCommPrcnt( int index, String defaultValue )
   {
      return _BranchCommPrcnt[index] == null ? defaultValue : _BranchCommPrcnt[index];
   }
    
   /**
    * Gets the array of Split Commission % for branch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission % for branch values.
    */
   public final String[] getBranchCommPrcntArray()
   {
      return _BranchCommPrcnt;
   }
    
   /**
    * Gets the Split Commission Amt for branch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission Amt for branch or null.
    */
   public final String getBranchCommRate( int index )
   {
      return _BranchCommRate[index];
   }
    
   /**
    * Gets the Split Commission Amt for branch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission Amt for branch or the specified default value.
    */
   public final String getBranchCommRate( int index, String defaultValue )
   {
      return _BranchCommRate[index] == null ? defaultValue : _BranchCommRate[index];
   }
    
   /**
    * Gets the array of Split Commission Amt for branch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission Amt for branch values.
    */
   public final String[] getBranchCommRateArray()
   {
      return _BranchCommRate;
   }
    
   /**
    * Gets the Split Commission % for sls rep field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission % for sls rep or null.
    */
   public final String getSlsRepCommPrcnt( int index )
   {
      return _SlsRepCommPrcnt[index];
   }
    
   /**
    * Gets the Split Commission % for sls rep field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission % for sls rep or the specified default value.
    */
   public final String getSlsRepCommPrcnt( int index, String defaultValue )
   {
      return _SlsRepCommPrcnt[index] == null ? defaultValue : _SlsRepCommPrcnt[index];
   }
    
   /**
    * Gets the array of Split Commission % for sls rep fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission % for sls rep values.
    */
   public final String[] getSlsRepCommPrcntArray()
   {
      return _SlsRepCommPrcnt;
   }
    
   /**
    * Gets the Split Commission Amt for sls rep field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission Amt for sls rep or null.
    */
   public final String getSlsRepCommRate( int index )
   {
      return _SlsRepCommRate[index];
   }
    
   /**
    * Gets the Split Commission Amt for sls rep field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission Amt for sls rep or the specified default value.
    */
   public final String getSlsRepCommRate( int index, String defaultValue )
   {
      return _SlsRepCommRate[index] == null ? defaultValue : _SlsRepCommRate[index];
   }
    
   /**
    * Gets the array of Split Commission Amt for sls rep fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission Amt for sls rep values.
    */
   public final String[] getSlsRepCommRateArray()
   {
      return _SlsRepCommRate;
   }
    
   /**
    * Gets the Split Commission % for mgmt company field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission % for mgmt company or null.
    */
   public final String getMgmtCompCommPrcnt( int index )
   {
      return _MgmtCompCommPrcnt[index];
   }
    
   /**
    * Gets the Split Commission % for mgmt company field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission % for mgmt company or the specified default value.
    */
   public final String getMgmtCompCommPrcnt( int index, String defaultValue )
   {
      return _MgmtCompCommPrcnt[index] == null ? defaultValue : _MgmtCompCommPrcnt[index];
   }
    
   /**
    * Gets the array of Split Commission % for mgmt company fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission % for mgmt company values.
    */
   public final String[] getMgmtCompCommPrcntArray()
   {
      return _MgmtCompCommPrcnt;
   }
    
   /**
    * Gets the Split Commission Amt for mgmt company field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Split Commission Amt for mgmt company or null.
    */
   public final String getMgmtCompCommRate( int index )
   {
      return _MgmtCompCommRate[index];
   }
    
   /**
    * Gets the Split Commission Amt for mgmt company field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission Amt for mgmt company or the specified default value.
    */
   public final String getMgmtCompCommRate( int index, String defaultValue )
   {
      return _MgmtCompCommRate[index] == null ? defaultValue : _MgmtCompCommRate[index];
   }
    
   /**
    * Gets the array of Split Commission Amt for mgmt company fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Split Commission Amt for mgmt company values.
    */
   public final String[] getMgmtCompCommRateArray()
   {
      return _MgmtCompCommRate;
   }
    
   /**
    * Gets the Comm Prcnt total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comm Prcnt total or null.
    */
   public final String getTotalCommPrcnt( int index )
   {
      return _TotalCommPrcnt[index];
   }
    
   /**
    * Gets the Comm Prcnt total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comm Prcnt total or the specified default value.
    */
   public final String getTotalCommPrcnt( int index, String defaultValue )
   {
      return _TotalCommPrcnt[index] == null ? defaultValue : _TotalCommPrcnt[index];
   }
    
   /**
    * Gets the array of Comm Prcnt total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comm Prcnt total values.
    */
   public final String[] getTotalCommPrcntArray()
   {
      return _TotalCommPrcnt;
   }
    
   /**
    * Gets the Comm Amt total field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comm Amt total or null.
    */
   public final String getTotalCommRate( int index )
   {
      return _TotalCommRate[index];
   }
    
   /**
    * Gets the Comm Amt total field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comm Amt total or the specified default value.
    */
   public final String getTotalCommRate( int index, String defaultValue )
   {
      return _TotalCommRate[index] == null ? defaultValue : _TotalCommRate[index];
   }
    
   /**
    * Gets the array of Comm Amt total fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comm Amt total values.
    */
   public final String[] getTotalCommRateArray()
   {
      return _TotalCommRate;
   }
    
   /**
    * Gets the Bank ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank ID or null.
    */
   public final String getBankId( int index )
   {
      return _BankId[index];
   }
    
   /**
    * Gets the Bank ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID or the specified default value.
    */
   public final String getBankId( int index, String defaultValue )
   {
      return _BankId[index] == null ? defaultValue : _BankId[index];
   }
    
   /**
    * Gets the array of Bank ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank ID values.
    */
   public final String[] getBankIdArray()
   {
      return _BankId;
   }
    
   /**
    * Gets the Bank Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Type or null.
    */
   public final String getBankType( int index )
   {
      return _BankType[index];
   }
    
   /**
    * Gets the Bank Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Type or the specified default value.
    */
   public final String getBankType( int index, String defaultValue )
   {
      return _BankType[index] == null ? defaultValue : _BankType[index];
   }
    
   /**
    * Gets the array of Bank Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Type values.
    */
   public final String[] getBankTypeArray()
   {
      return _BankType;
   }
    
   /**
    * Gets the Bank ID number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank ID number or null.
    */
   public final String getBankIdNum( int index )
   {
      return _BankIdNum[index];
   }
    
   /**
    * Gets the Bank ID number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID number or the specified default value.
    */
   public final String getBankIdNum( int index, String defaultValue )
   {
      return _BankIdNum[index] == null ? defaultValue : _BankIdNum[index];
   }
    
   /**
    * Gets the array of Bank ID number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank ID number values.
    */
   public final String[] getBankIdNumArray()
   {
      return _BankIdNum;
   }
    
   /**
    * Gets the Bank Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Country or null.
    */
   public final String getBankCntry( int index )
   {
      return _BankCntry[index];
   }
    
   /**
    * Gets the Bank Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Country or the specified default value.
    */
   public final String getBankCntry( int index, String defaultValue )
   {
      return _BankCntry[index] == null ? defaultValue : _BankCntry[index];
   }
    
   /**
    * Gets the array of Bank Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Country values.
    */
   public final String[] getBankCntryArray()
   {
      return _BankCntry;
   }
    
   /**
    * Gets the Bank Pstl field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Pstl or null.
    */
   public final String getBankPstl( int index )
   {
      return _BankPstl[index];
   }
    
   /**
    * Gets the Bank Pstl field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Pstl or the specified default value.
    */
   public final String getBankPstl( int index, String defaultValue )
   {
      return _BankPstl[index] == null ? defaultValue : _BankPstl[index];
   }
    
   /**
    * Gets the array of Bank Pstl fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Pstl values.
    */
   public final String[] getBankPstlArray()
   {
      return _BankPstl;
   }
    
   /**
    * Gets the Bank Address line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 1 or null.
    */
   public final String getBankAddr1( int index )
   {
      return _BankAddr1[index];
   }
    
   /**
    * Gets the Bank Address line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 1 or the specified default value.
    */
   public final String getBankAddr1( int index, String defaultValue )
   {
      return _BankAddr1[index] == null ? defaultValue : _BankAddr1[index];
   }
    
   /**
    * Gets the array of Bank Address line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 1 values.
    */
   public final String[] getBankAddr1Array()
   {
      return _BankAddr1;
   }
    
   /**
    * Gets the Bank Address line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 2 or null.
    */
   public final String getBankAddr2( int index )
   {
      return _BankAddr2[index];
   }
    
   /**
    * Gets the Bank Address line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 2 or the specified default value.
    */
   public final String getBankAddr2( int index, String defaultValue )
   {
      return _BankAddr2[index] == null ? defaultValue : _BankAddr2[index];
   }
    
   /**
    * Gets the array of Bank Address line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 2 values.
    */
   public final String[] getBankAddr2Array()
   {
      return _BankAddr2;
   }
    
   /**
    * Gets the Bank Address line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 3 or null.
    */
   public final String getBankAddr3( int index )
   {
      return _BankAddr3[index];
   }
    
   /**
    * Gets the Bank Address line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 3 or the specified default value.
    */
   public final String getBankAddr3( int index, String defaultValue )
   {
      return _BankAddr3[index] == null ? defaultValue : _BankAddr3[index];
   }
    
   /**
    * Gets the array of Bank Address line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 3 values.
    */
   public final String[] getBankAddr3Array()
   {
      return _BankAddr3;
   }
    
   /**
    * Gets the Bank Address line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 4 or null.
    */
   public final String getBankAddr4( int index )
   {
      return _BankAddr4[index];
   }
    
   /**
    * Gets the Bank Address line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 4 or the specified default value.
    */
   public final String getBankAddr4( int index, String defaultValue )
   {
      return _BankAddr4[index] == null ? defaultValue : _BankAddr4[index];
   }
    
   /**
    * Gets the array of Bank Address line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 4 values.
    */
   public final String[] getBankAddr4Array()
   {
      return _BankAddr4;
   }
    
   /**
    * Gets the Bank Address line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address line 5 or null.
    */
   public final String getBankAddr5( int index )
   {
      return _BankAddr5[index];
   }
    
   /**
    * Gets the Bank Address line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address line 5 or the specified default value.
    */
   public final String getBankAddr5( int index, String defaultValue )
   {
      return _BankAddr5[index] == null ? defaultValue : _BankAddr5[index];
   }
    
   /**
    * Gets the array of Bank Address line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address line 5 values.
    */
   public final String[] getBankAddr5Array()
   {
      return _BankAddr5;
   }
    
   /**
    * Gets the Institution Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Institution Name or null.
    */
   public final String getInstName( int index )
   {
      return _InstName[index];
   }
    
   /**
    * Gets the Institution Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Institution Name or the specified default value.
    */
   public final String getInstName( int index, String defaultValue )
   {
      return _InstName[index] == null ? defaultValue : _InstName[index];
   }
    
   /**
    * Gets the array of Institution Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Institution Name values.
    */
   public final String[] getInstNameArray()
   {
      return _InstName;
   }
    
   /**
    * Gets the Bank Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Number or null.
    */
   public final String getBankAcctNum( int index )
   {
      return _BankAcctNum[index];
   }
    
   /**
    * Gets the Bank Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Number or the specified default value.
    */
   public final String getBankAcctNum( int index, String defaultValue )
   {
      return _BankAcctNum[index] == null ? defaultValue : _BankAcctNum[index];
   }
    
   /**
    * Gets the array of Bank Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Number values.
    */
   public final String[] getBankAcctNumArray()
   {
      return _BankAcctNum;
   }
    
   /**
    * Gets the Bank Account Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Name or null.
    */
   public final String getBankAcctName( int index )
   {
      return _BankAcctName[index];
   }
    
   /**
    * Gets the Bank Account Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Name or the specified default value.
    */
   public final String getBankAcctName( int index, String defaultValue )
   {
      return _BankAcctName[index] == null ? defaultValue : _BankAcctName[index];
   }
    
   /**
    * Gets the array of Bank Account Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Name values.
    */
   public final String[] getBankAcctNameArray()
   {
      return _BankAcctName;
   }
    
   /**
    * Gets the Correspondent Bank Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Id or null.
    */
   public final String getCorrespBankId( int index )
   {
      return _CorrespBankId[index];
   }
    
   /**
    * Gets the Correspondent Bank Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Id or the specified default value.
    */
   public final String getCorrespBankId( int index, String defaultValue )
   {
      return _CorrespBankId[index] == null ? defaultValue : _CorrespBankId[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Id values.
    */
   public final String[] getCorrespBankIdArray()
   {
      return _CorrespBankId;
   }
    
   /**
    * Gets the Correspondent Bank type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank type or null.
    */
   public final String getCorrespBankType( int index )
   {
      return _CorrespBankType[index];
   }
    
   /**
    * Gets the Correspondent Bank type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank type or the specified default value.
    */
   public final String getCorrespBankType( int index, String defaultValue )
   {
      return _CorrespBankType[index] == null ? defaultValue : _CorrespBankType[index];
   }
    
   /**
    * Gets the array of Correspondent Bank type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank type values.
    */
   public final String[] getCorrespBankTypeArray()
   {
      return _CorrespBankType;
   }
    
   /**
    * Gets the Correspondent Bank Id Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Id Number or null.
    */
   public final String getCorrespBankIdNum( int index )
   {
      return _CorrespBankIdNum[index];
   }
    
   /**
    * Gets the Correspondent Bank Id Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Id Number or the specified default value.
    */
   public final String getCorrespBankIdNum( int index, String defaultValue )
   {
      return _CorrespBankIdNum[index] == null ? defaultValue : _CorrespBankIdNum[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Id Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Id Number values.
    */
   public final String[] getCorrespBankIdNumArray()
   {
      return _CorrespBankIdNum;
   }
    
   /**
    * Gets the Correspondent Bank Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Country or null.
    */
   public final String getCorrespBankCntry( int index )
   {
      return _CorrespBankCntry[index];
   }
    
   /**
    * Gets the Correspondent Bank Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Country or the specified default value.
    */
   public final String getCorrespBankCntry( int index, String defaultValue )
   {
      return _CorrespBankCntry[index] == null ? defaultValue : _CorrespBankCntry[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Country values.
    */
   public final String[] getCorrespBankCntryArray()
   {
      return _CorrespBankCntry;
   }
    
   /**
    * Gets the Correspondent Bank Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Postal Code or null.
    */
   public final String getCorrespBankPstl( int index )
   {
      return _CorrespBankPstl[index];
   }
    
   /**
    * Gets the Correspondent Bank Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Postal Code or the specified default value.
    */
   public final String getCorrespBankPstl( int index, String defaultValue )
   {
      return _CorrespBankPstl[index] == null ? defaultValue : _CorrespBankPstl[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Postal Code values.
    */
   public final String[] getCorrespBankPstlArray()
   {
      return _CorrespBankPstl;
   }
    
   /**
    * Gets the Correspondent Bank Address Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address Line 1 or null.
    */
   public final String getCorrespBankAddr1( int index )
   {
      return _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the Correspondent Bank Address Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address Line 1 or the specified default value.
    */
   public final String getCorrespBankAddr1( int index, String defaultValue )
   {
      return _CorrespBankAddr1[index] == null ? defaultValue : _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address Line 1 values.
    */
   public final String[] getCorrespBankAddr1Array()
   {
      return _CorrespBankAddr1;
   }
    
   /**
    * Gets the Correspondent Bank Address Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address Line 2 or null.
    */
   public final String getCorrespBankAddr2( int index )
   {
      return _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the Correspondent Bank Address Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address Line 2 or the specified default value.
    */
   public final String getCorrespBankAddr2( int index, String defaultValue )
   {
      return _CorrespBankAddr2[index] == null ? defaultValue : _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address Line 2 values.
    */
   public final String[] getCorrespBankAddr2Array()
   {
      return _CorrespBankAddr2;
   }
    
   /**
    * Gets the Correspondent Bank Address Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address Line 3 or null.
    */
   public final String getCorrespBankAddr3( int index )
   {
      return _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the Correspondent Bank Address Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address Line 3 or the specified default value.
    */
   public final String getCorrespBankAddr3( int index, String defaultValue )
   {
      return _CorrespBankAddr3[index] == null ? defaultValue : _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address Line 3 values.
    */
   public final String[] getCorrespBankAddr3Array()
   {
      return _CorrespBankAddr3;
   }
    
   /**
    * Gets the Correspondent Bank Address Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address Line 4 or null.
    */
   public final String getCorrespBankAddr4( int index )
   {
      return _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the Correspondent Bank Address Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address Line 4 or the specified default value.
    */
   public final String getCorrespBankAddr4( int index, String defaultValue )
   {
      return _CorrespBankAddr4[index] == null ? defaultValue : _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address Line 4 values.
    */
   public final String[] getCorrespBankAddr4Array()
   {
      return _CorrespBankAddr4;
   }
    
   /**
    * Gets the Correspondent Bank Address Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address Line 5 or null.
    */
   public final String getCorrespBankAddr5( int index )
   {
      return _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the Correspondent Bank Address Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address Line 5 or the specified default value.
    */
   public final String getCorrespBankAddr5( int index, String defaultValue )
   {
      return _CorrespBankAddr5[index] == null ? defaultValue : _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address Line 5 values.
    */
   public final String[] getCorrespBankAddr5Array()
   {
      return _CorrespBankAddr5;
   }
    
   /**
    * Gets the Correspondent Institution Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Institution Name or null.
    */
   public final String getCorrespInstName( int index )
   {
      return _CorrespInstName[index];
   }
    
   /**
    * Gets the Correspondent Institution Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Institution Name or the specified default value.
    */
   public final String getCorrespInstName( int index, String defaultValue )
   {
      return _CorrespInstName[index] == null ? defaultValue : _CorrespInstName[index];
   }
    
   /**
    * Gets the array of Correspondent Institution Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Institution Name values.
    */
   public final String[] getCorrespInstNameArray()
   {
      return _CorrespInstName;
   }
    
   /**
    * Gets the Credit Info Line1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Credit Info Line1 or null.
    */
   public final String getCreditInfoLine1( int index )
   {
      return _CreditInfoLine1[index];
   }
    
   /**
    * Gets the Credit Info Line1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line1 or the specified default value.
    */
   public final String getCreditInfoLine1( int index, String defaultValue )
   {
      return _CreditInfoLine1[index] == null ? defaultValue : _CreditInfoLine1[index];
   }
    
   /**
    * Gets the array of Credit Info Line1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Credit Info Line1 values.
    */
   public final String[] getCreditInfoLine1Array()
   {
      return _CreditInfoLine1;
   }
    
   /**
    * Gets the Credit Info Line2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Credit Info Line2 or null.
    */
   public final String getCreditInfoLine2( int index )
   {
      return _CreditInfoLine2[index];
   }
    
   /**
    * Gets the Credit Info Line2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line2 or the specified default value.
    */
   public final String getCreditInfoLine2( int index, String defaultValue )
   {
      return _CreditInfoLine2[index] == null ? defaultValue : _CreditInfoLine2[index];
   }
    
   /**
    * Gets the array of Credit Info Line2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Credit Info Line2 values.
    */
   public final String[] getCreditInfoLine2Array()
   {
      return _CreditInfoLine2;
   }
    
   /**
    * Gets the Pay Reason Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason Line 1 or null.
    */
   public final String getPayReason1( int index )
   {
      return _PayReason1[index];
   }
    
   /**
    * Gets the Pay Reason Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason Line 1 or the specified default value.
    */
   public final String getPayReason1( int index, String defaultValue )
   {
      return _PayReason1[index] == null ? defaultValue : _PayReason1[index];
   }
    
   /**
    * Gets the array of Pay Reason Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason Line 1 values.
    */
   public final String[] getPayReason1Array()
   {
      return _PayReason1;
   }
    
   /**
    * Gets the Pay Reason Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason Line 2 or null.
    */
   public final String getPayReason2( int index )
   {
      return _PayReason2[index];
   }
    
   /**
    * Gets the Pay Reason Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason Line 2 or the specified default value.
    */
   public final String getPayReason2( int index, String defaultValue )
   {
      return _PayReason2[index] == null ? defaultValue : _PayReason2[index];
   }
    
   /**
    * Gets the array of Pay Reason Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason Line 2 values.
    */
   public final String[] getPayReason2Array()
   {
      return _PayReason2;
   }
    
   /**
    * Gets the Condition Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Condition Rate or null.
    */
   public final String getConditionRate( int index )
   {
      return _ConditionRate[index];
   }
    
   /**
    * Gets the Condition Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Condition Rate or the specified default value.
    */
   public final String getConditionRate( int index, String defaultValue )
   {
      return _ConditionRate[index] == null ? defaultValue : _ConditionRate[index];
   }
    
   /**
    * Gets the array of Condition Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Condition Rate values.
    */
   public final String[] getConditionRateArray()
   {
      return _ConditionRate;
   }
    
   /**
    * Gets the Extra Commission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission or null.
    */
   public final Boolean getExtraCommission( int index )
   {
      return _ExtraCommission[index];
   }
    
   /**
    * Gets the Extra Commission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission or the specified default value.
    */
   public final boolean getExtraCommission( int index, boolean defaultValue )
   {
      return _ExtraCommission[index] == null ? defaultValue : _ExtraCommission[index].booleanValue();
   }
    
   /**
    * Gets the array of Extra Commission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission values.
    */
   public final Boolean[] getExtraCommissionArray()
   {
      return _ExtraCommission;
   }
    
   /**
    * Gets the Override DSC field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override DSC or null.
    */
   public final String getOverrideDSC( int index )
   {
      return _OverrideDSC[index];
   }
    
   /**
    * Gets the Override DSC field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override DSC or the specified default value.
    */
   public final String getOverrideDSC( int index, String defaultValue )
   {
      return _OverrideDSC[index] == null ? defaultValue : _OverrideDSC[index];
   }
    
   /**
    * Gets the array of Override DSC fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override DSC values.
    */
   public final String[] getOverrideDSCArray()
   {
      return _OverrideDSC;
   }
    
   /**
    * Gets the Override DSC Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override DSC Desc or null.
    */
   public final String getOverrideDSCDesc( int index )
   {
      return _OverrideDSCDesc[index];
   }
    
   /**
    * Gets the Override DSC Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override DSC Desc or the specified default value.
    */
   public final String getOverrideDSCDesc( int index, String defaultValue )
   {
      return _OverrideDSCDesc[index] == null ? defaultValue : _OverrideDSCDesc[index];
   }
    
   /**
    * Gets the array of Override DSC Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override DSC Desc values.
    */
   public final String[] getOverrideDSCDescArray()
   {
      return _OverrideDSCDesc;
   }
    
   /**
    * Gets the Override Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Amount or null.
    */
   public final String getOverrideAmt( int index )
   {
      return _OverrideAmt[index];
   }
    
   /**
    * Gets the Override Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Amount or the specified default value.
    */
   public final String getOverrideAmt( int index, String defaultValue )
   {
      return _OverrideAmt[index] == null ? defaultValue : _OverrideAmt[index];
   }
    
   /**
    * Gets the array of Override Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Amount values.
    */
   public final String[] getOverrideAmtArray()
   {
      return _OverrideAmt;
   }
    
   /**
    * Gets the Override Tax field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Override Tax or null.
    */
   public final Boolean getOverrideTax( int index )
   {
      return _OverrideTax[index];
   }
    
   /**
    * Gets the Override Tax field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Override Tax or the specified default value.
    */
   public final boolean getOverrideTax( int index, boolean defaultValue )
   {
      return _OverrideTax[index] == null ? defaultValue : _OverrideTax[index].booleanValue();
   }
    
   /**
    * Gets the array of Override Tax fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Override Tax values.
    */
   public final Boolean[] getOverrideTaxArray()
   {
      return _OverrideTax;
   }
    
   /**
    * Gets the Federal Tax Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Tax Rate or null.
    */
   public final String getFedTaxRate( int index )
   {
      return _FedTaxRate[index];
   }
    
   /**
    * Gets the Federal Tax Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax Rate or the specified default value.
    */
   public final String getFedTaxRate( int index, String defaultValue )
   {
      return _FedTaxRate[index] == null ? defaultValue : _FedTaxRate[index];
   }
    
   /**
    * Gets the array of Federal Tax Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Tax Rate values.
    */
   public final String[] getFedTaxRateArray()
   {
      return _FedTaxRate;
   }
    
   /**
    * Gets the Federal Tax PUD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Federal Tax PUD or null.
    */
   public final String getFedTaxPUD( int index )
   {
      return _FedTaxPUD[index];
   }
    
   /**
    * Gets the Federal Tax PUD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Federal Tax PUD or the specified default value.
    */
   public final String getFedTaxPUD( int index, String defaultValue )
   {
      return _FedTaxPUD[index] == null ? defaultValue : _FedTaxPUD[index];
   }
    
   /**
    * Gets the array of Federal Tax PUD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Federal Tax PUD values.
    */
   public final String[] getFedTaxPUDArray()
   {
      return _FedTaxPUD;
   }
    
   /**
    * Gets the Provincial Tax Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Tax Rate or null.
    */
   public final String getProvTaxRate( int index )
   {
      return _ProvTaxRate[index];
   }
    
   /**
    * Gets the Provincial Tax Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax Rate or the specified default value.
    */
   public final String getProvTaxRate( int index, String defaultValue )
   {
      return _ProvTaxRate[index] == null ? defaultValue : _ProvTaxRate[index];
   }
    
   /**
    * Gets the array of Provincial Tax Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Tax Rate values.
    */
   public final String[] getProvTaxRateArray()
   {
      return _ProvTaxRate;
   }
    
   /**
    * Gets the Provincial Tax PUD field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Provincial Tax PUD or null.
    */
   public final String getProvTaxPUD( int index )
   {
      return _ProvTaxPUD[index];
   }
    
   /**
    * Gets the Provincial Tax PUD field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Provincial Tax PUD or the specified default value.
    */
   public final String getProvTaxPUD( int index, String defaultValue )
   {
      return _ProvTaxPUD[index] == null ? defaultValue : _ProvTaxPUD[index];
   }
    
   /**
    * Gets the array of Provincial Tax PUD fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Provincial Tax PUD values.
    */
   public final String[] getProvTaxPUDArray()
   {
      return _ProvTaxPUD;
   }
    
   /**
    * Gets the DSC Override Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC Override Code or null.
    */
   public final String getDSCOverridecode( int index )
   {
      return _DSCOverridecode[index];
   }
    
   /**
    * Gets the DSC Override Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Override Code or the specified default value.
    */
   public final String getDSCOverridecode( int index, String defaultValue )
   {
      return _DSCOverridecode[index] == null ? defaultValue : _DSCOverridecode[index];
   }
    
   /**
    * Gets the array of DSC Override Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC Override Code values.
    */
   public final String[] getDSCOverridecodeArray()
   {
      return _DSCOverridecode;
   }
    
   /**
    * Gets the DSC Override Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC Override Amount or null.
    */
   public final String getDSCOverrideAmt( int index )
   {
      return _DSCOverrideAmt[index];
   }
    
   /**
    * Gets the DSC Override Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Override Amount or the specified default value.
    */
   public final String getDSCOverrideAmt( int index, String defaultValue )
   {
      return _DSCOverrideAmt[index] == null ? defaultValue : _DSCOverrideAmt[index];
   }
    
   /**
    * Gets the array of DSC Override Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC Override Amount values.
    */
   public final String[] getDSCOverrideAmtArray()
   {
      return _DSCOverrideAmt;
   }
    
   /**
    * Gets the ROA Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ROA Amount or null.
    */
   public final String getROAAmount( int index )
   {
      return _ROAAmount[index];
   }
    
   /**
    * Gets the ROA Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ROA Amount or the specified default value.
    */
   public final String getROAAmount( int index, String defaultValue )
   {
      return _ROAAmount[index] == null ? defaultValue : _ROAAmount[index];
   }
    
   /**
    * Gets the array of ROA Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ROA Amount values.
    */
   public final String[] getROAAmountArray()
   {
      return _ROAAmount;
   }
    
   /**
    * Gets the Payment Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Type or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the Payment Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Type or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of Payment Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Type values.
    */
   public final String[] getPayTypeArray()
   {
      return _PayType;
   }
    
   /**
    * Gets the Payment Type Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Type Desc or null.
    */
   public final String getPayTypeDesc( int index )
   {
      return _PayTypeDesc[index];
   }
    
   /**
    * Gets the Payment Type Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Type Desc or the specified default value.
    */
   public final String getPayTypeDesc( int index, String defaultValue )
   {
      return _PayTypeDesc[index] == null ? defaultValue : _PayTypeDesc[index];
   }
    
   /**
    * Gets the array of Payment Type Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Type Desc values.
    */
   public final String[] getPayTypeDescArray()
   {
      return _PayTypeDesc;
   }
    
   /**
    * Gets the Settlement Currency Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Currency Name or null.
    */
   public final String getSettleCurrName( int index )
   {
      return _SettleCurrName[index];
   }
    
   /**
    * Gets the Settlement Currency Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Currency Name or the specified default value.
    */
   public final String getSettleCurrName( int index, String defaultValue )
   {
      return _SettleCurrName[index] == null ? defaultValue : _SettleCurrName[index];
   }
    
   /**
    * Gets the array of Settlement Currency Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Currency Name values.
    */
   public final String[] getSettleCurrNameArray()
   {
      return _SettleCurrName;
   }
    
   /**
    * Gets the Initial Purchase Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Initial Purchase Desc or null.
    */
   public final String getInitPurchDesc( int index )
   {
      return _InitPurchDesc[index];
   }
    
   /**
    * Gets the Initial Purchase Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Initial Purchase Desc or the specified default value.
    */
   public final String getInitPurchDesc( int index, String defaultValue )
   {
      return _InitPurchDesc[index] == null ? defaultValue : _InitPurchDesc[index];
   }
    
   /**
    * Gets the array of Initial Purchase Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Initial Purchase Desc values.
    */
   public final String[] getInitPurchDescArray()
   {
      return _InitPurchDesc;
   }
    
   /**
    * Gets the Rejection Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rejection Code or null.
    */
   public final String getRejCode( int index )
   {
      return _RejCode[index];
   }
    
   /**
    * Gets the Rejection Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rejection Code or the specified default value.
    */
   public final String getRejCode( int index, String defaultValue )
   {
      return _RejCode[index] == null ? defaultValue : _RejCode[index];
   }
    
   /**
    * Gets the array of Rejection Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rejection Code values.
    */
   public final String[] getRejCodeArray()
   {
      return _RejCode;
   }
    
   /**
    * Gets the Rejection Code Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rejection Code Desc or null.
    */
   public final String getRejCodeDesc( int index )
   {
      return _RejCodeDesc[index];
   }
    
   /**
    * Gets the Rejection Code Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rejection Code Desc or the specified default value.
    */
   public final String getRejCodeDesc( int index, String defaultValue )
   {
      return _RejCodeDesc[index] == null ? defaultValue : _RejCodeDesc[index];
   }
    
   /**
    * Gets the array of Rejection Code Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rejection Code Desc values.
    */
   public final String[] getRejCodeDescArray()
   {
      return _RejCodeDesc;
   }
    
   /**
    * Gets the Broker Commission Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Commission Amount or null.
    */
   public final String getBrokerCommAmt( int index )
   {
      return _BrokerCommAmt[index];
   }
    
   /**
    * Gets the Broker Commission Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Commission Amount or the specified default value.
    */
   public final String getBrokerCommAmt( int index, String defaultValue )
   {
      return _BrokerCommAmt[index] == null ? defaultValue : _BrokerCommAmt[index];
   }
    
   /**
    * Gets the array of Broker Commission Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Commission Amount values.
    */
   public final String[] getBrokerCommAmtArray()
   {
      return _BrokerCommAmt;
   }
    
   /**
    * Gets the Branch Commission Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Commission Amount or null.
    */
   public final String getBranchCommAmt( int index )
   {
      return _BranchCommAmt[index];
   }
    
   /**
    * Gets the Branch Commission Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Commission Amount or the specified default value.
    */
   public final String getBranchCommAmt( int index, String defaultValue )
   {
      return _BranchCommAmt[index] == null ? defaultValue : _BranchCommAmt[index];
   }
    
   /**
    * Gets the array of Branch Commission Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Commission Amount values.
    */
   public final String[] getBranchCommAmtArray()
   {
      return _BranchCommAmt;
   }
    
   /**
    * Gets the Sls Rep Commission Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sls Rep Commission Amount or null.
    */
   public final String getSlsRepCommAmt( int index )
   {
      return _SlsRepCommAmt[index];
   }
    
   /**
    * Gets the Sls Rep Commission Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sls Rep Commission Amount or the specified default value.
    */
   public final String getSlsRepCommAmt( int index, String defaultValue )
   {
      return _SlsRepCommAmt[index] == null ? defaultValue : _SlsRepCommAmt[index];
   }
    
   /**
    * Gets the array of Sls Rep Commission Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sls Rep Commission Amount values.
    */
   public final String[] getSlsRepCommAmtArray()
   {
      return _SlsRepCommAmt;
   }
    
   /**
    * Gets the Mgmt Comp Commission Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mgmt Comp Commission Amount or null.
    */
   public final String getMgmtCompCommAmt( int index )
   {
      return _MgmtCompCommAmt[index];
   }
    
   /**
    * Gets the Mgmt Comp Commission Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mgmt Comp Commission Amount or the specified default value.
    */
   public final String getMgmtCompCommAmt( int index, String defaultValue )
   {
      return _MgmtCompCommAmt[index] == null ? defaultValue : _MgmtCompCommAmt[index];
   }
    
   /**
    * Gets the array of Mgmt Comp Commission Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mgmt Comp Commission Amount values.
    */
   public final String[] getMgmtCompCommAmtArray()
   {
      return _MgmtCompCommAmt;
   }
    
   /**
    * Gets the Total Commission Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total Commission Amount or null.
    */
   public final String getTotalCommAmt( int index )
   {
      return _TotalCommAmt[index];
   }
    
   /**
    * Gets the Total Commission Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Commission Amount or the specified default value.
    */
   public final String getTotalCommAmt( int index, String defaultValue )
   {
      return _TotalCommAmt[index] == null ? defaultValue : _TotalCommAmt[index];
   }
    
   /**
    * Gets the array of Total Commission Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total Commission Amount values.
    */
   public final String[] getTotalCommAmtArray()
   {
      return _TotalCommAmt;
   }
    
   /**
    * Gets the Indicates if view will return Pend, Proc or Both trades field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicates if view will return Pend, Proc or Both trades or null.
    */
   public final String getrxRecordType( int index )
   {
      return _rxRecordType[index];
   }
    
   /**
    * Gets the Indicates if view will return Pend, Proc or Both trades field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if view will return Pend, Proc or Both trades or the specified default value.
    */
   public final String getrxRecordType( int index, String defaultValue )
   {
      return _rxRecordType[index] == null ? defaultValue : _rxRecordType[index];
   }
    
   /**
    * Gets the array of Indicates if view will return Pend, Proc or Both trades fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicates if view will return Pend, Proc or Both trades values.
    */
   public final String[] getrxRecordTypeArray()
   {
      return _rxRecordType;
   }
    
   /**
    * Gets the Additional fee rate for proc trades field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional fee rate for proc trades or null.
    */
   public final Integer getADLFeePrcnt( int index )
   {
      return _ADLFeePrcnt[index];
   }
    
   /**
    * Gets the Additional fee rate for proc trades field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional fee rate for proc trades or the specified default value.
    */
   public final int getADLFeePrcnt( int index, int defaultValue )
   {
      return _ADLFeePrcnt[index] == null ? defaultValue : _ADLFeePrcnt[index].intValue();
   }
    
   /**
    * Gets the array of Additional fee rate for proc trades fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional fee rate for proc trades values.
    */
   public final Integer[] getADLFeePrcntArray()
   {
      return _ADLFeePrcnt;
   }
    
   /**
    * Gets the Additional fee amount for proc trades field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional fee amount for proc trades or null.
    */
   public final String getADLFeeAmt( int index )
   {
      return _ADLFeeAmt[index];
   }
    
   /**
    * Gets the Additional fee amount for proc trades field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional fee amount for proc trades or the specified default value.
    */
   public final String getADLFeeAmt( int index, String defaultValue )
   {
      return _ADLFeeAmt[index] == null ? defaultValue : _ADLFeeAmt[index];
   }
    
   /**
    * Gets the array of Additional fee amount for proc trades fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional fee amount for proc trades values.
    */
   public final String[] getADLFeeAmtArray()
   {
      return _ADLFeeAmt;
   }
    
   /**
    * Gets the Environement Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Environement Code or null.
    */
   public final String getCompanyCode( int index )
   {
      return _CompanyCode[index];
   }
    
   /**
    * Gets the Environement Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Environement Code or the specified default value.
    */
   public final String getCompanyCode( int index, String defaultValue )
   {
      return _CompanyCode[index] == null ? defaultValue : _CompanyCode[index];
   }
    
   /**
    * Gets the array of Environement Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Environement Code values.
    */
   public final String[] getCompanyCodeArray()
   {
      return _CompanyCode;
   }
    
   /**
    * Gets the Processed trade units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Processed trade units or null.
    */
   public final String getUnits( int index )
   {
      return _Units[index];
   }
    
   /**
    * Gets the Processed trade units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Processed trade units or the specified default value.
    */
   public final String getUnits( int index, String defaultValue )
   {
      return _Units[index] == null ? defaultValue : _Units[index];
   }
    
   /**
    * Gets the array of Processed trade units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Processed trade units values.
    */
   public final String[] getUnitsArray()
   {
      return _Units;
   }
    
   /**
    * Gets the Gross amount in fund currency for proc trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross amount in fund currency for proc trade or null.
    */
   public final String getGrossAmt( int index )
   {
      return _GrossAmt[index];
   }
    
   /**
    * Gets the Gross amount in fund currency for proc trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross amount in fund currency for proc trade or the specified default value.
    */
   public final String getGrossAmt( int index, String defaultValue )
   {
      return _GrossAmt[index] == null ? defaultValue : _GrossAmt[index];
   }
    
   /**
    * Gets the array of Gross amount in fund currency for proc trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross amount in fund currency for proc trade values.
    */
   public final String[] getGrossAmtArray()
   {
      return _GrossAmt;
   }
    
   /**
    * Gets the Net amount in fund currency for proc trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net amount in fund currency for proc trade or null.
    */
   public final String getNetAmt( int index )
   {
      return _NetAmt[index];
   }
    
   /**
    * Gets the Net amount in fund currency for proc trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net amount in fund currency for proc trade or the specified default value.
    */
   public final String getNetAmt( int index, String defaultValue )
   {
      return _NetAmt[index] == null ? defaultValue : _NetAmt[index];
   }
    
   /**
    * Gets the array of Net amount in fund currency for proc trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net amount in fund currency for proc trade values.
    */
   public final String[] getNetAmtArray()
   {
      return _NetAmt;
   }
    
   /**
    * Gets the Gross amount in settlement currency for proc trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross amount in settlement currency for proc trade or null.
    */
   public final String getGrossAmtInSettleCurr( int index )
   {
      return _GrossAmtInSettleCurr[index];
   }
    
   /**
    * Gets the Gross amount in settlement currency for proc trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross amount in settlement currency for proc trade or the specified default value.
    */
   public final String getGrossAmtInSettleCurr( int index, String defaultValue )
   {
      return _GrossAmtInSettleCurr[index] == null ? defaultValue : _GrossAmtInSettleCurr[index];
   }
    
   /**
    * Gets the array of Gross amount in settlement currency for proc trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross amount in settlement currency for proc trade values.
    */
   public final String[] getGrossAmtInSettleCurrArray()
   {
      return _GrossAmtInSettleCurr;
   }
    
   /**
    * Gets the Net amount in settlement currency for processed trade. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net amount in settlement currency for processed trade. or null.
    */
   public final String getNetAmtInSettleCurr( int index )
   {
      return _NetAmtInSettleCurr[index];
   }
    
   /**
    * Gets the Net amount in settlement currency for processed trade. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net amount in settlement currency for processed trade. or the specified default value.
    */
   public final String getNetAmtInSettleCurr( int index, String defaultValue )
   {
      return _NetAmtInSettleCurr[index] == null ? defaultValue : _NetAmtInSettleCurr[index];
   }
    
   /**
    * Gets the array of Net amount in settlement currency for processed trade. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net amount in settlement currency for processed trade. values.
    */
   public final String[] getNetAmtInSettleCurrArray()
   {
      return _NetAmtInSettleCurr;
   }
    
   /**
    * Gets the Flag indicating if trade is settled field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if trade is settled or null.
    */
   public final Boolean getSettled( int index )
   {
      return _Settled[index];
   }
    
   /**
    * Gets the Flag indicating if trade is settled field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if trade is settled or the specified default value.
    */
   public final boolean getSettled( int index, boolean defaultValue )
   {
      return _Settled[index] == null ? defaultValue : _Settled[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if trade is settled fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if trade is settled values.
    */
   public final Boolean[] getSettledArray()
   {
      return _Settled;
   }
    
   /**
    * Gets the Indicates if money out was full or partial money out. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicates if money out was full or partial money out. or null.
    */
   public final String getFullPartial( int index )
   {
      return _FullPartial[index];
   }
    
   /**
    * Gets the Indicates if money out was full or partial money out. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if money out was full or partial money out. or the specified default value.
    */
   public final String getFullPartial( int index, String defaultValue )
   {
      return _FullPartial[index] == null ? defaultValue : _FullPartial[index];
   }
    
   /**
    * Gets the array of Indicates if money out was full or partial money out. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicates if money out was full or partial money out. values.
    */
   public final String[] getFullPartialArray()
   {
      return _FullPartial;
   }
    
   /**
    * Gets the Full estimanted money out. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Full estimanted money out. or null.
    */
   public final String getMktValue( int index )
   {
      return _MktValue[index];
   }
    
   /**
    * Gets the Full estimanted money out. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Full estimanted money out. or the specified default value.
    */
   public final String getMktValue( int index, String defaultValue )
   {
      return _MktValue[index] == null ? defaultValue : _MktValue[index];
   }
    
   /**
    * Gets the array of Full estimanted money out. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Full estimanted money out. values.
    */
   public final String[] getMktValueArray()
   {
      return _MktValue;
   }
    
   /**
    * Gets the SettleDate of transfer/exchange in field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SettleDate of transfer/exchange in or null.
    */
   public final Date getSettleInDate( int index )
   {
      return _SettleInDate[index];
   }
    
   /**
    * Gets the SettleDate of transfer/exchange in field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SettleDate of transfer/exchange in or the specified default value.
    */
   public final Date getSettleInDate( int index, Date defaultValue )
   {
      return _SettleInDate[index] == null ? defaultValue : _SettleInDate[index];
   }
    
   /**
    * Gets the array of SettleDate of transfer/exchange in fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SettleDate of transfer/exchange in values.
    */
   public final Date[] getSettleInDateArray()
   {
      return _SettleInDate;
   }
    
   /**
    * Gets the TUP - Traded unit position at the time the trade was entered field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TUP - Traded unit position at the time the trade was entered or null.
    */
   public final String getTUPUnits( int index )
   {
      return _TUPUnits[index];
   }
    
   /**
    * Gets the TUP - Traded unit position at the time the trade was entered field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TUP - Traded unit position at the time the trade was entered or the specified default value.
    */
   public final String getTUPUnits( int index, String defaultValue )
   {
      return _TUPUnits[index] == null ? defaultValue : _TUPUnits[index];
   }
    
   /**
    * Gets the array of TUP - Traded unit position at the time the trade was entered fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TUP - Traded unit position at the time the trade was entered values.
    */
   public final String[] getTUPUnitsArray()
   {
      return _TUPUnits;
   }
    
   /**
    * Gets the SUP - Settled units + marked settled units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SUP - Settled units + marked settled units or null.
    */
   public final String getSUPUnits( int index )
   {
      return _SUPUnits[index];
   }
    
   /**
    * Gets the SUP - Settled units + marked settled units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SUP - Settled units + marked settled units or the specified default value.
    */
   public final String getSUPUnits( int index, String defaultValue )
   {
      return _SUPUnits[index] == null ? defaultValue : _SUPUnits[index];
   }
    
   /**
    * Gets the array of SUP - Settled units + marked settled units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SUP - Settled units + marked settled units values.
    */
   public final String[] getSUPUnitsArray()
   {
      return _SUPUnits;
   }
    
   /**
    * Gets the TUP Tolerance % - Environment or fund level, whichever applies field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TUP Tolerance % - Environment or fund level, whichever applies or null.
    */
   public final String getTUPToleranceRate( int index )
   {
      return _TUPToleranceRate[index];
   }
    
   /**
    * Gets the TUP Tolerance % - Environment or fund level, whichever applies field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TUP Tolerance % - Environment or fund level, whichever applies or the specified default value.
    */
   public final String getTUPToleranceRate( int index, String defaultValue )
   {
      return _TUPToleranceRate[index] == null ? defaultValue : _TUPToleranceRate[index];
   }
    
   /**
    * Gets the array of TUP Tolerance % - Environment or fund level, whichever applies fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TUP Tolerance % - Environment or fund level, whichever applies values.
    */
   public final String[] getTUPToleranceRateArray()
   {
      return _TUPToleranceRate;
   }
    
   /**
    * Gets the TUP tolerance units - Traded unit position X TUP Tolerance % field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TUP tolerance units - Traded unit position X TUP Tolerance % or null.
    */
   public final String getTUPToleranceUnits( int index )
   {
      return _TUPToleranceUnits[index];
   }
    
   /**
    * Gets the TUP tolerance units - Traded unit position X TUP Tolerance % field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TUP tolerance units - Traded unit position X TUP Tolerance % or the specified default value.
    */
   public final String getTUPToleranceUnits( int index, String defaultValue )
   {
      return _TUPToleranceUnits[index] == null ? defaultValue : _TUPToleranceUnits[index];
   }
    
   /**
    * Gets the array of TUP tolerance units - Traded unit position X TUP Tolerance % fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TUP tolerance units - Traded unit position X TUP Tolerance % values.
    */
   public final String[] getTUPToleranceUnitsArray()
   {
      return _TUPToleranceUnits;
   }
    
   /**
    * Gets the TUP Oversell – Unit amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TUP Oversell – Unit amount or null.
    */
   public final String getTUPOversellUnits( int index )
   {
      return _TUPOversellUnits[index];
   }
    
   /**
    * Gets the TUP Oversell – Unit amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TUP Oversell – Unit amount or the specified default value.
    */
   public final String getTUPOversellUnits( int index, String defaultValue )
   {
      return _TUPOversellUnits[index] == null ? defaultValue : _TUPOversellUnits[index];
   }
    
   /**
    * Gets the array of TUP Oversell – Unit amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TUP Oversell – Unit amount values.
    */
   public final String[] getTUPOversellUnitsArray()
   {
      return _TUPOversellUnits;
   }
    
   /**
    * Gets the SUP Oversell – Unit amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SUP Oversell – Unit amount or null.
    */
   public final String getSUPOversellUnits( int index )
   {
      return _SUPOversellUnits[index];
   }
    
   /**
    * Gets the SUP Oversell – Unit amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SUP Oversell – Unit amount or the specified default value.
    */
   public final String getSUPOversellUnits( int index, String defaultValue )
   {
      return _SUPOversellUnits[index] == null ? defaultValue : _SUPOversellUnits[index];
   }
    
   /**
    * Gets the array of SUP Oversell – Unit amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SUP Oversell – Unit amount values.
    */
   public final String[] getSUPOversellUnitsArray()
   {
      return _SUPOversellUnits;
   }
    
   /**
    * Gets the Registration Agent Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Registration Agent Code or null.
    */
   public final String getRegAgentCode( int index )
   {
      return _RegAgentCode[index];
   }
    
   /**
    * Gets the Registration Agent Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Registration Agent Code or the specified default value.
    */
   public final String getRegAgentCode( int index, String defaultValue )
   {
      return _RegAgentCode[index] == null ? defaultValue : _RegAgentCode[index];
   }
    
   /**
    * Gets the array of Registration Agent Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Registration Agent Code values.
    */
   public final String[] getRegAgentCodeArray()
   {
      return _RegAgentCode;
   }
    
   /**
    * Gets the Account Tax Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Tax Type or null.
    */
   public final String getAccountTaxType( int index )
   {
      return _AccountTaxType[index];
   }
    
   /**
    * Gets the Account Tax Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Tax Type or the specified default value.
    */
   public final String getAccountTaxType( int index, String defaultValue )
   {
      return _AccountTaxType[index] == null ? defaultValue : _AccountTaxType[index];
   }
    
   /**
    * Gets the array of Account Tax Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Tax Type values.
    */
   public final String[] getAccountTaxTypeArray()
   {
      return _AccountTaxType;
   }
    
   /**
    * Gets the Reference Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reference Code or null.
    */
   public final String getRefCode( int index )
   {
      return _RefCode[index];
   }
    
   /**
    * Gets the Reference Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Code or the specified default value.
    */
   public final String getRefCode( int index, String defaultValue )
   {
      return _RefCode[index] == null ? defaultValue : _RefCode[index];
   }
    
   /**
    * Gets the array of Reference Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reference Code values.
    */
   public final String[] getRefCodeArray()
   {
      return _RefCode;
   }
    
   /**
    * Gets the RDR Trade Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RDR Trade Value or null.
    */
   public final String getRDRTradeValue( int index )
   {
      return _RDRTradeValue[index];
   }
    
   /**
    * Gets the RDR Trade Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RDR Trade Value or the specified default value.
    */
   public final String getRDRTradeValue( int index, String defaultValue )
   {
      return _RDRTradeValue[index] == null ? defaultValue : _RDRTradeValue[index];
   }
    
   /**
    * Gets the array of RDR Trade Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RDR Trade Value values.
    */
   public final String[] getRDRTradeValueArray()
   {
      return _RDRTradeValue;
   }
    
   /**
    * Gets the RDR Default Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RDR Default Value or null.
    */
   public final String getRDRDefaultValue( int index )
   {
      return _RDRDefaultValue[index];
   }
    
   /**
    * Gets the RDR Default Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RDR Default Value or the specified default value.
    */
   public final String getRDRDefaultValue( int index, String defaultValue )
   {
      return _RDRDefaultValue[index] == null ? defaultValue : _RDRDefaultValue[index];
   }
    
   /**
    * Gets the array of RDR Default Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RDR Default Value values.
    */
   public final String[] getRDRDefaultValueArray()
   {
      return _RDRDefaultValue;
   }
    
   /**
    * Gets the Event Receipt Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Event Receipt Date or null.
    */
   public final Date getEventReceiptDate( int index )
   {
      return _EventReceiptDate[index];
   }
    
   /**
    * Gets the Event Receipt Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Receipt Date or the specified default value.
    */
   public final Date getEventReceiptDate( int index, Date defaultValue )
   {
      return _EventReceiptDate[index] == null ? defaultValue : _EventReceiptDate[index];
   }
    
   /**
    * Gets the array of Event Receipt Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Receipt Date values.
    */
   public final Date[] getEventReceiptDateArray()
   {
      return _EventReceiptDate;
   }
    
   /**
    * Gets the Event Receipt Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Event Receipt Time or null.
    */
   public final String getEventReceiptTime( int index )
   {
      return _EventReceiptTime[index];
   }
    
   /**
    * Gets the Event Receipt Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Receipt Time or the specified default value.
    */
   public final String getEventReceiptTime( int index, String defaultValue )
   {
      return _EventReceiptTime[index] == null ? defaultValue : _EventReceiptTime[index];
   }
    
   /**
    * Gets the array of Event Receipt Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Receipt Time values.
    */
   public final String[] getEventReceiptTimeArray()
   {
      return _EventReceiptTime;
   }
    
   /**
    * Gets the Dealer Action field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dealer Action or null.
    */
   public final Boolean getDealerAction( int index )
   {
      return _DealerAction[index];
   }
    
   /**
    * Gets the Dealer Action field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dealer Action or the specified default value.
    */
   public final boolean getDealerAction( int index, boolean defaultValue )
   {
      return _DealerAction[index] == null ? defaultValue : _DealerAction[index].booleanValue();
   }
    
   /**
    * Gets the array of Dealer Action fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dealer Action values.
    */
   public final Boolean[] getDealerActionArray()
   {
      return _DealerAction;
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
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _TradeDate = resizeArray( _TradeDate, _RepeatCount );
      _SettleDate = resizeArray( _SettleDate, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _TransTypeDesc = resizeArray( _TransTypeDesc, _RepeatCount );
      _TransNum = resizeArray( _TransNum, _RepeatCount );
      _AccountTo = resizeArray( _AccountTo, _RepeatCount );
      _AcctToName = resizeArray( _AcctToName, _RepeatCount );
      _FundTo = resizeArray( _FundTo, _RepeatCount );
      _ClassToCode = resizeArray( _ClassToCode, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _AmountType = resizeArray( _AmountType, _RepeatCount );
      _AmountTypeDesc = resizeArray( _AmountTypeDesc, _RepeatCount );
      _GrossOrNet = resizeArray( _GrossOrNet, _RepeatCount );
      _OrderType = resizeArray( _OrderType, _RepeatCount );
      _WireOrdNum = resizeArray( _WireOrdNum, _RepeatCount );
      _BatchUser = resizeArray( _BatchUser, _RepeatCount );
      _GoodBad = resizeArray( _GoodBad, _RepeatCount );
      _PendingRid = resizeArray( _PendingRid, _RepeatCount );
      _SettleCurrency = resizeArray( _SettleCurrency, _RepeatCount );
      _ShrNum = resizeArray( _ShrNum, _RepeatCount );
      _rxAccountNum = resizeArray( _rxAccountNum, _RepeatCount );
      _GoodBadDesc = resizeArray( _GoodBadDesc, _RepeatCount );
      _OrderTypeDesc = resizeArray( _OrderTypeDesc, _RepeatCount );
      _AMSTrade = resizeArray( _AMSTrade, _RepeatCount );
      _TradeAMSCode = resizeArray( _TradeAMSCode, _RepeatCount );
      _TxnFee = resizeArray( _TxnFee, _RepeatCount );
      _AcqFeeOption = resizeArray( _AcqFeeOption, _RepeatCount );
      _Fee = resizeArray( _Fee, _RepeatCount );
      _FlatPercent = resizeArray( _FlatPercent, _RepeatCount );
      _FeeCurrency = resizeArray( _FeeCurrency, _RepeatCount );
      _BELFee = resizeArray( _BELFee, _RepeatCount );
      _AdminFeeAmt = resizeArray( _AdminFeeAmt, _RepeatCount );
      _UseEnteredFee = resizeArray( _UseEnteredFee, _RepeatCount );
      _ExchInFee = resizeArray( _ExchInFee, _RepeatCount );
      _ExchInFlatPercent = resizeArray( _ExchInFlatPercent, _RepeatCount );
      _ExchOutFee = resizeArray( _ExchOutFee, _RepeatCount );
      _ExchOutFlatPrcnt = resizeArray( _ExchOutFlatPrcnt, _RepeatCount );
      _ChargeERSTTRFee = resizeArray( _ChargeERSTTRFee, _RepeatCount );
      _ChargeWDFee = resizeArray( _ChargeWDFee, _RepeatCount );
      _IFeeTo = resizeArray( _IFeeTo, _RepeatCount );
      _ChargeADLFee = resizeArray( _ChargeADLFee, _RepeatCount );
      _Baycom = resizeArray( _Baycom, _RepeatCount );
      _BaycomTo = resizeArray( _BaycomTo, _RepeatCount );
      _FundISIN = resizeArray( _FundISIN, _RepeatCount );
      _FundToISIN = resizeArray( _FundToISIN, _RepeatCount );
      _FundCurrency = resizeArray( _FundCurrency, _RepeatCount );
      _SysNAV = resizeArray( _SysNAV, _RepeatCount );
      _SysExchRate = resizeArray( _SysExchRate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _BrokerCode = resizeArray( _BrokerCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _SlsRepCode = resizeArray( _SlsRepCode, _RepeatCount );
      _BrokerName = resizeArray( _BrokerName, _RepeatCount );
      _BranchName = resizeArray( _BranchName, _RepeatCount );
      _SlsRepName = resizeArray( _SlsRepName, _RepeatCount );
      _ToBrokerCode = resizeArray( _ToBrokerCode, _RepeatCount );
      _ToSlsRepCode = resizeArray( _ToSlsRepCode, _RepeatCount );
      _Remarks1 = resizeArray( _Remarks1, _RepeatCount );
      _Remarks2 = resizeArray( _Remarks2, _RepeatCount );
      _Remarks3 = resizeArray( _Remarks3, _RepeatCount );
      _InitPurch = resizeArray( _InitPurch, _RepeatCount );
      _Verified = resizeArray( _Verified, _RepeatCount );
      _FirstName = resizeArray( _FirstName, _RepeatCount );
      _LastName = resizeArray( _LastName, _RepeatCount );
      _NetworkId = resizeArray( _NetworkId, _RepeatCount );
      _ExtTransNum = resizeArray( _ExtTransNum, _RepeatCount );
      _SendRefNum = resizeArray( _SendRefNum, _RepeatCount );
      _DiscountRate = resizeArray( _DiscountRate, _RepeatCount );
      _TransId = resizeArray( _TransId, _RepeatCount );
      _ExchRate = resizeArray( _ExchRate, _RepeatCount );
      _BrokerCommPrcnt = resizeArray( _BrokerCommPrcnt, _RepeatCount );
      _BrokerCommRate = resizeArray( _BrokerCommRate, _RepeatCount );
      _BranchCommPrcnt = resizeArray( _BranchCommPrcnt, _RepeatCount );
      _BranchCommRate = resizeArray( _BranchCommRate, _RepeatCount );
      _SlsRepCommPrcnt = resizeArray( _SlsRepCommPrcnt, _RepeatCount );
      _SlsRepCommRate = resizeArray( _SlsRepCommRate, _RepeatCount );
      _MgmtCompCommPrcnt = resizeArray( _MgmtCompCommPrcnt, _RepeatCount );
      _MgmtCompCommRate = resizeArray( _MgmtCompCommRate, _RepeatCount );
      _TotalCommPrcnt = resizeArray( _TotalCommPrcnt, _RepeatCount );
      _TotalCommRate = resizeArray( _TotalCommRate, _RepeatCount );
      _BankId = resizeArray( _BankId, _RepeatCount );
      _BankType = resizeArray( _BankType, _RepeatCount );
      _BankIdNum = resizeArray( _BankIdNum, _RepeatCount );
      _BankCntry = resizeArray( _BankCntry, _RepeatCount );
      _BankPstl = resizeArray( _BankPstl, _RepeatCount );
      _BankAddr1 = resizeArray( _BankAddr1, _RepeatCount );
      _BankAddr2 = resizeArray( _BankAddr2, _RepeatCount );
      _BankAddr3 = resizeArray( _BankAddr3, _RepeatCount );
      _BankAddr4 = resizeArray( _BankAddr4, _RepeatCount );
      _BankAddr5 = resizeArray( _BankAddr5, _RepeatCount );
      _InstName = resizeArray( _InstName, _RepeatCount );
      _BankAcctNum = resizeArray( _BankAcctNum, _RepeatCount );
      _BankAcctName = resizeArray( _BankAcctName, _RepeatCount );
      _CorrespBankId = resizeArray( _CorrespBankId, _RepeatCount );
      _CorrespBankType = resizeArray( _CorrespBankType, _RepeatCount );
      _CorrespBankIdNum = resizeArray( _CorrespBankIdNum, _RepeatCount );
      _CorrespBankCntry = resizeArray( _CorrespBankCntry, _RepeatCount );
      _CorrespBankPstl = resizeArray( _CorrespBankPstl, _RepeatCount );
      _CorrespBankAddr1 = resizeArray( _CorrespBankAddr1, _RepeatCount );
      _CorrespBankAddr2 = resizeArray( _CorrespBankAddr2, _RepeatCount );
      _CorrespBankAddr3 = resizeArray( _CorrespBankAddr3, _RepeatCount );
      _CorrespBankAddr4 = resizeArray( _CorrespBankAddr4, _RepeatCount );
      _CorrespBankAddr5 = resizeArray( _CorrespBankAddr5, _RepeatCount );
      _CorrespInstName = resizeArray( _CorrespInstName, _RepeatCount );
      _CreditInfoLine1 = resizeArray( _CreditInfoLine1, _RepeatCount );
      _CreditInfoLine2 = resizeArray( _CreditInfoLine2, _RepeatCount );
      _PayReason1 = resizeArray( _PayReason1, _RepeatCount );
      _PayReason2 = resizeArray( _PayReason2, _RepeatCount );
      _ConditionRate = resizeArray( _ConditionRate, _RepeatCount );
      _ExtraCommission = resizeArray( _ExtraCommission, _RepeatCount );
      _OverrideDSC = resizeArray( _OverrideDSC, _RepeatCount );
      _OverrideDSCDesc = resizeArray( _OverrideDSCDesc, _RepeatCount );
      _OverrideAmt = resizeArray( _OverrideAmt, _RepeatCount );
      _OverrideTax = resizeArray( _OverrideTax, _RepeatCount );
      _FedTaxRate = resizeArray( _FedTaxRate, _RepeatCount );
      _FedTaxPUD = resizeArray( _FedTaxPUD, _RepeatCount );
      _ProvTaxRate = resizeArray( _ProvTaxRate, _RepeatCount );
      _ProvTaxPUD = resizeArray( _ProvTaxPUD, _RepeatCount );
      _DSCOverridecode = resizeArray( _DSCOverridecode, _RepeatCount );
      _DSCOverrideAmt = resizeArray( _DSCOverrideAmt, _RepeatCount );
      _ROAAmount = resizeArray( _ROAAmount, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _PayTypeDesc = resizeArray( _PayTypeDesc, _RepeatCount );
      _SettleCurrName = resizeArray( _SettleCurrName, _RepeatCount );
      _InitPurchDesc = resizeArray( _InitPurchDesc, _RepeatCount );
      _RejCode = resizeArray( _RejCode, _RepeatCount );
      _RejCodeDesc = resizeArray( _RejCodeDesc, _RepeatCount );
      _BrokerCommAmt = resizeArray( _BrokerCommAmt, _RepeatCount );
      _BranchCommAmt = resizeArray( _BranchCommAmt, _RepeatCount );
      _SlsRepCommAmt = resizeArray( _SlsRepCommAmt, _RepeatCount );
      _MgmtCompCommAmt = resizeArray( _MgmtCompCommAmt, _RepeatCount );
      _TotalCommAmt = resizeArray( _TotalCommAmt, _RepeatCount );
      _rxRecordType = resizeArray( _rxRecordType, _RepeatCount );
      _ADLFeePrcnt = resizeArray( _ADLFeePrcnt, _RepeatCount );
      _ADLFeeAmt = resizeArray( _ADLFeeAmt, _RepeatCount );
      _CompanyCode = resizeArray( _CompanyCode, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _GrossAmt = resizeArray( _GrossAmt, _RepeatCount );
      _NetAmt = resizeArray( _NetAmt, _RepeatCount );
      _GrossAmtInSettleCurr = resizeArray( _GrossAmtInSettleCurr, _RepeatCount );
      _NetAmtInSettleCurr = resizeArray( _NetAmtInSettleCurr, _RepeatCount );
      _Settled = resizeArray( _Settled, _RepeatCount );
      _FullPartial = resizeArray( _FullPartial, _RepeatCount );
      _MktValue = resizeArray( _MktValue, _RepeatCount );
      _SettleInDate = resizeArray( _SettleInDate, _RepeatCount );
      _TUPUnits = resizeArray( _TUPUnits, _RepeatCount );
      _SUPUnits = resizeArray( _SUPUnits, _RepeatCount );
      _TUPToleranceRate = resizeArray( _TUPToleranceRate, _RepeatCount );
      _TUPToleranceUnits = resizeArray( _TUPToleranceUnits, _RepeatCount );
      _TUPOversellUnits = resizeArray( _TUPOversellUnits, _RepeatCount );
      _SUPOversellUnits = resizeArray( _SUPOversellUnits, _RepeatCount );
      _RegAgentCode = resizeArray( _RegAgentCode, _RepeatCount );
      _AccountTaxType = resizeArray( _AccountTaxType, _RepeatCount );
      _RefCode = resizeArray( _RefCode, _RepeatCount );
      _RDRTradeValue = resizeArray( _RDRTradeValue, _RepeatCount );
      _RDRDefaultValue = resizeArray( _RDRDefaultValue, _RepeatCount );
      _EventReceiptDate = resizeArray( _EventReceiptDate, _RepeatCount );
      _EventReceiptTime = resizeArray( _EventReceiptTime, _RepeatCount );
      _DealerAction = resizeArray( _DealerAction, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AccountTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctToName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassToCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossOrNet[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OrderType[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _WireOrdNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GoodBad[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PendingRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SettleCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GoodBadDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrderTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMSTrade[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TradeAMSCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqFeeOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FlatPercent[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELFee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AdminFeeAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UseEnteredFee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExchInFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchInFlatPercent[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExchOutFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchOutFlatPrcnt[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ChargeERSTTRFee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ChargeWDFee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _IFeeTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChargeADLFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Baycom[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BaycomTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundISIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundToISIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SysNAV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SysExchRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ToBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ToSlsRepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InitPurch[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Verified[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetworkId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExtTransNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SendRefNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DiscountRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerCommPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerCommRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCommPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCommRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepCommPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepCommRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtCompCommPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtCompCommRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotalCommPrcnt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotalCommRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankIdNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankIdNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespInstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreditInfoLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreditInfoLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ConditionRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExtraCommission[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OverrideDSC[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OverrideDSCDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OverrideAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OverrideTax[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FedTaxRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FedTaxPUD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvTaxRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvTaxPUD[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DSCOverridecode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DSCOverrideAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROAAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleCurrName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InitPurchDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RejCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RejCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerCommAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCommAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepCommAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtCompCommAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotalCommAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxRecordType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ADLFeePrcnt[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ADLFeeAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CompanyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossAmtInSettleCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetAmtInSettleCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Settled[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FullPartial[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MktValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleInDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TUPUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SUPUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TUPToleranceRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TUPToleranceUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TUPOversellUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SUPOversellUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegAgentCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountTaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RefCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RDRTradeValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RDRDefaultValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EventReceiptDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EventReceiptTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DealerAction[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
