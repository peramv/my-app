
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Modify/Cancel Trade Edits view.
 * For additional view information see <A HREF="../../../../viewspecs/DuplicateTradeInquiry.doc">DuplicateTradeInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class DuplicateTradeInquiryView extends IFastView implements Serializable
{


   /**
    * Constructs the DuplicateTradeInquiryView object.
    * 
    */
   public DuplicateTradeInquiryView()
   {
      super ( new DuplicateTradeInquiryRequest() );
   }

   /**
    * Constructs the DuplicateTradeInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DuplicateTradeInquiryView( String hostEncoding )
   {
      super ( new DuplicateTradeInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the DuplicateTradeInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DuplicateTradeInquiryRequest object.
    */
   public final DuplicateTradeInquiryRequest getRequest()
   {
      return (DuplicateTradeInquiryRequest)getIFastRequest();
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
      
