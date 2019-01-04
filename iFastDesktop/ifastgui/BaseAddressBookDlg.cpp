// BaseAddressBookDlg.cpp : implementation file
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   :BaseAddressBookDlg.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : Sept. 3, 2002
//
// ^CLASS    : BaseAddressBookDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//****************************************************************************** 
#include "stdafx.h"
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include "mfdstc.h"
#include "BaseAddressBookDlg.h"
#include <ifastbp\addressprocessincludes.h>
#include <ifastbp\addressprocess.hpp>
#include <ifastbp\EntityAddressSearchProcessincludes.h>
#include <ifastbp\BrokerAddressProcessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\dstcworksession.hpp>

#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <uibase\dstedit.h>
#include <uibase\dstcfuncs.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dsttabctrl.h>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0071_vw.hpp>
#include <ifastdataimpl\dse_dstc0072_req.hpp>
#include <ifastdataimpl\dse_dstc0113_vw.hpp>
#include <ifastdataimpl\dse_dstc0214_vw.hpp>
#include <bfcbo\bfproperties.hpp>
#include <bfproc\AbstractProcess.hpp>

#include <ifastbp\nasuprocessincludes.h>
#include <uibase\DSTGridWnd.h>

#include <configmanager.hpp>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace
{  
   const I_CHAR *CLASSNAME                = I_( "BaseAddressBookDialog" );
   const I_CHAR *LV_ADDRESS_LIST          = I_( "AddressList" );
   const I_CHAR *SPACE_STRING             = I_( " " ); 
   const I_CHAR *EMPTY_STRING             = I_( "" );
   const I_CHAR *ADDRESS                  = I_("Address");
   const I_CHAR *ADDRESSCODE              = I_("AddrCode");
   const I_CHAR *ADDRESSCODEDESC          = I_("AddrCodeDesc");
   const I_CHAR *ADDRESSLINE              = I_( "AddressLine" );
   const I_CHAR *YES                      = I_( "Y" );
   const I_CHAR *NO                       = I_( "N" );

   const    int   DISPLAYCODEALL          = 0;
   const    int   DISPLAYCODESELECT       = 1;
   const I_CHAR *const STUB_MODE          = I_( "STUB_MODE" );
   const I_CHAR *const OFFLINE            = I_( "OFFLINE" );

   const _TCHAR *const SUPPRESS           = _T( "Suppress" );
   const _TCHAR *const WAIVEPAPER         = _T( "WaivePaper" );
   const _TCHAR *const CONSENT            = _T( "Consent" );
   const _TCHAR *const MAIL               = _T( "Mail" );
   const _TCHAR *const EPOST              = _T( "Epost" );

   const _TCHAR *const FAX                = _T( "Fax" );
   const _TCHAR *const CD                 = _T( "CD" );
   const _TCHAR *const EMAIL              = _T( "Email" );
   const _TCHAR *const FUNDGROUP          = _T( "FundGroup" );
   const I_CHAR *pINQUIRYONLY             = I_( "InquiryOnly" );

   const _TCHAR *const ACCOUNT_OWNER      = _T( "01" );

   const I_CHAR *const CHARACTERS         = I_("0123456789 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

   const I_CHAR* const TAB_ADDR_INFO      = I_("Address Info");
   const I_CHAR* const TAB_RETMAIL_INFO   = I_("Return Mail Info");

   const I_CHAR* const UNCLAIMED_STAGE    = I_( "S1,S2,S3,S4" );
   const I_CHAR* const SHRHLDR_LEVEL      = I_("01");
   const I_CHAR* const SHRHLDR_CATEGORY   = I_("3");
   const I_CHAR* const ALLOWED_DEFAULT_DOC   = I_( "02,13" );

}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDR_TAX_JURIS_UPDATE;
//---------------------------------------------------------------------
namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
} 
//---------------------------------------------------------------------
namespace ADDRLIT
{
   extern const BFFieldId REG_ADDR_READ_ONLY;
   const BFTextFieldId RetMailTab(190000L, I_("RetMailTab"));
}
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
   extern CLASS_IMPORT I_CHAR * const ENTITY_MAINTANENCE;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DelPerm;
   extern CLASS_IMPORT const BFTextFieldId ModPerm;
   extern CLASS_IMPORT const BFTextFieldId AddPerm;
   extern CLASS_IMPORT const BFTextFieldId LvAddressMailingCol;
   extern CLASS_IMPORT const BFTextFieldId LVAddressMailingRow;
   extern CLASS_IMPORT const BFTextFieldId LvEntityMailingHead;
   extern CLASS_IMPORT const BFTextFieldId AcctMailingOverrideHeading;
   extern CLASS_IMPORT const BFTextFieldId MailingByFundGroup;
   extern CLASS_IMPORT const BFTextFieldId OnHold;
   extern CLASS_IMPORT const BFDecimalFieldId EntityTypeSeq;
   extern CLASS_IMPORT const BFTextFieldId ContributionOnHold;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisUpdateOpt;
   extern CLASS_IMPORT const BFTextFieldId IsNewOrUpdate;
   extern CLASS_IMPORT const BFTextFieldId DskPCLookEnb;
   extern CLASS_IMPORT const BFTextFieldId VerifyStat;
   extern CLASS_IMPORT const BFTextFieldId VerifyCategory;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
   extern CLASS_IMPORT const BFTextFieldId ShareholderAddressHeadingVerifySet;
   extern CLASS_IMPORT const BFTextFieldId StmtFrequency;
   extern CLASS_IMPORT const BFTextFieldId StmtFreqList;
   extern CLASS_IMPORT const BFTextFieldId StmtFrequencyDisabled;
   extern CLASS_IMPORT const BFTextFieldId DocumentMail;
   extern CLASS_IMPORT const BFTextFieldId StmtMail;
   extern CLASS_IMPORT const BFTextFieldId DupStmtMail;
   extern CLASS_IMPORT const BFTextFieldId TaxMail;
   extern CLASS_IMPORT const BFTextFieldId ContributionMail;
   extern CLASS_IMPORT const BFTextFieldId ListDocType;
   extern CLASS_IMPORT const BFTextFieldId DocTypeMailMapping;
   extern CLASS_IMPORT const BFTextFieldId MailHouseholdID;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const DELOPN;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY_ADDRESS_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDRESS_LOOKUP_BROWSER;

BEGIN_MESSAGE_MAP(BaseAddressBookDlg, BaseMainDlg)
   //{{AFX_MSG_MAP(BaseAddressBookDlg)
   ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
   ON_BN_CLICKED(IDC_RB_SHAREHOLDER, OnRbShareHolder)
   ON_BN_CLICKED(IDC_RB_ENTITY, OnRbEntity)
   ON_BN_CLICKED(IDC_RB_DEFAULT, OnRbDefault)
   ON_BN_CLICKED(IDC_RB_OVERRIDE, OnRbOverride)
   ON_CBN_SELCHANGE(IDC_CMB_DISP_CODE, OnSelchangeCmbDispCode)
   ON_CBN_SELCHANGE(IDC_CMB_ENTITY, OnSelchangeCmbEntity)
   ON_CBN_SELCHANGE(IDC_CMB_CODE, OnSelAddressCode)
   ON_CBN_SELCHANGE(IDC_CMB_ENTITY_OUTPUT, OnSelEntityOutput)
   ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
   ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
   ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)	
   ON_BN_CLICKED(IDC_BTN_ENTITY_MAIL_ADD, OnBtnEntityMailAdd)
   ON_BN_CLICKED(IDC_BTN_ENTITY_MAIL_DELETE, OnBtnEntityMailDel)
   ON_BN_CLICKED(IDC_BTN_HISTORY, OnBtnHistoricalAddress)
   ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistoricalMailing)
   ON_BN_CLICKED(IDC_BTN_LOOKUP, OnBtnLookup)
   ON_BN_CLICKED(IDC_BTN_ENTITY_LOOKUP, OnBtnEntityLookup)
   ON_BN_CLICKED (IDC_CB_SKIP_VAL, OnChkSkipVal)
   ON_MESSAGE( UM_OPENBROKERADDRESSDLG, OpenBrokerAddressDlg )
   ON_MESSAGE(UM_OPENADDRESSSEARCHDLG, OpenAddressSearchDlg)
   ON_EN_KILLFOCUS(IDC_EDT_POST_CODE, OnKillfocusEdtPostCode)
   ON_CBN_SELCHANGE(IDC_CMB_ENTITY_DEFAULT_ADDRESS, OnSelDefaultEntityAddress)
   ON_CBN_SELCHANGE(IDC_CMB_RET_MAIL, OnSelRetMail)
   ON_NOTIFY(LVN_ITEMCHANGING, IDC_LV_ADDRESSES, OnListItemChanging)
   ON_NOTIFY(NM_CLICK, IDC_LV_ADDRESSES, OnListItemChanged)
   //}}AFX_MSG_MAP
   ON_MESSAGE(WM_VIEWITEMSELECTED, OnListViewItemChanged)
   ON_MESSAGE(UM_OPENALERTMESSAGEDLG,OnOpenAlertMessageBox)

END_MESSAGE_MAP()

//----------------------------------------------------------------------------
void BaseAddressBookDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AddressBookDlg)
   DDX_Control(pDX, IDC_CMB_ENTITY, m_EntityName);
   DDX_Control(pDX, IDC_CMB_DISP_CODE,             m_DisplayCode);
   //}}AFX_DATA_MAP

}


//************************************************************************
void BaseAddressBookDlg::OnSelAddressCode()
{
   FillMailAddressList();
}
//*************************************************************************
void BaseAddressBookDlg::OnSelEntityOutput()

{
   DSTComboBox* pCombo = static_cast<DSTComboBox* >(GetDlgItem(IDC_CMB_ENTITY_OUTPUT) );
   m_iCurOutput = pCombo->GetCurSel();
   FillMailAddressList();
}
//-------------------------------------------------------------------
// Construction/Destruction   LVAddressMailingRow
//--------------------------------------------------------------------

