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
// ^FILE   : FundBankInstructionsListRepository.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : FundBankInstructionsListRepository
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>
#include <ifastdataimpl\dse_dstc0052_req.hpp>

class FundBankInstructionsList;
class FundGroupBankInstructionsList;
class FundSponsorBankInstructionsList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundBankInstructionsListRepository : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FundBankInstructionsListRepository(BFAbstractCBO &parent);
   virtual ~FundBankInstructionsListRepository();

   // Initialize function
   SEVERITY init (const BFDataGroupId &idDataGroup = BF::HOST, 
                  const DString& dstrTrack = I_("N"), 
                  const DString& dstrPageName = NULL_STRING);
   SEVERITY getFundBankInstructionsList( const DString& dstrFundCode, 
                                         FundBankInstructionsList *&pFundBankInstructionsList, 
                                         const BFDataGroupId &idDataGroup, 
                                         const DString& dstrTrack = I_("N"), 
                                         const DString& dstrPageName = NULL_STRING);
   SEVERITY getFundBankInstructionsList( const DString& dstrFundCode, 
                                         const DString& dstrClassCode, 
                                         FundBankInstructionsList *&pFundBankInstructionsList, 
                                         const BFDataGroupId &idDataGroup, 
                                         const DString& dstrTrack = I_("N"), 
                                         const DString& dstrPageName = NULL_STRING);
   SEVERITY getFundGroupBankInstructionsList( const DString& dstrFundGroup, 
                                              FundGroupBankInstructionsList *&pFundGroupBankInstructionsList, 
                                              const BFDataGroupId &idDataGroup, 
                                              const DString& dstrTrack = I_("N"), 
                                              const DString& dstrPageName = NULL_STRING);
   SEVERITY getFundSponsorBankInstructionsList( const DString& dstrFundSponsor, 
                                                FundSponsorBankInstructionsList *&pFundSponsorBankInstructionsList, 
                                                const BFDataGroupId &idDataGroup, 
                                                const DString& dstrTrack = I_("N"), 
                                                const DString& dstrPageName = NULL_STRING);
private:
   void buildKey ( const DString& dstrFundCode, 
                   DString& dstrKey);
   void buildKey ( const DString& dstrFundCode, 
                   const DString& dstrClassCode, 
                   DString& dstrKey);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBankInstructionsListRepository.hpp-arc  $
//
//   Rev 1.4   Oct 18 2006 15:53:56   popescu
//PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
//
//   Rev 1.3   Nov 14 2004 14:41:28   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Sep 21 2004 13:31:10   HERNANDO
//PET1094 FN06 - Absatzmeldung Files enhancement.  Added getFundGroupBankInstructionsList.
//
//   Rev 1.1   Jun 09 2003 17:40:06   popescu
//Added support for fund and class search, still stopped at the Gui level, because it shouldn't be functional yet; do not know the id for the bank entity when seraching for bank using fund and class
//
//   Rev 1.0   May 31 2003 12:00:54   popescu
//Initial revision.
//
 */
