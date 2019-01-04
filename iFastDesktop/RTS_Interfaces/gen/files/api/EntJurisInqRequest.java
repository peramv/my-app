// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Entity Regulatory Jurisdiction Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/EntJurisInq.doc">EntJurisInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntJurisInqRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Compayny Id member variable.
    */
   private String _CompanyId = "";
            
            
            
            
   /**
    * Account Number member variable.
    */
   private String _rxAccountNum = "0";
            
   /**
    * Entity Id member variable.
    */
   private String _rxEntityId = "0";
            

   /**
    * Constructs the EntJurisInqRequest object.
    * 
    */
   EntJurisInqRequest()
   {
      super ( 458 );
   }

   /**
    * Constructs the EntJurisInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EntJurisInqRequest( String hostEncoding )
   {
      super ( 458, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
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
    * Sets the Compayny Id field for the request.
    * 
    * @param value  Value that the Compayny Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setrxAccountNum( String value )
   {
      assertUnsent();
      _rxAccountNum = value;
   }
	
   /**
    * Sets the Entity Id field for the request.
    * 
    * @param value  Value that the Entity Id will be set to.
    */
   public final void setrxEntityId( String value )
   {
      assertUnsent();
      _rxEntityId = value;
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
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _rxAccountNum );
      requestBuffer.appendField( _rxEntityId );
   }

}

