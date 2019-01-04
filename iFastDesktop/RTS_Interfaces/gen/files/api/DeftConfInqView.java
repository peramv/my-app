
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Default Config Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DeftConfInq.doc">DeftConfInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DeftConfInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * FldName member array.
    */
   private String[] _RespFldName = null;
   
   /**
    * DefValue member array.
    */
   private String[] _DefValue = null;
   

   /**
    * Constructs the DeftConfInqView object.
    * 
    */
   public DeftConfInqView()
   {
      super ( new DeftConfInqRequest() );
   }

   /**
    * Constructs the DeftConfInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DeftConfInqView( String hostEncoding )
   {
      super ( new DeftConfInqRequest( hostEncoding ) );
   }

   /**
    * Gets the DeftConfInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DeftConfInqRequest object.
    */
   public final DeftConfInqRequest getRequest()
   {
      return (DeftConfInqRequest)getIFastRequest();
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
    * Gets the FldName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FldName or null.
    */
   public final String getRespFldName( int index )
   {
      return _RespFldName[index];
   }
    
   /**
    * Gets the FldName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FldName or the specified default value.
    */
   public final String getRespFldName( int index, String defaultValue )
   {
      return _RespFldName[index] == null ? defaultValue : _RespFldName[index];
   }
    
   /**
    * Gets the array of FldName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FldName values.
    */
   public final String[] getRespFldNameArray()
   {
      return _RespFldName;
   }
    
   /**
    * Gets the DefValue field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DefValue or null.
    */
   public final String getDefValue( int index )
   {
      return _DefValue[index];
   }
    
   /**
    * Gets the DefValue field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DefValue or the specified default value.
    */
   public final String getDefValue( int index, String defaultValue )
   {
      return _DefValue[index] == null ? defaultValue : _DefValue[index];
   }
    
   /**
    * Gets the array of DefValue fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DefValue values.
    */
   public final String[] getDefValueArray()
   {
      return _DefValue;
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
      
      _RespFldName = resizeArray( _RespFldName, _RepeatCount );
      _DefValue = resizeArray( _DefValue, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RespFldName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DefValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
