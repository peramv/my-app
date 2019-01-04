///////////////////////////////////////////////////////////////////////////////
// gxxmlser.cpp : XML Grid serialization
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
#include "grid\xmlser\gxxmlrc.h"
#include "grid\xmlser\gxxmlser.h"

#pragma warning(disable: 4311 4312)

// Potential classifications:
// 1) End user interaction flags

//General:
// All formatters' constructor should accept a strElementName arg.
//Implementation
//TODO: While retrieving, m_apapCellStyle could have empty CPtrArray members instead of NULL in it's array.

CGXStylesMap* m_pGlobalStylesMap = NULL;

class CGXStylePtrArrayFTR : public CPtrArrayFTR<CGXStyle, CGXStyleFTR>
{
public:
	CGXStylePtrArrayFTR(CGXStylePtrArray*& pa, LPCTSTR strElementType = SECXMLLoadString(GX_IDS_STYLEPTRARRAY))
		: CPtrArrayFTR<CGXStyle, CGXStyleFTR>((CPtrArray*&)pa, strElementType), m_ptrObj(pa){};

	SEC_XML_DYNCREATE_OBJECT(CGXStylePtrArray)
};

void CGXUserPropertyInfoFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXProperties::UserPropertyInfo*& m_pInfo = m_ptrObj;

	ASSERT(m_pInfo);

	if(ar.IsLoading())
		m_pInfo->pStyle = new CGXStyle();

	ar.Serialize(SECXMLLoadString(GX_IDS_NAME), m_pInfo->sName);
	ar.Serialize(NULL, CGXStyleFTR(m_pInfo->pStyle));
}

void CGXCollMapDWordToLongFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXCollMapDWordToLong*& m_pMap = m_ptrObj;

	ASSERT_VALID(m_pMap);

	if (ar.IsStoring())
	{
		ASSERT(m_pMap->m_pHashTable != NULL);
		if(m_pMap->m_nHashTableSize > 0)
		{
			CString strElemName;
			UINT nElemCount = 0;

			for (UINT nHash = 0; nHash < m_pMap->m_nHashTableSize; nHash++)
			{
				CGXCollMapDWordToLong::CAssoc* pAssoc;
				for (pAssoc = m_pMap->m_pHashTable[nHash]; pAssoc != NULL;
				  pAssoc = pAssoc->pNext)
				{
					// QA: 31989 - #if Secure Code Cleanup.
					_stprintf(strElemName.GetBuffer(12), _T("%s%d"), SECXMLLoadString(GX_IDS_ELEMENT), nElemCount++); strElemName.ReleaseBuffer();
					ar.OpenElement(strElemName);
						ar.Write(SECXMLLoadString(GX_IDS_KEY), pAssoc->key);
						ar.Write(SECXMLLoadString(GX_IDS_VALUE), pAssoc->value);
					ar.CloseElement(strElemName);
				}
			}
		}
	}
	else
	{
		ASSERT(m_pMap);

		int i=0;
		while(TRUE)
		{
			CString strElemName;
			// QA: 31989 - #if Secure Code Cleanup.
			_stprintf(strElemName.GetBuffer(12), _T("%s%d"), SECXMLLoadString(GX_IDS_ELEMENT), i++); strElemName.ReleaseBuffer();

			if(ar.OpenElement(strElemName))
			{
				DWORD newKey;
				LONG newValue;
				ar.Read(SECXMLLoadString(GX_IDS_KEY), newKey);
				ar.Read(SECXMLLoadString(GX_IDS_VALUE), newValue);
				ar.CloseElement(strElemName);
				m_pMap->SetAt(newKey, newValue);
			}
			else
				break;
		}
	}
}

void CGXRangeFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXRange*& m_pRange = m_ptrObj;

	ar.Serialize(SECXMLLoadString(GX_IDS_TOP), m_pRange->top);
	ar.Serialize(SECXMLLoadString(GX_IDS_LEFT), m_pRange->left);
	ar.Serialize(SECXMLLoadString(GX_IDS_BOTTOM), m_pRange->bottom);
	ar.Serialize(SECXMLLoadString(GX_IDS_RIGHT), m_pRange->right);
	
	BYTE b = (BYTE)m_pRange->rtType;
	ar.Serialize(SECXMLLoadString(GX_IDS_TYPE), b);
	if(ar.IsLoading())
		m_pRange->rtType = (CGXRange::RangeType)b;

	ar.Serialize(SECXMLLoadString(GX_IDS_ISVALID), m_pRange->m_bValid);
}

void CGXFontFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXFont*& m_pFont = m_ptrObj;

	if (ar.IsStoring())
	{
		if(m_pFont->fontbits.italic)
			ar.Write(SECXMLLoadString(GX_IDS_ITALIC), m_pFont->fontbits.nItalic);

		if(m_pFont->fontbits.underline)
			ar.Write(SECXMLLoadString(GX_IDS_UNDERLINE), m_pFont->fontbits.nUnderline);

		if(m_pFont->fontbits.strikeout)
			ar.Write(SECXMLLoadString(GX_IDS_STRIKEOUT), m_pFont->fontbits.nStrikeOut);

		if (m_pFont->GetIncludeWeight()) ar.Write(SECXMLLoadString(GX_IDS_WEIGHT), m_pFont->GetWeight());
		if (m_pFont->GetIncludeSize()) ar.Write(SECXMLLoadString(GX_IDS_SIZE), m_pFont->GetSize()*10);
		if (m_pFont->GetIncludeOrientation()) ar.Write(SECXMLLoadString(GX_IDS_ORIENTATION), m_pFont->GetOrientation());
		if (m_pFont->GetIncludeFaceName())
		{
			CGXFontInfo* pInfo = GXGetFontState()->GetFontInfo(m_pFont->GetFaceNameId());
			ar.OpenElement(SECXMLLoadString(GX_IDS_FACENAME));
				ar.Write(SECXMLLoadString(GX_IDS_NAME), m_pFont->GetFaceName());
				ar.Write(SECXMLLoadString(GX_IDS_PITCHANDFAMILY), pInfo->lfPitchAndFamily);
				ar.Write(SECXMLLoadString(GX_IDS_CHARSET), pInfo->nCharSet);
			ar.CloseElement(SECXMLLoadString(GX_IDS_FACENAME));
		}
	}
	else
	{
		UINT nRead;
		if(ar.Read(SECXMLLoadString(GX_IDS_ITALIC), nRead))
		{
			m_pFont->fontbits.italic = 1;
			m_pFont->fontbits.nItalic = nRead;
		}
		else
			m_pFont->fontbits.italic = 0;

		if(ar.Read(SECXMLLoadString(GX_IDS_UNDERLINE), nRead))
		{
			m_pFont->fontbits.underline = 1;
			m_pFont->fontbits.nUnderline = nRead;
		}
		else
			m_pFont->fontbits.underline = 0;

		if(ar.Read(SECXMLLoadString(GX_IDS_STRIKEOUT), nRead))
		{
			m_pFont->fontbits.strikeout = 1;
			m_pFont->fontbits.nStrikeOut = nRead;
		}
		else
			m_pFont->fontbits.strikeout = 0;

		LONG lRead;
		if(ar.Read(SECXMLLoadString(GX_IDS_WEIGHT), lRead))
			m_pFont->SetWeight(lRead);

		if(ar.Read(SECXMLLoadString(GX_IDS_SIZE), lRead))
			m_pFont->SetSize(lRead/10.0);

		if(ar.Read(SECXMLLoadString(GX_IDS_ORIENTATION), lRead))
			m_pFont->SetOrientation(lRead);

		if(ar.OpenElement(SECXMLLoadString(GX_IDS_FACENAME)))
		{
			LPTSTR lpBuff = NULL;
			UINT len = 0;
			ar.Read(SECXMLLoadString(GX_IDS_NAME), lpBuff, len);
			
			BYTE lfPitchAndFamily, nCharSet;
			ar.Read(SECXMLLoadString(GX_IDS_PITCHANDFAMILY), lfPitchAndFamily);
			ar.Read(SECXMLLoadString(GX_IDS_CHARSET), nCharSet);

			if(lpBuff)
			{
				m_pFont->SetFaceNameId(GXGetFontState()->LookupFontInfo(lpBuff, lfPitchAndFamily, nCharSet));
				delete lpBuff;
			}
			ar.CloseElement(SECXMLLoadString(GX_IDS_FACENAME));
		}
	}
}

