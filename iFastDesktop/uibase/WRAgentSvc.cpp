// WRAgentSvc.cpp : implementation file

#include "stdafx.h"
#include "WRAgentSvc.h"
#include <mbstring.h>
#include <windows.h>
#include <atlconv.h>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWRAgentSvc

CWRAgentSvc* CWRAgentSvc::_instance = NULL;

CWRAgentSvc* CWRAgentSvc::Instance()
{
   if( _instance == 0 )
   {
      _instance = new CWRAgentSvc;
   }
   if( !_instance->m_bInitialized )
      _instance->Initialize();

   return(_instance);
}

void CWRAgentSvc::Destroy()
{
   if( _instance != 0 )
   {
      delete _instance;
   }
}

CWRAgentSvc::CWRAgentSvc()
{
   m_bInitialized = false;
}

void CWRAgentSvc::Initialize()
{
   m_hInOutFile = CreateFileMapping((HANDLE) 0xFFFFFFFF, NULL, PAGE_READWRITE, 0, IO_PARAM_MAX_SIZE, ST2WR_IO_PARAM);
   if( m_hInOutFile != NULL )
   {
      if( (m_lpvInOutBuf = MapViewOfFile(m_hInOutFile, FILE_MAP_WRITE, 0, 0, 0)) == NULL )
      {
         CloseHandle(m_hInOutFile);
      }
      else
         m_bInitialized = true;
   }
}
CWRAgentSvc::~CWRAgentSvc()
{
   if( m_lpvInOutBuf != NULL )
      UnmapViewOfFile(m_lpvInOutBuf);

   if( m_hInOutFile != NULL )
      CloseHandle(m_hInOutFile);
}




BEGIN_MESSAGE_MAP(CWRAgentSvc, CWnd)
//{{AFX_MSG_MAP(CWRAgentSvc)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()





/////////////////////////////////////////////////////////////////////////////
// CWRAgentSvc protected functions

#if defined INCLUDE_GRID
/*
BOOL CWRAgentSvc::ControlGetGrid(HWND hCtlWnd, CGXGridCore *&pGrid)
{
    CWnd *pCWnd = CWnd::FromHandle(hCtlWnd);
    
  pGrid=NULL;
  // Is it a grid?
  if(pCWnd->IsKindOf(RUNTIME_CLASS(CGXBrowserView)))
    pGrid = (CGXGridCore*) ((CGXBrowserView*)pCWnd);

  else if (pCWnd->IsKindOf(RUNTIME_CLASS(CGXBrowserWnd)))
    pGrid = (CGXGridCore*) ((CGXBrowserWnd*) pCWnd);

  else if (pCWnd->IsKindOf(RUNTIME_CLASS(CGXGridWnd)))
    pGrid = (CGXGridCore*) ((CGXGridWnd*) pCWnd);

  else if (pCWnd->IsKindOf(RUNTIME_CLASS(CGXGridView)))
    pGrid = (CGXGridCore*) ((CGXGridView*) pCWnd);

  else if (pCWnd->IsKindOf(RUNTIME_CLASS(CGXGridHandleView)))
    pGrid = ((CGXGridHandleView*) pCWnd)->GetGrid();

  if (pGrid)
      return (TRUE);
  else
    return (FALSE);
       
}
*/
int CWRAgentSvc::RemoveSpecialChars(CString& strBuf, int nRow)
{
   int nNewLinePos = 1, nSpacePos = 1;

   while( nNewLinePos != -1 )
   {
      nNewLinePos=strBuf.Find('\n');
      if( nNewLinePos != -1 )
         strBuf.SetAt(nNewLinePos,'_');
   }
   if( nRow == 0 )
   { //no empty space is allowed in the headers
      while( nSpacePos != -1 )
      {
         nSpacePos=strBuf.Find((TCHAR)" ");
         if( nSpacePos != -1 )
            strBuf.SetAt(nSpacePos, '_');
      }
   }
   return(TRUE);  
}

int CWRAgentSvc::SetCell(CGXGridCore * pGrid, int nRow, int nCol)
{
   return(pGrid->SetCurrentCell((ROWCOL)nRow, (ROWCOL)nCol, GX_SCROLLINVIEW | GX_INVALIDATE));
}

int CWRAgentSvc::GetCell(CGXGridCore * pGrid, ROWCOL * pRow, ROWCOL * pCol)
{
   if( pGrid->GetCurrentCell(pRow, pCol, FALSE) )
      return(TRUE);
   else
      return(FALSE);
}

int CWRAgentSvc::GetRowsColsCount(CGXGridCore * pGrid, int * pnRow, int * pnCol)
{
   *pnRow = pGrid->GetRowCount();
   *pnCol = pGrid->GetColCount();
   return(TRUE);
}

int CWRAgentSvc::GetCellData(CGXGridCore * pGrid, int nRow, int nCol, CString * text)
{
   *text = pGrid->GetValueRowCol((ROWCOL)nRow,(ROWCOL)nCol);

#ifdef _UNICODE

   USES_CONVERSION;//declared in "atlconv.h"
   LPSTR StrANSI;
   StrANSI = W2A(*text); //Convert UNICODE to ANSI
   *text = (LPCTSTR) StrANSI;

#endif //_UNICODE

   return(TRUE);
}

int CWRAgentSvc::GetCellColor(CGXGridCore * pGrid, int nRow, int nCol, long * color)
{
   const CGXStyle& style = pGrid->LookupStyleRowCol(nRow, nCol);
   *color = (style.GetInterior()).GetColor();
   return(TRUE);
}

int CWRAgentSvc::SetCellData(CGXGridCore * pGrid, int nRow, int nCol, CString text)
{
   BOOL rc;
   CGXRange* pRange = new (CGXRange);
   pRange->SetCells((ROWCOL)nRow, (ROWCOL) nCol);
   rc = pGrid->SetValueRange(*pRange, (LPCTSTR)text,gxOverride,0,GX_UPDATENOW);
   delete(pRange);
   return(rc);
}

int CWRAgentSvc::GetCellCoords(CGXGridCore * pGrid ,int nRow, int nCol, int *x, int *y)
{

   RECT rect;
   int row_sum = 0;
   int col_sum = 0;

   if( !pGrid )
      return(FALSE);
   else
   {
      for( int i=0; i <nRow;i++ )
         row_sum+=pGrid->GetRowHeight(i);
      for( int i=0; i <nCol;i++ )
         col_sum += pGrid->GetColWidth(i);


      row_sum +=(int) ((float)pGrid->GetRowHeight(nRow)/2.);
      col_sum +=(int) ((float)pGrid->GetColWidth(nCol)/2.);

      ::GetWindowRect(((CWnd*)pGrid)->GetSafeHwnd(), &rect);

      *x = rect.left + col_sum;


      *y = rect.top + row_sum;

      return(TRUE);
   }
}

