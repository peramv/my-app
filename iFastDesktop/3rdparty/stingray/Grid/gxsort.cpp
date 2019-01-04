///////////////////////////////////////////////////////////////////////////////
// gxsort.cpp : implementation of sorting for the grid
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
// Author: Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXSORT_H_  
#include "grid\gxsort.h"
#endif

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSORT")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#if _MFC_VER >= 0x0400
#define OLEDATE_SUPPORT 1
#endif

#pragma warning (disable: 4245) // Signed/Unsigned Mismatch

const LPCTSTR szDigits = _T("0123456789.,- ");   
const LPCTSTR szDigitsNatural = _T("0123456789.,-");   // No white space so that number discontinuity will sort correctly.
const LPCTSTR szNumber = _T("0123456789,.-e "); // Ambiguous e? How is the 'e' handled?
const LPCTSTR szAlpha  = _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

// Internal helper functions
//
// Function: absolute
// Returns the absolute value for Rogue Wave's Objective Grid.
// Note: absolute( d ) is faster than sqrt(d*d) and faster than ::abs( d )
double absolute (double number)
{
    return( number >= 0 ? number : -number );
};

// Function: natural
// The natural sort algorithm is an improved sorting algorithm for strings containing numbers. 
// Instead of sorting numbers in ASCII order like a standard sort, this algorithm sorts strings 
// in character and numeric order substrings for human readability. 

int natural(CString String1, CString String2, BOOL bCaseSensitive) 
{ 
	int n = 0; 
	// If strings are equal, we'll just return 0.
	if ( String1 != String2 ) 
	{
		// Copy the strings to compare
		CString strFirst = String1; 
		CString strNext = String2; 
	
		// Only make them both lower case if bCaseSensitive == false
		if(!bCaseSensitive)
		{
			strFirst.MakeLower(); 
			strNext.MakeLower(); 
		}
	
		while ( n == 0 && !(strFirst.IsEmpty() && strNext.IsEmpty() ) ) 
		{
			// A substring is either a group of letters or a group of numbers 
			CString strFirstSubString; 
			CString strFirstChar( strFirst[0] ); 
			
			if ( strFirstChar.FindOneOf( szDigitsNatural ) != -1 ) 
			{ 
				strFirstSubString = strFirst.SpanIncluding( szDigitsNatural ); 
			} 
			else 
			{ 
				strFirstSubString = strFirst.SpanExcluding( szDigitsNatural ); 
			} 
			
			// Get next substring 
			CString strNextSubString; 
			strFirstChar = strNext[0]; 
			
			if ( strFirstChar.FindOneOf( szDigitsNatural ) != -1 ) 
			{ 
				strNextSubString = strNext.SpanIncluding( szDigitsNatural ); 
			} 
			else 
			{ 
				strNextSubString = strNext.SpanExcluding( szDigitsNatural ); 
			} 
			
			// Remove the extracted substrings from the strings 
			strFirst = strFirst.Mid(strFirstSubString.GetLength(), strFirst.GetLength() - strFirstSubString.GetLength() ); 
			strNext = strNext.Mid(strNextSubString.GetLength(), strNext.GetLength() - strNextSubString.GetLength() ); 
			
			// Compare the substrings 
			//
			// Case #1: They both contain letters. We're assuming from above that these strings are NOT equal. 
			if ( strFirstSubString.FindOneOf( szDigitsNatural ) == -1 && strNextSubString.FindOneOf( szDigitsNatural ) == -1 ) 
			{ 
				n = strFirstSubString.Compare( strNextSubString );  
			} 
			// Case #2 or Case #3: They both contain numbers or one has letters, one has numbers, or one is empty
			else 
			{
				// Case #2: They both contain numbers
				if ( strFirstSubString.FindOneOf( szDigitsNatural ) != -1 && strNextSubString.FindOneOf( szDigitsNatural ) != -1) 
				{ 
					// Convert the numeric strings to double values 
					// NOTE: atoi, _atoi64, atol, _wtoi, _wtoi64 and _wtol do not recognize decimal points or exponents
					double dFirst = _tstof( strFirstSubString ); 
					double dNext = _tstof( strNextSubString ); 

					// if the numbers are equal, use string length to determine order
					if ( dFirst == dNext && strFirstSubString.GetLength() != strNextSubString.GetLength() ) 
					{
						n = strFirstSubString.GetLength() > strNextSubString.GetLength() ? 1 : -1;
					}

					// If these strings are equal, make one come before the other, 
					// i.e. the choice is arbitrary, to prevent getting stuck in a 
					// "while n==0" loop.

					// Note: Same result is expected when the first number is greater than the second.
					if ( dFirst > dNext ) 
					{ 
						n = 1; 
					} 
					else if ( dFirst < dNext ) 
					{ 
						n = -1; 
					} 
				} 
				// Case #3: One has letters, one has numbers, or one is empty
				else 
				{ 
					n = strFirstSubString.Compare( strNextSubString ); 
				} // inner else

			} // outer else
			
		} // while 

	} // if strings are unequal
	
	return n; 
}

