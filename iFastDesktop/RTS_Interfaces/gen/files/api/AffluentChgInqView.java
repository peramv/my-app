
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Affluent Flag Validation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/AffluentChgInq.doc">AffluentChgInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AffluentChgInqView extends IFastView implements Serializable
{

   /**
    * Affluent Flag change allowed member variable.
    */
   private Boolean _AffluentChgAllowed = null;
   

   /**
    * Constructs the AffluentChgInqView object.
    * 
    */
   public AffluentChgInqView()
   {
      super ( new AffluentChgInqRequest() );
   }

   /**
    * Constructs the AffluentChgInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AffluentChgInqView( String hostEncoding )
   {
      super ( new AffluentChgInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AffluentChgInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AffluentChgInqRequest object.
    */
   public final AffluentChgInqRequest getRequest()
   {
      return (AffluentChgInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Affluent Flag change allowed field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Affluent Flag change allowed or null.
    */
   public final Boolean getAffluentChgAllowed()
   {
      return _AffluentChgAllowed;
   }
	
   /**
    * Gets the Affluent Flag change allowed field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Affluent Flag change allowed or the specified default value.
    */
   public final boolean getAffluentChgAllowed( boolean defaultValue )
   {
      return _AffluentChgAllowed == null ? defaultValue : _AffluentChgAllowed.booleanValue();
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
      _AffluentChgAllowed = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
