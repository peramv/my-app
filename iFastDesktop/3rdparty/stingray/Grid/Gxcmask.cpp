///////////////////////////////////////////////////////////////////////////////
// gxcmask.cpp : implementation of the CGXMaskControl class
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

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifndef _AFXPRIV_H_
#include "afxpriv.h"    // for CSharedFile
#endif

#include <ctype.h>

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCMASK")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

GRID_IMPLEMENT_CONTROL(CGXMaskControl, CGXStatic);
IMPLEMENT_DYNAMIC(CGXMaskControl, CEdit);
IMPLEMENT_DYNCREATE(CGXMaskData, CObject);

#ifdef _MBCS
BOOL CGXMaskData::m_bDBCSEnabled = ::GetSystemMetrics(SM_DBCSENABLED);
#endif

//////////////////////////////////////////////////////
// CGXMaskData class
//
// The CGXMaskData class defines the functionality used
// which can be used by CEdit control to add this capapibilty.
//
//   Mask characters:
//
//      Literal - a character that is displayed as-is in the mask,
//          (anything but #,&,A,?,\)
//      # - Digit placeholder (0-9)
//      & - Character placeholder (Any ascii character)
//      A - Alphanumeric placeholder (a-z, A-Z, 0-9)
//      ? - Letters (a-z, A-Z)
//      U - Upper-case letters (A-Z)
//      L - Lower-case letters (a-z)
//      \ - Escape, so that any of the above can be used as a literal
//
//
// Examples:
//       Time: ##:## UU , Example: 12:20 AM
//       Date: ##/##/## , Example: 12/23/95
//       SSN: ###-##-####, Example: 148-92-1531
//       Phone: (###) ###-#### Ext: ####  Example: (800) 924-4223 Ext: 0007
//       Zip: #####, Example: 27858
//       Zip+4: #####-####, Example: 27858-1234
//       Name:  &&&&&&&&&&&&&&&&&&, Example: Bill Gates
//

CGXMaskData::CGXMaskData()
{
	//The default prompt character is a space.
	m_sPrompt = _T('_');
	m_bIgnoreEmptyMask = TRUE;
	m_nMaxLength = INT_MAX;
}

CGXMaskData::~CGXMaskData()
{
	//virtual destruction.
}

void CGXMaskData::Empty()
{
	m_abIsLiteral.RemoveAll();
	m_astrMask.RemoveAll();
}

void CGXMaskData::SetMask(LPCTSTR lpszMask)
{
	ASSERT_VALID(this);

	// check for empty mask string
	if (lpszMask == NULL || *lpszMask == _T('\0'))
	{
		m_abIsLiteral.RemoveAll();
		m_astrMask.RemoveAll();
		m_nMaxLength = INT_MAX;
		return;
	}

	int nMaskLen = (int)_tcsclen(lpszMask);
	int nSrcCount = 0,
		nMaskCount = 0;
	BOOL bEscapeChar = FALSE;
	TCHAR ch;

	// clear out the internal mask chars
	m_abIsLiteral.RemoveAll();
	m_abIsLiteral.SetSize(nMaskLen);

	m_astrMask.RemoveAll();
	m_astrMask.SetSize(nMaskLen);

	BOOL bDoubleByteChar = FALSE;
	TCHAR nDoubleByteLeadChar = 0;
	CString sChar;

	// go through the mask character by character
	for (nSrcCount = 0, nMaskCount = 0; lpszMask[nSrcCount] != _T('\0') && nMaskCount < nMaskLen; nSrcCount++)
	{
		ch = lpszMask[nSrcCount];

		if (GXGetDoubleByteChar(ch, sChar, bDoubleByteChar, nDoubleByteLeadChar))
		{
			if (sChar.IsEmpty())    // leading char
				continue;

			// Process double byte char

			// double byte chars are never mask chars
			bEscapeChar = FALSE;
			m_abIsLiteral[nMaskCount] = TRUE;
			m_astrMask.SetAt(nMaskCount, sChar);
			nMaskCount++;
		}
		else
		{
			// Process a normal character

			// Check and see if it's an escape character.  If it is,
			// then set bEscapeChar for next pass..

			if (!bEscapeChar && ch == _T('\\'))
			{
				bEscapeChar = TRUE;
			}
			else
			{
				if (bEscapeChar)
					m_abIsLiteral[nMaskCount] = (BYTE) TRUE;
				else
					m_abIsLiteral[nMaskCount] = (BYTE) !IsMaskChar(ch);

				m_astrMask[nMaskCount] = (CString) ch;
				bEscapeChar = FALSE;
				nMaskCount++;
			}
		}
	}

	m_abIsLiteral.SetSize( nMaskCount );
	m_astrMask.SetSize( nMaskCount );
}

BOOL CGXMaskData::IsMaskChar(TCHAR ch) const
{
	ASSERT(ch != '\0');
	BOOL bResult = FALSE;

	switch (ch)
	{
	case '#':
	case '&':
	case 'A':
	case '?':
	case 'U':
	case 'L':
		bResult = TRUE;
		break;
	}

	return bResult;
}


// GetData
//
// filters out mask chars from m_strDisplay and
// replaces m_chPrompt chars with blanks
// Return Value: TRUE if valid, FALSE if invalid chars

void CGXMaskData::GetData(CString& strData, int nFirstChar, int nLastChar, BOOL bTrim) const
{
	ASSERT_VALID(this);
	int nMaskCount = 0;
	int nMaskLen   = (int)m_astrMask.GetSize();

	if (nLastChar != -1)
		nMaskLen = min(nMaskLen, nLastChar+1);

	strData.Empty();

	// Just return display string when mask is empty
	if (m_bIgnoreEmptyMask && IsEmptyMask())
		GetDisplayString(strData, nFirstChar, nLastChar);
	else
	{
		for (nMaskCount = nFirstChar; nMaskCount < nMaskLen; nMaskCount++)
		{
			if (!IsLiteral(nMaskCount))
			{
				if (m_astrDisplay.GetAt(nMaskCount) == m_sPrompt)
					strData += _T(' ');
				else
					strData += m_astrDisplay[nMaskCount];
			}
		}

		if (bTrim)
		{
#if _MFC_VER >= 0x0400
			strData.TrimRight();
#else
			int nTrimPos = strData.GetLength() - 1;

			while (nTrimPos >= 0 && strData.GetAt(nTrimPos) == _T(' '))
				nTrimPos--;

			strData = strData.Left(nTrimPos + 1);
#endif
		}
	}
}

BOOL CGXMaskData::IsLiteral(int nPos) const
{
	if (m_bIgnoreEmptyMask && IsEmptyMask())
		return FALSE;
	else
		return m_abIsLiteral[nPos];

}

// SetData
//
// Adds mask chars to m_astrDisplay and
// replaces blanks with m_chPrompt chars
// Return Value: TRUE if valid, FALSE if invalid chars

int CGXMaskData::SetData(LPCTSTR lpszData, int nStartPos, BOOL bInsert)
{
	BOOL bIgnorePromptChars = TRUE;

	//
	ASSERT_VALID(this);
	int nDataLen    = (int)_tcslen(lpszData);       // data length

	// Just set display string when mask is empty
	if (m_bIgnoreEmptyMask && IsEmptyMask())
	{
		return SetDisplayString(lpszData, nStartPos, bInsert);
	}

	if (nStartPos == -1)
	{
		ClearData();
		nStartPos = 0;
	}

	int nDataCount  = 0;                        // counter for the data string
	int nMaskCount  = nStartPos;                // counter for the mask string
	int nMaskLen    = (int)m_astrMask.GetSize();     // mask length

	if (nMaskLen == 0)
		return -1;

	if (nStartPos < 0 || nStartPos >= nMaskLen)
	{
		TRACE(_T("CEdit::SetData() -- Start position '%d' is invalid!\n"), nStartPos);
		return -1;
	}

	// if the starting position is 0, rebuild the display string from scratch

	// if the starting position isn't a data position, get the
	// next data position after the starting position
	if (IsLiteral(nMaskCount))
		nMaskCount = GetNextDataPos(nMaskCount);

	// check to make sure we found a data position!
	if (nMaskCount >= nMaskLen || nMaskCount == -1)
		return -1;

	BOOL bDoubleByteChar = FALSE;
	TCHAR nDoubleByteLeadChar = 0;
	CString sChar;

	// now loop through the data string
	// go through the mask character by character
	for (nDataCount = 0; nDataCount < nDataLen; nDataCount++)
	{
		TCHAR ch = lpszData[nDataCount];
		int nPos;

		if (nMaskCount >= nMaskLen || nMaskCount == -1)
			break;

		if (GXGetDoubleByteChar(ch, sChar, bDoubleByteChar, nDoubleByteLeadChar))
		{
			if (sChar.IsEmpty())    // leading char
				continue;
		}

		if (IsLiteral(nMaskCount))
			nMaskCount = GetNextDataPos(nMaskCount);

		// Process both double-byte and single-byte chars

		if (nMaskCount < nMaskLen && IsCharValid(nMaskCount, sChar))
		{
			if(bInsert)
			{
				// push char into string
				if (!PushChar(nMaskCount, sChar, nPos))
					break; // could not push character, get out
			}
			else
				// overtype existing char
				m_astrDisplay.SetAtGrow(nMaskCount, sChar);

			// get the next data position
			nMaskCount++;
		}
		else
		{
			// if the bIgnorePromptChars flag has been set to FALSE, then we will
			// treat any data character that matches the current prompt character as an
			// implicit blank data position.
			if (!bIgnorePromptChars && sChar == m_sPrompt)
			{
				// get the next data position
				nMaskCount++;
				if (IsLiteral(nMaskCount))
					nMaskCount = GetNextDataPos(nMaskCount);
			}
			else
			{
				// could not push character, get out
				break;
			}
		}
	}

	return nMaskCount;
}

void CGXMaskData::ClearData()
{
	ASSERT_VALID(this);

	// Just set display string when mask is empty
	if (m_bIgnoreEmptyMask && IsEmptyMask())
	{
		m_astrDisplay.RemoveAll();
		return;
	}

	int nMaskCount = 0;   //counter in the mask string
	int nMaskLen = 0;  //length of mask string

	// get the length of the mask and data strings
	nMaskLen = (int)m_astrMask.GetSize();

	// empty the out string just in case
	m_astrDisplay.RemoveAll();
	m_astrDisplay.SetSize(nMaskLen);

	// go through the mask string
	for (nMaskCount = 0; nMaskCount < nMaskLen; nMaskCount++)
	{
		// get the character in the nMaskCount position
		const CString& sChar = m_astrMask.GetAt(nMaskCount);

		// if the character is a literal, add it to the out string
		if (IsLiteral(nMaskCount))
			m_astrDisplay.SetAt(nMaskCount, sChar);
		else    // else add the prompt character
			m_astrDisplay.SetAt(nMaskCount, m_sPrompt);
	}
}

#ifdef _MBCS
inline unsigned int AFXAPI _gxgetmbchar(LPCTSTR buf)
{
	unsigned int uChar;

	if (buf[1] != _T('\0'))
	{
		// multibyte char
		uChar = buf[1];
		uChar += buf[0] << 8;
	}
	else
		uChar = buf[0];

	return uChar;
}
#endif

