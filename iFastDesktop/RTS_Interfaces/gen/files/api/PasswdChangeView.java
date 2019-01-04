
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Password Change view.
 * For additional view information see <A HREF="../../../../viewspecs/PasswdChange.doc">PasswdChange.doc</A>.
 * 
 * @author RTS Generated
 */
public class PasswdChangeView extends IFastView implements Serializable
{

   /**
    * Valid Password member variable.
    */
   private Boolean _ValidPasswd = null;
   

   /**
    * Constructs the PasswdChangeView object.
    * 
    */
   public PasswdChangeView()
   {
      super ( new PasswdChangeRequest() );
   }

   /**
    * Constructs the PasswdChangeView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PasswdChangeView( String hostEncoding )
   {
      super ( new PasswdChangeRequest( hostEncoding ) );
   }

   /**
    * Gets the PasswdChangeRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PasswdChangeRequest object.
    */
   public final PasswdChangeRequest getRequest()
   {
      return (PasswdChangeRequest)getIFastRequest();
   }
        
   /**
    * Gets the Valid Password field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Valid Password or null.
    */
   public final Boolean getValidPasswd()
   {
      return _ValidPasswd;
   }
	
   /**
    * Gets the Valid Password field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valid Password or the specified default value.
    */
   public final boolean getValidPasswd( boolean defaultValue )
   {
      return _ValidPasswd == null ? defaultValue : _ValidPasswd.booleanValue();
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
      _ValidPasswd = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
