// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Informaiton request.
 * For additional view information see <A HREF="../../../../viewspecs/AccountInformation.doc">AccountInformation.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountInformationRequest extends IFastRequest implements Serializable
{

   /**
    * Entity ID member variable.
    */
   private String _EntityId = "0";
            
   /**
    * Account Number member variable.
    */
   private String _InputAcctNum = "0";
            
   /**
    * Shareholder Number member variable.
    */
   private String _InputShrNum = "0";
            
            
   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * UserId member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
            
            
            

   /**
    * Constructs the AccountInformationRequest object.
    * 
    */
   AccountInformationRequest()
   {
      super ( 4 );
   }

   /**
    * Constructs the AccountInformationRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AccountInformationRequest( String hostEncoding )
   {
      super ( 4, hostEncoding );
   }

   /**
    * Sets the Entity ID field for the request.
    * 
    * @param value  Value that the Entity ID will be set to.
    */
   public final void setEntityId( String value )
   {
      assertUnsent();
      _EntityId = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setInputAcctNum( String value )
   {
      assertUnsent();
      _InputAcctNum = value;
   }
	
   /**
    * Sets the Shareholder Number field for the request.
    * 
    * @param value  Value that the Shareholder Number will be set to.
    */
   public final void setInputShrNum( String value )
   {
      assertUnsent();
      _InputShrNum = value;
   }
	
   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
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
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _EntityId );
      requestBuffer.appendField( _InputAcctNum );
      requestBuffer.appendField( _InputShrNum );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
   }

}

