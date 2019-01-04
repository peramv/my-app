
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Network Config Detail Enquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/NetConfDetlInq.doc">NetConfDetlInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class NetConfDetlInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * NetworkID member array.
    */
   private String[] _NetworkID = null;
   
   /**
    * NetworkConfigType member array.
    */
   private String[] _NetworkConfigType = null;
   
   /**
    * NetworkConfigValue member array.
    */
   private String[] _NetworkConfigValue = null;
   

   /**
    * Constructs the NetConfDetlInqView object.
    * 
    */
   public NetConfDetlInqView()
   {
      super ( new NetConfDetlInqRequest() );
   }

   /**
    * Constructs the NetConfDetlInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public NetConfDetlInqView( String hostEncoding )
   {
      super ( new NetConfDetlInqRequest( hostEncoding ) );
   }

   /**
    * Gets the NetConfDetlInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The NetConfDetlInqRequest object.
    */
   public final NetConfDetlInqRequest getRequest()
   {
      return (NetConfDetlInqRequest)getIFastRequest();
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
    * Gets the NetworkID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NetworkID or null.
    */
   public final String getNetworkID( int index )
   {
      return _NetworkID[index];
   }
    
   /**
    * Gets the NetworkID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetworkID or the specified default value.
    */
   public final String getNetworkID( int index, String defaultValue )
   {
      return _NetworkID[index] == null ? defaultValue : _NetworkID[index];
   }
    
   /**
    * Gets the array of NetworkID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NetworkID values.
    */
   public final String[] getNetworkIDArray()
   {
      return _NetworkID;
   }
    
   /**
    * Gets the NetworkConfigType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NetworkConfigType or null.
    */
   public final String getNetworkConfigType( int index )
   {
      return _NetworkConfigType[index];
   }
    
   /**
    * Gets the NetworkConfigType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetworkConfigType or the specified default value.
    */
   public final String getNetworkConfigType( int index, String defaultValue )
   {
      return _NetworkConfigType[index] == null ? defaultValue : _NetworkConfigType[index];
   }
    
   /**
    * Gets the array of NetworkConfigType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NetworkConfigType values.
    */
   public final String[] getNetworkConfigTypeArray()
   {
      return _NetworkConfigType;
   }
    
   /**
    * Gets the NetworkConfigValue field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NetworkConfigValue or null.
    */
   public final String getNetworkConfigValue( int index )
   {
      return _NetworkConfigValue[index];
   }
    
   /**
    * Gets the NetworkConfigValue field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetworkConfigValue or the specified default value.
    */
   public final String getNetworkConfigValue( int index, String defaultValue )
   {
      return _NetworkConfigValue[index] == null ? defaultValue : _NetworkConfigValue[index];
   }
    
   /**
    * Gets the array of NetworkConfigValue fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NetworkConfigValue values.
    */
   public final String[] getNetworkConfigValueArray()
   {
      return _NetworkConfigValue;
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
      
      _NetworkID = resizeArray( _NetworkID, _RepeatCount );
      _NetworkConfigType = resizeArray( _NetworkConfigType, _RepeatCount );
      _NetworkConfigValue = resizeArray( _NetworkConfigValue, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _NetworkID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetworkConfigType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetworkConfigValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
