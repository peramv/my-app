// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * RESP Beneficiary Notional Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/RESPBenfNotlInq.doc">RESPBenfNotlInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPBenfNotlInqRequest extends IFastRequest implements Serializable
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
    * Trade type for new pending and process trade member variable.
    */
   private String _TradeType = "";
            
   /**
    * Transaction Id used to for existing pending and processed trades member variable.
    */
   private String _TransId = "0";
            
   /**
    * Account number for trade entry member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * RESP Beneficiary ID member variable.
    */
   private String _BenefId = "0";
            
   /**
    * Transaction type used to determine PlanNum and ContractID member variable.
    */
   private String _TransType = "";
            
   /**
    * Date to find YTD notional info member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Deposit type used to determine PlanNum and ContractID member variable.
    */
   private Integer _DepositType = null;
            
   /**
    * Redemption code used to determine PlanNum and ContractID member variable.
    */
   private String _RedCode = "";
            
   /**
    * Account To used to determine PlanNum and ContractID for TRs member variable.
    */
   private String _AccountTo = "0";
            
   /**
    * Transfer Percent member variable.
    */
   private String _TrfPercent = "0";
            
   /**
    * Record Level member variable.
    */
   private String _RecLvl = "";
            
   /**
    * rxIsResidualCESG member variable.
    */
   private Boolean _rxIsResidualCESG = new Boolean(false);
            

   /**
    * Constructs the RESPBenfNotlInqRequest object.
    * 
    */
   RESPBenfNotlInqRequest()
   {
      super ( 409 );
   }

   /**
    * Constructs the RESPBenfNotlInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RESPBenfNotlInqRequest( String hostEncoding )
   {
      super ( 409, hostEncoding );
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
    * Sets the Trade type for new pending and process trade field for the request.
    * 
    * @param value  Value that the Trade type for new pending and process trade will be set to.
    */
   public final void setTradeType( String value )
   {
      assertUnsent();
      _TradeType = value;
   }
	
   /**
    * Sets the Transaction Id used to for existing pending and processed trades field for the request.
    * 
    * @param value  Value that the Transaction Id used to for existing pending and processed trades will be set to.
    */
   public final void setTransId( String value )
   {
      assertUnsent();
      _TransId = value;
   }
	
   /**
    * Sets the Account number for trade entry field for the request.
    * 
    * @param value  Value that the Account number for trade entry will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the RESP Beneficiary ID field for the request.
    * 
    * @param value  Value that the RESP Beneficiary ID will be set to.
    */
   public final void setBenefId( String value )
   {
      assertUnsent();
      _BenefId = value;
   }
	
   /**
    * Sets the Transaction type used to determine PlanNum and ContractID field for the request.
    * 
    * @param value  Value that the Transaction type used to determine PlanNum and ContractID will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the Date to find YTD notional info field for the request.
    * 
    * @param value  Value that the Date to find YTD notional info will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the Deposit type used to determine PlanNum and ContractID field for the request.
    * 
    * @param value  Value that the Deposit type used to determine PlanNum and ContractID will be set to.
    */
   public final void setDepositType( Integer value )
   {
      assertUnsent();
      _DepositType = value;
   }
	
   /**
    * Sets the Redemption code used to determine PlanNum and ContractID field for the request.
    * 
    * @param value  Value that the Redemption code used to determine PlanNum and ContractID will be set to.
    */
   public final void setRedCode( String value )
   {
      assertUnsent();
      _RedCode = value;
   }
	
   /**
    * Sets the Account To used to determine PlanNum and ContractID for TRs field for the request.
    * 
    * @param value  Value that the Account To used to determine PlanNum and ContractID for TRs will be set to.
    */
   public final void setAccountTo( String value )
   {
      assertUnsent();
      _AccountTo = value;
   }
	
   /**
    * Sets the Transfer Percent field for the request.
    * 
    * @param value  Value that the Transfer Percent will be set to.
    */
   public final void setTrfPercent( String value )
   {
      assertUnsent();
      _TrfPercent = value;
   }
	
   /**
    * Sets the Record Level field for the request.
    * 
    * @param value  Value that the Record Level will be set to.
    */
   public final void setRecLvl( String value )
   {
      assertUnsent();
      _RecLvl = value;
   }
	
   /**
    * Sets the rxIsResidualCESG field for the request.
    * 
    * @param value  Value that the rxIsResidualCESG will be set to.
    */
   public final void setrxIsResidualCESG( Boolean value )
   {
      assertUnsent();
      _rxIsResidualCESG = value;
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
      requestBuffer.appendField( _TradeType );
      requestBuffer.appendField( _TransId );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _BenefId );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _DepositType );
      requestBuffer.appendField( _RedCode );
      requestBuffer.appendField( _AccountTo );
      requestBuffer.appendField( _TrfPercent );
      requestBuffer.appendField( _RecLvl );
      requestBuffer.appendField( _rxIsResidualCESG );
   }

}

