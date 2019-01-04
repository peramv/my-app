
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Negative Commission Validation view.
 * For additional view information see <A HREF="../../../../viewspecs/NegCommValid.doc">NegCommValid.doc</A>.
 * 
 * @author RTS Generated
 */
public class NegCommValidView extends IFastView implements Serializable
{

   /**
    * flag indicating in paying entity has negative commissions member variable.
    */
   private Boolean _NegativeComm = null;
   

   /**
    * Constructs the NegCommValidView object.
    * 
    */
   public NegCommValidView()
   {
      super ( new NegCommValidRequest() );
   }

   /**
    * Constructs the NegCommValidView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public NegCommValidView( String hostEncoding )
   {
      super ( new NegCommValidRequest( hostEncoding ) );
   }

   /**
    * Gets the NegCommValidRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The NegCommValidRequest object.
    */
   public final NegCommValidRequest getRequest()
   {
      return (NegCommValidRequest)getIFastRequest();
   }
        
   /**
    * Gets the flag indicating in paying entity has negative commissions field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the flag indicating in paying entity has negative commissions or null.
    */
   public final Boolean getNegativeComm()
   {
      return _NegativeComm;
   }
	
   /**
    * Gets the flag indicating in paying entity has negative commissions field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag indicating in paying entity has negative commissions or the specified default value.
    */
   public final boolean getNegativeComm( boolean defaultValue )
   {
      return _NegativeComm == null ? defaultValue : _NegativeComm.booleanValue();
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
      _NegativeComm = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
