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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : TaxExemptAuthorizationList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 13/07/2004
//
// ^CLASS    : TaxExemptAuthorizationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "TaxExemptAuthorization.hpp"
#include "TaxExemptAuthorizationlist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcworksession.hpp"
#include <ifastdataimpl\dse_dstc0301_vw.hpp>
#include <ifastdataimpl\dse_dstc0301_req.hpp>
#include <ifastdataimpl\dse_dstc0302_vw.hpp>
#include <ifastdataimpl\dse_dstc0302_req.hpp>
#include <bfutil\bfdate.hpp>

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                             //  Field DD Id,       State Flags,      Group Flags 
   {ifds::AccountNum, BFCBO::CALCULATED_FIELD,      0},    
};

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TAX_EXEMPT_AUTHORIZATION_LIST;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "TaxExemptAuthorizationList" );
   const I_CHAR * const NR301_NO = I_("NRNO");
   const I_CHAR * const NR301 = I_("NR");  
   const DString EXEMPT_SCOPE_FULL = I_("1");
   const DString EXEMPT_SCOPE_PARTIAL = I_("2");
   const DString EXEMPT_SCOPE_RATE_OVERRIDE = I_("3");
   const DString EXEMPT_LEVEL_LIST = I_( "01,02,03,04" );
}

namespace TRID
{
   extern const I_CHAR* TAXEXEMPTAUTHORIZATION;

}

namespace CND
{ // Conditions used
   extern const long ERR_DUPLICATE_RECORD;
   extern const long ERR_DATE_RANGE_OVERLAP;
   extern const long ERR_ONLY_ONE_ACTIVE_RECORD_NR301;
   extern const long ERR_ONLY_ONE_ACTIVE_RECORD_NR301_NO;
   extern const long ERR_ONLY_ONE_ACTIVE_RECORD_NR301_NO_AND_NR301;
   extern const long ERR_FULL_PARTIAL_EXEMPTION_SCOPE_EXIST_ACCT_FUND_CLASS;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId TaxExemptAuthorizationHeading;
   extern CLASS_IMPORT const BFTextFieldId ExemptLevelList;
}
static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
// Constructors
//******************************************************************************

TaxExemptAuthorizationList::TaxExemptAuthorizationList( BFAbstractCBO &parent ) : 
MFCanBFCbo( parent ), 
pMgmtCoOptions(NULL),
pMFAccount(NULL),
queryData(ifds::DSTC0301_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
   dstrAcctNum  = NULL_STRING;
}


//******************************************************************************

