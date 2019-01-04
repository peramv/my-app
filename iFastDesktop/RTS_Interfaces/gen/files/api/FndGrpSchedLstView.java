
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Group Schedule Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FndGrpSchedLst.doc">FndGrpSchedLst.doc</A>.
 * 
 * @author RTS Generated
 */
public class FndGrpSchedLstView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Response Fund Group Type member array.
    */
   private String[] _RxFundGroupType = null;
   
   /**
    * Fund Group Fund Group member array.
    */
   private String[] _FundGroupGroup = null;
   
   /**
    * Business Day Code member array.
    */
   private String[] _BusDayCode = null;
   
   /**
    * Holiday Code member array.
    */
   private String[] _HolidayCode = null;
   
   /**
    * Schedule member array.
    */
   private String[] _Schedule = null;
   

   /**
    * Constructs the FndGrpSchedLstView object.
    * 
    */
   public FndGrpSchedLstView()
   {
      super ( new FndGrpSchedLstRequest() );
   }

   /**
    * Constructs the FndGrpSchedLstView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FndGrpSchedLstView( String hostEncoding )
   {
      super ( new FndGrpSchedLstRequest( hostEncoding ) );
   }

   /**
    * Gets the FndGrpSchedLstRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FndGrpSchedLstRequest object.
    */
   public final FndGrpSchedLstRequest getRequest()
   {
      return (FndGrpSchedLstRequest)getIFastRequest();
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
    * Gets the Response Fund Group Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Response Fund Group Type or null.
    */
   public final String getRxFundGroupType( int index )
   {
      return _RxFundGroupType[index];
   }
    
   /**
    * Gets the Response Fund Group Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Response Fund Group Type or the specified default value.
    */
   public final String getRxFundGroupType( int index, String defaultValue )
   {
      return _RxFundGroupType[index] == null ? defaultValue : _RxFundGroupType[index];
   }
    
   /**
    * Gets the array of Response Fund Group Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Response Fund Group Type values.
    */
   public final String[] getRxFundGroupTypeArray()
   {
      return _RxFundGroupType;
   }
    
   /**
    * Gets the Fund Group Fund Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Group Fund Group or null.
    */
   public final String getFundGroupGroup( int index )
   {
      return _FundGroupGroup[index];
   }
    
   /**
    * Gets the Fund Group Fund Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Group Fund Group or the specified default value.
    */
   public final String getFundGroupGroup( int index, String defaultValue )
   {
      return _FundGroupGroup[index] == null ? defaultValue : _FundGroupGroup[index];
   }
    
   /**
    * Gets the array of Fund Group Fund Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Group Fund Group values.
    */
   public final String[] getFundGroupGroupArray()
   {
      return _FundGroupGroup;
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
    * Gets the Holiday Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Holiday Code or null.
    */
   public final String getHolidayCode( int index )
   {
      return _HolidayCode[index];
   }
    
   /**
    * Gets the Holiday Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Holiday Code or the specified default value.
    */
   public final String getHolidayCode( int index, String defaultValue )
   {
      return _HolidayCode[index] == null ? defaultValue : _HolidayCode[index];
   }
    
   /**
    * Gets the array of Holiday Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Holiday Code values.
    */
   public final String[] getHolidayCodeArray()
   {
      return _HolidayCode;
   }
    
   /**
    * Gets the Schedule field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Schedule or null.
    */
   public final String getSchedule( int index )
   {
      return _Schedule[index];
   }
    
   /**
    * Gets the Schedule field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Schedule or the specified default value.
    */
   public final String getSchedule( int index, String defaultValue )
   {
      return _Schedule[index] == null ? defaultValue : _Schedule[index];
   }
    
   /**
    * Gets the array of Schedule fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Schedule values.
    */
   public final String[] getScheduleArray()
   {
      return _Schedule;
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
      
      _RxFundGroupType = resizeArray( _RxFundGroupType, _RepeatCount );
      _FundGroupGroup = resizeArray( _FundGroupGroup, _RepeatCount );
      _BusDayCode = resizeArray( _BusDayCode, _RepeatCount );
      _HolidayCode = resizeArray( _HolidayCode, _RepeatCount );
      _Schedule = resizeArray( _Schedule, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _RxFundGroupType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundGroupGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BusDayCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HolidayCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Schedule[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
