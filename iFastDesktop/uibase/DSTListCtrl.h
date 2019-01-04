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
//    Copyright 2002 International Financial Data Services Ltd.
//
//******************************************************************************
//
// ^FILE   : listctrl.h
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 5/22/97
//
// ^CLASS    : DSTListCtrl
// ^SUBCLASS PARENT : CListCtrl
//
// ^CLASS DESCRIPTION :
//
//
// -----------------------------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// -----------------------------------------------------------------------------
//
// ^METHOD      : DSTListCtrl
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
//      0 if successful, or -1
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

#include <uibase\BaseDlgConstants.h>
#include <map>
#include <bfdata\bffieldid.hpp>
#include <bfproc\bfcontainerid.hpp>

// Forward references
class BaseDlg;
class GenericInterface;

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
//  (Added by Steve Bergee 08-15-1997)

#define  MAX_COLUMNS  20       // Arbitrary

// Sort order
const int SORT_ASCENDING = 1;
const int SORT_DESCENDING = -1;
// Additional flags
const WORD NOT_SPECIFIED         = 0x0000;
const WORD STRING_UPPERCASE      = 0x0001; // upperCase both strings before comparison
const WORD EUROPEAN_DATE_FORMAT  = 0x0002; // EuropeanDataFormat = dd/MM/yyyy

class SortColumn;

