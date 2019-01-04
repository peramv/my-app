///////////////////////////////////////////////////////////////////////////////
// gxwait.cpp : implementation of the CGXLongOperation class
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

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXWAIT")
#endif

#ifdef _DEBUG
#undef THIS_FILE
#define new DEBUG_NEW
static char THIS_FILE[] = __FILE__;
#endif

// CGXAbstractLongOperationImp* m_pLongOperationImp;

class CGXLongOperationImp: public CGXAbstractLongOperationImp
{
public:
	virtual void Start(CGXLongOperation* pTheOp);
	virtual void Stop(CGXLongOperation* pTheOp);
	virtual void FreeStatusText(CGXLongOperation* pTheOp);
	virtual void SetStatusText(CGXLongOperation* pTheOp, LPCTSTR pszText, BOOL bCopyBuffer);
	virtual BOOL DoMessages(CGXLongOperation* pTheOp);
	virtual BOOL DoMessages(CGXLongOperation* pTheOp, BOOL& bAbort);
	virtual void ProcessMessages(CGXLongOperation* pTheOp);
};

void AFXAPI CGXLongOperation::ImplementLongOperation()
{
	if (GXGetAppData()->m_pLongOperationImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pLongOperationImp = new CGXLongOperationImp);
		GXGetAppData()->m_pLongOperationImp = new CGXLongOperationImp;
	}
}

//

/////////////////////////////////////////////////////////////////////////////
// CGXLongOperation

