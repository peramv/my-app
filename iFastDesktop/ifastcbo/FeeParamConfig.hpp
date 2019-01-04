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
// ^FILE   : FeeParamConfig.hpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : Feb. 28, 2002
//
// ^CLASS    : FeeParamConfig
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeParamConfig : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeParamConfig( BFAbstractCBO &parent );
   virtual ~FeeParamConfig();
   SEVERITY init( const BFData& data);

   bool isShareholderGroupApplicable();
   bool isBrokerApplicable();
   bool isBranchApplicable();
   bool isSalesRepApplicable();
   void getFundGroupType(DString &dstrGroupType);
   bool isFundClassApplicable();
   bool isFromFundClassApplicable();
   void getFeeTypeList(DString &dstrFeeTypeList);
   void getBaseOnList(DString &dstrBaseOnList);
   void getHowPaidList(DString &dstrHowPaidList);
   void getFundNamesList(DString &dstrFundList);
   void getMinMaxFrqList(DString &dstrMinMaxFrqList);
   void getOverrideList(DString &dstrOverrideList);
   bool isOnPWApplicable();
   bool isOnFWApplicable();
   bool isFamilyCodeApplicable();
	bool isValidateSysLevelApplicable()
	{
		return bValidHighLevel == true;
	}
   void getChargeOptionList(DString &dstrChargeOptionList);
	void getAppliedMethodList(DString &dstrAppliedMethodList);
	bool isAppliedMethodApplicable();
    bool allowNegativeRate();
    bool isEnvLvlFee();

private:
   bool bValidHighLevel;
};