///////////////////////////////////////////////////////////////////////////////
// RWColorFunctions.cpp
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

#include "stdafx.h"

#if _MSC_VER >= 1500
	// Recommended to use the Windows Platform SDK v6.1 or higher.
	#include "vssym32.h"
#else
	#include "tmschema.h"
#endif

#pragma warning(disable: 4996)// Depracated functions
// Internal color map defines
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RW_clrWindow		0x00
#define RW_clrWindowText	0x01
#define RW_clrBtnFace		0x02
#define RW_clrBtnShadow		0x03
#define RW_clrBtnText		0x04
#define RW_clrHighlight		0x05
#define RW_clrGrayText		0x06
#define RW_clrMenuText		0x07

// Color array
// ~~~~~~~~~~~
#define RW_SYSCOLORELEMS	(RW_clrMenuText + 1)
#define RW_DRAWCOLORELEMS	(RW_GRIPPER + 1)
#define RW_O2K3COLORELEMS   (RW_O2K3_THEMEEDGEDARK + 1)
COLORREF	gSysColors[RW_SYSCOLORELEMS] = { 0, 0, 0, 0, 0, 0, 0, 0 };
COLORREF	gDrawColors[RW_DRAWCOLORELEMS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
COLORREF    gO2K3Colors[RW_O2K3COLORELEMS] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// Color manipulation constants
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const BYTE		gRedWeight   =	77;
const BYTE		gGreenWeight = 153;
const BYTE		gBlueWeight =  26;

const double	gRedWeightDouble   = 0.764706;
const double	gGreenWeightDouble = 1.52941;
const double	gBlueWeightDouble  = 0.254902;

// Look and Feel
extern SEC_AUX_DATA secData;

// Alpha blends two colors
// ~~~~~~~~~~~~~~~~~~~~~~~
RWTHEMEAPI(COLORREF) RWBlendColors( COLORREF dstClr, COLORREF srcClr, BYTE blendVal )
{
	DWORD val = ( blendVal >= 100 ? 1000 : 100 );

	return ((((( srcClr >> 16 )        ) * ( val - blendVal ) + (( dstClr >> 16 )        ) * blendVal + ( val >> 1 )) / val & 0xFF ) << 16 ) +
		   ((((( srcClr >> 8  ) & 0xFF ) * ( val - blendVal ) + (( dstClr >> 8  ) & 0xFF ) * blendVal + ( val >> 1 )) / val & 0xFF ) << 8  ) +
		   ((((( srcClr       ) & 0xFF ) * ( val - blendVal ) + (( dstClr       ) & 0xFF ) * blendVal + ( val >> 1 )) / val & 0xFF )       );
}

// Lighten every color component by given amount
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
RWTHEMEAPI(COLORREF) RWLightenColor( COLORREF srcClr, BYTE lightAmount )
{
	int r, g, b;

	r = GetRValue( srcClr ) + lightAmount; if( r < 0 ) r = 0; else if( r > 255 ) r = 255;
	g = GetGValue( srcClr ) + lightAmount; if( g < 0 ) g = 0; else if( g > 255 ) g = 255;
	b = GetBValue( srcClr ) + lightAmount; if( b < 0 ) b = 0; else if( b > 255 ) b = 255;

	return RGB( r, g, b );
}

// Determines if the color is dark by converting to 
// gray scale and comparing to given threshold
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
RWTHEMEAPI(BOOL) RWIsDarkColor( COLORREF tstClr, DWORD threshold )
{
	threshold <<= 8;
	return ( (( tstClr       ) & 0x000000FF ) * gRedWeight + 
			 (( tstClr >> 8  ) & 0x000000FF ) * gGreenWeight + 
			 (( tstClr >> 16 ) & 0x000000FF ) * gBlueWeight ) < threshold;
}

// Internal contrast manipulation helpers
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline double RWGetColorDistance( COLORREF clr1, COLORREF clr2 )
{
	double redDist, greenDist, blueDist;

	redDist   = ((int)(( clr1       ) & 0xFF ) - (int)(( clr2       ) & 0xFF )) * gRedWeightDouble;
	greenDist = ((int)(( clr1 >> 8  ) & 0xFF ) - (int)(( clr2 >> 8  ) & 0xFF )) * gGreenWeightDouble;
	blueDist  =	((int)(( clr1 >> 16 ) & 0xFF ) - (int)(( clr2 >> 16 ) & 0xFF )) * gBlueWeightDouble;

	return sqrt( redDist * redDist + greenDist * greenDist + blueDist * blueDist );
}

inline double RWGetAdjustedThreshold( double bkIntensity, double threshold )
{
	return ( (bkIntensity < 220) ? ( ( 2 - bkIntensity / 220 ) * threshold ) : threshold );
}

inline BOOL RWIsContrastEnough( COLORREF clr1, COLORREF clr2, BOOL adjustThreshold, double threshold )
{
	if( adjustThreshold )
		threshold = RWGetAdjustedThreshold( RWGetColorDistance( clr2, 0x00000000 ), threshold );

	return ( RWGetColorDistance( clr2, clr1 ) > threshold );
}

inline COLORREF RWAdjustContrast( COLORREF clr1, COLORREF clr2, double threshold )
{
	double	br, bg, bb;
	double  r, g, b;
	bool	invert = false;
	double	dist1, dist2;
	double  t1, t2, t3;
	int		iR, iG, iB;

	dist1 = RWGetColorDistance( clr1, 0x00000000 );
	dist2 = RWGetColorDistance( clr2, 0x00000000 );
	threshold = RWGetAdjustedThreshold( dist2, threshold );

	if( dist1 > dist2 )
		invert = ( dist2 < ( 442 - threshold ) );
	else
		invert = ( dist2 < threshold );

	br = (( clr2       ) & 0xFF ) * gRedWeightDouble;
	bg = (( clr2 >> 8  ) & 0xFF ) * gGreenWeightDouble;
	bb = (( clr2 >> 16 ) & 0xFF ) * gBlueWeightDouble;

	r = (( clr1       ) & 0xFF ) * gRedWeightDouble;
	g = (( clr1 >> 8  ) & 0xFF ) * gGreenWeightDouble;
	b = (( clr1 >> 16 ) & 0xFF ) * gBlueWeightDouble;

	if( invert )
	{
		 r = 195 -  r;  g = 390 -  g;  b = 65 -  b;
		br = 195 - br; bg = 390 - bg; bb = 65 - bb;
	}

	t1 = sqrt( b * b + g * g + r * r );

	if( t1 < 0.01 ) t1 = 0.01;

	t2 = ( r * br + g * bg + b * bb ) / t1;

	br = t2 / t1 * r - br;
	bg = t2 / t1 * g - bg;
	bb = t2 / t1 * b - bb;

	t3 = sqrt( threshold * threshold - br  * br - bg * bg - bb * bb );

	r = ( t2 - t3 ) * r / t1;
	g = ( t2 - t3 ) * g / t1;
	b = ( t2 - t3 ) * b / t1;

	if( invert )
	{
		r = 195 - r;
		g = 390 - g;
		b =  65 - b;
	}

	if( r < 0 ) r = 0; else if( r > 195 ) r = 195;
	if( g < 0 ) g = 0; else if( g > 390 ) g = 390;
	if( b < 0 ) b = 0; else if( b >  65 ) b =  65;

	iR = int( r * ( 1 / gRedWeightDouble   ) + 0.5 );
	iG = int( g * ( 1 / gGreenWeightDouble ) + 0.5 );
	iB = int( b * ( 1 / gBlueWeightDouble  ) + 0.5 );

	if( iR > 0xFF ) iR = 0xFF; else if( iR < 0 ) iR = 0;
	if( iG > 0xFF ) iG = 0xFF; else if( iG < 0 ) iG = 0;
	if( iB > 0xFF ) iB = 0xFF; else if( iB < 0 ) iB = 0;

	return RGB( iR, iG, iB );
}

RWTHEMEAPI(COLORREF) RWSetContrast( COLORREF clr1, COLORREF clr2, int threshold )
{
	return ( !RWIsContrastEnough( clr1, clr2, TRUE, (double)threshold ) ? RWAdjustContrast( clr1, clr2, (double)threshold ) : clr1 );
}

RWTHEMEAPI(void) RWResetColors()
{
	gSysColors[RW_clrWindow]		= ::GetSysColor( COLOR_WINDOW );
	gSysColors[RW_clrWindowText]	= ::GetSysColor( COLOR_WINDOWTEXT );
	gSysColors[RW_clrBtnFace]		= ::GetSysColor( COLOR_BTNFACE );
	gSysColors[RW_clrBtnShadow]		= ::GetSysColor( COLOR_BTNSHADOW );
	gSysColors[RW_clrBtnText]		= ::GetSysColor( COLOR_BTNTEXT );
	gSysColors[RW_clrHighlight]		= ::GetSysColor( COLOR_HIGHLIGHT );
	gSysColors[RW_clrGrayText]		= ::GetSysColor( COLOR_GRAYTEXT );
	gSysColors[RW_clrMenuText]		= ::GetSysColor( COLOR_MENUTEXT );

	gDrawColors[RW_TOOLBAR]			= RWBlendColors( gSysColors[RW_clrWindow], gSysColors[RW_clrBtnFace], 165 );
	gDrawColors[RW_TOOLBARSEP]		= RWSetContrast( RWBlendColors( gSysColors[RW_clrBtnShadow], gSysColors[RW_clrWindow], 70 ), gDrawColors[RW_TOOLBAR], 50 );
	gDrawColors[RW_TOOLBARTEXT]		= RWSetContrast( gSysColors[RW_clrBtnText], gDrawColors[RW_TOOLBAR], 180 );
	gDrawColors[RW_TBBTNFACENORM]	= gDrawColors[RW_TOOLBAR];
	gDrawColors[RW_TBBTNFRMNORM]	= gDrawColors[RW_TOOLBAR];
	gDrawColors[RW_TBBTNFACEHOT]	= RWSetContrast( RWBlendColors( gSysColors[RW_clrHighlight], gSysColors[RW_clrWindow], 30 ), gDrawColors[RW_TOOLBAR], 50 );
	gDrawColors[RW_TBBTNFRMHOT]		= RWSetContrast(gSysColors[RW_clrHighlight], gDrawColors[RW_TOOLBAR], 100);
	gDrawColors[RW_TBBTNFACEPRESS]	= RWBlendColors( gSysColors[RW_clrHighlight], gSysColors[RW_clrWindow], 50 );
	gDrawColors[RW_TBBTNFRMPRESS]	= gSysColors[RW_clrHighlight];
	gDrawColors[RW_TBBTNFACEDIS]	= gDrawColors[RW_TOOLBAR];
	gDrawColors[RW_TBBTNFRMDIS]		= gDrawColors[RW_TOOLBAR];
	gDrawColors[RW_TBBTNFACECHK]	= RWSetContrast( RWBlendColors( gSysColors[RW_clrHighlight], RWBlendColors(gSysColors[RW_clrBtnFace], gSysColors[RW_clrWindow],48), 7), gDrawColors[RW_TOOLBAR], 5 );
	gDrawColors[RW_TBBTNFRMCHK]		= gSysColors[RW_clrHighlight];
	gDrawColors[RW_TBBTNFACECHKHOT]	= RWSetContrast( RWBlendColors( gSysColors[RW_clrHighlight], gSysColors[RW_clrWindow], 50 ), gDrawColors[RW_TOOLBAR], 30 ); 
	gDrawColors[RW_TBBTNFRMCHKHOT]	= RWSetContrast( gSysColors[RW_clrHighlight], gDrawColors[RW_TBBTNFACECHKHOT], 100 );

	gDrawColors[RW_MENU]			= RWBlendColors( gSysColors[RW_clrBtnFace], gSysColors[RW_clrWindow], 143 );
	gDrawColors[RW_MENUTXT]			= RWSetContrast( gSysColors[RW_clrWindowText], gDrawColors[RW_MENU], 180 );
	gDrawColors[RW_MENUDIS]			= gDrawColors[RW_MENU];
	gDrawColors[RW_MENUTXTDIS]		= RWSetContrast( RWBlendColors( gSysColors[RW_clrGrayText], gSysColors[RW_clrWindow], 70 ), gDrawColors[RW_MENU], 80 );
	gDrawColors[RW_MENUHOT]			= RWSetContrast( RWBlendColors( gSysColors[RW_clrHighlight], gSysColors[RW_clrWindow], 30 ), gDrawColors[RW_TOOLBAR], 50 );
	gDrawColors[RW_MENUFRMHOT]		= RWSetContrast(gSysColors[RW_clrHighlight], gDrawColors[RW_TOOLBAR], 100);
	gDrawColors[RW_MENUTXTHOT]		= RWSetContrast( gSysColors[RW_clrMenuText], gDrawColors[RW_MENUHOT], 180 );
	gDrawColors[RW_MENUDISHOT]		= gDrawColors[RW_MENU];
	gDrawColors[RW_MENUTXTDISHOT]	= RWBlendColors( gSysColors[RW_clrGrayText], gSysColors[RW_clrWindow], 70 );
	gDrawColors[RW_MENUFRMDISHOT]	= RWSetContrast(gSysColors[RW_clrHighlight], gDrawColors[RW_TOOLBAR], 100);
	gDrawColors[RW_MENUBAND]		= RWBlendColors( gSysColors[RW_clrWindow], gSysColors[RW_clrBtnFace], 165 );
	gDrawColors[RW_MENUFRAME]		= RWSetContrast( RWBlendColors( gSysColors[RW_clrBtnText], gSysColors[RW_clrBtnShadow], 20 ), gDrawColors[RW_TOOLBAR], 100 );
	gDrawColors[RW_MENUSEP]			= RWSetContrast( RWBlendColors( gSysColors[RW_clrBtnShadow], gSysColors[RW_clrWindow], 70 ), gDrawColors[RW_TOOLBAR], 50 );
	gDrawColors[RW_MENUBAR]			= gSysColors[RW_clrBtnFace];
	gDrawColors[RW_MENUBARTXT]		= RWSetContrast(gSysColors[RW_clrBtnText], gDrawColors[RW_TOOLBAR], 180 );

	gDrawColors[RW_ICONSHADOW]		= RWBlendColors( 0x00000000, gDrawColors[RW_TBBTNFACEHOT], 25 );
	gDrawColors[RW_DISTEXT]			= RWBlendColors( gSysColors[RW_clrBtnShadow], gSysColors[RW_clrWindow], 90 );
	gDrawColors[RW_GRIPPER]			= RWSetContrast( RWBlendColors( gSysColors[RW_clrBtnShadow], gSysColors[RW_clrWindow], 75 ), gDrawColors[RW_TOOLBAR], 85 );
}

RWTHEMEAPI(void) RWResetO2K3Colors(HWND hwnd)
{
	HTHEME hTheme = NULL;
	if(!hwnd)
	{
		// SRSTUDIO-1482
		return;
	}

	DWORD dwVersion = ::GetVersion();
	if(((BYTE)dwVersion >= 6) && RWIsThemeActive() && RWIsAppThemed()) // Windows Vista
	{
		// Manually create the colors. Defaults to colors from Luna Blue Theme
		gO2K3Colors[RW_O2K3_THEMEGRADIENT1]		= RGB(136, 174, 228); // Dark Blue
		gO2K3Colors[RW_O2K3_THEMEGRADIENT2]		= RGB(220, 235, 254); // Light Blue
		gO2K3Colors[RW_O2K3_THEMEBACKGROUND]	= RGB(158, 190, 245); // Blend
		gO2K3Colors[RW_O2K3_THEMETBHOT]			= RGB(255, 180, 95);  // Orange
		gO2K3Colors[RW_O2K3_THEMETBHOTDARK]		= RGB(247, 154, 8);
		gO2K3Colors[RW_O2K3_THEMEMENUHOT]		= RGB(255, 240, 189);
		gO2K3Colors[RW_O2K3_THEMEEDGEFILL]		= RGB(49, 105, 198);
		gO2K3Colors[RW_O2K3_THEMEEDGEDARK]      = RGB(0, 0, 0);

	}else if( RWIsAppThemed() && RWIsThemeActive() )
	{
		WCHAR pszThemeName[MAX_PATH];
		WCHAR pszColor[MAX_PATH];
		WCHAR pszSize[MAX_PATH];
		BOOL bThemeNameGradients = FALSE;

		if(RWGetCurrentThemeName(pszThemeName, MAX_PATH, pszColor, MAX_PATH, pszSize, MAX_PATH) == S_OK)
		{
			if(wcsstr(_wcslwr(pszThemeName), L"luna.msstyles"))
			{
				if(wcscmp(_wcslwr(pszColor), L"normalcolor") == 0)
				{
					// "LunaBlue";
					gO2K3Colors[RW_O2K3_THEMEGRADIENT1]		= RGB(136, 174, 228); // Dark Blue
					gO2K3Colors[RW_O2K3_THEMEGRADIENT2]		= RGB(220, 235, 254); // Light Blue
					//gO2K3Colors[RW_O2K3_THEMEBACKGROUND]	= RGB(158, 190, 245); // Blend
					//gO2K3Colors[RW_O2K3_THEMETBHOT]			= RGB(255, 180, 95);  // Orange
					bThemeNameGradients = TRUE;
				}else if(wcscmp(_wcslwr(pszColor), L"homestead") == 0)
				{
					// "LunaOlive";
					gO2K3Colors[RW_O2K3_THEMEGRADIENT1]		= RGB(187, 202, 149); // Dark Olive
					gO2K3Colors[RW_O2K3_THEMEGRADIENT2]		= RGB(230, 237, 202); // Light Blue
					//gO2K3Colors[RW_O2K3_THEMEBACKGROUND]	= RGB(217, 217, 167); // Blend
					//gO2K3Colors[RW_O2K3_THEMETBHOT]			= RGB(255, 180, 95);  // Orange
					bThemeNameGradients = TRUE;
				}else if(wcscmp(_wcslwr(pszColor), L"metallic") == 0)
				{
					// "LunaSilver";
					gO2K3Colors[RW_O2K3_THEMEGRADIENT1]		= RGB(166, 165, 191); // Dark Silver
					gO2K3Colors[RW_O2K3_THEMEGRADIENT2]		= RGB(238, 239, 246); // Light Silver
					//gO2K3Colors[RW_O2K3_THEMEBACKGROUND]	= RGB(215, 215, 229); // Blend
					//gO2K3Colors[RW_O2K3_THEMETBHOT]			= RGB(255, 180, 95);  // Orange
					bThemeNameGradients = TRUE;
				}else
				{
					// Default Luna Blue
					//strText = "LunaBlue";
					gO2K3Colors[RW_O2K3_THEMEGRADIENT1]		= RGB(136, 174, 228); // Dark Blue
					gO2K3Colors[RW_O2K3_THEMEGRADIENT2]		= RGB(220, 235, 254); // Light Blue
					gO2K3Colors[RW_O2K3_THEMEBACKGROUND]	= RGB(158, 190, 245); // Blend
					gO2K3Colors[RW_O2K3_THEMETBHOT]			= RGB(255, 180, 95);  // Orange
					gO2K3Colors[RW_O2K3_THEMETBHOTDARK]		= RGB(247, 154, 8);
					gO2K3Colors[RW_O2K3_THEMEMENUHOT]		= RGB(255, 240, 189);
					gO2K3Colors[RW_O2K3_THEMEEDGEFILL]		= RGB(49, 105, 198);
					gO2K3Colors[RW_O2K3_THEMEEDGEDARK]      = RGB(0, 0, 0);
				}
			}		
		}// RWGetCurrentThemeName()

		if(FALSE == bThemeNameGradients)
		{
			gO2K3Colors[RW_O2K3_THEMEGRADIENT1] = ::GetSysColor(COLOR_GRADIENTINACTIVECAPTION);
			gO2K3Colors[RW_O2K3_THEMEGRADIENT2] = ::GetSysColor(COLOR_INACTIVECAPTIONTEXT);
		}
		
		COLORREF cGrad1 = gO2K3Colors[RW_O2K3_THEMEGRADIENT1];
		COLORREF cGrad2 = gO2K3Colors[RW_O2K3_THEMEGRADIENT2];
		gO2K3Colors[RW_O2K3_THEMEBACKGROUND] = RGB((GetRValue(cGrad1) + GetRValue(cGrad2))/2,
												   (GetGValue(cGrad1) + GetGValue(cGrad2))/2,
												   (GetBValue(cGrad1) + GetBValue(cGrad2))/2);

		if(hwnd) // SRSTUDIO-1482
		{
			hTheme = RWOpenThemeData( hwnd, L"TASKBAND" );
		}
		if(hTheme)
		{
			RWGetThemeColor(hTheme, TDP_FLASHBUTTON, 0, TMT_ACCENTCOLORHINT, &gO2K3Colors[RW_O2K3_THEMETBHOT]);
			gO2K3Colors[RW_O2K3_THEMETBHOTDARK] = RWAdjustContrast(gO2K3Colors[RW_O2K3_THEMETBHOT], gO2K3Colors[RW_O2K3_THEMETBHOT], -0.45);
			gO2K3Colors[RW_O2K3_THEMEMENUHOT] = RGB(255, 240, 189);
			RWGetThemeColor(hTheme, TDP_FLASHBUTTON, 0, TMT_EDGEFILLCOLOR, &gO2K3Colors[RW_O2K3_THEMEEDGEFILL]);
			RWGetThemeColor(hTheme, TDP_FLASHBUTTON, 0, TMT_EDGEDKSHADOWCOLOR, &gO2K3Colors[RW_O2K3_THEMEEDGEDARK]);
		}
	}

	if((NULL == hwnd) || (NULL == hTheme))
	{
		// Manually create the colors. Defaults to colors from Luna Blue Theme
		gO2K3Colors[RW_O2K3_THEMEGRADIENT1]		= RGB(136, 174, 228); // Dark Blue
		gO2K3Colors[RW_O2K3_THEMEGRADIENT2]		= RGB(220, 235, 254); // Light Blue
		gO2K3Colors[RW_O2K3_THEMEBACKGROUND]	= RGB(158, 190, 245); // Blend
		gO2K3Colors[RW_O2K3_THEMETBHOT]			= RGB(255, 180, 95);  // Orange
		gO2K3Colors[RW_O2K3_THEMETBHOTDARK]		= RGB(247, 154, 8);
		gO2K3Colors[RW_O2K3_THEMEMENUHOT]		= RGB(255, 240, 189);
		gO2K3Colors[RW_O2K3_THEMEEDGEFILL]		= RGB(49, 105, 198);
		gO2K3Colors[RW_O2K3_THEMEEDGEDARK]      = RGB(0, 0, 0);
	}
	if(hTheme)
	{
		RWCloseThemeData(hTheme);
	}
}

RWTHEMEAPI(COLORREF) RWGetDNETColor( DWORD colorId )
{
	// QA: 32441
	if(!RWGetSecData().m_bUpdateSysColorsCalled)
	{
		RWGetSecData().UpdateSysColors();
	}
	if( colorId >= RW_DRAWCOLORELEMS )
		return 0x00FFFFFF;

	return gDrawColors[colorId];
}

RWTHEMEAPI(COLORREF) RWGetO2K3Color( DWORD colorId )
{
	// QA: 32441
	if(!RWGetSecData().m_bUpdateSysColorsCalled)
	{
		RWGetSecData().UpdateSysColors();
	}
	if( colorId >= RW_DRAWCOLORELEMS )
		return 0x00FFFFFF;

	return gO2K3Colors[colorId];
}

// Internal Function
void RGBToHSL(COLORREF _color, float* _h, float* _s, float* _l)
{
	float delta;
	float r = (float)GetRValue(_color)/255;
	float g = (float)GetGValue(_color)/255;
	float b = (float)GetBValue(_color)/255;   
	float cmax = max(r,max(g,b));
	float cmin = min(r,min(g,b));   
	*_l = (cmax + cmin) / 2.0f;   

	if(cmax==cmin) 
	{
		*_s = 0;      
		*_h = 0;  
	}else 
	{
		if( *_l < 0.5f ) 
			*_s = (cmax-cmin)/(cmax+cmin);      
		else
			*_s = (cmax-cmin)/(2.0f-cmax-cmin);      
		delta = cmax - cmin;
		if( r == cmax ) 
			*_h = (g-b)/delta;      
		else if( g == cmax )
			*_h = 2.0f +(b-r)/delta;
		else          
			*_h = 4.0f + (r-g)/delta;
		*_h /= 6.0f; 
		if( *_h < 0.0f )
			*_h += 1.0f;  
	}
}

// Internal Function
float HueToRGB(float _m1, float _m2, float _h)
{
	if( _h < 0.0f ) _h += 1.0f;
	if( _h > 1.0f ) _h -= 1.0f;
	if( 6.0f*_h < 1.0f )
		return (_m1+(_m2-_m1)*_h*6.0f);
	if( 2.0f*_h < 1.0f )
		return _m2;
	if( 3.0f*_h < 2.0f )
		return (_m1+(_m2-_m1)*((2.0f/3.0f)-_h)*6.0f);
	return _m1;
}

// Internal Function
COLORREF HSLToRGB(float& _h, float& _s, float& _l)
{
	float r,g,b;
	float m1, m2;
	if( _s==0 )
	{
		r = g = b = _l;
	}
	else
	{
		if( _l <= 0.5f )
			m2 = _l*(1.0f+_s);
		else
			m2 = _l+_s-_l*_s;
		m1 = 2.0f*_l-m2;
		r = HueToRGB(m1,m2,_h+1.0f/3.0f);
		g = HueToRGB(m1,m2,_h);
		b = HueToRGB(m1,m2,_h-1.0f/3.0f);
	}
	return RGB((BYTE)(r*255),(BYTE)(g*255),(BYTE)(b*255));
}

RWTHEMEAPI(COLORREF) RWAdjustHSL(COLORREF color, float percentH, float percentS, float percentL)
{
	float H = 0.0f, L = 0.0f, S = 0.0f;
	RGBToHSL( color, &H, &S, &L );

	if( percentH > 0.0f )
		H = H + (1.0f - H) * percentH;
	else if ( percentH < 0.0f )
		H = H * (1.0f + percentH);
	if( H < 0.0f )
		H = 0.0f;
	else if( H > 1.0f )
		H = 1.0f;

	if( percentL > 0.0f )
		L = L + (1.0f - L) * percentL;
	else if ( percentL < 0.0f )
		L = L * (1.0f + percentL);
	if( L < 0.0f )
		L = 0.0f;
	else if( L > 1.0f )
		L = 1.0f;

	if ( percentS > 0.0f )
		S = S + (1.0f - S) * percentS;
	else if ( percentS < 0.0f )
		S = S * (1.0f + percentS);
	if( S < 0.0f )
		S = 0.0f;
	else if( S > 1.0f )
		S = 1.0f;

	return HSLToRGB( H, S, L );
}
