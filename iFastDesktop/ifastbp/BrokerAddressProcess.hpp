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
//    Copyright 2003 by DST Systems, Inc.
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



class IFASTBP_LINKAGE BrokerAddressProcess : public AbstractProcess
{
// Construction
public:
	BrokerAddressProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~BrokerAddressProcess();

protected:
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual E_COMMANDRETURN doProcess();

   virtual SEVERITY doInit();
   virtual void doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag );
private:
   GenericInterface *_rpChildGI;


};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerAddressProcess.hpp-arc  $
//
//   Rev 1.0   Apr 03 2003 09:36:16   YINGBAOL
//Initial revision.
 * 
 

  */

