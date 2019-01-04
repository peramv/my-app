///////////////////////////////////////////////////////////////////////////////
// gxcole.cpp : implementation of the CGXOlePreview control
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

#ifndef _GXCOLE_H__
#include "grid\gxcole.h"
#endif

#ifndef _GX_OLEVARIANT_USER_H__
#include "grid\gxoleusr.h"
#endif

#ifndef _GXDDIB_H_
#include "grid\gxddib.h"
#endif


#ifndef __AFXCONV_H__
#include "afxconv.h"
#endif

#include "grid\gxclsite.h"

#include "grid\gxresrc.h"

#include "oledlg.h"

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// compile this file only if DAO is supported
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)


GRID_IMPLEMENT_CONTROL(CGXOlePreview, CGXStatic);

// Use macro for the simplest cases of calling FormatMessage

#define GX_FORMAT_MSG(hr)\
{\
LPTSTR lpBuffer = NULL;\
DWORD dw = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,\
NULL,  hr,\
MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),\
(LPTSTR) &lpBuffer, 0, NULL);\
if(dw)\
{\
	AfxMessageBox(lpBuffer);\
	::LocalFree(lpBuffer);\
}\
}


/////////////////////////////////////////////////////////////////////////////
// CGXOlePreview
CGXOlePreview::CGXOlePreview(CGXBrowserGrid* pGrid, CGXViewerFactory* pFactory)
	: CGXStatic(pGrid)
{
	m_pActiveViewer = NULL;

	if(pFactory == NULL)
		pFactory = new CGXViewerFactory;

	m_pViewerManager = new CGXViewerManager(pFactory);
	
	m_bModified = FALSE;

	AddChild(m_pHotSpot = new CGXHotSpotButton(this));
	
	m_bDiscardActivate = FALSE;
}

CGXOlePreview::~CGXOlePreview()
{
	if(m_pViewerManager != NULL)
		delete m_pViewerManager;
}

BOOL CGXOlePreview::LButtonDblClk(UINT nFlags, CPoint pt)
{
	return CGXControl::LButtonDblClk(nFlags, pt);
}

HWND CGXOlePreview::PreRender()
{
	// When displaying a message-box, CGXGridCore:.OnActivateGrid
	// will be called. The message-box will become activ and the
	// grid window will become inactiv which results in
	// a further call to CGXGridCore::OnActivateGrid.
	// It is necessary to avoid that OnActivateGrid calls
	// CanSelectCurrentCell(FALSE) again.
	//
	// The semaphor m_bLockActivateGrid is checked in OnActivateGrid to avoid these behavior:

		Grid()->m_bLockActivateGrid = TRUE;

		HWND hWndFocus = ::GetFocus();

		// Remove any pendig Keyboard messages
		if (IsWindow(hWndFocus))
		{
			MSG msg;
			while (::PeekMessage(&msg,  // pointer to structure for message
				hWndFocus,  // handle to window
				WM_KEYFIRST, // first message
				WM_KEYLAST, // last message
				PM_REMOVE)  // removal flags
				)
				NULL;
		}

		// Make sure cell is visible
		ROWCOL nEditRow, nEditCol;
		if (Grid()->GetCurrentCell(nEditRow, nEditCol))
			Grid()->ScrollCellInView(nEditRow, nEditCol);
		
		return hWndFocus;
}

void CGXOlePreview::PostRender(HWND hWndFocus)
{
		Grid()->m_bWarningTextDisplayed = TRUE;
			// indicates that this function has displayed a message-box.
			// The grid checks this variable to determine if it should
			// cancel any internal modes (e.g. if user is selecting cells)

		if (IsWindow(hWndFocus))
		{
			::SetFocus(hWndFocus);

			if (Grid()->m_pGridWnd->GetSafeHwnd() == hWndFocus || ::IsChild(Grid()->m_pGridWnd->GetSafeHwnd(), hWndFocus))
				Grid()->m_bActiveFrame = TRUE;

		}

		Grid()->m_bLockActivateGrid = FALSE;
}


void CGXOlePreview::SetActiveViewer(CGXOleViewer* pViewer)
{
	m_pActiveViewer = pViewer;
}
	
CGXOleViewer* CGXOlePreview::GetActiveViewer() const
{
	return m_pActiveViewer;
}

CGXViewerManager* CGXOlePreview::GetViewerManager() const
{
	return m_pViewerManager;
}

void CGXOlePreview::SetModify(BOOL bModified)
{
	m_bModified = bModified;
}

BOOL CGXOlePreview::GetModify()
{
	return m_bModified;
}

BOOL CGXOlePreview::Store()
{
	// Calls SetStyleRange() 
	NeedStyle();
	ASSERT(m_pStyle);

	CString sValue;
	if (m_pStyle && GetModify() && IsInit())
	{
		SetActive(FALSE);
		
		CGXBrowserGrid* pGrid = (CGXBrowserGrid*)Grid();

		if(m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_DAOOLEBMP) && GetActiveViewer())
		{	
				const CGXOleVarUserAttribute& oleAttr = (const CGXOleVarUserAttribute&)m_pStyle->GetUserAttribute(GX_IDS_UA_DAOOLEBMP);
				CGXOleVarUserAttribute* oa = (CGXOleVarUserAttribute*) oleAttr.Clone();
				oa->SetOleVarValue(GetActiveViewer()->GetData());
				oa->m_bModifyState = TRUE;
				m_pStyle->SetUserAttributePtr(GX_IDS_UA_DAOOLEBMP, oa);
		}
		else if(GetActiveViewer() != NULL)
		{
				CGXOleVarUserAttribute* oa =  new CGXOleVarUserAttribute;
				oa->SetOleVarValue(GetActiveViewer()->GetData());
				oa->m_bModifyState = TRUE;
				m_pStyle->SetUserAttributePtr(GX_IDS_UA_DAOOLEBMP, oa);
		}
		
		return pGrid->SetStyleRange(CGXRange(m_nRow, m_nCol), *m_pStyle, gxOverride, 0, GX_INVALIDATE);
	}

	return TRUE;	
}

void CGXOlePreview::Init(ROWCOL nRow, ROWCOL nCol)
{
	CGXStatic::Init(nRow, nCol);
	
	GridWnd()->InvalidateRect(m_pHotSpot->GetRect());
	
	Refresh();
}


const int nEditBtnWidth = 13;

CRect CGXOlePreview::GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem /* = NULL */, const CGXStyle* pStyle /*= NULL*/)
{
	// compute the interior rectangle for the text
	// without buttons and borders

	CRect rect = CGXStatic::GetCellRect(nRow, nCol, rectItem, pStyle);

	rect.right -= nEditBtnWidth;

	return rect;
}

CSize CGXOlePreview::AddBorders(CSize size, const CGXStyle& style)
{
	size.cx += nEditBtnWidth;

	return CGXStatic::AddBorders(size, style);
}

void CGXOlePreview::OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect)
{
	nRow, nCol;

	const int nEditBtnWidth = 13;

	// init hotspot button
	CRect rectBtn;
	rectBtn.IntersectRect(rect,
				CRect(rect.right-1-nEditBtnWidth, rect.top, rect.right-1, rect.top+nEditBtnWidth));

	if (rectBtn.Height() < rect.Height()-1)
	{
		rectBtn.top += 1;
		rectBtn.bottom += 1;
	}

	m_pHotSpot->SetRect(rectBtn);
}

BOOL CGXOlePreview::CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL)
{
	// don't support floating
	return FALSE;
}

void CGXOlePreview::PreDoVerb()
{
	m_bDiscardActivate = GXGetAppData()->m_bDiscardNcActivate; 
	GXGetAppData()->m_bDiscardNcActivate = TRUE;
}

void CGXOlePreview::PostDoVerb()
{
	GXGetAppData()->m_bDiscardNcActivate = m_bDiscardActivate;
	m_bDiscardActivate = FALSE;
}

