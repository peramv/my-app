
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * User's Batches Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/UserBatchInq.doc">UserBatchInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class UserBatchInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Batch ID member array.
    */
   private String[] _BatchID = null;
   
   /**
    * Batch Status member array.
    */
   private String[] _BatchStatus = null;
   
   /**
    * Batch Trace member array.
    */
   private Integer[] _BatchTrace = null;
   
   /**
    * Batch User member array.
    */
   private String[] _BatchUser = null;
   
   /**
    * Batch Order Type member array.
    */
   private Boolean[] _BatchOrdType = null;
   

   /**
    * Constructs the UserBatchInqView object.
    * 
    */
   public UserBatchInqView()
   {
      super ( new UserBatchInqRequest() );
   }

   /**
    * Constructs the UserBatchInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public UserBatchInqView( String hostEncoding )
   {
      super ( new UserBatchInqRequest( hostEncoding ) );
   }

   /**
    * Gets the UserBatchInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The UserBatchInqRequest object.
    */
   public final UserBatchInqRequest getRequest()
   {
      return (UserBatchInqRequest)getIFastRequest();
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
    * Gets the Batch ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch ID or null.
    */
   public final String getBatchID( int index )
   {
      return _BatchID[index];
   }
    
   /**
    * Gets the Batch ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch ID or the specified default value.
    */
   public final String getBatchID( int index, String defaultValue )
   {
      return _BatchID[index] == null ? defaultValue : _BatchID[index];
   }
    
   /**
    * Gets the array of Batch ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch ID values.
    */
   public final String[] getBatchIDArray()
   {
      return _BatchID;
   }
    
   /**
    * Gets the Batch Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Status or null.
    */
   public final String getBatchStatus( int index )
   {
      return _BatchStatus[index];
   }
    
   /**
    * Gets the Batch Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Status or the specified default value.
    */
   public final String getBatchStatus( int index, String defaultValue )
   {
      return _BatchStatus[index] == null ? defaultValue : _BatchStatus[index];
   }
    
   /**
    * Gets the array of Batch Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Status values.
    */
   public final String[] getBatchStatusArray()
   {
      return _BatchStatus;
   }
    
   /**
    * Gets the Batch Trace field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Trace or null.
    */
   public final Integer getBatchTrace( int index )
   {
      return _BatchTrace[index];
   }
    
   /**
    * Gets the Batch Trace field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Trace or the specified default value.
    */
   public final int getBatchTrace( int index, int defaultValue )
   {
      return _BatchTrace[index] == null ? defaultValue : _BatchTrace[index].intValue();
   }
    
   /**
    * Gets the array of Batch Trace fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Trace values.
    */
   public final Integer[] getBatchTraceArray()
   {
      return _BatchTrace;
   }
    
   /**
    * Gets the Batch User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch User or null.
    */
   public final String getBatchUser( int index )
   {
      return _BatchUser[index];
   }
    
   /**
    * Gets the Batch User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch User or the specified default value.
    */
   public final String getBatchUser( int index, String defaultValue )
   {
      return _BatchUser[index] == null ? defaultValue : _BatchUser[index];
   }
    
   /**
    * Gets the array of Batch User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch User values.
    */
   public final String[] getBatchUserArray()
   {
      return _BatchUser;
   }
    
   /**
    * Gets the Batch Order Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Batch Order Type or null.
    */
   public final Boolean getBatchOrdType( int index )
   {
      return _BatchOrdType[index];
   }
    
   /**
    * Gets the Batch Order Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Batch Order Type or the specified default value.
    */
   public final boolean getBatchOrdType( int index, boolean defaultValue )
   {
      return _BatchOrdType[index] == null ? defaultValue : _BatchOrdType[index].booleanValue();
   }
    
   /**
    * Gets the array of Batch Order Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Batch Order Type values.
    */
   public final Boolean[] getBatchOrdTypeArray()
   {
      return _BatchOrdType;
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
      
      _BatchID = resizeArray( _BatchID, _RepeatCount );
      _BatchStatus = resizeArray( _BatchStatus, _RepeatCount );
      _BatchTrace = resizeArray( _BatchTrace, _RepeatCount );
      _BatchUser = resizeArray( _BatchUser, _RepeatCount );
      _BatchOrdType = resizeArray( _BatchOrdType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _BatchID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchTrace[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BatchUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BatchOrdType[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
