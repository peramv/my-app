///////////////////////////////////////////////////////////////////////////////
// gxScrCurEng.cpp : implementation of CGXADOEngine
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

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_GXSCRCUR_ENGINE"))
#endif

// Headers for imported classes 
#ifndef _GXDBEGRID
#include "grid\dbe\gxdbegrid.h"
#endif

#ifndef _GX_SCRCUR_ENG
#include "grid\dbe\gxScrCurEng.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSCRCURENG")
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

// class CGXDBDirtyFieldStruct

CGXDBDirtyFieldStruct::CGXDBDirtyFieldStruct()
{
	bDirty = FALSE;
}

// class CGXScrollableCurEngine

CGXScrollableCurEngine::CGXScrollableCurEngine()
{
	m_nCols = -1;
	m_bDirty = FALSE;
	m_nCurrentCursorPos = -1;
	m_nLastRecordSeen = -1;
	m_paDirtyFieldStruct = NULL;
};
CGXScrollableCurEngine::~CGXScrollableCurEngine()
{
	CancelRecord();
}
// 1 based
long CGXScrollableCurEngine::GetRecordCount()
{
	ASSERT(IsInit());

	return m_nLastRecordSeen + 1;
}

// 1 based
long CGXScrollableCurEngine::GetFieldCount()
{
	ASSERT(IsInit());
	return m_nCols;
}

// Initate edit mode.
BOOL CGXScrollableCurEngine::Edit(long nRecord)
{
	if(CanUpdate() && nRecord >= GetRecordCount())
		return FALSE;
	if(m_nEditMode != noMode)
	{
		TRACE0("Cannot start an edit mode since already in edit or addNew mode\n");
		return FALSE;
	}
	// Refresh the edit buffer
	if (m_paDirtyFieldStruct)
	{
		delete[] m_paDirtyFieldStruct;
		m_paDirtyFieldStruct = NULL;
	}
	m_paDirtyFieldStruct = new CGXDBDirtyFieldStruct[GetFieldCount()+1];

	m_nEditRecord = nRecord;
	m_nEditMode = edit;
	return TRUE;
}

// Get the value in row nRecord and nField as a CString
BOOL CGXScrollableCurEngine::GetValue(long nRecord, long nField, CString& strValue)
{
	ASSERT(IsInit());
	if(m_nEditMode != addNew && nRecord >= GetRecordCount() || m_nEditMode == addNew && nRecord >= GetRecordCount()+1 || nField >= GetFieldCount())
		return FALSE;
	if(nRecord == m_nEditRecord && m_nEditMode != noMode)
	{
		// If in addnew mode, get the value from the edit buffer.
		// If in edit mode, get the value from the edit buffer, only if diry.
		if(m_nEditMode == CGXDBEngine::addNew || m_paDirtyFieldStruct[nField].bDirty)
		{
			strValue = m_paDirtyFieldStruct[nField].sValue;
			return TRUE;
		}
	}
	if(MoveToPosition(nRecord, TRUE, TRUE))	// Ask it to throw an exception if it fails.
		return GetOrigFieldValue(nRecord, nField, strValue);
	return FALSE;
}

// nRecord and nField are 1 based
BOOL CGXScrollableCurEngine::SetValue(long nRecord, long nField, CString* pStrValue)
{
	ASSERT(pStrValue);

	if(nRecord != m_nEditRecord || nField >= GetFieldCount() || m_nEditMode == noMode)
		return FALSE;

	// If same as original value then mark the field non-dirty
	// (Assuming the user is undoing a edit-operation)
	BOOL bIsUndo = FALSE;
	if(m_nEditMode == edit)
	{
		CString strOrig;
		GetOrigFieldValue(nRecord, nField, strOrig);
		if(strOrig == *pStrValue)
		{
			m_paDirtyFieldStruct[nField].sValue.Empty();
			m_paDirtyFieldStruct[nField].bDirty = FALSE;
			bIsUndo = TRUE;
		}
	}
	else if(m_nEditMode == addNew && pStrValue->IsEmpty())
	{
		m_paDirtyFieldStruct[nField].sValue.Empty();
		m_paDirtyFieldStruct[nField].bDirty = FALSE;
		bIsUndo = TRUE;
	}

	// Reset the dirty flag if there is no dirty entry...
	if(bIsUndo)
	{
		BOOL bDirty = FALSE;
		int nFields = GetFieldCount();
		for(int i=0; i<nFields; i++)
		{
			if(m_paDirtyFieldStruct[i].bDirty)
			{
				bDirty = TRUE;
				break;
			}
		}
		m_bDirty = bDirty;
		return TRUE;
	}

	// Store the data in the cache
	ASSERT(m_paDirtyFieldStruct);
	m_paDirtyFieldStruct[nField].sValue = *pStrValue;
	m_paDirtyFieldStruct[nField].bDirty = TRUE;
	m_bDirty = TRUE;

	return TRUE;
}

