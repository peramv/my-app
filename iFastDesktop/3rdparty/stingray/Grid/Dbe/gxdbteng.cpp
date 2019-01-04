///////////////////////////////////////////////////////////////////////////////
// gxdbteng.cpp : implementation of CGXDBToolsEngine
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
#define AFXAPI_DATA __based(__segname("_DBTENGINE"))
#endif

// Header for dbtools libraries.

#ifndef _GXDBTLINKLIB
#include "grid\dbe\gxdbtlinklib.h"
#endif

// Headers for imported classes
#ifndef _GXDBEGRID
#include "grid\dbe\gxdbegrid.h"
#endif

// min/max is defined both in MFC and Tools.h,
// here we undefine the MFC defenition and use the Tools.h++ one.
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifndef __RWDB_DB_H__
#include <rw/db/db.h>
#endif

#ifndef __RWCSTRING_H__
#include <rw/cstring.h>
#endif

#ifndef _GXDBTENG
#include "grid\dbe\gxdbteng.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDBTOOLS")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Private constructor.
void CGXDBToolsEngine::InitMembers()
{
	m_nResultType = noType;
	m_nCols = -1;
	m_bDirty = FALSE;
	m_bEOF = FALSE;
}

// Use this to bind the engine to a table (with no selection criteria)
CGXDBToolsEngine::CGXDBToolsEngine(RWDBTable table, RWDBSchema updateCols, RWDBConnection conn)
{
	InitMembers();
	Init(table, updateCols, conn);
}

// Cleanup in the destructor
CGXDBToolsEngine::~CGXDBToolsEngine()
{
	CleanUp();
}

// Initialize with a table (without selection crietria)
void CGXDBToolsEngine::Init(RWDBTable table, RWDBSchema updateCols, RWDBConnection conn)
{
	CleanUp();
	m_conn = conn;
	m_nResultType = CGXDBToolsEngine::table;
	m_table = table;
	// Populate with m_nIncrement increments at a time.
	m_memTable.populate(table.reader(m_conn), m_nIncrement, m_bEOF);
	m_nCols = m_memTable.numberOfColumns();
	// Compose m_updateCols
	if(updateCols.entries())
		m_updateCols = updateCols;
	else	// Use the primary key or all the fields in the table...
	{
		m_updateCols = table.schema().primaryKey();
		if(m_updateCols.entries() == 0)
		{
			TRACE0("\nThere are no primary keys in the table. \nAll the fields in the table will be used in the criterion of the updater.\nThis might be inefficient and we suggest you identify the columns \nthat should be used in the where clause of the update statement \nto make the currently being updated record unique and specify \n those columns as the updateCols in the engine's constructor.");
			InitUpdateCols(table.schema());
		}
	}
	if(m_updateCols.entries() == 0)
		TRACE0("\n\nThere are no entries in the updateCols, the engine will be set to be readonly");
}

// Use this to bind the engine to the result of a join...
CGXDBToolsEngine::CGXDBToolsEngine(RWDBSelector selector, RWDBConnection conn)
{
	InitMembers();
	Init(selector, conn);
}

// Initialize with a table with selection cretria
void CGXDBToolsEngine::Init(RWDBSelector selector, RWDBConnection conn)
{
	m_nResultType = join;
	m_selector = selector;
	m_conn = conn;
	RWDBReader reader = selector.reader();
	m_memTable.populate(reader, m_nIncrement, m_bEOF);
	m_nCols = m_memTable.numberOfColumns();
}

// Use this to bind the engine to a table with some selection criteria...
CGXDBToolsEngine::CGXDBToolsEngine(RWDBTable table, RWDBSelector selector, RWDBSchema visibleCols, RWDBSchema updateCols,  RWDBConnection conn)
{
	InitMembers();
	Init(table, selector, visibleCols, updateCols, conn);
}

