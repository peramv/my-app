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
// ^FILE   : SettlementInstrList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SettlementInstrList
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

class SettlementInstr;

class IFASTCBO_LINKAGE SettlementInstrList : public MFCanBFCbo
{

public:

   SettlementInstrList( BFAbstractCBO &parent );
   virtual ~SettlementInstrList();

   SEVERITY init( const DString& dstrAccountNum,
                  const DString& dstrFundBrokerCode,
		          const BFDataGroupId& idDataGroup,
				  const DString& dstrTrack = I_("N"),
				  const DString& dstrPageName = NULL_STRING );

   SEVERITY init( const BFDataGroupId& idDataGroup,
                  const DString& dstrAccountNum,
                  const DString& dstrFundBrokerCode );   

   bool isDuplicateSettlementLocation( DString &, const BFDataGroupId& idDataGroup );
   bool isDuplicateDefault( DString &, const BFDataGroupId& idDataGroup );
   
   SEVERITY getSettlementCodeSubstList( DString& dstrSettleCodeSubstList, const BFDataGroupId& idDataGroup);
   SEVERITY checkDuplicate ( const SettlementInstr *pSettlementInstr, const BFDataGroupId &idDataGroup);


protected:

   virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doCreateNewObject(BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup );
	virtual void  getStrKey( DString &strKey, const BFData& data  );	

   BFData m_requestData;
   DString _accountNum;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementInstrList.hpp-arc  $
//
//   Rev 1.5   May 04 2007 13:53:58   jankovii
//PET 2321 FN01 - MT54X Default Pay Type.
//
//   Rev 1.4   Dec 10 2004 17:18:56   vadeanum
//PET117_FN21: settlement instructions enhancement.
//
//   Rev 1.3   Nov 30 2004 11:21:34   aguilaam
//PET117_FN21: settlement instructions enhancement.
//
//   Rev 1.2   Nov 19 2004 17:33:18   aguilaam
//PET117_FN21: settlement instructions enhancement (temporary check-in for build)
//
//   Rev 1.1   Nov 14 2004 14:54:06   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Oct 13 2004 13:34:04   VADEANUM
//Initial revision.
//
