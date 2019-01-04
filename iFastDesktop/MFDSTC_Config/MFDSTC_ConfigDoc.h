// MFDSTC_ConfigDoc.h : interface of the CMFDSTC_ConfigDoc class
//
#pragma once

#include <ifastgui/SiteConfig.h>

class CMFDSTC_ConfigDoc : public CDocument
{
protected: // create from serialization only
	CMFDSTC_ConfigDoc();
	DECLARE_DYNCREATE(CMFDSTC_ConfigDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMFDSTC_ConfigDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace = TRUE);

public:
   site::SiteConfig* pSiteConfig_;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
   static CMFDSTC_ConfigDoc* getDoc(void);
   virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
   afx_msg void OnFileSave();
   afx_msg void OnFileSaveAs();
   afx_msg void OnLoadRegistry(UINT nID);

private:
   void initFromRegistry( const DString& dstrHive );
};