// Initialize the grid with a join.
void CGXDBToolsEngine::Init(RWDBTable table, RWDBSelector selector, RWDBSchema visibleCols, RWDBSchema updateCols,  RWDBConnection conn)
{
	CleanUp();
	m_nResultType = tableSubset;
	m_table = table;
	m_selector = selector;
	m_visibleCols = visibleCols;
	InitUpdateCols(updateCols);
	if(m_updateCols.entries() == 0)
		InitUpdateCols(table.schema());
	for(unsigned int i=0; i<updateCols.entries(); i++)
	{
		if(ColumnInSchema(updateCols[i], m_visibleCols) == -1 && updateCols[i].type() != RWDBValue::Blob)
			selector << table[updateCols[i].name()];
	}
	m_conn = conn;
	m_selector.execute(m_conn);
	m_memTable.populate(m_selector.reader(), m_nIncrement, m_bEOF);
	m_nCols = m_visibleCols.entries();
}

// Helper for requery.
// Schema remains same, but the data is refetched from the source.
// Filter and sort criteria could have changed.
void CGXDBToolsEngine::ReInit()
{
	CleanUp();
	if(m_nResultType == CGXDBToolsEngine::table)
	{
		// Assuming schema remains same only refetch the data...
		m_memTable.populate(m_table.reader(m_conn), m_nIncrement, m_bEOF);
	}
	else if(m_nResultType == join)
	{
		// Assuming schema remains same, only reexecute the query...
		m_selector.execute(m_conn);
		m_memTable.populate(m_selector.reader(), m_nIncrement, m_bEOF);
	}
	else if(m_nResultType == tableSubset)
	{
		m_selector.execute(m_conn);
		m_memTable.populate(m_selector.reader(), m_nIncrement, m_bEOF);
	}
}

// Append updatecols with the schema except a Blob type column.
void CGXDBToolsEngine::InitUpdateCols(RWDBSchema schema)
{
	for(int i=0; i<schema.entries(); i++)
	{
		if(schema[i].type() != RWDBValue::Blob)
			m_updateCols.appendColumn(schema[i]);
	}
}

// Fetch records in increments... as needed.
void CGXDBToolsEngine::FetchRecords(long nRecords)
{
	if(IsEOFSeen())
		return;
	// Fetch in increments of m_nIncrement...
	if(nRecords > m_memTable.entries())
		if((nRecords - m_memTable.entries()) < m_nIncrement)
			nRecords = m_memTable.entries() + m_nIncrement;

	m_memTable.fillUpto(nRecords, m_bEOF/*o/p*/);
}

// Utility function
// Returns the index of the col in schema, if not present retuns -1
int CGXDBToolsEngine::ColumnInSchema(RWDBColumn col, RWDBSchema schema)
{
	for(unsigned int i=0; i<schema.entries(); i++)
	{
		if(schema[i].name() == col.name())
			return i;
	}
	return -1;
}

// This will be called from the destructor and from Init while reinitializing.
void CGXDBToolsEngine::CleanUp()
{
	m_memTable.clearAndDestroy();
}

// Is the engine initialized?
BOOL CGXDBToolsEngine::IsInit()
{
	return m_nResultType != noType;
}

// Get the value in row nRecord and nField as a CString
BOOL CGXDBToolsEngine::GetValue(long nRecord, long nField, CString& strValue)
{
	ASSERT(IsInit());
	if(m_nEditMode != addNew && nRecord >= GetRecordCount() || m_nEditMode == addNew && nRecord >= GetRecordCount()+1 || nField >= GetFieldCount())
		return FALSE;
	if(nRecord == m_nEditRecord && m_nEditMode != noMode)
	{
		// In edit or addnew mode, get the value from the edit buffer, if present
		RWDBValue value;
		if(m_editRow[nField].isNull() && m_nEditMode == edit)	// Current row but field not edited...
			value = (*m_memTable[nRecord])[nField];
		else value = m_editRow[nField];	// Present in the edit buffer
		GetDBTValueAsString(strValue, value, m_memTable.schema().column(nField).type());
	}
	else
	{
		GetDBTValueAsString(strValue, (*m_memTable[nRecord])[nField], m_memTable.schema().column(nField).type());
	}
	return TRUE;
}

