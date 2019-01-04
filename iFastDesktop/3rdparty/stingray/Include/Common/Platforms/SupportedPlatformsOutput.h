///////////////////////////////////////////////////////////////////////////////
// SupportedPlatformsOutput.h
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
// The purpose of this file is to output definitions of supported
// target platforms. Trying to compile libraries under an UNSUPPORTED
// platform will give a compile time error.
//-------------------------------------------------------------------

#if !defined(__SUPPORTEDPLATFORMSOUTPUT__H__)
#define __SUPPORTEDPLATFORMSOUTPUT__H__

#pragma warning(disable: 4005)

#ifndef NO_TARGETING

// Comment/uncomment #define below
// to disallow/allow binding to current compiler libraries.
//#if(_MSC_VER >= 1500) // Microsoft Visual Studio 2008 (9.0+) including SP1"
#define _BIND_TO_CURRENT_VCLIBS_VERSION 1
//#endif // _BIND...

//------------------------------------------------------//

    // Windows 8
    #if (NTDDI_VERSION >= NTDDI_WIN8) && (NTDDI_VERSION <= NTDDI_WIN8SP4)
        #define WINVER		 _WIN32_WINNT_WIN8 // 0x0602
        #define _WIN32_WINNT _WIN32_WINNT_WIN8 // 0x0602
        #define	_WIN32_IE	 _WIN32_IE_IE90    // 0x0900
        #pragma message("    Targeting supported (WINDOWS 8)* platform")
    // Windows 7
    #elif (NTDDI_VERSION >= NTDDI_WIN7) && (NTDDI_VERSION <= NTDDI_WIN7SP4)
        #define WINVER		 _WIN32_WINNT_WIN7 // 0x0601
        #define _WIN32_WINNT _WIN32_WINNT_WIN7 // 0x0601
        #define	_WIN32_IE	 _WIN32_IE_IE80    // 0x0800
        #pragma message("    Targeting supported (WINDOWS 7)* platform")
    // Windows Server 2008 R2
    #elif (NTDDI_VERSION >= NTDDI_WS08R2) && (NTDDI_VERSION <= NTDDI_WS08R2SP4)
		// SRSTUDIO-1915
        #define WINVER		 _WIN32_WINNT_WS08 // 0x0600
        #define _WIN32_WINNT _WIN32_WINNT_WS08 // 0x0600
        #define	_WIN32_IE	 _WIN32_IE_IE70    // 0x0700
        #pragma message("    Targeting supported (WINDOWS SERVER 2008 R2)* platform")
    // Windows Server 2008
    #elif (NTDDI_VERSION >= NTDDI_WS08) && (NTDDI_VERSION <= NTDDI_WS08SP4)
        #define WINVER		 _WIN32_WINNT_WS08 // 0x0600
        #define _WIN32_WINNT _WIN32_WINNT_WS08 // 0x0600
        #define	_WIN32_IE	 _WIN32_IE_IE70    // 0x0700
        #pragma message("    Targeting supported (WINDOWS SERVER 2008)* platform")
    // Windows Vista SP1 - SP4
    #elif (NTDDI_VERSION >= NTDDI_VISTA) && (NTDDI_VERSION <= NTDDI_VISTASP4)
        #define WINVER		 	_WIN32_WINNT_VISTA // 0x0600
        #define _WIN32_WINNT 	_WIN32_WINNT_VISTA // 0x0600
        #define	_WIN32_IE	 	_WIN32_IE_IE70     // 0x0700
        #pragma message("    Targeting supported (WINDOWS VISTA)* platform")
    // Windows Server 2003 R2 - Service Pack 4
    #elif (NTDDI_VERSION >= NTDDI_WS03R2) && (NTDDI_VERSION <= NTDDI_WS03R2SP4) 
        // NOTE: You may have a SDK version which requires these values to be 0x0503 instead of 0x0600. 
        // If so, change these values appropriately. 
        #define WINVER       	_WIN32_WINNT_VISTA // 0x0600 NOT 0x0503
        #define _WIN32_WINNT 	_WIN32_WINNT_VISTA // 0x0600 NOT 0x0503
        #define	_WIN32_IE	 	_WIN32_IE_IE70     // 0x0700
        #pragma message("    Targeting supported (WINDOWS 2003 SERVER R2)* platform")
    // Windows Server 2003 - Service Pack 4
    #elif (NTDDI_VERSION >= NTDDI_WS03) && (NTDDI_VERSION <= NTDDI_WS03SP4) 
        #define WINVER       	_WIN32_WINNT_WS03 // 0x0502
        #define _WIN32_WINNT 	_WIN32_WINNT_WS03 // 0x0502
        #define	_WIN32_IE	 	_WIN32_IE_IE60SP2 // 0x0603
        #pragma message("    Targeting supported (WINDOWS 2003 SERVER)* platform")
        #pragma message("    ***Some SDK's may require these to be defined as 0x0501***")
    #elif (NTDDI_VERSION >= NTDDI_WINXPSP3) && (NTDDI_VERSION <= NTDDI_WINXPSP4)  // Windows XP SP3 - SP4
        // These values are based on the Windows Server 2008 PSDK sdkddkver.h
        #define WINVER       	_WIN32_WINNT_WINXP  // 0x0501
        #define _WIN32_WINNT 	_WIN32_WINNT_WINXP  // 0x0501
        #define	_WIN32_IE	 	_WIN32_IE_IE60SP2   // 0x0603
        #pragma message("    Targeting supported (WINDOWS XP SP3)* platform")
        #pragma message("    ***Some SDK's may require these to be defined as 0x0502***")
    #elif NTDDI_VERSION == NTDDI_WINXPSP2 // Windows XP SP2
        // NOTE: With some Microsoft Platform SDKs, _WIN32_WINNT may need to be defined at 0x0502.
        #define WINVER       	_WIN32_WINNT_WINXP // 0x0501
        #define _WIN32_WINNT	_WIN32_WINNT_WINXP // 0x0501
        #define	_WIN32_IE	 	_WIN32_IE_IE60SP2 // 0x0603
        #pragma message("    Targeting supported (WINDOWS XP SP2)* platform")
        #pragma message("    ***Some SDK's may require these to be defined as 0x0502***")
    #elif NTDDI_VERSION == NTDDI_WINXPSP1 // Windows XP SP1
        #pragma message("    Windows XP SP1 is UNSUPPORTED, please upgrade to SP2 or higher.")
        #pragma message("    ***Please review the support matrix for supported target platforms.***")
        //#error Windows XP SP1 is UNSUPPORTED, please upgrade to SP2.
    // Windows 2000 - SP4
    #elif (NTDDI_VERSION >= NTDDI_WIN2K) && (NTDDI_VERSION <= NTDDI_WIN2KSP4) 
        #define WINVER       	_WIN32_WINNT_WIN2K // 0x0500
        #define _WIN32_WINNT 	_WIN32_WINNT_WIN2K // 0x0500
        #define	_WIN32_IE	 	_WIN32_IE_IE50     // 0x0500
        #define HRAWINPUT DWORD  // Required to remove specific syntax error: ‘<L_TYPE_raw>’
        #pragma message("    Windows 2000 (SP0 - SP4) are UNSUPPORTED.")
        #pragma message("    ***Please review the support matrix for supported target platforms.***")
        //#error Windows 2000 (SP0 - SP3) are UNSUPPORTED, please upgrade to SP4.
    #else // Other platform
        #define WINVER       	0x0502
        #define _WIN32_WINNT 	0x0502
        #define	_WIN32_IE	 	0x0603
        #pragma message("    Targeting UNSUPPORTED platform.")
        #pragma message("    ***Please review the support matrix for supported target platforms.***")
        //#error Target platforms where the appropriate NTDDI_VERSION is supported!
    #endif // WINVER
	
        #pragma message("          WINVER      >= " __PRAGMASTRING(WINVER))
        #pragma message("         _WIN32_WINNT == " __PRAGMASTRING(_WIN32_WINNT))
        #pragma message("         _WIN32_IE    == " __PRAGMASTRING(_WIN32_IE))


