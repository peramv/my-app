
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * International Wire Validation view.
 * For additional view information see <A HREF="../../../../viewspecs/IntlWireVldn.doc">IntlWireVldn.doc</A>.
 * 
 * @author RTS Generated
 */
public class IntlWireVldnView extends IFastView implements Serializable
{

   /**
    * International Wire member variable.
    */
   private Boolean _InternationalWire = null;
   

   /**
    * Constructs the IntlWireVldnView object.
    * 
    */
   public IntlWireVldnView()
   {
      super ( new IntlWireVldnRequest() );
   }

   /**
    * Constructs the IntlWireVldnView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public IntlWireVldnView( String hostEncoding )
   {
      super ( new IntlWireVldnRequest( hostEncoding ) );
   }

   /**
    * Gets the IntlWireVldnRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The IntlWireVldnRequest object.
    */
   public final IntlWireVldnRequest getRequest()
   {
      return (IntlWireVldnRequest)getIFastRequest();
   }
        
   /**
    * Gets the International Wire field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the International Wire or null.
    */
   public final Boolean getInternationalWire()
   {
      return _InternationalWire;
   }
	
   /**
    * Gets the International Wire field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the International Wire or the specified default value.
    */
   public final boolean getInternationalWire( boolean defaultValue )
   {
      return _InternationalWire == null ? defaultValue : _InternationalWire.booleanValue();
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
      _InternationalWire = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
