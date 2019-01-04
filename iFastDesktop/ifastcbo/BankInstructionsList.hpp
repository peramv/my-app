#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : BankInstructionsList.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 2/9/01
//
// ^CLASS  : BankInstructionsList
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class BankInstructions;

class IFASTCBO_LINKAGE BankInstructionsList : public MFCanBFCbo, private boost::noncopyable
{
public:
static SEVERITY isInternationalWire ( const MFCanBFCbo &objCaller,
                                      const DString &strFundCode, 
                                      const DString &strClassCode, 
                                      const DString &strSettleCurrency, 
                                      const DString &strCountryCode, 
                                      bool &bInternationalWire)
{
   return NO_CONDITION; //kept so code can compile
};


public:
   // X-structors
   BankInstructionsList( BFAbstractCBO &parent);
   ~BankInstructionsList();
   // Initialize function
   SEVERITY init ( const DString &bankType, 
                   const BFDataGroupId &idDataGroup);
   SEVERITY initNew ( const DString &bankType, 
                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll ( const BFDataGroupId &idDataGroup, 
                                    long lValidateGroup);
   SEVERITY validateEFTRedemptionBanking (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup) ;
   SEVERITY validateEFTPurchaseBanking (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup) ;
   SEVERITY switchToAlternativeEFTRedemption (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup);
   SEVERITY switchToAlternativeEFTPurchase (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup);
   SEVERITY displayEFTWarning (const BankInstructions *pBankInstructionsToCheck, const BFDataGroupId &idDataGroup);


protected:
//to be used only by derived classes
   SEVERITY init ( BFData &requestData, 
                   const DString &dstrBankType, 
                   const DString &dstrTrack = I_("N"), 
                   const DString &dstrPageName = NULL_STRING);
   virtual SEVERITY doCreateObject ( const BFData &data, 
                                     BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject ( BFCBO* &pBase, 
                                        DString &strKey, 
                                        const BFDataGroupId &idDataGroup);
private:
   void validateCurrencyAccountUseCode (const BFDataGroupId &idDataGroup);
   SEVERITY doesDefaultEFTRedemptionExist (const BFDataGroupId &idDataGroup);
   SEVERITY doesDefaultEFTPurchaseExist (const BFDataGroupId &idDataGroup);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructionsList.hpp-arc  $
 * 
 *    Rev 1.19   Jan 31 2011 18:09:36   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.18   Feb 20 2008 09:50:06   jankovii
 * PET 2385 FN06 Bank Details upload.
 * 
 *    Rev 1.17   Sep 10 2006 17:58:38   popescu
 * STP 2192/12
 * 
 *    Rev 1.16   Jul 31 2006 15:33:30   ZHANGCEL
 * PET2192 FN11 -- MgmtCo Banking related changes
 * 
 *    Rev 1.15   Nov 04 2004 17:37:18   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.14   Oct 23 2003 17:51:32   FENGYONG
 * doValidateAll set to virtual
 * 
 *    Rev 1.13   May 31 2003 11:54:48   popescu
 * RRIF bank work
 * 
 *    Rev 1.12   May 27 2003 18:29:22   popescu
 * due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
 * 
 *    Rev 1.11   May 27 2003 13:14:06   popescu
 * RRIF Banking work
 * 
 *    Rev 1.10   May 23 2003 10:04:16   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.9   May 22 2003 14:12:00   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
//
//   Rev 1.15   Mar 21 2003 18:00:18   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.14   Oct 09 2002 23:54:04   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.13   Aug 29 2002 12:51:52   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.12   Jul 05 2002 11:51:20   KOVACSRO
//Added BankInstType()
//
//   Rev 1.11   Jun 28 2002 11:49:42   KOVACSRO
//Added resetIntWire().
//
//   Rev 1.10   Jun 07 2002 17:34:02   KOVACSRO
//International Wire modifications.
//
//   Rev 1.9   03 Jun 2002 15:14:48   KOVACSRO
//Added isInternationalWire()
//
//   Rev 1.8   24 May 2002 15:14:50   KOVACSRO
//Fund and Client bank.
//
//   Rev 1.7   22 May 2002 18:21:38   PURDYECH
//BFData Implementation
//
//   Rev 1.6   19 Mar 2002 13:15:12   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.5   Jul 04 2001 10:47:14   ZHANGCEL
//Sync up with 1.2.1.2
//
//   Rev 1.4   09 May 2001 14:35:56   HSUCHIN
//Sync up with SSB
//
//   Rev 1.3   03 May 2001 14:03:48   SMITHDAV
//Session management restructuring.
//
//   Rev 1.2   30 Mar 2001 17:09:18   BUZILAMI
//Systematic bank changes
//
//   Rev 1.1   07 Mar 2001 15:41:54   BUZILAMI
//Broker, Branch, SlsRep Bank Instructions changes
//
//   Rev 1.0   Feb 21 2001 16:01:18   BUZILAMI
//Initial revision.
//
 * 
 *
*/