int CWRAgentSvc::GetRowColFromPoint(CGXGridCore * pGrid, CPoint pt, int * pnRow, int * pnCol)
{
   ROWCOL nClientRow, nClientCol;

   nClientRow = pGrid->CalcClientRowFromPt(pt,NULL);
   nClientCol = pGrid->CalcClientColFromPt(pt,NULL);
   *pnRow = pGrid->GetRow(nClientRow);
   *pnCol = pGrid->GetCol(nClientCol);

   return(TRUE);
}

int CWRAgentSvc::GetControlType(CGXGridCore * pGrid, int nRow, int nCol, char *ctrl_type, int len)
{
   CGXControl *pCtrl = pGrid->GetControl(nRow,nCol);
   CGXControlClass *pCtrlClass =  pCtrl->GetControlClass();
   if( pCtrlClass == NULL )
      return(FALSE);
   else
   {
      _mbsncpy((unsigned char *)ctrl_type, (const unsigned char *)pCtrlClass->m_lpszClassName,len);
      return(TRUE);
   }
}

int CWRAgentSvc::SetSelectedCell(CGXGridCore * pGrid, int nRow)
{
   CGXRange* pRange = new (CGXRange);
   pRange->SetCells((ROWCOL)nRow, (ROWCOL) 1,(ROWCOL)nRow, pGrid->GetColCount());
   pGrid->SelectRange(*pRange, TRUE, TRUE);

   return(TRUE);
}

int CWRAgentSvc::GetSelectedRow(CGXGridCore * pGrid, int * pnRow)
{
   CRowColArray *awRowf = new (CRowColArray);
   CRowColArray *awRowl = new (CRowColArray);

   pGrid->GetSelectedRows(*awRowf,*awRowl, FALSE,TRUE);
   *pnRow = awRowf->GetAt(0);

   return(TRUE);
}

int CWRAgentSvc::GetCellRect(CGXGridCore * pGrid, int nRow, int nCol, CRect &rect)
{
   CGXControl* pControl = NULL;
   CString cs;
   pControl=pGrid->GetControl(nRow, nCol);
   rect = pControl->GetCellRect(nRow, nCol);   
   return(TRUE);
}

int CWRAgentSvc::GetCellValue(CGXGridCore * pGrid, int nRow, int nCol, CString& s)
{
   CGXControl* pControl = NULL;
   BOOL rc;
   TCHAR *pchar;

   pControl=pGrid->GetControl(nRow, nCol);
   const CGXStyle& style = pGrid->LookupStyleRowCol(nRow, nCol);
   rc=pControl->GetControlText(s,nRow,nCol,NULL,style);
   pchar = s.GetBuffer(MEDIUM_SIZE);
   return(TRUE);
}

int CWRAgentSvc::GetTopRowLeftCol(CGXGridCore * pGrid, POINT& prowcol)
{
   prowcol.x=pGrid->GetTopRow();
   prowcol.y=pGrid->GetLeftCol();
   return(TRUE);
}

int CWRAgentSvc::ScrollCellInView(CGXGridCore * pGrid, POINT prowcol)
{
   prowcol.x=pGrid->ScrollCellInView(prowcol.x, prowcol.y);
   return(TRUE);
}

LRESULT CWRAgentSvc::HandleWRGridMsg(WPARAM wParam, CGXGridCore * pGrid)
{

//	CGXGridCore * pGrid = NULL;
   CString strName, strData, strBuf;
   CStdioFile GridCaptFile;
   int nRowNum, nColNum, nRow, nCol, nX, nY;
   POINT ptRowCol;
   ROWCOL gxRow, gxCol;
   long lColor;
   ST_ROWCOLSTR gxRowColStr;
   char lpsTmpBuf[MEDIUM_SIZE];
   CRect rect;

   if( !m_bInitialized )
      return(FALSE);

   if( !pGrid )
      return(FALSE);

   switch( wParam )
   {
      
      case ST_GET_NAME_SVC:

         strName = pGrid->GetTabName();
         _mbscpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)(LPCTSTR)strName);
         return(TRUE);


      case ST_GRID_CAP_SVC:
#ifdef _UNICODE

         int UniStrLen;
         LPCTSTR FileName_A, FileName_W;
         FileName_A = (LPCTSTR)m_lpvInOutBuf; //ANSI string from WR

         // Get the size of the buffer required for UNICODE string 	
         UniStrLen=MultiByteToWideChar(CP_ACP, 0, (char *)FileName_A,-1, NULL, 0);

         // Allocate buffer for UNICODE string
         FileName_W = (LPTSTR)malloc(UniStrLen*sizeof(WCHAR));

         // Convert ANSI string to UNICODE
         MultiByteToWideChar(CP_ACP, 0, (char *)FileName_A,-1, (LPTSTR)FileName_W, UniStrLen);

         TRY
         { // attempts to open a file.
           // catch any exceptions
            GridCaptFile.Open(((LPCTSTR)FileName_W), CFile::modeCreate | CFile::modeWrite);;
         }
         CATCH(CException, e)
         {
            return(-1);
         }
         END_CATCH

         free((void*)FileName_W); //Free the UNICODE string buffer
#else
         TRY
         { // attempts to open a file.
           // catch any exceptions
            GridCaptFile.Open(((LPCTSTR)m_lpvInOutBuf), CFile::modeCreate | CFile::modeWrite);;

         }
         CATCH(CException, e)
         {
            return(-1);
         }
         END_CATCH
