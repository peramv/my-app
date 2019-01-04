#include "stdafx.h"
#include "regdocumenttypelist.hpp"
#include "regdocumenttype.hpp"
#include "mfaccount.hpp"

#include <ifastdataimpl\dse_dstc0443_req.hpp>
#include <ifastdataimpl\dse_dstc0443_vw.hpp>

namespace
{
	const I_CHAR * const CLASSNAME             = I_ ("RegDocumentTypeList");
}

namespace ifds
{  
	extern CLASS_IMPORT const BFTextFieldId AcctType;
	extern CLASS_IMPORT const BFTextFieldId TaxType;
}

namespace DSTC_REQUEST 
{
	extern CLASS_IMPORT const DSTCRequest REG_DOCUMENT_TYPE;
}

RegDocumentTypeList::RegDocumentTypeList(BFAbstractCBO &parent):MFCanBFCbo(parent)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	setObjectAsList ();
}

//****************************************************************************
RegDocumentTypeList::~RegDocumentTypeList(void)
{
	TRACE_DESTRUCTOR(CLASSNAME);
}

//****************************************************************************
SEVERITY RegDocumentTypeList::init(const DString& dstrComplyRule, 
                                   const DString &dstrTrack,
                                   const DString &dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

	BFData queryData (ifds::DSTC0443_REQ);
	BFData *receivedData = new BFData (ifds::DSTC0443_VW);

	DString mgmtCoIdOut;
	queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	queryData.setElementValue (ifds::Track, dstrTrack);
	queryData.setElementValue (ifds::Activity, dstrPageName);
	queryData.setElementValue (ifds::ComplyRule, dstrComplyRule);

	if(ReceiveData(DSTC_REQUEST::REG_DOCUMENT_TYPE, 
					queryData, 
					*receivedData, 
					DSTCRequestor (getSecurity())) <= WARNING
	  )
	{ 
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//****************************************************************************
SEVERITY RegDocumentTypeList::init(const DString& dstrComplyRule,
                                   const DString& dstrAcctType,
                                   const DString& dstrTaxType, 
                                   const DString& dstrTaxJuris, 
								   const DString& dstrAcctDesignation, 
								   const DString& dstrBrokerCode, 
								   const DString& dstrInterCode, 
								   const DString& dstrEffectiveDate, 
                                   const DString &dstrTrack,
                                   const DString &dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

   BFData queryData (ifds::DSTC0443_REQ);
   BFData *receivedData = new BFData (ifds::DSTC0443_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue(ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue(ifds::Track, dstrTrack);
   queryData.setElementValue(ifds::Activity, dstrPageName);
   queryData.setElementValue(ifds::ComplyRule, dstrComplyRule);
   queryData.setElementValue(ifds::AcctType, dstrAcctType);
   queryData.setElementValue(ifds::TaxType, dstrTaxType);
   queryData.setElementValue(ifds::TaxJuris, dstrTaxJuris);
   queryData.setElementValue(ifds::AcctDesignation, dstrAcctDesignation);
   queryData.setElementValue(ifds::BrokerCode, dstrBrokerCode);
   queryData.setElementValue(ifds::InterCode, dstrInterCode);
   queryData.setElementValue(ifds::EffectiveDate, dstrEffectiveDate);
 
	if(ReceiveData(DSTC_REQUEST::REG_DOCUMENT_TYPE, 
					queryData, 
					*receivedData, 
					DSTCRequestor(getSecurity())) <= WARNING
	  )
	{
      

	}
	return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY RegDocumentTypeList::doCreateObject(const BFData &data, BFCBO *&pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doCreateObject"));

	RegDocumentType * pRegDocumentType = new RegDocumentType(*this);
	pRegDocumentType->init(data);
	pObjOut = pRegDocumentType;
   
	return GETCURRENTHIGHESTSEVERITY();
}
//****************************************************************************
DString RegDocumentTypeList::buildSubsitutionSet(const DString& dstrExcludeComplyRule)
{
	DString output;
	for(BFObjIter iter(*this, BF::HOST);
		!iter.end();
		++iter)
	{
		DString code, description, dstrDefaultDocComplyRule;
		iter.getObject()->getField(ifds::RegDocId, code, BF::HOST, false);
		iter.getObject()->getField(ifds::RegDocName, description, BF::HOST, false);
		iter.getObject()->getField(ifds::RegDocComplyRule, dstrDefaultDocComplyRule, BF::HOST, false);
		if(isCodeInList(dstrDefaultDocComplyRule, dstrExcludeComplyRule))
			continue;
		output += code + I_("=") + description + I_(";");
	}
   
	return output;
}
//*****************************************************************************
void RegDocumentTypeList::getStrKey(DString &strKey, const BFData *data)
{
	DString dstrRegDocId;
	data->getElementValue(ifds::RegDocId, dstrRegDocId);
	dstrRegDocId.strip();
	buildStrKey(strKey, dstrRegDocId);
}
//*****************************************************************************
void RegDocumentTypeList::buildStrKey(DString &strKey, DString dstrRegDocId)
{
	strKey = I_("RegDocumentType:Id=") + dstrRegDocId + I_(";");
}