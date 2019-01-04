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

#ifndef _GX_EXHND_H__
#define _GX_EXHND_H__

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

#ifndef _GX_EXMAN_H__
#include "grid\gxexman.h"
#endif

#ifndef _GX_EX_LOG_H__
#include "grid\gxexlog.h"
#endif //!_GX_EX_LOG_H__

#ifndef _GX_EX_TBL_RECSIZE_H__
#include "grid\gxexdef.h"
#endif //_GX_EX_TBL_RECSIZE_H__

// helper data structures
enum gxreadseekOp
{
	gxread,
	gxseek,
};

enum gxreadseekDataType
{
	gx_Word,
	gx_Long,
	gx_Bool,
	gx_Dword,
	gx_Short,
	gx_Int,
	gx_Tchar,
	gx_Byte,
	gx_Double,
};

// Seek data will be used by ReadSeekHelper to determine whether the operation is a read or a 
// seek and also to determine the offset as well as the actual data buffer. This will be filled 
// in from the CGXExcelHandler derivative that is making tbis call
struct GXREADSEEKDATA
{
	GXREADSEEKDATA();

	// overloaded constructors
	GXREADSEEKDATA(WORD* pwData, gxreadseekOp op = gxread);
	
	GXREADSEEKDATA(long* plData, gxreadseekOp op = gxread);
	
	GXREADSEEKDATA(DWORD* pdwData, gxreadseekOp op = gxread);
	
	GXREADSEEKDATA(short* psiData, gxreadseekOp op = gxread);
	
	GXREADSEEKDATA(int* piData, gxreadseekOp op = gxread);
	
	GXREADSEEKDATA(BYTE* piByte, gxreadseekOp op = gxread);
	
	GXREADSEEKDATA(TCHAR* pszData, DWORD dwSize = 255, gxreadseekOp op = gxread);
	
	GXREADSEEKDATA(double* pD, gxreadseekOp op = gxread);
	
	// initialization
	void Init(WORD* pwData, gxreadseekOp op = gxread);
	void Init(long* plData, gxreadseekOp op = gxread);
	void Init(DWORD* pdwData, gxreadseekOp op = gxread);
	void Init(short* psiData, gxreadseekOp op = gxread);
	void Init(int* piData, gxreadseekOp op = gxread);
	void Init(BYTE* piByte, DWORD dwSize = 1, gxreadseekOp op = gxread);
	void Init(TCHAR* pszData, DWORD dwSize = 255, gxreadseekOp op = gxread);
	void Init(double* pD, gxreadseekOp o = gxread);
	
	// union of types
	union 
	{
		WORD* pwData; //WORD
		long* plData; //long
		BOOL* pbData; //BOOL
		DWORD* pdwData; //DWORD
		short* psiData; //SHORT
		int* piData; //int
		TCHAR* pszData; //TCHAR
		BYTE* pbyData;//BYTE
		DOUBLE* pDData; //double
	};

	// the size of data
	// will be used for the actual read or seek operation
	DWORD dwSize;
	
	// the type of data held
	gxreadseekDataType type;

	// the type of operation to be performed
	gxreadseekOp op;
};

// Exception description structure
struct READSEEKEXCEP
{
	// construction
	READSEEKEXCEP(HRESULT h, DWORD dwindex);
	~READSEEKEXCEP();

	// operations
	void TraceError();
	void ReportError();
	
	void Destroy();

	//data
	HRESULT hrLast;
	DWORD dwerrorIndex;
};

// These functions perform the low level Read/Seek operation based on 
// parameters passed in.
void* ResolveReadSeekData(GXREADSEEKDATA* pReadSeekData);
BOOL ReadSeekHelper(IStream* pStream, GXREADSEEKDATA* pReadSeekData, DWORD cNum);

UINT GXExGetReadSeekOffset();
UINT& GXExGetReadSeekOffsetRef();

#define __T_CON__

