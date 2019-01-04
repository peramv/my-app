// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Request File for RESP Trading Validation Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/ResRESPTrdValInq.doc">ResRESPTrdValInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ResRESPTrdValInqRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Fund member variable.
    */
   private String _Fund = "";
            
   /**
    * Class member variable.
    */
   private String _Class = "";
            
   /**
    * Deposit Type member variable.
    */
   private Integer _DepositType = null;
            
   /**
    * Redemption Code member variable.
    */
   private String _RedCode = "";
            
   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Settlement Date member variable.
    */
   private Date _SettleDate = null;
            
   /**
    * Amount Type member variable.
    */
   private String _AmountType = "";
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Gross or Net Flag member variable.
    */
   private Boolean _GrossOrNet = new Boolean(false);
            
   /**
    * RESP Beneficiary ID member variable.
    */
   private String _RESPBenefID = "0";
            
   /**
    * Fee member variable.
    */
   private String _Fee = "0";
            
   /**
    * Flat or Percent flag member variable.
    */
   private Boolean _FlatPercent = new Boolean(false);
            
   /**
    * Year the overcontribution withdrawal to be applied member variable.
    */
   private Integer _OCRedYear = null;
            
   /**
    * Tax Year member variable.
    */
   private Integer _TaxYear = null;
            
   /**
    * Assisted Contribution Amount member variable.
    */
   private String _AssistedContrAmt = "0";
            

   /**
    * Constructs the ResRESPTrdValInqRequest object.
    * 
    */
   ResRESPTrdValInqRequest()
   {
      super ( 405 );
   }

   /**
    * Constructs the ResRESPTrdValInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ResRESPTrdValInqRequest( String hostEncoding )
   {
      super ( 405, hostEncoding );
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
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFund( String value )
   {
      assertUnsent();
      _Fund = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClass( String value )
   {
      assertUnsent();
      _Class = value;
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
    * Sets the Redemption Code field for the request.
    * 
    * @param value  Value that the Redemption Code will be set to.
    */
   public final void setRedCode( String value )
   {
      assertUnsent();
      _RedCode = value;
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
    * Sets the Settlement Date field for the request.
    * 
    * @param value  Value that the Settlement Date will be set to.
    */
   public final void setSettleDate( Date value )
   {
      assertUnsent();
      _SettleDate = value;
   }
	
   /**
    * Sets the Amount Type field for the request.
    * 
    * @param value  Value that the Amount Type will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
   }
	
   /**
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
   }
	
   /**
    * Sets the Gross or Net Flag field for the request.
    * 
    * @param value  Value that the Gross or Net Flag will be set to.
    */
   public final void setGrossOrNet( Boolean value )
   {
      assertUnsent();
      _GrossOrNet = value;
   }
	
   /**
    * Sets the RESP Beneficiary ID field for the request.
    * 
    * @param value  Value that the RESP Beneficiary ID will be set to.
    */
   public final void setRESPBenefID( String value )
   {
      assertUnsent();
      _RESPBenefID = value;
   }
	
   /**
    * Sets the Fee field for the request.
    * 
    * @param value  Value that the Fee will be set to.
    */
   public final void setFee( String value )
   {
      assertUnsent();
      _Fee = value;
   }
	
   /**
    * Sets the Flat or Percent flag field for the request.
    * 
    * @param value  Value that the Flat or Percent flag will be set to.
    */
   public final void setFlatPercent( Boolean value )
   {
      assertUnsent();
      _FlatPercent = value;
   }
	
   /**
    * Sets the Year the overcontribution withdrawal to be applied field for the request.
    * 
    * @param value  Value that the Year the overcontribution withdrawal to be applied will be set to.
    */
   public final void setOCRedYear( Integer value )
   {
      assertUnsent();
      _OCRedYear = value;
   }
	
   /**
    * Sets the Tax Year field for the request.
    * 
    * @param value  Value that the Tax Year will be set to.
    */
   public final void setTaxYear( Integer value )
   {
      assertUnsent();
      _TaxYear = value;
   }
	
   /**
    * Sets the Assisted Contribution Amount field for the request.
    * 
    * @param value  Value that the Assisted Contribution Amount will be set to.
    */
   public final void setAssistedContrAmt( String value )
   {
      assertUnsent();
      _AssistedContrAmt = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _Fund );
      requestBuffer.appendField( _Class );
      requestBuffer.appendField( _DepositType );
      requestBuffer.appendField( _RedCode );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _SettleDate );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _GrossOrNet );
      requestBuffer.appendField( _RESPBenefID );
      requestBuffer.appendField( _Fee );
      requestBuffer.appendField( _FlatPercent );
      requestBuffer.appendField( _OCRedYear );
      requestBuffer.appendField( _TaxYear );
      requestBuffer.appendField( _AssistedContrAmt );
   }

}

