// SFLCaptionBarEx
//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
#if !defined __SFLCAPTIONBAREX__H__
#define __SFLCAPTIONBAREX__H__

#include "StingrayExportDefs.h"
#include "afxcaptionbar.h"

namespace sflex
{

class SFLCaptionBarEx : public CMFCCaptionBar
{
	FOUNDATIONEX_DECLARE_DYNAMIC(SFLCaptionBarEx)

public:
	FOUNDATIONEX_API SFLCaptionBarEx();
	FOUNDATIONEX_API virtual ~SFLCaptionBarEx();

	// Is the close button removed?
	inline BOOL IsCloseButtonDisabled() { return m_bCloseBtnDisabled; }
	// Disable close button.
	inline void DisableCloseButton() { m_bCloseBtnDisabled = TRUE; Invalidate(); }
	// Enable close button.
	inline void EnableCloseButton() { m_bCloseBtnDisabled = FALSE; Invalidate(); }

	//----------------------//
	// Overrides            //
	//----------------------//

	// Set bitmap with resource ID.
	FOUNDATIONEX_API void SetBitmap(UINT uiBmpResID, COLORREF clrTransparent, BOOL bStretch = FALSE, BarElementAlignment bmpAlignment = ALIGN_RIGHT);
	// Set bitmap with 1 bitmap.
	FOUNDATIONEX_API void SetBitmap(HBITMAP hBitmap, COLORREF clrTransparent, BOOL bStretch = FALSE, BarElementAlignment bmpAlignment = ALIGN_RIGHT);
	// Set bitmap with the option for multiple bitmaps.
	FOUNDATIONEX_API void SetBitmap(HBITMAP* pBitmap, int count, COLORREF clrTransparent, BOOL bStretch = FALSE, BarElementAlignment bmpAlignment = ALIGN_RIGHT);
	// RecalcLayout.
	FOUNDATIONEX_API virtual void RecalcLayout();

protected:
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected:
	// Remove the caption bar close button.
	BOOL m_bCloseBtnDisabled;
};

} // namespace sflex

#endif // __SFLCAPTIONBAREX__H__
