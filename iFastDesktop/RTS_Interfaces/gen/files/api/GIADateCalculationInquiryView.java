
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * GIA Date Calculation Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/GIADateCalculationInquiry.doc">GIADateCalculationInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class GIADateCalculationInquiryView extends IFastView implements Serializable
{

   /**
    * Maturity Date member variable.
    */
   private Date _MaturityDate = null;
   
   /**
    * Next Interest Date member variable.
    */
   private Date _NextIntCredDate = null;
   

   /**
    * Constructs the GIADateCalculationInquiryView object.
    * 
    */
   public GIADateCalculationInquiryView()
   {
      super ( new GIADateCalculationInquiryRequest() );
   }

   /**
    * Constructs the GIADateCalculationInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public GIADateCalculationInquiryView( String hostEncoding )
   {
      super ( new GIADateCalculationInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the GIADateCalculationInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The GIADateCalculationInquiryRequest object.
    */
   public final GIADateCalculationInquiryRequest getRequest()
   {
      return (GIADateCalculationInquiryRequest)getIFastRequest();
   }
        
   /**
    * Gets the Maturity Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Maturity Date or null.
    */
   public final Date getMaturityDate()
   {
      return _MaturityDate;
   }
	
   /**
    * Gets the Maturity Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Date or the specified default value.
    */
   public final Date getMaturityDate( Date defaultValue )
   {
      return _MaturityDate == null ? defaultValue : _MaturityDate;
   }
                  
   /**
    * Gets the Next Interest Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Next Interest Date or null.
    */
   public final Date getNextIntCredDate()
   {
      return _NextIntCredDate;
   }
	
   /**
    * Gets the Next Interest Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Interest Date or the specified default value.
    */
   public final Date getNextIntCredDate( Date defaultValue )
   {
      return _NextIntCredDate == null ? defaultValue : _NextIntCredDate;
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
      _MaturityDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _NextIntCredDate = responseBuffer.decodeDate(responseBuffer.getNextField());
                  

   }

}
      
