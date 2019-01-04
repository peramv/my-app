// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Cot Legal Age Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/CotLegalAgeInquiry.doc">CotLegalAgeInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class CotLegalAgeInquiryRequest extends IFastRequest implements Serializable
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
    * ContractType member variable.
    */
   private String _ContractType = "";
            
   /**
    * TaxType member variable.
    */
   private String _TaxType = "";
            
   /**
    * ProvReg member variable.
    */
   private String _ProvReg = "";
            
   /**
    * EffectiveDate member variable.
    */
   private Date _EffectiveDate = null;
            

   /**
    * Constructs the CotLegalAgeInquiryRequest object.
    * 
    */
   CotLegalAgeInquiryRequest()
   {
      super ( 367 );
   }

   /**
    * Constructs the CotLegalAgeInquiryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   CotLegalAgeInquiryRequest( String hostEncoding )
   {
      super ( 367, hostEncoding );
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
    * Sets the ContractType field for the request.
    * 
    * @param value  Value that the ContractType will be set to.
    */
   public final void setContractType( String value )
   {
      assertUnsent();
      _ContractType = value;
   }
	
   /**
    * Sets the TaxType field for the request.
    * 
    * @param value  Value that the TaxType will be set to.
    */
   public final void setTaxType( String value )
   {
      assertUnsent();
      _TaxType = value;
   }
	
   /**
    * Sets the ProvReg field for the request.
    * 
    * @param value  Value that the ProvReg will be set to.
    */
   public final void setProvReg( String value )
   {
      assertUnsent();
      _ProvReg = value;
   }
	
   /**
    * Sets the EffectiveDate field for the request.
    * 
    * @param value  Value that the EffectiveDate will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
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
      requestBuffer.appendField( _ContractType );
      requestBuffer.appendField( _TaxType );
      requestBuffer.appendField( _ProvReg );
      requestBuffer.appendField( _EffectiveDate );
   }

}

