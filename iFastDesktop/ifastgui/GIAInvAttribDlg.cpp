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
//    Copyright 2011 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : GIAInvAttribDlg.cpp
// ^CLASS  : GIAInvAttribDlg
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "giainvattribdlg.h"

#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcombobox.h>
#include <uibase\dstcfuncs.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\giainvattribprocessincludes.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <uibase\DSTGridWnd.h>
#include <uibase\DSTOleDateTime.h>

#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mgmtcooptions.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_GIA_INVEST_ATTRIBS; 
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< GIAInvAttribDlg > dlgCreator( CMD_GUI_GIA_INVEST_ATTRIBS ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME                     = I_("GIAInvAttribDlg");

   const I_CHAR * const INVESTMENT_TYPE_FIX           = I_( "F" );
   const I_CHAR * const INVESTMENT_TYPE_PROGESSIVE    = I_( "P" );
   const I_CHAR * const FORCED_RATE_CONFIG_DERIVED    = I_( "1" );
   const I_CHAR * const FORCED_RATE_FORCED            = I_( "2" );
}

namespace CND
{
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ProgressiveIntRate;
   extern CLASS_IMPORT const BFNumericFieldId ProgressiveInvTerm;
   extern CLASS_IMPORT const BFTextFieldId ProgressiveIntRateDetailsList;
   extern CLASS_IMPORT const BFDateFieldId GIMaturityDate;
   extern CLASS_IMPORT const BFDecimalFieldId ForcedRateAmt;
}

class LVProgressiveIntRateData : public IFDSListCtrlRowDataBase
{
public:
    virtual ~LVProgressiveIntRateData() {}
    DString ProgressiveInvTerm, ProgressiveIntRate;

    virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
    {
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ProgressiveInvTerm, ProgressiveInvTerm, false );
        pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ProgressiveIntRate, ProgressiveIntRate, false );
    }
};

class LVProgressiveIntRateAdapter : public IFDSListCtrlAdapter< LVProgressiveIntRateData >
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
        } else if( *pFieldId == ifds::ProgressiveInvTerm ) {
            double dProgressiveInvTerm1 = DSTCommonFunctions::convertToDouble(pData1->ProgressiveInvTerm);
            double dProgressiveInvTerm2 = DSTCommonFunctions::convertToDouble(pData2->ProgressiveInvTerm);
            result = (dProgressiveInvTerm1 <= dProgressiveInvTerm2 )?-1:1;
        } else if( *pFieldId == ifds::ProgressiveIntRate ) {
            double dProgressiveIntRate1 = DSTCommonFunctions::convertToDouble(pData1->ProgressiveIntRate);
            double dProgressiveIntRate2 = DSTCommonFunctions::convertToDouble(pData2->ProgressiveIntRate);
            result = (dProgressiveIntRate1 <= dProgressiveIntRate2 )?-1:1;
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
            } else if( *pFieldId == ifds::ProgressiveInvTerm ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->ProgressiveInvTerm.c_str();
            } else if( *pFieldId == ifds::ProgressiveIntRate ) {
               pDispInfo->item.pszText = (I_CHAR*)pData->ProgressiveIntRate.c_str();
            }

            return( 1 );
        }
        return( 0 );
    }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
GIAInvAttribDlg::GIAInvAttribDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg( GIAInvAttribDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
,m_dstrCaller(NULL_STRING)
,m_dstrAccountNum (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*****************************************************************************
void GIAInvAttribDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(GIAInvAttribDlg)
   //}}AFX_DATA_MAP
}
//*****************************************************************************
BEGIN_MESSAGE_MAP(GIAInvAttribDlg, BaseMainDlg)
//{{AFX_MSG_MAP(GIAInvAttribDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
SEVERITY GIAInvAttribDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter (ACCOUNT_NUM, m_dstrAccountNum);
   getParameter (CALLER, m_dstrCaller);

   return (NO_CONDITION); /*sevRtn*/
}

