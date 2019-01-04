// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Update Distribution Instructions request.
 * For additional view information see <A HREF="../../../../viewspecs/DistInstrUpd.doc">DistInstrUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class DistInstrUpdRequest extends IFastRequest implements Serializable
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
    * AWD Business Area member variable.
    */
   private String _AWDBusinessArea = "";
            
   /**
    * AWD Work Type member variable.
    */
   private String _AWDWorkType = "";
            
   /**
    * AWD Object Key member variable.
    */
   private String _AWDObjectKey = "";
            
   /**
    * AWD Obj Date Time member variable.
    */
   private String _AWDObjDateTime = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[150];
            
   /**
    * Institution Code member array.
    */
   private Integer[] _InstCode = new Integer[150];
            
   /**
    * Swift Code member array.
    */
   private Integer[] _SwiftCode = new Integer[150];
            
   /**
    * Reference Number member array.
    */
   private Integer[] _RefNumber = new Integer[150];
            
   /**
    * Transit Code member array.
    */
   private String[] _TransitCode = new String[150];
            
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNum = new String[150];
            
   /**
    * Payment Type member array.
    */
   private String[] _PayType = new String[150];
            
   /**
    * Bank Account Type member array.
    */
   private String[] _BankAcctType = new String[150];
            
   /**
    * Currency member array.
    */
   private String[] _BankAcctCurrency = new String[150];
            
   /**
    * Pay Reason1 member array.
    */
   private String[] _PayReason1 = new String[150];
            
   /**
    * User Created record member array.
    */
   private String[] _Username = new String[150];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[150];
            
   /**
    * Date Created member array.
    */
   private Date[] _ProcessDate = new Date[150];
            
   /**
    * Distrib Detail Version Number member array.
    */
   private Integer[] _DistribDetlVer = new Integer[150];
            
   /**
    * Distrib Detail RECID member array.
    */
   private Integer[] _DistribDetlRid = new Integer[150];
            
   /**
    * Fund with Distribution Instruction member array.
    */
   private String[] _FundCode = new String[150];
            
   /**
    * Class from Code member array.
    */
   private String[] _ClassCode = new String[150];
            
   /**
    * Fund to Code member array.
    */
   private String[] _FundToCode = new String[150];
            
   /**
    * Class to Code member array.
    */
   private String[] _ClassToCode = new String[150];
            
   /**
    * Percent of Allocation that applies for Fund member array.
    */
   private String[] _AllocPercent = new String[150];
            
   /**
    * Bank-Detl version number member array.
    */
   private Integer[] _BankDetlVer = new Integer[150];
            
   /**
    * Bank-Detl record Id member array.
    */
   private Integer[] _BankDetlRid = new Integer[150];
            
   /**
    * Bank Acct Name member array.
    */
   private String[] _BankAcctName = new String[150];
            
   /**
    * Field linking Bank-Acct with Bank-Mstr member array.
    */
   private Integer[] _CorrespBankId = new Integer[150];
            
   /**
    * Bank type code member array.
    */
   private String[] _BankType = new String[150];
            
   /**
    * Correspondent Bank type code member array.
    */
   private String[] _CorrespBankType = new String[150];
            
   /**
    * Bank ID number for corresponding bank member array.
    */
   private String[] _CorrespBankIDNum = new String[150];
            
   /**
    * For further credit instruction l member array.
    */
   private String[] _CreditInfoLine1 = new String[150];
            
   /**
    * For further credit instruction 2 member array.
    */
   private String[] _CreditInfoLine2 = new String[150];
            
   /**
    * Code to define processing location member array.
    */
   private String[] _ACHProcessor = new String[150];
            
   /**
    * Bank contact person member array.
    */
   private String[] _CorrespBankContact = new String[150];
            
   /**
    * Bank address country code member array.
    */
   private String[] _CorrespBankCntry = new String[150];
            
   /**
    * Bank address pstl code member array.
    */
   private String[] _CorrespBankPstl = new String[150];
            
   /**
    * Corresp Bank Addr line 1 member array.
    */
   private String[] _CorrespBankAddr1 = new String[150];
            
   /**
    * Corresp Bank Addr line 2 member array.
    */
   private String[] _CorrespBankAddr2 = new String[150];
            
   /**
    * Corresp Bank Addr line 3 member array.
    */
   private String[] _CorrespBankAddr3 = new String[150];
            
   /**
    * Corresp Bank Addr line 4 member array.
    */
   private String[] _CorrespBankAddr4 = new String[150];
            
   /**
    * Corresp Bank Addr line 5 member array.
    */
   private String[] _CorrespBankAddr5 = new String[150];
            
   /**
    * Bank contact person member array.
    */
   private String[] _BankContact = new String[150];
            
   /**
    * Bank address country code member array.
    */
   private String[] _BankCntry = new String[150];
            
   /**
    * Bank address pstl code member array.
    */
   private String[] _BankPstl = new String[150];
            
   /**
    * Transit Number of the correspondent bank member array.
    */
   private Integer[] _CorrespTransitNo = new Integer[150];
            
   /**
    * Correspondent Bank Name member array.
    */
   private String[] _CorrespInstName = new String[150];
            
   /**
    * Bank Id Number member array.
    */
   private String[] _BankIdNum = new String[150];
            
   /**
    * Link between Bank-Acct and Bank-Mstr member array.
    */
   private Integer[] _BankId = new Integer[150];
            
   /**
    * Bank Addr Line 1 member array.
    */
   private String[] _BankAddr1 = new String[150];
            
   /**
    * Bank Addr Line 2 member array.
    */
   private String[] _BankAddr2 = new String[150];
            
   /**
    * Bank Addr Line 3 member array.
    */
   private String[] _BankAddr3 = new String[150];
            
   /**
    * Bank Addr Line 4 member array.
    */
   private String[] _BankAddr4 = new String[150];
            
   /**
    * Bank Addr Line 5 member array.
    */
   private String[] _BankAddr5 = new String[150];
            
   /**
    * Inst Name member array.
    */
   private String[] _InstName = new String[150];
            
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = new String[150];
            
   /**
    * Transaction Type member array.
    */
   private String[] _TransType = new String[150];
            
   /**
    * Pay Method member array.
    */
   private String[] _PayMethod = new String[150];
            
   /**
    * Pay Reason 2 member array.
    */
   private String[] _PayReason2 = new String[150];
            
   /**
    * Distribution Option member array.
    */
   private String[] _DistribOpt = new String[150];
            
   /**
    * Currency Option member array.
    */
   private String[] _CurrOption = new String[150];
            
   /**
    * Verify Status member array.
    */
   private String[] _VerifyStat = new String[150];
            
   /**
    * Flag indicates if one of distrib record is deleted from allocation member array.
    */
   private Boolean[] _DelDistribAlloc = new Boolean[150];
            
   /**
    * Distribution Rate member array.
    */
   private String[] _DistribRate = new String[150];
            

   /**
    * Constructs the DistInstrUpdRequest object.
    * 
    */
   DistInstrUpdRequest()
   {
      super ( 96 );
   }

   /**
    * Constructs the DistInstrUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DistInstrUpdRequest( String hostEncoding )
   {
      super ( 96, hostEncoding );
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
    * Sets the AWD Business Area field for the request.
    * 
    * @param value  Value that the AWD Business Area will be set to.
    */
   public final void setAWDBusinessArea( String value )
   {
      assertUnsent();
      _AWDBusinessArea = value;
   }
	
   /**
    * Sets the AWD Work Type field for the request.
    * 
    * @param value  Value that the AWD Work Type will be set to.
    */
   public final void setAWDWorkType( String value )
   {
      assertUnsent();
      _AWDWorkType = value;
   }
	
   /**
    * Sets the AWD Object Key field for the request.
    * 
    * @param value  Value that the AWD Object Key will be set to.
    */
   public final void setAWDObjectKey( String value )
   {
      assertUnsent();
      _AWDObjectKey = value;
   }
	
   /**
    * Sets the AWD Obj Date Time field for the request.
    * 
    * @param value  Value that the AWD Obj Date Time will be set to.
    */
   public final void setAWDObjDateTime( String value )
   {
      assertUnsent();
      _AWDObjDateTime = value;
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
    * Sets the Institution Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Institution Code will be set to.
    */
   public final void setInstCode( int index, Integer value )
   {
      assertUnsent();
      _InstCode[index] = value;
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
    * Sets the Pay Reason1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay Reason1 will be set to.
    */
   public final void setPayReason1( int index, String value )
   {
      assertUnsent();
      _PayReason1[index] = value;
   }
	
   /**
    * Sets the User Created record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the User Created record will be set to.
    */
   public final void setUsername( int index, String value )
   {
      assertUnsent();
      _Username[index] = value;
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
    * Sets the Date Created field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Date Created will be set to.
    */
   public final void setProcessDate( int index, Date value )
   {
      assertUnsent();
      _ProcessDate[index] = value;
   }
	
   /**
    * Sets the Distrib Detail Version Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distrib Detail Version Number will be set to.
    */
   public final void setDistribDetlVer( int index, Integer value )
   {
      assertUnsent();
      _DistribDetlVer[index] = value;
   }
	
   /**
    * Sets the Distrib Detail RECID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distrib Detail RECID will be set to.
    */
   public final void setDistribDetlRid( int index, Integer value )
   {
      assertUnsent();
      _DistribDetlRid[index] = value;
   }
	
   /**
    * Sets the Fund with Distribution Instruction field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund with Distribution Instruction will be set to.
    */
   public final void setFundCode( int index, String value )
   {
      assertUnsent();
      _FundCode[index] = value;
   }
	
   /**
    * Sets the Class from Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Class from Code will be set to.
    */
   public final void setClassCode( int index, String value )
   {
      assertUnsent();
      _ClassCode[index] = value;
   }
	
   /**
    * Sets the Fund to Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund to Code will be set to.
    */
   public final void setFundToCode( int index, String value )
   {
      assertUnsent();
      _FundToCode[index] = value;
   }
	
   /**
    * Sets the Class to Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Class to Code will be set to.
    */
   public final void setClassToCode( int index, String value )
   {
      assertUnsent();
      _ClassToCode[index] = value;
   }
	
   /**
    * Sets the Percent of Allocation that applies for Fund field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Percent of Allocation that applies for Fund will be set to.
    */
   public final void setAllocPercent( int index, String value )
   {
      assertUnsent();
      _AllocPercent[index] = value;
   }
	
   /**
    * Sets the Bank-Detl version number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank-Detl version number will be set to.
    */
   public final void setBankDetlVer( int index, Integer value )
   {
      assertUnsent();
      _BankDetlVer[index] = value;
   }
	
   /**
    * Sets the Bank-Detl record Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank-Detl record Id will be set to.
    */
   public final void setBankDetlRid( int index, Integer value )
   {
      assertUnsent();
      _BankDetlRid[index] = value;
   }
	
   /**
    * Sets the Bank Acct Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Acct Name will be set to.
    */
   public final void setBankAcctName( int index, String value )
   {
      assertUnsent();
      _BankAcctName[index] = value;
   }
	
   /**
    * Sets the Field linking Bank-Acct with Bank-Mstr field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Field linking Bank-Acct with Bank-Mstr will be set to.
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
    * Sets the Correspondent Bank type code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent Bank type code will be set to.
    */
   public final void setCorrespBankType( int index, String value )
   {
      assertUnsent();
      _CorrespBankType[index] = value;
   }
	
   /**
    * Sets the Bank ID number for corresponding bank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank ID number for corresponding bank will be set to.
    */
   public final void setCorrespBankIDNum( int index, String value )
   {
      assertUnsent();
      _CorrespBankIDNum[index] = value;
   }
	
   /**
    * Sets the For further credit instruction l field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the For further credit instruction l will be set to.
    */
   public final void setCreditInfoLine1( int index, String value )
   {
      assertUnsent();
      _CreditInfoLine1[index] = value;
   }
	
   /**
    * Sets the For further credit instruction 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the For further credit instruction 2 will be set to.
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
    * Sets the Bank address pstl code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank address pstl code will be set to.
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
    * Sets the Bank address pstl code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank address pstl code will be set to.
    */
   public final void setBankPstl( int index, String value )
   {
      assertUnsent();
      _BankPstl[index] = value;
   }
	
   /**
    * Sets the Transit Number of the correspondent bank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transit Number of the correspondent bank will be set to.
    */
   public final void setCorrespTransitNo( int index, Integer value )
   {
      assertUnsent();
      _CorrespTransitNo[index] = value;
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
    * Sets the Link between Bank-Acct and Bank-Mstr field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Link between Bank-Acct and Bank-Mstr will be set to.
    */
   public final void setBankId( int index, Integer value )
   {
      assertUnsent();
      _BankId[index] = value;
   }
	
   /**
    * Sets the Bank Addr Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr Line 1 will be set to.
    */
   public final void setBankAddr1( int index, String value )
   {
      assertUnsent();
      _BankAddr1[index] = value;
   }
	
   /**
    * Sets the Bank Addr Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr Line 2 will be set to.
    */
   public final void setBankAddr2( int index, String value )
   {
      assertUnsent();
      _BankAddr2[index] = value;
   }
	
   /**
    * Sets the Bank Addr Line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr Line 3 will be set to.
    */
   public final void setBankAddr3( int index, String value )
   {
      assertUnsent();
      _BankAddr3[index] = value;
   }
	
   /**
    * Sets the Bank Addr Line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr Line 4 will be set to.
    */
   public final void setBankAddr4( int index, String value )
   {
      assertUnsent();
      _BankAddr4[index] = value;
   }
	
   /**
    * Sets the Bank Addr Line 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr Line 5 will be set to.
    */
   public final void setBankAddr5( int index, String value )
   {
      assertUnsent();
      _BankAddr5[index] = value;
   }
	
   /**
    * Sets the Inst Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Inst Name will be set to.
    */
   public final void setInstName( int index, String value )
   {
      assertUnsent();
      _InstName[index] = value;
   }
	
   /**
    * Sets the Address Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Code will be set to.
    */
   public final void setAddrCode( int index, String value )
   {
      assertUnsent();
      _AddrCode[index] = value;
   }
	
   /**
    * Sets the Transaction Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setTransType( int index, String value )
   {
      assertUnsent();
      _TransType[index] = value;
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
    * Sets the Distribution Option field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distribution Option will be set to.
    */
   public final void setDistribOpt( int index, String value )
   {
      assertUnsent();
      _DistribOpt[index] = value;
   }
	
   /**
    * Sets the Currency Option field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Currency Option will be set to.
    */
   public final void setCurrOption( int index, String value )
   {
      assertUnsent();
      _CurrOption[index] = value;
   }
	
   /**
    * Sets the Verify Status field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Verify Status will be set to.
    */
   public final void setVerifyStat( int index, String value )
   {
      assertUnsent();
      _VerifyStat[index] = value;
   }
	
   /**
    * Sets the Flag indicates if one of distrib record is deleted from allocation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Flag indicates if one of distrib record is deleted from allocation will be set to.
    */
   public final void setDelDistribAlloc( int index, Boolean value )
   {
      assertUnsent();
      _DelDistribAlloc[index] = value;
   }
	
   /**
    * Sets the Distribution Rate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distribution Rate will be set to.
    */
   public final void setDistribRate( int index, String value )
   {
      assertUnsent();
      _DistribRate[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AWDBusinessArea );
      requestBuffer.appendField( _AWDWorkType );
      requestBuffer.appendField( _AWDObjectKey );
      requestBuffer.appendField( _AWDObjDateTime );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _InstCode[x] );
         requestBuffer.appendField( _SwiftCode[x] );
         requestBuffer.appendField( _RefNumber[x] );
         requestBuffer.appendField( _TransitCode[x] );
         requestBuffer.appendField( _BankAcctNum[x] );
         requestBuffer.appendField( _PayType[x] );
         requestBuffer.appendField( _BankAcctType[x] );
         requestBuffer.appendField( _BankAcctCurrency[x] );
         requestBuffer.appendField( _PayReason1[x] );
         requestBuffer.appendField( _Username[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _ProcessDate[x] );
         requestBuffer.appendField( _DistribDetlVer[x] );
         requestBuffer.appendField( _DistribDetlRid[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
         requestBuffer.appendField( _FundToCode[x] );
         requestBuffer.appendField( _ClassToCode[x] );
         requestBuffer.appendField( _AllocPercent[x] );
         requestBuffer.appendField( _BankDetlVer[x] );
         requestBuffer.appendField( _BankDetlRid[x] );
         requestBuffer.appendField( _BankAcctName[x] );
         requestBuffer.appendField( _CorrespBankId[x] );
         requestBuffer.appendField( _BankType[x] );
         requestBuffer.appendField( _CorrespBankType[x] );
         requestBuffer.appendField( _CorrespBankIDNum[x] );
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
         requestBuffer.appendField( _BankContact[x] );
         requestBuffer.appendField( _BankCntry[x] );
         requestBuffer.appendField( _BankPstl[x] );
         requestBuffer.appendField( _CorrespTransitNo[x] );
         requestBuffer.appendField( _CorrespInstName[x] );
         requestBuffer.appendField( _BankIdNum[x] );
         requestBuffer.appendField( _BankId[x] );
         requestBuffer.appendField( _BankAddr1[x] );
         requestBuffer.appendField( _BankAddr2[x] );
         requestBuffer.appendField( _BankAddr3[x] );
         requestBuffer.appendField( _BankAddr4[x] );
         requestBuffer.appendField( _BankAddr5[x] );
         requestBuffer.appendField( _InstName[x] );
         requestBuffer.appendField( _AddrCode[x] );
         requestBuffer.appendField( _TransType[x] );
         requestBuffer.appendField( _PayMethod[x] );
         requestBuffer.appendField( _PayReason2[x] );
         requestBuffer.appendField( _DistribOpt[x] );
         requestBuffer.appendField( _CurrOption[x] );
         requestBuffer.appendField( _VerifyStat[x] );
         requestBuffer.appendField( _DelDistribAlloc[x] );
         requestBuffer.appendField( _DistribRate[x] );
      }
   }

}

