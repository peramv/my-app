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
//    Copyright 2004 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   :DocumentListDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : DocumentListDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "documentlistdlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\RegDocumentListProcessincludes.h>
#include <ifastbp\RegDocumentListProcess.hpp>
#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\Entity.hpp>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_REG_DOCUMENT_LIST;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< DocumentListDlg > dlgCreator( CMD_GUI_REG_DOCUMENT_LIST ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	const I_CHAR * const CLASSNAME = I_("DocumentListDlg");
	const I_CHAR *LV_DOCUMENT_LIST = I_( "Document List" );
	const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
	const I_CHAR * const ENTITY_ID   = I_( "EntityId" );
	const I_CHAR * const ENTITY      = I_( "Entity" );
	const I_CHAR * const ARIDS      = I_( "ARIDS" );
    const I_CHAR * const CHARACTERS = I_( " 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" );
}

namespace COMPLY_RULE
{
	extern CLASS_IMPORT const DString TaxCompliant;
   extern CLASS_IMPORT const DString AccountholderRisk;
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const DOC_LIST;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId DocListExists;
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId ExpireDate;
	extern CLASS_IMPORT const BFDateFieldId RequestDate;
	extern CLASS_IMPORT const BFTextFieldId RefNum;
   extern CLASS_IMPORT const BFTextFieldId RiskLevel;
   extern CLASS_IMPORT const BFTextFieldId RiskForAcctHldrRsk;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisAppl;
	extern CLASS_IMPORT const BFTextFieldId TransmitMode;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
DocumentListDlg::DocumentListDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( DocumentListDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_bDialogInit (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(DocumentListDlg)
   m_rbAcctReg = -1;
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void DocumentListDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(DocumentListDlg)
   DDX_Radio(pDX, IDC_RB_ACCTREG, m_rbAcctReg);
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(DocumentListDlg, BaseMainDlg)
//{{AFX_MSG_MAP(DocumentListDlg)
ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_RB_ACCTREG, OnRbAcctRegistration)
ON_BN_CLICKED(IDC_RB_TAXCOMPLIANT, OnRbTaxCompliant)
ON_BN_CLICKED(IDC_RB_DEATHCLAIM, OnRbDeathClaim)
ON_BN_CLICKED(IDC_RB_ACCT_RISK, OnRbAccoutholderRisk)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL DocumentListDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

	AddListControl (CLASSNAME, IDC_LV_DOCUMENT_LIST, LV_DOCUMENT_LIST, ifds::DocumentListHeading, IFASTBP_PROC::DOCUMENT_LIST);

	AddControl (CTRL_COMBO, IDC_CMB_ENT_NAME, BF::NullContainerId, CrtEntityId, CTRLFLAG_INITCOMBO_BY_SUB_LIST, 0);
	AddControl (CTRL_COMBO, IDC_CMB_DOC_STATUS, IFASTBP_PROC::DOCUMENT_LIST, ifds::RegDocStatus, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DOCUMENT_LIST);
	AddControl (CTRL_STATIC, IDC_STC_DOCUMENT_NAME, IFASTBP_PROC::DOCUMENT_LIST, ifds::RegDocName, CTRLFLAG_DEFAULT, IDC_LV_DOCUMENT_LIST);   
	AddControl (CTRL_DATE, IDC_DTP_DATE_RECEIVIED, IFASTBP_PROC::DOCUMENT_LIST, ifds::DocReceivedDate, 0, IDC_LV_DOCUMENT_LIST);
	AddControl (CTRL_EDIT,IDC_EDT_DOC_REMARKS, IFASTBP_PROC::DOCUMENT_LIST, ifds::RegDocRemarks, CTRLFLAG_DEFAULT, IDC_LV_DOCUMENT_LIST);

	AddControl (CTRL_COMBO, IDC_CMB_DOCUMENT_NAME, IFASTBP_PROC::DOCUMENT_LIST, ifds::RegDocId, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DOCUMENT_LIST);
	//AddControl (CTRL_COMBO, IDC_LIST_TYPE, BF::NullContainerId, ifds::ComplyRule, CTRLFLAG_INITCOMBO_BY_SUB_LIST, 0);

    AddControl (CTRL_DATE, IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::DOCUMENT_LIST, ifds::EffectiveDate, 0, IDC_LV_DOCUMENT_LIST);
    AddControl (CTRL_DATE, IDC_DTP_EXPIRE_DATE, IFASTBP_PROC::DOCUMENT_LIST, ifds::ExpireDate, 0, IDC_LV_DOCUMENT_LIST);
    AddControl (CTRL_DATE, IDC_DTP_REQUEST_DATE, IFASTBP_PROC::DOCUMENT_LIST, ifds::RequestDate, 0, IDC_LV_DOCUMENT_LIST);
    AddControl (CTRL_EDIT, IDC_EDT_REFERENCE, IFASTBP_PROC::DOCUMENT_LIST, ifds::RefNum, CTRLFLAG_DEFAULT, IDC_LV_DOCUMENT_LIST);
    AddControl (CTRL_COMBO, IDC_CMB_REG_DOC_JURS, IFASTBP_PROC::DOCUMENT_LIST, ifds::RegDocJurisdiction, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DOCUMENT_LIST);
    
    AddControl (CTRL_COMBO,IDC_CMB_TRANSMIT_MODE, IFASTBP_PROC::DOCUMENT_LIST, ifds::TransmitMode, CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_INITCOMBO_WITH_BLANK, IDC_LV_DOCUMENT_LIST);

    AddControl (CTRL_COMBO, IDC_CMB_ISSUE_COUNTRY, IFASTBP_PROC::DOCUMENT_LIST, ifds::CountryOfIssue, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DOCUMENT_LIST);
    AddControl (CTRL_COMBO, IDC_CMB_IDEN_METHOD, IFASTBP_PROC::DOCUMENT_LIST, ifds::IDMethod, CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_INITCOMBO_WITH_BLANK, IDC_LV_DOCUMENT_LIST);
    AddControl (CTRL_EDIT, IDC_EDT_DOC_SOURCE, IFASTBP_PROC::DOCUMENT_LIST, ifds::DocSource, CTRLFLAG_DEFAULT, IDC_LV_DOCUMENT_LIST);
    AddControl (CTRL_DATE, IDC_DTP_VERIFICATION_DATE, IFASTBP_PROC::DOCUMENT_LIST, ifds::VerifiedDate, 0, IDC_LV_DOCUMENT_LIST);

    GetDlgItem(IDC_RB_ACCT_RISK)->EnableWindow(false);
    GetDlgItem(IDC_CMB_REG_DOC_JURS)->ShowWindow( SW_HIDE );
    GetDlgItem(IDC_TXT_REG_DOC_JURS)->ShowWindow( SW_HIDE );
    GetDlgItem(IDC_BTN_MORE)->EnableWindow(false);

    DSTEdit *edtDocSource = dynamic_cast<DSTEdit *>(GetDlgItem(IDC_EDT_DOC_SOURCE));
    edtDocSource->SetMaxCharNum(40);
    edtDocSource->SetAllowedChars(CHARACTERS);

	return TRUE;
}

//******************************************************************************
void DocumentListDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

