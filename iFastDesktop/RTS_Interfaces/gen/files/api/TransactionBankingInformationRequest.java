// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Transaction Banking Information request.
 * For additional view information see <A HREF="../../../../viewspecs/TransactionBankingInformation.doc">TransactionBankingInformation.doc</A>.
 * 
 * @author RTS Generated
 */
public class TransactionBankingInformationRequest extends IFastRequest implements Serializable
{

   /**
    * Transaction Id number member variable.
    */
   private String _TransId = "0";
            
   /**
    * Pending Record ID member variable.
    */
   private Integer _PendingRid = null;
            
   /**
    * Transaction or Pending member variable.
    */
   private String _TransPending = "";
            
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
    * Transaction settlement  Currency member variable.
    */
   private String _Currency = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
            
            
   /**
    * what type of last banking record is requested member variable.
    */
   private String _LastBankType = "";
            
            

   /**
    * Constructs the TransactionBankingInformationRequest object.
    * 
    */
   TransactionBankingInformationRequest()
   {
      super ( 55 );
   }

   /**
    * Constructs the TransactionBankingInformationRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TransactionBankingInformationRequest( String hostEncoding )
   {
      super ( 55, hostEncoding );
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
    * Sets the Pending Record ID field for the request.
    * 
    * @param value  Value that the Pending Record ID will be set to.
    */
   public final void setPendingRid( Integer value )
   {
      assertUnsent();
      _PendingRid = value;
   }
	
   /**
    * Sets the Transaction or Pending field for the request.
    * 
    * @param value  Value that the Transaction or Pending will be set to.
    */
   public final void setTransPending( String value )
   {
      assertUnsent();
      _TransPending = value;
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
    * Sets the Transaction settlement  Currency field for the request.
    * 
    * @param value  Value that the Transaction settlement  Currency will be set to.
    */
   public final void setCurrency( String value )
   {
      assertUnsent();
      _Currency = value;
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
    * Sets the what type of last banking record is requested field for the request.
    * 
    * @param value  Value that the what type of last banking record is requested will be set to.
    */
   public final void setLastBankType( String value )
   {
      assertUnsent();
      _LastBankType = value;
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
      requestBuffer.appendField( _PendingRid );
      requestBuffer.appendField( _TransPending );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _Currency );
      requestBuffer.appendField( _AccountNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _LastBankType );
      encodeNextKeyField( requestBuffer );
   }

}

