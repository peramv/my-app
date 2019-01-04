#ifndef VERIFYSEARCHDLG_H
#define VERIFYSEARCHDLG_H
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
// ^FILE   : VerifySearchDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : 03/10/99
//
// ^CLASS    : VerifySearchDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Verify Search / Multi Match screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class VerifySearchDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   VerifySearchDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   /**
    * Destructor
    */
   ~VerifySearchDlg ();

   /**
    * Dialog Data
    */
   //{{AFX_DATA(VerifySearchDlg)
   enum
   {
      IDD = IDD_VERIFYSEARCH
   };
   //}}AFX_DATA

   /** 
    * Overrides
    */
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(VerifySearchDlg)
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   /**
     * Method to filter out data in the list control
     * @returns true if the item will be shown and false otherwise
     */
   virtual bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL  );

protected:

   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();

   /**
     * The List controls are refreshed.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   /**
     * Method driven by base architecture to excute before doOk is called
     * @return true if successful, false otherwise
     */
   virtual bool PreOk();

   /**
    * Method to override data retrived for the control defined by the controlID 
    * passed in.
    * @param   UINT controlID - The custom control Id
    * @param   DString& strValueOut - The string to be display for the current control
    * @param   bool bFormatted - Flag determining the output to be formateed by
    *                            DataDictionary
    * @param   int index - index of field, if it has multiple fields for control
    * @returns true if override provided for the specified control, false otherwise
    */
   virtual bool GetDataForControl( UINT controlID, DString &strValueOut, 
                                   bool bFormatted, int index ) const;

   /**
    * Generated message map functions
    */
   //{{AFX_MSG(VerifySearchDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnMore();
   afx_msg void OnDblclkLvEntities(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnRadioAddress01();
   afx_msg void OnRadioAddress11();
   afx_msg void OnBtnWhereUsed();
   afx_msg void OnAccelEntity();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
     * This method initializes the Dialog by initilizing the controls
     * This method is invoked by the base architecture after OnInitDialog has 
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
   virtual void OnPostInitDialog();

   virtual bool filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag);

private:


   DString _fromScreen;
   HACCEL m_hAccel;
   std::set< DString > listKey;
   bool bIgnoreFiltering;
};

#endif // VerifySearchDlg_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/VerifySearchDlg.h-arc  $
 * 
 *    Rev 1.12   Apr 14 2005 11:07:12   popescu
 * Incident #262507, Multiple a/c with same alternate a/c
 * 
 *    Rev 1.11   Mar 09 2005 14:39:14   yingbaol
 * PET1171,FN01:EU saving, disable OK button if it is from All Entity screen.
 * 
 *    Rev 1.10   Mar 21 2003 18:42:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Jan 20 2003 10:44:16   KOVACSRO
 * back to 1.7
 * 
 *    Rev 1.7   Dec 19 2002 13:56:18   sanchez
 * New public method filterListColumn().  If the ifds::CompCodeFlag is "YES", show columns  ifds::AcctGroup and ifds::CompanyCode, otherwise hide them.  If the ifds:Viscount is "YES"  show the ifds::Viscount column, otherwise hide it.
 * 
 *    Rev 1.6   Oct 09 2002 23:56:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Sep 06 2001 14:11:42   ZHANGCEL
 * Added second parameter in ListViewControlFilter()
 * 
 *    Rev 1.4   20 Aug 2001 16:51:22   HSUCHIN
 * added comments and fix Market problem
 * 
 *    Rev 1.3   20 Aug 2001 15:08:56   HSUCHIN
 * beautify source
 * 
 *    Rev 1.2   Apr 10 2001 16:02:42   YINGZ
 * fix multiple entity problem
 * 
 *    Rev 1.1   Feb 15 2000 18:59:52   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:28   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Jan 14 2000 09:10:22   POPESCUS
 * updated VerifySearch to the new control model
 * 
 *    Rev 1.6   Nov 14 1999 12:57:04   VASILEAD
 * fixed dbl clck issue
 * 
 *    Rev 1.5   Nov 09 1999 16:53:42   VASILEAD
 * Changed to AccountEntityXref
 * 
 *    Rev 1.4   Oct 04 1999 16:31:24   HSUCHIN
 * Added Alt-L Acceleartor to put focus on search results.
 * 
 *    Rev 1.3   Sep 24 1999 17:25:36   HSUCHIN
 * minor bug fix
 * 
 *    Rev 1.2   Sep 16 1999 14:53:58   HSUCHIN
 * Added code for C1, added SIN to ID Types and changed Column Headings.  New fcn to get Market
 * 
 *    Rev 1.1   Jul 08 1999 10:06:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
