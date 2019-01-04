
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * GIA Investment Segment List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/GIAInvestmentSegmentListInquiry.doc">GIAInvestmentSegmentListInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class GIAInvestmentSegmentListInquiryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * IntInvestSegmtUUID member array.
    */
   private String[] _IntInvestSegmtUUID = null;
   
   /**
    * Seq member array.
    */
   private Integer[] _Seq = null;
   
   /**
    * IntSegment member array.
    */
   private String[] _IntSegment = null;
   
   /**
    * Code member array.
    */
   private String[] _Code = null;
   
   /**
    * Rate member array.
    */
   private String[] _Rate = null;
   

   /**
    * Constructs the GIAInvestmentSegmentListInquiryView object.
    * 
    */
   public GIAInvestmentSegmentListInquiryView()
   {
      super ( new GIAInvestmentSegmentListInquiryRequest() );
   }

   /**
    * Constructs the GIAInvestmentSegmentListInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public GIAInvestmentSegmentListInquiryView( String hostEncoding )
   {
      super ( new GIAInvestmentSegmentListInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the GIAInvestmentSegmentListInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The GIAInvestmentSegmentListInquiryRequest object.
    */
   public final GIAInvestmentSegmentListInquiryRequest getRequest()
   {
      return (GIAInvestmentSegmentListInquiryRequest)getIFastRequest();
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
    * Gets the IntInvestSegmtUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestSegmtUUID or null.
    */
   public final String getIntInvestSegmtUUID( int index )
   {
      return _IntInvestSegmtUUID[index];
   }
    
   /**
    * Gets the IntInvestSegmtUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestSegmtUUID or the specified default value.
    */
   public final String getIntInvestSegmtUUID( int index, String defaultValue )
   {
      return _IntInvestSegmtUUID[index] == null ? defaultValue : _IntInvestSegmtUUID[index];
   }
    
   /**
    * Gets the array of IntInvestSegmtUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestSegmtUUID values.
    */
   public final String[] getIntInvestSegmtUUIDArray()
   {
      return _IntInvestSegmtUUID;
   }
    
   /**
    * Gets the Seq field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Seq or null.
    */
   public final Integer getSeq( int index )
   {
      return _Seq[index];
   }
    
   /**
    * Gets the Seq field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Seq or the specified default value.
    */
   public final int getSeq( int index, int defaultValue )
   {
      return _Seq[index] == null ? defaultValue : _Seq[index].intValue();
   }
    
   /**
    * Gets the array of Seq fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Seq values.
    */
   public final Integer[] getSeqArray()
   {
      return _Seq;
   }
    
   /**
    * Gets the IntSegment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntSegment or null.
    */
   public final String getIntSegment( int index )
   {
      return _IntSegment[index];
   }
    
   /**
    * Gets the IntSegment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntSegment or the specified default value.
    */
   public final String getIntSegment( int index, String defaultValue )
   {
      return _IntSegment[index] == null ? defaultValue : _IntSegment[index];
   }
    
   /**
    * Gets the array of IntSegment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntSegment values.
    */
   public final String[] getIntSegmentArray()
   {
      return _IntSegment;
   }
    
   /**
    * Gets the Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Code or null.
    */
   public final String getCode( int index )
   {
      return _Code[index];
   }
    
   /**
    * Gets the Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Code or the specified default value.
    */
   public final String getCode( int index, String defaultValue )
   {
      return _Code[index] == null ? defaultValue : _Code[index];
   }
    
   /**
    * Gets the array of Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Code values.
    */
   public final String[] getCodeArray()
   {
      return _Code;
   }
    
   /**
    * Gets the Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Rate or null.
    */
   public final String getRate( int index )
   {
      return _Rate[index];
   }
    
   /**
    * Gets the Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Rate or the specified default value.
    */
   public final String getRate( int index, String defaultValue )
   {
      return _Rate[index] == null ? defaultValue : _Rate[index];
   }
    
   /**
    * Gets the array of Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Rate values.
    */
   public final String[] getRateArray()
   {
      return _Rate;
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
      
      _IntInvestSegmtUUID = resizeArray( _IntInvestSegmtUUID, _RepeatCount );
      _Seq = resizeArray( _Seq, _RepeatCount );
      _IntSegment = resizeArray( _IntSegment, _RepeatCount );
      _Code = resizeArray( _Code, _RepeatCount );
      _Rate = resizeArray( _Rate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _IntInvestSegmtUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Seq[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _IntSegment[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Code[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Rate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
