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
// ^FILE   : listctrl.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 5/22/97
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ListViewControl
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "listctrl.h"
#include "ConditionMessageDialog.h"
#include <ConfigManager.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <bfdata\bffieldid.hpp>
#include <MathString.hpp>
#include <bfproc\bfcontainerid.hpp>
#include <utility>

#include <assert.h>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const int GAPSIZE = 6;
   const I_CHAR *LV = I_( "LV_" );
   const I_CHAR *WORKSTATION = I_( "WORKSTATION" );
   const I_CHAR *DEFAULTWORKSTATION = I_("DefaultWorkstation");
   const I_CHAR *SETTINGS = I_( "SETTINGS" );

   // Trace literals
   const I_CHAR *CLASSNAME = I_( "ListViewControl" );

   const I_CHAR *COLUMNSORTOFF = I_( "ColumnSortOff" );
   const I_CHAR *DELETECOLUMN = I_( "DeleteColumn" );
   const I_CHAR *DELETEALLCOLUMNS = I_( "DeleteAllColumns" );
   const I_CHAR *GETNEXTSELECTION = I_( "GetNextSelection" );
   const I_CHAR *INSERTCOLUMN1 = I_( "InsertColumn1" );
   const I_CHAR *INSERTCOLUMN2 = I_( "InsertColumn2" ); 
   const I_CHAR *SETSELECTION = I_( "SetSelection" );
   const I_CHAR *SETSORTCOLUMN = I_( "SetSortColumn" );
   const I_CHAR *SAVESETTINGS = I_( "SaveSettings" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

class SortColumn
{
public:
   SortColumn()
   : m_pCaller( NULL )
   , idContainer_( BF::NullContainerId )
   , m_idField( ifds::NullFieldId )
   , m_iSortOrder( 0 )
   , m_wFlags( 0 )
   {
   }

   const GenericInterface *m_pCaller;
   BFContainerId idContainer_;
   BFFieldId m_idField;
   int m_iSortOrder;
   WORD m_wFlags;
};

static int m_ImageListCount=0;

//******************************************************************************
//              Static Functions
//******************************************************************************


//******************************************************************************
//    List Sorting implementor
//    This is the comparison function that must be supplied to the List Box
//    Sort method as a Callback.
//******************************************************************************
int CALLBACK ListViewControl::ListSorter( LPARAM lParam1, 
                                          LPARAM lParam2, 
                                          LPARAM lParamSort )
{
   // Both Item data parameters and the sorter object must be set
   if( lParam1 && lParam2 && lParamSort )
   {
      // Access passed parameter (pointer to Sort column description)
      SortColumn* pSortColumn = reinterpret_cast< SortColumn* >( lParamSort );
      DString strValue1, strValue2;

      const DString *pKey1 = reinterpret_cast< DString * >( lParam1 );
      pSortColumn->m_pCaller->getParent()->setCurrentListItem( pSortColumn->m_pCaller, 
                                                               pSortColumn->idContainer_, 
                                                               *pKey1 );
      pSortColumn->m_pCaller->getParent()->getField( pSortColumn->m_pCaller,
                                                     pSortColumn->idContainer_, 
                                                     pSortColumn->m_idField, 
                                                     strValue1 );
      strValue1.strip();
      const DString *pKey2 = reinterpret_cast< DString * >( lParam2 );
      pSortColumn->m_pCaller->getParent()->setCurrentListItem( pSortColumn->m_pCaller, 
                                                               pSortColumn->idContainer_, 
                                                               *pKey2 );
      pSortColumn->m_pCaller->getParent()->getField( pSortColumn->m_pCaller,
                                                     pSortColumn->idContainer_, 
                                                     pSortColumn->m_idField, 
                                                     strValue2 );
      strValue2.strip();

      int iRet = 0;

      // Different method used determined by type of element being sorted
      const BFDataFieldProperties* pProps = 
      pSortColumn->m_pCaller->getFieldAttributes( pSortColumn->m_pCaller, pSortColumn->m_idField );

      if( pProps->isText() )
      {
         if( pSortColumn->m_wFlags & STRING_UPPERCASE )
         {
            strValue1.upperCase();
            strValue2.upperCase();
         }
         if( strValue1 < strValue2 )
            iRet = -1;
         else if( strValue1 > strValue2 )
            iRet = 1;
         else//Redundant; just for clarity
            iRet = 0;
      }
      else if( pProps->isInteger() )
      {
         int iNum1 = strValue1.asInteger();
         int iNum2 = strValue2.asInteger();
         if( iNum1 < iNum2 )
            iRet = -1;
         else if( iNum1 > iNum2 )
            iRet = 1;
         else//Redundant; just for clarity
            iRet = 0;
      }
      else if( pProps->isDecimal() )
      {
         MathString mStrValue1( strValue1.c_str() );
         MathString mStrValue2( strValue2.c_str() );
         if( mStrValue1 < mStrValue2 )
            iRet = -1;
         else if( mStrValue1 > mStrValue2 )
            iRet = 1;
         else//Redundant; just for clarity
            iRet = 0;
      }
      else
      {
         iRet = 0;//Redundant; just for clarity
      }

      return( iRet * ( pSortColumn->m_iSortOrder ) );
   }
   else
      return(0);
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//******************************************************************************
//              Constructor
//******************************************************************************

ListViewControl::ListViewControl( bool bShowSelAlways ) 
: CListCtrl()
, m_bShowSelAlways( bShowSelAlways )
, m_columnCount( 0 )
, lvSettingName (NULL)
, DlgName (NULL)
, m_bSetSizeOnce( false )
, _pBD (NULL)
, _idSubstitute(ifds::NullFieldId)
, idList_( BF::NullContainerId )
, bIsDelete (false)
, bIsAdd(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );
   // Initialize sort column array
   memset( &m_SortArray, 0, sizeof( m_SortArray ) );


/* if(++m_ImageListCount==1)
   {
      m_Icons = new CImageList();
      ASSERT(m_Icons != NULL);    // serious allocation failure checking
      m_Icons->Create(16, 16, ILC_COLOR,   4,4);
      m_Icons->Add(AfxGetApp()->LoadIcon( IDI_NO_ERR_ICON ));
      m_Icons->Add(LoadIcon( NULL, IDI_HAND ));
      m_Icons->Add(LoadIcon( NULL, IDI_EXCLAMATION ));
      m_Icons->Add(LoadIcon( NULL, IDI_ASTERISK ));
   }
   */
}

//******************************************************************************

ListViewControl::~ListViewControl()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _fieldIDs.clear();

// if(--m_ImageListCount==0)
//    delete m_Icons;
}

