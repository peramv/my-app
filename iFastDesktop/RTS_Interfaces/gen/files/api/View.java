
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Transaction Fees Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/.doc">.doc</A>.
 * 
 * @author RTS Generated
 */
public class View extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Trans Number member array.
    */
   private Integer[] _rxTransNumber = null;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAccountNum = null;
   
   /**
    * Fund member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class member array.
    */
   private String[] _ClassCode = null;
   
   /**
    * Fee Code member array.
    */
   private Integer[] _FeeCode = null;
   
   /**
    * Fee Type member array.
    */
   private String[] _FeeType = null;
   
   /**
    * Fee Rate member array.
    */
   private String[] _FeeRate = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Charge Option member array.
    */
   private String[] _ChargeOption = null;
   
   /**
    * Trade Fee Option member array.
    */
   private String[] _TradeFeeOption = null;
   
   /**
    * Trans Fee Id member array.
    */
   private Integer[] _TransFeeId = null;
   
   /**
    * Orig Fee Type member array.
    */
   private String[] _OrigFeeType = null;
   
   /**
    * Orig Fee Rate member array.
    */
   private String[] _OrigFeeRate = null;
   

   /**
    * Constructs the View object.
    * 
    */
   public View()
   {
      super ( new Request() );
   }

   /**
    * Constructs the View object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public View( String hostEncoding )
   {
      super ( new Request( hostEncoding ) );
   }

   /**
    * Gets the Request object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The Request object.
    */
   public final Request getRequest()
   {
      return (Request)getIFastRequest();
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
    * Gets the Trans Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trans Number or null.
    */
   public final Integer getrxTransNumber( int index )
   {
      return _rxTransNumber[index];
   }
    
   /**
    * Gets the Trans Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trans Number or the specified default value.
    */
   public final int getrxTransNumber( int index, int defaultValue )
   {
      return _rxTransNumber[index] == null ? defaultValue : _rxTransNumber[index].intValue();
   }
    
   /**
    * Gets the array of Trans Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trans Number values.
    */
   public final Integer[] getrxTransNumberArray()
   {
      return _rxTransNumber;
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
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
   }
    
   /**
    * Gets the Fee Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Code or null.
    */
   public final Integer getFeeCode( int index )
   {
      return _FeeCode[index];
   }
    
   /**
    * Gets the Fee Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Code or the specified default value.
    */
   public final int getFeeCode( int index, int defaultValue )
   {
      return _FeeCode[index] == null ? defaultValue : _FeeCode[index].intValue();
   }
    
   /**
    * Gets the array of Fee Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Code values.
    */
   public final Integer[] getFeeCodeArray()
   {
      return _FeeCode;
   }
    
   /**
    * Gets the Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Type or null.
    */
   public final String getFeeType( int index )
   {
      return _FeeType[index];
   }
    
   /**
    * Gets the Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Type or the specified default value.
    */
   public final String getFeeType( int index, String defaultValue )
   {
      return _FeeType[index] == null ? defaultValue : _FeeType[index];
   }
    
   /**
    * Gets the array of Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Type values.
    */
   public final String[] getFeeTypeArray()
   {
      return _FeeType;
   }
    
   /**
    * Gets the Fee Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Rate or null.
    */
   public final String getFeeRate( int index )
   {
      return _FeeRate[index];
   }
    
   /**
    * Gets the Fee Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Rate or the specified default value.
    */
   public final String getFeeRate( int index, String defaultValue )
   {
      return _FeeRate[index] == null ? defaultValue : _FeeRate[index];
   }
    
   /**
    * Gets the array of Fee Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Rate values.
    */
   public final String[] getFeeRateArray()
   {
      return _FeeRate;
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Charge Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Charge Option or null.
    */
   public final String getChargeOption( int index )
   {
      return _ChargeOption[index];
   }
    
   /**
    * Gets the Charge Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Charge Option or the specified default value.
    */
   public final String getChargeOption( int index, String defaultValue )
   {
      return _ChargeOption[index] == null ? defaultValue : _ChargeOption[index];
   }
    
   /**
    * Gets the array of Charge Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Charge Option values.
    */
   public final String[] getChargeOptionArray()
   {
      return _ChargeOption;
   }
    
   /**
    * Gets the Trade Fee Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Fee Option or null.
    */
   public final String getTradeFeeOption( int index )
   {
      return _TradeFeeOption[index];
   }
    
   /**
    * Gets the Trade Fee Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Fee Option or the specified default value.
    */
   public final String getTradeFeeOption( int index, String defaultValue )
   {
      return _TradeFeeOption[index] == null ? defaultValue : _TradeFeeOption[index];
   }
    
   /**
    * Gets the array of Trade Fee Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Fee Option values.
    */
   public final String[] getTradeFeeOptionArray()
   {
      return _TradeFeeOption;
   }
    
   /**
    * Gets the Trans Fee Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trans Fee Id or null.
    */
   public final Integer getTransFeeId( int index )
   {
      return _TransFeeId[index];
   }
    
   /**
    * Gets the Trans Fee Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trans Fee Id or the specified default value.
    */
   public final int getTransFeeId( int index, int defaultValue )
   {
      return _TransFeeId[index] == null ? defaultValue : _TransFeeId[index].intValue();
   }
    
   /**
    * Gets the array of Trans Fee Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trans Fee Id values.
    */
   public final Integer[] getTransFeeIdArray()
   {
      return _TransFeeId;
   }
    
   /**
    * Gets the Orig Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Orig Fee Type or null.
    */
   public final String getOrigFeeType( int index )
   {
      return _OrigFeeType[index];
   }
    
   /**
    * Gets the Orig Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Orig Fee Type or the specified default value.
    */
   public final String getOrigFeeType( int index, String defaultValue )
   {
      return _OrigFeeType[index] == null ? defaultValue : _OrigFeeType[index];
   }
    
   /**
    * Gets the array of Orig Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Orig Fee Type values.
    */
   public final String[] getOrigFeeTypeArray()
   {
      return _OrigFeeType;
   }
    
   /**
    * Gets the Orig Fee Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Orig Fee Rate or null.
    */
   public final String getOrigFeeRate( int index )
   {
      return _OrigFeeRate[index];
   }
    
   /**
    * Gets the Orig Fee Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Orig Fee Rate or the specified default value.
    */
   public final String getOrigFeeRate( int index, String defaultValue )
   {
      return _OrigFeeRate[index] == null ? defaultValue : _OrigFeeRate[index];
   }
    
   /**
    * Gets the array of Orig Fee Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Orig Fee Rate values.
    */
   public final String[] getOrigFeeRateArray()
   {
      return _OrigFeeRate;
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
      
      _rxTransNumber = resizeArray( _rxTransNumber, _RepeatCount );
      _rxAccountNum = resizeArray( _rxAccountNum, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
      _FeeCode = resizeArray( _FeeCode, _RepeatCount );
      _FeeType = resizeArray( _FeeType, _RepeatCount );
      _FeeRate = resizeArray( _FeeRate, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _ChargeOption = resizeArray( _ChargeOption, _RepeatCount );
      _TradeFeeOption = resizeArray( _TradeFeeOption, _RepeatCount );
      _TransFeeId = resizeArray( _TransFeeId, _RepeatCount );
      _OrigFeeType = resizeArray( _OrigFeeType, _RepeatCount );
      _OrigFeeRate = resizeArray( _OrigFeeRate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxTransNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxAccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ChargeOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TradeFeeOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TransFeeId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _OrigFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OrigFeeRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