class CGXGridSortImp: public CGXAbstractGridSortImp   // instantiated by CGXGridCore::EnableSortRows
{
public:
	// General
	virtual void SortKeys(CGXGridCore* pGrid, const CGXSortInfoArray& sortInfo, CPtrArray& sortKeyArray);

	// Rows
	virtual void SortRows(CGXGridCore* pGrid, CGXRange& sortRange, CGXSortInfoArray& sortInfo, UINT flags);
	virtual BOOL MoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awRowIndex, UINT flags, GXCmdType ctCmd);
	virtual BOOL StoreMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awRowIndex);
	virtual void UpdateMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags, BOOL bCreateHint);
	virtual void OnGetSortRowsKey(CGXGridCore* pGrid, ROWCOL nRow, const CGXSortInfoArray& sortInfo, CStringArray& keys);

	// Columns
	virtual void SortCols(CGXGridCore* pGrid, CGXRange& sortRange, CGXSortInfoArray& sortInfo, UINT flags);
	virtual BOOL MoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awColIndex, UINT flags, GXCmdType ctCmd);
	virtual BOOL StoreMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awColIndex);
	virtual void UpdateMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags, BOOL bCreateHint);
	virtual void OnGetSortColsKey(CGXGridCore* pGrid, ROWCOL nCol, const CGXSortInfoArray& sortInfo, CStringArray& keys);

	// Dbl Click on header
	virtual BOOL OnLButtonDblClkRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
};

//////////////////////////////////////////////////////////////////////////
// Enable Sort Functionality

void CGXGridCore::ImplementGridSort()
{
	if (m_pSortImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pSortImp = new CGXGridSortImp);
		m_pSortImp = new CGXGridSortImp;
	}

	CGXData::ImplementSortMoveData();
}

//////////////////////////////////////////////////////////////////////////

CGXSortKey::CGXSortKey()
{
	darray = 0;
}

CGXSortKey::~CGXSortKey()
{
	delete darray;
}

//////////////////////////////////////////////////////////////////////////
// Generic compare method for qsort

#if defined(_UNIX_)
static int __cdecl __compare(const void* p1, const void* p2)
#else
extern "C" static int __cdecl __compare(const void* p1, const void* p2) 
#endif
{
	CGXSortKey* pKey1 = *((CGXSortKey**) p1);
	CGXSortKey* pKey2 = *((CGXSortKey**) p2);
	const CGXSortInfoArray* pSortInfo = pKey1->pSortInfo;

	for (int i = 0; i < pSortInfo->GetSize(); i++)
	{
		const CGXSortInfo& keyinfo = pSortInfo->GetAt(i);

		if (keyinfo.sortType == CGXSortInfo::date)
		{
			// date comparison

#ifdef OLEDATE_SUPPORT
			COleDateTime d1 = pKey1->darray[i];
			COleDateTime d2 = pKey2->darray[i];
#else
			ASSERT(0); // for 16-Bit this should be alphanumeric sort
			double d1 = 0, d2 = 0;
#endif

			if (d1 == d2)
				continue;

			if (d1 > d2)
				return keyinfo.sortOrder == CGXSortInfo::ascending ? 1 : -1;
			else
				return keyinfo.sortOrder == CGXSortInfo::ascending ? -1 : 1;
		}
		else if (keyinfo.sortType == CGXSortInfo::numeric)
		{
			// numeric comparison
			double d1 = pKey1->darray[i];
			double d2 = pKey2->darray[i];

			if (d1 == d2)
				continue;

			if (d1 > d2)
				return keyinfo.sortOrder == CGXSortInfo::ascending ? 1 : -1;
			else
				return keyinfo.sortOrder == CGXSortInfo::ascending ? -1 : 1;
		}
		else if (keyinfo.sortType == CGXSortInfo::absolute)
		{
			// absolute comparison
			double d1 = pKey1->darray[i];
			double d2 = pKey2->darray[i];
			d1 = absolute(d1);
			d2 = absolute(d2);

			if (d1 == d2)
				continue;

			if (d1 > d2)
				return keyinfo.sortOrder == CGXSortInfo::ascending ? 1 : -1;
			else
				return keyinfo.sortOrder == CGXSortInfo::ascending ? -1 : 1;
		}
		else if (keyinfo.sortType == CGXSortInfo::natural)
		{
			// alpha substring and numeric substring comparisons
			int n = 0;
			n = natural(pKey1->sKeys[i], pKey2->sKeys[i], keyinfo.bCase);
			
			if (n != 0)
				return keyinfo.sortOrder == CGXSortInfo::ascending ? n : -n;
		}
		else
		{
			// alphanumeric comparison
			int n = 0;

			// Flag for Natural Language Support ("NLS") sort, i.e. keyinfo.bCase
			if (keyinfo.bCase)
			{
				n = _tcscoll(pKey1->sKeys[i], pKey2->sKeys[i]);
			}
			else
			{
				n = _tcsicoll(pKey1->sKeys[i], pKey2->sKeys[i]);
			}

			if (n != 0)
				return keyinfo.sortOrder == CGXSortInfo::ascending ? n : -n;
		}
	}

	// values are equal - return ids

	return (int) (pKey1->nId - pKey2->nId);
}