//******************************************************************************

void ListViewControl::ColumnSortOff( int nCol )
{
   TRACE_METHOD( CLASSNAME, COLUMNSORTOFF );
   // Deallocate sort description and clear array entry
   if( m_SortArray[ nCol ] )
   {
      delete m_SortArray[ nCol ];
      m_SortArray[ nCol ] = NULL;
   }
}

//******************************************************************************

void ListViewControl::DeleteAllColumns()
{  
   TRACE_METHOD( CLASSNAME, DELETEALLCOLUMNS );
   int i;
   int count = GetColumnCount();

   if( 0 >= count )
   {  // nothing to do
      return;
   }

   for( i = 0; i < count; ++i )
   {
      DeleteColumn( 0 );
   }
}

//******************************************************************************

bool ListViewControl::DeleteColumn(
                                  int nCol
                                  )
{  // Replaced to track column count
   TRACE_METHOD( CLASSNAME, DELETECOLUMN );

   if( CListCtrl::DeleteColumn( nCol ) )
   {  // Decrement column count
      m_columnCount--;
      return(true);
   }
   return(false);
}

//******************************************************************************

void ListViewControl::DrawItem( LPDRAWITEMSTRUCT pdi )
{
   LV_ITEM lvi;

   lvi.mask       = LVIF_IMAGE | LVIF_STATE;
   lvi.iItem      = pdi->itemID;
   lvi.iSubItem   = 0;
   lvi.stateMask  = 0xFFFF;

   if( GetItem( &lvi) )
   {
      /* We have disabled right column anchoring
      CRect vr;
      GetClientRect( &vr );
      if ( vr.right > pdi->rcItem.right )
      {
         if ( m_columnCount > 0 )
         {
            int w = GetColumnWidth( m_columnCount - 1 );
            SetColumnWidth( m_columnCount - 1, w + vr.right -
               pdi->rcItem.right - 1 );
         }
      }
      */
//    pdi->rcItem.top=20*lvi.iItem;
//    pdi->rcItem.bottom=pdi->rcItem.top+20;



      CRect rcAllLabels = pdi->rcItem;
      CRect rcLabel;
      GetItemRect( pdi->itemID, rcLabel, LVIR_LABEL );
      rcAllLabels.left = rcLabel.left;

      bool bFocus     = ( GetFocus() == this );
      bool bEnabled   = IsWindowEnabled() != FALSE;
      bool bSelected  = ( lvi.state & LVIS_SELECTED  ) == LVIS_SELECTED;
      bool bFocusItem = ( lvi.state & LVIS_FOCUSED  ) == LVIS_FOCUSED;

      UINT uiFlags   = ILD_TRANSPARENT;
      if( bEnabled && bSelected && ( bFocus || m_bShowSelAlways ) )
      {
         // Add ILDBLEND so images come out selected if enabled, selected,
         // and focused or show sel always
         uiFlags |= ILD_BLEND50;
      }

      COLORREF foreColor = 0;
      COLORREF backColor = 0;
      COLORREF backgroundColor = 0;
      GetDrawColors( pdi->itemID, bEnabled, bFocus, bSelected || bFocusItem, foreColor, 
                     backColor, backgroundColor );
      CDC *pDC = CDC::FromHandle( pdi->hDC );

      COLORREF oldTextColor = pDC->SetTextColor( foreColor );
      COLORREF oldBkColor = pDC->SetBkColor( backColor );
      pDC->FillRect( rcAllLabels, &CBrush( backgroundColor ) );



/*
      if(_idSubstitute) // sub list is used
      {
         CRect rcIcon;
         GetItemRect(pdi->itemID, rcIcon, LVIR_ICON);
         ImageList_DrawEx(m_Icons->m_hImageList, lvi.iImage,
                  pDC->m_hDC,rcIcon.left,rcIcon.top, 16, 16,
                  CLR_NONE  , CLR_NONE  , ILD_TRANSPARENT );
      }
*/


      int pos     = 0;                          // Pixel position of column
      int cxImage = 0;                          // Right boundary of image

      // Set up global top/bottom clipping
      RECT r;
      r.top    = pdi->rcItem.top;
      r.bottom = pdi->rcItem.bottom;
      r.right  = pdi->rcItem.left + pos;        // Prime pump for loop

      LV_COLUMN lvc;
      lvc.mask = LVCF_FMT | LVCF_WIDTH;

      // Probably should worry about alignment, too
      UINT svAlign = GetTextAlign( pdi->hDC );
      UINT newAlign = 0;
      I_CHAR col[256] = NULL_STRING;

      int i = 0;
      while( GetColumn( i, &lvc ) )
      {  // Getting column width
         if( lvc.cx != 0 )
         {
            r.left = r.right;
            r.right = r.left + lvc.cx;
            col[ 0 ] = '\0';
            GetItemText( lvi.iItem, i, col, sizeof( col ) );
            if( lvc.fmt & LVCFMT_CENTER )
            {
               newAlign = DT_CENTER;
            }
            else if( lvc.fmt & LVCFMT_LEFT )
            {
               newAlign = DT_LEFT;
            }
            else if( lvc.fmt & LVCFMT_RIGHT )
            {
               newAlign = DT_RIGHT;
            }
            else
            {
               newAlign = DT_LEFT;
            }
            DrawItemColumn( pDC, col, &r, newAlign );
         }
         ++i;
      }

      pDC->SetTextColor( oldTextColor );
      pDC->SetBkColor(   oldBkColor   );

      if( bEnabled && bFocus && ( pdi->itemState & ODS_FOCUS ) )
      {  // If item is focused, draw focus rect around row
         // Adjust left edge to exclude the image
         r = pdi->rcItem;
         r.left += cxImage;
         DrawFocusRect( pdi->hDC, &r );
      }
   }
}

