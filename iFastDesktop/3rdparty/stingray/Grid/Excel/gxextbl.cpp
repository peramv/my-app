///////////////////////////////////////////////////////////////////////////////
// gxextbl.cpp
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Daniel Jebaraj
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"
#include "grid\gxexman.h"
#include "grid\gxexlog.h"
#include "grid\gxexmac.h"
#include "grid\gxexhdr.h"
#include "grid\gxexhnd.h"
#include "grid\gxexmap.h"
#include "grid\gxextbl.h"
#include "grid\gxexhlp.h"
#include "grid\gxexdef.h"
#include "grid\gxexmpst.h"
#include "grid\gxexfmrd.h"

#pragma warning(disable: 4244 4239 4267 4311 4312 4189)

CGXExcelLogger* CGXExcelTable::s_pLogger = NULL;

BOOL CGXExcelTable::m_bCanLog = FALSE;
BOOL CGXExcelTable::m_bOptimized = FALSE;

IMPLEMENT_DYNAMIC(CGXExcelTable, CObject)


GXEXIMPLEMENT_DYNAMIC(CGXExcelBaseTable, CGXExcelTable, T, T1)
GXEXIMPLEMENT_DYNCREATE(CGXExcelFontTable, CGXExcelBaseTable, fontStruct, CGXFont)
GXEXIMPLEMENT_DYNCREATE(CGXExcelStyleTable, CGXExcelBaseTable, styleStruct, CGXStyle)
GXEXIMPLEMENT_DYNCREATE(CGXExcelXFTable, CGXExcelBaseTable, XFStruct, CGXStyle)
GXEXIMPLEMENT_DYNCREATE(CGXExcelColorTable, CGXExcelBaseTable, colorStruct, _cgxNullClass)
GXEXIMPLEMENT_DYNCREATE(CGXExcelFormatTable, CGXExcelBaseTable, formatStruct, CGXStyle)
GXEXIMPLEMENT_DYNCREATE(CGXExcelSSTTable, CGXExcelBaseTable, sstStruct, CGXStyle)
GXEXIMPLEMENT_DYNCREATE(CGXExcelBoundSheetTable, CGXExcelBaseTable, BoundSheetStruct, CString)
GXEXIMPLEMENT_DYNCREATE(CGXExcelSharedFormulaTable, CGXExcelBaseTable, sfStruct, formulaStruct)



// base class for all tables
// CGXExcelTable implementation

CGXExcelTable::CGXExcelTable()
{
	m_dwRecordOffset = 0;
	m_dwRecordLength = 0;
}

CGXExcelTable::~CGXExcelTable()
{
	// no implementation
}

DWORD CGXExcelTable::GetRecordOffset() const
{
	return m_dwRecordOffset;
}

void CGXExcelTable::SetRecordOffset(DWORD dw, BOOL bInc /* = TRUE */)
{
	// bInc indicates an increment rather than a set
	if(bInc == FALSE)
		m_dwRecordOffset = dw;
	else
		m_dwRecordOffset += dw;
}
	
void CGXExcelTable::ResetRecordOffset()
{
	m_dwRecordOffset = 0;
}

DWORD CGXExcelTable::GetRecordLength() const
{
	return m_dwRecordLength;
}

void CGXExcelTable::SetRecordLength(DWORD dw)
{
	m_dwRecordLength = dw;
}


void CGXExcelTable::LogText(const TCHAR* pszText)
{
	if(s_pLogger && m_bCanLog)
		s_pLogger->LogText(pszText);
}

void CGXExcelTable::LogNumber(int nNum, BOOL bTerminate /*= FALSE*/)
{
	if(s_pLogger && m_bCanLog)
		s_pLogger->LogNumber(nNum, bTerminate);
}

void CGXExcelTable::LogXNumber(int nNum, BOOL bTerminate /*= FALSE*/)
{
	if(s_pLogger && m_bCanLog)
		s_pLogger->LogXNumber(nNum, bTerminate);
}

CGXExcelLogger* CGXExcelTable::GetLogger()
{
	return s_pLogger;
}
	
void CGXExcelTable::SetCanLog(BOOL bCanLog)
{
	m_bCanLog = bCanLog;
}

BOOL CGXExcelTable::GetOptimizedMode()
{
	return m_bOptimized;
}
	
void CGXExcelTable::SetOptimizedMode(BOOL b)
{
	m_bOptimized = b;
}

// Base implementation for tables. This provides for table memory management as 
// well as for Table iteration
template<class T, class T1>
void CGXExcelBaseTable<T, T1>::ResetInternalState()
{
	//iterate through the CMap and free memory	
	m_dwIndex = 0;
	
	POSITION pos = m_mapStruct.GetStartPosition();

	T* pStruct = NULL;
	DWORD dw = 0;

	while (pos!=NULL)
	{
		m_mapStruct.GetNextAssoc(pos, dw, pStruct);
		
		if(pStruct)
		{
			// the structures can clean up themselves
			pStruct->Cleanup();
			delete pStruct;
		}
	};
	
	m_mapStruct.RemoveAll();

}

template<class T, class T1>
DWORD CGXExcelBaseTable<T, T1>::GetTableSize()
{
	return m_mapStruct.GetCount();
}

template<class T, class T1>
BOOL CGXExcelBaseTable<T, T1>::LookupValue(DWORD index, T*& pT)
{
	if(index > m_dwIndex)
		return FALSE;

	if(!m_mapStruct.Lookup(index, pT))
		return FALSE;

	ASSERT(pT != NULL);

	if(pT == NULL)
		return FALSE;
	else
		return TRUE;
}

// each of these tables can given an index change an object of one type. This type
// is passed in as one of the template arguments during instantiation and is the
// most basic object on which this table can operate. Other higher level objects 
// will have to get initialized passing in an object of this type
template<class T, class T1>
BOOL CGXExcelBaseTable<T, T1>::ApplyToObject(DWORD /*index*/, T1*& p)
{
	if(p == NULL)
		p = CreateTableObject();
	
	return p!=NULL;
}

// _cgxNullClass
// should never be actually constructed
_cgxNullClass::_cgxNullClass()
{
	ASSERT(0);
}

_cgxNullClass::~_cgxNullClass()
{
	// no implementation
}

// for use by CGXExcelFontTable
// struct fontStruct

fontStruct::fontStruct()
{
	pszFontName = NULL;
}

fontStruct::~fontStruct()
{
	// no implementation
}
	
void fontStruct::Cleanup()
{
	if(pszFontName != NULL)
		delete[] pszFontName;
}


// CGXExcelFontTable implementation
CGXExcelFontTable::CGXExcelFontTable()
{
	// no implementation
}

CGXExcelFontTable::~CGXExcelFontTable()
{
	// no implementation
}	

// The font handler reuses the font table and releases it only when destroyed
/*
FONT: Font Description (231h)
The workbook font table contains at least five FONT records. FONT records are numbered as follows: ifnt = 00h 
(the first FONT record in the table), ifnt = 01h, ifnt = 02h, ifnt = 03h, ifnt = 05h (minimum table), and then
ifnt = 06h, ifnt = 07h, and so on. Notice that ifnt = 04h never appears in a BIFF file. This is for 
backward-compatibility with previous versions of Microsoft Excel.
*/

BOOL CGXExcelFontTable::ReadFromStream(IStream* pStream, DWORD /*dwLength*/)
{
	fontStruct* pFontStruct = new fontStruct;	

	
	static GXREADSEEKDATA readData[12];

	// phase 1
	readData[0].Init(&pFontStruct->dyHeight);
	readData[1].Init(&pFontStruct->grbit);
	readData[2].Init(&pFontStruct->icv); 
	readData[3].Init(&pFontStruct->bls); 
	readData[4].Init(&pFontStruct->sss); 
	readData[5].Init(&pFontStruct->uls); 
	readData[6].Init(&pFontStruct->bFamily); 
	readData[7].Init(&pFontStruct->bCharSet); 
	readData[8].Init(&pFontStruct->bReserved);
	readData[9].Init(&pFontStruct->cch); 
	readData[10].Init(&pFontStruct->grbit1); 

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 11))

	//
	// This change does not appear to be documented under fonts
	// check grbit to see if these are compressed
	if( (pFontStruct->grbit1 & 0x01) == 0)
	{
		BYTE* pszTemp = new BYTE[pFontStruct->cch];
		readData[11].Init( (BYTE*)pszTemp, pFontStruct->cch*sizeof(BYTE), gxread); // read the array of bytes
			
		// read the data
		GXEX_TRY(ReadSeekHelper(pStream, &readData[11], 1));

		// expand to a UNICODE string
		pFontStruct->pszFontName = _gxexExpandToUnicode(pszTemp, pFontStruct->cch);

		if(pszTemp)
			delete[] pszTemp;
			
			pszTemp = NULL;
		}
	else
	{
		// This is an uncompressed UNICODE string
		pFontStruct->pszFontName = new WCHAR[pFontStruct->cch];
		readData[11].Init( (BYTE*)pFontStruct->pszFontName, pFontStruct->cch*sizeof(WCHAR), gxread); // read the array of bytes
			
		// read the data
		GXEX_TRY(ReadSeekHelper(pStream, &readData[11], 1));
	}
	//
		
	m_mapStruct.SetAt(m_dwIndex, pFontStruct);
	
	++m_dwIndex;

	return TRUE;
}

BOOL CGXExcelFontTable::WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs)
{
	HRESULT hr(S_OK);
	
	// The font table is global with Excel unlike with Objective Grid where it depends on CGXData as well as the
	// styles map object. In this function we build and write out the global table
	
	// Iterate through all the fonts that we have in the grid and build the table
	ASSERT(pParam != NULL);

	if(pParam == NULL)
		throw egxInvalidParam;

	// CGXStylesMap styles
	ASSERT(*pParam != NULL);
	
	if(*pParam == NULL)
		throw egxInvalidParam;

	CGXStylesMap* pStylesMap = (*pParam)->GetStylesMap();
	
	ASSERT(pStylesMap != NULL);

	if(pStylesMap == NULL)
		throw egxInvalidStylesMap;
	
	// general variables
	UINT nFontIndex(0); // for the font index in the table
	BYTE pszBuffer[GX_EX_MAXFONTRECSIZE]; // we assume upper limit for the size of the variable record since the 
	memset(pszBuffer, 0, GX_EX_MAXFONTRECSIZE);
	
	// font name can be thought to have a resonable maximum size
	ULONG cb(0);

	CGXStyle* pStandard = NULL;
	pStylesMap->LookupStyle(pStylesMap->m_wStyleStandard, pStandard);
	
	// write the standard style font (the Normal Font)
	if(pStandard->GetIncludeFont())
	{
		WORD nLength = TranslateFontToFontEntry(pStandard->GetFont(), pszBuffer + 4, pStandard);
		
		if(nLength)
		{
			for (UINT ui(0); ui < 5; ui++)
			{
				if( 
					!IsInitFontIndex( CGXExcelFontIndex(pStandard->GetFont().GetFontKey(), pStandard->GetIncludeTextColor()?pStandard->GetTextColor():0))
					
					)
				{
					SetFontIndex( CGXExcelFontIndex(pStandard->GetFont().GetFontKey(), pStandard->GetIncludeTextColor()?pStandard->GetTextColor():0), nFontIndex);
				}
				
				if(nFontIndex !=3)
					nFontIndex++;
				else
					nFontIndex+=2;

				// write the standard style's font 5 times
				_gxExWriteWord(pszBuffer, typeFont);
				_gxExWriteWord(pszBuffer + 2, nLength - 4);
			
				GX_EX_WRITE(pStream->Write(pszBuffer, nLength, &cb));
				dwLength+=cb;
			}
		}		
	}
		
	memset(pszBuffer, 0, GX_EX_MAXFONTRECSIZE);

	POSITION pos = pStylesMap->StartStylesIteration();

	WORD wStyleId(0);
	CString strName;
	UINT nResourceID(0);
	const CGXStyle* pStyle = NULL;
	
	while(pos != NULL)
	{
		pStylesMap->GetNextStyle(pos, wStyleId, strName, nResourceID, pStyle);
		if(pStyle->GetIncludeFont())
		{
			CGXStyle* p = pStyle->Clone();
			// standard style
			p->ChangeStyle(*pStandard, gxApplyNew);
		
			WORD nLength = TranslateFontToFontEntry(p->GetFont(), pszBuffer + 4, p);
			
			if(nLength && (wStyleId != pStylesMap->m_wStyleStandard))
			{
				// add to our map
				if( 
					!IsInitFontIndex(CGXExcelFontIndex(pStyle->GetFont().GetFontKey(), pStyle->GetIncludeTextColor()?pStyle->GetTextColor():0)) 
					)
				{
					SetFontIndex( CGXExcelFontIndex(pStyle->GetFont().GetFontKey(), pStyle->GetIncludeTextColor()?pStyle->GetTextColor():0), nFontIndex);
					
					if(nFontIndex == 3)
						nFontIndex+=2;
					else
						nFontIndex++;
				}
				else
				{
					if(p)
						delete p;
					continue;
				}

				_gxExWriteWord(pszBuffer, typeFont);
				_gxExWriteWord(pszBuffer + 2, nLength - 4);
			
				GX_EX_WRITE(pStream->Write(pszBuffer, nLength, &cb));
				dwLength+=cb;

				TRACE0("Font information\n");
				// afxDump.HexDump( ".", (BYTE*) pszBuffer, nLength, nLength );

				memset(pszBuffer, 0, GX_EX_MAXFONTRECSIZE);

				//nFontIndex++;
			}

			if(p)
				delete p;
		}
	}

	// write out the other fonts

	CGXData* pData = NULL;
	_accData* pD  = NULL;

	CGXStylePtrArray* pRowStyles = NULL;
	CGXStylePtrArray* pColStyle = NULL;
	CGXStylePtrArrayPtrArray* pStylePtrAr = NULL;

	// Iterate through all the other styles
	CGXGridParam* pPa = pParam[0]; 
	for(ROWCOL nC(0); nC < nTabs; nC++)
	{
		pData = pPa->GetData();
		
		ASSERT(pData != NULL);
		
		pD  = (_accData*)pData;

	
		pRowStyles = &(pD->m_apRowBaseStyle);// row base styles
	
		WriteFontPtrArray(pRowStyles, pStream, 
								   dwLength, 
								   nFontIndex,
								   pStylesMap,
								   pStandard,
								   nC
								   );

		pColStyle = &pD->m_apColBaseStyle;// column base styles

	
		WriteFontPtrArray(pColStyle, pStream, 
								   dwLength, 
								   nFontIndex,
								   pStylesMap,
								   pStandard,
								   nC
								   );

	
		pStylePtrAr =  &pD->m_apapCellStyle; // spans the cell matrix,
												// CGXStylePtrArray elements are rows
												// which CGXStyle elements are styles
	
	
	
		if(pData->IsKindOf(RUNTIME_CLASS(CGXFormulaSheet)))
		{
			CGXFormulaSheet* pSheet = (CGXFormulaSheet*)pData;
			
			ASSERT(pSheet != NULL);
			// get the iteration limits
			int nOUpperBound(0);
			int nIUpperBound(0);
	
			int sIndex = pSheet->m_nSheetContext;
			// get the upper bound from the formula sheet
			gxRange gxR;
			_gx_init_range(&gxR);
#ifdef _DEBUG
			_gx_get_sheet_extent(sIndex, &gxR);
#else
			_gx_get_sheet_extent(sIndex, &gxR);
#endif
			nOUpperBound = pSheet->GetGridRow(gxR.r1) + 1;
			nIUpperBound = pSheet->GetGridCol(gxR.c1) + 1;
		
			CGXStyle* pStyle = NULL;
			
			pStyle = new CGXStyle;

			ASSERT(pStyle != NULL);

			for (int nR(1); nR < nOUpperBound; nR++)
			{
				for (int nCol = 1;  nCol < nIUpperBound; nCol++)
				{
					pStyle->Free();
					
					gxCell *cp = NULL;
					cp = _gx_find_cell(sIndex, pSheet->GetEngineRow(nR), pSheet->GetEngineCol(nCol));
					
					if (cp && cp->pStyle)
					{
						pStyle->ChangeStyle(*cp->pStyle, gxCopy);
					
						if(pStyle->GetIncludeFont())
							WriteFormulaFont(nR, nCol, pStream,  pStandard, pStylesMap, pStyle, dwLength, nFontIndex);
					}
				}
			}
		
			if(pStyle != NULL)
				delete pStyle;
		}
		else
		{
			CGXStylePtrArray* pStyleDataPtrAr = NULL;

			int nRMax = pStylePtrAr->GetUpperBound();

			for (int nR(0); nR < nRMax; nR++)
			{	
				
				pStyleDataPtrAr = pStylePtrAr->GetAt(nR);
				
				if(pStyleDataPtrAr != NULL)
					WriteFontPtrArray(pStyleDataPtrAr, pStream, 
									   dwLength, 
									   nFontIndex,
									   pStylesMap,
									   pStandard, nC);
				
				pStyleDataPtrAr = NULL;
			}
		}
		
		pPa = pParam[nC+1];
	}
	
	return TRUE;
}



