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
//    Copyright 2004 by IFDS.
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


class IFASTBP_LINKAGE BrokerRemarkProcess : public AbstractProcess
{
// Construction
public:
   BrokerRemarkProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~BrokerRemarkProcess();

protected:
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand);
   virtual SEVERITY doInit();
private:
   GenericInterface *_rpChildGI;
   DString _dstrCaller;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerRemarkProcess.hpp-arc  $
//
//   Rev 1.0   Sep 24 2004 14:49:44   YINGBAOL
//Initial revision.
 * 
 

  */