// local define
#define GX_MAX_SORTNUM_SIZE 500

#ifndef _UNICODE
// not required for the UNICODE build
WCHAR* _gxConvertDef(const char* psz)
{
	static WCHAR pszW[GX_MAX_SORTNUM_SIZE];
	
	memset(pszW, 0, GX_MAX_SORTNUM_SIZE*2);

	if (psz == NULL)
		return NULL;
	
	UINT nCount = MultiByteToWideChar(CP_ACP, 0, psz, -1, NULL, NULL);
	ASSERT(nCount);
	
	if(nCount == 0)
		return NULL;
	
	
	if(pszW == NULL)
		return NULL;
		
	if(!::MultiByteToWideChar(CP_ACP, 0, psz, -1, pszW, nCount))
		return NULL;
	
	pszW[nCount] = 0;
	
	return pszW;
}
#endif

//////////////////////////////////////////////////////////////////////////
// CGXGridSortImp implementation of sort functionality
// see gxabstr.cpp for calling methods in CGXGridCore

void CGXGridSortImp::SortKeys(CGXGridCore* pGrid, const CGXSortInfoArray& sortInfo, CPtrArray& sortKeyArray)
{
	// Unused
	GX_UNUSED_ALWAYS(pGrid);
	sortInfo;

	// Ref: http://support.microsoft.com/kb/216858
	// The Visual C++ run-time library (MSVCRT) implements the quick-sort function, qsort, as follows:
	// void qsort( void *base, size_t num, size_t width, int (__cdecl *compare )(const void *elem1, const void *elem2 ) );

	qsort(sortKeyArray.GetData(), sortKeyArray.GetSize(), sizeof(void*), __compare);

}