template<class T>
BOOL ReadSeekHelperEx(IStream* pStream, GXREADSEEKDATA* pReadSeekData, DWORD cNum, T* pHandler)
{
	ASSERT(pReadSeekData != NULL); //---->Invalid data sent

	HRESULT hr = S_OK;
	ULONG ulRead(0);
	void* pVoid = NULL;

	DWORD dwOffsetLeft(0);

	for (DWORD dw = 0; dw < cNum ; dw++)
	{
		ASSERT(pReadSeekData->op == gxread || pReadSeekData->op == gxseek);

		dwOffsetLeft =  pHandler->GetRecordLength() - pHandler->GetRecordOffset();

		TRACE1("ReadSeekHelperEx: Offset left: %x\n", dwOffsetLeft);

		if(pReadSeekData->op == gxread)
		{
			pVoid = ResolveReadSeekData(pReadSeekData); 
		
			if(pReadSeekData->dwSize < dwOffsetLeft)
			{
				hr = pStream->Read(pVoid, pReadSeekData->dwSize, &ulRead);
				pHandler->SetRecordOffset(ulRead);
			}
			else if(pReadSeekData->dwSize == dwOffsetLeft)
			{
				// 2 part read
				hr = pStream->Read(pVoid, dwOffsetLeft, &ulRead);
				
				pHandler->ResetRecordOffset();

#ifndef __T_CON__
				// do a seek on the continue record
				LARGE_INTEGER lit;
				LISet32(lit, GX_EX_SIZEOF_CONTINUE);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
#else
				WORD wType(0);
				WORD wLength(0);
				hr = pStream->Read(&wType, sizeof(WORD), &ulRead);
						
				if(wType != 0x003C)
				{
					LARGE_INTEGER lit;
					LISet32(lit, -2);
			
					hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
					
					GXExGetReadSeekOffsetRef() += pReadSeekData->dwSize;

					return TRUE;
				}
				
				hr = pStream->Read(&wLength, sizeof(WORD), &ulRead);
				
				pHandler->SetRecordLength(wLength);
#endif
			}
			else
			{
				// 2 part read
				hr = pStream->Read(pVoid, dwOffsetLeft, &ulRead);
				
				pHandler->ResetRecordOffset();

				pVoid = ((BYTE*)pVoid) + ulRead;

#ifndef __T_CON__
				// do a seek on the continue record
				LARGE_INTEGER lit;
				LISet32(lit, GX_EX_SIZEOF_CONTINUE);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
#else
				WORD wType(0);
				WORD wLength(0);
				hr = pStream->Read(&wType, sizeof(WORD), &ulRead);
						
				
				ASSERT(wType = 0x3c);
				
				hr = pStream->Read(&wLength, sizeof(WORD), &ulRead);
				
				pHandler->SetRecordLength(wLength);

				LARGE_INTEGER lit;
				LISet32(lit, 1);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);

				pHandler->SetRecordOffset(1);
#endif
	
				hr = pStream->Read(pVoid, pReadSeekData->dwSize - dwOffsetLeft, &ulRead);
				
				pHandler->SetRecordOffset(ulRead);

			}

			GXExGetReadSeekOffsetRef() += ulRead;
			
		}
		else
		{
			LARGE_INTEGER lit;
			
			
			if(pReadSeekData->dwSize < dwOffsetLeft)
			{

				LISet32(lit, pReadSeekData->dwSize);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
				
				pHandler->SetRecordOffset(pReadSeekData->dwSize);
			}
			else if(pReadSeekData->dwSize == dwOffsetLeft)
			{
				// 2 part seek
				LISet32(lit, dwOffsetLeft);
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
				
				pHandler->ResetRecordOffset();

#ifndef __T_CON__
				// do a seek on the continue record
				LISet32(lit, GX_EX_SIZEOF_CONTINUE);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
#else
				WORD wType(0);
				WORD wLength(0);
				hr = pStream->Read(&wType, sizeof(WORD), &ulRead);
						
				if(wType != 0x003C)
				{
					LARGE_INTEGER lit;
					LISet32(lit, -2);
			
					GXExGetReadSeekOffsetRef() += pReadSeekData->dwSize;
					
					hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
					
					return TRUE;
				}
						
				hr = pStream->Read(&wLength, sizeof(WORD), &ulRead);
					
				pHandler->SetRecordLength(wLength);

#endif
			}
			else
			{
					// 2 part seek
				LISet32(lit, dwOffsetLeft);
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
				
				pHandler->ResetRecordOffset();

#ifndef __T_CON__
				// do a seek on the continue record
				LISet32(lit, GX_EX_SIZEOF_CONTINUE);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
#else
				WORD wType(0);
				WORD wLength(0);
				hr = pStream->Read(&wType, sizeof(WORD), &ulRead);
						
				ASSERT(wType == 0x3C);
						
				hr = pStream->Read(&wLength, sizeof(WORD), &ulRead);
					
				pHandler->SetRecordLength(wLength);

				LARGE_INTEGER lit;
				LISet32(lit, 1);
			
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);

				pHandler->SetRecordOffset(1);
#endif


				LISet32(lit, pReadSeekData->dwSize - dwOffsetLeft);
				hr = pStream->Seek(lit, STREAM_SEEK_CUR, NULL);
				
	
				pHandler->SetRecordOffset(pReadSeekData->dwSize - dwOffsetLeft);
			}


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



UINT GXExGetReadSeekOffset();
void GXExSetReadSeekOffset(UINT nOffset);


// This is the base class for all record specific handlers. This class lays out the interaction interface 
// for each label type (between the Excel data and that of a Objective Grid Data Structure)
class CGXExcelHandler : public CObject
{
	DECLARE_DYNAMIC(CGXExcelHandler)
public:
	// construction
	CGXExcelHandler();
	virtual ~CGXExcelHandler();

	// data declarations
	enum gxexType
	{
		nullPtr,
		corePtr,
		stylePtr,
		paramPtr,
		dataPtr
	};
	
	// nested classes
	struct gxexpointer
	{
		// default is core pointer
		gxexpointer(void* pv);

		gxexpointer();

		gxexpointer(CGXGridCore* p);

		virtual ~gxexpointer();
		
		// data
		gxexType vt;

		union
		{
			CGXGridCore* pCore;
			CGXGridParam* pParam;
			CGXStyle* pStyle;
			CGXData* pData;
		};
	};

	// operations
	
	// Read/Write from/to stream
	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);
		
	// logging support
	virtual void LogText(const TCHAR* pszText);
	virtual void LogNumber(int nNum, BOOL bTerminate = FALSE);
	virtual void LogXNumber(int nNum, BOOL bTerminate = FALSE);
	
	// public for the base class
	virtual void ResetInternalState() = 0;

	// static functions
	static CGXExcelLogger* GetLogger();
	static void SetCanLog(BOOL bCanLog);
	static BOOL GetClipMode();
	static void SetClipMode(BOOL b);
	
	static CGXExcelLogger* s_pLogger;

	static BOOL GetOptimizedMode();
	static void SetOptimizedMode(BOOL b);

	// this is used for dealing with continue records
	DWORD GetRecordOffset() const;
	void SetRecordOffset(DWORD dw, BOOL bInc = TRUE );
	void ResetRecordOffset();
	
	DWORD GetRecordLength() const;
	void SetRecordLength(DWORD dw);

protected:
	virtual BOOL DelegateHelper(gxexpointer p, BOOL bStore = FALSE);
	
	// actual init functions
	virtual BOOL InitializeStyle(CGXStyle* pStyle, BOOL bStore = FALSE);
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);
	virtual BOOL InitializeParam(CGXGridParam* pParam, BOOL bStore = FALSE);
	virtual BOOL InitializeData(CGXData* pData, BOOL bStore = FALSE);

	// data
	static BOOL m_bCanLog;
	static BOOL m_bClipMode;
	static BOOL m_bOptimized;

	DWORD m_dwRecordOffset;
	DWORD m_dwRecordLength;
};


