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
// ^FILE   : ADLFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July 2004
//
// ^CLASS    : ADLFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "adlfee.hpp"

#include "funddetail.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ADLFee");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ADLevyFee;
   extern CLASS_IMPORT const BFTextFieldId ADLevyFeeTransType;
   extern CLASS_IMPORT const BFTextFieldId AntiDilutionCalc;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
   extern CLASS_IMPORT const BFTextFieldId UnitsCal;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * ADL;
}

//******************************************************************************
ADLFee::ADLFee (BFAbstractCBO &parent) : TransFeeCharge (parent, FEES::ADL)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
ADLFee::~ADLFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
bool ADLFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
   return hasFieldContextChanged (ifds::FromFund, idDataGroup) ||
          hasFieldContextChanged (ifds::FromClass, idDataGroup);
}

//******************************************************************************
bool ADLFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   DString adlApplicable;

   getWorkSession ().getOption ( ifds::ADLevyFee, 
                                 adlApplicable,
                                 BF::HOST,
                                 false);
   return adlApplicable == Y;
}

//******************************************************************************
bool ADLFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString adlTransTypeCodeList, 
		   transType;

	   getWorkSession ().getOption ( ifds::ADLevyFeeTransType, 
								     adlTransTypeCodeList, 
									 BF::HOST,
									 false);
	   
	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   return DSTCommonFunctions::codeInList (transType, adlTransTypeCodeList) && 
	          isApplicableForFund (idDataGroup);
   }
   return false;
}

//******************************************************************************
void ADLFee::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
   if (canBeInitialized (idDataGroup))
   {
      TransFeeCharge::doInitWithDefaultValues (idDataGroup);
      //per system default
      setFieldNoValidate (ifds::TradeFeeOption, I_("0"), idDataGroup, false); 
      //charge
      setFieldNoValidate (ifds::ChargeOption, I_("0"), idDataGroup, false); 
      //flat
      setFieldReadOnly (ifds::FeeType, idDataGroup, true);
      setFieldNoValidate ( ifds::FeeType, I_("1"), idDataGroup, false,
                           false, true, false); //percent
      setFieldNoValidate ( ifds::OrigFeeType, I_("1"), idDataGroup, false,
                           false, true, false); //percent
      setFeeDefault (idDataGroup);
   }
}

//******************************************************************************
SEVERITY ADLFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeDefault")
                         );
   setFieldNoValidate (ifds::FeeCharge, Y, idDataGroup, false, false, true, false); //Yes
   setFieldNoValidate ( ifds::FeeRate, charge2Rate (DString (Y)), idDataGroup, false, 
                        false, true, false);
   setFieldNoValidate ( ifds::OrigFeeRate, charge2Rate (DString (Y)), idDataGroup, false, 
                        false, true, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ADLFee::isApplicableForFund (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isApplicableForFund")
                         );
   bool bIsApplicable = false;
   
//retrieve the fund fields
   DString fromFund, 
      fromClass;

   getContext().getField (ifds::FromFund, fromFund, idDataGroup);
   getContext().getField (ifds::FromClass, fromClass, idDataGroup);

   FundDetail *pFundDetail = NULL;
   
   if ( !fromFund.empty() &&
        !fromClass.empty() &&
         getWorkSession().
            getFundDetail (fromFund, fromClass, idDataGroup, pFundDetail) && 
         pFundDetail)
   {
      DString unitsCal,
         antiDilutionCalc;

	   getWorkSession ().getOption ( ifds::AntiDilutionCalc, 
                                    antiDilutionCalc, 
                                    BF::HOST,
                                    false);
      pFundDetail->getField (ifds::UnitsCal, unitsCal, idDataGroup, false);
      bIsApplicable = DSTCommonFunctions::codeInList (unitsCal.strip().upperCase(), antiDilutionCalc.strip().upperCase());
   }
   return bIsApplicable;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ADLFee.cpp-arc  $
// 
//    Rev 1.13   03 Sep 2009 15:24:56   sibuhatm
// According to IN1824948, We have changed the logic to fullfiill lowercase and upper case issue in ADL Fee under Fees tab.
// 
//    Rev 1.12   Feb 28 2005 16:51:06   popescu
// PET 1117/56, call the base class's doInitwithDefaultValues
// 
//    Rev 1.11   Feb 22 2005 17:53:58   popescu
// PET 1117/56, change chargeoption initialization, to '0' from '1' (1 no longer means 'Charge')
// 
//    Rev 1.10   Dec 17 2004 17:39:40   popescu
// PET 1117/06, removed refresh method, no use for it.
// 
//    Rev 1.9   Dec 17 2004 17:36:34   popescu
// PET 1117/06, restrict the applicability of ADL Fee to funds for which the value of UnitsCal is part of AntiDilutionCalc generic control
// 
//    Rev 1.8   Dec 08 2004 22:08:10   popescu
// PET 1117/06, more fees
// 
//    Rev 1.7   Nov 17 2004 16:14:48   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.6   Nov 15 2004 16:22:18   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.5   Nov 09 2004 16:48:58   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.4   Nov 08 2004 12:31:04   popescu
// PET 1117/06 trade processing
// 
//    Rev 1.3   Nov 06 2004 00:39:38   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.2   Nov 05 2004 16:05:36   popescu
// PET 1117/06, TP
// 
//    Rev 1.1   Nov 04 2004 17:37:00   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 04 2004 11:03:26   popescu
// Initial revision.
// 
 */