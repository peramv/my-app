#pragma warning(disable: 4001)      /* Single-line comment */

#include "stdafx.h"
//#include <afxdllx.h>
#include <map>
#include <DString.hpp>
#include <typeinfo>
#include "ifsupp.h"
#include "ControlTextRewriter.h"

static HINSTANCE s_hInstDll;
static HHOOK s_hHookCallWndProc;
static HHOOK s_hHookCallWndProcRet;
static HHOOK s_hHookMouseProc;

typedef std::map<int, std::wstring> ID_TEXT_MAP;
typedef ID_TEXT_MAP::iterator ID_TEXT_MAP_ITER;
typedef std::map<std::wstring, ID_TEXT_MAP*> DLG_TEXT_MAP;
typedef DLG_TEXT_MAP::iterator DLG_TEXT_MAP_ITER;

static DLG_TEXT_MAP s_dlgTextMap;
static HWND s_hwndEdit = NULLHANDLE;
static HWND s_hwndRelated = NULLHANDLE;

static bool s_bEnable = false;
static DString s_dstrPath;

bool ifsupp::EnableControlTextRewriter( const DString& dstrPath ) {
   bool rc = s_bEnable;
   s_dstrPath = dstrPath;
   if( dstrPath == I_("") ) {
      s_bEnable = false;
   } 
   else {
      s_dstrPath += I_("\\");
      s_bEnable = true;
   }
   return rc;
}

static DString getCurrentISOLocale()
{
   DString isoLocale;
   I_CHAR szLanguage[ 64 ];
   I_CHAR szCountry[ 64 ];
   ::GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SISO639LANGNAME, szLanguage, sizeof( szLanguage ) / sizeof( szLanguage[ 0 ] ) );
   ::GetLocaleInfoW( LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, szCountry, sizeof( szCountry ) / sizeof( szCountry[0] ) );

   isoLocale = szLanguage;
   isoLocale += szCountry;
   return( isoLocale );
}

static DString getClassName( const char* pszClassName ) 
{
   if( NULL == pszClassName ) {
     return( DString( I_("NoClass") ) );
   } 
   else if( strlen( pszClassName ) > 6 ) {
     if( 0 == strncmp( pszClassName, "class ", 6 ) ) {
        return( DString( DStringA( pszClassName + 6 ) ) );
     }
   }
   return( DString( DStringA( pszClassName ) ) );
}


static std::wstring getDialogClassName(HWND hwnd) {
   std::string str;

   char szWindowName[256] = "NoClass";
   GetWindowTextA(hwnd,szWindowName,256);
   CWnd* pWnd = CWnd::FromHandle(hwnd);
   if( NULL != pWnd ) {
      try { 
         const char* pszName = typeid(*pWnd).name();
         str = pszName;
      }
      catch( std::bad_typeid& ) 
      {}
   }
   DString dstr = getClassName(str.c_str());
   std::wstring wstr = dstr.c_str();

   return(wstr);
}

static bool isStaticControl( HWND hwnd ) {
	I_CHAR szClassName[256];
	long style = GetClassName( hwnd, szClassName, sizeof(szClassName) - 1 );
	if( i_strcmp( I_("Static"), szClassName ) == 0 ) {
		return( true );
	}
   return( false );
}

static bool isButtonControl( HWND hwnd ) {
	I_CHAR szClassName[256];
	long style = GetClassName( hwnd, szClassName, sizeof(szClassName) - 1 );
	if( i_strcmp( I_("Button"), szClassName ) == 0 ) {
		return( true );
	}
   return( false );
}

static bool isGroupBox( HWND hwnd ) {
	I_CHAR szClassName[256];
	long style = GetClassName( hwnd, szClassName, sizeof(szClassName) - 1 );
	if( i_strcmp( I_("Button"), szClassName ) == 0 ) {
      if( GetWindowLong(hwnd,GWL_STYLE) & BS_GROUPBOX ) {
         return true;
      }
	}
   return( false );
}

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

static bool UpdateControlText( HWND hwndControl, LPTSTR pszText ) {
   int idCtrl = GetWindowLong( hwndControl, GWL_ID );
   if( -1 == idCtrl ) { return false; }   // get containing dialog
   HWND hwndDialog = GetContainingDialog( hwndControl );
   if( NULLHANDLE == hwndDialog ) { return false; }
   // get DLG_TEXT_MAP for dialog
   std::wstring strDlg = getDialogClassName(hwndDialog);
   
   std::wstring strText;
   DLG_TEXT_MAP_ITER it = s_dlgTextMap.find(strDlg);
   if( s_dlgTextMap.end() != it ) {
      ID_TEXT_MAP* pIdTextMap = (*it).second;
      ID_TEXT_MAP_ITER itText = pIdTextMap->find(idCtrl);
      if( pIdTextMap->end() != itText ) {
         (*itText).second = pszText;
         SetWindowText( hwndControl, pszText );
      }
   }

   return true;
}

