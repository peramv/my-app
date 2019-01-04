// This is a part of the Objective Grid C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government’s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Stefan Hoenig
//

// gxcmd.h : interface of the undo command classes


#ifndef _GXCMD_H_
#define _GXCMD_H_

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXABSTR_H_
#include "grid\gxabstr.h"	// Abstract base classes
#endif

// constants

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif



class CGXCommandFactory: public CGXAbstractCommandFactory
{
public:
	CGXCommandFactory();

	virtual CGXCommand* CreateBlockCmd(LPCTSTR s = NULL);
	virtual CGXCommand* CreateSetRowHeightCmd(ROWCOL nFromRow, ROWCOL nToRow, int* anHeightArray);
	virtual CGXCommand* CreateHideRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, BOOL* abHide);
	virtual CGXCommand* CreateSetDefaultRowHeightCmd(int nHeight);
	virtual CGXCommand* CreateSetColWidthCmd(ROWCOL nFromCol, ROWCOL nToCol, int* anWidthArray);
	virtual CGXCommand* CreateHideColsCmd(ROWCOL nFromCol, ROWCOL nToCol, BOOL* abHide);
	virtual CGXCommand* CreateSetDefaultColWidthCmd(int nWidth);
	virtual CGXCommand* CreateMoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	virtual CGXCommand* CreateMoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);
	virtual CGXCommand* CreateRemoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow);
	virtual CGXCommand* CreateRemoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol);
	virtual CGXCommand* CreateInsertRowsCmd(ROWCOL nRow, ROWCOL nCount, int* anHeightArray, CObArray* pCellsArray, CObArray* pRowsArray, ROWCOL nColCount);
	virtual CGXCommand* CreateInsertColsCmd(ROWCOL nCol, ROWCOL nCount, int* anWidthArray, CObArray* pCellsArray, CObArray* pColsArray, ROWCOL nRowCount);
	virtual CGXCommand* CreateSetCoveredCellsCmd(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol);
	virtual CGXCommand* CreateSetStyleRangeCmd(const CGXRange& range, int nType, CObArray* pCellsArray);
	virtual CGXCommand* CreateSetFrozenRowsCmd(ROWCOL nFrozenRows, ROWCOL nHeaderRows);
	virtual CGXCommand* CreateSetFrozenColsCmd(ROWCOL nFrozenCols, ROWCOL nHeaderCols);
	virtual CGXCommand* CreateMoveDataRowsCmd(const CGXRange& rangeSort, CRowColArray* pawRowIndex);
	virtual CGXCommand* CreateMoveDataColsCmd(const CGXRange& rangeSort, CRowColArray* pawColIndex);
	virtual CGXCommand* CreateChangeStylesMapCmd(const CGXStylesMap& stylesMap);
	virtual CGXCommand* CreateChangePropertiesCmd(const CGXProperties& Properties);
	virtual CGXCommand* CreateChangeBaseStyleCmd(WORD wStyleId, const CGXStyle& BaseStyle, const CString& sName);
	virtual CGXCommand* CreateMoveCellsCmd(const CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo);
	virtual CGXCommand* CreateSetRangeNameCmd(CString name, BOOL bOldRange, const CGXRange& oldRange);
	virtual CGXCommand* CreateDeleteRangeNameCmd(CString name, const CGXRange& oldRange, CObject* pUndoInfo);

	virtual BOOL SetAdvancedUndo(CGXGridCore* pGrid, BOOL bAdvUndo);
	virtual CObject* GetAdvancedUndoInfo(CGXGridCore* pGrid);
	virtual BOOL UndoAdvanced(CGXGridCore* pGrid, CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells);
	virtual void CleanAdvancedUndo(CGXGridCore* pGrid);
	virtual BOOL ExecuteCommand(CGXCommand* pCmd, CGXGridCore* pGrid, GXCmdType ctType);
	virtual void AddCommand(CGXGridCore* pGrid, CGXCommand* pCmd, GXCmdType ctCmd);
	virtual void RemoveCommand(CGXGridCore* pGrid, GXCmdType ctCmd);
	virtual BOOL Undo(CGXGridCore* pGrid);
	virtual BOOL Redo(CGXGridCore* pGrid);
	virtual void BeginTrans(CGXGridCore* pGrid, LPCTSTR s);
	virtual void CommitTrans(CGXGridCore* pGrid);
	virtual void Rollback(CGXGridCore* pGrid);
	virtual void OnCellUndone(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, BOOL bSetEdit);
	virtual BOOL CanUndo(CGXGridCore* pGrid, CCmdUI* pCmdUI);
	virtual BOOL CanRedo(CGXGridCore* pGrid, CCmdUI* pCmdUI);
	virtual BOOL CreateRemoveRowsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromRow, ROWCOL& nCount, ROWCOL& nColCount, CObArray*& pOldCellsArray, CObArray*& pOldRowsArray, CGXLongOperation& theOp);
	virtual BOOL CreateRemoveColsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromCol, ROWCOL& nCount, ROWCOL& nRowCount, CObArray*& pOldCellsArray, CObArray*& pOldRowsArray, CGXLongOperation& theOp);
};

