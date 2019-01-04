#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE      : FundTransType.hpp
// ^AUTHOR    : Winnie Shiu
// ^DATE      : January 09, 2003
//
// ^CLASS     : FundTransType
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class FundLmtOverrideList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE FundTransType : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundTransType( BFAbstractCBO &parent );
   virtual ~FundTransType();

   SEVERITY init ( const DString &transType, 
                   const DString &fundCode, 
                   const DString &classCode, 
                   const BFDataGroupId &idDataGroup);
   SEVERITY getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList, 
                                     const BFDataGroupId &idDataGroup);
   SEVERITY getStopFlag ( const DSTCWorkSession &workSession,
                          const DString &accountNum, 
                          DString &stopFlag,
                          DString &stopSeverityCode,
                          const BFDataGroupId &idDataGroup);
   SEVERITY getMinAmount ( const DSTCWorkSession &workSession,
                           const DString &accountNum, 
                           DString &minAmount,
                           DString &minSeverityCode,
                           const BFDataGroupId &idDataGroup);
   SEVERITY getSubseqMinAmount ( const DSTCWorkSession &workSession,
                                 const DString &accountNum, 
                                 DString &subseqMinAmount,
                                 DString &subseqMinSeverityCode,
                                 const BFDataGroupId &idDataGroup);
   SEVERITY getMinUnits ( const DSTCWorkSession &workSession,
                          const DString &accountNum, 
                          DString &minUnits,
                          DString &minSeverityCode,
                          const BFDataGroupId &idDataGroup);
   SEVERITY getEntityOverride ( const DSTCWorkSession &workSession,
                                const DString &accountNum, 
                                DString &entityOverride,
                                DString &overrideSeverityCode,
                                const BFDataGroupId &idDataGroup);

   SEVERITY getStopAmtTradeFlag ( const DSTCWorkSession &workSession,
                                      const DString &accountNum, 
                                      DString &stopFlag,
                                      DString &stopSeverityCode,
                                      const BFDataGroupId &idDataGroup);   
   
private:
   DString _stopCode,
      _initMinCode,
      _subseqMinCode,
      _unitMinCode,
      _entityOverride,
      _stopAmtTradeCode;
   void setLimitationCode (const BFDataGroupId &idDataGroup);  
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundTransType.hpp-arc  $
//
//   Rev 1.13   Jul 20 2011 15:27:14   wp040027
//PET P0186065 - Aggregated Amount Orders via Swift- Implementation of Rule 36 on Fund
//
//   Rev 1.12   24 Jul 2007 20:13:12   popescu
//GAP 20 -22 AIM
//
//   Rev 1.11   Nov 14 2004 14:43:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.10   Nov 04 2004 17:37:48   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.9   Jul 08 2004 16:13:14   popescu
//PTS 10032006, check the trade minimum amount for to side funds, for rollovers transaction type
//
//   Rev 1.8   Jun 25 2004 19:05:20   popescu
//PTS 10031525, Fund limitation overrides issue
//
//   Rev 1.7   Jun 25 2004 16:38:26   popescu
//PST 10031525, fund limitation override issues
//
//   Rev 1.6   Apr 04 2003 10:18:34   popescu
//split commsion work
//
//   Rev 1.5   Mar 21 2003 19:50:52   PURDYECH
//Sync 1.3.1.0 back to trunk
//
//   Rev 1.3.1.0   Mar 21 2003 18:12:22   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Mar 11 2003 10:34:18   popescu
//Synch-up with Pre51
//
//   Rev 1.2.1.0   Mar 08 2003 12:49:04   WINNIE
//Bug fix : existing logic does not match corresponding limitation code to the corresponding limitation setting, it is likely to get the wrong record if there are multiple limitation under same fund/class but for different transtype and different limitation code.
//
//   Rev 1.2   Jan 30 2003 19:05:06   WINNIE
//Call by reference for input parameters of getStopFlag, override and minimum amount 
//
//   Rev 1.1   Jan 21 2003 18:32:36   WINNIE
//add method getMinAmountFlag for systematic minimum edit check; add register data in contractor to correct field assignment; pass fund and class for invoking fund limitation override CBO
//
//   Rev 1.0   Jan 12 2003 16:05:42   WINNIE
//Initial revision.
//
*/