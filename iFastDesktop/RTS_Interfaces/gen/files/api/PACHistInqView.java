
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * PAC Indexing History Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/PACHistInq.doc">PACHistInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PACHistInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Modification Id member array.
    */
   private Integer[] _ModId = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Modofication Time member array.
    */
   private Integer[] _ModTime = null;
   
   /**
    * Field Label member array.
    */
   private String[] _FieldLabel = null;
   
   /**
    * Old Value of Field member array.
    */
   private String[] _OldValue = null;
   
   /**
    * New Value of Field member array.
    */
   private String[] _NewValue = null;
   

   /**
    * Constructs the PACHistInqView object.
    * 
    */
   public PACHistInqView()
   {
      super ( new PACHistInqRequest() );
   }

   /**
    * Constructs the PACHistInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PACHistInqView( String hostEncoding )
   {
      super ( new PACHistInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PACHistInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PACHistInqRequest object.
    */
   public final PACHistInqRequest getRequest()
   {
      return (PACHistInqRequest)getIFastRequest();
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
    * Gets the Modification Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modification Id or null.
    */
   public final Integer getModId( int index )
   {
      return _ModId[index];
   }
    
   /**
    * Gets the Modification Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification Id or the specified default value.
    */
   public final int getModId( int index, int defaultValue )
   {
      return _ModId[index] == null ? defaultValue : _ModId[index].intValue();
   }
    
   /**
    * Gets the array of Modification Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modification Id values.
    */
   public final Integer[] getModIdArray()
   {
      return _ModId;
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modification Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modification Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modification Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Modofication Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modofication Time or null.
    */
   public final Integer getModTime( int index )
   {
      return _ModTime[index];
   }
    
   /**
    * Gets the Modofication Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modofication Time or the specified default value.
    */
   public final int getModTime( int index, int defaultValue )
   {
      return _ModTime[index] == null ? defaultValue : _ModTime[index].intValue();
   }
    
   /**
    * Gets the array of Modofication Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modofication Time values.
    */
   public final Integer[] getModTimeArray()
   {
      return _ModTime;
   }
    
   /**
    * Gets the Field Label field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Field Label or null.
    */
   public final String getFieldLabel( int index )
   {
      return _FieldLabel[index];
   }
    
   /**
    * Gets the Field Label field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Field Label or the specified default value.
    */
   public final String getFieldLabel( int index, String defaultValue )
   {
      return _FieldLabel[index] == null ? defaultValue : _FieldLabel[index];
   }
    
   /**
    * Gets the array of Field Label fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Field Label values.
    */
   public final String[] getFieldLabelArray()
   {
      return _FieldLabel;
   }
    
   /**
    * Gets the Old Value of Field field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Old Value of Field or null.
    */
   public final String getOldValue( int index )
   {
      return _OldValue[index];
   }
    
   /**
    * Gets the Old Value of Field field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Old Value of Field or the specified default value.
    */
   public final String getOldValue( int index, String defaultValue )
   {
      return _OldValue[index] == null ? defaultValue : _OldValue[index];
   }
    
   /**
    * Gets the array of Old Value of Field fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Old Value of Field values.
    */
   public final String[] getOldValueArray()
   {
      return _OldValue;
   }
    
   /**
    * Gets the New Value of Field field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the New Value of Field or null.
    */
   public final String getNewValue( int index )
   {
      return _NewValue[index];
   }
    
   /**
    * Gets the New Value of Field field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the New Value of Field or the specified default value.
    */
   public final String getNewValue( int index, String defaultValue )
   {
      return _NewValue[index] == null ? defaultValue : _NewValue[index];
   }
    
   /**
    * Gets the array of New Value of Field fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of New Value of Field values.
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
      
      _ModId = resizeArray( _ModId, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModTime = resizeArray( _ModTime, _RepeatCount );
      _FieldLabel = resizeArray( _FieldLabel, _RepeatCount );
      _OldValue = resizeArray( _OldValue, _RepeatCount );
      _NewValue = resizeArray( _NewValue, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ModId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModTime[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FieldLabel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OldValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NewValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
