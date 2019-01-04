// GXSINC.H : Memory management
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


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <memory.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <errno.h>
#include <math.h>


#include "grid\gxengine.h"
#include "grid\gxscell.h"
#include "grid\gxsexpr.h"
#include "grid\gxserror.h"
#include "grid\gxsregex.h"

extern void* _gxAddMemObj(void* pObj);

#define GX_XSmalloc(n) _gxAddMemObj(malloc(n))
#define GX_XScalloc calloc
#define GX_XSrealloc realloc

extern void __cdecl _gxFreeObject(void* pObj);

#define GX_XSfree _gxFreeObject
