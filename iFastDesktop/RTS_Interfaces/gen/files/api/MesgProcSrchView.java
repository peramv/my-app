
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Message Process Search view.
 * For additional view information see <A HREF="../../../../viewspecs/MesgProcSrch.doc">MesgProcSrch.doc</A>.
 * 
 * @author RTS Generated
 */
public class MesgProcSrchView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * NetworkID member array.
    */
   private String[] _rxNetworkID = null;
   
   /**
    * Process ID member array.
    */
   private String[] _ProcessID = null;
   
   /**
    * Process Type member array.
    */
   private String[] _rxProcessType = null;
   
   /**
    * Process Status member array.
    */
   private String[] _rxProcessStatus = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Process Time member array.
    */
   private String[] _ProcessTime = null;
   
   /**
    * Process Category member array.
    */
   private String[] _rxProcessCategory = null;
   
   /**
    * File Name member array.
    */
   private String[] _FileName = null;
   

   /**
    * Constructs the MesgProcSrchView object.
    * 
    */
   public MesgProcSrchView()
   {
      super ( new MesgProcSrchRequest() );
   }

   /**
    * Constructs the MesgProcSrchView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MesgProcSrchView( String hostEncoding )
   {
      super ( new MesgProcSrchRequest( hostEncoding ) );
   }

   /**
    * Gets the MesgProcSrchRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MesgProcSrchRequest object.
    */
   public final MesgProcSrchRequest getRequest()
   {
      return (MesgProcSrchRequest)getIFastRequest();
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
   public final String getrxNetworkID( int index )
   {
      return _rxNetworkID[index];
   }
    
   /**
    * Gets the NetworkID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetworkID or the specified default value.
    */
   public final String getrxNetworkID( int index, String defaultValue )
   {
      return _rxNetworkID[index] == null ? defaultValue : _rxNetworkID[index];
   }
    
   /**
    * Gets the array of NetworkID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NetworkID values.
    */
   public final String[] getrxNetworkIDArray()
   {
      return _rxNetworkID;
   }
    
   /**
    * Gets the Process ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process ID or null.
    */
   public final String getProcessID( int index )
   {
      return _ProcessID[index];
   }
    
   /**
    * Gets the Process ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process ID or the specified default value.
    */
   public final String getProcessID( int index, String defaultValue )
   {
      return _ProcessID[index] == null ? defaultValue : _ProcessID[index];
   }
    
   /**
    * Gets the array of Process ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process ID values.
    */
   public final String[] getProcessIDArray()
   {
      return _ProcessID;
   }
    
   /**
    * Gets the Process Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Type or null.
    */
   public final String getrxProcessType( int index )
   {
      return _rxProcessType[index];
   }
    
   /**
    * Gets the Process Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Type or the specified default value.
    */
   public final String getrxProcessType( int index, String defaultValue )
   {
      return _rxProcessType[index] == null ? defaultValue : _rxProcessType[index];
   }
    
   /**
    * Gets the array of Process Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Type values.
    */
   public final String[] getrxProcessTypeArray()
   {
      return _rxProcessType;
   }
    
   /**
    * Gets the Process Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Status or null.
    */
   public final String getrxProcessStatus( int index )
   {
      return _rxProcessStatus[index];
   }
    
   /**
    * Gets the Process Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Status or the specified default value.
    */
   public final String getrxProcessStatus( int index, String defaultValue )
   {
      return _rxProcessStatus[index] == null ? defaultValue : _rxProcessStatus[index];
   }
    
   /**
    * Gets the array of Process Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Status values.
    */
   public final String[] getrxProcessStatusArray()
   {
      return _rxProcessStatus;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Process Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Time or null.
    */
   public final String getProcessTime( int index )
   {
      return _ProcessTime[index];
   }
    
   /**
    * Gets the Process Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Time or the specified default value.
    */
   public final String getProcessTime( int index, String defaultValue )
   {
      return _ProcessTime[index] == null ? defaultValue : _ProcessTime[index];
   }
    
   /**
    * Gets the array of Process Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Time values.
    */
   public final String[] getProcessTimeArray()
   {
      return _ProcessTime;
   }
    
   /**
    * Gets the Process Category field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Category or null.
    */
   public final String getrxProcessCategory( int index )
   {
      return _rxProcessCategory[index];
   }
    
   /**
    * Gets the Process Category field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Category or the specified default value.
    */
   public final String getrxProcessCategory( int index, String defaultValue )
   {
      return _rxProcessCategory[index] == null ? defaultValue : _rxProcessCategory[index];
   }
    
   /**
    * Gets the array of Process Category fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Category values.
    */
   public final String[] getrxProcessCategoryArray()
   {
      return _rxProcessCategory;
   }
    
   /**
    * Gets the File Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the File Name or null.
    */
   public final String getFileName( int index )
   {
      return _FileName[index];
   }
    
   /**
    * Gets the File Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the File Name or the specified default value.
    */
   public final String getFileName( int index, String defaultValue )
   {
      return _FileName[index] == null ? defaultValue : _FileName[index];
   }
    
   /**
    * Gets the array of File Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of File Name values.
    */
   public final String[] getFileNameArray()
   {
      return _FileName;
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
      
      _rxNetworkID = resizeArray( _rxNetworkID, _RepeatCount );
      _ProcessID = resizeArray( _ProcessID, _RepeatCount );
      _rxProcessType = resizeArray( _rxProcessType, _RepeatCount );
      _rxProcessStatus = resizeArray( _rxProcessStatus, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ProcessTime = resizeArray( _ProcessTime, _RepeatCount );
      _rxProcessCategory = resizeArray( _rxProcessCategory, _RepeatCount );
      _FileName = resizeArray( _FileName, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxNetworkID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxProcessType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxProcessStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxProcessCategory[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FileName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
