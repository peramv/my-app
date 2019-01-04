// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * EOE Trade Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/EOETDInq.doc">EOETDInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class EOETDInqRequest extends IFastRequest implements Serializable
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
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Order Type member variable.
    */
   private Boolean _OrderType = new Boolean(false);
            
   /**
    * Pay Type member variable.
    */
   private String _PayType = "";
            
   /**
    * Amount Type member variable.
    */
   private String _AmountType = "";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * Fund To Code member variable.
    */
   private String _FundToCode = "";
            
   /**
    * Class To Code member variable.
    */
   private String _ClassToCode = "";
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            

   /**
    * Constructs the EOETDInqRequest object.
    * 
    */
   EOETDInqRequest()
   {
      super ( 368 );
   }

   /**
    * Constructs the EOETDInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EOETDInqRequest( String hostEncoding )
   {
      super ( 368, hostEncoding );
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
    * Sets the Order Type field for the request.
    * 
    * @param value  Value that the Order Type will be set to.
    */
   public final void setOrderType( Boolean value )
   {
      assertUnsent();
      _OrderType = value;
   }
	
   /**
    * Sets the Pay Type field for the request.
    * 
    * @param value  Value that the Pay Type will be set to.
    */
   public final void setPayType( String value )
   {
      assertUnsent();
      _PayType = value;
   }
	
   /**
    * Sets the Amount Type field for the request.
    * 
    * @param value  Value that the Amount Type will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
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
    * Sets the Fund To Code field for the request.
    * 
    * @param value  Value that the Fund To Code will be set to.
    */
   public final void setFundToCode( String value )
   {
      assertUnsent();
      _FundToCode = value;
   }
	
   /**
    * Sets the Class To Code field for the request.
    * 
    * @param value  Value that the Class To Code will be set to.
    */
   public final void setClassToCode( String value )
   {
      assertUnsent();
      _ClassToCode = value;
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
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _OrderType );
      requestBuffer.appendField( _PayType );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _FundToCode );
      requestBuffer.appendField( _ClassToCode );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _AccountNum );
   }

}

