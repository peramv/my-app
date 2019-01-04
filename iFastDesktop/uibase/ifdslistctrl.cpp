
#include "stdafx.h"
#include <dstring.hpp>
#include "ifdslistctrl.h"
#include "popupmessageres.h"
#include <bfdata\bfsubstitutionset.hpp>
#include <bfdata\bffieldid.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <configmanager.hpp>
#include <sstream>
#include <xutility>

#include <uibase\dstmsg.h>
#include <uibase\basedlg.h>


/*** Defines not yet available in MS VC++ 6.0 ********************************/
#ifndef HDF_SORTUP
   #define HDF_SORTUP 0x0400
#endif
#ifndef HDF_SORTDOWN
   #define HDF_SORTDOWN 0x0200
#endif
#ifndef IDC_HAND
   #define IDC_HAND MAKEINTRESOURCE(32649)
#endif

const int colorWindowText = COLOR_WINDOWTEXT;
const int colorHighlightText = COLOR_HIGHLIGHTTEXT;
const int colorReallySelected = COLOR_HIGHLIGHT;
// the current practice at IFDS if for ListView control items to display as 'selected'
// even if they are just in focus.  Also, we use the same highlight color even if the
// control has keyboard focus or not.  We should look at changing to a more user-friendly
// approach which uses a different highlight background color when the control has keyboard
// focus or not
//     CP 01Oct2003
//CP20031001const int colorAlwaysSelected = COLOR_3DFACE;
const int colorAlwaysSelected = COLOR_HIGHLIGHT;
const int colorInFocus = COLOR_HIGHLIGHT;
const int colorHotlight = COLOR_HOTLIGHT;
const int colorGrayText = COLOR_GRAYTEXT;

extern HINSTANCE g_hinstDLL;

namespace
{
   const I_CHAR* CLASSNAME = I_( "IFDSListCtrl " );
   const DString WORKSTATION( I_( "WORKSTATION" ) );
}

const DString IFDSListCtrl::s_strEmpty_( I_( "" ) );

int IFDSListBase::ITEM_DATA::s_iInsert_ = 0;

/*** Definition of class "IFDSListCtrl" ***************************************/

/*** Public Member functions *************************************************/
IFDSListCtrl::~IFDSListCtrl()
{
   delete pToolTip_;
   pToolTip_ = NULL;
}

/*** Protected member functions **********************************************/

/*** A column header has been clicked ****************************************/
BOOL IFDSListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
   return(IFDSListBase::OnColumnclick(pNMHDR, pResult));
}

/*** An item in the column selection menu has been selected ******************/
BOOL IFDSListCtrl::OnCommand(WPARAM wParam, LPARAM)
{
   return(IFDSListBase::OnCommand(wParam));
}

/*** The user has right clicked the mouse ************************************/
void IFDSListCtrl::OnContextMenu(CWnd* pWnd, CPoint) 
{
   IFDSListBase::OnContextMenu(pWnd);
}

/*** A list view (sub)item will be drawn *************************************/
void IFDSListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
   IFDSListBase::OnCustomDraw(pNMHDR, pResult);
}

/*** All items from a list view control will be removed **********************/
LRESULT IFDSListCtrl::OnDeleteAllItems(WPARAM, LPARAM)
{
   LRESULT lr;
   SetDeleting( true );
   lr = IFDSListBase::OnDeleteAllItems();
   SetDeleting( false );
   return( lr );
}

/*** A column in a list view control will be deleted *************************/
LRESULT IFDSListCtrl::OnDeleteColumn(WPARAM wParam, LPARAM)
{
   return(IFDSListBase::OnDeleteColumn(wParam));
}

/*** An item from a list view control will be removed ************************/
LRESULT IFDSListCtrl::OnDeleteItem(WPARAM wParam, LPARAM)
{
   return(IFDSListBase::OnDeleteItem(wParam));
}

/*** The list view control will be destroyed *********************************/
void IFDSListCtrl::OnDestroy() 
{
   saveState( m_strDialogName, m_strListName );
//CP20030820   SetDeleting( true );
   IFDSListBase::OnDestroy();
//CP20030820   SetDeleting( false );
}

/*** The background will be erased *******************************************/
BOOL IFDSListCtrl::OnEraseBkgnd(CDC* pDC) 
{
   return(IFDSListBase::OnEraseBkgnd(pDC));
}

/*** A specific item of a list view control will be searched *****************/
LRESULT IFDSListCtrl::OnFindItem(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnFindItem(wParam, lParam));
}

/*** The attributes of a list view control's column will be retrieved ********/
LRESULT IFDSListCtrl::OnGetColumn(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnGetColumn(wParam, lParam));
}

/*** The current left-to-right order of columns in a list view control *******/
/*** will be retrieved                                                 *******/
LRESULT IFDSListCtrl::OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnGetColumnOrderArray(wParam, lParam));
}

/*** The width of a column in a list view control will be retrieved **********/
LRESULT IFDSListCtrl::OnGetColumnWidth(WPARAM wParam, LPARAM)
{
   return(IFDSListBase::OnGetColumnWidth(wParam));
}

/*** Information needed to display a list view item **************************/
BOOL IFDSListCtrl::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
   return(IFDSListBase::OnGetdispinfo(pNMHDR, pResult));
}

/*** The extended list view style will be retrieved **************************/
LRESULT IFDSListCtrl::OnGetExtendedStyle(WPARAM, LPARAM)
{
   return(dwExtendedStyle_);
}

/*** Some or all of a list view item's attributes will be retrieved **********/
LRESULT IFDSListCtrl::OnGetItem(WPARAM, LPARAM lParam)
{
   return(IFDSListBase::OnGetItem(lParam));
}

/*** The text of a list view item or subitem will be retrieved ***************/
LRESULT IFDSListCtrl::OnGetItemText(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnGetItemText(wParam, lParam));
}

/*** The list-view item at a specified position will be determined ***********/
LRESULT IFDSListCtrl::OnHitTest(WPARAM, LPARAM lParam)
{
   return(IFDSListBase::OnHitTest(lParam));
}

/*** List control has been scrolled horizontally *****************************/
void IFDSListCtrl::OnHScroll(UINT, UINT, CScrollBar*)
{
   IFDSListBase::OnHScroll();
}

/*** A new column in a list-view control will be inserted ********************/
LRESULT IFDSListCtrl::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnInsertColumn(wParam, lParam));
}

/*** A new item in a list-view control will be inserted **********************/
LRESULT IFDSListCtrl::OnInsertItem(WPARAM, LPARAM lParam)
{
   return(IFDSListBase::OnInsertItem(lParam));
}

/*** A key has been pressed  *************************************************/
void IFDSListCtrl::OnKeyDown(UINT nChar, UINT, UINT) 
{
   IFDSListBase::OnKeyDown(nChar);

   switch( nChar )
   {
      case VK_F11:
         ToggleToolTip();
         break;
   }

}

/*** A key has been released *************************************************/
void IFDSListCtrl::OnKeyUp(UINT nChar, UINT, UINT) 
{
   IFDSListBase::OnKeyUp(nChar);
}

/*** List control loses input focus ******************************************/
void IFDSListCtrl::OnKillFocus(CWnd*) 
{
   if( ToolTipExists() )
   {  // Hide tooltip, if showing
      GetToolTip()->ShowMsg( false );
   }
   IFDSListBase::OnKillFocus();
}

/*** The user double-clicks the left mouse button ****************************/
void IFDSListCtrl::OnLButtonDblClk(UINT, CPoint point) 
{
   IFDSListBase::OnLButtonDblClk(point);
}

/*** The user presses the left mouse button **********************************/
void IFDSListCtrl::OnLButtonDown(UINT, CPoint point) 
{
   IFDSListBase::OnLButtonDown(point);
}

/*** The user releases the left mouse button *********************************/
void IFDSListCtrl::OnLButtonUp(UINT, CPoint) 
{
   IFDSListBase::OnLButtonUp();
}

/*** The mouse has been moved ************************************************/
void IFDSListCtrl::OnMouseMove(UINT, CPoint point) 
{
   IFDSListBase::OnMouseMove(point);

   // Do we need to show the tooltip?
//   if( /*IsError() &&*/ !IsToolTipVisible() )
   {
      UINT flags;
      int  iItem = HitTest(point, &flags);
      if( -1 < iItem ) 
      {
         CONDITIONVECTOR vConditions;
         if( getItemConditions( iItem, vConditions ) >= WARNING )
         {
            TriggerToolTip( iItem );
         }
      }
   }
}

/*** Divider in header control has been dragged ******************************/
BOOL IFDSListCtrl::OnNotify(WPARAM, LPARAM lParam, LRESULT*)
{
   return(IFDSListBase::OnNotify(lParam));
}

/*** The background color of the list view control will be set ***************/
LRESULT IFDSListCtrl::OnSetBkColor(WPARAM, LPARAM)
{
   return(IFDSListBase::OnSetBkColor());
}

/*** The attributes of a list view column will be set ************************/
LRESULT IFDSListCtrl::OnSetColumn(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnSetColumn(wParam, lParam));
}

/*** The left-to-right order of columns in a list view control will be set ***/
LRESULT IFDSListCtrl::OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnSetColumnOrderArray(wParam, lParam));
}

/*** The width of a column in a list view control will be changed ************/
LRESULT IFDSListCtrl::OnSetColumnWidth(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnSetColumnWidth(wParam, lParam));
}

/*** The extended list view style will be set ********************************/
LRESULT IFDSListCtrl::OnSetExtendedStyle(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnSetExtendedStyle(wParam, lParam));
}

/*** List control gains input focus ******************************************/
void IFDSListCtrl::OnSetFocus(CWnd*) 
{
   ShowToolTip( GetNextItem(-1, LVNI_SELECTED) );
   IFDSListBase::OnSetFocus();
}

/*** An image list will be assigned ******************************************/
LRESULT IFDSListCtrl::OnSetImageList(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnSetImageList(wParam, lParam));
}

/*** Some or all of a list view item's attributes will be set ****************/
LRESULT IFDSListCtrl::OnSetItem(WPARAM, LPARAM lParam)
{
   return(IFDSListBase::OnSetItem(lParam));
}

/*** The text of an item or a subitem in a list view control will be changed */
LRESULT IFDSListCtrl::OnSetItemText(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnSetItemText(wParam, lParam));
}

/*** The items of a list view control will be sorted *************************/
LRESULT IFDSListCtrl::OnSortItems(WPARAM wParam, LPARAM lParam)
{
   return(IFDSListBase::OnSortItems(wParam, lParam));
}

/*** System colors have been changed *****************************************/
void IFDSListCtrl::OnSysColorChange()
{
   IFDSListBase::OnSysColorChange();
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(IFDSListCtrl, DSTListCtrl)
//{{AFX_MSG_MAP(IFDSListCtrl)
ON_WM_SYSCOLORCHANGE()
ON_WM_ERASEBKGND()
ON_WM_HSCROLL()
ON_WM_KILLFOCUS()
ON_WM_SETFOCUS()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_DESTROY()
ON_WM_CONTEXTMENU()
//}}AFX_MSG_MAP
ON_MESSAGE(LVM_DELETEALLITEMS, OnDeleteAllItems)
ON_MESSAGE(LVM_DELETECOLUMN, OnDeleteColumn)
ON_MESSAGE(LVM_DELETEITEM, OnDeleteItem)
ON_MESSAGE(LVM_FINDITEM, OnFindItem)
ON_MESSAGE(LVM_GETCOLUMN, OnGetColumn)
ON_MESSAGE(LVM_GETCOLUMNORDERARRAY, OnGetColumnOrderArray)
ON_MESSAGE(LVM_GETCOLUMNWIDTH, OnGetColumnWidth)
ON_MESSAGE(LVM_GETEXTENDEDLISTVIEWSTYLE , OnGetExtendedStyle)
ON_MESSAGE(LVM_GETITEM, OnGetItem)
ON_MESSAGE(LVM_GETITEMTEXT, OnGetItemText)
ON_MESSAGE(LVM_HITTEST, OnHitTest)
ON_MESSAGE(LVM_INSERTCOLUMN, OnInsertColumn)
ON_MESSAGE(LVM_INSERTITEM, OnInsertItem)
ON_MESSAGE(LVM_SETBKCOLOR, OnSetBkColor)
ON_MESSAGE(LVM_SETCOLUMN, OnSetColumn)
ON_MESSAGE(LVM_SETCOLUMNORDERARRAY, OnSetColumnOrderArray)
ON_MESSAGE(LVM_SETCOLUMNWIDTH, OnSetColumnWidth)
ON_MESSAGE(LVM_SETEXTENDEDLISTVIEWSTYLE , OnSetExtendedStyle)
ON_MESSAGE(LVM_SETIMAGELIST, OnSetImageList)
ON_MESSAGE(LVM_SETITEM, OnSetItem)
ON_MESSAGE(LVM_SETITEMTEXT, OnSetItemText)
ON_MESSAGE(LVM_SORTITEMS, OnSortItems)
ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, OnColumnclick)
ON_NOTIFY_REFLECT_EX(LVN_GETDISPINFO, OnGetdispinfo)
END_MESSAGE_MAP()


/*** Definition of helper class "IFDSListCtrlHelper" ****************************/
class IFDSListCtrlHelper: public CListCtrl
{
public:

   LRESULT Default();
   LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(IFDSListCtrlHelper)
   //}}AFX_VIRTUAL

   // Generated message map functions
   //{{AFX_MSG(IFDSListCtrlHelper)
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnDestroy();
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
};

/*** Public member functions *************************************************/

/*** Message handlers ********************************************************/
LRESULT IFDSListCtrlHelper::Default()
{
   return(CListCtrl::Default());
}

LRESULT IFDSListCtrlHelper::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
   return(CListCtrl::DefWindowProc(message, wParam, lParam));
}

void IFDSListCtrlHelper::OnDestroy() 
{
   CListCtrl::OnDestroy();
}

