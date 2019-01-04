// This is a part of the Objective Grid Pro C++ Library.
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
// Author: Daniel Jebaraj
//

#ifndef _GX_EXTBL_H__
#define _GX_EXTBL_H__

#ifndef _GX_EX_HLP_H__
#include "grid\gxexhlp.h"
#endif //_GX_EX_HLP_H__


//
// GridMFC Extension DLL
// initialize declaration context
//

#if	defined(_GXDLL) && !defined(_GXNOEXTSTATE) 
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#ifndef _GX_EX_TBL_RECSIZE_H__
#include "grid\gxexdef.h"
#endif //_GX_EX_TBL_RECSIZE_H__


// declaration for all classes managing tables in the Excel file

// This is the base class for reading and holding table structures
class CGXExcelTable : public CObject
{
	DECLARE_DYNAMIC(CGXExcelTable)
public:
	CGXExcelTable();
	virtual ~CGXExcelTable();

	// operations
	// Read/Write from/to stream
	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength) = 0;
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1) = 0;
	
	virtual DWORD GetTableSize() = 0;
	
	virtual void ResetInternalState() = 0;

	// logging support
	virtual void LogText(const TCHAR* pszText);
	virtual void LogNumber(int nNum, BOOL bTerminate = FALSE);
	virtual void LogXNumber(int nNum, BOOL bTerminate = FALSE);
	
	// continue record support
	// this is used for dealing with continue records
	DWORD GetRecordOffset() const;
	void SetRecordOffset(DWORD dw, BOOL bInc = TRUE );
	void ResetRecordOffset();

	DWORD GetRecordLength() const;
	void SetRecordLength(DWORD dw);

	// statics
	static CGXExcelLogger* GetLogger();
	static void SetCanLog(BOOL bCanLog);
	
	static BOOL GetOptimizedMode();
	static void SetOptimizedMode(BOOL b);

	static CGXExcelLogger* s_pLogger;

protected:
	// data
	static BOOL m_bCanLog;
	static BOOL m_bOptimized;
	// for continue record support
	DWORD m_dwRecordOffset;
	DWORD m_dwRecordLength;
};


// CGXExcelFontTable
struct fontStruct
{
	// construction
	fontStruct();
	~fontStruct();

	WORD dyHeight;//2
	WORD grbit;//2
	WORD icv;//2
	WORD bls;//2
	WORD sss;//2
	BYTE uls;//1
	BYTE bFamily;//1
	BYTE bCharSet;//1
	BYTE bReserved;//1
	BYTE cch;//1
	BYTE grbit1;
	WCHAR* pszFontName;//var
	
	void Cleanup();
};

// This class should never be constructed and is only used as 
// a default template argument
class _cgxNullClass
{
public:
	_cgxNullClass();
	~_cgxNullClass();
};

template<class T, class T1 = _cgxNullClass>
class CGXExcelBaseTable : public CGXExcelTable
{
	DECLARE_DYNAMIC(CGXExcelBaseTable)

public:
	typedef CGXExcelBaseTable _base;

	CGXExcelBaseTable()
	{
		ResetInternalState();
	};
	
	virtual ~CGXExcelBaseTable()
	{
		ResetInternalState();
	};

	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength) = 0;
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs) = 0;
	virtual DWORD GetTableSize();
	
	virtual BOOL ApplyToObject(DWORD index, T1*& p);

	T1* CreateTableObject()
	{return (T1*)gs_TableObjectManager.CreateObject();};
	
	void RecycleObject(T1* pObject)
	{gs_TableObjectManager.RecycleObject(pObject);};

	BOOL IsIndexValid(DWORD index)
	{return index <= m_dwIndex;};

	virtual void ResetInternalState();

protected:
	virtual BOOL LookupValue(DWORD index, T*& pT);

// implementation
	CMap<DWORD, DWORD&, T*, T*&> m_mapStruct;
	DWORD m_dwIndex;

	CGXCaptiveManager<T1> gs_TableObjectManager;
};


struct CGXExcelFontIndex
{
	GXBYTE8 byte8;
	COLORREF colorIndex;
	UINT nTabIndex;

	CGXExcelFontIndex(){
		this->byte8 = 0;
		this->colorIndex = 0;
		this->nTabIndex = 0xFFFF;
	}

	CGXExcelFontIndex(const CGXExcelFontIndex& fontIndex){
		this->byte8 = fontIndex.byte8;
		this->colorIndex = fontIndex.colorIndex;
		this->nTabIndex = fontIndex.nTabIndex;
	}

	
	CGXExcelFontIndex(GXBYTE8 _byte8, COLORREF _colorIndex, UINT _nTabIndex = 0xFFFF){
		this->byte8 = _byte8;
		this->colorIndex = _colorIndex;
		this->nTabIndex = _nTabIndex;
	}

