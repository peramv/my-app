///////////////////////////////////////////////////////////////////////////////
// MvcBufferedWrapper.h : Declaration of MvcBufferedWrapper_T
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author:       Dean Hallman
// Description:  Declaration of MvcBufferedWrapper_T interface.
//

// @doc MvcBufferedWrapper_T
//
// MvcBufferedWrapper_T class

#ifndef __COMPAT_MVCBUFFEREDWRAPPER_H__
#define __COMPAT_MVCBUFFEREDWRAPPER_H__

// Header Includes
#ifndef __COMPAT_MVCWRAPPER_H__
#include "Foundation\Compatibility\MVC\MvcWrapper.h"
#endif

//
// MVC Extension DLL
// Initialize declaration context
//
#ifdef _MVCDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    MVC_DATAEXT
#endif //_MVCDLL

//@doc MvcBufferedWrapper_T
//@mdata BOOL | MvcBufferedWrapper_T | m_bEnableBuffering | Turns screen buffering on or off
//@xref <c MvcController>

//@doc MvcBufferedWrapper_T
//@mdata CDC* | MvcBufferedWrapper_T | m_pBufferDC | Memory DC for offscreen buffer
//@xref <c MvcController>

//@doc MvcBufferedWrapper_T
//@mdata CBitmap* | MvcBufferedWrapper_T | m_pBufferBmp | Bitmap that is selected into offscreen DC
//@xref <c MvcController>

//@doc MvcBufferedWrapper_T
//@mdata CPalette* | MvcBufferedWrapper_T | m_pBufferPal | Palette used for offscreen buffer
//@xref <c MvcController>

//@doc MvcBufferedWrapper_T
//@mdata HBITMAP | MvcBufferedWrapper_T | m_hPrevBufferBmp | For restoring buffer DC
//@xref <c MvcController>

//@doc MvcBufferedWrapper_T
//@mdata HPALETTE | MvcBufferedWrapper_T | m_hPrevBufferPal | For restoring buffer DC
//@xref <c MvcController>

//@doc MvcBufferedWrapper_T
//@mdata int | MvcBufferedWrapper_T | m_nBufPadding | Extra width and height added to buffer to reduce reallocation.
//@xref <c MvcController>

//@doc MvcBufferedWrapper_T
//@mdata CRect | MvcBufferedWrapper_T | m_rcUpdate | Update rectangle.
//@xref <c MvcController>


/////////////////////////////////////////////////////////////////////////////
//
// MvcBufferedWrapper_T
//
// @class MvcBufferedWrapper_T |
// The MvcBufferedWrapper_T class wraps a viewport and provides off-screen,
// flicker free rendering.
//
// @tcarg class | base_t | The class of the viewport to derive from.
//

template
	<
	class base_t
	>

class MvcBufferedWrapper_T : public base_t
{
// Constructors & Destructor
public:
	// @cmember
	/* Constructor.*/
	MvcBufferedWrapper_T();
	// @cmember
	/* Destructor.*/
	virtual ~MvcBufferedWrapper_T();

// Attributes
protected:
	// @cmember
	/* Turn screen buffering on or off*/
	BOOL m_bEnableBuffering;
	// @cmember
	/* Memory DC for offscreen buffer*/
	CDC* m_pBufferDC;
	// @cmember
	/* Bitmap that is selected into offscreen DC*/
	CBitmap* m_pBufferBmp;
	// @cmember
	/* Palette used for offscreen buffer*/
	CPalette* m_pBufferPal;
	// @cmember
	/* For restoring buffer DC*/
	HBITMAP m_hPrevBufferBmp;
	// @cmember
	/* For restoring buffer DC*/
	HPALETTE m_hPrevBufferPal;
	// @cmember
	/* Extra width and height added to buffer to reduce reallocation.*/
	int m_nBufPadding;
	// @cmember
	/* Update rectangle.*/
	CRect m_rcUpdate;

// Operations
public:
	// @cmember
	/* Enable or disable use of the offscreen buffer.*/
	void EnableBuffering(const BOOL bEnableBuffering);

	// @cmember
	/* Draws an area of the viewport to the offscreen buffer.*/
	virtual void DrawOffscreen();

	// @cmember
	/* Transfers the entire offscreen buffer to a screen DC.*/
	virtual void Refresh(CDC* pDC);
	// @cmember
	/* Transfers a rectangular area of the offscreen buffer to a screen DC.*/
	virtual void Refresh(CDC* pDC, const CRect &rcUpdate);