// Operating System Bit Version---------------------------------------
#if defined(_WIN64)
    #if defined(_M_AMD64)
        #if(_MSC_VER >= 1400)
            #pragma message("    AMD x64 Processor Family is supported")
        //#else
            //#pragma message("    You must use Microsoft Visual Studio 2005 (8.0) or Higher!")
            //#error You must use Microsoft Visual Studio 2005 (8.0) or Higher!
        #endif
    #elif defined(_M_IA64)
        #pragma message("    Intel Itanium x64 Processor Family is not supported!")
    //#error
    #else
        #pragma message("    Unknown x64 Processor Family is not supported!")
        //#error
    #endif // x64 Processors
#endif // _WIN64

#if defined(_M_IX86) // x86 archictecture
    #if defined(_WIN64) // 64-bit application
        #pragma message("    x86 OS is supported for 32 Bit only. x64 cross-compiler is not supported.")
    #else
        #pragma message("    x86 OS is supported")
    #endif
#endif

#if defined(_M_X64)
    #if (_MSC_VER >= 1400)
        #pragma message("    x64 OS is supported")
    #else
        //#pragma message("    You must use Microsoft Visual Studio 2005 (8.0) or Higher!")
        //#error You must use Microsoft Visual Studio 2005 (8.0) or Higher!
    #endif
