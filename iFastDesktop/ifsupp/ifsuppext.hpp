#pragma once

#undef IFSUPP_LINKAGE
#ifdef IFSUPP_DLL
   #define IFSUPP_LINKAGE CLASS_EXPORT
#else
   #define IFSUPP_LINKAGE CLASS_IMPORT
#endif

#include <memory>
#include<ifastdbrkr\ifastdbrkr.hpp>
#include <atlstr.h>

class MgmtCo;
class DSTCUserSession;
class PooledHostConnectionManager;
class MessageServiceTest;

struct ifastdbrkr::MessageServiceConfig;

namespace ifsupp {
   typedef BOOL (__stdcall *PFNMGMTCOINFO)(DSTCUserSession*&, MgmtCo*&, CString&, CString&, CString&, CString&);
   void IFSUPP_LINKAGE SetMgmtCoInfoCallback(PFNMGMTCOINFO pfn);
   void __stdcall GetMgmtCoInfoCallback(PFNMGMTCOINFO& pfn);

   typedef void (__stdcall *PFNKICKSTATUSBAR)(void);
   void IFSUPP_LINKAGE SetStatusBarKicker(PFNKICKSTATUSBAR pfn);
   void __stdcall GetStatusBarKicker(PFNKICKSTATUSBAR& pfn);

   bool IFSUPP_LINKAGE EnableControlTextRewriter( const DString& );
   bool IFSUPP_LINKAGE testConnectivity(const ifastdbrkr::MessageService& service, const ifastdbrkr::MessageServiceConfig& config , DString& errorString);
   bool IFSUPP_LINKAGE testAWDConnectivity(DString& errorString);

   std::unique_ptr<MessageServiceTest> createTest(const ifastdbrkr::MessageService& service, const ifastdbrkr::MessageServiceConfig&);
};