	// @cmember
	/* Set the palette to use for drawing to the offscreen buffer.*/
	void SetPalette(CPalette *pPal);

	// @cmember
	/* Set padding added to offscreen buffer to reduce reallocation when*/
	// resizing occurs.
	void SetBufferPadding(const int nBufPadding);

// Overrides
public:
	// @cmember
	/* Draws the entire viewport to a device context.*/
	virtual void Draw(CDC* pDC);

	// @cmember
	/* Initializes the viewport.*/
	virtual void OnInitialUpdate();

	//@cmember
	/* Invalidate the specified rectangle within the viewport.*/
	virtual void InvalidateRect(const CRect& rcLog, BOOL bErase = TRUE, BOOL bRepairNow = FALSE);

	//@cmember
	/* Returns the current invalid region as a rectangle.*/
	virtual BOOL GetUpdateRect(LPRECT lpRect, BOOL bErase = FALSE);

	// @cmember
	/* Set the width and height of the viewport in device units. Reallocates*/
	// the offscreen buffer, if necessary.
	virtual CSize SetSize(int cx, int cy);
	CSize SetSize(CSize size) { return SetSize(size.cx,size.cy); }

// Implementation
protected:
	// @cmember
	/* Creates memory DC and bitmap for offscreen buffer.*/
	BOOL CreateOffscreenBuffer();
	// @cmember
	/* Compares the current buffer size to the viewport dimensions.*/
	BOOL NeedToResizeBuffer();
	// @cmember
	/* Deletes the bitmap and memory DC.*/
	void DestroyOffscreenBuffer();
	// @cmember
	/* Clears the offscreen buffer before rendering.*/
	virtual void OnBufferedEraseBkgnd(CDC* pDC, CRect rcFill);
};

/////////////////////////////////////////////////////////////////////////////
// MvcBufferedWrapper_T methods

// @doc MvcBufferedWrapper_T
// @mfunc Constructor.
template<class base_t>
MvcBufferedWrapper_T<base_t>::MvcBufferedWrapper_T()
{
	m_bEnableBuffering = TRUE;
	m_pBufferDC = NULL;
	m_pBufferBmp = NULL;
	m_pBufferPal = NULL;
	m_nBufPadding = 100;
	m_rcUpdate = CRect(0,0,0,0);
}

// @doc MvcBufferedWrapper_T
// @mfunc Destructor.
template<class base_t>
MvcBufferedWrapper_T<base_t>::~MvcBufferedWrapper_T()
{
	delete m_pBufferPal;
	DestroyOffscreenBuffer();
}

// @doc MvcBufferedWrapper_T
// @mfunc Set the palette to use for drawing to the offscreen buffer.
// @rdesc void
// @parm Pointer to palette to use in offscreen buffer.
template<class base_t>
void MvcBufferedWrapper_T<base_t>::SetPalette(CPalette *pPal)
{
	ASSERT_VALID(pPal);

	if (m_pBufferPal != NULL)
	{
		if (m_pBufferDC != NULL)
		{
			::SelectPalette(m_pBufferDC->m_hDC, m_hPrevBufferPal, FALSE);
		}
		delete m_pBufferPal;
	}

	USHORT nEntries = (USHORT) pPal->GetEntryCount();
	LPLOGPALETTE pLogPal = (LPLOGPALETTE) new BYTE[ sizeof( LOGPALETTE ) + ( ( nEntries - 1 ) * sizeof( PALETTEENTRY ) ) ]; 
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = nEntries;
	pPal->GetPaletteEntries(0, nEntries, &pLogPal->palPalEntry[0]);
	m_pBufferPal = new CPalette();
	ASSERT(m_pBufferPal);
	if(m_pBufferPal)
	{
		m_pBufferPal->CreatePalette(pLogPal);
	}
	delete[] pLogPal;
}

