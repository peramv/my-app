/////////////////////////////////////////////////////////////////////
// ProductVersions.h
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
//
// Author:	David Noi
// Date:	02.20.2006
//
// Changelog
// Date:	Initials:	Description:
//===========================================================================
// 09.08.2006	DN		Updated product versions for CD 49 release
// 09.28.2006	DN		No changes. 
//				NOTE:   _SFL_VER in this file is different 
//				        from _SFL_VER in ..\Src\ProductsVersion.mak
// 02.22.2007	CD		Updated product versions 
//				          to centralize all version changes to 
//				            ..\Include\ProductsVersion.h and 
//				            ..\Src\ProductsVersion.mak
// 04.09.2007	CD		Updated product versions for CD 50 release
// 07.29.2008	DN		Added RWUXTheme versioning info (QA 32237; changelist 178714)
// 09.11.2008	CD		Updated product versions for (10.1) CD 51 release
// 03.05.2009	CD		Search and replace macros, used by FAR scripts, added 
//                        to further centralize versions and formats
//                      Updated product versions for (10.2) CD 52 release
// 01.21.2010	CD		Updated product versions for (10.3) CD 53 release
// 05.19.2010	CD		Updated product versions for (10.4) CD 54 release
// 12.xx.2010	CD		Updated product versions for (10.5) NWM One-off informal release (CD 54.1)
//
// 03.xx.2011	CD		Updated product versions for (11.0) CD 55 release
//
////////////////////////////////////////////////////////////////////////////////////

#ifndef __PRODUCT_VERSION__H__
#define __PRODUCT_VERSION__H__

//------------------------------------------------------------//
// Here we define the product version numbers per release.    //
//------------------------------------------------------------//

// Stingray Foundation Library version
#define _SFL_VER	    0x0601
#define _SFL_VER_COMMA	6,0,1,0
#define _SFL_VER_TEXT	"6.0.1"
#define _SFL_VER_LIB    "601"

// Objective Chart version
#define _OC_VER		    0x01101
#define _OC_VER_COMMA	11,0,1,0
#define _OC_VER_TEXT	"11.0.1"
#define _OC_VER_LIB     "1101"

// Objective Chart Utility Toolkit version
#define _OCUT_VER	    0x01101
#define _OCUT_VER_COMMA 11,0,1,0
#define _OCUT_VER_TEXT	"11.0.1"
#define _OCUT_VER_LIB   "1101"

// Objective Edit version
#define _OE_VER		    0x01101
#define _OE_VER_COMMA	11,0,1,0
#define _OE_VER_TEXT	"11.0.1"
#define _OE_VER_LIB     "1101"

// Objective Grid version
#define _GX_VER		    0x01301
#define _GX_VER_COMMA	13,0,1,0
#define _GX_VER_TEXT	"13.0.1"
#define _GX_VER_LIB     "1301"

// Objective Toolkit version
#define _SEC_VER	    0x01201
#define _SEC_PRO_VER	_SEC_VER
#define _SEC_VER_COMMA	12,0,1,0
#define _SEC_VER_TEXT	"12.0.1"
#define _SEC_VER_LIB    "1201"

// Objective Views version
#define _OV_VER		    0x01201
#define _OV_VER_COMMA	12,0,1,0
#define _OV_VER_TEXT	"12.0.1"
#define _OV_VER_LIB     "1201"

// RWUXTheme version
#define _RWUXTHEME_VER		 0x01101
#define _RWUXTHEME_VER_COMMA 11,0,1,0
#define _RWUXTHEME_VER_TEXT	 "11.0.1"
#define _RWUXTHEME_VER_LIB	 "1101"

// Stingray FoundationEx Library version
#define _SFLEX_VER			0x0210
#define _SFLEX_VER_COMMA	2,1,0,0
#define _SFLEX_VER_TEXT		"2.1.0"
#define _SFLEX_VER_LIB		"210"

// Objective ChartEx version
#define _OCEX_VER		    0x00100
#define _OCEX_VER_COMMA	    1,0,0,0
#define _OCEX_VER_TEXT	    "1.0.0"
#define _OCEX_VER_LIB       "100"

// Objective Chart Utility ToolkitEx version
#define _OCUTEX_VER	      0x00100
#define _OCUTEX_VER_COMMA 1,0,0,0
#define _OCUTEX_VER_TEXT  "1.0.0"
#define _OCUTEX_VER_LIB   "100"

// Objective EditEx version
#define _OEEX_VER		0x00100
#define _OEEX_VER_COMMA	1,0,0,0
#define _OEEX_VER_TEXT	"1.0.0"
#define _OEEX_VER_LIB   "100"

// GridEx Library version
#define _OGEX_VER	    0x0201
#define _OGEX_VER_COMMA	2,0,1,0
#define _OGEX_VER_TEXT	"2.0.1"
#define _OGEX_VER_LIB	"201"

// Objective ToolkitEx version
#define _OTEX_VER	      0x00100
#define _OTEX_VER_COMMA  1,0,0,0
#define _OTEX_VER_TEXT	  "1.0.0"
#define _OTEX_VER_LIB    "100"

// Objective ViewsEx version
#define _OVEX_VER		0x00100
#define _OVEX_VER_COMMA	1,0,0,0
#define _OVEX_VER_TEXT	"1.0.0"
#define _OVEX_VER_LIB   "100"

// Objective Grid for .NET version
#define _OGN_VER		0x01301
#define _OGN_VER_COMMA	13,0,1,0
#define _OGN_VER_TEXT	"13.0.1"
#define _OGN_VER_LIB    "1301"

// Stingray FoundationEx .NET Library version
#define _SFLEXNET_VER			0x00100
#define _SFLEXNET_VER_COMMA	    1,0,0,0
#define _SFLEXNET_VER_TEXT		"1.0.0"
#define _SFLEXNET_VER_LIB		"100"

#endif // __PRODUCT_VERSION__H__
