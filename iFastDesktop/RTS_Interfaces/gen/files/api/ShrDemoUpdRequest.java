// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shareholder Demographic Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/ShrDemoUpd.doc">ShrDemoUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrDemoUpdRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Marital Code member variable.
    */
   private String _MaritalCode = "";
            
   /**
    * Employer Name member variable.
    */
   private String _Employer = "";
            
   /**
    * Employed Years member variable.
    */
   private String _EmployedYrs = "0";
            
   /**
    * Industry Code member variable.
    */
   private String _IndustryCode = "";
            
   /**
    * Occupational Code member variable.
    */
   private String _OccupationCode = "";
            
   /**
    * Annual Income Code member variable.
    */
   private String _AnnualIncomeCode = "";
            
   /**
    * Net Worth Code member variable.
    */
   private String _NetWorthCode = "";
            
   /**
    * Investment Objective Code member variable.
    */
   private String _InvObjCode = "";
            
   /**
    * Investment Knowledge Code member variable.
    */
   private String _InvKnowledgeCode = "";
            
   /**
    * Investment Horizon Code member variable.
    */
   private String _InvHorizonCode = "";
            
   /**
    * Risk Tolerance Code member variable.
    */
   private String _RiskToleranceCode = "";
            
   /**
    * Other Investments member variable.
    */
   private Boolean _OtherInvestments = new Boolean(false);
            
   /**
    * Advisor Code member variable.
    */
   private String _AdvisorCode = "";
            
   /**
    * Witness Name member variable.
    */
   private String _WitnessName = "";
            
   /**
    * Witness Address1 member variable.
    */
   private String _WitnessAddr1 = "";
            
   /**
    * Witness Address2 member variable.
    */
   private String _WitnessAddr2 = "";
            
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * Personal Security Code member variable.
    */
   private String _PersonalSecCode = "";
            
   /**
    * Shareholder Table Version Number member variable.
    */
   private Integer _PrimMstrVer = null;
            
   /**
    * Record Creation Date member variable.
    */
   private Date _ProcessDate = null;
            
            
            
   /**
    * Investment Philosophy member variable.
    */
   private String _InvestPhilosophy = "";
            
   /**
    * Occupation Code member variable.
    */
   private String _Occupation = "";
            
   /**
    * Growth Percent member variable.
    */
   private Integer _GrowthPercent = null;
            
   /**
    * Income Percent member variable.
    */
   private Integer _IncomePercent = null;
            
   /**
    * Safety Percent member variable.
    */
   private Integer _SafetyPercent = null;
            
   /**
    * Branch the representative  sells from member variable.
    */
   private String _RepBranch = "";
            
   /**
    * Representative Number who changed KYC Info member variable.
    */
   private Integer _RepNo = null;
            
   /**
    * SAM Financial Health member variable.
    */
   private String _SAMFInHealth = "";
            
   /**
    * TypeOfBusFreeFormat member variable.
    */
   private String _TypeOfBusFreeFormat = "";
            
   /**
    * Account Process Date member variable.
    */
   private Date _AcctProcessDate = null;
            
   /**
    * Account Rep Branch member variable.
    */
   private String _AcctRepBranch = "";
            
   /**
    * Account Rep No member variable.
    */
   private Integer _AcctRepNo = null;
            
   /**
    * AcctKYCVer member variable.
    */
   private Integer _AcctKYCVer = null;
            
   /**
    * Memorable Place member variable.
    */
   private String _MemorablePlace = "";
            
   /**
    * Memorable Word member variable.
    */
   private String _MemorableWord = "";
            
   /**
    * Memorable Date member variable.
    */
   private Date _MemorableDate = null;
            
   /**
    * Account KYC AgencyCode member variable.
    */
   private String _KYCAgencyCode = "";
            
   /**
    * Account KYC Branch member variable.
    */
   private String _KYCBranch = "";
            
   /**
    * Account KYC AgentCode member variable.
    */
   private String _KYCAgentCode = "";
            
   /**
    * KYC Comment member variable.
    */
   private String _KYCComment = "";
            
   /**
    * Employment Type member variable.
    */
   private String _EmploymentType = "";
            
   /**
    * Residence Type member variable.
    */
   private String _ResidenceType = "";
            
   /**
    * ResAmount member variable.
    */
   private String _ResAmount = "0";
            
   /**
    * KYC Mailed Date member variable.
    */
   private Date _KYCMailedDate = null;
            
   /**
    * Annual Income Amount member variable.
    */
   private String _AnnualIncomeAmt = "0";
            
   /**
    * Income Level Date member variable.
    */
   private Date _IncomeLevelDate = null;
            
   /**
    * Net Worth Amount member variable.
    */
   private String _NetWorthAmt = "0";
            
   /**
    * Net Worth Date member variable.
    */
   private Date _NetWorthDate = null;
            
   /**
    * Refferal Code member variable.
    */
   private String _RefferalCode = "";
            
   /**
    * Reference Name member variable.
    */
   private String _ReferenceName = "";
            
   /**
    * Specialty Code member variable.
    */
   private String _SpecialtyCode = "";
            
   /**
    * Tolerance Percentage member variable.
    */
   private String _TolerancePrcnt = "0";
            
   /**
    * Short Term Percentage member variable.
    */
   private String _ShortTermPrcnt = "0";
            
   /**
    * Aggressive Percentage member variable.
    */
   private String _AggressivePrcnt = "0";
            
   /**
    * Percentage Date member variable.
    */
   private Date _PrcntDate = null;
            
   /**
    * ShrKYCVer member variable.
    */
   private Integer _ShrKYCVer = null;
            
   /**
    * Investor Type member variable.
    */
   private String _InvestorType = "";
            
   /**
    * Invest on behalf of 3rd Party member variable.
    */
   private String _InvestFor3rdPrty = "";
            
   /**
    * Country where business is conducted member variable.
    */
   private String _BusCntryCode = "";
            
   /**
    * Initial payment member variable.
    */
   private String _OpenAcctPymn = "";
            
   /**
    * Source of Funds Identified member variable.
    */
   private String _FundScrlIdentified = "";
            
   /**
    * Power of attorney member variable.
    */
   private String _PowOfAtt = "";
            
   /**
    * Compliance Code member variable.
    */
   private String _ClientComplyCode = "";
            
   /**
    * ID of the Regulatory Standard member variable.
    */
   private String _ComplyCodeID = "";
            
   /**
    * Entity ID member variable.
    */
   private String _EntityID = "0";
            
   /**
    * Number Of Dependants member variable.
    */
   private Integer _NumOfDependants = null;
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName1 = "";
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName2 = "";
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName3 = "";
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName4 = "";
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName5 = "";
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName6 = "";
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName7 = "";
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName8 = "";
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName9 = "";
            
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName10 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp1 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp2 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp3 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp4 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp5 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp6 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp7 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp8 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp9 = "";
            
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp10 = "";
            
   /**
    * Suppress KYC Letter member variable.
    */
   private Boolean _SuppressKYCLetter = new Boolean(false);
            
   /**
    * KYC Information format code member variable.
    */
   private String _KYCInfoFormatCode = "";
            
   /**
    * Profile Number member variable.
    */
   private String _ProfileNum = "";
            
   /**
    * Reference Number member variable.
    */
   private String _RefNumber = "";
            
   /**
    * Profile Value member variable.
    */
   private String _ProfileVal = "";
            
   /**
    * KYC Last Review Date member variable.
    */
   private Date _LastReviewDate = null;
            
   /**
    * SolicitPublicContrib member variable.
    */
   private String _SolicitPublicContrib = "";
            
   /**
    * InvReason member variable.
    */
   private String _InvReason = "";
            

   /**
    * Constructs the ShrDemoUpdRequest object.
    * 
    */
   ShrDemoUpdRequest()
   {
      super ( 81 );
   }

   /**
    * Constructs the ShrDemoUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShrDemoUpdRequest( String hostEncoding )
   {
      super ( 81, hostEncoding );
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
    * Sets the Marital Code field for the request.
    * 
    * @param value  Value that the Marital Code will be set to.
    */
   public final void setMaritalCode( String value )
   {
      assertUnsent();
      _MaritalCode = value;
   }
	
   /**
    * Sets the Employer Name field for the request.
    * 
    * @param value  Value that the Employer Name will be set to.
    */
   public final void setEmployer( String value )
   {
      assertUnsent();
      _Employer = value;
   }
	
   /**
    * Sets the Employed Years field for the request.
    * 
    * @param value  Value that the Employed Years will be set to.
    */
   public final void setEmployedYrs( String value )
   {
      assertUnsent();
      _EmployedYrs = value;
   }
	
   /**
    * Sets the Industry Code field for the request.
    * 
    * @param value  Value that the Industry Code will be set to.
    */
   public final void setIndustryCode( String value )
   {
      assertUnsent();
      _IndustryCode = value;
   }
	
   /**
    * Sets the Occupational Code field for the request.
    * 
    * @param value  Value that the Occupational Code will be set to.
    */
   public final void setOccupationCode( String value )
   {
      assertUnsent();
      _OccupationCode = value;
   }
	
   /**
    * Sets the Annual Income Code field for the request.
    * 
    * @param value  Value that the Annual Income Code will be set to.
    */
   public final void setAnnualIncomeCode( String value )
   {
      assertUnsent();
      _AnnualIncomeCode = value;
   }
	
   /**
    * Sets the Net Worth Code field for the request.
    * 
    * @param value  Value that the Net Worth Code will be set to.
    */
   public final void setNetWorthCode( String value )
   {
      assertUnsent();
      _NetWorthCode = value;
   }
	
   /**
    * Sets the Investment Objective Code field for the request.
    * 
    * @param value  Value that the Investment Objective Code will be set to.
    */
   public final void setInvObjCode( String value )
   {
      assertUnsent();
      _InvObjCode = value;
   }
	
   /**
    * Sets the Investment Knowledge Code field for the request.
    * 
    * @param value  Value that the Investment Knowledge Code will be set to.
    */
   public final void setInvKnowledgeCode( String value )
   {
      assertUnsent();
      _InvKnowledgeCode = value;
   }
	
   /**
    * Sets the Investment Horizon Code field for the request.
    * 
    * @param value  Value that the Investment Horizon Code will be set to.
    */
   public final void setInvHorizonCode( String value )
   {
      assertUnsent();
      _InvHorizonCode = value;
   }
	
   /**
    * Sets the Risk Tolerance Code field for the request.
    * 
    * @param value  Value that the Risk Tolerance Code will be set to.
    */
   public final void setRiskToleranceCode( String value )
   {
      assertUnsent();
      _RiskToleranceCode = value;
   }
	
   /**
    * Sets the Other Investments field for the request.
    * 
    * @param value  Value that the Other Investments will be set to.
    */
   public final void setOtherInvestments( Boolean value )
   {
      assertUnsent();
      _OtherInvestments = value;
   }
	
   /**
    * Sets the Advisor Code field for the request.
    * 
    * @param value  Value that the Advisor Code will be set to.
    */
   public final void setAdvisorCode( String value )
   {
      assertUnsent();
      _AdvisorCode = value;
   }
	
   /**
    * Sets the Witness Name field for the request.
    * 
    * @param value  Value that the Witness Name will be set to.
    */
   public final void setWitnessName( String value )
   {
      assertUnsent();
      _WitnessName = value;
   }
	
   /**
    * Sets the Witness Address1 field for the request.
    * 
    * @param value  Value that the Witness Address1 will be set to.
    */
   public final void setWitnessAddr1( String value )
   {
      assertUnsent();
      _WitnessAddr1 = value;
   }
	
   /**
    * Sets the Witness Address2 field for the request.
    * 
    * @param value  Value that the Witness Address2 will be set to.
    */
   public final void setWitnessAddr2( String value )
   {
      assertUnsent();
      _WitnessAddr2 = value;
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
    * Sets the Personal Security Code field for the request.
    * 
    * @param value  Value that the Personal Security Code will be set to.
    */
   public final void setPersonalSecCode( String value )
   {
      assertUnsent();
      _PersonalSecCode = value;
   }
	
   /**
    * Sets the Shareholder Table Version Number field for the request.
    * 
    * @param value  Value that the Shareholder Table Version Number will be set to.
    */
   public final void setPrimMstrVer( Integer value )
   {
      assertUnsent();
      _PrimMstrVer = value;
   }
	
   /**
    * Sets the Record Creation Date field for the request.
    * 
    * @param value  Value that the Record Creation Date will be set to.
    */
   public final void setProcessDate( Date value )
   {
      assertUnsent();
      _ProcessDate = value;
   }
	
   /**
    * Sets the Investment Philosophy field for the request.
    * 
    * @param value  Value that the Investment Philosophy will be set to.
    */
   public final void setInvestPhilosophy( String value )
   {
      assertUnsent();
      _InvestPhilosophy = value;
   }
	
   /**
    * Sets the Occupation Code field for the request.
    * 
    * @param value  Value that the Occupation Code will be set to.
    */
   public final void setOccupation( String value )
   {
      assertUnsent();
      _Occupation = value;
   }
	
   /**
    * Sets the Growth Percent field for the request.
    * 
    * @param value  Value that the Growth Percent will be set to.
    */
   public final void setGrowthPercent( Integer value )
   {
      assertUnsent();
      _GrowthPercent = value;
   }
	
   /**
    * Sets the Income Percent field for the request.
    * 
    * @param value  Value that the Income Percent will be set to.
    */
   public final void setIncomePercent( Integer value )
   {
      assertUnsent();
      _IncomePercent = value;
   }
	
   /**
    * Sets the Safety Percent field for the request.
    * 
    * @param value  Value that the Safety Percent will be set to.
    */
   public final void setSafetyPercent( Integer value )
   {
      assertUnsent();
      _SafetyPercent = value;
   }
	
   /**
    * Sets the Branch the representative  sells from field for the request.
    * 
    * @param value  Value that the Branch the representative  sells from will be set to.
    */
   public final void setRepBranch( String value )
   {
      assertUnsent();
      _RepBranch = value;
   }
	
   /**
    * Sets the Representative Number who changed KYC Info field for the request.
    * 
    * @param value  Value that the Representative Number who changed KYC Info will be set to.
    */
   public final void setRepNo( Integer value )
   {
      assertUnsent();
      _RepNo = value;
   }
	
   /**
    * Sets the SAM Financial Health field for the request.
    * 
    * @param value  Value that the SAM Financial Health will be set to.
    */
   public final void setSAMFInHealth( String value )
   {
      assertUnsent();
      _SAMFInHealth = value;
   }
	
   /**
    * Sets the TypeOfBusFreeFormat field for the request.
    * 
    * @param value  Value that the TypeOfBusFreeFormat will be set to.
    */
   public final void setTypeOfBusFreeFormat( String value )
   {
      assertUnsent();
      _TypeOfBusFreeFormat = value;
   }
	
   /**
    * Sets the Account Process Date field for the request.
    * 
    * @param value  Value that the Account Process Date will be set to.
    */
   public final void setAcctProcessDate( Date value )
   {
      assertUnsent();
      _AcctProcessDate = value;
   }
	
   /**
    * Sets the Account Rep Branch field for the request.
    * 
    * @param value  Value that the Account Rep Branch will be set to.
    */
   public final void setAcctRepBranch( String value )
   {
      assertUnsent();
      _AcctRepBranch = value;
   }
	
   /**
    * Sets the Account Rep No field for the request.
    * 
    * @param value  Value that the Account Rep No will be set to.
    */
   public final void setAcctRepNo( Integer value )
   {
      assertUnsent();
      _AcctRepNo = value;
   }
	
   /**
    * Sets the AcctKYCVer field for the request.
    * 
    * @param value  Value that the AcctKYCVer will be set to.
    */
   public final void setAcctKYCVer( Integer value )
   {
      assertUnsent();
      _AcctKYCVer = value;
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
    * Sets the Memorable Date field for the request.
    * 
    * @param value  Value that the Memorable Date will be set to.
    */
   public final void setMemorableDate( Date value )
   {
      assertUnsent();
      _MemorableDate = value;
   }
	
   /**
    * Sets the Account KYC AgencyCode field for the request.
    * 
    * @param value  Value that the Account KYC AgencyCode will be set to.
    */
   public final void setKYCAgencyCode( String value )
   {
      assertUnsent();
      _KYCAgencyCode = value;
   }
	
   /**
    * Sets the Account KYC Branch field for the request.
    * 
    * @param value  Value that the Account KYC Branch will be set to.
    */
   public final void setKYCBranch( String value )
   {
      assertUnsent();
      _KYCBranch = value;
   }
	
   /**
    * Sets the Account KYC AgentCode field for the request.
    * 
    * @param value  Value that the Account KYC AgentCode will be set to.
    */
   public final void setKYCAgentCode( String value )
   {
      assertUnsent();
      _KYCAgentCode = value;
   }
	
   /**
    * Sets the KYC Comment field for the request.
    * 
    * @param value  Value that the KYC Comment will be set to.
    */
   public final void setKYCComment( String value )
   {
      assertUnsent();
      _KYCComment = value;
   }
	
   /**
    * Sets the Employment Type field for the request.
    * 
    * @param value  Value that the Employment Type will be set to.
    */
   public final void setEmploymentType( String value )
   {
      assertUnsent();
      _EmploymentType = value;
   }
	
   /**
    * Sets the Residence Type field for the request.
    * 
    * @param value  Value that the Residence Type will be set to.
    */
   public final void setResidenceType( String value )
   {
      assertUnsent();
      _ResidenceType = value;
   }
	
   /**
    * Sets the ResAmount field for the request.
    * 
    * @param value  Value that the ResAmount will be set to.
    */
   public final void setResAmount( String value )
   {
      assertUnsent();
      _ResAmount = value;
   }
	
   /**
    * Sets the KYC Mailed Date field for the request.
    * 
    * @param value  Value that the KYC Mailed Date will be set to.
    */
   public final void setKYCMailedDate( Date value )
   {
      assertUnsent();
      _KYCMailedDate = value;
   }
	
   /**
    * Sets the Annual Income Amount field for the request.
    * 
    * @param value  Value that the Annual Income Amount will be set to.
    */
   public final void setAnnualIncomeAmt( String value )
   {
      assertUnsent();
      _AnnualIncomeAmt = value;
   }
	
   /**
    * Sets the Income Level Date field for the request.
    * 
    * @param value  Value that the Income Level Date will be set to.
    */
   public final void setIncomeLevelDate( Date value )
   {
      assertUnsent();
      _IncomeLevelDate = value;
   }
	
   /**
    * Sets the Net Worth Amount field for the request.
    * 
    * @param value  Value that the Net Worth Amount will be set to.
    */
   public final void setNetWorthAmt( String value )
   {
      assertUnsent();
      _NetWorthAmt = value;
   }
	
   /**
    * Sets the Net Worth Date field for the request.
    * 
    * @param value  Value that the Net Worth Date will be set to.
    */
   public final void setNetWorthDate( Date value )
   {
      assertUnsent();
      _NetWorthDate = value;
   }
	
   /**
    * Sets the Refferal Code field for the request.
    * 
    * @param value  Value that the Refferal Code will be set to.
    */
   public final void setRefferalCode( String value )
   {
      assertUnsent();
      _RefferalCode = value;
   }
	
   /**
    * Sets the Reference Name field for the request.
    * 
    * @param value  Value that the Reference Name will be set to.
    */
   public final void setReferenceName( String value )
   {
      assertUnsent();
      _ReferenceName = value;
   }
	
   /**
    * Sets the Specialty Code field for the request.
    * 
    * @param value  Value that the Specialty Code will be set to.
    */
   public final void setSpecialtyCode( String value )
   {
      assertUnsent();
      _SpecialtyCode = value;
   }
	
   /**
    * Sets the Tolerance Percentage field for the request.
    * 
    * @param value  Value that the Tolerance Percentage will be set to.
    */
   public final void setTolerancePrcnt( String value )
   {
      assertUnsent();
      _TolerancePrcnt = value;
   }
	
   /**
    * Sets the Short Term Percentage field for the request.
    * 
    * @param value  Value that the Short Term Percentage will be set to.
    */
   public final void setShortTermPrcnt( String value )
   {
      assertUnsent();
      _ShortTermPrcnt = value;
   }
	
   /**
    * Sets the Aggressive Percentage field for the request.
    * 
    * @param value  Value that the Aggressive Percentage will be set to.
    */
   public final void setAggressivePrcnt( String value )
   {
      assertUnsent();
      _AggressivePrcnt = value;
   }
	
   /**
    * Sets the Percentage Date field for the request.
    * 
    * @param value  Value that the Percentage Date will be set to.
    */
   public final void setPrcntDate( Date value )
   {
      assertUnsent();
      _PrcntDate = value;
   }
	
   /**
    * Sets the ShrKYCVer field for the request.
    * 
    * @param value  Value that the ShrKYCVer will be set to.
    */
   public final void setShrKYCVer( Integer value )
   {
      assertUnsent();
      _ShrKYCVer = value;
   }
	
   /**
    * Sets the Investor Type field for the request.
    * 
    * @param value  Value that the Investor Type will be set to.
    */
   public final void setInvestorType( String value )
   {
      assertUnsent();
      _InvestorType = value;
   }
	
   /**
    * Sets the Invest on behalf of 3rd Party field for the request.
    * 
    * @param value  Value that the Invest on behalf of 3rd Party will be set to.
    */
   public final void setInvestFor3rdPrty( String value )
   {
      assertUnsent();
      _InvestFor3rdPrty = value;
   }
	
   /**
    * Sets the Country where business is conducted field for the request.
    * 
    * @param value  Value that the Country where business is conducted will be set to.
    */
   public final void setBusCntryCode( String value )
   {
      assertUnsent();
      _BusCntryCode = value;
   }
	
   /**
    * Sets the Initial payment field for the request.
    * 
    * @param value  Value that the Initial payment will be set to.
    */
   public final void setOpenAcctPymn( String value )
   {
      assertUnsent();
      _OpenAcctPymn = value;
   }
	
   /**
    * Sets the Source of Funds Identified field for the request.
    * 
    * @param value  Value that the Source of Funds Identified will be set to.
    */
   public final void setFundScrlIdentified( String value )
   {
      assertUnsent();
      _FundScrlIdentified = value;
   }
	
   /**
    * Sets the Power of attorney field for the request.
    * 
    * @param value  Value that the Power of attorney will be set to.
    */
   public final void setPowOfAtt( String value )
   {
      assertUnsent();
      _PowOfAtt = value;
   }
	
   /**
    * Sets the Compliance Code field for the request.
    * 
    * @param value  Value that the Compliance Code will be set to.
    */
   public final void setClientComplyCode( String value )
   {
      assertUnsent();
      _ClientComplyCode = value;
   }
	
   /**
    * Sets the ID of the Regulatory Standard field for the request.
    * 
    * @param value  Value that the ID of the Regulatory Standard will be set to.
    */
   public final void setComplyCodeID( String value )
   {
      assertUnsent();
      _ComplyCodeID = value;
   }
	
   /**
    * Sets the Entity ID field for the request.
    * 
    * @param value  Value that the Entity ID will be set to.
    */
   public final void setEntityID( String value )
   {
      assertUnsent();
      _EntityID = value;
   }
	
   /**
    * Sets the Number Of Dependants field for the request.
    * 
    * @param value  Value that the Number Of Dependants will be set to.
    */
   public final void setNumOfDependants( Integer value )
   {
      assertUnsent();
      _NumOfDependants = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName1( String value )
   {
      assertUnsent();
      _AssociateCorpName1 = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName2( String value )
   {
      assertUnsent();
      _AssociateCorpName2 = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName3( String value )
   {
      assertUnsent();
      _AssociateCorpName3 = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName4( String value )
   {
      assertUnsent();
      _AssociateCorpName4 = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName5( String value )
   {
      assertUnsent();
      _AssociateCorpName5 = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName6( String value )
   {
      assertUnsent();
      _AssociateCorpName6 = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName7( String value )
   {
      assertUnsent();
      _AssociateCorpName7 = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName8( String value )
   {
      assertUnsent();
      _AssociateCorpName8 = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName9( String value )
   {
      assertUnsent();
      _AssociateCorpName9 = value;
   }
	
   /**
    * Sets the Associate Corporate Name field for the request.
    * 
    * @param value  Value that the Associate Corporate Name will be set to.
    */
   public final void setAssociateCorpName10( String value )
   {
      assertUnsent();
      _AssociateCorpName10 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp1( String value )
   {
      assertUnsent();
      _RoleInCorp1 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp2( String value )
   {
      assertUnsent();
      _RoleInCorp2 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp3( String value )
   {
      assertUnsent();
      _RoleInCorp3 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp4( String value )
   {
      assertUnsent();
      _RoleInCorp4 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp5( String value )
   {
      assertUnsent();
      _RoleInCorp5 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp6( String value )
   {
      assertUnsent();
      _RoleInCorp6 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp7( String value )
   {
      assertUnsent();
      _RoleInCorp7 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp8( String value )
   {
      assertUnsent();
      _RoleInCorp8 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp9( String value )
   {
      assertUnsent();
      _RoleInCorp9 = value;
   }
	
   /**
    * Sets the Corporate Role field for the request.
    * 
    * @param value  Value that the Corporate Role will be set to.
    */
   public final void setRoleInCorp10( String value )
   {
      assertUnsent();
      _RoleInCorp10 = value;
   }
	
   /**
    * Sets the Suppress KYC Letter field for the request.
    * 
    * @param value  Value that the Suppress KYC Letter will be set to.
    */
   public final void setSuppressKYCLetter( Boolean value )
   {
      assertUnsent();
      _SuppressKYCLetter = value;
   }
	
   /**
    * Sets the KYC Information format code field for the request.
    * 
    * @param value  Value that the KYC Information format code will be set to.
    */
   public final void setKYCInfoFormatCode( String value )
   {
      assertUnsent();
      _KYCInfoFormatCode = value;
   }
	
   /**
    * Sets the Profile Number field for the request.
    * 
    * @param value  Value that the Profile Number will be set to.
    */
   public final void setProfileNum( String value )
   {
      assertUnsent();
      _ProfileNum = value;
   }
	
   /**
    * Sets the Reference Number field for the request.
    * 
    * @param value  Value that the Reference Number will be set to.
    */
   public final void setRefNumber( String value )
   {
      assertUnsent();
      _RefNumber = value;
   }
	
   /**
    * Sets the Profile Value field for the request.
    * 
    * @param value  Value that the Profile Value will be set to.
    */
   public final void setProfileVal( String value )
   {
      assertUnsent();
      _ProfileVal = value;
   }
	
   /**
    * Sets the KYC Last Review Date field for the request.
    * 
    * @param value  Value that the KYC Last Review Date will be set to.
    */
   public final void setLastReviewDate( Date value )
   {
      assertUnsent();
      _LastReviewDate = value;
   }
	
   /**
    * Sets the SolicitPublicContrib field for the request.
    * 
    * @param value  Value that the SolicitPublicContrib will be set to.
    */
   public final void setSolicitPublicContrib( String value )
   {
      assertUnsent();
      _SolicitPublicContrib = value;
   }
	
   /**
    * Sets the InvReason field for the request.
    * 
    * @param value  Value that the InvReason will be set to.
    */
   public final void setInvReason( String value )
   {
      assertUnsent();
      _InvReason = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( _MaritalCode );
      requestBuffer.appendField( _Employer );
      requestBuffer.appendField( _EmployedYrs );
      requestBuffer.appendField( _IndustryCode );
      requestBuffer.appendField( _OccupationCode );
      requestBuffer.appendField( _AnnualIncomeCode );
      requestBuffer.appendField( _NetWorthCode );
      requestBuffer.appendField( _InvObjCode );
      requestBuffer.appendField( _InvKnowledgeCode );
      requestBuffer.appendField( _InvHorizonCode );
      requestBuffer.appendField( _RiskToleranceCode );
      requestBuffer.appendField( _OtherInvestments );
      requestBuffer.appendField( _AdvisorCode );
      requestBuffer.appendField( _WitnessName );
      requestBuffer.appendField( _WitnessAddr1 );
      requestBuffer.appendField( _WitnessAddr2 );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _PersonalSecCode );
      requestBuffer.appendField( _PrimMstrVer );
      requestBuffer.appendField( _ProcessDate );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _InvestPhilosophy );
      requestBuffer.appendField( _Occupation );
      requestBuffer.appendField( _GrowthPercent );
      requestBuffer.appendField( _IncomePercent );
      requestBuffer.appendField( _SafetyPercent );
      requestBuffer.appendField( _RepBranch );
      requestBuffer.appendField( _RepNo );
      requestBuffer.appendField( _SAMFInHealth );
      requestBuffer.appendField( _TypeOfBusFreeFormat );
      requestBuffer.appendField( _AcctProcessDate );
      requestBuffer.appendField( _AcctRepBranch );
      requestBuffer.appendField( _AcctRepNo );
      requestBuffer.appendField( _AcctKYCVer );
      requestBuffer.appendField( _MemorablePlace );
      requestBuffer.appendField( _MemorableWord );
      requestBuffer.appendField( _MemorableDate );
      requestBuffer.appendField( _KYCAgencyCode );
      requestBuffer.appendField( _KYCBranch );
      requestBuffer.appendField( _KYCAgentCode );
      requestBuffer.appendField( _KYCComment );
      requestBuffer.appendField( _EmploymentType );
      requestBuffer.appendField( _ResidenceType );
      requestBuffer.appendField( _ResAmount );
      requestBuffer.appendField( _KYCMailedDate );
      requestBuffer.appendField( _AnnualIncomeAmt );
      requestBuffer.appendField( _IncomeLevelDate );
      requestBuffer.appendField( _NetWorthAmt );
      requestBuffer.appendField( _NetWorthDate );
      requestBuffer.appendField( _RefferalCode );
      requestBuffer.appendField( _ReferenceName );
      requestBuffer.appendField( _SpecialtyCode );
      requestBuffer.appendField( _TolerancePrcnt );
      requestBuffer.appendField( _ShortTermPrcnt );
      requestBuffer.appendField( _AggressivePrcnt );
      requestBuffer.appendField( _PrcntDate );
      requestBuffer.appendField( _ShrKYCVer );
      requestBuffer.appendField( _InvestorType );
      requestBuffer.appendField( _InvestFor3rdPrty );
      requestBuffer.appendField( _BusCntryCode );
      requestBuffer.appendField( _OpenAcctPymn );
      requestBuffer.appendField( _FundScrlIdentified );
      requestBuffer.appendField( _PowOfAtt );
      requestBuffer.appendField( _ClientComplyCode );
      requestBuffer.appendField( _ComplyCodeID );
      requestBuffer.appendField( _EntityID );
      requestBuffer.appendField( _NumOfDependants );
      requestBuffer.appendField( _AssociateCorpName1 );
      requestBuffer.appendField( _AssociateCorpName2 );
      requestBuffer.appendField( _AssociateCorpName3 );
      requestBuffer.appendField( _AssociateCorpName4 );
      requestBuffer.appendField( _AssociateCorpName5 );
      requestBuffer.appendField( _AssociateCorpName6 );
      requestBuffer.appendField( _AssociateCorpName7 );
      requestBuffer.appendField( _AssociateCorpName8 );
      requestBuffer.appendField( _AssociateCorpName9 );
      requestBuffer.appendField( _AssociateCorpName10 );
      requestBuffer.appendField( _RoleInCorp1 );
      requestBuffer.appendField( _RoleInCorp2 );
      requestBuffer.appendField( _RoleInCorp3 );
      requestBuffer.appendField( _RoleInCorp4 );
      requestBuffer.appendField( _RoleInCorp5 );
      requestBuffer.appendField( _RoleInCorp6 );
      requestBuffer.appendField( _RoleInCorp7 );
      requestBuffer.appendField( _RoleInCorp8 );
      requestBuffer.appendField( _RoleInCorp9 );
      requestBuffer.appendField( _RoleInCorp10 );
      requestBuffer.appendField( _SuppressKYCLetter );
      requestBuffer.appendField( _KYCInfoFormatCode );
      requestBuffer.appendField( _ProfileNum );
      requestBuffer.appendField( _RefNumber );
      requestBuffer.appendField( _ProfileVal );
      requestBuffer.appendField( _LastReviewDate );
      requestBuffer.appendField( _SolicitPublicContrib );
      requestBuffer.appendField( _InvReason );
   }

}

