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
//
// ^FILE   : RoadEncorr.h
// ^AUTHOR : Darrin Donahue
// ^DATE   : 8-97
//
// ^CLASS    : RoadEncorr
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : This is the code for Encorr stuff
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
// RoadEncorr command target

#include <bfdata\bfdata.hpp>

namespace AwdTags
{
   extern const I_CHAR *CRDA;
   extern const I_CHAR *RECO;
   extern const I_CHAR *CRNO;
   extern const I_CHAR *UNIT;
}

class RoadEncorr : public CCmdTarget
{
   DECLARE_DYNCREATE(RoadEncorr)

   RoadEncorr();             // protected constructor used by dynamic creation

// Attributes
public:
   void setData( BFData * );  // Sets our data so we can pass it to EnCorr
   void setAwdData( const BFData *pData ); // Sets awd data to pass to EnCorr
   void end();
   void setProcessing( BOOL processing = TRUE )
   {
      m_processing = processing;
   }
   BOOL isProcessing()
   {
      return(m_processing);
   }

// Operations
public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RoadEncorr)
   public:
   virtual void OnFinalRelease();
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual ~RoadEncorr();

   // Generated message map functions
   //{{AFX_MSG(RoadEncorr)
   // NOTE - the ClassWizard will add and remove member functions here.
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
   // Generated OLE dispatch map functions
   //{{AFX_DISPATCH(RoadEncorr)
   afx_msg BSTR CreateTime();
   afx_msg BSTR RecordCode();
   afx_msg BSTR CreateNode();
   afx_msg BSTR DataIDI();
   afx_msg BSTR BusinessArea();
   afx_msg void Update( LPCTSTR );
   afx_msg void Complete( LPCTSTR );
   afx_msg void Pass( LPCTSTR );
   afx_msg void Fail( LPCTSTR );
   afx_msg void Save();
   afx_msg void Abort();
   afx_msg void Cancel();
   //}}AFX_DISPATCH
   DECLARE_DISPATCH_MAP()
   DECLARE_INTERFACE_MAP()

   private:
   void updateAwd( LPCTSTR szIdi, bool completed );

private:
   CString m_csIDI;         // The whiteboard
   BOOL m_processing;
   CString m_businessArea;
   CString m_createDateTime;
   CString m_recordCode;
   CString m_createNode;
   DString m_completedStatus;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RoadEncorr.h-arc  $
 * 
 *    Rev 1.4   Nov 14 2004 15:00:48   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.3   Oct 09 2002 23:56:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   22 May 2002 19:16:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.1   Feb 15 2000 18:59:44   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:24   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:52   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