// Concrete implementation for the LABEL record
class CGXExcelLabelHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelLabelHandler)

public:
	CGXExcelLabelHandler();
	virtual ~CGXExcelLabelHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct labelStruct
	{
		WORD row;
		WORD col;
		WORD ixfe;
		WORD wLength;
		WCHAR* buffer;
		BYTE grbit;
	} m_lStruct;

};

// CGXExcelRkHandler
class CGXExcelRkHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelRkHandler)

public:
	// construction
	CGXExcelRkHandler();
	virtual ~CGXExcelRkHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct rkStruct
	{
		WORD row;
		WORD col;
		short ixfe;
		double dblVal;
	} m_rkStruct;
};

// CGXExcelMulRkHandler
class CGXExcelMulRkHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelMulRkHandler)

public:
	CGXExcelMulRkHandler();
	virtual ~CGXExcelMulRkHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct mulrkStruct
	{
		WORD row;
		WORD colStart;
		WORD colEnd;
		BYTE* pMulRkData;
	} m_mulrkStruct;
};


// CGXExcelColInfoHandler
class CGXExcelColInfoHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelColInfoHandler)

public:
	// construction
	CGXExcelColInfoHandler();
	virtual ~CGXExcelColInfoHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct colInfoStruct
	{
		WORD colFirst;
		WORD colLast;
		WORD coldx;
		short ixfe;
		WORD grbit;
	} m_colInfoStruct;
};

