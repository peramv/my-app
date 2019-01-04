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
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE MgmtCoRefreshProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   MgmtCoRefreshProcess();
   MgmtCoRefreshProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~MgmtCoRefreshProcess();

protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
private:
   DString _dstrCompanyId;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MgmtCoRefreshProcess.hpp-arc  $
//
//   Rev 1.4   Mar 21 2003 17:45:04   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:53:30   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   22 May 2002 18:20:26   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:18:00   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   09 Jul 2001 15:29:40   SMITHDAV
//Initial revision.
 */