void CGXBrushFTR::XMLSerialize(SECXMLArchive& ar)
{
	if (ar.IsStoring())
	{
		ar.Write(SECXMLLoadString(GX_IDS_STYLE), (DWORD)m_lb.lbStyle)
			.Write(SECXMLLoadString(GX_IDS_COLOR), GXGETCOLORNA2(m_lb.lbColor1, m_lb.lbColor2))
			.Write(SECXMLLoadString(GX_IDS_HATCH), (LONG)m_lb.lbHatch)
			.Write(SECXMLLoadString(GX_IDS_PATTERN), (LONG)m_lb.lbPattern)
			.Write(SECXMLLoadString(GX_IDS_BGCOLOR), GXGETCOLORNA2(m_lb.lbBkColor1, m_lb.lbBkColor2))
			;
	}
	else
	{
		DWORD dw;
		ar.Read(SECXMLLoadString(GX_IDS_STYLE), dw);
		m_lb.lbStyle = dw;

		DWORD lbColor;

		ar.Read(SECXMLLoadString(GX_IDS_COLOR), lbColor);
		
		m_lb.lbColor1 = GXCOLOR1(lbColor);
		m_lb.lbColor2 = GXCOLOR2(lbColor);

		LONG l;
		ar.Read(SECXMLLoadString(GX_IDS_HATCH), l);
		m_lb.lbHatch = l;
		
		ar.Read(SECXMLLoadString(GX_IDS_PATTERN), l);
		m_lb.lbPattern = l;
		
		if (m_lb.lbStyle == BS_PATTERN)
		{
			if (m_lb.lbPattern >= 0 && m_lb.lbPattern < (unsigned) _gxnPatternCount)
				m_lb.lbHatch = (INT32)GXGetPatternBitmap(m_lb.lbPattern)->GetSafeHandle();
			else
				m_lb.lbStyle = BS_NULL;
		}
		DWORD lbBkColor;

		ar.Read(SECXMLLoadString(GX_IDS_BGCOLOR), lbBkColor);
		
		m_lb.lbBkColor1 = GXCOLOR1(lbBkColor);
		m_lb.lbBkColor2 = GXCOLOR2(lbBkColor);
	}
}

void CGXDataFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXData*& m_data = m_ptrObj;

	ar.Serialize(SECXMLLoadString(GX_IDS_ROWCOUNT), m_data->m_nRows);
	ar.Serialize(SECXMLLoadString(GX_IDS_COLCOUNT), m_data->m_nCols);

	if(ar.IsLoading())
	{
		m_data->m_apapCellStyle.DeleteAll();
		m_data->m_apRowBaseStyle.DeleteAll();
		m_data->m_apColBaseStyle.DeleteAll();
	}

	CPtrArray* pa = &m_data->m_apapCellStyle;
	ar.Serialize(NULL, CPtrArrayFTR<CGXStylePtrArray, CGXStylePtrArrayFTR>(pa, SECXMLLoadString(GX_IDS_CELLSTYLESARRAY)));

	pa = &m_data->m_apRowBaseStyle;
	ar.Serialize(NULL, CPtrArrayFTR<CGXStyle, CGXStyleFTR>(pa, SECXMLLoadString(GX_IDS_ROWBASESTYLESARRAY)));
	pa = &m_data->m_apColBaseStyle;
	ar.Serialize(NULL, CPtrArrayFTR<CGXStyle, CGXStyleFTR>(pa, SECXMLLoadString(GX_IDS_COLBASESTYLESARRAY)));
}

void CGXPrintDeviceFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXPrintDevice*& m_dev = m_ptrObj;

	LPDEVNAMES pDevNames = 0;
	DWORD cbSizeDevNames = 0;

	LPDEVMODE pDevMode = 0;
	DWORD cbSizeDevMode = 0;

	if (ar.IsStoring())
	{
		m_dev->GetDeviceInfo(pDevNames, cbSizeDevNames, pDevMode, cbSizeDevMode);

		// DevNames structure
		if (cbSizeDevNames > 0)
			ar.Write(SECXMLLoadString(GX_IDS_DEVNAMES), (void*)pDevNames, cbSizeDevNames);

		// DevMode structure
		if (cbSizeDevMode > 0)
			ar.Write(SECXMLLoadString(GX_IDS_DEVMODE), (void*)pDevMode, cbSizeDevMode);

		delete pDevNames;
		delete pDevMode;
	}
	else
	{
		// DevNames structure
		TCHAR* lpBuff = NULL;
		UINT nLen = 0;
		if(ar.Read(SECXMLLoadString(GX_IDS_DEVNAMES), lpBuff, nLen) && nLen > 0)
		{
			cbSizeDevNames = nLen;
			pDevNames = (LPDEVNAMES)lpBuff;
		}

		nLen = 0;
		lpBuff = NULL;
		if(ar.Read(SECXMLLoadString(GX_IDS_DEVMODE), lpBuff, nLen) && nLen > 0)
		{
			cbSizeDevMode = nLen;
			pDevMode = (LPDEVMODE)lpBuff;
		}

		// Handles
		m_dev->CreateDeviceHandles((LPDEVNAMES) pDevNames,
			cbSizeDevNames,
			(LPDEVMODE) pDevMode,
			cbSizeDevMode);

		delete pDevNames;
		delete pDevMode;
	}
}

void CGXPropertiesFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXProperties*& m_prop = m_ptrObj;
	// Colors
	CDWordArray* padw = &m_prop->m_ColorArray;
	ar.Serialize(SECXMLLoadString(GX_IDS_COLORARRAY), CDWordArrayFTR(padw));

	if(ar.IsLoading())
		m_prop->m_ColorArray.SetSize(m_prop->m_ColorNameArray.GetSize());

	ar.Serialize(SECXMLLoadString(GX_IDS_VERTLINES), m_prop->m_bDisplayVertLines);
	ar.Serialize(SECXMLLoadString(GX_IDS_HORZ_LINES), m_prop->m_bDisplayHorzLines);
	ar.Serialize(SECXMLLoadString(GX_IDS_BUTTONS_3D), m_prop->m_b3dButtons);
	ar.Serialize(SECXMLLoadString(GX_IDS_MARK_ROWHEADER), m_prop->m_bMarkRowHeader);
	ar.Serialize(SECXMLLoadString(GX_IDS_MARK_COLHEADER), m_prop->m_bMarkColHeader);

	ar.Serialize(SECXMLLoadString(GX_IDS_PROFILE_SECTION), m_prop->m_sSection);
	ar.Serialize(SECXMLLoadString(GX_IDS_ZOOM), m_prop->m_nZoom);

	// Print Settings
	ar.Serialize(SECXMLLoadString(GX_IDS_PRINT_VERTLINES), m_prop->m_bPrintVertLines);
	ar.Serialize(SECXMLLoadString(GX_IDS_PRINT_HORZLINES), m_prop->m_bPrintHorzLines);
	ar.Serialize(SECXMLLoadString(GX_IDS_PAGE_ORDER), m_prop->m_nPageOrder);
	ar.Serialize(SECXMLLoadString(GX_IDS_BLACKANDWHITE), m_prop->m_bBlackWhite);
	ar.Serialize(SECXMLLoadString(GX_IDS_ROWHEADERS), m_prop->m_bRowHeaders);	
	ar.Serialize(SECXMLLoadString(GX_IDS_CENTERVERTICAL), m_prop->m_bCenterVertical);		
	ar.Serialize(SECXMLLoadString(GX_IDS_CENTERHORZ), m_prop->m_bCenterHorizontal);	
	ar.Serialize(SECXMLLoadString(GX_IDS_TOPMARGIN), m_prop->m_nTopMargin);		
	ar.Serialize(SECXMLLoadString(GX_IDS_LEFTMARGIN), m_prop->m_nLeftMargin);		
	ar.Serialize(SECXMLLoadString(GX_IDS_RIGHTMARGIN), m_prop->m_nRightMargin);
	ar.Serialize(SECXMLLoadString(GX_IDS_BOTTOMMARGIN), m_prop->m_nBottomMargin);
	ar.Serialize(SECXMLLoadString(GX_IDS_PRINTFRAME), m_prop->m_bPrintFrame);	


	// Header&Footer
	ar.Serialize(SECXMLLoadString(GX_IDS_HEADERLENGTH), m_prop->m_nDistTop);	
	ar.Serialize(SECXMLLoadString(GX_IDS_FOOTERLENGTH), m_prop->m_nDistBottom);	
	ar.Serialize(SECXMLLoadString(GX_IDS_FIRSTPAGE), m_prop->m_nFirstPage);	

	padw = &m_prop->m_awColBreaks;
	ar.Serialize(SECXMLLoadString(GX_IDS_COLBREAKSARRAY), CDWordArrayFTR(padw));
	padw = &m_prop->m_awRowBreaks;
	ar.Serialize(SECXMLLoadString(GX_IDS_ROWBREAKSARRAY), CDWordArrayFTR(padw));

	
	CGXData* pdata = &m_prop->m_mapDataHeader;
	ar.Serialize(SECXMLLoadString(GX_IDS_HEADERDATA), CGXDataFTR(pdata));
	pdata = &m_prop->m_mapDataFooter;
	ar.Serialize(SECXMLLoadString(GX_IDS_FOOTERDATA), CGXDataFTR(pdata));

	ar.Serialize(SECXMLLoadString(GX_IDS_COLUMNHEADERS), m_prop->m_bColHeaders);

	if(ar.IsLoading())
	{
		// Clear the infomap...
		for( POSITION pos = m_prop->m_UserPropertyInfoMap.GetStartPosition(); pos != NULL; )
		{
			WORD nID;
			CGXProperties::UserPropertyInfo* pInfo;
			m_prop->m_UserPropertyInfoMap.GetNextAssoc( pos, nID, (void*&)pInfo);
			delete pInfo;
		}
		
		m_prop->m_UserPropertyInfoMap.RemoveAll();

	}

	CMapWordToPtr* pmapWtoPtr = &m_prop->m_UserPropertyInfoMap;
	ar.Serialize(NULL, CMapWordToPtrFTR<CGXProperties::UserPropertyInfo, CGXUserPropertyInfoFTR>(pmapWtoPtr, SECXMLLoadString(GX_IDS_USERPROPERTY_INFOMAP)));
}

CString& GetBorderStringFromId(GXBorderType i, CString& strBorder)
{
	switch(i)
	{
	case gxBorderAll:	strBorder = SECXMLLoadString(GX_IDS_ALL);
		break;
	case gxBorderLeft:	strBorder = SECXMLLoadString(GX_IDS_LEFT);
		break;
	case gxBorderRight:	strBorder = SECXMLLoadString(GX_IDS_RIGHT);
		break;
	case gxBorderTop:	strBorder = SECXMLLoadString(GX_IDS_TOP);
		break;
	case gxBorderBottom: strBorder = SECXMLLoadString(GX_IDS_BOTTOM);
		break;
	};
	return strBorder;
}

