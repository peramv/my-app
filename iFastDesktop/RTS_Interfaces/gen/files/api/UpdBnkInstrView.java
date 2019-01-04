
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Update Banking Instructions view.
 * For additional view information see <A HREF="../../../../viewspecs/UpdBnkInstr.doc">UpdBnkInstr.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpdBnkInstrView extends IFastView implements Serializable
{

   /**
    * Update status member variable.
    */
   private Boolean _UpdateStatus = null;
   

   /**
    * Constructs the UpdBnkInstrView object.
    * 
    */
   public UpdBnkInstrView()
   {
      super ( new UpdBnkInstrRequest() );
   }

   /**
    * Constructs the UpdBnkInstrView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public UpdBnkInstrView( String hostEncoding )
   {
      super ( new UpdBnkInstrRequest( hostEncoding ) );
   }

   /**
    * Gets the UpdBnkInstrRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The UpdBnkInstrRequest object.
    */
   public final UpdBnkInstrRequest getRequest()
   {
      return (UpdBnkInstrRequest)getIFastRequest();
   }
        
   /**
    * Gets the Update status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Update status or null.
    */
   public final Boolean getUpdateStatus()
   {
      return _UpdateStatus;
   }
	
   /**
    * Gets the Update status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Update status or the specified default value.
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
      
