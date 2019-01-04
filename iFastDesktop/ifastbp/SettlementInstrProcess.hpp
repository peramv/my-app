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
//    Copyright 2003 by International Financial Data Service.
//
//******************************************************************************
#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

class SettleLocationAcctLvlList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE SettlementInstrProcess : public AbstractProcess,
   public IFastHistoricalParameters
{
public:

   SettlementInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~SettlementInstrProcess();

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD,
                                   const BFDataGroupId &idDataGroup );

   virtual E_COMMANDRETURN doProcess();
	void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual bool doOk(GenericInterface *rpGICaller);
   	
	virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer, 
                                            BFFieldId &recordIdField, DString& tableId, DString& dstrKeys); 
   
	SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   GenericInterface *m_rpChildGI;   
   DString _accountNum;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/SettlementInstrProcess.hpp-arc  $
//
//   Rev 1.2   Dec 09 2004 15:31:22   vadeanum
//PET1117_FN21: settlement instructions - added doValidateAll().
//
//   Rev 1.1   Nov 19 2004 17:32:20   aguilaam
//PET117_FN21: settlement instructions enhancement (temporary check-in for build)
//
//   Rev 1.0   Oct 13 2004 15:17:54   VADEANUM
//Initial revision.
//