void CGXStyleFTR::XMLSerialize(SECXMLArchive& ar)
{
	DWORD dw;
	BOOL b;
	CString s;

	CGXStyle*& m_pStyle = m_ptrObj;

	if (ar.IsStoring())
	{
		ASSERT_VALID(m_pStyle);

		dw = m_pStyle->stylebits.GetPortable();
		ar.Write(SECXMLLoadString(GX_IDS_STYLEBITS), dw);
	}
	else
	{
		ar.Read(SECXMLLoadString(GX_IDS_STYLEBITS), dw);
		m_pStyle->stylebits.SetPortable(dw);
	}

	if (m_pStyle->stylebits.interior)     ar.Serialize(SECXMLLoadString(GX_IDS_INTERIORCOLOR), CGXBrushFTR(m_pStyle->m_lbInterior));
	if (m_pStyle->stylebits.font)		  ar.Serialize(NULL, CGXFontFTR(m_pStyle->m_pFont));
	if (m_pStyle->stylebits.choicelist)   
	{
		CString* str = &m_pStyle->m_sChoiceList;
//		ar.Serialize(SECXMLLoadString(GX_IDS_CHOICELIST), CStringXMLCompatibleFTR(str));
		ar.Serialize(SECXMLLoadString(GX_IDS_CHOICELIST), str, 4); // 4 for NODE_CDATA_SECTION
	}
	if (m_pStyle->stylebits.maxlength)    ar.Serialize(SECXMLLoadString(GX_IDS_MAXLENGTH), m_pStyle->m_nMaxLength);

	if (ar.IsStoring())
	{
		if (m_pStyle->stylebits.horzalign)    ar.Write(SECXMLLoadString(GX_IDS_HORZALIGN), m_pStyle->GetHorizontalAlignment());
		if (m_pStyle->stylebits.vertalign)    ar.Write(SECXMLLoadString(GX_IDS_VERTALIGN), m_pStyle->GetVerticalAlignment());
		if (m_pStyle->stylebits.readonly)     ar.Write(SECXMLLoadString(GX_IDS_READONLY), m_pStyle->boolbits.m_bReadOnly);
		if (m_pStyle->stylebits.control)      ar.Write(SECXMLLoadString(GX_IDS_CONTROLID), m_pStyle->m_nControl);
		if (m_pStyle->stylebits.textcolor)    ar.Write(SECXMLLoadString(GX_IDS_TEXTCOLOR), GXGETCOLOR2(m_pStyle->boolbits.m_rgbTextColor1, m_pStyle->boolbits.m_rgbTextColor2));
		if (m_pStyle->stylebits.wraptext)     ar.Write(SECXMLLoadString(GX_IDS_WRAPPED_TEXT), m_pStyle->boolbits.m_bWrapText);
		if (m_pStyle->stylebits.allowenter)   ar.Write(SECXMLLoadString(GX_IDS_ALLOWENTER), m_pStyle->boolbits.m_bAllowEnter);
		if (m_pStyle->stylebits.value)        ar.Write(SECXMLLoadString(GX_IDS_VALUE), (CString) m_pStyle->GetValueRef());
		if (m_pStyle->stylebits.vertscroll)   ar.Write(SECXMLLoadString(GX_IDS_VERTICAL_SCROLL), (BYTE) m_pStyle->boolbits.m_bVertScroll);
		if (m_pStyle->stylebits.enabled)      ar.Write(SECXMLLoadString(GX_IDS_ENABLED), m_pStyle->boolbits.m_bEnabled);
		if (m_pStyle->stylebits.tristate)     ar.Write(SECXMLLoadString(GX_IDS_TRISTATE), m_pStyle->boolbits.m_bTriState);
		if (m_pStyle->stylebits.draw3dframe)  ar.Write(SECXMLLoadString(GX_IDS_DRAW3DFRAME), m_pStyle->boolbits.m_nDraw3dFrame);
		if (m_pStyle->stylebits.autosize)     ar.Write(SECXMLLoadString(GX_IDS_AUTOSIZE), m_pStyle->boolbits.m_bAutoSize);

		if (m_pStyle->GetIncludeBorders())
		{
			ar.OpenElement(SECXMLLoadString(GX_IDS_BORDERS));
			CString strBorder;
			for (int i = 0; i < CGXStyle::nBorders; i++)
			{
				if (m_pStyle->GetIncludeBorders((GXBorderType) i))
					ar.Write(GetBorderStringFromId((GXBorderType)i, strBorder), m_pStyle->GetBordersRef((GXBorderType) i).GetDescription());
			}
			ar.CloseElement(SECXMLLoadString(GX_IDS_BORDERS));
		}

		if (m_pStyle->stylebits.basestyle)
		{
			CString sStyleName;
			UINT nResourceID = 0;
			ASSERT(m_pGlobalStylesMap);
			if (m_pGlobalStylesMap)
				sStyleName = m_pGlobalStylesMap->GetStyleName((WORD) m_pStyle->boolbits.m_wBaseStyleId, nResourceID);
			ar.Write(SECXMLLoadString(GX_IDS_BASESTYLEID), nResourceID);
			if (nResourceID == 0)
				ar.Write(SECXMLLoadString(GX_IDS_BASESTYLENAME), sStyleName);
		}

		if(m_pStyle->m_pmapUserAttributes)
		{
			CObArray* paOb = m_pStyle->m_pmapUserAttributes;
			ar.Write(SECXMLLoadString(GX_IDS_USER_ATTRIBUTES), CObArrayFTR(paOb));
		}
	
		if (m_pStyle->stylebits.floatcell)     ar.Write(SECXMLLoadString(GX_IDS_FLOAT_CELL), m_pStyle->boolbits.m_bFloatCell);
		if (m_pStyle->stylebits.floodcell)     ar.Write(SECXMLLoadString(GX_IDS_FLOOD_CELL), m_pStyle->boolbits.m_bFloodCell);
		if (m_pStyle->stylebits.mergecell)     ar.Write(SECXMLLoadString(GX_IDS_MERGE_CELL), m_pStyle->boolbits.m_nMergeCell);

		if (m_pStyle->stylebits.format)		ar.Write(SECXMLLoadString(GX_IDS_FORMAT_ID), m_pStyle->boolbits.m_nFormat);
		if (m_pStyle->stylebits.places)		ar.Write(SECXMLLoadString(GX_IDS_PLACES), m_pStyle->boolbits.m_nPlaces);
		if (m_pStyle->stylebits.value)        ar.Write(SECXMLLoadString(GX_IDS_VALUETYPE), m_pStyle->boolbits.m_nValueType);
	}
	else
	{
		if (m_pStyle->stylebits.horzalign)    ar.Read(SECXMLLoadString(GX_IDS_HORZALIGN), dw), m_pStyle->SetHorizontalAlignment(dw);
		if (m_pStyle->stylebits.vertalign)    ar.Read(SECXMLLoadString(GX_IDS_VERTALIGN), dw), m_pStyle->SetVerticalAlignment(dw);
		if (m_pStyle->stylebits.readonly)     ar.Serialize(SECXMLLoadString(GX_IDS_READONLY), b), m_pStyle->boolbits.m_bReadOnly = b;
		if (m_pStyle->stylebits.control)      ar.Serialize(SECXMLLoadString(GX_IDS_CONTROLID), dw), m_pStyle->SetControl((WORD) dw);
		if (m_pStyle->stylebits.textcolor)    ar.Serialize(SECXMLLoadString(GX_IDS_TEXTCOLOR), dw), m_pStyle->SetTextColor(dw);
		if (m_pStyle->stylebits.wraptext)     ar.Serialize(SECXMLLoadString(GX_IDS_WRAPPED_TEXT), b), m_pStyle->boolbits.m_bWrapText = b;
		if (m_pStyle->stylebits.allowenter)   ar.Serialize(SECXMLLoadString(GX_IDS_ALLOWENTER), b), m_pStyle->boolbits.m_bAllowEnter = b;
		if (m_pStyle->stylebits.value)        {ar.Serialize(SECXMLLoadString(GX_IDS_VALUE), s); m_pStyle->SetValue(s);}
		if (m_pStyle->stylebits.vertscroll)   ar.Serialize(SECXMLLoadString(GX_IDS_VERTICAL_SCROLL), b), m_pStyle->boolbits.m_bVertScroll = b;
		if (m_pStyle->stylebits.enabled)      ar.Serialize(SECXMLLoadString(GX_IDS_ENABLED), b), m_pStyle->boolbits.m_bEnabled = b;
		if (m_pStyle->stylebits.tristate)     ar.Serialize(SECXMLLoadString(GX_IDS_TRISTATE), b), m_pStyle->boolbits.m_bTriState = b;
		if (m_pStyle->stylebits.draw3dframe)  ar.Serialize(SECXMLLoadString(GX_IDS_DRAW3DFRAME), b), m_pStyle->boolbits.m_nDraw3dFrame = b;
		if (m_pStyle->stylebits.autosize)     ar.Serialize(SECXMLLoadString(GX_IDS_AUTOSIZE), b), m_pStyle->boolbits.m_bAutoSize = b;

		if(ar.OpenElement(SECXMLLoadString(GX_IDS_BORDERS)))
		{
			CString strBorder, strDesc;
			for (int i = 0; i < CGXStyle::nBorders; i++)
			{
				ar.Read(GetBorderStringFromId((GXBorderType)i, strBorder), strDesc);
				if(!strDesc.IsEmpty())
					m_pStyle->SetBorders((GXBorderType) i, CGXPen(strDesc));
				strBorder.Empty();
				strDesc.Empty();
			}
			ar.CloseElement(SECXMLLoadString(GX_IDS_BORDERS));
		}

		if (m_pStyle->stylebits.basestyle)
		{
			UINT nResourceID = 0;
			ar.Read(SECXMLLoadString(GX_IDS_BASESTYLEID), nResourceID);
			if(nResourceID > 0)
				m_pStyle->SetBaseStyle(m_pGlobalStylesMap->GetBaseStyleId((UINT) nResourceID));
			else
			{
				CString sStyleName;
				ar.Read(SECXMLLoadString(GX_IDS_BASESTYLENAME), sStyleName);
				if (!sStyleName.IsEmpty())
					m_pStyle->SetBaseStyle(m_pGlobalStylesMap->GetBaseStyleId(sStyleName));
			}
		}

		CObArray* pMap = new CGXUserAttributeMap();
		if(ar.Read(SECXMLLoadString(GX_IDS_USER_ATTRIBUTES), CObArrayFTR(pMap)))
			m_pStyle->m_pmapUserAttributes = (CGXUserAttributeMap*)pMap;
		else 
			delete pMap;

		if (m_pStyle->stylebits.floatcell)     ar.Read(SECXMLLoadString(GX_IDS_FLOAT_CELL), b), m_pStyle->boolbits.m_bFloatCell = b;
		if (m_pStyle->stylebits.floodcell)     ar.Read(SECXMLLoadString(GX_IDS_FLOOD_CELL), b), m_pStyle->boolbits.m_bFloodCell = b;
		if (m_pStyle->stylebits.mergecell)     ar.Read(SECXMLLoadString(GX_IDS_MERGE_CELL), b), m_pStyle->boolbits.m_nMergeCell = b;

		if (m_pStyle->stylebits.format)		ar.Read(SECXMLLoadString(GX_IDS_FORMAT_ID), b),  m_pStyle->boolbits.m_nFormat = b;
		if (m_pStyle->stylebits.places)		ar.Read(SECXMLLoadString(GX_IDS_PLACES), b), m_pStyle->boolbits.m_nPlaces = b;
		if (m_pStyle->stylebits.value)        ar.Read(SECXMLLoadString(GX_IDS_VALUETYPE), b), m_pStyle->boolbits.m_nValueType = b;

	}
}