BOOL CGXExcelFontTable::WriteFormulaFont(int /*nR*/, int /*nCol*/, IStream* pStream, const CGXStyle*  pStyleStandard, const CGXStylesMap* pStylesMap, const CGXStyle* pStyle, DWORD& dwLength, UINT& nFontIndex)
{
	HRESULT hr(S_OK);
	//egxExcelRWFlags flags(egxSuccess);

	ULONG cb(0);

	BYTE pszBuffer[GX_EX_MAXFONTRECSIZE]; // we assume upper limit for the size of the variable record
	memset(pszBuffer, 0, GX_EX_MAXFONTRECSIZE);

	CGXStyle* p = pStyle->Clone();

	// then apply the base style
	if(pStylesMap != NULL  && p->GetIncludeBaseStyle() )
		p->LoadBaseStyle(*pStylesMap);
	
	// standard style
	p->ChangeStyle(*pStyleStandard, gxApplyNew);
		
	WORD nLength = TranslateFontToFontEntry(p->GetFont(), pszBuffer + 4, p);
			
	if(nLength)
	{
				// add to our map
				if( 
					!IsInitFontIndex(CGXExcelFontIndex(p->GetFont().GetFontKey(), p->GetIncludeTextColor()?p->GetTextColor():0))
					)
				{
					SetFontIndex( CGXExcelFontIndex(p->GetFont().GetFontKey(), p->GetIncludeTextColor()?p->GetTextColor():0), nFontIndex);
					nFontIndex++;
				}
				else
				{
					if(p)
						delete p;
					return TRUE;
				}

				_gxExWriteWord(pszBuffer, typeFont);
				_gxExWriteWord(pszBuffer + 2, nLength - 4);
			
				GX_EX_WRITE(pStream->Write(pszBuffer, nLength, &cb));
				
				dwLength+=cb;

				memset(pszBuffer, 0, GX_EX_MAXFONTRECSIZE);
	}

			
	if(p != NULL)
		delete p;

	return TRUE;
}

BOOL CGXExcelFontTable::WriteFontPtrArray(CGXStylePtrArray* pStylePtrArray, IStream* pStream, 
										 DWORD& dwLength, 
										 UINT& nFontIndex,
										 const CGXStylesMap* pStylesMap,
										 const CGXStyle* pStyleStandard,
										 UINT nTabIndex
										 )
{
	HRESULT hr(S_OK);
	//egxExcelRWFlags flags(egxSuccess);

	BYTE pszBuffer[GX_EX_MAXFONTRECSIZE]; // we assume upper limit for the size of the variable record since the 
	memset(pszBuffer, 0, GX_EX_MAXFONTRECSIZE);
	
	const CGXStyle* pStyle = NULL;
	
	ULONG cb(0);

	int nUBound = pStylePtrArray->GetUpperBound();

	for (int nCol = 0; nCol < nUBound; nCol++)
	{
		pStyle = pStylePtrArray->GetAt(nCol);
		
		if(pStyle == NULL)
			continue;
		
		if(pStyle->GetIncludeFont())
		{
			CGXStyle* p = pStyle->Clone();

			// then apply the base style
			if(pStylesMap != NULL  && p->GetIncludeBaseStyle() )
				p->LoadBaseStyle(*pStylesMap);
	
			// standard style
			p->ChangeStyle(*pStyleStandard, gxApplyNew);
		
			WORD nLength = TranslateFontToFontEntry(p->GetFont(), pszBuffer + 4, p);
			
			if(nLength)
			{
				// add to our map
				if( 
					!IsInitFontIndex( CGXExcelFontIndex(p->GetFont().GetFontKey(), p->GetIncludeTextColor()?p->GetTextColor():0, nTabIndex)) 
					)
				{
					SetFontIndex( CGXExcelFontIndex(p->GetFont().GetFontKey(), p->GetIncludeTextColor()?p->GetTextColor():0, nTabIndex), nFontIndex);
					nFontIndex++;
				}
				else
				{
					if(p)
						delete p;
					continue;
				}

				_gxExWriteWord(pszBuffer, typeFont);
				_gxExWriteWord(pszBuffer + 2, nLength - 4);
			
				GX_EX_WRITE(pStream->Write(pszBuffer, nLength, &cb));
				
				dwLength+=cb;

				memset(pszBuffer, 0, GX_EX_MAXFONTRECSIZE);
			}

			
			if(p != NULL)
				delete p;
		}
	}
	
	return TRUE;
}

// build the font entry
WORD CGXExcelFontTable::TranslateFontToFontEntry(CGXFont& font, BYTE* pszBuffer, const CGXStyle* pStyle)
{
	WORD dyHeight(0); WORD grbit(0); WORD icv(0); WORD bls(0); WORD sss(0); BYTE uls(0);
	BYTE bFamily(0); BYTE bCharSet(0); BYTE bReserved(0x0); BYTE cch(0);
	TCHAR* pszFontName = 0; BYTE* psz = pszBuffer;

	// return the actual size of the data since this is a variable field
	const LOGFONT& lf = font.GetLogFontRef();
	
	// the reserved first bit set to zero
	_gxExSetBit(grbit, 0, 0x0);
	
	// for the italic bit
	if(lf.lfItalic == TRUE)
		_gxExSetBit(grbit, 1, 0x1);
	
	// the reserved bit
	_gxExSetBit(grbit, 2, 0x0);

	// the strike out bit
	if(lf.lfStrikeOut == TRUE)
		_gxExSetBit(grbit, 3, 0x1);;

	// ignore outline and shadow

	// set the reserved bit
	_gxExSetBitEx(grbit, 6, 0x00);

	// Leave the unused bit as is

	// for the color palette
	CGXExcelColorTable* pColorTable = (CGXExcelColorTable*) GXExGetTableMap()->LocateHandler(typePalette);
	
	ASSERT(pColorTable != NULL);
	
	COLORREF ref = 0;
	
	if(pStyle->GetIncludeTextColor())
		ref = pStyle->GetTextColor();
	else
		ref = 0x7FFF;

	// start F2
	if(ref != 0 && ref!= 0x7FFF)
		icv = pColorTable->GetColorWriteIndex(ref);
	else
		icv = 0x7FFF;
	// end F2

	// the weight
	bls = (unsigned)lf.lfWeight;
	
	// sss ---> 0x00 is none
	
	// we do not distinguish between the different underlining styles that Excel supports
	uls = lf.lfUnderline;

	bFamily = lf.lfPitchAndFamily;
	
	bCharSet = lf.lfCharSet;
	
	//ignore pFontStruct->bReserved which is already set to zero
	
	// set the length of the facename
	cch = _tcslen(lf.lfFaceName);
	
	if(cch == 0)
		return 0;


	pszFontName = new TCHAR[cch+1];
#ifdef _WIN64 //RW64
	//_tcscpy_s(pszFontName, sizeof(pszFontName), lf.lfFaceName); 
	_tcscpy(pszFontName, lf.lfFaceName);
#else
	_tcscpy(pszFontName, lf.lfFaceName); 
#endif //_WIN64

	// We multiply by 20 since the units are to be in 1/20th of a point
	if(font.GetIncludeSize())
		dyHeight = (unsigned) font.GetSize()*20;

	//dyHeight = 400;
	
	BYTE ngrbit(1);

	BOOL bFreeWChar(FALSE);
	#ifdef _UNICODE
		int nCount = cch;
		const WCHAR* pszW = pszFontName;
	#else 
		int nCount = MultiByteToWideChar(CP_ACP, 0, pszFontName, -1, NULL, NULL);
		ASSERT(nCount);
		WCHAR* pszW = NULL;
		
		pszW = new WCHAR[nCount];
		bFreeWChar = TRUE;
		MultiByteToWideChar(CP_ACP, 0, pszFontName, -1, pszW, nCount);
	#endif
	
	

	// write to the buffer
	_gxdata(wr)
		_gxw(dyHeight) //2
		_gxw(grbit) // 2
		_gxw(icv) // 2
		_gxw(bls) // 2
		_gxw(sss) // 2
		_gxb(uls) // 1
		_gxb(bFamily) // 1
		_gxb(bCharSet) // 1
		_gxb(bReserved) // 1
		_gxb(cch) // 1
		_gxb(ngrbit) // 1
		_gxby(pszW, 2*cch ) // var
	_gxend

	_gxExWrite(wr, psz);
	
	if(pszFontName != NULL)
		delete [] pszFontName;

	if(bFreeWChar && pszW)
	{
		delete pszW;
		pszW = NULL;
		bFreeWChar = FALSE;
	}

	// return the length of the string
	return GX_EX_FONTRECSIZE + 2*cch;
}


UINT CGXExcelFontTable::GetFontIndex(const CGXExcelFontIndex&  b) const
{
	UINT nRetval;
	if(m_mpHashToIndex.Lookup(b, nRetval))
		return nRetval;
	else
		return 0;
}

void CGXExcelFontTable::SetFontIndex(const CGXExcelFontIndex&  b, UINT index)
{
	m_mpHashToIndex.SetAt(b, index);
}

BOOL CGXExcelFontTable::IsInitFontIndex(const CGXExcelFontIndex&  b)
{
	UINT nRetval;
	if(m_mpHashToIndex.Lookup(b, nRetval))
		return TRUE;
	else
		return FALSE;
}

void CGXExcelFontTable::ResetInternalState()
{
	_base::ResetInternalState();
	m_mpHashToIndex.RemoveAll();
}

BOOL CGXExcelFontTable::ApplyToObject(DWORD index, CGXStyle*& pStyleFont)
{
	// will allocate a style object if required
	_base::ApplyToObject(index, pStyleFont);

	fontStruct* pFontStruct = NULL;
	
	if( !LookupValue(index, pFontStruct))
		return FALSE;

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	
	if(pFontStruct->grbit & 0x02)
		lf.lfItalic = 0x01;

	if(pFontStruct->grbit & 0x08)
		lf.lfStrikeOut = 0x01;

	// for the color palette
	CGXExcelColorTable* pColorTable = (CGXExcelColorTable*) GXExGetTableMap()->LocateHandler(typePalette);
	
	ASSERT(pColorTable != NULL);
	
	WORD wIndex = pFontStruct->icv ;

	_gxadjustPalette(wIndex);

	pStyleFont->SetTextColor(pColorTable->GetColorAtPalIndex(wIndex, ::GetSysColor(COLOR_WINDOWTEXT)) );
	
	lf.lfWeight = pFontStruct->bls;
	
	// ignore pFontStruct->sss 
	
	// we do not distinguish between the different underlining styles that Excel supports
	lf.lfUnderline = pFontStruct->uls;

	lf.lfPitchAndFamily = pFontStruct->bFamily;
	
	lf.lfCharSet = pFontStruct->bCharSet;
	
	//ignore pFontStruct->bReserved

#ifndef _UNICODE
	GX_EX_WTMB(pFontStruct->pszFontName, psz, CP_ACP, pFontStruct->cch, "CGXExcelFontTable::ApplyToObject")
	
	if(psz!=NULL)
	{
		memcpy(lf.lfFaceName, psz, pFontStruct->cch); 
		delete [] psz;
	}

#else
		memcpy(lf.lfFaceName, pFontStruct->pszFontName, pFontStruct->cch); 
#endif //!_UNICODE

	CGXFont font;

	font.SetLogFont(lf);
	
	// set the font attributes here
	// we set the font attributes here instead of setting on the LOGFONT to
	// avoid the translations that the grid does when using the LOGFONT
	lf.lfHeight = pFontStruct->dyHeight;
	
	// we divide by 20 since this value is 1/20th of a point and we want the
	// value in points (1/72 of an inch)
	font.SetSize(pFontStruct->dyHeight/20);

	pStyleFont->SetFont(font);

	return TRUE;
}

// struct colorStruct

colorStruct::colorStruct()
{
	dwValues = 0;
}

colorStruct::~colorStruct()
{
	// no implementation
}

void colorStruct::Cleanup()
{
	if (dwValues)
		delete[] dwValues;
}

// CGXExcelColorTable implementation

CGXExcelColorTable::CGXExcelColorTable()
{
	m_gxWriteMode = gxWrite|gxRead;
}
	
CGXExcelColorTable::~CGXExcelColorTable()
{
	// no implementation
}
	
BOOL CGXExcelColorTable::ReadFromStream(IStream* pStream, DWORD /*dwLength*/)
{
	colorStruct* pColorStruct = new colorStruct;	

	static GXREADSEEKDATA readData[2];

	// phase 1
	readData[0].Init(&pColorStruct->num);
	
	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 1))

	pColorStruct->dwValues = new COLORREF[pColorStruct->num];
	
	memset(pColorStruct->dwValues, _T('0'), pColorStruct->num*4);
	
	//DWORD d = pColorStruct->num*4;

	readData[1].Init((TCHAR*)pColorStruct->dwValues, (pColorStruct->num)*4, gxread); //the actual array pointer
	GXEX_TRY(ReadSeekHelper(pStream, &readData[1], 1))
	
#ifdef _DEBUG
	for (DWORD dwDebC = 0; dwDebC < pColorStruct->num; dwDebC++)
		TRACE2("The color are index %d is %x \n", dwDebC, pColorStruct->dwValues[dwDebC]);
#endif
		
		
	m_mapStruct.SetAt(m_dwIndex, pColorStruct);
	
	++m_dwIndex;

	ASSERT(m_dwIndex == 1); //---->Only one color table can be available

	return TRUE;
}

void CGXExcelColorTable::SetWriteMode(short mode)
{
	m_gxWriteMode = mode;
}

short CGXExcelColorTable::GetWriteMode()
{
	return m_gxWriteMode;
}

// This is a special case does not support apply to object mainly because
// the color can be used in a wide variety of contexts. It is upto the calling
// object to consider the correct context and apply the color
// UserGetColorAtPalIndex for this purpose
BOOL CGXExcelColorTable::ApplyToObject(DWORD /*index*/, CGXStyle*& /*p*/)
{
	//ASSERT(0); 
	return FALSE;
}


// default color table
COLORREF g_ref[] = 
{
	0x0,		//0
	0xffffff,	//1 
	0xff,		//2
	0xff00,		//3
	0xff0000,	//4
	0xffff,		//5
	0xff00ff,	//6
	0xffff00,	//7
	0x80,		//8
	0x8000,		//9
	0x800000,	//10
	0x8080,		//11
	0x800080,	//12
	0x808000,	//13
	0xc0c0c0,	//14
	0x808080,	//15
	0xff9999,	//16
	0x663399,	//17
	0xccffff,	//18
	0xffffcc,	//19
	0x660066,	//20
	0x8080ff,	//21
	0xcc6600,	//22
	0xffcccc,	//23
	0x800000,	//24
	0xff00ff,	//25
	0xffff,		//26
	0xffff00,	//27
	0x800080,	//28
	0x80,		//29
	0x808000,	//30
	0xff0000,	//31
	0xffcc00,	//32
	0xffffcc,	//33
	0xccffcc,	//34
	0x99ffff,	//35
	0xffcc99,	//36
	0xcc99ff,	//37
	0xff99cc,	//38
	0xe3e3e3,	//39
	0xff6633,	//40
	0xcccc33,	//41
	0xcc99,		//42
	0xccff,		//43
	0x99ff,		//44
	0x66ff,		//45
	0x996666,	//46
	0x969696,	//47
	0x663300,	//48
	0x669933,	//49
	0x3300,		//50
	0x3333,		//51
	0x3399,		//52
	0x663399,	//53
	0x993333,	//54
	0x333333	//55
};

BOOL CGXExcelColorTable::WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT /*nTabs*/)
{
	HRESULT hr(S_OK);
	
	// Write all the colors that are to be stored
	// The color table is global with Excel unlike with Objective Grid where it depends on CGXData as well as the
	// styles map object. In this function we build and write out the global table
	
	// Iterate through all the colors that we have stored in the grid and build the table
	
	if( GetWriteMode() & CGXExcelColorTable::gxRead )
	{
		ASSERT(pParam != NULL);

		if(pParam == NULL)
			throw egxInvalidParam;
		
		ASSERT(*pParam != NULL);
		
		if(*pParam == NULL)
			throw egxInvalidParam;
			
		CGXStylesMap* pStylesMap = (*pParam)->GetStylesMap();
		
		ASSERT(pStylesMap != NULL);

		if(pStylesMap == NULL)
			throw egxInvalidStylesMap;
		
		// initialize map with default palette data
		for (UINT nColorInit(0) ; nColorInit < GX_EX_NUMPALCOLORS; nColorInit++)
			m_mpColorToIndex.SetAt(g_ref[nColorInit], nColorInit);
	}
	
	if(! (GetWriteMode() & CGXExcelColorTable::gxWrite) )
		return TRUE;
	
	// write out the table to the stream
	UINT nSize = GX_EX_NUMPALCOLORS;
	
	if(nSize == 0)
		return TRUE; // No Palette entry

	
	BYTE* pszBuffer = new BYTE[4 + 2 + nSize*4];
	BYTE* pszRel = pszBuffer;
	memset(pszBuffer, 0, 4 + 2 + nSize*4);

	// write out the header information for the palette
	_gxExWriteWord(pszBuffer, typePalette);
	pszBuffer += 2;
	_gxExWriteWord(pszBuffer, 2 + nSize*4);
	pszBuffer += 2;
	
	_gxExWriteWord(pszBuffer, nSize);
	pszBuffer += 2;

	// iterate through the map and fill the palette entries
	POSITION pos = m_mpColorToIndex.GetStartPosition();
	
	UINT index(0);
	COLORREF ref;
	while(pos != NULL)
	{
		m_mpColorToIndex.GetNextAssoc(pos, ref, index);
		// TRACE1("Index: %u\n", index);
		_gxExWriteDWord(pszBuffer + index * sizeof(COLORREF), ref);
		// TRACE1("Color: %x\n", ref);
	}

	ULONG cb(0);
	GX_EX_WRITE(pStream->Write(pszRel, 4 + 2 + nSize*4, &cb));
	
	dwLength+=cb;

	m_mpColorToIndex.RemoveAll();
	
	if(pszRel != NULL)
		delete [] pszRel;

	// done
	return TRUE;
}


void CGXExcelColorTable::WriteStyleColorInfo(const CGXStyle* pStyle, UINT& nColorIndex)
{
	// check the style
	if(pStyle->GetIncludeTextColor())
		// add to our map
		SetColorWriteIndex(pStyle->GetTextColor(), nColorIndex);
			

	// check the brush (interior)
	if(pStyle->GetIncludeInterior())
	{
		CGXBrush& br = pStyle->GetInterior(); 
		// add to our map
		SetColorWriteIndex(br.GetBkColor(), nColorIndex);
		// pattern color
		SetColorWriteIndex(br.GetColor(), nColorIndex);
	}
			
	// check the pens for the borders

	GXBorderType borders[] = {gxBorderTop, gxBorderLeft, gxBorderBottom, gxBorderRight};
			
	for (UINT n(0) ; n < sizeof(borders) / sizeof(GXBorderType); n++)
	{
		if(pStyle->GetIncludeBorders(borders[n]))
		{	
			CGXPen& pen = pStyle->GetBorders(borders[n]); 
			// add to our map
			SetColorWriteIndex(pen.GetColor(), nColorIndex);
		}	
	}
}


