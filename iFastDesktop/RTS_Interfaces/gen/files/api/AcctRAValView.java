
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Registration Agent Validation view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctRAVal.doc">AcctRAVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctRAValView extends IFastView implements Serializable
{

   /**
    * Warning Code member variable.
    */
   private Integer _WarnCode = null;
   

   /**
    * Constructs the AcctRAValView object.
    * 
    */
   public AcctRAValView()
   {
      super ( new AcctRAValRequest() );
   }

   /**
    * Constructs the AcctRAValView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctRAValView( String hostEncoding )
   {
      super ( new AcctRAValRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctRAValRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctRAValRequest object.
    */
   public final AcctRAValRequest getRequest()
   {
      return (AcctRAValRequest)getIFastRequest();
   }
        
   /**
    * Gets the Warning Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Warning Code or null.
    */
   public final Integer getWarnCode()
   {
      return _WarnCode;
   }
	
   /**
    * Gets the Warning Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Warning Code or the specified default value.
    */
   public final int getWarnCode( int defaultValue )
   {
      return _WarnCode == null ? defaultValue : _WarnCode.intValue();
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
      _WarnCode = responseBuffer.decodeInteger(responseBuffer.getNextField());
                  

   }

}
      
