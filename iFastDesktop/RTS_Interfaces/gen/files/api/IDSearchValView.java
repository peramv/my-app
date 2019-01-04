
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * ID Search Validation view.
 * For additional view information see <A HREF="../../../../viewspecs/IDSearchVal.doc">IDSearchVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class IDSearchValView extends IFastView implements Serializable
{

   /**
    * flag to indicate if ID is valid member variable.
    */
   private Boolean _IsValid = null;
   

   /**
    * Constructs the IDSearchValView object.
    * 
    */
   public IDSearchValView()
   {
      super ( new IDSearchValRequest() );
   }

   /**
    * Constructs the IDSearchValView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public IDSearchValView( String hostEncoding )
   {
      super ( new IDSearchValRequest( hostEncoding ) );
   }

   /**
    * Gets the IDSearchValRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The IDSearchValRequest object.
    */
   public final IDSearchValRequest getRequest()
   {
      return (IDSearchValRequest)getIFastRequest();
   }
        
   /**
    * Gets the flag to indicate if ID is valid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the flag to indicate if ID is valid or null.
    */
   public final Boolean getIsValid()
   {
      return _IsValid;
   }
	
   /**
    * Gets the flag to indicate if ID is valid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the flag to indicate if ID is valid or the specified default value.
    */
   public final boolean getIsValid( boolean defaultValue )
   {
      return _IsValid == null ? defaultValue : _IsValid.booleanValue();
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
      _IsValid = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
