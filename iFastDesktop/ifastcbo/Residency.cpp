#include "stdafx.h"
#include "Residency.hpp"
#include <ifastdataimpl\dse_dstc0392_req.hpp>
#include <ifastdataimpl\dse_dstc0392_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESIDENCY;
}

namespace
{
   const I_CHAR * const CLASSNAME           = I_( "Residency" );
   const I_CHAR * const YES                 = I_( "Y" );
   const I_CHAR * const NO                  = I_( "N" );
   const I_CHAR * const BLANK               = I_("");
}

namespace ifds
{  // Conditions used
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

/*const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                   State Flags, Group Flags 
   { ifds::AsofDate,               BFCBO::NONE,     0 }, 
   { ifds::AccountNum,             BFCBO::NONE,     0 }, 
   { ifds::TaxType,                BFCBO::NONE,     0 }, 
   { ifds::TaxJuris,               BFCBO::NONE,     0 }, 
   { ifds::DepositType,            BFCBO::NONE,     0 }, 
   { ifds::ShrNum,                 BFCBO::NONE,     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );*/


namespace CND
{  // Conditions used
   
}

//******************************************************************************
Residency::Residency( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   //registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
Residency::~Residency()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY Residency::init( const DString& dstrTaxType, 
                          const DString& dstrTaxJurisd, 
                          const BFDataGroupId& idDataGroup,
						  const DString& dstrTrack,
                          const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0392_REQ);
   BFData *receivedData = new BFData(ifds::DSTC0392_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
   queryData.setElementValue(ifds::AccountNum, I_("0") );
   queryData.setElementValue(ifds::AsofDate, BLANK );
   queryData.setElementValue(ifds::DepositType, BLANK );
   queryData.setElementValue(ifds::TaxType, dstrTaxType );
   queryData.setElementValue(ifds::TaxJuris, dstrTaxJurisd );   
   queryData.setElementValue(ifds::Track, dstrTrack);
   queryData.setElementValue(ifds::Activity, dstrPageName);

   //call the back-end
   ReceiveData(DSTC_REQUEST::RESIDENCY, queryData, *receivedData, DSTCRequestor(getSecurity(), false) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY Residency::init( const DString& dstrAccountNum, 
                          const DString& dstrAsOfDate, 
				          const DString& dstrDepositType, 
                          const BFDataGroupId& idDataGroup , 
                          const DString& dstrTrack ,
                          const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0392_REQ);
   BFData *receivedData = new BFData(ifds::DSTC0392_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
   queryData.setElementValue(ifds::AccountNum, dstrAccountNum );
   queryData.setElementValue(ifds::AsofDate, dstrAsOfDate );
   queryData.setElementValue(ifds::DepositType, dstrDepositType );
   queryData.setElementValue(ifds::TaxType, BLANK );
   queryData.setElementValue(ifds::TaxJuris, BLANK );   
   queryData.setElementValue(ifds::Track, dstrTrack);
   queryData.setElementValue(ifds::Activity, dstrPageName);

   //call the back-end
   ReceiveData(DSTC_REQUEST::RESIDENCY, queryData, *receivedData, DSTCRequestor(getSecurity(), false) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY Residency::initForShr ( const DString& dstrShrNum, 
                                 const DString& dstrTaxJurisd, 
                                 const BFDataGroupId& idDataGroup, 
                                 const DString& dstrTrack,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0392_REQ);
   BFData *receivedData = new BFData(ifds::DSTC0392_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
   queryData.setElementValue(ifds::ShrNum, dstrShrNum );
   queryData.setElementValue(ifds::AsofDate, BLANK );
   queryData.setElementValue(ifds::DepositType, BLANK );
   queryData.setElementValue(ifds::TaxType, BLANK );
   queryData.setElementValue(ifds::TaxJuris, dstrTaxJurisd );   
   queryData.setElementValue(ifds::Track, dstrTrack);
   queryData.setElementValue(ifds::Activity, dstrPageName);

   //call the back-end
   ReceiveData(DSTC_REQUEST::RESIDENCY, queryData, *receivedData, DSTCRequestor(getSecurity(), false) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Residency::isTaxJurisdictionValid()
{
	DString strValidTaxJuris;
	getField( ifds::TaxJurisValid, strValidTaxJuris, BF::HOST, false );
	
	return (strValidTaxJuris.strip().upperCase() == I_("Y") );
}

//******************************************************************************

bool Residency::isDateValid()
{
	DString strValidDate;
	getField( ifds::TradeDateValid, strValidDate, BF::HOST, false );    
	
	return (strValidDate.strip().upperCase() == I_("Y") );
}

//******************************************************************************
SEVERITY Residency::doValidateField( const BFFieldId& idField, 
                                        const DString& strValue, 
                                        const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
  
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Residency::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Residency.cpp-arc  $
// 
//    Rev 1.0   06 Oct 2008 14:28:28   kovacsro
// Initial revision.
 * 
// 
*/
