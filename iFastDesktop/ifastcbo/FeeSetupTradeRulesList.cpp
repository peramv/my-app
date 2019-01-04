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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FeeSetupTradeRulesList.cpp
// ^AUTHOR : Serban Popescu 
// ^DATE   : October 2004
//
// ^CLASS    : FeeSetupTradeRulesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "feesetuptraderuleslist.hpp"

#include "feeparamconfiglist.hpp"
#include "splitcommission.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0309_req.hpp>
#include <ifastdataimpl\dse_dstc0309_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_SETUP_TRADE_RULES;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("FeeSetupTradeRulesList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Status;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
}

namespace CND
{
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;
}

namespace FEES
{
   extern const I_CHAR * XFER_OUT;
   extern const I_CHAR * XFER_IN;
   extern const I_CHAR * REDEMPTION;
   extern const I_CHAR * EXCHANGE;
}

//******************************************************************************
FeeSetupTradeRulesList::FeeSetupTradeRulesList  (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR  (CLASSNAME , NULL_STRING);
   setObjectAsList ();
}

//******************************************************************************
FeeSetupTradeRulesList::~FeeSetupTradeRulesList ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY FeeSetupTradeRulesList::init ( const DString &dstrTrack, 
                                        const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init"));

   BFData queryData (ifds::DSTC0309_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   AsyncReceiveData ( DSTC_REQUEST::FEE_SETUP_TRADE_RULES, 
                      queryData, 
                      ifds::DSTC0309_VW, 
                      DSTCRequestor (getSecurity (), true));
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void FeeSetupTradeRulesList::buildKey ( const DString &feeCode, 
                                        const DString &transType,
                                        DString &strKey)
{
   DString feeCode_ (feeCode),
      transType_ (transType);

   strKey = I_("FeeCode=") + feeCode_.stripLeading ('0').strip() + 
            I_(";TransType=") + transType_.strip().upperCase();
}

//******************************************************************************
void FeeSetupTradeRulesList::getStrKey  (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      buildKey ( data->getElementValue (ifds::TransFeeCode),
                 data->getElementValue (ifds::TransType),
                 strKey);
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//******************************************************************************
void FeeSetupTradeRulesList::getFeeCodes ( const DString &transType,
                                           const DString &redCode,
                                           const DString &depositType,
                                           const DString &indc,
                                           const DString &taxJuris,
                                           std::vector <DString> &feeCodes)
{
   DString strKey;
   
   feeCodes.clear(); //just to make sure

   BFObjIter bfIter (*this, BF::HOST);

   (const_cast <DString&>(redCode)).stripLeading ('0');
   (const_cast <DString&>(depositType)).stripLeading ('0');
   for (bfIter.begin(); !bfIter.end(); ++bfIter)
   {
      DString redCodeDecl,
         depositTypeDecl,
         taxJurisDecl,
         indcDecl, 
         transType_;
      
      bfIter.getObject ()->getField (ifds::TransType, transType_, BF::HOST, false);
      bfIter.getObject ()->getField (ifds::RedCodeDecl, redCodeDecl, BF::HOST, false);
      redCodeDecl.strip (); //to make sure we compare same strings
      bfIter.getObject ()->getField (ifds::DepTypeDecl, depositTypeDecl, BF::HOST, false);
      depositTypeDecl.strip (); //to make sure we compare same strings
      bfIter.getObject ()->getField (ifds::TaxJurisDecl, taxJurisDecl, BF::HOST, false);
      bfIter.getObject ()->getField (ifds::INDCDecl, indcDecl, BF::HOST, false);
      if ( (transType == transType_ || transType_.empty()) && //trans type means it applies for all trans types
           isCodeInList (redCode, redCodeDecl) &&
           isCodeInList (depositType, depositTypeDecl) &&
           isCodeInList (indc, indcDecl) &&
           isCodeInList (taxJuris, taxJurisDecl))
      {
         DString feeCode;
         
         bfIter.getObject ()->getField (ifds::TransFeeCode, feeCode, BF::HOST, false);
         feeCodes.push_back (feeCode);
      }
   }
//manually push those codes in, fees set-up does not support them
   DString commissionType;
   MgmtCoOptions *pMgmtCoOptions = NULL;

   if ( getMgmtCo().getMgmtCoOptions (pMgmtCoOptions) <= WARNING &&
        pMgmtCoOptions)
   {
      pMgmtCoOptions->getField (ifds::CommissionType, commissionType, BF::HOST, false);
   }
   if (DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
   {
      if (!commissionType.empty())
      {
         if (commissionType != I_("0")) //commission type one or two, split comm environment
         {
            feeCodes.push_back (FEES::XFER_IN);
            feeCodes.push_back (FEES::XFER_OUT);
         }
         else
         {
            feeCodes.push_back (FEES::EXCHANGE); //non-split environment
         }
      }
   }
   if (transType == TRADETYPE::REDEMPTION)
   {
      feeCodes.push_back (FEES::REDEMPTION);
   }
}

//******************************************************************************
bool FeeSetupTradeRulesList::canFeeBeOverridden ( const DString &feeCode,
                                                  const DString &transType)
{
   bool bCanFeeBeOverridden = true; //can be overidden always, as default
   DString strKey;

   buildKey (feeCode, transType, strKey);

   BFObjIter bfIter (*this, BF::HOST);
   if (bfIter.positionByKey (strKey))
   {
      DString override;
      
      bfIter.getObject ()->getField (ifds::TransFeeOverrideAllowed, override, BF::HOST, false);
      bCanFeeBeOverridden = override == I_("Y");
   }   
   return bCanFeeBeOverridden;
}

//******************************************************************************
SEVERITY FeeSetupTradeRulesList::doCreateObject ( const BFData &data, 
                                                  BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doCreateObject"));
   pObjOut = NULL;
   bool bCreateObject = true; //always set to create the object
//seems that the status checking is not needed anymore
//until this is final and confirmed, keep the code commented out
/*   FeeParamConfigList *pFeeParamConfigList = NULL;

   if ( getMgmtCo().getFeeParamConfigList (pFeeParamConfigList) <= WARNING &&
        pFeeParamConfigList
      )
   {
//perform an extra check if the fee code is found in fee param configuration
      DString feeCode,
         strKey;
      
      feeCode = data.getElementValue (ifds::TransFeeCode);
      feeCode.stripLeading ('0').strip();
      pFeeParamConfigList->buildKeyForSystemLevel (feeCode, strKey);

      BFObjIter bfIter (*pFeeParamConfigList, BF::HOST);

      if (bfIter.positionByKey (strKey))
      {
         DString status;

         bfIter.getObject ()->getField (ifds::Status, status, BF::HOST, false);
         bCreateObject = status != I_("0"); //0 - not applicable
      }
   }
*/
   if (bCreateObject)
   {
      pObjOut = new FeeSetupTradeRules (*this);
      dynamic_cast <FeeSetupTradeRules *>(pObjOut)->init (data);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
FeeSetupTradeRules::FeeSetupTradeRules (BFAbstractCBO &parent) : MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR  (CLASSNAME , NULL_STRING);
}

//******************************************************************************
SEVERITY FeeSetupTradeRules::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init"));
   attachDataObject (const_cast <BFData&> (data), false, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeSetupTradeRulesList.cpp-arc  $
// 
//    Rev 1.13   24 Jul 2008 12:00:48   popescu
// Incident - 1190617 - set all the data init calls to be asynch
// 
//    Rev 1.12   Mar 15 2005 15:40:20   aguilaam
// IN_260181: split commissions not applicable for ED's with deposittypes 9,10,18
// 
//    Rev 1.11   Jan 29 2005 16:34:44   popescu
// PTS 10038434, handling of  two new fees (114 and 115) existing in pending trades, part of aggregated orders
// 
//    Rev 1.10   Jan 23 2005 13:56:26   popescu
// PTS 10037346, made exchange available for the user
// 
//    Rev 1.9   Jan 12 2005 18:51:10   popescu
// PTS 10037339, allowed user to set Redemption Fee up
// 
//    Rev 1.8   Dec 09 2004 22:30:54   popescu
// PET 11717/06, fees and mod pending trades
// 
//    Rev 1.7   Dec 07 2004 21:20:20   popescu
// PET 1117/06, pending trades/fees fixes, add-ons
// 
//    Rev 1.6   Dec 02 2004 18:22:52   popescu
// PET 1117/06/56, trades processing/fees processing
// 
//    Rev 1.5   Dec 01 2004 15:44:40   popescu
// PET 1117/56 fees processing, calculate the discount rate
// 
//    Rev 1.4   Nov 17 2004 16:15:04   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.3   Nov 15 2004 15:03:40   popescu
// PET 1117/06, .NET synch changes
// 
//    Rev 1.2   Nov 14 2004 14:40:44   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Nov 09 2004 16:49:14   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 05 2004 21:20:14   popescu
// Initial revision.
// 
//    Rev 1.0   Oct 29 2004 20:27:36   popescu
// Initial revision.
*/