//******************************************************************************

void ListViewControl::GetDrawColors(
                                   int       row,    // index of the listview item to draw
                                   bool      enabled,
                                   bool      focused,
                                   bool      selected,
                                   COLORREF &foreColor,
                                   COLORREF &backColor,
                                   COLORREF &backgroundColor
                                   )
{
   if( !enabled )
   {
      // Disabled is no selection, dark grey text and light grey background
      foreColor       = ::GetSysColor( COLOR_3DSHADOW );
      backColor       = ::GetSysColor( COLOR_BTNFACE );
      backgroundColor = ::GetSysColor( COLOR_BTNFACE );
   }
   else if( selected && ( focused || m_bShowSelAlways ) )
   {
      // We are showing a selection in an enabled window because we are
      // focused or because we always show one.
      foreColor       = ::GetSysColor( COLOR_HIGHLIGHTTEXT );
      backColor       = ::GetSysColor( COLOR_HIGHLIGHT );
      backgroundColor = ::GetSysColor( COLOR_HIGHLIGHT );
   }
   else
   {
      // We are not showing a selection in an enabled window
      foreColor       = ::GetSysColor( COLOR_WINDOWTEXT );
      backColor       = ::GetSysColor( COLOR_WINDOW );
      backgroundColor = ::GetSysColor( COLOR_WINDOW );
   }
}

//******************************************************************************

int ListViewControl::GetNextSelection(       // Get next selected item
                                             int idx                                   // Index to start after (-1 = all)
                                     )                                         // Returns index of first selected
{
   TRACE_METHOD( CLASSNAME, GETNEXTSELECTION );

   int rtn = GetNextItem( idx, LVNI_SELECTED );

   // if not selected, try focused item
   return( rtn == -1 )? GetNextItem( idx, LVIS_FOCUSED ) :rtn;
}

//******************************************************************************

int ListViewControl::InsertColumn(
                                 int nCol,
                                 const LV_COLUMN *pColumn
                                 )
{  // Replaced to track column count
   TRACE_METHOD( CLASSNAME, INSERTCOLUMN1 );

   // Currently, we are calling SetItemSize because the
   // original WM_MEASUREITEM happens before we get subclassed.
   SetItemSize();

   int rtn = CListCtrl::InsertColumn( nCol, pColumn );

   if( rtn != -1 )
   {  // Successful insert so add to counter
      ++m_columnCount;
   }
   return(rtn);
}

//******************************************************************************

int ListViewControl::InsertColumn(
                                 int nCol,
                                 LPCTSTR lpszColumnHeading,
                                 int nFormat,
                                 int nWidth,
                                 int nSubItem
                                 )
{  // Replaced to track column count
   TRACE_METHOD( CLASSNAME, INSERTCOLUMN2 );

   // Currently, we are calling SetItemSize because the
   // original WM_MEASUREITEM happens before we get subclassed.
   SetItemSize();
   int rtn = CListCtrl::InsertColumn( nCol, lpszColumnHeading, nFormat, nWidth,
                                      nSubItem );

   if( rtn != -1 )
   {  // Successful insert so add to counter
      ++m_columnCount;
   }
   return(rtn);
}

