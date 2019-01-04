
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Scheduled Job Master view.
 * For additional view information see <A HREF="../../../../viewspecs/SchedJobMstr.doc">SchedJobMstr.doc</A>.
 * 
 * @author RTS Generated
 */
public class SchedJobMstrView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Job Name member array.
    */
   private String[] _rxJobName = null;
   
   /**
    * flag indicating whether verification is required member array.
    */
   private Boolean[] _VerifReq = null;
   
   /**
    * flag indicating if job must be scheduled member array.
    */
   private Boolean[] _MustBeScheduled = null;
   
   /**
    * flag indicating if job is obsolete member array.
    */
   private Boolean[] _Obsolete = null;
   

   /**
    * Constructs the SchedJobMstrView object.
    * 
    */
   public SchedJobMstrView()
   {
      super ( new SchedJobMstrRequest() );
   }

   /**
    * Constructs the SchedJobMstrView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SchedJobMstrView( String hostEncoding )
   {
      super ( new SchedJobMstrRequest( hostEncoding ) );
   }

   /**
    * Gets the SchedJobMstrRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SchedJobMstrRequest object.
    */
   public final SchedJobMstrRequest getRequest()
   {
      return (SchedJobMstrRequest)getIFastRequest();
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
    * Gets the Job Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Job Name or null.
    */
   public final String getrxJobName( int index )
   {
      return _rxJobName[index];
   }
    
   /**
    * Gets the Job Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Job Name or the specified default value.
    */
   public final String getrxJobName( int index, String defaultValue )
   {
      return _rxJobName[index] == null ? defaultValue : _rxJobName[index];
   }
    
   /**
    * Gets the array of Job Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Job Name values.
    */
   public final String[] getrxJobNameArray()
   {
      return _rxJobName;
   }
    
   /**
    * Gets the flag indicating whether verification is required field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the flag indicating whether verification is required or null.
    */
   public final Boolean getVerifReq( int index )
   {
      return _VerifReq[index];
   }
    
   /**
    * Gets the flag indicating whether verification is required field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating whether verification is required or the specified default value.
    */
   public final boolean getVerifReq( int index, boolean defaultValue )
   {
      return _VerifReq[index] == null ? defaultValue : _VerifReq[index].booleanValue();
   }
    
   /**
    * Gets the array of flag indicating whether verification is required fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of flag indicating whether verification is required values.
    */
   public final Boolean[] getVerifReqArray()
   {
      return _VerifReq;
   }
    
   /**
    * Gets the flag indicating if job must be scheduled field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the flag indicating if job must be scheduled or null.
    */
   public final Boolean getMustBeScheduled( int index )
   {
      return _MustBeScheduled[index];
   }
    
   /**
    * Gets the flag indicating if job must be scheduled field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating if job must be scheduled or the specified default value.
    */
   public final boolean getMustBeScheduled( int index, boolean defaultValue )
   {
      return _MustBeScheduled[index] == null ? defaultValue : _MustBeScheduled[index].booleanValue();
   }
    
   /**
    * Gets the array of flag indicating if job must be scheduled fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of flag indicating if job must be scheduled values.
    */
   public final Boolean[] getMustBeScheduledArray()
   {
      return _MustBeScheduled;
   }
    
   /**
    * Gets the flag indicating if job is obsolete field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the flag indicating if job is obsolete or null.
    */
   public final Boolean getObsolete( int index )
   {
      return _Obsolete[index];
   }
    
   /**
    * Gets the flag indicating if job is obsolete field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating if job is obsolete or the specified default value.
    */
   public final boolean getObsolete( int index, boolean defaultValue )
   {
      return _Obsolete[index] == null ? defaultValue : _Obsolete[index].booleanValue();
   }
    
   /**
    * Gets the array of flag indicating if job is obsolete fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of flag indicating if job is obsolete values.
    */
   public final Boolean[] getObsoleteArray()
   {
      return _Obsolete;
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
      
      _rxJobName = resizeArray( _rxJobName, _RepeatCount );
      _VerifReq = resizeArray( _VerifReq, _RepeatCount );
      _MustBeScheduled = resizeArray( _MustBeScheduled, _RepeatCount );
      _Obsolete = resizeArray( _Obsolete, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxJobName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _VerifReq[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MustBeScheduled[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Obsolete[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
