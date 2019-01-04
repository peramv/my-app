
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Scheduled Job Parameters view.
 * For additional view information see <A HREF="../../../../viewspecs/PrintersInq.doc">PrintersInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PrintersInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Parameter Type member array.
    */
   private String[] _ParamType = null;
   
   /**
    * Parameter Value member array.
    */
   private String[] _ParamValue = null;
   
   /**
    * Include member array.
    */
   private Boolean[] _Include = null;
   

   /**
    * Constructs the PrintersInqView object.
    * 
    */
   public PrintersInqView()
   {
      super ( new PrintersInqRequest() );
   }

   /**
    * Constructs the PrintersInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PrintersInqView( String hostEncoding )
   {
      super ( new PrintersInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PrintersInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PrintersInqRequest object.
    */
   public final PrintersInqRequest getRequest()
   {
      return (PrintersInqRequest)getIFastRequest();
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
    * Gets the Parameter Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Parameter Type or null.
    */
   public final String getParamType( int index )
   {
      return _ParamType[index];
   }
    
   /**
    * Gets the Parameter Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Parameter Type or the specified default value.
    */
   public final String getParamType( int index, String defaultValue )
   {
      return _ParamType[index] == null ? defaultValue : _ParamType[index];
   }
    
   /**
    * Gets the array of Parameter Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Parameter Type values.
    */
   public final String[] getParamTypeArray()
   {
      return _ParamType;
   }
    
   /**
    * Gets the Parameter Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Parameter Value or null.
    */
   public final String getParamValue( int index )
   {
      return _ParamValue[index];
   }
    
   /**
    * Gets the Parameter Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Parameter Value or the specified default value.
    */
   public final String getParamValue( int index, String defaultValue )
   {
      return _ParamValue[index] == null ? defaultValue : _ParamValue[index];
   }
    
   /**
    * Gets the array of Parameter Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Parameter Value values.
    */
   public final String[] getParamValueArray()
   {
      return _ParamValue;
   }
    
   /**
    * Gets the Include field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Include or null.
    */
   public final Boolean getInclude( int index )
   {
      return _Include[index];
   }
    
   /**
    * Gets the Include field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Include or the specified default value.
    */
   public final boolean getInclude( int index, boolean defaultValue )
   {
      return _Include[index] == null ? defaultValue : _Include[index].booleanValue();
   }
    
   /**
    * Gets the array of Include fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Include values.
    */
   public final Boolean[] getIncludeArray()
   {
      return _Include;
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
      
      _ParamType = resizeArray( _ParamType, _RepeatCount );
      _ParamValue = resizeArray( _ParamValue, _RepeatCount );
      _Include = resizeArray( _Include, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ParamType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ParamValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Include[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
