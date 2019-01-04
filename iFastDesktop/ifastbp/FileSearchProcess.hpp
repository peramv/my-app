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
// ^FILE   : FileSearchProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/14/2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FileSearchProcess
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

class IFASTBP_LINKAGE FileSearchProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   EntityAddressSearchProcess();
   FileSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FileSearchProcess();

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

   virtual bool doModelessChildComplete(const Command &cmd); 
 
private:
   GenericInterface *_rpChildGI;
	FileSearchCriteria *pFileSearchCriteria;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FileSearchProcess.hpp-arc  $
//
//   Rev 1.0   Feb 24 2005 17:18:22   ZHANGCEL
//Initial revision.
//
*/