// @doc MvcBufferedWrapper_T
// @mfunc Creates memory DC and bitmap for offscreen buffer.
// @rdesc TRUE if offscreen buffer successfully created, otherwise FALSE.
template<class base_t>
BOOL MvcBufferedWrapper_T<base_t>::CreateOffscreenBuffer()
{
	if (!m_bEnableBuffering)
	{
		return FALSE;
	}

	if (m_pBufferDC != NULL || m_pBufferBmp != NULL)
	{
		return FALSE;
	}

	CWnd* pWnd = GetWnd();

	if (pWnd == NULL || !(::IsWindow(pWnd->m_hWnd)))
	{
		return FALSE;
	}

	CDC* pWndDC = pWnd->GetWindowDC();
	OnPrepareDC(pWndDC);

	CRect rcMargins;
	base_t::GetMargins(rcMargins);
	CSize szViewport = GetSize() + rcMargins.Size();

	if (szViewport.cx <= 0 || szViewport.cy <= 0)
	{
		return FALSE;
	}

	m_pBufferDC = new CDC();
	ASSERT(m_pBufferDC != NULL);

	if (m_pBufferDC && m_pBufferDC->CreateCompatibleDC(pWndDC))
	{
		this->OnPrepareDC(m_pBufferDC);

		CSize szBuffer(szViewport);
		szBuffer.cx += m_nBufPadding;
		szBuffer.cy += m_nBufPadding;

		if( m_pBufferPal != NULL )
		{
			m_hPrevBufferPal = (HPALETTE) m_pBufferDC->SelectPalette(m_pBufferPal, FALSE);
			m_pBufferDC->RealizePalette();
		}

		m_pBufferBmp = new CBitmap();
		ASSERT(m_pBufferBmp != NULL);

		BOOL bBmpCreated = m_pBufferBmp->CreateCompatibleBitmap(pWndDC,
		                                                        szBuffer.cx,
		                                                        szBuffer.cy);

		if (bBmpCreated)
		{
			// Bitmap creation successful
			m_pBufferBmp->SetBitmapDimension(szBuffer.cx, szBuffer.cy);
			m_hPrevBufferBmp = (HBITMAP) m_pBufferDC->SelectObject(m_pBufferBmp);
		}
		else
		{
			// Bitmap creation failed. Destroy the bitmap and DC.

			delete m_pBufferBmp;
			m_pBufferBmp = NULL;

			if (m_pBufferPal != NULL)
			{
				::SelectPalette(m_pBufferDC->m_hDC, m_hPrevBufferPal, FALSE);
			}

			delete m_pBufferDC;
			m_pBufferDC = NULL;
		}
	}
	else
	{
		delete m_pBufferDC;
		m_pBufferDC = NULL;
	}

	pWnd->ReleaseDC(pWndDC);

	return (m_pBufferDC != NULL);
}

// @doc MvcBufferedWrapper_T
// @mfunc Compares the current buffer size to the viewport dimensions.
// @rdesc TRUE if offscreen buffer should be reallocated.
template<class base_t>
BOOL MvcBufferedWrapper_T<base_t>::NeedToResizeBuffer()
{
	BOOL bNeedToResize = FALSE;

	if (m_pBufferBmp != NULL)
	{
		CSize bmpSize = m_pBufferBmp->GetBitmapDimension();
		CRect rcMargins;
		base_t::GetMargins(rcMargins);
		CSize szMargins(rcMargins.left + rcMargins.right, rcMargins.top + rcMargins.bottom);
		CSize szViewport = GetSize() + szMargins;
		bNeedToResize = (bmpSize.cx < szViewport.cx) || (bmpSize.cy < szViewport.cy);
	}

	return bNeedToResize;
}

// @doc MvcBufferedWrapper_T
// @mfunc Deletes the bitmap and memory DC.
// @rdesc void
template<class base_t>
void MvcBufferedWrapper_T<base_t>::DestroyOffscreenBuffer()
{
	delete m_pBufferBmp;
	m_pBufferBmp = NULL;
	delete m_pBufferDC;
	m_pBufferDC = NULL;
}

// @doc MvcBufferedWrapper_T
// @mfunc Invalidate the specified rectangle within the viewport.
// @rdesc void
// @parm const CRect& | rcLog | Specifies the rectangle to invalidate, in logical coordinates
// @parmopt BOOL | bErase | TRUE | Should the visual part be completely erased prior to redraw
// @parmopt BOOL | bRepairNow | FALSE | Repair the invalid area immediately
template<class base_t>
void MvcBufferedWrapper_T<base_t>::InvalidateRect(const CRect& rcLog, BOOL bErase, BOOL bRepairNow)
{
	DC dc(this);
	// A viewport with an upward positive Y requires normalization
	CRect rcLogNormal(rcLog);
	rcLogNormal.NormalizeRect();
	m_rcUpdate = rcLogNormal;

	// Windows always omits the right and bottom unit in a rectangle.
	// So, to compensate, we add one to the right and bottom.  Otherwise,
	// we get screen garbage on the right and bottom borders.
	m_rcUpdate.right++;
	m_rcUpdate.bottom++;

	dc.LPtoDP(&m_rcUpdate);
	GetWnd()->InvalidateRect(m_rcUpdate, bErase);

	DrawOffscreen();

	if (bRepairNow)
		GetWnd()->UpdateWindow();
}

