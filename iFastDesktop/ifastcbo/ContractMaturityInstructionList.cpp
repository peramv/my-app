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
//    Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : ContractMaturityInstructionList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "ContractMaturityInstruction.hpp"
#include "ContractMaturityInstructionList.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0430_vw.hpp>
#include <ifastdataimpl\dse_dstc0430_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0430_req.hpp>

#include <ifastdataimpl\dse_dstc0105_vw.hpp>
#include <ifastdataimpl\dse_dstc0105_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CONTRACT_MATURITY_INSTR_INQUIRY;
}

namespace
{
	const I_CHAR * const CLASSNAME	= I_( "ContractMaturityInstructionList" );
	const I_CHAR * const PERCENT	= I_("P");
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId PUD1;
	extern CLASS_IMPORT const BFDecimalFieldId Amount;
}

namespace CND
{
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
	extern const long ERR_CONTR_MATURITY_RED_100_PERCENT; 
	extern const long WARN_CONTR_MATURITY_RED_100_PERCENT; 
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const CONTR_MATURITY_REDUMPTION_TO_BE_100_PERCENT;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
    //Field DD Id,				State Flags,					Group Flags 
	{ ifds::AccountNum,			BFCBO::NONE,						0},
	{ ifds::ContractType,		BFCBO::NONE,						0},
	{ ifds::ContractTypeId,		BFCBO::NONE,						0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
ContractMaturityInstructionList::ContractMaturityInstructionList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_requestData (ifds::DSTC0430_REQ)
, m_dstrAccountNum( I_("") )
, m_dstrCotAcctRid( I_("") )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList ();

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
ContractMaturityInstructionList::~ContractMaturityInstructionList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY ContractMaturityInstructionList::init (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ContractMaturityInstructionList::init( const DString& dstrAccountNum, 
												const DString& dstrContractType,
												const DString& dstrContractTypeId, 
												const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

	m_dstrAccountNum = dstrAccountNum;

	DString mgmtCoIdOut;
	m_requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
	m_requestData.setElementValue( ifds::ContractType, dstrContractType );
	m_requestData.setElementValue( ifds::ContractTypeId, dstrContractTypeId );
	m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	m_requestData.setElementValue( ifds::Track, I_("N") );

	ReceiveData (	DSTC_REQUEST::CONTRACT_MATURITY_INSTR_INQUIRY,
					m_requestData,
					ifds::DSTC0430_VW,
					DSTCRequestor(getSecurity()),
					false );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ContractMaturityInstructionList::setContractMatInstrAddFields ( const DString& dstrAccountNum, const DString& dstrCotAcctRid )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setContractMatInstrFields" ) );	

	m_dstrAccountNum = dstrAccountNum;
    m_dstrCotAcctRid = dstrCotAcctRid;
}

//******************************************************************************
void ContractMaturityInstructionList::getContractMatInstrAddFields ( DString& dstrAccountNum, DString& dstrCotAcctRid )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getContractMatInstrFields" ) );	

	dstrAccountNum = m_dstrAccountNum;
    dstrCotAcctRid = m_dstrCotAcctRid;
}

//******************************************************************************
void ContractMaturityInstructionList::getCotAcctRid ( DString& dstrCotAcctRid )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getCotAcctRid" ) );	

    dstrCotAcctRid = m_dstrCotAcctRid;
}

//*************************************************************************************
SEVERITY ContractMaturityInstructionList::initNew(	const DString& dstrAccountNum, 
													const DString& dstrCotAcctRid)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	setContractMatInstrAddFields(dstrAccountNum, dstrCotAcctRid);

	//setFieldReadOnly (ifds::PUD1, BF::HOST, false);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ContractMaturityInstructionList::doCreateNewObject( BFCBO*& pBase, DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

	ContractMaturityInstruction *pContractMaturityInstruction = new ContractMaturityInstruction (*this);
	pContractMaturityInstruction->initNew( idDataGroup );

	pBase = pContractMaturityInstruction;

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY ContractMaturityInstructionList::doCreateObject (const BFData& data, BFCBO*& pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new ContractMaturityInstruction(*this);
   ((ContractMaturityInstruction*)pObjOut)->init(const_cast<BFData&>(data) );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY ContractMaturityInstructionList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if (doMoreRecordsExist())
   {
      ReceiveData ( DSTC_REQUEST::CONTRACT_MATURITY_INSTR_INQUIRY, 
                    m_requestData, 
                    ifds::DSTC0430_VW, 
                    DSTCRequestor(getSecurity(), false), 
                    false);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY ContractMaturityInstructionList::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ));


   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY ContractMaturityInstructionList::doValidateAll (const BFDataGroupId& idDataGroup, 
														 long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

	bool bIsAmountTypePercentage = false;

	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	
	double dTotalPercentage = 0;
	while (!iter.end())
	{
		ContractMaturityInstruction *pContractMatInstr = dynamic_cast<ContractMaturityInstruction*>(iter.getObject());
		if (pContractMatInstr)
		{
			DString dstrPercentOrDollar;
			pContractMatInstr->getField( ifds::PUD1, dstrPercentOrDollar, idDataGroup);

			if (dstrPercentOrDollar == PERCENT)
			{
				bIsAmountTypePercentage = true;

				DString dstrPercent;
				pContractMatInstr->getField( ifds::Amount, dstrPercent, idDataGroup );
				dstrPercent.strip().stripAll(I_CHAR(','));

				I_CHAR *stopstring;
				double dPercentage = 0;
				dPercentage = wcstod(dstrPercent.c_str(), &stopstring); 

				dTotalPercentage += dPercentage;
			}
		}
		++iter;
	}

	if ( bIsAmountTypePercentage && (fabs(dTotalPercentage) != 100) )
	{ 
		getErrMsg ( IFASTERR::CONTR_MATURITY_REDUMPTION_TO_BE_100_PERCENT, 
						CND::ERR_CONTR_MATURITY_RED_100_PERCENT, 
						CND::WARN_CONTR_MATURITY_RED_100_PERCENT, 
						idDataGroup);
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ContractMaturityInstructionList::doValidateField ( const BFFieldId &idField, 
                                                  const DString &strValue, 
                                                  const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
	                       I_("doValidateField"));


   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractMaturityInstructionList.cpp-arc  $
// 
//    Rev 1.4   Jun 26 2012 14:15:52   wp040240
// IN#2948564 - Error condtions for Contract maturity Instrucitons screen added.
// 
//    Rev 1.3   Mar 16 2012 17:45:06   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.2   Mar 15 2012 19:32:50   wp040100
// IN 2874666 - P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.1   Mar 05 2012 20:35:56   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.0   Feb 21 2012 15:35:36   wp040100
// Initial revision.
// 
//
// 
*/
