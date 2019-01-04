
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Settlements Search view.
 * For additional view information see <A HREF="../../../../viewspecs/SettlSrch.doc">SettlSrch.doc</A>.
 * 
 * @author RTS Generated
 */
public class SettlSrchView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Company Code member array.
    */
   private String[] _rxCompCode = null;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAcctNumber = null;
   
   /**
    * Wire Order Number member array.
    */
   private String[] _rxWireOrdNum = null;
   
   /**
    * Transaction Number member array.
    */
   private Integer[] _rxTransNum = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Gross Amount member array.
    */
   private String[] _GrossAmt = null;
   
   /**
    * Transaction ID member array.
    */
   private String[] _TransID = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _rxTransType = null;
   
   /**
    * Trade Date member array.
    */
   private Date[] _rxTradeDate = null;
   
   /**
    * Value Date member array.
    */
   private Date[] _rxValueDate = null;
   
   /**
    * Broker Code member array.
    */
   private String[] _rxBrokerCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = null;
   
   /**
    * Sales Rep Code member array.
    */
   private String[] _SlsRepCode = null;
   
   /**
    * Settle Currency member array.
    */
   private String[] _rxSettlCurr = null;
   
   /**
    * Gross/Net/Split settlement member array.
    */
   private String[] _GNSettle = null;
   
   /**
    * Trans Detl Recid member array.
    */
   private Integer[] _TransDetlRid = null;
   
   /**
    * Commission member array.
    */
   private String[] _Commission = null;
   
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * Payee Name 1 member array.
    */
   private String[] _Name1 = null;
   
   /**
    * Payee Name 2 member array.
    */
   private String[] _Name2 = null;
   
   /**
    * Payee Address Line 1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Payee Address Line 2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Payee Address Line 3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Payee Address Line 4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Payee Address Line 5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Payee Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Payee Country Code member array.
    */
   private String[] _CountryCode = null;
   
   /**
    * Dist Fee member array.
    */
   private String[] _DistFee = null;
   
   /**
    * Fee member array.
    */
   private String[] _Fee = null;
   
   /**
    * Units member array.
    */
   private String[] _Units = null;
   
   /**
    * Acct Value member array.
    */
   private String[] _AcctValue = null;
   
   /**
    * Price member array.
    */
   private String[] _Price = null;
   
   /**
    * Net Amount member array.
    */
   private String[] _NetAmt = null;
   
   /**
    * Pay Type member array.
    */
   private String[] _PayType = null;
   
   /**
    * Pay Method member array.
    */
   private String[] _PayMethod = null;
   
   /**
    * Alternate Account member array.
    */
   private String[] _AltAccount = null;
   
   /**
    * Settle Date member array.
    */
   private Date[] _rxSettleDate = null;
   
   /**
    * Commission 2 member array.
    */
   private String[] _Commission2 = null;
   
   /**
    * Original Order Source member array.
    */
   private String[] _OrigOrderSource = null;
   
   /**
    * Original Settle Source member array.
    */
   private String[] _OrigSettleSource = null;
   
   /**
    * Original Settlement Type member array.
    */
   private String[] _OrigSettleType = null;
   
   /**
    * Bank Charge member array.
    */
   private String[] _BankCharge = null;
   
   /**
    * Delivery Method member array.
    */
   private String[] _DeliveryMethod = null;
   
   /**
    * Volume Settlement Type member array.
    */
   private String[] _VolSettleType = null;
   
   /**
    * Settlement Method member array.
    */
   private Integer[] _SettleMethod = null;
   
   /**
    * Cheque Suppress Code member array.
    */
   private String[] _SuppressCode = null;
   
   /**
    * Exchange Rate member array.
    */
   private String[] _ExchRate = null;
   
   /**
    * Batch Name member array.
    */
   private String[] _BatchName = null;
   
   /**
    * Institution Name member array.
    */
   private String[] _InstName = null;
   
   /**
    * Swift Code member array.
    */
   private Integer[] _SwiftCode = null;
   
   /**
    * Reference Number member array.
    */
   private Integer[] _RefNumber = null;
   
   /**
    * Transit Number member array.
    */
   private Integer[] _TransitNo = null;
   
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNum = null;
   
   /**
    * Bank Account Name member array.
    */
   private String[] _BankAcctName = null;
   
   /**
    * Bank Account Type member array.
    */
   private String[] _BankAcctType = null;
   
   /**
    * Bank Account Type Desc member array.
    */
   private String[] _BankAcctTypeDesc = null;
   
   /**
    * Bank Account Currency member array.
    */
   private String[] _BankAcctCurrency = null;
   
   /**
    * Bank Account Currency Desc member array.
    */
   private String[] _BankAcctCurrDesc = null;
   
   /**
    * Pay Reason line 1 member array.
    */
   private String[] _PayReason1 = null;
   
   /**
    * Pay Reason line 2 member array.
    */
   private String[] _PayReason2 = null;
   
   /**
    * Correspondent Bank Id member array.
    */
   private String[] _CorrespBankId = null;
   
   /**
    * Bank Type member array.
    */
   private String[] _BankType = null;
   
   /**
    * Correspondent Bank Type member array.
    */
   private String[] _CorrespBankType = null;
   
   /**
    * Correspondent Bank ID Number member array.
    */
   private String[] _CorrespBankIDNum = null;
   
   /**
    * Credit Info Line 1 member array.
    */
   private String[] _CreditInfoLine1 = null;
   
   /**
    * Credit Info Line 2 member array.
    */
   private String[] _CreditInfoLine2 = null;
   
   /**
    * ACH Processor member array.
    */
   private String[] _ACHProcessor = null;
   
   /**
    * Correspondent Bank Contact member array.
    */
   private String[] _CorrespBankContact = null;
   
   /**
    * Correspondent Bank Country member array.
    */
   private String[] _CorrespBankCntry = null;
   
   /**
    * Correspondent Bank postal code member array.
    */
   private String[] _CorrespBankPstl = null;
   
   /**
    * Correspondent Bank Address 1 member array.
    */
   private String[] _CorrespBankAddr1 = null;
   
   /**
    * Correspondent Bank Address 2 member array.
    */
   private String[] _CorrespBankAddr2 = null;
   
   /**
    * Correspondent Bank Address 3 member array.
    */
   private String[] _CorrespBankAddr3 = null;
   
   /**
    * Correspondent Bank Address 4 member array.
    */
   private String[] _CorrespBankAddr4 = null;
   
   /**
    * Correspondent Bank Address 5 member array.
    */
   private String[] _CorrespBankAddr5 = null;
   
   /**
    * Bank Address 1 member array.
    */
   private String[] _BankAddr1 = null;
   
   /**
    * Bank Address 2 member array.
    */
   private String[] _BankAddr2 = null;
   
   /**
    * Bank Address 3 member array.
    */
   private String[] _BankAddr3 = null;
   
   /**
    * Bank Address 4 member array.
    */
   private String[] _BankAddr4 = null;
   
   /**
    * Bank Address 5 member array.
    */
   private String[] _BankAddr5 = null;
   
   /**
    * Bank Contact member array.
    */
   private String[] _BankContact = null;
   
   /**
    * Bank Country member array.
    */
   private String[] _BankCntry = null;
   
   /**
    * Bank Postal Code member array.
    */
   private String[] _BankPstl = null;
   
   /**
    * Correspondent Bank Transit No member array.
    */
   private Integer[] _CorrespTransitNo = null;
   
   /**
    * Correspondent Bank Institution Name member array.
    */
   private String[] _CorrespInstName = null;
   
   /**
    * PAC/ SWP recid member array.
    */
   private Integer[] _PACSWPId = null;
   
   /**
    * Distribution Detl recid member array.
    */
   private Integer[] _DistribDetlRId = null;
   
   /**
    * Bank ID Number member array.
    */
   private String[] _BankIDNum = null;
   
   /**
    * Bank ID member array.
    */
   private Integer[] _BankID = null;
   
   /**
    * Shareholder Number member array.
    */
   private String[] _ShrNum = null;
   
   /**
    * Flag indicating if EFT info can be updated member array.
    */
   private Boolean[] _EFTMod = null;
   
   /**
    * Gross amount in Settlement Currency member array.
    */
   private String[] _GrossAmtSettleCurr = null;
   
   /**
    * Commission amount in Settlement Currency member array.
    */
   private String[] _CommSettleCurr = null;
   
   /**
    * Other Commission amount is Settlement Currency member array.
    */
   private String[] _Comm2SettleCurr = null;
   
   /**
    * Expected settlement type member array.
    */
   private String[] _ExpGNSettle = null;
   
   /**
    * Code Indicator member array.
    */
   private Integer[] _Indc = null;
   
   /**
    * Stop Redemption from Settlement member array.
    */
   private Boolean[] _StopRedSettle = null;
   
   /**
    * Fund WKN member array.
    */
   private String[] _FundWKN = null;
   
   /**
    * Fund ISIN member array.
    */
   private String[] _FundISIN = null;
   
   /**
    * Stores AcctID of the parent banking info member array.
    */
   private String[] _BnkAcctIDLink = null;
   
   /**
    * Flag that indicates if Paytype change from EFT to Chq is allowed member array.
    */
   private Boolean[] _EftToChqAllowed = null;
   
   /**
    * PymtRoutingMthd member array.
    */
   private String[] _PymtRoutingMthd = null;
   
   /**
    * Payment Generate flag member array.
    */
   private Boolean[] _PymtGen = null;
   

   /**
    * Constructs the SettlSrchView object.
    * 
    */
   public SettlSrchView()
   {
      super ( new SettlSrchRequest() );
   }

   /**
    * Constructs the SettlSrchView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SettlSrchView( String hostEncoding )
   {
      super ( new SettlSrchRequest( hostEncoding ) );
   }

   /**
    * Gets the SettlSrchRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SettlSrchRequest object.
    */
   public final SettlSrchRequest getRequest()
   {
      return (SettlSrchRequest)getIFastRequest();
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
    * Gets the Company Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Company Code or null.
    */
   public final String getrxCompCode( int index )
   {
      return _rxCompCode[index];
   }
    
   /**
    * Gets the Company Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Company Code or the specified default value.
    */
   public final String getrxCompCode( int index, String defaultValue )
   {
      return _rxCompCode[index] == null ? defaultValue : _rxCompCode[index];
   }
    
   /**
    * Gets the array of Company Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Company Code values.
    */
   public final String[] getrxCompCodeArray()
   {
      return _rxCompCode;
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getrxAcctNumber( int index )
   {
      return _rxAcctNumber[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getrxAcctNumber( int index, String defaultValue )
   {
      return _rxAcctNumber[index] == null ? defaultValue : _rxAcctNumber[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getrxAcctNumberArray()
   {
      return _rxAcctNumber;
   }
    
   /**
    * Gets the Wire Order Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Wire Order Number or null.
    */
   public final String getrxWireOrdNum( int index )
   {
      return _rxWireOrdNum[index];
   }
    
   /**
    * Gets the Wire Order Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wire Order Number or the specified default value.
    */
   public final String getrxWireOrdNum( int index, String defaultValue )
   {
      return _rxWireOrdNum[index] == null ? defaultValue : _rxWireOrdNum[index];
   }
    
   /**
    * Gets the array of Wire Order Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Wire Order Number values.
    */
   public final String[] getrxWireOrdNumArray()
   {
      return _rxWireOrdNum;
   }
    
   /**
    * Gets the Transaction Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Number or null.
    */
   public final Integer getrxTransNum( int index )
   {
      return _rxTransNum[index];
   }
    
   /**
    * Gets the Transaction Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Number or the specified default value.
    */
   public final int getrxTransNum( int index, int defaultValue )
   {
      return _rxTransNum[index] == null ? defaultValue : _rxTransNum[index].intValue();
   }
    
   /**
    * Gets the array of Transaction Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Number values.
    */
   public final Integer[] getrxTransNumArray()
   {
      return _rxTransNum;
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
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Gross Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross Amount or null.
    */
   public final String getGrossAmt( int index )
   {
      return _GrossAmt[index];
   }
    
   /**
    * Gets the Gross Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross Amount or the specified default value.
    */
   public final String getGrossAmt( int index, String defaultValue )
   {
      return _GrossAmt[index] == null ? defaultValue : _GrossAmt[index];
   }
    
   /**
    * Gets the array of Gross Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross Amount values.
    */
   public final String[] getGrossAmtArray()
   {
      return _GrossAmt;
   }
    
   /**
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction ID or null.
    */
   public final String getTransID( int index )
   {
      return _TransID[index];
   }
    
   /**
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction ID or the specified default value.
    */
   public final String getTransID( int index, String defaultValue )
   {
      return _TransID[index] == null ? defaultValue : _TransID[index];
   }
    
   /**
    * Gets the array of Transaction ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction ID values.
    */
   public final String[] getTransIDArray()
   {
      return _TransID;
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type or null.
    */
   public final String getrxTransType( int index )
   {
      return _rxTransType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getrxTransType( int index, String defaultValue )
   {
      return _rxTransType[index] == null ? defaultValue : _rxTransType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
    */
   public final String[] getrxTransTypeArray()
   {
      return _rxTransType;
   }
    
   /**
    * Gets the Trade Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Date or null.
    */
   public final Date getrxTradeDate( int index )
   {
      return _rxTradeDate[index];
   }
    
   /**
    * Gets the Trade Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Date or the specified default value.
    */
   public final Date getrxTradeDate( int index, Date defaultValue )
   {
      return _rxTradeDate[index] == null ? defaultValue : _rxTradeDate[index];
   }
    
   /**
    * Gets the array of Trade Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Date values.
    */
   public final Date[] getrxTradeDateArray()
   {
      return _rxTradeDate;
   }
    
   /**
    * Gets the Value Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Value Date or null.
    */
   public final Date getrxValueDate( int index )
   {
      return _rxValueDate[index];
   }
    
   /**
    * Gets the Value Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Value Date or the specified default value.
    */
   public final Date getrxValueDate( int index, Date defaultValue )
   {
      return _rxValueDate[index] == null ? defaultValue : _rxValueDate[index];
   }
    
   /**
    * Gets the array of Value Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Value Date values.
    */
   public final Date[] getrxValueDateArray()
   {
      return _rxValueDate;
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Code or null.
    */
   public final String getrxBrokerCode( int index )
   {
      return _rxBrokerCode[index];
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Code or the specified default value.
    */
   public final String getrxBrokerCode( int index, String defaultValue )
   {
      return _rxBrokerCode[index] == null ? defaultValue : _rxBrokerCode[index];
   }
    
   /**
    * Gets the array of Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Code values.
    */
   public final String[] getrxBrokerCodeArray()
   {
      return _rxBrokerCode;
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
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep Code or null.
    */
   public final String getSlsRepCode( int index )
   {
      return _SlsRepCode[index];
   }
    
   /**
    * Gets the Sales Rep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep Code or the specified default value.
    */
   public final String getSlsRepCode( int index, String defaultValue )
   {
      return _SlsRepCode[index] == null ? defaultValue : _SlsRepCode[index];
   }
    
   /**
    * Gets the array of Sales Rep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep Code values.
    */
   public final String[] getSlsRepCodeArray()
   {
      return _SlsRepCode;
   }
    
   /**
    * Gets the Settle Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settle Currency or null.
    */
   public final String getrxSettlCurr( int index )
   {
      return _rxSettlCurr[index];
   }
    
   /**
    * Gets the Settle Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settle Currency or the specified default value.
    */
   public final String getrxSettlCurr( int index, String defaultValue )
   {
      return _rxSettlCurr[index] == null ? defaultValue : _rxSettlCurr[index];
   }
    
   /**
    * Gets the array of Settle Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settle Currency values.
    */
   public final String[] getrxSettlCurrArray()
   {
      return _rxSettlCurr;
   }
    
   /**
    * Gets the Gross/Net/Split settlement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross/Net/Split settlement or null.
    */
   public final String getGNSettle( int index )
   {
      return _GNSettle[index];
   }
    
   /**
    * Gets the Gross/Net/Split settlement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross/Net/Split settlement or the specified default value.
    */
   public final String getGNSettle( int index, String defaultValue )
   {
      return _GNSettle[index] == null ? defaultValue : _GNSettle[index];
   }
    
   /**
    * Gets the array of Gross/Net/Split settlement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross/Net/Split settlement values.
    */
   public final String[] getGNSettleArray()
   {
      return _GNSettle;
   }
    
   /**
    * Gets the Trans Detl Recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trans Detl Recid or null.
    */
   public final Integer getTransDetlRid( int index )
   {
      return _TransDetlRid[index];
   }
    
   /**
    * Gets the Trans Detl Recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trans Detl Recid or the specified default value.
    */
   public final int getTransDetlRid( int index, int defaultValue )
   {
      return _TransDetlRid[index] == null ? defaultValue : _TransDetlRid[index].intValue();
   }
    
   /**
    * Gets the array of Trans Detl Recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trans Detl Recid values.
    */
   public final Integer[] getTransDetlRidArray()
   {
      return _TransDetlRid;
   }
    
   /**
    * Gets the Commission field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission or null.
    */
   public final String getCommission( int index )
   {
      return _Commission[index];
   }
    
   /**
    * Gets the Commission field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission or the specified default value.
    */
   public final String getCommission( int index, String defaultValue )
   {
      return _Commission[index] == null ? defaultValue : _Commission[index];
   }
    
   /**
    * Gets the array of Commission fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission values.
    */
   public final String[] getCommissionArray()
   {
      return _Commission;
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the Payee Name 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Name 1 or null.
    */
   public final String getName1( int index )
   {
      return _Name1[index];
   }
    
   /**
    * Gets the Payee Name 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Name 1 or the specified default value.
    */
   public final String getName1( int index, String defaultValue )
   {
      return _Name1[index] == null ? defaultValue : _Name1[index];
   }
    
   /**
    * Gets the array of Payee Name 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Name 1 values.
    */
   public final String[] getName1Array()
   {
      return _Name1;
   }
    
   /**
    * Gets the Payee Name 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Name 2 or null.
    */
   public final String getName2( int index )
   {
      return _Name2[index];
   }
    
   /**
    * Gets the Payee Name 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Name 2 or the specified default value.
    */
   public final String getName2( int index, String defaultValue )
   {
      return _Name2[index] == null ? defaultValue : _Name2[index];
   }
    
   /**
    * Gets the array of Payee Name 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Name 2 values.
    */
   public final String[] getName2Array()
   {
      return _Name2;
   }
    
   /**
    * Gets the Payee Address Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Address Line 1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Payee Address Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Address Line 1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Payee Address Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Address Line 1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Payee Address Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Address Line 2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Payee Address Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Address Line 2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Payee Address Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Address Line 2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Payee Address Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Address Line 3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Payee Address Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Address Line 3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Payee Address Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Address Line 3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Payee Address Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Address Line 4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Payee Address Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Address Line 4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Payee Address Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Address Line 4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Payee Address Line 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Address Line 5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Payee Address Line 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Address Line 5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Payee Address Line 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Address Line 5 values.
    */
   public final String[] getAddrLine5Array()
   {
      return _AddrLine5;
   }
    
   /**
    * Gets the Payee Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Postal Code or null.
    */
   public final String getPostalCode( int index )
   {
      return _PostalCode[index];
   }
    
   /**
    * Gets the Payee Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Postal Code or the specified default value.
    */
   public final String getPostalCode( int index, String defaultValue )
   {
      return _PostalCode[index] == null ? defaultValue : _PostalCode[index];
   }
    
   /**
    * Gets the array of Payee Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Postal Code values.
    */
   public final String[] getPostalCodeArray()
   {
      return _PostalCode;
   }
    
   /**
    * Gets the Payee Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payee Country Code or null.
    */
   public final String getCountryCode( int index )
   {
      return _CountryCode[index];
   }
    
   /**
    * Gets the Payee Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payee Country Code or the specified default value.
    */
   public final String getCountryCode( int index, String defaultValue )
   {
      return _CountryCode[index] == null ? defaultValue : _CountryCode[index];
   }
    
   /**
    * Gets the array of Payee Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payee Country Code values.
    */
   public final String[] getCountryCodeArray()
   {
      return _CountryCode;
   }
    
   /**
    * Gets the Dist Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist Fee or null.
    */
   public final String getDistFee( int index )
   {
      return _DistFee[index];
   }
    
   /**
    * Gets the Dist Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist Fee or the specified default value.
    */
   public final String getDistFee( int index, String defaultValue )
   {
      return _DistFee[index] == null ? defaultValue : _DistFee[index];
   }
    
   /**
    * Gets the array of Dist Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist Fee values.
    */
   public final String[] getDistFeeArray()
   {
      return _DistFee;
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
    * Gets the Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Units or null.
    */
   public final String getUnits( int index )
   {
      return _Units[index];
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Units or the specified default value.
    */
   public final String getUnits( int index, String defaultValue )
   {
      return _Units[index] == null ? defaultValue : _Units[index];
   }
    
   /**
    * Gets the array of Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Units values.
    */
   public final String[] getUnitsArray()
   {
      return _Units;
   }
    
   /**
    * Gets the Acct Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct Value or null.
    */
   public final String getAcctValue( int index )
   {
      return _AcctValue[index];
   }
    
   /**
    * Gets the Acct Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct Value or the specified default value.
    */
   public final String getAcctValue( int index, String defaultValue )
   {
      return _AcctValue[index] == null ? defaultValue : _AcctValue[index];
   }
    
   /**
    * Gets the array of Acct Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct Value values.
    */
   public final String[] getAcctValueArray()
   {
      return _AcctValue;
   }
    
   /**
    * Gets the Price field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price or null.
    */
   public final String getPrice( int index )
   {
      return _Price[index];
   }
    
   /**
    * Gets the Price field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price or the specified default value.
    */
   public final String getPrice( int index, String defaultValue )
   {
      return _Price[index] == null ? defaultValue : _Price[index];
   }
    
   /**
    * Gets the array of Price fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price values.
    */
   public final String[] getPriceArray()
   {
      return _Price;
   }
    
   /**
    * Gets the Net Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Amount or null.
    */
   public final String getNetAmt( int index )
   {
      return _NetAmt[index];
   }
    
   /**
    * Gets the Net Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Amount or the specified default value.
    */
   public final String getNetAmt( int index, String defaultValue )
   {
      return _NetAmt[index] == null ? defaultValue : _NetAmt[index];
   }
    
   /**
    * Gets the array of Net Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Amount values.
    */
   public final String[] getNetAmtArray()
   {
      return _NetAmt;
   }
    
   /**
    * Gets the Pay Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Type or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the Pay Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Type or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of Pay Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Type values.
    */
   public final String[] getPayTypeArray()
   {
      return _PayType;
   }
    
   /**
    * Gets the Pay Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Method or null.
    */
   public final String getPayMethod( int index )
   {
      return _PayMethod[index];
   }
    
   /**
    * Gets the Pay Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Method or the specified default value.
    */
   public final String getPayMethod( int index, String defaultValue )
   {
      return _PayMethod[index] == null ? defaultValue : _PayMethod[index];
   }
    
   /**
    * Gets the array of Pay Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Method values.
    */
   public final String[] getPayMethodArray()
   {
      return _PayMethod;
   }
    
   /**
    * Gets the Alternate Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Alternate Account or null.
    */
   public final String getAltAccount( int index )
   {
      return _AltAccount[index];
   }
    
   /**
    * Gets the Alternate Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alternate Account or the specified default value.
    */
   public final String getAltAccount( int index, String defaultValue )
   {
      return _AltAccount[index] == null ? defaultValue : _AltAccount[index];
   }
    
   /**
    * Gets the array of Alternate Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Alternate Account values.
    */
   public final String[] getAltAccountArray()
   {
      return _AltAccount;
   }
    
   /**
    * Gets the Settle Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settle Date or null.
    */
   public final Date getrxSettleDate( int index )
   {
      return _rxSettleDate[index];
   }
    
   /**
    * Gets the Settle Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settle Date or the specified default value.
    */
   public final Date getrxSettleDate( int index, Date defaultValue )
   {
      return _rxSettleDate[index] == null ? defaultValue : _rxSettleDate[index];
   }
    
   /**
    * Gets the array of Settle Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settle Date values.
    */
   public final Date[] getrxSettleDateArray()
   {
      return _rxSettleDate;
   }
    
   /**
    * Gets the Commission 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission 2 or null.
    */
   public final String getCommission2( int index )
   {
      return _Commission2[index];
   }
    
   /**
    * Gets the Commission 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission 2 or the specified default value.
    */
   public final String getCommission2( int index, String defaultValue )
   {
      return _Commission2[index] == null ? defaultValue : _Commission2[index];
   }
    
   /**
    * Gets the array of Commission 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission 2 values.
    */
   public final String[] getCommission2Array()
   {
      return _Commission2;
   }
    
   /**
    * Gets the Original Order Source field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Original Order Source or null.
    */
   public final String getOrigOrderSource( int index )
   {
      return _OrigOrderSource[index];
   }
    
   /**
    * Gets the Original Order Source field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original Order Source or the specified default value.
    */
   public final String getOrigOrderSource( int index, String defaultValue )
   {
      return _OrigOrderSource[index] == null ? defaultValue : _OrigOrderSource[index];
   }
    
   /**
    * Gets the array of Original Order Source fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Original Order Source values.
    */
   public final String[] getOrigOrderSourceArray()
   {
      return _OrigOrderSource;
   }
    
   /**
    * Gets the Original Settle Source field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Original Settle Source or null.
    */
   public final String getOrigSettleSource( int index )
   {
      return _OrigSettleSource[index];
   }
    
   /**
    * Gets the Original Settle Source field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original Settle Source or the specified default value.
    */
   public final String getOrigSettleSource( int index, String defaultValue )
   {
      return _OrigSettleSource[index] == null ? defaultValue : _OrigSettleSource[index];
   }
    
   /**
    * Gets the array of Original Settle Source fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Original Settle Source values.
    */
   public final String[] getOrigSettleSourceArray()
   {
      return _OrigSettleSource;
   }
    
   /**
    * Gets the Original Settlement Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Original Settlement Type or null.
    */
   public final String getOrigSettleType( int index )
   {
      return _OrigSettleType[index];
   }
    
   /**
    * Gets the Original Settlement Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Original Settlement Type or the specified default value.
    */
   public final String getOrigSettleType( int index, String defaultValue )
   {
      return _OrigSettleType[index] == null ? defaultValue : _OrigSettleType[index];
   }
    
   /**
    * Gets the array of Original Settlement Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Original Settlement Type values.
    */
   public final String[] getOrigSettleTypeArray()
   {
      return _OrigSettleType;
   }
    
   /**
    * Gets the Bank Charge field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Charge or null.
    */
   public final String getBankCharge( int index )
   {
      return _BankCharge[index];
   }
    
   /**
    * Gets the Bank Charge field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Charge or the specified default value.
    */
   public final String getBankCharge( int index, String defaultValue )
   {
      return _BankCharge[index] == null ? defaultValue : _BankCharge[index];
   }
    
   /**
    * Gets the array of Bank Charge fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Charge values.
    */
   public final String[] getBankChargeArray()
   {
      return _BankCharge;
   }
    
   /**
    * Gets the Delivery Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Delivery Method or null.
    */
   public final String getDeliveryMethod( int index )
   {
      return _DeliveryMethod[index];
   }
    
   /**
    * Gets the Delivery Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Delivery Method or the specified default value.
    */
   public final String getDeliveryMethod( int index, String defaultValue )
   {
      return _DeliveryMethod[index] == null ? defaultValue : _DeliveryMethod[index];
   }
    
   /**
    * Gets the array of Delivery Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Delivery Method values.
    */
   public final String[] getDeliveryMethodArray()
   {
      return _DeliveryMethod;
   }
    
   /**
    * Gets the Volume Settlement Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Volume Settlement Type or null.
    */
   public final String getVolSettleType( int index )
   {
      return _VolSettleType[index];
   }
    
   /**
    * Gets the Volume Settlement Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Volume Settlement Type or the specified default value.
    */
   public final String getVolSettleType( int index, String defaultValue )
   {
      return _VolSettleType[index] == null ? defaultValue : _VolSettleType[index];
   }
    
   /**
    * Gets the array of Volume Settlement Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Volume Settlement Type values.
    */
   public final String[] getVolSettleTypeArray()
   {
      return _VolSettleType;
   }
    
   /**
    * Gets the Settlement Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settlement Method or null.
    */
   public final Integer getSettleMethod( int index )
   {
      return _SettleMethod[index];
   }
    
   /**
    * Gets the Settlement Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settlement Method or the specified default value.
    */
   public final int getSettleMethod( int index, int defaultValue )
   {
      return _SettleMethod[index] == null ? defaultValue : _SettleMethod[index].intValue();
   }
    
   /**
    * Gets the array of Settlement Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settlement Method values.
    */
   public final Integer[] getSettleMethodArray()
   {
      return _SettleMethod;
   }
    
   /**
    * Gets the Cheque Suppress Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cheque Suppress Code or null.
    */
   public final String getSuppressCode( int index )
   {
      return _SuppressCode[index];
   }
    
   /**
    * Gets the Cheque Suppress Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cheque Suppress Code or the specified default value.
    */
   public final String getSuppressCode( int index, String defaultValue )
   {
      return _SuppressCode[index] == null ? defaultValue : _SuppressCode[index];
   }
    
   /**
    * Gets the array of Cheque Suppress Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cheque Suppress Code values.
    */
   public final String[] getSuppressCodeArray()
   {
      return _SuppressCode;
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
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Name or null.
    */
   public final String getBatchName( int index )
   {
      return _BatchName[index];
   }
    
   /**
    * Gets the Batch Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Name or the specified default value.
    */
   public final String getBatchName( int index, String defaultValue )
   {
      return _BatchName[index] == null ? defaultValue : _BatchName[index];
   }
    
   /**
    * Gets the array of Batch Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Name values.
    */
   public final String[] getBatchNameArray()
   {
      return _BatchName;
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
    * Gets the Swift Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Swift Code or null.
    */
   public final Integer getSwiftCode( int index )
   {
      return _SwiftCode[index];
   }
    
   /**
    * Gets the Swift Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Swift Code or the specified default value.
    */
   public final int getSwiftCode( int index, int defaultValue )
   {
      return _SwiftCode[index] == null ? defaultValue : _SwiftCode[index].intValue();
   }
    
   /**
    * Gets the array of Swift Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Swift Code values.
    */
   public final Integer[] getSwiftCodeArray()
   {
      return _SwiftCode;
   }
    
   /**
    * Gets the Reference Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reference Number or null.
    */
   public final Integer getRefNumber( int index )
   {
      return _RefNumber[index];
   }
    
   /**
    * Gets the Reference Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Number or the specified default value.
    */
   public final int getRefNumber( int index, int defaultValue )
   {
      return _RefNumber[index] == null ? defaultValue : _RefNumber[index].intValue();
   }
    
   /**
    * Gets the array of Reference Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reference Number values.
    */
   public final Integer[] getRefNumberArray()
   {
      return _RefNumber;
   }
    
   /**
    * Gets the Transit Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transit Number or null.
    */
   public final Integer getTransitNo( int index )
   {
      return _TransitNo[index];
   }
    
   /**
    * Gets the Transit Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transit Number or the specified default value.
    */
   public final int getTransitNo( int index, int defaultValue )
   {
      return _TransitNo[index] == null ? defaultValue : _TransitNo[index].intValue();
   }
    
   /**
    * Gets the array of Transit Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transit Number values.
    */
   public final Integer[] getTransitNoArray()
   {
      return _TransitNo;
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
    * Gets the Bank Account Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Type or null.
    */
   public final String getBankAcctType( int index )
   {
      return _BankAcctType[index];
   }
    
   /**
    * Gets the Bank Account Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Type or the specified default value.
    */
   public final String getBankAcctType( int index, String defaultValue )
   {
      return _BankAcctType[index] == null ? defaultValue : _BankAcctType[index];
   }
    
   /**
    * Gets the array of Bank Account Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Type values.
    */
   public final String[] getBankAcctTypeArray()
   {
      return _BankAcctType;
   }
    
   /**
    * Gets the Bank Account Type Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Type Desc or null.
    */
   public final String getBankAcctTypeDesc( int index )
   {
      return _BankAcctTypeDesc[index];
   }
    
   /**
    * Gets the Bank Account Type Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Type Desc or the specified default value.
    */
   public final String getBankAcctTypeDesc( int index, String defaultValue )
   {
      return _BankAcctTypeDesc[index] == null ? defaultValue : _BankAcctTypeDesc[index];
   }
    
   /**
    * Gets the array of Bank Account Type Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Type Desc values.
    */
   public final String[] getBankAcctTypeDescArray()
   {
      return _BankAcctTypeDesc;
   }
    
   /**
    * Gets the Bank Account Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Currency or null.
    */
   public final String getBankAcctCurrency( int index )
   {
      return _BankAcctCurrency[index];
   }
    
   /**
    * Gets the Bank Account Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Currency or the specified default value.
    */
   public final String getBankAcctCurrency( int index, String defaultValue )
   {
      return _BankAcctCurrency[index] == null ? defaultValue : _BankAcctCurrency[index];
   }
    
   /**
    * Gets the array of Bank Account Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Currency values.
    */
   public final String[] getBankAcctCurrencyArray()
   {
      return _BankAcctCurrency;
   }
    
   /**
    * Gets the Bank Account Currency Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Account Currency Desc or null.
    */
   public final String getBankAcctCurrDesc( int index )
   {
      return _BankAcctCurrDesc[index];
   }
    
   /**
    * Gets the Bank Account Currency Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Account Currency Desc or the specified default value.
    */
   public final String getBankAcctCurrDesc( int index, String defaultValue )
   {
      return _BankAcctCurrDesc[index] == null ? defaultValue : _BankAcctCurrDesc[index];
   }
    
   /**
    * Gets the array of Bank Account Currency Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Account Currency Desc values.
    */
   public final String[] getBankAcctCurrDescArray()
   {
      return _BankAcctCurrDesc;
   }
    
   /**
    * Gets the Pay Reason line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason line 1 or null.
    */
   public final String getPayReason1( int index )
   {
      return _PayReason1[index];
   }
    
   /**
    * Gets the Pay Reason line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason line 1 or the specified default value.
    */
   public final String getPayReason1( int index, String defaultValue )
   {
      return _PayReason1[index] == null ? defaultValue : _PayReason1[index];
   }
    
   /**
    * Gets the array of Pay Reason line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason line 1 values.
    */
   public final String[] getPayReason1Array()
   {
      return _PayReason1;
   }
    
   /**
    * Gets the Pay Reason line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Reason line 2 or null.
    */
   public final String getPayReason2( int index )
   {
      return _PayReason2[index];
   }
    
   /**
    * Gets the Pay Reason line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Reason line 2 or the specified default value.
    */
   public final String getPayReason2( int index, String defaultValue )
   {
      return _PayReason2[index] == null ? defaultValue : _PayReason2[index];
   }
    
   /**
    * Gets the array of Pay Reason line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Reason line 2 values.
    */
   public final String[] getPayReason2Array()
   {
      return _PayReason2;
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
    * Gets the Correspondent Bank Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Type or null.
    */
   public final String getCorrespBankType( int index )
   {
      return _CorrespBankType[index];
   }
    
   /**
    * Gets the Correspondent Bank Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Type or the specified default value.
    */
   public final String getCorrespBankType( int index, String defaultValue )
   {
      return _CorrespBankType[index] == null ? defaultValue : _CorrespBankType[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Type values.
    */
   public final String[] getCorrespBankTypeArray()
   {
      return _CorrespBankType;
   }
    
   /**
    * Gets the Correspondent Bank ID Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank ID Number or null.
    */
   public final String getCorrespBankIDNum( int index )
   {
      return _CorrespBankIDNum[index];
   }
    
   /**
    * Gets the Correspondent Bank ID Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank ID Number or the specified default value.
    */
   public final String getCorrespBankIDNum( int index, String defaultValue )
   {
      return _CorrespBankIDNum[index] == null ? defaultValue : _CorrespBankIDNum[index];
   }
    
   /**
    * Gets the array of Correspondent Bank ID Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank ID Number values.
    */
   public final String[] getCorrespBankIDNumArray()
   {
      return _CorrespBankIDNum;
   }
    
   /**
    * Gets the Credit Info Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Credit Info Line 1 or null.
    */
   public final String getCreditInfoLine1( int index )
   {
      return _CreditInfoLine1[index];
   }
    
   /**
    * Gets the Credit Info Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line 1 or the specified default value.
    */
   public final String getCreditInfoLine1( int index, String defaultValue )
   {
      return _CreditInfoLine1[index] == null ? defaultValue : _CreditInfoLine1[index];
   }
    
   /**
    * Gets the array of Credit Info Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Credit Info Line 1 values.
    */
   public final String[] getCreditInfoLine1Array()
   {
      return _CreditInfoLine1;
   }
    
   /**
    * Gets the Credit Info Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Credit Info Line 2 or null.
    */
   public final String getCreditInfoLine2( int index )
   {
      return _CreditInfoLine2[index];
   }
    
   /**
    * Gets the Credit Info Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Credit Info Line 2 or the specified default value.
    */
   public final String getCreditInfoLine2( int index, String defaultValue )
   {
      return _CreditInfoLine2[index] == null ? defaultValue : _CreditInfoLine2[index];
   }
    
   /**
    * Gets the array of Credit Info Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Credit Info Line 2 values.
    */
   public final String[] getCreditInfoLine2Array()
   {
      return _CreditInfoLine2;
   }
    
   /**
    * Gets the ACH Processor field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ACH Processor or null.
    */
   public final String getACHProcessor( int index )
   {
      return _ACHProcessor[index];
   }
    
   /**
    * Gets the ACH Processor field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ACH Processor or the specified default value.
    */
   public final String getACHProcessor( int index, String defaultValue )
   {
      return _ACHProcessor[index] == null ? defaultValue : _ACHProcessor[index];
   }
    
   /**
    * Gets the array of ACH Processor fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ACH Processor values.
    */
   public final String[] getACHProcessorArray()
   {
      return _ACHProcessor;
   }
    
   /**
    * Gets the Correspondent Bank Contact field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Contact or null.
    */
   public final String getCorrespBankContact( int index )
   {
      return _CorrespBankContact[index];
   }
    
   /**
    * Gets the Correspondent Bank Contact field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Contact or the specified default value.
    */
   public final String getCorrespBankContact( int index, String defaultValue )
   {
      return _CorrespBankContact[index] == null ? defaultValue : _CorrespBankContact[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Contact fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Contact values.
    */
   public final String[] getCorrespBankContactArray()
   {
      return _CorrespBankContact;
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
    * Gets the Correspondent Bank postal code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank postal code or null.
    */
   public final String getCorrespBankPstl( int index )
   {
      return _CorrespBankPstl[index];
   }
    
   /**
    * Gets the Correspondent Bank postal code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank postal code or the specified default value.
    */
   public final String getCorrespBankPstl( int index, String defaultValue )
   {
      return _CorrespBankPstl[index] == null ? defaultValue : _CorrespBankPstl[index];
   }
    
   /**
    * Gets the array of Correspondent Bank postal code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank postal code values.
    */
   public final String[] getCorrespBankPstlArray()
   {
      return _CorrespBankPstl;
   }
    
   /**
    * Gets the Correspondent Bank Address 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address 1 or null.
    */
   public final String getCorrespBankAddr1( int index )
   {
      return _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the Correspondent Bank Address 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address 1 or the specified default value.
    */
   public final String getCorrespBankAddr1( int index, String defaultValue )
   {
      return _CorrespBankAddr1[index] == null ? defaultValue : _CorrespBankAddr1[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address 1 values.
    */
   public final String[] getCorrespBankAddr1Array()
   {
      return _CorrespBankAddr1;
   }
    
   /**
    * Gets the Correspondent Bank Address 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address 2 or null.
    */
   public final String getCorrespBankAddr2( int index )
   {
      return _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the Correspondent Bank Address 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address 2 or the specified default value.
    */
   public final String getCorrespBankAddr2( int index, String defaultValue )
   {
      return _CorrespBankAddr2[index] == null ? defaultValue : _CorrespBankAddr2[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address 2 values.
    */
   public final String[] getCorrespBankAddr2Array()
   {
      return _CorrespBankAddr2;
   }
    
   /**
    * Gets the Correspondent Bank Address 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address 3 or null.
    */
   public final String getCorrespBankAddr3( int index )
   {
      return _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the Correspondent Bank Address 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address 3 or the specified default value.
    */
   public final String getCorrespBankAddr3( int index, String defaultValue )
   {
      return _CorrespBankAddr3[index] == null ? defaultValue : _CorrespBankAddr3[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address 3 values.
    */
   public final String[] getCorrespBankAddr3Array()
   {
      return _CorrespBankAddr3;
   }
    
   /**
    * Gets the Correspondent Bank Address 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address 4 or null.
    */
   public final String getCorrespBankAddr4( int index )
   {
      return _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the Correspondent Bank Address 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address 4 or the specified default value.
    */
   public final String getCorrespBankAddr4( int index, String defaultValue )
   {
      return _CorrespBankAddr4[index] == null ? defaultValue : _CorrespBankAddr4[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address 4 values.
    */
   public final String[] getCorrespBankAddr4Array()
   {
      return _CorrespBankAddr4;
   }
    
   /**
    * Gets the Correspondent Bank Address 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Address 5 or null.
    */
   public final String getCorrespBankAddr5( int index )
   {
      return _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the Correspondent Bank Address 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Address 5 or the specified default value.
    */
   public final String getCorrespBankAddr5( int index, String defaultValue )
   {
      return _CorrespBankAddr5[index] == null ? defaultValue : _CorrespBankAddr5[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Address 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Address 5 values.
    */
   public final String[] getCorrespBankAddr5Array()
   {
      return _CorrespBankAddr5;
   }
    
   /**
    * Gets the Bank Address 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 1 or null.
    */
   public final String getBankAddr1( int index )
   {
      return _BankAddr1[index];
   }
    
   /**
    * Gets the Bank Address 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 1 or the specified default value.
    */
   public final String getBankAddr1( int index, String defaultValue )
   {
      return _BankAddr1[index] == null ? defaultValue : _BankAddr1[index];
   }
    
   /**
    * Gets the array of Bank Address 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 1 values.
    */
   public final String[] getBankAddr1Array()
   {
      return _BankAddr1;
   }
    
   /**
    * Gets the Bank Address 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 2 or null.
    */
   public final String getBankAddr2( int index )
   {
      return _BankAddr2[index];
   }
    
   /**
    * Gets the Bank Address 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 2 or the specified default value.
    */
   public final String getBankAddr2( int index, String defaultValue )
   {
      return _BankAddr2[index] == null ? defaultValue : _BankAddr2[index];
   }
    
   /**
    * Gets the array of Bank Address 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 2 values.
    */
   public final String[] getBankAddr2Array()
   {
      return _BankAddr2;
   }
    
   /**
    * Gets the Bank Address 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 3 or null.
    */
   public final String getBankAddr3( int index )
   {
      return _BankAddr3[index];
   }
    
   /**
    * Gets the Bank Address 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 3 or the specified default value.
    */
   public final String getBankAddr3( int index, String defaultValue )
   {
      return _BankAddr3[index] == null ? defaultValue : _BankAddr3[index];
   }
    
   /**
    * Gets the array of Bank Address 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 3 values.
    */
   public final String[] getBankAddr3Array()
   {
      return _BankAddr3;
   }
    
   /**
    * Gets the Bank Address 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 4 or null.
    */
   public final String getBankAddr4( int index )
   {
      return _BankAddr4[index];
   }
    
   /**
    * Gets the Bank Address 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 4 or the specified default value.
    */
   public final String getBankAddr4( int index, String defaultValue )
   {
      return _BankAddr4[index] == null ? defaultValue : _BankAddr4[index];
   }
    
   /**
    * Gets the array of Bank Address 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 4 values.
    */
   public final String[] getBankAddr4Array()
   {
      return _BankAddr4;
   }
    
   /**
    * Gets the Bank Address 5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Address 5 or null.
    */
   public final String getBankAddr5( int index )
   {
      return _BankAddr5[index];
   }
    
   /**
    * Gets the Bank Address 5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Address 5 or the specified default value.
    */
   public final String getBankAddr5( int index, String defaultValue )
   {
      return _BankAddr5[index] == null ? defaultValue : _BankAddr5[index];
   }
    
   /**
    * Gets the array of Bank Address 5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Address 5 values.
    */
   public final String[] getBankAddr5Array()
   {
      return _BankAddr5;
   }
    
   /**
    * Gets the Bank Contact field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Contact or null.
    */
   public final String getBankContact( int index )
   {
      return _BankContact[index];
   }
    
   /**
    * Gets the Bank Contact field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Contact or the specified default value.
    */
   public final String getBankContact( int index, String defaultValue )
   {
      return _BankContact[index] == null ? defaultValue : _BankContact[index];
   }
    
   /**
    * Gets the array of Bank Contact fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Contact values.
    */
   public final String[] getBankContactArray()
   {
      return _BankContact;
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
    * Gets the Bank Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Postal Code or null.
    */
   public final String getBankPstl( int index )
   {
      return _BankPstl[index];
   }
    
   /**
    * Gets the Bank Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Postal Code or the specified default value.
    */
   public final String getBankPstl( int index, String defaultValue )
   {
      return _BankPstl[index] == null ? defaultValue : _BankPstl[index];
   }
    
   /**
    * Gets the array of Bank Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Postal Code values.
    */
   public final String[] getBankPstlArray()
   {
      return _BankPstl;
   }
    
   /**
    * Gets the Correspondent Bank Transit No field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Transit No or null.
    */
   public final Integer getCorrespTransitNo( int index )
   {
      return _CorrespTransitNo[index];
   }
    
   /**
    * Gets the Correspondent Bank Transit No field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Transit No or the specified default value.
    */
   public final int getCorrespTransitNo( int index, int defaultValue )
   {
      return _CorrespTransitNo[index] == null ? defaultValue : _CorrespTransitNo[index].intValue();
   }
    
   /**
    * Gets the array of Correspondent Bank Transit No fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Transit No values.
    */
   public final Integer[] getCorrespTransitNoArray()
   {
      return _CorrespTransitNo;
   }
    
   /**
    * Gets the Correspondent Bank Institution Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Correspondent Bank Institution Name or null.
    */
   public final String getCorrespInstName( int index )
   {
      return _CorrespInstName[index];
   }
    
   /**
    * Gets the Correspondent Bank Institution Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Correspondent Bank Institution Name or the specified default value.
    */
   public final String getCorrespInstName( int index, String defaultValue )
   {
      return _CorrespInstName[index] == null ? defaultValue : _CorrespInstName[index];
   }
    
   /**
    * Gets the array of Correspondent Bank Institution Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Correspondent Bank Institution Name values.
    */
   public final String[] getCorrespInstNameArray()
   {
      return _CorrespInstName;
   }
    
   /**
    * Gets the PAC/ SWP recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAC/ SWP recid or null.
    */
   public final Integer getPACSWPId( int index )
   {
      return _PACSWPId[index];
   }
    
   /**
    * Gets the PAC/ SWP recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC/ SWP recid or the specified default value.
    */
   public final int getPACSWPId( int index, int defaultValue )
   {
      return _PACSWPId[index] == null ? defaultValue : _PACSWPId[index].intValue();
   }
    
   /**
    * Gets the array of PAC/ SWP recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAC/ SWP recid values.
    */
   public final Integer[] getPACSWPIdArray()
   {
      return _PACSWPId;
   }
    
   /**
    * Gets the Distribution Detl recid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Distribution Detl recid or null.
    */
   public final Integer getDistribDetlRId( int index )
   {
      return _DistribDetlRId[index];
   }
    
   /**
    * Gets the Distribution Detl recid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Distribution Detl recid or the specified default value.
    */
   public final int getDistribDetlRId( int index, int defaultValue )
   {
      return _DistribDetlRId[index] == null ? defaultValue : _DistribDetlRId[index].intValue();
   }
    
   /**
    * Gets the array of Distribution Detl recid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Distribution Detl recid values.
    */
   public final Integer[] getDistribDetlRIdArray()
   {
      return _DistribDetlRId;
   }
    
   /**
    * Gets the Bank ID Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank ID Number or null.
    */
   public final String getBankIDNum( int index )
   {
      return _BankIDNum[index];
   }
    
   /**
    * Gets the Bank ID Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID Number or the specified default value.
    */
   public final String getBankIDNum( int index, String defaultValue )
   {
      return _BankIDNum[index] == null ? defaultValue : _BankIDNum[index];
   }
    
   /**
    * Gets the array of Bank ID Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank ID Number values.
    */
   public final String[] getBankIDNumArray()
   {
      return _BankIDNum;
   }
    
   /**
    * Gets the Bank ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank ID or null.
    */
   public final Integer getBankID( int index )
   {
      return _BankID[index];
   }
    
   /**
    * Gets the Bank ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank ID or the specified default value.
    */
   public final int getBankID( int index, int defaultValue )
   {
      return _BankID[index] == null ? defaultValue : _BankID[index].intValue();
   }
    
   /**
    * Gets the array of Bank ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank ID values.
    */
   public final Integer[] getBankIDArray()
   {
      return _BankID;
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
    * Gets the Flag indicating if EFT info can be updated field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if EFT info can be updated or null.
    */
   public final Boolean getEFTMod( int index )
   {
      return _EFTMod[index];
   }
    
   /**
    * Gets the Flag indicating if EFT info can be updated field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if EFT info can be updated or the specified default value.
    */
   public final boolean getEFTMod( int index, boolean defaultValue )
   {
      return _EFTMod[index] == null ? defaultValue : _EFTMod[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if EFT info can be updated fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if EFT info can be updated values.
    */
   public final Boolean[] getEFTModArray()
   {
      return _EFTMod;
   }
    
   /**
    * Gets the Gross amount in Settlement Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross amount in Settlement Currency or null.
    */
   public final String getGrossAmtSettleCurr( int index )
   {
      return _GrossAmtSettleCurr[index];
   }
    
   /**
    * Gets the Gross amount in Settlement Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross amount in Settlement Currency or the specified default value.
    */
   public final String getGrossAmtSettleCurr( int index, String defaultValue )
   {
      return _GrossAmtSettleCurr[index] == null ? defaultValue : _GrossAmtSettleCurr[index];
   }
    
   /**
    * Gets the array of Gross amount in Settlement Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross amount in Settlement Currency values.
    */
   public final String[] getGrossAmtSettleCurrArray()
   {
      return _GrossAmtSettleCurr;
   }
    
   /**
    * Gets the Commission amount in Settlement Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commission amount in Settlement Currency or null.
    */
   public final String getCommSettleCurr( int index )
   {
      return _CommSettleCurr[index];
   }
    
   /**
    * Gets the Commission amount in Settlement Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission amount in Settlement Currency or the specified default value.
    */
   public final String getCommSettleCurr( int index, String defaultValue )
   {
      return _CommSettleCurr[index] == null ? defaultValue : _CommSettleCurr[index];
   }
    
   /**
    * Gets the array of Commission amount in Settlement Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commission amount in Settlement Currency values.
    */
   public final String[] getCommSettleCurrArray()
   {
      return _CommSettleCurr;
   }
    
   /**
    * Gets the Other Commission amount is Settlement Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Other Commission amount is Settlement Currency or null.
    */
   public final String getComm2SettleCurr( int index )
   {
      return _Comm2SettleCurr[index];
   }
    
   /**
    * Gets the Other Commission amount is Settlement Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other Commission amount is Settlement Currency or the specified default value.
    */
   public final String getComm2SettleCurr( int index, String defaultValue )
   {
      return _Comm2SettleCurr[index] == null ? defaultValue : _Comm2SettleCurr[index];
   }
    
   /**
    * Gets the array of Other Commission amount is Settlement Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Other Commission amount is Settlement Currency values.
    */
   public final String[] getComm2SettleCurrArray()
   {
      return _Comm2SettleCurr;
   }
    
   /**
    * Gets the Expected settlement type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Expected settlement type or null.
    */
   public final String getExpGNSettle( int index )
   {
      return _ExpGNSettle[index];
   }
    
   /**
    * Gets the Expected settlement type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Expected settlement type or the specified default value.
    */
   public final String getExpGNSettle( int index, String defaultValue )
   {
      return _ExpGNSettle[index] == null ? defaultValue : _ExpGNSettle[index];
   }
    
   /**
    * Gets the array of Expected settlement type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Expected settlement type values.
    */
   public final String[] getExpGNSettleArray()
   {
      return _ExpGNSettle;
   }
    
   /**
    * Gets the Code Indicator field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Code Indicator or null.
    */
   public final Integer getIndc( int index )
   {
      return _Indc[index];
   }
    
   /**
    * Gets the Code Indicator field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Code Indicator or the specified default value.
    */
   public final int getIndc( int index, int defaultValue )
   {
      return _Indc[index] == null ? defaultValue : _Indc[index].intValue();
   }
    
   /**
    * Gets the array of Code Indicator fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Code Indicator values.
    */
   public final Integer[] getIndcArray()
   {
      return _Indc;
   }
    
   /**
    * Gets the Stop Redemption from Settlement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Redemption from Settlement or null.
    */
   public final Boolean getStopRedSettle( int index )
   {
      return _StopRedSettle[index];
   }
    
   /**
    * Gets the Stop Redemption from Settlement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Redemption from Settlement or the specified default value.
    */
   public final boolean getStopRedSettle( int index, boolean defaultValue )
   {
      return _StopRedSettle[index] == null ? defaultValue : _StopRedSettle[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Redemption from Settlement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Redemption from Settlement values.
    */
   public final Boolean[] getStopRedSettleArray()
   {
      return _StopRedSettle;
   }
    
   /**
    * Gets the Fund WKN field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund WKN or null.
    */
   public final String getFundWKN( int index )
   {
      return _FundWKN[index];
   }
    
   /**
    * Gets the Fund WKN field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund WKN or the specified default value.
    */
   public final String getFundWKN( int index, String defaultValue )
   {
      return _FundWKN[index] == null ? defaultValue : _FundWKN[index];
   }
    
   /**
    * Gets the array of Fund WKN fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund WKN values.
    */
   public final String[] getFundWKNArray()
   {
      return _FundWKN;
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
    * Gets the Stores AcctID of the parent banking info field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stores AcctID of the parent banking info or null.
    */
   public final String getBnkAcctIDLink( int index )
   {
      return _BnkAcctIDLink[index];
   }
    
   /**
    * Gets the Stores AcctID of the parent banking info field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stores AcctID of the parent banking info or the specified default value.
    */
   public final String getBnkAcctIDLink( int index, String defaultValue )
   {
      return _BnkAcctIDLink[index] == null ? defaultValue : _BnkAcctIDLink[index];
   }
    
   /**
    * Gets the array of Stores AcctID of the parent banking info fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stores AcctID of the parent banking info values.
    */
   public final String[] getBnkAcctIDLinkArray()
   {
      return _BnkAcctIDLink;
   }
    
   /**
    * Gets the Flag that indicates if Paytype change from EFT to Chq is allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if Paytype change from EFT to Chq is allowed or null.
    */
   public final Boolean getEftToChqAllowed( int index )
   {
      return _EftToChqAllowed[index];
   }
    
   /**
    * Gets the Flag that indicates if Paytype change from EFT to Chq is allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if Paytype change from EFT to Chq is allowed or the specified default value.
    */
   public final boolean getEftToChqAllowed( int index, boolean defaultValue )
   {
      return _EftToChqAllowed[index] == null ? defaultValue : _EftToChqAllowed[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if Paytype change from EFT to Chq is allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if Paytype change from EFT to Chq is allowed values.
    */
   public final Boolean[] getEftToChqAllowedArray()
   {
      return _EftToChqAllowed;
   }
    
   /**
    * Gets the PymtRoutingMthd field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PymtRoutingMthd or null.
    */
   public final String getPymtRoutingMthd( int index )
   {
      return _PymtRoutingMthd[index];
   }
    
   /**
    * Gets the PymtRoutingMthd field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PymtRoutingMthd or the specified default value.
    */
   public final String getPymtRoutingMthd( int index, String defaultValue )
   {
      return _PymtRoutingMthd[index] == null ? defaultValue : _PymtRoutingMthd[index];
   }
    
   /**
    * Gets the array of PymtRoutingMthd fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PymtRoutingMthd values.
    */
   public final String[] getPymtRoutingMthdArray()
   {
      return _PymtRoutingMthd;
   }
    
   /**
    * Gets the Payment Generate flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Payment Generate flag or null.
    */
   public final Boolean getPymtGen( int index )
   {
      return _PymtGen[index];
   }
    
   /**
    * Gets the Payment Generate flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment Generate flag or the specified default value.
    */
   public final boolean getPymtGen( int index, boolean defaultValue )
   {
      return _PymtGen[index] == null ? defaultValue : _PymtGen[index].booleanValue();
   }
    
   /**
    * Gets the array of Payment Generate flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Payment Generate flag values.
    */
   public final Boolean[] getPymtGenArray()
   {
      return _PymtGen;
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
      
      _rxCompCode = resizeArray( _rxCompCode, _RepeatCount );
      _rxAcctNumber = resizeArray( _rxAcctNumber, _RepeatCount );
      _rxWireOrdNum = resizeArray( _rxWireOrdNum, _RepeatCount );
      _rxTransNum = resizeArray( _rxTransNum, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _GrossAmt = resizeArray( _GrossAmt, _RepeatCount );
      _TransID = resizeArray( _TransID, _RepeatCount );
      _rxTransType = resizeArray( _rxTransType, _RepeatCount );
      _rxTradeDate = resizeArray( _rxTradeDate, _RepeatCount );
      _rxValueDate = resizeArray( _rxValueDate, _RepeatCount );
      _rxBrokerCode = resizeArray( _rxBrokerCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _SlsRepCode = resizeArray( _SlsRepCode, _RepeatCount );
      _rxSettlCurr = resizeArray( _rxSettlCurr, _RepeatCount );
      _GNSettle = resizeArray( _GNSettle, _RepeatCount );
      _TransDetlRid = resizeArray( _TransDetlRid, _RepeatCount );
      _Commission = resizeArray( _Commission, _RepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _Name1 = resizeArray( _Name1, _RepeatCount );
      _Name2 = resizeArray( _Name2, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _CountryCode = resizeArray( _CountryCode, _RepeatCount );
      _DistFee = resizeArray( _DistFee, _RepeatCount );
      _Fee = resizeArray( _Fee, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _AcctValue = resizeArray( _AcctValue, _RepeatCount );
      _Price = resizeArray( _Price, _RepeatCount );
      _NetAmt = resizeArray( _NetAmt, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _PayMethod = resizeArray( _PayMethod, _RepeatCount );
      _AltAccount = resizeArray( _AltAccount, _RepeatCount );
      _rxSettleDate = resizeArray( _rxSettleDate, _RepeatCount );
      _Commission2 = resizeArray( _Commission2, _RepeatCount );
      _OrigOrderSource = resizeArray( _OrigOrderSource, _RepeatCount );
      _OrigSettleSource = resizeArray( _OrigSettleSource, _RepeatCount );
      _OrigSettleType = resizeArray( _OrigSettleType, _RepeatCount );
      _BankCharge = resizeArray( _BankCharge, _RepeatCount );
      _DeliveryMethod = resizeArray( _DeliveryMethod, _RepeatCount );
      _VolSettleType = resizeArray( _VolSettleType, _RepeatCount );
      _SettleMethod = resizeArray( _SettleMethod, _RepeatCount );
      _SuppressCode = resizeArray( _SuppressCode, _RepeatCount );
      _ExchRate = resizeArray( _ExchRate, _RepeatCount );
      _BatchName = resizeArray( _BatchName, _RepeatCount );
      _InstName = resizeArray( _InstName, _RepeatCount );
      _SwiftCode = resizeArray( _SwiftCode, _RepeatCount );
      _RefNumber = resizeArray( _RefNumber, _RepeatCount );
      _TransitNo = resizeArray( _TransitNo, _RepeatCount );
      _BankAcctNum = resizeArray( _BankAcctNum, _RepeatCount );
      _BankAcctName = resizeArray( _BankAcctName, _RepeatCount );
      _BankAcctType = resizeArray( _BankAcctType, _RepeatCount );
      _BankAcctTypeDesc = resizeArray( _BankAcctTypeDesc, _RepeatCount );
      _BankAcctCurrency = resizeArray( _BankAcctCurrency, _RepeatCount );
      _BankAcctCurrDesc = resizeArray( _BankAcctCurrDesc, _RepeatCount );
      _PayReason1 = resizeArray( _PayReason1, _RepeatCount );
      _PayReason2 = resizeArray( _PayReason2, _RepeatCount );
      _CorrespBankId = resizeArray( _CorrespBankId, _RepeatCount );
      _BankType = resizeArray( _BankType, _RepeatCount );
      _CorrespBankType = resizeArray( _CorrespBankType, _RepeatCount );
      _CorrespBankIDNum = resizeArray( _CorrespBankIDNum, _RepeatCount );
      _CreditInfoLine1 = resizeArray( _CreditInfoLine1, _RepeatCount );
      _CreditInfoLine2 = resizeArray( _CreditInfoLine2, _RepeatCount );
      _ACHProcessor = resizeArray( _ACHProcessor, _RepeatCount );
      _CorrespBankContact = resizeArray( _CorrespBankContact, _RepeatCount );
      _CorrespBankCntry = resizeArray( _CorrespBankCntry, _RepeatCount );
      _CorrespBankPstl = resizeArray( _CorrespBankPstl, _RepeatCount );
      _CorrespBankAddr1 = resizeArray( _CorrespBankAddr1, _RepeatCount );
      _CorrespBankAddr2 = resizeArray( _CorrespBankAddr2, _RepeatCount );
      _CorrespBankAddr3 = resizeArray( _CorrespBankAddr3, _RepeatCount );
      _CorrespBankAddr4 = resizeArray( _CorrespBankAddr4, _RepeatCount );
      _CorrespBankAddr5 = resizeArray( _CorrespBankAddr5, _RepeatCount );
      _BankAddr1 = resizeArray( _BankAddr1, _RepeatCount );
      _BankAddr2 = resizeArray( _BankAddr2, _RepeatCount );
      _BankAddr3 = resizeArray( _BankAddr3, _RepeatCount );
      _BankAddr4 = resizeArray( _BankAddr4, _RepeatCount );
      _BankAddr5 = resizeArray( _BankAddr5, _RepeatCount );
      _BankContact = resizeArray( _BankContact, _RepeatCount );
      _BankCntry = resizeArray( _BankCntry, _RepeatCount );
      _BankPstl = resizeArray( _BankPstl, _RepeatCount );
      _CorrespTransitNo = resizeArray( _CorrespTransitNo, _RepeatCount );
      _CorrespInstName = resizeArray( _CorrespInstName, _RepeatCount );
      _PACSWPId = resizeArray( _PACSWPId, _RepeatCount );
      _DistribDetlRId = resizeArray( _DistribDetlRId, _RepeatCount );
      _BankIDNum = resizeArray( _BankIDNum, _RepeatCount );
      _BankID = resizeArray( _BankID, _RepeatCount );
      _ShrNum = resizeArray( _ShrNum, _RepeatCount );
      _EFTMod = resizeArray( _EFTMod, _RepeatCount );
      _GrossAmtSettleCurr = resizeArray( _GrossAmtSettleCurr, _RepeatCount );
      _CommSettleCurr = resizeArray( _CommSettleCurr, _RepeatCount );
      _Comm2SettleCurr = resizeArray( _Comm2SettleCurr, _RepeatCount );
      _ExpGNSettle = resizeArray( _ExpGNSettle, _RepeatCount );
      _Indc = resizeArray( _Indc, _RepeatCount );
      _StopRedSettle = resizeArray( _StopRedSettle, _RepeatCount );
      _FundWKN = resizeArray( _FundWKN, _RepeatCount );
      _FundISIN = resizeArray( _FundISIN, _RepeatCount );
      _BnkAcctIDLink = resizeArray( _BnkAcctIDLink, _RepeatCount );
      _EftToChqAllowed = resizeArray( _EftToChqAllowed, _RepeatCount );
      _PymtRoutingMthd = resizeArray( _PymtRoutingMthd, _RepeatCount );
      _PymtGen = resizeArray( _PymtGen, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxCompCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAcctNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxWireOrdNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxTransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxTransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxTradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxValueDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _rxBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsRepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxSettlCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GNSettle[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransDetlRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Commission[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Name2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Fee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Price[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AltAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxSettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Commission2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrigOrderSource[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrigSettleSource[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrigSettleType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCharge[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DeliveryMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VolSettleType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleMethod[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SuppressCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SwiftCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RefNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctCurrDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayReason2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankIDNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreditInfoLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreditInfoLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ACHProcessor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankContact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespBankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankContact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCntry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankPstl[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CorrespTransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CorrespInstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PACSWPId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _DistribDetlRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankIDNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ShrNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EFTMod[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GrossAmtSettleCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommSettleCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Comm2SettleCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExpGNSettle[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Indc[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _StopRedSettle[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FundWKN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundISIN[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BnkAcctIDLink[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EftToChqAllowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PymtRoutingMthd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PymtGen[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
