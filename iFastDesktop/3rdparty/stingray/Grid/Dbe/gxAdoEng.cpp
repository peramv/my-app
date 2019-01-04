///////////////////////////////////////////////////////////////////////////////
// gxAdoEng.cpp : implementation of CGXADOEngine
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
// Author: Praveen Ramesh
//

#define _OG_EXPORT_IMPL

#if NTDDI_VERSION >= NTDDI_WIN8
#pragma message(_T("To suppress the backward-compatibility ADO messages, please refer to Grid's StdAfx.h file."))
#endif
#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_ADOENGINE"))
#endif

// Headers for imported classes
#ifndef _GXDBEGRID
#include "grid\dbe\gxdbegrid.h"
#endif

#ifndef _GXDBTENG
#include "grid\dbe\gxadoeng.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXADOENG")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifdef TICKCOUNT
#define _TC_(f) f
#else
#define _TC_(f)
#endif

// class CGXADOEngine

void CGXADOEngine::InitMembers()
{
	m_bIsInit = FALSE;
	//m_piRecordset = NULL;
	//m_piFields = NULL;
}
BOOL CGXADOEngine::m_bUnInitialize = TRUE;

// Use this to bind the engine to a table (with no selection criteria)
//@doc
//@mfunc
//@parm ADORecordset* | pSet | Specifies the ADO recordset from which to initialize the engine.
//@parm BOOL | bIsOpen | TRUE if the recordset is already open, FALSE if not. 
//@rem
//Use the first constructor to create an empty uninitialized ADO engine.
//You can later call Init to initialize the engine.<nl>
//Or you can call the second constructor to construct and initialize the engine in one shot.<nl>
//<nl>
//You can use Init in either case to initialize/re-initialize the engine.
//@xref <mf CGXADOEngine::Init>
CGXADOEngine::CGXADOEngine(CComPtr<ADORecordset> pSet, BOOL bIsOpen)
	:CGXScrollableCurEngine()
{
	InitMembers();
	Init(pSet, bIsOpen);
}

// Cleanup in the destructor
CGXADOEngine::~CGXADOEngine()
{
	CleanUp();
	if (m_bUnInitialize)
		CoUninitialize();
}
void CGXADOEngine::SetNoUnInitialize(BOOL bUnInitialize)
{
	m_bUnInitialize = bUnInitialize;
}

// This will be called from the destructor and from Init while reinitializing.
void CGXADOEngine::CleanUp()
{
	m_bIsInit = FALSE;
	LONG nState =0;
	BOOL bSuccess = FALSE;
	CComPtr<ADOConnection> piConnection;

	if((ADORecordset*)m_piRecordset != NULL)
    {
	    m_piRecordset->get_State(&nState);
	    if(nState ==1)
	    {
		    CComVariant var;
		    GX_ADO_CHECK(m_piRecordset->get_ActiveConnection(&var), m_piRecordset, bSuccess)
		    if(bSuccess)
		    {
		        piConnection = (ADOConnection *) V_DISPATCH(&var);
		        HRESULT hr = m_piRecordset->Close();
		        if(FAILED(hr))
		        {
		        	TRACE0("Failed to close recordset");
		        }
                else // m_piRecordset closed successfully            
                {		
                    piConnection->get_State(&nState);
		            if(nState == 1)
		            {
			            hr = piConnection->Close();
			            if(FAILED(hr))
                        {
				            TRACE0("Failed to close connection");
                        }
                    }
		        } // m_piRecordset->Closed()
	        }
            else
            {
	            TRACE0("Failed to get active connection");
		    }
        }
    }
}

//@doc
//@mfunc
//@parm ADORecordset* | pSet | Specifies the ADO recordset from which to initialize the engine.
//@parm BOOL | bIsOpen | TRUE if the recordset is already open, FALSE if not. 
//@rem
//This is a variant of the constructor-initializer 
//that can be used to re-initialize the engine. Make 
//sure to call <f CGXDBEGrid::InitFromEngine> if the schema of 
//the result set in the engine has changed to re-initialize the grid.
//@xref <mf CGXDBEGrid::InitFromEngine>
void CGXADOEngine::Init(CComPtr<ADORecordset> pSet, BOOL bIsOpen)
{
	CleanUp();
	// Will not call AddRef, so don't have to Release when done.
	// It's the app's responsibility to hold a reference to the recordset
	// and release it whenever appropriate.
	m_piRecordset = pSet;

	BOOL bSuccess = FALSE;

	if(!bIsOpen)
	{
		// Open the recordset.
		CGXWaitCursor theWait;
		COleVariant vNull;
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;
		GX_ADO_CHECK(m_piRecordset->Open(vNull, vNull, adOpenKeyset, adLockOptimistic, adCmdUnknown), m_piRecordset, bSuccess)
	}
	if(bSuccess || bIsOpen)
	{
		// Move to first record.
		m_bIsInit = TRUE;
		VARIANT_BOOL bEof;
		GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof), m_piRecordset, bSuccess)
		if(!bEof)
			GX_ADO_CHECK(m_piRecordset->MoveFirst(), m_piRecordset, bSuccess)
		if(bSuccess)
		{
			// Find the field count.
			GX_ADO_CHECK(m_piRecordset->get_Fields(&m_piFields), m_piRecordset, bSuccess)
			if(bSuccess)
			{
				long	lFieldCount = 0;
				GX_ADO_CHECK(m_piFields->get_Count(&lFieldCount), m_piRecordset, bSuccess)
				if(bSuccess)
					m_nCols = lFieldCount;
			}
		}
	}
	if(!bSuccess)
		m_bIsInit = FALSE;
}

// Fetch records in increments and as needed.

// NOTE: Call FetchRecords with LONG_MAX to fetch all the records and determine
// the total record count.

