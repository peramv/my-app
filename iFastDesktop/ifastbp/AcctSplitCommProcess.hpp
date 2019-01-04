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
// ^FILE   : AcctSplitCommProcess.hpp
// ^AUTHOR : 
// ^DATE   : Aug 23, 2001
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

class IFASTBP_LINKAGE AcctSplitCommProcess : public AbstractProcess
{

public:

   /**
    * Default constructor
    */

//CP20030319   AcctSplitCommProcess();
   AcctSplitCommProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

   /**
    * Default destructor
    */

   virtual ~AcctSplitCommProcess();
   virtual bool doOk( GenericInterface* rpGICaller );


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

private:

   GenericInterface   * m_rpChildGI;     

   //Globals
   DString _dstrAccountNum;
   DString _dstrCreatingAcct;
   DString _dstrCreatingShr;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AcctSplitCommProcess.hpp-arc  $
//
//   Rev 1.8   Jul 20 2012 14:25:28   dchatcha
//IN# 2994672 - Block Service Unit Transfers, simplified logic that let account cbo update b\b\s
//
//   Rev 1.7   May 14 2012 15:44:28   dchatcha
//P0186479 FN10 -Gap 14G - Block Service Unit Transfers.
//
//   Rev 1.6   Mar 21 2003 17:35:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:53:00   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:51:40   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:22:00   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:14:54   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   23 Nov 2001 10:58:14   HSUCHIN
//added 2 globals to store NASU params
//
//   Rev 1.0   23 Aug 2001 14:51:40   HSUCHIN
//Initial revision.
 */
