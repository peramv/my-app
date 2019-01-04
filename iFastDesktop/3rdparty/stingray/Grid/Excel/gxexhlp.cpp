///////////////////////////////////////////////////////////////////////////////
// gxexhlp.cpp
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

#include "grid\gxexhlp.h"

#include "grid\gxexdef.h"

#pragma warning(disable: 4244)

void _gxExWriteWord(BYTE* buffer, WORD w)
{
	*buffer++ = LOBYTE(w);
	*buffer = HIBYTE(w);
}

void _gxExWriteDWord(BYTE* buffer, DWORD dw)
{
	*((DWORD*)buffer)=dw;
}	

void _gxExWriteByte(BYTE* buffer, BYTE b)
{
	*buffer = b;
}

void _gxExWriteBuffer(BYTE* buffer, const BYTE* bufferData, ULONG nLength)
{
	memcpy(buffer, bufferData, nLength);
}

#pragma warning(push)
#pragma warning(disable: 4244)
// Sets or clears the zero based nth bit
void _gxExSetBit(WORD& w, UINT nBitPos, BOOL nBitval)
{
	ASSERT(nBitPos < 16);
	
	WORD wClear = 0x0001;
	wClear = wClear << nBitPos;
	wClear = ~(wClear);

	w = w&wClear;

	WORD wMask = (nBitval) ? 0x0001:0;	
	wMask = wMask << nBitPos;
	w = w|wMask;
}


// does not clear. only sets with OR

WORD _gxExCalcMask(WORD wBitval, UINT nBitStartPos)
{
	WORD wMask = wBitval;
	wMask = wMask << nBitStartPos; 
	return wMask;
}
#pragma warning (pop) // 4244

void _gxExSetBitEx(WORD& w, UINT nBitStartPos,WORD wBitval)
{
	ASSERT(nBitStartPos < 16);
	
	ASSERT(wBitval <= 0xFFFF);

	WORD wMask = _gxExCalcMask(wBitval, nBitStartPos);
	
	w = w|wMask;
}


DWORD _gxExCalcDWMask(DWORD dwBitval, UINT nBitStartPos)
{
	DWORD dwMask = dwBitval;
	dwMask = dwMask << nBitStartPos; 
	return dwMask;
}

void _gxExSetDWBitEx(DWORD& dw, UINT nBitStartPos, DWORD dwBitval)
{
	ASSERT(nBitStartPos < 32);
	
	ASSERT(dwBitval <= 0xFFFFFFFF);

	DWORD dwMask = _gxExCalcDWMask(dwBitval, nBitStartPos);
	
	dw = dw|dwMask;
}


void _gxExWriteDouble(BYTE* pszBuffer, double d)
{
	BYTE* p = (BYTE*)&d;
	
	TRACE1("%x\n", p[0]); 
	TRACE1("%x\n", p[1]);
	TRACE1("%x\n", p[2]);
	TRACE1("%x\n", p[3]);
	TRACE1("%x\n", p[4]);
	TRACE1("%x\n", p[5]);
	TRACE1("%x\n", p[6]);
	TRACE1("%x\n", p[7]);

	pszBuffer[0] = p[0]; 
	pszBuffer[1] = p[1];
	pszBuffer[2] = p[2];
	pszBuffer[3] = p[3];
	pszBuffer[4] = p[4];
	pszBuffer[5] = p[5];
	pszBuffer[6] = p[6];
	pszBuffer[7] = p[7];
}

// GXEXWRITEDATA helper data structure

GXEXWRITEDATA::GXEXWRITEDATA(DWORD dword)
{
	vt = gxexDword;
	dw = dword;
	nLength = 4;
}
	
GXEXWRITEDATA::GXEXWRITEDATA(WORD word)
{
	vt = gxexWord;
	w = word;
	nLength = 2;
}
	
GXEXWRITEDATA::GXEXWRITEDATA(BYTE byte)
{
	vt = gxexByte;
	by = byte;
	nLength = 1;
}


GXEXWRITEDATA::GXEXWRITEDATA(double d)
{
	vt = gxexDouble;
	db = d;
	nLength = 8;
}	

GXEXWRITEDATA::GXEXWRITEDATA(const BYTE* pbyte, UINT length)
{
	vt = gxexpByte;
	pby = pbyte;
	nLength = length;
}

GXEXWRITEDATA::GXEXWRITEDATA()
{
	vt = gxexEnd;
}

// simple helper function that writes and offsets the buffer as required

