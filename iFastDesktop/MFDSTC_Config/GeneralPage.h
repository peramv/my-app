#pragma once
#include "afxwin.h"
#include <ifastgui/SiteConfig.h>

// CGeneralPage dialog

class CGeneralPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CGeneralPage)
private:
public:
	CGeneralPage();
	virtual ~CGeneralPage();

// Dialog Data
	enum { IDD = IDD_GENERALPAGE };

private:
   bool bChanged_;
public:
   void setChanged( bool b ) { SetModified( (BOOL)b ); bChanged_ = b; }
   bool isChanged() const { return bChanged_; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnCbnSelchangeMarket();
   CComboBox ctlMarket_;
   CEdit ctlAwdInterfaceDll_;
   CString vMarket_;
   CString vAwdInterfaceDll_;
   BOOL vAwdAutoLogon_;
   CString vPath_;
   CString vFYIFile_;
   CString vRepository_;
   virtual BOOL OnInitDialog();
   void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
   afx_msg void OnEnChangeXmlDescription();
   CString vDescription_;
public:
   void UpdateFromDoc(LPARAM lHint = 0);
   site::SiteConfig* getSiteConfig(void);
   afx_msg void OnEnChangeAwdInterfaceDll();
   afx_msg void OnBnClickedAwdAutologon();
   afx_msg void OnEnChangeDatapathPath();
   afx_msg void OnEnChangeDatapathFyi();
   afx_msg void OnEnChangeDatapathRepository();
   BOOL SaveToDoc(void);
   afx_msg void OnEnKillfocusDatapathPath();
   CEdit ctlPath_;
   CEdit ctlFYIFile_;
   CEdit ctlRepository_;
   BOOL ValidateData(void);
   afx_msg void OnEnChangeLastChangedBy();
   CString vLastChangedUser_;
   CString vLastChangedDate_;
   afx_msg void OnEnChangeCsiHost();
   CString vCSIHost_;
   CString vCSIParam_;
   CString vCSIType_;
   afx_msg void OnEnChangeCsiParam();
   afx_msg void OnEnChangeCsiType();
};
