
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * SWP Amount Calculation for GWA/LWA Option view.
 * For additional view information see <A HREF="../../../../viewspecs/SWPAmtCalc.doc">SWPAmtCalc.doc</A>.
 * 
 * @author RTS Generated
 */
public class SWPAmtCalcView extends IFastView implements Serializable
{

   /**
    * SWP Calculation Amount member variable.
    */
   private String _SWPCalcAmount = null;
   

   /**
    * Constructs the SWPAmtCalcView object.
    * 
    */
   public SWPAmtCalcView()
   {
      super ( new SWPAmtCalcRequest() );
   }

   /**
    * Constructs the SWPAmtCalcView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SWPAmtCalcView( String hostEncoding )
   {
      super ( new SWPAmtCalcRequest( hostEncoding ) );
   }

   /**
    * Gets the SWPAmtCalcRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SWPAmtCalcRequest object.
    */
   public final SWPAmtCalcRequest getRequest()
   {
      return (SWPAmtCalcRequest)getIFastRequest();
   }
        
   /**
    * Gets the SWP Calculation Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SWP Calculation Amount or null.
    */
   public final String getSWPCalcAmount()
   {
      return _SWPCalcAmount;
   }
	
   /**
    * Gets the SWP Calculation Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SWP Calculation Amount or the specified default value.
    */
   public final String getSWPCalcAmount( String defaultValue )
   {
      return _SWPCalcAmount == null ? defaultValue : _SWPCalcAmount;
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
      _SWPCalcAmount = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
