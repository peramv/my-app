
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Default Regulatory Standard Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/DeftRegStdInq.doc">DeftRegStdInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DeftRegStdInqView extends IFastView implements Serializable
{

   /**
    * Comply Master UUID member variable.
    */
   private String _ComplyMstrUUID = null;
   

   /**
    * Constructs the DeftRegStdInqView object.
    * 
    */
   public DeftRegStdInqView()
   {
      super ( new DeftRegStdInqRequest() );
   }

   /**
    * Constructs the DeftRegStdInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DeftRegStdInqView( String hostEncoding )
   {
      super ( new DeftRegStdInqRequest( hostEncoding ) );
   }

   /**
    * Gets the DeftRegStdInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DeftRegStdInqRequest object.
    */
   public final DeftRegStdInqRequest getRequest()
   {
      return (DeftRegStdInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Comply Master UUID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Comply Master UUID or null.
    */
   public final String getComplyMstrUUID()
   {
      return _ComplyMstrUUID;
   }
	
   /**
    * Gets the Comply Master UUID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comply Master UUID or the specified default value.
    */
   public final String getComplyMstrUUID( String defaultValue )
   {
      return _ComplyMstrUUID == null ? defaultValue : _ComplyMstrUUID;
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
      _ComplyMstrUUID = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
