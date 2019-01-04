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
// ^FILE   : AdminFee.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : AdminFee - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "adminfee.hpp"

#include "clientbankinstructionslist.hpp"
#include "bankinstructions.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("AdminFee");
}

namespace ifds
{
//management company option   
   extern CLASS_IMPORT const BFTextFieldId ACHAdminFee;
//subst sets
   extern CLASS_IMPORT const BFTextFieldId AdminFeePayType;
   extern CLASS_IMPORT const BFTextFieldId AdminFeeAmtType;
//banking
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const SUPPRESS;
   extern CLASS_IMPORT I_CHAR * const EFT;
}

namespace AcctUseCode
{
   extern const I_CHAR * const COMM_CLEAR;
}

namespace CND
{
   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_GUARANTEE_FEE_TRADE_NOT_ALLOWED;
}

//******************************************************************************
AdminFee::AdminFee (BFAbstractCBO &parent) : Redemption (parent), Trade (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
}


//******************************************************************************
AdminFee::~AdminFee ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY AdminFee::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit")
                          );

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::ADMIN_FEE, 
                        idDataGroup, 
                        false
                      );
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool AdminFee::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
inline bool AdminFee::areTaxRatesAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY AdminFee::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues")
                          );
   Redemption::preInitWithDefaultValues (idDataGroup);

   DString adminFeePayTypeSubstList;
   BFProperties *pBFPropertiesPPT = 
      getFieldProperties (ifds::AdminFeePayType, idDataGroup);

   if (pBFPropertiesPPT)
   {
      pBFPropertiesPPT->getAllSubstituteValues (adminFeePayTypeSubstList);

//Remove pay type 'E' from the selection list if 'ACHAdminFee' in view 149 is not equal to 'Y' (yes).
      if (!isACHApplicable (idDataGroup))
      {
         adminFeePayTypeSubstList = removeItemFromSubtList (adminFeePayTypeSubstList, PAYTYPE::EFT);
      }
      setFieldAllSubstituteValues (ifds::TradesPayType, idDataGroup, adminFeePayTypeSubstList);
   }
   setFieldSubstituteValues (ifds::AmtType, idDataGroup, ifds::AdminFeeAmtType);
   setFieldReadOnly (ifds::OrderType, idDataGroup, true); //lock it
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void AdminFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues")
                          );
//call base class
   Redemption::doInitWithDefaultValues (idDataGroup);

   setFieldNoValidate ( ifds::OrderType, I_("N"), idDataGroup, false,  // set Order type to "Direct"
                        true, true); 
   setFieldNoValidate ( ifds::GrossOrNet, I_("N"), idDataGroup, false, // set Gross/Net to Net
                        true, 
                        true); 
   setFieldNoValidate ( ifds::RedCode, NULL_STRING, idDataGroup, false, 
                        true, 
                        true);
   setFieldValid (ifds::Amount, idDataGroup, false);
}

