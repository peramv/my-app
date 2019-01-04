#pragma once

// DSTGridWnd.h : header file
//
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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DSTGridWnd.h
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/03/2000
//
// ^CLASS    : DSTGridWnd
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include <Grid\GXALL.h>
#include <bfcbo\BFObserver.hpp>
#include <uibase\BaseControl.hpp>
#include <uibase\DSTOleDateTime.h>

#include <uibase\WRAgentDef.h>
#include <uibase\popupmessageres.h>

class BaseDlg;
class AbstractProcess;
class CAlphaNumericEditControl;
class DSTGridWnd;

/*************************************************************************

  ************         valid control types          ************
GX_IDS_CTRL_EDIT        "Edit Control"
GX_IDS_CTRL_DATETIME    "Date Time Control with popup calendar"
GX_IDS_CTRL_CBS_DROPDOWNLIST "MFC DropDownList"

GX_IDS_CTRL_STATIC      "Static Text"
GX_IDS_CTRL_PUSHBTN     "Pushbutton"
GX_IDS_CTRL_RADIOBTN    "Radio Buttons"
GX_IDS_CTRL_CHECKBOX    "Checkbox, 1/0"
GX_IDS_CTRL_COMBOBOX    "ComboBox, no text-fit"
GX_IDS_CTRL_HOTSPOT     "Hotspot Edit"
GX_IDS_CTRL_SPINEDIT    "Spin Edit"
GX_IDS_CTRL_HEADER      "Header"
GX_IDS_CTRL_SCROLLEDIT  "Edit Control, Scrollbar"
GX_IDS_CTRL_LISTBOX     "Listbox"
GX_IDS_CTRL_CHECKBOX3D  "Checkbox, 3d-Effect"
GX_IDS_CTRL_RADIOBTN3D  "Radio Buttons, 3d-Effect"
GX_IDS_CTRL_ZEROBASED   "ComboBox, zero-based"
GX_IDS_CTRL_ONEBASED    "ComboBox, one-based"
GX_IDS_CTRL_TEXTFIT     "ComboBox, text-fit"
GX_IDS_CTRL_CBS_DROPDOWN "MFC ComboBox"
GX_IDS_CTRL_ONEBASED_EX "Combo, disp.choice, 1-base"
GX_IDS_CTRL_ZEROBASED_EX "Combo, disp.choice, 0-base"
GX_IDS_CTRL_BROWSEARROWHEADER "Row Header"
GX_IDS_CTRL_RICHEDIT    "Rich Edit"
GX_IDS_CTRL_MASKEDIT    "Masked Edit"
GX_IDS_CTRL_PROGRESS    "Progressbar"
GX_IDS_CTRL_PASSWORD    "Password Edit"
GX_IDS_CTRL_CBS_TABBED_DROPDOWN "Tabbed MFC ComboBox"
GX_IDS_CTRL_CBS_TABBED_DROPDOWNLIST "Tabbed MFC DropDownList"
GX_IDS_CTRL_TABBED_COMBOBOX "Tabbed ComboBox"
GX_IDS_CTRL_CHECKLIST_COMBOBOX "Dropdown CheckListBox"
GX_IDS_CTRL_DATETIMENOCAL "Date Time control without calendar"


  ************         valid alignment          ************
DT_CENTER   Centers text horizontally.
DT_LEFT   Aligns text flush-left.
DT_RIGHT  Aligns text flush-right.

************************************************************************/
class DSTHeaderProperties
{
public:
   DSTHeaderProperties();
   DString strKey, strValue;
   int nCol, nWidth;
   UINT nAlignment; // the valid alignment are listed above
};

struct DSTComboProperties
{
   DSTComboProperties();

   BFFieldId idSubstitution;
   DString comboList; // when nInitMode = USE_IDI_STRING, the caller should prepare comboList which is an idi string
   int nInitMode;
   int nSortingMode;
};

struct SubstitutionCodeDesc;

class DSTCellProperties : public BFObserver
{
public:
   DSTCellProperties( DSTGridWnd * pParentGrid, ROWCOL nRow, ROWCOL nCol );
   virtual ~DSTCellProperties( );
   virtual void onNotify( E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString &hint );
   bool IsRegistered(){ return(m_bRegistered);};
   DSTGridWnd * m_pParentGrid;
   DString rowKey, colKey;
   DString listItemKey;
   DString m_mask;
   UINT nAlignment; // the valid alignment are listed above
   UINT cellCtrlType; // the valid control types are listed above
   BFFieldId idField;
   BFContainerId idContainer;
   UINT nIconId;
   int nCellState;
   UINT controlId;
   bool m_bRegistered;
   DSTComboProperties cb;
   ROWCOL m_nRow;
   ROWCOL m_nCol;
   SEVERITY m_sev;
   DString m_dstrAllowedChar;
};

