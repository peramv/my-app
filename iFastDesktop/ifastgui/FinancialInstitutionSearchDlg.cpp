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
// ^FILE   : FinancialInstitutionSearchDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FinancialInstitutionSearchDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "financialinstitutionsearchdlg.h"
#include <ifastcbo\financialinstitution.hpp>
#include <ifastbp\financialinstitutionsearchprocessincludes.h>
#include <uibase\dstlistctrl.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FINANCIAL_INSTITUTION_SEARCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FinancialInstitutionSearchDlg > dlgCreator(CMD_GUI_FINANCIAL_INSTITUTION_SEARCH);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME = I_("FinancialInstitutionSearchDlg");
   const I_CHAR *LV_FINANCIAL_INSTITUTION_LIST = I_("FinancialInsitutionList");
   const UINT FILLER = 1;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


/////////////////////////////////////////////////////////////////////////////
// FinancialInstitutionSearchDlg dialog

//*********************************************************************************************
FinancialInstitutionSearchDlg::FinancialInstitutionSearchDlg (CWnd* pParent, 
   GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(FinancialInstitutionSearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME),
m_dstrFICategory (NULL_STRING)
{
   //{{AFX_DATA_INIT(FinancialInstitutionSearchDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP (FinancialInstitutionSearchDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FinancialInstitutionSearchDlg)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_NOTIFY(NM_DBLCLK, IDC_LV_INSTITUTIONS, OnDblclkLvFI)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FinancialInstitutionSearchDlg message handlers

//*********************************************************************************************
SEVERITY FinancialInstitutionSearchDlg::doInit()
{
   getParameter (I_("FICategory"), m_dstrFICategory);
   getParameter (I_("FIName"), m_dstrFIName);
   return NO_CONDITION;
}

//*********************************************************************************************
BOOL FinancialInstitutionSearchDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*********************************************************************************************
void FinancialInstitutionSearchDlg::OnPostInitDialog()
{
   AddControl (CTRL_COMBO, IDC_CMB_USING, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchUsing, 
      CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, FILLER);
   AddControl(CTRL_STATIC, IDC_STC_SEARCH11, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel1, CTRLFLAG_DEFAULT, FILLER);
   AddControl (CTRL_COMBO, IDC_CMB_FI_CATEGORY, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria1, 
      CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, FILLER);
   AddControl(CTRL_STATIC, IDC_STC_SEARCH12, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel2, 
      CTRLFLAG_DEFAULT, FILLER);
   AddControl (CTRL_COMBO, IDC_CMB_FI_TYPE, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria2, 
      CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, FILLER);
   AddControl(CTRL_STATIC, IDC_STC_SEARCH3, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchLabel3, 
      CTRLFLAG_DEFAULT, FILLER);
   AddControl (CTRL_EDIT, IDC_EDT_SEARCH3, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      ifds::SearchFieldCriteria3, 
      CTRLFLAG_DEFAULT, FILLER);
   if (FinancialInstitution::institution (m_dstrFICategory))
   {
      AddListControl (CLASSNAME, IDC_LV_INSTITUTIONS, LV_FINANCIAL_INSTITUTION_LIST, 
         ifds::FinancialInstitutionsSearchHeading, 
         IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 0, true, 
         LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE);
   }
   else if (FinancialInstitution::transit (m_dstrFICategory))
   {
      AddListControl (CLASSNAME, IDC_LV_INSTITUTIONS, LV_FINANCIAL_INSTITUTION_LIST, 
         ifds::TransitsSearchHeading, 
         IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 0, true, 
         LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE);
   }
   doRefresh (this, NULL_STRING);
}

//******************************************************************************
bool FinancialInstitutionSearchDlg::doRefresh (GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   ConnectControlsToData (FILLER);
   LoadControls (FILLER);

   //this will load the connected controls
   LoadListControl(IDC_LV_INSTITUTIONS); 
   GetDlgItem(IDC_BTN_MORE)->EnableWindow (getParent()->doMoreRecordsExist (this, 
      IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST));
   SetDlgCaption();
   return true;
}

//*************************************************************************
void FinancialInstitutionSearchDlg::SetDlgCaption()
{
   CString csCaption;


   csCaption.LoadString (TXT_TRANSIT_SEARCH_CAPTION);
   
   DString dsc (I_(": ")),
      caption (
      m_dstrFIName != NULL_STRING ? 
         dsc + csCaption.GetBuffer(0) + dsc + m_dstrFIName : 
         NULL_STRING);

   SetCaption (caption);
}

//*********************************************************************************************
void FinancialInstitutionSearchDlg::PostOk (bool bOkay)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("PreOk"));

   if (bOkay)
   {
      CWaitCursor wait;

      try
      {
         DString strKey = GetList(IDC_LV_INSTITUTIONS)->GetCurrentKey();

         if (strKey != NULL_STRING)
         {
            DString str;

            getParent()->getField (this, 
               IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, ifds::BankIdNum, str);
            str.strip();
            setParameter (I_("InstCode"), str);
            getParent()->getField (this, 
               IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, ifds::FITransitCode, str);
            str.strip();
            setParameter (I_("TransitNo"), str);
            GetFullFIName (str);
            setParameter (I_("Name"), str);
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
}

//*********************************************************************************************
void FinancialInstitutionSearchDlg::OnDblclkLvFI(NMHDR* pNMHDR, LRESULT* pResult) 
{
   PostMessage(WM_COMMAND, IDOK);
   *pResult = 0;
}

//*********************************************************************************************
void FinancialInstitutionSearchDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch"));

   CWaitCursor wait;
   GetDlgItem (IDC_BTN_SEARCH)->SetFocus();
   if (getParent()->performSearch (this, IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
      SEARCH_START) > WARNING)
   {
      // Display error
      ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
   }
   else
   {
      LoadListControl (IDC_LV_INSTITUTIONS);
      GetList (IDC_LV_INSTITUTIONS)->SetFocus();
      SetDefID (IDOK);
      GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent()->doMoreRecordsExist (this, 
         IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST));
   }

}

//*********************************************************************************************
void FinancialInstitutionSearchDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList(IDC_LV_INSTITUTIONS)->GetNextItem(-1, 
      LVIS_SELECTED | LVNI_FOCUSED);
   const DString *crtKey = &getParent()->getCurrentListItemKey(this, 
      IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST);

   if (getParent()->performSearch(this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      SEARCH_NEXT_BLOCK ) <= WARNING)
   {
      LoadListControl(IDC_LV_INSTITUTIONS);
      if (*crtKey != NULL_STRING)
      {
         GetList(IDC_LV_INSTITUTIONS)->SetSelection (crtKey);
      }
   }
   GetDlgItem (IDC_BTN_MORE)->EnableWindow(getParent()->doMoreRecordsExist(this, 
      IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST));
   GetList (IDC_LV_INSTITUTIONS)->SetSelection(cursel, true, true);
}

