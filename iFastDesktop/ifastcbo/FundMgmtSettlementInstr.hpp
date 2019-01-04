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
//    Copyright 2003, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : FundMgmtSettlementInstr.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundMgmtSettlementInstr
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

class IFASTCBO_LINKAGE FundMgmtSettlementInstr : public MFCanBFCbo
{
public:

   FundMgmtSettlementInstr( BFAbstractCBO &parent );
   virtual ~FundMgmtSettlementInstr();

   SEVERITY init(const BFData& data, const DString&  );
	void     initNew(const BFDataGroupId& idDataGroup, const DString&, const DString& dstrIndexCode );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:

   SEVERITY validateSettlementLocation( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateDefault( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY setSettleAccountNum (const DString &dstrSettleLocCode, const BFDataGroupId& idDataGroup);
	void setFieldStates(const BFDataGroupId& idDataGroup);
};

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundMgmtSettlementInstr.hpp-arc  $
//
//   Rev 1.2   Nov 21 2004 17:06:02   aguilaam
//Pet 1117/21
//
//   Rev 1.1   Nov 14 2004 14:42:52   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Oct 13 2004 13:17:24   VADEANUM
//Initial revision.
//
//   Rev 1.1   Nov 24 2003 18:11:26   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:08:42   HERNANDO
//Initial revision.
//