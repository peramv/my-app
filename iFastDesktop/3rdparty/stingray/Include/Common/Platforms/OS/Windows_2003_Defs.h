///////////////////////////////////////////////////////////////////////////////
// Common\Platforms\OS\Windows_2003_Defs.h
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
#if !defined __WINDOWS__2003_DEFS__H__
#define __WINDOWS__2003_DEFS__H__

//-------------------------------------------------------------------//
// _WIN32_WINNT version constants
//-------------------------------------------------------------------//
#if !defined _WIN32_WINNT_WS03
#define _WIN32_WINNT_WS03                   0x0502
#endif // _WIN32_WINNT_WS03

#if !defined _WIN32_WINNT_WS03R2
#define _WIN32_WINNT_WS03R2                 0x05022
#endif // _WIN32_WINNT_WS03R2

//---------------------------------------------------------//
// WINDOWS 2003
//---------------------------------------------------------//
// Windows Server 2003
#if !defined NTDDI_WS03		
#define NTDDI_WS03          0x05020000
#endif 

// Windows Server 2003 with Service Pack 1
#if !defined NTDDI_WS03SP1	
#define NTDDI_WS03SP1       0x05020100
#endif 

// Windows Server 2003 with Service Pack 2
#if !defined NTDDI_WS03SP2	
#define NTDDI_WS03SP2       0x05020200
#endif

// Windows Server 2003 with Service Pack 3
#if !defined NTDDI_WS03SP3	
#define NTDDI_WS03SP3       0x05020300
#endif

// Windows Server 2003 with Service Pack 4
#if !defined NTDDI_WS03SP4	
#define NTDDI_WS03SP4		0x05020400
#endif

//---------------------------------------------------------//
// WINDOWS 2003 R2
//---------------------------------------------------------//
// Windows Server 2003 R2
#if !defined NTDDI_WS03R2		
#define NTDDI_WS03R2		0x05022000
#endif

// Windows Server 2003 R2 with Service Pack 1
#if !defined NTDDI_WS03R2SP1	
#define NTDDI_WS03R2SP1		0x05022100
#endif 

// Windows Server 2003 R2 with Service Pack 2
#if !defined NTDDI_WS03R2SP2	
#define NTDDI_WS03R2SP2		0x0502200
#endif 

// Windows Server 2003 R2 with Service Pack 3
#if !defined NTDDI_WS03R2SP3	
#define NTDDI_WS03R2SP3		0x05022300
#endif

// Windows Server 2003 R2 with Service Pack 4
#if !defined NTDDI_WS03R2SP4	
#define NTDDI_WS03R2SP4		0x05022400
#endif


#endif // __WINDOWS__2003_DEFS__H__