BOOL CGXExcelColorTable::WriteColorTablePtrArray(CGXStylePtrArray* pStylePtrArray, UINT& nColorIndex)
{
	
	CGXStyle* pStyle = NULL;
	
	//ULONG cb(0);

	for (int nCol = 0; nCol < pStylePtrArray->GetSize(); nCol++)
	{
		pStyle = pStylePtrArray->GetAt(nCol);
		
		if(pStyle == NULL)
			continue;

		WriteStyleColorInfo(pStyle, nColorIndex);
	}
	
	return TRUE;
}

UINT CGXExcelColorTable::GetColorWriteIndex(COLORREF ref) const
{
	UINT nRetval;
	if(m_mpColorToIndex.Lookup(ref, nRetval))
	{
		if( (nRetval + 0x8) > 8)
			nRetval += 0x8;
		return nRetval;
	}
	else
		return GX_INVALID;
}

void CGXExcelColorTable::SetColorWriteIndex(COLORREF ref, UINT& index)
{
	//UINT n(0);
	//COLORREF r = ref;
	
	m_mpColorToIndex.SetAt(ref, index);
	index++;
}

// Application part. This is different from other tables. Please refer to the header
// for notes.
COLORREF CGXExcelColorTable::GetColorAtPalIndex(DWORD index, COLORREF defColor)
{
	colorStruct* pColorStruct = NULL;
	
	//index++;

	if(index >= 56 && defColor == GX_INVALID)
		return ::GetSysColor(COLOR_WINDOW);
	else if(index >= 56)
		return defColor;

	// It is possible that the BIFF file
	// has no palette if it only uses the default palette
	if(!LookupValue(0, pColorStruct) || pColorStruct == NULL)
		return g_ref[index];
		
#ifdef _DEBUG
//	for (DWORD dwDebC = 0; dwDebC < pColorStruct->num; dwDebC++)
//		TRACE1("0x%x, \n", pColorStruct->dwValues[dwDebC]);
		//TRACE2("The color are index %d is %x \n", dwDebC, pColorStruct->dwValues[dwDebC]);
#endif

	if(index >= pColorStruct->num)
		g_ref[index];
		

	DWORD dw = pColorStruct->dwValues[index];

	DWORD t = (dw << 8);
	t&=0xFF000000;
	
	DWORD t1 = (dw << 16);
	t1&=0xFF000000;
	
	DWORD t2 = (dw << 24);
	t2&=0xFF000000;
	
	TRACE1("The color is %x\n", dw);

	COLORREF cr =  RGB( (BYTE)(t2>>24), (BYTE)(t1>>24), (BYTE)(t>>24) );

	return cr;
}


// struct styleStruct

styleStruct::styleStruct()
{
	pVarChar = NULL;
	istyBuiltIn = 0;
}

styleStruct::~styleStruct()
{
	// no implementation
}
	
void styleStruct::Cleanup()
{
	if(pVarChar)
		delete[] pVarChar;
	pVarChar = NULL;
}


// CGXExcelStyleTable
// Excel built in styles
TCHAR* g_szAscBuiltInStyles[] =
{
	_T("Normal"),
	_T("RowLevel_n"),
	_T("ColLevel_n"),
	_T("Comma"),
	_T("Currency"),
	_T("Percent"),
	_T("Comma[0]"),
	_T("Currency[0]"),
};

// 3 6 4 7 0 5
struct _gxexBuiltStyle
{
	TCHAR* pszChar;
	UINT index;
};

_gxexBuiltStyle g_szBuiltInStyles[] =
{
	{_T("Comma"), 3},
	{_T("Comma[0]"), 6},
	{_T("Currency"), 4},
	{_T("Currency[0]"), 7},
	{_T("Standard"), 0},  // OG alias for Normal
	{_T("Percent"), 5},
	//{_T("ColLevel_n"), 2},
	//{_T("RowLevel_n"), 1},
};

	
CGXExcelStyleTable::CGXExcelStyleTable()
{
	// no implementation
}

CGXExcelStyleTable::~CGXExcelStyleTable()
{
	// no implementation
}

BOOL CGXExcelStyleTable::ReadFromStream(IStream* pStream, DWORD /*dwLength*/)
{
	CGXStyle* pBaseStyle = NULL;

	styleStruct* pStyleStruct = new styleStruct;	
	static GXREADSEEKDATA readData[4];

	// phase 1
	readData[0].Init(&pStyleStruct->ixfe);
	
	// apply
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 1))

	
	ASSERT(pTable != NULL);

	pTable->ApplyToObject( (pStyleStruct->ixfe & 0x0fff), pBaseStyle);


	//phase 2
	if( (pStyleStruct->ixfe >> 15) & 0x0001 )
	{
		readData[1].Init(&pStyleStruct->istyBuiltIn);
		readData[2].Init(&pStyleStruct->iLevel); 
		
		GXEX_TRY(ReadSeekHelper(pStream, &readData[1], 2))

		if( (pStyleStruct->ixfe & 0x0FFF)!= 0 && pStyleStruct->istyBuiltIn < 6 )
			pStyleStruct->wID = GXExGetTableMap()->GetCore()->GetParam()->GetStylesMap()->RegisterStyle(g_szAscBuiltInStyles[pStyleStruct->istyBuiltIn], *pBaseStyle);
		else
			pStyleStruct->wID = 0;
	}
	else
	{
		readData[1].Init(&pStyleStruct->cch);
		readData[2].Init((BYTE*)NULL, 1, gxseek);  // I have to do this seek though according to the Excel SDK this should not
		// be required

		// phase 2 get the length
		GXEX_TRY(ReadSeekHelper(pStream, &readData[1], 2))
		
		pStyleStruct->pVarChar = new TCHAR[pStyleStruct->cch+1];
		pStyleStruct->pVarChar[pStyleStruct->cch] = _T('\0');

		// read the name
		readData[3].Init(pStyleStruct->pVarChar, pStyleStruct->cch, gxread); 

		GXEX_TRY(ReadSeekHelper(pStream, &readData[3], 1))
	
		// register the style
		pStyleStruct->wID = GXExGetTableMap()->GetCore()->GetParam()->GetStylesMap()->RegisterStyle(pStyleStruct->pVarChar, *pBaseStyle);
	}
	

	pStyleStruct->ixfe = pStyleStruct->ixfe & 0x0fff;
	m_mapStruct.SetAt(m_dwIndex, pStyleStruct);
	
	++m_dwIndex;
	
	if(pBaseStyle)
		delete pBaseStyle;

	return TRUE;
}

BOOL CGXExcelStyleTable::WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT /*nTabs*/)
{
	HRESULT hr(S_OK);
	
	UINT nBuiltInStyles = sizeof(g_szBuiltInStyles)/sizeof(_gxexBuiltStyle);
	
	UINT nBuiltInSize = nBuiltInStyles*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER);

	BYTE* pszBufferBuiltIn = new BYTE[nBuiltInSize];
	BYTE* pBShdw = pszBufferBuiltIn;
	
	memset(pszBufferBuiltIn, 0, nBuiltInSize);

	ASSERT(pParam != NULL);

	CGXGridParam* p = *pParam;

	ASSERT(p != NULL);

	CGXStylesMap* pStylesMap = p->GetStylesMap();

	ASSERT(pStylesMap != NULL);

	// write out the built in styles
	
	WORD ixfe(0); WORD wID(0);

	// get the XF table
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);

	ASSERT(pTable != NULL);

	// to store the base style index for the Excel/OG styles
	CWordArray wArExStyles;
	wArExStyles.Add(pStylesMap->m_wStyleColHeader);
	wArExStyles.Add(pStylesMap->m_wStyleRowHeader);
	wArExStyles.Add(pStylesMap->m_wStyleStandard);

	UINT nBuiltIndex(0);
	
	CString strStd;
#ifdef _DEBUG
	ASSERT(strStd.LoadString(GX_IDS_STYLE_STANDARD)); // Error---> Check if resources are included
#else
	strStd.LoadString(GX_IDS_STYLE_STANDARD); 
#endif

	UINT nActBuilt(0);
	UINT nC;
	for(nC =0; nC < nBuiltInStyles; nC++)
	{
		nBuiltIndex = g_szBuiltInStyles[nC].index;

		if(wID = pStylesMap->GetBaseStyleId(g_szBuiltInStyles[nC].pszChar))
		{
			ixfe = pTable->GetExcelBStyleMap().GetIndexID(wID);
			
			_gxExSetBit(ixfe, 15, 1);
			_gxExWriteWord(pszBufferBuiltIn + nC*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER), ixfe);
			_gxExWriteByte(pszBufferBuiltIn + nC*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER) + 2, nBuiltIndex);
			_gxExWriteByte(pszBufferBuiltIn + nC*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER) + 3, 0xFF); // We don't use outline styles
			
			nActBuilt++;
			wArExStyles.Add(wID);
		}
		else if(!_tcscmp(strStd, g_szBuiltInStyles[nC].pszChar))
		{
			// the standard style XF
			ixfe = 0;
			_gxExSetBit(ixfe, 15, 1);
			_gxExWriteWord(pszBufferBuiltIn + nC*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER), ixfe);
			_gxExWriteByte(pszBufferBuiltIn + nC*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER) + 2, nBuiltIndex);
			_gxExWriteByte(pszBufferBuiltIn + nC*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER) + 3, 0xFF); // We don't use outline styles
			
			nActBuilt++;
		}
		else
		{
			_gxExSetBit(ixfe, 15, 1);
			_gxExWriteWord(pszBufferBuiltIn + nC*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER), ixfe);
			_gxExWriteByte(pszBufferBuiltIn + nC*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER) + 2, nBuiltIndex);
			_gxExWriteByte(pszBufferBuiltIn + nC*(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER) + 3, 0xFF); // We don't use outline styles
			
			nActBuilt++;

			// To Do Log this
			TRACE1("OG Pro: Info...Base style: %s appears to have been removed\n", g_szBuiltInStyles[nC]);
			TRACE0("OG Pro: Info...If this is a new file being created you can ignore this\n");
		}	
	}

	// write out the other (custom) base styles (check with the XF table)
	struct __data
	{
		WORD ixfe;
		WORD cch;
		WCHAR* pszData;
	};
	
	__data* pCustData = new __data[GX_EX_BASESTYLEMAX]; // we limit this to 256 base styles
	__data* pCustDataShdw = pCustData;

	// iterate through the styles map
	// Base styles
	POSITION pos = pStylesMap->StartStylesIteration();

	WORD wStyleId(0); UINT nResourceID(0); 
	
	CString strBaseStyleName;
	
	UINT nCustomSize(0); // for the number of custom base styles
	
	DWORD nCustDataSize(0); // for the number of bytes to be used for this
	
	const CGXStyle* pIterStyle = NULL;

	while(pos != NULL)
	{
		pStylesMap->GetNextStyle(pos, wStyleId, strBaseStyleName, nResourceID, pIterStyle);
		if(pIterStyle != NULL)
		{
			// check if this is a user defined style
			if(!CheckIfUserDefined(wArExStyles, wStyleId))
				continue;

			// Get the actual XF for this base style
			pCustData->ixfe = pTable->GetExcelBStyleMap().GetIndexID(wStyleId);
			
			_gxExSetBit(pCustData->ixfe, 15, 0);
			
			pCustData->cch = _tcslen(strBaseStyleName);
			
	#ifdef _UNICODE
			pCustData->pszData = new WCHAR[pCustData->cch];
			memcpy(pCustData->pszData, (LPCTSTR) strBaseStyleName, pCustData->cch*2);
	#else 
			int nCount = MultiByteToWideChar(CP_ACP, 0, strBaseStyleName, -1, NULL, NULL);
			ASSERT(nCount);
			//WCHAR* pszW = NULL;
		
			pCustData->pszData = new WCHAR[nCount];
		
			MultiByteToWideChar(CP_ACP, 0, strBaseStyleName, -1, pCustData->pszData, nCount);
			
			//pCustData->cch = nCount;
	#endif
			
			nCustDataSize+=( sizeof(WCHAR)*pCustData->cch + sizeof(WORD) + sizeof(BYTE) + sizeof(WORD)); // String length +
			// ixfe + cch (which is actual a WORD) + the one extra byte

			pCustData++;
			nCustomSize++;
		}
	}

	// now write out the values
	ULONG cb(0);
	// Excel Base styles

	BYTE pszBuffer[GX_EX_FIXEDHEADER];
	
	// write out the header
	_gxdata(wr1)
		_gxw(typeStyle)
		_gxw(GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER)
	_gxend

	_gxExWrite(wr1, pszBuffer);

	
	pszBufferBuiltIn = pBShdw;

	for(nC = 0; nC < nActBuilt; nC++)
	{
		
		GX_EX_WRITE(pStream->Write(pszBuffer, GX_EX_FIXEDHEADER, &cb));
		dwLength+=cb;
				
		cb = 0;
		
		GX_EX_WRITE(pStream->Write(pszBufferBuiltIn, GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER, &cb));
		dwLength+=cb;
		
		pszBufferBuiltIn += (GX_EX_SIZE_BUILTINSTYLE - GX_EX_FIXEDHEADER);
	}

	if(pBShdw)
		delete[] pBShdw;

	// user defined styles
	BYTE* pCustWriteBuffer = new BYTE[nCustDataSize + 2*nCustomSize*sizeof(WORD)];
	BYTE* pCustWrShdw = pCustWriteBuffer;

	pCustData = pCustDataShdw;

	for(nC = 0; nC < nCustomSize; nC++)
	{
		_gxdata(wr3)
			_gxw(typeStyle)
			_gxw( sizeof(pCustData->ixfe) + sizeof(pCustData->cch) + 1 + pCustData->cch*sizeof(WCHAR) ) //2
			_gxw(pCustData->ixfe) //2
			_gxw(pCustData->cch) // 1
			_gxb(1) //1
			_gxby(pCustData->pszData, sizeof(WCHAR)*pCustData->cch) //cch
		_gxend

		_gxExWrite(wr3, pCustWriteBuffer);
		
		if(pCustData->pszData)
			delete[] pCustData->pszData;

			pCustData->pszData = NULL;

		pCustWriteBuffer+= (sizeof(pCustData->ixfe) + sizeof(pCustData->cch) + 1 + sizeof(WCHAR)*pCustData->cch + 2*sizeof(WORD));
		
		pCustData++;
	}

	cb = 0;
	GX_EX_WRITE(pStream->Write(pCustWrShdw, nCustDataSize + 2*nCustomSize*sizeof(WORD), &cb));
	dwLength+=cb;
		
	if(pCustWrShdw)
		delete [] pCustWrShdw;

	if(pCustDataShdw)
		delete [] pCustDataShdw;
	
	return TRUE;
}

BOOL CGXExcelStyleTable::CheckIfUserDefined(const CWordArray& arr, WORD index)
{
	for (int nC(0); nC < arr.GetSize(); nC++)
	{
		if(arr[nC] == index)
			return FALSE; // This is not an user defined style
	}

	return TRUE;	
}


WORD CGXExcelStyleTable::GetBaseStyleID(DWORD index)
{
	// loop through and look for this ixfe index
	POSITION pos = m_mapStruct.GetStartPosition();

	DWORD dwKey(0);
	styleStruct* pStyleStruct = NULL;
	while(pos != NULL)
	{
		m_mapStruct.GetNextAssoc(pos, dwKey, pStyleStruct);
	
		if(pStyleStruct->ixfe == index)
			return pStyleStruct->wID; // the correct base style index
	}

	// Removed this check. This can be the case for Row and Column base styles since these are stored
	// as cell styles in Excel.
	// ASSERT(0); // This should not happen. All the style object base styles should have been registered
	
	return 0;
}



// struct XFStruct

void XFStruct::Cleanup()
{
	/*No implementation*/
};

//CGXExcelXFTable

CGXExcelXFTable::CGXExcelXFTable()
{
	m_pArManager = new CGXXFArrayManager(new CGXXFArrayCreator, &CGXXFArray::Destroy);
	
	m_ArrPattern.Add(GXEXNOPATTERN);    // Element 1 This should never be used
	m_ArrPattern.Add(2);    // Element 2
	m_ArrPattern.Add(1);    // Element 3
	m_ArrPattern.Add(3);    // Element 4
	m_ArrPattern.Add(28);    // Element 5
	m_ArrPattern.Add(29);    // Element 6
	m_ArrPattern.Add(7);    // Element 7
	m_ArrPattern.Add(15);    // Element 8
	m_ArrPattern.Add(14);    // Element 9
	m_ArrPattern.Add(17);    // Element 10
	m_ArrPattern.Add(12);    // Element 11
	m_ArrPattern.Add(24);    // Element 12
	m_ArrPattern.Add(21);    // Element 13
	m_ArrPattern.Add(20);    // Element 14
	m_ArrPattern.Add(22);    // Element 15
	m_ArrPattern.Add(17);    // Element 16
	m_ArrPattern.Add(4);    // Element 17
	m_ArrPattern.Add(4);    // Element 18
	
	LogText("XFTable created\n");

	m_iCurRow = 0xFFFF; // invalid index
	m_iCurCol = 0xFFFF;
	m_uinTab = 0;
}


CGXExcelXFTable::~CGXExcelXFTable()
{
	if(m_pArManager)
		delete m_pArManager;
}

void CGXExcelXFTable::ResetInternalState()
{
	_base::ResetInternalState();

	if(m_pArManager)
		delete m_pArManager;

	m_pArManager = new CGXXFArrayManager(new CGXXFArrayCreator, &CGXXFArray::Destroy);
}

