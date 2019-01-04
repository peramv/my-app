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
// ^FILE   : DSTCGridWindow.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 11/24/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : DSTCGridWindow
//
// ^MEMBER VARIABLES :
//
//
//******************************************************************************
#include "stdafx.h"

#define WIN32UIBASE_DLL

#ifndef DSTCGRIDWINDOW_H
   #include "DSTCGridWindow.h"
#endif
namespace CND
{
}

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//****************************************************************************
DSTCGridWindow::DSTCGridWindow(CDialog* pDlg,int iControlId,ROWCOL iRowNum,ROWCOL iColNum):CGXGridWnd()
{
   ControlId = iControlId;
   _rowNum = iRowNum;
   _colNum = iColNum;

   setParent(pDlg);
   SubclassDlgItem(ControlId, pDlg);
   Initialize();
   SetRowCount(_rowNum);
   SetColCount(_colNum);
   GetParam()->EnableTrackColWidth(); 
   GetParam()->EnableSelection(GX_SELCELL  ); //(WORD) (GX_SELFULL & ~GX_SELCOL & ~GX_SELTABLE));
   ROWCOL _oldRow = 1;
   ROWCOL _oldCol = 1;

   SetDispFont();
}

//*****************************************************************************
void DSTCGridWindow::SetCellValue(ROWCOL row,ROWCOL col, DString& dstr1)
{
   SetCellValue(row,col,dstr1.c_str());
}

//*********************************************************************************
void DSTCGridWindow::SetCellValue(ROWCOL row,ROWCOL col, const CString& cstr)
{
   SetStyleRange(CGXRange(row,col),CGXStyle().SetValue(cstr) );
}
//********************************************************************************
void DSTCGridWindow::SetDispFont()
{
   CFont *pCFont = getParent()->GetFont();
   LOGFONT logFont;
   pCFont->GetLogFont(&logFont);
   for( int j = 0;j<= getRowNum();j++ )
      for( int i = 0;i<= getColNum();i++ )
         SetStyleRange(CGXRange( j,i),CGXStyle().SetFont( CGXFont().SetLogFont(logFont) ));


}
//********************************************************************************
BOOL DSTCGridWindow::IsSelectionChanged(ROWCOL nRow,ROWCOL nCol)
{
   if( _oldRow == nRow && _oldCol == nCol ) return(false);

   return(true);
}

//******************************************************************************
void DSTCGridWindow::ResetCombo(ROWCOL nRow,ROWCOL nCol)
{
   DString str = I_("");
   SetStyleRange(CGXRange(nRow,nCol),CGXStyle()
                 .SetControl(GX_IDS_CTRL_CBS_DROPDOWNLIST)
                 .SetChoiceList(str.c_str() ) ) ;

}

//--------------------------------------------------------------------------------
void DSTCGridWindow::FillComboByValue(BaseDlg* pBase,ROWCOL nRow,ROWCOL nCol,const BFContainerId& idContainer, const BFFieldId &idField)
{

   ResetCombo(nRow,nCol);

   CStringList temp;

   DString str,strList;

   const DString *pCurKey = &( pBase->getParent()->getCurrentListItemKey( pBase, idContainer ) );
   const DString *pKey=&(pBase->getParent()->getFirstListItemKey( pBase, idContainer ));

   if( (*pKey)!=NULL_STRING )
   {
      do
      {
         pBase->getParent()->getField( pBase, idContainer, idField, str,false );
         str.strip();
         if( temp.Find(str.c_str())==NULL )
         {
            temp.AddTail(str.c_str());
            strList += str;
            strList += I_("\n");
         }
      }while( *(pKey=&(pBase->getParent()->getNextListItemKey( pBase, idContainer ))) != NULL_STRING );

      if( (*pCurKey)!=NULL_STRING )
         pBase->getParent()->setCurrentListItem(pBase, idContainer, *pCurKey);
   }
   SetStyleRange(CGXRange(nRow,nCol),CGXStyle()
                 .SetControl(GX_IDS_CTRL_CBS_DROPDOWNLIST)
                 .SetChoiceList(strList.c_str() )
                ) ;

}

//--------------------------------------------------------------------------------
void DSTCGridWindow::FillComboBySubstitute(BaseDlg* pBase,ROWCOL nRow,ROWCOL nCol, const BFContainerId& idSubstitute, const BFFieldId &idSubstituteItem)
{


   ResetCombo(nRow,nCol);

   DString dstrDesc;
   DString dstrList;
   const DString *pKey = &( pBase->getParent()->getFirstListItemKey( pBase, idSubstitute ) );
   if( (*pKey)!=NULL_STRING )
   {
      do
      {
         pBase->getParent()->getField( pBase,  idSubstitute, idSubstituteItem, dstrDesc );
         dstrList += dstrDesc;
         dstrList += I_("\n");
         pKey = &( pBase->getParent()->getNextListItemKey( pBase, idSubstitute ) );
      } 
      while( *pKey != NULL_STRING );
   }

   SetStyleRange(CGXRange(nRow,nCol),CGXStyle()
                 .SetControl(GX_IDS_CTRL_CBS_DROPDOWNLIST)
                 .SetChoiceList(dstrList.c_str() ) ) ;
}
//******************************************************************************
/*
void DSTCGridWindow::SetDialogPnt(AddressBookDlg* _pDlg)
{
  _addDlg = _pDlg;
}
*/
//********************************************************************************
BOOL DSTCGridWindow::OnStartSelection(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint point)

{
   DString strValue;
   if( IsSelectionChanged(nRow,nCol) )
   {
      CString temp = GetValueRowCol( nRow, nCol );

      strValue = (LPCTSTR)temp;
//		SEVERITY sev = getDialogPnt()->SetMailingAddressField(_oldRow,_oldCol,strValue );
      _oldRow = nRow;
      _oldCol = nCol;
   }

   return(true);
}


