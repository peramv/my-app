
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * LIP Rate Check Inq for Purchase view.
 * For additional view information see <A HREF="../../../../viewspecs/LipRateInq.doc">LipRateInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class LipRateInqView extends IFastView implements Serializable
{

   /**
    * Flag indicating if LIP rate exists member variable.
    */
   private Boolean _LIPRateExist = null;
   

   /**
    * Constructs the LipRateInqView object.
    * 
    */
   public LipRateInqView()
   {
      super ( new LipRateInqRequest() );
   }

   /**
    * Constructs the LipRateInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public LipRateInqView( String hostEncoding )
   {
      super ( new LipRateInqRequest( hostEncoding ) );
   }

   /**
    * Gets the LipRateInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The LipRateInqRequest object.
    */
   public final LipRateInqRequest getRequest()
   {
      return (LipRateInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Flag indicating if LIP rate exists field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if LIP rate exists or null.
    */
   public final Boolean getLIPRateExist()
   {
      return _LIPRateExist;
   }
	
   /**
    * Gets the Flag indicating if LIP rate exists field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if LIP rate exists or the specified default value.
    */
   public final boolean getLIPRateExist( boolean defaultValue )
   {
      return _LIPRateExist == null ? defaultValue : _LIPRateExist.booleanValue();
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
      _LIPRateExist = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
