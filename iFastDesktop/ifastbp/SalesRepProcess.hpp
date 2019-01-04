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

class AgentList;

class IFASTBP_LINKAGE SalesRepProcess : public AbstractProcess
{
// Construction
public:
   SalesRepProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~SalesRepProcess();
   SEVERITY performSearch(GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction);
   bool doMoreRecordsExist(GenericInterface *rpGICaller, const BFContainerId& idSearch);

protected:
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand);
   virtual SEVERITY doInit();
   virtual void doPostOk(GenericInterface *rpGICaller, 
      bool bSuccessFlag);
private:
   GenericInterface *_rpChildGI;
   AgentList* _pAgentList;
   DString _dstrBrokerCode,
      _dstrBranchCode,
      _dstrCaller;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SalesRepProcess.hpp-arc  $
 * 
 *    Rev 1.6   Jul 10 2003 22:20:40   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.5   Mar 21 2003 17:47:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:53:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 18:19:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:18:24   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   16 Oct 2001 11:20:22   HSUCHIN
 * Implemented GetMore functionality
 * 
 *    Rev 1.0   Feb 15 2000 10:59:22   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 14 2000 08:51:24   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.4   Dec 31 1999 13:16:06   POPESCUS
// validations, fixes and misc
// 
//    Rev 1.3   Dec 24 1999 14:18:04   POPESCUS
// fixes and removed commented code
// 
//    Rev 1.2   Dec 22 1999 12:23:22   ZHANGCEL
// Revision bug fixed
// 
//    Rev 1.1   Dec 22 1999 11:47:12   ZHANGCEL
// For release
*/