	SetUserAccesFunctionCode (UAF::DOC_LIST); 
	addControlGroupIDForPermissionCheck (IDC_LV_DOCUMENT_LIST);  
   GetDlgItem(IDC_BTN_MORE)->EnableWindow(false);
  	DSTEdit *ed = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_DOC_REMARKS));
	ed->SetMaxCharNum (100);	

    ed = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_REFERENCE));
	ed->SetMaxCharNum (20);	

	Entity *pEntity = NULL;
	if (dstWorkSession->getEntity (getDataGroupId(), m_strEntityId, pEntity)&& pEntity)
	{
		//P0193400 - FATCA Phase 1B - 'List Type' drop down replaced by a row of radio buttons 
		if (!pEntity->isDead (getDataGroupId()))
		{		
			//getParent()->setField(this, ifds::ComplyRule, I_("0"));			
			OnRbAcctRegistration();
		}
		else
		{
			//getParent()->setField(this, ifds::ComplyRule, I_("1"));			
			OnRbDeathClaim(); 
		}
      GetDlgItem(IDC_RB_ACCT_RISK)->EnableWindow(pEntity->isAccountHolderRiskApplicable(getDataGroupId()));        
	}
	
	ConnectControlsToData ();
	LoadControls ();
	doRefresh (this, NULL_STRING);
	m_bDialogInit = false;
}

//*****************************************************************************
void DocumentListDlg::OnBtnHistorical() 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical") );   
	CWaitCursor wait;   
	IFastHistoricalInfo f;
	f( this, IFASTBP_PROC::DOCUMENT_LIST );
}

//*****************************************************************************
bool DocumentListDlg::doRefresh (GenericInterface * rpGICaller, 
                                 const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   SetDlgCaption();

   LoadListControl( IDC_LV_DOCUMENT_LIST );
   GetDlgItem (IDC_BTN_MORE)->EnableWindow ( getParent()->doMoreRecordsExist (this, IFASTBP_PROC::DOCUMENT_LIST) );

   return( true );
}


