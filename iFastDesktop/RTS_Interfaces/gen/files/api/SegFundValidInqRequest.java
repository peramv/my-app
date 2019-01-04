// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Seg Fund Validation Inquiry - NASU request.
 * For additional view information see <A HREF="../../../../viewspecs/SegFundValidInq.doc">SegFundValidInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class SegFundValidInqRequest extends IFastRequest implements Serializable
{

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
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * PAC Effective  Date member variable.
    */
   private Date _EffectiveDate = null;
            
            
            
   /**
    * Account Designation member variable.
    */
   private String _AcctDesignation = "";
            
   /**
    * Account Tax Type member variable.
    */
   private String _TaxType = "";
            
   /**
    * Provice of registration member variable.
    */
   private String _PensionJuris = "";
            
   /**
    * Shareholder's date of birth member variable.
    */
   private Date _DofBirth = null;
            
   /**
    * Contract Type member variable.
    */
   private String _ContractType = "";
            
   /**
    * Maturity Type member variable.
    */
   private String _MaturityType = "";
            
   /**
    * User defined Maturity Date member variable.
    */
   private Date _UserMaturDate = null;
            
   /**
    * Age base on code member variable.
    */
   private String _AgeBassedOn = "";
            

   /**
    * Constructs the SegFundValidInqRequest object.
    * 
    */
   SegFundValidInqRequest()
   {
      super ( 193 );
   }

   /**
    * Constructs the SegFundValidInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SegFundValidInqRequest( String hostEncoding )
   {
      super ( 193, hostEncoding );
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
    * Sets the Fund Code field for the request.
    * 
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class Code field for the request.
    * 
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the PAC Effective  Date field for the request.
    * 
    * @param value  Value that the PAC Effective  Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
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
    * Sets the Account Tax Type field for the request.
    * 
    * @param value  Value that the Account Tax Type will be set to.
    */
   public final void setTaxType( String value )
   {
      assertUnsent();
      _TaxType = value;
   }
	
   /**
    * Sets the Provice of registration field for the request.
    * 
    * @param value  Value that the Provice of registration will be set to.
    */
   public final void setPensionJuris( String value )
   {
      assertUnsent();
      _PensionJuris = value;
   }
	
   /**
    * Sets the Shareholder's date of birth field for the request.
    * 
    * @param value  Value that the Shareholder's date of birth will be set to.
    */
   public final void setDofBirth( Date value )
   {
      assertUnsent();
      _DofBirth = value;
   }
	
   /**
    * Sets the Contract Type field for the request.
    * 
    * @param value  Value that the Contract Type will be set to.
    */
   public final void setContractType( String value )
   {
      assertUnsent();
      _ContractType = value;
   }
	
   /**
    * Sets the Maturity Type field for the request.
    * 
    * @param value  Value that the Maturity Type will be set to.
    */
   public final void setMaturityType( String value )
   {
      assertUnsent();
      _MaturityType = value;
   }
	
   /**
    * Sets the User defined Maturity Date field for the request.
    * 
    * @param value  Value that the User defined Maturity Date will be set to.
    */
   public final void setUserMaturDate( Date value )
   {
      assertUnsent();
      _UserMaturDate = value;
   }
	
   /**
    * Sets the Age base on code field for the request.
    * 
    * @param value  Value that the Age base on code will be set to.
    */
   public final void setAgeBassedOn( String value )
   {
      assertUnsent();
      _AgeBassedOn = value;
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
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _EffectiveDate );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AcctDesignation );
      requestBuffer.appendField( _TaxType );
      requestBuffer.appendField( _PensionJuris );
      requestBuffer.appendField( _DofBirth );
      requestBuffer.appendField( _ContractType );
      requestBuffer.appendField( _MaturityType );
      requestBuffer.appendField( _UserMaturDate );
      requestBuffer.appendField( _AgeBassedOn );
   }

}

