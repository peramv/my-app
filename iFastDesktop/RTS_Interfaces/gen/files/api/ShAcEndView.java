
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Share/Acct Bus Group Upd end pers view.
 * For additional view information see <A HREF="../../../../viewspecs/ShAcEnd.doc">ShAcEnd.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShAcEndView extends IFastView implements Serializable
{

   /**
    * Update status member variable.
    */
   private Boolean _UpdateStatus = null;
   
   /**
    * Warning Message Code member variable.
    */
   private Integer _WarnCode1 = null;
   
   /**
    * Warning Message member variable.
    */
   private String _WarnDesc1 = null;
   
   /**
    * Warning Message Code member variable.
    */
   private Integer _WarnCode2 = null;
   
   /**
    * Warning Message member variable.
    */
   private String _WarnDesc2 = null;
   
   /**
    * Warning Message Code member variable.
    */
   private Integer _WarnCode3 = null;
   
   /**
    * Warning Message member variable.
    */
   private String _WarnDesc3 = null;
   
   /**
    * Warning Message Code member variable.
    */
   private Integer _WarnCode4 = null;
   
   /**
    * Warning Message member variable.
    */
   private String _WarnDesc4 = null;
   
   /**
    * Warning Message Code member variable.
    */
   private Integer _WarnCode5 = null;
   
   /**
    * Warning Message member variable.
    */
   private String _WarnDesc5 = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Key Type member array.
    */
   private String[] _KeyType = null;
   
   /**
    * Temporary Value member array.
    */
   private String[] _TempValue = null;
   
   /**
    * Permanent Value member array.
    */
   private String[] _PermValue = null;
   

   /**
    * Constructs the ShAcEndView object.
    * 
    */
   public ShAcEndView()
   {
      super ( new ShAcEndRequest() );
   }

   /**
    * Constructs the ShAcEndView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShAcEndView( String hostEncoding )
   {
      super ( new ShAcEndRequest( hostEncoding ) );
   }

   /**
    * Gets the ShAcEndRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShAcEndRequest object.
    */
   public final ShAcEndRequest getRequest()
   {
      return (ShAcEndRequest)getIFastRequest();
   }
        
   /**
    * Gets the Update status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Update status or null.
    */
   public final Boolean getUpdateStatus()
   {
      return _UpdateStatus;
   }
	
   /**
    * Gets the Update status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Update status or the specified default value.
    */
   public final boolean getUpdateStatus( boolean defaultValue )
   {
      return _UpdateStatus == null ? defaultValue : _UpdateStatus.booleanValue();
   }
                  
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code or null.
    */
   public final Integer getWarnCode1()
   {
      return _WarnCode1;
   }
	
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code or the specified default value.
    */
   public final int getWarnCode1( int defaultValue )
   {
      return _WarnCode1 == null ? defaultValue : _WarnCode1.intValue();
   }
                  
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message or null.
    */
   public final String getWarnDesc1()
   {
      return _WarnDesc1;
   }
	
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message or the specified default value.
    */
   public final String getWarnDesc1( String defaultValue )
   {
      return _WarnDesc1 == null ? defaultValue : _WarnDesc1;
   }
                  
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code or null.
    */
   public final Integer getWarnCode2()
   {
      return _WarnCode2;
   }
	
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code or the specified default value.
    */
   public final int getWarnCode2( int defaultValue )
   {
      return _WarnCode2 == null ? defaultValue : _WarnCode2.intValue();
   }
                  
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message or null.
    */
   public final String getWarnDesc2()
   {
      return _WarnDesc2;
   }
	
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message or the specified default value.
    */
   public final String getWarnDesc2( String defaultValue )
   {
      return _WarnDesc2 == null ? defaultValue : _WarnDesc2;
   }
                  
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code or null.
    */
   public final Integer getWarnCode3()
   {
      return _WarnCode3;
   }
	
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code or the specified default value.
    */
   public final int getWarnCode3( int defaultValue )
   {
      return _WarnCode3 == null ? defaultValue : _WarnCode3.intValue();
   }
                  
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message or null.
    */
   public final String getWarnDesc3()
   {
      return _WarnDesc3;
   }
	
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message or the specified default value.
    */
   public final String getWarnDesc3( String defaultValue )
   {
      return _WarnDesc3 == null ? defaultValue : _WarnDesc3;
   }
                  
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code or null.
    */
   public final Integer getWarnCode4()
   {
      return _WarnCode4;
   }
	
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code or the specified default value.
    */
   public final int getWarnCode4( int defaultValue )
   {
      return _WarnCode4 == null ? defaultValue : _WarnCode4.intValue();
   }
                  
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message or null.
    */
   public final String getWarnDesc4()
   {
      return _WarnDesc4;
   }
	
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message or the specified default value.
    */
   public final String getWarnDesc4( String defaultValue )
   {
      return _WarnDesc4 == null ? defaultValue : _WarnDesc4;
   }
                  
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message Code or null.
    */
   public final Integer getWarnCode5()
   {
      return _WarnCode5;
   }
	
   /**
    * Gets the Warning Message Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message Code or the specified default value.
    */
   public final int getWarnCode5( int defaultValue )
   {
      return _WarnCode5 == null ? defaultValue : _WarnCode5.intValue();
   }
                  
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Message or null.
    */
   public final String getWarnDesc5()
   {
      return _WarnDesc5;
   }
	
   /**
    * Gets the Warning Message field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Message or the specified default value.
    */
   public final String getWarnDesc5( String defaultValue )
   {
      return _WarnDesc5 == null ? defaultValue : _WarnDesc5;
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
    * Gets the Key Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Key Type or null.
    */
   public final String getKeyType( int index )
   {
      return _KeyType[index];
   }
    
   /**
    * Gets the Key Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Key Type or the specified default value.
    */
   public final String getKeyType( int index, String defaultValue )
   {
      return _KeyType[index] == null ? defaultValue : _KeyType[index];
   }
    
   /**
    * Gets the array of Key Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Key Type values.
    */
   public final String[] getKeyTypeArray()
   {
      return _KeyType;
   }
    
   /**
    * Gets the Temporary Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Temporary Value or null.
    */
   public final String getTempValue( int index )
   {
      return _TempValue[index];
   }
    
   /**
    * Gets the Temporary Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Temporary Value or the specified default value.
    */
   public final String getTempValue( int index, String defaultValue )
   {
      return _TempValue[index] == null ? defaultValue : _TempValue[index];
   }
    
   /**
    * Gets the array of Temporary Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Temporary Value values.
    */
   public final String[] getTempValueArray()
   {
      return _TempValue;
   }
    
   /**
    * Gets the Permanent Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Permanent Value or null.
    */
   public final String getPermValue( int index )
   {
      return _PermValue[index];
   }
    
   /**
    * Gets the Permanent Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Permanent Value or the specified default value.
    */
   public final String getPermValue( int index, String defaultValue )
   {
      return _PermValue[index] == null ? defaultValue : _PermValue[index];
   }
    
   /**
    * Gets the array of Permanent Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Permanent Value values.
    */
   public final String[] getPermValueArray()
   {
      return _PermValue;
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
      _UpdateStatus = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _WarnCode1 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnCode2 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnCode3 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnCode4 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WarnCode5 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _WarnDesc5 = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _KeyType = resizeArray( _KeyType, _RepeatCount );
      _TempValue = resizeArray( _TempValue, _RepeatCount );
      _PermValue = resizeArray( _PermValue, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _KeyType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TempValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PermValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