void IFDSListCtrlHelper::OnMouseMove(UINT nFlags, CPoint point) 
{
   CListCtrl::OnMouseMove(nFlags, point);
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(IFDSListCtrlHelper, CListCtrl)
//{{AFX_MSG_MAP(IFDSListCtrlHelper)
ON_WM_MOUSEMOVE()
ON_WM_DESTROY()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*** Definition of "workhorse" class "IFDSListBase" *****************************/

IFDSListBase::VISUAL_STYLE IFDSListBase::s_visualStyle_ = Unknown; // visual style?
const int IFDSListBase::s_nFirstColXOff_ = 2; // x-off of first col
const int IFDSListBase::s_nNextColXOff_ = 6; // y-off of other cols

/*** Public member functions *************************************************/

/*** Constructor *************************************************************/
IFDSListBase::IFDSListBase()
: nIconXOff_( 4 )
, pListCtrl_( NULL )
, bHasErrorIcon_( false )
, nColumnHidingAllowed_( 0 )
, bSortIconEnabled_( false )
, bInsertionSort_( false )
, bColorSortColumn_( false )
, iSortColumn_( 0 )
, bKeepIconLeft_( false )
, bLocked_( false )
, bControl_( false )
, bIconXOffCalculated_( false )
, dwExtendedStyle_( 0 )
, nHotItem_( -1 )
, dwHotLite_( WINVER <= 0x0400 ? RGB(0, 0, 128) : GetSysColor( colorHotlight ) )
, hcursorCustom_( 0 )
, hcursorArrow_( 0 )
, hcursorHand_( 0 )
, bOnGetDispinfo_( false )
, pConditionImages_( NULL )
{
   ctor();
}

void IFDSListBase::ctor()
{
   pConditionImages_ = new CImageList();
   pConditionImages_->Create( 16, 16, ILC_COLOR | ILC_MASK, 4, 4 );
   HICON hIcon;
   hIcon = ::LoadIcon( NULL, IDI_ASTERISK );
   pConditionImages_->Add( hIcon );
   pConditionImages_->Add(LoadIcon( NULL, IDI_ASTERISK ));
   pConditionImages_->Add(LoadIcon( NULL, IDI_EXCLAMATION ));
   pConditionImages_->Add(LoadIcon( NULL, IDI_HAND ));

   if( s_visualStyle_ == Unknown )
   {
      s_visualStyle_ = NotPresent;

      HINSTANCE hinstDll;
      hinstDll = LoadLibrary(I_("COMCTL32.DLL"));

      if( hinstDll )
      {
         DLLGETVERSIONPROC pDllGetVersion =
         reinterpret_cast<DLLGETVERSIONPROC>(GetProcAddress(hinstDll,
                                                            "DllGetVersion"));

         // Because some DLLs might not implement this function, you must test for
         // it explicitly. Depending on the particular DLL, the lack of a
         // DllGetVersion function can be a useful indicator of the version.
         if( pDllGetVersion )
         {
            DLLVERSIONINFO dvi = {sizeof(DLLVERSIONINFO)};

            if( SUCCEEDED((*pDllGetVersion)(&dvi)) && dvi.dwMajorVersion >= 6 )
               s_visualStyle_ = Present;
         }

         FreeLibrary(hinstDll);
      }
   }
}

/*** Destructor **************************************************************/
IFDSListBase::~IFDSListBase()
{
   delete pConditionImages_;

   // remove remembered column data
   for( COLUMN_VECTOR::iterator it = aColumnData_.begin();
      it != aColumnData_.end();
      ++it )
   {
      delete *it;
   }

   if( WINVER <= 0x400 && hcursorHand_ ) DestroyCursor(hcursorHand_);

}

IFDSListBase& IFDSListBase::privInit()
{
   pListCtrl_->SetImageList( pConditionImages_, LVSIL_SMALL );

   return( *this );
}

/*** Enable or disable coloring of sort column *******************************/
#if _MSC_VER == 1300
   #pragma runtime_checks("c", off)  // due to a flaw in the definition of
#endif                              // Get[R|G|B]Value
IFDSListBase& IFDSListBase::colorSortColumn(bool bEnable, int nSortColumn)
{
   ASSERT(pListCtrl_);

   if( bEnable == bColorSortColumn_ &&
       (nSortColumn == 0 || nSortColumn == iSortColumn_) ) return(*this);

   if( bEnable )
   {
      // 256 colors --> don't color sort column
      CDC* pDC = pListCtrl_->GetDC();
      bool bColor = pDC->GetDeviceCaps(BITSPIXEL) > 8;

      pListCtrl_->ReleaseDC(pDC);
      if( !bColor ) return(*this);
   }

   if( bEnable != bColorSortColumn_ )
   {
      if( bEnable )
      {
         DWORD dwColNormalColor = pListCtrl_->GetBkColor();

         // emulate sort column coloring of Windows XP explorer
         UINT nRed = GetRValue(dwColNormalColor);
         UINT nGreen = GetGValue(dwColNormalColor);
         UINT nBlue = GetBValue(dwColNormalColor);

         if( nRed > 240 && nGreen > 240 && nBlue > 240 )
         {
            nRed   -= 8;
            nGreen -= 8;
            nBlue  -= 8;
         }
         else
         {
            if( nRed   < 232 ) nRed   += nRed   / 10;
            else nRed = 255;
            if( nGreen < 232 ) nGreen += nGreen / 10;
            else nGreen = 255;
            if( nBlue  < 232 ) nBlue  += nBlue  / 10;
            else nBlue = 255;
         }
         rgbColSort_ = RGB(nRed, nGreen, nBlue);
      }
      bColorSortColumn_ = bEnable;
   }
   if( nSortColumn != 0 ) iSortColumn_ = nSortColumn;
   pListCtrl_->Invalidate();
   return( *this );
}
#if _MSC_VER == 1300
   #pragma runtime_checks("c", restore)
#endif

/*** Draw small icon *********************************************************/
void IFDSListBase::drawSmallIcon(CDC* pDC, LVITEM* pItem, LPRECT pRect) const
{
   ASSERT(pListCtrl_);

   if( pItem->iImage > 0 )
   {
      CImageList* pimglst = pListCtrl_->GetImageList(LVSIL_SMALL);

      if( pimglst )
      {
         IMAGEINFO imgInfo;

         if( pimglst->GetImageInfo(pItem->iImage, &imgInfo) )
         {
            pimglst->DrawIndirect(
                                 pDC, pItem->iImage, CPoint(pRect->left, pRect->top),
                                 CSize( std::min( pRect->right - pRect->left + 1L, imgInfo.rcImage.right - imgInfo.rcImage.left),
                                        std::min( pRect->bottom - pRect->top + 1L, imgInfo.rcImage.bottom - imgInfo.rcImage.top) ),
                                 CPoint(0, 0),
                                 pItem->state & LVIS_SELECTED &&
                                 pListCtrl_->GetFocus() == pListCtrl_ ? ILD_SELECTED : ILD_NORMAL,
                                 SRCCOPY, CLR_NONE);
         }
      }
   }
}

/*** Draw state icon *********************************************************/
void IFDSListBase::drawStateIcon(CDC* pDC, LVITEM* pItem, LPRECT pRect) const
{
   ASSERT(pListCtrl_);

   int nImage = (pItem->state & LVIS_STATEIMAGEMASK) >> 12;

   if( nImage > 0 )
   {
      CImageList* pimglst = pListCtrl_->GetImageList(LVSIL_STATE);

      if( pimglst )
      {
         IMAGEINFO imgInfo;
         // image indices are zero-based
         if( pimglst->GetImageInfo(--nImage, &imgInfo) )
         {
            pimglst->DrawIndirect(
                                 pDC, nImage, CPoint(pRect->left, pRect->top),
                                 CSize(std::min(pRect->right - pRect->left + 1L,
                                                     imgInfo.rcImage.right - imgInfo.rcImage.left),
                                       std::min(pRect->bottom - pRect->top + 1L,
                                                     imgInfo.rcImage.bottom - imgInfo.rcImage.top)),
                                 CPoint(0, 0),
                                 pItem->state & LVIS_SELECTED &&
                                 pListCtrl_->GetFocus() == pListCtrl_ ? ILD_SELECTED : ILD_NORMAL,
                                 SRCCOPY, CLR_NONE);
         }
      }
   }
}

/*** Allow or disallow the hiding of a column ********************************/
IFDSListBase& IFDSListBase::enableColumnHiding(int iColumn, bool bEnableIt)
{
   if( iColumn >= 0 && iColumn < (int)aColumnData_.size() )
      if( bEnableIt )
      {
         if( !aColumnData_[iColumn]->bHidingAllowed_ )
         {
            aColumnData_[iColumn]->bHidingAllowed_ = true;
            nColumnHidingAllowed_++;
         }
      }
      else
         if( aColumnData_[iColumn]->bHidingAllowed_ )
      {

         aColumnData_[iColumn]->bHidingAllowed_ = false;
         nColumnHidingAllowed_--;
      }

   ASSERT(nColumnHidingAllowed_ >= 0);
   return( *this );
}

/*** Draw the label of an item or subitem ************************************/
void IFDSListBase::drawSubItemText(CDC* pDC, LVITEM* pItem, LVCOLUMN* pColumn, LPRECT pRect) const
{
   if( *pItem->pszText )
      if( pRect->right - pRect->left > 0 )
         pDC->DrawText(pItem->pszText, -1, pRect,
                       (pColumn->fmt & LVCFMT_CENTER ? DT_CENTER :
                        pColumn->fmt & LVCFMT_RIGHT  ? DT_RIGHT  : DT_LEFT) |
                       DT_END_ELLIPSIS | DT_SINGLELINE | DT_NOPREFIX |
                       DT_NOCLIP | DT_VCENTER);
}

/*** Duplicate column information ********************************************/
LVCOLUMN* IFDSListBase::dupLVColumn(LVCOLUMN* pLVColumn) const
{
   LVCOLUMN* pLVColumn2 = new LVCOLUMN(*pLVColumn);

   // mask unnecessary fields
   if( !(pLVColumn2->mask & LVCF_FMT) ) pLVColumn2->fmt = 0;
   if( !(pLVColumn2->mask & LVCF_IMAGE) ) pLVColumn2->iImage = 0;
   if( !(pLVColumn2->mask & LVCF_ORDER) ) pLVColumn2->iOrder = 0;
   if( !(pLVColumn2->mask & LVCF_SUBITEM) ) pLVColumn2->iSubItem = 0;
   if( pLVColumn2->mask & LVCF_TEXT )
   {
      ASSERT(pLVColumn2->pszText);
      pLVColumn2->pszText = new TCHAR[i_strlen(pLVColumn->pszText) + 1];
      i_strcpy(pLVColumn2->pszText, pLVColumn->pszText);
   }
   else
      pLVColumn2->pszText = 0;
   if( !(pLVColumn2->mask & LVCF_WIDTH) ) pLVColumn2->cx = 0;
   pLVColumn2->cchTextMax = 0;

   return(pLVColumn2);
}

/*** Duplicate item information **********************************************/
LVITEM* IFDSListBase::dupLVItem(LVITEM* pLVItem) const
{
   LVITEM* pLVItem2 = new LVITEM(*pLVItem);

   // mask unnecessary fields
   if( !(pLVItem2->mask & LVIF_IMAGE) ) pLVItem2->iImage = 0;
   if( !(pLVItem2->mask & LVIF_INDENT) ) pLVItem2->iIndent = 0;
   if( !(pLVItem2->mask & LVIF_PARAM) ) pLVItem2->lParam = 0;
   if( pLVItem2->mask & LVIF_STATE )
      pLVItem2->state &= pLVItem2->stateMask;
   else
   {
      pLVItem2->state = 0;
      pLVItem2->stateMask = 0;
   }
   if( pLVItem2->mask & LVIF_TEXT )
   {
      ASSERT(pLVItem2->pszText);
      if( pLVItem2->pszText != LPSTR_TEXTCALLBACK )
      {
         pLVItem2->pszText = new TCHAR[i_strlen(pLVItem->pszText) + 1];
         i_strcpy(pLVItem2->pszText, pLVItem->pszText);
      }
   }
   else
      pLVItem2->pszText = 0;
   pLVItem2->iSubItem = 0;
   pLVItem2->cchTextMax = 0;

   return(pLVItem2);
}

/*** Enable or disable sort icon *********************************************/
IFDSListBase& IFDSListBase::enableSortIcon( bool bEnable, int nSortColumn)
{
   ASSERT(pListCtrl_);
   ASSERT(pListCtrl_->GetHeaderCtrl());

   bSortIconEnabled_ = bEnable;
   if( nSortColumn != 0 ) iSortColumn_ = nSortColumn;
   if( bEnable && s_visualStyle_ == NotPresent )
   {
      createSortIcons();
      pListCtrl_->GetHeaderCtrl()->SetImageList(&imglstSortIcons_);
   }
   setSortIcon();            // display or hide sort icon
   return( *this );
}

LPARAM IFDSListBase::getItemRowData( LPARAM lParam )
{
   return( reinterpret_cast< ITEM_DATA* >(lParam)->lParam_ ) ;
}

const LVITEM* IFDSListBase::getColumnLVItem( LPARAM lParam, int iColumn )
{
   ITEM_DATA* pItemData = reinterpret_cast< ITEM_DATA* >( lParam );
   if( iColumn < 0 || iColumn >= pItemData->apLVItem_.size() )
   {
      return(0);
   }
   return( pItemData->apLVItem_[iColumn] );
}

const BFFieldId* IFDSListBase::getColumnField( int iColumn ) const
{
   if( iColumn >=0 && iColumn < aColumnData_.size() )
   {
      return( aColumnData_[ iColumn ]->pFieldId_ );

   }
   return( NULL );
}

/*** Get attributes of this list view control ********************************/
bool IFDSListBase::getState( DString& dstrState ) const
{
   ASSERT(pListCtrl_);

   i_stringstream sState;

   // format of this data is as follows...
   // columnCount,sortColumn,[Visible,cx,order...]

   int cColumns = static_cast<int>(aColumnData_.size());

   if( cColumns > 0 )
   {
      sState << cColumns << I_( " " );

      sState << iSortColumn_ << I_( " " );

      for( int iColumn = 0; iColumn < cColumns; iColumn++ )
      {
         sState << ( aColumnData_[iColumn]->bHidingAllowed_ ? aColumnData_[iColumn]->bVisible_ : true ) << I_( " " );
         sState << ( aColumnData_[iColumn]->bVisible_  ? pListCtrl_->GetColumnWidth(iColumn) : aColumnData_[iColumn]->cx_) << I_( " " );
         sState << aColumnData_[ iColumn ]->iOrder_  << I_( " " );
      }

      dstrState = sState.str();
      return(true);
   }
   else
   {
      dstrState = I_( "" );
      return(false);
   }
}

/*** Small icon always should be kept left ***********************************/
bool IFDSListBase::keepIconLeft(bool bKeepLeft)
{
   bool bSuccess = true;

   if( bKeepLeft )
   {
      if( (pListCtrl_->GetStyle() & LVS_OWNERDRAWFIXED) == 0 )
      {
         bKeepLeft = false;
         bSuccess = false;
      }
   }

   bKeepIconLeft_ = bKeepLeft;
   return(bSuccess);
}

/*** Restore attributes of this list view control ****************************/
bool IFDSListBase::restoreState( const DString& configName, const DString& valueName )
{
   ASSERT(pListCtrl_);

   bool bSuccess = false;

   if( static_cast<int>(aColumnData_.size()) > 0 )
   {
      ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
      Configuration workstation = pWorkstation->retrieveConfig( configName );

      DString dstrState = workstation.getValueAsString( valueName );
      if( ! dstrState.empty() )
      {
         setState( dstrState );
      }
   }

   return( true );
}

/*** Save attributes of this list view control *******************************/
bool IFDSListBase::saveState( const DString& configName, const DString& valueName ) const
{
   DString dstrState;

   if( getState( dstrState ) )           // get current state
   {
      ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
      Configuration workstation = pWorkstation->retrieveConfig( configName );
      workstation.set( valueName + I_( "=" ) + dstrState );
      pWorkstation->storeConfig( workstation );
      pWorkstation->persist();
      return( true );
   }
   return(false);
}

/*** Set column to be sorted *************************************************/
IFDSListBase& IFDSListBase::setSortColumn(int iColumn)
{
   ASSERT(abs(iColumn) <= aColumnData_.size());
   ASSERT(pListCtrl_);

   if( iColumn != iSortColumn_ )
   {
      iSortColumn_ = iColumn;
      setSortIcon();
      if( abs(iColumn) != abs(iSortColumn_) ) pListCtrl_->Invalidate();
   }
   return( *this );
}

bool IFDSListBase::sortByInsertionOrder()
{
   bInsertionSort_ = true;
   enableSortIcon( false );
   return( TRUE == pListCtrl_->DefWindowProc(LVM_SORTITEMS, reinterpret_cast<WPARAM>(this), reinterpret_cast<LPARAM>(insertionOrderCompare)));
}

COLUMN_INFO_VECTOR IFDSListBase::prepareColumns( const BFFieldId& idField, const ClientLocale& rLocale ) const
{
   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
   if( NULL != pProps )
   {
      const BFSubstitutionSet* pSubSet = pProps->getSubstitutionSet( rLocale );
      return( prepareColumns( pSubSet ) );
   }
   return( COLUMN_INFO_VECTOR() );
}

COLUMN_INFO_VECTOR IFDSListBase::prepareColumns( const ClientLocale& rLocale ) const
{
   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( getColumnControlField() );
   if( NULL != pProps )
   {
      const BFSubstitutionSet* pSubSet = pProps->getSubstitutionSet( rLocale );
      return( prepareColumns( pSubSet ) );
   }
   return( COLUMN_INFO_VECTOR() );
}

COLUMN_INFO_VECTOR IFDSListBase::prepareColumns( const BFSubstitutionSet* pSubSet ) const
{
   if( NULL == pSubSet )
   {
      return( COLUMN_INFO_VECTOR() );
   }

   int iColumn = 0;

   COLUMN_INFO_VECTOR vColInfo;

   // iterate through substitution set entries and create columns
   std::vector< DString > keys;
   std::vector< DString > values;
   pSubSet->getKeys( keys );
   pSubSet->getValues( values );
   std::vector< DString >::iterator itId = keys.begin();
   std::vector< DString >::iterator itName = values.begin();
   for( ; itId != keys.end(); ++itId, ++itName, ++iColumn )
   {
      IFDSListCtrlColumnInfo ci;
      if( iColumn == 0 )
      {
         ci.bEnableHiding_ = false;
      }
      ci.name_ = *itName;
      ci.fmt_ = LVCFMT_LEFT;
      ci.cx_ = 100;

      const BFFieldId& idField = BFFieldId::getId( *itId );
      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
      if( NULL != pProps )
      {
         if( pProps->isNumeric() )
         {
            ci.fmt_ = LVCFMT_RIGHT;
         }
      }
      ci.pFieldId_ = &idField;
      vColInfo.push_back( ci );
   }
   return( vColInfo );
}

/*** Set attributes of this list view control ********************************/
bool IFDSListBase::setState( const DString& dstrState )
{
   ASSERT(pListCtrl_);

   i_istringstream sState( dstrState.getImp() );
   int cColumns;
   sState >> cColumns;
   if( cColumns != aColumnData_.size() )
   {
      return( false );
   }

   int iSortColumn;
   sState >> iSortColumn;
   if( abs(iSortColumn) <= cColumns )
   {
      setSortColumn(iSortColumn);
   }
   else
   {
      return(false);                       // wrong sort column
   }

   for( int iColumn = 0; iColumn < cColumns; iColumn++ )
   {
      COLUMN_DATA* pColData = aColumnData_[iColumn];

      // restore display status of column
      bool bVisible;
      sState >> bVisible;

      if( bVisible != pColData->bVisible_ )
      {
         if( pColData->bHidingAllowed_ || !pColData->bVisible_ )
         {
            showColumn(iColumn, bVisible);
         }
      }

      // restore width of column
      int cx;
      sState >> cx;
      pListCtrl_->SetColumnWidth(iColumn, cx);

      // restore column order
      int nOrder;
      sState >> nOrder;
      if( nOrder < cColumns )
      {
         pColData->iOrder_ = nOrder;
      }
      else
      {
         return(false);
      }
   }

   // set column order
   LPINT pnColOrder = new int[cColumns];
   for( int iColumn = 0; iColumn < cColumns; iColumn++ )
   {
      pnColOrder[aColumnData_[iColumn]->iOrder_] = iColumn;
   }
   pListCtrl_->SetColumnOrderArray(cColumns, pnColOrder);
   delete[] pnColOrder;

   return(true);
}

/*** Show or hide an individual column ***************************************/
void IFDSListBase::showColumn(int iColumn, bool bShowIt)
{
   ASSERT(pListCtrl_);
   ASSERT(iColumn >= 0 && iColumn < aColumnData_.size());

   if( aColumnData_[iColumn]->bHidingAllowed_ )
   {
      if( bShowIt )
      {
         if( !aColumnData_[iColumn]->bVisible_ )
         {
            // show column
            bool bNoColumnWasVisible = true;

            for( int i = aColumnData_.size() - 1; i >= 0; i-- )
               if( aColumnData_[i]->bVisible_ )
               {
                  bNoColumnWasVisible = false;
                  break;
               }

            aColumnData_[iColumn]->bVisible_ = true;

            int      nPhysicalColumn = getPhysicalIndex(iColumn);
            LVCOLUMN lvColumn = *aColumnData_[iColumn]->pLVColumn_;

            lvColumn.mask  |= LVCF_ORDER;
            lvColumn.iOrder = getPhysicalOrder(aColumnData_[iColumn]->iOrder_);
            if( pListCtrl_->DefWindowProc(LVM_INSERTCOLUMN, nPhysicalColumn, reinterpret_cast<LPARAM>(&lvColumn) ) != -1 )
            {
               if( nPhysicalColumn == 0 )
               {
                  // rejustify first column of listview control to enable a right-
                  // justified or centerd first column
                  justifyFirstColumn(lvColumn.fmt);
               }

               if( iSortColumn_ != 0 && abs(iSortColumn_) - 1 == iColumn )
               {
                  // restore sort icon
                  setSortIcon();
               }

               if( !(pListCtrl_->GetStyle() & LVS_OWNERDATA) )
               {
                  for( int nItem = pListCtrl_->GetItemCount(); --nItem >= 0; )
                  {
                     LVITEM lvItem = {LVIF_PARAM, nItem, 0};

                     if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) )
                     {
                        LVITEM* pLVItem =
                        reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->apLVItem_[iColumn];

                        pLVItem->iItem = nItem;
                        pLVItem->iSubItem = iColumn;
                        pListCtrl_->SetItem(pLVItem);
                     }
                  }

                  if( nPhysicalColumn == 0 && !bNoColumnWasVisible )
                  {
                     // After reinserting column 0 the text of the items in column 1
                     // is lost. Therefore the text must be restored here!
                     int iColumn1 = getLogicalIndex(1);
                     for( int nItem = pListCtrl_->GetItemCount(); --nItem >= 0; )
                     {
                        LVITEM lvItem = {LVIF_PARAM, nItem, 0};

                        if( pListCtrl_->DefWindowProc( LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) )
                        {
                           LVITEM* pLVItem =
                           reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->apLVItem_[iColumn1];

                           pLVItem->iItem = nItem;
                           pLVItem->iSubItem = iColumn1;
                           pListCtrl_->SetItem(pLVItem);
                        }
                     }
                  }
               }

               pListCtrl_->SetColumnWidth( iColumn, aColumnData_[iColumn]->cx_ );
            }
         }
      }
      else if( aColumnData_[iColumn]->bVisible_ )
      {
         // hide column
         int nPhysicalColumn = getPhysicalIndex(iColumn);

         aColumnData_[iColumn]->cx_ = pListCtrl_->GetColumnWidth(iColumn);
         pListCtrl_->DefWindowProc(LVM_DELETECOLUMN, nPhysicalColumn, 0);
         aColumnData_[iColumn]->bVisible_ = false;
      }
   }
}

