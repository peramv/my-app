
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Entity History Inquriy view.
 * For additional view information see <A HREF="../../../../viewspecs/EntHist.doc">EntHist.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntHistView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Mod Time member array.
    */
   private String[] _ModTime = null;
   
   /**
    * Field Label member array.
    */
   private String[] _FieldLabel = null;
   
   /**
    * Previous Display member array.
    */
   private String[] _PreviousDisp = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   

   /**
    * Constructs the EntHistView object.
    * 
    */
   public EntHistView()
   {
      super ( new EntHistRequest() );
   }

   /**
    * Constructs the EntHistView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public EntHistView( String hostEncoding )
   {
      super ( new EntHistRequest( hostEncoding ) );
   }

   /**
    * Gets the EntHistRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The EntHistRequest object.
    */
   public final EntHistRequest getRequest()
   {
      return (EntHistRequest)getIFastRequest();
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
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Mod Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Mod Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod Time or null.
    */
   public final String getModTime( int index )
   {
      return _ModTime[index];
   }
    
   /**
    * Gets the Mod Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Time or the specified default value.
    */
   public final String getModTime( int index, String defaultValue )
   {
      return _ModTime[index] == null ? defaultValue : _ModTime[index];
   }
    
   /**
    * Gets the array of Mod Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod Time values.
    */
   public final String[] getModTimeArray()
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
    * Gets the Previous Display field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Previous Display or null.
    */
   public final String getPreviousDisp( int index )
   {
      return _PreviousDisp[index];
   }
    
   /**
    * Gets the Previous Display field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Display or the specified default value.
    */
   public final String getPreviousDisp( int index, String defaultValue )
   {
      return _PreviousDisp[index] == null ? defaultValue : _PreviousDisp[index];
   }
    
   /**
    * Gets the array of Previous Display fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Previous Display values.
    */
   public final String[] getPreviousDispArray()
   {
      return _PreviousDisp;
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Mod User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
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
      _ModTime = resizeArray( _ModTime, _RepeatCount );
      _FieldLabel = resizeArray( _FieldLabel, _RepeatCount );
      _PreviousDisp = resizeArray( _PreviousDisp, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FieldLabel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PreviousDisp[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
