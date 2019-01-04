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
//    AUTHOR : Monica Vadeanu
//    DATE   : June 2004
//
//
//    Copyright 2004 by International Financial Data Services
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

class ShrFundSponsorAgreementList;

class IFASTBP_LINKAGE ShrFundSponsorAgreementProcess : public AbstractProcess
{
// Construction
public:
   ShrFundSponsorAgreementProcess( GenericInterfaceContainer* pGIC, 
                                   GenericInterface* pGIParent, 
										     const Command& rCommand );

   virtual ~ShrFundSponsorAgreementProcess();
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

	ShrFundSponsorAgreementList *_pShrFundSponsorAgreementList;
	DString _dstrAccount;
	DString _dstrShareholder;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ShrFundSponsorAgreementProcess.hpp-arc  $
//
//   Rev 1.1   Jul 27 2004 15:47:20   VADEANUM
//PET1117 FN01 - Shareholder Static Data - first working version.
//
//   Rev 1.0   Jul 26 2004 10:30:38   VADEANUM
//Initial revision.
//
