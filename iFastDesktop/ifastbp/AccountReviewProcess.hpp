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


#include <bfproc\abstractprocess.hpp>

// Forward references
class MFAccount;
class AccountReviewList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Account Review process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE AccountReviewProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AccountReviewProcess();
   AccountReviewProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AccountReviewProcess();

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

   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD,  const BFDataGroupId& idDataGroup   );
   virtual E_COMMANDRETURN doProcess();
   void *getPtrForContainer(
                           const BFContainerId& idContainer,
                           const BFDataGroupId& idDataGroup
                           );

private:

   GenericInterface *m_rpChildGI;
   DString m_dstrAccountNumber;
   DString m_dstrShrNum;

   AccountReviewList *m_pAccountReviewList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountReviewProcess.hpp-arc  $
//
//   Rev 1.6   Mar 21 2003 17:34:38   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:52:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:51:32   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   Jun 03 2002 16:55:10   HSUCHIN
//bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
//
//   Rev 1.2   31 May 2002 13:45:50   HERNANDO
//Revised for Rel47.
//
//   Rev 1.1   22 May 2002 18:21:54   PURDYECH
//BFData Implementation
//
//   Rev 1.0   08 May 2002 18:10:56   HERNANDO
//Initial revision.
 * 
 */
