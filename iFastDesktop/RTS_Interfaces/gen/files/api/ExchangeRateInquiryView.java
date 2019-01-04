
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Exchange Rate Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ExchangeRateInquiry.doc">ExchangeRateInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class ExchangeRateInquiryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * From Currency1 member array.
    */
   private String[] _rxFromCurrency1 = null;
   
   /**
    * To Currency1 member array.
    */
   private String[] _rxToCurrency1 = null;
   
   /**
    * Exchange Rate1 member array.
    */
   private String[] _ExchRate1 = null;
   
   /**
    * Effective Date1 member array.
    */
   private Date[] _rxEffectiveDate1 = null;
   

   /**
    * Constructs the ExchangeRateInquiryView object.
    * 
    */
   public ExchangeRateInquiryView()
   {
      super ( new ExchangeRateInquiryRequest() );
   }

   /**
    * Constructs the ExchangeRateInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ExchangeRateInquiryView( String hostEncoding )
   {
      super ( new ExchangeRateInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the ExchangeRateInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ExchangeRateInquiryRequest object.
    */
   public final ExchangeRateInquiryRequest getRequest()
   {
      return (ExchangeRateInquiryRequest)getIFastRequest();
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
    * Gets the From Currency1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the From Currency1 or null.
    */
   public final String getrxFromCurrency1( int index )
   {
      return _rxFromCurrency1[index];
   }
    
   /**
    * Gets the From Currency1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the From Currency1 or the specified default value.
    */
   public final String getrxFromCurrency1( int index, String defaultValue )
   {
      return _rxFromCurrency1[index] == null ? defaultValue : _rxFromCurrency1[index];
   }
    
   /**
    * Gets the array of From Currency1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of From Currency1 values.
    */
   public final String[] getrxFromCurrency1Array()
   {
      return _rxFromCurrency1;
   }
    
   /**
    * Gets the To Currency1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the To Currency1 or null.
    */
   public final String getrxToCurrency1( int index )
   {
      return _rxToCurrency1[index];
   }
    
   /**
    * Gets the To Currency1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To Currency1 or the specified default value.
    */
   public final String getrxToCurrency1( int index, String defaultValue )
   {
      return _rxToCurrency1[index] == null ? defaultValue : _rxToCurrency1[index];
   }
    
   /**
    * Gets the array of To Currency1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of To Currency1 values.
    */
   public final String[] getrxToCurrency1Array()
   {
      return _rxToCurrency1;
   }
    
   /**
    * Gets the Exchange Rate1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exchange Rate1 or null.
    */
   public final String getExchRate1( int index )
   {
      return _ExchRate1[index];
   }
    
   /**
    * Gets the Exchange Rate1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exchange Rate1 or the specified default value.
    */
   public final String getExchRate1( int index, String defaultValue )
   {
      return _ExchRate1[index] == null ? defaultValue : _ExchRate1[index];
   }
    
   /**
    * Gets the array of Exchange Rate1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exchange Rate1 values.
    */
   public final String[] getExchRate1Array()
   {
      return _ExchRate1;
   }
    
   /**
    * Gets the Effective Date1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date1 or null.
    */
   public final Date getrxEffectiveDate1( int index )
   {
      return _rxEffectiveDate1[index];
   }
    
   /**
    * Gets the Effective Date1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date1 or the specified default value.
    */
   public final Date getrxEffectiveDate1( int index, Date defaultValue )
   {
      return _rxEffectiveDate1[index] == null ? defaultValue : _rxEffectiveDate1[index];
   }
    
   /**
    * Gets the array of Effective Date1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date1 values.
    */
   public final Date[] getrxEffectiveDate1Array()
   {
      return _rxEffectiveDate1;
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
      
      _rxFromCurrency1 = resizeArray( _rxFromCurrency1, _RepeatCount );
      _rxToCurrency1 = resizeArray( _rxToCurrency1, _RepeatCount );
      _ExchRate1 = resizeArray( _ExchRate1, _RepeatCount );
      _rxEffectiveDate1 = resizeArray( _rxEffectiveDate1, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFromCurrency1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxToCurrency1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchRate1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxEffectiveDate1[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