void CGXADOEngine::FetchRecords(long nRecords)
{
	if(IsEOFSeen() || (ADORecordset*)m_piRecordset == NULL  || !IsInit() || nRecords <= m_nLastRecordSeen)
		return;

	// Fetch in increments of m_nIncrement...
	if (nRecords != LONG_MAX && m_nIncrement > 1 && nRecords > 0)
		// rounds up nRecords to the next possible increment
		nRecords = ((nRecords-1) / m_nIncrement + 1) * m_nIncrement;

	// First case: is record set empty?
	BOOL bSuccess = FALSE;
	VARIANT_BOOL bBof, bEof;
	GX_ADO_CHECK(m_piRecordset->get_BOF(&bBof), m_piRecordset, bSuccess)
	GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof), m_piRecordset, bSuccess)
	if (bBof && bEof)
	{
		m_bEOF = TRUE;
		m_nLastRecordSeen = -1;
	}
	// Second case: we have to manually move through the records
	else
	{
		SyncPosition();
                // quickly move to last seen record
		long nRecordsFetched = m_nLastRecordSeen;

		MoveToPosition(nRecordsFetched);

		// and try to position to record lRecord
		VARIANT_BOOL bEof;
		GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof), m_piRecordset, bSuccess)
		if(!bSuccess) goto ErrorExit;
		while (nRecordsFetched < nRecords && !bEof)
		{
			GX_ADO_CHECK(m_piRecordset->MoveNext(), m_piRecordset, bSuccess)
			if(!bSuccess) goto ErrorExit;
			GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof), m_piRecordset, bSuccess)
			nRecordsFetched++;
		}

		// Now, save the record and the "EOF seen" state
		GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof), m_piRecordset, bSuccess)
		m_bEOF = bEof;
		m_nLastRecordSeen = nRecordsFetched-1;
		m_nCurrentCursorPos = nRecordsFetched;
	}
ErrorExit:
	return;
}

long CGXADOEngine::SyncPosition()
{
	BOOL bSuccess;
	//If not yet initialized do it...
	if (m_nCurrentCursorPos == -1)
	{
		VARIANT_BOOL bEof;
		GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof),m_piRecordset,bSuccess)
		if (!bEof)
		{
			m_nCurrentCursorPos = 0;
			GX_ADO_CHECK(m_piRecordset->MoveFirst(),m_piRecordset,bSuccess)
		}
	}

	// else just return the current cursor position
	return m_nCurrentCursorPos;
}

BOOL CGXADOEngine::MoveToPosition(long nRecord, BOOL bSync /* = TRUE*/, BOOL bThrowExceptionOnError /* = FALSE */)
{
	COleVariant varBookmark;

	BOOL bSuccess;
	if (bSync)
		SyncPosition();

	long lMove = nRecord - m_nCurrentCursorPos;

	if (lMove == 0)
		return TRUE;

	VARIANT_BOOL bEof,bBof;
	GX_ADO_CHECK(m_piRecordset->get_BOF(&bBof),m_piRecordset,bSuccess)
	GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof),m_piRecordset,bSuccess)

	if(bEof && bBof)
	{
		m_bEOF = TRUE;
		m_nLastRecordSeen = -1;
		return FALSE;
	}
	else if (lMove > 0 && !bEof || lMove < 0 && !bBof)
	{
		COleVariant vNull;
		vNull.vt = VT_NULL;
		vNull.scode = DISP_E_PARAMNOTFOUND;
		if(bEof)	//Bookmarks doesnt work for eof, so move previous
		{
			GX_ADO_CHECK(m_piRecordset->MovePrevious(),m_piRecordset,bSuccess)
			lMove++;
		}
		if(bBof)	//Bookmarks doesnt work for bof, so move next
		{
			GX_ADO_CHECK(m_piRecordset->MoveNext(),m_piRecordset,bSuccess)
			lMove--;
		}
		if(lMove < 0)
		{
			// The following code removed in OG6.1 to make use of adBookmarkCurrent..
			//GX_ADO_CHECK(m_piRecordset->get_Bookmark(&varBookmark),m_piRecordset, bSuccess)
			GX_ADO_CHECK(m_piRecordset->Move(lMove, COleVariant((long)adBookmarkCurrent)), m_piRecordset,bSuccess)
			if(!bSuccess)goto ErrorExit;
		}
		else if(lMove > 0)
		{
			// The following code removed in OG6.1 to make use of adBookmarkCurrent..
			//GX_ADO_CHECK(m_piRecordset->get_Bookmark(&varBookmark),m_piRecordset, bSuccess)
			GX_ADO_CHECK(m_piRecordset->Move(lMove, COleVariant((long)adBookmarkCurrent)),m_piRecordset,bSuccess)
			if(!bSuccess)goto ErrorExit;
		}
	}
	GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof),m_piRecordset,bSuccess)
	if(bEof)goto ErrorExit;
	m_nCurrentCursorPos = nRecord;
	return TRUE;
ErrorExit:
	//Typically happens when records have been deleted in the source by someother app
	if(bThrowExceptionOnError)
		AfxThrowUserException();

	return FALSE;
}

BOOL CGXADOEngine::CanUpdate()
{
	if(m_piRecordset && m_bIsInit)
	{
		BOOL bSuccess = FALSE;
		VARIANT_BOOL bResult;
		GX_ADO_CHECK(m_piRecordset->Supports(adUpdate, &bResult), m_piRecordset, bSuccess)
		return bResult && bSuccess;
	}
	else return FALSE;
}

BOOL CGXADOEngine::CanAppend()
{
	return CanUpdate();
}


BOOL CGXADOEngine::GetOrigFieldValue(long nRecord, long nField, CString& strValue)
{
	ASSERT(IsInit());
	if(nRecord >= GetRecordCount() || nField >= GetFieldCount())
		return FALSE;

	BOOL bSuccess = FALSE;
	CComPtr<ADOField> pAdoField;

    /* [VC7] Construct ColeVariant outside the function call, temporary
    construction causes problems.*/
	COleVariant vLong ((long)nField);
	GX_ADO_CHECK(m_piFields->get_Item(vLong, &pAdoField), m_piRecordset, bSuccess)

	if(!bSuccess)
		goto ErrorExit;

	GetADOValueAsString(strValue, pAdoField);
	return TRUE;

ErrorExit:
	return FALSE;
}

