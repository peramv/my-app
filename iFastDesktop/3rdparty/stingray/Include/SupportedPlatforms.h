///////////////////////////////////////////////////////////////////////////////
// SupportedPlatforms.h
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
//-------------------------------------------------------------------
// The purpose of this file is to include definitions of supported
// target platforms. Trying to compile libraries under an UNSUPPORTED
// platform will give a compile time error.
//-------------------------------------------------------------------

#if !defined(__SUPPORTEDPLATFORMS__H__)
#define __SUPPORTEDPLATFORMS__H__

#pragma warning(disable: 4005)

// Note: Standard definitions are usually found in the Microsoft SDK's sdkddkver.h. 
// However in some instances an SDK defintion is not present so we provide these in 
// the following include files:
#include "Common\Platforms\OS\Windows_NT_Defs.h"
#include "Common\Platforms\OS\Windows_2000_Defs.h"
#include "Common\Platforms\OS\Windows_XP_Defs.h"
#include "Common\Platforms\OS\Windows_2003_Defs.h"
#include "Common\Platforms\OS\Windows_Longhorn_Defs.h"
#include "Common\Platforms\OS\Windows_Vista_Defs.h"
#include "Common\Platforms\OS\Windows_2008_Defs.h"
#include "Common\Platforms\OS\Windows_7_Defs.h"
#include "Common\Platforms\OS\Windows_8_Defs.h"
#include "Common\Platforms\IE\InternetExplorer_Defs.h"

#define __PRAGMASTRING2(x) #x
#define __PRAGMASTRING(x) __PRAGMASTRING2(x)

#pragma message("----------------------------------------------------")
#pragma message(__TIMESTAMP__)

// For more details, refer to 
//      http://msdn2.microsoft.com/en-us/library/aa383745.aspx

/*
Note:
One simple way of looking at this is from a Kernel standpoint:
Windows Vista SP1 = Windows Server 2008
Windows Vista SP2 = Windows Server 2008 SP2
Windows 7 = Windows Server 2008 R2
*/

#ifndef NO_TARGETING
#pragma message ("Operating System:")
	// Default Platform definition
	#if !defined NTDDI_VERSION
		//------------------------------------------------------//
    // Redefine default target platform with one of the     //
		// supported NTDDI_* versions listed below:             //
		// NTDDI_WIN2K             Windows 2000                 //
		// NTDDI_WIN2KSP1                                       //
		// NTDDI_WIN2KSP2                                       //
		// NTDDI_WIN2KSP3                                       //
		// NTDDI_WIN2KSP4                                       //
		// NTDDI_WINXP             Windows XP                   //
		// NTDDI_WINXPSP1                                       //
		// NTDDI_WINXPSP2                                       //
		// NTDDI_WINXPSP3                                       //
		// NTDDI_WINXPSP4                                       //
		// NTDDI_WS03              Windows Server 2003          //
		// NTDDI_WS03SP1                                        //
		// NTDDI_WS03SP2                                        //
		// NTDDI_WS03SP3                                        //
		// NTDDI_WS03SP4                                        //
		// NTDDI_WIN6                                           //
		// NTDDI_WIN6SP1                                        //
		// NTDDI_WIN6SP2                                        //
		// NTDDI_WIN6SP3                                        //
		// NTDDI_WIN6SP4                                        //
		// NTDDI_LONGHORN  	       Windows Longhorn             //
		// NTDDI_VISTA             Windows Vista                //
		// NTDDI_VISTASP1                                       //
		// NTDDI_VISTASP2                                       //
		// NTDDI_VISTASP3                                       //
		// NTDDI_VISTASP4                                       //
		// NTDDI_WS08              Windows Server 2008          //
		// NTDDI_WS08SP2                                        //
		// NTDDI_WS08SP3                                        //
		// NTDDI_WS08SP4                                        //
		// NTDDI_WIN7              Windows 7                    //
		// NTDDI_WIN7SP1                                        //
		// NTDDI_WIN7SP2										//
		// NTDDI_WIN7SP3										//
		// NTDDI_WIN7SP4										//
		// NTDDI_WS08R2            Windows Server 2008 R2       //
		// NTDDI_WS08R2SP2                                      //
		// NTDDI_WS08R2SP3                                      //
		// NTDDI_WS08R2SP4                                      //
		// NTDDI_WIN8              Windows 8                    //
		//------------------------------------------------------//
		#pragma message("    *Target platform defined in " __FILE__ " after line: " __PRAGMASTRING(__LINE__))
        #define NTDDI_VERSION					NTDDI_WIN7SP1
		#pragma message("    NTDDI_VERSION == " __PRAGMASTRING(NTDDI_VERSION))

	#endif // NTDDI_VERSION

// Note: In order to keep this file readable, 
//       we have separated the output logic to the following include file:
#include "Common\Platforms\SupportedPlatformsOutput.h"

#endif // (NO_TARGETING)
#endif // (__SUPPORTEDPLATFORMS__H__)
