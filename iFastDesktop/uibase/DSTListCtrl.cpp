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
//    Copyright 2002 International Financial Data Services Ltd.
//
//******************************************************************************
//
// ^FILE   : listctrl.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 5/22/97
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : DSTListCtrl
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"

#include "dstlistctrl.h"
#include <bfproc\AbstractProcess.hpp>
#include "BaseDlg.h"
#include <ClientLocale.hpp>
#include "ConditionMessageDialog.h"
#include <ConfigManager.hpp>
#include <bfdata\bfdatafieldproperties.hpp>
#include <bfdata\bffieldid.hpp>
#include <bfutil\bfdate.hpp>
#include <bfproc\bfcontainerid.hpp>

#include <IdiString.hpp>
#include <MathString.hpp>
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
   const I_CHAR *CLASSNAME = I_( "DSTListCtrl " );

   const I_CHAR *ADDROW = I_( "AddRow" );
   const I_CHAR *COLUMNSORTOFF = I_( "ColumnSortOff" );
   const I_CHAR *DELETEROW = I_( "DeleteRow" );
   const I_CHAR *DELETECOLUMN = I_( "DeleteColumn" );
   const I_CHAR *DELETEALLCOLUMNS = I_( "DeleteAllColumns" );
   const I_CHAR *GETNEXTSELECTION = I_( "GetNextSelection" );
   const I_CHAR *INSERTCOLUMN1 = I_( "InsertColumn1" );
   const I_CHAR *INSERTCOLUMN2 = I_( "InsertColumn2" );
   const I_CHAR *SETSELECTION = I_( "SetSelection" );
   const I_CHAR *SETSORTCOLUMN = I_( "SetSortColumn" );
   const I_CHAR *SAVESETTINGS = I_( "SaveSettings" );
}

const DString DSTListCtrl::s_strEmpty_;

namespace CND
{
   // Conditions used
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

//******************************************************************************
//              Public Methods
//******************************************************************************
DSTListCtrl::DSTListCtrl( BaseDlg *rpParent,
                          const I_CHAR *dialogName,
                          UINT controlID,
                          UINT parentControlID,
                          UINT flags,
                          bool bShowSelAlways ) 
: CListCtrl()
, m_bDataConnected( true )
, m_bEnabled( true )
, m_bVisible( true )
, m_bDeleting( false )
, m_bSetSizeOnce( false )
, m_bShowSelAlways( bShowSelAlways )
, m_columnCount( 0 )
, m_controlID( controlID )
, m_flags( flags )
, m_icons( NULL )
, m_idSubstitute( ifds::NullFieldId )
, m_idLeftSubstitute( ifds::NullFieldId )
, idContainer_( BF::NullContainerId )
, m_parentControlID( parentControlID )
, m_rpParentDialog( rpParent )
, m_strDialogName( dialogName )
, m_idSubstituteCode( ifds::NullFieldId )
, m_idSubstituteDescription( ifds::NullFieldId )
, m_sevMax(NO_SEVERITY)
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );
   // Initialize sort column array
   memset( &m_SortArray, 0, sizeof( m_SortArray ) );

   m_icons = new CImageList();
   ASSERT( m_icons != NULL );    // serious allocation failure checking
   m_icons->Create( 16, 16, ILC_COLOR | ILC_MASK, 4, 4 );

   //removed for new arch
   //m_icons->Add(AfxGetApp()->LoadIcon( IDI_NO_ERR_ICON ));

   m_icons->Add(LoadIcon( NULL, IDI_ASTERISK ));
   m_icons->Add(LoadIcon( NULL, IDI_ASTERISK ));
   m_icons->Add(LoadIcon( NULL, IDI_EXCLAMATION ));
   m_icons->Add(LoadIcon( NULL, IDI_HAND ));

   m_idSubstituteCode = BFFieldId::getId( I_( "Substitute_Code" ) );
   m_idSubstituteDescription = BFFieldId::getId( I_( "Substitute_Description" ) );
   
   if( 0 != controlID )
   {
      SubclassDlgItem( controlID, reinterpret_cast <CWnd *>( rpParent ) );
   }
}

//******************************************************************************
DSTListCtrl::~DSTListCtrl ()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete m_icons;
}

//******************************************************************************
SEVERITY DSTListCtrl::AddRow()
{
   MAKEFRAMEAUTOPROMOTE2( CND::GUI_CONDITION, CLASSNAME, ADDROW );

   const DString *pNewItemKey = &( m_rpParentDialog->getParent()->
                                   getKeyForNewListItem( m_rpParentDialog, idContainer_ ) );
   assert( pNewItemKey );

   if( pNewItemKey )
   {  // Add successful
      SetSelection( NewItem( (DWORD)pNewItemKey ) );
   }

   return(GETHIGHESTSEVERITY());
}

//******************************************************************************
void DSTListCtrl::ColumnSortOff( int nCol )
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
void DSTListCtrl::DeleteAllColumns()
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
bool DSTListCtrl::DeleteColumn( int nCol )
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
SEVERITY DSTListCtrl::DeleteRow()
{
   MAKEFRAMEAUTOPROMOTE2( CND::GUI_CONDITION, CLASSNAME, DELETEROW );
   int index = GetNextSelection();

   if( index != -1 )
   {
      const DString *strKey = getKey( index );
      // Need to set because this may be first update which would create a new
      //  iterator
      m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog,
                                                         idContainer_, *strKey );
      if( m_rpParentDialog->getParent()->deleteItemFromList( m_rpParentDialog,
                                                             idContainer_ ) <= WARNING )
      {  // Remove from list
         SetDeleting( true );
         DeleteItem( index );

         if( !GetItemCount() )
         {
            if( IsAutoAdd() )
            {  // If no more, must create new object
               AddRow();
            }
            else
            {  // Disable associated controls here
               m_rpParentDialog->ConnectControlsToData( GetControlID(), false );
            }
         }
         else
         {
            if( index >= GetItemCount() )
            {  // Deleted last item in list, so back up one
               index--;
            }
            if( index < GetItemCount() )
            {  // Select another item
               SetSelection( index );
            }
         }
         SetDeleting( false );
      }
   }

   return(GETHIGHESTSEVERITY());
}

