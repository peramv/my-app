//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DemographicsDlg.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : 3/99
//
// ----------------------------------------------------------
//
// ^CLASS    : DemographicsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Demographics dialog
//
//******************************************************************************

#include "stdafx.h"

#include <assert.h>
#include "mfdstc.h"
#include "DemographicsDlg.h"
#include <ifastbp\DemographicsProcessIncludes.h>
#include <ifastgui\ifasthistoricalinfo.hpp>
#include <uibase\dsttabctrl.h>
#include <ConfigManager.hpp>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\BranchProcessIncludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_DEMOGRAPHICS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REG_DOCUMENT_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_KYC_BROKER;


#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< DemographicsDlg > dlgCreator( CMD_GUI_DEMOGRAPHICS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef DSTCFUNCS_H
   #include <uibase\DstcFuncs.h>
#endif

#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>

#include <uibase\DSTComboBox.h>
#include <uibase\DSTEdit.h>
#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\BrokerList.hpp>
#include <ifastcbo\Broker.hpp>

namespace
{
   const I_CHAR *CLASSNAME                      = I_( "DemographicsDlg" );
   const I_CHAR * const FULL_REFRESH            = I_( "FullRefresh" );
   const I_CHAR * const PARTIAL_REFRESH         = I_( "PartialRefresh" );
   const int MAX_YEARS_EMPLOYED                 = 4; // The maximum length of years employed
   const int MAX_PERSONAL_SEC_CODE              = 4; // The maximum length of personal sec code
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const PERCENTAGE_CHARACTERS   = I_("0123456789");

   const I_CHAR * const ACCOUNT_NUM             = I_( "AccountNum" );
   const I_CHAR * const ENTITY_ID               = I_( "EntityId" );
   const I_CHAR * const CALLER                  = I_( "Caller" );
   const I_CHAR * const ENTITY                  = I_( "Entity" );
   const I_CHAR * const ACCTCOA                 = I_( "AcctCOA" );
   const I_CHAR * const REGSTANDARD             = I_( "RegulatoryStandard" );
   const I_CHAR * const PRIMARY                 = I_("1");
}

namespace KYC_CONTROLS
{
   const int MEMORABLE_DATA         = 1;
   const int WITNESS_DETAILS        = 2;
   const int EMPL_INFO              = 3;
   const int OBJECTIVES             = 4;
   const int INV_PROFILE            = 5;
   const int HOUSE_BROKER           = 6;
   const int COMPANY                = 7;
   const int AML                    = 8;
   const int SOURCE_OF_PAYMENT_AML  = 9;
   const int MISC                   = 10;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId WitnessAddr;
   extern CLASS_IMPORT const BFDecimalFieldId TotPercentage;
   extern CLASS_IMPORT const BFTextFieldId KYCLevel;   
   extern CLASS_IMPORT const BFTextFieldId KYCRequired;
   extern CLASS_IMPORT const BFTextFieldId HouseBroker;
   extern CLASS_IMPORT const BFTextFieldId AgentCode;
   extern CLASS_IMPORT const BFTextFieldId RegDocsExist;
   extern CLASS_IMPORT const BFTextFieldId SuppressKYCLetter;
   extern CLASS_IMPORT const BFTextFieldId NumOfDependents;
   extern CLASS_IMPORT const BFTextFieldId AssociateCorpName1;
   extern CLASS_IMPORT const BFTextFieldId AssociateCorpName2;
   extern CLASS_IMPORT const BFTextFieldId AssociateCorpName3;
   extern CLASS_IMPORT const BFTextFieldId AssociateCorpName4;
   extern CLASS_IMPORT const BFTextFieldId AssociateCorpName5;
   extern CLASS_IMPORT const BFTextFieldId AssociateCorpName6;
   extern CLASS_IMPORT const BFTextFieldId RoleInCorp1;
   extern CLASS_IMPORT const BFTextFieldId RoleInCorp2;
   extern CLASS_IMPORT const BFTextFieldId RoleInCorp3;
   extern CLASS_IMPORT const BFTextFieldId RoleInCorp4;
   extern CLASS_IMPORT const BFTextFieldId RoleInCorp5;
   extern CLASS_IMPORT const BFTextFieldId RoleInCorp6;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtSalary;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtBusinessIncome;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtBorrowedFunds;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtGiftedFunds;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtPrcdsFrmDeathBenefEstate;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtSocialBenefits;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtOther;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtOtherReason;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtExistingInvstAccount;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtOwnerSavings;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtSaleOfProperty;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtPensionIncome;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtInheritedFunds;
   extern CLASS_IMPORT const BFTextFieldId SolicitPublicContrib;
   extern CLASS_IMPORT const BFTextFieldId KYCBusinessType;
   extern CLASS_IMPORT const BFTextFieldId KYCLegalForm;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const DEMOGRAPHICS;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Public members
//******************************************************************************
DemographicsDlg::DemographicsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( DemographicsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_dstrKYCAccountLevel( NULL_STRING )
, m_bShowTabs( true )
, m_dstrEntityID( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(DemographicsDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
void DemographicsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(DemographicsDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(DemographicsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(DemographicsDlg)
//	ON_BN_CLICKED(IDC_BTN_CHANGE, OnBtnChange)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADMIN, OnBtnAdmin)
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical)
ON_BN_CLICKED( IDC_BTN_DOCLIST, OnBtnDocList)
ON_BN_CLICKED( IDC_BTN_BROKER, OnBtnBroker)
ON_MESSAGE( UM_OPENBRANCHLISTDLG, OpenBranchListDlg )
ON_EN_KILLFOCUS(IDC_EDT_PROFILE_NUMBER, OnKillfocusEdtProfileNumber)
ON_EN_KILLFOCUS(IDC_EDT_REF_NUMBER, OnKillfocusEdtRefNumber)
ON_EN_KILLFOCUS(IDC_EDT_PROFILE_VALUE, OnKillfocusEdtProfileValue)
ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_IS_SOLICITING_CORP, IDC_CHK_PENSIONINCOME, OnCheckBoxClickByRange)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// DemographicsDlg message handlers
//******************************************************************************
BOOL DemographicsDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

//   SetDlgItemText(IDCANCEL, I_("Cancel"));
   GetDlgItem(IDOK)->ShowWindow(true);
   GetDlgItem(IDOK)->EnableWindow(true);
   //GetDlgItem(IDC_DTP_EFF_DATE)->ShowWindow(SW_SHOW);

   AddControl(CTRL_COMBO,IDC_CMB_OBJECTIVE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::InvObjCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST); 
   AddControl(CTRL_COMBO,IDC_CMB_KNOWLEDGE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::InvKnowledgeCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_HORIZON, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::InvHorizonCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_RISK_TOLERANCE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RiskToleranceCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_INCOME_LEVEL, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AnnualIncomeCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_NET_WORTH, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::NetWorthCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_MARITAL_STATUS, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::MaritalCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_OTHER_INVEST, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::OtherInvestments, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_PRIOR_INV_ADVISOR, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AdvisorCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_INDUSTRY, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::IndustryCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_OCUPATION, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::OccupationCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_KYC_BUSINESS_TYPE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::KYCBusinessType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_KYC_LEGAL_FORM, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::KYCLegalForm, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   AddControl(CTRL_COMBO,IDC_CMB_INVPHILOSOPHY, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::InvestPhilosophyCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_EDIT,IDC_EDT_OCCUPATIONFREEFMT, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::OccupationFreeFormat);
   AddControl(CTRL_COMBO,IDC_CMB_SAMFINHEALTH, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::SAMFinHealthCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   //AddControl(CTRL_COMBO,IDC_CMB_TYPEOFBUS, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::TypeOfBusFreeFormat, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   AddControl(CTRL_EDIT,IDC_EDT_GROWTHPCNT, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::GrowthPercent);
   AddControl(CTRL_EDIT,IDC_EDT_SAFETYPCNT, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::SafetyPercent);
   AddControl(CTRL_EDIT,IDC_EDT_INCOMEPCNT, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::IncomePercent);
   AddControl(CTRL_STATIC,IDC_STA_TOTALPCNT,BF::NullContainerId,ifds::TotPercentage );

   AddControl(CTRL_EDIT,IDC_EDT_EMPL_NAME, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::Employer);
   AddControl(CTRL_EDIT,IDC_EDT_YEARS_EMPL, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::EmployedYrs);

   // Witness
   AddControl(CTRL_EDIT,IDC_EDT_WITNESS_NAME, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::WitnessName);
   AddControl(CTRL_EDIT,IDC_EDT_WITNESS_ADDR, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::WitnessAddr,CTRLFLAG_FIELDS_FROM_SUB_LIST);
   AddControl(CTRL_EDIT,IDC_EDT_PERS_SEC_CODE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::PersonalSecCode);

   // Memorable Data
   AddControl(CTRL_EDIT, IDC_EDT_MEMORABLE_WORD, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::MemorableWord);
   (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MEMORABLE_WORD)))->SetMaxCharNum( 40 );
   AddControl(CTRL_EDIT, IDC_EDT_MEMORABLE_PLACE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::MemorablePlace);
   (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MEMORABLE_PLACE)))->SetMaxCharNum( 40 );
   AddControl(CTRL_DATE, IDC_DTP_MEMORABLE_DATE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::MemorableDate);

   // Misc
   AddControl(CTRL_EDIT,IDC_EDT_COMMENTS, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::KYCComment);
   AddControl(CTRL_DATE,IDC_DTP_KYC_DATE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::KYCMailedDate);
   AddControl(CTRL_COMBO,IDC_CMB_KYCLETTER, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::SuppressKYCLetter, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   AddControl(CTRL_EDIT,IDC_EDT_TOLERANCE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::TolerancePrcnt);
   AddControl(CTRL_EDIT,IDC_EDT_SHORT_TERM, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::ShortTermPrcnt);
   AddControl(CTRL_EDIT,IDC_EDT_AGGRESSIVE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AggressivePrcnt);
   AddControl(CTRL_COMBO,IDC_CMB_EMPL_TYPE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::EmploymentType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_SPECIALTY_CODE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::SpecialtyCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_RES_TYPE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::ResidenceType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_EDIT,IDC_EDT_RES_AMOUNT, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::ResAmount);
   AddControl(CTRL_COMBO,IDC_CMB_REFERRAL_CODE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RefferalCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_EDIT,IDC_EDT_INCOME_LEVEL, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AnnualIncomeAmount);
   AddControl(CTRL_DATE,IDC_DTP_INCOME_LEVEL, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::IncomeLevelDate);
   AddControl(CTRL_EDIT,IDC_EDT_NET_WORTH, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::NetWorthAmount);
   AddControl(CTRL_DATE,IDC_DTP_NET_WORTH, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::NetWorthDate);
   AddControl(CTRL_EDIT,IDC_EDT_REFERENCE_NAME, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::ReferenceName);
   AddControl(CTRL_DATE,IDC_DTP_PRCNT_DATE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::PrcntDate);
   AddControl(CTRL_COMBO,IDC_CMB_KYC_INFO_FORMAT, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::KYCInfoFormat, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_EDIT,IDC_EDT_PROFILE_NUMBER, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::ProfileNum);
   AddControl(CTRL_EDIT,IDC_EDT_REF_NUMBER, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RefNum);
   AddControl(CTRL_EDIT,IDC_EDT_PROFILE_VALUE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::ProfileValue);   
   AddControl(CTRL_DATE,IDC_DTP_LAST_REVIEW_DATE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::LastReviewDate);

   // KYC AML
   AddControl(CTRL_COMBO,IDC_CMB_TYPEOFINVESTOR, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::TypeOfInvestor, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_INV3PARTY, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::InvestingOnBehalf, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_SOURCEOFFUNDS, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::SourceOfIncome, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_EDIT,IDC_EDT_PAYMENTMETHOD, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::InitialPayment);
   AddControl(CTRL_COMBO,IDC_CMB_POWEROFATTORNEY, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::PowerOfAttorney, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_EDIT,IDC_EDT_COMPCODE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::ComplianceCode);
   AddControl(CTRL_COMBO,IDC_CMB_REGSTANDARDS, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RegulatoryStandard,CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_COMBO,IDC_CMB_COUNTRY, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::CountryCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   AddControl(CTRL_EDIT,IDC_EDT_NUMOFDEPENDENTS, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::NumOfDependents );
   AddControl(CTRL_EDIT,IDC_EDT_INDUSTRYOTHER, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::TypeOfBusFreeFormat );

   // Associate company
   AddControl(CTRL_EDIT,IDC_EDT_COMPANY1, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AssociateCorpName1 );
   AddControl(CTRL_EDIT,IDC_EDT_COMPANY2, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AssociateCorpName2 );
   AddControl(CTRL_EDIT,IDC_EDT_COMPANY3, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AssociateCorpName3 );
   AddControl(CTRL_EDIT,IDC_EDT_COMPANY4, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AssociateCorpName4 );
   AddControl(CTRL_EDIT,IDC_EDT_COMPANY5, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AssociateCorpName5 );
   AddControl(CTRL_EDIT,IDC_EDT_COMPANY6, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AssociateCorpName6 );

   AddControl(CTRL_COMBO,IDC_CMB_ROLE1, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RoleInCorp1, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_ROLE2, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RoleInCorp2, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_ROLE3, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RoleInCorp3, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_ROLE4, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RoleInCorp4, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_ROLE5, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RoleInCorp5, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_ROLE6, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::RoleInCorp6, CTRLFLAG_INITCOMBO_BY_SUB_LIST );

   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_GROWTHPCNT ) ) )->SetAllowedChars( PERCENTAGE_CHARACTERS );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_INCOMEPCNT ) ) )->SetAllowedChars( PERCENTAGE_CHARACTERS );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_SAFETYPCNT ) ) )->SetAllowedChars( PERCENTAGE_CHARACTERS );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_AGGRESSIVE ) ) )->SetAllowedChars( PERCENTAGE_CHARACTERS );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_SHORT_TERM ) ) )->SetAllowedChars( PERCENTAGE_CHARACTERS );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_TOLERANCE  ) ) )->SetAllowedChars( PERCENTAGE_CHARACTERS );

   // AIM KYC Phase 02
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_NUMOFDEPENDENTS ) ) )->SetAllowedChars( PERCENTAGE_CHARACTERS );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_COMPANY1 ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_COMPANY2 ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_COMPANY3 ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_COMPANY4 ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_COMPANY5 ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_COMPANY6 ) ) )->SetMaxCharNum( 40 );
   
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_PROFILE_NUMBER ) ) )->SetMaxCharNum( 9 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_REF_NUMBER ) ) )->SetMaxCharNum( 10 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_PROFILE_VALUE ) ) )->SetMaxCharNum( 3 );   

   //Move to Admin
   //AddControl(CTRL_STATIC,IDC_TXT_PROCESS_DATE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::ProcessDate);
   AddControl(CTRL_DATE,IDC_DTP_EFF_DATE, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::EffectiveDate);

   DString dstrHouseBroker;
   getParent()->getField ( this, ifds::HouseBroker, dstrHouseBroker, false );

   bool bShow = dstrHouseBroker == YES;

   showHouseControls ( bShow && m_bShowTabs );

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   if(dstWorkSession) 
      dstWorkSession->getOption( ifds::KYCLevel, m_dstrKYCAccountLevel, BF::HOST, false );

   // additional KYC for SLF-AML
   AddControl( CTRL_CHECKBOX,IDC_CHK_IS_SOLICITING_CORP,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SolicitPublicContrib);
   AddControl( CTRL_CHECKBOX,IDC_CHK_SALARY,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtSalary);
   AddControl( CTRL_CHECKBOX,IDC_CHK_BUSINESSINCOME,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtBusinessIncome);
   AddControl( CTRL_CHECKBOX,IDC_CHK_BORROWEDFUNDS,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtBorrowedFunds);
   AddControl( CTRL_CHECKBOX,IDC_CHK_GIFTEDFUNDS,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtGiftedFunds);
   AddControl( CTRL_CHECKBOX,IDC_CHK_PRCDSFRMDEATHBENEFESTATE,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtPrcdsFrmDeathBenefEstate);
   AddControl( CTRL_CHECKBOX,IDC_CHK_SOCIALBENEFITS,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtSocialBenefits);
   AddControl( CTRL_CHECKBOX,IDC_CHK_EXISTINGINVSTACCOUNT,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtExistingInvstAccount);
   AddControl( CTRL_CHECKBOX,IDC_CHK_OWNERSAVINGS,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtOwnerSavings);
   AddControl( CTRL_CHECKBOX,IDC_CHK_SALEOFPROPERTY,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtSaleOfProperty);
   AddControl( CTRL_CHECKBOX,IDC_CHK_PENSIONINCOME,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtPensionIncome);
   AddControl( CTRL_CHECKBOX,IDC_CHK_INHERITEDFUNDS,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtInheritedFunds);
   AddControl( CTRL_CHECKBOX,IDC_CHK_OTHER,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtOther);
   AddControl( CTRL_EDIT,IDC_EDT_OTHERREASON,IFASTBP_PROC::DEMOGRAPHICS_CBO,ifds::SrcOfPymtOtherReason);

   (dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_OTHERREASON)))->SetMaxCharNum( 200 );

   addStaticControls (bShow);
   registerTabControls (bShow);

   ConnectControlsToData();
   LoadControls();

   ShowTabCtrl (IDC_TAB_KYC, true);
   LoadTabControl (IDC_TAB_KYC);

// GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow(false);
// UpdateData(FALSE);

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void DemographicsDlg::addStaticControls (bool bShow) 
{
   // Memorable Data:
   AddControl (CTRL_STATIC, IDC_STC_MEM_WORD,   CTRLFLAG_GUI_FIELD, KYC_CONTROLS::MEMORABLE_DATA);
   AddControl (CTRL_STATIC, IDC_STC_MEM_PLACE,  CTRLFLAG_GUI_FIELD, KYC_CONTROLS::MEMORABLE_DATA);
   AddControl (CTRL_STATIC, IDC_STC_MEM_DATE,   CTRLFLAG_GUI_FIELD, KYC_CONTROLS::MEMORABLE_DATA);

   // Witness Details
   AddControl(CTRL_STATIC, IDC_STC_WITNESS_NAME,      CTRLFLAG_GUI_FIELD, KYC_CONTROLS::WITNESS_DETAILS);
   AddControl(CTRL_STATIC, IDC_STC_WITNESS_ADDR,      CTRLFLAG_GUI_FIELD, KYC_CONTROLS::WITNESS_DETAILS);
   AddControl(CTRL_STATIC, IDC_STC_PERS_SEC_CODE,     CTRLFLAG_GUI_FIELD, KYC_CONTROLS::WITNESS_DETAILS); 
   AddControl(CTRL_STATIC, IDC_STC_WITNESS_EFF_DATE,  CTRLFLAG_GUI_FIELD, KYC_CONTROLS::WITNESS_DETAILS);

   // Employment Info
   AddControl(CTRL_STATIC, IDC_STC_EMPL_NAME,      CTRLFLAG_GUI_FIELD, KYC_CONTROLS::EMPL_INFO);
   AddControl(CTRL_STATIC, IDC_STC_INDUSTRY,       CTRLFLAG_GUI_FIELD, KYC_CONTROLS::EMPL_INFO);
   AddControl(CTRL_STATIC, IDC_STC_OCCUPATION,     CTRLFLAG_GUI_FIELD, KYC_CONTROLS::EMPL_INFO); 
   AddControl(CTRL_STATIC, IDC_STC_EMPL_TYPE,      CTRLFLAG_GUI_FIELD, KYC_CONTROLS::EMPL_INFO);
   AddControl(CTRL_STATIC, IDC_STC_YEARS_EMPL,     CTRLFLAG_GUI_FIELD, KYC_CONTROLS::EMPL_INFO);
   AddControl(CTRL_STATIC, IDC_STC_SPECIALTY_CODE, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::EMPL_INFO);
   AddControl(CTRL_STATIC, IDC_STC_KYC_BUSINESS_TYPE, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::EMPL_INFO);
   AddControl(CTRL_STATIC, IDC_STC_KYC_LEGAL_FORM, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::EMPL_INFO);

   // Investment Profile:
   AddControl(CTRL_STATIC, IDC_STC_TYPE_BUS,       CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_KNOWLEDGE,      CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_INV_PHILOSOPHY, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE); 
   AddControl(CTRL_STATIC, IDC_STC_INCOME_LEVEL,   CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_NET_WORTH,      CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_MARITAL_STATUS, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_OTHER_INV,      CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_PRIOR_ADVISOR,  CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_SAM_HEALTH,     CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);

   AddControl(CTRL_STATIC, IDC_STC_INCOME_GROUP,   CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_NETWORTH_GROUP, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_RES_TYPE,       CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_RES_AMOUNT,     CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_REFERRAL_CODE,  CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_ANNUAL_INCOME,  CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_INCOME_DATE,    CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_TOTAL_NETWORTH, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_NETWORHT_DATE,  CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);
   AddControl(CTRL_STATIC, IDC_STC_REFERENCE_NAME, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);

   // Objectives:
   AddControl(CTRL_STATIC, IDC_STC_OBJECTIVE,      CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_HORIZON,        CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_RISK_TOLERANCE, CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_TOLERANCE_PRCNT,CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_GROWTH_PRCT,        CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_SHORTTR_PRCNT,  CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_INCOME_PRCT,    CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_AGGRESIVE,      CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_SAFETY_PRCT,    CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_TOTAL_PRCT,     CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);

   AddControl(CTRL_STATIC, IDC_STC_TOL_PRCNT,      CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_SHORT_TR_PRCNT, CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_AGGRESIVE_PRCNT,CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);

   AddControl(CTRL_STATIC, IDC_STC1,               CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC2,               CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC3,               CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_ST4,                CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_PRCNT_DATE,     CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_ACCOUNT_LEVEL,  CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   if ( m_dstrKYCAccountLevel != I_( "03" ) )
   {
      ShowControl( IDC_STC_ACCOUNT_LEVEL, false );
   }
   AddControl(CTRL_STATIC, IDC_STC_KYC_INFO_FORMAT,  CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_PROFILE_NUMBER,   CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_REF_NUMBER,       CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_PROFILE_VALUE,    CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);
   AddControl(CTRL_STATIC, IDC_STC_LAST_REVIEW_DATE, CTRLFLAG_GUI_FIELD,  KYC_CONTROLS::OBJECTIVES);            
   // Misc:
   AddControl(CTRL_STATIC, IDC_STC_COMMENTS,    CTRLFLAG_GUI_FIELD, KYC_CONTROLS::MISC );
   AddControl(CTRL_STATIC, IDC_STC_MAILED,      CTRLFLAG_GUI_FIELD, KYC_CONTROLS::MISC);
   AddControl(CTRL_STATIC, IDC_STC_KYCLETTER,   CTRLFLAG_GUI_FIELD, KYC_CONTROLS::MISC);

   // KYC AML  
   AddControl(CTRL_STATIC, IDC_STC_TYPEOFINVESTOR,    CTRLFLAG_GUI_FIELD, KYC_CONTROLS::AML);
   AddControl(CTRL_STATIC, IDC_STC_INV3RDPARTY,       CTRLFLAG_GUI_FIELD, KYC_CONTROLS::AML);
   AddControl(CTRL_STATIC, IDC_STC_SOURCEOFFUNDS,     CTRLFLAG_GUI_FIELD, KYC_CONTROLS::AML );
   AddControl(CTRL_STATIC, IDC_STC_PAYMENTMETHOD,     CTRLFLAG_GUI_FIELD, KYC_CONTROLS::AML);
   AddControl(CTRL_STATIC, IDC_STC_POWEROFATTORNEY,   CTRLFLAG_GUI_FIELD, KYC_CONTROLS::AML );
   AddControl(CTRL_STATIC, IDC_STC_COMPCODE,          CTRLFLAG_GUI_FIELD, KYC_CONTROLS::AML);
   AddControl(CTRL_STATIC, IDC_STC_REGSTANDARDS,      CTRLFLAG_GUI_FIELD, KYC_CONTROLS::AML );

   AddControl(CTRL_STATIC, IDC_STC_COUNTRY,           CTRLFLAG_GUI_FIELD, KYC_CONTROLS::AML );

   // AIM KYC Phase 02
   AddControl(CTRL_STATIC, IDC_STC_NUMOFDEPENDENTS,   CTRLFLAG_GUI_FIELD, KYC_CONTROLS::INV_PROFILE);

   AddControl(CTRL_STATIC, IDC_STC_COMPANY,           CTRLFLAG_GUI_FIELD, KYC_CONTROLS::COMPANY);
   AddControl(CTRL_STATIC, IDC_STC_ROLE,              CTRLFLAG_GUI_FIELD, KYC_CONTROLS::COMPANY);

   AddControl(CTRL_STATIC, IDC_STC_OTHERREASON,       CTRLFLAG_GUI_FIELD, KYC_CONTROLS::SOURCE_OF_PAYMENT_AML);

}
//******************************************************************************
void DemographicsDlg::registerTabControls (bool bShow) 
{
   DSTTabCtrl* pTabCtrl = AddTabControl(CLASSNAME, IDC_TAB_KYC, I_("KYCTab"));
   DString strMarket = DSTCommonFunctions::getMarket();
   if ( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )

   if (pTabCtrl)
   {
      if(strMarket == MARKET_IDS::LUXEMBOURG && m_bShowTabs )
      {
         pTabCtrl->AddTab (TXT_AML); 
      }

      pTabCtrl->AddTab (TXT_INV_PROFILE);
      pTabCtrl->AddTab (TXT_EMPL_INFO);

      if ( m_bShowTabs )
      {
         pTabCtrl->AddTab (TXT_INV_OBJECTIVES);
         pTabCtrl->AddTab (TXT_WITN_DETAILS);
         pTabCtrl->AddTab (TXT_MEMORABLE_DATA);
      }

      pTabCtrl->AddTab (TXT_ASSOC_COMPANY);

      if(strMarket == MARKET_IDS::CANADA && m_bShowTabs )
      {
         pTabCtrl->AddTab (TXT_AML); 
         pTabCtrl->AddTab (TXT_SOURCE_OF_PAYMENT_AML);
      }

      if ( m_bShowTabs )
         pTabCtrl->AddTab (TXT_MISC);

      // Investment Profile
      //pTabCtrl->registerControl (IDC_STC_TYPE_BUS,        TXT_INV_PROFILE);
      //pTabCtrl->registerControl (IDC_CMB_TYPEOFBUS,       TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_KNOWLEDGE,         TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_KNOWLEDGE,         TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_INV_PHILOSOPHY,    TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_INVPHILOSOPHY,     TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_INCOME_GROUP,      TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_INCOME_LEVEL,      TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_INCOME_LEVEL,      TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_ANNUAL_INCOME,     TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_EDT_INCOME_LEVEL,      TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_INCOME_DATE,       TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_DTP_INCOME_LEVEL,      TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_NETWORTH_GROUP,    TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_NET_WORTH,         TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_NET_WORTH,         TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_TOTAL_NETWORTH,    TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_EDT_NET_WORTH,         TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_NETWORHT_DATE,     TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_DTP_NET_WORTH,         TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_MARITAL_STATUS,    TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_MARITAL_STATUS,    TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_OTHER_INV,         TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_OTHER_INVEST,      TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_PRIOR_ADVISOR,     TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_PRIOR_INV_ADVISOR, TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_SAM_HEALTH,        TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_SAMFINHEALTH,      TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_RES_TYPE,          TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_RES_TYPE,          TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_RES_AMOUNT,        TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_EDT_RES_AMOUNT,        TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_REFERRAL_CODE,     TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_CMB_REFERRAL_CODE,     TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_REFERENCE_NAME,    TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_EDT_REFERENCE_NAME,    TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_STC_NUMOFDEPENDENTS,   TXT_INV_PROFILE);
      pTabCtrl->registerControl (IDC_EDT_NUMOFDEPENDENTS,   TXT_INV_PROFILE);


      // Employment Info
      pTabCtrl->registerControl (IDC_STC_EMPL_NAME,         TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_EDT_EMPL_NAME,         TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_STC_INDUSTRY,          TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_CMB_INDUSTRY,          TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_STC_OCCUPATION,        TXT_EMPL_INFO); 
      pTabCtrl->registerControl (IDC_CMB_OCUPATION,         TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_EDT_OCCUPATIONFREEFMT, TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_STC_EMPL_TYPE,         TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_CMB_EMPL_TYPE,         TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_STC_YEARS_EMPL,        TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_EDT_YEARS_EMPL,        TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_STC_SPECIALTY_CODE,    TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_CMB_SPECIALTY_CODE,    TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_EDT_INDUSTRYOTHER,     TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_STC_KYC_BUSINESS_TYPE, TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_CMB_KYC_BUSINESS_TYPE, TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_STC_KYC_LEGAL_FORM,    TXT_EMPL_INFO);
      pTabCtrl->registerControl (IDC_CMB_KYC_LEGAL_FORM,    TXT_EMPL_INFO);

      //Assoicated Company
      pTabCtrl->registerControl (IDC_STC_COMPANY,  TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_EDT_COMPANY1, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_EDT_COMPANY2, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_EDT_COMPANY3, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_EDT_COMPANY4, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_EDT_COMPANY5, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_EDT_COMPANY6, TXT_ASSOC_COMPANY );

      pTabCtrl->registerControl (IDC_STC_ROLE,  TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_CMB_ROLE1, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_CMB_ROLE2, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_CMB_ROLE3, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_CMB_ROLE4, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_CMB_ROLE5, TXT_ASSOC_COMPANY );
      pTabCtrl->registerControl (IDC_CMB_ROLE6, TXT_ASSOC_COMPANY );

      if ( !m_bShowTabs )
      {
         //hideControls();
         hideAML( true );
         hideInvObjective( true );
         hideWitness( true );
         hideMemorable( true );
         hideKYCMisc( true );
         hideHouseBroker( true );
         hideSourceOfPayment( true );
         return;
      }

      // Objectives 
      pTabCtrl->registerControl (IDC_STC_OBJECTIVE,         TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_CMB_OBJECTIVE,         TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_HORIZON,           TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_CMB_HORIZON,           TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_RISK_TOLERANCE,    TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_CMB_RISK_TOLERANCE,    TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_TOLERANCE_PRCNT,   TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_EDT_TOLERANCE,         TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_TOL_PRCNT,         TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_GROWTH_PRCT,           TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_EDT_GROWTHPCNT,        TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC1,                  TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_SHORTTR_PRCNT,     TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_EDT_SHORT_TERM,        TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_SHORT_TR_PRCNT,    TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_INCOME_PRCT,       TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_EDT_INCOMEPCNT,        TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC2,                  TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_AGGRESIVE,         TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_EDT_AGGRESSIVE,        TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_AGGRESIVE_PRCNT,   TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_SAFETY_PRCT,       TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_EDT_SAFETYPCNT,        TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC3,                  TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_TOTAL_PRCT,        TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STA_TOTALPCNT,         TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_ST4,                   TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_PRCNT_DATE,        TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_DTP_PRCNT_DATE,        TXT_INV_OBJECTIVES);
      pTabCtrl->registerControl (IDC_STC_KYC_INFO_FORMAT,   TXT_INV_OBJECTIVES);      
      pTabCtrl->registerControl (IDC_CMB_KYC_INFO_FORMAT,   TXT_INV_OBJECTIVES);      
      pTabCtrl->registerControl (IDC_STC_PROFILE_NUMBER,    TXT_INV_OBJECTIVES);      
      pTabCtrl->registerControl (IDC_EDT_PROFILE_NUMBER,    TXT_INV_OBJECTIVES);      
      pTabCtrl->registerControl (IDC_STC_REF_NUMBER,        TXT_INV_OBJECTIVES);            
      pTabCtrl->registerControl (IDC_EDT_REF_NUMBER,        TXT_INV_OBJECTIVES);       
      pTabCtrl->registerControl (IDC_STC_PROFILE_VALUE,     TXT_INV_OBJECTIVES);            
      pTabCtrl->registerControl (IDC_EDT_PROFILE_VALUE,     TXT_INV_OBJECTIVES);      
      pTabCtrl->registerControl (IDC_STC_LAST_REVIEW_DATE,  TXT_INV_OBJECTIVES);            
      pTabCtrl->registerControl (IDC_DTP_LAST_REVIEW_DATE,  TXT_INV_OBJECTIVES);       

      if ( m_dstrKYCAccountLevel == I_( "03" ) )
      {
         pTabCtrl->registerControl (IDC_STC_ACCOUNT_LEVEL, TXT_INV_OBJECTIVES);
      }

      // House Broker
      if (bShow)
      {
         pTabCtrl->AddTab (TXT_HOUSEBROKER);
         
         pTabCtrl->registerControl (IDC_STC_BRANCH,   TXT_HOUSEBROKER);
         pTabCtrl->registerControl (IDC_STC_SLSREP,   TXT_HOUSEBROKER);
         pTabCtrl->registerControl (IDC_EDT_BRANCH,   TXT_HOUSEBROKER); 
         pTabCtrl->registerControl (IDC_EDT_SLSREP,   TXT_HOUSEBROKER);
         pTabCtrl->registerControl (IDC_TXT_BRANCH,   TXT_HOUSEBROKER);
         pTabCtrl->registerControl (IDC_TXT_SLSREP,   TXT_HOUSEBROKER);
      }

      // Witness Details
      pTabCtrl->registerControl (IDC_STC_WITNESS_NAME,      TXT_WITN_DETAILS);
      pTabCtrl->registerControl (IDC_STC_WITNESS_ADDR,      TXT_WITN_DETAILS);
      pTabCtrl->registerControl (IDC_STC_PERS_SEC_CODE,     TXT_WITN_DETAILS); 
      pTabCtrl->registerControl (IDC_STC_WITNESS_EFF_DATE,  TXT_WITN_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_WITNESS_NAME,      TXT_WITN_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_WITNESS_ADDR,      TXT_WITN_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_PERS_SEC_CODE,     TXT_WITN_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_EFF_DATE,          TXT_WITN_DETAILS);

      // Memorable Data
      pTabCtrl->registerControl (IDC_STC_MEM_WORD,          TXT_MEMORABLE_DATA);
      pTabCtrl->registerControl (IDC_STC_MEM_PLACE,         TXT_MEMORABLE_DATA);
      pTabCtrl->registerControl (IDC_STC_MEM_DATE,          TXT_MEMORABLE_DATA);
      pTabCtrl->registerControl (IDC_EDT_MEMORABLE_WORD,    TXT_MEMORABLE_DATA);
      pTabCtrl->registerControl (IDC_EDT_MEMORABLE_PLACE,   TXT_MEMORABLE_DATA);
      pTabCtrl->registerControl (IDC_DTP_MEMORABLE_DATE,    TXT_MEMORABLE_DATA);

      // Misc
      pTabCtrl->registerControl (IDC_STC_COMMENTS,    TXT_MISC);
      pTabCtrl->registerControl (IDC_EDT_COMMENTS,    TXT_MISC);
      pTabCtrl->registerControl (IDC_STC_MAILED,      TXT_MISC);
      pTabCtrl->registerControl (IDC_DTP_KYC_DATE,    TXT_MISC);
      pTabCtrl->registerControl (IDC_STC_KYCLETTER,   TXT_MISC);
      pTabCtrl->registerControl (IDC_CMB_KYCLETTER,   TXT_MISC);

      //KYC AML 
      pTabCtrl->registerControl (IDC_STC_TYPEOFINVESTOR,    TXT_AML);
      pTabCtrl->registerControl (IDC_CMB_TYPEOFINVESTOR,    TXT_AML);
      pTabCtrl->registerControl (IDC_STC_INV3RDPARTY,       TXT_AML);
      pTabCtrl->registerControl (IDC_CMB_INV3PARTY,         TXT_AML);
      pTabCtrl->registerControl (IDC_STC_SOURCEOFFUNDS,     TXT_AML);
      pTabCtrl->registerControl (IDC_CMB_SOURCEOFFUNDS,     TXT_AML);
      pTabCtrl->registerControl (IDC_STC_PAYMENTMETHOD,     TXT_AML);
      pTabCtrl->registerControl (IDC_EDT_PAYMENTMETHOD,     TXT_AML);
      pTabCtrl->registerControl (IDC_STC_POWEROFATTORNEY,   TXT_AML);
      pTabCtrl->registerControl (IDC_CMB_POWEROFATTORNEY,   TXT_AML);
      pTabCtrl->registerControl (IDC_STC_COMPCODE,          TXT_AML);
      pTabCtrl->registerControl (IDC_EDT_COMPCODE,          TXT_AML);
      pTabCtrl->registerControl (IDC_CHK_IS_SOLICITING_CORP,TXT_AML);
      pTabCtrl->registerControl (IDC_STC_REGSTANDARDS,      TXT_AML);
      pTabCtrl->registerControl (IDC_CMB_REGSTANDARDS,      TXT_AML);
      pTabCtrl->registerControl (IDC_STC_COUNTRY,           TXT_AML);
      pTabCtrl->registerControl (IDC_CMB_COUNTRY,           TXT_AML);

      // source of payment
      
      pTabCtrl->registerControl (IDC_CHK_SALARY,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_BUSINESSINCOME,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_BORROWEDFUNDS,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_GIFTEDFUNDS,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_PRCDSFRMDEATHBENEFESTATE,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_SOCIALBENEFITS,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_EXISTINGINVSTACCOUNT,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_OWNERSAVINGS,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_SALEOFPROPERTY,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_PENSIONINCOME,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_INHERITEDFUNDS,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_CHK_OTHER,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_STC_OTHERREASON,    TXT_SOURCE_OF_PAYMENT_AML);
      pTabCtrl->registerControl (IDC_EDT_OTHERREASON,    TXT_SOURCE_OF_PAYMENT_AML);

   }
}

//******************************************************************************
void DemographicsDlg::OnBtnAdmin() 
{
   ShowAdminDates( IFASTBP_PROC::DEMOGRAPHICS_CBO );
}

//******************************************************************
void DemographicsDlg::OnBtnHistorical()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistorical" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   DString dstrShrNum, dstrAccountNum;

   // Get Shareholder Number
   getParent()->getField ( this, ifds::ShrNum, dstrShrNum, false );
   // Get KYCAccountLevel to determine whether Account Level KYC is required
   getParent()->getField( this, ifds::AccountNum, dstrAccountNum, false );

   setParameter(MFCAN_IP_PARAM::SHR_NUM, dstrShrNum);
   setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum);   

   IFastHistoricalInfo historicalInfo;
   if( m_dstrKYCAccountLevel == I_( "01" ) )
   {
      historicalInfo( this, BF::NullContainerId, I_( "KYC" ) );
   }
   else
   {
      historicalInfo( this, IFASTBP_PROC::DEMOGRAPHICS_CBO, I_("SINGLE") );
   }
}

