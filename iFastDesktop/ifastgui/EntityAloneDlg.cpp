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
//    Copyright 2005 by IFDS, Inc.
//
//******************************************************************************
//
// ^FILE   : EntityAloneDlg.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 23/02/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : EntityAloneDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the System/MGMT selection dialog
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include "EntityAloneDlg.h"
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstcombobox.h>
#include <uibase\dsttabctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <uibase\dstedit.h>
#include <uibase\dstdatetime.h>
#include <uibase\dstlistctrl.h>
#include <ifastbp\EntityAloneProcessincludes.h>
#include <ifastbp\whereusedprocessincludes.h>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0061_vw.hpp>
#include <ifastbp\addressprocessincludes.h>
#include <ifastbp\fillsearchcriteriaprocessincludes.h>
#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_WHEREUSED;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ENTITY_ALONE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDGROUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MANAGEMENT_FEE;  // PMI
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DEMOGRAPHICS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENT_REG_MAINT;


#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< EntityAloneDlg > dlgCreator( CMD_GUI_ENTITY_ALONE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY_SEARCH;
//extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES;

namespace
{
   // trace literals
   const I_CHAR *CLASSNAME                      = I_( "EntityAloneDlg" );
   const I_CHAR *LV_ENTITY_LIST                 = I_( "Entity Name List" );
   const I_CHAR *LV_ENTITY_IDS_LIST             = I_( "Entity IDS List" );
   const I_CHAR *LV_WHEREUSEDLIST               = I_( "WhereUsed List" );

   const I_CHAR *YEARS                          = I_( "yrs" );
   const I_CHAR *MONTHS                         = I_( "mths" );
   const I_CHAR *COMMA_STRING                   = I_( "," );
   const I_CHAR *SEMICOLUMN_STRING              = I_( ";" );
   const I_CHAR *EMPTY_STRING                   = I_( "" );
   const I_CHAR *SPACE_STRING                   = I_( " " );
   const I_CHAR *DEFAULT_DATE                   = I_("12319999");
   const I_CHAR *RETURN                         = I_( "\n" );
   const I_CHAR *YES                            = I_( "Yes" );
   const I_CHAR *Y                              = I_( "Y" );
   const I_CHAR *NO                             = I_( "No" );
   const I_CHAR *N                              = I_( "N" );
   const I_CHAR *SIN                            = I_( "06" );
   const I_CHAR *NEQ                            = I_ ("22");
   const I_CHAR *CODE_CATEGORY_CORPORATE        = I_( "02" );
   const I_CHAR *TAX_ID_NUM                     = I_( "08" );
   const I_CHAR *DEPOSITARY_BANK_ACCOUNT        = I_( "07" );
   const I_CHAR * const CHARACTERS              = I_( "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" );
   const I_CHAR * const ALPHACHARACTERS         = I_( " ,abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" );
   const I_CHAR * const FUND_CODE               = I_( "FundCode" );
   const I_CHAR * const FUNDBROKER              = I_( "01" );
   const I_CHAR * const ACCOUNT                 = I_( "02" );
   const I_CHAR * const FUND                    = I_( "04" );
   const I_CHAR * const FUNDSPONSOR             = I_( "05" );
   const I_CHAR * const PAYING_AGENT            = I_( "04" );
   const I_CHAR * const NETWORK_SENDER          = I_( "06" );
   const I_CHAR * const HOLDING_ENTITY          = I_( "06" );
   const I_CHAR * const EXTERNAL_PRODUCT_PROVIDER   = I_( "12" );
   const I_CHAR * const ENTITY_ID_VALUE_COLUMN  = I_( "IdValue" );
   const TCHAR  * const CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES = I_( "BPROC_ACCT_LVL_CUT_OFF_TIMES" );
   const TCHAR  * const REG_AGENT_CODE_SET_CHAR          = I_("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-/()[]@#_:");
   const I_CHAR * const POLITICALLY_EXPOSED_PERSON       = I_( "3" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate2;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
   extern CLASS_IMPORT const BFTextFieldId CountryName;
   extern CLASS_IMPORT const BFTextFieldId BeneficiaryTitleDisplay;
   extern CLASS_IMPORT const BFTextFieldId InqPerm;
   extern CLASS_IMPORT const BFNumericFieldId SpouseEntityID;
   extern CLASS_IMPORT const BFTextFieldId OwnerSpouseName;
   extern CLASS_IMPORT const BFTextFieldId NAME_LENGTH;
   extern CLASS_IMPORT const BFTextFieldId EntityAloneHeading;
   extern CLASS_IMPORT const BFTextFieldId WhereUsedListHeading;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId IdExpireDate;
   extern CLASS_IMPORT const BFTextFieldId FATCAApplicable;
   extern CLASS_IMPORT const BFTextFieldId FATCAFFI;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ENTITY_MAINTANENCE;
   extern CLASS_IMPORT I_CHAR * const EXTERNAL_PROVIDER_UPDATE;
   extern CLASS_IMPORT I_CHAR * const ENTITY_REGULATORY_MAINT;
   extern CLASS_IMPORT I_CHAR * const APAC_SUPREGN;
}


namespace ENTITYALONESEARCH //entity search literals
{
   const I_CHAR * const SEARCH_CODE                = I_( "EntitySearchCode" );
   const I_CHAR * const FIRST_VALUE                = I_( "FirstValue" );
   const I_CHAR * const SECOND_VALUE               = I_( "SecondValue" );
   //by default it will be an account search;
   //this parameter should be set to Y if we are looking at a entity search
   const I_CHAR * const ENTITY_SEARCH              = I_( "N" );
   //this parameter should be set to Y if we are doing an entity search during adding a new entity to the system
   const I_CHAR * const ENTITY_BACKGROUNG_SEARCH   = I_( "BackgroundSearch" );
   const I_CHAR * const SEARCH_CRITERIA_CODE       = I_( "SearchCriteriaCode" );
   const I_CHAR * const SEARCH_USING_CODE          = I_( "SearchUsingCode" );
   const I_CHAR * const FROM_SCR                   = I_( "FromScreen" );
   const I_CHAR * const ENTITY_ALONE               = I_( "EntityAlone" );
   const I_CHAR * const ALLENTITY                  = I_( "AllEntity" );
   const I_CHAR * const EXACTSEARCH                = I_( "ExactSearch" );
}

namespace ENTITYALONEDLG
{
   const I_CHAR * const ACCOUNT_NUM          = I_( "AccountNum" );
   const I_CHAR * const ENTITY_ID            = I_( "EntityId" );
   const I_CHAR * const CALLER               = I_( "Caller" );
   const I_CHAR * const ENTITY               = I_( "Entity" );
}

namespace ENTITY_WHEREUSED_CONTROLS
{
   const UINT EDIT_CNTRL   = 1;
   const UINT COMBO_CNTRL  = 2;
}

namespace ENTITY_WHEREUSED_VALUE
{
   const I_CHAR * const CLIENT         = I_( "03" );
   const I_CHAR * const COUNTRY  =  I_( "11" );
   const I_CHAR * const REG_AGENT = I_( "14" );
   const I_CHAR * const LEGAL_ENTITY   = I_( "15" );
}

namespace ENTITY_IDS_CONTROLS
{
   const UINT EDIT_CNTRL   = 3;
   const UINT COMBO_CNTRL  = 4;
}

namespace ENTITY_IDS_VALUE
{
   const I_CHAR * const DRIVERS_LICENSE         = I_("01");
   const I_CHAR * const PASSPORT                = I_("02");
   const I_CHAR * const BIRTH_CERTIFICATE       = I_("03");
   const I_CHAR * const NATIONAL_ID             = I_("05");
   const I_CHAR * const TAX_ID_NUMBER           = I_("08");
   const I_CHAR * const BIC_CODE                = I_("10");
   const I_CHAR * const BUSINESS_NUMBER         = I_("17");
   const I_CHAR * const CLEARING_PLATFORM       = I_("18");
   const I_CHAR * const TRUST_ACCOUNT_NUMBER    = I_("24");
   const I_CHAR * const EMPLOYER_NUMBER         = I_("29");   
   const I_CHAR * const FAST					= I_("30");
   const I_CHAR * const iFAST_SICAV				= I_("31");
   const I_CHAR * const iFAST_OEIC				= I_("32" );
   const I_CHAR * const FATCA_GIIN              = I_("35" );
   const I_CHAR * const SOCIAL_SECURITY_NUMBER  = I_("39");
   const I_CHAR * const TAX_FILE_NUMBER			= I_("46");
   const I_CHAR * const AEOI					= I_("48");
}

//******************************************************************************
// Public methods
//******************************************************************************

EntityAloneDlg::EntityAloneDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( EntityAloneDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   m_bUpdateShareholder = false;

}

//***************************************************************
//  Afx Data Exchange
//***************************************************************


void EntityAloneDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);

   DDX_Check(pDX, IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS, m_bUpdateShareholder);

   //{{AFX_DATA_MAP(EntityAloneDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(EntityAloneDlg, BaseMainDlg)
