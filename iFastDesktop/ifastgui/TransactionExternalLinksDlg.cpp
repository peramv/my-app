//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial
//
//******************************************************************************
//
// ^FILE   : TransactionExternalLinksDlg.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : August 2004
//
//******************************************************************************
//
// ^CLASS    : TransactionExternalLinksDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#include <bfproc\AbstractProcess.hpp>

#include <ifastcbo\dstcworksession.hpp>

#include "TransactionExternalLinksDlg.h"

#include "ifastbp\TransHistoryProcessIncludes.h"

#include <ifastcbo\DSTCommonFunction.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRANSACTION_EXTERNAL_LINKS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TransactionExternalLinksDlg > dlgCreator( CMD_GUI_TRANSACTION_EXTERNAL_LINKS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TransactionExternalLinksDlg" );
}

namespace ifds
{ 
	extern CLASS_IMPORT const BFTextFieldId TransactionExtLinksHeadingSet;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}




class LVExternalLinksData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVExternalLinksData() {}   
   DString ExternalIdType_;   
   DString ExternalId_;   

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {      
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::ExternalIdType, ExternalIdType_ );
      ExternalIdType_.strip();      
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::ExternalId, ExternalId_ );
      ExternalId_.strip();      
   }
};

class LVExternalLinksAdapter : public IFDSListCtrlAdapter< LVExternalLinksData >
{
public:
   // required overrides
   virtual int compare( IFDSListBase* pCtrl, 
		                  int iSortColumn, 
								bool bAscending, 
                        RowData* pData1, 
								RowData* pData2, 
								LPARAM lParam1, 
								LPARAM lParam2)
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField(iSortColumn - 1);
      if (1 == iSortColumn) 
      {
         // Condition indicator column.  Sort on image index
         result = (IFDSListBase::getColumnLVItem(lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem(lParam2, iSortColumn - 1)->iImage);
      } 
      else if (NULL == pFieldId) 
      {
         return (0);
      }       
		else if (*pFieldId == ifds::ExternalIdType ) 
      {
         result = i_strcmp(pData1->ExternalIdType_.c_str(), pData2->ExternalIdType_.c_str());
      }       
      else if (*pFieldId == ifds::ExternalId ) 
      {
         result = i_strcmp(pData1->ExternalId_.c_str(), pData2->ExternalId_.c_str());
      }       
      return (bAscending ? result : -result);
   }

   virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
   {
      if (pDispInfo->item.mask & LVIF_TEXT)
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);

         if (NULL == pFieldId) 
         {
            pDispInfo->item.pszText = I_("");
         }          
         else if (*pFieldId == ifds::ExternalIdType) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ExternalIdType_.c_str();
         }          
         else if (*pFieldId == ifds::ExternalId )
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ExternalId_.c_str();
         }          
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
TransactionExternalLinksDlg::TransactionExternalLinksDlg( CWnd* pParent, 
																			 GenericInterfaceContainer* pGIC, 
                                                          GenericInterface* pGIParent, 
																			 const Command& rCommand )
: BaseMainDlg( TransactionExternalLinksDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	getParameter( I_( "TransNum" ),       _dstrTransNum);
	getParameter( I_( "AccountNum" ),     _dstrAccountNum );
	getParameter( I_( "ShareholderNum" ), _dstrShareholderNum );

   //{{AFX_DATA_INIT(TransactionExternalLinksDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void TransactionExternalLinksDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TransactionExternalLinksDlg)
   //}}AFX_DATA_MAP

}

//*****************************************************************************
SEVERITY TransactionExternalLinksDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
  		
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP( TransactionExternalLinksDlg, BaseMainDlg )
//{{AFX_MSG_MAP(TransactionExternalLinksDlg)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL TransactionExternalLinksDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   return(TRUE);
}

//*****************************************************************************
void TransactionExternalLinksDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG ); 
	
	IFDSListCtrl* pTransactionExternalLinksListCtrl = 
      new IFDSAdaptedListCtrl< LVExternalLinksAdapter >( this, 
		                                                      CLASSNAME, 
                                                            IDC_LV_TRANSACTION_HISTORY_EXTERNAL_LINKS, 
																				0, 
																				0, 
																				true, 
																				true );

   AddIFDSListControl( pTransactionExternalLinksListCtrl, 
							  I_( "Transaction External Links" ), 
	  					     IFASTBP_PROC::TRANSACTION_EXTERNAL_LINKS_LIST, 
                       ifds::TransactionExtLinksHeadingSet );

	// Default the sorting column to External Type ID
	if ( NULL != pTransactionExternalLinksListCtrl )		
		pTransactionExternalLinksListCtrl->SortOnColumn( 2 );

   doRefresh( this, NULL_STRING );
}

//******************************************************************************
bool TransactionExternalLinksDlg::doRefresh( GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

	ConnectListToData( IDC_LV_TRANSACTION_HISTORY_EXTERNAL_LINKS, true );
   
	// External Links List
   if( getParent()->getFirstListItemKey( this, IFASTBP_PROC::TRANSACTION_EXTERNAL_LINKS_LIST ) != NULL_STRING )
	{
		LoadListControl( IDC_LV_TRANSACTION_HISTORY_EXTERNAL_LINKS );
	}

   SetDlgCaption();

   return true;
}

//*************************************************************************
void TransactionExternalLinksDlg::SetDlgCaption()
{ 						 
	DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
                                                                                                    _dstrAccountNum,
																																    dstrEntityName);		 	
	DString dstrDlgCaption;
	CString cstrExtLinksTrans,cstrShareHolder,cstrAcct;
	cstrExtLinksTrans.LoadString(TXT_EXTERNAL_LINKS_FOR_TRANSACTION);
	cstrShareHolder.LoadString(TXT_SHARE_HOLDER);
	cstrAcct.LoadString(TXT_ACCOUNT);
	dstrDlgCaption = DString(cstrExtLinksTrans) + _dstrTransNum
		            + DString(cstrShareHolder) + _dstrShareholderNum
		            + DString(cstrAcct) + _dstrAccountNum						
						+ I_( "; " ) + dstrEntityName;
	
	SetWindowText( dstrDlgCaption.c_str() );		 
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionExternalLinksDlg.cpp-arc  $
// 
//    Rev 1.5   Nov 19 2011 01:46:58   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.4   Sep 15 2005 15:15:52   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Sep 21 2004 10:55:20   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.2   Sep 16 2004 09:17:46   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.1   Sep 07 2004 15:37:04   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.0   Aug 30 2004 16:37:56   VADEANUM
// Initial revision.
//
