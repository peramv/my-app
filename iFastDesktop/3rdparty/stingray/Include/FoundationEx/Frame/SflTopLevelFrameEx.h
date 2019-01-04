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
#if !defined __SFLTOPLEVELFRAMEEX__H__
#define __SFLTOPLEVELFRAMEEX__H__

#include "StingrayExportDefs.h"
#include "FoundationEx\Frame\SFLFrameWndEx.h"

namespace sflex
{

// SFLTopLevelFrameEx frame

class SFLTopLevelFrameEx : public SFLFrameWndEx
{
	FOUNDATIONEX_DECLARE_DYNCREATE(SFLTopLevelFrameEx)
protected:
	// Construction -----------------------------//
	FOUNDATIONEX_API SFLTopLevelFrameEx();
	FOUNDATIONEX_API virtual ~SFLTopLevelFrameEx();

public:
	//------------------------------------------------//
	// These functions required as a workaround to    //
	// properly import/export static member data      //
	// s_tlfList across DLL boundary.                 //
	//------------------------------------------------//

	// Get the list of top level frames.
	FOUNDATIONEX_API void GetCopyTLFList(CObList& rList);
	// Set the list of top level frames.
	FOUNDATIONEX_API void SetTLFList(CObList& rNewList);
	// Get a copy of the list of top level frames.
	FOUNDATIONEX_API static void GetCopyTLFListStatic(CObList& rList);
	// Set a static copy of the list of top level frames.
	FOUNDATIONEX_API static void SetTLFListStatic(CObList& rNewList);
	// Load the frame.
	FOUNDATIONEX_API virtual BOOL LoadFrame(UINT nIDResource, 
										  DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, 
										  CWnd* pParentWnd = NULL, 
										  CCreateContext* pContext = NULL);
   
protected:
	FOUNDATIONEX_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    FOUNDATIONEX_API afx_msg void OnWindowNew();
    FOUNDATIONEX_API afx_msg void OnClose();
	FOUNDATIONEX_API afx_msg void OnNcDestroy();
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected:
	// List of top level frames.
	FOUNDATIONEX_API static CObList s_tlfList;
};

} // namespace sflex

#endif // __SFLTOPLEVELFRAMEEX__H__