BOOL CGXExcelXFTable::ReadFromStream(IStream* pStream, DWORD /*dwLength*/)
{
	XFStruct* pXFStruct = new XFStruct;	
	static GXREADSEEKDATA readData[9];

	readData[0].Init(&pXFStruct->ifnt);
	readData[1].Init(&pXFStruct->ifmt);
	readData[2].Init(&pXFStruct->fLocked); 
	readData[3].Init(&pXFStruct->alc); 
	
	readData[4].Init(&pXFStruct->cIndent); 

	readData[5].Init(&pXFStruct->dgLeft); 
	readData[6].Init(&pXFStruct->icvLeft); 
	readData[7].Init(&pXFStruct->icvTop); 

	readData[8].Init(&pXFStruct->icvFore); 

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 9))

	m_mapStruct.SetAt(m_dwIndex, pXFStruct);
	
	++m_dwIndex;
	
	return TRUE;
}


BOOL CGXExcelXFTable::WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs)
{
	HRESULT hr(S_OK);
	
	BYTE pszBuffer[GXEX_SIZEOF_XF];
	
	memset(pszBuffer, 0, GXEX_SIZEOF_XF);

	// afxDump.HexDump( ".", (BYTE*) pszBuffer, 20, 20 );

	// write the standard style
	CGXStylesMap* pStylesMap = (*pParam)->GetStylesMap();
	ASSERT(pStylesMap != NULL); // Error---> The stylesmap has to be valid

	CGXStyle* pStyle = NULL;
	CGXStyle* pStandard = NULL;

	pStylesMap->LookupStyle(pStylesMap->m_wStyleStandard, pStyle);

	pStandard = pStyle;

	// write the header data
	_gxdata(wr)
		_gxw(typeXF)
		_gxw(GXEX_SIZEOF_XF - GX_EX_FIXEDHEADER)
	_gxend

	_gxExWrite(wr, pszBuffer);

	// write the actual XF to the buffer
	TranslateStyleToXF(pStyle, pszBuffer + GX_EX_FIXEDHEADER, TRUE, pStylesMap);

	// write the buffer to the stream
	ULONG cb(0);
	
	// write out all the default styles. We have no outline styles so all these are the same as the standard style.
	for (short s(0); s < GX_EX_NUM_DEFAULTXF; s++)
	{
		GX_EX_WRITE(pStream->Write(pszBuffer, GXEX_SIZEOF_XF, &cb));
		dwLength+=cb;
		cb = 0;
	}

	cb = 0;

	// Now, I will translate the same style as the default CELL XF style

	TranslateStyleToXF(pStyle, pszBuffer + GX_EX_FIXEDHEADER, FALSE, pStylesMap, TRUE);
	
	GX_EX_WRITE(pStream->Write(pszBuffer, GXEX_SIZEOF_XF, &cb));
	dwLength+=cb;

	GetExcelBStyleMap().SetIndexID(pStylesMap->m_wStyleStandard, 0); 

	// TRACE0("Binary data written\n");
	// afxDump.HexDump( ".", (BYTE*) pszBuffer, 20, 20 );
	
	pStyle = NULL;

	// Write the other styles (base styles and specific styles)
	// Base styles
	POSITION pos = pStylesMap->StartStylesIteration();

	WORD wStyleId(0); UINT nResourceID(0); UINT nStyleIndex(GX_EX_NUM_DEFAULTXF + 1); // This set of styles starts with index 16
	
	CString strName;
	
	const CGXStyle* pIterStyle = NULL;
	
	while(pos != NULL)
	{
		pStylesMap->GetNextStyle(pos, wStyleId, strName, nResourceID, pIterStyle);
		if(pIterStyle != NULL && wStyleId != pStylesMap->m_wStyleStandard)
		{
			// clear the buffer
			memset(pszBuffer, 0, GXEX_SIZEOF_XF);
	
			_gxdata(wr)
				_gxw(typeXF)
				_gxw(GXEX_SIZEOF_XF - GX_EX_FIXEDHEADER)
			_gxend

			_gxExWrite(wr, pszBuffer);
			
			// write the actual XF to the buffer
			TranslateStyleToXF(pIterStyle, pszBuffer + GX_EX_FIXEDHEADER, TRUE, pStylesMap);

			GX_EX_WRITE(pStream->Write(pszBuffer, GXEX_SIZEOF_XF, &cb));
			dwLength+=cb;
			
			GetExcelBStyleMap().SetIndexID(wStyleId, nStyleIndex); 
			nStyleIndex++;
			// TRACE0("Base style information\n");
			// afxDump.HexDump( ".", (BYTE*) pszBuffer, cb, cb );
		}
	}

	// The specific styles and the row and column styles from CGXData

	CGXData* pData = NULL;
	_accData* pD  = NULL;
	
	CGXStylePtrArray* pRowStyles = NULL;
	CGXStylePtrArray* pColStyle = NULL;
	
	CGXStylePtrArrayPtrArray* pStylePtrAr = NULL;

	// Iterate through all the other styles
	for(ROWCOL nC(0); nC < nTabs; nC++)
	{
		SetCurrentReadIndex(nC);
		
		pData = (*pParam)->GetData();
		
		ASSERT(pData != NULL);
		
		pD  = (_accData*)pData;

		pRowStyles = &pD->m_apRowBaseStyle;// row base styles
		pColStyle = &pD->m_apColBaseStyle;// column base styles
	
		pStylePtrAr =  &pD->m_apapCellStyle; // spans the cell matrix,
												// CGXStylePtrArray elements are rows
												// which CGXStyle elements are styles
	
	
		if(pData->IsKindOf(RUNTIME_CLASS(CGXFormulaSheet)))
		{
			CGXFormulaSheet* pSheet = (CGXFormulaSheet*)pData;
			
			ASSERT(pSheet != NULL);
			// get the iteration limits
			int nOUpperBound(0);
			int nIUpperBound(0);
	
			int sIndex = pSheet->m_nSheetContext;
			// get the upper bound from the formula sheet
			gxRange gxR;
			_gx_init_range(&gxR);
#ifdef _DEBUG
			_gx_get_sheet_extent(sIndex, &gxR);
#else
			_gx_get_sheet_extent(sIndex, &gxR);
#endif
			nOUpperBound = pSheet->GetGridRow(gxR.r1) + 1;
			nIUpperBound = pSheet->GetGridCol(gxR.c1) + 1;
		
			CGXStyle* pStyle = NULL;
			
			pStyle = new CGXStyle;

			ASSERT(pStyle != NULL);

			for (int nR(1); nR < nOUpperBound; nR++)
			{
				for (int nCol = 1;  nCol < nIUpperBound; nCol++)
				{
					pStyle->Free();
					
					gxCell *cp = NULL;
					cp = _gx_find_cell(sIndex, pSheet->GetEngineRow(nR), pSheet->GetEngineCol(nCol));
					
					if (cp && cp->pStyle)
					{
						pStyle->ChangeStyle(*cp->pStyle, gxCopy);
						WriteFormulaStyle(nR, nCol, pStream, pStylesMap, pStyle, dwLength, nStyleIndex, nC);
					}
				}
			}
		
			if(pStyle != NULL)
				delete pStyle;
		}
		else
		{
			CGXStylePtrArray* pStyleDataPtrAr = NULL;

			for (ROWCOL nR(1); nR < (ROWCOL) pStylePtrAr->GetSize(); nR++)
			{	
				
				pStyleDataPtrAr = pStylePtrAr->GetAt(nR);
				
				if(pStyleDataPtrAr != NULL)
					WriteComposedStylePtrArray(pStyleDataPtrAr, pStream, 
									   dwLength, 
									   gxRowCol,
									   nR,
									   nStyleIndex,
									   pStandard,
									   nC,
									   pStylesMap,
									   FALSE,
									   pColStyle,
									   pRowStyles
									   );
			}
		}
	
		WriteStylePtrArray(pRowStyles, pStream, 
								   dwLength, 
								   gxRowColRow,
								   0,
								   nStyleIndex,
								   pStandard,
								   nC,
								   pStylesMap,
								   FALSE);

	
		WriteStylePtrArray(pColStyle, pStream, 
								   dwLength, 
								   gxRowColCol,
								   0,
								   nStyleIndex,
								   pStandard,
								   nC,
								   pStylesMap,
								   FALSE);
 
	
		pParam++;
	}

	return TRUE;
}

BOOL CGXExcelXFTable::WriteFormulaStyle(int nR, int nCol, IStream* pStream, const CGXStylesMap* pStylesMap, const CGXStyle* pStyle, DWORD& dwLength, UINT& nStyleIndex, UINT nC)
{
	BYTE pszBuffer[GXEX_SIZEOF_XF];
	
	memset(pszBuffer, 0, GXEX_SIZEOF_XF);

	_gxdata(wr)
		_gxw(typeXF)
		_gxw(GXEX_SIZEOF_XF - GX_EX_FIXEDHEADER)
	_gxend

	_gxExWrite(wr, pszBuffer);
	
	// write the actual XF to the buffer
	// bStyle will be FALSE for all the cell specific styles
	TranslateStyleToXF(pStyle, pszBuffer + GX_EX_FIXEDHEADER, FALSE, pStylesMap);


	DWORD dwExistIndex(0xFFFF);
		
	
	dwExistIndex = GetExcelStyleMap(nC).IsXFPresent(pszBuffer + GX_EX_FIXEDHEADER); 
		
	if(dwExistIndex != 0xFFFF)
	{
		GetExcelStyleMap(nC).SetIndexRowCol(nR, nCol, dwExistIndex);	
		return TRUE;
	}	
		
	GetExcelStyleMap(nC).SetIndexRowCol(nR, nCol, nStyleIndex, pszBuffer + GX_EX_FIXEDHEADER);
	
	nStyleIndex++;

	HRESULT hr(S_OK);
	ULONG cb(0);
	GX_EX_WRITE(pStream->Write(pszBuffer, GXEX_SIZEOF_XF, &cb));
		
	dwLength+=cb;
	
	return TRUE;
}


// This method is a legacy hook for the WriteComposedStylePtrArray method.
BOOL CGXExcelXFTable::WriteStylePtrArray(CGXStylePtrArray* pStylePtrArray, IStream* pStream, 
										 DWORD& dwLength, 
										 CGXExcelXFTable::gxRowColType type,
										 ROWCOL nRC,
										 UINT& nStyleIndex,
										 const CGXStyle* pStyleStandard,
										 UINT nC,
										 const CGXStylesMap* pStylesMap,
										 BOOL bStyle )
{
	return WriteComposedStylePtrArray(pStylePtrArray, pStream, dwLength, type, nRC, nStyleIndex, pStyleStandard,
										 nC, pStylesMap, bStyle);
}

// Helper to write a CGXStylePtrArray
BOOL CGXExcelXFTable::WriteComposedStylePtrArray(CGXStylePtrArray* pStylePtrArray, IStream* pStream, 
										 DWORD& dwLength, 
										 gxRowColType type,
										 ROWCOL nRC,
										 UINT& nStyleIndex,
										 const CGXStyle* /*pStandardStyle*/,
										 UINT nC,
										 const CGXStylesMap* pStylesMap,
										 BOOL bStyle,
										 CGXStylePtrArray* pColStylePtrArray,
										 CGXStylePtrArray* pRowStylePtrArray						
								   )
{
	HRESULT hr(S_OK);
	//egxExcelRWFlags flags(egxSuccess);

	BYTE pszBuffer[GXEX_SIZEOF_XF];
	
	memset(pszBuffer, 0, GXEX_SIZEOF_XF);

	CGXStyle* pStyle = NULL;
	CGXStyle* pStyle1 = NULL;
	
	ULONG cb(0);

	for (int nCol = 0; nCol < pStylePtrArray->GetSize(); nCol++)
	{
		pStyle = pStylePtrArray->GetAt(nCol);
		
		if(pStyle == NULL)
			continue;

		//don't try to save cell information for row 0 or col 0.
		if((nRC == 0 || nCol == 0) && type == CGXExcelXFTable::gxRowCol)
			continue;
				
		memset(pszBuffer, 0, GXEX_SIZEOF_XF);
	
		if(type == CGXExcelXFTable::gxRowCol)
		{
			SetCurrentReadCol(nCol);
			SetCurrentReadRow(nRC);
		}
		
		//if being called for gxRowCol, check to see if col or row
		//styles need to be composed. Without the composition, copy
		//& paste fails in some circumstances within Excel.
		if(pRowStylePtrArray || pColStylePtrArray)
		{
			if(pStyle1 == NULL)
				pStyle1 = new CGXStyle();
			ASSERT(pStyle1);

			*pStyle1 = *pStyle;
			if(nRC > 0 && nCol > 0 )
			{
				if(pRowStylePtrArray &&
					(pStyle = pRowStylePtrArray->GetAt(nRC)) != NULL)
				{
					pStyle1->ChangeStyle(*pStyle, gxApplyNew);
				}
				if(pColStylePtrArray && 
					(pStyle = pColStylePtrArray->GetAt(nCol)) != NULL)
				{
					pStyle1->ChangeStyle(*pStyle, gxApplyNew);
				}
			}
			// write the actual XF to the buffer
			// bStyle will be FALSE for all the cell specific styles
			TranslateStyleToXF(pStyle1, pszBuffer + GX_EX_FIXEDHEADER, bStyle, pStylesMap, FALSE, nC);
		}
		else
		// write the actual XF to the buffer
		// bStyle will be FALSE for all the cell specific styles
		TranslateStyleToXF(pStyle, pszBuffer + GX_EX_FIXEDHEADER, bStyle, pStylesMap, FALSE, nC);

		if(type == CGXExcelXFTable::gxRowCol)
		{
			SetCurrentReadCol(0xFFFF);
			SetCurrentReadRow(0xFFFF);
		}
		

		DWORD dwExistIndex(0xFFFF);
		
		if(!bStyle)
			dwExistIndex = GetExcelStyleMap(nC).IsXFPresent(pszBuffer + GX_EX_FIXEDHEADER); 
		
		if(dwExistIndex != 0xFFFF)
		{
				// check the kind of style
			switch(type)
			{
			  case CGXExcelXFTable::gxRowCol:
					GetExcelStyleMap(nC).SetIndexRowCol(nRC, nCol, dwExistIndex);
					break;
			  case CGXExcelXFTable::gxRowColRow:
					GetExcelStyleMap(nC).SetIndexRowCol(nCol, 0, dwExistIndex);	
					break;
			  case CGXExcelXFTable::gxRowColCol:
					GetExcelStyleMap(nC).SetIndexRowCol(0, nCol, dwExistIndex);
					break;	
			  default:
					ASSERT(0); //--->Error unsupported enum value
			}
		
			continue;
		}
		
		_gxdata(wr)
			_gxw(typeXF)
			_gxw(GXEX_SIZEOF_XF - GX_EX_FIXEDHEADER)
		_gxend

		_gxExWrite(wr, pszBuffer);
	
	
		// check the kind of style
		switch(type)
		{
			case CGXExcelXFTable::gxRowColRow:
				GetExcelStyleMap(nC).SetIndexRowCol(nCol, 0, nStyleIndex);	
				break;
			case CGXExcelXFTable::gxRowColCol:
				GetExcelStyleMap(nC).SetIndexRowCol(0, nCol, nStyleIndex);
				break;	
			case CGXExcelXFTable::gxRowCol:
				GetExcelStyleMap(nC).SetIndexRowCol(nRC, nCol, nStyleIndex, pszBuffer + GX_EX_FIXEDHEADER);
				break;
			default:
				ASSERT(0); //--->Error unsupported enum value
		}
		
		nStyleIndex++;

		GX_EX_WRITE(pStream->Write(pszBuffer, GXEX_SIZEOF_XF, &cb));
		
		dwLength+=cb;
	}

	if(pStyle1 != NULL)
		delete pStyle1;

	return TRUE;
}