//{{AFX_MSG_MAP(EntityAloneDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdminDates)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_ADD_WHERE_USED, OnBtnAddWhereUsed)
ON_BN_CLICKED(IDC_BTN_DELETE_WHERE_USED, OnBtnDelWhereUsed)
ON_BN_CLICKED(IDC_BTN_ADD_ID, OnBtnAddId)
ON_BN_CLICKED(IDC_BTN_DELETE_ID, OnBtnDeleteId)
ON_BN_CLICKED(IDC_BTN_ENTITY_HISTORY, OnBtnHistorical)
ON_BN_CLICKED(IDC_BTN_CUTOFF_TIME, OnBtnCutOffTime)
ON_BN_CLICKED(IDC_BTN_MORE_WHERE_USED, OnBtnMoreWhereUsed)
ON_BN_CLICKED( IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS, OnChkUpdateShareholder )
ON_BN_CLICKED( IDC_BTN_ADDRESS, OnBtnAddress )
//ON_BN_CLICKED(IDC_BTN_COPYENTITY, OnBtnCopyentity)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_MESSAGE( UM_OPENFUNDGROUPDLG, OpenFundGroupDlg )
ON_BN_CLICKED( IDC_BTN_ENTITY_MANAGEMENT_FEE, OnBtnManagementFee )
ON_BN_CLICKED( IDC_BTN_KYC, OnBtnKYC )
ON_BN_CLICKED( IDC_BTN_ENT_REG_DETAIL, OnBtnEntRegDetail)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Message handlers
//******************************************************************************

//******************************************************************************
// Protected methods
//******************************************************************************
BOOL EntityAloneDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog") );
   BaseMainDlg::OnInitDialog();

   SetUserAccesFunctionCode( UAF::ENTITY_MAINTANENCE );

   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_ENTITIES);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_ENTITIES);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_ID, IDC_LV_ENTITY_IDS);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_ID, IDC_LV_ENTITY_IDS);
   addBtnAddForPermissionCheck(IDC_ADD_WHERE_USED, IDC_LST_WHERE_USED);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_WHERE_USED, IDC_LST_WHERE_USED);
   addBtnAddForPermissionCheck(IDC_BTN_CUTOFF_TIME, IDC_LST_WHERE_USED);

   AddListControl( CLASSNAME, IDC_LV_ENTITIES,     LV_ENTITY_LIST,      ifds::EntityAloneHeading, 
      IFASTBP_PROC::ENTITY_LIST );

   AddListControl( CLASSNAME, IDC_LV_ENTITY_IDS,   LV_ENTITY_IDS_LIST,  ifds::EntityIDSHeadingSet,
      IFASTBP_PROC::ENTITY_IDS_LIST, IDC_LV_ENTITIES );

   AddListControl( CLASSNAME, IDC_LST_WHERE_USED, LV_WHEREUSEDLIST,     ifds::WhereUsedListHeading,
      IFASTBP_PROC::WHEREUSED_LIST, IDC_LV_ENTITIES );

   DString strMarket = DSTCommonFunctions::getMarket();

// Where used
   AddControl( CTRL_COMBO, IDC_EDT_WHERE_USED_CODE,         IFASTBP_PROC::WHEREUSED_LIST, ifds::WhereUse,      CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_WHERE_USED );

   AddControl( CTRL_EDIT,  
               IDC_EDT_CODE,
               IFASTBP_PROC::WHEREUSED_LIST, 
               ifds::WhereUseCode,  
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               //(UINT)IDC_LST_WHERE_USED );
               (UINT)ENTITY_WHEREUSED_CONTROLS::EDIT_CNTRL );
               
   AddControl( CTRL_COMBO, 
               IDC_CMB_CODE,
               IFASTBP_PROC::WHEREUSED_LIST, 
               ifds::WhereUseCode,  
               CTRLFLAG_INITCOMBO_BY_SUB_LIST,
               ENTITY_WHEREUSED_CONTROLS::COMBO_CNTRL );

   AddControl( CTRL_COMBO, IDC_CMB_WHERE_USED_RELATION,     IFASTBP_PROC::WHEREUSED_LIST, ifds::EntityType,    CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_WHERE_USED );
   AddControl( CTRL_DATE,  IDC_DTP_EFFECTIVEDATE,           IFASTBP_PROC::WHEREUSED_LIST, ifds::EffectiveDate, 0,                              (UINT)IDC_LST_WHERE_USED );
   AddControl( CTRL_DATE,  IDC_DTP_STOPDATE,                IFASTBP_PROC::WHEREUSED_LIST, ifds::StopDate,      0,                              (UINT)IDC_LST_WHERE_USED );

// Contacts
   AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_EXT,         IFASTBP_PROC::ENTITY_LIST, ifds::BusinessExt,      0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_EMAIL,                IFASTBP_PROC::ENTITY_LIST, ifds::Email,            0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_CONTACT_NAME,         IFASTBP_PROC::ENTITY_LIST, ifds::ContactName,      0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_TELEX,                IFASTBP_PROC::ENTITY_LIST, ifds::Telex,            0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_EMAIL2,               IFASTBP_PROC::ENTITY_LIST, ifds::Email2,           0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_SECOND_PHONENUM,      IFASTBP_PROC::ENTITY_LIST, ifds::SecondPhoneNum,   0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_SECOND_PHONENUM_EXT,  IFASTBP_PROC::ENTITY_LIST, ifds::SecondPhoneNumExt,0,                              (UINT)IDC_LV_ENTITIES );


   if( strMarket == MARKET_IDS::CANADA )
   {
      AddControl( CTRL_EDIT,     IDC_EDT_HOME_TEL,                IFASTBP_PROC::ENTITY_LIST, ifds::HomePhone,             0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_TEL,            IFASTBP_PROC::ENTITY_LIST, ifds::BusinessPhone,         0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_HOME_FAX,                IFASTBP_PROC::ENTITY_LIST, ifds::HomeFax,               0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_FAX,            IFASTBP_PROC::ENTITY_LIST, ifds::BusinessFax,           0,                              (UINT)IDC_LV_ENTITIES );
      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_TELEX ) )->SetMaxCharNum( 13 );
      AddControl( CTRL_EDIT,     IDC_EDT_HOME_TEL_AREA,           IFASTBP_PROC::ENTITY_LIST, ifds::HomePhoneArea,         0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_TEL_AREA,       IFASTBP_PROC::ENTITY_LIST, ifds::BusinessPhoneArea,     0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_HOME_FAX_AREA,           IFASTBP_PROC::ENTITY_LIST, ifds::HomeFaxArea,           0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_FAX_AREA,       IFASTBP_PROC::ENTITY_LIST, ifds::BusFaxArea,            0,                              (UINT)IDC_LV_ENTITIES );
   }
   else if ( strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_EDIT,     IDC_EDT_HOME_TEL_LUX,            IFASTBP_PROC::ENTITY_LIST, ifds::HomePhone,             0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_TEL_LUX,        IFASTBP_PROC::ENTITY_LIST, ifds::BusinessPhone,         0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_HOME_FAX_LUX,            IFASTBP_PROC::ENTITY_LIST, ifds::HomeFax,               0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_FAX_LUX,        IFASTBP_PROC::ENTITY_LIST, ifds::BusinessFax,           0,                              (UINT)IDC_LV_ENTITIES );
   }
   UINT uShowWindowCan = strMarket == MARKET_IDS::CANADA? SW_SHOW:SW_HIDE;

   GetDlgItem( IDC_EDT_HOME_TEL           )->ShowWindow( uShowWindowCan );
   GetDlgItem( IDC_EDT_BUSINESS_TEL       )->ShowWindow( uShowWindowCan );
   GetDlgItem( IDC_EDT_HOME_FAX           )->ShowWindow( uShowWindowCan );
   GetDlgItem( IDC_EDT_BUSINESS_FAX       )->ShowWindow( uShowWindowCan );
   GetDlgItem( IDC_EDT_HOME_TEL_AREA      )->ShowWindow( uShowWindowCan );
   GetDlgItem( IDC_EDT_BUSINESS_TEL_AREA  )->ShowWindow( uShowWindowCan );
   GetDlgItem( IDC_EDT_HOME_FAX_AREA      )->ShowWindow( uShowWindowCan );
   GetDlgItem( IDC_EDT_BUSINESS_FAX_AREA  )->ShowWindow( uShowWindowCan );

   bool uShowWindowLux = MARKET_IDS::LUXEMBOURG? true:false;
   GetDlgItem( IDC_EDT_HOME_TEL_LUX       )->ShowWindow( !uShowWindowLux );
   GetDlgItem( IDC_EDT_BUSINESS_TEL_LUX   )->ShowWindow( !uShowWindowLux );
   GetDlgItem( IDC_EDT_HOME_FAX_LUX       )->ShowWindow( !uShowWindowLux );
   GetDlgItem( IDC_EDT_BUSINESS_FAX_LUX   )->ShowWindow( !uShowWindowLux );

