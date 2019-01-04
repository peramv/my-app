#pragma once
#include "afxwin.h"
#include "resource.h"
#include "MessageServiceTest.h"


// CSonicConnectionTest dialog

class CSonicConnectionTest : public CDialog
{
	DECLARE_DYNAMIC(CSonicConnectionTest)

private:
   MessageServiceTest& smqTest_;
public:
	CSonicConnectionTest(MessageServiceTest& smqTest, CWnd* pParent = NULL);   // standard constructor
	virtual ~CSonicConnectionTest();

   MessageServiceTest& getSMQTest() { return smqTest_; }

// Dialog Data
	enum { IDD = IDD_ABOUT_CONNECTION_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedPbTelnet();
   afx_msg void OnBnClickedPbConnect();
   afx_msg void OnBnClickedPbSingleq();
   afx_msg void OnBnClickedPbMultiq();
   afx_msg void OnBnClickedPbAuthq();
   afx_msg void OnBnClickedPbAwdq();
   afx_msg void OnBnClickedPbHeartbeat();
   afx_msg void OnStnClickedStPrimary();
   CStatic ctlStPrimary_;
   CStatic ctlStBackup_;
   CStatic ctlStConnect_;
   CStatic ctlStSingleQ_;
   CStatic ctlStMultiQ_;
   CStatic ctlStAuthQ_;
   CStatic ctlStAwdQ_;
   CStatic ctlStHeartbeat_;
   CButton ctlPbPrimary_;
   CButton ctlPbBackup_;
   CButton ctlPbConnect_;
   CButton ctlPbSingleQ_;
   CButton ctlPbMultiQ_;
   CButton ctlPbAuthQ_;
   CButton ctlPbAwdQ_;
   CButton ctlPbHeartbeat_;

   CStatic ctlStatusConnect_;
   CStatic ctlStatusTelnet_;
   CStatic ctlStatusSingleQ_;
   CStatic ctlStatusMultiQ_;
   CStatic ctlStatusAuthQ_;
   CStatic ctlStatusAwdQ_;

   CEdit ctlMessage_;
   virtual BOOL OnInitDialog();
};
