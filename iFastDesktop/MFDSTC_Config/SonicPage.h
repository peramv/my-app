#pragma once

#include <ifastgui/SiteConfig.h>
#include "BaseConfigPage.h"
#include "afxwin.h"
#include "afxcmn.h"
// CSonicPage dialog

class CSonicPage : public CPropertyPage, BaseConfigPage
{
	DECLARE_DYNAMIC(CSonicPage)

public:
	CSonicPage();
	virtual ~CSonicPage();

// Dialog Data
	enum { IDD = IDD_SONICPAGE };

private:
   bool isLocal() const;
   bool bChanged_;
public:
   void setChanged( bool b ) { SetModified( (BOOL)b ); bChanged_ = b; }
   bool isChanged() const { return bChanged_; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
   void setBackupHostList(const CString& str);
   CString makeBrokerURL();
public:
   afx_msg void OnCbnSelchangeTlUseSonic();
   CString vUseSonic_;
   CString vRecycleInterval_;
   CString vRTSHost_;
   CString vRTSPort_;
   CString vPrimaryProtocol_;
   CString vPrimaryHost_;
   CString vPrimaryPort_;
   CString vBackupProtocol_;
   CString vBackupHost_;
   CString vBackupPort_;
   CString vSingleQ_;
   CString vMultiQ_;
   CString vAuthQ_;
   CString vAwdQ_;
   CString vUserNS_;
   CString vSMQUser_;
   CString vSMQPassword_;
   CString vSMQTimeout_;
   BOOL vPersistentConnections_;
   CComboBox ctlPrimaryHost_;
   CComboBox ctlBackupHost_;
   CComboBox ctlSingleQ_;
   CComboBox ctlMultiQ_;
   CComboBox ctlAuthQ_;
   CComboBox ctlAwdQ_;
   CComboBox ctlUserNS_;
   BOOL vUseSingleConnection_;
public:
   void UpdateFromDoc(LPARAM lHint = 0);
   void OnUpdate(CView* pView, LPARAM lHint, CObject* pHint);
   virtual BOOL OnInitDialog();
   site::SiteConfig* getSiteConfig(void);
   CSpinButtonCtrl ctlRecycleSpin_;
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   BOOL SaveToDoc(void);
   afx_msg void OnBnClickedCheck2();
   afx_msg void OnEnChangeTlRecycleInterval();
   afx_msg void OnEnChangeTlRtsHost();
   afx_msg void OnEnChangeTlRtsPort();
   afx_msg void OnCbnSelchangeTlZtsPrimaryProtocol();
   afx_msg void OnCbnSelchangeTlZtsPrimaryHost();
   afx_msg void OnEnChangeTlZtsPrimaryPort();
   afx_msg void OnCbnSelchangeTlZtsBackupProtocol();
   afx_msg void OnCbnSelchangeTlZtsBackupHost();
   afx_msg void OnEnChangeTlZtsBackupPort2();
   afx_msg void OnCbnSelchangeTlSingleq();
   afx_msg void OnCbnSelchangeTlMultiq();
   afx_msg void OnCbnSelchangeTlAuthq();
   afx_msg void OnCbnSelchangeTlAwdq();
   afx_msg void OnCbnSelchangeTlUserns();
   afx_msg void OnEnChangeTlSmquser();
   afx_msg void OnEnChangeTlSmqpassword();
   afx_msg void OnEnChangeTlWaitTimeout();
   afx_msg void OnCbnEditchangeTlSingleq();
   afx_msg void OnCbnEditchangeTlMultiq();
   afx_msg void OnCbnEditchangeTlAuthq();
   afx_msg void OnCbnEditchangeTlAwdq();
   afx_msg void OnCbnEditchangeTlZtsPrimaryHost();
   afx_msg void OnCbnEditchangeTlZtsBackupHost();
   CSpinButtonCtrl ctlWaitTimeoutSpin_;
   afx_msg void OnEnKillfocusTlZtsPrimaryPort();
   afx_msg void OnEnKillfocusTlZtsBackupPort2();
   afx_msg void OnEnKillfocusTlRecycleInterval();
   afx_msg void OnEnKillfocusTlWaitTimeout();
   afx_msg void OnEnKillfocusTlRtsPort();
   CEdit ctlPrimaryPort_;
   CEdit ctlBackupPort_;
   CEdit ctlTimeout_;
   CEdit ctlRecycleInterval_;
   CEdit ctlRTSPort_;
   BOOL ValidateData(void);
   afx_msg void OnCbnKillfocusTlZtsPrimaryHost();
   afx_msg void OnBnClickedSonicTest();
   afx_msg void OnBnClickedRTSTest();
   CComboBox ctlUseSonic_;
   CButton ctlSonicTest_;
   CButton ctlRTSTest_;
private:
   void setQueueNames(void);
   void clearQueueLists(void);
   void addQueueList(CString strPrefix);
public:
   afx_msg void OnEnSetfocusTlZtsBackupPort2();
   CComboBox ctlPrimaryProtocol_;
   CComboBox ctlBackupProtocol_;
   afx_msg void OnCbnSetfocusTlZtsBackupProtocol();
   afx_msg void OnCbnSetfocusTlZtsBackupHost();
};
