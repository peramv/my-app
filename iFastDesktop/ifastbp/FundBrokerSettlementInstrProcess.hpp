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
//    AUTHOR : 
//    DATE   : 
//
//
//    Copyright 2004 by International Financial Data Service.
//
//******************************************************************************
#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>
#include <ifastbp\settlementinstrprocess.hpp>

class FundMgmtSettlementInstrList;
class FundBrokerSettlementInstrList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE FundBrokerSettlementInstrProcess : public SettlementInstrProcess
{
public:

   FundBrokerSettlementInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FundBrokerSettlementInstrProcess();

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd ); 
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD,
                                   const BFDataGroupId &idDataGroup );
   virtual E_COMMANDRETURN doProcess();
	//void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );   
   virtual bool doOk(GenericInterface *rpGICaller);
   
private:

   GenericInterface *m_rpChildGI;
   FundMgmtSettlementInstrList *m_pFndMgmtSettlementInstructiondList;
	FundBrokerSettlementInstrList *m_pSettlementInstructiondList;
   DString m_dstrFundBrokerCode;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/FundBrokerSettlementInstrProcess.hpp-arc  $
//
//   Rev 1.1   Dec 09 2004 15:32:38   vadeanum
//PET1117_FN21: settlement instructions - added doValidateAll().
//
//   Rev 1.0   Nov 26 2004 16:52:36   aguilaam
//Initial revision.
//
//   Rev 1.0   Oct 13 2004 15:22:24   VADEANUM
//Initial revision.
//
