
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Rule based validation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RuleValInq.doc">RuleValInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RuleValInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * EOEErrCode member array.
    */
   private Integer[] _EOEErrCode = null;
   
   /**
    * EOEErrText member array.
    */
   private String[] _EOEErrText = null;
   

   /**
    * Constructs the RuleValInqView object.
    * 
    */
   public RuleValInqView()
   {
      super ( new RuleValInqRequest() );
   }

   /**
    * Constructs the RuleValInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RuleValInqView( String hostEncoding )
   {
      super ( new RuleValInqRequest( hostEncoding ) );
   }

   /**
    * Gets the RuleValInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RuleValInqRequest object.
    */
   public final RuleValInqRequest getRequest()
   {
      return (RuleValInqRequest)getIFastRequest();
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
    * Gets the EOEErrCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EOEErrCode or null.
    */
   public final Integer getEOEErrCode( int index )
   {
      return _EOEErrCode[index];
   }
    
   /**
    * Gets the EOEErrCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EOEErrCode or the specified default value.
    */
   public final int getEOEErrCode( int index, int defaultValue )
   {
      return _EOEErrCode[index] == null ? defaultValue : _EOEErrCode[index].intValue();
   }
    
   /**
    * Gets the array of EOEErrCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EOEErrCode values.
    */
   public final Integer[] getEOEErrCodeArray()
   {
      return _EOEErrCode;
   }
    
   /**
    * Gets the EOEErrText field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the EOEErrText or null.
    */
   public final String getEOEErrText( int index )
   {
      return _EOEErrText[index];
   }
    
   /**
    * Gets the EOEErrText field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EOEErrText or the specified default value.
    */
   public final String getEOEErrText( int index, String defaultValue )
   {
      return _EOEErrText[index] == null ? defaultValue : _EOEErrText[index];
   }
    
   /**
    * Gets the array of EOEErrText fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of EOEErrText values.
    */
   public final String[] getEOEErrTextArray()
   {
      return _EOEErrText;
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
      
      _EOEErrCode = resizeArray( _EOEErrCode, _RepeatCount );
      _EOEErrText = resizeArray( _EOEErrText, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _EOEErrCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EOEErrText[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
