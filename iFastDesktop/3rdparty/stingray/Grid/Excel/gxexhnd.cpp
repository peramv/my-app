///////////////////////////////////////////////////////////////////////////////
// gxexhnd.cpp
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

#pragma warning(disable: 4244)


CGXExcelLogger* CGXExcelHandler::s_pLogger = NULL;

BOOL CGXExcelHandler::m_bCanLog = FALSE;
BOOL CGXExcelHandler::m_bClipMode = FALSE;
BOOL CGXExcelHandler::m_bOptimized = FALSE;

IMPLEMENT_DYNAMIC(CGXExcelHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelLabelHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelRkHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelMulRkHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelColInfoHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelRowHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelFormulaHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelBOFHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelBlankHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelMulBlankHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelLabelSSTHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelDimensionHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelWindow2Handler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelMergedCellsHandler, CObject)
IMPLEMENT_DYNCREATE(CGXExcelNumberHandler, CObject)


// Function name	: ReadSeekHelper
// Description	    : helper for reading and seeking given an IStream
// Return type		: BOOL 
// Argument         : IStream* pStream
// Argument         : GXREADSEEKDATA* pReadSeekData
// Argument         : DWORD cNum
// throws READSEEKEXCEP

UINT nReadSeekOffset(0);

UINT GXExGetReadSeekOffset()
{
	return nReadSeekOffset;
}

UINT& GXExGetReadSeekOffsetRef()
{
	return nReadSeekOffset;
}


void GXExSetReadSeekOffset(UINT nOffset)
{
	nReadSeekOffset = nOffset;
}


BOOL ReadSeekHelper(IStream* pStream, GXREADSEEKDATA* pReadSeekData, DWORD cNum)
{
	ASSERT(pReadSeekData != NULL); //---->Invalid data sent

	HRESULT hr = S_OK;
	ULONG ulRead(0);
	void* pVoid = NULL;

	for (DWORD dw = 0; dw < cNum ; dw++)
	{
		ASSERT(pReadSeekData->op == gxread || pReadSeekData->op == gxseek);

		if(pReadSeekData->op == gxread)
		{
			pVoid = ResolveReadSeekData(pReadSeekData); 
		
			hr = pStream->Read(pVoid, pReadSeekData->dwSize, &ulRead);
			GXExGetReadSeekOffsetRef() += ulRead;
		}
		else
		{
			LARGE_INTEGER lit;
			LISet32(lit, pReadSeekData->dwSize);
			hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
			GXExGetReadSeekOffsetRef() += pReadSeekData->dwSize;
		}
		
		if(FAILED(hr))
		{
			TRACE0("Warning: Unable to read from stream!");
			throw new READSEEKEXCEP(hr, dw);
		}
		
		pReadSeekData ++;

	}

	return TRUE;
}


// Function name	: ResolveReadSeekData
// Description	    : Resolve the seek/read data to the correct member of the union
// based on the type
// Return type		: void* 
// Argument         : GXREADSEEKDATA* pReadSeekData
void* ResolveReadSeekData(GXREADSEEKDATA* pReadSeekData)
{
	void* pVoid = NULL;
	switch(pReadSeekData->type)
	{
		case gx_Word:
			{
				pVoid = pReadSeekData->pwData;
				break;
			}
		case gx_Long:
			{
				pVoid = pReadSeekData->plData;
				break;
			}
		case gx_Bool:
			{
				pVoid = pReadSeekData->pbData;
				break;
			}
		case gx_Dword:
			{
				pVoid = pReadSeekData->pdwData;
				break;
			}
		case gx_Short:
			{
				pVoid = pReadSeekData->psiData;
				break;
			}
		case gx_Int:
			{
				pVoid = pReadSeekData->piData;
				break;
			}
		case gx_Byte:
			{
				pVoid = pReadSeekData->pbyData;
				break;
			}
		case gx_Tchar:
			{
				pVoid = pReadSeekData->pszData;
				break;
			}
		case gx_Double:
			{
				pVoid = pReadSeekData->pDData;
				break;
			}
		default:
			{
				ASSERT(0); //---->Invalid data type
				TRACE0("Warning: ResolveReadSeekData is unable to resolve data. Calls to Read/Seek may fail\n");
			}
	}
	
	return pVoid;
}


// GXREADSEEKDATA implementation
GXREADSEEKDATA::GXREADSEEKDATA()
{
	// no implementation
}

// overloaded constructors
GXREADSEEKDATA::GXREADSEEKDATA(WORD* pwData, gxreadseekOp op /* = gxread*/)
{
	Init( pwData, op);
}

GXREADSEEKDATA::GXREADSEEKDATA(long* plData, gxreadseekOp op /* = gxread*/)
{
	Init( plData, op);
}

GXREADSEEKDATA::GXREADSEEKDATA(DWORD* pdwData, gxreadseekOp op /*= gxread*/)
{
	Init( pdwData, op);
}

GXREADSEEKDATA::GXREADSEEKDATA(short* psiData, gxreadseekOp op /* = gxread*/)
{
	Init( psiData, op);
}

GXREADSEEKDATA::GXREADSEEKDATA(int* piData, gxreadseekOp op /* = gxread*/)
{
	Init( piData, op);
}

GXREADSEEKDATA::GXREADSEEKDATA(BYTE* piByte, gxreadseekOp op /* = gxread*/)
{
	Init( piByte, op);
}

GXREADSEEKDATA::GXREADSEEKDATA(TCHAR* pszData, DWORD /*dwSize*/ /*= 255*/, gxreadseekOp op /*= gxread*/)
{
	Init( pszData, op);
}

GXREADSEEKDATA::GXREADSEEKDATA(double* pD, gxreadseekOp op /*= gxread*/)
{
	Init( pD, op);
}

// Function name	: GXREADSEEKDATA::Init
// Description	    : Initialize for different data structures
// Return type		: void 
// Argument         : WORD* pwD
// Argument         : gxreadseekOp o /* = gxread */
void GXREADSEEKDATA::Init(WORD* pwD, gxreadseekOp o /* = gxread */)
{
	type = gx_Word;
	dwSize = 2;
	pwData = pwD;
	op = o;
}
void GXREADSEEKDATA::Init(long* plD, gxreadseekOp o /* = gxread */)
{
	type = gx_Long;
	dwSize = 4;
	plData = plD;
	op = o;
}
void GXREADSEEKDATA::Init(DWORD* pdwD, gxreadseekOp o /* = gxread */)
{
	type = gx_Dword;
	dwSize = 4;
	pdwData = pdwD;
	op = o;
}
void GXREADSEEKDATA::Init(short* psiD, gxreadseekOp o /* = gxread */)
{
	type = gx_Short;
	dwSize = 2;
	psiData = psiD;
	op = o;
}
void GXREADSEEKDATA::Init(int* piD, gxreadseekOp o /* = gxread */)
{
	type = gx_Int;
	dwSize = 4;
	piData = piD;
	op = o;
}
void GXREADSEEKDATA::Init(BYTE* piB, DWORD dw /*= 1*/, gxreadseekOp o /* = gxread */)
{
	type = gx_Byte;
	dwSize = dw;
	pbyData = piB;
	op = o;
}
void GXREADSEEKDATA::Init(TCHAR* pszD, DWORD dw /* = 255 */, gxreadseekOp o /* = gxread */)
{
	type = gx_Tchar;
	dwSize = dw;
	pszData = pszD;
	op = o;
}

void GXREADSEEKDATA::Init(double* pD, gxreadseekOp o /* = gxread */)
{
	type = gx_Double;
	dwSize = 8;
	pDData = pD;
	op = o;
}

// READSEEKEXCEP implementation
READSEEKEXCEP::READSEEKEXCEP(HRESULT h, DWORD dwindex)
{
	hrLast = h; 
	dwerrorIndex = dwindex;
}

READSEEKEXCEP::~READSEEKEXCEP()
{
	// no implementation
}

void READSEEKEXCEP::TraceError()
{
	// no implementation
}

void READSEEKEXCEP::Destroy()
{
	delete this;
}

// Function name	: READSEEKEXCEP::ReportError
// Description	    : Reports the generated error to the user
// Return type		: void 
void READSEEKEXCEP::ReportError()
{
	CString s;
	s.Format(_T("Error: Exception error code: %x"), hrLast);
	TRACE1("OG Pro: Read fails. %s", s);
}



// CGXExcelHandler implementation
CGXExcelHandler::CGXExcelHandler()
{
	// the read offset. useful with handling CONTINUE
	m_dwRecordOffset = 0;
	
	// the length of the current record being handled
	m_dwRecordLength = 0;
}

CGXExcelHandler::~CGXExcelHandler()
{
	// no implementation
}

DWORD CGXExcelHandler::GetRecordOffset() const
{
	return m_dwRecordOffset;
}

void CGXExcelHandler::SetRecordOffset(DWORD dw, BOOL bInc /* = TRUE */)
{
	// bInc indicates an increment rather than a set
	if(bInc == FALSE)
		m_dwRecordOffset = dw;
	else
		m_dwRecordOffset += dw;
}
	
void CGXExcelHandler::ResetRecordOffset()
{
	m_dwRecordOffset = 0;
}

DWORD CGXExcelHandler::GetRecordLength() const
{
	return m_dwRecordLength;
}

void CGXExcelHandler::SetRecordLength(DWORD dw)
{
	m_dwRecordLength = dw;
}


