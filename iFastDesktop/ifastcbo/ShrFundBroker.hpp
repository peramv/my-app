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
// ^FILE      : ShrFundBroker.hpp
// ^AUTHOR    : Monica Vadeanu
// ^DATE      : November, 2004
//
// ^CLASS     : ShrFundBroker
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

class IFASTCBO_LINKAGE ShrFundBroker : public MFCanBFCbo, private boost::noncopyable
{
public:
   ShrFundBroker (BFAbstractCBO &parent);
   virtual ~ShrFundBroker();

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
   // Validations	
   SEVERITY validateFundCode( const BFDataGroupId &idDataGroup, const DString &dstrFundCode );
   SEVERITY validateFundWKN( const BFDataGroupId &idDataGroup, const DString &dstrFundWKN );
   SEVERITY validateFundISIN( const BFDataGroupId &idDataGroup, const DString &dstrFundISIN );
   SEVERITY validateFundBrokerCode( const BFDataGroupId &idDataGroup, const DString &dstrFundBroker );
   bool isFundBrokerEligForFund( const BFDataGroupId& idDataGroup );

   // Setters
	SEVERITY getFundDetailInformation( const DString& dstrSearchType,
												  const DString& dstrFund,                                                                                                                          
												  const DString& dstrWKN,
                                      const DString& dstrISIN,
												  const BFDataGroupId &idDataGroup );
	SEVERITY setFundName( const BFDataGroupId &idDataGroup );
	SEVERITY setFundBrokerName( const BFDataGroupId &idDataGroup );   
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFundBroker.hpp-arc  $
//
//   Rev 1.2   Nov 28 2004 13:56:32   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support.
//
//   Rev 1.1   Nov 11 2004 16:38:12   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support - work in progress
//
//   Rev 1.0   Nov 04 2004 17:25:04   VADEANUM
//Initial revision.
//