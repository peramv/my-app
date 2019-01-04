
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * FATCA Regulation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FATCAReg.doc">FATCAReg.doc</A>.
 * 
 * @author RTS Generated
 */
public class FATCARegView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Regulation member array.
    */
   private String[] _FATCACode = null;
   
   /**
    * Regulation Description member array.
    */
   private String[] _FATCADesc = null;
   

   /**
    * Constructs the FATCARegView object.
    * 
    */
   public FATCARegView()
   {
      super ( new FATCARegRequest() );
   }

   /**
    * Constructs the FATCARegView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FATCARegView( String hostEncoding )
   {
      super ( new FATCARegRequest( hostEncoding ) );
   }

   /**
    * Gets the FATCARegRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FATCARegRequest object.
    */
   public final FATCARegRequest getRequest()
   {
      return (FATCARegRequest)getIFastRequest();
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
    * Gets the Regulation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Regulation or null.
    */
   public final String getFATCACode( int index )
   {
      return _FATCACode[index];
   }
    
   /**
    * Gets the Regulation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Regulation or the specified default value.
    */
   public final String getFATCACode( int index, String defaultValue )
   {
      return _FATCACode[index] == null ? defaultValue : _FATCACode[index];
   }
    
   /**
    * Gets the array of Regulation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Regulation values.
    */
   public final String[] getFATCACodeArray()
   {
      return _FATCACode;
   }
    
   /**
    * Gets the Regulation Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Regulation Description or null.
    */
   public final String getFATCADesc( int index )
   {
      return _FATCADesc[index];
   }
    
   /**
    * Gets the Regulation Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Regulation Description or the specified default value.
    */
   public final String getFATCADesc( int index, String defaultValue )
   {
      return _FATCADesc[index] == null ? defaultValue : _FATCADesc[index];
   }
    
   /**
    * Gets the array of Regulation Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Regulation Description values.
    */
   public final String[] getFATCADescArray()
   {
      return _FATCADesc;
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
      
      _FATCACode = resizeArray( _FATCACode, _RepeatCount );
      _FATCADesc = resizeArray( _FATCADesc, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _FATCACode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FATCADesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
