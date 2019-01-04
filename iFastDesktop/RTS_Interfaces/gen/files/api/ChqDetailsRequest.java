// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Cheque details request.
 * For additional view information see <A HREF="../../../../viewspecs/ChqDetails.doc">ChqDetails.doc</A>.
 * 
 * @author RTS Generated
 */
public class ChqDetailsRequest extends IFastRequest implements Serializable
{

   /**
    * Transaction Id number member variable.
    */
   private String _TransId = "0";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Cheque Number member variable.
    */
   private String _InCheqNum = "";
            
            
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
    * TxnLevelSec member variable.
    */
   private Boolean _TxnLevelSec = new Boolean(false);
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Cheque Status member variable.
    */
   private String _ChqStat = "";
            

   /**
    * Constructs the ChqDetailsRequest object.
    * 
    */
   ChqDetailsRequest()
   {
      super ( 21 );
   }

   /**
    * Constructs the ChqDetailsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ChqDetailsRequest( String hostEncoding )
   {
      super ( 21, hostEncoding );
   }

   /**
    * Sets the Transaction Id number field for the request.
    * 
    * @param value  Value that the Transaction Id number will be set to.
    */
   public final void setTransId( String value )
   {
      assertUnsent();
      _TransId = value;
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
    * Sets the Cheque Number field for the request.
    * 
    * @param value  Value that the Cheque Number will be set to.
    */
   public final void setInCheqNum( String value )
   {
      assertUnsent();
      _InCheqNum = value;
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
    * Sets the TxnLevelSec field for the request.
    * 
    * @param value  Value that the TxnLevelSec will be set to.
    */
   public final void setTxnLevelSec( Boolean value )
   {
      assertUnsent();
      _TxnLevelSec = value;
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
    * Sets the Cheque Status field for the request.
    * 
    * @param value  Value that the Cheque Status will be set to.
    */
   public final void setChqStat( String value )
   {
      assertUnsent();
      _ChqStat = value;
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
      requestBuffer.appendField( _TransId );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _InCheqNum );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _TxnLevelSec );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _ChqStat );
   }

}

