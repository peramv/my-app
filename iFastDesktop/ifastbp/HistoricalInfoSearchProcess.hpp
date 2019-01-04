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
//    AUTHOR : Serban Popescu
//    DATE   : 01/08/2003
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>

// Forward references
class HistoricalInfoSearchCriteria;
class BFFieldId;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the ProtectedFundList process
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 01/08/2003</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE HistoricalInfoSearchProcess : public AbstractProcess
{
// Construction
public:
//CP20030319   HistoricalInfoSearchProcess();
   HistoricalInfoSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~HistoricalInfoSearchProcess();

protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete(const Command &cmd);
private:
   HistoricalInfoSearchCriteria *_pHistoricalInfoSearchCriteria;
   GenericInterface *_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalInfoSearchProcess.hpp-arc  $
//
//   Rev 1.2   Mar 21 2003 17:41:06   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Mar 05 2003 11:22:44   PURDYECH
//IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
//
//   Rev 1.0   Feb 06 2003 11:53:52   popescu
//Initial revision.
//
 *
 */
