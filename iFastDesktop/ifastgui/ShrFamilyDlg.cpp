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
// ^FILE   : ShrFamilyDlg.cpp
// ^AUTHOR : Claudio Sanchez
// ^DATE   : January 09, 2003
//
// ----------------------------------------------------------
//
// ^CLASS    : ShrFamilyDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Shareholder famly dialog
//
//******************************************************************************

#include "stdafx.h"
#include <bfdata\bfdata.hpp>
#include "mfdstc.h"
#include "ConfigurationConstants.h"
#include <ConfigManager.hpp>
#include "ShrFamilyDlg.hpp"
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastbp\shrfamilyprocessincludes.h>
#include <assert.h>
#include <bfproc\concretedialogcreator.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SHR_FAMILY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BROKER;

static ConcreteDialogCreator< ShrFamilyDlg > dlgCreator( CMD_GUI_SHR_FAMILY );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME      = I_( "ShrFamilyDlg" );
   const I_CHAR * const LV_SHRFAMILY   = I_( "FamilyCodeList" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SHR_FAMILY;
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FamilyType;
   extern CLASS_IMPORT const BFTextFieldId ShrFamilyHeading;
   extern CLASS_IMPORT const BFTextFieldId ShrFamilyHeadingHouseHold;
}

namespace SHAREHOLDER_TYPE
{
   extern CLASS_IMPORT const I_CHAR * const DSC;
   extern CLASS_IMPORT const I_CHAR * const MFR_HOUSEHOLDING;
}

//******************************************************************************
ShrFamilyDlg::ShrFamilyDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ShrFamilyDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

ShrFamilyDlg::~ShrFamilyDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

void ShrFamilyDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ShrFamilyDlg)
   DDX_Control(pDX, IDC_BTN_MORE, m_BtnMore);
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(ShrFamilyDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ShrFamilyDlg)
ON_MESSAGE(UM_OPENBROKERLISTDLG, OpenBrokerListDlg)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED( IDC_BTN_HISTORICAL,  OnBtnHistorical )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShrFamilyDlg message handlers

//******************************************************************************
void ShrFamilyDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode(UAF::SHR_FAMILY);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_SHRFAMILY);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_SHRFAMILY);

   // Add shareholder family list view
   AddListControl( CLASSNAME, IDC_LV_SHRFAMILY, LV_SHRFAMILY, ifds::ShrFamilyHeading, IFASTBP_PROC::FAMILY_LIST );

   // Shareholder family name and code
   AddControl( CTRL_EDIT, IDC_EDT_FAMILY_NAME, IFASTBP_PROC::FAMILY_LIST, ifds::FamilyName, 0, IDC_LV_SHRFAMILY);
   AddControl( CTRL_EDIT, IDC_EDT_FAMILY_CODE, IFASTBP_PROC::FAMILY_LIST, ifds::FamilyCode, 0, IDC_LV_SHRFAMILY);

   // FamilyType->FamilyTypeSet
   AddControl( CTRL_COMBO,IDC_CMB_SHRTYPE,IFASTBP_PROC::FAMILY_LIST, ifds::FamilyType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SHRFAMILY);

   doRefresh(this, NULL_STRING);   
}

//******************************************************************************
SEVERITY ShrFamilyDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   // Save shareholder and account number
   getParameter( SHRFAMILYLIST::SHR_NUM,     s_Name );
   getParameter( SHRFAMILYLIST::ACCOUNT_NUM, s_AcctNum); 

   sevRtn = NO_CONDITION;
   return(sevRtn);
}
//******************************************************************************
void ShrFamilyDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString dstrShrNum, dstrAccountNum, dstrEntityName;
   CString strName;

   // Get Shareholder Number
   getParent()->getField(this, IFASTBP_PROC::SHAREHOLDER, ifds::ShrNum,   dstrShrNum,     false);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   // Get Entity Name
   if ( !s_AcctNum.strip().empty() ) {
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), s_AcctNum, dstrEntityName);
   }

   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
}

//******************************************************************************
bool ShrFamilyDlg::doRefresh( GenericInterface * rpGICaller, 
                            const I_CHAR * szOriginalCommand )
{
   SetDlgCaption();
   LoadListControl( IDC_LV_SHRFAMILY );

   return(true);
}

//******************************************************************************
void ShrFamilyDlg::OnBtnAdd() 
{
   AddToListControl( IDC_LV_SHRFAMILY);
   GetDlgItem(IDC_EDT_FAMILY_CODE)->SetFocus();
}

//******************************************************************************
void ShrFamilyDlg::OnBtnDelete() 
{
   DeleteFromListControl( IDC_LV_SHRFAMILY);
   GetDlgItem(IDC_EDT_FAMILY_CODE)->SetFocus();
}

//******************************************************************************
BOOL ShrFamilyDlg::PreTranslateMessage(MSG* pMsg) 
{
   if (pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && 
         !IsSelectedCtrlUpdateable())
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if(GetFocus()== GetDlgItem(IDC_EDT_FAMILY_CODE))
      {
         PostMessage(UM_OPENBROKERLISTDLG);
      }
   }
      
   BOOL isTranslated = FALSE;

   // make certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
   {
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }

   if( !isTranslated )
   {
      // pass message down the chain
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }

   return(isTranslated);
}

//******************************************************************************
void ShrFamilyDlg::OnBtnReset() 
{
   ResetListItem(IDC_LV_SHRFAMILY);
}

//**********************************************************************************
void ShrFamilyDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::FAMILY_LIST, I_("MULTI") );
}

//*************************************************************************
LRESULT ShrFamilyDlg::OpenBrokerListDlg(WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBrokerListDlg"));
   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   try
   {
      DString familyCode;

      getParent()->getField(this, IFASTBP_PROC::FAMILY_LIST, 
         ifds::FamilyCode, familyCode);
      setParameter(MFCAN_IP_PARAM::CALLER, I_("ShrFamily"));
      setParameter(I_("FamilyCodeSearchParam"), familyCode);

      eRtn = invokeCommand (getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL);
      switch(eRtn)
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               getParameter (I_("FamilyCode"), familyCode);
               if (!familyCode.empty())
               {
                  getParent()->setField ( this, IFASTBP_PROC::FAMILY_LIST, 
                                          ifds::FamilyCode, familyCode);
               }
               LoadControl (IDC_EDT_FAMILY_CODE);
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch(ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch(...)
   {
      DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return eRtn;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ShrFamilyDlg.cpp-arc  $
// 
//    Rev 1.13   Dec 23 2011 16:53:00   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.12   Dec 09 2011 11:34:58   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.11   Nov 16 2011 19:40:14   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.10   Nov 11 2011 18:07:46   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.9   Nov 08 2011 12:12:40   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.8   Sep 15 2005 15:15:12   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.7   Mar 21 2003 18:40:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Jan 24 2003 12:19:30   sanchez
// handle reset button event with void ShrFamilyDlg::OnBtnReset() .
// 
//    Rev 1.5   Jan 16 2003 12:49:46   sanchez
// Changes for the Family name edit control added to the dialog
// 
//    Rev 1.4   Jan 15 2003 16:56:50   sanchez
// set account caption for shareholder family
// 
//    Rev 1.3   Jan 14 2003 17:42:28   sanchez
// added  Revision Control Entries
 */