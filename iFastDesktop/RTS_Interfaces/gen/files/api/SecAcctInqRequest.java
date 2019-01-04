// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Security Recon - Account Level Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/SecAcctInq.doc">SecAcctInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SecAcctInqRequest extends IFastRequest implements Serializable
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
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
            
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Settlement Location Code member variable.
    */
   private String _SettlLocCode = "";
            
   /**
    * Fund Broker Code member variable.
    */
   private String _FundBrokerCode = "";
            

   /**
    * Constructs the SecAcctInqRequest object.
    * 
    */
   SecAcctInqRequest()
   {
      super ( 269 );
   }

   /**
    * Constructs the SecAcctInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SecAcctInqRequest( String hostEncoding )
   {
      super ( 269, hostEncoding );
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
    * Sets the Settlement Location Code field for the request.
    * 
    * @param value  Value that the Settlement Location Code will be set to.
    */
   public final void setSettlLocCode( String value )
   {
      assertUnsent();
      _SettlLocCode = value;
   }
	
   /**
    * Sets the Fund Broker Code field for the request.
    * 
    * @param value  Value that the Fund Broker Code will be set to.
    */
   public final void setFundBrokerCode( String value )
   {
      assertUnsent();
      _FundBrokerCode = value;
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
      requestBuffer.appendField( _SettlLocCode );
      requestBuffer.appendField( _FundBrokerCode );
   }

}