void CGXGridSortImp::SortRows(CGXGridCore* pGrid, CGXRange& sortRange, CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	if (pGrid->GetRowCount() <= 1)
		return;

	// SRSTUDIO-1693 Keep track of the sort type.
	if(sortInfo[0].sortType != CGXSortInfo::autodetect)
	{
		pGrid->m_sortType = sortInfo[0].sortType;
	}

	// Sort the grid with the columns specified in awCols.
	CGXGridParam* pParam = pGrid->GetParam();

	if (sortRange.IsTable())
		sortRange.SetRows(pGrid->GetHeaderRows()+1, pGrid->GetRowCount());

	pGrid->MoveCurrentCell(GX_TOP);
	pGrid->TransferCurrentCell();

	// Step 1:
	// Generate an array with sort key for each record 

	CGXLongOperation theOp;
	theOp.SetStatusText(GX_IDM_SORTROWS);
	theOp.SetCanRollback(FALSE);
	theOp.SetCanAbort(TRUE);    // Give the user the possibility to abort
	BOOL bCancel = FALSE;

	// Array with CGXSortKeys
	CPtrArray sortKeyArray;
	ROWCOL nCount = sortRange.GetHeight();
	sortKeyArray.SetSize((int) nCount);

	int nIndex = 0;
	CRowColArray awRowIndex;

#ifdef OLEDATE_SUPPORT
	COleDateTime dt;
#else
	TIMESTAMP_STRUCT tm;
#endif

	// Key pointer
	CGXSortKey* pKey;
	int n;
	for (n = 0; n < sortInfo.GetSize(); n++)
	{
		sortInfo[n].bOnlyNum = sortInfo[n].bOnlyDate = TRUE;
		sortInfo[n].bNatural = FALSE;
	}

	TRY
	{
		if (nCount >= INT_MAX)
			AfxThrowMemoryException();

		// loop through the records and append each records key to the file
		for (ROWCOL nRow = sortRange.top; nRow <= sortRange.bottom; nRow++)
		{
			// Allocate new key and add it to SortKeys
			sortKeyArray.SetAt((int) (nRow-sortRange.top), pKey = new CGXSortKey);
				// will throw an exveption if out of memory

			// fill sort key
			pKey->sKeys.SetSize(sortInfo.GetSize());

			pGrid->OnGetSortRowsKey(nRow, sortInfo, pKey->sKeys);

			// row identifier 
			pKey->nId = nRow-sortRange.top;
			pKey->pSortInfo = &sortInfo;

			// check if column consists only of numeric values
			for (n = 0; n < sortInfo.GetSize(); n++)
			{
				if (pKey->sKeys[n].IsEmpty())
					continue;

				CGXSortInfo& keyinfo = sortInfo[n];

				//-------------------------------//
				// Determine the sort type.      //
				//-------------------------------//

				// Date Only?
				if (keyinfo.bOnlyDate && keyinfo.sortType == CGXSortInfo::autodetect)
				{
#ifdef OLEDATE_SUPPORT
					keyinfo.bOnlyDate = pKey->sKeys[n].IsEmpty() || dt.ParseDateTime(pKey->sKeys[n]);
#else
					keyinfo.bOnlyDate = pKey->sKeys[n].IsEmpty() || GXParseDateTime(&tm, pKey->sKeys[n]);
#endif
				}

				// Number Only? 
				if (keyinfo.bOnlyNum && keyinfo.sortType == CGXSortInfo::autodetect)
				{
					// szNumber without "-"
					keyinfo.bOnlyNum = _tcsspnp((LPCTSTR) pKey->sKeys[n], szNumber) == NULL;
					
					if (keyinfo.bOnlyNum)
					{
						CString& str = pKey->sKeys[n];
						//if (str[0] == _T('_') && str.ReverseFind(_T('-')) != 0)
						
                        str.TrimLeft(); 
						if (str.ReverseFind(_T('-')) > 0)
							// There is a "-" some where in the middle of the string......
							keyinfo.bOnlyNum = FALSE;
					}
				}
				
				// Natural/Alpha Numeric?
				if (/*keyinfo.bNatural &&*/ keyinfo.sortType == CGXSortInfo::autodetect)
				{
					// sKeys[n] contains both alpha and numeric characters 
					keyinfo.bNatural = ( (_tcsspnp((LPCTSTR) pKey->sKeys[n],  szAlpha) != NULL) || (_tcsspnp((LPCTSTR) pKey->sKeys[n], szDigits) != NULL) );
				}
			}

			// give user a chance to cancel the operation
			if (theOp.NeedMessages())
			{
				theOp.DoMessages(bCancel);

				if (bCancel)
					AfxThrowUserException();
			}
		}
	}
	CATCH(CMemoryException, e)
	{
		GX_THROW_LAST
		AfxMessageBox(GX_IDM_NOTENOUGHMEMORY);  
		goto cleanup;
	}
	AND_CATCH(CUserException, e)
	{
		// User canceled.
		GX_THROW_LAST
		theOp.SetStatusText(GX_IDM_CANCELED);
		goto cleanup;
	}
	AND_CATCH(CNotSupportedException, e)
	{
		// User canceled.
		GX_THROW_LAST
		goto cleanup;
	}
	END_CATCH

	// autodetect - interprete data
	for (n = 0; n < sortInfo.GetSize(); n++)
	{
		CGXSortInfo& keyinfo = sortInfo[n];
		if (keyinfo.sortType == CGXSortInfo::autodetect)
		{
			if (keyinfo.bOnlyDate)
				keyinfo.sortType = CGXSortInfo::date;
			else if (keyinfo.bOnlyNum)
				keyinfo.sortType = CGXSortInfo::numeric;
				// SRSTUDIO-1296
			// else if (keyinfo.bNatural)
			//	keyinfo.sortType = CGXSortInfo::natural;
			else
				keyinfo.sortType = CGXSortInfo::alphanumeric;
		}

		// Date
		if (keyinfo.sortType == CGXSortInfo::date)
		{
			// Generate datetime sortkeys
			for (int nIndex = 0; nIndex < (int) nCount; nIndex++)
			{
				CGXSortKey* pKey = (CGXSortKey*) sortKeyArray[nIndex];

				if (pKey && pKey->darray == 0)
				{
					pKey->darray = new double[sortInfo.GetSize()];
				}

#if OLEDATE_SUPPORT
				if(pKey->sKeys[n].IsEmpty())
					dt = 0.0;
				else
					dt.ParseDateTime(pKey->sKeys[n]);

				pKey->darray[n] = dt;
				pKey->sKeys[n].Empty();

#else
				if (!pKey->sKeys[n].IsEmpty() && GXParseDateTime(&tm, pKey->sKeys[n]))
				{
					wsprintf(pKey->sKeys[n].GetBuffer(20),
						_T("%04d%02d%02d%02d%02d%02d"),
						tm.year,
						tm.month,
						tm.day,
						tm.hour,
						tm.minute,
						tm.second);
					pKey->sKeys[n].ReleaseBuffer();
				}
				else
					pKey->sKeys[n].Empty();
#endif
			}

#ifndef OLEDATE_SUPPORT
			keyinfo.sortType = CGXSortInfo::alphanumeric;
#endif
		}

		// Numeric
		if ( (keyinfo.sortType == CGXSortInfo::numeric) || (keyinfo.sortType == CGXSortInfo::absolute) )
		{
			OLECHAR* opsz = NULL;
			double d(0.0);
			
			// Generate numeric sortkeys
			for (int nIndex = 0; nIndex < (int) nCount; nIndex++)
			{
				CGXSortKey* pKey = (CGXSortKey*) sortKeyArray[nIndex];

				if (pKey->darray == 0)
					pKey->darray = new double[sortInfo.GetSize()];

				CString sTempKey;
				if (pKey->sKeys[n] != _T(""))
					sTempKey = pKey->sKeys[n];
                else
                    sTempKey = _T("0");

#ifndef _UNICODE
				opsz = _gxConvertDef(sTempKey);
#else	
				opsz = _tcsdup((const WCHAR*)sTempKey);
#endif

				::VarR8FromStr(opsz, LOCALE_USER_DEFAULT, NULL, &d);
				pKey->darray[n] = d;
				pKey->sKeys[n].Empty();
#ifdef _UNICODE
				if(opsz)
					delete[] opsz;
#endif
			}
		}
	}

    // Step 2:
	// Sort the key file
	pGrid->SortKeys(sortInfo, sortKeyArray);

	// Step 3:
	// Read in new row order from sorted memory file
	awRowIndex.RemoveAll();
	awRowIndex.SetSize((int) nCount);

	// loop through the sorted keys, fill up awRowIndex and
	// clean up sortKeyArray
	for (nIndex = 0; nIndex < (int) nCount; nIndex++)
	{
		CGXSortKey* pKey = (CGXSortKey*) sortKeyArray[nIndex];
		awRowIndex[nIndex] = pKey->nId;
	}

	// remember last sorted row
	pParam->m_nLastSortedRow = GX_INVALID;
	pParam->m_nLastSortedCol = sortInfo[0].nRC;

	pParam->m_bSortAscending = sortInfo[0].sortOrder == CGXSortInfo::ascending;

	pGrid->MoveDataRows(sortRange, awRowIndex, flags);

cleanup:
	for (nIndex = 0; nIndex < (int) nCount; nIndex++)
	{
		CGXSortKey* pKey = (CGXSortKey*) sortKeyArray[nIndex];
		delete pKey;
	}

	// Flush unused memory substrings after sorting
	HANDLE h = GetCurrentProcess();
	SetProcessWorkingSetSize( h, -1, -1 );
}

