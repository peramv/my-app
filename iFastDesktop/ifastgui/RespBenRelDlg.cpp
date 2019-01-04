// RespBenRelDlg.cpp : implementation file
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
// ^FILE   :RespBenRelDlg.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 17/07/2000
//
// ^CLASS    : RespBenRelDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include "stdafx.h"
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>
#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef  RESPBENRELDLG_H
   #include "RespBenRelDlg.h"
#endif

#ifndef RESPBENRELPROCESSINCLUDES_H
   #include <ifastbp\RespBenRelProcessIncludes.h>
#endif

#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef DSTCFUNCS_H
   #include <uibase\DstcFuncs.h>
#endif

#ifndef DSTLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif


#ifndef DSTC0051_VW_HPP
   #include <ifastdataimpl\dse_dstc0051_vw.hpp>
#endif

#ifndef DSTC0050_VW_HPP
   #include <ifastdataimpl\dse_dstc0050_vw.hpp>
#endif

#ifndef NASUPROCESSINCLUDES_H
   #include <ifastbp\NASUProcessIncludes.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_RESPBENREL;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RespBenRelDlg > dlgCreator( CMD_GUI_RESPBENREL );

#ifdef _DEBUG
   #undef THIS_FILE
static char THIS_FILE[]=__FILE__;
   #define new DEBUG_NEW
#endif

namespace
{  
   const I_CHAR *CLASSNAME             = I_( "RespBenRelDlg" );
   const I_CHAR *LV_TO_JOIN_BEN        = I_( "Entities to be joined" );
   const I_CHAR *LV_JOINED_TO_BEN      = I_( "Entities joined" );
   const I_CHAR * const Y_STRING       = I_( "Y" );

}




BEGIN_MESSAGE_MAP(RespBenRelDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RespBenRelDlg)
ON_CBN_SELCHANGE(IDC_CMB_RESP_BEN, OnSelchangeCmbRespBen)
ON_BN_CLICKED(IDC_BTN_JOIN, OnBtnJoin)
ON_BN_CLICKED(IDC_BTN_REMOVE, OnBtnRemove)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// RespBenRelDlg message handlers

RespBenRelDlg::RespBenRelDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RespBenRelDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

void RespBenRelDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(RespBenRelDlg)
   DDX_Control(pDX, IDC_BTN_REMOVE, m_BtnRemove);
   DDX_Control(pDX, IDC_BTN_JOIN, m_BtnJoin);
   //}}AFX_DATA_MAP
}

//------------------------------------------------------------------------------------

SEVERITY RespBenRelDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));
   getParameter( NASULIT::CREATING_ACCOUNT, m_strNASUFlag );
   getParameter( RESPBEN::ACCOUNT_NUMBER, _strAccountNum );
   getParameter( RESPBEN::CURRENT_RESP_BEN, _strInitialRespName );
//because of the strip that takes place we could loose the blank...
   if( _strInitialRespName == NULL_STRING )
      _strInitialRespName = I_(" ");

   return(NO_CONDITION);
}

//------------------------------------------------------------------------------------

void RespBenRelDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog"));
   m_BtnJoin.EnableWindow(false);
   m_BtnRemove.EnableWindow(false);
   AddListControl( CLASSNAME, IDC_LV_TO_JOIN_BEN, LV_TO_JOIN_BEN, ifds::LV_RESPBenRelJoinHeading, IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD );
   AddListControl( CLASSNAME, IDC_LV_JOINED_TO_BEN,LV_JOINED_TO_BEN, ifds::LV_RESPBenRelJoinHeading, IFASTBP_PROC::RESP_BEN_JOINED_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD );

   AddControl( CTRL_COMBO, IDC_CMB_RESP_BEN, IFASTBP_PROC::RESP_ACCOUNT_BEN, ifds::FirstName, CTRLFLAG_MANUAL_INIT );

   FillRespBenCombo();

}

//------------------------------------------------------------------------------------


void RespBenRelDlg::FillRespBenCombo()
{
   TRACE_METHOD( CLASSNAME, I_("FillRespBenCombo"));
   CWaitCursor wait;
   DSTComboBox *cb;

   cb = static_cast<DSTComboBox* >(GetDlgItem( IDC_CMB_RESP_BEN ) );
   cb->ResetContent();
   cb->FillInTwoListValues(IFASTBP_PROC::RESP_ACCOUNT_BEN, ifds::FirstName, ifds::LastName );
   int index = cb->SelectString(-1, _strInitialRespName.c_str());
   if( index >=0 ) OnSelchangeCmbRespBen();
}

//------------------------------------------------------------------------------------

bool RespBenRelDlg::doRefresh( GenericInterface * rpGICaller, 
                               const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_("doRefresh"));
   FillRespBenCombo();
   return(true);
}

//------------------------------------------------------------------------------------

BOOL RespBenRelDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();

   // TODO: Add extra initialization here
   setTitle();
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//------------------------------------------------------------------------------------

void RespBenRelDlg::setTitle(){
   TRACE_METHOD( CLASSNAME, I_("setTitle"));
   if( m_strNASUFlag != Y_STRING )
      return;
   DString title;
   _strAccountNum.stripLeading('0');
   CString cstrAcctNbr;
   cstrAcctNbr.LoadString(TXT_RESP_ACCOUNT);
   title = DString(cstrAcctNbr) + _strAccountNum;
   SetCaption(title);
}

//------------------------------------------------------------------------------------