/*
// Update
//
// This method writes dirty fields back to the data source.
// This action can rise exceptions. Sometimes it is necessary
// that the method catches the exception, sometimes it is
// necessary that the exception falls through. This behavior
// is determined through the ps parameter.
//
// If ps is NULL, Update will let exceptions fall through
// If ps is a pointer to a CString, exceptions will be caught and
// ps will be initialized with the text describing the exception.

BOOL CGXADOEngine::Update(CString* ps)
{

	BOOL bAddedNewRec = FALSE;
	BOOL bSuccess;
	VARIANT_BOOL bEof, bBof;
	COleVariant vNull, varBookmark;
	vNull.vt = VT_ERROR;
	vNull.scode = DISP_E_PARAMNOTFOUND;
	GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof), m_piRecordset, bSuccess)

	GX_ADO_CHECK(m_piRecordset->get_EOF(&bBof), m_piRecordset, bSuccess)

	TRY
	{
		// Update an exisiting record
		if(m_nEditMode == edit && m_bDirty)
		{
			VERIFY(MoveToPosition(m_nEditRecord, FALSE));
		}
		// Insert a new record
		else if(m_nEditMode == CGXDBEngine::addNew && m_bDirty)
		{
			GX_ADO_CHECK(m_piRecordset->AddNew(vNull, vNull), m_piRecordset, bSuccess)
			if (!bSuccess) goto ErrorExit;
			bAddedNewRec = TRUE;
		}
		if(CGXScrollableCurEngine::Update(ps))
		{
			GX_ADO_CHECK(m_piRecordset->Update(vNull,vNull), m_piRecordset, bSuccess)
			if(!bSuccess)goto ErrorExit;

			if(bAddedNewRec)
			{
				m_bEOF = FALSE;
				m_nCurrentCursorPos = -1;
				FetchRecords(LONG_MAX);
			}
			return TRUE;
		}
	}
	CATCH(CException, e)
	{
		// ps is a valid CString if we shall catch the exception
		if (ps)
		{
			TRACE0("CGXAdoEngine::Update failed!\n");
			ps->Empty();
		}
		else
			// let exception fall through
			THROW_LAST();

		// failed, ...
		goto ErrorExit;
	}
	END_CATCH

ErrorExit:
	{
		GX_ADO_CHECK(m_piRecordset->CancelUpdate(),m_piRecordset,bSuccess)

		//move cursor to first record
		m_nCurrentCursorPos=0;
		GX_ADO_CHECK(m_piRecordset->MoveFirst(),m_piRecordset,bSuccess)

		if (ps == NULL)  // check if we should throw an exception
			AfxThrowNotSupportedException();

		return FALSE;
	}
}
*/

BOOL CGXADOEngine::OnFlushRecord(long nRecord, CString* ps)
{
	BOOL bSuccess;
	VARIANT_BOOL bEof, bBof;
	COleVariant vNull, varBookmark;
	GX_ADO_CHECK(m_piRecordset->get_EOF(&bEof), m_piRecordset, bSuccess)

	GX_ADO_CHECK(m_piRecordset->get_EOF(&bBof), m_piRecordset, bSuccess)

	// Sandwich ADORecordset into Edit/AddNew and Update
	vNull.vt = VT_ERROR;
	vNull.scode = DISP_E_PARAMNOTFOUND;

	TRY
	{
		if (m_nEditMode == CGXDBEngine::addNew)
		{
			GX_ADO_CHECK(m_piRecordset->AddNew(vNull, vNull), m_piRecordset, bSuccess)
			if (!bSuccess) return FALSE;
		}

		else
		{
			VERIFY(MoveToPosition(nRecord, FALSE));
		}

		// Force writing dirty cells to ADORecordset
		// Base class version contains the necessary functionality
		// to check all fields and call OnFlushCellValue
		CGXScrollableCurEngine::OnFlushRecord(nRecord, NULL /* force throwing an exception */);
	}
	CATCH (CException, e)
	{
		// ps is a valid CString if we shall catch the exception
		if (ps)
		{
			TRACE0("CGXADOEngine::OnFlushRecord failed!\n");

			ps->Empty();
		}
		else
			// let exception fall through
			THROW_LAST();

		// failed, ...
		goto ErrorExit;
	}
	END_CATCH

//	PreUpdateRecordset(nRow);

	GX_ADO_CHECK(m_piRecordset->Update(vNull,vNull), m_piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;

	return TRUE;
ErrorExit:
//		GridWnd()->SendMessage(WM_CANCELMODE, 0, 0);
	GX_ADO_CHECK(m_piRecordset->CancelUpdate(),m_piRecordset,bSuccess)

	//move cursor to first record
	m_nCurrentCursorPos=0;
	GX_ADO_CHECK(m_piRecordset->MoveFirst(),m_piRecordset,bSuccess)

	if (ps == NULL)  // check if we should throw an exception
		AfxThrowNotSupportedException();

	return FALSE;
}

//void CGXAdoGrid::OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR strValue)
void CGXADOEngine::OnFlushCellValue(long nEditRow, long nField, CString& strValue)
{
	// Unused:
	nEditRow;
	BOOL bSuccess;

	long lFieldCount;
	COleVariant varIndex, vNull, vFieldValue, var;
	DataTypeEnum lFieldType;

	GX_ADO_CHECK(m_piFields->get_Count(&lFieldCount), m_piRecordset, bSuccess)
	if(!bSuccess)
	{
		AfxThrowNotSupportedException();
		return;
	}
	//if (FAILED(hr))		goto ErrorExit;

	if (nField < 0 || nField >= lFieldCount)
	{
		// This case will happen if the user did insert new
		// columns, e.g. a sum based on other fields in the row.
		// If you want to do this, you should make sure that CGXADOEngine
		// does not try to write this values to the CRecordset.

		// Possible solution to avoid this message is to set
		// the column read-only or static or override this method.

		AfxThrowNotSupportedException();
		return;
	}

	CComPtr<ADOField> pField;
	varIndex.vt = VT_I4;
	varIndex.lVal = (long)nField;
	GX_ADO_CHECK(m_piFields->get_Item(varIndex, &pField), m_piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;
	GX_ADO_CHECK(pField->get_Type(&lFieldType), m_piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;
	// Make empty strings NULL
	if (strValue.GetLength() == 0)
	{
		if(lFieldType == adNumeric)
			pField->put_Value(COleVariant(_T("0")));	//adNumeric doesn't seem to accept VT_NULL
		else
		{
			vNull.vt = VT_NULL;
			pField->put_Value(vNull);
		}
	}
	else
	{
		switch (lFieldType)
		{
		case adWChar:
		case adVarWChar:
		case adLongVarWChar:
		case adChar:
		case adVarChar:
				GX_ADO_CHECK(pField->put_Value(COleVariant(strValue)), m_piRecordset, bSuccess)
				break;
		case adUnsignedTinyInt:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((BYTE) _ttoi(strValue))), m_piRecordset, bSuccess)
				break;
		case adUnsignedSmallInt:
				var.vt = VT_UI2;
				var.uiVal = (WORD)_ttoi(strValue);
				GX_ADO_CHECK(pField->put_Value(var),m_piRecordset,bSuccess)
				break;
		case adUnsignedInt:
				var.vt = VT_UINT;
				var.uintVal = (UINT)_ttoi(strValue);
				GX_ADO_CHECK(pField->put_Value(var),m_piRecordset,bSuccess)
				break;
		case adUnsignedBigInt:
				var.vt = VT_UI4;
				var.ulVal = (DWORD)_ttol(strValue);
				GX_ADO_CHECK(pField->put_Value(var),m_piRecordset,bSuccess)
				break;
		case adTinyInt:
				var.vt = VT_I1;
				var.cVal = (BYTE)_ttoi(strValue);
				GX_ADO_CHECK(pField->put_Value(var),m_piRecordset,bSuccess)
				break;
		case adSmallInt:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((SHORT) _ttoi(strValue), VT_I2)), m_piRecordset, bSuccess)
				break;
		case adInteger:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((LONG) _ttol(strValue), VT_I4)), m_piRecordset, bSuccess)
				break;
		case adBigInt:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((LONG) _ttol(strValue), VT_I8)), m_piRecordset, bSuccess)
				break;
		case adSingle:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((FLOAT) _gxttof(strValue))), m_piRecordset, bSuccess)
				break;
		case adDouble:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((DOUBLE) _gxttof(strValue))), m_piRecordset, bSuccess)
				break;
		case adNumeric:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((FLOAT) _gxttof(strValue))), m_piRecordset, bSuccess)
				break;
		case adBoolean:
			{
				BOOL bBool = _tcsicmp(strValue, _T("TRUE")) == 0;
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((SHORT) bBool, VT_BOOL)), m_piRecordset, bSuccess)
				break;
			}
		case adCurrency:
			{
				COleCurrency varCurr;
				varCurr.ParseCurrency(strValue);
				CComVariant var;
				var.vt = VT_CY;
				var.cyVal = varCurr.m_cur;
				GX_ADO_CHECK(pField->put_Value(
					var), m_piRecordset, bSuccess)
				break;
			}

		case adDBTimeStamp:
		case adDBTime:
		case adDBDate:
		case adDate:
			{
				COleDateTime varTime;
				varTime.ParseDateTime(strValue);
				CComVariant var;
				var.vt = VT_DATE;
				var.date = varTime.m_dt;
				GX_ADO_CHECK(pField->put_Value(
				var), m_piRecordset, bSuccess)
				break;
			}
		case adBinary:
		case adVarBinary:
		case adLongVarBinary:
		case adGUID:
		case adChapter:

			// This case will only happen if you have set the
			// dirty field for these columns but you have not
			// overriden this method to store the data back to
			// the recordset.
			//
			ASSERT(1);
