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
// ^FILE   : FeeParamConfigList.hpp
// ^AUTHOR :  Yingbao Li, May Lin
// ^DATE   : Feb.28, 2003
//
// ^CLASS    : FeeParamConfigList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

// Forward references


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class FeeParamConfig;

class IFASTCBO_LINKAGE FeeParamConfigList : public MFCanBFCbo, private boost::noncopyable
{
public:

   // X-structors
   FeeParamConfigList( BFAbstractCBO &parent );
   virtual ~FeeParamConfigList();
   // Initialize function
   SEVERITY init( const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING  );
	SEVERITY getFeeCodeList(DString& dstrFeeCodeList, const DString & Level);
   SEVERITY getFeeCodeList( DString &dstrFeeCodeList, const DString & Level, const DString & dstrFundGroupType );
   SEVERITY getFeeParamConfig(FeeParamConfig*& pFeeParamConfig, DString& dstrFeeCode, const BFDataGroupId& idDataGroup);
	void buildKeyForSystemLevel( const DString& dstrFeeCode,DString &strKey );
	void buildKeyForAccountLevel( const DString& dstrFeeCode,DString &strKey );
   void buildKeyForFundSponsorLevel( const DString& dstrFeeCode,DString &strKey );
   void buildKeyForFundBrokerLevel( const DString& dstrFeeCode,DString &strKey );

   bool getAllFeeCodeInTheList(DString& feeCodList );
protected:
	virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
	virtual void getStrKey(DString &strKey, const BFData* data=NULL);


private:


};