#endif //_UNICODE

         strData.Empty();
         nRowNum = pGrid->GetRowCount();
         nColNum = pGrid->GetColCount();

         for( nRow = 0; nRow <= nRowNum; nRow++ )
         {
            for( nCol = 1; nCol <= nColNum - 1; nCol++ )
            {
               /* For empty column names */
               if( (nRow == 0) && (pGrid->GetValueRowCol(nRow, nCol) == "") )
               {
                  strBuf.Format((LPTSTR)"#%d\t",nCol);
                  strData += strBuf;
               }
               else
               {
                  strBuf = pGrid->GetValueRowCol(nRow, nCol);
                  RemoveSpecialChars(strBuf, nRow);
                  strData += strBuf + "\t";
               }
            }
            if( (nRow==0) && (pGrid->GetValueRowCol(nRow, nCol) == "") )
            {
               strBuf.Format((LPTSTR)"#%d\n", nColNum);
               strData += strBuf;
            }
            else
            {
               strBuf = pGrid->GetValueRowCol(nRow, nCol);
               RemoveSpecialChars(strBuf, nRow);
               strData += strBuf + "\n";
            }
         }
         GridCaptFile.WriteString(strData);
         return(S_OK);


      case TBL_SET_SELECTED_CELL:

         ptRowCol = *((POINT *)m_lpvInOutBuf);
         nRow = ptRowCol.x;
         nCol = ptRowCol.y;
         return(SetCell(pGrid, nRow, nCol));


      case TBL_GET_SELECTED_CELL:

         if( GetCell(pGrid, &gxRow, &gxCol) )
         {
            ptRowCol.x = gxRow;
            ptRowCol.y = gxCol;
            PACK_PARAM_BUF(ptRowCol, POINT);
            return(TRUE);
         }
         else
            return(FALSE);


      case TBL_GET_ROWS_COLS_COUNT:

         if( GetRowsColsCount(pGrid, &nRow, &nCol) )
         {
            ptRowCol.x = nRow;
            ptRowCol.y = nCol;
            PACK_PARAM_BUF(ptRowCol, POINT);
            return(TRUE);
         }
         else
            return(FALSE);


      case TBL_GET_CELL_DATA:

         ptRowCol = *((POINT *)m_lpvInOutBuf);
         if( GetCellData(pGrid, ptRowCol.x, ptRowCol.y, &strData) )
         {
            _mbscpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)(LPCTSTR)strData);
            return(TRUE);
         }
         else
            return(FALSE);


      case TBL_GET_CELL_COLOR:

         ptRowCol = *((POINT *)m_lpvInOutBuf);

         if( GetCellColor(pGrid, ptRowCol.x, ptRowCol.y, &lColor) )
         {
            PACK_PARAM_BUF(lColor, long);
            return(TRUE);
         }
         else
            return(FALSE);


      case TBL_SET_CELL_DATA:

         gxRowColStr = *((ST_ROWCOLSTR *)m_lpvInOutBuf);  
         return(SetCellData(pGrid, gxRowColStr.nRow, gxRowColStr.nCol, gxRowColStr.str));


      case TBL_GET_CELL_COORDS:

         ptRowCol = *((POINT *)m_lpvInOutBuf);
         if( GetCellCoords(pGrid, ptRowCol.x, ptRowCol.y, &nX, &nY) )
         {
            ptRowCol.x = nX;
            ptRowCol.y = nY;
            PACK_PARAM_BUF(ptRowCol, POINT);
            return(TRUE);
         }
         else
            return(FALSE);


      case TBL_GET_ROW_COL_FROM_POINT:

         ptRowCol = *((POINT *)m_lpvInOutBuf);

         if( GetRowColFromPoint(pGrid, ptRowCol, &nRow, &nCol) )
         {
            ptRowCol.x = nRow;
            ptRowCol.y = nCol;
            PACK_PARAM_BUF(ptRowCol, POINT);
            return(TRUE);
         }
         else
            return(FALSE);


      case TBL_GET_CONTROL_TYPE:

         ptRowCol = *((POINT *)m_lpvInOutBuf);
         if( GetControlType(pGrid, ptRowCol.x, ptRowCol.y, lpsTmpBuf, SMALL_SIZE) )
         {
            memcpy(m_lpvInOutBuf, lpsTmpBuf, SMALL_SIZE);
            return(TRUE);
         }
         else
            return(FALSE);


      case TBL_SET_SELECTED_ROW:

         nRow = atoi((char *)(LPCTSTR)m_lpvInOutBuf);
         if( SetSelectedCell(pGrid, nRow) )
            return(TRUE);
         else
            return(FALSE);


      case TBL_GET_SELECTED_ROW:

         if( GetSelectedRow(pGrid, &nRow) )
         {
            sprintf(lpsTmpBuf, "#%d", nRow);
            _mbscpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)lpsTmpBuf);
            return(TRUE);
         }
         else
            return(FALSE);


      case TBL_GET_CELL_RECT:

         ptRowCol = *((POINT *)m_lpvInOutBuf);
         GetCellRect(pGrid, ptRowCol.x, ptRowCol.y, rect);
         PACK_PARAM_BUF(rect, RECT);
         return(TRUE);


      case TBL_GET_CELL_VALUE:

         ptRowCol = *((POINT *)m_lpvInOutBuf);
         GetCellValue(pGrid, ptRowCol.x, ptRowCol.y, strData);
         _mbscpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)(LPCTSTR)strData);
         return(TRUE);


      case TBL_GET_TOP_ROW_LEFT_COL:

         GetTopRowLeftCol(pGrid, ptRowCol);
         PACK_PARAM_BUF(ptRowCol, POINT);
         return(TRUE);


      case TBL_SCROLL_CELL_IN_VIEW:

         ptRowCol = *((POINT *)m_lpvInOutBuf);
         ScrollCellInView(pGrid, ptRowCol);
         return(TRUE);


      case TBL_GET_PGRID:

         return(long)pGrid;  

   }

   return(FALSE);
}

#endif //INCLUDE_GRID

#if defined	INCLUDE_TREE
/*
BOOL CWRAgentSvc::ControlGetTree(
  HWND control_handle,
  SECTreeCtrl *&pTreeCtrl,
  SECTreeView *&pTreeView,
  char *MswClass
)
{
  CWnd *pcwnd=NULL;
    CWnd *pCWnd = CWnd::FromHandle(control_handle);
    
  pTreeCtrl=NULL;
  pTreeView=NULL;

  // Is it a tree?
  if(pCWnd->IsKindOf(RUNTIME_CLASS(SECTreeCtrl)))
  {
    pTreeCtrl = ((SECTreeCtrl*)pCWnd);
    if(MswClass)
      strcpy( MswClass, "SECTreeCtrl");
  }
  else
    if(pCWnd->IsKindOf(RUNTIME_CLASS(SECTreeView)))
    {
      pTreeView = ((SECTreeView*)pCWnd);
      if(MswClass) 
        strcpy( MswClass, "SECTreeView");
    }
  
    return (BOOL)(pTreeCtrl||pTreeView);
       
}
*/
HTREEITEM CWRAgentSvc::tree_find_child( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, HTREEITEM hTreeItem, CString ItemText)
{
   HTREEITEM hChild, hFoundChild=0;
   CString CurrentItemText;

   hChild = pTreeCtrl? pTreeCtrl->GetNextItem( hTreeItem, TVGN_CHILD) : pTreeView->GetNextItem( hTreeItem, TVGN_CHILD);

   while( hChild )
   {
      CurrentItemText = pTreeCtrl? pTreeCtrl->GetItemText(hChild) : pTreeView->GetItemText(hChild);
      if( CurrentItemText == ItemText )
      {
         hFoundChild=hChild;
         break;
      }
      hChild = pTreeCtrl? pTreeCtrl->GetNextSiblingItem(hChild) : pTreeView->GetNextSiblingItem(hChild);
   }

   return(hFoundChild); 
}



