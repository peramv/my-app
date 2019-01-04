// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Settlements Maintenance - changed records request.
 * For additional view information see <A HREF="../../../../viewspecs/SettlUpd1.doc">SettlUpd1.doc</A>.
 * 
 * @author RTS Generated
 */
public class SettlUpd1Request extends IFastRequest implements Serializable
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
    * Record Id of Transaction record member array.
    */
   private Integer[] _TransDetlRId = new Integer[50];
            
   /**
    * Transaction ID member array.
    */
   private String[] _TransId = new String[50];
            
   /**
    * Volume Settlement Type member array.
    */
   private String[] _rxVolSettleType = new String[50];
            
   /**
    * Address code member array.
    */
   private String[] _AddrCode = new String[50];
            
   /**
    * Payment Type member array.
    */
   private String[] _PayType = new String[50];
            
   /**
    * Payee Name 1 member array.
    */
   private String[] _Name1 = new String[50];
            
   /**
    * Payee Name 2 member array.
    */
   private String[] _Name2 = new String[50];
            
   /**
    * Payee address line 1 member array.
    */
   private String[] _AddrLine1 = new String[50];
            
   /**
    * Payee address line 2 member array.
    */
   private String[] _AddrLine2 = new String[50];
            
   /**
    * Payee address line 3 member array.
    */
   private String[] _AddrLine3 = new String[50];
            
   /**
    * Payee address line 4 member array.
    */
   private String[] _AddrLine4 = new String[50];
            
   /**
    * Payee address line 5 member array.
    */
   private String[] _AddrLine5 = new String[50];
            
   /**
    * Payee Postal Code member array.
    */
   private String[] _PostalCode = new String[50];
            
   /**
    * Payee Country Code member array.
    */
   private String[] _CountryCode = new String[50];
            
   /**
    * Institution Name member array.
    */
   private String[] _InstName = new String[50];
            
   /**
    * Swift Code member array.
    */
   private Integer[] _SwiftCode = new Integer[50];
            
   /**
    * Reference Code member array.
    */
   private Integer[] _RefNumber = new Integer[50];
            
   /**
    * Transit Code member array.
    */
   private String[] _TransitCode = new String[50];
            
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNum = new String[50];
            
   /**
    * Bank Accountholder Name member array.
    */
   private String[] _BankAcctName = new String[50];
            
   /**
    * Account Type member array.
    */
   private String[] _BankAcctType = new String[50];
            
   /**
    * Currency member array.
    */
   private String[] _BankAcctCurrency = new String[50];
            
   /**
    * Pay Reason Line 1 member array.
    */
   private String[] _PayReason1 = new String[50];
            
   /**
    * Pay Reason Line 2 member array.
    */
   private String[] _PayReason2 = new String[50];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[50];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[50];
            
   /**
    * Link b/w Bank-Acct and Bank-Mstr member array.
    */
   private Integer[] _CorrespBankId = new Integer[50];
            
   /**
    * Bank type code member array.
    */
   private String[] _BankType = new String[50];
            
   /**
    * Correspondent bank type code member array.
    */
   private String[] _CorrespBankType = new String[50];
            
   /**
    * Correspondent Bank Name member array.
    */
   private String[] _CorrespInstName = new String[50];
            
   /**
    * Transit Number of correspondent bank member array.
    */
   private Integer[] _CorrespTransitNo = new Integer[50];
            
   /**
    * Bank ID number member array.
    */
   private String[] _BankIdNum = new String[50];
            
   /**
    * Bank Id number of respondent bank member array.
    */
   private String[] _CorespBankIdNum = new String[50];
            
   /**
    * Futher credit instruction 1 member array.
    */
   private String[] _CreditInfoLine1 = new String[50];
            
   /**
    * Further credit instruction 2 member array.
    */
   private String[] _CreditInfoLine2 = new String[50];
            
   /**
    * Code to define processing location member array.
    */
   private String[] _ACHProcessor = new String[50];
            
   /**
    * Bank contact person member array.
    */
   private String[] _CorrespBankContact = new String[50];
            
   /**
    * Bank address country code member array.
    */
   private String[] _CorrespBankCntry = new String[50];
            
   /**
    * Bank address postal code member array.
    */
   private String[] _CorrespBankPstl = new String[50];
            
   /**
    * Corresp Bank Addr line 1 member array.
    */
   private String[] _CorrespBankAddr1 = new String[50];
            
   /**
    * Corresp Bank Addr line 2 member array.
    */
   private String[] _CorrespBankAddr2 = new String[50];
            
   /**
    * Corresp Bank Addr line 3 member array.
    */
   private String[] _CorrespBankAddr3 = new String[50];
            
   /**
    * Corresp Bank Addr line 4 member array.
    */
   private String[] _CorrespBankAddr4 = new String[50];
            
   /**
    * Corresp Bank Addr line 5 member array.
    */
   private String[] _CorrespBankAddr5 = new String[50];
            
   /**
    * Bank Addr line1 member array.
    */
   private String[] _BankAddr1 = new String[50];
            
   /**
    * Bank Addr line 2 member array.
    */
   private String[] _BankAddr2 = new String[50];
            
   /**
    * Bank Addr line 3 member array.
    */
   private String[] _BankAddr3 = new String[50];
            
   /**
    * Bank Addr line 4 member array.
    */
   private String[] _BankAddr4 = new String[50];
            
   /**
    * Bank Addr line 5 member array.
    */
   private String[] _BankAddr5 = new String[50];
            
   /**
    * Bank contact person member array.
    */
   private String[] _BankContact = new String[50];
            
   /**
    * Bank address country code member array.
    */
   private String[] _BankCntry = new String[50];
            
   /**
    * Bank address postal code member array.
    */
   private String[] _BankPstl = new String[50];
            
   /**
    * Link to Bank-Mstr member array.
    */
   private Integer[] _BankId = new Integer[50];
            
   /**
    * Settlement Method member array.
    */
   private Integer[] _SettleMethod = new Integer[50];
            
   /**
    * Pay Method member array.
    */
   private String[] _PayMethod = new String[50];
            
   /**
    * Bank Charge member array.
    */
   private String[] _BankCharge = new String[50];
            
   /**
    * Value Date member array.
    */
   private Date[] _ValueDate = new Date[50];
            
   /**
    * Deposit Id member array.
    */
   private String[] _DepId = new String[50];
            
   /**
    * GNSettle member array.
    */
   private String[] _GNSettle = new String[50];
            
   /**
    * Delivery Method member array.
    */
   private String[] _DeliveryMethod = new String[50];
            
   /**
    * Suppress Code member array.
    */
   private String[] _SuppressCode = new String[50];
            
   /**
    * Stores AcctID of the parent banking info member array.
    */
   private String[] _BnkAcctIDLink = new String[50];
            
   /**
    * Pymt Routing Mthd member array.
    */
   private String[] _PymtRoutingMthd = new String[50];
            

   /**
    * Constructs the SettlUpd1Request object.
    * 
    */
   SettlUpd1Request()
   {
      super ( 201 );
   }

   /**
    * Constructs the SettlUpd1Request object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SettlUpd1Request( String hostEncoding )
   {
      super ( 201, hostEncoding );
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
    * Sets the Record Id of Transaction record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Record Id of Transaction record will be set to.
    */
   public final void setTransDetlRId( int index, Integer value )
   {
      assertUnsent();
      _TransDetlRId[index] = value;
   }
	
   /**
    * Sets the Transaction ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transaction ID will be set to.
    */
   public final void setTransId( int index, String value )
   {
      assertUnsent();
      _TransId[index] = value;
   }
	
   /**
    * Sets the Volume Settlement Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Volume Settlement Type will be set to.
    */
   public final void setrxVolSettleType( int index, String value )
   {
      assertUnsent();
      _rxVolSettleType[index] = value;
   }
	
   /**
    * Sets the Address code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address code will be set to.
    */
   public final void setAddrCode( int index, String value )
   {
      assertUnsent();
      _AddrCode[index] = value;
   }
	
   /**
    * Sets the Payment Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payment Type will be set to.
    */
   public final void setPayType( int index, String value )
   {
      assertUnsent();
      _PayType[index] = value;
   }
	
   /**
    * Sets the Payee Name 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payee Name 1 will be set to.
    */
   public final void setName1( int index, String value )
   {
      assertUnsent();
      _Name1[index] = value;
   }
	
   /**
    * Sets the Payee Name 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payee Name 2 will be set to.
    */
   public final void setName2( int index, String value )
   {
      assertUnsent();
      _Name2[index] = value;
   }
	
   /**
    * Sets the Payee address line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payee address line 1 will be set to.
    */
   public final void setAddrLine1( int index, String value )
   {
      assertUnsent();
      _AddrLine1[index] = value;
   }
	
   /**
    * Sets the Payee address line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payee address line 2 will be set to.
    */
   public final void setAddrLine2( int index, String value )
   {
      assertUnsent();
      _AddrLine2[index] = value;
   }
	
   /**
    * Sets the Payee address line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payee address line 3 will be set to.
    */
   public final void setAddrLine3( int index, String value )
   {
      assertUnsent();
      _AddrLine3[index] = value;
   }
	
   /**
    * Sets the Payee address line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payee address line 4 will be set to.
    */
   public final void setAddrLine4( int index, String value )
   {
      assertUnsent();
      _AddrLine4[index] = value;
   }
	
   /**
    * Sets the Payee address line 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payee address line 5 will be set to.
    */
   public final void setAddrLine5( int index, String value )
   {
      assertUnsent();
      _AddrLine5[index] = value;
   }
	
   /**
    * Sets the Payee Postal Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payee Postal Code will be set to.
    */
   public final void setPostalCode( int index, String value )
   {
      assertUnsent();
      _PostalCode[index] = value;
   }
	
   /**
    * Sets the Payee Country Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Payee Country Code will be set to.
    */
   public final void setCountryCode( int index, String value )
   {
      assertUnsent();
      _CountryCode[index] = value;
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
    * Sets the Reference Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reference Code will be set to.
    */
   public final void setRefNumber( int index, Integer value )
   {
      assertUnsent();
      _RefNumber[index] = value;
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
    * Sets the Bank Account Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Account Number will be set to.
    */
   public final void setBankAcctNum( int index, String value )
   {
      assertUnsent();
      _BankAcctNum[index] = value;
   }
	
   /**
    * Sets the Bank Accountholder Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Accountholder Name will be set to.
    */
   public final void setBankAcctName( int index, String value )
   {
      assertUnsent();
      _BankAcctName[index] = value;
   }
	
   /**
    * Sets the Account Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Type will be set to.
    */
   public final void setBankAcctType( int index, String value )
   {
      assertUnsent();
      _BankAcctType[index] = value;
   }
	
   /**
    * Sets the Currency field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Currency will be set to.
    */
   public final void setBankAcctCurrency( int index, String value )
   {
      assertUnsent();
      _BankAcctCurrency[index] = value;
   }
	
   /**
    * Sets the Pay Reason Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Reason Line 1 will be set to.
    */
   public final void setPayReason1( int index, String value )
   {
      assertUnsent();
      _PayReason1[index] = value;
   }
	
   /**
    * Sets the Pay Reason Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Reason Line 2 will be set to.
    */
   public final void setPayReason2( int index, String value )
   {
      assertUnsent();
      _PayReason2[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
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
    * Sets the Link b/w Bank-Acct and Bank-Mstr field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Link b/w Bank-Acct and Bank-Mstr will be set to.
    */
   public final void setCorrespBankId( int index, Integer value )
   {
      assertUnsent();
      _CorrespBankId[index] = value;
   }
	
   /**
    * Sets the Bank type code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank type code will be set to.
    */
   public final void setBankType( int index, String value )
   {
      assertUnsent();
      _BankType[index] = value;
   }
	
   /**
    * Sets the Correspondent bank type code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent bank type code will be set to.
    */
   public final void setCorrespBankType( int index, String value )
   {
      assertUnsent();
      _CorrespBankType[index] = value;
   }
	
   /**
    * Sets the Correspondent Bank Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent Bank Name will be set to.
    */
   public final void setCorrespInstName( int index, String value )
   {
      assertUnsent();
      _CorrespInstName[index] = value;
   }
	
   /**
    * Sets the Transit Number of correspondent bank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transit Number of correspondent bank will be set to.
    */
   public final void setCorrespTransitNo( int index, Integer value )
   {
      assertUnsent();
      _CorrespTransitNo[index] = value;
   }
	
   /**
    * Sets the Bank ID number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank ID number will be set to.
    */
   public final void setBankIdNum( int index, String value )
   {
      assertUnsent();
      _BankIdNum[index] = value;
   }
	
   /**
    * Sets the Bank Id number of respondent bank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Id number of respondent bank will be set to.
    */
   public final void setCorespBankIdNum( int index, String value )
   {
      assertUnsent();
      _CorespBankIdNum[index] = value;
   }
	
   /**
    * Sets the Futher credit instruction 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Futher credit instruction 1 will be set to.
    */
   public final void setCreditInfoLine1( int index, String value )
   {
      assertUnsent();
      _CreditInfoLine1[index] = value;
   }
	
   /**
    * Sets the Further credit instruction 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Further credit instruction 2 will be set to.
    */
   public final void setCreditInfoLine2( int index, String value )
   {
      assertUnsent();
      _CreditInfoLine2[index] = value;
   }
	
   /**
    * Sets the Code to define processing location field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Code to define processing location will be set to.
    */
   public final void setACHProcessor( int index, String value )
   {
      assertUnsent();
      _ACHProcessor[index] = value;
   }
	
   /**
    * Sets the Bank contact person field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank contact person will be set to.
    */
   public final void setCorrespBankContact( int index, String value )
   {
      assertUnsent();
      _CorrespBankContact[index] = value;
   }
	
   /**
    * Sets the Bank address country code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank address country code will be set to.
    */
   public final void setCorrespBankCntry( int index, String value )
   {
      assertUnsent();
      _CorrespBankCntry[index] = value;
   }
	
   /**
    * Sets the Bank address postal code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank address postal code will be set to.
    */
   public final void setCorrespBankPstl( int index, String value )
   {
      assertUnsent();
      _CorrespBankPstl[index] = value;
   }
	
   /**
    * Sets the Corresp Bank Addr line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Corresp Bank Addr line 1 will be set to.
    */
   public final void setCorrespBankAddr1( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr1[index] = value;
   }
	
   /**
    * Sets the Corresp Bank Addr line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Corresp Bank Addr line 2 will be set to.
    */
   public final void setCorrespBankAddr2( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr2[index] = value;
   }
	
   /**
    * Sets the Corresp Bank Addr line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Corresp Bank Addr line 3 will be set to.
    */
   public final void setCorrespBankAddr3( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr3[index] = value;
   }
	
   /**
    * Sets the Corresp Bank Addr line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Corresp Bank Addr line 4 will be set to.
    */
   public final void setCorrespBankAddr4( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr4[index] = value;
   }
	
   /**
    * Sets the Corresp Bank Addr line 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Corresp Bank Addr line 5 will be set to.
    */
   public final void setCorrespBankAddr5( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr5[index] = value;
   }
	
   /**
    * Sets the Bank Addr line1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr line1 will be set to.
    */
   public final void setBankAddr1( int index, String value )
   {
      assertUnsent();
      _BankAddr1[index] = value;
   }
	
   /**
    * Sets the Bank Addr line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr line 2 will be set to.
    */
   public final void setBankAddr2( int index, String value )
   {
      assertUnsent();
      _BankAddr2[index] = value;
   }
	
   /**
    * Sets the Bank Addr line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr line 3 will be set to.
    */
   public final void setBankAddr3( int index, String value )
   {
      assertUnsent();
      _BankAddr3[index] = value;
   }
	
   /**
    * Sets the Bank Addr line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr line 4 will be set to.
    */
   public final void setBankAddr4( int index, String value )
   {
      assertUnsent();
      _BankAddr4[index] = value;
   }
	
   /**
    * Sets the Bank Addr line 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr line 5 will be set to.
    */
   public final void setBankAddr5( int index, String value )
   {
      assertUnsent();
      _BankAddr5[index] = value;
   }
	
   /**
    * Sets the Bank contact person field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank contact person will be set to.
    */
   public final void setBankContact( int index, String value )
   {
      assertUnsent();
      _BankContact[index] = value;
   }
	
   /**
    * Sets the Bank address country code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank address country code will be set to.
    */
   public final void setBankCntry( int index, String value )
   {
      assertUnsent();
      _BankCntry[index] = value;
   }
	
   /**
    * Sets the Bank address postal code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank address postal code will be set to.
    */
   public final void setBankPstl( int index, String value )
   {
      assertUnsent();
      _BankPstl[index] = value;
   }
	
   /**
    * Sets the Link to Bank-Mstr field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Link to Bank-Mstr will be set to.
    */
   public final void setBankId( int index, Integer value )
   {
      assertUnsent();
      _BankId[index] = value;
   }
	
   /**
    * Sets the Settlement Method field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Settlement Method will be set to.
    */
   public final void setSettleMethod( int index, Integer value )
   {
      assertUnsent();
      _SettleMethod[index] = value;
   }
	
   /**
    * Sets the Pay Method field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Method will be set to.
    */
   public final void setPayMethod( int index, String value )
   {
      assertUnsent();
      _PayMethod[index] = value;
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
    * Sets the Value Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Value Date will be set to.
    */
   public final void setValueDate( int index, Date value )
   {
      assertUnsent();
      _ValueDate[index] = value;
   }
	
   /**
    * Sets the Deposit Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Deposit Id will be set to.
    */
   public final void setDepId( int index, String value )
   {
      assertUnsent();
      _DepId[index] = value;
   }
	
   /**
    * Sets the GNSettle field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the GNSettle will be set to.
    */
   public final void setGNSettle( int index, String value )
   {
      assertUnsent();
      _GNSettle[index] = value;
   }
	
   /**
    * Sets the Delivery Method field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Delivery Method will be set to.
    */
   public final void setDeliveryMethod( int index, String value )
   {
      assertUnsent();
      _DeliveryMethod[index] = value;
   }
	
   /**
    * Sets the Suppress Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Suppress Code will be set to.
    */
   public final void setSuppressCode( int index, String value )
   {
      assertUnsent();
      _SuppressCode[index] = value;
   }
	
   /**
    * Sets the Stores AcctID of the parent banking info field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stores AcctID of the parent banking info will be set to.
    */
   public final void setBnkAcctIDLink( int index, String value )
   {
      assertUnsent();
      _BnkAcctIDLink[index] = value;
   }
	
   /**
    * Sets the Pymt Routing Mthd field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pymt Routing Mthd will be set to.
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
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _TransDetlRId[x] );
         requestBuffer.appendField( _TransId[x] );
         requestBuffer.appendField( _rxVolSettleType[x] );
         requestBuffer.appendField( _AddrCode[x] );
         requestBuffer.appendField( _PayType[x] );
         requestBuffer.appendField( _Name1[x] );
         requestBuffer.appendField( _Name2[x] );
         requestBuffer.appendField( _AddrLine1[x] );
         requestBuffer.appendField( _AddrLine2[x] );
         requestBuffer.appendField( _AddrLine3[x] );
         requestBuffer.appendField( _AddrLine4[x] );
         requestBuffer.appendField( _AddrLine5[x] );
         requestBuffer.appendField( _PostalCode[x] );
         requestBuffer.appendField( _CountryCode[x] );
         requestBuffer.appendField( _InstName[x] );
         requestBuffer.appendField( _SwiftCode[x] );
         requestBuffer.appendField( _RefNumber[x] );
         requestBuffer.appendField( _TransitCode[x] );
         requestBuffer.appendField( _BankAcctNum[x] );
         requestBuffer.appendField( _BankAcctName[x] );
         requestBuffer.appendField( _BankAcctType[x] );
         requestBuffer.appendField( _BankAcctCurrency[x] );
         requestBuffer.appendField( _PayReason1[x] );
         requestBuffer.appendField( _PayReason2[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _CorrespBankId[x] );
         requestBuffer.appendField( _BankType[x] );
         requestBuffer.appendField( _CorrespBankType[x] );
         requestBuffer.appendField( _CorrespInstName[x] );
         requestBuffer.appendField( _CorrespTransitNo[x] );
         requestBuffer.appendField( _BankIdNum[x] );
         requestBuffer.appendField( _CorespBankIdNum[x] );
         requestBuffer.appendField( _CreditInfoLine1[x] );
         requestBuffer.appendField( _CreditInfoLine2[x] );
         requestBuffer.appendField( _ACHProcessor[x] );
         requestBuffer.appendField( _CorrespBankContact[x] );
         requestBuffer.appendField( _CorrespBankCntry[x] );
         requestBuffer.appendField( _CorrespBankPstl[x] );
         requestBuffer.appendField( _CorrespBankAddr1[x] );
         requestBuffer.appendField( _CorrespBankAddr2[x] );
         requestBuffer.appendField( _CorrespBankAddr3[x] );
         requestBuffer.appendField( _CorrespBankAddr4[x] );
         requestBuffer.appendField( _CorrespBankAddr5[x] );
         requestBuffer.appendField( _BankAddr1[x] );
         requestBuffer.appendField( _BankAddr2[x] );
         requestBuffer.appendField( _BankAddr3[x] );
         requestBuffer.appendField( _BankAddr4[x] );
         requestBuffer.appendField( _BankAddr5[x] );
         requestBuffer.appendField( _BankContact[x] );
         requestBuffer.appendField( _BankCntry[x] );
         requestBuffer.appendField( _BankPstl[x] );
         requestBuffer.appendField( _BankId[x] );
         requestBuffer.appendField( _SettleMethod[x] );
         requestBuffer.appendField( _PayMethod[x] );
         requestBuffer.appendField( _BankCharge[x] );
         requestBuffer.appendField( _ValueDate[x] );
         requestBuffer.appendField( _DepId[x] );
         requestBuffer.appendField( _GNSettle[x] );
         requestBuffer.appendField( _DeliveryMethod[x] );
         requestBuffer.appendField( _SuppressCode[x] );
         requestBuffer.appendField( _BnkAcctIDLink[x] );
         requestBuffer.appendField( _PymtRoutingMthd[x] );
      }
   }

}

