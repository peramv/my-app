//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : MgmtFee.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : MgmtFee - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtfee.hpp"

#include "funddetail.hpp"
#include "mfaccount.hpp"
#include "taxtyperule.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("MgmtFee");
}

namespace ifds
{
//management company options
//account fields
   extern CLASS_IMPORT const BFTextFieldId TaxType;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId MgtFeeElig;
}

namespace CND
{
   extern const long ERR_MGMT_FEE_NOT_ALLOWED_FOR_TAXTYPE;
   extern const long ERR_FUND_NOT_ELIGIBLE_FOR_MGMT_FEE;
   extern const long ERR_SUPP_CODE_NOT_ALLOWED_FOR_TRANS_TYPE;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const SUPPRESS;
} 

//******************************************************************************
MgmtFee::MgmtFee (BFAbstractCBO &parent) : Redemption (parent), Trade (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING
                     );
}


//******************************************************************************
MgmtFee::~MgmtFee ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY MgmtFee::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit")
                         );

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::MGMT_FEE, 
                        idDataGroup, 
                        false
                      );
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool MgmtFee::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
inline bool MgmtFee::areTaxRatesAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY MgmtFee::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues")
                          );
   Redemption::preInitWithDefaultValues (idDataGroup);

//set the following fields read only
   setFieldReadOnly (ifds::TradesPayType, idDataGroup, true);
   setFieldReadOnly (ifds::SuppressCode, idDataGroup, true);
   setFieldReadOnly (ifds::RedCode, idDataGroup, true);
   setFieldReadOnly (ifds::OrderType, idDataGroup, true);
   setFieldReadOnly (ifds::OrderSource, idDataGroup, true);
   setFieldReadOnly (ifds::AmtType, idDataGroup, true);
   setFieldReadOnly (ifds::DepositDate, idDataGroup, true);
   setFieldReadOnly (ifds::CashDate, idDataGroup, true);
   setFieldReadOnly (ifds::ExchRate, idDataGroup, true);
   setFieldReadOnly (ifds::SettleCurrency, idDataGroup, true);
   setFieldReadOnly (ifds::SettledBy, idDataGroup, true);
   setFieldReadOnly (ifds::SettleType, idDataGroup, true);
   setFieldReadOnly (ifds::SettleSource, idDataGroup, true);
   setFieldReadOnly (ifds::ExpGNSettle, idDataGroup, true);
   setFieldReadOnly (ifds::CertRequired, idDataGroup, true);
   setFieldReadOnly (ifds::AddrCode, idDataGroup, true);
   setFieldReadOnly (ifds::ProvSales, idDataGroup, true);
   setFieldReadOnly (ifds::LSIFCode, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void MgmtFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
//call base class
   Redemption::doInitWithDefaultValues (idDataGroup);
   
   setFieldNoValidate ( ifds::SuppressCode, I_("99"), idDataGroup, false, 
                        true, 
                        true
                      ); 
   setFieldNoValidate ( ifds::RedCode, I_("91"), idDataGroup, false, 
                        true, true
                      );
   setFieldNoValidate ( ifds::OrderType, I_("N"), idDataGroup, false, 
                        true, true
                      );
   setFieldNoValidate ( ifds::OrderSource, I_("D"), idDataGroup, false, 
                        true, true
                      );
   setFieldNoValidate ( ifds::MFPayment, I_("99"), idDataGroup, false, 
                        true, true
                      );

    setFieldValid (ifds::MFPayment, idDataGroup, false);
}


//******************************************************************************
SEVERITY MgmtFee::doValidateField ( const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup
                                   )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField")
                          );
   if (Redemption::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
	   if (idField == ifds::SuppressCode)
	   {
		   if (strValue == I_( "16" ))
		   {
// Suppress Code not allowed for Transaction Type.
			   ADDCONDITIONFROMFILE (CND::ERR_SUPP_CODE_NOT_ALLOWED_FOR_TRANS_TYPE);
		   }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtFee::transTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("transTypeRelatedChanges")
                          );
   //call the base class
   Redemption::transTypeRelatedChanges (idDataGroup);
   setFieldNoValidate ( ifds::TradesPayType, PAYTYPE::SUPPRESS, idDataGroup, 
                        false, false, true, 
                        false  //no related changes
                      );
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MgmtFee::payTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("payTypeRelatedChanges")
                         );

   //skip the base class Redemption 'logic'
   return Trade::payTypeRelatedChanges (idDataGroup);
}

