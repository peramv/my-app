
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Shareholder demographics details view.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderDemographics.doc">ShareholderDemographics.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderDemographicsView extends IFastView implements Serializable
{

   /**
    * BirthDate member variable.
    */
   private Date _BirthDate = null;
   
   /**
    * Gender member variable.
    */
   private String _Gender = null;
   
   /**
    * MaritalCode member variable.
    */
   private String _MaritalCode = null;
   
   /**
    * MaritalDescription member variable.
    */
   private String _MaritalDesc = null;
   
   /**
    * EmployerName member variable.
    */
   private String _Employer = null;
   
   /**
    * Employed Years member variable.
    */
   private String _EmployedYrs = null;
   
   /**
    * IndustryCode member variable.
    */
   private String _IndustryCode = null;
   
   /**
    * Industry code description member variable.
    */
   private String _IndustryDesc = null;
   
   /**
    * OccupationalCode member variable.
    */
   private String _OccupationCode = null;
   
   /**
    * Occupation code description member variable.
    */
   private String _OccupationDesc = null;
   
   /**
    * AnnualIncomeCode member variable.
    */
   private String _AnnualIncomeCode = null;
   
   /**
    * Annual income code description member variable.
    */
   private String _AnnualIncomeDesc = null;
   
   /**
    * NetWorthCode member variable.
    */
   private String _NetWorthCode = null;
   
   /**
    * Net worth description member variable.
    */
   private String _NetWorthDesc = null;
   
   /**
    * InvObjCode member variable.
    */
   private String _InvObjCode = null;
   
   /**
    * Investment objectives description member variable.
    */
   private String _InvObjDesc = null;
   
   /**
    * InvKnowledgeCode member variable.
    */
   private String _InvKnowledgeCode = null;
   
   /**
    * Investment knowledge description member variable.
    */
   private String _InvKnowledgeDesc = null;
   
   /**
    * InvHorizonCode member variable.
    */
   private String _InvHorizonCode = null;
   
   /**
    * Investment horizon description member variable.
    */
   private String _InvHorizonDesc = null;
   
   /**
    * RiskToleranceCode member variable.
    */
   private String _RiskToleranceCode = null;
   
   /**
    * Risk tolerance description member variable.
    */
   private String _RiskToleranceDesc = null;
   
   /**
    * OtherInvestmnets member variable.
    */
   private Boolean _OtherInvestments = null;
   
   /**
    * AdvisorCode member variable.
    */
   private String _AdvisorCode = null;
   
   /**
    * Advisor description member variable.
    */
   private String _AdvisorDesc = null;
   
   /**
    * Witness Name member variable.
    */
   private String _WitnessName = null;
   
   /**
    * Witness Address1 member variable.
    */
   private String _WitnessAddr1 = null;
   
   /**
    * Witness Address2 member variable.
    */
   private String _WitnessAddr2 = null;
   
   /**
    * Effective date member variable.
    */
   private Date _EffectiveDate = null;
   
   /**
    * Record Creation Date member variable.
    */
   private Date _ProcessDate = null;
   
   /**
    * Personal Security Code member variable.
    */
   private String _PersonalSecCode = null;
   
   /**
    * Prim-Mstr Version Number member variable.
    */
   private Integer _PrimMstrVer = null;
   
   /**
    * Recid of Prim-Mstr record member variable.
    */
   private Integer _PrimMstrRid = null;
   
   /**
    * Investment Philosophy member variable.
    */
   private String _InvestPhilosophy = null;
   
   /**
    * Occupation Code member variable.
    */
   private String _Occupation = null;
   
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
   private String _RepBranch = null;
   
   /**
    * Representative Number who changed KYC Info member variable.
    */
   private Integer _RepNo = null;
   
   /**
    * SAM Financial Health member variable.
    */
   private String _SAMFInHealth = null;
   
   /**
    * TypeOfBusFreeFormat member variable.
    */
   private String _TypeOfBusFreeFormat = null;
   
   /**
    * Account Mod Date member variable.
    */
   private Date _AcctModDate = null;
   
   /**
    * Account Mod User member variable.
    */
   private String _AcctModUser = null;
   
   /**
    * Account Process Date member variable.
    */
   private Date _AcctProcessDate = null;
   
   /**
    * Account Rep Branch member variable.
    */
   private String _AcctRepBranch = null;
   
   /**
    * Account Rep No member variable.
    */
   private Integer _AcctRepNo = null;
   
   /**
    * Account User Name member variable.
    */
   private String _AcctUserName = null;
   
   /**
    * AcctKYCVer member variable.
    */
   private Integer _AcctKYCVer = null;
   
   /**
    * User Name member variable.
    */
   private String _UserName = null;
   
   /**
    * Mod User member variable.
    */
   private String _ModUser = null;
   
   /**
    * Mod Date member variable.
    */
   private Date _ModDate = null;
   
   /**
    * Memorable Place member variable.
    */
   private String _MemorablePlace = null;
   
   /**
    * Memorable Word member variable.
    */
   private String _MemorableWord = null;
   
   /**
    * Memorable Date member variable.
    */
   private Date _MemorableDate = null;
   
   /**
    * KYC Comment member variable.
    */
   private String _KYCComment = null;
   
   /**
    * Employment Type member variable.
    */
   private String _EmploymentType = null;
   
   /**
    * Residence Type member variable.
    */
   private String _ResidenceType = null;
   
   /**
    * ResAmount member variable.
    */
   private String _ResAmount = null;
   
   /**
    * KYC Mailed Date member variable.
    */
   private Date _KYCMailedDate = null;
   
   /**
    * Annual Income Amount member variable.
    */
   private String _AnnualIncomeAmt = null;
   
   /**
    * Income Level Date member variable.
    */
   private Date _IncomeLevelDate = null;
   
   /**
    * Net Worth Amount member variable.
    */
   private String _NetWorthAmt = null;
   
   /**
    * Net Worth Date member variable.
    */
   private Date _NetWorthDate = null;
   
   /**
    * Refferal Code member variable.
    */
   private String _RefferalCode = null;
   
   /**
    * Reference Name member variable.
    */
   private String _ReferenceName = null;
   
   /**
    * Specialty Code member variable.
    */
   private String _SpecialtyCode = null;
   
   /**
    * Tolerance Percentage member variable.
    */
   private String _TolerancePrcnt = null;
   
   /**
    * Short Term Percentage member variable.
    */
   private String _ShortTermPrcnt = null;
   
   /**
    * Aggressive Percentage member variable.
    */
   private String _AggressivePrcnt = null;
   
   /**
    * Percentage Date member variable.
    */
   private Date _PrcntDate = null;
   
   /**
    * ShrKYCVer member variable.
    */
   private Integer _ShrKYCVer = null;
   
   /**
    * KYC Rec ID member variable.
    */
   private Integer _KYCRID = null;
   
   /**
    * Investor Type member variable.
    */
   private String _InvestorType = null;
   
   /**
    * Invest on behalf of 3rd Party member variable.
    */
   private String _InvestFor3rdPrty = null;
   
   /**
    * Country where business is conducted member variable.
    */
   private String _BusCntryCode = null;
   
   /**
    * Initial payment member variable.
    */
   private String _OpenAcctPymn = null;
   
   /**
    * Source of Funds Identified member variable.
    */
   private String _FundScrlIdentified = null;
   
   /**
    * Power of attorney member variable.
    */
   private String _PowOfAtt = null;
   
   /**
    * Compliance Code member variable.
    */
   private String _ComplianceCode = null;
   
   /**
    * ID of the Regulatory Standard member variable.
    */
   private String _ComplyCodeID = null;
   
   /**
    * Country Code of the Regulation Standard member variable.
    */
   private String _ReguLatoryCntryCode = null;
   
   /**
    * Number Of Dependants member variable.
    */
   private Integer _NumOfDependants = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName1 = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName2 = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName3 = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName4 = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName5 = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName6 = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName7 = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName8 = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName9 = null;
   
   /**
    * Associate Corporate Name member variable.
    */
   private String _AssociateCorpName10 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp1 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp2 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp3 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp4 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp5 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp6 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp7 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp8 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp9 = null;
   
   /**
    * Corporate Role member variable.
    */
   private String _RoleInCorp10 = null;
   
   /**
    * Suppress KYC Letter member variable.
    */
   private Boolean _SuppressKYCLetter = null;
   
   /**
    * Code of the Regulatory Standard member variable.
    */
   private String _ComplyCode = null;
   
   /**
    * KYC Information format code member variable.
    */
   private String _KYCInfoFormatCode = null;
   
   /**
    * KYC Information format description member variable.
    */
   private String _KYCInfoFormatDesc = null;
   
   /**
    * Profile Number member variable.
    */
   private String _ProfileNum = null;
   
   /**
    * Reference Number member variable.
    */
   private String _RefNumber = null;
   
   /**
    * Profile Value member variable.
    */
   private String _ProfileVal = null;
   
   /**
    * KYC Last Review Date member variable.
    */
   private Date _LastReviewDate = null;
   
   /**
    * SolicitPublicContrib member variable.
    */
   private String _SolicitPublicContrib = null;
   
   /**
    * InvReason member variable.
    */
   private String _InvReason = null;
   

   /**
    * Constructs the ShareholderDemographicsView object.
    * 
    */
   public ShareholderDemographicsView()
   {
      super ( new ShareholderDemographicsRequest() );
   }

   /**
    * Constructs the ShareholderDemographicsView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ShareholderDemographicsView( String hostEncoding )
   {
      super ( new ShareholderDemographicsRequest( hostEncoding ) );
   }

   /**
    * Gets the ShareholderDemographicsRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ShareholderDemographicsRequest object.
    */
   public final ShareholderDemographicsRequest getRequest()
   {
      return (ShareholderDemographicsRequest)getIFastRequest();
   }
        
   /**
    * Gets the BirthDate field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the BirthDate or null.
    */
   public final Date getBirthDate()
   {
      return _BirthDate;
   }
	
   /**
    * Gets the BirthDate field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BirthDate or the specified default value.
    */
   public final Date getBirthDate( Date defaultValue )
   {
      return _BirthDate == null ? defaultValue : _BirthDate;
   }
                  
   /**
    * Gets the Gender field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Gender or null.
    */
   public final String getGender()
   {
      return _Gender;
   }
	
   /**
    * Gets the Gender field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gender or the specified default value.
    */
   public final String getGender( String defaultValue )
   {
      return _Gender == null ? defaultValue : _Gender;
   }
                  
   /**
    * Gets the MaritalCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MaritalCode or null.
    */
   public final String getMaritalCode()
   {
      return _MaritalCode;
   }
	
   /**
    * Gets the MaritalCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MaritalCode or the specified default value.
    */
   public final String getMaritalCode( String defaultValue )
   {
      return _MaritalCode == null ? defaultValue : _MaritalCode;
   }
                  
   /**
    * Gets the MaritalDescription field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the MaritalDescription or null.
    */
   public final String getMaritalDesc()
   {
      return _MaritalDesc;
   }
	
   /**
    * Gets the MaritalDescription field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the MaritalDescription or the specified default value.
    */
   public final String getMaritalDesc( String defaultValue )
   {
      return _MaritalDesc == null ? defaultValue : _MaritalDesc;
   }
                  
   /**
    * Gets the EmployerName field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EmployerName or null.
    */
   public final String getEmployer()
   {
      return _Employer;
   }
	
   /**
    * Gets the EmployerName field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EmployerName or the specified default value.
    */
   public final String getEmployer( String defaultValue )
   {
      return _Employer == null ? defaultValue : _Employer;
   }
                  
   /**
    * Gets the Employed Years field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Employed Years or null.
    */
   public final String getEmployedYrs()
   {
      return _EmployedYrs;
   }
	
   /**
    * Gets the Employed Years field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Employed Years or the specified default value.
    */
   public final String getEmployedYrs( String defaultValue )
   {
      return _EmployedYrs == null ? defaultValue : _EmployedYrs;
   }
                  
   /**
    * Gets the IndustryCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the IndustryCode or null.
    */
   public final String getIndustryCode()
   {
      return _IndustryCode;
   }
	
   /**
    * Gets the IndustryCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IndustryCode or the specified default value.
    */
   public final String getIndustryCode( String defaultValue )
   {
      return _IndustryCode == null ? defaultValue : _IndustryCode;
   }
                  
   /**
    * Gets the Industry code description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Industry code description or null.
    */
   public final String getIndustryDesc()
   {
      return _IndustryDesc;
   }
	
   /**
    * Gets the Industry code description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Industry code description or the specified default value.
    */
   public final String getIndustryDesc( String defaultValue )
   {
      return _IndustryDesc == null ? defaultValue : _IndustryDesc;
   }
                  
   /**
    * Gets the OccupationalCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the OccupationalCode or null.
    */
   public final String getOccupationCode()
   {
      return _OccupationCode;
   }
	
   /**
    * Gets the OccupationalCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OccupationalCode or the specified default value.
    */
   public final String getOccupationCode( String defaultValue )
   {
      return _OccupationCode == null ? defaultValue : _OccupationCode;
   }
                  
   /**
    * Gets the Occupation code description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Occupation code description or null.
    */
   public final String getOccupationDesc()
   {
      return _OccupationDesc;
   }
	
   /**
    * Gets the Occupation code description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Occupation code description or the specified default value.
    */
   public final String getOccupationDesc( String defaultValue )
   {
      return _OccupationDesc == null ? defaultValue : _OccupationDesc;
   }
                  
   /**
    * Gets the AnnualIncomeCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AnnualIncomeCode or null.
    */
   public final String getAnnualIncomeCode()
   {
      return _AnnualIncomeCode;
   }
	
   /**
    * Gets the AnnualIncomeCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AnnualIncomeCode or the specified default value.
    */
   public final String getAnnualIncomeCode( String defaultValue )
   {
      return _AnnualIncomeCode == null ? defaultValue : _AnnualIncomeCode;
   }
                  
   /**
    * Gets the Annual income code description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Annual income code description or null.
    */
   public final String getAnnualIncomeDesc()
   {
      return _AnnualIncomeDesc;
   }
	
   /**
    * Gets the Annual income code description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual income code description or the specified default value.
    */
   public final String getAnnualIncomeDesc( String defaultValue )
   {
      return _AnnualIncomeDesc == null ? defaultValue : _AnnualIncomeDesc;
   }
                  
   /**
    * Gets the NetWorthCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the NetWorthCode or null.
    */
   public final String getNetWorthCode()
   {
      return _NetWorthCode;
   }
	
   /**
    * Gets the NetWorthCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the NetWorthCode or the specified default value.
    */
   public final String getNetWorthCode( String defaultValue )
   {
      return _NetWorthCode == null ? defaultValue : _NetWorthCode;
   }
                  
   /**
    * Gets the Net worth description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Net worth description or null.
    */
   public final String getNetWorthDesc()
   {
      return _NetWorthDesc;
   }
	
   /**
    * Gets the Net worth description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net worth description or the specified default value.
    */
   public final String getNetWorthDesc( String defaultValue )
   {
      return _NetWorthDesc == null ? defaultValue : _NetWorthDesc;
   }
                  
   /**
    * Gets the InvObjCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the InvObjCode or null.
    */
   public final String getInvObjCode()
   {
      return _InvObjCode;
   }
	
   /**
    * Gets the InvObjCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvObjCode or the specified default value.
    */
   public final String getInvObjCode( String defaultValue )
   {
      return _InvObjCode == null ? defaultValue : _InvObjCode;
   }
                  
   /**
    * Gets the Investment objectives description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment objectives description or null.
    */
   public final String getInvObjDesc()
   {
      return _InvObjDesc;
   }
	
   /**
    * Gets the Investment objectives description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment objectives description or the specified default value.
    */
   public final String getInvObjDesc( String defaultValue )
   {
      return _InvObjDesc == null ? defaultValue : _InvObjDesc;
   }
                  
   /**
    * Gets the InvKnowledgeCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the InvKnowledgeCode or null.
    */
   public final String getInvKnowledgeCode()
   {
      return _InvKnowledgeCode;
   }
	
   /**
    * Gets the InvKnowledgeCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvKnowledgeCode or the specified default value.
    */
   public final String getInvKnowledgeCode( String defaultValue )
   {
      return _InvKnowledgeCode == null ? defaultValue : _InvKnowledgeCode;
   }
                  
   /**
    * Gets the Investment knowledge description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment knowledge description or null.
    */
   public final String getInvKnowledgeDesc()
   {
      return _InvKnowledgeDesc;
   }
	
   /**
    * Gets the Investment knowledge description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment knowledge description or the specified default value.
    */
   public final String getInvKnowledgeDesc( String defaultValue )
   {
      return _InvKnowledgeDesc == null ? defaultValue : _InvKnowledgeDesc;
   }
                  
   /**
    * Gets the InvHorizonCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the InvHorizonCode or null.
    */
   public final String getInvHorizonCode()
   {
      return _InvHorizonCode;
   }
	
   /**
    * Gets the InvHorizonCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvHorizonCode or the specified default value.
    */
   public final String getInvHorizonCode( String defaultValue )
   {
      return _InvHorizonCode == null ? defaultValue : _InvHorizonCode;
   }
                  
   /**
    * Gets the Investment horizon description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment horizon description or null.
    */
   public final String getInvHorizonDesc()
   {
      return _InvHorizonDesc;
   }
	
   /**
    * Gets the Investment horizon description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment horizon description or the specified default value.
    */
   public final String getInvHorizonDesc( String defaultValue )
   {
      return _InvHorizonDesc == null ? defaultValue : _InvHorizonDesc;
   }
                  
   /**
    * Gets the RiskToleranceCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RiskToleranceCode or null.
    */
   public final String getRiskToleranceCode()
   {
      return _RiskToleranceCode;
   }
	
   /**
    * Gets the RiskToleranceCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RiskToleranceCode or the specified default value.
    */
   public final String getRiskToleranceCode( String defaultValue )
   {
      return _RiskToleranceCode == null ? defaultValue : _RiskToleranceCode;
   }
                  
   /**
    * Gets the Risk tolerance description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Risk tolerance description or null.
    */
   public final String getRiskToleranceDesc()
   {
      return _RiskToleranceDesc;
   }
	
   /**
    * Gets the Risk tolerance description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Risk tolerance description or the specified default value.
    */
   public final String getRiskToleranceDesc( String defaultValue )
   {
      return _RiskToleranceDesc == null ? defaultValue : _RiskToleranceDesc;
   }
                  
   /**
    * Gets the OtherInvestmnets field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the OtherInvestmnets or null.
    */
   public final Boolean getOtherInvestments()
   {
      return _OtherInvestments;
   }
	
   /**
    * Gets the OtherInvestmnets field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the OtherInvestmnets or the specified default value.
    */
   public final boolean getOtherInvestments( boolean defaultValue )
   {
      return _OtherInvestments == null ? defaultValue : _OtherInvestments.booleanValue();
   }
                  
   /**
    * Gets the AdvisorCode field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AdvisorCode or null.
    */
   public final String getAdvisorCode()
   {
      return _AdvisorCode;
   }
	
   /**
    * Gets the AdvisorCode field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AdvisorCode or the specified default value.
    */
   public final String getAdvisorCode( String defaultValue )
   {
      return _AdvisorCode == null ? defaultValue : _AdvisorCode;
   }
                  
   /**
    * Gets the Advisor description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Advisor description or null.
    */
   public final String getAdvisorDesc()
   {
      return _AdvisorDesc;
   }
	
   /**
    * Gets the Advisor description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Advisor description or the specified default value.
    */
   public final String getAdvisorDesc( String defaultValue )
   {
      return _AdvisorDesc == null ? defaultValue : _AdvisorDesc;
   }
                  
   /**
    * Gets the Witness Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Witness Name or null.
    */
   public final String getWitnessName()
   {
      return _WitnessName;
   }
	
   /**
    * Gets the Witness Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Witness Name or the specified default value.
    */
   public final String getWitnessName( String defaultValue )
   {
      return _WitnessName == null ? defaultValue : _WitnessName;
   }
                  
   /**
    * Gets the Witness Address1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Witness Address1 or null.
    */
   public final String getWitnessAddr1()
   {
      return _WitnessAddr1;
   }
	
   /**
    * Gets the Witness Address1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Witness Address1 or the specified default value.
    */
   public final String getWitnessAddr1( String defaultValue )
   {
      return _WitnessAddr1 == null ? defaultValue : _WitnessAddr1;
   }
                  
   /**
    * Gets the Witness Address2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Witness Address2 or null.
    */
   public final String getWitnessAddr2()
   {
      return _WitnessAddr2;
   }
	
   /**
    * Gets the Witness Address2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Witness Address2 or the specified default value.
    */
   public final String getWitnessAddr2( String defaultValue )
   {
      return _WitnessAddr2 == null ? defaultValue : _WitnessAddr2;
   }
                  
   /**
    * Gets the Effective date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective date or null.
    */
   public final Date getEffectiveDate()
   {
      return _EffectiveDate;
   }
	
   /**
    * Gets the Effective date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective date or the specified default value.
    */
   public final Date getEffectiveDate( Date defaultValue )
   {
      return _EffectiveDate == null ? defaultValue : _EffectiveDate;
   }
                  
   /**
    * Gets the Record Creation Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Record Creation Date or null.
    */
   public final Date getProcessDate()
   {
      return _ProcessDate;
   }
	
   /**
    * Gets the Record Creation Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Creation Date or the specified default value.
    */
   public final Date getProcessDate( Date defaultValue )
   {
      return _ProcessDate == null ? defaultValue : _ProcessDate;
   }
                  
   /**
    * Gets the Personal Security Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Personal Security Code or null.
    */
   public final String getPersonalSecCode()
   {
      return _PersonalSecCode;
   }
	
   /**
    * Gets the Personal Security Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Personal Security Code or the specified default value.
    */
   public final String getPersonalSecCode( String defaultValue )
   {
      return _PersonalSecCode == null ? defaultValue : _PersonalSecCode;
   }
                  
   /**
    * Gets the Prim-Mstr Version Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Prim-Mstr Version Number or null.
    */
   public final Integer getPrimMstrVer()
   {
      return _PrimMstrVer;
   }
	
   /**
    * Gets the Prim-Mstr Version Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Prim-Mstr Version Number or the specified default value.
    */
   public final int getPrimMstrVer( int defaultValue )
   {
      return _PrimMstrVer == null ? defaultValue : _PrimMstrVer.intValue();
   }
                  
   /**
    * Gets the Recid of Prim-Mstr record field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Recid of Prim-Mstr record or null.
    */
   public final Integer getPrimMstrRid()
   {
      return _PrimMstrRid;
   }
	
   /**
    * Gets the Recid of Prim-Mstr record field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of Prim-Mstr record or the specified default value.
    */
   public final int getPrimMstrRid( int defaultValue )
   {
      return _PrimMstrRid == null ? defaultValue : _PrimMstrRid.intValue();
   }
                  
   /**
    * Gets the Investment Philosophy field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investment Philosophy or null.
    */
   public final String getInvestPhilosophy()
   {
      return _InvestPhilosophy;
   }
	
   /**
    * Gets the Investment Philosophy field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investment Philosophy or the specified default value.
    */
   public final String getInvestPhilosophy( String defaultValue )
   {
      return _InvestPhilosophy == null ? defaultValue : _InvestPhilosophy;
   }
                  
   /**
    * Gets the Occupation Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Occupation Code or null.
    */
   public final String getOccupation()
   {
      return _Occupation;
   }
	
   /**
    * Gets the Occupation Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Occupation Code or the specified default value.
    */
   public final String getOccupation( String defaultValue )
   {
      return _Occupation == null ? defaultValue : _Occupation;
   }
                  
   /**
    * Gets the Growth Percent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Growth Percent or null.
    */
   public final Integer getGrowthPercent()
   {
      return _GrowthPercent;
   }
	
   /**
    * Gets the Growth Percent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Growth Percent or the specified default value.
    */
   public final int getGrowthPercent( int defaultValue )
   {
      return _GrowthPercent == null ? defaultValue : _GrowthPercent.intValue();
   }
                  
   /**
    * Gets the Income Percent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Income Percent or null.
    */
   public final Integer getIncomePercent()
   {
      return _IncomePercent;
   }
	
   /**
    * Gets the Income Percent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Income Percent or the specified default value.
    */
   public final int getIncomePercent( int defaultValue )
   {
      return _IncomePercent == null ? defaultValue : _IncomePercent.intValue();
   }
                  
   /**
    * Gets the Safety Percent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Safety Percent or null.
    */
   public final Integer getSafetyPercent()
   {
      return _SafetyPercent;
   }
	
   /**
    * Gets the Safety Percent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Safety Percent or the specified default value.
    */
   public final int getSafetyPercent( int defaultValue )
   {
      return _SafetyPercent == null ? defaultValue : _SafetyPercent.intValue();
   }
                  
   /**
    * Gets the Branch the representative  sells from field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Branch the representative  sells from or null.
    */
   public final String getRepBranch()
   {
      return _RepBranch;
   }
	
   /**
    * Gets the Branch the representative  sells from field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Branch the representative  sells from or the specified default value.
    */
   public final String getRepBranch( String defaultValue )
   {
      return _RepBranch == null ? defaultValue : _RepBranch;
   }
                  
   /**
    * Gets the Representative Number who changed KYC Info field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Representative Number who changed KYC Info or null.
    */
   public final Integer getRepNo()
   {
      return _RepNo;
   }
	
   /**
    * Gets the Representative Number who changed KYC Info field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Representative Number who changed KYC Info or the specified default value.
    */
   public final int getRepNo( int defaultValue )
   {
      return _RepNo == null ? defaultValue : _RepNo.intValue();
   }
                  
   /**
    * Gets the SAM Financial Health field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SAM Financial Health or null.
    */
   public final String getSAMFInHealth()
   {
      return _SAMFInHealth;
   }
	
   /**
    * Gets the SAM Financial Health field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAM Financial Health or the specified default value.
    */
   public final String getSAMFInHealth( String defaultValue )
   {
      return _SAMFInHealth == null ? defaultValue : _SAMFInHealth;
   }
                  
   /**
    * Gets the TypeOfBusFreeFormat field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TypeOfBusFreeFormat or null.
    */
   public final String getTypeOfBusFreeFormat()
   {
      return _TypeOfBusFreeFormat;
   }
	
   /**
    * Gets the TypeOfBusFreeFormat field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TypeOfBusFreeFormat or the specified default value.
    */
   public final String getTypeOfBusFreeFormat( String defaultValue )
   {
      return _TypeOfBusFreeFormat == null ? defaultValue : _TypeOfBusFreeFormat;
   }
                  
   /**
    * Gets the Account Mod Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Mod Date or null.
    */
   public final Date getAcctModDate()
   {
      return _AcctModDate;
   }
	
   /**
    * Gets the Account Mod Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Mod Date or the specified default value.
    */
   public final Date getAcctModDate( Date defaultValue )
   {
      return _AcctModDate == null ? defaultValue : _AcctModDate;
   }
                  
   /**
    * Gets the Account Mod User field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Mod User or null.
    */
   public final String getAcctModUser()
   {
      return _AcctModUser;
   }
	
   /**
    * Gets the Account Mod User field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Mod User or the specified default value.
    */
   public final String getAcctModUser( String defaultValue )
   {
      return _AcctModUser == null ? defaultValue : _AcctModUser;
   }
                  
   /**
    * Gets the Account Process Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Process Date or null.
    */
   public final Date getAcctProcessDate()
   {
      return _AcctProcessDate;
   }
	
   /**
    * Gets the Account Process Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Process Date or the specified default value.
    */
   public final Date getAcctProcessDate( Date defaultValue )
   {
      return _AcctProcessDate == null ? defaultValue : _AcctProcessDate;
   }
                  
   /**
    * Gets the Account Rep Branch field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Rep Branch or null.
    */
   public final String getAcctRepBranch()
   {
      return _AcctRepBranch;
   }
	
   /**
    * Gets the Account Rep Branch field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Rep Branch or the specified default value.
    */
   public final String getAcctRepBranch( String defaultValue )
   {
      return _AcctRepBranch == null ? defaultValue : _AcctRepBranch;
   }
                  
   /**
    * Gets the Account Rep No field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Rep No or null.
    */
   public final Integer getAcctRepNo()
   {
      return _AcctRepNo;
   }
	
   /**
    * Gets the Account Rep No field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Rep No or the specified default value.
    */
   public final int getAcctRepNo( int defaultValue )
   {
      return _AcctRepNo == null ? defaultValue : _AcctRepNo.intValue();
   }
                  
   /**
    * Gets the Account User Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account User Name or null.
    */
   public final String getAcctUserName()
   {
      return _AcctUserName;
   }
	
   /**
    * Gets the Account User Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account User Name or the specified default value.
    */
   public final String getAcctUserName( String defaultValue )
   {
      return _AcctUserName == null ? defaultValue : _AcctUserName;
   }
                  
   /**
    * Gets the AcctKYCVer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AcctKYCVer or null.
    */
   public final Integer getAcctKYCVer()
   {
      return _AcctKYCVer;
   }
	
   /**
    * Gets the AcctKYCVer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AcctKYCVer or the specified default value.
    */
   public final int getAcctKYCVer( int defaultValue )
   {
      return _AcctKYCVer == null ? defaultValue : _AcctKYCVer.intValue();
   }
                  
   /**
    * Gets the User Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the User Name or null.
    */
   public final String getUserName()
   {
      return _UserName;
   }
	
   /**
    * Gets the User Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( String defaultValue )
   {
      return _UserName == null ? defaultValue : _UserName;
   }
                  
   /**
    * Gets the Mod User field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mod User or null.
    */
   public final String getModUser()
   {
      return _ModUser;
   }
	
   /**
    * Gets the Mod User field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod User or the specified default value.
    */
   public final String getModUser( String defaultValue )
   {
      return _ModUser == null ? defaultValue : _ModUser;
   }
                  
   /**
    * Gets the Mod Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Mod Date or null.
    */
   public final Date getModDate()
   {
      return _ModDate;
   }
	
   /**
    * Gets the Mod Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Date or the specified default value.
    */
   public final Date getModDate( Date defaultValue )
   {
      return _ModDate == null ? defaultValue : _ModDate;
   }
                  
   /**
    * Gets the Memorable Place field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Memorable Place or null.
    */
   public final String getMemorablePlace()
   {
      return _MemorablePlace;
   }
	
   /**
    * Gets the Memorable Place field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Memorable Place or the specified default value.
    */
   public final String getMemorablePlace( String defaultValue )
   {
      return _MemorablePlace == null ? defaultValue : _MemorablePlace;
   }
                  
   /**
    * Gets the Memorable Word field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Memorable Word or null.
    */
   public final String getMemorableWord()
   {
      return _MemorableWord;
   }
	
   /**
    * Gets the Memorable Word field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Memorable Word or the specified default value.
    */
   public final String getMemorableWord( String defaultValue )
   {
      return _MemorableWord == null ? defaultValue : _MemorableWord;
   }
                  
   /**
    * Gets the Memorable Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Memorable Date or null.
    */
   public final Date getMemorableDate()
   {
      return _MemorableDate;
   }
	
   /**
    * Gets the Memorable Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Memorable Date or the specified default value.
    */
   public final Date getMemorableDate( Date defaultValue )
   {
      return _MemorableDate == null ? defaultValue : _MemorableDate;
   }
                  
   /**
    * Gets the KYC Comment field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the KYC Comment or null.
    */
   public final String getKYCComment()
   {
      return _KYCComment;
   }
	
   /**
    * Gets the KYC Comment field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KYC Comment or the specified default value.
    */
   public final String getKYCComment( String defaultValue )
   {
      return _KYCComment == null ? defaultValue : _KYCComment;
   }
                  
   /**
    * Gets the Employment Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Employment Type or null.
    */
   public final String getEmploymentType()
   {
      return _EmploymentType;
   }
	
   /**
    * Gets the Employment Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Employment Type or the specified default value.
    */
   public final String getEmploymentType( String defaultValue )
   {
      return _EmploymentType == null ? defaultValue : _EmploymentType;
   }
                  
   /**
    * Gets the Residence Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Residence Type or null.
    */
   public final String getResidenceType()
   {
      return _ResidenceType;
   }
	
   /**
    * Gets the Residence Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Residence Type or the specified default value.
    */
   public final String getResidenceType( String defaultValue )
   {
      return _ResidenceType == null ? defaultValue : _ResidenceType;
   }
                  
   /**
    * Gets the ResAmount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ResAmount or null.
    */
   public final String getResAmount()
   {
      return _ResAmount;
   }
	
   /**
    * Gets the ResAmount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ResAmount or the specified default value.
    */
   public final String getResAmount( String defaultValue )
   {
      return _ResAmount == null ? defaultValue : _ResAmount;
   }
                  
   /**
    * Gets the KYC Mailed Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the KYC Mailed Date or null.
    */
   public final Date getKYCMailedDate()
   {
      return _KYCMailedDate;
   }
	
   /**
    * Gets the KYC Mailed Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KYC Mailed Date or the specified default value.
    */
   public final Date getKYCMailedDate( Date defaultValue )
   {
      return _KYCMailedDate == null ? defaultValue : _KYCMailedDate;
   }
                  
   /**
    * Gets the Annual Income Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Annual Income Amount or null.
    */
   public final String getAnnualIncomeAmt()
   {
      return _AnnualIncomeAmt;
   }
	
   /**
    * Gets the Annual Income Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Annual Income Amount or the specified default value.
    */
   public final String getAnnualIncomeAmt( String defaultValue )
   {
      return _AnnualIncomeAmt == null ? defaultValue : _AnnualIncomeAmt;
   }
                  
   /**
    * Gets the Income Level Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Income Level Date or null.
    */
   public final Date getIncomeLevelDate()
   {
      return _IncomeLevelDate;
   }
	
   /**
    * Gets the Income Level Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Income Level Date or the specified default value.
    */
   public final Date getIncomeLevelDate( Date defaultValue )
   {
      return _IncomeLevelDate == null ? defaultValue : _IncomeLevelDate;
   }
                  
   /**
    * Gets the Net Worth Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Net Worth Amount or null.
    */
   public final String getNetWorthAmt()
   {
      return _NetWorthAmt;
   }
	
   /**
    * Gets the Net Worth Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Worth Amount or the specified default value.
    */
   public final String getNetWorthAmt( String defaultValue )
   {
      return _NetWorthAmt == null ? defaultValue : _NetWorthAmt;
   }
                  
   /**
    * Gets the Net Worth Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Net Worth Date or null.
    */
   public final Date getNetWorthDate()
   {
      return _NetWorthDate;
   }
	
   /**
    * Gets the Net Worth Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Worth Date or the specified default value.
    */
   public final Date getNetWorthDate( Date defaultValue )
   {
      return _NetWorthDate == null ? defaultValue : _NetWorthDate;
   }
                  
   /**
    * Gets the Refferal Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Refferal Code or null.
    */
   public final String getRefferalCode()
   {
      return _RefferalCode;
   }
	
   /**
    * Gets the Refferal Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Refferal Code or the specified default value.
    */
   public final String getRefferalCode( String defaultValue )
   {
      return _RefferalCode == null ? defaultValue : _RefferalCode;
   }
                  
   /**
    * Gets the Reference Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Reference Name or null.
    */
   public final String getReferenceName()
   {
      return _ReferenceName;
   }
	
   /**
    * Gets the Reference Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Name or the specified default value.
    */
   public final String getReferenceName( String defaultValue )
   {
      return _ReferenceName == null ? defaultValue : _ReferenceName;
   }
                  
   /**
    * Gets the Specialty Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Specialty Code or null.
    */
   public final String getSpecialtyCode()
   {
      return _SpecialtyCode;
   }
	
   /**
    * Gets the Specialty Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Specialty Code or the specified default value.
    */
   public final String getSpecialtyCode( String defaultValue )
   {
      return _SpecialtyCode == null ? defaultValue : _SpecialtyCode;
   }
                  
   /**
    * Gets the Tolerance Percentage field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tolerance Percentage or null.
    */
   public final String getTolerancePrcnt()
   {
      return _TolerancePrcnt;
   }
	
   /**
    * Gets the Tolerance Percentage field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tolerance Percentage or the specified default value.
    */
   public final String getTolerancePrcnt( String defaultValue )
   {
      return _TolerancePrcnt == null ? defaultValue : _TolerancePrcnt;
   }
                  
   /**
    * Gets the Short Term Percentage field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Short Term Percentage or null.
    */
   public final String getShortTermPrcnt()
   {
      return _ShortTermPrcnt;
   }
	
   /**
    * Gets the Short Term Percentage field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Short Term Percentage or the specified default value.
    */
   public final String getShortTermPrcnt( String defaultValue )
   {
      return _ShortTermPrcnt == null ? defaultValue : _ShortTermPrcnt;
   }
                  
   /**
    * Gets the Aggressive Percentage field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Aggressive Percentage or null.
    */
   public final String getAggressivePrcnt()
   {
      return _AggressivePrcnt;
   }
	
   /**
    * Gets the Aggressive Percentage field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Aggressive Percentage or the specified default value.
    */
   public final String getAggressivePrcnt( String defaultValue )
   {
      return _AggressivePrcnt == null ? defaultValue : _AggressivePrcnt;
   }
                  
   /**
    * Gets the Percentage Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Percentage Date or null.
    */
   public final Date getPrcntDate()
   {
      return _PrcntDate;
   }
	
   /**
    * Gets the Percentage Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percentage Date or the specified default value.
    */
   public final Date getPrcntDate( Date defaultValue )
   {
      return _PrcntDate == null ? defaultValue : _PrcntDate;
   }
                  
   /**
    * Gets the ShrKYCVer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ShrKYCVer or null.
    */
   public final Integer getShrKYCVer()
   {
      return _ShrKYCVer;
   }
	
   /**
    * Gets the ShrKYCVer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ShrKYCVer or the specified default value.
    */
   public final int getShrKYCVer( int defaultValue )
   {
      return _ShrKYCVer == null ? defaultValue : _ShrKYCVer.intValue();
   }
                  
   /**
    * Gets the KYC Rec ID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the KYC Rec ID or null.
    */
   public final Integer getKYCRID()
   {
      return _KYCRID;
   }
	
   /**
    * Gets the KYC Rec ID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KYC Rec ID or the specified default value.
    */
   public final int getKYCRID( int defaultValue )
   {
      return _KYCRID == null ? defaultValue : _KYCRID.intValue();
   }
                  
   /**
    * Gets the Investor Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Investor Type or null.
    */
   public final String getInvestorType()
   {
      return _InvestorType;
   }
	
   /**
    * Gets the Investor Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Investor Type or the specified default value.
    */
   public final String getInvestorType( String defaultValue )
   {
      return _InvestorType == null ? defaultValue : _InvestorType;
   }
                  
   /**
    * Gets the Invest on behalf of 3rd Party field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Invest on behalf of 3rd Party or null.
    */
   public final String getInvestFor3rdPrty()
   {
      return _InvestFor3rdPrty;
   }
	
   /**
    * Gets the Invest on behalf of 3rd Party field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Invest on behalf of 3rd Party or the specified default value.
    */
   public final String getInvestFor3rdPrty( String defaultValue )
   {
      return _InvestFor3rdPrty == null ? defaultValue : _InvestFor3rdPrty;
   }
                  
   /**
    * Gets the Country where business is conducted field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Country where business is conducted or null.
    */
   public final String getBusCntryCode()
   {
      return _BusCntryCode;
   }
	
   /**
    * Gets the Country where business is conducted field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country where business is conducted or the specified default value.
    */
   public final String getBusCntryCode( String defaultValue )
   {
      return _BusCntryCode == null ? defaultValue : _BusCntryCode;
   }
                  
   /**
    * Gets the Initial payment field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Initial payment or null.
    */
   public final String getOpenAcctPymn()
   {
      return _OpenAcctPymn;
   }
	
   /**
    * Gets the Initial payment field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Initial payment or the specified default value.
    */
   public final String getOpenAcctPymn( String defaultValue )
   {
      return _OpenAcctPymn == null ? defaultValue : _OpenAcctPymn;
   }
                  
   /**
    * Gets the Source of Funds Identified field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Source of Funds Identified or null.
    */
   public final String getFundScrlIdentified()
   {
      return _FundScrlIdentified;
   }
	
   /**
    * Gets the Source of Funds Identified field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Source of Funds Identified or the specified default value.
    */
   public final String getFundScrlIdentified( String defaultValue )
   {
      return _FundScrlIdentified == null ? defaultValue : _FundScrlIdentified;
   }
                  
   /**
    * Gets the Power of attorney field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Power of attorney or null.
    */
   public final String getPowOfAtt()
   {
      return _PowOfAtt;
   }
	
   /**
    * Gets the Power of attorney field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Power of attorney or the specified default value.
    */
   public final String getPowOfAtt( String defaultValue )
   {
      return _PowOfAtt == null ? defaultValue : _PowOfAtt;
   }
                  
   /**
    * Gets the Compliance Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Compliance Code or null.
    */
   public final String getComplianceCode()
   {
      return _ComplianceCode;
   }
	
   /**
    * Gets the Compliance Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Compliance Code or the specified default value.
    */
   public final String getComplianceCode( String defaultValue )
   {
      return _ComplianceCode == null ? defaultValue : _ComplianceCode;
   }
                  
   /**
    * Gets the ID of the Regulatory Standard field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the ID of the Regulatory Standard or null.
    */
   public final String getComplyCodeID()
   {
      return _ComplyCodeID;
   }
	
   /**
    * Gets the ID of the Regulatory Standard field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID of the Regulatory Standard or the specified default value.
    */
   public final String getComplyCodeID( String defaultValue )
   {
      return _ComplyCodeID == null ? defaultValue : _ComplyCodeID;
   }
                  
   /**
    * Gets the Country Code of the Regulation Standard field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Country Code of the Regulation Standard or null.
    */
   public final String getReguLatoryCntryCode()
   {
      return _ReguLatoryCntryCode;
   }
	
   /**
    * Gets the Country Code of the Regulation Standard field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code of the Regulation Standard or the specified default value.
    */
   public final String getReguLatoryCntryCode( String defaultValue )
   {
      return _ReguLatoryCntryCode == null ? defaultValue : _ReguLatoryCntryCode;
   }
                  
   /**
    * Gets the Number Of Dependants field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Number Of Dependants or null.
    */
   public final Integer getNumOfDependants()
   {
      return _NumOfDependants;
   }
	
   /**
    * Gets the Number Of Dependants field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Number Of Dependants or the specified default value.
    */
   public final int getNumOfDependants( int defaultValue )
   {
      return _NumOfDependants == null ? defaultValue : _NumOfDependants.intValue();
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName1()
   {
      return _AssociateCorpName1;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName1( String defaultValue )
   {
      return _AssociateCorpName1 == null ? defaultValue : _AssociateCorpName1;
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName2()
   {
      return _AssociateCorpName2;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName2( String defaultValue )
   {
      return _AssociateCorpName2 == null ? defaultValue : _AssociateCorpName2;
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName3()
   {
      return _AssociateCorpName3;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName3( String defaultValue )
   {
      return _AssociateCorpName3 == null ? defaultValue : _AssociateCorpName3;
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName4()
   {
      return _AssociateCorpName4;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName4( String defaultValue )
   {
      return _AssociateCorpName4 == null ? defaultValue : _AssociateCorpName4;
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName5()
   {
      return _AssociateCorpName5;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName5( String defaultValue )
   {
      return _AssociateCorpName5 == null ? defaultValue : _AssociateCorpName5;
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName6()
   {
      return _AssociateCorpName6;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName6( String defaultValue )
   {
      return _AssociateCorpName6 == null ? defaultValue : _AssociateCorpName6;
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName7()
   {
      return _AssociateCorpName7;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName7( String defaultValue )
   {
      return _AssociateCorpName7 == null ? defaultValue : _AssociateCorpName7;
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName8()
   {
      return _AssociateCorpName8;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName8( String defaultValue )
   {
      return _AssociateCorpName8 == null ? defaultValue : _AssociateCorpName8;
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName9()
   {
      return _AssociateCorpName9;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName9( String defaultValue )
   {
      return _AssociateCorpName9 == null ? defaultValue : _AssociateCorpName9;
   }
                  
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Associate Corporate Name or null.
    */
   public final String getAssociateCorpName10()
   {
      return _AssociateCorpName10;
   }
	
   /**
    * Gets the Associate Corporate Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Associate Corporate Name or the specified default value.
    */
   public final String getAssociateCorpName10( String defaultValue )
   {
      return _AssociateCorpName10 == null ? defaultValue : _AssociateCorpName10;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp1()
   {
      return _RoleInCorp1;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp1( String defaultValue )
   {
      return _RoleInCorp1 == null ? defaultValue : _RoleInCorp1;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp2()
   {
      return _RoleInCorp2;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp2( String defaultValue )
   {
      return _RoleInCorp2 == null ? defaultValue : _RoleInCorp2;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp3()
   {
      return _RoleInCorp3;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp3( String defaultValue )
   {
      return _RoleInCorp3 == null ? defaultValue : _RoleInCorp3;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp4()
   {
      return _RoleInCorp4;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp4( String defaultValue )
   {
      return _RoleInCorp4 == null ? defaultValue : _RoleInCorp4;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp5()
   {
      return _RoleInCorp5;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp5( String defaultValue )
   {
      return _RoleInCorp5 == null ? defaultValue : _RoleInCorp5;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp6()
   {
      return _RoleInCorp6;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp6( String defaultValue )
   {
      return _RoleInCorp6 == null ? defaultValue : _RoleInCorp6;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp7()
   {
      return _RoleInCorp7;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp7( String defaultValue )
   {
      return _RoleInCorp7 == null ? defaultValue : _RoleInCorp7;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp8()
   {
      return _RoleInCorp8;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp8( String defaultValue )
   {
      return _RoleInCorp8 == null ? defaultValue : _RoleInCorp8;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp9()
   {
      return _RoleInCorp9;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp9( String defaultValue )
   {
      return _RoleInCorp9 == null ? defaultValue : _RoleInCorp9;
   }
                  
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Corporate Role or null.
    */
   public final String getRoleInCorp10()
   {
      return _RoleInCorp10;
   }
	
   /**
    * Gets the Corporate Role field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Corporate Role or the specified default value.
    */
   public final String getRoleInCorp10( String defaultValue )
   {
      return _RoleInCorp10 == null ? defaultValue : _RoleInCorp10;
   }
                  
   /**
    * Gets the Suppress KYC Letter field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Suppress KYC Letter or null.
    */
   public final Boolean getSuppressKYCLetter()
   {
      return _SuppressKYCLetter;
   }
	
   /**
    * Gets the Suppress KYC Letter field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Suppress KYC Letter or the specified default value.
    */
   public final boolean getSuppressKYCLetter( boolean defaultValue )
   {
      return _SuppressKYCLetter == null ? defaultValue : _SuppressKYCLetter.booleanValue();
   }
                  
   /**
    * Gets the Code of the Regulatory Standard field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Code of the Regulatory Standard or null.
    */
   public final String getComplyCode()
   {
      return _ComplyCode;
   }
	
   /**
    * Gets the Code of the Regulatory Standard field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Code of the Regulatory Standard or the specified default value.
    */
   public final String getComplyCode( String defaultValue )
   {
      return _ComplyCode == null ? defaultValue : _ComplyCode;
   }
                  
   /**
    * Gets the KYC Information format code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the KYC Information format code or null.
    */
   public final String getKYCInfoFormatCode()
   {
      return _KYCInfoFormatCode;
   }
	
   /**
    * Gets the KYC Information format code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KYC Information format code or the specified default value.
    */
   public final String getKYCInfoFormatCode( String defaultValue )
   {
      return _KYCInfoFormatCode == null ? defaultValue : _KYCInfoFormatCode;
   }
                  
   /**
    * Gets the KYC Information format description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the KYC Information format description or null.
    */
   public final String getKYCInfoFormatDesc()
   {
      return _KYCInfoFormatDesc;
   }
	
   /**
    * Gets the KYC Information format description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KYC Information format description or the specified default value.
    */
   public final String getKYCInfoFormatDesc( String defaultValue )
   {
      return _KYCInfoFormatDesc == null ? defaultValue : _KYCInfoFormatDesc;
   }
                  
   /**
    * Gets the Profile Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Profile Number or null.
    */
   public final String getProfileNum()
   {
      return _ProfileNum;
   }
	
   /**
    * Gets the Profile Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Profile Number or the specified default value.
    */
   public final String getProfileNum( String defaultValue )
   {
      return _ProfileNum == null ? defaultValue : _ProfileNum;
   }
                  
   /**
    * Gets the Reference Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Reference Number or null.
    */
   public final String getRefNumber()
   {
      return _RefNumber;
   }
	
   /**
    * Gets the Reference Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reference Number or the specified default value.
    */
   public final String getRefNumber( String defaultValue )
   {
      return _RefNumber == null ? defaultValue : _RefNumber;
   }
                  
   /**
    * Gets the Profile Value field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Profile Value or null.
    */
   public final String getProfileVal()
   {
      return _ProfileVal;
   }
	
   /**
    * Gets the Profile Value field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Profile Value or the specified default value.
    */
   public final String getProfileVal( String defaultValue )
   {
      return _ProfileVal == null ? defaultValue : _ProfileVal;
   }
                  
   /**
    * Gets the KYC Last Review Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the KYC Last Review Date or null.
    */
   public final Date getLastReviewDate()
   {
      return _LastReviewDate;
   }
	
   /**
    * Gets the KYC Last Review Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the KYC Last Review Date or the specified default value.
    */
   public final Date getLastReviewDate( Date defaultValue )
   {
      return _LastReviewDate == null ? defaultValue : _LastReviewDate;
   }
                  
   /**
    * Gets the SolicitPublicContrib field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SolicitPublicContrib or null.
    */
   public final String getSolicitPublicContrib()
   {
      return _SolicitPublicContrib;
   }
	
   /**
    * Gets the SolicitPublicContrib field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SolicitPublicContrib or the specified default value.
    */
   public final String getSolicitPublicContrib( String defaultValue )
   {
      return _SolicitPublicContrib == null ? defaultValue : _SolicitPublicContrib;
   }
                  
   /**
    * Gets the InvReason field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the InvReason or null.
    */
   public final String getInvReason()
   {
      return _InvReason;
   }
	
   /**
    * Gets the InvReason field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the InvReason or the specified default value.
    */
   public final String getInvReason( String defaultValue )
   {
      return _InvReason == null ? defaultValue : _InvReason;
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
      _BirthDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _Gender = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaritalCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _MaritalDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _Employer = responseBuffer.decodeString(responseBuffer.getNextField());
      _EmployedYrs = responseBuffer.decodeString(responseBuffer.getNextField());
      _IndustryCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _IndustryDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _OccupationCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _OccupationDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _AnnualIncomeCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AnnualIncomeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _NetWorthCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _NetWorthDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvObjCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvObjDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvKnowledgeCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvKnowledgeDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvHorizonCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvHorizonDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _RiskToleranceCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _RiskToleranceDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _OtherInvestments = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _AdvisorCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _AdvisorDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _WitnessName = responseBuffer.decodeString(responseBuffer.getNextField());
      _WitnessAddr1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _WitnessAddr2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _EffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ProcessDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _PersonalSecCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _PrimMstrVer = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PrimMstrRid = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _InvestPhilosophy = responseBuffer.decodeString(responseBuffer.getNextField());
      _Occupation = responseBuffer.decodeString(responseBuffer.getNextField());
      _GrowthPercent = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _IncomePercent = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _SafetyPercent = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _RepBranch = responseBuffer.decodeString(responseBuffer.getNextField());
      _RepNo = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _SAMFInHealth = responseBuffer.decodeString(responseBuffer.getNextField());
      _TypeOfBusFreeFormat = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctModDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _AcctModUser = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctProcessDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _AcctRepBranch = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctRepNo = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _AcctUserName = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctKYCVer = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _UserName = responseBuffer.decodeString(responseBuffer.getNextField());
      _ModUser = responseBuffer.decodeString(responseBuffer.getNextField());
      _ModDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _MemorablePlace = responseBuffer.decodeString(responseBuffer.getNextField());
      _MemorableWord = responseBuffer.decodeString(responseBuffer.getNextField());
      _MemorableDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _KYCComment = responseBuffer.decodeString(responseBuffer.getNextField());
      _EmploymentType = responseBuffer.decodeString(responseBuffer.getNextField());
      _ResidenceType = responseBuffer.decodeString(responseBuffer.getNextField());
      _ResAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _KYCMailedDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _AnnualIncomeAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _IncomeLevelDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _NetWorthAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _NetWorthDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _RefferalCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ReferenceName = responseBuffer.decodeString(responseBuffer.getNextField());
      _SpecialtyCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _TolerancePrcnt = responseBuffer.decodeString(responseBuffer.getNextField());
      _ShortTermPrcnt = responseBuffer.decodeString(responseBuffer.getNextField());
      _AggressivePrcnt = responseBuffer.decodeString(responseBuffer.getNextField());
      _PrcntDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ShrKYCVer = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _KYCRID = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _InvestorType = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvestFor3rdPrty = responseBuffer.decodeString(responseBuffer.getNextField());
      _BusCntryCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _OpenAcctPymn = responseBuffer.decodeString(responseBuffer.getNextField());
      _FundScrlIdentified = responseBuffer.decodeString(responseBuffer.getNextField());
      _PowOfAtt = responseBuffer.decodeString(responseBuffer.getNextField());
      _ComplianceCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _ComplyCodeID = responseBuffer.decodeString(responseBuffer.getNextField());
      _ReguLatoryCntryCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _NumOfDependants = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _AssociateCorpName1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociateCorpName2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociateCorpName3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociateCorpName4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociateCorpName5 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociateCorpName6 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociateCorpName7 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociateCorpName8 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociateCorpName9 = responseBuffer.decodeString(responseBuffer.getNextField());
      _AssociateCorpName10 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp4 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp5 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp6 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp7 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp8 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp9 = responseBuffer.decodeString(responseBuffer.getNextField());
      _RoleInCorp10 = responseBuffer.decodeString(responseBuffer.getNextField());
      _SuppressKYCLetter = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _ComplyCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _KYCInfoFormatCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _KYCInfoFormatDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProfileNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _RefNumber = responseBuffer.decodeString(responseBuffer.getNextField());
      _ProfileVal = responseBuffer.decodeString(responseBuffer.getNextField());
      _LastReviewDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _SolicitPublicContrib = responseBuffer.decodeString(responseBuffer.getNextField());
      _InvReason = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