//			SetWarningText(_T("Trying to store unsupported field type to data source"));
			AfxThrowNotSupportedException();
			return;
		}
	}
	return;
ErrorExit:
	AfxThrowNotSupportedException();
	return;
}

BOOL CGXADOEngine::DeleteRows(long nFrom, long nTo)
{
	if(nTo < nFrom)
		return FALSE;

	BOOL bSuccess = FALSE;

	CComPtr<ADOConnection> piConnection;
	CComVariant  var;
	// The following line will give a compiler error unless you have Oledb SDK 2.0 or later...
	GX_ADO_CHECK(m_piRecordset->get_ActiveConnection(&var), m_piRecordset, bSuccess)
	piConnection = (ADOConnection *) V_DISPATCH(&var);

	// Get the cursor location.
	// The position of the cursor after calling Delete seems to
	// depend on the location of the cursor.
	CursorLocationEnum curLoc = adUseClient;
	GX_ADO_CHECK(m_piRecordset->get_CursorLocation(&curLoc), m_piRecordset, bSuccess)
	int nCount = nTo-nFrom+1;

	for (int index = (int) nCount-1; index >= 0; index--)
	{
		MoveToPosition(nFrom + index);
		GX_ADO_CHECK(m_piRecordset->Delete(adAffectCurrent), m_piRecordset, bSuccess)
		if(!bSuccess) goto ErrorExit;
		if(curLoc == adUseClient)
		{
			GX_ADO_CHECK(m_piRecordset->MovePrevious(), m_piRecordset, bSuccess)
		}
		if(curLoc == adUseServer)
		{
			GX_ADO_CHECK(m_piRecordset->MoveNext(), m_piRecordset, bSuccess)
		}
		m_nCurrentCursorPos--;
	}

	return TRUE;
ErrorExit:
	GX_ADO_CHECK(m_piRecordset->CancelUpdate(), m_piRecordset, bSuccess)
	return FALSE;
}

void CGXADOEngine::Requery()
{
	//Reset high watermark
	m_bEOF = FALSE;
	long nOldLastRecordSeen= m_nLastRecordSeen;
	m_nLastRecordSeen = -1;
	m_nCurrentCursorPos = -1;
	if (m_piRecordset)
	{
		CGXWaitCursor theWait;
		BOOL bSuccess = FALSE;
		GX_ADO_CHECK(m_piRecordset->Requery(-1), m_piRecordset, bSuccess)
		// Refetch as many records as there were before the Requery
		if(nOldLastRecordSeen != -1)
			FetchRecords(nOldLastRecordSeen);
	}
}

