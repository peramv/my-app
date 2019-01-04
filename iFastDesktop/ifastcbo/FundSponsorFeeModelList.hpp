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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundSponsorFeeModelList.hpp
// ^AUTHOR :  
// ^DATE   : July 21, 2004
//
// ^CLASS    : FundSponsorFeeModelList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <boost\utility.hpp>

// Forward references

class FundSponsorFeeModel;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif



class IFASTCBO_LINKAGE FundSponsorFeeModelList : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey ( DString &dstrKey,
                          const DString &feeModelCode, 
                          const DString &fundSponsor);
public:
// X-structors
   FundSponsorFeeModelList (BFAbstractCBO &parent);
   virtual ~FundSponsorFeeModelList();
// Initialize function
   SEVERITY init(	const BFDataGroupId &idDataGroup, 
                  const DString &dstrTrack = I_("N"),
                  const DString &dstrPageName = NULL_STRING,
                  const DString &dstrFeeModelCode = NULL_STRING, 
                  const DString &dstrFundSponsorCode = NULL_STRING,
                  bool allResults = false);
	SEVERITY initNew (const BFDataGroupId& idDataGroup);
   SEVERITY checkDuplicate ( const FundSponsorFeeModel *pFundSponsorFeeModel, 
                             const BFDataGroupId &idDataGroup);
   SEVERITY getFundSponsorFeeModel ( const DString &feeModelCode,
                                     const DString &fundSponsorCode,
                                     FundSponsorFeeModel *&pFundSponsorFeeModel, 
                              	    const BFDataGroupId &idDataGroup);
   SEVERITY getFundSponsorFeeModel ( const DString &feeModelCode,
                                     FundSponsorFeeModel *&pFundSponsorFeeModel, 
                              	    const BFDataGroupId &idDataGroup);
   SEVERITY getMore();
protected:
	virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	virtual SEVERITY doCreateNewObject ( BFCBO *&pBase, 
                                        DString &strKey, 
                                        const BFDataGroupId &idDataGroup);
   void getStrKey ( DString &strKey, 
                    const BFData *data);
   bool canDeleteObject (const DString &strKey, const BFDataGroupId &idDataGroup);
   
private:
   BFData *_pRequestData307;
   std::set <DString> _feeModelCodes;
};

