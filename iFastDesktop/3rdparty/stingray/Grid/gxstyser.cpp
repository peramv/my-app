///////////////////////////////////////////////////////////////////////////////
// gxstyser.cpp : Serialization support for CGXStyle 
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

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#if _MFC_VER >= 0x0300
#ifndef _WINNLS_
#include "winnls.h"
#endif
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSTYLES")
#endif

#ifdef _DEBUG
#undef THIS_FILE
#define new DEBUG_NEW
static char THIS_FILE[] = __FILE__;
#endif



// Colors
const DWORD ExcludeAll = 0;
const DWORD IncludeAll = 0xffff;


class CGXStyleSerializeImp: public CGXAbstractStyleSerializeImp
{
public:
	virtual void Serialize(CGXStyle* pStyle, CArchive& ar, const CGXStylesMap* pStylesMap);
	virtual void Serialize(CGXPen& lp, CArchive& ar);
	virtual void Serialize(CGXBrush& lb, CArchive& ar);
	virtual void Serialize(CGXFont* pFont, CArchive &ar);
};

void AFXAPI CGXStyle::ImplementSerialize()
{
	if (GXGetAppData()->m_pStyleSerializeImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pStyleSerializeImp = new CGXStyleSerializeImp);
		GXGetAppData()->m_pStyleSerializeImp = new CGXStyleSerializeImp;
	}
}