//******************************************************************
void DemographicsDlg::OnBtnDocList()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDocList" ) );

   try
   {
      DString dstrEntityId,
         dstrAccountNum, 
         dstrRegStandard;

      getParent()->getField( this, ifds::AccountNum, dstrAccountNum, false );
      getParent()->getField( this, ifds::RegulatoryStandard, dstrRegStandard, false );

      MFAccount *pMFAccount = NULL;
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	
	  if ( dstWorkSession->getMFAccount (getDataGroupId(), dstrAccountNum, pMFAccount) <= WARNING  && 
          pMFAccount)
	  {
			pMFAccount->GetEntityIdForAcctOwnerSeq1 (getDataGroupId(), dstrEntityId);
	  }

      setParameter (ENTITY_ID, dstrEntityId);
      setParameter (ACCOUNT_NUM, dstrAccountNum); 
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_REG_DOCUMENT_LIST, PROC_SUPPORT, true, NULL );

      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************
void DemographicsDlg::OnBtnBroker()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDocList" ) );

	try
	{
		DString dstrAccountNum;

		getParent()->getField( this, ifds::AccountNum, dstrAccountNum, false );

		setParameter( ACCOUNT_NUM, dstrAccountNum ); 

		E_COMMANDRETURN eRtn; 
		eRtn = invokeCommand( getParent(), CMD_BPROC_KYC_BROKER, PROC_SUPPORT, true, NULL );

		switch( eRtn )
		{
			case CMD_OK:
			case CMD_CANCEL:
				break;
			case CMD_MODELESS_INPROCESS:
				break;
			default:
				// Display error
				ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
				break;
		}
	}
	catch( ConditionException &ce )
	{
		ConditionMessageBox( ce );
	}
	catch( ... )
	{
		DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
	}
}