int IFDSListBase::insertColumns( const COLUMN_INFO_VECTOR& rvColInfo )
{
   removeColumns();
   int iColumn = 0;

   if( hasErrorIcon() )
   {
      pListCtrl_->InsertColumn( iColumn, I_( "" ), LVCFMT_IMAGE, 20 );
      aColumnData_[ iColumn ]->pFieldId_ = &ifds::NullFieldId;
      ++iColumn;
   }

   COLUMN_INFO_VECTOR::const_iterator it = rvColInfo.begin();
   for( ; it != rvColInfo.end(); ++it, ++iColumn )
   {
      const IFDSListCtrlColumnInfo& rColInfo = *it;
      pListCtrl_->InsertColumn( iColumn, rColInfo.name_.c_str(), rColInfo.fmt_, rColInfo.cx_ );
      aColumnData_[ iColumn ]->pFieldId_ = rColInfo.pFieldId_;
      if( rColInfo.bEnableHiding_ )
      {
         enableColumnHiding( iColumn, true );
      }
   }
   return(iColumn);
}

bool IFDSListBase::removeColumns()
{
   while( pListCtrl_->SendMessage( LVM_DELETECOLUMN, 0, 0 ) == TRUE );
   return( true );
}


/*** Private member functions ************************************************/

/*** Compare function for sorting of list view control ***********************/
int CALLBACK IFDSListBase::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
   IFDSListBase* pThis = reinterpret_cast<IFDSListBase*>(lParamSort);

   return(pThis->pfnLVCompare_(lParam1,
                               lParam2,
                               lParamSort) );                 
}

int CALLBACK IFDSListBase::insertionOrderCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
   IFDSListBase* pThis = reinterpret_cast<IFDSListBase*>(lParamSort);
   ITEM_DATA* pI1 = reinterpret_cast<ITEM_DATA*>(lParam1);
   ITEM_DATA* pI2 = reinterpret_cast<ITEM_DATA*>(lParam2);
   return( pI1->iInsert_ - pI2->iInsert_ );
}

/*** Create image list with sort icons ***************************************/
void IFDSListBase::createSortIcons()
{
   if( !imglstSortIcons_.m_hImageList )
   {
      COLORMAP cm = {RGB(0, 0, 0), GetSysColor( colorGrayText )};
      imglstSortIcons_.Create(9, 5, ILC_COLOR24 | ILC_MASK, 2, 0);
      HBITMAP hBmp = ::CreateMappedBitmap( g_hinstDLL, IDB_HDRUP, 0, &cm, 1 ); 
      pBmpUpArrow_ = CBitmap::FromHandle( hBmp );
      nUpArrow_ = imglstSortIcons_.Add(pBmpUpArrow_, RGB(255, 255, 255));
      hBmp = ::CreateMappedBitmap( g_hinstDLL, IDB_HDRDOWN, 0, &cm, 1 ); 
      pBmpDownArrow_ = CBitmap::FromHandle( hBmp );
      nDownArrow_ = imglstSortIcons_.Add(pBmpDownArrow_, RGB(255, 255, 255));
   }
}

/*** Draw the entire item (called if window has style LVS_OWNERDRAWFIXED) ****/
void IFDSListBase::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   ASSERT(pListCtrl_);

   LVITEM* pItem = getLVItem(lpDrawItemStruct->itemID);

//->CP20031001   We have a wacked out definition of 'always selected' in that we don't care
//->CP20031001   what the actual control style is...
//->CP20031001   bool bAlwaysSelected = pItem->state & LVIS_SELECTED &&
//->CP20031001                          (pListCtrl_->GetStyle() & LVS_SHOWSELALWAYS) != 0;
   bool bAlwaysSelected = ( pItem->state & LVIS_SELECTED ) != 0;
   bool bLVHasFocus = pListCtrl_->GetFocus() == pListCtrl_;

//->CP20031001   The definition of 'has focus' includes the times that the control doesn't actually have
//->CP20031001   keyboard focus.   This is an IFDSism which will probably never go away.
//->CP20031001   bool bItemHasFocus = pItem->state & LVIS_FOCUSED && bLVHasFocus;
   bool bItemHasFocus = ( pItem->state & LVIS_FOCUSED ) != 0;
   bool bSelected = ( pItem->state & LVIS_SELECTED ) != 0;
//->CP20031001   The definition of 'really selected' includes the times that the control doesn't actually have
//->CP20031001   keyboard focus.   This is an IFDSism which will probably never go away.
   bool bReallySelected = bSelected || bItemHasFocus;
   bool bFullRowSelected = (dwExtendedStyle_ & LVS_EX_FULLROWSELECT) != 0;

   CRect rcItem;                   // rectangle bounding complete item
   pListCtrl_->GetItemRect(pItem->iItem, rcItem, LVIR_BOUNDS);

   CRect rcSubItem0;               // rectangle bounding subitem 0
   getRealSubItemRect(pItem->iItem, 0, LVIR_BOUNDS, rcSubItem0);

   CRect rcLabel;                  // rectangle bounding item label
   getRealSubItemRect(pItem->iItem, 0, LVIR_LABEL, rcLabel);

   CRect rcSelection;              // rectangle bounding selection
   if( bFullRowSelected )
   {
      rcSelection = rcItem;
      if( indexToOrder(0) == 0 || bKeepIconLeft_ )
      {
         rcSelection.left = rcLabel.left;
         int nWidthOfCol0 = static_cast<int>( pListCtrl_->DefWindowProc(LVM_GETCOLUMNWIDTH, orderToIndex(0), 0));
         if( rcSelection.left > nWidthOfCol0 )
         {
            rcSelection.left = nWidthOfCol0;
         }
      }
   }

   CDC*   pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
   CBrush brushHiLite;
   DWORD  dwNormalText = GetSysColor( colorWindowText );
   DWORD  dwHiLiteBk = 0;

   if( bReallySelected || bItemHasFocus )
   {
      dwHiLiteBk = pItem->iItem == nHotItem_ ? dwHotLite_ : GetSysColor( colorReallySelected );
      brushHiLite.CreateSolidBrush( dwHiLiteBk );
   }
   else if( bAlwaysSelected )
   {
      dwHiLiteBk = GetSysColor( colorAlwaysSelected );
      brushHiLite.CreateSolidBrush( dwHiLiteBk );
   }

   CFont* pfontPrev = 0;
   CFont* pfontHotUnderlined = 0;
   bool   bHotUnderlining = false;
   if( ( dwExtendedStyle_ & LVS_EX_TWOCLICKACTIVATE ) &&
       ( bSelected || bAlwaysSelected ) ||
       ( dwExtendedStyle_ & (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE) ) ==
       ( LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE ) &&
       pItem->iItem == nHotItem_ )
   {
      CFont*  pFont = pListCtrl_->GetFont();
      LOGFONT logFont;

      if( pFont->GetLogFont(&logFont) )
      {
         logFont.lfUnderline = TRUE;
         pfontHotUnderlined = new CFont;
         pfontHotUnderlined->CreateFontIndirect(&logFont);
         pfontPrev = pDC->SelectObject(pfontHotUnderlined);
         bHotUnderlining = true;
      }
   }

   LVCOLUMN lvc;
   lvc.mask = LVCF_FMT | LVCF_WIDTH;

   // display all subitems
   int nIndex;
   CRect   rcSubItem;                  // rectangle bounding subitem
   CRect   rcText;                     // output rectangle

   for( int iColumn = 0;
      pListCtrl_->DefWindowProc(LVM_GETCOLUMN, nIndex = orderToIndex(iColumn), reinterpret_cast<LPARAM>(&lvc));
      iColumn++ )
   {
      LVITEM* pSubItem = nIndex > 0 ? getLVItem(pItem->iItem, nIndex) : pItem;
      int     nAbsSortColumn = abs(iSortColumn_) - 1;

      // background color of current column
      DWORD  dwBkColor = bColorSortColumn_ &&
                         iSortColumn_ != 0 &&
                         aColumnData_[nAbsSortColumn]->bVisible_ &&
                         nIndex == getPhysicalIndex(nAbsSortColumn) ? rgbColSort_ : pListCtrl_->GetBkColor();
      CBrush brushBk(dwBkColor);

      // consider column margins
      if( iColumn > 0 )
      {
         // move output rectangle over next column
         rcSubItem.left = rcSubItem.right;
         rcSubItem.right += lvc.cx;
      }
      else
      {
         rcSubItem = rcItem;
         rcSubItem.right = rcSubItem.left + lvc.cx;
      }

      if( nIndex == 0 && !bKeepIconLeft_ || iColumn == 0 && bKeepIconLeft_ )
      {
         rcText = rcLabel;
         rcText.left  += s_nFirstColXOff_;
         rcText.right -= nIndex > 0 ? s_nNextColXOff_ : s_nFirstColXOff_;
      }
      else
      {
         rcText = rcSubItem;
         rcText.left  += s_nNextColXOff_;
         rcText.right -= s_nNextColXOff_;
      }

      int  nLabelWidth = getLabelWidth(pDC, pSubItem, rcText.Width());
      bool bHiLite = false;

      if( bReallySelected ||
          bAlwaysSelected ||
          bItemHasFocus && !bFullRowSelected )
         if( nIndex == 0 && iColumn != 0 && !bKeepIconLeft_ && !bFullRowSelected
             ||
             iColumn == 0 && (bKeepIconLeft_ || nIndex == 0) )
         {
            // calculate selection area
            CRect rcSubItemSelection(rcLabel);

            if( !bFullRowSelected )
            {
               int nFormat = nIndex == 0 && iColumn == 0 || !bKeepIconLeft_ ?
                             nFormatOfSubItem0_ : lvc.fmt & LVCFMT_JUSTIFYMASK;

               switch( nFormat )
               {
                  case LVCFMT_LEFT:
                     rcSubItemSelection.right = rcSubItemSelection.left + s_nFirstColXOff_ + nLabelWidth + s_nNextColXOff_;
                     break;

                  case LVCFMT_RIGHT:
                     rcSubItemSelection.left = rcSubItemSelection.right - s_nFirstColXOff_ - nLabelWidth - s_nNextColXOff_;
                     break;

                  case LVCFMT_CENTER:
                     {
                        int nSelectionWidth = s_nNextColXOff_ + nLabelWidth + s_nNextColXOff_;
                        rcSubItemSelection.left = rcLabel.left + (rcLabel.Width() - nSelectionWidth) / 2;
                        rcSubItemSelection.right = rcSubItemSelection.left + nSelectionWidth;
                        break;
                     }

                  default:
                     ASSERT(false);
                     break;
               }
               if( rcSubItemSelection.left < rcLabel.left )
               {
                  rcSubItemSelection.left = rcLabel.left;
               }
               if( rcSubItemSelection.right > rcLabel.right )
               {
                  rcSubItemSelection.right = rcLabel.right;
               }
               rcSelection = rcSubItemSelection;
            }

            if( bReallySelected || bAlwaysSelected )
            {
               if( rcSubItemSelection.left > rcSubItem.left )
               {
                  // fill area left from selection with background color
                  CRect rc(rcSubItem);
                  rc.right = rcSubItemSelection.left-1;
                  CBrush brush(dwBkColor);
                  pDC->FillRect(rc, &brushBk);
               }

               // fill selection area with highlight color
               pDC->FillRect(rcSubItemSelection, &brushHiLite);

               // fill area right from selection with background color
               if( rcSubItemSelection.right < rcSubItem.right )
               {
                  CRect rc(rcSubItem);
                  rc.left = rcSubItemSelection.right+1;
                  CBrush brush(dwBkColor);
                  pDC->FillRect(rc, &brushBk);
               }

               pDC->SetBkColor(dwHiLiteBk);
               pDC->SetTextColor( bReallySelected ? GetSysColor( colorHighlightText ) :
                                  bHotUnderlining ? dwHotLite_ : dwNormalText);
               bHiLite = true;
            }
         }
         else if( bFullRowSelected )
         {
            pDC->FillRect(rcSubItem, &brushHiLite);
            pDC->SetBkColor(dwHiLiteBk);
            pDC->SetTextColor( bReallySelected ? GetSysColor( colorHighlightText ) :
                               bHotUnderlining ? dwHotLite_ : dwNormalText);
            bHiLite = true;
         }

      if( !bHiLite )
      {
         pDC->FillRect(rcSubItem, &brushBk);
         pDC->SetBkColor(dwBkColor);
         pDC->SetTextColor(bHotUnderlining ? dwHotLite_ : dwNormalText);
      }

      if( nIndex == 0 && !bKeepIconLeft_ || iColumn == 0 && bKeepIconLeft_ )
      {
         CRect   rcIcon;
         LVITEM* pLogicalItem = reinterpret_cast<ITEM_DATA*>(pItem->lParam)->apLVItem_[0];

         if( getStateIconRect(pItem->iItem, rcIcon) )
         {
            drawStateIcon(pDC, pLogicalItem, rcIcon);
         }

         if( getRealSubItemRect(pItem->iItem, 0, LVIR_ICON, rcIcon) )
         {
            drawSmallIcon(pDC, pLogicalItem, rcIcon);
         }
      }

      pSubItem->iSubItem = getLogicalIndex(pSubItem->iSubItem);
      lvc.iSubItem = pSubItem->iSubItem;
      drawSubItemText(pDC, pSubItem, &lvc, rcText);

      if( nIndex > 0 )
      {
         delete[] pSubItem->pszText;
         delete pSubItem;
      }
   }

   if( bHotUnderlining )
   {
      pDC->SelectObject(pfontPrev);
      delete pfontHotUnderlined;
   }
   delete[] pItem->pszText;
   delete pItem;

   // If item has focus draw focus rectangle
   if( bItemHasFocus )
   {
      pDC->SetTextColor(dwNormalText);
      pDC->DrawFocusRect(rcSelection);
   }
}

/*** Calculate width of item or subitem label ********************************/
int IFDSListBase::getLabelWidth(CDC* pDC, LVITEM* pItem, LONG nMaxWidth) const
{
   if( nMaxWidth > 0 && *pItem->pszText )
   {
      return(std::min(pDC->GetTextExtent(pItem->pszText, static_cast<int>(i_strlen(pItem->pszText))).cx, nMaxWidth));
   }
   else
   {
      return(0);
   }
}

/*** Retrieve for a given physical column number the logical column number ***/
int IFDSListBase::getLogicalIndex(int nPhysicalIndex) const
{
   for( int i = 0; i < aColumnData_.size(); ++i )
   {
      if( aColumnData_[i]->bVisible_ )
      {
         if( i == nPhysicalIndex )
         {
            return(nPhysicalIndex);
         }
      }
      else
      {
         nPhysicalIndex++;
      }
   }
   ASSERT(false);
   return(-1);
}