void CGXOlePreview::OnClickedButton(CGXChild* pChild)
{
	CGXStatic::OnClickedButton(pChild);
	
	// check if we can start eidting
	if(!OnStartEditing())
		return;

	// check if there is an existing viewer available
	LPOLEOBJECT lpOleObject = NULL;
	
	if(GetActiveViewer() != NULL)
		lpOleObject = GetActiveViewer()->GetOleObject();

	if(GetActiveViewer() != NULL && lpOleObject !=NULL )
	{
		GetActiveViewer()->ActivateExisting();
		return;
	}
	
	ASSERT(m_bInit);
	
	// start the viewer if required
	NeedStyle();
	
	CGXOleViewer* pViewer = GetOleViewer();
	
	ASSERT(pViewer != NULL); // Error there is no viewer available for this data

	if(pViewer != NULL)
	{
		HWND hWnd = PreRender();
		SetActive(TRUE);
		PreDoVerb();
		pViewer->Render(m_pStyle, Grid(), this);
		PostRender(hWnd);
		SetActiveViewer(pViewer);
	}

	GX_UNUSED_ALWAYS(pChild);
}

CGXOleViewer* CGXOlePreview::GetOleViewer()
{
	NeedStyle();

	CGXBrowserGrid* pGrid = dynamic_cast<CGXBrowserGrid*>(Grid());

	ASSERT(pGrid != NULL); // Error; This control requires a browser grid parent

	if(pGrid == NULL)
		return NULL;

	// Get the viewer ID for this row and column
	DWORD dwId = GX_INVALID;

	if( m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_OLEVIEWERID) )
	{
		const CGXAbstractUserAttribute& uAttribute = m_pStyle->GetUserAttribute(GX_IDS_UA_OLEVIEWERID);
	
		if(!uAttribute.IsEmpty())
			dwId = uAttribute.GetDWordValue();
	}

	// use this ID to look up the viewer
	CGXOleViewer* pViewer = GetViewerManager()->CreateViewer(dwId);

	// give the user the possibility to change the viewer
	pGrid->GetOleViewerRowCol(m_nRow, m_nCol, dwId, pViewer);
	
	return pViewer;
}


BOOL CGXOlePreview::OnLeftCell(ROWCOL nNewRow, ROWCOL nNewCol)
{
	if(GetActiveViewer() != NULL)
	{
		GetActiveViewer()->Close();
		GetActiveViewer()->Clear();
	}

	SetActiveViewer(NULL);
	
	return CGXStatic::OnLeftCell(nNewRow, nNewCol);
}

BOOL CGXOlePreview::OnCancelEditing()
{
	if(GetActiveViewer() != NULL)
	{
		GetActiveViewer()->Close();
		GetActiveViewer()->Clear();
	}

	return CGXStatic::OnCancelEditing();
}

BOOL CGXOlePreview::Paste()
{
	// If there is an active viewer, then use the rendered application to paste the data
	if(GetActiveViewer() != NULL)
	{
		OnActiveViewerPresent();
		return FALSE;
	}

	// Check if we can edit
	if(!OnStartEditing())
		return FALSE;
	
	SetActive(TRUE);
	NeedStyle();

	
	CGXOleViewer* pViewer = GetOleViewer();
	ASSERT(pViewer != NULL);
	if(pViewer == NULL)
		return FALSE;
	
	
	COleVariant* pVariant = NULL;
	pViewer->SetActiveControl(this);
	
	pVariant = pViewer->Paste();
	
	//ASSERT(pVariant != NULL);
	
	if(pVariant == NULL)
	{
		AfxMessageBox(GX_IDS_ERRORBINDATA);
		// paste failed
		pViewer->Clear();
		pViewer->SetActiveControl(NULL);
		return FALSE;
	}

	SetActiveViewer(pViewer);

	// the next updated will catch this change
	pViewer->OnModify();
	SetModify(TRUE);
		
	return TRUE;
}

BOOL CGXOlePreview::CanPaste()
{
	if(GetActiveViewer() != NULL)
		return FALSE;
	
	NeedStyle();

	CGXOleViewer* pViewer = GetOleViewer();

	if(pViewer == NULL)
		return FALSE;
	
	return pViewer->CanPaste();
}

BOOL CGXOlePreview::CanCopy()
{
	// There is a active viewer....copy from there
	if(GetActiveViewer() != NULL)
		return FALSE;
	
	NeedStyle();

	CGXOleViewer* pViewer = GetOleViewer();

	BOOL b(FALSE);

	if(pViewer != NULL) // no viewer
		b = pViewer->CanCopy();
	
	if(b)
		return TRUE;
	else
		return CanCopyCanCutHelper();
}


BOOL CGXOlePreview::Copy()
{
	if(GetActiveViewer() != NULL)
	{
		OnActiveViewerPresent();
		return FALSE;
	}

	CGXOleViewer* pViewer = GetOleViewer();

	if(pViewer == NULL)
		return FALSE;

	NeedStyle();
	
	IDataObject* pDataObject = pViewer->Copy(m_pStyle, Grid(), this);

	if(pDataObject == NULL)
	{
		AfxMessageBox(GX_IDS_OLECOPYFAILED);
		return FALSE;
	}
#ifdef _DEBUG
	
	IEnumFORMATETC* pFormatEtc = NULL;
	pDataObject->EnumFormatEtc(DATADIR_GET,  &pFormatEtc);

	LPFORMATETC formatEtc = NULL;
	
	while (pFormatEtc->Next(1, formatEtc, NULL) == S_OK)
	{
		TRACE1("Clipboard format %d\n", formatEtc->cfFormat);	
		TRACE1("Tymed %d\n", formatEtc->tymed);	
	}

#endif

	HRESULT hr = ::OleSetClipboard(pDataObject);
	
	if(FAILED(hr))
	{
		TRACE0(" Call to OleSetClipboard fails in CGXOlePreview::Copy()\n");
		GX_FORMAT_MSG(hr);
		AfxMessageBox(GX_IDS_OLECOPYFAILED);
		pDataObject->Release();
		return FALSE;
	}
	
	// So that I can do a close. The normal route would be to do a delayed render.
	// While delayed render is more effecient, I cannot close the object.
	hr = ::OleFlushClipboard();

	if(FAILED(hr))
	{
		TRACE0(" Call to OleFlushClipboard fails in CGXOlePreview::Copy()\n");
		GX_FORMAT_MSG(hr);
		AfxMessageBox(GX_IDS_OLECOPYFAILED);
		pDataObject->Release();
		return FALSE;
	}
	

	pDataObject->Release();

	
	pViewer->Close();
	pViewer->Clear();

	return TRUE;
}

// Cut
//
// Cut will only cut  data to clipboard if cell is active (has the focus)
// If you also want to support Cut for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

BOOL CGXOlePreview::CanCut()
{
	// There is a active viewer....cut from there
	if(GetActiveViewer() != NULL)
		return FALSE;
	
	NeedStyle();

	CGXOleViewer* pViewer = GetOleViewer();

	BOOL b(FALSE);

	if(pViewer != NULL) //viewer
		b = pViewer->CanCut();
	
	if(b)
		return TRUE;
	else
		return CanCopyCanCutHelper();
}

void CGXOlePreview::OnActiveViewerPresent()
{
	AfxMessageBox(GX_IDS_ACTIVEVIEWERPRESENT);
	
	ASSERT(GetActiveViewer() != NULL); // Error This message is to be displayed only when there is an active viewer 
	// present
	
	if(GetActiveViewer() == NULL)
		return;

	GetActiveViewer()->ActivateExisting();
}

BOOL CGXOlePreview::Cut()
{
	// If there is an active viewer, then use that
	if(GetActiveViewer() != NULL)
	{
		OnActiveViewerPresent();
		return FALSE;
	}

	if(!OnStartEditing())
		return FALSE;

	SetActive(TRUE);

	CGXOleViewer* pViewer = GetOleViewer();

	if(pViewer == NULL)
	{
		AfxMessageBox(GX_IDS_OLECUTFAILED);
		return FALSE;
	}

	NeedStyle();

	pViewer->SetActiveControl(this);

	IDataObject* pDataObject = pViewer->Cut(m_pStyle, Grid(), this);

	if(pDataObject == NULL)
	{
		AfxMessageBox(GX_IDS_OLECUTFAILED);
		return FALSE;
	}
	
	HRESULT hr = ::OleSetClipboard(pDataObject);
	
	if(FAILED(hr))
	{
		TRACE0(" Call to OleSetClipboard fails in CGXOlePreview::Cut()\n");
		AfxMessageBox(GX_IDS_OLECUTFAILED);
		pDataObject->Release();
		return FALSE;
	}
	
	// So that I can do a close. The normal route would be to do a delayed render.
	// While delayed render is more effecient, I cannot close the object.
	hr = ::OleFlushClipboard();

	if(FAILED(hr))
	{
		TRACE0(" Call to OleFlushClipboard fails in CGXOlePreview::Cut()\n");
		AfxMessageBox(GX_IDS_OLECUTFAILED);
		pDataObject->Release();
		return FALSE;
	}
	

	pDataObject->Release();

	
	pViewer->Close();
	SetActiveViewer(pViewer);

	return TRUE;
}


