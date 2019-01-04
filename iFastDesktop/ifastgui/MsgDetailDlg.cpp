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
// ^FILE   : MsgDetailDlg.cpp
// ^CLASS  : MsgDetailDlg
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "MsgDetailDlg.h"
#include <ifastcbo\dstcworksession.hpp>
#include <configmanager.hpp>
#include <uibase\dstcombobox.h>
#include <uibase\ifdslistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\MsgDetailProcessIncludes.h>
#include <uibase\dstedit.h>
#include <bfproc\abstractprocess.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MSG_DETAIL;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MsgDetailDlg > dlgCreator( CMD_GUI_MSG_DETAIL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("MsgDetailDlg");
   const I_CHAR * const LV_MESSAGE  = I_( "Message" );
}


class LVMessageData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVMessageData() {}
   DString MsgID_, MsgType_, MsgSegment_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MsgID, MsgID_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MsgType, MsgType_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MsgSegment, MsgSegment_ );
   }
};

class LVMessageAdapter : public IFDSListCtrlAdapter< LVMessageData >
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
      } else if( *pFieldId == ifds::MsgID ) {
         result = i_strcmp( pData1->MsgID_.c_str(), pData2->MsgID_.c_str() );
      } else if( *pFieldId == ifds::MsgType ) {
         result = i_strcmp( pData1->MsgType_.c_str(), pData2->MsgType_.c_str() );
      } else if( *pFieldId == ifds::MsgSegment ) {
         double dMsgSegment1 = DSTCommonFunctions::convertToDouble( pData1->MsgSegment_ );
         double dMsgSegment2 = DSTCommonFunctions::convertToDouble( pData2->MsgSegment_ );
         result = ( dMsgSegment1 == dMsgSegment2) ? 0 : ( dMsgSegment1 < dMsgSegment2 ? -1 : 1 );
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
         } else if( *pFieldId == ifds::MsgID ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->MsgID_.c_str();
         } else if( *pFieldId == ifds::MsgType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->MsgType_.c_str();
         } else if( *pFieldId == ifds::MsgSegment ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->MsgSegment_.c_str();
         } 
         return( 1 );
      }
      return( 0 );
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************

MsgDetailDlg::MsgDetailDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( MsgDetailDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(MsgDetailDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************

void MsgDetailDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(MsgDetailDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(MsgDetailDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MsgDetailDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL MsgDetailDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//******************************************************************************

void MsgDetailDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   IFDSListCtrl* ifdsListControlMessage = new IFDSAdaptedListCtrl< LVMessageAdapter >( this, CLASSNAME, IDC_LV_MSG_PROCESSES, 0, 0, true, true );
   AddIFDSListControl( ifdsListControlMessage, LV_MESSAGE, IFASTBP_PROC::MSG_DETAIL_LIST, ifds::MsgDetailHeading );   
   AddControl( CTRL_EDIT, IDC_EDT_MSG_SEGMENT, IFASTBP_PROC::MSG_DETAIL_LIST, ifds::MsgData, CTRLFLAG_WORD_WRAP, IDC_LV_MSG_PROCESSES );
   LoadListControl( IDC_LV_MSG_PROCESSES );
}

//*****************************************************************************

bool MsgDetailDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return( true );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/MsgDetailDlg.cpp-arc  $
// 
//    Rev 1.1   Sep 15 2005 15:14:06   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.0   Feb 21 2005 09:59:04   hernando
// Initial revision.
