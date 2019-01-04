#pragma once
#include "afxwin.h"

#include <ifastgui/SiteConfig.h>

// CSupportPage dialog

class CSupportPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSupportPage)

private:
   bool bChanged_;
public:
   void setChanged( bool b ) { SetModified( (BOOL)b ); bChanged_ = b; }
   bool isChanged() const { return bChanged_; }

public:
	CSupportPage();
	virtual ~CSupportPage();

// Dialog Data
	enum { IDD = IDD_SUPPORTPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedSpLogEnable();
   CButton ctlLogEnable_;
   int vLogEnable_;
   CComboBox ctlLogLevel_;
   int vLogLevel_;
   CEdit ctlLogPath_;
   CString vLogPath_;
   CEdit ctlLogFile_;
   CString vLogFile_;

   afx_msg void OnBnClickedSpViewlogEnable();
   CButton ctlViewLogEnable_;
   int vViewLogEnable_;
   CEdit ctlViewLogPath_;
   CString vViewLogPath_;
   CButton ctlViewLogAppend_;
   BOOL vViewLogAppend_;
   CButton ctlViewLogComplete_;
   BOOL vViewLogComplete_;
   CButton ctlViewLogRawRequest_;
   BOOL vViewLogRawRequest_;
   CButton ctlViewLogRawResponse_;
   BOOL vViewLogRawResponse_;

   BOOL vViewTimeEnable_;
   afx_msg void OnBnClickedSpViewtimeEnable();
   CButton ctlViewTimeEnable_;
   CString vViewTimePath_;
   CString vViewTimeSize_;
   CEdit ctlViewTimePath_;
   CEdit ctlViewTimeSize_;

   BOOL vDisplayConnectionIcon_;
public:
   virtual BOOL OnInitDialog();
   void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
   void UpdateFromDoc(LPARAM lHint = 0);
   site::SiteConfig* getSiteConfig(void);
   BOOL SaveToDoc(void);
   afx_msg void OnEnChangeSpLogPath();
   afx_msg void OnCbnSelchangeSpLogLevel();
   afx_msg void OnEnChangeSpLogFile();
   afx_msg void OnEnChangeSpViewlogPath();
   afx_msg void OnBnClickedSpViewlogAppend();
   afx_msg void OnBnClickedSpViewlogComplete();
   afx_msg void OnBnClickedSpViewlogRawreq();
   afx_msg void OnBnClickedSpViewlogRawresp();
   afx_msg void OnEnChangeSpViewtimePath();
   afx_msg void OnEnChangeSpViewtimeSize();
   afx_msg void OnBnClickedSpDisplayconnectionicon();
   afx_msg void OnEnKillfocusSpViewtimeSize();
   BOOL vShowClientNamePane_;
   BOOL vDisplayConditionName_;
   afx_msg void OnBnClickedSpShowClientNamePane();
   afx_msg void OnBnClickedSpDisplayConditionName();
   afx_msg void OnEnChangeSpViewbatch();
   CString vViewBatch_;
   afx_msg void OnBnClickedSpExceptionReportEnable();
   int vExceptionReportEnable_;
   CString vExceptionReportPath_;
   afx_msg void OnEnChangeSpExceptionReportPath();
   CEdit ctlExceptionReportPath_;
   CButton ctlExceptionReportEnable_;
};
