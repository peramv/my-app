// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Trade Date Validation Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/TradeDateValidation.doc">TradeDateValidation.doc</A>.
 * 
 * @author RTS Generated
 */
public class TradeDateValidationRequest extends IFastRequest implements Serializable
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
    * Pay Type member variable.
    */
   private String _PayType = "";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Validation Type member variable.
    */
   private Integer _ValidationType = null;
            
   /**
    * TradeDate member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Settlement Date member variable.
    */
   private Date _SettleDate = null;
            
   /**
    * Business Date member variable.
    */
   private Date _BusDate = null;
            
   /**
    * BrokerCode member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * OrderType member variable.
    */
   private Boolean _OrderType = new Boolean(false);
            
   /**
    * Settlement Currency member variable.
    */
   private String _SettleCurrency = "";
            
   /**
    * Date deal was made member variable.
    */
   private Date _DealDate = null;
            
   /**
    * Time deal was made member variable.
    */
   private String _DealTime = "";
            
   /**
    * Fund to transfer to member variable.
    */
   private String _FundToCode = "";
            
   /**
    * Class to transfer to member variable.
    */
   private String _ClassToCode = "";
            
   /**
    * Amount to transfer member variable.
    */
   private String _Amount = "0";
            
   /**
    * Dollars or Units for Transfer Amount member variable.
    */
   private String _AmountType = "";
            
   /**
    * Link Number member variable.
    */
   private String _LinkNumber = "";
            
            
            
   /**
    * Value Date member variable.
    */
   private Date _ValueDate = null;
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * BrokerCode of the to side of tranfer/exchange member variable.
    */
   private String _BrokerToCode = "";
            
   /**
    * Settlement In Date member variable.
    */
   private Date _SettleInDate = null;
            
   /**
    * Account To member variable.
    */
   private String _AccountTo = "0";
            
   /**
    * Settle Currency From member variable.
    */
   private String _SettleCurrFrom = "";
            
   /**
    * Settle Currency To member variable.
    */
   private String _SettleCurrTo = "";
            
   /**
    * Valuation Dt member variable.
    */
   private Date _ValuationDt = null;
            
   /**
    * Network Order member variable.
    */
   private String _NetworkOrder = "";
            

   /**
    * Constructs the TradeDateValidationRequest object.
    * 
    */
   TradeDateValidationRequest()
   {
      super ( 135 );
   }

   /**
    * Constructs the TradeDateValidationRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TradeDateValidationRequest( String hostEncoding )
   {
      super ( 135, hostEncoding );
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
    * Sets the Pay Type field for the request.
    * 
    * @param value  Value that the Pay Type will be set to.
    */
   public final void setPayType( String value )
   {
      assertUnsent();
      _PayType = value;
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
    * Sets the Validation Type field for the request.
    * 
    * @param value  Value that the Validation Type will be set to.
    */
   public final void setValidationType( Integer value )
   {
      assertUnsent();
      _ValidationType = value;
   }
	
   /**
    * Sets the TradeDate field for the request.
    * 
    * @param value  Value that the TradeDate will be set to.
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
    * Sets the Business Date field for the request.
    * 
    * @param value  Value that the Business Date will be set to.
    */
   public final void setBusDate( Date value )
   {
      assertUnsent();
      _BusDate = value;
   }
	
   /**
    * Sets the BrokerCode field for the request.
    * 
    * @param value  Value that the BrokerCode will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the OrderType field for the request.
    * 
    * @param value  Value that the OrderType will be set to.
    */
   public final void setOrderType( Boolean value )
   {
      assertUnsent();
      _OrderType = value;
   }
	
   /**
    * Sets the Settlement Currency field for the request.
    * 
    * @param value  Value that the Settlement Currency will be set to.
    */
   public final void setSettleCurrency( String value )
   {
      assertUnsent();
      _SettleCurrency = value;
   }
	
   /**
    * Sets the Date deal was made field for the request.
    * 
    * @param value  Value that the Date deal was made will be set to.
    */
   public final void setDealDate( Date value )
   {
      assertUnsent();
      _DealDate = value;
   }
	
   /**
    * Sets the Time deal was made field for the request.
    * 
    * @param value  Value that the Time deal was made will be set to.
    */
   public final void setDealTime( String value )
   {
      assertUnsent();
      _DealTime = value;
   }
	
   /**
    * Sets the Fund to transfer to field for the request.
    * 
    * @param value  Value that the Fund to transfer to will be set to.
    */
   public final void setFundToCode( String value )
   {
      assertUnsent();
      _FundToCode = value;
   }
	
   /**
    * Sets the Class to transfer to field for the request.
    * 
    * @param value  Value that the Class to transfer to will be set to.
    */
   public final void setClassToCode( String value )
   {
      assertUnsent();
      _ClassToCode = value;
   }
	
   /**
    * Sets the Amount to transfer field for the request.
    * 
    * @param value  Value that the Amount to transfer will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
   }
	
   /**
    * Sets the Dollars or Units for Transfer Amount field for the request.
    * 
    * @param value  Value that the Dollars or Units for Transfer Amount will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
   }
	
   /**
    * Sets the Link Number field for the request.
    * 
    * @param value  Value that the Link Number will be set to.
    */
   public final void setLinkNumber( String value )
   {
      assertUnsent();
      _LinkNumber = value;
   }
	
   /**
    * Sets the Value Date field for the request.
    * 
    * @param value  Value that the Value Date will be set to.
    */
   public final void setValueDate( Date value )
   {
      assertUnsent();
      _ValueDate = value;
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
    * Sets the BrokerCode of the to side of tranfer/exchange field for the request.
    * 
    * @param value  Value that the BrokerCode of the to side of tranfer/exchange will be set to.
    */
   public final void setBrokerToCode( String value )
   {
      assertUnsent();
      _BrokerToCode = value;
   }
	
   /**
    * Sets the Settlement In Date field for the request.
    * 
    * @param value  Value that the Settlement In Date will be set to.
    */
   public final void setSettleInDate( Date value )
   {
      assertUnsent();
      _SettleInDate = value;
   }
	
   /**
    * Sets the Account To field for the request.
    * 
    * @param value  Value that the Account To will be set to.
    */
   public final void setAccountTo( String value )
   {
      assertUnsent();
      _AccountTo = value;
   }
	
   /**
    * Sets the Settle Currency From field for the request.
    * 
    * @param value  Value that the Settle Currency From will be set to.
    */
   public final void setSettleCurrFrom( String value )
   {
      assertUnsent();
      _SettleCurrFrom = value;
   }
	
   /**
    * Sets the Settle Currency To field for the request.
    * 
    * @param value  Value that the Settle Currency To will be set to.
    */
   public final void setSettleCurrTo( String value )
   {
      assertUnsent();
      _SettleCurrTo = value;
   }
	
   /**
    * Sets the Valuation Dt field for the request.
    * 
    * @param value  Value that the Valuation Dt will be set to.
    */
   public final void setValuationDt( Date value )
   {
      assertUnsent();
      _ValuationDt = value;
   }
	
   /**
    * Sets the Network Order field for the request.
    * 
    * @param value  Value that the Network Order will be set to.
    */
   public final void setNetworkOrder( String value )
   {
      assertUnsent();
      _NetworkOrder = value;
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
      requestBuffer.appendField( _PayType );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _ValidationType );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _SettleDate );
      requestBuffer.appendField( _BusDate );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _OrderType );
      requestBuffer.appendField( _SettleCurrency );
      requestBuffer.appendField( _DealDate );
      requestBuffer.appendField( _DealTime );
      requestBuffer.appendField( _FundToCode );
      requestBuffer.appendField( _ClassToCode );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _LinkNumber );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _ValueDate );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _BrokerToCode );
      requestBuffer.appendField( _SettleInDate );
      requestBuffer.appendField( _AccountTo );
      requestBuffer.appendField( _SettleCurrFrom );
      requestBuffer.appendField( _SettleCurrTo );
      requestBuffer.appendField( _ValuationDt );
      requestBuffer.appendField( _NetworkOrder );
   }

}