BaseAddressBookDlg::BaseAddressBookDlg( UINT nIDD, CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( nIDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_dstrSel_ShareholderList(NULL_STRING)
, m_dstrSel_EntityList(NULL_STRING)
, m_iCurOutput(0)
, m_bOverride(false)
, m_bShareEntity(false)
, m_strCurrentMailingPageName(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setupShareholderMailing();
}

//------------------------------------------------------------------------------------
SEVERITY BaseAddressBookDlg::doInit()
{
   getParameter( NASULIT::CREATING_ACCOUNT, m_strNASUFlag );
   getParameter( ADDRLIT::ACCOUNT_NUM, m_dstrAccountNum );
   getParameter( ADDRLIT::SHAREHOLDER_NUM, m_dstrShrNum ); 
   getParameter( ADDRLIT::ADDRESS_CODE, m_dstrAddrCode );
   getParameter( ADDRLIT::SEARCH_SHAREHOLDER, m_strSearShareholder );
   getParameter( pINQUIRYONLY, _InquiryOnly );

   DString dstrSalutationEdit;
   getParent()->getField( this, ADDRLIT::SALUTATION_EDIT, dstrSalutationEdit );
   m_bSalutationFreeFormat = (dstrSalutationEdit == I_("Y"));

   // This parameter will be used to disable the Shareholder radio button if Entity
   // is not linked to any Account
   getParameter( ADDRLIT::FROM_ENTITY, m_dstrFromEntity);
   getParameter( ADDRLIT::ENTITY_ID,   m_dstrEntityId);
   getParameter( ADDRLIT::ENTITY_TYPE, m_dstrEntityType );
   getParameter( ADDRLIT::SEQ_NUMBER,  m_dstrSeqNum );
   getParameter( I_("ENTITY_ALONE") ,  m_dstrFromEntityAlone );

   return NO_CONDITION;
}

//****************************************************************************************
void BaseAddressBookDlg::addControls()
{
   TRACE_METHOD( CLASSNAME, I_("addControls"));	

   AddControl( CTRL_EDIT, 
               IDC_TXT_ROLE, 
               IFASTBP_PROC::ENTITY_LIST, 
               ifds::EntityType, 
               CTRLFLAG_NOT_UPDATABLE, 
               0 );

   AddListControl( CLASSNAME, IDC_LV_ADDRESSES,0,true );

   AddControl( CTRL_COMBO, IDC_CMB_CODE, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_WITH_BLANK, IDC_LV_ADDRESSES );

   GetDlgItem( IDC_CMB_SALUTATION )->ShowWindow( m_bSalutationFreeFormat ? SW_HIDE : SW_SHOW );
   GetDlgItem( IDC_EDT_SALUTATION )->ShowWindow( m_bSalutationFreeFormat ? SW_SHOW : SW_HIDE );
   if( m_bSalutationFreeFormat )
   {
      AddControl( CTRL_EDIT, IDC_EDT_SALUTATION, IFASTBP_PROC::ADDRESSES_LIST, ifds::Salutation, 0, (UINT) IDC_LV_ADDRESSES );
   }
   else 
   {
      AddControl( CTRL_COMBO, IDC_CMB_SALUTATION, IFASTBP_PROC::ADDRESSES_LIST, 
      ifds::Salutation, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_WITH_BLANK, IDC_LV_ADDRESSES );
   }

   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE, IFASTBP_PROC::ADDRESSES_LIST, 
      ifds::EffectiveDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_ADDRESSES );

   AddControl( CTRL_DATE, IDC_DTP_STOP_DATE, IFASTBP_PROC::ADDRESSES_LIST, 
      ifds::StopDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_ADDRESSES );

   AddControl( CTRL_EDIT, IDC_EDT_NAME, IFASTBP_PROC::ADDRESSES_LIST, 
      ifds::Name12, CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_LV_ADDRESSES );

   AddControl( CTRL_EDIT, IDC_SHAREHOLDER_REG, IFASTBP_PROC::SHAREHOLDER_LIST, 
      ifds::Name2, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_ADDRESSES );

   AddControl( CTRL_EDIT, IDC_EDT_POST_CODE, IFASTBP_PROC::ADDRESSES_LIST, 
      ifds::PostalCode, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_ADDRESSES );

   AddControl( CTRL_EDIT, IDC_EDT_REG_ADDR_CODE, IFASTBP_PROC::ADDRESSES_LIST, 
      ifds::RegAddrCode, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_ADDRESSES );

   BFFieldId subField = getAddressSubId();

   AddControl( CTRL_EDIT, IDC_SHAREHOLDER_ADDRESS, IFASTBP_PROC::ADDRESSES_LIST, 
      subField,CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_LV_ADDRESSES );

   DSTEdit* pEditAddr =dynamic_cast<DSTEdit* >(GetControl(IDC_SHAREHOLDER_ADDRESS) );
   pEditAddr ->SetMaxCharNum( 40 );

   if ( !m_dstrAccountNum.empty() ) 
   {
      AddGrid( CLASSNAME, 
               IDC_LV_MAIL_ASSIGN, 
               I_("AddressMailing"),
               IFASTBP_PROC::ACCOUNT_MAILING_LIST, 
               0, 
               ifds::LvAddressMailingCol,
               ifds::LVAddressMailingRow,
               DSTGridWnd::GRID_TYPE::ATTRIBUTE );

      //setOverrideFlag(true);
     AddGrid( CLASSNAME, 
              IDC_LV_ACCT_MAILING_OVERRIDE, 
              I_("AcctMailingOverride"),
              IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST, 
              0, 
              ifds::AcctMailingOverrideHeading,
              ifds::NullFieldId,
              DSTGridWnd::GRID_TYPE::LIST);
      //setOverrideFlag(false);
   }
   
   /***************************************************************
   if( isDemoMode() )
   {
      GetControl( IDC_EDT_ENTITY_ADDRESS_CODE ) ->Enable( false );
      GetControl( IDC_CMB_ENTITY_HOLD_MAIL )    ->Enable( false );
      GetControl( IDC_CMB_ENTITY_COUNTRY )      ->Enable( false );
   }
   *****************************************************************/


   AddControl( CTRL_DATE, 
               IDC_DTP_ENTITY_ADDRESS_EFFECTIVE, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::EffectiveDate, 
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               IDC_LV_ADDRESSES );

   AddControl( CTRL_EDIT, 
               IDC_EDT_ENTITY_ADDRESS_CODE, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::AddrCode, 
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               (UINT) IDC_LV_ADDRESSES );

   DSTEdit *pEditEntityAddressCode = dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ENTITY_ADDRESS_CODE ));
   if ( NULL != pEditEntityAddressCode )
   {
      pEditEntityAddressCode->SetMaxCharNum( 2 );	  
   }
 
   AddControl( CTRL_EDIT, 
               IDC_ENTITY_ADDRESS, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::EntityAddress,
               CTRLFLAG_FIELDS_FROM_SUB_LIST /*| CTRLFLAG_NOT_UPDATABLE*/, 
               IDC_LV_ADDRESSES );

   AddControl( CTRL_EDIT, 
               IDC_EDT_CITY, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::City, 
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               IDC_LV_ADDRESSES );
   DSTEdit *pEditEntityAddressCity = dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_CITY ));
   if ( NULL != pEditEntityAddressCity )
   {
      pEditEntityAddressCity->SetMaxCharNum( 30 );	  
   }

   AddControl( CTRL_EDIT, 
               IDC_EDT_ENTITY_ADDRESS_ID, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::AddrId, 
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               IDC_LV_ADDRESSES );
   DSTEdit *pEditEntityAddressId = dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ENTITY_ADDRESS_ID ));
   if ( NULL != pEditEntityAddressId )
   {
      pEditEntityAddressId->SetMaxCharNum( 10 );	
      pEditEntityAddressId->SetAllDigits( true );
   }

   AddControl( CTRL_COMBO, 
               IDC_CMB_ENTITY_HOLD_MAIL, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::HoldMail, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST/*CTRLFLAG_NOT_UPDATABLE*/, 
               IDC_LV_ADDRESSES );
   
   AddControl( CTRL_EDIT, 
               IDC_EDT_ENTITY_POST, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::PostalCode, 
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               IDC_LV_ADDRESSES );
   DSTEdit *pEditEntityAddressPostalCode = dynamic_cast<DSTEdit *>(GetControl( IDC_EDT_ENTITY_POST ) );
   if ( NULL != pEditEntityAddressPostalCode )
   {
      pEditEntityAddressPostalCode->SetMaxCharNum( 9 );	  
   }

   AddControl( CTRL_COMBO, 
               IDC_CMB_ENTITY_COUNTRY, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::Country, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST/*CTRLFLAG_NOT_UPDATABLE*/, 
               IDC_LV_ADDRESSES );

   AddControl( CTRL_COMBO, 
               IDC_CMB_PROVINCE, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::Province, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               IDC_LV_ADDRESSES );
   
   AddControl( CTRL_EDIT, 
               IDC_EDT_ENTITY_PROVINCE, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::Province, 
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               IDC_LV_ADDRESSES );	
   DSTEdit *pEditEntityAddressProvince = dynamic_cast<DSTEdit *>(GetControl( IDC_EDT_ENTITY_PROVINCE ) );
   if ( NULL != pEditEntityAddressProvince )
   {
      pEditEntityAddressProvince->SetMaxCharNum( 2 );	  
   }

   AddControl( CTRL_EDIT, 
               IDC_EDT_ENTITY_ADDR_NAME, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
               ifds::AddrDesc, 
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               IDC_LV_ADDRESSES );	
   DSTEdit *pEditAddressDesc = dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ENTITY_ADDR_NAME ));
   if ( NULL != pEditAddressDesc )
   {
      pEditAddressDesc->SetMaxCharNum( 30 );	  
   }


   AddControl( CTRL_COMBO, 
               IDC_CMB_ENTITY_OUTPUT, 
               BF::NullContainerId, 
               ifds::NullFieldId, 
               CTRLFLAG_MANUAL_INIT | CTRLFLAG_GUI_FIELD, 
               IDC_LV_ADDRESSES );

   AddControl( CTRL_COMBO, 
               IDC_CMB_ENTITY_DEFAULT_ADDRESS, 
               IFASTBP_PROC::ENTITY_LIST, 
               ifds::AddrCode, 
               CTRLFLAG_MANUAL_INIT/*CTRLFLAG_NOT_UPDATABLE*/, 
               0 );
   AddControl( CTRL_COMBO, 
               IDC_CMB_VERIFY_STAT, 
               IFASTBP_PROC::ADDRESSES_LIST, 
               ifds::VerifyStat, 
               CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
               IDC_LV_ADDRESSES );
   AddControl(CTRL_STATIC, IDC_STATIC_VERIFY);

   if( m_strNASUFlag != YES && m_dstrFromEntityAlone != YES)
   {
      AddGrid( CLASSNAME, 
               IDC_LV_ENTITY_MAILING, 
               I_("EntityMailing"),
               IFASTBP_PROC::ENTITY_MAILING_LIST, 
               0, 
               ifds::AcctMailingOverrideHeading,
               ifds::NullFieldId,
               DSTGridWnd::GRID_TYPE::LIST);
   }

   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_ENTITY_POST ) )->SetAllowedChars( CHARACTERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_POST_CODE ) )->SetAllowedChars( CHARACTERS );
   
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA ) 
   {
      AddControl( CTRL_COMBO, 
                  IDC_CMB_UNCLAIM_REASON_CODE,
                  IFASTBP_PROC::ADDRESSES_LIST,
                  ifds::RetMailReasonCode,
                  CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES);
      
      AddControl( CTRL_COMBO, 
                  IDC_CMB_ENTITY_UNCLAIM_REASON_CODE,
                  IFASTBP_PROC::ENTITY_ADDRESS_LIST,
                  ifds::RetMailReasonCode,
                  CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES);

      AddControl( CTRL_COMBO, 
                  IDC_CMB_UNCLAIM_STAGE,
                  IFASTBP_PROC::ADDRESSES_LIST,
                  ifds::UnclmRetMailStage,
                  CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES);

      AddControl( CTRL_DATE, 
                  IDC_DTP_UNCLAIM_GOVT_STMT_DATE,
                  IFASTBP_PROC::ADDRESSES_LIST,
                  ifds::UnclmStmtDate,
                  CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES);

      AddControl( CTRL_DATE, 
                  IDC_DTP_UNCLAIM_REMITTANCE_DATE,
                  IFASTBP_PROC::ADDRESSES_LIST,
                  ifds::UnclmRemitDate,
                  CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES);

      AddControl( CTRL_EDIT, 
                  IDC_EDT_UNCLAIM_COMMENT,
                  IFASTBP_PROC::ADDRESSES_LIST,
                  ifds::UnclmComment,
                  CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES);

      AddControl( CTRL_EDIT, 
                  IDC_EDT_ENTITY_UNCLAIM_COMMENT,
                  IFASTBP_PROC::ENTITY_ADDRESS_LIST,
                  ifds::UnclmComment,
                  CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES);


      DSTEdit *pEditUnclaimedComment = dynamic_cast<DSTEdit *>(GetControl (IDC_EDT_UNCLAIM_COMMENT));
      
      if ( NULL != pEditUnclaimedComment )
      {
         pEditUnclaimedComment->SetMaxCharNum( 100 );
      }

      DString dstrAddrFormat;
      DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );


      AddControl( CTRL_DATE, 
                  IDC_DTP_UNCLAIM_STAMP_DATE,
                  IFASTBP_PROC::ADDRESSES_LIST,
                  ifds::StageStampDate,
                  CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES);

      AddControl( CTRL_COMBO, 
                  IDC_CMB_UNCLAIM_STAGE_ASSIGN,
                  IFASTBP_PROC::ADDRESSES_LIST,
                  ifds::StageAssignBy,
                  CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                  IDC_LV_ADDRESSES);

      AddControl(CTRL_STATIC, 
         IDC_STC_UNCLAIM_REASON_CODE);

      AddControl(CTRL_STATIC, 
         IDC_STC_UNCLAIM_STAGE);

      AddControl(CTRL_STATIC, 
         IDC_STC_UNCLAIM_GOVT_STMT_DATE);

      AddControl(CTRL_STATIC, 
         IDC_STC_UNCLAIM_REMITTANCE_DATE);

      AddControl(CTRL_STATIC, 
         IDC_STC_UNCLAIM_COMMENT);

      AddControl(CTRL_STATIC, 
         IDC_STC_UNCLAIM_STAMP_DATE);

      AddControl(CTRL_STATIC, 
         IDC_STC_UNCLAIM_STAGE_ASSIGN);

      AddControl(CTRL_STATIC, 
         IDC_STC_ENTITY_UNCLAIM_REASON_CODE);

      AddControl(CTRL_STATIC, 
         IDC_STC_ENTITY_UNCLAIM_COMMENT);

      m_pMailInfoTabCtrl = AddTabControl (CLASSNAME, IDC_TAB_MAILING_INFO, I_("MailingInfo"));

      m_pMailInfoTabCtrl->AddTab(TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->AddTab(TAB_RETMAIL_INFO);

      m_pMailInfoTabCtrl->registerControl(IDC_CMB_UNCLAIM_REASON_CODE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_CMB_UNCLAIM_STAGE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_DTP_UNCLAIM_GOVT_STMT_DATE, TAB_RETMAIL_INFO);
      //m_pMailInfoTabCtrl->registerControl(IDC_DTP_UNCLAIM_REMITTANCE_DATE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_EDT_UNCLAIM_COMMENT, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_DTP_UNCLAIM_STAMP_DATE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_CMB_UNCLAIM_STAGE_ASSIGN, TAB_RETMAIL_INFO);

      m_pMailInfoTabCtrl->registerControl(IDC_STC_UNCLAIM_REASON_CODE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STC_UNCLAIM_STAGE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STC_UNCLAIM_GOVT_STMT_DATE, TAB_RETMAIL_INFO);
      //m_pMailInfoTabCtrl->registerControl(IDC_STC_UNCLAIM_REMITTANCE_DATE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STC_UNCLAIM_COMMENT, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STC_UNCLAIM_STAMP_DATE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STC_UNCLAIM_STAGE_ASSIGN, TAB_RETMAIL_INFO);
	  // Entity Return Mail fields
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_ENTITY_RET_MAIL, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_CMB_ENTITY_RET_MAIL, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_ENTITY_RET_DATE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_DTP_ENTITY_RET_DATE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STC_ENTITY_UNCLAIM_REASON_CODE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_CMB_ENTITY_UNCLAIM_REASON_CODE, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STC_ENTITY_UNCLAIM_COMMENT, TAB_RETMAIL_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_EDT_ENTITY_UNCLAIM_COMMENT, TAB_RETMAIL_INFO);

      AddControl(CTRL_STATIC, IDC_STATIC_SHAREHOLDER_ADDTL);
      AddControl(CTRL_STATIC, IDC_STATIC__SHAREHOLDER_CODE);
      AddControl(CTRL_STATIC, IDC_STATIC_SALUTATION);
      AddControl(CTRL_STATIC, IDC_STATIC_SHAREHOLDER_NAME);
      AddControl(CTRL_STATIC, IDC_STATIC_EFFECTIVE);
      AddControl(CTRL_STATIC, IDC_STATIC_STOP);
      AddControl(CTRL_STATIC, IDC_STATIC_SHAREHOLDER_ADDRESS);
      AddControl(CTRL_STATIC, IDC_TXT_REG_ADDR_CODE);
      //AddControl(CTRL_STATIC, IDC_STATIC_SHR_POST);

      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_SHAREHOLDER_ADDTL, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC__SHAREHOLDER_CODE, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_SALUTATION, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_SHAREHOLDER_NAME, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_EFFECTIVE, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_STOP, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_SHAREHOLDER_ADDRESS, TAB_ADDR_INFO);

      m_pMailInfoTabCtrl->registerControl(IDC_SHAREHOLDER_REG, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_CMB_CODE, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl( m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION, TAB_ADDR_INFO);

      m_pMailInfoTabCtrl->registerControl(IDC_EDT_NAME, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_DTP_EFF_DATE, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_DTP_STOP_DATE, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_SHAREHOLDER_ADDRESS, TAB_ADDR_INFO);

      m_pMailInfoTabCtrl->registerControl(IDC_EDT_REG_ADDR_CODE, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_TXT_REG_ADDR_CODE, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_CMB_VERIFY_STAT, TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->registerControl(IDC_STATIC_VERIFY, TAB_ADDR_INFO);
      //m_pMailInfoTabCtrl->registerControl(IDC_STATIC_SHR_POST, TAB_ADDR_INFO);
      //m_pMailInfoTabCtrl->registerControl(IDC_EDT_POST_CODE, TAB_ADDR_INFO);
      //HideReturnMail();
      
      GetDlgItem (IDC_STC_UNCLAIM_REMITTANCE_DATE)->ShowWindow (false);
      GetDlgItem (IDC_DTP_UNCLAIM_REMITTANCE_DATE)->ShowWindow (false);
   }

   CWnd* pEntityCodeWnd = GetDlgItem(IDC_ENTITY_ADDRESS);
   if (NULL != pEntityCodeWnd)
   {
       if (DSTEdit* pDSTEditEntityCode = dynamic_cast<DSTEdit*>(pEntityCodeWnd))
       {
           pDSTEditEntityCode->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pPostCodeWnd = GetDlgItem(IDC_EDT_POST_CODE);
   if (NULL != pPostCodeWnd)
   {
       if (DSTEdit* pDSTEditPostCode = dynamic_cast<DSTEdit*>(pPostCodeWnd))
       {
           pDSTEditPostCode->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pShareholderAddressWnd = GetDlgItem(IDC_SHAREHOLDER_ADDRESS);
   if (NULL != pShareholderAddressWnd)
   {
       if (DSTEdit* pDSTEditShareholderAddress = dynamic_cast<DSTEdit*>(pShareholderAddressWnd))
       {
           pDSTEditShareholderAddress->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pEntityPostWnd = GetDlgItem(IDC_EDT_ENTITY_POST);
   if (NULL != pEntityPostWnd)
   {
       if (DSTEdit* pDSTEditEntityPost = dynamic_cast<DSTEdit*>(pEntityPostWnd))
       {
           pDSTEditEntityPost->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }
}

//------------------------------------------------------------------------------------
void BaseAddressBookDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog"));

   if (_InquiryOnly.strip() == YES)
      SetUserAccesFunctionCode(NULL);
   else
      SetUserAccesFunctionCode(UAF::ADDRESS_BOOK);

   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_ADDRESSES);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_ADDRESSES);

   if ( m_dstrFromEntity == I_( "Y" ) )
      setShareholoderFlag(false);
   else
      setShareholoderFlag(true);

   setOverrideFlag(false);
   int col=0;
   findAddrCode();
   addControls();
   FillDisplayCodeComboBox();
   if ( m_strSearShareholder == NULL_STRING )
      FillEntityCombo();
   setDlgTitle();

   DString str;
   getParent()->getField( this, BF::NullContainerId, ifds::MailingByFundGroup, str,false );
   GetDlgItem(IDC_RB_OVERRIDE)->EnableWindow(str.strip().upperCase() == YES );

   if ( m_strNASUFlag == I_("Y") || m_strSearShareholder == I_("Y") )
   {
      GetDlgItem( IDC_RB_ENTITY     )->EnableWindow(false);
      GetDlgItem( IDC_BTN_ADM_DATES )->EnableWindow(false);

   }
   // incident  322642
   // don't create a new account mailing info if it is already exist
   if( !m_dstrAccountNum.empty() &&
      !MailingPositionByAccount(m_dstrAccountNum) )
   {
         if( m_strNASUFlag == I_("Y") )
         {
            getParent()->getKeyForNewListItem( this, IFASTBP_PROC::ACCOUNT_MAILING_LIST  );
         }
    }
    if(  m_strNASUFlag == I_("Y") )
    {
       DString dstrCreat;
       getParent()->getField(this,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST,
                                  ADDRLIT::CREATE_MAIL_OVERRIDE,dstrCreat,false);
       if( dstrCreat == YES )
       {
         getParent()->setField(this,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST,
                                  ADDRLIT::CREATE_MAIL_OVERRIDE,dstrCreat );
       }
   }

   HideReturnMail();

   if ( IsShareholder() )
   {
      ShowShareHolder(true);
      if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      {
         DString dstrRetMailTab;
         getParent()->getField(this,BF::NullContainerId, ADDRLIT::RetMailTab,dstrRetMailTab,false);

         if(dstrRetMailTab == I_("Y"))
         {
            m_pMailInfoTabCtrl->SelectTab( TAB_RETMAIL_INFO);
            m_pMailInfoTabCtrl->Load(TAB_RETMAIL_INFO);
         }
         else
         {
            m_pMailInfoTabCtrl->SelectTab( TAB_ADDR_INFO );
            m_pMailInfoTabCtrl->Load(TAB_ADDR_INFO);
         }
      }
   }
   else
      ShowEntity();
   //HideReturnMail();

   postOpenAlertBox();
}

//-------------------------------------------------------------------------------------
void BaseAddressBookDlg::OnRbShareHolder()
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbShareHolder" ));
   setShareholoderFlag(  true );
   DString key = getParent()->getFirstListItemKey(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST);
   if( key != NULL_STRING )
   {
      m_dstrSel_EntityList = getParent()->getCurrentListItemKey(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST);
   }
   ShowShareHolder(true);	
}

//--------------------------------------------------------------------------------------
void BaseAddressBookDlg::OnRbEntity()
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbEntity" ));
   setShareholoderFlag( false );
   m_dstrSel_ShareholderList = getParent()->getCurrentListItemKey(this,IFASTBP_PROC::ADDRESSES_LIST);
   ClearMailingList();

   ShowEntity(); 
}

//--------------------------------------------------------------------------------------
void BaseAddressBookDlg::OnRbDefault()
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbDefault" ));
   GetDlgItem (IDC_LV_MAIL_ASSIGN)->ShowWindow ( SW_SHOW );
   GetDlgItem (IDC_LV_ACCT_MAILING_OVERRIDE)->ShowWindow( SW_HIDE );
   GetDlgItem (IDC_BTN_ENTITY_MAIL_ADD)->ShowWindow( SW_HIDE );
   GetDlgItem (IDC_BTN_ENTITY_MAIL_DELETE)->ShowWindow( SW_HIDE );
   setOverrideFlag( false );
   if(MailingPositionByAccount(m_dstrAccountNum))
   {
      getComboStringForAddressCode( m_dstrAddrCodeList);
      m_dstrOverrideAddrCodeList = m_dstrAddrCodeList;
      DSTGridWnd *pGrid = GetGrid( IDC_LV_MAIL_ASSIGN );
      pGrid->reLoadGrid();
      bool bNewitem = true;
      const DString key   = getParent()->getFirstListItemKey(this,IFASTBP_PROC::ACCOUNT_MAILING_LIST  );
      if( key != NULL_STRING )
      {
         bNewitem = dynamic_cast<AbstractProcess* >( getParent() )->isCurrentListItemNew( this, 
                                 IFASTBP_PROC::ACCOUNT_MAILING_LIST  );
      }
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( !bNewitem );         
   }
}

//--------------------------------------------------------------------------------------
void BaseAddressBookDlg::OnRbOverride()
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbOverride" ));
   setOverrideFlag( true );
   getComboStringForAddressCode( m_dstrAddrCodeList);
   m_dstrOverrideAddrCodeList = m_dstrAddrCodeList;

   ShowAcctMailingOverride(true);
   DSTGridWnd *pGrid = GetGrid( IDC_LV_ACCT_MAILING_OVERRIDE );
   pGrid->reLoadGrid();
   bool bNewitem = true;
   const DString key   = getParent()->getFirstListItemKey(this,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST  );
   if( key != NULL_STRING )
   {
       bNewitem = dynamic_cast<AbstractProcess* >(getParent() )->isCurrentListItemNew( this, 
                              IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST  );
   }  
   GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( !bNewitem );         
}

//--------------------------------------------------------------------------------------
void BaseAddressBookDlg::findAddrCode()
{
   if ( !m_dstrAccountNum.empty() && !m_dstrShrNum.empty() )
   {
      const DString *_pOldKey = &getParent()->getCurrentListItemKey(this, IFASTBP_PROC::ADDRESSES_LIST);
      const DString *key = &getParent()->getFirstListItemKey( this, IFASTBP_PROC::ADDRESSES_LIST );
      if ( *key == NULL_STRING )
         return;
      DString str;
      do
      {
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, str,false );
         str.strip();
         if ( str == m_dstrAddrCode )
         {

            m_dstrSel_ShareholderList = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::ADDRESSES_LIST);
            break;
         }
      } while ( getParent()->getNextListItemKey( this, IFASTBP_PROC::ADDRESSES_LIST ) != EMPTY_STRING );
      getParent()->setCurrentListItem(this,IFASTBP_PROC::ADDRESSES_LIST,*_pOldKey);
   }

}

//------------------------------------------------------------------------------------
bool BaseAddressBookDlg::IsShareholder() const
{
   return m_bShareEntity == true; 
}

//------------------------------------------------------------------------------------
void BaseAddressBookDlg::setShareholoderFlag( bool bFlag )
{
   m_bShareEntity = bFlag;
}

//------------------------------------------------------------------------------------
bool BaseAddressBookDlg::IsOverride() const
{
   return m_bOverride == true; 
}

//------------------------------------------------------------------------------------
void BaseAddressBookDlg::setOverrideFlag( bool bFlag )
{
   m_bOverride = bFlag;
}

//******************************************************************************************
void BaseAddressBookDlg::DisplayAddressLvList()
{
   TRACE_METHOD( CLASSNAME, I_("DisplayAddressLvList"));
   if ( IsShareholder() )
   {
      DString dstrRetMailTab,
              dstrAcctDesignation;
      getParent()->getField(this,BF::NullContainerId, ADDRLIT::RetMailTab,dstrRetMailTab,false);
      getParent()->getField(this,BF::NullContainerId, ifds::AcctDesignation, dstrAcctDesignation, false );

      dstrAcctDesignation.stripAll();
      if( dstrRetMailTab == I_("Y") && 
         ( dstrAcctDesignation == I_( "2" ) || dstrAcctDesignation == I_("3") ) )
      {
         SelAddrOfRetMailForNomineeIntermAcct();
      }
      LoadShareHolderAddress();

      DSTCWorkSession *pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
      bool bVerificationEnabled = false;
      pWorkSession->isVerificationEnabled ( idDataGroup, 
                                            SHRHLDR_CATEGORY, 
                                            SHRHLDR_LEVEL, 
                                            bVerificationEnabled);

      ReInitListControl( IDC_LV_ADDRESSES, 
                         ifds::ShareholderAddressHeadingVerifySet, 
                         IFASTBP_PROC::ADDRESSES_LIST, 
                         I_("ShareholderAddress") );

      DSTListCtrl *rpList = GetList( IDC_LV_ADDRESSES );
      rpList->setAutoAddFlag(false);
      ReInitControl(IDC_CMB_CODE,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrCode);
      setLoadMailing( true );

      if( m_dstrSel_ShareholderList != NULL_STRING)
         LoadListControl(IDC_LV_ADDRESSES, &m_dstrSel_ShareholderList);
      else
         LoadListControl(IDC_LV_ADDRESSES);

      setLoadMailing( false );
   }
   else
   {
      LoadEntityAddress();
      ReInitListControl( IDC_LV_ADDRESSES, ifds::EntityAddressHeadingSet, 
         IFASTBP_PROC::ENTITY_ADDRESS_LIST, I_("EntityAddress") );
      DSTListCtrl *rpList = GetList( IDC_LV_ADDRESSES );
      //rpList->setAutoAddFlag(true);

      GetDlgItem(IDC_EDT_ENTITY_ADDRESS_CODE)->SetWindowText(_T(""));
      GetDlgItem(IDC_EDT_ENTITY_ADDRESS_ID)->SetWindowText(_T(""));
      GetDlgItem(IDC_ENTITY_ADDRESS)->SetWindowText(_T(""));
      GetDlgItem(IDC_EDT_ENTITY_POST)->SetWindowText(_T(""));
      ReInitControl(IDC_EDT_ENTITY_ADDRESS_CODE,IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrCode);		

      setLoadMailing( true );

      if (m_dstrSel_EntityList != NULL_STRING)
         LoadListControl(IDC_LV_ADDRESSES, &m_dstrSel_EntityList);
      else
         LoadListControl(IDC_LV_ADDRESSES);

      setLoadMailing( false );   

   }
}

//-------------------------------------------------------------------------------------
void BaseAddressBookDlg::LoadShareHolderAddress()
{
   ConnectControl( IDC_CMB_CODE,            true );
   
   ConnectControl( m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION, true );
   ConnectControl(IDC_EDT_NAME,            true );	
   ConnectControl(IDC_SHAREHOLDER_REG,     true );
   ConnectControl(IDC_DTP_EFF_DATE,        true );
   ConnectControl(IDC_DTP_STOP_DATE,       true );
   ConnectControl(IDC_EDT_REG_ADDR_CODE,   true );
   ConnectControl(IDC_SHAREHOLDER_ADDRESS, true );	
   ConnectControl(IDC_EDT_POST_CODE,       true );
   ConnectControl(IDC_CMB_VERIFY_STAT,	   true );
   DString dstrAddrFormat;
   DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );

   ///ConnectControl(IDC_CMB_SHR_COUNTRY,     true );  
    
   // Disconnect all Entity Address related controls
   ConnectControl( IDC_DTP_ENTITY_ADDRESS_EFFECTIVE, false );
   ConnectControl( IDC_EDT_ENTITY_ADDRESS_CODE,      false );
   ConnectControl( IDC_ENTITY_ADDRESS,               false );
   ConnectControl( IDC_EDT_CITY,                     false );
   ConnectControl( IDC_EDT_ENTITY_ADDRESS_ID,        false );
   ConnectControl( IDC_CMB_ENTITY_HOLD_MAIL,         false );
   ConnectControl( IDC_EDT_ENTITY_POST,              false );
   ConnectControl( IDC_CMB_ENTITY_COUNTRY,           false );
   ConnectControl( IDC_CMB_PROVINCE,                 false );
   ConnectControl( IDC_EDT_ENTITY_PROVINCE,          false );
   ConnectControl( IDC_EDT_ENTITY_ADDR_NAME,         false );
   
   if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA){
      ConnectControl( IDC_CMB_UNCLAIM_REASON_CODE,       true);
      ConnectControl( IDC_CMB_UNCLAIM_STAGE,             true);
      ConnectControl( IDC_DTP_UNCLAIM_GOVT_STMT_DATE,    true);
      //ConnectControl( IDC_DTP_UNCLAIM_REMITTANCE_DATE,   true);
      ConnectControl( IDC_EDT_UNCLAIM_COMMENT,           true);
      ConnectControl( IDC_DTP_UNCLAIM_STAMP_DATE,        true);
      ConnectControl( IDC_CMB_UNCLAIM_STAGE_ASSIGN,      true);
      ConnectControl( IDC_CMB_RET_MAIL,                  true);
      ConnectControl( IDC_DTP_RET_DATE ,                 true); 
      // Entity Return Mail fields
      ConnectControl( IDC_CMB_ENTITY_RET_MAIL,            false );
      ConnectControl( IDC_DTP_ENTITY_RET_DATE,            false );
      ConnectControl( IDC_CMB_ENTITY_UNCLAIM_REASON_CODE, false );
      ConnectControl( IDC_EDT_ENTITY_UNCLAIM_COMMENT,     false );
   }
}

