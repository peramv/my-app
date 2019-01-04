///////////////////////////////////////////////////////////////////////////////
// Common\Platforms\OS\Windows_XP_Defs.h
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
#if !defined __WINDOWSXPDEFS__H__
#define __WINDOWSXPDEFS__H__

#if !defined _WIN32_WINNT_WINXP
#define _WIN32_WINNT_WINXP  0x0501
#endif // _WIN32_WINNT_WINXP

// Windows XP
#if !defined NTDDI_WINXP	
#define NTDDI_WINXP         0x05010000
#endif

// Windows XP with Service Pack 1
#if !defined NTDDI_WINXPSP1	
#define NTDDI_WINXPSP1      0x05010100
#endif

// Windows XP with Service Pack 2
#if !defined NTDDI_WINXPSP2	
#define NTDDI_WINXPSP2      0x05010200
#endif

// Windows XP with Service Pack 3
#if !defined NTDDI_WINXPSP3	
#define NTDDI_WINXPSP3      0x05010300
#endif

// Windows XP with Service Pack 4
#if !defined NTDDI_WINXPSP4	
#define NTDDI_WINXPSP4      0x05010400
#endif

#endif // __WINDOWSXPDEFS__H__