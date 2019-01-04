///////////////////////////////////////////////////////////////////////////////
// GXHtmlW.cpp: implementation of the CGXHtmlW class.
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

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_GX_TAG_MAP(CGXHtmlW)
	GX_TAG_MAP_ENTRY(gxTD)
	GX_TAG_MAP_ENTRY(gxTR)
	GX_TAG_MAP_ENTRY(gxTH)
	GX_TAG_MAP_ENTRY(gxFONT)
	GX_TAG_MAP_ENTRY(gxFBOLD)
	GX_TAG_MAP_ENTRY(gxFSTRIKE)
	GX_TAG_MAP_ENTRY(gxFITALIC)
	GX_TAG_MAP_ENTRY(gxFUNDERLINE)
	GX_TAG_MAP_ENTRY(gxA)
	GX_TAG_MAP_ENTRY(gxHTML)
	GX_TAG_MAP_ENTRY(gxHEAD)
	GX_TAG_MAP_ENTRY(gxBODY)
	GX_TAG_MAP_ENTRY(gxTITLE)
	GX_TAG_MAP_ENTRY(gxTABLE)
	GX_TAG_MAP_ENTRY(gxMETA)
END_GX_TAG_MAP()

//@doc CGXTagDefaultHandler
//@mfunc Default handler for HTML table related tags. 
//It just compose the string according to HTML specification.
//@rdesc CString The string wrapped with the given tag
//@parm const CGXTagInfo& tagInfo The tag content used by this handler
CString CGXTagDefaultHandler::ComposeOutput(const CGXTagInfo& tagInfo)
{
	if( strTag.IsEmpty() )
		return tagInfo.strContent;

	CString ret;
	if( tagInfo.bWrapByNewline && tagInfo.bEndingNewline)
		ret.Format(_T("<%s%s>\n%s\n</%s>\n"), strTag, tagInfo.strAttrib, tagInfo.strContent, strTag);
	else if( tagInfo.bWrapByNewline )
		ret.Format(_T("<%s%s>\n%s\n</%s>"), strTag, tagInfo.strAttrib, tagInfo.strContent, strTag);
	else if( tagInfo.bEndingNewline )
		ret.Format(_T("<%s%s>%s</%s>\n"), strTag, tagInfo.strAttrib, tagInfo.strContent, strTag);
	else
		ret.Format(_T("<%s%s>%s</%s>"), strTag, tagInfo.strAttrib, tagInfo.strContent, strTag);
	return ret;
}


//@doc CGXHtmlW
//@mfunc Contruct CGXHtmlW object with the given grid view class instance.
//@parm CGXGridCore* pGrid The grid view class instance this object will work with
//@parm  CGXRange* pSelectRange An optional selection range to tell this instance
//only to write this range into the HTML table
CGXHtmlW::CGXHtmlW(CGXGridCore* pGrid, CGXRange* pSelectRange)
{
	ASSERT(pGrid != NULL);
	m_pGrid = pGrid;
	m_pSelectRange = pSelectRange;
}

CGXHtmlW::~CGXHtmlW()
{

}

//@doc CGXHtmlW
//@mfunc Get the size of the tag handler map
//@rdesc int 
inline
int CGXHtmlW::GetMapSize()
{
	return sizeof(_gxTagHandlerEntries)/sizeof(CGXTagHandlerEntry);
}

//@doc CGXHtmlW
//@mfunc This function search the given tag from the tag map table. If one exists, it
//will return the corresponding tag handler. otherwise return NULL.
//@rdesc CGXTagHandler* The corresponding tag handler of the given tag or NULL if no one exists
//@parm LPCTSTR lpszTag A pointer to tag string to search for tag handler.
CGXTagHandler* CGXHtmlW::LookupTag(LPCTSTR lpszTag)
{
	CString tag = lpszTag;
	tag.TrimLeft();
	tag.TrimRight();
	CGXTagHandlerEntry* pMap = _gxTagHandlerEntries;
	for(int i = 0; i < GetMapSize(); i++)
	{
		if( pMap[i].strTag == tag )
			return pMap[i].pHandler;
	}
	return NULL;
}