TaxExemptAuthorizationList::~TaxExemptAuthorizationList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY TaxExemptAuthorizationList::initNew( const DString& strAccountNumber )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   dstrAcctNum = strAccountNumber;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TaxExemptAuthorizationList::init( const BFDataGroupId& idDataGroup, 
                                 const DString& AccountNumber, 
                                 bool bViewCall, 
                                 const DString& dstrTrack,
                                 const DString& dstrPageName )                              
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );   

	dstrAcctNum = AccountNumber;
	// Get info for doValidateField() and SetDefault()
	//getInfoForVldandDft( idDataGroup);

	if( bViewCall )
	{
		//BFData queryData(ifds::DSTC0301_REQ);
		BFData *pResponseData = new BFData(ifds::DSTC0301_VW);
		DString mgmtCoIdOut;

		setFieldNoValidate (ifds::AccountNum, dstrAcctNum, idDataGroup, false );
		queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );       
		queryData.setElementValue( ifds::AccountNum, AccountNumber ); 
		queryData.setElementValue( ifds::Track, dstrTrack );
		queryData.setElementValue( ifds::Activity, dstrPageName );
		ReceiveData( DSTC_REQUEST::TAX_EXEMPT_AUTHORIZATION_LIST, queryData, *pResponseData, DSTCRequestor(getSecurity(), false), false );
			pResponseData->getElementValue( ifds::DeregAmtYrToDate, m_dstrDeregAmtYrToDate );
	}
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TaxExemptAuthorizationList::doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   TaxExemptAuthorization *pTaxExemptAuthorization = new TaxExemptAuthorization ( *this );

	pTaxExemptAuthorization->initNew( idDataGroup );

   pBase = pTaxExemptAuthorization;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TaxExemptAuthorizationList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   TaxExemptAuthorization *pTaxExemptAuthorization = new TaxExemptAuthorization ( *this );
   pObjOut = pTaxExemptAuthorization;

   pTaxExemptAuthorization->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY TaxExemptAuthorizationList:: doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DString dstrStartDate, dstrEndDate, dstrStartDate1, dstrEndDate1, dstrTaxExType, dstrTaxExType1, dstrTaxJurisCode, dstrTaxJurisCode1, dstrEntityId, dstrEntityId1;
   DString dstrTaxExemptId, dstrTaxExemptId1, dstrFundCode, dstrFundCode1, dstrClassCode, dstrClassCode1, dstrExemptionScope, dstrExemptionScope1;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFAbstractCBO *pBFCBO = NULL;
   BFAbstractCBO *pBFCBO1 = NULL;  

   bool bExemptLevelExists = getTaxExemptLevel(idDataGroup); // Domestic-01, International(except SBF)-02, SBF-01,04

   while( !iter.end() )
   {
      pBFCBO = iter.getObject();
      if( !iter.isDummy()  && pBFCBO )
      {
         pBFCBO->getField(ifds::EffectiveDate, dstrStartDate, idDataGroup);
         pBFCBO->getField(ifds::StopDate, dstrEndDate, idDataGroup);
		 pBFCBO->getField(ifds::TaxExType, dstrTaxExType, idDataGroup);
		 pBFCBO->getField(ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup);
		 pBFCBO->getField(ifds::EntityId, dstrEntityId, idDataGroup);
		 pBFCBO->getField(ifds::FundCode, dstrFundCode, idDataGroup);
		 pBFCBO->getField(ifds::ClassCode, dstrClassCode, idDataGroup);
		 pBFCBO->getField(ifds::ExemptionScope, dstrExemptionScope, idDataGroup);
		 dstrEntityId.stripLeading('0');

		// position to the next item
		iter1.positionByKey( iter.getStringKey() );
        if( !iter1.end() )++iter1;
		 					
         while( !iter1.end() )
         {
				pBFCBO1 = iter1.getObject();

				if ( !iter1.isDummy()  && pBFCBO1 )
				{
					pBFCBO1->getField(ifds::TaxExType, dstrTaxExType1, idDataGroup );
					pBFCBO1->getField(ifds::TaxJurisCode, dstrTaxJurisCode1, idDataGroup);
					pBFCBO1->getField(ifds::EntityId, dstrEntityId1, idDataGroup);
					pBFCBO1->getField(ifds::FundCode, dstrFundCode1, idDataGroup);
					pBFCBO1->getField(ifds::ClassCode, dstrClassCode1, idDataGroup);
					pBFCBO1->getField(ifds::EffectiveDate, dstrStartDate1, idDataGroup);
					pBFCBO1->getField(ifds::StopDate, dstrEndDate1, idDataGroup);
					pBFCBO1->getField(ifds::ExemptionScope, dstrExemptionScope1, idDataGroup);
					
					dstrEntityId1.stripLeading('0');			

					//Only 1 record of NR301 should be active.
					if ( (dstrTaxExType == dstrTaxExType1) && (dstrTaxExType == I_("NR") )
						&& DSTCommonFunctions::dateRangesOverlap (dstrStartDate, dstrEndDate, dstrStartDate1, dstrEndDate1) )
					{
						ADDCONDITIONFROMFILE( CND::ERR_ONLY_ONE_ACTIVE_RECORD_NR301 );
						return(GETCURRENTHIGHESTSEVERITY());
					}
					//Only 1 record of NR301_NO should be active.	
					else if ( (dstrTaxExType == dstrTaxExType1) && (dstrTaxExType == NR301_NO )
						&& DSTCommonFunctions::dateRangesOverlap (dstrStartDate, dstrEndDate, dstrStartDate1, dstrEndDate1) )
					{
						ADDCONDITIONFROMFILE( CND::ERR_ONLY_ONE_ACTIVE_RECORD_NR301_NO );
						return(GETCURRENTHIGHESTSEVERITY());
					}
					//Any NR301 and NR301_NO shoud not overlap each other.
					else if((dstrTaxExType == NR301 && dstrTaxExType1 == NR301_NO) ||
						    (dstrTaxExType == NR301_NO && dstrTaxExType1 == NR301))
					{
						if (DSTCommonFunctions::dateRangesOverlap (dstrStartDate, dstrEndDate, dstrStartDate1, dstrEndDate1)){
							ADDCONDITIONFROMFILE(CND::ERR_ONLY_ONE_ACTIVE_RECORD_NR301_NO_AND_NR301);
							return(GETCURRENTHIGHESTSEVERITY());
						}
					}

					if((dstrTaxExType == dstrTaxExType1) && (dstrTaxJurisCode == dstrTaxJurisCode1) 
						&& (dstrEntityId == dstrEntityId1) && (dstrFundCode == dstrFundCode1) && (dstrClassCode == dstrClassCode1)
						&& (dstrExemptionScope == dstrExemptionScope1) )
					{
			
						if( DSTCommonFunctions::CompareDates( dstrStartDate1, dstrEndDate1 ) // check only when date are valid
							 == DSTCommonFunctions::FIRST_EARLIER )
						{
							if( DSTCommonFunctions::dateRangesOverlap( dstrStartDate, dstrEndDate,
																		 dstrStartDate1, dstrEndDate1 ) )
							{
								DString strTemp;
								ADDCONDITIONFROMFILEIDI( CND::ERR_DATE_RANGE_OVERLAP, strTemp);
								return(GETCURRENTHIGHESTSEVERITY());
							}

							if( DSTCommonFunctions::CompareDates( dstrStartDate1, dstrStartDate ) 
								 == DSTCommonFunctions::EQUAL &&
								 DSTCommonFunctions::CompareDates( dstrEndDate1, dstrEndDate ) 
								 == DSTCommonFunctions::EQUAL)
							{
								ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_RECORD );
								return(GETCURRENTHIGHESTSEVERITY());
							}
						}
					}

					if (bExemptLevelExists && (dstrTaxExType == dstrTaxExType1))
					{
						if( DSTCommonFunctions::CompareDates( dstrStartDate1, dstrEndDate1 ) == DSTCommonFunctions::FIRST_EARLIER ) // check only when date are valid
						{
							if( DSTCommonFunctions::dateRangesOverlap( dstrStartDate, dstrEndDate, dstrStartDate1, dstrEndDate1 ) )
							{	
								bool bExemptionScopeExists = validateExemptionScope(dstrFundCode.strip(), dstrFundCode1.strip(), 
																				    dstrClassCode.strip(), dstrClassCode1.strip(), 
																					dstrExemptionScope.strip(), dstrExemptionScope1.strip());

								if (!bExemptionScopeExists) {
									ADDCONDITIONFROMFILE( CND::ERR_FULL_PARTIAL_EXEMPTION_SCOPE_EXIST_ACCT_FUND_CLASS );								
									return(GETCURRENTHIGHESTSEVERITY());
								}
							}							
						}
					}
				}
            ++iter1;
         }
      }
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool TaxExemptAuthorizationList::hasFullExemptScope(const DString &taxExType, 
													const DString &taxJurisCode,
													const DString &entityId,
													const DString &fundCode,
													const DString &classCode,
													const DString &startDate,
													const DString &endDate,
													const BFDataGroupId& idDataGroup)
{
			
	/*
		Public method to check if there is a full exemption scope in any level
		to be benefit for validation checking.
	*/
	BFObjIter iterSearch( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	TaxExemptAuthorization *pTaxExemptAuthorization = NULL;
	iterSearch.begin();

	while(!iterSearch.end())
	{
		DString dstrTaxExType, dstrTaxJurisCode, dstrEntityId, dstrFundCode, 
			    dstrClassCode, dstrExemptionScope, dstrStartDate, dstrEndDate;

		pTaxExemptAuthorization = dynamic_cast<TaxExemptAuthorization*> (iterSearch.getObject());
		pTaxExemptAuthorization->getField(ifds::TaxExType, dstrTaxExType, idDataGroup, false);
		pTaxExemptAuthorization->getField(ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup, false);
		pTaxExemptAuthorization->getField(ifds::EntityId, dstrEntityId, idDataGroup, false);
		pTaxExemptAuthorization->getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
		pTaxExemptAuthorization->getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
		pTaxExemptAuthorization->getField(ifds::ExemptionScope, dstrExemptionScope, idDataGroup, false);
		pTaxExemptAuthorization->getField(ifds::EffectiveDate, dstrStartDate, idDataGroup, false);
		pTaxExemptAuthorization->getField(ifds::StopDate, dstrEndDate, idDataGroup, false);

		dstrEntityId.stripLeading('0');

		if((dstrTaxExType == taxExType) && (dstrTaxJurisCode == taxJurisCode) 
			&& (dstrEntityId == entityId) && (dstrFundCode == fundCode) && (dstrClassCode == classCode))
		{
			if( DSTCommonFunctions::CompareDates( dstrStartDate, dstrEndDate ) // check only when date are valid
												  == DSTCommonFunctions::FIRST_EARLIER )
			{
				if( DSTCommonFunctions::dateRangesOverlap( dstrStartDate, dstrEndDate,
														   startDate, endDate ) 
					&& dstrExemptionScope == I_("1")) // Full
				{
					return true;
				}
			}
		}
		++iterSearch;
	}
	return false;
}
//******************************************************************************
SEVERITY TaxExemptAuthorizationList::getMore()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

	if( doMoreRecordsExist() )
	{
		const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
		BFData *pResponseData = new BFData(ifds::DSTC0301_VW);
		ReceiveData( DSTC_REQUEST::TAX_EXEMPT_AUTHORIZATION_LIST, queryData, *pResponseData, DSTCRequestor(getSecurity(), false));
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************
bool TaxExemptAuthorizationList::getTaxExemptLevel (const BFDataGroupId &idDataGroup)
{  
	DString dstrExemptLevelList = NULL_STRING;
	bool bExemptLevelExists = false;	  

	getWorkSession().getOption (ifds::ExemptLevelList, dstrExemptLevelList, idDataGroup, false); // AcctTaxExempt generic control	
	dstrExemptLevelList.strip();	   

	do
	{	
		DString::size_type pos = 0;
		DString exemptLevel_;

		EXTRACT_VALUE(dstrExemptLevelList, exemptLevel_)
			if (DSTCommonFunctions::codeInList( exemptLevel_, EXEMPT_LEVEL_LIST))
			{				  			
				bExemptLevelExists = true;
				CHOP_STRING (dstrExemptLevelList)
				break;
			} 
			CHOP_STRING (dstrExemptLevelList)				
	}
	while (dstrExemptLevelList != NULL_STRING);

	return (bExemptLevelExists);	
}

//**********************************************************************************
bool TaxExemptAuthorizationList::validateExemptionScope(const DString &fundCode, 
														const DString &fundCode1, 
														const DString &classCode, 
														const DString &classCode1, 
														const DString &exemptionScope, 
														const DString &exemptionScope1) 
{			
	bool bAccountLevel = (fundCode.empty() && classCode.empty()) ? true : false;
	bool bAccountLevel1 = (fundCode1.empty() && classCode1.empty()) ? true : false;
	bool bSameFundClass = (fundCode == fundCode1 && classCode == classCode1) ? true : false;
	bool bPartialAndRateOverride = ((exemptionScope == EXEMPT_SCOPE_RATE_OVERRIDE && exemptionScope1 == EXEMPT_SCOPE_PARTIAL) ||
								    (exemptionScope == EXEMPT_SCOPE_PARTIAL && exemptionScope1 == EXEMPT_SCOPE_RATE_OVERRIDE)) ? true : false;

	// account/entity level only - Partial, Rate Override, or
	// account fund class level only - different fund & class or Partial, Rate Override for same fund & class
	if ( (bAccountLevel && bAccountLevel1 && bPartialAndRateOverride) ||
		 (!bAccountLevel && !bAccountLevel1 && (!bSameFundClass || (bSameFundClass && bPartialAndRateOverride))) ) 
	{				
			return true;					
	} 	

	return false;		

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxExemptAuthorizationList.cpp-arc  $
// 
//    Rev 1.6   Feb 07 2012 22:25:48   wp040100
// P0194640 FN02 - Non-Resident Withholding Tax
// 
//    Rev 1.5   Nov 28 2005 09:43:48   jankovii
// PET1228_FN02_ EU Savings Directive Phase Two
// 
//    Rev 1.4   Apr 21 2005 10:17:56   ZHANGCEL
//  Added initNew for a new account creation.
// 
//    Rev 1.3   Mar 04 2005 16:34:04   georgeet
// PET1171 FN01 - EU Savings Directive Tax Exemption.  Modified the existing screen to include four new fields with appropriate business logic.
// 
//    Rev 1.2   Nov 14 2004 14:56:52   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Sep 20 2004 10:41:16   ZHANGCEL
// PET1082-FNrlc --  New Quebec withholding tax enhancement
// 
//    Rev 1.0   Aug 06 2004 17:46:12   ZHANGCEL
// Initial revision.
 * 
 */