BOOL CGXDBToolsEngine::GetOrigFieldValue(long nRecord, long nField, CString& strValue)
{
	ASSERT(IsInit());
	if(m_nEditMode != addNew && nRecord >= GetRecordCount() || m_nEditMode == addNew || nField >= GetFieldCount())
		return FALSE;

	GetDBTValueAsString(strValue, (*m_memTable[nRecord])[nField], m_memTable.schema().column(nField).type());
	return TRUE;
}

/*
BOOL CGXDBToolsEngine::DeleteRow(long nRow)
{
	if(m_nEditMode != noMode || nRow >= GetRecordCount())
		return FALSE;
	RWDBDeleter deleter;
	deleter = m_table.deleter();
	RWDBCriterion crit;
	for(i=0; i<m_updateCols.entries(); i++)
	{
		int n;
		if((n = ColumnInSchema(m_updateCols[i], m_memTable.schema())) != -1)
		{
			crit = crit && (m_updateCols[i] == m_memTable[nRow][n]);
		}
	}
	deleter.where(crit);
	if(deleter.execute().status().errorCode() == RWDBStatus::ok)
	{
	}
}
*/

BOOL CGXDBToolsEngine::Update(CString* strError)
{
	if(m_nEditMode == noMode)
	{
		TRACE(_T("Update called without Edit or AddRow"));
		return FALSE;
	}
	// Update an exisiting record
	if(m_nEditMode == edit && m_bDirty)
	{
		RWDBUpdater updater;
		updater = m_table.updater();
		// Prepare the updater.
		// With the update data and
		for(unsigned int i=0; i<m_editRow.entries(); i++)
		{
			// If Value in editRow and memTable are different then include it in the udpate statement...
			// if(m_editRow[i].compareTo(& m_memTable[m_nEditRecord][i]) != 0)
			// if(m_editRow[i].compareTo(rwdbNull) != 0)
			if(!m_editRow[i].isNull())
			{
				updater << m_memTable.schema().column(i).assign(m_editRow[i]);
			}
		}
		// the key columns criteria
		RWDBCriterion crit;
		for(i=0; i<m_updateCols.entries(); i++)
		{
			int n;
			if((n = ColumnInSchema(m_updateCols[i], m_memTable.schema())) != -1)
			{
				crit = crit && (m_updateCols[i] == (*m_memTable[m_nEditRecord])[n]);
			}
		}
		updater.where(crit);
//		TRACE0(updater.asString());
		if(updater.execute(m_conn).status().errorCode() == RWDBStatus::ok)
		{
			// Successfully updated...
			for(int i=0; i<m_nCols; i++)
			{
				if(!m_editRow[i].isNull())
					(*m_memTable[m_nEditRecord])[i] = m_editRow[i];
			}
		}
		else
		{
			return FALSE;
		}
	}
	// Insert a new record
	else if(m_nEditMode == CGXDBEngine::addNew && m_bDirty)
	{
		RWDBSchema inserterSchema;
		for(int i=0; i<m_nCols; i++)
		{
			inserterSchema.appendColumn(m_memTable.schema().column(i));
		}
		RWDBInserter inserter = m_table.inserter(inserterSchema);
		// Prepare the inserter
		// Fill with data
		for(i=0; i<m_nCols; i++)
		{
			inserter << m_editRow[i];
		}
		// Execute.
		if(inserter.execute(m_conn).status().errorCode() == RWDBStatus::ok)
		{
			// If stored successfully then append to the self's data structure
			RWDBRow* pRow = new RWDBRow();
			for(unsigned int i=0; i<m_editRow.entries(); i++)
			{
				pRow->append(RWDBValue(m_editRow[i]));
			}
			m_memTable.append(pRow);
		}
		else
			return FALSE;
	}
	m_nEditMode = noMode;
	m_bDirty = FALSE;
	return TRUE;
}

// Initate edit mode.
BOOL CGXDBToolsEngine::Edit(long nRecord)
{
	if(CanUpdate() && nRecord >= GetRecordCount())
		return FALSE;
	// Refresh the edit buffer
	m_editRow.clearAndDestroy();
	//m_editRow = m_memTable[nRecord];
	for(int i=0; i<m_nCols; i++)
//		m_editRow.append((RWCollectable*)new RWDBValue(m_memTable[nRecord][i]));
		m_editRow.append(RWDBValue(rwdbNull));
	m_nEditRecord = nRecord;
	m_nEditMode = edit;
	return TRUE;
}

