
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Income Dividends view.
 * For additional view information see <A HREF="../../../../viewspecs/FundIncomeDividends.doc">FundIncomeDividends.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundIncomeDividendsView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Response Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Resposne Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Record Date member array.
    */
   private Date[] _RecordDate = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Dividend Rate member array.
    */
   private String[] _DividendRate = null;
   
   /**
    * ReinvestPrice member array.
    */
   private String[] _ReinvestPrice = null;
   
   /**
    * Pay Date member array.
    */
   private Date[] _PayDate = null;
   

   /**
    * Constructs the FundIncomeDividendsView object.
    * 
    */
   public FundIncomeDividendsView()
   {
      super ( new FundIncomeDividendsRequest() );
   }

   /**
    * Constructs the FundIncomeDividendsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundIncomeDividendsView( String hostEncoding )
   {
      super ( new FundIncomeDividendsRequest( hostEncoding ) );
   }

   /**
    * Gets the FundIncomeDividendsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundIncomeDividendsRequest object.
    */
   public final FundIncomeDividendsRequest getRequest()
   {
      return (FundIncomeDividendsRequest)getIFastRequest();
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
    * Gets the Response Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Response Fund Code or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Response Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Response Fund Code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Response Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Response Fund Code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Resposne Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Resposne Class Code or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Resposne Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Resposne Class Code or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Resposne Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Resposne Class Code values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Record Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Record Date or null.
    */
   public final Date getRecordDate( int index )
   {
      return _RecordDate[index];
   }
    
   /**
    * Gets the Record Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Date or the specified default value.
    */
   public final Date getRecordDate( int index, Date defaultValue )
   {
      return _RecordDate[index] == null ? defaultValue : _RecordDate[index];
   }
    
   /**
    * Gets the array of Record Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Record Date values.
    */
   public final Date[] getRecordDateArray()
   {
      return _RecordDate;
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
    * Gets the Dividend Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dividend Rate or null.
    */
   public final String getDividendRate( int index )
   {
      return _DividendRate[index];
   }
    
   /**
    * Gets the Dividend Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dividend Rate or the specified default value.
    */
   public final String getDividendRate( int index, String defaultValue )
   {
      return _DividendRate[index] == null ? defaultValue : _DividendRate[index];
   }
    
   /**
    * Gets the array of Dividend Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dividend Rate values.
    */
   public final String[] getDividendRateArray()
   {
      return _DividendRate;
   }
    
   /**
    * Gets the ReinvestPrice field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ReinvestPrice or null.
    */
   public final String getReinvestPrice( int index )
   {
      return _ReinvestPrice[index];
   }
    
   /**
    * Gets the ReinvestPrice field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ReinvestPrice or the specified default value.
    */
   public final String getReinvestPrice( int index, String defaultValue )
   {
      return _ReinvestPrice[index] == null ? defaultValue : _ReinvestPrice[index];
   }
    
   /**
    * Gets the array of ReinvestPrice fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ReinvestPrice values.
    */
   public final String[] getReinvestPriceArray()
   {
      return _ReinvestPrice;
   }
    
   /**
    * Gets the Pay Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pay Date or null.
    */
   public final Date getPayDate( int index )
   {
      return _PayDate[index];
   }
    
   /**
    * Gets the Pay Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pay Date or the specified default value.
    */
   public final Date getPayDate( int index, Date defaultValue )
   {
      return _PayDate[index] == null ? defaultValue : _PayDate[index];
   }
    
   /**
    * Gets the array of Pay Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pay Date values.
    */
   public final Date[] getPayDateArray()
   {
      return _PayDate;
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
      _RecordDate = resizeArray( _RecordDate, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _DividendRate = resizeArray( _DividendRate, _RepeatCount );
      _ReinvestPrice = resizeArray( _ReinvestPrice, _RepeatCount );
      _PayDate = resizeArray( _PayDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecordDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DividendRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReinvestPrice[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