void CGXLongOperationImp::Start(CGXLongOperation* pTheOp)
{
	GX_WAIT_STATE* pWaitState = GXGetWaitState();

	if (pWaitState->m_nRefCount++ == 0)
	{
		// statics
		pWaitState->m_bCanceled = FALSE;
		pWaitState->m_bWaitCursor = FALSE;
		pWaitState->m_nLevelLocked = -1;
		pWaitState->m_nPercentDone = -1;
		pWaitState->m_bCanAbort = TRUE;
		pWaitState->m_bCanRollback = FALSE;

		// members
		pTheOp->SetStatusText(pWaitState->m_sDefaultStatusText, FALSE);

		if (pWaitState->m_hFrameWnd == NULL || !::IsWindow(pWaitState->m_hFrameWnd))
		{
			pWaitState->m_hFrameWnd = NULL;
			CWnd* pWnd = AfxGetMainWnd();
			if (pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
				pWaitState->m_hFrameWnd = AfxGetMainWnd()->GetSafeHwnd();
		}
	}
	else
		pTheOp->SetStatusText(pWaitState->m_apszStatusText[pTheOp->GetCurrentLevel()-1], FALSE);

	pWaitState->m_bUserConfirmed = FALSE;
	pWaitState->m_bRollbackConfirmed = FALSE;

	// member
	pTheOp->m_nTickStart = ::GetTickCount();
	pTheOp->m_nLastTick = pTheOp->m_nTickStart;

	pTheOp->m_bResetStatusBar = TRUE;
	pTheOp->m_bUpdateStatusBar = TRUE;

	// TRACE(_T("Incremented operation counter = %d\n"), m_nRefCount);
}

void CGXLongOperationImp::Stop(CGXLongOperation* pTheOp)
{
	GX_WAIT_STATE* pWaitState = GXGetWaitState();

	//---------------------------------------------- 
	// QA: 32120 
	// Assert caused by global variables  
	// from multiple instances of Grid,  
	// statically linked in an OCX or DLL, 
	// within a multi-threaded environment. 
	// See GXSTATE.h for CThreadLocal<...> updates. 
	//---------------------------------------------- 
	ASSERT(pWaitState->m_nRefCount > 0);

	pTheOp->FreeStatusText();

	--pWaitState->m_nRefCount;
	// TRACE(_T("Decremented operation counter = %d\n"), m_nRefCount);
	if (pWaitState->m_nRefCount == 0)
	{
		if (pWaitState->m_bWaitCursor)
		{
			AfxGetApp()->EndWaitCursor();

			if (pTheOp->m_bResetStatusBar)
			{
				if (pWaitState->m_hFrameWnd && ::IsWindow(pWaitState->m_hFrameWnd))
					CWnd::FromHandle(pWaitState->m_hFrameWnd)->SendMessage(WM_SETMESSAGESTRING, 0, (LPARAM)(LPCTSTR)pWaitState->m_sDefaultDoneText);
			}
		}
	}
}

#if !defined(_AFXDLL) && !defined(_WINDLL)
CString CGXLongOperation::GetStrFTime(LPTSTR f) const
{
	if (f == NULL)
		f = _T("%H:%M:%S");
	long seconds = (::GetTickCount()-m_nTickStart)/1000L;
#if defined(_UNICODE) && _MFC_VER < 0x0400
	char astring[64];

	WideCharToMultiByte (CP_ACP, 0, f, -1,
						astring, 64, NULL, NULL);

	return CTimeSpan(seconds).Format(astring);
#else
	return CTimeSpan(seconds).Format(f);
#endif
}
#endif

void CGXLongOperationImp::FreeStatusText(CGXLongOperation* pTheOp)
{
	GX_UNUSED_ALWAYS(pTheOp);

	GX_WAIT_STATE* pWaitState = GXGetWaitState();

	int i = pTheOp->GetCurrentLevel();
	if (i < gxnMaxWaitLevel && pWaitState->m_abOwnStatusText[i])
	{
		LPTSTR p = (LPTSTR) pWaitState->m_apszStatusText[i];
		delete p;
		pWaitState->m_apszStatusText[i] = NULL;
		pWaitState->m_abOwnStatusText[i] = FALSE;
	}
}

void CGXLongOperationImp::SetStatusText(CGXLongOperation* pTheOp, LPCTSTR pszText, BOOL bCopyBuffer)
{
	GX_WAIT_STATE* pWaitState = GXGetWaitState();

	// delete current text
	pTheOp->FreeStatusText();

	if (!pTheOp->GetLockedState())  // Do I have the right to change the status text?
	{
		if (bCopyBuffer)
		{
			LPTSTR s = new TCHAR[_tcslen(pszText)+1];
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(s, pszText);
			pWaitState->m_apszStatusText[pTheOp->GetCurrentLevel()] = pTheOp->m_pszStatusText = s;
			pWaitState->m_abOwnStatusText[pTheOp->GetCurrentLevel()] = TRUE;
		}
		else
		{
			pWaitState->m_apszStatusText[pTheOp->GetCurrentLevel()] = pTheOp->m_pszStatusText = pszText;
			pWaitState->m_abOwnStatusText[pTheOp->GetCurrentLevel()] = FALSE;
		}
	}
}

BOOL CGXLongOperationImp::DoMessages(CGXLongOperation* pTheOp)
{
	GX_WAIT_STATE* pWaitState = GXGetWaitState();

	DWORD dwTick = ::GetTickCount();

	if (!pWaitState->m_bWaitCursor)
	{
		if (dwTick - pTheOp->m_nTickStart < pWaitState->m_dwTicksFirstTime)
			return FALSE;
	}
	else if (dwTick - pTheOp->m_nLastTick < pWaitState->m_dwTicksContinued)
		return FALSE;

	if (pTheOp->m_bUpdateStatusBar && !pTheOp->GetLockedState())
	{
		if (pWaitState->m_hFrameWnd && ::IsWindow(pWaitState->m_hFrameWnd))
		{
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(pWaitState->m_szStatusBuf, pTheOp->GetStatusText());
			if (pWaitState->m_nPercentDone != -1)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_stprintf(pWaitState->m_szStatusBuf +
					_tcsclen(pWaitState->m_szStatusBuf),
					_T(" %3d%%. "),
					pWaitState->m_nPercentDone);
					
			}else
			{
				LPTSTR p = pWaitState->m_szStatusBuf+_tcslen(pWaitState->m_szStatusBuf);
				switch(pWaitState->m_nIndicatorState++)
				{
				// QA: 31989 - #if Secure Code Cleanup.
				case 0: _tcscpy(p, _T("  -")); break;
				case 1: _tcscpy(p, _T("  \\")); break;
				case 2: _tcscpy(p, _T("  |")); break;
				case 3: _tcscpy(p, _T("  /")); pWaitState->m_nIndicatorState = 0; break;		
				}
			}

			CWnd::FromHandle(pWaitState->m_hFrameWnd)->SendMessage(WM_SETMESSAGESTRING, 0, (LPARAM)(LPVOID)pWaitState->m_szStatusBuf);
		}
	}

	// Process Messages
	pTheOp->ProcessMessages();

	pTheOp->m_nLastTick = dwTick;

	return TRUE;
}

