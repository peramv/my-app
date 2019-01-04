
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Province List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ProvinceInq.doc">ProvinceInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ProvinceInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Province member array.
    */
   private String[] _Province = null;
   
   /**
    * Province Description member array.
    */
   private String[] _ProvinceDesc = null;
   
   /**
    * 'PE' Group Code for Province member array.
    */
   private String[] _PEGroupCode = null;
   

   /**
    * Constructs the ProvinceInqView object.
    * 
    */
   public ProvinceInqView()
   {
      super ( new ProvinceInqRequest() );
   }

   /**
    * Constructs the ProvinceInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ProvinceInqView( String hostEncoding )
   {
      super ( new ProvinceInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ProvinceInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ProvinceInqRequest object.
    */
   public final ProvinceInqRequest getRequest()
   {
      return (ProvinceInqRequest)getIFastRequest();
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
    * Gets the Province field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Province or null.
    */
   public final String getProvince( int index )
   {
      return _Province[index];
   }
    
   /**
    * Gets the Province field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Province or the specified default value.
    */
   public final String getProvince( int index, String defaultValue )
   {
      return _Province[index] == null ? defaultValue : _Province[index];
   }
    
   /**
    * Gets the array of Province fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Province values.
    */
   public final String[] getProvinceArray()
   {
      return _Province;
   }
    
   /**
    * Gets the Province Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Province Description or null.
    */
   public final String getProvinceDesc( int index )
   {
      return _ProvinceDesc[index];
   }
    
   /**
    * Gets the Province Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Province Description or the specified default value.
    */
   public final String getProvinceDesc( int index, String defaultValue )
   {
      return _ProvinceDesc[index] == null ? defaultValue : _ProvinceDesc[index];
   }
    
   /**
    * Gets the array of Province Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Province Description values.
    */
   public final String[] getProvinceDescArray()
   {
      return _ProvinceDesc;
   }
    
   /**
    * Gets the 'PE' Group Code for Province field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the 'PE' Group Code for Province or null.
    */
   public final String getPEGroupCode( int index )
   {
      return _PEGroupCode[index];
   }
    
   /**
    * Gets the 'PE' Group Code for Province field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the 'PE' Group Code for Province or the specified default value.
    */
   public final String getPEGroupCode( int index, String defaultValue )
   {
      return _PEGroupCode[index] == null ? defaultValue : _PEGroupCode[index];
   }
    
   /**
    * Gets the array of 'PE' Group Code for Province fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of 'PE' Group Code for Province values.
    */
   public final String[] getPEGroupCodeArray()
   {
      return _PEGroupCode;
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
      
      _Province = resizeArray( _Province, _RepeatCount );
      _ProvinceDesc = resizeArray( _ProvinceDesc, _RepeatCount );
      _PEGroupCode = resizeArray( _PEGroupCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _Province[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProvinceDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PEGroupCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
