
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Help File Tracking view.
 * For additional view information see <A HREF="../../../../viewspecs/HlpFileTrack.doc">HlpFileTrack.doc</A>.
 * 
 * @author RTS Generated
 */
public class HlpFileTrackView extends IFastView implements Serializable
{


   /**
    * Constructs the HlpFileTrackView object.
    * 
    */
   public HlpFileTrackView()
   {
      super ( new HlpFileTrackRequest() );
   }

   /**
    * Constructs the HlpFileTrackView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public HlpFileTrackView( String hostEncoding )
   {
      super ( new HlpFileTrackRequest( hostEncoding ) );
   }

   /**
    * Gets the HlpFileTrackRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The HlpFileTrackRequest object.
    */
   public final HlpFileTrackRequest getRequest()
   {
      return (HlpFileTrackRequest)getIFastRequest();
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
                  

   }

}
      
