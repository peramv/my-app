
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Translation Info List view.
 * For additional view information see <A HREF="../../../../viewspecs/TranslationInfoList.doc">TranslationInfoList.doc</A>.
 * 
 * @author RTS Generated
 */
public class TranslationInfoListView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Translation Code member array.
    */
   private String[] _TranslationCode = null;
   
   /**
    * Description member array.
    */
   private String[] _Description = null;
   

   /**
    * Constructs the TranslationInfoListView object.
    * 
    */
   public TranslationInfoListView()
   {
      super ( new TranslationInfoListRequest() );
   }

   /**
    * Constructs the TranslationInfoListView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TranslationInfoListView( String hostEncoding )
   {
      super ( new TranslationInfoListRequest( hostEncoding ) );
   }

   /**
    * Gets the TranslationInfoListRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TranslationInfoListRequest object.
    */
   public final TranslationInfoListRequest getRequest()
   {
      return (TranslationInfoListRequest)getIFastRequest();
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
    * Gets the Translation Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Translation Code or null.
    */
   public final String getTranslationCode( int index )
   {
      return _TranslationCode[index];
   }
    
   /**
    * Gets the Translation Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Translation Code or the specified default value.
    */
   public final String getTranslationCode( int index, String defaultValue )
   {
      return _TranslationCode[index] == null ? defaultValue : _TranslationCode[index];
   }
    
   /**
    * Gets the array of Translation Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Translation Code values.
    */
   public final String[] getTranslationCodeArray()
   {
      return _TranslationCode;
   }
    
   /**
    * Gets the Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Description or null.
    */
   public final String getDescription( int index )
   {
      return _Description[index];
   }
    
   /**
    * Gets the Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Description or the specified default value.
    */
   public final String getDescription( int index, String defaultValue )
   {
      return _Description[index] == null ? defaultValue : _Description[index];
   }
    
   /**
    * Gets the array of Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Description values.
    */
   public final String[] getDescriptionArray()
   {
      return _Description;
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
      
      _TranslationCode = resizeArray( _TranslationCode, _RepeatCount );
      _Description = resizeArray( _Description, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TranslationCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Description[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
