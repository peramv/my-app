
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * System Availability view.
 * For additional view information see <A HREF="../../../../viewspecs/SysAvailability.doc">SysAvailability.doc</A>.
 * 
 * @author RTS Generated
 */
public class SysAvailabilityView extends IFastView implements Serializable
{

   /**
    * Flag that indicates if last cycle run status is 'Active' member variable.
    */
   private Boolean _TradingAvailable = null;
   
   /**
    * Flag that indicates if inquiry is available member variable.
    */
   private Boolean _InquiryAvailable = null;
   
   /**
    * DB State member variable.
    */
   private String _DBState = null;
   

   /**
    * Constructs the SysAvailabilityView object.
    * 
    */
   public SysAvailabilityView()
   {
      super ( new SysAvailabilityRequest() );
   }

   /**
    * Constructs the SysAvailabilityView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SysAvailabilityView( String hostEncoding )
   {
      super ( new SysAvailabilityRequest( hostEncoding ) );
   }

   /**
    * Gets the SysAvailabilityRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SysAvailabilityRequest object.
    */
   public final SysAvailabilityRequest getRequest()
   {
      return (SysAvailabilityRequest)getIFastRequest();
   }
        
   /**
    * Gets the Flag that indicates if last cycle run status is 'Active' field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag that indicates if last cycle run status is 'Active' or null.
    */
   public final Boolean getTradingAvailable()
   {
      return _TradingAvailable;
   }
	
   /**
    * Gets the Flag that indicates if last cycle run status is 'Active' field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if last cycle run status is 'Active' or the specified default value.
    */
   public final boolean getTradingAvailable( boolean defaultValue )
   {
      return _TradingAvailable == null ? defaultValue : _TradingAvailable.booleanValue();
   }
                  
   /**
    * Gets the Flag that indicates if inquiry is available field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag that indicates if inquiry is available or null.
    */
   public final Boolean getInquiryAvailable()
   {
      return _InquiryAvailable;
   }
	
   /**
    * Gets the Flag that indicates if inquiry is available field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if inquiry is available or the specified default value.
    */
   public final boolean getInquiryAvailable( boolean defaultValue )
   {
      return _InquiryAvailable == null ? defaultValue : _InquiryAvailable.booleanValue();
   }
                  
   /**
    * Gets the DB State field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DB State or null.
    */
   public final String getDBState()
   {
      return _DBState;
   }
	
   /**
    * Gets the DB State field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DB State or the specified default value.
    */
   public final String getDBState( String defaultValue )
   {
      return _DBState == null ? defaultValue : _DBState;
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
      _TradingAvailable = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _InquiryAvailable = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DBState = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
