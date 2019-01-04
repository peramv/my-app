
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * SEG Redemption/Transfer transaction Validations view.
 * For additional view information see <A HREF="../../../../viewspecs/SEGRdmTrfVal.doc">SEGRdmTrfVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class SEGRdmTrfValView extends IFastView implements Serializable
{

   private int _RespRepeatCount = 0;
   
   /**
    * Warning or Error Code member array.
    */
   private Integer[] _WarnCode = null;
   

   /**
    * Constructs the SEGRdmTrfValView object.
    * 
    */
   public SEGRdmTrfValView()
   {
      super ( new SEGRdmTrfValRequest() );
   }

   /**
    * Constructs the SEGRdmTrfValView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SEGRdmTrfValView( String hostEncoding )
   {
      super ( new SEGRdmTrfValRequest( hostEncoding ) );
   }

   /**
    * Gets the SEGRdmTrfValRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SEGRdmTrfValRequest object.
    */
   public final SEGRdmTrfValRequest getRequest()
   {
      return (SEGRdmTrfValRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RespRepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRespRepeatCount()
   {
      return _RespRepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRespRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RespRepeatCount += receivedRecordCount;
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
      int oldRespRepeatCount = _RespRepeatCount;
      decodeRespRepeatCount( responseBuffer );
      
      _WarnCode = resizeArray( _WarnCode, _RespRepeatCount );
        
      for (int x = oldRespRepeatCount ; x < _RespRepeatCount; x++)
      {
         _WarnCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