BOOL CGXOlePreview::CanCopyCanCutHelper()
{
	// check stored data
	NeedStyle();
	const COleVariant* pVariant = NULL;
	
	if(m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_DAOOLEBMP) )
	{	
			const CGXOleVarUserAttribute& oleAttr = (const CGXOleVarUserAttribute&)m_pStyle->GetUserAttribute(GX_IDS_UA_DAOOLEBMP);
			pVariant = oleAttr.GetOleVarValue();
			
			if(pVariant == NULL)
				return FALSE;

			LPCVARIANT var = (LPCVARIANT) pVariant;

			if( var->vt == (VT_ARRAY|VT_UI1) )
				return TRUE;		
			else
				return FALSE;
	}
	
	return FALSE;
}

void CGXOlePreview::SetActive(BOOL bActive)
{
	m_bActive = bActive;
}

BOOL CGXOlePreview::IsActive()
{
	return m_bActive;
}

void CGXOlePreview::SetCurrentText(const CString& str)
{
	// no Implementation
	GX_UNUSED_ALWAYS(str);
}

BOOL CGXOlePreview::SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle)
{
	return FALSE;
	GX_UNUSED_ALWAYS(pOldStyle);
	GX_UNUSED_ALWAYS(nFlags);
	GX_UNUSED_ALWAYS(str);
	GX_UNUSED_ALWAYS(nCol);
	GX_UNUSED_ALWAYS(nRow);
}

BOOL CGXOlePreview::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bProcessed = FALSE;

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;

	// Pass all CTRL keys to the grid
	if (!bCtl)
	{
		switch (nChar)
		{
		case VK_DELETE:
			{
				// If there is an active viewer, then use that
				if(GetActiveViewer() != NULL)
				{
					OnActiveViewerPresent();
					return FALSE;
				}

				if(!OnStartEditing())
					return FALSE;
				
				SetActive(TRUE);

				CGXOleViewer* pViewer = GetOleViewer();

				if(pViewer == NULL)
					return FALSE;

				NeedStyle();

				pViewer->SetActiveControl(this);

				pViewer->Clear();
				
				SetActiveViewer(pViewer);
				SetModify(TRUE);
				
				bProcessed = TRUE;
				break;
			}	
		}
	}

	if (bProcessed)
	{
		Grid()->TransferCurrentCell(TRUE);
		return TRUE;
	}

	return CGXStatic::OnGridKeyDown(nChar, nRepCnt, nFlags);
}


// Implementation of CGXViewerManager

CGXViewerManager::CGXViewerManager(CGXViewerFactory* pFactory):CGXNodeManager<CGXOleViewer>(NULL)
{
	m_pFactory = pFactory;
	InternalCheck();	
}

CGXViewerManager::~CGXViewerManager()
{
	if(m_pFactory != NULL)
		delete m_pFactory;
}

void CGXViewerManager::InternalCheck() const
{
	ASSERT(m_pFactory != NULL); // The viewer factory cannot be NULL. We cannot create any viewers!
}

CGXViewerFactory* CGXViewerManager::GetViewerFactory()
{
	InternalCheck();
	return m_pFactory;
}

CGXOleViewer* CGXViewerManager::CreateObject(SEC_DWORD dw)
{
	CGXOleViewer* pObject = NULL;
	if(GetMap()->Lookup(dw, pObject) == FALSE )
	{
		// check if we have a valid factory object
		InternalCheck();
		
		CGXOleViewer* p = GetViewerFactory()->CreateViewer(dw);
		ASSERT(p != NULL);
		GetMap()->SetAt(dw, p);
		
		return p;
	}
	else
	{
		return pObject;
	}	
}

CGXOleViewer* CGXViewerManager::CreateViewer(SEC_DWORD dw)
{
	return CreateObject(dw);	
}

// Implementation of CGXViewerFactory
// The default viewer factory. Derive from this factory if you have 
// other viewer implementation

CGXViewerFactory::CGXViewerFactory()
{

}

CGXViewerFactory::~CGXViewerFactory()
{
}

CGXOleViewer* CGXViewerFactory::CreateViewer(SEC_DWORD dw)
{
	switch(dw)
	{
		case GX_INVALID:
		default:
			{
				return new CGXGenericViewerImpl();
			}
	}	
}

// Implementation of CGXGenericViewerImpl
// Capable of viewing and editing embedded Ole objects in MS Access data bases.
// These routines assume that the data is stored and is to be written back as 
// OLE1 streams. If you are working with another data base or with a future version of
// MS Access (later than Access 97) then you can remove the code that goes back and forth
// between ole streams and IStorage. You can just use a storage object created on a HGLOBAL
// handle

CGXGenericViewerImpl::CGXGenericViewerImpl()
{
	m_oleVariant.Clear();
	
	// The cookie member for IAdviseSink
	m_dwAdviseCookie = 0;
}

CGXGenericViewerImpl::~CGXGenericViewerImpl()
{
	LPOLEOBJECT pOleObject = (LPOLEOBJECT) GetInterfaceManager().GetInterface(&IID_IOleObject);
	
	if(pOleObject != NULL)
	{
		pOleObject->Close(OLECLOSE_NOSAVE);
	}

	GetInterfaceManager().CleanObjects();
	m_oleVariant.Clear();
}

long CGXGenericViewerImpl::GetVerb()
{
	return OLEIVERB_PRIMARY;
}


// Some of these routines are from the most part from a Microsoft sample for Access 95
int _GXReadAccessHeader( HGLOBAL hgMemSource, LPCLSID lpclsid )
{
	USES_CONVERSION;

	// read the access header
	POLEOBJHDR pHdr = ( POLEOBJHDR ) GlobalLock( hgMemSource );
	if( NULL == pHdr )
		return 0;

	if(pHdr->typ != 0x1c15)
		return 0;

	// extract the ProgID and convert it to a CLSID
	LPCOLESTR	lpostrProgID;
	TCHAR		szProgID[ MAX_PROGID ];
	LPCTSTR		lpszProgIDinHeader = ( LPCTSTR ) pHdr + ( pHdr->ibClass );
	// QA: 31989 - #if Secure Code Cleanup.
	_tcsncpy( szProgID, lpszProgIDinHeader, pHdr->cchClass );
	lpostrProgID = T2COLE( szProgID );
	if( FAILED( CLSIDFromProgID( lpostrProgID, lpclsid )))
		return 0;

	return pHdr->ibClass + pHdr->cchClass;
}

int _GXWriteAccessHeader( HGLOBAL hgMemSource, IOleObject* pObject )
{
	USES_CONVERSION;

	// make some preparations needed to fill header
	LPOLESTR	lpostrObjectName;
	if( FAILED( pObject->GetUserType( USERCLASSTYPE_SHORT, &lpostrObjectName )))
		return 0;
	LPCTSTR		lpszObjectName = OLE2CT( lpostrObjectName );

	CLSID clsid;
	if( FAILED( pObject->GetUserClassID( &clsid )))
		return 0;

	LPOLESTR lposstrProgID;
	if( FAILED( ProgIDFromCLSID( clsid, &lposstrProgID )))
		return 0;
	LPCTSTR lpszProgID = OLE2CT( lposstrProgID );

	// fill in the ACCESS header
	POLEOBJHDR pHdr = ( POLEOBJHDR ) GlobalLock( hgMemSource );
	if( NULL == pHdr )
		return 0;
	pHdr->typ		= 0x1c15;
	pHdr->cbHdr		= sizeof( OLEOBJHDR );
	pHdr->oot		= OT_EMBEDDED;					// simplified !
	pHdr->cchName	= ( USHORT ) ( _tcslen( lpszObjectName ) + 1 );
	pHdr->cchClass	= ( USHORT ) ( _tcslen( lpszProgID     ) + 1 );
	pHdr->ibName	= sizeof( OLEOBJHDR );
	pHdr->ibClass	= ( USHORT ) ( pHdr->ibName + pHdr->cchName );
	pHdr->ptSize.x	= -1;
	pHdr->ptSize.y	= -1;
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(( LPTSTR ) (( LPTSTR ) pHdr) + pHdr->ibName,  lpszObjectName );
	_tcscpy(( LPTSTR ) (( LPTSTR ) pHdr) + pHdr->ibClass, lpszProgID	  );

	// clean-up
	GlobalUnlock( hgMemSource );
	return pHdr->ibClass + pHdr->cchClass;
}

