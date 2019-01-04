///////////////////////////////////////////////////////////////////////////////
// Common\Platforms\OS\Windows_Vista_Defs.h
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
#if !defined __WINDOWS__VISTA_DEFS__H__
#define __WINDOWS__VISTA_DEFS__H__

#include "Windows_Longhorn_Defs.h"

//-------------------------------------------------------------------//
// _WIN32_WINNT version constants
//-------------------------------------------------------------------//
#if !defined _WIN32_WINNT_VISTA
#define _WIN32_WINNT_VISTA  0x0600
#endif // _WIN32_WINNT_VISTA

//---------------------------------------------------------//
// WINDOWS VISTA
//---------------------------------------------------------//
// Windows Vista
#if !defined NTDDI_VISTA					
#define NTDDI_VISTA         NTDDI_WIN6 
#endif

// Windows Vista with Service Pack 1
#if !defined NTDDI_VISTASP1	
#define NTDDI_VISTASP1		NTDDI_WIN6SP1
#endif

// Windows Vista with Service Pack 2
#if !defined NTDDI_VISTASP2	
#define NTDDI_VISTASP2		NTDDI_WIN6SP2
#endif

// Windows Vista with Service Pack 3
#if !defined NTDDI_VISTASP3	
#define NTDDI_VISTASP3		NTDDI_WIN6SP3
#endif

// Windows Vista with Service Pack 4
#if !defined NTDDI_VISTASP4	
#define NTDDI_VISTASP4		NTDDI_WIN6SP4
#endif

#endif // __WINDOWS__VISTA_DEFS__H__