static bool loadDialogXlateFile( HWND hwndDialog ) {
   // construct name of dialog translation file
   std::wstring dlgName = getDialogClassName(hwndDialog);
   // Some dialog we want to ignore...
   if( dlgName == _T("CWnd") ||
       dlgName == _T("ConditionMessageDialog") ||
       dlgName == _T("PopupMessageDialog") ||
       dlgName == _T("MessageDialog") ||
       dlgName == _T("CFileDialog") ) {
      return true;
   }

   std::wstring xlateFileName = s_dstrPath.c_str();
   xlateFileName += dlgName;
   xlateFileName += _T("_");
   xlateFileName += getCurrentISOLocale().getImp();
   FILE* pXlate = NULL;
   if( (pXlate = i_fopen(xlateFileName.c_str(),_T("r"))) != NULL ) {
      
      ID_TEXT_MAP* p = s_dlgTextMap[dlgName];
      TCHAR szLine[4096];
      while( i_fgets(szLine,sizeof(szLine)/sizeof(szLine[0]),pXlate) != NULL ) {
         int len = i_strlen(szLine);
         if( len >= 1 ) {
            if( szLine[--len] == 0x0a ) {
               szLine[len] = 0x00;
            }
         }
         TCHAR* pszValue = NULL;
         if( (pszValue = i_strchr(szLine,I_('='))) != NULL) {
            (*pszValue++ = 0x00);
         }
         int id = wcstol(szLine,NULL,10);
         if( id > 0 ) {
            ID_TEXT_MAP_ITER it = p->find(id);
            if( it != p->end() ) {
               (*it).second = pszValue;
            }
         }
      }
      fclose(pXlate);
   }
   return true;
}

static bool saveDialogXlateFile( HWND hwndDialog ) {
   // construct name of dialog translation file
   std::wstring dlgName = getDialogClassName(hwndDialog);
   std::wstring xlateFileName = s_dstrPath.c_str();
   xlateFileName += dlgName;
   xlateFileName += _T("_");
   xlateFileName += getCurrentISOLocale().getImp();
   FILE* pXlate = NULL;
   if( (pXlate = i_fopen(xlateFileName.c_str(),_T("w+"))) != NULL ) {
      
      ID_TEXT_MAP* p = s_dlgTextMap[dlgName];
      for( ID_TEXT_MAP_ITER it = p->begin(); it != p->end(); ++it ) {
         int i = (*it).first;
         std::wstring wstr = (*it).second;
         TCHAR szBuf[32];
         i_sprintf(szBuf,_T("%d"),i);

         std::wstring out = szBuf;
         out += _T("=");
         out += wstr;
         out += _T("\n");
         i_fputs(out.c_str(), pXlate);
      }
      fclose(pXlate);
   }
   return true;
}


/**************************************************************** 
  WH_CALLWNDPROC hook procedure 
 ****************************************************************/ 
 
static BOOL isTextRewriteable( HWND hwnd ) {
   // get parent of window
   HWND hwndDialog = GetContainingDialog(hwnd, false);
   if( hwndDialog == NULLHANDLE ) { return FALSE; }
   if( isButtonControl(hwnd) || isStaticControl(hwnd) ) {
      return( true );
   }
   return false;
}

static LRESULT WINAPI CallWndProc(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
   if (nCode < 0)  // do not process message 
      return CallNextHookEx(s_hHookCallWndProc, nCode, wParam, lParam); 
 
   if( ! s_bEnable ) {
      return CallNextHookEx(s_hHookCallWndProc, nCode, wParam, lParam); 
   }

	PCWPSTRUCT pCWP = (PCWPSTRUCT)(lParam);
   if( WM_KILLFOCUS == pCWP->message ) {
      if( (s_hwndEdit != NULLHANDLE) && pCWP->hwnd == s_hwndEdit ) {
         int lenText = GetWindowTextLength( s_hwndEdit );
         TCHAR* pszText = new TCHAR[lenText + 1];
         GetWindowText( s_hwndEdit, pszText, lenText + 1 );
         if( UpdateControlText(s_hwndRelated, pszText) ) {
            SetWindowText(s_hwndRelated, pszText);
         }
         
         delete[] pszText;
         DestroyWindow(s_hwndEdit);
         s_hwndEdit = NULLHANDLE;
         s_hwndRelated = NULLHANDLE;
      }
   }
   else if( WM_DESTROY == pCWP->message ) {
      if( isDialog(pCWP->hwnd) ) {
         saveDialogXlateFile(pCWP->hwnd);
      }
   }
/*
   else if( WM_CTLCOLORSTATIC == pCWP->message ) {
      HDC hdcStatic = (HDC)pCWP->wParam;
      SetTextColor(hdcStatic, RGB(255,0,0));
     
   }
*/
   return CallNextHookEx(s_hHookCallWndProc, nCode, wParam, lParam); 
} 

