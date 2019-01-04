// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * AFB Order Recieved Header Update request.
 * For additional view information see <A HREF="../../../../viewspecs/AFBHeaderUpd.doc">AFBHeaderUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AFBHeaderUpdRequest extends IFastRequest implements Serializable
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
    * Order File Name member variable.
    */
   private String _OrderFileName = "";
            
   /**
    * RegTypeHdr member variable.
    */
   private String _RegTypeHdr = "";
            
   /**
    * RegTypeTrl member variable.
    */
   private String _RegTypeTrl = "";
            
   /**
    * Version member variable.
    */
   private Integer _Version = null;
            
   /**
    * Agent Company Code member variable.
    */
   private String _AgentCoCode = "";
            
   /**
    * Agent Company Description member variable.
    */
   private String _AgentCo = "";
            
   /**
    * Agent Broker member variable.
    */
   private String _AgBroker = "";
            
   /**
    * Agent Company for Contact member variable.
    */
   private String _AgCoForContact = "";
            
   /**
    * Agent Company From Contract member variable.
    */
   private String _AgCoFromContarct = "";
            
   /**
    * Agent Company Fax Number1 member variable.
    */
   private String _AgCoFaxNumber1 = "";
            
   /**
    * Agent Company Fax Number2 member variable.
    */
   private String _AgCoFaxNumber2 = "";
            
   /**
    * Agent Company Phone Number1 member variable.
    */
   private String _AgCoPhoneNumber1 = "";
            
   /**
    * Agent Company Phone Number2 member variable.
    */
   private String _AgCoPhoneNumber2 = "";
            
   /**
    * Trade Date member variable.
    */
   private String _Tradedate = "";
            
   /**
    * Session Number member variable.
    */
   private Integer _SessionNo = null;
            
   /**
    * Registry Number member variable.
    */
   private Integer _RegNum = null;
            
   /**
    * Total Charge member variable.
    */
   private String _TotalCharge = "0";
            
   /**
    * Total Shares member variable.
    */
   private String _TotalShares = "0";
            
   /**
    * NetworkID member variable.
    */
   private String _NetworkID = "";
            
   /**
    * File Status member variable.
    */
   private String _FileStatus = "";
            
   /**
    * File Create Date member variable.
    */
   private String _FileCreatedate = "";
            
   /**
    * File Time member variable.
    */
   private String _FileTime = "";
            
   /**
    * Fax Number1 member variable.
    */
   private String _FaxNumber1 = "";
            
   /**
    * Fax Number2 member variable.
    */
   private String _FaxNumber2 = "";
            
   /**
    * For Contact member variable.
    */
   private String _ForContact = "";
            
   /**
    * From Contact member variable.
    */
   private String _FromContact = "";
            
   /**
    * PhoneNumber1 member variable.
    */
   private String _PhoneNumber1 = "";
            
   /**
    * PhoneNumber2 member variable.
    */
   private String _PhoneNumber2 = "";
            
   /**
    * Confirmation File name member variable.
    */
   private String _ConfFileName = "";
            

   /**
    * Constructs the AFBHeaderUpdRequest object.
    * 
    */
   AFBHeaderUpdRequest()
   {
      super ( 277 );
   }

   /**
    * Constructs the AFBHeaderUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AFBHeaderUpdRequest( String hostEncoding )
   {
      super ( 277, hostEncoding );
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
    * Sets the Order File Name field for the request.
    * 
    * @param value  Value that the Order File Name will be set to.
    */
   public final void setOrderFileName( String value )
   {
      assertUnsent();
      _OrderFileName = value;
   }
	
   /**
    * Sets the RegTypeHdr field for the request.
    * 
    * @param value  Value that the RegTypeHdr will be set to.
    */
   public final void setRegTypeHdr( String value )
   {
      assertUnsent();
      _RegTypeHdr = value;
   }
	
   /**
    * Sets the RegTypeTrl field for the request.
    * 
    * @param value  Value that the RegTypeTrl will be set to.
    */
   public final void setRegTypeTrl( String value )
   {
      assertUnsent();
      _RegTypeTrl = value;
   }
	
   /**
    * Sets the Version field for the request.
    * 
    * @param value  Value that the Version will be set to.
    */
   public final void setVersion( Integer value )
   {
      assertUnsent();
      _Version = value;
   }
	
   /**
    * Sets the Agent Company Code field for the request.
    * 
    * @param value  Value that the Agent Company Code will be set to.
    */
   public final void setAgentCoCode( String value )
   {
      assertUnsent();
      _AgentCoCode = value;
   }
	
   /**
    * Sets the Agent Company Description field for the request.
    * 
    * @param value  Value that the Agent Company Description will be set to.
    */
   public final void setAgentCo( String value )
   {
      assertUnsent();
      _AgentCo = value;
   }
	
   /**
    * Sets the Agent Broker field for the request.
    * 
    * @param value  Value that the Agent Broker will be set to.
    */
   public final void setAgBroker( String value )
   {
      assertUnsent();
      _AgBroker = value;
   }
	
   /**
    * Sets the Agent Company for Contact field for the request.
    * 
    * @param value  Value that the Agent Company for Contact will be set to.
    */
   public final void setAgCoForContact( String value )
   {
      assertUnsent();
      _AgCoForContact = value;
   }
	
   /**
    * Sets the Agent Company From Contract field for the request.
    * 
    * @param value  Value that the Agent Company From Contract will be set to.
    */
   public final void setAgCoFromContarct( String value )
   {
      assertUnsent();
      _AgCoFromContarct = value;
   }
	
   /**
    * Sets the Agent Company Fax Number1 field for the request.
    * 
    * @param value  Value that the Agent Company Fax Number1 will be set to.
    */
   public final void setAgCoFaxNumber1( String value )
   {
      assertUnsent();
      _AgCoFaxNumber1 = value;
   }
	
   /**
    * Sets the Agent Company Fax Number2 field for the request.
    * 
    * @param value  Value that the Agent Company Fax Number2 will be set to.
    */
   public final void setAgCoFaxNumber2( String value )
   {
      assertUnsent();
      _AgCoFaxNumber2 = value;
   }
	
   /**
    * Sets the Agent Company Phone Number1 field for the request.
    * 
    * @param value  Value that the Agent Company Phone Number1 will be set to.
    */
   public final void setAgCoPhoneNumber1( String value )
   {
      assertUnsent();
      _AgCoPhoneNumber1 = value;
   }
	
   /**
    * Sets the Agent Company Phone Number2 field for the request.
    * 
    * @param value  Value that the Agent Company Phone Number2 will be set to.
    */
   public final void setAgCoPhoneNumber2( String value )
   {
      assertUnsent();
      _AgCoPhoneNumber2 = value;
   }
	
   /**
    * Sets the Trade Date field for the request.
    * 
    * @param value  Value that the Trade Date will be set to.
    */
   public final void setTradedate( String value )
   {
      assertUnsent();
      _Tradedate = value;
   }
	
   /**
    * Sets the Session Number field for the request.
    * 
    * @param value  Value that the Session Number will be set to.
    */
   public final void setSessionNo( Integer value )
   {
      assertUnsent();
      _SessionNo = value;
   }
	
   /**
    * Sets the Registry Number field for the request.
    * 
    * @param value  Value that the Registry Number will be set to.
    */
   public final void setRegNum( Integer value )
   {
      assertUnsent();
      _RegNum = value;
   }
	
   /**
    * Sets the Total Charge field for the request.
    * 
    * @param value  Value that the Total Charge will be set to.
    */
   public final void setTotalCharge( String value )
   {
      assertUnsent();
      _TotalCharge = value;
   }
	
   /**
    * Sets the Total Shares field for the request.
    * 
    * @param value  Value that the Total Shares will be set to.
    */
   public final void setTotalShares( String value )
   {
      assertUnsent();
      _TotalShares = value;
   }
	
   /**
    * Sets the NetworkID field for the request.
    * 
    * @param value  Value that the NetworkID will be set to.
    */
   public final void setNetworkID( String value )
   {
      assertUnsent();
      _NetworkID = value;
   }
	
   /**
    * Sets the File Status field for the request.
    * 
    * @param value  Value that the File Status will be set to.
    */
   public final void setFileStatus( String value )
   {
      assertUnsent();
      _FileStatus = value;
   }
	
   /**
    * Sets the File Create Date field for the request.
    * 
    * @param value  Value that the File Create Date will be set to.
    */
   public final void setFileCreatedate( String value )
   {
      assertUnsent();
      _FileCreatedate = value;
   }
	
   /**
    * Sets the File Time field for the request.
    * 
    * @param value  Value that the File Time will be set to.
    */
   public final void setFileTime( String value )
   {
      assertUnsent();
      _FileTime = value;
   }
	
   /**
    * Sets the Fax Number1 field for the request.
    * 
    * @param value  Value that the Fax Number1 will be set to.
    */
   public final void setFaxNumber1( String value )
   {
      assertUnsent();
      _FaxNumber1 = value;
   }
	
   /**
    * Sets the Fax Number2 field for the request.
    * 
    * @param value  Value that the Fax Number2 will be set to.
    */
   public final void setFaxNumber2( String value )
   {
      assertUnsent();
      _FaxNumber2 = value;
   }
	
   /**
    * Sets the For Contact field for the request.
    * 
    * @param value  Value that the For Contact will be set to.
    */
   public final void setForContact( String value )
   {
      assertUnsent();
      _ForContact = value;
   }
	
   /**
    * Sets the From Contact field for the request.
    * 
    * @param value  Value that the From Contact will be set to.
    */
   public final void setFromContact( String value )
   {
      assertUnsent();
      _FromContact = value;
   }
	
   /**
    * Sets the PhoneNumber1 field for the request.
    * 
    * @param value  Value that the PhoneNumber1 will be set to.
    */
   public final void setPhoneNumber1( String value )
   {
      assertUnsent();
      _PhoneNumber1 = value;
   }
	
   /**
    * Sets the PhoneNumber2 field for the request.
    * 
    * @param value  Value that the PhoneNumber2 will be set to.
    */
   public final void setPhoneNumber2( String value )
   {
      assertUnsent();
      _PhoneNumber2 = value;
   }
	
   /**
    * Sets the Confirmation File name field for the request.
    * 
    * @param value  Value that the Confirmation File name will be set to.
    */
   public final void setConfFileName( String value )
   {
      assertUnsent();
      _ConfFileName = value;
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
      requestBuffer.appendField( _OrderFileName );
      requestBuffer.appendField( _RegTypeHdr );
      requestBuffer.appendField( _RegTypeTrl );
      requestBuffer.appendField( _Version );
      requestBuffer.appendField( _AgentCoCode );
      requestBuffer.appendField( _AgentCo );
      requestBuffer.appendField( _AgBroker );
      requestBuffer.appendField( _AgCoForContact );
      requestBuffer.appendField( _AgCoFromContarct );
      requestBuffer.appendField( _AgCoFaxNumber1 );
      requestBuffer.appendField( _AgCoFaxNumber2 );
      requestBuffer.appendField( _AgCoPhoneNumber1 );
      requestBuffer.appendField( _AgCoPhoneNumber2 );
      requestBuffer.appendField( _Tradedate );
      requestBuffer.appendField( _SessionNo );
      requestBuffer.appendField( _RegNum );
      requestBuffer.appendField( _TotalCharge );
      requestBuffer.appendField( _TotalShares );
      requestBuffer.appendField( _NetworkID );
      requestBuffer.appendField( _FileStatus );
      requestBuffer.appendField( _FileCreatedate );
      requestBuffer.appendField( _FileTime );
      requestBuffer.appendField( _FaxNumber1 );
      requestBuffer.appendField( _FaxNumber2 );
      requestBuffer.appendField( _ForContact );
      requestBuffer.appendField( _FromContact );
      requestBuffer.appendField( _PhoneNumber1 );
      requestBuffer.appendField( _PhoneNumber2 );
      requestBuffer.appendField( _ConfFileName );
   }

}