void CGXExcelXFTable::TranslateStyleToStyleXF(const CGXStyle* p, BYTE* pszBuffer, const CGXStylesMap* pStylesMap)
{
	CGXStyle* pStyle = NULL;
	if(p)
		pStyle = p->Clone();

	// get the index for the font from the font table
	CGXExcelFontTable* pFTable = (CGXExcelFontTable*) GXExGetTableMap()->LocateHandler(typeFont);
	ASSERT(pFTable!=NULL); // Error---> There has to be a valid font table

	// get the color table
	CGXExcelColorTable* pColorTable = (CGXExcelColorTable*) GXExGetTableMap()->LocateHandler(typePalette);
	ASSERT(pColorTable!=NULL); // Error---> There has to be a valid color table


	CGXExcelFormatTable* pFormatTable = (CGXExcelFormatTable*) GXExGetTableMap()->LocateHandler(typeFormat);
	ASSERT(pFormatTable!=NULL); // Error---> There has to be a valid format table


	// The other words
	WORD wFormat(0);WORD fLocked(0); WORD alc(0); WORD cIndent(0); WORD dgLeft(0); WORD icvLeft(0); DWORD icvTop(0); WORD icvFore(0);
	

	_gxExSetBitEx(cIndent, 10, 0xFFFF); 

	// check the format
	if (pStyle->GetIncludeFormat())
		_gxExSetBit(cIndent, 10, 0); // format is included
	
	if (pStyle->GetIncludeFont())
		_gxExSetBit(cIndent, 11, 0); // font is included

	if(pStyle->GetIncludeHorizontalAlignment() || pStyle->GetIncludeWrapText())
		_gxExSetBit(cIndent, 12, 0); // alignment is included
	
	if(pStyle->GetIncludeInterior())
		_gxExSetBit(cIndent, 14, 0); // the interior pattern, color etc
	
	// standard style
	CGXStyle* pStandard = NULL;
	pStylesMap->LookupStyle(pStylesMap->m_wStyleStandard, pStandard);
	
	pStyle->ChangeStyle(*pStandard, gxApplyNew);
	
	UINT nFontIndex = 0;
	
	if(p->GetIncludeFont())
		nFontIndex = pFTable->GetFontIndex(CGXExcelFontIndex(p->GetFont().GetFontKey(), p->GetIncludeTextColor()?p->GetTextColor():0));
	
	wFormat = pFormatTable->GetExcelIndexForWrite(pStyle);
	
	// locked bit
	_gxExSetBit(fLocked, 0, 0);
	
	// hidden bit 
	_gxExSetBit(fLocked, 1, 0);

	// style or cell XF
	_gxExSetBit(fLocked, 2, 1);
	
	// the Lotus Bit always 0
	_gxExSetBit(fLocked, 3, 0);
	
	// the parent XF record. This is a style record. No Parent style
	// Excel has no support for multiple base style layers
	UINT nStyleIndex(ixfNULL);
	
	_gxExSetBitEx(fLocked, 4, nStyleIndex);

	// alignment
	// get the alignment
	if(pStyle->GetIncludeHorizontalAlignment())
	{
		switch(pStyle->GetHorizontalAlignment())
		{
		case DT_LEFT:
			_gxExSetBitEx(alc, 0, 0x1);
			break;
		case DT_CENTER:
			_gxExSetBitEx(alc, 0, 0x2);
			break;
		case DT_RIGHT:
			_gxExSetBitEx(alc, 0, 0x3);
			break;
		default:
			_gxExSetBitEx(alc, 0, 0x0);
			break;
		};
	}
	
	// Wrap Text
	if(pStyle->GetIncludeWrapText() && pStyle->GetWrapText())
		_gxExSetBit(alc, 3, 1);
	
	// vertical alignment
	if(pStyle->GetIncludeVerticalAlignment())
	{
		switch(pStyle->GetVerticalAlignment())
		{
		case DT_TOP:
			_gxExSetBitEx(alc, 4, 0x0);
			break;
		case DT_VCENTER:
			_gxExSetBitEx(alc, 4, 0x1);
			break;
		case DT_BOTTOM:
			_gxExSetBitEx(alc, 4, 0x2);
			break;
		default:
			_gxExSetBitEx(alc, 4, 0x0); //Top is used as default
			break;
		};
	}

	// fJustLast (Used only in Far East versions of MS Excel
	_gxExSetBit(alc, 7, 0);

	if(pStyle->GetIncludeFont() && pStyle->GetFont().GetIncludeOrientation())
	{
		long lOrient = pStyle->GetFont().GetOrientation();
		lOrient = lOrient/10;
		_gxExSetBitEx(alc, 8, (unsigned)lOrient); 
	}

	
	
	// index to the color palette for the foreground/background color of the color pattern
	UINT nColorIndex(0);
	
	UINT nDefColorIndex(0);
	
	nDefColorIndex = pColorTable->GetColorWriteIndex(::GetSysColor(COLOR_WINDOW));

	if(pStyle->GetIncludeInterior())
	{
			CGXBrush& br = pStyle->GetInterior();
			COLORREF refClr = br.GetColor();
			nColorIndex = pColorTable->GetColorWriteIndex(refClr);
			_gxExSetBitEx(icvFore, 0, nColorIndex);
		
			COLORREF refBk = br.GetBkColor();
			
			nColorIndex = pColorTable->GetColorWriteIndex(refBk);
			
			WORD wPattern = 0;
			
			if(br.GetStyle() == BS_PATTERN)
				wPattern = (WORD) TranslatePattern(br.GetPattern(), FALSE);
			else if(nDefColorIndex != pColorTable->GetColorWriteIndex(refClr))
				wPattern = 1;

			_gxExSetDWBitEx(icvTop, 26, wPattern);
			_gxExSetBitEx(icvFore, 7, nColorIndex);
	}

	
	GXBorderType borders[] = {gxBorderTop, gxBorderLeft, gxBorderBottom, gxBorderRight};
			
	for (UINT n(0) ; n < sizeof(borders) / sizeof(GXBorderType); n++)
	{
		if(pStyle->GetIncludeBorders(borders[n]) && (pStyle->GetBorders(borders[n]).GetStyle() != PS_NULL))
		{
			CGXPen& pen = pStyle->GetBorders(borders[n]);
			_gxExSetBit(cIndent, 13, 1); // set the include bit for the borders
			
			switch(borders[n])
			{
				case gxBorderTop:
					_gxExSetBitEx( dgLeft, 8, GetPenStyle(pen) );			
					_gxExSetDWBitEx( icvTop, 0, pColorTable->GetColorWriteIndex(pen.GetColor()) );
					break;
				case gxBorderLeft:
					_gxExSetBitEx( dgLeft, 0, GetPenStyle(pen) );			
					_gxExSetBitEx( icvLeft, 0, pColorTable->GetColorWriteIndex(pen.GetColor()) );
					break;
				case gxBorderBottom:
					_gxExSetBitEx( dgLeft, 12, GetPenStyle(pen) );			
					_gxExSetDWBitEx( icvTop, 7, pColorTable->GetColorWriteIndex(pen.GetColor()) );
					break;
				case gxBorderRight:
					_gxExSetBitEx( dgLeft, 4, GetPenStyle(pen) );			
					_gxExSetBitEx( icvLeft, 7, pColorTable->GetColorWriteIndex(pen.GetColor()) );
					break;
				default:
					ASSERT(0);
					// Invalid border value
			}	
		}
	}


	// reserved and pivot table (14 and 15)
	_gxExSetBit(icvFore, 14, 0);
	_gxExSetBit(icvFore, 15, 0);
	
	_gxExSetDWBitEx(icvTop, 25, 0);
	
	
	// now write the data to the buffer
	_gxdata(wr)
		_gxw(nFontIndex) // 2
		_gxw(wFormat) // 2
		_gxw(fLocked) //2
		_gxw(alc) //2
		_gxw(cIndent) // 2
		_gxw(dgLeft) // 2
		_gxw(icvLeft) // 2
		_gxdw(icvTop) // 4
		_gxw(icvFore) // 2
	_gxend

	/// Total ---> 24 Bytes for STYLE XF BIFF 8

	_gxExWrite(wr, pszBuffer);
	
	if(pStyle)
		delete pStyle;
	
	// done
}

void CGXExcelXFTable::TranslateStyleToCellXF(const CGXStyle* p, BYTE* pszBuffer, const CGXStylesMap* pStylesMap, BOOL bStandardStyle /*= FALSE*/, UINT nTab)
{
	CGXStyle* pStandard = NULL;
	pStylesMap->LookupStyle(pStylesMap->m_wStyleStandard, pStandard);
	
	CGXStyle* pStyle = p->Clone();

	if(bStandardStyle == TRUE) // special case for the standard CELL XF
		pStyle->ChangeStyle(*pStandard, gxExclude);
	
	// get the index for the font from the font table
	CGXExcelFontTable* pFTable = (CGXExcelFontTable*) GXExGetTableMap()->LocateHandler(typeFont);
	ASSERT(pFTable!=NULL); // Error---> There has to be a valid font table

	// get the color table
	CGXExcelColorTable* pColorTable = (CGXExcelColorTable*) GXExGetTableMap()->LocateHandler(typePalette);
	ASSERT(pColorTable!=NULL); // Error---> There has to be a valid color table

	CGXExcelFormatTable* pFormatTable = (CGXExcelFormatTable*) GXExGetTableMap()->LocateHandler(typeFormat);
	ASSERT(pFormatTable!=NULL); // Error---> There has to be a valid format table

	// The other words
	WORD wFormat(0); WORD fLocked(0); WORD alc(0); WORD cIndent(0); WORD dgLeft(0); WORD icvLeft(0); DWORD icvTop(0); WORD icvFore(0);

	// Note: Excel stores all data in individual styles as well as in base styles
	// It uses base styles merely as a point of propagation of changes and does not seem
	// to use it for storage savings.
	
	// This is different from what we do with Objective Grid. We have to annul the assignments that the
	// base styles would have anyway.
	
	// To get around this we set the include bits first. Then apply the base style so that the values are stored in
	// the XF structure anyway (irrespective of whether they are the same as in the base style)

	// first set the include bits
	if (pStyle->GetIncludeFormat())
		_gxExSetBit(cIndent, 10, 1); // format is different from that of parent
	
	if (pStyle->GetIncludeFont())
		_gxExSetBit(cIndent, 11, 1); // font is different from that of parent

	if(pStyle->GetIncludeHorizontalAlignment() || pStyle->GetIncludeWrapText())
		_gxExSetBit(cIndent, 12, 1); // alignment
	
	if(pStyle->GetIncludeInterior())
		_gxExSetBit(cIndent, 14, 1); // the interior pattern, color etc
	
	// the parent XF record. All CELL XFs must have a parent style
	UINT nStyleIndex(0);

	if(pStyle->GetIncludeBaseStyle())
		nStyleIndex = GetExcelBStyleMap().GetIndexID(pStyle->GetBaseStyle());

	
	// Before we do anything else...
	// apply the base style
	if(pStylesMap != NULL  &&  nStyleIndex)
		pStyle->LoadBaseStyle(*pStylesMap);
	

	//
	// DJ added this post 7.0
	// we now check to see if there is a Row style that can be used. In the absence of
	// a row style we will check for a column style. In the absence of both as well
	// as a base style we will use the Normal style, ixfe = 0
	// Please note that there are differences in the behavior of Excel and Objective Grid
	// in this area. With OG different styles can coexist and can be applied on top of the
	// other. With Excel this is supported but only for one layer. We cannot have multiple
	// layers that make sense. For example base styles cannot specify the font and row styles
	// the color. In OG they can. This can lead to some subtle inconsistencies in the generated
	// file.
	if( nStyleIndex == 0 && (0xFFFF != GetCurrentReadCol() || 0xFFFF != GetCurrentReadRow()))
	{
		// check if we have a column style
		nStyleIndex = GetExcelStyleMap(GetCurrentReadIndex()).GetIndexRowCol(0, GetCurrentReadCol());
		
		ASSERT(pStylesMap->Grid() != NULL); // There should be an associated grid
		
		CGXStyle* pStyleRowCol = pStylesMap->Grid()->CreateStyle();

		// if not check if we have a row style
		if(!nStyleIndex)
		{
			nStyleIndex = GetExcelStyleMap(GetCurrentReadIndex()).GetIndexRowCol(GetCurrentReadRow(), 0);
			if(nStyleIndex != 0 && pStylesMap->Grid()->GetRowStyle(GetCurrentReadRow(), *pStyleRowCol))
				pStyle->ChangeStyle(*pStyleRowCol, gxApplyNew);
		}
		else
		{
			if(pStylesMap->Grid()->GetColStyle(GetCurrentReadCol(), *pStyleRowCol))
				pStyle->ChangeStyle(*pStyleRowCol, gxApplyNew);
		}

		if (pStyleRowCol != NULL)
			pStylesMap->Grid()->RecycleStyle(pStyleRowCol);
	}
	//


	// standard style
	pStyle->ChangeStyle(*pStandard, gxApplyNew);
	
	UINT nFontIndex = 0;
	
	if(pStyle->GetIncludeFont())
	{
		nFontIndex = pFTable->GetFontIndex(CGXExcelFontIndex(pStyle->GetFont().GetFontKey(), pStyle->GetIncludeTextColor()?pStyle->GetTextColor():0, nTab));
		
		TRACE1("The font index is: %d\n", nFontIndex);
		TRACE1("The font name is: %s\n", pStyle->GetFont().GetFaceName());
	}
	
	wFormat = pFormatTable->GetExcelIndexForWrite(pStyle);

	// locked bit
	_gxExSetBit(fLocked, 0, 0);
	
	// hidden bit 
	_gxExSetBit(fLocked, 1, 0);

	// style or cell XF
	_gxExSetBit(fLocked, 2, 0);
	
	// the Lotus Bit always 0
	_gxExSetBit(fLocked, 3, 0);
	
	_gxExSetBitEx(fLocked, 4, nStyleIndex);

	// alignment
	// get the alignment
	if(pStyle->GetIncludeHorizontalAlignment())
	{
		switch(pStyle->GetHorizontalAlignment())
		{
		case DT_LEFT:
			_gxExSetBitEx(alc, 0, 0x1);
			break;
		case DT_CENTER:
			_gxExSetBitEx(alc, 0, 0x2);
			break;
		case DT_RIGHT:
			_gxExSetBitEx(alc, 0, 0x3);
			break;
		default:
			_gxExSetBitEx(alc, 0, 0x0);
			break;
		};
	}
	
	// Wrap Text
	if(pStyle->GetIncludeWrapText() && pStyle->GetWrapText())
		_gxExSetBit(alc, 3, 1);
	
	// vertical alignment
	if(pStyle->GetIncludeVerticalAlignment())
	{
		switch(pStyle->GetVerticalAlignment())
		{
		case DT_TOP:
			_gxExSetBitEx(alc, 4, 0x0);
			break;
		case DT_VCENTER:
			_gxExSetBitEx(alc, 4, 0x1);
			break;
		case DT_BOTTOM:
			_gxExSetBitEx(alc, 4, 0x2);
			break;
		default:
			_gxExSetBitEx(alc, 4, 0x0); //Top is used as default
			break;
		};
	}

	// fJustLast (Used only in Far East versions of MS Excel
	_gxExSetBit(alc, 7, 0);

	if(pStyle->GetIncludeFont() && pStyle->GetFont().GetIncludeOrientation())
	{
		long lOrient = pStyle->GetFont().GetOrientation();
		lOrient = lOrient/10;
		_gxExSetBitEx(alc, 8, (unsigned)lOrient); 
	}

	// index to the color palette for the foreground/background color of the color pattern
	UINT nColorIndex(0);
	
	UINT nDefColorIndex(0);

	nDefColorIndex = pColorTable->GetColorWriteIndex(::GetSysColor(COLOR_WINDOW));


	if(pStyle->GetIncludeInterior())
	{
			CGXBrush& br = pStyle->GetInterior();
			COLORREF refClr = br.GetColor();
			nColorIndex = pColorTable->GetColorWriteIndex(refClr);
			_gxExSetBitEx(icvFore, 0, nColorIndex);
		
			COLORREF refBk = br.GetBkColor();
			
			nColorIndex = pColorTable->GetColorWriteIndex(refBk);
			
			WORD wPattern = 0;

			if(br.GetStyle() == BS_PATTERN)
				wPattern = (WORD) TranslatePattern(br.GetPattern(), FALSE);
			else if(nDefColorIndex != pColorTable->GetColorWriteIndex(refClr))
				wPattern = 1;

			_gxExSetDWBitEx(icvTop, 26, wPattern);

			_gxExSetBitEx(icvFore, 7, nColorIndex);
	}

	GXBorderType borders[] = {gxBorderTop, gxBorderLeft, gxBorderBottom, gxBorderRight};
			
	for (UINT n(0) ; n < sizeof(borders) / sizeof(GXBorderType); n++)
	{
		if(pStyle->GetIncludeBorders(borders[n]) && (pStyle->GetBorders(borders[n]).GetStyle() != PS_NULL))
		{
			CGXPen& pen = pStyle->GetBorders(borders[n]);
			_gxExSetBit(cIndent, 13, 1); // set the include bit for the borders
			
			switch(borders[n])
			{
				case gxBorderTop:
					_gxExSetBitEx( dgLeft, 8, GetPenStyle(pen) );			
					_gxExSetDWBitEx( icvTop, 0, pColorTable->GetColorWriteIndex(pen.GetColor()) );
					break;
				case gxBorderLeft:
					_gxExSetBitEx( dgLeft, 0, GetPenStyle(pen) );			
					_gxExSetBitEx( icvLeft, 0, pColorTable->GetColorWriteIndex(pen.GetColor()) );
					break;
				case gxBorderBottom:
					_gxExSetBitEx( dgLeft, 12, GetPenStyle(pen) );			
					_gxExSetDWBitEx( icvTop, 7, pColorTable->GetColorWriteIndex(pen.GetColor()) );
					break;
				case gxBorderRight:
					_gxExSetBitEx( dgLeft, 4, GetPenStyle(pen) );			
					_gxExSetBitEx( icvLeft, 7, pColorTable->GetColorWriteIndex(pen.GetColor()) );
					break;
				default:
					ASSERT(0);
					// Invalid border value
			}	
		}
	}

	_gxExSetBitEx( icvLeft, 14, 0x00);

	// reserved and pivot table (14 and 15)
	_gxExSetBit(icvFore, 14, 0);
	_gxExSetBit(icvFore, 15, 0);
	
	_gxExSetDWBitEx(icvTop, 25, 0);
	
	// now write the data to the buffer
	_gxdata(wr)
		_gxw(nFontIndex) // 2
		_gxw(wFormat) // 2
		_gxw(fLocked) //2
		_gxw(alc) //2
		_gxw(cIndent) // 2
		_gxw(dgLeft) // 2
		_gxw(icvLeft) // 2
		_gxdw(icvTop) // 4
		_gxw(icvFore) // 2
	_gxend

	/// Total ---> 24 Bytes for CELL XF BIFF 8

	_gxExWrite(wr, pszBuffer);
	// done

	if(pStyle)
		delete pStyle;
}


void CGXExcelXFTable::TranslateStyleToXF(const CGXStyle* pStyle, BYTE* pszBuffer, BOOL bStyle /* = TRUE */, const CGXStylesMap* pStylesMap /* = NULL */, BOOL bStandardStyle /*= FALSE*/, UINT nTab)
{
	if (bStyle)
		TranslateStyleToStyleXF(pStyle, pszBuffer, pStylesMap);
	else
		TranslateStyleToCellXF(pStyle, pszBuffer, pStylesMap, bStandardStyle, nTab);
}


BOOL CGXExcelXFTable::ApplyToObject(DWORD index, CGXStyle*& pStyle)
{
	XFStruct* pXFStruct = NULL;
	
	// will allocate a style object if required
	_base::ApplyToObject(index, pStyle);

	if( !LookupValue(index, pXFStruct))
		return FALSE;

	if( ( (pXFStruct->fLocked & 0x0004) >> 2) == 1)
		StyleHelper(pXFStruct, pStyle);
	else
		CellHelper(pXFStruct, pStyle);
	
	return TRUE;
}