HGLOBAL _GXSkipAccessHeader( HGLOBAL hgMemSource, DWORD* pdwObjectLength )
{
	DWORD		dwBLOBSize;
	HGLOBAL		hgMemDest	= NULL;
	LPVOID		lpvMemDest	= NULL;
	LPVOID		lpvMemSrc	= NULL;
	WORD 		wSizeHeader = 0;
	POLEOBJHDR	pHdr		= NULL;

	// reset indicated length
	*pdwObjectLength = 0;
	
	// Get the length of the OLEOBJHDR
	if( NULL == ( lpvMemSrc = GlobalLock( hgMemSource )))
		return NULL;
	pHdr = ( POLEOBJHDR ) lpvMemSrc;
	wSizeHeader = ( USHORT ) ( pHdr->ibClass + pHdr->cchClass );
	if( 0 == wSizeHeader )
		return NULL;
	
	// Get the length of the memory pointed to by hgMemSource
	dwBLOBSize = (DWORD)GlobalSize( hgMemSource );

	// Allocate a new global memory-block of size "dwBLOBSize-wSizeHeader-sizeof(DWORD)" 
	// where dwBLOBSize is the size of the CLongBinary, wSizeHeader is the size of the
	// complete ACCESS header (including the ProgID and CLSID) and sizeof(DWORD) is the
	// size of the checksum which ACCESS writes immediately behind the OLEOBJECT.
	// NOTE: in versions up to ACCESS 2.0, the checksum isn't evaluated during read,
	//		 so there is no need to either read or write it.
	if( NULL == ( hgMemDest = GlobalAlloc( 
		GHND | GMEM_NODISCARD, ( DWORD ) dwBLOBSize-wSizeHeader-sizeof(DWORD) )))
		return NULL;
	if( NULL == ( lpvMemDest = GlobalLock( hgMemDest )))
		return NULL;

	// new copy the OLEOBJECT to the newly allocated memory block
	// NOTE:	use GHND | GMEM_NODISCARD for OLE memory!!
	memcpy( lpvMemDest, (( LPSTR ) lpvMemSrc ) + wSizeHeader, dwBLOBSize-wSizeHeader-sizeof(DWORD));
	*pdwObjectLength = dwBLOBSize - wSizeHeader - sizeof( DWORD );

	GlobalUnlock( hgMemDest );		// don't check for lock == 0, since ODBC
	GlobalUnlock( hgMemSource );	// still might have a lock on hgMemSource
	
	// return the new memory-block
	return hgMemDest;
}

// prepare OLESTREAM for use by OleConvertOLESTREAMToIStorage()
LPOLE1STREAM _GXCreateOle1Stream( LPSTREAM pStm, DWORD dwSize )
{
	ASSERT( pStm != NULL );
	
	// Create a new OLESTREAMVTBL to handle callbacks
	LPOLESTREAMVTBL pvt = new OLESTREAMVTBL;
	
	// Initialize callbacks w/ our global functions
	pvt->Get = &_GXGet;	
	pvt->Put = &_GXPut;
	
	// Create an OLE1STREAM
	LPOLE1STREAM pOle1Stream = new OLE1STREAM;
	
	// Initialize it with the OLESTREAMVTBL and data
	pOle1Stream->pvt	  = pvt;
	pOle1Stream->dwSize   = dwSize;
	pOle1Stream->lpStream = pStm;
	
	return pOle1Stream;
}

// destroy OLESTREAM used by OleConvertOLESTREAMToIStorage()
void _GXDeleteOleStream( LPOLE1STREAM pOle1Stream )
{
	ASSERT( pOle1Stream != NULL );
	ASSERT( pOle1Stream->pvt != NULL );
	
	// Delete / release member data
	delete pOle1Stream->pvt;
	pOle1Stream->lpStream->Release();	// will also delete the HGLOBAL which was
										// allocated during CreateStreamOnHGlobal()
	
	// Delete the stream itself
	delete pOle1Stream;
}

// this CALLBACK will be called from inside OleConvertOLESTREAMToIStorage
DWORD FAR PASCAL _GXGet(LPOLESTREAM pstm, void FAR* pb, DWORD cb)
{
	// convert the passed in LPOLESTREAM to our own LPOLE1STREAM format in order
	// to be able to access the IStream* created by CreateStreamOnHGlobal()
	LPOLE1STREAM pOle1Stream = ( LPOLE1STREAM ) pstm;

	// Check the validity of the stream and that we are
	// not reading more bytes than are in the stream.
	if ((pOle1Stream == NULL) || (pOle1Stream->lpStream == NULL) || 
		(pOle1Stream->dwSize < cb))
		return 0L;
	
	// try to read from the stream
	ULONG	ulBytesRead = 0;
	if( FAILED( pOle1Stream->lpStream->Read( pb, cb, &ulBytesRead )))
		return 0;
	pOle1Stream->dwSize -= ulBytesRead;
	
	return cb;
}

// this CALLBACK will be called from inside OleConvertOLESTREAMToIStorage
DWORD FAR PASCAL _GXPut(LPOLESTREAM pstm, const void FAR* pb, DWORD cb)
{
	// convert the passed in LPOLESTREAM to our own LPOLE1STREAM format in order
	// to be able to access the IStream* created by CreateStreamOnHGlobal()
	LPOLE1STREAM pOle1Stream = (LPOLE1STREAM)pstm;

	// Check the validity of the stream and that we are
	// not writing more data than we have space for.
	if ((pOle1Stream == NULL) || (pOle1Stream->lpStream == NULL) || (pb == NULL))
		return 0L;
	
	// ASSUME that buffers don't overlap.
	ULONG	ulBytesWritten = 0;
	if( FAILED( pOle1Stream->lpStream->Write( pb, cb, &ulBytesWritten )))
		return 0;
	pOle1Stream->dwSize += ulBytesWritten;
	
	return cb;
}

void CGXGenericViewerImpl::Render(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl, BOOL bShow /*= TRUE*/)
{
	HGLOBAL hReadData = AccessData(pStyle, pGrid, pCtrl);

	// Call SetActiveControl with the control instance that was passed in
	SetActiveControl(pCtrl);

	if(hReadData)
	{
		if(!SpawnViewer(hReadData, pGrid, bShow))
			SetActiveControl(NULL);

	}
	else
	{
		if(!CreateNew(pGrid))
			SetActiveControl(NULL);
	}
}

