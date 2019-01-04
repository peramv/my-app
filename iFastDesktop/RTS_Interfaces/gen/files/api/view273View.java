
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Reserved view.
 * For additional view information see <A HREF="../../../../viewspecs/view273.doc">view273.doc</A>.
 * 
 * @author RTS Generated
 */
public class view273View extends IFastView implements Serializable
{


   /**
    * Constructs the view273View object.
    * 
    */
   public view273View()
   {
      super ( new view273Request() );
   }

   /**
    * Constructs the view273View object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public view273View( String hostEncoding )
   {
      super ( new view273Request( hostEncoding ) );
   }

   /**
    * Gets the view273Request object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The view273Request object.
    */
   public final view273Request getRequest()
   {
      return (view273Request)getIFastRequest();
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
      
