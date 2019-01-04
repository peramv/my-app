//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
//    ^FILE   : ClientBankInstructions.cpp
//    ^AUTHOR : Serban Popescu
//    ^DATE   : August, 2003
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ClientBankInstructions
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "ClientBankInstructions.hpp"
#include "ClientBankInstructionslist.hpp"
#include "paymentinstructions.hpp"

namespace 
{
   const I_CHAR * CLASSNAME = I_( "ClientBankInstructions" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PaymentFor;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId CurrencyOption;
   extern CLASS_IMPORT const BFTextFieldId TransType;
}


namespace CND
{  // Conditions used
}

namespace AcctUseCode
{
   extern const I_CHAR * const MANAGEMENT_COMPANY;
}

namespace PAYMENT_FOR
{
   extern const I_CHAR * COMMISSION;
}

namespace PAY_TO
{
   extern const I_CHAR * CLIENT;
}


const BANKFIELDMAPPINGINFO client_bankFieldMappingInfo[] = {
   //Distributors,              //bank instructions,        //is bank field
   //these fields will not be copied over to the payment instructions object
   {ifds::PaymentFor,           ifds::TransType,           false},
   {ifds::Currency,             ifds::BankAcctCurrency,    false},
   {ifds::ACHProcessor,         ifds::ACHProcessor,        false},
};

int client_bankFieldMappingInfo_size = 
   sizeof(client_bankFieldMappingInfo) / sizeof(_bankFieldMappingInfo);

//******************************************************************************
ClientBankInstructions::ClientBankInstructions( BFAbstractCBO &parent, 
                                                const DString &bankType): 
      BankInstructionsEx( parent, 
                          bankType, 
                          client_bankFieldMappingInfo, 
                          client_bankFieldMappingInfo_size)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
}

//******************************************************************************
ClientBankInstructions::~ClientBankInstructions()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY ClientBankInstructions::initNew (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   BankInstructionsEx::initNew (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
BFAbstractCBO *ClientBankInstructions::getParentCBO ()
{
   assert (getParent ());
   BFAbstractCBO * parentCBO = 
      ((dynamic_cast <ClientBankInstructionsList*> (getParent ()))->getPayInstructionsParentCBO ());

   return parentCBO ? parentCBO : getParent ()->getParent ();
}

//******************************************************************************
SEVERITY ClientBankInstructions::getParentProcessDate ( DString &processDate, 
                                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getParentProcessDate"));
   processDate = NULL_STRING;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ClientBankInstructions::getParentCurrency ( DString &currency,
                                                     DString &description,
                                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getParentCurrency"));

   currency = description = NULL_STRING;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ClientBankInstructions::doInitBeforeCloning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInitBeforeCloning"));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ClientBankInstructions::preInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("preInit"));

   BankInstructionsEx::preInit (idDataGroup);

   DString transType;

   getField (ifds::TransType, transType, idDataGroup, false);
   if (transType == PAYMENT_FOR::COMMISSION)
   {
      setFieldNoValidate (ifds::AcctUseCode, AcctUseCode::MANAGEMENT_COMPANY, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ClientBankInstructions::postInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("postInit"));

   BankInstructionsEx::postInit (idDataGroup);
   setFieldReadOnly (ifds::BankAcctCurrency, idDataGroup, false);
   setFieldReadOnly (ifds::EffectiveDate, idDataGroup, false);
   setFieldReadOnly (ifds::StopDate, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ClientBankInstructions.cpp-arc  $
// 
//    Rev 1.1   Sep 13 2006 19:10:42   popescu
// STP 2192/FN 13
// 
//    Rev 1.0   Sep 12 2006 10:55:36   popescu
// Initial revision.
// 
//    Rev 1.11   Sep 10 2006 17:58:50   popescu
// STP 2192/12
// 
//    Rev 1.10   Jul 31 2006 15:33:48   ZHANGCEL
// PET2192 FN11 -- MgmtCo Banking related changes
// 
//    Rev 1.9   Sep 29 2005 18:57:24   popescu
// Incident# 405610 - added new validation when a bank is cloned. User should not be able to copy a bank if the process date of the transaction (i.e. trade date, systematic effective date), is not between effective date and stop date of the bank instructions record. Also, the process date has to be in the last EFT bank instructions dates range.
// 
//    Rev 1.8   Nov 14 2004 14:30:54   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.7   Sep 23 2004 10:10:10   popescu
// PET 1094 FN4 - Activest Bank File Interface, remove file processor from shareholder banking
// 
//    Rev 1.6   Sep 09 2004 13:19:48   popescu
// PET 1094 FN4 - Activest Bank File Interface, before cloning a bank object copy the TransType from the object parent (i.e. Systematic, Distribution) so the file processor values can be retrieved. Made BankInstrucitonEx class pure virtual, so everybody should implement initialization before cloning.
// 
//    Rev 1.5   Feb 18 2004 18:01:06   popescu
// PTS 10027184; - moved the ownership of the payment instructions banking list at the payment instructions CBO level.
// - clean-up the work session every time user hits 'Search' on the Features Search Dialog
// - do not add payment instructions/ pay to entity records, when refreshing the respective CBO lists in DistributorRepository, always read them from back-end. Now, this is possible since the work session is cleaned-up all the time.
// - fixed crash that happens when a new record is added to the payment instructions bank list. The scenario to get this crash is: go to pay to entity screen, then click the 'instructions' button, modify an existing payment instructions record with bank information. Hit okay, commit the changes in the parent. Go back to the payment instructions (you will notice that the previous changes are not saved -  another issue that has been fixed with this ticket), and then click the Bank button. Add a new bank record. Desktop reports an internal error.
// - use new IFDSListCtrl, for the PayToEntity list and PaymentInstructions list.
// 
//    Rev 1.4   Feb 13 2004 18:32:28   popescu
// PTS 10027180, open the stop date and effective date fields for the user to update for broker/branch/sales rep banking.
// 
//    Rev 1.3   Feb 09 2004 11:04:42   WINNIE
// PTS 10026408 : Bank currency should be updatable if there no corresponding parent object (such as TradeBank parent is Trade and SystematicBank's parent is Systematic, bankcurrency of TradeBank and SystematicBank should be disable but Object such has Broker Bank, Client bank should have bankcurrency updatable as there is no corresponding parent)
// 
//    Rev 1.2   Jan 30 2004 15:04:44   popescu
// PTS 10026408, 
// Removed hard coding of the file processor for banking, for broker/branch/slsrep, systematic,distribution,trade,shareholder.
// Set the value of the file processor to NULL_STRING if there are no values from the back-end, 
// For banking and distributions set the file processor NOT required if there are no values at the back-end
// 
//    Rev 1.1   Oct 04 2003 15:58:56   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.0   Aug 17 2003 16:19:10   popescu
// Initial revision.
// 
 */