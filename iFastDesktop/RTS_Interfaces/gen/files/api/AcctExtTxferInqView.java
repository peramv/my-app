
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Reserved view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctExtTxferInq.doc">AcctExtTxferInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctExtTxferInqView extends IFastView implements Serializable
{


   /**
    * Constructs the AcctExtTxferInqView object.
    * 
    */
   public AcctExtTxferInqView()
   {
      super ( new AcctExtTxferInqRequest() );
   }

   /**
    * Constructs the AcctExtTxferInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctExtTxferInqView( String hostEncoding )
   {
      super ( new AcctExtTxferInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctExtTxferInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctExtTxferInqRequest object.
    */
   public final AcctExtTxferInqRequest getRequest()
   {
      return (AcctExtTxferInqRequest)getIFastRequest();
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
      
