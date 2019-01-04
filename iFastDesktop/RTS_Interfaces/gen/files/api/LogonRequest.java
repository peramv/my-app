// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * User logon request.
 * For additional view information see <A HREF="../../../../viewspecs/Logon.doc">Logon.doc</A>.
 * 
 * @author RTS Generated
 */
public class LogonRequest extends IFastRequest implements Serializable
{

   /**
    * User's id member variable.
    */
   private String _User_Id = "";
            
   /**
    * User's password member variable.
    */
   private String _Password = "";
            
            
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            

   /**
    * Constructs the LogonRequest object.
    * 
    */
   LogonRequest()
   {
      super ( 1 );
   }

   /**
    * Constructs the LogonRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   LogonRequest( String hostEncoding )
   {
      super ( 1, hostEncoding );
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
    * Sets the User's password field for the request.
    * 
    * @param value  Value that the User's password will be set to.
    */
   public final void setPassword( String value )
   {
      assertUnsent();
      _Password = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
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
      requestBuffer.appendField( _Password );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
   }

}

