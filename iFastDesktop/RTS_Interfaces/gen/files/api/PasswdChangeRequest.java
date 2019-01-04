// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Password Change request.
 * For additional view information see <A HREF="../../../../viewspecs/PasswdChange.doc">PasswdChange.doc</A>.
 * 
 * @author RTS Generated
 */
public class PasswdChangeRequest extends IFastRequest implements Serializable
{

   /**
    * User's Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * New Password member variable.
    */
   private String _NewPasswd = "";
            
   /**
    * OldPassword member variable.
    */
   private String _OldPassword = "";
            
            
            

   /**
    * Constructs the PasswdChangeRequest object.
    * 
    */
   PasswdChangeRequest()
   {
      super ( 39 );
   }

   /**
    * Constructs the PasswdChangeRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PasswdChangeRequest( String hostEncoding )
   {
      super ( 39, hostEncoding );
   }

   /**
    * Sets the User's Id field for the request.
    * 
    * @param value  Value that the User's Id will be set to.
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
    * Sets the New Password field for the request.
    * 
    * @param value  Value that the New Password will be set to.
    */
   public final void setNewPasswd( String value )
   {
      assertUnsent();
      _NewPasswd = value;
   }
	
   /**
    * Sets the OldPassword field for the request.
    * 
    * @param value  Value that the OldPassword will be set to.
    */
   public final void setOldPassword( String value )
   {
      assertUnsent();
      _OldPassword = value;
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
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _NewPasswd );
      requestBuffer.appendField( _OldPassword );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
   }

}