//******************************************************************************

bool ListViewControl::LoadSettings(
                                  const I_CHAR *dialogName,
                                  const I_CHAR *lvName
                                  )
{
   DlgName=dialogName;
   lvSettingName=lvName;

   int i;
   int count = 0;
   bool useDefault=false;
   DString strHold;
   DString title( LV );
   title += lvName;

   ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
   Configuration workstation = pWorkstation->retrieveConfig( dialogName );

   // Get column count
   strHold = title;
   strHold += I_( ".colcount" );
   strHold = workstation.getValueAsString( strHold );
   if( strHold.empty() )
   {
      // try to get the default column setting
      pWorkstation = ConfigManager::getManager( DEFAULTWORKSTATION );
      workstation = pWorkstation->retrieveConfig( dialogName );
      strHold = title;
      strHold += I_( ".colcount" );
      strHold = workstation.getValueAsString( strHold );
      if( strHold.empty() )
         useDefault=true;
   }
   else
   {
      count = asInteger( strHold );
      if( count <= 0 )
      {
         return(false);
      }
   }

   LVCOLUMN col;
   col.mask = LVCF_WIDTH | LVCF_FMT;
   DString fmt;


   if( _idSubstitute != ifds::NullFieldId ) // sub list is used
   {
      COLUMNMAP_ITER Iter ;
      COLUMNMAP_ITER IterEnd = ColumnMap.end();

      Iter =    ColumnMap.begin();
      while( Iter != IterEnd )
      {
         if( (*Iter).first != NULL_STRING )
         {
            strHold = title;
            strHold += I_( "." );
            strHold += (*Iter).first;

            col.cx=100;
            col.fmt=0;
            if( !useDefault )
            {
               strHold = workstation.getValueAsString( strHold );
               if( !strHold.empty() ) 
               {
                  i_sscanf(strHold.c_str(), I_("%d,%d"), &col.cx, &col.fmt);
               }
            }
            // sanity check on column width
            col.cx = std::max( 0, std::min( col.cx, 1000 ) );

            SetColumn( (*Iter).second, &col );
         }
         ++Iter;
      }
   }
   else
   {
      for( i = 0; i < count; ++i )
      {
         col.cx=100;
         col.fmt=0;

         strHold = title;
         strHold += I_( ".col" );
         strHold += asString( i );
         strHold = workstation.getValueAsString( strHold );
         if( !strHold.empty() )
         {
            i_sscanf(strHold.c_str(), I_("%d,%d"), &col.cx, &col.fmt);
         }
         // sanity check on column width
         col.cx = std::max( 0, std::min( col.cx, 1000 ) );
         SetColumn( i, &col );
      }
   }

   return(true);
}

//******************************************************************************