BOOL CGXMaskData::IsCharValid(int nPos, CString& sChar) const
{
	ASSERT_VALID(this);
	BOOL bRet = FALSE;

	// All characters are valid when mask string is empty
	if (m_bIgnoreEmptyMask && IsEmptyMask())
	{
		return TRUE;
	}

	// if we are at the end of the input mask, this char is not valid
	if (nPos >= m_astrMask.GetSize() || nPos < 0)
		return FALSE;

	// if the position is on a literal char it's not valid
	if (IsLiteral(nPos))
		bRet = FALSE;
	else
	{
		if (sChar == _T(' '))
		{
			sChar = m_sPrompt;
			return TRUE;
		}

		if (sChar == m_sPrompt)
			return TRUE;

#ifdef _MBCS
		ASSERT(m_astrMask[nPos].GetLength() == 1);

		unsigned int uChar = _gxgetmbchar(sChar);

		// the following is some code snippet from ismbalph.c
		// buf[0] = (c >> 8) & 0xFF;
		// buf[1] = c & 0xFF;
#else
		TCHAR uChar = sChar[0];
#endif

		switch (m_astrMask[nPos][0])
		{
		case _T('#'): // numerics only, no double-byte
			{
			bRet = _istdigit(uChar);
			break;
			}

		case _T('?'): // alphas only, or double-byte
			{
			bRet = _istalpha(uChar);
			break;
			}

		case _T('A'): // alpanumerics only
			{
			bRet = _istalnum(uChar);
			break;
			}

		case _T('L'): // force lower case
			{
			bRet = _istalpha(uChar);
			if (bRet)
			{
#ifdef _MBCS
				uChar = _totlower(uChar);
				if (sChar.GetLength() == 2)
				{
					sChar.SetAt(0, (TCHAR) ((uChar >> 8) & 0xFF));
					sChar.SetAt(1, (TCHAR) (uChar & 0xFF));
				}
				else
					sChar = (TCHAR) uChar;
#else
				sChar = (TCHAR) _totlower(uChar);
#endif
			}
			break;
			}

		case _T('U'): // force upper case
			{
			bRet = _istalpha(uChar);
			if (bRet)
			{
#ifdef _MBCS
				uChar = _totupper(uChar);
				if (sChar.GetLength() == 2)
				{
					sChar.SetAt(0, (TCHAR) ((uChar >> 8) & 0xFF));
					sChar.SetAt(1, (TCHAR) (uChar & 0xFF));
				}
				else
					sChar = (TCHAR) uChar;
#else
				sChar = (TCHAR) _totupper(uChar);
#endif
			}
			break;
			}

		case _T('&'): // any ASCII character
			{
			bRet = TRUE;
			break;
			}

		}
	}

	return bRet;
}

// GetDisplayString
//
// Build strDisplay from m_astrDisplay

void CGXMaskData::GetDisplayString(CString& strDisplay, int nFirstChar, int nLastChar) const
{
	strDisplay.Empty();

	int nLen = (int)m_astrDisplay.GetSize();
	if (nLastChar != -1)
		nLen = min(nLen, nLastChar+1);

	for (int nCounter = nFirstChar; nCounter < nLen; nCounter++)
		strDisplay += m_astrDisplay[nCounter];
}

// SetDisplayString
//
// Change m_astrDisplay

int CGXMaskData::SetDisplayString(LPCTSTR lpszDisplay, int nStartPos, BOOL bInsert)
{
	int nDispCount = 0,
		nCount = 0,
		nSize = (int)_tcsclen(lpszDisplay),
		nMaskLen = (int)m_astrMask.GetSize();

	if (nStartPos == -1)
	{
		ClearData();
		nStartPos = 0;
	}
	ASSERT(nStartPos == 0 || nStartPos > 0 && nStartPos <= m_astrDisplay.GetSize());
	// ASERTION-> Argument must be either -1 or between 0 and string length->END

	if (nMaskLen == 0 && !bInsert)
		m_astrDisplay.SetSize(nSize+nStartPos);

	nCount = nStartPos;

	BOOL bDoubleByteChar = FALSE;
	TCHAR nDoubleByteLeadChar = 0;
	CString sChar;

	while (lpszDisplay[nDispCount] != _T('\0'))
	{
		// Get out if string gets too long
		if (nMaskLen > 0 && nCount >= nMaskLen)
			break;

		if (GXGetDoubleByteChar(lpszDisplay[nDispCount++], sChar, bDoubleByteChar, nDoubleByteLeadChar))
		{
			if (sChar.IsEmpty())    // leading char
				continue;
		}

		// Process both double-byte and single-byte chars

		BOOL bLiteral = IsLiteral(nCount);

		// literal must not be different
		if (bLiteral && _tcscmp(sChar, m_astrMask[nCount]) != 0
			|| !bLiteral && !IsCharValid(nCount, sChar))
		{
			// get out
			return -1;
		}

		if (bInsert)
		{
			int nPos;
			if (!bLiteral && !PushChar(nCount, sChar, nPos))
				return -1;
		}
		else
			m_astrDisplay[nCount] = sChar;

		nCount++;
	}

	if (nMaskLen != 0)
		m_astrDisplay.SetSize(nMaskLen);
	else if (m_astrDisplay.GetSize() > m_nMaxLength)
		m_astrDisplay.SetSize(m_nMaxLength);

	return nCount;
}

//
//  SetPromptChar
//
//  Changes the prompt character from the default ' '
//  to something else like '_'.
//
//  Updates the display string to reflect the changes.
//

BOOL CGXMaskData::SetPromptChar(const CString& sPrompt, BOOL bUpdateDisplayString /*= TRUE*/)
{
	ASSERT_VALID(this);

	// Make sure this is only one single or double byte char
	if (sPrompt.GetLength() > 2 || sPrompt.GetLength() == 2 && !_istlead(sPrompt[0]))
	{
		TRACE0("CGXMaskData::SetPromptChar: Warning, attempt to set invalid prompt character, ignoring....");
		return FALSE;
	}

	LPCTSTR pszPrompt = sPrompt;

	// Blank is default
	if (sPrompt.IsEmpty())
		pszPrompt = _T("_");

	if (bUpdateDisplayString)
	{
		int nPosition = 0;
		int nMaskLen = (int)m_astrMask.GetSize();

		for (nPosition = 0; nPosition < nMaskLen; nPosition++)
		{
			if (!IsLiteral(nPosition))
			{
				if (m_sPrompt == m_astrDisplay[nPosition])
					m_astrDisplay[nPosition] = pszPrompt;
			}
		}
	}

	m_sPrompt = pszPrompt;

	return TRUE;
}

//
//  GetNextDataPos
//
//  Parses the mask and figures out where the next
//  position that will accept data is located.
//

int CGXMaskData::GetNextDataPos(int nOldPos) const
{
	ASSERT_VALID(this);

	int nMaskLen = (int)m_astrMask.GetSize();      // length of mask string
	int nNewPos = nOldPos;                    // new position for cursor

	// if the mask string is empty, use the length of the dispay string
	if (m_bIgnoreEmptyMask && IsEmptyMask())
		nMaskLen = m_nMaxLength;

	ASSERT(nOldPos >= -1 || nOldPos <= nMaskLen);

	// if the mask string is empty, just return
	if (nMaskLen < 1)
		return nOldPos;

	// if we are at the end of the mask, skip this code
	if (nNewPos < nMaskLen)
	{
		nNewPos++;

		// try positions forward until you find one or fall off
		while (nNewPos < nMaskLen)
		{
			if (IsLiteral(nNewPos))
				nNewPos++;
			else
				break;
		}

		// if we fell off the end without finding a data position
		// return -1
		if (nNewPos >= nMaskLen)
		{
			nNewPos = -1;
		}
	}

	return nNewPos;
}

//
//  GetPrevDataPos
//
//  Parses through the mask to find the location
//  of the previous data (non-literal) character
//  used when VK_BACK/VK_LEFting through the medit.
//

int CGXMaskData::GetPrevDataPos(int nOldPos) const
{
	ASSERT_VALID(this);

	int nMaskLen = (int)m_astrMask.GetSize();      // length of mask string
	int nNewPos = nOldPos;                    // new position for cursor

	// if the mask string is empty, use the length of the dispay string
	if (m_bIgnoreEmptyMask && IsEmptyMask())
		nMaskLen = (int)m_astrDisplay.GetSize()+1;

	// test inputs
	ASSERT(nOldPos >= 0 || nOldPos <= nMaskLen);

	// if the mask string is empty, just return
	if (nMaskLen < 1)
		return nOldPos;

	nNewPos--;

	// try positions backward until you find one or fall off
	while (nNewPos >= 0)
	{
		if (IsLiteral(nNewPos))
			nNewPos--;
		else
			break;
	}

	return nNewPos;
}

//
//  FindLastFilledDataPos
//
//     Finds the last spot where data was entered.
//

// TO DO:	Overhaul to account for always positive positions and architecture integer sizes, 
//			i.e. replace int in function def/decl with size_t
int CGXMaskData::FindLastFilledDataPos(int nStartPos) const
{
	ASSERT_VALID(this);
	int nNextPos = 0;

	// return length of display string when mask is empty
	if (m_bIgnoreEmptyMask && IsEmptyMask())
	{
		return min(nStartPos, int(m_astrDisplay.GetSize()));
	}

	if (nStartPos == 0 && IsEmptyMask())
	{
		TRACE0("Warning, attempt to type into a masked edit without a mask set..\n");
		return 1;
	}

	// if the start pos is greater than the length of the mask,
	if (nStartPos >= m_astrMask.GetSize() && nStartPos != 0)
	{
		// check to see if the last position in the mask is a data position
		// if so then if it's filled, return the length of the mask
		// if not then subtract 1 from the start pos, so we don't assert
		// when checking the mask later
		if (!IsLiteral(nStartPos-1) && m_astrDisplay[nStartPos-1] != m_sPrompt)
			return nStartPos;

		nStartPos--;
	}

	// check to see if the next data position to the right is filled
	// if so, then don't change the position
	if (IsLiteral(nStartPos))
		nNextPos = GetNextDataPos(nStartPos);
	else
		nNextPos = nStartPos;

	if (nNextPos != -1 && m_astrDisplay[nNextPos] != m_sPrompt)
		return nStartPos;

	// check to see if this position is a data position.
	if (IsLiteral(nStartPos))
		nStartPos = GetPrevDataPos(nStartPos);

	// keep checking in a loop for a filled data pos
	while (nStartPos > 0 && m_astrDisplay[nStartPos] == m_sPrompt)
		nStartPos = GetPrevDataPos(nStartPos);

	// if there were no data positions to the left of the start pos
	// then return the first data position
	if (nStartPos <= 0)
	{
		if (nStartPos == 0 && m_astrDisplay[nStartPos] != m_sPrompt)
			return 1;
		else
			return GetNextDataPos(-1);
	}
	else
		// return one greater so that it will line up on the
		// right side of the position
		return nStartPos + 1;
}

// PushChar
//
//
//
//
//
//
//

