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
// ^FILE   : SysLvlSettlementInstr.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SysLvlSettlementInstr
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

class MktIndexFundsList;

class IFASTCBO_LINKAGE SysLvlSettlementInstr : public MFCanBFCbo
{
public:

   SysLvlSettlementInstr( BFAbstractCBO &parent );
   virtual ~SysLvlSettlementInstr();

   SEVERITY init(const BFData&   data );
	void		initNew(const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );

private:

	void setFieldStates(const BFDataGroupId& idDataGroup);
	SEVERITY validateSettleLocation(const DString& strValue,const BFDataGroupId& idDataGroup );
};

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SysLvlSettlementInstr.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:56:28   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Oct 13 2004 13:02:16   VADEANUM
//Initial revision.
//
//   Rev 1.1   Nov 24 2003 18:12:58   HERNANDO
//Next revision.
//
//   Rev 1.0   Nov 20 2003 11:08:46   HERNANDO
//Initial revision.
//
//