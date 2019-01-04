
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Get Next Fund Broker Code view.
 * For additional view information see <A HREF="../../../../viewspecs/GetFundBrkCode.doc">GetFundBrkCode.doc</A>.
 * 
 * @author RTS Generated
 */
public class GetFundBrkCodeView extends IFastView implements Serializable
{

   /**
    * Fund Broker Code member variable.
    */
   private String _FundBrokerCode = null;
   

   /**
    * Constructs the GetFundBrkCodeView object.
    * 
    */
   public GetFundBrkCodeView()
   {
      super ( new GetFundBrkCodeRequest() );
   }

   /**
    * Constructs the GetFundBrkCodeView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public GetFundBrkCodeView( String hostEncoding )
   {
      super ( new GetFundBrkCodeRequest( hostEncoding ) );
   }

   /**
    * Gets the GetFundBrkCodeRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The GetFundBrkCodeRequest object.
    */
   public final GetFundBrkCodeRequest getRequest()
   {
      return (GetFundBrkCodeRequest)getIFastRequest();
   }
        
   /**
    * Gets the Fund Broker Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund Broker Code or null.
    */
   public final String getFundBrokerCode()
   {
      return _FundBrokerCode;
   }
	
   /**
    * Gets the Fund Broker Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Code or the specified default value.
    */
   public final String getFundBrokerCode( String defaultValue )
   {
      return _FundBrokerCode == null ? defaultValue : _FundBrokerCode;
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
      _FundBrokerCode = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