// Convert the ADOField value into a CString
BOOL CGXADOEngine::GetADOValueAsString(CString& strRet, CComPtr<ADOField> pAdoField)
{
	COleVariant varValue;
	short nType;
	BOOL bSuccess;
	CString sFormat;
	HRESULT hr;
	FLOAT ft;

//	Removing the error check with the macro, otherwise pFields->Release crashes
//	in apps built with VC6 SP1 and SP2 (SPs released so far) !!
//	GX_ADO_CHECK(pAdoField->get_Type((DataTypeEnum*)&nType), m_piRecordset, bSuccess)
//	if(!bSuccess) goto ErrorExit;

	if(FAILED(pAdoField->get_Type((DataTypeEnum*)&nType)))
	{
		AfxMessageBox(_T("Unable to get the Type of the field successfully"));
		goto ErrorExit;
	}

	GX_ADO_CHECK(pAdoField->get_Value(&varValue), m_piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;

	switch(nType)
	{
	case adBinary:
	case adVarBinary:
	case adLongVarBinary:
	case adGUID:
	case adChapter:
		// not supported data types
		//
		// NOTE: It is possible to convert the value for these special data types
		// in the CGXControl::Draw method.
		//
		// An example would be a CGXAdoBitmapControl class, where you you could convert a
		// dbLongBinary field to a bitmap.
		//
		// Another example would be to display memo fields in a message box when
		// the user double-clicked on the memo field. If the memo-field is drawn in the
		// cell, you could simply display "Memo" in the cell without need to convert the
		// COleVariant, but when the user double-clicks on the cell, you call
		// var = m_piRecordset->GetVieldFalue(nField) and convert the COleVariant into
		// a string.
		//
		// Skipping this normally very big data types increases performance. Although
		// ìt would be possible to translate memo fields to strings, I think it should
		// be the programmers choice if he wants to display them in cells.
		//

		return FALSE;
	}

	switch(varValue.vt)
	{
	case VT_EMPTY:
	case VT_NULL:
		strRet = _T("");
		break;
	case VT_UI1:
		strRet.Format(_T("%hu"),V_UI1(&varValue));
		break;
	case VT_UI2:
		strRet.Format(_T("%hu"),V_UI2(&varValue));
		break;
	case VT_UI4:
		strRet.Format(_T("%u"),V_UINT(&varValue));
		break;
	case VT_UI8:
		strRet.Format(_T("%lu"),V_UI4(&varValue));
		break;
	case VT_I1:
		strRet.Format(_T("%hd"),V_I1(&varValue));
		break;
	case VT_I2:
		strRet.Format(_T("%hd"),V_I2(&varValue));
		break;
	case VT_I4:
		strRet.Format(_T("%d"),V_I4(&varValue));
		break;
	case VT_I8:
		strRet.Format(_T("%ld"),V_I4(&varValue));
		break;
	case VT_R4:
		strRet.Format(_T("%g"),(double)V_R4(&varValue));
		break;
	case VT_R8:
		strRet.Format(_T("%.13g"),V_R8(&varValue));
		break;
	case VT_DECIMAL:
		// Convert to float...
		// Unable to convert to string here, instead converting to float
		//hr = VarBstrFromDec(&V_DECIMAL(&varValue), LANG_SYSTEM_DEFAULT, 0, &V_BSTR(&var));
		//var.vt = VT_BSTR;
		//strRet = V_BSTRT(&var);

		{
		// If there is any loss of data override ConvertValueToString and do the conversion yourself
		hr = VarR4FromDec(&V_DECIMAL(&varValue), &ft);
		if(FAILED(hr))
			return FALSE;
		// Begin Formatting
		// Get Precision and scale from the field's properties
		short nPrec=10, nScale=2;
		BYTE cTemp;
		GX_ADO_CHECK(pAdoField->get_Precision(&cTemp), m_piRecordset, bSuccess)
		if(!bSuccess)
			ASSERT(0);	// Don't know in what format to retrieve data
						// Override ConvertValueToString and retrieve data yourself
		else
		{
			nPrec = cTemp;
			GX_ADO_CHECK(pAdoField->get_NumericScale(&cTemp), m_piRecordset, bSuccess)
			if(!bSuccess)
				ASSERT(0);	// Same workaround as above
			else
				nScale = cTemp;
		}
		sFormat.Format(_T("%%0%d.%df"), nPrec+1, nScale);	// +1 for decimal; append with 0s
		// User reported problem that CString::Format is not able to convert float to double(b'cos of %f) succesfully (even with a cast)
		// Hence using a double explicitly
		double d = (double)ft;
		strRet.Format(sFormat, d);
		// End of formatting
		// Call VariantClear instead of the destructor calling Clear()
		// To prevent bug as described in MS Article ID: Q177912
		VariantClear(&varValue);
		}
		break;
	case VT_CY:
		strRet = COleCurrency(varValue).Format();
		break;
	case VT_DATE:
		strRet = COleDateTime(varValue).Format();
		break;
	case VT_BSTR:
		strRet = (LPCWSTR)varValue.bstrVal;//$V_BSTRT(&var);
		break;
	case VT_BOOL:
		strRet = V_BOOL(&varValue) ? _T("TRUE") : _T("FALSE");
		break;
	default:
		strRet = _T("Unknown Data type");
		ASSERT(0);
		break;
	}
ErrorExit:
	return TRUE;
}

const int MAX_NUM_STRING_SIZE = 29;

// Get the display size based on the column type
long GXGetDisplaySize(CComPtr<ADOField> piField, CComPtr<ADORecordset> pRecordset)
{
	DataTypeEnum sFieldType;
	long lSize;
	BOOL bSuccess;
	GX_ADO_CHECK(piField->get_Type(&sFieldType), pRecordset, bSuccess)
	if(!bSuccess) return 0;

	// computes column size
	switch(sFieldType)
	{

	case adBoolean:
		return 4;

	case adUnsignedTinyInt:
	case adTinyInt:
		return 3;

	case adUnsignedSmallInt:
	case adUnsignedInt:
	case adSmallInt:
	case adInteger:
		return 6;

	case adUnsignedBigInt:
	case adBigInt:
		return 11;

	case adCurrency:
		return 11;

	case adSingle:
	case adDouble:
		return MAX_NUM_STRING_SIZE;

	case adDBTimeStamp:
	case adDBTime:
	case adDBDate:
	case adDate:
		// NOTE: This is the maximum supported size of a timestamp, not the average size.
		// This size accounts for intervals (the :FFF) which is not supported by many databases.
		return 24;  // DTB: 'YYYY-MM-DD HH:MM:SS:FFF'

	case adWChar:
	case adVarWChar:
	case adLongVarWChar:
	case adChar:
	case adVarChar:
		{

#if defined(_WIN64) && (NTDDI_VERSION < NTDDI_WIN8) // SRSTUDIO-1792/1867
            GX_ADO_CHECK(piField->get_DefinedSize(reinterpret_cast<__int64*>(&lSize)), pRecordset, bSuccess)
	#else
		// NOTE: If you receive an error message here, make sure you are targeting
		// the correct OS with the NTDDI_VERSION definition. 
            GX_ADO_CHECK(piField->get_DefinedSize(reinterpret_cast<long*>(&lSize)), pRecordset, bSuccess)
	#endif // _MSC_VER >= 1700

		if(!bSuccess) return 0;
		return lSize;
		}

	case adNumeric:
		{
			BYTE cSize;
			GX_ADO_CHECK(piField->get_Precision(&cSize), pRecordset, bSuccess)
			if(!bSuccess) return 0;
			return cSize+2;	// +2 for decimal point and sign
		}

	case adBinary:
	case adVarBinary:
	case adLongVarBinary:
	case adGUID:
	case adChapter:
		// not supported types, field will be hidden
		return 0;

	}
	return 0;
}

CComPtr<ADORecordset> CGXADOEngine::CreateRecordset(
	CComBSTR		bstrSource,
	CComBSTR		bstrSQL)
{
	HRESULT		hr;
	COleVariant	vNull;
	CComPtr<ADORecordset> piRecordSet;
	CComPtr<ADOConnection> piConnection;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Unable to Initialize COM"));
		goto ErrorExit;
	}
	//Intialize Connection
	hr = CoCreateInstance(CLSID_CADOConnection, NULL, CLSCTX_INPROC_SERVER, IID_IADOConnection, (LPVOID *)&piConnection);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Unable to create connection object"));
		goto ErrorExit;
	}

	if ( bstrSource == NULL || bstrSQL == NULL )
	{
		AfxMessageBox(_T("Invalid(NULL) Source name or SQL string"));
		goto ErrorExit;
	}
 	//Initialize Recordset
	hr = CoCreateInstance(CLSID_CADORecordset, NULL, CLSCTX_INPROC_SERVER, IID_IADORecordset, (LPVOID *)&piRecordSet);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Unable to create Recordset"));
		if (FAILED(hr))		goto ErrorExit;
	}


	BOOL bSuccess;
	hr = piConnection->Open( bstrSource, NULL, NULL, -1 );
 	if (FAILED(hr))
	{
		AfxMessageBox(_T("Unable to make connection to Source: ")+CString(bstrSource));
		goto ErrorExit;
	}

	hr = piRecordSet->putref_ActiveConnection(piConnection);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Unable to bind Connection/Recordset"));
		goto ErrorExit;
	}


	hr = piRecordSet->put_Source(bstrSQL);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Unable to put_Source"));
		goto ErrorExit;
	}


	// If your provider does not have cursor capabilities set use
	// put_CursorLocation(adUseClient) on the recordset before calling Open
	// to make ADO use the cursor library from the service components.

	vNull.vt = VT_ERROR;
	vNull.scode = DISP_E_PARAMNOTFOUND;
	GX_ADO_CHECK(piRecordSet->Open(vNull, vNull, adOpenKeyset, adLockOptimistic, adCmdText),piRecordSet,bSuccess)
	if(!bSuccess) goto ErrorExit;
	return piRecordSet;