BOOL CGXMaskData::PushChar(int nStartPos, const CString& sChar, int& nNextPos)
{
	ASSERT_VALID(this);
	int nLastDataPos;
	int nPosCount;
	int nMaskLen = (int)m_astrMask.GetSize();      // length of mask string
	nNextPos = -1;

	// check if the mask string is empty
	if (m_bIgnoreEmptyMask && IsEmptyMask())
	{
		if (m_astrDisplay.GetSize() >= m_nMaxLength)
			return FALSE;

		m_astrDisplay.InsertAt(nStartPos, sChar);
		nNextPos = nStartPos+1;
		return TRUE;
	}

	// check inputs
	if (nStartPos < 0 || nStartPos > nMaskLen)
	{
		ASSERT(FALSE);
		TRACE(_T("CGXMaskData::PushChar() -- Start position '%i' is invalid!\n"), nStartPos);
		return FALSE;
	}

	// get the index of the last data position
	nLastDataPos = GetPrevDataPos(nMaskLen);

	// now go backwards until you find an actual data character
	nPosCount = nLastDataPos;
	while (nPosCount >= 0 && m_astrDisplay[nPosCount] == m_sPrompt)
		nPosCount = GetPrevDataPos(nPosCount);

	// if we are still in the last data position, return -1 and get out
	if (nPosCount == nLastDataPos)
		return FALSE;
	else
	{
		while (nPosCount >= nStartPos)
		{
			// shift the character forward one data place
			m_astrDisplay.SetAtGrow(GetNextDataPos(nPosCount), m_astrDisplay[nPosCount]);
			// move nPosCount to the previous data position
			nPosCount = GetPrevDataPos(nPosCount);
		}

		// set the input char in the starting position
		m_astrDisplay[nStartPos] = sChar;

		// set the selection foward one data position
		nNextPos = GetNextDataPos(nStartPos);

		// check if we are at the end of the mask
		if(nNextPos == -1)
			nNextPos = nStartPos + 1;
	}

	return TRUE;
}

//
//  PullChar
//
//
//
//
//
//

void CGXMaskData::PullChar(int nFromPos, int nToPos)
{
	ASSERT_VALID(this);

	int nToCount;
	int nMaskLen = (int)m_astrMask.GetSize();      // length of mask string

	// check if the mask string is empty
	if (m_bIgnoreEmptyMask && IsEmptyMask())
	{
		m_astrDisplay.RemoveAt(nToPos, nFromPos-nToPos);
		return;
	}

	if (nFromPos < 0 || nFromPos > nMaskLen)
	{
		ASSERT(FALSE);
		TRACE(_T("CGXMaskData::PullChar() -- Start position '%d' is invalid!\n"), nFromPos);
		return;
	}

	// if the to position is on a literal position,
	// then try to move it foward
	if (IsLiteral(nToPos))
	{
		nToPos = GetNextDataPos(nToPos);

		// if the to pos is now greater than the from pos,
		// there was no data to pull
		if (nToPos > nFromPos)
			return;
	}

	// if the from pos is = to the length of m_strMask, set to -1
	if (nFromPos == m_astrMask.GetSize())
		nFromPos = -1;
	else if (IsLiteral(nFromPos))
		nFromPos = GetNextDataPos(nFromPos);

	nToCount = nToPos;

	while (nFromPos >= 0)
	{
		// move the character
		m_astrDisplay[nToCount] = m_astrDisplay[nFromPos];

		// move the pointers
		nFromPos = GetNextDataPos(nFromPos);
		nToCount = GetNextDataPos(nToCount);
	}

	// clear out the rest of the data from the nToCount on
	while (nToCount >= 0)
	{
		m_astrDisplay[nToCount] = m_sPrompt;
		nToCount = GetNextDataPos(nToCount);
	}

}

BOOL CGXMaskData::IsValidDisplayString() const
{
	// First, handle case for empty mask
	if (m_bIgnoreEmptyMask && IsEmptyMask())
		return m_astrDisplay.GetSize() <= m_nMaxLength;

	for (int nCounter = 0; nCounter < m_astrDisplay.GetSize(); nCounter++)
	{
		if (IsLiteral(nCounter))
		{
			// literal must not be different
			if (_tcscmp(m_astrDisplay[nCounter], m_astrMask[nCounter]) != 0)
				return FALSE;
		}
		else
		{
			// check mask chars
			CString sChar = m_astrDisplay[nCounter];
			if (!IsCharValid(nCounter, sChar))
				return FALSE;
		}
	}

	return TRUE;
}

// GetEditPos
//
// Computes the edit position from the given character position
// The edit position can be passed to SetSel so that the
// caret will be positioned before a double-byte char

int CGXMaskData::GetEditPos(int nCharPos) const
{
	ASSERT(nCharPos >= -1);
#ifdef _MBCS
	if (!m_bDBCSEnabled || nCharPos == -1)
		return nCharPos;

	int nEditPos = 0;

	for (int nCounter = 0; nCounter < nCharPos; nCounter++)
		nEditPos += m_astrDisplay[nCounter].GetLength();

	return nEditPos;
#else
	return nCharPos;
#endif
}

// GetCharPos
//
// Computes the absolute characater position from the given edit position

