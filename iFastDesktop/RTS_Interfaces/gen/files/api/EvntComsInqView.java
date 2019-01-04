
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Event Commission Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/EvntComsInq.doc">EvntComsInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class EvntComsInqView extends IFastView implements Serializable
{

   /**
    * Event Commission member variable.
    */
   private String _EventComm = null;
   

   /**
    * Constructs the EvntComsInqView object.
    * 
    */
   public EvntComsInqView()
   {
      super ( new EvntComsInqRequest() );
   }

   /**
    * Constructs the EvntComsInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public EvntComsInqView( String hostEncoding )
   {
      super ( new EvntComsInqRequest( hostEncoding ) );
   }

   /**
    * Gets the EvntComsInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The EvntComsInqRequest object.
    */
   public final EvntComsInqRequest getRequest()
   {
      return (EvntComsInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Event Commission field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Event Commission or null.
    */
   public final String getEventComm()
   {
      return _EventComm;
   }
	
   /**
    * Gets the Event Commission field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Event Commission or the specified default value.
    */
   public final String getEventComm( String defaultValue )
   {
      return _EventComm == null ? defaultValue : _EventComm;
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
      _EventComm = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
