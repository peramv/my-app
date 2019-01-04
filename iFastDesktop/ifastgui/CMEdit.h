#include <imm.h>

/////////////////////////////////////////////////////////////////////////////
// CTelEdit window

class CMEdit : public CEdit
{
// Construction
public:
   CMEdit();

// Attributes
public:

// Operations
   public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CMEdit)
   //}}AFX_VIRTUAL

// Implementation
   public:
   void SetMaxCharPerLine(long n);
   void SetMaxLine(long n);
   virtual ~CMEdit();

   // Generated message map functions
protected:
   //{{AFX_MSG(CMEdit)
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
   private:
   long MaxCharPerLine;
   long MaxLine;
   HIMC current;
   BOOL OpenStatus;
};