//**********************************************************************************
void DocumentListDlg::ControlUpdated( UINT controlID, const DString &strValue )
{  
	if (controlID == IDC_CMB_ENT_NAME)
	{
	    LoadListControl( IDC_LV_DOCUMENT_LIST );
	}
   if(IDC_CMB_DOCUMENT_NAME == controlID  )
   {
      if( 1 == m_rbAcctReg )
      {
          DString dstrJurAppl;
          getParent()->getField( this, IFASTBP_PROC::DOCUMENT_LIST, ifds::TaxJurisAppl, dstrJurAppl, false );
          GetDlgItem(IDC_CMB_REG_DOC_JURS)->ShowWindow(I_("Y") == dstrJurAppl );
          GetDlgItem(IDC_TXT_REG_DOC_JURS)->ShowWindow(I_("Y") == dstrJurAppl );
          if( I_("Y") == dstrJurAppl)
          {
            ConnectControlToData(IDC_CMB_REG_DOC_JURS, true);
            LoadControl(IDC_CMB_REG_DOC_JURS);
          }
      }
      else
      {
         GetDlgItem(IDC_CMB_REG_DOC_JURS)->ShowWindow(false );
         GetDlgItem(IDC_TXT_REG_DOC_JURS)->ShowWindow(false);
         ConnectControlToData(IDC_CMB_REG_DOC_JURS, false);
      } 
      GetDlgItem(IDC_BTN_MORE)->EnableWindow( m_rbAcctReg == 0  && 
                                              getParent()->doMoreRecordsExist( this, IFASTBP_PROC::DOCUMENT_LIST ) ); 
  }
   //else if(controlID == IDC_LIST_TYPE)
   //{
   //   
   //   if(strValue == COMPLY_RULE::TaxCompliant)//Tax Compliant
   //   {
   //      GetDlgItem(IDC_BTN_ADD)->EnableWindow(true);
   //      GetDlgItem(IDC_BTN_DELETE)->EnableWindow(true);
   //   }
   //   else
   //   {
   //      GetDlgItem(IDC_BTN_ADD)->EnableWindow(false);
   //      GetDlgItem(IDC_BTN_DELETE)->EnableWindow(false);
   //   }

   //   GetControl (IDC_CMB_ENT_NAME)->ConnectToData (false);
   //   BFFieldId idField = CrtEntityId;
   //   if(strValue == I_("0")) 
   //      idField = CrtEntityId;
   //   else if (strValue == I_("1")) 
   //      idField = DeathEntityId;
   //   else if (strValue == COMPLY_RULE::TaxCompliant) 
   //      idField = TaxCompliantEntityId;
   //   if(strValue == COMPLY_RULE::TaxCompliant)
   //   {
   //      GetDlgItem(IDC_STC_DOCUMENT_NAME)->ShowWindow(SW_HIDE);
   //      GetDlgItem(IDC_CMB_DOCUMENT_NAME)->ShowWindow(SW_SHOW);
   //   }
   //   else
   //   {
   //      GetDlgItem(IDC_STC_DOCUMENT_NAME)->ShowWindow(SW_SHOW);
   //      GetDlgItem(IDC_CMB_DOCUMENT_NAME)->ShowWindow(SW_HIDE);
   //   }
	  // ReInitControl (IDC_CMB_ENT_NAME, BF::NullContainerId, idField);
   //   GetControl (IDC_CMB_ENT_NAME)->ConnectToData (true);
	  // LoadControl (IDC_CMB_ENT_NAME);
   //}
}

//**********************************************************************************
void DocumentListDlg::SetDlgCaption()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

    DString dstrShrNum, dstrEntityName;
	CString strName;

	// Get Entity Name
	if ( !m_dstrAccountNum.empty() ) 
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
         getDataGroupId(), m_dstrAccountNum, dstrEntityName);

	SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);
}

//*****************************************************************************
SEVERITY DocumentListDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	getParameter (ACCOUNT_NUM, m_dstrAccountNum);
	getParameter (ENTITY_ID, m_strEntityId);
	m_bDialogInit = true;
	return NO_CONDITION;
}

//*****************************************************************************
void DocumentListDlg::OnBtnAdd() 
{
   AddToListControl(IDC_LV_DOCUMENT_LIST);
}
//*****************************************************************************
void DocumentListDlg::OnBtnDelete() 
{
   DeleteFromListControl(IDC_LV_DOCUMENT_LIST);
}

