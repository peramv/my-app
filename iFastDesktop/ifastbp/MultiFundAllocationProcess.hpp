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
//    DATE   : August, 2003
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
class MFAccount;
class TradeFromFundAllocList;
class TradeFundAllocList;

class IFASTBP_LINKAGE MultiFundAllocationProcess : public AbstractProcess
{
// Construction
public:
   MultiFundAllocationProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~MultiFundAllocationProcess();
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand)
   {
      return true;
   }
   virtual SEVERITY doValidateAll(BFAbstractCBO *rpWSD,
      const BFDataGroupId &idDataGroup);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual void doGetField(const GenericInterface *rpGICaller,
      const BFContainerId& idContainer, const BFFieldId& idField,
      const BFDataGroupId& idDataGroup, DString &strValueOut,
      bool bFormatted) const;
   virtual void *getPtrForContainer(const BFContainerId& idContainer,
      const BFDataGroupId& idDataGroup);
   virtual void doPostOk(GenericInterface *rpGICaller, 
      bool bSuccessFlag);
private:
   SEVERITY processParameters();
   GenericInterface *_rpChildGI;
   DString _dstrCaller,
      _dstrAcctNum,
      _dstrListKey,
      _dstrTransType;
   MFAccount *_pMFAccount;
   TradeFromFundAllocList *_pTradeFromFundAllocList;
   TradeFundAllocList *_pTradeToFundAllocList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MultiFundAllocationProcess.hpp-arc  $
//
//   Rev 1.1   Sep 01 2003 21:21:12   popescu
//PET 809 FN 02, CIBC Multi fund enhancement
//
//   Rev 1.0   Aug 14 2003 15:48:16   popescu
//Initial revision.
 */