// Function name	: CGXExcelHandler::ReadFromStream
// Description	    : Reads data that is specific to the type of record from the supplied IStream pointer
// Return type		: BOOL 
// Argument         : IStream* /*pStream*/
// Argument         : CGXExcelHandler::gxexpointer p
BOOL CGXExcelHandler::ReadFromStream(IStream* /*pStream*/,  CGXExcelHandler::gxexpointer p, DWORD /*dwLength*/)
{
	BOOL b = DelegateHelper(p);
	ResetInternalState();
	return b;
}



// Function name	: CGXExcelHandler::WriteToStream
// Description	    : Merely resets internal state
// Return type		: BOOL 
// Argument         : IStream* /*pStream*/
// Argument         : CGXExcelHandler::gxexpointer p
BOOL CGXExcelHandler::WriteToStream(IStream* /*pStream*/,  CGXExcelHandler::gxexpointer p, DWORD& /*dwLength*/, UINT /*nTabIndex*/ /*= 0*/)
{
	ResetInternalState();
	return TRUE;
}


// Function name	: CGXExcelHandler::DelegateHelper
// Description	    : This function delegates to the correct version of the grid object initialization
// code that is desired to be called by the caller
// Return type		: BOOL 
// Argument         : CGXExcelHandler::gxexpointer p
// Argument         : BOOL bStore /*= FALSE*/
BOOL CGXExcelHandler::DelegateHelper(CGXExcelHandler::gxexpointer p, BOOL bStore /*= FALSE*/)
{
	BOOL b(FALSE);

	switch(p.vt)
	{
		case CGXExcelHandler::corePtr:
			{
				b = InitializeCore(p.pCore, bStore);
				break;
			}
		case CGXExcelHandler::stylePtr:
			{
				b = InitializeStyle(p.pStyle, bStore);
				break;
			}
		case CGXExcelHandler::paramPtr:
			{
				b = InitializeParam(p.pParam, bStore);
				break;
			}
		case CGXExcelHandler::dataPtr:
			{
				b = InitializeData(p.pData, bStore);
				break;
			}
		default:
			TRACE0("Error in CGXExcelHandler::DelegateHelper. Unrecognized format\n");
	}

	return b;
}


// Function name	: CGXExcelHandler::InitializeStyle
// Description	    : Handle if you want this object to initialize a CGXStyle object
// Return type		: BOOL 
// Argument         : CGXStyle* pStyle
// Argument         : BOOL bStore /* = FALSE*/
BOOL CGXExcelHandler::InitializeStyle(CGXStyle* /*pStyle*/, BOOL /*bStore*/ /* = FALSE*/)
{
	//ASSERT(0);
	// If you intend to call this then you should provide an implementation
	return TRUE;
}


// Function name	: CGXExcelHandler::InitializeCore
// Description	    : Handle if you want this object to initialize a CGXGridCore object
// Return type		: BOOL 
// Argument         : CGXGridCore* pCore
// Argument         : BOOL bStore /* = FALSE*/
BOOL CGXExcelHandler::InitializeCore(CGXGridCore* /*pCore*/, BOOL /*bStore*/ /* = FALSE*/)
{
	//ASSERT(0);
	// If you intend to call this then you should provide an implementation
	return TRUE;
}


// Function name	: CGXExcelHandler::InitializeParam
// Description	    : Handle if you want this object to initialize a CGXGridParam object
// Return type		: BOOL 
// Argument         : CGXGridParam* pParam
// Argument         : BOOL bStore /* = FALSE*/
BOOL CGXExcelHandler::InitializeParam(CGXGridParam* /*pParam*/, BOOL /*bStore*/ /* = FALSE*/)
{	
	//ASSERT(0);
	// If you intend to call this then you should provide an implementation
	return TRUE;
}


// Function name	: CGXExcelHandler::InitializeData
// Description	    : Handle if you want this object to initialize a CGXData object
// Return type		: BOOL 
// Argument         : CGXData* pData
// Argument         : BOOL bStore /*= FALSE*/
BOOL CGXExcelHandler::InitializeData(CGXData* /*pData*/, BOOL /*bStore*/ /*= FALSE*/)
{
	//ASSERT(0);
	// If you intend to call this then you should provide an implementation
	return TRUE;
}


// default is core pointer
CGXExcelHandler::gxexpointer::gxexpointer(void* /*pv*/):vt(nullPtr) 
{
	// no implementation
}

CGXExcelHandler::gxexpointer::gxexpointer():vt(corePtr) 
{
	// no implementation
}


CGXExcelHandler::gxexpointer::gxexpointer(CGXGridCore* p)
{
	vt = corePtr;
	pCore = p;
}

CGXExcelHandler::gxexpointer::~gxexpointer()
{
	// no implementation
}

void CGXExcelHandler::LogText(const TCHAR* pszText)
{
	if(s_pLogger && m_bCanLog)
		s_pLogger->LogText(pszText);
}

void CGXExcelHandler::LogNumber(int nNum, BOOL bTerminate /*= FALSE*/)
{
	if(s_pLogger && m_bCanLog)
		s_pLogger->LogNumber(nNum, bTerminate);
}

void CGXExcelHandler::LogXNumber(int nNum, BOOL bTerminate /*= FALSE*/)
{
	if(s_pLogger && m_bCanLog)
		s_pLogger->LogXNumber(nNum, bTerminate);
}
	
CGXExcelLogger* CGXExcelHandler::GetLogger()
{
	return s_pLogger;
}

void CGXExcelHandler::SetCanLog(BOOL bCanLog)
{
	m_bCanLog = bCanLog;
}

BOOL CGXExcelHandler::GetClipMode()
{
	return m_bClipMode;
}

void CGXExcelHandler::SetClipMode(BOOL b)
{
	m_bClipMode = b;
}

BOOL CGXExcelHandler::GetOptimizedMode()
{
	return m_bOptimized;
}
	
void CGXExcelHandler::SetOptimizedMode(BOOL b)
{
	m_bOptimized = b;
}



// CGXExcelLabelHandler implementation
// Concrete implementation for the LABEL record


CGXExcelLabelHandler::CGXExcelLabelHandler()
{
	m_lStruct.buffer = NULL;
	m_lStruct.row = 0;
	m_lStruct.col = 0;
	m_lStruct.wLength = 0;
}

CGXExcelLabelHandler::~CGXExcelLabelHandler()
{
	// no implementation
}

/*
LABEL: Cell Value, String Constant (204h)
A LABEL record describes a cell that contains a string constant. 
*/
BOOL CGXExcelLabelHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[6];

	// phase 1
	readData[0].Init(&m_lStruct.row); //row
	readData[1].Init(&m_lStruct.col); //column
	readData[2].Init(&m_lStruct.ixfe); //index to XF record
	readData[3].Init(&m_lStruct.wLength); // Length of the string
	readData[4].Init(&m_lStruct.grbit); //grbit flags

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 5))

	//phase 2
	if( (m_lStruct.grbit & 0x01) == 0)
	{
		BYTE* pszTemp = new BYTE[m_lStruct.wLength];
		readData[5].Init( (BYTE*)pszTemp, m_lStruct.wLength*sizeof(BYTE), gxread); // read the array of bytes
			
		// read the data
		GXEX_TRY(ReadSeekHelper(pStream, &readData[5], 1));

		// expand to a UNICODE string
		m_lStruct.buffer = _gxexExpandToUnicode(pszTemp, m_lStruct.wLength);

		if(pszTemp)
			delete[] pszTemp;
			
		pszTemp = NULL;
	}
	else
	{
		// This is an uncompressed UNICODE string
		m_lStruct.buffer = new WCHAR[m_lStruct.wLength];
		readData[5].Init( (BYTE*)m_lStruct.buffer, m_lStruct.wLength*sizeof(WCHAR), gxread); // read the array of bytes
			
		// read the data
		GXEX_TRY(ReadSeekHelper(pStream, &readData[5], 1));
	}
	//
	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelLabelHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT /*nTabIndex*/ /*= 0*/)
{
	// implemented in RkHandler for writing (this is more effecient)
	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}

void CGXExcelLabelHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelLabelHandler::ResetInternalState called\n");
	if(m_lStruct.buffer)
		delete[] m_lStruct.buffer;

	m_lStruct.buffer = NULL;
	
	m_lStruct.row = 0;
	m_lStruct.col = 0;
	m_lStruct.wLength = 0;
}

BOOL CGXExcelLabelHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	ASSERT(pCore!=NULL);

	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);

	ASSERT(pTable!=NULL);
	
	CGXStyle* pStyle = pCore->CreateStyle();

	pTable->ApplyToObject(m_lStruct.ixfe, pStyle);

#ifdef _UNICODE
	pStyle->SetValue(psstStruct->pStrings[index].pszValue);
#else //!_UNICODE
	GX_EX_WTMB(m_lStruct.buffer, psz, CP_ACP, m_lStruct.wLength, "CGXExcelLabelHandler::InitializeCore")
	
	if(psz != NULL)
	{
		pStyle->SetValue(psz);
		delete [] psz;
	}
#endif

	if(GetOptimizedMode())
		pCore->GetParam()->GetData()->StoreStyleRowCol(m_lStruct.row+1, m_lStruct.col+1, pStyle, gxOverride);
	else
		pCore->SetStyleRange(CGXRange(m_lStruct.row+1, m_lStruct.col+1), *pStyle);

	if(pStyle)
		pCore->RecycleStyle(pStyle);

	return TRUE;
}

//CGXExcelRkHandler Implementation
/*
Microsoft Excel uses an internal number type, called an RK number, to save memory and disk space.
Record Data
*/

// copied this for the most part from the Excel SDK docs