ErrorExit:
	TCHAR szBuf[256];
	wsprintf(szBuf, _T("Error: %d \n"), hr);
	if (hr)
		AfxMessageBox(szBuf);
	if (m_bUnInitialize)
		CoUninitialize();
	return NULL;
}

// Support for transactions.

// BeginTrans
//
// BeginTrans calls BeginTrans on the Connection object.

void CGXADOEngine::BeginTrans(LPCTSTR pszDescription)
{
	BOOL bSuccess;
	long lTransLevel;
	CComPtr<ADOProperties> pProperties;
	CComPtr<ADOProperty> pProperty;
	CComPtr<ADOConnection> piConnection;

	if ((ADORecordset*)m_piRecordset == NULL || !IsInit())
		return;

	CComVariant var;
	// The following line will give a compiler error unless you have Oledb SDK 2.0 or later...
	GX_ADO_CHECK(m_piRecordset->get_ActiveConnection(&var), m_piRecordset, bSuccess)
	if(!bSuccess)
		goto ErrorExit;
	piConnection = (ADOConnection *) V_DISPATCH(&var);

	GX_ADO_CHECK(piConnection->get_Properties(&pProperties), m_piRecordset, bSuccess)

	GX_ADO_CHECK(pProperties->get_Item(COleVariant(_T("Transaction DDL")), &pProperty), m_piRecordset, bSuccess)

	if((ADOProperty*)pProperty == NULL || !bSuccess)
		goto ErrorExit;

	long attrib;
	GX_ADO_CHECK(pProperty->get_Attributes(&attrib), m_piRecordset, bSuccess)
	if(attrib == adPropNotSupported || !(attrib & adPropWrite))
	{
		ASSERT("Transaction not supported by this provider!!\n");
		return;
	}

	GX_ADO_CHECK(piConnection->BeginTrans(&lTransLevel), m_piRecordset, bSuccess)
	// While using the provider for ODBC and connecting to a data source via Jet
	// you cannot initiate a transaction because Jet does not allow transactions
	// on a connection when there are open recordsets associated with it...

	if(!bSuccess)
		goto ErrorExit;
	m_nTransPending++;

	pszDescription;

ErrorExit:
	return;

}