// Initiate the addnew mode
long CGXDBToolsEngine::AddRow()
{
	if(!CanAppend())
		return -1;
	// Refresh the edit buffer
	m_editRow.clearAndDestroy();
	// Fetch all the records first.
	FetchRecords(ULONG_MAX);
	for(int i=0; i<m_nCols; i++)
		m_editRow.append(RWDBValue(rwdbNull));
	// The append row id (0 based)
	m_nEditRecord = m_memTable.entries();
	m_nEditMode = CGXDBEngine::addNew;
	return m_nEditRecord;
}

BOOL CGXDBToolsEngine::DeleteRows(long nFrom, long nTo)
{
	if(nTo < nFrom)
		return FALSE;
	BOOL bSuccess = FALSE;
	long nRecord;
	for(nRecord=nFrom; nRecord<=nTo; nRecord++)
	{
		if(nRecord >= GetRecordCount() || !CanUpdate())
			break;
		m_nEditRecord = nRecord;
		RWDBDeleter deleter = m_table.deleter();
		// Prepare deleter
		// set criteria based on key columns
		RWDBCriterion crit;
		for(unsigned int i=0; i<m_updateCols.entries(); i++)
		{
			int n;
			if((n = ColumnInSchema(m_updateCols[i], m_memTable.schema())) != -1)
			{
				crit = crit && (m_updateCols[i] == (*m_memTable[m_nEditRecord])[n]);
			}
		}
		deleter.where(crit);
		if(deleter.execute(m_conn).status().errorCode() == RWDBStatus::ok)
			bSuccess = TRUE;
	}
	if(bSuccess)
	{
		// If successful then remove from the self's data structure
		for(int i=nFrom; i<=nRecord && i<=nTo; i++)
			m_memTable.removeAt(nFrom);	//P
	}
	return TRUE;
}

// 1 based
long CGXDBToolsEngine::GetRecordCount()
{
	ASSERT(IsInit());
	return m_memTable.entries();
}
// 1 based
long CGXDBToolsEngine::GetFieldCount()
{
	ASSERT(IsInit());
	return m_nCols;
}
// nRecord and nField are 1 based
// Will not cache a new value if it is same as the original value.
BOOL CGXDBToolsEngine::SetValue(long nRecord, long nField, CString* strValue)
{
	if(nRecord != m_nEditRecord || nField >= GetFieldCount() || m_nEditMode == noMode)
		return FALSE;
	// Update the cache...
	m_editRow[nField] = ComposeValue(m_memTable.schema().column(nField).type(), strValue);
	// If same as original value then mark it not-dirty
	if((m_nEditMode == edit && m_editRow[nField].isEqual(&(*m_memTable[nRecord])[nField]))
		|| (m_nEditMode == addNew && m_editRow[nField].isNull()))
	{
		m_editRow[nField] = rwdbNull;
		// Reset the dirty flag if there is no dirty entry...
		BOOL bDirty = FALSE;
		for(unsigned int i=0; i<m_editRow.entries(); i++)
		{
			if(!m_editRow[i].isNull())
			{
				bDirty = TRUE;
				break;
			}
		}
		m_bDirty = bDirty;
		return TRUE;
	}
	// Turn on the dirty flag.
	if(!m_editRow[nField].isNull())
		m_bDirty = TRUE;
	return TRUE;
}