BOOL CWRAgentSvc::tree_get_item_full_path( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, HTREEITEM hItem, CString *ItemFullPath)
{
   *ItemFullPath = "";

   while( hItem )
   {
      *ItemFullPath = (pTreeCtrl? pTreeCtrl->GetItemText( hItem) : pTreeView->GetItemText( hItem))+(*ItemFullPath);
      hItem=pTreeCtrl? pTreeCtrl->GetParentItem(hItem) : pTreeView->GetParentItem(hItem);
      if( hItem )
         *ItemFullPath = ";"+(*ItemFullPath);
   }

   return(TRUE);

}
BOOL CWRAgentSvc::tree_get_content( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView,  CString *TreeContent)
{
   int nIndex, ItemsCount, nContentSize;
   CString ItemPath;
   HTREEITEM hItem;
   (*TreeContent).Empty();

   //get items count
   ItemsCount =  ( pTreeCtrl? pTreeCtrl->GetItemCount() : pTreeView->GetItemCount() );

   for( nIndex=0; nIndex<ItemsCount; nIndex++ )
   {
      //Gets an HTREEITEM based on a list index//HTREEITEM GetItemAt(int nIndex) const
      if( (hItem = (pTreeCtrl? pTreeCtrl->GetItemAt(nIndex) : pTreeView->GetItemAt(nIndex)))==FALSE )
         continue;

      // Get item path from HTREEITEM
      if( !tree_get_item_full_path( pTreeCtrl, pTreeView, hItem, &ItemPath) )
         return(FALSE);

      //Append the current item to the content
      *TreeContent = (*TreeContent) + (ItemPath) + "\r\n" ; 

   }//for

   //Cut trailing "\r\n"
   nContentSize= (*TreeContent).GetLength();
   *TreeContent = (*TreeContent).Left(nContentSize-2);

   return(TRUE);
}

BOOL CWRAgentSvc::tree_get_item_from_full_path( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView, HTREEITEM *phItem, CString ItemFullPath, BOOL expand)
{
   CString item;
   HTREEITEM hItem = 0;

   while( ItemFullPath.GetLength() )
   {
      item=ItemFullPath.SpanExcluding( ";");   
      if( ItemFullPath.Find( ';')==-1 )
         ItemFullPath = "";
      else
         ItemFullPath = ItemFullPath.Mid( item.GetLength()+1);

      if( expand && hItem )
      {
         if( pTreeCtrl /* &&!pTree->IsExpanded( hItem)*/ )
            pTreeCtrl->Expand( hItem, TVE_EXPAND);
         else
            pTreeView->Expand( hItem, TVE_EXPAND);
      }
      if( (hItem = tree_find_child( pTreeCtrl, pTreeView, hItem, item))==FALSE )
         return(FALSE);
   }

   *phItem = hItem;
   return(TRUE);

}

BOOL CWRAgentSvc::tree_get_item_check_state(SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView,  HTREEITEM hItem, int *CheckState)
{
   UINT StateMask;

   *CheckState=-1;

   StateMask=(pTreeCtrl? pTreeCtrl->GetItemState(hItem, TVIS_STATEIMAGEMASK): pTreeView->GetItemState(hItem, TVIS_STATEIMAGEMASK));


   if( StateMask == INDEXTOSTATEIMAGEMASK(1) )
      *CheckState=Check_OFF;
   else
   {
      if( StateMask == INDEXTOSTATEIMAGEMASK(2) )
         *CheckState=Check_ON;
      else
      {
         if( StateMask == INDEXTOSTATEIMAGEMASK(3) )
            *CheckState=Check_DIMMED;
      }
   }

   return(TRUE);
}

BOOL CWRAgentSvc::tree_get_checked( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView,  CString *TreeContent, char* Separator)
{
   int nIndex, ItemsCount, nContentSize;
   CString ItemPath;
   HTREEITEM hItem;
   int CheckState=FALSE;

   *TreeContent = "";

   //get items count
   ItemsCount =  ( pTreeCtrl? pTreeCtrl->GetItemCount() : pTreeView->GetItemCount() );

   for( nIndex=0; nIndex<ItemsCount; nIndex++ )
   {
      //Gets an HTREEITEM based on a list index//HTREEITEM GetItemAt(int nIndex) const
      if( (hItem = ( pTreeCtrl? pTreeCtrl->GetItemAt(nIndex) : pTreeView->GetItemAt(nIndex)))==FALSE )
         continue;

      if( !tree_get_item_check_state(pTreeCtrl, pTreeView, hItem, &CheckState) )
         return(FALSE);

      if( CheckState == Check_ON )
      {
         // Get item path from HTREEITEM
         if( !tree_get_item_full_path( pTreeCtrl, pTreeView, hItem, &ItemPath) )
            return(FALSE);
         //Append the current item to the content
         *TreeContent=(*TreeContent) + (ItemPath) + Separator ; 
      }
   }//for

   //Cut trailing Separator
   nContentSize= (*TreeContent).GetLength();
   *TreeContent = (*TreeContent).Left( nContentSize - _mbslen((const unsigned char *)Separator));


   return(TRUE);
}
BOOL CWRAgentSvc::tree_get_checked_count( SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView,  int *CheckedCount)
{
   int ItemsCount, nIndex;
   HTREEITEM hItem;
   int CheckState=FALSE;

   *CheckedCount=0;

   //get items count
   ItemsCount =  ( pTreeCtrl? pTreeCtrl->GetItemCount() : pTreeView->GetItemCount() );

   for( nIndex=0; nIndex<ItemsCount; nIndex++ )
   {
      //Gets an HTREEITEM based on a list index//HTREEITEM GetItemAt(int nIndex) const
      if( (hItem = ( pTreeCtrl? pTreeCtrl->GetItemAt(nIndex) : pTreeView->GetItemAt(nIndex)))==FALSE )
         continue;

      if( !tree_get_item_check_state(pTreeCtrl, pTreeView, hItem, &CheckState) )
         return(FALSE);

      if( CheckState == Check_ON )
         (*CheckedCount)++;
   }//for

   return(TRUE);
}