void CGXStyleSerializeImp::Serialize(CGXStyle* pStyle, CArchive& ar, const CGXStylesMap* pStylesMap)
{
	// check out, if stylesmap is stored in CArchive::m_pDocument
	// (done in CGXGridParam::Serialize)
	if (pStylesMap == NULL && ar.m_pDocument && ar.m_pDocument->IsKindOf(RUNTIME_CLASS(CGXStylesMap)))
		pStylesMap = (const CGXStylesMap*) ar.m_pDocument;

#ifndef _WIN64
	static const WORD wVersion = 6;
#else	// WIN64
	// For x64 serialization, the high-bit of 'wVersion' is always set. This allows us to differentiate between
	// Win32 and Win64 serialized files.
	static const WORD wVersion = (6 | 0x8000);
#endif	// ndef _WIN64

	WORD wActualVersion = wVersion;

	ASSERT_VALID(pStyle);

	/*if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion > wVersion )
		{
		*/
	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;

		// QA: 32473 - Serialization between Win32/x64
        if( (wActualVersion & 0x7FFF ) > (wVersion & 0x7FFF )) // Need to unset 64-bit flag
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0("Incompatible format while reading CGXStyle" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXStyle object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	if (ar.IsStoring())
	{
		ASSERT_VALID(pStyle);

		DWORD dw = pStyle->stylebits.GetPortable();
		ar << dw;

		if (pStyle->stylebits.horzalign)    ar << pStyle->GetHorizontalAlignment();
		if (pStyle->stylebits.vertalign)    ar << pStyle->GetVerticalAlignment();
		if (pStyle->stylebits.readonly)     ar << (BYTE) pStyle->boolbits.m_bReadOnly;
		if (pStyle->stylebits.control)      ar << (DWORD) pStyle->m_nControl;
		if (pStyle->stylebits.interior)     ar << pStyle->m_lbInterior;
		if (pStyle->stylebits.textcolor)    ar << GXGETCOLOR2(pStyle->boolbits.m_rgbTextColor1, pStyle->boolbits.m_rgbTextColor2);
		if (pStyle->stylebits.wraptext)     ar << (BYTE) pStyle->boolbits.m_bWrapText;
		if (pStyle->stylebits.allowenter)   ar << (BYTE) pStyle->boolbits.m_bAllowEnter;
		if (pStyle->stylebits.font)         ar << pStyle->m_pFont;
		if (pStyle->stylebits.value)        ar << (CString) pStyle->GetValueRef();
		if (pStyle->stylebits.choicelist)   ar << pStyle->m_sChoiceList;
		if (pStyle->stylebits.vertscroll)   ar << (BYTE) pStyle->boolbits.m_bVertScroll;
		if (pStyle->stylebits.maxlength)    ar << pStyle->m_nMaxLength;
		if (pStyle->stylebits.enabled)      ar << (BYTE) pStyle->boolbits.m_bEnabled;
		if (pStyle->stylebits.tristate)     ar << (BYTE) pStyle->boolbits.m_bTriState;
		if (pStyle->stylebits.draw3dframe)  ar << (BYTE) pStyle->boolbits.m_nDraw3dFrame;
		if (pStyle->stylebits.autosize)     ar << (BYTE) pStyle->boolbits.m_bAutoSize;

		if (pStyle->GetIncludeBorders())
		{
			ar << (WORD) 1;
			for (int i = 0; i < CGXStyle::nBorders; i++)
			{
				if (pStyle->GetIncludeBorders((GXBorderType) i))
				{
					ar << (WORD) 1;
					ar << pStyle->GetBordersRef((GXBorderType) i).GetDescription();
				}
				else
					ar << (WORD) 0;
			}
		}
		else
			ar << (WORD) 0;

		if (pStyle->stylebits.basestyle)
		{
			CString sStyleName;
			UINT nResourceID = 0;
			ASSERT(pStylesMap);
			if (pStylesMap)
				sStyleName = pStylesMap->GetStyleName((WORD) pStyle->boolbits.m_wBaseStyleId, nResourceID);
			ar << (DWORD) nResourceID;
			if (nResourceID == 0)
				ar << sStyleName;
		}

		ar << pStyle->m_pmapUserAttributes;
	}
	else
	{
		DWORD dw;
		ar >> dw;
		pStyle->stylebits.SetPortable(dw);

		BYTE b;
		CString s;

		if (pStyle->stylebits.horzalign)    ar >> dw, pStyle->SetHorizontalAlignment(dw);
		if (pStyle->stylebits.vertalign)    ar >> dw, pStyle->SetVerticalAlignment(dw);
		if (pStyle->stylebits.readonly)     ar >> b, pStyle->boolbits.m_bReadOnly = b;
		if (pStyle->stylebits.control)      ar >> dw, pStyle->SetControl((WORD) dw);
		if (pStyle->stylebits.interior)     ar >> pStyle->m_lbInterior;
		if (pStyle->stylebits.textcolor)    ar >> dw, pStyle->SetTextColor(dw);
		if (pStyle->stylebits.wraptext)     ar >> b, pStyle->boolbits.m_bWrapText = b;
		if (pStyle->stylebits.allowenter)   ar >> b, pStyle->boolbits.m_bAllowEnter = b;
		if (pStyle->stylebits.font)			ar >> pStyle->m_pFont;
		if (pStyle->stylebits.value)        ar >> s, pStyle->SetValue(s);
		if (pStyle->stylebits.choicelist)   ar >> pStyle->m_sChoiceList;
		if (pStyle->stylebits.vertscroll)   ar >> b, pStyle->boolbits.m_bVertScroll = b;
		if (pStyle->stylebits.maxlength)    ar >> pStyle->m_nMaxLength;
		if (pStyle->stylebits.enabled)      ar >> b, pStyle->boolbits.m_bEnabled = b;
		if (pStyle->stylebits.tristate)     ar >> b, pStyle->boolbits.m_bTriState = b;
		if (pStyle->stylebits.draw3dframe)  ar >> b, pStyle->boolbits.m_nDraw3dFrame = b;
		if (pStyle->stylebits.autosize)     ar >> b, pStyle->boolbits.m_bAutoSize = b;

		WORD w;
		ar >> w;
		if (w)
		{
			for (int i = 0; i < CGXStyle::nBorders; i++)
			{
				ar >> w;
				if (w)
				{
					CString s;
					ar >> s;
					pStyle->SetBorders((GXBorderType) i, CGXPen(s));
				}
			}
		}

		if (pStyle->stylebits.basestyle)
		{
			ASSERT(pStylesMap);
			DWORD nResourceID;
			CString sStyleName;
			ar >> nResourceID;
			if (nResourceID > 0)
			{
				if (pStylesMap)
					pStyle->SetBaseStyle(pStylesMap->GetBaseStyleId((UINT) nResourceID));
			}
			else
			{
				ar >> sStyleName;
				if (pStylesMap && !sStyleName.IsEmpty())
					pStyle->SetBaseStyle(pStylesMap->GetBaseStyleId(sStyleName));
			}
		}

		if (wActualVersion <= 4)
		{
			if (GXGetAppData()->m_pSerializeOG5CompatibleImp)
				GXGetAppData()->m_pSerializeOG5CompatibleImp->SerializeOG5Map(pStyle, ar);

			else
			{
				TRACE(_T("Warning you tried to load a style object that was written with\n"));
				TRACE(_T("OG 5.0 or earlier. ´Call ImplementSerializeOG5Compatible() from\n"));
				TRACE(_T("the control factory class to enable backward compatibility.\n"));

				AfxThrowArchiveException(CArchiveException::badSchema);
			}
		}
		else
			ar >> pStyle->m_pmapUserAttributes;

		ASSERT_VALID(pStyle);
	}

	if (wActualVersion >= 2)
	{
		if (ar.IsStoring())
		{
			if (pStyle->stylebits.floatcell)     ar << (BYTE) pStyle->boolbits.m_bFloatCell;
			if (pStyle->stylebits.floodcell)     ar << (BYTE) pStyle->boolbits.m_bFloodCell;
			if (pStyle->stylebits.mergecell)     ar << (BYTE) pStyle->boolbits.m_nMergeCell;
		}
		else
		{
			BYTE b;
			if (pStyle->stylebits.floatcell)     ar >> b, pStyle->boolbits.m_bFloatCell = b;
			if (pStyle->stylebits.floodcell)     ar >> b, pStyle->boolbits.m_bFloodCell = b;
			if (pStyle->stylebits.mergecell)     ar >> b, pStyle->boolbits.m_nMergeCell = b;
		}
	}

	if (wActualVersion >= 3)
	{
		// NOTE: It is not supported to serialize m_pItemDataPtr
		// to a disk file, but in certain cases (e.g. Ole Drag&Drop),
		// it makes sense to serialize the pointer to the archive.
		//
		// Be careful!
		// If the style object is loaded from a disk file and
		// m_pItemDataPtr is set, no valid pointer can be restored!

		if (ar.IsStoring())
		{
			if (pStyle->stylebits.itemdataptr)
			{
#ifdef _WIN64
				ar << (ULONGLONG)pStyle->m_pItemDataPtr;
#else	//WIN32
				ar << (DWORD) (LONG) pStyle->m_pItemDataPtr;
#endif	//_WIN64
			}
		}else // Reading
		{
#ifdef _WIN64
			// QA: 32473 - Serialization between Win32/x64
			// m_pItemDataPtr is 32-bits when reading a Win32 grid file. Serializing the pointer into a
			// DWORD ensures grid documents persisted on Win32 can be read on x64. 
			// Native serialization on x64 will always have the high-bit of wVersion set.
			if(wActualVersion & 0x8000) 
			{
				ULONGLONG dw;
				if (pStyle->stylebits.itemdataptr)     ar >> dw, pStyle->m_pItemDataPtr = (void*)dw;
			}
			else	// We are reading a Win32 serialized file.
			{
				DWORD dw;
				if (pStyle->stylebits.itemdataptr)     ar >> dw, pStyle->m_pItemDataPtr = (void*) (SEC_LONG) dw;
			}
#else	//WIN32*/
			 // QA: 32473 - Serialization between Win32/x64
             if(wActualVersion & 0x8000)
             {
                 ULONGLONG dw;
                 if (pStyle->stylebits.itemdataptr)
				 {
					 ar >> dw, pStyle->m_pItemDataPtr = (void*)(DWORD)dw;
				 }
             }else // We are reading a Win32 serialized file.
             {
				DWORD dw;
				if (pStyle->stylebits.itemdataptr)    
				{
					ar >> dw, pStyle->m_pItemDataPtr = (void*) (LONG) dw;
				}
             }

#endif	//_WIN64
		}
	}

	if (ar.IsStoring())
	{
		if (pStyle->stylebits.format)		ar << (BYTE) pStyle->boolbits.m_nFormat;
		if (pStyle->stylebits.places)		ar << (BYTE) pStyle->boolbits.m_nPlaces;
		if (pStyle->stylebits.value)        ar << (BYTE) pStyle->boolbits.m_nValueType;
	}
	else
	{
		BYTE b;
		if (wActualVersion >= 4 && wActualVersion < 6)
		{
			if (pStyle->stylebits.format)
			{
				ar >> b; pStyle->boolbits.m_nFormat = b;
				ar >> b; pStyle->boolbits.m_nPlaces = b;
				pStyle->stylebits.places = 1;
			}

			if (pStyle->stylebits.value)        ar >> b, pStyle->boolbits.m_nValueType = b;
		}
		else if (wActualVersion >= 6)
		{
			if (pStyle->stylebits.format)		ar >> b, pStyle->boolbits.m_nFormat = b;
			if (pStyle->stylebits.places)		ar >> b, pStyle->boolbits.m_nPlaces = b;
			if (pStyle->stylebits.value)        ar >> b, pStyle->boolbits.m_nValueType = b;
		}
	}
}

void CGXStyleSerializeImp::Serialize(CGXPen& lp, CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar 
		<< (DWORD) lp.lopnStyle 
		<< (WORD) lp.lopnWidth 
		<< (WORD) lp.GetInclude() 
		<< GXGETCOLORNA2(lp.lopnColor1, lp.lopnColor2);
	}
	else
	{
		DWORD dw;
		ar >> dw;
		lp.lopnStyle = (UINT) dw;
		WORD us;
		ar >> us;
		lp.lopnWidth = (int) us;
		ar >> us;
		if (!us)
			lp.lopnStyle = GX_PS_DEFAULT;
		COLORREF lopnColor;
		ar  >> lopnColor;

		lp.lopnColor1 = GXCOLOR1(lopnColor);
		lp.lopnColor2 = GXCOLOR2(lopnColor);
	}
}

