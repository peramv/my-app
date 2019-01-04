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
//    Copyright 2001 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class HistoricalSystematicIndexList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Historical Systematic Index process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> </dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE HistoricalSystematicIndexProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   HistoricalSystematicIndexProcess();
   HistoricalSystematicIndexProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~HistoricalSystematicIndexProcess();

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
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
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
                         )
   {
      return(false);
   }
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

private:

   HistoricalSystematicIndexList* m_pHistoricalSystematicIndexList;
   DString                 m_dstrTransactionNumber;
   GenericInterface*           m_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalSystematicIndexProcess.hpp-arc  $
//
//   Rev 1.6   Mar 21 2003 17:41:22   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:53:18   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   22 May 2002 18:20:54   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:17:28   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   Jun 01 2001 15:17:42   HERNANDO
//Clean up.
//
//   Rev 1.1   May 11 2001 12:48:58   HERNANDO
//_
//
//   Rev 1.0   May 10 2001 14:12:58   HERNANDO
//Initial revision.
 * 
 * 
 */