// Compose a RWDBValue from CString based on the col type.
RWDBValue CGXDBToolsEngine::ComposeValue(RWDBValue::ValueType type, CString* strValue)
{
	RWDBValue valueResult = rwdbNull;
	BOOL bDateTime = FALSE;
	// If null value then return rwdbNull for all types...
	if(strValue == NULL)
			valueResult = rwdbNull;
	switch(type)
	{
	case RWDBValue::Char:
		valueResult = RWDBValue(strValue->GetAt(0));
		break;
	case RWDBValue::UnsignedChar:
		valueResult = RWDBValue((BYTE) _ttoi((LPCTSTR)*strValue));
		break;
	case RWDBValue::Short:
		valueResult = RWDBValue((short)_ttoi((LPCTSTR)*strValue));
		break;
	case RWDBValue::UnsignedShort:
		valueResult = RWDBValue((short)_ttoi((LPCTSTR)*strValue)).asUnsignedShort();
		break;
	case RWDBValue::Int:
		valueResult = RWDBValue((int)_ttoi((LPCTSTR)*strValue));
		break;
	case RWDBValue::UnsignedInt:
		valueResult = RWDBValue((unsigned int)_ttoi((LPCTSTR)*strValue));
		break;
	case RWDBValue::Long:
		valueResult = RWDBValue((long)_ttol((LPCTSTR)*strValue));
		break;
	case RWDBValue::UnsignedLong:
		valueResult = RWDBValue((unsigned long)_ttol((LPCTSTR)*strValue));
		break;
	case RWDBValue::Float:
		valueResult = RWDBValue((float)_gxttof((LPCTSTR)*strValue));
		break;
	case RWDBValue::Double:
		valueResult = RWDBValue((double)_gxttof((LPCTSTR)*strValue));
		break;
	case RWDBValue::Decimal:
		valueResult = RWDBValue((float)_gxttof((LPCTSTR)*strValue)).asDecimal();
		break;
	case RWDBValue::DateTime:
		bDateTime = TRUE;
	case RWDBValue::Date:
		{
			struct tm tm;
			COleDateTime date;

			if (date.ParseDateTime((LPCTSTR)*strValue))
			{
				tm.tm_year = date.GetYear()-1900; // tm_year is 1900 based
				tm.tm_mon = date.GetMonth()-1;    // month is zero-based
				tm.tm_mday = date.GetDay();
				tm.tm_hour = date.GetHour();
				tm.tm_min = date.GetMinute();
				tm.tm_sec = date.GetSecond();
			}

			if(!bDateTime)
			{
				RWDate date(&tm);
				if(date.isValid())
					valueResult = RWDBValue(date);
				else
					TRACE0("Tried to set invalid date value...\nChanges will not take effect.");
			}
			else
			{
				RWDBDateTime dateTime(&tm);
				if(dateTime.isValid())
					valueResult = RWDBValue(dateTime);
				else
					TRACE0("Tried to set invalid date value...\nChanges will not take effect.");
			}
		}
		break;
	case RWDBValue::String:
	case RWDBValue::WString:
	case RWDBValue::MBString:
		if(strValue->IsEmpty())
			valueResult = RWDBValue(" ").asString();
		else
			valueResult = RWDBValue((LPCTSTR)*strValue).asString();
		break;
	case RWDBValue::NoType:
	default:
		valueResult = rwdbNull;
	}
	return valueResult;
}

BOOL CGXDBToolsEngine::CanUpdate()
{
	return !((m_updateCols.entries() == 0) || (m_nResultType == noType) || (m_nResultType == join));
}

BOOL CGXDBToolsEngine::CanAppend()
{
	return CanUpdate();
}

// Cancel the current (edit or addnew) mode.
void CGXDBToolsEngine::CancelRecord()
{
	if(m_nEditMode == noMode)
		return;
	if(m_nEditMode == addNew)
		m_nEditRecord = -1;
	m_editRow.clearAndDestroy();
	m_nEditMode = noMode;
	m_bDirty = FALSE;
}

void CGXDBToolsEngine::Requery()
{
	ReInit();
}

// CGXMemTable is the data structure in which the result set is held

CGXDBToolsEngine::CGXMemTable::~CGXMemTable()
{
	clearAndDestroy();	// Clear and destroy the Singly linked list...
}

void CGXDBToolsEngine::CGXMemTable::populate(RWDBReader reader, int nUpto, BOOL& bEOF)
{
	rd = reader;
	sch = rd.table().schema();
	fillUpto(nUpto, bEOF);
}

