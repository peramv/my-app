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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TradeSearchProcess.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 02/21/2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TradeSearchProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE TradeSearchProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   TradeSearchProcess();
   TradeSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~TradeSearchProcess();

protected:

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
     * This is a method which may be overridden by a subclass to set container
     * pointers on demand.  This method is invoked whenever an attempt is
     * about to be made to use a container that hasn't been set yet.  The
     * pointer returned will be used to set the container pointer.
     * @param idList - ID of list to set pointer for.
     * @param idDataGroup - group ID currently being used.
     * @returns void pointer of list to use.
     */
   void *getPtrForContainer(
                           const BFContainerId& idContainer,
                           const BFDataGroupId& idDataGroup
                           );

	/**
     * This method implements the base functionality for ok processing,
     * including committing all updated groups and submitting a transaction,
     * if required.  This may be overridden if the derived process needs more
     * than the base functionality.
     * @param rpGICaller - A reference pointer to the calling GenericInterface.
     * returns returns highest SEVERITY encountered, check conditions
     */
   SEVERITY ok2(
      GenericInterface *rpGICaller
      );
   /**
     * This method is used to implement subclass overrides for getField.  The business
     * process must determine where to locate the field.
     * Override this method and set appropriate flags via addFieldDetails,
     * if the derived class must process getField differently than this
     * base class does.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param fieldID - ID of field we are getting.
     * @param idDataGroup - group ID to use for CBO processing
     * @param strValue - A string reference where value is returned.
     * @param bFormatted - Flag where true means get data formatted.
     */
   void doGetField(
      const GenericInterface *rpGICaller,
      const BFContainerId& idContainer,
      const BFFieldId& fieldID,
      const BFDataGroupId& idDataGroup,
      DString &strValueOut,
      bool bFormatted
      ) const;
	/**
     * This method is used to implement subclass overrides for setField.  The business
     * process must determine where to locate the field.
     * Override this method and set appropriate flags via addFieldDetails,
     * if the derived class must process setField differently than this
     * base class does.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param fieldID - ID of field we are getting.
     * @param idDataGroup - group ID to use for CBO processing
     * @param strValue - A string reference for the value of the field to be
     * set.
     * @param bFormatted - Flag where true means incoming data is formatted.
     * @returns SEVERITY indicating any errors/warnings encountered.
     */
   SEVERITY doSetField(
      const GenericInterface *rpGICaller,
      const BFContainerId& idContainer,
      const BFFieldId& fieldID,
      const BFDataGroupId& idDataGroup,
      const DString& strValue,
      bool bFormatted
      );

   /**
     * The caller is expected to have set up any search criteria  (via setField) 
     * prior to calling this method.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idSearch - ID of specific search to perform.
     * @param eSearchType - Search action to perform.  (Start or next block). 
     * @returns SEVERITY noting any error/warning conditions
     */
   SEVERITY performSearch( GenericInterface *rpGI, 
                           const BFContainerId& idSearch, 
                           E_SEARCHACTION eSearchAction );
   /**
     * Subclasses will implement this method to reflect state of a search.
     * Used by child to check if more records exist in a search.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idSearch - ID of search to check for more records.
     * @returns true if more exist
     */
   bool doMoreRecordsExist(
                               GenericInterface *rpGICaller,
                               const BFContainerId& idSearch
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
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
private:
   GenericInterface *_rpChildGI;
   PendingTradeList *_pPendingList;
   TransactionList *_pTransactionList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradeSearchProcess.hpp-arc  $
//
//   Rev 1.3   Nov 10 2005 13:22:54   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.2   Apr 26 2004 13:09:46   popescu
//PET 1046, FN02, Trade search by account, code clean-up, removed old comments
//
//   Rev 1.1   Mar 21 2003 17:49:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Mar 03 2003 09:52:18   KOVACSRO
//Initial revision.

  */