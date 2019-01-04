// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Agent List Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/AgentList.doc">AgentList.doc</A>.
 * 
 * @author RTS Generated
 */
public class AgentListRequest extends IFastRequest implements Serializable
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
    * Sales Rep (blank for all under Broker/Branch) member variable.
    */
   private String _SlsRep = "";
            
   /**
    * Check User Access member variable.
    */
   private Boolean _CheckUserAccess = new Boolean(false);
            
   /**
    * Sorting of records member variable.
    */
   private String _SortBy = "";
            
            
            
            
   /**
    * Use sales rep info only ignore Broker/Branch member variable.
    */
   private Boolean _IgnoreBrokerBranch = new Boolean(false);
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Validation Type: at account screen or trade member variable.
    */
   private String _ValidationType = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Sales Rep Name member variable.
    */
   private String _SlsRepName = "";
            

   /**
    * Constructs the AgentListRequest object.
    * 
    */
   AgentListRequest()
   {
      super ( 92 );
   }

   /**
    * Constructs the AgentListRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AgentListRequest( String hostEncoding )
   {
      super ( 92, hostEncoding );
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
    * Sets the Sales Rep (blank for all under Broker/Branch) field for the request.
    * 
    * @param value  Value that the Sales Rep (blank for all under Broker/Branch) will be set to.
    */
   public final void setSlsRep( String value )
   {
      assertUnsent();
      _SlsRep = value;
   }
	
   /**
    * Sets the Check User Access field for the request.
    * 
    * @param value  Value that the Check User Access will be set to.
    */
   public final void setCheckUserAccess( Boolean value )
   {
      assertUnsent();
      _CheckUserAccess = value;
   }
	
   /**
    * Sets the Sorting of records field for the request.
    * 
    * @param value  Value that the Sorting of records will be set to.
    */
   public final void setSortBy( String value )
   {
      assertUnsent();
      _SortBy = value;
   }
	
   /**
    * Sets the Use sales rep info only ignore Broker/Branch field for the request.
    * 
    * @param value  Value that the Use sales rep info only ignore Broker/Branch will be set to.
    */
   public final void setIgnoreBrokerBranch( Boolean value )
   {
      assertUnsent();
      _IgnoreBrokerBranch = value;
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
    * Sets the Validation Type: at account screen or trade field for the request.
    * 
    * @param value  Value that the Validation Type: at account screen or trade will be set to.
    */
   public final void setValidationType( String value )
   {
      assertUnsent();
      _ValidationType = value;
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
    * Sets the Sales Rep Name field for the request.
    * 
    * @param value  Value that the Sales Rep Name will be set to.
    */
   public final void setSlsRepName( String value )
   {
      assertUnsent();
      _SlsRepName = value;
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
      requestBuffer.appendField( _CheckUserAccess );
      requestBuffer.appendField( _SortBy );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _IgnoreBrokerBranch );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _ValidationType );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _SlsRepName );
   }

}

