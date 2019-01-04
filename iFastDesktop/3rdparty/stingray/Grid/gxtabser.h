// This is a part of the Objective Grid C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government’s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Daniel Jebaraj
//
//
// gxtabser.h : header file
//


#ifndef _GX_TAB_SER_H__
#define _GX_TAB_SER_H__

#ifndef _GX_TMPL_H__
#include "grid\gxtmpl.h"
#endif

#ifndef _GX_TB_MGR_H__
#include "grid\gxtbmgr.h"
#endif

#ifndef _GXTWND_H_
#include "grid\gxtwnd.h"
#endif

#ifndef _GX_TAB_ADAPT_H__
#include "grid\gxtbadpt.h"
#endif

#ifndef _GX_TB_GRD_ADAPT_H__
#include "grid\gxtbgadp.h"
#endif

#ifndef _GXPRIV_H_
#include "grid\gxpriv.h"
#endif

#ifndef _GXMSG_H
#include "grid\gxmsg.h"
#endif

#ifndef _GX_AP_ATR_H__
#include "grid\gxapatr.h"
#endif

#ifndef _GX_DOC_H__
#include "grid\gxdoc.h"
#endif

#ifndef _GX_FRAME_ADPT_H__
#include "grid\gxfradpt.h"
#endif

#ifndef _GX_CH_FRM_H__
#include "grid\gxchfrm.h"
#endif

#ifndef _GX_DTMPL_H__
#include "grid\gxdtmpl.h"
#endif


#define GXIMPLEMENT_DYNCREATE(cl, clb)\
	IMPLEMENT_SERIAL(cl, clb, 0)

#define GXDECLARE_DYNCREATE(cl)\
	DECLARE_SERIAL(cl)


#endif //_GX_TAB_SER_H__