// Command persistence

#define DECLARE_COMMAND(class_name) \
public: \
	static CString GXNEAR cmd##class_name; \
	virtual LPCTSTR GetDescription() const; \

#define IMPLEMENT_COMMAND(class_name, resource_id) \
	CString GXNEAR class_name::cmd##class_name; \
	LPCTSTR class_name::GetDescription() const \
		{ if (cmd##class_name.IsEmpty() && \
			!cmd##class_name.LoadString(resource_id)) \
				cmd##class_name = _T(' '); \
			return (LPCTSTR) cmd##class_name; } \

class CGXCommand: public CObject
{
	DECLARE_DYNAMIC(CGXCommand)
public:
	// Construction
	CGXCommand();
	virtual ~CGXCommand();

	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType) = 0;
			// TRUE, if succesfull
			// FALSE, if canceled

	ROWCOL  m_ncRow,        // current cell
			m_ncCol;
	BOOL    m_bCCell;
	CObject* m_pAdvUndo;

	// Data
	virtual LPCTSTR GetDescription() const = 0;
};

class CGXBlockCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXBlockCmd)

public:
	// Construction
	CGXBlockCmd(LPCTSTR s = NULL);
	virtual ~CGXBlockCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);
	virtual LPCTSTR GetDescription() const;

	// List of commands
	CObList m_CommandList;

protected:
	CString m_sDesc;
};

class CGXSetRowHeightCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXSetRowHeightCmd)
	DECLARE_COMMAND(CGXSetRowHeightCmd)

public:
	// Construction
	CGXSetRowHeightCmd(ROWCOL nFromRow, ROWCOL nToRow, int* anHeightArray);

	virtual ~CGXSetRowHeightCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromRow,
				m_nToRow;
	int*        m_anHeightArray;
};

class CGXHideRowsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXHideRowsCmd)
	DECLARE_COMMAND(CGXHideRowsCmd)

public:
	// Construction
	CGXHideRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, BOOL* abHide);

	virtual ~CGXHideRowsCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromRow,
				m_nToRow;
	BOOL*       m_abHide;
};

class CGXSetDefaultRowHeightCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXSetDefaultRowHeightCmd)
	DECLARE_COMMAND(CGXSetDefaultRowHeightCmd)

public:
	// Construction
	CGXSetDefaultRowHeightCmd(int nHeight);

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	int     m_nHeight;
};

class CGXSetColWidthCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXSetColWidthCmd)
	DECLARE_COMMAND(CGXSetColWidthCmd)

public:
	// Construction
	CGXSetColWidthCmd(ROWCOL nFromCol, ROWCOL nToCol, int* anWidthArray);

	virtual ~CGXSetColWidthCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromCol,
				m_nToCol;
	int*        m_anWidthArray;
};

class CGXHideColsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXHideColsCmd)
	DECLARE_COMMAND(CGXHideColsCmd)

public:
	// Construction
	CGXHideColsCmd(ROWCOL nFromCol, ROWCOL nToCol, BOOL* abHide);

	virtual ~CGXHideColsCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromCol,
				m_nToCol;
	BOOL*       m_abHide;
};

class CGXSetDefaultColWidthCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXSetDefaultColWidthCmd)
	DECLARE_COMMAND(CGXSetDefaultColWidthCmd)

public:
	// Construction
	CGXSetDefaultColWidthCmd(int nWidth);

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	int     m_nWidth;
};


class CGXMoveRowsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXMoveRowsCmd)
	DECLARE_COMMAND(CGXMoveRowsCmd)

public:
	// Construction
	CGXMoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromRow,
				m_nToRow,
				m_nDestRow;
};

class CGXMoveColsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXMoveColsCmd)
	DECLARE_COMMAND(CGXMoveColsCmd)

public:
	// Construction
	CGXMoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromCol,
				m_nToCol,
				m_nDestCol;
};

class CGXRemoveRowsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXRemoveRowsCmd)
	DECLARE_COMMAND(CGXRemoveRowsCmd)

public:
	// Construction
	CGXRemoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow);

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromRow,
				m_nToRow;
};

class CGXRemoveColsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXRemoveColsCmd)
	DECLARE_COMMAND(CGXRemoveColsCmd)

public:
	// Construction
	CGXRemoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol);

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFromCol,
				m_nToCol;
};

class CGXInsertRowsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXInsertRowsCmd)
	DECLARE_COMMAND(CGXInsertRowsCmd)

public:
	// Construction
	CGXInsertRowsCmd(ROWCOL nRow, ROWCOL nCount, int* anHeightArray, CObArray* pCellsArray, CObArray* pRowsArray, ROWCOL nColCount);
	virtual ~CGXInsertRowsCmd();

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nRow,
				m_nCount;

	int*        m_anHeightArray;
	CObArray*   m_pCellsArray;
	CObArray*   m_pRowsArray;
	ROWCOL      m_nColCount;    // No. of Columns in m_pCellsArray
};

class CGXInsertColsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXInsertColsCmd)
	DECLARE_COMMAND(CGXInsertColsCmd)

public:
	// Construction
	CGXInsertColsCmd(ROWCOL nCol, ROWCOL nCount, int* anWidthArray, CObArray* pCellsArray, CObArray* pColsArray, ROWCOL nRowCount);
	virtual ~CGXInsertColsCmd();

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nCol,
				m_nCount;

	int*        m_anWidthArray;
	CObArray*   m_pCellsArray;
	CObArray*   m_pColsArray;
	ROWCOL      m_nRowCount;    // No. of Rows in m_pCellsArray
};

class CGXSetCoveredCellsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXSetCoveredCellsCmd)
	DECLARE_COMMAND(CGXSetCoveredCellsCmd)

public:
	// Construction
	CGXSetCoveredCellsCmd(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol);

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nRow;
	ROWCOL      m_nCol;
	ROWCOL      m_nToRow;
	ROWCOL      m_nToCol;
};

class CGXSetStyleRangeCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXSetStyleRangeCmd)
	DECLARE_COMMAND(CGXSetStyleRangeCmd)

public:
	// Construction
	CGXSetStyleRangeCmd(const CGXRange& range, int nType, CObArray* pCellsArray);
	virtual ~CGXSetStyleRangeCmd();

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXRange    m_range;
	int         m_nType;

	CObArray*   m_pCellsArray;
};

class CGXSetFrozenRowsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXSetFrozenRowsCmd)
	DECLARE_COMMAND(CGXSetFrozenRowsCmd)

