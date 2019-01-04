
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * AMS Rebalancing Date view.
 * For additional view information see <A HREF="../../../../viewspecs/AMSRebalDte.doc">AMSRebalDte.doc</A>.
 * 
 * @author RTS Generated
 */
public class AMSRebalDteView extends IFastView implements Serializable
{

   /**
    * NextRebalDate member variable.
    */
   private Date _NextRebalDate = null;
   

   /**
    * Constructs the AMSRebalDteView object.
    * 
    */
   public AMSRebalDteView()
   {
      super ( new AMSRebalDteRequest() );
   }

   /**
    * Constructs the AMSRebalDteView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AMSRebalDteView( String hostEncoding )
   {
      super ( new AMSRebalDteRequest( hostEncoding ) );
   }

   /**
    * Gets the AMSRebalDteRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AMSRebalDteRequest object.
    */
   public final AMSRebalDteRequest getRequest()
   {
      return (AMSRebalDteRequest)getIFastRequest();
   }
        
   /**
    * Gets the NextRebalDate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the NextRebalDate or null.
    */
   public final Date getNextRebalDate()
   {
      return _NextRebalDate;
   }
	
   /**
    * Gets the NextRebalDate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NextRebalDate or the specified default value.
    */
   public final Date getNextRebalDate( Date defaultValue )
   {
      return _NextRebalDate == null ? defaultValue : _NextRebalDate;
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
      _NextRebalDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
