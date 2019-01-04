//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2010 by International Financial Data Services, Inc.
//
//******************************************************************************
//
// ^FILE   :AcctGuaranteeGuardOptDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : AcctGuaranteeGuardOptDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "AcctGuaranteeGuardOptDlg.h"
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <uibase\dstlistctrl.h>
#include <uibase\ifdslistctrl.h>
#include <uibase\DSTOleDateTime.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\AcctGuaranteeGuardOptProcessIncludes.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>

#include <ifastdataimpl\dse_dstc0412_req.hpp>
#include <ifastdataimpl\dse_dstc0412_vw.hpp>
#include <ifastdataimpl\dse_dstc0412_vwrepeat_record.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCT_GUARNT_GUARD_OPTN;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AcctGuaranteeGuardOptDlg > dlgCreator( CMD_GUI_ACCT_GUARNT_GUARD_OPTN ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME            = I_("AcctGuaranteeGuardOptDlg");
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCT_GUARNT_GUARD_OPTN;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId AcctGuaranteeGuardOptHeadingSet;
}

namespace MFCAN_IP_PARAM
{
}

namespace CND
{
   // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

class LVAcctGuaranteeGuardOptData : public IFDSListCtrlRowDataBase
{
public:
    virtual ~LVAcctGuaranteeGuardOptData() {}
    DString GuardOptCurrent, GuardOptAfter, DeffUntil, GBCD,
            GuardOptCurrentFmt, GuardOptAfterFmt,GBCDFmt,
            strGood, strBad;

    virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
    {
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GuardOptCurrent, GuardOptCurrent, false );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GuardOptAfter, GuardOptAfter, false );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::DeffUntil, DeffUntil );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GBCD, GBCD, false );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GuardOptCurrent, GuardOptCurrentFmt, true );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GuardOptAfter, GuardOptAfterFmt, true );
        strGood = I_("Good");
        strBad = I_("Bad");
    }
};

class LVAcctGuaranteeGuardOptAdapter : public IFDSListCtrlAdapter< LVAcctGuaranteeGuardOptData >
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
        } else if( *pFieldId == ifds::GuardOptCurrent ) {
            result = i_strcmp( pData1->GuardOptCurrent.c_str(), pData2->GuardOptCurrent.c_str() );
        } else if( *pFieldId == ifds::GuardOptAfter ) {
            result = i_strcmp( pData1->GuardOptAfter.c_str(), pData2->GuardOptAfter.c_str() );
        } else if( *pFieldId == ifds::GBCD ) {
            result = i_strcmp( pData1->GBCD.c_str(), pData2->GBCD.c_str() );
        } else if( *pFieldId == ifds::DeffUntil ) {
            if ( DSTCommonFunctions::CompareDates (pData1->DeffUntil, pData2->DeffUntil) == DSTCommonFunctions::FIRST_EARLIER ) {
               result = -1;
            } else if ( DSTCommonFunctions::CompareDates (pData1->DeffUntil, pData2->DeffUntil) == DSTCommonFunctions::EQUAL )  {
               result = 0;
            } else {
               result = 1;
            }
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
            } else if( *pFieldId == ifds::GuardOptCurrent ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->GuardOptCurrentFmt.c_str();
            } else if( *pFieldId == ifds::GuardOptAfter ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->GuardOptAfterFmt.c_str();
            } else if( *pFieldId == ifds::GBCD ) {
               DString dstrGBCD;
               dstrGBCD = pData->GBCD;
               dstrGBCD.strip().upperCase();
               if(dstrGBCD == I_("Y"))
                  pDispInfo->item.pszText = (I_CHAR*)pData->strGood.c_str();
               else if (dstrGBCD == I_("N"))
                  pDispInfo->item.pszText = (I_CHAR*)pData->strBad.c_str();

            } else if( *pFieldId == ifds::DeffUntil ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->DeffUntil.c_str();
            }
            return( 1 );
        }
        return( 0 );
    }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