// CommitTrans
//
// CommitTrans calls CommitTrans for the Connection.

void CGXADOEngine::CommitTrans()
{
	if(m_nTransPending <= 0)
		return;

	BOOL bSuccess;
	if (!m_piRecordset || !IsInit())
		return;

	CComPtr<ADOConnection> piConnection;
	CComVariant var;
	// The following line will give a compiler error unless you have Oledb SDK 2.0 or later...
	GX_ADO_CHECK(m_piRecordset->get_ActiveConnection(&var), m_piRecordset, bSuccess)
	if(!bSuccess)
		goto ErrorExit;
	piConnection = (ADOConnection *) V_DISPATCH(&var);

	if(m_nTransPending > 0)
	{
		GX_ADO_CHECK(piConnection->CommitTrans(), m_piRecordset, bSuccess)
		if(!bSuccess)
			goto ErrorExit;
		m_nTransPending--;
	}
ErrorExit:
	// Requery the recordset first before operating on it
	// Also Reset high watermark to keep the grid in sync
	m_bEOF = FALSE;
	m_nLastRecordSeen = -1;
	m_nCurrentCursorPos = -1;
	if (m_piRecordset)
	{
		CGXWaitCursor theWait;
		m_piRecordset->Requery(-1);
	}
	// End of Requery
	return;
}

// Rollback
//
// Rollback calls Rollback for the Connection.

