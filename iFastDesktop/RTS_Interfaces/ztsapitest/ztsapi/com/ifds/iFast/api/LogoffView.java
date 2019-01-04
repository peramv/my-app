
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * User logoff view.
 * For additional view information see <A HREF="../../../../viewspecs/Logoff.doc">Logoff.doc</A>.
 * 
 * @author RTS Generated
 */
public class LogoffView extends IFastView implements Serializable
{

   /**
    * Logout message member variable.
    */
   private String _LogoutMsg = null;
   

   /**
    * Constructs the LogoffView object.
    * 
    */
   public LogoffView()
   {
      super ( new LogoffRequest() );
   }

   /**
    * Constructs the LogoffView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public LogoffView( String hostEncoding )
   {
      super ( new LogoffRequest( hostEncoding ) );
   }

   /**
    * Gets the LogoffRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The LogoffRequest object.
    */
   public final LogoffRequest getRequest()
   {
      return (LogoffRequest)getIFastRequest();
   }
        
   /**
    * Gets the Logout message field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Logout message or null.
    */
   public final String getLogoutMsg()
   {
      return _LogoutMsg;
   }
	
   /**
    * Gets the Logout message field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Logout message or the specified default value.
    */
   public final String getLogoutMsg( String defaultValue )
   {
      return _LogoutMsg == null ? defaultValue : _LogoutMsg;
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
      _LogoutMsg = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