//CGXExcelRowHandler
class CGXExcelRowHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelRowHandler)

public:
	// construction
	CGXExcelRowHandler();
	virtual ~CGXExcelRowHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct rowInfoStruct
	{
		WORD rw;
		WORD colMic;
		WORD colMac;
		WORD miyRw;
		WORD grbit;
		short ixfe;
	} m_rowInfoStruct;
};


//CGXExcelFormulaHandler
class CGXExcelFormulaHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelFormulaHandler)
	
public:
	// construction
	CGXExcelFormulaHandler();
	virtual ~CGXExcelFormulaHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	formulaStruct m_formulaStruct;

	friend void gx_xls_do_formula(CGXExcelFormulaHandler::formulaStruct* pFormulaStruct, int row, int col, int ixfe, int flags,
					int len, WORD *data, WORD *val);
};


// BOF handler
class CGXExcelBOFHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelBOFHandler)

public:
	CGXExcelBOFHandler();
	virtual ~CGXExcelBOFHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	
	// implementation
	struct BOFStruct
	{
		WORD vers;
		WORD dt;
	} m_bofStruct;
};


//CGXExcelBlankHandler
class CGXExcelBlankHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelBlankHandler)

public:
	// construction
	CGXExcelBlankHandler();
	virtual ~CGXExcelBlankHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct blankStruct
	{
		WORD rw;
		WORD col;
		short ixfe;
	} m_blankStruct;
};


//CGXExcelMulBlankHandler
class CGXExcelMulBlankHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelMulBlankHandler)

public:
	CGXExcelMulBlankHandler();
	virtual ~CGXExcelMulBlankHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct mblankStruct
	{
		WORD rw;
		WORD colFirst;
		short* pixfe;
		WORD colLast;
	} m_mblankStruct;
};

//CGXExcelLabelSSTHandler
class CGXExcelLabelSSTHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelLabelSSTHandler)

public:
	CGXExcelLabelSSTHandler();
	virtual ~CGXExcelLabelSSTHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct labelSSTStruct
	{
		WORD row;
		WORD col;
		WORD ixfe;
		WORD ixsst;
	} m_sslStruct;
};


//
// CGXExcelDimensionHandler
class CGXExcelDimensionHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelDimensionHandler)
	
	friend class CGXExcelClipHandler;

public:
	CGXExcelDimensionHandler();
	virtual ~CGXExcelDimensionHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct dimStruct
	{
		DWORD rwMic;
		DWORD rwMac;
		WORD colMic;
		WORD colMac;
		WORD wRes;
	} m_dimStruct;
};


//
// CGXExcelWindow2Handler
class CGXExcelWindow2Handler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelWindow2Handler)

public:
	CGXExcelWindow2Handler();
	virtual ~CGXExcelWindow2Handler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

// implementation
	struct window2Struct
	{
		WORD grbit;
		WORD rwTop;
		WORD colLeft;
		DWORD icvHdr;
		WORD wScaleSLV;
		WORD wScaleNormal;
		DWORD wRes;
	} m_Window2Struct;
};

// Merged cells handler
// This does not seem to be documented anywhere.
// CGXExcelMergedCellsHandler
class CGXExcelMergedCellsHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelMergedCellsHandler)

public:
	CGXExcelMergedCellsHandler();
	virtual ~CGXExcelMergedCellsHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	WORD m_nCount;
	struct mergedStruct
	{
		WORD nStartRow;
		WORD nEndRow;
		WORD nStartCol;
		WORD nEndCol;
	};
		
	mergedStruct* m_pMergedStruct;
};


// CGXNumberHandler

class CGXExcelNumberHandler : public CGXExcelHandler
{
	DECLARE_DYNCREATE(CGXExcelNumberHandler)

public:
	CGXExcelNumberHandler();
	virtual ~CGXExcelNumberHandler();

	virtual BOOL ReadFromStream(IStream* pStream, gxexpointer p, DWORD dwLength);
	virtual BOOL WriteToStream(IStream* pStream, gxexpointer p, DWORD& dwLength, UINT nTabIndex = 0);

protected:
	void ResetInternalState();
	
	// handlers
	virtual BOOL InitializeCore(CGXGridCore* pCore, BOOL bStore = FALSE);

	// implementation
	struct numberStruct
	{
		WORD row;
		WORD col;
		WORD ixfe;
		double value;
	};
	
	numberStruct m_numberStruct;
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

#endif //_GX_EXHND_H__