//---------------------------------------------------------------------------------------
void BaseAddressBookDlg::LoadEntityAddress()
{
   ConnectControl(IDC_TXT_ROLE,            true );
   ConnectControlToData(IDC_TXT_ROLE,      true );

   ConnectControl(IDC_CMB_CODE,            false );
   ConnectControl(IDC_CMB_VERIFY_STAT,     false );
   ConnectControl( m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION, false );   
   ConnectControl(IDC_EDT_NAME,            false );	
   ConnectControl(IDC_SHAREHOLDER_REG,     false );
   ConnectControl(IDC_DTP_EFF_DATE,        false );
   ConnectControl(IDC_DTP_STOP_DATE,       false );
   ConnectControl(IDC_EDT_REG_ADDR_CODE,   false );
   ConnectControl(IDC_SHAREHOLDER_ADDRESS, false );	
   ConnectControl(IDC_EDT_POST_CODE,       false );

   DString dstrAddrFormat;
   DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );

   //ConnectControl(IDC_CMB_SHR_COUNTRY,     false );  

   // Connect all Entity Address related controls
   ConnectControl(IDC_DTP_ENTITY_ADDRESS_EFFECTIVE, true );
   ConnectControl(IDC_EDT_ENTITY_ADDRESS_CODE,      true );
   ConnectControl(IDC_ENTITY_ADDRESS,               true );
   ConnectControl(IDC_EDT_CITY,                     true );
   ConnectControl(IDC_EDT_ENTITY_ADDRESS_ID,        true );
   
   if ( !m_dstrAccountNum.empty() && !isAccountOwner() )
      ConnectControl(IDC_CMB_ENTITY_HOLD_MAIL,    true );
   ConnectControl(IDC_EDT_ENTITY_POST,              true );
   ConnectControl(IDC_CMB_ENTITY_COUNTRY,           true );
   ConnectControl(IDC_CMB_PROVINCE,                 true );
   ConnectControl(IDC_EDT_ENTITY_ADDR_NAME,         true );
   
   if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA){
      ConnectControl( IDC_CMB_UNCLAIM_REASON_CODE,       false);
      ConnectControl( IDC_CMB_UNCLAIM_STAGE,             false);
      ConnectControl( IDC_DTP_UNCLAIM_GOVT_STMT_DATE,    false);
      //ConnectControl( IDC_DTP_UNCLAIM_REMITTANCE_DATE,   false);
      ConnectControl( IDC_EDT_UNCLAIM_COMMENT,           false);
      ConnectControl( IDC_DTP_UNCLAIM_STAMP_DATE,        false);
      ConnectControl( IDC_CMB_UNCLAIM_STAGE_ASSIGN,      false);
      ConnectControl( IDC_CMB_RET_MAIL,                  false);
      ConnectControl( IDC_DTP_RET_DATE ,                 false);
      // Entity Return Mail Fields
      ConnectControl( IDC_CMB_ENTITY_RET_MAIL,            true );
      ConnectControl( IDC_DTP_ENTITY_RET_DATE,            true );
      ConnectControl( IDC_CMB_ENTITY_UNCLAIM_REASON_CODE, true );
      ConnectControl( IDC_EDT_ENTITY_UNCLAIM_COMMENT,     true ); 
   }

}

//***************************************************************************************
void BaseAddressBookDlg::InitCombo(UINT controlID,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& fieldId,bool bCode )
{
   DSTComboBox *cb;
   cb = static_cast<DSTComboBox* >(GetDlgItem( controlID ) );
   cb->ResetContent();
   if(!bCode ){
      CString cstrAll;   //for out put
      cstrAll.LoadString( TXT_ALL );
      cb->AddString(cstrAll);

   }
   CStringList temp;
   DString str,strDes;
   int iIndex;
   const DString *pCurKey = &( getParent()->getCurrentListItemKey(this, idContainer ) );
   const DString *pKey=&(getParent()->getFirstListItemKey( this, idContainer ));
   if ( *pKey != NULL_STRING )
   {
      do
      {
         getParent()->getField( this, idContainer, fieldId, str,false );
         getParent()->getField( this, idContainer, fieldId, strDes,true );
         str.strip(); strDes.strip();
         DString ComboStr;
         if(bCode)ComboStr = str;
         else ComboStr = strDes;

         if (temp.Find( ComboStr.c_str() ) == NULL )
         {
            temp.AddTail(ComboStr.c_str());
            iIndex = cb->AddString(ComboStr.c_str());
         }
      }while ( *( pKey = &( getParent()->getNextListItemKey( this, idContainer ))) != NULL_STRING);
   }

   if ( *pCurKey != NULL_STRING )
      getParent()->setCurrentListItem(this, idContainer, *pCurKey);
}

//**************************************************************************************
void BaseAddressBookDlg::InitControl(UINT controlID )
{
   switch (controlID) 
   {	
      case IDC_CMB_ENTITY_DEFAULT_ADDRESS:
      {
         InitCombo(IDC_CMB_ENTITY_DEFAULT_ADDRESS,IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrCode);			 
         break;
      }
      case IDC_CMB_ENTITY_OUTPUT:
      {
         if( !m_dstrAccountNum.empty() && !isAccountOwner() )
         {
            InitCombo(IDC_CMB_ENTITY_OUTPUT,IFASTBP_PROC::ENTITY_MAILING_LIST,
               ifds::DocumentType,false);
            DSTComboBox* pCombo = static_cast<DSTComboBox* >(GetDlgItem(IDC_CMB_ENTITY_OUTPUT) );
            pCombo->SetCurSel(m_iCurOutput);
         }
         break;
      }
      default:
         break;
   }
}

//---------------------------------------------------------------------------------------
BOOL BaseAddressBookDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();
   return TRUE;
}

//----------------------------------------------------------------------------------
void BaseAddressBookDlg::setDlgTitle(bool bNameFlag,bool entityFlag)
{
   if ( !m_dstrAccountNum.empty() )
   {
      m_dstrShrNum.stripLeading('0');
      DString dstrEntityName;
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
         m_dstrAccountNum, 
         dstrEntityName, 
         true);

      SetShrAcctCaption( m_dstrShrNum, m_dstrAccountNum, dstrEntityName );
   }
   else
   {
      DString dstrFirstName, dstrLastName;
      getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, dstrFirstName );
      getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName,  dstrLastName );
	  CString cstrEntityAddrforEntity;
	  cstrEntityAddrforEntity.LoadString(TXT_ENTITY_ADDR_FOR_ENTITY);
	  
		DString dstrCaption = DString(cstrEntityAddrforEntity) 
			+ m_dstrEntityId
			+ I_( "; " ) + dstrLastName + I_( "; " ) + dstrFirstName;

      SetWindowText( dstrCaption.c_str() );
   }
}

//-----------------------------------------------------------------------------------
void BaseAddressBookDlg::ShowAcctMailingOverride(bool bFreshList)
{

   /*((CButton* )GetDlgItem(IDC_RB_SHAREHOLDER))->SetCheck(true);
   ((CButton* )GetDlgItem(IDC_RB_ENTITY))->SetCheck(false);
   getParent()->getField(this, IFASTBP_PROC::SHAREHOLDER_LIST,ifds::Name2,strAddtlRegInit);

   GetDlgItem (IDC_TXT_ENTITY_DEFAULT_ADDRESS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_DEFAULT_ADDRESS)->ShowWindow (SW_HIDE);

   GetDlgItem (IDC_TXT_ENTITY_OUTPUT )->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_OUTPUT )->ShowWindow (SW_HIDE);	
   GetDlgItem(IDC_BTN_RESET)->EnableWindow();
   GetDlgItem (IDC_SHAREHOLDER_REG)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_ADDTL)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_ENTITY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ROLE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_TXT_ROLE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_ADDRESS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_ENTITY_ADDRESS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_CITY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ADDRESS_ID)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_ENTITY_ADDRESS_ID)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_ENTITY_POST)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_HOLD_MAIL)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_HOLD_MAIL)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_PROVINCE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_BTN_CHANGE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_LV_ENTITY_MAILING)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_ADD)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_BTN_DELETE)->ShowWindow (SW_SHOW);
   GetDlgItem(IDC_CMB_CODE)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_STATIC__SHAREHOLDER_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SALUTATION)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_SALUTATION)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_NAME)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_EDT_NAME)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_EFFECTIVE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_EFF_DATE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_STOP)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_STOP_DATE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_SHAREHOLDER_ADDRESS)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_ADDRESS)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_EDT_POST_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_MAIL)->EnableWindow (true);
   GetDlgItem (IDC_CMB_DISP_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_DISP_CODE)->EnableWindow (true);
   GetDlgItem (IDC_STATIC_CODE)->EnableWindow (true);*/

   GetDlgItem (IDC_RB_DEFAULT)->ShowWindow (SW_SHOW);
   ((CButton* )GetDlgItem(IDC_RB_DEFAULT))->SetCheck(false);
   GetDlgItem (IDC_RB_DEFAULT)->EnableWindow(true);
   GetDlgItem (IDC_RB_OVERRIDE)->ShowWindow (SW_SHOW);
   //	((CButton* )GetDlgItem(IDC_RB_OVERRIDE))->SetCheck(true);
   //	GetDlgItem (IDC_RB_OVERRIDE)->EnableWindow(true);

   GetDlgItem (IDC_LV_MAIL_ASSIGN)->ShowWindow (SW_HIDE);
   //	GetDlgItem (IDC_LV_MAIL_ASSIGN)->EnableWindow (false);
   GetDlgItem (IDC_LV_ACCT_MAILING_OVERRIDE)->ShowWindow (SW_SHOW);

   GetDlgItem (IDC_BTN_ENTITY_MAIL_ADD)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_BTN_ENTITY_MAIL_DELETE)->ShowWindow(SW_SHOW);

   if( m_strSearShareholder == I_("Y") )
   {
      GetDlgItem(IDC_LV_ACCT_MAILING_OVERRIDE)->EnableWindow(false);
   }
   else 
   {		
      GetDlgItem (IDC_LV_ACCT_MAILING_OVERRIDE)->EnableWindow (true);	
   }
   FillAcctMailOverrideList();
}

//-----------------------------------------------------------------------------------
void BaseAddressBookDlg::ShowShareHolder(bool bFreshList) 
{
   ((CButton* )GetDlgItem(IDC_RB_SHAREHOLDER))->SetCheck(true);
   ((CButton* )GetDlgItem(IDC_RB_ENTITY))->SetCheck(false);
   getParent()->getField(this, IFASTBP_PROC::SHAREHOLDER_LIST,ifds::Name2,strAddtlRegInit);
   //   GetDlgItem (IDC_EDT_SHAREHOLDER_ADDCODE)->ShowWindow (SW_HIDE);
   // GetDlgItem (IDC_SHAREHOLDER_CODEDESC)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_TXT_ENTITY_DEFAULT_ADDRESS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_DEFAULT_ADDRESS)->ShowWindow (SW_HIDE);

   GetDlgItem (IDC_TXT_ENTITY_OUTPUT )->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_OUTPUT )->ShowWindow (SW_HIDE);	
   GetDlgItem (IDC_BTN_RESET)->EnableWindow();
   GetDlgItem (IDC_SHAREHOLDER_REG)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_ADDTL)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_ENTITY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ROLE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_TXT_ROLE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_ADDRESS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_ENTITY_ADDRESS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_CITY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ADDRESS_ID)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_ENTITY_ADDRESS_ID)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_HOLD_MAIL)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_HOLD_MAIL)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_PROVINCE)->ShowWindow (SW_HIDE);	
   GetDlgItem (IDC_LV_ENTITY_MAILING)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_ENTITY_MAIL_ADD)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_ENTITY_MAIL_DELETE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_ADD)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_BTN_DELETE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_CODE)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_STATIC__SHAREHOLDER_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SALUTATION)->ShowWindow (SW_SHOW);
   GetDlgItem (m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_NAME)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_EDT_NAME)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_EFFECTIVE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_EFF_DATE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_STOP)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_STOP_DATE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_SHAREHOLDER_ADDRESS)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_ADDRESS)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_SHR_POST)->ShowWindow (SW_SHOW);	
   GetDlgItem (IDC_EDT_POST_CODE)->ShowWindow (SW_SHOW);

   DString dstrAddrFormat;
   DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );

   GetDlgItem (IDC_RB_DEFAULT)->ShowWindow (SW_SHOW);
   ((CButton* )GetDlgItem(IDC_RB_DEFAULT))->SetCheck(true);
   GetDlgItem (IDC_RB_DEFAULT)->EnableWindow(true);
   GetDlgItem (IDC_RB_OVERRIDE)->ShowWindow (SW_SHOW);
   DString str;
   getParent()->getField( this, BF::NullContainerId, ifds::MailingByFundGroup, str,false );
   GetDlgItem(IDC_RB_OVERRIDE)->EnableWindow(str.strip().upperCase() == YES );

//	((CButton* )GetDlgItem(IDC_RB_OVERRIDE))->SetCheck(false);
//	GetDlgItem (IDC_RB_OVERRIDE)->EnableWindow(true);
   GetDlgItem (IDC_LV_ACCT_MAILING_OVERRIDE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_LV_ACCT_MAILING_OVERRIDE)->EnableWindow (false);	



   // Mailing Assignments Group Control
   GetDlgItem (IDC_STATIC_MAIL)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_STATIC_MAIL)->EnableWindow (true);
   GetDlgItem (IDC_LV_MAIL_ASSIGN)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_DISP_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STATIC_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_DISP_CODE)->EnableWindow (true);
   GetDlgItem (IDC_STATIC_CODE)->EnableWindow (true);
   GetDlgItem (IDC_BTN_HISTORICAL)->EnableWindow(true);

   if( m_strSearShareholder == I_("Y") )
   {
      GetDlgItem(IDC_LV_MAIL_ASSIGN)->EnableWindow(false);
      GetDlgItem(IDC_CMB_DISP_CODE)->EnableWindow(false);
   }
   else GetDlgItem (IDC_LV_MAIL_ASSIGN)->EnableWindow (true);

   // Code
   GetDlgItem(IDC_CMB_CODE)->ShowWindow(SW_SHOW);
   // Entity Address Code
   GetDlgItem(IDC_EDT_ENTITY_ADDRESS_CODE)->ShowWindow(SW_HIDE);
   // Entity Address Effective Date   
   GetDlgItem(IDC_TXT_ENTITY_ADDRESS_EFFECTIVE )->ShowWindow( SW_HIDE );
   GetDlgItem(IDC_DTP_ENTITY_ADDRESS_EFFECTIVE)->ShowWindow( SW_HIDE );
   // Entity Address Name
   GetDlgItem(IDC_TXT_ENTITY_ADDR_NAME )->ShowWindow( SW_HIDE );
   GetDlgItem(IDC_EDT_ENTITY_ADDR_NAME)->ShowWindow( SW_HIDE ); 
   // Postal Code
   GetDlgItem (IDC_STATIC_ENTITY_POST)->ShowWindow (SW_HIDE);	
   GetDlgItem (IDC_EDT_ENTITY_POST)->ShowWindow (SW_HIDE);
   // Province
   GetDlgItem (IDC_STATIC_ENTITY_PROVINCE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_PROVINCE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_ENTITY_PROVINCE)->ShowWindow (SW_HIDE);		
   
   DisplayAddressLvList();

   if( m_dstrSel_ShareholderList!= NULL_STRING )
   {
      GetList(IDC_LV_ADDRESSES)->SetSelection( &m_dstrSel_ShareholderList );
   }
   else 
   {
      GetList(IDC_LV_ADDRESSES)->SetSelection( 0 );
   }

   DString strIsRegAddrReadOnly;
   getParent()->getField( this, ADDRLIT::REG_ADDR_READ_ONLY, strIsRegAddrReadOnly );
   if (	(m_strNASUFlag == YES )  &&	(strIsRegAddrReadOnly.compare(YES) == 0) ){
      if (getParent()->getNumberOfItemsInList(this,IFASTBP_PROC::ADDRESSES_LIST)<2)
         AddToListControl( IDC_LV_ADDRESSES );
      GetList( IDC_LV_ADDRESSES )->SetFocus();
   }
   FillMailAddressList();
   GetList( IDC_LV_ADDRESSES )->SetFocus();

   GetDlgItem( IDOK )->EnableWindow( true );	

   doDisableNonPermButtons();

   GetDlgItem (IDC_STATIC_VERIFY)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_VERIFY_STAT)->ShowWindow (SW_SHOW);

   if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA){
      m_pMailInfoTabCtrl->ShowWindow(SW_SHOW);
      m_pMailInfoTabCtrl->SelectTab(TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->Load(TAB_ADDR_INFO);
   }
   else
   {
      DSTCWorkSession *pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
      bool bVerificationEnabled = false;
      pWorkSession->isVerificationEnabled ( idDataGroup, 
                                            SHRHLDR_CATEGORY, 
                                            SHRHLDR_LEVEL, 
                                            bVerificationEnabled);

      if ( bVerificationEnabled )
      {
         GetDlgItem( IDC_CMB_VERIFY_STAT )->EnableWindow( TRUE );
      }
      else
      {
         GetDlgItem( IDC_CMB_VERIFY_STAT )->EnableWindow( FALSE );
      }
   }
}

//---------------------------------------------------------
void BaseAddressBookDlg::ShowEntity() 
{
   if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   {
      m_pMailInfoTabCtrl->SelectTab(TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->Load(TAB_ADDR_INFO);
	  m_pMailInfoTabCtrl->ShowWindow(SW_SHOW);
      //m_pMailInfoTabCtrl->ShowWindow(SW_HIDE);

   }

   ((CButton* )GetDlgItem(IDC_RB_SHAREHOLDER))->SetCheck(0);
   ((CButton* )GetDlgItem(IDC_RB_ENTITY))->SetCheck(1);

   // If we come directly from Entity, with no account attached to it, then
   // there is no Shareholder and disable the Shareholder option
   if ( m_dstrFromEntity == I_( "Y" ) && m_dstrAccountNum.empty() )
   {
      GetDlgItem( IDC_RB_SHAREHOLDER )->EnableWindow(false);
      GetDlgItem( IDC_RB_ENTITY )->EnableWindow(true);	
   }
   else
   {

   }

   GetDlgItem (IDC_STATIC_VERIFY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_VERIFY_STAT)->ShowWindow (SW_HIDE);

   // Hide Shareholder Address related controls
   GetDlgItem(IDC_CMB_CODE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_STATIC_SALUTATION)->ShowWindow(SW_HIDE);
   //GetDlgItem ( m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION)->ShowWindow (SW_HIDE);
   GetDlgItem ( IDC_EDT_SALUTATION )->ShowWindow (SW_HIDE);
   GetDlgItem ( IDC_CMB_SALUTATION )->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_NAME)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_EDT_NAME)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_STATIC_EFFECTIVE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_DTP_EFF_DATE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_STATIC_STOP)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_DTP_STOP_DATE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_SHAREHOLDER_REG)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_ADDTL)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_SHAREHOLDER_ADDRESS)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_STATIC_SHAREHOLDER_ADDRESS)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_STATIC_SHR_POST)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_EDT_POST_CODE)->ShowWindow(SW_HIDE);

   DString dstrAddrFormat;
   DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );

   GetDlgItem (IDC_EDT_REG_ADDR_CODE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_TXT_REG_ADDR_CODE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_STATIC_CODE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_CMB_DISP_CODE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_RB_DEFAULT)->ShowWindow(SW_HIDE);	
   GetDlgItem (IDC_RB_DEFAULT)->EnableWindow(false);
   GetDlgItem (IDC_RB_OVERRIDE)->ShowWindow(SW_HIDE);	
   GetDlgItem (IDC_RB_OVERRIDE)->EnableWindow(false);
   // Mailing Assignments
   GetDlgItem (IDC_LV_MAIL_ASSIGN)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_LV_MAIL_ASSIGN)->EnableWindow(false);
   // Hide Shaholder Mailing Override
   GetDlgItem (IDC_LV_ACCT_MAILING_OVERRIDE)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_LV_ACCT_MAILING_OVERRIDE)->EnableWindow(false);

   //************* Show Entity Address related controls  ****************/
   // Entities combo
   GetDlgItem (IDC_CMB_ENTITY)->ShowWindow(SW_SHOW);

   // Role
   if ( m_dstrAccountNum.empty() )
   {
      GetDlgItem (IDC_STATIC_ROLE)->ShowWindow(SW_HIDE);
      GetDlgItem (IDC_TXT_ROLE)->ShowWindow(SW_HIDE);
   }
   else
   {
      GetDlgItem (IDC_STATIC_ROLE)->ShowWindow(SW_SHOW);		
      GetDlgItem (IDC_TXT_ROLE)->ShowWindow(SW_SHOW);
   }

   // Address History   
   GetDlgItem(IDC_BTN_HISTORY)->EnableWindow( false );
      // Mailing History   
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( false );

   // Entity Address Effective Date
      GetDlgItem(IDC_STATIC_EFFECTIVE )->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TXT_ENTITY_ADDRESS_EFFECTIVE )->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_DTP_ENTITY_ADDRESS_EFFECTIVE)->ShowWindow(SW_SHOW);
   // Entity Address Code
   GetDlgItem(IDC_EDT_ENTITY_ADDRESS_CODE)->ShowWindow(SW_SHOW);    
   // Entity Adddress
   GetDlgItem (IDC_STATIC_ENTITY_ADDRESS)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_ENTITY_ADDRESS)->ShowWindow(SW_SHOW);
   // Entity Address City
   GetDlgItem (IDC_STATIC_CITY)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_EDT_CITY)->ShowWindow(SW_SHOW);
   // Entity Address ID
   GetDlgItem (IDC_STATIC_ADDRESS_ID)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_EDT_ENTITY_ADDRESS_ID)->ShowWindow(SW_SHOW);
   // Entity Address Postal/Zip
   GetDlgItem (IDC_STATIC_ENTITY_POST)->ShowWindow(SW_SHOW);	
   GetDlgItem (IDC_EDT_ENTITY_POST)->ShowWindow(SW_SHOW);
   // Entity Country
   GetDlgItem (IDC_STATIC_ENTITY_COUNTRY)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_CMB_ENTITY_COUNTRY)->ShowWindow(SW_SHOW);
   // Entity Province
   GetDlgItem (IDC_STATIC_ENTITY_PROVINCE)->ShowWindow(SW_SHOW);
   // If Country will have no Province, the Combo will be replaced
   // by an Edit so user can enter something
   // The switch will be done in COntrolUpdated for IDC_CMB_ENTITY_COUNTRY
   //int i = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::PROVINCE_LIST );	

   if ( m_dstrAccountNum.empty() )
   {
      /************ Hide Mailing Info related controls ***************/

      // Mailing Assignments Group Control
      GetDlgItem (IDC_STATIC_MAIL)->ShowWindow(SW_HIDE);

      // Hold Mail
      GetDlgItem (IDC_STATIC_ENTITY_HOLD_MAIL)->ShowWindow(SW_HIDE);
      GetDlgItem (IDC_CMB_ENTITY_HOLD_MAIL)->ShowWindow(SW_HIDE);

      SetDlgItemText( IDC_STATIC_MAIL, I_( "" ) );

      // Display Output
      GetDlgItem (IDC_CMB_ENTITY_OUTPUT)->ShowWindow(SW_HIDE);
      GetDlgItem (IDC_TXT_ENTITY_OUTPUT)->ShowWindow(SW_HIDE);

      // Default Address
      GetDlgItem (IDC_TXT_ENTITY_DEFAULT_ADDRESS)->ShowWindow(SW_HIDE);
      GetDlgItem (IDC_CMB_ENTITY_DEFAULT_ADDRESS)->ShowWindow(SW_HIDE);

      // Mailing Info
      GetDlgItem (IDC_LV_ENTITY_MAILING)->ShowWindow(SW_HIDE);
      GetDlgItem (IDC_LV_ENTITY_MAILING)->EnableWindow(false);

      ClearMailingList();

      // Add/Delete buttons for Mailing Info
      GetDlgItem (IDC_BTN_ENTITY_MAIL_ADD)->ShowWindow(SW_HIDE);
      GetDlgItem (IDC_BTN_ENTITY_MAIL_DELETE)->ShowWindow(SW_HIDE);				
   }
   else
   {
      /**************** Show Mailing Info related controls *************/

      // Mailing Assignments Group Control
      GetDlgItem (IDC_STATIC_MAIL)->ShowWindow(SW_SHOW);

      // Hold Mail
      GetDlgItem (IDC_STATIC_ENTITY_HOLD_MAIL)->ShowWindow(SW_SHOW);
      GetDlgItem (IDC_CMB_ENTITY_HOLD_MAIL)->ShowWindow(SW_SHOW);				

      // Display Output
      GetDlgItem (IDC_TXT_ENTITY_OUTPUT)->ShowWindow(SW_SHOW);
      GetDlgItem (IDC_CMB_ENTITY_OUTPUT)->ShowWindow(SW_SHOW);

      // Default Address
      GetDlgItem (IDC_TXT_ENTITY_DEFAULT_ADDRESS)->ShowWindow(SW_SHOW);
      GetDlgItem (IDC_CMB_ENTITY_DEFAULT_ADDRESS)->ShowWindow(SW_SHOW);

      // Mailing Info
      GetDlgItem (IDC_LV_ENTITY_MAILING)->ShowWindow (SW_SHOW);
      GetDlgItem (IDC_LV_ENTITY_MAILING)->EnableWindow (true);

      // Add/Delete buttons for Mailing Info
      GetDlgItem (IDC_BTN_ENTITY_MAIL_ADD)->ShowWindow ( SW_SHOW );
      GetDlgItem (IDC_BTN_ENTITY_MAIL_DELETE)->ShowWindow ( SW_SHOW );		
   } 

   // Entity Address Name
   GetDlgItem(IDC_TXT_ENTITY_ADDR_NAME )->ShowWindow( SW_SHOW );
   GetDlgItem(IDC_EDT_ENTITY_ADDR_NAME)->ShowWindow( SW_SHOW );

   GetDlgItem (IDC_STATIC_VERIFY)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_VERIFY_STAT)->ShowWindow (SW_HIDE);

   OnSelchangeCmbEntity();

   if( m_dstrSel_EntityList!= NULL_STRING )
      GetList(IDC_LV_ADDRESSES)->SetSelection( &m_dstrSel_EntityList );
   else 
      GetList(IDC_LV_ADDRESSES)->SetSelection( 0 );

   GetList( IDC_LV_ADDRESSES )->SetFocus();

   GetDlgItem( IDOK )->EnableWindow( hasCreatePermission( UAF::ENTITY_MAINTANENCE ) ||
                                     hasUpdatePermission( UAF::ENTITY_MAINTANENCE ) );

   doDisableNonPermButtons();
}

