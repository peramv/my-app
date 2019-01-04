//////////////////////////////////////////////////////////////////////////////
#if !defined __SFLRIBBONFONTCOMBOBOXEX__H__
#define __SFLRIBBONFONTCOMBOBOXEX__H__

#include "StingrayExportDefs.h"
#include "afxribboncombobox.h"

namespace sflex
{

// SFLRibbonFontComboBoxEx

class SFLRibbonFontComboBoxEx : public CMFCRibbonFontComboBox
{
	FOUNDATIONEX_DECLARE_DYNCREATE(SFLRibbonFontComboBoxEx)

public:
	FOUNDATIONEX_API SFLRibbonFontComboBoxEx(UINT nID, int nFontType = DEVICE_FONTTYPE | RASTER_FONTTYPE | TRUETYPE_FONTTYPE,
		BYTE nCharSet = DEFAULT_CHARSET, BYTE nPitchAndFamily = DEFAULT_PITCH, int nWidth = -1);
	FOUNDATIONEX_API virtual ~SFLRibbonFontComboBoxEx();


#if _MSC_VER <= 1500 // VS 2008 - 
public:
	// Returns which font types to display in the combo box. Valid options are DEVICE_FONTTYPE, RASTER_FONTTYPE, and TRUETYPE_FONTTYPE, or any bitwise combination thereof.
	int GetFontType() const { return m_nFontType; }

	// Returns the specified character set.
	BYTE GetCharSet() const { return m_nCharSet; }

	// Returns the pitch and the family of the fonts that are displayed in the combo box.
	BYTE GetPitchAndFamily() const { return m_nPitchAndFamily; }
#endif // VS 2008 -
};

} // namespace sflex

#endif // __SFLRIBBONFONTCOMBOBOXEX__H__
