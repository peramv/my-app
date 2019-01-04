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
// ^FILE   : AcctSettlementInstrList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AcctSettlementInstrList
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

class AcctSettlementInstr;

class IFASTCBO_LINKAGE AcctSettlementInstrList : public SettlementInstrList
{

public:

   AcctSettlementInstrList( BFAbstractCBO &parent );
   virtual ~AcctSettlementInstrList();
  
	SEVERITY getAcctSettlementInstr( const DString &dstrSettleInstrCode,	
				  					 const BFDataGroupId &idDataGroup,
									 AcctSettlementInstr *&pAcctSettlementInstr );

   SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, 
                           long lValidateGroup );

	

protected:

    virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );   
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData *data  );

	SEVERITY validateDuplicateDefaultInstr(const BFDataGroupId& idDataGroup);
	SEVERITY doesActiveDefaultInstrExist(const BFDataGroupId& idDataGroup,
		                                 DString &dstrInstrCode,
										 DString &dstrStopDate);
	SEVERITY doesFutureDefaultInstrExist(const BFDataGroupId& idDataGroup,
										 const DString dstrInstrCode,
										 const DString dstrStopDate);


   BFData m_requestData;

private:

	void buildKey( DString &dstrKey, 
				   const DString &dstrAccountNum,
				   const DString &dstrSettleInstrCode,
				   const DString &dstrEffectiveDate,
				   const DString &dstrStopDate );
   
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementInstrList.hpp-arc  $
//
//   Rev 1.2   May 04 2007 13:48:42   jankovii
//PET 2321 FN01 - MT54X Default Pay Type.
//
//   Rev 1.1   Nov 24 2004 13:01:34   aguilaam
//PET1117_FN21: settlement instructions
//
//   Rev 1.0   Oct 13 2004 13:47:24   VADEANUM
//Initial revision.
//
