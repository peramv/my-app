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
// ^FILE   : EntityAddressSearchProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/14/2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : EntityAddressSearchProcess
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

class IFASTBP_LINKAGE EntityAddressSearchProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   EntityAddressSearchProcess();
   EntityAddressSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~EntityAddressSearchProcess();

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

	virtual bool doModelessChildComplete(const Command &cmd); 
   	
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
	virtual void doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag );

private:
   GenericInterface *_rpChildGI;
	EntityAddressSearchCriteria *_pEntityAddressSearchCriteria;
   AddressEntityList *_pAddressEntityList;
	DString _strSearchType;
	DString _dstrAddressId;
	
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntityAddressSearchProcess.hpp-arc  $
//
//   Rev 1.1   Mar 18 2005 07:43:02   porteanm
//PET 1171 FN01 - EUSD Entity Address Update support.
//
//   Rev 1.0   Mar 10 2005 16:40:04   ZHANGCEL
//Initial revision.
//
*/