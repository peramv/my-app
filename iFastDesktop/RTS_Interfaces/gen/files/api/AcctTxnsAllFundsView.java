
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account/fund transaction history (all funds) view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctTxnsAllFunds.doc">AcctTxnsAllFunds.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctTxnsAllFundsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * TransId member array.
    */
   private String[] _TransId = null;
   
   /**
    * TransactionNum member array.
    */
   private Integer[] _TransNum = null;
   
   /**
    * TransType member array.
    */
   private String[] _TransType = null;
   
   /**
    * SettleDate member array.
    */
   private Date[] _SettleDate = null;
   
   /**
    * Settled member array.
    */
   private Boolean[] _Settled = null;
   
   /**
    * TradeDate member array.
    */
   private Date[] _TradeDate = null;
   
   /**
    * GrossAmt member array.
    */
   private String[] _GrossAmt = null;
   
   /**
    * NetAmt member array.
    */
   private String[] _NetAmt = null;
   
   /**
    * UnitPrice member array.
    */
   private String[] _UnitPrice = null;
   
   /**
    * Units member array.
    */
   private String[] _Units = null;
   
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
    * BackdatedOn member array.
    */
   private Date[] _BackDatedOn = null;
   
   /**
    * Cancelled member array.
    */
   private Boolean[] _Cancelled = null;
   
   /**
    * Cancellation member array.
    */
   private Boolean[] _Cancellation = null;
   
   /**
    * Trans type description member array.
    */
   private String[] _TransTypeDesc = null;
   
   /**
    * Fund code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class of fund member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * PayType Code member array.
    */
   private String[] _PayType = null;
   
   /**
    * PayType Code Description member array.
    */
   private String[] _PayTypeDesc = null;
   
   /**
    * Statement Code member array.
    */
   private String[] _StatementCode = null;
   
   /**
    * StatementCode Desc member array.
    */
   private String[] _StatementCodeDesc = null;
   
   /**
    * Paid by EFT, Cheque or Other member array.
    */
   private String[] _PaymentType = null;
   

   /**
    * Constructs the AcctTxnsAllFundsView object.
    * 
    */
   public AcctTxnsAllFundsView()
   {
      super ( new AcctTxnsAllFundsRequest() );
   }

   /**
    * Constructs the AcctTxnsAllFundsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctTxnsAllFundsView( String hostEncoding )
   {
      super ( new AcctTxnsAllFundsRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctTxnsAllFundsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctTxnsAllFundsRequest object.
    */
   public final AcctTxnsAllFundsRequest getRequest()
   {
      return (AcctTxnsAllFundsRequest)getIFastRequest();
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
    * Gets the TransId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransId or null.
    */
   public final String getTransId( int index )
   {
      return _TransId[index];
   }
    
   /**
    * Gets the TransId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransId or the specified default value.
    */
   public final String getTransId( int index, String defaultValue )
   {
      return _TransId[index] == null ? defaultValue : _TransId[index];
   }
    
   /**
    * Gets the array of TransId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransId values.
    */
   public final String[] getTransIdArray()
   {
      return _TransId;
   }
    
   /**
    * Gets the TransactionNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TransactionNum or null.
    */
   public final Integer getTransNum( int index )
   {
      return _TransNum[index];
   }
    
   /**
    * Gets the TransactionNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransactionNum or the specified default value.
    */
   public final int getTransNum( int index, int defaultValue )
   {
      return _TransNum[index] == null ? defaultValue : _TransNum[index].intValue();
   }
    
   /**
    * Gets the array of TransactionNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TransactionNum values.
    */
   public final Integer[] getTransNumArray()
   {
      return _TransNum;
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
    * Gets the GrossAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GrossAmt or null.
    */
   public final String getGrossAmt( int index )
   {
      return _GrossAmt[index];
   }
    
   /**
    * Gets the GrossAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrossAmt or the specified default value.
    */
   public final String getGrossAmt( int index, String defaultValue )
   {
      return _GrossAmt[index] == null ? defaultValue : _GrossAmt[index];
   }
    
   /**
    * Gets the array of GrossAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GrossAmt values.
    */
   public final String[] getGrossAmtArray()
   {
      return _GrossAmt;
   }
    
   /**
    * Gets the NetAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NetAmt or null.
    */
   public final String getNetAmt( int index )
   {
      return _NetAmt[index];
   }
    
   /**
    * Gets the NetAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetAmt or the specified default value.
    */
   public final String getNetAmt( int index, String defaultValue )
   {
      return _NetAmt[index] == null ? defaultValue : _NetAmt[index];
   }
    
   /**
    * Gets the array of NetAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NetAmt values.
    */
   public final String[] getNetAmtArray()
   {
      return _NetAmt;
   }
    
   /**
    * Gets the UnitPrice field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UnitPrice or null.
    */
   public final String getUnitPrice( int index )
   {
      return _UnitPrice[index];
   }
    
   /**
    * Gets the UnitPrice field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UnitPrice or the specified default value.
    */
   public final String getUnitPrice( int index, String defaultValue )
   {
      return _UnitPrice[index] == null ? defaultValue : _UnitPrice[index];
   }
    
   /**
    * Gets the array of UnitPrice fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UnitPrice values.
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
    * Gets the BackdatedOn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BackdatedOn or null.
    */
   public final Date getBackDatedOn( int index )
   {
      return _BackDatedOn[index];
   }
    
   /**
    * Gets the BackdatedOn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BackdatedOn or the specified default value.
    */
   public final Date getBackDatedOn( int index, Date defaultValue )
   {
      return _BackDatedOn[index] == null ? defaultValue : _BackDatedOn[index];
   }
    
   /**
    * Gets the array of BackdatedOn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BackdatedOn values.
    */
   public final Date[] getBackDatedOnArray()
   {
      return _BackDatedOn;
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
    * Gets the Cancellation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cancellation or null.
    */
   public final Boolean getCancellation( int index )
   {
      return _Cancellation[index];
   }
    
   /**
    * Gets the Cancellation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cancellation or the specified default value.
    */
   public final boolean getCancellation( int index, boolean defaultValue )
   {
      return _Cancellation[index] == null ? defaultValue : _Cancellation[index].booleanValue();
   }
    
   /**
    * Gets the array of Cancellation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cancellation values.
    */
   public final Boolean[] getCancellationArray()
   {
      return _Cancellation;
   }
    
   /**
    * Gets the Trans type description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trans type description or null.
    */
   public final String getTransTypeDesc( int index )
   {
      return _TransTypeDesc[index];
   }
    
   /**
    * Gets the Trans type description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trans type description or the specified default value.
    */
   public final String getTransTypeDesc( int index, String defaultValue )
   {
      return _TransTypeDesc[index] == null ? defaultValue : _TransTypeDesc[index];
   }
    
   /**
    * Gets the array of Trans type description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trans type description values.
    */
   public final String[] getTransTypeDescArray()
   {
      return _TransTypeDesc;
   }
    
   /**
    * Gets the Fund code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund code or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class of fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class of fund or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class of fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class of fund or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class of fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class of fund values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the PayType Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PayType Code or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the PayType Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PayType Code or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of PayType Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PayType Code values.
    */
   public final String[] getPayTypeArray()
   {
      return _PayType;
   }
    
   /**
    * Gets the PayType Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PayType Code Description or null.
    */
   public final String getPayTypeDesc( int index )
   {
      return _PayTypeDesc[index];
   }
    
   /**
    * Gets the PayType Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PayType Code Description or the specified default value.
    */
   public final String getPayTypeDesc( int index, String defaultValue )
   {
      return _PayTypeDesc[index] == null ? defaultValue : _PayTypeDesc[index];
   }
    
   /**
    * Gets the array of PayType Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PayType Code Description values.
    */
   public final String[] getPayTypeDescArray()
   {
      return _PayTypeDesc;
   }
    
   /**
    * Gets the Statement Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Statement Code or null.
    */
   public final String getStatementCode( int index )
   {
      return _StatementCode[index];
   }
    
   /**
    * Gets the Statement Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Statement Code or the specified default value.
    */
   public final String getStatementCode( int index, String defaultValue )
   {
      return _StatementCode[index] == null ? defaultValue : _StatementCode[index];
   }
    
   /**
    * Gets the array of Statement Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Statement Code values.
    */
   public final String[] getStatementCodeArray()
   {
      return _StatementCode;
   }
    
   /**
    * Gets the StatementCode Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StatementCode Desc or null.
    */
   public final String getStatementCodeDesc( int index )
   {
      return _StatementCodeDesc[index];
   }
    
   /**
    * Gets the StatementCode Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StatementCode Desc or the specified default value.
    */
   public final String getStatementCodeDesc( int index, String defaultValue )
   {
      return _StatementCodeDesc[index] == null ? defaultValue : _StatementCodeDesc[index];
   }
    
   /**
    * Gets the array of StatementCode Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StatementCode Desc values.
    */
   public final String[] getStatementCodeDescArray()
   {
      return _StatementCodeDesc;
   }
    
   /**
    * Gets the Paid by EFT, Cheque or Other field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Paid by EFT, Cheque or Other or null.
    */
   public final String getPaymentType( int index )
   {
      return _PaymentType[index];
   }
    
   /**
    * Gets the Paid by EFT, Cheque or Other field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Paid by EFT, Cheque or Other or the specified default value.
    */
   public final String getPaymentType( int index, String defaultValue )
   {
      return _PaymentType[index] == null ? defaultValue : _PaymentType[index];
   }
    
   /**
    * Gets the array of Paid by EFT, Cheque or Other fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Paid by EFT, Cheque or Other values.
    */
   public final String[] getPaymentTypeArray()
   {
      return _PaymentType;
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
      _TransNum = resizeArray( _TransNum, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _SettleDate = resizeArray( _SettleDate, _RepeatCount );
      _Settled = resizeArray( _Settled, _RepeatCount );
      _TradeDate = resizeArray( _TradeDate, _RepeatCount );
      _GrossAmt = resizeArray( _GrossAmt, _RepeatCount );
      _NetAmt = resizeArray( _NetAmt, _RepeatCount );
      _UnitPrice = resizeArray( _UnitPrice, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
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
      _BackDatedOn = resizeArray( _BackDatedOn, _RepeatCount );
      _Cancelled = resizeArray( _Cancelled, _RepeatCount );
      _Cancellation = resizeArray( _Cancellation, _RepeatCount );
      _TransTypeDesc = resizeArray( _TransTypeDesc, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _PayTypeDesc = resizeArray( _PayTypeDesc, _RepeatCount );
      _StatementCode = resizeArray( _StatementCode, _RepeatCount );
      _StatementCodeDesc = resizeArray( _StatementCodeDesc, _RepeatCount );
      _PaymentType = resizeArray( _PaymentType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TransId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Settled[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _GrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnitPrice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
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
         _BackDatedOn[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Cancelled[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Cancellation[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatementCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatementCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PaymentType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
