
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * System Configuration view.
 * For additional view information see <A HREF="../../../../viewspecs/SystemConfiguration.doc">SystemConfiguration.doc</A>.
 * 
 * @author RTS Generated
 */
public class SystemConfigurationView extends IFastView implements Serializable
{

   /**
    * System Currency member variable.
    */
   private String _SysCurrency = null;
   
   /**
    * Shareholder Number Control member variable.
    */
   private String _ShrNumCtrl = null;
   
   /**
    * Shareholder Number Validation member variable.
    */
   private Boolean _ShrNumVal = null;
   
   /**
    * Account Number Control member variable.
    */
   private String _AcctNumCtrl = null;
   
   /**
    * Account Number Validation member variable.
    */
   private Boolean _AcctNumVal = null;
   
   /**
    * Default Group Code member variable.
    */
   private String _DefaultGrp = null;
   
   /**
    * Group Code Level member variable.
    */
   private String _GrpCodeLevel = null;
   
   /**
    * TaxType,AcctType,Unsizeable Update member variable.
    */
   private Boolean _TaxTypeUpd = null;
   
   /**
    * Marketing Mail Default member variable.
    */
   private Boolean _MktMailDef = null;
   
   /**
    * Identify Salesrep by BranchCode member variable.
    */
   private Boolean _RepByBranch = null;
   
   /**
    * Default Branch with Broker Code member variable.
    */
   private Boolean _BrokerBranch = null;
   
   /**
    * Capitalize Address Input member variable.
    */
   private Boolean _CapAddress = null;
   
   /**
    * Validate Country Code member variable.
    */
   private Boolean _CountryVal = null;
   
   /**
    * Mandatory ID Type member variable.
    */
   private String _MandatoryId = null;
   
   /**
    * Birth Name Mandatory member variable.
    */
   private Boolean _BirthNameMand = null;
   
   /**
    * Valid SIN List member variable.
    */
   private String _ValidSIN = null;
   
   /**
    * Shadow Nominee Name member variable.
    */
   private Boolean _ShadowNominee = null;
   
   /**
    * Bank Validation Rule 1 member variable.
    */
   private Integer _BankValid1 = null;
   
   /**
    * Bank Validation Rule 2 member variable.
    */
   private Boolean _BankValid2 = null;
   
   /**
    * Banking Layout member variable.
    */
   private Integer _BankLayout = null;
   
   /**
    * Broker Updatable on Systematic Screen member variable.
    */
   private Boolean _SYMBrkUpd = null;
   
   /**
    * Broker Authorized to deal with the fund member variable.
    */
   private Boolean _BrokerFund = null;
   
   /**
    * Generic Controls on PAC Minimum Amt member variable.
    */
   private String _PACMinAmt = null;
   
   /**
    * Edit Check controls on PAC MinimumAmt member variable.
    */
   private Integer _PACAmtEdit = null;
   
   /**
    * GIC Fund on Allocation Screen Only member variable.
    */
   private Boolean _GICAllocOnly = null;
   
   /**
    * Disable Fee for Allocation Trade member variable.
    */
   private Boolean _DisableFee4Alloc = null;
   
   /**
    * Currency defines rounding Precison member variable.
    */
   private Boolean _BusRounding = null;
   
   /**
    * Multiple Currency Applicable member variable.
    */
   private Boolean _MultiCurrency = null;
   
   /**
    * Split Commission Applicable member variable.
    */
   private Boolean _SplitComm = null;
   
   /**
    * Fee Parameter Set Up for New Acct member variable.
    */
   private Boolean _AcctFeeParm = null;
   
   /**
    * Capped Fund Error,Warning,Ignore member variable.
    */
   private String _CappedFund = null;
   
   /**
    * Banking Format Applicable member variable.
    */
   private Boolean _BankingFormat = null;
   
   /**
    * InstCode Max Digits member variable.
    */
   private Integer _InstCodeMax = null;
   
   /**
    * TransitNo Max Digits member variable.
    */
   private Integer _TransitNoMax = null;
   
   /**
    * BankAcctNum Max Digits member variable.
    */
   private Integer _BankAcctNumMax = null;
   
   /**
    * Current Business Date member variable.
    */
   private Date _CurrBusDate = null;
   
   /**
    * Mandatory Address Lines Code member variable.
    */
   private String _MandAddrLines = null;
   
   /**
    * Current System Date member variable.
    */
   private Date _CurrSysDate = null;
   
   /**
    * Current System Time member variable.
    */
   private String _CurrSysTime = null;
   
   /**
    * Check for Duplicate Transactions member variable.
    */
   private Boolean _CheckDup = null;
   
   /**
    * Investment Advice member variable.
    */
   private Boolean _InvAdvic = null;
   
   /**
    * Acquisition Fee Defaults member variable.
    */
   private Boolean _AcqFeeDefaults = null;
   
   /**
    * Last Cycle Date member variable.
    */
   private Date _LastCycleDate = null;
   
   /**
    * Acquisition Code Mandatory (Dilution) member variable.
    */
   private Boolean _AcCodeMand = null;
   
   /**
    * Split Acquisition Codes member variable.
    */
   private Boolean _SplitAcCode = null;
   
   /**
    * Excluded Red Code List member variable.
    */
   private String _TRExclRedCodes = null;
   
   /**
    * Transfer In Kind Red Code List member variable.
    */
   private String _TIKRedCodes = null;
   
   /**
    * Deal Date Time member variable.
    */
   private Boolean _DealDateTime = null;
   
   /**
    * EFT Purchase member variable.
    */
   private Boolean _EFTPurchase = null;
   
   /**
    * EFT Purchase in Future soft edit member variable.
    */
   private Boolean _EFTPurchFuture = null;
   
   /**
    * Group Contribution member variable.
    */
   private Boolean _GrpContribution = null;
   
   /**
    * Allow Fractions member variable.
    */
   private Boolean _AllowFractions = null;
   
   /**
    * Split Comm Trans Types member variable.
    */
   private String _SplitCommTransTypes = null;
   
   /**
    * Cash Receipt Track member variable.
    */
   private Boolean _CashReceiptTrack = null;
   
   /**
    * DepositId member variable.
    */
   private Boolean _DepositId = null;
   
   /**
    * DepositIdMand member variable.
    */
   private String _DepositIdMand = null;
   
   /**
    * DefaultPurchPayType member variable.
    */
   private String _DefaultPurchPayType = null;
   
   /**
    * EftPurchLeadDays member variable.
    */
   private Integer _EftPurchLeadDays = null;
   
   /**
    * Wire Number is suppossed to be character member variable.
    */
   private Boolean _CharWireNum = null;
   
   /**
    * Wire Number is mandatory member variable.
    */
   private Boolean _WireNumMand = null;
   
   /**
    * Wire number is defaulting to trans number member variable.
    */
   private Boolean _WireNoDefault = null;
   
   /**
    * Source of fund mandatory member variable.
    */
   private Boolean _SrcOfFundMandatory = null;
   
   /**
    * Previous year RRIF records are updatable member variable.
    */
   private Boolean _RRIFPrevYear = null;
   
   /**
    * Payment amount override is allowed for Minimum pay option member variable.
    */
   private Boolean _RRIFOrPayment = null;
   
   /**
    * validate rrif records member variable.
    */
   private Boolean _RRIFValidation = null;
   
   /**
    * Funds limit on allocations member variable.
    */
   private Integer _FundAllocLimit = null;
   
   /**
    * AMS client member variable.
    */
   private Boolean _AMSOrder = null;
   
   /**
    * Default settlement currency to Client's report currency member variable.
    */
   private Boolean _DefSetlCurr = null;
   
   /**
    * Previous Business Date member variable.
    */
   private Date _PrevBusDate = null;
   
   /**
    * Currency Check by Tax Type member variable.
    */
   private Boolean _CurrCheckByTaxType = null;
   
   /**
    * European Address Format member variable.
    */
   private Boolean _EuropAddrFormat = null;
   
   /**
    * Invalid Currency member variable.
    */
   private String _InvalidCurr = null;
   
   /**
    * Tax Type by Currency Check member variable.
    */
   private String _TaxTypeByCurrCheck = null;
   
   /**
    * Flag indicating if client has access to product seg member variable.
    */
   private Boolean _SegClient = null;
   
   /**
    * Flag indicating if client has access to product cot member variable.
    */
   private Boolean _CotClient = null;
   
   /**
    * Flag indicating if client has access to product res member variable.
    */
   private Boolean _ResClient = null;
   
   /**
    * Flag indicating if client has access to product lip member variable.
    */
   private Boolean _LipClient = null;
   
   /**
    * Flag indication amendment/exception based T550 Registration Listing member variable.
    */
   private Boolean _T550ReportMethod = null;
   
   /**
    * Consolidated EFT member variable.
    */
   private Boolean _ShrEftConsol = null;
   
   /**
    * PAC Consolidate member variable.
    */
   private Boolean _PacSwpEftConsol = null;
   
   /**
    * Flag indicating if client has limited access to Unseizable Accounts member variable.
    */
   private Boolean _Unseizable = null;
   
   /**
    * Flag indicating if redemption is allowed on Locked-In Accounts member variable.
    */
   private Boolean _RdLckdE = null;
   
   /**
    * Flag indicating Edit/Warning Message for redeeming from Locked-In Account member variable.
    */
   private Boolean _RdLckdW = null;
   
   /**
    * Title Restrictions Edits member variable.
    */
   private Boolean _TitleRestrict = null;
   
   /**
    * Flag indicating if trade can be process with date greater than 365 days member variable.
    */
   private Boolean _EditDeffs = null;
   
   /**
    * Flag that indicates if purchase will be rounded Up or Down member variable.
    */
   private Boolean _RoundFlag = null;
   
   /**
    * Flag indicating Redemption of Interest for Money Market Fund of Omnibus member variable.
    */
   private Boolean _RedAccruedInt = null;
   
   /**
    * PQLIF/LIRAFullRedReq - Red Code member variable.
    */
   private String _PQLIFLIRARedCodes = null;
   
   /**
    * PQLIF/LIRAFullRedReq - Juris member variable.
    */
   private String _PQLIFLIRAJuris = null;
   
   /**
    * PQLIF/LIRAFullRedReq -  Age member variable.
    */
   private Integer _PQLIFLIRAAge = null;
   
   /**
    * PQLIF/LIRAFullRedReq - % MPE member variable.
    */
   private Integer _PQLIFLIRAMaxPrct = null;
   
   /**
    * PQLIFLIRAFullRedReq - TaxType member variable.
    */
   private String _PQLIFLIRATaxType = null;
   
   /**
    * Auto Banking member variable.
    */
   private Boolean _AutoBanking = null;
   