//------------------------------------------------------------------------------
void	BaseAddressBookDlg::PostOk( bool  bOkStatus  )
{
   setParameter( ADDRLIT::ACCOUNT_NUM, m_dstrAccountNum );
   setParameter( ADDRLIT::ENTITY_ID, m_dstrEntityId );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, m_dstrEntityId );
   setParameter( ADDRLIT::SHAREHOLDER_NUM, m_dstrShrNum );

   if ( isModal() )
   {
      setParameter( ADDRLIT::ADDRESS_CODE, m_dstrAddrCode );
   }
}

//-------------------------------------------------------------------------------
void BaseAddressBookDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;

   if ( IsShareholder() )
      ShowAdminDates( IFASTBP_PROC::ADDRESSES_LIST );
   else
      ShowAdminDates( IFASTBP_PROC::ENTITY_ADDRESS_LIST );
}

//*******************************************************************************
bool BaseAddressBookDlg::PreOk()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "PreOk" ) );

   try
   {
      //Moved to AddressProcess::doOk
   /*
      DString dstrTaxJurisUpdateOpt, dstrIsNewOrUpdate;

      SEVERITY severity =  GETHIGHESTSEVERITY();
      
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(ifds::TaxJurisUpdateOpt, dstrTaxJurisUpdateOpt, 
         getDataGroupId(), false);
      getParent()->getField(this, BF::NullContainerId, ifds::IsNewOrUpdate, dstrIsNewOrUpdate, false);
      if(dstrTaxJurisUpdateOpt == I_("Y")&& dstrIsNewOrUpdate == I_("Y"))
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         setParameter(ADDRLIT::ACCOUNT_NUM, m_dstrAccountNum);
         setParameter(ADDRLIT::SHAREHOLDER_NUM, m_dstrShrNum);
         setParameter(ADDRLIT::ENTITY_ID, m_dstrEntityId);
         setParameter(ADDRLIT::SEQ_NUMBER, m_dstrSeqNum);
         
         eRtn = invokeCommand(getParent(), CMD_BPROC_ADDR_TAX_JURIS_UPDATE, PROC_SUPPORT, true, NULL);
         if(eRtn == CMD_CANCEL)
            return false;
      }
      */
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return true;
}

//---------------------------------------------------------------------------------------------
void BaseAddressBookDlg::FillDisplayCodeComboBox()
{
   m_DisplayCode.Clear();
   CString cString;
   DString strAll;
   DString strSelect;
   m_DisplayCode.ResetContent();	
   cString.LoadString( TXT_ALL );
   strAll = (LPCTSTR )cString;
   m_DisplayCode.InsertString(DISPLAYCODEALL,strAll.c_str() );
   cString.LoadString( TXT_SELECTED );
   strSelect = (LPCTSTR )cString;
   m_DisplayCode.InsertString(DISPLAYCODESELECT, strSelect.c_str() );
   m_DisplayCode.SetCurSel(0);
}

//-----------------------------------------------------------------------------
bool  BaseAddressBookDlg::doRefresh( GenericInterface * /*rpGICaller*/, 
                                     const I_CHAR * //*szOriginalCommand
                                    )
{  
   getParent()->getParameter( NASULIT::CREATING_ACCOUNT, m_strNASUFlag );
   getParent()->getParameter( ADDRLIT::ACCOUNT_NUM, m_dstrAccountNum );
   getParent()->getParameter( ADDRLIT::SHAREHOLDER_NUM, m_dstrShrNum ); 
   getParent()->getParameter( ADDRLIT::ADDRESS_CODE, m_dstrAddrCode );

   getParameter( ADDRLIT::FROM_ENTITY, m_dstrFromEntity);
   getParameter( ADDRLIT::ENTITY_ID,   m_dstrEntityId);
   getParameter( ADDRLIT::ENTITY_TYPE, m_dstrEntityType );
   getParameter( ADDRLIT::SEQ_NUMBER,  m_dstrSeqNum );

   getParent()->clearParameters();
   setDlgTitle();

   findAddrCode();

   if ( m_bShareEntity )
      ShowShareHolder(true);
   else
      ShowEntity();   
   return true;
}

//------------------------------------------------------------------------------------------------------
void  BaseAddressBookDlg::FillEntityCombo()
{
   DString str,str1; 
   const DString *key = &getParent()->getFirstListItemKey( this, IFASTBP_PROC::ENTITY_LIST); 
   m_EntityName.ResetContent();
   int index = 0, iCurrent = 0;
   if ( *key != EMPTY_STRING )
   {
      do
      {
         DString dstrCurrentAccountNum, dstrCurrentEntityId, dstrCurrentEntityType, dstrCurrentSeqNum;			
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::AccountNum, dstrCurrentAccountNum );	
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId,   dstrCurrentEntityId );				
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrCurrentEntityType, false );				
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::SeqNumber,  dstrCurrentSeqNum );							
         if ( dstrCurrentAccountNum.strip() == m_dstrAccountNum &&
            dstrCurrentEntityId.strip()   == m_dstrEntityId &&
            dstrCurrentEntityType.strip() == m_dstrEntityType &&
            dstrCurrentSeqNum.strip()     == m_dstrSeqNum	)
         {
            iCurrent = index;
         }

         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, str );
         str.strip(); 
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, str1 );
         str1.strip(); 
         str += I_(" ") + str1;

         getDisplayName(IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, ifds::LastName, str);

         m_EntityName.InsertString(index,str.c_str() );
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, str1 );   
         m_EntityName.SetItemData( index, (DWORD)key);
         index++;
      } while ( *(key = &getParent()->getNextListItemKey( this, IFASTBP_PROC::ENTITY_LIST )) !=EMPTY_STRING ); 

      m_EntityName.SetCurSel(iCurrent);
      const DString* key =(const DString* )m_EntityName.GetItemData( iCurrent );      	  
      getParent()->setCurrentListItem( this, IFASTBP_PROC::ENTITY_LIST, *key );
   }
}

//----------------------------------------------------------------------------------------------------------
void BaseAddressBookDlg::OnSelchangeCmbDispCode() 
{
   FillMailAddressList();
   
}

//---------------------------------------------------------------------------------------------------------
void BaseAddressBookDlg::OnSelchangeCmbEntity() 
{
   /******************** Called only for Entity Address *********************************/
   DString   str;
   int index = m_EntityName.GetCurSel();
   if ( index >= 0 )
   {
      SetMessageStatusBar( TXT_LOAD_ENTITY_ADDRESS );
      CWaitCursor wait;

      const DString* key =(const DString* )m_EntityName.GetItemData( index );      	  
      getParent()->setCurrentListItem( this, IFASTBP_PROC::ENTITY_LIST, *key );
      getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, m_dstrEntityId );
      m_dstrEntityId.stripLeading('0');
      setParameter(I_( "EntityID" ), m_dstrEntityId);
      setParameter(I_("ListKey"),*key);
      getParent()->setCurrentListItem(this, IFASTBP_PROC::ENTITY_LIST,SPACE_STRING );//
      DisplayAddressLvList();

      if ( !m_dstrAccountNum.empty() )	
         LoadControl(IDC_TXT_ROLE);
      
      SetMessageStatusBar( NULL_STRING);
   }

   // Build m_dstrEntityAddrCodeList only if Entity is linked to an Account
   // m_dstrEntityAddrCodeList will be used for Default Addr Code
   if ( !m_dstrAccountNum.empty() )
   {
      DString dstrCode,dstrDes;
      m_dstrEntityAddrCodeList = NULL_STRING;
      const DString *pCurKey = &(getParent()->getCurrentListItemKey(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST) );
      const DString *pKey = &(getParent()->getFirstListItemKey(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST) );
      if(*pKey!= EMPTY_STRING )
      {
         do
         {
            getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrCode,dstrCode,false );
            dstrCode.strip();	
            //getParent()->getField( this, ENTITY_ADDRESS_LIST, ifds::AddrDesc,dstrDes,false );
            //dstrCode.strip();	
            m_dstrEntityAddrCodeList += dstrCode + I_("=") + dstrCode + I_(";");

         } while ( *( pKey = &getParent()->getNextListItemKey( this, 
               IFASTBP_PROC::ENTITY_ADDRESS_LIST) ) != EMPTY_STRING );

            getParent()->setCurrentListItem(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST,*pCurKey);
      }
   }

   LoadEntityAddress();

   // Load Mailing only if Entity is linked to an Account
   if ( !m_dstrAccountNum.empty() )
   {
      InitControl(IDC_CMB_ENTITY_OUTPUT );
      InitControl(IDC_CMB_ENTITY_DEFAULT_ADDRESS);

      bool bModPermit = hasUpdatePermission(UAF::ENTITY_MAINTANENCE);
      GetDlgItem( IDC_CMB_ENTITY_DEFAULT_ADDRESS )->EnableWindow( bModPermit );

      DString dstrOPDeliveryOption;
      getParent()->getField(this, BF::NullContainerId, ifds::OPDeliveryOption,dstrOPDeliveryOption,false);					

      dstrOPDeliveryOption.strip();
      int iNum = getParent()->getNumberOfItemsInList(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST);

      bool bEnable = dstrOPDeliveryOption == YES ;

      int iShow = isAccountOwner() ||  dstrOPDeliveryOption == NO? SW_HIDE : SW_SHOW;
      GetDlgItem (IDC_STATIC_ENTITY_HOLD_MAIL)->ShowWindow (m_strCurrentMailingPageName == TAB_RETMAIL_INFO ? SW_HIDE:iShow);
      GetDlgItem (IDC_CMB_ENTITY_HOLD_MAIL)->ShowWindow (m_strCurrentMailingPageName == TAB_RETMAIL_INFO ? SW_HIDE:iShow);
      GetDlgItem (IDC_STATIC_MAIL)->ShowWindow(iShow);
      GetDlgItem (IDC_TXT_ENTITY_OUTPUT )->ShowWindow (iShow);
      GetDlgItem (IDC_CMB_ENTITY_OUTPUT )->ShowWindow (iShow);
      GetDlgItem (IDC_TXT_ENTITY_DEFAULT_ADDRESS)->ShowWindow (iShow);
      GetDlgItem (IDC_CMB_ENTITY_DEFAULT_ADDRESS)->ShowWindow (iShow);
      GetDlgItem (IDC_LV_ENTITY_MAILING)->ShowWindow (iShow);
      GetDlgItem (IDC_BTN_ENTITY_MAIL_ADD)->ShowWindow (iShow);
      GetDlgItem (IDC_BTN_ENTITY_MAIL_DELETE)->ShowWindow (iShow);		

      if( !isAccountOwner() )	
      {
         GetDlgItem(IDC_LV_ENTITY_MAILING )->EnableWindow(bEnable);
         DSTGridWnd *pGrid = GetGrid( IDC_LV_ENTITY_MAILING );
         pGrid->SetSorting( true );
         pGrid->reLoadGrid();
         //GetDlgItem(IDC_BTN_ENTITY_MAIL_ADD)->EnableWindow(bEnable);
         //GetDlgItem(IDC_BTN_ENTITY_MAIL_DELETE)->EnableWindow(bEnable);
         bool bNewitem = true;
         const DString key = getParent()->getFirstListItemKey(this,
                           IFASTBP_PROC::ENTITY_MAILING_LIST  );
         if( key != NULL_STRING )
         {

            bNewitem = dynamic_cast<AbstractProcess* >( getParent() )->isCurrentListItemNew( this, 
                                    IFASTBP_PROC::ENTITY_MAILING_LIST  );
         }
         GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow(bEnable && !bNewitem );         
      }
   }

   if ( !m_dstrAccountNum.empty() )
   {
      DString strValue;
      getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::AddrCode,strValue,false);
      strValue.strip();
      DSTComboBox*	pCombo = dynamic_cast<DSTComboBox* >(GetDlgItem (IDC_CMB_ENTITY_DEFAULT_ADDRESS) );
      pCombo->SelectString(0, strValue.c_str() );
   }
}

//***********************************************************************************************************
void BaseAddressBookDlg::OnBtnReset() 
{
   if( IsShareholder() )
   {
      //for Acc. Des. 2 or 3 for AddCode 01, the only thing to reset is Addtl reg.
      DString strIsRegAddrReadOnly;
      DString strAddrCode,
              strAcctDesignation;

      getParent()->getField( this, ADDRLIT::REG_ADDR_READ_ONLY, strIsRegAddrReadOnly );
      getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, strAddrCode, false );
      getParent()->getField( this, BF::NullContainerId, ifds::AcctDesignation, strAcctDesignation, false );
      strAcctDesignation.strip().upperCase();

      bool bCanRefreshAddress = true;

      if ( ( strAcctDesignation == I_("2") || strAcctDesignation == I_("3")) && (strAddrCode == I_("01") ) )
      {
         bCanRefreshAddress = false;
      }

      if ( bCanRefreshAddress )
      {
         ResetListItem( IDC_LV_ADDRESSES );
      }
      else
      {
         // need special code for uncliamed property
         // relate to be able reset unclaimed related fields
         // of address code 01 of non-client help account
         DoRefreshUncliamedRelatedFieldsForAddrCode01( );

         // only nominee account whose 'RegAddr' canbe change
         // therefore allow reset to this field
         if ( strAddrCode == I_("01") && strIsRegAddrReadOnly == YES )
         {
            // refresh field RegAddrCode if there is a change
            DoRefreshRegAddrCode( );
         }
      }

      //ResetListItem( IDC_LV_ADDRESSES );

      getParent()->resetCurrentItem( IFASTBP_PROC::ACCOUNT_MAILING_LIST );
      if( m_strNASUFlag == I_("Y") )getParent()->getKeyForNewListItem( this, 
                     IFASTBP_PROC::ACCOUNT_MAILING_LIST  );

      getParent()->setField(this, IFASTBP_PROC::SHAREHOLDER_LIST,ifds::Name2, strAddtlRegInit);
      LoadControl(IDC_SHAREHOLDER_REG);
      OnSelRetMail( );
      if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      {
         m_pMailInfoTabCtrl->SelectTab(TAB_ADDR_INFO);
         m_pMailInfoTabCtrl->Load();
      }
   }
   else
   {
      ResetListItem( IDC_LV_ADDRESSES );

      if ( !m_dstrAccountNum.empty() )
         ResetGridItem( IDC_LV_ENTITY_MAILING );
   }

   FillMailAddressList();
   GetList( IDC_LV_ADDRESSES )->SetFocus();
}

//*************************************************************************************************************

LRESULT BaseAddressBookDlg::OnListViewItemChanged(WPARAM PreviousSelection, LPARAM ListIdentifier)
{
   TRACE_METHOD( CLASSNAME, I_( "OnListViewItemChanged" ) );

   return(0);

}
//*************************************************************************************************************
void BaseAddressBookDlg::OnBtnDelete() 
{
   //if( IsShareholder() ){
      if( DeleteFromListControl( IDC_LV_ADDRESSES ) )
         FillMailAddressList();
   //}
   if( IsShareholder() && DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   {
      m_pMailInfoTabCtrl->SelectTab(TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->Load();
   }

   if ( !IsShareholder() )
   {
		// Build m_dstrEntityAddrCodeList only if Entity is linked to an Account
		// m_dstrEntityAddrCodeList will be used for Default Addr Code
		if ( !m_dstrAccountNum.empty() )
		{
			DString dstrCode,dstrDes;
			m_dstrEntityAddrCodeList = NULL_STRING;
			const DString *pCurKey = &(getParent()->getCurrentListItemKey(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST) );
			const DString *pKey = &(getParent()->getFirstListItemKey(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST) );
			if(*pKey!= EMPTY_STRING )
			{	
				do
				{
					getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrCode,dstrCode,false );
					dstrCode.strip();	
					//getParent()->getField( this, ENTITY_ADDRESS_LIST, ifds::AddrDesc,dstrDes,false );
					//dstrCode.strip();	
 					m_dstrEntityAddrCodeList += dstrCode + I_("=") + dstrCode + I_(";");
						
				} while ( *( pKey = &getParent()->getNextListItemKey( this, 
                        IFASTBP_PROC::ENTITY_ADDRESS_LIST) ) != EMPTY_STRING );
				
				getParent()->setCurrentListItem(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST,*pCurKey);
			}

         DString strValue;
         getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::AddrCode,strValue,false);
         strValue.strip();

         InitControl(IDC_CMB_ENTITY_DEFAULT_ADDRESS);	

         DSTComboBox*	pCombo = dynamic_cast<DSTComboBox* >(GetDlgItem (IDC_CMB_ENTITY_DEFAULT_ADDRESS) );
         pCombo->SelectString(0, strValue.c_str() );

         if( !isAccountOwner() )	
         {
            DSTGridWnd *pGrid = GetGrid( IDC_LV_ENTITY_MAILING );
            pGrid->reLoadGrid();
         }
      }
   }

   GetList( IDC_LV_ADDRESSES )->SetFocus();
}

//**************************************************************************************************************
void BaseAddressBookDlg::OnBtnAdd() 
{
   AddToListControl( IDC_LV_ADDRESSES );
   GetList( IDC_LV_ADDRESSES )->SetFocus();
}

//**************************************************************************************************************
void	BaseAddressBookDlg::DoListItemChanged(
      UINT ListControlID,
      const DString &strKey, 
      bool bIsNewItem , 
      bool bIsDummyItem
      )
{
   m_bCurrAddressNew = bIsNewItem;
   if ( strKey != NULL_STRING )
   {
      if ( !IsShareholder() )
         getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrCode, m_dstrAddrCode,false );	
      else
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST,      ifds::AddrCode, m_dstrAddrCode,false );

      m_dstrAddrCode.strip();
      if(!m_bLoadMailing)
         FillMailAddressList();
   }

   // History
   if ( IsShareholder() )
   {
      GetDlgItem(IDC_BTN_HISTORY)->EnableWindow( (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );
	  m_dstrSel_ShareholderList = getParent()->getCurrentListItemKey(this,IFASTBP_PROC::ADDRESSES_LIST);
   }
   else 
   {
      GetDlgItem(IDC_BTN_HISTORY)->EnableWindow( false );
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( false );
      m_dstrSel_EntityList = getParent()->getCurrentListItemKey(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST);
   }


   DString dstrAddrFormat;
   DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );
}

//*********************************************************************************************************
void BaseAddressBookDlg::SetAddressControlsReadOnly(bool bReadOnly)
{
   GetDlgItem(IDC_CMB_CODE)->EnableWindow(!bReadOnly);
   GetDlgItem( m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION )->EnableWindow(!bReadOnly);	
   GetDlgItem( IDC_EDT_NAME )->EnableWindow(!bReadOnly);
   GetDlgItem( IDC_SHAREHOLDER_ADDRESS )->EnableWindow(!bReadOnly);
   GetDlgItem( IDC_EDT_POST_CODE )->EnableWindow(!bReadOnly);
   GetDlgItem( IDC_DTP_EFF_DATE )->EnableWindow(!bReadOnly);
   GetDlgItem( IDC_DTP_STOP_DATE )->EnableWindow(!bReadOnly);
}

