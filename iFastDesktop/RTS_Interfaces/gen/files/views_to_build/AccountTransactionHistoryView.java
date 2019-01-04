
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account/fund transaction history view.
 * For additional view information see <A HREF="../../../../viewspecs/AccountTransactionHistory.doc">AccountTransactionHistory.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountTransactionHistoryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * TransId (Unique Transaction Identifier) member array.
    */
   private String[] _TransId = null;
   
   /**
    * Transaction Type member array.
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
    * TradeDate member array.
    */
   private Date[] _TradeDate = null;
   
   /**
    * SettleDate member array.
    */
   private Date[] _SettleDate = null;
   
   /**
    * BackedDateOn member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Settled member array.
    */
   private Boolean[] _Settled = null;
   
   /**
    * Gross Amount member array.
    */
   private String[] _GrossAmt = null;
   
   /**
    * Net Amount member array.
    */
   private String[] _NetAmt = null;
   
   /**
    * Unit Price member array.
    */
   private String[] _UnitPrice = null;
   
   /**
    * Units member array.
    */
   private String[] _Units = null;
   
   /**
    * Unit Balance member array.
    */
   private String[] _UnitBalance = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Cancelled member array.
    */
   private Boolean[] _Cancelled = null;
   
   /**
    * Reversal member array.
    */
   private Boolean[] _Reversal = null;
   
   /**
    * Pay Type member array.
    */
   private String[] _PayType = null;
   
   /**
    * Pay Type Description member array.
    */
   private String[] _PayTypeDesc = null;
   
   /**
    * OrderBatch member array.
    */
   private String[] _OrderBatch = null;
   
   /**
    * OrderTrace member array.
    */
   private Integer[] _OrderTrace = null;
   
   /**
    * OrderUser member array.
    */
   private String[] _OrderUser = null;
   
   /**
    * CancelBatch member array.
    */
   private String[] _CancelBatch = null;
   
   /**
    * CancelTrace member array.
    */
   private Integer[] _CancelTrace = null;
   
   /**
    * CancelUser member array.
    */
   private String[] _CancelUser = null;
   
   /**
    * SettleBatch member array.
    */
   private String[] _SettleBatch = null;
   
   /**
    * SettleTrace member array.
    */
   private Integer[] _SettleTrace = null;
   
   /**
    * SettleUser member array.
    */
   private String[] _SettleUser = null;
   
   /**
    * VerifiedBy member array.
    */
   private String[] _VerifiedBy = null;
   
   /**
    * Account To/From member array.
    */
   private String[] _TfrAcct = null;
   
   /**
    * Fund To/From member array.
    */
   private String[] _TfrFund = null;
   
   /**
    * Class To/From member array.
    */
   private String[] _TfrClass = null;
   
   /**
    * Settle Currency member array.
    */
   private String[] _SettleCurrency = null;
   
   /**
    * Amount member array.
    */
   private String[] _Amount = null;
   
   /**
    * Broker Code member array.
    */
   private String[] _BrokerCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = null;
   
   /**
    * SalesRepCode member array.
    */
   private String[] _SalesRepCode = null;
   
   /**
    * Offer Price member array.
    */
   private String[] _OfferPrice = null;
   
   /**
    * Acct Owner's First Name member array.
    */
   private String[] _FirstName = null;
   
   /**
    * Acct Owner's Last Name member array.
    */
   private String[] _LastName = null;
   
   /**
    * Settled Description member array.
    */
   private String[] _SettledDesc = null;
   
   /**
    * Sequence Number member array.
    */
   private Integer[] _SeqNum = null;
   
   /**
    * AMS Trade member array.
    */
   private Boolean[] _AMSTrade = null;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAccountNum = null;
   
   /**
    * Existing External Id member array.
    */
   private Boolean[] _ExistExternalId = null;
   
   /**
    * YES/NO - if message exists member array.
    */
   private Boolean[] _MessageExist = null;
   
   /**
    * Transaction Status member array.
    */
   private String[] _TransStatus = null;
   
   /**
    * Reporting Exchange Rate member array.
    */
   private String[] _ReportingExchRate = null;
   
   /**
    * Flag indicating if response from HRDC is pending member array.
    */
   private Boolean[] _HRDCRespPending = null;
   

   /**
    * Constructs the AccountTransactionHistoryView object.
    * 
    */
   public AccountTransactionHistoryView()
   {
      super ( new AccountTransactionHistoryRequest() );
   }

   /**
    * Constructs the AccountTransactionHistoryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccountTransactionHistoryView( String hostEncoding )
   {
      super ( new AccountTransactionHistoryRequest( hostEncoding ) );
   }

   /**
    * Gets the AccountTransactionHistoryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccountTransactionHistoryRequest object.
    */
   public final AccountTransactionHistoryRequest getRequest()
   {
      return (AccountTransactionHistoryRequest)getIFastRequest();
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
    * Gets the TransId (Unique Transaction Identifier) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransId (Unique Transaction Identifier) or null.
    */
   public final String getTransId( int index )
   {
      return _TransId[index];
   }
    
   /**
    * Gets the TransId (Unique Transaction Identifier) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransId (Unique Transaction Identifier) or the specified default value.
    */
   public final String getTransId( int index, String defaultValue )
   {
      return _TransId[index] == null ? defaultValue : _TransId[index];
   }
    
   /**
    * Gets the array of TransId (Unique Transaction Identifier) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransId (Unique Transaction Identifier) values.
    */
   public final String[] getTransIdArray()
   {
      return _TransId;
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type or null.
    */
   public final String getTransType( int index )
   {
      return _TransType[index];
   }
    
   /**
    * Gets the Transaction Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type or the specified default value.
    */
   public final String getTransType( int index, String defaultValue )
   {
      return _TransType[index] == null ? defaultValue : _TransType[index];
   }
    
   /**
    * Gets the array of Transaction Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type values.
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
    * Gets the BackedDateOn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BackedDateOn or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the BackedDateOn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BackedDateOn or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of BackedDateOn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BackedDateOn values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Settled field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settled or null.
    */
   public final Boolean getSettled( int index )
   {
      return _Settled[index];
   }
    
   /**
    * Gets the Settled field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled or the specified default value.
    */
   public final boolean getSettled( int index, boolean defaultValue )
   {
      return _Settled[index] == null ? defaultValue : _Settled[index].booleanValue();
   }
    
   /**
    * Gets the array of Settled fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled values.
    */
   public final Boolean[] getSettledArray()
   {
      return _Settled;
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
    * Gets the Unit Price field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Price or null.
    */
   public final String getUnitPrice( int index )
   {
      return _UnitPrice[index];
   }
    
   /**
    * Gets the Unit Price field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Price or the specified default value.
    */
   public final String getUnitPrice( int index, String defaultValue )
   {
      return _UnitPrice[index] == null ? defaultValue : _UnitPrice[index];
   }
    
   /**
    * Gets the array of Unit Price fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Price values.
    */
   public final String[] getUnitPriceArray()
   {
      return _UnitPrice;
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
    * Gets the Unit Balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Balance or null.
    */
   public final String getUnitBalance( int index )
   {
      return _UnitBalance[index];
   }
    
   /**
    * Gets the Unit Balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Balance or the specified default value.
    */
   public final String getUnitBalance( int index, String defaultValue )
   {
      return _UnitBalance[index] == null ? defaultValue : _UnitBalance[index];
   }
    
   /**
    * Gets the array of Unit Balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Balance values.
    */
   public final String[] getUnitBalanceArray()
   {
      return _UnitBalance;
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
    * Gets the Cancelled field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cancelled or null.
    */
   public final Boolean getCancelled( int index )
   {
      return _Cancelled[index];
   }
    
   /**
    * Gets the Cancelled field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cancelled or the specified default value.
    */
   public final boolean getCancelled( int index, boolean defaultValue )
   {
      return _Cancelled[index] == null ? defaultValue : _Cancelled[index].booleanValue();
   }
    
   /**
    * Gets the array of Cancelled fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cancelled values.
    */
   public final Boolean[] getCancelledArray()
   {
      return _Cancelled;
   }
    
   /**
    * Gets the Reversal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reversal or null.
    */
   public final Boolean getReversal( int index )
   {
      return _Reversal[index];
   }
    
   /**
    * Gets the Reversal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reversal or the specified default value.
    */
   public final boolean getReversal( int index, boolean defaultValue )
   {
      return _Reversal[index] == null ? defaultValue : _Reversal[index].booleanValue();
   }
    
   /**
    * Gets the array of Reversal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reversal values.
    */
   public final Boolean[] getReversalArray()
   {
      return _Reversal;
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
    * Gets the Pay Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Type Description or null.
    */
   public final String getPayTypeDesc( int index )
   {
      return _PayTypeDesc[index];
   }
    
   /**
    * Gets the Pay Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Type Description or the specified default value.
    */
   public final String getPayTypeDesc( int index, String defaultValue )
   {
      return _PayTypeDesc[index] == null ? defaultValue : _PayTypeDesc[index];
   }
    
   /**
    * Gets the array of Pay Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Type Description values.
    */
   public final String[] getPayTypeDescArray()
   {
      return _PayTypeDesc;
   }
    
   /**
    * Gets the OrderBatch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OrderBatch or null.
    */
   public final String getOrderBatch( int index )
   {
      return _OrderBatch[index];
   }
    
   /**
    * Gets the OrderBatch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OrderBatch or the specified default value.
    */
   public final String getOrderBatch( int index, String defaultValue )
   {
      return _OrderBatch[index] == null ? defaultValue : _OrderBatch[index];
   }
    
   /**
    * Gets the array of OrderBatch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OrderBatch values.
    */
   public final String[] getOrderBatchArray()
   {
      return _OrderBatch;
   }
    
   /**
    * Gets the OrderTrace field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OrderTrace or null.
    */
   public final Integer getOrderTrace( int index )
   {
      return _OrderTrace[index];
   }
    
   /**
    * Gets the OrderTrace field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OrderTrace or the specified default value.
    */
   public final int getOrderTrace( int index, int defaultValue )
   {
      return _OrderTrace[index] == null ? defaultValue : _OrderTrace[index].intValue();
   }
    
   /**
    * Gets the array of OrderTrace fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OrderTrace values.
    */
   public final Integer[] getOrderTraceArray()
   {
      return _OrderTrace;
   }
    
   /**
    * Gets the OrderUser field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the OrderUser or null.
    */
   public final String getOrderUser( int index )
   {
      return _OrderUser[index];
   }
    
   /**
    * Gets the OrderUser field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OrderUser or the specified default value.
    */
   public final String getOrderUser( int index, String defaultValue )
   {
      return _OrderUser[index] == null ? defaultValue : _OrderUser[index];
   }
    
   /**
    * Gets the array of OrderUser fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of OrderUser values.
    */
   public final String[] getOrderUserArray()
   {
      return _OrderUser;
   }
    
   /**
    * Gets the CancelBatch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CancelBatch or null.
    */
   public final String getCancelBatch( int index )
   {
      return _CancelBatch[index];
   }
    
   /**
    * Gets the CancelBatch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CancelBatch or the specified default value.
    */
   public final String getCancelBatch( int index, String defaultValue )
   {
      return _CancelBatch[index] == null ? defaultValue : _CancelBatch[index];
   }
    
   /**
    * Gets the array of CancelBatch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CancelBatch values.
    */
   public final String[] getCancelBatchArray()
   {
      return _CancelBatch;
   }
    
   /**
    * Gets the CancelTrace field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CancelTrace or null.
    */
   public final Integer getCancelTrace( int index )
   {
      return _CancelTrace[index];
   }
    
   /**
    * Gets the CancelTrace field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CancelTrace or the specified default value.
    */
   public final int getCancelTrace( int index, int defaultValue )
   {
      return _CancelTrace[index] == null ? defaultValue : _CancelTrace[index].intValue();
   }
    
   /**
    * Gets the array of CancelTrace fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CancelTrace values.
    */
   public final Integer[] getCancelTraceArray()
   {
      return _CancelTrace;
   }
    
   /**
    * Gets the CancelUser field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CancelUser or null.
    */
   public final String getCancelUser( int index )
   {
      return _CancelUser[index];
   }
    
   /**
    * Gets the CancelUser field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CancelUser or the specified default value.
    */
   public final String getCancelUser( int index, String defaultValue )
   {
      return _CancelUser[index] == null ? defaultValue : _CancelUser[index];
   }
    
   /**
    * Gets the array of CancelUser fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CancelUser values.
    */
   public final String[] getCancelUserArray()
   {
      return _CancelUser;
   }
    
   /**
    * Gets the SettleBatch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SettleBatch or null.
    */
   public final String getSettleBatch( int index )
   {
      return _SettleBatch[index];
   }
    
   /**
    * Gets the SettleBatch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SettleBatch or the specified default value.
    */
   public final String getSettleBatch( int index, String defaultValue )
   {
      return _SettleBatch[index] == null ? defaultValue : _SettleBatch[index];
   }
    
   /**
    * Gets the array of SettleBatch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SettleBatch values.
    */
   public final String[] getSettleBatchArray()
   {
      return _SettleBatch;
   }
    
   /**
    * Gets the SettleTrace field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SettleTrace or null.
    */
   public final Integer getSettleTrace( int index )
   {
      return _SettleTrace[index];
   }
    
   /**
    * Gets the SettleTrace field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SettleTrace or the specified default value.
    */
   public final int getSettleTrace( int index, int defaultValue )
   {
      return _SettleTrace[index] == null ? defaultValue : _SettleTrace[index].intValue();
   }
    
   /**
    * Gets the array of SettleTrace fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SettleTrace values.
    */
   public final Integer[] getSettleTraceArray()
   {
      return _SettleTrace;
   }
    
   /**
    * Gets the SettleUser field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SettleUser or null.
    */
   public final String getSettleUser( int index )
   {
      return _SettleUser[index];
   }
    
   /**
    * Gets the SettleUser field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SettleUser or the specified default value.
    */
   public final String getSettleUser( int index, String defaultValue )
   {
      return _SettleUser[index] == null ? defaultValue : _SettleUser[index];
   }
    
   /**
    * Gets the array of SettleUser fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SettleUser values.
    */
   public final String[] getSettleUserArray()
   {
      return _SettleUser;
   }
    
   /**
    * Gets the VerifiedBy field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the VerifiedBy or null.
    */
   public final String getVerifiedBy( int index )
   {
      return _VerifiedBy[index];
   }
    
   /**
    * Gets the VerifiedBy field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the VerifiedBy or the specified default value.
    */
   public final String getVerifiedBy( int index, String defaultValue )
   {
      return _VerifiedBy[index] == null ? defaultValue : _VerifiedBy[index];
   }
    
   /**
    * Gets the array of VerifiedBy fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of VerifiedBy values.
    */
   public final String[] getVerifiedByArray()
   {
      return _VerifiedBy;
   }
    
   /**
    * Gets the Account To/From field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account To/From or null.
    */
   public final String getTfrAcct( int index )
   {
      return _TfrAcct[index];
   }
    
   /**
    * Gets the Account To/From field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account To/From or the specified default value.
    */
   public final String getTfrAcct( int index, String defaultValue )
   {
      return _TfrAcct[index] == null ? defaultValue : _TfrAcct[index];
   }
    
   /**
    * Gets the array of Account To/From fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account To/From values.
    */
   public final String[] getTfrAcctArray()
   {
      return _TfrAcct;
   }
    
   /**
    * Gets the Fund To/From field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund To/From or null.
    */
   public final String getTfrFund( int index )
   {
      return _TfrFund[index];
   }
    
   /**
    * Gets the Fund To/From field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund To/From or the specified default value.
    */
   public final String getTfrFund( int index, String defaultValue )
   {
      return _TfrFund[index] == null ? defaultValue : _TfrFund[index];
   }
    
   /**
    * Gets the array of Fund To/From fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund To/From values.
    */
   public final String[] getTfrFundArray()
   {
      return _TfrFund;
   }
    
   /**
    * Gets the Class To/From field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class To/From or null.
    */
   public final String getTfrClass( int index )
   {
      return _TfrClass[index];
   }
    
   /**
    * Gets the Class To/From field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class To/From or the specified default value.
    */
   public final String getTfrClass( int index, String defaultValue )
   {
      return _TfrClass[index] == null ? defaultValue : _TfrClass[index];
   }
    
   /**
    * Gets the array of Class To/From fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class To/From values.
    */
   public final String[] getTfrClassArray()
   {
      return _TfrClass;
   }
    
   /**
    * Gets the Settle Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settle Currency or null.
    */
   public final String getSettleCurrency( int index )
   {
      return _SettleCurrency[index];
   }
    
   /**
    * Gets the Settle Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settle Currency or the specified default value.
    */
   public final String getSettleCurrency( int index, String defaultValue )
   {
      return _SettleCurrency[index] == null ? defaultValue : _SettleCurrency[index];
   }
    
   /**
    * Gets the array of Settle Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settle Currency values.
    */
   public final String[] getSettleCurrencyArray()
   {
      return _SettleCurrency;
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
    * Gets the SalesRepCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SalesRepCode or null.
    */
   public final String getSalesRepCode( int index )
   {
      return _SalesRepCode[index];
   }
    
   /**
    * Gets the SalesRepCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SalesRepCode or the specified default value.
    */
   public final String getSalesRepCode( int index, String defaultValue )
   {
      return _SalesRepCode[index] == null ? defaultValue : _SalesRepCode[index];
   }
    
   /**
    * Gets the array of SalesRepCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SalesRepCode values.
    */
   public final String[] getSalesRepCodeArray()
   {
      return _SalesRepCode;
   }
    
   /**
    * Gets the Offer Price field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Offer Price or null.
    */
   public final String getOfferPrice( int index )
   {
      return _OfferPrice[index];
   }
    
   /**
    * Gets the Offer Price field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Offer Price or the specified default value.
    */
   public final String getOfferPrice( int index, String defaultValue )
   {
      return _OfferPrice[index] == null ? defaultValue : _OfferPrice[index];
   }
    
   /**
    * Gets the array of Offer Price fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Offer Price values.
    */
   public final String[] getOfferPriceArray()
   {
      return _OfferPrice;
   }
    
   /**
    * Gets the Acct Owner's First Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct Owner's First Name or null.
    */
   public final String getFirstName( int index )
   {
      return _FirstName[index];
   }
    
   /**
    * Gets the Acct Owner's First Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct Owner's First Name or the specified default value.
    */
   public final String getFirstName( int index, String defaultValue )
   {
      return _FirstName[index] == null ? defaultValue : _FirstName[index];
   }
    
   /**
    * Gets the array of Acct Owner's First Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct Owner's First Name values.
    */
   public final String[] getFirstNameArray()
   {
      return _FirstName;
   }
    
   /**
    * Gets the Acct Owner's Last Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct Owner's Last Name or null.
    */
   public final String getLastName( int index )
   {
      return _LastName[index];
   }
    
   /**
    * Gets the Acct Owner's Last Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct Owner's Last Name or the specified default value.
    */
   public final String getLastName( int index, String defaultValue )
   {
      return _LastName[index] == null ? defaultValue : _LastName[index];
   }
    
   /**
    * Gets the array of Acct Owner's Last Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct Owner's Last Name values.
    */
   public final String[] getLastNameArray()
   {
      return _LastName;
   }
    
   /**
    * Gets the Settled Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settled Description or null.
    */
   public final String getSettledDesc( int index )
   {
      return _SettledDesc[index];
   }
    
   /**
    * Gets the Settled Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled Description or the specified default value.
    */
   public final String getSettledDesc( int index, String defaultValue )
   {
      return _SettledDesc[index] == null ? defaultValue : _SettledDesc[index];
   }
    
   /**
    * Gets the array of Settled Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled Description values.
    */
   public final String[] getSettledDescArray()
   {
      return _SettledDesc;
   }
    
   /**
    * Gets the Sequence Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sequence Number or null.
    */
   public final Integer getSeqNum( int index )
   {
      return _SeqNum[index];
   }
    
   /**
    * Gets the Sequence Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sequence Number or the specified default value.
    */
   public final int getSeqNum( int index, int defaultValue )
   {
      return _SeqNum[index] == null ? defaultValue : _SeqNum[index].intValue();
   }
    
   /**
    * Gets the array of Sequence Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sequence Number values.
    */
   public final Integer[] getSeqNumArray()
   {
      return _SeqNum;
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
    * Gets the Existing External Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Existing External Id or null.
    */
   public final Boolean getExistExternalId( int index )
   {
      return _ExistExternalId[index];
   }
    
   /**
    * Gets the Existing External Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Existing External Id or the specified default value.
    */
   public final boolean getExistExternalId( int index, boolean defaultValue )
   {
      return _ExistExternalId[index] == null ? defaultValue : _ExistExternalId[index].booleanValue();
   }
    
   /**
    * Gets the array of Existing External Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Existing External Id values.
    */
   public final Boolean[] getExistExternalIdArray()
   {
      return _ExistExternalId;
   }
    
   /**
    * Gets the YES/NO - if message exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the YES/NO - if message exists or null.
    */
   public final Boolean getMessageExist( int index )
   {
      return _MessageExist[index];
   }
    
   /**
    * Gets the YES/NO - if message exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the YES/NO - if message exists or the specified default value.
    */
   public final boolean getMessageExist( int index, boolean defaultValue )
   {
      return _MessageExist[index] == null ? defaultValue : _MessageExist[index].booleanValue();
   }
    
   /**
    * Gets the array of YES/NO - if message exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of YES/NO - if message exists values.
    */
   public final Boolean[] getMessageExistArray()
   {
      return _MessageExist;
   }
    
   /**
    * Gets the Transaction Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Status or null.
    */
   public final String getTransStatus( int index )
   {
      return _TransStatus[index];
   }
    
   /**
    * Gets the Transaction Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Status or the specified default value.
    */
   public final String getTransStatus( int index, String defaultValue )
   {
      return _TransStatus[index] == null ? defaultValue : _TransStatus[index];
   }
    
   /**
    * Gets the array of Transaction Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Status values.
    */
   public final String[] getTransStatusArray()
   {
      return _TransStatus;
   }
    
   /**
    * Gets the Reporting Exchange Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reporting Exchange Rate or null.
    */
   public final String getReportingExchRate( int index )
   {
      return _ReportingExchRate[index];
   }
    
   /**
    * Gets the Reporting Exchange Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reporting Exchange Rate or the specified default value.
    */
   public final String getReportingExchRate( int index, String defaultValue )
   {
      return _ReportingExchRate[index] == null ? defaultValue : _ReportingExchRate[index];
   }
    
   /**
    * Gets the array of Reporting Exchange Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reporting Exchange Rate values.
    */
   public final String[] getReportingExchRateArray()
   {
      return _ReportingExchRate;
   }
    
   /**
    * Gets the Flag indicating if response from HRDC is pending field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if response from HRDC is pending or null.
    */
   public final Boolean getHRDCRespPending( int index )
   {
      return _HRDCRespPending[index];
   }
    
   /**
    * Gets the Flag indicating if response from HRDC is pending field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if response from HRDC is pending or the specified default value.
    */
   public final boolean getHRDCRespPending( int index, boolean defaultValue )
   {
      return _HRDCRespPending[index] == null ? defaultValue : _HRDCRespPending[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if response from HRDC is pending fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if response from HRDC is pending values.
    */
   public final Boolean[] getHRDCRespPendingArray()
   {
      return _HRDCRespPending;
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
      
      _TransId = resizeArray( _TransId, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _TransTypeDesc = resizeArray( _TransTypeDesc, _RepeatCount );
      _TransNum = resizeArray( _TransNum, _RepeatCount );
      _TradeDate = resizeArray( _TradeDate, _RepeatCount );
      _SettleDate = resizeArray( _SettleDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _Settled = resizeArray( _Settled, _RepeatCount );
      _GrossAmt = resizeArray( _GrossAmt, _RepeatCount );
      _NetAmt = resizeArray( _NetAmt, _RepeatCount );
      _UnitPrice = resizeArray( _UnitPrice, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _UnitBalance = resizeArray( _UnitBalance, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _Cancelled = resizeArray( _Cancelled, _RepeatCount );
      _Reversal = resizeArray( _Reversal, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _PayTypeDesc = resizeArray( _PayTypeDesc, _RepeatCount );
      _OrderBatch = resizeArray( _OrderBatch, _RepeatCount );
      _OrderTrace = resizeArray( _OrderTrace, _RepeatCount );
      _OrderUser = resizeArray( _OrderUser, _RepeatCount );
      _CancelBatch = resizeArray( _CancelBatch, _RepeatCount );
      _CancelTrace = resizeArray( _CancelTrace, _RepeatCount );
      _CancelUser = resizeArray( _CancelUser, _RepeatCount );
      _SettleBatch = resizeArray( _SettleBatch, _RepeatCount );
      _SettleTrace = resizeArray( _SettleTrace, _RepeatCount );
      _SettleUser = resizeArray( _SettleUser, _RepeatCount );
      _VerifiedBy = resizeArray( _VerifiedBy, _RepeatCount );
      _TfrAcct = resizeArray( _TfrAcct, _RepeatCount );
      _TfrFund = resizeArray( _TfrFund, _RepeatCount );
      _TfrClass = resizeArray( _TfrClass, _RepeatCount );
      _SettleCurrency = resizeArray( _SettleCurrency, _RepeatCount );
      _Amount = resizeArray( _Amount, _RepeatCount );
      _BrokerCode = resizeArray( _BrokerCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _SalesRepCode = resizeArray( _SalesRepCode, _RepeatCount );
      _OfferPrice = resizeArray( _OfferPrice, _RepeatCount );
      _FirstName = resizeArray( _FirstName, _RepeatCount );
      _LastName = resizeArray( _LastName, _RepeatCount );
      _SettledDesc = resizeArray( _SettledDesc, _RepeatCount );
      _SeqNum = resizeArray( _SeqNum, _RepeatCount );
      _AMSTrade = resizeArray( _AMSTrade, _RepeatCount );
      _rxAccountNum = resizeArray( _rxAccountNum, _RepeatCount );
      _ExistExternalId = resizeArray( _ExistExternalId, _RepeatCount );
      _MessageExist = resizeArray( _MessageExist, _RepeatCount );
      _TransStatus = resizeArray( _TransStatus, _RepeatCount );
      _ReportingExchRate = resizeArray( _ReportingExchRate, _RepeatCount );
      _HRDCRespPending = resizeArray( _HRDCRespPending, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Settled[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitPrice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitBalance[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Cancelled[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Reversal[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrderBatch[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrderTrace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _OrderUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CancelBatch[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CancelTrace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _CancelUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleBatch[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleTrace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SettleUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VerifiedBy[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrClass[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Amount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SalesRepCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OfferPrice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettledDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SeqNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AMSTrade[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _rxAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExistExternalId[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MessageExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TransStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReportingExchRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HRDCRespPending[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