BOOL CWRAgentSvc::tree_get_state_point(SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView,  HTREEITEM hItem, int* hCoord, int* vCoord)
{
   int xCoord, LeftCoord=0, RightCoord=0;
   RECT ItemRect, IconTextRect;
   CString ItemFullPath;
   CPoint point;
   UINT pFlags;
   HTREEITEM hHitItem;
   BOOL InFlag=FALSE;

   *hCoord=*vCoord=0;

   if( (pTreeCtrl? pTreeCtrl->EnsureVisible( hItem) : pTreeView->EnsureVisible( hItem)) != TRUE )
      return(FALSE);

   if( !( pTreeCtrl? pTreeCtrl->GetItemRect( hItem, &ItemRect, LVIR_BOUNDS) : pTreeView->GetItemRect( hItem, &ItemRect, LVIR_BOUNDS)) )
      return(FALSE);
   if( !( pTreeCtrl? pTreeCtrl->GetItemRect( hItem, &IconTextRect, LVIR_ICON/*Label only*/) : pTreeView->GetItemRect( hItem, &IconTextRect, LVIR_ICON/*Label only*/)) )
      if( !(pTreeCtrl? pTreeCtrl->GetItemRect( hItem, &IconTextRect, LVIR_LABEL/*Icon only*/) : pTreeView->GetItemRect( hItem, &IconTextRect, LVIR_LABEL/*Icon only*/)) )
         return(FALSE);

   point.y = (ItemRect.bottom + ItemRect.top)/2;

   for( xCoord=ItemRect.left; xCoord <= IconTextRect.left; xCoord+=2 )
   {
      point.x = xCoord;
      if( (hHitItem = pTreeCtrl? pTreeCtrl->HitTest( point, &pFlags): pTreeView->HitTest(  point,  &pFlags))==FALSE )
         return(FALSE);
      if( !InFlag )
      {
         if( pFlags & TVHT_ONITEMSTATEICON )
         {
            LeftCoord=xCoord;
            InFlag=TRUE;
         }
      }
      else
      {
         if( !(pFlags & TVHT_ONITEMSTATEICON) )
         {
            RightCoord=xCoord;
            break;
         }
      }
   }

   if( InFlag )
   {
      *hCoord=(LeftCoord+RightCoord)/2;
      *vCoord=point.y;  
   }

   return(TRUE);

}