//******************************************************************************
void DSTListCtrl::DrawItem( LPDRAWITEMSTRUCT pdi )
{
   LV_ITEM lvi;

   lvi.mask       = LVIF_IMAGE | LVIF_STATE;
   lvi.iItem      = pdi->itemID;
   lvi.iSubItem   = 0;
   lvi.stateMask  = 0xFFFF;

   if( GetItem( &lvi) )
   {
      CRect rcAllLabels = pdi->rcItem;
      CRect rcLabel;
      GetItemRect( pdi->itemID, rcLabel, LVIR_LABEL );
      rcAllLabels.left = rcLabel.left;

      bool bFocus     = ( GetFocus() == this );
      bool bEnabled   = IsWindowEnabled( ) == TRUE;  // Just to remove warning
      bool bSelected  = ( lvi.state & LVIS_SELECTED  ) == LVIS_SELECTED;
      bool bFocusItem = ( lvi.state & LVIS_FOCUSED  ) == LVIS_FOCUSED;

      COLORREF foreColor = 0;
      COLORREF backColor = 0;
      COLORREF backgroundColor = 0;
      GetDrawColors( pdi->itemID, bEnabled, bFocus, bSelected || bFocusItem,
                     foreColor, backColor, backgroundColor );
      CDC *pDC = CDC::FromHandle( pdi->hDC );

      COLORREF oldTextColor = pDC->SetTextColor( foreColor );
      COLORREF oldBkColor = pDC->SetBkColor( backColor );
      pDC->FillRect( rcAllLabels, &CBrush( backgroundColor ) );

      CImageList *piml = GetImageList( LVSIL_SMALL );
      if( piml && ( lvi.iImage > 0 ) )
      {  // Get and draw image if one exists
         CRect rcIcon;
         GetItemRect( pdi->itemID, rcIcon, LVIR_ICON );
         ImageList_DrawEx( piml->m_hImageList, lvi.iImage,
                           pDC->m_hDC,rcIcon.left,rcIcon.top, 16, 16,
                           CLR_NONE, CLR_NONE, ILD_TRANSPARENT );
      }

      int pos     = 0;                        // Pixel position of column
      int cxImage = 0;                        // Right boundary of image

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
const DString &DSTListCtrl::GetCurrentKey() const
{
   int idx = GetNextSelection();

   if( idx == -1 )
   {
      return(s_strEmpty_);
   }
   return(*( getKey( idx ) ) );
}

//******************************************************************************
void DSTListCtrl::GetDrawColors( int       row,    // index of the listview item to draw
                                 bool      enabled,
                                 bool      focused,
                                 bool      selected,
                                 COLORREF &foreColor,
                                 COLORREF &backColor,
                                 COLORREF &backgroundColor ) const
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
// get item number using its key, return -1 when no row is found
int DSTListCtrl::GetItemNo( const DString *pKey ) const
{
   const DString *key;
   for( int i = 0; i < GetItemCount(); i++ )
   {
      key = getKey( i );
      if( *key == *pKey )
         return(i);
   }

   return(-1);
}

//******************************************************************************
// get the str from the cell
// ColumnKey is the code in the sub list
CString DSTListCtrl::GetItemString(int nItem, const I_CHAR * ColumnKey) const
{
   if( m_idSubstitute != ifds::NullFieldId ) // sub list is used
   {
      COLUMNMAP_CONST_ITER Iter = m_columnMap.find(ColumnKey);

      if( Iter != m_columnMap.end() )
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
BOOL DSTListCtrl::doSetItemText( int nItem, int nSubItem, LPCTSTR lpszText, BFFieldId fieldId )
{
	DString str = lpszText;
	BaseDlg::DisplayFormat( str, fieldId );	
		
	return ( SetItemText(nItem, nSubItem, str.strip().c_str() ));
}
//******************************************************************************
// Get next selected item
// Returns index of first selected
int DSTListCtrl::GetNextSelection( int idx )  const // Index to start after (-1 = all)

{
   TRACE_METHOD( CLASSNAME, GETNEXTSELECTION );

   int rtn = GetNextItem( idx, LVNI_SELECTED );

   // if not selected, try focused item
   return( rtn == -1 )? GetNextItem( idx, LVIS_FOCUSED ) :rtn;
}

//******************************************************************************
void DSTListCtrl::Init( BaseDlg *rpBD,
                        const BFFieldId &idSubstitute,
                        const BFContainerId& idContainer,
                        const I_CHAR *listName )
{
   m_rpParentDialog = rpBD;
   m_idSubstitute = idSubstitute;
   idContainer_ = idContainer;
   m_strListName = listName;

   SetColumnHeadings( m_idSubstitute, LVCFMT_LEFT , 100 );
   LoadSettings();

   if( m_idSubstitute != ifds::NullFieldId && !(m_flags & LISTFLAG_NOT_UPDATABLE) ) // sub list is used and listctrl is updatable
   {
      SetImageList( m_icons, LVSIL_SMALL );
   }
}

//******************************************************************************
void DSTListCtrl::Init( BaseDlg *rpBD,
                        const BFFieldId &idSubstitute,
                        const BFFieldId &idLeftSubstitute,
                        const BFContainerId& idContainer,
                        const I_CHAR *listName )
{
   m_idLeftSubstitute = idLeftSubstitute;

   m_rpParentDialog = rpBD;
   m_idSubstitute  = idSubstitute;
   idContainer_ = idContainer;
   m_strListName    = listName;

   SetColumnHeadings( m_idSubstitute, LVCFMT_LEFT , 100 );

   LoadSettings();
}

//******************************************************************************
int DSTListCtrl::InsertColumn( int nCol,
                               const LV_COLUMN *pColumn )
{
   // Replaced to track column count
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
int DSTListCtrl::InsertColumn( int nCol,
                               LPCTSTR lpszColumnHeading,
                               int nFormat,
                               int nWidth,
                               int nSubItem )
{  // Replaced to track column count
   TRACE_METHOD( CLASSNAME, INSERTCOLUMN2 );

   // Currently, we are calling SetItemSize because the
   // original WM_MEASUREITEM happens before we get subclassed.
   SetItemSize();
   int rtn = CListCtrl::InsertColumn( nCol, lpszColumnHeading, nFormat, nWidth, nSubItem );

   if( rtn != -1 )
   {  // Successful insert so add to counter
      ++m_columnCount;
   }
   return(rtn);
}

//******************************************************************************
void DSTListCtrl::PopulateList( const DString *rpStrKey )
{
   if( !IsDataConnected() || !idContainer_.isValid() )
   {
      return;
   }

   DeleteAllItems();

   if( m_idLeftSubstitute == ifds::NullFieldId )
      PopulateListType( rpStrKey );
   else
      PopulateAttributeType( );
}

//******************************************************************************
void DSTListCtrl::RefreshAllItems()
{
   const DString* strKey;
   m_sevMax = NO_SEVERITY;
   for( int i = 0; i < GetItemCount(); i++ )
   {
      strKey = getKey( i );
      m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog,
                                                         idContainer_, *strKey );
      UpdateItem( i );
   }

   // Reset current item
   int idx = GetNextSelection();

   if( idx != -1 )
   {
      strKey = getKey( idx );

      m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog,
                                                         idContainer_, *strKey );
   }
}

//******************************************************************************
void DSTListCtrl::RefreshCurrentItem(bool bReregisterObservers)
{
   int idx = GetNextSelection();

   if( idx != -1 )
   {
      const DString* strKey = getKey( idx );

      m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog,
                                                         idContainer_, *strKey );
      UpdateItem( idx );

      if( bReregisterObservers )
         m_rpParentDialog->ReregisterObservers( m_controlID );

      // Load associated controls
      m_rpParentDialog->LoadControls( m_controlID );
   }
}

//******************************************************************************
void DSTListCtrl::ResetCurrentItem()
{
   DString strKey = GetCurrentKey();

   if( strKey != NULL_STRING )
   {
      m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog,
                                                         idContainer_, strKey );
      m_rpParentDialog->getParent()->resetCurrentItem( idContainer_ );

      // reset erased fieldinfo so we need to re-register observers
      RefreshCurrentItem(true);

      m_rpParentDialog->LoadChildListControls( m_controlID );
   }
}

//******************************************************************************
// set the str to the cell
// ColumnKey is the code in the sub list
BOOL DSTListCtrl::SetItemString( int nItem,
                                 const I_CHAR *ColumnKey,
                                 DString &Str )
{
   if( m_idSubstitute != ifds::NullFieldId ) // sub list is used
   {
      COLUMNMAP_ITER Iter = m_columnMap.find( ColumnKey );

      if( Iter != m_columnMap.end() )
      {
		 BFFieldId fieldId = BFFieldId::getId( (*Iter).first );		 
         return(doSetItemText( nItem, (*Iter).second,Str.c_str(), fieldId ));
      }
   }

   return(FALSE);
}

//******************************************************************************
// selection should be in sync with view list!
// Set selection state of row
void DSTListCtrl::SetSelection( int idx,              // Row to set
                                bool bSelect,         // true = select, false = unselect
                                bool bVisible )       // true = ensure visible
// If select, row will get focus
{
   TRACE_METHOD( CLASSNAME, SETSELECTION );

   int total = GetItemCount();

   if( !total )return;

   const DString* key;
   if( idx == -1 || idx >= total )
   {
      idx = 0;
      key = &(m_rpParentDialog->getParent()->getFirstListItemKey( m_rpParentDialog,
                                                                  idContainer_ ));
   }
   else
   {
      key = getKey( idx );
   }

   m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog,
                                                      idContainer_, *key );

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
// Set selection state of row
void DSTListCtrl::SetSelection( const DString *strKey,    // Row to set
                                bool bSelect,             // true = select, false = unselect
                                bool bVisible )           // true = ensure visible
// If select, row will get focus
{
   TRACE_METHOD( CLASSNAME, SETSELECTION );

   SetSelection( GetItemNo( strKey ), bSelect, bVisible );
}

//******************************************************************************
int DSTListCtrl::SetSortColumn( int nCol,
                                const GenericInterface *pCaller,
                                const BFContainerId& idList,
                                const BFFieldId &idField,
                                int iSortOrder,
                                WORD wFlags )
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
   SortCol->idContainer_ = idList;
   SortCol->m_idField = idField;
   SortCol->m_iSortOrder = iSortOrder;
   SortCol->m_wFlags = wFlags;
   return(nRet);
}