//------------------------------------------------------------------------------
void DocumentListDlg::setRadioButton()
{
	((CButton* )GetDlgItem(IDC_RB_ACCTREG))->SetCheck(m_rbAcctReg == 0);
	((CButton* )GetDlgItem(IDC_RB_TAXCOMPLIANT))->SetCheck(m_rbAcctReg == 1);
	((CButton* )GetDlgItem(IDC_RB_DEATHCLAIM))->SetCheck(m_rbAcctReg == 2);  
   ((CButton* )GetDlgItem(IDC_RB_ACCT_RISK))->SetCheck(m_rbAcctReg == 3);  
}

//**********************************************************************************
void DocumentListDlg::switchDocumentListType()
{      
	setRadioButton();

	if(m_rbAcctReg == 1) //Tax Compliant
	{
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(hasCreatePermission(GetUserAccesFunctionCode()));
		GetDlgItem(IDC_BTN_DELETE)->EnableWindow(hasDeletePermission(GetUserAccesFunctionCode()));
		GetDlgItem(IDC_CMB_DOCUMENT_NAME)->EnableWindow(true);
		GetDlgItem(IDC_CMB_DOC_STATUS)->EnableWindow(true);
	}
	else 
	{
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(m_rbAcctReg == 0);
        DString hasRegStd;
        getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, HasRegStandard, hasRegStd, false);

		GetDlgItem(IDC_BTN_ADD)->EnableWindow((m_rbAcctReg == 0 && hasRegStd == I_("Y"))? true:false);
		GetDlgItem(IDC_BTN_DELETE)->EnableWindow(false);
		GetDlgItem(IDC_CMB_DOC_STATUS)->EnableWindow(false);
        GetDlgItem(IDC_BTN_ADD)->ShowWindow(3 != m_rbAcctReg);
		GetDlgItem(IDC_BTN_DELETE)->ShowWindow( 3 != m_rbAcctReg);
	}

	GetControl (IDC_CMB_ENT_NAME)->ConnectToData (false);
	BFFieldId idField = CrtEntityId;

	if (m_rbAcctReg == 0) // Account Registration
		idField = CrtEntityId;
	else if (m_rbAcctReg == 1) // Tax Compliant
		idField = TaxCompliantEntityId;	
	else if (m_rbAcctReg == 2) // Death Claim
		idField = DeathEntityId;
   else if (m_rbAcctReg == 3) // Accountholder Risk
		idField = AccountholderRiskEntityId;
	
	if(m_rbAcctReg == 1) // Tax Compliant
	{			
		GetDlgItem(IDC_STC_DOCUMENT_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMB_DOCUMENT_NAME)->ShowWindow(SW_SHOW);	
	}
	else
	{
		GetDlgItem(IDC_STC_DOCUMENT_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMB_DOCUMENT_NAME)->ShowWindow(SW_HIDE);
	}

	ReInitControl (IDC_CMB_ENT_NAME, BF::NullContainerId, idField);
	GetControl (IDC_CMB_ENT_NAME)->ConnectToData (true);
	LoadControl (IDC_CMB_ENT_NAME);  
  LoadListControl( IDC_LV_DOCUMENT_LIST );
}

//**********************************************************************************
void DocumentListDlg::OnRbAcctRegistration()
{
	TRACE_METHOD( CLASSNAME, I_( "OnRbAcctRegistration" ) );

	if( m_rbAcctReg != 0 )
	{
		m_rbAcctReg = 0;
		getParent()->setField(this, ifds::ComplyRule, I_("0"));
		switchDocumentListType();
	}
}

//**********************************************************************************
void DocumentListDlg::OnRbTaxCompliant()
{
	TRACE_METHOD( CLASSNAME, I_( "OnRbTaxCompliant" ) );

	if( m_rbAcctReg != 1 )
	{
		m_rbAcctReg = 1;
		getParent()->setField(this, ifds::ComplyRule, I_("FA"));
		switchDocumentListType();
	}	
}

//**********************************************************************************
void DocumentListDlg::OnRbDeathClaim()
{
	TRACE_METHOD( CLASSNAME, I_( "OnRbDeathClaim" ) );

	if( m_rbAcctReg != 2 )
	{
		m_rbAcctReg = 2;	
		getParent()->setField(this, ifds::ComplyRule, I_("1"));
		switchDocumentListType();
	}	
}

//**********************************************************************************
void DocumentListDlg::OnRbAccoutholderRisk()
{
	TRACE_METHOD( CLASSNAME, I_( "OnRbAccoutholderRisk" ) );

	if( m_rbAcctReg != 3 )
	{
		m_rbAcctReg = 3;	
		getParent()->setField(this, ifds::ComplyRule, I_("AR"));
		switchDocumentListType();        
	}	
}

