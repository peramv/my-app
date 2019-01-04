
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Message File Search view.
 * For additional view information see <A HREF="../../../../viewspecs/MesgFileSearch.doc">MesgFileSearch.doc</A>.
 * 
 * @author RTS Generated
 */
public class MesgFileSearchView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Network ID member array.
    */
   private String[] _rxNetworkID = null;
   
   /**
    * File Name member array.
    */
   private String[] _rxFileName = null;
   
   /**
    * Envelope Status member array.
    */
   private String[] _EnvelopeStatus = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Process Time member array.
    */
   private String[] _ProcessTime = null;
   
   /**
    * Envelope ID member array.
    */
   private String[] _EnvelopeID = null;
   

   /**
    * Constructs the MesgFileSearchView object.
    * 
    */
   public MesgFileSearchView()
   {
      super ( new MesgFileSearchRequest() );
   }

   /**
    * Constructs the MesgFileSearchView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MesgFileSearchView( String hostEncoding )
   {
      super ( new MesgFileSearchRequest( hostEncoding ) );
   }

   /**
    * Gets the MesgFileSearchRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MesgFileSearchRequest object.
    */
   public final MesgFileSearchRequest getRequest()
   {
      return (MesgFileSearchRequest)getIFastRequest();
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
    * Gets the Network ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Network ID or null.
    */
   public final String getrxNetworkID( int index )
   {
      return _rxNetworkID[index];
   }
    
   /**
    * Gets the Network ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Network ID or the specified default value.
    */
   public final String getrxNetworkID( int index, String defaultValue )
   {
      return _rxNetworkID[index] == null ? defaultValue : _rxNetworkID[index];
   }
    
   /**
    * Gets the array of Network ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Network ID values.
    */
   public final String[] getrxNetworkIDArray()
   {
      return _rxNetworkID;
   }
    
   /**
    * Gets the File Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the File Name or null.
    */
   public final String getrxFileName( int index )
   {
      return _rxFileName[index];
   }
    
   /**
    * Gets the File Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the File Name or the specified default value.
    */
   public final String getrxFileName( int index, String defaultValue )
   {
      return _rxFileName[index] == null ? defaultValue : _rxFileName[index];
   }
    
   /**
    * Gets the array of File Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of File Name values.
    */
   public final String[] getrxFileNameArray()
   {
      return _rxFileName;
   }
    
   /**
    * Gets the Envelope Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Envelope Status or null.
    */
   public final String getEnvelopeStatus( int index )
   {
      return _EnvelopeStatus[index];
   }
    
   /**
    * Gets the Envelope Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Envelope Status or the specified default value.
    */
   public final String getEnvelopeStatus( int index, String defaultValue )
   {
      return _EnvelopeStatus[index] == null ? defaultValue : _EnvelopeStatus[index];
   }
    
   /**
    * Gets the array of Envelope Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Envelope Status values.
    */
   public final String[] getEnvelopeStatusArray()
   {
      return _EnvelopeStatus;
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
    * Gets the Envelope ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Envelope ID or null.
    */
   public final String getEnvelopeID( int index )
   {
      return _EnvelopeID[index];
   }
    
   /**
    * Gets the Envelope ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Envelope ID or the specified default value.
    */
   public final String getEnvelopeID( int index, String defaultValue )
   {
      return _EnvelopeID[index] == null ? defaultValue : _EnvelopeID[index];
   }
    
   /**
    * Gets the array of Envelope ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Envelope ID values.
    */
   public final String[] getEnvelopeIDArray()
   {
      return _EnvelopeID;
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
      _rxFileName = resizeArray( _rxFileName, _RepeatCount );
      _EnvelopeStatus = resizeArray( _EnvelopeStatus, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ProcessTime = resizeArray( _ProcessTime, _RepeatCount );
      _EnvelopeID = resizeArray( _EnvelopeID, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxNetworkID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFileName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EnvelopeStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessTime[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EnvelopeID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
