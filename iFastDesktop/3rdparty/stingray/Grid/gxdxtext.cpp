///////////////////////////////////////////////////////////////////////////////
// gxdxtext.cpp : Read/write text format (files, clipboard)
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

#pragma warning (disable: 4390)

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORCLP")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

class CGXGridTextDataExchangeImp: public CGXAbstractGridTextDataExchangeImp
{
public:
	virtual BOOL CopyTextToFile(CGXGridCore* pGrid, CFile& destFile, const CGXRangeList& selList);
	virtual CString GetCopyTextRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol);
	virtual BOOL PasteTextFromBuffer(CGXGridCore* pGrid, LPCTSTR psz, DWORD size, const CGXRange& range);
	virtual BOOL PasteTextRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle);
	virtual BOOL CalcBufferDimension(CGXGridCore* pGrid, LPCTSTR psz, DWORD size, ROWCOL& nRows, ROWCOL& nCols);
};

void CGXGridCore::ImplementTextDataExchange()
{
	if (m_pTextDataExchangeImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pTextDataExchangeImp = new CGXGridTextDataExchangeImp);
		m_pTextDataExchangeImp = new CGXGridTextDataExchangeImp;
	}
}

BOOL CGXGridTextDataExchangeImp::CopyTextToFile(CGXGridCore* pGrid, CFile& destFile, const CGXRangeList& selList)
{
	// process selected cells

	// store rows/columns indizes to process in an array
	CRowColArray    awLeftCol, awRightCol,
					awTopRow, awBottomRow;

	selList.GetRowArray(pGrid->GetRowCount(), awTopRow, awBottomRow, FALSE);
	selList.GetColArray(pGrid->GetColCount(), awLeftCol, awRightCol, FALSE);

	// determine no of rows/cols to process
	ROWCOL nRows = 0;
	int rowindex;
	for (rowindex = 0; rowindex < awTopRow.GetSize(); rowindex++)
		nRows += awBottomRow[rowindex]-awTopRow[rowindex]+1;

	ROWCOL nCols = 0;
	int colindex;
	for (colindex = 0; colindex < awLeftCol.GetSize(); colindex++)
		nCols += awRightCol[colindex]-awLeftCol[colindex]+1;

	DWORD dwSize = nRows*nCols;

	ROWCOL nRowsDone = 0, nColsDone = 0;

	// status message, let the user abort the operation
	CGXLongOperation theOp;
	theOp.SetStatusText(pGrid->m_pAppData->strmCopyText, FALSE);

	BOOL bCanceled = FALSE;
	BOOL bAnyChar = FALSE;

	CString sTabDelim = _T('\t');
	if (!pGrid->m_sExportTabDelim.IsEmpty())
		sTabDelim = pGrid->m_sExportTabDelim;

#ifdef _DEBUG
	if (_tcslen(sTabDelim) > 1)
	{
		TRACE(_T("Warning: the length of m_sExportTabDelim in CopyTextToFile is more than one character!\n"));
		TRACE(_T("Columns will be separated with the following string: %1\n"), pGrid->m_sExportTabDelim);
	}
#endif

	// fill memory file row by row
	// lines are separated with \r\n, columns with \t
	for (rowindex = 0; !bCanceled && rowindex < awTopRow.GetSize(); rowindex++)
	{
		for (ROWCOL nRow = awTopRow[rowindex]; !bCanceled && nRow <= awBottomRow[rowindex]; nRow++)
		{
			if (nRowsDone > 0)
				destFile.Write(_T("\r\n"), sizeof(TCHAR)*2);

			BOOL firstCol;
			firstCol = TRUE;
			nColsDone = 0;
			for (colindex = 0; !bCanceled && colindex < awLeftCol.GetSize(); colindex++)
			{
				for (ROWCOL nCol = awLeftCol[colindex]; !bCanceled && nCol <= awRightCol[colindex]; nCol++)
				{
					DWORD dwIndex;

					dwIndex = nRowsDone*nCols+nColsDone;

					if (!firstCol)
						destFile.Write((LPCTSTR) sTabDelim, sTabDelim.GetLength()*sizeof(TCHAR));

					// Get text from control (and give control the chance
					// to convert value into unformatted text or vice versa).
					CString sText = pGrid->GetCopyTextRowCol(nRow, nCol);

					// filter newline characters (DBCS aware)
					LPCTSTR pszSrc = sText;

					while (*pszSrc)
					{
						// replace crlf, cr and lf with a space
						if (*pszSrc != _T('\n') && *pszSrc != _T('\r') && *pszSrc != _T('\t'))
						{
							destFile.Write(pszSrc, (int)_tclen(pszSrc)*sizeof(TCHAR));
						}
						else
						{
							if (pGrid->m_nClipboardFlags & GX_DNDMULTILINETEXT)
							{
								if (*pszSrc == _T('\r'))
									destFile.Write(_T("\\r"),2*sizeof(TCHAR));
								else if (*pszSrc == _T('\n'))
									destFile.Write(_T("\\n"),2*sizeof(TCHAR));
								else if (*pszSrc == _T('\t'))
									destFile.Write(_T("\\t"),2*sizeof(TCHAR));
							}
							else
							{
								if (*pszSrc == _T('\r') && *(pszSrc+1) == _T('\n'))
									pszSrc++;

								if(*pszSrc != _T('\t'))
									destFile.Write(_T(" "), 1*sizeof(TCHAR));
								else
									destFile.Write(_T("\\t"),2*sizeof(TCHAR));

							}
						}

						bAnyChar = TRUE;
						pszSrc += _tclen(pszSrc);
					}

					firstCol = FALSE;

					// check, if user pressed ESC to cancel
					if (theOp.NeedMessages())
					{
						theOp.SetPercentDone((int) (dwIndex * 100 / dwSize));
						theOp.DoMessages(bCanceled);
					}

					nColsDone++;
				}
			}
			nRowsDone++;
		}
	}

	if (nRowsDone > 1 || nColsDone > 1)
		destFile.Write(_T("\r\n"), sizeof(TCHAR)*2);

	// you may use these internal attributes to determine
	// the number of written rows and cols after this function
	// returns

	pGrid->m_nRowsCopied = nRowsDone;
	pGrid->m_nColsCopied = nColsDone;

	return !bCanceled && bAnyChar;
}