//******************************************************************************
bool DSTListCtrl::SortOnColumn( int column )
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
//              Methods similar to BaseControl
//******************************************************************************
void DSTListCtrl::ConnectToData( bool bFlag,
                                 bool bShowHideBasedOnConnection )
{
   SetDataConnected( bFlag );
   if( bShowHideBasedOnConnection )
   {  // Show/Hide based on connection
      Show( bFlag );
   }
}

//******************************************************************************
void DSTListCtrl::Enable( bool bFlag )
{
   m_bEnabled = bFlag;
   EnableWindow( bFlag );
}

//******************************************************************************
void DSTListCtrl::Show( bool bFlag )
{
   int nCmdShow = SW_SHOW;

   m_bVisible = bFlag;
   if( !bFlag )
   {
      nCmdShow = SW_HIDE;
   }
   ShowWindow( nCmdShow );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
BEGIN_MESSAGE_MAP(DSTListCtrl , CListCtrl)
//{{AFX_MSG_MAP(DSTListCtrl )
ON_WM_KILLFOCUS()
ON_WM_SETFOCUS()
ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, Itemchanged)
ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnDblclkItem)
ON_WM_DESTROY()
ON_WM_MEASUREITEM_REFLECT()
ON_WM_CREATE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
//              Message Handlers
//******************************************************************************
void DSTListCtrl::Itemchanged( NMHDR *pNMHDR, LRESULT *pResult )
{
   // only available to list type
   if( m_idLeftSubstitute != ifds::NullFieldId ) return;

   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

   if( pNMListView->iItem == -1 )
   {
      return;
   }

   const DString* strKey = getKey( pNMListView->iItem );
// TODO - we may be able to be smarter about identifying which situations require
//  row update.....  Unselected only need if something updated,
   if( LVN_UNSELECTED )
   {
      if( !Deleting() )
      {  // Don't update if deleting
         // This should already be current item ??
         CWaitCursor wait;

         m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog,
                                                            idContainer_, *strKey );
         // Make sure all controls are stored
         m_rpParentDialog->ProcessControls();
         // Fire all cross-edits for list item
         m_rpParentDialog->getParentProcess()->fireCrossEdit( m_rpParentDialog, idContainer_, ifds::NullFieldId );
         UpdateItem( pNMListView->iItem );
      }
   }
   else if( LVN_SELECTED )
   {
      UpdateWindow();
      newSelection(pNMListView->iItem);//a new selection occured; we might want to handle it right away or later
   }

   *pResult = 0;
}

