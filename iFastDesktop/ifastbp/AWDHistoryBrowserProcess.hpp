#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2013 by International Financial, Inc.
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

class IFASTBP_LINKAGE AWDHistoryBrowserProcess : public AbstractProcess
{
public:
   AWDHistoryBrowserProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   ~AWDHistoryBrowserProcess(void);

protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();

private:
   GenericInterface *_rpChildGI;
   DString _accountNum;
   DString _extTransNum;
};