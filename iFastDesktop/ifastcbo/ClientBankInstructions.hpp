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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : ClientBankInstructions.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : September, 2006
//
// ^CLASS     : ClientBankInstructions
// ^SUBCLASS  :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\bankinstructionsex.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ClientBankInstructions : public BankInstructionsEx
{
public:
   ClientBankInstructions ( BFAbstractCBO &parent, 
                            const DString &bankType);
   virtual ~ClientBankInstructions();
   SEVERITY initNew (const BFDataGroupId &idDataGroup);
   void setParentCBO (BFAbstractCBO *pParentCBO);
protected:
   virtual SEVERITY preInit (const BFDataGroupId& idDataGroup);
   virtual SEVERITY postInit (const BFDataGroupId& idDataGroup);
   virtual SEVERITY doInitBeforeCloning (const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentCurrency ( DString &currency,
                                        DString &description,
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY getParentProcessDate ( DString &processDate, 
                                           const BFDataGroupId &idDataGroup);
   virtual BFAbstractCBO * getParentCBO ();
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ClientBankInstructions.hpp-arc  $
//
//   Rev 1.0   Sep 12 2006 10:55:44   popescu
//Initial revision.
//
//   Rev 1.10   Sep 10 2006 17:58:56   popescu
//STP 2192/12
//
//   Rev 1.9   Jul 31 2006 15:34:06   ZHANGCEL
//PET2192 FN11 -- MgmtCo Banking related changes
//
//   Rev 1.8   Sep 29 2005 18:57:26   popescu
//Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
//
//   Rev 1.7   Nov 14 2004 14:30:56   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.6   Sep 23 2004 10:10:14   popescu
//PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
//
//   Rev 1.5   Sep 09 2004 13:19:50   popescu
//PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
//
//   Rev 1.4   Feb 18 2004 18:01:10   popescu
//PTS 10027184; - moved the ownership of the payment instructions banking list at the payment instructions CBO level.
//- clean-up the work session every time user hits 'Search' on the Features Search Dialog
//- do not add payment instructions/ pay to entity records, when refreshing the respective CBO lists in DistributorRepository, always read them from back-end. Now, this is possible since the work session is cleaned-up all the time.
//- fixed crash that happens when a new record is added to the payment instructions bank list. The scenario to get this crash is: go to pay to entity screen, then click the 'instructions' button, modify an existing payment instructions record with bank information. Hit okay, commit the changes in the parent. Go back to the payment instructions (you will notice that the previous changes are not saved -  another issue that has been fixed with this ticket), and then click the Bank button. Add a new bank record. Desktop reports an internal error.
//- use new IFDSListCtrl, for the PayToEntity list and PaymentInstructions list.
//
//   Rev 1.3   Feb 09 2004 11:05:06   WINNIE
//PTS 10026408 : Bank currency should be updatable if there no corresponding parent object (such as TradeBank parent is Trade and SystematicBank's parent is Systematic, bankcurrency of TradeBank and SystematicBank should be disable but Object such has Broker Bank, Client bank should have bankcurrency updatable as there is no corresponding parent)
//
//   Rev 1.2   Jan 30 2004 15:04:46   popescu
//PTS 10026408, 
//Removed hard coding of the file processor for banking, for broker/branch/slsrep, systematic,distribution,trade,shareholder.
//Set the value of the file processor to NULL_STRING if there are no values from the back-end, 
//For banking and distributions set the file processor NOT required if there are no values at the back-end
//
//   Rev 1.1   Oct 04 2003 15:58:58   popescu
//CIBC PET 809, FN 13;
//also cleaned-up BankSearch and BankList objects,
//replaced with FinancialInstitutionList
//
//   Rev 1.0   Aug 17 2003 16:19:12   popescu
//Initial revision.
//
 */