class CNumericEditControl: public CGXEditControl
{
 GRID_DECLARE_CONTROL(CNumericEditControl) 
public: 
    // Constructor & Destructor
      CNumericEditControl(CGXGridCore* pGrid, UINT nID); 
protected: 
    // Overrides
//      BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
      BOOL ValidateString(const CString& sEdit);

   // Generated message map functions 
   //{{AFX_MSG(CNumericEditControl)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}; 

/////////////////////////////////////////////////////////////////////////////
// DSTGridWnd window

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTGridWnd : public CGXGridWnd, public BaseControl
{
   DECLARE_USING_WR_AGENT
// Construction
public:
   DSTGridWnd(
             BaseDlg *pParentDlg,
             const I_CHAR *dialogName,
             UINT controlId,
             const I_CHAR *gridName,
             const BFContainerId& idContainer,
             UINT controlGroupID,
             UINT flags);
   virtual ~DSTGridWnd();

// Attributes
public:
   enum GRID_TYPE
   {
      LIST, ATTRIBUTE, OTHER
   };
   enum COMBO_INIT_MODE
   {
      USE_SUBSTITUTION_LIST, MANUAL, USE_IDI_STRING
   };
   enum CELL_STATE
   {
      READ_ONLY, SKIPPED, USE_FIELD_PROPERTY
   };
   enum GRD_CMB_SORT_STATE
   {
      NO_SORT = 0, 
      CODE_ASCENDING, 
      CODE_DESCENDING, 
      DESC_ASCENDING, 
      DESC_DESCENDING
   };

// Operations
public:
   bool Store();
   void DoGetText(DString &strValueOut, int index) const;
   void DoInit(void);
   bool DoSetText(const DString &strValueIn, int index);

   // e.g., strAttributeCodes = I_("Fund,Class,") will exclude fund, class from attributes
   // to make things fast, strAttributeCodes must not contain space before and after ',' and must end with ','
   void SetExcludeAttributes( const DString &strAttributeCodes )
   {
      m_strAttributeCodes = strAttributeCodes;
   };


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTGridWnd)
   //}}AFX_VIRTUAL

// Implementation
public:
   void setUseCBOSubstitutions( bool bUseCBOSubstitutions = true ) { m_useCBOSubstitutions = bUseCBOSubstitutions;};

   void LoadGrid (bool bSetSelection = true);
   void reLoadGrid (bool bSetSelection = true);

   /**
    * Reload the cell which has the specified row name and column name
    * 
    * @param rowKey name of row
    * @param colKey name of column
    */
   void reloadCell( const DString& rowKey, const DString& colKey );

   void setGridType( int gridType ){ m_gridType = gridType;}

   void CreateHeader( const BFFieldId &idTopSubstitution, const BFFieldId &idLeftSubstitution = ifds::NullFieldId );
   void SetCurrCellProp( ROWCOL nRow, ROWCOL nCol, DSTCellProperties *cell );
   UINT GetControlGroupID()
   {
      return(m_controlGroupID);
   }

   void ClearGrid();
   void ClearContents();
   void ResetCurrentItem();
   void SetSorting( bool turnOnSorting ){m_turnOnSorting = turnOnSorting;};
   int SelectRow( const DString& strKey );
   void setContainer( const BFContainerId& idContainer );
   SEVERITY AddRow ( );
   SEVERITY DeleteRow ( );
   SEVERITY GetMaxErrorState();
   const DString& GetCurrentRowKey ();

   // Generated message map functions
protected:
   //{{AFX_MSG(DSTGridWnd)
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnTimer(UINT nIDEvent);
   DECLARE_WR_AGENT_MSG
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   bool SaveSettings();
   bool LoadSettings();

   BOOL OnActivateGrid( BOOL bActivate );
//   void OnGridSetFocus(CWnd* pOldWnd);
//   void OnGridKillFocus(CWnd* pOldWnd);
   void UpdateItem( int idx, const DString& rowKey );
   virtual BOOL OnTrackColWidth(ROWCOL nCol);
   virtual BOOL OnValidateCell(ROWCOL nRow, ROWCOL nCol);
   virtual BOOL OnStartEditing(ROWCOL nRow, ROWCOL nCol);

   virtual void OnDrawItem(CDC *pDC, 
                           ROWCOL nRow, 
                           ROWCOL nCol, 
                           const CRect& rectDraw, 
                           const CGXStyle& style);

