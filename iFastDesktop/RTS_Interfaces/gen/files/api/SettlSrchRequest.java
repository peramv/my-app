// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Settlements Search request.
 * For additional view information see <A HREF="../../../../viewspecs/SettlSrch.doc">SettlSrch.doc</A>.
 * 
 * @author RTS Generated
 */
public class SettlSrchRequest extends IFastRequest implements Serializable
{

            
   /**
    * Session Id member variable.
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
    * Search Type member variable.
    */
   private String _SearchType = "";
            
   /**
    * Wire Order Number member variable.
    */
   private String _WireOrdNum = "";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _Transnum = null;
            
   /**
    * Account Number member variable.
    */
   private String _AcctNumber = "0";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Company Code member variable.
    */
   private String _CompCode = "";
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Intermediary Code member variable.
    */
   private String _InterCode = "";
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Settle Currency member variable.
    */
   private String _SettlCurr = "";
            
   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * SettleDate member variable.
    */
   private Date _SettleDate = null;
            
   /**
    * Start Date member variable.
    */
   private Date _StartDate = null;
            
   /**
    * End Date member variable.
    */
   private Date _EndDate = null;
            
            
   /**
    * Volume settlement type member variable.
    */
   private String _rxVolSettleType = "";
            
   /**
    * Class Code member variable.
    */
   private String _ReqClassCode = "";
            
   /**
    * External Id Type member variable.
    */
   private String _ExternalIdType = "";
            
   /**
    * External Id member variable.
    */
   private String _ExternalId = "";
            
   /**
    * Registration Agent Code member variable.
    */
   private String _RegAgentCode = "";
            
   /**
    * Flag ExcludeStopSettle member variable.
    */
   private Boolean _ExcludeStopSettle = new Boolean(false);
            

   /**
    * Constructs the SettlSrchRequest object.
    * 
    */
   SettlSrchRequest()
   {
      super ( 200 );
   }

   /**
    * Constructs the SettlSrchRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SettlSrchRequest( String hostEncoding )
   {
      super ( 200, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
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
    * Sets the Wire Order Number field for the request.
    * 
    * @param value  Value that the Wire Order Number will be set to.
    */
   public final void setWireOrdNum( String value )
   {
      assertUnsent();
      _WireOrdNum = value;
   }
	
   /**
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransnum( Integer value )
   {
      assertUnsent();
      _Transnum = value;
   }
	
   /**
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAcctNumber( String value )
   {
      assertUnsent();
      _AcctNumber = value;
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
    * Sets the Company Code field for the request.
    * 
    * @param value  Value that the Company Code will be set to.
    */
   public final void setCompCode( String value )
   {
      assertUnsent();
      _CompCode = value;
   }
	
   /**
    * Sets the Broker Code field for the request.
    * 
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Intermediary Code field for the request.
    * 
    * @param value  Value that the Intermediary Code will be set to.
    */
   public final void setInterCode( String value )
   {
      assertUnsent();
      _InterCode = value;
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
    * Sets the Settle Currency field for the request.
    * 
    * @param value  Value that the Settle Currency will be set to.
    */
   public final void setSettlCurr( String value )
   {
      assertUnsent();
      _SettlCurr = value;
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
    * Sets the SettleDate field for the request.
    * 
    * @param value  Value that the SettleDate will be set to.
    */
   public final void setSettleDate( Date value )
   {
      assertUnsent();
      _SettleDate = value;
   }
	
   /**
    * Sets the Start Date field for the request.
    * 
    * @param value  Value that the Start Date will be set to.
    */
   public final void setStartDate( Date value )
   {
      assertUnsent();
      _StartDate = value;
   }
	
   /**
    * Sets the End Date field for the request.
    * 
    * @param value  Value that the End Date will be set to.
    */
   public final void setEndDate( Date value )
   {
      assertUnsent();
      _EndDate = value;
   }
	
   /**
    * Sets the Volume settlement type field for the request.
    * 
    * @param value  Value that the Volume settlement type will be set to.
    */
   public final void setrxVolSettleType( String value )
   {
      assertUnsent();
      _rxVolSettleType = value;
   }
	
   /**
    * Sets the Class Code field for the request.
    * 
    * @param value  Value that the Class Code will be set to.
    */
   public final void setReqClassCode( String value )
   {
      assertUnsent();
      _ReqClassCode = value;
   }
	
   /**
    * Sets the External Id Type field for the request.
    * 
    * @param value  Value that the External Id Type will be set to.
    */
   public final void setExternalIdType( String value )
   {
      assertUnsent();
      _ExternalIdType = value;
   }
	
   /**
    * Sets the External Id field for the request.
    * 
    * @param value  Value that the External Id will be set to.
    */
   public final void setExternalId( String value )
   {
      assertUnsent();
      _ExternalId = value;
   }
	
   /**
    * Sets the Registration Agent Code field for the request.
    * 
    * @param value  Value that the Registration Agent Code will be set to.
    */
   public final void setRegAgentCode( String value )
   {
      assertUnsent();
      _RegAgentCode = value;
   }
	
   /**
    * Sets the Flag ExcludeStopSettle field for the request.
    * 
    * @param value  Value that the Flag ExcludeStopSettle will be set to.
    */
   public final void setExcludeStopSettle( Boolean value )
   {
      assertUnsent();
      _ExcludeStopSettle = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _WireOrdNum );
      requestBuffer.appendField( _Transnum );
      requestBuffer.appendField( _AcctNumber );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _CompCode );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _InterCode );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _SettlCurr );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _SettleDate );
      requestBuffer.appendField( _StartDate );
      requestBuffer.appendField( _EndDate );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _rxVolSettleType );
      requestBuffer.appendField( _ReqClassCode );
      requestBuffer.appendField( _ExternalIdType );
      requestBuffer.appendField( _ExternalId );
      requestBuffer.appendField( _RegAgentCode );
      requestBuffer.appendField( _ExcludeStopSettle );
   }

}

