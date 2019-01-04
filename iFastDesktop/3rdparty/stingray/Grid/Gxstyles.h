// This is a part of the Objective Grid C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
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
//          Supplement Section 227.7202, Government’s use, duplication or 
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
// Author: Stefan Hoenig
//

// gxstyles.h : header file
//

#ifndef _GXSTYLES_H_
#define _GXSTYLES_H_

#ifndef _GXCOLL_H_
#include "grid\gxcoll.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA	GX_DATAEXT
#endif

// header file

class CGXStylesMap;

// enums

enum GXBorderType {
		gxBorderAll = -1,
		gxBorderLeft = 0,
		gxBorderRight = 1,
		gxBorderTop = 2,
		gxBorderBottom = 3
	};

enum GXDraw3dFrameType {
		gxFrameNormal = 0,
		gxFrameRaised = 1,
		gxFrameInset = 2
	};

// Automatic alignment based on format
#define GX_JUST_AUTO	3

/* Cell Formats */

#define GX_FMT_DEFAULT		0
#define GX_FMT_FLOAT		1
#define GX_FMT_FIXED		2
#define GX_FMT_GEN			3
#define GX_FMT_DOLLARS		4
#define GX_FMT_COMMA		5
#define GX_FMT_HEX			6
#define GX_FMT_LOGIC		7
#define GX_FMT_DAY_MONTH_YEAR	8
#define GX_FMT_DAY_MONTH		9
#define GX_FMT_MONTH_YEAR		10
#define GX_FMT_DATE			11
#define GX_FMT_HIDDEN		12
#define GX_FMT_TIME			13
#define GX_FMT_PERCENT		14
#define GX_FMT_TEXT			15
#define GX_FMT_INTL_DATE	16
#define GX_FMT_ISO8061_DATE	17
#define GX_FMT_DATETIME		18
#define GX_FMT_USER1		19
#define GX_FMT_USER2		20
#define GX_FMT_USER3		21
#define GX_FMT_USER4		22

#define GX_FMT_FIXED_PARENS				23
#define GX_FMT_MIXED_FRACTIONS    		24
#define GX_FMT_TIME_HM_AMPM				25
#define GX_FMT_TIME_HMS_AMPM			26
#define GX_FMT_TIME_HM					27
#define GX_FMT_NUMLOCALE				28
#define GX_FMT_MAXVAL					28

#define GX_CHECK_FORMAT(X)		((X)>=0 && (X)<=GX_FMT_MAXVAL)
#define GX_CHECK_PLACES(X)		((X)>=0 && (X)<=15)

#define GX_IS_DATE_FORMAT(X)	((X)==GX_FMT_DAY_MONTH_YEAR || \
				 (X)==GX_FMT_DAY_MONTH || \
				 (X)==GX_FMT_MONTH_YEAR || \
				 (X)==GX_FMT_DATE || \
				 (X)==GX_FMT_DATETIME)

#define GX_IS_TIME_FORMAT(X)	((X)==GX_FMT_TIME)

// Value Types
#define GX_VT_STRING		0
#define GX_VT_NUMERIC		1
#define GX_VT_EXPRESSION	2
#define GX_VT_ERROR			3

// Support for system colors

#define GXSYSCOLOR(n) ( ((DWORD)(BYTE)(254-n))<<24 | GXGetSysData()->GetSysColor(n) )
#define GXISSYSCOLOR(rgbclr)( (BYTE)((rgbclr)>>24) > 64 && (BYTE)((rgbclr)>>24) <= 254 )
#define GXGETSYSCOLOR(rgbclr) ( GXISSYSCOLOR(rgbclr) ? 254-(BYTE)((rgbclr)>>24) : 0 )
#define GXGETCOLOR(rgbclr)( GXISSYSCOLOR(rgbclr) ? GXGetSysData()->GetSysColor(254-(int)((rgbclr)>>24)) : rgbclr)

// Support for brush and pen colors with separate hi-byte (0 - 24-Bit RGB, 1 - Palette Index, 2 - Palette RGB, 3 - System Color)
#define GXGETCOLOR2(n1, n2)		( (COLORREF) ((n1 == 3) ? GXGetSysData()->GetSysColor((int) n2) : (n1 << 24 | n2) ))
#define GXGETCOLORNA2(n1, n2)	( (COLORREF) ((n1 == 3) ? GXSYSCOLOR((int) n2) : (n1 << 24 | n2) ))
// GXCOLOR1 - Hi-Byte
#define GXCOLOR1(rgbclr)		( GXISSYSCOLOR(rgbclr) ? 3 : (BYTE)((rgbclr)>>24))
// GXCOLOR2 - Color (3 Bytes)
#define GXCOLOR2(rgbclr)		( GXISSYSCOLOR(rgbclr) ? GXGETSYSCOLOR(rgbclr) : ((rgbclr)<<8)>>8 )

class CGXRange;
class CGXFont;


struct CGXFontInfo
{
	CGXFontInfo();

	TCHAR lfFaceName[LF_FACESIZE*2+3];// 67 Byte: Facename (Script)
	BYTE nFaceLen;
	BYTE lfPitchAndFamily;
	BYTE nCharSet;
	unsigned nFontIndex : 10; // max. 1024 fonts available (see GX_FONT_STATE::m_apUsedFonts)
	unsigned nFontType: 3;// TRUETYPE_FONTTYPE, DEVICE_FONTTYPE, RASTER_FONTTYPE
	unsigned nInstalled : 1;
	unsigned nDefaultCharset : 1;
};

#define GX_DEFAULT_FACENAME		1023
#define GX_DEFAULT_ORIENTATION	511
#define GX_DEFAULT_WEIGHT		15
#define GX_DEFAULT_SIZE			0

class CGXFont: public CObject
{
	DECLARE_SERIAL(CGXFont)

public:
	// operations
	CGXFont();
	CGXFont(LPCTSTR pszDescription);
	CGXFont(const LOGFONT& lf);
	CGXFont(const CGXFont& font);

