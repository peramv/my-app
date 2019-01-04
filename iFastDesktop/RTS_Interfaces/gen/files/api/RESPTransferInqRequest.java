// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * RESP Transfer Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/RESPTransferInq.doc">RESPTransferInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPTransferInqRequest extends IFastRequest implements Serializable
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
    * Trade Type member variable.
    */
   private String _TradeType = "";
            
   /**
    * Used to for existing pending and processed trades member variable.
    */
   private String _TransId = "0";
            
   /**
    * Account number for trade entry member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Used to determine PlanNum and ContractID member variable.
    */
   private String _TransType = "";
            
   /**
    * Date to find YTD notional info member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Used to determine PlanNum and ContractID member variable.
    */
   private Integer _DepositType = null;
            
   /**
    * Used to determine PlanNum and ContractID member variable.
    */
   private String _RedCode = "";
            
   /**
    * Used to determine PlanNum and ContractID for TRs member variable.
    */
   private String _AccountTo = "0";
            
            

   /**
    * Constructs the RESPTransferInqRequest object.
    * 
    */
   RESPTransferInqRequest()
   {
      super ( 406 );
   }

   /**
    * Constructs the RESPTransferInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   RESPTransferInqRequest( String hostEncoding )
   {
      super ( 406, hostEncoding );
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
    * Sets the Trade Type field for the request.
    * 
    * @param value  Value that the Trade Type will be set to.
    */
   public final void setTradeType( String value )
   {
      assertUnsent();
      _TradeType = value;
   }
	
   /**
    * Sets the Used to for existing pending and processed trades field for the request.
    * 
    * @param value  Value that the Used to for existing pending and processed trades will be set to.
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
    * Sets the Used to determine PlanNum and ContractID field for the request.
    * 
    * @param value  Value that the Used to determine PlanNum and ContractID will be set to.
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
    * Sets the Used to determine PlanNum and ContractID field for the request.
    * 
    * @param value  Value that the Used to determine PlanNum and ContractID will be set to.
    */
   public final void setDepositType( Integer value )
   {
      assertUnsent();
      _DepositType = value;
   }
	
   /**
    * Sets the Used to determine PlanNum and ContractID field for the request.
    * 
    * @param value  Value that the Used to determine PlanNum and ContractID will be set to.
    */
   public final void setRedCode( String value )
   {
      assertUnsent();
      _RedCode = value;
   }
	
   /**
    * Sets the Used to determine PlanNum and ContractID for TRs field for the request.
    * 
    * @param value  Value that the Used to determine PlanNum and ContractID for TRs will be set to.
    */
   public final void setAccountTo( String value )
   {
      assertUnsent();
      _AccountTo = value;
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
      requestBuffer.appendField( _TradeType );
      requestBuffer.appendField( _TransId );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _DepositType );
      requestBuffer.appendField( _RedCode );
      requestBuffer.appendField( _AccountTo );
      encodeOverrideRepeatsField( requestBuffer );
   }

}