//**********************************************************************************************************
bool BaseAddressBookDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   DString str;
   if ( lSubstituteId == ifds::EntityAddressHeadingSet.getId() )
   {
      if ( ColumnKey == ADDRESSCODE )
      {
         getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrCode, strOut,false );
         strOut.strip();

         return true;
      }
      else if ( ColumnKey == ADDRESSLINE )
      {
         getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrLine1, str );
         str.strip();
         strOut = str;
         getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrLine2, str );
         str.strip();
         strOut += str;
         getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrLine3, str );
         str.strip();
         strOut += str;
         strOut +=I_(" ");
         getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::PostalCode, str );
         str.strip();
         strOut += str;
         return true;
      }
   }
   else if(lSubstituteId == ifds::ShareholderAddressHeadingVerifySet.getId() )
   {
      if(ColumnKey == ADDRESSCODE){
         getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, strOut,false );
         strOut.strip();
         return true;
      }
      else if( ColumnKey == ADDRESSCODEDESC ){

         DString strTemp1,strTemp2,strTemp3;
         getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrCode,strTemp1,false);
         strTemp1.strip();
         getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrCode,strTemp2);
         strTemp2.strip();
         if(strTemp1 == strTemp2 ) strOut = I_("");
         else	 strOut = strTemp2;
         return true;	
      }
   }

   return false;
}

//******************************************************************************************
bool BaseAddressBookDlg:: SetDataFromControl(
      UINT controlID,
      const DString &strValue,
      bool bFormatted,
      SEVERITY &sevRtn,
        int index
      )
{
   switch(controlID){
      case IDC_CMB_ENTITY_OUTPUT:
         sevRtn = NO_CONDITION;
         return true;
         break;
      default:
         break;
   }
   return false;
}

//*******************************************************************************************************************
bool BaseAddressBookDlg::GetDataForControl(UINT controlID,  
                                           DString &strValueOut, 
                                           bool bFormatted, 
                                           int index   ) const
{  
	DString  str;
	//int Index;
	//DSTComboBox*  pCombo;
	bool _bRet = false;
	switch(controlID){

   case IDC_SHAREHOLDER_REG:
			getParent()->getField(this, IFASTBP_PROC::SHAREHOLDER_LIST,ifds::Name2,strValueOut, bFormatted);
			_bRet = true;
			break;

/***************************
	case  IDC_EDT_ENTITY_ADDRESS_ID:
			getParent()->getField(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrId,strValueOut);
			strValueOut.stripLeading('0').stripLeading('+');
			_bRet = true;
			break;	
*************************/
 
	case  IDC_EDT_ENTITY_ADDRESS_CODE:
			getParent()->getField(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrCode,strValueOut,false);
			strValueOut.strip();
			//pCombo = dynamic_cast<DSTComboBox* >(GetDlgItem (IDC_EDT_ENTITY_ADDRESS_CODE) );
			//pCombo->ResetContent();
			//Index = pCombo->AddString(strValueOut.c_str());
			//pCombo->SetCurSel(Index);
			_bRet = true;
			break;


	case IDC_CMB_PREFECTURE:
			getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::CountryCode,strValueOut,false);
			strValueOut.strip();
			_bRet = true;
			break;

	//case IDC_CMB_ENTITY_COUNTRY:
	//		getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::Country,strValueOut,false);
	//		strValueOut.strip();
	//		_bRet = true;
	//		break;

	
	case IDC_TXT_ROLE:
	{
		int index = m_EntityName.GetCurSel();
		const DString *key =(const DString* )m_EntityName.GetItemData( index );
		const DString *pKey = &(getParent()->getFirstListItemKey(this,IFASTBP_PROC::ENTITY_LIST) );
		do
      {
			if ( *pKey == NULL_STRING )
            return true;
			if ( *key == *pKey )
         {
				getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType,
               strValueOut );
				strValueOut.strip();	
				_bRet = true;
				break;
			}
      } while ( *( pKey = &getParent()->getNextListItemKey( this, IFASTBP_PROC::ENTITY_LIST) )
         != EMPTY_STRING );
		break;
	}

	/*****************
	case IDC_CMB_CODE:
		if ( !IsShareholder() ){
				getParent()->getField(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrCode,strValueOut,true);
				strValueOut.strip();
				_bRet = true;
		}
		break;
		****************/

	case IDC_CMB_ENTITY_DEFAULT_ADDRESS:

		getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::AddrCode,strValueOut,false);


		break;

	case IDC_CMB_ENTITY_OUTPUT:
		_bRet = true;
		break;
	default:

		break;
	}
   return _bRet;
}

//***************************************************************************************************
void BaseAddressBookDlg::OnKillfocusEdtPostCode() 
{
   // TODO: Add your control notification handler code here
   LoadControl( IDC_EDT_POST_CODE );

}

//****************************************************************************************
void BaseAddressBookDlg::OnSelDefaultEntityAddress()
{
   DSTComboBox*	pCombo = dynamic_cast<DSTComboBox* >(GetDlgItem (IDC_CMB_ENTITY_DEFAULT_ADDRESS) );
   CString cstr;		
   int iSel = pCombo->GetCurSel( );
   pCombo->GetLBText(iSel,cstr);
   DString dstr = LPCTSTR( cstr );
   getParent()->setField(this,IFASTBP_PROC::ENTITY_LIST,ifds::AddrCode,dstr,false);
}

//************************************************************
bool BaseAddressBookDlg::doDisablePermCheckButton(UINT nID)
{
	if (nID == IDC_BTN_DELETE)
	{
		if ( !IsShareholder() )
		{
          bool bNewItem = dynamic_cast<AbstractProcess* >( getParent() )->isCurrentListItemNew( this, 
                              IFASTBP_PROC::ENTITY_ADDRESS_LIST);
          return bNewItem;
		}
		else
		//if( IsOverride() )
		{
		   DString strAddrCode, strIsRegAddrReadOnly;
		   getParent()->getField(this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, strAddrCode, false);
		   if (strAddrCode == I_("01"))
		   {   
			  getParent()->getField( this, ADDRLIT::REG_ADDR_READ_ONLY, strIsRegAddrReadOnly );
			  if (strIsRegAddrReadOnly == YES)
				 return true;
		   }
		}		
	}
	else if (nID == IDC_RB_OVERRIDE)
	{
		//checkgeneric control
		DString str;
		getParent()->getField( this, BF::NullContainerId, ifds::MailingByFundGroup, str,false );
		return(str.strip() != I_("Y"));
	}
	
   return false;
}

//****************************************************************************************************
bool BaseAddressBookDlg::doDisableControl(UINT nID, bool bIsNew)
{
   switch (nID)
   {
      case IDC_CMB_CODE:
      case IDC_CMB_SALUTATION:
      case IDC_EDT_SALUTATION:
      case IDC_EDT_NAME:
      case IDC_SHAREHOLDER_ADDRESS:
      case IDC_EDT_POST_CODE:
      case IDC_DTP_EFF_DATE:
      case IDC_DTP_STOP_DATE:
      case IDC_BTN_LOOKUP:
      case IDC_CB_SKIP_VAL:
      case IDC_CMB_RET_MAIL:
         return disableControlForAddress01();
         break;
      default: ;
   }
   return false;
}

//*****************************************************************************************************
bool BaseAddressBookDlg::disableControlForAddress01()
{
   bool blResult = false;

   DString strAddrCode, strIsRegAddrReadOnly;

   if ( IsShareholder() )
   {
      getParent()->getField(this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, strAddrCode, false);

      if (strAddrCode == I_("01"))
      {   
         getParent()->getField( this, ADDRLIT::REG_ADDR_READ_ONLY, strIsRegAddrReadOnly );

         if (strIsRegAddrReadOnly == YES)
         {
            blResult = true;
         }
      }
   }

   return( blResult );
}

//*******************************************************************************************************
bool  BaseAddressBookDlg::MailingPositionByAccount(const DString& AccountNumber)
{
	bool rtn = false;
	const DString* key;
	DString  strAccount;
	key = &getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACCOUNT_MAILING_LIST);
	if(*key == EMPTY_STRING ) return false;

	do
   {
		getParent()->getField(this, IFASTBP_PROC::ACCOUNT_MAILING_LIST, ifds::AccountNum, strAccount);
		strAccount.strip();
		if ( *key == EMPTY_STRING )
         break;
		if ( strAccount == AccountNumber )
      {
			getParent()->setCurrentListItem(this,IFASTBP_PROC::ACCOUNT_MAILING_LIST,*key);	
			return true;
		}		
   } while ( *( key = &getParent()->getNextListItemKey( this, 
                           IFASTBP_PROC::ACCOUNT_MAILING_LIST ) ) != EMPTY_STRING );
		
	return rtn;
} 

//*******************************************************************************************************
void BaseAddressBookDlg::FillMailAddressList()
{
   if( IsShareholder() )
   {
      if( IsOverride() ) OnRbOverride();
      else OnRbDefault();
   }
   else
   {
      if ( !m_dstrAccountNum.empty() && !isAccountOwner() )
      {
         DSTGridWnd *pGrid = GetGrid( IDC_LV_ENTITY_MAILING );
         pGrid->reLoadGrid();
      }
   }
}

//*******************************************************************************************************
void BaseAddressBookDlg::FillAcctMailOverrideList()
{
}

//*******************************************************************************************************
void BaseAddressBookDlg::ClearMailingList()
{
}

//********************************************************************************************************
void BaseAddressBookDlg::setupShareholderMailing()
{
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Register"),					new Mailing(BFFieldId(ifds::RegAddr),			BFFieldId(ifds::RegOnHold),		BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::RegSuppress	),	BFFieldId(ifds::RegWaive	),		BFFieldId(ifds::RegMail	),		BFFieldId(ifds::RegFax	),		BFFieldId(ifds::RegCD	),		BFFieldId(ifds::RegEmail	),BFFieldId(ifds::RegEpost),BFFieldId(ifds::RegAuth),BFFieldId(ifds::StmtFrequencyDisabled) )));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("DividendConfirmation"),		new Mailing(BFFieldId(ifds::DivConfAddr),		BFFieldId(ifds::DivConfOnHold),	BFFieldId(ifds::SADivConfCode),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::DivConfSuppress),	BFFieldId(ifds::DivConfWaive),		BFFieldId(ifds::DivConfMail),	BFFieldId(ifds::DivConfFax),	BFFieldId(ifds::DivConfCD),		BFFieldId(ifds::DivConfEmail),BFFieldId(ifds::DivConfEpost),BFFieldId(ifds::DivConfAuth),BFFieldId(ifds::StmtFrequencyDisabled) )));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("DividendCheque"),				new Mailing(BFFieldId(ifds::DivChqAddr),		BFFieldId(ifds::DivChqOnHold),	BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::DivChqSuppress),	BFFieldId(ifds::DivChqWaive),		BFFieldId(ifds::DivChqMail),	BFFieldId(ifds::DivChqFax),		BFFieldId(ifds::DivChqCD),		BFFieldId(ifds::DivChqEmail),BFFieldId(ifds::DivChqEpost),BFFieldId(ifds::DivChqAuth),BFFieldId(ifds::StmtFrequencyDisabled)	  )));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Confirmation"),				new Mailing(BFFieldId(ifds::TxnConfAddr),		BFFieldId(ifds::TxnConfOnHold),	BFFieldId(ifds::SATxnConfCode),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::TxnConfSuppress),	BFFieldId(ifds::TxnConfWaive),		BFFieldId(ifds::TxnConfMail),	BFFieldId(ifds::TxnConfFax),	BFFieldId(ifds::TxnConfCD),		BFFieldId(ifds::TxnConfEmail),BFFieldId(ifds::TxnConfEpost),BFFieldId(ifds::TxnConfAuth),BFFieldId(ifds::StmtFrequencyDisabled) )));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("AdditionalConfirmation"),		new Mailing(BFFieldId(ifds::DupConfAddr),		BFFieldId(ifds::DupConfOnHold),	BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::DupConfCopies),	 BFFieldId(ifds::DupConfSuppress),	BFFieldId(ifds::DupConfWaive),		BFFieldId(ifds::DupConfMail),	BFFieldId(ifds::DupConfFax),	BFFieldId(ifds::DupConfCD),		BFFieldId(ifds::DupConfEmail),BFFieldId(ifds::DupConfEpost),BFFieldId(ifds::DupConfAuth),BFFieldId(ifds::StmtFrequencyDisabled)			)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Statements"),					new Mailing(BFFieldId(ifds::StmtAddr),			BFFieldId(ifds::StmtOnHold),	BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::StmtSuppress),		BFFieldId(ifds::StmtWaive),			BFFieldId(ifds::StmtMail),		BFFieldId(ifds::StmtFax),		BFFieldId(ifds::StmtCD),		BFFieldId(ifds::StmtEmail),BFFieldId(ifds::StmtEpost),BFFieldId(ifds::StmtAuth),BFFieldId(ifds::StmtFrequency)				)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("AdditionalStatement"),		new Mailing(BFFieldId(ifds::DupStmtAddr),		BFFieldId(ifds::DupStmtOnHold),	BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::DupStmtCopies),	 BFFieldId(ifds::DupStmtSuppress),	BFFieldId(ifds::DupStmtWaive),		BFFieldId(ifds::DupStmtMail),	BFFieldId(ifds::DupStmtFax),	BFFieldId(ifds::DupStmtCD),		BFFieldId(ifds::DupStmtEmail),BFFieldId(ifds::DupStmtEpost),BFFieldId(ifds::DupStmtAuth),BFFieldId(ifds::StmtFrequencyDisabled)			)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Certificate"),				new Mailing(BFFieldId(ifds::CertAddr),			BFFieldId(ifds::CertOnHold),	BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::CertSuppress),		BFFieldId(ifds::CertWaive),			BFFieldId(ifds::CertMail),		BFFieldId(ifds::CertFax),		BFFieldId(ifds::CertCD),		BFFieldId(ifds::CertEmail),BFFieldId(ifds::CertEpost),BFFieldId(ifds::CertAuth),BFFieldId(ifds::StmtFrequencyDisabled)				)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("TaxReceipt"),					new Mailing(BFFieldId(ifds::TaxAddr),			BFFieldId(ifds::TaxOnHold),		BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::TaxSuppress),		BFFieldId(ifds::TaxWaive),			BFFieldId(ifds::TaxMail),		BFFieldId(ifds::TaxFax),		BFFieldId(ifds::TaxCD),			BFFieldId(ifds::TaxEmail),BFFieldId(ifds::TaxEpost),BFFieldId(ifds::TaxAuth),BFFieldId(ifds::StmtFrequencyDisabled)				)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Letters"),					new Mailing(BFFieldId(ifds::LetAddr),			BFFieldId(ifds::LetOnHold),		BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::LetSuppress),		BFFieldId(ifds::LetWaive),			BFFieldId(ifds::LetMail),		BFFieldId(ifds::LetFax),		BFFieldId(ifds::LetCD),			BFFieldId(ifds::LetEmail),BFFieldId(ifds::LetEpost),BFFieldId(ifds::LetAuth),BFFieldId(ifds::StmtFrequencyDisabled)				)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("BeneficialOwner"),			new Mailing(BFFieldId(ifds::BenAddr),			BFFieldId(ifds::BenOnHold),		BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::BenSuppress),		BFFieldId(ifds::BenWaive),			BFFieldId(ifds::BenMail),		BFFieldId(ifds::BenFax),		BFFieldId(ifds::BenCD),			BFFieldId(ifds::BenEmail),BFFieldId(ifds::BenEpost),BFFieldId(ifds::BenAuth),BFFieldId(ifds::StmtFrequencyDisabled)     )));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("NonFinancialConfirm"),		new Mailing(BFFieldId(ifds::NFCAddr),			BFFieldId(ifds::NFConHold),		BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::NFConfSuppress),	BFFieldId(ifds::NFConfWaive),		BFFieldId(ifds::NFConfMail),	BFFieldId(ifds::NFConfFax),		BFFieldId(ifds::NFConfCD),		BFFieldId(ifds::NFConfEmail),BFFieldId(ifds::NFConfEpost),BFFieldId(ifds::NFConAuth),BFFieldId(ifds::StmtFrequencyDisabled)			)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("ContractNotes"),				new Mailing(BFFieldId(ifds::ContrAddr),			BFFieldId(ifds::ContrHold),		BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::ContrSuppress),	BFFieldId(ifds::ContrWaive),		BFFieldId(ifds::ContrMail),		BFFieldId(ifds::ContrFax),		BFFieldId(ifds::ContrCD),		BFFieldId(ifds::ContrEmail),BFFieldId(ifds::ContrEPost),BFFieldId(ifds::ContrAuth),BFFieldId(ifds::StmtFrequencyDisabled)				)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("AnnualReports"),				new Mailing(BFFieldId(ifds::AnnlRptsAddr),		BFFieldId(ifds::AnnlRptsHold),	BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::AnnlRptsSuppress),	BFFieldId(ifds::AnnlRptsWaive),		BFFieldId(ifds::AnnlRptsMail),	BFFieldId(ifds::AnnlRptsFax),	BFFieldId(ifds::AnnlRptsCD),	BFFieldId(ifds::AnnlRptsEmail),BFFieldId(ifds::AnnlRptsEpost),BFFieldId(ifds::AnnlRptsAuth),BFFieldId(ifds::StmtFrequencyDisabled)			)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("SemiAnnualReport"),			new Mailing(BFFieldId(ifds::SemiAnnualAddr),	BFFieldId(ifds::SemiAnnualOnHold),BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::SemiAnnualSuppress),BFFieldId(ifds::SemiAnnualWaive),	BFFieldId(ifds::SemiAnnualMail),BFFieldId(ifds::SemiAnnualFax),	BFFieldId(ifds::SemiAnnualCD),	BFFieldId(ifds::SemiAnnualEmail),BFFieldId(ifds::SemiAnnualEpost),BFFieldId(ifds::SmAnnlRptsAuth),BFFieldId(ifds::StmtFrequencyDisabled)		)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Prospectuses"),				new Mailing(BFFieldId(ifds::ProspAddr),			BFFieldId(ifds::ProspHold),		BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::ProspSuppress),	BFFieldId(ifds::ProspWaive),		BFFieldId(ifds::ProspMail),		BFFieldId(ifds::ProspFax),		BFFieldId(ifds::ProspCD),		BFFieldId(ifds::ProspEmail),BFFieldId(ifds::ProspEpost),BFFieldId(ifds::ProspAuth),BFFieldId(ifds::StmtFrequencyDisabled)				)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("ContributionReceipt"),		new Mailing(BFFieldId(ifds::ContributionAddr),	BFFieldId(ifds::ContributionOnHold),		BFFieldId(ifds::NullFieldId),		BFFieldId(ifds::NullFieldId),	 BFFieldId(ifds::ContributionSuppress),	BFFieldId(ifds::ContributionWaive), BFFieldId(ifds::ContributionMail),		BFFieldId(ifds::ContributionFax),BFFieldId(ifds::ContributionCD),		BFFieldId(ifds::ContributionEmail),	   BFFieldId(ifds::ContributionEpost),BFFieldId(ifds::ContributionAuth),BFFieldId(ifds::StmtFrequencyDisabled)			)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("AnnualMRFP"),                new Mailing(BFFieldId(ifds::AnnlMRFPAddr),      BFFieldId(ifds::AnnlMRFPHold),          BFFieldId(ifds::NullFieldId),    BFFieldId(ifds::NullFieldId),  BFFieldId(ifds::AnnlMRFPSuppress),       BFFieldId(ifds::AnnlMRFPWaive	),	   BFFieldId(ifds::AnnlMRFPMail),         BFFieldId(ifds::AnnlMRFPFax),	   BFFieldId(ifds::AnnlMRFPCD),        BFFieldId(ifds::AnnlMRFPEmail),	      BFFieldId(ifds::AnnlMRFPEpost),BFFieldId(ifds::AnnlMRFPAuth),BFFieldId(ifds::StmtFrequencyDisabled)   	)));
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("SmAnnlMRFP"),              new Mailing(BFFieldId(ifds::SmAnnlMRFPAddr),      BFFieldId(ifds::SmAnnlMRFPHold),        BFFieldId(ifds::NullFieldId),    BFFieldId(ifds::NullFieldId),  BFFieldId(ifds::SmAnnlMRFPSuppress),     BFFieldId(ifds::SmAnnlMRFPWaive	),	BFFieldId(ifds::SmAnnlMRFPMail),       BFFieldId(ifds::SmAnnlMRFPFax),	BFFieldId(ifds::SmAnnlMRFPCD),      BFFieldId(ifds::SmAnnlMRFPEmail),	   BFFieldId(ifds::SmAnnlMRFPEpost),BFFieldId(ifds::SmAnnlMRFPAuth),BFFieldId(ifds::StmtFrequencyDisabled)   	)));
}

//**********************************************************************************************************	
void BaseAddressBookDlg::clearMailmap()		
{
	MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      delete (*iter).second;
      ++iter;
   }
   _mailmap.clear();	
}

//****************************************************************************************
void BaseAddressBookDlg::getComboStringForAddressCode(DString& dstrList)
{
	dstrList = NULL_STRING;
	
	const DString *pCurKey = &( getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ADDRESSES_LIST ) );
	const DString *pKey=&( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ADDRESSES_LIST ));

	if ( (*pKey) != NULL_STRING )
   {
		do
      {
			DString dstr;
			getParent()->getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, dstr,false );
			dstr.strip();
			if ( dstr != I_("") )
         {
			 dstrList += dstr + I_("=") + dstr + I_(";");
			}
      } while (*(pKey=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::ADDRESSES_LIST ))) != NULL_STRING);

		if ( *pCurKey != NULL_STRING )
			getParent()->setCurrentListItem( this, IFASTBP_PROC::ADDRESSES_LIST, *pCurKey );
	}
}