//*************************************************************************
void FinancialInstitutionSearchDlg::ControlUpdated (UINT controlID, 
   const DString &strValue)
{
   if (FinancialInstitution::transit (m_dstrFICategory) && 
      controlID == IDC_CMB_USING && 
      strValue == FI_SEARCH_INSTITUTIONS_F4_USING::CODE)
   {
	   CString cstrTransitNbr;
	   cstrTransitNbr.LoadString(TXT_TRANSIT_NBR);
      SetControlText (IDC_STC_SEARCH3, DString(cstrTransitNbr));
   }
   else if ( controlID == IDC_CMB_FI_CATEGORY ||
	         controlID == IDC_CMB_FI_TYPE )
   {		
	    DString dstrBankType;
	    getParent ()->getField ( this, 
			                     IFASTBP_PROC::SEARCH_CRITERIA_FILLER, 
                                 ifds::SearchFieldCriteria2, 
								 dstrBankType, false);
		if ( FinancialInstitution::institution (m_dstrFICategory) &&
			!FinancialInstitution::hasTransits( m_dstrFICategory, dstrBankType ) )
		{
			ReInitListControl( IDC_LV_INSTITUTIONS, 
                               ifds::FinancialInstitutionsSearchHeading, 
                               IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
                               LV_FINANCIAL_INSTITUTION_LIST );
		}
		else if ( ( FinancialInstitution::institution (m_dstrFICategory) &&
			        FinancialInstitution::hasTransits( m_dstrFICategory, dstrBankType ) ) ||

                  ( FinancialInstitution::transit (m_dstrFICategory) ) ) 
		{
			ReInitListControl( IDC_LV_INSTITUTIONS, 
                               ifds::TransitsSearchHeading, 
                               IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
                               LV_FINANCIAL_INSTITUTION_LIST );
		}
   }

   //this dialog should not care for the updated flag
   setUpdateFlag (false);
}

