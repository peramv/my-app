
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * ESoP Plan History view.
 * For additional view information see <A HREF="../../../../viewspecs/ESoPHist.doc">ESoPHist.doc</A>.
 * 
 * @author RTS Generated
 */
public class ESoPHistView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Modify Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Field Name member array.
    */
   private String[] _FieldName = null;
   
   /**
    * Modify User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Old Value member array.
    */
   private String[] _OldValue = null;
   
   /**
    * New Value member array.
    */
   private String[] _NewValue = null;
   

   /**
    * Constructs the ESoPHistView object.
    * 
    */
   public ESoPHistView()
   {
      super ( new ESoPHistRequest() );
   }

   /**
    * Constructs the ESoPHistView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ESoPHistView( String hostEncoding )
   {
      super ( new ESoPHistRequest( hostEncoding ) );
   }

   /**
    * Gets the ESoPHistRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ESoPHistRequest object.
    */
   public final ESoPHistRequest getRequest()
   {
      return (ESoPHistRequest)getIFastRequest();
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
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modify Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modify Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Field Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Field Name or null.
    */
   public final String getFieldName( int index )
   {
      return _FieldName[index];
   }
    
   /**
    * Gets the Field Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Field Name or the specified default value.
    */
   public final String getFieldName( int index, String defaultValue )
   {
      return _FieldName[index] == null ? defaultValue : _FieldName[index];
   }
    
   /**
    * Gets the array of Field Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Field Name values.
    */
   public final String[] getFieldNameArray()
   {
      return _FieldName;
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modify User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modify User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modify User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modify User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modify User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Old Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Old Value or null.
    */
   public final String getOldValue( int index )
   {
      return _OldValue[index];
   }
    
   /**
    * Gets the Old Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Old Value or the specified default value.
    */
   public final String getOldValue( int index, String defaultValue )
   {
      return _OldValue[index] == null ? defaultValue : _OldValue[index];
   }
    
   /**
    * Gets the array of Old Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Old Value values.
    */
   public final String[] getOldValueArray()
   {
      return _OldValue;
   }
    
   /**
    * Gets the New Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the New Value or null.
    */
   public final String getNewValue( int index )
   {
      return _NewValue[index];
   }
    
   /**
    * Gets the New Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the New Value or the specified default value.
    */
   public final String getNewValue( int index, String defaultValue )
   {
      return _NewValue[index] == null ? defaultValue : _NewValue[index];
   }
    
   /**
    * Gets the array of New Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of New Value values.
    */
   public final String[] getNewValueArray()
   {
      return _NewValue;
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
      
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _FieldName = resizeArray( _FieldName, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _OldValue = resizeArray( _OldValue, _RepeatCount );
      _NewValue = resizeArray( _NewValue, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FieldName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OldValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NewValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