AcctGuaranteeGuardOptDlg::AcctGuaranteeGuardOptDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AcctGuaranteeGuardOptDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_bDialogInit (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(AcctGuaranteeGuardOptDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void AcctGuaranteeGuardOptDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AcctGuaranteeGuardOptDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(AcctGuaranteeGuardOptDlg, BaseMainDlg)

//{{AFX_MSG_MAP(AcctGuaranteeGuardOptDlg)
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmin )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL AcctGuaranteeGuardOptDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog(); 

   return TRUE;
}

//******************************************************************************
void AcctGuaranteeGuardOptDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode (UAF::ACCT_GUARNT_GUARD_OPTN); 
   addBtnAddForPermissionCheck (IDC_BTN_ADD, IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST);
         
   IFDSListCtrl* ifdsListAcctGuaranteeGuardOpt = 
      new IFDSAdaptedListCtrl< LVAcctGuaranteeGuardOptAdapter >( this, 
                                                                 CLASSNAME, 
                                                                 IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST, 
                                                                 0, 
                                                                 0,
                                                                 //LISTFLAG_NOT_AUTO_ADD , 
                                                                 true /*ShowSelAlways*/, 
                                                                 true /*ShowConditions*/);

   AddIFDSListControl( ifdsListAcctGuaranteeGuardOpt, 
                       I_("ACCT_GUARNT_GUARD_OPTN_LIST"), 
                       IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, 
                       ifds::AcctGuaranteeGuardOptHeadingSet );

    AddControl ( CTRL_STATIC, IDC_BTN_ADD, CTRLFLAG_GUI_FIELD );
    AddControl ( CTRL_STATIC, IDC_BTN_ADM_DATES, CTRLFLAG_GUI_FIELD );

    AddControl ( CTRL_COMBO, 
                 IDC_CMB_CURR_GUARD_OPTN, 
                 IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, 
                 ifds::GuardOptCurrent, 
                 CTRLFLAG_DEFAULT | 
                 CTRLFLAG_AUTO_UPDATE_ON_CHANGE |
                 CTRLFLAG_INITCOMBO_BY_SUB_LIST , 
                 IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST );

    AddControl( CTRL_DATE,
                IDC_DTP_EFFECTIVE_UNTIL,
                IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST,
                ifds::DeffUntil,
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE,
                IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST );

    AddControl( CTRL_COMBO, 
                IDC_CMB_AFTR_GUARD_OPTN, 
                IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, 
                ifds::GuardOptAfter, 
                CTRLFLAG_DEFAULT | 
                CTRLFLAG_AUTO_UPDATE_ON_CHANGE |
                CTRLFLAG_INITCOMBO_BY_SUB_LIST , 
                IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST );

   ConnectListToData( IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST, true );
   LoadListControl( IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST );

   m_bDialogInit = false;
   
   doRefresh (this, NULL);

}

//*****************************************************************************
SEVERITY AcctGuaranteeGuardOptDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   m_bDialogInit = true;
      
   return NO_CONDITION;
}

//******************************************************************************
void AcctGuaranteeGuardOptDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString strShrNum, strAccountNum, dstrEntityName;
   CString strName;
   getParent()->getField(this, BF::NullContainerId, ifds::ShrNum, strShrNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, strAccountNum, false);

   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
   getFirstSequenced01AccountholderEntityName(getDataGroupId(),
                                             strAccountNum,dstrEntityName);

   SetShrAcctCaption(strShrNum, strAccountNum, dstrEntityName);
}

//************************************************************************
bool AcctGuaranteeGuardOptDlg::doRefresh ( GenericInterface * rpGICaller, 
                                           const I_CHAR * szOriginalCommand)
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   SetDlgCaption();

   DString isNewAccountGuardList;
   getParent()->getField(this, IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, IsNewAccountGuardList, isNewAccountGuardList, false);
   isNewAccountGuardList.strip().upperCase();

   LoadListControl(IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST);
   LoadControls(IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST);
   
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST));

   return true;
}

