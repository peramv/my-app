
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Reinvestment Period Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ReinvestmentInq.doc">ReinvestmentInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ReinvestmentInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Calendar Year member array.
    */
   private Integer[] _CalendarYear = null;
   
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = null;
   
   /**
    * End Date member array.
    */
   private Date[] _EndDate = null;
   

   /**
    * Constructs the ReinvestmentInqView object.
    * 
    */
   public ReinvestmentInqView()
   {
      super ( new ReinvestmentInqRequest() );
   }

   /**
    * Constructs the ReinvestmentInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ReinvestmentInqView( String hostEncoding )
   {
      super ( new ReinvestmentInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ReinvestmentInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ReinvestmentInqRequest object.
    */
   public final ReinvestmentInqRequest getRequest()
   {
      return (ReinvestmentInqRequest)getIFastRequest();
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
    * Gets the Calendar Year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Calendar Year or null.
    */
   public final Integer getCalendarYear( int index )
   {
      return _CalendarYear[index];
   }
    
   /**
    * Gets the Calendar Year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Calendar Year or the specified default value.
    */
   public final int getCalendarYear( int index, int defaultValue )
   {
      return _CalendarYear[index] == null ? defaultValue : _CalendarYear[index].intValue();
   }
    
   /**
    * Gets the array of Calendar Year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Calendar Year values.
    */
   public final Integer[] getCalendarYearArray()
   {
      return _CalendarYear;
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start Date or null.
    */
   public final Date getStartDate( int index )
   {
      return _StartDate[index];
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Date or the specified default value.
    */
   public final Date getStartDate( int index, Date defaultValue )
   {
      return _StartDate[index] == null ? defaultValue : _StartDate[index];
   }
    
   /**
    * Gets the array of Start Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start Date values.
    */
   public final Date[] getStartDateArray()
   {
      return _StartDate;
   }
    
   /**
    * Gets the End Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the End Date or null.
    */
   public final Date getEndDate( int index )
   {
      return _EndDate[index];
   }
    
   /**
    * Gets the End Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the End Date or the specified default value.
    */
   public final Date getEndDate( int index, Date defaultValue )
   {
      return _EndDate[index] == null ? defaultValue : _EndDate[index];
   }
    
   /**
    * Gets the array of End Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of End Date values.
    */
   public final Date[] getEndDateArray()
   {
      return _EndDate;
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
      
      _CalendarYear = resizeArray( _CalendarYear, _RepeatCount );
      _StartDate = resizeArray( _StartDate, _RepeatCount );
      _EndDate = resizeArray( _EndDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _CalendarYear[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _StartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EndDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