//Entity  Detail
   AddControl( CTRL_COMBO,    IDC_CMB_EMPLOYEECLASS,           IFASTBP_PROC::ENTITY_LIST, ifds::EmployeeClass,       CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   GetDlgItem( IDC_CMB_SALUTATION )->ShowWindow( m_bSalutationFreeFormat ? SW_HIDE : SW_SHOW );
   GetDlgItem( IDC_EDT_SALUTATION )->ShowWindow( m_bSalutationFreeFormat ? SW_SHOW : SW_HIDE );
   if( m_bSalutationFreeFormat )
   {
      AddControl( CTRL_EDIT,  IDC_EDT_SALUTATION,              IFASTBP_PROC::ENTITY_LIST, ifds::Salutation, 0, (UINT)IDC_LV_ENTITIES );
   }
   else
   {
      AddControl( CTRL_COMBO,    IDC_CMB_SALUTATION,           IFASTBP_PROC::ENTITY_LIST, ifds::Salutation,          CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_WITH_BLANK, (UINT)IDC_LV_ENTITIES );
   }
   AddControl( CTRL_EDIT,     IDC_EDT_NAME,                    IFASTBP_PROC::ENTITY_LIST, ifds::LastName,            0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_LAST_NAME,               IFASTBP_PROC::ENTITY_LIST, ifds::LastName,            0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_FIRST_NAME,              IFASTBP_PROC::ENTITY_LIST, ifds::FirstName,           0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_DATE,     IDC_DTP_BIRTH_DATE,              IFASTBP_PROC::ENTITY_LIST, ifds::DofBirth,            0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_BIRTH_PLACE,             IFASTBP_PROC::ENTITY_LIST, ifds::BirthPlace,          0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_COUNTRY_OF_BIRTH,        IFASTBP_PROC::ENTITY_LIST, ifds::CountryOfBirth,      CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_GENDER,                  IFASTBP_PROC::ENTITY_LIST, ifds::Gender,              CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );

   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_STATIC, IDC_TXT_AGE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD, IDC_LV_ENTITIES );
   }
   AddControl( CTRL_COMBO,    IDC_CMB_NATIONALITY,             IFASTBP_PROC::ENTITY_LIST, ifds::Nationality ,        CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_LANGUAGE,                IFASTBP_PROC::ENTITY_LIST, ifds::LanguageCode,        CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_OCUPATION,               IFASTBP_PROC::ENTITY_LIST, ifds::OccupationCode,      CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_OCCUPATION,              IFASTBP_PROC::ENTITY_LIST, ifds::OtherOccupation,     0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_DATE,     IDC_DTP_EFFECTIVE_DATE,          IFASTBP_PROC::ENTITY_LIST, ifds::EffectiveDate,       0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_DATE,     IDC_DTP_DEATH_DATE,              IFASTBP_PROC::ENTITY_LIST, ifds::DofDeath,            0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_DATE,     IDC_DTP_DEATHNOTIFDATE,          IFASTBP_PROC::ENTITY_LIST, ifds::DofDeathNotice,      0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_RISK_LEVEL,              IFASTBP_PROC::ENTITY_LIST, ifds::RiskLevel,           CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );

   //Tax Juris
   AddControl( CTRL_COMBO,    IDC_CMB_EUSD_OPTION,             IFASTBP_PROC::ENTITY_LIST, ifds::EUSDTaxOption,       CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_DATE,     IDC_DTP_TAX_JURIS_EFFECTIVE,     IFASTBP_PROC::ENTITY_LIST, ifds::TaxJurisDeff,        0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_EDT_TAX_JURIS,               IFASTBP_PROC::ENTITY_LIST, ifds::TaxJuris,            CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   //AddControl( CTRL_COMBO,    IDC_CMB_FATCA_FFID,              IFASTBP_PROC::ENTITY_LIST, ifds::FATCAFFI,            CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );

   // id related
   AddControl( CTRL_COMBO,    IDC_CMB_ID_TYPE,                 IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType,          CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   //AddControl( CTRL_EDIT,     IDC_EDT_ID_VALUE,                IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue,         0,                              (UINT)IDC_LV_ENTITY_IDS );
   AddControl( CTRL_EDIT,     IDC_EDT_ID_VALUE,                IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue,         0,                              ENTITY_IDS_CONTROLS::EDIT_CNTRL  );
   AddControl( CTRL_COMBO,    IDC_CMB_ID_VALUE,                IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue,         CTRLFLAG_INITCOMBO_BY_SUB_LIST, ENTITY_IDS_CONTROLS::COMBO_CNTRL );
   AddControl( CTRL_DATE,     IDC_DTP_ID_DATE,                 IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdDate,          CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   AddControl( CTRL_DATE,     IDC_DTP_ID_DATE_EXPIRE,          IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdExpireDate,    CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   AddControl( CTRL_COMBO,    IDC_CMB_COUNTRY_OF_ISSUE,        IFASTBP_PROC::ENTITY_IDS_LIST, ifds::CountryOfIssue,  CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   AddControl( CTRL_STATIC,   IDC_BTN_DELETE,                                                           CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_DELETE_ID,                                                        CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_ADD,                                                              CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_ADD_ID,                                                           CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_SEARCH,                                                           CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_RESET,                                                            CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDOK,                                                                     CTRLFLAG_GUI_FIELD                                        );

   // Tab enhancement
   AddControl (CTRL_STATIC, IDC_STATIC_SALUTATION,       CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_CATEGORY,            CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_LAST_NAME,           CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_FIRST_NAME,          CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_NAME,                CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BIRTH_DATE,          CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BIRTH_COUNTRY,       CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BIRTH_PLACE,         CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_GENDER,              CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_AGE,                 CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_NATIONALITY,         CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_TXT_LANGUAGE,            CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_OCCUPATION,          CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_RISK_LEVEL,          CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_HOME_TEL,            CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BUSINESS_TEL,        CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BUSINESS_EXT,        CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_HOME_FAX,            CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BUSINESS_FAX,        CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_EMAIL,               CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_EMAIL2,              CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_SECOND_PHONENUM,     CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_SECOND_PHONENUM_EXT, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_CONTACT_NAME,        CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_TELEX,               CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_DATE_EFFECTIVE,      CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_DATE_DEATH_NOTIF,    CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_DATE_DEATH,          CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_EFFECTIVE_DATE,      CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_STOP_DATE,           CTRLFLAG_GUI_FIELD);

// Tax Juris
   AddControl (CTRL_STATIC,IDC_STC_TAX_JURIS,            CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,IDC_STC_TAX_JURIS_EFFECTIVE,  CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,IDC_STC_EUSD_OPTION,          CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS, CTRLFLAG_GUI_FIELD);
   //AddControl (CTRL_STATIC,IDC_STC_FATCA_FFID,           CTRLFLAG_GUI_FIELD);

   DString eusd;
   getParent()->getField(this, ifds::EUSDParticip,eusd,false);
   eusd.strip().upperCase();
   if( eusd == N )  // if it is not eusd environment,hide option
   {
      GetDlgItem (IDC_STC_EUSD_OPTION )->ShowWindow( SW_HIDE );
      GetDlgItem (IDC_CMB_EUSD_OPTION )->ShowWindow( SW_HIDE );
   }

   //tab control
   DSTTabCtrl* pTabCtrl =
      AddTabControl(CLASSNAME, IDC_TAB_ENTITY_MAINTENANCE, I_("EntityMaintDetailsTab"));
   if (pTabCtrl)
   {
      pTabCtrl->AddTab (TXT_PAGE_DETAILS);
      pTabCtrl->AddTab (TXT_PAGE_CONTACTS);
      pTabCtrl->AddTab (TXT_PAGE_TAX);

      // Details
      pTabCtrl->registerControl (IDC_STC_CATEGORY,       TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_EMPLOYEECLASS,  TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STATIC_SALUTATION,  TXT_PAGE_DETAILS);
      if( m_bSalutationFreeFormat )
      {
         pTabCtrl->registerControl (IDC_EDT_SALUTATION,  TXT_PAGE_DETAILS);
      }
      else
      {
         pTabCtrl->registerControl (IDC_CMB_SALUTATION,  TXT_PAGE_DETAILS);
      }
      pTabCtrl->registerControl (IDC_STC_LAST_NAME,      TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_LAST_NAME,      TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_FIRST_NAME,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_FIRST_NAME,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_NAME,           TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_NAME,           TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_BIRTH_DATE,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_BIRTH_COUNTRY,  TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_BIRTH_DATE,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_BIRTH_PLACE,    TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_BIRTH_PLACE,    TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_COUNTRY_OF_BIRTH,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_GENDER,         TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_GENDER,         TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_AGE,            TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_TXT_AGE,            TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_NATIONALITY,    TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_NATIONALITY,    TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_TXT_LANGUAGE,       TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_LANGUAGE,       TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_OCCUPATION,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_OCUPATION,      TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_OCCUPATION,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_RISK_LEVEL,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_RISK_LEVEL,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_DATE_EFFECTIVE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_EFFECTIVE_DATE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_DATE_DEATH_NOTIF,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_DEATH_DATE,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_DATE_DEATH,     TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_DEATHNOTIFDATE, TXT_PAGE_DETAILS);
      //Contacts
      pTabCtrl->registerControl (IDC_EDT_EMAIL,          TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_CONTACT_NAME,   TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_HOME_TEL,       TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_TELEX,          TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_EMAIL2,         TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_SECOND_PHONENUM,      TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_SECOND_PHONENUM_EXT,  TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_EMAIL2,         TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_SECOND_PHONENUM,      TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_SECOND_PHONENUM_EXT,  TXT_PAGE_CONTACTS);

      if (strMarket == MARKET_IDS::CANADA)
      {
         pTabCtrl->registerControl (IDC_EDT_HOME_TEL_AREA,     TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_BUSINESS_TEL_AREA, TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_HOME_FAX_AREA,     TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_BUSINESS_FAX_AREA, TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_BUSINESS_TEL,      TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_HOME_FAX,          TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_BUSINESS_FAX,      TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_HOME_TEL,          TXT_PAGE_CONTACTS);
      }
      else if (strMarket == MARKET_IDS::LUXEMBOURG)
      {
         pTabCtrl->registerControl (IDC_EDT_HOME_TEL_LUX,      TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_BUSINESS_TEL_LUX,  TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_HOME_FAX_LUX,      TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_BUSINESS_FAX_LUX,  TXT_PAGE_CONTACTS);
      }

      pTabCtrl->registerControl (IDC_STC_BUSINESS_TEL,         TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_BUSINESS_EXT,         TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_BUSINESS_EXT,         TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_HOME_FAX,             TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_BUSINESS_FAX,         TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_EMAIL,                TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_CONTACT_NAME,         TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_TELEX,                TXT_PAGE_CONTACTS);

      //Tax Juris
      pTabCtrl->registerControl (IDC_STC_TAX_JURIS,                     TXT_PAGE_TAX);
      pTabCtrl->registerControl (IDC_EDT_TAX_JURIS,                     TXT_PAGE_TAX);
      pTabCtrl->registerControl (IDC_STC_TAX_JURIS_EFFECTIVE,           TXT_PAGE_TAX);
      pTabCtrl->registerControl (IDC_DTP_TAX_JURIS_EFFECTIVE,           TXT_PAGE_TAX);
      if( eusd == Y )
      {
         pTabCtrl->registerControl (IDC_STC_EUSD_OPTION,                TXT_PAGE_TAX);
         pTabCtrl->registerControl (IDC_CMB_EUSD_OPTION,                TXT_PAGE_TAX);
      }
      pTabCtrl->registerControl (IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS,  TXT_PAGE_TAX);
	  //pTabCtrl->registerControl (IDC_STC_FATCA_FFID,                    TXT_PAGE_TAX);
	  //pTabCtrl->registerControl (IDC_CMB_FATCA_FFID,                    TXT_PAGE_TAX);

      // Tab control
      ShowTabCtrl (IDC_TAB_ENTITY_MAINTENANCE, true);
      LoadTabControl (IDC_TAB_ENTITY_MAINTENANCE );
   }

   GetDlgItem(IDC_BTN_DELETE_WHERE_USED)->EnableWindow( false );

   GetDlgItem ( IDC_BTN_ENT_REG_DETAIL )->EnableWindow ( hasReadPermission(UAF::ENTITY_REGULATORY_MAINT) );

   return(TRUE);
}

//******************************************************************************
void EntityAloneDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::ENTITY_MAINTANENCE);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_ENTITIES);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_ID, IDC_LV_ENTITY_IDS);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_ENTITIES);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_ID, IDC_LV_ENTITY_IDS);

   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_LAST_NAME ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_FIRST_NAME ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_NAME ) ) )->SetMaxCharNum( 80 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_EMAIL2 ) ) )->SetMaxCharNum( 60 );

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA )
   {
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_TEL_AREA ) ) )->SetMaxCharNum( 3 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_TEL_AREA ) ) )->SetMaxCharNum( 3 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_FAX_AREA ) ) )->SetMaxCharNum( 3 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_FAX_AREA ) ) )->SetMaxCharNum( 3 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_TEL ) ) )->SetMaxCharNum( 22 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_TEL ) ) )->SetMaxCharNum( 22 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_FAX ) ) )->SetMaxCharNum( 22 );
      //( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_FAX ) ) )->SetMaxCharNum( 22 );
   }
   else if( strMarket == MARKET_IDS::LUXEMBOURG )
   {
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_TEL_LUX ) ) )->SetMaxCharNum( 22 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_TEL_LUX ) ) )->SetMaxCharNum( 22 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_FAX_LUX ) ) )->SetMaxCharNum( 22 );
      //( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_FAX_LUX ) ) )->SetMaxCharNum( 22 );
   }
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_EXT ) ) )->SetMaxCharNum( 10 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 20 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_EMAIL ) ) )->SetMaxCharNum( 60 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_CONTACT_NAME ) ) )->SetMaxCharNum( 80 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BIRTH_PLACE ) ) )->SetAllowedChars( ALPHACHARACTERS );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BIRTH_PLACE ) ) )->SetMaxCharNum( 40 );

   ConnectControlsToData();
   LoadListControl( IDC_LV_ENTITIES );
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ENTITY_LIST ) );
   DString dstrIDtype = NULL_STRING;
   getParent()->getField( this, ifds::IdType, dstrIDtype,false );
   if( dstrIDtype == ENTITY_IDS_VALUE::BIRTH_CERTIFICATE || dstrIDtype == ENTITY_IDS_VALUE::DRIVERS_LICENSE || 
       dstrIDtype == ENTITY_IDS_VALUE::PASSPORT || dstrIDtype == ENTITY_IDS_VALUE::NATIONAL_ID || 
       dstrIDtype == ENTITY_IDS_VALUE::TRUST_ACCOUNT_NUMBER || dstrIDtype == ENTITY_IDS_VALUE::BUSINESS_NUMBER ||
       dstrIDtype == ENTITY_IDS_VALUE::TAX_ID_NUMBER || dstrIDtype == ENTITY_IDS_VALUE::EMPLOYER_NUMBER  ||
       dstrIDtype == ENTITY_IDS_VALUE::BIC_CODE || dstrIDtype == ENTITY_IDS_VALUE::FATCA_GIIN ||
	   dstrIDtype == ENTITY_IDS_VALUE::SOCIAL_SECURITY_NUMBER || dstrIDtype == ENTITY_IDS_VALUE::AEOI)
   {
      GetDlgItem(IDC_CMB_COUNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);	 
      GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);
   }
   else
   {
      GetDlgItem(IDC_CMB_COUNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);	 
      GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);
   }

   DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
   if (pTabCtrl != NULL)
   {
      CString cstrDetailsPageName, cstrPageName;
      TCITEM tcItem;
      wchar_t buffer[256] = {0};
      tcItem.pszText = buffer;
      tcItem.cchTextMax = 256;
      tcItem.mask = TCIF_TEXT;

      int iPagePos = pTabCtrl->GetCurSel();
      pTabCtrl->GetItem(iPagePos, &tcItem);

      cstrPageName = tcItem.pszText;
      cstrDetailsPageName.LoadString( TXT_PAGE_DETAILS);
      if( cstrDetailsPageName == cstrPageName )
      {
         DString strRiskLevel;
         getParent()->getField (this, 
                                IFASTBP_PROC::ENTITY_LIST, 
                                ifds::RiskLevel,
                                strRiskLevel,
                                false);
         strRiskLevel.strip().upperCase();
         if (POLITICALLY_EXPOSED_PERSON != strRiskLevel) {
            GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
            GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
         }
         else{
            GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
         }
      }
   }

   UpdateData(FALSE);
}

