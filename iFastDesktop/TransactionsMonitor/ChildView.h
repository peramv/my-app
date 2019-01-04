
// ChildView.h : interface of the CChildView class
//


#pragma once


#include <ifdscore\condition.hpp>




// Forward declares
class DSTCUserSession;
class DSTCWorkSession;



// CChildView window

class CChildView : public CWnd	
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	void Initialize();

	// Generated message map functions
protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

	void InitInputParameters();

private:
	SEVERITY Logon();
	SEVERITY Logoff();
   SEVERITY CallView(const DString& mgmtCoName);
   SEVERITY CallSmartView();
private:
	DString _strUserName;
	DString _strPassword;
	DString _strClient;

   DSTCUserSession* _dstcUserSession;
   DSTCWorkSession* _dstcWorkSession;
   int errCode;
};