//***************************************************************************************
void BaseAddressBookDlg::GetCellProperties( UINT ctrlId, 
                                            const DString &rowKey, 
                                            const DString &colKey, 
                                            BFContainerId& idContainer,
                                            BFFieldId &idField,
                                            DString& ListItemKey,
                                            int& nCellState,
                                            UINT& cellCtrlType, 
                                            int& nCtrlInitMode,
                                            BFFieldId &idSubstitution,
                                            DString& combolist, 
                                            DString& mask,
                                            int& nComboSortingMode,
                                            DString& dstrAllowedChar)
{
   bool hasUpdatePerm = hasUpdatePermission(UAF::ADDRESS_BOOK);
   dstrAllowedChar = NULL_STRING;
   if( ctrlId == IDC_LV_MAIL_ASSIGN )
   {
      if( colKey  == _T("AddressCode") )
      {
         idContainer          = IFASTBP_PROC::ACCOUNT_MAILING_LIST;
         nCellState           = hasUpdatePerm ? 
                                DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
                                DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType         = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode        = DSTGridWnd::COMBO_INIT_MODE::USE_IDI_STRING;
         combolist            = m_dstrAddrCodeList;
         MAIL_MAP_ITER iter   = _mailmap.find(rowKey);
         if( iter != _mailmap.end() )
         {
            idField = (*iter).second->getAddrCode();
         }
         else 
         {
            assert(0);
         }
      }
      else if( colKey  == _T("Hold") )
      {
         idContainer          = IFASTBP_PROC::ACCOUNT_MAILING_LIST;
         nCellState           = hasUpdatePerm ? 
                                DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
                                DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType         = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode        = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution       = ifds::Yes_NO;
         MAIL_MAP_ITER iter   = _mailmap.find(rowKey);
         if( iter != _mailmap.end() )
         {
            idField = (*iter).second->getHold();
         }
         else 
         {
            assert(0);
         }
      }
      else if ( colKey  == _T("Authorization" )  )
      {
         idContainer          = IFASTBP_PROC::ACCOUNT_MAILING_LIST;
         nCellState           = hasUpdatePerm ? 
                                DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
                                DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType         = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode        = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         MAIL_MAP_ITER iter   = _mailmap.find(rowKey);
         if( iter != _mailmap.end() )
         {
            idField = (*iter).second->getAuthorization();
            idSubstitution = idField;
         }
         else 
         {
            assert(0);
         }
      }
      else if ( colKey  == _T("Frequency" )  )  
      {
         DString stmtfreqlist;
         DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
         pdstcWorkSession->getOption( ifds::StmtFreqList,stmtfreqlist, getParent()->getDataGroupId(), false );

         idContainer       = IFASTBP_PROC::ACCOUNT_MAILING_LIST;
         idField           = ifds::StmtFrequencyDisabled;
         idSubstitution    = idField;
         /*nCellState           = hasUpdatePerm ? 
         DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;*/
         cellCtrlType      =  GX_IDS_CTRL_EDIT;
         if( !stmtfreqlist.empty() ) 
         {
            if ( rowKey == _T("Statements" ) )
            {	
               cellCtrlType      =  GX_IDS_CTRL_CBS_DROPDOWNLIST;
            }
            else
            {
               cellCtrlType      =  GX_IDS_CTRL_EDIT;
            }

            nCtrlInitMode        = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
            MAIL_MAP_ITER iter   = _mailmap.find(rowKey);

            if( iter != _mailmap.end() )
            {
               idField = (*iter).second->getInvstFrequency();
               idSubstitution = idField;
            }

            else 
            {
               assert(0);
            }
         }
      }
      else if( colKey == _T("ServiceAgent") )
      {
         MAIL_MAP_ITER iter = _mailmap.find(rowKey);
         if( iter != _mailmap.end() )
         {
            idField = (*iter).second->getAgent();
            if(idField != ifds::NullFieldId ){
               idContainer    = IFASTBP_PROC::ACCOUNT_MAILING_LIST;
               nCellState     = DSTGridWnd::CELL_STATE::READ_ONLY;
               cellCtrlType   = GX_IDS_CTRL_EDIT;
               }
            else {
               nCellState     = DSTGridWnd::CELL_STATE::SKIPPED;
            }
         }
         else 
         {
            assert(0);
         } 
      }
      else if( colKey == _T("NumberCopies")  )
      {
         MAIL_MAP_ITER iter = _mailmap.find(rowKey);
         if( iter != _mailmap.end() )
         {
            idField = (*iter).second->getCopies();	
            if(idField != ifds::NullFieldId ){
               idContainer    = IFASTBP_PROC::ACCOUNT_MAILING_LIST;
               nCellState     = hasUpdatePerm ? 
                                DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
                                DSTGridWnd::CELL_STATE::READ_ONLY;
               cellCtrlType   = GX_IDS_CTRL_EDIT;
            }
            else {
               nCellState     = DSTGridWnd::CELL_STATE::SKIPPED;
            }
         }
         else 
         {
            assert(0);
         }
      }
      else if( colKey == SUPPRESS || colKey == WAIVEPAPER || colKey == EPOST || 
               colKey == FAX      || colKey == CD         || colKey == EMAIL )
      {
         MAIL_MAP_ITER iter = _mailmap.find(rowKey);
         if( iter != _mailmap.end() )
         {
            if(colKey == SUPPRESS )	idField = (*iter).second->getSuppress();
            else if(colKey == WAIVEPAPER) idField = (*iter).second->getWaive();
            //else if(colKey == MAIL ) idField = (*iter).second->getMail();
            else if(colKey == FAX ) idField = (*iter).second->getFax();
            else if(colKey == CD ) idField = (*iter).second->getCD();
            else if(colKey == EMAIL ) idField = (*iter).second->getEmail();
            else if(colKey == EPOST ) idField = (*iter).second->getEpost();

            if(idField != ifds::NullFieldId ){
               idContainer       = IFASTBP_PROC::ACCOUNT_MAILING_LIST;
               nCellState        = hasUpdatePerm ? 
                                   DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
                                   DSTGridWnd::CELL_STATE::READ_ONLY;
               cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;	
               nCtrlInitMode     = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
               idSubstitution    = idField;
            }
            else {
               nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;
            }
         }
      }
      else if( colKey == MAIL ){
         MAIL_MAP_ITER iter = _mailmap.find(rowKey);
         if( iter != _mailmap.end() )
         {
            idField = (*iter).second->getMail();
            if(idField != ifds::NullFieldId ){
               idContainer       = IFASTBP_PROC::ACCOUNT_MAILING_LIST;
               nCellState        = hasUpdatePerm ? 
                                   DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
                                   DSTGridWnd::CELL_STATE::READ_ONLY;
               cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;	
               nCtrlInitMode     = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;

               BFFieldId mailOption = ifds::Yes_NO;
               AddressProcess* pProcess = 
                  dynamic_cast<AddressProcess*>(getParent());
               if(pProcess)
               {
                  pProcess->getMailOptionSubstitutionByDocKey (rowKey,
                                                               mailOption);
                  idSubstitution    = mailOption;
               }
            } else {
               nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;
            }
         }
      }
      else{
         nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;  
      }
   }
   else if (ctrlId == IDC_LV_ENTITY_MAILING )
   {
      //entityMailing
      if( colKey == _T("DocumentType") )
      {
         idField           = ifds::DocumentType;
         idContainer       = IFASTBP_PROC::ENTITY_MAILING_LIST;
         nCellState        = hasUpdatePerm ? 
                             DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
                             DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         idSubstitution    = ifds::DocumentType;
      }
      else if( colKey == _T( "EntityAddrCode" ) )
      {
         idField           = ifds::EntityAddrCode;
         idContainer       = IFASTBP_PROC::ENTITY_MAILING_LIST;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode     = DSTGridWnd::COMBO_INIT_MODE::USE_IDI_STRING;
         combolist         = m_dstrEntityAddrCodeList;  
      }
      else if(colKey == _T( "Suppress" ))
      {
         idField           = ifds::Suppress;
         idContainer       = IFASTBP_PROC::ENTITY_MAILING_LIST;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState        = hasUpdatePerm ? 
                             DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
                             DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode     = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution    = ifds::Suppress; 
      }
      else if(colKey == _T("Consent") )
      {
         idField           = ifds::Consent;
         idContainer       = IFASTBP_PROC::ENTITY_MAILING_LIST;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState        = hasUpdatePerm ? 
                             DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
                             DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode     = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution    = ifds::Consent;  
      }
      else if( colKey == _T("DeliveryOption") )
      {
         nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;

         //idField = ifds::DeliveryOption,
         //idContainer = IFASTBP_PROC::ENTITY_MAILING_LIST;
         //cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         //nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         //idSubstitution = ifds::DeliveryOption;  
      }

      else if( colKey == _T("Mail") )
      {
         idField = ifds::Mail,
            idContainer = IFASTBP_PROC::ENTITY_MAILING_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if( colKey == _T("Fax") )		  
      {
         idField = ifds::Fax,
            idContainer = IFASTBP_PROC::ENTITY_MAILING_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if( colKey == _T("CD") )		  
      {
         idField = ifds::CD,
            idContainer = IFASTBP_PROC::ENTITY_MAILING_LIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if( colKey == _T("Email") )		  
      {
         idField = ifds::LEmail,
            idContainer = IFASTBP_PROC::ENTITY_MAILING_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if (colKey == _T("Epost"))
      {
         idField = ifds::EPost,
            idContainer = IFASTBP_PROC::ENTITY_MAILING_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      } 
      else if (colKey == _T("OnHold"))
      {
         idField = ifds::OnHold,
            idContainer = IFASTBP_PROC::ENTITY_MAILING_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      } 
      else if (colKey == _T("AuthCode"))
      {
         idField = ifds::AuthCode,
            idContainer = IFASTBP_PROC::ENTITY_MAILING_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::AuthCode;  
      } 
      else if( colKey == _T("FundGroup") )
      {
         nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;
      }
   }
   else if( ctrlId == IDC_LV_ACCT_MAILING_OVERRIDE )
   {
      //Add code when exiting record, set documenttype and fundgroup readonly
      bool existing = true;
      AbstractProcess * pParentProcess = dynamic_cast<AbstractProcess *>(getParentProcess());
      if ( pParentProcess->isCurrentListItemNew(this, IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST) )
      {
         existing  = false;
      }

      if( colKey == _T("DocumentType") )
      {
         idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         idField     = ifds::DocumentType;
         if(existing == true) 
         {
            nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
            cellCtrlType = GX_IDS_CTRL_EDIT;
         }
         else 
         {
            nCellState  = hasUpdatePerm ? 
               DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
            DSTGridWnd::CELL_STATE::READ_ONLY;
            cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
            nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
            idSubstitution = ifds::DocumentType;
         }
      }
      else if( colKey == _T("FundGroup") )
      {
         idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         idField     = ifds::FundGroup;
         if(existing == true) 
         {
            nCellState  = DSTGridWnd::CELL_STATE::READ_ONLY;
            cellCtrlType = GX_IDS_CTRL_EDIT;
         }
         else 
         {
            nCellState  = hasUpdatePerm ? 
               DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
            DSTGridWnd::CELL_STATE::READ_ONLY;
            cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
            nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
            idSubstitution = ifds::FundGroup;
         }
      }
      else if( colKey == _T( "EntityAddrCode" ) )	
      {
         idField = ifds::EntityAddrCode;
         idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_IDI_STRING;
         combolist = m_dstrOverrideAddrCodeList;  
      }
      else if(colKey == _T( "Suppress" )	)
      {
         idField = ifds::Suppress;
         idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Suppress;  
      }
      else if( colKey == _T("Mail") )		  
      {
         idField = ifds::Mail,
            idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if( colKey == _T("Fax") )		  
      {
         idField = ifds::Fax,
            idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if( colKey == _T("CD") )		  
      {
         idField = ifds::CD,
            idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if( colKey == _T("Email") )		  
      {
         idField = ifds::LEmail,
            idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if (colKey == _T("Epost"))
      {
         idField = ifds::EPost,
            idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      } 
      else if(colKey == _T("Consent") )
      {
         idField = ifds::Consent;
         idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if(colKey == _T("OnHold") )
      {
         idField = ifds::OnHold;
         idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Consent;  
      }
      else if(colKey == _T("AuthCode") )
      {
         idField = ifds::AuthCode;
         idContainer = IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCellState  = hasUpdatePerm ? 
            DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY:
         DSTGridWnd::CELL_STATE::READ_ONLY;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::AuthCode;  
      }
      else
         nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;  
   }
}

//***********************************************************************************************************
bool BaseAddressBookDlg::HideGridRowColumn(DString& dstrTag)
{
   if( m_DisplayCode.GetCurSel() == DISPLAYCODESELECT )
   {
      if(IsShareholder() )
      {
         BFFieldId idField;
         MAIL_MAP_ITER iter = _mailmap.find(dstrTag);
         if( iter != _mailmap.end() )
         {
            idField = (*iter).second->getAddrCode();
            DString dstrAddr,dstrAddrCode;
            getParent()->getField(this,IFASTBP_PROC::ACCOUNT_MAILING_LIST,idField,dstrAddr,false);
            getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrCode,dstrAddrCode,false);
            dstrAddr.strip();
            dstrAddrCode.strip();
            if(dstrAddr != dstrAddrCode) return true;
         }
      }
   }
   if(IsShareholder() /*&& !IsOverride()*/)
   {
      if(dstrTag == SUPPRESS || dstrTag == WAIVEPAPER || dstrTag == MAIL || 
         dstrTag == FAX || dstrTag == CD || 
         dstrTag == EMAIL || dstrTag == EPOST )
      {
         DString dstrOption;
         getParent()->getField(this, BF::NullContainerId, ifds::OPDeliveryOption,dstrOption,false);
         dstrOption.strip();
         if(dstrOption == NO ) return true;
         else return HideMailOption(dstrTag );
      }
   }
   else  // entity mailing
   {
      if(dstrTag == I_("FundGroup") /*|| dstrTag == I_("Consent")*/ )
      {
            return true;
      } 
      else if(dstrTag == SUPPRESS || dstrTag == WAIVEPAPER || dstrTag == MAIL || 
              dstrTag == FAX || dstrTag == CD || 
              dstrTag == EMAIL || dstrTag == EPOST )
      {
         DString dstrOption;
         getParent()->getField(this, BF::NullContainerId, ifds::OPDeliveryOption,dstrOption,false);
         dstrOption.strip();
         if(dstrOption == NO ) return true;
         else return HideMailOption(dstrTag );		
      }

   }

   return false;
}

//********************************************************************************************************
bool BaseAddressBookDlg::HideMailOption(DString& dstrTag )
{
   DString dstrDelMethod;
   getParent()->getField(this, BF::NullContainerId, ifds::OPDeliveryMethods,dstrDelMethod,false);
   dstrDelMethod.strip();
   bool bFind = true;
   if(dstrTag == MAIL) bFind = (dstrDelMethod.find(I_("01") )!= DString::npos );
   else if(dstrTag == EMAIL ) bFind = (dstrDelMethod.find(I_("02") ) != DString::npos );
   else if(dstrTag == FAX ) bFind = (dstrDelMethod.find(I_("03") ) != DString::npos );
   else if(dstrTag == CD ) bFind = (dstrDelMethod.find(I_("04") ) != DString::npos );
   else if(dstrTag == EPOST ) bFind = (dstrDelMethod.find(I_("05") ) != DString::npos );

   else if(dstrTag == WAIVEPAPER )
   {
      DString dstrWaive;
      getParent()->getField(this, BF::NullContainerId, ifds::CnsntToWaive,dstrWaive,false);
      if(dstrWaive == NO )bFind = false;			
   }
   return !bFind;
}

//********************************************************************************************************
bool BaseAddressBookDlg::GridControlFilter( UINT ctrlId, const DString &rowKey )
{
   if(ctrlId == IDC_LV_ENTITY_MAILING )
   {

      DString dstrDocType,dstrDocTypeSel;
      const DString *pCurKey = &getParent()->getCurrentListItemKey(this, IFASTBP_PROC::ENTITY_MAILING_LIST);			
      DSTComboBox* pCombo = static_cast<DSTComboBox* >(GetDlgItem(IDC_CMB_ENTITY_OUTPUT) );
      if(pCombo )
      {
         int index = pCombo->GetCurSel();
         if ( index == CB_ERR ){
            dstrDocTypeSel = NULL_STRING;
            return true;
         }
         else
         {
            CString cstr;
            pCombo->GetLBText( index, cstr );
            CString cstrAll;
            cstrAll.LoadString( TXT_ALL );
            if(cstr == cstrAll ) return true;
            const DString *pKey=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::ENTITY_MAILING_LIST ));
            if ( *pKey != NULL_STRING )
            {
               do
               {
                  DString str,strDes;
                  getParent()->getField( this, IFASTBP_PROC::ENTITY_MAILING_LIST, 
                     ifds::DocumentType, str,false );
                  getParent()->getField( this, IFASTBP_PROC::ENTITY_MAILING_LIST, 
                     ifds::DocumentType, strDes,true );
                  str.strip(); strDes.strip();
                  if(strDes.c_str() == cstr){
                     dstrDocTypeSel = 	str;
                     break;
                  }

               }while ( *( pKey = &( getParent()->getNextListItemKey( this, 
                  IFASTBP_PROC::ENTITY_MAILING_LIST ))) != NULL_STRING);
            }

            if ( *pCurKey != NULL_STRING )
               getParent()->setCurrentListItem(this, IFASTBP_PROC::ENTITY_MAILING_LIST, *pCurKey);						
         }
      }	
      if(*pCurKey!= NULL_STRING)
         getParent()->getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::DocumentType,dstrDocType,false);
      dstrDocType.strip();
      if(dstrDocType != dstrDocTypeSel) return false;		
   }
   return true;
}

//*********************************************************************************************************
/*
bool BaseAddressBookDlg::isDemoMode()
{
   I_CHAR *rpEnv = NULL;
   rpEnv = i_getenv( STUB_MODE );    // Can return NULL pointer if no variable
   if( rpEnv && !i_strcmp( rpEnv, OFFLINE ) )
      return true;
   else
      return false;
}
*/

//**********************************************************************************************************
void BaseAddressBookDlg::OnBtnEntityMailAdd()
{
   if(!IsShareholder())
      AddToGridControl( IDC_LV_ENTITY_MAILING );
   else if( IsOverride() )
      AddToGridControl( IDC_LV_ACCT_MAILING_OVERRIDE );
}

//***********************************************************************************************************
void BaseAddressBookDlg::OnBtnEntityMailDel()
{
   if(!IsShareholder())
      DeleteFromGridControl( IDC_LV_ENTITY_MAILING );
   else if( IsOverride() )
      DeleteFromGridControl( IDC_LV_ACCT_MAILING_OVERRIDE );
}

//**********************************************************************************************************
//iPos----0 based

DString BaseAddressBookDlg::getMailOption(BFFieldId& lFieldId, int iPos, bool bFormated		)
{
   DString dstrValue,retValue;
   getParent()->getField(this,IFASTBP_PROC::ACCOUNT_MAILING_LIST,lFieldId,dstrValue,false);
   dstrValue.stripAll();
   retValue = dstrValue.left(iPos + 1);
   retValue = retValue.right(1);

   if(bFormated)  // to do unformat it
   {
      DString pdstrSubst; 
      const BFProperties * pBFProp = 
         getParent()->getFieldAttributes(this, IFASTBP_PROC::ACCOUNT_MAILING_LIST, lFieldId );
      if( pBFProp ){
         DString strKey,strValue; 
         pBFProp->getSubstituteValues(pdstrSubst);
         I_CHAR* iStringPtr = const_cast < I_CHAR* > ( pdstrSubst.c_str());
         while( *iStringPtr != 0 )
         {
            iStringPtr = parseIdiString( iStringPtr, strKey, strValue );
            if ( retValue == strKey )
            {
               retValue = strValue;
               break;

            }
         }
      }	
   }
   return retValue;
}

//***********************************************************************************************************
void BaseAddressBookDlg::setMailOption(BFFieldId& lFieldId,int iPos,const DString& inValue,bool bFormated)
{
   DString dstrInValue(inValue);	
   if(bFormated)  // to do unformat it
   {
      DString pdstrSubst; 
      const BFProperties * pBFProp = getParent()->getFieldAttributes(this, IFASTBP_PROC::ACCOUNT_MAILING_LIST, ifds::Yes_NO );
      if( pBFProp ){
         DString strKey,strValue; 
         pBFProp->getSubstituteValues(pdstrSubst);
         I_CHAR* iStringPtr = const_cast < I_CHAR* > ( pdstrSubst.c_str());
         while( *iStringPtr != 0 )
         {
            iStringPtr = parseIdiString( iStringPtr, strKey, strValue );
            if ( inValue == strValue )
            {
               dstrInValue = strKey;
               break;

            }
         }
      }	
   }
   DString dstrValue,dstrLeft,dstrRight,dstrOldValue;
   getParent()->getField(this,IFASTBP_PROC::ACCOUNT_MAILING_LIST,lFieldId,dstrOldValue,false);
   dstrOldValue.stripLeading().stripTrailing();	
   dstrLeft = dstrOldValue.left(iPos);
   int nRight = dstrOldValue.length()-iPos - 1;
   if( nRight > 0 )
      dstrRight = dstrOldValue.right(nRight);
   dstrValue = dstrLeft + dstrInValue + dstrRight;
   if(dstrValue != dstrOldValue ){	
      getParent()->setField(this,IFASTBP_PROC::ACCOUNT_MAILING_LIST,lFieldId,dstrValue,false);
   }
}

//************************************************************************************************************
bool BaseAddressBookDlg::GetCellValue( UINT ctrlId,
                                       const DString &rowKey,
                                       const DString &colKey,
                                       DString &strOut,
                                       bool bFormatted)

{
   if(ctrlId == IDC_LV_ENTITY_MAILING)
   {
      if( colKey == _T( "AddrCode" ) )
      {
         getParent()->getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::EntityAddrCode,strOut,false);
         return true;
      }	
   }
   else if(ctrlId == IDC_LV_MAIL_ASSIGN )
   {

/*     MAIL_MAP_ITER iter = _mailmap.find(rowKey);
      if( iter != _mailmap.end() )
      {
         BFFieldId idField;
         idField = (*iter).second->getMailOption();	
         if(idField != ifds::NullFieldId ){
            //ACCOUNT_MAILING_LIST;

            if( colKey == SUPPRESS)
            {
               strOut = getMailOption(idField, 0,bFormatted);
               return true;
            }
            else if( colKey == WAIVEPAPER)
            {
               strOut = getMailOption(idField, 1,bFormatted);
               return true;
            }
            else if( colKey == MAIL)
            {
               strOut = getMailOption(idField, 2,bFormatted);
               return true;
            }
            else if( colKey == CD )
            {
               strOut = getMailOption(idField, 4,bFormatted);
               return true;
            }
            else if( colKey == EMAIL )
            {
               strOut = getMailOption(idField, 5,bFormatted);
               return true;
            }
            else if( colKey == FAX )
            {
               strOut = getMailOption(idField, 3,bFormatted);
               return true;
            }


         }
      }*/
   }
   return false;
}

//*******************************************************************************************
bool BaseAddressBookDlg::SetCellValue( UINT ctrlId,
                                       const DString &rowKey,
                                       const DString &colKey,
                                       const DString &strIn,
                                       bool bFormated,
                                       SEVERITY &sevRtn)
{
	if(ctrlId == IDC_LV_MAIL_ASSIGN )
	{
/*
	  	MAIL_MAP_ITER iter = _mailmap.find(rowKey);
	   if( iter != _mailmap.end() )
		{
			BFFieldId idField;
			idField = (*iter).second->getMailOption();	
			if(idField != ifds::NullFieldId ){
  						 //ACCOUNT_MAILING_LIST;								
		
				if( colKey == SUPPRESS)
				{				
					setMailOption(idField,0,strIn,bFormated);
					return true;				
				}
				else if( colKey == WAIVEPAPER)
				{
					setMailOption(idField,1,strIn,bFormated);
					return true;				
				}
				else if( colKey == MAIL)
				{
					setMailOption(idField,2,strIn,bFormated);
					return true;
				}
				else if( colKey == FAX )
				{
					setMailOption(idField,3,strIn,bFormated);
					return true;	  				
				}
				else if( colKey == CD )
				{
					setMailOption(idField,4,strIn,bFormated);

					return true;				
				}
				else if( colKey == EMAIL )
				{
					setMailOption(idField,5,strIn,bFormated);
					return true;	  				
				}

			}
		}*/
	}
	return false;

}

//*******************************************************************************
void BaseAddressBookDlg::GridControlUpdated( UINT ctrlId,
                                             const DString &rowKey,
                                             const DString &colKey,
                                             const DString &strNewValue,
                                             bool bFormatted,
                                             SEVERITY nSeverity)
{
   if(ctrlId == IDC_LV_ENTITY_MAILING )
   {
      if(colKey == I_("DocumentType") )
      {
         InitControl( IDC_CMB_ENTITY_OUTPUT );
      }
   }
}

//*******************************************************************************
const BFFieldId BaseAddressBookDlg::getAddressSubId() 
{
   return ifds::ShareholderAddress;
}

//********************************************************************************
void BaseAddressBookDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   switch (controlID)
   {
      case IDC_LV_ADDRESSES:
         m_pMailInfoTabCtrl->Load();
         break;

      case IDC_CMB_CODE:	
      {
         if(IsShareholder() )
         {
            DString dstrNominee,dstrAddrCode;
            getParent()->getField(this,ADDRLIT::REG_ADDR_READ_ONLY,dstrNominee,false);
            getParent()->getField(this,IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrCode,dstrAddrCode,false);
            dstrAddrCode.strip();
            UINT nShow;
            if(dstrNominee == YES && I_("01") == dstrAddrCode  )
               nShow =  SW_SHOW;			
            else
               nShow = SW_HIDE;

            ConnectControl(IDC_EDT_REG_ADDR_CODE,nShow==SW_SHOW );	
            ConnectControlToData(IDC_EDT_REG_ADDR_CODE,nShow==SW_SHOW,true );
            LoadControl( IDC_EDT_REG_ADDR_CODE );
            if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
            {
               m_pMailInfoTabCtrl->showTabControl(IDC_TXT_REG_ADDR_CODE,0,nShow==SW_SHOW);
               m_pMailInfoTabCtrl->showTabControl(IDC_EDT_REG_ADDR_CODE,0,nShow==SW_SHOW);

               DString dstrAddrFormat;
               DSTCWorkSession *pdstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
               pdstcWorkSession->getOption( ifds::ShrAddressFormat,dstrAddrFormat, getParent()->getDataGroupId(), false );

               //OnSelRetMail( );
               m_pMailInfoTabCtrl->Load(TAB_ADDR_INFO);

            }
            else
            {
               GetDlgItem(IDC_TXT_REG_ADDR_CODE)->ShowWindow(nShow);
               GetDlgItem(IDC_EDT_REG_ADDR_CODE)->ShowWindow(nShow);
            }
         }
      }
      break;

      case IDC_EDT_ENTITY_ADDRESS_CODE:
      {
         if ( !IsShareholder() )
         {
            // Build m_dstrEntityAddrCodeList only if Entity is linked to an Account
            // m_dstrEntityAddrCodeList will be used for Default Addr Code
            if ( !m_dstrAccountNum.empty() )
            {
               DString dstrCode,dstrDes;
               m_dstrEntityAddrCodeList = NULL_STRING;
               const DString *pCurKey = &(getParent()->getCurrentListItemKey(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST) );
               const DString *pKey = &(getParent()->getFirstListItemKey(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST) );
               if(*pKey!= EMPTY_STRING )
               {	
                  do
                  {
                     getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
                        ifds::AddrCode,dstrCode,false );
                     dstrCode.strip();	
                     //getParent()->getField( this, ENTITY_ADDRESS_LIST, ifds::AddrDesc,dstrDes,false );
                     //dstrCode.strip();	
                     m_dstrEntityAddrCodeList += dstrCode + I_("=") + dstrCode + I_(";");

                  } while ( *( pKey = &getParent()->getNextListItemKey( this, 
                        IFASTBP_PROC::ENTITY_ADDRESS_LIST) ) != EMPTY_STRING );

                  getParent()->setCurrentListItem(this,IFASTBP_PROC::ENTITY_ADDRESS_LIST,*pCurKey);
               }

               DString strValue;
               getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::AddrCode,strValue,false);
               strValue.strip();

               InitControl(IDC_CMB_ENTITY_DEFAULT_ADDRESS);

               DSTComboBox*	pCombo = dynamic_cast<DSTComboBox* >(GetDlgItem (IDC_CMB_ENTITY_DEFAULT_ADDRESS) );
               pCombo->SelectString(0, strValue.c_str() );

               if( !isAccountOwner() )	
               {
                  DSTGridWnd *pGrid = GetGrid( IDC_LV_ENTITY_MAILING );
                  pGrid->reLoadGrid();
               }
            }
         }
      }
      break;

      case IDC_EDT_ENTITY_ADDRESS_ID:	
      {	
         LoadControl( IDC_ENTITY_ADDRESS );
         LoadControl( IDC_EDT_CITY );				
         if ( !m_dstrAccountNum.empty() && !isAccountOwner() )
            LoadControl( IDC_CMB_ENTITY_HOLD_MAIL );   
         LoadControl( IDC_EDT_ENTITY_POST );				
         LoadControl( IDC_CMB_ENTITY_COUNTRY );  // this will trigger Province load					
         LoadControl( IDC_EDT_ENTITY_ADDR_NAME );
      }
      break;
      case IDC_CMB_ENTITY_COUNTRY:	
      {	
         if( !IsShareholder() )
         {
            DString dstrCountry;
            getParent()->getField( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::Country, dstrCountry ,false );	

            doSwitchProvinceControl();
         }
      }
      break;
   }

}

//******************************************************************
void BaseAddressBookDlg::doSwitchProvinceControl()  
{

    MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "doSwitchProvinceControl" ) );

	int i = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::PROVINCE_LIST );					

	// If no province exists for Country, then allow user to enter a province
	// Hide combo and show edit
	if ( i == 0 )
	{
		GetDlgItem( IDC_CMB_PROVINCE )->ShowWindow( false );
		ConnectControl( IDC_CMB_PROVINCE, false );

		GetDlgItem( IDC_EDT_ENTITY_PROVINCE )->ShowWindow( true );
		GetDlgItem( IDC_EDT_ENTITY_PROVINCE )->EnableWindow( true );
		ConnectControl(IDC_EDT_ENTITY_PROVINCE, true );
		ConnectControlToData(IDC_EDT_ENTITY_PROVINCE, true );
		LoadControl( IDC_EDT_ENTITY_PROVINCE );
	}
	else
	{
		GetDlgItem(IDC_EDT_ENTITY_PROVINCE)->ShowWindow( false );
		ConnectControl( IDC_EDT_ENTITY_PROVINCE, false );

		GetDlgItem( IDC_CMB_PROVINCE )->ShowWindow( true );
		GetDlgItem( IDC_CMB_PROVINCE )->EnableWindow( true );	
		ConnectControl( IDC_CMB_PROVINCE, true );
		ConnectControlToData(IDC_CMB_PROVINCE, true );
		LoadControl( IDC_CMB_PROVINCE );
	}
}
//******************************************************************
BOOL BaseAddressBookDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_REG_ADDR_CODE ) )
      {
         PostMessage( UM_OPENBROKERADDRESSDLG );      
      }
      if( GetFocus() == GetDlgItem( IDC_EDT_ENTITY_ADDRESS_ID ) )
      {
         PostMessage( UM_OPENADDRESSSEARCHDLG );      
      }		  
   }
   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************************
