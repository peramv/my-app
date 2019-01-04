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
// ^FILE   : DistributorRepository.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 3/6/01
//
// ^CLASS    : DistributorRepository
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

class DistributorBankInstructionsList;
class PayToEntityList;
class PaymentInstructionsList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DistributorRepository : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   DistributorRepository(BFAbstractCBO &parent);
   virtual ~DistributorRepository();

   // Initialize function
   SEVERITY init(
      const BFDataGroupId &idDataGroup = BF::HOST, 
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY getDistributorBankInstructionsList( const DString &dstrBroker, 
                                                const DString &dstrBranch, 
                                                const DString &dstrSlsRep, 
                                                DistributorBankInstructionsList *&pDistributorBankInstructionsList, 
                                                const BFDataGroupId &idDataGroup, 
                                                BFAbstractCBO *parent_ =NULL, 
                                                const DString &dstrTrack = I_("N"), 
                                                const DString &dstrPageName = NULL_STRING);

   SEVERITY getPayToEntityList( const DString &dstrBroker, 
		                          const DString &dstrSearchTypeMgmt,
                                PayToEntityList *&pPayToEntityList, 
                                const BFDataGroupId &idDataGroup, 
                                const DString &dstrTrack = I_("N"), 
                                const DString &dstrPageName = NULL_STRING);

   SEVERITY getPaymentInstructionsList( const DString &dstrBroker, 
                                        const DString &dstrBranch,
		                                  const DString &dstrSlsRep,
                                        const DString &dstrPaymentFor,
		                                  const DString &dstrSearchTypeMgmt,
		                                  PaymentInstructionsList *&pPaymentInstructionsList, 
                                        const BFDataGroupId &idDataGroup, 
                                        const DString &dstrTrack = I_("N"), 
                                        const DString &dstrPageName = NULL_STRING);
private:
   void buildKey ( const DString &dstrBroker, 
                   const DString &dstrBranch, 
                   const DString &dstrSlsRep,
                   DString &dstrKey);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DistributorRepository.hpp-arc  $
//
//   Rev 1.9   Sep 10 2006 17:59:04   popescu
//STP 2192/12
//
//   Rev 1.8   Jul 31 2006 15:35:16   ZHANGCEL
//PET2192 FN11 -- MgmtCo Banking related changes
//
//   Rev 1.7   Jul 27 2006 17:59:54   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.6   Nov 14 2004 14:31:02   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Feb 18 2004 18:01:14   popescu
//PTS 10027184; - moved the ownership of the payment instructions banking list at the payment instructions CBO level.
//- clean-up the work session every time user hits 'Search' on the Features Search Dialog
//- do not add payment instructions/ pay to entity records, when refreshing the respective CBO lists in DistributorRepository, always read them from back-end. Now, this is possible since the work session is cleaned-up all the time.
//- fixed crash that happens when a new record is added to the payment instructions bank list. The scenario to get this crash is: go to pay to entity screen, then click the 'instructions' button, modify an existing payment instructions record with bank information. Hit okay, commit the changes in the parent. Go back to the payment instructions (you will notice that the previous changes are not saved -  another issue that has been fixed with this ticket), and then click the Bank button. Add a new bank record. Desktop reports an internal error.
//- use new IFDSListCtrl, for the PayToEntity list and PaymentInstructions list.
//
//   Rev 1.4   Aug 17 2003 16:14:34   popescu
//When asking for DistributorBanks, payment instructions sends itself as the parent CBO
//
//   Rev 1.3   Jul 09 2003 21:56:52   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.2   Jul 01 2003 18:09:28   popescu
//Added the payment instruction dialog, process and CBO's, as well as the DistributorRepository builder
//
//   Rev 1.1   Jun 27 2003 18:13:32   popescu
//Pay To Entity feature, dialog, process and CBO
//
//   Rev 1.0   May 31 2003 12:00:48   popescu
//Initial revision.
//
 */