void RespBenRelDlg::OnSelchangeCmbRespBen() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnSelchangeCmbRespBen"));
   CWaitCursor wait;
   DSTComboBox *cb; 
   cb = static_cast<DSTComboBox* >(GetDlgItem( IDC_CMB_RESP_BEN ) );
   int index = cb->GetCurSel();
   if( index != -1 )
   {
      _strCurrentRespBenKey = *(reinterpret_cast<DString* >(cb->GetItemData(index)));
      getParent()->setCurrentListItem(this, IFASTBP_PROC::RESP_ACCOUNT_BEN, _strCurrentRespBenKey);
      FillLVToJoin();
      FillLVJoined();
   }
}

//------------------------------------------------------------------------------------

void RespBenRelDlg::FillLVToJoin(){
   TRACE_METHOD( CLASSNAME, I_("FillLVToJoin"));
   //if nothing selected in the combo, don't fill the lists
   DSTComboBox *cb; 
   cb = static_cast<DSTComboBox* >(GetDlgItem( IDC_CMB_RESP_BEN ) );
   int currSel = cb->GetCurSel();
   if( currSel == -1 )
      return;
   CWaitCursor wait;
   //ReInitListControl( IDC_LV_TO_JOIN_BEN, DBR::LV_RESPBenRelJoinHeading, RESPBEN::RESP_BEN_TO_JOIN_LIST, LV_TO_JOIN_BEN );
   LoadListControl( IDC_LV_TO_JOIN_BEN );
   DSTListCtrl* pListCtrl = dynamic_cast<DSTListCtrl*>(GetDlgItem(IDC_LV_TO_JOIN_BEN));
   POSITION index = pListCtrl->GetFirstSelectedItemPosition();
   if( index != NULL )
      m_BtnJoin.EnableWindow();
   else
      m_BtnJoin.EnableWindow(false);
}

//------------------------------------------------------------------------------------

void RespBenRelDlg::FillLVJoined()
{
   TRACE_METHOD( CLASSNAME, I_("FillLVJoined"));
   DSTComboBox *cb; 
   cb = static_cast<DSTComboBox* >(GetDlgItem( IDC_CMB_RESP_BEN ) );
   int currSel = cb->GetCurSel();
   if( currSel == -1 )
      return;
   CWaitCursor wait;
   //ReInitListControl( IDC_LV_JOINED_TO_BEN, DBR::LV_RESPBenRelJoinHeading, RESPBEN::RESP_BEN_JOINED_LIST, LV_JOINED_TO_BEN );
   LoadListControl( IDC_LV_JOINED_TO_BEN );
   DSTListCtrl* pListCtrl = dynamic_cast<DSTListCtrl*>(GetDlgItem(IDC_LV_JOINED_TO_BEN));
   POSITION index = pListCtrl->GetFirstSelectedItemPosition();
   if( index != NULL )
      m_BtnRemove.EnableWindow();
   else
      m_BtnRemove.EnableWindow(false);
}

//------------------------------------------------------------------------------------

void RespBenRelDlg::OnBtnJoin() 
{
   //TRACE_METHOD( CLASSNAME, I_("OnBtnJoin"));
   CWaitCursor wait;
   // TODO: Add your control notification handler code here
   DSTListCtrl* pListCtrl = dynamic_cast<DSTListCtrl*>(GetDlgItem(IDC_LV_TO_JOIN_BEN));
   POSITION index = pListCtrl->GetFirstSelectedItemPosition();
   if( index < 0 )
   {
      return;
   }
   if( getParent()->send(this, RESPBEN::BTN_JOIN) )
   {
      FillLVJoined();
   }
   else
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnJoin") );
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
   }
}

//------------------------------------------------------------------------------------

void RespBenRelDlg::OnBtnRemove() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnRemove"));
   // TODO: Add your control notification handler code here
   CWaitCursor wait;
   DSTListCtrl* pListCtrl = dynamic_cast<DSTListCtrl*>(GetDlgItem(IDC_LV_JOINED_TO_BEN));
   POSITION index = pListCtrl->GetFirstSelectedItemPosition();
   if( index < 0 )
      return;
   if( getParent()->send(this, RESPBEN::BTN_REMOVE) )
      FillLVJoined();

}

//------------------------------------------------------------------------------------

void RespBenRelDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   CWaitCursor wait;
   // TODO: Add your control notification handler code here
   getParent()->reset(this, IFASTBP_PROC::RESP_ACCOUNT_BEN);
   getParent()->setCurrentListItem( this, IFASTBP_PROC::RESP_ACCOUNT_BEN, I_( "RESET" ) );
   FillRespBenCombo();
}

//------------------------------------------------------------------------------------

/*void RespBenRelDlg::DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem,	bool bIsDummyItem )
{
   TRACE_METHOD( CLASSNAME, I_("DoListItemChanged"));
   switch (listControlID)
   {
   case IDC_LV_TO_JOIN_BEN:
      {
         DSTListCtrl* pListCtrl = dynamic_cast<DSTListCtrl*>(GetDlgItem(IDC_LV_TO_JOIN_BEN));
         POSITION index = pListCtrl->GetFirstSelectedItemPosition();
         if (index != NULL)
            m_BtnJoin.EnableWindow();
         else
            m_BtnJoin.EnableWindow(false);
      }
      break;
   case IDC_LV_JOINED_TO_BEN:
      {
         DSTListCtrl* pListCtrl = dynamic_cast<DSTListCtrl*>(GetDlgItem(IDC_LV_JOINED_TO_BEN));
         POSITION index = pListCtrl->GetFirstSelectedItemPosition();
         if (index != NULL)
            m_BtnRemove.EnableWindow();
         else
            m_BtnRemove.EnableWindow(false);
      }
      break;
   }

}*/

//------------------------------------------------------------------------------------
