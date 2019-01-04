// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Sessions Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/SessionInq.doc">SessionInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SessionInqRequest extends IFastRequest implements Serializable
{

   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
            
            
   /**
    * Session Date member variable.
    */
   private Date _SessionDate = null;
            
   /**
    * Password member variable.
    */
   private String _Password = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            

   /**
    * Constructs the SessionInqRequest object.
    * 
    */
   SessionInqRequest()
   {
      super ( 360 );
   }

   /**
    * Constructs the SessionInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SessionInqRequest( String hostEncoding )
   {
      super ( 360, hostEncoding );
   }

   /**
    * Sets the UserId field for the request.
    * 
    * @param value  Value that the UserId will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Session Date field for the request.
    * 
    * @param value  Value that the Session Date will be set to.
    */
   public final void setSessionDate( Date value )
   {
      assertUnsent();
      _SessionDate = value;
   }
	
   /**
    * Sets the Password field for the request.
    * 
    * @param value  Value that the Password will be set to.
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
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _SessionDate );
      requestBuffer.appendField( _Password );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
   }

}

