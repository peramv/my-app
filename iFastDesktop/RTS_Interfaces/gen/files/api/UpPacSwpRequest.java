// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account PAC/SWP/AT Details/Alloc Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/UpPacSwp.doc">UpPacSwp.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpPacSwpRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
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
   private String _CompanyID = "";
            
   /**
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Transaction Type member variable.
    */
   private String _TransType = "";
            
   /**
    * PAC/SWP Record ID member variable.
    */
   private Integer _PacSwpId = null;
            
   /**
    * Broker Code (PAC/SWP) member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code (PAC/SWP) member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep Code (PAC/SWP) member variable.
    */
   private String _SalesRepCode = "";
            
   /**
    * Amount member variable.
    */
   private String _Amount = "0";
            
   /**
    * Amount Type Code member variable.
    */
   private String _AmountType = "";
            
   /**
    * Amount Gross or Net (PAC/SWP) member variable.
    */
   private Boolean _GrossOrNet = new Boolean(false);
            
   /**
    * Flat Fee Amount or Percent member variable.
    */
   private String _Fee = "0";
            
   /**
    * Fee is Flat (yes) or  Percent (no) member variable.
    */
   private Boolean _FlatPercent = new Boolean(false);
            
   /**
    * Fee Currency (PAC/SWP) member variable.
    */
   private String _FeeCurrency = "";
            
   /**
    * Administration Fee (PAC/SWP) member variable.
    */
   private String _AdminFeeAmt = "0";
            
   /**
    * Admin Fee Currency (PAC/SWP) member variable.
    */
   private String _AdminFeeCurr = "";
            
   /**
    * Payment Type Code (PAC/SWP) member variable.
    */
   private String _LastBankType = "";
            
   /**
    * Institution Code to debit (PAC/SWP) member variable.
    */
   private String _BankIdNum = "";
            
   /**
    * Swift Code (PAC/SWP) member variable.
    */
   private Integer _SwiftCode = null;
            
   /**
    * Reference Number (PAC/SWP) member variable.
    */
   private Integer _RefNumber = null;
            
   /**
    * Transit Number (PAC/SWP) member variable.
    */
   private String _TransitCode = "";
            
   /**
    * Bank Account Number (PAC/SWP) member variable.
    */
   private String _BankAcctNum = "";
            
   /**
    * Bank Account Name (PAC/SWP) member variable.
    */
   private String _BankAcctName = "";
            
   /**
    * Source of Bank Account (PAC/SWP) member variable.
    */
   private String _SourceOfBankAcct = "";
            
   /**
    * Bank Account Currency (PAC/SWP) member variable.
    */
   private String _BankAcctCurrency = "";
            
   /**
    * Bank Account Type (PAC/SWP) member variable.
    */
   private String _BankAcctType = "";
            
   /**
    * Source of Fund (PAC/SWP) member variable.
    */
   private String _SrcOfFund = "";
            
   /**
    * January member variable.
    */
   private Boolean _January = new Boolean(false);
            
   /**
    * February member variable.
    */
   private Boolean _February = new Boolean(false);
            
   /**
    * March member variable.
    */
   private Boolean _March = new Boolean(false);
            
   /**
    * April member variable.
    */
   private Boolean _April = new Boolean(false);
            
   /**
    * May member variable.
    */
   private Boolean _May = new Boolean(false);
            
   /**
    * June member variable.
    */
   private Boolean _June = new Boolean(false);
            
   /**
    * July member variable.
    */
   private Boolean _July = new Boolean(false);
            
   /**
    * August member variable.
    */
   private Boolean _August = new Boolean(false);
            
   /**
    * September member variable.
    */
   private Boolean _September = new Boolean(false);
            
   /**
    * October member variable.
    */
   private Boolean _October = new Boolean(false);
            
   /**
    * November member variable.
    */
   private Boolean _November = new Boolean(false);
            
   /**
    * December member variable.
    */
   private Boolean _December = new Boolean(false);
            
   /**
    * Occurs at end of month member variable.
    */
   private Boolean _EndOfMonth = new Boolean(false);
            
   /**
    * Day of Week PAC occurs on member variable.
    */
   private Integer _DayOfWeek = null;
            
   /**
    * Address Code (SWP) member variable.
    */
   private String _AddrCode = "";
            
   /**
    * Record Active member variable.
    */
   private Boolean _GoodBad = new Boolean(false);
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Stop Date member variable.
    */
   private Date _StopDate = null;
            
   /**
    * FundCode member variable.
    */
   private String _FundCode = "";
            
   /**
    * ClassCode member variable.
    */
   private String _ClassCode = "";
            
   /**
    * Set As Default member variable.
    */
   private Boolean _SetAsDefault = new Boolean(false);
            
   /**
    * Version of Bank-Detl or Recur-Detail member variable.
    */
   private Integer _VersionNum = null;
            
   /**
    * Initial Factor (Clan Plan) member variable.
    */
   private String _InitFactor = "0";
            
   /**
    * Plan Term (Clan Plan) member variable.
    */
   private Integer _PlanTerm = null;
            
   /**
    * Payment Amount (Clan Plan) member variable.
    */
   private String _PaymentAmt = "0";
            
   /**
    * Last Payment (Clan Plan) member variable.
    */
   private Integer _LastPayment = null;
            
   /**
    * Commission (Clan Plan) member variable.
    */
   private String _Commission = "0";
            
   /**
    * Admin Fee Amount (Clan Plan) member variable.
    */
   private String _AdminFeeAmtClan = "0";
            
   /**
    * Transfer To Account (AT) member variable.
    */
   private String _AccountTo = "0";
            
   /**
    * Transfer To Fund (AT) member variable.
    */
   private String _FundToCode = "";
            
   /**
    * Transfer To Class (AT) member variable.
    */
   private String _ClassToCode = "";
            
   /**
    * Back End Load Fee Applicable(AT) member variable.
    */
   private Boolean _BELFee = new Boolean(false);
            
   /**
    * Frequency Code member variable.
    */
   private String _Frequency = "";
            
   /**
    * Transfer Type (AT) member variable.
    */
   private String _TransferType = "";
            
   /**
    * Payment Reason 1 member variable.
    */
   private String _PayReason1 = "";
            
   /**
    * Entity Type member variable.
    */
   private String _Entitytype = "";
            
   /**
    * Entity Type Sequence member variable.
    */
   private Integer _EntityTypeSeq = null;
            
   /**
    * Batch Name member variable.
    */
   private String _BatchName = "";
            
            
            
   /**
    * Bank type code member variable.
    */
   private String _BankType = "";
            
   /**
    * Code to define processing location member variable.
    */
   private String _ACHProcessor = "";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Bank Id member variable.
    */
   private Integer _BankId = null;
            
   /**
    * Pay Type member variable.
    */
   private String _PayType = "";
            
   /**
    * Accept Default Split Commission member variable.
    */
   private Boolean _AutoSplitComm = new Boolean(false);
            
   /**
    * Credit Info Line 1 member variable.
    */
   private String _CreditInfoLine1 = "";
            
   /**
    * Credit Info Line 2 member variable.
    */
   private String _CreditInfoLine2 = "";
            
   /**
    * Bank Address Line 1 member variable.
    */
   private String _BankAddr1 = "";
            
   /**
    * Bank Address Line 2 member variable.
    */
   private String _BankAddr2 = "";
            
   /**
    * Bank Address Line 3 member variable.
    */
   private String _BankAddr3 = "";
            
   /**
    * Bank Address Line 4 member variable.
    */
   private String _BankAddr4 = "";
            
   /**
    * Bank Address Line 5 member variable.
    */
   private String _BankAddr5 = "";
            
   /**
    * Bank Contact Person member variable.
    */
   private String _BankContact = "";
            
   /**
    * Bank Address Country Code member variable.
    */
   private String _BankCntry = "";
            
   /**
    * Bank Address Postal Code member variable.
    */
   private String _BankPstl = "";
            
   /**
    * Bank Name member variable.
    */
   private String _InstName = "";
            
   /**
    * Saving Plan fee type member variable.
    */
   private String _VUBPayOption = "";
            
   /**
    * Saving Plan Code member variable.
    */
   private String _PlanCode = "";
            
   /**
    * Fee on In side of Exchange member variable.
    */
   private String _ExchInFee = "0";
            
   /**
    * Fee on In side of Exchnage is Flat(yes) Percentage(no) member variable.
    */
   private Boolean _ExchInFlatPercent = new Boolean(false);
            
   /**
    * Annual maintenance fee date member variable.
    */
   private Date _AnnualFeeDate = null;
            
   /**
    * Annual Fee  charged? member variable.
    */
   private Boolean _AnnualFee = new Boolean(false);
            
   /**
    * Initial Amount member variable.
    */
   private String _InitialAmt = "0";
            
   /**
    * VUB Expected Amount member variable.
    */
   private String _VUBExpectedAmt = "0";
            
   /**
    * Exchange Out Fee member variable.
    */
   private String _ExchOutFee = "0";
            
   /**
    * Exchange Out Flat/ Prcnt member variable.
    */
   private Boolean _ExchOutFlatPrcnt = new Boolean(false);
            
   /**
    * Payment Method member variable.
    */
   private String _PayMethod = "";
            
   /**
    * Override Federal Tax PUD member variable.
    */
   private String _FedTaxPUDOverride = "";
            
   /**
    * Federal Rate member variable.
    */
   private String _FedRate = "0";
            
   /**
    * Override Provisional Tax PUD member variable.
    */
   private String _ProvTaxPUDOverride = "";
            
   /**
    * Provisional Rate member variable.
    */
   private String _ProvRate = "0";
            
   /**
    * Pay Reason 2 member variable.
    */
   private String _PayReason2 = "";
            
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
    * Verify Status member variable.
    */
   private String _VerifyStat = "";
            
   /**
    * Stop Reason member variable.
    */
   private String _StopReason = "";
            
   /**
    * Non Financial Confirm member variable.
    */
   private String _NonFinConfirm = "";
            
   /**
    * RDR Advice member variable.
    */
   private String _RDRAdvice = "";
            
   /**
    * Event Receipt Date member variable.
    */
   private Date _EventReceiptDate = null;
            
   /**
    * Event Receipt Time member variable.
    */
   private String _EventReceiptTime = "";
            
   /**
    * SourceOfTrade member variable.
    */
   private String _SourceOfTrade = "";
            
   /**
    * ChannelOfTrade member variable.
    */
   private String _ChannelOfTrade = "";
            
   /**
    * Platform member variable.
    */
   private String _Platform = "";
            
   /**
    * PSDAdvice member variable.
    */
   private String _PSDAdvice = "";
            
   /**
    * SignatureDate member variable.
    */
   private Date _SignatureDate = null;
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Allocation Run Mode - fund record member array.
    */
   private String[] _FundLvlRunMode = new String[25];
            
   /**
    * Allocation Fund To Code member array.
    */
   private String[] _AllocFundToCode = new String[25];
            
   /**
    * Allocation Class To Code member array.
    */
   private String[] _AllocClassToCode = new String[25];
            
   /**
    * Allocation Percentage member array.
    */
   private String[] _AllocPercentage = new String[25];
            
   /**
    * Allocation Amount member array.
    */
   private String[] _AllocAmount = new String[25];
            
   /**
    * Distrib-Detl Recid for fund record member array.
    */
   private Integer[] _DistribFundLvlRId = new Integer[25];
            
   /**
    * Allocation Level (AT) member array.
    */
   private Integer[] _Level = new Integer[25];
            
   /**
    * Allocation Account To (AT) member array.
    */
   private String[] _AllocAccountNum = new String[25];
            
   /**
    * Transaction Sequence member array.
    */
   private Integer[] _TransSeq = new Integer[25];
            
   /**
    * RunMode for Commisions member array.
    */
   private String[] _CommRunMode = new String[25];
            
   /**
    * Commission PayType member array.
    */
   private String[] _CommPayType = new String[25];
            
   /**
    * Commission - fixed or not member array.
    */
   private Boolean[] _CommFixed = new Boolean[25];
            
   /**
    * Commission - Gross or Net member array.
    */
   private Boolean[] _CommGrossNet = new Boolean[25];
            
   /**
    * Commission Percent member array.
    */
   private String[] _CommPrcnt = new String[25];
            
   /**
    * Commission - Broker Code member array.
    */
   private String[] _CommBrokCode = new String[25];
            
   /**
    * Commission - Branch Code member array.
    */
   private String[] _CommBranCode = new String[25];
            
   /**
    * Commission - Sls Rep Code member array.
    */
   private String[] _CommRepCode = new String[25];
            
   /**
    * Commision Level member array.
    */
   private Integer[] _CommLevel = new Integer[25];
            
   /**
    * Commission Rate member array.
    */
   private String[] _CommRate = new String[25];
            
   /**
    * Renunciation Amount member array.
    */
   private String[] _RenunAmount = new String[25];
            
   /**
    * Repeating session Record Type member array.
    */
   private String[] _RecType = new String[25];
            
   /**
    * Index Run Mode member array.
    */
   private String[] _IndexRunMode = new String[25];
            
   /**
    * Index Amount member array.
    */
   private String[] _IndexAmt = new String[25];
            
   /**
    * Index Type member array.
    */
   private String[] _IndexType = new String[25];
            
   /**
    * Index Frequency member array.
    */
   private String[] _IndexFrequency = new String[25];
            
   /**
    * Effective date of Indexing Record member array.
    */
   private Date[] _StartDate = new Date[25];
            
   /**
    * End date for Indexing Record member array.
    */
   private Date[] _EndDate = new Date[25];
            
   /**
    * PAC-Index record id member array.
    */
   private Integer[] _PACIndexRId = new Integer[25];
            
   /**
    * PAC-Index record version number member array.
    */
   private Integer[] _PACIndexVer = new Integer[25];
            
   /**
    * Percentage allocated to the account member array.
    */
   private String[] _AcctPrcnt = new String[25];
            
   /**
    * Distrib-Detl version for acct alloc member array.
    */
   private Integer[] _DistribAcctLvlVer = new Integer[25];
            
   /**
    * Distrib-Detl rec id for Acct alloc record member array.
    */
   private Integer[] _DistribAcctLvlRId = new Integer[25];
            
   /**
    * Acct level run mode member array.
    */
   private String[] _AcctLvlRunMode = new String[25];
            
   /**
    * Acct level allocated amount member array.
    */
   private String[] _AcctLvlAmount = new String[25];
            
   /**
    * Distrib-Detl record version for fund level rec member array.
    */
   private Integer[] _DistribFundLvlVer = new Integer[25];
            
   /**
    * Next Index Date member array.
    */
   private Date[] _NextIndexDate = new Date[25];
            
   /**
    * Split Commission Recid member array.
    */
   private Integer[] _SplitCommRid = new Integer[25];
            

   /**
    * Constructs the UpPacSwpRequest object.
    * 
    */
   UpPacSwpRequest()
   {
      super ( 84 );
   }

   /**
    * Constructs the UpPacSwpRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   UpPacSwpRequest( String hostEncoding )
   {
      super ( 84, hostEncoding );
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
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
    * Sets the Transaction Type field for the request.
    * 
    * @param value  Value that the Transaction Type will be set to.
    */
   public final void setTransType( String value )
   {
      assertUnsent();
      _TransType = value;
   }
	
   /**
    * Sets the PAC/SWP Record ID field for the request.
    * 
    * @param value  Value that the PAC/SWP Record ID will be set to.
    */
   public final void setPacSwpId( Integer value )
   {
      assertUnsent();
      _PacSwpId = value;
   }
	
   /**
    * Sets the Broker Code (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Broker Code (PAC/SWP) will be set to.
    */
   public final void setBrokerCode( String value )
   {
      assertUnsent();
      _BrokerCode = value;
   }
	
   /**
    * Sets the Branch Code (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Branch Code (PAC/SWP) will be set to.
    */
   public final void setBranchCode( String value )
   {
      assertUnsent();
      _BranchCode = value;
   }
	
   /**
    * Sets the Sales Rep Code (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Sales Rep Code (PAC/SWP) will be set to.
    */
   public final void setSalesRepCode( String value )
   {
      assertUnsent();
      _SalesRepCode = value;
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
    * Sets the Amount Type Code field for the request.
    * 
    * @param value  Value that the Amount Type Code will be set to.
    */
   public final void setAmountType( String value )
   {
      assertUnsent();
      _AmountType = value;
   }
	
   /**
    * Sets the Amount Gross or Net (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Amount Gross or Net (PAC/SWP) will be set to.
    */
   public final void setGrossOrNet( Boolean value )
   {
      assertUnsent();
      _GrossOrNet = value;
   }
	
   /**
    * Sets the Flat Fee Amount or Percent field for the request.
    * 
    * @param value  Value that the Flat Fee Amount or Percent will be set to.
    */
   public final void setFee( String value )
   {
      assertUnsent();
      _Fee = value;
   }
	
   /**
    * Sets the Fee is Flat (yes) or  Percent (no) field for the request.
    * 
    * @param value  Value that the Fee is Flat (yes) or  Percent (no) will be set to.
    */
   public final void setFlatPercent( Boolean value )
   {
      assertUnsent();
      _FlatPercent = value;
   }
	
   /**
    * Sets the Fee Currency (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Fee Currency (PAC/SWP) will be set to.
    */
   public final void setFeeCurrency( String value )
   {
      assertUnsent();
      _FeeCurrency = value;
   }
	
   /**
    * Sets the Administration Fee (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Administration Fee (PAC/SWP) will be set to.
    */
   public final void setAdminFeeAmt( String value )
   {
      assertUnsent();
      _AdminFeeAmt = value;
   }
	
   /**
    * Sets the Admin Fee Currency (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Admin Fee Currency (PAC/SWP) will be set to.
    */
   public final void setAdminFeeCurr( String value )
   {
      assertUnsent();
      _AdminFeeCurr = value;
   }
	
   /**
    * Sets the Payment Type Code (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Payment Type Code (PAC/SWP) will be set to.
    */
   public final void setLastBankType( String value )
   {
      assertUnsent();
      _LastBankType = value;
   }
	
   /**
    * Sets the Institution Code to debit (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Institution Code to debit (PAC/SWP) will be set to.
    */
   public final void setBankIdNum( String value )
   {
      assertUnsent();
      _BankIdNum = value;
   }
	
   /**
    * Sets the Swift Code (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Swift Code (PAC/SWP) will be set to.
    */
   public final void setSwiftCode( Integer value )
   {
      assertUnsent();
      _SwiftCode = value;
   }
	
   /**
    * Sets the Reference Number (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Reference Number (PAC/SWP) will be set to.
    */
   public final void setRefNumber( Integer value )
   {
      assertUnsent();
      _RefNumber = value;
   }
	
   /**
    * Sets the Transit Number (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Transit Number (PAC/SWP) will be set to.
    */
   public final void setTransitCode( String value )
   {
      assertUnsent();
      _TransitCode = value;
   }
	
   /**
    * Sets the Bank Account Number (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Bank Account Number (PAC/SWP) will be set to.
    */
   public final void setBankAcctNum( String value )
   {
      assertUnsent();
      _BankAcctNum = value;
   }
	
   /**
    * Sets the Bank Account Name (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Bank Account Name (PAC/SWP) will be set to.
    */
   public final void setBankAcctName( String value )
   {
      assertUnsent();
      _BankAcctName = value;
   }
	
   /**
    * Sets the Source of Bank Account (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Source of Bank Account (PAC/SWP) will be set to.
    */
   public final void setSourceOfBankAcct( String value )
   {
      assertUnsent();
      _SourceOfBankAcct = value;
   }
	
   /**
    * Sets the Bank Account Currency (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Bank Account Currency (PAC/SWP) will be set to.
    */
   public final void setBankAcctCurrency( String value )
   {
      assertUnsent();
      _BankAcctCurrency = value;
   }
	
   /**
    * Sets the Bank Account Type (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Bank Account Type (PAC/SWP) will be set to.
    */
   public final void setBankAcctType( String value )
   {
      assertUnsent();
      _BankAcctType = value;
   }
	
   /**
    * Sets the Source of Fund (PAC/SWP) field for the request.
    * 
    * @param value  Value that the Source of Fund (PAC/SWP) will be set to.
    */
   public final void setSrcOfFund( String value )
   {
      assertUnsent();
      _SrcOfFund = value;
   }
	
   /**
    * Sets the January field for the request.
    * 
    * @param value  Value that the January will be set to.
    */
   public final void setJanuary( Boolean value )
   {
      assertUnsent();
      _January = value;
   }
	
   /**
    * Sets the February field for the request.
    * 
    * @param value  Value that the February will be set to.
    */
   public final void setFebruary( Boolean value )
   {
      assertUnsent();
      _February = value;
   }
	
   /**
    * Sets the March field for the request.
    * 
    * @param value  Value that the March will be set to.
    */
   public final void setMarch( Boolean value )
   {
      assertUnsent();
      _March = value;
   }
	
   /**
    * Sets the April field for the request.
    * 
    * @param value  Value that the April will be set to.
    */
   public final void setApril( Boolean value )
   {
      assertUnsent();
      _April = value;
   }
	
   /**
    * Sets the May field for the request.
    * 
    * @param value  Value that the May will be set to.
    */
   public final void setMay( Boolean value )
   {
      assertUnsent();
      _May = value;
   }
	
   /**
    * Sets the June field for the request.
    * 
    * @param value  Value that the June will be set to.
    */
   public final void setJune( Boolean value )
   {
      assertUnsent();
      _June = value;
   }
	
   /**
    * Sets the July field for the request.
    * 
    * @param value  Value that the July will be set to.
    */
   public final void setJuly( Boolean value )
   {
      assertUnsent();
      _July = value;
   }
	
   /**
    * Sets the August field for the request.
    * 
    * @param value  Value that the August will be set to.
    */
   public final void setAugust( Boolean value )
   {
      assertUnsent();
      _August = value;
   }
	
   /**
    * Sets the September field for the request.
    * 
    * @param value  Value that the September will be set to.
    */
   public final void setSeptember( Boolean value )
   {
      assertUnsent();
      _September = value;
   }
	
   /**
    * Sets the October field for the request.
    * 
    * @param value  Value that the October will be set to.
    */
   public final void setOctober( Boolean value )
   {
      assertUnsent();
      _October = value;
   }
	
   /**
    * Sets the November field for the request.
    * 
    * @param value  Value that the November will be set to.
    */
   public final void setNovember( Boolean value )
   {
      assertUnsent();
      _November = value;
   }
	
   /**
    * Sets the December field for the request.
    * 
    * @param value  Value that the December will be set to.
    */
   public final void setDecember( Boolean value )
   {
      assertUnsent();
      _December = value;
   }
	
   /**
    * Sets the Occurs at end of month field for the request.
    * 
    * @param value  Value that the Occurs at end of month will be set to.
    */
   public final void setEndOfMonth( Boolean value )
   {
      assertUnsent();
      _EndOfMonth = value;
   }
	
   /**
    * Sets the Day of Week PAC occurs on field for the request.
    * 
    * @param value  Value that the Day of Week PAC occurs on will be set to.
    */
   public final void setDayOfWeek( Integer value )
   {
      assertUnsent();
      _DayOfWeek = value;
   }
	
   /**
    * Sets the Address Code (SWP) field for the request.
    * 
    * @param value  Value that the Address Code (SWP) will be set to.
    */
   public final void setAddrCode( String value )
   {
      assertUnsent();
      _AddrCode = value;
   }
	
   /**
    * Sets the Record Active field for the request.
    * 
    * @param value  Value that the Record Active will be set to.
    */
   public final void setGoodBad( Boolean value )
   {
      assertUnsent();
      _GoodBad = value;
   }
	
   /**
    * Sets the Effective Date field for the request.
    * 
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the Stop Date field for the request.
    * 
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( Date value )
   {
      assertUnsent();
      _StopDate = value;
   }
	
   /**
    * Sets the FundCode field for the request.
    * 
    * @param value  Value that the FundCode will be set to.
    */
   public final void setFundCode( String value )
   {
      assertUnsent();
      _FundCode = value;
   }
	
   /**
    * Sets the ClassCode field for the request.
    * 
    * @param value  Value that the ClassCode will be set to.
    */
   public final void setClassCode( String value )
   {
      assertUnsent();
      _ClassCode = value;
   }
	
   /**
    * Sets the Set As Default field for the request.
    * 
    * @param value  Value that the Set As Default will be set to.
    */
   public final void setSetAsDefault( Boolean value )
   {
      assertUnsent();
      _SetAsDefault = value;
   }
	
   /**
    * Sets the Version of Bank-Detl or Recur-Detail field for the request.
    * 
    * @param value  Value that the Version of Bank-Detl or Recur-Detail will be set to.
    */
   public final void setVersionNum( Integer value )
   {
      assertUnsent();
      _VersionNum = value;
   }
	
   /**
    * Sets the Initial Factor (Clan Plan) field for the request.
    * 
    * @param value  Value that the Initial Factor (Clan Plan) will be set to.
    */
   public final void setInitFactor( String value )
   {
      assertUnsent();
      _InitFactor = value;
   }
	
   /**
    * Sets the Plan Term (Clan Plan) field for the request.
    * 
    * @param value  Value that the Plan Term (Clan Plan) will be set to.
    */
   public final void setPlanTerm( Integer value )
   {
      assertUnsent();
      _PlanTerm = value;
   }
	
   /**
    * Sets the Payment Amount (Clan Plan) field for the request.
    * 
    * @param value  Value that the Payment Amount (Clan Plan) will be set to.
    */
   public final void setPaymentAmt( String value )
   {
      assertUnsent();
      _PaymentAmt = value;
   }
	
   /**
    * Sets the Last Payment (Clan Plan) field for the request.
    * 
    * @param value  Value that the Last Payment (Clan Plan) will be set to.
    */
   public final void setLastPayment( Integer value )
   {
      assertUnsent();
      _LastPayment = value;
   }
	
   /**
    * Sets the Commission (Clan Plan) field for the request.
    * 
    * @param value  Value that the Commission (Clan Plan) will be set to.
    */
   public final void setCommission( String value )
   {
      assertUnsent();
      _Commission = value;
   }
	
   /**
    * Sets the Admin Fee Amount (Clan Plan) field for the request.
    * 
    * @param value  Value that the Admin Fee Amount (Clan Plan) will be set to.
    */
   public final void setAdminFeeAmtClan( String value )
   {
      assertUnsent();
      _AdminFeeAmtClan = value;
   }
	
   /**
    * Sets the Transfer To Account (AT) field for the request.
    * 
    * @param value  Value that the Transfer To Account (AT) will be set to.
    */
   public final void setAccountTo( String value )
   {
      assertUnsent();
      _AccountTo = value;
   }
	
   /**
    * Sets the Transfer To Fund (AT) field for the request.
    * 
    * @param value  Value that the Transfer To Fund (AT) will be set to.
    */
   public final void setFundToCode( String value )
   {
      assertUnsent();
      _FundToCode = value;
   }
	
   /**
    * Sets the Transfer To Class (AT) field for the request.
    * 
    * @param value  Value that the Transfer To Class (AT) will be set to.
    */
   public final void setClassToCode( String value )
   {
      assertUnsent();
      _ClassToCode = value;
   }
	
   /**
    * Sets the Back End Load Fee Applicable(AT) field for the request.
    * 
    * @param value  Value that the Back End Load Fee Applicable(AT) will be set to.
    */
   public final void setBELFee( Boolean value )
   {
      assertUnsent();
      _BELFee = value;
   }
	
   /**
    * Sets the Frequency Code field for the request.
    * 
    * @param value  Value that the Frequency Code will be set to.
    */
   public final void setFrequency( String value )
   {
      assertUnsent();
      _Frequency = value;
   }
	
   /**
    * Sets the Transfer Type (AT) field for the request.
    * 
    * @param value  Value that the Transfer Type (AT) will be set to.
    */
   public final void setTransferType( String value )
   {
      assertUnsent();
      _TransferType = value;
   }
	
   /**
    * Sets the Payment Reason 1 field for the request.
    * 
    * @param value  Value that the Payment Reason 1 will be set to.
    */
   public final void setPayReason1( String value )
   {
      assertUnsent();
      _PayReason1 = value;
   }
	
   /**
    * Sets the Entity Type field for the request.
    * 
    * @param value  Value that the Entity Type will be set to.
    */
   public final void setEntitytype( String value )
   {
      assertUnsent();
      _Entitytype = value;
   }
	
   /**
    * Sets the Entity Type Sequence field for the request.
    * 
    * @param value  Value that the Entity Type Sequence will be set to.
    */
   public final void setEntityTypeSeq( Integer value )
   {
      assertUnsent();
      _EntityTypeSeq = value;
   }
	
   /**
    * Sets the Batch Name field for the request.
    * 
    * @param value  Value that the Batch Name will be set to.
    */
   public final void setBatchName( String value )
   {
      assertUnsent();
      _BatchName = value;
   }
	
   /**
    * Sets the Bank type code field for the request.
    * 
    * @param value  Value that the Bank type code will be set to.
    */
   public final void setBankType( String value )
   {
      assertUnsent();
      _BankType = value;
   }
	
   /**
    * Sets the Code to define processing location field for the request.
    * 
    * @param value  Value that the Code to define processing location will be set to.
    */
   public final void setACHProcessor( String value )
   {
      assertUnsent();
      _ACHProcessor = value;
   }
	
   /**
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransNum( Integer value )
   {
      assertUnsent();
      _TransNum = value;
   }
	
   /**
    * Sets the Bank Id field for the request.
    * 
    * @param value  Value that the Bank Id will be set to.
    */
   public final void setBankId( Integer value )
   {
      assertUnsent();
      _BankId = value;
   }
	
   /**
    * Sets the Pay Type field for the request.
    * 
    * @param value  Value that the Pay Type will be set to.
    */
   public final void setPayType( String value )
   {
      assertUnsent();
      _PayType = value;
   }
	
   /**
    * Sets the Accept Default Split Commission field for the request.
    * 
    * @param value  Value that the Accept Default Split Commission will be set to.
    */
   public final void setAutoSplitComm( Boolean value )
   {
      assertUnsent();
      _AutoSplitComm = value;
   }
	
   /**
    * Sets the Credit Info Line 1 field for the request.
    * 
    * @param value  Value that the Credit Info Line 1 will be set to.
    */
   public final void setCreditInfoLine1( String value )
   {
      assertUnsent();
      _CreditInfoLine1 = value;
   }
	
   /**
    * Sets the Credit Info Line 2 field for the request.
    * 
    * @param value  Value that the Credit Info Line 2 will be set to.
    */
   public final void setCreditInfoLine2( String value )
   {
      assertUnsent();
      _CreditInfoLine2 = value;
   }
	
   /**
    * Sets the Bank Address Line 1 field for the request.
    * 
    * @param value  Value that the Bank Address Line 1 will be set to.
    */
   public final void setBankAddr1( String value )
   {
      assertUnsent();
      _BankAddr1 = value;
   }
	
   /**
    * Sets the Bank Address Line 2 field for the request.
    * 
    * @param value  Value that the Bank Address Line 2 will be set to.
    */
   public final void setBankAddr2( String value )
   {
      assertUnsent();
      _BankAddr2 = value;
   }
	
   /**
    * Sets the Bank Address Line 3 field for the request.
    * 
    * @param value  Value that the Bank Address Line 3 will be set to.
    */
   public final void setBankAddr3( String value )
   {
      assertUnsent();
      _BankAddr3 = value;
   }
	
   /**
    * Sets the Bank Address Line 4 field for the request.
    * 
    * @param value  Value that the Bank Address Line 4 will be set to.
    */
   public final void setBankAddr4( String value )
   {
      assertUnsent();
      _BankAddr4 = value;
   }
	
   /**
    * Sets the Bank Address Line 5 field for the request.
    * 
    * @param value  Value that the Bank Address Line 5 will be set to.
    */
   public final void setBankAddr5( String value )
   {
      assertUnsent();
      _BankAddr5 = value;
   }
	
   /**
    * Sets the Bank Contact Person field for the request.
    * 
    * @param value  Value that the Bank Contact Person will be set to.
    */
   public final void setBankContact( String value )
   {
      assertUnsent();
      _BankContact = value;
   }
	
   /**
    * Sets the Bank Address Country Code field for the request.
    * 
    * @param value  Value that the Bank Address Country Code will be set to.
    */
   public final void setBankCntry( String value )
   {
      assertUnsent();
      _BankCntry = value;
   }
	
   /**
    * Sets the Bank Address Postal Code field for the request.
    * 
    * @param value  Value that the Bank Address Postal Code will be set to.
    */
   public final void setBankPstl( String value )
   {
      assertUnsent();
      _BankPstl = value;
   }
	
   /**
    * Sets the Bank Name field for the request.
    * 
    * @param value  Value that the Bank Name will be set to.
    */
   public final void setInstName( String value )
   {
      assertUnsent();
      _InstName = value;
   }
	
   /**
    * Sets the Saving Plan fee type field for the request.
    * 
    * @param value  Value that the Saving Plan fee type will be set to.
    */
   public final void setVUBPayOption( String value )
   {
      assertUnsent();
      _VUBPayOption = value;
   }
	
   /**
    * Sets the Saving Plan Code field for the request.
    * 
    * @param value  Value that the Saving Plan Code will be set to.
    */
   public final void setPlanCode( String value )
   {
      assertUnsent();
      _PlanCode = value;
   }
	
   /**
    * Sets the Fee on In side of Exchange field for the request.
    * 
    * @param value  Value that the Fee on In side of Exchange will be set to.
    */
   public final void setExchInFee( String value )
   {
      assertUnsent();
      _ExchInFee = value;
   }
	
   /**
    * Sets the Fee on In side of Exchnage is Flat(yes) Percentage(no) field for the request.
    * 
    * @param value  Value that the Fee on In side of Exchnage is Flat(yes) Percentage(no) will be set to.
    */
   public final void setExchInFlatPercent( Boolean value )
   {
      assertUnsent();
      _ExchInFlatPercent = value;
   }
	
   /**
    * Sets the Annual maintenance fee date field for the request.
    * 
    * @param value  Value that the Annual maintenance fee date will be set to.
    */
   public final void setAnnualFeeDate( Date value )
   {
      assertUnsent();
      _AnnualFeeDate = value;
   }
	
   /**
    * Sets the Annual Fee  charged? field for the request.
    * 
    * @param value  Value that the Annual Fee  charged? will be set to.
    */
   public final void setAnnualFee( Boolean value )
   {
      assertUnsent();
      _AnnualFee = value;
   }
	
   /**
    * Sets the Initial Amount field for the request.
    * 
    * @param value  Value that the Initial Amount will be set to.
    */
   public final void setInitialAmt( String value )
   {
      assertUnsent();
      _InitialAmt = value;
   }
	
   /**
    * Sets the VUB Expected Amount field for the request.
    * 
    * @param value  Value that the VUB Expected Amount will be set to.
    */
   public final void setVUBExpectedAmt( String value )
   {
      assertUnsent();
      _VUBExpectedAmt = value;
   }
	
   /**
    * Sets the Exchange Out Fee field for the request.
    * 
    * @param value  Value that the Exchange Out Fee will be set to.
    */
   public final void setExchOutFee( String value )
   {
      assertUnsent();
      _ExchOutFee = value;
   }
	
   /**
    * Sets the Exchange Out Flat/ Prcnt field for the request.
    * 
    * @param value  Value that the Exchange Out Flat/ Prcnt will be set to.
    */
   public final void setExchOutFlatPrcnt( Boolean value )
   {
      assertUnsent();
      _ExchOutFlatPrcnt = value;
   }
	
   /**
    * Sets the Payment Method field for the request.
    * 
    * @param value  Value that the Payment Method will be set to.
    */
   public final void setPayMethod( String value )
   {
      assertUnsent();
      _PayMethod = value;
   }
	
   /**
    * Sets the Override Federal Tax PUD field for the request.
    * 
    * @param value  Value that the Override Federal Tax PUD will be set to.
    */
   public final void setFedTaxPUDOverride( String value )
   {
      assertUnsent();
      _FedTaxPUDOverride = value;
   }
	
   /**
    * Sets the Federal Rate field for the request.
    * 
    * @param value  Value that the Federal Rate will be set to.
    */
   public final void setFedRate( String value )
   {
      assertUnsent();
      _FedRate = value;
   }
	
   /**
    * Sets the Override Provisional Tax PUD field for the request.
    * 
    * @param value  Value that the Override Provisional Tax PUD will be set to.
    */
   public final void setProvTaxPUDOverride( String value )
   {
      assertUnsent();
      _ProvTaxPUDOverride = value;
   }
	
   /**
    * Sets the Provisional Rate field for the request.
    * 
    * @param value  Value that the Provisional Rate will be set to.
    */
   public final void setProvRate( String value )
   {
      assertUnsent();
      _ProvRate = value;
   }
	
   /**
    * Sets the Pay Reason 2 field for the request.
    * 
    * @param value  Value that the Pay Reason 2 will be set to.
    */
   public final void setPayReason2( String value )
   {
      assertUnsent();
      _PayReason2 = value;
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
    * Sets the Verify Status field for the request.
    * 
    * @param value  Value that the Verify Status will be set to.
    */
   public final void setVerifyStat( String value )
   {
      assertUnsent();
      _VerifyStat = value;
   }
	
   /**
    * Sets the Stop Reason field for the request.
    * 
    * @param value  Value that the Stop Reason will be set to.
    */
   public final void setStopReason( String value )
   {
      assertUnsent();
      _StopReason = value;
   }
	
   /**
    * Sets the Non Financial Confirm field for the request.
    * 
    * @param value  Value that the Non Financial Confirm will be set to.
    */
   public final void setNonFinConfirm( String value )
   {
      assertUnsent();
      _NonFinConfirm = value;
   }
	
   /**
    * Sets the RDR Advice field for the request.
    * 
    * @param value  Value that the RDR Advice will be set to.
    */
   public final void setRDRAdvice( String value )
   {
      assertUnsent();
      _RDRAdvice = value;
   }
	
   /**
    * Sets the Event Receipt Date field for the request.
    * 
    * @param value  Value that the Event Receipt Date will be set to.
    */
   public final void setEventReceiptDate( Date value )
   {
      assertUnsent();
      _EventReceiptDate = value;
   }
	
   /**
    * Sets the Event Receipt Time field for the request.
    * 
    * @param value  Value that the Event Receipt Time will be set to.
    */
   public final void setEventReceiptTime( String value )
   {
      assertUnsent();
      _EventReceiptTime = value;
   }
	
   /**
    * Sets the SourceOfTrade field for the request.
    * 
    * @param value  Value that the SourceOfTrade will be set to.
    */
   public final void setSourceOfTrade( String value )
   {
      assertUnsent();
      _SourceOfTrade = value;
   }
	
   /**
    * Sets the ChannelOfTrade field for the request.
    * 
    * @param value  Value that the ChannelOfTrade will be set to.
    */
   public final void setChannelOfTrade( String value )
   {
      assertUnsent();
      _ChannelOfTrade = value;
   }
	
   /**
    * Sets the Platform field for the request.
    * 
    * @param value  Value that the Platform will be set to.
    */
   public final void setPlatform( String value )
   {
      assertUnsent();
      _Platform = value;
   }
	
   /**
    * Sets the PSDAdvice field for the request.
    * 
    * @param value  Value that the PSDAdvice will be set to.
    */
   public final void setPSDAdvice( String value )
   {
      assertUnsent();
      _PSDAdvice = value;
   }
	
   /**
    * Sets the SignatureDate field for the request.
    * 
    * @param value  Value that the SignatureDate will be set to.
    */
   public final void setSignatureDate( Date value )
   {
      assertUnsent();
      _SignatureDate = value;
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
    * Sets the Allocation Run Mode - fund record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Run Mode - fund record will be set to.
    */
   public final void setFundLvlRunMode( int index, String value )
   {
      assertUnsent();
      _FundLvlRunMode[index] = value;
   }
	
   /**
    * Sets the Allocation Fund To Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Fund To Code will be set to.
    */
   public final void setAllocFundToCode( int index, String value )
   {
      assertUnsent();
      _AllocFundToCode[index] = value;
   }
	
   /**
    * Sets the Allocation Class To Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Class To Code will be set to.
    */
   public final void setAllocClassToCode( int index, String value )
   {
      assertUnsent();
      _AllocClassToCode[index] = value;
   }
	
   /**
    * Sets the Allocation Percentage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Percentage will be set to.
    */
   public final void setAllocPercentage( int index, String value )
   {
      assertUnsent();
      _AllocPercentage[index] = value;
   }
	
   /**
    * Sets the Allocation Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Amount will be set to.
    */
   public final void setAllocAmount( int index, String value )
   {
      assertUnsent();
      _AllocAmount[index] = value;
   }
	
   /**
    * Sets the Distrib-Detl Recid for fund record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distrib-Detl Recid for fund record will be set to.
    */
   public final void setDistribFundLvlRId( int index, Integer value )
   {
      assertUnsent();
      _DistribFundLvlRId[index] = value;
   }
	
   /**
    * Sets the Allocation Level (AT) field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Level (AT) will be set to.
    */
   public final void setLevel( int index, Integer value )
   {
      assertUnsent();
      _Level[index] = value;
   }
	
   /**
    * Sets the Allocation Account To (AT) field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Allocation Account To (AT) will be set to.
    */
   public final void setAllocAccountNum( int index, String value )
   {
      assertUnsent();
      _AllocAccountNum[index] = value;
   }
	
   /**
    * Sets the Transaction Sequence field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Transaction Sequence will be set to.
    */
   public final void setTransSeq( int index, Integer value )
   {
      assertUnsent();
      _TransSeq[index] = value;
   }
	
   /**
    * Sets the RunMode for Commisions field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RunMode for Commisions will be set to.
    */
   public final void setCommRunMode( int index, String value )
   {
      assertUnsent();
      _CommRunMode[index] = value;
   }
	
   /**
    * Sets the Commission PayType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission PayType will be set to.
    */
   public final void setCommPayType( int index, String value )
   {
      assertUnsent();
      _CommPayType[index] = value;
   }
	
   /**
    * Sets the Commission - fixed or not field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission - fixed or not will be set to.
    */
   public final void setCommFixed( int index, Boolean value )
   {
      assertUnsent();
      _CommFixed[index] = value;
   }
	
   /**
    * Sets the Commission - Gross or Net field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission - Gross or Net will be set to.
    */
   public final void setCommGrossNet( int index, Boolean value )
   {
      assertUnsent();
      _CommGrossNet[index] = value;
   }
	
   /**
    * Sets the Commission Percent field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission Percent will be set to.
    */
   public final void setCommPrcnt( int index, String value )
   {
      assertUnsent();
      _CommPrcnt[index] = value;
   }
	
   /**
    * Sets the Commission - Broker Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission - Broker Code will be set to.
    */
   public final void setCommBrokCode( int index, String value )
   {
      assertUnsent();
      _CommBrokCode[index] = value;
   }
	
   /**
    * Sets the Commission - Branch Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission - Branch Code will be set to.
    */
   public final void setCommBranCode( int index, String value )
   {
      assertUnsent();
      _CommBranCode[index] = value;
   }
	
   /**
    * Sets the Commission - Sls Rep Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission - Sls Rep Code will be set to.
    */
   public final void setCommRepCode( int index, String value )
   {
      assertUnsent();
      _CommRepCode[index] = value;
   }
	
   /**
    * Sets the Commision Level field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commision Level will be set to.
    */
   public final void setCommLevel( int index, Integer value )
   {
      assertUnsent();
      _CommLevel[index] = value;
   }
	
   /**
    * Sets the Commission Rate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission Rate will be set to.
    */
   public final void setCommRate( int index, String value )
   {
      assertUnsent();
      _CommRate[index] = value;
   }
	
   /**
    * Sets the Renunciation Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Renunciation Amount will be set to.
    */
   public final void setRenunAmount( int index, String value )
   {
      assertUnsent();
      _RenunAmount[index] = value;
   }
	
   /**
    * Sets the Repeating session Record Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Repeating session Record Type will be set to.
    */
   public final void setRecType( int index, String value )
   {
      assertUnsent();
      _RecType[index] = value;
   }
	
   /**
    * Sets the Index Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Index Run Mode will be set to.
    */
   public final void setIndexRunMode( int index, String value )
   {
      assertUnsent();
      _IndexRunMode[index] = value;
   }
	
   /**
    * Sets the Index Amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Index Amount will be set to.
    */
   public final void setIndexAmt( int index, String value )
   {
      assertUnsent();
      _IndexAmt[index] = value;
   }
	
   /**
    * Sets the Index Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Index Type will be set to.
    */
   public final void setIndexType( int index, String value )
   {
      assertUnsent();
      _IndexType[index] = value;
   }
	
   /**
    * Sets the Index Frequency field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Index Frequency will be set to.
    */
   public final void setIndexFrequency( int index, String value )
   {
      assertUnsent();
      _IndexFrequency[index] = value;
   }
	
   /**
    * Sets the Effective date of Indexing Record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective date of Indexing Record will be set to.
    */
   public final void setStartDate( int index, Date value )
   {
      assertUnsent();
      _StartDate[index] = value;
   }
	
   /**
    * Sets the End date for Indexing Record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the End date for Indexing Record will be set to.
    */
   public final void setEndDate( int index, Date value )
   {
      assertUnsent();
      _EndDate[index] = value;
   }
	
   /**
    * Sets the PAC-Index record id field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the PAC-Index record id will be set to.
    */
   public final void setPACIndexRId( int index, Integer value )
   {
      assertUnsent();
      _PACIndexRId[index] = value;
   }
	
   /**
    * Sets the PAC-Index record version number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the PAC-Index record version number will be set to.
    */
   public final void setPACIndexVer( int index, Integer value )
   {
      assertUnsent();
      _PACIndexVer[index] = value;
   }
	
   /**
    * Sets the Percentage allocated to the account field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Percentage allocated to the account will be set to.
    */
   public final void setAcctPrcnt( int index, String value )
   {
      assertUnsent();
      _AcctPrcnt[index] = value;
   }
	
   /**
    * Sets the Distrib-Detl version for acct alloc field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distrib-Detl version for acct alloc will be set to.
    */
   public final void setDistribAcctLvlVer( int index, Integer value )
   {
      assertUnsent();
      _DistribAcctLvlVer[index] = value;
   }
	
   /**
    * Sets the Distrib-Detl rec id for Acct alloc record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distrib-Detl rec id for Acct alloc record will be set to.
    */
   public final void setDistribAcctLvlRId( int index, Integer value )
   {
      assertUnsent();
      _DistribAcctLvlRId[index] = value;
   }
	
   /**
    * Sets the Acct level run mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Acct level run mode will be set to.
    */
   public final void setAcctLvlRunMode( int index, String value )
   {
      assertUnsent();
      _AcctLvlRunMode[index] = value;
   }
	
   /**
    * Sets the Acct level allocated amount field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Acct level allocated amount will be set to.
    */
   public final void setAcctLvlAmount( int index, String value )
   {
      assertUnsent();
      _AcctLvlAmount[index] = value;
   }
	
   /**
    * Sets the Distrib-Detl record version for fund level rec field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distrib-Detl record version for fund level rec will be set to.
    */
   public final void setDistribFundLvlVer( int index, Integer value )
   {
      assertUnsent();
      _DistribFundLvlVer[index] = value;
   }
	
   /**
    * Sets the Next Index Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Next Index Date will be set to.
    */
   public final void setNextIndexDate( int index, Date value )
   {
      assertUnsent();
      _NextIndexDate[index] = value;
   }
	
   /**
    * Sets the Split Commission Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Split Commission Recid will be set to.
    */
   public final void setSplitCommRid( int index, Integer value )
   {
      assertUnsent();
      _SplitCommRid[index] = value;
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
      requestBuffer.appendField( _CompanyID );
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _TransType );
      requestBuffer.appendField( _PacSwpId );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SalesRepCode );
      requestBuffer.appendField( _Amount );
      requestBuffer.appendField( _AmountType );
      requestBuffer.appendField( _GrossOrNet );
      requestBuffer.appendField( _Fee );
      requestBuffer.appendField( _FlatPercent );
      requestBuffer.appendField( _FeeCurrency );
      requestBuffer.appendField( _AdminFeeAmt );
      requestBuffer.appendField( _AdminFeeCurr );
      requestBuffer.appendField( _LastBankType );
      requestBuffer.appendField( _BankIdNum );
      requestBuffer.appendField( _SwiftCode );
      requestBuffer.appendField( _RefNumber );
      requestBuffer.appendField( _TransitCode );
      requestBuffer.appendField( _BankAcctNum );
      requestBuffer.appendField( _BankAcctName );
      requestBuffer.appendField( _SourceOfBankAcct );
      requestBuffer.appendField( _BankAcctCurrency );
      requestBuffer.appendField( _BankAcctType );
      requestBuffer.appendField( _SrcOfFund );
      requestBuffer.appendField( _January );
      requestBuffer.appendField( _February );
      requestBuffer.appendField( _March );
      requestBuffer.appendField( _April );
      requestBuffer.appendField( _May );
      requestBuffer.appendField( _June );
      requestBuffer.appendField( _July );
      requestBuffer.appendField( _August );
      requestBuffer.appendField( _September );
      requestBuffer.appendField( _October );
      requestBuffer.appendField( _November );
      requestBuffer.appendField( _December );
      requestBuffer.appendField( _EndOfMonth );
      requestBuffer.appendField( _DayOfWeek );
      requestBuffer.appendField( _AddrCode );
      requestBuffer.appendField( _GoodBad );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _StopDate );
      requestBuffer.appendField( _FundCode );
      requestBuffer.appendField( _ClassCode );
      requestBuffer.appendField( _SetAsDefault );
      requestBuffer.appendField( _VersionNum );
      requestBuffer.appendField( _InitFactor );
      requestBuffer.appendField( _PlanTerm );
      requestBuffer.appendField( _PaymentAmt );
      requestBuffer.appendField( _LastPayment );
      requestBuffer.appendField( _Commission );
      requestBuffer.appendField( _AdminFeeAmtClan );
      requestBuffer.appendField( _AccountTo );
      requestBuffer.appendField( _FundToCode );
      requestBuffer.appendField( _ClassToCode );
      requestBuffer.appendField( _BELFee );
      requestBuffer.appendField( _Frequency );
      requestBuffer.appendField( _TransferType );
      requestBuffer.appendField( _PayReason1 );
      requestBuffer.appendField( _Entitytype );
      requestBuffer.appendField( _EntityTypeSeq );
      requestBuffer.appendField( _BatchName );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _BankType );
      requestBuffer.appendField( _ACHProcessor );
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _BankId );
      requestBuffer.appendField( _PayType );
      requestBuffer.appendField( _AutoSplitComm );
      requestBuffer.appendField( _CreditInfoLine1 );
      requestBuffer.appendField( _CreditInfoLine2 );
      requestBuffer.appendField( _BankAddr1 );
      requestBuffer.appendField( _BankAddr2 );
      requestBuffer.appendField( _BankAddr3 );
      requestBuffer.appendField( _BankAddr4 );
      requestBuffer.appendField( _BankAddr5 );
      requestBuffer.appendField( _BankContact );
      requestBuffer.appendField( _BankCntry );
      requestBuffer.appendField( _BankPstl );
      requestBuffer.appendField( _InstName );
      requestBuffer.appendField( _VUBPayOption );
      requestBuffer.appendField( _PlanCode );
      requestBuffer.appendField( _ExchInFee );
      requestBuffer.appendField( _ExchInFlatPercent );
      requestBuffer.appendField( _AnnualFeeDate );
      requestBuffer.appendField( _AnnualFee );
      requestBuffer.appendField( _InitialAmt );
      requestBuffer.appendField( _VUBExpectedAmt );
      requestBuffer.appendField( _ExchOutFee );
      requestBuffer.appendField( _ExchOutFlatPrcnt );
      requestBuffer.appendField( _PayMethod );
      requestBuffer.appendField( _FedTaxPUDOverride );
      requestBuffer.appendField( _FedRate );
      requestBuffer.appendField( _ProvTaxPUDOverride );
      requestBuffer.appendField( _ProvRate );
      requestBuffer.appendField( _PayReason2 );
      requestBuffer.appendField( _AWDBusinessArea );
      requestBuffer.appendField( _AWDWorkType );
      requestBuffer.appendField( _AWDObjectKey );
      requestBuffer.appendField( _AWDObjDateTime );
      requestBuffer.appendField( _VerifyStat );
      requestBuffer.appendField( _StopReason );
      requestBuffer.appendField( _NonFinConfirm );
      requestBuffer.appendField( _RDRAdvice );
      requestBuffer.appendField( _EventReceiptDate );
      requestBuffer.appendField( _EventReceiptTime );
      requestBuffer.appendField( _SourceOfTrade );
      requestBuffer.appendField( _ChannelOfTrade );
      requestBuffer.appendField( _Platform );
      requestBuffer.appendField( _PSDAdvice );
      requestBuffer.appendField( _SignatureDate );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _FundLvlRunMode[x] );
         requestBuffer.appendField( _AllocFundToCode[x] );
         requestBuffer.appendField( _AllocClassToCode[x] );
         requestBuffer.appendField( _AllocPercentage[x] );
         requestBuffer.appendField( _AllocAmount[x] );
         requestBuffer.appendField( _DistribFundLvlRId[x] );
         requestBuffer.appendField( _Level[x] );
         requestBuffer.appendField( _AllocAccountNum[x] );
         requestBuffer.appendField( _TransSeq[x] );
         requestBuffer.appendField( _CommRunMode[x] );
         requestBuffer.appendField( _CommPayType[x] );
         requestBuffer.appendField( _CommFixed[x] );
         requestBuffer.appendField( _CommGrossNet[x] );
         requestBuffer.appendField( _CommPrcnt[x] );
         requestBuffer.appendField( _CommBrokCode[x] );
         requestBuffer.appendField( _CommBranCode[x] );
         requestBuffer.appendField( _CommRepCode[x] );
         requestBuffer.appendField( _CommLevel[x] );
         requestBuffer.appendField( _CommRate[x] );
         requestBuffer.appendField( _RenunAmount[x] );
         requestBuffer.appendField( _RecType[x] );
         requestBuffer.appendField( _IndexRunMode[x] );
         requestBuffer.appendField( _IndexAmt[x] );
         requestBuffer.appendField( _IndexType[x] );
         requestBuffer.appendField( _IndexFrequency[x] );
         requestBuffer.appendField( _StartDate[x] );
         requestBuffer.appendField( _EndDate[x] );
         requestBuffer.appendField( _PACIndexRId[x] );
         requestBuffer.appendField( _PACIndexVer[x] );
         requestBuffer.appendField( _AcctPrcnt[x] );
         requestBuffer.appendField( _DistribAcctLvlVer[x] );
         requestBuffer.appendField( _DistribAcctLvlRId[x] );
         requestBuffer.appendField( _AcctLvlRunMode[x] );
         requestBuffer.appendField( _AcctLvlAmount[x] );
         requestBuffer.appendField( _DistribFundLvlVer[x] );
         requestBuffer.appendField( _NextIndexDate[x] );
         requestBuffer.appendField( _SplitCommRid[x] );
      }
   }

}

