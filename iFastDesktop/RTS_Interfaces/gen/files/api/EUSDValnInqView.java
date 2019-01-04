
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * EUSD Validation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/EUSDValnInq.doc">EUSDValnInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class EUSDValnInqView extends IFastView implements Serializable
{

   /**
    * EUSD Error Status member variable.
    */
   private Integer _EUSDStatus = null;
   

   /**
    * Constructs the EUSDValnInqView object.
    * 
    */
   public EUSDValnInqView()
   {
      super ( new EUSDValnInqRequest() );
   }

   /**
    * Constructs the EUSDValnInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public EUSDValnInqView( String hostEncoding )
   {
      super ( new EUSDValnInqRequest( hostEncoding ) );
   }

   /**
    * Gets the EUSDValnInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The EUSDValnInqRequest object.
    */
   public final EUSDValnInqRequest getRequest()
   {
      return (EUSDValnInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the EUSD Error Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EUSD Error Status or null.
    */
   public final Integer getEUSDStatus()
   {
      return _EUSDStatus;
   }
	
   /**
    * Gets the EUSD Error Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EUSD Error Status or the specified default value.
    */
   public final int getEUSDStatus( int defaultValue )
   {
      return _EUSDStatus == null ? defaultValue : _EUSDStatus.intValue();
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
      _EUSDStatus = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