BOOL CGXGenericViewerImpl::CreateNew(CGXGridCore* pGrid)
{
	if(pGrid == NULL)
		return FALSE;

	// Interface and handle manager
	CGXInterfaceManager<IUnknown> _intmgr;
	CGXHandleManager<HGLOBAL> _hmgr;
	
	LPSTORAGE pStorage = NULL;
	LPOLEOBJECT pOleObject = NULL;
	
	// Create the Storage 
	try
	{
		HGLOBAL hG = NULL;

		hG = GlobalAlloc(GHND|GMEM_NODISCARD, 0);
			
		if(hG == NULL)
			throw eDataAllocFails;
		
		_hmgr.SetHandle(&hG);

		ILockBytes * pLockBytes = NULL;
		
		HRESULT hr = ::CreateILockBytesOnHGlobal(
							hG,
							TRUE,
							&pLockBytes);  

		if(FAILED(hr))
			throw eStreamAllocFails;
		
		// Will be taken care of by the lockbytes
		_intmgr.SetInterface(pLockBytes, &IID_ILockBytes);
		
		_hmgr.RemoveHandle(&hG);
			

		hr = ::StgCreateDocfileOnILockBytes( pLockBytes, 
												 STGM_TRANSACTED | STGM_CREATE| STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
												 0,        
												 &pStorage  
												 );

		// Register this with the global interface manager. We need this around
		GetInterfaceManager().SetInterface(pStorage, &IID_IStorage);
	}
	catch(eViewerFlags& e )
	{
		switch (e)
		{
			case eBlankImage:
			
			case eInvalidData:
				TRACE0("OG Warning: Invalid data passed in to CGXGenericViewerImpl::Render\n");				
			case eDataAllocFails:
				TRACE0("OG Error: Data allocation in CGXGenericViewerImpl::Render fails\n");				
			case eInvalidOleStreamData:
				TRACE0("OG Error: An ole stream was available but was not recognized in CGXGenericViewerImpl::Render\n");		
			case eStreamAllocFails:
				TRACE0("OG Error: Unable to create Ole Stream in CGXGenericViewerImpl::Render\n");		
			default:
				TRACE0("OG Error: Unknown error in CGXGenericViewerImpl::Render\n");
		}
		// report to the user
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);
	}
	catch(...)
	{
		TRACE0("OG Error: Unknown error in CGXGenericViewerImpl::Render\n");
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);
	}


	OLEUIINSERTOBJECT oui;
	
	memset(&oui, 0, sizeof(OLEUIINSERTOBJECT));
	
	TCHAR pszFile[255];

	oui.cbStruct = sizeof(OLEUIINSERTOBJECT); 
	oui.dwFlags = IOF_SELECTCREATENEW | IOF_CREATENEWOBJECT;
	oui.hWndOwner = pGrid->GridWnd()->GetSafeHwnd(); 
	
	CString strCaption;
	strCaption.LoadString(GX_IDS_INSERTOBJCAPTION);
	oui.lpszCaption = strCaption;
	
	oui.lpfnHook = NULL; 
	oui.lCustData = NULL;
	oui.hInstance = NULL;
	oui.lpszTemplate = NULL;
	oui.hResource = NULL;
	oui.lpszFile = pszFile; 
	oui.cchFile = 255;
	oui.cClsidExclude = 0;
	oui.lpClsidExclude = NULL;
	oui.iid = IID_IOleObject;
	oui.lpIOleClientSite = GetClientSite();
	oui.lpIStorage = pStorage;
	oui.ppvObj = (void**)&pOleObject;

	UINT nRetval = ::OleUIInsertObject(&oui); 
	
	
	if(nRetval != OLEUI_SUCCESS || pOleObject == NULL)
	{
		oui.lpIOleClientSite->Release();
		Close();
		if(nRetval != OLEUI_CANCEL)
			AfxMessageBox(GX_IDS_OLEUIFAILED);
		TRACE1("GetLastError returns: %x\n", ::GetLastError);
		return FALSE;
	}

	MSG msg;
	
	HRESULT	hr = S_OK;
	
	if(FAILED(hr))
	{
		oui.lpIOleClientSite->Release();
		Close();
		return FALSE;
	}

	CGXOlePreview* pOlePreview = dynamic_cast<CGXOlePreview*>(GetActiveControl());

	if(pOlePreview == NULL)
	{
		Close();
		return FALSE;
	}

	hr = pOleObject->DoVerb(GetVerb(), &msg, oui.lpIOleClientSite, 0, pGrid->GridWnd()->GetSafeHwnd(), NULL); 
	
	pOleObject->AddRef();
	
	if(FAILED(hr))
	{
		Close();
		return FALSE;
	}
	
	GetInterfaceManager().SetInterface(pOleObject, &IID_IOleObject);

	ASSERT(m_dwAdviseCookie == NULL);

	hr = pOleObject->Advise(GetAdviseSink(), &m_dwAdviseCookie);
		
	if(FAILED(hr))
	{
		Close();
		return FALSE;
	}

	TRACE1("CreateNew IOleObject %x\n", pOleObject);

	return TRUE;
}

void CGXGenericViewerImpl::ActivateExisting()
{
	CGXOlePreview* pOlePreview = dynamic_cast<CGXOlePreview*>(GetActiveControl());

	if(pOlePreview == NULL || GetOleObject() == NULL)
		return;
	
	MSG msg;
	GetOleObject()->AddRef();
	pOlePreview->PreDoVerb();
	HRESULT hr = GetOleObject()->DoVerb(GetVerb(), &msg, NULL, 0, GetActiveControl()->Grid()->GridWnd()->GetSafeHwnd(), NULL); 
	GetOleObject()->Release();
		
	if(FAILED(hr))
	{
		// Tell the user what happened
		GX_FORMAT_MSG(hr);
		TRACE0("OG Error: IOleObject::DoVerb fails in CGXOlePreview::OnClickedButton\n");
		pOlePreview->PostDoVerb();
	}

	return;
}


HGLOBAL CGXGenericViewerImpl::AccessData(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl)
{
	USES_CONVERSION;
	
	GX_UNUSED_ALWAYS(pCtrl);
	GX_UNUSED_ALWAYS(pGrid);

	const COleVariant* pVar = NULL;

	if( ((LPCVARIANT)m_oleVariant)->vt != VT_EMPTY && ((LPCVARIANT)m_oleVariant)->vt != VT_NULL)
		pVar = &m_oleVariant;

	if( pVar == NULL)
	{
		if(pStyle->GetIncludeUserAttribute(GX_IDS_UA_DAOOLEBMP) )
			pVar = ( (const CGXOleVarUserAttribute&)pStyle->GetUserAttribute(GX_IDS_UA_DAOOLEBMP)).GetOleVarValue();
		else
			return NULL; // Blank...no image
	}

	const VARIANT* pV = (const VARIANT*) pVar; 
	
	if (pVar == NULL)
		return NULL; // Blank...no image
	
	if(pVar->vt == VT_EMPTY || pVar->vt == VT_NULL)
		return NULL;
	
	// Subclass Render and handle the data if it is some other form
	ASSERT(pV->vt == (VT_ARRAY|VT_UI1));

	unsigned long cDimLength = 0;
	BYTE* pBuffer = NULL;
	
	HGLOBAL hReadData = NULL;
	HRESULT hr = S_OK;

	try
	{

		if( pV->vt == (VT_ARRAY|VT_UI1) )  // (OLE SAFEARRAY)
		{
			//Retrieve size of array
			cDimLength = pV->parray->rgsabound[0].cElements;
			
			hReadData = ::GlobalAlloc(GHND | GMEM_NODISCARD, cDimLength);
			
			ASSERT(hReadData != NULL);

			if(hReadData == NULL)
				throw eDataAllocFails;

			pBuffer = (BYTE*)::GlobalLock(hReadData);
			
			ASSERT(pBuffer != NULL);

			if(pBuffer == NULL)
				throw eDataAllocFails;

			if(pBuffer != NULL)
			{
				void* pvArrayData = NULL;
					
				try
				{
					//Obtain safe pointer to the array
					hr = SafeArrayAccessData(pV->parray,&pvArrayData);
					
					ASSERT(!FAILED(hr));
					
					if(FAILED(hr))
						throw hr;

					//Copy the bitmap into our buffer
					memcpy(pBuffer, pvArrayData, cDimLength);
					
					//Unlock the variant data
					hr = SafeArrayUnaccessData(pV->parray);
					
					if(FAILED(hr))
						throw hr;

				}
				catch(...)
				{
					if(hReadData)
					{
						GlobalUnlock(hReadData);
						GlobalFree(hReadData);
						TRACE0("OG Errror: Safe array access fails in CGXGenericViewerImpl::Render\n");
						GX_THROW_LAST
						return NULL;
					}
				}

				GlobalUnlock(hReadData);
			}
	}
	else 
		{
			// not a blank and not valid data
			TRACE0("OG Error: Object data not in required format. CGXGenericViewerImpl::Render fails\n");
			AfxMessageBox(GX_IDS_ERRORBINDATA);
			return NULL;
		}
	}
	catch(eViewerFlags& e )
	{
		switch (e)
		{
			case eBlankImage:
			
			case eInvalidData:
				TRACE0("OG Warning: Invalid data passed in to CGXGenericViewerImpl::Render\n");				
			case eDataAllocFails:
				TRACE0("OG Error: Data allocation in CGXGenericViewerImpl::Render fails\n");				
			case eInvalidOleStreamData:
				TRACE0("OG Error: An ole stream was available but was not recognized in CGXGenericViewerImpl::Render\n");		
			case eStreamAllocFails:
				TRACE0("OG Error: Unable to create Ole Stream in CGXGenericViewerImpl::Render\n");		
			default:
				TRACE0("OG Error: Unknown error in CGXGenericViewerImpl::Render\n");
		}
		// report to the user
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);
	}
	catch(...)
	{
		TRACE0("OG Error: Unknown error in CGXGenericViewerImpl::Render\n");
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);
	}

	return hReadData;
}


