///////////////////////////////////////////////////////////////////////////////
// GXALL.h
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

#ifndef _GXALL_H_
#define _GXALL_H_

// OG needs 8 byte packing for structures
#if _MFC_VER >= 0x0300
// pshpack8.h saves the current #pragma pack value
#include /* */ "pshpack8.h"
#else
#pragma pack(8)
#endif

#if _MFC_VER >= 0x0300
#include <afxcmn.h>         // MFC support for Windows 95 Common Controls
#include <afxole.h>         // MFC support for OLE
#endif

// version info
#include "grid\gxver.h"

// resources
#include "grid\gxresrc.h"

#ifndef __RWUXTHEME_H
#include "RWUXTheme.h"
#endif

// dll support
#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#ifndef _GXDEF_H_
#include "grid\gxdef.h"
#endif

// Unicode
#ifndef _GXTCHAR_H_
#include "grid\gxtchar.h"
#endif

// core header
#ifndef _GXCOLL_H_
#include "grid\gxcoll.h"
#endif
#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif
#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif
#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif
#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif
#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif
#ifndef _GXCVRCEL_H_
#include "grid\gxcvrcel.h"
#endif
#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
#endif
#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

// grid window
#ifndef _GXWND_H_
#include "grid\gxwnd.h"
#endif

// grid view
#ifndef _GXVIEW_H_
#include "grid\gxview.h"
#endif
#ifndef _GXVW_H_
#include "grid\gxvw.h"
#endif

// dialogs
#ifndef _GXPRPDLG_H_
#include "grid\gxprpdlg.h"
#endif
#ifndef _GXSTYDLG_H_
#include "grid\gxstydlg.h"
#endif

// workbooks
#ifndef _GXTWND_H_
#include "grid\gxtwnd.h"
#endif

// Record status window
#ifndef _GXINFWND_H_
#include "grid\gxinfwnd.h"
#endif

// Browser Grid
#ifndef _GXBROWSE_H_
#include "grid\gxbrowse.h"
#endif

#if _MFC_VER >= 0x0400

#include <winnls.h>

#ifndef _GXCRTF_H_
#include "grid\gxcrtf.h"
#endif

#ifndef _GXOLE_H_
#include "grid\gxole.h"
#endif

#ifndef _GXSCRLTP_H_
#include "grid\gxscrltp.h"
#endif

#ifndef _GXDTCTRL_H_
#include "grid\gxdtctrl.h"
#endif

#ifndef _GXCURCTL_H_
#include "grid\gxcurctl.h"
#endif

#ifndef _GXCMD_H_
#include "grid\gxcmd.h"
#endif

#ifndef _GXSINC_H_
#include "grid\gxsinc.h" // formula support
#endif

#ifndef _GXSPLIT_H_
#include "grid\gxsplit.h"
#endif

// Grid HTML Write support
#ifndef _GXHTMLW_H_
#include "grid\gxhtmlW.h"
#endif

//Dynamic split window support
#ifndef _GXDTABWND_H_
#include "grid\gxDTabWnd.h"
#endif

#ifndef _GXDSPLIT_H_
#include "grid\gxDSplit.h"
#endif

// Page break UI
#ifndef _GXPGBRAK_H_
#include "grid\gxpgbrak.h"
#endif

#endif

#ifndef _GXIMOUSE_H_
#include "grid\gximouse.h"
#endif

#ifndef _GX_TAB_SER_H__
#include "grid\gxtabser.h"
#endif


//XML 
#ifndef _SFL_MFC_SUPPORT
#define _SFL_MFC_SUPPORT
#endif //_SFL_MFC_SUPPORT 

#if _MFC_VER >= 0x0300
// poppack.h restores the original #pragma pack value
#include /* */ "poppack.h"
#else
// restore default packing value
#pragma pack()
#endif

#endif // _GXALL_H_