void CGXStylesMapFTR::XMLSerialize(SECXMLArchive& ar)
{
	int i=0;

	CGXStylesMap*& pStylesMap = m_ptrObj;

	if(ar.IsLoading())
	{
		pStylesMap->FreeStylesMap();
		pStylesMap->FreeControlMap();
	}

	// Control names
	CMapWordToPtr* pMap = &pStylesMap->m_ControlNameMap;
	ar.Serialize(NULL, CMapWordToPtrFTR<CString, CString*>(pMap, SECXMLLoadString(GX_IDS_CONTROLNAMES)));

	// Base Styles
	CMapStringToPtr* pmapSToP = &pStylesMap->m_mswNameId;
	ar.Serialize(NULL, CMapStringToPtrFTR<WORD, LONG&>(pmapSToP, SECXMLLoadString(GX_IDS_BASESTYLENAMES)));

	// User Attribute Info Map
	pMap = &pStylesMap->m_UserAttrInfoMap;
	ar.Serialize(NULL, CMapWordToPtrFTR<CGXProperties::UserPropertyInfo, CGXUserPropertyInfoFTR>(pMap, _T("UserAttributeInfoMap")));
	
	if(ar.IsStoring())
	{
		ar.Write(SECXMLLoadString(GX_IDS_PROFILE_SECTION), pStylesMap->m_sSection);

		ar.OpenElement(SECXMLLoadString(GX_IDS_BASE_STYLES_INFO));
		ar.Write(SECXMLLoadString(GX_IDS_COUNT), (WORD) pStylesMap->m_mwpIdInfo.GetCount());

		if (pStylesMap->m_mwpIdInfo.GetCount() > 0)
		{
			// BaseStyleInfo
			CString strElemName;
			i=0;
			WORD wStyleId;
			CGXStylesMap::BaseStyleInfo* pSrcInfo;
			POSITION pos = pStylesMap->m_mwpIdInfo.GetStartPosition();
			while (pos)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_stprintf(strElemName.GetBuffer(20), _T("%s%d"), SECXMLLoadString(GX_IDS_BASE_STYLE_INFO), i++);

				strElemName.ReleaseBuffer();

				pStylesMap->m_mwpIdInfo.GetNextAssoc(pos, wStyleId, (void*&) pSrcInfo);
				ar.OpenElement(strElemName);
					ar.Write(SECXMLLoadString(GX_IDS_STYLEID), wStyleId);
					ar.Write(SECXMLLoadString(GX_IDS_RESOURCEID), (DWORD) pSrcInfo->nResourceID);
					ar.Write(SECXMLLoadString(GX_IDS_NAME), pSrcInfo->sName);
					ar.Write(SECXMLLoadString(GX_IDS_SYSTEM), (BYTE) pSrcInfo->bSystem);
					ar.Write(NULL, CGXStyleFTR(pSrcInfo->pStyle));
				ar.CloseElement(strElemName);
			}
		}
		ar.CloseElement(SECXMLLoadString(GX_IDS_BASE_STYLES_INFO));

		ar.Write(SECXMLLoadString(GX_IDS_LASTID), pStylesMap->m_nLastId);

	}
	else
	{
		ar.Read(SECXMLLoadString(GX_IDS_PROFILE_SECTION), pStylesMap->m_sSection);

		// Base Styles Info
		if(	ar.OpenElement(SECXMLLoadString(GX_IDS_BASE_STYLES_INFO)))
		{
			WORD count;
			ar.Read(SECXMLLoadString(GX_IDS_COUNT), count);

			// BaseStyleInfo
			CString strElemName;
			int i=0;
			BYTE byte;
			while (i < count)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_stprintf(strElemName.GetBuffer(20), _T("%s%d"), SECXMLLoadString(GX_IDS_BASE_STYLE_INFO), i++);
				strElemName.ReleaseBuffer();
				CGXStylesMap::BaseStyleInfo* pInfo = new CGXStylesMap::BaseStyleInfo();

				ar.OpenElement(strElemName);
					ar.Read(SECXMLLoadString(GX_IDS_STYLEID), pInfo->nID);
					ar.Read(SECXMLLoadString(GX_IDS_RESOURCEID), pInfo->nResourceID);
					ar.Read(SECXMLLoadString(GX_IDS_NAME), pInfo->sName);
					ar.Read(SECXMLLoadString(GX_IDS_SYSTEM), byte); pInfo->bSystem = (BOOL) byte;
					pInfo->pStyle = (CGXStyle*) pStylesMap->m_pStyleClass->CreateObject();
					ar.Read(NULL, CGXStyleFTR(pInfo->pStyle));

					if(pInfo->nResourceID > 0)
					{
						if (!pInfo->sName.LoadString(pInfo->nResourceID))
						{
							// resource string not found 
							pInfo->sName.Format(_T("%s%u"), SECXMLLoadString(GX_IDS_STYLE), pInfo->nResourceID);
						}
				
						pStylesMap->m_mpwResourceId.SetAt((void*) (LONG32)pInfo->nResourceID, pInfo->nID);
					}
				pStylesMap->m_mswNameId.SetAt(pInfo->sName, (void*) (LONG32)pInfo->nID);
				pStylesMap->m_mwpIdInfo.SetAt(pInfo->nID, pInfo);

				ar.CloseElement(strElemName);
			}
			ar.CloseElement(SECXMLLoadString(GX_IDS_BASE_STYLES_INFO));
		}

		ar.Read(SECXMLLoadString(GX_IDS_LASTID), pStylesMap->m_nLastId);

		pStylesMap->m_wStyleStandard = pStylesMap->GetBaseStyleId(GX_IDS_STYLE_STANDARD);
		pStylesMap->m_wStyleColHeader = pStylesMap->GetBaseStyleId(GX_IDS_STYLE_COLHEADER);
		pStylesMap->m_wStyleRowHeader = pStylesMap->GetBaseStyleId(GX_IDS_STYLE_ROWHEADER);
	}
}

void CGXGridParamFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXGridParam*& m_pParam = m_ptrObj;

	ar.Serialize(SECXMLLoadString(GX_IDS_THUMB_TRACKING_BOOL), m_pParam->m_bThumbTrack);
	ar.Serialize(SECXMLLoadString(GX_IDS_TABNAME_EDITABLE_BOOL), m_pParam->m_bNeedChangeTab);
	ar.Serialize(SECXMLLoadString(GX_IDS_GRID_READONLY_BOOL), m_pParam->m_bReadOnly);
	ar.Serialize(SECXMLLoadString(GX_IDS_UNDO_ENABLED_BOOL), m_pParam->m_bUndoEnabled);
	ar.Serialize(SECXMLLoadString(GX_IDS_NUMBERED_ROW_HEADERS_BOOL), m_pParam->m_bNumberedRowHeaders);
	ar.Serialize(SECXMLLoadString(GX_IDS_NUMBERED_COL_HEADERS_BOOL), m_pParam->m_bNumberedColHeaders);
	ar.Serialize(SECXMLLoadString(GX_IDS_ENABLEMOVECOLS_BOOL), m_pParam->m_bAllowSelDragCols);
	ar.Serialize(SECXMLLoadString(GX_IDS_ENABLEMOVEROWS_BOOL), m_pParam->m_bAllowSelDragRows);

	ar.Serialize(SECXMLLoadString(GX_IDS_EATFMCOA_BOOL), m_pParam->m_bEatFirstMouseClick);
	ar.Serialize(SECXMLLoadString(GX_IDS_TRANSPARENT_BG_BOOL), m_pParam->m_bTransparentBackground);
	ar.Serialize(SECXMLLoadString(GX_IDS_LOCKREADONLYCELLS_BOOL), m_pParam->m_bLockReadOnly);
	ar.Serialize(SECXMLLoadString(GX_IDS_SMART_RESIZE), m_pParam->m_bSmartResize);

	ar.Serialize(SECXMLLoadString(GX_IDS_SELECTION_FLAGS), m_pParam->m_wAllowSelection);
	ar.Serialize(SECXMLLoadString(GX_IDS_ROW_HEIGHT_TRACKING_FLAGS), m_pParam->m_wAllowTrackRowHeight);
	ar.Serialize(SECXMLLoadString(GX_IDS_COL_WIDTH_TRACKING_FLAGS),  m_pParam->m_wAllowTrackColWidth);
	ar.Serialize(SECXMLLoadString(GX_IDS_FROZEN_ROWS_COUNT), m_pParam->m_nFrozenRows);
	ar.Serialize(SECXMLLoadString(GX_IDS_FROZEN_COLS_COUNT), m_pParam->m_nFrozenCols);
	ar.Serialize(SECXMLLoadString(GX_IDS_DEFAULT_CELL_WIDTH), m_pParam->m_nDefaultWidth);
	ar.Serialize(SECXMLLoadString(GX_IDS_DEFAULT_CELL_HEIGHT), m_pParam->m_nDefaultHeight);
	ar.Serialize(SECXMLLoadString(GX_IDS_TAB_SHEET_NAME), m_pParam->m_sSheetName);

	ar.Serialize(SECXMLLoadString(GX_IDS_CELL_ACTIVATION_FLAGS), m_pParam->m_wActivateCell);
	ar.Serialize(SECXMLLoadString(GX_IDS_CURRENTCELLFRAME_FLAGS), m_pParam->m_nHideCurrentCell);
	ar.Serialize(SECXMLLoadString(GX_IDS_MIN_ROWHEIGHT_ON_TRACKING),  m_pParam->m_nMinTrackRowHeight);
	ar.Serialize(SECXMLLoadString(GX_IDS_MIN_COLWIDTH_ON_TRACKING),  m_pParam->m_nMinTrackColWidth);

	ar.Serialize(SECXMLLoadString(GX_IDS_DRAWING_ORDER), m_pParam->m_nDrawRowOrder);

	ar.Serialize(SECXMLLoadString(GX_IDS_HEADER_ROWSCOUNT), m_pParam->m_nHeaderRows);
	ar.Serialize(SECXMLLoadString(GX_IDS_HEADER_COLSCOUNT), m_pParam->m_nHeaderCols);

	CPtrList* pl = &m_pParam->m_SelRects;
	ar.Serialize(SECXMLLoadString(GX_IDS_SELECTION_LIST), CPtrListFTR<CGXRange, CGXRangeFTR>(pl));
	pl = &m_pParam->m_CoveredCellsList;
	ar.Serialize(SECXMLLoadString(GX_IDS_COVEREDCELLS_LIST), CPtrListFTR<CGXRange, CGXRangeFTR>(pl));

	if (!ar.IsStoring())
		m_pParam->UpdateCoveredCellsList();

	CGXMapDWordToLong* pRowHeights = &m_pParam->m_RowHeights;
	CGXMapDWordToLong* pColWidths = &m_pParam->m_ColWidths;
	ar.Serialize(SECXMLLoadString(GX_IDS_ROWHEIGHTS), CGXCollMapDWordToLongFTR((CGXCollMapDWordToLong*&)pRowHeights));
	ar.Serialize(SECXMLLoadString(GX_IDS_COLUMNWIDTHS), CGXCollMapDWordToLongFTR((CGXCollMapDWordToLong*&)pColWidths));

	CByteArray* pab = &m_pParam->m_abRowHidden;
	ar.Serialize(SECXMLLoadString(GX_IDS_HIDDEN_ROWARRAY), CByteArrayFTR(pab));
	pab = &m_pParam->m_abColHidden;
	ar.Serialize(SECXMLLoadString(GX_IDS_HIDDEN_COLARRAY), CByteArrayFTR(pab));

	ar.Serialize(SECXMLLoadString(GX_IDS_EXCELLIKE_SCROLL_BOOL), m_pParam->m_bScrollLikeExcel);

	ar.Serialize(SECXMLLoadString(GX_IDS_SYNCCURRENTCELL_BOOL), m_pParam->m_bSyncCurrentCell);
	ar.Serialize(SECXMLLoadString(GX_IDS_INITIALIZED), m_pParam->m_bIsInit);

	if(ar.OpenElement(SECXMLLoadString(GX_IDS_FROZENCOLS_UNDO_INFO)))
	{
		ar.Serialize(SECXMLLoadString(GX_IDS_FROM), m_pParam->m_nUndoFreezeFromCol);   // additional information
		ar.Serialize(SECXMLLoadString(GX_IDS_TO), m_pParam->m_nUndoFreezeToCol);     // for "Unfreeze" columns
		ar.Serialize(SECXMLLoadString(GX_IDS_DEST), m_pParam->m_nUndoFreezeDestCol);
		ar.CloseElement(SECXMLLoadString(GX_IDS_FROZENCOLS_UNDO_INFO));
	}

	ar.Serialize(SECXMLLoadString(GX_IDS_SPECIAL_MODE), m_pParam->m_nSpecialMode);   // special mode

	ar.Serialize(SECXMLLoadString(GX_IDS_DRAW_WYSIWYG_BOOL), m_pParam->m_bDrawWYSIWYG);

	ar.Serialize(SECXMLLoadString(GX_IDS_ENTER_KEYACTION), m_pParam->m_nEnterKeyAction);
	ar.Serialize(SECXMLLoadString(GX_IDS_UNDO_LIMIT), m_pParam->m_dwUndoLimit);

	ar.Serialize(SECXMLLoadString(GX_IDS_SORT_COLS_ON_DBLCLK), m_pParam->m_bSortColsOnDblClk);
	ar.Serialize(SECXMLLoadString(GX_IDS_SORT_ROWS_ON_DBLCLK), m_pParam->m_bSortRowsOnDblClk);
	ar.Serialize(SECXMLLoadString(GX_IDS_EXCEL_LIKE_CURRENT_CELL), m_pParam->m_bExcelLikeCurrentCell);
	ar.Serialize(SECXMLLoadString(GX_IDS_EXCEL_LIKE_SELECTION_FRAME), m_pParam->m_bExcelLikeSelectionFrame);
	ar.Serialize(SECXMLLoadString(GX_IDS_NEWGRIDLINEMODE), m_pParam->m_bNewGridLineMode);

	ar.Serialize(SECXMLLoadString(GX_IDS_FLOATCELLSMODE), m_pParam->m_wFloatCellsMode);

	CObArray* paOb;
	if(ar.IsStoring() && m_pParam->m_pDelayedDispFloatCells)
	{
		paOb = &m_pParam->m_pDelayedDispFloatCells->m_argDelayed;
		ar.Write(SECXMLLoadString(GX_IDS_FLOATCELLSDELAYEVAL), CObArrayFTR(paOb));
	}
	else if(ar.IsLoading() && ar.IsElementAvailable(SECXMLLoadString(GX_IDS_FLOATCELLSDELAYEVAL)))
	{
		m_pParam->m_pDelayedDispFloatCells = new CGXDelayedRangePool;
		paOb = &m_pParam->m_pDelayedDispFloatCells->m_argDelayed;
		ar.Read(SECXMLLoadString(GX_IDS_FLOATCELLSDELAYEVAL), CObArrayFTR(paOb));
	}

	BOOL bSer = FALSE;
	if(ar.IsStoring() && m_pParam->m_pDispFloatCells)
		bSer = TRUE;
	else if(ar.IsLoading() && ar.IsElementAvailable(SECXMLLoadString(GX_IDS_FLOATCELLSONDISPLAY)))
	{
		m_pParam->m_pDispFloatCells = new CGXSpanCellPool();
		bSer = TRUE;
	}

	CPtrArray* ppa;
	if(bSer && ar.OpenElement(SECXMLLoadString(GX_IDS_FLOATCELLSONDISPLAY)))
	{
		ppa = &m_pParam->m_pDispFloatCells->m_SpanRows;
		ar.Serialize(SECXMLLoadString(GX_IDS_ROWS), CPtrArrayFTR<CDWordArray, CDWordArrayFTR>(ppa));
		ppa = &m_pParam->m_pDispFloatCells->m_SpanCols;
		ar.Serialize(SECXMLLoadString(GX_IDS_COLS), CPtrArrayFTR<CDWordArray, CDWordArrayFTR>(ppa));
		ar.CloseElement(SECXMLLoadString(GX_IDS_FLOATCELLSONDISPLAY));
	}

	ar.Serialize(SECXMLLoadString(GX_IDS_MERGE_CELLS_MODE), m_pParam->m_wMergeCellsMode);
	
	if(ar.IsStoring() && m_pParam->m_pDelayedMergeCells)
	{
		paOb = &m_pParam->m_pDelayedMergeCells->m_argDelayed;
		ar.Write(SECXMLLoadString(GX_IDS_MERGE_CELLS_DELAYEVAL), CObArrayFTR(paOb));
	}
	else if(ar.IsLoading() && ar.IsElementAvailable(SECXMLLoadString(GX_IDS_MERGE_CELLS_DELAYEVAL)))
	{
		m_pParam->m_pDelayedMergeCells = new CGXDelayedRangePool;
		paOb = &m_pParam->m_pDelayedMergeCells->m_argDelayed;
		ar.Read(SECXMLLoadString(GX_IDS_MERGE_CELLS_DELAYEVAL), CObArrayFTR(paOb));
	}

	if(ar.OpenElement(SECXMLLoadString(GX_IDS_MERGE_CELLS)))
	{
		bSer = FALSE;
		if(ar.IsStoring() && m_pParam->m_pHorzMergeCells)
			bSer = TRUE;
		else if(ar.IsLoading() && ar.IsElementAvailable(SECXMLLoadString(GX_IDS_HORZ_CELLS)))
		{
			m_pParam->m_pHorzMergeCells = new CGXSpanCellPool();
			bSer = TRUE;
		}
		if(bSer && ar.OpenElement(SECXMLLoadString(GX_IDS_HORZ_CELLS)))
		{
			ppa = &m_pParam->m_pHorzMergeCells->m_SpanRows;
			ar.Serialize(SECXMLLoadString(GX_IDS_ROWS), CPtrArrayFTR<CDWordArray, CDWordArrayFTR>(ppa));
			ppa = &m_pParam->m_pHorzMergeCells->m_SpanCols;
			ar.Serialize(SECXMLLoadString(GX_IDS_COLS), CPtrArrayFTR<CDWordArray, CDWordArrayFTR>(ppa));
			ar.CloseElement(SECXMLLoadString(GX_IDS_HORZ_CELLS));
		}

		bSer = FALSE;
		if(ar.IsStoring() && m_pParam->m_pVertMergeCells)
			bSer = TRUE;
		else if(ar.IsLoading() && ar.IsElementAvailable(SECXMLLoadString(GX_IDS_VERT_CELLS)))
		{
			m_pParam->m_pVertMergeCells = new CGXSpanCellPool();
			bSer = TRUE;
		}
		if(bSer && ar.OpenElement(SECXMLLoadString(GX_IDS_VERT_CELLS)))
		{
			ppa = &m_pParam->m_pVertMergeCells->m_SpanRows;
			ar.Serialize(SECXMLLoadString(GX_IDS_ROWS), CPtrArrayFTR<CDWordArray, CDWordArrayFTR>(ppa));
			ppa = &m_pParam->m_pVertMergeCells->m_SpanCols;
			ar.Serialize(SECXMLLoadString(GX_IDS_COLS), CPtrArrayFTR<CDWordArray, CDWordArrayFTR>(ppa));
			ar.CloseElement(SECXMLLoadString(GX_IDS_VERT_CELLS));
		}
		ar.CloseElement(SECXMLLoadString(GX_IDS_MERGE_CELLS));
	}

	ar.Serialize(SECXMLLoadString(GX_IDS_GRID_LINE_STYLE), m_pParam->m_nGridLineStyle);

	ar.Serialize(SECXMLLoadString(GX_IDS_DIRECT_COPY_PASTE), m_pParam->m_bDirectCopyPaste);
	ar.Serialize(SECXMLLoadString(GX_IDS_DIRECT_CUT_PASTE), m_pParam->m_bDirectCutPaste);
	ar.Serialize(SECXMLLoadString(GX_IDS_DIRECT_DRAG_DROP), m_pParam->m_bDirectDragDrop);
		
	ar.Serialize(SECXMLLoadString(GX_IDS_DISPLAYEXPRESSION), m_pParam->m_nDisplayExpression);

	ar.Serialize(SECXMLLoadString(GX_IDS_EXCELLIKE_HEADERS), m_pParam->m_bExcelLikeHeaders);