//******************************************************************************
bool DemographicsDlg::GetDataForControl(
                                       UINT controlID,
                                       DString &strValueOut,
                                       bool bFormatted,
                                       int index
                                       ) const
{
   bool bRtn = false;

   switch( controlID )
   {
      
      case IDC_EDT_YEARS_EMPL:
         {
            getParent()->getField( this, ifds::EmployedYrs, strValueOut, false );
            double dValue = 0.0;
            dValue = DSTCommonFunctions::convertToDouble( strValueOut );
            strValueOut.strip().stripLeading( I_CHAR( '0' ) );
            if( strValueOut[0] == I_CHAR('.') )
            {
               strValueOut = I_("0") + strValueOut;
            }
            if( strValueOut.empty() || dValue == 0 )
            {
               strValueOut = I_( "0.00" );
            }
            bRtn = true;
         }
         break;

   }
   return(bRtn);
}

/************************* SetDataFromControl -- xyz added at 11/01/99 *******************/
bool DemographicsDlg::SetDataFromControl(
                                        UINT controlID,
                                        const DString &strValue,
                                        bool bFormatted,
                                        SEVERITY &sevRtn,
                                        int index
                                        )
{
   sevRtn = NO_CONDITION;
   return(false);
}

/********************************* OnPostInitDialog() **********************************/
void DemographicsDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::DEMOGRAPHICS);
   addControlGroupIDForPermissionCheck(0);

   DString dstrAccountNum, dstrShrNum, dstrEntityName;
   getParent()->getField( this, ifds::AccountNum,         dstrAccountNum );
   getParent()->getField( this, ifds::ShrNum,             dstrShrNum );
   getParent()->getField( this, PRIMARY_ACCOUNT_OWNER,    dstrEntityName );

   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_YEARS_EMPL ) ) )->
      SetMaxCharNum( MAX_YEARS_EMPLOYED );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_YEARS_EMPL ) ) )->
      SetAllowedChars(I_("0123456789."));


   dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_PERS_SEC_CODE ) )->
   SetMaxCharNum( MAX_PERSONAL_SEC_CODE );

   dynamic_cast<DSTEdit*>( GetControl( IDC_EDT_COMMENTS ) )->SetMaxCharNum( 200 );

   DisplayCaption();

   //IN2895115 - format allowed must be numeric only on KYC
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_PROFILE_NUMBER))->
	   SetAllowedChars (I_ ("0123456789"));
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_REF_NUMBER))->
	   SetAllowedChars (I_ ("0123456789"));
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_PROFILE_VALUE))->
	   SetAllowedChars (I_ ("0123456789"));

