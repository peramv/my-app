// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * eInvestor UserId Setup request.
 * For additional view information see <A HREF="../../../../viewspecs/InvIDSetup.doc">InvIDSetup.doc</A>.
 * 
 * @author RTS Generated
 */
public class InvIDSetupRequest extends IFastRequest implements Serializable
{

   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Language member variable.
    */
   private String _LanguageCode = "";
            
            
            
   /**
    * EntityID member variable.
    */
   private String _EntityID = "0";
            
   /**
    * Mode member variable.
    */
   private String _Mode = "";
            
   /**
    * Preferred Currency member variable.
    */
   private String _Currency = "";
            
   /**
    * Memorable Date - security validation member variable.
    */
   private Date _MemorableDate = null;
            
   /**
    * Relationship for memorable date member variable.
    */
   private String _MemorableDateReln = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Password member variable.
    */
   private String _Password = "";
            
   /**
    * IDValue member variable.
    */
   private String _IDValue = "";
            
   /**
    * IDType member variable.
    */
   private String _IDType = "";
            
   /**
    * UserType member variable.
    */
   private String _UserType = "";
            

   /**
    * Constructs the InvIDSetupRequest object.
    * 
    */
   InvIDSetupRequest()
   {
      super ( 188 );
   }

   /**
    * Constructs the InvIDSetupRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   InvIDSetupRequest( String hostEncoding )
   {
      super ( 188, hostEncoding );
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
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Language field for the request.
    * 
    * @param value  Value that the Language will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the EntityID field for the request.
    * 
    * @param value  Value that the EntityID will be set to.
    */
   public final void setEntityID( String value )
   {
      assertUnsent();
      _EntityID = value;
   }
	
   /**
    * Sets the Mode field for the request.
    * 
    * @param value  Value that the Mode will be set to.
    */
   public final void setMode( String value )
   {
      assertUnsent();
      _Mode = value;
   }
	
   /**
    * Sets the Preferred Currency field for the request.
    * 
    * @param value  Value that the Preferred Currency will be set to.
    */
   public final void setCurrency( String value )
   {
      assertUnsent();
      _Currency = value;
   }
	
   /**
    * Sets the Memorable Date - security validation field for the request.
    * 
    * @param value  Value that the Memorable Date - security validation will be set to.
    */
   public final void setMemorableDate( Date value )
   {
      assertUnsent();
      _MemorableDate = value;
   }
	
   /**
    * Sets the Relationship for memorable date field for the request.
    * 
    * @param value  Value that the Relationship for memorable date will be set to.
    */
   public final void setMemorableDateReln( String value )
   {
      assertUnsent();
      _MemorableDateReln = value;
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
    * Sets the IDValue field for the request.
    * 
    * @param value  Value that the IDValue will be set to.
    */
   public final void setIDValue( String value )
   {
      assertUnsent();
      _IDValue = value;
   }
	
   /**
    * Sets the IDType field for the request.
    * 
    * @param value  Value that the IDType will be set to.
    */
   public final void setIDType( String value )
   {
      assertUnsent();
      _IDType = value;
   }
	
   /**
    * Sets the UserType field for the request.
    * 
    * @param value  Value that the UserType will be set to.
    */
   public final void setUserType( String value )
   {
      assertUnsent();
      _UserType = value;
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
      requestBuffer.appendField( _CompanyId );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _EntityID );
      requestBuffer.appendField( _Mode );
      requestBuffer.appendField( _Currency );
      requestBuffer.appendField( _MemorableDate );
      requestBuffer.appendField( _MemorableDateReln );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _Password );
      requestBuffer.appendField( _IDValue );
      requestBuffer.appendField( _IDType );
      requestBuffer.appendField( _UserType );
   }

}