//******************************************************************************
SEVERITY EntityAloneDlg::doInit()
{
   DString dstrSalutationEdit;
   getParent()->getField( this, EntityAlone::SALUTATION_EDIT, dstrSalutationEdit );
   m_bSalutationFreeFormat = (dstrSalutationEdit == I_("Y"));
   return(NO_CONDITION);
}

//********************************************************************************
void EntityAloneDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ENTITY_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::ENTITY_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_ENTITIES, crtKey );
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ENTITY_LIST ) );
}

//********************************************************************************
void EntityAloneDlg::OnBtnMoreWhereUsed()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMoreWhereUsed"));
   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::WHEREUSED_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::WHEREUSED_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LST_WHERE_USED, crtKey );
   }
   GetDlgItem(IDC_BTN_MORE_WHERE_USED)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::WHEREUSED_LIST ) );

}

//******************************************************************************
void EntityAloneDlg::OnBtnAdminDates()
{
   ShowAdminDates( IFASTBP_PROC::ENTITY_LIST );
}

//******************************************************************************
bool EntityAloneDlg::doRefresh( GenericInterface * /*rpGICaller*/,
                                const I_CHAR * //*szOriginalCommand
                              )
{

   return(true);
}

//***************************************************************************
void EntityAloneDlg::DoListItemChanged( UINT listControlID,
                                        const DString &strKey,
                                        bool isNewItem,
                                        bool bIsDummyItem
                                      )
{
   DString strMarket = DSTCommonFunctions::getMarket();
   DString str, str1;
   bool bNewDummyItem = isNewItem || bIsDummyItem ? true : false;

   switch( listControlID )
   {
      case IDC_LV_ENTITIES:
         {
            DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
            if (pTabCtrl != NULL)
            {
               pTabCtrl->SelectTab ( TXT_PAGE_DETAILS );

            }
            // Historical Button
            GetDlgItem(IDC_BTN_ENTITY_HISTORY)->EnableWindow (!bNewDummyItem);
            DString dstrUpdate,status;
            getParent()->getField(this,EntityAlone::UPDATE_SHAREHOLDER,dstrUpdate,false);
            GetDlgItem(IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS)->EnableWindow( (dstrUpdate == Y) ? true : false );
            GetDlgItem( IDC_BTN_MORE_WHERE_USED )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::WHEREUSED_LIST ) );


            // the code here is to avoid issue in basedlg class
            // ideally it should be fixed in base classes.
            int iNum = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::WHEREUSED_LIST );
            if( iNum == 0 )
            {
               LoadListControl( IDC_LST_WHERE_USED );
            }

            if (bNewDummyItem)
               GetDlgItem(IDC_BTN_CUTOFF_TIME)->EnableWindow (!bNewDummyItem);
            else
            {
               bool bDisable = disableCutOffTimeButton ();
               GetDlgItem(IDC_BTN_CUTOFF_TIME)->EnableWindow (bDisable);
            }
            //prevent crashing for 'Bad' entity
            DString strBadGoodEntity;
            getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST,ifds::GoodBad,strBadGoodEntity,false);
            GetDlgItem( IDC_BTN_RESET )->EnableWindow( (strBadGoodEntity.strip().upperCase() == Y) ? true : false );

            pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
            if (pTabCtrl != NULL)
            {
               CString cstrDetailsPageName, cstrPageName;
               TCITEM tcItem;
               wchar_t buffer[256] = {0};
               tcItem.pszText = buffer;
               tcItem.cchTextMax = 256;
               tcItem.mask = TCIF_TEXT;

               int iPagePos = pTabCtrl->GetCurSel();
               pTabCtrl->GetItem(iPagePos, &tcItem);

               cstrPageName = tcItem.pszText;
               cstrDetailsPageName.LoadString( TXT_PAGE_DETAILS);
               if( cstrDetailsPageName == cstrPageName )
               {
                  DString strRiskLevel;
                  getParent()->getField (this, 
                                         IFASTBP_PROC::ENTITY_LIST, 
                                         ifds::RiskLevel,
                                         strRiskLevel,
                                         false);
                  strRiskLevel.strip().upperCase();
                  if (POLITICALLY_EXPOSED_PERSON != strRiskLevel) {
                     GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                     GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                  }
                  else{
                     GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
                     GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
                  }
               }
            }
         }
         break;
      case IDC_LST_WHERE_USED:
         {
            DString strEntityWhereUsed;
            getParent()->getField (this, IFASTBP_PROC::WHEREUSED_LIST, ifds::WhereUse, strEntityWhereUsed, false);

            if ( strEntityWhereUsed == ENTITY_WHEREUSED_VALUE::COUNTRY )
            {
               ConnectControlsToData (ENTITY_WHEREUSED_CONTROLS::EDIT_CNTRL, false);
               ConnectControlsToData (ENTITY_WHEREUSED_CONTROLS::COMBO_CNTRL,true );
               LoadControls (ENTITY_WHEREUSED_CONTROLS::COMBO_CNTRL);
            }
            else
            {
               ConnectControlsToData (ENTITY_WHEREUSED_CONTROLS::COMBO_CNTRL, false);
               ConnectControlsToData (ENTITY_WHEREUSED_CONTROLS::EDIT_CNTRL,true );
               LoadControls (ENTITY_WHEREUSED_CONTROLS::EDIT_CNTRL);
            }

            LoadControls (IDC_LV_ENTITIES);

            DString strEntityIDType;
            getParent()->getField (this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType, strEntityIDType, false);

            if ( strEntityIDType == ENTITY_IDS_VALUE::CLEARING_PLATFORM )
            {
               ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, false);
               ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,true );
               LoadControls (ENTITY_IDS_CONTROLS::COMBO_CNTRL);
            }
            else
            {
               ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL, false);
               ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL,true );
               LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
            }

            LoadControls (IDC_LV_ENTITY_IDS);
         }
         break;
      case IDC_LV_ENTITY_IDS:
         {
            DString strEntityIDType;
            getParent()->getField (this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType, strEntityIDType, false);

			EnableEntityIdsControls(UAF::ENTITY_MAINTANENCE, isNewItem);
			if (strEntityIDType == ENTITY_IDS_VALUE::TAX_FILE_NUMBER )
			{
				EnableEntityIdsControls(UAF::APAC_SUPREGN, isNewItem);
			}

            if ( strEntityIDType == ENTITY_IDS_VALUE::CLEARING_PLATFORM )
            {
               ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, false);
               ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,true );
               LoadControls (ENTITY_IDS_CONTROLS::COMBO_CNTRL);
            }
            else
            {
               ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL, false);
               ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL,true );
               LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
            }

            LoadControls (IDC_LV_ENTITY_IDS);

            break;
         }
     default:
        break;
   }
}

