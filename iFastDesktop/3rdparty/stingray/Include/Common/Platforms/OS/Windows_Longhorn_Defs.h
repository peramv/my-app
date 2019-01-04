///////////////////////////////////////////////////////////////////////////////
// Common\Platforms\OS\Windows_Longhorn_Defs.h
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
#if !defined __WINDOWS__LONGHORN_DEFS__H__
#define __WINDOWS__LONGHORN_DEFS__H__

//-------------------------------------------------------------------//
// _WIN32_WINNT version constants
//-------------------------------------------------------------------//
#if !defined _WIN32_WINNT_WIN6
#define _WIN32_WINNT_WIN6   0x0600
#endif // _WIN32_WINNT_WIN6

#if !defined _WIN32_WINNT_LONGHORN
#define _WIN32_WINNT_LONGHORN               0x0600
#endif // _WIN32_WINNT_LONGHORN

//---------------------------------------------------------//
// WINDOWS LONGHORN
//---------------------------------------------------------//
#if !defined NTDDI_LONGHORN	
#define NTDDI_LONGHORN      0x06000000
#endif

#if !defined NTDDI_WIN6 
#define NTDDI_WIN6          0x06000000
#endif 

#if !defined NTDDI_WIN6SP1
#define NTDDI_WIN6SP1       0x06000100
#endif

#if !defined NTDDI_WIN6SP2
#define NTDDI_WIN6SP2       0x06000200
#endif

#if !defined NTDDI_WIN6SP3
#define NTDDI_WIN6SP3       0x06000300
#endif

#if !defined NTDDI_WIN6SP4
#define NTDDI_WIN6SP4       0x06000400
#endif


#endif // __WINDOWS__LONGHORN_DEFS__H__