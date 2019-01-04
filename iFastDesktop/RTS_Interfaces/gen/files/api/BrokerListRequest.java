// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Broker List Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/BrokerList.doc">BrokerList.doc</A>.
 * 
 * @author RTS Generated
 */
public class BrokerListRequest extends IFastRequest implements Serializable
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
    * Broker Code (blank for all) member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Broker Name member variable.
    */
   private String _SrchBrokerName = "";
            
   /**
    * Request Type member variable.
    */
   private String _RequestType = "";
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
            
            
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Validation Type member variable.
    */
   private String _ValidationType = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * ClearingFirmBroker member variable.
    */
   private String _ClearingFirmBroker = "";
            
   /**
    * Relation Type member variable.
    */
   private String _RelationType = "";
            

   /**
    * Constructs the BrokerListRequest object.
    * 
    */
   BrokerListRequest()
   {
      super ( 90 );
   }

   /**
    * Constructs the BrokerListRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   BrokerListRequest( String hostEncoding )
   {
      super ( 90, hostEncoding );
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
    * Sets the Broker Code (blank for all) field for the request.
    * 
    * @param value  Value that the Broker Code (blank for all) will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Broker Name field for the request.
    * 
    * @param value  Value that the Broker Name will be set to.
    */
   public final void setSrchBrokerName( String value )
   {
      assertUnsent();
      _SrchBrokerName = value;
   }
	
   /**
    * Sets the Request Type field for the request.
    * 
    * @param value  Value that the Request Type will be set to.
    */
   public final void setRequestType( String value )
   {
      assertUnsent();
      _RequestType = value;
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
    * Sets the ClearingFirmBroker field for the request.
    * 
    * @param value  Value that the ClearingFirmBroker will be set to.
    */
   public final void setClearingFirmBroker( String value )
   {
      assertUnsent();
      _ClearingFirmBroker = value;
   }
	
   /**
    * Sets the Relation Type field for the request.
    * 
    * @param value  Value that the Relation Type will be set to.
    */
   public final void setRelationType( String value )
   {
      assertUnsent();
      _RelationType = value;
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
      requestBuffer.appendField( _SrchBrokerName );
      requestBuffer.appendField( _RequestType );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _ValidationType );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _ClearingFirmBroker );
      requestBuffer.appendField( _RelationType );
   }

}