//*****************************************************************************
BOOL GIAInvAttribDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog(); 
   
   if (m_dstrCaller == I_("TradeEntry"))
   {
      AddControl ( CTRL_COMBO, IDC_CMB_INVEST_TYPE,    
                   IFASTBP_PROC::TRADE, ifds::IntInvestType, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
      AddControl ( CTRL_EDIT,  IDC_EDT_ADD_AMOUNT,     
                  IFASTBP_PROC::TRADE, ifds::AddlAmt, CTRLFLAG_DEFAULT);
      AddControl ( CTRL_COMBO, IDC_CMB_INT_CALC_TYPE,  
                   IFASTBP_PROC::TRADE, ifds::IntCalcMthd, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
      AddControl ( CTRL_COMBO, IDC_CMB_DEPOSIT_TERM,   
                   IFASTBP_PROC::TRADE, ifds::InvestTerm, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
      AddControl ( CTRL_DATE,  IDC_DTP_INVEST_DATE,    
                   IFASTBP_PROC::TRADE, ifds::EffectiveDate, CTRLFLAG_DEFAULT);
      AddControl ( CTRL_DATE,  IDC_DTP_MATURE_DATE,    
                   IFASTBP_PROC::TRADE, ifds::GIMaturityDate, CTRLFLAG_DEFAULT );
      AddControl ( CTRL_COMBO, IDC_CMB_INT_FREQ,       
                   IFASTBP_PROC::TRADE, ifds::IntCredFreq,
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
      AddControl ( CTRL_DATE,  IDC_DTP_NXT_INVEST_DAY, 
                   IFASTBP_PROC::TRADE, ifds::NextIntCredDate, CTRLFLAG_DEFAULT  );
      AddControl ( CTRL_COMBO, IDC_CMB_FORCED_RATE, IFASTBP_PROC::TRADE, ifds::ForcedRate, 
                   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST );
      AddControl ( CTRL_EDIT,  IDC_EDT_INT_RATE,
                   IFASTBP_PROC::TRADE, ifds::IntRate, CTRLFLAG_DEFAULT  );
      AddControl ( CTRL_COMBO, IDC_CMB_COMM_REDUCTION, 
                   IFASTBP_PROC::TRADE, ifds::CommRedRate, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST );
      AddControl ( CTRL_EDIT, IDC_EDT_FORCED_RATE_AMOUNT, 
                   IFASTBP_PROC::TRADE, ifds::ForcedRateAmt);

      IFDSListCtrl* ifdsListProgressiveIntRate = 
         new IFDSAdaptedListCtrl< LVProgressiveIntRateAdapter >( this, 
                                                                 CLASSNAME, 
                                                                 IDC_LV_INT_RATE_TERM, 
                                                                 0, 
                                                                 LISTFLAG_NOT_AUTO_ADD , 
                                                                 false /*ShowSelAlways*/, 
                                                                 false /*ShowConditions*/);

      AddIFDSListControl( ifdsListProgressiveIntRate, 
                        I_("PROGRESSIVE_INTEREST_RATE"), 
                        IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST, 
                        ifds::ProgressiveIntRateDetailsList );
   }

   return TRUE; 
}
//******************************************************************************
void GIAInvAttribDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   doRefresh (this, NULL);
}

//*****************************************************************************
bool GIAInvAttribDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   ConnectControlsToData ();
   LoadControls ();
   SetDlgCaption ();
   GetControl (IDC_DTP_INVEST_DATE)->Enable (false); //this follows trade date...
   return true;
}

//**********************************************************************************
void GIAInvAttribDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString dstrShrNum, 
      dstrEntityName;

   // Get Entity Name
   if (!m_dstrAccountNum.empty()) 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
         getDataGroupId(), m_dstrAccountNum, dstrEntityName);

   SetShrAcctCaption (dstrShrNum, m_dstrAccountNum, dstrEntityName);
}

//******************************************************************************
void GIAInvAttribDlg::OnCancel()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnCancel"));
   if (getParent()->send (this, I_("Cancel")))
   {
      CDialog::OnCancel();
   }
   else
   {
      // Display error
      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
   }
}

//******************************************************************************
void GIAInvAttribDlg::ControlUpdated(UINT controlID, const DString &strValue )
{
   DString investType;
   getParent()->getField(this, IFASTBP_PROC::TRADE, ifds::IntInvestType,investType,false);
   investType.strip().upperCase();
   switch( controlID )
   {
      case IDC_CMB_INVEST_TYPE:
         if(investType == INVESTMENT_TYPE_PROGESSIVE)
         {
            GetDlgItem ( IDC_LV_INT_RATE_TERM )->ShowWindow ( true );
            ConnectListToData ( IDC_LV_INT_RATE_TERM, true );
            LoadListControl( IDC_LV_INT_RATE_TERM );
         }
         else
         {
            ConnectListToData ( IDC_LV_INT_RATE_TERM, false );
            GetDlgItem ( IDC_LV_INT_RATE_TERM )->ShowWindow ( false );
         }
      break;

      default:
         break;
   }

   if(investType == INVESTMENT_TYPE_PROGESSIVE)
   {
      getParent()->refresh(this, I_(""));
      LoadListControl( IDC_LV_INT_RATE_TERM );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/GIAInvAttribDlg.cpp-arc  $
// 
//    Rev 1.7   Dec 07 2011 16:08:46   dchatcha
// P0186477/FN03 - GIA - Purchase, rewrite logic on modify pending trade by using view 54 instead call to view 421
// 
//    Rev 1.6   Dec 03 2011 11:14:04   dchatcha
// P0186477/FN03 - GIA - Purchase, only show proggressive interest rate list when invest type is progressive and forced is driven by system.
// 
//    Rev 1.5   Dec 03 2011 01:32:06   dchatcha
// P0186477/FN03 - GIA - Purchase
// 
//    Rev 1.4   Dec 01 2011 11:29:08   dchatcha
// P0186477/FN03 - GIA - Purchase, removed estimated rate field from screen.
// 
//    Rev 1.3   Nov 30 2011 17:55:38   dchatcha
// P0186477/FN03 - GIA - Purchase, no need proxy fields anymore
// 
//    Rev 1.2   Nov 30 2011 00:33:22   dchatcha
// P0186477/FN03 - GIA - Purchase
// 
//    Rev 1.1   Nov 27 2011 19:44:16   popescu
// INA Commission Work
// 
// Initial revision.
**/