double GXNumFromRk(long rk)
{
	double num;
	
	if(rk & 0x02)
		{
		// int
		num = (double) (rk >> 2);
		}
	else
		{
		// hi words of IEEE num
		*((long *)&num+1) = rk & 0xfffffffc;
		*((long *)&num) = 0;
		}
	if(rk & 0x01)
		// divide by 100
		num /= 100;
	
	return num;
}


long GXRkFromNum(double /*num*/)
{
	return 0;
}

CGXExcelRkHandler::CGXExcelRkHandler()
{
	ResetInternalState();
}

CGXExcelRkHandler::~CGXExcelRkHandler()
{
	// no implementation
}

// With the mulrk handler it is easier to convert from the RK number as 
// required whilst we do the conversion here in the beginning itself
// since there is only one number involved
BOOL CGXExcelRkHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[5];
	
	readData[0].Init(&m_rkStruct.row); //row
	readData[1].Init(&m_rkStruct.col); //column
	readData[2].Init(&m_rkStruct.ixfe); //index to XF record
	
	long lVal(0);
	readData[3].Init(&lVal); //number
	
	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 4))

	// convert the rk value to a double
	m_rkStruct.dblVal = GXNumFromRk(lVal);
	
	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelRkHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT nTabIndex /*= 0*/)
{
	HRESULT hr(S_OK);
	
	ASSERT(p.vt == CGXExcelHandler::corePtr); // We insist on a CGXGridCore pointer so that it becomes easy to add
											  // support for virtual grids later
	
	// check parameters
	if (p.vt != CGXExcelHandler::corePtr)
		throw egxWriteInvalidData;
		
	CGXGridCore* pCore = p.pCore;
	
	if (pCore == NULL)
		throw egxInvalidGrid;
		
	CGXGridParam* pParam = pCore->GetParam();

	if (pParam == NULL)
		throw egxInvalidParam;
		
	// This stuff is not written globally and is hence written one tab at a time
	CGXData* pData = NULL;
	CGXFormulaSheet* pSheet = NULL;
	
	// helper to access protected members:)
	_accData* pD = NULL;

	// Iterate through all the other styles
	pData = pParam->GetData();
		
	ASSERT(pData != NULL);
		
	if(pData == NULL)
		throw egxWriteNoData;
		
	pD  = (_accData*)pData;

	CGXStylePtrArrayPtrArray* pStylePtrAr =  NULL;
	//CGXStylePtrArray* pStyleDataPtrAr = NULL;
		
	
	BOOL bData(TRUE); // Specifies if this is CGXData or CGXFormulaSheet (TRUE for CGXData)

	if(!pData->IsKindOf(RUNTIME_CLASS(CGXFormulaSheet)))
		pStylePtrAr = &pD->m_apapCellStyle; // spans the cell matrix,
												// CGXStylePtrArray elements are rows
												// which CGXStyle elements are styles
		
	else
	{
		pSheet = (CGXFormulaSheet*) pData;
		bData = FALSE; // This is a formula sheet
	}	


	BYTE psz[GX_EX_SIZEOF_WRITEBUFFER];
	WCHAR pszWBuffer[GX_EX_SIZEOF_WRITEBUFFER];	
	
	// for the formula write
	BYTE byFormula[GX_EX_SIZEMAX_FORMULA];
	BYTE* pszBuffer = psz;
	BYTE grBit(0);

	int nBufferSize = GX_EX_SIZEOF_WRITEBUFFER;
	BOOL bAlloc = FALSE;
	
	CString strValue;

	ULONG cb(0);
	unsigned short sType(0);
	double d(0);
	//long rk(0);

	WORD ixfe(0); WORD cch(0);
	
	memset(pszBuffer, 0, GX_EX_SIZEOF_NUMBER);

	// iteration limits
	int nOUpperBound = 0;
	int nIUpperBound(0);

	if(bData)
		nOUpperBound = (int)pStylePtrAr->GetUpperBound();
	else
	{
			int sIndex = pCore->GetSheetContext()->m_nSheetContext;
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
	}

	// Get the XF table
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);
	ASSERT(pTable!=NULL); // Error---> There has to be a valid XF table

	if(pTable == NULL)
		throw egxWriteHandlerNotFound;
		
	

	CGXStylePtrArray* pStylePtrArray = NULL;
	CGXStyle* pStyle = NULL;

	if(!bData)
		pStyle = new CGXStyle;

	int nInitSize = GX_EX_SIZEOF_WRITEBUFFER;


	int sIndex (0);
	gxCell *cp = NULL;	
	formulaStruct fs;
	WORD wParseLength(0);

	BYTE pszVal[GX_EX_SIZEOF_VALBUF];
	memset(pszVal, 0, GX_EX_SIZEOF_VALBUF);

	BOOL bClip = GetClipMode();

	//DWORD dwTime = ::GetTickCount();

	for (int nR(1); nR <= nOUpperBound; nR++)
	{	
		if(bData)
		{
			pStylePtrArray = pStylePtrAr->GetAt(nR);
			if(pStylePtrArray)
				nIUpperBound = 	(int)pStylePtrArray->GetUpperBound();
			else
				continue;	
		}
		// else
		// Already available for Formula sheet
			
		// loop through and get the value
		for (int nCol = 1;  nCol <= nIUpperBound; nCol++)
		{
			if(bData)
				pStyle = pStylePtrArray->GetAt(nCol);
			else
			{
				pStyle->Free();
				
				sIndex = pCore->GetSheetContext()->m_nSheetContext;
				cp = _gx_find_cell(sIndex, pSheet->GetEngineRow(nR), pSheet->GetEngineCol(nCol));
				
				if(cp == NULL)
					continue;

				if(cp && cp->formula == NULL)
					pCore->ComposeStyleRowCol(nR, nCol, pStyle, FALSE);
				else
					pData->GetStyleRowCol(nR, nCol, *pStyle, gxCopy, GX_VALUE_EXPRESSION); // CGXFormulaSheet
			}

			TRACE1("%d\n", nCol);

			if(pStyle == NULL)
				continue;
			
			if(pStyle->GetIncludeValue())
			{
				ixfe = (WORD)pTable->GetExcelStyleMap(nTabIndex).GetIndexRowCol(nR, nCol);
				
				TRACE1("ixfe used:%x\n", ixfe);
					
				sType = (WORD)pStyle->GetValueType();
					
				switch(sType)
				{	
					case GX_VT_STRING:
						// will call the label handler from here
						{
							strValue = pStyle->GetValue();
							cch = (WORD)_tcslen(strValue);
	
							if(cch == 0)
							{
								_gxdata(wr)
									_gxw(typeBlank)
									_gxw(GX_EX_SIZEOF_BLANK - 4)
									_gxw(nR-1)
									_gxw(nCol-1)
									_gxw(ixfe)
								_gxend
										
								_gxExWrite(wr, pszBuffer);
								GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_BLANK, &cb));
								// GXEXDUMP(pszBuffer, GX_EX_SIZEOF_BLANK)
								dwLength+=cb;
								continue;
							}

							BOOL bFreeWChar(FALSE);
						#ifdef _UNICODE
							int nCount = cch;
							const WCHAR* pszW = strValue;
						#else 
							int nCount = MultiByteToWideChar(CP_ACP, 0, strValue, -1, NULL, NULL);
							ASSERT(nCount);
							
							if(nCount == 0)
								continue;
							
							WCHAR* pszW = NULL;
							
							if(nInitSize < nCount)
							{
								pszW = new WCHAR[nCount];
								bFreeWChar = TRUE;
								nInitSize = nCount;
							}
							else
								pszW = pszWBuffer;
							
							MultiByteToWideChar(CP_ACP, 0, strValue, -1, pszW, nCount);
						#endif
							grBit = 1;
									
							_gxdata(wr)
								_gxw(typeLabel)
								_gxw(GX_EX_SIZEOF_LABEL - 4 + (GX_EX_WCHARSIZE * nCount - 2) )
								_gxw(nR-1)
								_gxw(nCol-1)
								_gxw(ixfe)
								_gxw(nCount-1)
								_gxb(grBit)
								_gxby(pszW, GX_EX_WCHARSIZE * nCount)
							_gxend


							if(GX_EX_SIZEOF_LABEL + GX_EX_WCHARSIZE * nCount > nBufferSize)
							{
								if(bAlloc)
									delete [] pszBuffer; 
								pszBuffer = new BYTE[GX_EX_SIZEOF_LABEL + GX_EX_WCHARSIZE * nCount];
								nBufferSize = GX_EX_SIZEOF_LABEL + GX_EX_WCHARSIZE * nCount;
								bAlloc = TRUE;
							}

							_gxExWrite(wr, pszBuffer);
							
							GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_LABEL + GX_EX_WCHARSIZE * nCount - 2, &cb));
							
							memset(pszBuffer, 0, GX_EX_SIZEOF_LABEL + GX_EX_WCHARSIZE * nCount - 2);
							dwLength+=cb;
									
							if(bFreeWChar && pszW)
							{
								delete pszW;
								pszW = NULL;
								bFreeWChar = FALSE;
							}
						}
					break;
				case GX_VT_NUMERIC:
						{
							d = pStyle->GetDoubleValue();	
									
							// TRACE0("Dumping double value");
							// GXEXDUMP(&d, 8)

							_gxdata(wr)
								_gxw(typeNumber)
								_gxw(GX_EX_SIZEOF_NUMBER - 4)
								_gxw(nR-1)
								_gxw(nCol-1)
								_gxw(ixfe)
								_gxdo(d)
							_gxend
									
							_gxExWrite(wr, pszBuffer);
							GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_NUMBER, &cb));
							
							//GXEXDUMP(pszBuffer, GX_EX_SIZEOF_NUMBER)
							
							dwLength+=cb;
						}
					break;
				case GX_VT_EXPRESSION: // formulas
						{
							// we don't call the formula handler for this
							memset(byFormula, 0, GX_EX_SIZEMAX_FORMULA);
							fs.pVarParsed = byFormula;
									
							wParseLength = (WORD)gx_xls_build_formula(&fs, cp, fs.pVarParsed);
		
							if(wParseLength == 0)
								continue;

							if(bClip)
								gx_xls_make_formula_val (&fs, cp, pszVal);

							_gxdata(wr)
								_gxw(typeFormula)
								_gxw(GX_EX_SIZEOF_FORMULA + wParseLength - 4)
								_gxw(nR-1) //rw
								_gxw(nCol-1) //col
								_gxw(ixfe) //ixfe
								_gxby(pszVal, 8)
								_gxw(3) // grbit---> we let Excel calculate the value when the file gets read
								_gxdw(0) // chn
								_gxw(wParseLength) //cce
								_gxby(byFormula, wParseLength) // var
							_gxend
									
							_gxExWrite(wr, pszBuffer);

							GXEXDUMP(byFormula, wParseLength)

							cb = 0;
							GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_FORMULA + wParseLength, &cb));
							// GXEXDUMP(pszBuffer, GX_EX_SIZEOF_FORMULA + wParseLength)
							dwLength+=cb;
							
							
							if(bClip && (cp->value_type == GX_VALUE_STRING || cp->value_type == GX_VALUE_SHORT_STRING) )
							{
								
								TCHAR* psz = NULL;
								
								if(cp->value_type == GX_VALUE_STRING)
									psz = cp->value.string;
								else
									psz = cp->value.short_string;	

								if(psz == NULL)
									continue;

								WORD wC = (WORD)_tcslen(psz);
								_gxdata(wr)
									_gxw(typegxString)
									_gxw(GX_EX_FIXED_STRING + wC)
									_gxw(wC)
									_gxb(0)
									_gxby(psz, wC) // var
								_gxend

								_gxExWrite(wr, pszBuffer);
							
								cb = 0;
								GX_EX_WRITEEX(pStream->Write(pszBuffer, GX_EX_FIXEDHEADER + GX_EX_FIXED_STRING + wC, &cb));
								// GXEXDUMP(pszBuffer, GX_EX_SIZEOF_FORMULA + wParseLength)
								dwLength+=cb;
							}
						}
					break;
					default:;
					// do nothing
					}
				}
				else
					// generate blank cells with formatting
				{
						ixfe = pTable->GetExcelStyleMap(nTabIndex).GetIndexRowCol(nR, nCol);
						
						_gxdata(wr)
							_gxw(typeBlank)
							_gxw(GX_EX_SIZEOF_BLANK - 4)
							_gxw(nR-1)
							_gxw(nCol-1)
							_gxw(ixfe)
						_gxend
								
						_gxExWrite(wr, pszBuffer);
						GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_BLANK, &cb));
						// GXEXDUMP(pszBuffer, GX_EX_SIZEOF_BLANK)
						dwLength+=cb;
				}
			}
		}
	
		// CString str;
		// str.Format("Time:%u", GetTickCount() - dwTime);
		// AfxMessageBox(str);

		if(!bData && pStyle)
			delete pStyle;
		
		if(bAlloc)
			delete [] pszBuffer; 
		
		return TRUE;
}

void CGXExcelRkHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelRkHandler::ResetInternalState called\n");
	
	m_rkStruct.row = 0;
	m_rkStruct.col = 0;
	m_rkStruct.dblVal = 0.0;
}

BOOL CGXExcelRkHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);

	ASSERT(pTable != NULL);

	CGXStyle* pStyle = pCore->CreateStyle();

	pStyle->SetValue(m_rkStruct.dblVal);
	pTable->ApplyToObject(m_rkStruct.ixfe, pStyle);
	
	if(GetOptimizedMode())
		pCore->GetParam()->GetData()->StoreStyleRowCol(m_rkStruct.row+1, m_rkStruct.col+1, pStyle, gxOverride);
	else
		pCore->SetStyleRange(CGXRange(m_rkStruct.row+1, m_rkStruct.col+1), *pStyle);
	
	if(pStyle)
		pCore->RecycleStyle(pStyle);
	
	return TRUE;
}



//CGXExcelMulRkHandler Implementation
CGXExcelMulRkHandler::CGXExcelMulRkHandler()
{
	m_mulrkStruct.pMulRkData = NULL;
	ResetInternalState();
}

CGXExcelMulRkHandler::~CGXExcelMulRkHandler()
{
	// no implementation
}

/*
MULRK: Multiple RK Cells (BDh)
The MULRK record stores up to the equivalent of 256 RK records; the MULRK record is a file size optimization. 
*/

// 8 bytes in the beginning + 2 in the end.. rest is variable
// length

BOOL CGXExcelMulRkHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	//long lVal(0);
	static GXREADSEEKDATA readData[4];
	
	// phase 1
	readData[0].Init(&m_mulrkStruct.row); //row
	readData[1].Init(&m_mulrkStruct.colStart); //starting column
	
	// calculate the size of the variable data block
	DWORD dwSize = (dwLength - GX_RK_FIXEDBLOCK);
	
	// allocate an appropriate array of bytes. The actual numbers and the xf offsets
	// are in 6 byte blocks
	m_mulrkStruct.pMulRkData = new BYTE[dwSize];
	
	readData[2].Init( (BYTE*)m_mulrkStruct.pMulRkData, dwLength - GX_RK_FIXEDBLOCK, gxread); //the actual array pointer
	readData[3].Init( &m_mulrkStruct.colEnd); //ending column

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 4))

	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelMulRkHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT /*nTabIndex*/ /*= 0*/)
{
	// will never be called in this version since we only write out number data. No Rk fields are written out
	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}

void CGXExcelMulRkHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelMulRkHandler::ResetInternalState called\n");
	m_mulrkStruct.row = 0;
	m_mulrkStruct.colStart = 0;
	m_mulrkStruct.colEnd = 0;

	if(m_mulrkStruct.pMulRkData)
		delete [] m_mulrkStruct.pMulRkData;

	m_mulrkStruct.pMulRkData = NULL;
}

BOOL CGXExcelMulRkHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);

	ASSERT(pTable != NULL);

	ASSERT(pCore != NULL);

	CGXStyle* pStyle = pCore->CreateStyle();

	double d(0.0);
	DWORD nRow = m_mulrkStruct.row;
	BYTE* pRk = (BYTE*) m_mulrkStruct.pMulRkData;
	
	BOOL bOp = GetOptimizedMode();
	
	for(DWORD nCol = m_mulrkStruct.colStart; nCol <= m_mulrkStruct.colEnd; nCol++)
	{
		pTable->ApplyToObject(*(short*)(pRk), pStyle);
		d = GXNumFromRk( *(long*)(pRk+2) );
		pStyle->SetValue(d);

		if(bOp)
			pCore->GetParam()->GetData()->StoreStyleRowCol(nRow + 1, nCol + 1, pStyle, gxOverride);	
		else
			pCore->SetStyleRange(CGXRange(nRow + 1, nCol + 1), *pStyle);
		
		pRk+=6;
		
		pStyle->Free();
	}

	if(pStyle)
		pCore->RecycleStyle(pStyle);

	return TRUE;
}

// CGXExcelColInfoHandler Implementation
CGXExcelColInfoHandler::CGXExcelColInfoHandler()
{
	ResetInternalState();
}
	
CGXExcelColInfoHandler::~CGXExcelColInfoHandler()
{
	// no implementation
}

/*
COLINFO: Column Formatting Information (7Dh)
The COLINFO record describes the column formatting for a range of columns.
Record Data
*/
BOOL CGXExcelColInfoHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[6];
	
	readData[0].Init(&m_colInfoStruct.colFirst); // row
	readData[1].Init(&m_colInfoStruct.colLast); // starting column
	readData[2].Init(&m_colInfoStruct.coldx); // column width
	readData[3].Init(&m_colInfoStruct.ixfe); // XF index
	
	readData[4].Init(&m_colInfoStruct.grbit); // flags
	
	readData[5].Init((BYTE*)NULL, 1, gxseek); // ignore the reserved flag

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 6))

	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelColInfoHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT nTabIndex /*= 0*/)
{
	ASSERT(p.vt == CGXExcelHandler::corePtr); //This has to be a CGXGridCore pointer
	HRESULT hr(S_OK);
	
	CGXGridCore* pCore = p.pCore;
	ASSERT(pCore != NULL);
	
	if(pCore == NULL)
		throw egxInvalidGrid;
	
	ROWCOL nColCount = pCore->GetColCount();

	WORD ixfe(0); WORD grbit(0); WORD coldx(0);

	ULONG cb(0);

	// locate the XF handler
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);
	ASSERT(pTable!=NULL); // Error---> There has to be a valid XF table

	if(pTable == NULL)
		throw egxWriteHandlerNotFound;

	BYTE pszBuffer[GX_EX_SIZEOF_COLINFO];

	for (ROWCOL nCol(1); nCol <= nColCount; nCol++)
	{
		memset(pszBuffer, 0, GX_EX_SIZEOF_COLINFO);

		ixfe = pTable->GetExcelStyleMap(nTabIndex).GetIndexRowCol(0, nCol);
	
		if(ixfe == 0 && pCore->GetColWidth(nCol) == pCore->GetDefaultColWidth())
			continue;

		coldx = pCore->GetColWidth(nCol) * (256 * GX_EXCEL_WIDTHFACTOR) / pCore->GetFontWidth();

		// compose grbit
		_gxExSetBit(grbit, 0, pCore->IsColHidden(nCol)? 1:0);

		_gxdata(wr)
			_gxw(typeColInfo)
			_gxw(GX_EX_SIZEOF_COLINFO - 4)
			_gxw(nCol-1)
			_gxw(nCol-1)
			_gxw(coldx)
			_gxw(ixfe)
			_gxw(grbit)
			_gxb(0)
		_gxend
								
		_gxExWrite(wr, pszBuffer);
		GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_COLINFO, &cb));
		GXEXDUMP(pszBuffer, GX_EX_SIZEOF_COLINFO)
		dwLength+=cb;
			
	}	
	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}

void CGXExcelColInfoHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelColInfoHandler::ResetInternalState called\n");
	m_colInfoStruct.colFirst = 0;
	m_colInfoStruct.colLast = 0;
	m_colInfoStruct.coldx = 0;
	m_colInfoStruct.ixfe = 0;
	m_colInfoStruct.coldx = 0;
}

BOOL CGXExcelColInfoHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);

	ASSERT(pTable != NULL);

	CGXStyle* pStyle = pCore->CreateStyle();

	ROWCOL nCol = m_colInfoStruct.colFirst;
	ROWCOL nColLast = m_colInfoStruct.colLast;

	pTable->ApplyToObject(m_colInfoStruct.ixfe, pStyle);
		
	pCore->SetStyleRange(CGXRange().SetCols(nCol + 1, nColLast + 1), *pStyle, gxOverride, -1);
	
	pCore->SetColWidth(nCol + 1, nColLast + 1, MulDiv(m_colInfoStruct.coldx, pCore->GetFontWidth(), 256 * GX_EXCEL_WIDTHFACTOR) );

	pStyle->Free();
		
	// we do not use the rest of the grbit flags
	if(m_colInfoStruct.grbit & 0x01)
		pCore->HideCols(nCol+1, m_colInfoStruct.colLast+1);
	

	if(pStyle)
		pCore->RecycleStyle(pStyle);

	return TRUE;
}


//CGXExcelRowHandler
CGXExcelRowHandler::CGXExcelRowHandler()
{
	ResetInternalState();
}

CGXExcelRowHandler::~CGXExcelRowHandler()
{
	// no implementation
}

BOOL CGXExcelRowHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[7];
	
	readData[0].Init(&m_rowInfoStruct.rw); // row
	readData[1].Init(&m_rowInfoStruct.colMic); // starting column
	readData[2].Init(&m_rowInfoStruct.colMac); // ending column
	readData[3].Init(&m_rowInfoStruct.miyRw); // column width
	readData[4].Init((BYTE*)NULL, 4, gxseek); // ignore the reserved flag and irwMac
	readData[5].Init(&m_rowInfoStruct.grbit); // flags
	readData[6].Init(&m_rowInfoStruct.ixfe); // XF index
	
	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 7))

	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelRowHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT nTabIndex /*= 0*/)
{
	// check parameters
	ASSERT(p.vt == CGXExcelHandler::corePtr); //This has to be a CGXGridCore pointer
	CGXGridCore* pCore = p.pCore;
	
	if(p.vt != CGXExcelHandler::corePtr)
		throw egxWriteInvalidData;
	
	ASSERT(pCore != NULL);
	
	if(pCore == NULL)
		throw egxInvalidGrid;

	ROWCOL nRowCount = pCore->GetRowCount();

	WORD ixfe(0); WORD grbit(0); WORD rowdx(0); ULONG cb(0);

	HRESULT hr(S_OK);
	
	// locate the XF handler
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);
	ASSERT(pTable!=NULL); // Error---> There has to be a valid XF table

	BYTE pszBuffer[GX_EX_SIZEOF_ROWINFO];

	for (ROWCOL nRow(1); nRow <= nRowCount; nRow++)
	{
		memset(pszBuffer, 0, GX_EX_SIZEOF_ROWINFO);

		ixfe = pTable->GetExcelStyleMap(nTabIndex).GetIndexRowCol(nRow, 0);
	
		if( ixfe == 0 && pCore->GetRowHeight(nRow) == pCore->GetDefaultRowHeight() )
			continue;

		if(ixfe != 0) // row has been formatted...ixfe is valid
		{
			_gxExSetBit(grbit, 7, 1);
			_gxExSetBit(grbit, 8, 1); // this is not documented but from dumps is required.
			// without setting the 8 th bit in this word nothing works
		}

		if(pCore->GetRowHeight(nRow) != 0)
		{
			rowdx = pCore->GetRowHeight(nRow) * (72*20) / GXGetFontState()->m_nLogPixelsY;
			_gxExSetBit(grbit, 6, 1);
		}
		else
			rowdx = 0;

		if(rowdx == 0)
			_gxExSetBit(grbit, 5, 1);

		_gxdata(wr)
			_gxw(typeRow)
			_gxw(GX_EX_SIZEOF_ROWINFO - 4)
			_gxw(nRow-1)
			_gxw(0)
			_gxw(1)
			_gxw(rowdx)
			_gxw(0)
			_gxw(0) // reserved
			_gxw(grbit)
			_gxw(ixfe)
		_gxend
								
		_gxExWrite(wr, pszBuffer);
		GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_ROWINFO, &cb));
		GXEXDUMP(pszBuffer, GX_EX_SIZEOF_ROWINFO)
		dwLength+=cb;
	}	
	
	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}

void CGXExcelRowHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelRowHandler::ResetInternalState called\n");
	memset(&m_rowInfoStruct, '0', sizeof(CGXExcelRowHandler::rowInfoStruct));
}


BOOL CGXExcelRowHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	
	DWORD nRow = m_rowInfoStruct.rw;

	pCore->SetRowHeight(nRow+1, nRow+1, MulDiv(m_rowInfoStruct.miyRw, GXGetFontState()->m_nLogPixelsY, 72*20) );
		
	// we do not use the rest of the grbit flags
	if( (m_rowInfoStruct.grbit & 0x80) >> 7 ) // only if this is set is ixfe meaningful
	{
		CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);
		ASSERT(pTable != NULL);
		CGXStyle* pStyle = pCore->CreateStyle();
		// only the low order 12 bits specify ixfe
		pTable->ApplyToObject( (m_rowInfoStruct.ixfe & 0x0FFF), pStyle);
		pCore->SetStyleRange(CGXRange().SetRows(nRow+1), *pStyle);
		pStyle->Free();
			
		if(pStyle)
			pCore->RecycleStyle(pStyle);
	}
	return TRUE;
}

// CGXExcelFormulaHandler
CGXExcelFormulaHandler::CGXExcelFormulaHandler()
{
	m_formulaStruct.pVarParsed = NULL;
	ResetInternalState();
}

CGXExcelFormulaHandler::~CGXExcelFormulaHandler()
{
	// no implementation
}

BOOL CGXExcelFormulaHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[8];
	
	readData[0].Init(&m_formulaStruct.rw); // row
	readData[1].Init(&m_formulaStruct.col); // starting column
	readData[2].Init(&m_formulaStruct.ixfe); // ixfe
	
	readData[3].Init(&m_formulaStruct.num[0], 8, gxread); // ignore the reserved flag and irwMac
	
	readData[4].Init(&m_formulaStruct.grbit); // flags
	
	readData[5].Init(&m_formulaStruct.chn); // DWORD
	readData[6].Init(&m_formulaStruct.cce); // WORD

//phase 1 read
	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 7))

	m_formulaStruct.pVarParsed = new BYTE[m_formulaStruct.cce];

	readData[7].Init(m_formulaStruct.pVarParsed, m_formulaStruct.cce, gxread); // parsed formula

// phase 2 read
	GXEX_TRY(ReadSeekHelper(pStream, &readData[7], 1))


	// Check if this is a shared formula. Handle it as such
	// refer CGXExcelSharedFormulaTable for more information
	if ((m_formulaStruct.grbit & 0x08 ) && (*m_formulaStruct.pVarParsed == 0x01))
	{
		//ASSERT(*m_formulaStruct.pVarParsed == 0x01); // If this ASSERT fails then this
		// file must be corrupt
		
		// get the shared formula table
		CGXExcelSharedFormulaTable* pTable = (CGXExcelSharedFormulaTable*) GXExGetTableMap()->LocateHandler(typeSF);
		ASSERT(pTable != NULL); // Error---> check if your table map has a shared formula table. This is required
		// to properly read formulas written by Excel

		// 1) Check if this record is already available in the shared formula table
		WORD nRow = * ((WORD*)(m_formulaStruct.pVarParsed + 1));
		WORD nCol = * ((WORD*)(m_formulaStruct.pVarParsed + 3));

		if(pTable->LookupSharedFormula(nRow, nCol))
		{
			// 2) If yes, use it	
			formulaStruct * pFS = &m_formulaStruct;
			pTable->ApplyToObject(nRow, nCol, pFS);
		}
		else
		{
			static GXREADSEEKDATA readMoreData[3];
	
			// 3) If not skip till we read the shared formula for this and then use it
			WORD type(0);
			WORD wLength(0);
			do
			{
				readMoreData[0].Init(&type); // type of record 
				readMoreData[1].Init(&wLength); // length
				
				GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 2))

				
				if(type == typeSF)
				{
					// read shared formula
					DWORD dwI = pTable->GetCompositeIndex(nRow, nCol);
					// I know that passing in dwI as the second parameter is rather
					// nasty...
					pTable->ReadFromStream(pStream, dwI);					

					// now apply the object and break
					formulaStruct * pFS = &m_formulaStruct;
					pTable->ApplyToObject(nRow, nCol, pFS);
					break;
				}
				else
				{
					readMoreData[2].Init((BYTE*)NULL, dwLength, gxseek); // ignore the others

					GXEX_TRY(ReadSeekHelper(pStream, &readMoreData[2], 1))
				}	

				//phase 1 read
				GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 7))
			
			}while (type != typeSF);

		}
	}

	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

