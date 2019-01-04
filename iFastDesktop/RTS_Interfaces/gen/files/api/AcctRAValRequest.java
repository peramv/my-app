// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Registration Agent Validation request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctRAVal.doc">AcctRAVal.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctRAValRequest extends IFastRequest implements Serializable
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
    * Tax Type member variable.
    */
   private String _TaxType = "";
            
   /**
    * EntityId member variable.
    */
   private String _EntityId = "0";
            
   /**
    * National ID member variable.
    */
   private String _NationalID = "";
            
   /**
    * Country of Issue NationalID member variable.
    */
   private String _COINationalID = "";
            
   /**
    * Passport ID member variable.
    */
   private String _PassportID = "";
            
   /**
    * Country Of Issue PassportID member variable.
    */
   private String _COIPassportID = "";
            

   /**
    * Constructs the AcctRAValRequest object.
    * 
    */
   AcctRAValRequest()
   {
      super ( 446 );
   }

   /**
    * Constructs the AcctRAValRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctRAValRequest( String hostEncoding )
   {
      super ( 446, hostEncoding );
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
    * Sets the Tax Type field for the request.
    * 
    * @param value  Value that the Tax Type will be set to.
    */
   public final void setTaxType( String value )
   {
      assertUnsent();
      _TaxType = value;
   }
	
   /**
    * Sets the EntityId field for the request.
    * 
    * @param value  Value that the EntityId will be set to.
    */
   public final void setEntityId( String value )
   {
      assertUnsent();
      _EntityId = value;
   }
	
   /**
    * Sets the National ID field for the request.
    * 
    * @param value  Value that the National ID will be set to.
    */
   public final void setNationalID( String value )
   {
      assertUnsent();
      _NationalID = value;
   }
	
   /**
    * Sets the Country of Issue NationalID field for the request.
    * 
    * @param value  Value that the Country of Issue NationalID will be set to.
    */
   public final void setCOINationalID( String value )
   {
      assertUnsent();
      _COINationalID = value;
   }
	
   /**
    * Sets the Passport ID field for the request.
    * 
    * @param value  Value that the Passport ID will be set to.
    */
   public final void setPassportID( String value )
   {
      assertUnsent();
      _PassportID = value;
   }
	
   /**
    * Sets the Country Of Issue PassportID field for the request.
    * 
    * @param value  Value that the Country Of Issue PassportID will be set to.
    */
   public final void setCOIPassportID( String value )
   {
      assertUnsent();
      _COIPassportID = value;
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
      requestBuffer.appendField( _TaxType );
      requestBuffer.appendField( _EntityId );
      requestBuffer.appendField( _NationalID );
      requestBuffer.appendField( _COINationalID );
      requestBuffer.appendField( _PassportID );
      requestBuffer.appendField( _COIPassportID );
   }

}

