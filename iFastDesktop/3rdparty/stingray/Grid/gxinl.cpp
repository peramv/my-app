///////////////////////////////////////////////////////////////////////////////
// gxinl.cpp : Expansion of inline methods
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

/*
// compile this file only
// a) when inline expansions have not been included 
//    in header file (ndef _GX_ENABLE_INLINES)
// b) and inline functions shall not be left out (e.g. when 
//    creating .DEF files - ndef _GX_DISABLE_INLINES)
*/

#if !defined(_GX_ENABLE_INLINES) && !defined(_GX_DISABLE_INLINES)

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXCOLL_H_
#include "grid\gxcoll.h"
#endif

#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
#endif

#ifndef _GXBROWSE_H_
#include "grid\gxbrowse.h"
#endif

#ifndef _GXVW_H_
#include "grid\gxvw.h"
#endif

#ifndef _GXWND_H_
#include "grid\gxwnd.h"
#endif


#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXINL")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define GX_INLINE

#include "grid\gxcore.inl"
#include "grid\gxstyles.inl"
#include "grid\gxext.inl"
#include "grid\gxcoll.inl"
#include "grid\gxdelayr.inl"
#include "grid\gxbrowse.inl"
#include "grid\gxvw.inl"
#include "grid\gxwnd.inl"
#include "grid\gxdtcal.inl"

#endif //!_GX_ENABLE_INLINES
