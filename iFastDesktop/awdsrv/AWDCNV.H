        // WINDOWS REDEFINES

#ifndef AWDCNV

#define AWDCNV 1

#define LIT_END (-1)
#define BOOL unsigned short
#define CHAR char
#define USHORT unsigned short
#define UCHAR char
#define ULONG unsigned long
#define SHORT int
#define INT   int
#define PVOID void*
#define PSZ LPSTR
#define PUCHAR char*
#define HAB HANDLE
#define PCHAR char*
#define PFNWP FARPROC
#define PUSHORT USHORT*
#define PULONG  ULONG*
#define HPOINTER HANDLE
#define PFN FARPROC
#define APIRET LONG
#define HPS HANDLE
#define NULLHANDLE NULL
#define HEV HANDLE
#define PID int
#define PBOOL  BOOL*
#define PLONG  long*
#define CCHMAXPATH 260
#define HMODULE  HINSTANCE
//   #define NO_ERROR 0
#define MBID_ERROR 1
#ifndef DID_OK
  #define DID_OK     IDOK
#endif
#ifndef DID_CANCEL
  #define DID_CANCEL IDCANCEL
#endif
#define MPARAM LPARAM
#define MRESULT LRESULT

#define PVOIDFROMMP(mp) ((void *)(mp))
#define MPFROMP(p) ((LPARAM)p)
#define MPFROM2SHORT MAKELONG
#define PRECORDCORE  LPRECORDCORE
#define WM_CONTROL   WM_COMMAND
#define LN_SELECT    LBN_SELCHANGE
#define LN_ENTER     LBN_DBLCLK
#define WinInsertLboxItem( hwnd, usindex, psztext ) SendMessage( hwnd, LB_INSERTSTRING, (WPARAM) usindex, (LPARAM) psztext )
#define WinDeleteLboxItem( hwnd, usindex ) SendMessage( hwnd, LB_DELETESTRING, (WPARAM) usindex, 0L )
#define WinDeleteAllLboxItems( hwnd ) SendMessage( hwnd, LB_RESETCONTENT, 0, 0L )
#define WinQueryLboxItemText( hwnd, usindex, psztext, uslen ) SendMessage( hwnd, LB_GETTEXT, usindex, (LPARAM) psztext )

#define WinQueryWindowPtr                    GetWindowLong
#define WinQueryWindowULong                  GetWindowLong
#define WinSetWindowULong                    SetWindowLong
#define WinSetWindowPtr                     SetWindowLong

#define QWL_USER DWL_USER
#define QWL_STYLE GWL_STYLE

#define WinWindowFromID( hwnd, usid ) GetDlgItem( hwnd, usid )
#define LIT_NONE  LB_ERR
#define WinQueryLboxSelectedItem( hwnd, id ) SendDlgItemMessage( hwnd, id, LB_GETCURSEL, 0, 0L )
#define WinQueryLboxCount( hwnd, id ) SendDlgItemMessage( hwnd, id, LB_GETCOUNT, 0, 0L )
#define WinSelectLboxItem( hwnd, i, b ) SendMessage( hwnd, LB_SELITEMRANGE, b, MAKELPARAM(i, i))

#define CLEAR_VCB(x) memset( &x, 0x00, sizeof( x ) )

#define WinWindowFromID( hwnd, usid ) GetDlgItem( hwnd, usid )
#define WinEnableWindow( hwnd, bool ) EnableWindow( hwnd, bool )
#define WinEnableControl( hwnd, id, bool ) EnableWindow( WinWindowFromID(hwnd, id), bool )
#define WinSetTextLimit(hwnd, id, size) SendDlgItemMessage(hwnd, id, EM_LIMITTEXT, (WPARAM)size, 0L)
#define WinSetDlgItemText(hwnd, id, sz) SetDlgItemText(hwnd, id, sz)
#define WinQueryDlgItemText(hwnd, id, l, sz) GetDlgItemText(hwnd, id, sz, l)
#define WinCheckButton(hwnd, id, b) CheckDlgButton(hwnd, id, b)
#define WinQueryCheckButton(hwnd, id) IsDlgButtonChecked(hwnd, id)