//******************************************************************************
SEVERITY AdminFee::transTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("transTypeRelatedChanges")
                          );
   //call the base class
   Redemption::transTypeRelatedChanges (idDataGroup);

   if (!_bInitPending)
   {
      setFieldNoValidate ( ifds::TradesPayType, 
                           isACHApplicable (idDataGroup) ? PAYTYPE::EFT : PAYTYPE::SUPPRESS, 
                           idDataGroup, 
                           false, false, true, 
                           false  //no related changes
                        );
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY AdminFee::doInit (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   
   Redemption::doInit (data);
   setFieldValid (ifds::Amount, BF::HOST, false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
inline bool AdminFee::isACHApplicable (const BFDataGroupId &idDataGroup)
{
   DString achAdminFee;

   getWorkSession ().getOption ( ifds::ACHAdminFee, 
                                 achAdminFee, 
                                 idDataGroup,
                                 false);
   return achAdminFee == I_("Y");
}

//******************************************************************************
SEVERITY AdminFee::getDefaultBankInstructions ( BankInstructions *&pBankInstructions, 
                                                const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDefaultBankInstructions"));

   ClientBankInstructionsList *pClientBankInstructionsList = NULL;
   if (getWorkSession().
         getClientBankInstructionsList ( pClientBankInstructionsList, idDataGroup) <= WARNING && 
                                         pClientBankInstructionsList
                                       )
   {
      BFObjIter iter ( *pClientBankInstructionsList, 
                       idDataGroup
                     );

      DString currency;

      getField (ifds::SettleCurrency, currency, idDataGroup, false);
      if (!currency.empty())
      {
         while (!iter.end())
         {
            DString acctUseCode,
               bankAcctCurrency;

            iter.getObject()->getField ( ifds::BankAcctCurrency, 
                                         bankAcctCurrency, 
                                         idDataGroup,
                                         false
                                       );
            iter.getObject()->getField ( ifds::AcctUseCode, 
                                         acctUseCode, 
                                         idDataGroup,
                                         false
                                       );
            if (bankAcctCurrency == currency && 
                  AcctUseCode::COMM_CLEAR == acctUseCode)
            {
               pBankInstructions = 
                  dynamic_cast <BankInstructions*> (iter.getObject());
               break;
            }
            ++iter;
         }
      }
   }
   if (!pBankInstructions)
   {
//if not found look for the last eft bank used
      getLastEFTBankInstructions (pBankInstructions, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
inline SEVERITY AdminFee::withholdingTaxRelatedChanges (const BFDataGroupId& idDataGroup)  
{   
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("withholdingTaxRelatedChanges") 
                         ); 

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
inline SEVERITY AdminFee::validateSettleType ( const DString &settleType,
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
inline SEVERITY AdminFee::validateAmountAmtType (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                           CLASSNAME,
                           I_( "validateAmountAmtType" ) 
                         );
//this method is to check the maximum amount allowed. 
//not applicable to admin fee.

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY AdminFee::validateMinFromFundAmount ( const DString& amtType,
                                                const DString &amount,
                                                const BFDataGroupId &idDataGroup
                                              )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateMinFromFundAmount")
                         );
//empty for admin fee
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AdminFee::validateAmount ( const DString &amount,  
                                     const BFDataGroupId &idDataGroup 
                                   )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmount")
                         );

// amount cannot be zero
   double dec_amount = DSTCommonFunctions::convertToDouble (amount);

   if (dec_amount == 0)
   {
      ADDCONDITIONFROMFILE (CND::ERR_VALUE_CANNOT_BE_ZERO);
   }
   else
   {
      Redemption::validateAmount (amount, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AdminFee::validateAmountGrossNet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmountGrossNet") 
                         );

   // AdminFee does not allow 0 amount regardless gross or net.
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AdminFee::validateRedCode ( const DString &redCode, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRedCode"));

   DString strRedCode(redCode),
      strSrcOfFund;
   strRedCode.strip().upperCase();

   getField(ifds::SrcOfFund,strSrcOfFund,idDataGroup,false);
   strSrcOfFund.strip().upperCase();
   
   if(strRedCode == I_("GF") && strSrcOfFund == I_("11"))
   {
      // do some error code raising up here
      ADDCONDITIONFROMFILE (CND::ERR_GUARANTEE_FEE_TRADE_NOT_ALLOWED);
   }
   else
   {
      Redemption::validateRedCode (redCode, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AdminFee::validateSrcOfFund(const DString& strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateSrcOfFund"));

   DString strSrcOfFund(strValue),
      strRedCode;
   strSrcOfFund.strip().upperCase();
   getField(ifds::RedCode,strRedCode,idDataGroup,false);
   strRedCode.strip().upperCase();

   if(strRedCode == I_("GF") && strSrcOfFund == I_("11"))
   {
      // do some error code raising up here
      ADDCONDITIONFROMFILE (CND::ERR_GUARANTEE_FEE_TRADE_NOT_ALLOWED);
   }
   else
   {
      Redemption::validateSrcOfFund (strValue, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AdminFee.cpp-arc  $
// 
//    Rev 1.17   Mar 05 2012 11:41:52   dchatcha
// P0186484 FN05 - SEG Trade Processing.
// 
//    Rev 1.16   Jul 14 2005 15:28:46   porteanm
// PET1171 EUSD 1B - Req change - removed  validateEUSDBackDates().
// 
//    Rev 1.15   Jul 07 2005 11:39:10   porteanm
// PET1171 EUSD 1B - Added validateEUSDBackDates().
// 
//    Rev 1.14   Feb 25 2005 17:35:06   popescu
// PET 1117/06, admin fee should not allow the amount to be zero.
// 
//    Rev 1.13   Dec 23 2004 15:51:28   popescu
// PET 1117/06, AdminFee does not support allocation
// 
//    Rev 1.12   Dec 22 2004 10:51:06   popescu
// PTS 10036805, get the las eft transaction bank for AF's, synch-up from rel 58.1.1, branch 1.7.1.0
// 
//    Rev 1.11   Dec 07 2004 01:37:24   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.10   Nov 29 2004 20:30:10   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.9   Nov 27 2004 21:18:52   popescu
// PET 1117/06, trades processing
// 
//    Rev 1.8   Nov 06 2004 00:39:46   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.5   Nov 04 2004 17:37:02   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.4   Oct 28 2004 18:23:44   popescu
// PET 1117/06
// 
//    Rev 1.3   Oct 27 2004 11:26:46   popescu
// PET 1117/06
// 
//    Rev 1.2   Oct 22 2004 19:58:42   popescu
// PET 1117/06, work in progress...
// 
//    Rev 1.1   Oct 21 2004 06:28:58   popescu
// PET 1117/06 - Trade processing work in progress..
// 
//    Rev 1.0   Oct 01 2004 19:29:40   popescu
// Initial revision.
 * 
 *    Rev 1.566   Sep 21 2004 16:02:32   popescu
  * Initial revision.
// 
// 
*/
