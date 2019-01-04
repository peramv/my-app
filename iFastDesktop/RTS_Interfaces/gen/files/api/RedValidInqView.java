
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * PAC/SWP NextProcDate Inq view.
 * For additional view information see <A HREF="../../../../viewspecs/RedValidInq.doc">RedValidInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RedValidInqView extends IFastView implements Serializable
{

   /**
    * Next Process Date member variable.
    */
   private Date _NextProcDate = null;
   

   /**
    * Constructs the RedValidInqView object.
    * 
    */
   public RedValidInqView()
   {
      super ( new RedValidInqRequest() );
   }

   /**
    * Constructs the RedValidInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RedValidInqView( String hostEncoding )
   {
      super ( new RedValidInqRequest( hostEncoding ) );
   }

   /**
    * Gets the RedValidInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RedValidInqRequest object.
    */
   public final RedValidInqRequest getRequest()
   {
      return (RedValidInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Next Process Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Next Process Date or null.
    */
   public final Date getNextProcDate()
   {
      return _NextProcDate;
   }
	
   /**
    * Gets the Next Process Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Process Date or the specified default value.
    */
   public final Date getNextProcDate( Date defaultValue )
   {
      return _NextProcDate == null ? defaultValue : _NextProcDate;
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
      _NextProcDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
