
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Advisor Processed Trades Listing view.
 * For additional view information see <A HREF="../../../../viewspecs/AdvProcTrades.doc">AdvProcTrades.doc</A>.
 * 
 * @author RTS Generated
 */
public class AdvProcTradesView extends IFastView implements Serializable
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
    * Transaction ID member array.
    */
   private Integer[] _TransID = null;
   
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
    * Gross Amount in Fund Currency member array.
    */
   private String[] _GrossAmtFundCurr = null;
   
   /**
    * Settle Date member array.
    */
   private Date[] _SettleDate = null;
   
   /**
    * Settle Currency member array.
    */
   private String[] _SettleCurrency = null;
   
   /**
    * Gross Amount in Settlement Currency member array.
    */
   private String[] _GrossAmtSettleCurr = null;
   
   /**
    * Number of Units member array.
    */
   private String[] _Units = null;
   
   /**
    * Rate member array.
    */
   private String[] _Rate = null;
   
   /**
    * Settled Y/N member array.
    */
   private Boolean[] _Settled = null;
   
   /**
    * Settled Units Balance member array.
    */
   private String[] _SettledUnitsBalance = null;
   
   /**
    * Total Units Balance member array.
    */
   private String[] _TotalUnitsBalance = null;
   

   /**
    * Constructs the AdvProcTradesView object.
    * 
    */
   public AdvProcTradesView()
   {
      super ( new AdvProcTradesRequest() );
   }

   /**
    * Constructs the AdvProcTradesView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AdvProcTradesView( String hostEncoding )
   {
      super ( new AdvProcTradesRequest( hostEncoding ) );
   }

   /**
    * Gets the AdvProcTradesRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AdvProcTradesRequest object.
    */
   public final AdvProcTradesRequest getRequest()
   {
      return (AdvProcTradesRequest)getIFastRequest();
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
    * Gets the Transaction ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction ID or null.
    */
   public final Integer getTransID( int index )
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
   public final int getTransID( int index, int defaultValue )
   {
      return _TransID[index] == null ? defaultValue : _TransID[index].intValue();
   }
    
   /**
    * Gets the array of Transaction ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction ID values.
    */
   public final Integer[] getTransIDArray()
   {
      return _TransID;
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
    * Gets the Gross Amount in Fund Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross Amount in Fund Currency or null.
    */
   public final String getGrossAmtFundCurr( int index )
   {
      return _GrossAmtFundCurr[index];
   }
    
   /**
    * Gets the Gross Amount in Fund Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross Amount in Fund Currency or the specified default value.
    */
   public final String getGrossAmtFundCurr( int index, String defaultValue )
   {
      return _GrossAmtFundCurr[index] == null ? defaultValue : _GrossAmtFundCurr[index];
   }
    
   /**
    * Gets the array of Gross Amount in Fund Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross Amount in Fund Currency values.
    */
   public final String[] getGrossAmtFundCurrArray()
   {
      return _GrossAmtFundCurr;
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
    * Gets the Gross Amount in Settlement Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Gross Amount in Settlement Currency or null.
    */
   public final String getGrossAmtSettleCurr( int index )
   {
      return _GrossAmtSettleCurr[index];
   }
    
   /**
    * Gets the Gross Amount in Settlement Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gross Amount in Settlement Currency or the specified default value.
    */
   public final String getGrossAmtSettleCurr( int index, String defaultValue )
   {
      return _GrossAmtSettleCurr[index] == null ? defaultValue : _GrossAmtSettleCurr[index];
   }
    
   /**
    * Gets the array of Gross Amount in Settlement Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Gross Amount in Settlement Currency values.
    */
   public final String[] getGrossAmtSettleCurrArray()
   {
      return _GrossAmtSettleCurr;
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
    * Gets the Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rate or null.
    */
   public final String getRate( int index )
   {
      return _Rate[index];
   }
    
   /**
    * Gets the Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rate or the specified default value.
    */
   public final String getRate( int index, String defaultValue )
   {
      return _Rate[index] == null ? defaultValue : _Rate[index];
   }
    
   /**
    * Gets the array of Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rate values.
    */
   public final String[] getRateArray()
   {
      return _Rate;
   }
    
   /**
    * Gets the Settled Y/N field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settled Y/N or null.
    */
   public final Boolean getSettled( int index )
   {
      return _Settled[index];
   }
    
   /**
    * Gets the Settled Y/N field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled Y/N or the specified default value.
    */
   public final boolean getSettled( int index, boolean defaultValue )
   {
      return _Settled[index] == null ? defaultValue : _Settled[index].booleanValue();
   }
    
   /**
    * Gets the array of Settled Y/N fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled Y/N values.
    */
   public final Boolean[] getSettledArray()
   {
      return _Settled;
   }
    
   /**
    * Gets the Settled Units Balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settled Units Balance or null.
    */
   public final String getSettledUnitsBalance( int index )
   {
      return _SettledUnitsBalance[index];
   }
    
   /**
    * Gets the Settled Units Balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settled Units Balance or the specified default value.
    */
   public final String getSettledUnitsBalance( int index, String defaultValue )
   {
      return _SettledUnitsBalance[index] == null ? defaultValue : _SettledUnitsBalance[index];
   }
    
   /**
    * Gets the array of Settled Units Balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settled Units Balance values.
    */
   public final String[] getSettledUnitsBalanceArray()
   {
      return _SettledUnitsBalance;
   }
    
   /**
    * Gets the Total Units Balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Total Units Balance or null.
    */
   public final String getTotalUnitsBalance( int index )
   {
      return _TotalUnitsBalance[index];
   }
    
   /**
    * Gets the Total Units Balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Total Units Balance or the specified default value.
    */
   public final String getTotalUnitsBalance( int index, String defaultValue )
   {
      return _TotalUnitsBalance[index] == null ? defaultValue : _TotalUnitsBalance[index];
   }
    
   /**
    * Gets the array of Total Units Balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Total Units Balance values.
    */
   public final String[] getTotalUnitsBalanceArray()
   {
      return _TotalUnitsBalance;
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
      _TransID = resizeArray( _TransID, _RepeatCount );
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _FirstName = resizeArray( _FirstName, _RepeatCount );
      _LastName = resizeArray( _LastName, _RepeatCount );
      _FundCurrency = resizeArray( _FundCurrency, _RepeatCount );
      _GrossAmtFundCurr = resizeArray( _GrossAmtFundCurr, _RepeatCount );
      _SettleDate = resizeArray( _SettleDate, _RepeatCount );
      _SettleCurrency = resizeArray( _SettleCurrency, _RepeatCount );
      _GrossAmtSettleCurr = resizeArray( _GrossAmtSettleCurr, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _Rate = resizeArray( _Rate, _RepeatCount );
      _Settled = resizeArray( _Settled, _RepeatCount );
      _SettledUnitsBalance = resizeArray( _SettledUnitsBalance, _RepeatCount );
      _TotalUnitsBalance = resizeArray( _TotalUnitsBalance, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TransType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossAmtFundCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SettleCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GrossAmtSettleCurr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Rate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Settled[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SettledUnitsBalance[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TotalUnitsBalance[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