void CGXStyleSerializeImp::Serialize(CGXBrush& lb, CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar 
		<< (DWORD) lb.lbStyle 
		<< GXGETCOLORNA2(lb.lbColor1, lb.lbColor2) 
		<< (LONG) lb.lbHatch 
		<< (LONG) lb.lbPattern 
		<< GXGETCOLORNA2(lb.lbBkColor1, lb.lbBkColor2);
	}
	else
	{
		DWORD dw;

		ar >> dw;

		lb.lbStyle = (UINT) dw;
		LONG l;
		DWORD lbColor;

		ar  >> lbColor;
		
		lb.lbColor1 = GXCOLOR1(lbColor);
		lb.lbColor2 = GXCOLOR2(lbColor);

		ar >> l;
		
		lb.lbHatch = (int) l;

		ar >> l;
		
		lb.lbPattern = (UINT) l;
		if (lb.lbStyle == BS_PATTERN)
		{
			if (lb.lbPattern >= 0 && lb.lbPattern < (unsigned) _gxnPatternCount)
				lb.lbHatch = (int)(SEC_DWORD) GXGetPatternBitmap(lb.lbPattern)->GetSafeHandle();
			else
				lb.lbStyle = BS_NULL;
		}
		DWORD lbBkColor;

		ar >> lbBkColor;
		
		lb.lbBkColor1 = GXCOLOR1(lbBkColor);
		lb.lbBkColor2 = GXCOLOR2(lbBkColor);
	}
}