BOOL CGXExcelXFTable::StyleHelper(XFStruct* pXFStruct, CGXStyle* pStyle)
{
	ASSERT(pXFStruct != NULL);
	ASSERT(pStyle != NULL);
	
	CGXExcelFontTable* pTable = (CGXExcelFontTable*) GXExGetTableMap()->LocateHandler(typeFont);

	ASSERT(pTable != NULL);

	BOOL b(TRUE);

	// use the font index to apply the font
	WORD wFontIndex = pXFStruct->ifnt >= 4 ? pXFStruct->ifnt - 1:pXFStruct->ifnt; 
	b = b && (pTable->ApplyToObject(wFontIndex, pStyle));
	
	//Apply format
	CGXExcelFormatTable* pFormatTable = (CGXExcelFormatTable*) GXExGetTableMap()->LocateHandler(typeFormat);
	ASSERT(pFormatTable != NULL);
	b = b && (pFormatTable->ApplyToObject(pXFStruct->ifmt, pStyle));

	// ignore the hidden flag for the cell
	_gxlog("Hidden flag ignored\n");

	// Lock setting ignored
	_gxlog("Lock setting ignored\n");
	
	//ignore Lotus 123 stuff
	_gxlog("Lotus 123 stuff ignored\n");

	// Handle parent XF record. This is always ixfNULL for Style Records
	ASSERT ( (pXFStruct->fLocked & 0xFFF0) >> 4 == ixfNULL);
		
	
	// horizontal alignment
	switch(pXFStruct->alc & 0x0007)
	{
	case 0:
		_gxlog("Default alignment used\n");
		break;
	case 1:
		pStyle->SetHorizontalAlignment(DT_LEFT);
		break;
	case 2:
		pStyle->SetHorizontalAlignment(DT_CENTER);
		break;
	case 3:
		pStyle->SetHorizontalAlignment(DT_RIGHT);
		break;
	default:
		_gxlog("Default alignment used. Unsupported alignment specified. Value:\n");
		_gxlnumt(pXFStruct->alc & 0x0007);
		break;
		;
	};

	if(pXFStruct->alc & 0x0008)
		pStyle->SetWrapText(TRUE);
	
	// vertical alignment
	switch( (pXFStruct->alc & 0x0070) >> 4)
	{
	case 0:
		pStyle->SetVerticalAlignment(DT_TOP);
		break;
	case 1:
		pStyle->SetVerticalAlignment(DT_VCENTER);
		break;
	case 2:
		pStyle->SetVerticalAlignment(DT_BOTTOM);
		break;
	default:
		_gxlog("Unsupported vertical alignment. Value:\n");
		_gxlnumt(pXFStruct->alc & 0x0070);
		break;
	};

	//orientation
	WORD wOrient = (pXFStruct->alc & 0xFF00) >> 8;
	
	pStyle->SetFont(CGXFont().SetOrientation(wOrient));
		
	CGXExcelColorTable* pColorTable = (CGXExcelColorTable*) GXExGetTableMap()->LocateHandler(typePalette);

	ASSERT(pColorTable != NULL);

	WORD wPat = (unsigned) (pXFStruct->icvTop & 0xFC000000) >> 26;

	{
		// fore color for the pattern
		WORD dwForeIndex = pXFStruct->icvFore & 0x007F;

		_gxadjustPalette(dwForeIndex);

		// back color for the pattern
		WORD dwBackIndex = (pXFStruct->icvFore & 0x3f80) >> 7;

		_gxadjustPalette(dwBackIndex);

		if( pStyle->GetIncludeInterior() )
		{
			if(wPat && wPat != 1)
				pStyle->GetInterior().SetPattern(TranslatePattern(wPat));

			pStyle->SetInterior( pStyle->GetInterior()
													.SetBkColor(pColorTable->GetColorAtPalIndex(dwBackIndex))
													.SetColor(pColorTable->GetColorAtPalIndex(dwForeIndex))
													);
		}
		else
		{
			
			pStyle->SetInterior( CGXBrush()
										   .SetBkColor(pColorTable->GetColorAtPalIndex(dwBackIndex))
										   .SetColor(pColorTable->GetColorAtPalIndex(dwForeIndex))
										   );
			
			if(wPat && wPat != 1) // this corresponds to no Pattern
				pStyle->GetInterior().SetPattern(TranslatePattern(wPat));

		}
	}

	CGXPen pen;
	WORD wPenColorIndex(0);
	
	// now apply the borders
	WORD wBottom((pXFStruct->dgLeft & 0xF000) >> 12),
		 wLeft(pXFStruct->dgLeft & 0x000F), 
		 wTop((pXFStruct->dgLeft & 0x0F00) >> 8),
		 wRight((pXFStruct->dgLeft & 0x00F0) >> 4); 
	
	WORD clrBottom( (unsigned)(pXFStruct->icvTop & 0x00003F80) >> 7),
		 clrLeft(pXFStruct->icvLeft & 0x007f),
		 clrTop((unsigned)pXFStruct->icvTop & 0x0000007F), 
		 clrRight((unsigned)(pXFStruct->icvTop & 0x3f80) >> 7); 

	//bottom
	if(wBottom)
	{
		SetPenStyle(wBottom, pen);
		wPenColorIndex = clrBottom;
		_gxadjustPalette(wPenColorIndex);
		pen.SetColor(pColorTable->GetColorAtPalIndex(wPenColorIndex));
		pStyle->SetBorders(gxBorderBottom, pen);
	}

	memset(&pen, 0, sizeof(CGXPen));

	//top
	if(wTop)
	{
		CGXPen* pPenTop = new(&pen) CGXPen();
		SetPenStyle(wTop, pen);
		wPenColorIndex = clrTop;
		_gxadjustPalette(wPenColorIndex);
		pPenTop->SetColor(pColorTable->GetColorAtPalIndex(wPenColorIndex));
		pStyle->SetBorders(gxBorderTop, *pPenTop);
	}

	//left
	memset(&pen, 0, sizeof(CGXPen));
	
	if(wLeft)
	{
		CGXPen* pPenLeft = new(&pen) CGXPen();
		SetPenStyle(wLeft, pen);
		wPenColorIndex = clrLeft;
		_gxadjustPalette(wPenColorIndex);
		pPenLeft->SetColor(pColorTable->GetColorAtPalIndex(wPenColorIndex));
		pStyle->SetBorders(gxBorderLeft, *pPenLeft);
	}

	//right
	if(wRight)
	{
		memset(&pen, 0, sizeof(CGXPen));
		CGXPen* pPenRight = new(&pen) CGXPen();
		SetPenStyle(wRight, pen);
		wPenColorIndex = clrRight;
		_gxadjustPalette(wPenColorIndex);
		pPenRight->SetColor(pColorTable->GetColorAtPalIndex(wPenColorIndex));
		pStyle->SetBorders(gxBorderRight, *pPenRight);
	}
	
	return b;
}


BOOL CGXExcelXFTable::CellHelper(XFStruct* pXFStruct, CGXStyle* pStyle)
{
	ASSERT(pXFStruct != NULL);
	ASSERT(pStyle != NULL);
	
	CGXExcelFontTable* pTable = (CGXExcelFontTable*) GXExGetTableMap()->LocateHandler(typeFont);

	ASSERT(pTable != NULL);

	// some boolean flags used for optimization
	BOOL bfmt(FALSE), bfnt(FALSE), bAlcWrap(FALSE), bBdr(FALSE), bPat(FALSE);

	// if any of these flags are set then the corresponding modifiers are the same as in the base class
	// and need not be applied again
	if( (pXFStruct->cIndent & 0x0400) >> 10)	
		bfmt = TRUE;
	
	if( (pXFStruct->cIndent & 0x0800) >> 11)	
		bfnt = TRUE;
	
	if( (pXFStruct->cIndent & 0x1000) >> 12)	
		bAlcWrap = TRUE;
	
	if( (pXFStruct->cIndent & 0x2000) >> 13)
		bBdr = TRUE;
	
	if( (pXFStruct->cIndent & 0x4000) >> 14)
		bPat = TRUE;

	BOOL b(TRUE);
	// use the font index to apply the font
	if(bfnt)
		b = b && (pTable->ApplyToObject( (pXFStruct->ifnt) ? pXFStruct->ifnt-1 : pXFStruct->ifnt, pStyle));
	

	TRACE1("The font index is %x\n", pXFStruct->ifnt);

	
	//Apply format
	CGXExcelFormatTable* pTableFormat = (CGXExcelFormatTable*) GXExGetTableMap()->LocateHandler(typeFormat);

	ASSERT(pTableFormat != NULL);

	// use the index to apply the format to the style
	if(bfmt)
		b = b && (pTableFormat->ApplyToObject(pXFStruct->ifmt, pStyle) );
	
	TRACE1("The format index is %x\n", pXFStruct->ifmt);

	_gxlog("Ignoring the hidden/locked flag for the cell\n");
	_gxlog("Ignoring 123 stuff\n");

	// Handle parent XF record
		// check if normal style
		// else use ApplyToObject to apply to this style
	CGXExcelXFTable* pTableXF = (CGXExcelXFTable* ) GXExGetTableMap()->LocateHandler(typeXF);
	
	CGXExcelStyleTable* pStyleTable = (CGXExcelStyleTable*) GXExGetTableMap()->LocateHandler(typeStyle);

	ASSERT(pTableXF != NULL);

	ASSERT(pStyleTable != NULL);

	// use the index to apply the format to the style
	// compose the base style
	// If this is zero this would have been applied as part of the standard style
	if((pXFStruct->fLocked & 0xFFF0) >> 4 != 0 && ((pXFStruct->fLocked & 0xFFF0) >> 4) != 0x0FFF)
	{
		// get the base style ID based on the XF index
		WORD wId = pStyleTable->GetBaseStyleID((pXFStruct->fLocked & 0xFFF0) >> 4);
		
		// ASSERT(wId != NULL);
		
		if(wId != NULL)
			pStyle->SetBaseStyle(wId);
	}

	// horizontal alignment
	if(bAlcWrap)
	{
		switch(pXFStruct->alc & 0x0007)
		{
		case 0:
			//do nothing
			break;
		case 1:
			pStyle->SetHorizontalAlignment(DT_LEFT);
			break;
		case 2:
			pStyle->SetHorizontalAlignment(DT_CENTER);
			break;
		case 3:
			pStyle->SetHorizontalAlignment(DT_RIGHT);
			break;
		default:
			_gxlog("Unsupported horizontal alignment value. Value: ");
			_gxlnumt(pXFStruct->alc & 0x0007);
			break;
		};
	}

	if(bAlcWrap && pXFStruct->alc & 0x0008)
		pStyle->SetWrapText(TRUE);
	

	// vertical alignment
	switch( (pXFStruct->alc & 0x0070) >> 4)
	{
	case 0:
		pStyle->SetVerticalAlignment(DT_TOP);
		break;
	case 1:
		pStyle->SetVerticalAlignment(DT_VCENTER);
		break;
	case 2:
		pStyle->SetVerticalAlignment(DT_BOTTOM);
		break;
	default:
		_gxlog("Unsupported vertical alignment value. Value: ");
		_gxlnumt(pXFStruct->alc & 0x0070);
		break;
	};

	// fJustLast is ignored
	WORD wOrient = ((pXFStruct->alc & 0xFF00) >> 8) * 10;
	
	pStyle->SetFont(CGXFont().SetOrientation(wOrient));
	

	CGXExcelColorTable* pColorTable = (CGXExcelColorTable*) GXExGetTableMap()->LocateHandler(typePalette);

	ASSERT(pColorTable != NULL);

	// check if there are patterns
	if(bPat)
	{
		// fore color for the pattern
		WORD dwForeIndex = pXFStruct->icvFore & 0x007F;

		_gxadjustPalette(dwForeIndex);
		
		// back color for the pattern
		WORD dwBackIndex = (pXFStruct->icvFore & 0x3f80) >> 7;

		_gxadjustPalette(dwBackIndex);

		WORD wPattern = (unsigned)(pXFStruct->icvTop & 0xFC000000) >> 26;

		TRACE1("Pattern specified %d\n", wPattern);
		
		if( pStyle->GetIncludeInterior() )
		{
			pStyle->SetInterior( pStyle->GetInterior()
														  .SetBkColor(pColorTable->GetColorAtPalIndex(dwBackIndex))
														  .SetColor(pColorTable->GetColorAtPalIndex(dwForeIndex))
														  );
			if(wPattern && wPattern != 1) // this corresponds to no Pattern
				pStyle->GetInterior().SetPattern(TranslatePattern(wPattern));
		}
		else
		{
			pStyle->SetInterior( CGXBrush()
											   .SetBkColor(pColorTable->GetColorAtPalIndex(dwBackIndex))
											   .SetColor(pColorTable->GetColorAtPalIndex(dwForeIndex))
											   );
			if(wPattern && wPattern != 1) // this corresponds to no Pattern
				pStyle->GetInterior().SetPattern(TranslatePattern(wPattern));
		}
	}

	
	
	CGXPen pen;
	WORD wPenColorIndex(0);
	
	// now apply the borders
	//bottom
	if(bBdr)
		SetPenStyle( (pXFStruct->dgLeft & 0xF000) >> 12, pen);
	else
		pen.SetStyle(PS_NULL);

	if(bPat)
	{
		wPenColorIndex = (unsigned)(pXFStruct->icvTop & 0x00003F80) >> 7; 
		_gxadjustPalette(wPenColorIndex);
		pen.SetColor(pColorTable->GetColorAtPalIndex(wPenColorIndex));
	}

	if(bBdr)
		pStyle->SetBorders(gxBorderBottom, pen);
	memset(&pen, 0, sizeof(CGXPen));

	//top
	CGXPen* pPenTop = new(&pen) CGXPen();
	if(bBdr)
		SetPenStyle( (pXFStruct->dgLeft & 0x0F00) >> 8, pen);
	else
		pPenTop->SetStyle(PS_NULL);

	if(bPat)
	{
		wPenColorIndex = (unsigned) pXFStruct->icvTop & 0x0000007F; 
		_gxadjustPalette(wPenColorIndex);
		pPenTop->SetColor(pColorTable->GetColorAtPalIndex(wPenColorIndex));
	}
	
	if(bBdr)
		pStyle->SetBorders(gxBorderTop, *pPenTop);
	
	//left
	memset(&pen, 0, sizeof(CGXPen));
	CGXPen* pPenLeft = new(&pen) CGXPen();
	if(bBdr)
		SetPenStyle(pXFStruct->dgLeft & 0x000F, pen);
	else
		pPenLeft->SetStyle(PS_NULL);

	if(bPat)
	{
		wPenColorIndex = pXFStruct->icvLeft & 0x007F; 
		_gxadjustPalette(wPenColorIndex);
		pPenLeft->SetColor(pColorTable->GetColorAtPalIndex(wPenColorIndex));
	}
	
	if(bBdr)
		pStyle->SetBorders(gxBorderLeft, *pPenLeft);
	
	//right
	memset(&pen, 0, sizeof(CGXPen));
	CGXPen* pPenRight = new(&pen) CGXPen();
	if(bBdr)
		SetPenStyle( (pXFStruct->dgLeft & 0x00F0) >> 4, pen);
	else
		pPenRight->SetStyle(PS_NULL);

	if(bPat)
	{
		wPenColorIndex = (pXFStruct->icvLeft & 0x3F80) >> 7; 
		_gxadjustPalette(wPenColorIndex);
		pPenRight->SetColor(pColorTable->GetColorAtPalIndex(wPenColorIndex));
	}

	if(bBdr)
		pStyle->SetBorders(gxBorderRight, *pPenRight);
	
	return b;
}

// This helper function translates the Excel border style to a compatible grid border style and vice versa
BOOL CGXExcelXFTable::SetPenStyle(WORD wStyle, CGXPen& pen)
{
	switch (wStyle)
	{
			case 0:
				pen.SetStyle(PS_NULL);
				break;
			case 1:
				pen.SetStyle(PS_SOLID);
				pen.SetWidth(1);
				break;
			case 2:
				pen.SetStyle(PS_SOLID);
				pen.SetWidth(2);
				break;
			case 3:
				pen.SetWidth(1);
				pen.SetStyle(PS_DASH);
				break;
			case 4:
				pen.SetWidth(1);
				pen.SetStyle(PS_DOT);
				break;
			case 5:
				pen.SetWidth(3);
				pen.SetStyle(PS_SOLID);
				break;
			case 6:
				// approximation
				pen.SetWidth(3);
				pen.SetStyle(PS_SOLID);
				break;
			case 7:
				pen.SetWidth(1);
				pen.SetStyle(PS_DOT);
				break;
			case 8:
				pen.SetWidth(1);
				pen.SetStyle(PS_DASH);
				break;
			case 9:
				pen.SetWidth(1);
				pen.SetStyle(PS_DASHDOT);
				break;
			case 10:
				pen.SetWidth(1);
				pen.SetStyle(PS_DASHDOT);
				break;
			case 11:
				pen.SetWidth(1);
				pen.SetStyle(PS_DASHDOTDOT);
				break;
			case 12:
				pen.SetWidth(1);
				pen.SetStyle(PS_DASHDOTDOT);
				break;
			case 13:
				// approximation
				pen.SetWidth(1);
				pen.SetStyle(PS_DASHDOT);
				break;
			
			default:
				pen.SetWidth(1);
				pen.SetStyle(PS_DOT);
				_gxlog("Unsupported pen style. Using defaults. Value: ");
				_gxlnumt(wStyle);
				// return 0;
				// unsupported pen style? ----> version error?		
	}
	
	return TRUE;
}

WORD CGXExcelXFTable::GetDefaultExcelBorder()
{
	return PS_NULL;
}

WORD CGXExcelXFTable::GetDefaultExcelBorderColor()
{
	return 0;
}

