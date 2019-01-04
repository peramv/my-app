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
// ^FILE   : ManualForeignCapGainAllocAdjustment.cpp
// ^AUTHOR :  
// ^DATE   : //
// ^CLASS    : ManualForeignCapGainAllocAdjustment - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "manualforeigncapgainallocadjustment.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "mfaccountholdinglist.hpp"

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ManualTradesTransType;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
   extern CLASS_IMPORT const BFDataFieldProperties s_FldProp_USDollar;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const FOREIGN_CAP_GAIN_ALLOC_ADJUSTMENT;
}


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME      = I_ ("ManualForeignCapGainAllocAdjustment");
   const I_CHAR * const FC_TRANS_TYPE  = I_ ("FC");
}

namespace CND
{
   extern const long ERR_FOREIGN_CAP_GAIN_ALLOC_NOT_ALLOWED;
   extern const long ERR_FUND_UNIT_PRICE_NOT_AVAILABLE;
   extern const long ERR_ACCT_NO_HOLDINGS_FOR_FUND;
}

//******************************************************************************
ManualForeignCapGainAllocAdjustment::ManualForeignCapGainAllocAdjustment (BFAbstractCBO &parent) : ManualDividend (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
}

//******************************************************************************
ManualForeignCapGainAllocAdjustment::~ManualForeignCapGainAllocAdjustment ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY ManualForeignCapGainAllocAdjustment::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   setFieldSubstituteValues (ifds::TradesTransType, idDataGroup, ifds::ManualTradesTransType);

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::FOREIGN_CAP_GAIN_ALLOC_ADJUSTMENT, 
                        idDataGroup, 
                        false);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualForeignCapGainAllocAdjustment::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
//base class call   
   ManualDividend::preInitWithDefaultValues (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualForeignCapGainAllocAdjustment::setField ( const BFFieldId &idField, 
                                                         const DString &dstrValue,
                                                         const BFDataGroupId &idDataGroup, 
                                                         bool bFormatted, 
                                                         bool bSideEffect, 
                                                         bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setField"));
                           
   if( idField == ifds::Amount )
   {
      bFormatted = false;
   }

   ManualDividend::setField( idField,
                             dstrValue,
                             idDataGroup,
                             bFormatted,
                             bSideEffect,
                             bCheckCurrentValue);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void ManualForeignCapGainAllocAdjustment::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   ManualDividend::doInitWithDefaultValues (idDataGroup);

   setFieldReadOnly (ifds::AmtType, idDataGroup, false);
}

//******************************************************************************
SEVERITY ManualForeignCapGainAllocAdjustment::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   ManualDividend::doApplyRelatedChanges (idField, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualForeignCapGainAllocAdjustment::doValidateField ( const BFFieldId &idField, 
                                                                const DString &strValue, 
                                                                const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField"));

   if (ManualDividend::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY ManualForeignCapGainAllocAdjustment::validateFundClass (const DString &fundCode, 
                                                                 const DString &classCode, 
                                                                 const DString &accountNum, 
                                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"));

   if (!fundCode.empty() && !classCode.empty())
   {
      //if (isManualDividendAllowed (fundCode, classCode, idDataGroup))
      {
         validateEUSDBackdates (fundCode, classCode,	accountNum,	idDataGroup ); 

         MFAccountHoldingList *pMFAccountHoldingList = NULL;

         if (getAccountHoldings (pMFAccountHoldingList, idDataGroup) <= WARNING &&
             pMFAccountHoldingList)
         {
            if (pMFAccountHoldingList->isFundInHoldings ( const_cast <DString&>(fundCode), 
                                                          const_cast <DString&>(classCode), 
                                                          idDataGroup))
            {
               DString tradeDate;

               getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);

               double dUnitPrice = getUnitPrice (fundCode, 
                                                 classCode, 
                                                 tradeDate, 
                                                 tradeDate, 
                                                 idDataGroup, 
                                                 FC_TRANS_TYPE, // when we look for units trans type is FC
                                                 I_("N"),       //  PrevDatePressed
                                                 I_("N"));      //  NextDatePresed

               if (dUnitPrice == 0.0)
               {
                  // Unit price is not available for this fund.
                  ADDCONDITIONFROMFILE (CND::ERR_FUND_UNIT_PRICE_NOT_AVAILABLE);
               }
            }
            else
            {
               // Account has no holdings for this fund.
               ADDCONDITIONFROMFILE (CND::ERR_ACCT_NO_HOLDINGS_FOR_FUND); 
            }
         }
      }
      //else
      //{
      //   // Manual dividend posting for this fund is not allowed.
      //   ADDCONDITIONFROMFILE (CND::ERR_FOREIGN_CAP_GAIN_ALLOC_NOT_ALLOWED);
      //}
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualForeignCapGainAllocAdjustment::validateToFundClass ( const DString &toFund, 
                                                                    const DString &toClass, 
                                                                    const DString &accountNum, 
                                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToFundClass"));

   validateMasterActAMS(idDataGroup);
   validateToFundClassAgainstFundEligible(toFund, toClass, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualForeignCapGainAllocAdjustment::validateFromToFundClass ( const DString &fromFund,
                                                                        const DString &fromClass,
                                                                        const DString &toFund,
                                                                        const DString &toClass,
                                                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFromToFundClass"));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualForeignCapGainAllocAdjustment::validateNegativeAmount ( const DString &amount, 
                                                                       const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateNegativeAmount"));
//empty implementation we allow negative amounts
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
double ManualForeignCapGainAllocAdjustment::getFCUnitPrice( const DString &fundCode,
                                                            const DString &classCode,
                                                            const DString &fromDate,
                                                            const DString &toDate,
                                                            const BFDataGroupId &idDataGroup )
{
   double dUnitPrice = getUnitPrice( fundCode, 
                                     classCode, 
                                     fromDate, 
                                     toDate, 
                                     idDataGroup, 
                                     FC_TRANS_TYPE, // when we look for units trans type is FC
                                     I_("N"),       //  PrevDatePressed
                                     I_("N"));
                                     
   return dUnitPrice;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ManualForeignCapGainAllocAdjustment.cpp-arc  $
// 
//    Rev 1.2   17 Aug 2009 10:38:32   popescu
// IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop - revised the code a little bit
// 
//    Rev 1.1   Aug 17 2009 08:40:12   dchatcha
// IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop.
//
