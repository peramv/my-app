#pragma once
#include "afxwin.h"

#include <ifastgui/SiteConfig.h>

// CSpecialPage dialog

class CSpecialPage : public CPropertyPage
{
   DECLARE_DYNAMIC(CSpecialPage)

private:
   bool bChanged_;
public:
   void setChanged( bool b ) { SetModified( (BOOL)b ); bChanged_ = b; }
   bool isChanged() const { return bChanged_; }

public:
   CSpecialPage();
   virtual ~CSpecialPage();

// Dialog Data
   enum { IDD = IDD_SPECIALPAGE };

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   DECLARE_MESSAGE_MAP()
public:
public:
   virtual BOOL OnInitDialog();
   void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
   void UpdateFromDoc(LPARAM lHint = 0);
   site::SiteConfig* getSiteConfig(void);
   BOOL SaveToDoc(void);
   afx_msg void OnBnClickedSpecMmf();
   CButton ctlMMFPassword_;
   BOOL vMMFPassword_;
};

