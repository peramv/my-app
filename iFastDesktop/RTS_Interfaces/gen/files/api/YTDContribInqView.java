
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Year-To-Date Contribution Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/YTDContribInq.doc">YTDContribInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class YTDContribInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Year of contribution member array.
    */
   private Integer[] _ContribYear = null;
   
   /**
    * Contributions during first 60 days member array.
    */
   private String[] _First60days = null;
   
   /**
    * Contributions during remainder of year member array.
    */
   private String[] _Remaining = null;
   

   /**
    * Constructs the YTDContribInqView object.
    * 
    */
   public YTDContribInqView()
   {
      super ( new YTDContribInqRequest() );
   }

   /**
    * Constructs the YTDContribInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public YTDContribInqView( String hostEncoding )
   {
      super ( new YTDContribInqRequest( hostEncoding ) );
   }

   /**
    * Gets the YTDContribInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The YTDContribInqRequest object.
    */
   public final YTDContribInqRequest getRequest()
   {
      return (YTDContribInqRequest)getIFastRequest();
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
    * Gets the Year of contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Year of contribution or null.
    */
   public final Integer getContribYear( int index )
   {
      return _ContribYear[index];
   }
    
   /**
    * Gets the Year of contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Year of contribution or the specified default value.
    */
   public final int getContribYear( int index, int defaultValue )
   {
      return _ContribYear[index] == null ? defaultValue : _ContribYear[index].intValue();
   }
    
   /**
    * Gets the array of Year of contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Year of contribution values.
    */
   public final Integer[] getContribYearArray()
   {
      return _ContribYear;
   }
    
   /**
    * Gets the Contributions during first 60 days field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contributions during first 60 days or null.
    */
   public final String getFirst60days( int index )
   {
      return _First60days[index];
   }
    
   /**
    * Gets the Contributions during first 60 days field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contributions during first 60 days or the specified default value.
    */
   public final String getFirst60days( int index, String defaultValue )
   {
      return _First60days[index] == null ? defaultValue : _First60days[index];
   }
    
   /**
    * Gets the array of Contributions during first 60 days fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contributions during first 60 days values.
    */
   public final String[] getFirst60daysArray()
   {
      return _First60days;
   }
    
   /**
    * Gets the Contributions during remainder of year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contributions during remainder of year or null.
    */
   public final String getRemaining( int index )
   {
      return _Remaining[index];
   }
    
   /**
    * Gets the Contributions during remainder of year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contributions during remainder of year or the specified default value.
    */
   public final String getRemaining( int index, String defaultValue )
   {
      return _Remaining[index] == null ? defaultValue : _Remaining[index];
   }
    
   /**
    * Gets the array of Contributions during remainder of year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contributions during remainder of year values.
    */
   public final String[] getRemainingArray()
   {
      return _Remaining;
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
      
      _ContribYear = resizeArray( _ContribYear, _RepeatCount );
      _First60days = resizeArray( _First60days, _RepeatCount );
      _Remaining = resizeArray( _Remaining, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _ContribYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _First60days[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remaining[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
