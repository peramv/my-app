
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Date and Time Conversion Inq view.
 * For additional view information see <A HREF="../../../../viewspecs/DateAndTimeConversion.doc">DateAndTimeConversion.doc</A>.
 * 
 * @author RTS Generated
 */
public class DateAndTimeConversionView extends IFastView implements Serializable
{

   /**
    * Back Office Date member variable.
    */
   private Date _BODate = null;
   
   /**
    * Back Office Time member variable.
    */
   private String _BOTime = null;
   
   /**
    * Back Office Zone member variable.
    */
   private String _BOZone = null;
   
   /**
    * Financial Institution Date member variable.
    */
   private Date _FIDate = null;
   
   /**
    * Financial Institution Time member variable.
    */
   private String _FITime = null;
   
   /**
    * Financial Institution Time Zone member variable.
    */
   private String _FIZone = null;
   
   /**
    * Confirmation Number member variable.
    */
   private String _ConfNum = null;
   

   /**
    * Constructs the DateAndTimeConversionView object.
    * 
    */
   public DateAndTimeConversionView()
   {
      super ( new DateAndTimeConversionRequest() );
   }

   /**
    * Constructs the DateAndTimeConversionView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DateAndTimeConversionView( String hostEncoding )
   {
      super ( new DateAndTimeConversionRequest( hostEncoding ) );
   }

   /**
    * Gets the DateAndTimeConversionRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DateAndTimeConversionRequest object.
    */
   public final DateAndTimeConversionRequest getRequest()
   {
      return (DateAndTimeConversionRequest)getIFastRequest();
   }
        
   /**
    * Gets the Back Office Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Back Office Date or null.
    */
   public final Date getBODate()
   {
      return _BODate;
   }
	
   /**
    * Gets the Back Office Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back Office Date or the specified default value.
    */
   public final Date getBODate( Date defaultValue )
   {
      return _BODate == null ? defaultValue : _BODate;
   }
                  
   /**
    * Gets the Back Office Time field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Back Office Time or null.
    */
   public final String getBOTime()
   {
      return _BOTime;
   }
	
   /**
    * Gets the Back Office Time field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back Office Time or the specified default value.
    */
   public final String getBOTime( String defaultValue )
   {
      return _BOTime == null ? defaultValue : _BOTime;
   }
                  
   /**
    * Gets the Back Office Zone field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Back Office Zone or null.
    */
   public final String getBOZone()
   {
      return _BOZone;
   }
	
   /**
    * Gets the Back Office Zone field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back Office Zone or the specified default value.
    */
   public final String getBOZone( String defaultValue )
   {
      return _BOZone == null ? defaultValue : _BOZone;
   }
                  
   /**
    * Gets the Financial Institution Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Financial Institution Date or null.
    */
   public final Date getFIDate()
   {
      return _FIDate;
   }
	
   /**
    * Gets the Financial Institution Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Financial Institution Date or the specified default value.
    */
   public final Date getFIDate( Date defaultValue )
   {
      return _FIDate == null ? defaultValue : _FIDate;
   }
                  
   /**
    * Gets the Financial Institution Time field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Financial Institution Time or null.
    */
   public final String getFITime()
   {
      return _FITime;
   }
	
   /**
    * Gets the Financial Institution Time field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Financial Institution Time or the specified default value.
    */
   public final String getFITime( String defaultValue )
   {
      return _FITime == null ? defaultValue : _FITime;
   }
                  
   /**
    * Gets the Financial Institution Time Zone field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Financial Institution Time Zone or null.
    */
   public final String getFIZone()
   {
      return _FIZone;
   }
	
   /**
    * Gets the Financial Institution Time Zone field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Financial Institution Time Zone or the specified default value.
    */
   public final String getFIZone( String defaultValue )
   {
      return _FIZone == null ? defaultValue : _FIZone;
   }
                  
   /**
    * Gets the Confirmation Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Confirmation Number or null.
    */
   public final String getConfNum()
   {
      return _ConfNum;
   }
	
   /**
    * Gets the Confirmation Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Confirmation Number or the specified default value.
    */
   public final String getConfNum( String defaultValue )
   {
      return _ConfNum == null ? defaultValue : _ConfNum;
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
      _BODate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _BOTime = responseBuffer.decodeString(responseBuffer.getNextField());
      _BOZone = responseBuffer.decodeString(responseBuffer.getNextField());
      _FIDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _FITime = responseBuffer.decodeString(responseBuffer.getNextField());
      _FIZone = responseBuffer.decodeString(responseBuffer.getNextField());
      _ConfNum = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
