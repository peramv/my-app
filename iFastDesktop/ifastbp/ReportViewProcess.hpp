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

class IFASTBP_LINKAGE ReportViewProcess : public AbstractProcess
{

   public:
   //******************************************************************************
   // Constructor
   //******************************************************************************
//CP20030319   ReportViewProcess();
   ReportViewProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

   //******************************************************************************
   // Destructor
   //******************************************************************************
   virtual ~ReportViewProcess();

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

   virtual bool ReportViewProcess::doModelessSetFocus( GenericInterface *rpGICaller );

   virtual SEVERITY ok2( GenericInterface *rpGI );
   //******************************************************************************
   // This functions starts the Reports Dialog
   // @returns E_COMMANDRETURN.
   //******************************************************************************
   virtual E_COMMANDRETURN doProcess();

   virtual void doGetField(
                             const GenericInterface *rpGICaller,
                             const BFContainerId& idContainer,
                             const BFFieldId& idField,
                             const BFDataGroupId& idDataGroup,
                             DString &strValueOut,
                             bool bFormatted
                             ) const;
   private:
   GenericInterface *_rpChildGI;                      //Pointer to parent object.   
   DString _dstrReportPath, _dstrReportName, _dstrReportData;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ReportViewProcess.hpp-arc  $
//
//   Rev 1.3   Mar 21 2003 17:46:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Dec 10 2002 13:34:58   HSUCHIN
//added dogetfield
//
//   Rev 1.1   Dec 10 2002 10:59:24   HSUCHIN
//added report data
//
//   Rev 1.0   Dec 08 2002 22:10:52   HSUCHIN
//Initial Revision
 */