CString CGXGridTextDataExchangeImp::GetCopyTextRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol)
{
	// Override this method if you want to copy formula
	// expressions instead of text

	// Get text from control (and give control the chance
	// to convert value into unformatted text or vice versa).
	CString sText;
	CGXStyle* pStyle = pGrid->CreateStyle();

	pGrid->ComposeStyleRowCol(nRow, nCol, pStyle);

	CGXControl* pControl = pGrid->GetRegisteredControl(pStyle->GetControl());
	if (pControl)
		pControl->GetControlText(sText, nRow, nCol, NULL, *pStyle);
	else
		sText = pStyle->GetValueRef();

	pGrid->RecycleStyle(pStyle);

	return sText;
}

#pragma warning (push)
#pragma warning (disable: 4706)

// paste unformatted text
BOOL CGXGridTextDataExchangeImp::PasteTextFromBuffer(CGXGridCore* pGrid, LPCTSTR psz, DWORD size, const CGXRange& range)
{
	BOOL bCanceled = FALSE;

	CGXLongOperation theOp;
	theOp.SetCanRollback(TRUE);
	theOp.SetStatusText(pGrid->m_pAppData->strmPastingData, FALSE);
	theOp.SetLockedState(TRUE);

	CString s;
	ROWCOL nRow, nCol;

	// paste text into cells
	// (newline will start a new row, tab delimiter will
	// move to the next column).

	CString sTabDelim = _T('\t');
	if (!pGrid->m_sImportTabDelim.IsEmpty())
		sTabDelim = pGrid->m_sImportTabDelim;

	// Store and decativate current cell
	pGrid->TransferCurrentCell();

	pGrid->BeginTrans(pGrid->m_pAppData->strmPasteData);

	nRow = range.top;
	nCol = range.left;

	ROWCOL nRows = pGrid->GetRowCount();
    ROWCOL nCols = pGrid->GetColCount();

	BOOL bLock = pGrid->LockUpdate(TRUE);
	ROWCOL nLastCol = nCol;
    size /= sizeof(psz[0]);  
	TRY
	{
		// parse buffer (DBCS aware)
		for (DWORD nIndex = 0, nLast = 0; !bCanceled && nIndex < size; nIndex += (int)_tclen(psz+nIndex))
		{
			// check for a delimiter
			// Intentinal Assignment???
			BOOL bUseLastChar = FALSE;
			if (psz[nIndex] == _T('\0') || _tcschr(_T("\r\n"), psz[nIndex]) || _tcschr(sTabDelim, psz[nIndex])
				|| (bUseLastChar = (nIndex == size - 1)) )
			{
				//handle last char not being a delimiter
				//only use last char if it is not \0, \r\n or delimiter.
				if(bUseLastChar)
					nIndex++;

				// end of a string found, copy value to cell
				if (nRow > pGrid->GetRowCount())
				{
					if ((pGrid->m_nClipboardFlags & GX_DNDNOAPPENDROWS) == 0
						&& pGrid->SetRowCount(nRow))
						; // ok - successfully append rows
					else
						break;
				}

				if (nCol > pGrid->GetColCount())
				{
					// C4390: empty controlled statement found; is this the intent?
					if ((pGrid->m_nClipboardFlags & GX_DNDNOAPPENDCOLS) == 0 && pGrid->SetColCount(nCol))
						; // ok - successfully appended columns
				}

				if (nRow <= pGrid->GetRowCount() && nCol <= pGrid->GetColCount())
				{
					s.Empty();
					if (nIndex != nLast)
					{
												if (pGrid->m_nClipboardFlags & GX_DNDMULTILINETEXT)
						{
							// _tcsncpy copies exactly cnt bytes from src to dst
							TCHAR*	pszBuf;
							int	iInd, iLen = nIndex-nLast;
							pszBuf = s.GetBuffer(iLen);
							for (iInd=0; iInd<iLen; iInd++, nLast++)
							{
								if (psz[nLast]=='\\')
								{
									if (psz[nLast+1]=='r')
										pszBuf[iInd]='\r', nLast++, iLen--;
									else if(psz[nLast+1]=='n')
										pszBuf[iInd]='\n', nLast++, iLen--;
									else if(psz[nLast+1]=='t')
										pszBuf[iInd]='\t', nLast++, iLen--;
									else
										pszBuf[iInd]=psz[nLast];
								}else
									pszBuf[iInd]=psz[nLast];
							}
							s.ReleaseBuffer(iInd);
						}
						else
						{
							// _tcsncpy copies exactly cnt bytes from src to dst
							// QA: 31989 - #if Secure Code Cleanup.
							_tcsncpy(s.GetBuffer((int) (nIndex-nLast)),
								psz+nLast,
								(size_t) (nIndex-nLast));
								

							// [VC7] Don't rely on GetBuffer to Null terminate the buffer.
							s.ReleaseBuffer(nIndex - nLast);
						}
					}

					CGXStyle* pStyle = pGrid->CreateStyle();
					pGrid->ComposeStyleRowCol(nRow, nCol, pStyle);

					// Give the control the chance to validate
					// and change the pasted text
					bCanceled = !pGrid->PasteTextRowCol(nRow, nCol, s, GX_INVALIDATE, pStyle);

					pGrid->RecycleStyle(pStyle);
				}

				// abort parsing the string if next char
				// is an end-of-string or if canceled
				if (bCanceled || psz[nIndex] == _T('\0'))
					break;

				// Now, that the value has been copied to the cell,
				// let's check if we should jump to a new row.
				else if (_tcschr(_T("\r\n"), psz[nIndex]))
				{
					// Yes, I found an end of line
					// Let's increase nRow and reset nCol to first column
					nRow++;
					nCol = range.left;
					if (psz[nIndex] == _T('\r') && psz[nIndex+1] == _T('\n'))
						nIndex++;

					// abort parsing the string if next char
					// is an end-of-string
					if (psz[nIndex+1] == _T('\0'))
						break;
				}
				// move to next column
				else
					nCol++;

				// save index where the next cells value starts
				nLast = nIndex + (int)_tclen(psz+nIndex);

				nLastCol = max(nCol, nLastCol);

				// check, if user pressed ESC to cancel
				if (theOp.NeedMessages())
				{
					theOp.SetPercentDone((int) (nIndex * 100 / size));

					theOp.DoMessages(bCanceled);

					if (bCanceled)
						AfxThrowUserException();
				}
			}
		}
	}
	CATCH(CUserException, e);
	{
		bCanceled = TRUE;
		GX_THROW_LAST
	}
	END_CATCH

	if (bCanceled && theOp.GetRollbackConfirmedState())
		pGrid->Rollback();
	else
		pGrid->CommitTrans();

	pGrid->LockUpdate(bLock);
	pGrid->RedrawRowCol(range.top, range.left, nRow, nLastCol);
    if(nRows < pGrid->GetRowCount())
       pGrid->RedrawRowCol(nRows+1,0,nRow, range.left-1);
    if(nCols < pGrid->GetColCount())
		pGrid->RedrawRowCol(0,nCols+1,range.top-1, nLastCol);
	pGrid->UpdateScrollbars();
	// Also formula refresh cells that have references to the pasted cells
	pGrid->RefreshViews();

	return !bCanceled;
}