IOleClientSite* CGXGenericViewerImpl::GetClientSite()
{
	return (IOleClientSite*) new CGXClientSite(this);
}

IAdviseSink* CGXGenericViewerImpl::GetAdviseSink()
{
	return  (IAdviseSink*) new CGXAdviseSink(this);
}


CGXInterfaceManager<IUnknown>& CGXGenericViewerImpl::GetInterfaceManager()
{
	return m_InterfaceMgr;
}

BOOL CGXGenericViewerImpl::SpawnViewer(HGLOBAL hReadData, CGXGridCore* pGrid,  BOOL bShow)
{
	
	CGXInterfaceManager<IUnknown> _intmgr;
	CGXHandleManager<HGLOBAL> _hmgr;
	
	LPOLE1STREAM lpOle1Stream= NULL;
	BOOL bRetval(TRUE);

	CGXOlePreview* pOlePreview = dynamic_cast<CGXOlePreview*>(GetActiveControl());

	if(pOlePreview == NULL)
		return FALSE;
	
	try
	{
		CLSID clsidObj;
		HRESULT hr = S_OK;
		
		_hmgr.SetHandle(&hReadData);

		// This part creates the OLE STREAM
		// call helper to read the header
		if( _GXReadAccessHeader( hReadData, &clsidObj) == FALSE)
			throw eInvalidOleStreamData;

		// skip the ACCESS header to get at the OLE object
		// NOTE: the returned HGLOBAL (without the header) 
		// will be deleted once the IStream is released
		DWORD dwObjectSize = 0;
		HGLOBAL	hgMemObject	= NULL;
		if(NULL == (hgMemObject = _GXSkipAccessHeader(hReadData, &dwObjectSize )) )
			throw eInvalidOleStreamData;
		
		_hmgr.SetHandle(&hgMemObject);

		// create an IStream on top of the ILockBytes 
		// (indicate automatic deletion of HGLOBAL on Release)
		// IMPORTANT: This IStream* (and therewith the memory
		// will be released during DeleteOleStream()
		LPSTREAM lpObjStream = NULL;
		
		if( FAILED( ::CreateStreamOnHGlobal( 
			hgMemObject, TRUE, &lpObjStream )))
			throw eStreamAllocFails;
		
		// The stream is to take care of this from here
		_hmgr.RemoveHandle(&hgMemObject);

		// convert the IStream to an IStorage ( ACCESS stores OLE Objects the OLE1 way)
		// in order to do so, we first have to wrap the OLE2 IStream into an OLE1 OLESTREAM
		// see MSDN Article: "More on Using Storage Objects in OLE"
		// NOTE: the Get() and Put() functions wrapped in the OLESTREAMVTBL will
		// access the newly opened stream using an IStream* variable
		if( NULL == ( lpOle1Stream = _GXCreateOle1Stream( lpObjStream, dwObjectSize )))
			throw eStreamAllocFails;
		
		// convert the OLE1 OLESTREAM to a valid IStorage* for loading the object
		// memory will grow as required
		HGLOBAL hG = NULL;

		hG = GlobalAlloc(GHND|GMEM_NODISCARD, 0);
		
		_hmgr.SetHandle(&hG);

		if(hG == NULL)
			throw eDataAllocFails;
	
		ILockBytes * pLockBytes = NULL;
		hr = ::CreateILockBytesOnHGlobal(
						hG,
						TRUE,
						&pLockBytes);  

		
		if(FAILED(hr))
			throw eStreamAllocFails;
	
		// Will be taken care of by the lockbytes
		GetInterfaceManager().SetInterface(pLockBytes, &IID_ILockBytes);
		_hmgr.RemoveHandle(&hG);
		

		LPSTORAGE pStorage = NULL;
		hr = ::StgCreateDocfileOnILockBytes( pLockBytes, 
											 STGM_TRANSACTED | STGM_CREATE| STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
											 0,        
											 &pStorage  
											 );

		// Register this with the global interface manager. We need this around
		GetInterfaceManager().SetInterface(pStorage, &IID_IStorage);

		if (FAILED(hr))
			throw hr;
	
		LPOLEOBJECT pOleObject = NULL;

		hr = ::CoCreateInstance(clsidObj, NULL, CLSCTX_LOCAL_SERVER, IID_IOleObject, (void**)&pOleObject);

		if (FAILED(hr))
			throw hr;
	
		GetInterfaceManager().SetInterface(pOleObject, &IID_IOleObject);

		if( FAILED ( hr = ::OleConvertOLESTREAMToIStorage(
			( LPOLESTREAM ) lpOle1Stream, pStorage, NULL )))
			throw hr;
	
		// Get the client site object
		IOleClientSite* pSite = NULL;
		pSite = GetClientSite();

		if(pSite == NULL)
			throw eNoClientSite;
	
		hr = pOleObject->SetClientSite(pSite);
	
		if(FAILED(hr))
			throw hr;
	
		IPersistStorage* pPersist = NULL;
	
		hr = pOleObject->QueryInterface(IID_IPersistStorage, (void**) &pPersist);

		_intmgr.SetInterface(pPersist, &IID_IPersistStorage);

		if(FAILED(hr))
			throw hr;
	
		hr = pPersist->Load(pStorage);

		if(FAILED(hr))
			throw hr;
	
		MSG msg;
		if(bShow)
			hr = pOleObject->DoVerb(GetVerb(), &msg, pSite, 0, pGrid->GridWnd()->GetSafeHwnd(), NULL); 
			
		if(FAILED(hr))
			throw hr;
	
		hr = pOleObject->Advise(GetAdviseSink(), &m_dwAdviseCookie);
		
		if(FAILED(hr))
			throw hr;
	}
	//
	catch(eViewerFlags& e )
	{
		switch (e)
		{
			case eNoClientSite:
				TRACE0("OG Warning: Unable to obtain client site in CGXGenericViewerImpl::SpawnViewer\n");				
				break;
			case eBlankImage:
				break;
			case eInvalidData:
				TRACE0("OG Warning: Invalid data passed in to CGXGenericViewerImpl::SpawnViewer\n");				
				break;
			case eDataAllocFails:
				TRACE0("OG Error: Data allocation in CGXGenericViewerImpl::SpawnViewer fails\n");				
				break;
			case eInvalidOleStreamData:
				TRACE0("OG Error: An ole stream was available but was not recognized in CGXGenericViewerImpl::SpawnViewer\n");		
				break;
			case eStreamAllocFails:
				TRACE0("OG Error: Unable to create Ole Stream in CGXGenericViewerImpl::SpawnViewer\n");		
				break;
			default:
				TRACE0("OG Error: Unknown error in CGXGenericViewerImpl::SpawnViewer\n");
			// report to the user
			TRACE1("GetLastError returns %x\n", GetLastError());
		}
		
		GetInterfaceManager().CleanObjects();
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);

		bRetval = FALSE;
	}
	catch(HRESULT& h)
	{
		GetInterfaceManager().CleanObjects();
		GX_FORMAT_MSG(h);
		bRetval = FALSE;

		GX_THROW_LAST
	}
	catch(...)
	{
		GetInterfaceManager().CleanObjects();
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);
		bRetval = FALSE;
	}

	// final clean up
	if(lpOle1Stream != NULL)
		_GXDeleteOleStream(lpOle1Stream);

	return bRetval;
}