   /**
    * Defaukt Settle Currency with Acct currency for redemption member variable.
    */
   private Boolean _RdAcctCurrency = null;
   
   /**
    * Indicates if  client use srcaccount for EURO Banking member variable.
    */
   private Boolean _BankSrcAcct = null;
   
   /**
    * Source of Fund member variable.
    */
   private Boolean _SourceOfFund = null;
   
   /**
    * Recipient Type member variable.
    */
   private Boolean _ModRecipType = null;
   
   /**
    * Wire Order Account Numbers member variable.
    */
   private String _SpecAcctNum = null;
   
   /**
    * Trading Cut Off Time Parameters member variable.
    */
   private Boolean _TradeCutOff = null;
   
   /**
    * Indicates if Sytem feature "PartTransAsFull" is active member variable.
    */
   private Boolean _PartTransAsFull = null;
   
   /**
    * Flag indicating Generic Control "Cheque Delivery Method" control is available member variable.
    */
   private String _DelivDeflt = null;
   
   /**
    * Flag indicating if SplitComm is assigned member variable.
    */
   private Boolean _Split100 = null;
   
   /**
    * Flag indicating if control "Valid CASH ID Pay Types" exists member variable.
    */
   private Boolean _CashDistRule = null;
   
   /**
    * Valid CASH ID Pay Type member variable.
    */
   private String _ValidDistPayTypes = null;
   
   /**
    * All Funds Transfers member variable.
    */
   private Boolean _AllFundsTransfers = null;
   
   /**
    * Flag indicating if Transfer from registered acct to diff shareholder member variable.
    */
   private Boolean _TfrToDiffSH = null;
   
   /**
    * List of the valid Death Claim Redemption member variable.
    */
   private String _DeathRedCode = null;
   
   /**
    * Codes for RRSP and RRIF Spouse beneficiaries member variable.
    */
   private String _SpouseBenefReln = null;
   
   /**
    * Codes for RRSP and RRIF Child beneficiaries member variable.
    */
   private String _ChildBenefReln = null;
   
   /**
    * Flag indicating if Shareholder Relation is 1 to 1 member variable.
    */
   private Boolean _MultiAcctEachShrNum = null;
   
   /**
    * Flag which permits update of Order Type field on trade entry screens member variable.
    */
   private Boolean _UpdOrdType = null;
   
   /**
    * Commission Type member variable.
    */
   private Integer _CommissionType = null;
   
   /**
    * Residency field 1 member variable.
    */
   private String _Residency1 = null;
   
   /**
    * Residency field 2 member variable.
    */
   private String _Residency2 = null;
   
   /**
    * Residency field 3 member variable.
    */
   private String _Residency3 = null;
   
   /**
    * Default Redemption Code Enabled member variable.
    */
   private Boolean _DefltRedCodeFlag = null;
   
   /**
    * Default Redemption Code member variable.
    */
   private String _DefltRedCode = null;
   
   /**
    * Flag indicating that sls rep will  be validated if it is eligible to deal  with the fund member variable.
    */
   private Boolean _FundEligSlsRepLvl = null;
   
   /**
    * Flag indicating if Wrap Column is to be displayed on Account Verify screen member variable.
    */
   private Boolean _WrapAccount = null;
   
   /**
    * Flag indicating if funds will be validated against Allowable Tranfers Table member variable.
    */
   private Boolean _DistribFundsValidate = null;
   
   /**
    * Flag indicating if target fund will be validated against fund groups member variable.
    */
   private Boolean _XSFundsValidate = null;
   
   /**
    * AMS Type supported by client member variable.
    */
   private String _ClientAMSType = null;
   
   /**
    * Class Rule member variable.
    */
   private Integer _ClassRule = null;
   
   /**
    * Profile Code Default member variable.
    */
   private String _ProfileCodeDflt = null;
   
   /**
    * Mgmt Fee Payment Option Default value member variable.
    */
   private String _MgmtFeePayOptDflt = null;
   
   /**
    * Flag indicating if Mgmt Company will be paid commission member variable.
    */
   private Boolean _MgmtCoPayReq = null;
   
   /**
    * Option for configuration on the split preference member variable.
    */
   private Integer _SplitPreferenceOption = null;
   
   /**
    * Flag indicates env support RESP 2 member variable.
    */
   private Boolean _RES2Client = null;
   
   /**
    * Flag indicating if QESI functionality is active member variable.
    */
   private Boolean _QESIClient = null;
   
   /**
    * Effective date of HRDC Interface Transaction Standard 3.0.1 member variable.
    */
   private Date _PSEEAPEditDate = null;
   
   /**
    * Eligible Date for CLB member variable.
    */
   private Date _EligDateforCLB = null;
   
   /**
    * Non Trustee Start Date member variable.
    */
   private Date _NonTrustStartDate = null;
   
   /**
    * Non Trustee Stop Date member variable.
    */
   private Date _NonTrustStopDate = null;
   
   /**
    * Flag indicating if Non Trustee trade member variable.
    */
   private Boolean _IsNonTrustee = null;
   
   /**
    * Automatically assign regulatory document member variable.
    */
   private Boolean _AutoDocAssign = null;
   

   /**
    * Constructs the SystemConfigurationView object.
    * 
    */
   public SystemConfigurationView()
   {
      super ( new SystemConfigurationRequest() );
   }

   /**
    * Constructs the SystemConfigurationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public SystemConfigurationView( String hostEncoding )
   {
      super ( new SystemConfigurationRequest( hostEncoding ) );
   }

   /**
    * Gets the SystemConfigurationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The SystemConfigurationRequest object.
    */
   public final SystemConfigurationRequest getRequest()
   {
      return (SystemConfigurationRequest)getIFastRequest();
   }
        
   /**
    * Gets the System Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the System Currency or null.
    */
   public final String getSysCurrency()
   {
      return _SysCurrency;
   }
	
   /**
    * Gets the System Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the System Currency or the specified default value.
    */
   public final String getSysCurrency( String defaultValue )
   {
      return _SysCurrency == null ? defaultValue : _SysCurrency;
   }
                  
   /**
    * Gets the Shareholder Number Control field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Number Control or null.
    */
   public final String getShrNumCtrl()
   {
      return _ShrNumCtrl;
   }
	
   /**
    * Gets the Shareholder Number Control field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number Control or the specified default value.
    */
   public final String getShrNumCtrl( String defaultValue )
   {
      return _ShrNumCtrl == null ? defaultValue : _ShrNumCtrl;
   }
                  
   /**
    * Gets the Shareholder Number Validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Number Validation or null.
    */
   public final Boolean getShrNumVal()
   {
      return _ShrNumVal;
   }
	
   /**
    * Gets the Shareholder Number Validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number Validation or the specified default value.
    */
   public final boolean getShrNumVal( boolean defaultValue )
   {
      return _ShrNumVal == null ? defaultValue : _ShrNumVal.booleanValue();
   }
                  
   /**
    * Gets the Account Number Control field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Number Control or null.
    */
   public final String getAcctNumCtrl()
   {
      return _AcctNumCtrl;
   }
	
   /**
    * Gets the Account Number Control field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number Control or the specified default value.
    */
   public final String getAcctNumCtrl( String defaultValue )
   {
      return _AcctNumCtrl == null ? defaultValue : _AcctNumCtrl;
   }
                  
   /**
    * Gets the Account Number Validation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Number Validation or null.
    */
   public final Boolean getAcctNumVal()
   {
      return _AcctNumVal;
   }
	
   /**
    * Gets the Account Number Validation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number Validation or the specified default value.
    */
   public final boolean getAcctNumVal( boolean defaultValue )
   {
      return _AcctNumVal == null ? defaultValue : _AcctNumVal.booleanValue();
   }
                  
   /**
    * Gets the Default Group Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Group Code or null.
    */
   public final String getDefaultGrp()
   {
      return _DefaultGrp;
   }
	
   /**
    * Gets the Default Group Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Group Code or the specified default value.
    */
   public final String getDefaultGrp( String defaultValue )
   {
      return _DefaultGrp == null ? defaultValue : _DefaultGrp;
   }
                  
   /**
    * Gets the Group Code Level field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Group Code Level or null.
    */
   public final String getGrpCodeLevel()
   {
      return _GrpCodeLevel;
   }
	
   /**
    * Gets the Group Code Level field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Code Level or the specified default value.
    */
   public final String getGrpCodeLevel( String defaultValue )
   {
      return _GrpCodeLevel == null ? defaultValue : _GrpCodeLevel;
   }
                  
   /**
    * Gets the TaxType,AcctType,Unsizeable Update field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TaxType,AcctType,Unsizeable Update or null.
    */
   public final Boolean getTaxTypeUpd()
   {
      return _TaxTypeUpd;
   }
	
   /**
    * Gets the TaxType,AcctType,Unsizeable Update field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TaxType,AcctType,Unsizeable Update or the specified default value.
    */
   public final boolean getTaxTypeUpd( boolean defaultValue )
   {
      return _TaxTypeUpd == null ? defaultValue : _TaxTypeUpd.booleanValue();
   }
                  
   /**
    * Gets the Marketing Mail Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Marketing Mail Default or null.
    */
   public final Boolean getMktMailDef()
   {
      return _MktMailDef;
   }
	
   /**
    * Gets the Marketing Mail Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Marketing Mail Default or the specified default value.
    */
   public final boolean getMktMailDef( boolean defaultValue )
   {
      return _MktMailDef == null ? defaultValue : _MktMailDef.booleanValue();
   }
                  
   /**
    * Gets the Identify Salesrep by BranchCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Identify Salesrep by BranchCode or null.
    */
   public final Boolean getRepByBranch()
   {
      return _RepByBranch;
   }
	
   /**
    * Gets the Identify Salesrep by BranchCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Identify Salesrep by BranchCode or the specified default value.
    */
   public final boolean getRepByBranch( boolean defaultValue )
   {
      return _RepByBranch == null ? defaultValue : _RepByBranch.booleanValue();
   }
                  
   /**
    * Gets the Default Branch with Broker Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Branch with Broker Code or null.
    */
   public final Boolean getBrokerBranch()
   {
      return _BrokerBranch;
   }
	
   /**
    * Gets the Default Branch with Broker Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Branch with Broker Code or the specified default value.
    */
   public final boolean getBrokerBranch( boolean defaultValue )
   {
      return _BrokerBranch == null ? defaultValue : _BrokerBranch.booleanValue();
   }
                  
   /**
    * Gets the Capitalize Address Input field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Capitalize Address Input or null.
    */
   public final Boolean getCapAddress()
   {
      return _CapAddress;
   }
	