#pragma warning (pop) //4706

// The following method provides a hook for pasting text
// into the grid and lets you validate its contents.
//
// PasteTextRowCol is called from within PasteTextFromBuffer
// and lets you validate the text as it is pasted from the
// buffer. Also the controls themselves will call SetControlTextRowCol
// when the cell text (not the value) should be changed
//
// ------------------------------------------------------------------
// NOTE: value and cell text can be different. An example is
// tabbed comboboxes where an entry from a choice list is displayed
// in the cell and key for that string is stored in the cell.
//
// Another example is masked edit. The text displayed in the cell
// contains literals (e.g. "(001)-999"). The value does not
// contain literals  (e.g. "001999")
// ------------------------------------------------------------------
//
// SetControlTextRowCol calls pControl->SetControlText (unless
// you change its default behavior).
//
// pControl->SetControlText will convert the text into the raw
// value which should be stored in the cell and will then
// call SetValueRange to store that value in the grid
//
// The actual conversion from display text to value is done
// in the cell type's ConvertValueToString method. SetControlText
// is calling ConvertValueToString .


BOOL CGXGridTextDataExchangeImp::PasteTextRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle)
{
	return pGrid->SetControlTextRowCol(nRow, nCol, str, nFlags, pOldStyle);
}

BOOL CGXGridTextDataExchangeImp::CalcBufferDimension(CGXGridCore* pGrid, LPCTSTR psz, DWORD size, ROWCOL& nRows, ROWCOL& nCols)
{
	CString s;

	ROWCOL  nRowsDone = 0,
			nColsDone = 0;

	ROWCOL  nCol = 0;

	// (newline will start a new row, tab delimiter will
	// move to the next column).

	CString sTabDelim = _T('\t');
	if (!pGrid->m_sImportTabDelim.IsEmpty())
		sTabDelim = pGrid->m_sImportTabDelim;

	// parse buffer (DBCS aware)
	for (DWORD nIndex = 0, nLast = 0; nIndex < size; nIndex += (int)_tclen(psz+nIndex))
	{
		// check for a delimiter
		if (psz[nIndex] == _T('\0') || _tcschr(_T("\r\n"), psz[nIndex]) || _tcschr(sTabDelim, psz[nIndex]))
		{
			// end of a string found

			// abort parsing the string if next char
			// is an end-of-string
			if (psz[nIndex] == _T('\0'))
			{
				if (nIndex > nLast)
					nCol++;
				break;
			}

			// Now, that the value has been copied to the cell,
			// let's check if we should jump to a new row.
			else if (_tcschr(_T("\r\n"), psz[nIndex]))
			{
				// Yes, I found an end of line
				// Let's increase nRow and reset nCol to first column
				nRowsDone++;
				nCol = 0;

				if (psz[nIndex] == _T('\r') && psz[nIndex+1] == _T('\n'))
					nIndex++;

				// abort parsing the string if next char
				// is an end-of-string
				if (psz[nIndex+1] == _T('\0'))
					break;
			}
			// move to next column
			else
				nCol++;

			// save index where the next cells value starts
			nLast = nIndex + (int)_tclen(psz+nIndex);

			nColsDone = max(nColsDone, nCol+1);
		}
	}

	if (nCol > 0)
		nRowsDone++;

	nRows = nRowsDone;
	nCols = max(nColsDone, 1);

	return TRUE;
}

