#pragma once
//******************************************************************************
//
// COPYRIGHT:
// 
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    AUTHOR : Monica Porteanu
//    DATE   : May 2005
//
//
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\opcconfirmreprintprocess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class OPCOnlineConfirmReprint;

class IFASTBP_LINKAGE OPCOnlineConfirmReprintProcess : public OPCConfirmReprintProcess
{
// Construction
public:
   OPCOnlineConfirmReprintProcess( GenericInterfaceContainer* pGIC, 
                                   GenericInterface* pGIParent, 
							       const Command& rCommand );

   virtual ~OPCOnlineConfirmReprintProcess();
protected:
   virtual SEVERITY doInit();

   virtual E_COMMANDRETURN doProcess();

   virtual bool doModelessChildComplete( const Command &cmd );   	 	

   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand )
   {
      return true;
   }
   
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD,
                                   const BFDataGroupId &idDataGroup );
   
	void *getPtrForContainer( const BFContainerId &idContainer,
                             const BFDataGroupId &idDataGroup );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

	bool doOk( GenericInterface *rpGICaller );

private:
   GenericInterface *_rpChildGI;
   
   SEVERITY processParameters();	

   OPCOnlineConfirmReprint *_pOPCOnlineConfirmReprint;
   DString _dstrTransId;
   DString _dstrFund;
   DString _dstrClass;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/OPCOnlineConfirmReprintProcess.hpp-arc  $
//
//   Rev 1.0   May 06 2005 12:34:40   porteanm
//Initial revision.
//

