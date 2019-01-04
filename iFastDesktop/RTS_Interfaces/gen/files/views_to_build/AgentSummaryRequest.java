// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Agent Summary request.
 * For additional view information see <A HREF="../../../../viewspecs/AgentSummary.doc">AgentSummary.doc</A>.
 * 
 * @author RTS Generated
 */
public class AgentSummaryRequest extends IFastRequest implements Serializable
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
    * ReqFundGroup member variable.
    */
   private String _ReqFundGroup = "";
            
   /**
    * ReqFund member variable.
    */
   private String _ReqFund = "";
            
   /**
    * ReqClass member variable.
    */
   private String _ReqClass = "";
            
            
   /**
    * Calculate Pending Trades Y/N member variable.
    */
   private Boolean _CalcPendingTrades = new Boolean(false);
            
   /**
    * Filter Currency member variable.
    */
   private String _FilterCurrency = "";
            

   /**
    * Constructs the AgentSummaryRequest object.
    * 
    */
   AgentSummaryRequest()
   {
      super ( 94 );
   }

   /**
    * Constructs the AgentSummaryRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AgentSummaryRequest( String hostEncoding )
   {
      super ( 94, hostEncoding );
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
    * Sets the ReqFundGroup field for the request.
    * 
    * @param value  Value that the ReqFundGroup will be set to.
    */
   public final void setReqFundGroup( String value )
   {
      assertUnsent();
      _ReqFundGroup = value;
   }
	
   /**
    * Sets the ReqFund field for the request.
    * 
    * @param value  Value that the ReqFund will be set to.
    */
   public final void setReqFund( String value )
   {
      assertUnsent();
      _ReqFund = value;
   }
	
   /**
    * Sets the ReqClass field for the request.
    * 
    * @param value  Value that the ReqClass will be set to.
    */
   public final void setReqClass( String value )
   {
      assertUnsent();
      _ReqClass = value;
   }
	
   /**
    * Sets the Calculate Pending Trades Y/N field for the request.
    * 
    * @param value  Value that the Calculate Pending Trades Y/N will be set to.
    */
   public final void setCalcPendingTrades( Boolean value )
   {
      assertUnsent();
      _CalcPendingTrades = value;
   }
	
   /**
    * Sets the Filter Currency field for the request.
    * 
    * @param value  Value that the Filter Currency will be set to.
    */
   public final void setFilterCurrency( String value )
   {
      assertUnsent();
      _FilterCurrency = value;
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
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _ReqFundGroup );
      requestBuffer.appendField( _ReqFund );
      requestBuffer.appendField( _ReqClass );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _CalcPendingTrades );
      requestBuffer.appendField( _FilterCurrency );
   }

}