   /**
    * Gets the Capitalize Address Input field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Capitalize Address Input or the specified default value.
    */
   public final boolean getCapAddress( boolean defaultValue )
   {
      return _CapAddress == null ? defaultValue : _CapAddress.booleanValue();
   }
                  
   /**
    * Gets the Validate Country Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Validate Country Code or null.
    */
   public final Boolean getCountryVal()
   {
      return _CountryVal;
   }
	
   /**
    * Gets the Validate Country Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Validate Country Code or the specified default value.
    */
   public final boolean getCountryVal( boolean defaultValue )
   {
      return _CountryVal == null ? defaultValue : _CountryVal.booleanValue();
   }
                  
   /**
    * Gets the Mandatory ID Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mandatory ID Type or null.
    */
   public final String getMandatoryId()
   {
      return _MandatoryId;
   }
	
   /**
    * Gets the Mandatory ID Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mandatory ID Type or the specified default value.
    */
   public final String getMandatoryId( String defaultValue )
   {
      return _MandatoryId == null ? defaultValue : _MandatoryId;
   }
                  
   /**
    * Gets the Birth Name Mandatory field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Birth Name Mandatory or null.
    */
   public final Boolean getBirthNameMand()
   {
      return _BirthNameMand;
   }
	
   /**
    * Gets the Birth Name Mandatory field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Birth Name Mandatory or the specified default value.
    */
   public final boolean getBirthNameMand( boolean defaultValue )
   {
      return _BirthNameMand == null ? defaultValue : _BirthNameMand.booleanValue();
   }
                  
   /**
    * Gets the Valid SIN List field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Valid SIN List or null.
    */
   public final String getValidSIN()
   {
      return _ValidSIN;
   }
	
   /**
    * Gets the Valid SIN List field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valid SIN List or the specified default value.
    */
   public final String getValidSIN( String defaultValue )
   {
      return _ValidSIN == null ? defaultValue : _ValidSIN;
   }
                  
   /**
    * Gets the Shadow Nominee Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shadow Nominee Name or null.
    */
   public final Boolean getShadowNominee()
   {
      return _ShadowNominee;
   }
	
   /**
    * Gets the Shadow Nominee Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shadow Nominee Name or the specified default value.
    */
   public final boolean getShadowNominee( boolean defaultValue )
   {
      return _ShadowNominee == null ? defaultValue : _ShadowNominee.booleanValue();
   }
                  
   /**
    * Gets the Bank Validation Rule 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Validation Rule 1 or null.
    */
   public final Integer getBankValid1()
   {
      return _BankValid1;
   }
	
   /**
    * Gets the Bank Validation Rule 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Validation Rule 1 or the specified default value.
    */
   public final int getBankValid1( int defaultValue )
   {
      return _BankValid1 == null ? defaultValue : _BankValid1.intValue();
   }
                  
   /**
    * Gets the Bank Validation Rule 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Bank Validation Rule 2 or null.
    */
   public final Boolean getBankValid2()
   {
      return _BankValid2;
   }
	
   /**
    * Gets the Bank Validation Rule 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Validation Rule 2 or the specified default value.
    */
   public final boolean getBankValid2( boolean defaultValue )
   {
      return _BankValid2 == null ? defaultValue : _BankValid2.booleanValue();
   }
                  
   /**
    * Gets the Banking Layout field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Banking Layout or null.
    */
   public final Integer getBankLayout()
   {
      return _BankLayout;
   }
	
   /**
    * Gets the Banking Layout field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Banking Layout or the specified default value.
    */
   public final int getBankLayout( int defaultValue )
   {
      return _BankLayout == null ? defaultValue : _BankLayout.intValue();
   }
                  
   /**
    * Gets the Broker Updatable on Systematic Screen field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Updatable on Systematic Screen or null.
    */
   public final Boolean getSYMBrkUpd()
   {
      return _SYMBrkUpd;
   }
	
   /**
    * Gets the Broker Updatable on Systematic Screen field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Updatable on Systematic Screen or the specified default value.
    */
   public final boolean getSYMBrkUpd( boolean defaultValue )
   {
      return _SYMBrkUpd == null ? defaultValue : _SYMBrkUpd.booleanValue();
   }
                  
   /**
    * Gets the Broker Authorized to deal with the fund field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Broker Authorized to deal with the fund or null.
    */
   public final Boolean getBrokerFund()
   {
      return _BrokerFund;
   }
	
   /**
    * Gets the Broker Authorized to deal with the fund field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Authorized to deal with the fund or the specified default value.
    */
   public final boolean getBrokerFund( boolean defaultValue )
   {
      return _BrokerFund == null ? defaultValue : _BrokerFund.booleanValue();
   }
                  
   /**
    * Gets the Generic Controls on PAC Minimum Amt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Generic Controls on PAC Minimum Amt or null.
    */
   public final String getPACMinAmt()
   {
      return _PACMinAmt;
   }
	
   /**
    * Gets the Generic Controls on PAC Minimum Amt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Generic Controls on PAC Minimum Amt or the specified default value.
    */
   public final String getPACMinAmt( String defaultValue )
   {
      return _PACMinAmt == null ? defaultValue : _PACMinAmt;
   }
                  
   /**
    * Gets the Edit Check controls on PAC MinimumAmt field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Edit Check controls on PAC MinimumAmt or null.
    */
   public final Integer getPACAmtEdit()
   {
      return _PACAmtEdit;
   }
	
   /**
    * Gets the Edit Check controls on PAC MinimumAmt field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Edit Check controls on PAC MinimumAmt or the specified default value.
    */
   public final int getPACAmtEdit( int defaultValue )
   {
      return _PACAmtEdit == null ? defaultValue : _PACAmtEdit.intValue();
   }
                  
   /**
    * Gets the GIC Fund on Allocation Screen Only field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the GIC Fund on Allocation Screen Only or null.
    */
   public final Boolean getGICAllocOnly()
   {
      return _GICAllocOnly;
   }
	
   /**
    * Gets the GIC Fund on Allocation Screen Only field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GIC Fund on Allocation Screen Only or the specified default value.
    */
   public final boolean getGICAllocOnly( boolean defaultValue )
   {
      return _GICAllocOnly == null ? defaultValue : _GICAllocOnly.booleanValue();
   }
                  
   /**
    * Gets the Disable Fee for Allocation Trade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Disable Fee for Allocation Trade or null.
    */
   public final Boolean getDisableFee4Alloc()
   {
      return _DisableFee4Alloc;
   }
	
   /**
    * Gets the Disable Fee for Allocation Trade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Disable Fee for Allocation Trade or the specified default value.
    */
   public final boolean getDisableFee4Alloc( boolean defaultValue )
   {
      return _DisableFee4Alloc == null ? defaultValue : _DisableFee4Alloc.booleanValue();
   }
                  
   /**
    * Gets the Currency defines rounding Precison field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Currency defines rounding Precison or null.
    */
   public final Boolean getBusRounding()
   {
      return _BusRounding;
   }
	
   /**
    * Gets the Currency defines rounding Precison field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency defines rounding Precison or the specified default value.
    */
   public final boolean getBusRounding( boolean defaultValue )
   {
      return _BusRounding == null ? defaultValue : _BusRounding.booleanValue();
   }
                  
   /**
    * Gets the Multiple Currency Applicable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Multiple Currency Applicable or null.
    */
   public final Boolean getMultiCurrency()
   {
      return _MultiCurrency;
   }
	
   /**
    * Gets the Multiple Currency Applicable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Multiple Currency Applicable or the specified default value.
    */
   public final boolean getMultiCurrency( boolean defaultValue )
   {
      return _MultiCurrency == null ? defaultValue : _MultiCurrency.booleanValue();
   }
                  
   /**
    * Gets the Split Commission Applicable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Split Commission Applicable or null.
    */
   public final Boolean getSplitComm()
   {
      return _SplitComm;
   }
	
   /**
    * Gets the Split Commission Applicable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Commission Applicable or the specified default value.
    */
   public final boolean getSplitComm( boolean defaultValue )
   {
      return _SplitComm == null ? defaultValue : _SplitComm.booleanValue();
   }
                  
   /**
    * Gets the Fee Parameter Set Up for New Acct field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Fee Parameter Set Up for New Acct or null.
    */
   public final Boolean getAcctFeeParm()
   {
      return _AcctFeeParm;
   }
	
   /**
    * Gets the Fee Parameter Set Up for New Acct field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Parameter Set Up for New Acct or the specified default value.
    */
   public final boolean getAcctFeeParm( boolean defaultValue )
   {
      return _AcctFeeParm == null ? defaultValue : _AcctFeeParm.booleanValue();
   }
                  
   /**
    * Gets the Capped Fund Error,Warning,Ignore field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Capped Fund Error,Warning,Ignore or null.
    */
   public final String getCappedFund()
   {
      return _CappedFund;
   }
	
   /**
    * Gets the Capped Fund Error,Warning,Ignore field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Capped Fund Error,Warning,Ignore or the specified default value.
    */
   public final String getCappedFund( String defaultValue )
   {
      return _CappedFund == null ? defaultValue : _CappedFund;
   }
                  
   /**
    * Gets the Banking Format Applicable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Banking Format Applicable or null.
    */
   public final Boolean getBankingFormat()
   {
      return _BankingFormat;
   }
	
   /**
    * Gets the Banking Format Applicable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Banking Format Applicable or the specified default value.
    */
   public final boolean getBankingFormat( boolean defaultValue )
   {
      return _BankingFormat == null ? defaultValue : _BankingFormat.booleanValue();
   }
                  
   /**
    * Gets the InstCode Max Digits field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the InstCode Max Digits or null.
    */
   public final Integer getInstCodeMax()
   {
      return _InstCodeMax;
   }
	
   /**
    * Gets the InstCode Max Digits field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InstCode Max Digits or the specified default value.
    */
   public final int getInstCodeMax( int defaultValue )
   {
      return _InstCodeMax == null ? defaultValue : _InstCodeMax.intValue();
   }
                  
   /**
    * Gets the TransitNo Max Digits field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TransitNo Max Digits or null.
    */
   public final Integer getTransitNoMax()
   {
      return _TransitNoMax;
   }
	
   /**
    * Gets the TransitNo Max Digits field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TransitNo Max Digits or the specified default value.
    */
   public final int getTransitNoMax( int defaultValue )
   {
      return _TransitNoMax == null ? defaultValue : _TransitNoMax.intValue();
   }
                  
   /**
    * Gets the BankAcctNum Max Digits field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BankAcctNum Max Digits or null.
    */
   public final Integer getBankAcctNumMax()
   {
      return _BankAcctNumMax;
   }
	