BOOL CGXLongOperationImp::DoMessages(CGXLongOperation* pTheOp, BOOL& bAbort)
{
	GX_WAIT_STATE* pWaitState = GXGetWaitState();

	DWORD dwTick = ::GetTickCount();
	bAbort = FALSE;

	if (!pWaitState->m_bWaitCursor)
	{
		if (dwTick - pTheOp->m_nTickStart < pWaitState->m_dwTicksFirstTime)
			return FALSE;
	}
	else if (dwTick - pTheOp->m_nLastTick < pWaitState->m_dwTicksContinued)
		return FALSE;

	if (pTheOp->m_bUpdateStatusBar && !pTheOp->GetLockedState())
	{
		if (pWaitState->m_hFrameWnd && ::IsWindow(pWaitState->m_hFrameWnd))
		{
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(pWaitState->m_szStatusBuf, pTheOp->GetStatusText());
			if (pWaitState->m_nPercentDone != -1)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_stprintf(pWaitState->m_szStatusBuf +
					_tcsclen(pWaitState->m_szStatusBuf),
					_T(" %3d%%. "),
					pWaitState->m_nPercentDone);
			}
			if (pWaitState->m_bCanAbort)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_tcscat(pWaitState->m_szStatusBuf, _T("   "));  // Add some space between
				_tcscat(pWaitState->m_szStatusBuf, pWaitState->m_sDefaultCancelText);				
			}

			if (pWaitState->m_nPercentDone == -1)
			{
				LPTSTR p = pWaitState->m_szStatusBuf+_tcslen(pWaitState->m_szStatusBuf);
				switch(pWaitState->m_nIndicatorState++)
				{
				// QA: 31989 - #if Secure Code Cleanup.
				case 0: _tcscpy(p, _T("  -")); break;
				case 1: _tcscpy(p, _T("  \\")); break;
				case 2: _tcscpy(p, _T("  |")); break;
				case 3: _tcscpy(p, _T("  /")); pWaitState->m_nIndicatorState = 0; break;
				}
			}

			CWnd::FromHandle(pWaitState->m_hFrameWnd)->SendMessage(WM_SETMESSAGESTRING, 0, (LPARAM)(LPVOID)pWaitState->m_szStatusBuf);

		}
	}

	// Process Messages
	pTheOp->ProcessMessages();

	// Display abort dialog if m_sMessage is set
	if (pWaitState->m_bCanAbort && pWaitState->m_bCanceled && !pWaitState->m_bUserConfirmed)

	{
		if (!pWaitState->m_bAbortDialog)     // no abort dialog
		{
			pWaitState->m_bUserConfirmed = TRUE;
			pWaitState->m_bRollbackConfirmed = pWaitState->m_bCanRollback;
		}
		else
		{
			if (pWaitState->m_bCanRollback)
			{
				int nIDPressed =
					AfxMessageBox(pWaitState->m_sAbortText, MB_ABORTRETRYIGNORE);

				switch (nIDPressed)
				{
				case IDRETRY:
					pWaitState->m_bRollbackConfirmed = TRUE;
					// *** Fall through ***
				case IDABORT:
					pWaitState->m_bUserConfirmed = TRUE;
					break;
				}
			}
			else
				pWaitState->m_bUserConfirmed = AfxMessageBox(pWaitState->m_sAbortText, MB_YESNO) == IDYES;
			pWaitState->m_bCanceled = FALSE;
		}

		bAbort = pWaitState->m_bUserConfirmed;
	}

	pTheOp->m_nLastTick = dwTick;
	return TRUE;
}

// Implementation

void CGXLongOperationImp::ProcessMessages(CGXLongOperation* pTheOp)
{
	GX_UNUSED_ALWAYS(pTheOp);

	GX_WAIT_STATE* pWaitState = GXGetWaitState();

	if (!pWaitState->m_bWaitCursor)
	{
		AfxGetApp()->BeginWaitCursor();
		pWaitState->m_bWaitCursor = TRUE;
	}

    MSG msg;
    //
    // QA 31956
    // It is NOT guaranteed that the message inspected by PM_NOREMOVE is the same message 
    // removed by the commented out ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) call below.
    // Refer to http://msdn2.microsoft.com/en-us/library/ms644943.aspx for ::PeekMessage() details
    //
    // Inspect incoming messages
    while ( ::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
    { 
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.wParam == VK_ESCAPE || msg.wParam == VK_CANCEL)
					pWaitState->m_bCanceled = TRUE;
			}

			// Range of interest
			if (	msg.message >= WM_KEYFIRST    && msg.message <= WM_KEYLAST
			   || msg.message >= WM_MOUSEFIRST  && msg.message <= WM_MOUSELAST
			   || msg.message >= WM_NCMOUSEMOVE && msg.message <= WM_NCMBUTTONDBLCLK
			   || msg.message == WM_COMMAND )
			{
				AfxGetApp()->RestoreWaitCursor();
				// begin QA 31956
				// Original ::PeekMessage() call
				//::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ); 
				
				// Rogue Wave suggested fix:
                                // This suggested fix seems to have better response time and cleanup
				::PeekMessage( &msg, NULL, msg.message, msg.message, PM_REMOVE );

				// Microsoft suggested fix:
				// Make sure we only remove messages from the message queue that are in the range of interest
				//::PeekMessage( &msg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE );
				//::PeekMessage( &msg, NULL, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE );
				//::PeekMessage( &msg, NULL, WM_NCMOUSEMOVE, WM_NCMBUTTONDBLCLK, PM_REMOVE );
				//::PeekMessage( &msg, NULL, WM_COMMAND, WM_COMMAND, PM_REMOVE );
				// end QA 31956
				continue;
			}

#if _MFC_VER >= 0x0400
      if ( !AfxGetThread()->PumpMessage( ) ) 
      { 
          ::PostQuitMessage(0); 
          break; 
      } 
#else
			if (!AfxGetApp()->PreTranslateMessage(&msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
#endif
		} // end while

    // let MFC do its idle processing
    LONG lIdle = 0;
    while ( AfxGetApp()->OnIdle(lIdle++ ) )
        ;  
}

