
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Broker Remarks Update view.
 * For additional view information see <A HREF="../../../../viewspecs/BrkrRemarksUpd.doc">BrkrRemarksUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class BrkrRemarksUpdView extends IFastView implements Serializable
{

   /**
    * UpdateStatus member variable.
    */
   private Boolean _UpdateStatus = null;
   

   /**
    * Constructs the BrkrRemarksUpdView object.
    * 
    */
   public BrkrRemarksUpdView()
   {
      super ( new BrkrRemarksUpdRequest() );
   }

   /**
    * Constructs the BrkrRemarksUpdView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public BrkrRemarksUpdView( String hostEncoding )
   {
      super ( new BrkrRemarksUpdRequest( hostEncoding ) );
   }

   /**
    * Gets the BrkrRemarksUpdRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The BrkrRemarksUpdRequest object.
    */
   public final BrkrRemarksUpdRequest getRequest()
   {
      return (BrkrRemarksUpdRequest)getIFastRequest();
   }
        
   /**
    * Gets the UpdateStatus field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the UpdateStatus or null.
    */
   public final Boolean getUpdateStatus()
   {
      return _UpdateStatus;
   }
	
   /**
    * Gets the UpdateStatus field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UpdateStatus or the specified default value.
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
      