   /**
    * Gets the BankAcctNum Max Digits field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAcctNum Max Digits or the specified default value.
    */
   public final int getBankAcctNumMax( int defaultValue )
   {
      return _BankAcctNumMax == null ? defaultValue : _BankAcctNumMax.intValue();
   }
                  
   /**
    * Gets the Current Business Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Current Business Date or null.
    */
   public final Date getCurrBusDate()
   {
      return _CurrBusDate;
   }
	
   /**
    * Gets the Current Business Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current Business Date or the specified default value.
    */
   public final Date getCurrBusDate( Date defaultValue )
   {
      return _CurrBusDate == null ? defaultValue : _CurrBusDate;
   }
                  
   /**
    * Gets the Mandatory Address Lines Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mandatory Address Lines Code or null.
    */
   public final String getMandAddrLines()
   {
      return _MandAddrLines;
   }
	
   /**
    * Gets the Mandatory Address Lines Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mandatory Address Lines Code or the specified default value.
    */
   public final String getMandAddrLines( String defaultValue )
   {
      return _MandAddrLines == null ? defaultValue : _MandAddrLines;
   }
                  
   /**
    * Gets the Current System Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Current System Date or null.
    */
   public final Date getCurrSysDate()
   {
      return _CurrSysDate;
   }
	
   /**
    * Gets the Current System Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current System Date or the specified default value.
    */
   public final Date getCurrSysDate( Date defaultValue )
   {
      return _CurrSysDate == null ? defaultValue : _CurrSysDate;
   }
                  
   /**
    * Gets the Current System Time field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Current System Time or null.
    */
   public final String getCurrSysTime()
   {
      return _CurrSysTime;
   }
	
   /**
    * Gets the Current System Time field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Current System Time or the specified default value.
    */
   public final String getCurrSysTime( String defaultValue )
   {
      return _CurrSysTime == null ? defaultValue : _CurrSysTime;
   }
                  
   /**
    * Gets the Check for Duplicate Transactions field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Check for Duplicate Transactions or null.
    */
   public final Boolean getCheckDup()
   {
      return _CheckDup;
   }
	
   /**
    * Gets the Check for Duplicate Transactions field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Check for Duplicate Transactions or the specified default value.
    */
   public final boolean getCheckDup( boolean defaultValue )
   {
      return _CheckDup == null ? defaultValue : _CheckDup.booleanValue();
   }
                  
   /**
    * Gets the Investment Advice field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment Advice or null.
    */
   public final Boolean getInvAdvic()
   {
      return _InvAdvic;
   }
	
   /**
    * Gets the Investment Advice field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Advice or the specified default value.
    */
   public final boolean getInvAdvic( boolean defaultValue )
   {
      return _InvAdvic == null ? defaultValue : _InvAdvic.booleanValue();
   }
                  
   /**
    * Gets the Acquisition Fee Defaults field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Acquisition Fee Defaults or null.
    */
   public final Boolean getAcqFeeDefaults()
   {
      return _AcqFeeDefaults;
   }
	
   /**
    * Gets the Acquisition Fee Defaults field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Fee Defaults or the specified default value.
    */
   public final boolean getAcqFeeDefaults( boolean defaultValue )
   {
      return _AcqFeeDefaults == null ? defaultValue : _AcqFeeDefaults.booleanValue();
   }
                  
   /**
    * Gets the Last Cycle Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Last Cycle Date or null.
    */
   public final Date getLastCycleDate()
   {
      return _LastCycleDate;
   }
	
   /**
    * Gets the Last Cycle Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Cycle Date or the specified default value.
    */
   public final Date getLastCycleDate( Date defaultValue )
   {
      return _LastCycleDate == null ? defaultValue : _LastCycleDate;
   }
                  
   /**
    * Gets the Acquisition Code Mandatory (Dilution) field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Acquisition Code Mandatory (Dilution) or null.
    */
   public final Boolean getAcCodeMand()
   {
      return _AcCodeMand;
   }
	
   /**
    * Gets the Acquisition Code Mandatory (Dilution) field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Code Mandatory (Dilution) or the specified default value.
    */
   public final boolean getAcCodeMand( boolean defaultValue )
   {
      return _AcCodeMand == null ? defaultValue : _AcCodeMand.booleanValue();
   }
                  
   /**
    * Gets the Split Acquisition Codes field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Split Acquisition Codes or null.
    */
   public final Boolean getSplitAcCode()
   {
      return _SplitAcCode;
   }
	
   /**
    * Gets the Split Acquisition Codes field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Acquisition Codes or the specified default value.
    */
   public final boolean getSplitAcCode( boolean defaultValue )
   {
      return _SplitAcCode == null ? defaultValue : _SplitAcCode.booleanValue();
   }
                  
   /**
    * Gets the Excluded Red Code List field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Excluded Red Code List or null.
    */
   public final String getTRExclRedCodes()
   {
      return _TRExclRedCodes;
   }
	
   /**
    * Gets the Excluded Red Code List field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Excluded Red Code List or the specified default value.
    */
   public final String getTRExclRedCodes( String defaultValue )
   {
      return _TRExclRedCodes == null ? defaultValue : _TRExclRedCodes;
   }
                  
   /**
    * Gets the Transfer In Kind Red Code List field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transfer In Kind Red Code List or null.
    */
   public final String getTIKRedCodes()
   {
      return _TIKRedCodes;
   }
	
   /**
    * Gets the Transfer In Kind Red Code List field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer In Kind Red Code List or the specified default value.
    */
   public final String getTIKRedCodes( String defaultValue )
   {
      return _TIKRedCodes == null ? defaultValue : _TIKRedCodes;
   }
                  
   /**
    * Gets the Deal Date Time field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Deal Date Time or null.
    */
   public final Boolean getDealDateTime()
   {
      return _DealDateTime;
   }
	
   /**
    * Gets the Deal Date Time field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deal Date Time or the specified default value.
    */
   public final boolean getDealDateTime( boolean defaultValue )
   {
      return _DealDateTime == null ? defaultValue : _DealDateTime.booleanValue();
   }
                  
   /**
    * Gets the EFT Purchase field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EFT Purchase or null.
    */
   public final Boolean getEFTPurchase()
   {
      return _EFTPurchase;
   }
	
   /**
    * Gets the EFT Purchase field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EFT Purchase or the specified default value.
    */
   public final boolean getEFTPurchase( boolean defaultValue )
   {
      return _EFTPurchase == null ? defaultValue : _EFTPurchase.booleanValue();
   }
                  
   /**
    * Gets the EFT Purchase in Future soft edit field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EFT Purchase in Future soft edit or null.
    */
   public final Boolean getEFTPurchFuture()
   {
      return _EFTPurchFuture;
   }
	
   /**
    * Gets the EFT Purchase in Future soft edit field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EFT Purchase in Future soft edit or the specified default value.
    */
   public final boolean getEFTPurchFuture( boolean defaultValue )
   {
      return _EFTPurchFuture == null ? defaultValue : _EFTPurchFuture.booleanValue();
   }
                  
   /**
    * Gets the Group Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Group Contribution or null.
    */
   public final Boolean getGrpContribution()
   {
      return _GrpContribution;
   }
	
   /**
    * Gets the Group Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Contribution or the specified default value.
    */
   public final boolean getGrpContribution( boolean defaultValue )
   {
      return _GrpContribution == null ? defaultValue : _GrpContribution.booleanValue();
   }
                  
   /**
    * Gets the Allow Fractions field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Allow Fractions or null.
    */
   public final Boolean getAllowFractions()
   {
      return _AllowFractions;
   }
	
   /**
    * Gets the Allow Fractions field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allow Fractions or the specified default value.
    */
   public final boolean getAllowFractions( boolean defaultValue )
   {
      return _AllowFractions == null ? defaultValue : _AllowFractions.booleanValue();
   }
                  
   /**
    * Gets the Split Comm Trans Types field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Split Comm Trans Types or null.
    */
   public final String getSplitCommTransTypes()
   {
      return _SplitCommTransTypes;
   }
	
   /**
    * Gets the Split Comm Trans Types field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Split Comm Trans Types or the specified default value.
    */
   public final String getSplitCommTransTypes( String defaultValue )
   {
      return _SplitCommTransTypes == null ? defaultValue : _SplitCommTransTypes;
   }
                  
   /**
    * Gets the Cash Receipt Track field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Cash Receipt Track or null.
    */
   public final Boolean getCashReceiptTrack()
   {
      return _CashReceiptTrack;
   }
	
   /**
    * Gets the Cash Receipt Track field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cash Receipt Track or the specified default value.
    */
   public final boolean getCashReceiptTrack( boolean defaultValue )
   {
      return _CashReceiptTrack == null ? defaultValue : _CashReceiptTrack.booleanValue();
   }
                  
   /**
    * Gets the DepositId field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DepositId or null.
    */
   public final Boolean getDepositId()
   {
      return _DepositId;
   }
	
   /**
    * Gets the DepositId field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DepositId or the specified default value.
    */
   public final boolean getDepositId( boolean defaultValue )
   {
      return _DepositId == null ? defaultValue : _DepositId.booleanValue();
   }
                  
   /**
    * Gets the DepositIdMand field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DepositIdMand or null.
    */
   public final String getDepositIdMand()
   {
      return _DepositIdMand;
   }
	
   /**
    * Gets the DepositIdMand field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DepositIdMand or the specified default value.
    */
   public final String getDepositIdMand( String defaultValue )
   {
      return _DepositIdMand == null ? defaultValue : _DepositIdMand;
   }
                  
   /**
    * Gets the DefaultPurchPayType field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the DefaultPurchPayType or null.
    */
   public final String getDefaultPurchPayType()
   {
      return _DefaultPurchPayType;
   }
	
   /**
    * Gets the DefaultPurchPayType field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DefaultPurchPayType or the specified default value.
    */
   public final String getDefaultPurchPayType( String defaultValue )
   {
      return _DefaultPurchPayType == null ? defaultValue : _DefaultPurchPayType;
   }
                  
   /**
    * Gets the EftPurchLeadDays field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EftPurchLeadDays or null.
    */
   public final Integer getEftPurchLeadDays()
   {
      return _EftPurchLeadDays;
   }
	
   /**
    * Gets the EftPurchLeadDays field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EftPurchLeadDays or the specified default value.
    */
   public final int getEftPurchLeadDays( int defaultValue )
   {
      return _EftPurchLeadDays == null ? defaultValue : _EftPurchLeadDays.intValue();
   }
                  
   /**
    * Gets the Wire Number is suppossed to be character field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Wire Number is suppossed to be character or null.
    */
   public final Boolean getCharWireNum()
   {
      return _CharWireNum;
   }
	
