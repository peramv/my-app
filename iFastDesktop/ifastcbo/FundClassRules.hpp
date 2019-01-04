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
//    Copyright 2003 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FundClassRules.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : January 8, 2003
//
// ^CLASS    : FundClassRules
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

class FundDetail;

class IFASTCBO_LINKAGE FundClassRules : public MFCanBFCbo, private boost::noncopyable
{
public:

   FundClassRules( BFAbstractCBO &parent );
   virtual ~FundClassRules();
   SEVERITY init(
      const BFFieldId& fundNumberId = ifds::NullFieldId, 
      const BFFieldId& fundCodeId = ifds::NullFieldId, 
      const BFFieldId& classCodeId = ifds::NullFieldId,
      const BFFieldId& effectiveDateId = ifds::NullFieldId);
	SEVERITY validateFundCode(const BFDataGroupId& idDataGroup);
	SEVERITY validateClassCode(const BFDataGroupId& idDataGroup);
	SEVERITY validateFundNumber(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundClass(const BFDataGroupId& idDataGroup)  ;
   void setFundClassCode(const BFDataGroupId& idDataGroup);
	void setFundNumber(const BFDataGroupId& idDataGroup);
private:
   SEVERITY getFundDetail(const DString& strFundCode, 
      const DString& strClassCode, FundDetail *&pFundDetail);
   BFFieldId FundNumber;
   BFFieldId FundCode;
   BFFieldId ClassCode;
   BFFieldId EffectiveDate;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundClassRules.hpp-arc  $
//
//   Rev 1.5   Nov 14 2004 14:41:48   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.4   Mar 21 2003 18:10:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 21 2003 10:18:08   popescu
//Fixed some compiling issues related to FeePram Base class
//
//   Rev 1.2   Jan 20 2003 15:43:50   popescu
//Checked in for unit testing the ProtectedFundSetup feature
//
//   Rev 1.1   Jan 16 2003 15:34:10   YINGBAOL
//change init
//
//   Rev 1.0   Jan 09 2003 10:06:54   YINGBAOL
//Initial Revision
//
/
 * 
 
*/