/**************************************************************** 
  WH_CALLWNDPROCRET hook procedure 
 ****************************************************************/ 
 
static BOOL CALLBACK getChildWindowText( HWND hwnd, LPARAM lParam ) 
{
   ID_TEXT_MAP* pTextMap = (ID_TEXT_MAP*)lParam;
   // is this a static or button?
   if( isButtonControl(hwnd) || isStaticControl(hwnd) ) {
      int id = GetWindowLong(hwnd, GWL_ID);
      TCHAR szWindowText[1024];
      GetWindowText(hwnd, szWindowText, sizeof(szWindowText)/sizeof(szWindowText[0]));
      std::wstring wstr = szWindowText;
      (*pTextMap)[id] = wstr;
   }

   return( TRUE );
}

static LRESULT WINAPI CallWndProcRet(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
   if (nCode < 0)  // do not process message 
      return CallNextHookEx(s_hHookCallWndProcRet, nCode, wParam, lParam); 
 
   if( ! s_bEnable ) {
      return CallNextHookEx(s_hHookCallWndProc, nCode, wParam, lParam); 
   }

	PCWPRETSTRUCT pCWP = (PCWPRETSTRUCT)(lParam);
	if( WM_INITDIALOG == pCWP->message ) {
      // it's a dialog window!

      // create a map and associate it if necessary
      std::wstring str = getDialogClassName(pCWP->hwnd);
      DLG_TEXT_MAP_ITER it = s_dlgTextMap.find(str);
      if( s_dlgTextMap.end() == it ) {
         ID_TEXT_MAP* p = new ID_TEXT_MAP;
         s_dlgTextMap[str] = p;
      }
      ID_TEXT_MAP* pTextMap = s_dlgTextMap[str];
      // enumerate all of the controls in the dialog 
      // grab the text of all static and button type controls and stuff it into the ID_TEXT_MAP
      EnumChildWindows(pCWP->hwnd, getChildWindowText, (LPARAM)pTextMap);

      loadDialogXlateFile(pCWP->hwnd);

      // set the text from the dialog ID_TEXT_MAP list
      for( ID_TEXT_MAP_ITER it = pTextMap->begin(); it != pTextMap->end(); ++it ) {
         int id = (*it).first;
         std::wstring wstr = (*it).second;
         HWND hwndControl = GetDlgItem(pCWP->hwnd, id);
         int lenText = GetWindowTextLength(hwndControl);
         TCHAR* pszText = new TCHAR[lenText+1];
         GetWindowText(hwndControl,pszText,lenText+1);
         if( wstr != pszText ) {
            SetWindowText(hwndControl, wstr.c_str());
         }
      }
	}
   return CallNextHookEx(s_hHookCallWndProcRet, nCode, wParam, lParam); 
} 

/**************************************************************** 
  WH_MOUSEPROC hook procedure 
 ****************************************************************/ 
static HWND GetControlWindow(PMOUSEHOOKSTRUCT pMH) {
   if( isStaticControl(pMH->hwnd) || isButtonControl(pMH->hwnd) ) {
      return pMH->hwnd;
   }
   if( isDialog(pMH->hwnd) ) {
      // grrrr ... find the conrol that the mouse is over
      RECT rect;
      GetWindowRect(pMH->hwnd, &rect);

   }
   return( NULLHANDLE );
}

typedef struct {
   HWND hwndDialog;
   HWND hwndInterest;
   POINT pt;
} FOOZLESTRUCT;

static BOOL CALLBACK FindControlUnderPoint( HWND hwnd, LPARAM lParam ) {
   FOOZLESTRUCT* p = (FOOZLESTRUCT*)lParam;
   if( isStaticControl( hwnd ) ) {
      RECT rect;
      GetWindowRect(hwnd, &rect);
      // is the point within the rect?
      if( p->pt.x >= rect.left && p->pt.y >= rect.top &&
         p->pt.x <= rect.right && p->pt.y <= rect.bottom ) {
         p->hwndInterest = hwnd;
         return( FALSE );
      }
   }
   return( TRUE );
}


