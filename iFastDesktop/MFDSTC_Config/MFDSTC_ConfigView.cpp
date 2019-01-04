// MFDSTC_ConfigView.cpp : implementation of the CMFDSTC_ConfigView class
//

#include "stdafx.h"
#include "MFDSTC_Config.h"

#include "MFDSTC_ConfigDoc.h"
#include "MFDSTC_ConfigView.h"
#include ".\mfdstc_configview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "QuickRegistry.h"


// CMFDSTC_ConfigView

IMPLEMENT_DYNCREATE(CMFDSTC_ConfigView, CFormView)

BEGIN_MESSAGE_MAP(CMFDSTC_ConfigView, CFormView)
   ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
   ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
END_MESSAGE_MAP()

// CMFDSTC_ConfigView construction/destruction

CMFDSTC_ConfigView::CMFDSTC_ConfigView()
	: CFormView(CMFDSTC_ConfigView::IDD)
   , pConfigSheet_(NULL)
{
	// TODO: add construction code here

}

CMFDSTC_ConfigView::~CMFDSTC_ConfigView()
{
}

void CMFDSTC_ConfigView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMFDSTC_ConfigView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMFDSTC_ConfigView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
   // create and asociated the property sheet with the "place holder" window
	CWnd* pwndPropSheetHolder = GetDlgItem(IDC_PLACEHOLDER);
   if( NULL == pConfigSheet_ ) {
	   pConfigSheet_ = new CConfigSheet(pwndPropSheetHolder);
	   if (!pConfigSheet_->Create(pwndPropSheetHolder,
		   WS_CHILD | WS_VISIBLE, 0))
	   {
		   delete pConfigSheet_;
		   pConfigSheet_ = NULL;
		   return;
	   }

	   // fit the property sheet into the place holder window, and show it
	   CRect rectPropSheet;
	   pwndPropSheetHolder->GetWindowRect(rectPropSheet);
	   pConfigSheet_->SetWindowPos(NULL, 0, 0,
		   rectPropSheet.Width(), rectPropSheet.Height(),
		   SWP_NOZORDER | SWP_NOACTIVATE);
   }

}


// CMFDSTC_ConfigView diagnostics

#ifdef _DEBUG
void CMFDSTC_ConfigView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFDSTC_ConfigView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFDSTC_ConfigDoc* CMFDSTC_ConfigView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFDSTC_ConfigDoc)));
	return (CMFDSTC_ConfigDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFDSTC_ConfigView message handlers

void CMFDSTC_ConfigView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* pHint)
{
   if( NULL != pConfigSheet_ ) {
      if( NULL == pHint ) {
         pHint = (CObject*)(GetDocument()->pSiteConfig_);
      }
      pConfigSheet_->OnUpdate( NULL, lHint, pHint );
   }
   // TODO: Add your specialized code here and/or call the base class
}

bool CMFDSTC_ConfigView::isUpdated(void)
{
   if( NULL != pConfigSheet_ &&
       pConfigSheet_->isUpdated() ) {
      return true;
   }
   return false;
}

void CMFDSTC_ConfigView::OnFileSaveAs()
{
   if( NULL != pConfigSheet_ ) {
      pConfigSheet_->SaveToDoc();
   }
  
}

void CMFDSTC_ConfigView::OnUpdateLoadRegistry(CCmdUI *pCmdUI)
{
   pCmdUI->Enable(TRUE);
}


void CMFDSTC_ConfigView::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
   BOOL bEnable = FALSE;
   if( NULL != pConfigSheet_ &&
       pConfigSheet_->isUpdated() ) {
      bEnable = TRUE;
   }
   pCmdUI->Enable(bEnable);
}

void CMFDSTC_ConfigView::OnFileSave()
{
   if( NULL != pConfigSheet_ ) {
      pConfigSheet_->SaveToDoc();
   }
}

void CMFDSTC_ConfigView::OnUpdateFileSave(CCmdUI *pCmdUI)
{
   BOOL bEnable = FALSE;
   if( NULL != pConfigSheet_ &&
       pConfigSheet_->isUpdated() ) {
      bEnable = TRUE;
   }
   pCmdUI->Enable(bEnable);
}

