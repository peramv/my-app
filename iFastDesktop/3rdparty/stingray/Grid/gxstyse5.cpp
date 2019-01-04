///////////////////////////////////////////////////////////////////////////////
// gxstyse5.cpp : OG 5 Backward compatible serialization 
//                support for CGXStyle 
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

#if _MFC_VER >= 0x0300
#ifndef _WINNLS_
#include "winnls.h"
#endif
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

class CGXSerializeOG5CompatibleImp: public CGXAbstractSerializeOG5CompatibleImp
{
public:
	virtual void SerializeOG5Map(CGXStyle* pStyle, CArchive& ar);
};

void AFXAPI CGXStyle::ImplementSerializeOG5Compatible()
{
	if (GXGetAppData()->m_pSerializeOG5CompatibleImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pSerializeOG5CompatibleImp = new CGXSerializeOG5CompatibleImp);
		GXGetAppData()->m_pSerializeOG5CompatibleImp = new CGXSerializeOG5CompatibleImp;
	}
}

void CGXSerializeOG5CompatibleImp::SerializeOG5Map(CGXStyle* pStyle, CArchive& ar)
{
	CGXCollMapDWordToString* pMap = NULL;
	ar >> pMap;
	if (pMap)
	{
		pStyle->m_pmapUserAttributes = new CGXUserAttributeMap;
		pStyle->m_pmapUserAttributes->AppendOG5Map(pMap);
	}
	delete pMap;
}

void CGXUserAttributeMap::AppendOG5Map(CGXCollMapDWordToString* pSrc)
{
	if (pSrc && pSrc->GetCount() > 0)
	{
		for (POSITION pos = pSrc->GetStartPosition(); pos; )
		{
			DWORD dw;
			CString value;
			pSrc->GetNextAssoc(pos, dw, value);

			SetAttribute((WORD) dw, CGXUserAttribute(value));
		}

		Sort();
	}
}