	CGXExcelFontIndex& operator = (const CGXExcelFontIndex& fontIndex){
		this->byte8 = fontIndex.byte8;
		this->colorIndex = fontIndex.colorIndex;
		this->nTabIndex = fontIndex.nTabIndex;
	
		return *this;
	}
	
	bool operator == (const CGXExcelFontIndex& fontIndex) const{
		return (this->byte8 == fontIndex.byte8 
			&& this->colorIndex == fontIndex.colorIndex
			&& this->nTabIndex == fontIndex.nTabIndex);
	}

	bool operator != (const CGXExcelFontIndex& fontIndex) const{
		return !(*this == fontIndex);
	}
};

template<>
UINT AFXAPI HashKey(const CGXExcelFontIndex& key);

class CGXExcelFontTable : public CGXExcelBaseTable<fontStruct, CGXStyle>
{
	DECLARE_DYNCREATE(CGXExcelFontTable)

public:
	CGXExcelFontTable();
	virtual ~CGXExcelFontTable();

	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	virtual BOOL ApplyToObject(DWORD index, CGXStyle*& pStyleFont);

	// does a lookup and returns the index of the font in the font table
	UINT GetFontIndex(const CGXExcelFontIndex& b) const;
	void SetFontIndex(const CGXExcelFontIndex&  b, UINT index);
	BOOL IsInitFontIndex(const CGXExcelFontIndex&  b);

	virtual WORD TranslateFontToFontEntry(CGXFont& font, BYTE* pszBuffer, const CGXStyle* pStyle);

	
	virtual BOOL WriteFontPtrArray( CGXStylePtrArray* pStylePtrArray,
									IStream* pStream, 
									DWORD& dwLength, 
									UINT& nFontIndex,
									const CGXStylesMap* pStylesMap,
									const CGXStyle* pStyleStandard, UINT nTabIndex = 0);

	virtual BOOL WriteFormulaFont(int nR, int nCol, IStream* pStream, const CGXStyle*  pStandard,
									const CGXStylesMap* pStylesMap, const CGXStyle* pStyle, DWORD& dwLength, UINT& nFontIndex);

protected:
	virtual void ResetInternalState();
	
	//data
	CMap<CGXExcelFontIndex, const CGXExcelFontIndex&, UINT, UINT&> m_mpHashToIndex;
};


// CGXExcelColorTable

struct colorStruct
{
	// construction
	colorStruct();
	~colorStruct();
	
	// data
	WORD	num; // size 2: number of entries
	COLORREF* dwValues;

	void Cleanup();
};


class CGXExcelColorTable : public CGXExcelBaseTable<colorStruct, CGXStyle>
{
	DECLARE_DYNCREATE(CGXExcelColorTable)

	enum gxWriteMode
	{	
		gxRead = 0x1,
		gxWrite = 0x2,
	};

public:
	CGXExcelColorTable();
	virtual ~CGXExcelColorTable();

	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);
	virtual COLORREF GetColorAtPalIndex(DWORD index, COLORREF defColor = GX_INVALID);

	// write support
	virtual BOOL WriteColorTablePtrArray(CGXStylePtrArray* pStylePtrArray, UINT& nColorIndex);
	virtual void WriteStyleColorInfo(const CGXStyle* pStyle, UINT& nColorIndex);
	
	//access
	void SetColorWriteIndex(COLORREF ref, UINT& index);
	UINT GetColorWriteIndex(COLORREF ref) const;

	void SetWriteMode(short b);
	short GetWriteMode();

	// This is a special case does not support apply to object mainly because
	// the color can be used in a wide variety of contexts. It is upto the calling
	// object to consider the correct context and apply the color
	// UserGetColorAtPalIndex for this purpose
	virtual BOOL ApplyToObject(DWORD index, CGXStyle*& p);

protected:
	// writing support
	CMap<COLORREF, COLORREF&, UINT, UINT&> m_mpColorToIndex;
	short m_gxWriteMode;
};


// CGXExcelStyleTable

struct styleStruct
{
	styleStruct();
	~styleStruct();
	
	// data
	WORD	ixfe; //2
	BYTE 	istyBuiltIn; //1
	BYTE	iLevel; //1
	
	WORD	cch; //2
	TCHAR* pVarChar;
	
	WORD wID;

	void Cleanup();
};