int CGXMaskData::GetCharPos(int nEditPos) const
{
	ASSERT(nEditPos >= -1);
#ifdef _MBCS
	if (!m_bDBCSEnabled ||nEditPos == -1)
		return nEditPos;

	int nCharPos = 0,
		nCounter = 0;

	while (nCounter < nEditPos)
	{
		nCounter += m_astrDisplay[nCharPos].GetLength();
		nCharPos++;
	}

	return nCharPos;
#else
	return nEditPos;
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CGXMaskControl
//
// CGXMaskControl is fully compatible with OG - control
// interface and can be shared among many cells.
//
// It is necessary to register the control in OnInitialUpdate() with
//
// RegisterControl(
//      GX_IDS_CTRL_MASKEDIT,
//      new CGXMaskControl(this, GX_IDS_CTRL_MASKEDIT));
//
// and also register user attributes for the edit mask and prompt char with
//
// GetParam()->GetStylesMap()->AddUserAttribute(GX_IDS_UA_INPUTMASK);
// GetParam()->GetStylesMap()->AddUserAttribute(GX_IDS_UA_INPUTPROMPT);
//
// An example for applying the control to cells is:
//
//      SetStyleRange(CGXRange(5,5,10,10),
//          CGXStyle()
//          .SetControl(GX_IDS_CTRL_MASKEDIT)
//          .SetUserAttribute(GX_IDS_UA_INPUTMASK, _T("###-###"))
//          .SetUserAttribute(GX_IDS_UA_INPUTPROMPT, _T("_"))
//          .SetValue("123456");
//
// This will display "123-456" in the cells.
//
// Note: the mask characters are not stored in style.value
// See CGXMaskEdit for a list of Mask characters.
//
// Known limitation:
// - AutoSize is not possible.
// - WordBreak is not possible.
// - Multiple line edit is not supported.
//
// If you need the above features, you should consider using
// the standard edit control.
//

/////////////////////////////////////////////////////////////////////////////
// CGXMaskControl

CGXMaskControl::CGXMaskControl(CGXGridCore* pGrid, UINT nID, CRuntimeClass* pDataClass)
	: CGXStatic(pGrid)
{
	ASSERT(pDataClass != NULL);

	m_nID = nID;

	m_bDisplayEmpty = FALSE;    // Set this TRUE if mask should
		// also be displayed for empty values

	m_bInsertMode = TRUE;
	m_bIsActive = FALSE;

	m_pMask = NULL;
	m_pExtMask = NULL;
	m_bUpdateEditStyle = FALSE;
	m_dyHeight = 0;
	m_dxMaxCharWidth = 0;

	m_rgbWndHilightText   = GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_bAlwaysLeftJustified = FALSE;

	m_dwEditStyle = 0;

	// NOTE: There is a problem with Win32s. It is
	// not possible to support the automatic switching
	// from right-aligned to left-aligned text on the
	// fly while the user is entering data. Therefore
	// I have turned off this method for Win32s.
	//
	// So, if the user wants to type in text in a right-aligned
	// or centered cell, and the CEdit window gets the focus
	// the text will be displayed left-aligned.
	//
	// A note to MAC and UNIX developers: If you encounter
	// weird things when the user enters large text into
	// right-aligned or centered cells, you should also
	// turn off this feature. Please let us know if you
	// think we should turn this feature off for MAC
	// or UNIX.

#if _MFC_VER >= 0x0300 && _MFC_VER < 0x0420
	if (GXGetAppData()->bWin31)
		m_bAlwaysLeftJustified = TRUE;
#endif

	m_bForceReplaceData = FALSE;

	// this creates objects of the specified runtime type
	AttachData(pDataClass);
}

CGXMaskControl::~CGXMaskControl()
{
		delete m_pMask;
		delete m_pExtMask;

	DestroyWindow();
}


void AFXAPI CGXMaskControl::AddUserAttributes(CGXStylesMap* pStylesMap)
{
		// Masked input
	pStylesMap->AddUserAttribute(GX_IDS_UA_INPUTMASK,
		CGXStyle().SetWrapText(TRUE).SetAutoSize(TRUE));

	pStylesMap->AddUserAttribute(GX_IDS_UA_INPUTPROMPT,
		CGXStyle().SetMaxLength(1));
}

CWnd* CGXMaskControl::GetWndPtr() const
{
	return (CWnd*) this;
}

void CGXMaskControl::AttachData(CRuntimeClass* pDataClass)
{
	ASSERT(pDataClass);

	if (pDataClass)
	{
			delete m_pMask;
			delete m_pExtMask;
		m_pMask = (CGXMaskData*) pDataClass->CreateObject();
		m_pExtMask = (CGXMaskData*) pDataClass->CreateObject();
	}
}

BOOL CGXMaskControl::CreateControl(DWORD dwStyle, LPRECT lpRect)
{
	if (!m_pMask)
		AttachData();

	CRect r(0,0,0,0);

	if (lpRect)
		r = *lpRect;

#ifndef _UNICODE
	return CWnd::Create(_T("EDIT"), NULL, dwStyle, r, GridWnd(), m_nID);
#else
	return CWnd::Create(_T("GXEDIT"), NULL, dwStyle, r, GridWnd(), m_nID);
#endif
}

BEGIN_MESSAGE_MAP(CGXMaskControl, CEdit)
	//{{AFX_MSG_MAP(CGXMaskControl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
	ON_WM_SYSKEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
#if _MFC_VER >= 0x0300
	ON_WM_CONTEXTMENU()
#endif
END_MESSAGE_MAP()

// Status
void CGXMaskControl::SetActive(BOOL bActive)
{
	if (!m_bIsActive && bActive && m_hWnd)
	{				 
		m_bIsActive = TRUE;
		// Force a call to GetStyleRowCol() because
		// GetStyleRowCol() might set style attributes
		// depending on the IsActive() flag
		FreeStyle();
		NeedStyle();
	}
	else
		m_bIsActive = bActive && m_hWnd;
}

BOOL CGXMaskControl::IsActive()
{
	return m_bIsActive;
}

void CGXMaskControl::SetModify(BOOL bModified)
{
	if (m_hWnd)
		CEdit::SetModify(bModified);
}

BOOL CGXMaskControl::GetModify()
{
	return m_hWnd && CEdit::GetModify();
}


void CGXMaskControl::InitMask(CGXMaskData* pMask, const CGXStyle& style)
{
	// Load strings from CGXStyle
	CString sMask;
	CString sPrompt = _T('_');
	style.GetUserAttribute(GX_IDS_UA_INPUTMASK, sMask);
	style.GetUserAttribute(GX_IDS_UA_INPUTPROMPT, sPrompt);

	// and initialize CGXMaskData
	pMask->Empty();
	pMask->SetPromptChar(sPrompt, FALSE);
	pMask->SetMask(sMask);
	pMask->SetMaxLength(INT_MAX);
	if (style.GetIncludeMaxLength() && style.GetMaxLength() > 0)
		pMask->SetMaxLength(style.GetMaxLength());
}

// Operations
void CGXMaskControl::Init(ROWCOL nRow, ROWCOL nCol)
{
	// Stores the cell coordinates, resets the style and sets the window text
	CGXStatic::Init(nRow, nCol);

	if (!m_hWnd)
		CreateControl();

	NeedStyle();

	// window text
	SetValue(m_pStyle->GetIncludeValue() ? (LPCTSTR) m_pStyle->GetValueRef() : _T(""));

	if (m_hWnd)
	{
		SetSel(0, -1, FALSE);   // Select all
		// Note: Call SetSel(0, 0, FALSE); instead, if you want to set the cursor to the leftmost position. 

		if ((Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_SETCURRENT)
			&& OnStartEditing())
			SetActive(TRUE);
	}

	SetModify(FALSE);
}

// NOTE: UpdateDisplay will set the modified flag for the cell
// and call OnModifyCell().

void CGXMaskControl::UpdateDisplay(LPCTSTR lpszText)
{
	if (lpszText)
		m_pMask->SetDisplayString(lpszText);

	CString sText;
	m_pMask->GetDisplayString(sText);
	SetWindowText(sText);
	SetModify(TRUE);
}

void CGXMaskControl::SetCurrentText(const CString& str)
{
	if (!IsInit() || !m_hWnd)
		return;

	if (!IsActive())
		SetActive(TRUE);

	if (ValidateString(str))
	{
		UpdateDisplay(str);
		OnModifyCell();
	}
}

// GetCurrentText
//
// Get masked text which is displayed in the cell

void CGXMaskControl::GetCurrentText(CString& sMaskedResult)
{
	if (IsInit())
	{
		m_pMask->GetDisplayString(sMaskedResult);
	}
	else
	{
		TRACE0("Warning: GetCurrentText was called for an unitialized control!\n");

		// Control is not initialized - Unable to determine text
		sMaskedResult.Empty();
	}
}

BOOL CGXMaskControl::GetValue(CString& strResult)
{
	// Reads out the window text and converts it into
	// the plain value which should be stored in the style object.

	if (!IsInit())
		return FALSE;

	m_pMask->GetData(strResult);

	return TRUE;
}

void CGXMaskControl::SetValue(LPCTSTR pszRawValue)
{
	// Convert the value to the text which should be
	// displayed in the current cell and show this
	// text. (don't change the modify flag and do not
	// call OnModifyCell!)

	if (m_hWnd)
	{
		NeedStyle();
		InitMask(m_pMask, *m_pStyle);
		m_pMask->SetData(pszRawValue);

		CString sText;
		m_pMask->GetDisplayString(sText);
		SetWindowText(sText);
	}
}

BOOL CGXMaskControl::Store()
{
	// Calls SetStyleRange() and resets the modify flag
	ASSERT(m_pStyle);

	CString sValue;
	if (m_pStyle && GetModify() && GetValue(sValue))
	{
		SetActive(FALSE);

		return Grid()->SetValueRange(
			CGXRange(m_nRow, m_nCol),
			sValue,
			gxOverride,
			0, GX_INVALIDATE);
			// Cell will be automatically redrawn inactive
	}

	return TRUE;
}

// GetControlText
//
// Adds literals from the input mask to the value
//

BOOL CGXMaskControl::GetControlText(CString& strDisplay, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style)
{
	// Unused:
	nRow, nCol;

	InitMask(m_pExtMask, style);

	if (pszRawValue == NULL)
		pszRawValue = style.GetValueRef();

	if (m_bDisplayEmpty || _tcslen(pszRawValue) > 0)
	{
		if (m_pExtMask->SetData(pszRawValue) == -1)
		{
			TRACE(_T("Warning: %s does not fit to mask\n"),
				pszRawValue ? pszRawValue : (LPCTSTR) style.GetValueRef());
			return FALSE;
		}

		m_pExtMask->GetDisplayString(strDisplay);
	}
	else
		strDisplay.Empty();

	return TRUE;
}

// SetControlText
//
// Validates the string and filters out literals
// before it stores the value in the grid.
//

BOOL CGXMaskControl::ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle)
{
	CGXStyle* pStyle = NULL;
	BOOL bSuccess = FALSE;

	if (pOldStyle == NULL)
	{
		pStyle = Grid()->CreateStyle();
		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	// allow only valid input
	{
		InitMask(m_pExtMask, *pOldStyle);

		m_pExtMask->SetDisplayString(str);

		if (!m_pExtMask->IsValidDisplayString())
		{
			// Display string does not match correcttly, try data only
			if (m_pExtMask->SetData(str) == -1)
				goto exitcv;
		}

		m_pExtMask->GetData(str);

		bSuccess = TRUE;
	}

exitcv:
	if (pStyle)
		Grid()->RecycleStyle(pStyle);

	return bSuccess;
}

void CGXMaskControl::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	// Notes on Draw:
	// if (nRow == m_nRow && nCol == m_nCol && m_bIsActive)
	//     initialize CWnd, make it visible and set focus
	// else {
	//     lookup style and draw static, e.g.:
	//     - edit control with GXDrawTextLikeMultiLineEdit
	// }

	ASSERT_VALID(pDC);

	// if (nRow == m_nRow && nCol == m_nCol && m_bIsActive)
	//     initialize CWnd, make it visible and set focus
	if (nRow == m_nRow && nCol == m_nCol && IsActive() && !Grid()->IsPrinting())
	{
		// ------------------ Active Window ---------------------------

		Hide();

		// Font
		if (m_font.GetSafeHandle())
			m_font.DeleteObject();

		CFont* pOldFont = 0;

		CGXFont font(m_pStyle->GetFontRef());
		font.SetSize(font.GetSize()*Grid()->GetZoom()/100);
		font.SetOrientation(0);
		
		// no vertical font for editing the cell
		const LOGFONT& _lf = font.GetLogFontRef();
		if ( !m_font.CreateFontIndirect(&_lf) )
		{
			TRACE1("Failed to create font '%s' in CGXMaskControl::Draw\n",
				(LPCTSTR) m_pStyle->GetFontRef().GetDescription());
		}
		
		// Cell-Color
		COLORREF rgbText = m_rgbWndHilightText;
		COLORREF rgbCell = m_pStyle->GetInteriorRef().GetColor();

		if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		{
			rgbText = RGB(0,0,0);
			rgbCell = RGB(255,255,255);
		}

		// Background + Frame
		DrawBackground(pDC, rect, *m_pStyle, TRUE);

		CRect rectText = GetCellRect(nRow, nCol, rect);

		pOldFont = pDC->SelectObject(&m_font);

		TEXTMETRIC    tm;
		pDC->GetTextMetrics(&tm);
		m_dyHeight = tm.tmHeight + tm.tmExternalLeading + 1;
		m_dxMaxCharWidth = tm.tmMaxCharWidth;

		if (pOldFont)
			pDC->SelectObject(pOldFont);

		if (!m_pStyle->GetWrapText()) //  && !m_pStyle->GetAllowEnter())
		{
			// vertical alignment for single line text
			// is done by computing the window rectangle for the CEdit
			if (m_pStyle->GetIncludeVerticalAlignment())
			{
				switch (m_pStyle->GetVerticalAlignment())
				{
				case DT_VCENTER:
					rectText.top += max(0, (rectText.Height() - m_dyHeight) /2);
					break;
				case DT_BOTTOM:
					rectText.top = max(rectText.top, rectText.bottom-m_dyHeight);
				break;
				}
			}
			rectText.bottom = min(rectText.bottom, rectText.top + m_dyHeight - 1);
		}

		DWORD ntAlign = m_pStyle->GetHorizontalAlignment() | m_pStyle->GetVerticalAlignment();

		if (ntAlign & DT_RIGHT)
			rectText.right++;

		SetFont(&m_font);

		MoveWindow(rectText, FALSE);
		m_rgbCell = rgbCell;
		m_ntAlign = ntAlign;

		SetCellColor(rgbCell);
		SetTextAlign((UINT) ntAlign);

		SetActive(TRUE);

#ifdef _UNIX_
		// Wind/U-specific: ShowWindow was being called from within OnShowWindow
		// if the edit style has changed because the edit control
		// is destroyed and recreated if it's styles has changed.
		// This caused a crash on Solaris. I call UpdateEditStyle
		// before ShowWindow to prevent this.
		UpdateEditStyle();
#endif

		SetReadOnly(IsReadOnly());

		if (GetFocus() == GridWnd())
		{
			Grid()->SetIgnoreFocus(TRUE);
			SetFocus();
			Grid()->SetIgnoreFocus(FALSE);
		}

#if _MFC_VER < 0x0300
		// scroll caret into view
		int nStart, nEnd;
		GetSel(nStart, nEnd);
		SetSel(nStart, nEnd, FALSE);
#endif

		ShowWindow(SW_SHOW);

		if (nRow > Grid()->GetFrozenRows() && (Grid()->GetTopRow() > nRow 
			|| nCol > Grid()->GetFrozenCols() && Grid()->GetLeftCol() > nCol))
		// Ensure that the window cannot draw outside the clipping area!
		{
			CRect rectClip;
			if (pDC->GetClipBox(&rectClip) != ERROR)
			{
				CRect r = rect & Grid()->GetGridRect();
				GridWnd()->ClientToScreen(&r);
				ScreenToClient(&r);
				GridWnd()->ClientToScreen(&rectClip);
				ScreenToClient(&rectClip);
				ValidateRect(r); 
				InvalidateRect(rectClip); 
				HideCaret();
			}
		}

		UpdateWindow();

		// child Controls: spin-buttons, hotspot, combobox btn, ...
		CGXControl::Draw(pDC, rect, nRow, nCol, *m_pStyle, pStandardStyle);

		ExcludeClipRect(rectText);
	}
	else
	// else {
	//     lookup style and draw static:
	//     - edit control with GXDrawTextLikeMultiLineEdit
	// }
	{

		// ------------------ Static Text ---------------------------

		CGXStatic::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
	}
}

void CGXMaskControl::Hide()
{
	// Hides the CEdit without changing the m_bIsActive flag
	// and without invalidating the screen
	if (m_hWnd && IsWindowVisible())
	{
		Grid()->SetIgnoreFocus(TRUE);
		HideCaret();
		MoveWindow0(FALSE);
		ShowWindow(SW_HIDE);
		Grid()->SetIgnoreFocus(FALSE);
	}
}

// Mouse hit
BOOL CGXMaskControl::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	if (m_hWnd)
	{
		// Sets the caret position
		int n = -1;

		n = CalcTextPosUnderPt(pt);

		if (n != -1)
		{
			int nPos = m_pMask->GetCharPos(n);
			n = m_pMask->GetNextDataPos(nPos-1);
			if (n == -1)
				n = m_pMask->GetPrevDataPos(nPos);

			// check to see if the cursor was put after the last piece
			// of data.  if so then we need to put it after the last filled data
			// position or if the whole thing is empty, we need to put it at the
			// first data position.
			int nSel = m_pMask->FindLastFilledDataPos(m_pMask->GetTextLength());

			n = m_pMask->GetEditPos(min(n, nSel));
		}

		if (n != -1 && (Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_CLICKINTEXT) > 0
			|| Grid()->GetParam()->GetActivateCellFlags()&(GX_CAFOCUS_CLICKONCELL|GX_CAFOCUS_SETCURRENT))
		{
			if (IsActive())
				SetSel(n == -1 ? 0 : n, n, FALSE);
			else if (OnStartEditing())
			{
				SetActive(TRUE);
				SetSel(n == -1 ? 0 : n, n, FALSE);
				Refresh();
			}
		}
	}

	// check child buttons
	CGXStatic::LButtonUp(nFlags, pt, nHitState);

	return TRUE;
}