	const CGXFont& operator=(const CGXFont& font);
	const CGXFont& operator=(const LOGFONT& lf);

	// LogFont
	const LOGFONT& GetLogFontRef() const;
	LOGFONT GetLogFont(int nZoom = 100) const;
	CGXFont& SetLogFont(const LOGFONT& lf);
	operator LOGFONT() const;
	operator const LOGFONT*() const;
	BOOL operator==(const CGXFont& font) const;
	BOOL operator!=(const CGXFont& font) const;

	CGXFont& SetDefault();
	CGXFont& ChangeFont(const CGXFont& font, GXModifyType mt);
	BOOL IsSubSet(const CGXFont& fontSubSet) const; // is font subset from this

	void Serialize(CArchive &ar);

	void WriteProfile(LPCTSTR pszSection, LPCTSTR pszEntry) const;
	BOOL ReadProfile(LPCTSTR pszSection, LPCTSTR pszEntry);

	CGXFont& SetDescription(LPCTSTR szDescription);
	CString GetDescription() const;
	void GetDescription(LPTSTR s) const;

	BOOL IsEmptyFont() const;
	GXBYTE8 GetFontKey() const;
	BOOL IsEqual(const CGXFont& font) const;

	~CGXFont();

protected:
	void Init();

	// LogFont structure (with reference count)
	CGXFontData* GetData(GXBYTE8 key) const;
	CGXFontData* GetData() const;
	void Release(GXBYTE8 key);
	void Release();
	void InitLogFont(LOGFONT& lf) const;

	// static helper functions
	static unsigned AFXAPI Size_lf2ui(double lfSize);
	static double AFXAPI Size_ui2lf(unsigned nSize);
	static unsigned AFXAPI Orientation_lf2ui(LONG lfOrientation);
	static LONG AFXAPI Orientation_ui2lf(unsigned nOrientation);
	static unsigned AFXAPI Weight_lf2ui(LONG lfWeight);
	static LONG AFXAPI Weight_ui2lf(unsigned nWeight);
	static unsigned AFXAPI FaceName_str2ui(LPCTSTR lfFaceName);
	static LPCTSTR AFXAPI FaceName_ui2str(unsigned nFaceName);

// Attributes
protected:
	union
	{
		struct
		{
			unsigned fontdata : 1;// TRUE if associated CGXFontData exists (and should be freed)

			// include bits
			// weight, size, facename see below
			unsigned italic : 1;
			unsigned underline: 1;
			unsigned strikeout: 1;

			// settings
			unsigned nWeight: 4;	// 15 - not included, weight stored in 100 steps (0-10)
			unsigned nSize: 10;	// 0 - not included
			unsigned nItalic: 1;
			unsigned nUnderline : 1;
			unsigned nStrikeOut : 1;
			unsigned nOrientation : 9;// 511 - not included, orientation stored in 15 degree steps (0-24)
			unsigned nFaceName:10;	// 1023 - not included, index to array with face names
			//----
			// Total 36 Bits - same size as a GXBYTE8
		} fontbits;

		GXBYTE8 m_b8Value;
	};

// Access member functions
public:
	// weight
	BOOL GetIncludeWeight() const;
	CGXFont& SetIncludeWeight(BOOL b);
	LONG GetWeight() const;
	CGXFont& SetWeight(LONG nWeight);

	BOOL GetBold() const;
	CGXFont& SetBold(BOOL b);

	// Italic
	BOOL GetIncludeItalic() const;
	CGXFont& SetIncludeItalic(BOOL b);
	BOOL GetItalic() const;
	CGXFont& SetItalic(BOOL b);

	// Underline
	BOOL GetIncludeUnderline() const;
	CGXFont& SetIncludeUnderline(BOOL b);
	BOOL GetUnderline() const;
	CGXFont& SetUnderline(BOOL b);

	// StrikeOut
	BOOL GetIncludeStrikeOut() const;
	CGXFont& SetIncludeStrikeOut(BOOL b);
	BOOL GetStrikeOut() const;
	CGXFont& SetStrikeOut(BOOL b);

	// Size
	BOOL GetIncludeSize() const;
	CGXFont& SetIncludeSize(BOOL b);
	double GetSize() const;
	CGXFont& SetSize(double size);

	// Orientation
	BOOL GetIncludeOrientation() const;
	CGXFont& SetIncludeOrientation(BOOL b);
	LONG GetOrientation() const;
	CGXFont& SetOrientation(LONG Orientation);

	// FaceName
	BOOL GetIncludeFaceName() const;
	CGXFont& SetIncludeFaceName(BOOL b);
	LPCTSTR GetFaceName() const;
	CGXFont& SetFaceName(LPCTSTR facename);
	unsigned GetFaceNameId() const;
	CGXFont& SetFaceNameId(unsigned nFaceName);

public:
	// constants
	static LPCTSTR szArial;

	friend class CGXStyleSerializeImp;
	friend class CGXFontFTR;
};

CArchive& AFXAPI operator <<(CArchive& ar, const CGXFont& font);
CArchive& AFXAPI operator >>(CArchive& ar, CGXFont& font);

// Brush

// Patterns (used in brushes)
const CBitmap* AFXAPI GXGetPatternBitmap(int n);

