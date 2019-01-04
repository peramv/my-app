// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Delivery Methods for Entities request.
 * For additional view information see <A HREF="../../../../viewspecs/DelivMethEntReq.doc">DelivMethEntReq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DelivMethEntReqRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
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
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Account Nuimber member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Entity Type member variable.
    */
   private String _EntityType = "";
            
   /**
    * Entity Type Sequence member variable.
    */
   private Integer _EntityTypeSeq = null;
            
            
            
            
   /**
    * Request Type member variable.
    */
   private String _RequestType = "";
            

   /**
    * Constructs the DelivMethEntReqRequest object.
    * 
    */
   DelivMethEntReqRequest()
   {
      super ( 214 );
   }

   /**
    * Constructs the DelivMethEntReqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DelivMethEntReqRequest( String hostEncoding )
   {
      super ( 214, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
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
    * Sets the Account Nuimber field for the request.
    * 
    * @param value  Value that the Account Nuimber will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Entity Type field for the request.
    * 
    * @param value  Value that the Entity Type will be set to.
    */
   public final void setEntityType( String value )
   {
      assertUnsent();
      _EntityType = value;
   }
	
   /**
    * Sets the Entity Type Sequence field for the request.
    * 
    * @param value  Value that the Entity Type Sequence will be set to.
    */
   public final void setEntityTypeSeq( Integer value )
   {
      assertUnsent();
      _EntityTypeSeq = value;
   }
	
   /**
    * Sets the Request Type field for the request.
    * 
    * @param value  Value that the Request Type will be set to.
    */
   public final void setRequestType( String value )
   {
      assertUnsent();
      _RequestType = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _EntityType );
      requestBuffer.appendField( _EntityTypeSeq );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _RequestType );
   }

}

