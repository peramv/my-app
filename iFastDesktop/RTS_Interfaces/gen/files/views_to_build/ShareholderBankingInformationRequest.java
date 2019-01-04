// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shareholder/Account Banking Information request.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderBankingInformation.doc">ShareholderBankingInformation.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderBankingInformationRequest extends IFastRequest implements Serializable
{

   /**
    * ShrhlderNum member variable.
    */
   private String _ShrNum = "0";
            
            
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
    * Banking Entity member variable.
    */
   private String _BankingEntity = "";
            
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
    * FundCode member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Fund Group member variable.
    */
   private String _FundGroup = "";
            
   /**
    * Fund Sponsor member variable.
    */
   private String _FundSponsor = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Registration Agent Code member variable.
    */
   private String _RegAgentCode = "";
            

   /**
    * Constructs the ShareholderBankingInformationRequest object.
    * 
    */
   ShareholderBankingInformationRequest()
   {
      super ( 52 );
   }

   /**
    * Constructs the ShareholderBankingInformationRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShareholderBankingInformationRequest( String hostEncoding )
   {
      super ( 52, hostEncoding );
   }

   /**
    * Sets the ShrhlderNum field for the request.
    * 
    * @param value  Value that the ShrhlderNum will be set to.
    */
   public final void setShrNum( String value )
   {
      assertUnsent();
      _ShrNum = value;
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
    * Sets the Banking Entity field for the request.
    * 
    * @param value  Value that the Banking Entity will be set to.
    */
   public final void setBankingEntity( String value )
   {
      assertUnsent();
      _BankingEntity = value;
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
    * Sets the FundCode field for the request.
    * 
    * @param value  Value that the FundCode will be set to.
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
    * Sets the Fund Group field for the request.
    * 
    * @param value  Value that the Fund Group will be set to.
    */
   public final void setFundGroup( String value )
   {
      assertUnsent();
      _FundGroup = value;
   }
	
   /**
    * Sets the Fund Sponsor field for the request.
    * 
    * @param value  Value that the Fund Sponsor will be set to.
    */
   public final void setFundSponsor( String value )
   {
      assertUnsent();
      _FundSponsor = value;
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
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _ShrNum );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _BankingEntity );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SlsRep );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _FundGroup );
      requestBuffer.appendField( _FundSponsor );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _RegAgentCode );
   }

}