LRESULT CWRAgentSvc::HandleWRTreeMsg(WPARAM wParam, SECTreeCtrl* pTreeCtrl, SECTreeView* pTreeView)
{

   CString strName, strData, strBuf;
   CStdioFile GridCaptFile;
   CRect rect;

   BOOL res;
   CPoint pt;
   HTREEITEM hItem;

   if( !m_bInitialized )
      return(FALSE);


   if( !pTreeCtrl && !pTreeView )
      return(FALSE);

   switch( wParam )
   {
      
      case GET_MSW_CLASS:
         {

            char MswClass[30];

            MswClass[0]=0;


            if( pTreeCtrl )
               _mbscpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)"SECTreeCtrl");
            else
               if( pTreeView )
               _mbscpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)"SECTreeView");
            else
               return(FALSE);       

            return(TRUE);

         }

      case TREE_GET_ITEM_RECT:
         {
            RECT ItemRect;

            hItem=*((HTREEITEM* )m_lpvInOutBuf);

            res = pTreeCtrl? pTreeCtrl->EnsureVisible( hItem) : pTreeView->EnsureVisible( hItem);
            if( res )
            {
               res = pTreeCtrl? pTreeCtrl->GetItemRect( hItem, &ItemRect, 2/*Label only*/) : pTreeView->GetItemRect( hItem, &ItemRect, 2/*Label only*/);
               PACK_PARAM_BUF( ItemRect, RECT);
            }

            return(res);
         }
      case TREE_EXPAND_ITEM:
         {

            hItem=*((HTREEITEM* )m_lpvInOutBuf);

            return(pTreeCtrl? pTreeCtrl->Expand( hItem, TVE_EXPAND) : pTreeView->Expand( hItem, TVE_EXPAND));
         }
      case TREE_COLLAPSE_ITEM:
         {


            hItem=*((HTREEITEM* )m_lpvInOutBuf);

            return(pTreeCtrl? pTreeCtrl->Expand( hItem, TVE_COLLAPSE) : pTreeView->Expand( hItem, TVE_COLLAPSE));
         } 
      case TREE_SELECT_ITEM:
         {

            hItem=*((HTREEITEM* )m_lpvInOutBuf);

            return(pTreeCtrl? pTreeCtrl->SelectItem(hItem) : pTreeView->SelectItem(hItem));
         }
      case TREE_GET_ITEM_FROM_POINT:
         {

            pt=*((POINT *)m_lpvInOutBuf);
            hItem = pTreeCtrl? pTreeCtrl->HitTest( pt) : pTreeView->HitTest( pt);
            PACK_PARAM_BUF( hItem, HTREEITEM);

            return(TRUE);
         }
      case TREE_IS_SELECTED:
         {
            BOOL IsSelected;

            hItem=*((HTREEITEM* )m_lpvInOutBuf);
            IsSelected = pTreeCtrl? pTreeCtrl->IsSelected( hItem) : 0;//pTreeView->IsSelected( hItem);
            PACK_PARAM_BUF( IsSelected, BOOL);

            return(TRUE);
         }
      case TREE_IS_EXPANDED:
         {
            BOOL IsExpanded;

            hItem=*((HTREEITEM* )m_lpvInOutBuf);
            IsExpanded = pTreeCtrl? pTreeCtrl->IsExpanded( hItem) : pTreeView->IsExpanded( hItem);
            PACK_PARAM_BUF( IsExpanded, BOOL);

            return(TRUE);
         }
      case TREE_GET_ITEM_FULL_PATH:
         {
            CString ItemFullPath;

            hItem=*((HTREEITEM* )m_lpvInOutBuf);
            if( !tree_get_item_full_path( pTreeCtrl, pTreeView, hItem,&ItemFullPath) )
               return(FALSE);

            _mbsncpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)(LPCTSTR)ItemFullPath, IO_PARAM_MAX_SIZE);
            return(TRUE);        

         }
      case TREE_GET_SELECTED:
         {
            CString ItemFullPath;

            if( (hItem = (pTreeCtrl? pTreeCtrl->GetFirstSelectedItem() : pTreeView->GetFirstSelectedItem()))==FALSE )
               return(FALSE);

            PACK_PARAM_BUF( hItem, HTREEITEM);
            return(TRUE);
         }

      case TREE_GET_ITEM_FROM_FULL_PATH:
         {
            CString ItemFullPath;

            ItemFullPath = (char*)m_lpvInOutBuf;

            if( !tree_get_item_from_full_path( pTreeCtrl, pTreeView, &hItem, ItemFullPath, TRUE) )
               return(FALSE);

            PACK_PARAM_BUF( hItem, HTREEITEM);
            return(TRUE);
         }

      case TREE_GET_ITEMS_COUNT:
         {
            UINT ItemsCount;

            ItemsCount =  ( pTreeCtrl? pTreeCtrl->GetItemCount() : pTreeView->GetItemCount() );

            PACK_PARAM_BUF( ItemsCount, UINT); 
            return(TRUE);
         }
      case TREE_GET_CONTENT:
         {
            static CString TreeContent;
            static int nContentSize;
            CString TreeChunk;
            int nChunk, nContentLeft, nChunkSize;
            TreeChunk="";

            nChunk = *((int* )m_lpvInOutBuf);

            if( nChunk==0 )
            {
               TreeContent.Empty();

               if( !tree_get_content( pTreeCtrl, pTreeView, &TreeContent) )
                  return(FALSE);

               nContentSize= TreeContent.GetLength();

#ifdef _UNICODE
               nContentSize= nContentSize * sizeof(WCHAR);
#endif //_UNICODE
            }

            nContentLeft = nContentSize - (nChunk*IO_PARAM_MAX_SIZE);
            TreeChunk=TreeContent.Right(nContentLeft);
            nChunkSize=TreeChunk.GetLength();

            _mbsncpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)(LPCTSTR)TreeChunk, IO_PARAM_MAX_SIZE);

            if( nContentLeft<= IO_PARAM_MAX_SIZE )
               return(E_FINAL);
            else
               return(E_CONTINUE);

         }

      case TREE_GET_CHECKED_ITEMS:
         {
            int nChunk, nContentLeft, nChunkSize,InParameter;
            static int nContentSize;
            TCHAR Separator[32]="";
            static CString TreeContent;
            CString TreeChunk;

            TreeChunk="";

            InParameter = *((int* )m_lpvInOutBuf);

            if( (InParameter==USE_WR_SEPARATOR)||(InParameter==USE_VER_SEPARATOR) )
            {
               nChunk=0;
               if( InParameter==USE_VER_SEPARATOR )
                  _mbsncpy((unsigned char *)Separator, (const unsigned char *)"\r\n", _mbslen((const unsigned char *)"\r\n"));
               else
                  GetPrivateProfileString((LPTSTR)"WrCfg", SEPARATOR_KEY_NAME,(LPTSTR)"",(LPTSTR)Separator ,64, (LPTSTR)"wrun.ini");
            }
            else
               nChunk=InParameter;

            if( nChunk==0 )
            {
               TreeContent.Empty();

               if( !tree_get_checked( pTreeCtrl, pTreeView, &TreeContent, Separator) )
                  return(FALSE);

               nContentSize= TreeContent.GetLength();

#ifdef _UNICODE
               nContentSize= nContentSize * sizeof(WCHAR);
#endif //_UNICODE
            }

            nContentLeft = nContentSize - (nChunk*IO_PARAM_MAX_SIZE);
            TreeChunk=TreeContent.Right(nContentLeft);
            nChunkSize=TreeChunk.GetLength();

            _mbsncpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)(LPCTSTR)TreeChunk, IO_PARAM_MAX_SIZE);

            if( nContentLeft<= IO_PARAM_MAX_SIZE )
               return(E_FINAL);
            else
               return(E_CONTINUE);

         }

      case TREE_GET_CHECKED_COUNT:
         {
            int CheckedCount;

            if( !tree_get_checked_count( pTreeCtrl, pTreeView, &CheckedCount) )
               return(FALSE);

            PACK_PARAM_BUF( CheckedCount, int); 

            return(TRUE);
         }

      case TREE_GET_ITEM_CHECK_STATE:
         {
            int CheckState;

            hItem=*((HTREEITEM* )m_lpvInOutBuf);

            if( !tree_get_item_check_state(pTreeCtrl, pTreeView, hItem, &CheckState) )
               return(FALSE);

            PACK_PARAM_BUF(CheckState, int);

            return(TRUE);
         }

      case TREE_GET_STATE_POINT:
         {
            int hCoord, vCoord;
            CString ItemFullPath;
            POINT StatePoint;

            StatePoint.x=NULL;
            StatePoint.y=NULL;  

            ItemFullPath = (char*)m_lpvInOutBuf;

            if( !tree_get_item_from_full_path( pTreeCtrl, pTreeView, &hItem, ItemFullPath, TRUE) )
               return(FALSE);

            if( !tree_get_state_point( pTreeCtrl, pTreeView, hItem, &hCoord, &vCoord) )
               return(FALSE);

            StatePoint.x=hCoord;
            StatePoint.y=vCoord;  

            PACK_PARAM_BUF( StatePoint, POINT);

            return(TRUE);
         }

      case TREE_GET_ITEM_INDEX:
         {
            int Index;
            HTREEITEM hItem;

            hItem=*((HTREEITEM* )m_lpvInOutBuf);

            Index = pTreeCtrl? pTreeCtrl->ItemIndex( hItem): pTreeView->ItemIndex( hItem);

            PACK_PARAM_BUF( Index, int);

            return(TRUE);
         }

      case TREE_GET_ITEM_FROM_INDEX:
         {
            int Index;

            Index =*((int* )m_lpvInOutBuf);

            hItem = pTreeCtrl? pTreeCtrl->GetItemAt( Index): pTreeView->GetItemAt( Index);

            if( !hItem )
               return(FALSE);

            PACK_PARAM_BUF( hItem, HTREEITEM);
            return(TRUE);
         }

      case TREE_GET_MULTI_SELECTED:
         {
            int nSize, res;
            HTREEITEM hCurrentItem;
            CString TreeMultiSelected, ItemPath;
            TCHAR Separator[IO_PARAM_MAX_SIZE]="";

            TreeMultiSelected.Empty();
            ItemPath.Empty();

            _mbsncpy((unsigned char *)Separator, (unsigned char *)m_lpvInOutBuf, IO_PARAM_MAX_SIZE);

            res=_mbsncmp((const unsigned char *) Separator, (const unsigned char *)"", 4);

            if( res==0 )
               GetPrivateProfileString((LPTSTR)"WrCfg", SEPARATOR_KEY_NAME,(LPTSTR)"",(LPTSTR)Separator ,64, (LPTSTR)"wrun.ini");

            if( (hItem = (pTreeCtrl? pTreeCtrl->GetFirstSelectedItem() : pTreeView->GetFirstSelectedItem()))==FALSE )
               return(FALSE);

            while( hItem )
            {
               // Get item path from HTREEITEM
               if( !tree_get_item_full_path( pTreeCtrl, pTreeView, hItem, &ItemPath) )
                  return(FALSE);

               //Append the current item to the content
               TreeMultiSelected=(TreeMultiSelected) + (ItemPath) + (Separator); 

               //Get next selected item
               hCurrentItem=hItem;
               if( (hItem = (pTreeCtrl? pTreeCtrl->GetNextSelectedItem(hCurrentItem) : pTreeView->GetNextSelectedItem(hCurrentItem)))==FALSE )
                  break;
            }

            //Cut trailing Separator
            nSize= TreeMultiSelected.GetLength();
            TreeMultiSelected = TreeMultiSelected.Left(nSize-_mbslen((const unsigned char *)Separator));

            _mbsncpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)(LPCTSTR)TreeMultiSelected, IO_PARAM_MAX_SIZE);

            return(TRUE);

         }

      case TREE_GET_SELECTED_COUNT:
         {
            int Count=0;
            HTREEITEM hCurrentItem;

            if( (hItem = (pTreeCtrl? pTreeCtrl->GetFirstSelectedItem() : pTreeView->GetFirstSelectedItem()))==FALSE )
            {
               PACK_PARAM_BUF( Count, int);
               return(TRUE);
            }

            while( hItem )
            {
               Count++;
               //Get next selected item
               hCurrentItem=hItem;
               if( (hItem = (pTreeCtrl? pTreeCtrl->GetNextSelectedItem(hCurrentItem) : pTreeView->GetNextSelectedItem(hCurrentItem)))==FALSE )
                  break;
            }

            PACK_PARAM_BUF( Count, int);
            return(TRUE);
         }
      case TREE_IS_ON_CHECK_ICON:
         {
            UINT pFlags;
            POINT point;
            BOOL bOnCheck;

            bOnCheck=FALSE;

            point=*((POINT *)m_lpvInOutBuf);

            if( (hItem = pTreeCtrl? pTreeCtrl->HitTest( point, &pFlags): pTreeView->HitTest(  point,  &pFlags))==FALSE )
               return(FALSE);

            if( pFlags & TVHT_ONITEMSTATEICON )
               bOnCheck=TRUE;

            PACK_PARAM_BUF( bOnCheck, BOOL);
            return(TRUE);
         }

   }

   return(FALSE);
}