//@doc CGXHtmlW
//@mfunc This function write the portion of the grid as HTML table into an
//HTML file.
//@rdesc void 
//@parm LPCTSTR lpszFileName The output file name
void CGXHtmlW::WriteToFile(LPCTSTR lpszFileName)
{
	m_strFileName = lpszFileName;
	
	CString s;	
	try
	{
		WriteToString(s);
		CStdioFile file(lpszFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
		file.WriteString(s);
	}
	catch(CFileException * e)
	{
		s.Format(_T("Can't open file: %s"), lpszFileName);
		AfxMessageBox(s);
		e->Delete();
	}
}

//@doc CGXHtmlW
//@mfunc This function write the portion of the grid as in HTML format into the given string.
//@rdesc void 
//@parm CString& s The string to output to.
void CGXHtmlW::WriteToString(CString& s)
{
	s = _T("");
	CGXTagHandler* pHandler = NULL;
	if( (pHandler = LookupTag(gxTITLE)) != NULL )
		s = pHandler->ComposeOutput(CGXTagInfo(_T(""), m_strFileName, FALSE, TRUE));
	if( (pHandler = LookupTag(gxMETA)) != NULL  )
		s += pHandler->ComposeOutput(CGXTagInfo(_T("Name=\"Objective Grid Doc\" Content=\"7.0\""), _T(""), FALSE, TRUE));
	if( (pHandler = LookupTag(gxHEAD))!= NULL)
		s = pHandler->ComposeOutput(CGXTagInfo(_T(""), s));
	if( (pHandler = LookupTag(gxBODY) ) != NULL )
		s = pHandler->ComposeOutput(CGXTagInfo(_T(""), s + GetTableString()));
	if( (pHandler = LookupTag(gxHTML)) != NULL )
		s = pHandler->ComposeOutput(CGXTagInfo(_T(""), s));
}


//@doc CGXHtmlW
//@mfunc This function compose the whole table contents as a long string in HTML format.
//The returned string can be use to insert the grid into a existing HTML document.
//@rdesc CString returnt the whole table contents in HTML format as a long string
CString CGXHtmlW::GetTableString()
{
	CString s;

	int i, j;
	int nLeft, nRight, nTop, nBottom;
	if( m_pSelectRange != 0 )
	{
		nLeft = m_pSelectRange->left;
		nRight = m_pSelectRange->right;
		nTop = m_pSelectRange->top;
		nBottom = m_pSelectRange->bottom;
	}
	else
	{
		nLeft = 1;
		nRight = m_pGrid->GetColCount();
		nTop = 1;
		nBottom = m_pGrid->GetRowCount();
	}

	CellSpan *pCellSpan = NULL;

	if( nRight >= nLeft && nBottom >= nTop)
		pCellSpan = new CellSpan[nRight - nLeft + 2];  // We need consider row header

	j = 0;
	// Write column header
	s = GetTableCellString(nRight, nBottom, 0, j,
							pCellSpan[0], TRUE);
	while(j <= nRight )
		s += GetTableCellString(nRight, nBottom, 0, j, pCellSpan[j - nLeft + 1], TRUE);

	CGXTagHandler* pHandlerTR = LookupTag(gxTR);
	if( pHandlerTR != NULL)
		s = pHandlerTR->ComposeOutput(CGXTagInfo(_T(""), s));

	for(i = nTop; i <= nBottom; i++)
	{
		j = 0;
		CString str = GetTableCellString(nRight, nBottom,
								i, j, pCellSpan[0], TRUE);
		while( j <= nRight )
			str += GetTableCellString(nRight, nBottom,
									i, j, pCellSpan[j - nLeft + 1]);
		if( pHandlerTR != NULL )
			str = pHandlerTR->ComposeOutput(CGXTagInfo(_T(""), str));
		s += str;
	}

	if( pCellSpan != NULL )
		delete [] pCellSpan;

	// Reuse the pointer here
	if( (pHandlerTR = LookupTag(gxTABLE))  != NULL )
		s = pHandlerTR->ComposeOutput(CGXTagInfo(GetTableAttrib(), s));

	return s;
}

//@doc CGXHtmlW
//@mfunc This function composes the table attributes as a string.
//@rdesc CString Return the composed string
CString CGXHtmlW::GetTableAttrib()
{
	CString s;
	s.Format(_T(" width=\"%d\"") 
		     _T(" height=\"%d\"")
			 _T(" cols=\"%d\"")
			 _T(" align=\"left\"")
			 _T(" valign=\"middle\"")
			 _T(" bgcolor=\"#ffffff\"")
			 _T(" border=\"1\""),
			 
			 m_pGrid->GetColCount() * m_pGrid->GetColWidth(0), 
			 m_pGrid->GetRowCount(), // * m_pGrid->GetRowHeight(0),
			 m_pGrid->GetColCount() );
	return s;
}

//@doc CGXHtmlW
//@mfunc This function composes the contents of the given cell in the grid as a string.
//This string will contains the font attributes for the cell contents in the HTML table 
//cell.
//@rdesc CString Return the composed string
//@parm int nRow Row index of the cell in the grid
//@parm  int nCol Column index of the cell in the grid
//@parm  const CGXStyle &style Style of the given cell in the grid
CString CGXHtmlW::GetCellContentString(int nRow, int nCol, const CGXStyle &style)
{
	CString s;
	CGXControl* pControl = m_pGrid->GetRegisteredControl(style.GetControl());
	if (pControl == NULL || !pControl->GetControlText(s, nRow, nCol, NULL, style))
		s = style.GetValue();

	// Adding Unicode symbols support for HTML generation
	#ifdef _UNICODE
	CString resultString;
	const wchar_t *pBuffer = s.GetBuffer(s.GetLength());
	for (unsigned int uChar = *pBuffer; uChar != 0x0000; uChar = *(++pBuffer)) 
	{
		switch (uChar) 
		{
			case '<':
				resultString += _T("&lt;");
				continue;
			case '>':
				resultString += _T("&gt;");
				continue;
			case '&':
				resultString += _T("&amp;");
				continue;
			case '"': 
				resultString += _T("&quot;");
				continue;
			/*case '\'': 
				resultString += _T("&apos;");
				continue;*/
		}

		if (uChar < (1 << 7))
		{
			resultString += (wchar_t)uChar;
		}
		else
		{
			resultString += _T("&#");
			CString tmpString;
			tmpString.Format(_T("%u"), uChar);
			resultString += tmpString;
			resultString += _T(";");
		}
	}
	s = resultString;
	#endif

	const CGXFont& font = style.GetFontRef();
	BOOL bBold = font.GetBold();
	BOOL bStrike = font.GetStrikeOut();
	BOOL bUnderline = font.GetUnderline();
	BOOL bItalic = font.GetItalic();

	if( s.IsEmpty() )
		s = gxSPACE;

	CGXTagHandler* pHandler = NULL;
	if( bBold && ( pHandler = LookupTag(gxFBOLD))  != NULL )
		s = pHandler->ComposeOutput(CGXTagInfo(_T(""), s, FALSE, FALSE));
	if( bStrike &&  ( pHandler = LookupTag(gxFSTRIKE)) != NULL )
		s = pHandler->ComposeOutput(CGXTagInfo(_T(""), s, FALSE, FALSE));
	if( bUnderline && ( pHandler = LookupTag(gxFUNDERLINE)) != NULL )
		s = pHandler->ComposeOutput(CGXTagInfo(_T(""), s, FALSE, FALSE));
	if( bItalic && ( pHandler = LookupTag(gxFITALIC)) != NULL )
		s = pHandler->ComposeOutput(CGXTagInfo(_T(""), s, FALSE, FALSE));

	if( (pHandler = LookupTag(gxFONT)) != NULL )
		s = pHandler->ComposeOutput(CGXTagInfo(GetFontAttribString(style), s, FALSE, FALSE));

	return s;
}

//@doc CGXHtmlW
//@mfunc This function composes the font attributes of the given cell as a string usable 
//in the HTML table cell. It is used by the GetCellContentString function.
//@rdesc CString Return the composed string
//@parm const CGXStyle &style The style of a given cell.
CString CGXHtmlW::GetFontAttribString(const CGXStyle &style)
{
	CString s, strBuf;
	
	COLORREF clr = style.GetTextColor();

	s.Format(_T(" color=\"#%x%x%x%x%x%x\""), 
		GetRValue(clr) / 16, GetRValue(clr) % 16,
		GetGValue(clr) / 16, GetGValue(clr) % 16, 
		GetBValue(clr) / 16, GetBValue(clr) % 16);
	strBuf.Format(_T(" face=\"%s\""), style.GetFontRef().GetFaceName());
	s += strBuf;

	int nFontSize = (int)style.GetFontRef().GetSize();
	if( nFontSize >= 36 )
		nFontSize = 7;
	else if( nFontSize >= 24 )
		nFontSize = 6;
	else if( nFontSize >= 18 )
		nFontSize = 5;
	else if( nFontSize >= 14 )
		nFontSize = 4;
	else if( nFontSize >= 11 )
		nFontSize = 3;
	else if( nFontSize >= 10 )
		nFontSize = 2;
	else 
	{
		if( style.GetFontRef().GetBold())
			nFontSize = 2;
		else
			nFontSize = 1;
	}

	strBuf.Format(_T(" size=\"%d\""), nFontSize);
	s += strBuf;

	return s;
}


//@doc CGXHtmlW
//@mfunc This function composes the HTML table cell string from a given Object grid cell contents.
//It takes into the consideration of merge cell and float cell in the grid to create correct 
//cell span in the HTML table. This composed string is the whole string start with <td> or <th> and
//end with </td> or </th> tags.
//@rdesc CString Return the composed string
//@parm int nRight The right most cell index in the passing selected range or the column count of 
// grid.
//@parm  int nBottom The bottom cell index in the passing selected range or the row count of the
//grid if no selection range is specified.
//@parm  int nRow The current cell row index.
//@parm  int& nNextCol The current cell column index. When the function returns, this variable
//will be assigned a value for the next column index. The increment depends on the cell span of
//this current cell.
//@parm  CellSpan& cellSpan Store the cell span information. This informatoin will be update 
//after the function is returned.
//@parm  BOOL bHeader Indicating whether the current cell is a header cell
CString CGXHtmlW::GetTableCellString(int nRight, int nBottom, int nRow, 
									int& nNextCol, CellSpan& cellSpan, BOOL bHeader)
{
	CString str;

	CGXStyle* pStyle = NULL;
	CGXRange range;
	
	if( cellSpan.row == 0 )
	{
		pStyle = m_pGrid->CreateStyle();
		if( pStyle == NULL )
		{
			throw new CMemoryException;
			//return _T("");
		}
		
		m_pGrid->ComposeStyleRowCol(nRow, nNextCol, pStyle);

		int nOldRow =  nRow;
		int nOldCol = nNextCol;

		BOOL bCovered = FALSE;
		// setup the rowspan and colspan attributes
		if( m_pGrid->GetCoveredCellsRowCol(nRow, nNextCol, range) ||
			m_pGrid->GetMergedCellsRowCol(nRow, nNextCol, range) ||
			m_pGrid->GetFloatedCellsRowCol(nRow, nNextCol, range) )
		{
			// This is a covered cell,
			// Need to initialize the data, and set the col and row span
			cellSpan.row = min(nBottom, (int)range.bottom) - nRow;
			cellSpan.col = min(nRight, (int)range.right) - nNextCol;

			nNextCol += cellSpan.col + 1; // Go to the next uncovered cell
			bCovered = TRUE;
		}
		else // Not a covered cell
			nNextCol++;


		CGXTagHandler* pHandler = NULL;
		if( bHeader )
			pHandler = LookupTag(gxTH);
		else
			pHandler = LookupTag(gxTD);
		// If TH handler doesn't exist, try use TD handler
		if( pHandler == NULL && bHeader )
			pHandler = LookupTag(gxTD);

		if( pHandler != NULL )
			str += pHandler->ComposeOutput(
					CGXTagInfo( GetCellAttribString(*pStyle, bCovered, cellSpan),
					          GetCellContentString(nOldRow, nOldCol, *pStyle), FALSE, TRUE)
							);

		m_pGrid->RecycleStyle(pStyle);
	}
	else // Covered cell
	{
		// decrement the row count and jump to the next uncovered cell
		cellSpan.row--;
		nNextCol += cellSpan.col + 1;

		// If reach the bottom of the covered cell, reset the col information
		if( cellSpan.row == 0 ) 
			cellSpan.col = 0;

		// We do write the cell string !!!
	}
	return str;
}

//@doc CGXHtmlW
//@mfunc This function composes the cell attributes as a string, which include the alignment, 
//background color and the cell span attributes.
//@rdesc CString Return the composed string
//@parm const CGXStyle& style Style of the given grid cell
//@parm  BOOL bCovered Indicating the current cell will span
//@parm  const CellSpan& cellSpan The cell span information if the current cell spans
CString CGXHtmlW::GetCellAttribString(const CGXStyle& style, BOOL bCovered, const CellSpan& cellSpan)
{
	CString strCellAttrib;
	COLORREF bkColor;

	// Compose the cell attributes string
	switch( style.GetHorizontalAlignment() )
	{
	default:
	case DT_LEFT:
		strCellAttrib = _T("");
		break;
	case DT_CENTER:
		strCellAttrib = _T(" align=\"center\"");
		break;
	case DT_RIGHT:
		strCellAttrib = _T(" align=\"right\"");
		break;
	}
	switch( style.GetVerticalAlignment() )
	{
	default:
	case DT_TOP:
		break;
	case DT_VCENTER:
		strCellAttrib += _T(" valign=\"middle\"");
		break;
	case DT_BOTTOM:
		strCellAttrib += _T(" valign=\"bottom\"");
		break;
	}
	bkColor = style.GetInteriorRef().GetColor();
	if( bkColor != RGB(255, 255, 255) )
	{
		CString tmpBuf;
		tmpBuf.Format(_T("  bgcolor=\"#%x%x%x%x%x%x\""),
			GetRValue(bkColor) / 16, GetRValue(bkColor) % 16,
			GetGValue(bkColor) / 16, GetGValue(bkColor) % 16,
			GetBValue(bkColor) / 16, GetBValue(bkColor) % 16);
		strCellAttrib += tmpBuf;
	}
	else
		strCellAttrib += _T(" bgcolor=\"#ffffff\"");

	//	strCellAttrib += _T(" bordercolor=\"#800000\"");
	//	strCellAttrib += _T(" bordercolordark=\"#808080\"");
	//	strCellAttrib += _T(" bordercolorlight=\"#800000\"");

	if( !style.GetWrapText() )
		strCellAttrib += _T(" nowrap");

	if( bCovered )
	{
		CString strTmp;
		if( cellSpan.col > 0 )
		{
			strTmp.Format(_T(" colspan=\"%d\""), cellSpan.col + 1);
			strCellAttrib += strTmp;
		}					
		if( cellSpan.row > 0 )
		{
			strTmp.Format(_T(" rowspan=\"%d\""), cellSpan.row + 1);
			strCellAttrib += strTmp;
		}
	}
	return strCellAttrib;
}