// Fill the list with RWDBRows.
void CGXDBToolsEngine::CGXMemTable::fillUpto(unsigned int nCount, BOOL& bEOF)
{
	BOOL eof = FALSE;
	while(nCount > entries() && !(eof = !rd()))
	{
		RWDBRow* pRow = new RWDBRow();
		rd >> *pRow;
		insert(pRow);
	}
	bEOF = eof;
}

size_t CGXDBToolsEngine::CGXMemTable::numberOfColumns()
{
	return sch.entries();
}

const RWDBSchema& CGXDBToolsEngine::CGXMemTable::schema()
{
	return sch;
}

RWDBSelector& CGXDBToolsEngine::GetSelector()
{
	ASSERT(m_nResultType == join || m_nResultType == tableSubset);
	// If you are using the default CGXDBToolsEngine Call this
	// function only if you had initialized the engine with a selector.
	// If you had subclassed CGXDBToolsEngine then override this function
	// and remove the ASSERT.
	return m_selector;
}

// Convert the RWDBValue into a CString
BOOL CGXDBToolsEngine::GetDBTValueAsString(CString& strValue, RWDBValue value, RWDBValue::ValueType type)
{
	if(value.isNull())
	{
		strValue = _T("");
		return TRUE;
	}
	switch(type)
	{
	case RWDBValue::Date:
		{
		RWDate date = value.asDate();
		if(!date.isValid())
		{
			strValue = _T("");
			break;
		}
		COleDateTime oleDate(date.year(), date.month(), date.day(), 0 , 0 , 0);
		strValue = oleDate.Format(_T("%x"));
		}
		break;
	case RWDBValue::DateTime:
		{
		RWDBDateTime dateTime = value.asDateTime();
		if(!dateTime.isValid())
		{
			strValue = _T("");
			break;
		}
		TIMESTAMP_STRUCT time;
		time.year = dateTime.year();
		time.month = dateTime.month();
		time.day = dateTime.dayOfMonth();
		time.hour = dateTime.hour();
		time.minute = dateTime.minute();
		time.second = dateTime.second();
		time.fraction = dateTime.millisecond();
/*		if (!(time.year    == AFX_RFX_TIMESTAMP_PSEUDO_NULL
				&& time.month   == AFX_RFX_TIMESTAMP_PSEUDO_NULL
				&& time.day     == AFX_RFX_TIMESTAMP_PSEUDO_NULL
				&& time.hour    == AFX_RFX_TIMESTAMP_PSEUDO_NULL
				&& time.minute  == AFX_RFX_TIMESTAMP_PSEUDO_NULL
				&& time.second  == AFX_RFX_TIMESTAMP_PSEUDO_NULL
				&& time.fraction== AFX_RFX_TIMESTAMP_PSEUDO_NULL)
			)*/
		GXFormatTimeStamp(strValue, &time);
		}
		break;
	case RWDBValue::Blob:
		strValue = _T("");
		break;
	default:
		strValue = value.asString();
	}
	return TRUE;
}

const MAX_NUM_STRING_SIZE = 29;

// Get the display size based on the column type
long GXGetDisplaySize(RWDBColumn column)
{
	switch(column.type())
	{
		case RWDBValue::Short:
		case RWDBValue::UnsignedShort:
			return 3;

		case RWDBValue::Int:
		case RWDBValue::UnsignedInt:
			return 6;

		case RWDBValue::Long:
		case RWDBValue::UnsignedLong:
			return 11;

		case RWDBValue::Float:
		case RWDBValue::Decimal:
		case RWDBValue::Double:
			return MAX_NUM_STRING_SIZE;

		case RWDBValue::Date:
		case RWDBValue::DateTime:
		case RWDBValue::Duration:

			// NOTE: This is the maximum supported size of a timestamp, not the average size.
			// This size accounts for intervals (the :FFF) which is not supported by many databases.
			return 24;  // DTB: 'YYYY-MM-DD HH:MM:SS:FFF'

		case RWDBValue::String:
		case RWDBValue::WString:
		case RWDBValue::MBString:
			return column.storageLength();

		case RWDBValue::Blob:
			return 0;
	}
	return 0;
}

#undef NOMINMAX
