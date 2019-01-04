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
// ^FILE   : SettlementInstr.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SettlementInstr
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

class IFASTCBO_LINKAGE SettlementInstr : public MFCanBFCbo
{
public:

   SettlementInstr( BFAbstractCBO &parent );
   virtual ~SettlementInstr();

   SEVERITY init( const BFData& data );
	SEVERITY init(const BFDataGroupId& idDataGroup );

protected:

   virtual SEVERITY doValidateField( const BFFieldId& idField, 
		                               const DString& strValue, 
												 const BFDataGroupId& idDataGroup );   
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

private:

   SEVERITY validateSettlementInstrCode( const DString& dstrSettlementInstrCode, 
													  const BFDataGroupId& idDataGroup );
   SEVERITY validateDefaultSettlementInstr( const DString& dstrDefaultCode, 
														  const BFDataGroupId& idDataGroup );
   SEVERITY validateEffectiveDate( const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup );
   SEVERITY validateStopDate( const DString& dstrStopDate, const BFDataGroupId& idDataGroup );
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementInstr.hpp-arc  $
//
//   Rev 1.2   May 04 2007 13:52:22   jankovii
//PET 2321 FN01 - MT54X Default Pay Type.
//
//   Rev 1.1   Nov 14 2004 14:54:02   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Oct 13 2004 13:33:52   VADEANUM
//Initial revision.
//