/**
   DString strMarket = DSTCommonFunctions::getMarket();
   if ( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      GetDlgItem( IDC_BTN_RESET )->ShowWindow( SW_SHOW );
   }
   else if ( strMarket == MARKET_IDS::JAPAN )
   {
      GetDlgItem( IDC_BTN_RESET )->ShowWindow( SW_HIDE );
   }
*/

   //set Account level caption
   DString dstrBrokerCode, dstrKYCRequired, AcctLevelCaption;

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();

   MFAccount * pMFAccount = NULL;
   if( ( dstWorkSession->getMFAccount( getDataGroupId(), dstrAccountNum, pMFAccount ) <= WARNING ) &&
       ( pMFAccount != NULL ) )
   {
      BrokerList* pBrokerList;
      dstWorkSession->getBrokerList(pBrokerList);
      if( pBrokerList )
      {
         pMFAccount->getField(ifds::BrokerCode, dstrBrokerCode,idDataGroup,false );
         dstrBrokerCode.strip();
         Broker*  pBroker;
         pBrokerList->getBroker(dstrBrokerCode, pBroker);
         if(pBroker )
            pBroker->getField( ifds::KYCRequired, dstrKYCRequired, idDataGroup, false);
      }
   }

   DString dstrRegDocsExist;
   if(dstWorkSession) 
      dstWorkSession->getOption( ifds::RegDocsExist, dstrRegDocsExist, BF::HOST, false );

   bool bEnableDocList = dstrRegDocsExist == I_("Y") && !pMFAccount->isNew () ? true : false;
   bool bEnableBroker = dstrRegDocsExist == I_("Y") ? true : false;

   GetDlgItem (IDC_BTN_DOCLIST)->EnableWindow (bEnableDocList); 
   GetDlgItem (IDC_BTN_BROKER)->EnableWindow (bEnableBroker); 

   /*if( m_dstrKYCAccountLevel == YES )
   {
      CString cstrLabel;
      CString cstrAccount;
      cstrAccount.LoadString( IDS_TXT_ACCT_NUM );
      cstrAccount += " ";
      cstrAccount += dstrAccountNum.c_str();
      GetDlgItem( IDC_STATIC_ACCTLEVEL )->GetWindowText( cstrLabel );
      if( cstrLabel.IsEmpty() == FALSE )
      {
         cstrLabel += ": ";
      }
      cstrLabel += cstrAccount;
      GetDlgItem( IDC_STATIC_ACCTLEVEL )->SetWindowText( cstrLabel );
   }*/

   CString cstrInvProfileInfoPageName;
   CString cstrKYCAMLInfoPageName;

   cstrInvProfileInfoPageName.LoadString ( TXT_INV_PROFILE );
   cstrKYCAMLInfoPageName.LoadString ( TXT_AML );

   DString strInvProfileInfoPageName = cstrInvProfileInfoPageName;
   DString strKYCAMLInfoPageName     = cstrKYCAMLInfoPageName;
   
   DString strMarket = DSTCommonFunctions::getMarket();
   if ( strMarket == MARKET_IDS::LUXEMBOURG )
   {
      if (!dstrEntityName.empty ())
      {
         tabSelectionChanged( IDC_TAB_KYC, strKYCAMLInfoPageName );
      }
   }
   else // Canadian and rest (if there is exist!)
   {
      tabSelectionChanged( IDC_TAB_KYC, strInvProfileInfoPageName );
   }

   for (UINT ctrlId = IDC_CHK_IS_SOLICITING_CORP; ctrlId <= IDC_CHK_PENSIONINCOME; ctrlId++)
   {
      CButton* pCheckBox = dynamic_cast<CButton*>(GetDlgItem(ctrlId));

      if (pCheckBox)
      {
         DString fieldValue;
         const BFFieldId& idField = GetControl(ctrlId)->GetFieldID();
         getParent()->getField(this,
                               IFASTBP_PROC::DEMOGRAPHICS_CBO,
                               idField,
                               fieldValue,
                               false);
         fieldValue.strip().upperCase();
         pCheckBox->SetCheck(fieldValue==I_("Y")?BST_CHECKED:BST_UNCHECKED);
      }
   }
}

//******************************************************************************
void DemographicsDlg::setEmptyForNotAvailable( DString &str )
{
   if( str == I_( "N/A (code:     )" ) )
   {
      str = NULL_STRING;
   }
}

//******************************************************************************
SEVERITY DemographicsDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   DString dstrCaller,
           dstrEntityId;

   getParameter( DEMOGRAPHICS_TITLE, m_strDemoTitle );
   getParameter( CALLER, dstrCaller );

   if ( !dstrCaller.empty() && dstrCaller == ENTITY  )
   {
      m_bShowTabs = false;
      getParameter( ENTITY_ID, dstrEntityId );
      m_dstrEntityID = dstrEntityId;
      m_dstrEntityID.stripAll();
   }

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
bool DemographicsDlg::doRefresh( GenericInterface * rpGICaller, 
                                 const I_CHAR * szOriginalCommand )
{
   DisplayCaption();

   ConnectControlsToData();
   LoadControls( -1L );
   LoadTabControl( IDC_TAB_KYC );
   return(true);
}

/****************************************************************************************/
void DemographicsDlg::OnBtnReset() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   
   getParent()->reset(this, IFASTBP_PROC::DEMOGRAPHICS_CBO);
//   ConnectControlsToData();
//   LoadControls( -1L );
   doRefresh( this, NULL_STRING );
}

//***********************************************************
void DemographicsDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   switch( controlID )
   {
      
      case IDC_EDT_GROWTHPCNT:
      case IDC_EDT_INCOMEPCNT:
      case IDC_EDT_SAFETYPCNT:
      case IDC_EDT_AGGRESSIVE:
      case IDC_EDT_SHORT_TERM:
         {
            DString dstrtotalpcnt;
            getParent()->getField( this, ifds::TotPercentage, dstrtotalpcnt, true );
            GetDlgItem(IDC_STA_TOTALPCNT)->SetWindowText(dstrtotalpcnt.c_str());
         }
         break;
      default:
         break;
   }
}

//***********************************************************
void DemographicsDlg::showHouseControls( bool bShow )
{
   GetDlgItem (IDC_STC_BRANCH)->ShowWindow (bShow);
   GetDlgItem (IDC_STC_SLSREP)->ShowWindow (bShow);
   GetDlgItem (IDC_EDT_BRANCH)->ShowWindow (bShow);
   GetDlgItem (IDC_EDT_SLSREP)->ShowWindow (bShow);
   GetDlgItem (IDC_TXT_BRANCH)->ShowWindow (bShow);
   GetDlgItem (IDC_TXT_SLSREP)->ShowWindow (bShow);

   if ( bShow ) {
     AddControl (CTRL_STATIC, IDC_STC_BRANCH, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::HOUSE_BROKER);
     AddControl (CTRL_STATIC, IDC_STC_SLSREP, CTRLFLAG_GUI_FIELD, KYC_CONTROLS::HOUSE_BROKER);
     AddControl (CTRL_EDIT, IDC_EDT_BRANCH, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::BranchCode);
     AddControl (CTRL_EDIT, IDC_EDT_SLSREP, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AgentCode);
     AddControl (CTRL_STATIC, IDC_TXT_BRANCH, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::BranchName);
     AddControl (CTRL_STATIC, IDC_TXT_SLSREP, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::SlsrepName);
   }
}

/*************************************************************************************/

BOOL DemographicsDlg::PreTranslateMessage( MSG* pMsg ) 
{
   BOOL isTranslated = FALSE;

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 )
   {
      if( GetFocus()== GetDlgItem( IDC_EDT_BRANCH ) ) {
         //Rule: if repByBranch is Yes, F4 should work
         DString dstrRepByBranch;
         getParent()->getField( this, ifds::RepByBranch, dstrRepByBranch );
         if( dstrRepByBranch == YES ) {           
               PostMessage( UM_OPENBRANCHLISTDLG );
         }
      }
   }
   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

/*************************************************************************************/
// This will open be called when the account broker is defined as a house broker.
LRESULT DemographicsDlg::OpenBranchListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBranchListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString dstrBrokerCode;
      getParent()->getField( this, ifds::BrokerCode,   dstrBrokerCode );
      
      setParameter(MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode);
      
      eRtn = invokeCommand( getParent(), CMD_BPROC_BRANCH, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrBranchCode;
               getParameter( MFCAN_IP_PARAM::BRANCH_CODE, dstrBranchCode );
               if( !dstrBranchCode.empty() )
               {
                  bool success = SetControlText( IDC_EDT_BRANCH, dstrBranchCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BRANCH ));
                  if ( !success && pBC )
                     pBC->Load();
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();

               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(0);
}

//******************************************************************************
void DemographicsDlg::PostOk (bool bOkStatus)
{
   if (bOkStatus)
   {
      DString dstrRegulatoryStandard;
      getParent()->getField ( this, ifds::RegulatoryStandard, dstrRegulatoryStandard, false );
      setParameter(I_("RegulatoryStandard"), dstrRegulatoryStandard);
   }
}

//******************************************************************************
void DemographicsDlg::hideControls( void )
{
   hideInvProfile( true );
   hideEmploymentInfo( true );
   hideAML( true );
   hideInvObjective( true );
   hideWitness( true );
   hideMemorable( true );
   hideAssociateComp( true );
   hideKYCMisc( true );
   hideHouseBroker( true );
   hideSourceOfPayment( true );
}

