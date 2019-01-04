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
// ^CLASS    : ClientProcess
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

class IFASTBP_LINKAGE ClientProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   TradeSearchProcess();
   ClientProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ClientProcess();

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
   SEVERITY ValidateFieldsValues();
   bool CompareDouble(const BFFieldId& fieldID, const DString string1, const DString string2 );

private:

   GenericInterface *_rpChildGI;
   TransactionList *_pTransactionList;
};
