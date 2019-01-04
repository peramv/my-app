// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * User logoff request.
 * For additional view information see <A HREF="../../../../viewspecs/Logoff.doc">Logoff.doc</A>.
 * 
 * @author RTS Generated
 */
public class LogoffRequest extends IFastRequest implements Serializable
{

   /**
    * User's id member variable.
    */
   private String _User_Id = "";
            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
            
            
   /**
    * Language member variable.
    */
   private String _LanguageCode = "";
            

   /**
    * Constructs the LogoffRequest object.
    * 
    */
   LogoffRequest()
   {
      super ( 2 );
   }

   /**
    * Constructs the LogoffRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   LogoffRequest( String hostEncoding )
   {
      super ( 2, hostEncoding );
   }

   /**
    * Sets the User's id field for the request.
    * 
    * @param value  Value that the User's id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the Language field for the request.
    * 
    * @param value  Value that the Language will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _User_Id );
      requestBuffer.appendField( _SessionId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
   }

}

