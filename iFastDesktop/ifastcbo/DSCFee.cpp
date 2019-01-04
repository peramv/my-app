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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSCFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : DSCFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "dscfee.hpp"

#include "lsifcodeslist.hpp"
#include "mgmtco.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "supportedproductslist.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("DSCFee");
}

namespace ifds
{
//mgmtco fields
   extern CLASS_IMPORT const BFTextFieldId DSCOverride;
//fees fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
   extern CLASS_IMPORT const BFDecimalFieldId MinFee;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId OverrideDSCAllow;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * DSC;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
}

//******************************************************************************
DSCFee::DSCFee (BFAbstractCBO &parent, const DString &feeCode) : TransFeeRate (parent, feeCode)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
DSCFee::DSCFee (BFAbstractCBO &parent) : TransFeeRate (parent, FEES::DSC)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
DSCFee::~DSCFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY DSCFee::restore ( BFCBO &rpParent, 
                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("restore"));
   DString feeRate,
      dscOverrideCode;

   rpParent.getField (ifds::DSCOverrideAmt, feeRate, idDataGroup);
   getFormattedFee (idDataGroup, feeRate);
   rpParent.getField (ifds::DSCOverrideCode, dscOverrideCode, idDataGroup);
   setFieldNoValidate ( ifds::FeeRate, feeRate, idDataGroup, false, 
                        false, false, false);
   if (dscOverrideCode == I_("1")) //flat
   {
      setFieldNoValidate ( ifds::FeeType, I_("0"), idDataGroup, false, 
                           false, false, false);
   }
   else if (dscOverrideCode == I_("2")) //percent
   {
      setFieldNoValidate ( ifds::FeeType, I_("1"), idDataGroup, false, 
                           false, false, false);
   }
   if (dscOverrideCode == I_("0"))
   {
      setFieldNoValidate ( ifds::TradeFeeOption, I_("0"), idDataGroup, false, 
                           false, false, false); //charge as per default
   }
   else
   {
      setFieldNoValidate ( ifds::TradeFeeOption, I_("2"), idDataGroup, false, 
                           false, false, false); //override
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DSCFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   DString dscOverride;
   
   getWorkSession().getOption ( ifds::DSCOverride, 
                                dscOverride, 
                                BF::HOST, 
                                false);
   dscOverride.upperCase();
   return dscOverride == I_("Y");
}

//******************************************************************************
bool DSCFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   return (transType == TRADETYPE::REDEMPTION ||
		   transType == TRADETYPE::ROLLOVER) && 
		   /* hasFeeParams (idDataGroup) &&*/ //DSC has no FeeParm set up
		   isApplicableForFund (idDataGroup);
   }
   return false;
}

//******************************************************************************
bool DSCFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if any of these parameters change
   return hasFieldContextChanged (ifds::LSIFCode, idDataGroup) ||
          hasFieldContextChanged (ifds::FromFund, idDataGroup) ||
          hasFieldContextChanged (ifds::FromClass, idDataGroup) ||
          hasFieldContextChanged (ifds::Amount, idDataGroup);
}

//******************************************************************************
bool DSCFee::isApplicableForFund (const BFDataGroupId &idDataGroup)
{
   bool bIsApplicable = false;

   DString fundCode,
      classCode;
   FundDetail *pFundDetail = NULL;
   
   getContext().getField (ifds::FromFund, fundCode, idDataGroup);
   getContext().getField (ifds::FromClass, classCode, idDataGroup);
   
   if ( !fundCode.empty() &&
        !classCode.empty() &&
         getWorkSession().
            getFundDetail (fundCode, classCode, idDataGroup, pFundDetail) && 
         pFundDetail
      )
   {
      DString overrideDSCAllow;
      
      pFundDetail->getField (ifds::OverrideDSCAllow, overrideDSCAllow, idDataGroup, false);
      bIsApplicable = overrideDSCAllow == I_("Y");
      if (bIsApplicable) //check LSIF set-up
      {
         FundMasterList *pFundMasterList; 

         if ( getMgmtCo().getFundMasterList (pFundMasterList) && 
              pFundMasterList
            )
         {
//if fund is LSIF, check for the lsif code...
            if (pFundMasterList->isLSIFFund (fundCode))
            {
               SupportedProductsList *pSupportedProductsList = NULL;

               if ( getMgmtCo ().getSupportedProductsList (pSupportedProductsList) <= WARNING && 
                    pSupportedProductsList
                  )
               {
                  if (pSupportedProductsList->isLSIFProductActive ())
	               {
            //check the LSIF dscoverride code
                     DString lsifCode;
                     LSIFCodesList *pLSIFCodesList;

                     getContext().getField (ifds::LSIFCode, lsifCode, idDataGroup, false);
                     if (!lsifCode.empty())
                     {
                        if ( getMgmtCo ().getLSIFCodesList (pLSIFCodesList) <= WARNING &&
                             pLSIFCodesList
                           )
                        {
                           DString lsifDSCOverrideCode = pLSIFCodesList->getDSCOverrideFlag (lsifCode);

                           bIsApplicable = lsifDSCOverrideCode != I_("1");
                        }
                     }
	               }
               } //supports lsif products 
            } //is lsif fund
         } //fund master list
      } // fundDSCOverrideAllow  
   }
   return bIsApplicable;
}

//******************************************************************************
SEVERITY DSCFee::setFeeMinMax (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeMinMax"));
   DString maxFee;

   if (isFeeTypePercentage (idDataGroup))
   {
      maxFee = I_("100");
      setField (ifds::MinFee, I_("0"), idDataGroup, false);
   }
   else
   {
      getContext().getField (ifds::Amount, maxFee, idDataGroup);
   }
   setField (ifds::MaxFee, maxFee, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSCFee.cpp-arc  $
// 
//    Rev 1.7   Nov 27 2011 19:40:12   popescu
// INA Commission Work
// 
//    Rev 1.6   Mar 23 2005 11:36:14   popescu
// Incident 271383, fix restore from character base issue
// 
//    Rev 1.5   Mar 03 2005 08:13:26   popescu
// PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
// 
//    Rev 1.4   Feb 28 2005 11:29:00   popescu
// PET 1117/56, set the correct min/max values based on the fee types
// 
//    Rev 1.3   Feb 28 2005 09:04:18   popescu
// PET 1117/06, set the correct maximum for the fee; fee cannot be greater the trade amount
// 
//    Rev 1.2   Feb 26 2005 12:53:20   winnie
// PET 1117 FN56 : Fee Parm is not applicable to DSC Fee. Get fund and class from the value object for isApplicableForFund
// 
//    Rev 1.1   Dec 02 2004 20:59:20   popescu
// PET 1117/06, more fee fixes
// 
//    Rev 1.0   Nov 17 2004 15:56:56   popescu
// Initial revision.
// 
//    Rev 1.2   Nov 15 2004 16:22:32   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.0   Nov 10 2004 09:31:18   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 06 2004 00:35:04   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 04 2004 11:03:16   popescu
// Initial revision.
// 
 */