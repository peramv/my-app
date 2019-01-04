//******************************************************************************
//
// COPYRIGHT:
//
//  The computer systems, procedures, data bases and
//  programs created and maintained by International Financial Data Services,
//  are proprietary in nature and as such are confidential.
//  Any unauthorized use or disclosure of such information
//  may result in civil liabilities.
//
//  Copyright 2018 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DilutionValidation.cpp
// ^AUTHOR : Nuengruethai Wirojyuti
// ^DATE   : Jan 17, 2018
//
// ^CLASS    : DilutionValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "DilutionValidation.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0167_req.hpp>
#include <ifastdataimpl\dse_dstc0167_vw.hpp>

namespace DSTC_REQUEST
{
  extern CLASS_IMPORT const DSTCRequest TRADE_MIN_AMT_CHECK;
}

namespace ifds
{
  extern CLASS_IMPORT const BFTextFieldId DilutionLinkNum;
}

namespace CND
{
  extern const long ERR_DILUTION_LINK_ID_DOES_NOT_EXIST;
  extern const long WARN_DILUTION_LINK_ID_DOES_NOT_EXIST;
  extern const long ERR_DILUTION_LINK_ID_IS_ASSOCIATED_F50_TRADE;
  extern const long WARN_DILUTION_LINK_ID_IS_ASSOCIATED_F50_TRADE;
}

namespace
{
  const I_CHAR * const CLASSNAME                     = I_("DilutionValidation");
  const I_CHAR * const YES                           = I_("Y");
  const I_CHAR * const NO                            = I_("N");
  const I_CHAR * const EWI_ERROR                     = I_("E");
  const I_CHAR * const EWI_WARNING                   = I_("W");

  const long DILUTION_LINK_ID_DOES_NOT_EXIST         = 988;
  const long DILUTION_LINK_ID_IS_ASSOCIATED_F50_TRADE = 989;
}

//******************************************************************************
DilutionValidation::DilutionValidation(BFAbstractCBO &parent)
:MFCanBFCbo (parent),
 _dilutionLinkNum(NULL_STRING)
{
  TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
  setObjectAsList();
}

//******************************************************************************
DilutionValidation::~DilutionValidation()
{
  TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY DilutionValidation::init(const DString &dstrAccountNum, 
                                  const DString &dstrFundCode, 
                                  const DString &dstrClassCode, 
                                  const DString &dstrDilutionLinkNum)
{
  MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

  _dilutionLinkNum = dstrDilutionLinkNum;
  BFData queryData(ifds::DSTC0167_REQ);
  DString mgmtCoIdOut;
  bool ignoreDataNotFound = true;

  queryData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
  queryData.setElementValue(ifds::AccountNum, dstrAccountNum);
  queryData.setElementValue(ifds::FundCode, dstrFundCode);
  queryData.setElementValue(ifds::ClassCode, dstrClassCode);
  queryData.setElementValue(ifds::DilutionLinkNum, dstrDilutionLinkNum);

  queryData.setElementValue(ifds::TransType, NULL_STRING);
  queryData.setElementValue(ifds::EffectiveDate, NULL_STRING);
  queryData.setElementValue(ifds::Amount, NULL_STRING);
  queryData.setElementValue(ifds::AmountType, NULL_STRING);
  queryData.setElementValue(ifds::SettleCurrency, NULL_STRING);
  queryData.setElementValue(ifds::ExchRate, NULL_STRING);
  queryData.setElementValue(ifds::BrokerCode, NULL_STRING);
  queryData.setElementValue(ifds::BranchCode, NULL_STRING);
  queryData.setElementValue(ifds::SalesRepCode, NULL_STRING);
  queryData.setElementValue(ifds::AMSCode, NULL_STRING);
  queryData.setElementValue(ifds::AMSType, NULL_STRING);
  queryData.setElementValue(ifds::DepositType, NULL_STRING); 
  queryData.setElementValue(ifds::OrderType, NO);
  queryData.setElementValue(ifds::FullExchPrntToPrnt, NO);
  queryData.setElementValue(ifds::RDSPValidation, NO);
  queryData.setElementValue(ifds::GRRepayReason, NULL_STRING);
  queryData.setElementValue(ifds::RDSPPaymtDate, NULL_STRING);

  ReceiveData(DSTC_REQUEST::TRADE_MIN_AMT_CHECK, 
              queryData, 
              ifds::DSTC0167_VW,
              DSTCRequestor(getSecurity (), true, ignoreDataNotFound));

  return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionValidation::addConditions(DString &dstrDilutionNSM)
{
  MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("addConditions"));

  BFObjIter iter(*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
  iter.begin();
  DString errNum, severityCode;
  while(!iter.end())
  {
    iter.getObject()->getField(ifds::ErrNum, errNum, BF::HOST, false);
    iter.getObject()->getField(ifds::EWI, severityCode, BF::HOST, false);
    severityCode.upperCase ();
    
    long nErrNum = errNum.strip().stripLeading('0').convertToULong();
    if(errNum.empty())
      return GETCURRENTHIGHESTSEVERITY();
    
    switch(nErrNum)
    {
      case DILUTION_LINK_ID_DOES_NOT_EXIST:
      {
        if(severityCode == EWI_WARNING)
          ADDCONDITIONFROMFILE(CND::WARN_DILUTION_LINK_ID_DOES_NOT_EXIST);
        
        if (severityCode == EWI_ERROR)
          ADDCONDITIONFROMFILE(CND::ERR_DILUTION_LINK_ID_DOES_NOT_EXIST);
      }
      break;
      case DILUTION_LINK_ID_IS_ASSOCIATED_F50_TRADE:
      {
        if(dstrDilutionNSM == I_("03"))
        {
          if(severityCode == EWI_WARNING)
            ADDCONDITIONFROMFILE(CND::WARN_DILUTION_LINK_ID_IS_ASSOCIATED_F50_TRADE);
          
          if (severityCode == EWI_ERROR)
            ADDCONDITIONFROMFILE(CND::ERR_DILUTION_LINK_ID_IS_ASSOCIATED_F50_TRADE);
        }
      }
      break;
      default:
        assert(0);
    }
    ++iter;
  }
  return GETCURRENTHIGHESTSEVERITY();
}