
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Calculation of Discount Rate view.
 * For additional view information see <A HREF="../../../../viewspecs/CalcDiscRate.doc">CalcDiscRate.doc</A>.
 * 
 * @author RTS Generated
 */
public class CalcDiscRateView extends IFastView implements Serializable
{

   /**
    * Commission Discount member variable.
    */
   private String _CommissionDiscount = null;
   

   /**
    * Constructs the CalcDiscRateView object.
    * 
    */
   public CalcDiscRateView()
   {
      super ( new CalcDiscRateRequest() );
   }

   /**
    * Constructs the CalcDiscRateView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public CalcDiscRateView( String hostEncoding )
   {
      super ( new CalcDiscRateRequest( hostEncoding ) );
   }

   /**
    * Gets the CalcDiscRateRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The CalcDiscRateRequest object.
    */
   public final CalcDiscRateRequest getRequest()
   {
      return (CalcDiscRateRequest)getIFastRequest();
   }
        
   /**
    * Gets the Commission Discount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commission Discount or null.
    */
   public final String getCommissionDiscount()
   {
      return _CommissionDiscount;
   }
	
   /**
    * Gets the Commission Discount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Discount or the specified default value.
    */
   public final String getCommissionDiscount( String defaultValue )
   {
      return _CommissionDiscount == null ? defaultValue : _CommissionDiscount;
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
      _CommissionDiscount = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