void CGXGenericViewerImpl::SaveFromStorage()
{
	// use the earlier storage
	ASSERT(GetInterfaceManager().GetInterface(&IID_IStorage) != NULL);

	// Update the COleVariant
	//DWORD				dwObjectSize	= 0;
	DWORD				dwCheckSum		= 0;
	int					iHeaderSize		= 0;
	//int					nIDLast			= 1;
	
	ULARGE_INTEGER		ulStreamSize;
	DWORD dwlength = 0;
	
	HRESULT hr = S_OK;
	BYTE* pvData = NULL;

	LPOLE1STREAM lpOle1Stream = NULL;
	LPSTORAGE pStorage = (LPSTORAGE) GetInterfaceManager().GetInterface(&IID_IStorage);
	LPOLEOBJECT pOleObject = (LPOLEOBJECT) GetInterfaceManager().GetInterface(&IID_IOleObject);
	
	if(pStorage == NULL || pOleObject == NULL)
		return;
	
	SAFEARRAY* psa = NULL;

	CGXInterfaceManager<IUnknown> _intmgr;
	CGXHandleManager<HGLOBAL> _hmgr;
	
	try
	{
		// allocate enough memory to write access header to
		HGLOBAL	hgAccessHeader = NULL;
		if( NULL == ( hgAccessHeader = GlobalAlloc( 
			GMEM_MOVEABLE, sizeof( OLEOBJHDR ) + 100 )))
				throw eDataAllocFails;
			
		// In case something goes wrong
		_hmgr.SetHandle(&hgAccessHeader);

		// write the access-header
		if( 0 == ( iHeaderSize = _GXWriteAccessHeader(hgAccessHeader, pOleObject ) ) )
			throw eDataWriteFails;

		_hmgr.RemoveHandle(&hgAccessHeader);
		
		// adjust size of memory-block according to WriteAccessHeader()
		if( NULL == ( hgAccessHeader = GlobalReAlloc( 
			hgAccessHeader, iHeaderSize, GMEM_MOVEABLE )))
			throw eDataAllocFails;
	
		_hmgr.SetHandle(&hgAccessHeader);


		// Alloc the memory to store the long binary
		// NOTE: we allocate zero bytes since the IStream* created on top
		//		 of the HGLOBAL will automatically adjust the HGLOBAL's size
		HGLOBAL	hgMemObject	= NULL;
		if( NULL == ( hgMemObject = GlobalAlloc( 
			GMEM_MOVEABLE | GMEM_DDESHARE, 0 )))
			throw eDataAllocFails;

		_hmgr.SetHandle(&hgMemObject);

		// create an IStream on top of the ILockBytes 
		// (indicate automatic deletion of HGLOBAL on Release)
		// IMPORTANT: This IStream* (and therewith the memory
		//			  will be released during DeleteOleStream()
		LPSTREAM lpObjStream = NULL;
		if( FAILED( ::CreateStreamOnHGlobal( hgMemObject, TRUE, &lpObjStream )))
			throw eStreamAllocFails;
	
		// will be released by the stream
		_hmgr.RemoveHandle(&hgMemObject);

		// register this interface
		_intmgr.SetInterface(lpObjStream, &IID_IStream);
		
		// convert the IStream to an IStorage ( ACCESS stores OLE Objects the OLE1 way)
		// in order to do so, we first have to wrap the OLE2 IStream into an OLE1 OLESTREAM
		// see MSDN Article: "More on Using Storage Objects in OLE"
		// NOTE: the Get() and Put() functions wrapped in the OLESTREAMVTBL will
		//		 access the newly opened stream using an IStream* variable
		if( NULL == ( lpOle1Stream = _GXCreateOle1Stream( lpObjStream, 0  )))
			throw eStreamAllocFails;

		_intmgr.RemoveInterface(&IID_IStream);

		// convert the client-item's IStorage* to an OLE1 OLESTREAM
		// NOTE: as soon as the stream gets converted, the data will be written
		//		 to the IStream* and thereby to the HGLOBAL (see Put() function)
	
		if( FAILED ( ::OleConvertIStorageToOLESTREAM(
		pStorage, ( LPOLESTREAM ) lpOle1Stream )))
			throw hr;

		// adjust stream's size to reflect exactly the amount of bytes written to it
		ulStreamSize.LowPart = lpOle1Stream->dwSize;
		ulStreamSize.HighPart = 0;
		if( FAILED ( lpOle1Stream->lpStream->SetSize( ulStreamSize )))
			throw eStreamAllocFails;

		// allocate a new memory handle which is large enough to hold the
		// Access header, the OLE1 OLESTREAM containing the object and the checksum
		HGLOBAL	hgNewLongBinary	= NULL;
		if( NULL == ( hgNewLongBinary = GlobalAlloc( 
			GHND, iHeaderSize + lpOle1Stream->dwSize + sizeof( DWORD ))))
				throw eDataAllocFails;

		LPBYTE	lpbMemObject	= NULL;
		LPBYTE	lpbAccessHeader	= NULL;
		LPBYTE	lpbNewLongBinary= NULL;
	
		// and copy the complete information into it
		if( NULL == ( lpbAccessHeader = ( LPBYTE ) GlobalLock( hgAccessHeader )))
			throw eDataAllocFails;

		if( NULL == ( lpbMemObject = ( LPBYTE ) GlobalLock( hgMemObject )))
		{
			::GlobalUnlock(hgAccessHeader);
			throw eDataAllocFails;
		}

		if( NULL == ( lpbNewLongBinary = ( LPBYTE ) GlobalLock( hgNewLongBinary )))
		{
			::GlobalUnlock(hgAccessHeader);
			::GlobalUnlock(hgMemObject);
			throw eDataAllocFails;
		}
	
		// do the copying of data
		memcpy( lpbNewLongBinary, lpbAccessHeader, iHeaderSize );
		lpbNewLongBinary += iHeaderSize;
		memcpy( lpbNewLongBinary, lpbMemObject, lpOle1Stream->dwSize );
		lpbNewLongBinary += lpOle1Stream->dwSize;
		memcpy( lpbNewLongBinary, &dwCheckSum, sizeof( DWORD ));
		lpbNewLongBinary += sizeof( DWORD );
	
		// Unlock memory
		GlobalUnlock( hgMemObject );
		GlobalUnlock( hgAccessHeader );
		GlobalUnlock( hgNewLongBinary );

		// set the blob length
		dwlength = iHeaderSize + lpOle1Stream->dwSize + sizeof( DWORD );

		// Update the COleVariant
		BYTE* pBuffer = NULL;
		pBuffer = (BYTE*) ::GlobalLock(hgNewLongBinary);

		ASSERT(pBuffer != NULL);
	

		if(pBuffer == NULL)
			throw eDataAllocFails; // So close!

		// Compose safe array 
		hr = S_OK;
		SAFEARRAYBOUND rgsabound[1];  
		rgsabound[0].lLbound = 0;

	
		rgsabound[0].cElements = dwlength;
    
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		
		if(psa == NULL)
			throw eDataAllocFails; // So close!

		pvData = NULL;

		hr = SafeArrayAccessData(psa, (void**)&pvData);
	
		if(FAILED(hr))
		{
			SafeArrayDestroy(psa);
			throw hr;
		}

		memcpy(pvData, pBuffer, dwlength);
	
		hr = SafeArrayUnaccessData(psa );
 
		if(FAILED(hr))
		{
			SafeArrayDestroy(psa);
			throw hr;
		}
	}
	catch(eViewerFlags& e )
	{
		switch (e)
		{
			case eNoClientSite:
				TRACE0("OG Warning: Unable to obtain client site in CGXGenericViewerImpl::SaveFromStorage\n");				
				break;
			case eBlankImage:
				break;
			case eInvalidData:
				TRACE0("OG Warning: Invalid data passed in to CGXGenericViewerImpl::SaveFromStorage\n");				
				break;
			case eDataAllocFails:
				TRACE0("OG Error: Data allocation in CGXGenericViewerImpl::SaveFromStorage fails\n");				
				break;
			case eDataWriteFails:
				TRACE0("OG Error: Data write in CGXGenericViewerImpl::SaveFromStorage fails\n");				
				break;
			case eInvalidOleStreamData:
				TRACE0("OG Error: An ole stream was available but was not recognized in CGXGenericViewerImpl::SaveFromStorage\n");		
				break;
			case eStreamAllocFails:
				TRACE0("OG Error: Unable to create Ole Stream in CGXGenericViewerImpl::SaveFromStorage\n");		
				break;
			default:
				TRACE0("OG Error: Unknown error in CGXGenericViewerImpl::SaveFromStorage\n");
			// report to the user
			TRACE1("GetLastError returns %x\n", GetLastError());
		}
		
		GetInterfaceManager().CleanObjects();
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);
	}
	catch(HRESULT& h)
	{
		GetInterfaceManager().CleanObjects();
		GX_FORMAT_MSG(h);
		
		GX_THROW_LAST
	}
	catch(...)
	{
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);
	}

	// final clean up
	if(lpOle1Stream != NULL)
		_GXDeleteOleStream( lpOle1Stream );

	// hold the array till store is called
	VARIANT var;
	var.vt = VT_ARRAY|VT_UI1;
	var.parray = psa;
	
	m_oleVariant.Clear();
	m_oleVariant.Attach(var); 
	
	ASSERT(GetActiveControl() != NULL);

	GetActiveControl()->SetModify(TRUE);
}

