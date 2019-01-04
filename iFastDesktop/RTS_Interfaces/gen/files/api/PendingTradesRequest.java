// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Pending Transactions request.
 * For additional view information see <A HREF="../../../../viewspecs/PendingTrades.doc">PendingTrades.doc</A>.
 * 
 * @author RTS Generated
 */
public class PendingTradesRequest extends IFastRequest implements Serializable
{

   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
            
   /**
    * SessionID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
    */
   private String _User_Id = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyID member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Agency Code member variable.
    */
   private String _Brokercode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SalesRepCode = "";
            
            
            
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * From Date member variable.
    */
   private Date _FromDate = null;
            
   /**
    * To Date member variable.
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
   private String _ReqWireOrdNum = "";
            
   /**
    * Network ID member variable.
    */
   private String _NetworkID = "";
            
   /**
    * External Transnum member variable.
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
    * Rebook member variable.
    */
   private Boolean _Rebook = new Boolean(false);
            
   /**
    * Exclude Bad Trades member variable.
    */
   private Boolean _ExcludeBadTrades = new Boolean(false);
            
   /**
    * NSCC Control Number member variable.
    */
   private String _NSCControlNum = "";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransactionType = "";
            
   /**
    * ExcludeVerifiedTrades member variable.
    */
   private Boolean _ExcludeVerifiedTrades = new Boolean(false);
            
   /**
    * SrchUserID member variable.
    */
   private String _SrchUserID = "";
            
   /**
    * ExcludeAggrOrd member variable.
    */
   private Boolean _ExcludeAggrOrd = new Boolean(false);
            

   /**
    * Constructs the PendingTradesRequest object.
    * 
    */
   PendingTradesRequest()
   {
      super ( 53 );
   }

   /**
    * Constructs the PendingTradesRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PendingTradesRequest( String hostEncoding )
   {
      super ( 53, hostEncoding );
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
    * Sets the SessionID field for the request.
    * 
    * @param value  Value that the SessionID will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the CompanyID field for the request.
    * 
    * @param value  Value that the CompanyID will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Agency Code field for the request.
    * 
    * @param value  Value that the Agency Code will be set to.
    */
   public final void setBrokercode( String value )
   {
      assertUnsent();
      _Brokercode = value;
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
    * Sets the Sales Rep Code field for the request.
    * 
    * @param value  Value that the Sales Rep Code will be set to.
    */
   public final void setSalesRepCode( String value )
   {
      assertUnsent();
      _SalesRepCode = value;
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
   public final void setReqWireOrdNum( String value )
   {
      assertUnsent();
      _ReqWireOrdNum = value;
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
    * Sets the External Transnum field for the request.
    * 
    * @param value  Value that the External Transnum will be set to.
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
    * Sets the Rebook field for the request.
    * 
    * @param value  Value that the Rebook will be set to.
    */
   public final void setRebook( Boolean value )
   {
      assertUnsent();
      _Rebook = value;
   }
	
   /**
    * Sets the Exclude Bad Trades field for the request.
    * 
    * @param value  Value that the Exclude Bad Trades will be set to.
    */
   public final void setExcludeBadTrades( Boolean value )
   {
      assertUnsent();
      _ExcludeBadTrades = value;
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
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setTransactionType( String value )
   {
      assertUnsent();
      _TransactionType = value;
   }
	
   /**
    * Sets the ExcludeVerifiedTrades field for the request.
    * 
    * @param value  Value that the ExcludeVerifiedTrades will be set to.
    */
   public final void setExcludeVerifiedTrades( Boolean value )
   {
      assertUnsent();
      _ExcludeVerifiedTrades = value;
   }
	
   /**
    * Sets the SrchUserID field for the request.
    * 
    * @param value  Value that the SrchUserID will be set to.
    */
   public final void setSrchUserID( String value )
   {
      assertUnsent();
      _SrchUserID = value;
   }
	
   /**
    * Sets the ExcludeAggrOrd field for the request.
    * 
    * @param value  Value that the ExcludeAggrOrd will be set to.
    */
   public final void setExcludeAggrOrd( Boolean value )
   {
      assertUnsent();
      _ExcludeAggrOrd = value;
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
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _Brokercode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SalesRepCode );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _FromDate );
      requestBuffer.appendField( _ToDate );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _ReqTransNum );
      requestBuffer.appendField( _ReqWireOrdNum );
      requestBuffer.appendField( _NetworkID );
      requestBuffer.appendField( _ExtTransNum );
      requestBuffer.appendField( _SendRefNum );
      requestBuffer.appendField( _PartRefNum );
      requestBuffer.appendField( _MasterRefNum );
      requestBuffer.appendField( _TxnLevelSec );
      requestBuffer.appendField( _ExternalIdType );
      requestBuffer.appendField( _ExternalId );
      requestBuffer.appendField( _Rebook );
      requestBuffer.appendField( _ExcludeBadTrades );
      requestBuffer.appendField( _NSCControlNum );
      requestBuffer.appendField( _TransactionType );
      requestBuffer.appendField( _ExcludeVerifiedTrades );
      requestBuffer.appendField( _SrchUserID );
      requestBuffer.appendField( _ExcludeAggrOrd );
   }

}