bool ListViewControl::SaveSettings(
                                  const I_CHAR *dialogName,
                                  const I_CHAR *lvName
                                  )
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, SAVESETTINGS );

   bool result = false;

   try
   {
      int count = GetColumnCount();

      if( count > 0 )
      {
         ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
         Configuration workstation = pWorkstation->retrieveConfig( dialogName );

         LV_COLUMN col;
         col.mask = LVCF_WIDTH | LVCF_FMT;

         DString title( LV );
         title += lvName;

         DString strHold( title );
         strHold += I_( ".colcount=" );
         strHold += asString( count );
         workstation.set( strHold );

         if( _idSubstitute != ifds::NullFieldId ) // sub list is used
         {
            COLUMNMAP_ITER Iter ;
            COLUMNMAP_ITER IterEnd = ColumnMap.end();

            Iter =    ColumnMap.begin();
            while( Iter != IterEnd )
            {
               if( (*Iter).first != NULL_STRING )
               {
                  if( GetColumn( (*Iter).second, &col ) )
                  {  // Save settings
                     strHold = title;
                     strHold += I_( "." );
                     strHold += (*Iter).first;
                     strHold += I_( "=" );
                     strHold += asString( col.cx );

                     strHold += I_( "," );

                     strHold += asString( col.fmt & LVCFMT_JUSTIFYMASK );  // get format


                     workstation.set( strHold );
                  }
               }
               ++Iter;
            }
         }
         else
         {
            for( int i = 0; i < count; ++i )
            {
               if( GetColumn( i, &col ) )
               {  // Save settings
                  strHold = title;
                  strHold += I_( ".col" );
                  strHold += asString( i );
                  strHold += I_( "=" );

                  strHold += asString( col.cx );

                  strHold += I_( "," );

                  strHold += asString( col.fmt & LVCFMT_JUSTIFYMASK );  // get format

                  workstation.set( strHold );
               }
            }
         }

         pWorkstation->storeConfig( workstation );
         pWorkstation->persist();   // Throws on bad reg config

         result = true;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   return(result);
}

//******************************************************************************

void ListViewControl::SetSelection(          // Set selection state of row
                                             int idx,                                  // Row to set
                                             bool bSelect,                             // true = select, false = unselect
                                             bool bVisible                             // true = ensure visible
                                  )                                         // If select, row will get focus
{
   TRACE_METHOD( CLASSNAME, SETSELECTION );

   int state = 0;

   if( bSelect )
   {
      state = LVIS_FOCUSED | LVIS_SELECTED;
   }
   SetItemState( idx, state, LVIS_FOCUSED | LVIS_SELECTED );
   if( bVisible && bSelect )
   {  // Ensure visible if they have selected an item and want it visible
      EnsureVisible( idx, false );
   }
}

//******************************************************************************

int ListViewControl::SetSortColumn(
                                  int nCol,
                                  const GenericInterface *pCaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId &idField,
                                  int iSortOrder,
                                  WORD wFlags
                                  )
{
   TRACE_METHOD( CLASSNAME, SETSORTCOLUMN );
   int nRet = 0;
   // Create sort description for column, if not one already
   // created
   if( m_SortArray[ nCol ] == NULL )
   {
      m_SortArray[ nCol ] = new SortColumn;
   }
   SortColumn* SortCol = m_SortArray[ nCol ];
   SortCol->m_pCaller = pCaller;
   SortCol->idContainer_ = idContainer;
   SortCol->m_idField = idField;
   SortCol->m_iSortOrder = iSortOrder;
   SortCol->m_wFlags = wFlags;
   return(nRet);
}


//******************************************************************************

bool ListViewControl::SortOnColumn( int column )
{
   bool bRtn = false;

   if( column < m_columnCount )
   {  // range ok
      // Hold sort description for selected column
      SortColumn* SortCol = m_SortArray[ column ];
      // Determine if column is set up for sorting
      if( SortCol )
      {
         // Call control sort manager with address of Callback
         // compare function and selected columns sort
         // description
         bRtn = SortItems( (PFNLVCOMPARE)ListSorter,
                           (DWORD)SortCol ) != 0;
         // Ensure column sorts in opposite order next time clicked
         ( SortCol->m_iSortOrder ) *= -1;
      }
   }
   return(bRtn);
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

BEGIN_MESSAGE_MAP(ListViewControl, CListCtrl)
//{{AFX_MSG_MAP(ListViewControl)
ON_WM_KILLFOCUS()
ON_WM_SETFOCUS()
ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
ON_WM_DESTROY()
ON_WM_MEASUREITEM_REFLECT()
ON_WM_CREATE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
//              Message Handlers
//******************************************************************************

void ListViewControl::MeasureItem( LPMEASUREITEMSTRUCT lpmis ) 
{
   if( !m_bSetSizeOnce )
   {  //  We are currently only doing this once - if need to allow for
      //  dynamic changes, this would have to change
      TEXTMETRIC tm;
      HDC hDC = ::GetDC(NULL);
      CFont* pFont = GetFont();
      HFONT hFontOld = (HFONT)SelectObject(hDC, pFont->GetSafeHandle());
      GetTextMetrics(hDC, &tm);
      lpmis->itemHeight = tm.tmHeight + tm.tmExternalLeading + 1;
      SelectObject(hDC, hFontOld);
      ::ReleaseDC(NULL, hDC);
   }
}

//******************************************************************************

void ListViewControl::OnKillFocus(CWnd* pNewWnd)
{
   CListCtrl::OnKillFocus(pNewWnd);

   // Check if we are losing focus to label edit box
   if( pNewWnd != NULL && pNewWnd->GetParent() == this )
      return;
   RepaintSelectedItems();

   if( DlgName!=NULL && lvSettingName!=NULL )
      SaveSettings(DlgName,lvSettingName);
}

//******************************************************************************

void ListViewControl::OnSetFocus(CWnd* pOldWnd)
{
   CListCtrl::OnSetFocus(pOldWnd);

   // Check if we are getting focus to label edit box
   if( pOldWnd != NULL && pOldWnd->GetParent() == this )
      return;
   RepaintSelectedItems();
}

//******************************************************************************
//
//  ^PROTECTED METHOD : ListViewControl::OnColumnclick
//
//  ^DESCRIPTION      : Click on a column header instigates a sort of the list
//                      control on the clicked column.
//
//  ^PARAMETERS     : none
//
// ^RETURNS         : none
//
// ^THROWS          :
//
// ^EXAMPLE         :
//
//******************************************************************************
void ListViewControl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
{
   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
   BOOL  fRet;

   // Selected column
   int   SelectedCol = pNMListView->iSubItem;
   // Hold sort description for selected column
   SortColumn* SortCol = m_SortArray[ SelectedCol ];
   // Determine if column is set up for sorting
   if( SortCol )
   {
      // Call control sort manager with address of Callback
      // compare function and selected columns sort
      // description
      fRet = SortItems( /*(PFNLVCOMPARE)*/&ListSorter,
                        (DWORD)SortCol );
      // Ensure column sorts in opposite order next time clicked
      ( SortCol->m_iSortOrder ) *= -1;
   }
   *pResult = 0;
}

//******************************************************************************
//
//  ^PROTECTED METHOD : ListViewControl::OnDestroy
//
//  ^DESCRIPTION      : Called when list window is being destroyed.
//
//  ^PARAMETERS     : none
//
// ^RETURNS         : none
//
// ^THROWS          :
//
// ^EXAMPLE         :
//
//******************************************************************************
void ListViewControl::OnDestroy()
{
   // Make sure sorting array cleared
   SortColumn* pSortColumn;
   int i;
   // Delete any sort column entries
   for( i = 0; i < MAX_COLUMNS; ++i )
   {
      pSortColumn = m_SortArray[i];
      if( pSortColumn )
      {
         delete pSortColumn;
         m_SortArray[i] = NULL;
      }
   }

   CListCtrl::OnDestroy();
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
//  ^PRIVATE METHOD : ListViewControl::DrawItemColumn
//
//  ^DESCRIPTION    : Draws the text for one of the columns in the list view.
//
//  ^PARAMETERS     :
//     ^^ CDC *pDC       - DC to draw the text into.
//     ^^ LPTSTR lpsz    - String to draw.
//     ^^ LPRECT prcClip - Rectangle to clip the string to.
//     ^^ UINT fmt       - How to format
//
// ^RETURNS         : none
//
// ^THROWS          :
//
// ^EXAMPLE         :
//
//******************************************************************************

void ListViewControl::DrawItemColumn( CDC *pDC, LPTSTR lpsz, LPRECT prcClip,
                                      UINT fmt )
{
   // DT_END_ELLIPSIS is only supported on 32 bit platforms & I'm not sure
   //  about NT 3.51 or below
   UINT myFmt = fmt | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER 
                | DT_END_ELLIPSIS;
   RECT r = *prcClip;

   if( r.right - r.left > 4 * GAPSIZE )
   {  // Only do gap if reasonable amount of room
      r.left += GAPSIZE;
      r.right -= GAPSIZE;
   }
   // print the text
   pDC->DrawText( lpsz, -1, &r, myFmt );
}

//******************************************************************************
//
//  ^PRIVATE METHOD : ListViewControl::RepaintSelectedItems
//
//  ^DESCRIPTION    : Repaint an item
//
//  ^PARAMETERS     : none
//
// ^RETURNS         : none
//
// ^THROWS          :
//
// ^EXAMPLE         :
//
//******************************************************************************

void ListViewControl::RepaintSelectedItems()
{
   CRect rcItem, rcLabel;
   CRect rcIcon;
   // Invalidate focused item so it can repaint properly
   int idx = GetNextItem( -1, LVNI_FOCUSED );

   //if ( idx != -1 )
   {  // Invalidate rectangle
      GetItemRect( idx, rcItem, LVIR_BOUNDS );
      InvalidateRect( rcItem, false );
   }

   // If selected items should not be preserved, invalidate them
   if( !m_bShowSelAlways )
   {
      idx = -1;
      while( ( idx = GetNextItem( idx, LVNI_SELECTED ) ) != -1 )
      {  // Loop through selections
         GetItemRect( idx, rcItem, LVIR_BOUNDS );
         InvalidateRect( rcItem, false );
      }
   }
   UpdateWindow();
}

//******************************************************************************

void ListViewControl::SetItemSize()
{
   if( !m_bSetSizeOnce )
   {  // Currently, we are only doing this once.  If we need to allow
      // for dynamic changing of fonts this would need to change.

      // We are using WM_WINDOWPOSCHANGED to cause the WM_MEASUREITEM
      // message to occur per information on internet site CODEGURU.

      // Currently, we are calling this from InsertColumn methods because the
      // original WM_MEASUREITEM happens before we get subclassed.

      CRect rc;
      WINDOWPOS wp;

      GetWindowRect( &rc );
      wp.hwnd = m_hWnd;
      wp.cx = rc.Width();
      wp.cy = rc.Height();
      wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
      SendMessage( WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp );
      m_bSetSizeOnce = true;
   }
}

//******************************************************************************

void ListViewControl::SetColumnHeadings(const BFFieldId &idSubstitute, int nFormat , int nWidth )
{
   DString strIdi;
   DString strTag;
   DString strValue;
   int col = 0;

   DeleteAllItems();
   DeleteAllColumns();
   ColumnMap.clear();

   const BFDataFieldProperties* pProps = _pBD->getFieldAttributes( _pBD, idSubstitute );

   if( pProps->getSubstitutionSet( ClientLocaleContext::get() ) )
   {
      pProps->getAllSubstituteValues( strIdi, ClientLocaleContext::get(), true );
   }
   else
   {  // problem ??
      assert( 0 );
      return;
   }

   I_CHAR *rpStr = const_cast< I_CHAR * >( strIdi.c_str() );

   while( *rpStr != '\0' )
   {
      rpStr = parseIdiString( rpStr, strTag, strValue );
      if( strTag != NULL_STRING )
      {
         ColumnMap.insert( COLUMNMAP::value_type( strTag, col ) );

         InsertColumn( col++, strValue.strip().c_str(), nFormat, nWidth );
      }
   }
}

//******************************************************************************

int ListViewControl::NewItem(DWORD ItemData)
{
   CurrentItem = InsertItem( 99999, _T("") );

   if( CurrentItem != -1 )
   {
      SetItemData( CurrentItem, ItemData );
   }

   return(CurrentItem);
}

//******************************************************************************

void ListViewControl::PopulateList()
{
   if( !idList_.isValid() ) return;

   DeleteAllItems();

   int nItem;
   COLUMNMAP_ITER Iter ;
   COLUMNMAP_ITER IterEnd = ColumnMap.end();

   DString str;
   const DString* key = &_pBD->getParent()->getFirstListItemKey( _pBD, idList_ );

   if( (*key) == NULL_STRING )
   {
      return;
   }

   do
   {
      if( _pBD->ListViewControlFilter( _idSubstitute.getId() ) )
      {
         nItem=NewItem((DWORD)key );

         Iter =    ColumnMap.begin();
         while( Iter != IterEnd )
         {
            if( (*Iter).first != NULL_STRING )
            {
               // get str from 
               if( _pBD->GetOverrideItemString(_idSubstitute.getId(),(*Iter).first, str)!=true )
               {
                  _pBD->getParent()->getField( _pBD, 
                                               idList_,
                                               BFFieldId::getId( (*Iter).first ),
                                               str );
                  str.strip();
               }

			   BFFieldId fieldId = BFFieldId::getId( (*Iter).first );
               doSetItemText(nItem,(*Iter).second,str.c_str(), fieldId);
            }
            ++Iter;
         }
      }
   }while( *(key = &(_pBD->getParent()->getNextListItemKey( _pBD, idList_ ))) != NULL_STRING );
}

//******************************************************************************

void ListViewControl::Init(
                          BaseDlg *pBD, 
                          const BFFieldId &idSubstitute, 
                          const BFContainerId& idList,
                          const I_CHAR *dialogName,
                          const I_CHAR *lvName)
{
   _pBD = pBD;

   _idSubstitute = idSubstitute;
   idList_ = idList;

   SetColumnHeadings( idSubstitute, LVCFMT_LEFT , 100 );
   LoadSettings(dialogName, lvName);
}

//******************************************************************************

// set the str to the cell
// ColumnKey is the code in the sub list
BOOL ListViewControl::SetItemString(int nItem, const I_CHAR * ColumnKey, DString &Str)
{
   if( _idSubstitute != ifds::NullFieldId ) // sub list is used
   {
      COLUMNMAP_ITER Iter = ColumnMap.find(ColumnKey);

      if( Iter != ColumnMap.end() )
      {
		 BFFieldId fieldId = BFFieldId::getId( (*Iter).first );
         return(doSetItemText( nItem, (*Iter).second,Str.c_str(), fieldId ));
      }
   }

   return(FALSE);
}

//******************************************************************************

BOOL ListViewControl::SetItemString(DWORD ItemData, const I_CHAR * ColumnKey, DString &Str)
{
   int index=-1;
   for( int i=0;i<GetItemCount();i++ )
   {
      if( GetItemData(i) == ItemData )
      {
         index=i;
         break;
      }
   }

   if( index!=-1 )
      return(SetItemString( index, ColumnKey, Str));
   else
      return(FALSE);
}

//******************************************************************************
BOOL ListViewControl::doSetItemText( int nItem, int nSubItem, LPCTSTR lpszText, BFFieldId fieldId )
{
	DString str = lpszText;
	BaseDlg::DisplayFormat( str, fieldId );	
		
	return ( SetItemText(nItem, nSubItem, str.strip().c_str() ));
}

//******************************************************************************

// get the str from the cell
// ColumnKey is the code in the sub list
CString ListViewControl::GetItemString(int nItem, const I_CHAR * ColumnKey) const
{
   if( _idSubstitute != ifds::NullFieldId ) // sub list is used
   {
      COLUMNMAP_CONST_ITER Iter = ColumnMap.find(ColumnKey);

      if( Iter != ColumnMap.end() )
      {
	     CString cstr = GetItemText( nItem, (*Iter).second );
		 DString dstr = cstr;
		 BFFieldId fieldId = BFFieldId::getId( (*Iter).first );
		 BaseDlg::DisplayUnFormat( dstr, fieldId );
         return( dstr.c_str() );
      }
   }

   return(_T(""));
}

//******************************************************************************

int ListViewControl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if( CListCtrl::OnCreate(lpCreateStruct) == -1 )
      return(-1);

// if(_Substitute) // sub list is used
//    SetImageList(m_Icons, LVSIL_SMALL);

   return(0);
}

//******************************************************************************

void ListViewControl::SetStateIcon(int nItem, int Severty)
{
   LV_ITEM lvi;
   lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
   lvi.iItem = nItem;
   lvi.iSubItem = 0;
   lvi.stateMask = 0xFFFF;     
   GetItem(&lvi);

   lvi.iImage=Severty; // select image that reflect severty
   SetItem(&lvi);

   SetItemText(nItem,0,_T(""));
}

//******************************************************************************

// get item number using its key, return -1 when no row is found
int ListViewControl::GetItemNo(DString *pKey)
{
   for( int i=0; i<GetItemCount(); i++ )
   {
      if( *((DString *)GetItemData(i)) == *pKey )
         return(i);
   }

   return(-1);
}

//******************************************************************************

void ListViewControl::UpdateItem(DString *pKey)
{
   int nItem = GetItemNo( pKey );

   if( nItem != -1 )
   {
      DString str;
      COLUMNMAP_ITER Iter ;
      COLUMNMAP_ITER IterEnd = ColumnMap.end();

      Iter =    ColumnMap.begin();
      while( Iter != IterEnd )
      {
         if( (*Iter).first != NULL_STRING )
         {
            // get str from 
            if( _pBD->GetOverrideItemString(_idSubstitute.getId(), (*Iter).first, str)!=true )
            {
               _pBD->getParent()->getField( _pBD, 
                                            idList_,
                                            BFFieldId::getId( (*Iter).first ),
                                            str );
            }

			BFFieldId fieldId = BFFieldId::getId( (*Iter).first );
            doSetItemText(nItem,(*Iter).second,str.strip().c_str(), fieldId);
         }
         ++Iter;
      }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/listctrl.cpp-arc  $
//
//   Rev 1.15   Jun 24 2005 17:01:34   Fengyong
//PET1250 FN02 - EuroPean numeric enhancement
//
//   Rev 1.14   Nov 14 2004 15:02:20   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.13   May 01 2003 15:29:52   PURDYECH
//Columns were not being set to correct width if there was no registry entry.  No we correctly deal with this boundary case.  Also, we sanity check the column width before setting it ... must be no less than 0 and no more than 1000 pels.
 * 
 *    Rev 1.12   Jan 06 2003 16:46:58   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 17:42:50   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.10   Sep 19 2002 12:05:12   PURDYECH
 * BFFieldId has lost its operator long() method, so BFFieldId can no longer be compared to ints.  Code was changed to reflect this.
 * 
 *    Rev 1.9   Sep 10 2002 14:34:38   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.8   Sep 10 2002 11:01:20   PURDYECH
 * SORT_COLUMN was moved from header to implementation
 * 
 *    Rev 1.7   Aug 29 2002 12:57:36   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   May 28 2002 12:21:22   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.5   22 May 2002 19:17:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   Feb 25 2002 18:58:08   PURDYECH
 * Removed annoying compiler warnings.
 * 
 *    Rev 1.3   Jun 26 2001 19:01:58   PURDYECH
 * More Infrastructure Release 1.9 Integration stuff.
 * 
 *    Rev 1.2   Mar 07 2000 15:13:28   DT24433
 * changed to get substitutes directly from data dictionary
 * 
 *    Rev 1.1   Feb 17 2000 15:27:58   YINGZ
 * set default column width
 * 
 *    Rev 1.0   Feb 15 2000 11:01:40   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.26   Jan 20 2000 17:03:50   YINGZ
 * fix GetNextSelection problem
 * 
 *    Rev 1.25   Dec 29 1999 16:29:04   YINGZ
 * take off the first icon column
 * 
 *    Rev 1.24   Dec 06 1999 17:31:06   DT24433
 * removed basecontrol usage
 * 
 *    Rev 1.23   Dec 03 1999 10:41:36   YINGZ
 * get rid of E in icon column
 * 
 *    Rev 1.22   Nov 11 1999 11:33:56   YINGZ
 * for people to use
 * 
 *    Rev 1.21   Nov 06 1999 14:27:32   YINGZ
 * add UpdateItem function
 * 
 *    Rev 1.20   Nov 02 1999 17:28:32   YINGZ
 * add setitemstring
 * 
 *    Rev 1.19   Oct 28 1999 09:35:34   YINGZ
 * for a clean Get from PVCS!
 * 
 *    Rev 1.18   Oct 18 1999 16:19:58   YINGZ
 * support indicator
 * 
 *    Rev 1.17   Sep 29 1999 11:21:58   YINGZ
 * add GetCurrentItem
 * 
 *    Rev 1.16   Sep 28 1999 09:25:10   YINGZ
 * put column align info, SetItemString and GetItemString
 * 
 *    Rev 1.15   Sep 14 1999 11:04:38   YINGZ
 * add configureable feature
 * 
 *    Rev 1.14   Sep 03 1999 16:14:12   YINGZ
 * change parameter
 * 
 *    Rev 1.13   Sep 03 1999 14:36:36   YINGZ
 * add strip to PopulateList
 * 
 *    Rev 1.12   Sep 01 1999 11:37:12   YINGZ
 * add SetColumnAlignment
 * 
 *    Rev 1.11   Aug 26 1999 16:35:52   DT24433
 * changed getFieldFromCurrentListItem to getField
 * 
 *    Rev 1.10   Aug 23 1999 09:49:10   YINGZ
 * associate field with column key
 * 
 *    Rev 1.9   Aug 19 1999 10:02:10   YINGZ
 * configuration
 * 
 *    Rev 1.8   Aug 18 1999 16:57:52   YINGZ
 * ?
 * 
 *    Rev 1.7   Aug 16 1999 17:17:14   VASILEAD
 * You cannot unselect a row anymore
 * 
 *    Rev 1.6   Aug 04 1999 13:45:38   YINGZ
 * support default column width setting
 * 
 *    Rev 1.5   Jul 23 1999 15:03:12   VASILEAD
 * Removed OnKillFocus notification message
 * 
 *    Rev 1.4   Jul 20 1999 12:12:02   YINGZ
 * Auto save heading size
 * 
 *    Rev 1.3   Jul 20 1999 11:19:02   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 15 1999 16:54:20   PRAGERYA
 * Sorting enabled
 * 
 *    Rev 1.1   Jul 08 1999 10:05:22   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