//********************************************************************************
void EntityAloneDlg::OnBtnAddWhereUsed()
{
   AddToListControl( IDC_LST_WHERE_USED );
}

//*********************************************************************************
void EntityAloneDlg::OnBtnDelWhereUsed()
{
    DeleteFromListControl( IDC_LST_WHERE_USED );
}

//******************************************************************************
void EntityAloneDlg::OnBtnAdd()
{
   AddToListControl( IDC_LV_ENTITIES );
   EnableControl( IDOK, true );
   FocusOnControl( IDC_CMB_ID_TYPE );
}

//******************************************************************************
void EntityAloneDlg::OnBtnDelete()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnDelete()" ) );

    int nr = GetList( IDC_LV_ENTITIES )->GetItemCount();
    DeleteFromListControl( IDC_LV_ENTITIES );
    if( nr == 1 ) //that means a dummy entity will be added after deletion of the last entity in the list
    {
      EnableControl( IDC_BTN_SEARCH, true );
    }
}

//******************************************************************************
void EntityAloneDlg::OnBtnDeleteId()
{
   DeleteFromListControl( IDC_LV_ENTITY_IDS );
}

//********************************************************************************
void EntityAloneDlg:: OnBtnSearch()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch" ) );

   DString lastName, firstName, birthLastName, birthFirstName, homeTel, businessTel;
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, lastName, false );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, firstName, false );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::BirthLastName, birthLastName, false );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::BirthFirstName, birthFirstName, false );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::HomePhone, homeTel, false );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::BusinessPhone, businessTel, false );

   bool bSearch = false;

   if(lastName.strip() != NULL_STRING || firstName.strip() != NULL_STRING )
   {
         setParameter( ENTITYALONESEARCH::SEARCH_CODE, SEARCHENTITYUSING::NAME );
         setParameter( ENTITYALONESEARCH::FIRST_VALUE, firstName );
         setParameter( ENTITYALONESEARCH::SECOND_VALUE, lastName );
         bSearch = true;
   }

   if( bSearch )
   {
      setParameter( ENTITYALONESEARCH::ALLENTITY, YES );
      setParameter( ENTITYALONESEARCH::EXACTSEARCH, NO );
      setParameter( ENTITYALONESEARCH::FROM_SCR, ENTITYALONESEARCH::ENTITY_ALONE );

      try
      {
         invokeCommand( this, CMD_BPROC_ENTITY_SEARCH, getProcessType(), true, NULL ); // invoke model dialoge
      }
      catch (ConditionException &ce)
      {
         ConditionMessageBox(ce);
      }
      catch (...)
      {
         assert(0);
         DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      }
   }
}

//******************************************************************************
void EntityAloneDlg::OnBtnAddId()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAddId" ) );

   AddToListControl( IDC_LV_ENTITY_IDS );
}

//******************************************************************************
void EntityAloneDlg::OnBtnReset()
{
   //We do reset for the selected Entity CBO first (which is not register as container in the process)

   ResetListItem( IDC_LV_ENTITIES );
   LoadTabControl (IDC_TAB_ENTITY_MAINTENANCE );

/*   DString strYears, strMonths;
   getParent()->getField( this, ENTPROC::AGE_YEARS, strYears );
   getParent()->getField( this, ENTPROC::AGE_MONTHS, strMonths );
   CString yrs, mnths, comma;
   yrs.LoadString( TXT_YEARS );
   mnths.LoadString( TXT_MONTHS );
   comma.LoadString( TXT_COMMA );

   DString strAge = strYears + SPACE_STRING + ( LPCTSTR ) yrs + ( LPCTSTR ) comma + SPACE_STRING + strMonths + SPACE_STRING + ( LPCTSTR ) mnths;
   GetDlgItem( IDC_TXT_AGE )->SetWindowText( strAge.c_str() );*/
}


//******************************************************************************
bool EntityAloneDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   if( lSubstituteId == ifds::EntityIDSHeadingSet.getId() )
   {
      if ( ColumnKey == ENTITY_ID_VALUE_COLUMN )
      {
         DString strIDType;
         getParent()->getField( this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType, strIDType, false );
         if ( strIDType == ENTITY_IDS_VALUE::CLEARING_PLATFORM )
         {
            getParent()->getField( this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue, strOut, true );
         }
         else
         {
            getParent()->getField( this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue, strOut, false );
         }
         strOut.strip();
         return(true);
      }
      else
      {
         return ( false );
      }
   }

   return false;
}

//******************************************************************************
bool EntityAloneDlg::PreOk()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("PreOk" ) ) ;

   return true;
}

//******************************************************************************
void EntityAloneDlg::PostOk( bool /*bOkStatus*/ )
{
}

//******************************************************************************
bool EntityAloneDlg::GetDataForControl( UINT controlID, DString &strValueOut, bool bFormatted, int index ) const
{
   strValueOut = NULL_STRING;
   CString str;

   switch( controlID )
   {

      case IDC_TXT_AGE:
         {
            DString strYears, strMonths;
            getParent()->getField( this, EntityAlone::AGE_YEARS, strYears );
            getParent()->getField( this, EntityAlone::AGE_MONTHS, strMonths );
            CString yrs, mnths, comma;
            yrs.LoadString( TXT_YEARS );
            mnths.LoadString( TXT_MONTHS );
            comma.LoadString( TXT_COMMA );
            if( !strYears.empty() && strYears.asInteger() >= 0 )
               strValueOut = strYears + SPACE_STRING + ( LPCTSTR ) yrs + ( LPCTSTR ) comma + SPACE_STRING + strMonths + SPACE_STRING + ( LPCTSTR ) mnths;
            else
               strValueOut = NULL_STRING;
         }
         break;

      default :
         return(false);
   }
   strValueOut.strip();
   return(true);
}

//******************************************************************************
/*void EntityAloneDlg::OnAccelEntity()
{
   FocusOnControl( IDC_LV_ENTITIES );
}

*/

