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
//    Copyright 2002 by International Financial, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAMSDeltaTrxnBuilder.cpp
// ^AUTHOR : Thanisorn S.
// ^DATE   : Jan 18,2018
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAMSDeltaTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcAMSDeltatrxnbuilder.hpp"
#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0484_req.hpp>
#include <ifastdataimpl\dse_dstc0484_vw.hpp>
#include <ifastdataimpl\dse_dstc0484_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0483_vwrepeat_record.hpp>
#include "AmsMstrInfo.hpp"
#include "AMSDeltaAllocList.hpp"
#include "AMSDeltaAlloc.hpp"
#include "AMSAcctLvl.hpp"

namespace DSTC_REQUEST
{
  extern CLASS_IMPORT const DSTCRequest AMS_DELTA_ALLOC_LIST_UPDATE;
}

namespace
{
  const I_CHAR* CLASSNAME = I_("DSTCAMSDeltaTrxnBuilder");
  const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
  const I_CHAR* MarketValueWeight = I_("M");
}

namespace ifds
{  
  extern CLASS_IMPORT const BFTextFieldId FundCode;
  extern CLASS_IMPORT const BFTextFieldId ClassCode;
  extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
  extern CLASS_IMPORT const BFTextFieldId TargetMixOption;
}

namespace KEYTYPES
{
  extern CLASS_IMPORT I_CHAR * const AMSCode;
}

const BFFieldId fieldsInAMSDeltaRequest[]=
{
  ifds::AMSCode,
  ifds::AccountNum,
  ifds::Status,
  ifds::AMSDeltaRequestUUID, 
};

static const int numFieldsInAMSDeltaRequest = sizeof( fieldsInAMSDeltaRequest ) / sizeof( BFFieldId );

//******************************************************************************
void DSTCAMSDeltaTrxnBuilder::buildTrxnKey( DString& strKey, AMSDeltaAllocList* pAMSDeltaAllocList )
{
  DString dstrAMSCode, dstrAcctNum;
  pAMSDeltaAllocList->getField(ifds::AMSCode, dstrAMSCode, BF::HOST, false);
  pAMSDeltaAllocList->getField(ifds::AccountNum, dstrAcctNum, BF::HOST, false);
  //build the key    
  addIDITagValue(strKey, TRXNTAG::AMSCODETAG, dstrAMSCode);
  addIDITagValue(strKey, TRXNTAG::ACCTTAG, dstrAcctNum);
}

//******************************************************************************
SEVERITY DSTCAMSDeltaTrxnBuilder::buildTransactions(DSTCWorkSession &workSession,
                                                    BFAbstractCBO* pObj,
                                                    HostTransactionContainer* pTrCont,
                                                    BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

  AmsMstrInfo* pAMSMstrInfo = dynamic_cast<AmsMstrInfo*>(pObj);
  AMSAcctLvl* pAMSAcctLvl = dynamic_cast<AMSAcctLvl*>(pObj);
  AMSDeltaAllocList* pAMSDeltaAllocList = NULL;
  DString dstrTargetMixOpt;

  if (pAMSMstrInfo)
  {
    pAMSMstrInfo->getAMSDeltaAllocList(pAMSDeltaAllocList,BF::HOST,false);
    pAMSMstrInfo->getField(ifds::TargetMixOption, dstrTargetMixOpt, BF::HOST, false);
  }
  else if(pAMSAcctLvl)
  {
    pAMSAcctLvl->getAMSDeltaAllocList(pAMSDeltaAllocList,BF::HOST,false);
	  pAMSAcctLvl->getField(ifds::TargetMixOption, dstrTargetMixOpt, BF::HOST, false);
  }
	  	  	  
  if(pAMSDeltaAllocList && dstrTargetMixOpt == MarketValueWeight)
  {
    DString currBusDate;
    workSession.getDateInHostFormat(currBusDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, BF::HOST);
    BFData* request = new BFData(ifds::DSTC0484_REQ);
    BFData* response = new BFData(ifds::DSTC0484_VW);
    DString mgmtCoId, dstrTrack, dstrActivity, dstr;
    workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
    request->setElementValue(ifds::CompanyId, mgmtCoId );
    request->setElementValue(ifds::Track, I_("N"), false, false);
    request->setElementValue(ifds::Activity, I_(""), false, false);  
      
    //populate fixed section.
    for(int i=0; i<=numFieldsInAMSDeltaRequest; i++)
    {
      pAMSDeltaAllocList->getField(fieldsInAMSDeltaRequest[i], dstr, BF::HOST);
      request->setElementValue(fieldsInAMSDeltaRequest[i], dstr, false, false);
    }  
		  
		//Effective date of AMS Delta is always current business date.
		request->setElementValue(ifds::EffectiveDate, currBusDate, false, false);

		//populate repeat section.
		int count = 0;
		BFFieldId fieldId;

		BFObjIter iter(*pAMSDeltaAllocList, BF::HOST, false, BFObjIter::ITERTYPE::ALL);   
		BFData dataRepeat(ifds::DSTC0484_REQRepeat_Record);          		  

    for(iter.begin(); !iter.end(); iter++)
    {
      AMSDeltaAlloc* pAMSDeltaAlloc = dynamic_cast<AMSDeltaAlloc*>(iter.getObject());
      DString fundCode, classCode, AMSAllocDelta, version, runMode, status;
			 
      pAMSDeltaAlloc->getField(ifds::Version, version, BF::HOST);
      pAMSDeltaAlloc->getField(ifds::AMSAllocDelta, AMSAllocDelta, BF::HOST, true);
      pAMSDeltaAlloc->getField(ifds::Status, status, BF::HOST);

      if (version == I_("0") && status == I_("M"))
        runMode = RUNMODE::ADDED;
      else if(version != I_("0") && status == I_("M"))
        runMode = RUNMODE::MODIFIED;
      else
        continue;

      pAMSDeltaAlloc->getField(ifds::FundCode, fundCode, BF::HOST, false);
      pAMSDeltaAlloc->getField(ifds::ClassCode, classCode, BF::HOST, false);
		 
      dataRepeat.setElementValue(ifds::RunMode, runMode, false, false);
      dataRepeat.setElementValue(ifds::FundCode, fundCode, false, false);
      dataRepeat.setElementValue(ifds::ClassCode, classCode, false, false);
      dataRepeat.setElementValue(ifds::AMSAllocDelta, AMSAllocDelta, false, false);
      request->addRepeat(dataRepeat);	
      ++count;
    }

		request->setElementValue(ifds::RepeatCount, DString::asString(count), false, false);
    if (count > 0)
    {
      DString dstrKeyTypes, strKey;
      buildTrxnKey( strKey, pAMSDeltaAllocList );
      JData *jdata = new JData( DSTC_REQUEST::AMS_DELTA_ALLOC_LIST_UPDATE, request, response );
      pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, dstrKeyTypes );
    }
  }
  return(GETCURRENTHIGHESTSEVERITY());   
}