//*********************************************************************************************
bool FinancialInstitutionSearchDlg::GetOverrideItemString (long lSubstituteId, 
   const DString &columnKey, DString &strOut)
{
   bool bRet = false;

   strOut = NULL_STRING;
   if (lSubstituteId == ifds::TransitsSearchHeading.getId())
   {
      if (columnKey == I_("Name"))
      {
         GetFullFIName (strOut);
         bRet = true;
      }
   }
   if (columnKey == I_("BankIdNum"))
   {
      DString dstrBankIDType;
      int nMaxLength, nAllMaxLength;
      bool bIsAllDigits;
      getParent ()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
         ifds::BankIdType, dstrBankIDType, false);

      if (FinancialInstitution::getBankIdNumInfo (dstrBankIDType, 
         nMaxLength, bIsAllDigits, nAllMaxLength))
      {
         if( bIsAllDigits )
         {
            getParent ()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
               ifds::BankIdNum, strOut, false);
            strOut.padLeft( nMaxLength, I_('0') );
            bRet = true;
         }
      }
   }
   else if( columnKey == I_("FITransitCode") )
   {
      DString dstrBankIDType;
      int nMaxLength, nAllMaxLength;
      bool bIsAllDigits;
      getParent ()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
         ifds::BankIdType, dstrBankIDType, false);

      if (FinancialInstitution::getBankTransitNumInfo (dstrBankIDType, 
         nMaxLength, bIsAllDigits, nAllMaxLength))
      {
         if( bIsAllDigits )
         {
            getParent ()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
               ifds::FITransitCode, strOut, false);
            strOut.padLeft( nMaxLength, I_('0') );
            bRet = true;
         }
      }
   }
   return bRet;
}

//*********************************************************************************************
void FinancialInstitutionSearchDlg::GetFullFIName (DString &name) const
{
   DString branchName;

   getParent()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::BranchName, branchName);
   branchName.strip();
   getParent()->getField (this, IFASTBP_PROC::FINANCIAL_INSTITUTION_LIST, 
      ifds::Name, name);
   name.strip();
   if (branchName != NULL_STRING)
   {
      name = name + I_("-") + branchName;
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FinancialInstitutionSearchDlg.cpp-arc  $
// 
//    Rev 1.8   Nov 19 2011 01:36:24   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.7   Sep 15 2005 15:12:18   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.6   May 12 2005 11:57:24   porteanm
// Incident 265740 - Bank search.
// 
//    Rev 1.5   Nov 24 2004 19:14:30   hernando
// PTS10033887 - Pad Institution Number and Transit Number with zeros.
// 
//    Rev 1.4   Jan 30 2004 08:14:26   popescu
// PET 809, FN13, fixed internal error on banking search screen; 
// 
//    Rev 1.3   Jan 20 2004 18:27:50   popescu
// PET 809, FN 13,
// part backing-out bank master, 
// display the bank name in the FinancialSearchDialog caption if searching for transits
// 
//    Rev 1.2   Jan 12 2004 17:55:24   popescu
// PTS 10020577, added F4 institution search and F4 transit search on banking instriuctions screen, for corresponding edit fields
// 
//    Rev 1.1   Nov 19 2003 10:02:20   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 04 2003 16:10:40   popescu
// Initial revision.
// Initial revision.
 *
 */