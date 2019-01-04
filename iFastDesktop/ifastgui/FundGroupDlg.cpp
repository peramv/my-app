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
// ^FILE   : FundGroupDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : FundGroupDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************
#include "stdafx.h"

#include "MFDSTC.h"
#include "resource.h"
#include "FundGroupDlg.h"
#include <ifastbp\FundGroupProcessIncludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <bfproc\BPGlobal.h>
#include <bfdata\bfdatafieldproperties.hpp>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <uibase\DSTListCtrl.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FUNDGROUP;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FundGroupDlg > dlgCreator( CMD_GUI_FUNDGROUP );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME    = I_( "FundGroupDlg" );
   const I_CHAR *LV_FundGroup = I_( "FundGroupList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundSponsorsHeading; // When possible, we'll rename this in DD and here.
	extern CLASS_IMPORT const BFTextFieldId FundGroupHeading;
}

namespace CND
{
   extern const long GUI_ERR_DATA_NOT_FOUND;
}

/*
class LVFundGroupData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFundGroupData() {}
   DString fundGroupCode_;
   DString fundGroupDesc_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundGroup, fundGroupCode_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GroupName, fundGroupDesc_ );
   }
};

class LVFundGroupAdapter : public IFDSListCtrlAdapter< LVFundGroupData >
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
      } else if( *pFieldId == ifds::FundGroup ) {
         result = i_strcmp( pData1->fundGroupCode_.c_str(), pData2->fundGroupCode_.c_str() );
      } else if( *pFieldId == ifds::GroupName ) {
         result = i_strcmp( pData1->fundGroupDesc_.c_str(), pData2->fundGroupDesc_.c_str() );
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
         } else if( *pFieldId == ifds::FundGroup ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundGroupCode_.c_str();
         } else if( *pFieldId == ifds::GroupName ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->fundGroupDesc_.c_str();
         }
         return( 1 );
      }
      return( 0 );
   }
};
*/
/////////////////////////////////////////////////////////////////////////////
// FundGroupDlg dialog


FundGroupDlg::FundGroupDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FundGroupDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(FundGroupDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

FundGroupDlg::~FundGroupDlg()
{
}


//******************************************************************************

BOOL FundGroupDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*****************************************************************************
SEVERITY FundGroupDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter(MFCAN_IP_PARAM::SPONSOR_GROUP, m_dstrSponsorGroup);
   return(NO_CONDITION);
}
//******************************************************************************

void FundGroupDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   /*IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVFundGroupAdapter >
         ( this, CLASSNAME, IDC_LIST1, 0, LISTFLAG_NOT_UPDATABLE, true, true ); 

   AddIFDSListControl( pCtrl, 
                       LV_FundGroup,
                       IFASTBP_PROC::FUNDGROUP_LIST,
                       ifds::FundSponsorsHeading ); */  // When possible, we'll rename this in DD and here.

	CString cstrCommString;

	if ( m_dstrSponsorGroup == I_("GROUP") )
	{

		cstrCommString.LoadString(TXT_FUND_GROUP);
		
		AddListControl( CLASSNAME, IDC_LIST1, I_("FUNDSPONSOR"), ifds::FundGroupHeading, 
							IFASTBP_PROC::FUNDGROUP_LIST, 0 ); 
	}
	else if ( m_dstrSponsorGroup == I_("SPONSOR") )
	{
		cstrCommString.LoadString(TXT_FUND_SPONSOR);

		AddListControl( CLASSNAME, IDC_LIST1, I_("FUNDSPONSOR"), ifds::FundSponsorsHeading, 
							IFASTBP_PROC::FUNDGROUP_LIST, 0 ); 
	}

	SetWindowText( cstrCommString );
   ConnectControlsToData();
   LoadListControl( IDC_LIST1 );   
}

//*****************************************************************************

void FundGroupDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(FundGroupDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(FundGroupDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FundGroupDlg)
// NOTE: the ClassWizard will add message map macros here
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************

void FundGroupDlg::OnDblclkList( NMHDR* pNMHDR, LRESULT* pResult ) 
{
   PostMessage( WM_COMMAND, IDOK );
   *pResult = 0;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/FundGroupDlg.cpp-arc  $
// 
//    Rev 1.3   Nov 24 2011 15:51:14   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.2   Nov 01 2006 11:19:00   ZHANGCEL
// PET2217 FN26 -- Add a logic to pop up FundSponsor list with <F4>
// 
//    Rev 1.1   Sep 15 2005 15:13:06   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.0   Sep 21 2004 16:47:14   HERNANDO
// Initial revision.