//******************************************************************************
void DemographicsDlg::tabSelectionChanged ( UINT tabControlID, 
                                            const DString &pageName)
{
   if ( tabControlID == IDC_TAB_KYC )
   {
      CString cstrInvProfileInfoPageName;
      CString cstrEmploymentInfoPageName;
      CString cstrAMLInfoPageName;
      CString cstrInvObjectiveInfoPageName;
      CString cstrWitnessInfoPageName;
      CString cstrMemorableInfoPageName;
      CString cstrAssociateCompInfoPageName;
      CString cstrKYCMiscInfoPageName;
      CString cstrHouseBrokerInfoPageName;
      CString cstrAddlAMLInfoPageName;

      cstrInvProfileInfoPageName.LoadString ( TXT_INV_PROFILE );
      cstrEmploymentInfoPageName.LoadString ( TXT_EMPL_INFO );
      cstrAMLInfoPageName.LoadString ( TXT_AML );
      cstrInvObjectiveInfoPageName.LoadString ( TXT_INV_OBJECTIVES );
      cstrWitnessInfoPageName.LoadString ( TXT_WITN_DETAILS );
      cstrMemorableInfoPageName.LoadString ( TXT_MEMORABLE_DATA );
      cstrAssociateCompInfoPageName.LoadString ( TXT_ASSOC_COMPANY );
      cstrKYCMiscInfoPageName.LoadString ( TXT_MISC );
      cstrHouseBrokerInfoPageName.LoadString ( TXT_HOUSEBROKER );
      cstrAddlAMLInfoPageName.LoadString( TXT_SOURCE_OF_PAYMENT_AML );

      if ( pageName.c_str() == cstrInvProfileInfoPageName )
      {
         hideInvProfile( false );
         hideEmploymentInfo( true );
         hideAML( true );
         hideInvObjective( true );
         hideWitness( true );
         hideMemorable( true );
         hideAssociateComp( true );
         hideKYCMisc( true );
         hideHouseBroker( true );
         hideSourceOfPayment( true );
      }
      else if ( pageName.c_str() == cstrEmploymentInfoPageName )
      {
         hideInvProfile( true );
         hideEmploymentInfo( false );
         hideAML( true );
         hideInvObjective( true );
         hideWitness( true );
         hideMemorable( true );
         hideAssociateComp( true );
         hideKYCMisc( true );
         hideHouseBroker( true );
         hideSourceOfPayment( true );
      }
      else if ( pageName.c_str() == cstrAMLInfoPageName )
      {
         hideInvProfile( true );
         hideEmploymentInfo( true );
         hideAML( false );
         hideInvObjective( true );
         hideWitness( true );
         hideMemorable( true );
         hideAssociateComp( true );
         hideKYCMisc( true );
         hideHouseBroker( true );
         hideSourceOfPayment( true );
      }
      else if ( pageName.c_str() == cstrInvObjectiveInfoPageName )
      {
         hideInvProfile( true );
         hideEmploymentInfo( true );
         hideAML( true );
         hideInvObjective( false );
         hideWitness( true );
         hideMemorable( true );
         hideAssociateComp( true );
         hideKYCMisc( true );
         hideHouseBroker( true );
         hideSourceOfPayment( true );
      }
      else if ( pageName.c_str() == cstrWitnessInfoPageName )
      {
         hideInvProfile( true );
         hideEmploymentInfo( true );
         hideAML( true );
         hideInvObjective( true );
         hideWitness( false );
         hideMemorable( true );
         hideAssociateComp( true );
         hideKYCMisc( true );
         hideHouseBroker( true );
         hideSourceOfPayment( true );
      }
      else if ( pageName.c_str() == cstrMemorableInfoPageName )
      {
         hideInvProfile( true );
         hideEmploymentInfo( true );
         hideAML( true );
         hideInvObjective( true );
         hideWitness( true );
         hideMemorable( false );
         hideAssociateComp( true );
         hideKYCMisc( true );
         hideHouseBroker( true );
         hideSourceOfPayment( true );
      }
      else if ( pageName.c_str() == cstrAssociateCompInfoPageName )
      {
         hideInvProfile( true );
         hideEmploymentInfo( true );
         hideAML( true );
         hideInvObjective( true );
         hideWitness( true );
         hideMemorable( true );
         hideAssociateComp( false );
         hideKYCMisc( true );
         hideHouseBroker( true );
         hideSourceOfPayment( true );
      }
      else if ( pageName.c_str() == cstrKYCMiscInfoPageName )
      {
         hideInvProfile( true );
         hideEmploymentInfo( true );
         hideAML( true );
         hideInvObjective( true );
         hideWitness( true );
         hideMemorable( true );
         hideAssociateComp( true );
         hideKYCMisc( false );
         hideHouseBroker( true );
         hideSourceOfPayment( true );
      }
      else if ( pageName.c_str() == cstrHouseBrokerInfoPageName )
      {
         hideInvProfile( true );
         hideEmploymentInfo( true );
         hideAML( true );
         hideInvObjective( true );
         hideWitness( true );
         hideMemorable( true );
         hideAssociateComp( true );
         hideKYCMisc( true );
         hideHouseBroker( false );
         hideSourceOfPayment( true );
      }
      else if ( pageName.c_str() == cstrAddlAMLInfoPageName )
      {
         hideInvProfile( true );
         hideEmploymentInfo( true );
         hideAML( true );
         hideInvObjective( true );
         hideWitness( true );
         hideMemorable( true );
         hideAssociateComp( true );
         hideKYCMisc( true );
         hideHouseBroker( true );
         hideSourceOfPayment( false );
      }
      else
      {
         assert( 0 );
      }
   }
}

//******************************************************************************
void DemographicsDlg::hideInvProfile( bool bShow )
{
   GetControl (IDC_STC_KNOWLEDGE)->Show ( !bShow );
   GetControl (IDC_CMB_KNOWLEDGE)->Show ( !bShow );
   GetControl (IDC_STC_INV_PHILOSOPHY)->Show ( !bShow );
   GetControl (IDC_CMB_INVPHILOSOPHY)->Show ( !bShow );
   GetControl (IDC_STC_INCOME_GROUP)->Show ( !bShow );
   GetControl (IDC_STC_INCOME_LEVEL)->Show ( !bShow );
   GetControl (IDC_CMB_INCOME_LEVEL)->Show ( !bShow );
   GetControl (IDC_STC_ANNUAL_INCOME)->Show ( !bShow );
   GetControl (IDC_EDT_INCOME_LEVEL)->Show ( !bShow );
   GetControl (IDC_STC_INCOME_DATE)->Show ( !bShow );
   GetControl (IDC_DTP_INCOME_LEVEL)->Show ( !bShow );
   GetControl (IDC_STC_NETWORTH_GROUP)->Show ( !bShow );
   GetControl (IDC_STC_NET_WORTH)->Show ( !bShow );
   GetControl (IDC_CMB_NET_WORTH)->Show ( !bShow );
   GetControl (IDC_STC_TOTAL_NETWORTH)->Show ( !bShow );
   GetControl (IDC_EDT_NET_WORTH)->Show ( !bShow );
   GetControl (IDC_STC_NETWORHT_DATE)->Show ( !bShow );
   GetControl (IDC_DTP_NET_WORTH)->Show ( !bShow );
   GetControl (IDC_STC_MARITAL_STATUS)->Show ( !bShow );
   GetControl (IDC_CMB_MARITAL_STATUS)->Show ( !bShow );
   GetControl (IDC_STC_OTHER_INV)->Show ( !bShow );
   GetControl (IDC_CMB_OTHER_INVEST)->Show ( !bShow );
   GetControl (IDC_STC_PRIOR_ADVISOR)->Show ( !bShow );
   GetControl (IDC_CMB_PRIOR_INV_ADVISOR)->Show ( !bShow );
   GetControl (IDC_STC_SAM_HEALTH)->Show ( !bShow );
   GetControl (IDC_CMB_SAMFINHEALTH)->Show ( !bShow );
   GetControl (IDC_STC_RES_TYPE)->Show ( !bShow );
   GetControl (IDC_CMB_RES_TYPE)->Show ( !bShow );
   GetControl (IDC_STC_RES_AMOUNT)->Show ( !bShow );
   GetControl (IDC_EDT_RES_AMOUNT)->Show ( !bShow );
   GetControl (IDC_STC_REFERRAL_CODE)->Show ( !bShow );
   GetControl (IDC_CMB_REFERRAL_CODE)->Show ( !bShow );
   GetControl (IDC_STC_REFERENCE_NAME)->Show ( !bShow );
   GetControl (IDC_EDT_REFERENCE_NAME)->Show ( !bShow );
   GetControl (IDC_STC_NUMOFDEPENDENTS)->Show ( !bShow );
   GetControl (IDC_EDT_NUMOFDEPENDENTS)->Show ( !bShow );
}

//******************************************************************************
void DemographicsDlg::hideEmploymentInfo( bool bShow )
{
   GetControl (IDC_STC_EMPL_NAME)->Show ( !bShow );
   GetControl (IDC_EDT_EMPL_NAME)->Show ( !bShow );
   GetControl (IDC_STC_INDUSTRY)->Show ( !bShow );
   GetControl (IDC_CMB_INDUSTRY)->Show ( !bShow );
   GetControl (IDC_STC_OCCUPATION)->Show ( !bShow );
   GetControl (IDC_CMB_OCUPATION)->Show ( !bShow );
   GetControl (IDC_EDT_OCCUPATIONFREEFMT)->Show ( !bShow );
   GetControl (IDC_STC_EMPL_TYPE)->Show ( !bShow );
   GetControl (IDC_CMB_EMPL_TYPE)->Show ( !bShow );
   GetControl (IDC_STC_YEARS_EMPL)->Show ( !bShow );
   GetControl (IDC_EDT_YEARS_EMPL)->Show ( !bShow );
   GetControl (IDC_STC_SPECIALTY_CODE)->Show ( !bShow );
   GetControl (IDC_CMB_SPECIALTY_CODE)->Show ( !bShow );
   GetControl (IDC_EDT_INDUSTRYOTHER)->Show ( !bShow );
   GetControl (IDC_STC_KYC_BUSINESS_TYPE)->Show (!bShow);
   GetControl (IDC_CMB_KYC_BUSINESS_TYPE)->Show (!bShow);
   GetControl (IDC_STC_KYC_LEGAL_FORM)->Show (!bShow);
   GetControl (IDC_CMB_KYC_LEGAL_FORM)->Show (!bShow);
}

//******************************************************************************
void DemographicsDlg::hideAML( bool bShow )
{
   //KYC AML 
   GetControl (IDC_STC_TYPEOFINVESTOR)->Show ( !bShow );
   GetControl (IDC_CMB_TYPEOFINVESTOR)->Show ( !bShow );
   GetControl (IDC_STC_INV3RDPARTY)->Show ( !bShow );
   GetControl (IDC_CMB_INV3PARTY)->Show ( !bShow );
   GetControl (IDC_STC_SOURCEOFFUNDS)->Show ( !bShow );
   GetControl (IDC_CMB_SOURCEOFFUNDS)->Show ( !bShow );
   GetControl (IDC_STC_PAYMENTMETHOD)->Show ( !bShow );
   GetControl (IDC_EDT_PAYMENTMETHOD)->Show ( !bShow );
   GetControl (IDC_STC_POWEROFATTORNEY)->Show ( !bShow );
   GetControl (IDC_CMB_POWEROFATTORNEY)->Show ( !bShow );
   GetControl (IDC_STC_COMPCODE)->Show ( !bShow );
   GetControl (IDC_EDT_COMPCODE)->Show ( !bShow );
   GetControl (IDC_STC_REGSTANDARDS)->Show ( !bShow );
   GetControl (IDC_CMB_REGSTANDARDS)->Show ( !bShow );
   GetControl (IDC_STC_COUNTRY)->Show ( !bShow );
   GetControl (IDC_CMB_COUNTRY)->Show ( !bShow );
   GetControl (IDC_CHK_IS_SOLICITING_CORP)->Show( !bShow );
}

