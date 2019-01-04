// AddrTaxJurisUpdateDlg.cpp : implementation file
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
// ^FILE   : AddrTaxJurisUpdateDlg.cpp
// ^AUTHOR : Wutipong W.
// ^DATE   : 14/10/2008
//
// ^CLASS    : AddrTaxJurisUpdateDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "AddrTaxJurisUpdateDlg.h"

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ADDR_TAX_JURIS_UPDATE;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AddrTaxJurisUpdateDlg > dlgCreator( CMD_GUI_ADDR_TAX_JURIS_UPDATE );

namespace
{
   const I_CHAR *CLASSNAME             = I_( "AddrTaxJurisUpdateDlg" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId OldTaxJuris;
   extern CLASS_IMPORT const BFTextFieldId OldResProv;
   extern CLASS_IMPORT const BFTextFieldId UpdShrTaxJuris;
   extern CLASS_IMPORT const BFTextFieldId UpdShrProvRes;
   extern CLASS_IMPORT const BFTextFieldId OldAcctOwnersTaxJuris;
}

namespace IFASTBP_PROC
{
   extern CLASS_IMPORT const BFContainerId ADDR_TAX_JURIS_UPDATE;
}



extern CLASS_IMPORT const I_CHAR* CMD_GUI_ADDR_TAX_JURIS_UPDATE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDR_TAX_JURIS_UPDATE;

BEGIN_MESSAGE_MAP(AddrTaxJurisUpdateDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AddrTaxJurisUpdateDlg)
ON_BN_CLICKED(IDC_CHK_UPDATE_TAX_JURISDICTION, OnChkUpdateTaxJuris)
ON_BN_CLICKED(IDC_CHK_UPDATE_RESIDENCE_PROV, OnChkUpdateProvRes)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
AddrTaxJurisUpdateDlg::AddrTaxJurisUpdateDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AddrTaxJurisUpdateDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//--------------------------------------------
SEVERITY AddrTaxJurisUpdateDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;
   
   sevRtn = NO_CONDITION;
   
   return(sevRtn);
}
//-------------------------------------------------

void AddrTaxJurisUpdateDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog")); 
   AddControl(CTRL_EDIT, IDC_EDT_OLD_UPDATE_TAX_JURIS,
      BF::NullContainerId,
      ifds::OldTaxJuris,
      CTRLFLAG_NOT_UPDATABLE|CTRLFLAG_AUTO_UPDATE_ON_CHANGE);
   AddControl(CTRL_EDIT, IDC_EDT_OLD_UPDATE_PROV_RES,
      BF::NullContainerId,
      ifds::OldResProv,
      CTRLFLAG_NOT_UPDATABLE|CTRLFLAG_AUTO_UPDATE_ON_CHANGE);

   AddControl(CTRL_EDIT, IDC_EDT_OWNERS_TAX_JURIS,
      BF::NullContainerId,
	  ifds::OldAcctOwnersTaxJuris,
      CTRLFLAG_NOT_UPDATABLE|CTRLFLAG_AUTO_UPDATE_ON_CHANGE);

      
   ConnectControlToData(IDC_EDT_OLD_UPDATE_TAX_JURIS,true);
   ConnectControlToData(IDC_EDT_OLD_UPDATE_PROV_RES,true);
   ConnectControlToData(IDC_EDT_OWNERS_TAX_JURIS,true);
   
   LoadControl(IDC_EDT_OLD_UPDATE_TAX_JURIS);
   LoadControl(IDC_EDT_OLD_UPDATE_PROV_RES);
   LoadControl(IDC_EDT_OWNERS_TAX_JURIS);
   
   static_cast<CButton*>(GetDlgItem(IDC_CHK_UPDATE_TAX_JURISDICTION))->SetCheck(BST_CHECKED);
   static_cast<CButton*>(GetDlgItem(IDC_CHK_UPDATE_RESIDENCE_PROV))->SetCheck(BST_CHECKED);
}

//---------------------------------------------------------------------------
BOOL AddrTaxJurisUpdateDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();
   
  
   ShowWindow(SW_SHOW);

   return(TRUE);
}

//----------------------------------------------------------------------------

void AddrTaxJurisUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
}
//-----------------------------------------------------------------------------
bool AddrTaxJurisUpdateDlg::doRefresh(
                                GenericInterface * /*rpGICaller*/, 
                                const I_CHAR * //*szOriginalCommand
                                )
{  
   ShowWindow(SW_SHOW);
   return(true);  
}
//-----------------------------------------------------------------------------

void AddrTaxJurisUpdateDlg::OnChkUpdateTaxJuris()
{
   TRACE_METHOD( CLASSNAME, I_("OnChkUpdateTaxJuris"));
   int checkStatus = 
      static_cast<CButton*>(GetDlgItem(IDC_CHK_UPDATE_TAX_JURISDICTION))->GetCheck();
   getParent()->setField(this, 
         BF::NullContainerId, 
         ifds::UpdShrTaxJuris,
         (checkStatus == BST_CHECKED)? I_("Y"):I_("N"),
         false);
}
//-----------------------------------------------------------------------------
void AddrTaxJurisUpdateDlg::OnChkUpdateProvRes()
{
   TRACE_METHOD( CLASSNAME, I_("OnChkUpdateProvRes"));
   int checkStatus = 
      static_cast<CButton*>(GetDlgItem(IDC_CHK_UPDATE_RESIDENCE_PROV))->GetCheck();
   getParent()->setField(this, 
         BF::NullContainerId, 
         ifds::UpdShrProvRes,
         (checkStatus == BST_CHECKED)? I_("Y"):I_("N"),
         false);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AddrTaxJurisUpdateDlg.cpp-arc  $ */
// 
//    Rev 1.0   Oct 29 2008 21:15:24   wongsakw
// Initial revision.
