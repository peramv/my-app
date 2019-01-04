#pragma once


//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <uibase\BaseControl.hpp>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTStatic : public CStatic, public BaseControl
{
// Construction
public:
   DSTStatic(
            BaseDlg *rpParent,
            UINT controlID
            );

// Attributes
public:

// Operations
   public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTStatic)
   //}}AFX_VIRTUAL

// Implementation
   public:
   virtual ~DSTStatic();

   // Generated message map functions
protected:
   //{{AFX_MSG(DSTStatic)
   // NOTE - the ClassWizard will add and remove member functions here.
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   //}}AFX_MSG
   LRESULT OnMouseLeave(WPARAM a=0, LPARAM b=0L);
   bool doSetCtrlReadOnly(bool bReadOnly);

   DECLARE_MESSAGE_MAP()

   virtual void DoGetText(
                         DString &strValueOut,
                         int index=0
                         ) const;
   /**
    * This method is called from BaseControl::Init to allow us to get new
    * properties.
    * This may be called more than once (to allow the same control to be tied
    * to different fields, depending on context).
    */
   virtual void DoInit();
   /**
    * This method is called from BaseControl::SetText and is expected to sets
    * the value of the control to the specified value.
    * 
    * @returns flag with true = success, false = failure, check conditions
    * @param strValueIn value to set.
    * @param index      not used by this class
    * 
    * @return 
    */
   virtual bool DoSetText(
                         const DString &strValueIn,
                         int index=0
                         );
   virtual void DoClear();
};

/////////////////////////////////////////////////////////////////////////////
