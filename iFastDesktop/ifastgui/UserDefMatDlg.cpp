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
//    Copyright 2003 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : UserDefMatDlg.cpp
// ^CLASS  : UserDefMatDlg
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "UserDefMatDlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\UserDefMatProcessIncludes.h>
#include <uibase\dstedit.h>
#include <uibase\ifdslistctrl.h>
#include <bfproc\abstractprocess.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_USERDEFMAT;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< UserDefMatDlg > dlgCreator( CMD_GUI_USERDEFMAT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("UserDefMatDlg");
}

namespace CND
{
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
}

// Maturity Date List Control
class LVMaturityDateData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVMaturityDateData() {}
   DString ContractMaturityDate_, EffectiveDate_, StopDate_, OrigEventType_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ContractMaturityDate, ContractMaturityDate_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EffectiveDate, EffectiveDate_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::StopDate, StopDate_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::OrigEventType, OrigEventType_ );
   }
};

class LVMaturityDateAdapter : public IFDSListCtrlAdapter< LVMaturityDateData >
{
public:
   // required overrides
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
      if( 1 == iSortColumn ) {
         // Condition indicator column.  Sort on image index
         result = ( IFDSListBase::getColumnLVItem( lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem( lParam2, iSortColumn - 1)->iImage );
      } else if( NULL == pFieldId ) {
         return( 0 );
      } else if( *pFieldId == ifds::ContractMaturityDate ) {
         if ( DSTCommonFunctions::CompareDates( pData1->ContractMaturityDate_.c_str(), pData2->ContractMaturityDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
            result = -1;
         else if ( DSTCommonFunctions::CompareDates( pData2->ContractMaturityDate_.c_str(), pData1->ContractMaturityDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
            result = 1;
      } else if( *pFieldId == ifds::EffectiveDate ) {
         if ( DSTCommonFunctions::CompareDates( pData1->EffectiveDate_.c_str(), pData2->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
            result = -1;
         else if ( DSTCommonFunctions::CompareDates( pData2->EffectiveDate_.c_str(), pData1->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
            result = 1;
      } else if( *pFieldId == ifds::StopDate ) {
         if ( DSTCommonFunctions::CompareDates( pData1->StopDate_.c_str(), pData2->StopDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
            result = -1;
         else if ( DSTCommonFunctions::CompareDates( pData2->StopDate_.c_str(), pData1->StopDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
            result = 1;
      } else if( *pFieldId == ifds::OrigEventType ) {
         result = i_strcmp( pData1->OrigEventType_.c_str(), pData2->OrigEventType_.c_str() );
      }

      return( bAscending ? result : -result );
   }

   virtual LRESULT onGetDispInfo( IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo )
   {
      if( pDispInfo->item.mask & LVIF_TEXT )
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField( pDispInfo->item.iSubItem );

         if( NULL == pFieldId ) {
            pDispInfo->item.pszText = I_( "" );
         } else if( *pFieldId == ifds::ContractMaturityDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->ContractMaturityDate_.c_str();
         } else if( *pFieldId == ifds::EffectiveDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate_.c_str();
         } else if( *pFieldId == ifds::StopDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->StopDate_.c_str();
         } else if( *pFieldId == ifds::OrigEventType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->OrigEventType_.c_str();
         } 
         return( 1 );
      }
      return( 0 );
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************

UserDefMatDlg::UserDefMatDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( UserDefMatDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_dstrIsContract( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(UserDefMatDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void UserDefMatDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(UserDefMatDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(UserDefMatDlg, BaseMainDlg)
//{{AFX_MSG_MAP(UserDefMatDlg)
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

SEVERITY UserDefMatDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   // Get Parameters
   getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNumber );
   getParameter( MFCAN_IP_PARAM::SHR_NUM, m_dstrShareholderNumber );
   getParameter( I_("IsContract"), m_dstrIsContract );
   getParameter( MFCAN_IP_PARAM::SEG_TRANS_EXIST, m_dstrSegTransExist );
   getParameter( MFCAN_IP_PARAM::MOD_PERM, m_dstrModPerm );

   return( NO_CONDITION );
}

//******************************************************************************

BOOL UserDefMatDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   // Caption
   m_dstrShareholderNumber.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   m_dstrAccountNumber.stripLeading(I_CHAR('0')).stripTrailing();
   SetAccount( m_dstrAccountNumber );

   DString dstrEntityName;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   pDSTCWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), m_dstrAccountNumber, dstrEntityName );
   SetShrAcctCaption( m_dstrShareholderNumber, m_dstrAccountNumber, dstrEntityName );

   // Contract/Deposit Maturity Date Label
   CString cstrLabel;
   
   DString dstrGuaranteeCalcByRules;
   pDSTCWorkSession->getOption( ifds::GuaranteeCalcByRules, dstrGuaranteeCalcByRules, BF::HOST, false );
   dstrGuaranteeCalcByRules.strip().upperCase();

   if(dstrGuaranteeCalcByRules == I_("Y"))
   {
      cstrLabel.LoadString( IDS_TXT_CONTRACT_MATURITY_DATE );
   }
   else
   {
      cstrLabel.LoadString( m_dstrIsContract == I_("Y") ? IDS_TXT_CONTRACT_MATURITY_DATE : IDS_TXT_DEPOSIT_MATURITY_DATE );
   }
   GetDlgItem( IDC_STC_MATURE_DATE )->SetWindowText( cstrLabel );

   return(TRUE);
}

//******************************************************************************

void UserDefMatDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   // List Control
   // this is ignore, and ContractMaturityDate is based on the new added field ModPerm 
   //UINT uintFlags = m_dstrSegTransExist == I_("Y") ? LISTFLAG_NOT_UPDATABLE : CTRLFLAG_DEFAULT;

   UINT uintFlags = m_dstrModPerm == I_("Y") ? CTRLFLAG_DEFAULT : LISTFLAG_NOT_UPDATABLE ;

   IFDSListCtrl* ifdsListControlMaturityDates = new IFDSAdaptedListCtrl< LVMaturityDateAdapter >( this, CLASSNAME, IDC_LV_DATES, 0, uintFlags, true , true );
   AddIFDSListControl( ifdsListControlMaturityDates, I_("MATURITY_DATES"), IFASTBP_PROC::USER_DEF_MAT_LIST, ifds::UserDefMatHeading );

   // Contract Maturity Date
   AddControl( CTRL_DATE, IDC_DTP_MATURITY_DATE, IFASTBP_PROC::USER_DEF_MAT_LIST, 
      ifds::ContractMaturityDate, uintFlags, IDC_LV_DATES );

   // End Date
   AddControl( CTRL_DATE, IDC_DTP_STOP_DATE, IFASTBP_PROC::USER_DEF_MAT_LIST, 
      ifds::StopDate, CTRLFLAG_NOT_UPDATABLE, IDC_LV_DATES );

   // Effective Date
   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE, IFASTBP_PROC::USER_DEF_MAT_LIST, 
      ifds::EffectiveDate, CTRLFLAG_NOT_UPDATABLE, IDC_LV_DATES );

   // Original Event Type
   AddControl( CTRL_EDIT, IDC_TXT_ORIGEVENTTYPE, IFASTBP_PROC::USER_DEF_MAT_LIST, 
      ifds::OrigEventType, CTRLFLAG_NOT_UPDATABLE, IDC_LV_DATES );

   LoadListControl( IDC_LV_DATES );
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::USER_DEF_MAT_LIST ) );
}

//************************************************************************
void UserDefMatDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAdmDates") );
   ShowAdminDates( IFASTBP_PROC::USER_DEF_MAT_LIST );
}

//************************************************************************
void UserDefMatDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));

   CWaitCursor wait;
   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::USER_DEF_MAT_LIST );
   if( getParent()->performSearch( this, IFASTBP_PROC::USER_DEF_MAT_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_DATES );
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//*****************************************************************************
void UserDefMatDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   ResetListItem( IDC_LV_DATES );
}

//*****************************************************************************
bool UserDefMatDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return( true );
}

//*******************************************************************************************
bool UserDefMatDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
   return( false );
}

//**********************************************************************************
bool UserDefMatDlg::GetDataForControl(UINT controlID, DString &strValueOut, bool bFormatted, int index ) const
{
   return false;
};

//**********************************************************************************
void UserDefMatDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   if( controlID == IDC_CMB_CONTRACT_TYPE )
   {
      LoadListControl( IDC_LV_DATES );
   }
}

//**********************************************************************************
void UserDefMatDlg::DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem )
{
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/UserDefMatDlg.cpp-arc  $
// 
//    Rev 1.9   Feb 03 2012 18:19:56   dchatcha
// IN# 2799812 - Contract Screen Issues.
// 
//    Rev 1.8   Jan 30 2012 11:27:32   dchatcha
// IN# 2799812 - Contract Screen Issues.
// 
//    Rev 1.7   Feb 14 2006 14:14:42   zhengcon
// Incident #528284 - add one field ModPerm for updatable permission of User Defined Maturity Date of converted account
// 
//    Rev 1.6   Sep 15 2005 15:16:12   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.5   May 08 2005 16:26:48   hernando
// Incident 305718 - Seg Trans Exist will set the Updateable flag for the date control.
// 
//    Rev 1.4   Apr 14 2005 13:49:20   hernando
// PET1024 FN02 - Changed Date comparison for sort.
// 
//    Rev 1.3   Mar 21 2005 11:44:44   hernando
// PET1024 FN02 - Added SegTransExist parameter.
// 
//    Rev 1.2   Mar 21 2005 09:50:26   hernando
// PET1024 FN02 - Switched ID name to IDC_TXT_ORIGEVENTTYPE on the User Def Mat dialog.
// 
//    Rev 1.1   Mar 20 2005 18:33:28   hernando
// PET1024 FN02 - Added additional controls.
// 
//    Rev 1.0   Mar 20 2005 17:20:18   hernando
// Initial revision.
