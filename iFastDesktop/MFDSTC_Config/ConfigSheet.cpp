// ConfigSheet.cpp : implementation file
//

#include "stdafx.h"
#include "MFDSTC_Config.h"
#include "ConfigSheet.h"
#include ".\configsheet.h"


// CConfigSheet

IMPLEMENT_DYNAMIC(CConfigSheet, CPropertySheet)
CConfigSheet::CConfigSheet(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(_T(""), pParentWnd, iSelectPage)
{
   AddPage(&GeneralPage_);
   AddPage(&SonicPage_);
   AddPage(&SupportPage_);
   AddPage(&SpecialPage_);
}


CConfigSheet::~CConfigSheet()
{
}


BEGIN_MESSAGE_MAP(CConfigSheet, CPropertySheet)
END_MESSAGE_MAP()


// CConfigSheet message handlers

void CConfigSheet::OnUpdate(CView* pView, LPARAM lHint, CObject* pHint)
{
   if( pHint != NULL ) {
      GeneralPage_.OnUpdate(pView, lHint, pHint);
      SonicPage_.OnUpdate(pView, lHint, pHint);
      SupportPage_.OnUpdate(pView, lHint, pHint);
      SpecialPage_.OnUpdate(pView, lHint, pHint);
   }
}

bool CConfigSheet::isUpdated(void)
{
   if( GeneralPage_.isChanged() ) {
      return true;
   }
   if( SonicPage_.isChanged() ) {
      return true;
   }
   if( SupportPage_.isChanged() ) {
      return true;
   }
   if( SpecialPage_.isChanged() ) {
      return true;
   }
   return false;
}

BOOL CConfigSheet::SaveToDoc(void)
{
   GeneralPage_.SaveToDoc();
   SonicPage_.SaveToDoc();
   SupportPage_.SaveToDoc();
   SpecialPage_.SaveToDoc();
   return TRUE;
}

BOOL CConfigSheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
   LPNMHDR pnmhd = (LPNMHDR)lParam;

   // Item change event
   if( pnmhd->code == TCN_SELCHANGING ) {
      int iTab = TabCtrl_GetCurSel( pnmhd->hwndFrom );
      switch( iTab ) {
         case 0:  // General Tab
            if( GeneralPage_.ValidateData() ) {
               return( FALSE );
            }
            else {
               *pResult = 1;
               return( TRUE );
            }
            break;
         case 1:  // Sonic Tab
            if( SonicPage_.ValidateData() ) {
               return( FALSE );
            }
            else {
               *pResult = 1;
               return( TRUE );
            }
            break;
         case 2:  // Support Tab
            break;
         case 3:  // Special Tab
            break;
      }
   }
   return CPropertySheet::OnNotify(wParam, lParam, pResult);
}


BOOL CConfigSheet::PreTranslateMessage(MSG* pMsg)
{
   WPARAM key = pMsg->wParam;
   if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0 &&
      (key == VK_TAB || key == VK_PRIOR || key == VK_NEXT)) {
      CTabCtrl* pTabCtrl = GetTabControl();
      int iTab = TabCtrl_GetCurSel( pTabCtrl->GetSafeHwnd() );
      switch( iTab ) {
         case 0:  // General Tab
            if( !GeneralPage_.ValidateData() ) {
               return( TRUE );
            }
            break;
         case 1:  // Sonic Tab
            if( !SonicPage_.ValidateData() ) {
               return( TRUE );
            }
            break;
         case 2:  // Support Tab
            break;
         case 3:  // Special Tab
            break;
      }
   }

   return CPropertySheet::PreTranslateMessage(pMsg);
}
