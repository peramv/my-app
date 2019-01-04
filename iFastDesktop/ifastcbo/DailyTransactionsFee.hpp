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
// ^FILE      : DailyTransactionsFee.hpp
// ^AUTHOR    : Monica Vadeanu
// ^DATE      : Jan, 2004
//
// ^CLASS     : DailyTransactionsFee
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

class IFASTCBO_LINKAGE DailyTransactionsFee : public MFCanBFCbo, private boost::noncopyable
{
public:
   DailyTransactionsFee (BFAbstractCBO &parent);
   virtual ~DailyTransactionsFee();

   SEVERITY init (const BFData &viewData);
   SEVERITY init( const DString &dstrRecordType, 
						const DString &dstrFeeCode, 
						const DString &dstrFundCode,
						const DString &dstrClassCode, 
						const DString &dstrEffectiveDate, 
						const BFDataGroupId &idDataGroup );
protected:
   virtual SEVERITY doValidateField( const BFFieldId &idField, 
											    const DString &strValue, 
											    const BFDataGroupId &idDataGroup );
	virtual SEVERITY doApplyRelatedChanges( const BFFieldId &idField, 
														 const BFDataGroupId &idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId &idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId &idDataGroup, 
											  long lValidateGroup );
   virtual void doReset( const BFDataGroupId &idDataGroup );
private:
   SEVERITY commonInit( const DString &dstrRecordType, 
								const DString &dstrFeeCode, 
								const DString &dstrFundCode,
								const DString &dstrClassCode, 
								const DString &dstrEffectiveDate, 
								const BFDataGroupId &idDataGroup );

   SEVERITY setFundName( const BFDataGroupId &idDataGroup );
	SEVERITY setEffectiveDate( const BFDataGroupId &idDataGroup );
	SEVERITY setStopDate( const BFDataGroupId &idDataGroup );
   SEVERITY setStopDate9999( const BFDataGroupId &idDataGroup );
	SEVERITY setFeeRate( const BFDataGroupId &idDataGroup );

	SEVERITY validateFundCode( const DString &dstrFundCode, const BFDataGroupId &idDataGroup );
   SEVERITY validateClassCode( const DString &dstrClassCode, const BFDataGroupId &idDataGroup );
   SEVERITY validateEffectiveStopDate( const BFDataGroupId &idDataGroup );	
	SEVERITY validateDateAgainstCurrBusDate( const DString &dstrDate, const BFDataGroupId &idDataGroup );
	SEVERITY validateFeeRate( const DString &dstrFeeRate, const BFDataGroupId &idDataGroup );
    SEVERITY validateFeeCodeForClassEffHuddleRate( const BFDataGroupId &idDataGroup);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DailyTransactionsFee.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:30:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Feb 13 2004 14:03:56   VADEANUM
//PET859 FN23 - ADL - Additional FeeRate and Dates validations.
//
//   Rev 1.2   Feb 12 2004 13:31:44   VADEANUM
//PET859 FN23 - ADL - replaced FeePercent with FeeRate for correct display mask.
//
//   Rev 1.1   Feb 10 2004 16:52:28   VADEANUM
//PET 859 FN23 - ADL - first working version.
//
//   Rev 1.0   Jan 28 2004 14:07:02   popescu
//Initial revision.
*/