   /**
    * Gets the Wire Number is suppossed to be character field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wire Number is suppossed to be character or the specified default value.
    */
   public final boolean getCharWireNum( boolean defaultValue )
   {
      return _CharWireNum == null ? defaultValue : _CharWireNum.booleanValue();
   }
                  
   /**
    * Gets the Wire Number is mandatory field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Wire Number is mandatory or null.
    */
   public final Boolean getWireNumMand()
   {
      return _WireNumMand;
   }
	
   /**
    * Gets the Wire Number is mandatory field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wire Number is mandatory or the specified default value.
    */
   public final boolean getWireNumMand( boolean defaultValue )
   {
      return _WireNumMand == null ? defaultValue : _WireNumMand.booleanValue();
   }
                  
   /**
    * Gets the Wire number is defaulting to trans number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Wire number is defaulting to trans number or null.
    */
   public final Boolean getWireNoDefault()
   {
      return _WireNoDefault;
   }
	
   /**
    * Gets the Wire number is defaulting to trans number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wire number is defaulting to trans number or the specified default value.
    */
   public final boolean getWireNoDefault( boolean defaultValue )
   {
      return _WireNoDefault == null ? defaultValue : _WireNoDefault.booleanValue();
   }
                  
   /**
    * Gets the Source of fund mandatory field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Source of fund mandatory or null.
    */
   public final Boolean getSrcOfFundMandatory()
   {
      return _SrcOfFundMandatory;
   }
	
   /**
    * Gets the Source of fund mandatory field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of fund mandatory or the specified default value.
    */
   public final boolean getSrcOfFundMandatory( boolean defaultValue )
   {
      return _SrcOfFundMandatory == null ? defaultValue : _SrcOfFundMandatory.booleanValue();
   }
                  
   /**
    * Gets the Previous year RRIF records are updatable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Previous year RRIF records are updatable or null.
    */
   public final Boolean getRRIFPrevYear()
   {
      return _RRIFPrevYear;
   }
	
   /**
    * Gets the Previous year RRIF records are updatable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous year RRIF records are updatable or the specified default value.
    */
   public final boolean getRRIFPrevYear( boolean defaultValue )
   {
      return _RRIFPrevYear == null ? defaultValue : _RRIFPrevYear.booleanValue();
   }
                  
   /**
    * Gets the Payment amount override is allowed for Minimum pay option field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Payment amount override is allowed for Minimum pay option or null.
    */
   public final Boolean getRRIFOrPayment()
   {
      return _RRIFOrPayment;
   }
	
   /**
    * Gets the Payment amount override is allowed for Minimum pay option field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Payment amount override is allowed for Minimum pay option or the specified default value.
    */
   public final boolean getRRIFOrPayment( boolean defaultValue )
   {
      return _RRIFOrPayment == null ? defaultValue : _RRIFOrPayment.booleanValue();
   }
                  
   /**
    * Gets the validate rrif records field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the validate rrif records or null.
    */
   public final Boolean getRRIFValidation()
   {
      return _RRIFValidation;
   }
	
   /**
    * Gets the validate rrif records field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the validate rrif records or the specified default value.
    */
   public final boolean getRRIFValidation( boolean defaultValue )
   {
      return _RRIFValidation == null ? defaultValue : _RRIFValidation.booleanValue();
   }
                  
   /**
    * Gets the Funds limit on allocations field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Funds limit on allocations or null.
    */
   public final Integer getFundAllocLimit()
   {
      return _FundAllocLimit;
   }
	
   /**
    * Gets the Funds limit on allocations field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Funds limit on allocations or the specified default value.
    */
   public final int getFundAllocLimit( int defaultValue )
   {
      return _FundAllocLimit == null ? defaultValue : _FundAllocLimit.intValue();
   }
                  
   /**
    * Gets the AMS client field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AMS client or null.
    */
   public final Boolean getAMSOrder()
   {
      return _AMSOrder;
   }
	
   /**
    * Gets the AMS client field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS client or the specified default value.
    */
   public final boolean getAMSOrder( boolean defaultValue )
   {
      return _AMSOrder == null ? defaultValue : _AMSOrder.booleanValue();
   }
                  
   /**
    * Gets the Default settlement currency to Client's report currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default settlement currency to Client's report currency or null.
    */
   public final Boolean getDefSetlCurr()
   {
      return _DefSetlCurr;
   }
	
   /**
    * Gets the Default settlement currency to Client's report currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default settlement currency to Client's report currency or the specified default value.
    */
   public final boolean getDefSetlCurr( boolean defaultValue )
   {
      return _DefSetlCurr == null ? defaultValue : _DefSetlCurr.booleanValue();
   }
                  
   /**
    * Gets the Previous Business Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Previous Business Date or null.
    */
   public final Date getPrevBusDate()
   {
      return _PrevBusDate;
   }
	
   /**
    * Gets the Previous Business Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Previous Business Date or the specified default value.
    */
   public final Date getPrevBusDate( Date defaultValue )
   {
      return _PrevBusDate == null ? defaultValue : _PrevBusDate;
   }
                  
   /**
    * Gets the Currency Check by Tax Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Currency Check by Tax Type or null.
    */
   public final Boolean getCurrCheckByTaxType()
   {
      return _CurrCheckByTaxType;
   }
	
   /**
    * Gets the Currency Check by Tax Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Check by Tax Type or the specified default value.
    */
   public final boolean getCurrCheckByTaxType( boolean defaultValue )
   {
      return _CurrCheckByTaxType == null ? defaultValue : _CurrCheckByTaxType.booleanValue();
   }
                  
   /**
    * Gets the European Address Format field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the European Address Format or null.
    */
   public final Boolean getEuropAddrFormat()
   {
      return _EuropAddrFormat;
   }
	
   /**
    * Gets the European Address Format field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the European Address Format or the specified default value.
    */
   public final boolean getEuropAddrFormat( boolean defaultValue )
   {
      return _EuropAddrFormat == null ? defaultValue : _EuropAddrFormat.booleanValue();
   }
                  
   /**
    * Gets the Invalid Currency field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Invalid Currency or null.
    */
   public final String getInvalidCurr()
   {
      return _InvalidCurr;
   }
	
   /**
    * Gets the Invalid Currency field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Invalid Currency or the specified default value.
    */
   public final String getInvalidCurr( String defaultValue )
   {
      return _InvalidCurr == null ? defaultValue : _InvalidCurr;
   }
                  
   /**
    * Gets the Tax Type by Currency Check field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Type by Currency Check or null.
    */
   public final String getTaxTypeByCurrCheck()
   {
      return _TaxTypeByCurrCheck;
   }
	
   /**
    * Gets the Tax Type by Currency Check field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type by Currency Check or the specified default value.
    */
   public final String getTaxTypeByCurrCheck( String defaultValue )
   {
      return _TaxTypeByCurrCheck == null ? defaultValue : _TaxTypeByCurrCheck;
   }
                  
   /**
    * Gets the Flag indicating if client has access to product seg field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if client has access to product seg or null.
    */
   public final Boolean getSegClient()
   {
      return _SegClient;
   }
	
