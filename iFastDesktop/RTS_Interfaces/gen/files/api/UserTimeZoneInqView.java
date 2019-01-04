
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * UNIX Time Zone  Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/UserTimeZoneInq.doc">UserTimeZoneInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class UserTimeZoneInqView extends IFastView implements Serializable
{

   /**
    * User's Time Zone member variable.
    */
   private String _UserTimeZone = null;
   
   /**
    * Time at User's Time Zone member variable.
    */
   private String _UserTime = null;
   
   /**
    * Date at User's Time Zone member variable.
    */
   private Date _UserDate = null;
   

   /**
    * Constructs the UserTimeZoneInqView object.
    * 
    */
   public UserTimeZoneInqView()
   {
      super ( new UserTimeZoneInqRequest() );
   }

   /**
    * Constructs the UserTimeZoneInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public UserTimeZoneInqView( String hostEncoding )
   {
      super ( new UserTimeZoneInqRequest( hostEncoding ) );
   }

   /**
    * Gets the UserTimeZoneInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The UserTimeZoneInqRequest object.
    */
   public final UserTimeZoneInqRequest getRequest()
   {
      return (UserTimeZoneInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the User's Time Zone field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the User's Time Zone or null.
    */
   public final String getUserTimeZone()
   {
      return _UserTimeZone;
   }
	
   /**
    * Gets the User's Time Zone field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User's Time Zone or the specified default value.
    */
   public final String getUserTimeZone( String defaultValue )
   {
      return _UserTimeZone == null ? defaultValue : _UserTimeZone;
   }
                  
   /**
    * Gets the Time at User's Time Zone field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Time at User's Time Zone or null.
    */
   public final String getUserTime()
   {
      return _UserTime;
   }
	
   /**
    * Gets the Time at User's Time Zone field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Time at User's Time Zone or the specified default value.
    */
   public final String getUserTime( String defaultValue )
   {
      return _UserTime == null ? defaultValue : _UserTime;
   }
                  
   /**
    * Gets the Date at User's Time Zone field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date at User's Time Zone or null.
    */
   public final Date getUserDate()
   {
      return _UserDate;
   }
	
   /**
    * Gets the Date at User's Time Zone field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date at User's Time Zone or the specified default value.
    */
   public final Date getUserDate( Date defaultValue )
   {
      return _UserDate == null ? defaultValue : _UserDate;
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
      _UserTimeZone = responseBuffer.decodeString(responseBuffer.getNextField());
      _UserTime = responseBuffer.decodeString(responseBuffer.getNextField());
      _UserDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
