
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Title Restrictions view.
 * For additional view information see <A HREF="../../../../viewspecs/TitleRestInq.doc">TitleRestInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TitleRestInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Event Code member array.
    */
   private String[] _rxEventCode = null;
   
   /**
    * Reason Code member array.
    */
   private String[] _rxReasonCode = null;
   
   /**
    * Severity member array.
    */
   private String[] _Severity = null;
   
   /**
    * Error Code member array.
    */
   private String[] _rxErrorCode = null;
   
   /**
    * ESG Error Code member array.
    */
   private String[] _ESGErrorCode = null;
   
   /**
    * ESG Severity member array.
    */
   private String[] _ESGSeverity = null;
   

   /**
    * Constructs the TitleRestInqView object.
    * 
    */
   public TitleRestInqView()
   {
      super ( new TitleRestInqRequest() );
   }

   /**
    * Constructs the TitleRestInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TitleRestInqView( String hostEncoding )
   {
      super ( new TitleRestInqRequest( hostEncoding ) );
   }

   /**
    * Gets the TitleRestInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TitleRestInqRequest object.
    */
   public final TitleRestInqRequest getRequest()
   {
      return (TitleRestInqRequest)getIFastRequest();
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
    * Gets the Event Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Event Code or null.
    */
   public final String getrxEventCode( int index )
   {
      return _rxEventCode[index];
   }
    
   /**
    * Gets the Event Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Code or the specified default value.
    */
   public final String getrxEventCode( int index, String defaultValue )
   {
      return _rxEventCode[index] == null ? defaultValue : _rxEventCode[index];
   }
    
   /**
    * Gets the array of Event Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Code values.
    */
   public final String[] getrxEventCodeArray()
   {
      return _rxEventCode;
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason Code or null.
    */
   public final String getrxReasonCode( int index )
   {
      return _rxReasonCode[index];
   }
    
   /**
    * Gets the Reason Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason Code or the specified default value.
    */
   public final String getrxReasonCode( int index, String defaultValue )
   {
      return _rxReasonCode[index] == null ? defaultValue : _rxReasonCode[index];
   }
    
   /**
    * Gets the array of Reason Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason Code values.
    */
   public final String[] getrxReasonCodeArray()
   {
      return _rxReasonCode;
   }
    
   /**
    * Gets the Severity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Severity or null.
    */
   public final String getSeverity( int index )
   {
      return _Severity[index];
   }
    
   /**
    * Gets the Severity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Severity or the specified default value.
    */
   public final String getSeverity( int index, String defaultValue )
   {
      return _Severity[index] == null ? defaultValue : _Severity[index];
   }
    
   /**
    * Gets the array of Severity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Severity values.
    */
   public final String[] getSeverityArray()
   {
      return _Severity;
   }
    
   /**
    * Gets the Error Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Error Code or null.
    */
   public final String getrxErrorCode( int index )
   {
      return _rxErrorCode[index];
   }
    
   /**
    * Gets the Error Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Error Code or the specified default value.
    */
   public final String getrxErrorCode( int index, String defaultValue )
   {
      return _rxErrorCode[index] == null ? defaultValue : _rxErrorCode[index];
   }
    
   /**
    * Gets the array of Error Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Error Code values.
    */
   public final String[] getrxErrorCodeArray()
   {
      return _rxErrorCode;
   }
    
   /**
    * Gets the ESG Error Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ESG Error Code or null.
    */
   public final String getESGErrorCode( int index )
   {
      return _ESGErrorCode[index];
   }
    
   /**
    * Gets the ESG Error Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ESG Error Code or the specified default value.
    */
   public final String getESGErrorCode( int index, String defaultValue )
   {
      return _ESGErrorCode[index] == null ? defaultValue : _ESGErrorCode[index];
   }
    
   /**
    * Gets the array of ESG Error Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ESG Error Code values.
    */
   public final String[] getESGErrorCodeArray()
   {
      return _ESGErrorCode;
   }
    
   /**
    * Gets the ESG Severity field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ESG Severity or null.
    */
   public final String getESGSeverity( int index )
   {
      return _ESGSeverity[index];
   }
    
   /**
    * Gets the ESG Severity field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ESG Severity or the specified default value.
    */
   public final String getESGSeverity( int index, String defaultValue )
   {
      return _ESGSeverity[index] == null ? defaultValue : _ESGSeverity[index];
   }
    
   /**
    * Gets the array of ESG Severity fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ESG Severity values.
    */
   public final String[] getESGSeverityArray()
   {
      return _ESGSeverity;
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
      
      _rxEventCode = resizeArray( _rxEventCode, _RepeatCount );
      _rxReasonCode = resizeArray( _rxReasonCode, _RepeatCount );
      _Severity = resizeArray( _Severity, _RepeatCount );
      _rxErrorCode = resizeArray( _rxErrorCode, _RepeatCount );
      _ESGErrorCode = resizeArray( _ESGErrorCode, _RepeatCount );
      _ESGSeverity = resizeArray( _ESGSeverity, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxEventCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxReasonCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Severity[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxErrorCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ESGErrorCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ESGSeverity[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
