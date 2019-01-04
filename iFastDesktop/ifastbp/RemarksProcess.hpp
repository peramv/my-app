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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class MFAccount;
class RemarksList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the remarks process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE RemarksProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   RemarksProcess();
   RemarksProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RemarksProcess();

   SEVERITY performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

protected:
   /**
     * Implementation for the refresh method.  Not implemented yet.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
      * Implementation to support the modelessChildComplete method.
      * modelessChildComplete is used by the GenericInterfaceContainer to tell
      * the parent that the modeless child has been destroyed.
      * @param cmd - A reference to a command representing the object that has
      * been destroyed.
      * @returns true if this modeless object should end as well, false if not
      * done yet.  When returning true, the calling modelessChildComplete method
      * will call GenericInterfaceContainer::modelessDestroySelf to delete and
      * remove this object from the container
      */
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   /**
      * Used to bring a modeless dialog (via parent process) to the top of the
      * window stack.
      * @param rpGICaller - A reference pointer to the calling object.
      * @returns true if successful, check conditions if false
      */
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   bool doOk( GenericInterface *rpGICaller );
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   void *getPtrForContainer(
                           const BFContainerId& idContainer,
                           const BFDataGroupId& idDataGroup
                           );
   virtual bool setCommitDataGroupAsHost()
   {
      return(false);
   }
   bool getNumberOfAccountsInRemarksList( )const;

   virtual SEVERITY doSetField(const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& idField,
                               const BFDataGroupId& idDataGroup,
                               const DString& strValue,
                               bool bFormatted);

   virtual void doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag);

private:
   GenericInterface *_rpChildGI;
   DString _strName;
   DString _strAccountNumber;
   DString _strShrNum;
   DString m_filterBy;

   RemarksList *_pRemarksList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RemarksProcess.hpp-arc  $
 * 
 *    Rev 1.12   Oct 03 2003 12:19:52   VADEANUM
 * PTS 10022545 - Record created when no Remark entered on the Remarks dialog - removed getKeyForNewListItem().
 * 
 *    Rev 1.11   Jul 30 2003 11:26:58   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.10   Mar 21 2003 17:46:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:53:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Aug 29 2002 12:53:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   Jun 03 2002 14:13:12   FENGYONG
 * override "setCommitDataGroupAsHost" for NASU API
 * 
 *    Rev 1.6   22 May 2002 18:20:12   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:18:10   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   Aug 02 2000 15:31:48   BUZILA
 * "locale" changes
 * 
 *    Rev 1.3   Jul 26 2000 17:55:00   HUDAVID
 * added performSearch and doMoreRecordsExist
 * 
 *    Rev 1.2   Mar 29 2000 13:06:20   DT24433
 * consistent naming of member variables
 * 
 *    Rev 1.1   Feb 15 2000 18:56:42   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:18   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Jan 26 2000 19:40:10   POPESCUS
 * fixes related to a crash
 * 
 *    Rev 1.7   Jan 19 2000 10:12:06   BUZILA
 * refresh stuf
 * 
 *    Rev 1.6   08 Jan 2000 14:54:52   HSUCHIN
 * modified so that effective date now defaults to next business date when new remarks is added.
 * 
 *    Rev 1.5   Dec 23 1999 14:40:52   BUZILA
 * made doOK protected
 * 
 *    Rev 1.4   Dec 10 1999 18:46:32   BUZILA
 * setting remarks flag in COANavig CBO
 * 
 *    Rev 1.3   Nov 10 1999 11:19:20   HSUCHIN
 * modified to update transactions and using the new basedlg and controls
 * 
 *    Rev 1.2   Nov 02 1999 18:40:06   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.1   Jul 08 1999 10:03:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
