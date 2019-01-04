// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Affluent Flag Validation Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AffluentChgInq.doc">AffluentChgInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class AffluentChgInqRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Link Account member variable.
    */
   private Boolean _LinkAccount = new Boolean(false);
            
   /**
    * Affluent Flag From member variable.
    */
   private String _AffluentFlgFrom = "";
            
   /**
    * Affluent Flag To member variable.
    */
   private String _AffluentFlgTo = "";
            

   /**
    * Constructs the AffluentChgInqRequest object.
    * 
    */
   AffluentChgInqRequest()
   {
      super ( 385 );
   }

   /**
    * Constructs the AffluentChgInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AffluentChgInqRequest( String hostEncoding )
   {
      super ( 385, hostEncoding );
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
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Link Account field for the request.
    * 
    * @param value  Value that the Link Account will be set to.
    */
   public final void setLinkAccount( Boolean value )
   {
      assertUnsent();
      _LinkAccount = value;
   }
	
   /**
    * Sets the Affluent Flag From field for the request.
    * 
    * @param value  Value that the Affluent Flag From will be set to.
    */
   public final void setAffluentFlgFrom( String value )
   {
      assertUnsent();
      _AffluentFlgFrom = value;
   }
	
   /**
    * Sets the Affluent Flag To field for the request.
    * 
    * @param value  Value that the Affluent Flag To will be set to.
    */
   public final void setAffluentFlgTo( String value )
   {
      assertUnsent();
      _AffluentFlgTo = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _LinkAccount );
      requestBuffer.appendField( _AffluentFlgFrom );
      requestBuffer.appendField( _AffluentFlgTo );
   }

}

