///////////////////////////////////////////////////////////////////////////////
// gxcrgnam.cpp : Named ranges (needed by formula engine)
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

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORCLP")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

class CGXGridRangeNameImp: public CGXAbstractGridRangeNameImp
{
public:
	virtual BOOL SetRangeName(CGXGridCore* pGrid, LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo, UINT flags, GXCmdType ctCmd);
	virtual BOOL GetRangeName(CGXGridCore* pGrid, LPCTSTR name, CGXRange& rg);
	virtual BOOL DeleteRangeName(CGXGridCore* pGrid, LPCTSTR name, CObject* pUndoInfo, GXCmdType ctCmd);
};

void CGXGridCore::ImplementRangeName()
{
	if (m_pRangeNameImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pRangeNameImp = new CGXGridRangeNameImp);
		m_pRangeNameImp = new CGXGridRangeNameImp;
	}
}

/*
	CGXAbstractGridRangeNameImp* m_pRangeNameImp;
	friend class CGXGridRangeNameImp;
	void EnableRangeName();
*/


BOOL CGXGridRangeNameImp::SetRangeName(CGXGridCore* pGrid, LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo, UINT flags, GXCmdType ctCmd)
{
	// Unused:
	flags;

	if (pGrid->IsReadOnly())
		return FALSE;

	CGXData* pData = pGrid->GetParam()->GetData();
	BOOL bCreateUndo = pGrid->m_pUndoImp && pGrid->m_pParam->m_bUndoEnabled && ctCmd != gxRollback;
	CGXRange oldRange;

	BOOL bOldRange = pGrid->GetRangeName(name, oldRange);

	BOOL bDone = pData->SetRangeName(name, rg, pUndoInfo);

	if (bDone)
	{
		pGrid->SetModifiedFlag();

		if (bCreateUndo && ctCmd != gxRollback)
			pGrid->AddCommand(pGrid->m_pUndoImp->CreateSetRangeNameCmd(name, bOldRange, oldRange), ctCmd);

		pGrid->RefreshViews(FALSE);

		return TRUE;
	}

	return FALSE;
}

BOOL CGXGridRangeNameImp::GetRangeName(CGXGridCore* pGrid, LPCTSTR name, CGXRange& rg)
{
	CGXData* pData = pGrid->GetParam()->GetData();

	return pData->GetRangeName(name, rg);
}

BOOL CGXGridRangeNameImp::DeleteRangeName(CGXGridCore* pGrid, LPCTSTR name, CObject* pUndoInfo, GXCmdType ctCmd)
{
	if (pGrid->IsReadOnly())
		return FALSE;

	CGXRange oldRange;
	if (!pGrid->GetRangeName(name, oldRange))
		return FALSE;	// nothing to delete

	CGXData* pData = pGrid->GetParam()->GetData();
	BOOL bCreateUndo = pGrid->m_pUndoImp && pGrid->m_pParam->m_bUndoEnabled && ctCmd != gxRollback;
	
	BOOL bDone = pData->DeleteRangeName(name, pUndoInfo, ctCmd != gxRollback);

	if (bDone)
	{
		pGrid->SetModifiedFlag();

		if (bCreateUndo && ctCmd != gxRollback)
			pGrid->AddCommand(pGrid->m_pUndoImp->CreateDeleteRangeNameCmd(name, oldRange, pUndoInfo), ctCmd);

		return TRUE;
	}

	return FALSE;
}

