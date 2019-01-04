
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Update Default Allocations view.
 * For additional view information see <A HREF="../../../../viewspecs/UpDefAllocations.doc">UpDefAllocations.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpDefAllocationsView extends IFastView implements Serializable
{

   /**
    * Update Status member variable.
    */
   private Boolean _UpdateStatus = null;
   

   /**
    * Constructs the UpDefAllocationsView object.
    * 
    */
   public UpDefAllocationsView()
   {
      super ( new UpDefAllocationsRequest() );
   }

   /**
    * Constructs the UpDefAllocationsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public UpDefAllocationsView( String hostEncoding )
   {
      super ( new UpDefAllocationsRequest( hostEncoding ) );
   }

   /**
    * Gets the UpDefAllocationsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The UpDefAllocationsRequest object.
    */
   public final UpDefAllocationsRequest getRequest()
   {
      return (UpDefAllocationsRequest)getIFastRequest();
   }
        
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Update Status or null.
    */
   public final Boolean getUpdateStatus()
   {
      return _UpdateStatus;
   }
	
   /**
    * Gets the Update Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Update Status or the specified default value.
    */
   public final boolean getUpdateStatus( boolean defaultValue )
   {
      return _UpdateStatus == null ? defaultValue : _UpdateStatus.booleanValue();
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
      _UpdateStatus = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
