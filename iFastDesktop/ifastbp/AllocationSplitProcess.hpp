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
//    DATE   : Aug 2003
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTBP_LINKAGE AllocationSplitProcess : public AbstractProcess
{
// Construction
public:
   AllocationSplitProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~AllocationSplitProcess();
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand)
   {
      return true;
   }
   bool doModelessSetFocus(GenericInterface *rpGICaller)
   {
      return true;
   }
private:
   SEVERITY processParameters();
   SEVERITY passParametersOn();
   bool isMultiAllocationPossible();
   DString _dstrAcctNum, 
      _dstrCaller, 
      _dstrListKey,
      _dstrSubListKey,
      _dstrTransType,
      _dstrTransNum,
      _dstrAllocationType,
      _dstrTradeDate,
      _dstrSettleCurrency;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AllocationSplitProcess.hpp-arc  $
//
//   Rev 1.2   Sep 03 2003 17:16:00   popescu
//fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
//
//   Rev 1.1   Sep 01 2003 21:21:06   popescu
//PET 809 FN 02, CIBC Multi fund enhancement
//
//   Rev 1.0   Aug 14 2003 15:50:40   popescu
//Initial revision.
 */
