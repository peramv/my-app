// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * FUNDcom Account Inquiry request.
 * For additional view information see <A HREF="../../../../viewspecs/FUNDComAcctInq.doc">FUNDComAcctInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FUNDComAcctInqRequest extends IFastRequest implements Serializable
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
    * Return Next or Previous record member variable.
    */
   private Boolean _NextOrPrevious = new Boolean(false);
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SalesRepCode = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Social Insurance Number member variable.
    */
   private String _SIN = "";
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Alternative Account Number member variable.
    */
   private String _AltAccount = "";
            
   /**
    * Last Name member variable.
    */
   private String _LastName = "";
            
   /**
    * First Name member variable.
    */
   private String _FirstName = "";
            
   /**
    * Corporate or Individual member variable.
    */
   private Boolean _CorpIndiv = new Boolean(false);
            
   /**
    * In Trust For or Joint member variable.
    */
   private String _InTrustJoint = "";
            
   /**
    * Intermediary Code member variable.
    */
   private String _IntermCode = "";
            
   /**
    * Intermediary Account member variable.
    */
   private String _InterAcct = "";
            
            

   /**
    * Constructs the FUNDComAcctInqRequest object.
    * 
    */
   FUNDComAcctInqRequest()
   {
      super ( 118 );
   }

   /**
    * Constructs the FUNDComAcctInqRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FUNDComAcctInqRequest( String hostEncoding )
   {
      super ( 118, hostEncoding );
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
    * Sets the Return Next or Previous record field for the request.
    * 
    * @param value  Value that the Return Next or Previous record will be set to.
    */
   public final void setNextOrPrevious( Boolean value )
   {
      assertUnsent();
      _NextOrPrevious = value;
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
    * Sets the Social Insurance Number field for the request.
    * 
    * @param value  Value that the Social Insurance Number will be set to.
    */
   public final void setSIN( String value )
   {
      assertUnsent();
      _SIN = value;
   }
	
   /**
    * Sets the Shareholder Number field for the request.
    * 
    * @param value  Value that the Shareholder Number will be set to.
    */
   public final void setShrNum( String value )
   {
      assertUnsent();
      _ShrNum = value;
   }
	
   /**
    * Sets the Alternative Account Number field for the request.
    * 
    * @param value  Value that the Alternative Account Number will be set to.
    */
   public final void setAltAccount( String value )
   {
      assertUnsent();
      _AltAccount = value;
   }
	
   /**
    * Sets the Last Name field for the request.
    * 
    * @param value  Value that the Last Name will be set to.
    */
   public final void setLastName( String value )
   {
      assertUnsent();
      _LastName = value;
   }
	
   /**
    * Sets the First Name field for the request.
    * 
    * @param value  Value that the First Name will be set to.
    */
   public final void setFirstName( String value )
   {
      assertUnsent();
      _FirstName = value;
   }
	
   /**
    * Sets the Corporate or Individual field for the request.
    * 
    * @param value  Value that the Corporate or Individual will be set to.
    */
   public final void setCorpIndiv( Boolean value )
   {
      assertUnsent();
      _CorpIndiv = value;
   }
	
   /**
    * Sets the In Trust For or Joint field for the request.
    * 
    * @param value  Value that the In Trust For or Joint will be set to.
    */
   public final void setInTrustJoint( String value )
   {
      assertUnsent();
      _InTrustJoint = value;
   }
	
   /**
    * Sets the Intermediary Code field for the request.
    * 
    * @param value  Value that the Intermediary Code will be set to.
    */
   public final void setIntermCode( String value )
   {
      assertUnsent();
      _IntermCode = value;
   }
	
   /**
    * Sets the Intermediary Account field for the request.
    * 
    * @param value  Value that the Intermediary Account will be set to.
    */
   public final void setInterAcct( String value )
   {
      assertUnsent();
      _InterAcct = value;
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
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _NextOrPrevious );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SalesRepCode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _SIN );
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( _AltAccount );
      requestBuffer.appendField( _LastName );
      requestBuffer.appendField( _FirstName );
      requestBuffer.appendField( _CorpIndiv );
      requestBuffer.appendField( _InTrustJoint );
      requestBuffer.appendField( _IntermCode );
      requestBuffer.appendField( _InterAcct );
      encodeOverrideRepeatsField( requestBuffer );
   }

}

