// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * eInvestor Registration request.
 * For additional view information see <A HREF="../../../../viewspecs/InvRgstrn.doc">InvRgstrn.doc</A>.
 * 
 * @author RTS Generated
 */
public class InvRgstrnRequest extends IFastRequest implements Serializable
{

            
            
   /**
    * CompanyID member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Language member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * First Name member variable.
    */
   private String _FirstName = "";
            
   /**
    * Last Name member variable.
    */
   private String _LastName = "";
            
   /**
    * Postal Code member variable.
    */
   private String _PostalCode = "";
            
   /**
    * Mode - 1 - NewUser, 2 - Existing User member variable.
    */
   private String _Mode = "";
            
   /**
    * User ID member variable.
    */
   private String _User_Id = "";
            
   /**
    * Password member variable.
    */
   private String _Passwd = "";
            
   /**
    * ValidateSIN member variable.
    */
   private Boolean _ValidateSIN = new Boolean(false);
            
   /**
    * IDValue member variable.
    */
   private String _IDValue = "";
            

   /**
    * Constructs the InvRgstrnRequest object.
    * 
    */
   InvRgstrnRequest()
   {
      super ( 187 );
   }

   /**
    * Constructs the InvRgstrnRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   InvRgstrnRequest( String hostEncoding )
   {
      super ( 187, hostEncoding );
   }

   /**
    * Sets the CompanyID field for the request.
    * 
    * @param value  Value that the CompanyID will be set to.
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
    * Sets the First Name field for the request.
    * 
    * @param value  Value that the First Name will be set to.
    */
   public final void setFirstName( String value )
   {
      assertUnsent();
      _FirstName = value;
   }
	
   /**
    * Sets the Last Name field for the request.
    * 
    * @param value  Value that the Last Name will be set to.
    */
   public final void setLastName( String value )
   {
      assertUnsent();
      _LastName = value;
   }
	
   /**
    * Sets the Postal Code field for the request.
    * 
    * @param value  Value that the Postal Code will be set to.
    */
   public final void setPostalCode( String value )
   {
      assertUnsent();
      _PostalCode = value;
   }
	
   /**
    * Sets the Mode - 1 - NewUser, 2 - Existing User field for the request.
    * 
    * @param value  Value that the Mode - 1 - NewUser, 2 - Existing User will be set to.
    */
   public final void setMode( String value )
   {
      assertUnsent();
      _Mode = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Password field for the request.
    * 
    * @param value  Value that the Password will be set to.
    */
   public final void setPasswd( String value )
   {
      assertUnsent();
      _Passwd = value;
   }
	
   /**
    * Sets the ValidateSIN field for the request.
    * 
    * @param value  Value that the ValidateSIN will be set to.
    */
   public final void setValidateSIN( Boolean value )
   {
      assertUnsent();
      _ValidateSIN = value;
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
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FirstName );
      requestBuffer.appendField( _LastName );
      requestBuffer.appendField( _PostalCode );
      requestBuffer.appendField( _Mode );
      requestBuffer.appendField( _User_Id );
      requestBuffer.appendField( _Passwd );
      requestBuffer.appendField( _ValidateSIN );
      requestBuffer.appendField( _IDValue );
   }

}

