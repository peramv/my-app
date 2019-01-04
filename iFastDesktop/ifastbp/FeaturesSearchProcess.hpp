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
//    DATE   : June 2003
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>

// Forward references
class FillSearchCriteria;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE FeaturesSearchProcess : public AbstractProcess
{
// Construction
public:
   FeaturesSearchProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~FeaturesSearchProcess();
   virtual SEVERITY performSearch(GenericInterface *rpGI, 
      const BFContainerId &idSearch, E_SEARCHACTION eSearchAction);
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual void doGetField(const GenericInterface *rpGICaller,
      const BFContainerId& idContainer, const BFFieldId& idField,
      const BFDataGroupId& idDataGroup, DString &strValueOut,
      bool bFormatted) const;
private:
   FillSearchCriteria *_pFillSearchCriteria;
   GenericInterface *_rpChildGI;
   DString _searchType,
      _initSearchCriteria,
      _initSearchUsing,
      _backgroundSearch;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeaturesSearchProcess.hpp-arc  $
//
//   Rev 1.0   Oct 04 2003 16:06:04   popescu
//Initial revision.
//
//   Rev 1.1   Jul 09 2003 21:56:22   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.0   Jun 27 2003 18:15:18   popescu
//Initial revision.
 *
 */