public:
	// Construction
	CGXSetFrozenRowsCmd(ROWCOL nFrozenRows, ROWCOL nHeaderRows);

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFrozenRows;
	ROWCOL      m_nHeaderRows;
};

class CGXSetFrozenColsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXSetFrozenColsCmd)
	DECLARE_COMMAND(CGXSetFrozenColsCmd)

public:
	// Construction
	CGXSetFrozenColsCmd(ROWCOL nFrozenCols, ROWCOL nHeaderCols);

	// Operation
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	ROWCOL      m_nFrozenCols;
	ROWCOL      m_nHeaderCols;
};

class CGXMoveDataRowsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXMoveDataRowsCmd)
	DECLARE_COMMAND(CGXMoveDataRowsCmd)

public:
	// Construction
	CGXMoveDataRowsCmd(const CGXRange& rangeSort, CRowColArray* pawRowIndex);

	virtual ~CGXMoveDataRowsCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CRowColArray*        m_pawRowIndex;
	CGXRange m_rangeSort;
};


class CGXMoveDataColsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXMoveDataColsCmd)
	DECLARE_COMMAND(CGXMoveDataColsCmd)

public:
	// Construction
	CGXMoveDataColsCmd(const CGXRange& rangeSort, CRowColArray* pawColIndex);

	virtual ~CGXMoveDataColsCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CRowColArray*        m_pawColIndex;
	CGXRange m_rangeSort;
};

class CGXChangeStylesMapCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXChangeStylesMapCmd)
	DECLARE_COMMAND(CGXChangeStylesMapCmd)

public:
	// Construction
	CGXChangeStylesMapCmd(const CGXStylesMap& stylesMap);
	virtual ~CGXChangeStylesMapCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXStylesMap* m_pStylesMap;
};

class CGXChangePropertiesCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXChangePropertiesCmd)
	DECLARE_COMMAND(CGXChangePropertiesCmd)

public:
	// Construction
	CGXChangePropertiesCmd(const CGXProperties& Properties);
	virtual ~CGXChangePropertiesCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXProperties* m_pProperties;
};

class CGXChangeBaseStyleCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXChangeBaseStyleCmd)

public:
	// Construction
	CGXChangeBaseStyleCmd(WORD wStyleId, const CGXStyle& BaseStyle, const CString& sName);
	virtual ~CGXChangeBaseStyleCmd();
	virtual LPCTSTR GetDescription() const;

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXStyle* m_pBaseStyle;
	CString m_sName;
	WORD m_wStyleId;
};

class CGXMoveCellsCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXMoveCellsCmd)
	DECLARE_COMMAND(CGXMoveCellsCmd)

public:
	// Construction
	CGXMoveCellsCmd(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo);
	virtual ~CGXMoveCellsCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CGXRange m_rg;
	ROWCOL m_nRow, m_nCol;
	CObject* m_pUndoInfo;
};

class CGXSetRangeNameCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXSetRangeNameCmd)
	DECLARE_COMMAND(CGXSetRangeNameCmd)

public:
	// Construction
	CGXSetRangeNameCmd(CString name, BOOL bOldRange, const CGXRange& oldRange);
	virtual ~CGXSetRangeNameCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CString m_strName;
	BOOL m_bOldRange;
	CGXRange m_oldRange;
};

class CGXDeleteRangeNameCmd: public CGXCommand
{
	DECLARE_DYNAMIC(CGXDeleteRangeNameCmd)
	DECLARE_COMMAND(CGXDeleteRangeNameCmd)

public:
	// Construction
	CGXDeleteRangeNameCmd(CString name, const CGXRange& oldRange, CObject* pUndoInfo);
	virtual ~CGXDeleteRangeNameCmd();

	// Operations
	virtual BOOL Execute(CGXGridCore* pGrid, GXCmdType ctType);

	// Data
	CString m_strName;
	CGXRange m_oldRange;
	CObject* m_pUndoInfo;
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES

// inlines

#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//


#endif //_GXCMD_H_