// Equivalent Excel border styles as documented in the Excel File format are
// given as comments
WORD CGXExcelXFTable::GetPenStyle(CGXPen& pen)
{
	ASSERT(pen.GetInclude());

	if(!pen.GetInclude())
		return PS_NULL;

	switch (pen.GetStyle())
	{
			case PS_DOT:
				return 4; // Dotted
				break;
			case PS_SOLID:
				
				if(pen.GetWidth() == 1)
					return 1; // thin
				else if (pen.GetWidth() == 2)
					return 2; // Medium
				else if (pen.GetWidth() == 3)
					return 5; // Thick
					
				return 1; // default is thin
				break;
			case PS_DASH:
				return 3; // Dashed
				break;
			case PS_DASHDOT:
				return 9; // Dotted
				break;
			case PS_NULL:
				return 0; // None
			default:
				ASSERT(0);
				_gxlog("Unsupported pen style. Value: ");
				_gxlnumt(pen.GetStyle());
				return 0;
				// unsupported pen style? ----> version error?		
	}
}

// This function translates the Excel pattern into a grid pattern and vice versa

int CGXExcelXFTable::TranslatePattern(int index, BOOL bToGrid /* = TRUE*/)
{
	if(bToGrid && index)
		index--;

	if(bToGrid) // translate to a grid pattern
		return m_ArrPattern[index];
	else // translate to an Excel pattern
	{
		for (int n(0); n < m_ArrPattern.GetSize(); n++)
		{
			if(m_ArrPattern[n] == index)
				return n + 1;
		}
		
		return 0;
	}
}

ROWCOL CGXExcelXFTable::GetCurrentReadCol()
{
	return m_iCurCol;
}

ROWCOL CGXExcelXFTable::GetCurrentReadRow()
{
	return m_iCurRow;
}

UINT CGXExcelXFTable::GetCurrentReadIndex()
{
	return m_uinTab;
}

void CGXExcelXFTable::SetCurrentReadCol(ROWCOL nCol)
{
	m_iCurCol = nCol;
}

void CGXExcelXFTable::SetCurrentReadRow(ROWCOL nRow)
{
	m_iCurRow = nRow;
}

void CGXExcelXFTable::SetCurrentReadIndex(UINT nIndex)
{
	m_uinTab = nIndex;
}




	



CGXExStyleMap& CGXExcelXFTable::GetExcelStyleMap(UINT index)
{
	ASSERT(m_pArManager != NULL);
	return *(m_pArManager->CreateObject(index));
}
	
CGXExStyleIDMap& CGXExcelXFTable::GetExcelBStyleMap()
{
	return m_mpStyleIDMap;
}

CGXXFArray::CGXXFArray()
{
	// no implementation
}

CGXXFArray::~CGXXFArray()
{
	// no implementation
}

void CGXXFArray::Destroy()
{
	delete this;
}

// CGXXFArrayCreator

CGXXFArray* CGXXFArrayCreator::CreateObject()
{
	return new CGXXFArray;
}

// struct formatStruct

void formatStruct::Cleanup()
{
	ifmt = 0; cch = 0; 
	if(pVarFormat!=NULL)
		delete pVarFormat;
	pVarFormat = NULL;
}

// CGXExcelFormatTable
CGXExcelFormatTable::CGXExcelFormatTable()
{
	// no implementation
}

CGXExcelFormatTable::~CGXExcelFormatTable()
{
	// no implementation
}

/*
FORMAT: Number Format (41Eh)
The FORMAT record describes a number format in the workbook.
All the FORMAT records should appear together in a BIFF file. 
The order of FORMAT records in an existing BIFF file 
should not be changed. You can write custom number formats in a file, 
but they should be added at the end of the existing FORMAT records.
*/

BOOL CGXExcelFormatTable::ReadFromStream(IStream* pStream, DWORD /*dwLength*/)
{
	formatStruct* pFStruct = new formatStruct;	
	
	static GXREADSEEKDATA readData[3];

	readData[0].Init(&pFStruct->ifmt);
	readData[1].Init(&pFStruct->cch);
	
	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 2))

	pFStruct->pVarFormat = new TCHAR[pFStruct->cch+1];

	pFStruct->pVarFormat[pFStruct->cch] = _T('\0');

	readData[2].Init(pFStruct->pVarFormat, pFStruct->cch, gxread); 
	
	GXEX_TRY(ReadSeekHelper(pStream, &readData[2], 1))

	TRACE1("The format is %s", pFStruct->pVarFormat);
		
	m_mapStruct.SetAt(m_dwIndex, pFStruct);
	
	++m_dwIndex;
	
	return TRUE;
}

BOOL CGXExcelFormatTable::WriteToStream(IStream* /*pStream*/, DWORD& /*dwLength*/, CGXGridParam** /*pParam*/, UINT /*nTabs*/)
{
	// we do not write out a format table since we do not have custom format support
	return TRUE;
}

COLORREF CGXExcelFormatTable::GetDefaultNegativeStateColor()
{
	return RGB(255,0,0); // Red is the default color negative colors
}


WORD CGXExcelFormatTable::GetExcelIndexForWrite(const CGXStyle* pStyle)
{
	WORD wRetval(0);

	if(!pStyle->GetIncludeFormat())
		return 0;

	switch (pStyle->GetFormat())
	{
		case GX_FMT_GEN:
			wRetval = 0;
			break;
		case GX_FMT_FIXED:
		//0.00
			wRetval = 0x02;
			break;
		case GX_FMT_COMMA:
		//#,##0
			if(pStyle->GetIncludePlaces() && pStyle->GetIncludeNegativeStateColor())
				wRetval = 0x26;
			else if(pStyle->GetIncludePlaces())
				wRetval = 0x04;
			else
				wRetval = 0x03;
			break;
		case GX_FMT_DOLLARS:
		//($#,##0_);($#,##0)
			if(pStyle->GetIncludeNegativeStateColor())
				wRetval = 0x06;
			else
				wRetval = 0x05;
		break;
		case GX_FMT_PERCENT:
		//0%
			if(pStyle->GetIncludePlaces())
				wRetval = 0x0A;
			else
				wRetval = 0x09;
			break;
		case GX_FMT_FLOAT:
		//0.00E+00
			wRetval = 0x0B;
			break;
		case GX_FMT_MIXED_FRACTIONS:
			wRetval = 0x0C;
			break;
		case GX_FMT_DATE:
		//m/d/yy
			wRetval = 0x0E;
			break;
		case GX_FMT_DAY_MONTH_YEAR:
		//d-mmm-yy
			wRetval = 0x0F;
			break;
		case GX_FMT_DAY_MONTH:
		//d-mmm
			wRetval = 0x10;
			break;
		case GX_FMT_MONTH_YEAR:
		//mmm-yy
			wRetval = 0x11;
			break;
		case GX_FMT_TIME_HM_AMPM:
		// The time formats are approximate. We do not have the same
		// formats that Excel has
		//h:mm AM/PM
			wRetval = 0x12;
			break;
		case GX_FMT_TIME_HMS_AMPM:
		//h:mm:ss AM/PM
			wRetval = 0x13;
			break;
		case GX_FMT_TIME_HM:
		//h:mm
			wRetval = 0x14;
			break;
		case GX_FMT_TIME:
		//h:mm:ss
			wRetval = 0x15;
			break;
		case GX_FMT_DATETIME:
		//m/d/yy h:mm
			wRetval = 0x16;
			break;
	} 
	
	return wRetval;
}

// We use several approximations here. The formats that we support do not correpond one to one with Excel
// and hence the approximations

BOOL CGXExcelFormatTable::ApplyToObject(DWORD index, CGXStyle*& pStyle)
{
	//formatStruct* pFStruct = NULL;
	
	// we skip the lookup and directly use the index because the lookup only applies for custom formats
	// which we do not currently support
	// if( !LookupValue(index & 0x000F, pFStruct))
	//		return FALSE;

	// To decipher Custom Excel formats and apply data is not supported
	// The present version just ignores custom formats

	switch (index)
	{
		case 0x00:
		//General
			pStyle->SetFormat(GX_FMT_GEN);
			break;
		case 0x01:
		//0
			pStyle->SetFormat(GX_FMT_GEN);
			break;
		case 0x02:
		//0.00
			pStyle->SetFormat(GX_FMT_FIXED);
			pStyle->SetPlaces(2);
			break;
		case 0x03:
		//#,##0
			pStyle->SetFormat(GX_FMT_COMMA);
			break;
		case 0x04:
		//#,##0.00
			pStyle->SetFormat(GX_FMT_COMMA);
			pStyle->SetPlaces(2);
			break;
		case 0x05:
		//($#,##0_);($#,##0)
			pStyle->SetPlaces(2);
			pStyle->SetFormat(GX_FMT_DOLLARS);
			break;
		case 0x06:
		//($#,##0_);[Red]($#,##0)
			// displaying negative values in red
			pStyle->SetNegativeStateColor(GetDefaultNegativeStateColor());
			pStyle->SetPlaces(2);
			pStyle->SetFormat(GX_FMT_DOLLARS);
			break;
		case 0x07:
		//($#,##0.00_);($#,##0.00)
			pStyle->SetFormat(GX_FMT_DOLLARS);
			pStyle->SetPlaces(2);
			break;
		case 0x08:
		//($#,##0.00_);[Red]($#,##0.00)
			pStyle->SetNegativeStateColor(GetDefaultNegativeStateColor());
			pStyle->SetFormat(GX_FMT_DOLLARS);
			pStyle->SetPlaces(2);
			break;
		case 0x09:
		//0%
			pStyle->SetFormat(GX_FMT_PERCENT);
			break;
		case 0x0a:
		//0.00%
			pStyle->SetFormat(GX_FMT_PERCENT);
			pStyle->SetPlaces(2);
			break;
		case 0x0b:
		//0.00E+00
			pStyle->SetFormat(GX_FMT_FLOAT);
			break;
		case 0x0c:
		//# ?/?
			pStyle->SetFormat(GX_FMT_MIXED_FRACTIONS);
			break;
		case 0x0d:
		//# ??/??
			pStyle->SetFormat(GX_FMT_MIXED_FRACTIONS);
			break;
		case 0x0e:
		//m/d/yy
			pStyle->SetFormat(GX_FMT_DATE);
			break;
		case 0x0f:
		//d-mmm-yy
			pStyle->SetFormat(GX_FMT_DAY_MONTH_YEAR);
			break;
		case 0x10:
		//d-mmm
			pStyle->SetFormat(GX_FMT_DAY_MONTH);
			break;
		case 0x11:
		//mmm-yy
			pStyle->SetFormat(GX_FMT_MONTH_YEAR);
			break;
		case 0x12:
		// The time formats are approximate. We do not have the same
		// formats that Excel has
		//h:mm AM/PM
			pStyle->SetFormat(GX_FMT_TIME_HM_AMPM);
			break;
		case 0x13:
		//h:mm:ss AM/PM
			pStyle->SetFormat(GX_FMT_TIME_HMS_AMPM);
			break;
		case 0x14:
		//h:mm
			pStyle->SetFormat(GX_FMT_TIME_HM);
			break;
		case 0x15:
		//h:mm:ss
			pStyle->SetFormat(GX_FMT_TIME);
			break;
		case 0x16:
		//m/d/yy h:mm
			pStyle->SetFormat(GX_FMT_DATETIME);
			break;
		case 0x25:
		//(#,##0_);(#,##0)
			pStyle->SetFormat(GX_FMT_COMMA);
			break;
		case 0x26:
		//(#,##0_);[Red](#,##0)
			pStyle->SetFormat(GX_FMT_COMMA);
			pStyle->SetNegativeStateColor(GetDefaultNegativeStateColor());
			break;
		case 0x27:
		//(#,##0.00_);(#,##0.00)
			pStyle->SetFormat(GX_FMT_COMMA);
			pStyle->SetPlaces(2);
			break;
		case 0x28:
		//(#,##0.00_);[Red](#,##0.00)
			pStyle->SetFormat(GX_FMT_COMMA);
			pStyle->SetNegativeStateColor(GetDefaultNegativeStateColor());
			pStyle->SetPlaces(2);
			break;
		case 0x29:
			// approx
		//_(* #,##0_);_(* (#,##0);_(* "-"_);_(@_)
			pStyle->SetFormat(GX_FMT_COMMA);
			break;
		case 0x2a:
			// approx
		//_($* #,##0_);_($* (#,##0);_($* "-"_);_(@_)
			pStyle->SetFormat(GX_FMT_DOLLARS);
			break;
		case 0x2b:
			// approx
		//_(* #,##0.00_);_(* (#,##0.00);_(* "-"??_);_(@_)
			pStyle->SetFormat(GX_FMT_COMMA);
			break;
		case 0x2c:
			// approx
		//_($* #,##0.00_);_($* (#,##0.00);_($* "-"??_);_(@_)
			pStyle->SetFormat(GX_FMT_DOLLARS);
			break;
		case 0x2d:
		//mm:ss
			pStyle->SetFormat(GX_FMT_TIME_HMS_AMPM);
			break;
		case 0x2e:
		//[h]:mm:ss
			pStyle->SetFormat(GX_FMT_TIME_HMS_AMPM);
			break;
		case 0x2f:
		//mm:ss.0
			pStyle->SetFormat(GX_FMT_TIME_HMS_AMPM);
			break;
		case 0x30:
		//##0.0E+0
			pStyle->SetFormat(GX_FMT_FLOAT);
			break;
		case 0x31:
		//@
			pStyle->SetFormat(GX_FMT_GEN);
		break;
	} 
	return TRUE;
}

// struct _sst
_sst::_sst()
{
	pszValue = NULL;
}

_sst::~_sst()
{
	Cleanup();
}

void _sst::Cleanup()
{
	if(pszValue != NULL)
		delete[] pszValue;
	
	pszValue = NULL;
}

// struct sstStruct
sstStruct::sstStruct()
{
	pStrings = NULL;
}

sstStruct::~sstStruct()
{
	Cleanup();
}

void sstStruct::Cleanup()
{
	cstTotal = 0;cstUnique = 0; 
	if(pStrings!=NULL)
	{
		for (UINT nC(0) ; nC < cstUnique; nC++ )
			pStrings[nC].Cleanup();
				
	}

	delete [] pStrings;
		
	pStrings = NULL;
}

// CGXExcelSSTTable
CGXExcelSSTTable::CGXExcelSSTTable()
{
	// no implementation
}

CGXExcelSSTTable::~CGXExcelSSTTable()
{
	// no implementation
}

BOOL CGXExcelSSTTable::ReadFromStream(IStream* pStream, DWORD /*dwLength*/)
{
	// This table supports the continue field. Set the index to 0.
	ResetRecordOffset();

	sstStruct* psstStruct = new sstStruct;	
	static GXREADSEEKDATA readData[7];

	// phase 1
	readData[0].Init(&psstStruct->cstTotal);
	readData[1].Init(&psstStruct->cstUnique);
	
	GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[0], 2, this))

	//phase 2
	_sst*	pStrings = new _sst[psstStruct->cstUnique];
	
	psstStruct->pStrings = pStrings;

	BYTE* pszTemp = NULL;
	
	for (UINT nC(0) ; nC < psstStruct->cstUnique; nC++)
	{
		memset(&readData[2], 0, sizeof(GXREADSEEKDATA));
		memset(&readData[3], 0, sizeof(GXREADSEEKDATA));
		memset(&readData[4], 0, sizeof(GXREADSEEKDATA));
		memset(&readData[5], 0, sizeof(GXREADSEEKDATA));
		memset(&readData[6], 0, sizeof(GXREADSEEKDATA));

		readData[2].Init(&pStrings[nC].cch);
		readData[3].Init(&pStrings[nC].grbit); 
		
		GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[2], 2, this))

		TRACE1("Nc Value: %x\n", nC);
			
		//if(nC == 43)
		//	AfxDebugBreak();

		// display skip. This will be corrected after the beta
		if((pStrings[nC].grbit & 0x04) || (pStrings[nC].grbit & 0x08))
		{
			UINT nFac = ( (pStrings[nC].grbit & 0x01) == 0) ? 1:2;

			if(nFac == 2)
			{
				pStrings[nC].pszValue = new WCHAR[pStrings[nC].cch];
				
				readData[4].Init(&pStrings[nC].wRuns);
				GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[4], 1, this));

				readData[5].Init( (BYTE*)pStrings[nC].pszValue, pStrings[nC].cch*nFac*sizeof(BYTE), gxread); // read the array of bytes
				
				GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[5], 1, this));
				
				// we don't use the formatting
				readData[6].Init((BYTE*)NULL, pStrings[nC].wRuns*GX_EX_SIZEOFRUNSSST, gxseek); // read the array of bytes
				// do a seek now
				GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[6], 1, this));
			
				//if(pStrings[nC].cch)
				//	GXEXDUMP(pStrings[nC].pszValue, 2*pStrings[nC].cch);
			}
			else
			{
				pszTemp = new BYTE[pStrings[nC].cch + 1];
			
				readData[4].Init(&pStrings[nC].wRuns);
				GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[4], 1, this));

				readData[5].Init( (BYTE*)pszTemp, pStrings[nC].cch*nFac*sizeof(BYTE), gxread); // read the array of bytes
				
				GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[5], 1, this));
				
				pStrings[nC].pszValue = _gxexExpandToUnicode(pszTemp, pStrings[nC].cch);

				// we don't use the formatting
				readData[6].Init((BYTE*)NULL, pStrings[nC].wRuns*GX_EX_SIZEOFRUNSSST, gxseek); // read the array of bytes
				// do a seek now
				GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[6], 1, this));
			
				
				if(pStrings[nC].cch)
				{
					pszTemp[pStrings[nC].cch] = '\0';
						GXEXDUMP(pszTemp, pStrings[nC].cch);
					//TRACE1("%s\n", pszTemp);
				}
				
				if(pszTemp)
					delete[] pszTemp;
			
				pszTemp = NULL;
			}
			continue;
		}


		// check grbit to see if these are compressed
		if( (pStrings[nC].grbit & 0x01) == 0)
		{
			pszTemp = new BYTE[pStrings[nC].cch + 1];
			readData[4].Init( (BYTE*)pszTemp, pStrings[nC].cch*sizeof(BYTE), gxread); // read the array of bytes
			
			// read the data
			GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[4], 1, this));

			// expand to a UNICODE string
			pStrings[nC].pszValue = _gxexExpandToUnicode(pszTemp, pStrings[nC].cch);

			if(pStrings[nC].cch)
			{
				pszTemp[pStrings[nC].cch] = '\0';
					GXEXDUMP(pszTemp, pStrings[nC].cch);
				//TRACE1("%s\n", pszTemp);
			}

			if(pszTemp)
				delete[] pszTemp;
			
			pszTemp = NULL;
			
		}
		else
		{
			// This is an uncompressed UNICODE string
			pStrings[nC].pszValue = new WCHAR[pStrings[nC].cch];
			readData[4].Init( (BYTE*)pStrings[nC].pszValue, pStrings[nC].cch*sizeof(WCHAR), gxread); // read the array of bytes
			
			// read the data
			GXEX_TRY(ReadSeekHelperEx<CGXExcelTable>(pStream, &readData[4], 1, this));
		
			//if(pStrings[nC].cch)
				//GXEXDUMP(pStrings[nC].pszValue, 2*pStrings[nC].cch);
				
		}
		
	}
	
	m_mapStruct.SetAt(m_dwIndex, psstStruct);
	
	++m_dwIndex;

	// done
	ResetRecordOffset();

	return TRUE;
}

