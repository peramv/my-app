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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : ShrFundSponsorAgreementList.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : June, 2004
//
// ^CLASS    : ShrFundSponsorAgreementList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "ShrFundSponsorAgreement.hpp"
#include "ShrFundSponsorAgreementlist.hpp"
#include "dstcommonfunction.hpp"

#include <ifastdataimpl\dse_dstc0069_vw.hpp>    // Shareholder
#include <ifastdataimpl\dse_dstc0299_req.hpp>   // Shareholder Fund Sponsor Agreement Inquiry
#include <ifastdataimpl\dse_dstc0299_vw.hpp>    // Shareholder Fund Sponsor Agreement Inquiry


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SHR_FUND_SPONSOR_AGREEMENT_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ShrFundSponsorAgreementList");
}

namespace CND
{  // Conditions used   
	extern const long ERR_DUPLICATE_RECORD;	
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
  // Field DD Id,    State Flags, Group Flags 
   {ifds::ShrNum,    BFCBO::NONE, 0},    
   {ifds::FundGroup, BFCBO::NONE, 0},    	   
};


static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
ShrFundSponsorAgreementList::ShrFundSponsorAgreementList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
}

//******************************************************************************
ShrFundSponsorAgreementList::~ShrFundSponsorAgreementList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreementList::initNew( const DString& dstrShrNum, 
															  const BFDataGroupId& idDataGroup ) // = BF::HOST 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

	setFieldNoValidate (ifds::ShrNum, dstrShrNum, idDataGroup, false );
   
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreementList::init( const DString &dstrFundGroup, 
														  const BFDataGroupId &idDataGroup, // BF::HOST
														  const DString& dstrTrack,         // I_("N"), 
														  const DString &dstrPageName )     // NULL_STRING )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   DString dstrLocalFundGroup( dstrFundGroup ),
           dstrShareholderNum;

	getParent()->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );

	dstrLocalFundGroup.stripAll().upperCase();
	dstrShareholderNum.stripAll().upperCase();
   
	setFieldNoValidate (ifds::ShrNum, dstrShareholderNum, idDataGroup, false );
   setFieldNoValidate (ifds::FundGroup,     dstrLocalFundGroup,  idDataGroup, false );
   	
   _pRequestData = new BFData (ifds::DSTC0299_REQ);

   DString mgmtCoIdOut;

   _pRequestData->setElementValue (ifds::ShrNum, dstrShareholderNum );
   _pRequestData->setElementValue (ifds::FundGroup,      dstrLocalFundGroup );   
   _pRequestData->setElementValue (ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue (ifds::Track,          dstrTrack );
   _pRequestData->setElementValue (ifds::Activity,       dstrPageName );
  
	AsyncReceiveData( DSTC_REQUEST::SHR_FUND_SPONSOR_AGREEMENT_LIST, 
		               *_pRequestData, 
							ifds::DSTC0299_VW, 
							DSTCRequestor( getSecurity(), 
							true) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreementList::doCreateNewObject( BFCBO *&pBase, 
																		   DString &dstrKey, 
																		   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
   	
	ShrFundSponsorAgreement *pShrFundSponsorAgreement = new ShrFundSponsorAgreement (*this);
   if( pShrFundSponsorAgreement->init( idDataGroup) <= WARNING )
   {
      pBase = pShrFundSponsorAgreement;		
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY ShrFundSponsorAgreementList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   ShrFundSponsorAgreement *pShrFundSponsorAgreement = new ShrFundSponsorAgreement (*this);

   if (pShrFundSponsorAgreement->init( data ) <= WARNING)
   {
      pObjOut = pShrFundSponsorAgreement;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ShrFundSponsorAgreementList::getStrKey( DString &dstrKey, const BFData *data )
{
   if( data ) 
   {
      DString dstrShareholderNum;
		if ( NULL != _pRequestData )
			_pRequestData->getElementValue (ifds::ShrNum, dstrShareholderNum );
      
		DString dstrFundGroup = data->getElementValue( ifds::FundGroup );
      
      buildKey( dstrKey, 
					 dstrShareholderNum, 
					 dstrFundGroup );
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL);
   }
}

//creates a unique key for the list
//******************************************************************************
void ShrFundSponsorAgreementList::buildKey( DString &dstrKey, 
													     const DString &dstrShareholderNum, 
													     const DString &dstrFundGroup )
{
   DString dstrLocalShareholderNum (dstrShareholderNum),
           dstrLocalFundGroup( dstrFundGroup );
   	
	dstrKey = I_("ShareholderNum=") + dstrLocalShareholderNum.stripAll().upperCase() +
			    I_(";FundGroup=")     + dstrLocalFundGroup.stripAll().upperCase();
}

//********************************************************************
SEVERITY ShrFundSponsorAgreementList::checkDuplicate( const ShrFundSponsorAgreement *pShrFundSponsorAgreementToCheck, 
																		const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );   	
	
	bool blHasDuplicate = false;

	DString dstrShareholderNumToCheck, dstrFundGroupToCheck;

   //get the values that are part of key, to check against them
	pShrFundSponsorAgreementToCheck->getField (ifds::ShrNum, dstrShareholderNumToCheck, idDataGroup, false);
   pShrFundSponsorAgreementToCheck->getField (ifds::FundGroup,      dstrFundGroupToCheck,      idDataGroup, false);
   
   dstrShareholderNumToCheck.stripAll().upperCase();
   dstrFundGroupToCheck.stripAll().upperCase();
   
	BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
	while( !iter.end() )
   {
		ShrFundSponsorAgreement *pCurrentShrFundSponsorAgreement = dynamic_cast<ShrFundSponsorAgreement*>(iter.getObject());
      if ( NULL != pCurrentShrFundSponsorAgreement &&
			  pShrFundSponsorAgreementToCheck != pCurrentShrFundSponsorAgreement ) // Do not check against itself
		{
			DString dstrCurrentFundGroup;
			pCurrentShrFundSponsorAgreement->getField( ifds::FundGroup, dstrCurrentFundGroup, idDataGroup );
			if ( dstrFundGroupToCheck == dstrCurrentFundGroup.stripAll().upperCase() )
			{
				ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_RECORD );
				break;
			}          
        }
		++iter;
	}	
   
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY ShrFundSponsorAgreementList::getShrFundSponsorAgreement( const DString &dstrFundGroup,																			  
																						const BFDataGroupId &idDataGroup,
																						ShrFundSponsorAgreement *&pShrFundSponsorAgreement )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getShrFundSponsorAgreement"));

	pShrFundSponsorAgreement = NULL;

	DString dstrKey;
	DString dstrShareholderNum;
	getParent()->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
	buildKey( dstrKey, dstrShareholderNum, dstrFundGroup );

	pShrFundSponsorAgreement = dynamic_cast<ShrFundSponsorAgreement*>( getObject( dstrKey, idDataGroup ) );
	
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFundSponsorAgreementList.cpp-arc  $
// 
//    Rev 1.3   Apr 27 2005 14:02:52   porteanm
// Incident 283312 - Changed field name from ShareholderNum to ShrNum for 299 req, 300 req in order to support NASU flow.
// 
//    Rev 1.2   Nov 14 2004 14:56:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Jul 28 2004 14:45:02   VADEANUM
// PET1117 FN01 - Shareholder Static Data.
// 
//    Rev 1.0   Jul 26 2004 10:18:04   VADEANUM
// Initial revision.
//
