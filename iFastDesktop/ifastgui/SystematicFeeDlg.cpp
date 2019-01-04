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
// ^FILE   : SystematicFeeDlg.cpp
// ^AUTHOR : Shaobo Huang   
// ^DATE   : Nov 20, 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : SystematicFeeDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include "systematicfeedlg.h"
#include <uibase\dstedit.h>
#include <ifastbp\systematicfeeprocessincludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SYSTEMATIC_FEE;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SystematicFeeDlg > dlgCreator( CMD_GUI_SYSTEMATIC_FEE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME         = I_( "SystematicFeeDlg" );

   const I_CHAR * const TRANS_TYPE_PAC    = I_( "P" );  
   const I_CHAR * const TRANS_TYPE_SWP    = I_( "S" );
   const I_CHAR * const TRANS_TYPE_AT     = I_( "AT" );

   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
   const I_CHAR * const ACCOUNT_NUM       = I_( "AccountNum" );
   const I_CHAR * const LIST_KEY          = I_( "ListKey");
}                                         

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const BANKING_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const DEFAULT_ALLOCATION;
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
}

//******************************************************************************

SystematicFeeDlg::SystematicFeeDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SystematicFeeDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(SystematicFeeDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

void SystematicFeeDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SystematicFeeDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(SystematicFeeDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SystematicFeeDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************

SEVERITY SystematicFeeDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   getParent()->getField(this, ifds::AccountNum, m_dstrAccountNum);
   m_dstrAccountNum.strip();

   getParent()->getField(this, ifds::NullFieldId, m_dstrCurSystematicListKey);
   m_dstrCurSystematicListKey.strip();

   getParent()->setCurrentListItem(this, IFASTBP_PROC::SYSTEMATIC_LIST, m_dstrCurSystematicListKey);
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************

BOOL SystematicFeeDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void SystematicFeeDlg::OnPostInitDialog()
{
   SetAccount(m_dstrAccountNum);
   DString dstrShrNum, dstrEntityName;
   getParent()->getField( this, ifds::ShrNum,    dstrShrNum );
   getParent()->getField( this, SYSTEMATICFEELIT::PRIMARY_ACCOUNT_OWNER, dstrEntityName );
   SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);

   //Add all controls on the screen to the container
   addControls();
   showTransType();
}

//******************************************************************************

void SystematicFeeDlg::addControls() 
{
   AddControl(CTRL_EDIT, IDC_EDT_FEE,      IFASTBP_PROC::SYSTEMATIC_LIST, ifds::Fee);
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FEE))->SetAllowedChars(I_("0123456789."));
   AddControl(CTRL_STATIC,IDC_TXT_FEE_CUR, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::FeeCurrency);
   AddControl(CTRL_EDIT, IDC_EDT_ADMINFEE, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::AdminFeeAmt);
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ADMINFEE))->SetAllowedChars(I_("0123456789."));
   AddControl(CTRL_STATIC,IDC_TXT_ADMINFEE_CUR, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::AdminFeeCurr);
   AddControl(CTRL_COMBO, IDC_CMB_FLATPERCENT, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::FlatPercent, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   //   AddControl(CTRL_EDIT,IDC_TXT_ACQFEE, SYSTEMATIC_LIST, DBR::AcquisitionFee);
   //Back end load
   //   AddControl(CTRL_EDIT,IDC_CMB_BEL,    SYSTEMATIC_LIST, DBR::BEL, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

   ConnectControlsToData();
   LoadControls();
}

//******************************************************************************

void SystematicFeeDlg::showTransType() 
{
   DString dstrTransType, dstrPayType;
   getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::TransType, dstrTransType, false);

   int iShowAT = SW_HIDE;
   int iShowSP = SW_SHOW;
   if( dstrTransType == TRANS_TYPE_AT )
   {
      iShowAT = SW_SHOW;
      iShowSP = SW_HIDE;
   }
   (CWnd *)GetDlgItem(IDC_LBL_FEE)->ShowWindow(iShowSP);
   (CWnd *)GetDlgItem(IDC_EDT_FEE)->ShowWindow(iShowSP);
   (CWnd *)GetDlgItem(IDC_LBL_ADMINFEE)->ShowWindow(iShowSP);
   (CWnd *)GetDlgItem(IDC_EDT_ADMINFEE)->ShowWindow(iShowSP);
   (CWnd *)GetDlgItem(IDC_LBL_FEE_CUR)->ShowWindow(iShowSP);
   (CWnd *)GetDlgItem(IDC_TXT_FEE_CUR)->ShowWindow(iShowSP);
   (CWnd *)GetDlgItem(IDC_LBL_ADMINFEE_CUR)->ShowWindow(iShowSP);
   (CWnd *)GetDlgItem(IDC_TXT_ADMINFEE_CUR)->ShowWindow(iShowSP);

   (CWnd *)GetDlgItem(IDC_LBL_ACQFEE)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_EDT_ACQFEE)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_LBL_BEL)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_CMB_BEL)->ShowWindow(iShowAT);

   (CWnd *)GetDlgItem(IDC_CMB_FLATPERCENT)->ShowWindow(SW_SHOW);
   (CWnd *)GetDlgItem(IDC_CMB_FLATPERCENT)->EnableWindow(true);
}