//******************************************************************************
void DemographicsDlg::hideInvObjective( bool bShow )
{
   GetControl (IDC_STC_OBJECTIVE)->Show ( !bShow );
   GetControl (IDC_CMB_OBJECTIVE)->Show ( !bShow );
   GetControl (IDC_STC_HORIZON)->Show ( !bShow );
   GetControl (IDC_CMB_HORIZON)->Show ( !bShow );
   GetControl (IDC_STC_RISK_TOLERANCE)->Show ( !bShow );
   GetControl (IDC_CMB_RISK_TOLERANCE)->Show ( !bShow );
   GetControl (IDC_STC_TOLERANCE_PRCNT)->Show ( !bShow );
   GetControl (IDC_EDT_TOLERANCE)->Show ( !bShow );
   GetControl (IDC_STC_TOL_PRCNT)->Show ( !bShow );
   GetControl (IDC_GROWTH_PRCT)->Show ( !bShow );
   GetControl (IDC_EDT_GROWTHPCNT)->Show ( !bShow );
   GetControl (IDC_STC1)->Show ( !bShow );
   GetControl (IDC_STC_SHORTTR_PRCNT)->Show ( !bShow );
   GetControl (IDC_EDT_SHORT_TERM)->Show ( !bShow );
   GetControl (IDC_STC_SHORT_TR_PRCNT)->Show ( !bShow );
   GetControl (IDC_STC_INCOME_PRCT)->Show ( !bShow );
   GetControl (IDC_EDT_INCOMEPCNT)->Show ( !bShow );
   GetControl (IDC_STC2)->Show ( !bShow );
   GetControl (IDC_STC_AGGRESIVE)->Show ( !bShow );
   GetControl (IDC_EDT_AGGRESSIVE)->Show ( !bShow );
   GetControl (IDC_STC_AGGRESIVE_PRCNT)->Show ( !bShow );
   GetControl (IDC_STC_SAFETY_PRCT)->Show ( !bShow );
   GetControl (IDC_EDT_SAFETYPCNT)->Show ( !bShow );
   GetControl (IDC_STC3)->Show ( !bShow );
   GetControl (IDC_STC_TOTAL_PRCT)->Show ( !bShow );
   GetControl (IDC_STA_TOTALPCNT)->Show ( !bShow );
   GetControl (IDC_ST4)->Show ( !bShow );
   GetControl (IDC_STC_PRCNT_DATE)->Show ( !bShow );
   GetControl (IDC_DTP_PRCNT_DATE)->Show ( !bShow );
   GetControl (IDC_STC_KYC_INFO_FORMAT)->Show  ( !bShow );
   GetControl (IDC_CMB_KYC_INFO_FORMAT)->Show  ( !bShow );
   GetControl (IDC_STC_PROFILE_NUMBER)->Show ( !bShow );
   GetControl (IDC_EDT_PROFILE_NUMBER)->Show ( !bShow );   
   GetControl (IDC_STC_REF_NUMBER)->Show ( !bShow );
   GetControl (IDC_EDT_REF_NUMBER)->Show ( !bShow );  
   GetControl (IDC_STC_PROFILE_VALUE)->Show  ( !bShow );
   GetControl (IDC_EDT_PROFILE_VALUE)->Show  ( !bShow );
   GetControl (IDC_STC_LAST_REVIEW_DATE)->Show  ( !bShow );
   GetControl (IDC_DTP_LAST_REVIEW_DATE)->Show  ( !bShow );

}

//******************************************************************************
void DemographicsDlg::hideWitness( bool bShow )
{
   // Witness Details
   GetControl (IDC_STC_WITNESS_NAME)->Show ( !bShow );
   GetControl (IDC_STC_WITNESS_ADDR)->Show ( !bShow );
   GetControl (IDC_STC_PERS_SEC_CODE)->Show ( !bShow ); 
   GetControl (IDC_STC_WITNESS_EFF_DATE)->Show ( !bShow );
   GetControl (IDC_EDT_WITNESS_NAME)->Show ( !bShow );
   GetControl (IDC_EDT_WITNESS_ADDR)->Show ( !bShow );
   GetControl (IDC_EDT_PERS_SEC_CODE)->Show ( !bShow );
   GetControl (IDC_DTP_EFF_DATE)->Show ( !bShow );
}

//******************************************************************************
void DemographicsDlg::hideMemorable( bool bShow )
{
   // Memorable Data
   GetControl (IDC_STC_MEM_WORD)->Show ( !bShow );
   GetControl (IDC_STC_MEM_PLACE)->Show ( !bShow );
   GetControl (IDC_STC_MEM_DATE)->Show ( !bShow );
   GetControl (IDC_EDT_MEMORABLE_WORD)->Show ( !bShow );
   GetControl (IDC_EDT_MEMORABLE_PLACE)->Show ( !bShow );
   GetControl (IDC_DTP_MEMORABLE_DATE)->Show ( !bShow );
}

//******************************************************************************
void DemographicsDlg::hideAssociateComp( bool bShow )
{
   GetControl (IDC_STC_COMPANY )->Show ( !bShow );
   GetControl (IDC_EDT_COMPANY1)->Show ( !bShow );
   GetControl (IDC_EDT_COMPANY2)->Show ( !bShow );
   GetControl (IDC_EDT_COMPANY3)->Show ( !bShow );
   GetControl (IDC_EDT_COMPANY4)->Show ( !bShow );
   GetControl (IDC_EDT_COMPANY5)->Show ( !bShow );
   GetControl (IDC_EDT_COMPANY6)->Show ( !bShow );

   GetControl (IDC_STC_ROLE )->Show ( !bShow );
   GetControl (IDC_CMB_ROLE1)->Show ( !bShow );
   GetControl (IDC_CMB_ROLE2)->Show ( !bShow );
   GetControl (IDC_CMB_ROLE3)->Show ( !bShow );
   GetControl (IDC_CMB_ROLE4)->Show ( !bShow );
   GetControl (IDC_CMB_ROLE5)->Show ( !bShow );
   GetControl (IDC_CMB_ROLE6)->Show ( !bShow );
}

//******************************************************************************
void DemographicsDlg::hideKYCMisc( bool bShow )
{
   // Misc
   GetControl (IDC_STC_COMMENTS)->Show ( !bShow );
   GetControl (IDC_EDT_COMMENTS)->Show ( !bShow );
   GetControl (IDC_STC_MAILED)->Show ( !bShow );
   GetControl (IDC_DTP_KYC_DATE)->Show ( !bShow );
   GetControl (IDC_STC_KYCLETTER)->Show ( !bShow );
   GetControl (IDC_CMB_KYCLETTER)->Show ( !bShow );
}

//******************************************************************************
void DemographicsDlg::hideHouseBroker( bool bShow )
{
   DString dstrHouseBroker;
   getParent()->getField ( this, ifds::HouseBroker, dstrHouseBroker, false );

   if ( dstrHouseBroker == YES )
   {
      GetControl (IDC_STC_BRANCH)->Show ( !bShow );
      GetControl (IDC_STC_SLSREP)->Show ( !bShow );
      GetControl (IDC_EDT_BRANCH)->Show ( !bShow );
      GetControl (IDC_EDT_SLSREP)->Show ( !bShow );
      GetControl (IDC_TXT_BRANCH)->Show ( !bShow );
      GetControl (IDC_TXT_SLSREP)->Show ( !bShow );
   }
}

//******************************************************************************
void DemographicsDlg::hideSourceOfPayment( bool bShow )
{
   GetControl (IDC_CHK_SALARY)->Show ( !bShow );
   GetControl (IDC_CHK_BUSINESSINCOME)->Show ( !bShow );
   GetControl (IDC_CHK_BORROWEDFUNDS)->Show ( !bShow );
   GetControl (IDC_CHK_GIFTEDFUNDS)->Show ( !bShow );
   GetControl (IDC_CHK_PRCDSFRMDEATHBENEFESTATE)->Show ( !bShow );
   GetControl (IDC_CHK_SOCIALBENEFITS)->Show ( !bShow );
   GetControl (IDC_CHK_OTHER)->Show ( !bShow );
   GetControl (IDC_CHK_EXISTINGINVSTACCOUNT)->Show ( !bShow );
   GetControl (IDC_CHK_OWNERSAVINGS)->Show ( !bShow );
   GetControl (IDC_CHK_SALEOFPROPERTY)->Show ( !bShow );
   GetControl (IDC_CHK_PENSIONINCOME)->Show ( !bShow );
   GetControl (IDC_CHK_INHERITEDFUNDS)->Show ( !bShow );
   GetControl (IDC_EDT_OTHERREASON)->Show ( !bShow );
   GetControl (IDC_STC_OTHERREASON)->Show ( !bShow );
}

//******************************************************************************
void DemographicsDlg::DisplayCaption( void )
{

   DString  dstrAccountNum, 
            dstrShrNum, 
            dstrEntityName;

   getParent()->getField( this, ifds::AccountNum,         dstrAccountNum );
   getParent()->getField( this, ifds::ShrNum,             dstrShrNum );
   getParent()->getField( this, PRIMARY_ACCOUNT_OWNER,    dstrEntityName );

   if ( !m_bShowTabs ) // Entity level KYC
   {
      DString dstrEntityLastName,
              dstrEntityFirstName,
              dstrEntityDetail;

      getParent()->setField( this, DEMO_ENTITY_ID,    m_dstrEntityID );
      getParent()->getField( this, ENTITY_LAST_NAME,  dstrEntityLastName );
      getParent()->getField( this, ENTITY_FIRST_NAME, dstrEntityFirstName );

      dstrEntityDetail = I_( " ")            +
                         dstrEntityLastName  +
                         I_( ";" )           +
                         dstrEntityFirstName +
                         I_( " EntityID:" )  +
                         m_dstrEntityID;

      DString strTemp;
      if ( m_strDemoTitle.empty() )
      {
         strTemp = dstrEntityName +
                   dstrEntityDetail;
      }
      else
      {
         strTemp = m_strDemoTitle +
                   dstrEntityDetail;
      }

      SetShrAcctCaption(dstrShrNum, dstrAccountNum, strTemp );
   }
   else
   {
      SetShrAcctCaption(dstrShrNum, dstrAccountNum, m_strDemoTitle.empty() ? dstrEntityName : m_strDemoTitle );
   }
}

//******************************************************************************
void DemographicsDlg::OnKillfocusEdtProfileNumber() 
{
   DString dstrProfileNumber;
   GetControl (IDC_EDT_PROFILE_NUMBER)->GetText (dstrProfileNumber);
   
   if(dstrProfileNumber.length() > 9)
   {
      dstrProfileNumber = dstrProfileNumber.left(9);
      GetControl (IDC_EDT_PROFILE_NUMBER)->SetText (dstrProfileNumber);
   }
}

//******************************************************************************
void DemographicsDlg::OnKillfocusEdtRefNumber() 
{
   DString dstrRefNumber;
   GetControl (IDC_EDT_REF_NUMBER)->GetText (dstrRefNumber);
   
   if(dstrRefNumber.length() > 10)
   {
      dstrRefNumber = dstrRefNumber.left(10);
      GetControl (IDC_EDT_REF_NUMBER)->SetText (dstrRefNumber);
   }

}

