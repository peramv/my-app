
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Frequency List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FreqListInq.doc">FreqListInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FreqListInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * SchedSetupFreq ID member array.
    */
   private Integer[] _SchedSetupFreqID = null;
   
   /**
    * Sched Frequency Description member array.
    */
   private String[] _SchedFreqDesc = null;
   
   /**
    * Frequency Type member array.
    */
   private String[] _FrequencyType = null;
   

   /**
    * Constructs the FreqListInqView object.
    * 
    */
   public FreqListInqView()
   {
      super ( new FreqListInqRequest() );
   }

   /**
    * Constructs the FreqListInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FreqListInqView( String hostEncoding )
   {
      super ( new FreqListInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FreqListInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FreqListInqRequest object.
    */
   public final FreqListInqRequest getRequest()
   {
      return (FreqListInqRequest)getIFastRequest();
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
    * Gets the SchedSetupFreq ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SchedSetupFreq ID or null.
    */
   public final Integer getSchedSetupFreqID( int index )
   {
      return _SchedSetupFreqID[index];
   }
    
   /**
    * Gets the SchedSetupFreq ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SchedSetupFreq ID or the specified default value.
    */
   public final int getSchedSetupFreqID( int index, int defaultValue )
   {
      return _SchedSetupFreqID[index] == null ? defaultValue : _SchedSetupFreqID[index].intValue();
   }
    
   /**
    * Gets the array of SchedSetupFreq ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SchedSetupFreq ID values.
    */
   public final Integer[] getSchedSetupFreqIDArray()
   {
      return _SchedSetupFreqID;
   }
    
   /**
    * Gets the Sched Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sched Frequency Description or null.
    */
   public final String getSchedFreqDesc( int index )
   {
      return _SchedFreqDesc[index];
   }
    
   /**
    * Gets the Sched Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sched Frequency Description or the specified default value.
    */
   public final String getSchedFreqDesc( int index, String defaultValue )
   {
      return _SchedFreqDesc[index] == null ? defaultValue : _SchedFreqDesc[index];
   }
    
   /**
    * Gets the array of Sched Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sched Frequency Description values.
    */
   public final String[] getSchedFreqDescArray()
   {
      return _SchedFreqDesc;
   }
    
   /**
    * Gets the Frequency Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Frequency Type or null.
    */
   public final String getFrequencyType( int index )
   {
      return _FrequencyType[index];
   }
    
   /**
    * Gets the Frequency Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Frequency Type or the specified default value.
    */
   public final String getFrequencyType( int index, String defaultValue )
   {
      return _FrequencyType[index] == null ? defaultValue : _FrequencyType[index];
   }
    
   /**
    * Gets the array of Frequency Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Frequency Type values.
    */
   public final String[] getFrequencyTypeArray()
   {
      return _FrequencyType;
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
      
      _SchedSetupFreqID = resizeArray( _SchedSetupFreqID, _RepeatCount );
      _SchedFreqDesc = resizeArray( _SchedFreqDesc, _RepeatCount );
      _FrequencyType = resizeArray( _FrequencyType, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _SchedSetupFreqID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SchedFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FrequencyType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
