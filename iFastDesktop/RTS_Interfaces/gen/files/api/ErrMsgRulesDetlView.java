
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Error Messages Rules view.
 * For additional view information see <A HREF="../../../../viewspecs/ErrMsgRulesDetl.doc">ErrMsgRulesDetl.doc</A>.
 * 
 * @author RTS Generated
 */
public class ErrMsgRulesDetlView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Error Number member array.
    */
   private Integer[] _ErrNum = null;
   
   /**
    * Error Message member array.
    */
   private String[] _ErrMsg = null;
   
   /**
    * Error severity member array.
    */
   private String[] _EWI = null;
   

   /**
    * Constructs the ErrMsgRulesDetlView object.
    * 
    */
   public ErrMsgRulesDetlView()
   {
      super ( new ErrMsgRulesDetlRequest() );
   }

   /**
    * Constructs the ErrMsgRulesDetlView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ErrMsgRulesDetlView( String hostEncoding )
   {
      super ( new ErrMsgRulesDetlRequest( hostEncoding ) );
   }

   /**
    * Gets the ErrMsgRulesDetlRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ErrMsgRulesDetlRequest object.
    */
   public final ErrMsgRulesDetlRequest getRequest()
   {
      return (ErrMsgRulesDetlRequest)getIFastRequest();
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
    * Gets the Error Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Error Number or null.
    */
   public final Integer getErrNum( int index )
   {
      return _ErrNum[index];
   }
    
   /**
    * Gets the Error Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error Number or the specified default value.
    */
   public final int getErrNum( int index, int defaultValue )
   {
      return _ErrNum[index] == null ? defaultValue : _ErrNum[index].intValue();
   }
    
   /**
    * Gets the array of Error Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Error Number values.
    */
   public final Integer[] getErrNumArray()
   {
      return _ErrNum;
   }
    
   /**
    * Gets the Error Message field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Error Message or null.
    */
   public final String getErrMsg( int index )
   {
      return _ErrMsg[index];
   }
    
   /**
    * Gets the Error Message field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error Message or the specified default value.
    */
   public final String getErrMsg( int index, String defaultValue )
   {
      return _ErrMsg[index] == null ? defaultValue : _ErrMsg[index];
   }
    
   /**
    * Gets the array of Error Message fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Error Message values.
    */
   public final String[] getErrMsgArray()
   {
      return _ErrMsg;
   }
    
   /**
    * Gets the Error severity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Error severity or null.
    */
   public final String getEWI( int index )
   {
      return _EWI[index];
   }
    
   /**
    * Gets the Error severity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error severity or the specified default value.
    */
   public final String getEWI( int index, String defaultValue )
   {
      return _EWI[index] == null ? defaultValue : _EWI[index];
   }
    
   /**
    * Gets the array of Error severity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Error severity values.
    */
   public final String[] getEWIArray()
   {
      return _EWI;
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
      
      _ErrNum = resizeArray( _ErrNum, _RepeatCount );
      _ErrMsg = resizeArray( _ErrMsg, _RepeatCount );
      _EWI = resizeArray( _EWI, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ErrNum[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ErrMsg[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EWI[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