/*** Retrieve for a given physical column order the logical column order *****/
int IFDSListBase::getLogicalOrder(int nPhysicalOrder) const
{
   for( int i = 0; i <= nPhysicalOrder; i++ )
   {
      for( int j = aColumnData_.size() - 1; j >= 0; --j )
      {
         if( aColumnData_[j]->iOrder_ == i )
         {
            if( aColumnData_[j]->bVisible_ )
            {
               if( i == nPhysicalOrder )
               {
                  return(nPhysicalOrder);
               }
            }
            else
            {
               ++nPhysicalOrder;
            }
            break;
         }
      }
   }
   ASSERT(false);
   return(-1);
}

/*** Get all attributes of a given physical item or subitem ******************/
LVITEM* IFDSListBase::getLVItem(int nItem, int nSubItem) const
{
   ASSERT(pListCtrl_);

   LVITEM* pItem = new LVITEM;

   pItem->mask = LVIF_IMAGE | LVIF_STATE | LVIF_TEXT | LVIF_PARAM;
   pItem->iItem = nItem;
   pItem->iSubItem = nSubItem;
   pItem->stateMask = ~0U;

   // enlarge text buffer gradually until it's large enough
   for( int nLen = 128;; nLen += nLen )
   {
      LPTSTR pszText = new TCHAR[nLen];

      pItem->cchTextMax = nLen;
      pItem->pszText = pszText;
      if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(pItem)) )
      {
         if( pItem->pszText != pszText )
         {
            // Windows hasn't used our buffer!
            i_strcpy(pszText, pItem->pszText);
            pItem->pszText = pszText;
         }
      }
      else
      {
         delete[] pszText;
         delete pItem;
         return(0);
      }
      if( static_cast<int>(i_strlen(pItem->pszText)) < nLen-1 )
      {
         break;
      }
      delete[] pItem->pszText;
   }

   return(pItem);
}

/*** Returns the physical index of a given column index **********************/
int IFDSListBase::getPhysicalIndex(int nColumnIndex) const
{
   int nIndex = 0;

   for( int i = 0; i < nColumnIndex; i++ )
   {
      if( aColumnData_[i]->bVisible_ )
      {
         ++nIndex;
      }
   }

   return(nIndex);
}

/*** Returns the physical order of a given column order **********************/
int IFDSListBase::getPhysicalOrder(int nColumnOrder) const
{
   int nOrder = 0;

   for( int i = 0; i < nColumnOrder; i++ )
      for( int j = aColumnData_.size() - 1; j >= 0; j-- )
         if( aColumnData_[j]->iOrder_ == i )
         {
            if( aColumnData_[j]->bVisible_ )
            {
               ++nOrder;
            }
            break;
         }

   return(nOrder);
}

/*** Calculates the bounding rectangle of a subitem.                       ***/
/*** Difference to GetSubItemRect:                                         ***/
/*** If the bounding rectangle of subitem 0 is requested, the function     ***/
/*** returns the bounding rectangle of the label including the icons only, ***/
/*** not the bounding rectangle of the whole item.                         ***/
bool IFDSListBase::getRealSubItemRect(int iItem, int iSubItem, int nArea, CRect& ref)
{
   ASSERT(pListCtrl_);
   ASSERT(iSubItem >= 0);

   switch( nArea )
   {
      case LVIR_BOUNDS:
         if( pListCtrl_->GetSubItemRect(iItem, iSubItem, LVIR_BOUNDS, ref) )
            if( iSubItem == 0 )
            {
               CRect rcLabel;

               if( pListCtrl_->GetSubItemRect(iItem, 0, LVIR_LABEL, rcLabel) )
               {
                  ref.right = rcLabel.right;

                  int nOrder = indexToOrder(0);
                  if( nOrder > 0 )
                  {
                     // The left edge of subitem 0 is identical with the right edge of
                     // the subitem left of subitem 0.
                     CRect rcSubItem;

                     if( pListCtrl_->GetSubItemRect(iItem, orderToIndex(nOrder - 1),
                                                    LVIR_BOUNDS, rcSubItem) )
                     {
                        ref.left = rcSubItem.right;
                        return(true);
                     }
                  }
                  else
                  {
                     return(true);
                  }
               }
            }
            else
            {
               return(true);
            }
         break;

      case LVIR_ICON:
         {
            CRect rcIcon;           // rectangle bounding small icon of subitem 0  

            if( pListCtrl_->GetSubItemRect(iItem, 0, LVIR_ICON, rcIcon) )
            {
               CRect rcSubItem0;     // rectangle bounding subitem 0

               if( getRealSubItemRect(iItem, 0, LVIR_BOUNDS, rcSubItem0) )
                  if( indexToOrder(0) > 0 && bKeepIconLeft_ )
                  {
                     int nIndex = orderToIndex(0);

                     if( getRealSubItemRect(iItem, nIndex, LVIR_BOUNDS, ref) )
                     {
                        int nSmallIconXOff = rcIcon.left - rcSubItem0.left;

                        ref.left  += nSmallIconXOff;
                        ref.right = ref.left + rcIcon.Width();

                        // clip rectangle at right edge if necessary
                        INT_PTR nWidth = pListCtrl_->DefWindowProc(LVM_GETCOLUMNWIDTH, nIndex, 0);
                        if( nSmallIconXOff + ref.Width() >= nWidth )
                        {
                           ref.right = ref.left - nSmallIconXOff + nWidth - 1;
                        }
                        return(true);
                     }
                  }
                  else
                  {
                     // clip rectangle at right edge if necessary
                     if( rcIcon.right > rcSubItem0.right )
                     {
                        rcIcon.right = rcSubItem0.right;
                     }
                     ref = rcIcon;
                     return(true);
                  }
            }
            break;
         }

      case LVIR_LABEL:
         {
            CRect rcLabel;          // rectangle bounding label of subitem 0

            if( pListCtrl_->GetSubItemRect(iItem, 0, LVIR_LABEL, rcLabel) )
            {
               CRect rcSubItem0;     // rectangle bounding subitem 0

               if( getRealSubItemRect(iItem, 0, LVIR_BOUNDS, rcSubItem0) )
               {
                  if( indexToOrder(0) > 0 && bKeepIconLeft_ )
                  {
                     if( getRealSubItemRect(iItem, orderToIndex(0), LVIR_BOUNDS, ref) )
                     {
                        ref.left += rcLabel.left - rcSubItem0.left;
                        return(true);
                     }
                  }
                  else
                  {
                     ref = rcLabel;
                     return(true);
                  }
               }
            }
            break;
         }

      default:
         ASSERT(false);
         break;
   }

   return(false);
}

/*** Retrieves the bounding rectangle for the state icon of an item **********/
bool IFDSListBase::getStateIconRect(int nItem, LPRECT pRect)
{
   CRect rcSubItem;

   if( getRealSubItemRect(nItem, bKeepIconLeft_ ? orderToIndex(0) : 0,
                          LVIR_BOUNDS, rcSubItem) )
   {
      CRect rcSmallIcon;

      if( getRealSubItemRect(nItem, 0, LVIR_ICON, rcSmallIcon) )
      {
         *pRect = rcSubItem;
         pRect->right = rcSmallIcon.left;
         if( rcSmallIcon.right > rcSmallIcon.left )
         {
            pRect->right--;
         }

         // calculate x-offset of state icon
         if( !bIconXOffCalculated_ )
         {
            ASSERT(pListCtrl_);
            CImageList* pImageList = pListCtrl_->GetImageList(LVSIL_STATE);

            if( pImageList )
            {
               // retrieve width of state icon
               IMAGEINFO ii = {0, 0, 0, 0};

               if( pImageList->GetImageInfo(0, &ii) )
               {
                  int nXOff = pRect->right - (ii.rcImage.right - ii.rcImage.left) - pRect->left;

                  if( nXOff < 0 )
                  {
                     nIconXOff_ = 0;
                  }
                  else if( nXOff < 4 )
                  {
                     nIconXOff_ = nXOff;
                  }
                  else
                  {
                     nIconXOff_ = 4;
                  }
               }
               else
               {
                  nIconXOff_ = 4;
               }
            }
            else
            {
               nIconXOff_ = 4;
            }

            bIconXOffCalculated_ = true;
         }

         pRect->left += nIconXOff_;

         // clip at right column border
         int nWidth = rcSubItem.Width();
         if( pRect->right >= rcSubItem.left + nWidth )
         {
            pRect->right = pRect->left - nIconXOff_ + nWidth - 1;
         }

         return(true);
      }
   }

   return(false);
}

/*** Return the order in the header control of a subitem, based on its index */
int IFDSListBase::indexToOrder(int nIndex)
{
   ASSERT(pListCtrl_);
   ASSERT(pListCtrl_->GetHeaderCtrl());

   HDITEM headerItem = {HDI_ORDER};
   return(pListCtrl_->GetHeaderCtrl()->GetItem(nIndex, &headerItem) ? headerItem.iOrder : -1);

}

/*** Invalidate client area not covered by list control items ****************/
void IFDSListBase::invalidateNonItemArea()
{
   ASSERT(pListCtrl_);

   int nTopIndex = pListCtrl_->GetTopIndex();

   if( nTopIndex >= 0 )
   {
      // update coloring of sort column
      CRect rectHdrItem;
      ASSERT(pListCtrl_->GetHeaderCtrl());
      if( pListCtrl_->GetHeaderCtrl()->GetItemRect( abs(iSortColumn_) - 1, rectHdrItem) )
      {
         // erase area above top item
         CRect rectThis;
         pListCtrl_->GetClientRect(rectThis);

         CRect rectItem;
         pListCtrl_->GetItemRect(nTopIndex, rectItem, LVIR_BOUNDS);

         CRect rectToBeErased(rectThis.left, rectHdrItem.bottom, rectThis.right, rectItem.top);
         pListCtrl_->InvalidateRect(rectToBeErased);

         // erase area below bottom item
         pListCtrl_->GetItemRect(pListCtrl_->GetItemCount() - 1, rectItem, LVIR_BOUNDS);
         if( rectItem.bottom < rectThis.bottom )
         {
            rectToBeErased.top = rectItem.bottom;
            rectToBeErased.bottom = rectThis.bottom;
         }
         pListCtrl_->InvalidateRect(rectToBeErased);
      }
   }
}

/*** Rejustify first column of listview control to enable a right- ***********/
/*** justified or centerd first column                             ***********/
void IFDSListBase::justifyFirstColumn(int nFormat)
{
   ASSERT(pListCtrl_);

   nFormatOfSubItem0_ = nFormat;

   if( pListCtrl_->GetStyle() & LVS_OWNERDRAWFIXED ||
       dwExtendedStyle_ & LVS_EX_FULLROWSELECT )
   {
      CHeaderCtrl* pHeaderCtrl = pListCtrl_->GetHeaderCtrl();
      ASSERT(pHeaderCtrl);
      HDITEM hdrItem;

      hdrItem.mask = HDI_FORMAT;
      if( pHeaderCtrl->GetItem(0, &hdrItem) )
      {
         hdrItem.fmt = hdrItem.fmt & ~HDF_JUSTIFYMASK | nFormat & HDF_JUSTIFYMASK;
         pHeaderCtrl->SetItem(0, &hdrItem);
      }
   }
}

/*** A column header has been clicked ****************************************/
BOOL IFDSListBase::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
   NMLISTVIEW* pNMListView = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
   int nAbsSortColumn = abs(iSortColumn_);

   pNMListView->iSubItem = getLogicalIndex(pNMListView->iSubItem);
   if( nAbsSortColumn > 0 )
   {
      if( pNMListView->iSubItem == nAbsSortColumn-1 )
      {
         iSortColumn_ = -iSortColumn_;
      }
      else
      {
         iSortColumn_ = pNMListView->iSubItem + 1;
      }
   }
   else
   {
      iSortColumn_ = pNMListView->iSubItem + 1;
   }
   setSortIcon();

   *pResult = 0;
   return(FALSE);
}

/*** An item in the column selection menu has been selected ******************/
BOOL IFDSListBase::OnCommand(WPARAM wParam)
{
   if( -1 == wParam )
   {
      // use defaults
      // This would require that the list be emptied and reloaded.  How do we support this?


   }
   else
   {
      showColumn(static_cast<int>(wParam), !aColumnData_[wParam]->bVisible_);
   }

   return(TRUE);
}

/*** The user has right clicked the mouse ************************************/
void IFDSListBase::OnContextMenu(CWnd* pWnd)
{
   ASSERT(pListCtrl_);

   if( pWnd == pListCtrl_->GetHeaderCtrl() )
   {
      if( nColumnHidingAllowed_ )
      {
         CMenu menu;

         if( menu.CreatePopupMenu() )
         {
            for( int i = aColumnData_.size() - 1; i > 0; --i )
            {
               menu.InsertMenu(0,
                               MF_BYPOSITION |
                               (aColumnData_[i]->bVisible_ ? MF_CHECKED : MF_UNCHECKED) |
                               (aColumnData_[i]->bHidingAllowed_ ? 0 : MF_GRAYED) | 
                               MF_STRING, 
                               i, 
                               aColumnData_[i]->pLVColumn_->pszText);
            }

            CPoint pt(0, 0);
            GetCursorPos(&pt);
            menu.TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, pListCtrl_, 0);
         }
      }
   }
}

/*** A list view (sub)item will be drawn *************************************/
void IFDSListBase::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
   ASSERT(pListCtrl_);
   ASSERT(pListCtrl_->GetHeaderCtrl());

   NMLVCUSTOMDRAW* pNMLVCustomDraw = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

   switch( pNMLVCustomDraw->nmcd.dwDrawStage )
   {
      case CDDS_PREPAINT:
         *pResult = CDRF_NOTIFYITEMDRAW;
         break;

      case CDDS_ITEMPREPAINT:
         *pResult = CDRF_NOTIFYSUBITEMDRAW;
         break;

      case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
         if( bColorSortColumn_ )
         {
            pNMLVCustomDraw->clrTextBk = pNMLVCustomDraw->iSubItem + 1 == abs(iSortColumn_) ?
                                         rgbColSort_ : pListCtrl_->GetBkColor();
            *pResult = CDRF_NEWFONT;
         }
         else
            *pResult = CDRF_DODEFAULT;
         if( pNMLVCustomDraw->iSubItem == 0 ) *pResult |= CDRF_NOTIFYPOSTPAINT;
         break;

      default:
         *pResult = CDRF_DODEFAULT;
         break;
   }
}

/*** All items will be removed ***********************************************/
LRESULT IFDSListBase::OnDeleteAllItems()
{
   ASSERT(pListCtrl_);

   BOOL bSuccess = TRUE;

   for( int nItem = static_cast<int>(pListCtrl_->DefWindowProc(LVM_GETITEMCOUNT, 0, 0));
      --nItem >= 0; )
   {
      LVITEM lvItem = {LVIF_PARAM, nItem, 0};

      if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) &&
          pListCtrl_->DefWindowProc(LVM_DELETEITEM, nItem, 0) )
      {
 //        delete reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
         ITEM_DATA* pData = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);

         IFDSListCtrlRowDataBase* pItemData = reinterpret_cast< IFDSListCtrlRowDataBase* >( pData->lParam_ );
         delete pItemData;
         // remove administration data
         delete pData;
      }
      else
      {
         ASSERT(false);
         bSuccess = FALSE;
      }

   }

   return(bSuccess);
}

/*** A column will be deleted ************************************************/
LRESULT IFDSListBase::OnDeleteColumn(WPARAM wParam)
{
   ASSERT(pListCtrl_);

   int iColumn = static_cast<int>(wParam);
   if( iColumn < 0 || iColumn >= aColumnData_.size() )
   {
      return(FALSE);
   }

   LRESULT lResult = aColumnData_[iColumn]->bVisible_ ? pListCtrl_->DefWindowProc(LVM_DELETECOLUMN, getPhysicalIndex(iColumn), 0) : TRUE;

   if( lResult )
   {
      // adjust column order
      int i;
      for( i = 0; i < aColumnData_.size(); ++i )
      {
         if( aColumnData_[i]->iOrder_ > aColumnData_[iColumn]->iOrder_ )
         {
            aColumnData_[i]->iOrder_--;
         }
      }

      delete aColumnData_[iColumn];
      aColumnData_.erase(aColumnData_.begin() + iColumn);

      if( iSortColumn_ )
      {
         // adjust index of sort column
         if( iSortColumn_ < 0 )
         {
            if( iColumn < -iSortColumn_ ) iSortColumn_++;
         }
         else
         {
            if( iColumn < iSortColumn_ ) iSortColumn_--;
         }
         if( abs(iSortColumn_) == iColumn ) iSortColumn_ = 0;
      }

      // delete subitem structures belonging to column
      for( i = static_cast<int>(pListCtrl_->DefWindowProc( LVM_GETITEMCOUNT, 0, 0)); --i >= 0; )
      {
         LVITEM lvItem = {LVIF_PARAM, i, 0};

         if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) )
         {
            ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
            LVITEM*    pLVItem = pItemData->apLVItem_[iColumn];

            pItemData->apLVItem_.erase( pItemData->apLVItem_.begin() + iColumn );
            if( pLVItem )
            {
               delete[] pLVItem->pszText;
               delete pLVItem;
            }
         }
      }
   }

   return(lResult);
}

