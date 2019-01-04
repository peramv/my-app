
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account Informaiton view.
 * For additional view information see <A HREF="../../../../viewspecs/AccountInformation.doc">AccountInformation.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountInformationView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Account number member array.
    */
   private String[] _AccountNum = null;
   
   /**
    * Benifical owner member array.
    */
   private String[] _BeneficialOwner = null;
   
   /**
    * Alternate account number member array.
    */
   private String[] _AltAccount = null;
   
   /**
    * Account type code member array.
    */
   private String[] _AcctType = null;
   
   /**
    * Account type description member array.
    */
   private String[] _AcctTypeDesc = null;
   
   /**
    * Tax type member array.
    */
   private String[] _TaxType = null;
   
   /**
    * Tax type description member array.
    */
   private String[] _TaxTypeDesc = null;
   
   /**
    * Recipient Type member array.
    */
   private String[] _RecipientType = null;
   
   /**
    * Recipient Type Description member array.
    */
   private String[] _RecipientTypeDesc = null;
   
   /**
    * Account Designation member array.
    */
   private String[] _AcctDesignation = null;
   
   /**
    * Account Designation Description member array.
    */
   private String[] _AcctDesignationDesc = null;
   
   /**
    * Currency Code member array.
    */
   private String[] _Currency = null;
   
   /**
    * Currency Name member array.
    */
   private String[] _CurrencyName = null;
   
   /**
    * Cross Reference Number member array.
    */
   private String[] _XrefNum = null;
   
   /**
    * Broker Code member array.
    */
   private String[] _BrokerCode = null;
   
   /**
    * Branch Code member array.
    */
   private String[] _BranchCode = null;
   
   /**
    * Salesrep Code member array.
    */
   private String[] _Slsrep = null;
   
   /**
    * Intermediary Code member array.
    */
   private String[] _InterCode = null;
   
   /**
    * Intermediary Account member array.
    */
   private String[] _InterAccount = null;
   
   /**
    * Account Status member array.
    */
   private String[] _AcctStatus = null;
   
   /**
    * Account Status Description member array.
    */
   private String[] _AcctStatusDesc = null;
   
   /**
    * Date of Registration member array.
    */
   private Date[] _DateOfReg = null;
   
   /**
    * RRSP Fee Indicator member array.
    */
   private String[] _RRSPFee = null;
   
   /**
    * RRSP Fee Indicator Description member array.
    */
   private String[] _RRSPFeeDesc = null;
   
   /**
    * Asset Management Code member array.
    */
   private String[] _AMSCode = null;
   
   /**
    * Pension Jurisdiction member array.
    */
   private String[] _PensionJuris = null;
   
   /**
    * Pension Jurisdiction Description member array.
    */
   private String[] _PensionJurisDesc = null;
   
   /**
    * Stop Purchase member array.
    */
   private Boolean[] _StopPurchase = null;
   
   /**
    * Stop Transfer In member array.
    */
   private Boolean[] _StopXferIn = null;
   
   /**
    * Stop Transfer Out member array.
    */
   private Boolean[] _StopXferOut = null;
   
   /**
    * Stop Redemption member array.
    */
   private Boolean[] _StopRed = null;
   
   /**
    * Fee Waived member array.
    */
   private Boolean[] _FeeWaived = null;
   
   /**
    * Market Mailing member array.
    */
   private Boolean[] _MarketMail = null;
   
   /**
    * Unseizable member array.
    */
   private Boolean[] _Unseizable = null;
   
   /**
    * Registration Completed member array.
    */
   private Boolean[] _RegCompleted = null;
   
   /**
    * Suppress All Confirm member array.
    */
   private Boolean[] _SupConf = null;
   
   /**
    * Suppress Employee Confirm member array.
    */
   private Boolean[] _SupEmpConf = null;
   
   /**
    * In Trust For member array.
    */
   private Boolean[] _InTrustFor = null;
   
   /**
    * Escrow member array.
    */
   private Boolean[] _Escrow = null;
   
   /**
    * Group member array.
    */
   private String[] _AcctGroup = null;
   
   /**
    * Group Name member array.
    */
   private String[] _AcctGroupName = null;
   
   /**
    * Broker's Name member array.
    */
   private String[] _BrokerName = null;
   
   /**
    * Branch's Name member array.
    */
   private String[] _BranchName = null;
   
   /**
    * Salesrep's Name member array.
    */
   private String[] _SlsrepName = null;
   
   /**
    * Salesrep Alternate Name member array.
    */
   private String[] _SlsrepAltName = null;
   
   /**
    * Account Settled Balance in $ member array.
    */
   private String[] _AccountBalance = null;
   
   /**
    * Shareholder Number member array.
    */
   private String[] _ShrNum = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Date of Creation member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * Modification Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Created by User ID member array.
    */
   private String[] _Username = null;
   
   /**
    * Modified by User ID member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Acct-Mstr Version Number member array.
    */
   private Integer[] _AcctMstrVer = null;
   
   /**
    * Recid of Acct-Mstr record member array.
    */
   private Integer[] _AcctMstrRid = null;
   
   /**
    * Employee member array.
    */
   private String[] _Employee = null;
   
   /**
    * Minimum Withdrawal Age member array.
    */
   private Integer[] _MinWithAge = null;
   
   /**
    * Shareholder's SIN exists member array.
    */
   private Boolean[] _ExistSIN = null;
   
   /**
    * Shareholder's SIN is valid member array.
    */
   private Boolean[] _ValidSIN = null;
   
   /**
    * Tax Jurisdiction is valid member array.
    */
   private Boolean[] _ValidTaxJuris = null;
   
   /**
    * Beneficial Owner's address exists member array.
    */
   private Boolean[] _ExistBenAddr = null;
   
   /**
    * One of the addresses is not active member array.
    */
   private Boolean[] _HoldMail = null;
   
   /**
    * Some units are escrowed member array.
    */
   private Boolean[] _ExistEscrow = null;
   
   /**
    * Beneficiary exists member array.
    */
   private Boolean[] _ExistBeneficiary = null;
   
   /**
    * LIF/RIF/LRIF allocations exist member array.
    */
   private Boolean[] _ExistAlloc = null;
   
   /**
    * Outstanding Wire Order member array.
    */
   private Boolean[] _OutWireOrd = null;
   
   /**
    * Sales Rep is active member array.
    */
   private Boolean[] _SlsRepActive = null;
   
   /**
    * Contract within closing decade member array.
    */
   private Boolean[] _ClosingContr = null;
   
   /**
    * Contract matured member array.
    */
   private Boolean[] _ContrMatured = null;
   
   /**
    * Shareholder will turn 69 years this year member array.
    */
   private Boolean[] _Age69 = null;
   
   /**
    * Pending Death Claim member array.
    */
   private Boolean[] _DeathClaim = null;
   
   /**
    * Flag indicating if adding account to the member array.
    */
   private Boolean[] _AddAcctFlag = null;
   
   /**
    * Pending Trade exists member array.
    */
   private Boolean[] _PendingTrade = null;
   
   /**
    * Certificates Issued(Cert-Detl exists) member array.
    */
   private Boolean[] _Certificates = null;
   
   /**
    * Systematic Transfer setup member array.
    */
   private Boolean[] _SystemTrsfr = null;
   
   /**
    * PAC setup member array.
    */
   private Boolean[] _PAC = null;
   
   /**
    * SWP setup member array.
    */
   private Boolean[] _SWP = null;
   
   /**
    * Account Allocation exists member array.
    */
   private Boolean[] _AcctAlloc = null;
   
   /**
    * Clan Plan setup member array.
    */
   private Boolean[] _ClanPlan = null;
   
   /**
    * Unsettled transaction exists member array.
    */
   private Boolean[] _UnsettledTrn = null;
   
   /**
    * Transaction Found? member array.
    */
   private Boolean[] _TransFound = null;
   
   /**
    * First Effective Date of Account member array.
    */
   private Date[] _FirstEffective = null;
   
   /**
    * Affect Maximum? member array.
    */
   private Boolean[] _MaxApplies = null;
   
   /**
    * Qualified plan allowed for tax type member array.
    */
   private Boolean[] _RRIFQualified = null;
   
   /**
    * Legal min withdrawal age member array.
    */
   private Integer[] _LegMinWithAge = null;
   
   /**
    * Tax type is locked in plan type member array.
    */
   private Boolean[] _LockedIn = null;
   
   /**
    * Is federal jurisdiction allowed member array.
    */
   private Boolean[] _FedJurAllowed = null;
   
   /**
    * Minimum Age member array.
    */
   private Integer[] _MinAge = null;
   
   /**
    * Maximum Age member array.
    */
   private Integer[] _MaxAge = null;
   
   /**
    * LipTaxByJuris exists for shareholder's tax juris member array.
    */
   private Boolean[] _TaxTypeRules = null;
   
   /**
    * LipTaxByJuris exists for '0000' tax juris member array.
    */
   private Boolean[] _DefTaxTypeRules = null;
   
   /**
    * Flag indicating if account tax type is configured for Foreign Content rebalancing member array.
    */
   private Boolean[] _FCConfig = null;
   
   /**
    * Flag indicating if account has  Stop Foreign Content Excess Rebalancing member array.
    */
   private Boolean[] _StopFCrebal = null;
   
   /**
    * Foreign Content Override flag member array.
    */
   private Boolean[] _FCOverrides = null;
   
   /**
    * Flag indicating if entire account is locked member array.
    */
   private Boolean[] _AllLocked = null;
   
   /**
    * Flag indicating if account has been coded as assigned member array.
    */
   private Boolean[] _AcctLocked = null;
   
   /**
    * Flag indicating if  account is selfdirected type member array.
    */
   private Boolean[] _SelfDirected = null;
   
   /**
    * Flag indicating what plan type is the account member array.
    */
   private String[] _PlanType = null;
   
   /**
    * Flag indicating if Spouse's SIN is valid member array.
    */
   private Boolean[] _ValidSpSIN = null;
   
   /**
    * Flag indicating if RIF setup exist to RIF acct member array.
    */
   private Boolean[] _RIFExist = null;
   
   /**
    * Flag indicating status member array.
    */
   private Boolean[] _DeathStat = null;
   
   /**
    * Flag indicating if  account has BEL fund holdings member array.
    */
   private Boolean[] _ACBExist = null;
   
   /**
    * Flag indicating if Account has MM holdings member array.
    */
   private Boolean[] _IntAccrExist = null;
   
   /**
    * Flag indicating if distribution exist for the account member array.
    */
   private Boolean[] _DistribExist = null;
   
   /**
    * Flag indication if outstanding cheque exist member array.
    */
   private Boolean[] _ChequeExist = null;
   
   /**
    * Flag indicating if contract for account exist member array.
    */
   private Boolean[] _ContractExist = null;
   
   /**
    * Outstanding LLP member array.
    */
   private String[] _OutstLLP = null;
   
   /**
    * Social Code member array.
    */
   private String[] _SocialCode = null;
   
   /**
    * Social Code Description member array.
    */
   private String[] _SocialCodeDesc = null;
   
   /**
    * Save Plan Exist member array.
    */
   private Boolean[] _SavePlanExist = null;
   
   /**
    * Product Code member array.
    */
   private String[] _ProdCode = null;
   
   /**
    * Account Level Commission Exists Y/N member array.
    */
   private Boolean[] _AcctCommExists = null;
   
   /**
    * GST Exempt member array.
    */
   private Boolean[] _GSTExempt = null;
   
   /**
    * Account Fee Exist member array.
    */
   private Boolean[] _AcctFeesExist = null;
   
   /**
    * Apply PST  y/n member array.
    */
   private Boolean[] _ApplyPST = null;
   
   /**
    * Unisex member array.
    */
   private Boolean[] _Unisex = null;
   
   /**
    * Sex Distinct member array.
    */
   private Boolean[] _SexDistinct = null;
   
   /**
    * Bank Charge member array.
    */
   private String[] _BankCharge = null;
   
   /**
    * Consolidation EFT member array.
    */
   private String[] _ConsolidEFT = null;
   
   /**
    * Pension Juris Info Avail member array.
    */
   private Boolean[] _PensionJurisAvail = null;
   
   /**
    * settled date of the first settled trade member array.
    */
   private Date[] _FirstSettleDate = null;
   
   /**
    * Investment Profile member array.
    */
   private String[] _AMSROCode = null;
   
   /**
    * Mangement Fee Option member array.
    */
   private String[] _MgmtFeePayOption = null;
   
   /**
    * Created Today member array.
    */
   private Boolean[] _CreatedToday = null;
   
   /**
    * Protect Contract Exists member array.
    */
   private Boolean[] _ProtContractExists = null;
   
   /**
    * AcctCategory record exists member array.
    */
   private Boolean[] _AcctCatExists = null;
   
   /**
    * Early Redemption Fees will be charged member array.
    */
   private Boolean[] _ChargeERFee = null;
   
   /**
    * ShortTerm Transfer Fee wil be charged member array.
    */
   private Boolean[] _ChargeSTTRFee = null;
   
   /**
    * Use Broker Mangement Fee member array.
    */
   private Boolean[] _UseBrokerMF = null;
   
   /**
    * StopAMSRebal member array.
    */
   private Boolean[] _StopAMSRebal = null;
   
   /**
    * Account Purpose member array.
    */
   private String[] _AcctPurpose = null;
   
   /**
    * Additional Information member array.
    */
   private String[] _AdditionalInfo = null;
   
   /**
    * Business Number member array.
    */
   private String[] _BusinessNo = null;
   
   /**
    * Memorable Place member array.
    */
   private String[] _MemorablePlace = null;
   
   /**
    * Memorable Word member array.
    */
   private String[] _MemorableWord = null;
   
   /**
    * Memorable Date member array.
    */
   private Date[] _MemorableDate = null;
   
   /**
    * PensionLeg Code member array.
    */
   private String[] _PensionLegCode = null;
   
   /**
    * Tel/Fax Agreement member array.
    */
   private Boolean[] _TelFaxAgreement = null;
   
   /**
    * Clearing ID member array.
    */
   private String[] _ClearingID = null;
   
   /**
    * SettlLoc Exist member array.
    */
   private Boolean[] _SettlLocExist = null;
   
   /**
    * DTA Type member array.
    */
   private String[] _DTAType = null;
   
   /**
    * NetworkControlInd member array.
    */
   private String[] _NetworkControlInd = null;
   
   /**
    * ClearingFirm member array.
    */
   private String[] _ClearingFirm = null;
   
   /**
    * PAC with LSIF Funds Y/N member array.
    */
   private Boolean[] _LSIFPAC = null;
   
   /**
    * Highest Entity Risk member array.
    */
   private String[] _HighestEntityRisk = null;
   
   /**
    * Stop Redemption from Settlement member array.
    */
   private Boolean[] _StopRedSettle = null;
   
   /**
    * Registration Information member array.
    */
   private String[] _RegistrationInfo = null;
   
   /**
    * Fee model Code member array.
    */
   private String[] _FeeModelCode = null;
   
   /**
    * DSC Fee Level based on type from genctrl 'OverridePercentFree' member array.
    */
   private String[] _DSCFeeLevel = null;
   
   /**
    * Latest Effective Date member array.
    */
   private Date[] _LatestEffectiveDate = null;
   
   /**
    * Account Cut Off Exist member array.
    */
   private Boolean[] _AcctCutOffExist = null;
   
   /**
    * AgentForFirmAgencyCode member array.
    */
   private String[] _AgentForFirmAgencyCode = null;
   
   /**
    * TPAFirmAgencyCode member array.
    */
   private String[] _TPAFirmAgencyCode = null;
   
   /**
    * NSC Participant Id member array.
    */
   private String[] _NSCPartId = null;
   
   /**
    * Network ID member array.
    */
   private String[] _NetworkID = null;
   
   /**
    * Indicates that account has assignee with assigned units member array.
    */
   private Boolean[] _ExistAssignee = null;
   
   /**
    * Consolidation Type for Redemption member array.
    */
   private String[] _ConsolTypePW = null;
   
   /**
    * Fund Limitation Override Exist member array.
    */
   private Boolean[] _FundLimitOvrdExist = null;
   
   /**
    * NSCDividend member array.
    */
   private Boolean[] _NSCDividend = null;
   
   /**
    * Consolidation Type for Distribution member array.
    */
   private String[] _ConsolTypeID = null;
   
   /**
    * Pending Private Flag member array.
    */
   private Boolean[] _PendingPrivate = null;
   
   /**
    * Account Closing Reason member array.
    */
   private String[] _AcctClosingReason = null;
   
   /**
    * Active AMS Exist member array.
    */
   private Boolean[] _ActiveAMSExist = null;
   
   /**
    * Sibling Only member array.
    */
   private String[] _SiblingOnly = null;
   
   /**
    * Affluent member array.
    */
   private String[] _Aflluent = null;
   
   /**
    * Management Fee ID member array.
    */
   private String[] _MgmtFeeID = null;
   
   /**
    * Management Fee Type member array.
    */
   private String[] _MgmtFeeType = null;
   
   /**
    * Management Fee Rebate ID member array.
    */
   private String[] _MgmtFeeRbtID = null;
   
   /**
    * Manamgement Fee Rebate Type member array.
    */
   private String[] _MgmtFeeRbtType = null;
   
   /**
    * Link MFR member array.
    */
   private Boolean[] _LinkMFR = null;
   
   /**
    * Account AMS Exist flag member array.
    */
   private Boolean[] _AcctAMSExist = null;
   
   /**
    * Invoice Model ID member array.
    */
   private String[] _InvoiceModelID = null;
   
   /**
    * Active Certificate member array.
    */
   private Boolean[] _ActiveCert = null;
   
   /**
    * Flag indicating in account holder asked to waive the RRIF Min Payment member array.
    */
   private Boolean[] _MinWaived = null;
   
   /**
    * Hold Dividend Payment member array.
    */
   private Boolean[] _HoldDivPymt = null;
   
   /**
    * indicates if DOT or Addendum or both exists member array.
    */
   private String[] _DOTAdnd = null;
   
   /**
    * Flag indicating if Settlement Rule exists member array.
    */
   private Boolean[] _SettlementRuleExist = null;
   
   /**
    * Tax Type Schedule introduced for Old LIF member array.
    */
   private String[] _TaxTypeSchedule = null;
   
   /**
    * AcctActivityExists member array.
    */
   private Boolean[] _AcctActivityExists = null;
   
   /**
    * Stop Reason member array.
    */
   private String[] _StopReason = null;
   
   /**
    * Stop Reason Other member array.
    */
   private String[] _StopReasonOther = null;
   
   /**
    * Investor Type member array.
    */
   private String[] _InvestorType = null;
   
   /**
    * Invest on behalf of 3rd Party member array.
    */
   private String[] _InvestFor3rdParty = null;
   
   /**
    * Compliance Code member array.
    */
   private String[] _ComplianceCode = null;
   
   /**
    * Account Document List Exist member array.
    */
   private Boolean[] _AcctDocListExist = null;
   
   /**
    * Unit Rounding Method member array.
    */
   private String[] _UnitRoundMethod = null;
   
   /**
    * Last Unlocking Amount member array.
    */
   private String[] _UnLockGrossAmt = null;
   
   /**
    * Trade Date of the Last Unlocking Amt member array.
    */
   private Date[] _UnLockDeff = null;
   
   /**
    * Stage of Returned Mail member array.
    */
   private String[] _RtnMailStage = null;
   
   /**
    * Stage of Stale Cheque member array.
    */
   private String[] _StaleChqStage = null;
   
   /**
    * Flag that indicates if non financial updates are allowed in the account member array.
    */
   private Boolean[] _StopNFU = null;
   
   /**
    * Exemption Date member array.
    */
   private Date[] _ExemptDate = null;
   
   /**
    * Next Process Date for MFR member array.
    */
   private Date[] _NextMFRProcessDate = null;
   
   /**
    * Flag indicating if account is setup for MFR model member array.
    */
   private Boolean[] _IsMFRAccount = null;
   
   /**
    * Flag indicating if account is closed country resident member array.
    */
   private Boolean[] _IsClosedCountryResident = null;
   
   /**
    * Flag indicates if account has Acct-Auth record member array.
    */
   private Boolean[] _InvestorAuthorizationExist = null;
   
   /**
    * Flag indicates if there is outstanding unverified Entity Name member array.
    */
   private Boolean[] _EntityUnverifiedExist = null;
   
   /**
    * Flag if account registered CCRA in Jan 1,1998. member array.
    */
   private Boolean[] _GrandFathered = null;
   
   /**
    * Flag if RESP beneficiary deleted for account. member array.
    */
   private Boolean[] _RESPBenefDeleted = null;
   
   /**
    * Flag indicating if RESP Account Info exists member array.
    */
   private Boolean[] _RESPAcctInfoExists = null;
   
   /**
    * Flag indicating if there were contributions made before 1998. member array.
    */
   private Boolean[] _Pre98Contrib = null;
   
   /**
    * Flag indicating if AIP Withdrawal member array.
    */
   private Boolean[] _AIPWithdrawalExists = null;
   
   /**
    * Date to determine year of plan member array.
    */
   private Date[] _OrigPlanDeff = null;
   
   /**
    * Flag indicates whether the account can have a GWO contract or not member array.
    */
   private Boolean[] _IsGWOContract = null;
   
   /**
    * Flag indicates whether the account guarantee guard has been set up member array.
    */
   private Boolean[] _AcctGuarGuardExists = null;
   
   /**
    * Flag indicates if any of RESP beneficiaries ever lived in Quebec member array.
    */
   private Boolean[] _RESPQCResidentFound = null;
   
   /**
    * Flag indicates if Government Amendment record exist for the account member array.
    */
   private Boolean[] _GovAmendmentExist = null;
   
   /**
    * Flag indicates if account is run to curator file member array.
    */
   private Boolean[] _IsAcctRunToCurFile = null;
   
   /**
    * Flag indicates if account has been unfrozen member array.
    */
   private Boolean[] _HasAcctBeenUnFrozen = null;
   
   /**
    * Flag indicates if stale dated cheque exists in an account member array.
    */
   private Boolean[] _StaleChqExists = null;
   
   /**
    * Flag indicates remitted cheque exists in an account member array.
    */
   private Boolean[] _RemittedChqExists = null;
   
   /**
    * Flag indicates a list of remitted cheque stages member array.
    */
   private String[] _RemittedChqStage = null;
   
   /**
    * Consolidation Type for Purchase member array.
    */
   private String[] _ConsolTypeED = null;
   
   /**
    * RESP Account Inception Date member array.
    */
   private Date[] _InceptionDate = null;
   
   /**
    * ProdPortfolio UUID member array.
    */
   private String[] _ProdPortfolioUUID = null;
   
   /**
    * ProdPortfolioPlan UUID member array.
    */
   private String[] _ProdPortfolioPlanUUID = null;
   
   /**
    * Date that property is remitted to the government member array.
    */
   private Date[] _UnclmRemitDate = null;
   
   /**
    * NSCC Social Code member array.
    */
   private String[] _NSCSocialCode = null;
   
   /**
    * HasGIAHolding member array.
    */
   private Boolean[] _HasGIAHolding = null;
   
   /**
    * Can have CashSweep instruction member array.
    */
   private Boolean[] _CanHaveCashSweep = null;
   
   /**
    * Can have Maturity Instruction member array.
    */
   private Boolean[] _CanHaveMatInstr = null;
   
   /**
    * CashSweep exists member array.
    */
   private Boolean[] _CashSweepExists = null;
   
   /**
    * Maturity Instruction exists member array.
    */
   private Boolean[] _MatIntExists = null;
   
   /**
    * Organisation Type member array.
    */
   private String[] _OrgType = null;
   
   /**
    * Sub Organisation Type member array.
    */
   private String[] _SubOrgType = null;
   
   /**
    * Territory Code member array.
    */
   private String[] _TerritoryCode = null;
   
   /**
    * Commitment Status member array.
    */
   private String[] _CommitmentStatus = null;
   
   /**
    * Life Annuit Exists member array.
    */
   private Boolean[] _LifeAnnuityExists = null;
   
   /**
    * Stop Adjustment Date member array.
    */
   private Date[] _StopAdjDate = null;
   
   /**
    * Non Financial Confirm member array.
    */
   private Boolean[] _NonFinConfirm = null;
   
   /**
    * Account Settlement Currency member array.
    */
   private String[] _SettleCurrency = null;
   
   /**
    * Registration Agent Code member array.
    */
   private String[] _RegAgentCode = null;
   
   /**
    * GWA/LWA Pay Optons member array.
    */
   private String[] _GWLWAAvailOptions = null;
   
   /**
    * T5 Anniversary Date member array.
    */
   private Date[] _T5AnniversaryDate = null;
   
   /**
    * SWP with Amount Type G or L member array.
    */
   private String[] _SWPGLOpt = null;
   
   /**
    * RRIF with Amount Type G or L member array.
    */
   private String[] _RRIFGLOpt = null;
   
   /**
    * Taxable Trust Date member array.
    */
   private Date[] _TaxableTrustDate = null;
   
   /**
    * Contract Value Issue Date member array.
    */
   private Date[] _ContValIssueDate = null;
   
   /**
    * Contract Value Initial Market Value member array.
    */
   private String[] _ContValInitMKV = null;
   
   /**
    * Contract Value Net Transaction Amount member array.
    */
   private String[] _ContValNetTranAmt = null;
   
   /**
    * Contract Value Net Transaction Date member array.
    */
   private Date[] _ContValNetTranDate = null;
   
   /**
    * Account Fee Model Associated member array.
    */
   private Boolean[] _AcctFeeModelAssociated = null;
   
   /**
    * Shareholder Output Type member array.
    */
   private String[] _ShrOutputType = null;
   
   /**
    * Annuitant age (younger for joint annuitant age) member array.
    */
   private Integer[] _AnnuitantYoungerAge = null;
   
   /**
    * Account Identifier record Exist member array.
    */
   private Boolean[] _AcctIdentifierExist = null;
   
   /**
    * Account Regulatory Detail Exist member array.
    */
   private Boolean[] _AcctRegDetlExist = null;
   
   /**
    * Entity Regulatory Setup Exist member array.
    */
   private String[] _EntRegSetupExist = null;
   
   /**
    * Pending FATCA Search member array.
    */
   private Boolean[] _PendingFATCASrch = null;
   
   /**
    * CID Money Movement Eligible member array.
    */
   private Boolean[] _AcctCIDElig = null;
   
   /**
    * Flag to indicate if Trailer Fee Rebate is existed member array.
    */
   private Boolean[] _TFRExists = null;
   
   /**
    * AdvisorFeeExist member array.
    */
   private Boolean[] _AdvisorFeeExist = null;
   
   /**
    * InvestorClassification member array.
    */
   private String[] _InvestorClassification = null;
   
   /**
    * AIFMDInvestorCategory member array.
    */
   private String[] _AIFMDInvestorCategory = null;
   
   /**
    * Account Group Exist member array.
    */
   private Boolean[] _AccountGroupExist = null;
   
   /**
    * Private Wealth Account member array.
    */
   private Boolean[] _PrivateWealthAcct = null;
   
   /**
    * Private Wealth Opt Out member array.
    */
   private Boolean[] _PrivateWealthOptOut = null;
   
   /**
    * Tax Forms Apply member array.
    */
   private Boolean[] _TaxFormsAppl = null;
   
   /**
    * AggrType member array.
    */
   private String[] _AggrType = null;
   
   /**
    * MoneyInExist member array.
    */
   private Boolean[] _MoneyInExist = null;
   

   /**
    * Constructs the AccountInformationView object.
    * 
    */
   public AccountInformationView()
   {
      super ( new AccountInformationRequest() );
   }

   /**
    * Constructs the AccountInformationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AccountInformationView( String hostEncoding )
   {
      super ( new AccountInformationRequest( hostEncoding ) );
   }

   /**
    * Gets the AccountInformationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AccountInformationRequest object.
    */
   public final AccountInformationRequest getRequest()
   {
      return (AccountInformationRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the Account number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account number or null.
    */
   public final String getAccountNum( int index )
   {
      return _AccountNum[index];
   }
    
   /**
    * Gets the Account number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account number or the specified default value.
    */
   public final String getAccountNum( int index, String defaultValue )
   {
      return _AccountNum[index] == null ? defaultValue : _AccountNum[index];
   }
    
   /**
    * Gets the array of Account number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account number values.
    */
   public final String[] getAccountNumArray()
   {
      return _AccountNum;
   }
    
   /**
    * Gets the Benifical owner field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Benifical owner or null.
    */
   public final String getBeneficialOwner( int index )
   {
      return _BeneficialOwner[index];
   }
    
   /**
    * Gets the Benifical owner field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Benifical owner or the specified default value.
    */
   public final String getBeneficialOwner( int index, String defaultValue )
   {
      return _BeneficialOwner[index] == null ? defaultValue : _BeneficialOwner[index];
   }
    
   /**
    * Gets the array of Benifical owner fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Benifical owner values.
    */
   public final String[] getBeneficialOwnerArray()
   {
      return _BeneficialOwner;
   }
    
   /**
    * Gets the Alternate account number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Alternate account number or null.
    */
   public final String getAltAccount( int index )
   {
      return _AltAccount[index];
   }
    
   /**
    * Gets the Alternate account number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Alternate account number or the specified default value.
    */
   public final String getAltAccount( int index, String defaultValue )
   {
      return _AltAccount[index] == null ? defaultValue : _AltAccount[index];
   }
    
   /**
    * Gets the array of Alternate account number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Alternate account number values.
    */
   public final String[] getAltAccountArray()
   {
      return _AltAccount;
   }
    
   /**
    * Gets the Account type code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account type code or null.
    */
   public final String getAcctType( int index )
   {
      return _AcctType[index];
   }
    
   /**
    * Gets the Account type code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account type code or the specified default value.
    */
   public final String getAcctType( int index, String defaultValue )
   {
      return _AcctType[index] == null ? defaultValue : _AcctType[index];
   }
    
   /**
    * Gets the array of Account type code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account type code values.
    */
   public final String[] getAcctTypeArray()
   {
      return _AcctType;
   }
    
   /**
    * Gets the Account type description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account type description or null.
    */
   public final String getAcctTypeDesc( int index )
   {
      return _AcctTypeDesc[index];
   }
    
   /**
    * Gets the Account type description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account type description or the specified default value.
    */
   public final String getAcctTypeDesc( int index, String defaultValue )
   {
      return _AcctTypeDesc[index] == null ? defaultValue : _AcctTypeDesc[index];
   }
    
   /**
    * Gets the array of Account type description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account type description values.
    */
   public final String[] getAcctTypeDescArray()
   {
      return _AcctTypeDesc;
   }
    
   /**
    * Gets the Tax type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax type or null.
    */
   public final String getTaxType( int index )
   {
      return _TaxType[index];
   }
    
   /**
    * Gets the Tax type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax type or the specified default value.
    */
   public final String getTaxType( int index, String defaultValue )
   {
      return _TaxType[index] == null ? defaultValue : _TaxType[index];
   }
    
   /**
    * Gets the array of Tax type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax type values.
    */
   public final String[] getTaxTypeArray()
   {
      return _TaxType;
   }
    
   /**
    * Gets the Tax type description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax type description or null.
    */
   public final String getTaxTypeDesc( int index )
   {
      return _TaxTypeDesc[index];
   }
    
   /**
    * Gets the Tax type description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax type description or the specified default value.
    */
   public final String getTaxTypeDesc( int index, String defaultValue )
   {
      return _TaxTypeDesc[index] == null ? defaultValue : _TaxTypeDesc[index];
   }
    
   /**
    * Gets the array of Tax type description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax type description values.
    */
   public final String[] getTaxTypeDescArray()
   {
      return _TaxTypeDesc;
   }
    
   /**
    * Gets the Recipient Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recipient Type or null.
    */
   public final String getRecipientType( int index )
   {
      return _RecipientType[index];
   }
    
   /**
    * Gets the Recipient Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recipient Type or the specified default value.
    */
   public final String getRecipientType( int index, String defaultValue )
   {
      return _RecipientType[index] == null ? defaultValue : _RecipientType[index];
   }
    
   /**
    * Gets the array of Recipient Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recipient Type values.
    */
   public final String[] getRecipientTypeArray()
   {
      return _RecipientType;
   }
    
   /**
    * Gets the Recipient Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recipient Type Description or null.
    */
   public final String getRecipientTypeDesc( int index )
   {
      return _RecipientTypeDesc[index];
   }
    
   /**
    * Gets the Recipient Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recipient Type Description or the specified default value.
    */
   public final String getRecipientTypeDesc( int index, String defaultValue )
   {
      return _RecipientTypeDesc[index] == null ? defaultValue : _RecipientTypeDesc[index];
   }
    
   /**
    * Gets the array of Recipient Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recipient Type Description values.
    */
   public final String[] getRecipientTypeDescArray()
   {
      return _RecipientTypeDesc;
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Designation or null.
    */
   public final String getAcctDesignation( int index )
   {
      return _AcctDesignation[index];
   }
    
   /**
    * Gets the Account Designation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Designation or the specified default value.
    */
   public final String getAcctDesignation( int index, String defaultValue )
   {
      return _AcctDesignation[index] == null ? defaultValue : _AcctDesignation[index];
   }
    
   /**
    * Gets the array of Account Designation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Designation values.
    */
   public final String[] getAcctDesignationArray()
   {
      return _AcctDesignation;
   }
    
   /**
    * Gets the Account Designation Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Designation Description or null.
    */
   public final String getAcctDesignationDesc( int index )
   {
      return _AcctDesignationDesc[index];
   }
    
   /**
    * Gets the Account Designation Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Designation Description or the specified default value.
    */
   public final String getAcctDesignationDesc( int index, String defaultValue )
   {
      return _AcctDesignationDesc[index] == null ? defaultValue : _AcctDesignationDesc[index];
   }
    
   /**
    * Gets the array of Account Designation Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Designation Description values.
    */
   public final String[] getAcctDesignationDescArray()
   {
      return _AcctDesignationDesc;
   }
    
   /**
    * Gets the Currency Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Code or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Code or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Code values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency Name or null.
    */
   public final String getCurrencyName( int index )
   {
      return _CurrencyName[index];
   }
    
   /**
    * Gets the Currency Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency Name or the specified default value.
    */
   public final String getCurrencyName( int index, String defaultValue )
   {
      return _CurrencyName[index] == null ? defaultValue : _CurrencyName[index];
   }
    
   /**
    * Gets the array of Currency Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency Name values.
    */
   public final String[] getCurrencyNameArray()
   {
      return _CurrencyName;
   }
    
   /**
    * Gets the Cross Reference Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cross Reference Number or null.
    */
   public final String getXrefNum( int index )
   {
      return _XrefNum[index];
   }
    
   /**
    * Gets the Cross Reference Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cross Reference Number or the specified default value.
    */
   public final String getXrefNum( int index, String defaultValue )
   {
      return _XrefNum[index] == null ? defaultValue : _XrefNum[index];
   }
    
   /**
    * Gets the array of Cross Reference Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cross Reference Number values.
    */
   public final String[] getXrefNumArray()
   {
      return _XrefNum;
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker Code or null.
    */
   public final String getBrokerCode( int index )
   {
      return _BrokerCode[index];
   }
    
   /**
    * Gets the Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker Code or the specified default value.
    */
   public final String getBrokerCode( int index, String defaultValue )
   {
      return _BrokerCode[index] == null ? defaultValue : _BrokerCode[index];
   }
    
   /**
    * Gets the array of Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker Code values.
    */
   public final String[] getBrokerCodeArray()
   {
      return _BrokerCode;
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch Code or null.
    */
   public final String getBranchCode( int index )
   {
      return _BranchCode[index];
   }
    
   /**
    * Gets the Branch Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch Code or the specified default value.
    */
   public final String getBranchCode( int index, String defaultValue )
   {
      return _BranchCode[index] == null ? defaultValue : _BranchCode[index];
   }
    
   /**
    * Gets the array of Branch Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch Code values.
    */
   public final String[] getBranchCodeArray()
   {
      return _BranchCode;
   }
    
   /**
    * Gets the Salesrep Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Salesrep Code or null.
    */
   public final String getSlsrep( int index )
   {
      return _Slsrep[index];
   }
    
   /**
    * Gets the Salesrep Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salesrep Code or the specified default value.
    */
   public final String getSlsrep( int index, String defaultValue )
   {
      return _Slsrep[index] == null ? defaultValue : _Slsrep[index];
   }
    
   /**
    * Gets the array of Salesrep Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Salesrep Code values.
    */
   public final String[] getSlsrepArray()
   {
      return _Slsrep;
   }
    
   /**
    * Gets the Intermediary Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Intermediary Code or null.
    */
   public final String getInterCode( int index )
   {
      return _InterCode[index];
   }
    
   /**
    * Gets the Intermediary Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Code or the specified default value.
    */
   public final String getInterCode( int index, String defaultValue )
   {
      return _InterCode[index] == null ? defaultValue : _InterCode[index];
   }
    
   /**
    * Gets the array of Intermediary Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Intermediary Code values.
    */
   public final String[] getInterCodeArray()
   {
      return _InterCode;
   }
    
   /**
    * Gets the Intermediary Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Intermediary Account or null.
    */
   public final String getInterAccount( int index )
   {
      return _InterAccount[index];
   }
    
   /**
    * Gets the Intermediary Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Intermediary Account or the specified default value.
    */
   public final String getInterAccount( int index, String defaultValue )
   {
      return _InterAccount[index] == null ? defaultValue : _InterAccount[index];
   }
    
   /**
    * Gets the array of Intermediary Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Intermediary Account values.
    */
   public final String[] getInterAccountArray()
   {
      return _InterAccount;
   }
    
   /**
    * Gets the Account Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Status or null.
    */
   public final String getAcctStatus( int index )
   {
      return _AcctStatus[index];
   }
    
   /**
    * Gets the Account Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Status or the specified default value.
    */
   public final String getAcctStatus( int index, String defaultValue )
   {
      return _AcctStatus[index] == null ? defaultValue : _AcctStatus[index];
   }
    
   /**
    * Gets the array of Account Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Status values.
    */
   public final String[] getAcctStatusArray()
   {
      return _AcctStatus;
   }
    
   /**
    * Gets the Account Status Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Status Description or null.
    */
   public final String getAcctStatusDesc( int index )
   {
      return _AcctStatusDesc[index];
   }
    
   /**
    * Gets the Account Status Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Status Description or the specified default value.
    */
   public final String getAcctStatusDesc( int index, String defaultValue )
   {
      return _AcctStatusDesc[index] == null ? defaultValue : _AcctStatusDesc[index];
   }
    
   /**
    * Gets the array of Account Status Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Status Description values.
    */
   public final String[] getAcctStatusDescArray()
   {
      return _AcctStatusDesc;
   }
    
   /**
    * Gets the Date of Registration field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date of Registration or null.
    */
   public final Date getDateOfReg( int index )
   {
      return _DateOfReg[index];
   }
    
   /**
    * Gets the Date of Registration field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Registration or the specified default value.
    */
   public final Date getDateOfReg( int index, Date defaultValue )
   {
      return _DateOfReg[index] == null ? defaultValue : _DateOfReg[index];
   }
    
   /**
    * Gets the array of Date of Registration fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date of Registration values.
    */
   public final Date[] getDateOfRegArray()
   {
      return _DateOfReg;
   }
    
   /**
    * Gets the RRSP Fee Indicator field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Fee Indicator or null.
    */
   public final String getRRSPFee( int index )
   {
      return _RRSPFee[index];
   }
    
   /**
    * Gets the RRSP Fee Indicator field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Fee Indicator or the specified default value.
    */
   public final String getRRSPFee( int index, String defaultValue )
   {
      return _RRSPFee[index] == null ? defaultValue : _RRSPFee[index];
   }
    
   /**
    * Gets the array of RRSP Fee Indicator fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Fee Indicator values.
    */
   public final String[] getRRSPFeeArray()
   {
      return _RRSPFee;
   }
    
   /**
    * Gets the RRSP Fee Indicator Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Fee Indicator Description or null.
    */
   public final String getRRSPFeeDesc( int index )
   {
      return _RRSPFeeDesc[index];
   }
    
   /**
    * Gets the RRSP Fee Indicator Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Fee Indicator Description or the specified default value.
    */
   public final String getRRSPFeeDesc( int index, String defaultValue )
   {
      return _RRSPFeeDesc[index] == null ? defaultValue : _RRSPFeeDesc[index];
   }
    
   /**
    * Gets the array of RRSP Fee Indicator Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Fee Indicator Description values.
    */
   public final String[] getRRSPFeeDescArray()
   {
      return _RRSPFeeDesc;
   }
    
   /**
    * Gets the Asset Management Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Asset Management Code or null.
    */
   public final String getAMSCode( int index )
   {
      return _AMSCode[index];
   }
    
   /**
    * Gets the Asset Management Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Asset Management Code or the specified default value.
    */
   public final String getAMSCode( int index, String defaultValue )
   {
      return _AMSCode[index] == null ? defaultValue : _AMSCode[index];
   }
    
   /**
    * Gets the array of Asset Management Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Asset Management Code values.
    */
   public final String[] getAMSCodeArray()
   {
      return _AMSCode;
   }
    
   /**
    * Gets the Pension Jurisdiction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pension Jurisdiction or null.
    */
   public final String getPensionJuris( int index )
   {
      return _PensionJuris[index];
   }
    
   /**
    * Gets the Pension Jurisdiction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pension Jurisdiction or the specified default value.
    */
   public final String getPensionJuris( int index, String defaultValue )
   {
      return _PensionJuris[index] == null ? defaultValue : _PensionJuris[index];
   }
    
   /**
    * Gets the array of Pension Jurisdiction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pension Jurisdiction values.
    */
   public final String[] getPensionJurisArray()
   {
      return _PensionJuris;
   }
    
   /**
    * Gets the Pension Jurisdiction Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pension Jurisdiction Description or null.
    */
   public final String getPensionJurisDesc( int index )
   {
      return _PensionJurisDesc[index];
   }
    
   /**
    * Gets the Pension Jurisdiction Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pension Jurisdiction Description or the specified default value.
    */
   public final String getPensionJurisDesc( int index, String defaultValue )
   {
      return _PensionJurisDesc[index] == null ? defaultValue : _PensionJurisDesc[index];
   }
    
   /**
    * Gets the array of Pension Jurisdiction Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pension Jurisdiction Description values.
    */
   public final String[] getPensionJurisDescArray()
   {
      return _PensionJurisDesc;
   }
    
   /**
    * Gets the Stop Purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Purchase or null.
    */
   public final Boolean getStopPurchase( int index )
   {
      return _StopPurchase[index];
   }
    
   /**
    * Gets the Stop Purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Purchase or the specified default value.
    */
   public final boolean getStopPurchase( int index, boolean defaultValue )
   {
      return _StopPurchase[index] == null ? defaultValue : _StopPurchase[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Purchase values.
    */
   public final Boolean[] getStopPurchaseArray()
   {
      return _StopPurchase;
   }
    
   /**
    * Gets the Stop Transfer In field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Transfer In or null.
    */
   public final Boolean getStopXferIn( int index )
   {
      return _StopXferIn[index];
   }
    
   /**
    * Gets the Stop Transfer In field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer In or the specified default value.
    */
   public final boolean getStopXferIn( int index, boolean defaultValue )
   {
      return _StopXferIn[index] == null ? defaultValue : _StopXferIn[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Transfer In fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Transfer In values.
    */
   public final Boolean[] getStopXferInArray()
   {
      return _StopXferIn;
   }
    
   /**
    * Gets the Stop Transfer Out field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Transfer Out or null.
    */
   public final Boolean getStopXferOut( int index )
   {
      return _StopXferOut[index];
   }
    
   /**
    * Gets the Stop Transfer Out field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Transfer Out or the specified default value.
    */
   public final boolean getStopXferOut( int index, boolean defaultValue )
   {
      return _StopXferOut[index] == null ? defaultValue : _StopXferOut[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Transfer Out fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Transfer Out values.
    */
   public final Boolean[] getStopXferOutArray()
   {
      return _StopXferOut;
   }
    
   /**
    * Gets the Stop Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Redemption or null.
    */
   public final Boolean getStopRed( int index )
   {
      return _StopRed[index];
   }
    
   /**
    * Gets the Stop Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Redemption or the specified default value.
    */
   public final boolean getStopRed( int index, boolean defaultValue )
   {
      return _StopRed[index] == null ? defaultValue : _StopRed[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Redemption values.
    */
   public final Boolean[] getStopRedArray()
   {
      return _StopRed;
   }
    
   /**
    * Gets the Fee Waived field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee Waived or null.
    */
   public final Boolean getFeeWaived( int index )
   {
      return _FeeWaived[index];
   }
    
   /**
    * Gets the Fee Waived field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee Waived or the specified default value.
    */
   public final boolean getFeeWaived( int index, boolean defaultValue )
   {
      return _FeeWaived[index] == null ? defaultValue : _FeeWaived[index].booleanValue();
   }
    
   /**
    * Gets the array of Fee Waived fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee Waived values.
    */
   public final Boolean[] getFeeWaivedArray()
   {
      return _FeeWaived;
   }
    
   /**
    * Gets the Market Mailing field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Market Mailing or null.
    */
   public final Boolean getMarketMail( int index )
   {
      return _MarketMail[index];
   }
    
   /**
    * Gets the Market Mailing field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Market Mailing or the specified default value.
    */
   public final boolean getMarketMail( int index, boolean defaultValue )
   {
      return _MarketMail[index] == null ? defaultValue : _MarketMail[index].booleanValue();
   }
    
   /**
    * Gets the array of Market Mailing fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Market Mailing values.
    */
   public final Boolean[] getMarketMailArray()
   {
      return _MarketMail;
   }
    
   /**
    * Gets the Unseizable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unseizable or null.
    */
   public final Boolean getUnseizable( int index )
   {
      return _Unseizable[index];
   }
    
   /**
    * Gets the Unseizable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unseizable or the specified default value.
    */
   public final boolean getUnseizable( int index, boolean defaultValue )
   {
      return _Unseizable[index] == null ? defaultValue : _Unseizable[index].booleanValue();
   }
    
   /**
    * Gets the array of Unseizable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unseizable values.
    */
   public final Boolean[] getUnseizableArray()
   {
      return _Unseizable;
   }
    
   /**
    * Gets the Registration Completed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Registration Completed or null.
    */
   public final Boolean getRegCompleted( int index )
   {
      return _RegCompleted[index];
   }
    
   /**
    * Gets the Registration Completed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Registration Completed or the specified default value.
    */
   public final boolean getRegCompleted( int index, boolean defaultValue )
   {
      return _RegCompleted[index] == null ? defaultValue : _RegCompleted[index].booleanValue();
   }
    
   /**
    * Gets the array of Registration Completed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Registration Completed values.
    */
   public final Boolean[] getRegCompletedArray()
   {
      return _RegCompleted;
   }
    
   /**
    * Gets the Suppress All Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Suppress All Confirm or null.
    */
   public final Boolean getSupConf( int index )
   {
      return _SupConf[index];
   }
    
   /**
    * Gets the Suppress All Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suppress All Confirm or the specified default value.
    */
   public final boolean getSupConf( int index, boolean defaultValue )
   {
      return _SupConf[index] == null ? defaultValue : _SupConf[index].booleanValue();
   }
    
   /**
    * Gets the array of Suppress All Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Suppress All Confirm values.
    */
   public final Boolean[] getSupConfArray()
   {
      return _SupConf;
   }
    
   /**
    * Gets the Suppress Employee Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Suppress Employee Confirm or null.
    */
   public final Boolean getSupEmpConf( int index )
   {
      return _SupEmpConf[index];
   }
    
   /**
    * Gets the Suppress Employee Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suppress Employee Confirm or the specified default value.
    */
   public final boolean getSupEmpConf( int index, boolean defaultValue )
   {
      return _SupEmpConf[index] == null ? defaultValue : _SupEmpConf[index].booleanValue();
   }
    
   /**
    * Gets the array of Suppress Employee Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Suppress Employee Confirm values.
    */
   public final Boolean[] getSupEmpConfArray()
   {
      return _SupEmpConf;
   }
    
   /**
    * Gets the In Trust For field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the In Trust For or null.
    */
   public final Boolean getInTrustFor( int index )
   {
      return _InTrustFor[index];
   }
    
   /**
    * Gets the In Trust For field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the In Trust For or the specified default value.
    */
   public final boolean getInTrustFor( int index, boolean defaultValue )
   {
      return _InTrustFor[index] == null ? defaultValue : _InTrustFor[index].booleanValue();
   }
    
   /**
    * Gets the array of In Trust For fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of In Trust For values.
    */
   public final Boolean[] getInTrustForArray()
   {
      return _InTrustFor;
   }
    
   /**
    * Gets the Escrow field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Escrow or null.
    */
   public final Boolean getEscrow( int index )
   {
      return _Escrow[index];
   }
    
   /**
    * Gets the Escrow field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Escrow or the specified default value.
    */
   public final boolean getEscrow( int index, boolean defaultValue )
   {
      return _Escrow[index] == null ? defaultValue : _Escrow[index].booleanValue();
   }
    
   /**
    * Gets the array of Escrow fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Escrow values.
    */
   public final Boolean[] getEscrowArray()
   {
      return _Escrow;
   }
    
   /**
    * Gets the Group field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group or null.
    */
   public final String getAcctGroup( int index )
   {
      return _AcctGroup[index];
   }
    
   /**
    * Gets the Group field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group or the specified default value.
    */
   public final String getAcctGroup( int index, String defaultValue )
   {
      return _AcctGroup[index] == null ? defaultValue : _AcctGroup[index];
   }
    
   /**
    * Gets the array of Group fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group values.
    */
   public final String[] getAcctGroupArray()
   {
      return _AcctGroup;
   }
    
   /**
    * Gets the Group Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Group Name or null.
    */
   public final String getAcctGroupName( int index )
   {
      return _AcctGroupName[index];
   }
    
   /**
    * Gets the Group Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Group Name or the specified default value.
    */
   public final String getAcctGroupName( int index, String defaultValue )
   {
      return _AcctGroupName[index] == null ? defaultValue : _AcctGroupName[index];
   }
    
   /**
    * Gets the array of Group Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Group Name values.
    */
   public final String[] getAcctGroupNameArray()
   {
      return _AcctGroupName;
   }
    
   /**
    * Gets the Broker's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Broker's Name or null.
    */
   public final String getBrokerName( int index )
   {
      return _BrokerName[index];
   }
    
   /**
    * Gets the Broker's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Broker's Name or the specified default value.
    */
   public final String getBrokerName( int index, String defaultValue )
   {
      return _BrokerName[index] == null ? defaultValue : _BrokerName[index];
   }
    
   /**
    * Gets the array of Broker's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Broker's Name values.
    */
   public final String[] getBrokerNameArray()
   {
      return _BrokerName;
   }
    
   /**
    * Gets the Branch's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Branch's Name or null.
    */
   public final String getBranchName( int index )
   {
      return _BranchName[index];
   }
    
   /**
    * Gets the Branch's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch's Name or the specified default value.
    */
   public final String getBranchName( int index, String defaultValue )
   {
      return _BranchName[index] == null ? defaultValue : _BranchName[index];
   }
    
   /**
    * Gets the array of Branch's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Branch's Name values.
    */
   public final String[] getBranchNameArray()
   {
      return _BranchName;
   }
    
   /**
    * Gets the Salesrep's Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Salesrep's Name or null.
    */
   public final String getSlsrepName( int index )
   {
      return _SlsrepName[index];
   }
    
   /**
    * Gets the Salesrep's Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salesrep's Name or the specified default value.
    */
   public final String getSlsrepName( int index, String defaultValue )
   {
      return _SlsrepName[index] == null ? defaultValue : _SlsrepName[index];
   }
    
   /**
    * Gets the array of Salesrep's Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Salesrep's Name values.
    */
   public final String[] getSlsrepNameArray()
   {
      return _SlsrepName;
   }
    
   /**
    * Gets the Salesrep Alternate Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Salesrep Alternate Name or null.
    */
   public final String getSlsrepAltName( int index )
   {
      return _SlsrepAltName[index];
   }
    
   /**
    * Gets the Salesrep Alternate Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Salesrep Alternate Name or the specified default value.
    */
   public final String getSlsrepAltName( int index, String defaultValue )
   {
      return _SlsrepAltName[index] == null ? defaultValue : _SlsrepAltName[index];
   }
    
   /**
    * Gets the array of Salesrep Alternate Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Salesrep Alternate Name values.
    */
   public final String[] getSlsrepAltNameArray()
   {
      return _SlsrepAltName;
   }
    
   /**
    * Gets the Account Settled Balance in $ field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Settled Balance in $ or null.
    */
   public final String getAccountBalance( int index )
   {
      return _AccountBalance[index];
   }
    
   /**
    * Gets the Account Settled Balance in $ field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Settled Balance in $ or the specified default value.
    */
   public final String getAccountBalance( int index, String defaultValue )
   {
      return _AccountBalance[index] == null ? defaultValue : _AccountBalance[index];
   }
    
   /**
    * Gets the array of Account Settled Balance in $ fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Settled Balance in $ values.
    */
   public final String[] getAccountBalanceArray()
   {
      return _AccountBalance;
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Number or null.
    */
   public final String getShrNum( int index )
   {
      return _ShrNum[index];
   }
    
   /**
    * Gets the Shareholder Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final String getShrNum( int index, String defaultValue )
   {
      return _ShrNum[index] == null ? defaultValue : _ShrNum[index];
   }
    
   /**
    * Gets the array of Shareholder Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Number values.
    */
   public final String[] getShrNumArray()
   {
      return _ShrNum;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Date of Creation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date of Creation or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Date of Creation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Creation or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Date of Creation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date of Creation values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modification Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Modification Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modification Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Modification Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modification Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Created by User ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created by User ID or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the Created by User ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created by User ID or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of Created by User ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created by User ID values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the Modified by User ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Modified by User ID or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Modified by User ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified by User ID or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Modified by User ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Modified by User ID values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Acct-Mstr Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acct-Mstr Version Number or null.
    */
   public final Integer getAcctMstrVer( int index )
   {
      return _AcctMstrVer[index];
   }
    
   /**
    * Gets the Acct-Mstr Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acct-Mstr Version Number or the specified default value.
    */
   public final int getAcctMstrVer( int index, int defaultValue )
   {
      return _AcctMstrVer[index] == null ? defaultValue : _AcctMstrVer[index].intValue();
   }
    
   /**
    * Gets the array of Acct-Mstr Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acct-Mstr Version Number values.
    */
   public final Integer[] getAcctMstrVerArray()
   {
      return _AcctMstrVer;
   }
    
   /**
    * Gets the Recid of Acct-Mstr record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recid of Acct-Mstr record or null.
    */
   public final Integer getAcctMstrRid( int index )
   {
      return _AcctMstrRid[index];
   }
    
   /**
    * Gets the Recid of Acct-Mstr record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of Acct-Mstr record or the specified default value.
    */
   public final int getAcctMstrRid( int index, int defaultValue )
   {
      return _AcctMstrRid[index] == null ? defaultValue : _AcctMstrRid[index].intValue();
   }
    
   /**
    * Gets the array of Recid of Acct-Mstr record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recid of Acct-Mstr record values.
    */
   public final Integer[] getAcctMstrRidArray()
   {
      return _AcctMstrRid;
   }
    
   /**
    * Gets the Employee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Employee or null.
    */
   public final String getEmployee( int index )
   {
      return _Employee[index];
   }
    
   /**
    * Gets the Employee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Employee or the specified default value.
    */
   public final String getEmployee( int index, String defaultValue )
   {
      return _Employee[index] == null ? defaultValue : _Employee[index];
   }
    
   /**
    * Gets the array of Employee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Employee values.
    */
   public final String[] getEmployeeArray()
   {
      return _Employee;
   }
    
   /**
    * Gets the Minimum Withdrawal Age field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Withdrawal Age or null.
    */
   public final Integer getMinWithAge( int index )
   {
      return _MinWithAge[index];
   }
    
   /**
    * Gets the Minimum Withdrawal Age field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Withdrawal Age or the specified default value.
    */
   public final int getMinWithAge( int index, int defaultValue )
   {
      return _MinWithAge[index] == null ? defaultValue : _MinWithAge[index].intValue();
   }
    
   /**
    * Gets the array of Minimum Withdrawal Age fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Withdrawal Age values.
    */
   public final Integer[] getMinWithAgeArray()
   {
      return _MinWithAge;
   }
    
   /**
    * Gets the Shareholder's SIN exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder's SIN exists or null.
    */
   public final Boolean getExistSIN( int index )
   {
      return _ExistSIN[index];
   }
    
   /**
    * Gets the Shareholder's SIN exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder's SIN exists or the specified default value.
    */
   public final boolean getExistSIN( int index, boolean defaultValue )
   {
      return _ExistSIN[index] == null ? defaultValue : _ExistSIN[index].booleanValue();
   }
    
   /**
    * Gets the array of Shareholder's SIN exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder's SIN exists values.
    */
   public final Boolean[] getExistSINArray()
   {
      return _ExistSIN;
   }
    
   /**
    * Gets the Shareholder's SIN is valid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder's SIN is valid or null.
    */
   public final Boolean getValidSIN( int index )
   {
      return _ValidSIN[index];
   }
    
   /**
    * Gets the Shareholder's SIN is valid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder's SIN is valid or the specified default value.
    */
   public final boolean getValidSIN( int index, boolean defaultValue )
   {
      return _ValidSIN[index] == null ? defaultValue : _ValidSIN[index].booleanValue();
   }
    
   /**
    * Gets the array of Shareholder's SIN is valid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder's SIN is valid values.
    */
   public final Boolean[] getValidSINArray()
   {
      return _ValidSIN;
   }
    
   /**
    * Gets the Tax Jurisdiction is valid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Jurisdiction is valid or null.
    */
   public final Boolean getValidTaxJuris( int index )
   {
      return _ValidTaxJuris[index];
   }
    
   /**
    * Gets the Tax Jurisdiction is valid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction is valid or the specified default value.
    */
   public final boolean getValidTaxJuris( int index, boolean defaultValue )
   {
      return _ValidTaxJuris[index] == null ? defaultValue : _ValidTaxJuris[index].booleanValue();
   }
    
   /**
    * Gets the array of Tax Jurisdiction is valid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Jurisdiction is valid values.
    */
   public final Boolean[] getValidTaxJurisArray()
   {
      return _ValidTaxJuris;
   }
    
   /**
    * Gets the Beneficial Owner's address exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficial Owner's address exists or null.
    */
   public final Boolean getExistBenAddr( int index )
   {
      return _ExistBenAddr[index];
   }
    
   /**
    * Gets the Beneficial Owner's address exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficial Owner's address exists or the specified default value.
    */
   public final boolean getExistBenAddr( int index, boolean defaultValue )
   {
      return _ExistBenAddr[index] == null ? defaultValue : _ExistBenAddr[index].booleanValue();
   }
    
   /**
    * Gets the array of Beneficial Owner's address exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficial Owner's address exists values.
    */
   public final Boolean[] getExistBenAddrArray()
   {
      return _ExistBenAddr;
   }
    
   /**
    * Gets the One of the addresses is not active field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the One of the addresses is not active or null.
    */
   public final Boolean getHoldMail( int index )
   {
      return _HoldMail[index];
   }
    
   /**
    * Gets the One of the addresses is not active field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the One of the addresses is not active or the specified default value.
    */
   public final boolean getHoldMail( int index, boolean defaultValue )
   {
      return _HoldMail[index] == null ? defaultValue : _HoldMail[index].booleanValue();
   }
    
   /**
    * Gets the array of One of the addresses is not active fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of One of the addresses is not active values.
    */
   public final Boolean[] getHoldMailArray()
   {
      return _HoldMail;
   }
    
   /**
    * Gets the Some units are escrowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Some units are escrowed or null.
    */
   public final Boolean getExistEscrow( int index )
   {
      return _ExistEscrow[index];
   }
    
   /**
    * Gets the Some units are escrowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Some units are escrowed or the specified default value.
    */
   public final boolean getExistEscrow( int index, boolean defaultValue )
   {
      return _ExistEscrow[index] == null ? defaultValue : _ExistEscrow[index].booleanValue();
   }
    
   /**
    * Gets the array of Some units are escrowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Some units are escrowed values.
    */
   public final Boolean[] getExistEscrowArray()
   {
      return _ExistEscrow;
   }
    
   /**
    * Gets the Beneficiary exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary exists or null.
    */
   public final Boolean getExistBeneficiary( int index )
   {
      return _ExistBeneficiary[index];
   }
    
   /**
    * Gets the Beneficiary exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary exists or the specified default value.
    */
   public final boolean getExistBeneficiary( int index, boolean defaultValue )
   {
      return _ExistBeneficiary[index] == null ? defaultValue : _ExistBeneficiary[index].booleanValue();
   }
    
   /**
    * Gets the array of Beneficiary exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary exists values.
    */
   public final Boolean[] getExistBeneficiaryArray()
   {
      return _ExistBeneficiary;
   }
    
   /**
    * Gets the LIF/RIF/LRIF allocations exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LIF/RIF/LRIF allocations exist or null.
    */
   public final Boolean getExistAlloc( int index )
   {
      return _ExistAlloc[index];
   }
    
   /**
    * Gets the LIF/RIF/LRIF allocations exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LIF/RIF/LRIF allocations exist or the specified default value.
    */
   public final boolean getExistAlloc( int index, boolean defaultValue )
   {
      return _ExistAlloc[index] == null ? defaultValue : _ExistAlloc[index].booleanValue();
   }
    
   /**
    * Gets the array of LIF/RIF/LRIF allocations exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LIF/RIF/LRIF allocations exist values.
    */
   public final Boolean[] getExistAllocArray()
   {
      return _ExistAlloc;
   }
    
   /**
    * Gets the Outstanding Wire Order field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Outstanding Wire Order or null.
    */
   public final Boolean getOutWireOrd( int index )
   {
      return _OutWireOrd[index];
   }
    
   /**
    * Gets the Outstanding Wire Order field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Outstanding Wire Order or the specified default value.
    */
   public final boolean getOutWireOrd( int index, boolean defaultValue )
   {
      return _OutWireOrd[index] == null ? defaultValue : _OutWireOrd[index].booleanValue();
   }
    
   /**
    * Gets the array of Outstanding Wire Order fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Outstanding Wire Order values.
    */
   public final Boolean[] getOutWireOrdArray()
   {
      return _OutWireOrd;
   }
    
   /**
    * Gets the Sales Rep is active field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sales Rep is active or null.
    */
   public final Boolean getSlsRepActive( int index )
   {
      return _SlsRepActive[index];
   }
    
   /**
    * Gets the Sales Rep is active field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sales Rep is active or the specified default value.
    */
   public final boolean getSlsRepActive( int index, boolean defaultValue )
   {
      return _SlsRepActive[index] == null ? defaultValue : _SlsRepActive[index].booleanValue();
   }
    
   /**
    * Gets the array of Sales Rep is active fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sales Rep is active values.
    */
   public final Boolean[] getSlsRepActiveArray()
   {
      return _SlsRepActive;
   }
    
   /**
    * Gets the Contract within closing decade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract within closing decade or null.
    */
   public final Boolean getClosingContr( int index )
   {
      return _ClosingContr[index];
   }
    
   /**
    * Gets the Contract within closing decade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract within closing decade or the specified default value.
    */
   public final boolean getClosingContr( int index, boolean defaultValue )
   {
      return _ClosingContr[index] == null ? defaultValue : _ClosingContr[index].booleanValue();
   }
    
   /**
    * Gets the array of Contract within closing decade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract within closing decade values.
    */
   public final Boolean[] getClosingContrArray()
   {
      return _ClosingContr;
   }
    
   /**
    * Gets the Contract matured field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract matured or null.
    */
   public final Boolean getContrMatured( int index )
   {
      return _ContrMatured[index];
   }
    
   /**
    * Gets the Contract matured field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract matured or the specified default value.
    */
   public final boolean getContrMatured( int index, boolean defaultValue )
   {
      return _ContrMatured[index] == null ? defaultValue : _ContrMatured[index].booleanValue();
   }
    
   /**
    * Gets the array of Contract matured fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract matured values.
    */
   public final Boolean[] getContrMaturedArray()
   {
      return _ContrMatured;
   }
    
   /**
    * Gets the Shareholder will turn 69 years this year field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder will turn 69 years this year or null.
    */
   public final Boolean getAge69( int index )
   {
      return _Age69[index];
   }
    
   /**
    * Gets the Shareholder will turn 69 years this year field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder will turn 69 years this year or the specified default value.
    */
   public final boolean getAge69( int index, boolean defaultValue )
   {
      return _Age69[index] == null ? defaultValue : _Age69[index].booleanValue();
   }
    
   /**
    * Gets the array of Shareholder will turn 69 years this year fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder will turn 69 years this year values.
    */
   public final Boolean[] getAge69Array()
   {
      return _Age69;
   }
    
   /**
    * Gets the Pending Death Claim field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pending Death Claim or null.
    */
   public final Boolean getDeathClaim( int index )
   {
      return _DeathClaim[index];
   }
    
   /**
    * Gets the Pending Death Claim field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pending Death Claim or the specified default value.
    */
   public final boolean getDeathClaim( int index, boolean defaultValue )
   {
      return _DeathClaim[index] == null ? defaultValue : _DeathClaim[index].booleanValue();
   }
    
   /**
    * Gets the array of Pending Death Claim fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pending Death Claim values.
    */
   public final Boolean[] getDeathClaimArray()
   {
      return _DeathClaim;
   }
    
   /**
    * Gets the Flag indicating if adding account to the field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if adding account to the or null.
    */
   public final Boolean getAddAcctFlag( int index )
   {
      return _AddAcctFlag[index];
   }
    
   /**
    * Gets the Flag indicating if adding account to the field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if adding account to the or the specified default value.
    */
   public final boolean getAddAcctFlag( int index, boolean defaultValue )
   {
      return _AddAcctFlag[index] == null ? defaultValue : _AddAcctFlag[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if adding account to the fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if adding account to the values.
    */
   public final Boolean[] getAddAcctFlagArray()
   {
      return _AddAcctFlag;
   }
    
   /**
    * Gets the Pending Trade exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pending Trade exists or null.
    */
   public final Boolean getPendingTrade( int index )
   {
      return _PendingTrade[index];
   }
    
   /**
    * Gets the Pending Trade exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pending Trade exists or the specified default value.
    */
   public final boolean getPendingTrade( int index, boolean defaultValue )
   {
      return _PendingTrade[index] == null ? defaultValue : _PendingTrade[index].booleanValue();
   }
    
   /**
    * Gets the array of Pending Trade exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pending Trade exists values.
    */
   public final Boolean[] getPendingTradeArray()
   {
      return _PendingTrade;
   }
    
   /**
    * Gets the Certificates Issued(Cert-Detl exists) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Certificates Issued(Cert-Detl exists) or null.
    */
   public final Boolean getCertificates( int index )
   {
      return _Certificates[index];
   }
    
   /**
    * Gets the Certificates Issued(Cert-Detl exists) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Certificates Issued(Cert-Detl exists) or the specified default value.
    */
   public final boolean getCertificates( int index, boolean defaultValue )
   {
      return _Certificates[index] == null ? defaultValue : _Certificates[index].booleanValue();
   }
    
   /**
    * Gets the array of Certificates Issued(Cert-Detl exists) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Certificates Issued(Cert-Detl exists) values.
    */
   public final Boolean[] getCertificatesArray()
   {
      return _Certificates;
   }
    
   /**
    * Gets the Systematic Transfer setup field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Systematic Transfer setup or null.
    */
   public final Boolean getSystemTrsfr( int index )
   {
      return _SystemTrsfr[index];
   }
    
   /**
    * Gets the Systematic Transfer setup field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Systematic Transfer setup or the specified default value.
    */
   public final boolean getSystemTrsfr( int index, boolean defaultValue )
   {
      return _SystemTrsfr[index] == null ? defaultValue : _SystemTrsfr[index].booleanValue();
   }
    
   /**
    * Gets the array of Systematic Transfer setup fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Systematic Transfer setup values.
    */
   public final Boolean[] getSystemTrsfrArray()
   {
      return _SystemTrsfr;
   }
    
   /**
    * Gets the PAC setup field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAC setup or null.
    */
   public final Boolean getPAC( int index )
   {
      return _PAC[index];
   }
    
   /**
    * Gets the PAC setup field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC setup or the specified default value.
    */
   public final boolean getPAC( int index, boolean defaultValue )
   {
      return _PAC[index] == null ? defaultValue : _PAC[index].booleanValue();
   }
    
   /**
    * Gets the array of PAC setup fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAC setup values.
    */
   public final Boolean[] getPACArray()
   {
      return _PAC;
   }
    
   /**
    * Gets the SWP setup field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SWP setup or null.
    */
   public final Boolean getSWP( int index )
   {
      return _SWP[index];
   }
    
   /**
    * Gets the SWP setup field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SWP setup or the specified default value.
    */
   public final boolean getSWP( int index, boolean defaultValue )
   {
      return _SWP[index] == null ? defaultValue : _SWP[index].booleanValue();
   }
    
   /**
    * Gets the array of SWP setup fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SWP setup values.
    */
   public final Boolean[] getSWPArray()
   {
      return _SWP;
   }
    
   /**
    * Gets the Account Allocation exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Allocation exists or null.
    */
   public final Boolean getAcctAlloc( int index )
   {
      return _AcctAlloc[index];
   }
    
   /**
    * Gets the Account Allocation exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Allocation exists or the specified default value.
    */
   public final boolean getAcctAlloc( int index, boolean defaultValue )
   {
      return _AcctAlloc[index] == null ? defaultValue : _AcctAlloc[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Allocation exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Allocation exists values.
    */
   public final Boolean[] getAcctAllocArray()
   {
      return _AcctAlloc;
   }
    
   /**
    * Gets the Clan Plan setup field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Clan Plan setup or null.
    */
   public final Boolean getClanPlan( int index )
   {
      return _ClanPlan[index];
   }
    
   /**
    * Gets the Clan Plan setup field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Clan Plan setup or the specified default value.
    */
   public final boolean getClanPlan( int index, boolean defaultValue )
   {
      return _ClanPlan[index] == null ? defaultValue : _ClanPlan[index].booleanValue();
   }
    
   /**
    * Gets the array of Clan Plan setup fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Clan Plan setup values.
    */
   public final Boolean[] getClanPlanArray()
   {
      return _ClanPlan;
   }
    
   /**
    * Gets the Unsettled transaction exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unsettled transaction exists or null.
    */
   public final Boolean getUnsettledTrn( int index )
   {
      return _UnsettledTrn[index];
   }
    
   /**
    * Gets the Unsettled transaction exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unsettled transaction exists or the specified default value.
    */
   public final boolean getUnsettledTrn( int index, boolean defaultValue )
   {
      return _UnsettledTrn[index] == null ? defaultValue : _UnsettledTrn[index].booleanValue();
   }
    
   /**
    * Gets the array of Unsettled transaction exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unsettled transaction exists values.
    */
   public final Boolean[] getUnsettledTrnArray()
   {
      return _UnsettledTrn;
   }
    
   /**
    * Gets the Transaction Found? field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transaction Found? or null.
    */
   public final Boolean getTransFound( int index )
   {
      return _TransFound[index];
   }
    
   /**
    * Gets the Transaction Found? field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transaction Found? or the specified default value.
    */
   public final boolean getTransFound( int index, boolean defaultValue )
   {
      return _TransFound[index] == null ? defaultValue : _TransFound[index].booleanValue();
   }
    
   /**
    * Gets the array of Transaction Found? fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transaction Found? values.
    */
   public final Boolean[] getTransFoundArray()
   {
      return _TransFound;
   }
    
   /**
    * Gets the First Effective Date of Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the First Effective Date of Account or null.
    */
   public final Date getFirstEffective( int index )
   {
      return _FirstEffective[index];
   }
    
   /**
    * Gets the First Effective Date of Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Effective Date of Account or the specified default value.
    */
   public final Date getFirstEffective( int index, Date defaultValue )
   {
      return _FirstEffective[index] == null ? defaultValue : _FirstEffective[index];
   }
    
   /**
    * Gets the array of First Effective Date of Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of First Effective Date of Account values.
    */
   public final Date[] getFirstEffectiveArray()
   {
      return _FirstEffective;
   }
    
   /**
    * Gets the Affect Maximum? field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Affect Maximum? or null.
    */
   public final Boolean getMaxApplies( int index )
   {
      return _MaxApplies[index];
   }
    
   /**
    * Gets the Affect Maximum? field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Affect Maximum? or the specified default value.
    */
   public final boolean getMaxApplies( int index, boolean defaultValue )
   {
      return _MaxApplies[index] == null ? defaultValue : _MaxApplies[index].booleanValue();
   }
    
   /**
    * Gets the array of Affect Maximum? fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Affect Maximum? values.
    */
   public final Boolean[] getMaxAppliesArray()
   {
      return _MaxApplies;
   }
    
   /**
    * Gets the Qualified plan allowed for tax type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Qualified plan allowed for tax type or null.
    */
   public final Boolean getRRIFQualified( int index )
   {
      return _RRIFQualified[index];
   }
    
   /**
    * Gets the Qualified plan allowed for tax type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Qualified plan allowed for tax type or the specified default value.
    */
   public final boolean getRRIFQualified( int index, boolean defaultValue )
   {
      return _RRIFQualified[index] == null ? defaultValue : _RRIFQualified[index].booleanValue();
   }
    
   /**
    * Gets the array of Qualified plan allowed for tax type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Qualified plan allowed for tax type values.
    */
   public final Boolean[] getRRIFQualifiedArray()
   {
      return _RRIFQualified;
   }
    
   /**
    * Gets the Legal min withdrawal age field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Legal min withdrawal age or null.
    */
   public final Integer getLegMinWithAge( int index )
   {
      return _LegMinWithAge[index];
   }
    
   /**
    * Gets the Legal min withdrawal age field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Legal min withdrawal age or the specified default value.
    */
   public final int getLegMinWithAge( int index, int defaultValue )
   {
      return _LegMinWithAge[index] == null ? defaultValue : _LegMinWithAge[index].intValue();
   }
    
   /**
    * Gets the array of Legal min withdrawal age fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Legal min withdrawal age values.
    */
   public final Integer[] getLegMinWithAgeArray()
   {
      return _LegMinWithAge;
   }
    
   /**
    * Gets the Tax type is locked in plan type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax type is locked in plan type or null.
    */
   public final Boolean getLockedIn( int index )
   {
      return _LockedIn[index];
   }
    
   /**
    * Gets the Tax type is locked in plan type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax type is locked in plan type or the specified default value.
    */
   public final boolean getLockedIn( int index, boolean defaultValue )
   {
      return _LockedIn[index] == null ? defaultValue : _LockedIn[index].booleanValue();
   }
    
   /**
    * Gets the array of Tax type is locked in plan type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax type is locked in plan type values.
    */
   public final Boolean[] getLockedInArray()
   {
      return _LockedIn;
   }
    
   /**
    * Gets the Is federal jurisdiction allowed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Is federal jurisdiction allowed or null.
    */
   public final Boolean getFedJurAllowed( int index )
   {
      return _FedJurAllowed[index];
   }
    
   /**
    * Gets the Is federal jurisdiction allowed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Is federal jurisdiction allowed or the specified default value.
    */
   public final boolean getFedJurAllowed( int index, boolean defaultValue )
   {
      return _FedJurAllowed[index] == null ? defaultValue : _FedJurAllowed[index].booleanValue();
   }
    
   /**
    * Gets the array of Is federal jurisdiction allowed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Is federal jurisdiction allowed values.
    */
   public final Boolean[] getFedJurAllowedArray()
   {
      return _FedJurAllowed;
   }
    
   /**
    * Gets the Minimum Age field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Minimum Age or null.
    */
   public final Integer getMinAge( int index )
   {
      return _MinAge[index];
   }
    
   /**
    * Gets the Minimum Age field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Age or the specified default value.
    */
   public final int getMinAge( int index, int defaultValue )
   {
      return _MinAge[index] == null ? defaultValue : _MinAge[index].intValue();
   }
    
   /**
    * Gets the array of Minimum Age fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Minimum Age values.
    */
   public final Integer[] getMinAgeArray()
   {
      return _MinAge;
   }
    
   /**
    * Gets the Maximum Age field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maximum Age or null.
    */
   public final Integer getMaxAge( int index )
   {
      return _MaxAge[index];
   }
    
   /**
    * Gets the Maximum Age field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maximum Age or the specified default value.
    */
   public final int getMaxAge( int index, int defaultValue )
   {
      return _MaxAge[index] == null ? defaultValue : _MaxAge[index].intValue();
   }
    
   /**
    * Gets the array of Maximum Age fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maximum Age values.
    */
   public final Integer[] getMaxAgeArray()
   {
      return _MaxAge;
   }
    
   /**
    * Gets the LipTaxByJuris exists for shareholder's tax juris field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LipTaxByJuris exists for shareholder's tax juris or null.
    */
   public final Boolean getTaxTypeRules( int index )
   {
      return _TaxTypeRules[index];
   }
    
   /**
    * Gets the LipTaxByJuris exists for shareholder's tax juris field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LipTaxByJuris exists for shareholder's tax juris or the specified default value.
    */
   public final boolean getTaxTypeRules( int index, boolean defaultValue )
   {
      return _TaxTypeRules[index] == null ? defaultValue : _TaxTypeRules[index].booleanValue();
   }
    
   /**
    * Gets the array of LipTaxByJuris exists for shareholder's tax juris fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LipTaxByJuris exists for shareholder's tax juris values.
    */
   public final Boolean[] getTaxTypeRulesArray()
   {
      return _TaxTypeRules;
   }
    
   /**
    * Gets the LipTaxByJuris exists for '0000' tax juris field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the LipTaxByJuris exists for '0000' tax juris or null.
    */
   public final Boolean getDefTaxTypeRules( int index )
   {
      return _DefTaxTypeRules[index];
   }
    
   /**
    * Gets the LipTaxByJuris exists for '0000' tax juris field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LipTaxByJuris exists for '0000' tax juris or the specified default value.
    */
   public final boolean getDefTaxTypeRules( int index, boolean defaultValue )
   {
      return _DefTaxTypeRules[index] == null ? defaultValue : _DefTaxTypeRules[index].booleanValue();
   }
    
   /**
    * Gets the array of LipTaxByJuris exists for '0000' tax juris fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of LipTaxByJuris exists for '0000' tax juris values.
    */
   public final Boolean[] getDefTaxTypeRulesArray()
   {
      return _DefTaxTypeRules;
   }
    
   /**
    * Gets the Flag indicating if account tax type is configured for Foreign Content rebalancing field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if account tax type is configured for Foreign Content rebalancing or null.
    */
   public final Boolean getFCConfig( int index )
   {
      return _FCConfig[index];
   }
    
   /**
    * Gets the Flag indicating if account tax type is configured for Foreign Content rebalancing field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if account tax type is configured for Foreign Content rebalancing or the specified default value.
    */
   public final boolean getFCConfig( int index, boolean defaultValue )
   {
      return _FCConfig[index] == null ? defaultValue : _FCConfig[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if account tax type is configured for Foreign Content rebalancing fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if account tax type is configured for Foreign Content rebalancing values.
    */
   public final Boolean[] getFCConfigArray()
   {
      return _FCConfig;
   }
    
   /**
    * Gets the Flag indicating if account has  Stop Foreign Content Excess Rebalancing field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if account has  Stop Foreign Content Excess Rebalancing or null.
    */
   public final Boolean getStopFCrebal( int index )
   {
      return _StopFCrebal[index];
   }
    
   /**
    * Gets the Flag indicating if account has  Stop Foreign Content Excess Rebalancing field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if account has  Stop Foreign Content Excess Rebalancing or the specified default value.
    */
   public final boolean getStopFCrebal( int index, boolean defaultValue )
   {
      return _StopFCrebal[index] == null ? defaultValue : _StopFCrebal[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if account has  Stop Foreign Content Excess Rebalancing fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if account has  Stop Foreign Content Excess Rebalancing values.
    */
   public final Boolean[] getStopFCrebalArray()
   {
      return _StopFCrebal;
   }
    
   /**
    * Gets the Foreign Content Override flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Foreign Content Override flag or null.
    */
   public final Boolean getFCOverrides( int index )
   {
      return _FCOverrides[index];
   }
    
   /**
    * Gets the Foreign Content Override flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Foreign Content Override flag or the specified default value.
    */
   public final boolean getFCOverrides( int index, boolean defaultValue )
   {
      return _FCOverrides[index] == null ? defaultValue : _FCOverrides[index].booleanValue();
   }
    
   /**
    * Gets the array of Foreign Content Override flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Foreign Content Override flag values.
    */
   public final Boolean[] getFCOverridesArray()
   {
      return _FCOverrides;
   }
    
   /**
    * Gets the Flag indicating if entire account is locked field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if entire account is locked or null.
    */
   public final Boolean getAllLocked( int index )
   {
      return _AllLocked[index];
   }
    
   /**
    * Gets the Flag indicating if entire account is locked field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if entire account is locked or the specified default value.
    */
   public final boolean getAllLocked( int index, boolean defaultValue )
   {
      return _AllLocked[index] == null ? defaultValue : _AllLocked[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if entire account is locked fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if entire account is locked values.
    */
   public final Boolean[] getAllLockedArray()
   {
      return _AllLocked;
   }
    
   /**
    * Gets the Flag indicating if account has been coded as assigned field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if account has been coded as assigned or null.
    */
   public final Boolean getAcctLocked( int index )
   {
      return _AcctLocked[index];
   }
    
   /**
    * Gets the Flag indicating if account has been coded as assigned field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if account has been coded as assigned or the specified default value.
    */
   public final boolean getAcctLocked( int index, boolean defaultValue )
   {
      return _AcctLocked[index] == null ? defaultValue : _AcctLocked[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if account has been coded as assigned fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if account has been coded as assigned values.
    */
   public final Boolean[] getAcctLockedArray()
   {
      return _AcctLocked;
   }
    
   /**
    * Gets the Flag indicating if  account is selfdirected type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if  account is selfdirected type or null.
    */
   public final Boolean getSelfDirected( int index )
   {
      return _SelfDirected[index];
   }
    
   /**
    * Gets the Flag indicating if  account is selfdirected type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if  account is selfdirected type or the specified default value.
    */
   public final boolean getSelfDirected( int index, boolean defaultValue )
   {
      return _SelfDirected[index] == null ? defaultValue : _SelfDirected[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if  account is selfdirected type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if  account is selfdirected type values.
    */
   public final Boolean[] getSelfDirectedArray()
   {
      return _SelfDirected;
   }
    
   /**
    * Gets the Flag indicating what plan type is the account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating what plan type is the account or null.
    */
   public final String getPlanType( int index )
   {
      return _PlanType[index];
   }
    
   /**
    * Gets the Flag indicating what plan type is the account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating what plan type is the account or the specified default value.
    */
   public final String getPlanType( int index, String defaultValue )
   {
      return _PlanType[index] == null ? defaultValue : _PlanType[index];
   }
    
   /**
    * Gets the array of Flag indicating what plan type is the account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating what plan type is the account values.
    */
   public final String[] getPlanTypeArray()
   {
      return _PlanType;
   }
    
   /**
    * Gets the Flag indicating if Spouse's SIN is valid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if Spouse's SIN is valid or null.
    */
   public final Boolean getValidSpSIN( int index )
   {
      return _ValidSpSIN[index];
   }
    
   /**
    * Gets the Flag indicating if Spouse's SIN is valid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Spouse's SIN is valid or the specified default value.
    */
   public final boolean getValidSpSIN( int index, boolean defaultValue )
   {
      return _ValidSpSIN[index] == null ? defaultValue : _ValidSpSIN[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if Spouse's SIN is valid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if Spouse's SIN is valid values.
    */
   public final Boolean[] getValidSpSINArray()
   {
      return _ValidSpSIN;
   }
    
   /**
    * Gets the Flag indicating if RIF setup exist to RIF acct field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if RIF setup exist to RIF acct or null.
    */
   public final Boolean getRIFExist( int index )
   {
      return _RIFExist[index];
   }
    
   /**
    * Gets the Flag indicating if RIF setup exist to RIF acct field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if RIF setup exist to RIF acct or the specified default value.
    */
   public final boolean getRIFExist( int index, boolean defaultValue )
   {
      return _RIFExist[index] == null ? defaultValue : _RIFExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if RIF setup exist to RIF acct fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if RIF setup exist to RIF acct values.
    */
   public final Boolean[] getRIFExistArray()
   {
      return _RIFExist;
   }
    
   /**
    * Gets the Flag indicating status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating status or null.
    */
   public final Boolean getDeathStat( int index )
   {
      return _DeathStat[index];
   }
    
   /**
    * Gets the Flag indicating status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating status or the specified default value.
    */
   public final boolean getDeathStat( int index, boolean defaultValue )
   {
      return _DeathStat[index] == null ? defaultValue : _DeathStat[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating status values.
    */
   public final Boolean[] getDeathStatArray()
   {
      return _DeathStat;
   }
    
   /**
    * Gets the Flag indicating if  account has BEL fund holdings field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if  account has BEL fund holdings or null.
    */
   public final Boolean getACBExist( int index )
   {
      return _ACBExist[index];
   }
    
   /**
    * Gets the Flag indicating if  account has BEL fund holdings field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if  account has BEL fund holdings or the specified default value.
    */
   public final boolean getACBExist( int index, boolean defaultValue )
   {
      return _ACBExist[index] == null ? defaultValue : _ACBExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if  account has BEL fund holdings fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if  account has BEL fund holdings values.
    */
   public final Boolean[] getACBExistArray()
   {
      return _ACBExist;
   }
    
   /**
    * Gets the Flag indicating if Account has MM holdings field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if Account has MM holdings or null.
    */
   public final Boolean getIntAccrExist( int index )
   {
      return _IntAccrExist[index];
   }
    
   /**
    * Gets the Flag indicating if Account has MM holdings field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Account has MM holdings or the specified default value.
    */
   public final boolean getIntAccrExist( int index, boolean defaultValue )
   {
      return _IntAccrExist[index] == null ? defaultValue : _IntAccrExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if Account has MM holdings fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if Account has MM holdings values.
    */
   public final Boolean[] getIntAccrExistArray()
   {
      return _IntAccrExist;
   }
    
   /**
    * Gets the Flag indicating if distribution exist for the account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if distribution exist for the account or null.
    */
   public final Boolean getDistribExist( int index )
   {
      return _DistribExist[index];
   }
    
   /**
    * Gets the Flag indicating if distribution exist for the account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if distribution exist for the account or the specified default value.
    */
   public final boolean getDistribExist( int index, boolean defaultValue )
   {
      return _DistribExist[index] == null ? defaultValue : _DistribExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if distribution exist for the account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if distribution exist for the account values.
    */
   public final Boolean[] getDistribExistArray()
   {
      return _DistribExist;
   }
    
   /**
    * Gets the Flag indication if outstanding cheque exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indication if outstanding cheque exist or null.
    */
   public final Boolean getChequeExist( int index )
   {
      return _ChequeExist[index];
   }
    
   /**
    * Gets the Flag indication if outstanding cheque exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indication if outstanding cheque exist or the specified default value.
    */
   public final boolean getChequeExist( int index, boolean defaultValue )
   {
      return _ChequeExist[index] == null ? defaultValue : _ChequeExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indication if outstanding cheque exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indication if outstanding cheque exist values.
    */
   public final Boolean[] getChequeExistArray()
   {
      return _ChequeExist;
   }
    
   /**
    * Gets the Flag indicating if contract for account exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if contract for account exist or null.
    */
   public final Boolean getContractExist( int index )
   {
      return _ContractExist[index];
   }
    
   /**
    * Gets the Flag indicating if contract for account exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if contract for account exist or the specified default value.
    */
   public final boolean getContractExist( int index, boolean defaultValue )
   {
      return _ContractExist[index] == null ? defaultValue : _ContractExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if contract for account exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if contract for account exist values.
    */
   public final Boolean[] getContractExistArray()
   {
      return _ContractExist;
   }
    
   /**
    * Gets the Outstanding LLP field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Outstanding LLP or null.
    */
   public final String getOutstLLP( int index )
   {
      return _OutstLLP[index];
   }
    
   /**
    * Gets the Outstanding LLP field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Outstanding LLP or the specified default value.
    */
   public final String getOutstLLP( int index, String defaultValue )
   {
      return _OutstLLP[index] == null ? defaultValue : _OutstLLP[index];
   }
    
   /**
    * Gets the array of Outstanding LLP fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Outstanding LLP values.
    */
   public final String[] getOutstLLPArray()
   {
      return _OutstLLP;
   }
    
   /**
    * Gets the Social Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Social Code or null.
    */
   public final String getSocialCode( int index )
   {
      return _SocialCode[index];
   }
    
   /**
    * Gets the Social Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Social Code or the specified default value.
    */
   public final String getSocialCode( int index, String defaultValue )
   {
      return _SocialCode[index] == null ? defaultValue : _SocialCode[index];
   }
    
   /**
    * Gets the array of Social Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Social Code values.
    */
   public final String[] getSocialCodeArray()
   {
      return _SocialCode;
   }
    
   /**
    * Gets the Social Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Social Code Description or null.
    */
   public final String getSocialCodeDesc( int index )
   {
      return _SocialCodeDesc[index];
   }
    
   /**
    * Gets the Social Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Social Code Description or the specified default value.
    */
   public final String getSocialCodeDesc( int index, String defaultValue )
   {
      return _SocialCodeDesc[index] == null ? defaultValue : _SocialCodeDesc[index];
   }
    
   /**
    * Gets the array of Social Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Social Code Description values.
    */
   public final String[] getSocialCodeDescArray()
   {
      return _SocialCodeDesc;
   }
    
   /**
    * Gets the Save Plan Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Save Plan Exist or null.
    */
   public final Boolean getSavePlanExist( int index )
   {
      return _SavePlanExist[index];
   }
    
   /**
    * Gets the Save Plan Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Save Plan Exist or the specified default value.
    */
   public final boolean getSavePlanExist( int index, boolean defaultValue )
   {
      return _SavePlanExist[index] == null ? defaultValue : _SavePlanExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Save Plan Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Save Plan Exist values.
    */
   public final Boolean[] getSavePlanExistArray()
   {
      return _SavePlanExist;
   }
    
   /**
    * Gets the Product Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Product Code or null.
    */
   public final String getProdCode( int index )
   {
      return _ProdCode[index];
   }
    
   /**
    * Gets the Product Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Product Code or the specified default value.
    */
   public final String getProdCode( int index, String defaultValue )
   {
      return _ProdCode[index] == null ? defaultValue : _ProdCode[index];
   }
    
   /**
    * Gets the array of Product Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Product Code values.
    */
   public final String[] getProdCodeArray()
   {
      return _ProdCode;
   }
    
   /**
    * Gets the Account Level Commission Exists Y/N field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Level Commission Exists Y/N or null.
    */
   public final Boolean getAcctCommExists( int index )
   {
      return _AcctCommExists[index];
   }
    
   /**
    * Gets the Account Level Commission Exists Y/N field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Level Commission Exists Y/N or the specified default value.
    */
   public final boolean getAcctCommExists( int index, boolean defaultValue )
   {
      return _AcctCommExists[index] == null ? defaultValue : _AcctCommExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Level Commission Exists Y/N fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Level Commission Exists Y/N values.
    */
   public final Boolean[] getAcctCommExistsArray()
   {
      return _AcctCommExists;
   }
    
   /**
    * Gets the GST Exempt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GST Exempt or null.
    */
   public final Boolean getGSTExempt( int index )
   {
      return _GSTExempt[index];
   }
    
   /**
    * Gets the GST Exempt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GST Exempt or the specified default value.
    */
   public final boolean getGSTExempt( int index, boolean defaultValue )
   {
      return _GSTExempt[index] == null ? defaultValue : _GSTExempt[index].booleanValue();
   }
    
   /**
    * Gets the array of GST Exempt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GST Exempt values.
    */
   public final Boolean[] getGSTExemptArray()
   {
      return _GSTExempt;
   }
    
   /**
    * Gets the Account Fee Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Fee Exist or null.
    */
   public final Boolean getAcctFeesExist( int index )
   {
      return _AcctFeesExist[index];
   }
    
   /**
    * Gets the Account Fee Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Fee Exist or the specified default value.
    */
   public final boolean getAcctFeesExist( int index, boolean defaultValue )
   {
      return _AcctFeesExist[index] == null ? defaultValue : _AcctFeesExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Fee Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Fee Exist values.
    */
   public final Boolean[] getAcctFeesExistArray()
   {
      return _AcctFeesExist;
   }
    
   /**
    * Gets the Apply PST  y/n field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Apply PST  y/n or null.
    */
   public final Boolean getApplyPST( int index )
   {
      return _ApplyPST[index];
   }
    
   /**
    * Gets the Apply PST  y/n field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Apply PST  y/n or the specified default value.
    */
   public final boolean getApplyPST( int index, boolean defaultValue )
   {
      return _ApplyPST[index] == null ? defaultValue : _ApplyPST[index].booleanValue();
   }
    
   /**
    * Gets the array of Apply PST  y/n fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Apply PST  y/n values.
    */
   public final Boolean[] getApplyPSTArray()
   {
      return _ApplyPST;
   }
    
   /**
    * Gets the Unisex field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unisex or null.
    */
   public final Boolean getUnisex( int index )
   {
      return _Unisex[index];
   }
    
   /**
    * Gets the Unisex field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unisex or the specified default value.
    */
   public final boolean getUnisex( int index, boolean defaultValue )
   {
      return _Unisex[index] == null ? defaultValue : _Unisex[index].booleanValue();
   }
    
   /**
    * Gets the array of Unisex fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unisex values.
    */
   public final Boolean[] getUnisexArray()
   {
      return _Unisex;
   }
    
   /**
    * Gets the Sex Distinct field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sex Distinct or null.
    */
   public final Boolean getSexDistinct( int index )
   {
      return _SexDistinct[index];
   }
    
   /**
    * Gets the Sex Distinct field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sex Distinct or the specified default value.
    */
   public final boolean getSexDistinct( int index, boolean defaultValue )
   {
      return _SexDistinct[index] == null ? defaultValue : _SexDistinct[index].booleanValue();
   }
    
   /**
    * Gets the array of Sex Distinct fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sex Distinct values.
    */
   public final Boolean[] getSexDistinctArray()
   {
      return _SexDistinct;
   }
    
   /**
    * Gets the Bank Charge field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Bank Charge or null.
    */
   public final String getBankCharge( int index )
   {
      return _BankCharge[index];
   }
    
   /**
    * Gets the Bank Charge field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Bank Charge or the specified default value.
    */
   public final String getBankCharge( int index, String defaultValue )
   {
      return _BankCharge[index] == null ? defaultValue : _BankCharge[index];
   }
    
   /**
    * Gets the array of Bank Charge fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Bank Charge values.
    */
   public final String[] getBankChargeArray()
   {
      return _BankCharge;
   }
    
   /**
    * Gets the Consolidation EFT field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Consolidation EFT or null.
    */
   public final String getConsolidEFT( int index )
   {
      return _ConsolidEFT[index];
   }
    
   /**
    * Gets the Consolidation EFT field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consolidation EFT or the specified default value.
    */
   public final String getConsolidEFT( int index, String defaultValue )
   {
      return _ConsolidEFT[index] == null ? defaultValue : _ConsolidEFT[index];
   }
    
   /**
    * Gets the array of Consolidation EFT fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Consolidation EFT values.
    */
   public final String[] getConsolidEFTArray()
   {
      return _ConsolidEFT;
   }
    
   /**
    * Gets the Pension Juris Info Avail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pension Juris Info Avail or null.
    */
   public final Boolean getPensionJurisAvail( int index )
   {
      return _PensionJurisAvail[index];
   }
    
   /**
    * Gets the Pension Juris Info Avail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pension Juris Info Avail or the specified default value.
    */
   public final boolean getPensionJurisAvail( int index, boolean defaultValue )
   {
      return _PensionJurisAvail[index] == null ? defaultValue : _PensionJurisAvail[index].booleanValue();
   }
    
   /**
    * Gets the array of Pension Juris Info Avail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pension Juris Info Avail values.
    */
   public final Boolean[] getPensionJurisAvailArray()
   {
      return _PensionJurisAvail;
   }
    
   /**
    * Gets the settled date of the first settled trade field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the settled date of the first settled trade or null.
    */
   public final Date getFirstSettleDate( int index )
   {
      return _FirstSettleDate[index];
   }
    
   /**
    * Gets the settled date of the first settled trade field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the settled date of the first settled trade or the specified default value.
    */
   public final Date getFirstSettleDate( int index, Date defaultValue )
   {
      return _FirstSettleDate[index] == null ? defaultValue : _FirstSettleDate[index];
   }
    
   /**
    * Gets the array of settled date of the first settled trade fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of settled date of the first settled trade values.
    */
   public final Date[] getFirstSettleDateArray()
   {
      return _FirstSettleDate;
   }
    
   /**
    * Gets the Investment Profile field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Investment Profile or null.
    */
   public final String getAMSROCode( int index )
   {
      return _AMSROCode[index];
   }
    
   /**
    * Gets the Investment Profile field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Profile or the specified default value.
    */
   public final String getAMSROCode( int index, String defaultValue )
   {
      return _AMSROCode[index] == null ? defaultValue : _AMSROCode[index];
   }
    
   /**
    * Gets the array of Investment Profile fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Investment Profile values.
    */
   public final String[] getAMSROCodeArray()
   {
      return _AMSROCode;
   }
    
   /**
    * Gets the Mangement Fee Option field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mangement Fee Option or null.
    */
   public final String getMgmtFeePayOption( int index )
   {
      return _MgmtFeePayOption[index];
   }
    
   /**
    * Gets the Mangement Fee Option field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mangement Fee Option or the specified default value.
    */
   public final String getMgmtFeePayOption( int index, String defaultValue )
   {
      return _MgmtFeePayOption[index] == null ? defaultValue : _MgmtFeePayOption[index];
   }
    
   /**
    * Gets the array of Mangement Fee Option fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mangement Fee Option values.
    */
   public final String[] getMgmtFeePayOptionArray()
   {
      return _MgmtFeePayOption;
   }
    
   /**
    * Gets the Created Today field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Created Today or null.
    */
   public final Boolean getCreatedToday( int index )
   {
      return _CreatedToday[index];
   }
    
   /**
    * Gets the Created Today field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created Today or the specified default value.
    */
   public final boolean getCreatedToday( int index, boolean defaultValue )
   {
      return _CreatedToday[index] == null ? defaultValue : _CreatedToday[index].booleanValue();
   }
    
   /**
    * Gets the array of Created Today fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Created Today values.
    */
   public final Boolean[] getCreatedTodayArray()
   {
      return _CreatedToday;
   }
    
   /**
    * Gets the Protect Contract Exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Protect Contract Exists or null.
    */
   public final Boolean getProtContractExists( int index )
   {
      return _ProtContractExists[index];
   }
    
   /**
    * Gets the Protect Contract Exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Protect Contract Exists or the specified default value.
    */
   public final boolean getProtContractExists( int index, boolean defaultValue )
   {
      return _ProtContractExists[index] == null ? defaultValue : _ProtContractExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Protect Contract Exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Protect Contract Exists values.
    */
   public final Boolean[] getProtContractExistsArray()
   {
      return _ProtContractExists;
   }
    
   /**
    * Gets the AcctCategory record exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctCategory record exists or null.
    */
   public final Boolean getAcctCatExists( int index )
   {
      return _AcctCatExists[index];
   }
    
   /**
    * Gets the AcctCategory record exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctCategory record exists or the specified default value.
    */
   public final boolean getAcctCatExists( int index, boolean defaultValue )
   {
      return _AcctCatExists[index] == null ? defaultValue : _AcctCatExists[index].booleanValue();
   }
    
   /**
    * Gets the array of AcctCategory record exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctCategory record exists values.
    */
   public final Boolean[] getAcctCatExistsArray()
   {
      return _AcctCatExists;
   }
    
   /**
    * Gets the Early Redemption Fees will be charged field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Early Redemption Fees will be charged or null.
    */
   public final Boolean getChargeERFee( int index )
   {
      return _ChargeERFee[index];
   }
    
   /**
    * Gets the Early Redemption Fees will be charged field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Early Redemption Fees will be charged or the specified default value.
    */
   public final boolean getChargeERFee( int index, boolean defaultValue )
   {
      return _ChargeERFee[index] == null ? defaultValue : _ChargeERFee[index].booleanValue();
   }
    
   /**
    * Gets the array of Early Redemption Fees will be charged fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Early Redemption Fees will be charged values.
    */
   public final Boolean[] getChargeERFeeArray()
   {
      return _ChargeERFee;
   }
    
   /**
    * Gets the ShortTerm Transfer Fee wil be charged field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ShortTerm Transfer Fee wil be charged or null.
    */
   public final Boolean getChargeSTTRFee( int index )
   {
      return _ChargeSTTRFee[index];
   }
    
   /**
    * Gets the ShortTerm Transfer Fee wil be charged field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ShortTerm Transfer Fee wil be charged or the specified default value.
    */
   public final boolean getChargeSTTRFee( int index, boolean defaultValue )
   {
      return _ChargeSTTRFee[index] == null ? defaultValue : _ChargeSTTRFee[index].booleanValue();
   }
    
   /**
    * Gets the array of ShortTerm Transfer Fee wil be charged fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ShortTerm Transfer Fee wil be charged values.
    */
   public final Boolean[] getChargeSTTRFeeArray()
   {
      return _ChargeSTTRFee;
   }
    
   /**
    * Gets the Use Broker Mangement Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Use Broker Mangement Fee or null.
    */
   public final Boolean getUseBrokerMF( int index )
   {
      return _UseBrokerMF[index];
   }
    
   /**
    * Gets the Use Broker Mangement Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Use Broker Mangement Fee or the specified default value.
    */
   public final boolean getUseBrokerMF( int index, boolean defaultValue )
   {
      return _UseBrokerMF[index] == null ? defaultValue : _UseBrokerMF[index].booleanValue();
   }
    
   /**
    * Gets the array of Use Broker Mangement Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Use Broker Mangement Fee values.
    */
   public final Boolean[] getUseBrokerMFArray()
   {
      return _UseBrokerMF;
   }
    
   /**
    * Gets the StopAMSRebal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the StopAMSRebal or null.
    */
   public final Boolean getStopAMSRebal( int index )
   {
      return _StopAMSRebal[index];
   }
    
   /**
    * Gets the StopAMSRebal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the StopAMSRebal or the specified default value.
    */
   public final boolean getStopAMSRebal( int index, boolean defaultValue )
   {
      return _StopAMSRebal[index] == null ? defaultValue : _StopAMSRebal[index].booleanValue();
   }
    
   /**
    * Gets the array of StopAMSRebal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of StopAMSRebal values.
    */
   public final Boolean[] getStopAMSRebalArray()
   {
      return _StopAMSRebal;
   }
    
   /**
    * Gets the Account Purpose field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Purpose or null.
    */
   public final String getAcctPurpose( int index )
   {
      return _AcctPurpose[index];
   }
    
   /**
    * Gets the Account Purpose field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Purpose or the specified default value.
    */
   public final String getAcctPurpose( int index, String defaultValue )
   {
      return _AcctPurpose[index] == null ? defaultValue : _AcctPurpose[index];
   }
    
   /**
    * Gets the array of Account Purpose fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Purpose values.
    */
   public final String[] getAcctPurposeArray()
   {
      return _AcctPurpose;
   }
    
   /**
    * Gets the Additional Information field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Additional Information or null.
    */
   public final String getAdditionalInfo( int index )
   {
      return _AdditionalInfo[index];
   }
    
   /**
    * Gets the Additional Information field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional Information or the specified default value.
    */
   public final String getAdditionalInfo( int index, String defaultValue )
   {
      return _AdditionalInfo[index] == null ? defaultValue : _AdditionalInfo[index];
   }
    
   /**
    * Gets the array of Additional Information fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Additional Information values.
    */
   public final String[] getAdditionalInfoArray()
   {
      return _AdditionalInfo;
   }
    
   /**
    * Gets the Business Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Business Number or null.
    */
   public final String getBusinessNo( int index )
   {
      return _BusinessNo[index];
   }
    
   /**
    * Gets the Business Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Business Number or the specified default value.
    */
   public final String getBusinessNo( int index, String defaultValue )
   {
      return _BusinessNo[index] == null ? defaultValue : _BusinessNo[index];
   }
    
   /**
    * Gets the array of Business Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Business Number values.
    */
   public final String[] getBusinessNoArray()
   {
      return _BusinessNo;
   }
    
   /**
    * Gets the Memorable Place field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Memorable Place or null.
    */
   public final String getMemorablePlace( int index )
   {
      return _MemorablePlace[index];
   }
    
   /**
    * Gets the Memorable Place field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Memorable Place or the specified default value.
    */
   public final String getMemorablePlace( int index, String defaultValue )
   {
      return _MemorablePlace[index] == null ? defaultValue : _MemorablePlace[index];
   }
    
   /**
    * Gets the array of Memorable Place fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Memorable Place values.
    */
   public final String[] getMemorablePlaceArray()
   {
      return _MemorablePlace;
   }
    
   /**
    * Gets the Memorable Word field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Memorable Word or null.
    */
   public final String getMemorableWord( int index )
   {
      return _MemorableWord[index];
   }
    
   /**
    * Gets the Memorable Word field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Memorable Word or the specified default value.
    */
   public final String getMemorableWord( int index, String defaultValue )
   {
      return _MemorableWord[index] == null ? defaultValue : _MemorableWord[index];
   }
    
   /**
    * Gets the array of Memorable Word fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Memorable Word values.
    */
   public final String[] getMemorableWordArray()
   {
      return _MemorableWord;
   }
    
   /**
    * Gets the Memorable Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Memorable Date or null.
    */
   public final Date getMemorableDate( int index )
   {
      return _MemorableDate[index];
   }
    
   /**
    * Gets the Memorable Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Memorable Date or the specified default value.
    */
   public final Date getMemorableDate( int index, Date defaultValue )
   {
      return _MemorableDate[index] == null ? defaultValue : _MemorableDate[index];
   }
    
   /**
    * Gets the array of Memorable Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Memorable Date values.
    */
   public final Date[] getMemorableDateArray()
   {
      return _MemorableDate;
   }
    
   /**
    * Gets the PensionLeg Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PensionLeg Code or null.
    */
   public final String getPensionLegCode( int index )
   {
      return _PensionLegCode[index];
   }
    
   /**
    * Gets the PensionLeg Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PensionLeg Code or the specified default value.
    */
   public final String getPensionLegCode( int index, String defaultValue )
   {
      return _PensionLegCode[index] == null ? defaultValue : _PensionLegCode[index];
   }
    
   /**
    * Gets the array of PensionLeg Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PensionLeg Code values.
    */
   public final String[] getPensionLegCodeArray()
   {
      return _PensionLegCode;
   }
    
   /**
    * Gets the Tel/Fax Agreement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tel/Fax Agreement or null.
    */
   public final Boolean getTelFaxAgreement( int index )
   {
      return _TelFaxAgreement[index];
   }
    
   /**
    * Gets the Tel/Fax Agreement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tel/Fax Agreement or the specified default value.
    */
   public final boolean getTelFaxAgreement( int index, boolean defaultValue )
   {
      return _TelFaxAgreement[index] == null ? defaultValue : _TelFaxAgreement[index].booleanValue();
   }
    
   /**
    * Gets the array of Tel/Fax Agreement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tel/Fax Agreement values.
    */
   public final Boolean[] getTelFaxAgreementArray()
   {
      return _TelFaxAgreement;
   }
    
   /**
    * Gets the Clearing ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Clearing ID or null.
    */
   public final String getClearingID( int index )
   {
      return _ClearingID[index];
   }
    
   /**
    * Gets the Clearing ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Clearing ID or the specified default value.
    */
   public final String getClearingID( int index, String defaultValue )
   {
      return _ClearingID[index] == null ? defaultValue : _ClearingID[index];
   }
    
   /**
    * Gets the array of Clearing ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Clearing ID values.
    */
   public final String[] getClearingIDArray()
   {
      return _ClearingID;
   }
    
   /**
    * Gets the SettlLoc Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SettlLoc Exist or null.
    */
   public final Boolean getSettlLocExist( int index )
   {
      return _SettlLocExist[index];
   }
    
   /**
    * Gets the SettlLoc Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SettlLoc Exist or the specified default value.
    */
   public final boolean getSettlLocExist( int index, boolean defaultValue )
   {
      return _SettlLocExist[index] == null ? defaultValue : _SettlLocExist[index].booleanValue();
   }
    
   /**
    * Gets the array of SettlLoc Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SettlLoc Exist values.
    */
   public final Boolean[] getSettlLocExistArray()
   {
      return _SettlLocExist;
   }
    
   /**
    * Gets the DTA Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DTA Type or null.
    */
   public final String getDTAType( int index )
   {
      return _DTAType[index];
   }
    
   /**
    * Gets the DTA Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DTA Type or the specified default value.
    */
   public final String getDTAType( int index, String defaultValue )
   {
      return _DTAType[index] == null ? defaultValue : _DTAType[index];
   }
    
   /**
    * Gets the array of DTA Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DTA Type values.
    */
   public final String[] getDTATypeArray()
   {
      return _DTAType;
   }
    
   /**
    * Gets the NetworkControlInd field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NetworkControlInd or null.
    */
   public final String getNetworkControlInd( int index )
   {
      return _NetworkControlInd[index];
   }
    
   /**
    * Gets the NetworkControlInd field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetworkControlInd or the specified default value.
    */
   public final String getNetworkControlInd( int index, String defaultValue )
   {
      return _NetworkControlInd[index] == null ? defaultValue : _NetworkControlInd[index];
   }
    
   /**
    * Gets the array of NetworkControlInd fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NetworkControlInd values.
    */
   public final String[] getNetworkControlIndArray()
   {
      return _NetworkControlInd;
   }
    
   /**
    * Gets the ClearingFirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClearingFirm or null.
    */
   public final String getClearingFirm( int index )
   {
      return _ClearingFirm[index];
   }
    
   /**
    * Gets the ClearingFirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClearingFirm or the specified default value.
    */
   public final String getClearingFirm( int index, String defaultValue )
   {
      return _ClearingFirm[index] == null ? defaultValue : _ClearingFirm[index];
   }
    
   /**
    * Gets the array of ClearingFirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClearingFirm values.
    */
   public final String[] getClearingFirmArray()
   {
      return _ClearingFirm;
   }
    
   /**
    * Gets the PAC with LSIF Funds Y/N field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PAC with LSIF Funds Y/N or null.
    */
   public final Boolean getLSIFPAC( int index )
   {
      return _LSIFPAC[index];
   }
    
   /**
    * Gets the PAC with LSIF Funds Y/N field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PAC with LSIF Funds Y/N or the specified default value.
    */
   public final boolean getLSIFPAC( int index, boolean defaultValue )
   {
      return _LSIFPAC[index] == null ? defaultValue : _LSIFPAC[index].booleanValue();
   }
    
   /**
    * Gets the array of PAC with LSIF Funds Y/N fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PAC with LSIF Funds Y/N values.
    */
   public final Boolean[] getLSIFPACArray()
   {
      return _LSIFPAC;
   }
    
   /**
    * Gets the Highest Entity Risk field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Highest Entity Risk or null.
    */
   public final String getHighestEntityRisk( int index )
   {
      return _HighestEntityRisk[index];
   }
    
   /**
    * Gets the Highest Entity Risk field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Highest Entity Risk or the specified default value.
    */
   public final String getHighestEntityRisk( int index, String defaultValue )
   {
      return _HighestEntityRisk[index] == null ? defaultValue : _HighestEntityRisk[index];
   }
    
   /**
    * Gets the array of Highest Entity Risk fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Highest Entity Risk values.
    */
   public final String[] getHighestEntityRiskArray()
   {
      return _HighestEntityRisk;
   }
    
   /**
    * Gets the Stop Redemption from Settlement field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Redemption from Settlement or null.
    */
   public final Boolean getStopRedSettle( int index )
   {
      return _StopRedSettle[index];
   }
    
   /**
    * Gets the Stop Redemption from Settlement field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Redemption from Settlement or the specified default value.
    */
   public final boolean getStopRedSettle( int index, boolean defaultValue )
   {
      return _StopRedSettle[index] == null ? defaultValue : _StopRedSettle[index].booleanValue();
   }
    
   /**
    * Gets the array of Stop Redemption from Settlement fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Redemption from Settlement values.
    */
   public final Boolean[] getStopRedSettleArray()
   {
      return _StopRedSettle;
   }
    
   /**
    * Gets the Registration Information field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Registration Information or null.
    */
   public final String getRegistrationInfo( int index )
   {
      return _RegistrationInfo[index];
   }
    
   /**
    * Gets the Registration Information field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Registration Information or the specified default value.
    */
   public final String getRegistrationInfo( int index, String defaultValue )
   {
      return _RegistrationInfo[index] == null ? defaultValue : _RegistrationInfo[index];
   }
    
   /**
    * Gets the array of Registration Information fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Registration Information values.
    */
   public final String[] getRegistrationInfoArray()
   {
      return _RegistrationInfo;
   }
    
   /**
    * Gets the Fee model Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee model Code or null.
    */
   public final String getFeeModelCode( int index )
   {
      return _FeeModelCode[index];
   }
    
   /**
    * Gets the Fee model Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee model Code or the specified default value.
    */
   public final String getFeeModelCode( int index, String defaultValue )
   {
      return _FeeModelCode[index] == null ? defaultValue : _FeeModelCode[index];
   }
    
   /**
    * Gets the array of Fee model Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee model Code values.
    */
   public final String[] getFeeModelCodeArray()
   {
      return _FeeModelCode;
   }
    
   /**
    * Gets the DSC Fee Level based on type from genctrl 'OverridePercentFree' field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DSC Fee Level based on type from genctrl 'OverridePercentFree' or null.
    */
   public final String getDSCFeeLevel( int index )
   {
      return _DSCFeeLevel[index];
   }
    
   /**
    * Gets the DSC Fee Level based on type from genctrl 'OverridePercentFree' field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DSC Fee Level based on type from genctrl 'OverridePercentFree' or the specified default value.
    */
   public final String getDSCFeeLevel( int index, String defaultValue )
   {
      return _DSCFeeLevel[index] == null ? defaultValue : _DSCFeeLevel[index];
   }
    
   /**
    * Gets the array of DSC Fee Level based on type from genctrl 'OverridePercentFree' fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DSC Fee Level based on type from genctrl 'OverridePercentFree' values.
    */
   public final String[] getDSCFeeLevelArray()
   {
      return _DSCFeeLevel;
   }
    
   /**
    * Gets the Latest Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Latest Effective Date or null.
    */
   public final Date getLatestEffectiveDate( int index )
   {
      return _LatestEffectiveDate[index];
   }
    
   /**
    * Gets the Latest Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Latest Effective Date or the specified default value.
    */
   public final Date getLatestEffectiveDate( int index, Date defaultValue )
   {
      return _LatestEffectiveDate[index] == null ? defaultValue : _LatestEffectiveDate[index];
   }
    
   /**
    * Gets the array of Latest Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Latest Effective Date values.
    */
   public final Date[] getLatestEffectiveDateArray()
   {
      return _LatestEffectiveDate;
   }
    
   /**
    * Gets the Account Cut Off Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Cut Off Exist or null.
    */
   public final Boolean getAcctCutOffExist( int index )
   {
      return _AcctCutOffExist[index];
   }
    
   /**
    * Gets the Account Cut Off Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Cut Off Exist or the specified default value.
    */
   public final boolean getAcctCutOffExist( int index, boolean defaultValue )
   {
      return _AcctCutOffExist[index] == null ? defaultValue : _AcctCutOffExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Cut Off Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Cut Off Exist values.
    */
   public final Boolean[] getAcctCutOffExistArray()
   {
      return _AcctCutOffExist;
   }
    
   /**
    * Gets the AgentForFirmAgencyCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AgentForFirmAgencyCode or null.
    */
   public final String getAgentForFirmAgencyCode( int index )
   {
      return _AgentForFirmAgencyCode[index];
   }
    
   /**
    * Gets the AgentForFirmAgencyCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AgentForFirmAgencyCode or the specified default value.
    */
   public final String getAgentForFirmAgencyCode( int index, String defaultValue )
   {
      return _AgentForFirmAgencyCode[index] == null ? defaultValue : _AgentForFirmAgencyCode[index];
   }
    
   /**
    * Gets the array of AgentForFirmAgencyCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AgentForFirmAgencyCode values.
    */
   public final String[] getAgentForFirmAgencyCodeArray()
   {
      return _AgentForFirmAgencyCode;
   }
    
   /**
    * Gets the TPAFirmAgencyCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the TPAFirmAgencyCode or null.
    */
   public final String getTPAFirmAgencyCode( int index )
   {
      return _TPAFirmAgencyCode[index];
   }
    
   /**
    * Gets the TPAFirmAgencyCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TPAFirmAgencyCode or the specified default value.
    */
   public final String getTPAFirmAgencyCode( int index, String defaultValue )
   {
      return _TPAFirmAgencyCode[index] == null ? defaultValue : _TPAFirmAgencyCode[index];
   }
    
   /**
    * Gets the array of TPAFirmAgencyCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of TPAFirmAgencyCode values.
    */
   public final String[] getTPAFirmAgencyCodeArray()
   {
      return _TPAFirmAgencyCode;
   }
    
   /**
    * Gets the NSC Participant Id field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NSC Participant Id or null.
    */
   public final String getNSCPartId( int index )
   {
      return _NSCPartId[index];
   }
    
   /**
    * Gets the NSC Participant Id field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NSC Participant Id or the specified default value.
    */
   public final String getNSCPartId( int index, String defaultValue )
   {
      return _NSCPartId[index] == null ? defaultValue : _NSCPartId[index];
   }
    
   /**
    * Gets the array of NSC Participant Id fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NSC Participant Id values.
    */
   public final String[] getNSCPartIdArray()
   {
      return _NSCPartId;
   }
    
   /**
    * Gets the Network ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Network ID or null.
    */
   public final String getNetworkID( int index )
   {
      return _NetworkID[index];
   }
    
   /**
    * Gets the Network ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Network ID or the specified default value.
    */
   public final String getNetworkID( int index, String defaultValue )
   {
      return _NetworkID[index] == null ? defaultValue : _NetworkID[index];
   }
    
   /**
    * Gets the array of Network ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Network ID values.
    */
   public final String[] getNetworkIDArray()
   {
      return _NetworkID;
   }
    
   /**
    * Gets the Indicates that account has assignee with assigned units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Indicates that account has assignee with assigned units or null.
    */
   public final Boolean getExistAssignee( int index )
   {
      return _ExistAssignee[index];
   }
    
   /**
    * Gets the Indicates that account has assignee with assigned units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Indicates that account has assignee with assigned units or the specified default value.
    */
   public final boolean getExistAssignee( int index, boolean defaultValue )
   {
      return _ExistAssignee[index] == null ? defaultValue : _ExistAssignee[index].booleanValue();
   }
    
   /**
    * Gets the array of Indicates that account has assignee with assigned units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Indicates that account has assignee with assigned units values.
    */
   public final Boolean[] getExistAssigneeArray()
   {
      return _ExistAssignee;
   }
    
   /**
    * Gets the Consolidation Type for Redemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Consolidation Type for Redemption or null.
    */
   public final String getConsolTypePW( int index )
   {
      return _ConsolTypePW[index];
   }
    
   /**
    * Gets the Consolidation Type for Redemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consolidation Type for Redemption or the specified default value.
    */
   public final String getConsolTypePW( int index, String defaultValue )
   {
      return _ConsolTypePW[index] == null ? defaultValue : _ConsolTypePW[index];
   }
    
   /**
    * Gets the array of Consolidation Type for Redemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Consolidation Type for Redemption values.
    */
   public final String[] getConsolTypePWArray()
   {
      return _ConsolTypePW;
   }
    
   /**
    * Gets the Fund Limitation Override Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Limitation Override Exist or null.
    */
   public final Boolean getFundLimitOvrdExist( int index )
   {
      return _FundLimitOvrdExist[index];
   }
    
   /**
    * Gets the Fund Limitation Override Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Limitation Override Exist or the specified default value.
    */
   public final boolean getFundLimitOvrdExist( int index, boolean defaultValue )
   {
      return _FundLimitOvrdExist[index] == null ? defaultValue : _FundLimitOvrdExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Fund Limitation Override Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Limitation Override Exist values.
    */
   public final Boolean[] getFundLimitOvrdExistArray()
   {
      return _FundLimitOvrdExist;
   }
    
   /**
    * Gets the NSCDividend field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NSCDividend or null.
    */
   public final Boolean getNSCDividend( int index )
   {
      return _NSCDividend[index];
   }
    
   /**
    * Gets the NSCDividend field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NSCDividend or the specified default value.
    */
   public final boolean getNSCDividend( int index, boolean defaultValue )
   {
      return _NSCDividend[index] == null ? defaultValue : _NSCDividend[index].booleanValue();
   }
    
   /**
    * Gets the array of NSCDividend fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NSCDividend values.
    */
   public final Boolean[] getNSCDividendArray()
   {
      return _NSCDividend;
   }
    
   /**
    * Gets the Consolidation Type for Distribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Consolidation Type for Distribution or null.
    */
   public final String getConsolTypeID( int index )
   {
      return _ConsolTypeID[index];
   }
    
   /**
    * Gets the Consolidation Type for Distribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consolidation Type for Distribution or the specified default value.
    */
   public final String getConsolTypeID( int index, String defaultValue )
   {
      return _ConsolTypeID[index] == null ? defaultValue : _ConsolTypeID[index];
   }
    
   /**
    * Gets the array of Consolidation Type for Distribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Consolidation Type for Distribution values.
    */
   public final String[] getConsolTypeIDArray()
   {
      return _ConsolTypeID;
   }
    
   /**
    * Gets the Pending Private Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pending Private Flag or null.
    */
   public final Boolean getPendingPrivate( int index )
   {
      return _PendingPrivate[index];
   }
    
   /**
    * Gets the Pending Private Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pending Private Flag or the specified default value.
    */
   public final boolean getPendingPrivate( int index, boolean defaultValue )
   {
      return _PendingPrivate[index] == null ? defaultValue : _PendingPrivate[index].booleanValue();
   }
    
   /**
    * Gets the array of Pending Private Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pending Private Flag values.
    */
   public final Boolean[] getPendingPrivateArray()
   {
      return _PendingPrivate;
   }
    
   /**
    * Gets the Account Closing Reason field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Closing Reason or null.
    */
   public final String getAcctClosingReason( int index )
   {
      return _AcctClosingReason[index];
   }
    
   /**
    * Gets the Account Closing Reason field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Closing Reason or the specified default value.
    */
   public final String getAcctClosingReason( int index, String defaultValue )
   {
      return _AcctClosingReason[index] == null ? defaultValue : _AcctClosingReason[index];
   }
    
   /**
    * Gets the array of Account Closing Reason fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Closing Reason values.
    */
   public final String[] getAcctClosingReasonArray()
   {
      return _AcctClosingReason;
   }
    
   /**
    * Gets the Active AMS Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Active AMS Exist or null.
    */
   public final Boolean getActiveAMSExist( int index )
   {
      return _ActiveAMSExist[index];
   }
    
   /**
    * Gets the Active AMS Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Active AMS Exist or the specified default value.
    */
   public final boolean getActiveAMSExist( int index, boolean defaultValue )
   {
      return _ActiveAMSExist[index] == null ? defaultValue : _ActiveAMSExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Active AMS Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Active AMS Exist values.
    */
   public final Boolean[] getActiveAMSExistArray()
   {
      return _ActiveAMSExist;
   }
    
   /**
    * Gets the Sibling Only field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sibling Only or null.
    */
   public final String getSiblingOnly( int index )
   {
      return _SiblingOnly[index];
   }
    
   /**
    * Gets the Sibling Only field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sibling Only or the specified default value.
    */
   public final String getSiblingOnly( int index, String defaultValue )
   {
      return _SiblingOnly[index] == null ? defaultValue : _SiblingOnly[index];
   }
    
   /**
    * Gets the array of Sibling Only fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sibling Only values.
    */
   public final String[] getSiblingOnlyArray()
   {
      return _SiblingOnly;
   }
    
   /**
    * Gets the Affluent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Affluent or null.
    */
   public final String getAflluent( int index )
   {
      return _Aflluent[index];
   }
    
   /**
    * Gets the Affluent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Affluent or the specified default value.
    */
   public final String getAflluent( int index, String defaultValue )
   {
      return _Aflluent[index] == null ? defaultValue : _Aflluent[index];
   }
    
   /**
    * Gets the array of Affluent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Affluent values.
    */
   public final String[] getAflluentArray()
   {
      return _Aflluent;
   }
    
   /**
    * Gets the Management Fee ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Management Fee ID or null.
    */
   public final String getMgmtFeeID( int index )
   {
      return _MgmtFeeID[index];
   }
    
   /**
    * Gets the Management Fee ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Management Fee ID or the specified default value.
    */
   public final String getMgmtFeeID( int index, String defaultValue )
   {
      return _MgmtFeeID[index] == null ? defaultValue : _MgmtFeeID[index];
   }
    
   /**
    * Gets the array of Management Fee ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Management Fee ID values.
    */
   public final String[] getMgmtFeeIDArray()
   {
      return _MgmtFeeID;
   }
    
   /**
    * Gets the Management Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Management Fee Type or null.
    */
   public final String getMgmtFeeType( int index )
   {
      return _MgmtFeeType[index];
   }
    
   /**
    * Gets the Management Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Management Fee Type or the specified default value.
    */
   public final String getMgmtFeeType( int index, String defaultValue )
   {
      return _MgmtFeeType[index] == null ? defaultValue : _MgmtFeeType[index];
   }
    
   /**
    * Gets the array of Management Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Management Fee Type values.
    */
   public final String[] getMgmtFeeTypeArray()
   {
      return _MgmtFeeType;
   }
    
   /**
    * Gets the Management Fee Rebate ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Management Fee Rebate ID or null.
    */
   public final String getMgmtFeeRbtID( int index )
   {
      return _MgmtFeeRbtID[index];
   }
    
   /**
    * Gets the Management Fee Rebate ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Management Fee Rebate ID or the specified default value.
    */
   public final String getMgmtFeeRbtID( int index, String defaultValue )
   {
      return _MgmtFeeRbtID[index] == null ? defaultValue : _MgmtFeeRbtID[index];
   }
    
   /**
    * Gets the array of Management Fee Rebate ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Management Fee Rebate ID values.
    */
   public final String[] getMgmtFeeRbtIDArray()
   {
      return _MgmtFeeRbtID;
   }
    
   /**
    * Gets the Manamgement Fee Rebate Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Manamgement Fee Rebate Type or null.
    */
   public final String getMgmtFeeRbtType( int index )
   {
      return _MgmtFeeRbtType[index];
   }
    
   /**
    * Gets the Manamgement Fee Rebate Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Manamgement Fee Rebate Type or the specified default value.
    */
   public final String getMgmtFeeRbtType( int index, String defaultValue )
   {
      return _MgmtFeeRbtType[index] == null ? defaultValue : _MgmtFeeRbtType[index];
   }
    
   /**
    * Gets the array of Manamgement Fee Rebate Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Manamgement Fee Rebate Type values.
    */
   public final String[] getMgmtFeeRbtTypeArray()
   {
      return _MgmtFeeRbtType;
   }
    
   /**
    * Gets the Link MFR field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Link MFR or null.
    */
   public final Boolean getLinkMFR( int index )
   {
      return _LinkMFR[index];
   }
    
   /**
    * Gets the Link MFR field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Link MFR or the specified default value.
    */
   public final boolean getLinkMFR( int index, boolean defaultValue )
   {
      return _LinkMFR[index] == null ? defaultValue : _LinkMFR[index].booleanValue();
   }
    
   /**
    * Gets the array of Link MFR fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Link MFR values.
    */
   public final Boolean[] getLinkMFRArray()
   {
      return _LinkMFR;
   }
    
   /**
    * Gets the Account AMS Exist flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account AMS Exist flag or null.
    */
   public final Boolean getAcctAMSExist( int index )
   {
      return _AcctAMSExist[index];
   }
    
   /**
    * Gets the Account AMS Exist flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account AMS Exist flag or the specified default value.
    */
   public final boolean getAcctAMSExist( int index, boolean defaultValue )
   {
      return _AcctAMSExist[index] == null ? defaultValue : _AcctAMSExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Account AMS Exist flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account AMS Exist flag values.
    */
   public final Boolean[] getAcctAMSExistArray()
   {
      return _AcctAMSExist;
   }
    
   /**
    * Gets the Invoice Model ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Invoice Model ID or null.
    */
   public final String getInvoiceModelID( int index )
   {
      return _InvoiceModelID[index];
   }
    
   /**
    * Gets the Invoice Model ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Invoice Model ID or the specified default value.
    */
   public final String getInvoiceModelID( int index, String defaultValue )
   {
      return _InvoiceModelID[index] == null ? defaultValue : _InvoiceModelID[index];
   }
    
   /**
    * Gets the array of Invoice Model ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Invoice Model ID values.
    */
   public final String[] getInvoiceModelIDArray()
   {
      return _InvoiceModelID;
   }
    
   /**
    * Gets the Active Certificate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Active Certificate or null.
    */
   public final Boolean getActiveCert( int index )
   {
      return _ActiveCert[index];
   }
    
   /**
    * Gets the Active Certificate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Active Certificate or the specified default value.
    */
   public final boolean getActiveCert( int index, boolean defaultValue )
   {
      return _ActiveCert[index] == null ? defaultValue : _ActiveCert[index].booleanValue();
   }
    
   /**
    * Gets the array of Active Certificate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Active Certificate values.
    */
   public final Boolean[] getActiveCertArray()
   {
      return _ActiveCert;
   }
    
   /**
    * Gets the Flag indicating in account holder asked to waive the RRIF Min Payment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating in account holder asked to waive the RRIF Min Payment or null.
    */
   public final Boolean getMinWaived( int index )
   {
      return _MinWaived[index];
   }
    
   /**
    * Gets the Flag indicating in account holder asked to waive the RRIF Min Payment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating in account holder asked to waive the RRIF Min Payment or the specified default value.
    */
   public final boolean getMinWaived( int index, boolean defaultValue )
   {
      return _MinWaived[index] == null ? defaultValue : _MinWaived[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating in account holder asked to waive the RRIF Min Payment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating in account holder asked to waive the RRIF Min Payment values.
    */
   public final Boolean[] getMinWaivedArray()
   {
      return _MinWaived;
   }
    
   /**
    * Gets the Hold Dividend Payment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Hold Dividend Payment or null.
    */
   public final Boolean getHoldDivPymt( int index )
   {
      return _HoldDivPymt[index];
   }
    
   /**
    * Gets the Hold Dividend Payment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hold Dividend Payment or the specified default value.
    */
   public final boolean getHoldDivPymt( int index, boolean defaultValue )
   {
      return _HoldDivPymt[index] == null ? defaultValue : _HoldDivPymt[index].booleanValue();
   }
    
   /**
    * Gets the array of Hold Dividend Payment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Hold Dividend Payment values.
    */
   public final Boolean[] getHoldDivPymtArray()
   {
      return _HoldDivPymt;
   }
    
   /**
    * Gets the indicates if DOT or Addendum or both exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the indicates if DOT or Addendum or both exists or null.
    */
   public final String getDOTAdnd( int index )
   {
      return _DOTAdnd[index];
   }
    
   /**
    * Gets the indicates if DOT or Addendum or both exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the indicates if DOT or Addendum or both exists or the specified default value.
    */
   public final String getDOTAdnd( int index, String defaultValue )
   {
      return _DOTAdnd[index] == null ? defaultValue : _DOTAdnd[index];
   }
    
   /**
    * Gets the array of indicates if DOT or Addendum or both exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of indicates if DOT or Addendum or both exists values.
    */
   public final String[] getDOTAdndArray()
   {
      return _DOTAdnd;
   }
    
   /**
    * Gets the Flag indicating if Settlement Rule exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if Settlement Rule exists or null.
    */
   public final Boolean getSettlementRuleExist( int index )
   {
      return _SettlementRuleExist[index];
   }
    
   /**
    * Gets the Flag indicating if Settlement Rule exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if Settlement Rule exists or the specified default value.
    */
   public final boolean getSettlementRuleExist( int index, boolean defaultValue )
   {
      return _SettlementRuleExist[index] == null ? defaultValue : _SettlementRuleExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if Settlement Rule exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if Settlement Rule exists values.
    */
   public final Boolean[] getSettlementRuleExistArray()
   {
      return _SettlementRuleExist;
   }
    
   /**
    * Gets the Tax Type Schedule introduced for Old LIF field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Type Schedule introduced for Old LIF or null.
    */
   public final String getTaxTypeSchedule( int index )
   {
      return _TaxTypeSchedule[index];
   }
    
   /**
    * Gets the Tax Type Schedule introduced for Old LIF field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Type Schedule introduced for Old LIF or the specified default value.
    */
   public final String getTaxTypeSchedule( int index, String defaultValue )
   {
      return _TaxTypeSchedule[index] == null ? defaultValue : _TaxTypeSchedule[index];
   }
    
   /**
    * Gets the array of Tax Type Schedule introduced for Old LIF fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Type Schedule introduced for Old LIF values.
    */
   public final String[] getTaxTypeScheduleArray()
   {
      return _TaxTypeSchedule;
   }
    
   /**
    * Gets the AcctActivityExists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AcctActivityExists or null.
    */
   public final Boolean getAcctActivityExists( int index )
   {
      return _AcctActivityExists[index];
   }
    
   /**
    * Gets the AcctActivityExists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctActivityExists or the specified default value.
    */
   public final boolean getAcctActivityExists( int index, boolean defaultValue )
   {
      return _AcctActivityExists[index] == null ? defaultValue : _AcctActivityExists[index].booleanValue();
   }
    
   /**
    * Gets the array of AcctActivityExists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AcctActivityExists values.
    */
   public final Boolean[] getAcctActivityExistsArray()
   {
      return _AcctActivityExists;
   }
    
   /**
    * Gets the Stop Reason field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Reason or null.
    */
   public final String getStopReason( int index )
   {
      return _StopReason[index];
   }
    
   /**
    * Gets the Stop Reason field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Reason or the specified default value.
    */
   public final String getStopReason( int index, String defaultValue )
   {
      return _StopReason[index] == null ? defaultValue : _StopReason[index];
   }
    
   /**
    * Gets the array of Stop Reason fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Reason values.
    */
   public final String[] getStopReasonArray()
   {
      return _StopReason;
   }
    
   /**
    * Gets the Stop Reason Other field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Reason Other or null.
    */
   public final String getStopReasonOther( int index )
   {
      return _StopReasonOther[index];
   }
    
   /**
    * Gets the Stop Reason Other field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Reason Other or the specified default value.
    */
   public final String getStopReasonOther( int index, String defaultValue )
   {
      return _StopReasonOther[index] == null ? defaultValue : _StopReasonOther[index];
   }
    
   /**
    * Gets the array of Stop Reason Other fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Reason Other values.
    */
   public final String[] getStopReasonOtherArray()
   {
      return _StopReasonOther;
   }
    
   /**
    * Gets the Investor Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Investor Type or null.
    */
   public final String getInvestorType( int index )
   {
      return _InvestorType[index];
   }
    
   /**
    * Gets the Investor Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investor Type or the specified default value.
    */
   public final String getInvestorType( int index, String defaultValue )
   {
      return _InvestorType[index] == null ? defaultValue : _InvestorType[index];
   }
    
   /**
    * Gets the array of Investor Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Investor Type values.
    */
   public final String[] getInvestorTypeArray()
   {
      return _InvestorType;
   }
    
   /**
    * Gets the Invest on behalf of 3rd Party field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Invest on behalf of 3rd Party or null.
    */
   public final String getInvestFor3rdParty( int index )
   {
      return _InvestFor3rdParty[index];
   }
    
   /**
    * Gets the Invest on behalf of 3rd Party field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Invest on behalf of 3rd Party or the specified default value.
    */
   public final String getInvestFor3rdParty( int index, String defaultValue )
   {
      return _InvestFor3rdParty[index] == null ? defaultValue : _InvestFor3rdParty[index];
   }
    
   /**
    * Gets the array of Invest on behalf of 3rd Party fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Invest on behalf of 3rd Party values.
    */
   public final String[] getInvestFor3rdPartyArray()
   {
      return _InvestFor3rdParty;
   }
    
   /**
    * Gets the Compliance Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Compliance Code or null.
    */
   public final String getComplianceCode( int index )
   {
      return _ComplianceCode[index];
   }
    
   /**
    * Gets the Compliance Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Compliance Code or the specified default value.
    */
   public final String getComplianceCode( int index, String defaultValue )
   {
      return _ComplianceCode[index] == null ? defaultValue : _ComplianceCode[index];
   }
    
   /**
    * Gets the array of Compliance Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Compliance Code values.
    */
   public final String[] getComplianceCodeArray()
   {
      return _ComplianceCode;
   }
    
   /**
    * Gets the Account Document List Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Document List Exist or null.
    */
   public final Boolean getAcctDocListExist( int index )
   {
      return _AcctDocListExist[index];
   }
    
   /**
    * Gets the Account Document List Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Document List Exist or the specified default value.
    */
   public final boolean getAcctDocListExist( int index, boolean defaultValue )
   {
      return _AcctDocListExist[index] == null ? defaultValue : _AcctDocListExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Document List Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Document List Exist values.
    */
   public final Boolean[] getAcctDocListExistArray()
   {
      return _AcctDocListExist;
   }
    
   /**
    * Gets the Unit Rounding Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Unit Rounding Method or null.
    */
   public final String getUnitRoundMethod( int index )
   {
      return _UnitRoundMethod[index];
   }
    
   /**
    * Gets the Unit Rounding Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unit Rounding Method or the specified default value.
    */
   public final String getUnitRoundMethod( int index, String defaultValue )
   {
      return _UnitRoundMethod[index] == null ? defaultValue : _UnitRoundMethod[index];
   }
    
   /**
    * Gets the array of Unit Rounding Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Unit Rounding Method values.
    */
   public final String[] getUnitRoundMethodArray()
   {
      return _UnitRoundMethod;
   }
    
   /**
    * Gets the Last Unlocking Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Unlocking Amount or null.
    */
   public final String getUnLockGrossAmt( int index )
   {
      return _UnLockGrossAmt[index];
   }
    
   /**
    * Gets the Last Unlocking Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Unlocking Amount or the specified default value.
    */
   public final String getUnLockGrossAmt( int index, String defaultValue )
   {
      return _UnLockGrossAmt[index] == null ? defaultValue : _UnLockGrossAmt[index];
   }
    
   /**
    * Gets the array of Last Unlocking Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Unlocking Amount values.
    */
   public final String[] getUnLockGrossAmtArray()
   {
      return _UnLockGrossAmt;
   }
    
   /**
    * Gets the Trade Date of the Last Unlocking Amt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trade Date of the Last Unlocking Amt or null.
    */
   public final Date getUnLockDeff( int index )
   {
      return _UnLockDeff[index];
   }
    
   /**
    * Gets the Trade Date of the Last Unlocking Amt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trade Date of the Last Unlocking Amt or the specified default value.
    */
   public final Date getUnLockDeff( int index, Date defaultValue )
   {
      return _UnLockDeff[index] == null ? defaultValue : _UnLockDeff[index];
   }
    
   /**
    * Gets the array of Trade Date of the Last Unlocking Amt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trade Date of the Last Unlocking Amt values.
    */
   public final Date[] getUnLockDeffArray()
   {
      return _UnLockDeff;
   }
    
   /**
    * Gets the Stage of Returned Mail field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stage of Returned Mail or null.
    */
   public final String getRtnMailStage( int index )
   {
      return _RtnMailStage[index];
   }
    
   /**
    * Gets the Stage of Returned Mail field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stage of Returned Mail or the specified default value.
    */
   public final String getRtnMailStage( int index, String defaultValue )
   {
      return _RtnMailStage[index] == null ? defaultValue : _RtnMailStage[index];
   }
    
   /**
    * Gets the array of Stage of Returned Mail fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stage of Returned Mail values.
    */
   public final String[] getRtnMailStageArray()
   {
      return _RtnMailStage;
   }
    
   /**
    * Gets the Stage of Stale Cheque field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stage of Stale Cheque or null.
    */
   public final String getStaleChqStage( int index )
   {
      return _StaleChqStage[index];
   }
    
   /**
    * Gets the Stage of Stale Cheque field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stage of Stale Cheque or the specified default value.
    */
   public final String getStaleChqStage( int index, String defaultValue )
   {
      return _StaleChqStage[index] == null ? defaultValue : _StaleChqStage[index];
   }
    
   /**
    * Gets the array of Stage of Stale Cheque fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stage of Stale Cheque values.
    */
   public final String[] getStaleChqStageArray()
   {
      return _StaleChqStage;
   }
    
   /**
    * Gets the Flag that indicates if non financial updates are allowed in the account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag that indicates if non financial updates are allowed in the account or null.
    */
   public final Boolean getStopNFU( int index )
   {
      return _StopNFU[index];
   }
    
   /**
    * Gets the Flag that indicates if non financial updates are allowed in the account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag that indicates if non financial updates are allowed in the account or the specified default value.
    */
   public final boolean getStopNFU( int index, boolean defaultValue )
   {
      return _StopNFU[index] == null ? defaultValue : _StopNFU[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag that indicates if non financial updates are allowed in the account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag that indicates if non financial updates are allowed in the account values.
    */
   public final Boolean[] getStopNFUArray()
   {
      return _StopNFU;
   }
    
   /**
    * Gets the Exemption Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exemption Date or null.
    */
   public final Date getExemptDate( int index )
   {
      return _ExemptDate[index];
   }
    
   /**
    * Gets the Exemption Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exemption Date or the specified default value.
    */
   public final Date getExemptDate( int index, Date defaultValue )
   {
      return _ExemptDate[index] == null ? defaultValue : _ExemptDate[index];
   }
    
   /**
    * Gets the array of Exemption Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exemption Date values.
    */
   public final Date[] getExemptDateArray()
   {
      return _ExemptDate;
   }
    
   /**
    * Gets the Next Process Date for MFR field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Next Process Date for MFR or null.
    */
   public final Date getNextMFRProcessDate( int index )
   {
      return _NextMFRProcessDate[index];
   }
    
   /**
    * Gets the Next Process Date for MFR field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Next Process Date for MFR or the specified default value.
    */
   public final Date getNextMFRProcessDate( int index, Date defaultValue )
   {
      return _NextMFRProcessDate[index] == null ? defaultValue : _NextMFRProcessDate[index];
   }
    
   /**
    * Gets the array of Next Process Date for MFR fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Next Process Date for MFR values.
    */
   public final Date[] getNextMFRProcessDateArray()
   {
      return _NextMFRProcessDate;
   }
    
   /**
    * Gets the Flag indicating if account is setup for MFR model field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if account is setup for MFR model or null.
    */
   public final Boolean getIsMFRAccount( int index )
   {
      return _IsMFRAccount[index];
   }
    
   /**
    * Gets the Flag indicating if account is setup for MFR model field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if account is setup for MFR model or the specified default value.
    */
   public final boolean getIsMFRAccount( int index, boolean defaultValue )
   {
      return _IsMFRAccount[index] == null ? defaultValue : _IsMFRAccount[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if account is setup for MFR model fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if account is setup for MFR model values.
    */
   public final Boolean[] getIsMFRAccountArray()
   {
      return _IsMFRAccount;
   }
    
   /**
    * Gets the Flag indicating if account is closed country resident field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if account is closed country resident or null.
    */
   public final Boolean getIsClosedCountryResident( int index )
   {
      return _IsClosedCountryResident[index];
   }
    
   /**
    * Gets the Flag indicating if account is closed country resident field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if account is closed country resident or the specified default value.
    */
   public final boolean getIsClosedCountryResident( int index, boolean defaultValue )
   {
      return _IsClosedCountryResident[index] == null ? defaultValue : _IsClosedCountryResident[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if account is closed country resident fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if account is closed country resident values.
    */
   public final Boolean[] getIsClosedCountryResidentArray()
   {
      return _IsClosedCountryResident;
   }
    
   /**
    * Gets the Flag indicates if account has Acct-Auth record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates if account has Acct-Auth record or null.
    */
   public final Boolean getInvestorAuthorizationExist( int index )
   {
      return _InvestorAuthorizationExist[index];
   }
    
   /**
    * Gets the Flag indicates if account has Acct-Auth record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates if account has Acct-Auth record or the specified default value.
    */
   public final boolean getInvestorAuthorizationExist( int index, boolean defaultValue )
   {
      return _InvestorAuthorizationExist[index] == null ? defaultValue : _InvestorAuthorizationExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates if account has Acct-Auth record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates if account has Acct-Auth record values.
    */
   public final Boolean[] getInvestorAuthorizationExistArray()
   {
      return _InvestorAuthorizationExist;
   }
    
   /**
    * Gets the Flag indicates if there is outstanding unverified Entity Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates if there is outstanding unverified Entity Name or null.
    */
   public final Boolean getEntityUnverifiedExist( int index )
   {
      return _EntityUnverifiedExist[index];
   }
    
   /**
    * Gets the Flag indicates if there is outstanding unverified Entity Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates if there is outstanding unverified Entity Name or the specified default value.
    */
   public final boolean getEntityUnverifiedExist( int index, boolean defaultValue )
   {
      return _EntityUnverifiedExist[index] == null ? defaultValue : _EntityUnverifiedExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates if there is outstanding unverified Entity Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates if there is outstanding unverified Entity Name values.
    */
   public final Boolean[] getEntityUnverifiedExistArray()
   {
      return _EntityUnverifiedExist;
   }
    
   /**
    * Gets the Flag if account registered CCRA in Jan 1,1998. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag if account registered CCRA in Jan 1,1998. or null.
    */
   public final Boolean getGrandFathered( int index )
   {
      return _GrandFathered[index];
   }
    
   /**
    * Gets the Flag if account registered CCRA in Jan 1,1998. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag if account registered CCRA in Jan 1,1998. or the specified default value.
    */
   public final boolean getGrandFathered( int index, boolean defaultValue )
   {
      return _GrandFathered[index] == null ? defaultValue : _GrandFathered[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag if account registered CCRA in Jan 1,1998. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag if account registered CCRA in Jan 1,1998. values.
    */
   public final Boolean[] getGrandFatheredArray()
   {
      return _GrandFathered;
   }
    
   /**
    * Gets the Flag if RESP beneficiary deleted for account. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag if RESP beneficiary deleted for account. or null.
    */
   public final Boolean getRESPBenefDeleted( int index )
   {
      return _RESPBenefDeleted[index];
   }
    
   /**
    * Gets the Flag if RESP beneficiary deleted for account. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag if RESP beneficiary deleted for account. or the specified default value.
    */
   public final boolean getRESPBenefDeleted( int index, boolean defaultValue )
   {
      return _RESPBenefDeleted[index] == null ? defaultValue : _RESPBenefDeleted[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag if RESP beneficiary deleted for account. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag if RESP beneficiary deleted for account. values.
    */
   public final Boolean[] getRESPBenefDeletedArray()
   {
      return _RESPBenefDeleted;
   }
    
   /**
    * Gets the Flag indicating if RESP Account Info exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if RESP Account Info exists or null.
    */
   public final Boolean getRESPAcctInfoExists( int index )
   {
      return _RESPAcctInfoExists[index];
   }
    
   /**
    * Gets the Flag indicating if RESP Account Info exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if RESP Account Info exists or the specified default value.
    */
   public final boolean getRESPAcctInfoExists( int index, boolean defaultValue )
   {
      return _RESPAcctInfoExists[index] == null ? defaultValue : _RESPAcctInfoExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if RESP Account Info exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if RESP Account Info exists values.
    */
   public final Boolean[] getRESPAcctInfoExistsArray()
   {
      return _RESPAcctInfoExists;
   }
    
   /**
    * Gets the Flag indicating if there were contributions made before 1998. field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if there were contributions made before 1998. or null.
    */
   public final Boolean getPre98Contrib( int index )
   {
      return _Pre98Contrib[index];
   }
    
   /**
    * Gets the Flag indicating if there were contributions made before 1998. field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if there were contributions made before 1998. or the specified default value.
    */
   public final boolean getPre98Contrib( int index, boolean defaultValue )
   {
      return _Pre98Contrib[index] == null ? defaultValue : _Pre98Contrib[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if there were contributions made before 1998. fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if there were contributions made before 1998. values.
    */
   public final Boolean[] getPre98ContribArray()
   {
      return _Pre98Contrib;
   }
    
   /**
    * Gets the Flag indicating if AIP Withdrawal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicating if AIP Withdrawal or null.
    */
   public final Boolean getAIPWithdrawalExists( int index )
   {
      return _AIPWithdrawalExists[index];
   }
    
   /**
    * Gets the Flag indicating if AIP Withdrawal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicating if AIP Withdrawal or the specified default value.
    */
   public final boolean getAIPWithdrawalExists( int index, boolean defaultValue )
   {
      return _AIPWithdrawalExists[index] == null ? defaultValue : _AIPWithdrawalExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicating if AIP Withdrawal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicating if AIP Withdrawal values.
    */
   public final Boolean[] getAIPWithdrawalExistsArray()
   {
      return _AIPWithdrawalExists;
   }
    
   /**
    * Gets the Date to determine year of plan field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date to determine year of plan or null.
    */
   public final Date getOrigPlanDeff( int index )
   {
      return _OrigPlanDeff[index];
   }
    
   /**
    * Gets the Date to determine year of plan field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date to determine year of plan or the specified default value.
    */
   public final Date getOrigPlanDeff( int index, Date defaultValue )
   {
      return _OrigPlanDeff[index] == null ? defaultValue : _OrigPlanDeff[index];
   }
    
   /**
    * Gets the array of Date to determine year of plan fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date to determine year of plan values.
    */
   public final Date[] getOrigPlanDeffArray()
   {
      return _OrigPlanDeff;
   }
    
   /**
    * Gets the Flag indicates whether the account can have a GWO contract or not field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates whether the account can have a GWO contract or not or null.
    */
   public final Boolean getIsGWOContract( int index )
   {
      return _IsGWOContract[index];
   }
    
   /**
    * Gets the Flag indicates whether the account can have a GWO contract or not field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates whether the account can have a GWO contract or not or the specified default value.
    */
   public final boolean getIsGWOContract( int index, boolean defaultValue )
   {
      return _IsGWOContract[index] == null ? defaultValue : _IsGWOContract[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates whether the account can have a GWO contract or not fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates whether the account can have a GWO contract or not values.
    */
   public final Boolean[] getIsGWOContractArray()
   {
      return _IsGWOContract;
   }
    
   /**
    * Gets the Flag indicates whether the account guarantee guard has been set up field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates whether the account guarantee guard has been set up or null.
    */
   public final Boolean getAcctGuarGuardExists( int index )
   {
      return _AcctGuarGuardExists[index];
   }
    
   /**
    * Gets the Flag indicates whether the account guarantee guard has been set up field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates whether the account guarantee guard has been set up or the specified default value.
    */
   public final boolean getAcctGuarGuardExists( int index, boolean defaultValue )
   {
      return _AcctGuarGuardExists[index] == null ? defaultValue : _AcctGuarGuardExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates whether the account guarantee guard has been set up fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates whether the account guarantee guard has been set up values.
    */
   public final Boolean[] getAcctGuarGuardExistsArray()
   {
      return _AcctGuarGuardExists;
   }
    
   /**
    * Gets the Flag indicates if any of RESP beneficiaries ever lived in Quebec field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates if any of RESP beneficiaries ever lived in Quebec or null.
    */
   public final Boolean getRESPQCResidentFound( int index )
   {
      return _RESPQCResidentFound[index];
   }
    
   /**
    * Gets the Flag indicates if any of RESP beneficiaries ever lived in Quebec field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates if any of RESP beneficiaries ever lived in Quebec or the specified default value.
    */
   public final boolean getRESPQCResidentFound( int index, boolean defaultValue )
   {
      return _RESPQCResidentFound[index] == null ? defaultValue : _RESPQCResidentFound[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates if any of RESP beneficiaries ever lived in Quebec fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates if any of RESP beneficiaries ever lived in Quebec values.
    */
   public final Boolean[] getRESPQCResidentFoundArray()
   {
      return _RESPQCResidentFound;
   }
    
   /**
    * Gets the Flag indicates if Government Amendment record exist for the account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates if Government Amendment record exist for the account or null.
    */
   public final Boolean getGovAmendmentExist( int index )
   {
      return _GovAmendmentExist[index];
   }
    
   /**
    * Gets the Flag indicates if Government Amendment record exist for the account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates if Government Amendment record exist for the account or the specified default value.
    */
   public final boolean getGovAmendmentExist( int index, boolean defaultValue )
   {
      return _GovAmendmentExist[index] == null ? defaultValue : _GovAmendmentExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates if Government Amendment record exist for the account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates if Government Amendment record exist for the account values.
    */
   public final Boolean[] getGovAmendmentExistArray()
   {
      return _GovAmendmentExist;
   }
    
   /**
    * Gets the Flag indicates if account is run to curator file field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates if account is run to curator file or null.
    */
   public final Boolean getIsAcctRunToCurFile( int index )
   {
      return _IsAcctRunToCurFile[index];
   }
    
   /**
    * Gets the Flag indicates if account is run to curator file field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates if account is run to curator file or the specified default value.
    */
   public final boolean getIsAcctRunToCurFile( int index, boolean defaultValue )
   {
      return _IsAcctRunToCurFile[index] == null ? defaultValue : _IsAcctRunToCurFile[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates if account is run to curator file fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates if account is run to curator file values.
    */
   public final Boolean[] getIsAcctRunToCurFileArray()
   {
      return _IsAcctRunToCurFile;
   }
    
   /**
    * Gets the Flag indicates if account has been unfrozen field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates if account has been unfrozen or null.
    */
   public final Boolean getHasAcctBeenUnFrozen( int index )
   {
      return _HasAcctBeenUnFrozen[index];
   }
    
   /**
    * Gets the Flag indicates if account has been unfrozen field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates if account has been unfrozen or the specified default value.
    */
   public final boolean getHasAcctBeenUnFrozen( int index, boolean defaultValue )
   {
      return _HasAcctBeenUnFrozen[index] == null ? defaultValue : _HasAcctBeenUnFrozen[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates if account has been unfrozen fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates if account has been unfrozen values.
    */
   public final Boolean[] getHasAcctBeenUnFrozenArray()
   {
      return _HasAcctBeenUnFrozen;
   }
    
   /**
    * Gets the Flag indicates if stale dated cheque exists in an account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates if stale dated cheque exists in an account or null.
    */
   public final Boolean getStaleChqExists( int index )
   {
      return _StaleChqExists[index];
   }
    
   /**
    * Gets the Flag indicates if stale dated cheque exists in an account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates if stale dated cheque exists in an account or the specified default value.
    */
   public final boolean getStaleChqExists( int index, boolean defaultValue )
   {
      return _StaleChqExists[index] == null ? defaultValue : _StaleChqExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates if stale dated cheque exists in an account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates if stale dated cheque exists in an account values.
    */
   public final Boolean[] getStaleChqExistsArray()
   {
      return _StaleChqExists;
   }
    
   /**
    * Gets the Flag indicates remitted cheque exists in an account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates remitted cheque exists in an account or null.
    */
   public final Boolean getRemittedChqExists( int index )
   {
      return _RemittedChqExists[index];
   }
    
   /**
    * Gets the Flag indicates remitted cheque exists in an account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates remitted cheque exists in an account or the specified default value.
    */
   public final boolean getRemittedChqExists( int index, boolean defaultValue )
   {
      return _RemittedChqExists[index] == null ? defaultValue : _RemittedChqExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag indicates remitted cheque exists in an account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates remitted cheque exists in an account values.
    */
   public final Boolean[] getRemittedChqExistsArray()
   {
      return _RemittedChqExists;
   }
    
   /**
    * Gets the Flag indicates a list of remitted cheque stages field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag indicates a list of remitted cheque stages or null.
    */
   public final String getRemittedChqStage( int index )
   {
      return _RemittedChqStage[index];
   }
    
   /**
    * Gets the Flag indicates a list of remitted cheque stages field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag indicates a list of remitted cheque stages or the specified default value.
    */
   public final String getRemittedChqStage( int index, String defaultValue )
   {
      return _RemittedChqStage[index] == null ? defaultValue : _RemittedChqStage[index];
   }
    
   /**
    * Gets the array of Flag indicates a list of remitted cheque stages fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag indicates a list of remitted cheque stages values.
    */
   public final String[] getRemittedChqStageArray()
   {
      return _RemittedChqStage;
   }
    
   /**
    * Gets the Consolidation Type for Purchase field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Consolidation Type for Purchase or null.
    */
   public final String getConsolTypeED( int index )
   {
      return _ConsolTypeED[index];
   }
    
   /**
    * Gets the Consolidation Type for Purchase field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Consolidation Type for Purchase or the specified default value.
    */
   public final String getConsolTypeED( int index, String defaultValue )
   {
      return _ConsolTypeED[index] == null ? defaultValue : _ConsolTypeED[index];
   }
    
   /**
    * Gets the array of Consolidation Type for Purchase fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Consolidation Type for Purchase values.
    */
   public final String[] getConsolTypeEDArray()
   {
      return _ConsolTypeED;
   }
    
   /**
    * Gets the RESP Account Inception Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RESP Account Inception Date or null.
    */
   public final Date getInceptionDate( int index )
   {
      return _InceptionDate[index];
   }
    
   /**
    * Gets the RESP Account Inception Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Account Inception Date or the specified default value.
    */
   public final Date getInceptionDate( int index, Date defaultValue )
   {
      return _InceptionDate[index] == null ? defaultValue : _InceptionDate[index];
   }
    
   /**
    * Gets the array of RESP Account Inception Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RESP Account Inception Date values.
    */
   public final Date[] getInceptionDateArray()
   {
      return _InceptionDate;
   }
    
   /**
    * Gets the ProdPortfolio UUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProdPortfolio UUID or null.
    */
   public final String getProdPortfolioUUID( int index )
   {
      return _ProdPortfolioUUID[index];
   }
    
   /**
    * Gets the ProdPortfolio UUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProdPortfolio UUID or the specified default value.
    */
   public final String getProdPortfolioUUID( int index, String defaultValue )
   {
      return _ProdPortfolioUUID[index] == null ? defaultValue : _ProdPortfolioUUID[index];
   }
    
   /**
    * Gets the array of ProdPortfolio UUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProdPortfolio UUID values.
    */
   public final String[] getProdPortfolioUUIDArray()
   {
      return _ProdPortfolioUUID;
   }
    
   /**
    * Gets the ProdPortfolioPlan UUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ProdPortfolioPlan UUID or null.
    */
   public final String getProdPortfolioPlanUUID( int index )
   {
      return _ProdPortfolioPlanUUID[index];
   }
    
   /**
    * Gets the ProdPortfolioPlan UUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ProdPortfolioPlan UUID or the specified default value.
    */
   public final String getProdPortfolioPlanUUID( int index, String defaultValue )
   {
      return _ProdPortfolioPlanUUID[index] == null ? defaultValue : _ProdPortfolioPlanUUID[index];
   }
    
   /**
    * Gets the array of ProdPortfolioPlan UUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ProdPortfolioPlan UUID values.
    */
   public final String[] getProdPortfolioPlanUUIDArray()
   {
      return _ProdPortfolioPlanUUID;
   }
    
   /**
    * Gets the Date that property is remitted to the government field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Date that property is remitted to the government or null.
    */
   public final Date getUnclmRemitDate( int index )
   {
      return _UnclmRemitDate[index];
   }
    
   /**
    * Gets the Date that property is remitted to the government field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date that property is remitted to the government or the specified default value.
    */
   public final Date getUnclmRemitDate( int index, Date defaultValue )
   {
      return _UnclmRemitDate[index] == null ? defaultValue : _UnclmRemitDate[index];
   }
    
   /**
    * Gets the array of Date that property is remitted to the government fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Date that property is remitted to the government values.
    */
   public final Date[] getUnclmRemitDateArray()
   {
      return _UnclmRemitDate;
   }
    
   /**
    * Gets the NSCC Social Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the NSCC Social Code or null.
    */
   public final String getNSCSocialCode( int index )
   {
      return _NSCSocialCode[index];
   }
    
   /**
    * Gets the NSCC Social Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NSCC Social Code or the specified default value.
    */
   public final String getNSCSocialCode( int index, String defaultValue )
   {
      return _NSCSocialCode[index] == null ? defaultValue : _NSCSocialCode[index];
   }
    
   /**
    * Gets the array of NSCC Social Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of NSCC Social Code values.
    */
   public final String[] getNSCSocialCodeArray()
   {
      return _NSCSocialCode;
   }
    
   /**
    * Gets the HasGIAHolding field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the HasGIAHolding or null.
    */
   public final Boolean getHasGIAHolding( int index )
   {
      return _HasGIAHolding[index];
   }
    
   /**
    * Gets the HasGIAHolding field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the HasGIAHolding or the specified default value.
    */
   public final boolean getHasGIAHolding( int index, boolean defaultValue )
   {
      return _HasGIAHolding[index] == null ? defaultValue : _HasGIAHolding[index].booleanValue();
   }
    
   /**
    * Gets the array of HasGIAHolding fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of HasGIAHolding values.
    */
   public final Boolean[] getHasGIAHoldingArray()
   {
      return _HasGIAHolding;
   }
    
   /**
    * Gets the Can have CashSweep instruction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Can have CashSweep instruction or null.
    */
   public final Boolean getCanHaveCashSweep( int index )
   {
      return _CanHaveCashSweep[index];
   }
    
   /**
    * Gets the Can have CashSweep instruction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Can have CashSweep instruction or the specified default value.
    */
   public final boolean getCanHaveCashSweep( int index, boolean defaultValue )
   {
      return _CanHaveCashSweep[index] == null ? defaultValue : _CanHaveCashSweep[index].booleanValue();
   }
    
   /**
    * Gets the array of Can have CashSweep instruction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Can have CashSweep instruction values.
    */
   public final Boolean[] getCanHaveCashSweepArray()
   {
      return _CanHaveCashSweep;
   }
    
   /**
    * Gets the Can have Maturity Instruction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Can have Maturity Instruction or null.
    */
   public final Boolean getCanHaveMatInstr( int index )
   {
      return _CanHaveMatInstr[index];
   }
    
   /**
    * Gets the Can have Maturity Instruction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Can have Maturity Instruction or the specified default value.
    */
   public final boolean getCanHaveMatInstr( int index, boolean defaultValue )
   {
      return _CanHaveMatInstr[index] == null ? defaultValue : _CanHaveMatInstr[index].booleanValue();
   }
    
   /**
    * Gets the array of Can have Maturity Instruction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Can have Maturity Instruction values.
    */
   public final Boolean[] getCanHaveMatInstrArray()
   {
      return _CanHaveMatInstr;
   }
    
   /**
    * Gets the CashSweep exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CashSweep exists or null.
    */
   public final Boolean getCashSweepExists( int index )
   {
      return _CashSweepExists[index];
   }
    
   /**
    * Gets the CashSweep exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CashSweep exists or the specified default value.
    */
   public final boolean getCashSweepExists( int index, boolean defaultValue )
   {
      return _CashSweepExists[index] == null ? defaultValue : _CashSweepExists[index].booleanValue();
   }
    
   /**
    * Gets the array of CashSweep exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CashSweep exists values.
    */
   public final Boolean[] getCashSweepExistsArray()
   {
      return _CashSweepExists;
   }
    
   /**
    * Gets the Maturity Instruction exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Maturity Instruction exists or null.
    */
   public final Boolean getMatIntExists( int index )
   {
      return _MatIntExists[index];
   }
    
   /**
    * Gets the Maturity Instruction exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Maturity Instruction exists or the specified default value.
    */
   public final boolean getMatIntExists( int index, boolean defaultValue )
   {
      return _MatIntExists[index] == null ? defaultValue : _MatIntExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Maturity Instruction exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Maturity Instruction exists values.
    */
   public final Boolean[] getMatIntExistsArray()
   {
      return _MatIntExists;
   }
    
   /**
    * Gets the Organisation Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Organisation Type or null.
    */
   public final String getOrgType( int index )
   {
      return _OrgType[index];
   }
    
   /**
    * Gets the Organisation Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Organisation Type or the specified default value.
    */
   public final String getOrgType( int index, String defaultValue )
   {
      return _OrgType[index] == null ? defaultValue : _OrgType[index];
   }
    
   /**
    * Gets the array of Organisation Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Organisation Type values.
    */
   public final String[] getOrgTypeArray()
   {
      return _OrgType;
   }
    
   /**
    * Gets the Sub Organisation Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Sub Organisation Type or null.
    */
   public final String getSubOrgType( int index )
   {
      return _SubOrgType[index];
   }
    
   /**
    * Gets the Sub Organisation Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sub Organisation Type or the specified default value.
    */
   public final String getSubOrgType( int index, String defaultValue )
   {
      return _SubOrgType[index] == null ? defaultValue : _SubOrgType[index];
   }
    
   /**
    * Gets the array of Sub Organisation Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Sub Organisation Type values.
    */
   public final String[] getSubOrgTypeArray()
   {
      return _SubOrgType;
   }
    
   /**
    * Gets the Territory Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Territory Code or null.
    */
   public final String getTerritoryCode( int index )
   {
      return _TerritoryCode[index];
   }
    
   /**
    * Gets the Territory Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Territory Code or the specified default value.
    */
   public final String getTerritoryCode( int index, String defaultValue )
   {
      return _TerritoryCode[index] == null ? defaultValue : _TerritoryCode[index];
   }
    
   /**
    * Gets the array of Territory Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Territory Code values.
    */
   public final String[] getTerritoryCodeArray()
   {
      return _TerritoryCode;
   }
    
   /**
    * Gets the Commitment Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Commitment Status or null.
    */
   public final String getCommitmentStatus( int index )
   {
      return _CommitmentStatus[index];
   }
    
   /**
    * Gets the Commitment Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Commitment Status or the specified default value.
    */
   public final String getCommitmentStatus( int index, String defaultValue )
   {
      return _CommitmentStatus[index] == null ? defaultValue : _CommitmentStatus[index];
   }
    
   /**
    * Gets the array of Commitment Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Commitment Status values.
    */
   public final String[] getCommitmentStatusArray()
   {
      return _CommitmentStatus;
   }
    
   /**
    * Gets the Life Annuit Exists field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Life Annuit Exists or null.
    */
   public final Boolean getLifeAnnuityExists( int index )
   {
      return _LifeAnnuityExists[index];
   }
    
   /**
    * Gets the Life Annuit Exists field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Life Annuit Exists or the specified default value.
    */
   public final boolean getLifeAnnuityExists( int index, boolean defaultValue )
   {
      return _LifeAnnuityExists[index] == null ? defaultValue : _LifeAnnuityExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Life Annuit Exists fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Life Annuit Exists values.
    */
   public final Boolean[] getLifeAnnuityExistsArray()
   {
      return _LifeAnnuityExists;
   }
    
   /**
    * Gets the Stop Adjustment Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Adjustment Date or null.
    */
   public final Date getStopAdjDate( int index )
   {
      return _StopAdjDate[index];
   }
    
   /**
    * Gets the Stop Adjustment Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Adjustment Date or the specified default value.
    */
   public final Date getStopAdjDate( int index, Date defaultValue )
   {
      return _StopAdjDate[index] == null ? defaultValue : _StopAdjDate[index];
   }
    
   /**
    * Gets the array of Stop Adjustment Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Adjustment Date values.
    */
   public final Date[] getStopAdjDateArray()
   {
      return _StopAdjDate;
   }
    
   /**
    * Gets the Non Financial Confirm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Non Financial Confirm or null.
    */
   public final Boolean getNonFinConfirm( int index )
   {
      return _NonFinConfirm[index];
   }
    
   /**
    * Gets the Non Financial Confirm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Non Financial Confirm or the specified default value.
    */
   public final boolean getNonFinConfirm( int index, boolean defaultValue )
   {
      return _NonFinConfirm[index] == null ? defaultValue : _NonFinConfirm[index].booleanValue();
   }
    
   /**
    * Gets the array of Non Financial Confirm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Non Financial Confirm values.
    */
   public final Boolean[] getNonFinConfirmArray()
   {
      return _NonFinConfirm;
   }
    
   /**
    * Gets the Account Settlement Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Settlement Currency or null.
    */
   public final String getSettleCurrency( int index )
   {
      return _SettleCurrency[index];
   }
    
   /**
    * Gets the Account Settlement Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Settlement Currency or the specified default value.
    */
   public final String getSettleCurrency( int index, String defaultValue )
   {
      return _SettleCurrency[index] == null ? defaultValue : _SettleCurrency[index];
   }
    
   /**
    * Gets the array of Account Settlement Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Settlement Currency values.
    */
   public final String[] getSettleCurrencyArray()
   {
      return _SettleCurrency;
   }
    
   /**
    * Gets the Registration Agent Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Registration Agent Code or null.
    */
   public final String getRegAgentCode( int index )
   {
      return _RegAgentCode[index];
   }
    
   /**
    * Gets the Registration Agent Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Registration Agent Code or the specified default value.
    */
   public final String getRegAgentCode( int index, String defaultValue )
   {
      return _RegAgentCode[index] == null ? defaultValue : _RegAgentCode[index];
   }
    
   /**
    * Gets the array of Registration Agent Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Registration Agent Code values.
    */
   public final String[] getRegAgentCodeArray()
   {
      return _RegAgentCode;
   }
    
   /**
    * Gets the GWA/LWA Pay Optons field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the GWA/LWA Pay Optons or null.
    */
   public final String getGWLWAAvailOptions( int index )
   {
      return _GWLWAAvailOptions[index];
   }
    
   /**
    * Gets the GWA/LWA Pay Optons field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GWA/LWA Pay Optons or the specified default value.
    */
   public final String getGWLWAAvailOptions( int index, String defaultValue )
   {
      return _GWLWAAvailOptions[index] == null ? defaultValue : _GWLWAAvailOptions[index];
   }
    
   /**
    * Gets the array of GWA/LWA Pay Optons fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of GWA/LWA Pay Optons values.
    */
   public final String[] getGWLWAAvailOptionsArray()
   {
      return _GWLWAAvailOptions;
   }
    
   /**
    * Gets the T5 Anniversary Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the T5 Anniversary Date or null.
    */
   public final Date getT5AnniversaryDate( int index )
   {
      return _T5AnniversaryDate[index];
   }
    
   /**
    * Gets the T5 Anniversary Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the T5 Anniversary Date or the specified default value.
    */
   public final Date getT5AnniversaryDate( int index, Date defaultValue )
   {
      return _T5AnniversaryDate[index] == null ? defaultValue : _T5AnniversaryDate[index];
   }
    
   /**
    * Gets the array of T5 Anniversary Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of T5 Anniversary Date values.
    */
   public final Date[] getT5AnniversaryDateArray()
   {
      return _T5AnniversaryDate;
   }
    
   /**
    * Gets the SWP with Amount Type G or L field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SWP with Amount Type G or L or null.
    */
   public final String getSWPGLOpt( int index )
   {
      return _SWPGLOpt[index];
   }
    
   /**
    * Gets the SWP with Amount Type G or L field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SWP with Amount Type G or L or the specified default value.
    */
   public final String getSWPGLOpt( int index, String defaultValue )
   {
      return _SWPGLOpt[index] == null ? defaultValue : _SWPGLOpt[index];
   }
    
   /**
    * Gets the array of SWP with Amount Type G or L fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SWP with Amount Type G or L values.
    */
   public final String[] getSWPGLOptArray()
   {
      return _SWPGLOpt;
   }
    
   /**
    * Gets the RRIF with Amount Type G or L field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF with Amount Type G or L or null.
    */
   public final String getRRIFGLOpt( int index )
   {
      return _RRIFGLOpt[index];
   }
    
   /**
    * Gets the RRIF with Amount Type G or L field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF with Amount Type G or L or the specified default value.
    */
   public final String getRRIFGLOpt( int index, String defaultValue )
   {
      return _RRIFGLOpt[index] == null ? defaultValue : _RRIFGLOpt[index];
   }
    
   /**
    * Gets the array of RRIF with Amount Type G or L fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF with Amount Type G or L values.
    */
   public final String[] getRRIFGLOptArray()
   {
      return _RRIFGLOpt;
   }
    
   /**
    * Gets the Taxable Trust Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Taxable Trust Date or null.
    */
   public final Date getTaxableTrustDate( int index )
   {
      return _TaxableTrustDate[index];
   }
    
   /**
    * Gets the Taxable Trust Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Taxable Trust Date or the specified default value.
    */
   public final Date getTaxableTrustDate( int index, Date defaultValue )
   {
      return _TaxableTrustDate[index] == null ? defaultValue : _TaxableTrustDate[index];
   }
    
   /**
    * Gets the array of Taxable Trust Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Taxable Trust Date values.
    */
   public final Date[] getTaxableTrustDateArray()
   {
      return _TaxableTrustDate;
   }
    
   /**
    * Gets the Contract Value Issue Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Value Issue Date or null.
    */
   public final Date getContValIssueDate( int index )
   {
      return _ContValIssueDate[index];
   }
    
   /**
    * Gets the Contract Value Issue Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Value Issue Date or the specified default value.
    */
   public final Date getContValIssueDate( int index, Date defaultValue )
   {
      return _ContValIssueDate[index] == null ? defaultValue : _ContValIssueDate[index];
   }
    
   /**
    * Gets the array of Contract Value Issue Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Value Issue Date values.
    */
   public final Date[] getContValIssueDateArray()
   {
      return _ContValIssueDate;
   }
    
   /**
    * Gets the Contract Value Initial Market Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Value Initial Market Value or null.
    */
   public final String getContValInitMKV( int index )
   {
      return _ContValInitMKV[index];
   }
    
   /**
    * Gets the Contract Value Initial Market Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Value Initial Market Value or the specified default value.
    */
   public final String getContValInitMKV( int index, String defaultValue )
   {
      return _ContValInitMKV[index] == null ? defaultValue : _ContValInitMKV[index];
   }
    
   /**
    * Gets the array of Contract Value Initial Market Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Value Initial Market Value values.
    */
   public final String[] getContValInitMKVArray()
   {
      return _ContValInitMKV;
   }
    
   /**
    * Gets the Contract Value Net Transaction Amount field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Value Net Transaction Amount or null.
    */
   public final String getContValNetTranAmt( int index )
   {
      return _ContValNetTranAmt[index];
   }
    
   /**
    * Gets the Contract Value Net Transaction Amount field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Value Net Transaction Amount or the specified default value.
    */
   public final String getContValNetTranAmt( int index, String defaultValue )
   {
      return _ContValNetTranAmt[index] == null ? defaultValue : _ContValNetTranAmt[index];
   }
    
   /**
    * Gets the array of Contract Value Net Transaction Amount fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Value Net Transaction Amount values.
    */
   public final String[] getContValNetTranAmtArray()
   {
      return _ContValNetTranAmt;
   }
    
   /**
    * Gets the Contract Value Net Transaction Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Contract Value Net Transaction Date or null.
    */
   public final Date getContValNetTranDate( int index )
   {
      return _ContValNetTranDate[index];
   }
    
   /**
    * Gets the Contract Value Net Transaction Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Contract Value Net Transaction Date or the specified default value.
    */
   public final Date getContValNetTranDate( int index, Date defaultValue )
   {
      return _ContValNetTranDate[index] == null ? defaultValue : _ContValNetTranDate[index];
   }
    
   /**
    * Gets the array of Contract Value Net Transaction Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Contract Value Net Transaction Date values.
    */
   public final Date[] getContValNetTranDateArray()
   {
      return _ContValNetTranDate;
   }
    
   /**
    * Gets the Account Fee Model Associated field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Fee Model Associated or null.
    */
   public final Boolean getAcctFeeModelAssociated( int index )
   {
      return _AcctFeeModelAssociated[index];
   }
    
   /**
    * Gets the Account Fee Model Associated field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Fee Model Associated or the specified default value.
    */
   public final boolean getAcctFeeModelAssociated( int index, boolean defaultValue )
   {
      return _AcctFeeModelAssociated[index] == null ? defaultValue : _AcctFeeModelAssociated[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Fee Model Associated fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Fee Model Associated values.
    */
   public final Boolean[] getAcctFeeModelAssociatedArray()
   {
      return _AcctFeeModelAssociated;
   }
    
   /**
    * Gets the Shareholder Output Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Shareholder Output Type or null.
    */
   public final String getShrOutputType( int index )
   {
      return _ShrOutputType[index];
   }
    
   /**
    * Gets the Shareholder Output Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Output Type or the specified default value.
    */
   public final String getShrOutputType( int index, String defaultValue )
   {
      return _ShrOutputType[index] == null ? defaultValue : _ShrOutputType[index];
   }
    
   /**
    * Gets the array of Shareholder Output Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Shareholder Output Type values.
    */
   public final String[] getShrOutputTypeArray()
   {
      return _ShrOutputType;
   }
    
   /**
    * Gets the Annuitant age (younger for joint annuitant age) field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Annuitant age (younger for joint annuitant age) or null.
    */
   public final Integer getAnnuitantYoungerAge( int index )
   {
      return _AnnuitantYoungerAge[index];
   }
    
   /**
    * Gets the Annuitant age (younger for joint annuitant age) field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annuitant age (younger for joint annuitant age) or the specified default value.
    */
   public final int getAnnuitantYoungerAge( int index, int defaultValue )
   {
      return _AnnuitantYoungerAge[index] == null ? defaultValue : _AnnuitantYoungerAge[index].intValue();
   }
    
   /**
    * Gets the array of Annuitant age (younger for joint annuitant age) fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Annuitant age (younger for joint annuitant age) values.
    */
   public final Integer[] getAnnuitantYoungerAgeArray()
   {
      return _AnnuitantYoungerAge;
   }
    
   /**
    * Gets the Account Identifier record Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Identifier record Exist or null.
    */
   public final Boolean getAcctIdentifierExist( int index )
   {
      return _AcctIdentifierExist[index];
   }
    
   /**
    * Gets the Account Identifier record Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Identifier record Exist or the specified default value.
    */
   public final boolean getAcctIdentifierExist( int index, boolean defaultValue )
   {
      return _AcctIdentifierExist[index] == null ? defaultValue : _AcctIdentifierExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Identifier record Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Identifier record Exist values.
    */
   public final Boolean[] getAcctIdentifierExistArray()
   {
      return _AcctIdentifierExist;
   }
    
   /**
    * Gets the Account Regulatory Detail Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Regulatory Detail Exist or null.
    */
   public final Boolean getAcctRegDetlExist( int index )
   {
      return _AcctRegDetlExist[index];
   }
    
   /**
    * Gets the Account Regulatory Detail Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Regulatory Detail Exist or the specified default value.
    */
   public final boolean getAcctRegDetlExist( int index, boolean defaultValue )
   {
      return _AcctRegDetlExist[index] == null ? defaultValue : _AcctRegDetlExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Regulatory Detail Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Regulatory Detail Exist values.
    */
   public final Boolean[] getAcctRegDetlExistArray()
   {
      return _AcctRegDetlExist;
   }
    
   /**
    * Gets the Entity Regulatory Setup Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Regulatory Setup Exist or null.
    */
   public final String getEntRegSetupExist( int index )
   {
      return _EntRegSetupExist[index];
   }
    
   /**
    * Gets the Entity Regulatory Setup Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Regulatory Setup Exist or the specified default value.
    */
   public final String getEntRegSetupExist( int index, String defaultValue )
   {
      return _EntRegSetupExist[index] == null ? defaultValue : _EntRegSetupExist[index];
   }
    
   /**
    * Gets the array of Entity Regulatory Setup Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Regulatory Setup Exist values.
    */
   public final String[] getEntRegSetupExistArray()
   {
      return _EntRegSetupExist;
   }
    
   /**
    * Gets the Pending FATCA Search field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Pending FATCA Search or null.
    */
   public final Boolean getPendingFATCASrch( int index )
   {
      return _PendingFATCASrch[index];
   }
    
   /**
    * Gets the Pending FATCA Search field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pending FATCA Search or the specified default value.
    */
   public final boolean getPendingFATCASrch( int index, boolean defaultValue )
   {
      return _PendingFATCASrch[index] == null ? defaultValue : _PendingFATCASrch[index].booleanValue();
   }
    
   /**
    * Gets the array of Pending FATCA Search fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Pending FATCA Search values.
    */
   public final Boolean[] getPendingFATCASrchArray()
   {
      return _PendingFATCASrch;
   }
    
   /**
    * Gets the CID Money Movement Eligible field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CID Money Movement Eligible or null.
    */
   public final Boolean getAcctCIDElig( int index )
   {
      return _AcctCIDElig[index];
   }
    
   /**
    * Gets the CID Money Movement Eligible field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CID Money Movement Eligible or the specified default value.
    */
   public final boolean getAcctCIDElig( int index, boolean defaultValue )
   {
      return _AcctCIDElig[index] == null ? defaultValue : _AcctCIDElig[index].booleanValue();
   }
    
   /**
    * Gets the array of CID Money Movement Eligible fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CID Money Movement Eligible values.
    */
   public final Boolean[] getAcctCIDEligArray()
   {
      return _AcctCIDElig;
   }
    
   /**
    * Gets the Flag to indicate if Trailer Fee Rebate is existed field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag to indicate if Trailer Fee Rebate is existed or null.
    */
   public final Boolean getTFRExists( int index )
   {
      return _TFRExists[index];
   }
    
   /**
    * Gets the Flag to indicate if Trailer Fee Rebate is existed field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag to indicate if Trailer Fee Rebate is existed or the specified default value.
    */
   public final boolean getTFRExists( int index, boolean defaultValue )
   {
      return _TFRExists[index] == null ? defaultValue : _TFRExists[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag to indicate if Trailer Fee Rebate is existed fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag to indicate if Trailer Fee Rebate is existed values.
    */
   public final Boolean[] getTFRExistsArray()
   {
      return _TFRExists;
   }
    
   /**
    * Gets the AdvisorFeeExist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AdvisorFeeExist or null.
    */
   public final Boolean getAdvisorFeeExist( int index )
   {
      return _AdvisorFeeExist[index];
   }
    
   /**
    * Gets the AdvisorFeeExist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AdvisorFeeExist or the specified default value.
    */
   public final boolean getAdvisorFeeExist( int index, boolean defaultValue )
   {
      return _AdvisorFeeExist[index] == null ? defaultValue : _AdvisorFeeExist[index].booleanValue();
   }
    
   /**
    * Gets the array of AdvisorFeeExist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AdvisorFeeExist values.
    */
   public final Boolean[] getAdvisorFeeExistArray()
   {
      return _AdvisorFeeExist;
   }
    
   /**
    * Gets the InvestorClassification field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the InvestorClassification or null.
    */
   public final String getInvestorClassification( int index )
   {
      return _InvestorClassification[index];
   }
    
   /**
    * Gets the InvestorClassification field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvestorClassification or the specified default value.
    */
   public final String getInvestorClassification( int index, String defaultValue )
   {
      return _InvestorClassification[index] == null ? defaultValue : _InvestorClassification[index];
   }
    
   /**
    * Gets the array of InvestorClassification fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of InvestorClassification values.
    */
   public final String[] getInvestorClassificationArray()
   {
      return _InvestorClassification;
   }
    
   /**
    * Gets the AIFMDInvestorCategory field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AIFMDInvestorCategory or null.
    */
   public final String getAIFMDInvestorCategory( int index )
   {
      return _AIFMDInvestorCategory[index];
   }
    
   /**
    * Gets the AIFMDInvestorCategory field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AIFMDInvestorCategory or the specified default value.
    */
   public final String getAIFMDInvestorCategory( int index, String defaultValue )
   {
      return _AIFMDInvestorCategory[index] == null ? defaultValue : _AIFMDInvestorCategory[index];
   }
    
   /**
    * Gets the array of AIFMDInvestorCategory fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AIFMDInvestorCategory values.
    */
   public final String[] getAIFMDInvestorCategoryArray()
   {
      return _AIFMDInvestorCategory;
   }
    
   /**
    * Gets the Account Group Exist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Group Exist or null.
    */
   public final Boolean getAccountGroupExist( int index )
   {
      return _AccountGroupExist[index];
   }
    
   /**
    * Gets the Account Group Exist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Group Exist or the specified default value.
    */
   public final boolean getAccountGroupExist( int index, boolean defaultValue )
   {
      return _AccountGroupExist[index] == null ? defaultValue : _AccountGroupExist[index].booleanValue();
   }
    
   /**
    * Gets the array of Account Group Exist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Group Exist values.
    */
   public final Boolean[] getAccountGroupExistArray()
   {
      return _AccountGroupExist;
   }
    
   /**
    * Gets the Private Wealth Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Private Wealth Account or null.
    */
   public final Boolean getPrivateWealthAcct( int index )
   {
      return _PrivateWealthAcct[index];
   }
    
   /**
    * Gets the Private Wealth Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Private Wealth Account or the specified default value.
    */
   public final boolean getPrivateWealthAcct( int index, boolean defaultValue )
   {
      return _PrivateWealthAcct[index] == null ? defaultValue : _PrivateWealthAcct[index].booleanValue();
   }
    
   /**
    * Gets the array of Private Wealth Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Private Wealth Account values.
    */
   public final Boolean[] getPrivateWealthAcctArray()
   {
      return _PrivateWealthAcct;
   }
    
   /**
    * Gets the Private Wealth Opt Out field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Private Wealth Opt Out or null.
    */
   public final Boolean getPrivateWealthOptOut( int index )
   {
      return _PrivateWealthOptOut[index];
   }
    
   /**
    * Gets the Private Wealth Opt Out field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Private Wealth Opt Out or the specified default value.
    */
   public final boolean getPrivateWealthOptOut( int index, boolean defaultValue )
   {
      return _PrivateWealthOptOut[index] == null ? defaultValue : _PrivateWealthOptOut[index].booleanValue();
   }
    
   /**
    * Gets the array of Private Wealth Opt Out fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Private Wealth Opt Out values.
    */
   public final Boolean[] getPrivateWealthOptOutArray()
   {
      return _PrivateWealthOptOut;
   }
    
   /**
    * Gets the Tax Forms Apply field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Forms Apply or null.
    */
   public final Boolean getTaxFormsAppl( int index )
   {
      return _TaxFormsAppl[index];
   }
    
   /**
    * Gets the Tax Forms Apply field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Forms Apply or the specified default value.
    */
   public final boolean getTaxFormsAppl( int index, boolean defaultValue )
   {
      return _TaxFormsAppl[index] == null ? defaultValue : _TaxFormsAppl[index].booleanValue();
   }
    
   /**
    * Gets the array of Tax Forms Apply fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Forms Apply values.
    */
   public final Boolean[] getTaxFormsApplArray()
   {
      return _TaxFormsAppl;
   }
    
   /**
    * Gets the AggrType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AggrType or null.
    */
   public final String getAggrType( int index )
   {
      return _AggrType[index];
   }
    
   /**
    * Gets the AggrType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AggrType or the specified default value.
    */
   public final String getAggrType( int index, String defaultValue )
   {
      return _AggrType[index] == null ? defaultValue : _AggrType[index];
   }
    
   /**
    * Gets the array of AggrType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AggrType values.
    */
   public final String[] getAggrTypeArray()
   {
      return _AggrType;
   }
    
   /**
    * Gets the MoneyInExist field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the MoneyInExist or null.
    */
   public final Boolean getMoneyInExist( int index )
   {
      return _MoneyInExist[index];
   }
    
   /**
    * Gets the MoneyInExist field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MoneyInExist or the specified default value.
    */
   public final boolean getMoneyInExist( int index, boolean defaultValue )
   {
      return _MoneyInExist[index] == null ? defaultValue : _MoneyInExist[index].booleanValue();
   }
    
   /**
    * Gets the array of MoneyInExist fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of MoneyInExist values.
    */
   public final Boolean[] getMoneyInExistArray()
   {
      return _MoneyInExist;
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
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _AccountNum = resizeArray( _AccountNum, _RepeatCount );
      _BeneficialOwner = resizeArray( _BeneficialOwner, _RepeatCount );
      _AltAccount = resizeArray( _AltAccount, _RepeatCount );
      _AcctType = resizeArray( _AcctType, _RepeatCount );
      _AcctTypeDesc = resizeArray( _AcctTypeDesc, _RepeatCount );
      _TaxType = resizeArray( _TaxType, _RepeatCount );
      _TaxTypeDesc = resizeArray( _TaxTypeDesc, _RepeatCount );
      _RecipientType = resizeArray( _RecipientType, _RepeatCount );
      _RecipientTypeDesc = resizeArray( _RecipientTypeDesc, _RepeatCount );
      _AcctDesignation = resizeArray( _AcctDesignation, _RepeatCount );
      _AcctDesignationDesc = resizeArray( _AcctDesignationDesc, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _CurrencyName = resizeArray( _CurrencyName, _RepeatCount );
      _XrefNum = resizeArray( _XrefNum, _RepeatCount );
      _BrokerCode = resizeArray( _BrokerCode, _RepeatCount );
      _BranchCode = resizeArray( _BranchCode, _RepeatCount );
      _Slsrep = resizeArray( _Slsrep, _RepeatCount );
      _InterCode = resizeArray( _InterCode, _RepeatCount );
      _InterAccount = resizeArray( _InterAccount, _RepeatCount );
      _AcctStatus = resizeArray( _AcctStatus, _RepeatCount );
      _AcctStatusDesc = resizeArray( _AcctStatusDesc, _RepeatCount );
      _DateOfReg = resizeArray( _DateOfReg, _RepeatCount );
      _RRSPFee = resizeArray( _RRSPFee, _RepeatCount );
      _RRSPFeeDesc = resizeArray( _RRSPFeeDesc, _RepeatCount );
      _AMSCode = resizeArray( _AMSCode, _RepeatCount );
      _PensionJuris = resizeArray( _PensionJuris, _RepeatCount );
      _PensionJurisDesc = resizeArray( _PensionJurisDesc, _RepeatCount );
      _StopPurchase = resizeArray( _StopPurchase, _RepeatCount );
      _StopXferIn = resizeArray( _StopXferIn, _RepeatCount );
      _StopXferOut = resizeArray( _StopXferOut, _RepeatCount );
      _StopRed = resizeArray( _StopRed, _RepeatCount );
      _FeeWaived = resizeArray( _FeeWaived, _RepeatCount );
      _MarketMail = resizeArray( _MarketMail, _RepeatCount );
      _Unseizable = resizeArray( _Unseizable, _RepeatCount );
      _RegCompleted = resizeArray( _RegCompleted, _RepeatCount );
      _SupConf = resizeArray( _SupConf, _RepeatCount );
      _SupEmpConf = resizeArray( _SupEmpConf, _RepeatCount );
      _InTrustFor = resizeArray( _InTrustFor, _RepeatCount );
      _Escrow = resizeArray( _Escrow, _RepeatCount );
      _AcctGroup = resizeArray( _AcctGroup, _RepeatCount );
      _AcctGroupName = resizeArray( _AcctGroupName, _RepeatCount );
      _BrokerName = resizeArray( _BrokerName, _RepeatCount );
      _BranchName = resizeArray( _BranchName, _RepeatCount );
      _SlsrepName = resizeArray( _SlsrepName, _RepeatCount );
      _SlsrepAltName = resizeArray( _SlsrepAltName, _RepeatCount );
      _AccountBalance = resizeArray( _AccountBalance, _RepeatCount );
      _ShrNum = resizeArray( _ShrNum, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _AcctMstrVer = resizeArray( _AcctMstrVer, _RepeatCount );
      _AcctMstrRid = resizeArray( _AcctMstrRid, _RepeatCount );
      _Employee = resizeArray( _Employee, _RepeatCount );
      _MinWithAge = resizeArray( _MinWithAge, _RepeatCount );
      _ExistSIN = resizeArray( _ExistSIN, _RepeatCount );
      _ValidSIN = resizeArray( _ValidSIN, _RepeatCount );
      _ValidTaxJuris = resizeArray( _ValidTaxJuris, _RepeatCount );
      _ExistBenAddr = resizeArray( _ExistBenAddr, _RepeatCount );
      _HoldMail = resizeArray( _HoldMail, _RepeatCount );
      _ExistEscrow = resizeArray( _ExistEscrow, _RepeatCount );
      _ExistBeneficiary = resizeArray( _ExistBeneficiary, _RepeatCount );
      _ExistAlloc = resizeArray( _ExistAlloc, _RepeatCount );
      _OutWireOrd = resizeArray( _OutWireOrd, _RepeatCount );
      _SlsRepActive = resizeArray( _SlsRepActive, _RepeatCount );
      _ClosingContr = resizeArray( _ClosingContr, _RepeatCount );
      _ContrMatured = resizeArray( _ContrMatured, _RepeatCount );
      _Age69 = resizeArray( _Age69, _RepeatCount );
      _DeathClaim = resizeArray( _DeathClaim, _RepeatCount );
      _AddAcctFlag = resizeArray( _AddAcctFlag, _RepeatCount );
      _PendingTrade = resizeArray( _PendingTrade, _RepeatCount );
      _Certificates = resizeArray( _Certificates, _RepeatCount );
      _SystemTrsfr = resizeArray( _SystemTrsfr, _RepeatCount );
      _PAC = resizeArray( _PAC, _RepeatCount );
      _SWP = resizeArray( _SWP, _RepeatCount );
      _AcctAlloc = resizeArray( _AcctAlloc, _RepeatCount );
      _ClanPlan = resizeArray( _ClanPlan, _RepeatCount );
      _UnsettledTrn = resizeArray( _UnsettledTrn, _RepeatCount );
      _TransFound = resizeArray( _TransFound, _RepeatCount );
      _FirstEffective = resizeArray( _FirstEffective, _RepeatCount );
      _MaxApplies = resizeArray( _MaxApplies, _RepeatCount );
      _RRIFQualified = resizeArray( _RRIFQualified, _RepeatCount );
      _LegMinWithAge = resizeArray( _LegMinWithAge, _RepeatCount );
      _LockedIn = resizeArray( _LockedIn, _RepeatCount );
      _FedJurAllowed = resizeArray( _FedJurAllowed, _RepeatCount );
      _MinAge = resizeArray( _MinAge, _RepeatCount );
      _MaxAge = resizeArray( _MaxAge, _RepeatCount );
      _TaxTypeRules = resizeArray( _TaxTypeRules, _RepeatCount );
      _DefTaxTypeRules = resizeArray( _DefTaxTypeRules, _RepeatCount );
      _FCConfig = resizeArray( _FCConfig, _RepeatCount );
      _StopFCrebal = resizeArray( _StopFCrebal, _RepeatCount );
      _FCOverrides = resizeArray( _FCOverrides, _RepeatCount );
      _AllLocked = resizeArray( _AllLocked, _RepeatCount );
      _AcctLocked = resizeArray( _AcctLocked, _RepeatCount );
      _SelfDirected = resizeArray( _SelfDirected, _RepeatCount );
      _PlanType = resizeArray( _PlanType, _RepeatCount );
      _ValidSpSIN = resizeArray( _ValidSpSIN, _RepeatCount );
      _RIFExist = resizeArray( _RIFExist, _RepeatCount );
      _DeathStat = resizeArray( _DeathStat, _RepeatCount );
      _ACBExist = resizeArray( _ACBExist, _RepeatCount );
      _IntAccrExist = resizeArray( _IntAccrExist, _RepeatCount );
      _DistribExist = resizeArray( _DistribExist, _RepeatCount );
      _ChequeExist = resizeArray( _ChequeExist, _RepeatCount );
      _ContractExist = resizeArray( _ContractExist, _RepeatCount );
      _OutstLLP = resizeArray( _OutstLLP, _RepeatCount );
      _SocialCode = resizeArray( _SocialCode, _RepeatCount );
      _SocialCodeDesc = resizeArray( _SocialCodeDesc, _RepeatCount );
      _SavePlanExist = resizeArray( _SavePlanExist, _RepeatCount );
      _ProdCode = resizeArray( _ProdCode, _RepeatCount );
      _AcctCommExists = resizeArray( _AcctCommExists, _RepeatCount );
      _GSTExempt = resizeArray( _GSTExempt, _RepeatCount );
      _AcctFeesExist = resizeArray( _AcctFeesExist, _RepeatCount );
      _ApplyPST = resizeArray( _ApplyPST, _RepeatCount );
      _Unisex = resizeArray( _Unisex, _RepeatCount );
      _SexDistinct = resizeArray( _SexDistinct, _RepeatCount );
      _BankCharge = resizeArray( _BankCharge, _RepeatCount );
      _ConsolidEFT = resizeArray( _ConsolidEFT, _RepeatCount );
      _PensionJurisAvail = resizeArray( _PensionJurisAvail, _RepeatCount );
      _FirstSettleDate = resizeArray( _FirstSettleDate, _RepeatCount );
      _AMSROCode = resizeArray( _AMSROCode, _RepeatCount );
      _MgmtFeePayOption = resizeArray( _MgmtFeePayOption, _RepeatCount );
      _CreatedToday = resizeArray( _CreatedToday, _RepeatCount );
      _ProtContractExists = resizeArray( _ProtContractExists, _RepeatCount );
      _AcctCatExists = resizeArray( _AcctCatExists, _RepeatCount );
      _ChargeERFee = resizeArray( _ChargeERFee, _RepeatCount );
      _ChargeSTTRFee = resizeArray( _ChargeSTTRFee, _RepeatCount );
      _UseBrokerMF = resizeArray( _UseBrokerMF, _RepeatCount );
      _StopAMSRebal = resizeArray( _StopAMSRebal, _RepeatCount );
      _AcctPurpose = resizeArray( _AcctPurpose, _RepeatCount );
      _AdditionalInfo = resizeArray( _AdditionalInfo, _RepeatCount );
      _BusinessNo = resizeArray( _BusinessNo, _RepeatCount );
      _MemorablePlace = resizeArray( _MemorablePlace, _RepeatCount );
      _MemorableWord = resizeArray( _MemorableWord, _RepeatCount );
      _MemorableDate = resizeArray( _MemorableDate, _RepeatCount );
      _PensionLegCode = resizeArray( _PensionLegCode, _RepeatCount );
      _TelFaxAgreement = resizeArray( _TelFaxAgreement, _RepeatCount );
      _ClearingID = resizeArray( _ClearingID, _RepeatCount );
      _SettlLocExist = resizeArray( _SettlLocExist, _RepeatCount );
      _DTAType = resizeArray( _DTAType, _RepeatCount );
      _NetworkControlInd = resizeArray( _NetworkControlInd, _RepeatCount );
      _ClearingFirm = resizeArray( _ClearingFirm, _RepeatCount );
      _LSIFPAC = resizeArray( _LSIFPAC, _RepeatCount );
      _HighestEntityRisk = resizeArray( _HighestEntityRisk, _RepeatCount );
      _StopRedSettle = resizeArray( _StopRedSettle, _RepeatCount );
      _RegistrationInfo = resizeArray( _RegistrationInfo, _RepeatCount );
      _FeeModelCode = resizeArray( _FeeModelCode, _RepeatCount );
      _DSCFeeLevel = resizeArray( _DSCFeeLevel, _RepeatCount );
      _LatestEffectiveDate = resizeArray( _LatestEffectiveDate, _RepeatCount );
      _AcctCutOffExist = resizeArray( _AcctCutOffExist, _RepeatCount );
      _AgentForFirmAgencyCode = resizeArray( _AgentForFirmAgencyCode, _RepeatCount );
      _TPAFirmAgencyCode = resizeArray( _TPAFirmAgencyCode, _RepeatCount );
      _NSCPartId = resizeArray( _NSCPartId, _RepeatCount );
      _NetworkID = resizeArray( _NetworkID, _RepeatCount );
      _ExistAssignee = resizeArray( _ExistAssignee, _RepeatCount );
      _ConsolTypePW = resizeArray( _ConsolTypePW, _RepeatCount );
      _FundLimitOvrdExist = resizeArray( _FundLimitOvrdExist, _RepeatCount );
      _NSCDividend = resizeArray( _NSCDividend, _RepeatCount );
      _ConsolTypeID = resizeArray( _ConsolTypeID, _RepeatCount );
      _PendingPrivate = resizeArray( _PendingPrivate, _RepeatCount );
      _AcctClosingReason = resizeArray( _AcctClosingReason, _RepeatCount );
      _ActiveAMSExist = resizeArray( _ActiveAMSExist, _RepeatCount );
      _SiblingOnly = resizeArray( _SiblingOnly, _RepeatCount );
      _Aflluent = resizeArray( _Aflluent, _RepeatCount );
      _MgmtFeeID = resizeArray( _MgmtFeeID, _RepeatCount );
      _MgmtFeeType = resizeArray( _MgmtFeeType, _RepeatCount );
      _MgmtFeeRbtID = resizeArray( _MgmtFeeRbtID, _RepeatCount );
      _MgmtFeeRbtType = resizeArray( _MgmtFeeRbtType, _RepeatCount );
      _LinkMFR = resizeArray( _LinkMFR, _RepeatCount );
      _AcctAMSExist = resizeArray( _AcctAMSExist, _RepeatCount );
      _InvoiceModelID = resizeArray( _InvoiceModelID, _RepeatCount );
      _ActiveCert = resizeArray( _ActiveCert, _RepeatCount );
      _MinWaived = resizeArray( _MinWaived, _RepeatCount );
      _HoldDivPymt = resizeArray( _HoldDivPymt, _RepeatCount );
      _DOTAdnd = resizeArray( _DOTAdnd, _RepeatCount );
      _SettlementRuleExist = resizeArray( _SettlementRuleExist, _RepeatCount );
      _TaxTypeSchedule = resizeArray( _TaxTypeSchedule, _RepeatCount );
      _AcctActivityExists = resizeArray( _AcctActivityExists, _RepeatCount );
      _StopReason = resizeArray( _StopReason, _RepeatCount );
      _StopReasonOther = resizeArray( _StopReasonOther, _RepeatCount );
      _InvestorType = resizeArray( _InvestorType, _RepeatCount );
      _InvestFor3rdParty = resizeArray( _InvestFor3rdParty, _RepeatCount );
      _ComplianceCode = resizeArray( _ComplianceCode, _RepeatCount );
      _AcctDocListExist = resizeArray( _AcctDocListExist, _RepeatCount );
      _UnitRoundMethod = resizeArray( _UnitRoundMethod, _RepeatCount );
      _UnLockGrossAmt = resizeArray( _UnLockGrossAmt, _RepeatCount );
      _UnLockDeff = resizeArray( _UnLockDeff, _RepeatCount );
      _RtnMailStage = resizeArray( _RtnMailStage, _RepeatCount );
      _StaleChqStage = resizeArray( _StaleChqStage, _RepeatCount );
      _StopNFU = resizeArray( _StopNFU, _RepeatCount );
      _ExemptDate = resizeArray( _ExemptDate, _RepeatCount );
      _NextMFRProcessDate = resizeArray( _NextMFRProcessDate, _RepeatCount );
      _IsMFRAccount = resizeArray( _IsMFRAccount, _RepeatCount );
      _IsClosedCountryResident = resizeArray( _IsClosedCountryResident, _RepeatCount );
      _InvestorAuthorizationExist = resizeArray( _InvestorAuthorizationExist, _RepeatCount );
      _EntityUnverifiedExist = resizeArray( _EntityUnverifiedExist, _RepeatCount );
      _GrandFathered = resizeArray( _GrandFathered, _RepeatCount );
      _RESPBenefDeleted = resizeArray( _RESPBenefDeleted, _RepeatCount );
      _RESPAcctInfoExists = resizeArray( _RESPAcctInfoExists, _RepeatCount );
      _Pre98Contrib = resizeArray( _Pre98Contrib, _RepeatCount );
      _AIPWithdrawalExists = resizeArray( _AIPWithdrawalExists, _RepeatCount );
      _OrigPlanDeff = resizeArray( _OrigPlanDeff, _RepeatCount );
      _IsGWOContract = resizeArray( _IsGWOContract, _RepeatCount );
      _AcctGuarGuardExists = resizeArray( _AcctGuarGuardExists, _RepeatCount );
      _RESPQCResidentFound = resizeArray( _RESPQCResidentFound, _RepeatCount );
      _GovAmendmentExist = resizeArray( _GovAmendmentExist, _RepeatCount );
      _IsAcctRunToCurFile = resizeArray( _IsAcctRunToCurFile, _RepeatCount );
      _HasAcctBeenUnFrozen = resizeArray( _HasAcctBeenUnFrozen, _RepeatCount );
      _StaleChqExists = resizeArray( _StaleChqExists, _RepeatCount );
      _RemittedChqExists = resizeArray( _RemittedChqExists, _RepeatCount );
      _RemittedChqStage = resizeArray( _RemittedChqStage, _RepeatCount );
      _ConsolTypeED = resizeArray( _ConsolTypeED, _RepeatCount );
      _InceptionDate = resizeArray( _InceptionDate, _RepeatCount );
      _ProdPortfolioUUID = resizeArray( _ProdPortfolioUUID, _RepeatCount );
      _ProdPortfolioPlanUUID = resizeArray( _ProdPortfolioPlanUUID, _RepeatCount );
      _UnclmRemitDate = resizeArray( _UnclmRemitDate, _RepeatCount );
      _NSCSocialCode = resizeArray( _NSCSocialCode, _RepeatCount );
      _HasGIAHolding = resizeArray( _HasGIAHolding, _RepeatCount );
      _CanHaveCashSweep = resizeArray( _CanHaveCashSweep, _RepeatCount );
      _CanHaveMatInstr = resizeArray( _CanHaveMatInstr, _RepeatCount );
      _CashSweepExists = resizeArray( _CashSweepExists, _RepeatCount );
      _MatIntExists = resizeArray( _MatIntExists, _RepeatCount );
      _OrgType = resizeArray( _OrgType, _RepeatCount );
      _SubOrgType = resizeArray( _SubOrgType, _RepeatCount );
      _TerritoryCode = resizeArray( _TerritoryCode, _RepeatCount );
      _CommitmentStatus = resizeArray( _CommitmentStatus, _RepeatCount );
      _LifeAnnuityExists = resizeArray( _LifeAnnuityExists, _RepeatCount );
      _StopAdjDate = resizeArray( _StopAdjDate, _RepeatCount );
      _NonFinConfirm = resizeArray( _NonFinConfirm, _RepeatCount );
      _SettleCurrency = resizeArray( _SettleCurrency, _RepeatCount );
      _RegAgentCode = resizeArray( _RegAgentCode, _RepeatCount );
      _GWLWAAvailOptions = resizeArray( _GWLWAAvailOptions, _RepeatCount );
      _T5AnniversaryDate = resizeArray( _T5AnniversaryDate, _RepeatCount );
      _SWPGLOpt = resizeArray( _SWPGLOpt, _RepeatCount );
      _RRIFGLOpt = resizeArray( _RRIFGLOpt, _RepeatCount );
      _TaxableTrustDate = resizeArray( _TaxableTrustDate, _RepeatCount );
      _ContValIssueDate = resizeArray( _ContValIssueDate, _RepeatCount );
      _ContValInitMKV = resizeArray( _ContValInitMKV, _RepeatCount );
      _ContValNetTranAmt = resizeArray( _ContValNetTranAmt, _RepeatCount );
      _ContValNetTranDate = resizeArray( _ContValNetTranDate, _RepeatCount );
      _AcctFeeModelAssociated = resizeArray( _AcctFeeModelAssociated, _RepeatCount );
      _ShrOutputType = resizeArray( _ShrOutputType, _RepeatCount );
      _AnnuitantYoungerAge = resizeArray( _AnnuitantYoungerAge, _RepeatCount );
      _AcctIdentifierExist = resizeArray( _AcctIdentifierExist, _RepeatCount );
      _AcctRegDetlExist = resizeArray( _AcctRegDetlExist, _RepeatCount );
      _EntRegSetupExist = resizeArray( _EntRegSetupExist, _RepeatCount );
      _PendingFATCASrch = resizeArray( _PendingFATCASrch, _RepeatCount );
      _AcctCIDElig = resizeArray( _AcctCIDElig, _RepeatCount );
      _TFRExists = resizeArray( _TFRExists, _RepeatCount );
      _AdvisorFeeExist = resizeArray( _AdvisorFeeExist, _RepeatCount );
      _InvestorClassification = resizeArray( _InvestorClassification, _RepeatCount );
      _AIFMDInvestorCategory = resizeArray( _AIFMDInvestorCategory, _RepeatCount );
      _AccountGroupExist = resizeArray( _AccountGroupExist, _RepeatCount );
      _PrivateWealthAcct = resizeArray( _PrivateWealthAcct, _RepeatCount );
      _PrivateWealthOptOut = resizeArray( _PrivateWealthOptOut, _RepeatCount );
      _TaxFormsAppl = resizeArray( _TaxFormsAppl, _RepeatCount );
      _AggrType = resizeArray( _AggrType, _RepeatCount );
      _MoneyInExist = resizeArray( _MoneyInExist, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AccountNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BeneficialOwner[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AltAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecipientType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RecipientTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDesignation[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDesignationDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CurrencyName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XrefNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Slsrep[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InterCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InterAccount[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctStatusDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DateOfReg[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RRSPFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPFeeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AMSCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PensionJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PensionJurisDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopPurchase[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopXferOut[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopRed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FeeWaived[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MarketMail[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Unseizable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RegCompleted[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SupConf[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SupEmpConf[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InTrustFor[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Escrow[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctGroup[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctGroupName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BrokerName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BranchName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsrepName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SlsrepAltName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountBalance[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ShrNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctMstrVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctMstrRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Employee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MinWithAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _ExistSIN[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ValidSIN[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ValidTaxJuris[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExistBenAddr[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _HoldMail[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExistEscrow[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExistBeneficiary[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExistAlloc[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OutWireOrd[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SlsRepActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ClosingContr[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ContrMatured[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Age69[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DeathClaim[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AddAcctFlag[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PendingTrade[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Certificates[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SystemTrsfr[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PAC[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SWP[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctAlloc[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ClanPlan[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _UnsettledTrn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TransFound[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FirstEffective[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _MaxApplies[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RRIFQualified[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _LegMinWithAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _LockedIn[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FedJurAllowed[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MinAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _MaxAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TaxTypeRules[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DefTaxTypeRules[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FCConfig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopFCrebal[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FCOverrides[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AllLocked[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctLocked[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SelfDirected[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PlanType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ValidSpSIN[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RIFExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DeathStat[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ACBExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _IntAccrExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DistribExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ChequeExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ContractExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OutstLLP[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SocialCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SocialCodeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SavePlanExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProdCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctCommExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GSTExempt[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctFeesExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ApplyPST[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Unisex[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SexDistinct[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BankCharge[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ConsolidEFT[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PensionJurisAvail[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _FirstSettleDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AMSROCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtFeePayOption[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CreatedToday[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ProtContractExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctCatExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ChargeERFee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ChargeSTTRFee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _UseBrokerMF[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopAMSRebal[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctPurpose[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AdditionalInfo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BusinessNo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MemorablePlace[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MemorableWord[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MemorableDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _PensionLegCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TelFaxAgreement[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ClearingID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettlLocExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DTAType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetworkControlInd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClearingFirm[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LSIFPAC[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _HighestEntityRisk[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopRedSettle[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RegistrationInfo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FeeModelCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DSCFeeLevel[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LatestEffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AcctCutOffExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AgentForFirmAgencyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TPAFirmAgencyCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NSCPartId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetworkID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExistAssignee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConsolTypePW[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundLimitOvrdExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _NSCDividend[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ConsolTypeID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PendingPrivate[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctClosingReason[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActiveAMSExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SiblingOnly[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Aflluent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtFeeID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtFeeRbtID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MgmtFeeRbtType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LinkMFR[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctAMSExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InvoiceModelID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ActiveCert[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MinWaived[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _HoldDivPymt[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DOTAdnd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SettlementRuleExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxTypeSchedule[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctActivityExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopReason[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopReasonOther[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvestorType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InvestFor3rdParty[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ComplianceCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctDocListExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _UnitRoundMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnLockGrossAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnLockDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _RtnMailStage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StaleChqStage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopNFU[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ExemptDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NextMFRProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _IsMFRAccount[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _IsClosedCountryResident[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InvestorAuthorizationExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EntityUnverifiedExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GrandFathered[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RESPBenefDeleted[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RESPAcctInfoExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _Pre98Contrib[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AIPWithdrawalExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OrigPlanDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _IsGWOContract[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctGuarGuardExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RESPQCResidentFound[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _GovAmendmentExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _IsAcctRunToCurFile[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _HasAcctBeenUnFrozen[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StaleChqExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RemittedChqExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RemittedChqStage[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ConsolTypeED[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _InceptionDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProdPortfolioUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProdPortfolioPlanUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnclmRemitDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NSCSocialCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HasGIAHolding[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CanHaveCashSweep[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CanHaveMatInstr[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CashSweepExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MatIntExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _OrgType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SubOrgType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TerritoryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommitmentStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LifeAnnuityExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _StopAdjDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _NonFinConfirm[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _SettleCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegAgentCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _GWLWAAvailOptions[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _T5AnniversaryDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _SWPGLOpt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFGLOpt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxableTrustDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ContValIssueDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ContValInitMKV[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContValNetTranAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ContValNetTranDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AcctFeeModelAssociated[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ShrOutputType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AnnuitantYoungerAge[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AcctIdentifierExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctRegDetlExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _EntRegSetupExist[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PendingFATCASrch[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcctCIDElig[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TFRExists[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AdvisorFeeExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _InvestorClassification[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AIFMDInvestorCategory[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountGroupExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PrivateWealthAcct[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _PrivateWealthOptOut[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TaxFormsAppl[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AggrType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MoneyInExist[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      }
      

   }

}
      