//**********************************************************************************
void EntityAloneDlg::ControlUpdated(UINT controlID, const DString &dstrValue)
{
   DString str;
   switch( controlID )
   {

      case IDC_CMB_ID_TYPE:
         if( dstrValue == SIN )
         {
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( false );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( true ); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 9 );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars(I_("0123456789"));
            LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
         }
         else if( dstrValue == NEQ )
         {
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( false );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( true ); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 10 );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars( I_("0123456789") );
            LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
         }
         else if ( dstrValue == TAX_ID_NUM )
         {
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( false );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( true ); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 40 );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars( CHARACTERS );
            LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
         }
         else if ( dstrValue == DEPOSITARY_BANK_ACCOUNT )
         {
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( false );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( true ); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 35 );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars( CHARACTERS );
            LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
         }
         else if ( dstrValue == ENTITY_IDS_VALUE::CLEARING_PLATFORM )
         {
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( true );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( false ); 
            GetDlgItem ( IDC_CMB_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, false);
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,true );
            LoadControls (ENTITY_IDS_CONTROLS::COMBO_CNTRL);
         }

		 else if ( dstrValue == ENTITY_IDS_VALUE::FAST ||
			       dstrValue == ENTITY_IDS_VALUE::iFAST_OEIC ||
				   dstrValue == ENTITY_IDS_VALUE::iFAST_SICAV)
		 {
		    GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( SW_HIDE );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( SW_SHOW); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( SW_SHOW );

            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false ); 

			( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 20 );
			LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
		 }
         else
         {
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( false );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( true ); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 20 );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars( NULL_STRING );
            LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
         }

         if( dstrValue == ENTITY_IDS_VALUE::BIRTH_CERTIFICATE || dstrValue == ENTITY_IDS_VALUE::DRIVERS_LICENSE || 
             dstrValue == ENTITY_IDS_VALUE::PASSPORT || dstrValue == ENTITY_IDS_VALUE::NATIONAL_ID ||
             dstrValue == ENTITY_IDS_VALUE::TRUST_ACCOUNT_NUMBER || dstrValue == ENTITY_IDS_VALUE::BUSINESS_NUMBER ||
             dstrValue == ENTITY_IDS_VALUE::TAX_ID_NUMBER || dstrValue == ENTITY_IDS_VALUE::EMPLOYER_NUMBER ||
             dstrValue == ENTITY_IDS_VALUE::BIC_CODE || dstrValue == ENTITY_IDS_VALUE::FATCA_GIIN || 
             dstrValue == ENTITY_IDS_VALUE::SOCIAL_SECURITY_NUMBER || dstrValue == ENTITY_IDS_VALUE::AEOI )
         {
            GetDlgItem(IDC_CMB_COUNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);
         }
         else
         {
            GetDlgItem(IDC_CMB_COUNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);
         }

         LoadControls (IDC_LV_ENTITY_IDS);
         break;
      case IDC_DTP_BIRTH_DATE:
         {
            DString strMarket = DSTCommonFunctions::getMarket();
            if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
               LoadControl( IDC_TXT_AGE );
         }
         break;
      case IDC_CMB_OCUPATION:
         // Display Other Edit field if Occupation is 'Other' (Code 08)
         LoadControl( IDC_EDT_OCCUPATION );
         GetDlgItem( IDC_EDT_OCCUPATION )->ShowWindow( ( dstrValue == I_("08") ) ? SW_SHOW : SW_HIDE );
         break;
      case IDC_CMB_EMPLOYEECLASS:
         {
            DString dstrNameLength = NULL_STRING;
            getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::NAME_LENGTH, dstrNameLength, false );
            int iMaxCharNum = dstrNameLength.asInteger();
            bool bShowName = ( dstrValue == CODE_CATEGORY_CORPORATE );
            DSTTabCtrl* pTabCtrl = GetTabCtrl( IDC_TAB_ENTITY_MAINTENANCE );
            pTabCtrl->showTabControl( IDC_EDT_FIRST_NAME,0, !bShowName  );
            pTabCtrl->showTabControl( IDC_EDT_LAST_NAME,0, !bShowName  );
            pTabCtrl->showTabControl( IDC_STC_FIRST_NAME,0, !bShowName  );
            pTabCtrl->showTabControl( IDC_STC_LAST_NAME,0, !bShowName  );
            pTabCtrl->showTabControl( IDC_STATIC_SALUTATION,0, !bShowName  );
            pTabCtrl->showTabControl( IDC_EDT_NAME,0, bShowName  );
            pTabCtrl->showTabControl( IDC_STC_NAME,0, bShowName  );

            pTabCtrl->showTabControl( m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION,
                              0, !bShowName  );

            ConnectControlToData( IDC_EDT_LAST_NAME, !bShowName );
            ConnectControlToData( IDC_EDT_NAME, bShowName );
            if( iMaxCharNum > 0 )
            {
               dynamic_cast< DSTEdit * >( GetControl( bShowName ? IDC_EDT_NAME : IDC_EDT_LAST_NAME ) )->SetMaxCharNum( iMaxCharNum );
            }
            else
            {
               // Use default maximum number of characters if category value is 0 or undefined.
               if( bShowName )
               {
                  dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_NAME ) )->SetMaxCharNum( 80 );
               }
               else
               {
                  dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_LAST_NAME ) )->SetMaxCharNum( 40 );
               }
            }
            LoadControl( IDC_EDT_NAME );
            LoadControl( IDC_EDT_FIRST_NAME );
            LoadControl( IDC_EDT_LAST_NAME );
            LoadControl( m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION );
            break;
         }
       case IDC_EDT_WHERE_USED_CODE:
          {
            DString dstrWhereUse;
            getParent()->getField (this, IFASTBP_PROC::WHEREUSED_LIST, ifds::WhereUse, dstrWhereUse, false);

            if ( dstrWhereUse == ENTITY_WHEREUSED_VALUE::COUNTRY )
            {
               GetDlgItem ( IDC_EDT_CODE )->ShowWindow ( false );
               GetDlgItem ( IDC_CMB_CODE )->ShowWindow ( true ); 
               GetDlgItem ( IDC_CMB_CODE )->EnableWindow ( true );
               GetDlgItem ( IDC_CMB_WHERE_USED_RELATION )->EnableWindow ( false );
               ConnectControlsToData (ENTITY_WHEREUSED_CONTROLS::EDIT_CNTRL, false);
               ConnectControlsToData (ENTITY_WHEREUSED_CONTROLS::COMBO_CNTRL,true );
               LoadControl (IDC_CMB_CODE);
            }
            else
            {
               GetDlgItem ( IDC_CMB_CODE )->ShowWindow ( false );
               GetDlgItem ( IDC_EDT_CODE )->ShowWindow ( true ); 
               GetDlgItem ( IDC_EDT_CODE )->EnableWindow ( true );
               GetDlgItem ( IDC_CMB_WHERE_USED_RELATION )->EnableWindow ( true ); 
			   if( dstrWhereUse == ENTITY_WHEREUSED_VALUE::REG_AGENT )
			   {
				   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_CODE ))->SetAllowedChars(REG_AGENT_CODE_SET_CHAR); 
			   }	
               else if ( dstrWhereUse == ENTITY_WHEREUSED_VALUE::LEGAL_ENTITY)
               {
                  dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_CODE ))->SetAllowedChars(ALPHACHARACTERS); 
               }
			   else
			   {
				   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_CODE ))->SetAllowedChars(_T(""));
			   }
               ConnectControlsToData (ENTITY_WHEREUSED_CONTROLS::COMBO_CNTRL, false);
               ConnectControlsToData (ENTITY_WHEREUSED_CONTROLS::EDIT_CNTRL,true );
               LoadControl (IDC_EDT_CODE);
            }

            // enable Mgmt Fee button only when Where Used = Holding Entity...
            GetDlgItem(IDC_BTN_ENTITY_MANAGEMENT_FEE)->EnableWindow (dstrWhereUse == HOLDING_ENTITY);

            // enable KYC button only when Where Used = Account
            GetDlgItem(IDC_BTN_KYC)->EnableWindow ( dstrWhereUse == ACCOUNT );

            break;
          }
       case IDC_CMB_WHERE_USED_RELATION:
         {
            DString dstrWhereUse;
            getParent()->getField (this, IFASTBP_PROC::WHEREUSED_LIST, ifds::WhereUse, dstrWhereUse, false);

            if ( dstrWhereUse == ENTITY_WHEREUSED_VALUE::COUNTRY )
            {
               LoadControl (IDC_CMB_CODE);
            }
            else
            {
               LoadControl (IDC_EDT_CODE);
            }

            break;
         }
     case IDC_CMB_RISK_LEVEL:
        {
           DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
           if (pTabCtrl != NULL)
           {
              CString cstrDetailsPageName, cstrPageName;
              TCITEM tcItem;
              wchar_t buffer[256] = {0};
              tcItem.pszText = buffer;
              tcItem.cchTextMax = 256;
              tcItem.mask = TCIF_TEXT;

              int iPagePos = pTabCtrl->GetCurSel();
              pTabCtrl->GetItem(iPagePos, &tcItem);

              cstrPageName = tcItem.pszText;
              cstrDetailsPageName.LoadString( TXT_PAGE_DETAILS);
              if( cstrDetailsPageName == cstrPageName )
              {
                  DString strRiskLevel;
                  getParent()->getField (this, 
                                         IFASTBP_PROC::ENTITY_LIST, 
                                         ifds::RiskLevel,
                                         strRiskLevel,
                                         false);
                  strRiskLevel.strip().upperCase();
                  if (POLITICALLY_EXPOSED_PERSON != strRiskLevel) {
                     GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                     GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                  }
                  else{
                     GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
                     GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
                  }
              }
           }
        }
        break;
      default:
         break;
   }

}

