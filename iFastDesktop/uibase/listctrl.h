#pragma once

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
// ^FILE   : listctrl.h
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 5/22/97
//
// ^CLASS    : ListViewControl
// ^SUBCLASS PARENT : CListCtrl
//
// ^CLASS DESCRIPTION :
//
//
// -----------------------------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// -----------------------------------------------------------------------------
//
// ^METHOD      : ListViewControl
//
// ^DESCRIPTION : constructor
//
// ^PARAMETERS  :
//    ^^ bool bShowSelAlways - true = show selection always (default)
//                           - false = don't show selection if not focused
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : DeleteAllColumns
//
// ^DESCRIPTION : Deletes all existing columns. The user must delete items.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : DeleteColumn
//
// ^DESCRIPTION : Override CListCtrl's DeleteColumn so can keep track of
//                columns.
//
// ^PARAMETERS  :
//    ^^ int nCol - 0 relative column to delete
//
// ^RETURNS     :
//    ^^ BOOL - true = successful
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : DrawItem
//
// ^DESCRIPTION : Draw's an item in the control
//
// ^PARAMETERS  :
//    ^^ LPDRAWITEMSTRUCT pdi - structure defining item to draw
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : GetColumnCount
//
// ^DESCRIPTION : Get number of columns
//
// ^PARAMETERS  : none
//
// ^RETURNS     :
//    ^^ int - number of columns
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : GetNextSelection
//
// ^DESCRIPTION : Get next selected item
//
// ^PARAMETERS  :
//    ^^ int idx - index to start search from,
//                 -1 = start from beginning (default)
//
// ^RETURNS     :
//    ^^ int - Index of item or -1 if no selection found
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : InsertColumn
//
// ^DESCRIPTION : Override CListCtrl's InsertColumn to keep track of columns.
//
// ^PARAMETERS  :
//    ^^ int nCol                 - index of column to insert
//    ^^ const LV_COLUMN *pColumn - structure defining column to insert
//
// ^RETURNS     :
//    ^^ int - index of column if successful, or -1
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : InsertColumn
//
// ^DESCRIPTION : Override CListCtrl's InsertColumn to keep track of columns.
//
// ^PARAMETERS  :
//    ^^ int nCol                  - index of column to insert
//    ^^ LPCTSTR lpszColumnHeading - string for column heading
//    ^^ int nFormat               - format flags (default = LVCFMT_LEFT)
//    ^^ int nWidth                - Width in pixels (default = -1)
//    ^^ int nSubItem              - Associated subitem (default = -1)
//
// ^RETURNS     :
//    ^^ int - index of column if successful, or -1
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : SetSelection
//
// ^DESCRIPTION : Set selection state of row
//
// ^PARAMETERS  :
//    ^^ int idx   - index of row to set state
//    ^^ bool bSelect - true = selected (default)
//    ^^ bool bVisible - true = ensure visible (default)
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : SetSortColumn
//
// ^DESCRIPTION : Initializing a column for sorting on its corresponding
//                view member.
//
// ^PARAMETERS  :
//    ^^ int col              - Column # (zero-based)
//    ^^ string &ViewMember   - Defines the view field that is associated
//                            - with this column.
//    ^^ int  ElementType     - SORT_STRING(Default), SORT_INT, or SORT_FLOAT
//    ^^ BOOL UseSubstitution - Indicates whether or not to sort on
//                            - substitution value in view field definition
//                            - (Only valid for SORT_STRING). Default = FALSE
//    ^^ int  SortOrder       - Determines order on first sort
//                            - SORT_ASCENDING(Default), SORT_DESCENDING.
//    
//
// ^RETURNS     :
//    0 if successful, or -1
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : ColumnSortOff
//
// ^DESCRIPTION : Turns sorting off for a column
//
// ^PARAMETERS  :
//    ^^ int col              - Column # (zero-based)
//
// ^RETURNS     :
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// -----------------------------------------------------------------------------
//
// ^METHOD      : OnKillFocus
//
// ^DESCRIPTION : Need to repaint for focus.
//
// ^PARAMETERS  :
//    ^^ CWnd * pNewWnd - window getting focus
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : OnSetFocus
//
// ^DESCRIPTION : Need to repaint for focus
//
// ^PARAMETERS  :
//    ^^ CWnd *pOldWnd - Window losing focus
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
//
//******************************************************************************

//yakov sort [
#ifndef GENERICINTERFACE_HPP
   #include <bfproc\GenericInterface.hpp>
#endif
//yakov sort ]
#ifndef BASEDLG_H
   #include <uibase\BaseDlg.h>