LRESULT BaseAddressBookDlg::OpenBrokerAddressDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

     
      setParameter( ADDRLIT::ACCOUNT_NUM, m_dstrAccountNum );
      //invoke the broker address dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER_ADDRESS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString dstrValue;
               getParameter( ADDRLIT::ADDRESS_CODE, dstrValue );
               getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::RegAddrCode, dstrValue);
               getParameter( ADDRLIT::AddrLine1, dstrValue );
               getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine1, dstrValue);
               getParameter( ADDRLIT::AddrLine2, dstrValue );
               getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine2, dstrValue);
               getParameter( ADDRLIT::AddrLine3, dstrValue );
               getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine3, dstrValue);
               getParameter( ADDRLIT::AddrLine4, dstrValue );
               getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine4, dstrValue);
               getParameter( ADDRLIT::AddrLine5, dstrValue );
               getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine5, dstrValue);
               getParameter( ADDRLIT::CountryCode, dstrValue );
               getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::CountryCode, dstrValue);
               getParameter( ADDRLIT::PostCode, dstrValue );
               getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::PostalCode, dstrValue);
               const DString* dstrCurrKey = &( getParent()->getCurrentListItemKey(this, IFASTBP_PROC::ADDRESSES_LIST) );

               LoadListControl(IDC_LV_ADDRESSES,dstrCurrKey);

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
LRESULT BaseAddressBookDlg::OpenAddressSearchDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenAddressSearchDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      CString cstrAddressId;      
      GetDlgItem(IDC_EDT_ENTITY_ADDRESS_ID)->GetWindowText( cstrAddressId );
      DString dstrAddressId( cstrAddressId );	
      setParameter( MFCAN_IP_PARAM::SEARCH_TYPE, I_("AddrId"));	  
      //setParameter( MFCAN_IP_PARAM::SEARCH_TYPE, I_("AddrId") );	  
      setParameter( MFCAN_IP_PARAM::ADDRSS_ID,   dstrAddressId );

      //invoke the Address Search process
      eRtn = invokeCommand( getParent(), CMD_BPROC_ENTITY_ADDRESS_SEARCH, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         {
            const DString* dstrCurrKey = &( getParent()->getCurrentListItemKey(this, 
                                             IFASTBP_PROC::ENTITY_ADDRESS_LIST ) );

            DString dstrAddrId, dstrAddrLine1, dstrAddrLine2, dstrAddrLine3, dstrCity;
            DString dstrProvince, dstrCountry, dstrPostalCode;			   

            getParameter( MFCAN_IP_PARAM::ADDRSS_ID, dstrAddrId );			   
            getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrId, dstrAddrId );

            getParameter( MFCAN_IP_PARAM::ADDRESS_LINE1, dstrAddrLine1);		 	   
            getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrLine1, dstrAddrLine1 );
            getParameter( MFCAN_IP_PARAM::ADDRESS_LINE2, dstrAddrLine2 );			   
            getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrLine2, dstrAddrLine2 );
            getParameter( MFCAN_IP_PARAM::ADDRESS_LINE3, dstrAddrLine3 );
            getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrLine3, dstrAddrLine3 );

            getParameter( MFCAN_IP_PARAM::CITY, dstrCity);			   
            getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::City, dstrCity );

            getParameter( MFCAN_IP_PARAM::POST_CODE, dstrPostalCode );		 			   
            getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::PostalCode, dstrPostalCode );

            getParameter( MFCAN_IP_PARAM::PROVICE, dstrProvince );			   
            getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::Province, dstrProvince );

            getParameter( MFCAN_IP_PARAM::COUNTRY, dstrCountry );			   
            getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::Country, dstrCountry );	

            LoadListControl(IDC_LV_ADDRESSES,dstrCurrKey);

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
bool BaseAddressBookDlg::isAccountOwner()
{
   const DString *pCurKey = &(getParent()->getCurrentListItemKey(this,IFASTBP_PROC::ENTITY_LIST) );

   if(pCurKey != NULL )
   {
      DString dstrEntityType, dstrSeq;
      getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::EntityType,dstrEntityType,false);
      getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::SeqNumber,dstrSeq,false);
      dstrEntityType.strip();
      dstrSeq.strip();
      if( ACCOUNT_OWNER == dstrEntityType && dstrSeq == I_("1") )
         return true;

   }
   return false;
}

//******************************************************************************
void BaseAddressBookDlg::doDisableNonPermButtons()
{
   if (IsShareholder())
   {
      int iAddressNo = 
         getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::ADDRESSES_LIST);

      GetDlgItem(IDC_BTN_RESET)->EnableWindow(iAddressNo > 0);
      GetDlgItem(IDC_BTN_ADM_DATES)->EnableWindow(iAddressNo > 0);
   }
   else
   {
      // Add Address/Ok/Reset buttons enabled based on same permissions as Entity Maintenance (Function Level Security 11).	
      GetDlgItem( IDC_BTN_ADD )->EnableWindow( hasCreatePermission( UAF::ENTITY_MAINTANENCE ) );		  

      int iEntityAddressNo = 
         getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST);

      if ( iEntityAddressNo > 0 )
      {
         GetDlgItem( IDC_BTN_RESET )->EnableWindow( hasCreatePermission( UAF::ENTITY_MAINTANENCE ) ||
            hasUpdatePermission( UAF::ENTITY_MAINTANENCE ) );
      }
      else
         GetDlgItem(IDC_BTN_RESET)->EnableWindow( false );

      GetDlgItem(IDC_BTN_ADM_DATES)->EnableWindow(iEntityAddressNo > 0);
   }
}

//******************************************************************************
void BaseAddressBookDlg::OnBtnHistoricalAddress()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistoricalAddress" ) );

   CWaitCursor wait;

   IFastHistoricalInfo f;
   // Shareholder
   if( IsShareholder() )
   {
      f( this, IFASTBP_PROC::ADDRESSES_LIST );
   }
}

//******************************************************************************
void BaseAddressBookDlg::OnBtnHistoricalMailing()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistoricalMailing" ) );

   CWaitCursor wait;

   IFastHistoricalInfo f;
   // Account Mailing; View side will take care of getting the information for both Delivery options
   // and for Override Delivery options.
   // 
   // historical information will be the same for 3 level mailing panel.
   // This is the constrain right now 
   // Yingbao  Sept. 28, 2005
   //
   DString dstrAccountNum, dstrRecord, keyStringIDI;

   // Account Number
   setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum);
   // Record
   getParent()->getField( this, BF::NullContainerId, ifds::AcctMstrRid, dstrRecord, false );
   setParameter(MFCAN_IP_PARAM::RECID, dstrRecord);
   // Table ID
   setParameter(MFCAN_IP_PARAM::TABLEID, AUDITTYPE::DELOPN);
   // Key is Account Number
   addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum );
   setParameter(MFCAN_IP_PARAM::KEYS, keyStringIDI);
   f( this, BF::NullContainerId, I_("MAIL") );
/*
   // Shareholder
   if( IsShareholder()  )
   {
      if( IsOverride() )
      {
         // audit for override mailing option;
           f( this, IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST, I_("SINGLE") );
      }
      else
      {
            DString dstrAccountNum, dstrRecord, keyStringIDI;

            // Account Number
            setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum);
            // Record
            getParent()->getField( this, BF::NullContainerId, ifds::AcctMstrRid, dstrRecord, false );
            setParameter(MFCAN_IP_PARAM::RECID, dstrRecord);
            // Table ID
            setParameter(MFCAN_IP_PARAM::TABLEID, AUDITTYPE::DELOPN);
            // Key is Account Number
            addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum );
            setParameter(MFCAN_IP_PARAM::KEYS, keyStringIDI);
            f( this, BF::NullContainerId, I_("MAIL") );
      }
   }
   else  // entity mailing
   {
      f( this, IFASTBP_PROC::ENTITY_MAILING_LIST, I_("SINGLE") );

   
   }
   */
}

/*void BaseAddressBookDlg::ShowReturnMail()
{
   if(DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA)
      return;

   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_REASON_CODE,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_CMB_UNCLAIM_REASON_CODE,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_STAGE,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_CMB_UNCLAIM_STAGE,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_GOVT_STMT_DATE,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_DTP_UNCLAIM_GOVT_STMT_DATE,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_REMITTANCE_DATE,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_DTP_UNCLAIM_REMITTANCE_DATE,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_COMMENT,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_EDT_UNCLAIM_COMMENT,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_STC_UNCLAIM_STAMP_DATE,1,true);
   BaseAddressBookDlg::m_pMailInfoTabCtrl->showTabControl(IDC_DTP_UNCLAIM_STAMP_DATE,1,true);
   
   //showTabControl

   GetDlgItem (IDC_STC_UNCLAIM_REASON_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_UNCLAIM_REASON_CODE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_UNCLAIM_STAGE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_UNCLAIM_STAGE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_UNCLAIM_GOVT_STMT_DATE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_UNCLAIM_GOVT_STMT_DATE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_UNCLAIM_REMITTANCE_DATE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_UNCLAIM_REMITTANCE_DATE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_UNCLAIM_COMMENT)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_EDT_UNCLAIM_COMMENT)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_UNCLAIM_STAMP_DATE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_UNCLAIM_STAMP_DATE)->ShowWindow (SW_SHOW);  

}
*/

//******************************************************************************
void BaseAddressBookDlg::HideReturnMail()
{
   if(DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA)
   {
      GetDlgItem (IDC_TAB_MAILING_INFO)->ShowWindow (SW_HIDE);
   }

   GetDlgItem (IDC_STATIC_RET_MAIL)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_RET_MAIL)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_RET_DATE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_DTP_RET_DATE)->ShowWindow (SW_HIDE);

   GetDlgItem (IDC_STC_UNCLAIM_REASON_CODE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_UNCLAIM_REASON_CODE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_UNCLAIM_STAGE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_UNCLAIM_STAGE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_UNCLAIM_GOVT_STMT_DATE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_DTP_UNCLAIM_GOVT_STMT_DATE)->ShowWindow (SW_HIDE);
   //GetDlgItem (IDC_STC_UNCLAIM_REMITTANCE_DATE)->ShowWindow (SW_HIDE);
   //GetDlgItem (IDC_DTP_UNCLAIM_REMITTANCE_DATE)->ShowWindow (SW_HIDE); 
   GetDlgItem (IDC_STC_UNCLAIM_COMMENT)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_UNCLAIM_COMMENT)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_UNCLAIM_STAMP_DATE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_DTP_UNCLAIM_STAMP_DATE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_UNCLAIM_STAGE_ASSIGN)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_UNCLAIM_STAGE_ASSIGN)->ShowWindow (SW_HIDE);
   // Entity Return Mail fields
   GetDlgItem (IDC_STATIC_ENTITY_RET_MAIL)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_RET_MAIL)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STATIC_ENTITY_RET_DATE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_DTP_ENTITY_RET_DATE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_ENTITY_UNCLAIM_REASON_CODE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_ENTITY_UNCLAIM_REASON_CODE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_ENTITY_UNCLAIM_COMMENT)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_EDT_ENTITY_UNCLAIM_COMMENT)->ShowWindow (SW_HIDE);

   // Entity Address: If return mail info is displayed, hide address controls
   GetDlgItem (IDC_TXT_ENTITY_ADDRESS_EFFECTIVE)->ShowWindow (false);
   GetDlgItem (IDC_DTP_ENTITY_ADDRESS_EFFECTIVE)->ShowWindow (false);
   GetDlgItem (IDC_EDT_ENTITY_ADDRESS_CODE)->ShowWindow (false);
   GetDlgItem (IDC_STATIC_ENTITY_ADDRESS)->ShowWindow (false);
   GetDlgItem (IDC_ENTITY_ADDRESS)->ShowWindow (false);

   if( IsShareholder() )
   {
   }
   else
   {
	   ShowEntity();
	   LoadEntityAddress();
	   
   }
}

//******************************************************************************
void BaseAddressBookDlg::tabSelectionChanged ( UINT tabControlID, 
                                               const DString &pageName)
{
   if(tabControlID == IDC_TAB_MAILING_INFO)
   {
      m_strCurrentMailingPageName = pageName;

      if( pageName == TAB_RETMAIL_INFO)
         OnSelRetMail();
	  
	  else if ( pageName == TAB_ADDR_INFO )
	  {
		
		if( IsShareholder() )
		{
			ShowShareHolder(true);
		    LoadShareHolderAddress();

		}
		else
		{
			ShowEntity();
			LoadEntityAddress();	   
		}		
	  }

      if(!m_bLoadMailing)
         FillMailAddressList();
   }
}
//**********************************************************
void BaseAddressBookDlg::OnListItemChanging(NMHDR* pNMHDR, LRESULT* pResult)
{
   if(DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA)
      return;
   if(IsShareholder()){
      m_pMailInfoTabCtrl->SelectTab(TAB_ADDR_INFO);
   }
}
//**********************************************************
void BaseAddressBookDlg::OnListItemChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
   if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA 
      && IsShareholder())
   {
      m_pMailInfoTabCtrl->SelectTab(TAB_ADDR_INFO);
      m_pMailInfoTabCtrl->Load(TAB_ADDR_INFO);
   }
}

