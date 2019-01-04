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
// ^FILE   : FinancialInstitutionDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FinancialInstitutionDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "financialinstitutiondlg.h"
#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\financialinstitution.hpp>
#include <ifastbp\financialinstitutionprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <uibase\DSTEdit.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FINANCIAL_INSTITUTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANSITS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FinancialInstitutionDlg > dlgCreator (CMD_GUI_FINANCIAL_INSTITUTION);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME = I_ ("FinancialInstitutionDlg");
   const I_CHAR *LV_FINANCIAL_INSTITUTION_LIST = I_ ("FinancialInsitutionList");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


/////////////////////////////////////////////////////////////////////////////
// FinancialInstitutionDlg dialog

//*********************************************************************************************
FinancialInstitutionDlg::FinancialInstitutionDlg (CWnd* pParent, 
   GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg (FinancialInstitutionDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME)
{
   //{{AFX_DATA_INIT (FinancialInstitutionDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP (FinancialInstitutionDlg, BaseMainDlg)
//{{AFX_MSG_MAP (FinancialInstitutionDlg)
ON_NOTIFY (NM_DBLCLK, IDC_LV_INSTITUTIONS, OnDblclkLvFI)
ON_BN_CLICKED (IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED (IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED (IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED (IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED (IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED (IDC_BTN_TRANSITS, OnBtnTransits)
//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////////
// FinancialInstitutionDlg message handlers

//*********************************************************************************************
SEVERITY FinancialInstitutionDlg::doInit ()
{
   return NO_CONDITION;
}

//*********************************************************************************************
BOOL FinancialInstitutionDlg::OnInitDialog () 
{
   BaseMainDlg::OnInitDialog ();

   return TRUE;
}

//*********************************************************************************************
void FinancialInstitutionDlg::OnPostInitDialog ()
{
   AddListControl (CLASSNAME, IDC_LV_INSTITUTIONS, LV_FINANCIAL_INSTITUTION_LIST, 
      ifds::FinancialInstitutionsHeading, 
      IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 0, true);

   AddControl (CTRL_COMBO, IDC_CMB_FI_CATEGORY, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::InstCategory, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_COMBO, IDC_CMB_FI_TYPE, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::BankIdType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_EDIT, IDC_EDT_FI_INT_NUMBER, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::BankIdNum, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);   
   AddControl (CTRL_EDIT, IDC_EDT_FI_LONG_NAME, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::Name, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);   
   AddControl (CTRL_EDIT, IDC_EDT_FI_SWIFT_CODE, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::SwiftCode, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_EDIT, IDC_EDT_FI_REFERENCE, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::RefNumber, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_EDIT, IDC_EDT_FI_ADDRESS, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::BankAddr,  CTRLFLAG_FIELDS_FROM_SUB_LIST, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_EDIT, IDC_EDT_FI_POSTAL, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::BankPostal, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_COMBO, IDC_CMB_FI_COUNTRY, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::BankCountry, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_EDIT, IDC_EDT_FI_CONTACT, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::BankContact, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_COMBO, IDC_CMB_FI_EFT_FILE_CODE_PAGE, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::CodePage, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_EDIT, IDC_EDT_FI_SHORT_NAME, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::ShortName, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_EDIT, IDC_EDT_FI_PHONE, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::PhoneNumber, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);   
   AddControl (CTRL_EDIT, IDC_EDT_FI_TELEX, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::Telex, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_EDIT, IDC_EDT_FI_FAX, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::FaxNumber, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_COMBO, IDC_CMB_FI_STATUS, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::FIStatusCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_COMBO, IDC_CMB_FI_ROLE, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::InstRole, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_INSTITUTIONS);
   AddControl (CTRL_STATIC, IDC_STC_FI_NUMBER, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::InstCodeLabel, CTRLFLAG_DEFAULT, IDC_LV_INSTITUTIONS);
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FI_SWIFT_CODE))->SetAllDigits (true);
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FI_REFERENCE))->SetAllDigits (true);
   doRefresh (this, NULL_STRING);
}

//******************************************************************************
bool FinancialInstitutionDlg::doRefresh (GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD (CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 
   if (DString (szOriginalCommand) == I_ ("ReloadParams"))
   {
   }

   //this will load the connected controls
   LoadListControl (IDC_LV_INSTITUTIONS); 
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, 
      IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST));
   SetDlgCaption ();

   DString strMarket = DSTCommonFunctions::getMarket();

   if (strMarket != MARKET_IDS::JAPAN)
   {
      GetDlgItem (IDC_CMB_FI_EFT_FILE_CODE_PAGE)->EnableWindow (false);
      GetDlgItem (IDC_CMB_FI_EFT_FILE_CODE_PAGE)->ShowWindow (false);
      GetDlgItem (IDC_STC_FI_EFT_FILE_CODE_PAGE)->EnableWindow (false);
      GetDlgItem (IDC_STC_FI_EFT_FILE_CODE_PAGE)->ShowWindow (false);
   }
   return true;
}

//*************************************************************************
void FinancialInstitutionDlg::SetDlgCaption ()
{
   DString caption;

   SetCaption (caption);
}

//*********************************************************************************************
void FinancialInstitutionDlg::PostOk (bool bOkay)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("PostOk"));

   if (bOkay)
   {
      CWaitCursor wait;

      try
      {
         DString str;

         getParent()->getField (this, 
            IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, ifds::BankIdNum, str);
         str.strip();
         setParameter (I_("InstCode"), str);
         getParent()->getField (this, 
            IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, ifds::Name, str);
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
void FinancialInstitutionDlg::OnBtnAdd ()
{
   TRACE_METHOD (CLASSNAME, I_ ("OnBtnAdd"));

   CWaitCursor wait;

   AddToListControl (IDC_LV_INSTITUTIONS);
}

//******************************************************************************
void FinancialInstitutionDlg::OnBtnDelete ()
{
   TRACE_METHOD (CLASSNAME, I_ ("OnBtnDelete"));

   CWaitCursor wait;

   DeleteFromListControl (IDC_LV_INSTITUTIONS);
}

//*********************************************************************************************
void FinancialInstitutionDlg::OnBtnMore () 
{
   TRACE_METHOD ( CLASSNAME, I_ ("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList (IDC_LV_INSTITUTIONS)->GetNextItem (-1, 
      LVIS_SELECTED | LVNI_FOCUSED);
   const DString *crtKey = &getParent ()->getCurrentListItemKey (this, 
      IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);

   if (getParent ()->performSearch (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      SEARCH_NEXT_BLOCK ) <= WARNING)
   {
      LoadListControl (IDC_LV_INSTITUTIONS);
      if (*crtKey != NULL_STRING)
      {
         GetList (IDC_LV_INSTITUTIONS)->SetSelection (crtKey);
      }
   }
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, 
      IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST));
   GetList (IDC_LV_INSTITUTIONS)->SetSelection (cursel, true, true);
}

//****************************************************************
void FinancialInstitutionDlg::OnBtnReset ()
{
   TRACE_METHOD (CLASSNAME, I_ ("OnBtnReset"));

   CWaitCursor wait;

   ResetListItem (IDC_LV_INSTITUTIONS);
}

//*************************************************************************
void FinancialInstitutionDlg::OnBtnAdmDates ()
{
   ShowAdminDates (IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);
}

//*************************************************************************
void FinancialInstitutionDlg::OnBtnTransits ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnTransits"));
   CWaitCursor wait;
   E_COMMANDRETURN eRtn = CMD_CANCEL;

   try
   {
      const DString *pCurKey = 
         &(getParent()->getCurrentListItemKey(this, 
         IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST));

      setParameter (MFCAN_IP_PARAM::LIST_KEY, *pCurKey);
      eRtn = invokeCommand (getParent(), CMD_BPROC_TRANSITS, 
            PROC_SUPPORT, true, NULL);
      switch (eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
}

//*********************************************************************************************
void FinancialInstitutionDlg::OnDblclkLvFI (NMHDR* pNMHDR, LRESULT* pResult) 
{
   if (GetDlgItem (IDC_BTN_TRANSITS)->IsWindowEnabled ())
   {
      OnBtnTransits ();
   }
   *pResult = 0;
}

//******************************************************************
void FinancialInstitutionDlg::DoListItemChanged (UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   DString category,
      type;

   getParent ()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST,
      ifds::InstCategory, category, false);
   getParent ()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST,
      ifds::BankIdType, type, false);
   GetDlgItem (IDC_BTN_TRANSITS)->EnableWindow (FinancialInstitution::hasTransits (
      category, type));
}

//*************************************************************************
void FinancialInstitutionDlg::ControlUpdated (UINT controlID, 
   const DString &strValue)
{
   DString category, 
      type;

   if (IDC_CMB_FI_TYPE == controlID || IDC_CMB_FI_CATEGORY == controlID)
   {
      if (IDC_CMB_FI_TYPE == controlID)
      {
         type = strValue;
         getParent ()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST,
            ifds::InstCategory, category, false);
      }
      else if (IDC_CMB_FI_CATEGORY == controlID)
      {
         category = strValue;
         getParent ()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST,
            ifds::BankIdType, type, false);
      }
      if (category != NULL_STRING && type != NULL_STRING)
      {
         GetDlgItem (IDC_BTN_TRANSITS)->EnableWindow (
            FinancialInstitution::hasTransits (category, type));
         modifyInstCodeControlStyle (category, type);
      }
   }
}

//*********************************************************************************************
bool FinancialInstitutionDlg::GetOverrideItemString (long lSubstituteId, 
   const DString &columnKey, DString &strOut)
{
   bool bRet = false;

   strOut = NULL_STRING;
   if (lSubstituteId == ifds::FinancialInstitutionsHeading.getId())
   {
   }
   return bRet;
}

//******************************************************************************
void FinancialInstitutionDlg::modifyInstCodeControlStyle (const DString &category, 
   const DString &type)
{
   int nMaxLength = 0;
   int nAllMaxLength = 0;
   bool bIsAllDigits = false;

   if (FinancialInstitution::getFICodeNumInfo (category, type, 
      nMaxLength, bIsAllDigits, nAllMaxLength))
   {
      DSTEdit *pEdit = dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_FI_INT_NUMBER));
      if (pEdit)
      {
         pEdit->SetMaxCharNum (nMaxLength);
         pEdit->SetAllDigits (bIsAllDigits);
      }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FinancialInstitutionDlg.cpp-arc  $
// 
//    Rev 1.3   Sep 15 2005 15:12:16   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.2   Nov 19 2003 10:02:12   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.1   Oct 24 2003 17:20:22   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 04 2003 16:10:38   popescu
// Initial revision.
 *
 */






