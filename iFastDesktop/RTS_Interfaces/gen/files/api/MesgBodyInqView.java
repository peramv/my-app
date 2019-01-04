
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Message Body Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/MesgBodyInq.doc">MesgBodyInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class MesgBodyInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Unique Message ID member array.
    */
   private Integer[] _MessageID = null;
   
   /**
    * Message Type member array.
    */
   private String[] _MessageType = null;
   
   /**
    * Unique Message ID sequence number member array.
    */
   private Integer[] _SegmentSeq = null;
   
   /**
    * Message Text member array.
    */
   private String[] _SegmentData = null;
   

   /**
    * Constructs the MesgBodyInqView object.
    * 
    */
   public MesgBodyInqView()
   {
      super ( new MesgBodyInqRequest() );
   }

   /**
    * Constructs the MesgBodyInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public MesgBodyInqView( String hostEncoding )
   {
      super ( new MesgBodyInqRequest( hostEncoding ) );
   }

   /**
    * Gets the MesgBodyInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The MesgBodyInqRequest object.
    */
   public final MesgBodyInqRequest getRequest()
   {
      return (MesgBodyInqRequest)getIFastRequest();
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
    * Gets the Unique Message ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unique Message ID or null.
    */
   public final Integer getMessageID( int index )
   {
      return _MessageID[index];
   }
    
   /**
    * Gets the Unique Message ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unique Message ID or the specified default value.
    */
   public final int getMessageID( int index, int defaultValue )
   {
      return _MessageID[index] == null ? defaultValue : _MessageID[index].intValue();
   }
    
   /**
    * Gets the array of Unique Message ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unique Message ID values.
    */
   public final Integer[] getMessageIDArray()
   {
      return _MessageID;
   }
    
   /**
    * Gets the Message Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Message Type or null.
    */
   public final String getMessageType( int index )
   {
      return _MessageType[index];
   }
    
   /**
    * Gets the Message Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Message Type or the specified default value.
    */
   public final String getMessageType( int index, String defaultValue )
   {
      return _MessageType[index] == null ? defaultValue : _MessageType[index];
   }
    
   /**
    * Gets the array of Message Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Message Type values.
    */
   public final String[] getMessageTypeArray()
   {
      return _MessageType;
   }
    
   /**
    * Gets the Unique Message ID sequence number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unique Message ID sequence number or null.
    */
   public final Integer getSegmentSeq( int index )
   {
      return _SegmentSeq[index];
   }
    
   /**
    * Gets the Unique Message ID sequence number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unique Message ID sequence number or the specified default value.
    */
   public final int getSegmentSeq( int index, int defaultValue )
   {
      return _SegmentSeq[index] == null ? defaultValue : _SegmentSeq[index].intValue();
   }
    
   /**
    * Gets the array of Unique Message ID sequence number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unique Message ID sequence number values.
    */
   public final Integer[] getSegmentSeqArray()
   {
      return _SegmentSeq;
   }
    
   /**
    * Gets the Message Text field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Message Text or null.
    */
   public final String getSegmentData( int index )
   {
      return _SegmentData[index];
   }
    
   /**
    * Gets the Message Text field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Message Text or the specified default value.
    */
   public final String getSegmentData( int index, String defaultValue )
   {
      return _SegmentData[index] == null ? defaultValue : _SegmentData[index];
   }
    
   /**
    * Gets the array of Message Text fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Message Text values.
    */
   public final String[] getSegmentDataArray()
   {
      return _SegmentData;
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
      
      _MessageID = resizeArray( _MessageID, _RepeatCount );
      _MessageType = resizeArray( _MessageType, _RepeatCount );
      _SegmentSeq = resizeArray( _SegmentSeq, _RepeatCount );
      _SegmentData = resizeArray( _SegmentData, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _MessageID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MessageType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SegmentSeq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _SegmentData[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