#if !defined(_DEBUG) && _MFC_VER < 0x0400
#pragma optimize("", off)
#endif

void CGXStyleSerializeImp::Serialize(CGXFont* pFont, CArchive &ar)
{
	static const WORD wVersion = 2;
	WORD wActualVersion = wVersion;

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion > wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXFont" );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXFont object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	if (ar.IsStoring())
	{
		DWORD dw = 
			0x0001 * pFont->fontbits.italic
			| 0x0002 * pFont->fontbits.underline
			| 0x0004 * pFont->fontbits.strikeout
			| 0x0008 * pFont->fontbits.nItalic
			| 0x0010 * pFont->fontbits.nUnderline
			| 0x0020 * pFont->fontbits.nStrikeOut
			| 0x0040 * pFont->GetIncludeWeight()
			| 0x0080 * pFont->GetIncludeSize()
			| 0x0100 * pFont->GetIncludeOrientation()
			| 0x0200 * pFont->GetIncludeFaceName();

		ar << dw;

		if (pFont->GetIncludeWeight()) ar << (WORD) pFont->GetWeight();
		if (pFont->GetIncludeSize()) ar << (WORD) (pFont->GetSize()*10);
		if (pFont->GetIncludeOrientation()) ar << (WORD) pFont->GetOrientation();
		if (pFont->GetIncludeFaceName())
		{
			CGXFontInfo* pInfo = GXGetFontState()->GetFontInfo(pFont->GetFaceNameId());
			ar << CString(pFont->GetFaceName());
			ar << pInfo->lfPitchAndFamily;
			ar << pInfo->nCharSet;
		}
	}
	else
	{
		if (wActualVersion == 1)
		{
			// old format
			LONG l; BYTE b; DWORD dw; CString strFont;

			LOGFONT lf;
			memset(&lf, 0, sizeof(lf));

			ar >> l; lf.lfHeight = (int)l;
			ar >> l; lf.lfWeight = (int)l;
			ar >> b; lf.lfItalic = (BYTE)b;
			ar >> b; lf.lfUnderline = (BYTE)b;
			ar >> b; lf.lfPitchAndFamily = (BYTE)b;
			ar >> strFont;
			// QA: 31989 - #if Secure Code Cleanup.
			_tcsncpy(lf.lfFaceName, strFont, sizeof(lf.lfFaceName)/sizeof(TCHAR));
			// m_lf.lfFaceName[sizeof(m_lf.lfFaceName)/sizeof(TCHAR) - 1] = _T('\0');
			// pFont->SetFaceName will also initialize lfCharSet
			// pFont->SetFaceName(strFont);

			*pFont = lf;

			ar >> dw; 
			// pFont->fontbits.SetPortable(dw);
			if ((dw & 0x0001) == 0) pFont->SetIncludeWeight(FALSE);
			if ((dw & 0x0002) == 0) pFont->SetIncludeItalic(FALSE);
			if ((dw & 0x0004) == 0) pFont->SetIncludeUnderline(FALSE);
			if ((dw & 0x0008) == 0) pFont->SetIncludeStrikeOut(FALSE);
			if ((dw & 0x0010) == 0) pFont->SetIncludeSize(FALSE);
			if ((dw & 0x0020) == 0) pFont->SetIncludeFaceName(FALSE); else pFont->SetFaceName(strFont);
			if ((dw & 0x0040) == 0) 
				pFont->SetOrientation(0); // not supported in OG 5.0
			else
			{
				ar >> l; pFont->SetOrientation(l);
			}
		}
		else
		{
			// new format
			pFont->Release();

			pFont->fontbits.fontdata = 0;
			
			DWORD dw;
			ar >> dw;
			pFont->fontbits.italic = (dw&0x0001) != 0;
			pFont->fontbits.underline = (dw&0x0002) != 0;
			pFont->fontbits.strikeout = (dw&0x0004) != 0;
			pFont->fontbits.nItalic = (dw&0x0008) != 0;
			pFont->fontbits.nUnderline = (dw&0x0010) != 0;
			pFont->fontbits.nStrikeOut = (dw&0x0020) != 0;

			WORD w;
			if ((dw & 0x0040) != 0)
				ar >> w, pFont->SetWeight((LONG) w);

			if ((dw & 0x0080) != 0)
				ar >> w, pFont->SetSize(w/10.0);

			if ((dw & 0x0100) != 0)
				ar >> w, pFont->SetOrientation((LONG) w);

			if ((dw & 0x0200) != 0)
			{
				CString strFont;
				ar >> strFont;
				BYTE lfPitchAndFamily, nCharSet;
				ar >> lfPitchAndFamily;
				ar >> nCharSet;
				pFont->SetFaceNameId(GXGetFontState()->LookupFontInfo(strFont, lfPitchAndFamily, nCharSet));
			}
		} 
	}
}



