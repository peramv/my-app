//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : AMSDeltaAllocList.cpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : Jan 10, 2018
//
// ^CLASS    : AMSDeltaAllocList
// ^SUBCLASS :
//
//******************************************************************************
#include "stdafx.h"
#include "AMSDeltaAlloc.hpp"
#include "AMSDeltaAllocList.hpp"
#include <ifastdataimpl\dse_dstc0218_req.hpp>
#include <ifastdataimpl\dse_dstc0218_vw.hpp>
#include <ifastdataimpl\dse_dstc0483_req.hpp>
#include <ifastdataimpl\dse_dstc0483_vw.hpp>
#include <ifastdataimpl\dse_dstc0483_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_("AMSDeltaAllocList");
}

namespace CND
{
   extern const long ERR_WARNING_AMS_ALLOCATION_CHANGE;
   extern const long ERR_SUM_OF_DELTA_MUST_BE_0;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_FUND_ALLOC_LIST;
   extern CLASS_IMPORT const DSTCRequest AMS_DELTA_ALLOC_LIST;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   {ifds::AMSCode,BFCBO::NONE,0},
   {ifds::AccountNum,BFCBO::NONE,0},
   {ifds::EffectiveDate,BFCBO::NONE,0},
   {ifds::Status,BFCBO::NONE,0},
   {ifds::ProcessDate,BFCBO::NONE,0},
   {ifds::Username,BFCBO::NONE,0},
   {ifds::AMSDeltaRequestUUID,BFCBO::NONE,0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   {I_( "AMSDeltaAlloc" ),BFCBO::REQUIRED,0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );
//******************************************************************************
AMSDeltaAllocList::AMSDeltaAllocList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0483_REQ)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
   registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}

//******************************************************************************
AMSDeltaAllocList::~AMSDeltaAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AMSDeltaAllocList::initExisting(const DString& dstrTrack,
                                          const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,CLASSNAME,I_("initExisting"));
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSDeltaAllocList::init(const DString& dstrAmsCode, const DString& dstrEffectiveDate, const DString& dstrAccountNum, const DString& dstrAMSDeltaReqUUID, const DString& dstrTrack,const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,CLASSNAME,I_("init"));

   BFData *receivedData = new BFData(ifds::DSTC0483_VW);

   DString mgmtCoIdOut;
   _requestData.setElementValue(ifds::CompanyId,getMgmtCoId(mgmtCoIdOut));
   _requestData.setElementValue(ifds::Track,dstrTrack);
   _requestData.setElementValue(ifds::Activity,dstrPageName);
   _requestData.setElementValue(ifds::AMSDeltaRequestUUID,dstrAMSDeltaReqUUID);

   ReceiveData(DSTC_REQUEST::AMS_DELTA_ALLOC_LIST,_requestData,*receivedData,DSTCRequestor(getSecurity(),false,false));
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSDeltaAllocList::initNew(const BFDataGroupId& idDataGroup,
                                    bool bGetDefault,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,CLASSNAME,I_("initNew"));

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSDeltaAllocList::doCreateNewObject(BFCBO *&pBase,DString &strKey,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,CLASSNAME,I_("doCreateNewObject"));

   AMSDeltaAlloc *pAllocation = new AMSDeltaAlloc(*this);
   pAllocation->initNew(idDataGroup);
   pBase = pAllocation;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSDeltaAllocList::doCreateObject(const BFData &data,BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,CLASSNAME,I_("doCreateObject"));

   pObjOut = new AMSDeltaAlloc(*this);
   dynamic_cast<AMSDeltaAlloc*>(pObjOut)->initExisting(data);
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
void AMSDeltaAllocList::getTotalDeltaPrcnt(DString &strTotalDeltaPrcnt, const BFDataGroupId& idDataGroup, bool bFormatted)
{
   BigDecimal dTotalValue = 0;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strAllocDeltaVal;
      iter.getObject()->getField(ifds::AMSAllocDelta,strAllocDeltaVal,idDataGroup,bFormatted);
      BigDecimal dAllocValue = DSTCommonFunctions::convertToBigDecimal(strAllocDeltaVal.strip());
      dTotalValue += dAllocValue;
      ++iter;
   }
   strTotalDeltaPrcnt = dTotalValue.asDString();
   DSTCommonFunctions::formattedField(ifds::USDollar,2,strTotalDeltaPrcnt);
}

//******************************************************************************
SEVERITY AMSDeltaAllocList::doCopyCurrAlloc(DString dstrToFundNumber,DString dstrFundCode,DString dstrClassCode,DString dstrAllocPrcnt,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCopyCurrAlloc" ) );
   DString dstrKey,dstrAMSCode;
   getField(ifds::AMSCode,dstrAMSCode,idDataGroup);
   getStrKey(dstrKey);
   AMSDeltaAlloc *pAllocation = new AMSDeltaAlloc(*this);
   pAllocation->initNew(idDataGroup);
   pAllocation->setField(ifds::ToFundNumber,dstrToFundNumber,idDataGroup);
   pAllocation->setField(ifds::FundCode,dstrFundCode,idDataGroup);
   pAllocation->setField(ifds::ClassCode,dstrClassCode,idDataGroup);
   pAllocation->setField(ifds::AllocPercentage,dstrAllocPrcnt,idDataGroup);
   pAllocation->setField(ifds::AMSAllocDelta,I_("0"),idDataGroup);
   pAllocation->setField(ifds::Version,I_("0"),idDataGroup);
   setObject(pAllocation,dstrKey,OBJ_ACTIVITY_ADDED,idDataGroup);
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSDeltaAllocList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,CLASSNAME,I_("doValidateAll"));

   DString dstrTotDelta;
   BigDecimal dTotalPercent = 0;

   getTotalDeltaPrcnt(dstrTotDelta, idDataGroup);
   dTotalPercent = DSTCommonFunctions::convertToBigDecimal(dstrTotDelta);
   if(dTotalPercent != DSTCommonFunctions::convertToBigDecimal(I_("0")))
      ADDCONDITIONFROMFILE(CND::ERR_SUM_OF_DELTA_MUST_BE_0);

   return (GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AMSDeltaAllocList::doDeleteObject (const DString &strKey,const BFDataGroupId& idDataGroup,bool bIsObjectDestroyed)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION,CLASSNAME,I_("doDeleteObject"));
   
   return GETCURRENTHIGHESTSEVERITY();
}