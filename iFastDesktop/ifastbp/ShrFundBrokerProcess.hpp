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
//    DATE   : November 2004
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


class ShrFundBrokerList;

class IFASTBP_LINKAGE ShrFundBrokerProcess : public AbstractProcess
{
// Construction
public:
   ShrFundBrokerProcess( GenericInterfaceContainer* pGIC, 
                          GenericInterface* pGIParent, 
								  const Command& rCommand );

   virtual ~ShrFundBrokerProcess();
protected:
   virtual SEVERITY doInit();

   virtual E_COMMANDRETURN doProcess();

   virtual bool doModelessChildComplete( const Command &cmd );  

   virtual SEVERITY performSearch( GenericInterface *rpGI, 
                                   const BFContainerId& idSearch, 
											  E_SEARCHACTION eSearchAction );
   
	virtual bool doMoreRecordsExist( GenericInterface *rpGICaller,
                                    const BFContainerId& idSearch );

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

	ShrFundBrokerList *_pShrFundBrokerList;
	DString _dstrAccount;
	DString _dstrShareholder;
};



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ShrFundBrokerProcess.hpp-arc  $
//
//   Rev 1.2   Nov 28 2004 14:07:42   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support 
//
//   Rev 1.1   Nov 11 2004 16:26:30   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support.
//
//   Rev 1.0   Nov 04 2004 10:34:06   VADEANUM
//Initial revision.
//