#endif

// COMPILERS --------------------------------------------------------
#pragma message("Compiler:")
#pragma message("    _MSC_VER == " __PRAGMASTRING(_MSC_VER))
// Add the compiler info into our object file.
#if(_MSC_VER >= 1800) // Microsoft Visual Studio 20??
	#pragma message("    Compilers Newer than Microsoft Visual Studio 2012 are not supported.")
#elif(_MSC_VER >= 1700) // Microsoft Visual Studio 2012
    #pragma message("    Microsoft Visual Studio 2012 (11.0 +) is supported.")
#elif(_MSC_VER >= 1600) // Microsoft Visual Studio 2010 (10.0 +)
    // This is a supported compiler.
    #pragma message("    Microsoft Visual Studio 2010 (10.0 +) is supported.")
#elif(_MSC_VER >= 1500) // Microsoft Visual Studio 2008 (9.0 +)
    // This is a supported compiler.
    #pragma message("    Microsoft Visual Studio 2008 (9.0 +) including SP1")
#elif(_MSC_VER >= 1400) // Microsoft Visual Studio 2005 (8.0 +) including SP1
    // This is a supported compiler.
    #pragma message("    Microsoft Visual Studio 2005 (8.0 +) is supported.")
#elif(_MSC_VER == 1310) // Microsoft Visual Studio 2003 .NET (7.1 +)
    #if WINVER >= 0x0600
        // This is not a supported compiler on Vista.
        #pragma message("    Microsoft Visual Studio 2003 .NET (7.1 +) is not supported on Vista!")
        #pragma message("    ***Please review the support matrix for supported compilers.***")
        //#error Microsoft Visual Studio 2003 .NET (7.1 +) is not supported on Vista!
    #else
        // This is no longer a supported compiler.
        #pragma message("    Microsoft Visual Studio 2003 .NET (7.1 +) is no longer supported.")
        #pragma message("    ***Please review the support matrix for supported compilers.***")
    #endif
#elif (_MSC_VER == 1300) // Microsoft Visual Studio 2002 .NET (7.0)
    // This is not a supported compiler.
    #pragma message("    Microsoft Visual Studio 2002 .NET (7.0) is no longer supported!")
    #pragma message("    ***Please review the support matrix for supported compilers.***")
    //#error Microsoft Visual Studio 2002 .NET (7.0) is not supported!
#elif (_MSC_VER == 1200) // Microsoft Visual Studio 1998 (6.0)
    #if WINVER >= 0x0600
        // This is not a supported compiler on Vista.
        #pragma message("    Microsoft Visual Studio 1998 (6.0) is not supported on Vista!")
        #pragma message("    ***Please review the support matrix for supported compilers.***")
        //#error Microsoft Visual Studio 1998 (6.0) is not supported on Vista!
    #else
        // This is no longer a supported compiler.
        #pragma message("    Microsoft Visual Studio 1998 (6.0) is no longer supported.")
        #pragma message("    ***Please review the support matrix for supported compilers.***")
        //#error Microsoft Visual Studio 1998 (6.0) is no longer supported.
    #endif
