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
#if !defined __SFLCHILDTOOLBAREX__H__
#define __SFLCHILDTOOLBAREX__H__

#include "StingrayExportDefs.h"
#include "FoundationEx\UI\SFLToolBarEx.h"

namespace sflex
{

// SFLChildToolBarEx

template<class T> // Type used in AdjustLayout().
class SFLChildToolBarEx : public SFLToolBarEx
{
public:
	// Construction -----------------------------//
	inline SFLChildToolBarEx();
	inline virtual ~SFLChildToolBarEx();

	// Create. Override to provide any addition custom creation functionality.
	inline virtual BOOL Create(CWnd* pParentWnd, DWORD dwStyle = AFX_DEFAULT_TOOLBAR_STYLE, UINT nID = 59392);
	// All commands should be routed via owner window, not via frame:
	inline virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler); 

	// Layout -----------------------------------//
	// Adjust the layout with parent.
	inline virtual void AdjustLayout();

protected:
	DECLARE_MESSAGE_MAP()
};

template<class T>
SFLChildToolBarEx<T>::SFLChildToolBarEx()
{
}

template<class T>
SFLChildToolBarEx<T>::~SFLChildToolBarEx()
{
}


BEGIN_TEMPLATE_MESSAGE_MAP(SFLChildToolBarEx, T, SFLToolBarEx)
END_MESSAGE_MAP()

// SFLChildToolBarEx message handlers

template<class T>
BOOL SFLChildToolBarEx<T>::Create(CWnd* pParentWnd, DWORD dwStyle /*= AFX_DEFAULT_TOOLBAR_STYLE*/, UINT nID /*= 59392*/)
{
	if(!SFLToolBarEx::Create(pParentWnd, dwStyle, nID))
	{
		return FALSE;
	}
	// The parent frame owns this toolbar.
	SetOwner(pParentWnd);
	// All commands will be routed via this control , not via the parent frame.
	SetRouteCommandsViaFrame(FALSE);
	// Remove some styles.
	SetPaneStyle(GetPaneStyle() & ~(CBRS_GRIPPER       | 
									CBRS_SIZE_DYNAMIC  | 
									CBRS_BORDER_TOP    | 
									CBRS_BORDER_BOTTOM | 
									CBRS_BORDER_LEFT   | 
									CBRS_BORDER_RIGHT));
	
	return TRUE;
}

template<class T>
void SFLChildToolBarEx<T>::OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler) 
{ 
	// Get the owner as the target frame.
	SFLToolBarEx::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
}

template<class T>
void SFLChildToolBarEx<T>::AdjustLayout()
{
	// Base toolbar adjustment.
	SFLToolBarEx::AdjustLayout();
	// Adjust the layout for the parent.
	((T*)GetParent())->AdjustLayout();
}

} // namespace sflex

#endif // __SFLCHILDTOOLBAREX__H__
