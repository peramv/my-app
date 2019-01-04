#if !defined(AFX_WRAgentSvc_H__AAD8E992_06C3_11D3_A916_00104B7AEFD4__INCLUDED_)
   #define AFX_WRAgentSvc_H__AAD8E992_06C3_11D3_A916_00104B7AEFD4__INCLUDED_


   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000
// WRAgentSvc.h : header file
//
//#define INCLUDE_TREE
   #define INCLUDE_GRID
//#define INCLUDE_TAB
//#define INCLUDE_TOOLBAR

   #ifndef _GXALL_H_
      #include <grid\gxall.h>
   #endif

   #ifndef INCLUDE_GRID
      #define CGXGridCore int
   #endif

   #define IO_PARAM_MAX_SIZE		0x1000
   #define SMALL_SIZE				64
   #define MEDIUM_SIZE				256
   #define PACK_PARAM_BUF(var, type) memcpy((void *)m_lpvInOutBuf, (void *)&var, sizeof(type));
   #define ST2WR_IO_PARAM			_TEXT("ST2WR_IO_PARAM")
   #define E_CONTINUE -1
   #define E_FINAL 1
   #define USE_WR_SEPARATOR 0
   #define USE_VER_SEPARATOR -1
   #define SEPARATOR_KEY_NAME _TEXT("HL_LISTVIEW_ITEM_SEPARATOR_STRING")

typedef struct
{
   long nRow;
   long nCol;
   CHAR  str[MEDIUM_SIZE]; 
} ST_ROWCOLSTR;

enum TREE_CHECK_STATE
{
   Check_OFF,
   Check_ON,
   Check_DIMMED,
};

enum
{
   ST_GET_NAME_SVC,
   ST_GRID_CAP_SVC,
   TBL_SET_SELECTED_CELL,
   TBL_GET_SELECTED_CELL,
   TBL_GET_ROWS_COLS_COUNT,
   TBL_SET_CELL_DATA,
   TBL_GET_CELL_DATA,
   TBL_GET_CELL_COORDS,           
   TBL_GET_COLUMN_NAMES,
   TBL_GET_ROW_COL_FROM_POINT,
   TBL_GET_CONTROL_TYPE,
   TBL_SET_SELECTED_ROW,
   TBL_GET_SELECTED_ROW,
   TBL_GET_CELL_RECT,
   TBL_GET_CELL_VALUE,
   TBL_GET_CELL_COLOR,
   TBL_GET_TOP_ROW_LEFT_COL,
   TBL_SCROLL_CELL_IN_VIEW,
   TBL_GET_PGRID,

   TREE_GET_ITEM_RECT,
   TREE_EXPAND_ITEM,
   TREE_COLLAPSE_ITEM,
   TREE_SELECT_ITEM,
   TREE_GET_ITEM_FROM_POINT,
   TREE_IS_SELECTED,
   TREE_IS_EXPANDED,
   TREE_GET_ITEM_FULL_PATH,
   TREE_GET_ITEM_FROM_FULL_PATH,
   TREE_GET_SELECTED,
   GET_MSW_CLASS,
   TREE_GET_ITEMS_COUNT,
   TREE_GET_CONTENT,
   TREE_GET_CHECKED_ITEMS,
   TREE_GET_CHECKED_COUNT,
   TREE_GET_ITEM_CHECK_STATE,
   TREE_GET_STATE_POINT,
   TREE_GET_ITEM_INDEX,
   TREE_GET_ITEM_FROM_INDEX,
   TREE_GET_MULTI_SELECTED,
   TREE_GET_SELECTED_COUNT,
   TREE_IS_ON_CHECK_ICON,

   TAB_SELECT_ITEM,
   TAB_GET_SELECTED,
   TAB_GET_ITEM_NAME,
   TAB_GET_ITEM_COORDS,
   TAB_GET_ITEM_NUMBER,
   TAB_GET_ITEMS_COUNT,

   TOOLBAR_GET_BUTTONS_COUNT,
   TOOLBAR_BUTTON_GET_RECT,
   TOOLBAR_GET_SELECTED,
   TOOLBAR_GET_BUTTON_NAME,
   TOOLBAR_GET_BUTTON_INDEX,
   TOOLBAR_GET_RECORD_BUTTON_NAME,
   TOOLBAR_GET_RECORD_BUTTON_INDEX
};

/////////////////////////////////////////////////////////////////////////////
// CWRAgentSvc window

class CWRAgentSvc : public CWnd
{
// Construction
public:

   static  CWRAgentSvc*  Instance(); // Instance returns a referance to the single class instance
   static  void    Destroy();  // Destroy the _instance pointer


// Attributes
protected:
   bool m_bInitialized;
   HANDLE m_hInOutFile;
   LPVOID m_lpvInOutBuf;
// Operations
private:

   static  CWRAgentSvc* _instance;   // the single class instance

// Overrides
   //{{AFX_VIRTUAL(CWRAgentSvc)