/*** An item will be removed *************************************************/
LRESULT IFDSListBase::OnDeleteItem(WPARAM wParam)
{
   ASSERT(pListCtrl_);

   int nItem = static_cast<int>(wParam);
   if( nItem < 0 ) return(FALSE);

   LVITEM lvItem = {LVIF_PARAM, nItem, 0};

   if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) &&
       pListCtrl_->Default() )
   {
      ITEM_DATA* pData = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);

      IFDSListCtrlRowDataBase* pItemData = reinterpret_cast< IFDSListCtrlRowDataBase* >( pData->lParam_ );
      delete pItemData;
      // remove administration data
      delete pData;
      return(TRUE);
   }
   else
   {
      return(FALSE);
   }
}

/*** The list view control will be destroyed *********************************/
void IFDSListBase::OnDestroy()
{
   ASSERT(pListCtrl_);

   // delete all items explicitly to ensure
   // that all administration data will be deleted, too
   pListCtrl_->DeleteAllItems();
   pListCtrl_->OnDestroy();
}

/*** The background will be erased *******************************************/
BOOL IFDSListBase::OnEraseBkgnd(CDC* pDC) 
{
   ASSERT(pListCtrl_);

   if( bColorSortColumn_ && iSortColumn_ != 0 )
   {
      int nAbsSortColumn = abs(iSortColumn_) - 1;

      if( aColumnData_[nAbsSortColumn]->bVisible_ )
      {
         CRect rect;
         if( !pListCtrl_->GetHeaderCtrl()->GetItemRect( getPhysicalIndex(nAbsSortColumn), rect) )
         {
            return(pListCtrl_->Default() != 0);
         }

         int nXScrlOff = pListCtrl_->GetScrollPos(SB_HORZ);
         int nLeftX = rect.left  - nXScrlOff;
         int nRightX = rect.right - nXScrlOff;

         pDC->GetClipBox(&rect);     // get area to be erased
         if( nLeftX < rect.right && nRightX > rect.left )
         {
            CBrush  brushNormalColor(pListCtrl_->GetBkColor());
            CBrush  brushSortColor(rgbColSort_);
            CBrush* pbrushPrev = 0;

            if( nLeftX > rect.left )
            {
               // select brush with normal background color and save default brush
               pbrushPrev = pDC->SelectObject(&brushNormalColor);

               // erase area left from sort column with normal background color
               pDC->PatBlt(rect.left, rect.top, nLeftX - rect.left, rect.Height(), PATCOPY);
            }

            // select brush with sort color and save default brush
            if( pbrushPrev )
            {
               pDC->SelectObject(&brushSortColor);
            }
            else
            {
               pbrushPrev = pDC->SelectObject(&brushSortColor);
            }

            // erase area inside sort column with sort color
            if( nLeftX < rect.left )
            {
               if( nRightX < rect.right )
               {
                  pDC->PatBlt(rect.left, rect.top, nRightX - rect.left, rect.Height(), PATCOPY);
               }
               else
               {
                  pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
               }
            }
            else if( nRightX < rect.right )
            {
               pDC->PatBlt(nLeftX, rect.top, nRightX - nLeftX, rect.Height(), PATCOPY);
            }
            else
            {
               pDC->PatBlt(nLeftX, rect.top, rect.right - nLeftX, rect.Height(), PATCOPY);
            }

            if( nRightX < rect.right )
            {
               // select brush with normal background color
               pDC->SelectObject(&brushNormalColor);

               // color area right from sort column
               pDC->PatBlt(nRightX, rect.top, rect.right - nRightX, rect.Height(), PATCOPY);
            }

            // restore previous brush
            pDC->SelectObject(pbrushPrev);

            return(TRUE);
         }
      }
   }

   return(pListCtrl_->Default() != 0);
}

/*** A specific item will be searched ****************************************/
LRESULT IFDSListBase::OnFindItem(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);

   int iStart = static_cast<int>(wParam);
   ASSERT(iStart >= -1);

   const LVFINDINFO* plvfi = reinterpret_cast<const LVFINDINFO*>(lParam);

   if( plvfi->flags & LVFI_PARAM )
   {
      int nItemCount = pListCtrl_->GetItemCount();

      for( int nItem = iStart; ++nItem < nItemCount; )
      {
         LVITEM lvItem = {LVIF_PARAM, nItem, 0};

         if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) )
         {
            if( reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->lParam_ == plvfi->lParam )
            {
               return(nItem);
            }
         }
      }

      // wrap around?
      if( iStart >= 0 && plvfi->flags & LVFI_WRAP )
      {
         for( int nItem = 0; nItem <= iStart; nItem++ )
         {
            LVITEM lvItem = {LVIF_PARAM, nItem, 0};

            if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) )
            {
               if( reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->lParam_ == plvfi->lParam )
               {
                  return(nItem);
               }
            }
         }

      }
      return(-1);
   }
   else
   {
      return(pListCtrl_->Default());
   }
}

/*** The attributes of a column will be retrieved ****************************/
LRESULT IFDSListBase::OnGetColumn(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);

   int iColumn = static_cast<int>(wParam);
   if( iColumn < 0 || iColumn >= aColumnData_.size() ) return(FALSE);

   LVCOLUMN* pLVColumn = reinterpret_cast<LVCOLUMN*>(lParam);

   if( aColumnData_[iColumn]->bVisible_ )
   {
      LRESULT lResult = pListCtrl_->DefWindowProc(LVM_GETCOLUMN, getPhysicalIndex(iColumn), lParam);

      if( lResult )
      {
         // adjust index and order
         if( pLVColumn->mask & LVCF_ORDER )
         {
            pLVColumn->iOrder = aColumnData_[iColumn]->iOrder_;
         }
         if( pLVColumn->mask & LVCF_SUBITEM )
         {
            pLVColumn->iSubItem = iColumn;
         }
      }

      return(lResult);
   }
   else
   {
      LVCOLUMN* pLVColumnSrc = aColumnData_[iColumn]->pLVColumn_;

      // retrieve column attributes from remembered column data
      if( pLVColumn->mask & LVCF_FMT )
      {
         if( pLVColumnSrc->mask & LVCF_FMT )
         {
            pLVColumn->fmt = pLVColumnSrc->fmt;
         }
         else
         {
            pLVColumn->fmt = LVCFMT_LEFT;
         }
      }
      if( pLVColumn->mask & LVCF_IMAGE )
      {
         if( pLVColumnSrc->mask & LVCF_IMAGE )
         {
            pLVColumn->iImage = pLVColumnSrc->iImage;
         }
         else
         {
            pLVColumn->iImage = -1;
         }
      }
      if( pLVColumn->mask & LVCF_ORDER )
      {
         pLVColumn->iOrder = aColumnData_[iColumn]->iOrder_;
      }
      if( pLVColumn->mask & LVCF_SUBITEM )
      {
         pLVColumn->iSubItem = iColumn;
      }
      if( pLVColumn->mask & LVCF_TEXT && pLVColumn->pszText && pLVColumn->cchTextMax > 0 )
      {
         if( pLVColumnSrc->mask & LVCF_TEXT )
         {
            if( i_strlen(pLVColumnSrc->pszText) >= static_cast<size_t>(pLVColumn->cchTextMax - 1) )
            {
               i_strncpy(pLVColumn->pszText, pLVColumnSrc->pszText,
                        pLVColumn->cchTextMax - 1);
               pLVColumn->pszText[pLVColumn->cchTextMax - 1] = I_('\0');
            }
            else
            {
               i_strcpy(pLVColumn->pszText, pLVColumnSrc->pszText);
            }
         }
         else
         {
            *pLVColumn->pszText = I_('\0');
         }
      }
      if( pLVColumn->mask & LVCF_WIDTH )
      {
         pLVColumn->cx = aColumnData_[iColumn]->cx_;
      }

      return(TRUE);
   }
}

/*** The current left-to-right order of columns will be retrieved ************/
LRESULT IFDSListBase::OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
   INT_PTR nCount = wParam;
   if( nCount <= 0 )
   {
      return(0);
   }
   int cColumns = aColumnData_.size();
   if( nCount > cColumns )
   {
      nCount = cColumns;
   }

   LPINT pArray = reinterpret_cast<LPINT>(lParam);

   for( int iColumn = 0; iColumn < nCount; ++iColumn )
   {
      for( int j = 0; j < cColumns; j++ )
      {
         if( aColumnData_[j]->iOrder_ == iColumn )
         {
            pArray[iColumn] = j;
         }
      }

   }
   return(nCount);
}

/*** The width of a column will be retrieved *********************************/
LRESULT IFDSListBase::OnGetColumnWidth(WPARAM wParam)
{
   ASSERT(pListCtrl_);

   int iColumn = static_cast<int>(wParam);
   if( iColumn < 0 || iColumn >= aColumnData_.size() )
   {
      return(0);
   }

   if( aColumnData_[iColumn]->bVisible_ )
   {
      return(pListCtrl_->DefWindowProc(LVM_GETCOLUMNWIDTH, getPhysicalIndex(iColumn), 0));
   }
   else
   {
      // invisible column returns 0
      return(0);
   }
}

/*** Information needed to display an item will be requested *****************/
BOOL IFDSListBase::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
   ASSERT(pListCtrl_);

   if( bOnGetDispinfo_ )
   {
      return(FALSE);
   }
   bOnGetDispinfo_ = true;

   *pResult = 0;

   LVITEM* pLVItem = &reinterpret_cast<NMLVDISPINFO*>(pNMHDR)->item;
   bool bNotifyParent = true;
   int iOrigSubItem = pLVItem->iSubItem;

   pLVItem->iSubItem = getLogicalIndex(pLVItem->iSubItem);
   if( !(pListCtrl_->GetStyle() & LVS_OWNERDATA) && pLVItem->mask & LVIF_TEXT )
   {
      LVITEM* pLVItemStored = reinterpret_cast<ITEM_DATA*>( pLVItem->lParam)->apLVItem_[pLVItem->iSubItem];

      if( pLVItemStored->mask & LVIF_TEXT &&
          pLVItemStored->pszText != LPSTR_TEXTCALLBACK )
      {
         pLVItem->pszText = pLVItemStored->pszText;
         bNotifyParent = false;
      }
   }

   if( bNotifyParent )
   {
      // notify parent window
      CWnd* pParent = pListCtrl_->GetParent();

      if( pParent )
      {
         pParent->SendMessage(WM_NOTIFY, pListCtrl_->GetDlgCtrlID(), reinterpret_cast<LPARAM>(pNMHDR));
      }
   }

   // restore original subitem number
   pLVItem->iSubItem = iOrigSubItem;

   bOnGetDispinfo_ = false;
   return(TRUE);
}

/*** Some or all of an item's attributes will be retrieved *******************/
LRESULT IFDSListBase::OnGetItem(LPARAM lParam)
{
   ASSERT(pListCtrl_);

   LVITEM* pLVItem = reinterpret_cast<LVITEM*>(lParam);
   int iColumn = pLVItem->iSubItem;

   if( iColumn < 0 || iColumn >= aColumnData_.size() || pLVItem->iItem < 0 )
      return(FALSE);

   bool bVisible = aColumnData_[iColumn]->bVisible_;
   UINT origMask = pLVItem->mask;

   if( bVisible )
   {
      pLVItem->iSubItem = getPhysicalIndex(iColumn);
   }
   else
   {
      if( pLVItem->mask & ~LVIF_STATE )
      {
         pLVItem->mask |= LVIF_PARAM;
      }
      pLVItem->mask &= LVIF_STATE | LVIF_PARAM;
      pLVItem->iSubItem = 0;
   }

   LRESULT lResult = pListCtrl_->Default();
   pLVItem->mask = origMask;
   pLVItem->iSubItem = iColumn;

   if( lResult && (!bVisible || pLVItem->mask != LVIF_STATE) )
   {
      ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(pLVItem->lParam);
#if 0
      if( pLVItem->mask & LVIF_PARAM )
      {
         pLVItem->lParam = pItemData->lParam_;
      }
#endif

      // column visible and only lParam (and state) shall be retrieved
      //   --> all has been done!
      if( bVisible )
      {
         return(lResult);
      }

      LVITEM* pLVItemSrc = pItemData->apLVItem_[iColumn];

      // retrieve item attributes from remembered item data (except state)
      if( pLVItem->mask & LVIF_IMAGE )
      {
         if( pLVItemSrc && pLVItemSrc->mask & LVIF_IMAGE )
         {
            pLVItem->iImage = pLVItemSrc->iImage;
         }
         else
         {
            pLVItem->iImage = 0;
         }
      }
      if( pLVItem->mask & LVIF_INDENT )
      {
         if( pLVItemSrc && pLVItemSrc->mask & LVIF_INDENT )
         {
            pLVItem->iIndent = pLVItemSrc->iIndent;
         }
         else
         {
            pLVItem->iIndent = 0;
         }
      }
      if( pLVItem->mask & LVIF_TEXT &&
          pLVItem->pszText && pLVItem->cchTextMax > 0 )
      {
         if( pLVItemSrc && pLVItemSrc->mask & LVIF_TEXT )
         {
            if( i_strlen(pLVItemSrc->pszText) >
                static_cast<size_t>(pLVItem->cchTextMax - 1) )
            {
               i_strncpy(pLVItem->pszText, pLVItemSrc->pszText,
                        pLVItem->cchTextMax - 1);
               pLVItem->pszText[pLVItem->cchTextMax - 1] = I_('\0');
            }
            else
            {
               i_strcpy(pLVItem->pszText, pLVItemSrc->pszText);
            }
         }
         else
         {
            *pLVItem->pszText = I_('\0');
         }
      }
   }

   return(lResult);
}

/*** The text of an item or subitem will be retrieved ************************/
LRESULT IFDSListBase::OnGetItemText(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);

   INT_PTR nItem = wParam;
   LVITEM* pLVItem = reinterpret_cast<LVITEM*>(lParam);
   int     iColumn = pLVItem->iSubItem;

   if( iColumn < 0 || iColumn >= aColumnData_.size() || nItem < 0 )
      return(FALSE);

   if( aColumnData_[iColumn]->bVisible_ )
   {
      pLVItem->iSubItem = getPhysicalIndex(iColumn);
      LRESULT lResult = pListCtrl_->DefWindowProc(LVM_GETITEMTEXT, wParam, lParam);
      pLVItem->iSubItem = iColumn;

      return(lResult);
   }
   else
   {
      LVITEM lvItem = {LVIF_PARAM, pLVItem->iItem, 0};

      if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) )
      {
         LVITEM* pLVItemSrc = reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->apLVItem_[iColumn];

         // retrieve text from remembered item
         if( pLVItemSrc &&
             pLVItemSrc->mask & LVIF_TEXT &&
             pLVItemSrc->pszText && pLVItemSrc->cchTextMax > 0 &&
             pLVItem->pszText && pLVItem->cchTextMax > 0 )
            if( i_strlen(pLVItemSrc->pszText) > static_cast<size_t>(pLVItem->cchTextMax - 1) )
            {
               i_strncpy(pLVItem->pszText, pLVItemSrc->pszText, pLVItem->cchTextMax - 1);
               pLVItem->pszText[pLVItem->cchTextMax - 1] = I_('\0');
               return(pLVItem->cchTextMax - 1);
            }
            else
            {
               i_strcpy(pLVItem->pszText, pLVItemSrc->pszText);
               return(i_strlen(pLVItem->pszText));
            }
         else
         {
            *pLVItem->pszText = I_('\0');
            return(0);
         }
      }
      else
         return(0);
   }
}

/*** Determines which list view item, if any, is at a specified position *****/
int IFDSListBase::OnHitTest(LPARAM lParam)
{
   ASSERT(pListCtrl_);

   if( pListCtrl_->Default() != -1 )
   {
      LPLVHITTESTINFO pHitTestInfo = reinterpret_cast<LPLVHITTESTINFO>(lParam);

      if( pListCtrl_->GetStyle() & LVS_OWNERDRAWFIXED &&
          pHitTestInfo->iItem >= 0 )
      {
         if( pHitTestInfo->flags == LVHT_ONITEM )
         {
            CRect rc;
            if( getRealSubItemRect(pHitTestInfo->iItem, 0, LVIR_LABEL, rc) && 
                rc.PtInRect(pHitTestInfo->pt) )
            {
               pHitTestInfo->flags = LVHT_ONITEMLABEL;
            }
            else if( getRealSubItemRect(pHitTestInfo->iItem, 0, LVIR_ICON, rc) &&
                     rc.PtInRect(pHitTestInfo->pt) )
            {
               pHitTestInfo->flags = LVHT_ONITEMICON;
            }
            else if( getStateIconRect(pHitTestInfo->iItem, rc) &&
                     rc.PtInRect(pHitTestInfo->pt) )
            {
               pHitTestInfo->flags = LVHT_ONITEMSTATEICON;
            }
            else if( pListCtrl_->GetItemRect(pHitTestInfo->iItem, rc, LVIR_BOUNDS) &&
                     (!rc.PtInRect(pHitTestInfo->pt) ||
                      // The small area left from state icon is LVHT_NOWHERE!!!
                      rc.left > -nIconXOff_ &&
                      pHitTestInfo->pt.x < std::min(nIconXOff_+(int)(rc.left), nIconXOff_) ) )
            {
               pHitTestInfo->flags = LVHT_NOWHERE;
            }
         }
      }
      return(pHitTestInfo->iItem);
   }
   else
   {
      return(-1);
   }
}

/*** List control has been scrolled horizontally *****************************/
void IFDSListBase::OnHScroll()
{
   ASSERT(pListCtrl_);

   pListCtrl_->Default();
   invalidateNonItemArea();
}

