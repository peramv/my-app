
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Decode Account Identifier view.
 * For additional view information see <A HREF="../../../../viewspecs/DecodeAccIDInq.doc">DecodeAccIDInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DecodeAccIDInqView extends IFastView implements Serializable
{

   /**
    * Account Number member variable.
    */
   private String _AccountNum = null;
   
   /**
    * Shareholder Number member variable.
    */
   private String _ShareHoldNum = null;
   

   /**
    * Constructs the DecodeAccIDInqView object.
    * 
    */
   public DecodeAccIDInqView()
   {
      super ( new DecodeAccIDInqRequest() );
   }

   /**
    * Constructs the DecodeAccIDInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public DecodeAccIDInqView( String hostEncoding )
   {
      super ( new DecodeAccIDInqRequest( hostEncoding ) );
   }

   /**
    * Gets the DecodeAccIDInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The DecodeAccIDInqRequest object.
    */
   public final DecodeAccIDInqRequest getRequest()
   {
      return (DecodeAccIDInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Account Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Number or null.
    */
   public final String getAccountNum()
   {
      return _AccountNum;
   }
	
   /**
    * Gets the Account Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getAccountNum( String defaultValue )
   {
      return _AccountNum == null ? defaultValue : _AccountNum;
   }
                  
   /**
    * Gets the Shareholder Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Number or null.
    */
   public final String getShareHoldNum()
   {
      return _ShareHoldNum;
   }
	
   /**
    * Gets the Shareholder Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final String getShareHoldNum( String defaultValue )
   {
      return _ShareHoldNum == null ? defaultValue : _ShareHoldNum;
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
      _AccountNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _ShareHoldNum = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