//		ar.Serialize(_T("DataAvailable"), m_pParam->m_bOwnData);
//		ar.Serialize(_T("PrintDeviceInfoAvailable"), m_pParam->m_bOwnPD);
//		ar.Serialize(_T("GridPropertiesAvailable"), m_pParam->m_bOwnProperties);
//		ar.Serialize(_T("StylesMapAvailable"), m_pParam->m_bOwnStylesMap);

	if(ar.IsStoring())
	{
		m_pGlobalStylesMap = m_pParam->GetStylesMap();

		if (m_pParam->m_bOwnStylesMap)
			ar.Write(NULL, CGXStylesMapFTR(m_pParam->m_pStylesMap));

		if (m_pParam->m_bOwnData)
			ar.Write(NULL, CGXDataFTR(m_pParam->m_pData));

		if (m_pParam->m_bOwnProperties)
			ar.Write(NULL, CGXPropertiesFTR(m_pParam->m_pProperties));

		if (m_pParam->m_bOwnPD)
			ar.Write(NULL, CGXPrintDeviceFTR(m_pParam->m_pPD));

		ASSERT_VALID(m_pParam);
	}
	else
	{
		if(ar.Read(NULL, CGXStylesMapFTR(m_pParam->m_pStylesMap)))
			m_pParam->m_bOwnStylesMap = TRUE;
		else
			m_pParam->m_bOwnStylesMap = FALSE;

		m_pGlobalStylesMap = m_pParam->GetStylesMap();

		if(ar.Read(NULL, CGXDataFTR(m_pParam->m_pData)))
			m_pParam->m_bOwnData = TRUE;
		else
			m_pParam->m_bOwnData = FALSE;

		if(ar.Read(NULL, CGXPropertiesFTR(m_pParam->m_pProperties)))
			m_pParam->m_bOwnProperties = TRUE;
		else
			m_pParam->m_bOwnProperties = FALSE;

		if(ar.Read(NULL, CGXPrintDeviceFTR(m_pParam->m_pPD)))
			m_pParam->m_bOwnPD = TRUE;
		else
			m_pParam->m_bOwnPD = FALSE;

	}
}

