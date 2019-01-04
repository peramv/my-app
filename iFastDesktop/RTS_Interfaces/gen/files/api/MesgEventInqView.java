
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Message Event Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/MesgEventInq.doc">MesgEventInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MesgEventInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Event Code member array.
    */
   private String[] _EventCode = null;
   
   /**
    * Event Type member array.
    */
   private String[] _EventType = null;
   
   /**
    * Event Description member array.
    */
   private String[] _EventText = null;
   

   /**
    * Constructs the MesgEventInqView object.
    * 
    */
   public MesgEventInqView()
   {
      super ( new MesgEventInqRequest() );
   }

   /**
    * Constructs the MesgEventInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MesgEventInqView( String hostEncoding )
   {
      super ( new MesgEventInqRequest( hostEncoding ) );
   }

   /**
    * Gets the MesgEventInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MesgEventInqRequest object.
    */
   public final MesgEventInqRequest getRequest()
   {
      return (MesgEventInqRequest)getIFastRequest();
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
   public final String getEventCode( int index )
   {
      return _EventCode[index];
   }
    
   /**
    * Gets the Event Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Code or the specified default value.
    */
   public final String getEventCode( int index, String defaultValue )
   {
      return _EventCode[index] == null ? defaultValue : _EventCode[index];
   }
    
   /**
    * Gets the array of Event Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Code values.
    */
   public final String[] getEventCodeArray()
   {
      return _EventCode;
   }
    
   /**
    * Gets the Event Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Event Type or null.
    */
   public final String getEventType( int index )
   {
      return _EventType[index];
   }
    
   /**
    * Gets the Event Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Type or the specified default value.
    */
   public final String getEventType( int index, String defaultValue )
   {
      return _EventType[index] == null ? defaultValue : _EventType[index];
   }
    
   /**
    * Gets the array of Event Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Type values.
    */
   public final String[] getEventTypeArray()
   {
      return _EventType;
   }
    
   /**
    * Gets the Event Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Event Description or null.
    */
   public final String getEventText( int index )
   {
      return _EventText[index];
   }
    
   /**
    * Gets the Event Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Description or the specified default value.
    */
   public final String getEventText( int index, String defaultValue )
   {
      return _EventText[index] == null ? defaultValue : _EventText[index];
   }
    
   /**
    * Gets the array of Event Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Event Description values.
    */
   public final String[] getEventTextArray()
   {
      return _EventText;
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
      
      _EventCode = resizeArray( _EventCode, _RepeatCount );
      _EventType = resizeArray( _EventType, _RepeatCount );
      _EventText = resizeArray( _EventText, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _EventCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EventType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EventText[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
