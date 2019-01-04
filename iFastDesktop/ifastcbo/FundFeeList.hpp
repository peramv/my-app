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
// ^FILE   : FundFeeList.hpp
// ^AUTHOR :  Yingbao Li
// ^DATE   : Feb. 1, 2002
//
// ^CLASS    : FundFeeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundFeeList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FundFeeList( BFAbstractCBO &parent );
   virtual ~FundFeeList();
   // Initialize function
	SEVERITY init( const DString& dstrFeeCode,
					   const DString& dstrFundCode, 
					   const DString& dstrClassCode,
					   const DString& dstrCommGroupCode,
					   const DString& dstrEffectiveDate,
					   const DString& dstrAcctNum,
					   const DString& dstrValidateType,
					   const DString& dstrFeeId,
					   const DString& dstrFamilyCode = NULL_STRING,
					   const DString& dstrFundFrom = NULL_STRING,
					   const DString& dstrClassFrom = NULL_STRING,   
					   const DString& dstrStopDate = NULL_STRING,
					   const DString& dstrBrokerCode = NULL_STRING,
					   const DString& dstrShGroup = NULL_STRING,
					   const DString& dstrBranchCode = NULL_STRING,
					   const DString& dstrSalesRepCode = NULL_STRING,
					   const DString& dstrExclFeeCode = NULL_STRING,
                       const DString& dstrFeeModelCode = NULL_STRING,
                       const DString& dstrDistributionChannel = NULL_STRING,
					   const DString& dstrTrack = I_("N"),
					   const DString& dstrPageName = NULL_STRING
                );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundFeeList.hpp-arc  $
//
//   Rev 1.15   Oct 31 2011 10:09:00   kitticha
//PETP0186479 FN01 - IA Base Commission.
//
//   Rev 1.14   Nov 23 2004 12:29:52   popescu
//PET 1117/56, added fee model code as parameter for request
// 
**/