BOOL CGXGridSortImp::MoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, 
	                              const CRowColArray& awRowIndex, 
	                              UINT flags /*= GX_UPDATENOW*/,
	                              GXCmdType ctCmd /*= gxDo*/)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pGrid->StoreMoveDataRows(sortRange, awRowIndex))
	{
		pGrid->SetSelection(0);

		pGrid->DelayFloatCells(CGXRange().SetTable());
		pGrid->DelayMergeCells(CGXRange().SetTable());

		pGrid->Recalc(TRUE);

		pGrid->UpdateMoveDataRows(sortRange, flags);

		if (pGrid->m_pUndoImp && ctCmd != gxRollback && pParam->m_bUndoEnabled)
		{
			// Create undo information
			CRowColArray* pUndoArray = new CRowColArray;
			pUndoArray->SetSize(awRowIndex.GetSize());
			for (int n = 0; n < awRowIndex.GetSize(); n++)
			{
				int nSrc = (int) awRowIndex[n];
				pUndoArray->SetAt(nSrc, n);
			}

			pGrid->AddCommand(pGrid->m_pUndoImp->CreateMoveDataRowsCmd(sortRange, pUndoArray), ctCmd);
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CGXGridSortImp::StoreMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awRowIndex)
{
	ASSERT(sortRange.IsRows());
	// ASSERTION-> Only full rows supported. Override this
	// method if you want to support sorting only a limited
	// range of cells ->END

	return pGrid->GetParam()->GetData()->StoreMoveDataRows(sortRange, awRowIndex);
}

void CGXGridSortImp::UpdateMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags /*= GX_UPDATENOW*/, BOOL bCreateHint /*=TRUE*/)
{
	pGrid->TransferCurrentCell(FALSE, FALSE);

	if (!pGrid->IsLockUpdate())
		pGrid->Redraw(flags, FALSE);

	// Generate Hint
	if (pGrid->m_pUpdateHintImp && bCreateHint && pGrid->m_bHintsEnabled)
		pGrid->m_pUpdateHintImp->HintUpdateMoveDataRows(pGrid, sortRange, flags);
}

void CGXGridSortImp::OnGetSortRowsKey(CGXGridCore* pGrid, ROWCOL nRow, const CGXSortInfoArray& sortInfo, CStringArray& keys)
{
	CGXStyle* pStyle = pGrid->CreateStyle();

	// append each columns value to the sort key
	for (int n = 0; n < sortInfo.GetSize(); n++)
	{
		pGrid->ComposeStyleRowCol(nRow, sortInfo[n].nRC, pStyle);

		CGXControl* pControl = pGrid->GetRegisteredControl(pStyle->GetControl());
		CString sKey;

		pGrid->GetSortKey(pControl, nRow, sortInfo[n].nRC, sortInfo[n], *pStyle, sKey);

		keys.SetAtGrow(n, sKey);
		pStyle->Free();
	}

	pGrid->RecycleStyle(pStyle);
}


// This is the main routine for sorting. You should
// change OnGetSortKey to return a proper sort key.
// Make sure that the sort key always has the same length!

