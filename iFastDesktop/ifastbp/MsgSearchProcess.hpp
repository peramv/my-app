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
//******************************************************************************

#include <bfproc\abstractprocess.hpp>

// Forward references
class MsgSearchCriteria;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE MsgSearchProcess : public AbstractProcess
{
// Construction
public:
   MsgSearchProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~MsgSearchProcess();
   virtual SEVERITY performSearch(GenericInterface *rpGI, 
      const BFContainerId &idSearch, E_SEARCHACTION eSearchAction);
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete(const Command &cmd);

private:
   MsgSearchCriteria *_pMsgSearchCriteria;
   GenericInterface *_rpChildGI;
   DString _searchType,
      _initSearchCriteria, // Kept for possible future use.
      _initSearchUsing,    // Kept for possible future use.
      _backgroundSearch;   // Kept for possible future use.
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/MsgSearchProcess.hpp-arc  $
//
//   Rev 1.0   Feb 21 2005 11:09:22   hernando
//Initial revision.
