// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * SEG Contract Maturity Instruction Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/SEGConMatInstMaint.doc">SEGConMatInstMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class SEGConMatInstMaintRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Cot-Acct-Contract recid member variable.
    */
   private Integer _CotAcctRid = null;
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Instruction ID member array.
    */
   private String[] _InstId = new String[25];
            
   /**
    * Account ID member array.
    */
   private String[] _AcctID = new String[25];
            
   /**
    * SEGMATINSTDETAILUUID member array.
    */
   private String[] _SEGMATINSTDETAILUUID = new String[25];
            
   /**
    * Redemption Code member array.
    */
   private String[] _RedCode = new String[25];
            
   /**
    * Address Code member array.
    */
   private String[] _Adcd = new String[25];
            
   /**
    * Pay Type member array.
    */
   private String[] _PayType = new String[25];
            
   /**
    * Percentage/Dollar member array.
    */
   private String[] _PUD = new String[25];
            
   /**
    * Instruction Percentage member array.
    */
   private String[] _Amount = new String[25];
            
   /**
    * Source of Fund member array.
    */
   private String[] _SourceOfFund = new String[25];
            
   /**
    * Institution Name member array.
    */
   private String[] _InstName = new String[25];
            
   /**
    * Swift Code member array.
    */
   private Integer[] _SwiftCode = new Integer[25];
            
   /**
    * Reference Number member array.
    */
   private Integer[] _RefNumber = new Integer[25];
            
   /**
    * Transit Number member array.
    */
   private Integer[] _TransitNo = new Integer[25];
            
   /**
    * Bank ID Number member array.
    */
   private Integer[] _BankIDNum = new Integer[25];
            
   /**
    * BankID	Bank ID member array.
    */
   private String[] _BankID = new String[25];
            
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNum = new String[25];
            
   /**
    * Bank Account Name member array.
    */
   private String[] _BankAcctName = new String[25];
            
   /**
    * Bank Account Type member array.
    */
   private String[] _BankAcctType = new String[25];
            
   /**
    * Bank Account Type Desc member array.
    */
   private String[] _BankAcctTypeDesc = new String[25];
            
   /**
    * Bank Account Currency member array.
    */
   private String[] _BankAcctCurr = new String[25];
            
   /**
    * Bank Account Currency Description member array.
    */
   private String[] _BankAcctCurrDesc = new String[25];
            
   /**
    * Bank Address 1 member array.
    */
   private String[] _BankAddr1 = new String[25];
            
   /**
    * Bank Address 2 member array.
    */
   private String[] _BankAddr2 = new String[25];
            
   /**
    * Bank Address 3 member array.
    */
   private String[] _BankAddr3 = new String[25];
            
   /**
    * Bank Address 4 member array.
    */
   private String[] _BankAddr4 = new String[25];
            
   /**
    * Bank Address 5 member array.
    */
   private String[] _BankAddr5 = new String[25];
            
   /**
    * Bank Contract member array.
    */
   private String[] _BankContact = new String[25];
            
   /**
    * Bank Country member array.
    */
   private String[] _BankCntry = new String[25];
            
   /**
    * Bank Postal Code member array.
    */
   private String[] _BankPstl = new String[25];
            
   /**
    * Bank Type member array.
    */
   private String[] _BankType = new String[25];
            
   /**
    * Pay Reason 1 member array.
    */
   private String[] _PayReason1 = new String[25];
            
   /**
    * Pay Reason 2 member array.
    */
   private String[] _PayReason2 = new String[25];
            
   /**
    * ACH Processor member array.
    */
   private String[] _ACHProcessor = new String[25];
            
   /**
    * Correspondent Bank Type member array.
    */
   private String[] _CorrespBankType = new String[25];
            
   /**
    * Correspondent Bank ID Num member array.
    */
   private String[] _CorrespBankIDNum = new String[25];
            
   /**
    * Credit Info Line 1 member array.
    */
   private String[] _CreditInfoLine1 = new String[25];
            
   /**
    * Credit Info Line 2 member array.
    */
   private String[] _CreditInfoLine2 = new String[25];
            
   /**
    * Correspondent Bank ID member array.
    */
   private String[] _CorrespBankId = new String[25];
            
   /**
    * Correspondent Transit Number member array.
    */
   private Integer[] _CorrespTransitNo = new Integer[25];
            
   /**
    * Correspondent Institution Name member array.
    */
   private String[] _CorrespInstName = new String[25];
            
   /**
    * Correspondent Bank Contract member array.
    */
   private String[] _CorrespBankContact = new String[25];
            
   /**
    * Corresponded Bank Country member array.
    */
   private String[] _CorrespBankCntry = new String[25];
            
   /**
    * Corresponded Bank Postal Code member array.
    */
   private String[] _CorrespBankPstl = new String[25];
            
   /**
    * Correspondent  Bank Address 1 member array.
    */
   private String[] _CorrespBankAddr1 = new String[25];
            
   /**
    * Correspondent  Bank Address 2 member array.
    */
   private String[] _CorrespBankAddr2 = new String[25];
            
   /**
    * Correspondent  Bank Address 3 member array.
    */
   private String[] _CorrespBankAddr3 = new String[25];
            
   /**
    * Correspondent  Bank Address 4 member array.
    */
   private String[] _CorrespBankAddr4 = new String[25];
            
   /**
    * Correspondent  Bank Address 5 member array.
    */
   private String[] _CorrespBankAddr5 = new String[25];
            
   /**
    * Bank Account Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Bank Account Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Bank Account record version number member array.
    */
   private Integer[] _BankAcctVer = new Integer[25];
            
   /**
    * Account Use Code member array.
    */
   private String[] _AcctUseCode = new String[25];
            

   /**
    * Constructs the SEGConMatInstMaintRequest object.
    * 
    */
   SEGConMatInstMaintRequest()
   {
      super ( 431 );
   }

   /**
    * Constructs the SEGConMatInstMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   SEGConMatInstMaintRequest( String hostEncoding )
   {
      super ( 431, hostEncoding );
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
    * Sets the Cot-Acct-Contract recid field for the request.
    * 
    * @param value  Value that the Cot-Acct-Contract recid will be set to.
    */
   public final void setCotAcctRid( Integer value )
   {
      assertUnsent();
      _CotAcctRid = value;
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
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Instruction ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Instruction ID will be set to.
    */
   public final void setInstId( int index, String value )
   {
      assertUnsent();
      _InstId[index] = value;
   }
	
   /**
    * Sets the Account ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account ID will be set to.
    */
   public final void setAcctID( int index, String value )
   {
      assertUnsent();
      _AcctID[index] = value;
   }
	
   /**
    * Sets the SEGMATINSTDETAILUUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SEGMATINSTDETAILUUID will be set to.
    */
   public final void setSEGMATINSTDETAILUUID( int index, String value )
   {
      assertUnsent();
      _SEGMATINSTDETAILUUID[index] = value;
   }
	
   /**
    * Sets the Redemption Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Redemption Code will be set to.
    */
   public final void setRedCode( int index, String value )
   {
      assertUnsent();
      _RedCode[index] = value;
   }
	
   /**
    * Sets the Address Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Code will be set to.
    */
   public final void setAdcd( int index, String value )
   {
      assertUnsent();
      _Adcd[index] = value;
   }
	
   /**
    * Sets the Pay Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Type will be set to.
    */
   public final void setPayType( int index, String value )
   {
      assertUnsent();
      _PayType[index] = value;
   }
	
   /**
    * Sets the Percentage/Dollar field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Percentage/Dollar will be set to.
    */
   public final void setPUD( int index, String value )
   {
      assertUnsent();
      _PUD[index] = value;
   }
	
   /**
    * Sets the Instruction Percentage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Instruction Percentage will be set to.
    */
   public final void setAmount( int index, String value )
   {
      assertUnsent();
      _Amount[index] = value;
   }
	
   /**
    * Sets the Source of Fund field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Source of Fund will be set to.
    */
   public final void setSourceOfFund( int index, String value )
   {
      assertUnsent();
      _SourceOfFund[index] = value;
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
    * Sets the Transit Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transit Number will be set to.
    */
   public final void setTransitNo( int index, Integer value )
   {
      assertUnsent();
      _TransitNo[index] = value;
   }
	
   /**
    * Sets the Bank ID Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank ID Number will be set to.
    */
   public final void setBankIDNum( int index, Integer value )
   {
      assertUnsent();
      _BankIDNum[index] = value;
   }
	
   /**
    * Sets the BankID	Bank ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankID	Bank ID will be set to.
    */
   public final void setBankID( int index, String value )
   {
      assertUnsent();
      _BankID[index] = value;
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
    * Sets the Bank Account Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Account Name will be set to.
    */
   public final void setBankAcctName( int index, String value )
   {
      assertUnsent();
      _BankAcctName[index] = value;
   }
	
   /**
    * Sets the Bank Account Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Account Type will be set to.
    */
   public final void setBankAcctType( int index, String value )
   {
      assertUnsent();
      _BankAcctType[index] = value;
   }
	
   /**
    * Sets the Bank Account Type Desc field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Account Type Desc will be set to.
    */
   public final void setBankAcctTypeDesc( int index, String value )
   {
      assertUnsent();
      _BankAcctTypeDesc[index] = value;
   }
	
   /**
    * Sets the Bank Account Currency field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Account Currency will be set to.
    */
   public final void setBankAcctCurr( int index, String value )
   {
      assertUnsent();
      _BankAcctCurr[index] = value;
   }
	
   /**
    * Sets the Bank Account Currency Description field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Account Currency Description will be set to.
    */
   public final void setBankAcctCurrDesc( int index, String value )
   {
      assertUnsent();
      _BankAcctCurrDesc[index] = value;
   }
	
   /**
    * Sets the Bank Address 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Address 1 will be set to.
    */
   public final void setBankAddr1( int index, String value )
   {
      assertUnsent();
      _BankAddr1[index] = value;
   }
	
   /**
    * Sets the Bank Address 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Address 2 will be set to.
    */
   public final void setBankAddr2( int index, String value )
   {
      assertUnsent();
      _BankAddr2[index] = value;
   }
	
   /**
    * Sets the Bank Address 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Address 3 will be set to.
    */
   public final void setBankAddr3( int index, String value )
   {
      assertUnsent();
      _BankAddr3[index] = value;
   }
	
   /**
    * Sets the Bank Address 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Address 4 will be set to.
    */
   public final void setBankAddr4( int index, String value )
   {
      assertUnsent();
      _BankAddr4[index] = value;
   }
	
   /**
    * Sets the Bank Address 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Address 5 will be set to.
    */
   public final void setBankAddr5( int index, String value )
   {
      assertUnsent();
      _BankAddr5[index] = value;
   }
	
   /**
    * Sets the Bank Contract field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Contract will be set to.
    */
   public final void setBankContact( int index, String value )
   {
      assertUnsent();
      _BankContact[index] = value;
   }
	
   /**
    * Sets the Bank Country field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Country will be set to.
    */
   public final void setBankCntry( int index, String value )
   {
      assertUnsent();
      _BankCntry[index] = value;
   }
	
   /**
    * Sets the Bank Postal Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Postal Code will be set to.
    */
   public final void setBankPstl( int index, String value )
   {
      assertUnsent();
      _BankPstl[index] = value;
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
    * Sets the Pay Reason 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Reason 1 will be set to.
    */
   public final void setPayReason1( int index, String value )
   {
      assertUnsent();
      _PayReason1[index] = value;
   }
	
   /**
    * Sets the Pay Reason 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Reason 2 will be set to.
    */
   public final void setPayReason2( int index, String value )
   {
      assertUnsent();
      _PayReason2[index] = value;
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
    * Sets the Correspondent Bank Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent Bank Type will be set to.
    */
   public final void setCorrespBankType( int index, String value )
   {
      assertUnsent();
      _CorrespBankType[index] = value;
   }
	
   /**
    * Sets the Correspondent Bank ID Num field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent Bank ID Num will be set to.
    */
   public final void setCorrespBankIDNum( int index, String value )
   {
      assertUnsent();
      _CorrespBankIDNum[index] = value;
   }
	
   /**
    * Sets the Credit Info Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Credit Info Line 1 will be set to.
    */
   public final void setCreditInfoLine1( int index, String value )
   {
      assertUnsent();
      _CreditInfoLine1[index] = value;
   }
	
   /**
    * Sets the Credit Info Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Credit Info Line 2 will be set to.
    */
   public final void setCreditInfoLine2( int index, String value )
   {
      assertUnsent();
      _CreditInfoLine2[index] = value;
   }
	
   /**
    * Sets the Correspondent Bank ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent Bank ID will be set to.
    */
   public final void setCorrespBankId( int index, String value )
   {
      assertUnsent();
      _CorrespBankId[index] = value;
   }
	
   /**
    * Sets the Correspondent Transit Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent Transit Number will be set to.
    */
   public final void setCorrespTransitNo( int index, Integer value )
   {
      assertUnsent();
      _CorrespTransitNo[index] = value;
   }
	
   /**
    * Sets the Correspondent Institution Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent Institution Name will be set to.
    */
   public final void setCorrespInstName( int index, String value )
   {
      assertUnsent();
      _CorrespInstName[index] = value;
   }
	
   /**
    * Sets the Correspondent Bank Contract field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent Bank Contract will be set to.
    */
   public final void setCorrespBankContact( int index, String value )
   {
      assertUnsent();
      _CorrespBankContact[index] = value;
   }
	
   /**
    * Sets the Corresponded Bank Country field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Corresponded Bank Country will be set to.
    */
   public final void setCorrespBankCntry( int index, String value )
   {
      assertUnsent();
      _CorrespBankCntry[index] = value;
   }
	
   /**
    * Sets the Corresponded Bank Postal Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Corresponded Bank Postal Code will be set to.
    */
   public final void setCorrespBankPstl( int index, String value )
   {
      assertUnsent();
      _CorrespBankPstl[index] = value;
   }
	
   /**
    * Sets the Correspondent  Bank Address 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent  Bank Address 1 will be set to.
    */
   public final void setCorrespBankAddr1( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr1[index] = value;
   }
	
   /**
    * Sets the Correspondent  Bank Address 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent  Bank Address 2 will be set to.
    */
   public final void setCorrespBankAddr2( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr2[index] = value;
   }
	
   /**
    * Sets the Correspondent  Bank Address 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent  Bank Address 3 will be set to.
    */
   public final void setCorrespBankAddr3( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr3[index] = value;
   }
	
   /**
    * Sets the Correspondent  Bank Address 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent  Bank Address 4 will be set to.
    */
   public final void setCorrespBankAddr4( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr4[index] = value;
   }
	
   /**
    * Sets the Correspondent  Bank Address 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent  Bank Address 5 will be set to.
    */
   public final void setCorrespBankAddr5( int index, String value )
   {
      assertUnsent();
      _CorrespBankAddr5[index] = value;
   }
	
   /**
    * Sets the Bank Account Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Account Effective Date will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
   }
	
   /**
    * Sets the Bank Account Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Account Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Bank Account record version number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Account record version number will be set to.
    */
   public final void setBankAcctVer( int index, Integer value )
   {
      assertUnsent();
      _BankAcctVer[index] = value;
   }
	
   /**
    * Sets the Account Use Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Use Code will be set to.
    */
   public final void setAcctUseCode( int index, String value )
   {
      assertUnsent();
      _AcctUseCode[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _CotAcctRid );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _InstId[x] );
         requestBuffer.appendField( _AcctID[x] );
         requestBuffer.appendField( _SEGMATINSTDETAILUUID[x] );
         requestBuffer.appendField( _RedCode[x] );
         requestBuffer.appendField( _Adcd[x] );
         requestBuffer.appendField( _PayType[x] );
         requestBuffer.appendField( _PUD[x] );
         requestBuffer.appendField( _Amount[x] );
         requestBuffer.appendField( _SourceOfFund[x] );
         requestBuffer.appendField( _InstName[x] );
         requestBuffer.appendField( _SwiftCode[x] );
         requestBuffer.appendField( _RefNumber[x] );
         requestBuffer.appendField( _TransitNo[x] );
         requestBuffer.appendField( _BankIDNum[x] );
         requestBuffer.appendField( _BankID[x] );
         requestBuffer.appendField( _BankAcctNum[x] );
         requestBuffer.appendField( _BankAcctName[x] );
         requestBuffer.appendField( _BankAcctType[x] );
         requestBuffer.appendField( _BankAcctTypeDesc[x] );
         requestBuffer.appendField( _BankAcctCurr[x] );
         requestBuffer.appendField( _BankAcctCurrDesc[x] );
         requestBuffer.appendField( _BankAddr1[x] );
         requestBuffer.appendField( _BankAddr2[x] );
         requestBuffer.appendField( _BankAddr3[x] );
         requestBuffer.appendField( _BankAddr4[x] );
         requestBuffer.appendField( _BankAddr5[x] );
         requestBuffer.appendField( _BankContact[x] );
         requestBuffer.appendField( _BankCntry[x] );
         requestBuffer.appendField( _BankPstl[x] );
         requestBuffer.appendField( _BankType[x] );
         requestBuffer.appendField( _PayReason1[x] );
         requestBuffer.appendField( _PayReason2[x] );
         requestBuffer.appendField( _ACHProcessor[x] );
         requestBuffer.appendField( _CorrespBankType[x] );
         requestBuffer.appendField( _CorrespBankIDNum[x] );
         requestBuffer.appendField( _CreditInfoLine1[x] );
         requestBuffer.appendField( _CreditInfoLine2[x] );
         requestBuffer.appendField( _CorrespBankId[x] );
         requestBuffer.appendField( _CorrespTransitNo[x] );
         requestBuffer.appendField( _CorrespInstName[x] );
         requestBuffer.appendField( _CorrespBankContact[x] );
         requestBuffer.appendField( _CorrespBankCntry[x] );
         requestBuffer.appendField( _CorrespBankPstl[x] );
         requestBuffer.appendField( _CorrespBankAddr1[x] );
         requestBuffer.appendField( _CorrespBankAddr2[x] );
         requestBuffer.appendField( _CorrespBankAddr3[x] );
         requestBuffer.appendField( _CorrespBankAddr4[x] );
         requestBuffer.appendField( _CorrespBankAddr5[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _BankAcctVer[x] );
         requestBuffer.appendField( _AcctUseCode[x] );
      }
   }

}