struct CGXBrush
{
	static LPCTSTR szBrushFormat;

// Attributes
	unsigned lbHatch : 3;
	//unsigned notused : 1;
	unsigned long lbColor1: 2;// 0 - 24-Bit RGB, 1 - Palette Index, 2 - Palette RGB, 3 - System Color
	unsigned long lbBkColor1: 2;// 0 - 24-Bit RGB, 1 - Palette Index, 2 - Palette RGB, 3 - System Color
	unsigned long lbColor2: 24;
	unsigned long lbBkColor2: 24;
	// Increased number of bits for lbPattern, remove notused.
	unsigned lbPattern : 7;
	unsigned lbStyle : 2;
	//----
	// Total64 Bits

// construction
	CGXBrush();
	CGXBrush(const LOGBRUSH& logbrush);
	CGXBrush(const CGXBrush& brush);
	CGXBrush(LPCTSTR pszDescription);
	CGXBrush(UINT style, COLORREF color, LONG hatch);

// copying
	CGXBrush& operator=(const CGXBrush& brush);
	operator tagLOGBRUSH() const;
	operator const tagLOGBRUSH*() const;

// comparing
	BOOL operator==(const CGXBrush& brush) const;
	BOOL operator!=(const CGXBrush& brush) const;
	GXBYTE8 GetBrushKey() const;

// attributes
	UINT GetStyle() const;
	CGXBrush& SetStyle(UINT style);
	COLORREF GetColor() const;
	COLORREF GetColorNA() const;
	CGXBrush& SetColor(COLORREF color);
	LONG GetHatch() const;
	CGXBrush& SetHatch(LONG hatch);
	int GetPattern() const;
	CGXBrush& SetPattern(int nPattern);
	COLORREF GetBkColor() const;
	COLORREF GetBkColorNA() const;
	CGXBrush& SetBkColor(COLORREF color);

// description
	CGXBrush& SetDescription(LPCTSTR szDescription);
	CString GetDescription() const;
	void GetDescription(LPTSTR s) const;
};

CArchive& AFXAPI operator <<(CArchive& ar, const CGXBrush& lb);
CArchive& AFXAPI operator >>(CArchive& ar, CGXBrush& lb);

// Pen

#define GX_PS_DEFAULT 7

struct CGXPen
{
	static LPCTSTR szPenFormat;

// Attributes
	unsigned lopnStyle : 3;
	unsigned lopnWidth : 16;
	unsigned long lopnColor1: 2;
	unsigned long lopnColor2: 24;
	// Total ----
	// 45 Bits -> same size as a GXBTYE8
	// not included -> lopnstyle = 7

// construction
	CGXPen();
	CGXPen(const tagLOGPEN& logpen);
	CGXPen(const CGXPen& pen);
	CGXPen(LPCTSTR szDescription);
	CGXPen(UINT style, int width, COLORREF color);

// assignment
	CGXPen& operator=(const tagLOGPEN& logpen);
	CGXPen& operator=(const CGXPen& pen);
	operator tagLOGPEN() const;
	operator tagLOGPEN*() const;

// comparing
	BOOL operator==(const CGXPen& pen) const;
	BOOL operator!=(const CGXPen& pen) const;
	GXBYTE8 GetPenKey() const;

// attributes
	CGXPen& SetInclude(BOOL b);
	BOOL GetInclude() const;
	UINT GetStyle() const;
	CGXPen& SetStyle(UINT style);
	int GetWidth() const;
	CGXPen& SetWidth(int width);
	COLORREF GetColor() const;
	COLORREF GetColorNA() const;
	CGXPen& SetColor(COLORREF color);

// description
	CGXPen& SetDescription(LPCTSTR szDescription);
	CString GetDescription() const;
	void GetDescription(LPTSTR s) const;

// optimize drawing for vertical and horizontal lines
	BOOL CreateCompatibleBrush(CGXBrush& br, const CGXBrush& brInterior, BOOL bHorzOrVert, BOOL bBlackWhite) const;
};

CArchive& AFXAPI operator <<(CArchive& ar, const CGXPen& lp);
CArchive& AFXAPI operator >>(CArchive& ar, CGXPen& lp);

// simple wrapper class for using strings directly from a resource id.

class CGXResourceString: public CString
{
public:
	CGXResourceString(UINT nID);
};


/////////////////////////////////////////////////////////////////////
// abstract CGXAbstractUserAttribute class

class CGXAbstractUserAttribute: public CObject
{
	DECLARE_SERIAL(CGXAbstractUserAttribute);

public:
	CGXAbstractUserAttribute();
	virtual ~CGXAbstractUserAttribute();

	// Change value, update the grid, generate undo info
	virtual CGXAbstractUserAttribute& SetValue(const CString& strValue);
	virtual CGXAbstractUserAttribute& SetValue(LPCTSTR pszValue);

	// Simply return the value
	virtual const CString& GetValue() const;
	virtual DWORD GetDWordValue() const;
	virtual LONG GetLongValue() const;
	virtual double GetDoubleValue() const;

	// Copying attribute (e.g. from one style object to another)
	virtual CGXAbstractUserAttribute* Clone() const;

	virtual void Serialize(CArchive& ar);

	// Comparision
	virtual BOOL IsEqual(const CGXAbstractUserAttribute& p) const; // (TRUE if equal)

	operator LPCTSTR() const;

	virtual BOOL IsEmpty() const;

private:
	// Disable the copy constructor and assignment by default so you will get
	//   compiler errors instead of unexpected behaviour if you pass objects
	//   by value or assign objects.
	CGXAbstractUserAttribute(const CGXAbstractUserAttribute& src);  // no implementation
	void operator=(const CGXAbstractUserAttribute& src);            // no implementation

	// Note: The correct way to copy user attributes is to call Clone()

public:
	WORD m_nId;
	static CString m_strValueCache;	// Value to be used for converting into a string in GetValue
};

/////////////////////////////////////////////////////////////////////
// CGXUserAttribute class for C++ datatypes

class CGXUserAttribute: public CGXAbstractUserAttribute
{
	DECLARE_SERIAL(CGXUserAttribute);

public:
	CGXUserAttribute();
	CGXUserAttribute(DWORD value);
	CGXUserAttribute(LONG value);
	CGXUserAttribute(const CString& value);
	CGXUserAttribute(LPCTSTR value);
	CGXUserAttribute(double value);
	CGXUserAttribute(GXBYTE8 value);
	CGXUserAttribute(const CGXUserAttribute& p);
	virtual ~CGXUserAttribute();

	virtual CGXAbstractUserAttribute& SetValue(LPCTSTR pszValue);
	virtual const CString& GetValue() const;
	virtual DWORD GetDWordValue() const;
	virtual LONG GetLongValue() const;
	virtual double GetDoubleValue() const;
	virtual void Serialize(CArchive& ar);