#pragma warning(push)
#pragma warning(disable: 4706)
BOOL CGXExcelFormulaHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT /*nTabIndex*/ /*= 0*/)
{
	// Intentional Assignment???
	ASSERT(p.vt = stylePtr); // This has to be a style pointer

	if(p.vt != stylePtr)
		throw egxWriteInvalidData;

	//CGXStyle* pStyle = p.pStyle;
	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}
#pragma warning(pop)//4706

void CGXExcelFormulaHandler::ResetInternalState()
{
	if(m_formulaStruct.pVarParsed)
		delete[] m_formulaStruct.pVarParsed;
	memset(&m_formulaStruct, '0', sizeof(formulaStruct));
}


BOOL CGXExcelFormulaHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{	
	//enable formula support
	((_core*)pCore)->m_pDefaultDataClass = RUNTIME_CLASS(CGXFormulaSheet);
	((_core*)pCore)->m_nExpressionValueType = GX_VALUE_EXPRESSION;
	GXEnableWorksheetFunctions();
	
	CGXGridParam* pParam = NULL;

	pParam =  pCore->GetParam();
	
	ASSERT(pParam != NULL);
		
	
	CGXData* pData = pParam->GetData();
	
	ASSERT(pData != NULL);
		
	if(pParam && pData && !pData->IsKindOf(RUNTIME_CLASS(CGXFormulaSheet)))
	{
		CGXData* pData = (CGXData*)new CGXFormulaSheet();
		CGXData* pOrigData = pParam->GetData();
		*pData = *pOrigData;
		pParam->SetData(pData, TRUE);
	}

	TRACE1("The row count is %x\n", pCore->GetRowCount());
	TRACE1("The column count is %x\n", pCore->GetColCount());

	// call the formula handler helper code
	gx_xls_do_formula(&m_formulaStruct, pCore);

	//apply formatting
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);

	ASSERT(pTable != NULL);

	CGXStyle* pStyle = pCore->CreateStyle();
	pTable->ApplyToObject(m_formulaStruct.ixfe, pStyle);
	pCore->SetStyleRange(CGXRange(m_formulaStruct.rw+1, m_formulaStruct.col+1), *pStyle);
	
	if(pStyle)
		pCore->RecycleStyle(pStyle);
	

	return TRUE;
}

//CGXExcelBOFHandler
CGXExcelBOFHandler::CGXExcelBOFHandler()
{
	ResetInternalState();
}

CGXExcelBOFHandler::~CGXExcelBOFHandler()
{
	// no implementation
}

BOOL CGXExcelBOFHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD /*dwLength*/)
{
	static GXREADSEEKDATA readData[3];
	
	readData[0].Init(&m_bofStruct.vers); //version
	readData[1].Init(&m_bofStruct.dt); //type
	
	readData[2].Init((BYTE*)NULL, 4, gxseek); // ignore the others

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 3))

	// does not call the base class. Data will be interpreted by the caller
	return TRUE;
}

BOOL CGXExcelBOFHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT /*nTabIndex*/ /*= 0*/)
{
	WORD vers(0x0600); // Version number for BIFF 8
	WORD dt = (p.vt == nullPtr) ? 0x0005 : 0x0010; // the style of sub stream 
	WORD rupBuild(0x0DBB);
	WORD rupYear(0x07CC);
	
	// fill these two fields
	DWORD bfh(0);
	DWORD sfo(0x0600); // the earliest Excel version that can read all the fields that
	// we write

	HRESULT hr(S_OK);
	//egxExcelRWFlags flags(egxSuccess);

	// bfh
	_gxExSetDWBitEx(bfh, 0, 1); // To indicate that this was last edited on Windows
	
	_gxdata(wr)
			_gxw(typeBOF) // 2
			_gxw(GX_EX_SIZEOF_BOF - 4) // 2
			_gxw(vers) //2
			_gxw(dt) // 2
			_gxw(rupBuild) // 2
			_gxw(rupYear) // 2
			_gxdw(bfh) // 4
			_gxdw(sfo) // 4
	_gxend
						
	// Total ---> 20 BYTES for BOF Handler BIFF 8

	ULONG cb(0);
	
	BYTE pszBuffer[GX_EX_SIZEOF_BOF];
	
	_gxExWrite(wr, pszBuffer);
	GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_BOF, &cb));
	GXEXDUMP(pszBuffer, GX_EX_SIZEOF_BOF)
	dwLength+=cb;
	
	return TRUE;
}

void CGXExcelBOFHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelBOFHandler::ResetInternalState called\n");
}

// CGXExcelBlankHandler
CGXExcelBlankHandler::CGXExcelBlankHandler()
{
	ResetInternalState();
};

CGXExcelBlankHandler::~CGXExcelBlankHandler()
{
	// no implementation
}

BOOL CGXExcelBlankHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[3];
	
	readData[0].Init(&m_blankStruct.rw); // row
	readData[1].Init(&m_blankStruct.col); // column
	readData[2].Init(&m_blankStruct.ixfe); // XF index
	
	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 3))

	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelBlankHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT /*nTabIndex*/ /*= 0*/)
{
	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}

void CGXExcelBlankHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelBlankHandler::ResetInternalState called\n");
	memset(&m_blankStruct, 0, sizeof(CGXExcelBlankHandler::blankStruct));
}


BOOL CGXExcelBlankHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	ROWCOL nRow = m_blankStruct.rw + 1;
	ROWCOL nCol = m_blankStruct.col + 1;

	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);
	ASSERT(pTable != NULL);
	CGXStyle* pStyle = pCore->CreateStyle();
		
	pTable->ApplyToObject( (m_blankStruct.ixfe), pStyle);
	
	if(GetOptimizedMode())
		pCore->GetParam()->GetData()->StoreStyleRowCol(nRow, nCol, pStyle, gxOverride);
	else
		pCore->SetStyleRange(CGXRange(nRow, nCol), *pStyle);
	
	if(pStyle)
			pCore->RecycleStyle(pStyle);
	
	return TRUE;
}

// CGXExcelMulBlankHandler
CGXExcelMulBlankHandler::CGXExcelMulBlankHandler()
{
	m_mblankStruct.pixfe = 0;
}

CGXExcelMulBlankHandler::~CGXExcelMulBlankHandler()
{
	// no implementation
}

BOOL CGXExcelMulBlankHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[4];
	
	readData[0].Init(&m_mblankStruct.rw); // row
	readData[1].Init(&m_mblankStruct.colFirst); // First column
	
	UINT ixfeSize = (dwLength - GX_EX_FIXEDOFFSET - 3*sizeof(WORD))/sizeof(short);
	m_mblankStruct.pixfe = new short[ixfeSize];
	
	readData[2].Init( (BYTE*)m_mblankStruct.pixfe, ixfeSize*sizeof(short), gxread); // read the array of ixfe shorts
	readData[3].Init(&m_mblankStruct.colLast); // Last column

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 4))

	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelMulBlankHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT /*nTabIndex*/ /*= 0*/)
{
	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}

void CGXExcelMulBlankHandler::ResetInternalState()
{
	if(m_mblankStruct.pixfe != NULL)
		delete [] m_mblankStruct.pixfe;

	TRACE0("Info: CGXExcelMulBlankHandler::ResetInternalState called\n");
	memset(&m_mblankStruct, 0, sizeof(CGXExcelMulBlankHandler::mblankStruct));
}


BOOL CGXExcelMulBlankHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	ROWCOL nRow = m_mblankStruct.rw + 1;
	
	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);
	ASSERT(pTable != NULL);
	CGXStyle* pStyle = pCore->CreateStyle();

	BOOL bOp = GetOptimizedMode();
	for (ROWCOL nCol(m_mblankStruct.colFirst); nCol <= m_mblankStruct.colLast; nCol++)
	{
		pTable->ApplyToObject( (m_mblankStruct.pixfe[nCol-m_mblankStruct.colFirst]), pStyle);
		
		if(bOp)
			pCore->GetParam()->GetData()->StoreStyleRowCol(nRow, nCol + 1, pStyle, gxOverride);
		else
			pCore->SetStyleRange(CGXRange(nRow, nCol+1), *pStyle);
		
		pStyle->Free();
	}

	if(pStyle)
			pCore->RecycleStyle(pStyle);
	
	return TRUE;
}

//CGXExcelLabelSSTHandler
CGXExcelLabelSSTHandler::CGXExcelLabelSSTHandler()
{
	ResetInternalState();
}

CGXExcelLabelSSTHandler::~CGXExcelLabelSSTHandler()
{
	// no implementation
}

BOOL CGXExcelLabelSSTHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	//WORD wLength(0);

	static GXREADSEEKDATA readData[4];

	readData[0].Init(&m_sslStruct.row); //row
	readData[1].Init(&m_sslStruct.col); //column
	readData[2].Init(&m_sslStruct.ixfe); //index to XF record
	readData[3].Init(&m_sslStruct.ixsst); // Length of the string
	
	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 4))
	
	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelLabelSSTHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT /*nTabIndex*/ /*= 0*/)
{
	// This will not be implemented. We will write out as labels as with Excel 95/97
	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}


void CGXExcelLabelSSTHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelLabelSSTHandler::ResetInternalState called\n");
		
	m_sslStruct.row = 0;
	m_sslStruct.col = 0;

	m_sslStruct.ixfe = 0;
	m_sslStruct.ixsst = 0;
}


BOOL CGXExcelLabelSSTHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	ASSERT(pCore!=NULL);

	CGXExcelSSTTable* pTable = (CGXExcelSSTTable*) GXExGetTableMap()->LocateHandler(typeSST);

	ASSERT(pTable!=NULL);
	
	CGXStyle* pStyle = pCore->CreateStyle();

	pTable->ApplyToObject(m_sslStruct.ixsst, pStyle);

	CGXExcelXFTable* pXFTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);

	ASSERT(pXFTable != NULL);
	
	pXFTable->ApplyToObject(m_sslStruct.ixfe, pStyle);

	// change profile 1
	if( GetOptimizedMode() )
		pCore->GetParam()->GetData()->StoreStyleRowCol(m_sslStruct.row+1, m_sslStruct.col+1, pStyle, gxOverride);
	else
		pCore->SetStyleRange(CGXRange(m_sslStruct.row+1, m_sslStruct.col+1), *pStyle);
	
	if(pStyle)
		pCore->RecycleStyle(pStyle);

	return TRUE;
}


//
// CGXExcelDimensionHandler
CGXExcelDimensionHandler::CGXExcelDimensionHandler()
{
	ResetInternalState();
}

CGXExcelDimensionHandler::~CGXExcelDimensionHandler()
{
	// no implementation
}

BOOL CGXExcelDimensionHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	//WORD wLength(0);

	static GXREADSEEKDATA readData[5];

	readData[0].Init(&m_dimStruct.rwMic); //row
	readData[1].Init(&m_dimStruct.rwMac); // last row + 1
	readData[2].Init(&m_dimStruct.colMic); // column
	readData[3].Init(&m_dimStruct.colMac); // last column
	readData[4].Init(&m_dimStruct.wRes); // reserved

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 5))
	
	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelDimensionHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT /*nTabIndex*/ /*= 0*/)
{
	ASSERT(p.vt == CGXExcelHandler::corePtr); //This has to be a CGXGridCore pointer
	
	if(p.vt != CGXExcelHandler::corePtr)
		throw egxWriteInvalidData;
	
	HRESULT hr(S_OK);
	
	CGXGridCore* pCore = p.pCore;
	
	ASSERT(pCore != NULL);
	
	if(pCore == NULL)
		throw egxInvalidGrid;

	ROWCOL nRowCount = pCore->GetRowCount();
	ROWCOL nColCount = pCore->GetColCount();

	if(CGXExcelHandler::GetClipMode())
	{
		if(nRowCount)
			nRowCount--;
		if(nColCount)
			nColCount--;
	}

	BYTE pszBuffer[GX_EX_SIZEOF_DIMENSION];

	_gxdata(wr)
			_gxw(typeDimension)
			_gxw(GX_EX_SIZEOF_DIMENSION - 4)
			_gxdw(0)
			_gxdw(nRowCount)
			_gxw(0)
			_gxw(nColCount)
			_gxw(0)
	_gxend
								
	ULONG cb(0);
	_gxExWrite(wr, pszBuffer);

	GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_DIMENSION, &cb));
	GXEXDUMP(pszBuffer, GX_EX_SIZEOF_DIMENSION)
	dwLength+=cb;

	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}


void CGXExcelDimensionHandler::ResetInternalState()
{
	if(GetClipMode() == TRUE)
		return;
	
	TRACE0("Info: CGXExcelDimensionHandler::ResetInternalState called\n");
	m_dimStruct.rwMic = 0;
	m_dimStruct.rwMac = 0;
	m_dimStruct.colMic = 0;
	m_dimStruct.colMac = 0;
	m_dimStruct.wRes = 0;	
}


BOOL CGXExcelDimensionHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	ASSERT(pCore!=NULL);

	ROWCOL nR = m_dimStruct.rwMac + GX_EX_DEFAULTSIZEINCREASEROW;
	ROWCOL nC = m_dimStruct.colMac + GX_EX_DEFAULTSIZEINCREASECOL;

	nR = (nR > GX_EX_DEFAULTSIZEROW) ? GX_EX_DEFAULTSIZEROW : nR;
	nC = (nC > GX_EX_DEFAULTSIZECOL) ? GX_EX_DEFAULTSIZECOL : nC;

	// we increase the row and column numbers by a pre defined amount (looks better)
	pCore->SetRowCount(nR);
	pCore->SetColCount(nC);

	return TRUE;
}

//
// CGXExcelWindow2Handler

CGXExcelWindow2Handler::CGXExcelWindow2Handler()
{
	ResetInternalState();
}

CGXExcelWindow2Handler::~CGXExcelWindow2Handler()
{
	// no implementation
}

BOOL CGXExcelWindow2Handler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[7];

	readData[0].Init(&m_Window2Struct.grbit); //Option flags
	readData[1].Init(&m_Window2Struct.rwTop); // Top row visible in the window
	readData[2].Init(&m_Window2Struct.colLeft); // Leftmost column visible in the window
	readData[3].Init(&m_Window2Struct.icvHdr); // Index to color value for row/column headings and gridlines
	readData[4].Init(&m_Window2Struct.wScaleSLV); // Zoom magnification in page break preview
	readData[5].Init(&m_Window2Struct.wScaleNormal); // Zoom magnification in normal view
	readData[6].Init(&m_Window2Struct.wRes); // reserved

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 7))
	
	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelWindow2Handler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT nTabIndex /*= 0*/)
{
	ASSERT(p.vt == CGXExcelHandler::corePtr); //This has to be a CGXGridCore pointer
	
	if(p.vt != CGXExcelHandler::corePtr)
		throw egxWriteInvalidData;
	
	HRESULT hr(S_OK);
	
	CGXGridCore* pCore = p.pCore;
	ASSERT(pCore != NULL);
	
	if(pCore == NULL)
		throw egxInvalidGrid;

	CGXGridParam* pParam = pCore->GetParam();
	ASSERT(pParam != NULL);
	
	if(pParam == NULL)
		throw egxInvalidParam;
		
	CGXProperties* pProp = pParam->GetProperties();
	ASSERT(pProp != NULL);

	if(pProp == NULL)
		throw egxInvalidProp;

	window2Struct ws;
	memset(&ws, 0, sizeof(ws));

	// initialize grbit
	// interpret and use the flags
	// Commented this out DJ: The end results are somewhat confusing.
	// There is no direct way to turn the display of the formula instead of the
	// value in Excel
	//if(pCore->GetParam()->m_nDisplayExpression == GX_EXPR_DISPLAYNEVER)
	//	_gxExSetBit(ws.grbit, 0, 0);
	//else
	
	_gxExSetBit(ws.grbit, 0, 0);
	
	if( pProp->GetDisplayVertLines() || pProp->GetDisplayHorzLines()) // Excel does not
																			  // have two settings
		_gxExSetBit(ws.grbit, 1, 1);
	else
		_gxExSetBit(ws.grbit, 1, 0);

	// Set the bit that controls display of zeros
	_gxExSetBit(ws.grbit, 4, 1);

	// This is not really 100% accurate but Excel has only one setting for Col and Row header
	// display. If you want other settings please replace with derived class in Map
	if( pCore->IsColHidden(0) || pCore->IsRowHidden(0))
		_gxExSetBit(ws.grbit, 2, 0);
	else
		_gxExSetBit(ws.grbit, 2, 1);

	BYTE pszBuffer[GX_EX_SIZEOF_WINDOW2];

	// this is the fix for the problem that Excel had with Printing OG exported data
	// what was happening was that we were not setting the selected sheet index and 
	// this was causing Excel to get confused. Do even when there was data it would refuse to
	// print the data

	if(nTabIndex == 0)
		_gxExSetBit(ws.grbit, 9, 1);
	

	_gxdata(wr)
			_gxw(typeWindow2)
			_gxw(GX_EX_SIZEOF_WINDOW2 - 4)
			_gxw(ws.grbit)
			_gxw(ws.rwTop)
			_gxw(ws.colLeft)
			_gxdw(64)
			_gxw(ws.wScaleSLV)
			_gxw(ws.wScaleNormal)
			_gxdw(0) // reserved
	_gxend
								
	ULONG cb(0);
	_gxExWrite(wr, pszBuffer);
	GX_EX_WRITEEX(pStream->Write(pszBuffer,  GX_EX_SIZEOF_WINDOW2, &cb));
	GXEXDUMP(pszBuffer, GX_EX_SIZEOF_WINDOW2)
	dwLength+=cb;

	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}


void CGXExcelWindow2Handler::ResetInternalState()
{
	TRACE0("Info: CGXExcelWindow2Handler::ResetInternalState called\n");
	memset(&m_Window2Struct, 0, sizeof(m_Window2Struct));
}