void CGXGenericViewerImpl::Close()
{
	HRESULT hr = S_OK;
	
	LPOLEOBJECT pOleObject = (LPOLEOBJECT) GetInterfaceManager().GetInterface(&IID_IOleObject);
	
	if(pOleObject != NULL)
		pOleObject->Unadvise(m_dwAdviseCookie);

	m_dwAdviseCookie = NULL;

	if(pOleObject != NULL)
		hr = pOleObject->Close(OLECLOSE_SAVEIFDIRTY);
	
	if(FAILED(hr))
		GX_FORMAT_MSG(hr);

	if(pOleObject != NULL)
		GetInterfaceManager().RemoveInterface(&IID_IOleObject);

	GetInterfaceManager().CleanObjects();
	
	CGXOlePreview* pOlePreview = dynamic_cast<CGXOlePreview*>(GetActiveControl());

	if(pOlePreview == NULL)
		return;

	pOlePreview->PostDoVerb();
}

void CGXGenericViewerImpl::Clear()
{
	if( ((LPCVARIANT)m_oleVariant)->vt != VT_EMPTY && ((LPCVARIANT)m_oleVariant)->vt != VT_NULL)
		m_oleVariant.Clear();

	// ASSERT(GetInterfaceManager().GetInterface(&IID_IOleObject) == NULL);
	
	GetInterfaceManager().CleanObjects();
}


COleVariant& CGXGenericViewerImpl::GetData()
{
	return m_oleVariant;
}

LPSTORAGE CGXGenericViewerImpl::GetStorage()
{
	return (LPSTORAGE) GetInterfaceManager().GetInterface(&IID_IStorage);
}

LPOLEOBJECT CGXGenericViewerImpl::GetOleObject()
{
	return (LPOLEOBJECT) GetInterfaceManager().GetInterface(&IID_IOleObject);
}

BOOL CGXGenericViewerImpl::CanPaste()
{
	IDataObject* pDataObj = NULL;
	HRESULT hr =  ::OleGetClipboard(&pDataObj);
	
	if(FAILED(hr))
		return FALSE;
	
	pDataObj->Release();

	return TRUE;
}

COleVariant* CGXGenericViewerImpl::Paste()
{
	IDataObject* pDataObj = NULL;
	HRESULT hr =  ::OleGetClipboard(&pDataObj);
	
	if(FAILED(hr))
		return FALSE;

	LPOLEOBJECT pObject = NULL;

	CGXInterfaceManager<IUnknown> _intmgr;
	CGXHandleManager<HGLOBAL> _hmgr;
	
	// Create the Storage 
	try
	{
		HGLOBAL hG = NULL;

		hG = GlobalAlloc(GHND|GMEM_NODISCARD, 0);
			
		_hmgr.SetHandle(&hG);

		if(hG == NULL)
			throw eDataAllocFails;
		
		ILockBytes * pLockBytes = NULL;
		hr = ::CreateILockBytesOnHGlobal(
							hG,
							TRUE,
							&pLockBytes);  

			
		if(FAILED(hr))
			throw eStreamAllocFails;
		
		// Will be taken care of by the lockbytes
		// GetInterfaceManager().SetInterface(pLockBytes, &IID_ILockBytes);
		
		_hmgr.RemoveHandle(&hG);
			

		LPSTORAGE pStorage = NULL;
		hr = ::StgCreateDocfileOnILockBytes( pLockBytes, 
												 STGM_TRANSACTED | STGM_CREATE| STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
												 0,        
												 &pStorage  
												 );

		if (FAILED(hr))
			throw hr;
		
		
		// Register this with the global interface manager. We need this around
		GetInterfaceManager().SetInterface(pStorage, &IID_IStorage);

		
		IOleClientSite* pClientSite = GetClientSite();

		hr = OleCreateFromData(
		pDataObj,
		IID_IOleObject,
		OLERENDER_NONE,
		NULL,
		pClientSite,
		pStorage,
		(void**)&pObject);
		
		if(FAILED(hr))
		{
			if(pClientSite)
				pClientSite->Release();
			throw hr;
		}

		// set up the interface manager
		GetInterfaceManager().SetInterface(pObject, &IID_IOleObject);
		
		pDataObj->Release();

		// save this to the current variant
		SaveFromStorage();
	
		// return intrinsic data
		return &m_oleVariant;
	}	
	catch(eViewerFlags& e )
	{
		switch (e)
		{
			case eNoClientSite:
				TRACE0("OG Warning: Unable to obtain client site in CGXGenericViewerImpl::SaveFromStorage\n");				
				break;
			case eBlankImage:
				break;
			case eInvalidData:
				TRACE0("OG Warning: Invalid data passed in to CGXGenericViewerImpl::SaveFromStorage\n");				
				break;
			case eDataAllocFails:
				TRACE0("OG Error: Data allocation in CGXGenericViewerImpl::SaveFromStorage fails\n");				
				break;
			case eDataWriteFails:
				TRACE0("OG Error: Data write in CGXGenericViewerImpl::SaveFromStorage fails\n");				
				break;
			case eInvalidOleStreamData:
				TRACE0("OG Error: An ole stream was available but was not recognized in CGXGenericViewerImpl::SaveFromStorage\n");		
				break;
			case eStreamAllocFails:
				TRACE0("OG Error: Unable to create Ole Stream in CGXGenericViewerImpl::SaveFromStorage\n");		
				break;
			default:
				TRACE0("OG Error: Unknown error in CGXGenericViewerImpl::SaveFromStorage\n");
			// report to the user
			TRACE1("GetLastError returns %x\n", GetLastError());
		}
		GetInterfaceManager().CleanObjects();
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);
	}
	catch(HRESULT& h)
	{
		GetInterfaceManager().CleanObjects();
		GX_FORMAT_MSG(h);

		GX_THROW_LAST
	}
	catch(...)
	{
		GX_THROW_LAST
		AfxMessageBox(GX_IDS_ERRORBINDATA);
	}
	return NULL;
}

BOOL CGXGenericViewerImpl::CanCopy()
{
	return CanCopyCanCutHelper();
}

// Helper for CanCopy/CanCut
BOOL CGXGenericViewerImpl::CanCopyCanCutHelper()
{
	// check current data
	LPCVARIANT var  = (LPCVARIANT)m_oleVariant;
	if(var->vt == (VT_ARRAY | VT_UI1))
		return TRUE;
	else
		return FALSE;
}
	
IDataObject* CGXGenericViewerImpl::Copy(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl)
{
	HGLOBAL hReadData = AccessData(pStyle, pGrid, pCtrl);
	
	SetActiveControl(pCtrl);
	SpawnViewer(hReadData, pGrid, FALSE);

	IOleObject* pOleObject = GetOleObject();
	
	// ASSERT(pOleObject != NULL);

	if(pOleObject == NULL)
		return NULL;

	LPDATAOBJECT pDataObject = NULL;
	HRESULT hr = pOleObject->GetClipboardData(0, &pDataObject);
	
	// we rely on GetClipboard data. If this is not implemented we cannot do a copy
	if(FAILED(hr))
	{
		TRACE0("Copy operation fails. IOleObject::GetClipboardData fails in CGXGenericViewerImpl::Copy\n");
		GX_FORMAT_MSG(hr);
		// Grid Error message
		AfxMessageBox(GX_IDS_OLECOPYFAILED);
		Close();
	}
	
	SetActiveControl(NULL);
	return pDataObject;
}
	
BOOL CGXGenericViewerImpl::CanCut()
{
	return CanCopyCanCutHelper();
}
	
IDataObject* CGXGenericViewerImpl::Cut(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl)
{
	IDataObject* pDataObject = Copy(pStyle, pGrid, pCtrl);
	
	m_oleVariant.Clear();
	
	ASSERT(pCtrl != NULL);

	pCtrl->SetModify(TRUE);
	
	return pDataObject;
}

#endif