	// Copying attribute (e.g. from one style object to another)
	virtual CGXAbstractUserAttribute* Clone() const;

	// Comparision
	virtual BOOL IsEqual(const CGXAbstractUserAttribute& p) const; // (TRUE if equal)

protected:
	typedef enum
	{
		vtEmpty,
		vtDWord,
		vtLong,
		vtShortString,
		vtString,
		vtDouble,
		vtByte8
	} ValueType;

	ValueType m_vtType;
	union
	{
		DWORD dwValue;
		LONG lValue;
		LPTSTR pszValue;
		TCHAR szShortString[8/sizeof(TCHAR)];
		double dValue;
		GXBYTE8 b8Value;
	} m_value;

	friend class CGXUserAttributeFTR;
};


/////////////////////////////////////////////////////////////////////
// CGXEllipseUserAttribute class for gxEllipseType
// used by CGXDrawingAndFormatting for ellipse setting

enum gxEllipseType
{
	gxNoEllipse			= 0, // no ellipse...the default setting
	gxDotEllipse		= 1, // Dotted ellipse ...
	gxPoundEllipse		= 2, // Pound ellipses ####
};


class CGXEllipseUserAttribute: public CGXAbstractUserAttribute
{
	DECLARE_SERIAL(CGXEllipseUserAttribute);
public:
	CGXEllipseUserAttribute();
	CGXEllipseUserAttribute(gxEllipseType type);
	CGXEllipseUserAttribute(const CGXEllipseUserAttribute& p);

	virtual ~CGXEllipseUserAttribute();

	virtual CGXAbstractUserAttribute& SetValue(const CString& strValue);
	virtual CGXAbstractUserAttribute& SetValue(LPCTSTR pszValue);

	// this is the interface to be used
	virtual CGXAbstractUserAttribute& SetEllipseValue(gxEllipseType type);


	// Return the value
	virtual const CString& GetValue() const;
	virtual DWORD GetDWordValue() const;
	virtual LONG GetLongValue() const;
	virtual double GetDoubleValue() const;

	// this is to be used
	virtual gxEllipseType GetEllipseValue() const;

	// Copying attribute (e.g. from one style object to another)
	virtual CGXAbstractUserAttribute* Clone() const;

	virtual void Serialize(CArchive& ar);

	// Comparision
	virtual BOOL IsEqual(const CGXAbstractUserAttribute& p) const; // (TRUE if equal)

	virtual BOOL IsEmpty() const;

protected:
	gxEllipseType m_gxEllipseType;

	friend class CGXEllipseUserAttributeFTR;
};


/////////////////////////////////////////////////////////////////////
// CGXUserAttributeMap

class CGXUserAttributeMap: public CObArray
{
	DECLARE_SERIAL(CGXUserAttributeMap)
public:

// Construction
	CGXUserAttributeMap();
	~CGXUserAttributeMap();

// Empty
	void Empty();
	BOOL IsEmpty() const;

// Attributes (each CGXUserAttributeMap always holds its own
	// attribute objects on the heap)
	void SetAttribute(WORD nID, const CGXAbstractUserAttribute& value);
	void SetAttributePtr(WORD nID, CGXAbstractUserAttribute* pValue);
	void DeleteAttribute(WORD nID);
	const CGXAbstractUserAttribute* GetAttribute(WORD nID) const;

	void ChangeMap(const CGXUserAttributeMap* pSrc, GXModifyType mt);

	int FindAttribute(WORD nID) const;
	void Sort();

// Operations
	void WriteProfile(LPCTSTR pszSection) const;
	BOOL ReadProfile(LPCTSTR pszSection);
	void Serialize(CArchive& ar);

// compatibility with OG 5
	void AppendOG5Map(CGXCollMapDWordToString* pSrc);
};


// cell style

class CGXStyle : public CObject
{
	DECLARE_SERIAL(CGXStyle)

public:
	// operations
	CGXStyle();
	CGXStyle(const CGXStyle& p);
	CGXStyle(LPCTSTR s);

	virtual ~CGXStyle();

	virtual CGXStyle* Clone() const;// create a new style with "new CGXStyle(*this);"

	virtual const CGXStyle& operator=(const CGXStyle& p);
	virtual const CGXStyle& operator=(LPCTSTR s);

	virtual CGXStyle& SetDefault();

	virtual BOOL IsSubSet(const CGXStyle& styleSubSet) const; // is styleSubSet subset from this

	virtual void Serialize(CArchive& ar);
	virtual void Serialize(CArchive& ar, const CGXStylesMap* pStylesMap);

	virtual void WriteProfile(LPCTSTR pszSection, const CGXStylesMap* pStylesMap) const;
	virtual BOOL ReadProfile(LPCTSTR pszSection, const CGXStylesMap* pStylesMap);

	virtual void LoadBaseStyle(const CGXStylesMap& stylesmap);
	virtual void ChangeStyle(const CGXStyle& p, GXModifyType mt);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual void Free();

	static void AFXAPI ImplementCompareSubset();
	static void AFXAPI ImplementSerialize();
	static void AFXAPI ImplementSerializeOG5Compatible();
	static void AFXAPI ImplementProfile();

protected:
	void ConstructStyle();

// Attributes
public:

	struct STYLEBITS
	{
		unsigned horzalign: 1;
		unsigned vertalign: 1;
		unsigned readonly : 1;
		unsigned control: 1;
		unsigned interior : 1;
		unsigned textcolor: 1;
		unsigned wraptext : 1;
		unsigned allowenter : 1;
		unsigned borders: 1;
		unsigned font : 1;
		unsigned value: 1;
		unsigned choicelist : 1;
		unsigned vertscroll : 1;
		unsigned maxlength: 1;
		unsigned basestyle: 1;
		unsigned enabled: 1;
		unsigned tristate : 1;
		unsigned draw3dframe: 1;
		unsigned userattr : 1;
		unsigned autosize : 1;
		unsigned itemdataptr: 1;
		unsigned floodcell: 1;
		unsigned floatcell: 1;
		unsigned mergecell: 1;
		unsigned format:1;
		unsigned places:1;
				//24 Bits