BOOL CGXScrollableCurEngine::Update(CString* ps /* = NULL */)
{
	if(m_nEditMode == noMode)
	{
		TRACE(_T("Update called before calling Edit or AddRow"));
		if(ps)
			*ps = _T("Error: Must call Edit or AddNew mode before calling Update.");
		return FALSE;
	}

	ASSERT(m_paDirtyFieldStruct);

	//long nFields = GetFieldCount(); // Not used
	// Write dirty cells into the data-source
	if(m_bDirty)
	{
		if (!OnFlushRecord(m_nEditRecord, ps))
			return FALSE;

		// Empty the edit buffer
		if (m_paDirtyFieldStruct)
		{
			delete[] m_paDirtyFieldStruct;
			m_paDirtyFieldStruct = NULL;
		}

		// trigger an event indicating that a new record has been added
		if (m_nEditMode == CGXDBEngine::addNew)
		{
			m_nEditMode = CGXDBEngine::noMode;
			
			OnAddedNewRecord();
		}
		m_bDirty = FALSE;
	}

	m_nEditMode = noMode;
	
	return TRUE;
}

BOOL CGXScrollableCurEngine::OnFlushRecord(long nEditRecord, CString* ps)
{
	long nFields = GetFieldCount();

	TRY
	{
		// Flush the cached values.
		for(long nField = 0; nField < nFields; nField++)
		{
			if(m_paDirtyFieldStruct[nField].bDirty)
				OnFlushCellValue(nEditRecord, nField, m_paDirtyFieldStruct[nField].sValue);
		}
	}
	CATCH(CException, e)
	{
		// if ps is a valid CString we catch the exception
		if (ps)
		{
			TRACE0("CGXScrollableCurEngine::OnFlushRecord failed!\n");
			ps->Empty();
		}
		else
			// let exception fall through
			THROW_LAST();

		// failed, ...
		return FALSE;
	}
	END_CATCH

	return TRUE;
}

void CGXScrollableCurEngine::OnAddedNewRecord()
{
	m_bEOF = FALSE;
	m_nCurrentCursorPos = -1;
	FetchRecords(LONG_MAX);
}

// Initiate the addNew mode
long CGXScrollableCurEngine::AddRow()
{
	if(!CanAppend())
		return -1;

	if(m_nEditMode != noMode)
	{
		TRACE0("Cannot start an addNew mode since already in edit or addNew mode\n");
		return -1;
	}

	// Refresh the edit buffer
	if (m_paDirtyFieldStruct)
	{
		delete[] m_paDirtyFieldStruct;
		m_paDirtyFieldStruct = NULL;
	}
	m_paDirtyFieldStruct = new CGXDBDirtyFieldStruct[GetFieldCount()+1];

	// Fetch all the records first.
	FetchRecords(ULONG_MAX);
	ASSERT(m_bEOF);

	// The append row id (0 based)
	m_nEditRecord = m_nLastRecordSeen + 1;
	m_nEditMode = CGXDBEngine::addNew;
	return m_nEditRecord;
}

// Cancel the current (edit or addNew) mode.
void CGXScrollableCurEngine::CancelRecord()
{
	if(m_nEditMode == noMode)
		return;
	if(m_nEditMode == addNew)
		m_nEditRecord = -1;

	// Clear the dirty-fields buffer
	if (m_paDirtyFieldStruct)
	{
		delete[] m_paDirtyFieldStruct;
		m_paDirtyFieldStruct = NULL;
	}

	m_nEditMode = noMode;
	m_bDirty = FALSE;
}

void CGXScrollableCurEngine::OnDeletedRecords()
{
	Requery();
}

#undef NOMINMAX