void CGXADOEngine::Rollback()
{
	BOOL bSuccess;

	if (!m_piRecordset || !IsInit())
		return;

	CComPtr<ADOConnection> piConnection;
	CComVariant var;
	// The following line will give a compiler error unless you have Oledb SDK 2.0 or later...
	GX_ADO_CHECK(m_piRecordset->get_ActiveConnection(&var), m_piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;
	piConnection = (ADOConnection *) V_DISPATCH(&var);

	if(m_nTransPending > 0)
	{
		GX_ADO_CHECK(piConnection->RollbackTrans(), m_piRecordset, bSuccess)
		if(!bSuccess)
			goto ErrorExit;
		m_nTransPending--;
	}

ErrorExit:
	Requery();
	return;

}


// class CGXHierADOEngine

CGXHierADOEngine::CGXHierADOEngine(CComPtr<ADORecordset> pSet, BOOL bIsOpen /*= TRUE*/)
: CGXADOEngine(pSet, bIsOpen)
{
	InitMembers();
}

// Cleanup in the destructor
CGXHierADOEngine::~CGXHierADOEngine()
{
	CleanUp();
}

void CGXHierADOEngine::InitMembers()
{
	m_pParentEngine = NULL;
	m_nChildId = -1;
	m_lRecsetCursorMovedBy = -1;
	m_nCanUpdate = -1;
}

void CGXHierADOEngine::CleanUp()
{
	CGXADOEngine::CleanUp();
	m_pParentEngine = NULL;
	m_nChildId = -1;
	m_lRecsetCursorMovedBy = -1;
	m_nCanUpdate = -1;

	// Delete child engines.
	for(int i=0; i < m_apChildEngines.GetSize(); i++)
	{
		CGXHierADOEngine* pChild = (CGXHierADOEngine*)m_apChildEngines.GetAt(i);
		if(pChild)
			delete pChild;
		m_apChildEngines.SetAt(i, NULL);
	}
}

// GetChildAt
// Creates and returns a engine corresponding to the record.

CGXDBEngine* CGXHierADOEngine::GetChildAt(long nRecord)
{
	ASSERT((ADORecordset*)m_piRecordset && IsInit());

	ASSERT(MoveToPosition(nRecord));

	CComPtr<ADOField> pAdoField;
	CGXHierADOEngine* pChildEngine = NULL;

	// If the engine already exists, return it.
	if(m_apChildEngines.GetSize() > nRecord)
	{
		if((pChildEngine = (CGXHierADOEngine*)m_apChildEngines.GetAt(nRecord)) != NULL)
			return pChildEngine;
	}

	// Else create a new one.
	BOOL bSuccess = FALSE;
	DataTypeEnum lFieldType;
	for(int i = GetFieldCount()-1; i >= 0; i--)
	{
		// Look for adChapter Field Type
		GX_ADO_CHECK(m_piFields->get_Item(
			COleVariant((long)i), &pAdoField), m_piRecordset, bSuccess)
		if(!bSuccess)goto ErrorExit;

		GX_ADO_CHECK(pAdoField->get_Type(&lFieldType), m_piRecordset, bSuccess)
		if(!bSuccess)goto ErrorExit;

		if(lFieldType == adChapter)
		{
			// Retrieve the child recordset from the record
			COleVariant varValue;
			GX_ADO_CHECK(pAdoField->get_Value(&varValue), m_piRecordset, bSuccess)
			if(!bSuccess) goto ErrorExit;

			CComPtr<ADORecordset> piChildRecSet;
			varValue.pdispVal->QueryInterface(IID_IADORecordset, (LPVOID *)&piChildRecSet);
			pChildEngine = new CGXHierADOEngine(piChildRecSet);
			pChildEngine->m_pParentEngine = this;
			pChildEngine->m_nChildId = nRecord;
			m_apChildEngines.SetAtGrow(nRecord, pChildEngine);
			break;
		}
	}
	return pChildEngine;
ErrorExit:
	return NULL;
}

CComPtr<ADORecordset> CGXHierADOEngine::GetChildRecordset()
{
	CComPtr<ADORecordset> piChildRecSet;
	CComPtr<ADOField> pAdoField;
	BOOL bSuccess = FALSE;
	DataTypeEnum lFieldType;

	for(int i = GetFieldCount()-1; i >= 0; i--)
	{
		// Look for adChapter Field Type
		GX_ADO_CHECK(m_piFields->get_Item(
			COleVariant((long)i), &pAdoField), m_piRecordset, bSuccess)
		if(!bSuccess)goto ErrorExit;

		GX_ADO_CHECK(pAdoField->get_Type(&lFieldType), m_piRecordset, bSuccess)
		if(!bSuccess)goto ErrorExit;

		if(lFieldType == adChapter)
		{
			// Retrieve the child recordset from the record
			MoveToPosition(1);
			COleVariant varValue;
			GX_ADO_CHECK(pAdoField->get_Value(&varValue), m_piRecordset, bSuccess)
			if(!bSuccess) goto ErrorExit;

			varValue.pdispVal->QueryInterface(IID_IADORecordset, (LPVOID *)&piChildRecSet);
			break;
		}
	}
ErrorExit:
	return piChildRecSet;
}

BOOL CGXHierADOEngine::AreChildrenAvailable()
{
	CComPtr<ADOField> pAdoField;
	BOOL bSuccess = FALSE;
	DataTypeEnum lFieldType;
	for(int i = GetFieldCount()-1; i >= 0; i--)
	{
		// Look for adChapter Field Type
		GX_ADO_CHECK(m_piFields->get_Item(
			COleVariant((long)i), &pAdoField), m_piRecordset, bSuccess)
		if(!bSuccess)goto ErrorExit;

		GX_ADO_CHECK(pAdoField->get_Type(&lFieldType), m_piRecordset, bSuccess)
		if(!bSuccess)goto ErrorExit;

		if(lFieldType == adChapter)
			return TRUE;
	}
ErrorExit:
	return FALSE;
}

// The MS Data Shape Provider actually refreshes the child recordset every time
// the parent recordset cursor is moved to a new record. Hence before accessing the
// child recordset make sure it contains the right data.

void CGXHierADOEngine::SyncParentRecordset()
{
	// Necessary if this is a child
	if(m_pParentEngine == NULL)
		return;

	BOOL bForceResync = FALSE;
	// Move parent cursor to the record corresponding to this child.
	// If not already there.
	if(m_pParentEngine->GetCurrentCursorPos() != m_nChildId)
	{
		bForceResync = TRUE;
		m_pParentEngine->MoveToPosition(m_nChildId);
		m_pParentEngine->m_lRecsetCursorMovedBy = m_nChildId;
	}

	// Cursor in this child recordset could have gone out of sync. So resync.
	if(bForceResync || m_pParentEngine->m_lRecsetCursorMovedBy != m_nChildId)
	{
		m_nCurrentCursorPos = -1;	// -1 will resync later in SyncPos.
		SyncPosition();
		m_pParentEngine->m_lRecsetCursorMovedBy = m_nChildId;
	}

	// The m_bEOF and m_nLastRecordSeen values should still be valid.
}

void CGXHierADOEngine::FetchRecords(long nRecords)
{
	if(IsEOFSeen() || (ADORecordset*)m_piRecordset == NULL  || !IsInit() || nRecords <= m_nLastRecordSeen)
		return;

	SyncParentRecordset();
	CGXADOEngine::FetchRecords(nRecords);
}

BOOL CGXHierADOEngine::GetOrigFieldValue(long nRecord, long nField, CString& strValue)
{
	ASSERT(IsInit());
	SyncParentRecordset();
	return CGXADOEngine::GetOrigFieldValue(nRecord, nField, strValue);
}

BOOL CGXHierADOEngine::MoveToPosition(long nRecord, BOOL bSync /* = TRUE*/, BOOL bThrowExceptionOnError /* = FALSE */)
{
	SyncParentRecordset();
	m_lRecsetCursorMovedBy = -1;
	return CGXADOEngine::MoveToPosition(nRecord, bSync, bThrowExceptionOnError);
}

BOOL CGXHierADOEngine::Update(CString* ps)
{
	SyncParentRecordset();
	return CGXADOEngine::Update(ps);
}

BOOL CGXHierADOEngine::DeleteRows(long nFrom, long nTo)
{
	SyncParentRecordset();
	return CGXADOEngine::DeleteRows(nFrom, nTo);
}

void CGXHierADOEngine::OnFlushCellValue(long nEditRow, long nField, CString& strValue)
{
	// If child, make sure the parent record is already in sync. (Enforced in the Update method).
	if(m_pParentEngine != NULL)
		ASSERT(m_pParentEngine->GetCurrentCursorPos() == m_nChildId
		&&  m_pParentEngine->m_lRecsetCursorMovedBy == m_nChildId);

	CGXADOEngine::OnFlushCellValue(nEditRow, nField, strValue);
}

BOOL CGXHierADOEngine::CanUpdate()
{
	if(m_nCanUpdate == -1)
	{
		SyncParentRecordset();
		m_nCanUpdate = CGXADOEngine::CanUpdate();
	}
	return m_nCanUpdate;
}

void CGXHierADOEngine::Requery()
{
	// If Child do not requery.
	if(m_pParentEngine)
	{
		// Requery the parent first.
		m_pParentEngine->Requery();
		// Then Resync and Refresh the engine
/*		SyncParentRecordset();
			//Reset high watermark
		m_bEOF = FALSE;
		m_nLastRecordSeen = -1;
		m_nCurrentCursorPos = -1;
		SyncPosition();
*/
	}
	else
	{
		CGXADOEngine::Requery();
		BOOL bSuccess = FALSE;
		CComPtr<ADORecordset> pSet = GetChildRecordset();
		// If parent Reinit the children with the new recordset.
		for(int i=0; i < m_apChildEngines.GetSize(); i++)
		{
			CGXHierADOEngine* pChildEngine = (CGXHierADOEngine*)m_apChildEngines.GetAt(i);
			if(pChildEngine)
			{
				ADOFields *pFields=NULL;
				if(pSet)
				{
					// Reinitialize the child with the new recordset.
					pChildEngine->m_piRecordset = pSet;
					pFields= (ADOFields *)(pChildEngine->m_piFields);    
					GX_ADO_CHECK(pChildEngine->m_piRecordset->get_Fields(&pFields), pChildEngine->m_piRecordset, bSuccess)
				}
				// Reset High watermark.
				pChildEngine->m_bEOF = FALSE;
				pChildEngine->m_nLastRecordSeen = -1;
				pChildEngine->m_nCurrentCursorPos = -1;
				pChildEngine->FetchRecords(1);
				pFields->Release();
				// The rest of the members need not be re-initialized.
			}
		}
	}
}
