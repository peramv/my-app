// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account/fund transaction history request.
 * For additional view information see <A HREF="../../../../viewspecs/AccountTransactionHistory.doc">AccountTransactionHistory.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountTransactionHistoryRequest extends IFastRequest implements Serializable
{

   /**
    * Account number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Fund code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class of fund member variable.
    */
   private String _ClassCode = "";
            
   /**
    * All Fund Mode member variable.
    */
   private Boolean _AllFundMode = new Boolean(false);
            
            
   /**
    * SessionId member variable.
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
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
   /**
    * From Date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * To Date member variable.
    */
   private Date _ToDate = null;
            
   /**
    * Use Date Flag member variable.
    */
   private Boolean _UseDateFlag = new Boolean(false);
            
            
            
            
   /**
    * transaction Id member variable.
    */
   private String _ReqTransid = "0";
            
   /**
    * Search Type member variable.
    */
   private String _SearchType = "";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _ReqTransNum = null;
            
   /**
    * Wire Order Number member variable.
    */
   private String _WireOrdNum = "";
            
   /**
    * Network ID member variable.
    */
   private String _NetworkID = "";
            
   /**
    * External Transnumber member variable.
    */
   private String _ExtTransNum = "";
            
   /**
    * Sender's Reference Number member variable.
    */
   private String _SendRefNum = "";
            
   /**
    * Participant's Reference Number member variable.
    */
   private String _PartRefNum = "";
            
   /**
    * Master Reference Number member variable.
    */
   private String _MasterRefNum = "";
            
   /**
    * Transaction Level Security member variable.
    */
   private Boolean _TxnLevelSec = new Boolean(false);
            
   /**
    * External Id Type member variable.
    */
   private String _ExternalIdType = "";
            
   /**
    * External Id member variable.
    */
   private String _ExternalId = "";
            
   /**
    * Alternate Account member variable.
    */
   private String _AltAccount = "";
            
   /**
    * Transaction Type member variable.
    */
   private String _rxTransType = "";
            
   /**
    * Units member variable.
    */
   private String _rxUnits = "0";
            
   /**
    * FundIDValue member variable.
    */
   private String _FundIdValue = "";
            
   /**
    * FundIDType member variable.
    */
   private String _FundIdType = "";
            
   /**
    * Status of Trade member variable.
    */
   private String _TradeStatus = "";
            
   /**
    * EUSD Scope member variable.
    */
   private String _EUSDScope = "";
            
   /**
    * Exclude Reversal member variable.
    */
   private Boolean _ExcludeReversal = new Boolean(false);
            
   /**
    * Trade Date member variable.
    */
   private Date _rxTradeDate = null;
            
   /**
    * Exclude Cancelled member variable.
    */
   private Boolean _ExcludeCancelled = new Boolean(false);
            
   /**
    * Reporting Currency member variable.
    */
   private String _ReportingCurrency = "";
            
   /**
    * NSCC Control Number member variable.
    */
   private String _NSCControlNum = "";
            

   /**
    * Constructs the AccountTransactionHistoryRequest object.
    * 
    */
   AccountTransactionHistoryRequest()
   {
      super ( 17 );
   }

   /**
    * Constructs the AccountTransactionHistoryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AccountTransactionHistoryRequest( String hostEncoding )
   {
      super ( 17, hostEncoding );
   }

   /**
    * Sets the Account number field for the request.
    * 
    * @param value  Value that the Account number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
   }
	
   /**
    * Sets the Fund code field for the request.
    * 
    * @param value  Value that the Fund code will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the Class of fund field for the request.
    * 
    * @param value  Value that the Class of fund will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the All Fund Mode field for the request.
    * 
    * @param value  Value that the All Fund Mode will be set to.
    */
   public final void setAllFundMode( Boolean value )
   {
      assertUnsent();
      _AllFundMode = value;
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
    * Sets the From Date field for the request.
    * 
    * @param value  Value that the From Date will be set to.
    */
   public final void setFromDate( Date value )
   {
      assertUnsent();
      _FromDate = value;
   }
	
   /**
    * Sets the To Date field for the request.
    * 
    * @param value  Value that the To Date will be set to.
    */
   public final void setToDate( Date value )
   {
      assertUnsent();
      _ToDate = value;
   }
	
   /**
    * Sets the Use Date Flag field for the request.
    * 
    * @param value  Value that the Use Date Flag will be set to.
    */
   public final void setUseDateFlag( Boolean value )
   {
      assertUnsent();
      _UseDateFlag = value;
   }
	
   /**
    * Sets the transaction Id field for the request.
    * 
    * @param value  Value that the transaction Id will be set to.
    */
   public final void setReqTransid( String value )
   {
      assertUnsent();
      _ReqTransid = value;
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
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setReqTransNum( Integer value )
   {
      assertUnsent();
      _ReqTransNum = value;
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
    * Sets the Network ID field for the request.
    * 
    * @param value  Value that the Network ID will be set to.
    */
   public final void setNetworkID( String value )
   {
      assertUnsent();
      _NetworkID = value;
   }
	
   /**
    * Sets the External Transnumber field for the request.
    * 
    * @param value  Value that the External Transnumber will be set to.
    */
   public final void setExtTransNum( String value )
   {
      assertUnsent();
      _ExtTransNum = value;
   }
	
   /**
    * Sets the Sender's Reference Number field for the request.
    * 
    * @param value  Value that the Sender's Reference Number will be set to.
    */
   public final void setSendRefNum( String value )
   {
      assertUnsent();
      _SendRefNum = value;
   }
	
   /**
    * Sets the Participant's Reference Number field for the request.
    * 
    * @param value  Value that the Participant's Reference Number will be set to.
    */
   public final void setPartRefNum( String value )
   {
      assertUnsent();
      _PartRefNum = value;
   }
	
   /**
    * Sets the Master Reference Number field for the request.
    * 
    * @param value  Value that the Master Reference Number will be set to.
    */
   public final void setMasterRefNum( String value )
   {
      assertUnsent();
      _MasterRefNum = value;
   }
	
   /**
    * Sets the Transaction Level Security field for the request.
    * 
    * @param value  Value that the Transaction Level Security will be set to.
    */
   public final void setTxnLevelSec( Boolean value )
   {
      assertUnsent();
      _TxnLevelSec = value;
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
    * Sets the Alternate Account field for the request.
    * 
    * @param value  Value that the Alternate Account will be set to.
    */
   public final void setAltAccount( String value )
   {
      assertUnsent();
      _AltAccount = value;
   }
	
   /**
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setrxTransType( String value )
   {
      assertUnsent();
      _rxTransType = value;
   }
	
   /**
    * Sets the Units field for the request.
    * 
    * @param value  Value that the Units will be set to.
    */
   public final void setrxUnits( String value )
   {
      assertUnsent();
      _rxUnits = value;
   }
	
   /**
    * Sets the FundIDValue field for the request.
    * 
    * @param value  Value that the FundIDValue will be set to.
    */
   public final void setFundIdValue( String value )
   {
      assertUnsent();
      _FundIdValue = value;
   }
	
   /**
    * Sets the FundIDType field for the request.
    * 
    * @param value  Value that the FundIDType will be set to.
    */
   public final void setFundIdType( String value )
   {
      assertUnsent();
      _FundIdType = value;
   }
	
   /**
    * Sets the Status of Trade field for the request.
    * 
    * @param value  Value that the Status of Trade will be set to.
    */
   public final void setTradeStatus( String value )
   {
      assertUnsent();
      _TradeStatus = value;
   }
	
   /**
    * Sets the EUSD Scope field for the request.
    * 
    * @param value  Value that the EUSD Scope will be set to.
    */
   public final void setEUSDScope( String value )
   {
      assertUnsent();
      _EUSDScope = value;
   }
	
   /**
    * Sets the Exclude Reversal field for the request.
    * 
    * @param value  Value that the Exclude Reversal will be set to.
    */
   public final void setExcludeReversal( Boolean value )
   {
      assertUnsent();
      _ExcludeReversal = value;
   }
	
   /**
    * Sets the Trade Date field for the request.
    * 
    * @param value  Value that the Trade Date will be set to.
    */
   public final void setrxTradeDate( Date value )
   {
      assertUnsent();
      _rxTradeDate = value;
   }
	
   /**
    * Sets the Exclude Cancelled field for the request.
    * 
    * @param value  Value that the Exclude Cancelled will be set to.
    */
   public final void setExcludeCancelled( Boolean value )
   {
      assertUnsent();
      _ExcludeCancelled = value;
   }
	
   /**
    * Sets the Reporting Currency field for the request.
    * 
    * @param value  Value that the Reporting Currency will be set to.
    */
   public final void setReportingCurrency( String value )
   {
      assertUnsent();
      _ReportingCurrency = value;
   }
	
   /**
    * Sets the NSCC Control Number field for the request.
    * 
    * @param value  Value that the NSCC Control Number will be set to.
    */
   public final void setNSCControlNum( String value )
   {
      assertUnsent();
      _NSCControlNum = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _AllFundMode );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
      requestBuffer.appendField( _UseDateFlag );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _ReqTransid );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _ReqTransNum );
      requestBuffer.appendField( _WireOrdNum );
      requestBuffer.appendField( _NetworkID );
      requestBuffer.appendField( _ExtTransNum );
      requestBuffer.appendField( _SendRefNum );
      requestBuffer.appendField( _PartRefNum );
      requestBuffer.appendField( _MasterRefNum );
      requestBuffer.appendField( _TxnLevelSec );
      requestBuffer.appendField( _ExternalIdType );
      requestBuffer.appendField( _ExternalId );
      requestBuffer.appendField( _AltAccount );
      requestBuffer.appendField( _rxTransType );
      requestBuffer.appendField( _rxUnits );
      requestBuffer.appendField( _FundIdValue );
      requestBuffer.appendField( _FundIdType );
      requestBuffer.appendField( _TradeStatus );
      requestBuffer.appendField( _EUSDScope );
      requestBuffer.appendField( _ExcludeReversal );
      requestBuffer.appendField( _rxTradeDate );
      requestBuffer.appendField( _ExcludeCancelled );
      requestBuffer.appendField( _ReportingCurrency );
      requestBuffer.appendField( _NSCControlNum );
   }

}

