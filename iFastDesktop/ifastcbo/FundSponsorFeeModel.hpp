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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundSponsorFeeModel.hpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : FundSponsorFeeModel
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif
class FundSponsorFeeList;
class FeeModeList;

class IFASTCBO_LINKAGE FundSponsorFeeModel : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundSponsorFeeModel( BFAbstractCBO &parent );
   virtual ~FundSponsorFeeModel();

   SEVERITY init (const BFData &data);
   SEVERITY initNew (const BFDataGroupId &idDataGroup); //for creating new object
   SEVERITY getFundSponsorFeeList( FundSponsorFeeList *&pFundSponsorFeeList, 
	                                const BFDataGroupId& idDataGroup,
	                                bool inquireDatabase = true);
   SEVERITY doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup);
protected:
	SEVERITY doValidateField ( const BFFieldId &idField,
                              const DString &strValue,
                              const BFDataGroupId &idDataGroup);
   SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                    const BFDataGroupId &idDataGroup);
   void doInitWithDefaultValues( const BFDataGroupId &idDataGroup) ;

private:
   void setFieldsReadOnly (const BFDataGroupId &idDataGroup, bool bReadOnly); 
   SEVERITY validateOverlap (const BFDataGroupId &idDataGroup);
   SEVERITY validateEffectiveStopDate (const BFDataGroupId &idDataGroup);
   void validateModelCode ( const BFDataGroupId &idDataGroup, 
                            const DString &dstrValue);  
   void setSubstitutionList (const BFDataGroupId& idDataGroup);

  SEVERITY getFeeModelInfo (FeeModelList *&pFeeModelList, 
						    const DString &dstrFeeModelCode,
							const BFDataGroupId& idDataGroup);
};