		DWORD GetPortable() const;
		void SetPortable(DWORD dw);
		STYLEBITS(DWORD dw = 0);
		DWORD GetNoPortableBits() const;
        void SetNoPortableBits(DWORD dw);
        BOOL NoPortableIsEmptyBits() const;
	};

protected:
	STYLEBITS	stylebits;// 4 Byte

	WORD		m_nMaxLength; // 2 Byte

	CGXBrush	m_lbInterior; // 8 Byte

	WORD		m_nControl; // 2 byte: edit, text, combobox, ...

	struct BOOLS
	{
		unsigned m_nDraw3dFrame : 2;
		unsigned m_bReadOnly: 1;
		unsigned m_bVertScroll: 1;
		unsigned m_bWrapText: 1;
		unsigned m_bAllowEnter: 1;
		unsigned m_bEnabled : 1;
		unsigned m_bTriState: 1;
		unsigned m_bAutoSize: 1;
		unsigned m_bFloodCell : 1;
		unsigned m_bFloatCell : 1;
		unsigned m_nMergeCell : 3;
		unsigned m_nHorizontalAlignment : 2;
		unsigned m_nVerticalAlignment : 2;
		unsigned long m_rgbTextColor1 : 2; // Textcolor
		unsigned m_nValueType : 3;
		unsigned long m_rgbTextColor2 : 24; // Textcolor
		unsigned m_wBaseStyleId : 8;// derive from another style
		unsigned m_nFormat : 5;  // format
		unsigned m_nPlaces : 4;  // precision
		// 64 Bits

	} boolbits; // 8 Byte

	CGXPen* m_pPenArray;	// pointer to array with borders
		// 4 byte

	CGXFont* m_pFont;	// pointer to font structure
		// 4 byte

	CString m_sValue;
		// 4 byte

	CString m_sChoiceList;	// used for DropDown-Lists, Items are separated with newline
		// 4 byte

	CGXUserAttributeMap*	// The programmer can use extra attributes for derived CGXControls
				m_pmapUserAttributes;	// key is an String-Resource-Id, value is a CGXAbstractUserAttribute
		// 4 byte

	void* m_pItemDataPtr;
		// 4 byte

	// Total = 50 byte for empty style object
	//         + heap allocations (choice list, value string, user attributes, pen array 4x4Byte)

// Access member functions
public:

	// Horizontal Alignment
	BOOL GetIncludeHorizontalAlignment() const;
	CGXStyle& SetIncludeHorizontalAlignment(BOOL b);
	DWORD GetHorizontalAlignment() const;
	CGXStyle& SetHorizontalAlignment(DWORD dwAlign);

	// Vertical Alignment
	BOOL GetIncludeVerticalAlignment() const;
	CGXStyle& SetIncludeVerticalAlignment(BOOL b);
	DWORD GetVerticalAlignment() const;
	CGXStyle& SetVerticalAlignment(DWORD dwAlign);

	// Readonly
	BOOL GetIncludeReadOnly() const;
	CGXStyle& SetIncludeReadOnly(BOOL b);
	BOOL GetReadOnly() const;
	CGXStyle& SetReadOnly(BOOL b);

	// Control
	BOOL GetIncludeControl() const;
	CGXStyle& SetIncludeControl(BOOL b);
	WORD GetControl() const;
	CGXStyle& SetControl(WORD nControl);

	// MaxLength
	BOOL GetIncludeMaxLength() const;
	CGXStyle& SetIncludeMaxLength(BOOL b);
	WORD GetMaxLength() const;
	CGXStyle& SetMaxLength(WORD nMaxLength);

	// VertScrollBar
	BOOL GetIncludeVertScrollBar() const;
	CGXStyle& SetIncludeVertScrollBar(BOOL b);
	BOOL GetVertScrollBar() const;
	CGXStyle& SetVertScrollBar(BOOL b);

	// Interior
	BOOL GetIncludeInterior() const;
	CGXStyle& SetIncludeInterior(BOOL b);
	CGXBrush GetInterior() const;
	const CGXBrush& GetInteriorRef() const;
	CGXStyle& SetInterior(const CGXBrush& lb);
	CGXStyle& SetInterior(COLORREF rgbColor);

	// Borders
	BOOL GetIncludeBorders() const;
	CGXStyle& SetIncludeBorders(BOOL b);

	CGXPen GetBorders(GXBorderType border) const;
	const CGXPen& GetBordersRef(GXBorderType border) const;
	CGXStyle& SetBorders(GXBorderType border, const CGXPen& pen);
	BOOL GetIncludeBorders(GXBorderType border) const;
	CGXStyle& SetIncludeBorders(GXBorderType border, BOOL b);

	// Font
	BOOL GetIncludeFont() const;
	CGXStyle& SetIncludeFont(BOOL b);
	CGXFont GetFont() const;
	const CGXFont& GetFontRef() const;
	CGXStyle& SetFont(const CGXFont& font, GXModifyType mt = gxOverride);

	// Text Color
	BOOL GetIncludeTextColor() const;
	CGXStyle& SetIncludeTextColor(BOOL b);
	COLORREF GetTextColor() const;
	COLORREF GetTextColorNA() const;
	CGXStyle& SetTextColor(COLORREF rgbColor);

	// WrapText
	BOOL GetIncludeWrapText() const;
	CGXStyle& SetIncludeWrapText(BOOL b);
	BOOL GetWrapText() const;
	CGXStyle& SetWrapText(BOOL b);

	// AutoSize
	BOOL GetIncludeAutoSize() const;
	CGXStyle& SetIncludeAutoSize(BOOL b);
	BOOL GetAutoSize() const;
	CGXStyle& SetAutoSize(BOOL b);

	// Allow Enter
	BOOL GetIncludeAllowEnter() const;
	CGXStyle& SetIncludeAllowEnter(BOOL b);
	BOOL GetAllowEnter() const;
	CGXStyle& SetAllowEnter(BOOL b);

