
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Advisor Pending Trades Listing view.
 * For additional view information see <A HREF="../../../../viewspecs/AdvPendTrades.doc">AdvPendTrades.doc</A>.
 * 
 * @author RTS Generated
 */
public class AdvPendTradesView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Trade Date member array.
    */
   private Date[] _TradeDate = null;
   
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = null;
   
   /**
    * Transaction Type Description member array.
    */
   private String[] _TransTypeDesc = null;
   
   /**
    * Transaction Number member array.
    */
   private Integer[] _TransNum = null;
   
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * First Name of Accountholder member array.
    */
   private String[] _FirstName = null;
   
   /**
    * Last Name of Accountholder member array.
    */
   private String[] _LastName = null;
   
   /**
    * Fund Currency member array.
    */
   private String[] _FundCurrency = null;
   
   /**
    * Dollar Amount of Trade in Fund Currency member array.
    */
   private String[] _AmountFundCurr = null;
   
   /**
    * Gross or Net member array.
    */
   private Boolean[] _GrossNet = null;
   
   /**
    * Settle Date member array.
    */
   private Date[] _SettleDate = null;
   
   /**
    * Settle Currency member array.
    */
   private String[] _SettleCurrency = null;
   
   /**
    * Dollar Amount of Trade in Settlement Currency member array.
    */
   private String[] _AmountSettleCurr = null;
   
   /**
    * Number of Units member array.
    */
   private String[] _Units = null;
   
   /**
    * Good or Bad Y/N member array.
    */
   private Boolean[] _GBCD = null;
   
   /**
    * Record ID member array.
    */
   private Integer[] _PendingRId = null;
   

   /**
    * Constructs the AdvPendTradesView object.
    * 
    */
   public AdvPendTradesView()
   {
      super ( new AdvPendTradesRequest() );
   }

   /**
    * Constructs the AdvPendTradesView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AdvPendTradesView( String hostEncoding )
   {
      super ( new AdvPendTradesRequest( hostEncoding ) );
   }

   /**
    * Gets the AdvPendTradesRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AdvPendTradesRequest object.
    */
   public final AdvPendTradesRequest getRequest()
   {
      return (AdvPendTradesRequest)getIFastRequest();
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
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
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
    * Gets the Trade Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Date or null.
    */
   public final Date getTradeDate( int index )
   {
      return _TradeDate[index];
   }
    
   /**
    * Gets the Trade Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Date or the specified default value.
    */
   public final Date getTradeDate( int index, Date defaultValue )
   {
      return _TradeDate[index] == null ? defaultValue : _TradeDate[index];
   }
    
   /**
    * Gets the array of Trade Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Date values.
    */
   public final Date[] getTradeDateArray()
   {
      return _TradeDate;
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
    * Gets the Transaction Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Type Description or null.
    */
   public final String getTransTypeDesc( int index )
   {
      return _TransTypeDesc[index];
   }
    
   /**
    * Gets the Transaction Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Type Description or the specified default value.
    */
   public final String getTransTypeDesc( int index, String defaultValue )
   {
      return _TransTypeDesc[index] == null ? defaultValue : _TransTypeDesc[index];
   }
    
   /**
    * Gets the array of Transaction Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Type Description values.
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
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getAccountNum( int index )
   {
      return _AccountNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getAccountNum( int index, String defaultValue )
   {
      return _AccountNum[index] == null ? defaultValue : _AccountNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getAccountNumArray()
   {
      return _AccountNum;
   }
    
   /**
    * Gets the First Name of Accountholder field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the First Name of Accountholder or null.
    */
   public final String getFirstName( int index )
   {
      return _FirstName[index];
   }
    
   /**
    * Gets the First Name of Accountholder field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Name of Accountholder or the specified default value.
    */
   public final String getFirstName( int index, String defaultValue )
   {
      return _FirstName[index] == null ? defaultValue : _FirstName[index];
   }
    
   /**
    * Gets the array of First Name of Accountholder fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of First Name of Accountholder values.
    */
   public final String[] getFirstNameArray()
   {
      return _FirstName;
   }
    
   /**
    * Gets the Last Name of Accountholder field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Name of Accountholder or null.
    */
   public final String getLastName( int index )
   {
      return _LastName[index];
   }
    
   /**
    * Gets the Last Name of Accountholder field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Name of Accountholder or the specified default value.
    */
   public final String getLastName( int index, String defaultValue )
   {
      return _LastName[index] == null ? defaultValue : _LastName[index];
   }
    
   /**
    * Gets the array of Last Name of Accountholder fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Name of Accountholder values.
    */
   public final String[] getLastNameArray()
   {
      return _LastName;
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
    * Gets the Dollar Amount of Trade in Fund Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dollar Amount of Trade in Fund Currency or null.
    */
   public final String getAmountFundCurr( int index )
   {
      return _AmountFundCurr[index];
   }
    
   /**
    * Gets the Dollar Amount of Trade in Fund Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dollar Amount of Trade in Fund Currency or the specified default value.
    */
   public final String getAmountFundCurr( int index, String defaultValue )
   {
      return _AmountFundCurr[index] == null ? defaultValue : _AmountFundCurr[index];
   }
    
   /**
    * Gets the array of Dollar Amount of Trade in Fund Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dollar Amount of Trade in Fund Currency values.
    */
   public final String[] getAmountFundCurrArray()
   {
      return _AmountFundCurr;
   }
    
   /**
    * Gets the Gross or Net field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross or Net or null.
    */
   public final Boolean getGrossNet( int index )
   {
      return _GrossNet[index];
   }
    
   /**
    * Gets the Gross or Net field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross or Net or the specified default value.
    */
   public final boolean getGrossNet( int index, boolean defaultValue )
   {
      return _GrossNet[index] == null ? defaultValue : _GrossNet[index].booleanValue();
   }
    
   /**
    * Gets the array of Gross or Net fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross or Net values.
    */
   public final Boolean[] getGrossNetArray()
   {
      return _GrossNet;
   }
    
   /**
    * Gets the Settle Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settle Date or null.
    */
   public final Date getSettleDate( int index )
   {
      return _SettleDate[index];
   }
    
   /**
    * Gets the Settle Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settle Date or the specified default value.
    */
   public final Date getSettleDate( int index, Date defaultValue )
   {
      return _SettleDate[index] == null ? defaultValue : _SettleDate[index];
   }
    
   /**
    * Gets the array of Settle Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settle Date values.
    */
   public final Date[] getSettleDateArray()
   {
      return _SettleDate;
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
    * Gets the Dollar Amount of Trade in Settlement Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dollar Amount of Trade in Settlement Currency or null.
    */
   public final String getAmountSettleCurr( int index )
   {
      return _AmountSettleCurr[index];
   }
    
   /**
    * Gets the Dollar Amount of Trade in Settlement Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dollar Amount of Trade in Settlement Currency or the specified default value.
    */
   public final String getAmountSettleCurr( int index, String defaultValue )
   {
      return _AmountSettleCurr[index] == null ? defaultValue : _AmountSettleCurr[index];
   }
    
   /**
    * Gets the array of Dollar Amount of Trade in Settlement Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dollar Amount of Trade in Settlement Currency values.
    */
   public final String[] getAmountSettleCurrArray()
   {
      return _AmountSettleCurr;
   }
    
   /**
    * Gets the Number of Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Number of Units or null.
    */
   public final String getUnits( int index )
   {
      return _Units[index];
   }
    
   /**
    * Gets the Number of Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number of Units or the specified default value.
    */
   public final String getUnits( int index, String defaultValue )
   {
      return _Units[index] == null ? defaultValue : _Units[index];
   }
    
   /**
    * Gets the array of Number of Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Number of Units values.
    */
   public final String[] getUnitsArray()
   {
      return _Units;
   }
    
   /**
    * Gets the Good or Bad Y/N field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Good or Bad Y/N or null.
    */
   public final Boolean getGBCD( int index )
   {
      return _GBCD[index];
   }
    
   /**
    * Gets the Good or Bad Y/N field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Good or Bad Y/N or the specified default value.
    */
   public final boolean getGBCD( int index, boolean defaultValue )
   {
      return _GBCD[index] == null ? defaultValue : _GBCD[index].booleanValue();
   }
    
   /**
    * Gets the array of Good or Bad Y/N fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Good or Bad Y/N values.
    */
   public final Boolean[] getGBCDArray()
   {
      return _GBCD;
   }
    
   /**
    * Gets the Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record ID or null.
    */
   public final Integer getPendingRId( int index )
   {
      return _PendingRId[index];
   }
    
   /**
    * Gets the Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record ID or the specified default value.
    */
   public final int getPendingRId( int index, int defaultValue )
   {
      return _PendingRId[index] == null ? defaultValue : _PendingRId[index].intValue();
   }
    
   /**
    * Gets the array of Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record ID values.
    */
   public final Integer[] getPendingRIdArray()
   {
      return _PendingRId;
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
      
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _TradeDate = resizeArray( _TradeDate, _RepeatCount );
      _TransType = resizeArray( _TransType, _RepeatCount );
      _TransTypeDesc = resizeArray( _TransTypeDesc, _RepeatCount );
      _TransNum = resizeArray( _TransNum, _RepeatCount );
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _FirstName = resizeArray( _FirstName, _RepeatCount );
      _LastName = resizeArray( _LastName, _RepeatCount );
      _FundCurrency = resizeArray( _FundCurrency, _RepeatCount );
      _AmountFundCurr = resizeArray( _AmountFundCurr, _RepeatCount );
      _GrossNet = resizeArray( _GrossNet, _RepeatCount );
      _SettleDate = resizeArray( _SettleDate, _RepeatCount );
      _SettleCurrency = resizeArray( _SettleCurrency, _RepeatCount );
      _AmountSettleCurr = resizeArray( _AmountSettleCurr, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _GBCD = resizeArray( _GBCD, _RepeatCount );
      _PendingRId = resizeArray( _PendingRId, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountFundCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossNet[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SettleCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AmountSettleCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GBCD[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PendingRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