#endif   // INCLUDE_TREE

#if defined	INCLUDE_TAB

LRESULT CWRAgentSvc::HandleWRTabMsg(WPARAM wParam, SECTabControlBase *pTabCtrl, SECTabWndBase *pTabWnd)
{

   CString strName, strData, strBuf;
   CStdioFile GridCaptFile;
   CRect rect;
   CPoint pt;
   char *TabName;
   CObject *Client;
   HMENU hMenu;
   void* pExtra;
   BOOL bSelected;

   if( !m_bInitialized )
      return(FALSE);

   if( !pTabCtrl )
   {
      if( pTabWnd )
         pTabCtrl = (SECTabControlBase *)pTabWnd->GetTabControl();
      else
         return(FALSE);
   }
   switch( wParam )
   {
      
      case TAB_GET_ITEM_COORDS:
         {
            char TabToSelect[MEDIUM_SIZE];

            _mbsncpy( (unsigned char *)TabToSelect, (const unsigned char *)m_lpvInOutBuf, MEDIUM_SIZE);

            if( !pTabCtrl )
               return(FALSE);

            int cTabs = pTabCtrl->GetTabCount();

            for( int i=0; i<cTabs; i++ )
            {
               pTabCtrl->GetTabInfo( i, TabName,  bSelected, Client, hMenu, pExtra);
               if( !_mbscmp( (const unsigned char *)TabName, (const unsigned char *)TabToSelect) )
               {
                  RECT rect;
                  CPoint p;
                  POINT point;
                  pTabCtrl->GetClientRect( /*(HWND)lParam,*/ &rect);
                  p.y = rect.bottom/2;
                  for( p.x=0; p.x<rect.right; p.x+=2 )
                     if( ((SECTabControl*)pTabCtrl)->TabHit( i, p) )
                     {
                        point.x=p.x;
                        point.y=p.y;
                        PACK_PARAM_BUF( point, POINT);
                        return(TRUE);
                     }

                  return(FALSE);
               }
            }
            return(FALSE);
         }
      case TAB_SELECT_ITEM:
         {

            if( (*((int* )m_lpvInOutBuf)) >= (pTabCtrl->GetTabCount()) )
               return(FALSE); //index out of the range

            pTabCtrl->ActivateTab(*((int* )m_lpvInOutBuf));
            return(TRUE);

         }
      case TAB_GET_ITEMS_COUNT:
         {
            int cTabs;

            if( ( cTabs = pTabCtrl->GetTabCount()) < NULL )
               return(FALSE);

            PACK_PARAM_BUF( cTabs, int);
            return(TRUE);

         }
      case TAB_GET_ITEM_NUMBER:
         {
            char TabToGetIndex[MEDIUM_SIZE];

            _mbsncpy( (unsigned char *)TabToGetIndex, (const unsigned char *)m_lpvInOutBuf, MEDIUM_SIZE);

            int cTabs = pTabCtrl->GetTabCount();

            for( int i=0; i<cTabs; i++ )
            {
               pTabCtrl->GetTabInfo( i, TabName,  bSelected, Client, hMenu, pExtra);
               if( !_mbscmp( (const unsigned char *)TabName, (const unsigned char *)TabToGetIndex) )
               {
                  PACK_PARAM_BUF( i, int);
                  return(TRUE);
               }
            }
            return(FALSE);
         }

      case TAB_GET_SELECTED:
         {

            pTabCtrl->GetActiveTab(*((int* )m_lpvInOutBuf));

            return(TRUE);
         }

      case TAB_GET_ITEM_NAME:
         {

            if( (*((int* )m_lpvInOutBuf)) >= (pTabCtrl->GetTabCount()) )
               return(FALSE); //index out of the range

            pTabCtrl->GetTabInfo( *((int* )m_lpvInOutBuf), TabName,  bSelected, Client, hMenu, pExtra);

            _mbscpy( (unsigned char *)m_lpvInOutBuf, (const unsigned char *)TabName);

            return(TRUE);
         }


      case GET_MSW_CLASS:
         {

            char MswClass[30];

            MswClass[0]=0;

            if( pTabWnd )
               _mbscpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)"SECTabWnd");
            else
               if( pTabCtrl )
               _mbscpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)"SECTabCtrl");
            else
               return(FALSE);       

            return(TRUE);

         }
   }

   return(FALSE);
}

#endif   // INCLUDE_TAB


#if defined	INCLUDE_TOOLBAR

typedef struct name_index
{
   unsigned char  name[256];
   int index;
} NAME_INDEX;