// @doc MvcBufferedWrapper_T
// @mfunc Retreives the coordinates of the smallest rectangle that encloses the update region.
// The bErase parameter specifies whether GetUpdateRect should erase the background of the
// update region.
// @parm LPRECT | lpRect | Rectangle of update region.
// @parm BOOL | bErase | Specifies whether the background of the update region is to be erased.
// @rdesc Specifies the status of the update region.  The value is nonzero if the region is not empty;
// otherwise, 0.
template<class base_t>
BOOL MvcBufferedWrapper_T<base_t>::GetUpdateRect(LPRECT lpRect, BOOL bErase)
{
	BOOL bStatus = GetWnd()->GetUpdateRect(lpRect, bErase);

	if (bStatus && !m_rcUpdate.IsRectEmpty())
	{
		if (m_rcUpdate.left < lpRect->left)
			lpRect->left = m_rcUpdate.left;
		if (m_rcUpdate.right > lpRect->right)
			lpRect->right = m_rcUpdate.right;
		if (m_rcUpdate.top < lpRect->top)
			lpRect->top = m_rcUpdate.top;
		if (m_rcUpdate.bottom > lpRect->bottom)
			lpRect->bottom = m_rcUpdate.bottom;
	}

	return bStatus;
}

// @doc MvcBufferedWrapper_T
// @mfunc Draws an area of the viewport to the offscreen buffer. If buffering is disabled,
// this function does nothing.
// @syntax void MvcBufferedWrapper_T::DrawOffscreen()
// @rdesc void
template<class base_t>
void MvcBufferedWrapper_T<base_t>::DrawOffscreen()
{
	if (m_bEnableBuffering && m_pBufferDC != NULL)
	{
		int nSaveDC = m_pBufferDC->SaveDC();
		OnPrepareDC(m_pBufferDC);

		CRect rcUpdate;

		if (GetWnd()->GetUpdateRect(&rcUpdate, FALSE))
		{
			DPtoLP(&rcUpdate);
		}
		else
		{
			rcUpdate = GetLogBounds();
		}

		// Ensure a normalized rect for viewport's with 
		// an upward positive Y-Axis.
		rcUpdate.NormalizeRect();

		OnBufferedEraseBkgnd(m_pBufferDC, rcUpdate);
		base_t::Draw(m_pBufferDC);

		if (nSaveDC != 0)
		{
			m_pBufferDC->RestoreDC(nSaveDC);
		}

		m_rcUpdate = CRect(0,0,0,0);
	}
}

// @doc MvcBufferedWrapper_T
// @mfunc Draws the entire diagram to a device context.
// @rdesc void
// @parm The device context to draw in.
template<class base_t>
void MvcBufferedWrapper_T<base_t>::Draw(CDC* pDC)
{
	if (m_bEnableBuffering && !pDC->IsPrinting())
	{
		//
		// Perform Refresh() only. Rendering to the offscreen
		// buffer has already been performed in one of the
		// invalidate functions.
		//
		CRect rcUpdate;

		if (!(GetWnd()->GetUpdateRect(&rcUpdate, FALSE)))
		{
			CRect rcMargins;
			base_t::GetMargins(rcMargins);
			rcUpdate = GetBounds();
			rcUpdate.InflateRect(&rcMargins);
		}
		
		// Ensure a normalized rect for viewport's with 
		// an upward positive Y-Axis.
		rcUpdate.NormalizeRect();
		Refresh(pDC, rcUpdate);
	}
	else
	{
		base_t::Draw(pDC);
	}
}

//@doc MvcBufferedWrapper_T
//@mfunc Transfers the offscreen buffer to a screen DC.
//@syntax void MvcBufferedWrapper_T::Refresh(CDC* pDC)
//@syntax void MvcBufferedWrapper_T::Refresh(CDC* pDC, const CRect &rcUpdate)
//@rdesc void
//@parm CDC* | pDC | Device context to refresh.
//@parm CRect& | rcUpdate | Rectangular area to refresh in container units.
template<class base_t>
inline void MvcBufferedWrapper_T<base_t>::Refresh(CDC* pDC)
{
	CRect rcMargins;
	base_t::GetMargins(rcMargins);
	CRect rcBounds = GetBounds();
	rcBounds.InflateRect(&rcMargins);
	Refresh(pDC, rcBounds);
}