/*** A new column will be inserted *******************************************/
LRESULT IFDSListBase::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);

   int iColumn = static_cast<int>(wParam);
   int cColumns = aColumnData_.size();
   if( iColumn < 0 || iColumn > cColumns ) return(-1);

   LVCOLUMN* pLVColumn = dupLVColumn(reinterpret_cast<LVCOLUMN*>(lParam));

   // adjust column attributes according to the real physical conditions
   pLVColumn->mask &= ~LVCF_SUBITEM;   // mask unnecessary subitem number
   if( pLVColumn->mask & LVCF_ORDER )
   {
      ASSERT(pLVColumn->iOrder >= 0 && pLVColumn->iOrder <= cColumns);
      pLVColumn->iOrder = getPhysicalOrder(pLVColumn->iOrder);
   }

   LRESULT lResult = pListCtrl_->DefWindowProc(LVM_INSERTCOLUMN, getPhysicalIndex(iColumn), reinterpret_cast<LPARAM>(pLVColumn));

   if( lResult != -1 )
   {
      if( iColumn == 0 )
      {
         // Rejustify first column of listview control to enable a right-justified or centerd first column
      }

      // create and fill column administration structure
      COLUMN_DATA* pColumnData = new COLUMN_DATA;

      pLVColumn->mask |= LVCF_WIDTH;
      pLVColumn->cx = 0;
      pColumnData->pLVColumn_ = pLVColumn;
      pColumnData->iOrder_ = pLVColumn->mask & LVCF_ORDER ? reinterpret_cast<LVCOLUMN*>(lParam)->iOrder : iColumn;

      // adjust column order
      int iColumnAdjust;
      for( iColumnAdjust = 0; iColumnAdjust < cColumns; ++iColumnAdjust )
      {
         if( aColumnData_[iColumnAdjust]->iOrder_ >= pColumnData->iOrder_ )
         {
            aColumnData_[iColumnAdjust]->iOrder_++;
         }
      }

      // store column administration structure
      aColumnData_.insert(aColumnData_.begin() + iColumn, pColumnData);

      if( iSortColumn_ )
      {
         // adjust index of sort column
         if( iSortColumn_ < 0 )
         {
            if( iColumn < -iSortColumn_ ) iSortColumn_--;
         }
         else
         {
            if( iColumn < iSortColumn_ ) iSortColumn_++;
         }
      }

      // insert subitem placeholders belonging to column
      for( int i = static_cast<int>(pListCtrl_->DefWindowProc( LVM_GETITEMCOUNT, 0, 0)); --i >= 0; )
      {
         LVITEM lvItem = {LVIF_PARAM, i, 0};

         if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) )
         {
            ITEM_DATA* pID = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
            pID->apLVItem_.insert( pID->apLVItem_.begin() + iColumn, NULL );
         }
      }
   }
   else
   {
      delete[] pLVColumn->pszText;
      delete pLVColumn;
   }

   return(lResult);
}

/*** A new item will be inserted *********************************************/
LRESULT IFDSListBase::OnInsertItem(LPARAM lParam)
{
   ASSERT(pListCtrl_);

   LVITEM* pLVItemSrc = reinterpret_cast<LVITEM*>(lParam);
   if( pLVItemSrc->iItem < 0 ) return(-1);
   LVITEM* pLVItem = dupLVItem(pLVItemSrc);

   // save lParam in administration data
   ITEM_DATA* pItemData = new ITEM_DATA;
   pItemData->iInsert_ = ++ITEM_DATA::s_iInsert_;
   if( pLVItemSrc->mask & LVIF_PARAM ) pItemData->lParam_ = pLVItem->lParam;
   // ^administration data is physical lParam
   pLVItem->lParam = reinterpret_cast<LPARAM>(pItemData);
   pLVItem->mask |= LVIF_PARAM;

   // physical text is always LPSTR_TEXTCALLBACK
   LPTSTR pszOrigText = pLVItem->pszText;
   if( pLVItemSrc->mask & LVIF_TEXT &&
       pLVItemSrc->pszText != LPSTR_TEXTCALLBACK &&
       !(pListCtrl_->GetStyle() & (LVS_SORTASCENDING | LVS_SORTDESCENDING) ) )
   {
      pLVItem->pszText = LPSTR_TEXTCALLBACK;
   }

   LRESULT lResult = pListCtrl_->DefWindowProc(LVM_INSERTITEM, 0, reinterpret_cast<LPARAM>(pLVItem));

   if( lResult != -1 )
   {
      // correct item data
      pLVItem->mask = pLVItemSrc->mask;
      pLVItem->pszText = pszOrigText;
      pLVItem->iItem = static_cast<int>(lResult);

      // insert item into administration data for column 0
      pItemData->apLVItem_.insert( pItemData->apLVItem_.begin(), pLVItem);
   }
   else
   {
      if( pLVItemSrc->pszText != LPSTR_TEXTCALLBACK ) delete[] pszOrigText;
      delete pLVItem;
      delete pItemData;
   }

   return(lResult);
}

/*** A key has been pressed  *************************************************/
void IFDSListBase::OnKeyDown(UINT nChar) 
{
   ASSERT(pListCtrl_);

   switch( nChar )
   {
      // Numpad-Plus
      case VK_ADD:
         // Ctrl-Numpad-Plus --> set optimum width for all columns
         if( bControl_ && bKeepIconLeft_ && indexToOrder(0) > 0 )
         {
            LVCOLUMN lvc;
            lvc.mask = LVCF_FMT;

            int nIndex;
            for( int iColumn = 0;
               pListCtrl_->DefWindowProc(LVM_GETCOLUMN, nIndex = orderToIndex(iColumn), reinterpret_cast<LPARAM>(&lvc));
               ++iColumn )
            {
               int nOptWidth;

               if( nIndex == 0 || iColumn == 0 )
               {
                  // calculate needed column width
                  nOptWidth = 0;
                  for( int nItem = pListCtrl_->GetItemCount(); --nItem >= 0; )
                  {
                     int nWidth = pListCtrl_->GetStringWidth( pListCtrl_->GetItemText(nItem, nIndex));
                     if( nWidth > nOptWidth )
                     {
                        nOptWidth = nWidth;
                     }
                  }

                  if( nIndex > 0 )
                  {
                     // add space for state icon and small icon
                     CRect rcSubItem;
                     if( getRealSubItemRect(0, nIndex, LVIR_BOUNDS, rcSubItem) )
                     {
                        CRect rcLabel;
                        if( getRealSubItemRect(0, nIndex, LVIR_LABEL, rcLabel) )
                        {
                           nOptWidth += rcLabel.left - rcSubItem.left;
                        }
                     }

                     nOptWidth += s_nFirstColXOff_;   // add left offset
                  }
                  else
                  {
                     nOptWidth += s_nNextColXOff_;    // add left offset
                  }


                  nOptWidth += s_nNextColXOff_;       // add right offset
               }
               else
               {
                  nOptWidth = LVSCW_AUTOSIZE;
               }

               pListCtrl_->SetColumnWidth(nIndex, nOptWidth);
            }
         }
         else
         {
            pListCtrl_->Default();
         }
         break;

         // Ctrl
      case VK_CONTROL:
         if( bKeepIconLeft_ && indexToOrder(0) > 0 )
         {
            bControl_ = true;
         }
         else
         {
            pListCtrl_->Default();
         }
         break;

         // All other keys
      default:
         pListCtrl_->Default();
         break;
   }
}

/*** A key has been released *************************************************/
void IFDSListBase::OnKeyUp(UINT nChar) 
{
   ASSERT(pListCtrl_);

   if( nChar == VK_CONTROL )
   {
      bControl_ = false;
   }
   pListCtrl_->Default();  
}

/*** List control loses input focus ******************************************/
void IFDSListBase::OnKillFocus() 
{
   ASSERT(pListCtrl_);

   pListCtrl_->Default();

   // manually remove focus state so that custom drawing will function properly
   int nItem = pListCtrl_->GetNextItem(-1, LVNI_SELECTED);
   if( nItem >= 0 )
   {
      pListCtrl_->SetItemState(nItem, 0, LVIS_FOCUSED);
   }
}

/*** The user double-clicks the left mouse button ****************************/
void IFDSListBase::OnLButtonDblClk(CPoint point) 
{
   ASSERT(pListCtrl_);

   if( pListCtrl_->GetStyle() & LVS_OWNERDRAWFIXED )
   {
      UINT flags;
      int  iItem = pListCtrl_->HitTest(point, &flags);

      if( iItem >= 0 &&
          dwExtendedStyle_ & LVS_EX_CHECKBOXES &&
          flags == LVHT_ONITEMSTATEICON )
      {
         pListCtrl_->SetCheck(iItem, !pListCtrl_->GetCheck(iItem));
      }
      else
      {
         pListCtrl_->Default();
      }
   }
   else
   {
      pListCtrl_->Default();
   }
}

/*** The user presses the left mouse button **********************************/
void IFDSListBase::OnLButtonDown(CPoint point) 
{
   ASSERT(pListCtrl_);

   if( pListCtrl_->GetStyle() & LVS_OWNERDRAWFIXED )
   {
      if( hcursorCustom_ ) SetCursor(hcursorCustom_);

      UINT flags;
      int  iItem = pListCtrl_->HitTest(point, &flags);
      if( iItem >= 0 &&
          ( dwExtendedStyle_ & LVS_EX_CHECKBOXES ) &&
          LVHT_ONITEMSTATEICON == flags )
      {
         pListCtrl_->SetCheck(iItem, !pListCtrl_->GetCheck(iItem));
      }
      else
      {
         pListCtrl_->Default();
      }
   }
   else
   {
      pListCtrl_->Default();
   }

   setHotCursor(point);
}

/*** The user releases the left mouse button *********************************/
void IFDSListBase::OnLButtonUp()
{
   ASSERT(pListCtrl_);

   if( pListCtrl_->GetStyle() & LVS_OWNERDRAWFIXED )
   {
      if( hcursorCustom_ )
      {
         SetCursor(hcursorCustom_);
      }
   }

   pListCtrl_->Default();
}

/*** The mouse has been moved ************************************************/
void IFDSListBase::OnMouseMove(CPoint point)
{
   ASSERT(pListCtrl_);
   pListCtrl_->Default();
   setHotCursor(point);
}

/*** Divider in header control has been dragged ******************************/
BOOL IFDSListBase::OnNotify(LPARAM lParam) 
{
   ASSERT(pListCtrl_);
   ASSERT(pListCtrl_->GetHeaderCtrl());

   BOOL bRet = pListCtrl_->Default() != 0;
   NMHEADER* pNMHdr = reinterpret_cast<NMHEADER*>(lParam);

   if( pNMHdr->hdr.hwndFrom == pListCtrl_->GetHeaderCtrl()->m_hWnd )
      switch( pNMHdr->hdr.code )
      {
         case HDN_DIVIDERDBLCLICKW:
         case HDN_DIVIDERDBLCLICKA:
            if( bKeepIconLeft_ &&
                (getLogicalIndex(pNMHdr->iItem) > 0 &&
                 indexToOrder(pNMHdr->iItem) == 0 ||
                 pNMHdr->iItem == 0 &&
                 indexToOrder(pNMHdr->iItem) > 0) )
            {
               // calculate needed column width
               int nOptWidth = 0;
               for( int nItem = pListCtrl_->GetItemCount(); --nItem >= 0; )
               {
                  int nWidth = pListCtrl_->GetStringWidth( pListCtrl_->GetItemText(nItem, getLogicalIndex(pNMHdr->iItem)));
                  if( nWidth > nOptWidth ) nOptWidth = nWidth;
               }

               if( getLogicalIndex(pNMHdr->iItem) > 0 )
               {
                  // add space for state icon and small icon
                  CRect rcSubItem;
                  if( getRealSubItemRect(0, pNMHdr->iItem, LVIR_BOUNDS, rcSubItem) )
                  {
                     CRect rcLabel;
                     if( getRealSubItemRect(0, pNMHdr->iItem, LVIR_LABEL, rcLabel) )
                        nOptWidth += rcLabel.left - rcSubItem.left;
                  }

                  // add left offset
                  nOptWidth += s_nFirstColXOff_;
               }
               else
                  // add left offset
                  nOptWidth += s_nNextColXOff_;

               // add right offset
               nOptWidth += s_nNextColXOff_;

               pListCtrl_->DefWindowProc(LVM_SETCOLUMNWIDTH, pNMHdr->iItem, nOptWidth);
               return(TRUE);
            }
            break;

         case HDN_BEGINDRAG:
#if 0
            if( 
               hasErrorIcon() &&
                getLogicalIndex( pNMHdr->iItem ) == 0 )
            {
               // can't reorder the error icon column
               return( TRUE );
            }
#endif
            break;
         case HDN_ENDDRAG:
            if( pNMHdr->pitem->iOrder >= 0 )
            {
               int iColumn = getLogicalIndex(pNMHdr->iItem);
               int nOrder = getLogicalOrder(pNMHdr->pitem->iOrder);

               if( nOrder < aColumnData_[iColumn]->iOrder_ )
               {
                  // adjust column order
                  for( int i = aColumnData_.size() - 1; i >= 0; i-- )
                     if( aColumnData_[i]->iOrder_ >= nOrder &&
                         aColumnData_[i]->iOrder_ <
                         aColumnData_[iColumn]->iOrder_ )
                        aColumnData_[i]->iOrder_++;
                  aColumnData_[iColumn]->iOrder_ = nOrder;
               }
               else if( nOrder > aColumnData_[iColumn]->iOrder_ )
               {
                  // adjust column order
                  for( int i = aColumnData_.size() - 1; i >= 0; i-- )
                     if( aColumnData_[i]->iOrder_ >
                         aColumnData_[iColumn]->iOrder_ &&
                         aColumnData_[i]->iOrder_ <= nOrder )
                        aColumnData_[i]->iOrder_--;
                  aColumnData_[iColumn]->iOrder_ = nOrder;
               }
            }
            break;

         case HDN_ENDTRACKW:
         case HDN_ENDTRACKA:
         case HDN_ITEMCHANGEDW:
         case HDN_ITEMCHANGEDA:
            if( bColorSortColumn_ ) invalidateNonItemArea();
            break;

         case HDN_ITEMCLICK:
            // Suppress further processing of this message to prevent Windows from
            // sending the notification message LVN_COLUMNCLICK a second time!
            // For unknown reasons this is necessary in an Unicode environment
            // only.
            return(TRUE);

         default:
            break;
      }

   return(bRet);
}

/*** The background color of the list view control will be set ***************/
LRESULT IFDSListBase::OnSetBkColor()
{
   ASSERT(pListCtrl_);

   if( pListCtrl_->Default() )
   {
      if( bColorSortColumn_ )
      {
         // force recalculation of sort column color
         bColorSortColumn_ = false;
         colorSortColumn();
      }
      return(TRUE);
   }
   else
      return(FALSE);
}

/*** The attributes of a column will be set **********************************/
LRESULT IFDSListBase::OnSetColumn(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);

   int iColumn = static_cast<int>(wParam);
   int cColumns = aColumnData_.size();
   if( iColumn < 0 || iColumn >= cColumns ) return(FALSE);

   LVCOLUMN* pLVColumn = dupLVColumn(reinterpret_cast<LVCOLUMN*>(lParam));

   // adjust column attributes according to the real physical conditions
   pLVColumn->mask &= ~LVCF_SUBITEM;   // mask unnecessary subitem number
   if( pLVColumn->mask & LVCF_ORDER )
   {
      ASSERT(pLVColumn->iOrder >= 0 && pLVColumn->iOrder < cColumns);
      pLVColumn->iOrder = getPhysicalOrder(pLVColumn->iOrder);
   }

   LRESULT lResult = aColumnData_[iColumn]->bVisible_ ? pListCtrl_->DefWindowProc(LVM_SETCOLUMN, getPhysicalIndex(iColumn), reinterpret_cast<LPARAM>(pLVColumn)) : TRUE;

   if( lResult )
   {
      // update column data
      LVCOLUMN* pLVColumnDst = aColumnData_[iColumn]->pLVColumn_;
      if( pLVColumn->mask & LVCF_FMT ) pLVColumnDst->fmt = pLVColumn->fmt;
      if( pLVColumn->mask & LVCF_IMAGE ) pLVColumnDst->iImage = pLVColumn->iImage;
      if( pLVColumn->mask & LVCF_ORDER )
      {
         int nOrder = reinterpret_cast<LVCOLUMN*>(lParam)->iOrder;

         if( nOrder < aColumnData_[iColumn]->iOrder_ )
         {
            // adjust column order
            for( int i = 0; i < cColumns; i++ )
               if( aColumnData_[i]->iOrder_ >= nOrder &&
                   aColumnData_[i]->iOrder_ <  aColumnData_[iColumn]->iOrder_ )
                  aColumnData_[i]->iOrder_++;
            aColumnData_[iColumn]->iOrder_ = nOrder;
         }
         else if( nOrder > aColumnData_[iColumn]->iOrder_ )
         {
            // adjust column order
            for( int i = 0; i < cColumns; i++ )
               if( aColumnData_[i]->iOrder_ >  aColumnData_[iColumn]->iOrder_ &&
                   aColumnData_[i]->iOrder_ <= nOrder )
                  aColumnData_[i]->iOrder_--;
            aColumnData_[iColumn]->iOrder_ = nOrder;
         }
      }
      if( pLVColumn->mask & LVCF_TEXT && pLVColumn->pszText )
      {
         delete[] pLVColumnDst->pszText;
         pLVColumnDst->pszText = new TCHAR[i_strlen(pLVColumn->pszText)+1];
         i_strcpy(pLVColumnDst->pszText, pLVColumn->pszText);
      }
      pLVColumnDst->mask |= pLVColumn->mask;
   }

   delete[] pLVColumn->pszText;
   delete pLVColumn;

   return(lResult);
}