   //}}AFX_VIRTUAL

// Implementation
public:


   void CWRAgentSvc::Initialize();

#ifdef INCLUDE_TREE
   LRESULT HandleWRTreeMsg(WPARAM wParam, SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView);
#endif
#ifdef INCLUDE_GRID
   LRESULT HandleWRGridMsg(WPARAM wParam, CGXGridCore * pGrid);
#endif
#ifdef INCLUDE_TAB
   LRESULT CWRAgentSvc::HandleWRTabMsg(WPARAM wParam, SECTabControlBase *pTabCtrl, SECTabWndBase *pTabWnd);
#endif
#ifdef INCLUDE_TOOLBAR
   LRESULT HandleWRToolBarMsg(WPARAM wParam, SECCustomToolBar* pCustomToolBar);
#endif

   // Generated message map functions
protected:
   CWRAgentSvc();
   virtual ~CWRAgentSvc();

#ifdef INCLUDE_GRID
   BOOL ControlGetGrid(HWND hCtlWnd, CGXGridCore *&pGrid);
   int RemoveSpecialChars(CString & strBuf, int nRow);
   int SetCell(CGXGridCore * pGrid, int nRow, int nCol);
   int GetCell(CGXGridCore * pGrid, ROWCOL * pRow, ROWCOL * pCol);
   int GetRowsColsCount(CGXGridCore * pGrid, int * pnRow, int * pnCol);
   int GetCellData(CGXGridCore * pGrid, int nRow, int nCol, CString * text);
   int GetCellColor(CGXGridCore * pGrid, int nRow, int nCol, long * color);
   int SetCellData(CGXGridCore * pGrid, int nRow, int nCol, CString text);
   int GetCellCoords(CGXGridCore * pGrid, int nRow, int nCol, int * x, int  *y);
   int GetRowColFromPoint(CGXGridCore * pGrid, CPoint pt, int * pnRow, int * pnCol);
   int GetControlType(CGXGridCore * pGrid, int nRow, int nCol, char * ctrl_type, int len);
   int SetSelectedCell(CGXGridCore * pGrid, int nRow);
   int GetSelectedRow(CGXGridCore * pGrid, int * pnRow);
   int GetCellRect(CGXGridCore * pGrid, int nRow, int nCol, CRect & rect);
   int GetCellValue(CGXGridCore * pGrid, int nRow, int nCol, CString & s);
   int GetTopRowLeftCol(CGXGridCore * pGrid, POINT& prowcol);
   int ScrollCellInView(CGXGridCore * pGrid, POINT prowcol);
#endif

#if defined	INCLUDE_TREE   
   BOOL ControlGetTree( HWND control_handle, SECTreeCtrl *&pTreeCtrl,  SECTreeView *&pTreeView, char *MswClass=NULL);
   HTREEITEM tree_find_child( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, HTREEITEM hTreeItem, CString ItemText);
   BOOL tree_get_item_full_path( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, HTREEITEM hItem, CString *ItemFullPath);
   BOOL tree_get_item_from_full_path( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, HTREEITEM *phItem, CString ItemFullPath, BOOL expand);
//LRESULT HandleWRTreeMsg(WPARAM wParam, SECTreeCtrl* pTreeCtrl);//, SECTreeView* pTreeView);
   BOOL tree_get_content( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, CString *TreeContent);
   BOOL tree_get_item_check_state( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, HTREEITEM hItem, int* CheckState);
   BOOL tree_get_checked( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, CString *ItemPath, char* Separator);
   BOOL tree_get_checked_count( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, int* CheckedCount);
   BOOL tree_get_state_point( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, HTREEITEM hItem, int* hCoord, int* vCoord);
#endif   

#if defined	INCLUDE_TAB  
//BOOL ControlGetTab(	HWND control_handle, SECTabWndBase *&pTabWnd, SECTabControlBase *&pTabCtrl,	char *MswClass=NULL);
//LRESULT HandleWRTabMsg(WPARAM wParam, SECTabWndBase *pTabWnd,	SECTabControlBase *pTabCtrl);
#endif   

#if defined	INCLUDE_TOOLBAR   
   BOOL IsBtnSeparatorOrHidden(SECCustomToolBar* pCustomToolBar, int nIndex);
   int toolbar_get_button_name(SECCustomToolBar* pCustomToolBar, int nIndex, char* btnName);
   int AbsIndexToVisibleIndex(SECCustomToolBar* pCustomToolBar, int* AbsoluteIndex, int* VisibleIndex);
   int VisibleIndexToAbsIndex(SECCustomToolBar* pCustomToolBar, int* VisibleIndex, int* AbsoluteIndex);

#endif
   //{{AFX_MSG(CWRAgentSvc)

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_WRAgentSvc_H__AAD8E992_06C3_11D3_A916_00104B7AEFD4__INCLUDED_)
