
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Pending Transactions view.
 * For additional view information see <A HREF="../../../../viewspecs/PendingTrades.doc">PendingTrades.doc</A>.
 * 
 * @author RTS Generated
 */
public class PendingTradesView extends IFastView implements Serializable
{

   /**
    * Loss Count member variable.
    */
   private Integer _LossCount = null;
   
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
   private String[] _GrossOrNet = null;
   
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
    * Batch Name member array.
    */
   private String[] _BatchName = null;
   
   /**
    * Batch Trace member array.
    */
   private Integer[] _BatchTrace = null;
   
   /**
    * Good Bad Code member array.
    */
   private Boolean[] _GoodBad = null;
   
   /**
    * Pending Trade Record ID member array.
    */
   private Integer[] _PendingRid = null;
   
   /**
    * Settlement Currency member array.
    */
   private String[] _SettleCurrency = null;
   
   /**
    * Cash Date member array.
    */
   private Date[] _CashDate = null;
   
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
    * Exists External Id member array.
    */
   private Boolean[] _ExistExternalId = null;
   
   /**
    * Client Settlement Amount member array.
    */
   private String[] _ClntSettlAmt = null;
   
   /**
    * Broker Settlement Amount member array.
    */
   private String[] _BrkSettlAmt = null;
   
   /**
    * Condition Rate member array.
    */
   private String[] _ConditionRate = null;
   
   /**
    * Transaction Fee member array.
    */
   private String[] _TxnFee = null;
   
   /**
    * Acq Fee Option member array.
    */
   private String[] _AcqFeeOpt = null;
   
   /**
    * Gain Loss Amount member array.
    */
   private String[] _GainLossAmount = null;
   
   /**
    * YES/NO - if message exists member array.
    */
   private Boolean[] _MessageExist = null;
   
   /**
    * Settle Date of transfer/exchange in member array.
    */
   private Date[] _SettleInDate = null;
   
   /**
    * VerPerm member array.
    */
   private String[] _VerPerm = null;
   
   /**
    * RejPerm member array.
    */
   private String[] _RejPerm = null;
   
   /**
    * RuleValWarnExist member array.
    */
   private Boolean[] _RuleValWarnExist = null;
   
   /**
    * Network_ID member array.
    */
   private String[] _Network_ID = null;
   

   /**
    * Constructs the PendingTradesView object.
    * 
    */
   public PendingTradesView()
   {
      super ( new PendingTradesRequest() );
   }

   /**
    * Constructs the PendingTradesView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PendingTradesView( String hostEncoding )
   {
      super ( new PendingTradesRequest( hostEncoding ) );
   }

   /**
    * Gets the PendingTradesRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PendingTradesRequest object.
    */
   public final PendingTradesRequest getRequest()
   {
      return (PendingTradesRequest)getIFastRequest();
   }
        
   /**
    * Gets the Loss Count field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Loss Count or null.
    */
   public final Integer getLossCount()
   {
      return _LossCount;
   }
	
