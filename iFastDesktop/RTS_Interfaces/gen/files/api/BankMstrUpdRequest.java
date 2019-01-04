// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Bank Master Update request.
 * For additional view information see <A HREF="../../../../viewspecs/BankMstrUpd.doc">BankMstrUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class BankMstrUpdRequest extends IFastRequest implements Serializable
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
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Bank Id Number member array.
    */
   private String[] _BankIdNum = new String[25];
            
   /**
    * Swift Code member array.
    */
   private Integer[] _SwiftCode = new Integer[25];
            
   /**
    * Reference Number member array.
    */
   private Integer[] _RefNumber = new Integer[25];
            
   /**
    * Institution Name member array.
    */
   private String[] _InstName = new String[25];
            
   /**
    * Short Name member array.
    */
   private String[] _ShortName = new String[25];
            
   /**
    * Contact member array.
    */
   private String[] _Contact = new String[25];
            
   /**
    * Parent Bank member array.
    */
   private Integer[] _ParentBank = new Integer[25];
            
   /**
    * Bank Type member array.
    */
   private String[] _BankType = new String[25];
            
   /**
    * Telex member array.
    */
   private String[] _Telex = new String[25];
            
   /**
    * Fax Country Code member array.
    */
   private String[] _FaxCntry = new String[25];
            
   /**
    * Fax Area Code member array.
    */
   private String[] _FaxArea = new String[25];
            
   /**
    * Fax Number member array.
    */
   private String[] _FaxNumber = new String[25];
            
   /**
    * Phone Cntry Code member array.
    */
   private String[] _PhoneCntry = new String[25];
            
   /**
    * Phone Area Code member array.
    */
   private String[] _PhoneArea = new String[25];
            
   /**
    * Phone Number member array.
    */
   private String[] _PhoneNumber = new String[25];
            
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
    * Address Country member array.
    */
   private String[] _CntryCode = new String[25];
            
   /**
    * City member array.
    */
   private String[] _City = new String[25];
            
   /**
    * Province member array.
    */
   private String[] _Province = new String[25];
            
   /**
    * Inst Role member array.
    */
   private Integer[] _InstRole = new Integer[25];
            
   /**
    * Version member array.
    */
   private Integer[] _BankMstrVer = new Integer[25];
            
   /**
    * Code Page member array.
    */
   private String[] _CodePage = new String[25];
            
   /**
    * Account Number member array.
    */
   private String[] _AcctNumber = new String[25];
            
   /**
    * Currency member array.
    */
   private String[] _Currency = new String[25];
            
   /**
    * Financial Year End member array.
    */
   private Date[] _FinancialYearEnd = new Date[25];
            
   /**
    * Status Code member array.
    */
   private Integer[] _StatusCode = new Integer[25];
            
   /**
    * Inst Category member array.
    */
   private String[] _InstCategory = new String[25];
            
   /**
    * Bank Mstr RecId member array.
    */
   private Integer[] _BankRID = new Integer[25];
            
   /**
    * Transit Code member array.
    */
   private String[] _TransitCode = new String[25];
            

   /**
    * Constructs the BankMstrUpdRequest object.
    * 
    */
   BankMstrUpdRequest()
   {
      super ( 264 );
   }

   /**
    * Constructs the BankMstrUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   BankMstrUpdRequest( String hostEncoding )
   {
      super ( 264, hostEncoding );
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
    * Sets the Bank Id Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Id Number will be set to.
    */
   public final void setBankIdNum( int index, String value )
   {
      assertUnsent();
      _BankIdNum[index] = value;
   }
	
   /**
    * Sets the Swift Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Swift Code will be set to.
    */
   public final void setSwiftCode( int index, Integer value )
   {
      assertUnsent();
      _SwiftCode[index] = value;
   }
	
   /**
    * Sets the Reference Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reference Number will be set to.
    */
   public final void setRefNumber( int index, Integer value )
   {
      assertUnsent();
      _RefNumber[index] = value;
   }
	
   /**
    * Sets the Institution Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Institution Name will be set to.
    */
   public final void setInstName( int index, String value )
   {
      assertUnsent();
      _InstName[index] = value;
   }
	
   /**
    * Sets the Short Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Short Name will be set to.
    */
   public final void setShortName( int index, String value )
   {
      assertUnsent();
      _ShortName[index] = value;
   }
	
   /**
    * Sets the Contact field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contact will be set to.
    */
   public final void setContact( int index, String value )
   {
      assertUnsent();
      _Contact[index] = value;
   }
	
   /**
    * Sets the Parent Bank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Parent Bank will be set to.
    */
   public final void setParentBank( int index, Integer value )
   {
      assertUnsent();
      _ParentBank[index] = value;
   }
	
   /**
    * Sets the Bank Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Type will be set to.
    */
   public final void setBankType( int index, String value )
   {
      assertUnsent();
      _BankType[index] = value;
   }
	
   /**
    * Sets the Telex field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Telex will be set to.
    */
   public final void setTelex( int index, String value )
   {
      assertUnsent();
      _Telex[index] = value;
   }
	
   /**
    * Sets the Fax Country Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fax Country Code will be set to.
    */
   public final void setFaxCntry( int index, String value )
   {
      assertUnsent();
      _FaxCntry[index] = value;
   }
	
   /**
    * Sets the Fax Area Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fax Area Code will be set to.
    */
   public final void setFaxArea( int index, String value )
   {
      assertUnsent();
      _FaxArea[index] = value;
   }
	
   /**
    * Sets the Fax Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fax Number will be set to.
    */
   public final void setFaxNumber( int index, String value )
   {
      assertUnsent();
      _FaxNumber[index] = value;
   }
	
   /**
    * Sets the Phone Cntry Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Phone Cntry Code will be set to.
    */
   public final void setPhoneCntry( int index, String value )
   {
      assertUnsent();
      _PhoneCntry[index] = value;
   }
	
   /**
    * Sets the Phone Area Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Phone Area Code will be set to.
    */
   public final void setPhoneArea( int index, String value )
   {
      assertUnsent();
      _PhoneArea[index] = value;
   }
	
   /**
    * Sets the Phone Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Phone Number will be set to.
    */
   public final void setPhoneNumber( int index, String value )
   {
      assertUnsent();
      _PhoneNumber[index] = value;
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
    * Sets the Address Country field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Country will be set to.
    */
   public final void setCntryCode( int index, String value )
   {
      assertUnsent();
      _CntryCode[index] = value;
   }
	
   /**
    * Sets the City field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the City will be set to.
    */
   public final void setCity( int index, String value )
   {
      assertUnsent();
      _City[index] = value;
   }
	
   /**
    * Sets the Province field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Province will be set to.
    */
   public final void setProvince( int index, String value )
   {
      assertUnsent();
      _Province[index] = value;
   }
	
   /**
    * Sets the Inst Role field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Inst Role will be set to.
    */
   public final void setInstRole( int index, Integer value )
   {
      assertUnsent();
      _InstRole[index] = value;
   }
	
   /**
    * Sets the Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version will be set to.
    */
   public final void setBankMstrVer( int index, Integer value )
   {
      assertUnsent();
      _BankMstrVer[index] = value;
   }
	
   /**
    * Sets the Code Page field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Code Page will be set to.
    */
   public final void setCodePage( int index, String value )
   {
      assertUnsent();
      _CodePage[index] = value;
   }
	
   /**
    * Sets the Account Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAcctNumber( int index, String value )
   {
      assertUnsent();
      _AcctNumber[index] = value;
   }
	
   /**
    * Sets the Currency field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Currency will be set to.
    */
   public final void setCurrency( int index, String value )
   {
      assertUnsent();
      _Currency[index] = value;
   }
	
   /**
    * Sets the Financial Year End field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Financial Year End will be set to.
    */
   public final void setFinancialYearEnd( int index, Date value )
   {
      assertUnsent();
      _FinancialYearEnd[index] = value;
   }
	
   /**
    * Sets the Status Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Status Code will be set to.
    */
   public final void setStatusCode( int index, Integer value )
   {
      assertUnsent();
      _StatusCode[index] = value;
   }
	
   /**
    * Sets the Inst Category field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Inst Category will be set to.
    */
   public final void setInstCategory( int index, String value )
   {
      assertUnsent();
      _InstCategory[index] = value;
   }
	
   /**
    * Sets the Bank Mstr RecId field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Mstr RecId will be set to.
    */
   public final void setBankRID( int index, Integer value )
   {
      assertUnsent();
      _BankRID[index] = value;
   }
	
   /**
    * Sets the Transit Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transit Code will be set to.
    */
   public final void setTransitCode( int index, String value )
   {
      assertUnsent();
      _TransitCode[index] = value;
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
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _BankIdNum[x] );
         requestBuffer.appendField( _SwiftCode[x] );
         requestBuffer.appendField( _RefNumber[x] );
         requestBuffer.appendField( _InstName[x] );
         requestBuffer.appendField( _ShortName[x] );
         requestBuffer.appendField( _Contact[x] );
         requestBuffer.appendField( _ParentBank[x] );
         requestBuffer.appendField( _BankType[x] );
         requestBuffer.appendField( _Telex[x] );
         requestBuffer.appendField( _FaxCntry[x] );
         requestBuffer.appendField( _FaxArea[x] );
         requestBuffer.appendField( _FaxNumber[x] );
         requestBuffer.appendField( _PhoneCntry[x] );
         requestBuffer.appendField( _PhoneArea[x] );
         requestBuffer.appendField( _PhoneNumber[x] );
         requestBuffer.appendField( _AddrLine1[x] );
         requestBuffer.appendField( _AddrLine2[x] );
         requestBuffer.appendField( _AddrLine3[x] );
         requestBuffer.appendField( _AddrLine4[x] );
         requestBuffer.appendField( _AddrLine5[x] );
         requestBuffer.appendField( _PostalCode[x] );
         requestBuffer.appendField( _CntryCode[x] );
         requestBuffer.appendField( _City[x] );
         requestBuffer.appendField( _Province[x] );
         requestBuffer.appendField( _InstRole[x] );
         requestBuffer.appendField( _BankMstrVer[x] );
         requestBuffer.appendField( _CodePage[x] );
         requestBuffer.appendField( _AcctNumber[x] );
         requestBuffer.appendField( _Currency[x] );
         requestBuffer.appendField( _FinancialYearEnd[x] );
         requestBuffer.appendField( _StatusCode[x] );
         requestBuffer.appendField( _InstCategory[x] );
         requestBuffer.appendField( _BankRID[x] );
         requestBuffer.appendField( _TransitCode[x] );
      }
   }

}