BOOL CGXExcelWindow2Handler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	ASSERT(pCore!=NULL);
	
	pCore->SetTopRow(m_Window2Struct.rwTop + 1);
	pCore->SetLeftCol(m_Window2Struct.colLeft + 1);

	CGXGridParam* pParam = pCore->GetParam();

	ASSERT(pParam != NULL);

	CGXProperties* pProp = pParam->GetProperties();

	ASSERT(pProp != NULL);

	// interpret and use the flags
	if(! (m_Window2Struct.grbit & 0x01) )
		pCore->GetParam()->m_nDisplayExpression = GX_EXPR_DISPLAYNEVER;
	else
		pCore->GetParam()->m_nDisplayExpression = GX_EXPR_DISPLAYACTIVE; // the default

	
	if( (m_Window2Struct.grbit & 0x02) >> 1)
	{
		pProp->SetDisplayVertLines(TRUE);
		pProp->SetDisplayHorzLines(TRUE);
	}
	else
	{
		pProp->SetDisplayVertLines(FALSE);
		pProp->SetDisplayHorzLines(FALSE);
	}


	if( (m_Window2Struct.grbit & 0x04) >> 2)
	{
		pCore->HideRows(0, pCore->GetFrozenRows(), FALSE);
		pCore->HideCols(0, pCore->GetFrozenCols(), FALSE);	
	}
	else
	{
		pCore->HideRows(0, pCore->GetFrozenRows(), TRUE);
		pCore->HideCols(0, pCore->GetFrozenCols(), TRUE);	
	}
	
	return TRUE;
}


// CGXExcelMergedCellsHandler

CGXExcelMergedCellsHandler::CGXExcelMergedCellsHandler()
{
	m_pMergedStruct = NULL; 
	m_nCount = 0;
}

CGXExcelMergedCellsHandler::~CGXExcelMergedCellsHandler()
{
	// no implementation
}

BOOL CGXExcelMergedCellsHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[5];

// read the number of entries first
	readData[0].Init(&m_nCount); // flags
	
	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 1))
	
	if(m_nCount == 0)
		return TRUE;

	m_pMergedStruct = new mergedStruct[m_nCount];
	
	mergedStruct * pM =  m_pMergedStruct;

// now do the rest of the read in sequence
	for(WORD n(0); n < m_nCount; n++)
	{	
		readData[1].Init(&pM->nStartRow); // Top row 
		readData[2].Init(&pM->nEndRow); // End Row
		readData[3].Init(&pM->nStartCol); // Top Column
		readData[4].Init(&pM->nEndCol); // End column
		
		GXEX_TRY(ReadSeekHelper(pStream, &readData[1], 4))
		pM++;
	}
	
	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelMergedCellsHandler::WriteToStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD& dwLength, UINT /*nTabIndex*/ /*= 0*/)
{
	
	ASSERT(p.vt == CGXExcelHandler::corePtr); //This has to be a CGXGridCore pointer
	
	if(p.vt != CGXExcelHandler::corePtr)
		throw egxWriteInvalidData;
	
	HRESULT hr(S_OK);
	
	CGXGridCore* pCore = p.pCore;
	ASSERT(pCore != NULL);
	
	if(pCore == NULL)
		throw egxInvalidGrid;

	CGXGridParam* pParam = pCore->GetParam();
	ASSERT(pParam != NULL);
	
	if(pParam == NULL)
		throw egxInvalidParam;
		
	
	mergedStruct* pM = NULL;
	
	WORD nCount = (WORD)pParam->GetCoveredCellsList()->GetCount();
	
	if (nCount == 0)
		return TRUE;

	pM = new mergedStruct[nCount];
	
	mergedStruct* pIter = pM;

	POSITION pos = pParam->GetCoveredCellsList()->GetHeadPosition();
	while (pos)
	{
		CGXRange* r = pParam->GetCoveredCellsList()->GetNext(pos);
		
		pIter->nStartRow = (WORD) r->top - 1;
		pIter->nEndRow = (WORD) r->bottom - 1;
		pIter->nStartCol = (WORD) r->left - 1;
		pIter->nEndCol = (WORD) r->right - 1;
		pIter++;
	}
	
	// restore iteration pointer
	pIter = pM;

	// this is the total size including the fixed offset
	DWORD nRecSize = (GX_EX_SIZEOF_MERGEDCELL - GX_EX_FIXEDOFFSET - 2) * nCount + GX_EX_FIXEDOFFSET + 2;
	
	BYTE* pszBuffer = new BYTE[nRecSize];
	BYTE* pWrite = pszBuffer;

	_gxdata(wr)
			_gxw(typeMergedCell)
			_gxw(nRecSize - GX_EX_FIXEDOFFSET)
			_gxw(nCount)
	_gxend
								
	_gxExWrite(wr, pWrite);
	
	pWrite += (GX_EX_FIXEDOFFSET + 2); // the header size

	// now write out the rest of the stuff
	for(WORD w(0); w < nCount; w++)
	{
		_gxdata(wr)
			_gxw(pIter->nStartRow)
			_gxw(pIter->nEndRow)
			_gxw(pIter->nStartCol)
			_gxw(pIter->nEndCol)
		_gxend
								
		_gxExWrite(wr, pWrite);
	
		pIter++;

		// we have written 4 words
		pWrite += ( 4 * sizeof(WORD) );
	}

	ULONG cb(0);
	GX_EX_WRITEEX(pStream->Write(pszBuffer,  nRecSize, &cb));
	dwLength+=cb;
	
	if(pszBuffer != NULL)
		delete[] pszBuffer;
	
	if(pM != NULL)
		delete[] pM;

	return CGXExcelHandler::WriteToStream(pStream, p, dwLength);
}


void CGXExcelMergedCellsHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelMergedCellsHandler::ResetInternalState called\n");
	
	if(m_pMergedStruct != NULL)
		delete m_pMergedStruct;
	
	m_pMergedStruct = NULL;
	m_nCount = 0;
}


BOOL CGXExcelMergedCellsHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	ASSERT(pCore!=NULL);
	
	if(pCore == NULL)
		throw;
	
	mergedStruct * p =  m_pMergedStruct;

	for(WORD n(0); n < m_nCount; n++)
	{	
		pCore->SetCoveredCellsRowCol(p->nStartRow+1, p->nStartCol+1, p->nEndRow+1, p->nEndCol+1);
		p++;
	}
	
	return TRUE;
}

// CGXExcelNumberHandler handler
//
CGXExcelNumberHandler::CGXExcelNumberHandler()
{
	// no implementation
}
	
CGXExcelNumberHandler::~CGXExcelNumberHandler()
{
	// no implementation
}

BOOL CGXExcelNumberHandler::ReadFromStream(IStream* pStream, CGXExcelHandler::gxexpointer p, DWORD dwLength)
{
	static GXREADSEEKDATA readData[4];

	readData[0].Init(&m_numberStruct.row); // row
	readData[1].Init(&m_numberStruct.col); // column
	readData[2].Init(&m_numberStruct.ixfe); // ixfe
	readData[3].Init(&m_numberStruct.value); // value

	GXEX_TRY(ReadSeekHelper(pStream, &readData[0], 4))
	
	return CGXExcelHandler::ReadFromStream(pStream, p, dwLength);
}

BOOL CGXExcelNumberHandler::WriteToStream(IStream* /*pStream*/, CGXExcelHandler::gxexpointer /*p*/, DWORD& /*dwLength*/, UINT /*nTabIndex*/ /*= 0*/)
{
	ASSERT(0); // The RK handler is the handler that writes these records
	return TRUE;
}

void CGXExcelNumberHandler::ResetInternalState()
{
	TRACE0("Info: CGXExcelNumberHandler::ResetInternalState called\n");
	memset(&m_numberStruct, 0, sizeof(m_numberStruct));
}


BOOL CGXExcelNumberHandler::InitializeCore(CGXGridCore* pCore, BOOL /*bStore*/ /* = FALSE*/)
{
	ASSERT(pCore != NULL);

	CGXExcelXFTable* pTable = (CGXExcelXFTable*) GXExGetTableMap()->LocateHandler(typeXF);

	ASSERT(pTable!=NULL);
	
	CGXStyle* pStyle = pCore->CreateStyle();

	pTable->ApplyToObject(m_numberStruct.ixfe, pStyle);
	
	if(pStyle->GetIncludeFormat() && (
										(pStyle->GetFormat() < 28 && pStyle->GetFormat() > 24)||
										(pStyle->GetFormat() == GX_FMT_TIME)
										)
									 )
									
	{
		if(!pCore->GetParam()->GetData()->IsKindOf(RUNTIME_CLASS(CGXFormulaSheet)))
			pStyle->SetValue(m_numberStruct.value);
		else
		{
			static COleDateTime dt;
			double dTime = 24 * m_numberStruct.value;
			BYTE byHrs = (BYTE) dTime;
			BYTE byMins = (BYTE)((dTime-byHrs)*60);
			BYTE bySecs = ((int)((dTime-byHrs)*3600))%60;
			

			dt.SetTime(byHrs, byMins, bySecs);

			switch (pStyle->GetFormat())
			{
				case GX_FMT_TIME_HM_AMPM	:
					pStyle->SetValue(dt.Format(_T("%I:%M %p")));
					break;
				case GX_FMT_TIME_HMS_AMPM	:
					pStyle->SetValue(dt.Format(_T("%I:%M:%S %p")));
					break;
				case GX_FMT_TIME_HM			:
					pStyle->SetValue(dt.Format(_T("%H:%M")));
					break;
				case GX_FMT_TIME			:
					pStyle->SetValue(dt.Format());
					break;
			}
		}
	}
	else
		pStyle->SetValue(m_numberStruct.value);

	if(GetOptimizedMode())
		pCore->GetParam()->GetData()->StoreStyleRowCol(m_numberStruct.row + 1, m_numberStruct.col + 1, pStyle, gxOverride);
	else
		pCore->SetStyleRange(CGXRange(m_numberStruct.row + 1, m_numberStruct.col + 1), *pStyle);

	if(pStyle)
		pCore->RecycleStyle(pStyle);

	return TRUE;
}