//******************************************************************************
SEVERITY MgmtFee::canAccountTrade ( MFAccount *pMFAccount, 
                                    const BFDataGroupId &idDataGroup
                                   )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canTradeAccount")
                          );

   TaxTypeRule *pTaxTypeRule = NULL;
   if ( pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
   {
      if (!pTaxTypeRule->isValidRedCode (I_("91")))
      {
         ADDCONDITIONFROMFILE (CND::ERR_MGMT_FEE_NOT_ALLOWED_FOR_TAXTYPE);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MgmtFee::validateFundClass ( const DString &fundCode, 
                                      const DString &classCode, 
                                      const DString &accountNum, 
                                      const BFDataGroupId &idDataGroup
                                    )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass")
                         );
   if (Redemption::validateFundClass (fundCode, classCode, accountNum, idDataGroup) <= WARNING)
   {
      FundDetail *pFundDetail = NULL;
      if ( getWorkSession().getFundDetail (fundCode, classCode, idDataGroup, pFundDetail) && 
           pFundDetail
         )
      {
         DString mgmtFeeElig;

         pFundDetail->getField (ifds::MgtFeeElig, mgmtFeeElig, idDataGroup, false);
         mgmtFeeElig.strip();
         if (mgmtFeeElig != I_("Y"))
         {
            ADDCONDITIONFROMFILE (CND::ERR_FUND_NOT_ELIGIBLE_FOR_MGMT_FEE);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MgmtFee::fromFundClassRelatedChanges ( const DString &fundCode, 
                                                const DString &classCode, 
                                                const BFDataGroupId &idDataGroup
                                              )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fromFundClassRelatedChanges")
                         );
   if (Redemption::fromFundClassRelatedChanges (fundCode, classCode, idDataGroup) <= WARNING)
   {
//management fee transactions for LSIF funds will call the LSIF available units module, 
//to determine whether the user is able to place the trade. 
//However, the user should not be able to change the LSIF Clawback code, 
//therefore lock the corresponding field (PTS 10031126)
      setFieldReadOnly (ifds::LSIFCode, idDataGroup, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
inline SEVERITY MgmtFee::validateSettleType ( const DString &settleType,
                                               const BFDataGroupId &idDataGroup
                                             )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateSettleType")
                         );
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MgmtFee.cpp-arc  $
// 
//    Rev 1.29   15 Apr 2008 12:09:44   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.28   Nov 30 2007 16:07:14   jankovii
// IN 1098169 - Mgmt fee payment option.
// 
//    Rev 1.27   Aug 10 2007 14:11:32   jankovii
// PET 2360 FN14&FN19 - Management Fee.
// 
//    Rev 1.26   Jul 14 2005 15:27:56   porteanm
// PET1171 EUSD 1B - Req change - removed  validateEUSDBackDates().
// 
//    Rev 1.25   Jul 07 2005 11:40:12   porteanm
// PET1171 EUSD 1B - Added validateEUSDBackDates().
// 
//    Rev 1.24   Dec 21 2004 12:13:50   popescu
// PTS 10037026, fixed minor comp error
// 
//    Rev 1.23   Dec 21 2004 12:11:16   popescu
// PTS 10037026, Management fee transactions for LSIF funds will call the LSIF available units module, to determine whether the user is able to place the trade. However, the user should not be able to change the LSIF Clawback code, therefore Desktop locks the corresponding field (missed validation of PTS 10031126)
// 
//    Rev 1.22   Dec 07 2004 01:37:34   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.21   Nov 29 2004 20:30:22   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.20   Nov 14 2004 14:50:20   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.19   Nov 06 2004 00:42:08   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.6   Nov 04 2004 17:38:10   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.5   Nov 02 2004 19:19:26   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.4   Oct 28 2004 18:23:46   popescu
// PET 1117/06
// 
//    Rev 1.3   Oct 27 2004 11:26:50   popescu
// PET 1117/06
// 
//    Rev 1.2   Oct 22 2004 19:58:44   popescu
// PET 1117/06, work in progress...
// 
//    Rev 1.1   Oct 21 2004 06:29:02   popescu
// PET 1117/06 - Trade processing work in progress..
// 
//    Rev 1.0   Oct 01 2004 19:29:48   popescu
// Initial revision.
 * 
 *    Rev 1.566   Sep 21 2004 16:02:32   popescu
  * Initial revision.
// 
// 
*/
