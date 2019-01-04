///////////////////////////////////////////////////////////////////////////////
// gxexmpst.cpp
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

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#include "grid\gxexhdr.h"

#include "grid\gxexman.h"

#include "grid\gxexhnd.h"

#include "grid\gxexmap.h"

#include "grid\gxexmpst.h"

CGXExMapHolder::CGXExMapHolder()
{
}
	
CGXExMapHolder::~CGXExMapHolder()
{
	if(m_pHandlerMap)
		delete m_pHandlerMap;

	if(m_pTableMap)
		delete m_pTableMap;
}


void CGXExMapHolder::SetHandlerMap(CGXHandlerMap* pHandlerMap)
{
	
	m_pHandlerMap = pHandlerMap;
}

void CGXExMapHolder::SetTableMap(CGXTableMap* pTableMap)
{

	m_pTableMap = pTableMap;
}

CGXHandlerMap* CGXExMapHolder::GetHandlerMap() const
{
	return m_pHandlerMap;
}

CGXTableMap*  CGXExMapHolder::GetTableMap() const
{
	return m_pTableMap;
}

CGXHandlerMap* GXExGetHandlerMap()
{
	CWinApp* pApp = AfxGetApp();
	CGXExMapHolder* pMapHolder = dynamic_cast<CGXExMapHolder*>(pApp);

	ASSERT(pMapHolder != NULL); // Error this is not a valid application object or maybe you did not enable RTTI
	
	if(pMapHolder != NULL)
		return pMapHolder->GetHandlerMap();
	else
		return NULL;
}

CGXTableMap* GXExGetTableMap()
{
	CWinApp* pApp = AfxGetApp();
	CGXExMapHolder* pMapHolder = dynamic_cast<CGXExMapHolder*>(pApp);

	ASSERT(pMapHolder != NULL); // Error this is not a valid application object or maybe you did not enable RTTI
	
	if(pMapHolder != NULL)
		return pMapHolder->GetTableMap();
	else
		return NULL;
}