/*** The left-to-right order of columns will be set **************************/
LRESULT IFDSListBase::OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
   INT_PTR nCount = wParam;
   if( nCount <= 0 ) return(0);
   INT_PTR cColumns = aColumnData_.size();
   if( nCount > cColumns ) nCount = cColumns;

   LPINT pArraySrc = reinterpret_cast<LPINT>(lParam);
   LPINT pArrayDst = new int[nCount];

   int n = 0;
   for( int i = 0; i < nCount; i++ )
   {
      int iColumn = pArraySrc[i];
      if( iColumn >= cColumns )
      {
         // illegal column index
         delete[] pArrayDst;
         return(0);
      }

      if( aColumnData_[iColumn]->bVisible_ )
         pArrayDst[n++] = getPhysicalIndex(iColumn);
   }

   LRESULT lResult = pListCtrl_->DefWindowProc(LVM_SETCOLUMNORDERARRAY, n, reinterpret_cast<LPARAM>(pArrayDst));

   delete[] pArrayDst;

   if( lResult )
      // adjust column order
      for( int i = 0; i < nCount; i++ )
      {
         int iColumn = pArraySrc[i];

         if( i < aColumnData_[iColumn]->iOrder_ )
         {
            for( int j = 0; j < cColumns; j++ )
               if( aColumnData_[j]->iOrder_ >= i &&
                   aColumnData_[j]->iOrder_ <  aColumnData_[iColumn]->iOrder_ )
                  aColumnData_[j]->iOrder_++;
            aColumnData_[iColumn]->iOrder_ = i;
         }
         else if( i > aColumnData_[iColumn]->iOrder_ )
         {
            for( int j = 0; j < cColumns; j++ )
               if( aColumnData_[j]->iOrder_ >  aColumnData_[iColumn]->iOrder_ &&
                   aColumnData_[j]->iOrder_ <= i ) aColumnData_[j]->iOrder_--;
            aColumnData_[iColumn]->iOrder_ = i;
         }
      }

   return(lResult);
}

/*** The width of a column will be changed ***********************************/
LRESULT IFDSListBase::OnSetColumnWidth(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);

   int iColumn = static_cast<int>(wParam);
   if( iColumn < 0 || iColumn >= aColumnData_.size() ) return(FALSE);

   if( aColumnData_[iColumn]->bVisible_ )
      return(pListCtrl_->DefWindowProc(LVM_SETCOLUMNWIDTH, getPhysicalIndex(iColumn), lParam));
   else
   {
      // remember new column width
      aColumnData_[iColumn]->cx_ = static_cast<int>(lParam);
      return(TRUE);
   }
}

/*** The extended list view style will be set ********************************/
LRESULT IFDSListBase::OnSetExtendedStyle(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);

   LRESULT dwResult = dwExtendedStyle_;
   if( !wParam ) wParam = ~0U;
   dwExtendedStyle_ = static_cast<DWORD>(wParam & lParam);

   if( pListCtrl_->GetStyle() & LVS_OWNERDRAWFIXED )
      // Hide the bits LVS_EX_UNDERLINEHOT, LVS_EX_ONECLICKACTIVATE, and
      // LVS_EX_TWOCLICKACTIVATE from Windows
      if( wParam & (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
                    LVS_EX_TWOCLICKACTIVATE) )
      {
         if( lParam & (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
                       LVS_EX_TWOCLICKACTIVATE) ) prepareHotUnderlining();

         pListCtrl_->DefWindowProc(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwExtendedStyle_ & ~(LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TWOCLICKACTIVATE));
         return(dwResult);
      }
      else
         hcursorCustom_ = 0;

   return(pListCtrl_->Default());
}

/*** List control gains input focus ******************************************/
void IFDSListBase::OnSetFocus() 
{
   ASSERT(pListCtrl_);

   pListCtrl_->Default();

   // manually set focus state so that custom drawing will function properly
   int nItem = pListCtrl_->GetNextItem(-1, LVNI_SELECTED);
   if( nItem >= 0 ) pListCtrl_->SetItemState(nItem, LVIS_FOCUSED, LVIS_FOCUSED);
}

/*** Assigns an image list to a list control *********************************/
LRESULT IFDSListBase::OnSetImageList(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);
   ASSERT(pListCtrl_->GetHeaderCtrl());
   ASSERT(wParam != LVSIL_NORMAL);

   LRESULT dwResult = pListCtrl_->Default();

   if( wParam == LVSIL_SMALL && lParam )
   {
      // restore image list with sort icons because default behavior is that the
      // header control shares its image list with the small icon list of the
      // list control
      pListCtrl_->GetHeaderCtrl()->SetImageList(&imglstSortIcons_);
   }

   return(dwResult);
}

/*** Some or all of a list view items attributes will be set *****************/
LRESULT IFDSListBase::OnSetItem(LPARAM lParam)
{
   ASSERT(pListCtrl_);

   LVITEM* pLVItemSrc = reinterpret_cast<LVITEM*>(lParam);
   int     iColumn = pLVItemSrc->iSubItem;

   if( iColumn < 0 || iColumn >= aColumnData_.size() || pLVItemSrc->iItem < 0 )
   {
      return(FALSE);
   }

   LVITEM* pLVItem = dupLVItem(pLVItemSrc);
   bool    bVisible = aColumnData_[iColumn]->bVisible_;
   LRESULT lResult;
   LPTSTR  pszOrigText = pLVItem->pszText;

   if( bVisible && 
       pLVItemSrc->mask & ~LVIF_PARAM ||
       iColumn == 0 && 
       pLVItemSrc->mask & LVIF_STATE )
   {
      // column is visible and other attributes than lParam will be set
      //   or
      // column zero and at least state will be set
      //   --> do it physically
      pLVItem->mask &= ~LVIF_PARAM;
      if( bVisible )
      {
         if( pLVItemSrc->mask & LVIF_TEXT &&
             pLVItemSrc->pszText != LPSTR_TEXTCALLBACK &&
             !(pListCtrl_->GetStyle() & (LVS_SORTASCENDING | LVS_SORTDESCENDING)) )
         {
            pLVItem->pszText = LPSTR_TEXTCALLBACK;
         }
      }
      else
      {
         pLVItem->mask &= LVIF_STATE;
      }

      if( pLVItem->mask )
      {
         pLVItem->iSubItem = getPhysicalIndex(iColumn);
         lResult = pListCtrl_->DefWindowProc(LVM_SETITEM, 0, reinterpret_cast<LPARAM>(pLVItem));
      }
      else
      {
         lResult = TRUE;
      }
   }
   else
   {
      lResult = TRUE;
   }

   if( lResult )
   {
      LVITEM lvItem = {LVIF_PARAM, pLVItemSrc->iItem, 0};

      if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) )
      {
         ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);

         // store lParam in administration data
         if( pLVItemSrc->mask & LVIF_PARAM )
            pItemData->lParam_ = pLVItemSrc->lParam;

         LVITEM* pLVItemDst;
         bool    bInsertItem;

         if( pItemData->apLVItem_.size() > iColumn )
         {
            pLVItemDst = pItemData->apLVItem_[iColumn];
            bInsertItem = false;
         }
         else
         {
            pLVItemDst = 0;
            bInsertItem = true;
         }

         // Does the subitem already exist in the administration data?
         if( pLVItemDst )
         {
            delete pLVItem;

            // update subitem data
            if( pLVItemSrc->mask & LVIF_IMAGE )
            {
               pLVItemDst->iImage = pLVItemSrc->iImage;
            }
            if( pLVItemSrc->mask & LVIF_INDENT )
            {
               pLVItemDst->iIndent = pLVItemSrc->iIndent;
            }
            if( pLVItemSrc->mask & LVIF_TEXT && pszOrigText )
            {
               if( pLVItemDst->mask & LVIF_TEXT &&
                   pLVItemDst->pszText != LPSTR_TEXTCALLBACK )
               {
                  delete[] pLVItemDst->pszText;
               }
               pLVItemDst->pszText = pszOrigText;
            }
            pLVItemDst->mask |= pLVItemSrc->mask;
         }
         else
         {
            // store subitem administration data
            pLVItem->mask = pLVItemSrc->mask;
            pLVItem->iSubItem = iColumn;
            pLVItem->pszText = pszOrigText;
            if( bInsertItem )
            {
               pItemData->apLVItem_.insert( pItemData->apLVItem_.begin() + iColumn, pLVItem);
            }
            else
            {
               pItemData->apLVItem_[iColumn] = pLVItem;
            }
         }
      }
   }
   else
   {
      if( pLVItemSrc->mask & LVIF_TEXT &&
          pLVItemSrc->pszText != LPSTR_TEXTCALLBACK ) delete[] pszOrigText;
      delete pLVItem;
   }

   return(lResult);
}

/*** The text of an item or a subitem will be changed ************************/
LRESULT IFDSListBase::OnSetItemText(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);

   int     nItem = static_cast<int>(wParam);
   LVITEM  lvItemSrc = *reinterpret_cast<LVITEM*>(lParam);

   if( lvItemSrc.iSubItem < 0 ||
       lvItemSrc.iSubItem >= aColumnData_.size() ||
       nItem <  0 )
   {
      return(FALSE);
   }

   lvItemSrc.mask = LVIF_TEXT;
   LVITEM* pLVItem = dupLVItem(&lvItemSrc);
   LRESULT lResult;
   LPTSTR  pszOrigText = pLVItem->pszText;

   if( aColumnData_[lvItemSrc.iSubItem]->bVisible_ )
   {
      if( pszOrigText != LPSTR_TEXTCALLBACK &&
          !(pListCtrl_->GetStyle() & (LVS_SORTASCENDING | LVS_SORTDESCENDING)) )
      {
         pLVItem->pszText = LPSTR_TEXTCALLBACK;
      }
      pLVItem->iSubItem = getPhysicalIndex(lvItemSrc.iSubItem);
      lResult = pListCtrl_->DefWindowProc(LVM_SETITEMTEXT, wParam, reinterpret_cast<LPARAM>(pLVItem));
   }
   else
   {
      lResult = TRUE;
   }

   if( lResult )
   {
      LVITEM lvItem = {LVIF_PARAM, nItem, 0};

      if( pListCtrl_->DefWindowProc(LVM_GETITEM, 0, reinterpret_cast<LPARAM>(&lvItem)) )
      {
         ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
         LVITEM*    pLVItemDst;
         bool       bInsertItem;

         if( pItemData->apLVItem_.size() > lvItemSrc.iSubItem )
         {
            pLVItemDst = pItemData->apLVItem_[lvItemSrc.iSubItem];
            bInsertItem = false;
         }
         else
         {
            pLVItemDst = 0;
            bInsertItem = true;
         }

         // Does the subitem already exist in the administration data?
         if( pLVItemDst )
         {
            delete pLVItem;

            // update subitem text
            if( pszOrigText )
            {
               if( pLVItemDst->mask & LVIF_TEXT &&
                   pLVItemDst->pszText != LPSTR_TEXTCALLBACK )
                  delete[] pLVItemDst->pszText;
               pLVItemDst->pszText = pszOrigText;
            }
            pLVItemDst->mask |= lvItemSrc.mask;
         }
         else
         {
            // store subitem administration data
            pLVItem->iSubItem = lvItemSrc.iSubItem;
            pLVItem->pszText = pszOrigText;
            if( bInsertItem )
                pItemData->apLVItem_.insert(pItemData->apLVItem_.begin() + lvItemSrc.iSubItem, pLVItem);
            else
               pItemData->apLVItem_[lvItemSrc.iSubItem] = pLVItem;
         }
      }
   }
   else
   {
      if( lvItemSrc.pszText != LPSTR_TEXTCALLBACK ) delete[] pszOrigText;
      delete pLVItem;
   }

   return(lResult);
}



/*** The items will be sorted ************************************************/
LRESULT IFDSListBase::OnSortItems(WPARAM wParam, LPARAM lParam)
{
   ASSERT(pListCtrl_);

   if( true == bInsertionSort_ )
   {
      bInsertionSort_ = false;
      enableSortIcon( true );
   }

   pfnLVCompare_ = reinterpret_cast<PFNLVCOMPARE>(lParam);

   return(pListCtrl_->DefWindowProc(LVM_SORTITEMS, reinterpret_cast<WPARAM>(this), reinterpret_cast<LPARAM>(CompareFunc)));
}

/*** System colors have been changed *****************************************/
void IFDSListBase::OnSysColorChange() 
{
   ASSERT(pListCtrl_);
   ASSERT(pListCtrl_->GetHeaderCtrl());

   pListCtrl_->Default();

   // update color of sort icons
   if( imglstSortIcons_.m_hImageList )
   {
      imglstSortIcons_.DeleteImageList();
      pBmpUpArrow_->DeleteObject();
      pBmpDownArrow_->DeleteObject();
      createSortIcons();
      pListCtrl_->GetHeaderCtrl()->SetImageList(&imglstSortIcons_);
      setSortIcon();
   }

   // force update of column colors
   bColorSortColumn_ = !bColorSortColumn_;
   colorSortColumn(!bColorSortColumn_);
}

/*** Return the index of a subitem, based in its order in the header control */
int IFDSListBase::orderToIndex(int nOrder)
{
   ASSERT(pListCtrl_);
   ASSERT(pListCtrl_->GetHeaderCtrl());

   return(pListCtrl_->GetHeaderCtrl()->OrderToIndex(nOrder));
}

/*** Prepare resources for hot underlining ***********************************/
void IFDSListBase::prepareHotUnderlining()
{
   ASSERT(pListCtrl_);

   if( !hcursorArrow_ ) hcursorArrow_ = LoadCursor(0, IDC_ARROW);
   if( !hcursorHand_ )
      if( WINVER <= 0x0400 )
         // Under Windows 95/NT we must create our own cursor
         // to indicate hot items
         hcursorHand_ = LoadCursor(AfxGetResourceHandle(), I_("IDC_HAND"));
      else
         hcursorHand_ = LoadCursor(0, IDC_HAND);
}

/*** Set cursor if hot-tracking is enabled ***********************************/
void IFDSListBase::setHotCursor(const CPoint& point)
{
   if( dwExtendedStyle_ & (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
                           LVS_EX_TWOCLICKACTIVATE) )
   {
      // determine item under mouse cursor (hot item) and
      // the appropriate mouse cursor
      UINT flags;
      int  nItem = pListCtrl_->HitTest(point, &flags);
      int  nOldHotItem = nHotItem_;

      nHotItem_ = nItem >= 0 &&
                  ( flags & LVHT_ONITEM & ~LVHT_ONITEMSTATEICON ) &&
                  ( dwExtendedStyle_ & LVS_EX_TWOCLICKACTIVATE ) &&
                  ( pListCtrl_->GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED ) ||
                  ( dwExtendedStyle_ & LVS_EX_ONECLICKACTIVATE)  ? nItem : -1 ;

      if( pListCtrl_->GetStyle() & LVS_OWNERDRAWFIXED )
      {
         hcursorCustom_ = nHotItem_ != -1 ? hcursorHand_ : hcursorArrow_;

         if( nHotItem_ != nOldHotItem )
         {
            CRect rc;

            if( nOldHotItem != -1 )
            {
               pListCtrl_->GetItemRect(nOldHotItem, rc, LVIR_BOUNDS);
               pListCtrl_->InvalidateRect(rc, FALSE);
            }
            if( nHotItem_ != -1 )
            {
               pListCtrl_->GetItemRect(nHotItem_, rc, LVIR_BOUNDS);
               pListCtrl_->InvalidateRect(rc, FALSE);
            }
         }

         SetCursor(hcursorCustom_);
      }
   }
}

/*** Display or hide sort icon on column to be sorted ************************/
void IFDSListBase::setSortIcon()
{
   ASSERT(pListCtrl_);
   CHeaderCtrl* pHeaderCtrl = pListCtrl_->GetHeaderCtrl();
   ASSERT(pHeaderCtrl);

   for( int col = static_cast<int>(aColumnData_.size() - 1 );
      col >= 0;
      col-- )
   {
      if( aColumnData_[col]->bVisible_ )
      {
         HDITEM hdrItem;
         int    nPhysicalCol = getPhysicalIndex(col);

         if( s_visualStyle_ == Present )
         {
            hdrItem.mask = HDI_FORMAT;
            pHeaderCtrl->GetItem(nPhysicalCol, &hdrItem);
            if( bSortIconEnabled_ &&
                iSortColumn_ != 0 &&
                iSortColumn_ - 1 == col )
            {
               hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING | HDF_SORTUP;
            }
            else if( bSortIconEnabled_ &&
                     iSortColumn_ != 0 &&
                     -iSortColumn_ - 1 == col )
            {
               hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING | HDF_SORTDOWN;
            }
            else
            {
               hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING;
            }
         }
         else
         {
            hdrItem.mask = HDI_FORMAT | HDI_IMAGE;
            pHeaderCtrl->GetItem(nPhysicalCol, &hdrItem);
            if( bSortIconEnabled_ &&
                iSortColumn_ != 0 &&
                iSortColumn_ - 1 == col )
            {
               hdrItem.iImage = nUpArrow_;
               hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_IMAGE | HDF_STRING | HDF_BITMAP_ON_RIGHT;
            }
            else if( bSortIconEnabled_ &&
                     iSortColumn_ != 0 &&
                     -iSortColumn_ - 1 == col )
            {
               hdrItem.iImage = nDownArrow_;
               hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_IMAGE | HDF_STRING | HDF_BITMAP_ON_RIGHT;
            }
            else
            {
               hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING;
            }
         }

         pHeaderCtrl->SetItem(nPhysicalCol, &hdrItem);
      }
   }
}