#else
    // These are not supported compilers.
    #pragma message("    This compiler is not supported!")
    #pragma message("    ***Please review the support matrix for supported compilers.***")
    //#error This compiler is not supported!
#endif 

// 64 Bit Support:
#if defined(_WIN64)
	#if(_MSC_VER >= 1800) // Microsoft Visual Studio 20??
        #pragma message("    Licensed 64 Bit builds are NOT supported on compilers newer than Microsoft Visual Studio 2012.")
    #elif(_MSC_VER >= 1700) // Microsoft Visual Studio 20??
        #pragma message("    Licensed 64 Bit builds are supported with Microsoft Visual Studio 2012 (11.0).")
    #elif(_MSC_VER >= 1600)
        #pragma message("    Licensed 64 Bit builds are supported with Microsoft Visual Studio 2010 (10.0)")
    #elif(_MSC_VER >= 1500)
        #pragma message("    Licensed 64 Bit builds are supported with Microsoft Visual Studio 2008 (9.0 +)")
    #elif(_MSC_VER >= 1400)
        #pragma message("    Licensed 64 Bit builds are supported with Microsoft Visual Studio 2005 (8.0 +)")
    #else
        #pragma message("    64 Bit libraries require Microsoft Visual Studio 2005 (8.0 +) or higher!")
        //#error 64 Bit libraries require Microsoft Visual Studio 2005 (8.0) or higher!
    #endif // 1400 == _MSC_VER
#endif // _WIN64

// Build Configurations ---------------------------------------------
//
#pragma message("Build Configuration:")

// MFC Static or DLL 
#if defined(_AFXDLL) || defined(_WINDLL)
    #pragma message("    (a) AFX/MFC DLL")
#else
    #pragma message("    ( ) MFC/AFX Static Library")

    // Specific "user-friendly" (non-intrusive) work around to the MFC static library
    // linking issue on Windows 7 SP1 (or higher) with MSVS 2010 SP1 and the Windows SDK 7.1
    #if (((NTDDI_VERSION == NTDDI_WIN7SP1) || (NTDDI_VERSION == NTDDI_WS08R2SP1)) && (_MSC_VER == 1600) && (_MSC_FULL_VER >= 160040219))
        // This links the necessary library under the "correct" platform and build conditions
        #pragma comment(lib, "windowscodecs")
    #endif

#endif // _AFXDLL

// Stingray Static or DLL
#if defined(_RWUXTHEMEDLL) || defined(_SFLDLL) || defined(_SFLEXDLL) || defined(_OBJCHART_DLL) || defined(_OBJCHART_UT_DLL) || defined(_SECEDITDLL) || defined(_GXDLL) || defined(_OGEXDLL) || defined(_SECDLL) || defined(_OVDLL)
    #pragma message("    (s) Stingray DLL")
#else
    #pragma message("    ( ) Stingray Static Library")	
#endif // _PRODUCTDLL

// Unicode
#if defined(_UNICODE)
    #pragma message("    (u) Unicode")
#else
    #pragma message("    ( ) ANSI")	
#endif // _UNICODE

// Debug or Release
#if defined(_DEBUG)
    #pragma message("    (d) Debug")
#elif defined(NDEBUG)
    #pragma message("    ( ) Release")
#endif // _DEBUG

// Managed /CLR?
#if defined (_MANAGED)
#pragma message ("    (m) Managed")
#else
#pragma message ("    ( ) Unmanaged")
#endif // _MANAGED

#pragma message("----------------------------------------------------")
#pragma message(" ")
#if defined(_AFXDLL) || defined(_WINDLL)
// No-op
#else
    #if (((NTDDI_VERSION == NTDDI_WIN7SP1) || (NTDDI_VERSION == NTDDI_WS08R2SP1)) && (_MSC_VER == 1600) && (_MSC_FULL_VER >= 160040219))
        // This links the necessary library under the "correct" platform and build conditions
        #pragma message("        Automatically linking windowscodecs.lib...")
    #endif
#endif

#endif // (NO_TARGETING)
#endif // (__SUPPORTEDPLATFORMSOUTPUT__H__)
