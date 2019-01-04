// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Agent Transactions request.
 * For additional view information see <A HREF="../../../../viewspecs/AgentTransactions.doc">AgentTransactions.doc</A>.
 * 
 * @author RTS Generated
 */
public class AgentTransactionsRequest extends IFastRequest implements Serializable
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
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep member variable.
    */
   private String _SlsRep = "";
            
   /**
    * From Date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * ToDate member variable.
    */
   private Date _ToDate = null;
            
            
            
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
    * Exclude Cancelled Trades member variable.
    */
   private Boolean _ExcludeCancelled = new Boolean(false);
            
   /**
    * Exclude Reversed Trades member variable.
    */
   private Boolean _ExcludeReversals = new Boolean(false);
            
   /**
    * Reporting Currency member variable.
    */
   private String _ReportingCurrency = "";
            

   /**
    * Constructs the AgentTransactionsRequest object.
    * 
    */
   AgentTransactionsRequest()
   {
      super ( 93 );
   }

   /**
    * Constructs the AgentTransactionsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AgentTransactionsRequest( String hostEncoding )
   {
      super ( 93, hostEncoding );
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
    * Sets the Branch Code field for the request.
    * 
    * @param value  Value that the Branch Code will be set to.
    */
   public final void setBranchCode( String value )
   {
      assertUnsent();
      _BranchCode = value;
   }
	
   /**
    * Sets the Sales Rep field for the request.
    * 
    * @param value  Value that the Sales Rep will be set to.
    */
   public final void setSlsRep( String value )
   {
      assertUnsent();
      _SlsRep = value;
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
    * Sets the ToDate field for the request.
    * 
    * @param value  Value that the ToDate will be set to.
    */
   public final void setToDate( Date value )
   {
      assertUnsent();
      _ToDate = value;
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
    * Sets the Exclude Cancelled Trades field for the request.
    * 
    * @param value  Value that the Exclude Cancelled Trades will be set to.
    */
   public final void setExcludeCancelled( Boolean value )
   {
      assertUnsent();
      _ExcludeCancelled = value;
   }
	
   /**
    * Sets the Exclude Reversed Trades field for the request.
    * 
    * @param value  Value that the Exclude Reversed Trades will be set to.
    */
   public final void setExcludeReversals( Boolean value )
   {
      assertUnsent();
      _ExcludeReversals = value;
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
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SlsRep );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _ReqTransNum );
      requestBuffer.appendField( _WireOrdNum );
      requestBuffer.appendField( _NetworkID );
      requestBuffer.appendField( _ExtTransNum );
      requestBuffer.appendField( _SendRefNum );
      requestBuffer.appendField( _PartRefNum );
      requestBuffer.appendField( _MasterRefNum );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _TxnLevelSec );
      requestBuffer.appendField( _ExcludeCancelled );
      requestBuffer.appendField( _ExcludeReversals );
      requestBuffer.appendField( _ReportingCurrency );
   }

}

