// This is a part of the Objective Grid C++ Library.
// Copyright � 1999-2004 Quovadx, Inc.  All Rights Reserved.
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
//          Supplement Section 227.7202, Government�s use, duplication or 
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
// Author: Arun Balasubramanyan
//

// gxdbtlinklib.h : header file
//

#ifndef _GXDBTLINKLIB
#define _GXDBTLINKLIB

// Link to the appropriate import lib.
// Only SPM naming convention is supported. For other conventions,
// manually change this file and replace the appropriate library names.

#if defined _AFXDLL & !defined _GXDLL
#error Linkage with DBTools not allowed in this configuration(Grid LIB/MFC DLL). Choose Grid DLL/MFC DLL or Grid LIB/MFC LIB.
#endif

#ifdef _AFXDLL

#ifndef _DEBUG
#define _RWCONFIG_4d
#pragma comment(lib, "dbt4d.lib")
#pragma comment(lib, "tls4d.lib")
#else			// _DEBUG
#define _RWCONFIG_7d
#pragma comment(lib, "dbt7d.lib")
#pragma comment(lib, "tls7d.lib")
#endif			// _DEBUG
#else			// !_AFXDLL
#ifndef _DEBUG
#define _RWCONFIG_4s
#pragma comment(lib, "dbt4s.lib")
#pragma comment(lib, "tls4s.lib")
#else			// _DEBUG
#define _RWCONFIG_7s
#pragma comment(lib, "dbt7s.lib")
#pragma comment(lib, "tls7s.lib")
#endif			// _DEBUG

#endif			// _AFXDLL

#endif //_GXDBTLINKLIB
