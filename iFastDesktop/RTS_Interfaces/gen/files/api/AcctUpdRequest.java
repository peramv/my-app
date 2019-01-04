// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/AcctUpd.doc">AcctUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctUpdRequest extends IFastRequest implements Serializable
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
    * Run Mode member variable.
    */
   private String _RunMode = "";
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Account Number Manual member variable.
    */
   private Boolean _AccountNumManual = new Boolean(false);
            
   /**
    * Alternate Account Number member variable.
    */
   private String _AltAccount = "";
            
   /**
    * Account Type Code member variable.
    */
   private String _AcctType = "";
            
   /**
    * Tax Type member variable.
    */
   private String _TaxType = "";
            
   /**
    * Recipient Type member variable.
    */
   private String _RecipientType = "";
            
   /**
    * Currency Code member variable.
    */
   private String _Currency = "";
            
   /**
    * Cross Reference Number member variable.
    */
   private String _XrefNum = "";
            
   /**
    * Broker Code member variable.
    */
   private String _BrokerCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Sales Rep Code member variable.
    */
   private String _SalesRepCode = "";
            
   /**
    * Intermediary Code member variable.
    */
   private String _InterCode = "";
            
   /**
    * Intermediary Account Number member variable.
    */
   private String _InterAccount = "";
            
   /**
    * Account Status member variable.
    */
   private String _AcctStatus = "";
            
   /**
    * Date of Registration member variable.
    */
   private Date _DateofReg = null;
            
   /**
    * RRSP Fee Indicator member variable.
    */
   private String _RRSPFee = "";
            
   /**
    * Pension Jurisdiction member variable.
    */
   private String _PensionJuris = "";
            
   /**
    * Stop Purchase member variable.
    */
   private Boolean _StopPur = new Boolean(false);
            
   /**
    * Stop Transfer In member variable.
    */
   private Boolean _StopXferIn = new Boolean(false);
            
   /**
    * Stop Transfer Out member variable.
    */
   private Boolean _StopXferOut = new Boolean(false);
            
   /**
    * Stop Redemption member variable.
    */
   private Boolean _StopRed = new Boolean(false);
            
   /**
    * Fee Waived member variable.
    */
   private Boolean _FeeWaived = new Boolean(false);
            
   /**
    * Market Mailing member variable.
    */
   private Boolean _MarketMail = new Boolean(false);
            
   /**
    * Market Mailing Change Shareholder member variable.
    */
   private Boolean _MarketMailChgSh = new Boolean(false);
            
   /**
    * Unseizable member variable.
    */
   private Boolean _Unseizable = new Boolean(false);
            
   /**
    * Registration Completed member variable.
    */
   private Boolean _RegCompleted = new Boolean(false);
            
   /**
    * Suppress All Confirm member variable.
    */
   private Boolean _SupConf = new Boolean(false);
            
   /**
    * Suppress Employee Confirm member variable.
    */
   private Boolean _SupEmpConf = new Boolean(false);
            
   /**
    * In Trust For member variable.
    */
   private Boolean _InTrustFor = new Boolean(false);
            
   /**
    * Escrow member variable.
    */
   private Boolean _Escrow = new Boolean(false);
            
   /**
    * Group Code member variable.
    */
   private String _GroupCode = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Acct Table Version Number member variable.
    */
   private Integer _AcctMstrVer = null;
            
   /**
    * Create SalesRep member variable.
    */
   private Boolean _CreateRep = new Boolean(false);
            
   /**
    * Employee member variable.
    */
   private String _Employee = "";
            
            
            
   /**
    * Social Code member variable.
    */
   private String _SocialCode = "";
            
   /**
    * Stop Foreign Content Rebalancing member variable.
    */
   private Boolean _StopFCRebal = new Boolean(false);
            
   /**
    * GST Exempt member variable.
    */
   private Boolean _GSTExempt = new Boolean(false);
            
   /**
    * Apply PST member variable.
    */
   private Boolean _ApplyPST = new Boolean(false);
            
   /**
    * Stop SWP member variable.
    */
   private Boolean _StopSWP = new Boolean(false);
            
   /**
    * Bank Charge member variable.
    */
   private String _BankCharge = "";
            
   /**
    * Consolidation EFT member variable.
    */
   private String _ConsolidEFT = "";
            
   /**
    * Management Fee Option member variable.
    */
   private String _MgmtFeePayOption = "";
            
   /**
    * Early Redemption Fees will be charged member variable.
    */
   private Boolean _ChargeERFee = new Boolean(false);
            
   /**
    * Short Term Transfer Fees will be charged member variable.
    */
   private Boolean _ChargeSTTRFee = new Boolean(false);
            
   /**
    * StopAMSRebal member variable.
    */
   private Boolean _StopAMSRebal = new Boolean(false);
            
   /**
    * Account Purpose member variable.
    */
   private String _AcctPurpose = "";
            
   /**
    * Additional Information member variable.
    */
   private String _AdditionalInfo = "";
            
   /**
    * Business Number member variable.
    */
   private String _BusinessNo = "";
            
   /**
    * Memorable Place member variable.
    */
   private String _MemorablePlace = "";
            
   /**
    * Memorable Word member variable.
    */
   private String _MemorableWord = "";
            
   /**
    * MemorableDate member variable.
    */
   private Date _MemorableDate = null;
            
   /**
    * PensionLeg Code member variable.
    */
   private String _PensionLegCode = "";
            
   /**
    * Tel/Fax Agreement member variable.
    */
   private Boolean _TelFaxAgreement = new Boolean(false);
            
   /**
    * Clearing Id member variable.
    */
   private String _ClearingId = "";
            
   /**
    * NetworkControlInd member variable.
    */
   private String _NetworkControlInd = "";
            
   /**
    * Stop Redemption from Settlement member variable.
    */
   private Boolean _StopRedSettle = new Boolean(false);
            
   /**
    * Registration Information member variable.
    */
   private String _RegistrationInfo = "";
            
   /**
    * Fee Model Code member variable.
    */
   private String _FeeModelCode = "";
            
   /**
    * Clearing Firm member variable.
    */
   private String _ClearingFirm = "";
            
   /**
    * AgentForFirmAgencyCode member variable.
    */
   private String _AgentForFirmAgencyCode = "";
            
   /**
    * TPAFirmAgencyCode member variable.
    */
   private String _TPAFirmAgencyCode = "";
            
   /**
    * Network ID member variable.
    */
   private String _NetworkID = "";
            
   /**
    * Consolidation Type for Redemption member variable.
    */
   private String _ConsolTypePW = "";
            
   /**
    * Consolidation Type for Distribution member variable.
    */
   private String _ConsolTypeID = "";
            
   /**
    * Account Closing Reason member variable.
    */
   private String _AcctClosingReason = "";
            
   /**
    * Affluent member variable.
    */
   private String _Affluent = "";
            
   /**
    * Hold Dividend Payment member variable.
    */
   private Boolean _HoldDivPymt = new Boolean(false);
            
   /**
    * Dummy Tax Type for Old LIF member variable.
    */
   private String _TaxTypeSchedule = "";
            
   /**
    * Stop Reason member variable.
    */
   private String _StopReason = "";
            
   /**
    * Stop Reason Other member variable.
    */
   private String _StopReasonOther = "";
            
   /**
    * Unit Rounding Method member variable.
    */
   private String _UnitRoundMethod = "";
            
   /**
    * Flag if beneficiaries request additional grants. member variable.
    */
   private String _SiblingOnly = "";
            
   /**
    * Flag if acccount reporting to HRSDC member variable.
    */
   private Boolean _CESGEligible = new Boolean(false);
            
   /**
    * Flag if there were contributions made before 1998 member variable.
    */
   private Boolean _Pre98Contrib = new Boolean(false);
            
   /**
    * Consolidation Type for Purchase member variable.
    */
   private String _ConsolTypeED = "";
            
   /**
    * ProdPortfolio UUID member variable.
    */
   private String _ProdPortfolioUUID = "";
            
   /**
    * ProdPortfolioPlan UUID member variable.
    */
   private String _ProdPortfolioPlanUUID = "";
            
   /**
    * Date that property is remitted to the government member variable.
    */
   private Date _UnclmRemitDate = null;
            
   /**
    * NSCC Social Code member variable.
    */
   private String _NSCSocialCode = "";
            
   /**
    * Organisation Type member variable.
    */
   private String _OrgType = "";
            
   /**
    * Sub Organisation Type member variable.
    */
   private String _SubOrgType = "";
            
   /**
    * Account Settlement Currency member variable.
    */
   private String _SettleCurrency = "";
            
   /**
    * Non Financial Confirm member variable.
    */
   private Boolean _NonFinConfirm = new Boolean(false);
            
   /**
    * Stop Adjustment Date member variable.
    */
   private Date _StopAdjDate = null;
            
   /**
    * Contract Value Issue Date member variable.
    */
   private Date _ContValIssueDate = null;
            
   /**
    * Contract Value Initial Market Value member variable.
    */
   private String _ContValInitMKV = "0";
            
   /**
    * Contract Value Net Transaction Amount member variable.
    */
   private String _ContValNetTranAmt = "0";
            
   /**
    * Contract Value Net Transaction Date member variable.
    */
   private Date _ContValNetTranDate = null;
            
   /**
    * Shareholder Output Type member variable.
    */
   private String _ShrOutputType = "";
            
   /**
    * InvestorClassification member variable.
    */
   private String _InvestorClassification = "";
            
   /**
    * AIFMDInvestorCategory member variable.
    */
   private String _AIFMDInvestorCategory = "";
            
   /**
    * AggrType member variable.
    */
   private String _AggrType = "";
            

   /**
    * Constructs the AcctUpdRequest object.
    * 
    */
   AcctUpdRequest()
   {
      super ( 76 );
   }

   /**
    * Constructs the AcctUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AcctUpdRequest( String hostEncoding )
   {
      super ( 76, hostEncoding );
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
    * Sets the Account Number Manual field for the request.
    * 
    * @param value  Value that the Account Number Manual will be set to.
    */
   public final void setAccountNumManual( Boolean value )
   {
      assertUnsent();
      _AccountNumManual = value;
   }
	
   /**
    * Sets the Alternate Account Number field for the request.
    * 
    * @param value  Value that the Alternate Account Number will be set to.
    */
   public final void setAltAccount( String value )
   {
      assertUnsent();
      _AltAccount = value;
   }
	
   /**
    * Sets the Account Type Code field for the request.
    * 
    * @param value  Value that the Account Type Code will be set to.
    */
   public final void setAcctType( String value )
   {
      assertUnsent();
      _AcctType = value;
   }
	
   /**
    * Sets the Tax Type field for the request.
    * 
    * @param value  Value that the Tax Type will be set to.
    */
   public final void setTaxType( String value )
   {
      assertUnsent();
      _TaxType = value;
   }
	
   /**
    * Sets the Recipient Type field for the request.
    * 
    * @param value  Value that the Recipient Type will be set to.
    */
   public final void setRecipientType( String value )
   {
      assertUnsent();
      _RecipientType = value;
   }
	
   /**
    * Sets the Currency Code field for the request.
    * 
    * @param value  Value that the Currency Code will be set to.
    */
   public final void setCurrency( String value )
   {
      assertUnsent();
      _Currency = value;
   }
	
   /**
    * Sets the Cross Reference Number field for the request.
    * 
    * @param value  Value that the Cross Reference Number will be set to.
    */
   public final void setXrefNum( String value )
   {
      assertUnsent();
      _XrefNum = value;
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
    * Sets the Sales Rep Code field for the request.
    * 
    * @param value  Value that the Sales Rep Code will be set to.
    */
   public final void setSalesRepCode( String value )
   {
      assertUnsent();
      _SalesRepCode = value;
   }
	
   /**
    * Sets the Intermediary Code field for the request.
    * 
    * @param value  Value that the Intermediary Code will be set to.
    */
   public final void setInterCode( String value )
   {
      assertUnsent();
      _InterCode = value;
   }
	
   /**
    * Sets the Intermediary Account Number field for the request.
    * 
    * @param value  Value that the Intermediary Account Number will be set to.
    */
   public final void setInterAccount( String value )
   {
      assertUnsent();
      _InterAccount = value;
   }
	
   /**
    * Sets the Account Status field for the request.
    * 
    * @param value  Value that the Account Status will be set to.
    */
   public final void setAcctStatus( String value )
   {
      assertUnsent();
      _AcctStatus = value;
   }
	
   /**
    * Sets the Date of Registration field for the request.
    * 
    * @param value  Value that the Date of Registration will be set to.
    */
   public final void setDateofReg( Date value )
   {
      assertUnsent();
      _DateofReg = value;
   }
	
   /**
    * Sets the RRSP Fee Indicator field for the request.
    * 
    * @param value  Value that the RRSP Fee Indicator will be set to.
    */
   public final void setRRSPFee( String value )
   {
      assertUnsent();
      _RRSPFee = value;
   }
	
   /**
    * Sets the Pension Jurisdiction field for the request.
    * 
    * @param value  Value that the Pension Jurisdiction will be set to.
    */
   public final void setPensionJuris( String value )
   {
      assertUnsent();
      _PensionJuris = value;
   }
	
   /**
    * Sets the Stop Purchase field for the request.
    * 
    * @param value  Value that the Stop Purchase will be set to.
    */
   public final void setStopPur( Boolean value )
   {
      assertUnsent();
      _StopPur = value;
   }
	
   /**
    * Sets the Stop Transfer In field for the request.
    * 
    * @param value  Value that the Stop Transfer In will be set to.
    */
   public final void setStopXferIn( Boolean value )
   {
      assertUnsent();
      _StopXferIn = value;
   }
	
   /**
    * Sets the Stop Transfer Out field for the request.
    * 
    * @param value  Value that the Stop Transfer Out will be set to.
    */
   public final void setStopXferOut( Boolean value )
   {
      assertUnsent();
      _StopXferOut = value;
   }
	
   /**
    * Sets the Stop Redemption field for the request.
    * 
    * @param value  Value that the Stop Redemption will be set to.
    */
   public final void setStopRed( Boolean value )
   {
      assertUnsent();
      _StopRed = value;
   }
	
   /**
    * Sets the Fee Waived field for the request.
    * 
    * @param value  Value that the Fee Waived will be set to.
    */
   public final void setFeeWaived( Boolean value )
   {
      assertUnsent();
      _FeeWaived = value;
   }
	
   /**
    * Sets the Market Mailing field for the request.
    * 
    * @param value  Value that the Market Mailing will be set to.
    */
   public final void setMarketMail( Boolean value )
   {
      assertUnsent();
      _MarketMail = value;
   }
	
   /**
    * Sets the Market Mailing Change Shareholder field for the request.
    * 
    * @param value  Value that the Market Mailing Change Shareholder will be set to.
    */
   public final void setMarketMailChgSh( Boolean value )
   {
      assertUnsent();
      _MarketMailChgSh = value;
   }
	
   /**
    * Sets the Unseizable field for the request.
    * 
    * @param value  Value that the Unseizable will be set to.
    */
   public final void setUnseizable( Boolean value )
   {
      assertUnsent();
      _Unseizable = value;
   }
	
   /**
    * Sets the Registration Completed field for the request.
    * 
    * @param value  Value that the Registration Completed will be set to.
    */
   public final void setRegCompleted( Boolean value )
   {
      assertUnsent();
      _RegCompleted = value;
   }
	
   /**
    * Sets the Suppress All Confirm field for the request.
    * 
    * @param value  Value that the Suppress All Confirm will be set to.
    */
   public final void setSupConf( Boolean value )
   {
      assertUnsent();
      _SupConf = value;
   }
	
   /**
    * Sets the Suppress Employee Confirm field for the request.
    * 
    * @param value  Value that the Suppress Employee Confirm will be set to.
    */
   public final void setSupEmpConf( Boolean value )
   {
      assertUnsent();
      _SupEmpConf = value;
   }
	
   /**
    * Sets the In Trust For field for the request.
    * 
    * @param value  Value that the In Trust For will be set to.
    */
   public final void setInTrustFor( Boolean value )
   {
      assertUnsent();
      _InTrustFor = value;
   }
	
   /**
    * Sets the Escrow field for the request.
    * 
    * @param value  Value that the Escrow will be set to.
    */
   public final void setEscrow( Boolean value )
   {
      assertUnsent();
      _Escrow = value;
   }
	
   /**
    * Sets the Group Code field for the request.
    * 
    * @param value  Value that the Group Code will be set to.
    */
   public final void setGroupCode( String value )
   {
      assertUnsent();
      _GroupCode = value;
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
    * Sets the Acct Table Version Number field for the request.
    * 
    * @param value  Value that the Acct Table Version Number will be set to.
    */
   public final void setAcctMstrVer( Integer value )
   {
      assertUnsent();
      _AcctMstrVer = value;
   }
	
   /**
    * Sets the Create SalesRep field for the request.
    * 
    * @param value  Value that the Create SalesRep will be set to.
    */
   public final void setCreateRep( Boolean value )
   {
      assertUnsent();
      _CreateRep = value;
   }
	
   /**
    * Sets the Employee field for the request.
    * 
    * @param value  Value that the Employee will be set to.
    */
   public final void setEmployee( String value )
   {
      assertUnsent();
      _Employee = value;
   }
	
   /**
    * Sets the Social Code field for the request.
    * 
    * @param value  Value that the Social Code will be set to.
    */
   public final void setSocialCode( String value )
   {
      assertUnsent();
      _SocialCode = value;
   }
	
   /**
    * Sets the Stop Foreign Content Rebalancing field for the request.
    * 
    * @param value  Value that the Stop Foreign Content Rebalancing will be set to.
    */
   public final void setStopFCRebal( Boolean value )
   {
      assertUnsent();
      _StopFCRebal = value;
   }
	
   /**
    * Sets the GST Exempt field for the request.
    * 
    * @param value  Value that the GST Exempt will be set to.
    */
   public final void setGSTExempt( Boolean value )
   {
      assertUnsent();
      _GSTExempt = value;
   }
	
   /**
    * Sets the Apply PST field for the request.
    * 
    * @param value  Value that the Apply PST will be set to.
    */
   public final void setApplyPST( Boolean value )
   {
      assertUnsent();
      _ApplyPST = value;
   }
	
   /**
    * Sets the Stop SWP field for the request.
    * 
    * @param value  Value that the Stop SWP will be set to.
    */
   public final void setStopSWP( Boolean value )
   {
      assertUnsent();
      _StopSWP = value;
   }
	
   /**
    * Sets the Bank Charge field for the request.
    * 
    * @param value  Value that the Bank Charge will be set to.
    */
   public final void setBankCharge( String value )
   {
      assertUnsent();
      _BankCharge = value;
   }
	
   /**
    * Sets the Consolidation EFT field for the request.
    * 
    * @param value  Value that the Consolidation EFT will be set to.
    */
   public final void setConsolidEFT( String value )
   {
      assertUnsent();
      _ConsolidEFT = value;
   }
	
   /**
    * Sets the Management Fee Option field for the request.
    * 
    * @param value  Value that the Management Fee Option will be set to.
    */
   public final void setMgmtFeePayOption( String value )
   {
      assertUnsent();
      _MgmtFeePayOption = value;
   }
	
   /**
    * Sets the Early Redemption Fees will be charged field for the request.
    * 
    * @param value  Value that the Early Redemption Fees will be charged will be set to.
    */
   public final void setChargeERFee( Boolean value )
   {
      assertUnsent();
      _ChargeERFee = value;
   }
	
   /**
    * Sets the Short Term Transfer Fees will be charged field for the request.
    * 
    * @param value  Value that the Short Term Transfer Fees will be charged will be set to.
    */
   public final void setChargeSTTRFee( Boolean value )
   {
      assertUnsent();
      _ChargeSTTRFee = value;
   }
	
   /**
    * Sets the StopAMSRebal field for the request.
    * 
    * @param value  Value that the StopAMSRebal will be set to.
    */
   public final void setStopAMSRebal( Boolean value )
   {
      assertUnsent();
      _StopAMSRebal = value;
   }
	
   /**
    * Sets the Account Purpose field for the request.
    * 
    * @param value  Value that the Account Purpose will be set to.
    */
   public final void setAcctPurpose( String value )
   {
      assertUnsent();
      _AcctPurpose = value;
   }
	
   /**
    * Sets the Additional Information field for the request.
    * 
    * @param value  Value that the Additional Information will be set to.
    */
   public final void setAdditionalInfo( String value )
   {
      assertUnsent();
      _AdditionalInfo = value;
   }
	
   /**
    * Sets the Business Number field for the request.
    * 
    * @param value  Value that the Business Number will be set to.
    */
   public final void setBusinessNo( String value )
   {
      assertUnsent();
      _BusinessNo = value;
   }
	
   /**
    * Sets the Memorable Place field for the request.
    * 
    * @param value  Value that the Memorable Place will be set to.
    */
   public final void setMemorablePlace( String value )
   {
      assertUnsent();
      _MemorablePlace = value;
   }
	
   /**
    * Sets the Memorable Word field for the request.
    * 
    * @param value  Value that the Memorable Word will be set to.
    */
   public final void setMemorableWord( String value )
   {
      assertUnsent();
      _MemorableWord = value;
   }
	
   /**
    * Sets the MemorableDate field for the request.
    * 
    * @param value  Value that the MemorableDate will be set to.
    */
   public final void setMemorableDate( Date value )
   {
      assertUnsent();
      _MemorableDate = value;
   }
	
   /**
    * Sets the PensionLeg Code field for the request.
    * 
    * @param value  Value that the PensionLeg Code will be set to.
    */
   public final void setPensionLegCode( String value )
   {
      assertUnsent();
      _PensionLegCode = value;
   }
	
   /**
    * Sets the Tel/Fax Agreement field for the request.
    * 
    * @param value  Value that the Tel/Fax Agreement will be set to.
    */
   public final void setTelFaxAgreement( Boolean value )
   {
      assertUnsent();
      _TelFaxAgreement = value;
   }
	
   /**
    * Sets the Clearing Id field for the request.
    * 
    * @param value  Value that the Clearing Id will be set to.
    */
   public final void setClearingId( String value )
   {
      assertUnsent();
      _ClearingId = value;
   }
	
   /**
    * Sets the NetworkControlInd field for the request.
    * 
    * @param value  Value that the NetworkControlInd will be set to.
    */
   public final void setNetworkControlInd( String value )
   {
      assertUnsent();
      _NetworkControlInd = value;
   }
	
   /**
    * Sets the Stop Redemption from Settlement field for the request.
    * 
    * @param value  Value that the Stop Redemption from Settlement will be set to.
    */
   public final void setStopRedSettle( Boolean value )
   {
      assertUnsent();
      _StopRedSettle = value;
   }
	
   /**
    * Sets the Registration Information field for the request.
    * 
    * @param value  Value that the Registration Information will be set to.
    */
   public final void setRegistrationInfo( String value )
   {
      assertUnsent();
      _RegistrationInfo = value;
   }
	
   /**
    * Sets the Fee Model Code field for the request.
    * 
    * @param value  Value that the Fee Model Code will be set to.
    */
   public final void setFeeModelCode( String value )
   {
      assertUnsent();
      _FeeModelCode = value;
   }
	
   /**
    * Sets the Clearing Firm field for the request.
    * 
    * @param value  Value that the Clearing Firm will be set to.
    */
   public final void setClearingFirm( String value )
   {
      assertUnsent();
      _ClearingFirm = value;
   }
	
   /**
    * Sets the AgentForFirmAgencyCode field for the request.
    * 
    * @param value  Value that the AgentForFirmAgencyCode will be set to.
    */
   public final void setAgentForFirmAgencyCode( String value )
   {
      assertUnsent();
      _AgentForFirmAgencyCode = value;
   }
	
   /**
    * Sets the TPAFirmAgencyCode field for the request.
    * 
    * @param value  Value that the TPAFirmAgencyCode will be set to.
    */
   public final void setTPAFirmAgencyCode( String value )
   {
      assertUnsent();
      _TPAFirmAgencyCode = value;
   }
	
   /**
    * Sets the Network ID field for the request.
    * 
    * @param value  Value that the Network ID will be set to.
    */
   public final void setNetworkID( String value )
   {
      assertUnsent();
      _NetworkID = value;
   }
	
   /**
    * Sets the Consolidation Type for Redemption field for the request.
    * 
    * @param value  Value that the Consolidation Type for Redemption will be set to.
    */
   public final void setConsolTypePW( String value )
   {
      assertUnsent();
      _ConsolTypePW = value;
   }
	
   /**
    * Sets the Consolidation Type for Distribution field for the request.
    * 
    * @param value  Value that the Consolidation Type for Distribution will be set to.
    */
   public final void setConsolTypeID( String value )
   {
      assertUnsent();
      _ConsolTypeID = value;
   }
	
   /**
    * Sets the Account Closing Reason field for the request.
    * 
    * @param value  Value that the Account Closing Reason will be set to.
    */
   public final void setAcctClosingReason( String value )
   {
      assertUnsent();
      _AcctClosingReason = value;
   }
	
   /**
    * Sets the Affluent field for the request.
    * 
    * @param value  Value that the Affluent will be set to.
    */
   public final void setAffluent( String value )
   {
      assertUnsent();
      _Affluent = value;
   }
	
   /**
    * Sets the Hold Dividend Payment field for the request.
    * 
    * @param value  Value that the Hold Dividend Payment will be set to.
    */
   public final void setHoldDivPymt( Boolean value )
   {
      assertUnsent();
      _HoldDivPymt = value;
   }
	
   /**
    * Sets the Dummy Tax Type for Old LIF field for the request.
    * 
    * @param value  Value that the Dummy Tax Type for Old LIF will be set to.
    */
   public final void setTaxTypeSchedule( String value )
   {
      assertUnsent();
      _TaxTypeSchedule = value;
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
    * Sets the Stop Reason Other field for the request.
    * 
    * @param value  Value that the Stop Reason Other will be set to.
    */
   public final void setStopReasonOther( String value )
   {
      assertUnsent();
      _StopReasonOther = value;
   }
	
   /**
    * Sets the Unit Rounding Method field for the request.
    * 
    * @param value  Value that the Unit Rounding Method will be set to.
    */
   public final void setUnitRoundMethod( String value )
   {
      assertUnsent();
      _UnitRoundMethod = value;
   }
	
   /**
    * Sets the Flag if beneficiaries request additional grants. field for the request.
    * 
    * @param value  Value that the Flag if beneficiaries request additional grants. will be set to.
    */
   public final void setSiblingOnly( String value )
   {
      assertUnsent();
      _SiblingOnly = value;
   }
	
   /**
    * Sets the Flag if acccount reporting to HRSDC field for the request.
    * 
    * @param value  Value that the Flag if acccount reporting to HRSDC will be set to.
    */
   public final void setCESGEligible( Boolean value )
   {
      assertUnsent();
      _CESGEligible = value;
   }
	
   /**
    * Sets the Flag if there were contributions made before 1998 field for the request.
    * 
    * @param value  Value that the Flag if there were contributions made before 1998 will be set to.
    */
   public final void setPre98Contrib( Boolean value )
   {
      assertUnsent();
      _Pre98Contrib = value;
   }
	
   /**
    * Sets the Consolidation Type for Purchase field for the request.
    * 
    * @param value  Value that the Consolidation Type for Purchase will be set to.
    */
   public final void setConsolTypeED( String value )
   {
      assertUnsent();
      _ConsolTypeED = value;
   }
	
   /**
    * Sets the ProdPortfolio UUID field for the request.
    * 
    * @param value  Value that the ProdPortfolio UUID will be set to.
    */
   public final void setProdPortfolioUUID( String value )
   {
      assertUnsent();
      _ProdPortfolioUUID = value;
   }
	
   /**
    * Sets the ProdPortfolioPlan UUID field for the request.
    * 
    * @param value  Value that the ProdPortfolioPlan UUID will be set to.
    */
   public final void setProdPortfolioPlanUUID( String value )
   {
      assertUnsent();
      _ProdPortfolioPlanUUID = value;
   }
	
   /**
    * Sets the Date that property is remitted to the government field for the request.
    * 
    * @param value  Value that the Date that property is remitted to the government will be set to.
    */
   public final void setUnclmRemitDate( Date value )
   {
      assertUnsent();
      _UnclmRemitDate = value;
   }
	
   /**
    * Sets the NSCC Social Code field for the request.
    * 
    * @param value  Value that the NSCC Social Code will be set to.
    */
   public final void setNSCSocialCode( String value )
   {
      assertUnsent();
      _NSCSocialCode = value;
   }
	
   /**
    * Sets the Organisation Type field for the request.
    * 
    * @param value  Value that the Organisation Type will be set to.
    */
   public final void setOrgType( String value )
   {
      assertUnsent();
      _OrgType = value;
   }
	
   /**
    * Sets the Sub Organisation Type field for the request.
    * 
    * @param value  Value that the Sub Organisation Type will be set to.
    */
   public final void setSubOrgType( String value )
   {
      assertUnsent();
      _SubOrgType = value;
   }
	
   /**
    * Sets the Account Settlement Currency field for the request.
    * 
    * @param value  Value that the Account Settlement Currency will be set to.
    */
   public final void setSettleCurrency( String value )
   {
      assertUnsent();
      _SettleCurrency = value;
   }
	
   /**
    * Sets the Non Financial Confirm field for the request.
    * 
    * @param value  Value that the Non Financial Confirm will be set to.
    */
   public final void setNonFinConfirm( Boolean value )
   {
      assertUnsent();
      _NonFinConfirm = value;
   }
	
   /**
    * Sets the Stop Adjustment Date field for the request.
    * 
    * @param value  Value that the Stop Adjustment Date will be set to.
    */
   public final void setStopAdjDate( Date value )
   {
      assertUnsent();
      _StopAdjDate = value;
   }
	
   /**
    * Sets the Contract Value Issue Date field for the request.
    * 
    * @param value  Value that the Contract Value Issue Date will be set to.
    */
   public final void setContValIssueDate( Date value )
   {
      assertUnsent();
      _ContValIssueDate = value;
   }
	
   /**
    * Sets the Contract Value Initial Market Value field for the request.
    * 
    * @param value  Value that the Contract Value Initial Market Value will be set to.
    */
   public final void setContValInitMKV( String value )
   {
      assertUnsent();
      _ContValInitMKV = value;
   }
	
   /**
    * Sets the Contract Value Net Transaction Amount field for the request.
    * 
    * @param value  Value that the Contract Value Net Transaction Amount will be set to.
    */
   public final void setContValNetTranAmt( String value )
   {
      assertUnsent();
      _ContValNetTranAmt = value;
   }
	
   /**
    * Sets the Contract Value Net Transaction Date field for the request.
    * 
    * @param value  Value that the Contract Value Net Transaction Date will be set to.
    */
   public final void setContValNetTranDate( Date value )
   {
      assertUnsent();
      _ContValNetTranDate = value;
   }
	
   /**
    * Sets the Shareholder Output Type field for the request.
    * 
    * @param value  Value that the Shareholder Output Type will be set to.
    */
   public final void setShrOutputType( String value )
   {
      assertUnsent();
      _ShrOutputType = value;
   }
	
   /**
    * Sets the InvestorClassification field for the request.
    * 
    * @param value  Value that the InvestorClassification will be set to.
    */
   public final void setInvestorClassification( String value )
   {
      assertUnsent();
      _InvestorClassification = value;
   }
	
   /**
    * Sets the AIFMDInvestorCategory field for the request.
    * 
    * @param value  Value that the AIFMDInvestorCategory will be set to.
    */
   public final void setAIFMDInvestorCategory( String value )
   {
      assertUnsent();
      _AIFMDInvestorCategory = value;
   }
	
   /**
    * Sets the AggrType field for the request.
    * 
    * @param value  Value that the AggrType will be set to.
    */
   public final void setAggrType( String value )
   {
      assertUnsent();
      _AggrType = value;
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
      requestBuffer.appendField( _RunMode );
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _AccountNumManual );
      requestBuffer.appendField( _AltAccount );
      requestBuffer.appendField( _AcctType );
      requestBuffer.appendField( _TaxType );
      requestBuffer.appendField( _RecipientType );
      requestBuffer.appendField( _Currency );
      requestBuffer.appendField( _XrefNum );
      requestBuffer.appendField( _BrokerCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _SalesRepCode );
      requestBuffer.appendField( _InterCode );
      requestBuffer.appendField( _InterAccount );
      requestBuffer.appendField( _AcctStatus );
      requestBuffer.appendField( _DateofReg );
      requestBuffer.appendField( _RRSPFee );
      requestBuffer.appendField( _PensionJuris );
      requestBuffer.appendField( _StopPur );
      requestBuffer.appendField( _StopXferIn );
      requestBuffer.appendField( _StopXferOut );
      requestBuffer.appendField( _StopRed );
      requestBuffer.appendField( _FeeWaived );
      requestBuffer.appendField( _MarketMail );
      requestBuffer.appendField( _MarketMailChgSh );
      requestBuffer.appendField( _Unseizable );
      requestBuffer.appendField( _RegCompleted );
      requestBuffer.appendField( _SupConf );
      requestBuffer.appendField( _SupEmpConf );
      requestBuffer.appendField( _InTrustFor );
      requestBuffer.appendField( _Escrow );
      requestBuffer.appendField( _GroupCode );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _AcctMstrVer );
      requestBuffer.appendField( _CreateRep );
      requestBuffer.appendField( _Employee );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _SocialCode );
      requestBuffer.appendField( _StopFCRebal );
      requestBuffer.appendField( _GSTExempt );
      requestBuffer.appendField( _ApplyPST );
      requestBuffer.appendField( _StopSWP );
      requestBuffer.appendField( _BankCharge );
      requestBuffer.appendField( _ConsolidEFT );
      requestBuffer.appendField( _MgmtFeePayOption );
      requestBuffer.appendField( _ChargeERFee );
      requestBuffer.appendField( _ChargeSTTRFee );
      requestBuffer.appendField( _StopAMSRebal );
      requestBuffer.appendField( _AcctPurpose );
      requestBuffer.appendField( _AdditionalInfo );
      requestBuffer.appendField( _BusinessNo );
      requestBuffer.appendField( _MemorablePlace );
      requestBuffer.appendField( _MemorableWord );
      requestBuffer.appendField( _MemorableDate );
      requestBuffer.appendField( _PensionLegCode );
      requestBuffer.appendField( _TelFaxAgreement );
      requestBuffer.appendField( _ClearingId );
      requestBuffer.appendField( _NetworkControlInd );
      requestBuffer.appendField( _StopRedSettle );
      requestBuffer.appendField( _RegistrationInfo );
      requestBuffer.appendField( _FeeModelCode );
      requestBuffer.appendField( _ClearingFirm );
      requestBuffer.appendField( _AgentForFirmAgencyCode );
      requestBuffer.appendField( _TPAFirmAgencyCode );
      requestBuffer.appendField( _NetworkID );
      requestBuffer.appendField( _ConsolTypePW );
      requestBuffer.appendField( _ConsolTypeID );
      requestBuffer.appendField( _AcctClosingReason );
      requestBuffer.appendField( _Affluent );
      requestBuffer.appendField( _HoldDivPymt );
      requestBuffer.appendField( _TaxTypeSchedule );
      requestBuffer.appendField( _StopReason );
      requestBuffer.appendField( _StopReasonOther );
      requestBuffer.appendField( _UnitRoundMethod );
      requestBuffer.appendField( _SiblingOnly );
      requestBuffer.appendField( _CESGEligible );
      requestBuffer.appendField( _Pre98Contrib );
      requestBuffer.appendField( _ConsolTypeED );
      requestBuffer.appendField( _ProdPortfolioUUID );
      requestBuffer.appendField( _ProdPortfolioPlanUUID );
      requestBuffer.appendField( _UnclmRemitDate );
      requestBuffer.appendField( _NSCSocialCode );
      requestBuffer.appendField( _OrgType );
      requestBuffer.appendField( _SubOrgType );
      requestBuffer.appendField( _SettleCurrency );
      requestBuffer.appendField( _NonFinConfirm );
      requestBuffer.appendField( _StopAdjDate );
      requestBuffer.appendField( _ContValIssueDate );
      requestBuffer.appendField( _ContValInitMKV );
      requestBuffer.appendField( _ContValNetTranAmt );
      requestBuffer.appendField( _ContValNetTranDate );
      requestBuffer.appendField( _ShrOutputType );
      requestBuffer.appendField( _InvestorClassification );
      requestBuffer.appendField( _AIFMDInvestorCategory );
      requestBuffer.appendField( _AggrType );
   }

}

