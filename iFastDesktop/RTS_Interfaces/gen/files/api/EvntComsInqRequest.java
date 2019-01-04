// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Event Commission Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/EvntComsInq.doc">EvntComsInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class EvntComsInqRequest extends IFastRequest implements Serializable
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
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Account From member variable.
    */
   private String _AcctFrom = "0";
            
   /**
    * Account To member variable.
    */
   private String _AcctTo = "0";
            
   /**
    * Redemption Code member variable.
    */
   private String _RedCode = "";
            

   /**
    * Constructs the EvntComsInqRequest object.
    * 
    */
   EvntComsInqRequest()
   {
      super ( 445 );
   }

   /**
    * Constructs the EvntComsInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EvntComsInqRequest( String hostEncoding )
   {
      super ( 445, hostEncoding );
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
    * Sets the LanguageCode field for the request.
    * 
    * @param value  Value that the LanguageCode will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Account From field for the request.
    * 
    * @param value  Value that the Account From will be set to.
    */
   public final void setAcctFrom( String value )
   {
      assertUnsent();
      _AcctFrom = value;
   }
	
   /**
    * Sets the Account To field for the request.
    * 
    * @param value  Value that the Account To will be set to.
    */
   public final void setAcctTo( String value )
   {
      assertUnsent();
      _AcctTo = value;
   }
	
   /**
    * Sets the Redemption Code field for the request.
    * 
    * @param value  Value that the Redemption Code will be set to.
    */
   public final void setRedCode( String value )
   {
      assertUnsent();
      _RedCode = value;
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
      requestBuffer.appendField( _AcctFrom );
      requestBuffer.appendField( _AcctTo );
      requestBuffer.appendField( _RedCode );
   }

}