BOOL CGXExcelSSTTable::WriteToStream(IStream* /*pStream*/, DWORD& /*dwLength*/, CGXGridParam** /*pParam*/, UINT /*nTabs*/)
{
	// this will not be implemented. We will write out data as labels
	return TRUE;
}

BOOL CGXExcelSSTTable::ApplyToObject(DWORD index, CGXStyle*& pStyle)
{
	sstStruct* psstStruct = NULL;
	
	// will allocate a style object if required
	_base::ApplyToObject(0, pStyle);

	if( !LookupValue(0, psstStruct))
		return FALSE;

#ifdef _UNICODE
	pStyle->SetValue(psstStruct->pStrings[index].pszValue);
#else 

	GX_EX_WTMB(psstStruct->pStrings[index].pszValue, psz, CP_ACP, psstStruct->pStrings[index].cch, "CGXExcelSSTTable::ApplyToObject")

	if(psz!=NULL)
	{
		pStyle->SetValue(psz);
		delete [] psz;
	}
#endif
	
	return TRUE;
}

// struct BoundSheetStruct

BoundSheetStruct::BoundSheetStruct()
{
	dwOffsetPos = 0;
	grbit = 0;
	cch = 0;
	pszName = NULL;
}
		
void BoundSheetStruct::Cleanup()
{
	dwOffsetPos = 0;
	grbit = 0;
	cch = 0;
	if(pszName != NULL)
		delete[] pszName;
	
	pszName = NULL;
}

// CGXExcelBoundSheetTable

CGXExcelBoundSheetTable::CGXExcelBoundSheetTable()
{
	m_dwOffsetPos = 0; 
	m_bSeekMode = FALSE;
};

CGXExcelBoundSheetTable::~CGXExcelBoundSheetTable()
{
	// no implementation
}

BOOL CGXExcelBoundSheetTable::ReadFromStream(IStream* pStream,DWORD /*dwLength*/)
{
	static GXREADSEEKDATA readData[4];
	
	BoundSheetStruct* bsStruct = new BoundSheetStruct;	

	readData[0].Init(&bsStruct->dwOffsetPos); //offsetpos
	readData[1].Init(&bsStruct->grbit); //flags
	
	readData[2].Init(&bsStruct->cch); // the length of the string data

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 3))

	TRACE1("BoundSheetHandler: The sheet type is %x\n", bsStruct->grbit);

	if(bsStruct->cch)
	{
		bsStruct->pszName = new TCHAR[bsStruct->cch + 1];
		readData[3].Init(bsStruct->pszName, bsStruct->cch); // read the name of the tab
		GXEX_TRY(ReadSeekHelper(pStream, &readData[3], 1))
		bsStruct->pszName[bsStruct->cch] = _T('\0');
	}

	m_mapStruct.SetAt(m_dwIndex, bsStruct);
	
	++m_dwIndex;
	

	return TRUE;
}


BOOL CGXExcelBoundSheetTable::WriteToStream(IStream* pStream, DWORD& dwLength, CGXGridParam** pParam, UINT nTabs /*= 1*/)
{
	HRESULT hr(S_OK);
	
	if(pParam == NULL)
		throw egxInvalidParam;
	
	if(GetSeekMode() == FALSE)
	{
		// I have to do a seek to get to the correct offset pos
		ASSERT(GetOffsetPos() != NULL); // Error-->Did you initialize the offset pos in your code?
	
		LARGE_INTEGER lit;
		LISet32(lit, GetOffsetPos());
		HRESULT hr = pStream->Seek(lit, STREAM_SEEK_SET, NULL);

		ASSERT(FAILED(hr) == FALSE);

		ASSERT( ((UINT) m_ArOffsetPos.GetSize()) == nTabs); // There should exactly as many offset entries as the number of tabs
	}

	DWORD nRecLen(0);

	// now that the stream is in the correct position get the tab name 
	for (UINT nC(0); nC < nTabs; nC++)
	{
		ASSERT(pParam[nC] != NULL);

		CString strTabName = pParam[nC]->m_sSheetName;

		DWORD dwOffsetPos(0);
		WORD grbit(0);
		WORD cch(0);
		
		if(!strTabName.IsEmpty())
			cch = _tcslen(strTabName);

		if(GetSeekMode())
		{
			nRecLen+= GX_EX_FIXEDOFFSET + GX_EX_FIXED_BSHEET + cch;
			continue;
		}

		dwOffsetPos = m_ArOffsetPos[nC];

		// declare the buffer 
		BYTE* pszBuffer = new BYTE[GX_EX_FIXEDOFFSET + GX_EX_FIXED_BSHEET + cch];
		
		memset(pszBuffer, 0, GX_EX_FIXEDOFFSET + GX_EX_FIXED_BSHEET + cch);
		
		// the grbit bits use the defaults worksheet
		
		// compose the buffer
		_gxdata(wr)
			_gxw(typeBoundSheet)
			_gxw( (GX_EX_FIXED_BSHEET + cch) )
			_gxdw(dwOffsetPos)
			_gxw(grbit)
			_gxw(cch)
			_gxstr(strTabName, cch)
		_gxend

		_gxExWrite(wr, pszBuffer);

		// No write to the stream
		ULONG cb(0);
		GX_EX_WRITE(pStream->Write(pszBuffer, GX_EX_FIXEDOFFSET + GX_EX_FIXED_BSHEET + cch, &cb));
		
		dwLength += cb;

		TRACE0("Dumping data for CGXExcelBoundSheetTable\n");
		GXEXDUMP(pszBuffer, cb)
	
		if(pszBuffer)
			delete[] pszBuffer;
	}

	// If this is in seek mode I will do a simple seek
	if(GetSeekMode())
	{
		LARGE_INTEGER lit;
		LISet32(lit, nRecLen);
		HRESULT hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
		dwLength += nRecLen;
	}

	return TRUE;
}

BOOL CGXExcelBoundSheetTable::ApplyToObject(DWORD index, CString*& pstrTabName)
{
	BoundSheetStruct* bsStruct = NULL;
	
	// will allocate a object if required
	_base::ApplyToObject(index, pstrTabName);

	if( !LookupValue(index, bsStruct))
		return FALSE;

	*pstrTabName = bsStruct->pszName;
	
	return TRUE;
}

BoundSheetStruct* CGXExcelBoundSheetTable::LookupOffsetStruct(DWORD index)
{
	BoundSheetStruct* bsStruct = NULL;
	
	if( !LookupValue(index, bsStruct))
		return FALSE;
	else
		return bsStruct;
}

void CGXExcelBoundSheetTable::ResetInternalState()
{
	_base::ResetInternalState();
	m_ArOffsetPos.RemoveAll();
}

CGXExcelBoundSheetTable::CGXExOffsetArray* CGXExcelBoundSheetTable::GetBOFOffsetArray()
{
	return &m_ArOffsetPos;
}
	
DWORD CGXExcelBoundSheetTable::GetOffsetPos() const
{
	return m_dwOffsetPos;
}

void CGXExcelBoundSheetTable::SetOffsetPos(DWORD dw)
{
	m_dwOffsetPos = dw;
}

BOOL CGXExcelBoundSheetTable::GetSeekMode() const
{
	return m_bSeekMode;
}

void CGXExcelBoundSheetTable::SetSeekMode(BOOL b)
{
	m_bSeekMode = b;
}

// Reading shared formula support

// sfStruct

sfStruct::sfStruct()
{
	rwFirst = 0;
	rwLast = 0;
	colFirst = 0;
	colLast = 0;
	cce = 0;
	pVar = NULL;
}

void sfStruct::Cleanup()
{
	rwFirst = 0;
	rwLast = 0;
	colFirst = 0;
	colLast = 0;
	cce = 0;
	
	if(pVar != NULL)
		delete pVar;

	pVar = NULL;
}


// CGXExcelSharedFormulaTable

CGXExcelSharedFormulaTable::CGXExcelSharedFormulaTable()
{
	m_dwIndex = ULONG_MAX; // This is a special index that is composed from
	// row and column values. We set this to a high value so that checks for
	// invalid indexes do not catch this one.
}

CGXExcelSharedFormulaTable::~CGXExcelSharedFormulaTable()
{
	// no implementation
}

BOOL CGXExcelSharedFormulaTable::ReadFromStream(IStream* pStream,DWORD dwLength)
{
	static GXREADSEEKDATA readData[7];
	
	sfStruct* p = new sfStruct;

	readData[0].Init(&p->rwFirst); // rwFirst 2
	readData[1].Init(&p->rwLast); //rwLast 2
	
	readData[2].Init(&p->colFirst); // colFirst 1
	readData[3].Init(&p->colLast); // colLast 1

	readData[4].Init((BYTE*)NULL, sizeof(WORD), gxseek); // ignore the reserved value

	readData[5].Init(&p->cce); // the length of the binary data that follows 2

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 6))

	TRACE0("CGXExcelSharedFormulaTable read from Stream\n");

	ASSERT(p->cce != 0); // there has to be data in shared formula structure

	if(p->cce)
	{
		p->pVar = new BYTE[p->cce];
		readData[6].Init(p->pVar, p->cce); // read the binary data
		GXEX_TRY(ReadSeekHelper(pStream, &readData[6], 1))
	}
	
	m_mapStruct.SetAt(dwLength, p);
	
	return TRUE;
}

DWORD CGXExcelSharedFormulaTable::GetCompositeIndex(WORD nRow, WORD nCol)
{
	DWORD dwRow = nRow;
	DWORD dwCol = nCol;

	DWORD dwIndex = dwRow | (dwCol << 16);
	
	return dwIndex;
}

BOOL CGXExcelSharedFormulaTable::WriteToStream(IStream* /*pStream*/, DWORD& /*dwLength*/, CGXGridParam** /*pParam*/, UINT /*nTabs*/ /*= 1*/)
{
	//ASSERT(0); 
	// Incorrect call. We do not write shared formulas at all.
	// The Excel SDK does not recommend this. Shared formulas are only used 
	// when Excel does the write as an optimization.
	return TRUE;
}


BOOL CGXExcelSharedFormulaTable::ApplyToObject(DWORD index, formulaStruct*& pFS)
{
	ASSERT(pFS != NULL); // pFS cannot be NULL. Unlike other tables
	// this table supplements the value that is stored in formulsStruct.
	// In the absence of this value the information becomes meaningless.
	
	if(pFS == NULL)
		return FALSE;

	sfStruct* p = NULL;
	if( !LookupValue(index, p))
		return FALSE;

	BYTE* pVarCpy = new BYTE[p->cce ];
	
	ASSERT(pVarCpy != NULL);

	memcpy(pVarCpy, p->pVar, p->cce);

	BYTE* pCOrig = pVarCpy;

	// apply p onto pFS

	WORD cch(0); 
	//WORD iftab(0); 
	//WORD cargs(0);
	//gxFormulaState	fs;
	
	// now apply the ptg changes
	DWORD dwC(0);
	do
	{
		switch (*pVarCpy)
		{
			case 0:
				dwC += 1;
				break;

			case ptgStr :
				cch = *(pVarCpy + 1);
				pVarCpy += cch+2;
				dwC += cch+2;
				break;

			case ptgBool :
				pVarCpy += 3;
				dwC += 3;
				break;

			case ptgInt :
				pVarCpy += 3;
				dwC += 3;
				break;

			case ptgNum :
				pVarCpy += 9;
				break;

			case ptgParen :
				pVarCpy += 1;
				dwC += 1;
				break;

			case ptgRef :
			case ptgRefV :
				pVarCpy += 5;
				dwC += 5;
				break;

			case ptgArea :
			case ptgAreaV :
			case ptgAreaA :
				pVarCpy += 9;
				dwC += 9;
				break;
			
			//
			case ptgRefN :
				{
					*pVarCpy = ptgRef;
					
					if(*((WORD*)(pVarCpy+3)) & 0x8000)
						*((WORD*)(pVarCpy+1)) += pFS->rw;
					
					if(*((WORD*)(pVarCpy+3)) & 0x4000)
						*((BYTE*)(pVarCpy+3)) += pFS->col;
					
					pVarCpy += 5;
					dwC += 5;
					break;
				}
			//
			case ptgRefNV :
				{
					GXEXDUMP(pVarCpy, 5)
					*pVarCpy = ptgRefV;
					
					if(*((WORD*)(pVarCpy+3)) & 0x8000)
						*((WORD*)(pVarCpy+1)) += pFS->rw;
					
					if(*((WORD*)(pVarCpy+3)) & 0x4000)
						*((BYTE*)(pVarCpy+3)) += pFS->col;
					
					GXEXDUMP(pVarCpy, 5)
					pVarCpy += 5;
					dwC += 5;
					break;
				}
			//
			case ptgAreaN :
				{
					GXEXDUMP(pVarCpy, 0x0d)
					*pVarCpy = ptgArea;
					*((WORD*)(pVarCpy+1)) += pFS->rw;
					*((WORD*)(pVarCpy+3)) += pFS->rw;
					
					WORD w = (*((WORD*)(pVarCpy+5))) & 0xC000; 
					(*((WORD*)(pVarCpy+5))) = (*((WORD*)(pVarCpy+5))) & 0x3FFF;
					*((WORD*)(pVarCpy+5)) += pFS->col;
					(*((WORD*)(pVarCpy+5))) = (*((WORD*)(pVarCpy+5))) | w;

					w = (*((WORD*)(pVarCpy+7))) & 0xC000; 
					(*((WORD*)(pVarCpy+7))) = (*((WORD*)(pVarCpy+7))) & 0x3FFF;
					*((WORD*)(pVarCpy+7)) += pFS->col;
					(*((WORD*)(pVarCpy+7))) = (*((WORD*)(pVarCpy+7))) | w;

					
					GXEXDUMP(pVarCpy, 10)
					pVarCpy += 9;
					dwC += 9;
					break;
				}
			case ptgAreaNV :
				*pVarCpy = ptgAreaN;
				*((WORD*)(pVarCpy+1)) += pFS->rw;
				*((BYTE*)(pVarCpy+5)) += pFS->col;
				pVarCpy += 7;
				dwC += 7;
				break;
			
			case ptgErr :
				pVarCpy += 2;
				dwC += 2;
				break;
			
			case ptgRefErr :
			case ptgRefErrV :
				pVarCpy += 4;
				dwC += 4;
				break;

			case ptgAreaErr :
			case ptgAreaErrV :
				pVarCpy += 7;
				dwC += 7;
				break;

			case ptgFunc :
			case ptgFuncV :
				pVarCpy += 3;
				dwC += 3;
				break;

			case ptgFuncVar :
			case ptgFuncVarV :
				pVarCpy += 4;
				dwC += 4;
				break;

			case ptgUplus :		pVarCpy += 1; dwC += 1; break;
			
			case ptgUminus :	pVarCpy += 1; dwC += 1;  break;
			
			case ptgPercent :	pVarCpy += 1; dwC += 1;  break;

			case ptgConcat :	pVarCpy += 1; dwC += 1;  break;
			
			case ptgIsect :		pVarCpy += 1; dwC += 1;  break;

			case ptgRange :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgAdd :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgSub :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgMul :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgDiv :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgPower :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgLT :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgLE :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgEQ :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgGE :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgGT :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgNE :		pVarCpy += 1; dwC += 1;  break;
			
			case ptgAttr:
				pVarCpy += 4;
				dwC += 4;
				break;

			default :
				// if we are unable to recognize a ptg return FALSE.
				{
					if (pCOrig != NULL)
						delete[] pCOrig;
					return FALSE;
				}
		}
	}
	while(dwC < p->cce);

	pFS->cce = p->cce;
	
	if(pFS->pVarParsed != NULL)
		delete pFS->pVarParsed;
	
	pFS->pVarParsed = pCOrig;

	// end apply	
	return TRUE;
}


BOOL CGXExcelSharedFormulaTable::ApplyToObject(WORD nRow, WORD nCol, formulaStruct*& pFS)
{
	DWORD dwRow = nRow;
	DWORD dwCol = nCol;
	
	// get the look up index
	DWORD dwIndex = dwRow | (dwCol << 16);

	return ApplyToObject(dwIndex, pFS);
}

BOOL CGXExcelSharedFormulaTable::LookupSharedFormula(WORD nRow, WORD nCol)
{
	DWORD dwRow = nRow;
	DWORD dwCol = nCol;
	
	// get the look up index
	DWORD dwIndex = dwRow | (dwCol << 16);
	
	sfStruct* p = NULL;
	return LookupValue(dwIndex, p);
}

void CGXExcelSharedFormulaTable::ResetInternalState()
{
	_base::ResetInternalState();
	
	m_dwIndex = ULONG_MAX; // This is a special index that is composed from
	// row and column values. We set this to a high value so that checks for
	// invalid indexes do not catch this one.
}


template<>
UINT AFXAPI HashKey(const CGXExcelFontIndex& key)
{
	return (((UINT)(void*)(DWORD)key.byte8) >> 4) +
		(((UINT)(void*)(DWORD)key.colorIndex) >> 4) +
		key.nTabIndex;
}