//******************************************************************************

bool SystematicFeeDlg::GetDataForControl(UINT controlID, DString &dstrValueOut, 
                                         bool bFormatted, int index) const
{
   bool bReturn = true;

   switch( controlID )
   {
      case IDC_TXT_FEE_CUR:
         {
            DString dstrFund, dstrClass;
            getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::FeeCurrency, dstrValueOut);
            if( dstrValueOut.strip() == I_("") )
            {
               getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::FundCode, dstrFund, false);
               getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::ClassCode, dstrClass, false);
               dstrFund.strip();
               dstrClass.strip();
               if( dstrFund != I_("") && dstrClass != I_("") )
                  getFundCurrency(dstrFund, dstrClass, dstrValueOut);
            }
            break;
         }
      case IDC_TXT_ADMINFEE_CUR:
         {
            DString dstrFund, dstrClass;
            getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::AdminFeeCurr, dstrValueOut);
            if( dstrValueOut.strip() == I_("") )
            {
               getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::FundCode, dstrFund, false);
               getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::ClassCode, dstrClass, false);
               dstrFund.strip();
               dstrClass.strip();
               if( dstrFund != I_("") && dstrClass != I_("") )
                  getFundCurrency(dstrFund, dstrClass, dstrValueOut);
            }
            break;
         }
      default:
         bReturn = false;
         break;
   }
   return(bReturn);
}

//******************************************************************************

void SystematicFeeDlg::getFundCurrency(DString &dstrFundCodeSel, DString &dstrClassCodeSel, DString &dstrCurr) const
{
   DString dstrClassCode, dstrFundCode;
   dstrCurr = I_("");
   const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, IFASTBP_PROC::FUND_DETAIL_LIST));
   const DString *pKey = &getParent()->getFirstListItemKey(this, IFASTBP_PROC::FUND_DETAIL_LIST);
   do
   {
      getParent()->getField(this, IFASTBP_PROC::FUND_DETAIL_LIST, ifds::FundCode, dstrFundCode);
      getParent()->getField(this, IFASTBP_PROC::FUND_DETAIL_LIST, ifds::ClassCode, dstrClassCode);
      if( dstrFundCode.strip().upperCase() == dstrFundCodeSel.strip().upperCase() &&
          dstrClassCode.strip().upperCase() == dstrClassCodeSel.strip().upperCase() )
      {
         getParent()->getField(this, IFASTBP_PROC::FUND_DETAIL_LIST, ifds::Currency, dstrCurr);
         dstrCurr.strip().upperCase();
         break;
      }
   }
   while( *(pKey = &(getParent()->getNextListItemKey(this, IFASTBP_PROC::FUND_DETAIL_LIST))) != I_("") );

   if( (*pCurKey) != NULL_STRING )
      getParent()->setCurrentListItem( this, IFASTBP_PROC::FUND_DETAIL_LIST, *pCurKey );
}

//******************************************************************************

bool SystematicFeeDlg::doRefresh(GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  
   getParent()->getField(this, ifds::AccountNum, m_dstrAccountNum);
   m_dstrAccountNum.strip();

   SetAccount(m_dstrAccountNum);
   DString dstrShrNum, dstrEntityName;
   getParent()->getField( this, ifds::ShrNum,    dstrShrNum );
   getParent()->getField( this, SYSTEMATICFEELIT::PRIMARY_ACCOUNT_OWNER, dstrEntityName );
   SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);

   getParent()->getField(this, ifds::NullFieldId, m_dstrCurSystematicListKey);
   m_dstrCurSystematicListKey.strip();

   getParent()->setCurrentListItem(this, IFASTBP_PROC::SYSTEMATIC_LIST, m_dstrCurSystematicListKey);

   ConnectControlsToData();
   LoadControls();

   showTransType();
   return(true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SystematicFeeDlg.cpp-arc  $
 * 
 *    Rev 1.7   Sep 15 2005 15:15:28   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.6   Mar 21 2003 18:41:32   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:56:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   Aug 29 2002 12:57:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   22 May 2002 19:16:30   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   27 Mar 2002 20:01:26   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.1   Mar 16 2000 12:02:04   DT24433
 * added revision log and removed unused headers
 * 
 */
