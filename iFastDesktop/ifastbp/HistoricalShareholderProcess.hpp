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

class HistoricalShareholderList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE HistoricalShareholderProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   HistoricalShareholderProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~HistoricalShareholderProcess();

protected:
   /**
      * Used to bring a modeless dialog (via parent process) to the top of the
      * window stack.
      * @param rpGICaller - A reference pointer to the calling object.
      * @returns true if successful, check conditions if false
      */
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
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
   void doGetField(
                  const GenericInterface *rpGICaller,
                  const BFContainerId& idContainer,
                  const BFFieldId& idField,
                  const BFDataGroupId& idDataGroup,
                  DString &strValueOut,
                  bool bFormatted
                  ) const;

   virtual SEVERITY doInit();

   virtual E_COMMANDRETURN doProcess();
   /**
     * Implementation for the refresh method.  Not implemented yet.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(
                         GenericInterface *rpGICaller,
                         const I_CHAR *szOriginalCommand
                         );

   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

private:

   HistoricalShareholderList *m_pHistoricalShareholderList;
   DString m_dstrShareholderNumber;
   DString m_dstrName;
   GenericInterface *m_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalShareholderProcess.hpp-arc  $
//
//   Rev 1.0   Feb 06 2004 14:52:44   HERNANDO
//Initial revision.
 */
