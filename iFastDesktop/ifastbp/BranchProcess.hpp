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

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class BranchList;

class IFASTBP_LINKAGE BranchProcess : public AbstractProcess
{
// Construction
public:
   BranchProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~BranchProcess();
   bool doMoreRecordsExist(GenericInterface *rpGICaller, const BFContainerId& idSearch);
   SEVERITY performSearch(GenericInterface *rpGI, 
      const BFContainerId& idSearch, E_SEARCHACTION eSearchAction);
protected:
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand);
   virtual SEVERITY doInit();
   virtual void doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag);
private:
   GenericInterface *_rpChildGI;
   BranchList *_pBranchList;
   DString _dstrBrokerCode,
      _dstrCaller;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BranchProcess.hpp-arc  $
 * 
 *    Rev 1.6   Jul 10 2003 22:19:14   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.5   Mar 21 2003 17:36:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:53:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   Jul 31 2002 16:13:26   HERNANDO
 * More button implementation.
 * 
 *    Rev 1.2   22 May 2002 18:21:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.1   19 Mar 2002 13:15:20   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.0   Feb 15 2000 10:58:58   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 14 2000 08:51:22   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.4   Jan 11 2000 08:41:42   POPESCUS
// fixes and validation
// 
//    Rev 1.3   Dec 24 1999 14:18:02   POPESCUS
// fixes and removed commented code
// 
//    Rev 1.2   Dec 22 1999 12:23:14   ZHANGCEL
// Revision bug fixed
// 
//    Rev 1.1   Dec 22 1999 11:46:46   ZHANGCEL
// For release
*/