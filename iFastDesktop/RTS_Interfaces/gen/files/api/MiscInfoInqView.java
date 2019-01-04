
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Misc-Info Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/MiscInfoInq.doc">MiscInfoInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MiscInfoInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Group Code member array.
    */
   private String[] _rxGroupCode = null;
   
   /**
    * Misc-Info Code member array.
    */
   private String[] _MiscCode = null;
   
   /**
    * Misc-Info Description member array.
    */
   private String[] _MiscDesc = null;
   
   /**
    * Category member array.
    */
   private String[] _MiscCategory = null;
   

   /**
    * Constructs the MiscInfoInqView object.
    * 
    */
   public MiscInfoInqView()
   {
      super ( new MiscInfoInqRequest() );
   }

   /**
    * Constructs the MiscInfoInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MiscInfoInqView( String hostEncoding )
   {
      super ( new MiscInfoInqRequest( hostEncoding ) );
   }

   /**
    * Gets the MiscInfoInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MiscInfoInqRequest object.
    */
   public final MiscInfoInqRequest getRequest()
   {
      return (MiscInfoInqRequest)getIFastRequest();
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
    * Gets the Group Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Code or null.
    */
   public final String getrxGroupCode( int index )
   {
      return _rxGroupCode[index];
   }
    
   /**
    * Gets the Group Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Code or the specified default value.
    */
   public final String getrxGroupCode( int index, String defaultValue )
   {
      return _rxGroupCode[index] == null ? defaultValue : _rxGroupCode[index];
   }
    
   /**
    * Gets the array of Group Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Code values.
    */
   public final String[] getrxGroupCodeArray()
   {
      return _rxGroupCode;
   }
    
   /**
    * Gets the Misc-Info Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Misc-Info Code or null.
    */
   public final String getMiscCode( int index )
   {
      return _MiscCode[index];
   }
    
   /**
    * Gets the Misc-Info Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Misc-Info Code or the specified default value.
    */
   public final String getMiscCode( int index, String defaultValue )
   {
      return _MiscCode[index] == null ? defaultValue : _MiscCode[index];
   }
    
   /**
    * Gets the array of Misc-Info Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Misc-Info Code values.
    */
   public final String[] getMiscCodeArray()
   {
      return _MiscCode;
   }
    
   /**
    * Gets the Misc-Info Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Misc-Info Description or null.
    */
   public final String getMiscDesc( int index )
   {
      return _MiscDesc[index];
   }
    
   /**
    * Gets the Misc-Info Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Misc-Info Description or the specified default value.
    */
   public final String getMiscDesc( int index, String defaultValue )
   {
      return _MiscDesc[index] == null ? defaultValue : _MiscDesc[index];
   }
    
   /**
    * Gets the array of Misc-Info Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Misc-Info Description values.
    */
   public final String[] getMiscDescArray()
   {
      return _MiscDesc;
   }
    
   /**
    * Gets the Category field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Category or null.
    */
   public final String getMiscCategory( int index )
   {
      return _MiscCategory[index];
   }
    
   /**
    * Gets the Category field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Category or the specified default value.
    */
   public final String getMiscCategory( int index, String defaultValue )
   {
      return _MiscCategory[index] == null ? defaultValue : _MiscCategory[index];
   }
    
   /**
    * Gets the array of Category fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Category values.
    */
   public final String[] getMiscCategoryArray()
   {
      return _MiscCategory;
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
      
      _rxGroupCode = resizeArray( _rxGroupCode, _RepeatCount );
      _MiscCode = resizeArray( _MiscCode, _RepeatCount );
      _MiscDesc = resizeArray( _MiscDesc, _RepeatCount );
      _MiscCategory = resizeArray( _MiscCategory, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxGroupCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MiscCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MiscDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MiscCategory[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
