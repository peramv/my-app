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

// gxengine.h : Objective Grid interface to the formula engine
//

#ifndef _GXENGINE_H_
#define _GXENGINE_H_

#ifndef _GXCOLL_H_
#include "grid\gxcoll.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA	GX_DATAEXT
#endif

struct gxCell;
struct _gx_formula;
typedef struct _gx_formula gxFormula;

struct _gx_keyword;
typedef struct _gx_keyword gxKeyword;

class CGXUndoEngineCellsInfo;
class CGXFormula;
class CGXWorksheetFunctions;

class GX_ENGINE_STATE: public CObject
{
public:
// costruction/destruction
	GX_ENGINE_STATE();
	virtual ~GX_ENGINE_STATE();

	// Support for custom worksheet functions
	void SetWorksheetFunctionClass(CGXWorksheetFunctions* pClassObject);
	void SetDefaultWorksheetFunctions();

// Attributes
	int print_lotus;
	int print_lc;
	int print_at_sign;

	int expr_err_flag;
	int error_reason;
	int error_position;

	int xs_error_silence;
	int xs_error_status;
	int xs_error_code;
	int last_severity;
	int doing_insert_or_delete;

	TCHAR _gx_col_to_text_alpha[10];
	TCHAR _gx_rc_to_text_id[20];
	TCHAR _gx_range_to_text_buf[24];

	int iso_escape;

	CString text_buf;
	
	// sheet contexts
	CPtrArray m_apSheetContext;

	CGXWorksheetFunctions* m_pWorksheetFunctions;
};

GX_ENGINE_STATE* __cdecl GXGetEngineState();

void __cdecl GXEnableWorksheetFunctions();

class CGXFormulaSheet: public CGXData
{
	DECLARE_SERIAL(CGXFormulaSheet)

public:
// Constructor/Destructor
	CGXFormulaSheet();
	virtual ~CGXFormulaSheet();
	void ResetSheet();
	virtual void InitParam(CGXGridParam* pParam);

// Value Interface
	virtual BOOL SetFormulaRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszFormula);
	virtual BOOL SetTextRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszText);
	virtual BOOL SetNumberRowCol(ROWCOL nRow, ROWCOL nCol, double number);
	virtual BOOL SetFormatRowCol(ROWCOL nRow, ROWCOL nCol, unsigned format, unsigned places);
	virtual unsigned GetFormatRowCol(ROWCOL nRow, ROWCOL nCol, unsigned* pPlaces = NULL);

	virtual BOOL SetExpressionRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszInput);
		// parse text, set formula/text/number, apply format (if date)

	virtual int GetNumberRowCol(ROWCOL nRow, ROWCOL nCol, double& number);
		// formula will be evaluated if needed
		// d will be 0 for text cells 
		// returns errcode (ok, error, constraint, cycle, N/A)

	virtual int GetTextRowCol(ROWCOL nRow, ROWCOL nCol, CString& sText);
		// formula will be evaluated if needed
		// numeric cells will be converted to string 
		// returns errcode (ok, error, constraint, cycle, N/A)

	virtual int GetExpressionRowCol(ROWCOL nRow, ROWCOL nCol, CString& sText);
		// stores formula as string is sText if formula cell
		// otherwise cell value will be stored in sText
		// returns errcode (ok, error, constraint, cycle, N/A)

// Convert Row/Col Coordinates
	static int __cdecl GetEngineRow(ROWCOL nRow);
	static int __cdecl GetEngineCol(ROWCOL nCol);
	static ROWCOL __cdecl GetGridRow(int nEngineRow);
	static ROWCOL __cdecl GetGridCol(int nEngineCol);

// Common settings for Formula Engine:
	void SetIterationLimit(int nLimit);	// 0 - no iteration
	int GetIterationLimit() const;

	void SetBlanksAreZeros(BOOL bToggle);
	BOOL GetBlanksAreZeros() const;

	void SetRecalcMode(int nMode);	// automatic/manual
	int GetRecalcMode() const;

	void SetRecalcMethod(int nMethod); // foreground / as needed
	int GetRecalcMethod() const;

	void SetConstraintCheck(BOOL bToggle);	
	BOOL GetConstraintCheck() const;

// Base Styles
	void RegisterBaseStyles(CGXStylesMap* pMap);

	// CGXStyle* colstyles, rowstyles, tablestyle will 
	// be inherited from CGXData