BOOL CGXMaskControl::LButtonDblClk(UINT nFlags, CPoint pt)
{
	if (m_hWnd)
	{
		if (!IsActive() &&
			(Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_DBLCLICKONCELL) > 0
			)
		{
			// Set the caret position
			int n = CalcTextPosUnderPt(pt);

			if (n != -1)
			{
				int nPos = m_pMask->GetCharPos(n);
				n = m_pMask->GetNextDataPos(nPos-1);
				if (n == -1)
					n = m_pMask->GetPrevDataPos(nPos);
			}

			if (IsActive())
				SetSel(n == -1 ? 0 : n, n, FALSE);
			else if (OnStartEditing())
			{
				SetActive(TRUE);
				SetSel(n == -1 ? 0 : n, n, FALSE);
				Refresh();
			}

			// check child buttons
			CGXStatic::LButtonDblClk(nFlags, pt);

			return TRUE;
		}
	}

	return CGXStatic::LButtonDblClk(nFlags, pt);
}

// Keyboard

// called from CGXGridCore when current cell is incative
// (does not have the focus) and before CGXGridCore
// interpretes the key.

BOOL CGXMaskControl::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_hWnd)
		return FALSE;

	BOOL bProcessed = FALSE;

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;

	// Pass all CTRL keys to the grid
	if (!bCtl)
	{
		switch (nChar)
		{
		case VK_DELETE:
			if (Grid()->GetParam()->GetRangeList()->IsEmpty() // no ranges of cells selected
				&& !bShift
				&& !IsReadOnly()        // cell is not readonly
				&& OnDeleteCell()       // OnDeleteCell notification returns TRUE
				&& OnStartEditing())    // OnStartEditing notification returns TRUE
			{
				SetActive(TRUE);

				// Delete text
				SetValue(_T(""));
				SetModify(TRUE);
				OnModifyCell();

				bProcessed = TRUE;
			}
			break;

		case VK_END:
			if (OnStartEditing())
			{
				if (!IsInit())
					Init(m_nRow, m_nCol);
				SetActive(TRUE);

				// position caret
				int nLast = m_pMask->FindLastFilledDataPos(m_pMask->GetTextLength());
				if (nLast != -1)
					SetCharSel(nLast, nLast, FALSE);

				bProcessed = TRUE;
			}
			break;

		case VK_HOME:
			if (OnStartEditing())
			{
				if (!IsInit())
					Init(m_nRow, m_nCol);
				SetActive(TRUE);

				int n = m_pMask->GetEditPos(m_pMask->GetNextDataPos(-1));

				// position caret
				SetSel(n, n, FALSE);

				bProcessed = TRUE;
			}
			break;
		}
	}

	if (bProcessed)
	{
		// eventually destroys and creates CEdit with appropriate window style
		UpdateEditStyle();

		if (!Grid()->ScrollCellInView(m_nRow, m_nCol))
			Refresh();

		return TRUE;
	}

	return CGXStatic::OnGridKeyDown(nChar, nRepCnt, nFlags);

}

BOOL CGXMaskControl::OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_hWnd)
		return FALSE;

	// is this a valid character (no Ctrl-Key)
	CString s = (TCHAR) nChar;

	// pass valid characters as string to OnGridDoubleByteChar
	if (nChar >= 0x020 && nChar != 0x7f)
		return OnGridDoubleByteChar((CString) (TCHAR) nChar, nRepCnt, nFlags);

	// default processing
	return CGXControl::OnGridChar(nChar, nRepCnt, nFlags);
}

BOOL CGXMaskControl::OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nRepCnt, nFlags;

	if (IsReadOnly())
		return FALSE;

	// When several DBCS characters come in, the first char
	// will set the control active and subsequent chars will
	// be handled differently.

	if (IsActive())
	{
		// Get current caret position
		int nStartChar, nEndChar;
		GetSel(nStartChar, nEndChar);

		// Get character position (double byte chars only as one char)
		int nCharPos = m_pMask->GetCharPos(nStartChar);

		// Validate character. Eventually convert it to upper or lowercase
		CString sCharEx = sChar;
		BOOL bValid = m_pMask->IsCharValid(nCharPos, sCharEx);

		// Insert character
		if (bValid)
		{
			m_pMask->PushChar(nCharPos, sCharEx, nEndChar);
			nEndChar = m_pMask->GetEditPos(nEndChar);
			UpdateDisplay();
			SetSel(nEndChar, nEndChar, FALSE);
		}

		return TRUE;
	}
	else
	{
		// discard key if cell is read only
		if (IsReadOnly() || !OnStartEditing())
			return FALSE;

		// Get first valid char position
		int nCharPos = m_pMask->GetNextDataPos(-1);

		// Validate character. Eventually convert it to upper or lowercase
		CString sCharEx = sChar;
		BOOL bValid = m_pMask->IsCharValid(nCharPos, sCharEx);

		if (bValid)
		{
			// Clear out data
			m_pMask->ClearData();

			int nNextChar;
			m_pMask->PushChar(nCharPos, sCharEx, nNextChar);
			nNextChar = m_pMask->GetEditPos(nNextChar);

			SetActive(TRUE);
			UpdateDisplay();
			OnModifyCell();

			SetSel(nNextChar, nNextChar, FALSE);
			Refresh();

#if _MFC_VER >= 0x0300 && _MFC_VER < 0x0420
			// Fix some weird problems with Win32s
			if (GXGetAppData()->bWin31)
			{
				GridWnd()->UpdateWindow();
				SetSel(nNextChar, nNextChar, FALSE);
			}
#endif
		}

		return TRUE;
	}
}

void CGXMaskControl::GetCharSel(int& nPosition, int& nEndPos) const
{
	GetSel(nPosition, nEndPos);

	if (nEndPos != nPosition)
	{
		nPosition = m_pMask->GetCharPos(nPosition);
		nEndPos = m_pMask->GetCharPos(nEndPos);
	}
	else
		nPosition = nEndPos = m_pMask->GetCharPos(nEndPos);
}

void CGXMaskControl::SetCharSel(int nPosition, int nEndPos, BOOL bNoScroll)
{
	int n = m_pMask->GetEditPos(nPosition);
	if (nPosition == nEndPos)
		SetSel(n, n, bNoScroll);
	else
		SetSel(n, m_pMask->GetEditPos(nEndPos), bNoScroll);
}

void CGXMaskControl::SendEvent(UINT nEvent)
{
#if _MFC_VER >= 0x0300
	WPARAM wParam = (WPARAM) MAKELONG(0, nEvent);
	LPARAM lParam = (LPARAM) GetSafeHwnd();
#else
	WPARAM wParam = (WPARAM) 0;
	LPARAM lParam = (LPARAM) MAKELONG(GetSafeHwnd(), nEvent);
#endif
	GetParent()->SendMessage(WM_COMMAND, wParam, lParam);
}

void CGXMaskControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	ASSERT(IsActive());

	BOOL bProcessed = FALSE;
	BOOL bCallDefault = TRUE;

	// TRACE("CGXMaskControl::OnKeyDown nChar = %d\n", nChar);

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	// Pass all CTRL keys to the grid
	if (!bCtl)
	{
		// window text and caret position
		CString s;
		GetWindowText(s);

		int nFirstChar, nLastChar;
		GetCharSel(nFirstChar, nLastChar);

		switch (nChar)
		{

		case VK_BACK:
			if (!IsReadOnly())
			{
				// if we have a multiple selection, handle it differently
				if (nFirstChar != nLastChar)
				{
					m_pMask->PullChar(nLastChar, nFirstChar);

					UpdateDisplay();
					nFirstChar = m_pMask->GetNextDataPos(nFirstChar - 1);
					if (nFirstChar == -1)
						nFirstChar = m_pMask->GetPrevDataPos(-1);

					SetCharSel(nFirstChar, nFirstChar);
					SendEvent(EN_CHANGE);
				}
				else
				{
					int nPrevChar = m_pMask->GetPrevDataPos(nFirstChar);

					// if this is the leftmost data position,
					// then ignore the backspace key
					if (nPrevChar != -1)
					{
						m_pMask->PullChar(nFirstChar, nPrevChar);
						UpdateDisplay();
						SetCharSel(nPrevChar, nPrevChar);
						SendEvent(EN_CHANGE);
					}
				}

				bCallDefault = FALSE;
				bProcessed = TRUE;
			}
			break;

		case VK_DELETE:
			if (!IsReadOnly())
			{
				// if we have a multiple selection, handle it differently
				if (nFirstChar != nLastChar)
				{
					if (bShift)
					{
						OpenClipboard();
						EmptyClipboard();
						CloseClipboard();

						Cut();
					}
					else
						ReplaceSel(_T(""));
				}
				else
				{
					int nNextChar = m_pMask->GetNextDataPos(nFirstChar);

					if (nNextChar != -1)
					{
						// make sure we are not at the end of the mask
						if (nNextChar > nFirstChar && nNextChar <= m_pMask->GetTextLength())
						{
							m_pMask->PullChar(nNextChar, nFirstChar);
							UpdateDisplay();
							SetCharSel(nFirstChar, nFirstChar);
							SendEvent(EN_CHANGE);
						}
					}
					else
					{
						m_pMask->PullChar(nFirstChar + 1, nFirstChar);

						UpdateDisplay();
						SetCharSel(nFirstChar, nFirstChar);
						SendEvent(EN_CHANGE);
					}
				} //else

				bCallDefault = FALSE;
				bProcessed = TRUE;
			}
			break;

		case VK_INSERT:
			if (!IsReadOnly())
			{
				if (bShift)
				{
					Paste();
					bCallDefault = FALSE;
					bProcessed = TRUE;
				}
				else
				{
					// Toggle insert mode
					m_bInsertMode = !m_bInsertMode;
				}
			}
			break;

		case VK_LEFT:
			{
				// test for a multi select
				if (nFirstChar != nLastChar)
				{
					// test for the shift key
					if (!bShift)
					{
						nFirstChar = m_pMask->GetPrevDataPos(nFirstChar+1);
						if (nFirstChar != -1)
							SetCharSel(nFirstChar, nFirstChar);

						bCallDefault = FALSE;
						bProcessed = TRUE;
					}
				}
				else    // single select state
				{
					// test for the shift key
					if (!bShift)
					{
						if (nFirstChar > 0)
						{
							nFirstChar = m_pMask->GetPrevDataPos(nFirstChar);
							if (nFirstChar != -1)
								SetCharSel(nFirstChar, nFirstChar);

							bProcessed = TRUE;
						}

						bCallDefault = FALSE;
					}
				}
				break;
			}

		case VK_RIGHT:
			{
				// test for a multi select
				if (nFirstChar != nLastChar)
				{
					// test for the shift key
					if (!bShift)
					{
						nFirstChar = m_pMask->GetNextDataPos(nLastChar-1);
						if (nFirstChar != -1)
							SetCharSel(nFirstChar, nFirstChar);

						bCallDefault = FALSE;
						bProcessed = TRUE;
					}
				}
				else    // single select state
				{
					// test for the shift key
					if (!bShift)
					{
						if (nFirstChar < m_pMask->GetTextLength())
						{
							nFirstChar = m_pMask->GetNextDataPos(nFirstChar);

							if (nFirstChar == -1)
								nFirstChar = m_pMask->FindLastFilledDataPos(m_pMask->GetTextLength());

							if (nFirstChar != -1)
								SetCharSel(nFirstChar, nFirstChar);

							bProcessed = TRUE;
						}
						bCallDefault = FALSE;
					}
				}
				break;
			}

		case VK_END:
			{
				// test for the shift key
				if (bShift)
				{
					SetCharSel(nFirstChar, m_pMask->GetTextLength());
				}
				else
				{
					int nPos = m_pMask->FindLastFilledDataPos(m_pMask->GetTextLength());
					SetCharSel(nPos, nPos, FALSE);
				}

				bCallDefault = FALSE;
				bProcessed = TRUE;

				break;
			}

		case VK_HOME:
			{
				// test for the shift key
				if (bShift)
				{
					SetCharSel(0, nFirstChar);
				}
				else
				{
					int n = m_pMask->GetNextDataPos(-1);

					// position caret
					SetCharSel(n, n, FALSE);
				}

				bCallDefault = FALSE;
				bProcessed = TRUE;

				break;
			}

		case VK_DOWN:
			{
				// process down arrow if not at last line
				bCallDefault = LineFromChar(LOWORD(GetSel()))+1 < GetLineCount();
				break;
			}

		case VK_UP:
			{
				// process up arrow if not at first line
				bCallDefault = LineFromChar(LOWORD(GetSel())) > 0;
				break;
			}

		case VK_RETURN:
			{
				// does edit control want to handle the RETURN key itsself?
				// Mask edit does not support multiline
				bCallDefault = FALSE;
				break;
			}

		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
		case VK_F5:
		case VK_F6:
		case VK_F7:
		case VK_F8:
		case VK_F9:
		case VK_F10:
		case VK_F11:
		case VK_F12:
		case VK_F13:
		case VK_F14:
		case VK_F15:
		case VK_F16:
		case VK_F17:
		case VK_F18:
		case VK_F19:
		case VK_F20:
		case VK_F21:
		case VK_F22:
		case VK_F23:
		case VK_F24:
		case VK_TAB:
		case VK_NEXT:
		case VK_PRIOR:
		case VK_ESCAPE:
			{
				// let grid handle escape key
				bCallDefault = FALSE;
				break;
			}

		case VK_SHIFT:
		default:
			{
				// let CEdit handle delete and Insert key
				// let CEdit handle all other keys
				bCallDefault = TRUE;
				break;
			}
		}

		if (bCallDefault)
		{
			CEdit::OnKeyDown(nChar, nRepCnt, flags);
			bProcessed = TRUE;
		}

	}

	if (!bProcessed)
		Grid()->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags);
}

