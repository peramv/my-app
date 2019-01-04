// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * KYC  Document List Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/KCYDocListInq.doc">KCYDocListInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class KCYDocListInqRequest extends IFastRequest implements Serializable
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
    * Entity  ID member variable.
    */
   private String _EntityID = "0";
            
   /**
    * Type of the Regulatory Standard member variable.
    */
   private String _ComplyRule = "";
            
   /**
    * ID of the Regulatory Standard member variable.
    */
   private String _ComplyCodeID = "";
            

   /**
    * Constructs the KCYDocListInqRequest object.
    * 
    */
   KCYDocListInqRequest()
   {
      super ( 389 );
   }

   /**
    * Constructs the KCYDocListInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   KCYDocListInqRequest( String hostEncoding )
   {
      super ( 389, hostEncoding );
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
    * Sets the Entity  ID field for the request.
    * 
    * @param value  Value that the Entity  ID will be set to.
    */
   public final void setEntityID( String value )
   {
      assertUnsent();
      _EntityID = value;
   }
	
   /**
    * Sets the Type of the Regulatory Standard field for the request.
    * 
    * @param value  Value that the Type of the Regulatory Standard will be set to.
    */
   public final void setComplyRule( String value )
   {
      assertUnsent();
      _ComplyRule = value;
   }
	
   /**
    * Sets the ID of the Regulatory Standard field for the request.
    * 
    * @param value  Value that the ID of the Regulatory Standard will be set to.
    */
   public final void setComplyCodeID( String value )
   {
      assertUnsent();
      _ComplyCodeID = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _EntityID );
      requestBuffer.appendField( _ComplyRule );
      requestBuffer.appendField( _ComplyCodeID );
   }

}