	// Value
	CGXStyle& SetValueType(unsigned nType);
	unsigned GetValueType() const;

	BOOL GetIncludeValue() const;
	CGXStyle& SetIncludeValue(BOOL b);
	const CString& GetValue() const;
	const CString& GetValueRef() const;
	CGXStyle& SetValue(LPCTSTR s);
	CGXStyle& SetValue(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetValue will convert ansi characters
	// to wide characters.
	CGXStyle& SetValue(const char* s);
#endif
	CGXStyle& SetValue(DWORD dw);
	CGXStyle& SetValue(UINT ui);
	CGXStyle& SetValue(WORD w);
	CGXStyle& SetValue(short s);
	CGXStyle& SetValue(LONG l);
	CGXStyle& SetValue(float f);
	CGXStyle& SetValue(double d);
	DWORD GetDWordValue() const;
	WORD GetWordValue() const;
	UINT GetUIntValue() const;
	short GetShortValue() const;
	LONG GetLongValue() const;
	float GetFloatValue() const;
	double GetDoubleValue() const;

	// Basestyle
	BOOL GetIncludeBaseStyle() const;
	CGXStyle& SetIncludeBaseStyle(BOOL b);
	WORD GetBaseStyle() const;
	CGXStyle& SetBaseStyle(WORD wBaseStyleId);

	// Choice list: each choice is separated with a new newline
	BOOL GetIncludeChoiceList() const;
	CGXStyle& SetIncludeChoiceList(BOOL b);
	const CString& GetChoiceList() const;
	const CString& GetChoiceListRef() const;
	CGXStyle& SetChoiceList(LPCTSTR s);
	CGXStyle& SetChoiceList(const CString& s);
#ifdef _UNICODE
	// this special UNICODE version of SetChoiceList will convert ansi characters
	// to wide characters.
	CGXStyle& SetChoiceList(const char* s);
#endif

	// Enabled
	BOOL GetIncludeEnabled() const;
	CGXStyle& SetIncludeEnabled(BOOL b);
	BOOL GetEnabled() const;
	CGXStyle& SetEnabled(BOOL b);

	// TriState
	BOOL GetIncludeTriState() const;
	CGXStyle& SetIncludeTriState(BOOL b);
	BOOL GetTriState() const;
	CGXStyle& SetTriState(BOOL b);

	// Draw3dFrame
	BOOL GetIncludeDraw3dFrame() const;
	CGXStyle& SetIncludeDraw3dFrame(BOOL b);
	GXDraw3dFrameType GetDraw3dFrame() const;
	CGXStyle& SetDraw3dFrame(GXDraw3dFrameType t);

	// FloatCell
	BOOL GetIncludeFloatCell() const;
	CGXStyle& SetIncludeFloatCell(BOOL b);
	BOOL GetFloatCell() const;
	CGXStyle& SetFloatCell(BOOL b);

	// FloodCell
	BOOL GetIncludeFloodCell() const;
	CGXStyle& SetIncludeFloodCell(BOOL b);
	BOOL GetFloodCell() const;
	CGXStyle& SetFloodCell(BOOL b);

	// MergeCell
	BOOL GetIncludeMergeCell() const;
	CGXStyle& SetIncludeMergeCell(BOOL b);
	unsigned GetMergeCell() const;
	CGXStyle& SetMergeCell(unsigned ui);

	// Format
	BOOL GetIncludeFormat() const;
	CGXStyle& SetIncludeFormat(BOOL b);
	unsigned GetFormat() const;
	CGXStyle& SetFormat(unsigned ui);

	// Places
	BOOL GetIncludePlaces() const;
	CGXStyle& SetIncludePlaces(BOOL b);
	unsigned GetPlaces() const;
	CGXStyle& SetPlaces(unsigned ui);

	// ItemDataPtr
	BOOL GetIncludeItemDataPtr() const;
	CGXStyle& SetIncludeItemDataPtr(BOOL b);
	void* GetItemDataPtr() const;
	CGXStyle& SetItemDataPtr(void* pv);

	// Negative State Text color
	BOOL GetIncludeNegativeStateColor() const;
	CGXStyle& SetIncludeNegativeStateColor(BOOL b);
	DWORD GetNegativeStateColor() const;
	CGXStyle& SetNegativeStateColor(DWORD color);

	// User attributs
	BOOL GetIncludeUserAttribute(WORD nID) const;
	CGXStyle& SetIncludeUserAttribute(WORD nID, BOOL b);
	const CGXAbstractUserAttribute& GetUserAttribute(WORD nID) const;
	void GetUserAttribute(WORD nID, CString& s) const;
	CGXStyle& SetUserAttribute(WORD nID, const CGXAbstractUserAttribute& attribute);
	CGXStyle& SetUserAttributePtr(WORD nID, CGXAbstractUserAttribute* pValue);
	CGXStyle& SetUserAttribute(WORD nID, const CString& s);
	CGXStyle& SetUserAttribute(WORD nID, LPCTSTR pszValue);
	CGXStyle& SetUserAttribute(WORD nID, DWORD value);
	CGXStyle& SetUserAttribute(WORD nID, LONG value);
	CGXStyle& SetUserAttribute(WORD nID, double value);
	CGXStyle& SetUserAttribute(WORD nID, GXBYTE8 value);

	CGXStyle& SetUserAttributes(const CGXUserAttributeMap* p);
	const CGXUserAttributeMap* GetUserAttributeMap() const;

protected:
	CGXPen* GetBorders() const;

	CGXStyle& SetBorders(const CGXPen* pPenArray);

public:
	// constants
	static const int nBorders;

	// profile entries
	static LPCTSTR szHorizontalAlignment;
	static LPCTSTR szVerticalAlignment;
	static LPCTSTR szReadOnly;
	static LPCTSTR szControl;
	static LPCTSTR szInterior;
	static LPCTSTR szTextColor;
	static LPCTSTR szWrapText;
	static LPCTSTR szAllowEnter;
	static LPCTSTR szFont;
	static LPCTSTR szBorders;
	static LPCTSTR szBorder[4];
	static LPCTSTR szValue;
	static LPCTSTR szMaxLength;
	static LPCTSTR szVertScroll;
	static LPCTSTR szBaseStyle;
	static LPCTSTR szChoiceList;
	static LPCTSTR szEnabled;
	static LPCTSTR szTriState;
	static LPCTSTR szDraw3dFrame;
	static LPCTSTR szAutoSize;
	static LPCTSTR szFloatCell;
	static LPCTSTR szFloodCell;
	static LPCTSTR szMergeCell;
	static LPCTSTR szFormat;
	static LPCTSTR szPlaces;

// Implementation
	DWORD GetStyleBits() const;

	friend class CGXStyleCompareSubsetImp;
	friend class CGXStyleSerializeImp;
	friend class CGXGridProfileImp;
	friend class CGXSerializeOG5CompatibleImp;
	friend class CGXStyleFTR;
};

// for portability
#define AddUserAttribut AddUserAttribute

typedef const CGXStyle* LPCSTYLE;

class CGXStylesMap: public CObject
{
	DECLARE_SERIAL(CGXStylesMap)

public:
	// operations
	CGXStylesMap(CRuntimeClass* pStyleClass = NULL);
	CGXStylesMap(const CGXStylesMap& p);
	void CreateStandardStyles();

