
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shareholder Remarks view.
 * For additional view information see <A HREF="../../../../viewspecs/ShrRemarks.doc">ShrRemarks.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrRemarksView extends IFastView implements Serializable
{

   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
   

   /**
    * Constructs the ShrRemarksView object.
    * 
    */
   public ShrRemarksView()
   {
      super ( new ShrRemarksRequest() );
   }

   /**
    * Constructs the ShrRemarksView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShrRemarksView( String hostEncoding )
   {
      super ( new ShrRemarksRequest( hostEncoding ) );
   }

   /**
    * Gets the ShrRemarksRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShrRemarksRequest object.
    */
   public final ShrRemarksRequest getRequest()
   {
      return (ShrRemarksRequest)getIFastRequest();
   }
        
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate()
   {
      return _EffectiveDate;
   }
	
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( Date defaultValue )
   {
      return _EffectiveDate == null ? defaultValue : _EffectiveDate;
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
      _EffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
