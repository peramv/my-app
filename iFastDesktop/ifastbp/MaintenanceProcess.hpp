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
//    Copyright 1997 by DST Systems, Inc.
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

// Forward references
/**
 * Class that manages the entity process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */
class GroupList;

class IFASTBP_LINKAGE MaintenanceProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   MaintenanceProcess();
   MaintenanceProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~MaintenanceProcess();

protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();

private:
   GroupList *_pGroupList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MaintenanceProcess.hpp-arc  $
//
//   Rev 1.5   Mar 21 2003 17:44:36   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:53:28   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:20:32   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:17:52   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Aug 14 2000 17:29:28   FENGYONG
//Add fields
//
//   Rev 1.0   Aug 02 2000 13:44:22   VASILEAD
//Initial revision.
 *
 */