void CGXMaskControl::OnChar(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!IsInit()
		|| !IsActive()
		|| IsReadOnly()
		|| (GetStyle() & ES_READONLY)
		|| nChar == 8)
		return;

	BOOL bCallDefault = TRUE;

	// TRACE(_T("CGXMaskControl::OnChar nChar = %d\n"), nChar);

	BOOL bCtl = (GetKeyState(VK_CONTROL) & 0x8000) && !(GetKeyState(VK_MENU) & 0x8000) ;

	// Get the Sel position
	int nFirstChar, nLastChar;
	GetCharSel(nFirstChar, nLastChar);

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	// CTRL+BACKSPACE??

	if (bCtl)
	{
		switch (nChar)
		{
		case 24:    // CTRL+X
			OpenClipboard();
			EmptyClipboard();
			CloseClipboard();

			Cut();
			return;

		case 3:     // CTRL+C
			OpenClipboard();
			EmptyClipboard();
			CloseClipboard();

			Copy();
			return;

		case 22:    // CTRL+V
			Paste();
			return;
		}

		// Pass all other CTRL keys to the grid
	}
	else
	{
		BOOL bChar = FALSE;

		// support for DBCS characters
		CString sChar;
		if (GXGetDoubleByteChar((TCHAR) nChar, sChar, m_bDoubleByteChar, m_nDoubleByteLeadChar))
		{
			if (sChar.IsEmpty())
				return; // leading byte

			// double byte character in sChar
			bChar = TRUE;
		}
		else if (nChar >= 0x020) // this is a normal character
		{
			sChar = (TCHAR) nChar;
			bChar = TRUE;
		}

		// Is it an alphanumeric or double byte character?
		if (bChar)
		{
			if (IsReadOnly())
				return;

			if (nFirstChar != nLastChar)
			{
				// make sure that the starting position is on a valid data field.
				// if nPosition is not on a data field, then advance it
				nFirstChar = m_pMask->GetNextDataPos(nFirstChar-1);

				// if nPosition >= nEndPos, they weren't highlighting a
				// data field at all.  Beep and Get out
				if (nFirstChar >= nLastChar || nFirstChar == -1)
				{
					MessageBeep(MB_ICONEXCLAMATION);
					return;
				}
			}
			else // not in multi-select
			{
				// make sure that the starting position is on a valid data field.
				// if nPosition is not on a data field, then advance it
				nFirstChar = m_pMask->GetNextDataPos(nFirstChar-1);

				// if nPosition = -1 then there wasn't a data position to fill
				if (nFirstChar == -1)
				{
					MessageBeep(MB_ICONEXCLAMATION);
					return;
				}
			}

			// see if it's valid for it's position

			if (m_pMask->IsCharValid(nFirstChar, sChar))
			{
				// if we have a multi-select state, clear the text first
				BOOL bSuccess = TRUE;

				if (m_bInsertMode)
				{
					if (nFirstChar < nLastChar)
						m_pMask->PullChar(nLastChar, nFirstChar);

					bSuccess = m_pMask->PushChar(nFirstChar, sChar, nLastChar);
				}
				else
				{
					if (nFirstChar + 1 < nLastChar)
						m_pMask->PullChar(nLastChar, nFirstChar+1);

					m_pMask->SetDisplayString(sChar, nFirstChar, FALSE);
					nLastChar = nFirstChar+1;
				}

				if (bSuccess)
				{
					UpdateDisplay();
					SendEvent(EN_CHANGE);

					// set the caret to one place past where they were
					SetCharSel(nLastChar, nLastChar, FALSE);
				}
			}
			else
			{
				OnInvalidKeyPressed(sChar);
			}

			bCallDefault = FALSE;
		}
		else if (nChar == 13 || nChar == 10)
		{
			bCallDefault = FALSE;
		}
	}

	if (bCallDefault)
	{
		CEdit::OnChar(nChar, nRepCnt, flags);
		Grid()->ProcessKeys(this, WM_CHAR, nChar, nRepCnt, flags);
	}
}

void CGXMaskControl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags))
	{
		CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
		UpdateEditStyle();
	}
}

void CGXMaskControl::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CEdit::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXMaskControl::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CEdit::OnSysChar(nChar, nRepCnt, nFlags);
}

void CGXMaskControl::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CEdit::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CGXMaskControl::OnCommand(WPARAM wParam, LPARAM lParam)
{
#if _MFC_VER < 0x0300
	UINT nNotification = HIWORD(lParam);
	HWND hCtl = (HWND) LOWORD(lParam);
#else
	UINT nNotification = HIWORD(wParam);
	HWND hCtl = (HWND) lParam;
#endif

	if (hCtl == m_hWnd && IsActive())
	{
		if (nNotification == EN_CHANGE)
			OnModifyCell();
	}

	return CGXControl::OnCommand(wParam, lParam);
}

// Find and Replace
BOOL CGXMaskControl::FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell)
{
	LPCTSTR szValue = NULL;
	LPCTSTR pszFound = NULL;
	LPCTSTR szFind = find.strFindUpper;
		// strFindUpper contains the string to search.
		// if bCase is FALSE (case insensitive search),
		// the text in strFindUpper is converted to uppercase

	// if the active cell contains the text, mark it and return TRUE
	// if not, do a find and return FALSE
	if (nRow == m_nRow && nCol == m_nCol && IsActive())
	{
		CString s;

		int nStart, nEnd;

		GetSel(nStart, nEnd);
		GetWindowText(s);

		// Convert text in s to upper case if we are doing a case insensitive search
		if (!find.bCase)
			s.MakeUpper();

		LPCTSTR pv = szValue = s;

		if (nStart != -1 && nEnd != -1)
			szValue += nStart + (bCurrentPos ? 0 : _tclen(szValue + nStart));

		pszFound = _tcsstr(szValue, szFind);

		if (pszFound != NULL)
		{
			if (bSetCell)
			{
				int nStart = (int)(pszFound - pv);

				// mark the text I have found
				Grid()->ScrollCellInView(nRow, nCol);
				SetSel(nStart, nStart+(int)_tcslen(szFind));
			}
			return TRUE;
		}
	}
	else
	{
		CString s;
		BOOL b;
		if (find.m_pStyle)
		{
			b = GetControlText(s, nRow, nCol, NULL, *find.m_pStyle);
		}
		else
		{
			// request a style object
			CGXStyle* pStyle = Grid()->CreateStyle();

			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);

			b = GetControlText(s, nRow, nCol, NULL, *pStyle);

			// free style object
			Grid()->RecycleStyle(pStyle);
		}

		if (b)
		{
			// Convert text to upper case if we are doing a case insensitive search
			if (!find.bCase)
				s.MakeUpper();

			szValue = s;
		}
		else
			szValue = _T("");

		pszFound = _tcsstr(szValue, szFind);

		if (pszFound != NULL)
		{
			if (bSetCell)
			{
				int nStart = (int)(pszFound - szValue);

				// mark the text I have found
				Grid()->ScrollCellInView(nRow, nCol);
				Grid()->SetCurrentCell(nRow, nCol, GX_SMART|GX_NOSETFOCUS);
				SetActive(TRUE);
				SetSel(nStart, nStart+(int)_tcslen(szFind));
				Refresh();
			}
			return TRUE;
		}
	}

	return FALSE;
}

void CGXMaskControl::ReplaceSel(LPCTSTR pszReplaceText)
{
	if (!IsInit() || IsReadOnly())
		return;

	int nFirstChar = 0, nLastChar = -1;

	GetCharSel(nFirstChar, nLastChar);

	if (IsActive() && nLastChar != -1)
	{
		if (nFirstChar != nLastChar)
		{
			// make sure that the starting position is on a valid data field.
			// if nPosition is not on a data field, then advance it
			nFirstChar = m_pMask->GetNextDataPos(nFirstChar-1);

			// if nPosition >= nEndPos, they weren't highlighting a
			// data field at all.  Beep and Get out
			if (nFirstChar >= nLastChar || nFirstChar == -1)
				return;
		}
		else // not in multi-select
		{
			// make sure that the starting position is on a valid data field.
			// if nPosition is not on a data field, then advance it
			nFirstChar = m_pMask->GetNextDataPos(nFirstChar-1);

			// if nPosition = -1 then there wasn't a data position to fill
			if (nFirstChar == -1)
				return;
		}

		// if we have a multi-select state, clear the text first
		if (nFirstChar < nLastChar)
			m_pMask->PullChar(nLastChar, nFirstChar);

		// First, try to insert the display string together with literals
		int nNextChar = -1;

		if (!m_bForceReplaceData)
			nNextChar = m_pMask->SetDisplayString(pszReplaceText, nFirstChar, TRUE);

		if (nNextChar  == -1 || !m_pMask->IsValidDisplayString())
		{
			// restore old display string
			if (!m_bForceReplaceData)
			{
				CString s;
				GetWindowText(s);
				m_pMask->SetDisplayString(s);
			}

			// if we have a multi-select state, clear the text first
			// if (nFirstChar < nLastChar)
			//	m_pMask->PullChar(nLastChar, nFirstChar);

			// If the replace text did not fit into the cell, try the
			// raw data text
			nNextChar = m_pMask->SetData(pszReplaceText, nFirstChar, TRUE);

			if (nNextChar  == -1 || !m_pMask->IsValidDisplayString())
			{
				// restore old display string
				CString s;
				GetWindowText(s);
				m_pMask->SetDisplayString(s);
			}
		}

		// insert new data (SetData will return -1 if failed)
		if (nNextChar  != -1)
		{
			UpdateDisplay();
			SendEvent(EN_CHANGE);

			// set the caret to one place past where they were
			SetCharSel(nNextChar, nNextChar, FALSE);
		}
	}
	else
		CGXControl::ReplaceSel(pszReplaceText);
}

