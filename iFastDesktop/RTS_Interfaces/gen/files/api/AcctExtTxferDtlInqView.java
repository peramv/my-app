
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Reserved view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctExtTxferDtlInq.doc">AcctExtTxferDtlInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctExtTxferDtlInqView extends IFastView implements Serializable
{


   /**
    * Constructs the AcctExtTxferDtlInqView object.
    * 
    */
   public AcctExtTxferDtlInqView()
   {
      super ( new AcctExtTxferDtlInqRequest() );
   }

   /**
    * Constructs the AcctExtTxferDtlInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctExtTxferDtlInqView( String hostEncoding )
   {
      super ( new AcctExtTxferDtlInqRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctExtTxferDtlInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctExtTxferDtlInqRequest object.
    */
   public final AcctExtTxferDtlInqRequest getRequest()
   {
      return (AcctExtTxferDtlInqRequest)getIFastRequest();
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
      