class CGXExcelStyleTable : public CGXExcelBaseTable<styleStruct, CGXStyle>
{
	DECLARE_DYNCREATE(CGXExcelStyleTable)

public:
	CGXExcelStyleTable();
	virtual ~CGXExcelStyleTable();

	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	virtual BOOL CheckIfUserDefined(const CWordArray& arr, WORD index);
	virtual WORD GetBaseStyleID(DWORD index);
};


//CGXExcelXFTable
struct XFStruct
{
	WORD	ifnt;
	WORD	ifmt;	
	WORD	fLocked;	
	WORD	alc;
	WORD	cIndent;
	WORD	dgLeft;
	WORD	icvLeft;
	DWORD	icvTop;
	WORD	icvFore;
	
	void Cleanup();
};

class CGXXFArray : public CGXExStyleMap
{
public:
	CGXXFArray();
	virtual ~CGXXFArray();
	virtual void Destroy();
};

struct CGXXFArrayCreator :public CGXCreator<CGXXFArray>
{
	virtual CGXXFArray* CreateObject();
};

typedef CGXNodeManagerNor<CGXXFArray> CGXXFArrayManager;

class CGXExcelXFTable : public CGXExcelBaseTable<XFStruct, CGXStyle>
{
	enum gxRowColType
	{
		gxRowColRow,
		gxRowColCol,
		gxRowCol,
	};

	DECLARE_DYNCREATE(CGXExcelXFTable)

	typedef  CGXExcelBaseTable<XFStruct> _baseClass;

public:
	CGXExcelXFTable();
	virtual ~CGXExcelXFTable();

	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);
	virtual BOOL ApplyToObject(DWORD index, CGXStyle*& pStyle);
	
	BOOL StyleHelper(XFStruct* pXFStruct, CGXStyle* pStyle);
	BOOL CellHelper(XFStruct* pXFStruct, CGXStyle* pStyle);

	//access
	CGXExStyleMap& GetExcelStyleMap(UINT index);
	CGXExStyleIDMap& GetExcelBStyleMap();
	
	// these functions are to be used only when reading/writing sheet data
	// never for global data
	ROWCOL GetCurrentReadCol();
	ROWCOL GetCurrentReadRow();
	UINT GetCurrentReadIndex();
	
	void SetCurrentReadCol(ROWCOL nCol);
	void SetCurrentReadRow(ROWCOL nRow);
	void SetCurrentReadIndex(UINT nIndex);


protected:
	virtual void ResetInternalState();

	virtual int TranslatePattern(int index, BOOL bToGrid = TRUE);
	
	virtual void TranslateStyleToXF(const CGXStyle* pStyle, BYTE* pszBuffer, BOOL bStyle = TRUE, const CGXStylesMap* pStylesMap = NULL, BOOL bStandardStyle = FALSE, UINT nTab = 0xffff);
	virtual void TranslateStyleToStyleXF(const CGXStyle* pStyle, BYTE* pszBuffer, const CGXStylesMap* pStylesMap);
	virtual void TranslateStyleToCellXF(const CGXStyle* pStyle, BYTE* pszBuffer, const CGXStylesMap* pStylesMap = NULL, BOOL bStandard = FALSE, UINT nTab = 0xffff);

	virtual BOOL WriteStylePtrArray(     CGXStylePtrArray* pStylePtrArray, IStream* pStream, 
										 DWORD& dwLength, 
										 gxRowColType type,
										 ROWCOL nRC,
										 UINT& nStyleIndex,
										 const CGXStyle* pStandardStyle,
										 UINT nC,
										 const CGXStylesMap* pStylesMap = NULL,
										 BOOL bStyle = TRUE
								   );

	virtual BOOL WriteComposedStylePtrArray(CGXStylePtrArray* pStylePtrArray, IStream* pStream, 
										 DWORD& dwLength, 
										 gxRowColType type,
										 ROWCOL nRC,
										 UINT& nStyleIndex,
										 const CGXStyle* pStandardStyle,
										 UINT nC,
										 const CGXStylesMap* pStylesMap = NULL,
										 BOOL bStyle = TRUE,
										 CGXStylePtrArray* pColStylePtrArray = NULL,
										 CGXStylePtrArray* pRowStylePtrArray = NULL						
								   );


	virtual BOOL WriteFormulaStyle(int nR, int nCol, IStream* pStream, const CGXStylesMap* pStylesMap, const CGXStyle* pStyle, DWORD& dwLength, UINT& nStyleIndex, UINT nC);

	virtual BOOL SetPenStyle(WORD wStyle, CGXPen& pen);
	WORD GetPenStyle(CGXPen& pen);
	
	virtual WORD GetDefaultExcelBorder();
	virtual WORD GetDefaultExcelBorderColor();

	// data
	//CGXExStyleMap m_mpStyleMap;
	CGXExStyleIDMap m_mpStyleIDMap;
	CArray<int, int> m_ArrPattern;
	CGXXFArrayManager* m_pArManager;
	
	ROWCOL m_iCurRow;
	ROWCOL m_iCurCol;
	UINT m_uinTab;
};