#endif

#ifndef INCLUDED_MAP
   #include <map>
   #define INCLUDED_MAP
#endif 

// Macro to detect if a new selection occurred within LVN_ITEMCHANGED message
#define LVN_SELECTED \
   ( ( pNMListView->uChanged & LVIF_STATE ) == LVIF_STATE && \
   ( pNMListView->uNewState & LVIS_SELECTED ) == LVIS_SELECTED && \
   ( pNMListView->uOldState & LVIS_SELECTED ) != LVIS_SELECTED )

#define LVN_UNSELECTED \
   ( ( pNMListView->uChanged & LVIF_STATE ) == LVIF_STATE && \
   ( pNMListView->uNewState & LVIS_SELECTED ) != LVIS_SELECTED && \
   ( pNMListView->uOldState & LVIS_SELECTED ) == LVIS_SELECTED )

//  Definitions needed for Sorting capability
// (Added by Steve Bergee 08-15-1997)

#define  MAX_COLUMNS  20       // Arbitrary

#include <bfproc\bfcontainerid.hpp>


// Sort order
const int SORT_ASCENDING = 1;
const int SORT_DESCENDING = -1;
// Additional flags
const WORD NOT_SPECIFIED = 0x0000;
const WORD STRING_UPPERCASE = 0x0001;//upperCase both strings before comparison

