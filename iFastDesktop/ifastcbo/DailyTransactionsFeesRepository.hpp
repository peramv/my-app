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
// ^FILE   : DailyTransactionsFeesRepository.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : DailyTransactionsFeesRepository
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>


class DailyTransactionsFeeList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DailyTransactionsFeesRepository : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   DailyTransactionsFeesRepository (BFAbstractCBO &parent);
   virtual ~DailyTransactionsFeesRepository();

   // Initialize function
   SEVERITY init (
      const BFDataGroupId &idDataGroup = BF::HOST, 
      const DString& dstrTrack = I_("N"), 
      const DString& dstrPageName = NULL_STRING);
//this method is used to search for all institutions
   SEVERITY getDailyTransactionsFeeList(
      const DString &recordType,
      const DString &feeCode,
      const DString &fundCode,
      const DString &classCode,
      DailyTransactionsFeeList *&pDailyTransactionsFeeList, 
      const BFDataGroupId &idDataGroup, 
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY getDailyTransactionsFeeList(
      const DString &recordType,
      const DString &feeCode,
      const DString &effectiveDate,
      DailyTransactionsFeeList *&pDailyTransactionsFeeList, 
      const BFDataGroupId &idDataGroup, 
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
private:
   void buildDTFKey (DString &dstrKey);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DailyTransactionsFeesRepository.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:30:14   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Jan 28 2004 14:07:08   popescu
//Initial revision.
//
//
 */
