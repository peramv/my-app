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
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FundMgmtSettlementInstrList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundMgmtSettlementInstrList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundMgmtSettlementInstrList : public MFCanBFCbo
{

friend class FundMgmtSettlementInstr;

public:

   FundMgmtSettlementInstrList( BFAbstractCBO &parent );
   virtual ~FundMgmtSettlementInstrList();

   SEVERITY init(	const DString& dstrAccountNum,
					   const DString& dstrFundBrokerCode,
					   const DString& dstrTrack = I_("N"),
					   const DString& dstrPageName = NULL_STRING);

   SEVERITY init( const DString& dstrAccountNum,
					   const DString& dstrFundBrokerCode,
                  const BFDataGroupId &idDataGroup );

   SEVERITY reInit();

   bool isDuplicateSettlementLocation( DString &, const BFDataGroupId& idDataGroup );
   bool isDuplicateDefault( DString &, const BFDataGroupId& idDataGroup );

   SEVERITY getSettlementLocationSubstList(DString& dstrSettleLocSubstList, const BFDataGroupId& idDataGroup);

protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );

   BFData m_requestData;

private:

   DString m_dstrSettleLocationCodeSubstitution;
   DString m_dstrInitialSettleLocationCode;
};


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundMgmtSettlementInstrList.hpp-arc  $
//
//   Rev 1.4   Dec 10 2004 17:19:58   vadeanum
//PET117_FN21: settlement instructions enhancement.
//
//   Rev 1.3   Nov 30 2004 16:13:36   aguilaam
//PET1117_FN21: settlement instructions
//
//   Rev 1.2   Nov 30 2004 11:37:58   aguilaam
//PET117_FN21: settlement instructions enhancement.
//
//   Rev 1.1   Nov 19 2004 17:33:04   aguilaam
//PET117_FN21: settlement instructions enhancement (temporary check-in for build)
//
//   Rev 1.0.1.0   Nov 14 2004 14:42:54   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Oct 13 2004 13:17:30   VADEANUM
//Initial revision.
//
//   Rev 1.1   Nov 24 2003 18:12:26   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:08:44   HERNANDO
//Initial revision.