	const CGXStylesMap& operator=(const CGXStylesMap& p);

	void Serialize(CArchive& ar);

	// Profile
	virtual void WriteProfile() const;
	virtual BOOL ReadProfile();

	void SetSection(LPCTSTR pszSection);
	const CString& GetSection() const;

	// Base Style
		// Register a new style (or change an already registered style)
	WORD RegisterStyle(LPCTSTR pszName, const CGXStyle& style, BOOL bSystemStyle = FALSE);
	WORD RegisterStyle(UINT nResourceId, const CGXStyle& style, BOOL bSystemStyle = FALSE);

		// Return the id for the style
	WORD GetBaseStyleId(LPCTSTR pszName) const;
	WORD GetBaseStyleId(UINT nResourceID) const;

		// Return the name for the style
	LPCTSTR GetStyleName(WORD wStyleId) const;
	LPCTSTR GetStyleName(WORD wStyleId, UINT& nResourceId) const;

		// Some Operations with the styles
	BOOL IsSystemStyle(WORD wStyleId) const;
	BOOL LookupStyle(WORD wStyleId, CGXStyle*& style) const;
	void RemoveStyle(WORD wStyleId);

	// Support for User attributes
	void AddUserAttribute(WORD nID, const CGXStyle& style);
	void AddUserAttribute(WORD nID, const CGXStyle* pStyle = NULL);

	// Default user attribute and control which shall be shown
	// in CGXStyleSheet Controls and User Attribute page
	void RegisterDefaultControls();
	void RegisterDefaultUserAttributes();

	CGXGridCore* Grid() const;

public:
	// constants
	// default style names
	static LPCTSTR szDefaultSection;

	WORD m_wStyleStandard,
		 m_wStyleColHeader,
		 m_wStyleRowHeader;

	CRuntimeClass* m_pStyleClass;

// Implementation
public:
	virtual ~CGXStylesMap();

#ifdef _DEBUG
	void AssertValid() const;
	void Dump(CDumpContext& dc) const;
#endif

		// Implementation - Iterate through the styles
	POSITION StartStylesIteration() const;
	void GetNextStyle(POSITION& pos, WORD& wStyleId, CString& sName, UINT& nResourceID, const CGXStyle*& pStyle) const;

		// Implementation - Controls
	void AddControl(WORD nID);
	const CMapWordToPtr& GetControlNameMap() const;

		// Implementation - User attributes
	const CMapWordToPtr& GetUserAttrInfoMap() const;

public:
	// Implementation - structures
	struct UserAttrInfo
	{
		UserAttrInfo();
		UserAttrInfo(const UserAttrInfo& srcInfo);
		~UserAttrInfo();

		WORD nID;
		CString sName;
		CGXStyle* pStyle;
	};

	struct BaseStyleInfo
	{
		BaseStyleInfo();
		BaseStyleInfo(const BaseStyleInfo& srcInfo);
		~BaseStyleInfo();

		WORD nID;
		UINT nResourceID;// used for system-styles, otherwise 0
		CString sName;
		CGXStyle* pStyle;
		BOOL bSystem;
	};

protected:
	// Implementation - CleanUp
	void Free();
	void FreeStylesMap();
	void FreeControlMap();

protected:
	// Implementation - Attributes
	void StoreStyle(WORD wStyleId, const CGXStyle& style, LPCTSTR szName, UINT nResourceId, BOOL bSystem);

	// base styles
	CMapWordToPtr m_mwpIdInfo;
	CMapWordToPtr m_mwpIdStyle;
	CMapPtrToWord m_mpwResourceId;
	CMapStringToPtr m_mswNameId;

	WORD m_nLastId;
	WORD GetNewId();

	// control names
	CMapWordToPtr m_ControlNameMap;

	// user attributes
	CMapWordToPtr m_UserAttrInfoMap;

	// section name
	CString m_sSection;

	friend class CGXGridDocSerializeImp;
	friend class CGXGridProfileImp;
	friend class CGXGridParamCopyOperatorImp;
	friend class CGXStylesMapFTR;
};


// type-safe CPtrArray for CGXStyle objects

class CGXStylePtrArray: public CPtrArray
{
	DECLARE_DYNAMIC(CGXStylePtrArray)

public:
	// Construcion/Destruction
	CGXStylePtrArray();
	CGXStylePtrArray(const CGXStylePtrArray& other);
	virtual ~CGXStylePtrArray();
		// destructor automatically deletes all referenced objects

	const CGXStylePtrArray& operator=(const CGXStylePtrArray& other);

