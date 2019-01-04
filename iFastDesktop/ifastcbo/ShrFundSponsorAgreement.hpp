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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE      : ShrFundSponsorAgreement.hpp
// ^AUTHOR    : Monica Vadeanu
// ^DATE      : June, 2004
//
// ^CLASS     : ShrFundSponsorAgreement
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ShrFundSponsorAgreement : public MFCanBFCbo, private boost::noncopyable
{
public:
   ShrFundSponsorAgreement (BFAbstractCBO &parent);
   virtual ~ShrFundSponsorAgreement();

   SEVERITY init( const BFData &viewData );

   SEVERITY init( const BFDataGroupId &idDataGroup );
protected:
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId &idField, 
														 const BFDataGroupId &idDataGroup );
	virtual void doInitWithDefaultValues( const BFDataGroupId &idDataGroup );
   virtual SEVERITY doValidateField( const BFFieldId &idField, 
											    const DString &strValue, 
											    const BFDataGroupId &idDataGroup );

   virtual void doReset( const BFDataGroupId &idDataGroup );
private:
   SEVERITY commonInit( const DString &dstrFundGroup, 														 
								const BFDataGroupId &idDataGroup );

   SEVERITY setFundGroupName( const BFDataGroupId &idDataGroup );
	SEVERITY setEffectiveDate( const BFDataGroupId &idDataGroup );		
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFundSponsorAgreement.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:56:04   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Jul 28 2004 14:43:08   VADEANUM
//PET1117 FN01 - Shareholder Static Data.
//
//   Rev 1.0   Jul 26 2004 10:17:52   VADEANUM
//Initial revision.
//
