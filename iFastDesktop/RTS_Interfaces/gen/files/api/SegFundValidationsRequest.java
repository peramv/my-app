// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Seg Fund Validations request.
 * For additional view information see <A HREF="../../../../viewspecs/SegFundValidations.doc">SegFundValidations.doc</A>.
 * 
 * @author RTS Generated
 */
public class SegFundValidationsRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
   /**
    * Account Num member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Validation Type member variable.
    */
   private String _ValidationType = "";
            
   /**
    * Trans Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Trans ID member variable.
    */
   private String _TransID = "0";
            
   /**
    * Account To Num member variable.
    */
   private String _AccountToNum = "0";
            
   /**
    * Fund To Code member variable.
    */
   private String _FundToCode = "";
            
   /**
    * Class To Code member variable.
    */
   private String _ClassToCode = "";
            

   /**
    * Constructs the SegFundValidationsRequest object.
    * 
    */
   SegFundValidationsRequest()
   {
      super ( 436 );
   }

   /**
    * Constructs the SegFundValidationsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SegFundValidationsRequest( String hostEncoding )
   {
      super ( 436, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Account Num field for the request.
    * 
    * @param value  Value that the Account Num will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
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
    * Sets the Trade Date field for the request.
    * 
    * @param value  Value that the Trade Date will be set to.
    */
   public final void setTradeDate( Date value )
   {
      assertUnsent();
      _TradeDate = value;
   }
	
   /**
    * Sets the Validation Type field for the request.
    * 
    * @param value  Value that the Validation Type will be set to.
    */
   public final void setValidationType( String value )
   {
      assertUnsent();
      _ValidationType = value;
   }
	
   /**
    * Sets the Trans Type field for the request.
    * 
    * @param value  Value that the Trans Type will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the Trans ID field for the request.
    * 
    * @param value  Value that the Trans ID will be set to.
    */
   public final void setTransID( String value )
   {
      assertUnsent();
      _TransID = value;
   }
	
   /**
    * Sets the Account To Num field for the request.
    * 
    * @param value  Value that the Account To Num will be set to.
    */
   public final void setAccountToNum( String value )
   {
      assertUnsent();
      _AccountToNum = value;
   }
	
   /**
    * Sets the Fund To Code field for the request.
    * 
    * @param value  Value that the Fund To Code will be set to.
    */
   public final void setFundToCode( String value )
   {
      assertUnsent();
      _FundToCode = value;
   }
	
   /**
    * Sets the Class To Code field for the request.
    * 
    * @param value  Value that the Class To Code will be set to.
    */
   public final void setClassToCode( String value )
   {
      assertUnsent();
      _ClassToCode = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _ValidationType );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _TransID );
      requestBuffer.appendField( _AccountToNum );
      requestBuffer.appendField( _FundToCode );
      requestBuffer.appendField( _ClassToCode );
   }

}