LRESULT CWRAgentSvc::HandleWRToolBarMsg(WPARAM wParam, SECCustomToolBar* pCustomToolBar)
{

   if( !m_bInitialized )
      return(FALSE);

   if( !pCustomToolBar )
      return(FALSE);

   switch( wParam )
   {
      case GET_MSW_CLASS:
         {

            char MswClass[30];

            MswClass[0]=0;

            if( pCustomToolBar )
               _mbscpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)"SECCustomToolBar");
            else
               return(FALSE);       

            return(TRUE);

         }
      case TOOLBAR_GET_BUTTONS_COUNT:
         {
            int ItemsCount;
            int nIndex;
            int VisibleCount;

            ItemsCount = pCustomToolBar->GetBtnCount();
            //Exclude Separator and Hidden buttons
            VisibleCount=0;
            for( nIndex=0; nIndex<ItemsCount; nIndex++ )
            {
               if( !IsBtnSeparatorOrHidden(pCustomToolBar, nIndex) )
                  VisibleCount++;
            }
            PACK_PARAM_BUF(VisibleCount, int);

            return(TRUE);
         }

      case TOOLBAR_BUTTON_GET_RECT:
         {
            int ButtonIndex;
            RECT rect;

            ButtonIndex = *((int* )m_lpvInOutBuf);
            int AbsIndex;
            if( !VisibleIndexToAbsIndex(pCustomToolBar, &ButtonIndex, &AbsIndex) )
               return(FALSE);
            pCustomToolBar->GetItemRect(AbsIndex, &rect);

            PACK_PARAM_BUF(rect, RECT);

            return(TRUE);


         }
      case TOOLBAR_GET_SELECTED:
         {
            int nCurButton;

            nCurButton = pCustomToolBar->GetCurBtn();       

            PACK_PARAM_BUF(nCurButton, int);

            return(TRUE);
         }
      case TOOLBAR_GET_RECORD_BUTTON_NAME:
         {
            int nIndex;
            nIndex = *((int* )m_lpvInOutBuf);

            char btnName[256];

            toolbar_get_button_name(pCustomToolBar, nIndex, btnName);

            _mbsncpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)(LPCTSTR)btnName, IO_PARAM_MAX_SIZE);

            return(TRUE);
         }
      case TOOLBAR_GET_BUTTON_NAME:
         {
            int nIndex;
            nIndex = *((int* )m_lpvInOutBuf);

            int AbsIndex;
            //convert mercury visible index to absolute index
            if( !VisibleIndexToAbsIndex(pCustomToolBar, &nIndex, &AbsIndex) )
               return(FALSE);

            char btnName[256];

            toolbar_get_button_name(pCustomToolBar, AbsIndex, btnName);

            _mbsncpy((unsigned char *)m_lpvInOutBuf, (unsigned char *)(LPCTSTR)btnName, IO_PARAM_MAX_SIZE);

            return(TRUE);
         }
      case TOOLBAR_GET_RECORD_BUTTON_INDEX:
         {
            int nIndex;
            int VisIndex;

            nIndex = *((int* )m_lpvInOutBuf);

            //convert to Mercury visible index
            AbsIndexToVisibleIndex(pCustomToolBar, &nIndex, &VisIndex);
            PACK_PARAM_BUF(VisIndex, int);
            return(TRUE);  
         }

      case TOOLBAR_GET_BUTTON_INDEX:
         {
            int nIndex;
            char BtnName[256];
            char CurrentBtnName[256];
            int ItemsCount;
            int VisIndex;

            _mbsncpy( (unsigned char *)BtnName, (const unsigned char *)m_lpvInOutBuf, 256);

            ItemsCount = pCustomToolBar->GetBtnCount();

            for( nIndex=0; nIndex<ItemsCount; nIndex++ )
            {
               toolbar_get_button_name(pCustomToolBar, nIndex, CurrentBtnName);
               if( _mbsncmp((const unsigned char *)BtnName, (const unsigned char *)CurrentBtnName,sizeof(BtnName))==0 )
               {
                  //convert to Mercury visible index
                  AbsIndexToVisibleIndex(pCustomToolBar, &nIndex, &VisIndex);
                  PACK_PARAM_BUF(VisIndex, int);
                  return(TRUE);
               }
            }
            //name does not exist
            nIndex= -1;
            PACK_PARAM_BUF(nIndex, int);
            return(FALSE);
         }
         return(TRUE);

   }//switch(wParam)

   return(TRUE);
}
BOOL CWRAgentSvc::IsBtnSeparatorOrHidden(SECCustomToolBar* pCustomToolBar, int nIndex)
{
   //get button instance
   BOOL StyleSeparator,StyleHidden;
   SECStdBtn* btn=pCustomToolBar->GetBtnObject(nIndex);
   StyleSeparator=btn->m_nStyle & TBBS_SEPARATOR;
   StyleHidden=btn->m_nStyle & TBBS_HIDDEN;

   if( StyleSeparator||StyleHidden )
   {
      return(TRUE);
   }
   return(FALSE);
}
int CWRAgentSvc::AbsIndexToVisibleIndex(SECCustomToolBar* pCustomToolBar, int* AbsoluteIndex, int* VisibleIndex)
{

   int index;
   int InvisibleCount=0;
   for( index=0; index <= (*AbsoluteIndex);index++ )
   {
      if( IsBtnSeparatorOrHidden(pCustomToolBar, index) )
         InvisibleCount++;
   }
   *VisibleIndex=(*AbsoluteIndex) - InvisibleCount;
   return(TRUE);
}

int CWRAgentSvc::VisibleIndexToAbsIndex(SECCustomToolBar* pCustomToolBar, int* VisibleIndex, int* AbsoluteIndex)
{

   int Index,ItemsCount;
   int VisibleCount=0;
   int VisIndex;
   BOOL SepOrHidden;
   VisIndex=*VisibleIndex;
   ItemsCount = pCustomToolBar->GetBtnCount();

   for( Index=0; Index < ItemsCount; Index++ )
   {
      SepOrHidden=IsBtnSeparatorOrHidden(pCustomToolBar, Index);
      if( !SepOrHidden )
         VisibleCount++;
      if( VisibleCount==(VisIndex+1) )
         break;

   }
   if( VisibleCount!=(VisIndex+1) )
      return(FALSE);
   *AbsoluteIndex=Index;
   return(TRUE);
}
int CWRAgentSvc::toolbar_get_button_name(SECCustomToolBar* pCustomToolBar, int nIndex, char * btnName)
{
   char load_string[256]="";
   char tooltip_string[256]="";


   SECStdBtn* btn=pCustomToolBar->GetBtnObject(nIndex);
   int ID = btn->m_nID;

   LoadString(NULL,ID, load_string, sizeof(load_string));

   if( unsigned char* p=_mbsstr((const unsigned char *)load_string,(const unsigned char *)"\n") )
   {
      _mbscpy((unsigned char *)tooltip_string,(const unsigned char *)p+1);


      if( _mbslen((const unsigned char *)tooltip_string)==0 )
      {
         //copy without the trailing '\n'
         _mbsncpy((unsigned char *)tooltip_string,(const unsigned char *)load_string,_mbslen((const unsigned char *)load_string)-1);
      }
   }
   else
      _mbscpy((unsigned char *)tooltip_string,(const unsigned char *)load_string);

   _mbscpy((unsigned char *)btnName,(const unsigned char *)tooltip_string);

   return(TRUE);
}
#endif   // INCLUDE_TOOLBAR