   void InitCombobox( ROWCOL nRow, 
                      ROWCOL nCol, 
                      int nInitMode = USE_SUBSTITUTION_LIST,
                      int nSortingMode = NO_SORT,
                      const BFFieldId &idSubstitution = ifds::NullFieldId );

   void SetCellPropertiesPtr( ROWCOL nRow, ROWCOL nCol, DSTCellProperties *pDSTCellProperties );
   DSTCellProperties * GetCellPropertiesPtr( ROWCOL nRow, ROWCOL nCol );
   bool doSetCtrlReadOnly(bool bReadOnly);
   //virtual void OnModifyCell( ROWCOL nRow, ROWCOL nCol );
   void HandleSelection( int iItem );
   virtual void OnChangedSelection(const CGXRange* pRange, BOOL bIsDragging, BOOL bKey);
   virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
   virtual void OnClickedButtonRowCol(ROWCOL nRow, ROWCOL nCol);
   virtual BOOL  OnEndEditing(ROWCOL nRow, ROWCOL nCol);

   /**
    * Refresh cell contents.  
    * 
    * @param nRow
    * @param nCol
    * @param pParentProc
    * @param idContainer
    * 
    * @return 
    */
   BOOL refreshCell( ROWCOL nRow, ROWCOL nCol, AbstractProcess* pParentProc, const BFContainerId& idContainer );

   /**
    * Return 1-based index of row which corresponds to the specified key
    * 
    * @param rowKey name of row to find
    * 
    * @return 1-based index of row.  0 if row is not found.
    */
   ROWCOL getRowFromKey( const DString& rowKey ) const;

   /**
    * Return 1-based index of column which corresponds to the specified key
    * 
    * @param colKey name of column to find
    * 
    * @return 1-based index of column.  0 if column is not found.
    */
   ROWCOL getColFromKey( const DString& colKey ) const;
private:
   static const DString s_empty_;
private:
   int m_curRow;
   int m_newRow;
   UINT m_Timer;
   bool m_turnOnSorting;
   int m_sortAscending;
   bool bReadyForIcon;
   void DrawIcon( CDC *pDC, ROWCOL nRow, ROWCOL nCol, CRect& rectDraw );
   void privClearContents();
   void privClearContainer();
   void SetCell( ROWCOL nRow, ROWCOL nCol, DSTCellProperties *cell );
   int  PrepareHeader( const BFFieldId &idSubstitution, bool bIsTopHeader = true );
   void SetMessageFromConditions( CONDITIONVECTOR &conditions, CString& Msg );
   void PopulateListGrid( const BFContainerId& idContainer, bool bSetSelection = true);
   void PopulateAttriGrid( const BFContainerId& idContainer );
   void GetSubstituionCodeFromDesc( const BFContainerId& idContainer, const BFFieldId &idSubstition, const DString& dstrDesc, DString& dstrCode );
   void GetSubstituionCodeFromDesc( const DString& dstrIdi, const DString& dstrDesc, DString& dstrCode );
   void BuildComboStr( const DString& dstrIdi, CString& comboStr );
   void SortComboStr( int iSortMode, const DString& dstrIdiIn, DString& dstrIdiOut );
   bool isValueInList(CString& dstrValue,CString& dstrList );
   bool HideTheCode(DString& dstrTag );
   void SetCheckBoxTicked(ROWCOL nRow, ROWCOL nCol);

   bool isComboCell(UINT nCellCtrlType){
      return(
            nCellCtrlType == GX_IDS_CTRL_CBS_DROPDOWNLIST        || //"MFC DropDownList"
            nCellCtrlType == GX_IDS_CTRL_COMBOBOX                || //"ComboBox, no text-fit"
            nCellCtrlType == GX_IDS_CTRL_ZEROBASED               || //"ComboBox, zero-based"
            nCellCtrlType == GX_IDS_CTRL_ONEBASED                || //"ComboBox, one-based"
            nCellCtrlType == GX_IDS_CTRL_TEXTFIT                 || //"ComboBox, text-fit"
            nCellCtrlType == GX_IDS_CTRL_CBS_DROPDOWN            || //"MFC ComboBox"
            nCellCtrlType == GX_IDS_CTRL_ONEBASED_EX             || //"Combo, disp.choice, 1-base"
            nCellCtrlType == GX_IDS_CTRL_ZEROBASED_EX            || //"Combo, disp.choice, 0-base"
            nCellCtrlType == GX_IDS_CTRL_CBS_TABBED_DROPDOWN     || //"Tabbed MFC ComboBox"
            nCellCtrlType == GX_IDS_CTRL_CBS_TABBED_DROPDOWNLIST || //"Tabbed MFC DropDownList"
            nCellCtrlType == GX_IDS_CTRL_TABBED_COMBOBOX            //"Tabbed ComboBox"
            );
   };
   typedef std::vector< DSTCellProperties * > CELL;