//******************************************************************************
void DSTListCtrl::MeasureItem( LPMEASUREITEMSTRUCT lpmis )
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
//
//  ^PROTECTED METHOD : DSTListCtrl ::OnColumnclick
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
void DSTListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
{
   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
   BOOL fRet;

   // Selected column
   int  SelectedCol = pNMListView->iSubItem;
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
int DSTListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if( CListCtrl::OnCreate(lpCreateStruct) == -1 )
   {
      return(-1);
   }
   return(0);
}

//******************************************************************************
void DSTListCtrl::OnDestroy()
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
void DSTListCtrl::OnKillFocus(CWnd* pNewWnd)
{
   CListCtrl::OnKillFocus(pNewWnd);

   // Check if we are losing focus to label edit box
   if( pNewWnd != NULL && pNewWnd->GetParent() == this )
   {
      return;
   }
   RepaintSelectedItems();

   if( m_strDialogName != NULL_STRING && m_strListName != NULL_STRING )
   {
      SaveSettings();
   }
}

//******************************************************************************
void DSTListCtrl::OnSetFocus(CWnd* pOldWnd)
{
   CListCtrl::OnSetFocus(pOldWnd);

   // Check if we are getting focus to label edit box
   if( pOldWnd != NULL && pOldWnd->GetParent() == this )
   {
      return;
   }
   RepaintSelectedItems();
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
//  ^PRIVATE METHOD : DSTListCtrl ::DrawItemColumn
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
void DSTListCtrl::DrawItemColumn( CDC *pDC,
                                  LPTSTR lpsz,
                                  LPRECT prcClip,
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

void DSTListCtrl::newSelection(int iItem)
{
   CWaitCursor wait;
   HandleSelection(iItem);
}

//******************************************************************************
void DSTListCtrl::HandleSelection( int iItem )
{
   bool bNew = false;
   bool bIsDummy = false;
   const DString *strKey = getKey( iItem );

   m_rpParentDialog->getParent()->setCurrentListItem( m_rpParentDialog,
                                                      idContainer_,
                                                      *strKey );

   bNew = m_rpParentDialog->getParentProcess()->isCurrentListItemNew( m_rpParentDialog, idContainer_ );
   bIsDummy = m_rpParentDialog->getParentProcess()->isCurrentListItemDummy( m_rpParentDialog, idContainer_ );

   //   derived dialog handling (DoListItemChanged)
   m_rpParentDialog->DoPreListItemChanged( m_controlID, *strKey, bNew, bIsDummy );

   // Note - have to connect for selection change for different properties
   m_rpParentDialog->ConnectControlsToData( GetControlID(), true );

   // Load associated controls
   m_rpParentDialog->LoadControls( m_controlID );

   // Let BaseDlg take care of any nested list propogation and allow for
   //   derived dialog handling (DoListItemChanged)
   m_rpParentDialog->ListItemChanged( m_controlID, *strKey, bNew , bIsDummy);
}

//******************************************************************************
bool DSTListCtrl::LoadSettings()
{
   int count;
   bool useDefault=false;
   DString strHold;
   DString title( LV );
   title += m_strListName;

   ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
   Configuration workstation = pWorkstation->retrieveConfig( m_strDialogName );

   // Get column count
   strHold = title;
   strHold += I_( ".colcount" );
   strHold = workstation.getValueAsString( strHold );
   if( strHold.empty() )
   {
      // try to get the default column setting
      pWorkstation = ConfigManager::getManager( DEFAULTWORKSTATION );
      workstation = pWorkstation->retrieveConfig( m_strDialogName );
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
         useDefault=true;
      }
   }

   LVCOLUMN col;
   col.mask = LVCF_WIDTH | LVCF_FMT;
   DString fmt;

   COLUMNMAP_ITER Iter ;
   COLUMNMAP_ITER IterEnd = m_columnMap.end();

   Iter =    m_columnMap.begin();
   while( Iter != IterEnd )
   {
      if( (*Iter).first != NULL_STRING )
      {
         strHold = title;
         strHold += I_( "." );
         strHold += (*Iter).first;

         col.cx = 100;
         col.fmt = 0;

         if( false == useDefault )
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

   return(true);
}

//******************************************************************************
int DSTListCtrl::NewItem( DWORD ItemData )
{
   m_currentItem = InsertItem( 99999, _T("") );

   if( m_currentItem != -1 )
   {
      SetItemData( m_currentItem, ItemData );
   }

   return(m_currentItem);
}

//******************************************************************************
void DSTListCtrl::RepaintSelectedItems()
{
   CRect rcItem, rcLabel;
   CRect rcIcon;
   // Invalidate focused item so it can repaint properly
   int idx = GetNextItem( -1, LVNI_FOCUSED );

   if( idx != -1 )
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
bool DSTListCtrl::SaveSettings()
{
   MAKEFRAME2( CND::GUI_CONDITION, CLASSNAME, SAVESETTINGS );

   bool result = false;

   try
   {
      int count = GetColumnCount();

      if( count > 0 )
      {
         ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
         Configuration workstation = pWorkstation->retrieveConfig( m_strDialogName );

         LV_COLUMN col;
         col.mask = LVCF_WIDTH | LVCF_FMT;

         DString title( LV );
         title += m_strListName;

         DString strHold( title );
         strHold += I_( ".colcount=" );
         strHold += asString( count );
         workstation.set( strHold );

         if( m_idSubstitute != ifds::NullFieldId ) // sub list is used
         {
            COLUMNMAP_ITER Iter ;
            COLUMNMAP_ITER IterEnd = m_columnMap.end();

            Iter =    m_columnMap.begin();
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

                     strHold += asString( col.fmt & LVCFMT_JUSTIFYMASK );    // get format


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

                  strHold += asString( col.fmt & LVCFMT_JUSTIFYMASK );    // get format

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
void DSTListCtrl::SetColumnHeadings( const BFFieldId &idSubstitute, int nFormat , int nWidth )
{
   DString strIdi;
   DString strTag;
   DString strValue;
   int col = 1;

   DeleteAllItems();
   DeleteAllColumns();
   m_columnMap.clear();

   const BFDataFieldProperties* pProps = m_rpParentDialog->getFieldAttributes( m_rpParentDialog, idSubstitute );

   if( NULL != pProps->getSubstitutionSet( ClientLocaleContext::get() ) )
   {
      pProps->getAllSubstituteValues( strIdi, ClientLocaleContext::get(), true );
   }
   else
   {  // problem ??
      assert( 0 );
      return;
   }

   // add room for icon column
   if( m_idLeftSubstitute == ifds::NullFieldId )
   {
      m_columnMap.insert( COLUMNMAP::value_type ( I_(""), 0 ) );
      InsertColumn( 0, I_(" "), LVCFMT_IMAGE, 20 );
   }

   I_CHAR *rpStr = const_cast< I_CHAR * >( strIdi.c_str() );

   while( *rpStr != '\0' )
   {
      rpStr = parseIdiString( rpStr, strTag, strValue );
      if( strTag != NULL_STRING && m_rpParentDialog->filterListColumn(idSubstitute,strTag) )
      {
         m_columnMap.insert( COLUMNMAP::value_type( strTag, col ) );

         InsertColumn( col++, strValue.strip().c_str(), nFormat, nWidth );
      }
   }
}

//******************************************************************************
void DSTListCtrl::SetItemSize()
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
void DSTListCtrl::UpdateItem( int idx )
{  // Assumes the current item has also been set current for the container
   if( idx == -1 )
   {
      assert( 0 );
      return;
   }

   DString str;
   COLUMNMAP_ITER Iter ;
   COLUMNMAP_ITER IterEnd = m_columnMap.end();

   Iter = m_columnMap.begin();
   while( Iter != IterEnd )
   {
      if( (*Iter).first != NULL_STRING )
      {
         // get str from
         if( m_rpParentDialog->GetOverrideItemString( m_idSubstitute.getId(),
                                                      (*Iter).first, str ) != true )
         {
            m_rpParentDialog->getParent()->getField( m_rpParentDialog, idContainer_, BFFieldId::getId( (*Iter).first ), str );
            str.strip();
         }

		 BFFieldId fieldId = BFFieldId::getId( (*Iter).first );		 
         doSetItemText( idx, (*Iter).second, str.c_str(), fieldId );
      }
      ++Iter;
   }

   // Also update image
   CONDITIONVECTOR conditions;
   int conditionIcon = 0;

   SEVERITY sevRtn = m_rpParentDialog->getParent()->getErrors( m_rpParentDialog,idContainer_, 
                                                               ifds::NullFieldId, conditions );
   if( sevRtn >  m_sevMax )
      m_sevMax = sevRtn;

   if( sevRtn > WARNING )
   {
      conditionIcon = 3;
   }
   else if( sevRtn == WARNING )
   {
      conditionIcon = 2;
   }
   else if( sevRtn == INFORMATIONAL )
   {
      conditionIcon = 1;
   }

   // Set correct icon image
   SetItem( idx, 0, LVIF_IMAGE, NULL, conditionIcon, 0, 0, NULL );
}

//******************************************************************************
//              Methods similar to BaseControl
//******************************************************************************
void DSTListCtrl::SetDataConnected( bool bFlag )
{
   m_bDataConnected = bFlag;
   if( !bFlag )
   {  // Don't allow disconnected controls to be enabled ( but don't affect
      // Programmer set Enabled flag
      EnableWindow( false );
      DeleteAllItems();
   }
   else
   {
      EnableWindow( IsEnabled() );
   }
}

//******************************************************************************
bool DSTListCtrl::doSetCtrlReadOnly(bool bReadOnly)
{
   //with the current design DSTListCtrl is always readonly
   return(true);
}

//******************************************************************************
void DSTListCtrl::PopulateListType( const DString *rpStrKey )
{
   DString str;
   int nItem;
   m_sevMax = NO_SEVERITY;

   const DString *key = &m_rpParentDialog->getParent()->getFirstListItemKey( m_rpParentDialog, idContainer_ );

   if( (*key) == NULL_STRING )
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
         if( m_rpParentDialog->ListViewControlFilter( m_idSubstitute.getId(), key ) )
         {
            nItem = NewItem( (DWORD)key );
            UpdateItem( nItem );
         }
      } while( *(key = &(m_rpParentDialog->getParent()->getNextListItemKey( m_rpParentDialog, idContainer_ ) ) ) != NULL_STRING );
   }

   if( GetItemCount() > 0 )
   {  // Force selection
      int idx = 0;

      if( rpStrKey != NULL )
      {  // Try to get key
         idx = GetItemNo( rpStrKey );
         if( idx == -1 )
         {
            idx = 0;
         }
      }
      SetSelection( idx );

      // method perform sorting only if there are defined sortColumns in m_SortArray[]
      SortListCtrl();
   }
   else
   {  // Disable associated controls here
      m_rpParentDialog->ConnectControlsToData( GetControlID(), false );
      // Make sure any sub-lists get cleared as well
      m_rpParentDialog->LoadChildListControls( GetControlID() );
   }
}

//******************************************************************************
void DSTListCtrl::PopulateAttributeType( )
{
   assert( m_idLeftSubstitute != ifds::NullFieldId );

   DString str;
   int iIndex;

   const DString *pKey = &( m_rpParentDialog->getParent()->getFirstListItemKey( m_rpParentDialog,
                                                                                BFContainerId( m_idLeftSubstitute.getId() ) ) );
   while( *pKey != NULL_STRING )
   {
      if( m_rpParentDialog->ListViewControlFilter( m_idSubstitute.getId(), pKey ) )
      {
         iIndex = NewItem( (DWORD)pKey );


         m_rpParentDialog->getParent()->getField( m_rpParentDialog, BFContainerId( m_idLeftSubstitute.getId() ),
                                                  m_idSubstituteDescription, str );


         SetItemText( iIndex, 0, str.c_str() );

         if( m_rpParentDialog->GetOverrideItemString( m_idLeftSubstitute.getId(),
                                                      *pKey, str ) != true )
         {
            m_rpParentDialog->getParent()->getField( m_rpParentDialog, idContainer_, BFFieldId::getId( *pKey ), str );
            str.strip();
         }
		 BFFieldId fieldId = BFFieldId::getId( *pKey );		 
         doSetItemText( iIndex, 1, str.c_str(), fieldId );
      }

      pKey = &( m_rpParentDialog->getParent()->getNextListItemKey( m_rpParentDialog, BFContainerId( m_idLeftSubstitute.getId() ) ) );
   }
}

//******************************************************************************
BOOL DSTListCtrl::OnDblclkItem(NMHDR* pNMHDR, LRESULT* pResult)
{
   // only available to attribute list
   if( m_idLeftSubstitute != ifds::NullFieldId )
   {
      NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

      if( pNMListView->iItem != -1 )
      {
         const DString *pKey = getKey( pNMListView->iItem );
         m_rpParentDialog->doDblclkListItem( m_idSubstitute.getId(), pKey );
      }
   }
   return(FALSE);
}

//******************************************************************************
//              Static Functions
//******************************************************************************
//    List Sorting implementor
//    This is the comparison function that must be supplied to the List Box
//    Sort method as a Callback.
//******************************************************************************
int CALLBACK DSTListCtrl::ListSorter( LPARAM lParam1,
                                      LPARAM lParam2,
                                      LPARAM lParamSort )
{
   // Both Item data parameters and the sorter object must be set
   if( !lParam1 || !lParam2 || !lParamSort )
   {
      return(0);
   }

   // Access passed parameter (pointer to Sort column description)
   SortColumn* pSortColumn = reinterpret_cast< SortColumn* >( lParamSort );
   DString strValue1( NULL_STRING ), 
   strValue2( NULL_STRING );

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

   if( pSortColumn->m_wFlags & EUROPEAN_DATE_FORMAT )
   {
      BFDate date1( strValue1, BFDate::DF_FSEURO );
      BFDate date2( strValue2, BFDate::DF_FSEURO );
      if( date1 < date2 ) iRet = -1;
      else if( date1 == date2 ) iRet = 0;
      else iRet = 1;
      return( iRet * ( pSortColumn->m_iSortOrder ) );
   }

   // Different method used determined by type of element being sorted
   const BFDataFieldProperties* pProps;
   pProps = pSortColumn->m_pCaller->getFieldAttributes( pSortColumn->m_pCaller, pSortColumn->m_idField );

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
      iRet = 0;
   }

   return( iRet * ( pSortColumn->m_iSortOrder ) );
}

//******************************************************************************
int CALLBACK DSTListCtrl::ListSorterByManyColumns( LPARAM lParam1,
                                                   LPARAM lParam2,
                                                   LPARAM lParamSort )
{
   // Both Item data parameters and the sorter object must be set
   if( !lParam1 || !lParam2 || !lParamSort )
   {
      return(0);
   }

   // Access passed parameter (pointer to Sort column description)
   SortColumn** pSortColumnsArray = reinterpret_cast< SortColumn** >( lParamSort );

   // get iSortColumnsCount - should be better declared as a class member
   int iSortColumnsCount = 0; 
   for( int i = 0; i < MAX_COLUMNS; i++ )
   {
      if( pSortColumnsArray[i] != NULL )
      {
         iSortColumnsCount++;
      }
   }

   // get the commom things in the array
   const GenericInterface* pCaller = pSortColumnsArray[0]->m_pCaller;
   const BFContainerId& idContainer = pSortColumnsArray[0]->idContainer_;

   // verify these commom things are the same for all other positions in array
   for( int i = 1; i < iSortColumnsCount; i++ )
   {
      if( pSortColumnsArray[i]->m_pCaller != pCaller ||
          pSortColumnsArray[i]->idContainer_ != idContainer )
      {
         // In the dialog, in the all SetSortColumn() methods, "pCaller" and "idContainer" parameters 
         // should be the same 
         assert(0);
      }
   }

   //verify if all fields values are STRING
   for( int i = 0; i < iSortColumnsCount; i++ )
   {
      const BFDataFieldProperties* pProps; 
      pProps = pCaller->getFieldAttributes( pCaller, pSortColumnsArray[i]->m_idField );

      if( !pProps->isText() )
      {
         // only fields values as STRING values could be comparated with this method
         assert( 0 );
         return(0);
      }
   }

   //get fields values for the sorter columns on the first ListCtrl row
   DString dstrRow1FieldValue[MAX_COLUMNS];

   const DString *pKey1 = reinterpret_cast< DString * >( lParam1 );
   pCaller->getParent()->setCurrentListItem( pCaller, idContainer, *pKey1 );
   for( int i = 0; i < iSortColumnsCount; i++ )
   {
      pCaller->getParent()->getField( pCaller, 
                                      idContainer, 
                                      pSortColumnsArray[i]->m_idField, 
                                      dstrRow1FieldValue[i] );
      dstrRow1FieldValue[i].strip();
   }

   //get fields values for the sorter columns on the second ListCtrl row
   DString dstrRow2FieldValue[MAX_COLUMNS];

   const DString *pKey2 = reinterpret_cast< DString * >( lParam2 );
   pCaller->getParent()->setCurrentListItem( pCaller, idContainer, *pKey2 );
   for( int i = 0; i < iSortColumnsCount; i++ )
   {
      pCaller->getParent()->getField( pCaller, 
                                      idContainer, 
                                      pSortColumnsArray[i]->m_idField, 
                                      dstrRow2FieldValue[i] );
      dstrRow2FieldValue[i].strip();
   }

   // The comparison function must return:
   //  - a negative value if the first item should precede the second, 
   //  - a positive value if the first item should follow the second, 
   //  - or zero if the two items are equivalent.
   // SORT_ASCENDING = 1;
   // SORT_DESCENDING = -1;

   int iReturn = 0;
   for( int i = 0; i < iSortColumnsCount; i++ )
   {
      iReturn = pSortColumnsArray[i]->m_iSortOrder;

      if( pSortColumnsArray[i]->m_wFlags & EUROPEAN_DATE_FORMAT )
      {
         BFDate date1( dstrRow1FieldValue[i], BFDate::DF_FSEURO );
         BFDate date2( dstrRow2FieldValue[i], BFDate::DF_FSEURO );
         if( date1 < date2 )
         {
            iReturn *= -1;
            break;
         }
         else if( date1 > date2 )
         {
            break;
         }
         // if they are equal then goes to compare the next field values
      }
      else
      {
         if( dstrRow1FieldValue[i] < dstrRow2FieldValue[i] )
         {
            iReturn *= -1;
            break;
         }
         else if( dstrRow1FieldValue[i] > dstrRow2FieldValue[i] )
         {
            break;
         }
         // if they are equal then goes to compare the next field values
      }
   }

   return(iReturn);
}

//******************************************************************************
void DSTListCtrl::SortListCtrl( )
{
   // test if there are sorter columns
   int iSortColumnsCount = 0; // should be better declared as a class member

   SortColumn* pTheOnlyOneSortColumn = NULL;
   for( int i = 0; i < MAX_COLUMNS; i++ )
   {
      SortColumn* pSortColumn = m_SortArray[i];

      if( pSortColumn != NULL )
      {
         iSortColumnsCount++;
         pTheOnlyOneSortColumn = pSortColumn;
      }
   }

   if( iSortColumnsCount == 1 )
   {  // single column sorting

      // Call control sort manager with address of Callback compare function
      SortItems( (PFNLVCOMPARE)ListSorter, (DWORD)pTheOnlyOneSortColumn );
   }
   else if( iSortColumnsCount > 1 )
   {  // many columns sorting

      // verify if m_SortArray was set correct
      for( int i = 0; i < iSortColumnsCount; i++ )
      {
         SortColumn* pSortColumn = m_SortArray[i];
         if( pSortColumn == NULL )
         {  // in the case of many columns sorting, on the position "0" in the m_SortArray
            // should be the column base on which will be the primary sorting criteria of the 
            // ListCtrl, on the position "1" should be the column base on which will be the 
            // secondary sorting criteria , ...
            // These settings should be done in dialog, before LoadListControl(), like this:
            //  SetSortColumn( 0, ...); - for primary sorting criteria 
            //  SetSortColumn( 1, ...); - for secondary sorting criteria 
            //  SetSortColumn( 2, ...);
            assert(0);
         }
      }

      SortItems( (PFNLVCOMPARE)ListSorterByManyColumns, (DWORD)m_SortArray );
   }
}

//******************************************************************************
SEVERITY DSTListCtrl::GetMaxErrorState()
{
	DString strKey = GetCurrentKey();
	PopulateList( &strKey );
	return(m_sevMax);
}

//******************************************************************************
const DString* DSTListCtrl::getKey( int iItem ) const
{
   return( reinterpret_cast< const DString* >( GetItemData( iItem ) ) );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTListCtrl.cpp-arc  $
//
//   Rev 1.43   08 Jan 2009 14:31:22   kovacsro
//IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop
//
//   Rev 1.42   Jun 24 2005 17:02:18   Fengyong
//PET1250 FN02 - EuroPean numeric enhancement
//
//   Rev 1.41   Nov 14 2004 15:02:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.40   May 11 2004 14:28:12   FENGYONG
//PET1046 FN1 - transfer-switch -Rel57
//
//   Rev 1.39   May 24 2003 15:02:30   PURDYECH
//Use getKey whenever the key is needed.  This abstracts the concept that they key is stored as the ItemData.
//
//   Rev 1.38   May 01 2003 15:29:48   PURDYECH
//Columns were not being set to correct width if there was no registry entry.  No we correctly deal with this boundary case.  Also, we sanity check the column width before setting it ... must be no less than 0 and no more than 1000 pels.
 * 
 *    Rev 1.37   Jan 06 2003 16:46:50   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.36   Nov 20 2002 11:34:42   PURDYECH
 * Change SetColumnHeadings to call the filterListColumn method of parent dialog.
 * 
 *    Rev 1.35   Nov 15 2002 15:31:12   KOVACSRO
 * Have to reload the list whenever calling GeMaxErrorState
 * 
 *    Rev 1.34   Nov 13 2002 13:32:10   PURDYECH
 * Virtualized and const'd up some of the methods to make extension simpler.
 * 
 *    Rev 1.33   Oct 09 2002 17:42:44   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.32   Oct 09 2002 16:11:08   DINACORN
 * Added EUROPEAN_DATE_FORMAT for ListSorterByManyColumns.
 * 
 *    Rev 1.31   Oct 07 2002 14:04:02   KOVACSRO
 * Added GetMaxErrorState().
 * 
 *    Rev 1.30   Sep 23 2002 14:17:32   PURDYECH
 * An assert had the wrong sense in PopulateAttributeType
 * 
 *    Rev 1.29   Sep 23 2002 14:02:00   OLTEANCR
 * modif. init(...) - set icon just for updatable list ctrls.
 * 
 *    Rev 1.28   Sep 19 2002 12:05:12   PURDYECH
 * BFFieldId has lost its operator long() method, so BFFieldId can no longer be compared to ints.  Code was changed to reflect this.
 * 
 *    Rev 1.27   Sep 13 2002 14:01:16   DINACORN
 * Fixed performance issues for sorters.
 * 
 *    Rev 1.26   Sep 11 2002 14:17:52   DINACORN
 * Sort fix for EUROPEAN_DATE_FORMAT.
 * 
 *    Rev 1.25   Sep 10 2002 14:34:36   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.24   Sep 10 2002 11:01:18   PURDYECH
 * SORT_COLUMN was moved from header to implementation
 * 
 *    Rev 1.23   Sep 03 2002 12:45:10   PURDYECH
 * BFFieldId and ClientLocale changes
 * 
 *    Rev 1.22   Aug 29 2002 12:57:34   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.21   Jul 05 2002 11:49:42   PURDYECH
 * Infrastructure Fixup ... no more ICU!
 * 
 *    Rev 1.20   May 28 2002 12:21:20   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.19   22 May 2002 19:17:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   Apr 04 2002 17:02:32   DINACORN
 * Added SortListCtrl().
 * 
 *    Rev 1.17   Mar 06 2002 11:42:06   DINACORN
 * 1. Added ListSorterByManyColumns().
 * 2. Added EUROPEAN_DATE_FORMAT sorter staff.
 * 
 *    Rev 1.16   04 Feb 2002 15:20:40   KOVACSRO
 * Added newSelection() method which calls HandleSelection() (basically no change)
 * 
 *    Rev 1.15   13 Nov 2001 10:14:20   KOVACSRO
 * synch-up to 1.13.1.0
 * 
 *    Rev 1.14   Oct 25 2001 19:01:00   IVESPAUL
 * Removed dependency on mfdstcids.
 *
 *    Rev 1.13   Sep 06 2001 14:14:08   ZHANGCEL
 * Support attribute type list
 *
 *    Rev 1.12   20 Aug 2001 15:58:48   HSUCHIN
 * changed ondblclkitem to return bool and use ON_NOTIFY_REFLECT_EX
 *
 *    Rev 1.11   Aug 15 2001 10:53:56   ZHANGCEL
 * Remove Icon from Attribute type list
 *
 *    Rev 1.10   Aug 15 2001 10:34:20   ZHANGCEL
 * support attibute type list
 *
 *    Rev 1.9   15 Aug 2001 09:45:02   YINGZ
 * support attribute type list
 *
 *    Rev 1.8   27 Jul 2001 12:52:34   YINGZ
 * fix reset problem
 *
 *    Rev 1.7   29 Jun 2001 11:16:22   HSUCHIN
 * bug fix for getfield
 *
 *    Rev 1.6   Jun 26 2001 19:01:58   PURDYECH
 * More Infrastructure Release 1.9 Integration stuff.
 *
 *    Rev 1.5   03 Apr 2001 11:57:56   KOVACSRO
 * Permission check stuff.
 *
 *    Rev 1.4   30 Mar 2001 12:12:40   KOVACSRO
 * Added SetCtrlReadOnly().
 *
 *    Rev 1.3   Dec 13 2000 15:10:18   KOVACSRO
 * Added bIsDummy to  DoListItemChanged, DoPreListItemChanged
 *
 *    Rev 1.2   Sep 28 2000 17:14:32   DINACORN
 * Modification for fix the big at substitution list (heading)
 *
 *    Rev 1.1   May 24 2000 10:20:40   BUZILA
 * fix displaying error icon
 *
 *    Rev 1.0   Feb 15 2000 11:01:40   SMITHDAV
 * Initial revision.
//
//    Rev 1.38   Jan 25 2000 15:39:56   YINGZ
// fix idx=-1
//
//    Rev 1.37   Jan 25 2000 15:35:16   YINGZ
// fix RefreshAllItems
//
//    Rev 1.36   Jan 22 2000 19:35:36   VASILEAD
// reloading child lists after resetting an item
//
//    Rev 1.35   Jan 19 2000 07:03:20   DT24433
// added reloading child lists after resetting an item
//
//    Rev 1.34   Jan 18 2000 16:40:58   DT24433
// changed resetCurrentItem to ResetCurrentItem
//
//    Rev 1.33   Jan 18 2000 16:41:24   YINGZ
// add resetCurrentItem for reset list
//
//    Rev 1.32   Jan 13 2000 17:01:00   DT24433
// added ConnectToData, Enable, Show & RefreshAllItems
//
//    Rev 1.31   Jan 11 2000 17:25:00   DT24433
// added RefreshCurrentListItem
//
//    Rev 1.30   Jan 10 2000 13:08:06   YINGZ
// fix GetNextSelection so that focused item will be selected
//
//    Rev 1.29   Jan 05 2000 18:03:46   DT24433
// validate previous item on selection change
//
//    Rev 1.28   Jan 04 2000 14:56:44   YINGZ
// fix heading order problem
//
//    Rev 1.27   Jan 03 2000 13:31:14   DT24433
// changed to get columns directly from data dictionary instead of thru process
//
//    Rev 1.26   Dec 24 1999 11:05:54   YINGZ
// clean up
//
//    Rev 1.25   Dec 24 1999 10:45:22   YINGZ
// modify GetItemNo and PopulateList
//
//    Rev 1.24   Dec 22 1999 16:07:14   YINGZ
// bug fix
//
//    Rev 1.23   Dec 22 1999 15:12:26   YINGZ
// sync list and view in SetSelection
//
//    Rev 1.22   Dec 21 1999 17:26:52   YINGZ
// add setselection by key
//
//    Rev 1.21   Dec 08 1999 16:22:46   DT24433
// changed new item checking & improved child list support
//
//    Rev 1.20   Dec 06 1999 18:27:04   DT24433
// added call to BaseDlg::DoPreListItemChanged
//
//    Rev 1.19   Dec 02 1999 11:28:12   DT24433
// added code to check autoadd when all rows deleted
//
//    Rev 1.18   Dec 01 1999 18:00:58   DT24433
// only add new row if updateable and auto add is on
//
//    Rev 1.17   Nov 30 1999 10:40:46   DT24433
// changed to not post user selection message
//
//    Rev 1.16   Nov 29 1999 15:03:32   YINGZ
// add bIsNewItem to DoListItemChanged
//
//    Rev 1.15   Nov 29 1999 11:40:20   PRAGERYA
// GetCurrentKey changed to return a reference
//
//    Rev 1.14   Nov 25 1999 09:34:56   YINGZ
// give column a default width and alignment (left)
//
//    Rev 1.13   Nov 24 1999 13:33:40   DT24433
// postmessage for selection
//
//    Rev 1.12   Nov 24 1999 11:01:30   DT24433
// added call to BaseDlg::ListItemChanged
//
//    Rev 1.11   Nov 23 1999 17:08:20   DT24433
// added icon support
//
//    Rev 1.10   Nov 23 1999 16:00:40   DT24433
// consolidated UpdateItem & added hourglass
//
//    Rev 1.9   Nov 17 1999 12:53:16   DT24433
// support empty lists and split out populate
//
//    Rev 1.8   Nov 15 1999 14:42:32   DT24433
// removed auto setfocus
//
//    Rev 1.7   Nov 13 1999 13:12:24   YINGZ
// add list filter
//
//    Rev 1.6   Nov 12 1999 16:19:58   DT24433
// fixed delete problem
//
//    Rev 1.5   Nov 12 1999 13:16:44   DT24433
// initial changes for container based list
//
//    Rev 1.4   Nov 11 1999 11:42:14   YINGZ
// sync with listctrl
//
//    Rev 1.3   Nov 06 1999 14:27:08   YINGZ
// add UpdateItem function
//
//    Rev 1.2   Oct 28 1999 09:35:28   YINGZ
// for a clean Get from PVCS!
//
//    Rev 1.1   Oct 15 1999 13:29:18   YINGZ
// make it compilable
 *
 *    Rev 1.17   Sep 29 1999 11:21:58   YINGZ
 * add Getm_currentItem
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

