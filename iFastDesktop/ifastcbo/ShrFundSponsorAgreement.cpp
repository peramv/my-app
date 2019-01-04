//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : ShrFundSponsorAgreement.cpp
//    ^AUTHOR : Monica Vadeanu
//    ^DATE   : June, 2004
//    Copyright 2004 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ShrFundSponsorAgreement
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "fundsponsorslist.hpp"
#include "mgmtco.hpp"
#include "shrfundsponsoragreement.hpp"
#include "shrfundsponsoragreementlist.hpp"


#include <ifastdataimpl\dse_dstc0069_vw.hpp>                // Shareholder
#include <ifastdataimpl\dse_dstc0083_vw.hpp>                // System Configuration 
#include <ifastdataimpl\dse_dstc0299_req.hpp>               // Shareholder Fund Sponsor Agreement Inquiry
#include <ifastdataimpl\dse_dstc0299_vwrepeat_record.hpp>   // Shareholder Fund Sponsor Agreement Inquiry
#include <ifastdataimpl\dse_dstc0300_req.hpp>               // Shareholder Fund Sponsor Agreement Update


// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("ShrFundSponsorAgreement");
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
                              //  Field DD Id,         State Flags,     Group Flags 
   {ifds::FundGroup,         BFCBO::REQUIRED, 0 }, 
	{ifds::FundGroupDesc,     BFCBO::NONE,     0 }, 
	{ifds::EffectiveDate,     BFCBO::REQUIRED, 0 }, 
	{ifds::DistribCoopAgrmnt, BFCBO::REQUIRED, 0 },       
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
ShrFundSponsorAgreement::ShrFundSponsorAgreement(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);     
}

//******************************************************************************
ShrFundSponsorAgreement::~ShrFundSponsorAgreement()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreement::init( const BFData &viewData )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(viewData), false, true);
   
	DString dstrFundGroup( viewData.getElementValue( ifds::FundGroup ) );             
   dstrFundGroup.stripAll().upperCase();
   
   commonInit( dstrFundGroup, 				
					BF::HOST);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreement::init( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   //DString dstrShareholderNum;

	//getParent()->getParent()->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
   //dstrShareholderNum.stripAll().upperCase();     
   //setFieldNoValidate(ifds::ShareholderNum, dstrShareholderNum, idDataGroup, false, false, true, true);   
      
	commonInit( I_( "" ), 					
					idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreement::commonInit( const DString &dstrFundGroup, 														 
														    const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

	// Set substitute value from Fund Sponsors list	
	FundSponsorsList* pFundSponsorsList = NULL;
	if ( getMgmtCo ().getFundSponsorsList( pFundSponsorsList ) <= WARNING &&
		  NULL != pFundSponsorsList )
	{
		DString dstrFundSponsorSubstList;
		if ( pFundSponsorsList->getFundSponsorCodeSubstList( dstrFundSponsorSubstList ) <= WARNING &&
           !dstrFundSponsorSubstList.strip().empty() )
		{
			setFieldAllSubstituteValues( ifds::FundGroup, idDataGroup, dstrFundSponsorSubstList );
		}
	}
	
   //the values of the key should be made read only, if not a new object,   
	setFieldReadOnly( ifds::FundGroup, idDataGroup, idDataGroup == BF::HOST );     
	setValidFlag( ifds::FundGroup,     idDataGroup, idDataGroup == BF::HOST );  
	setUpdatedFlag( ifds::FundGroup,   idDataGroup, !(idDataGroup == BF::HOST) );

	setFundGroupName (idDataGroup);	
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ShrFundSponsorAgreement::doInitWithDefaultValues( const BFDataGroupId &idDataGroup )
{   	
	setEffectiveDate( idDataGroup );		
	setFieldNoValidate( ifds::DistribCoopAgrmnt, I_( "1" ), idDataGroup );
}

//******************************************************************************
void ShrFundSponsorAgreement::doReset (const BFDataGroupId &idDataGroup)
{
   if( isNew() )
   {
      init( idDataGroup );
   }
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreement::doApplyRelatedChanges( const BFFieldId &idField, 
																		   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::FundGroup )
   {
      setFundGroupName (idDataGroup);
   }	

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreement::setFundGroupName( const BFDataGroupId &idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundGroupName"));

	DString dstrFundGroup;
	getField( ifds::FundGroup, dstrFundGroup, idDataGroup );
	dstrFundGroup.stripAll().upperCase();

	if ( !dstrFundGroup.empty() )
	{
		FundSponsorsList* pFundSponsorsList = NULL;
		if ( getMgmtCo ().getFundSponsorsList( pFundSponsorsList ) <= WARNING &&
			  NULL != pFundSponsorsList )
		{
			BFAbstractCBO *pFundSponsor = NULL;
			if( pFundSponsorsList->getFundSponsor( dstrFundGroup, pFundSponsor ) <= WARNING &&
				 NULL != pFundSponsor )
			{
				DString dstrFundGroupDesc;
				pFundSponsor->getField( ifds::FundGroupDesc, dstrFundGroupDesc, idDataGroup );
				setFieldNoValidate( ifds::FundGroupDesc, dstrFundGroupDesc, idDataGroup );	
			}                		
		}
	}
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreement::setEffectiveDate( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("setEffectiveDate"));

	DString dstrCurrBusDate;
	getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

	setFieldNoValidate( ifds::EffectiveDate, dstrCurrBusDate, idDataGroup );

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreement::doValidateField( const BFFieldId &idField, 
																   const DString &strValue, 
																   const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );
   
	if (idField == ifds::FundGroup )
   {
		ShrFundSponsorAgreementList *pShrFundSponsorAgreementList = dynamic_cast<ShrFundSponsorAgreementList*>( getParent( ) );      
		if ( NULL != pShrFundSponsorAgreementList )
		{
			// Call duplicate check from Parent
			pShrFundSponsorAgreementList->checkDuplicate( this, idDataGroup );		
		}
   }   

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFundSponsorAgreement.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:56:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Jul 28 2004 14:44:08   VADEANUM
// PET1117 FN01 - Shareholder Static Data.
// 
//    Rev 1.0   Jul 26 2004 10:17:34   VADEANUM
// Initial revision.
//
