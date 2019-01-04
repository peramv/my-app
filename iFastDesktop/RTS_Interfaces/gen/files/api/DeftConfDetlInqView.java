
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Default Config Details Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DeftConfDetlInq.doc">DeftConfDetlInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DeftConfDetlInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * FldName member array.
    */
   private String[] _RespFldName = null;
   
   /**
    * KeyField1 member array.
    */
   private String[] _KeyField1 = null;
   
   /**
    * KeyField2 member array.
    */
   private String[] _KeyField2 = null;
   
   /**
    * KeyField3 member array.
    */
   private String[] _KeyField3 = null;
   
   /**
    * KeyField4 member array.
    */
   private String[] _KeyField4 = null;
   
   /**
    * KeyField5 member array.
    */
   private String[] _KeyField5 = null;
   
   /**
    * DefValue member array.
    */
   private String[] _DefValue = null;
   
   /**
    * StatCode member array.
    */
   private String[] _StatCode = null;
   

   /**
    * Constructs the DeftConfDetlInqView object.
    * 
    */
   public DeftConfDetlInqView()
   {
      super ( new DeftConfDetlInqRequest() );
   }

   /**
    * Constructs the DeftConfDetlInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DeftConfDetlInqView( String hostEncoding )
   {
      super ( new DeftConfDetlInqRequest( hostEncoding ) );
   }

   /**
    * Gets the DeftConfDetlInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DeftConfDetlInqRequest object.
    */
   public final DeftConfDetlInqRequest getRequest()
   {
      return (DeftConfDetlInqRequest)getIFastRequest();
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
    * Gets the KeyField1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the KeyField1 or null.
    */
   public final String getKeyField1( int index )
   {
      return _KeyField1[index];
   }
    
   /**
    * Gets the KeyField1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KeyField1 or the specified default value.
    */
   public final String getKeyField1( int index, String defaultValue )
   {
      return _KeyField1[index] == null ? defaultValue : _KeyField1[index];
   }
    
   /**
    * Gets the array of KeyField1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of KeyField1 values.
    */
   public final String[] getKeyField1Array()
   {
      return _KeyField1;
   }
    
   /**
    * Gets the KeyField2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the KeyField2 or null.
    */
   public final String getKeyField2( int index )
   {
      return _KeyField2[index];
   }
    
   /**
    * Gets the KeyField2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KeyField2 or the specified default value.
    */
   public final String getKeyField2( int index, String defaultValue )
   {
      return _KeyField2[index] == null ? defaultValue : _KeyField2[index];
   }
    
   /**
    * Gets the array of KeyField2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of KeyField2 values.
    */
   public final String[] getKeyField2Array()
   {
      return _KeyField2;
   }
    
   /**
    * Gets the KeyField3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the KeyField3 or null.
    */
   public final String getKeyField3( int index )
   {
      return _KeyField3[index];
   }
    
   /**
    * Gets the KeyField3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KeyField3 or the specified default value.
    */
   public final String getKeyField3( int index, String defaultValue )
   {
      return _KeyField3[index] == null ? defaultValue : _KeyField3[index];
   }
    
   /**
    * Gets the array of KeyField3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of KeyField3 values.
    */
   public final String[] getKeyField3Array()
   {
      return _KeyField3;
   }
    
   /**
    * Gets the KeyField4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the KeyField4 or null.
    */
   public final String getKeyField4( int index )
   {
      return _KeyField4[index];
   }
    
   /**
    * Gets the KeyField4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KeyField4 or the specified default value.
    */
   public final String getKeyField4( int index, String defaultValue )
   {
      return _KeyField4[index] == null ? defaultValue : _KeyField4[index];
   }
    
   /**
    * Gets the array of KeyField4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of KeyField4 values.
    */
   public final String[] getKeyField4Array()
   {
      return _KeyField4;
   }
    
   /**
    * Gets the KeyField5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the KeyField5 or null.
    */
   public final String getKeyField5( int index )
   {
      return _KeyField5[index];
   }
    
   /**
    * Gets the KeyField5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KeyField5 or the specified default value.
    */
   public final String getKeyField5( int index, String defaultValue )
   {
      return _KeyField5[index] == null ? defaultValue : _KeyField5[index];
   }
    
   /**
    * Gets the array of KeyField5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of KeyField5 values.
    */
   public final String[] getKeyField5Array()
   {
      return _KeyField5;
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
    * Gets the StatCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StatCode or null.
    */
   public final String getStatCode( int index )
   {
      return _StatCode[index];
   }
    
   /**
    * Gets the StatCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StatCode or the specified default value.
    */
   public final String getStatCode( int index, String defaultValue )
   {
      return _StatCode[index] == null ? defaultValue : _StatCode[index];
   }
    
   /**
    * Gets the array of StatCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StatCode values.
    */
   public final String[] getStatCodeArray()
   {
      return _StatCode;
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
      _KeyField1 = resizeArray( _KeyField1, _RepeatCount );
      _KeyField2 = resizeArray( _KeyField2, _RepeatCount );
      _KeyField3 = resizeArray( _KeyField3, _RepeatCount );
      _KeyField4 = resizeArray( _KeyField4, _RepeatCount );
      _KeyField5 = resizeArray( _KeyField5, _RepeatCount );
      _DefValue = resizeArray( _DefValue, _RepeatCount );
      _StatCode = resizeArray( _StatCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RespFldName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _KeyField1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _KeyField2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _KeyField3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _KeyField4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _KeyField5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DefValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
