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
// ^FILE   : EarlyRedemptionFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : EarlyRedemptionFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "earlyredemptionfee.hpp"

#include "mfaccount.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("EarlyRedemptionFee");
}

namespace ifds
{
//mgmtco options
   extern CLASS_IMPORT const BFTextFieldId EarlyPWFeeElig;
//fee fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
//other fields
   extern CLASS_IMPORT const BFTextFieldId WDFeeDefn;
   extern CLASS_IMPORT const BFTextFieldId ChargeERFee;
}

namespace CND
{  // Conditions used
   extern long const WARN_CHARGE_EARLY_REDEMPTION_FEE_ALLOWED;
}

namespace FEES
{
   extern const I_CHAR * EARLY_REDEMPTION;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
}

//******************************************************************************
EarlyRedemptionFee::EarlyRedemptionFee (BFAbstractCBO &parent) : TransFeeCharge (parent, FEES::EARLY_REDEMPTION)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
EarlyRedemptionFee::~EarlyRedemptionFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
bool EarlyRedemptionFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
   return hasFeeParamsContextChanged (idDataGroup);
}

//******************************************************************************
bool EarlyRedemptionFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   DString earlyPWFeeElig;

   getWorkSession ().getOption ( ifds::EarlyPWFeeElig, 
                                 earlyPWFeeElig, 
                                 BF::HOST, 
                                 false
                               );
   return earlyPWFeeElig == Y;
}

//******************************************************************************
bool EarlyRedemptionFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType,
		   fundCode,
		   classCode;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   getContext().getField (ifds::FromFund, fundCode, idDataGroup, false);
	   getContext().getField (ifds::FromClass, classCode, idDataGroup, false);
	   return  transType == TRADETYPE::REDEMPTION &&
		       ((hasFeeParams (idDataGroup) && !fundCode.empty () && !classCode.empty()) ||
		       (fundCode.empty () && classCode.empty())); //allocated redemptions 
   }
   return false;
}

//******************************************************************************
SEVERITY EarlyRedemptionFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeDefaults")
                         );
   DString accountNum;
   MFAccount *pMFAccount = NULL;

   getContext().getField (ifds::AccountNum, accountNum, idDataGroup, false);
   if ( getWorkSession ().getMFAccount ( idDataGroup, 
                                         accountNum, 
                                         pMFAccount
                                       ) <= WARNING && 
        pMFAccount
      )
   {
      DString chargeERFee;

      pMFAccount->getField (ifds::ChargeERFee, chargeERFee, idDataGroup, false);
      if (chargeERFee.empty())
      {
         chargeERFee = N;
      }
      setFieldNoValidate ( ifds::FeeCharge, chargeERFee, idDataGroup, false, 
                           false, true, false
                         );
      setFieldNoValidate ( ifds::FeeRate, charge2Rate (chargeERFee), idDataGroup, false, 
                           false, true, false
                         );
      setFieldNoValidate ( ifds::OrigFeeRate, charge2Rate (chargeERFee), idDataGroup, false, 
                           false, true, false
                         );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EarlyRedemptionFee::doValidateField ( const BFFieldId &idField, 
                                               const DString &strValue, 
                                               const BFDataGroupId &idDataGroup
                                             )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField")
                         );
   if (TransFeeCharge::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if (idField == ifds::FeeCharge)
      {
         if (strValue == N)
         {
//should raise the warning so user knows, that the early redemption can be charged
            ADDCONDITIONFROMFILE (CND::WARN_CHARGE_EARLY_REDEMPTION_FEE_ALLOWED);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EarlyRedemptionFee::restore ( BFCBO &rpParent, 
													const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("restore"));
   DString chargeSTTRFee;

   rpParent.getField (ifds::ChargeERSTTRFee, chargeSTTRFee, idDataGroup);

   setFieldNoValidate ( ifds::FeeCharge, chargeSTTRFee, idDataGroup, false, 
                        false, true, false
                        );
   setFieldNoValidate ( ifds::FeeRate, charge2Rate (chargeSTTRFee), idDataGroup, false, 
                        false, true, false
                     );
   setFieldNoValidate ( ifds::OrigFeeRate, charge2Rate (chargeSTTRFee), idDataGroup, false, 
                        false, true, false
                         );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EarlyRedemptionFee.cpp-arc  $
// 
//    Rev 1.8   Jan 13 2006 17:05:58   AGUILAAM
// IN 518397 - for rebook of trade that's not entered thru Desktop, get ChargeERSTTRFee from original trade instead of TransFee (it does not exist in this case) 
// 
//    Rev 1.7   Mar 13 2005 17:39:18   popescu
// PET 1117/56, fixed availability of ER and STTR fees
// 
//    Rev 1.6   Dec 08 2004 22:08:12   popescu
// PET 1117/06, more fees
// 
//    Rev 1.5   Nov 17 2004 16:14:54   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.4   Nov 15 2004 16:22:24   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.2   Nov 09 2004 16:49:06   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.1   Nov 06 2004 00:40:28   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.0   Nov 05 2004 17:06:00   popescu
// Initial Revision
// 
//    Rev 1.1   Nov 04 2004 17:37:00   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 04 2004 11:03:26   popescu
// Initial revision.
// 
 */