BOOL CGXMaskControl::ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol)
{
	// find, nRow, nCol;
	// return TRUE if found and replace else return FALSE
	const CString& strFind = find.strFindUpper;
		// strFindUpper contains the string to search.
		// if bCase is FALSE (case insensitive search),
		// the text in strFindUpper is converted to uppercase

	CGXMaskData* pMask;
	CGXMaskData mask;

	CUIntArray posArray;  // store all hits

	// check if the cell is the current active cell
	if (IsInit() && nRow == m_nRow && nCol == m_nCol)
		pMask = m_pMask; // the current cells mask

	else 
	{
		pMask = &mask;

		// this is not the active cell. get the style
		if (find.m_pStyle)
		{
			InitMask(pMask, *find.m_pStyle);
			pMask->SetData(find.m_pStyle->GetValueRef());
		}
		else
		{
			// this is not the active cell. get the style
			CGXStyle* pStyle = Grid()->CreateStyle();

			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
			InitMask(pMask, *pStyle);
			pMask->SetData(pStyle->GetValueRef());

			// free style object
			Grid()->RecycleStyle(pStyle);
		}
	}

	// original display string
	CString strDisplayText;
	pMask->GetDisplayString(strDisplayText);

	// convert strDisplayTextUpper to uppercase for case insensitive search
	CString strDisplayTextUpper = strDisplayText;
	if (!find.bCase)
		strDisplayTextUpper.MakeUpper();

	LPCTSTR pszSearch = strDisplayTextUpper;
	int nIndex = 0;
	LPCTSTR p = 0;

	do
	{
		p = _tcsstr(pszSearch + nIndex, strFind);

		if (p != NULL)
		{
			// add hit to array
			nIndex = (int)(p - pszSearch);
			posArray.Add(nIndex);

			// skip this text now
			nIndex += strFind.GetLength();
		}
	}
	while (p != NULL && *(pszSearch + nIndex) != 0);

	if (posArray.GetSize() > 0)
	{
		int nFirstChar = 0, nLastChar = -1;
		const CString& strReplace = find.strReplace;

		for (int counter = (int)posArray.GetSize() - 1; counter >= 0; counter--)
		{
			// set the value of the first and last chars here
			nFirstChar = pMask->GetCharPos(posArray[counter]);
			nLastChar = pMask->GetCharPos(nFirstChar + strFind.GetLength());

			// execute ReplaceSel() code
			if (nLastChar != -1)
			{
				if (nFirstChar != nLastChar)
				{
					// make sure that the starting position is on a valid data field.
					// if nPosition is not on a data field, then advance it
					nFirstChar = pMask->GetNextDataPos(nFirstChar-1);

					// if nPosition >= nEndPos, they weren't highlighting a
					// data field at all.  Beep and Get out
					if (nFirstChar >= nLastChar || nFirstChar == -1)
						continue;
				}
				else // not in multi-select
				{
					// make sure that the starting position is on a valid data field.
					// if nPosition is not on a data field, then advance it
					nFirstChar = pMask->GetNextDataPos(nFirstChar-1);

					// if nPosition = -1 then there wasn't a data position to fill
					if (nFirstChar == -1)
						continue;
				}

				// if we have a multi-select state, clear the text first
				if (nFirstChar < nLastChar)
					pMask->PullChar(nLastChar, nFirstChar);

				// First, try to insert the display string together with literals
				int nNextChar = -1;

				if (!m_bForceReplaceData)
					nNextChar = pMask->SetDisplayString(strReplace, nFirstChar, TRUE);

				if (nNextChar  == -1 || !pMask->IsValidDisplayString())
				{
					// restore old display string
					if (!m_bForceReplaceData)
					{
						//CString s;
						//GetWindowText(s);
						pMask->SetDisplayString(strDisplayText);
					}

					// if we have a multi-select state, clear the text first
					if (nFirstChar < nLastChar)
						pMask->PullChar(nLastChar, nFirstChar);

					// If the replace text did not fit into the cell, try the
					// raw data text
					nNextChar = pMask->SetData(strReplace, nFirstChar, TRUE);

					if (nNextChar  == -1 || !pMask->IsValidDisplayString())
					{
						// restore old display string
						pMask->SetDisplayString(strDisplayText);
					}
				}
			}
			else
			{
				// replace all data (SetData will return FALSE if failed)
				if (pMask->SetData(strReplace) == -1)
				{
					// restore old display string
					pMask->SetDisplayString(strDisplayText);

				}
			}
		}

		// Store value in grid
		CString strData;
		pMask->GetData(strData);
		Grid()->SetValueRange(CGXRange(nRow, nCol), strData);

		return TRUE;
	}

	// nothing found
	return FALSE;
}

BOOL CGXMaskControl::GetSelectedText(CString& sWindowText)
{
	if (IsActive())
	{
		// Get selected text
		int nStartChar = 0,
			 nEndChar = -1;

		GetSel(nStartChar, nEndChar);
		GetWindowText(sWindowText);

		// if no text is selected use all text
		if (nEndChar == nStartChar)
			return FALSE;   // no text selected

		else
		{
			// if nEndChar is -1 get whole text
			int nLength = (nEndChar == -1) ? GetWindowTextLength() : nEndChar-nStartChar;

			// Copy text to strResult
			sWindowText = sWindowText.Mid(nStartChar, nLength);

			return TRUE;    // text selected
		}
	}
	else
	{
		// No caret visible. Get text which is displayed in the cell
		GetCurrentText(sWindowText);

		return FALSE;   // no text selected
	}
}

// Edit specific

int CGXMaskControl::CalcTextPosUnderPt(CPoint point)
{
	// used to compute textposition after mouseclick

	NeedStyle();
	CRect rect = GetCellRect(m_nRow, m_nCol);

	CString s;
	GetWindowText(s);

	DWORD ntAlign = m_pStyle->GetHorizontalAlignment() | m_pStyle->GetVerticalAlignment();

	ntAlign |= DT_NOPREFIX | DT_SINGLELINE;

	CClientDC dc(GridWnd());

	CFont* pOldFont = Grid()->LoadFont(&dc, *m_pStyle);

	int nHitSel = GXGetMultiLineTextPosUnderPt(
		&dc, s, -1, rect,
		(UINT) ntAlign, point);

	if (pOldFont)
	{
		if ((pOldFont = dc.SelectObject(pOldFont)) != NULL)
			pOldFont->DeleteObject();
	}

	return nHitSel;
}

void CGXMaskControl::SetCellColor(COLORREF rgb)
{
	m_rgbCell = rgb;
}

void CGXMaskControl::SetTextAlign(UINT ntAlign)
{
	m_ntAlign = AlignTAToES(AlignDTToTA(ntAlign));
}

BOOL CGXMaskControl::UpdateEditStyle()
{
	if (m_bUpdateEditStyle || !m_hWnd)
		// semaphor for not recursively re-entering UpdateEditStyle()
		return FALSE;

	// TRACE0("CGXMaskControl: BEGIN UpdateEditStyle()\n");

	int nLine;
	RECT rect;
	GetClientRect(&rect);

	RECT rectNP;
	DWORD dwEditStyle = CalcEditStyle(&rectNP, m_dyHeight);
	BOOL bChanged = m_dwEditStyle != dwEditStyle;

	int ns, ne;
	GetSel(ns, ne);

	if (bChanged)
	{
		m_bUpdateEditStyle = TRUE;

		BOOL bModify   = GetModify();
		BOOL bReadOnly = (BOOL) (GetStyle() & ES_READONLY);

		MapWindowPoints(GridWnd(), &rect);

		CString s;
		GetWindowText(s);

		CFont *pFont = GetFont();

		HideCaret();
		MoveWindow0(FALSE);

		Grid()->SetIgnoreFocus(TRUE);

		DestroyWindow();

		// TRACE0("CGXMaskControl: Destroying and recreating EDIT-Window\n");

		VERIFY(CreateControl(m_dwEditStyle = dwEditStyle, &rect));

#if !defined(_UNIX_) && !defined(_MAC)
		// not supported by Wind/U and Mac
		SetRect(&rectNP);
#endif
		SetFont(pFont);
		SetWindowText(s);
		SetSel(ns, ne, FALSE);
		SetModify(bModify);
		SetReadOnly(bReadOnly);

		m_bUpdateEditStyle = FALSE;
		nLine = LineFromChar(ne);

		HideCaret();
		UpdateWindow();
		ShowCaret();
#if _MFC_VER >= 0x0300
		SendMessage(EM_SCROLLCARET, 0, 0);
#endif

		SetFocus();

		Grid()->SetIgnoreFocus(FALSE);
	}
	else
	{
		nLine = LineFromChar();
#if !defined(_UNIX_) && !defined(_MAC)
		// not supported by Wind/U and Mac
		SetRectNP(&rectNP);
#endif
	}

	int nLast = GetLastVisibleLine(&rect);
	int nFirst = GetFirstVisibleLine();

	// TRACE(_T("CGXMaskControl: FirstVisible=%d,LineFromChar=%d,LastVisible=%d\n"),
	//  nFirst, nLine, nLast);

	if (nLine > nLast || nLine < nFirst)
	{
		HideCaret();

		if (nLine > nLast)
			LineScroll(nLine - nLast);
		else
			LineScroll(nLine - nFirst);
#if _MFC_VER < 0x0300
		SetSel(ns, ne, FALSE);
#else
		SendMessage(EM_SCROLLCARET, 0, 0);
#endif
		UpdateWindow();
		ShowCaret();
	}
	else
	{
#if _MFC_VER >= 0x0300
		SendMessage(EM_SCROLLCARET, 0, 0);
#endif
		;
	}

	// TRACE1("CGXMaskControl: END   UpdateEditStyle() RET %d\n", bChanged);

	return bChanged;
}

int CGXMaskControl::GetLastVisibleLine(LPRECT lprect)
{
	RECT rect;

	if (lprect)
		rect = *lprect;
	else
		GetClientRect(&rect);

	if (m_dyHeight == 0)
	{
		CDC *pDC = GetDC();
		CFont *pOldFont = pDC->SelectObject(GetFont());

		TEXTMETRIC tm;
		pDC->GetTextMetrics(&tm);
		m_dyHeight = tm.tmHeight + tm.tmExternalLeading;
		m_dxMaxCharWidth = tm.tmMaxCharWidth;

		ReleaseDC(pDC);
		if (pOldFont)
			pDC->SelectObject(pOldFont);
	}

	return GetFirstVisibleLine()+max(0, (rect.bottom-rect.top)/m_dyHeight-1);
}

