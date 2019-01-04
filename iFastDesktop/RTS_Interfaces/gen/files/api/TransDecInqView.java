
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * TransDec Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TransDecInq.doc">TransDecInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TransDecInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Decimal Type member array.
    */
   private String[] _DecimalType = null;
   
   /**
    * Decimal Type Description member array.
    */
   private String[] _DecimalTypeDesc = null;
   
   /**
    * Decimal Value member array.
    */
   private String[] _DecimalValue = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   

   /**
    * Constructs the TransDecInqView object.
    * 
    */
   public TransDecInqView()
   {
      super ( new TransDecInqRequest() );
   }

   /**
    * Constructs the TransDecInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TransDecInqView( String hostEncoding )
   {
      super ( new TransDecInqRequest( hostEncoding ) );
   }

   /**
    * Gets the TransDecInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TransDecInqRequest object.
    */
   public final TransDecInqRequest getRequest()
   {
      return (TransDecInqRequest)getIFastRequest();
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
    * Gets the Decimal Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Decimal Type or null.
    */
   public final String getDecimalType( int index )
   {
      return _DecimalType[index];
   }
    
   /**
    * Gets the Decimal Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Decimal Type or the specified default value.
    */
   public final String getDecimalType( int index, String defaultValue )
   {
      return _DecimalType[index] == null ? defaultValue : _DecimalType[index];
   }
    
   /**
    * Gets the array of Decimal Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Decimal Type values.
    */
   public final String[] getDecimalTypeArray()
   {
      return _DecimalType;
   }
    
   /**
    * Gets the Decimal Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Decimal Type Description or null.
    */
   public final String getDecimalTypeDesc( int index )
   {
      return _DecimalTypeDesc[index];
   }
    
   /**
    * Gets the Decimal Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Decimal Type Description or the specified default value.
    */
   public final String getDecimalTypeDesc( int index, String defaultValue )
   {
      return _DecimalTypeDesc[index] == null ? defaultValue : _DecimalTypeDesc[index];
   }
    
   /**
    * Gets the array of Decimal Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Decimal Type Description values.
    */
   public final String[] getDecimalTypeDescArray()
   {
      return _DecimalTypeDesc;
   }
    
   /**
    * Gets the Decimal Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Decimal Value or null.
    */
   public final String getDecimalValue( int index )
   {
      return _DecimalValue[index];
   }
    
   /**
    * Gets the Decimal Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Decimal Value or the specified default value.
    */
   public final String getDecimalValue( int index, String defaultValue )
   {
      return _DecimalValue[index] == null ? defaultValue : _DecimalValue[index];
   }
    
   /**
    * Gets the array of Decimal Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Decimal Value values.
    */
   public final String[] getDecimalValueArray()
   {
      return _DecimalValue;
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
      
      _DecimalType = resizeArray( _DecimalType, _RepeatCount );
      _DecimalTypeDesc = resizeArray( _DecimalTypeDesc, _RepeatCount );
      _DecimalValue = resizeArray( _DecimalValue, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _DecimalType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DecimalTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DecimalValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