//******************************************************************************
bool EntityAloneDlg::doSend( GenericInterface *rpGICaller,
                             const I_CHAR * szMessage)
{
   //I know that overwriting this method in this way looks weird for now
   //I just wanted to be sure that, if overwritten, the call to the base class for WarningConfirm will be there
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" doSend() " ) );
   bool bRetVal = true;

   DString str( szMessage );
   if( str == I_( "WarningConfirm" ) || str == I_( "TrxnsError" ) )
      bRetVal = AbstractBaseMainDlg::doSend(rpGICaller, szMessage);

   return(bRetVal);
}

//******************************************************************************
void EntityAloneDlg::EnableEntityIdsControls( const I_CHAR * functionCode, bool isNewItem )
{
	bool bRead = hasReadPermission(functionCode);
	bool bCreate = hasCreatePermission(functionCode);
	bool bUpdate = hasUpdatePermission(functionCode);
	bool bDel  = hasDeletePermission(functionCode);

  // For APAC_SUPREGN band, user is able to add new TFN Number.
  if(!isNewItem || functionCode != UAF::APAC_SUPREGN)
  {
	  EnableControl(IDC_CMB_ID_TYPE, bRead && bUpdate);
	  EnableControl(IDC_EDT_ID_VALUE, bRead && bUpdate);
	  EnableControl(IDC_DTP_ID_DATE, bRead && bUpdate);
	  EnableControl(IDC_DTP_ID_DATE_EXPIRE, bRead && bUpdate);
	  EnableControl(IDC_BTN_DELETE_ID, bDel);
  }
}

//******************************************************************************
bool EntityAloneDlg::doDisablePermCheckButton(UINT nID)
{
   TRACE_METHOD( CLASSNAME, I_( "doDisablePermCheckButtons" ));

   bool bDisable = false;
   DString status;
    getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::GoodBad, status,false);
    status.strip().upperCase();

   if( nID == IDC_BTN_DELETE    ||
       nID == IDC_BTN_DELETE_ID ||
       nID == IDC_BTN_ADD_ID    ||
       nID == IDC_ADD_WHERE_USED )
   {
      DString accountEntity;
      getParent()->getField(this, EntityAlone::ACCOUNT_ENTITY,accountEntity,false ); // if it is account entity, user can not delete any thing.
      if( accountEntity == Y || status == I_("N") )
      {
         bDisable = true;
      }
      else if (nID == IDC_BTN_DELETE)
         bDisable = disableEntityDeleteButton ();
   }
   else if ( nID == IDC_BTN_DELETE_WHERE_USED )
   {
      if(status == I_("N"))
         bDisable = true;
      else
         bDisable = disableWhereUseDeleteButton ();
   }
   else if (nID == IDC_BTN_CUTOFF_TIME)
   {
      if(status == I_("N") )
      {
         bDisable = true;
      }
      else
         bDisable = disableCutOffTimeButton ();
   }

   return bDisable;
}
//******************************************************************************

bool EntityAloneDlg::disableCutOffTimeButton ()
{
   bool  bDisable = false;
   int       nItems = 0;

   nItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::WHEREUSED_LIST );
   AbstractProcess * pParentProcess = dynamic_cast<AbstractProcess *>(getParentProcess());

   if ( nItems == 0 || (nItems == 1 && pParentProcess->isCurrentListItemDummy(this, IFASTBP_PROC::WHEREUSED_LIST)))
      bDisable = true;
   else
   {
      DString dstrIsNetworkSender;
      getParent ()->getField ( this, ifds::IsNetworkSender, dstrIsNetworkSender, false);

      bDisable = dstrIsNetworkSender == I_("Y") ? false : true;
   }

   return bDisable;
}

//******************************************************************************
bool EntityAloneDlg::disableWhereUseDeleteButton ()
{
   int       nItems = 0;
   bool  bDisable = false;

   nItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::WHEREUSED_LIST );
   AbstractProcess * pParentProcess = dynamic_cast<AbstractProcess *>(getParentProcess());

   if ( nItems == 0 || (nItems == 1 && pParentProcess->isCurrentListItemDummy(this, IFASTBP_PROC::WHEREUSED_LIST)))
   {
      bDisable = true;
   }
   else
   {
      DString dstrWhereUse;
      getParent()->getField( this, IFASTBP_PROC::WHEREUSED_LIST, ifds::WhereUse, dstrWhereUse, false );

      if (dstrWhereUse == EXTERNAL_PRODUCT_PROVIDER)
      {
	      DSTCWorkSession *pDSTCWorkSession = 
               dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

         assert (pDSTCWorkSession);
         bDisable = !pDSTCWorkSession->hasDeletePermission (UAF::EXTERNAL_PROVIDER_UPDATE);
      }
      else if ( dstrWhereUse == ACCOUNT || dstrWhereUse == FUNDBROKER )
      {
         bDisable = true;
      }
      else
      {
         // it is either CLIENT or FUND
         DString dstrRelationship;
         getParent()->getField( this, IFASTBP_PROC::WHEREUSED_LIST, ifds::EntityType, dstrRelationship, false );

         if (dstrRelationship == PAYING_AGENT)
         {
            bDisable = pParentProcess->isCurrentListItemNew (this, IFASTBP_PROC::WHEREUSED_LIST)? false : true;
         }
         else
         {
            bDisable = false;
         }
      }
   }

   return bDisable;
}

//******************************************************************************
bool EntityAloneDlg::disableEntityDeleteButton ()
{
   int   nItems   = 0;
   bool  bDisable = true;
   AbstractProcess * pParentProcess = dynamic_cast<AbstractProcess *>(getParentProcess());

   nItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::WHEREUSED_LIST );

   if (nItems == 1 && pParentProcess->isCurrentListItemDummy(this, IFASTBP_PROC::WHEREUSED_LIST))
      bDisable = false;
   else if (pParentProcess->isCurrentListItemNew(this, IFASTBP_PROC::ENTITY_LIST))
      bDisable = false;

   return bDisable;
}

//******************************************************************************
void EntityAloneDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   IFastHistoricalInfo historicalInfo;
   historicalInfo( this, IFASTBP_PROC::ENTITY_LIST, I_("MULTI") );
}

//******************************************************************************
void EntityAloneDlg::OnBtnCutOffTime()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnCutOffTime" ) );

   try
    {
      E_COMMANDRETURN eRtn;
      DString        dstrEntityId;

      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false);
      getParent()->setParameter( I_("EntityId"), dstrEntityId);

      eRtn = invokeCommand( getParent(), CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES, PROC_SUPPORT, true, NULL );

        switch( eRtn )
        {
         case CMD_OK:
            case CMD_CANCEL:
            case CMD_MODELESS_INPROCESS:
            break;

         default:
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
void EntityAloneDlg::tabSelectionChanged( UINT tabControlID, const DString& strPageName )
{
   CString cstrPageName;
   cstrPageName.LoadString( TXT_PAGE_DETAILS );
   if( strPageName.c_str() == cstrPageName )
   {
      DString dstrValue;
      getParent()->getField( this, ifds::OccupationCode, dstrValue, false );
      ControlUpdated(IDC_CMB_OCUPATION, dstrValue);
      getParent()->getField( this, ifds::EmployeeClass, dstrValue, false );
      ControlUpdated(IDC_CMB_EMPLOYEECLASS, dstrValue);
   }

}

//******************************************************************************
void EntityAloneDlg::OnChkUpdateShareholder()
{

   UpdateData(true);
   getParent()->setField( this, IFASTBP_PROC::ENTITY_LIST, ifds::UpdShrTaxJuris,
      m_bUpdateShareholder? Y:N, false );
}

//*******************************************************************************
void EntityAloneDlg::OnBtnAddress()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAddress" ) );


   try
   {
      DString dstrEntityId, dstrShareholderNum;
      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false);
      setParameter( ADDRLIT::ENTITY_ID,       dstrEntityId);
      setParameter( ADDRLIT::FROM_ENTITY ,    I_( "Y" ) );
      setParameter( I_("ENTITY_ALONE") ,      I_( "Y" ) );
      SetMessageStatusBar( TXT_LOAD_ADDRESS_BOOK );
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADDRESSES, PROC_SUPPORT, true, NULL );
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