template<class base_t>
void MvcBufferedWrapper_T<base_t>::Refresh(CDC* pDC, const CRect &rcUpdate)
{
	CRect rcMargins;
	base_t::GetMargins(rcMargins);
	CRect rcBounds = GetBounds();
	rcBounds.InflateRect(&rcMargins);
	CRect rcClippedUpdate(rcUpdate);
	rcClippedUpdate.IntersectRect(&rcClippedUpdate, &rcBounds);

	base_t::Erase(pDC);

	if (!m_bEnableBuffering || m_pBufferDC == NULL)
	{
		// Buffering is disabled. Revert to normal draw.
		base_t::Draw(pDC);
	}
	else
	{
		//
		// Make sure that source and destination DC's are set
		// to MM_TEXT. The offscreen buffer is already in
		// device units.
		//
		int prevMapMode = pDC->SetMapMode(MM_TEXT);

		pDC->SetViewportOrg(0,0);
		pDC->SetWindowOrg(0,0);

		m_pBufferDC->SetMapMode(MM_TEXT);
		m_pBufferDC->SetViewportOrg(0,0);
		m_pBufferDC->SetWindowOrg(0,0);

		CPalette *pPrevPal = NULL;
		if (m_pBufferPal != NULL)
		{
			pPrevPal = pDC->SelectPalette(m_pBufferPal, FALSE);
			pDC->RealizePalette();
		}
 
		pDC->BitBlt(rcClippedUpdate.left, rcClippedUpdate.top,
					rcClippedUpdate.Width(), rcClippedUpdate.Height(),
					m_pBufferDC,
					rcClippedUpdate.left, rcClippedUpdate.top,
					SRCCOPY);

		if (pPrevPal != NULL)
		{
			pDC->SelectPalette(pPrevPal, FALSE);
		}

		pDC->SetMapMode(prevMapMode);
	}
}

// @doc MvcBufferedWrapper_T
// @mfunc Called when the viewport is first instantiated. This is used
// to initialize the viewport.
// @rdesc void
template<class base_t>
inline void MvcBufferedWrapper_T<base_t>::OnInitialUpdate()
{
	base_t::OnInitialUpdate();
	CreateOffscreenBuffer();
	DrawOffscreen();
}

// @doc MvcBufferedWrapper_T
// @mfunc Set the width and height of the viewport in device units. Reallocates
// the offscreen buffer, if necessary.
// @rdesc CSize The new size
// @parm int | cx | The horizontal size
// @parm  int | cy | The vertical size
template<class base_t>
CSize MvcBufferedWrapper_T<base_t>::SetSize(int cx, int cy)
{
	CSize rc = base_t::SetSize(cx, cy);

	if (m_bEnableBuffering && GetWnd() != NULL)
	{
		if (m_pBufferDC == NULL || NeedToResizeBuffer())
		{
			DestroyOffscreenBuffer();
			CreateOffscreenBuffer();
		}
		DrawOffscreen();
	}

	return rc;
}

// @doc MvcBufferedWrapper_T
// @mfunc Enable or disable use of the offscreen buffer.
// @rdesc void
// @parm Boolean flag that indicates if buffering should be enabled or disabled.
template<class base_t>
inline void MvcBufferedWrapper_T<base_t>::EnableBuffering(const BOOL bEnableBuffering)
{
	m_bEnableBuffering = bEnableBuffering;
}

// @doc MvcBufferedWrapper_T
// @mfunc Set padding added to offscreen buffer to reduce reallocation when
// resizing occurs.
// @rdesc void
// @parm Padding width and height in device units.
template<class base_t>
inline void MvcBufferedWrapper_T<base_t>::SetBufferPadding(const int nBufPadding)
{
	m_nBufPadding = nBufPadding;
}

// @doc MvcBufferedWrapper_T
// @mfunc Clears the offscreen buffer before rendering.
// @rdesc void
// @parm Pointer to device context to erase.
// @parm Rectangular area to erase.
template<class base_t>
inline void MvcBufferedWrapper_T<base_t>::OnBufferedEraseBkgnd(CDC* pDC, CRect rcFill)
{
	CBrush br(::GetSysColor(COLOR_WINDOW));
	pDC->FillRect(&rcFill, &br);
}

///////////////////////////////////////////////////////////////////////////

//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // __COMPAT_MVCBUFFEREDWRAPPER_H__

