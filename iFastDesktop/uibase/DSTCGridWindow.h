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
#include <grid\gxall.h>
#include <uibase\BaseDlg.h>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTCGridWindow :public CGXGridWnd
{
public:
   DSTCGridWindow(CDialog* pDlg,int iControlId,ROWCOL iRowNum,ROWCOL iColNum);
   ~DSTCGridWindow(){};
   void SetCellValue(ROWCOL row,ROWCOL col, DString& dstr);
   void SetCellValue(ROWCOL row,ROWCOL col, const CString& cstr);
   int getControlId(){return(ControlId);}
   ROWCOL getColNum(){return(_colNum);}
   ROWCOL getRowNum(){return(_rowNum);}
//	void AddCell(cell::CELL_STYLE,ROWCOL nRow,ROWCOL nCol,long lContainerId,long lFieldId);

   void FillComboByValue(BaseDlg* pBase,  ROWCOL nRow,ROWCOL nCol, const BFContainerId& idContainer, const BFFieldId& idField);
   void FillComboBySubstitute(BaseDlg* pBase,ROWCOL nRow,ROWCOL nCol, const BFContainerId& idSubstitute, const BFFieldId &idSubstituteItem);
protected:
//	virtual void OnChangedSelection(const CGXRange* pRange, BOOL bIsDragging, BOOL bKey);
   virtual BOOL OnStartSelection(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint point);

   CDialog* getParent(){ return(_pParent);}
   void setParent(CDialog* pDlg){_pParent = pDlg;}
   void SetDispFont();
   BOOL IsSelectionChanged(ROWCOL nRow,ROWCOL nCol);

   void ResetCombo(ROWCOL nRow,ROWCOL nCol);

private:
   /*
   typedef std::vector< const cell * > CELL;
   typedef CELL::iterator       CELL_ITERATOR;

  CELL   _cell;
*/
   ROWCOL _rowNum;
   ROWCOL _colNum;
   ROWCOL _oldRow;
   ROWCOL _oldCol;
   CDialog* _pParent;  
   int ControlId;
};