DWORD CGXMaskControl::CalcEditStyle(LPRECT rectNP, int& dyHeight)
{
	// TRACE0("CGXMaskControl: BEGIN CalcEditStyle()\n");

	// figure out edit control style
	DWORD dwStyle   = WS_VISIBLE | WS_CHILD | WS_TABSTOP;
	LONG  ntAlign   = m_bAlwaysLeftJustified ? ES_LEFT : m_ntAlign;

	CRect rect;
	GetClientRect(&rect);

	// Device Context needed
	CDC* pDC = GetDC();

	CFont *pOldFont = NULL;
	CFont* pFont = GetFont();
	if (pFont)
		pOldFont = pDC->SelectObject(pFont);

	CString s;
	GetWindowText(s);

	CSize size = pDC->GetTextExtent(s, s.GetLength());

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	m_dyHeight = tm.tmHeight + tm.tmExternalLeading + 1;
	m_dxMaxCharWidth = tm.tmMaxCharWidth;

	UINT nFormat = DT_NOPREFIX | DT_SINGLELINE;

	// Calculate no of lines needed to display text
	GXGetMultiLineTextBreakCount(pDC, s, -1, rect, nFormat);

	if (pOldFont)
		pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	// ES_MULTILINE | ES_AUTOVSCROLL is needed to display the editwnd
	// with horizontal Alignment
	DWORD dwEditStyle = ES_NOHIDESEL | ES_MULTILINE | ES_AUTOHSCROLL;

	// switch right aligned or centered edit control
	// into a left aligned one, so that autoscrolling
	// works correctly.
	if (size.cx > rect.Width()-m_dxMaxCharWidth)
		ntAlign = ES_LEFT;

	if (rectNP)
		*rectNP = rect;

	rectNP->bottom = max(rectNP->bottom, dyHeight+1);

	dwEditStyle = MAKELONG(((WORD) ntAlign | (WORD) dwEditStyle), HIWORD(dwStyle));

	// TRACE1("CGXMaskControl: END   CalcEditStyle() RET %08lx\n", dwEditStyle);

	return dwEditStyle;
}


void CGXMaskControl::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	CGXControl::OnKillFocus(pNewWnd);
}

UINT CGXMaskControl::OnGetDlgCode()
{
	return CEdit::OnGetDlgCode() | DLGC_WANTTAB | DLGC_WANTARROWS | DLGC_WANTCHARS;
}

BOOL CGXMaskControl::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);

	// Erase Background
	GXPatB(pDC, rect, RGB(255,255,255));
	if (m_pStyle)
		pDC->FillRect(rect, Grid()->LookupOrCreateBrush(m_pStyle->GetInteriorRef()));

	return TRUE;
}

void CGXMaskControl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if (bShow)
		UpdateEditStyle();

	CEdit::OnShowWindow(bShow, nStatus);
}

void CGXMaskControl::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);

	UpdateEditStyle();
}

#if _MFC_VER >= 0x0400
void CGXMaskControl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	pWnd, point;
}
#endif

#define GX_MASKDATA "GX_MASKDATA"

#ifndef _WINDU_SOURCE
#if !defined(_UNICODE)
UINT s_cfMASKDATA = RegisterClipboardFormat(GX_MASKDATA);
#else
UINT s_cfMASKDATA = RegisterClipboardFormat(_T(GX_MASKDATA));
#endif
#else
UINT s_cfMASKDATA = 0xffff;
#endif

// Copy
//
// Copy will only copy data to clipboard if cell is active (has the focus)
// If you also want to support Copy for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

BOOL CGXMaskControl::CanCopy()
{
#ifdef _WINDU_SOURCE
	if( s_cfMASKDATA == 0xffff)
#if !defined(_UNICODE)
		s_cfMASKDATA = RegisterClipboardFormat(GX_MASKDATA);
#else
			s_cfMASKDATA = RegisterClipboardFormat(_T(GX_MASKDATA));
#endif
#endif
	return CGXControl::CanCopy();
}

// Copy()
//
// Called when user calls Edit|Copy and the grid
// has a current cell but no range is selected.
//
// Copy() performs the followin g job:
// a) Copy Plain Data (without literals) to private s_cfMASKDATA clipboard format
// b) Copy Selected Text as formatted in the cell if cell is active
// - or - Standard grid copy if cell is inactive

BOOL CGXMaskControl::Copy()
{
	if (!IsInit() || !Grid()->IsCurrentCell(m_nRow, m_nCol))
		return FALSE;

	BOOL bSuccess = FALSE;

	// Copy Plain Data (without literals) to private s_cfMASKDATA clipboard format

	int nFirstChar = 0, nLastChar = -1;
	if (IsActive())
		GetCharSel(nFirstChar, nLastChar);

	if (nLastChar != nFirstChar)
	{
		CString sData;
		m_pMask->GetData(sData, nFirstChar, max(-1, nLastChar-1));
		if (!sData.IsEmpty())
		{
			CSharedFile clipb (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);

			clipb.Write(sData, sData.GetLength()*sizeof(TCHAR));
			clipb.Write(_T("\0"), sizeof(TCHAR));

			HANDLE hData = clipb.Detach();

			VERIFY(GridWnd()->OpenClipboard());

			HANDLE hResult = SetClipboardData(s_cfMASKDATA, hData);
			bSuccess |= hResult != 0;

			VERIFY(CloseClipboard());
		}
	}

	bSuccess |= CGXControl::Copy();

	return bSuccess;
}

// Cut
//
// Cut will only cut  data to clipboard if cell is active (has the focus)
// If you also want to support Cut for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

BOOL CGXMaskControl::CanCut()
{
#ifdef _WINDU_SOURCE
	if( s_cfMASKDATA == 0xffff)
#if !defined(_UNICODE)
		s_cfMASKDATA = RegisterClipboardFormat(GX_MASKDATA);
#else
			s_cfMASKDATA = RegisterClipboardFormat(_T(GX_MASKDATA));
#endif
#endif
	return CGXControl::CanCut();
}

BOOL CGXMaskControl::Cut()
{
	return CGXControl::Cut();
}

// Paste
//
// Paste will only paste data from clipboard if cell is active (has the focus)
// If you also want to support Paste for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

BOOL CGXMaskControl::CanPaste()
{
	BOOL bCanPaste = FALSE;

#ifdef _WINDU_SOURCE
	if( s_cfMASKDATA == 0xffff)
#if !defined(_UNICODE)
		s_cfMASKDATA = RegisterClipboardFormat(GX_MASKDATA);
#else
			s_cfMASKDATA = RegisterClipboardFormat(_T(GX_MASKDATA));
#endif
#endif
	BOOL bStyles =
		IsClipboardFormatAvailable(GXGetAppData()->m_uiStylesClipboardFormat);

	if ((!bStyles || Grid()->GetParam()->GetRangeList()->GetCount() == 0)
		&& IsInit() && IsActive()
		&& !(m_pStyle->GetIncludeReadOnly() && m_pStyle->GetReadOnly()))
	{
		bCanPaste = IsClipboardFormatAvailable(s_cfMASKDATA);
	}

	return bCanPaste;
}

// Copy() performs the followin g job:
// a) Copy Selected Text as formatted in the cell
// b) Copy Plain Data (without literals) to private s_cfMASKDATA clipboard format
// c) Only if cell is inactive copy the CGXStyle info for the cell

BOOL CGXMaskControl::Paste()
{
	BOOL bStyles =
		IsClipboardFormatAvailable(GXGetAppData()->m_uiStylesClipboardFormat);

	if ((!bStyles || Grid()->GetParam()->GetRangeList()->GetCount() == 0)
		&& IsInit() && IsActive()
		&& !(m_pStyle->GetIncludeReadOnly() && m_pStyle->GetReadOnly()))
	{
		// Check if clipboard is opened
		BOOL bOpen = FALSE;
		if (CWnd::GetOpenClipboardWindow() == NULL)
			bOpen = GridWnd()->OpenClipboard();

		// a) First check for private s_cfMASKDATA clipboard format
		//    for pasting plain data (without literals)

		HGLOBAL handle;

		handle = GetClipboardData(s_cfMASKDATA);

		// b) Check for CF_TEXT and related clipboard formats

		if (handle == 0)
		{
#ifdef _UNICODE
			handle = GetClipboardData(CF_UNICODETEXT);
#else
			handle = GetClipboardData(CF_TEXT);

			if (handle == 0)
				handle = GetClipboardData(CF_OEMTEXT);
#endif
		}
		else
			m_bForceReplaceData = TRUE;

		// insert text into active current cell
		if (handle)
		{
			LPTSTR psz = (LPTSTR) GlobalLock(handle);
			ReplaceSel(psz);
			GlobalUnlock(handle);
		}

		m_bForceReplaceData = FALSE;

		// If we did open the clipboard, we also need to close it again
		if (bOpen)
			CloseClipboard();

		return handle != 0;
	}

	return FALSE;
}

void CGXMaskControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	ASSERT_VALID(this);

	int nOldStartSel, nOldEndSel;
	GetCharSel(nOldStartSel, nOldEndSel);

	// call the base class so the caret gets set right
	CEdit::OnLButtonDown(nFlags, point);

	// check if user clicked into selectect text
	int nStartSel, nEndSel;
	GetCharSel(nStartSel, nEndSel);

	if (nOldStartSel != nOldEndSel
		&& nStartSel == nEndSel
		&& nStartSel >= nOldStartSel
		&& nStartSel <= nOldEndSel)
	{
		// Keep old selection
		SetCharSel(nOldStartSel, nOldEndSel);

		// Start Drag&Drop
		Grid()->DndStartDragDrop(m_nRow, m_nCol);

		// if internal state is still valid
		if (!IsInit() || !IsActive() || !Grid()->IsCurrentCell(m_nRow, m_nCol))
			return;

		// ... continue
		SetCharSel(nStartSel, nEndSel);
	}
}


void CGXMaskControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	CEdit::OnLButtonUp(nFlags, point);

	// check to see if the cursor was put after the last piece
	// of data.  if so then we need to put it after the last filled data
	// position or if the whole thing is empty, we need to put it at the
	// first data position.
	int nStartSel, nEndSel;
	GetCharSel(nStartSel, nEndSel);

	// only do this if there isn't a multi select now.
	if (nStartSel == nEndSel)
	{
		// find the last filled data position to the left
		// we will re-use nEndSel since its original value
		// isn't needed anymore
		nEndSel = m_pMask->FindLastFilledDataPos(nStartSel);

		int nPos = m_pMask->GetNextDataPos(nEndSel-1);
		if (nPos == -1)
			nPos = m_pMask->GetPrevDataPos(nEndSel);
		nEndSel = nPos;

		if (nEndSel != nStartSel)
		{
			// if the new position is different from the current one,
			// set the selection.
			SetCharSel(nEndSel, nEndSel);
		}
	}
}

BOOL CGXMaskControl::OnValidate()
{
	CString sText;

	if (IsActive() && GetModify())
	{
		if (!m_pMask->IsValidDisplayString())
			return FALSE;
	}

	return CGXControl::OnValidate();
}