BOOL _gxExWrite(GXEXWRITEDATA* wr, BYTE* pszBuffer)
{
	while(wr != NULL && wr->vt != GXEXWRITEDATA::gxexEnd)
	{
		switch(wr->vt)
		{	
		case GXEXWRITEDATA::gxexDword:
			_gxExWriteDWord(pszBuffer, wr->dw);
			pszBuffer+=4;
			break;
		case GXEXWRITEDATA::gxexWord:
			_gxExWriteWord(pszBuffer, wr->w);
			pszBuffer+=2;
			break;
		case GXEXWRITEDATA::gxexpByte:
			_gxExWriteBuffer(pszBuffer, wr->pby, wr->nLength);
			pszBuffer+=wr->nLength;
			break;
		case GXEXWRITEDATA::gxexByte:
			_gxExWriteByte(pszBuffer, wr->by);		
			pszBuffer+=1;
			break;
		case GXEXWRITEDATA::gxexDouble:
			_gxExWriteDouble(pszBuffer, wr->db);		
			pszBuffer+=8;
			break;
		default:
			ASSERT(0);
			return FALSE;
		}

		wr++;
	}

	return TRUE;
}

void __gxexmpSt::Cleanup()
{
	if(by != NULL)
		delete by;
}

// class to store index of stored style in the XF table
CGXExStyleMap::CGXExStyleMap()
{

}

CGXExStyleMap::~CGXExStyleMap()
{
	POSITION pos = GetStartPosition();

	__gxexmpSt* pM = NULL;
	DWORD dw(0);
	while(pos != NULL)
	{
		GetNextAssoc(pos, dw, pM);
		
		if(pM != NULL)
		{
			pM->Cleanup();
			delete pM;
			pM = NULL;
		}
	}

}

DWORD CGXExStyleMap::GetDWordFromRowCol(ROWCOL nRow, ROWCOL nCol) const
{
	ASSERT(nCol <=  65535 && nRow <=  65535);
	
	DWORD dw = nRow | (nCol << 16);
	
	return dw;
}

DWORD CGXExStyleMap::IsXFPresent(const BYTE* by)
{
	POSITION pos = GetStartPosition();

	__gxexmpSt* pM = NULL;
	DWORD dw(0);
	while(pos != NULL)
	{
		GetNextAssoc(pos, dw, pM);
		
		if(pM != NULL)
		{
			if(pM->by && (!memcmp(pM->by, by, GXEX_SIZEOF_XF - GX_EX_FIXEDHEADER)) && pM->uival > 0x10)
				return pM->uival;
		}
	}

	return 0xFFFF;
}

UINT CGXExStyleMap::GetIndexRowCol(ROWCOL nRow, ROWCOL nCol)
{
	DWORD dw = GetDWordFromRowCol(nRow, nCol);
	__gxexmpSt* pM = 0;
	
	if(Lookup(dw, pM) == FALSE)
		return 0;
	
	return pM->uival;
}
	

void CGXExStyleMap::SetIndexRowCol(ROWCOL nRow, ROWCOL nCol, UINT nIndex, const BYTE* pb)
{
	__gxexmpSt* pM = new __gxexmpSt;

	pM->uival = nIndex;
	
	if(pb != NULL)
	{
		pM->by = new BYTE[GXEX_SIZEOF_XF - GX_EX_FIXEDHEADER];
	
		memcpy(pM->by, pb, GXEX_SIZEOF_XF - GX_EX_FIXEDHEADER);
	}
	else
		pM->by = 0;

	DWORD dw = GetDWordFromRowCol(nRow, nCol);
	TRACE1("XF INDEX USED %x\n", dw);
	SetAt(dw, pM);
}


// for the base styles
// class to store index of stored style in the XF table
CGXExStyleIDMap::CGXExStyleIDMap()
{

}

CGXExStyleIDMap::~CGXExStyleIDMap()
{

}

UINT CGXExStyleIDMap::GetIndexID(DWORD nID)
{
	DWORD dw = nID;
	UINT nRetval(0);
	
	if(Lookup(dw, nRetval) == FALSE)
		return 0;
	
	return nRetval;
}
	
void CGXExStyleIDMap::SetIndexID(DWORD nID, UINT nIndex)
{
	DWORD dw = nID;
	UINT nRetval(0);
	
	if(Lookup(dw, nRetval) == TRUE)
		return;

	SetAt(nID, nIndex);
}


// shared string table (UNICODE string handler) helpers
WCHAR* _gxexExpandToUnicode(BYTE* pByte, UINT nCount)
{
	WCHAR* pszWchar = NULL;
	if(pByte == NULL)
	{
		pszWchar = new WCHAR[1];
		*pszWchar = L'\0';
		
	}
	else
	{
		pszWchar = new WCHAR[nCount+1];
		for (UINT nC(0); nC < nCount; nC++)
		{
			pszWchar[nC] = pByte[nC]; 
		}
		
		pszWchar[nCount] = L'\0';
	}

	return pszWchar;
}