   typedef std::vector< DSTHeaderProperties * > HEADER;

   typedef std::map< DString, ROWCOL > HEADERMAP;
   typedef HEADERMAP::iterator HEADERMAP_ITER;

   CELL              m_cell;

   HEADER            m_topHeader;
   HEADER            m_leftHeader;

   HEADERMAP         m_topHeaderMap;
   HEADERMAP         m_leftHeaderMap;

   LOGFONT           m_logFont;
   CONDITIONVECTOR   m_conditions;
   AbstractProcess * m_pParentProcess;
   BaseDlg         * m_pParentDlg;
   int               m_gridType;
   BFContainerId     idContainer_;
   bool              m_bHideLeftHeader;
   UINT              m_controlId;
   CImageList      * m_icons;
   UINT              m_controlGroupID;
   DString           m_strDialogName;
   DString           m_strGridName;
   BFFieldId         m_idTopSubstitution;
   BFFieldId         m_idLeftSubstitution;
   bool              m_useCBOSubstitutions;
   CString             m_dateFormat;
   DSTOleDateTime dt;

   DString             m_strAttributeCodes;
   bool                    bExcludeThisCode( DString& strCode );
   DString       m_currentKey;  
   DString       m_oldComboValue;
   UINT          m_flags;

   static bool codeAscending(const SubstitutionCodeDesc& input1, 
                             const SubstitutionCodeDesc& input2);
   static bool codeDescending(const SubstitutionCodeDesc& input1, 
                              const SubstitutionCodeDesc& input2);
   static bool descAscending(const SubstitutionCodeDesc& input1, 
                             const SubstitutionCodeDesc& input2);
   static bool descDescending(const SubstitutionCodeDesc& input1, 
                              const SubstitutionCodeDesc& input2);
                       
};
   
///////////////////////////////////////////////////////////////////////////////
//CAlphaNumericEditControl control
//Implements the Alphanumeric Control with set of characters input
///////////////////////////////////////////////////////////////////////////////

class CAlphaNumericEditControl: public CGXEditControl
{
  GRID_DECLARE_CONTROL(CAlphaNumericEditControl) 
public: 
    // Constructor & Destructor 	  
    CAlphaNumericEditControl(CGXGridCore* pGrid, UINT nID); 
	virtual ~CAlphaNumericEditControl();
	void GetAllowedCharacters( DString& dstrAllowedChar );
protected:
	 BOOL ValidateString(const CString& sEdit);
	 // Generated message map functions 
     //{{AFX_MSG(CNumericEditControl)
     //}}AFX_MSG
     DECLARE_MESSAGE_MAP()
}; 

