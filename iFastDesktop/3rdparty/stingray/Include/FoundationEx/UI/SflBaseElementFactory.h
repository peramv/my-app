#if !defined __SFLBASEELEMENTFACTORY__H__
#define __SFLBASEELEMENTFACTORY__H__

// Includes.
#include "StingrayExportDefs.h"
#include "afxbaseribbonelement.h"

namespace sflex
{

// Fowards.

class SFLBaseElementFactory
{
public:
	// Construction/Destruction
	FOUNDATIONEX_API SFLBaseElementFactory(void);
	FOUNDATIONEX_API virtual ~SFLBaseElementFactory(void);

public:
	// Create a new CMFCRibbonBaseElement.
	static CMFCRibbonBaseElement* Create(CString strClassName);
	// Clone a new CMFCRibbonBaseElement.
	static CMFCRibbonBaseElement* Clone(CMFCRibbonBaseElement* pSrcElement);
	// Syncronize the data between elements. 
	static void Syncronize(CMFCRibbonBaseElement* pSrcElement, CMFCRibbonBaseElement* pDestElement);
	// Get Special Value.
	static int GetSpecialInt(CMFCRibbonBaseElement* pSrcElement);
	// Set with Special Value.
	static void SetSpecialInt(CMFCRibbonBaseElement* pDestElement, int iValue);
	// Get Special Text.
	static CString GetSpecialText(CMFCRibbonBaseElement* pSrcElement);
	// Set with Special Text.
	static void SetSpecialText(CMFCRibbonBaseElement* pDestElement, CString strValue);

protected:
	template <class T>
	static void ImplCopy(CMFCRibbonBaseElement* pSrcElement, T* pDestElement);
};

template <class T>
void SFLBaseElementFactory::ImplCopy(CMFCRibbonBaseElement* pSrcElement, T* pDestElement)
{
	//pDestElement->SetACCData() // NO EQ
	pDestElement->SetCompactMode(((T*)pSrcElement)->IsCompactMode());
	pDestElement->SetData(((T*)pSrcElement)->GetData());
	pDestElement->SetDefaultCommand(((T*)pSrcElement)->IsDefaultCommand());
	pDestElement->SetDefaultMenuLook(((T*)pSrcElement)->IsDefaultMenuLook());
	pDestElement->SetDescription(((T*)pSrcElement)->GetDescription());
	pDestElement->SetID(((T*)pSrcElement)->GetID());
	pDestElement->SetImageIndex(((T*)pSrcElement)->GetImageIndex(FALSE), FALSE);
	pDestElement->SetImageIndex(((T*)pSrcElement)->GetImageIndex(TRUE), TRUE);
	//pDestElement->SetInitialMode() // NO EQ
	pDestElement->SetKeys(((T*)pSrcElement)->GetKeys(), ((T*)pSrcElement)->GetMenuKeys());
	if(((T*)pSrcElement)->GetMenu())
	{
		pDestElement->SetMenu(((T*)pSrcElement)->GetMenu(), ((T*)pSrcElement)->IsDefaultCommand(), ((T*)pSrcElement)->IsRightAlignMenu());
	}
	//pDestElement->SetOriginal() // NO ACCESS
	//pDestElement->SetParentCategory(((T*)pSrcElement)->GetParentCategory()); // N/A
	//pDestElement->SetParentMenu() // NO EQ
	//pDestElement->SetParentRibbonBar() // NO ACCESS
	pDestElement->SetRect(((T*)pSrcElement)->GetRect());
	pDestElement->SetRightAlignMenu(((T*)pSrcElement)->IsRightAlignMenu());
	pDestElement->SetText(((T*)pSrcElement)->GetText());
	pDestElement->SetTextAlwaysOnRight(((T*)pSrcElement)->IsTextAlwaysOnRight());
	//pDestElement->SetToolTipText(((T*)pSrcElement)->GetToolTipText()); // N/A
	pDestElement->SetVisible(((T*)pSrcElement)->IsVisible());
}



} // namespace sflex

#endif // __SFLBASEELEMENTFACTORY__H__
