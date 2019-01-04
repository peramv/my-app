// DstcCsiTestDlg.h : header file
//

#if !defined(AFX_IFASTCSITESTDLG_H__CB03005A_137A_11D3_9FB5_00C04F5519AF__INCLUDED_)
#define AFX_IFASTCSITESTDLG_H__CB03005A_137A_11D3_9FB5_00C04F5519AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( disable : 4786 )
#pragma warning( disable : 4251 )
#pragma warning( disable : 4503 )

#include <string>
#include <map>
#include <list>

/////////////////////////////////////////////////////////////////////////////
// CDstcCsiTestDlg dialog

class CIFastCsiTestDlg : public CDialog
{
// Construction
public:
	CIFastCsiTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDstcCsiTestDlg)
	enum { IDD = IDD_IFASTCSITEST_DIALOG };
	CEdit	m_ParameterValue;
	CStatic	m_ParameterName;
	CListBox	m_ProcessList;
	CListCtrl	m_ParameterList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDstcCsiTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDstcCsiTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExecute();
	afx_msg void OnSelchangeProcessList();
	afx_msg void OnDblclkProcessList();
	afx_msg void OnItemchangedParameterList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeParameterValue();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

   void refreshProcessList();
   void refreshParameterList();
	void setSessionParameter();
//   typedef std::string ParameterList;
//   typedef std::map< std::string, ParameterList > ProcessMap;
   typedef std::list< std::string > ParameterList;
   typedef std::map< std::string, ParameterList > ProcessMap;
   typedef std::map< std::string, std::string > ParameterMap;

   ProcessMap processes;
   ParameterMap parameters;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSTCCSITESTDLG_H__CB03005A_137A_11D3_9FB5_00C04F5519AF__INCLUDED_)