/////////////////////////////////////////////////////////////////////////////


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTGridWnd.h-arc  $
 * 
 *   23-Oct-2014.Robs-fixing the task # issue .Renaming T78456 to T78460 in the checkin comments.
 *    Rev 1.54   Apr 15 2010 18:10:52   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - F4 Browser screen helper...
 * 
 *    Rev 1.53   Jul 24 2009 00:53:16   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.52   Jun 10 2005 12:52:40   popescu
 * Incident# 280865 - grid should not steal focus if there is a control with focus on it, due to the fact that the error state is greater then WARNING
 * 
 *    Rev 1.51   Feb 17 2005 16:43:38   popescu
 * Incident # 243445, added a new parameter to LoadGrid method that will determine, whether the grid selection should be set or not, based on the dialogs business flow - default parameter is true (always set the selection)
 * 
 *    Rev 1.50   Jan 10 2005 18:54:16   popescu
 * PTS 10037268, fee rate should only be entered as numeric
 * 
 *    Rev 1.49   Oct 01 2004 18:15:18   popescu
 * PET 1117/06, SSB Germany - Added 'flags' parameter to the grid control - not very useful for the moment
 * 
 *    Rev 1.48   Oct 01 2003 16:47:56   PURDYECH
 * Added public function clearContents() to remove the contents of a Grid without removing the headers, etc.
 * 
 *    Rev 1.47   Mar 20 2003 15:08:56   PURDYECH
 * Merge back from branch.
 * 
 *    Rev 1.46   Jan 06 2003 16:46:46   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.45   Nov 27 2002 15:06:48   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.44   Nov 13 2002 11:43:20   PURDYECH
 * Fixed up C4275 warning error.
 * 
 *    Rev 1.43   Nov 08 2002 10:00:34   PURDYECH
 * Use #pragma warning(...) to remove warning C4275 (non-Dll interface class used as base for interface class).
 * 
 *    Rev 1.42   Oct 09 2002 17:42:44   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.41   Oct 07 2002 13:51:44   KOVACSRO
 * Added GetMaxErrorState();
 * 
 *    Rev 1.40   Sep 19 2002 10:42:52   YINGBAOL
 * add setGrid type
 * 
 *    Rev 1.39   Sep 12 2002 15:27:38   YINGBAOL
 * support dynamic hide/show grid
 * 
 *    Rev 1.38   Sep 05 2002 14:01:00   HSUCHIN
 * added support for add/delete from Stingray Grid
 * 
 *    Rev 1.37   Sep 05 2002 10:43:00   DINACORN
 * Added setContainer().
 * 
 *    Rev 1.36   Aug 29 2002 12:57:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.35   Jul 25 2002 12:33:16   YINGBAOL
 * fix del in Combo ----PTS 10008601
 * 
 *    Rev 1.34   23 Jul 2002 10:23:40   YINGZ
 * rollback
 * 
 *    Rev 1.32   19 Jun 2002 11:52:12   YINGZ
 * positioning
 * 
 *    Rev 1.31   17 Jun 2002 16:36:32   YINGZ
 * position key when reload
 * 
 *    Rev 1.30   Jun 06 2002 15:38:26   YINGZ
 * allow disable sorting
 * 
 *    Rev 1.29   Jun 05 2002 16:47:18   YINGZ
 * support reset
 * 
 *    Rev 1.28   Jun 05 2002 14:13:40   YINGZ
 * support timer list
 * 
 *    Rev 1.27   Jun 04 2002 14:40:58   YINGZ
 * support check box
 * 
 *    Rev 1.26   Jun 03 2002 15:43:42   YINGZ
 * support drag
 * 
 *    Rev 1.25   May 30 2002 11:48:32   YINGZ
 * list/sorting support
 * 
 *    Rev 1.24   May 30 2002 10:10:46   YINGZ
 * check
 * 
 *    Rev 1.23   Apr 05 2002 17:02:06   VADEANUM
 * clearGrid() is public now.
 *
 *    Rev 1.22   Mar 20 2002 15:45:30   HERNANDO
 * Support for WinRunner Agent.
 *
 *    Rev 1.21   19 Mar 2002 13:36:24   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 *
 *    Rev 1.20   14 Mar 2002 15:50:10   KOVACSRO
 * Syncup 1.16-1.18
 *
 *    Rev 1.15   30 May 2001 15:43:14   YINGZ
 * support exclusion
 *
 *    Rev 1.14   Apr 26 2001 13:20:38   YINGZ
 * fix stingery date display problem
 *
 *    Rev 1.13   10 Apr 2001 14:12:10   KOVACSRO
 * removed UPDATABLE flag for cell state (permission check issue)
 *
 *    Rev 1.12   03 Apr 2001 11:46:42   KOVACSRO
 * Permission check stuff.
 *
 *    Rev 1.11   30 Mar 2001 17:40:14   KOVACSRO
 * Added SetCtrlReadOnly
 *
 *    Rev 1.10   Oct 30 2000 16:01:06   HUANGSHA
 * added function GetSubstitutionCodeFromDesc(...)
 *
 *    Rev 1.9   May 29 2000 09:20:08   BUZILA
 * added m_mask data member in order to support maskedEdit controls
 *
 *    Rev 1.8   May 09 2000 10:18:12   BUZILA
 * grid fixes
 *
 *    Rev 1.7   Apr 28 2000 18:20:06   BUZILA
 * M3
 *
 *    Rev 1.6   Apr 04 2000 12:59:24   BUZILA
 * implemented SaveSettings/LoadSettings
 *
 *    Rev 1.5   Mar 22 2000 12:56:32   BUZILA
 * Grid changes
 *
 *    Rev 1.4   Mar 14 2000 09:44:54   YINGZ
 * change nReadOnly to nCellState to provide more state
 *
 *    Rev 1.3   Mar 09 2000 11:35:50   YINGZ
 * modify comment 8))
 *
 *    Rev 1.2   Mar 09 2000 11:25:42   YINGZ
 * add OnStartEditing
 *
 *    Rev 1.1   Mar 08 2000 17:01:58   YINGZ
 * change linkage
 *
 *    Rev 1.0   Mar 08 2000 16:23:14   YINGZ
 * Initial revision.
*/