void CGXGridSortImp::SortCols(CGXGridCore* pGrid, CGXRange& sortRange, CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	if (pGrid->GetColCount() <= 1)
		return;

	// SRSTUDIO-1693 Keep track of the sort type.
	if(sortInfo[0].sortType != CGXSortInfo::autodetect)
	{
		pGrid->m_sortType = sortInfo[0].sortType;
	}

	CGXGridParam* pParam = pGrid->GetParam();

	// Sort the grid with the columns specified in awCols.

	if (sortRange.IsTable())
		sortRange.SetCols(pGrid->GetHeaderCols()+1, pGrid->GetColCount());

	pGrid->MoveCurrentCell(GX_LEFT);
	pGrid->TransferCurrentCell();

	// Step 1:
	// Generate an array with sort key for each record 

	CGXLongOperation theOp;
	theOp.SetStatusText(GX_IDM_SORTCOLS);
	theOp.SetCanRollback(FALSE);
	theOp.SetCanAbort(TRUE);    // Give the user the possibility to abort
	BOOL bCancel = FALSE;

	// Array with CGXSortKeys
	CPtrArray sortKeyArray;
	ROWCOL nCount = sortRange.GetWidth();
	sortKeyArray.SetSize((int) nCount);

	CRowColArray awColIndex;
	int nIndex = 0;

#ifdef OLEDATE_SUPPORT
	COleDateTime dt;
#else
	TIMESTAMP_STRUCT tm;
#endif

	// Key pointer
	CGXSortKey* pKey;
	int n;
	for (n = 0; n < sortInfo.GetSize(); n++)
	{
		sortInfo[n].bOnlyNum = sortInfo[n].bOnlyDate = TRUE;
		sortInfo[n].bNatural = FALSE;
	}

	TRY
	{
		if (nCount >= INT_MAX)
			AfxThrowMemoryException();

		// loop through the records and append each records key to the file
		for (ROWCOL nCol = sortRange.left; nCol <= sortRange.right; nCol++)
		{
			// Allocate new key and add it to SortKeys
			sortKeyArray.SetAt((int) (nCol-sortRange.left), pKey = new CGXSortKey);
				// will Throw an exveption if out of memory

			// fill sort key
			pKey->sKeys.SetSize(sortInfo.GetSize());

			pGrid->OnGetSortColsKey(nCol, sortInfo, pKey->sKeys);

			// Col identifier 
			pKey->nId = nCol-sortRange.left;
			pKey->pSortInfo = &sortInfo;

			// check if column consists only of numeric values
			for (int n = 0; n < sortInfo.GetSize(); n++)
			{
				if (pKey->sKeys[n].IsEmpty())
					continue;

				CGXSortInfo& keyinfo = sortInfo[n];

				if (keyinfo.bOnlyDate && keyinfo.sortType == CGXSortInfo::autodetect)
				{
#ifdef OLEDATE_SUPPORT
					keyinfo.bOnlyDate = pKey->sKeys[n].IsEmpty() || dt.ParseDateTime(pKey->sKeys[n]);
#else
					keyinfo.bOnlyDate = pKey->sKeys[n].IsEmpty() || GXParseDateTime(&tm, pKey->sKeys[n]);
#endif
				}

				if (keyinfo.bOnlyNum && keyinfo.sortType == CGXSortInfo::autodetect)
				{
					// szNumber without "-"
					keyinfo.bOnlyNum = _tcsspnp((LPCTSTR) pKey->sKeys[n], szNumber) == NULL;
					
					if (keyinfo.bOnlyNum)
					{
						CString& str = pKey->sKeys[n];
						//if (str[0] == _T('_') && str.ReverseFind(_T('-')) != 0)
						
                        str.TrimLeft();
						if (str.ReverseFind(_T('-')) > 0)
							// There is a "-" some where in the middle of the string......
							keyinfo.bOnlyNum = FALSE;
					}
				}
				
				if (/*keyinfo.bNatural &&*/ keyinfo.sortType == CGXSortInfo::autodetect)
				{
					// sKeys[n] contains both alpha and number characters
					keyinfo.bNatural = ((_tcsspnp((LPCTSTR) pKey->sKeys[n],  szAlpha) != NULL) && 
					                    (_tcsspnp((LPCTSTR) pKey->sKeys[n], szNumber) != NULL));
				}
				
			}

			// give user a chance to cancel the operation
			if (theOp.NeedMessages())
			{
				theOp.DoMessages(bCancel);

				if (bCancel)
					AfxThrowUserException();
			}
		}
	}
	CATCH(CMemoryException, e)
	{
		GX_THROW_LAST
		AfxMessageBox(GX_IDM_NOTENOUGHMEMORY);  
		goto cleanup;
	}
	AND_CATCH(CUserException, e)
	{
		// User canceled.
		GX_THROW_LAST
		theOp.SetStatusText(GX_IDM_CANCELED);
		goto cleanup;
	}
	AND_CATCH(CNotSupportedException, e)
	{
		// User canceled.
		GX_THROW_LAST
		goto cleanup;
	}
	END_CATCH

	// autodetect - interprete data
	for (n = 0; n < sortInfo.GetSize(); n++)
	{
		CGXSortInfo& keyinfo = sortInfo[n];
		if (keyinfo.sortType == CGXSortInfo::autodetect)
		{
			if (keyinfo.bOnlyDate)
				keyinfo.sortType = CGXSortInfo::date;
			else if (keyinfo.bOnlyNum)
				keyinfo.sortType = CGXSortInfo::numeric;
			// SRSTUDIO-1296
			// else if (keyinfo.bNatural)
			//	keyinfo.sortType = CGXSortInfo::natural;
			else
				keyinfo.sortType = CGXSortInfo::alphanumeric;
		}

		if (keyinfo.sortType == CGXSortInfo::date)
		{
			// Generate datetime sortkeys
			for (int nIndex = 0; nIndex < (int) nCount; nIndex++)
			{
				CGXSortKey* pKey = (CGXSortKey*) sortKeyArray[nIndex];

				if (pKey->darray == 0)
					pKey->darray = new double[sortInfo.GetSize()];

#if OLEDATE_SUPPORT
				if(pKey->sKeys[n].IsEmpty())
					dt = 0.0;
				else
				dt.ParseDateTime(pKey->sKeys[n]);
				pKey->darray[n] = dt;
				pKey->sKeys[n].Empty();
#else
				if (!pKey->sKeys[n].IsEmpty() && GXParseDateTime(&tm, pKey->sKeys[n]))
				{
					wsprintf(pKey->sKeys[n].GetBuffer(20),
						_T("%04d%02d%02d%02d%02d%02d"),
						tm.year,
						tm.month,
						tm.day,
						tm.hour,
						tm.minute,
						tm.second);
					pKey->sKeys[n].ReleaseBuffer();
				}
				else
					pKey->sKeys[n].Empty();
#endif
			}

#ifndef OLEDATE_SUPPORT
			keyinfo.sortType = CGXSortInfo::alphanumeric;
#endif
		}

		if ( (keyinfo.sortType == CGXSortInfo::numeric) || (keyinfo.sortType == CGXSortInfo::absolute) )
		{
			OLECHAR* opsz = NULL;
			double d(0.0);
			
			// Generate numeric sortkeys
			for (int nIndex = 0; nIndex < (int) nCount; nIndex++)
			{
				CGXSortKey* pKey = (CGXSortKey*) sortKeyArray[nIndex];

				if (pKey->darray == 0)
					pKey->darray = new double[sortInfo.GetSize()];

				CString sTempKey;
				if (pKey->sKeys[n] != _T(""))
					sTempKey = pKey->sKeys[n];
                else
                    sTempKey = _T("0");

#ifndef _UNICODE
				opsz = _gxConvertDef(sTempKey);
#else
				opsz = _tcsdup((const WCHAR*)sTempKey);
#endif
				// Convert an OLEChar string to a double
				::VarR8FromStr(opsz, LOCALE_USER_DEFAULT, NULL, &d);
				pKey->darray[n] = d;
				pKey->sKeys[n].Empty();
#ifdef _UNICODE
				if(opsz)
					delete[] opsz;
#endif
			}
		}
		
		if ( keyinfo.sortType == CGXSortInfo::natural )
		{
			// Generate natural sortkeys
		}
	}

	// Step 2:
	// Sort the key file
	pGrid->SortKeys(sortInfo, sortKeyArray);

	// Step 3:
	// Read in new Col order from sorted memory file
	awColIndex.RemoveAll();
	awColIndex.SetSize((int) nCount);

	// loop through the sorted keys, fill up awColIndex and
	// clean up sortKeyArray
	for (nIndex = 0; nIndex < (int) nCount; nIndex++)
	{
		CGXSortKey* pKey = (CGXSortKey*) sortKeyArray[nIndex];
		awColIndex[nIndex] = pKey->nId;
	}

	// remember last sorted row
	pParam->m_nLastSortedCol = GX_INVALID;
	pParam->m_nLastSortedRow = sortInfo[0].nRC;

	pParam->m_bSortAscending = sortInfo[0].sortOrder == CGXSortInfo::ascending;

	pGrid->MoveDataCols(sortRange, awColIndex, flags);

cleanup:
	for (nIndex = 0; nIndex < (int) nCount; nIndex++)
	{
		CGXSortKey* pKey = (CGXSortKey*) sortKeyArray[nIndex];
		delete pKey;
	}

	// Flush unused memory substrings after sorting
	HANDLE h = GetCurrentProcess();
	SetProcessWorkingSetSize( h, -1, -1 );
}