//************************************************************************
void AcctGuaranteeGuardOptDlg::OnBtnAdmin() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAdmin") );

   ShowAdminDates( IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );
}

//******************************************************************************
void AcctGuaranteeGuardOptDlg::OnBtnAdd() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAdd"));

   AddToListControl( IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST );

   getParent ()->setField( this, 
                           IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, 
                           AddNewAccountGuard, I_("Y"));

   LoadListControl(IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST);
   LoadControls(IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST);
   EnableControl( IDC_BTN_ADD, false );
}

//******************************************************************************
void AcctGuaranteeGuardOptDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));

   ResetListItem( IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST );
   
/*   ReInitControl( IDC_CMB_AFTR_GUARD_OPTN,
	              IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, 
				  ifds::GuardOptAfter );*/	
   getParent ()->setField( this, 
                           IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, 
                           AddNewAccountGuard, I_("Y"));
   doRefresh( this, NULL_STRING );   

}

//******************************************************************
void AcctGuaranteeGuardOptDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   const DString *crtKey = 
      &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );

   if( getParent()->performSearch( this, 
                                   IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, 
                                   SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_ACCT_GUARNT_GUARD_OPTN_LIST, crtKey );      
   }

   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST ) );
}

//******************************************************************
void AcctGuaranteeGuardOptDlg::ControlUpdated ( UINT controlID, 
                                                const DString &strValue)
{
   switch (controlID)
   {
      case IDC_CMB_CURR_GUARD_OPTN :
         break;
      case IDC_CMB_AFTR_GUARD_OPTN :
         break;
      case IDC_DTP_EFFECTIVE_UNTIL :
         LoadControl(IDC_CMB_AFTR_GUARD_OPTN);         
         break;
      default:
         break;
   }
}

//******************************************************************
bool AcctGuaranteeGuardOptDlg::GetDataForControl( UINT controlID, 
                                                  DString &strValueOut, 
                                                  bool bFormatted, 
                                                  int index ) const
{
   strValueOut = NULL_STRING;

   return(false);
}

//******************************************************************
BOOL AcctGuaranteeGuardOptDlg::PreTranslateMessage( MSG* pMsg ) 
{
   BOOL isTranslated = FALSE;

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//**********************************************************************************
bool AcctGuaranteeGuardOptDlg::doDisablePermCheckButton(UINT nID)
{
   if( nID == IDC_BTN_ADD )
   {
      DString dstrHasGoodGuarGuardRecordExist, dstrHasRecordAdded, dstrIsNewAccountGuardList;
      getParent()->getField(this, BF::NullContainerId, HasGoodGuarGuardRecordExist, dstrHasGoodGuarGuardRecordExist, false);
      getParent()->getField(this, BF::NullContainerId, HasRecordAdded, dstrHasRecordAdded, false);
      getParent()->getField(this, IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, IsNewAccountGuardList, dstrIsNewAccountGuardList, false);
      dstrHasGoodGuarGuardRecordExist.strip().upperCase();
      dstrHasRecordAdded.strip().upperCase();
      dstrIsNewAccountGuardList.strip().upperCase();

      if((dstrIsNewAccountGuardList == YES) && (dstrHasRecordAdded == YES))
      {
         return true;
      }
      else
      {
         return dstrHasGoodGuarGuardRecordExist == YES;
      }
   }
   return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastgui/AcctGuaranteeGuardOptDlg.cpp-arc  $
// 
//    Rev 1.2   Nov 04 2010 11:44:34   kitticha
// IN#2313085 - P0173756FN02- Don't bust the rules - Add Button not disabled.
// 
//    Rev 1.1   Nov 04 2010 11:21:26   kitticha
// IN#2313085 - P0173756FN02- Don't bust the rules - Add Button not disabled.
// 
//    Rev 1.0   Sep 17 2010 05:49:58   kitticha
// Initial revision.
// 