   /**
    * Gets the Flag indicating if client has access to product seg field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if client has access to product seg or the specified default value.
    */
   public final boolean getSegClient( boolean defaultValue )
   {
      return _SegClient == null ? defaultValue : _SegClient.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if client has access to product cot field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if client has access to product cot or null.
    */
   public final Boolean getCotClient()
   {
      return _CotClient;
   }
	
   /**
    * Gets the Flag indicating if client has access to product cot field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if client has access to product cot or the specified default value.
    */
   public final boolean getCotClient( boolean defaultValue )
   {
      return _CotClient == null ? defaultValue : _CotClient.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if client has access to product res field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if client has access to product res or null.
    */
   public final Boolean getResClient()
   {
      return _ResClient;
   }
	
   /**
    * Gets the Flag indicating if client has access to product res field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if client has access to product res or the specified default value.
    */
   public final boolean getResClient( boolean defaultValue )
   {
      return _ResClient == null ? defaultValue : _ResClient.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if client has access to product lip field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if client has access to product lip or null.
    */
   public final Boolean getLipClient()
   {
      return _LipClient;
   }
	
   /**
    * Gets the Flag indicating if client has access to product lip field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if client has access to product lip or the specified default value.
    */
   public final boolean getLipClient( boolean defaultValue )
   {
      return _LipClient == null ? defaultValue : _LipClient.booleanValue();
   }
                  
   /**
    * Gets the Flag indication amendment/exception based T550 Registration Listing field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indication amendment/exception based T550 Registration Listing or null.
    */
   public final Boolean getT550ReportMethod()
   {
      return _T550ReportMethod;
   }
	
   /**
    * Gets the Flag indication amendment/exception based T550 Registration Listing field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indication amendment/exception based T550 Registration Listing or the specified default value.
    */
   public final boolean getT550ReportMethod( boolean defaultValue )
   {
      return _T550ReportMethod == null ? defaultValue : _T550ReportMethod.booleanValue();
   }
                  
   /**
    * Gets the Consolidated EFT field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Consolidated EFT or null.
    */
   public final Boolean getShrEftConsol()
   {
      return _ShrEftConsol;
   }
	
   /**
    * Gets the Consolidated EFT field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consolidated EFT or the specified default value.
    */
   public final boolean getShrEftConsol( boolean defaultValue )
   {
      return _ShrEftConsol == null ? defaultValue : _ShrEftConsol.booleanValue();
   }
                  
   /**
    * Gets the PAC Consolidate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PAC Consolidate or null.
    */
   public final Boolean getPacSwpEftConsol()
   {
      return _PacSwpEftConsol;
   }
	
   /**
    * Gets the PAC Consolidate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC Consolidate or the specified default value.
    */
   public final boolean getPacSwpEftConsol( boolean defaultValue )
   {
      return _PacSwpEftConsol == null ? defaultValue : _PacSwpEftConsol.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if client has limited access to Unseizable Accounts field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if client has limited access to Unseizable Accounts or null.
    */
   public final Boolean getUnseizable()
   {
      return _Unseizable;
   }
	
   /**
    * Gets the Flag indicating if client has limited access to Unseizable Accounts field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if client has limited access to Unseizable Accounts or the specified default value.
    */
   public final boolean getUnseizable( boolean defaultValue )
   {
      return _Unseizable == null ? defaultValue : _Unseizable.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if redemption is allowed on Locked-In Accounts field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if redemption is allowed on Locked-In Accounts or null.
    */
   public final Boolean getRdLckdE()
   {
      return _RdLckdE;
   }
	
   /**
    * Gets the Flag indicating if redemption is allowed on Locked-In Accounts field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if redemption is allowed on Locked-In Accounts or the specified default value.
    */
   public final boolean getRdLckdE( boolean defaultValue )
   {
      return _RdLckdE == null ? defaultValue : _RdLckdE.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating Edit/Warning Message for redeeming from Locked-In Account field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating Edit/Warning Message for redeeming from Locked-In Account or null.
    */
   public final Boolean getRdLckdW()
   {
      return _RdLckdW;
   }
	
   /**
    * Gets the Flag indicating Edit/Warning Message for redeeming from Locked-In Account field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating Edit/Warning Message for redeeming from Locked-In Account or the specified default value.
    */
   public final boolean getRdLckdW( boolean defaultValue )
   {
      return _RdLckdW == null ? defaultValue : _RdLckdW.booleanValue();
   }
                  
   /**
    * Gets the Title Restrictions Edits field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Title Restrictions Edits or null.
    */
   public final Boolean getTitleRestrict()
   {
      return _TitleRestrict;
   }
	
   /**
    * Gets the Title Restrictions Edits field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Title Restrictions Edits or the specified default value.
    */
   public final boolean getTitleRestrict( boolean defaultValue )
   {
      return _TitleRestrict == null ? defaultValue : _TitleRestrict.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if trade can be process with date greater than 365 days field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if trade can be process with date greater than 365 days or null.
    */
   public final Boolean getEditDeffs()
   {
      return _EditDeffs;
   }
	
   /**
    * Gets the Flag indicating if trade can be process with date greater than 365 days field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if trade can be process with date greater than 365 days or the specified default value.
    */
   public final boolean getEditDeffs( boolean defaultValue )
   {
      return _EditDeffs == null ? defaultValue : _EditDeffs.booleanValue();
   }
                  
   /**
    * Gets the Flag that indicates if purchase will be rounded Up or Down field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag that indicates if purchase will be rounded Up or Down or null.
    */
   public final Boolean getRoundFlag()
   {
      return _RoundFlag;
   }
	
   /**
    * Gets the Flag that indicates if purchase will be rounded Up or Down field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if purchase will be rounded Up or Down or the specified default value.
    */
   public final boolean getRoundFlag( boolean defaultValue )
   {
      return _RoundFlag == null ? defaultValue : _RoundFlag.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating Redemption of Interest for Money Market Fund of Omnibus field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating Redemption of Interest for Money Market Fund of Omnibus or null.
    */
   public final Boolean getRedAccruedInt()
   {
      return _RedAccruedInt;
   }
	
   /**
    * Gets the Flag indicating Redemption of Interest for Money Market Fund of Omnibus field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating Redemption of Interest for Money Market Fund of Omnibus or the specified default value.
    */
   public final boolean getRedAccruedInt( boolean defaultValue )
   {
      return _RedAccruedInt == null ? defaultValue : _RedAccruedInt.booleanValue();
   }
                  
   /**
    * Gets the PQLIF/LIRAFullRedReq - Red Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PQLIF/LIRAFullRedReq - Red Code or null.
    */
   public final String getPQLIFLIRARedCodes()
   {
      return _PQLIFLIRARedCodes;
   }
	
   /**
    * Gets the PQLIF/LIRAFullRedReq - Red Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PQLIF/LIRAFullRedReq - Red Code or the specified default value.
    */
   public final String getPQLIFLIRARedCodes( String defaultValue )
   {
      return _PQLIFLIRARedCodes == null ? defaultValue : _PQLIFLIRARedCodes;
   }
                  
   /**
    * Gets the PQLIF/LIRAFullRedReq - Juris field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PQLIF/LIRAFullRedReq - Juris or null.
    */
   public final String getPQLIFLIRAJuris()
   {
      return _PQLIFLIRAJuris;
   }
	
   /**
    * Gets the PQLIF/LIRAFullRedReq - Juris field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PQLIF/LIRAFullRedReq - Juris or the specified default value.
    */
   public final String getPQLIFLIRAJuris( String defaultValue )
   {
      return _PQLIFLIRAJuris == null ? defaultValue : _PQLIFLIRAJuris;
   }
                  
   /**
    * Gets the PQLIF/LIRAFullRedReq -  Age field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PQLIF/LIRAFullRedReq -  Age or null.
    */
   public final Integer getPQLIFLIRAAge()
   {
      return _PQLIFLIRAAge;
   }
	
   /**
    * Gets the PQLIF/LIRAFullRedReq -  Age field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PQLIF/LIRAFullRedReq -  Age or the specified default value.
    */
   public final int getPQLIFLIRAAge( int defaultValue )
   {
      return _PQLIFLIRAAge == null ? defaultValue : _PQLIFLIRAAge.intValue();
   }
                  
   /**
    * Gets the PQLIF/LIRAFullRedReq - % MPE field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PQLIF/LIRAFullRedReq - % MPE or null.
    */
   public final Integer getPQLIFLIRAMaxPrct()
   {
      return _PQLIFLIRAMaxPrct;
   }
	
   /**
    * Gets the PQLIF/LIRAFullRedReq - % MPE field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PQLIF/LIRAFullRedReq - % MPE or the specified default value.
    */
   public final int getPQLIFLIRAMaxPrct( int defaultValue )
   {
      return _PQLIFLIRAMaxPrct == null ? defaultValue : _PQLIFLIRAMaxPrct.intValue();
   }
                  
   /**
    * Gets the PQLIFLIRAFullRedReq - TaxType field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PQLIFLIRAFullRedReq - TaxType or null.
    */
   public final String getPQLIFLIRATaxType()
   {
      return _PQLIFLIRATaxType;
   }
	
   /**
    * Gets the PQLIFLIRAFullRedReq - TaxType field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PQLIFLIRAFullRedReq - TaxType or the specified default value.
    */
   public final String getPQLIFLIRATaxType( String defaultValue )
   {
      return _PQLIFLIRATaxType == null ? defaultValue : _PQLIFLIRATaxType;
   }
                  
   /**
    * Gets the Auto Banking field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Auto Banking or null.
    */
   public final Boolean getAutoBanking()
   {
      return _AutoBanking;
   }
	
   /**
    * Gets the Auto Banking field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Auto Banking or the specified default value.
    */
   public final boolean getAutoBanking( boolean defaultValue )
   {
      return _AutoBanking == null ? defaultValue : _AutoBanking.booleanValue();
   }
                  
   /**
    * Gets the Defaukt Settle Currency with Acct currency for redemption field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Defaukt Settle Currency with Acct currency for redemption or null.
    */
   public final Boolean getRdAcctCurrency()
   {
      return _RdAcctCurrency;
   }
	
   /**
    * Gets the Defaukt Settle Currency with Acct currency for redemption field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Defaukt Settle Currency with Acct currency for redemption or the specified default value.
    */
   public final boolean getRdAcctCurrency( boolean defaultValue )
   {
      return _RdAcctCurrency == null ? defaultValue : _RdAcctCurrency.booleanValue();
   }
                  
   /**
    * Gets the Indicates if  client use srcaccount for EURO Banking field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Indicates if  client use srcaccount for EURO Banking or null.
    */
   public final Boolean getBankSrcAcct()
   {
      return _BankSrcAcct;
   }
	
   /**
    * Gets the Indicates if  client use srcaccount for EURO Banking field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if  client use srcaccount for EURO Banking or the specified default value.
    */
   public final boolean getBankSrcAcct( boolean defaultValue )
   {
      return _BankSrcAcct == null ? defaultValue : _BankSrcAcct.booleanValue();
   }
                  
   /**
    * Gets the Source of Fund field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Source of Fund or null.
    */
   public final Boolean getSourceOfFund()
   {
      return _SourceOfFund;
   }
	
   /**
    * Gets the Source of Fund field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of Fund or the specified default value.
    */
   public final boolean getSourceOfFund( boolean defaultValue )
   {
      return _SourceOfFund == null ? defaultValue : _SourceOfFund.booleanValue();
   }
                  
   /**
    * Gets the Recipient Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Recipient Type or null.
    */
   public final Boolean getModRecipType()
   {
      return _ModRecipType;
   }
	
   /**
    * Gets the Recipient Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recipient Type or the specified default value.
    */
   public final boolean getModRecipType( boolean defaultValue )
   {
      return _ModRecipType == null ? defaultValue : _ModRecipType.booleanValue();
   }
                  
   /**
    * Gets the Wire Order Account Numbers field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Wire Order Account Numbers or null.
    */
   public final String getSpecAcctNum()
   {
      return _SpecAcctNum;
   }
	
   /**
    * Gets the Wire Order Account Numbers field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Wire Order Account Numbers or the specified default value.
    */
   public final String getSpecAcctNum( String defaultValue )
   {
      return _SpecAcctNum == null ? defaultValue : _SpecAcctNum;
   }
                  
   /**
    * Gets the Trading Cut Off Time Parameters field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Trading Cut Off Time Parameters or null.
    */
   public final Boolean getTradeCutOff()
   {
      return _TradeCutOff;
   }
	
   /**
    * Gets the Trading Cut Off Time Parameters field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trading Cut Off Time Parameters or the specified default value.
    */
   public final boolean getTradeCutOff( boolean defaultValue )
   {
      return _TradeCutOff == null ? defaultValue : _TradeCutOff.booleanValue();
   }
                  
   /**
    * Gets the Indicates if Sytem feature "PartTransAsFull" is active field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Indicates if Sytem feature "PartTransAsFull" is active or null.
    */
   public final Boolean getPartTransAsFull()
   {
      return _PartTransAsFull;
   }
	
   /**
    * Gets the Indicates if Sytem feature "PartTransAsFull" is active field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates if Sytem feature "PartTransAsFull" is active or the specified default value.
    */
   public final boolean getPartTransAsFull( boolean defaultValue )
   {
      return _PartTransAsFull == null ? defaultValue : _PartTransAsFull.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating Generic Control "Cheque Delivery Method" control is available field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating Generic Control "Cheque Delivery Method" control is available or null.
    */
   public final String getDelivDeflt()
   {
      return _DelivDeflt;
   }
	
   /**
    * Gets the Flag indicating Generic Control "Cheque Delivery Method" control is available field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating Generic Control "Cheque Delivery Method" control is available or the specified default value.
    */
   public final String getDelivDeflt( String defaultValue )
   {
      return _DelivDeflt == null ? defaultValue : _DelivDeflt;
   }
                  
   /**
    * Gets the Flag indicating if SplitComm is assigned field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if SplitComm is assigned or null.
    */
   public final Boolean getSplit100()
   {
      return _Split100;
   }
	
   /**
    * Gets the Flag indicating if SplitComm is assigned field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if SplitComm is assigned or the specified default value.
    */
   public final boolean getSplit100( boolean defaultValue )
   {
      return _Split100 == null ? defaultValue : _Split100.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if control "Valid CASH ID Pay Types" exists field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if control "Valid CASH ID Pay Types" exists or null.
    */
   public final Boolean getCashDistRule()
   {
      return _CashDistRule;
   }
	
   /**
    * Gets the Flag indicating if control "Valid CASH ID Pay Types" exists field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if control "Valid CASH ID Pay Types" exists or the specified default value.
    */
   public final boolean getCashDistRule( boolean defaultValue )
   {
      return _CashDistRule == null ? defaultValue : _CashDistRule.booleanValue();
   }
                  
   /**
    * Gets the Valid CASH ID Pay Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Valid CASH ID Pay Type or null.
    */
   public final String getValidDistPayTypes()
   {
      return _ValidDistPayTypes;
   }
	
   /**
    * Gets the Valid CASH ID Pay Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Valid CASH ID Pay Type or the specified default value.
    */
   public final String getValidDistPayTypes( String defaultValue )
   {
      return _ValidDistPayTypes == null ? defaultValue : _ValidDistPayTypes;
   }
                  
   /**
    * Gets the All Funds Transfers field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the All Funds Transfers or null.
    */
   public final Boolean getAllFundsTransfers()
   {
      return _AllFundsTransfers;
   }
	
   /**
    * Gets the All Funds Transfers field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the All Funds Transfers or the specified default value.
    */
   public final boolean getAllFundsTransfers( boolean defaultValue )
   {
      return _AllFundsTransfers == null ? defaultValue : _AllFundsTransfers.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if Transfer from registered acct to diff shareholder field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if Transfer from registered acct to diff shareholder or null.
    */
   public final Boolean getTfrToDiffSH()
   {
      return _TfrToDiffSH;
   }
	
   /**
    * Gets the Flag indicating if Transfer from registered acct to diff shareholder field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Transfer from registered acct to diff shareholder or the specified default value.
    */
   public final boolean getTfrToDiffSH( boolean defaultValue )
   {
      return _TfrToDiffSH == null ? defaultValue : _TfrToDiffSH.booleanValue();
   }
                  
   /**
    * Gets the List of the valid Death Claim Redemption field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the List of the valid Death Claim Redemption or null.
    */
   public final String getDeathRedCode()
   {
      return _DeathRedCode;
   }
	
   /**
    * Gets the List of the valid Death Claim Redemption field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the List of the valid Death Claim Redemption or the specified default value.
    */
   public final String getDeathRedCode( String defaultValue )
   {
      return _DeathRedCode == null ? defaultValue : _DeathRedCode;
   }
                  
   /**
    * Gets the Codes for RRSP and RRIF Spouse beneficiaries field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Codes for RRSP and RRIF Spouse beneficiaries or null.
    */
   public final String getSpouseBenefReln()
   {
      return _SpouseBenefReln;
   }
	
   /**
    * Gets the Codes for RRSP and RRIF Spouse beneficiaries field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Codes for RRSP and RRIF Spouse beneficiaries or the specified default value.
    */
   public final String getSpouseBenefReln( String defaultValue )
   {
      return _SpouseBenefReln == null ? defaultValue : _SpouseBenefReln;
   }
                  
   /**
    * Gets the Codes for RRSP and RRIF Child beneficiaries field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Codes for RRSP and RRIF Child beneficiaries or null.
    */
   public final String getChildBenefReln()
   {
      return _ChildBenefReln;
   }
	
   /**
    * Gets the Codes for RRSP and RRIF Child beneficiaries field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Codes for RRSP and RRIF Child beneficiaries or the specified default value.
    */
   public final String getChildBenefReln( String defaultValue )
   {
      return _ChildBenefReln == null ? defaultValue : _ChildBenefReln;
   }
                  
   /**
    * Gets the Flag indicating if Shareholder Relation is 1 to 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if Shareholder Relation is 1 to 1 or null.
    */
   public final Boolean getMultiAcctEachShrNum()
   {
      return _MultiAcctEachShrNum;
   }
	
   /**
    * Gets the Flag indicating if Shareholder Relation is 1 to 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Shareholder Relation is 1 to 1 or the specified default value.
    */
   public final boolean getMultiAcctEachShrNum( boolean defaultValue )
   {
      return _MultiAcctEachShrNum == null ? defaultValue : _MultiAcctEachShrNum.booleanValue();
   }
                  
   /**
    * Gets the Flag which permits update of Order Type field on trade entry screens field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag which permits update of Order Type field on trade entry screens or null.
    */
   public final Boolean getUpdOrdType()
   {
      return _UpdOrdType;
   }
	
   /**
    * Gets the Flag which permits update of Order Type field on trade entry screens field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag which permits update of Order Type field on trade entry screens or the specified default value.
    */
   public final boolean getUpdOrdType( boolean defaultValue )
   {
      return _UpdOrdType == null ? defaultValue : _UpdOrdType.booleanValue();
   }
                  
   /**
    * Gets the Commission Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Commission Type or null.
    */
   public final Integer getCommissionType()
   {
      return _CommissionType;
   }
	
   /**
    * Gets the Commission Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commission Type or the specified default value.
    */
   public final int getCommissionType( int defaultValue )
   {
      return _CommissionType == null ? defaultValue : _CommissionType.intValue();
   }
                  
   /**
    * Gets the Residency field 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Residency field 1 or null.
    */
   public final String getResidency1()
   {
      return _Residency1;
   }
	
   /**
    * Gets the Residency field 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Residency field 1 or the specified default value.
    */
   public final String getResidency1( String defaultValue )
   {
      return _Residency1 == null ? defaultValue : _Residency1;
   }
                  
   /**
    * Gets the Residency field 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Residency field 2 or null.
    */
   public final String getResidency2()
   {
      return _Residency2;
   }
	
   /**
    * Gets the Residency field 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Residency field 2 or the specified default value.
    */
   public final String getResidency2( String defaultValue )
   {
      return _Residency2 == null ? defaultValue : _Residency2;
   }
                  
   /**
    * Gets the Residency field 3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Residency field 3 or null.
    */
   public final String getResidency3()
   {
      return _Residency3;
   }
	
   /**
    * Gets the Residency field 3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Residency field 3 or the specified default value.
    */
   public final String getResidency3( String defaultValue )
   {
      return _Residency3 == null ? defaultValue : _Residency3;
   }
                  
   /**
    * Gets the Default Redemption Code Enabled field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Redemption Code Enabled or null.
    */
   public final Boolean getDefltRedCodeFlag()
   {
      return _DefltRedCodeFlag;
   }
	
   /**
    * Gets the Default Redemption Code Enabled field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Redemption Code Enabled or the specified default value.
    */
   public final boolean getDefltRedCodeFlag( boolean defaultValue )
   {
      return _DefltRedCodeFlag == null ? defaultValue : _DefltRedCodeFlag.booleanValue();
   }
                  
   /**
    * Gets the Default Redemption Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Default Redemption Code or null.
    */
   public final String getDefltRedCode()
   {
      return _DefltRedCode;
   }
	
   /**
    * Gets the Default Redemption Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Default Redemption Code or the specified default value.
    */
   public final String getDefltRedCode( String defaultValue )
   {
      return _DefltRedCode == null ? defaultValue : _DefltRedCode;
   }
                  
   /**
    * Gets the Flag indicating that sls rep will  be validated if it is eligible to deal  with the fund field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating that sls rep will  be validated if it is eligible to deal  with the fund or null.
    */
   public final Boolean getFundEligSlsRepLvl()
   {
      return _FundEligSlsRepLvl;
   }
	
   /**
    * Gets the Flag indicating that sls rep will  be validated if it is eligible to deal  with the fund field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating that sls rep will  be validated if it is eligible to deal  with the fund or the specified default value.
    */
   public final boolean getFundEligSlsRepLvl( boolean defaultValue )
   {
      return _FundEligSlsRepLvl == null ? defaultValue : _FundEligSlsRepLvl.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if Wrap Column is to be displayed on Account Verify screen field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if Wrap Column is to be displayed on Account Verify screen or null.
    */
   public final Boolean getWrapAccount()
   {
      return _WrapAccount;
   }
	
   /**
    * Gets the Flag indicating if Wrap Column is to be displayed on Account Verify screen field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Wrap Column is to be displayed on Account Verify screen or the specified default value.
    */
   public final boolean getWrapAccount( boolean defaultValue )
   {
      return _WrapAccount == null ? defaultValue : _WrapAccount.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if funds will be validated against Allowable Tranfers Table field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if funds will be validated against Allowable Tranfers Table or null.
    */
   public final Boolean getDistribFundsValidate()
   {
      return _DistribFundsValidate;
   }
	
   /**
    * Gets the Flag indicating if funds will be validated against Allowable Tranfers Table field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if funds will be validated against Allowable Tranfers Table or the specified default value.
    */
   public final boolean getDistribFundsValidate( boolean defaultValue )
   {
      return _DistribFundsValidate == null ? defaultValue : _DistribFundsValidate.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if target fund will be validated against fund groups field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if target fund will be validated against fund groups or null.
    */
   public final Boolean getXSFundsValidate()
   {
      return _XSFundsValidate;
   }
	
   /**
    * Gets the Flag indicating if target fund will be validated against fund groups field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if target fund will be validated against fund groups or the specified default value.
    */
   public final boolean getXSFundsValidate( boolean defaultValue )
   {
      return _XSFundsValidate == null ? defaultValue : _XSFundsValidate.booleanValue();
   }
                  
   /**
    * Gets the AMS Type supported by client field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AMS Type supported by client or null.
    */
   public final String getClientAMSType()
   {
      return _ClientAMSType;
   }
	
   /**
    * Gets the AMS Type supported by client field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AMS Type supported by client or the specified default value.
    */
   public final String getClientAMSType( String defaultValue )
   {
      return _ClientAMSType == null ? defaultValue : _ClientAMSType;
   }
                  
   /**
    * Gets the Class Rule field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Class Rule or null.
    */
   public final Integer getClassRule()
   {
      return _ClassRule;
   }
	
   /**
    * Gets the Class Rule field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Rule or the specified default value.
    */
   public final int getClassRule( int defaultValue )
   {
      return _ClassRule == null ? defaultValue : _ClassRule.intValue();
   }
                  
   /**
    * Gets the Profile Code Default field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Profile Code Default or null.
    */
   public final String getProfileCodeDflt()
   {
      return _ProfileCodeDflt;
   }
	
   /**
    * Gets the Profile Code Default field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Profile Code Default or the specified default value.
    */
   public final String getProfileCodeDflt( String defaultValue )
   {
      return _ProfileCodeDflt == null ? defaultValue : _ProfileCodeDflt;
   }
                  
   /**
    * Gets the Mgmt Fee Payment Option Default value field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mgmt Fee Payment Option Default value or null.
    */
   public final String getMgmtFeePayOptDflt()
   {
      return _MgmtFeePayOptDflt;
   }
	
   /**
    * Gets the Mgmt Fee Payment Option Default value field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mgmt Fee Payment Option Default value or the specified default value.
    */
   public final String getMgmtFeePayOptDflt( String defaultValue )
   {
      return _MgmtFeePayOptDflt == null ? defaultValue : _MgmtFeePayOptDflt;
   }
                  
   /**
    * Gets the Flag indicating if Mgmt Company will be paid commission field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if Mgmt Company will be paid commission or null.
    */
   public final Boolean getMgmtCoPayReq()
   {
      return _MgmtCoPayReq;
   }
	
   /**
    * Gets the Flag indicating if Mgmt Company will be paid commission field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Mgmt Company will be paid commission or the specified default value.
    */
   public final boolean getMgmtCoPayReq( boolean defaultValue )
   {
      return _MgmtCoPayReq == null ? defaultValue : _MgmtCoPayReq.booleanValue();
   }
                  
   /**
    * Gets the Option for configuration on the split preference field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Option for configuration on the split preference or null.
    */
   public final Integer getSplitPreferenceOption()
   {
      return _SplitPreferenceOption;
   }
	
   /**
    * Gets the Option for configuration on the split preference field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Option for configuration on the split preference or the specified default value.
    */
   public final int getSplitPreferenceOption( int defaultValue )
   {
      return _SplitPreferenceOption == null ? defaultValue : _SplitPreferenceOption.intValue();
   }
                  
   /**
    * Gets the Flag indicates env support RESP 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicates env support RESP 2 or null.
    */
   public final Boolean getRES2Client()
   {
      return _RES2Client;
   }
	
   /**
    * Gets the Flag indicates env support RESP 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates env support RESP 2 or the specified default value.
    */
   public final boolean getRES2Client( boolean defaultValue )
   {
      return _RES2Client == null ? defaultValue : _RES2Client.booleanValue();
   }
                  
   /**
    * Gets the Flag indicating if QESI functionality is active field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if QESI functionality is active or null.
    */
   public final Boolean getQESIClient()
   {
      return _QESIClient;
   }
	
   /**
    * Gets the Flag indicating if QESI functionality is active field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if QESI functionality is active or the specified default value.
    */
   public final boolean getQESIClient( boolean defaultValue )
   {
      return _QESIClient == null ? defaultValue : _QESIClient.booleanValue();
   }
                  
   /**
    * Gets the Effective date of HRDC Interface Transaction Standard 3.0.1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective date of HRDC Interface Transaction Standard 3.0.1 or null.
    */
   public final Date getPSEEAPEditDate()
   {
      return _PSEEAPEditDate;
   }
	
   /**
    * Gets the Effective date of HRDC Interface Transaction Standard 3.0.1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective date of HRDC Interface Transaction Standard 3.0.1 or the specified default value.
    */
   public final Date getPSEEAPEditDate( Date defaultValue )
   {
      return _PSEEAPEditDate == null ? defaultValue : _PSEEAPEditDate;
   }
                  
   /**
    * Gets the Eligible Date for CLB field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Eligible Date for CLB or null.
    */
   public final Date getEligDateforCLB()
   {
      return _EligDateforCLB;
   }
	
   /**
    * Gets the Eligible Date for CLB field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Eligible Date for CLB or the specified default value.
    */
   public final Date getEligDateforCLB( Date defaultValue )
   {
      return _EligDateforCLB == null ? defaultValue : _EligDateforCLB;
   }
                  
   /**
    * Gets the Non Trustee Start Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Non Trustee Start Date or null.
    */
   public final Date getNonTrustStartDate()
   {
      return _NonTrustStartDate;
   }
	
   /**
    * Gets the Non Trustee Start Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non Trustee Start Date or the specified default value.
    */
   public final Date getNonTrustStartDate( Date defaultValue )
   {
      return _NonTrustStartDate == null ? defaultValue : _NonTrustStartDate;
   }
                  
   /**
    * Gets the Non Trustee Stop Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Non Trustee Stop Date or null.
    */
   public final Date getNonTrustStopDate()
   {
      return _NonTrustStopDate;
   }
	
   /**
    * Gets the Non Trustee Stop Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non Trustee Stop Date or the specified default value.
    */
   public final Date getNonTrustStopDate( Date defaultValue )
   {
      return _NonTrustStopDate == null ? defaultValue : _NonTrustStopDate;
   }
                  
   /**
    * Gets the Flag indicating if Non Trustee trade field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag indicating if Non Trustee trade or null.
    */
   public final Boolean getIsNonTrustee()
   {
      return _IsNonTrustee;
   }
	
   /**
    * Gets the Flag indicating if Non Trustee trade field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Non Trustee trade or the specified default value.
    */
   public final boolean getIsNonTrustee( boolean defaultValue )
   {
      return _IsNonTrustee == null ? defaultValue : _IsNonTrustee.booleanValue();
   }
                  
   /**
    * Gets the Automatically assign regulatory document field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Automatically assign regulatory document or null.
    */
   public final Boolean getAutoDocAssign()
   {
      return _AutoDocAssign;
   }
	
   /**
    * Gets the Automatically assign regulatory document field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Automatically assign regulatory document or the specified default value.
    */
   public final boolean getAutoDocAssign( boolean defaultValue )
   {
      return _AutoDocAssign == null ? defaultValue : _AutoDocAssign.booleanValue();
   }
                  
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      _SysCurrency = responseBuffer.decodeString(responseBuffer.getNextField());
      _ShrNumCtrl = responseBuffer.decodeString(responseBuffer.getNextField());
      _ShrNumVal = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AcctNumCtrl = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctNumVal = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DefaultGrp = responseBuffer.decodeString(responseBuffer.getNextField());
      _GrpCodeLevel = responseBuffer.decodeString(responseBuffer.getNextField());
      _TaxTypeUpd = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _MktMailDef = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RepByBranch = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BrokerBranch = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CapAddress = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CountryVal = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _MandatoryId = responseBuffer.decodeString(responseBuffer.getNextField());
      _BirthNameMand = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ValidSIN = responseBuffer.decodeString(responseBuffer.getNextField());
      _ShadowNominee = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BankValid1 = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _BankValid2 = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BankLayout = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _SYMBrkUpd = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BrokerFund = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PACMinAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _PACAmtEdit = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _GICAllocOnly = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DisableFee4Alloc = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BusRounding = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _MultiCurrency = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SplitComm = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AcctFeeParm = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CappedFund = responseBuffer.decodeString(responseBuffer.getNextField());
      _BankingFormat = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _InstCodeMax = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _TransitNoMax = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _BankAcctNumMax = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _CurrBusDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _MandAddrLines = responseBuffer.decodeString(responseBuffer.getNextField());
      _CurrSysDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _CurrSysTime = responseBuffer.decodeString(responseBuffer.getNextField());
      _CheckDup = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _InvAdvic = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AcqFeeDefaults = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _LastCycleDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _AcCodeMand = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SplitAcCode = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TRExclRedCodes = responseBuffer.decodeString(responseBuffer.getNextField());
      _TIKRedCodes = responseBuffer.decodeString(responseBuffer.getNextField());
      _DealDateTime = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _EFTPurchase = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _EFTPurchFuture = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _GrpContribution = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AllowFractions = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SplitCommTransTypes = responseBuffer.decodeString(responseBuffer.getNextField());
      _CashReceiptTrack = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DepositId = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DepositIdMand = responseBuffer.decodeString(responseBuffer.getNextField());
      _DefaultPurchPayType = responseBuffer.decodeString(responseBuffer.getNextField());
      _EftPurchLeadDays = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _CharWireNum = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _WireNumMand = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _WireNoDefault = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SrcOfFundMandatory = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RRIFPrevYear = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RRIFOrPayment = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RRIFValidation = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _FundAllocLimit = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _AMSOrder = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DefSetlCurr = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PrevBusDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _CurrCheckByTaxType = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _EuropAddrFormat = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _InvalidCurr = responseBuffer.decodeString(responseBuffer.getNextField());
      _TaxTypeByCurrCheck = responseBuffer.decodeString(responseBuffer.getNextField());
      _SegClient = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CotClient = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ResClient = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _LipClient = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _T550ReportMethod = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ShrEftConsol = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PacSwpEftConsol = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _Unseizable = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RdLckdE = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RdLckdW = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TitleRestrict = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _EditDeffs = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RoundFlag = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RedAccruedInt = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PQLIFLIRARedCodes = responseBuffer.decodeString(responseBuffer.getNextField());
      _PQLIFLIRAJuris = responseBuffer.decodeString(responseBuffer.getNextField());
      _PQLIFLIRAAge = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PQLIFLIRAMaxPrct = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PQLIFLIRATaxType = responseBuffer.decodeString(responseBuffer.getNextField());
      _AutoBanking = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _RdAcctCurrency = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BankSrcAcct = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SourceOfFund = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ModRecipType = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SpecAcctNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _TradeCutOff = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PartTransAsFull = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DelivDeflt = responseBuffer.decodeString(responseBuffer.getNextField());
      _Split100 = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CashDistRule = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ValidDistPayTypes = responseBuffer.decodeString(responseBuffer.getNextField());
      _AllFundsTransfers = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TfrToDiffSH = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DeathRedCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _SpouseBenefReln = responseBuffer.decodeString(responseBuffer.getNextField());
      _ChildBenefReln = responseBuffer.decodeString(responseBuffer.getNextField());
      _MultiAcctEachShrNum = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _UpdOrdType = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CommissionType = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _Residency1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _Residency2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _Residency3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _DefltRedCodeFlag = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DefltRedCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundEligSlsRepLvl = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _WrapAccount = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _DistribFundsValidate = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _XSFundsValidate = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ClientAMSType = responseBuffer.decodeString(responseBuffer.getNextField());
      _ClassRule = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _ProfileCodeDflt = responseBuffer.decodeString(responseBuffer.getNextField());
      _MgmtFeePayOptDflt = responseBuffer.decodeString(responseBuffer.getNextField());
      _MgmtCoPayReq = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SplitPreferenceOption = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _RES2Client = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _QESIClient = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _PSEEAPEditDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _EligDateforCLB = responseBuffer.decodeDate(responseBuffer.getNextField());
      _NonTrustStartDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _NonTrustStopDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _IsNonTrustee = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AutoDocAssign = responseBuffer.decodeBoolean(responseBuffer.getNextField());
                  

   }

}
      