// Internal structure which describes many sorting columns
typedef struct _SortManyColumns
{
   const GenericInterface *m_pCaller;
   int m_iListId;
   BFFieldId m_idField[MAX_COLUMNS];
   int m_iFieldSortOrder[MAX_COLUMNS];
   int m_iColumnsNbr;
   WORD m_wFlags;
} SORT_MANY_COLUMNS, *PSORT_MANY_COLUMNS;

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTListCtrl  : public CListCtrl
{
public:
   DSTListCtrl( BaseDlg *rpDialog,
                const I_CHAR *dialogName,
                UINT controlID,
                UINT parentControlID,
                UINT flags,
                bool bShowSelAlways );
   ~DSTListCtrl();

   virtual SEVERITY AddRow();     // Add item to list
   virtual void ColumnSortOff( int nCol );
   virtual SEVERITY DeleteRow();  // Delete current item in list
   virtual void DeleteAllColumns();
   virtual bool DeleteColumn( int nCol );
   virtual void DrawItem( LPDRAWITEMSTRUCT pdi );
   virtual int GetColumnCount() const { return(m_columnCount); }

   const BFContainerId& getContainerId() const { return idContainer_; }
   /**
     * This method gets the Windows control ID for the list view.
     * @returns - UINT Windows control ID
     */
   UINT GetControlID() const { return(m_controlID); }
   /**
     * This method gets the key (item data) to the currently selected item.
     * @returns - String value of key
     */
   virtual const DString &GetCurrentKey() const;

   virtual CString GetItemString( int nItem, const I_CHAR * ColumnKey ) const;
   // Get next selected item
   // Returns index of first selected
   //  item or -1 if no selection
   int GetNextSelection( int idx = -1 /* Index to start after (-1 = all) */ ) const;
                                                              
   UINT GetParentControlID() const { return(m_parentControlID); }

   // init list type
   virtual void Init( BaseDlg *rpBD,
                      const BFFieldId &idSubstitute,
                      const BFContainerId& idContainer,
                      const I_CHAR *listName );

   // init attribute type
   virtual void Init( BaseDlg *rpBD,
                      const BFFieldId &idSubstitute,
                      const BFFieldId &idLeftSubstitute,
                      const BFContainerId& idContainer,
                      const I_CHAR *listName );

   int InsertColumn( int nCol, const LV_COLUMN *pColumn );
   int InsertColumn( int nCol, 
                     LPCTSTR lpszColumnHeading,
                     int nFormat = LVCFMT_LEFT,
                     int nWidth = -1,
                     int nSubItem = -1 );
   bool IsAutoAdd() const { return(!( m_flags & LISTFLAG_NOT_AUTO_ADD )); }
   bool IsUpdatable() const { return(!( m_flags & LISTFLAG_NOT_UPDATABLE )); }
   void setAutoAddFlag( bool newValue)
   {
      m_flags = newValue ? m_flags | LISTFLAG_NOT_AUTO_ADD : m_flags & ~((UINT)LISTFLAG_NOT_AUTO_ADD );
   }

   /**
     * This method loads associated data rows for the list.
     * @param rpStrKey - Key to set as selection, NULL = first row
     */
   virtual void PopulateList( const DString *rpStrKey );

   virtual void PopulateListType( const DString *rpStrKey );
   virtual void PopulateAttributeType( );
   /**
     * This method refreshes all list items from the container
     */
   virtual void RefreshAllItems();
   /**
     * This method refreshes the list item and controls associated with the item
     * @param bReregisterObservers - specify if we want to re-register the observers or not
     */
   virtual void RefreshCurrentItem(bool bReregisterObservers = false);
   /**
     * This method resets the associated list item back to the original data and
     * then refreshes the list item display and controls associated with the
     * item.
     */
   virtual void ResetCurrentItem();
   virtual void SetColumnHeadings( const BFFieldId &idSubstitute, int nFormat = LVCFMT_LEFT, int nWidth = -1);
   virtual BOOL SetItemString(int nItem, const I_CHAR * ColumnKey, DString &Str);

   // Set selection state of row
   void SetSelection( int idx,             // Row to set
                      bool bSelect = true, // true = select, false = unselect
                      bool bVisible = true // true = ensure visible
                    ); // If select, row will get focus

   // Set selection state of row
   void SetSelection( const DString *strKey, // Row to set
                      bool bSelect = true,   // true = select, false = unselect
                      bool bVisible = true   // true = ensure visible
                    ); // If select, row will get focus

   virtual int SetSortColumn( int nCol,
                      const GenericInterface *pCaller,
                      const BFContainerId& idList,
                      const BFFieldId &idField,
                      int iSortOrder = SORT_ASCENDING,
                      WORD wFlags = NOT_SPECIFIED );

   virtual bool SortOnColumn( int nCol );

   static int CALLBACK ListSorter( LPARAM lParam1, 
                                   LPARAM lParam2,
                                   LPARAM lParamSort );

   static int CALLBACK ListSorterByManyColumns( LPARAM lParam1,
                                                LPARAM lParam2,
                                                LPARAM lParamSort );

   // method perform sorting only if there are defined sortColumns in m_SortArray[]
   virtual void SortListCtrl();

   // Methods that are similar to BaseControl
   /**
   * This method sets the connected state.
   * @param bFlag - true = connected, get properties & setup
   *                false = disconnected, disable control for user input
   * @param bShowHideBasedOnConnection - true = use the connection state to
   *    show/hide list, false = don't affect visibility
   */
   virtual void ConnectToData( bool bFlag, bool bShowHideBasedOnConnection = false );
   /**
     * This method sets the Enabled state
     * @param bFlag - true = enabled
     */
   void Enable( bool bFlag );
   /**
     * This method checks if a control is connected to live data. If an item is
     * not data connected, it will be automatically disabled and cleared.
     * @returns true = data connected, false = disconnected
     */
   bool IsDataConnected() const
   {
      return(m_bDataConnected);
   }
   /**
     * This method checks the control's enabled state.
     * @returns true = enabled
     */
   bool IsEnabled() const
   {
      return(m_bEnabled);
   }
   /**
     * This method checks the control's visibility state.
     * @returns true = visible
     */
   bool IsVisible() const
   {
      return(m_bVisible);
   }
   /**
     * This method sets the visible state
     * @param bFlag - true = visible
     */
   void Show( bool bFlag ); 
   virtual void doOk(){};
   SEVERITY GetMaxErrorState();

   BOOL doSetItemText( int nItem, int nSubItem, LPCTSTR lpszText, BFFieldId fieldId );

protected:
   virtual void GetDrawColors(
                             int       row,    // index of the listview item to draw
                             bool      enabled,
                             bool      focused,
                             bool      selected,
                             COLORREF &foreColor,
                             COLORREF &backColor,
                             COLORREF &backgroundColor
                             ) const;
   bool doSetCtrlReadOnly(bool bReadOnly);
   virtual void newSelection(int iItem);
   void HandleSelection( int iItem );
   // Generated message map functions
   //{{AFX_MSG(DSTListCtrl )
   afx_msg void OnKillFocus(CWnd* pNewWnd);
   afx_msg void OnSetFocus(CWnd* pOldWnd);
   afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void Itemchanged( NMHDR* pNMHDR, LRESULT* pResult );
   afx_msg BOOL OnDblclkItem(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnDestroy();
   afx_msg void MeasureItem( LPMEASUREITEMSTRUCT lpmis );
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
//CP20021113private:
protected:  // hack to allow for use by derived classes (CP 20021113)
   // Flags that are similar to BaseControl
   bool m_bDataConnected;         // true = control connected to live data
   bool m_bEnabled;               // true = control is enabled
   bool m_bVisible;               // true = control is visible

   bool m_bDeleting;
   bool m_bSetSizeOnce;
   bool m_bShowSelAlways;
   int m_columnCount;
   UINT m_controlID;
   int m_currentItem;
   UINT m_flags;
   CImageList *m_icons;
   BFContainerId idContainer_;
   BFFieldId m_idSubstitute; 
   BFFieldId m_idLeftSubstitute;
   UINT m_parentControlID;
   GenericInterface *m_rpGICaller;
   BaseDlg *m_rpParentDialog;
   SortColumn*  m_SortArray[MAX_COLUMNS];
   DString m_strDialogName;
   DString m_strListName;
   SEVERITY m_sevMax;

   // map column
   typedef std::map< DString, int > COLUMNMAP;
#if _MSC_VER >= 1300
   typedef COLUMNMAP::const_iterator COLUMNMAP_CONST_ITER;
#else
   typedef COLUMNMAP::iterator COLUMNMAP_CONST_ITER;
#endif
   typedef COLUMNMAP::iterator COLUMNMAP_ITER;
   COLUMNMAP m_columnMap;

   BFFieldId m_idSubstituteCode;
   BFFieldId m_idSubstituteDescription;

   bool Deleting()
   {
      return(m_bDeleting);
   }

   void DrawItemColumn( CDC *pDC,
                        LPTSTR lpsz,
                        LPRECT prcClip,
                        UINT fmt );
   int GetItemNo( const DString *pKey ) const;
   virtual bool LoadSettings();
   virtual int NewItem( DWORD ItemData );
   void RepaintSelectedItems();
   virtual bool SaveSettings();
   void SetDeleting( bool bFlag )
   {
      m_bDeleting = bFlag;
   }
   void SetItemSize();
   virtual void UpdateItem( int idx );

   virtual const DString* getKey( int iItem ) const;

   // Methods that are similar to BaseControl
   /**
     * This method sets the data connected state
     * @param bFlag - true = data connected
     */
   void SetDataConnected( bool bFlag );

   static const DString s_strEmpty_;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTListCtrl.h-arc  $
 * 
 *    Rev 1.28   Jun 24 2005 17:01:38   Fengyong
 * PET1250 FN02 - EuroPean numeric enhancement
 * 
 *    Rev 1.27   Nov 14 2004 15:02:12   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.26   May 24 2003 15:01:46   PURDYECH
 * Made a bunch of methods virtual so that IFDSListCtrl could override them.
 * Added getKey() method so that it could work harmoniously with IFDSListCtrl.
 * 
 *    Rev 1.25   Jan 06 2003 16:46:54   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.24   Nov 27 2002 15:06:52   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.23   Nov 15 2002 15:30:18   KOVACSRO
 * Fixed GetMaxErrorState()
 * 
 *    Rev 1.22   Nov 13 2002 15:01:38   PURDYECH
 * Make methods/members which were private protected to allow derived classes to use them.
 * 
 *    Rev 1.21   Nov 13 2002 13:32:12   PURDYECH
 * Virtualized and const'd up some of the methods to make extension simpler.
 * 
 *    Rev 1.20   Nov 13 2002 11:43:20   PURDYECH
 * Fixed up C4275 warning error.
 * 
 *    Rev 1.19   Nov 08 2002 10:00:36   PURDYECH
 * Use #pragma warning(...) to remove warning C4275 (non-Dll interface class used as base for interface class).
 * 
 *    Rev 1.18   Oct 09 2002 17:42:46   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.17   Oct 07 2002 14:03:24   KOVACSRO
 * Added GetMaxErrorState().
 * 
 *    Rev 1.16   Sep 19 2002 12:05:58   PURDYECH
 * SortColumn used instead of SORTCOLUMN
 * 
 *    Rev 1.15.1.0   Sep 10 2002 11:01:16   PURDYECH
 * SORT_COLUMN was moved from header to implementation
 * 
 *    Rev 1.15   Sep 03 2002 12:45:08   PURDYECH
 * BFFieldId and ClientLocale changes
 * 
 *    Rev 1.14   Aug 29 2002 12:57:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   Jul 16 2002 09:54:54   KOVACSRO
 * Added doOk() which is triggered when user hits OK button.
 * 
 *    Rev 1.12   Apr 04 2002 17:02:32   DINACORN
 * Added SortListCtrl().
 * 
 *    Rev 1.11   19 Mar 2002 13:36:00   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.10   Mar 06 2002 11:42:06   DINACORN
 * 1. Added ListSorterByManyColumns().
 * 2. Added EUROPEAN_DATE_FORMAT sorter staff.
 * 
 *    Rev 1.9   04 Feb 2002 15:19:48   KOVACSRO
 * Added newSelection() method which calls HandleSelection() (basically no change)
 * 
 *    Rev 1.8   13 Nov 2001 10:12:10   KOVACSRO
 * synchup to 1.6.1.0
 * 
 *    Rev 1.7   Oct 25 2001 19:00:58   IVESPAUL
 * Removed dependency on mfdstcids.
 *
 *    Rev 1.6   20 Aug 2001 15:58:36   HSUCHIN
 * changed ondblclkitem to return bool and use ON_NOTIFY_REFLECT_EX
 *
 *    Rev 1.5   15 Aug 2001 09:45:20   YINGZ
 * support attribute type list
 *
 *    Rev 1.4   03 Apr 2001 11:47:20   KOVACSRO
 * Permission check stuff.
 *
 *    Rev 1.3   30 Mar 2001 12:06:56   KOVACSRO
 * Added SetCtrlReadOnly.
 *
 *    Rev 1.2   07 Mar 2001 15:44:40   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 *
 *    Rev 1.1   Feb 15 2000 18:58:54   MCNABBGL
 * changed comment format
 *
 *    Rev 1.0   Feb 15 2000 11:00:58   SMITHDAV
 * Initial revision.
//
//    Rev 1.15   Jan 18 2000 16:42:44   DT24433
// changed resetCurrentItem to ResetCurrentItem
//
//    Rev 1.14   Jan 18 2000 16:41:26   YINGZ
// add resetCurrentItem for reset list
//
//    Rev 1.13   Jan 13 2000 17:04:36   DT24433
// added ConnectToData, Enable, Show & RefreshAllItems
//
//    Rev 1.12   Jan 11 2000 17:27:02   DT24433
// added RefreshCurrentListItem
//
//    Rev 1.11   Dec 21 1999 17:26:54   YINGZ
// add setselection by key
//
//    Rev 1.10   Dec 08 1999 16:24:04   DT24433
// moved flags out to basedlgconstants.h
//
//    Rev 1.9   Dec 01 1999 17:55:38   DT24433
// added LISTFLAG_NOT_AUTO_ADD
//
//    Rev 1.8   Nov 29 1999 11:40:20   PRAGERYA
// GetCurrentKey changed to return a reference
//
//    Rev 1.7   Nov 24 1999 13:35:14   DT24433
// postmessage for selection
//
//    Rev 1.6   Nov 24 1999 11:08:22   DT24433
// added GetParentControl
//
//    Rev 1.5   Nov 23 1999 16:02:12   DT24433
// changed UpdateItem parm
//
//    Rev 1.4   Nov 17 1999 12:54:34   DT24433
// support empty lists and split out populate
//
//    Rev 1.3   Nov 12 1999 13:18:08   DT24433
// initial changes for container based list
//
//    Rev 1.2   Nov 11 1999 11:42:14   YINGZ
// sync with listctrl
//
//    Rev 1.1   Nov 06 1999 14:27:10   YINGZ
// add UpdateItem function
//
//    Rev 1.0   Oct 15 1999 13:23:16   YINGZ
// Initial revision.
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
