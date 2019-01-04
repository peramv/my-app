
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Business Day List Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/BusDayInq.doc">BusDayInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class BusDayInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Business Day Code member array.
    */
   private String[] _BusDayCode = null;
   
   /**
    * Include/Exclude Code member array.
    */
   private String[] _IncludeCode = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Sunday is a Business Day member array.
    */
   private Boolean[] _SundayIsBusDay = null;
   
   /**
    * Monday is a Business Day member array.
    */
   private Boolean[] _MondayIsBusDay = null;
   
   /**
    * Tuesday is a Business Day member array.
    */
   private Boolean[] _TuesdayIsBusDay = null;
   
   /**
    * Wednesday is a Business Day member array.
    */
   private Boolean[] _WednesdayIsBusDay = null;
   
   /**
    * Thursday is a Business Day member array.
    */
   private Boolean[] _ThursdayIsBusDay = null;
   
   /**
    * Friday is a Business Day member array.
    */
   private Boolean[] _FridayIsBusDay = null;
   
   /**
    * Saturday is a Business Day member array.
    */
   private Boolean[] _SaturdayIsBusDay = null;
   

   /**
    * Constructs the BusDayInqView object.
    * 
    */
   public BusDayInqView()
   {
      super ( new BusDayInqRequest() );
   }

   /**
    * Constructs the BusDayInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BusDayInqView( String hostEncoding )
   {
      super ( new BusDayInqRequest( hostEncoding ) );
   }

   /**
    * Gets the BusDayInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BusDayInqRequest object.
    */
   public final BusDayInqRequest getRequest()
   {
      return (BusDayInqRequest)getIFastRequest();
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
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Business Day Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Business Day Code or null.
    */
   public final String getBusDayCode( int index )
   {
      return _BusDayCode[index];
   }
    
   /**
    * Gets the Business Day Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Business Day Code or the specified default value.
    */
   public final String getBusDayCode( int index, String defaultValue )
   {
      return _BusDayCode[index] == null ? defaultValue : _BusDayCode[index];
   }
    
   /**
    * Gets the array of Business Day Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Business Day Code values.
    */
   public final String[] getBusDayCodeArray()
   {
      return _BusDayCode;
   }
    
   /**
    * Gets the Include/Exclude Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Include/Exclude Code or null.
    */
   public final String getIncludeCode( int index )
   {
      return _IncludeCode[index];
   }
    
   /**
    * Gets the Include/Exclude Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Include/Exclude Code or the specified default value.
    */
   public final String getIncludeCode( int index, String defaultValue )
   {
      return _IncludeCode[index] == null ? defaultValue : _IncludeCode[index];
   }
    
   /**
    * Gets the array of Include/Exclude Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Include/Exclude Code values.
    */
   public final String[] getIncludeCodeArray()
   {
      return _IncludeCode;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Sunday is a Business Day field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sunday is a Business Day or null.
    */
   public final Boolean getSundayIsBusDay( int index )
   {
      return _SundayIsBusDay[index];
   }
    
   /**
    * Gets the Sunday is a Business Day field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sunday is a Business Day or the specified default value.
    */
   public final boolean getSundayIsBusDay( int index, boolean defaultValue )
   {
      return _SundayIsBusDay[index] == null ? defaultValue : _SundayIsBusDay[index].booleanValue();
   }
    
   /**
    * Gets the array of Sunday is a Business Day fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sunday is a Business Day values.
    */
   public final Boolean[] getSundayIsBusDayArray()
   {
      return _SundayIsBusDay;
   }
    
   /**
    * Gets the Monday is a Business Day field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Monday is a Business Day or null.
    */
   public final Boolean getMondayIsBusDay( int index )
   {
      return _MondayIsBusDay[index];
   }
    
   /**
    * Gets the Monday is a Business Day field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Monday is a Business Day or the specified default value.
    */
   public final boolean getMondayIsBusDay( int index, boolean defaultValue )
   {
      return _MondayIsBusDay[index] == null ? defaultValue : _MondayIsBusDay[index].booleanValue();
   }
    
   /**
    * Gets the array of Monday is a Business Day fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Monday is a Business Day values.
    */
   public final Boolean[] getMondayIsBusDayArray()
   {
      return _MondayIsBusDay;
   }
    
   /**
    * Gets the Tuesday is a Business Day field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tuesday is a Business Day or null.
    */
   public final Boolean getTuesdayIsBusDay( int index )
   {
      return _TuesdayIsBusDay[index];
   }
    
   /**
    * Gets the Tuesday is a Business Day field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tuesday is a Business Day or the specified default value.
    */
   public final boolean getTuesdayIsBusDay( int index, boolean defaultValue )
   {
      return _TuesdayIsBusDay[index] == null ? defaultValue : _TuesdayIsBusDay[index].booleanValue();
   }
    
   /**
    * Gets the array of Tuesday is a Business Day fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tuesday is a Business Day values.
    */
   public final Boolean[] getTuesdayIsBusDayArray()
   {
      return _TuesdayIsBusDay;
   }
    
   /**
    * Gets the Wednesday is a Business Day field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Wednesday is a Business Day or null.
    */
   public final Boolean getWednesdayIsBusDay( int index )
   {
      return _WednesdayIsBusDay[index];
   }
    
   /**
    * Gets the Wednesday is a Business Day field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wednesday is a Business Day or the specified default value.
    */
   public final boolean getWednesdayIsBusDay( int index, boolean defaultValue )
   {
      return _WednesdayIsBusDay[index] == null ? defaultValue : _WednesdayIsBusDay[index].booleanValue();
   }
    
   /**
    * Gets the array of Wednesday is a Business Day fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Wednesday is a Business Day values.
    */
   public final Boolean[] getWednesdayIsBusDayArray()
   {
      return _WednesdayIsBusDay;
   }
    
   /**
    * Gets the Thursday is a Business Day field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Thursday is a Business Day or null.
    */
   public final Boolean getThursdayIsBusDay( int index )
   {
      return _ThursdayIsBusDay[index];
   }
    
   /**
    * Gets the Thursday is a Business Day field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Thursday is a Business Day or the specified default value.
    */
   public final boolean getThursdayIsBusDay( int index, boolean defaultValue )
   {
      return _ThursdayIsBusDay[index] == null ? defaultValue : _ThursdayIsBusDay[index].booleanValue();
   }
    
   /**
    * Gets the array of Thursday is a Business Day fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Thursday is a Business Day values.
    */
   public final Boolean[] getThursdayIsBusDayArray()
   {
      return _ThursdayIsBusDay;
   }
    
   /**
    * Gets the Friday is a Business Day field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Friday is a Business Day or null.
    */
   public final Boolean getFridayIsBusDay( int index )
   {
      return _FridayIsBusDay[index];
   }
    
   /**
    * Gets the Friday is a Business Day field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Friday is a Business Day or the specified default value.
    */
   public final boolean getFridayIsBusDay( int index, boolean defaultValue )
   {
      return _FridayIsBusDay[index] == null ? defaultValue : _FridayIsBusDay[index].booleanValue();
   }
    
   /**
    * Gets the array of Friday is a Business Day fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Friday is a Business Day values.
    */
   public final Boolean[] getFridayIsBusDayArray()
   {
      return _FridayIsBusDay;
   }
    
   /**
    * Gets the Saturday is a Business Day field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Saturday is a Business Day or null.
    */
   public final Boolean getSaturdayIsBusDay( int index )
   {
      return _SaturdayIsBusDay[index];
   }
    
   /**
    * Gets the Saturday is a Business Day field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Saturday is a Business Day or the specified default value.
    */
   public final boolean getSaturdayIsBusDay( int index, boolean defaultValue )
   {
      return _SaturdayIsBusDay[index] == null ? defaultValue : _SaturdayIsBusDay[index].booleanValue();
   }
    
   /**
    * Gets the array of Saturday is a Business Day fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Saturday is a Business Day values.
    */
   public final Boolean[] getSaturdayIsBusDayArray()
   {
      return _SaturdayIsBusDay;
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
      
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _BusDayCode = resizeArray( _BusDayCode, _RepeatCount );
      _IncludeCode = resizeArray( _IncludeCode, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _SundayIsBusDay = resizeArray( _SundayIsBusDay, _RepeatCount );
      _MondayIsBusDay = resizeArray( _MondayIsBusDay, _RepeatCount );
      _TuesdayIsBusDay = resizeArray( _TuesdayIsBusDay, _RepeatCount );
      _WednesdayIsBusDay = resizeArray( _WednesdayIsBusDay, _RepeatCount );
      _ThursdayIsBusDay = resizeArray( _ThursdayIsBusDay, _RepeatCount );
      _FridayIsBusDay = resizeArray( _FridayIsBusDay, _RepeatCount );
      _SaturdayIsBusDay = resizeArray( _SaturdayIsBusDay, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BusDayCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncludeCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SundayIsBusDay[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MondayIsBusDay[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TuesdayIsBusDay[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _WednesdayIsBusDay[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ThursdayIsBusDay[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FridayIsBusDay[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SaturdayIsBusDay[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