//******************************************************************************
void BaseAddressBookDlg::SelAddrOfRetMailForNomineeIntermAcct( void )
{
   if ( !m_dstrAccountNum.empty() && !m_dstrShrNum.empty() )
   {
      const DString* key;
      key = &getParent()->getFirstListItemKey( this, IFASTBP_PROC::ADDRESSES_LIST);
      if(*key == EMPTY_STRING ) return;

      do
      {
         DString strUnclmRetMailStage;
         getParent()->getField( this, 
                                IFASTBP_PROC::ADDRESSES_LIST, 
                                ifds::UnclmRetMailStage, 
                                strUnclmRetMailStage,
                                false );

         strUnclmRetMailStage.stripAll();

         if (DSTCommonFunctions::codeInList( strUnclmRetMailStage, UNCLAIMED_STAGE) )
         {
            getParent()->setCurrentListItem(this,IFASTBP_PROC::ADDRESSES_LIST,*key);
            m_dstrSel_ShareholderList = *key;
            break;
         }
      } while ( *( key = &getParent()->getNextListItemKey( this, 
                           IFASTBP_PROC::ADDRESSES_LIST ) ) != EMPTY_STRING );
   }
}


//**************************************************************************************
void BaseAddressBookDlg::OnBtnEntityLookup()
{
       MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnEntityLookup"));
   
   CWaitCursor wait;   
   E_COMMANDRETURN eRtn = CMD_OK;
   DString postalCode;
   
   getParent()->getField (this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::PostalCode, postalCode);
   postalCode.stripAll();
  // setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
   
   CString browserTitle;
   browserTitle.LoadString(TXT_ADDRESS_LOOKUP_SCREEN_TITLE);

   DString screenTitle = browserTitle;
   DString urlParamsIDI;

   addIDITagValue (urlParamsIDI, I_("screen"),I_("AddressLookup") );

   if ( postalCode != I_("") )
   {
		addIDITagValue (urlParamsIDI, I_("pstlCode"), postalCode);
   }

   setParameter (I_("UrlParams"), urlParamsIDI);
   setParameter( I_("BrowserTitle"), screenTitle );
   setParameter (I_("from_screen"), I_("BaseAddressBookDlg"));

   eRtn = invokeCommand (getParent(), CMD_BPROC_ADDRESS_LOOKUP_BROWSER, PROC_NO_TYPE, true, NULL);
   wait.Restore();
   
   SetMessageStatusBar (NULL_STRING);
 
   switch (eRtn)
   {
      case CMD_OK:
      case CMD_MODELESS_INPROCESS:
		  {
			  DString dstrReturnResult;
			  
			  getParameter (I_("BrowserResults"), dstrReturnResult);
			  I_CHAR *temp = const_cast<I_CHAR*> (dstrReturnResult.c_str ());

			 do
			 {
			 	DString tag,
					value;

				temp = parseIdiString (temp, tag, value);
				
				if ( I_("AddrLine1") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrLine1, value );						
				}
				else if ( I_("AddrLine2") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrLine2, value );						
				}
				else if ( I_("AddrLine3") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::AddrLine3, value );						
				}				
				else if ( I_("PostalCode") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::PostalCode, value );				
				}				
				else if ( I_("CountryCode") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::Country, value );				
				}				
				else if ( I_("City") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::City, value );				
				}				
				else if ( I_("Province") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST,ifds::Province, value );				
				}
			} while (temp && temp != NULL_STRING && *temp);
			const DString* dstrCurrKey = &( getParent()->getCurrentListItemKey(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST) );

			LoadListControl(IDC_LV_ADDRESSES,dstrCurrKey);
		  }
		  break;         
      case CMD_CANCEL:          
			break;		  
      default:
         // Display error
         ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
         break;
   }
}

//******************************************************************************
void BaseAddressBookDlg::OnBtnLookup( void )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnCloneAcct "));
   
   CWaitCursor wait;   
   E_COMMANDRETURN eRtn = CMD_OK;
   DString postalCode;
   
   getParent()->getField (this, IFASTBP_PROC::ADDRESSES_LIST, ifds::PostalCode, postalCode);
   postalCode.stripAll();
  // setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, accountNum);
   
   CString browserTitle;
   browserTitle.LoadString(TXT_ADDRESS_LOOKUP_SCREEN_TITLE);

   DString screenTitle = browserTitle;
   DString urlParamsIDI;

   if ( postalCode != I_("") )
   {
		addIDITagValue (urlParamsIDI, I_("pstlCode"), postalCode);
   }

   addIDITagValue (urlParamsIDI, I_("screen"),I_("AddressLookup") );

   setParameter (I_("UrlParams"), urlParamsIDI);
   setParameter( I_("BrowserTitle"), screenTitle );
   setParameter (I_("from_screen"), I_("BaseAddressBookDlg"));
   //SetMessageStatusBar (TXT_CLONE_ACCOUNT);

   eRtn = invokeCommand (getParent(), CMD_BPROC_ADDRESS_LOOKUP_BROWSER, PROC_NO_TYPE, true, NULL);
   wait.Restore();
   
   SetMessageStatusBar (NULL_STRING);
 
   switch (eRtn)
   {
      case CMD_OK:
      case CMD_MODELESS_INPROCESS:
		  {
			  DString dstrReturnResult;
			  
			  getParameter (I_("BrowserResults"), dstrReturnResult);
			  I_CHAR *temp = const_cast<I_CHAR*> (dstrReturnResult.c_str ());

			 do
			 {
			 	DString tag,
					value;

				temp = parseIdiString (temp, tag, value);
				
				if ( I_("AddrLine1") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine1, value );						
				}
				else if ( I_("AddrLine2") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine2, value );						
				}
				else if ( I_("AddrLine3") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine3, value );						
				}
				else if ( I_("AddrLine4") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine4, value );						
				}
				else if ( I_("AddrLine5") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::AddrLine5, value );						
				}				
				else if ( I_("PostalCode") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::PostalCode, value );				
				}				
				else if ( I_("CountryCode") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::CountryCode, value );				
				}				
				else if ( I_("City") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::City, value );				
				}				
				else if ( I_("Province") == tag )
				{
					getParent()->setField(this, IFASTBP_PROC::ADDRESSES_LIST,ifds::ProvinceCanadaUS, value );				
				}
			} while (temp && temp != NULL_STRING && *temp);
			const DString* dstrCurrKey = &( getParent()->getCurrentListItemKey(this, IFASTBP_PROC::ADDRESSES_LIST) );

			LoadListControl(IDC_LV_ADDRESSES,dstrCurrKey);
		  }
		  break;         
      case CMD_CANCEL:          
			break;		  
      default:
         // Display error
         ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
         break;
   }
}

//******************************************************************************
void BaseAddressBookDlg::OnChkSkipVal()
{
   CWaitCursor wait;

   if (((CButton *) GetDlgItem (IDC_CB_SKIP_VAL))->GetCheck() != 1)
   {
      getParent()->setField ( this, 
                              IFASTBP_PROC::ADDRESSES_LIST, 
                              ifds::SkipValidate, 
                              I_("0"), 
                              false);
   }
   else
   {
      getParent()->setField ( this, 
                              IFASTBP_PROC::ADDRESSES_LIST, 
                              ifds::SkipValidate, 
                              I_("1"), 
                              false);  
   }
}

//******************************************************************************
void BaseAddressBookDlg::DoRefreshRegAddrCode( void )
{
   AddressProcess* pProcess = 
      dynamic_cast<AddressProcess*>(getParent());

   if ( pProcess )
   {
      pProcess->refreshRegAddrForNominee( getParent()->getDataGroupId() );
      LoadControl( IDC_EDT_REG_ADDR_CODE );
   }
}

//******************************************************************************
void BaseAddressBookDlg::postOpenAlertBox()
{
   DString strMailHouseholdID;
   getParent()->getField(this,IFASTBP_PROC::SHAREHOLDER_LIST, ifds::MailHouseholdID, strMailHouseholdID,false);
   strMailHouseholdID.strip().upperCase();

   if (!strMailHouseholdID.empty()) {
      m_cstrAlert.LoadString(IDS_ALRT_MAIL_IN_HOUSEHOLD);
      m_cstrAlert += L"[";
      m_cstrAlert += strMailHouseholdID.c_str();
      m_cstrAlert += L"]";
      PostMessage( UM_OPENALERTMESSAGEDLG, 0, 0 );
   }
}

//******************************************************************************
LRESULT BaseAddressBookDlg::OnOpenAlertMessageBox( WPARAM wWordParam, LPARAM lLongParam )
{
   TRACE_METHOD( CLASSNAME, I_( "OnOpenAlertMessageBox" ) );

   if(!m_cstrAlert.IsEmpty()){
      AfxMessageBox( m_cstrAlert.GetBuffer(), MB_ICONINFORMATION | MB_OK | MB_APPLMODAL );
   }

   return(0);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BaseAddressBookDlg.cpp-arc  $
// 
//    Rev 1.102   Aug 15 2012 19:01:14   wp040133
// IN# 3057134
// PET: P0187485Error Message appear when Trying to add address at All Entity Level
// 
//    Rev 1.101   Jan 23 2012 21:09:04   wp040132
// Minerva ISF code change
// 
//    Rev 1.100   Jan 19 2012 12:13:44   wp040132
// Minerva ISF Code changes..
// 
//    Rev 1.99   Nov 23 2011 15:16:26   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.98   Nov 21 2011 20:47:52   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.97   Nov 21 2011 20:46:18   wp040168
// CString cstrBrowserTitle;
// 		 cstrBrowserTitle.LoadString(TXT_BROWSER_TITLE);
// 
//    Rev 1.96.1.2   Nov 21 2011 17:27:58   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.96.1.1   Nov 21 2011 15:57:18   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.97   Nov 19 2011 01:32:28   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.96   Oct 07 2011 00:44:06   kitticha
// PETP0183105 FN02 - Unclaimed Property Alberta.
// 
//    Rev 1.95   Jan 25 2010 22:56:52   dchatcha
// IN# 1983880 - Rel 97 Static Data - Status of Nom (01 Reg address) is set to Unverified.
// 
//    Rev 1.94   Jan 22 2010 09:06:46   dchatcha
// IN# 1982767 - REl 97 - Static Data - Display of Verified status.
// 
//    Rev 1.93   Dec 14 2009 03:25:14   dchatcha
// PET0166583 FN02 FN03 - Static Verification Phase 2, Negative testing, 'Verify Status' field should not be displayed on non-support for verification environment.
// 
//    Rev 1.92   Dec 03 2009 03:53:58   dchatcha
// PET0166583 FN02 FN03 - Static Verification Phase 2.
// 
//    Rev 1.91   Aug 20 2009 10:06:40   jankovii
// IN 1801422 - R95 - Address field is not visible for LUX
// 
//    Rev 1.90   Aug 18 2009 11:13:38   jankovii
// IN 1794778 - Skip Vlaidation box misplaced on DK screeen
// 
//    Rev 1.89   Aug 07 2009 09:25:54   jankovii
// IN 1789793 - R95 Stability-Desktop - Cannot create account.
// 
//    Rev 1.88   Jul 28 2009 07:36:10   dchatcha
// PET 157825 - FN 13 - Dilution Allocation Enhancements, Default NO_SORT for combo box type.
// 
//    Rev 1.87   Jul 24 2009 01:56:54   dchatcha
// PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
// 
//    Rev 1.86   21 Jul 2009 15:10:20   walkerro
// PET156681 FN03 - fixed error when Postal Code is left blank when calling Lookup screen
// 
//    Rev 1.85   17 Jul 2009 14:08:00   walkerro
// PET156681 FN03 - Postal Code Lookup on address screen
// 
//    Rev 1.84   Jun 05 2009 17:31:30   wutipong
// INC#1708593 Disable RetMail flag on Code 01 of Nominee and Intermediery
// 
//    Rev 1.83   02 Mar 2009 13:52:50   popescu
// Incident 1569397 - fixed display issue on the mailing planel, reduce flickering.
// 
//    Rev 1.82   Jan 06 2009 05:35:54   daechach
// IN 1461977 - Return mail on caution box does not link to the return mail screen for nominee.
// 
//    Rev 1.81   03 Dec 2008 16:23:02   popescu
// IN1490683 -- Comment Field for Unclaim Property Return Mail Screen - limited the number of chars in the edit control to 100
// 
//    Rev 1.80   Nov 26 2008 03:20:30   daechach
// in# 1493599 - Entity Address of Revenue Quebec not displaying properly on Desktop. (Check in for Noom).
// 
//    Rev 1.79   Nov 19 2008 17:24:46   wongsakw
// IN1483714 - REL 89 - Unclaimed Property Retun Mail Flag issues and Stage -- Sync Up
// 
//    Rev 1.78   Nov 11 2008 23:50:16   daechach
// IN 1434870 - User s/b be able to flagged '01' address of Nom/Intermediary w/ ret. mail=yes, Code Review. Synch up from R89.
// 
//    Rev 1.77   Nov 11 2008 08:23:04   daechach
// PET0096390 FN01 Tax Jurisdiction Update - check in for Noom.
// 
//    Rev 1.76   Nov 06 2008 02:51:10   daechach
// PET5517 FN71 Unclaimed Property Phase 2
// 
//    Rev 1.75   Oct 29 2008 21:06:04   wongsakw
// PET0096390 FN01 Tax Jurisdiction Update
// 
//    Rev 1.74   Oct 28 2008 00:03:50   daechach
// IN 1434870 - User s/b be able to flagged '01' address of Nom/Intermediary w/ ret. mail=yes
// 
//    Rev 1.73   Oct 08 2008 14:58:00   wongsakw
// IN 1435612 -- Return mail reason should default to 'Unspecified'.
// 
//    Rev 1.72   Sep 29 2008 07:57:30   wongsakw
// PET5517 FN71 Unclaimed Property - Return Mail
// 
//    Rev 1.71   Sep 22 2008 08:46:40   wongsakw
// PET5517 FN71 Unclaimed Property
// 
//    Rev 1.70   31 Jul 2008 09:55:16   kovacsro
// IN1272263 - code review (	ServiceAgent used to be a read-only field, so we should keep it read-only - I couldn't see any requirement under this incident to make this field updateable) )		
// 
//    Rev 1.69   Jul 25 2008 03:42:30   wongsakw
// IN1272263 Ability to Modify Mailing Assignments - Bug in iFast/Desktop
// 
//    Rev 1.68   Oct 06 2006 16:24:58   fengyong
// Incident #729113 - fix field name
// 
//    Rev 1.67   Nov 08 2005 10:43:42   yingbaol
// Incident 447060, remove disable logic for add/delete button
// 
//    Rev 1.66   Oct 26 2005 14:39:10   porteanm
// PET1277 FN09 - Fix
// 
//    Rev 1.65   Sep 30 2005 10:30:52   popescu
// Incident# 403519 - aligned all dialogs to pass in the CLASSNAME in the constructor
// 
//    Rev 1.64   Sep 29 2005 10:56:46   yingbaol
// PET1277,FN09: Add mailing option override to NASU flow.
// 
//    Rev 1.63   Sep 21 2005 16:51:36   yingbaol
// PET1277,FN09 Investment Fund Continious Disclosure
// 
//    Rev 1.62   Jun 20 2005 09:36:22   Yingbaol
// Incident337182: fix mailing info in the nasu flow.
// 
//    Rev 1.61   May 30 2005 15:05:30   yingbaol
// Incident322642: don't create a new account mailing info if  there is one during NASU flow.
// 
//    Rev 1.60   Apr 27 2005 17:56:16   porteanm
// Incident 292892 - Fixed the refresh entity address code list for Default Address and Address Code for Entity Mailing, when Mailing enabled.
// 
//    Rev 1.59   Apr 19 2005 17:36:46   porteanm
// Incident 291639 - Disable Historical Mailing, move Postal Code at the end for Entity Address
// 
//    Rev 1.58   Apr 04 2005 18:45:18   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.57   Mar 18 2005 08:06:26   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.56   Mar 18 2005 07:41:22   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.55   Mar 16 2005 14:21:50   yingbaol
// Incident#252121: Sync. up version 1.41.1.0
// 
//    Rev 1.54   Mar 16 2005 11:31:18   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.53   Mar 15 2005 16:31:42   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.52   Mar 15 2005 12:54:28   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
// 
//    Rev 1.51   Mar 15 2005 11:22:06   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
// 
//    Rev 1.49   Mar 11 2005 15:00:54   porteanm
// PET 1171 FN01 - EUSD Entity Address Update - work in progress.
// 
//    Rev 1.48   Mar 08 2005 14:33:36   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.47   Mar 08 2005 10:17:32   porteanm
// PET 1171 FN01 - EUSD Entity Address Update - work in progress.
// 
//    Rev 1.45   Mar 05 2005 09:58:28   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.44   Mar 04 2005 16:16:30   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
// 
//    Rev 1.43   Mar 03 2005 12:47:32   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support - work in porgress.
// 
//    Rev 1.42   Feb 25 2005 13:18:50   porteanm
// PET 1171 FN01 - EUSD Entity Address Search - work in progress.
// 
//    Rev 1.41   Dec 02 2004 11:38:50   yingbaol
// PET1137,FN01: add Epost functionalities
// 
//    Rev 1.40   Apr 06 2004 16:05:06   HERNANDO
// PTS10028486 - Made the caption display consistent with other screens.
// 
//    Rev 1.39   Mar 28 2004 16:28:20   HERNANDO
// PTS10028484 - Renamed existing OnBtnHistorical fn., and added additional historical function.
// 
//    Rev 1.38   Mar 10 2004 11:25:42   HERNANDO
// PET965 FN11 - Changed to using iFastHistoricalInfo.
// 
//    Rev 1.37   Mar 05 2004 09:51:26   HERNANDO
// PET965 FN11 - Changed Delivery Options.
// 
//    Rev 1.36   Mar 02 2004 16:21:34   HERNANDO
// PET965 FN11 - Added Historical functionality.
// 
//    Rev 1.35   Jan 12 2004 12:15:28   YINGBAOL
// PTS10021623---Let user choose address from broker address screen Work has not been saved in previous version
// 
//    Rev 1.32   Oct 14 2003 13:21:48   HERNANDO
// PET893 FN08 - Salutation enhancement.
// 
//    Rev 1.31   Jul 15 2003 16:33:02   YINGBAOL
// if there is no entity address, don't get current list item key.
// 
//    Rev 1.30   Jun 06 2003 16:42:48   YINGBAOL
// fix entity mailing crash
// 
//    Rev 1.29   Jun 06 2003 14:52:16   popescu
// Fixed PTS 10018010
// 
//    Rev 1.28   Jun 05 2003 14:39:24   YINGBAOL
// PTS 10017895
// 
//    Rev 1.27   May 20 2003 18:04:36   YINGBAOL
// fix grid for entity mailing
// 
//    Rev 1.26   May 16 2003 18:17:58   YINGBAOL
// add method isAccountOwner and corresponding logic for EntityAddressMainling
// 
//    Rev 1.25   Apr 07 2003 14:33:32   YINGBAOL
// Fix display mailing panel for default
// 
//    Rev 1.24   Apr 04 2003 16:50:02   YINGBAOL
// Hide RegAddress for Entity 
// 
//    Rev 1.23   Apr 04 2003 12:16:26   FENGYONG
// fix hideadd delete button problem
// 
//    Rev 1.22   Apr 04 2003 11:48:48   YINGBAOL
// small change
// 
//    Rev 1.21   Apr 03 2003 19:13:30   FENGYONG
// addresscode list box update fix
// 
//    Rev 1.20   Apr 03 2003 09:39:58   YINGBAOL
// Broker Address Enhancement
// 
//    Rev 1.19   Apr 01 2003 16:54:44   FENGYONG
// Add AcctMailingOverride panel
// 
//    Rev 1.18   Mar 25 2003 14:50:20   linmay
// fix bug for postal code entry
// 
//    Rev 1.17   Mar 21 2003 18:33:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.16   Mar 03 2003 12:00:54   KOVACSRO
// support for InquiryOnly.
// 
//    Rev 1.15   Feb 18 2003 10:49:14   YINGBAOL
// fix PTS 10013793
// 
//    Rev 1.14   Feb 14 2003 16:26:32   linmay
// added semiannualreport
// 
//    Rev 1.13   Feb 06 2003 10:20:30   linmay
// added getAddressSubId() 
// 
//    Rev 1.12   Nov 13 2002 09:54:42   YINGBAOL
// small correction
// 
//    Rev 1.11   Nov 12 2002 14:03:02   YINGBAOL
// alway show default address code
// 
//    Rev 1.10   Nov 06 2002 10:32:52   YINGBAOL
// sync. up release 49
// 
//    Rev 1.11   Oct 21 2002 11:17:34   YINGBAOL
// allow add and delete for entity mailing even if there is no address record in entity address list
// 
//    Rev 1.10   Oct 11 2002 11:41:18   YINGBAOL
// change AddrCode to EntityAddrCode
// 
//    Rev 1.9   Oct 10 2002 15:05:52   YINGBAOL
// add OnSelDefaultEntityAddress
// 
//    Rev 1.8   Oct 08 2002 16:45:48   YINGBAOL
// take some unused code
// 
//    Rev 1.7   Oct 08 2002 15:42:24   YINGBAOL
// hide mailing option for entity mailing if OPDelivaryOption is no
// 
//    Rev 1.6   Oct 08 2002 11:51:56   YINGBAOL
// add output  control for Entity Mailing
// 
//    Rev 1.5   Sep 25 2002 11:01:28   YINGBAOL
// create account mailing for NASU
// 
//    Rev 1.4   Sep 24 2002 14:24:56   YINGBAOL
// fix Empty list  crash
// 
//    Rev 1.3   Sep 24 2002 10:52:38   YINGBAOL
// check general control  for entitymailing add and delete button
// 
//    Rev 1.2   Sep 23 2002 15:25:30   YINGBAOL
// dynamic show mailing according to view 149
// 
//    Rev 1.1   Sep 19 2002 14:05:40   YINGBAOL
// add grid control filter
// 
//    Rev 1.0   Sep 13 2002 15:10:42   YINGBAOL
// Initial revision.
 * 

 */
