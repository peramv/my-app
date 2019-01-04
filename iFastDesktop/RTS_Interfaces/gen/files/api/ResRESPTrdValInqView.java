
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Request File for RESP Trading Validation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ResRESPTrdValInq.doc">ResRESPTrdValInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ResRESPTrdValInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Warning or Error Code member array.
    */
   private Integer[] _WarnCode = null;
   
   /**
    * Warning or Error Parameter 1 member array.
    */
   private String[] _WarnParam1 = null;
   
   /**
    * Warning or Error Parameter 2 member array.
    */
   private String[] _WarnParam2 = null;
   

   /**
    * Constructs the ResRESPTrdValInqView object.
    * 
    */
   public ResRESPTrdValInqView()
   {
      super ( new ResRESPTrdValInqRequest() );
   }

   /**
    * Constructs the ResRESPTrdValInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ResRESPTrdValInqView( String hostEncoding )
   {
      super ( new ResRESPTrdValInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ResRESPTrdValInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ResRESPTrdValInqRequest object.
    */
   public final ResRESPTrdValInqRequest getRequest()
   {
      return (ResRESPTrdValInqRequest)getIFastRequest();
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
    * Gets the Warning or Error Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Warning or Error Code or null.
    */
   public final Integer getWarnCode( int index )
   {
      return _WarnCode[index];
   }
    
   /**
    * Gets the Warning or Error Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning or Error Code or the specified default value.
    */
   public final int getWarnCode( int index, int defaultValue )
   {
      return _WarnCode[index] == null ? defaultValue : _WarnCode[index].intValue();
   }
    
   /**
    * Gets the array of Warning or Error Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Warning or Error Code values.
    */
   public final Integer[] getWarnCodeArray()
   {
      return _WarnCode;
   }
    
   /**
    * Gets the Warning or Error Parameter 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Warning or Error Parameter 1 or null.
    */
   public final String getWarnParam1( int index )
   {
      return _WarnParam1[index];
   }
    
   /**
    * Gets the Warning or Error Parameter 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning or Error Parameter 1 or the specified default value.
    */
   public final String getWarnParam1( int index, String defaultValue )
   {
      return _WarnParam1[index] == null ? defaultValue : _WarnParam1[index];
   }
    
   /**
    * Gets the array of Warning or Error Parameter 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Warning or Error Parameter 1 values.
    */
   public final String[] getWarnParam1Array()
   {
      return _WarnParam1;
   }
    
   /**
    * Gets the Warning or Error Parameter 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Warning or Error Parameter 2 or null.
    */
   public final String getWarnParam2( int index )
   {
      return _WarnParam2[index];
   }
    
   /**
    * Gets the Warning or Error Parameter 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning or Error Parameter 2 or the specified default value.
    */
   public final String getWarnParam2( int index, String defaultValue )
   {
      return _WarnParam2[index] == null ? defaultValue : _WarnParam2[index];
   }
    
   /**
    * Gets the array of Warning or Error Parameter 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Warning or Error Parameter 2 values.
    */
   public final String[] getWarnParam2Array()
   {
      return _WarnParam2;
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
      
      _WarnCode = resizeArray( _WarnCode, _RepeatCount );
      _WarnParam1 = resizeArray( _WarnParam1, _RepeatCount );
      _WarnParam2 = resizeArray( _WarnParam2, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _WarnCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _WarnParam1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WarnParam2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
