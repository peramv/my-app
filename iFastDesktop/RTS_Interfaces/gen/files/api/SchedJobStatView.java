
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Scheduled Job Status view.
 * For additional view information see <A HREF="../../../../viewspecs/SchedJobStat.doc">SchedJobStat.doc</A>.
 * 
 * @author RTS Generated
 */
public class SchedJobStatView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Scheduled Job Id member array.
    */
   private Integer[] _SchedJobId = null;
   
   /**
    * Job Name member array.
    */
   private String[] _JobName = null;
   
   /**
    * Job Start Date member array.
    */
   private Date[] _JobStartDate = null;
   
   /**
    * Job End Date member array.
    */
   private Date[] _JobEndDate = null;
   
   /**
    * Job run start time member array.
    */
   private String[] _JobStartTime = null;
   
   /**
    * Job Run End Time member array.
    */
   private String[] _JobEndTime = null;
   
   /**
    * Job Status member array.
    */
   private String[] _JobStatus = null;
   
   /**
    * Output file Name member array.
    */
   private String[] _OutputFileName = null;
   
   /**
    * Output file path member array.
    */
   private String[] _OutputFilePath = null;
   

   /**
    * Constructs the SchedJobStatView object.
    * 
    */
   public SchedJobStatView()
   {
      super ( new SchedJobStatRequest() );
   }

   /**
    * Constructs the SchedJobStatView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SchedJobStatView( String hostEncoding )
   {
      super ( new SchedJobStatRequest( hostEncoding ) );
   }

   /**
    * Gets the SchedJobStatRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SchedJobStatRequest object.
    */
   public final SchedJobStatRequest getRequest()
   {
      return (SchedJobStatRequest)getIFastRequest();
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
    * Gets the Scheduled Job Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Scheduled Job Id or null.
    */
   public final Integer getSchedJobId( int index )
   {
      return _SchedJobId[index];
   }
    
   /**
    * Gets the Scheduled Job Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Scheduled Job Id or the specified default value.
    */
   public final int getSchedJobId( int index, int defaultValue )
   {
      return _SchedJobId[index] == null ? defaultValue : _SchedJobId[index].intValue();
   }
    
   /**
    * Gets the array of Scheduled Job Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Scheduled Job Id values.
    */
   public final Integer[] getSchedJobIdArray()
   {
      return _SchedJobId;
   }
    
   /**
    * Gets the Job Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Job Name or null.
    */
   public final String getJobName( int index )
   {
      return _JobName[index];
   }
    
   /**
    * Gets the Job Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Job Name or the specified default value.
    */
   public final String getJobName( int index, String defaultValue )
   {
      return _JobName[index] == null ? defaultValue : _JobName[index];
   }
    
   /**
    * Gets the array of Job Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Job Name values.
    */
   public final String[] getJobNameArray()
   {
      return _JobName;
   }
    
   /**
    * Gets the Job Start Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Job Start Date or null.
    */
   public final Date getJobStartDate( int index )
   {
      return _JobStartDate[index];
   }
    
   /**
    * Gets the Job Start Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Job Start Date or the specified default value.
    */
   public final Date getJobStartDate( int index, Date defaultValue )
   {
      return _JobStartDate[index] == null ? defaultValue : _JobStartDate[index];
   }
    
   /**
    * Gets the array of Job Start Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Job Start Date values.
    */
   public final Date[] getJobStartDateArray()
   {
      return _JobStartDate;
   }
    
   /**
    * Gets the Job End Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Job End Date or null.
    */
   public final Date getJobEndDate( int index )
   {
      return _JobEndDate[index];
   }
    
   /**
    * Gets the Job End Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Job End Date or the specified default value.
    */
   public final Date getJobEndDate( int index, Date defaultValue )
   {
      return _JobEndDate[index] == null ? defaultValue : _JobEndDate[index];
   }
    
   /**
    * Gets the array of Job End Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Job End Date values.
    */
   public final Date[] getJobEndDateArray()
   {
      return _JobEndDate;
   }
    
   /**
    * Gets the Job run start time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Job run start time or null.
    */
   public final String getJobStartTime( int index )
   {
      return _JobStartTime[index];
   }
    
   /**
    * Gets the Job run start time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Job run start time or the specified default value.
    */
   public final String getJobStartTime( int index, String defaultValue )
   {
      return _JobStartTime[index] == null ? defaultValue : _JobStartTime[index];
   }
    
   /**
    * Gets the array of Job run start time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Job run start time values.
    */
   public final String[] getJobStartTimeArray()
   {
      return _JobStartTime;
   }
    
   /**
    * Gets the Job Run End Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Job Run End Time or null.
    */
   public final String getJobEndTime( int index )
   {
      return _JobEndTime[index];
   }
    
   /**
    * Gets the Job Run End Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Job Run End Time or the specified default value.
    */
   public final String getJobEndTime( int index, String defaultValue )
   {
      return _JobEndTime[index] == null ? defaultValue : _JobEndTime[index];
   }
    
   /**
    * Gets the array of Job Run End Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Job Run End Time values.
    */
   public final String[] getJobEndTimeArray()
   {
      return _JobEndTime;
   }
    
   /**
    * Gets the Job Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Job Status or null.
    */
   public final String getJobStatus( int index )
   {
      return _JobStatus[index];
   }
    
   /**
    * Gets the Job Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Job Status or the specified default value.
    */
   public final String getJobStatus( int index, String defaultValue )
   {
      return _JobStatus[index] == null ? defaultValue : _JobStatus[index];
   }
    
   /**
    * Gets the array of Job Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Job Status values.
    */
   public final String[] getJobStatusArray()
   {
      return _JobStatus;
   }
    
   /**
    * Gets the Output file Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Output file Name or null.
    */
   public final String getOutputFileName( int index )
   {
      return _OutputFileName[index];
   }
    
   /**
    * Gets the Output file Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Output file Name or the specified default value.
    */
   public final String getOutputFileName( int index, String defaultValue )
   {
      return _OutputFileName[index] == null ? defaultValue : _OutputFileName[index];
   }
    
   /**
    * Gets the array of Output file Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Output file Name values.
    */
   public final String[] getOutputFileNameArray()
   {
      return _OutputFileName;
   }
    
   /**
    * Gets the Output file path field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Output file path or null.
    */
   public final String getOutputFilePath( int index )
   {
      return _OutputFilePath[index];
   }
    
   /**
    * Gets the Output file path field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Output file path or the specified default value.
    */
   public final String getOutputFilePath( int index, String defaultValue )
   {
      return _OutputFilePath[index] == null ? defaultValue : _OutputFilePath[index];
   }
    
   /**
    * Gets the array of Output file path fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Output file path values.
    */
   public final String[] getOutputFilePathArray()
   {
      return _OutputFilePath;
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
      
      _SchedJobId = resizeArray( _SchedJobId, _RepeatCount );
      _JobName = resizeArray( _JobName, _RepeatCount );
      _JobStartDate = resizeArray( _JobStartDate, _RepeatCount );
      _JobEndDate = resizeArray( _JobEndDate, _RepeatCount );
      _JobStartTime = resizeArray( _JobStartTime, _RepeatCount );
      _JobEndTime = resizeArray( _JobEndTime, _RepeatCount );
      _JobStatus = resizeArray( _JobStatus, _RepeatCount );
      _OutputFileName = resizeArray( _OutputFileName, _RepeatCount );
      _OutputFilePath = resizeArray( _OutputFilePath, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _SchedJobId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _JobName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _JobStartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _JobEndDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _JobStartTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _JobEndTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _JobStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OutputFileName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _OutputFilePath[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
