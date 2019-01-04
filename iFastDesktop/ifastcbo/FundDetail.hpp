#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1
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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundDetail.hpp
// ^AUTHOR : Karen Jan
// ^DATE   : Dec 19, 2000
//
// ^CLASS    : FundDetail
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class DSTCWorkSession;
class FundToList;
class FeeInfoInquiry;
class FundTransTypeList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundDetail : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundDetail( BFAbstractCBO &parent );
   virtual ~FundDetail();
   SEVERITY init (const BFData &viewData);
   SEVERITY fundClassForPlanType ( const DString &dstrPlanType, 
                                    const BFDataGroupId &idDataGroup );
   bool IsFundValidAtDate ( const DString &effectiveDate, 
                            const BFDataGroupId &idDataGroup ); 
   void getFeeInfoInquiryField (const BFFieldId &idField, 
                                 DString &strValue, 
                                 const BFDataGroupId &idDataGroup, 
                                 bool formattedReturn);
   bool splitCommActive ( const DSTCWorkSession &workSession, 
                          const DString &dstrTransType, 
                          const BFDataGroupId &idDataGroup); 
   bool isFundSoftCapped(const BFDataGroupId &idDataGroup);
   SEVERITY getFundTransTypeList (FundTransTypeList *&pFundTransTypeList);
   bool isFundERISAProhibited (const BFDataGroupId &idDataGroup);
   SEVERITY commonInit ( const BFDataGroupId &idDataGroup );
   virtual void getFundIdValue ( const BFFieldId &idField, DString &strValue, const BFDataGroupId &idDataGroup, 
								   bool formattedReturn  = false  ) const;
   bool isAMSParentFund(const BFDataGroupId &idDataGroup);
   bool isAMSChildFund(const BFDataGroupId &idDataGroup);
   void getGrossNetDefault(const BFDataGroupId &idDataGroup, DString &dstrGrossNetDefault, DString& dstrFormattedValue);
   bool isSoftCapped(const DString& date, const BFDataGroupId &idDataGroup);
   bool hasFundSubCat(const DString &fundSubCat, const BFDataGroupId &idDataGroup);
   bool isCustomPayoutFund(const BFDataGroupId &idDataGroup);
   bool isPortfolioPayoutFund(const BFDataGroupId &idDataGroup);
   bool isAmtTypeValidForLoadType(const DSTCWorkSession &dstcWorkSession, const DString &amtType, const BFDataGroupId &idDataGroup);
   bool amountInventoryAppl(const BFDataGroupId &idDataGroup);

private:
   FundToList *_pFundToList;
   FeeInfoInquiry *_pFeeInfoInquiry;
   FundTransTypeList *_pFundTransTypeList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundDetail.hpp-arc  $
//
//   Rev 1.19   Jan 20 2012 15:40:30   wp040027
//P0188394_Performance Fees - Order Entry
//
//   Rev 1.18   23 Jul 2007 16:49:42   popescu
//PET 2360 - FN 20 - GAP 20 Soft cap functionality
//
//   Rev 1.17   Nov 18 2004 13:28:06   YINGBAOL
//PET1117: Perfermance Tunning
//
//   Rev 1.16   Nov 14 2004 14:41:54   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.15   Jun 25 2004 16:37:58   popescu
//PST 10031525, fund limitation override issues
//
//   Rev 1.14   Mar 21 2003 18:10:58   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.13   Jan 13 2003 14:32:24   WINNIE
//Add Stop flag methods with only the GroupID as parameters
//
//   Rev 1.12   Jan 12 2003 15:34:06   WINNIE
//Add new stopflag such as StopPAC,StopSWP and Stop Automatic Transfer in/out. These edit checks no longer share with same flag with Purchase, Redemption and Transfer in/out etc. Add new class FundTransTypeList, FundTransType to allow StopFlag override at TaxType, TaxJuris, ProvofResident, Acct Type and Acct Designation level. It allow flexibility of setting the severity to Error, Warning or Ignore
//
//   Rev 1.11   Oct 09 2002 23:54:32   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.10   Aug 29 2002 12:52:30   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.9   22 May 2002 18:21:00   PURDYECH
//BFData Implementation
//
//   Rev 1.8   19 Mar 2002 13:17:08   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.7   20 Feb 2002 17:58:42   WINNIE
//new method for each stopflag
//
//   Rev 1.6   Oct 29 2001 16:29:00   ZHANGCEL
//Added a new method: getFeeInfoInquiryField()
//
//   Rev 1.5   17 May 2001 10:44:28   HSUCHIN
//added DSTCWorkSession point to SplitCommActive function
//
//   Rev 1.4   09 May 2001 14:16:54   HSUCHIN
//Sync up with SSB
//
//   Rev 1.3   03 May 2001 14:04:12   SMITHDAV
//Session management restructuring.
//
//   Rev 1.2   Mar 22 2001 14:36:28   WINNIE
//new method to check if fund/class active
//
//   Rev 1.1   Mar 10 2001 15:14:36   WINNIE
//fund detail own the fundlist instead having master list : to improve performance for transfer/exchange
//
//   Rev 1.0   Jan 31 2001 11:24:14   JANKAREN
//Initial revision.

*/