DEFINE_SEC_XMLFORMATTERMAP(CGXAbstractUserAttributeFTR)

void CGXAbstractUserAttributeFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXAbstractUserAttribute*& m_pUA = m_ptrObj;
	ar.Serialize(SECXMLLoadString(GX_IDS_VALUE), m_pUA->m_strValueCache);
	ar.Serialize(SECXMLLoadString(GX_IDS_ID), m_pUA->m_nId);
}

DEFINE_SEC_XMLFORMATTERMAP(CGXUserAttributeFTR)

void CGXUserAttributeFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXUserAttribute*& m_pUA = m_ptrObj;

	if(ar.IsStoring())
	{
		ar.Write(SECXMLLoadString(GX_IDS_TYPE), (BYTE)m_pUA->m_vtType);
		if (m_pUA->m_vtType != CGXUserAttribute::vtString && m_pUA->m_vtType != CGXUserAttribute::vtShortString)
		{
			__int64 i64Val = m_pUA->m_value.b8Value;
			ar.Write(SECXMLLoadString(GX_IDS_VALUE_LWORD),(int)i64Val);
			i64Val = i64Val >> 32;
			ar.Write(SECXMLLoadString(GX_IDS_VALUE_HWORD),(int)i64Val);
		}
		else
			ar.Write(SECXMLLoadString(GX_IDS_VALUE), m_pUA->GetValue());
	}
	else
	{
		BYTE b;
		ar.Read(SECXMLLoadString(GX_IDS_TYPE), b);
		m_pUA->m_vtType = (CGXUserAttribute::ValueType)b;

		if (m_pUA->m_vtType != CGXUserAttribute::vtString && m_pUA->m_vtType != CGXUserAttribute::vtShortString)
		{
			__int64 i64Val; 
			int iVal;

			ar.Read(SECXMLLoadString(GX_IDS_VALUE_HWORD),(int)iVal);
			i64Val = iVal;
			i64Val = i64Val << 32;
			ar.Read(SECXMLLoadString(GX_IDS_VALUE_LWORD),(int)iVal);
			i64Val |= iVal;

			m_pUA->m_value.b8Value = i64Val;
		}
		else
		{
			CString s;
			ar.Read(SECXMLLoadString(GX_IDS_VALUE), s);
			if (s.GetLength() <= 8/sizeof(TCHAR))
			{
				m_pUA->m_vtType = CGXUserAttribute::vtShortString;
				// QA: 31989 - #if Secure Code Cleanup.
				_tcsncpy(m_pUA->m_value.szShortString, s, 8/sizeof(TCHAR));
			}
			else
			{
				m_pUA->m_vtType = CGXUserAttribute::vtString;
				m_pUA->m_value.pszValue = new TCHAR[s.GetLength()+1];
				// QA: 31989 - #if Secure Code Cleanup.
				_tcscpy(m_pUA->m_value.pszValue, s);
			}
		}

	}
	ar.Serialize(SECXMLLoadString(GX_IDS_ID), m_pUA->m_nId);
}

DEFINE_SEC_XMLFORMATTERMAP(CGXEllipseUserAttributeFTR)
void CGXEllipseUserAttributeFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXEllipseUserAttribute*& m_pUA = m_ptrObj;

	ar.Serialize(SECXMLLoadString(GX_IDS_VALUE), (int&)m_pUA->m_gxEllipseType);
	ar.Serialize(SECXMLLoadString(GX_IDS_ID), m_pUA->m_nId);
}

DEFINE_SEC_XMLFORMATTERMAP(CGXOleVarUserAttributeFTR)
void CGXOleVarUserAttributeFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXOleVarUserAttribute*& m_pUA = m_ptrObj;

	if(ar.IsStoring() && m_pUA->m_pOleVar)
		ar.Write(SECXMLLoadString(GX_IDS_VALUE), (DWORD)m_pUA->m_pOleVar);
	else if(ar.IsLoading())
		ar.Read(SECXMLLoadString(GX_IDS_VALUE), (DWORD&)m_pUA->m_pOleVar);

	ar.Serialize(SECXMLLoadString(GX_IDS_ID), m_pUA->m_nId);
}

DEFINE_SEC_XMLFORMATTERMAP(CGXDelayedRangeFTR)
void CGXDelayedRangeFTR::XMLSerialize(SECXMLArchive& ar)
{
	CGXDelayedRange*& m_pDelayedRange = m_ptrObj;

	CGXRange* pRange = &(m_pDelayedRange->m_range);
	ar.Serialize(NULL, CGXRangeFTR(pRange));

	CDWordArray* paDw = &m_pDelayedRange->m_awFirstRow;
	ar.Serialize(SECXMLLoadString(GX_IDS_FIRSTROW), CDWordArrayFTR(paDw));
	paDw = &m_pDelayedRange->m_awLastRow;
	ar.Serialize(SECXMLLoadString(GX_IDS_LASTROW), CDWordArrayFTR(paDw));

}

void CStringXMLCompatibleFTR::XMLSerialize(SECXMLArchive& ar)
{
	CString*& pString = m_ptrObj;

	if(ar.IsStoring())
	{
		CString strXMLComp = *pString;
		// replace escape sequences with XML compatible chars
		// for ex: \r is replaced with $R
		// $ becomes our escape char, so replacing $s with $$s
		strXMLComp.Replace(_T("$"), _T("$$"));

		for(int i = 0; i < m_strOrig.GetLength(); i++)
		{
			char orig = static_cast<char>(m_strOrig[i]);
			char repl = static_cast<char>(m_strWrite[i]);
			strXMLComp.Replace(CString(orig), _T("$") + CString(repl));
		}
		ar.Write(SECXMLLoadString(GX_IDS_STRING), strXMLComp);
	}
	else
	{
		if(ar.Read(SECXMLLoadString(GX_IDS_STRING), *pString))
		{
			// First replace all $$s with "#^*"
			pString->Replace(_T("$$"), _T("#^*"));	

			// Replace $Xs with \Xs
			for(int i = 0; i < m_strOrig.GetLength(); i++)
			{
				CString strOld(_T("$"));
				strOld += m_strWrite[i];
				pString->Replace(strOld, CString(m_strOrig[i]));
			}

			pString->Replace(_T("#^*"), _T("$"));
		}
	}
}

/*
void CInt64FTR::XMLSerialize(SECXMLArchive& ar)
{
	if(ar.IsStoring())
	{
		int i;
		i = i >> 2;
		m_iVal = m_iVal >> 16;
	}
}
*/