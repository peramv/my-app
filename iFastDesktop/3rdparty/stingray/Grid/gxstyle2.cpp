///////////////////////////////////////////////////////////////////////////////
// gxstyles.cpp : implementation of the CGXStyle and supporting classes
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

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSTYLES")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


class CGXStyleCompareSubsetImp: public CGXAbstractStyleCompareSubsetImp
{
public:
	virtual BOOL IsSubset(const CGXStyle* pStyle, const CGXStyle& p);
};

void AFXAPI CGXStyle::ImplementCompareSubset()
{
	if (GXGetAppData()->m_pStyleCompareSubsetImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pStyleCompareSubsetImp = new CGXStyleCompareSubsetImp);
		GXGetAppData()->m_pStyleCompareSubsetImp = new CGXStyleCompareSubsetImp;
	}
}

BOOL CGXStyleCompareSubsetImp::IsSubset(const CGXStyle* pStyle, const CGXStyle& p)
{
	BOOL b = TRUE;

	// HorizontalAlignment
	if (b && p.GetIncludeHorizontalAlignment())
		b &= pStyle->GetIncludeHorizontalAlignment()
			&& pStyle->GetHorizontalAlignment() == p.GetHorizontalAlignment();

	// VerticalAlignment
	if (b && p.GetIncludeVerticalAlignment())
		b &= pStyle->GetIncludeVerticalAlignment()
			&& pStyle->GetVerticalAlignment() == p.GetVerticalAlignment();

	// ReadOnly
	if (b && p.GetIncludeReadOnly())
		b &= pStyle->GetIncludeReadOnly()
			&& pStyle->GetReadOnly() == p.GetReadOnly();

	// FloatCell
	if (b && p.GetIncludeFloatCell())
		b &= pStyle->GetIncludeFloatCell()
			&& pStyle->GetFloatCell() == p.GetFloatCell();

	// FloodCell
	if (b && p.GetIncludeFloodCell())
		b &= pStyle->GetIncludeFloodCell()
			&& pStyle->GetFloodCell() == p.GetFloodCell();

	// MergeCell
	if (b && p.GetIncludeMergeCell())
		b &= pStyle->GetIncludeMergeCell()
			&& pStyle->GetMergeCell() == p.GetMergeCell();

	// Draw3dFrame
	if (b && p.GetIncludeDraw3dFrame())
		b &= pStyle->GetIncludeDraw3dFrame()
			&& pStyle->GetDraw3dFrame() == p.GetDraw3dFrame();

	// MaxLength
	if (b && p.GetIncludeMaxLength())
		b &= pStyle->GetIncludeMaxLength()
			&& pStyle->GetMaxLength() == p.GetMaxLength();

	// Vertical Scrollbar
	if (b && p.GetIncludeVertScrollBar())
		b &= pStyle->GetIncludeVertScrollBar()
			&& pStyle->GetVertScrollBar() == p.GetVertScrollBar();

	// Textcolor
	if (b && p.GetIncludeTextColor())
		b &= pStyle->GetIncludeTextColor()
			&& pStyle->GetTextColorNA() == p.GetTextColorNA();

	// WrapText
	if (b && p.GetIncludeWrapText())
		b &= pStyle->GetIncludeWrapText()
			&& pStyle->GetWrapText() == p.GetWrapText();

	// AutoSize
	if (b && p.GetIncludeAutoSize())
		b &= pStyle->GetIncludeAutoSize()
			&& pStyle->GetAutoSize() == p.GetAutoSize();

	// AllowEnter
	if (b && p.GetIncludeAllowEnter())
		b &= pStyle->GetIncludeAllowEnter()
			&& pStyle->GetAllowEnter() == p.GetAllowEnter();

	// Enabled
	if (b && p.GetIncludeEnabled())
		b &= pStyle->GetIncludeEnabled()
			&& pStyle->GetEnabled() == p.GetEnabled();

	// TriState
	if (b && p.GetIncludeTriState())
		b &= pStyle->GetIncludeTriState()
			&& pStyle->GetTriState() == p.GetTriState();

	// Control
	if (b && p.GetIncludeControl())
		b &= pStyle->GetIncludeControl()
			&& pStyle->GetControl() == p.GetControl();

	// Interior
	if (b && p.GetIncludeInterior())
		b &= pStyle->GetIncludeInterior()
			&& pStyle->GetInterior() == p.GetInterior();

	// Borders
	if (b && p.GetIncludeBorders())
	{
		b &= pStyle->GetIncludeBorders();
		if (b)
		{
			for (int i = 0; i < CGXStyle::nBorders; i++)
			{
				GXBorderType t = (GXBorderType) i;
				if (b && p.GetIncludeBorders(t))
					b &= pStyle->GetIncludeBorders(t)
						&& pStyle->GetBorders(t) == p.GetBorders(t);
			}
		}
	}

	// Font
	if (b && p.GetIncludeFont())
		b &= pStyle->GetIncludeFont()
			&& pStyle->GetFontRef().IsSubSet(p.GetFontRef());

	// Value
	if (b && p.GetIncludeValue())
		b &= pStyle->GetIncludeValue()
			&& pStyle->GetValueRef() == p.GetValueRef();

	// Format
	if (b && p.GetIncludeFormat())
		b &= pStyle->GetIncludeFormat()
			&& pStyle->GetFormat() == p.GetFormat();

	// Places
	if (b && p.GetIncludePlaces())
		b &= pStyle->GetIncludePlaces()
			&& pStyle->GetPlaces() == p.GetPlaces();

	// Base Style
	if (b && p.GetIncludeBaseStyle())
		b &= pStyle->GetIncludeBaseStyle()
			&& pStyle->GetBaseStyle() == p.GetBaseStyle();

	// Value Array
	if (b && p.GetIncludeChoiceList())
	{
		b &= pStyle->GetIncludeChoiceList()
			&& pStyle->GetChoiceListRef() == p.GetChoiceListRef();
	}

	// ItemDataPtr
	if (b && p.GetIncludeItemDataPtr())
	{
		b &= pStyle->GetIncludeItemDataPtr()
			&& pStyle->GetItemDataPtr() == p.GetItemDataPtr();
	}

	// UserAttributs
	if (b && p.GetUserAttributeMap() && !p.GetUserAttributeMap()->IsEmpty())
	{
		b &= pStyle->GetUserAttributeMap() != NULL;

		for (int i = 0; b && i < p.GetUserAttributeMap()->GetSize(); i++)
		{
			CGXAbstractUserAttribute* pValue = (CGXAbstractUserAttribute*) p.GetUserAttributeMap()->GetAt(i);
			CGXAbstractUserAttribute* pThisValue = (CGXAbstractUserAttribute*) pStyle->GetUserAttributeMap()->GetAt(i);

			b &= pThisValue->IsEqual(*pValue);
		}
	} 

	return b;
}

