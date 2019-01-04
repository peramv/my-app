
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * User logon view.
 * For additional view information see <A HREF="../../../../viewspecs/Logon.doc">Logon.doc</A>.
 * 
 * @author RTS Generated
 */
public class LogonView extends IFastView implements Serializable
{


   /**
    * Constructs the LogonView object.
    * 
    */
   public LogonView()
   {
      super ( new LogonRequest() );
   }

   /**
    * Constructs the LogonView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public LogonView( String hostEncoding )
   {
      super ( new LogonRequest( hostEncoding ) );
   }

   /**
    * Gets the LogonRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The LogonRequest object.
    */
   public final LogonRequest getRequest()
   {
      return (LogonRequest)getIFastRequest();
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
      

   }

}
      