//*****************************************************************************
void DocumentListDlg::OnBtnMore()
{
    TRACE_METHOD( CLASSNAME, ONBTNMORE );
    CWaitCursor wait;
    
   static int cursel;
   cursel = GetList( IDC_LV_DOCUMENT_LIST )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);    
   const DString *crtKey = &getParent()->getCurrentListItemKey( this,  IFASTBP_PROC::DOCUMENT_LIST );
   SetMessageStatusBar( TXT_DOCUMENT_LIST );
    if( getParent()->performSearch( this, IFASTBP_PROC::DOCUMENT_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
    {
       LoadListControl( IDC_LV_DOCUMENT_LIST );
       GetList( IDC_LV_DOCUMENT_LIST )->SetSelection(cursel, true, true);
       GetDlgItem (IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::DOCUMENT_LIST ) );
    }
    SetMessageStatusBar( NULL_STRING );
}

//**********************************************************************************
void DocumentListDlg::DoListItemChanged(UINT listControlID, 
                                        const DString &strKey,
                                        bool bIsNewItem, 
                                        bool bIsDummyItem)
{
   if (listControlID == IDC_LV_DOCUMENT_LIST)
   {
       if(m_rbAcctReg == 1) //Tax Compliant
       {
           GetDlgItem(IDC_CMB_TRANSMIT_MODE)->EnableWindow(true);
       }  
       else 
       {
           GetDlgItem(IDC_CMB_TRANSMIT_MODE)->EnableWindow(false);
       }

       if (m_rbAcctReg == 0) // Account Registration
       {		
           DString dstrRegDocComplyRule, dstrRegDocId;
           getParent()->getField(this, IFASTBP_PROC::DOCUMENT_LIST, ifds::RegDocComplyRule, dstrRegDocComplyRule, false);
           getParent()->getField(this, IFASTBP_PROC::DOCUMENT_LIST, ifds::RegDocId, dstrRegDocId, false);

           dstrRegDocComplyRule.stripAll().upperCase();
           dstrRegDocId.stripAll().upperCase();

           GetDlgItem(IDC_CMB_DOCUMENT_NAME)->ShowWindow((dstrRegDocComplyRule == ARIDS || dstrRegDocId.empty()) ? SW_SHOW:SW_HIDE);
           GetDlgItem(IDC_STC_DOCUMENT_NAME)->ShowWindow((dstrRegDocComplyRule == ARIDS || dstrRegDocId.empty()) ? SW_HIDE:SW_SHOW);
           GetDlgItem(IDC_BTN_DELETE)->EnableWindow((dstrRegDocComplyRule == ARIDS || dstrRegDocId.empty()) ? true:false);

           if (dstrRegDocComplyRule == ARIDS || dstrRegDocComplyRule.empty())
           {
               GetDlgItem(IDC_CMB_IDEN_METHOD)->EnableWindow(true);
               GetDlgItem(IDC_CMB_ISSUE_COUNTRY)->EnableWindow(true);
               GetDlgItem(IDC_EDT_DOC_SOURCE)->EnableWindow(true);
               GetDlgItem(IDC_DTP_VERIFICATION_DATE)->EnableWindow(true);
           }
           else
           {
               GetDlgItem(IDC_CMB_IDEN_METHOD)->EnableWindow(false);
               GetDlgItem(IDC_CMB_ISSUE_COUNTRY)->EnableWindow(false);
               GetDlgItem(IDC_EDT_DOC_SOURCE)->EnableWindow(false);
               GetDlgItem(IDC_DTP_VERIFICATION_DATE)->EnableWindow(false);
           }
       }
       else
       {
           GetDlgItem(IDC_CMB_IDEN_METHOD)->EnableWindow(false);
           GetDlgItem(IDC_CMB_ISSUE_COUNTRY)->EnableWindow(false);
           GetDlgItem(IDC_EDT_DOC_SOURCE)->EnableWindow(false);
           GetDlgItem(IDC_DTP_VERIFICATION_DATE)->EnableWindow(false);
       }
   }
}

//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DocumentListDlg.cpp-arc  $
// 
//    Rev 1.8   Jul 23 2012 12:55:02   wutipong
// PETP0179630_FN01 FATCA Account Entity Document Tracking
// 
//    Rev 1.7   04 Nov 2008 13:11:52   popescu
// KYC-AML fixes after system integrated testing
// 
//    Rev 1.6   03 Nov 2008 17:33:02   popescu
// KYC/AML - Joint accounts feature - after System Integrated Testing
// 
//    Rev 1.8   31 Oct 2008 16:17:20   popescu
// KYC/AML - joint accounts feature
*/