BOOL CGXGridSortImp::MoveDataCols(CGXGridCore* pGrid, 
								  const CGXRange& sortRange, 
								  const CRowColArray& awColIndex, 
								  UINT flags /*= GX_UPDATENOW*/,
								  GXCmdType ctCmd /*= gxDo*/)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pGrid->StoreMoveDataCols(sortRange, awColIndex))
	{
		pGrid->SetSelection(0);

		pGrid->DelayFloatCells(CGXRange().SetTable());
		pGrid->DelayMergeCells(CGXRange().SetTable());

		pGrid->Recalc(TRUE);

		pGrid->UpdateMoveDataCols(sortRange, flags);

		if (pGrid->m_pUndoImp && ctCmd != gxRollback && pParam->m_bUndoEnabled)
		{
			// Create undo information
			CRowColArray* pUndoArray = new CRowColArray;
			pUndoArray->SetSize(awColIndex.GetSize());
			for (int n = 0; n < awColIndex.GetSize(); n++)
			{
				int nSrc = (int) awColIndex[n];
				pUndoArray->SetAt(nSrc, n);
			}

			pGrid->AddCommand(pGrid->m_pUndoImp->CreateMoveDataColsCmd(sortRange, pUndoArray), ctCmd);
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CGXGridSortImp::StoreMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awColIndex)
{
	ASSERT(sortRange.IsCols());
	// ASSERTION-> Only full Cols supported. Override this
	// method if you want to support sorting only a limited
	// range of cells ->END

	return pGrid->GetParam()->GetData()->StoreMoveDataCols(sortRange, awColIndex);
}

void CGXGridSortImp::UpdateMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags /*= GX_UPDATENOW*/, BOOL bCreateHint /*=TRUE*/)
{
	pGrid->TransferCurrentCell(FALSE, FALSE);

	if (!pGrid->IsLockUpdate())
		pGrid->Redraw(flags, FALSE);

	// Generate Hint
	if (pGrid->m_pUpdateHintImp && bCreateHint && pGrid->m_bHintsEnabled)
		pGrid->m_pUpdateHintImp->HintUpdateMoveDataCols(pGrid, sortRange, flags);
}

