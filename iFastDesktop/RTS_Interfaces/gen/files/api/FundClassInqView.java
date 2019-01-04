
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Class Information view.
 * For additional view information see <A HREF="../../../../viewspecs/FundClassInq.doc">FundClassInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundClassInqView extends IFastView implements Serializable
{


   /**
    * Constructs the FundClassInqView object.
    * 
    */
   public FundClassInqView()
   {
      super ( new FundClassInqRequest() );
   }

   /**
    * Constructs the FundClassInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundClassInqView( String hostEncoding )
   {
      super ( new FundClassInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundClassInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundClassInqRequest object.
    */
   public final FundClassInqRequest getRequest()
   {
      return (FundClassInqRequest)getIFastRequest();
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
      
