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
// ^FILE   : InvestmentHistoryList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "investmenthistory.hpp"
#include "investmenthistorylist.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0421_vw.hpp>
#include <ifastdataimpl\dse_dstc0421_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0421_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INVESTMENT_HISTORY_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME	= I_( "InvestmentHistoryList" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
}

namespace CND
{  
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_INVALID_INVESTMENT_NUMBER;
   extern const long ERR_INVALID_INVESTMENT_STATUS;
   extern const long WARN_INVALID_FUND_NUMBER;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                     State Flags,      Group Flags 
   { ifds::InvestmentHistoryFund,      BFCBO::REQUIRED,				0},
   { ifds::InvestmentHistoryClass,     BFCBO::REQUIRED,				0},
   { ifds::InvestmentHistorySearch,    BFCBO::REQUIRED,				0},
   { ifds::InvestmentHistoryNumber,    BFCBO::NONE,					0},
   { ifds::InvestmentHistoryStatus,    BFCBO::NONE,					0},
   { ifds::FromFundNumber,			   BFCBO::NONE,					0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
InvestmentHistoryList::InvestmentHistoryList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_requestData (ifds::DSTC0421_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList ();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
InvestmentHistoryList::~InvestmentHistoryList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY InvestmentHistoryList::init (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setFieldNoValidate (ifds::InvestmentHistorySearch, I_("ALL"), idDataGroup, false, true, true);

   setFieldRequired (ifds::InvestmentHistoryFund,		idDataGroup, true);
   setFieldRequired (ifds::InvestmentHistoryClass,		idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InvestmentHistoryList::init( const DString& dstrAccountNum, 
                                      const DString& dstrTransId, 
                                      const DString& dstrFund,
                                      const DString& dstrClass,
                                      const DString& dstrInvNum,
                                      const DString& dstrInvStatus,
                                      const DString& dstrSearchBy,
                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;

   if( !dstrFund.empty() && !dstrClass.empty() )
   {
		m_requestData.setElementValue( ifds::InputAcctNum, dstrAccountNum);
		m_requestData.setElementValue( ifds::TransId, dstrTransId);
		m_requestData.setElementValue( ifds::InvestmentHistoryFund, dstrFund);
		m_requestData.setElementValue( ifds::InvestmentHistoryClass, dstrClass );
		m_requestData.setElementValue( ifds::InvestmentHistoryNumber, dstrInvNum);
		m_requestData.setElementValue( ifds::InvestmentHistoryStatus, dstrInvStatus);
		m_requestData.setElementValue( ifds::InvestmentHistorySearch, dstrSearchBy );
		m_requestData.setElementValue( ifds::GrossNet, I_("N"));
		m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
		m_requestData.setElementValue( ifds::Track, I_("N") );

		ReceiveData (DSTC_REQUEST::INVESTMENT_HISTORY_INQUIRY, m_requestData, 
			ifds::DSTC0421_VW, DSTCRequestor(getSecurity(), false, true), false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
SEVERITY InvestmentHistoryList::doCreateObject (const BFData& data, 
                                                BFCBO*& pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new InvestmentHistory(*this);
   ((InvestmentHistory*)pObjOut)->init(const_cast<BFData&>(data) );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY InvestmentHistoryList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if (doMoreRecordsExist())
   {
      ReceiveData ( DSTC_REQUEST::INVESTMENT_HISTORY_INQUIRY, 
                    m_requestData, 
                    ifds::DSTC0421_VW, 
                    DSTCRequestor(getSecurity(), false), 
                    false);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY InvestmentHistoryList::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ));
   
	if ( idField == ifds::InvestmentHistoryFund || idField == ifds::InvestmentHistoryClass )
	{
		DString	dstrFund, dstrClass;
		getField (ifds::InvestmentHistoryFund, dstrFund, idDataGroup, false);
		getField (ifds::InvestmentHistoryClass, dstrClass, idDataGroup, false);

		if(!dstrFund.empty() && !dstrClass.empty() )
		{
			DString dstrFundNumber;
			getWorkSession().GetFundNumber(dstrFund, dstrClass, dstrFundNumber);
			setFieldNoValidate ( ifds::FromFundNumber, dstrFundNumber, idDataGroup, false, 
									true, 
									true, //notify
									false);
		}
	} 
	else if ( idField == ifds::InvestmentHistorySearch )
	{
		DString dstrInvSearch;
		getField(ifds::InvestmentHistorySearch, dstrInvSearch, idDataGroup, false);

		bool bInvNumber = false, bInvStatus = false; //By default values will be false, so need to check for dstrInvSearch == I_("ALL")
		if ( dstrInvSearch == I_("INVNUM") )
		{
			bInvNumber = true;
			bInvStatus = false;
		}
		else if ( dstrInvSearch == I_("INVSTAT") )
		{
			bInvStatus = true;
			bInvNumber = false;
		}

		setFieldRequired (ifds::InvestmentHistoryNumber,	idDataGroup, bInvNumber);
		setFieldValid (ifds::InvestmentHistoryNumber, idDataGroup, !bInvNumber);

		setFieldRequired (ifds::InvestmentHistoryStatus,	idDataGroup, bInvStatus);
		setFieldValid (ifds::InvestmentHistoryStatus, idDataGroup, !bInvStatus);
	}
	else if (idField == ifds::FromFundNumber)
	{
		DString dstrFundNumber;
		getField (ifds::FromFundNumber, dstrFundNumber, idDataGroup, false);

		if (!dstrFundNumber.empty())
		{
			DString dstrFundCode, dstrClassCode;
			if (getWorkSession ().GetFundClassCode (dstrFundNumber, dstrFundCode, dstrClassCode))
			{
				setField (ifds::InvestmentHistoryFund,   dstrFundCode, idDataGroup, false, true);
				setField (ifds::InvestmentHistoryClass, dstrClassCode, idDataGroup, false, true);

				setFieldValid (ifds::InvestmentHistoryFund,  idDataGroup, false);
				setFieldValid (ifds::InvestmentHistoryClass, idDataGroup, false);
			}
		}
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY InvestmentHistoryList::doValidateAll (const BFDataGroupId& idDataGroup, 
                                               long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InvestmentHistoryList::doValidateField ( const BFFieldId &idField, 
                                                  const DString &strValue, 
                                                  const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
	                       I_("doValidateField"));

   if (idField == ifds::InvestmentHistoryFund)
   {
      FundMasterList *pFundMasterList (NULL);
      if (!strValue.empty())
      {
         if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
              pFundMasterList)
         {
            if (!pFundMasterList->IsFundExist (strValue, idDataGroup))
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
            }
         }
      }
   }
   else if(idField == ifds::InvestmentHistoryClass)
   {
      DString dstrFund;
      getField(ifds::InvestmentHistoryFund, dstrFund, idDataGroup, false);

      FundDetail *pFundDetail = NULL;
	  if(!strValue.empty())
	  {
		if (!dstrFund.empty() && !getWorkSession().getFundDetail (  dstrFund,
																	strValue,
																	idDataGroup,
																	pFundDetail) ||
			!pFundDetail)
		{
			ADDCONDITIONFROMFILE (CND::ERR_INVALID_FUND_CLASS_CODES);
		}
	  }
   }
   else if(idField == ifds::InvestmentHistoryNumber)
   {
		DString dstrInvSearch;
		getField(ifds::InvestmentHistorySearch, dstrInvSearch, idDataGroup, false);

		if( strValue.empty() && dstrInvSearch == I_("INVNUM") )
		{
			ADDCONDITIONFROMFILE (CND::ERR_INVALID_INVESTMENT_NUMBER);
		}
   }
   else if(idField == ifds::InvestmentHistoryStatus)
   {
		DString dstrInvSearch;
		getField(ifds::InvestmentHistorySearch, dstrInvSearch, idDataGroup, false);

		if( strValue.empty() && dstrInvSearch == I_("INVSTAT") )
		{
			ADDCONDITIONFROMFILE (CND::ERR_INVALID_INVESTMENT_STATUS);
		}
   }
   else if (idField == ifds::FromFundNumber )
	{
		if (!strValue.empty())
		{
			DString dstrFundCode, dstrClassCode;
			if ( !getWorkSession().GetFundClassCode(strValue, dstrFundCode, dstrClassCode) )
			{
				ADDCONDITIONFROMFILE (CND::WARN_INVALID_FUND_NUMBER);
			}
		}
	}

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestmentHistoryList.cpp-arc  $
// 
//    Rev 1.13   May 14 2012 18:28:18   wp040100
// IN 2886441 - Included BayCom/Fund Number 
// 1. Cash Sweep Screen.
// 2. Maturity Interest Instructions Screen.
// 3. GI investment Histroy Screen.
// 
//    Rev 1.12   Mar 14 2012 09:55:16   if991250
// added default value (N) for GrossNet in vw 421 
// 
//    Rev 1.11   Jan 26 2012 20:30:04   wp040100
// IN 2817749 - P0186477 FN03 - GIA Investment History - Error Handling
// 
//    Rev 1.10   Jan 13 2012 10:47:26   wp040100
// P0186477/FN03 - GIA - Investment History Changes - Bug fixes.
// 
//    Rev 1.9   Dec 21 2011 17:56:00   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.8   Dec 19 2011 18:23:12   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.7   Dec 13 2011 10:20:30   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.6   Dec 01 2011 11:44:14   dchatcha
// P0186477/FN03 - GIA - Purchase, fix transid issue on calling to view 421.
// 
//    Rev 1.5   Nov 26 2011 16:40:26   wp040100
// P0186477/FN03 - GIA - Investment History Changes - Add Fund and Class validations.
// 
//    Rev 1.4   Nov 25 2011 17:40:58   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
*/