//*******************************************************************************
void EntityAloneDlg::OnBtnManagementFee()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnManagementFee" ) );

   // Button should only be enabled IF Where_Used = 07

   try
   {
      E_COMMANDRETURN eRtn = CMD_OK;

      SetMessageStatusBar( TXT_LOAD_MANAGEMENT_FEE );

      DString dstrEntityId;
      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false);
      setParameter (I_( "EntityID" ), dstrEntityId);
      
      DString urlParamsIDI;

      addIDITagValue (urlParamsIDI, I_("EntityID"), dstrEntityId);
      setParameter (I_("UrlParams"), urlParamsIDI);   
	  CString cstrMgmtFeeSetup;
	  cstrMgmtFeeSetup.LoadString(TXT_MANAGEMENT_FEE_SETUP_ENTITY_ID);
	   setParameter (I_("BrowserTitle"), DString(cstrMgmtFeeSetup) + dstrEntityId);
      setParameter (I_("from_screen"),  I_("EntityAloneDlg"));

      eRtn = getParentProcess()->invokeProcessFromChild( getParent(), CMD_BPROC_MANAGEMENT_FEE, PROC_SUPPORT );

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
LRESULT EntityAloneDlg::OpenFundGroupDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundGroupDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      CString cstrValue;

      setParameter (MFCAN_IP_PARAM::SPONSOR_GROUP, I_("SPONSOR"));

      //setParameter( FUND_CODE, NULL_STRING );
      //GetFocus()->GetWindowText( cstrValue );
      //DString dstrValue( cstrValue );

      if ( GetFocus()->GetDlgCtrlID() != IDC_EDT_CODE )
         return(0);

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDGROUP, PROC_NO_TYPE, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundGroupCode;
               getParameter (I_("FUNDSPONSOR"), dstrFundGroupCode );
               getParent()->setField( this, IFASTBP_PROC::WHEREUSED_LIST, ifds::WhereUseCode, dstrFundGroupCode );
               LoadControl( IDC_EDT_CODE );
            }
         case CMD_CANCEL:
            break;
         default:
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
LRESULT EntityAloneDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      CString cstrValue;

      setParameter( FUND_CODE, NULL_STRING );
      GetFocus()->GetWindowText( cstrValue );
      DString dstrValue( cstrValue );

      if ( GetFocus()->GetDlgCtrlID() != IDC_EDT_CODE )
      return(0);

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode;
               getParameter ( FUND_CODE, dstrFundCode );
               getParent()->setField( this, IFASTBP_PROC::WHEREUSED_LIST, ifds::WhereUseCode, dstrFundCode );
               LoadControl( IDC_EDT_CODE );
            }
         case CMD_CANCEL:
            break;
         default:
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
BOOL EntityAloneDlg::PreTranslateMessage (MSG*pMsg)
{
   if ( pMsg->message == WM_KEYDOWN &&
        (int) (pMsg->wParam) == VK_F4)
   {
      if ( GetFocus () == GetDlgItem (IDC_EDT_CODE) )
      {
         DString dstrWhereUse;
         getParent()->getField( this, IFASTBP_PROC::WHEREUSED_LIST, ifds::WhereUse, dstrWhereUse, false );

         if ( dstrWhereUse == FUND)
            PostMessage (UM_OPENFUNDCLASSLISTDLG);
         else if (dstrWhereUse == FUNDSPONSOR)
            PostMessage (UM_OPENFUNDGROUPDLG);
      }
   }

   return BaseMainDlg::PreTranslateMessage (pMsg);
}

//******************************************************************************
void EntityAloneDlg::OnBtnKYC()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnKYC" ) );

   try
   {
      DString dstrEntityId,
              dstrEntityType,
              dstrAcctNumber;

      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false);

      dstrAcctNumber = I_("0");
      setParameter( ENTITYALONEDLG::ENTITY_ID, dstrEntityId );
      setParameter( ENTITYALONEDLG::ACCOUNT_NUM, dstrAcctNumber );
      setParameter( ENTITYALONEDLG::CALLER, ENTITYALONEDLG::ENTITY );

      E_COMMANDRETURN eRtn;

      eRtn = invokeCommand( getParent(), CMD_BPROC_DEMOGRAPHICS, PROC_SUPPORT, true, NULL );

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
void EntityAloneDlg::OnBtnEntRegDetail()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnEntRegDetail" ) );

   try
   {
      DString dstrEntityId, dstrIsUnderAccount, dstrAccountNum;

      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false);   
	  
	  setParameter( I_("AccountNum") , I_("0") ); 	  
      setParameter( I_("EntityId") ,  dstrEntityId); 
      setParameter( I_("Caller") ,  I_("AllEntity")); 

      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ENT_REG_MAINT, PROC_SUPPORT, true, NULL );

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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EntityAloneDlg.cpp-arc  $
// 
//    Rev 1.43   Jul 17 2012 10:52:54   dchatcha
// P0179630 FN01 FATCA Project - Entity level.
// 
//    Rev 1.42   Jul 17 2012 10:40:34   dchatcha
// P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts, code review.
// 
//    Rev 1.41   Jul 16 2012 12:30:26   dchatcha
// P0179630 FN01 FATCA Project - Entity level.
// 
//    Rev 1.40   Jul 12 2012 11:36:48   dchatcha
// P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
// 
//    Rev 1.39   Apr 19 2012 13:22:46   wp040039
// PETP0187485- Agent bank and CPFB
// Incident# 2926984
// 
//    Rev 1.38   Apr 04 2012 22:59:08   wp040039
// PETP0187485-Entity Maintenance
// 
//    Rev 1.37   Mar 29 2012 21:29:44   wp040039
// PETP0187485.FN01- CPF - Agent bank and CPFB 
// Added for checking space is not allowed between Registration Agent code
// 
//    Rev 1.36   Nov 25 2011 15:59:50   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.35   Nov 21 2011 18:44:08   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.34   Nov 19 2011 01:33:34   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.33   May 13 2010 13:34:56   jankovii
// Fixed NEQ.
// 
//    Rev 1.32   May 12 2010 11:59:14   popescu
// RESP/QESI - adding extra security to the EPP where used type
// 
//    Rev 1.31   Sep 28 2009 08:35:24   dchatcha
// P0163546 FN01 TA Automate Fund Transfer.
// 
//    Rev 1.30   Jan 27 2009 06:36:12   daechach
// IN 1548019 - fix some issues found in retesting.
// 
//    Rev 1.29   Jan 07 2009 04:48:58   daechach
// IN 1544134 - R91-MT535/MT536-Clearing platform BIC code disp blank, etc.
// 
//    Rev 1.28   Nov 11 2008 05:13:54   daechach
// PET5517 FN71 Unclaimed Property Phase 2 - disable 'KYC' button when Entity Where Used type is not 'Account'
// 
//    Rev 1.27   Nov 06 2008 07:05:10   daechach
// PET5517 FN71 Unclaimed Property Phase 2 - disable relationship when where use type is country.
// 
//    Rev 1.26   Nov 06 2008 02:38:54   daechach
// PET5517 FN71 Unclaimed Property Phase 2
// 
//    Rev 1.25   Sep 12 2008 07:08:22   daechach
// PET0128026 - KYC Phase 2
// 
//    Rev 1.24   06 Dec 2007 15:20:26   popescu
// Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
// 
//    Rev 1.23   21 Aug 2007 17:50:50   popescu
// Incident 983396 - Can't access Management Fee Screen
// 
//    Rev 1.22   15 Aug 2007 14:29:32   popescu
// PET2360 - Web Integration - "Enable Mgmt Fee button only when Where_Used = Holding Entity ('07')" - to fix a crash
// 
//    Rev 1.21   Aug 13 2007 10:16:34   ivespaul
// PET2360 - Web Integration - "Enable Mgmt Fee button only when Where_Used = Holding Entity ('07')"
//
//    Rev 1.20   Aug 10 2007 18:34:48   ivespaul
// PET2360 - Web Integration - moved button from Entity Maint Dlg to All Entity aka ENTITY_ALONE Dlg.
//
//    Rev 1.19   Jul 27 2007 17:04:30   kovacsro
// PET 2372 FN02 AIM-FDP KYC
//
//    Rev 1.18   Nov 21 2006 16:32:42   jankovii
// PET 2287 FN01 - Grupo Mundial Trade Aggregation
//
//    Rev 1.17   Nov 20 2006 13:50:20   jankovii
// PET 2287 FN01 - Grupo Mundial Trade Aggregation.
//
//    Rev 1.16   Oct 05 2006 12:24:30   porteanm
// Incident ####### - Cannot add an Entity.
//
//    Rev 1.15   Jul 21 2006 16:38:32   jankovii
// PET 2192 FN02 - Dealings - Sender Cut Off Time.
//
//    Rev 1.14   Jan 10 2006 11:15:52   jankovii
// Incident #511921 - Wrong error message when delete the only whereuse type in an entity.
//
//    Rev 1.13   Dec 20 2005 09:22:20   jankovii
// PET1228_FN02-WhereUse Delete button is disabled for Client/Fund & Paying Agent records.
//
//    Rev 1.12   Nov 30 2005 14:17:12   jankovii
// PET1228_FN02 - small fixes.
//
//    Rev 1.11   Nov 28 2005 10:00:06   jankovii
// PET1228_FN02_ EU Savings Directive Phase Two
//
//    Rev 1.8   Oct 27 2005 10:36:32   jankovii
// PET1228_FN01-EU Savings Directive Phase
//
//    Rev 1.7   Oct 25 2005 10:12:58   jankovii
// gfdsgfd
//
//    Rev 1.6   Sep 15 2005 15:11:24   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
//
//    Rev 1.5   May 19 2005 16:01:18   yingbaol
// Incident 297032: if the status is bad, the record can not be deleted
//
//    Rev 1.4   Apr 19 2005 15:20:56   yingbaol
// Incident290524: fix crash during base class can not handle permission check properly.
//
//    Rev 1.3   Mar 16 2005 11:29:30   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
//
//    Rev 1.2   Mar 11 2005 16:03:06   yingbaol
// PET1171,FN01, EU saving: dynamically display controls on tab.
//
//    Rev 1.1   Mar 09 2005 16:08:56   yingbaol
// PET1171,FN01: EU saving, entity update
//
//    Rev 1.0   Mar 01 2005 09:58:48   yingbaol
// Initial revision.
 *
 *
 */