static LRESULT WINAPI MouseProc(int nCode, WPARAM wParam, LPARAM lParam) 
{ 
   if (nCode < 0)  // do not process message 
      return CallNextHookEx(s_hHookMouseProc, nCode, wParam, lParam); 
 
   if( ! s_bEnable ) {
      return CallNextHookEx(s_hHookCallWndProc, nCode, wParam, lParam); 
   }

	PMOUSEHOOKSTRUCT pMH = (PMOUSEHOOKSTRUCT)(lParam);
   if( WM_MBUTTONDOWN == wParam ) {
      // is this a control that needs editable static text?
      // some rules about how mouse messages are processed.
      // if the mouse is over a static control then the message is passed to the dialog!
      HWND hwndInterest = pMH->hwnd;
      if( isDialog( hwndInterest ) ) {
         // maybe the mouse is over a static text control?
         POINT pt; pt.x = pMH->pt.x; pt.y = pMH->pt.y;

         ScreenToClient(pMH->hwnd, &pt);
         HWND hwndPoint = ChildWindowFromPointEx(hwndInterest,
                                                 pt,
                                                 CWP_SKIPTRANSPARENT | CWP_SKIPINVISIBLE );

         if( isGroupBox(hwndPoint) ) {
            // urk!  is there a static control under the group box?
            // enumerate the child controls of the parent.  If there is a static or button 
            // under the point then make *that* window the WindowOfInterest
            FOOZLESTRUCT fs; fs.hwndDialog = hwndInterest; fs.hwndInterest = NULLHANDLE; fs.pt.x = pMH->pt.x; fs.pt.y = pMH->pt.y;
            EnumChildWindows(hwndInterest, FindControlUnderPoint, (LPARAM)&fs);
            if( fs.hwndInterest != NULLHANDLE ) {
               hwndInterest = fs.hwndInterest;
            } else {
               hwndInterest = hwndPoint;
            }
         } 
         else {
            if( isStaticControl(hwndPoint) ) {
               hwndInterest = hwndPoint;
            }
            if( isButtonControl(hwndPoint) ) {
               hwndInterest = hwndPoint;
            }
         }
      }
      if( isStaticControl(hwndInterest) || isButtonControl(hwndInterest) ) {
         if( GetKeyState(VK_LCONTROL) ) {
            if( s_hwndEdit != NULLHANDLE ) {
               DestroyWindow(s_hwndEdit);
               s_hwndEdit = NULLHANDLE;
               s_hwndRelated = NULLHANDLE;
            }
/*
            int lenText = GetWindowTextLength(hwndInterest);
            TCHAR* pszText = (TCHAR*)malloc((++lenText)*sizeof(TCHAR));
            GetWindowText(hwndInterest,pszText,lenText);
*/
            HWND hwndParent = (HWND)GetWindowLong(hwndInterest,GWL_HWNDPARENT);
            RECT rectParent;
            GetWindowRect(hwndParent,&rectParent);
            RECT rect;
            GetWindowRect(hwndInterest,&rect);
            DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_NOHIDESEL | ES_AUTOHSCROLL;
            HINSTANCE hInst = GetModuleHandleA(0);
            int x = rect.left - rectParent.left - 5;
            int y = rect.top - rectParent.top - 5;
            int width = rect.right - rect.left;
            int height = 32 /*rect.bottom - rect.top*/;

            int idCtrl = GetWindowLong(hwndInterest, GWL_ID);
            std::wstring strDlg = getDialogClassName(hwndParent);
            
            std::wstring strText;
            DLG_TEXT_MAP_ITER it = s_dlgTextMap.find(strDlg);
            if( s_dlgTextMap.end() != it ) {
               ID_TEXT_MAP* pIdTextMap = (*it).second;
               ID_TEXT_MAP_ITER itText = pIdTextMap->find(idCtrl);
               if( pIdTextMap->end() != itText ) {
                  strText = (*itText).second;
               }
            }


            s_hwndEdit = CreateWindow(_T("Edit"),
                                    strText.c_str(),
                                    style,
                                    x,y,width,height,
                                    hwndParent,(HMENU)777,hInst,NULL);
            s_hwndRelated = hwndInterest;
            /*
            free(pszText);
            */
            SetFocus(s_hwndEdit);
         }
      }
   }
   return CallNextHookEx(s_hHookMouseProc, nCode, wParam, lParam); 
} 

void RegisterControlTextRewriterHooks( HINSTANCE hInstDll ) {
   s_hInstDll = hInstDll;

	s_hHookCallWndProc = 
      SetWindowsHookEx( WH_CALLWNDPROC, 
								CallWndProc,
								s_hInstDll,
								GetCurrentThreadId() );
	s_hHookCallWndProcRet = 
      SetWindowsHookEx( WH_CALLWNDPROCRET, 
								CallWndProcRet,
								s_hInstDll,
								GetCurrentThreadId() );
	s_hHookMouseProc = 
      SetWindowsHookEx( WH_MOUSE, 
				 				MouseProc,
								s_hInstDll,
								GetCurrentThreadId() );
}



