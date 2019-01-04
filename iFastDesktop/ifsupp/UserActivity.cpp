#pragma warning(disable: 4001)      /* Single-line comment */

#include "stdafx.h"
#include <map>
#include <DString.hpp>
#include <typeinfo>

#include "UserActivity.h"
#include <bf/log/log.hpp>

static HINSTANCE s_hInstDll;
static HHOOK s_hHookCallWndProc;

/**************************************************************** 
  WH_CALLWNDPROC hook procedure 
 ****************************************************************/ 
static bool isDialog( HWND hwnd ) {
	I_CHAR szClassName[256];
	long style = GetClassName( hwnd, szClassName, sizeof(szClassName) - 1 );
   if( i_strcmp( I_("#32770"), szClassName ) == 0 ) {
		return( true );
	}
   return( false );
}

static HWND GetContainingDialog( HWND hwnd, bool bRecurse = true ) 
{
	HWND hwndParent = (HWND)GetWindowLong( hwnd, GWL_HWNDPARENT );
	if( NULL == hwndParent ) {
		return( NULL );
	}
   if( isDialog(hwndParent) ) {
		return( hwndParent );
	}
   if( !bRecurse ) { return NULL; }
	return( GetContainingDialog( hwndParent ) );
}

 
static LRESULT WINAPI CallWndProc(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
    if (nCode < 0)  // do not process message 
        return CallNextHookEx(s_hHookCallWndProc, nCode, wParam, lParam); 
 
	PCWPSTRUCT pCWP = (PCWPSTRUCT)(lParam);
	if( WM_SETFOCUS == pCWP->message ||
		 WM_KILLFOCUS == pCWP->message ) {
		I_CHAR* pszMsg = (pCWP->message == WM_SETFOCUS) ? I_("WM_SETFOCUS") : I_("WM_KILLFOCUS");
		int wid = GetWindowLong( pCWP->hwnd, GWL_ID );
		HWND hwndDlg = GetContainingDialog( pCWP->hwnd );
		I_CHAR szWindowText[256];
      bf::log::LogStream ls( bf::log::gui );
      ls << bf::log::ltrace;
		if( NULL != hwndDlg ) {
			GetWindowText( hwndDlg, szWindowText, sizeof( szWindowText ) / sizeof(szWindowText[0]) );
			ls << pszMsg << I_(" on ") << wid << I_(": ") << szWindowText;
		} else {
			ls << pszMsg << I_(" on ") << wid;
		}

		bf::log::theLog << bf::log::endlf;
	}
   else if( WM_CREATE == pCWP->message ) {
      LPCREATESTRUCT pCS = (LPCREATESTRUCT)(pCWP->lParam);
      if( NULL != pCS &&
          (pCS->style & WS_CAPTION) &&
          NULL != pCS->lpszName ) {
         bf::log::LogStream ls( bf::log::gui );
         ls << bf::log::ltrace;
         ls << I_("Create window ") << pCS->lpszName << bf::log::endlf;
      }
   }
   else if( WM_DESTROY == pCWP->message ) {
      int wStyle = GetWindowLong( pCWP->hwnd, GWL_STYLE );
      if( (wStyle & WS_CAPTION ) ) {
         I_CHAR szTitle[128];
         if( 0 != GetWindowText( pCWP->hwnd, szTitle, sizeof( szTitle ) / sizeof( szTitle[0] ) ) ) {
            bf::log::LogStream ls( bf::log::gui );
            ls << bf::log::ltrace;
            ls << I_("Destroy window ") << szTitle << bf::log::endlf;
         }
      }
   }
   return CallNextHookEx(s_hHookCallWndProc, nCode, wParam, lParam); 
} 

void RegisterUserActivityHooks( HINSTANCE hInstDll ) {
   s_hInstDll = hInstDll;

	s_hHookCallWndProc = 
      SetWindowsHookEx( WH_CALLWNDPROC, 
								CallWndProc,
								s_hInstDll,
								GetCurrentThreadId() );
}
