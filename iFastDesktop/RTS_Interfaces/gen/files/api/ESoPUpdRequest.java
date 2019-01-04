// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * ESoP Plan  Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/ESoPUpd.doc">ESoPUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class ESoPUpdRequest extends IFastRequest implements Serializable
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
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Administrating Institution of the ESoP member variable.
    */
   private String _IFASNumber = "";
            
   /**
    * Initial Purchase Date member variable.
    */
   private Date _InitPurchDate = null;
            
   /**
    * Flag indicating if new acct is created automatically member variable.
    */
   private Boolean _AutoCreate = new Boolean(false);
            
   /**
    * Interruption Date member variable.
    */
   private Date _InterruptDate = null;
            
   /**
    * Interruption Code member variable.
    */
   private String _InterruptCode = "";
            
   /**
    * Banking record Effective Date member variable.
    */
   private Date _BankEffectiveDate = null;
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Currency member variable.
    */
   private String _Currency = "";
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * SalesRepCode member variable.
    */
   private String _SalesRepCode = "";
            
   /**
    * Last Name member variable.
    */
   private String _LastName = "";
            
   /**
    * First Name member variable.
    */
   private String _FirstName = "";
            
            
            
   /**
    * Version Number member variable.
    */
   private Integer _EsopVersion = null;
            
   /**
    * Esop RecId member variable.
    */
   private Integer _EsopRId = null;
            

   /**
    * Constructs the ESoPUpdRequest object.
    * 
    */
   ESoPUpdRequest()
   {
      super ( 168 );
   }

   /**
    * Constructs the ESoPUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ESoPUpdRequest( String hostEncoding )
   {
      super ( 168, hostEncoding );
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
    * Sets the Run Mode field for the request.
    * 
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( String value )
   {
      assertUnsent();
      _RunMode = value;
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
    * Sets the Administrating Institution of the ESoP field for the request.
    * 
    * @param value  Value that the Administrating Institution of the ESoP will be set to.
    */
   public final void setIFASNumber( String value )
   {
      assertUnsent();
      _IFASNumber = value;
   }
	
   /**
    * Sets the Initial Purchase Date field for the request.
    * 
    * @param value  Value that the Initial Purchase Date will be set to.
    */
   public final void setInitPurchDate( Date value )
   {
      assertUnsent();
      _InitPurchDate = value;
   }
	
   /**
    * Sets the Flag indicating if new acct is created automatically field for the request.
    * 
    * @param value  Value that the Flag indicating if new acct is created automatically will be set to.
    */
   public final void setAutoCreate( Boolean value )
   {
      assertUnsent();
      _AutoCreate = value;
   }
	
   /**
    * Sets the Interruption Date field for the request.
    * 
    * @param value  Value that the Interruption Date will be set to.
    */
   public final void setInterruptDate( Date value )
   {
      assertUnsent();
      _InterruptDate = value;
   }
	
   /**
    * Sets the Interruption Code field for the request.
    * 
    * @param value  Value that the Interruption Code will be set to.
    */
   public final void setInterruptCode( String value )
   {
      assertUnsent();
      _InterruptCode = value;
   }
	
   /**
    * Sets the Banking record Effective Date field for the request.
    * 
    * @param value  Value that the Banking record Effective Date will be set to.
    */
   public final void setBankEffectiveDate( Date value )
   {
      assertUnsent();
      _BankEffectiveDate = value;
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
    * Sets the Amount field for the request.
    * 
    * @param value  Value that the Amount will be set to.
    */
   public final void setAmount( String value )
   {
      assertUnsent();
      _Amount = value;
   }
	
   /**
    * Sets the Currency field for the request.
    * 
    * @param value  Value that the Currency will be set to.
    */
   public final void setCurrency( String value )
   {
      assertUnsent();
      _Currency = value;
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
    * Sets the SalesRepCode field for the request.
    * 
    * @param value  Value that the SalesRepCode will be set to.
    */
   public final void setSalesRepCode( String value )
   {
      assertUnsent();
      _SalesRepCode = value;
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
    * Sets the Version Number field for the request.
    * 
    * @param value  Value that the Version Number will be set to.
    */
   public final void setEsopVersion( Integer value )
   {
      assertUnsent();
      _EsopVersion = value;
   }
	
   /**
    * Sets the Esop RecId field for the request.
    * 
    * @param value  Value that the Esop RecId will be set to.
    */
   public final void setEsopRId( Integer value )
   {
      assertUnsent();
      _EsopRId = value;
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
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _IFASNumber );
      requestBuffer.appendField( _InitPurchDate );
      requestBuffer.appendField( _AutoCreate );
      requestBuffer.appendField( _InterruptDate );
      requestBuffer.appendField( _InterruptCode );
      requestBuffer.appendField( _BankEffectiveDate );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _Currency );
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SalesRepCode );
      requestBuffer.appendField( _LastName );
      requestBuffer.appendField( _FirstName );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _EsopVersion );
      requestBuffer.appendField( _EsopRId );
   }

}

