// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Update Banking Instructions request.
 * For additional view information see <A HREF="../../../../viewspecs/UpdBnkInstr.doc">UpdBnkInstr.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpdBnkInstrRequest extends IFastRequest implements Serializable
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
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
            
            
   /**
    * Type of entity doing banking member variable.
    */
   private String _BankingEntity = "";
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep member variable.
    */
   private String _SlsRep = "";
            
   /**
    * Fund Code member variable.
    */
   private String _FundCode = "";
            
   /**
    * Class Code member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Fund Group member variable.
    */
   private String _FundGroup = "";
            
   /**
    * Fund Sponsor member variable.
    */
   private String _FundSponsor = "";
            
   /**
    * Registration Agent Code member variable.
    */
   private String _RegAgentCode = "";
            
   /**
    * AccountNum member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Swift Code member array.
    */
   private Integer[] _SwiftCode = new Integer[25];
            
   /**
    * Reference Number member array.
    */
   private Integer[] _RefNumber = new Integer[25];
            
   /**
    * Transit Code member array.
    */
   private String[] _TransitCode = new String[25];
            
   /**
    * Bank Account Number member array.
    */
   private String[] _BankAcctNum = new String[25];
            
   /**
    * Bank Account Type member array.
    */
   private String[] _BankAcctType = new String[25];
            
   /**
    * Currency member array.
    */
   private String[] _BankAcctCurrency = new String[25];
            
   /**
    * Pay Reason1 member array.
    */
   private String[] _PayReason1 = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Bank Acct Version Number member array.
    */
   private Integer[] _BankAcctVer = new Integer[25];
            
   /**
    * Bank Acct RECID member array.
    */
   private Integer[] _BankAcctRid = new Integer[25];
            
   /**
    * Account Use Code member array.
    */
   private String[] _AcctUseCode = new String[25];
            
   /**
    * Instituition Name member array.
    */
   private String[] _InstName = new String[25];
            
   /**
    * Pay reason 2 member array.
    */
   private String[] _PayReason2 = new String[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Bank Account Name member array.
    */
   private String[] _BankAcctName = new String[25];
            
   /**
    * Field linking Bank-Acct with Bank-Mstr.  It is a pointer to  Correspondent Bank stored in Bank-Mstr Table member array.
    */
   private Integer[] _CorrespBankId = new Integer[25];
            
   /**
    * Bank type code to include what fields uniquely identify bank member array.
    */
   private String[] _BankType = new String[25];
            
   /**
    * Correspondent BankType code to indicate what fields uniquely identify bank member array.
    */
   private String[] _CorrespBankType = new String[25];
            
   /**
    * Correspondent Bank Name member array.
    */
   private String[] _CorrespInstName = new String[25];
            
   /**
    * Transit Number of the correspondent bank member array.
    */
   private Integer[] _CorrespTransitNo = new Integer[25];
            
   /**
    * Bank ID number for the corresponding Bank member array.
    */
   private String[] _CorrespBankIdNum = new String[25];
            
   /**
    * Credit instruction 1 member array.
    */
   private String[] _CreditInfoLine1 = new String[25];
            
   /**
    * Credit instruction 2 member array.
    */
   private String[] _CreditInfoLine2 = new String[25];
            
   /**
    * Code to define processing location member array.
    */
   private String[] _ACHProcessor = new String[25];
            
   /**
    * Bank Contact Person member array.
    */
   private String[] _CorrespBankContact = new String[25];
            
   /**
    * Bank address country code member array.
    */
   private String[] _CorrespBankCntry = new String[25];
            
   /**
    * Bank address postal code member array.
    */
   private String[] _CorrespBankPstl = new String[25];
            
   /**
    * Corresp Bank Addr line 1 member array.
    */
   private String[] _CorrespBankAddr1 = new String[25];
            
   /**
    * Corresp Bank Addr line 2 member array.
    */
   private String[] _CorrespBankAddr2 = new String[25];
            
   /**
    * Corresp Bank Addr line 3 member array.
    */
   private String[] _CorrespBankAddr3 = new String[25];
            
   /**
    * Corresp Bank Addr line 4 member array.
    */
   private String[] _CorrespBankAddr4 = new String[25];
            
   /**
    * Corresp Bank Addr line 5 member array.
    */
   private String[] _CorrespBankAddr5 = new String[25];
            
   /**
    * Bank Addr line 1 member array.
    */
   private String[] _BankAddr1 = new String[25];
            
   /**
    * Bank Addr line 2 member array.
    */
   private String[] _BankAddr2 = new String[25];
            
   /**
    * Bank Addr line 3 member array.
    */
   private String[] _BankAddr3 = new String[25];
            
   /**
    * Bank Addr line 4 member array.
    */
   private String[] _BankAddr4 = new String[25];
            
   /**
    * Bank Addr line 5 member array.
    */
   private String[] _BankAddr5 = new String[25];
            
   /**
    * Bank Contact Person member array.
    */
   private String[] _BankContact = new String[25];
            
   /**
    * Bank address country code member array.
    */
   private String[] _BankCntry = new String[25];
            
   /**
    * Bank address postal code member array.
    */
   private String[] _BankPstl = new String[25];
            
   /**
    * Bank Id Number member array.
    */
   private String[] _BankIdNum = new String[25];
            
   /**
    * Bank Id member array.
    */
   private Integer[] _BankId = new Integer[25];
            
   /**
    * Indicates if record is verified member array.
    */
   private String[] _VerifyStat = new String[25];
            

   /**
    * Constructs the UpdBnkInstrRequest object.
    * 
    */
   UpdBnkInstrRequest()
   {
      super ( 97 );
   }

   /**
    * Constructs the UpdBnkInstrRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   UpdBnkInstrRequest( String hostEncoding )
   {
      super ( 97, hostEncoding );
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
    * Sets the Type of entity doing banking field for the request.
    * 
    * @param value  Value that the Type of entity doing banking will be set to.
    */
   public final void setBankingEntity( String value )
   {
      assertUnsent();
      _BankingEntity = value;
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
    * Sets the Sales Rep field for the request.
    * 
    * @param value  Value that the Sales Rep will be set to.
    */
   public final void setSlsRep( String value )
   {
      assertUnsent();
      _SlsRep = value;
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
    * Sets the Fund Group field for the request.
    * 
    * @param value  Value that the Fund Group will be set to.
    */
   public final void setFundGroup( String value )
   {
      assertUnsent();
      _FundGroup = value;
   }
	
   /**
    * Sets the Fund Sponsor field for the request.
    * 
    * @param value  Value that the Fund Sponsor will be set to.
    */
   public final void setFundSponsor( String value )
   {
      assertUnsent();
      _FundSponsor = value;
   }
	
   /**
    * Sets the Registration Agent Code field for the request.
    * 
    * @param value  Value that the Registration Agent Code will be set to.
    */
   public final void setRegAgentCode( String value )
   {
      assertUnsent();
      _RegAgentCode = value;
   }
	
   /**
    * Sets the AccountNum field for the request.
    * 
    * @param value  Value that the AccountNum will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
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
    * Sets the Bank Acct Version Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Acct Version Number will be set to.
    */
   public final void setBankAcctVer( int index, Integer value )
   {
      assertUnsent();
      _BankAcctVer[index] = value;
   }
	
   /**
    * Sets the Bank Acct RECID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Acct RECID will be set to.
    */
   public final void setBankAcctRid( int index, Integer value )
   {
      assertUnsent();
      _BankAcctRid[index] = value;
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
    * Sets the Instituition Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Instituition Name will be set to.
    */
   public final void setInstName( int index, String value )
   {
      assertUnsent();
      _InstName[index] = value;
   }
	
   /**
    * Sets the Pay reason 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Pay reason 2 will be set to.
    */
   public final void setPayReason2( int index, String value )
   {
      assertUnsent();
      _PayReason2[index] = value;
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
    * Sets the Field linking Bank-Acct with Bank-Mstr.  It is a pointer to  Correspondent Bank stored in Bank-Mstr Table field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Field linking Bank-Acct with Bank-Mstr.  It is a pointer to  Correspondent Bank stored in Bank-Mstr Table will be set to.
    */
   public final void setCorrespBankId( int index, Integer value )
   {
      assertUnsent();
      _CorrespBankId[index] = value;
   }
	
   /**
    * Sets the Bank type code to include what fields uniquely identify bank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank type code to include what fields uniquely identify bank will be set to.
    */
   public final void setBankType( int index, String value )
   {
      assertUnsent();
      _BankType[index] = value;
   }
	
   /**
    * Sets the Correspondent BankType code to indicate what fields uniquely identify bank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Correspondent BankType code to indicate what fields uniquely identify bank will be set to.
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
    * Sets the Bank ID number for the corresponding Bank field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank ID number for the corresponding Bank will be set to.
    */
   public final void setCorrespBankIdNum( int index, String value )
   {
      assertUnsent();
      _CorrespBankIdNum[index] = value;
   }
	
   /**
    * Sets the Credit instruction 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Credit instruction 1 will be set to.
    */
   public final void setCreditInfoLine1( int index, String value )
   {
      assertUnsent();
      _CreditInfoLine1[index] = value;
   }
	
   /**
    * Sets the Credit instruction 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Credit instruction 2 will be set to.
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
    * Sets the Bank Contact Person field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Contact Person will be set to.
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
    * Sets the Bank Addr line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Addr line 1 will be set to.
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
    * Sets the Bank Contact Person field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Contact Person will be set to.
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
    * Sets the Bank Id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Bank Id will be set to.
    */
   public final void setBankId( int index, Integer value )
   {
      assertUnsent();
      _BankId[index] = value;
   }
	
   /**
    * Sets the Indicates if record is verified field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Indicates if record is verified will be set to.
    */
   public final void setVerifyStat( int index, String value )
   {
      assertUnsent();
      _VerifyStat[index] = value;
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
      requestBuffer.appendField( _ShrNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _BankingEntity );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SlsRep );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _FundGroup );
      requestBuffer.appendField( _FundSponsor );
      requestBuffer.appendField( _RegAgentCode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _SwiftCode[x] );
         requestBuffer.appendField( _RefNumber[x] );
         requestBuffer.appendField( _TransitCode[x] );
         requestBuffer.appendField( _BankAcctNum[x] );
         requestBuffer.appendField( _BankAcctType[x] );
         requestBuffer.appendField( _BankAcctCurrency[x] );
         requestBuffer.appendField( _PayReason1[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _BankAcctVer[x] );
         requestBuffer.appendField( _BankAcctRid[x] );
         requestBuffer.appendField( _AcctUseCode[x] );
         requestBuffer.appendField( _InstName[x] );
         requestBuffer.appendField( _PayReason2[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _BankAcctName[x] );
         requestBuffer.appendField( _CorrespBankId[x] );
         requestBuffer.appendField( _BankType[x] );
         requestBuffer.appendField( _CorrespBankType[x] );
         requestBuffer.appendField( _CorrespInstName[x] );
         requestBuffer.appendField( _CorrespTransitNo[x] );
         requestBuffer.appendField( _CorrespBankIdNum[x] );
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
         requestBuffer.appendField( _BankIdNum[x] );
         requestBuffer.appendField( _BankId[x] );
         requestBuffer.appendField( _VerifyStat[x] );
      }
   }

}

