///////////////////////////////////////////////////////////////////////////////
// gxxrdrim.cpp
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
// Excel read/write core code. This is the code that invokes the handlers
// and tables to read and write data


#define _OG_EXPORT_IMPL

#include "stdafx.h"
#include "grid\gxxrdrim.h"
#include "grid\gxexman.h"
#include "grid\gxexlog.h"
#include "objbase.h"
#include "memory.h"
#include "grid\gxexhdr.h"
#include "grid\gxexhnd.h"
#include "grid\gxextbl.h"
#include "grid\gxexmap.h"
#include "grid\gxdcadpt.h"
#include "grid\gxhexbyte.h"
#include "grid\gxwchr.h"
#include "grid\gxexdef.h"
#include "grid\gxexmpst.h"

#pragma warning(disable: 4244 4189 4702)

// For testing
DWORD WINAPI WriteRecord(LPWSTR szRecord, IStream* pstm);

// for BIFF 8 this is the name of the stream.
// This cannot be changed normally
WCHAR* GetBiffStreamName()
{
	return L"WorkBook";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CGXExcelReader ///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

// base class for Excel Read
CGXExcelReader::CGXExcelReader()
{
	m_nReadIndex = 0;
}

CGXExcelReader::~CGXExcelReader()
{
	// No implementation
}


void CGXExcelReader::SetReadIndex(UINT index)
{
	m_nReadIndex = index;
}
	
UINT CGXExcelReader::GetReadIndex() const
{
	return m_nReadIndex;
}

CGXWriteEntry::CGXWriteEntry(const int t, gxTableHandler hType, gxPassData d /*= gxPassOne*/)
{
	type = 	t;
	data = d;
	handlerType = hType;
}

CGXWriteEntry::~CGXWriteEntry()
{
	// no implementation
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CGXExcelReaderImpl ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

// CGXExcelReaderImpl implementation
CGXExcelReaderImpl::CGXExcelReaderImpl()
{
	m_eReadMode = gxExReadAll;
	m_nCTabs = 0;
}

CGXExcelReaderImpl::~CGXExcelReaderImpl()
{
}

int CGXExcelReaderImpl::SetReadMode(int eMode)
{
	int oldMode = m_eReadMode;
	m_eReadMode = eMode;
	return oldMode;
}

int CGXExcelReaderImpl::GetReadMode() const
{
	return m_eReadMode;
}

DWORD CGXExcelReaderImpl::GetDocFileCreateMode() const
{
	return STGM_READWRITE | 
		   STGM_SHARE_EXCLUSIVE | STGM_DIRECT;
}

DWORD CGXExcelReaderImpl::GetStreamCreateMode() const
{
	return STGM_READWRITE | STGM_SHARE_EXCLUSIVE |
						STGM_DIRECT;
}

DWORD CGXExcelReaderImpl::GetDocFileReadMode() const
{
	return STGM_READ | STGM_SHARE_DENY_WRITE;
}

DWORD CGXExcelReaderImpl::GetStreamReadMode() const
{
	return STGM_READWRITE | STGM_SHARE_EXCLUSIVE	|
						STGM_DIRECT;
}

DWORD CGXExcelReaderImpl::GetStorageFormatReadMode() const
{
	// MSDN:
	// Indicates that the file must be a compound file, and is similar to the STGFMT_STORAGE flag,
	// but indicates that the compound-file form of the compound-file implementation must be used. 
	//return STGFMT_DOCFILE;
	return STGFMT_ANY;
}

USHORT CGXExcelReaderImpl::GetStorageOptionsVersion() const
{
	if(NTDDI_VERSION >= NTDDI_WINXP)
	{
		return (USHORT)2;
	}else if(NTDDI_VERSION >= NTDDI_WIN2K)
	{
		return (USHORT)1;
	}else if (NTDDI_VERSION < NTDDI_WIN2K)
	{
		return (USHORT)0;
	}
	return (USHORT)0;
}

ULONG CGXExcelReaderImpl::GetStorageFileLimits() const
{
	return 512; // 2 GB.
	//return (ULONG)4096; // Up to the file system limits.
}

void CGXExcelReaderImpl::ReadCompoundExcelFile(LPCTSTR pszFileName, CGXExcelDocAdapter* pDocAdapter)
{
	OLECHAR pszTFile[255];

	#ifdef _UNICODE
		wcscpy(pszTFile, pszFileName);
	#else 
		int nCount = MultiByteToWideChar(CP_ACP, 0, pszFileName, -1, pszTFile, NULL);
		ASSERT(nCount);
		
		if(nCount == 0)
			throw egxFileReadError;
		
		MultiByteToWideChar(CP_ACP, 0, pszFileName, -1, pszTFile, nCount);
	#endif

	InitLogFiles();
	
	_GXEXLogText("Filename:"); _GXEXLogText(pszFileName); _GXEXLogText("\n");
	
	LPSTORAGE pStorage = NULL;
	
#if _MSC_VER >= 1600
	// SRSTUDIO-713
	//STGOPTIONS stgOptions;
	//stgOptions.usVersion = GetStorageOptionsVersion();
	//stgOptions.ulSectorSize = GetStorageFileLimits();
	HRESULT hr = ::StgOpenStorageEx(pszTFile, GetDocFileReadMode(), GetStorageFormatReadMode(), /*FILE_FLAG_NO_BUFFERING*/ 0, /*&stgOptions*/ NULL, NULL, IID_IStorage, reinterpret_cast<void**>(&pStorage));
#else
	HRESULT hr = ::StgOpenStorage(pszTFile, NULL, GetDocFileReadMode(), NULL, 0, &pStorage);
#endif 

	if(FAILED(hr))
	{
		CloseLogFiles();
		throw egxFileReadError;
	}
	else
	{
		try
		{
			ReadStorage(pStorage, pDocAdapter);
		}
		catch(...)
		{
			CloseLogFiles();
			if(pStorage)
				pStorage->Release();
			pStorage = NULL;
			throw;
		}
		
		if(pStorage)
			pStorage->Release();
	}
}

void CGXExcelReaderImpl::InitLogFiles()
{
	CGXExcelHandler::s_pLogger = CGXExcelLoggerFactory::CreateInstance();
	CGXExcelTable::s_pLogger = CGXExcelLoggerFactory::CreateInstance();

	TCHAR pszPath[255];
	memset(pszPath, 0, 255);
	
	CString strHandlerFile;
	CString strTableFile;

	if(GetTempPath(255, pszPath))
	{
		strHandlerFile = pszPath;
		strHandlerFile += GetHandlerLogName();
		strTableFile = pszPath;
		strTableFile += GetTableLogName();
	}
	else
	{
		strHandlerFile = GetHandlerLogName();
		strTableFile = GetTableLogName();
	}

	
	if(CGXExcelHandler::GetLogger() != NULL)
		CGXExcelHandler::GetLogger()->InitLogFile(strHandlerFile);
		
	if(CGXExcelTable::GetLogger() != NULL)
		CGXExcelTable::GetLogger()->InitLogFile(strTableFile);
}

void CGXExcelReaderImpl::CloseLogFiles()
{
	if(CGXExcelHandler::GetLogger() != NULL)
		CGXExcelHandler::GetLogger()->CloseLogFile();
	
	if(CGXExcelTable::GetLogger() != NULL)
		CGXExcelTable::GetLogger()->CloseLogFile();	
}

CString CGXExcelReaderImpl::GetHandlerLogName()
{
	return _T("Handler.log");
}

CString CGXExcelReaderImpl::GetTableLogName()
{
	return _T("Table.log");
}

void CGXExcelReaderImpl::ReadStream(IStream* pStream, CGXExcelDocAdapter* pDocAdapter)
{
		BOOL bSeek = FALSE; BOOL bRead(FALSE); BOOL bIndex(FALSE);

		if( (GetReadMode() & gxExReadNum) == gxExReadNum )
		{
			bSeek = TRUE;
		}
		
		if ( (GetReadMode() & gxExReadIndex) == gxExReadIndex )
		{
			bIndex = TRUE;
		}

		int nBOF = -1;
		UINT nCount(0); UINT nBoundSheet(GX_INVALID); UINT nEOFCount(0);
		ULONG ulRead(0);
		WORD wType(0); WORD wLength(0); WORD bY(0);
		DWORD dwReadPos(0);

		do
		{
			nCount++;
			bRead = FALSE;
			wType = 0;
			
			//check the type of record
			HRESULT hr = S_OK;
			
			GX_EX_TRY(pStream->Read(&wType, 2, &ulRead));
			//check the length of the record
			GX_EX_TRY(pStream->Read(&wLength, 2, &ulRead));
			_GXEXLogText("The recordtype is:"); _GXEXLogXNumber(wType, TRUE);
			_GXEXLogText("The length of this record is:"); _GXEXLogXNumber(wLength, TRUE);
			TRACE1("The recordtype is %x\n", wType);
			// TRACE1("\tThe length of this record is %d\n", wLength);
		
			dwReadPos += 4;
			dwReadPos += wLength;

			// if you have an ASSERT at this point check whether you have RTTI enabled
			// also check if your application object derives multiply from public CGXExMapHolder
			CGXExcelHandler* pHandler = GXExGetHandlerMap()->LocateHandler(wType);
		
			CGXExcelTable* pTable = NULL;

#ifndef _DEBUG
			if(pHandler == NULL)
#endif
			pTable = GXExGetTableMap()->LocateHandler(wType);

			ASSERT((pHandler && pTable) == FALSE);//-----> There cannot be both kind of handlers at the same
			// time. It has to either be a table or a regular record handler

			if((pHandler && pTable) != FALSE)
			{
				throw egxWriteHandlerNotFound; // incorrect handler code--->Check handler map
			}

			// special case for BOF record
			if (pHandler && pHandler->IsKindOf(RUNTIME_CLASS(CGXExcelBOFHandler)))
			{
				// initialize the parameter objects when in read tab number mode
				if (nBOF >= 0 && ((GetReadMode() & gxExReadNum) == gxExReadNum) && nBOF != -1 && !bIndex)
				{
					pDocAdapter->InitializeParam(nBOF, 0xFFFF);
				}
				
				nBOF++;
			}

			if(pTable && pTable->IsKindOf(RUNTIME_CLASS(CGXExcelBoundSheetTable)))
			{
				if(nBoundSheet == GX_INVALID)
				{
					nBoundSheet = 0;
				}
				nBoundSheet++;
			}

			if( (pHandler == NULL && pTable == NULL) || bSeek || (bIndex && nEOFCount != GetReadIndex() + 1 && nEOFCount != 0))
			{
				// seek to the new position since we are not reading the data
				LARGE_INTEGER lit;
				LISet32(lit, wLength);
				
				LARGE_INTEGER li;
				li.LowPart = wLength;
				GX_EX_TRY(pStream->Seek(lit, STREAM_SEEK_CUR, NULL));
			
				if(CGXExcelHandler::GetLogger() != NULL)
				{
					CGXExcelHandler::GetLogger()->LogText("No handler. Ignoring type:");
					CGXExcelHandler::GetLogger()->LogXNumber(wType, TRUE);
				}

				if(CGXExcelTable::GetLogger() != NULL)
				{
					CGXExcelTable::GetLogger()->LogText("No handler. Ignoring type:");
					CGXExcelTable::GetLogger()->LogXNumber(wType, TRUE);
				}
			}
			else if (pHandler != NULL)
			{
				pHandler->SetRecordLength(wLength);

				CGXExcelHandler::gxexpointer p;
				
				if(nBOF > 0)
				{
					p.pCore = pDocAdapter->GetGrid(nBOF-1);
				}else if(nBOF == 0)
				{
					p.pCore = pDocAdapter->GetGrid(0);
				}else
				{
					ASSERT(0);//Invalid BOF index
				}

				GXExGetTableMap()->SetCore(p.pCore);			
				
				GXExSetReadSeekOffset(0);
				pHandler->ReadFromStream(pStream, p, wLength+4);
				
				if(GXExGetReadSeekOffset() < wLength)
				{
					// do a seek for the remainder of the data to avoid propagation
					// seek to the new position since we are not reading the data
					LARGE_INTEGER lit;
					LISet32(lit, wLength - GXExGetReadSeekOffset());
				
					GX_EX_TRY(pStream->Seek(lit, STREAM_SEEK_CUR, NULL));

					TRACE0("OG Pro: Correcting unread data offset\n");
				
					if(CGXExcelHandler::GetLogger() != NULL)
					{
						CGXExcelHandler::GetLogger()->LogText("OG Pro: Correcting unread data offset for:");
						CGXExcelHandler::GetLogger()->LogXNumber(wType, TRUE);
					}
				}
			}
			else if (pTable != NULL)
			{
				pTable->SetRecordLength(wLength);

				GXExSetReadSeekOffset(0);
				pTable->ReadFromStream(pStream, wLength+4);
				
				
				if(GXExGetReadSeekOffset() < wLength)
				{
					// do a seek for the remainder of the data to avoid propagation
					// seek to the new position since we are not reading the data
					LARGE_INTEGER lit;
					LISet32(lit, wLength - GXExGetReadSeekOffset());
				
					GX_EX_TRY(pStream->Seek(lit, STREAM_SEEK_CUR, NULL));
					
					// if you hit this warning it is usually a sign that the field structure that you have read
					// is not correct. The actual size appears to be different than what you have read in.
					TRACE0("OG Pro: Correcting unread data table offset\n");
					
					if(CGXExcelTable::GetLogger() != NULL)
					{
						CGXExcelTable::GetLogger()->LogText("OG Pro: Correcting unread data offset for:");
						CGXExcelTable::GetLogger()->LogXNumber(wType, TRUE);
					}
				}
			}

			bY = 0;
			BYTE_CHECK(bY, wType)

			if(bY == typeEOF)
			{
				nEOFCount++;
			}
		
			if(ulRead == 0)
			{
				break;
			}
		}
		while( bY != typeEOF || nBoundSheet == GX_INVALID || (nEOFCount < nBoundSheet + 1) 
			 && ( ((GetReadMode() & gxExReadNum) == gxExReadNum) || (nEOFCount < GetTabCount() + 1) )
			 );

		if(CGXExcelHandler::GetClipMode() == FALSE)
		{
			//apply the standard style (normal style in Excel)
			CGXExcelXFTable* pTable = (CGXExcelXFTable* ) GXExGetTableMap()->LocateHandler(typeXF);

			ASSERT(pTable != NULL);

			// The zero entry is the Standard Style
			CGXStyle* pStyle = NULL;
			pTable->ApplyToObject(0, pStyle);
			
			CGXExcelBoundSheetTable* pbsTable = (CGXExcelBoundSheetTable*) GXExGetTableMap()->LocateHandler(typeBoundSheet);

			CString strTabName;
			CString* pStrTabName = &strTabName;
			for(nCount = 0; nCount < m_nCTabs ; nCount++)
			{
				if(bIndex && nCount != GetReadIndex())
				{
					continue;
				}

				CGXGridCore* pCore = pDocAdapter->GetGrid(nCount);

				pCore->ChangeStandardStyle(*pStyle);
				
				pbsTable->ApplyToObject(nCount, pStrTabName);
				pCore->SetTabName(*pStrTabName);
				pCore->GetParam()->m_sSheetName = *pStrTabName;
			
				// so that the col headers are not displayed with formatted numbers
				if(pStyle->GetIncludeFormat())
				{
					pCore->ChangeRowHeaderStyle(CGXStyle().SetFormat(GX_FMT_FIXED).SetPlaces(0));
				}
			
				pCore->RefreshViews();
			}

			if(pStyle)
			{
				delete pStyle;
			}
		}

		CloseLogFiles();

		if( (GetReadMode() & gxExReadNum) == gxExReadNum)
		{
			//m_nCTabs = nBOF;
			m_nCTabs = nBoundSheet;
		}
		GXExGetTableMap()->Reset();
}

void CGXExcelReaderImpl::ReadStorage(IStorage* pStorage, CGXExcelDocAdapter* pDocAdapter)
{
		LPSTREAM pStream = NULL;	

		OLECHAR* pszStream = GetBiffStreamName();

		HRESULT hr = pStorage->OpenStream(pszStream, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE,
														0, &pStream);
		if(!FAILED(hr))
		{
			ReadStream(pStream, pDocAdapter);
			pStream->Release();
		}
		else
			throw egxProbableVersionError; // most likely is a version error
}

void CGXExcelReaderImpl::ExcelReadImpl(CArchive& ar, CGXExcelDocAdapter* pDocAdapter)
{
	// get the underlying file and read out an Excel file into the parameter object data in the
	// CGXExcelDocAdapter class
	CFile* pFile = ar.GetFile();

	ASSERT(pFile != NULL);

	if(pFile == NULL)
		throw egxFileReadError;

	CString strFilePath = pFile->GetFilePath();

	ReadCompoundExcelFile(strFilePath, pDocAdapter);
}

void CGXExcelReaderImpl::ExcelReadImpl(const CString& strFilePath, CGXExcelDocAdapter* pDocAdapter)
{
	ReadCompoundExcelFile(strFilePath, pDocAdapter);
}

// throws egxExcelRWFlags
BOOL CGXExcelReaderImpl::ProcessStorageFile(const TCHAR* psz, IStorage*& pStorage, IStream*& pStream)
{
	ASSERT(pStorage == NULL && pStream == NULL); // these are out params and have to be NULL.

	egxExcelRWFlags flags(egxSuccess);
	
	WCHAR* pszWFilePath = NULL;

	InitLogFiles();

	_GXEXLogText("Filename:"); _GXEXLogText(psz); _GXEXLogText("\n");

#ifdef _UNICODE
	pszWFilePath = NULL;
#else
	pszWFilePath = CGXWChar::ConvertDef(psz);
#endif
	// 1) If the file that gets passed in is a framework created non doc file
	// then we simply create a copy of this on disk. We then create a compound file.


	// 2) If this is an existing compound file we check to see 

		// a) If this is a Excel file: In this case we open the stream in transacted mode.
		// Will rollback if there is a write failure

		// b) If this is not an Excel file we will create a copy and then delete the file and 
		// use the name to create and use another file of the same name

	// 1)
	HRESULT hr(S_OK);
	LPSTORAGE pstr = NULL;
	LPSTREAM ps = NULL;

	if( (hr = ::StgIsStorageFile(pszWFilePath)) == S_FALSE) // check if this is a doc file
	{
		// this is a regular file
		OFSTRUCT of;
		BOOL bBackup = (::OpenFile(psz, &of, OF_EXIST) != HFILE_ERROR);
		
		if(bBackup)
		{
			CString strTempFileName(psz);
			strTempFileName = strTempFileName.Left(strTempFileName.GetLength() - GX_EX_DEFEXTSIZE) + _T("bak");
			// will overwrite the existing back file (if any)
			BOOL b = ::CopyFile(psz, strTempFileName, FALSE);
			
			if(!b)
			{
				CString strMessage;
				if(!strMessage.LoadString(GX_IDS_COPYFAILED))
					strMessage = _T("Unable to create back up copy. Do you want to continue?");;
				if(IDYES != AfxGetMainWnd()->MessageBox(strMessage, NULL, MB_YESNO|MB_ICONQUESTION))
				{
					flags = egxUserAbort;
					goto errExit;
				}
			}
			else
				::DeleteFile(psz);
		}
	}
	else if(hr == S_OK) // 2) Open the storage
	{
		hr = ::StgOpenStorage
		(
			pszWFilePath, 	//Points to the pathname of the file containing storage object
			NULL, 	//Points to a previous opening of a root storage object
			GetDocFileCreateMode()|STGM_TRANSACTED, 	//Specifies the access mode for the object
			NULL, 	//Points to an SNB structure specifying elements to be excluded
			0, 	//Reserved; must be zero
			&pstr	//Indirect IStorage pointer to the storage object on return
		);
	
		if(FAILED(hr))
		{
			flags = egxFileExistButIsInvalid;
			goto errExit;
		}
		
		hr = pstr->OpenStream(
			GetBiffStreamName(), 	//Points to name of stream to open
			NULL, 	//Reserved; must be NULL
			GetStreamCreateMode(), 	//Access mode for the new stream
			NULL, 	//Reserved; must be zero
			&ps	//Indirect pointer to opened stream object
		);
	
		if(FAILED(hr))
		{
			flags = egxFileExistButIsNotExcelFile;
			pstr->Release();
			goto errExit;
		}
		
		pStorage = pstr;
		pStream = ps;
		
#ifndef _UNICODE
		if(pszWFilePath)
			CGXWChar::FreeAllocData(pszWFilePath);
#endif

		return TRUE;
	}
	
	// create the doc file and stream
	hr = ::StgCreateDocfile(pszWFilePath, GetDocFileCreateMode(), 0, &pstr);
		
	if(FAILED(hr))
	{
		flags = egxFailDocCreate;
		goto errExit;
	}
	
	pStorage = pstr;

	// Create a workbook stream in the storage.  A BIFF8 file must
	// have at least a workbook stream.  This stream must be named "WorkBook." // Excel 97
		
	hr = pStorage->CreateStream(GetBiffStreamName(), GetStreamCreateMode(), 0, 0, &ps);
	
	if(FAILED(hr))
	{
		flags = egxStreamFailCreate;
		pStorage->Release();
		goto errExit;
	}

	pStream = ps;

	
#ifndef _UNICODE
	if(pszWFilePath)
		CGXWChar::FreeAllocData(pszWFilePath);
#endif

	return TRUE;

errExit:
	#ifndef _UNICODE
	if(pszWFilePath)
		CGXWChar::FreeAllocData(pszWFilePath);
	#endif

	GX_EX_FMT_TRACE("OG Pro Error: CGXExcelReaderImpl::ProcessStorageFile.")
	throw flags;
	return NULL;
}

// get the underlying file and write out an Excel file from the parameter object data in the
// CGXExcelDocAdapter class
void CGXExcelReaderImpl::ExcelWriteImpl(CArchive& ar, CGXExcelDocAdapter* pDocAdapter)
{
	// Get the filename
	CFile* pFile = ar.GetFile();
	ASSERT(pFile != NULL);
	
	if(pFile == NULL)
		throw egxFileReadError;

	CString strFilePath = pFile->GetFilePath();
	CGXExcelReaderImpl::ExcelWriteImpl(strFilePath, pDocAdapter);
}	

void CGXExcelReaderImpl::ExcelWriteImpl(const CString& strFilePath, CGXExcelDocAdapter* pDocAdapter)
{

	LPSTORAGE pStorage = NULL; LPSTREAM pStream = NULL;
	HRESULT hr(S_OK);

	// throws egxExcelRWFlags. Will be caught and handled by outer block
	// no other processing required at this point
	try
	{
		ProcessStorageFile(strFilePath, pStorage, pStream);
	}
	catch(egxExcelRWFlags flags)
	{
		GX_EX_FMT_TRACE("OG Pro Error: CGXExcelReaderImpl::ExcelWriteImpl.")
		CGXExRWErrorHandler::HandleError(flags);
		
		GX_THROW_LAST
		return;
	}

	try
	{
		WriteBIFFHelper(pStream, pDocAdapter);
	}
	catch(egxExcelRWFlags flags)
	{
		GX_EX_FMT_TRACE("OG Pro Error: CGXExcelReaderImpl::ExcelWriteImpl.")
		CGXExRWErrorHandler::HandleError(flags);
		
		GX_THROW_LAST
	}
	catch(...)
	{
		GX_EX_FMT_MSG()
		if(pStorage)		
			pStorage->Revert();
		
		GX_THROW_LAST
		goto exitl;
	}
	
	hr = pStorage->Commit(STGC_DEFAULT);

	if(FAILED(hr))
	{
		GX_EX_FMT_MSG()
	}
	else
	{
		CDocument* pDoc = pDocAdapter->GetParentDoc();
		if(pDoc)
			pDoc->SetModifiedFlag(FALSE);
	}

exitl:
	//close and return
	if(pStream)
		pStream->Release();

	if(pStorage)
		pStorage->Release();
}



// special instance for the color table
void gxTableProcessor(CGXExcelColorTable* pTable, gxProcessState state, gxPassData data, DWORD /*dwLength*/, UINT /*nCTab*/)
{
	if(state == gxPreProcess)
	{
		if(data == gxPassOne)
			pTable->SetWriteMode(CGXExcelColorTable::gxRead);	
		else if(data == gxPassTwo)
			pTable->SetWriteMode(CGXExcelColorTable::gxWrite);
		
		// do nothing otherwise
	}
	else
	if(state == gxPostProcess)
	{
		// do nothing
	}
	else
	{
		ASSERT(0); // the state specified is invalid. This has to be either gxPreProcess or gxPostProcess in this version
		throw;
	}
}


// special instance for the bound sheet table
void gxTableProcessor(CGXExcelBoundSheetTable* pTable, gxProcessState state, gxPassData data, DWORD dwLength, UINT nCTab)
{
	if(state == gxPreProcess)
	{
		if(data == gxPassOne)
		{
			pTable->SetSeekMode(TRUE);
			pTable->SetOffsetPos(dwLength);
		}
		else
		if(data == gxBoundSheetSpecialPass)
			pTable->GetBOFOffsetArray()->SetAtGrow(nCTab, dwLength);
	
		// do nothing otherwise
	}
	else
	if(state == gxPostProcess)
	{
		if(data == gxPassOne)
			pTable->SetSeekMode(FALSE);
	}
	else
	{
		ASSERT(0); // the state specified is invalid. This has to be either gxPreProcess or gxPostProcess in this version
		throw;
	}
}

// These maps only control the sequence of the write. They use the handlers and the table from 
// the application specific table and map handlers

// global fields
CGXWriteEntry* CGXExcelReaderImpl::GetWriteTableMap()
{
	static CGXWriteEntry _map[] = 
	{
		GX_EXCEL_WRITEMAP_ENTRY(typeBOF, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(typeWindow1, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(typePalette, gxTable)
		GX_EXCEL_WRITEMAP_ENTRY(typeFont, gxTable)
		GX_EXCEL_WRITEMAP_ENTRY(typeXF, gxTable)
		GX_EXCEL_WRITEMAP_ENTRY(typeStyle, gxTable)
		GX_EXCEL_WRITEMAP_ENTRY1(typePalette, gxTable, gxPassTwo)
		GX_EXCEL_WRITEMAP_ENTRY(typeBoundSheet, gxTable)
		GX_EXCEL_WRITEMAP_ENTRY(typeEOF, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(ixfNULL, gxHandler)
	};

	return _map;
}

// handlers for local fields
CGXWriteEntry* CGXExcelReaderImpl::GetWriteHandlerMap()
{
	static CGXWriteEntry _map[] = 
	{
		GX_EXCEL_WRITEMAP_ENTRY(typeBOF, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY1(typeBoundSheet, gxTable, gxBoundSheetSpecialPass)
		GX_EXCEL_WRITEMAP_ENTRY(typeColInfo, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(typeDimension, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(typeRow, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(typeRk, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(typeWindow2, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(typeMergedCell, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(typeEOF, gxHandler)
		GX_EXCEL_WRITEMAP_ENTRY(ixfNULL, gxHandler)
	};

	return _map;
}

void CGXExcelReaderImpl::gxTableProcessor(int /*type*/, CGXExcelHandler* pHandler, gxProcessState state, gxPassData data, DWORD dwLength, UINT nCTab)
{
	::gxTableProcessor(pHandler, state, data, dwLength, nCTab);
}

void CGXExcelReaderImpl::gxTableProcessor(int type, CGXExcelTable* pTable, gxProcessState state, gxPassData data, DWORD dwLength, UINT nCTab)
{
	switch(type)
	{
		case (typeBoundSheet):
			::gxTableProcessor( (CGXExcelBoundSheetTable*) pTable, state, data, dwLength, nCTab);
			break;
		case (typePalette):
			::gxTableProcessor( (CGXExcelColorTable*) pTable, state, data, dwLength, nCTab);
			break;
		default:
			::gxTableProcessor(pTable, state, data, dwLength, nCTab);
	}
}

// to write out a field you need to have this available in the application global map. This 
// map merely specifies the sequence of the write
void CGXExcelReaderImpl::WriteBIFFHelper(LPSTREAM pstm, CGXExcelDocAdapter* pDocAdapter, UINT nTabs)
{
	if(nTabs == GX_INVALID)
		nTabs = m_nCTabs;
	
	ASSERT(nTabs <= m_nCTabs); // the number of tabs to write out cannot be greater than the number of tabs that are present

	CGXWriteEntry* pTableMap = GetWriteTableMap();
	
	ASSERT(pTableMap != NULL); // Incorrect---> There has to be a table map that is valid for a write.
							   // Please check your override of GetWriteTableMap()

	if(pTableMap == NULL)
		throw;

	CGXExcelHandler* pHandler = NULL;
	CGXExcelTable* pTable = NULL;

	DWORD dwLength(0);

	// compose data
	CGXGridParam** pParamH = new CGXGridParam*[nTabs];
	
	// so that we are covered in case we have to throw an exception
	CGXExDeleteHlp<CGXGridParam*> 
		delHlp;
	delHlp.SetPtr(pParamH, TRUE);

	for (UINT nIndex = 0; nIndex < nTabs; nIndex++)
		pParamH[nIndex] = pDocAdapter->GetParam(nIndex);
	

	while(pTableMap->type != ixfNULL)
	{
		
		if(pTableMap->handlerType == gxTable)
		{
			// Locate handler
			pTable = GXExGetTableMap()->LocateHandler(pTableMap->type);

			BOOL bWRH(TRUE);

			if(pTable == NULL)
				bWRH = OnWriteHandlerNotFound(pTableMap->type, pstm, dwLength);

			// if there is no handler in the application map OnWriteHandlerNotFound
			// should have handled this
			ASSERT(bWRH || (pTable != NULL) );

			if(bWRH && (pTable == NULL) )
			{
				pTableMap++;
				continue;
			}

			// pre process
			gxTableProcessor(pTableMap->type, pTable, gxPreProcess, pTableMap->data, dwLength);

			// call handler
			pTable->WriteToStream(pstm, dwLength, pParamH, nTabs);
			
			if(CGXExcelTable::GetLogger() != NULL)
			{
				CGXExcelTable::GetLogger()->LogText("Type Written: ");
				CGXExcelTable::GetLogger()->LogXNumber(pTableMap->type, TRUE);
			}
			// post process
			gxTableProcessor(pTableMap->type, pTable, gxPostProcess, pTableMap->data, dwLength);
		}
		else 
		if(pTableMap->handlerType == gxHandler)
		{
			// Locate handler
			pHandler = GXExGetHandlerMap()->LocateHandler(pTableMap->type );
			
			BOOL bWRH(TRUE);

			if(pHandler == NULL)
				bWRH = OnWriteHandlerNotFound(pTableMap->type, pstm, dwLength);

			// if there is no handler in the application map OnWriteHandlerNotFound
			// should have handled this
			ASSERT(bWRH || (pHandler != NULL) );

			if(bWRH && (pHandler == NULL) )
			{
				pTableMap++;
				continue;
			}

			// pre process
			gxTableProcessor(pTableMap->type, pHandler, gxPreProcess, pTableMap->data, dwLength);

			// call handler
			// special case for global BOF
			// if(pTableMap->type == typeBOF)
			pHandler->WriteToStream(pstm, CGXExcelHandler::gxexpointer((void*)NULL), dwLength);
			
			if( CGXExcelHandler::GetLogger() != NULL)
			{
				CGXExcelHandler::GetLogger()->LogText("Type Written: ");
				CGXExcelHandler::GetLogger()->LogXNumber(pTableMap->type, TRUE);
			}
			// post process
			gxTableProcessor(pTableMap->type, pHandler, gxPostProcess, pTableMap->data, dwLength);
		}

		pTableMap++;
	}

	pTableMap = GetWriteHandlerMap();
	
	ASSERT(pTableMap != NULL); // Incorrect---> There has to be a handler map that is valid for a write.
							   // Please check your override of GetWriteHandlerMap()

	if(pTableMap == NULL)
		throw;

	// write the sheet records
	for (UINT nCTab(0); nCTab < nTabs; nCTab++ )
	{
		while(pTableMap->type != ixfNULL)
		{
			
			if(pTableMap->handlerType == gxTable)
			{
				// This is really a special case that is used by the bound sheet handler.
				// We have this structure so that this can be extended for other table handlers
				// if required
				// Locate handler
				pTable = GXExGetTableMap()->LocateHandler(pTableMap->type);

				BOOL bWRH(TRUE);

				if(pTable == NULL)
					bWRH = OnWriteHandlerNotFound(pTableMap->type, pstm, dwLength);

				// if there is no handler in the application map OnWriteHandlerNotFound
				// should have handled this
				ASSERT(bWRH || (pTable != NULL) );

				if(bWRH && (pTable == NULL) )
				{
					pTableMap++;
					continue;
				}

				// pre process
				gxTableProcessor(pTableMap->type, pTable, gxPreProcess, pTableMap->data, dwLength, nCTab);

				// post process
				gxTableProcessor(pTableMap->type, pTable, gxPostProcess, pTableMap->data, dwLength);
			}
			else 
			if(pTableMap->handlerType == gxHandler)
			{
				// Locate handler
				pHandler = GXExGetHandlerMap()->LocateHandler(pTableMap->type );
				
				BOOL bWRH(TRUE);

				if(pHandler == NULL)
					bWRH = OnWriteHandlerNotFound(pTableMap->type, pstm, dwLength);

				// if there is no handler in the application map OnWriteHandlerNotFound
				// should have handled this
				ASSERT(bWRH || (pHandler != NULL) );

				if(bWRH && (pHandler == NULL) )
				{
					pTableMap++;
					continue;
				}

				// pre process
				gxTableProcessor(pTableMap->type, pHandler, gxPreProcess, pTableMap->data, dwLength);

				// call handler
				// special case for global BOF
				// if(pTableMap->type == typeBOF)
				pHandler->WriteToStream(pstm, CGXExcelHandler::gxexpointer(pDocAdapter->GetGrid(nCTab)), dwLength, nCTab);
				
				// post process
				gxTableProcessor(pTableMap->type, pHandler, gxPostProcess, pTableMap->data, dwLength);
			}
			
			pTableMap++;
		}

		// get the map again
		pTableMap = GetWriteHandlerMap();
	}

	// special case for bound sheet offsets
	CGXExcelBoundSheetTable* pbsTable = (CGXExcelBoundSheetTable*) GXExGetTableMap()->LocateHandler(typeBoundSheet);
	ASSERT(pbsTable != NULL); // There has to be a valid bound sheet handler

	if(pbsTable == NULL)
		throw egxWriteHandlerNotFound;

	// Now write out the bound sheet record with the offsets
	pbsTable->WriteToStream(pstm, dwLength, pParamH, nTabs);

	// reset the table map (this persists data between invocations)
	GXExGetTableMap()->Reset();

	CloseLogFiles();
}	

BOOL CGXExcelReaderImpl::OnWriteHandlerNotFound(int type, LPSTREAM pstm, DWORD& dwLength)
{
	BOOL bRetval(FALSE);

	switch (type)
	{
		case typeWindow1:
			dwLength += WriteRecord(L"3d001200000069009f335d1b38000000000001005802", pstm);
			bRetval = TRUE;
			break;
		
		case typeEOF:
			dwLength += WriteRecord(L"0A000000", pstm);
			bRetval = TRUE;
			break;
		
	}
	
	return bRetval;
}


// will return the correct number of tabs in this Excel file
UINT CGXExcelReaderImpl::GetTabCount() const
{
	return m_nCTabs;
}

void CGXExcelReaderImpl::SetTabCount(UINT nTabs)
{
	m_nCTabs = nTabs;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Error handling code ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CGXExRWErrorHandler::bDisplay = TRUE; // default is that errors will popup a message box

const  CEGXTable CGXExRWErrorHandler::f_table[] = 
{	
	{egxSuccess, egxSuccess, NULL, NULL},
	{egxGenericFailure, egxGenericFailure, GX_IDS_EGXGENERICFAILURE, GX_IDS_EGXGENERICFAILURE},
	{egxUserAbort, egxUserAbort, GX_IDS_EGXUSERABORT, GX_IDS_EGXUSERABORT },
	{egxFileExistButIsInvalid, egxFileExistButIsInvalid, GX_IDS_EGXFILEEXISTBUTISINVALID, GX_IDS_EGXFILEEXISTBUTISINVALID},
	{egxFileExistButIsNotExcelFile, egxFileExistButIsNotExcelFile, GX_IDS_EGXFILEEXISTBUTISNOTEXCELFILE, GX_IDS_EGXFILEEXISTBUTISNOTEXCELFILE},
	{egxFailDocCreate, egxFailDocCreate, GX_IDS_EGXFAILDOCCREATE, GX_IDS_EGXFAILDOCCREATE},
	{egxStreamFailCreate, egxStreamFailCreate, GX_IDS_EGXSTREAMFAILCREATE, GX_IDS_EGXSTREAMFAILCREATE},
	{egxWriteHandlerNotFound, egxCodeError, GX_IDS_EGXWRITEHANDLERNOTFOUND, GX_IDS_EGXWRITEHANDLERNOTFOUND},
	{egxWriteNoData, egxWriteNoData, GX_IDS_EGXWRITENODATA, GX_IDS_EGXWRITENODATA},
	{egxWriteStream, egxFileWriteError, GX_IDS_EGXWRITESTREAM, NULL},
	{egxInvalidGrid, egxInvalidData, GX_IDS_EGXINVALIDGRID, GX_IDS_EGXINVALIDGRID},
	{egxInvalidParam, egxInvalidData, GX_IDS_EGXINVALIDPARAM, GX_IDS_EGXINVALIDPARAM},
	{egxInvalidProp, egxInvalidData, GX_IDS_EGXINVALIDPROP, GX_IDS_EGXINVALIDPROP},
	{egxInvalidStylesMap, egxInvalidData, GX_IDS_EGXINVALIDSTYLESMAP, GX_IDS_EGXINVALIDSTYLESMAP},
	{egxReadStream, egxFileReadError, GX_IDS_EGXREADSTREAM, NULL},
	{egxWriteInvalidData, egxWriteInvalidData, GX_IDS_EGXWRITEINVALIDDATA, GX_IDS_EGXWRITEINVALIDDATA},
	{egxFileWriteError, egxFileWriteError, GX_IDS_EGXFILEWRITEERROR, GX_IDS_EGXFILEWRITEERROR},
	{egxInvalidData, egxInvalidData, GX_IDS_EGXINVALIDDATA, GX_IDS_EGXINVALIDDATA},
	{egxFileReadError, egxFileReadError, GX_IDS_EGXFILEREADERROR, GX_IDS_EGXFILEREADERROR},
	{egxCodeError, egxCodeError, GX_IDS_EGXCODEERROR, GX_IDS_EGXCODEERROR},
	{egxEndPoint, egxEndPoint, NULL, NULL},
	{egxProbableVersionError, egxProbableVersionError, GX_IDS_EGXVERERROR, GX_IDS_EGXVERERROR},
			
};

void CGXExRWErrorHandler::HandleError(egxExcelRWFlags flags)
{
	const CEGXTable* pLoc = NULL;

	egxExcelRWFlags flagLoc(egxSuccess);

	pLoc = LocateEntry(flags);

	if(pLoc == NULL)
	{
		if(bDisplay)
			AfxMessageBox(GX_IDS_EGXGENERICFAILURE);
		return;
	}

#ifndef _DEBUG // only for release
	// change based on mapping
	flags = pLoc->userFlag; 
	
	// locate correct entry for mapped value
	pLoc = LocateEntry(flags);
	
	// I don't check for this but normally 
	// (pLoc->errFlag == pLoc->userFlag)
	if(pLoc == NULL)
	{
		if(bDisplay)
			AfxMessageBox(GX_IDS_EGXGENERICFAILURE);
		return;
	}
#endif

	// handle error
#ifdef _DEBUG
	if(bDisplay)
		AfxMessageBox(pLoc->nIDDevMessage);
#else
	if(bDisplay)
		AfxMessageBox(pLoc->nIDUserMessage);
#endif
}

const CEGXTable* CGXExRWErrorHandler::LocateEntry(egxExcelRWFlags flags)
{
	// locate the correct entry
	const CEGXTable* p = f_table;
	const CEGXTable* pLoc = NULL;
	while(p->errFlag != egxEndPoint)
	{
		if(flags == p->errFlag)
		{
			pLoc = p;
			break;
		}
		p++;
	}

	return pLoc;
}

// Testing code

DWORD WINAPI WriteRecord(LPWSTR szRecord, 
                         IStream* pstm)
{
	// This code is just used for testing and is from an MS Sample that writes out a simple
	// BIFF file
	DWORD dwBufSize;
	PBYTE pBuf;
	ULONG cbWritten;
	HRESULT hr;

	dwBufSize = (DWORD)wcslen(szRecord) / 2;  // Divide by 2 -> 2 chars == 1 byte
	pBuf = (BYTE*)malloc(dwBufSize);
	ZeroMemory(pBuf, dwBufSize);
	Hex2BytesW(szRecord, pBuf);
	hr = pstm->Write((VOID const HUGEP*)pBuf,dwBufSize, &cbWritten); 
	free(pBuf);
	return dwBufSize;
}
