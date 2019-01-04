// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Payment Instructions Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/PayInstructMaint.doc">PayInstructMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class PayInstructMaintRequest extends IFastRequest implements Serializable
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
    * SearchType member variable.
    */
   private String _SearchType = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Broker Code member array.
    */
   private String[] _BrokerCode = new String[25];
            
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = new String[25];
            
   /**
    * SalesRepCode member array.
    */
   private String[] _SalesRepCode = new String[25];
            
   /**
    * PaymentFor member array.
    */
   private String[] _PaymentFor = new String[25];
            
   /**
    * PayType member array.
    */
   private String[] _PayType = new String[25];
            
   /**
    * Payment Method member array.
    */
   private String[] _PaymentMethod = new String[25];
            
   /**
    * Bank Charge member array.
    */
   private String[] _BankCharge = new String[25];
            
   /**
    * Currency Option member array.
    */
   private String[] _CurrencyOption = new String[25];
            
   /**
    * Pay Currency member array.
    */
   private String[] _PayCurrency = new String[25];
            
   /**
    * Use Entity Address member array.
    */
   private Boolean[] _UseEntityAddress = new Boolean[25];
            
   /**
    * Address Line 1 member array.
    */
   private String[] _AddrLine1 = new String[25];
            
   /**
    * Address Line 2 member array.
    */
   private String[] _AddrLine2 = new String[25];
            
   /**
    * Address Line 3 member array.
    */
   private String[] _AddrLine3 = new String[25];
            
   /**
    * Address Line 4 member array.
    */
   private String[] _AddrLine4 = new String[25];
            
   /**
    * Address Line 5 member array.
    */
   private String[] _AddrLine5 = new String[25];
            
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = new String[25];
            
   /**
    * Country Code member array.
    */
   private String[] _CountryCode = new String[25];
            
   /**
    * Payment Instruction ID member array.
    */
   private String[] _PayInstructId = new String[25];
            
   /**
    * ACH Processor member array.
    */
   private String[] _ACHProcessor = new String[25];
            
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = new String[25];
            
   /**
    * DirectTo member array.
    */
   private String[] _DirectTo = new String[25];
            
   /**
    * Redirect To SHGroup member array.
    */
   private String[] _ToSHGroup = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _Deff = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Consolidation Type member array.
    */
   private String[] _ConsolType = new String[25];
            
   /**
    * PymtRoutingMthd member array.
    */
   private String[] _PymtRoutingMthd = new String[25];
            

   /**
    * Constructs the PayInstructMaintRequest object.
    * 
    */
   PayInstructMaintRequest()
   {
      super ( 257 );
   }

   /**
    * Constructs the PayInstructMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PayInstructMaintRequest( String hostEncoding )
   {
      super ( 257, hostEncoding );
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
    * Sets the SearchType field for the request.
    * 
    * @param value  Value that the SearchType will be set to.
    */
   public final void setSearchType( String value )
   {
      assertUnsent();
      _SearchType = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the RunMode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RunMode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Broker Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Broker Code will be set to.
    */
   public final void setBrokerCode( int index, String value )
   {
      assertUnsent();
      _BrokerCode[index] = value;
   }
	
   /**
    * Sets the Branch Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Branch Code will be set to.
    */
   public final void setBranchCode( int index, String value )
   {
      assertUnsent();
      _BranchCode[index] = value;
   }
	
   /**
    * Sets the SalesRepCode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SalesRepCode will be set to.
    */
   public final void setSalesRepCode( int index, String value )
   {
      assertUnsent();
      _SalesRepCode[index] = value;
   }
	
   /**
    * Sets the PaymentFor field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the PaymentFor will be set to.
    */
   public final void setPaymentFor( int index, String value )
   {
      assertUnsent();
      _PaymentFor[index] = value;
   }
	
   /**
    * Sets the PayType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the PayType will be set to.
    */
   public final void setPayType( int index, String value )
   {
      assertUnsent();
      _PayType[index] = value;
   }
	
   /**
    * Sets the Payment Method field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payment Method will be set to.
    */
   public final void setPaymentMethod( int index, String value )
   {
      assertUnsent();
      _PaymentMethod[index] = value;
   }
	
   /**
    * Sets the Bank Charge field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Charge will be set to.
    */
   public final void setBankCharge( int index, String value )
   {
      assertUnsent();
      _BankCharge[index] = value;
   }
	
   /**
    * Sets the Currency Option field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Currency Option will be set to.
    */
   public final void setCurrencyOption( int index, String value )
   {
      assertUnsent();
      _CurrencyOption[index] = value;
   }
	
   /**
    * Sets the Pay Currency field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Currency will be set to.
    */
   public final void setPayCurrency( int index, String value )
   {
      assertUnsent();
      _PayCurrency[index] = value;
   }
	
   /**
    * Sets the Use Entity Address field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Use Entity Address will be set to.
    */
   public final void setUseEntityAddress( int index, Boolean value )
   {
      assertUnsent();
      _UseEntityAddress[index] = value;
   }
	
   /**
    * Sets the Address Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 1 will be set to.
    */
   public final void setAddrLine1( int index, String value )
   {
      assertUnsent();
      _AddrLine1[index] = value;
   }
	
   /**
    * Sets the Address Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 2 will be set to.
    */
   public final void setAddrLine2( int index, String value )
   {
      assertUnsent();
      _AddrLine2[index] = value;
   }
	
   /**
    * Sets the Address Line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 3 will be set to.
    */
   public final void setAddrLine3( int index, String value )
   {
      assertUnsent();
      _AddrLine3[index] = value;
   }
	
   /**
    * Sets the Address Line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 4 will be set to.
    */
   public final void setAddrLine4( int index, String value )
   {
      assertUnsent();
      _AddrLine4[index] = value;
   }
	
   /**
    * Sets the Address Line 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 5 will be set to.
    */
   public final void setAddrLine5( int index, String value )
   {
      assertUnsent();
      _AddrLine5[index] = value;
   }
	
   /**
    * Sets the Postal Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Postal Code will be set to.
    */
   public final void setPostalCode( int index, String value )
   {
      assertUnsent();
      _PostalCode[index] = value;
   }
	
   /**
    * Sets the Country Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Country Code will be set to.
    */
   public final void setCountryCode( int index, String value )
   {
      assertUnsent();
      _CountryCode[index] = value;
   }
	
   /**
    * Sets the Payment Instruction ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payment Instruction ID will be set to.
    */
   public final void setPayInstructId( int index, String value )
   {
      assertUnsent();
      _PayInstructId[index] = value;
   }
	
   /**
    * Sets the ACH Processor field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ACH Processor will be set to.
    */
   public final void setACHProcessor( int index, String value )
   {
      assertUnsent();
      _ACHProcessor[index] = value;
   }
	
   /**
    * Sets the Account Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( int index, String value )
   {
      assertUnsent();
      _AccountNum[index] = value;
   }
	
   /**
    * Sets the DirectTo field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the DirectTo will be set to.
    */
   public final void setDirectTo( int index, String value )
   {
      assertUnsent();
      _DirectTo[index] = value;
   }
	
   /**
    * Sets the Redirect To SHGroup field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Redirect To SHGroup will be set to.
    */
   public final void setToSHGroup( int index, String value )
   {
      assertUnsent();
      _ToSHGroup[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setDeff( int index, Date value )
   {
      assertUnsent();
      _Deff[index] = value;
   }
	
   /**
    * Sets the Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Consolidation Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Consolidation Type will be set to.
    */
   public final void setConsolType( int index, String value )
   {
      assertUnsent();
      _ConsolType[index] = value;
   }
	
   /**
    * Sets the PymtRoutingMthd field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the PymtRoutingMthd will be set to.
    */
   public final void setPymtRoutingMthd( int index, String value )
   {
      assertUnsent();
      _PymtRoutingMthd[index] = value;
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
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _BrokerCode[x] );
         requestBuffer.appendField( _BranchCode[x] );
         requestBuffer.appendField( _SalesRepCode[x] );
         requestBuffer.appendField( _PaymentFor[x] );
         requestBuffer.appendField( _PayType[x] );
         requestBuffer.appendField( _PaymentMethod[x] );
         requestBuffer.appendField( _BankCharge[x] );
         requestBuffer.appendField( _CurrencyOption[x] );
         requestBuffer.appendField( _PayCurrency[x] );
         requestBuffer.appendField( _UseEntityAddress[x] );
         requestBuffer.appendField( _AddrLine1[x] );
         requestBuffer.appendField( _AddrLine2[x] );
         requestBuffer.appendField( _AddrLine3[x] );
         requestBuffer.appendField( _AddrLine4[x] );
         requestBuffer.appendField( _AddrLine5[x] );
         requestBuffer.appendField( _PostalCode[x] );
         requestBuffer.appendField( _CountryCode[x] );
         requestBuffer.appendField( _PayInstructId[x] );
         requestBuffer.appendField( _ACHProcessor[x] );
         requestBuffer.appendField( _AccountNum[x] );
         requestBuffer.appendField( _DirectTo[x] );
         requestBuffer.appendField( _ToSHGroup[x] );
         requestBuffer.appendField( _Deff[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _ConsolType[x] );
         requestBuffer.appendField( _PymtRoutingMthd[x] );
      }
   }

}

