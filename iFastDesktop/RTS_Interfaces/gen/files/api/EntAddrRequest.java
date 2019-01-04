// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Entity Address Information Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/EntAddr.doc">EntAddr.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntAddrRequest extends IFastRequest implements Serializable
{

   /**
    * Enitity ID member variable.
    */
   private String _EntityId = "0";
            
            
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
    * Entity Address Id member variable.
    */
   private String _EntityAddrId = "0";
            
            
            
            
   /**
    * Search Type member variable.
    */
   private String _SrchType = "";
            
   /**
    * Entity's First Name member variable.
    */
   private String _SrchFirstName = "";
            
   /**
    * Entity's Last Name member variable.
    */
   private String _SrchLastName = "";
            
   /**
    * Postal Code member variable.
    */
   private String _SrchPSTL = "";
            
   /**
    * Country Code member variable.
    */
   private String _SrchCountry = "";
            
   /**
    * City member variable.
    */
   private String _SrchCity = "";
            
   /**
    * Address Line 1 member variable.
    */
   private String _SrchAddrLine1 = "";
            

   /**
    * Constructs the EntAddrRequest object.
    * 
    */
   EntAddrRequest()
   {
      super ( 71 );
   }

   /**
    * Constructs the EntAddrRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EntAddrRequest( String hostEncoding )
   {
      super ( 71, hostEncoding );
   }

   /**
    * Sets the Enitity ID field for the request.
    * 
    * @param value  Value that the Enitity ID will be set to.
    */
   public final void setEntityId( String value )
   {
      assertUnsent();
      _EntityId = value;
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
    * Sets the Entity Address Id field for the request.
    * 
    * @param value  Value that the Entity Address Id will be set to.
    */
   public final void setEntityAddrId( String value )
   {
      assertUnsent();
      _EntityAddrId = value;
   }
	
   /**
    * Sets the Search Type field for the request.
    * 
    * @param value  Value that the Search Type will be set to.
    */
   public final void setSrchType( String value )
   {
      assertUnsent();
      _SrchType = value;
   }
	
   /**
    * Sets the Entity's First Name field for the request.
    * 
    * @param value  Value that the Entity's First Name will be set to.
    */
   public final void setSrchFirstName( String value )
   {
      assertUnsent();
      _SrchFirstName = value;
   }
	
   /**
    * Sets the Entity's Last Name field for the request.
    * 
    * @param value  Value that the Entity's Last Name will be set to.
    */
   public final void setSrchLastName( String value )
   {
      assertUnsent();
      _SrchLastName = value;
   }
	
   /**
    * Sets the Postal Code field for the request.
    * 
    * @param value  Value that the Postal Code will be set to.
    */
   public final void setSrchPSTL( String value )
   {
      assertUnsent();
      _SrchPSTL = value;
   }
	
   /**
    * Sets the Country Code field for the request.
    * 
    * @param value  Value that the Country Code will be set to.
    */
   public final void setSrchCountry( String value )
   {
      assertUnsent();
      _SrchCountry = value;
   }
	
   /**
    * Sets the City field for the request.
    * 
    * @param value  Value that the City will be set to.
    */
   public final void setSrchCity( String value )
   {
      assertUnsent();
      _SrchCity = value;
   }
	
   /**
    * Sets the Address Line 1 field for the request.
    * 
    * @param value  Value that the Address Line 1 will be set to.
    */
   public final void setSrchAddrLine1( String value )
   {
      assertUnsent();
      _SrchAddrLine1 = value;
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
      requestBuffer.appendField( _EntityId );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _EntityAddrId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _SrchType );
      requestBuffer.appendField( _SrchFirstName );
      requestBuffer.appendField( _SrchLastName );
      requestBuffer.appendField( _SrchPSTL );
      requestBuffer.appendField( _SrchCountry );
      requestBuffer.appendField( _SrchCity );
      requestBuffer.appendField( _SrchAddrLine1 );
   }

}

