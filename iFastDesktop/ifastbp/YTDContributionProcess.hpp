#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : YTDContributionProcess.hpp
// ^AUTHOR : 
// ^DATE   : 03/08/2001
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class RSPReceiptsList;

class IFASTBP_LINKAGE YTDContributionProcess : public AbstractProcess
{

public:

   /**
    * Default constructor
    */

//CP20030319   YTDContributionProcess();
   YTDContributionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

   /**
    * Default destructor
    */

   virtual ~YTDContributionProcess();

protected:

   /**     
     * Used to bring a modeless dialog (via parent process) to the top of the
     * window stack.  Note that if the process needs to change its state due
     * to a change in input parameters, then this would occur here and the
     * process would notify the child dialog of the need to refresh.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, check conditions if false
     */

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

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

   virtual bool doModelessChildComplete( const Command &cmd );

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
     * This method is invoked whenever an attempt is about to be made 
     * to use a container that hasn't been set yet.  The pointer returned 
     * will be used to set the container pointer.
     * @param idList - ID of list to set pointer for.
     * @param idDataGroup - group ID currently being used.
     * @returns void pointer of list to use.
     */

   virtual void *getPtrForContainer( const BFContainerId& idContainer,
                                     const BFDataGroupId& idDataGroup );

   /**
     * This method is used to implement subclass overrides for getField.  The business
     * process must determine where to locate the field.
     * Override this method and set appropriate flags via addFieldDetails,
     * if the derived class must process getField differently than this
     * base class does.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param idDataGroup - group ID to use for CBO processing
     * @param strValue - A string reference where value is returned.
     * @param bFormatted - Flag where true means get data formatted.
     */

   void doGetField( const GenericInterface *rpGICaller, 
                    const BFContainerId& idContainer, 
                    const BFFieldId& idField,
                    const BFDataGroupId& idDataGroup, 
                    DString &strValueOut, 
                    bool bFormatted ) const;

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

   bool doMoreRecordsExist( GenericInterface *rpGICaller, 
                            const BFContainerId& idSearch );

private:

   GenericInterface   * m_rpChildGI;

   //Pointer to RSPReceipts List.  This pointer is used to perform getMore searches

   RSPReceiptsList *_pRSPReceiptsList;

   //Globals
   DString _dstrAccountNum;
   DString _dstrShrNum;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/YTDContributionProcess.hpp-arc  $
//
//   Rev 1.6   Mar 21 2003 17:50:22   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:53:44   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:54:04   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   19 Mar 2002 13:20:16   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   20 Aug 2001 12:05:42   HSUCHIN
//cleanup and added comments
//
//   Rev 1.1   18 Aug 2001 09:28:34   HSUCHIN
//implemented moreAvailiable and other enhancements
//
//   Rev 1.0   05 Aug 2001 15:31:42   HSUCHIN
//Initial revision.
 */
