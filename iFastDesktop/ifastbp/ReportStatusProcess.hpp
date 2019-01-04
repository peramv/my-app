#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>
// Forward references

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class ReportStatusList;

class IFASTBP_LINKAGE ReportStatusProcess : public AbstractProcess
{

   public:
   //******************************************************************************
   // Constructor
   //******************************************************************************
//CP20030319   ReportStatusProcess();
   ReportStatusProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

   //******************************************************************************
   // Destructor
   //******************************************************************************
   virtual ~ReportStatusProcess();

   SEVERITY performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

   bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

   protected:

   //******************************************************************************
   // @returns SEVERITY.
   //******************************************************************************
   virtual SEVERITY doInit();

   //******************************************************************************
   // Function which tells the generic interface container that the modeless child
   // has been destroyed.
   // @param   const Command &cmd - cmd indicating the child is destroyed.
   // @returns bool - true when successful.
   //******************************************************************************
   virtual bool doModelessChildComplete( const Command &cmd );

   //******************************************************************************
   // Functions which brings the Report dialog to focus and top of the window 
   // stack.  It also notifies Report to refresh in case account information 
   // has changed.
   // @param   GenericInterface *rpGICaller - pointer to parent object.
   // @return bool - true when successful, false otherwise.
   //******************************************************************************
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

   //******************************************************************************
   // This functions starts the Reports Dialog
   // @returns E_COMMANDRETURN.
   //******************************************************************************
   virtual E_COMMANDRETURN doProcess();

   //******************************************************************************
   // Function which get the container pointer on demand.
   // @param   const BFContainerId& idContainer - Id to the container.
   //          const BFDataGroupId& idDataGroup - group id.
   // @returns void.
   //******************************************************************************
   void * getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

   SEVERITY doSetField( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& fieldID,
                                          const BFDataGroupId& idDataGroup,
                                          const DString& strValue,
                                          bool bFormatted );
   private:
   GenericInterface *_rpChildGI;                      //Pointer to parent object.   
   ReportStatusList* _pReportStatusList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ReportStatusProcess.hpp-arc  $
//
//   Rev 1.2   Mar 21 2003 17:46:46   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Dec 08 2002 22:12:38   HSUCHIN
//added support for printer process and report view
//
//   Rev 1.0   Nov 29 2002 13:52:48   HSUCHIN
//Initial Revision
 */
