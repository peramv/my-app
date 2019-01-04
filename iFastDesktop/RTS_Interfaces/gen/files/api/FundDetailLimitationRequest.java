// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund Detail Limitation request.
 * For additional view information see <A HREF="../../../../viewspecs/FundDetailLimitation.doc">FundDetailLimitation.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundDetailLimitationRequest extends IFastRequest implements Serializable
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
    * Effective Date for newly created RRIF/LIF/LRIF record member variable.
    */
   private Date _AllocEffectiveDate = null;
            
            
            
            
   /**
    * Search Type member variable.
    */
   private String _SearchType = "";
            
   /**
    * WKN member variable.
    */
   private String _WKN = "";
            
   /**
    * ISIN member variable.
    */
   private String _ISIN = "";
            
   /**
    * Fund Number/ Baycom member variable.
    */
   private String _FNUM = "";
            
   /**
    * Fund English Name member variable.
    */
   private String _FNAM = "";
            
   /**
    * Fund Code member variable.
    */
   private String _reqFundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _reqClassCode = "";
            

   /**
    * Constructs the FundDetailLimitationRequest object.
    * 
    */
   FundDetailLimitationRequest()
   {
      super ( 56 );
   }

   /**
    * Constructs the FundDetailLimitationRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundDetailLimitationRequest( String hostEncoding )
   {
      super ( 56, hostEncoding );
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
    * Sets the Effective Date for newly created RRIF/LIF/LRIF record field for the request.
    * 
    * @param value  Value that the Effective Date for newly created RRIF/LIF/LRIF record will be set to.
    */
   public final void setAllocEffectiveDate( Date value )
   {
      assertUnsent();
      _AllocEffectiveDate = value;
   }
	
   /**
    * Sets the Search Type field for the request.
    * 
    * @param value  Value that the Search Type will be set to.
    */
   public final void setSearchType( String value )
   {
      assertUnsent();
      _SearchType = value;
   }
	
   /**
    * Sets the WKN field for the request.
    * 
    * @param value  Value that the WKN will be set to.
    */
   public final void setWKN( String value )
   {
      assertUnsent();
      _WKN = value;
   }
	
   /**
    * Sets the ISIN field for the request.
    * 
    * @param value  Value that the ISIN will be set to.
    */
   public final void setISIN( String value )
   {
      assertUnsent();
      _ISIN = value;
   }
	
   /**
    * Sets the Fund Number/ Baycom field for the request.
    * 
    * @param value  Value that the Fund Number/ Baycom will be set to.
    */
   public final void setFNUM( String value )
   {
      assertUnsent();
      _FNUM = value;
   }
	
   /**
    * Sets the Fund English Name field for the request.
    * 
    * @param value  Value that the Fund English Name will be set to.
    */
   public final void setFNAM( String value )
   {
      assertUnsent();
      _FNAM = value;
   }
	
   /**
    * Sets the Fund Code field for the request.
    * 
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setreqFundCode( String value )
   {
      assertUnsent();
      _reqFundCode = value;
   }
	
   /**
    * Sets the Class Code field for the request.
    * 
    * @param value  Value that the Class Code will be set to.
    */
   public final void setreqClassCode( String value )
   {
      assertUnsent();
      _reqClassCode = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _AllocEffectiveDate );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _WKN );
      requestBuffer.appendField( _ISIN );
      requestBuffer.appendField( _FNUM );
      requestBuffer.appendField( _FNAM );
      requestBuffer.appendField( _reqFundCode );
      requestBuffer.appendField( _reqClassCode );
   }

}

