
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Identifier Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundIdentifierInq.doc">FundIdentifierInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundIdentifierInqView extends IFastView implements Serializable
{

   /**
    * Fund Code member variable.
    */
   private String _FundCode = null;
   
   /**
    * Class Code member variable.
    */
   private String _ClassCode = null;
   

   /**
    * Constructs the FundIdentifierInqView object.
    * 
    */
   public FundIdentifierInqView()
   {
      super ( new FundIdentifierInqRequest() );
   }

   /**
    * Constructs the FundIdentifierInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundIdentifierInqView( String hostEncoding )
   {
      super ( new FundIdentifierInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundIdentifierInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundIdentifierInqRequest object.
    */
   public final FundIdentifierInqRequest getRequest()
   {
      return (FundIdentifierInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Fund Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode()
   {
      return _FundCode;
   }
	
   /**
    * Gets the Fund Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( String defaultValue )
   {
      return _FundCode == null ? defaultValue : _FundCode;
   }
                  
   /**
    * Gets the Class Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Class Code or null.
    */
   public final String getClassCode()
   {
      return _ClassCode;
   }
	
   /**
    * Gets the Class Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( String defaultValue )
   {
      return _ClassCode == null ? defaultValue : _ClassCode;
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
      _FundCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ClassCode = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