struct formatStruct
{
	WORD	ifmt;
	BYTE	cch;	
	TCHAR*	pVarFormat;

	void Cleanup();
};

// class CGXExcelFormatTable
class CGXExcelFormatTable : public CGXExcelBaseTable<formatStruct, CGXStyle>
{
	DECLARE_DYNCREATE(CGXExcelFormatTable)

	typedef  CGXExcelBaseTable<formatStruct> _baseClass;

public:
	CGXExcelFormatTable();
	virtual ~CGXExcelFormatTable();

	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);
	virtual BOOL ApplyToObject(DWORD index, CGXStyle*& pStyle);

	virtual COLORREF GetDefaultNegativeStateColor();
	virtual WORD GetExcelIndexForWrite(const CGXStyle* pStyle);
};


struct _sst
{
	// construction
	_sst();
	~_sst();

	// data
	WORD cch;
	BYTE grbit;
	WCHAR* pszValue;
	
	WORD wRuns;

	void Cleanup();
};

// sstStruct
struct sstStruct
{
	sstStruct();
	~sstStruct();
	
	DWORD	cstTotal;
	DWORD	cstUnique;	
	_sst*	pStrings;

	void Cleanup();
};

class CGXExcelSSTTable : public CGXExcelBaseTable<sstStruct, CGXStyle>
{
	DECLARE_DYNCREATE(CGXExcelSSTTable)

public:
	CGXExcelSSTTable();
	virtual ~CGXExcelSSTTable();

	virtual BOOL ReadFromStream(IStream* pStream, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	virtual BOOL ApplyToObject(DWORD index, CGXStyle*& pStyle);
};


// CGXExcelBoundSheetTable

struct BoundSheetStruct
{
	BoundSheetStruct();
		
	DWORD dwOffsetPos;
	WORD grbit;
	WORD cch;
	TCHAR* pszName;
		
	void Cleanup();
} ;

class CGXExcelBoundSheetTable : public CGXExcelBaseTable<BoundSheetStruct, CString>
{
	DECLARE_DYNCREATE(CGXExcelBoundSheetTable)

	typedef CArray<DWORD, DWORD&> CGXExOffsetArray;

public:
	// construction
	CGXExcelBoundSheetTable();
	virtual ~CGXExcelBoundSheetTable();

	virtual BOOL ReadFromStream(IStream* pStream,DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	virtual BOOL ApplyToObject(DWORD index, CString*& pStrName);
	virtual void ResetInternalState();

	// access
	CGXExOffsetArray* GetBOFOffsetArray();
	DWORD GetOffsetPos() const;
	void  SetOffsetPos(DWORD dw);

	BOOL GetSeekMode() const;
	void  SetSeekMode(BOOL b);

	BoundSheetStruct* LookupOffsetStruct(DWORD index);
protected:
	CArray<DWORD, DWORD&> m_ArOffsetPos;
	DWORD m_dwOffsetPos;
	BOOL m_bSeekMode;
};


struct sfStruct
{
	sfStruct();

	WORD rwFirst;
	WORD rwLast;
	BYTE colFirst;
	BYTE colLast;
	WORD cce;
	BYTE* pVar;

	static DWORD GetFixedSize()
	{
		return (3*sizeof(WORD) + 2*sizeof(BYTE));
	}
	
	void Cleanup();
};



class CGXExcelSharedFormulaTable : public CGXExcelBaseTable<sfStruct, formulaStruct>
{
	DECLARE_DYNCREATE(CGXExcelSharedFormulaTable)

public:
	// construction
	CGXExcelSharedFormulaTable();
	virtual ~CGXExcelSharedFormulaTable();

	virtual BOOL ReadFromStream(IStream* pStream,DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs = 1);

	virtual BOOL ApplyToObject(DWORD index, formulaStruct*& pFS);
	virtual void ResetInternalState();

	DWORD GetCompositeIndex(WORD nRow, WORD nCol);

	// interface
	virtual BOOL LookupSharedFormula(WORD nRow, WORD nCol);
	BOOL ApplyToObject(WORD nRow, WORD nCol, formulaStruct*& pFS);
};


//
// GridMFC extension DLL
// reset declaration context
//

#if !defined(_GXNOEXTSTATE) 
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif //_GX_EXTBL_H__
