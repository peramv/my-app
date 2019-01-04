// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Settlements Maintenance - main request.
 * For additional view information see <A HREF="../../../../viewspecs/SettlUpd2.doc">SettlUpd2.doc</A>.
 * 
 * @author RTS Generated
 */
public class SettlUpd2Request extends IFastRequest implements Serializable
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
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Batch Name member variable.
    */
   private String _BatchName = "";
            
   /**
    * Batch Trace member variable.
    */
   private Integer _BatchTrace = null;
            
   /**
    * Search Type member variable.
    */
   private String _SearchType = "";
            
   /**
    * Settle All Flag Y/N member variable.
    */
   private Boolean _SettleAll = new Boolean(false);
            
   /**
    * Wire Order Number member variable.
    */
   private String _WireOrdNum = "";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
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
   private String _SettleCurr = "";
            
   /**
    * Trade Date member variable.
    */
   private Date _TradeDate = null;
            
   /**
    * Settle Date member variable.
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
    * Volum Settle Type member variable.
    */
   private String _VolSettleType = "";
            
   /**
    * Settlement Method member variable.
    */
   private Integer _SettleMethod = null;
            
   /**
    * Net Settlement member variable.
    */
   private String _NetSettlement = "0";
            
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
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Transaction ID member array.
    */
   private String[] _TransId = new String[3000];
            
   /**
    * Settled flag member array.
    */
   private Boolean[] _Settled = new Boolean[3000];
            
   /**
    * Transaction Type of the Individual Trade member array.
    */
   private String[] _IndTransType = new String[3000];
            

   /**
    * Constructs the SettlUpd2Request object.
    * 
    */
   SettlUpd2Request()
   {
      super ( 208 );
   }

   /**
    * Constructs the SettlUpd2Request object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SettlUpd2Request( String hostEncoding )
   {
      super ( 208, hostEncoding );
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
    * Sets the Batch Name field for the request.
    * 
    * @param value  Value that the Batch Name will be set to.
    */
   public final void setBatchName( String value )
   {
      assertUnsent();
      _BatchName = value;
   }
	
   /**
    * Sets the Batch Trace field for the request.
    * 
    * @param value  Value that the Batch Trace will be set to.
    */
   public final void setBatchTrace( Integer value )
   {
      assertUnsent();
      _BatchTrace = value;
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
    * Sets the Settle All Flag Y/N field for the request.
    * 
    * @param value  Value that the Settle All Flag Y/N will be set to.
    */
   public final void setSettleAll( Boolean value )
   {
      assertUnsent();
      _SettleAll = value;
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
   public final void setTransNum( Integer value )
   {
      assertUnsent();
      _TransNum = value;
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
   public final void setSettleCurr( String value )
   {
      assertUnsent();
      _SettleCurr = value;
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
    * Sets the Settle Date field for the request.
    * 
    * @param value  Value that the Settle Date will be set to.
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
    * Sets the Volum Settle Type field for the request.
    * 
    * @param value  Value that the Volum Settle Type will be set to.
    */
   public final void setVolSettleType( String value )
   {
      assertUnsent();
      _VolSettleType = value;
   }
	
   /**
    * Sets the Settlement Method field for the request.
    * 
    * @param value  Value that the Settlement Method will be set to.
    */
   public final void setSettleMethod( Integer value )
   {
      assertUnsent();
      _SettleMethod = value;
   }
	
   /**
    * Sets the Net Settlement field for the request.
    * 
    * @param value  Value that the Net Settlement will be set to.
    */
   public final void setNetSettlement( String value )
   {
      assertUnsent();
      _NetSettlement = value;
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
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Transaction ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transaction ID will be set to.
    */
   public final void setTransId( int index, String value )
   {
      assertUnsent();
      _TransId[index] = value;
   }
	
   /**
    * Sets the Settled flag field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Settled flag will be set to.
    */
   public final void setSettled( int index, Boolean value )
   {
      assertUnsent();
      _Settled[index] = value;
   }
	
   /**
    * Sets the Transaction Type of the Individual Trade field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transaction Type of the Individual Trade will be set to.
    */
   public final void setIndTransType( int index, String value )
   {
      assertUnsent();
      _IndTransType[index] = value;
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
      requestBuffer.appendField( _BatchName );
      requestBuffer.appendField( _BatchTrace );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _SettleAll );
      requestBuffer.appendField( _WireOrdNum );
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _CompCode );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _InterCode );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _SettleCurr );
      requestBuffer.appendField( _TradeDate );
      requestBuffer.appendField( _SettleDate );
      requestBuffer.appendField( _StartDate );
      requestBuffer.appendField( _EndDate );
      requestBuffer.appendField( _VolSettleType );
      requestBuffer.appendField( _SettleMethod );
      requestBuffer.appendField( _NetSettlement );
      requestBuffer.appendField( _ExternalIdType );
      requestBuffer.appendField( _ExternalId );
      requestBuffer.appendField( _RegAgentCode );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _TransId[x] );
         requestBuffer.appendField( _Settled[x] );
         requestBuffer.appendField( _IndTransType[x] );
      }
   }

}