void CGXGridSortImp::OnGetSortColsKey(CGXGridCore* pGrid, ROWCOL nCol, const CGXSortInfoArray& sortInfo, CStringArray& keys)
{
	CGXStyle* pStyle = pGrid->CreateStyle();

	// append each columns value to the sort key
	for (int n = 0; n < sortInfo.GetSize(); n++)
	{
		pGrid->ComposeStyleRowCol(sortInfo[n].nRC, nCol, pStyle);

		CGXControl* pControl = pGrid->GetRegisteredControl(pStyle->GetControl());

		CString sKey;

		pGrid->GetSortKey(pControl, sortInfo[n].nRC, nCol, sortInfo[n], *pStyle, sKey);

		keys.SetAtGrow(n, sKey);
	}

	pGrid->RecycleStyle(pStyle);
}


BOOL CGXGridSortImp::OnLButtonDblClkRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
	nRow, nCol, nFlags, pt;

	CGXGridParam* pParam = pGrid->GetParam();

	if (nRow == 0 && nCol > 0 && pParam->GetSortRowsOnDblClk())
	{
		// user double-clicked on a column header

		// fill up array with sort order
		CGXSortInfoArray sortInfo;
		sortInfo.SetSize(1); // only 1 column (you can also sort by several columns)
		sortInfo[0].nRC = nCol;
		if(pGrid->m_sortType == CGXSortInfo::natural)
		{
			sortInfo[0].sortType = CGXSortInfo::natural;
		}else
		{
			sortInfo[0].sortType = CGXSortInfo::autodetect;
		}

		if (pParam->m_nLastSortedCol != nCol || !pParam->m_bSortAscending)
		{
			sortInfo[0].sortOrder = CGXSortInfo::ascending;
		}else
		{
			sortInfo[0].sortOrder = CGXSortInfo::descending;
		}

		pGrid->SortRows(CGXRange().SetTable(), sortInfo);
		pGrid->MoveCurrentCell(GX_TOP);

		return TRUE;
	}
	else if (nRow > 0 && nCol == 0 && pParam->GetSortColsOnDblClk())
	{
		// user double-clicked on a column header

		// fill up array with sort order
		CGXSortInfoArray sortInfo;
		sortInfo.SetSize(1); // only 1 row (you can also sort by several row)
		sortInfo[0].nRC = nRow;
		if(pGrid->m_sortType == CGXSortInfo::natural)
		{
			sortInfo[0].sortType = CGXSortInfo::natural;
		}else
		{
			sortInfo[0].sortType = CGXSortInfo::autodetect;
		}

		if (pParam->m_nLastSortedRow != nRow || !pParam->m_bSortAscending)
		{
			sortInfo[0].sortOrder = CGXSortInfo::ascending;
		}else
		{
			sortInfo[0].sortOrder = CGXSortInfo::descending;
		}

		pGrid->SortCols(CGXRange().SetTable(), sortInfo);
		pGrid->MoveCurrentCell(GX_LEFT);

		return TRUE;
	}

	return FALSE;
}