#define WinPostMsg( hwnd, msg, mp1, mp2 ) PostMessage( hwnd, msg, mp1, mp2 )
#define WinSetLboxItemData(hwnd, id, i, p) SendMessage(GetDlgItem(hwnd, id), LB_SETITEMDATA, (WPARAM)i, (LPARAM)p)
#define WinQueryLboxItemData(hwnd, id, i) SendMessage(GetDlgItem(hwnd, id), LB_GETITEMDATA, (WPARAM)i, 0L)
#define WinDefWindowProc DefWindowProc
#define WinQueryWindowText( hwnd, sSize, szBuffer ) GetWindowText( hwnd, szBuffer, sSize )
#define WinLoadString( hab, hmod, ids, cb, psz) LoadString(hmod, ids, psz, cb)
#define WinQueryAnchorBlock(hwnd) NULL
#define WinSetWindowText SetWindowText
#define WinSendMsg SendMessage
#define WinDefDlgProc DefDlgProc
#define WinShowWindow(hwnd, i)   ShowWindow(hwnd, i)

#define SetActiveWindow                         SetFocus

#define MB_CUACRITICAL  MB_ICONEXCLAMATION
#define MB_WARNING      MB_ICONEXCLAMATION
#define MB_ERROR        MB_ICONEXCLAMATION
#define MB_MOVEABLE     0

#define WinMessageBox(hwndParent, hwndOwner, msg, title, i, style) MessageBox(hwndParent, msg, title, style)
#define WinDestroyWindow(hwnd) DestroyWindow(hwnd)
#define WinDismissDialog(hwnd) DestroyWindow(hwnd)
#define WinDismissDlg(hwnd, rc) EndDialog(hwnd, rc); WinDestroyWindow(hwnd)
#define DosDelete(sz) remove(sz)

#define WinInvalidateRegion   InvalidateRgn
/* yingbao comment out
#ifndef EXPENTRY
  #define EXPENTRY _export
#endif
  
  yingbao comment end
  */
//#ifndef APIENTRY
//  #define APIENTRY _export
//#endif

#define OBOOL ULONG                    // 4 byte bool for os/2 compat

/*Û#define°HENUM°°PXLIST°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°Û 03-29-94 08:06 Û*/
/*Û#define°WinBeginEnumWindows(°hwndCsd°)°CsdBeginEnumWindows(°hwndCsd°)°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°Û 03-29-94 08:06 Û*/
/*Û#define°WinGetNextWindow(°hEnum°)°°°°°°CsdGetNextWindow(°hEnum°)°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°Û 03-29-94 08:06 Û*/
/*Û#define°WinEndEnumWindows(°hEnum°)°°°°°CsdEndEnumWindows(°hEnum°)°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°Û 03-29-94 08:06 Û*/

#define WM_INITDLG           WM_INITDIALOG
#define WM_QUERYDLGCODE      WM_GETDLGCODE
#define DLGC_ENTRYFIELD      DLGC_WANTALLKEYS
#define ES_MARGIN            ES_READONLY

#define WinRemoveMenuItem( hwnd, id ) DeleteMenu( GetMenu(hwnd), id, MF_BYCOMMAND )

#define AWD_USER \
      ( sizeof( FARPROC ) + sizeof( int ) \
      + sizeof( int ) )

typedef struct _doubleptr
 {
  PVOID  pThing1;
  PVOID  pThing2;
 } DOUBLEPTR, *PDOUBLEPTR;

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AWDCNV.H-arc  $
//
//   Rev 1.1   Nov 08 2005 14:15:02   yingbaol
//PET1332,FN09: remove DString and infra structure
//
//   Rev 1.0   Oct 31 2005 15:06:36   yingbaol
//Initial revision.
 * 
 *

 */