	void DeleteAll(); // delete all referenced objects
	void DeleteAt(int nIndex, int nCount = 1);
	void Move(int nIndex, int nCount, int nDest);

	virtual void Serialize(CArchive& ar);

public:
	// Accessing elements
	CGXStyle* GetAt(int nIndex) const;
	void SetAt(int nIndex, CGXStyle* newElement);

	// Potentially growing the array
	void SetAtGrow(int nIndex, CGXStyle* newElement);
	int Add(CGXStyle* newElement);

	// overloaded operator helpers
	CGXStyle* operator[](int nIndex) const;
	CGXStyle*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CGXStyle* newElement, int nCount = 1);
	void InsertAt(int nStartIndex, CGXStylePtrArray* pNewArray);

	friend class CGXGridDocSerializeImp;
};

// type-safe CPtrArray for array with CGXStylePtrArray objects

class CGXStylePtrArrayPtrArray: public CPtrArray
{
	DECLARE_DYNAMIC(CGXStylePtrArrayPtrArray)

public:
	// Construcion/Destruction
	CGXStylePtrArrayPtrArray();
	CGXStylePtrArrayPtrArray(const CGXStylePtrArrayPtrArray& other);
	virtual ~CGXStylePtrArrayPtrArray();
		// destructor automatically deletes all referenced objects

	const CGXStylePtrArrayPtrArray& operator=(const CGXStylePtrArrayPtrArray& other);

	void DeleteAll(); // delete all referenced objects
	void DeleteAt(int nIndex, int nCount = 1);
	void Move(int nIndex, int nCount, int nDest);

	virtual void Serialize(CArchive& ar);

public:
	// Accessing elements
	CGXStylePtrArray* GetAt(int nIndex) const;
	void SetAt(int nIndex, CGXStylePtrArray* newElement);

	// Potentially growing the array
	void SetAtGrow(int nIndex, CGXStylePtrArray* newElement);
	int Add(CGXStylePtrArray* newElement);

	// overloaded operator helpers
	CGXStylePtrArray* operator[](int nIndex) const;
	CGXStylePtrArray*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CGXStylePtrArray* newElement, int nCount = 1);
	void InsertAt(int nStartIndex, CGXStylePtrArrayPtrArray* pNewArray);

	friend class CGXGridDocSerializeImp;
};

/* [VC7] VC7 Libraries already defines these operators, so
calls are ambigous*/
#if (_MFC_VER < 0x0700)
CArchive& AFXAPI operator <<(CArchive& ar, const GXBYTE8& b);
CArchive& AFXAPI operator >>(CArchive& ar, GXBYTE8& b);
#endif

// Data

class CGXGridParam;

class CGXData: public CObject
{
	DECLARE_SERIAL(CGXData)

public:
	// operations
	CGXData();
	virtual ~CGXData();
	virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);

	virtual const CGXData& operator=(const CGXData& p);
	virtual void InitParam(CGXGridParam* pParam);

	static void AFXAPI ImplementSortMoveData();
	static void AFXAPI ImplementCopyMoveCells();

	friend class CGXGridSortMoveDataImp;
	friend class CGXDataCopyMoveCellsImp;
	friend class CGXDataFTR;

protected:
	// attributes
	ROWCOL	m_nRows, // row count
			m_nCols; // column count

	CGXStylePtrArray m_apRowBaseStyle;// row base styles
	CGXStylePtrArray m_apColBaseStyle;// column base styles

	CGXStylePtrArrayPtrArray m_apapCellStyle; // spans the cell matrix,
												// CGXStylePtrArray elements are rows
												// which CGXStyle elements are styles

	CGXStyle m_tmpValueStyle;
	CGXStyle m_tmpValueGetStyle;

	CGXAppData* m_pAppData;

// Access member functions
public:
	// Number of Rows and Colums
	virtual ROWCOL GetRowCount();
	virtual ROWCOL GetColCount();
	virtual BOOL StoreRowCount(ROWCOL wRows);
	virtual BOOL StoreColCount(ROWCOL wCols);

// Operations
public:
	// Inserting Colums or Rows
	virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount);
	virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount);

	// Removing Colums or Rows
	virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow);
	virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol);

	// Moving Colums or Rows
	virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);

	// copy/move ranges in one step
	virtual BOOL StoreCopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol);
	virtual BOOL StoreMoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndoInfo, int ctCmd);

	// Cell data
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType = 0);
	BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, GXModifyType mt, int nType = 0);
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType = 0);

	// Sorting (rearraging) rows and columns
	virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& anRowIndex);
	virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& anColIndex);

	// Update
	virtual BOOL GetUpdateFlag(ROWCOL nRow, ROWCOL nCol);
	virtual void SetUpdateFlag(ROWCOL nRow, ROWCOL nCol, BOOL bToggle);
		// set update flag (TRUE if cell shall be updated next time CGXGridCore::RefreshView is called)
	virtual void AddRecalcRange(const CGXRange& range);
	virtual void Recalc(BOOL bForceRecalc = FALSE);
	virtual void ResetError();
	virtual BOOL GetError(CString& strError);

	virtual CObject* GetAdvancedUndoInfo();
	virtual BOOL UndoAdvanced(CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells);
	virtual BOOL SetAdvancedUndo(BOOL b);

	virtual BOOL SetRangeName(LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo = NULL);
	virtual BOOL GetRangeName(LPCTSTR name, CGXRange& rg);
	virtual BOOL DeleteRangeName(LPCTSTR name, CObject*& pUndoInfo, BOOL bCreateUndoInfo);

	CGXGridCore* Grid() const;

	// Optimized for value only
	BOOL StoreValueRowCol(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszValue, GXModifyType mt, int nType = 0, CGXStyle* pValueStyle = NULL);
	LPCTSTR GetValueRowCol(ROWCOL nRow, ROWCOL nCol, int nType = 0, CGXStyle* pValueStyle = NULL);

	friend class CGXGridDocSerializeImp;
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "grid\gxstyles.inl"
#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//


#endif // _GXSTYLES_H_