class SortColumn;

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( push )
#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE ListViewControl : public CListCtrl
{
#pragma warning( pop )
public:
   ListViewControl( bool bShowSelAlways = true );
   ~ListViewControl();

   void Init(
            BaseDlg *pBD, 
            const BFFieldId &idSubstitute, 
            const BFContainerId& idList,
            const I_CHAR *dialogName,
            const I_CHAR *lvName
            );

   void PopulateList();
   int NewItem(DWORD ItemData);
   void SetColumnHeadings( const BFFieldId &idSubstitute, int nFormat = LVCFMT_LEFT, int nWidth = -1);
   BOOL SetItemString(int nItem, const I_CHAR * ColumnKey, DString &Str);
   BOOL SetItemString(DWORD ItemData, const I_CHAR * ColumnKey, DString &Str);
   CString GetItemString(int nItem, const I_CHAR * ColumnKey) const;

   void ColumnSortOff( int nCol );
   void DeleteAllColumns();
   bool DeleteColumn(
                    int nCol
                    );
   void DrawItem( LPDRAWITEMSTRUCT pdi );
   int GetColumnCount() const { return( m_columnCount ); }
   // Get next selected item
   // Returns index of first selected
   //  item or -1 if no selection
   int GetNextSelection( int idx = -1 /* Index to start after (-1 = all) */ );                                     
   int InsertColumn( int nCol,
                     const LV_COLUMN *pColumn );
   int InsertColumn( int nCol,
                     LPCTSTR lpszColumnHeading,
                     int nFormat = LVCFMT_LEFT,
                     int nWidth = -1,
                     int nSubItem = -1 );
   bool LoadSettings( const I_CHAR *dialogName,
                      const I_CHAR *lvName );
   bool SaveSettings( const I_CHAR *dialogName,
                      const I_CHAR *lvName );
   // Set selection state of row
   // If select, row will get focus
   void SetSelection( int idx, /* Row to set */
                      bool bSelect = true, /* true = select, false = unselect */
                      bool bVisible = true /* true = ensure visible */ );                                     

   int SetSortColumn( int nCol,
                      const GenericInterface *pCaller,
                      const BFContainerId& idList,
                      const BFFieldId &idField,
                      int iSortOrder = SORT_ASCENDING,
                      WORD wFlags = NOT_SPECIFIED );
   bool SortOnColumn( int nCol );
   static int CALLBACK ListSorter( LPARAM lParam1, 
                                   LPARAM lParam2,
                                   LPARAM lParamSort );
   void SetStateIcon(int nItem, int Severty = 0);
   void UpdateItem(DString *pKey);
   BOOL doSetItemText( int nItem, int nSubItem, LPCTSTR lpszText, BFFieldId fieldId );

protected:
   virtual void GetDrawColors( int       row,    // index of the listview item to draw
                               bool      enabled,
                               bool      focused,
                               bool      selected,
                               COLORREF &foreColor,
                               COLORREF &backColor,
                               COLORREF &backgroundColor );
   // Generated message map functions
   //{{AFX_MSG(ListViewControl)
   afx_msg void OnKillFocus(CWnd* pNewWnd);
   afx_msg void OnSetFocus(CWnd* pOldWnd);
   afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnDestroy();
   afx_msg void MeasureItem( LPMEASUREITEMSTRUCT lpmis );
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
   private:
   bool bIsDelete;
   bool bIsAdd;
   int GetItemNo(DString *pKey);
   int CurrentItem;
   BFFieldId _idSubstitute;
   BaseDlg* _pBD;
   BFContainerId idList_;
   GenericInterface *_pGICaller;
   bool m_bSetSizeOnce;
   bool m_bShowSelAlways;
   int m_columnCount;
   const I_CHAR *lvSettingName, *DlgName;
   SortColumn*  m_SortArray[MAX_COLUMNS];
// CImageList *m_Icons;

   // map column 
   typedef std::map< DString, int > COLUMNMAP;
#if _MSC_VER >= 1300
   typedef COLUMNMAP::const_iterator COLUMNMAP_CONST_ITER;
#else
   typedef COLUMNMAP::iterator COLUMNMAP_CONST_ITER;
#endif
   typedef COLUMNMAP::iterator COLUMNMAP_ITER;
   COLUMNMAP ColumnMap;

   // updatable fields associated with this control
   typedef std::vector< UINT > FIELDIDS;
   FIELDIDS _fieldIDs;

   void SetItemSize();
   void DrawItemColumn(
                      CDC *pDC,
                      LPTSTR lpsz,
                      LPRECT prcClip,
                      UINT fmt
                      );
   void RepaintSelectedItems();
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/listctrl.h-arc  $
 * 
 *    Rev 1.11   Jun 24 2005 17:01:30   Fengyong
 * PET1250 FN02 - EuroPean numeric enhancement
 * 
 *    Rev 1.10   Feb 11 2005 15:35:24   purdyech
 * PET910 - Removed compiler warning.
 * 
 *    Rev 1.9   Nov 14 2004 15:02:22   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.8   Jan 06 2003 16:47:02   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.7   Nov 08 2002 10:00:38   PURDYECH
 * Use #pragma warning(...) to remove warning C4275 (non-Dll interface class used as base for interface class).
 * 
 *    Rev 1.6   Oct 09 2002 17:42:50   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.5   Sep 10 2002 11:01:16   PURDYECH
 * SORT_COLUMN was moved from header to implementation
 * 
 *    Rev 1.4   Sep 09 2002 15:12:42   VADEANUM
 * Fixed some stupid thing in SortColumn - Chris Purdye
 * 
 *    Rev 1.3   Aug 29 2002 12:57:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.2   19 Mar 2002 13:36:16   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Feb 15 2000 18:58:56   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.18   Dec 29 1999 16:29:04   YINGZ
 * take off the first icon column
 * 
 *    Rev 1.17   Dec 06 1999 17:32:40   DT24433
 * removed basecontrol usage
 * 
 *    Rev 1.16   Nov 11 1999 11:33:56   YINGZ
 * for people to use
 * 
 *    Rev 1.15   Nov 06 1999 14:27:34   YINGZ
 * add UpdateItem function
 * 
 *    Rev 1.14   Nov 02 1999 17:28:32   YINGZ
 * add setitemstring
 * 
 *    Rev 1.13   Oct 18 1999 16:20:08   YINGZ
 * support indicator
 * 
 *    Rev 1.12   Sep 29 1999 11:22:06   YINGZ
 * add GetCurrentItem
 * 
 *    Rev 1.11   Sep 28 1999 09:25:18   YINGZ
 * put column align info, SetItemString and GetItemString
 * 
 *    Rev 1.10   Sep 14 1999 11:04:46   YINGZ
 * add configureable feature
 * 
 *    Rev 1.9   Sep 03 1999 16:14:18   YINGZ
 * change parameter
 * 
 *    Rev 1.8   Sep 01 1999 11:36:56   YINGZ
 * add SetColumnAlignment
 * 
 *    Rev 1.7   Aug 23 1999 09:49:22   YINGZ
 * associate field with column key
 * 
 *    Rev 1.6   Aug 19 1999 10:02:22   YINGZ
 * configuration
 * 
 *    Rev 1.5   Aug 18 1999 16:59:40   YINGZ
 * ?
 * 
 *    Rev 1.4   Jul 28 1999 13:34:14   VASILEAD
 * Jerry's changes
 * 
 *    Rev 1.3   Jul 20 1999 12:12:04   YINGZ
 * Auto save heading size
 * 
 *    Rev 1.2   Jul 15 1999 16:54:40   PRAGERYA
 * Sorting enabled
 * 
 *    Rev 1.1   Jul 08 1999 10:05:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
