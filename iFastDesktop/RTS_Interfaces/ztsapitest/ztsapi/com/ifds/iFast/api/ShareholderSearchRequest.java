// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Search for shareholder/account Enitty request.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderSearch.doc">ShareholderSearch.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderSearchRequest extends IFastRequest implements Serializable
{

   /**
    * Shareholder account number member variable.
    */
   private String _SrchAccountNum = "0";
            
   /**
    * Shareholder number member variable.
    */
   private String _SrchShrNum = "0";
            
   /**
    * Entity last name member variable.
    */
   private String _SrchLastName = "";
            
   /**
    * Entity first name member variable.
    */
   private String _SrchFirstName = "";
            
   /**
    * Entity Birth Last Name member variable.
    */
   private String _SrchBirthLName = "";
            
   /**
    * Entity Birth First Name member variable.
    */
   private String _SrchBirthFName = "";
            
   /**
    * Shareholder's SIN Number member variable.
    */
   private String _SrchSIN = "";
            
   /**
    * Identification Type member variable.
    */
   private String _SrchIdType = "";
            
   /**
    * Identification Number member variable.
    */
   private String _SrchIdValue = "";
            
   /**
    * Family Code member variable.
    */
   private String _SrchFamily = "";
            
   /**
    * Shareholder Group member variable.
    */
   private String _SrchGroup = "";
            
   /**
    * Intermediary Code member variable.
    */
   private String _SrchIntCode = "";
            
   /**
    * Intermediary Account member variable.
    */
   private String _SrchIntAcct = "";
            
   /**
    * Cross Reference Number member variable.
    */
   private String _SrchXrefNum = "";
            
   /**
    * Alternate Account member variable.
    */
   private String _SrchAltAcct = "";
            
   /**
    * Broker Code member variable.
    */
   private String _SrchBroker = "";
            
   /**
    * BranchCode member variable.
    */
   private String _SrchBranch = "";
            
   /**
    * Salesrep Code member variable.
    */
   private String _SrchSlsrep = "";
            
   /**
    * Wire Order Number member variable.
    */
   private String _SrchWireNum = "";
            
   /**
    * Home Telephone Number Country Code member variable.
    */
   private String _SrchPhoneCntry = "";
            
   /**
    * Home Telephone Number Area Code member variable.
    */
   private String _SrchPhoneArea = "";
            
   /**
    * Home Telephone Number member variable.
    */
   private String _SrchPhoneNum = "";
            
            
   /**
    * Session ID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Records order code member variable.
    */
   private String _SortBy = "";
            
   /**
    * Entity Type to be search for member variable.
    */
   private String _SrchEntType = "";
            
   /**
    * Return all accounts or only 1 member variable.
    */
   private Boolean _AllAccounts = new Boolean(false);
            
            
            
            
   /**
    * Return Next or Previous record member variable.
    */
   private Boolean _NextOrPrevious = new Boolean(false);
            
   /**
    * Fund Company Code member variable.
    */
   private String _tmpCompanyCode = "";
            
   /**
    * Business Number member variable.
    */
   private String _SrchBusinessNo = "";
            
   /**
    * Exact Match member variable.
    */
   private Boolean _ExactMatch = new Boolean(false);
            
   /**
    * All Entities member variable.
    */
   private Boolean _AllEntities = new Boolean(false);
            
   /**
    * indicates that Entity Search is by WhereUse member variable.
    */
   private String _SrchWhereUse = "";
            
   /**
    * Indicates fund code the paying agent is setup for member variable.
    */
   private String _SrchWhereUseKey = "";
            
   /**
    * Reference Code member variable.
    */
   private String _SrchRefCode = "";
            
   /**
    * Registration Agent Code member variable.
    */
   private String _SrchAcctRegKey = "";
            
   /**
    * Returns only Holding Company when yes member variable.
    */
   private String _RetHoldingCoOnly = "";
            

   /**
    * Constructs the ShareholderSearchRequest object.
    * 
    */
   ShareholderSearchRequest()
   {
      super ( 3 );
   }

   /**
    * Constructs the ShareholderSearchRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShareholderSearchRequest( String hostEncoding )
   {
      super ( 3, hostEncoding );
   }

   /**
    * Sets the Shareholder account number field for the request.
    * 
    * @param value  Value that the Shareholder account number will be set to.
    */
   public final void setSrchAccountNum( String value )
   {
      assertUnsent();
      _SrchAccountNum = value;
   }
	
   /**
    * Sets the Shareholder number field for the request.
    * 
    * @param value  Value that the Shareholder number will be set to.
    */
   public final void setSrchShrNum( String value )
   {
      assertUnsent();
      _SrchShrNum = value;
   }
	
   /**
    * Sets the Entity last name field for the request.
    * 
    * @param value  Value that the Entity last name will be set to.
    */
   public final void setSrchLastName( String value )
   {
      assertUnsent();
      _SrchLastName = value;
   }
	
   /**
    * Sets the Entity first name field for the request.
    * 
    * @param value  Value that the Entity first name will be set to.
    */
   public final void setSrchFirstName( String value )
   {
      assertUnsent();
      _SrchFirstName = value;
   }
	
   /**
    * Sets the Entity Birth Last Name field for the request.
    * 
    * @param value  Value that the Entity Birth Last Name will be set to.
    */
   public final void setSrchBirthLName( String value )
   {
      assertUnsent();
      _SrchBirthLName = value;
   }
	
   /**
    * Sets the Entity Birth First Name field for the request.
    * 
    * @param value  Value that the Entity Birth First Name will be set to.
    */
   public final void setSrchBirthFName( String value )
   {
      assertUnsent();
      _SrchBirthFName = value;
   }
	
   /**
    * Sets the Shareholder's SIN Number field for the request.
    * 
    * @param value  Value that the Shareholder's SIN Number will be set to.
    */
   public final void setSrchSIN( String value )
   {
      assertUnsent();
      _SrchSIN = value;
   }
	
   /**
    * Sets the Identification Type field for the request.
    * 
    * @param value  Value that the Identification Type will be set to.
    */
   public final void setSrchIdType( String value )
   {
      assertUnsent();
      _SrchIdType = value;
   }
	
   /**
    * Sets the Identification Number field for the request.
    * 
    * @param value  Value that the Identification Number will be set to.
    */
   public final void setSrchIdValue( String value )
   {
      assertUnsent();
      _SrchIdValue = value;
   }
	
   /**
    * Sets the Family Code field for the request.
    * 
    * @param value  Value that the Family Code will be set to.
    */
   public final void setSrchFamily( String value )
   {
      assertUnsent();
      _SrchFamily = value;
   }
	
   /**
    * Sets the Shareholder Group field for the request.
    * 
    * @param value  Value that the Shareholder Group will be set to.
    */
   public final void setSrchGroup( String value )
   {
      assertUnsent();
      _SrchGroup = value;
   }
	
   /**
    * Sets the Intermediary Code field for the request.
    * 
    * @param value  Value that the Intermediary Code will be set to.
    */
   public final void setSrchIntCode( String value )
   {
      assertUnsent();
      _SrchIntCode = value;
   }
	
   /**
    * Sets the Intermediary Account field for the request.
    * 
    * @param value  Value that the Intermediary Account will be set to.
    */
   public final void setSrchIntAcct( String value )
   {
      assertUnsent();
      _SrchIntAcct = value;
   }
	
   /**
    * Sets the Cross Reference Number field for the request.
    * 
    * @param value  Value that the Cross Reference Number will be set to.
    */
   public final void setSrchXrefNum( String value )
   {
      assertUnsent();
      _SrchXrefNum = value;
   }
	
   /**
    * Sets the Alternate Account field for the request.
    * 
    * @param value  Value that the Alternate Account will be set to.
    */
   public final void setSrchAltAcct( String value )
   {
      assertUnsent();
      _SrchAltAcct = value;
   }
	
   /**
    * Sets the Broker Code field for the request.
    * 
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setSrchBroker( String value )
   {
      assertUnsent();
      _SrchBroker = value;
   }
	
   /**
    * Sets the BranchCode field for the request.
    * 
    * @param value  Value that the BranchCode will be set to.
    */
   public final void setSrchBranch( String value )
   {
      assertUnsent();
      _SrchBranch = value;
   }
	
   /**
    * Sets the Salesrep Code field for the request.
    * 
    * @param value  Value that the Salesrep Code will be set to.
    */
   public final void setSrchSlsrep( String value )
   {
      assertUnsent();
      _SrchSlsrep = value;
   }
	
   /**
    * Sets the Wire Order Number field for the request.
    * 
    * @param value  Value that the Wire Order Number will be set to.
    */
   public final void setSrchWireNum( String value )
   {
      assertUnsent();
      _SrchWireNum = value;
   }
	
   /**
    * Sets the Home Telephone Number Country Code field for the request.
    * 
    * @param value  Value that the Home Telephone Number Country Code will be set to.
    */
   public final void setSrchPhoneCntry( String value )
   {
      assertUnsent();
      _SrchPhoneCntry = value;
   }
	
   /**
    * Sets the Home Telephone Number Area Code field for the request.
    * 
    * @param value  Value that the Home Telephone Number Area Code will be set to.
    */
   public final void setSrchPhoneArea( String value )
   {
      assertUnsent();
      _SrchPhoneArea = value;
   }
	
   /**
    * Sets the Home Telephone Number field for the request.
    * 
    * @param value  Value that the Home Telephone Number will be set to.
    */
   public final void setSrchPhoneNum( String value )
   {
      assertUnsent();
      _SrchPhoneNum = value;
   }
	
   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Records order code field for the request.
    * 
    * @param value  Value that the Records order code will be set to.
    */
   public final void setSortBy( String value )
   {
      assertUnsent();
      _SortBy = value;
   }
	
   /**
    * Sets the Entity Type to be search for field for the request.
    * 
    * @param value  Value that the Entity Type to be search for will be set to.
    */
   public final void setSrchEntType( String value )
   {
      assertUnsent();
      _SrchEntType = value;
   }
	
   /**
    * Sets the Return all accounts or only 1 field for the request.
    * 
    * @param value  Value that the Return all accounts or only 1 will be set to.
    */
   public final void setAllAccounts( Boolean value )
   {
      assertUnsent();
      _AllAccounts = value;
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
    * Sets the Fund Company Code field for the request.
    * 
    * @param value  Value that the Fund Company Code will be set to.
    */
   public final void settmpCompanyCode( String value )
   {
      assertUnsent();
      _tmpCompanyCode = value;
   }
	
   /**
    * Sets the Business Number field for the request.
    * 
    * @param value  Value that the Business Number will be set to.
    */
   public final void setSrchBusinessNo( String value )
   {
      assertUnsent();
      _SrchBusinessNo = value;
   }
	
   /**
    * Sets the Exact Match field for the request.
    * 
    * @param value  Value that the Exact Match will be set to.
    */
   public final void setExactMatch( Boolean value )
   {
      assertUnsent();
      _ExactMatch = value;
   }
	
   /**
    * Sets the All Entities field for the request.
    * 
    * @param value  Value that the All Entities will be set to.
    */
   public final void setAllEntities( Boolean value )
   {
      assertUnsent();
      _AllEntities = value;
   }
	
   /**
    * Sets the indicates that Entity Search is by WhereUse field for the request.
    * 
    * @param value  Value that the indicates that Entity Search is by WhereUse will be set to.
    */
   public final void setSrchWhereUse( String value )
   {
      assertUnsent();
      _SrchWhereUse = value;
   }
	
   /**
    * Sets the Indicates fund code the paying agent is setup for field for the request.
    * 
    * @param value  Value that the Indicates fund code the paying agent is setup for will be set to.
    */
   public final void setSrchWhereUseKey( String value )
   {
      assertUnsent();
      _SrchWhereUseKey = value;
   }
	
   /**
    * Sets the Reference Code field for the request.
    * 
    * @param value  Value that the Reference Code will be set to.
    */
   public final void setSrchRefCode( String value )
   {
      assertUnsent();
      _SrchRefCode = value;
   }
	
   /**
    * Sets the Registration Agent Code field for the request.
    * 
    * @param value  Value that the Registration Agent Code will be set to.
    */
   public final void setSrchAcctRegKey( String value )
   {
      assertUnsent();
      _SrchAcctRegKey = value;
   }
	
   /**
    * Sets the Returns only Holding Company when yes field for the request.
    * 
    * @param value  Value that the Returns only Holding Company when yes will be set to.
    */
   public final void setRetHoldingCoOnly( String value )
   {
      assertUnsent();
      _RetHoldingCoOnly = value;
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
      requestBuffer.appendField( _SrchAccountNum );
      requestBuffer.appendField( _SrchShrNum );
      requestBuffer.appendField( _SrchLastName );
      requestBuffer.appendField( _SrchFirstName );
      requestBuffer.appendField( _SrchBirthLName );
      requestBuffer.appendField( _SrchBirthFName );
      requestBuffer.appendField( _SrchSIN );
      requestBuffer.appendField( _SrchIdType );
      requestBuffer.appendField( _SrchIdValue );
      requestBuffer.appendField( _SrchFamily );
      requestBuffer.appendField( _SrchGroup );
      requestBuffer.appendField( _SrchIntCode );
      requestBuffer.appendField( _SrchIntAcct );
      requestBuffer.appendField( _SrchXrefNum );
      requestBuffer.appendField( _SrchAltAcct );
      requestBuffer.appendField( _SrchBroker );
      requestBuffer.appendField( _SrchBranch );
      requestBuffer.appendField( _SrchSlsrep );
      requestBuffer.appendField( _SrchWireNum );
      requestBuffer.appendField( _SrchPhoneCntry );
      requestBuffer.appendField( _SrchPhoneArea );
      requestBuffer.appendField( _SrchPhoneNum );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _SortBy );
      requestBuffer.appendField( _SrchEntType );
      requestBuffer.appendField( _AllAccounts );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( _NextOrPrevious );
      requestBuffer.appendField( _tmpCompanyCode );
      requestBuffer.appendField( _SrchBusinessNo );
      requestBuffer.appendField( _ExactMatch );
      requestBuffer.appendField( _AllEntities );
      requestBuffer.appendField( _SrchWhereUse );
      requestBuffer.appendField( _SrchWhereUseKey );
      requestBuffer.appendField( _SrchRefCode );
      requestBuffer.appendField( _SrchAcctRegKey );
      requestBuffer.appendField( _RetHoldingCoOnly );
   }

}

