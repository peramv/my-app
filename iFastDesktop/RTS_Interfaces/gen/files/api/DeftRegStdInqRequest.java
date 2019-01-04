// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Default Regulatory Standard Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/DeftRegStdInq.doc">DeftRegStdInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class DeftRegStdInqRequest extends IFastRequest implements Serializable
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
    * Account Designation member variable.
    */
   private String _AcctDesignation = "";
            
   /**
    * Account Type member variable.
    */
   private String _AccountType = "";
            
   /**
    * Tax Type member variable.
    */
   private String _TaxType = "";
            
   /**
    * Country Code member variable.
    */
   private String _CountryCode = "";
            
   /**
    * Investor Type member variable.
    */
   private String _InvestorType = "";
            
   /**
    * Invest on behalf of 3rd party member variable.
    */
   private String _InvestOnBhf3Prty = "";
            

   /**
    * Constructs the DeftRegStdInqRequest object.
    * 
    */
   DeftRegStdInqRequest()
   {
      super ( 453 );
   }

   /**
    * Constructs the DeftRegStdInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DeftRegStdInqRequest( String hostEncoding )
   {
      super ( 453, hostEncoding );
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
    * Sets the Account Designation field for the request.
    * 
    * @param value  Value that the Account Designation will be set to.
    */
   public final void setAcctDesignation( String value )
   {
      assertUnsent();
      _AcctDesignation = value;
   }
	
   /**
    * Sets the Account Type field for the request.
    * 
    * @param value  Value that the Account Type will be set to.
    */
   public final void setAccountType( String value )
   {
      assertUnsent();
      _AccountType = value;
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
    * Sets the Country Code field for the request.
    * 
    * @param value  Value that the Country Code will be set to.
    */
   public final void setCountryCode( String value )
   {
      assertUnsent();
      _CountryCode = value;
   }
	
   /**
    * Sets the Investor Type field for the request.
    * 
    * @param value  Value that the Investor Type will be set to.
    */
   public final void setInvestorType( String value )
   {
      assertUnsent();
      _InvestorType = value;
   }
	
   /**
    * Sets the Invest on behalf of 3rd party field for the request.
    * 
    * @param value  Value that the Invest on behalf of 3rd party will be set to.
    */
   public final void setInvestOnBhf3Prty( String value )
   {
      assertUnsent();
      _InvestOnBhf3Prty = value;
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
      requestBuffer.appendField( _AcctDesignation );
      requestBuffer.appendField( _AccountType );
      requestBuffer.appendField( _TaxType );
      requestBuffer.appendField( _CountryCode );
      requestBuffer.appendField( _InvestorType );
      requestBuffer.appendField( _InvestOnBhf3Prty );
   }

}

