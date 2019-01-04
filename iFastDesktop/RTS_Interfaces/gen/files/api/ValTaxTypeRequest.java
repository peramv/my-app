// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Validations for Tax Type request.
 * For additional view information see <A HREF="../../../../viewspecs/ValTaxType.doc">ValTaxType.doc</A>.
 * 
 * @author RTS Generated
 */
public class ValTaxTypeRequest extends IFastRequest implements Serializable
{

   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * User_Id member variable.
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
    * Account member variable.
    */
   private String _Account = "0";
            
   /**
    * Tax Type member variable.
    */
   private String _TaxType = "";
            
   /**
    * Tax Jurisdiction member variable.
    */
   private String _TaxJuris = "";
            
   /**
    * AsOfDate member variable.
    */
   private Date _AsOfDate = null;
            
   /**
    * Deposit Type member variable.
    */
   private Integer _DepositType = null;
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            

   /**
    * Constructs the ValTaxTypeRequest object.
    * 
    */
   ValTaxTypeRequest()
   {
      super ( 392 );
   }

   /**
    * Constructs the ValTaxTypeRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ValTaxTypeRequest( String hostEncoding )
   {
      super ( 392, hostEncoding );
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
    * Sets the User_Id field for the request.
    * 
    * @param value  Value that the User_Id will be set to.
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
    * Sets the Account field for the request.
    * 
    * @param value  Value that the Account will be set to.
    */
   public final void setAccount( String value )
   {
      assertUnsent();
      _Account = value;
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
    * Sets the Tax Jurisdiction field for the request.
    * 
    * @param value  Value that the Tax Jurisdiction will be set to.
    */
   public final void setTaxJuris( String value )
   {
      assertUnsent();
      _TaxJuris = value;
   }
	
   /**
    * Sets the AsOfDate field for the request.
    * 
    * @param value  Value that the AsOfDate will be set to.
    */
   public final void setAsOfDate( Date value )
   {
      assertUnsent();
      _AsOfDate = value;
   }
	
   /**
    * Sets the Deposit Type field for the request.
    * 
    * @param value  Value that the Deposit Type will be set to.
    */
   public final void setDepositType( Integer value )
   {
      assertUnsent();
      _DepositType = value;
   }
	
   /**
    * Sets the Shareholder Number field for the request.
    * 
    * @param value  Value that the Shareholder Number will be set to.
    */
   public final void setShrNum( String value )
   {
      assertUnsent();
      _ShrNum = value;
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
      requestBuffer.appendField( _Account );
      requestBuffer.appendField( _TaxType );
      requestBuffer.appendField( _TaxJuris );
      requestBuffer.appendField( _AsOfDate );
      requestBuffer.appendField( _DepositType );
      requestBuffer.appendField( _ShrNum );
   }

}

