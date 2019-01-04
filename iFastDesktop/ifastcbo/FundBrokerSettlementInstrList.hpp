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
//    Copyright 2004, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : FundBrokerSettlementInstrList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundBrokerSettlementInstrList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#include <ifastcbo\settlementinstrlist.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class FundBrokerSettlementInstr;

class IFASTCBO_LINKAGE FundBrokerSettlementInstrList : public SettlementInstrList
{

public:

   FundBrokerSettlementInstrList( BFAbstractCBO &parent );
   virtual ~FundBrokerSettlementInstrList();

   SEVERITY getFundBrokerSettlementInstr(	const DString &dstrSettleInstrCode,																			 
											const BFDataGroupId &idDataGroup,
											FundBrokerSettlementInstr *&pFundBrokerSettlementInstr )	;

   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, 
                           long lValidateGroup ) ;


protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );   
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );	

   BFData m_requestData;

private:

	void buildKey( DString &dstrKey, 
					  	const DString &dstrAccountNum,
						const DString &dstrSettleInstrCode );
   
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBrokerSettlementInstrList.hpp-arc  $
//
//   Rev 1.1   Nov 26 2004 16:56:28   aguilaam
//PET1117_FN21: settlement instructions
//
//   Rev 1.0   Nov 17 2004 15:39:22   aguilaam
//Initial revision.
//
//   Rev 1.0   Oct 13 2004 13:47:24   VADEANUM
//Initial revision.
//
