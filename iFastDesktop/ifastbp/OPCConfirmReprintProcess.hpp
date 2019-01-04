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
#include <ifastbp\confirmreprintprocess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class OPCConfirmReprint;

class IFASTBP_LINKAGE OPCConfirmReprintProcess : public ConfirmReprintProcess
{
// Construction
public:
   OPCConfirmReprintProcess( GenericInterfaceContainer* pGIC, 
                          GenericInterface* pGIParent, 
 						  const Command& rCommand );

   virtual ~OPCConfirmReprintProcess();
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
	
   virtual bool doSend( GenericInterface *rpGICaller, const I_CHAR *szMessage );

private:
   GenericInterface *_rpChildGI;
   
   SEVERITY processParameters();	

   OPCConfirmReprint *_pOPCConfirmReprint;
   DString _dstrAccountNum;
   DString _dstrTransId;
   DString _dstrFund;
   DString _dstrClass;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/OPCConfirmReprintProcess.hpp-arc  $
//
//   Rev 1.3   May 26 2005 09:42:36   porteanm
//PET OPC Confirm Reprint - Cleanup.
//
//   Rev 1.2   May 25 2005 14:57:14   porteanm
//PET OPC Confirm Reprint - Reset.
//
//   Rev 1.1   May 24 2005 12:50:18   porteanm
//PET OPC Confirm Reprint - Renamed OPC files. Changed class hierarchy.
//
//   Rev 1.0   May 05 2005 13:54:20   porteanm
//Initial revision.
//