/*** Definition of structure "IFDSListBase::COLUMN_DATA" ************************/

/*** Destructor **************************************************************/
IFDSListBase::COLUMN_DATA::~COLUMN_DATA()
{
   if( pLVColumn_ )
   {
      delete[] pLVColumn_->pszText;
      delete pLVColumn_;
   }
}


/*** Definition of structure "IFDSListBase::ITEM_DATA" **************************/

/*** Destructor **************************************************************/
IFDSListBase::ITEM_DATA::~ITEM_DATA()
{
   for( int iColumn = apLVItem_.size() - 1; iColumn >= 0; iColumn-- )
   {
      LVITEM* pLVItem = apLVItem_[iColumn];

      if( pLVItem )
      {
         if( pLVItem->pszText != LPSTR_TEXTCALLBACK )
         {
            delete[] pLVItem->pszText;
         }
         delete pLVItem;
      }
   }
}


/*==========================================================================
 *----------------------- DSTListCtrl-related Methods ----------------------
 *==========================================================================*/
void IFDSListCtrl::PopulateList( const DString* rpStrKey )
{
   if( !IsDataConnected() || !idContainer_.isValid() )
   {
      return;
   }

   try {
      LockWindowUpdate();
//      SetDeleting( true );
      DeleteAllItems();
//      SetDeleting( false );
      PopulateListType( rpStrKey );
      UnlockWindowUpdate();
      RedrawWindow();
   } catch( ... ) {
      UnlockWindowUpdate();
      RedrawWindow();
      throw;
   }
}

void IFDSListCtrl::PopulateListType( const DString* rpStrKey )
{
   DString str;
   int nItem;
   m_sevMax = NO_SEVERITY;

   const DString* pKey = &m_rpParentDialog->getParent()->getFirstListItemKey( m_rpParentDialog, idContainer_ );

   if( *pKey == NULL_STRING )
   {
      if( IsUpdatable() && IsAutoAdd() )
      {  // Add row so we have something to work with
         AddRow();
      }
   }
   else
   {
      do
      {
         if( m_rpParentDialog->ListViewControlFilter( m_idSubstitute.getId() ) )
         {
            nItem = NewItem( reinterpret_cast< DWORD >( pKey ) );
         }
      } while( *(pKey = &(m_rpParentDialog->getParent()->getNextListItemKey( m_rpParentDialog, idContainer_ ) ) ) != NULL_STRING );
      SortListCtrl();
   }

   if( GetItemCount() > 0 )
   {  // Force selection
      int iItem = 0;

      if( rpStrKey != NULL )
      {  // Try to get key
         iItem = getItemNo( rpStrKey );
         if( -1 == iItem )
         {
            iItem = 0;
         }
      }
      SetSelection( iItem );

   }
   else
   {  // Disable associated controls here
      m_rpParentDialog->ConnectControlsToData( GetControlID(), false );
      // Make sure any sub-lists get cleared as well
      m_rpParentDialog->LoadChildListControls( GetControlID() );
   }
}

//******************************************************************************
int IFDSListCtrl::NewItem( DWORD dw )
{
   const DString* pKey = reinterpret_cast< const DString* >( dw );
   IFDSListCtrlRowDataBase* pItemData = getAdapter()->newItemData();
   pItemData->update( this->m_rpParentDialog, this, pKey );

   InsertItem( LVIF_PARAM | LVIF_TEXT,
               0,
               LPSTR_TEXTCALLBACK,
               INDEXTOSTATEIMAGEMASK( 1 ),
               LVIS_STATEIMAGEMASK,
               0,
               reinterpret_cast< LPARAM >( pItemData ) );
   // get item data and assign pKey to it!
   ITEM_DATA* pData = reinterpret_cast< ITEM_DATA* >( GetItemData( 0 ) );
   if( NULL != pKey ) 
   {
      pData->strKey_ = *pKey;
   }

   for( int iColumn = 1; iColumn < getColumnCount(); ++iColumn )
   {
      SetItemText(0, iColumn, LPSTR_TEXTCALLBACK);
   }
   m_currentItem = 0;
   if( IsUpdatable() )
   {
	attachConditionToItem( 0 );
   }
   return( m_currentItem );
}

void IFDSListCtrl::RefreshAllItems()
{
   const DString* pKey;
   m_sevMax = NO_SEVERITY;
   for( int iItem = 0; iItem < GetItemCount(); ++iItem )
   {
      pKey = getKey( iItem );
      m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog, idContainer_, *pKey );
   }

   // Reset current item
   int iCurItem = GetNextSelection();
   if( iCurItem != -1 )
   {
      pKey = getKey( iCurItem );
      m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog, idContainer_, *pKey );
   }
}

int IFDSListCtrl::GetNextSelection( int iItem ) const
{
   int rtn = GetNextItem( iItem, LVNI_SELECTED );

   // if not selected, try focused item
   return( rtn == -1 )? GetNextItem( iItem, LVIS_FOCUSED ) :rtn;
}

void IFDSListCtrl::RefreshCurrentItem(bool bReregisterObservers)
{
   int iItem = GetNextSelection();

   if( -1 != iItem )
   {
      const DString* pKey = getKey( iItem );

      m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog, idContainer_, *pKey );
      UpdateItem( iItem );

      if( bReregisterObservers )
      {
         m_rpParentDialog->ReregisterObservers( m_controlID );
      }

      // Load associated controls
      m_rpParentDialog->LoadControls( m_controlID );
   }
}

//******************************************************************************
void IFDSListCtrl::ResetCurrentItem()
{
   DString strKey = GetCurrentKey();

   if( strKey != NULL_STRING )
   {
      m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog, idContainer_, strKey );
      m_rpParentDialog->getParent()->resetCurrentItem( idContainer_ );

      // reset erased fieldinfo so we need to re-register observers
      RefreshCurrentItem(true);

      m_rpParentDialog->LoadChildListControls( m_controlID );
   }
}

//******************************************************************************
IFDSListCtrl& IFDSListCtrl::privInit()
{
   IFDSListBase::privInit();

   COLUMN_INFO_VECTOR vColumns = prepareColumns();
   getAdapter()->prepareColumns( this, vColumns );
   insertColumns( vColumns );

   enableSortIcon( true );
   colorSortColumn( true );
   setSortColumn( 1 );
   keepIconLeft( false );

   restoreState( m_strDialogName, m_strListName );

   getAdapter()->init( this );

   return( *this );
}

//******************************************************************************
void IFDSListCtrl::Init( BaseDlg* pDialog,
                         const BFFieldId& idSubstitute,
                         const BFContainerId& idContainer,
                         const I_CHAR* pszListName )
{
   m_rpParentDialog = pDialog;
   m_idSubstitute = idSubstitute;
   idContainer_ = idContainer;
   m_strListName = pszListName;

   // The ListView *must* be ownerdraw
   ASSERT( ( GetStyle() & LVS_OWNERDRAWFIXED ) == LVS_OWNERDRAWFIXED );

   // The ListView *must* has a column header
   ASSERT( ( GetStyle() & LVS_NOCOLUMNHEADER ) == 0 );

   // The ListView *must* be in ReportView
   ASSERT( ( GetStyle() & LVS_TYPEMASK ) == LVS_REPORT );

   DWORD dwStyle = GetStyle();
   dwStyle |= LVS_SINGLESEL;
   ::SetWindowLong( GetSafeHwnd(), GWL_STYLE, dwStyle ); 

   SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_SUBITEMIMAGES);

   privInit();
}

//******************************************************************************
void IFDSListCtrl::SetSelection( const DString *strKey,    // Row to set
                                 bool bSelect,             // true = select, false = unselect
                                 bool bVisible )           // true = ensure visible
{
   SetSelection( getItemNo( strKey ), bSelect, bVisible );
}

//******************************************************************************
void IFDSListCtrl::SetSelection( int iItem,              // Row to set
                                 bool bSelect,         // true = select, false = unselect
                                 bool bVisible )       // true = ensure visible
{
   int total = GetItemCount();

   if( !total )return;

   const DString* pKey;
   if( -1 == iItem || iItem >= total )
   {
      iItem = 0;
      pKey = &(m_rpParentDialog->getParent()->getFirstListItemKey( m_rpParentDialog, idContainer_ ));
   }
   else
   {
      pKey = getKey( iItem );
   }

   m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog, idContainer_, *pKey );

   int state = 0;

   if( bSelect )
   {
      state = LVIS_FOCUSED | LVIS_SELECTED;
   }
   SetItemState( iItem, state, LVIS_FOCUSED | LVIS_SELECTED );
   if( bVisible && bSelect )
   {  // Ensure visible if they have selected an item and want it visible
      EnsureVisible( iItem, FALSE );
   }
}

//******************************************************************************
SEVERITY IFDSListCtrl::SetSelectionWithSearch( const DString *pKey,
                                               bool bSelect /*= true*/,
                                               bool bVisible /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::GUI_CONDITION, CLASSNAME, I_( "SetSelectionWithSearch" ) ); 

   int itemNo = -1; 
   int total = GetItemCount();

   if( !total ) return NO_CONDITION;

   const DString* pKey_ = &m_rpParentDialog->getParent()->getFirstListItemKey( m_rpParentDialog, idContainer_);
   
   while (*pKey_ != *pKey && *pKey_ != NULL_STRING)
   {
      DString pKey__(*pKey_);

      if (*(pKey_ = &(m_rpParentDialog->getParent()->getNextListItemKey( m_rpParentDialog, idContainer_ ))) == NULL_STRING &&
           m_rpParentDialog->getParent ()->doMoreRecordsExist (m_rpParentDialog, idContainer_))
      {
         if ( m_rpParentDialog->getParent()->performSearch( m_rpParentDialog, 
                                                            idContainer_, 
                                                            SEARCH_NEXT_BLOCK) <= WARNING)
         {
            m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog, idContainer_, pKey__ );
            pKey_ = &(m_rpParentDialog->getParent()->getNextListItemKey (m_rpParentDialog, idContainer_));
         }
         else 
         {
            break;
         }
      }
   }
   if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      PopulateList (pKey);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}  


//******************************************************************************
void IFDSListCtrl::ConnectToData( bool bFlag, bool bShowHideBasedOnConnection )
{
   SetDataConnected( bFlag );
   if( bShowHideBasedOnConnection )
   {  // Show/Hide based on connection
      Show( bFlag );
   }
}

//******************************************************************************
const DString* IFDSListCtrl::getKey( int iItem ) const
{
   if( iItem >= 0 && iItem < GetItemCount() )
   {
      ITEM_DATA* pItemData = reinterpret_cast< ITEM_DATA* >( GetItemData( iItem ) );
      if( NULL != pItemData )
      {
         return( &pItemData->strKey_ );
      }
   }
   return( NULL );
}

//******************************************************************************
void IFDSListCtrl::setKey( int iItem, const DString& rKey )
{
   if( iItem >= 0 && iItem < GetItemCount() )
   {

      ITEM_DATA* pItemData = reinterpret_cast< ITEM_DATA* >( GetItemData( iItem ) );
      if( NULL != pItemData )
      {  
         pItemData->strKey_ = rKey;
      }
   }
}

//******************************************************************************
int IFDSListCtrl::getItemNo( const DString* pItemKey ) const
{
   if( NULL == pItemKey )
   {
      return( -1 );
   }
   for( int i = 0; i < GetItemCount(); i++ )
   {
      const DString* pKey = getKey( i );
      if( NULL != pKey && *pItemKey == *pKey )
      {
         return(i);
      }
   }
   return(-1);
}

//******************************************************************************
const DString& IFDSListCtrl::GetCurrentKey() const
{
   int iItem = GetNextSelection();

   if( iItem == -1 )
   {
      return(s_strEmpty_);
   }
   return(*(getKey( iItem ) ) );
}

//******************************************************************************
SEVERITY IFDSListCtrl::AddRow()
{
   MAKEFRAMEAUTOPROMOTE2( CND::GUI_CONDITION, CLASSNAME, I_( "AddRow" ) );

   const DString *pNewItemKey = &( m_rpParentDialog->getParent()->getKeyForNewListItem( m_rpParentDialog, idContainer_ ) );
   assert( pNewItemKey );

   if( pNewItemKey )
   {  // Add successful
      SetSelection( NewItem( (DWORD)pNewItemKey ) );
   }

   return(GETHIGHESTSEVERITY());
}

//******************************************************************************
void IFDSListCtrl::UpdateItem( int iItem )
{  // Assumes the current item has also been set current for the container
   if( -1 == iItem && iItem < GetItemCount() )
   {
      assert( 0 );
      return;
   }

   ITEM_DATA* pItemData = reinterpret_cast< ITEM_DATA* >( GetItemData( iItem ) );
   IFDSListCtrlRowDataBase* pRowData = reinterpret_cast< IFDSListCtrlRowDataBase* >( pItemData->lParam_ );
   pRowData->update( m_rpParentDialog, this, &pItemData->strKey_ );

   if( hasErrorIcon() )
   {
      if( IsUpdatable() )
	  {
		attachConditionToItem( iItem );
	  }
      Update( iItem );
   }
}

//******************************************************************************
void IFDSListCtrl::attachConditionToItem( int iItem )
{
   if( -1 < iItem && hasErrorIcon() )
   {
      // Also update image
      CONDITIONVECTOR vConditions;
      int iconConditions = 0;

      SEVERITY sevRtn = m_rpParentDialog->getParent()->getItemErrors( m_rpParentDialog, idContainer_, getKey( iItem ), ifds::NullFieldId, vConditions );
      if( sevRtn >  m_sevMax )
      {
         m_sevMax = sevRtn;
      }

      if( sevRtn > WARNING )
      {
         iconConditions = 3;
      }
      else if( sevRtn == WARNING )
      {
         iconConditions = 2;
      }
      else if( sevRtn == INFORMATIONAL )
      {
         iconConditions = 1;
      }
      // Set correct icon image
      SetItem( iItem, 0, LVIF_IMAGE, NULL, iconConditions, 0, 0, NULL );
   }
}

//******************************************************************************
LRESULT IFDSListCtrl::OnMouseLeave(WPARAM , LPARAM )
{
   MouseLeave();
   return(0);
}


//******************************************************************************
//  Tooltip display interface
//******************************************************************************
DSTMsg* IFDSListCtrl::GetToolTip()
{
   if( pToolTip_ == NULL )
   {
      pToolTip_ = new DSTMsg( GetWindow() );
   }
   return(pToolTip_);
}

//******************************************************************************
bool IFDSListCtrl::IsToolTipVisible()
{
   if( !ToolTipExists() )
   {
      return(false);
   }
   return(GetToolTip()->IsMsgAlreadyShown());
}

//******************************************************************************
void IFDSListCtrl::MouseLeave()
{
   if( !IsDataConnected() )
   {
      return;
   }
   if( ToolTipExists() )
   {
      GetToolTip()->MouseLeave();
   }
}

//******************************************************************************
void IFDSListCtrl::ToggleToolTip()
{
   if( !IsDataConnected() )
   {
      return;
   }

   GetToolTip()->ToggleMsgBox();
}

//******************************************************************************
void IFDSListCtrl::TriggerToolTip( int iItem )
{
   if( !IsDataConnected() || !IsVisible() )
   {
      return;
   }
//   if( !GetToolTip()->IsMsgAlreadyShown() /*&& !IsGUIField()*/ )
   {  // Controls must be associated with process/CBO field currently
      m_rpParentDialog->getParent()->getItemErrors( m_rpParentDialog, idContainer_, getKey( iItem ), ifds::NullFieldId, vConditions_ ); 
      GetToolTip()->SetMessageFromConditions( vConditions_ );
      GetToolTip()->DelayedDisplay();

      TRACKMOUSEEVENT MouseEvent;
      MouseEvent.cbSize = sizeof( TRACKMOUSEEVENT );
      MouseEvent.dwFlags = TME_LEAVE;
      MouseEvent.hwndTrack = GetWindow()->m_hWnd;
      MouseEvent.dwHoverTime = 0;
      ::_TrackMouseEvent( &MouseEvent );
   }
}

CWnd *IFDSListCtrl::GetWindow()
{
   CWnd *wnd = m_rpParentDialog->GetDlgItem( GetControlID() );

   if( !wnd )
   {
      assert( 0 );
      // TODO - set condition
      throw;
   }
   return(wnd);
}

//******************************************************************************

void IFDSListCtrl::ClearErrorState()
{
   vConditions_.clear();
   HideToolTip();
}

void IFDSListCtrl::ShowToolTip( int iItem )
{
   CONDITIONVECTOR vConditions;
   if( iItem >= 0 && iItem < GetItemCount() && 
       getItemConditions( iItem, vConditions ) >= WARNING )
   {
      {  
         GetToolTip()->SetMessageFromConditions( vConditions );
         GetToolTip()->ShowMsg( true, false );
      }
   }
   else if( ToolTipExists() )
   {  // Hide tooltip, if showing - error went away
      GetToolTip()->ShowMsg( false );
   }
}

//******************************************************************************

void IFDSListCtrl::HideToolTip()
{
   if( IsToolTipVisible() )
   {
      GetToolTip()->ShowMsg( false );
   }
}


SEVERITY IFDSListCtrl::getItemConditions( int iItem, CONDITIONVECTOR& rvConditions ) const
{
   SEVERITY sevRtn = m_rpParentDialog->getParent()->getItemErrors( m_rpParentDialog, 
                                                                   idContainer_, 
                                                                   getKey( iItem ),
                                                                   ifds::NullFieldId, 
                                                                   rvConditions );
   return( sevRtn );
}