// overrides
	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);
	virtual const CGXData& operator=(const CGXData& p);

	// Inserting Colums or Rows
	virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount);
	virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount);

	// Removing Colums or Rows
	virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow);
	virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol);

	// Moving Colums or Rows
	virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);

	// copy/move ranges in one step
	virtual BOOL StoreCopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol);
	virtual BOOL StoreMoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndoInfo, int ctCmd);

	// gxCell data
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType = 0);
	BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, GXModifyType mt, int nType = 0);
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType = 0);

	// Sorting (rearraging) rows and columns
	virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& anRowIndex);
	virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& anColIndex);

	// Update
	virtual BOOL GetUpdateFlag(ROWCOL nRow, ROWCOL nCol);  
	virtual void SetUpdateFlag(ROWCOL nRow, ROWCOL nCol, BOOL bToggle);  
		// set update flag (TRUE if cell shall be updated next time CGXGridCore::RefreshView is called)
	virtual void AddRecalcRange(const CGXRange& range);
	virtual void Recalc(BOOL bForceRecalc = FALSE);
	virtual void ResetError();
	virtual BOOL GetError(CString& strError);

	// Range names
	virtual BOOL SetRangeName(LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo = NULL);
	virtual BOOL GetRangeName(LPCTSTR name, CGXRange& rg);
	virtual BOOL DeleteRangeName(LPCTSTR name, CObject*& pUndoInfo, BOOL bCreateUndoInfo);
	BOOL GetRangeNameArray(CStringArray& strarray) const;
	void SetRangeNameArray(CStringArray& namedRanges);

	// Text/Range conversion
	static BOOL __cdecl TextToRange(LPCTSTR strRange, CGXRange& rg);
	static LPCTSTR __cdecl RangeToText(const CGXRange& rg, LPTSTR buffer, int nSize, BOOL bForceRange = FALSE);

	// Manual evaluation of formulas
	virtual BOOL EvaluateExpression(CString& sResult, LPCTSTR pszFormula);
	virtual BOOL EvaluateExpression(CString& sResult, CGXFormula& fm);
	virtual BOOL ParseExpression(LPCTSTR pszFormula, CGXFormula& fm);

// Implementation
public:
	virtual int GetCellText(gxCell* cp, CString& sText);
	virtual int GetExpression(gxCell* cp, CString& sText);

	virtual CObject* GetAdvancedUndoInfo();
	virtual BOOL UndoAdvanced(CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells);
	virtual BOOL SetAdvancedUndo(BOOL b);

	void CheckAdvancedUndo(BOOL bClearDest, BOOL bToolCells);
	BOOL SetPreserveCells(BOOL b);

// Attributes
public:
	WORD m_bsConstraint;	// Base Style id for constraint violation
	int m_nSheetContext;	// sheet index (see GX_ENGINE_STATE::m_apSheetContext)
protected:
	BOOL m_bAdvancedUndoInfo;
	CGXUndoEngineCellsInfo* m_pAdvUndoInfo;
};

class CGXFormula
{
public:
	CGXFormula();
	virtual ~CGXFormula();

	gxFormula* pfm;
};

class CGXWorksheetFunctions: public CObject
{										   
public:
	CGXWorksheetFunctions();

	virtual gxKeyword* LookupFunction(LPCTSTR text) = 0;
		// Override this methode in your derived class and 
		// return Lookup(text, fn_table, sizeof(fn_table)); 
		// (see CGXAllWorksheetFunctions::Lookup as an example)
	
	// Helper routine for lookup in a gived keyword table 
	static gxKeyword* __cdecl Lookup(LPCTSTR text, gxKeyword* fn_table, int sizeofTable);

	// Helper routine for sorting the table
	static void __cdecl SortTable(gxKeyword* fn_table, int sizeofTable);
};

class CGXDefaultWorksheetFunctions: public CGXWorksheetFunctions
{										   
public:
	// Constructor
	CGXDefaultWorksheetFunctions();

	// Lookup
	virtual gxKeyword* LookupFunction(LPCTSTR text);

	// Attributes (keyword table table)
	static gxKeyword fn_table[];
	static int fn_table_size;
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES

GX_INLINE BOOL CGXFormulaSheet::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, GXModifyType mt, int nType)
{
	return StoreStyleRowCol(nRow, nCol, &style, mt, nType);
}

// #include "grid\gxstyles.inl"
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


#endif //_GXENGINE_H_
