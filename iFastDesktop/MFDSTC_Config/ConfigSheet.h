#pragma once

#include "GeneralPage.h"
#include "SonicPage.h"
#include "SupportPage.h"
#include "SpecialPage.h"

// CConfigSheet

class CConfigSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CConfigSheet)

public:
	CConfigSheet(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CConfigSheet();

protected:
	DECLARE_MESSAGE_MAP()

   CGeneralPage GeneralPage_;
   CSonicPage SonicPage_;
   CSupportPage SupportPage_;
   CSpecialPage SpecialPage_;

public:
   void OnUpdate(CView* pView, LPARAM lHint, CObject* pHint);
   bool isUpdated(void);
   BOOL SaveToDoc(void);
protected:
   virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
};


