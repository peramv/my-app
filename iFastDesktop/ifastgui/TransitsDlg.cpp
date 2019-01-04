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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TransitsDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransitsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "transitsdlg.h"
#include <ifastcbo\financialinstitution.hpp>
#include <ifastbp\transitsprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <bfproc\abstractprocess.hpp>
#include <uibase\dstlistctrl.h>
#include <uibase\DSTEdit.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FINANCIAL_INSTITUTION_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRANSITS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TransitsDlg > dlgCreator (CMD_GUI_TRANSITS);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME = I_ ("TransitsDlg");
   const I_CHAR *LV_TRANSITS_LIST = I_ ("TransitsList");
   const UINT FI = 1;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


/////////////////////////////////////////////////////////////////////////////
// TransitsDlg dialog

//*********************************************************************************************
TransitsDlg::TransitsDlg (CWnd* pParent, 
   GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg (TransitsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME),
m_dstrCaller (NULL_STRING)
{
   //{{AFX_DATA_INIT (TransitsDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP (TransitsDlg, BaseMainDlg)
//{{AFX_MSG_MAP (TransitsDlg)
ON_BN_CLICKED (IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED (IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED (IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED (IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED (IDC_BTN_MORE, OnBtnMore)
ON_MESSAGE (UM_OPENBANKSEARCH, OpenBankListDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////////
// TransitsDlg message handlers

//*********************************************************************************************
SEVERITY TransitsDlg::doInit ()
{
   getParameter (MFCAN_IP_PARAM::CALLER, m_dstrCaller);
   return NO_CONDITION;
}

//*********************************************************************************************
BOOL TransitsDlg::OnInitDialog () 
{
   BaseMainDlg::OnInitDialog ();

   return TRUE;
}

//*********************************************************************************************
void TransitsDlg::OnPostInitDialog ()
{
   AddListControl (CLASSNAME, IDC_LV_TRANSITS, LV_TRANSITS_LIST, 
      ifds::TransitsHeading, IFASTBP_PROC::TRANSITS_LIST, 0, true);


   AddControl (CTRL_COMBO, IDC_CMB_TR_CATEGORY, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::InstCategory, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TRANSITS);
   AddControl (CTRL_EDIT, IDC_EDT_TR_NUMBER, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::FITransitCode, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);
   AddControl (CTRL_EDIT, IDC_EDT_TR_LONG_NAME, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::Name, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);   
   AddControl (CTRL_EDIT, IDC_EDT_TR_SHORT_NAME, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::ShortName, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);
   AddControl (CTRL_EDIT, IDC_EDT_TR_ADDRESS, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::BankAddr,  CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_LV_TRANSITS);
   AddControl (CTRL_EDIT, IDC_EDT_TR_POSTAL, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::BankPostal, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);
   AddControl (CTRL_COMBO, IDC_CMB_TR_COUNTRY, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::BankCountry, CTRLFLAG_DEFAULT | 
      CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TRANSITS);
   AddControl (CTRL_EDIT, IDC_EDT_TR_CONTACT, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::BankContact, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);
   AddControl (CTRL_EDIT, IDC_EDT_TR_TELEX, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::Telex, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);
   AddControl (CTRL_EDIT, IDC_EDT_TR_PHONE, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::PhoneNumber, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);
   AddControl (CTRL_EDIT, IDC_EDT_TR_FAX, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::FaxNumber, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);
   /*AddControl (CTRL_EDIT, IDC_EDT_TR_TELEX, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::Telex, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);*/
   AddControl (CTRL_COMBO, IDC_CMB_TR_STATUS, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::FIStatusCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TRANSITS);
   AddControl (CTRL_COMBO, IDC_CMB_TR_ROLE, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::InstRole, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TRANSITS);
   AddControl (CTRL_STATIC, IDC_STC_FI_CODE_LABEL, IFASTBP_PROC::TRANSITS_LIST, 
      ifds::InstCodeLabel, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);

   //institution controls
   if (m_dstrCaller == I_("TransitsMaint"))
   {
      AddControl (CTRL_COMBO, IDC_CMB_FI_TYPE, IFASTBP_PROC::TRANSITS_LIST, 
         ifds::BankIdType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_TRANSITS);
      AddControl (CTRL_EDIT, IDC_EDT_FI_CODE, IFASTBP_PROC::TRANSITS_LIST, 
         ifds::BankIdNum, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);
      AddControl (CTRL_STATIC, IDC_STC_FI_NAME, IFASTBP_PROC::TRANSITS_LIST, 
         InstName, CTRLFLAG_DEFAULT, IDC_LV_TRANSITS);
   }
   else
   {
      AddControl (CTRL_STATIC, IDC_STC_FI_TYPE, IFASTBP_PROC::FINANCIAL_INSTITUTION, 
         ifds::BankIdType, CTRLFLAG_DEFAULT, FI);
      AddControl (CTRL_STATIC, IDC_STC_FI_CODE, IFASTBP_PROC::FINANCIAL_INSTITUTION, 
         ifds::BankIdNum, CTRLFLAG_DEFAULT, FI);
      AddControl (CTRL_STATIC, IDC_STC_FI_NAME, IFASTBP_PROC::FINANCIAL_INSTITUTION, 
         ifds::Name, CTRLFLAG_DEFAULT, FI);
   }
   doRefresh (this, NULL_STRING);
}

//******************************************************************************
bool TransitsDlg::doRefresh (GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD (CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 
   if (DString (szOriginalCommand) == I_ ("ReloadParams"))
   {
      getParameter (MFCAN_IP_PARAM::CALLER, m_dstrCaller);
   }
   if (m_dstrCaller != I_("TransitsMaint"))
   {
      ConnectControlsToData (FI);
      LoadControls (FI);
      GetDlgItem (IDC_STC_FI_TYPE)->ShowWindow (true);
      GetDlgItem (IDC_STC_FI_CODE)->ShowWindow (true);      
      GetDlgItem (IDC_EDT_FI_CODE)->ShowWindow (false);
      GetDlgItem (IDC_CMB_FI_TYPE)->ShowWindow (false);
   }
   else
   {
      GetDlgItem (IDC_STC_FI_TYPE)->ShowWindow (false);
      GetDlgItem (IDC_STC_FI_CODE)->ShowWindow (false);      
      GetDlgItem (IDC_EDT_FI_CODE)->ShowWindow (true);
      GetDlgItem (IDC_CMB_FI_TYPE)->ShowWindow (true);
   }
   //this will load the connected controls
   LoadListControl (IDC_LV_TRANSITS); 
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, 
      IFASTBP_PROC::TRANSITS_LIST));
   SetDlgCaption ();
   modifyTransitCodeControlStyle ();
   return true;
}

//*************************************************************************
void TransitsDlg::SetDlgCaption ()
{
   DString caption;

   SetCaption (caption);
}

//*********************************************************************************************
void TransitsDlg::PostOk (bool bOkay)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("PostOk"));

   DString isSupport;

   getParent()->getField (this, BF::NullContainerId, IsSupport, isSupport);   
   if (bOkay && isSupport == I_("Y"))
   {
      CWaitCursor wait;

      try
      {
         DString str;

         getParent()->getField (this, 
            IFASTBP_PROC::TRANSITS_LIST, ifds::FITransitCode, str);
         str.strip();
         setParameter (I_("FITransitCode"), str);
         getParent()->getField (this, 
            IFASTBP_PROC::TRANSITS_LIST, ifds::Name, str);
         str.strip();
         setParameter (I_("Name"), str);
      }
      catch (ConditionException &ce)
      {
         ConditionMessageBox (ce);
      }
      catch (...)
      {
         DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
      }
   }
}

//******************************************************************************
void TransitsDlg::OnBtnAdd ()
{
   TRACE_METHOD (CLASSNAME, I_ ("OnBtnAdd"));

   CWaitCursor wait;

   AddToListControl (IDC_LV_TRANSITS);
}

//******************************************************************************
void TransitsDlg::OnBtnDelete ()
{
   TRACE_METHOD (CLASSNAME, I_ ("OnBtnDelete"));

   CWaitCursor wait;

   DeleteFromListControl (IDC_LV_TRANSITS);
}

//*********************************************************************************************
void TransitsDlg::OnBtnMore () 
{
   TRACE_METHOD ( CLASSNAME, I_ ("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList (IDC_LV_TRANSITS)->GetNextItem (-1, 
      LVIS_SELECTED | LVNI_FOCUSED);
   const DString *crtKey = &getParent ()->getCurrentListItemKey (this, 
      IFASTBP_PROC::TRANSITS_LIST);

   if (getParent ()->performSearch (this, IFASTBP_PROC::TRANSITS_LIST, 
      SEARCH_NEXT_BLOCK) <= WARNING)
   {
      LoadListControl (IDC_LV_TRANSITS);
      if (*crtKey != NULL_STRING)
      {
         GetList (IDC_LV_TRANSITS)->SetSelection (crtKey);
      }
   }
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, 
      IFASTBP_PROC::TRANSITS_LIST));
   GetList (IDC_LV_TRANSITS)->SetSelection (cursel, true, true);
}

//****************************************************************
void TransitsDlg::OnBtnReset ()
{
   TRACE_METHOD (CLASSNAME, I_ ("OnBtnReset"));

   CWaitCursor wait;

   ResetListItem (IDC_LV_TRANSITS);
}

//*************************************************************************
void TransitsDlg::OnBtnAdmDates ()
{
   ShowAdminDates (IFASTBP_PROC::TRANSITS_LIST);
}

//******************************************************************
void TransitsDlg::DoListItemChanged (UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
}

//*************************************************************************
void TransitsDlg::ControlUpdated (UINT controlID, 
   const DString &strValue)
{
   if ((controlID == IDC_CMB_FI_TYPE || controlID == IDC_EDT_FI_CODE ||
      controlID == IDC_CMB_TR_CATEGORY) &&
      m_dstrCaller == I_("TransitsMaint"))
   {
      LoadControl (IDC_STC_FI_NAME);
      modifyTransitCodeControlStyle();
   }

}

//*********************************************************************************************
bool TransitsDlg::GetOverrideItemString (long lSubstituteId, 
   const DString &columnKey, DString &strOut)
{
   bool bRet = false;

   strOut = NULL_STRING;
   if (lSubstituteId == ifds::TransitsHeading.getId())
   {
   }
   return bRet;
}

//******************************************************************************
void TransitsDlg::modifyTransitCodeControlStyle ()
{
   int nMaxLength = 0;
   int nAllMaxLength = 0;
   bool bIsAllDigits = false;
   DString category,
      type;

   if (m_dstrCaller == I_("TransitsMaint"))
   {
      getParent()->getField (this, 
         IFASTBP_PROC::TRANSITS_LIST, InstCateg, category, false);
      getParent()->getField (this, 
         IFASTBP_PROC::TRANSITS_LIST, ifds::BankIdType, type, false);
   }
   else 
   {
      getParent()->getField (this, 
         IFASTBP_PROC::FINANCIAL_INSTITUTION, ifds::InstCategory, category, false);
      getParent()->getField (this, 
         IFASTBP_PROC::FINANCIAL_INSTITUTION, ifds::BankIdType, type, false);
   }
   if (!type.empty () && !category.empty())
   {
      if (FinancialInstitution::getFITransitNumInfo (category, type, 
         nMaxLength, bIsAllDigits, nAllMaxLength))
      {
         DSTEdit *pEdit = dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_TR_NUMBER));
         if (pEdit)
         {
            pEdit->SetMaxCharNum (nMaxLength);
            pEdit->SetAllDigits (bIsAllDigits);
         }
      }
   }
}

//******************************************************************
BOOL TransitsDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   //do not allow F4 on the edit controls that are not updateable
   if (pMsg->message == WM_KEYDOWN && 
      (int)(pMsg->wParam) == VK_F4 && 
      !IsSelectedCtrlUpdateable())
   {
      return TRUE;
   }
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4)
   {
      if (GetFocus() == GetDlgItem (IDC_EDT_FI_CODE))
      {
         PostMessage (UM_OPENBANKSEARCH);
      }
   }
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//******************************************************************************
LRESULT TransitsDlg::OpenBankListDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OpenBankListDlg"));
   CWaitCursor wait;
   
   try
   {
      DString type, 
         category;

      getParent ()->getField (this, IFASTBP_PROC::TRANSITS_LIST, 
         ifds::BankIdType, type, false);
      type.strip ();
      getParent ()->getField (this, IFASTBP_PROC::TRANSITS_LIST, 
         ifds::InstCategory, category, false);
      category.strip ();
      setParameter (I_("FICategory"), 
         FinancialInstitution::getParentCategory (category));
      setParameter (I_("FIType"), type);
      switch (getParentProcess()->invokeProcessFromChild (this, 
            CMD_BPROC_FINANCIAL_INSTITUTION_SEARCH, PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         {
            DString code, 
               name;

            getParameter (I_("InstCode"), code);
            getParameter (I_("Name"), name);
            if (code != NULL_STRING)
            {
               getParent()->setField (this, IFASTBP_PROC::TRANSITS_LIST, 
                  ifds::BankIdNum, code);
               LoadControl (IDC_EDT_FI_CODE);
            }
            SetControlText (IDC_STC_FI_NAME, name);
         }
         case CMD_CANCEL:
         {
            break;
         }
         default:
         {
            // Display error
            ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
            break;
         }
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return 0;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransitsDlg.cpp-arc  $
// 
//    Rev 1.3   Sep 15 2005 15:16:04   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.2   Oct 27 2003 19:48:52   popescu
// CIBC PET809, FN 13, added Transit Search by name
// 
//    Rev 1.1   Oct 24 2003 17:20:24   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 04 2003 16:10:42   popescu
// Initial revision.
// Initial revision.
 *
 */