   /**
    * Gets the Loss Count field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Loss Count or the specified default value.
    */
   public final int getLossCount( int defaultValue )
   {
      return _LossCount == null ? defaultValue : _LossCount.intValue();
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
   public final String getGrossOrNet( int index )
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
   public final String getGrossOrNet( int index, String defaultValue )
   {
      return _GrossOrNet[index] == null ? defaultValue : _GrossOrNet[index];
   }
    
   /**
    * Gets the array of Gross or Net fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross or Net values.
    */
   public final String[] getGrossOrNetArray()
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
    * Gets the Batch Trace field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Trace or null.
    */
   public final Integer getBatchTrace( int index )
   {
      return _BatchTrace[index];
   }
    
   /**
    * Gets the Batch Trace field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Trace or the specified default value.
    */
   public final int getBatchTrace( int index, int defaultValue )
   {
      return _BatchTrace[index] == null ? defaultValue : _BatchTrace[index].intValue();
   }
    
   /**
    * Gets the array of Batch Trace fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Trace values.
    */
   public final Integer[] getBatchTraceArray()
   {
      return _BatchTrace;
   }
    
   /**
    * Gets the Good Bad Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Good Bad Code or null.
    */
   public final Boolean getGoodBad( int index )
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
   public final boolean getGoodBad( int index, boolean defaultValue )
   {
      return _GoodBad[index] == null ? defaultValue : _GoodBad[index].booleanValue();
   }
    
   /**
    * Gets the array of Good Bad Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Good Bad Code values.
    */
   public final Boolean[] getGoodBadArray()
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
    * Gets the Cash Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cash Date or null.
    */
   public final Date getCashDate( int index )
   {
      return _CashDate[index];
   }
    
   /**
    * Gets the Cash Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cash Date or the specified default value.
    */
   public final Date getCashDate( int index, Date defaultValue )
   {
      return _CashDate[index] == null ? defaultValue : _CashDate[index];
   }
    
   /**
    * Gets the array of Cash Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cash Date values.
    */
   public final Date[] getCashDateArray()
   {
      return _CashDate;
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
    * Gets the Exists External Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exists External Id or null.
    */
   public final Boolean getExistExternalId( int index )
   {
      return _ExistExternalId[index];
   }
    
   /**
    * Gets the Exists External Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exists External Id or the specified default value.
    */
   public final boolean getExistExternalId( int index, boolean defaultValue )
   {
      return _ExistExternalId[index] == null ? defaultValue : _ExistExternalId[index].booleanValue();
   }
    
   /**
    * Gets the array of Exists External Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exists External Id values.
    */
   public final Boolean[] getExistExternalIdArray()
   {
      return _ExistExternalId;
   }
    
   /**
    * Gets the Client Settlement Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Client Settlement Amount or null.
    */
   public final String getClntSettlAmt( int index )
   {
      return _ClntSettlAmt[index];
   }
    
   /**
    * Gets the Client Settlement Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Client Settlement Amount or the specified default value.
    */
   public final String getClntSettlAmt( int index, String defaultValue )
   {
      return _ClntSettlAmt[index] == null ? defaultValue : _ClntSettlAmt[index];
   }
    
   /**
    * Gets the array of Client Settlement Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Client Settlement Amount values.
    */
   public final String[] getClntSettlAmtArray()
   {
      return _ClntSettlAmt;
   }
    
   /**
    * Gets the Broker Settlement Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Settlement Amount or null.
    */
   public final String getBrkSettlAmt( int index )
   {
      return _BrkSettlAmt[index];
   }
    
   /**
    * Gets the Broker Settlement Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Settlement Amount or the specified default value.
    */
   public final String getBrkSettlAmt( int index, String defaultValue )
   {
      return _BrkSettlAmt[index] == null ? defaultValue : _BrkSettlAmt[index];
   }
    
   /**
    * Gets the array of Broker Settlement Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Settlement Amount values.
    */
   public final String[] getBrkSettlAmtArray()
   {
      return _BrkSettlAmt;
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
   public final String getAcqFeeOpt( int index )
   {
      return _AcqFeeOpt[index];
   }
    
   /**
    * Gets the Acq Fee Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acq Fee Option or the specified default value.
    */
   public final String getAcqFeeOpt( int index, String defaultValue )
   {
      return _AcqFeeOpt[index] == null ? defaultValue : _AcqFeeOpt[index];
   }
    
   /**
    * Gets the array of Acq Fee Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acq Fee Option values.
    */
   public final String[] getAcqFeeOptArray()
   {
      return _AcqFeeOpt;
   }
    
   /**
    * Gets the Gain Loss Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gain Loss Amount or null.
    */
   public final String getGainLossAmount( int index )
   {
      return _GainLossAmount[index];
   }
    
   /**
    * Gets the Gain Loss Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gain Loss Amount or the specified default value.
    */
   public final String getGainLossAmount( int index, String defaultValue )
   {
      return _GainLossAmount[index] == null ? defaultValue : _GainLossAmount[index];
   }
    
   /**
    * Gets the array of Gain Loss Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gain Loss Amount values.
    */
   public final String[] getGainLossAmountArray()
   {
      return _GainLossAmount;
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
    * Gets the Settle Date of transfer/exchange in field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settle Date of transfer/exchange in or null.
    */
   public final Date getSettleInDate( int index )
   {
      return _SettleInDate[index];
   }
    
   /**
    * Gets the Settle Date of transfer/exchange in field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settle Date of transfer/exchange in or the specified default value.
    */
   public final Date getSettleInDate( int index, Date defaultValue )
   {
      return _SettleInDate[index] == null ? defaultValue : _SettleInDate[index];
   }
    
   /**
    * Gets the array of Settle Date of transfer/exchange in fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settle Date of transfer/exchange in values.
    */
   public final Date[] getSettleInDateArray()
   {
      return _SettleInDate;
   }
    
   /**
    * Gets the VerPerm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the VerPerm or null.
    */
   public final String getVerPerm( int index )
   {
      return _VerPerm[index];
   }
    
   /**
    * Gets the VerPerm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the VerPerm or the specified default value.
    */
   public final String getVerPerm( int index, String defaultValue )
   {
      return _VerPerm[index] == null ? defaultValue : _VerPerm[index];
   }
    
   /**
    * Gets the array of VerPerm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of VerPerm values.
    */
   public final String[] getVerPermArray()
   {
      return _VerPerm;
   }
    
   /**
    * Gets the RejPerm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RejPerm or null.
    */
   public final String getRejPerm( int index )
   {
      return _RejPerm[index];
   }
    
   /**
    * Gets the RejPerm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RejPerm or the specified default value.
    */
   public final String getRejPerm( int index, String defaultValue )
   {
      return _RejPerm[index] == null ? defaultValue : _RejPerm[index];
   }
    
   /**
    * Gets the array of RejPerm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RejPerm values.
    */
   public final String[] getRejPermArray()
   {
      return _RejPerm;
   }
    
   /**
    * Gets the RuleValWarnExist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RuleValWarnExist or null.
    */
   public final Boolean getRuleValWarnExist( int index )
   {
      return _RuleValWarnExist[index];
   }
    
   /**
    * Gets the RuleValWarnExist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RuleValWarnExist or the specified default value.
    */
   public final boolean getRuleValWarnExist( int index, boolean defaultValue )
   {
      return _RuleValWarnExist[index] == null ? defaultValue : _RuleValWarnExist[index].booleanValue();
   }
    
   /**
    * Gets the array of RuleValWarnExist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RuleValWarnExist values.
    */
   public final Boolean[] getRuleValWarnExistArray()
   {
      return _RuleValWarnExist;
   }
    
   /**
    * Gets the Network_ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Network_ID or null.
    */
   public final String getNetwork_ID( int index )
   {
      return _Network_ID[index];
   }
    
   /**
    * Gets the Network_ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Network_ID or the specified default value.
    */
   public final String getNetwork_ID( int index, String defaultValue )
   {
      return _Network_ID[index] == null ? defaultValue : _Network_ID[index];
   }
    
   /**
    * Gets the array of Network_ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Network_ID values.
    */
   public final String[] getNetwork_IDArray()
   {
      return _Network_ID;
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
      _LossCount = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  
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
      _BatchName = resizeArray( _BatchName, _RepeatCount );
      _BatchTrace = resizeArray( _BatchTrace, _RepeatCount );
      _GoodBad = resizeArray( _GoodBad, _RepeatCount );
      _PendingRid = resizeArray( _PendingRid, _RepeatCount );
      _SettleCurrency = resizeArray( _SettleCurrency, _RepeatCount );
      _CashDate = resizeArray( _CashDate, _RepeatCount );
      _ShrNum = resizeArray( _ShrNum, _RepeatCount );
      _rxAccountNum = resizeArray( _rxAccountNum, _RepeatCount );
      _GoodBadDesc = resizeArray( _GoodBadDesc, _RepeatCount );
      _OrderTypeDesc = resizeArray( _OrderTypeDesc, _RepeatCount );
      _AMSTrade = resizeArray( _AMSTrade, _RepeatCount );
      _TradeAMSCode = resizeArray( _TradeAMSCode, _RepeatCount );
      _ExistExternalId = resizeArray( _ExistExternalId, _RepeatCount );
      _ClntSettlAmt = resizeArray( _ClntSettlAmt, _RepeatCount );
      _BrkSettlAmt = resizeArray( _BrkSettlAmt, _RepeatCount );
      _ConditionRate = resizeArray( _ConditionRate, _RepeatCount );
      _TxnFee = resizeArray( _TxnFee, _RepeatCount );
      _AcqFeeOpt = resizeArray( _AcqFeeOpt, _RepeatCount );
      _GainLossAmount = resizeArray( _GainLossAmount, _RepeatCount );
      _MessageExist = resizeArray( _MessageExist, _RepeatCount );
      _SettleInDate = resizeArray( _SettleInDate, _RepeatCount );
      _VerPerm = resizeArray( _VerPerm, _RepeatCount );
      _RejPerm = resizeArray( _RejPerm, _RepeatCount );
      _RuleValWarnExist = resizeArray( _RuleValWarnExist, _RepeatCount );
      _Network_ID = resizeArray( _Network_ID, _RepeatCount );
        
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
         _GrossOrNet[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrderType[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _WireOrdNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchTrace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _GoodBad[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PendingRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SettleCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CashDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ShrNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GoodBadDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrderTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMSTrade[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TradeAMSCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExistExternalId[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ClntSettlAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrkSettlAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ConditionRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TxnFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqFeeOpt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GainLossAmount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MessageExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SettleInDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _VerPerm[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RejPerm[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RuleValWarnExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Network_ID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
