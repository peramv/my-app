
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Retail Distribution Review Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RDRInq.doc">RDRInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RDRInqView extends IFastView implements Serializable
{

   /**
    * RDR Applicable member variable.
    */
   private String _RDRApplic = null;
   
   /**
    * RDR Default member variable.
    */
   private String _RDRDefault = null;
   

   /**
    * Constructs the RDRInqView object.
    * 
    */
   public RDRInqView()
   {
      super ( new RDRInqRequest() );
   }

   /**
    * Constructs the RDRInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RDRInqView( String hostEncoding )
   {
      super ( new RDRInqRequest( hostEncoding ) );
   }

   /**
    * Gets the RDRInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RDRInqRequest object.
    */
   public final RDRInqRequest getRequest()
   {
      return (RDRInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the RDR Applicable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RDR Applicable or null.
    */
   public final String getRDRApplic()
   {
      return _RDRApplic;
   }
	
   /**
    * Gets the RDR Applicable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RDR Applicable or the specified default value.
    */
   public final String getRDRApplic( String defaultValue )
   {
      return _RDRApplic == null ? defaultValue : _RDRApplic;
   }
                  
   /**
    * Gets the RDR Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RDR Default or null.
    */
   public final String getRDRDefault()
   {
      return _RDRDefault;
   }
	
   /**
    * Gets the RDR Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RDR Default or the specified default value.
    */
   public final String getRDRDefault( String defaultValue )
   {
      return _RDRDefault == null ? defaultValue : _RDRDefault;
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
      _RDRApplic = responseBuffer.decodeString(responseBuffer.getNextField());
      _RDRDefault = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
