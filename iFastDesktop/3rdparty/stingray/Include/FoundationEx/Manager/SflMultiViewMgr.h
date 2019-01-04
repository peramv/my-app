#if !defined __SFLMULTIVIEWMGR__H__
#define __SFLMULTIVIEWMGR__H__

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
#include "StingrayExportDefs.h"

namespace sflex
{

// SFLMultiViewMgr class

class SFLMultiViewMgr
{
public:
	FOUNDATIONEX_API SFLMultiViewMgr(void);
	FOUNDATIONEX_API virtual ~SFLMultiViewMgr(void);

public:
	// Initialize first view.
	FOUNDATIONEX_API virtual BOOL Initialize(CFrameWnd* pFrameWnd);
	// Get the list of views.
	inline CArray<CView*, CView*>& GetArrayViews() { return m_arrViews; }
	// Add a CView. Return should be the ID, greater than 0.
	FOUNDATIONEX_API virtual UINT AddView(CView* pView, UINT uiViewID);
	// Remove a CView by address.
	FOUNDATIONEX_API virtual BOOL RemoveView(CView* pView);
	// Remove a CView by ID.
	FOUNDATIONEX_API virtual BOOL RemoveView(UINT uiIndex);
	// Get view by ID. 0 based index.
	FOUNDATIONEX_API CView* GetView(UINT uiIndex);

	enum eViewIndex
	{
		MULTIVIEW_0 = 0,
		MULTIVIEW_1,
		MULTIVIEW_2,
		MULTIVIEW_3,
		MULTIVIEW_4,
		MULTIVIEW_5,
		MULTIVIEW_6,
		MULTIVIEW_7,
		MULTIVIEW_8,
		MULTIVIEW_9,
		MULTIVIEW_10,
		MULTIVIEW_11,
		MULTIVIEW_12,
		MULTIVIEW_13,
		MULTIVIEW_14,
		MULTIVIEW_15,
		MULTIVIEW_16,
		MULTIVIEW_17,
		MULTIVIEW_18,
		MULTIVIEW_19,
		MULTIVIEW_20,
		MULTIVIEW_MAX
	};

	// Get ID of current view.
	inline eViewIndex GetViewIndex() { return m_uiCurrentViewIndex; }
	// Switch view. 0 based index.
	FOUNDATIONEX_API void SwitchView(eViewIndex uiIndex);

protected:
	FOUNDATIONEX_API virtual void Cleanup();

protected:
	FOUNDATIONEX_API static CArray<CView*, CView*> m_arrViews;
	FOUNDATIONEX_API static eViewIndex m_uiCurrentViewIndex;
	FOUNDATIONEX_API static CFrameWnd* m_pFrameWnd;
};

} // namespace sflex

#endif // __SFLMULTIVIEWMGR__H__