//******************************************************************************
void DemographicsDlg::OnKillfocusEdtProfileValue() 
{
   DString dstrProfileValue;
   GetControl (IDC_EDT_PROFILE_VALUE)->GetText (dstrProfileValue);
   
   if(dstrProfileValue.length() > 3)
   {
      dstrProfileValue = dstrProfileValue.left(3);
      GetControl (IDC_EDT_PROFILE_VALUE)->SetText (dstrProfileValue);
   }
}

//******************************************************************************
void DemographicsDlg::OnCheckBoxClickByRange(UINT ctrlID)
{
   CButton* pCheckBox = dynamic_cast<CButton*>(GetDlgItem(ctrlID));

   if (pCheckBox)
   {
      bool bBtnState = (pCheckBox->GetCheck() == BST_CHECKED);

      switch (ctrlID)
      {
      case IDC_CHK_IS_SOLICITING_CORP :
      case IDC_CHK_SALARY :
      case IDC_CHK_BUSINESSINCOME :
      case IDC_CHK_BORROWEDFUNDS :
      case IDC_CHK_GIFTEDFUNDS :
      case IDC_CHK_PRCDSFRMDEATHBENEFESTATE :
      case IDC_CHK_SOCIALBENEFITS :
      case IDC_CHK_OTHER :
      case IDC_CHK_INHERITEDFUNDS :
      case IDC_CHK_EXISTINGINVSTACCOUNT :
      case IDC_CHK_OWNERSAVINGS :
      case IDC_CHK_SALEOFPROPERTY :
      case IDC_CHK_PENSIONINCOME :
         {
            const BFFieldId& idField = GetControl(ctrlID)->GetFieldID();
            getParent()->setField(this,
                                  IFASTBP_PROC::DEMOGRAPHICS_CBO,
                                  idField,
                                  bBtnState == true?I_("Y"):I_("N"),
                                  false);

            if (ctrlID == IDC_CHK_OTHER)
            {
               LoadControl (IDC_EDT_OTHERREASON);
            }
         }
         break;
      default :
         break;
      }
   }

   //controlFieldTable.clear();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DemographicsDlg.cpp-arc  $
 * 
 *    Rev 1.55   Mar 27 2012 01:34:48   panatcha
 * IN2895115 - format allowed must be numeric only on KYC
 * 
 *    Rev 1.54   Oct 17 2011 03:27:00   kitticha
 * PETP0186486 FN14 IN2698689 - KYC Risk Tolerance issues.
 * 
 *    Rev 1.53   Sep 16 2011 06:04:16   kitticha
 * PETP0186486 - KYC Risk Tolerance.
 * 
 *    Rev 1.52   Dec 12 2008 10:51:18   jankovii
 * IN 1514603 - In entity screen, select entity/beneficiary, click on KYC,tab wrong
 * 
 *    Rev 1.51   31 Oct 2008 16:19:10   popescu
 * KYC/AML - joint accounts feature
 * 
 *    Rev 1.50   Oct 28 2008 08:34:34   jankovii
 * PET 59888 FN03 AML KYC.
 * 
 *    Rev 1.49   Oct 14 2008 23:59:22   daechach
 * in# 1446903 - Regression issue of PET59888FN01-- while click on Demographics, Tab "KYC AML" disp.wrong contents.
 * 
 *    Rev 1.48   Oct 09 2008 11:54:36   jankovii
 * IN 1437673 KYC Broker info.
 * 
 *    Rev 1.47   Sep 12 2008 07:29:06   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.46   Sep 08 2008 03:30:42   daechach
 * PET0128026 - KYC Phase 2 - Fix build error for R89Unit
 * 
 *    Rev 1.45   Aug 28 2008 14:23:42   jankovii
 * IN 1388930 - NASU flow does not update document list unless at least one document.
 * 
 *    Rev 1.44   Jul 23 2008 16:29:14   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.43   Jul 16 2008 16:08:40   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.42   Aug 06 2007 16:28:26   kovacsro
 * PET2372 FN02 - FDP-AIM KYC - fixed account level group box and changed historical according to the new view design
 * 
 *    Rev 1.41   Jul 27 2007 17:40:10   kovacsro
 * PET 2372 FN02 FDP-AIM KYC
 * 
 *    Rev 1.40   Jul 16 2007 13:55:30   jankovii
 * PET 2372 FN02 - FDP New data elements. Removed Group Member # control.
 *
 *    Rev 1.39   Jul 06 2007 14:47:28   jankovii
 * PET 2360 FN96 - added one more field.
 * 
 *    Rev 1.38   Jul 06 2007 14:23:56   jankovii
 * PET 2360 FN96 - added support for AIM KYC screen.
 * 
 *    Rev 1.37   Sep 15 2005 15:11:16   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.36   Mar 15 2004 17:52:50   HERNANDO
 * PET965 FN11 - Changed Historical KYC for Account.
 * 
 *    Rev 1.35   Mar 10 2004 11:30:18   HERNANDO
 * PET965 FN11 - Changed to use iFastHistoricalInfo.
 * 
 *    Rev 1.34   Feb 28 2004 16:15:50   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.33   Nov 20 2003 10:05:06   HSUCHIN
 * PTS 10024105 - Enable branch search for house brokers.
 * 
 *    Rev 1.32   Oct 02 2003 17:37:56   HERNANDO
 * Revised the display for the number of years worked; especially for new shareholders.
 * 
 *    Rev 1.31   Sep 22 2003 15:13:12   HERNANDO
 * Changed Investment Objectives display of Account Level.  No longer uses hardcoded English strings in the source.  Also made the display consistent with Memorable Data.
 * 
 *    Rev 1.30   Sep 19 2003 13:07:54   FENGYONG
 * change occupation freefmt to edit box
 * 
 *    Rev 1.29   Aug 19 2003 15:55:50   HSUCHIN
 * added support for branch / agent code input
 * 
 *    Rev 1.28   Aug 19 2003 14:39:38   HERNANDO
 * Changed container from MFAccount to Demographics for Memorable Data fields.
 * 
 *    Rev 1.27   Aug 14 2003 10:03:32   FENGYONG
 * remove account level for non CIBC client
 * 
 *    Rev 1.26   Aug 12 2003 16:06:56   HERNANDO
 * Added Account # to Memorable Data label.
 * 
 *    Rev 1.25   Jul 31 2003 13:24:12   FENGYONG
 * Add historical logic
 * 
 *    Rev 1.24   Jul 28 2003 14:19:54   HERNANDO
 * Added MemorablePlace, MemorableWord, and MemorableDate controls.
 * 
 *    Rev 1.23   Jul 11 2003 17:00:14   FENGYONG
 * Add account level caption to KYC screen
 * 
 *    Rev 1.22   Jul 11 2003 16:00:32   FENGYONG
 * PET 809, FN07 Show KYC screen FOR CIBC broker
 * 
 *    Rev 1.21   Mar 21 2003 18:34:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.20   Oct 09 2002 23:55:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.19   Jul 05 2002 10:42:18   PURDYECH
 * Include file cleanup.
 * 
 *    Rev 1.18   22 May 2002 19:15:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.17   27 Mar 2002 20:01:04   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.16   Jul 09 2001 11:19:06   HUANGSHA
 * Enable Reset button for Japan Market, remove the hard-coded string
 * 
 *    Rev 1.15   Mar 30 2001 18:31:16   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.14   29 Mar 2001 16:10:00   KOVACSRO
 * perm. check.
 * 
 *    Rev 1.13   27 Mar 2001 16:50:40   KOVACSRO
 * perm. check stuff
 * 
 *    Rev 1.12   Feb 23 2001 13:49:44   YINGBAOL
 * fix multiline edit isuues
 * 
 *    Rev 1.11   Feb 12 2001 16:22:22   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.10   Feb 09 2001 13:34:02   DINACORN
 * M3/C4 synchronization
 * 
 *    Rev 1.9   Dec 01 2000 14:43:24   KOVACSRO
 * Added permission check.
 * 
 *    Rev 1.8   Oct 27 2000 17:31:46   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.7   Oct 19 2000 18:19:18   ZHANGCEL
 * WitnessAssress bug fixed
 * 
 *    Rev 1.6   Oct 13 2000 10:25:34   DINACORN
 * Modified the maximum number of digits for some fields
 * 
 *    Rev 1.5   Sep 22 2000 15:26:16   HERNANDO
 * Implemented RESET Button.
 * 
 *    Rev 1.4   Aug 09 2000 11:48:34   ZHANGCEL
 * Bug fixed and code clean up
 * 
 *    Rev 1.3   Aug 08 2000 14:22:00   ZHANGCEL
 * Removed OnBtnChanged() and the stuffs related Button Change
 * 
 *    Rev 1.2   Aug 03 2000 09:32:40   WINNIE
 * Remove 'Change' button for Canadian Market. Canadian client should has the same screen as MSDW with update option
 * 
 *    Rev 1.1   Aug 01 2000 11:44:32   HUANGSHA
 * Fixed the crashing problem when lauched from NASU
 * 
 *    Rev 1.0   Feb 15 2000 11:01:12   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.15   Jan 24 2000 09:36:48   YINGBAOL
 * hllapi change
 * 
 *    Rev 1.14   Jan 19 2000 10:12:16   BUZILA
 * refresh stuf
 * 
 *    Rev 1.13   Dec 22 1999 11:28:02   YINGBAOL
 * Hllpai Change Sync.
 * 
 *    Rev 1.12   Nov 22 1999 10:38:24   ZHANGCEL
 * Using new control functions to populate the dialog
 * 
 *    Rev 1.11   Nov 15 1999 12:19:02   ZHANGCEL
 * Change Multi_line edit box
 * 
 *    Rev 1.10   Nov 11 1999 09:54:34   ZHANGCEL
 * Using DST new controls to implement functions
 * 
 *    Rev 1.9   Oct 31 1999 16:29:04   PRAGERYA
 * getField calls corrected
 * 
 *    Rev 1.8   Oct 04 1999 14:12:16   HSUCHIN
 * bug fix for other investment drop down to display properly.
 * 
 *    Rev 1.7   Sep 20 1999 13:13:38   HSUCHIN
 * Minor bug fixes, added missing control
 * 
 *    Rev 1.6   Sep 17 1999 14:12:16   HSUCHIN
 * Demographic change for C1 and M2
 * 
 *    Rev 1.5   01 Sep 1999 16:40:46   HUANGSHA
 * Add OtherInvestment substitute list
 * 
 *    Rev 1.4   Aug 25 1999 15:38:52   DT24433
 * misc.
 * 
 *    Rev 1.3   25 Aug 1999 16:00:00   HUANGSHA
 * Check in temperorily
 * 
 *    Rev 1.2   Aug 11 1999 17:48:46   BUZILA
 * fix dtp control
 * 
 *    Rev 1.1   Jul 08 1999 10:04:56   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
