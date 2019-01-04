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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AmsFundAllocList.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : Nov. 7, 2002
//
// ^CLASS    : AmsFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Ams FundAllocationList
//
//******************************************************************************

#include "stdafx.h"
#include "AmsFundAlloc.hpp"
#include "AmsFundAllocList.hpp"
#include "FundAllocList.hpp"
#include <ifastdataimpl\dse_dstc0218_req.hpp>
#include <ifastdataimpl\dse_dstc0218_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AmsFundAllocList" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
   const double dSmallValue       = .0000000001;
}

namespace CND
{

   extern const long	ERR_WARNING_AMS_ALLOCATION_CHANGE;
}

namespace ifds
{  
	extern CLASS_IMPORT const BFTextFieldId    FundAlloc;
   extern CLASS_IMPORT const BFTextFieldId    ForeignRelFundClass;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_FUND_ALLOC_LIST;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::AMSCode, BFCBO::NONE, 0 }, 
   { ifds::AMSType, BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate, BFCBO::NONE, 0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "AMSFundAlloc" ),    BFCBO::REQUIRED,     0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );
//******************************************************************************
AmsFundAllocList::AmsFundAllocList( BFAbstractCBO &parent ) 
: FundAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
AmsFundAllocList::~AmsFundAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY AmsFundAllocList::initExisting(const DString& dstrTrack,
                                          const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   setListFields(BF::HOST);

	DString dstrAMSCode, dstrAMSType, dstrEffectiveDate;
	getField(ifds::AMSCode,dstrAMSCode,BF::HOST,false);
   getField(ifds::AMSType,dstrAMSType,BF::HOST,false);
   getField(ifds::EffectiveDate,dstrEffectiveDate,BF::HOST,false);

	dstrAMSCode.strip();
   BFData* pReqFundAlloc =  new BFData( ifds::DSTC0218_REQ);

   DString mgmtCoIdOut, strAccountNum, dstrRIFId;
   pReqFundAlloc->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   pReqFundAlloc->setElementValue( ifds::NextKey,NULL_STRING );
   pReqFundAlloc->setElementValue( ifds::Track, dstrTrack );
   pReqFundAlloc->setElementValue( ifds::AMSCode, dstrAMSCode );
   pReqFundAlloc->setElementValue( ifds::AMSType, dstrAMSType );
   pReqFundAlloc->setElementValue( ifds::Activity, dstrPageName );
   pReqFundAlloc->setElementValue( ifds::EffectiveDate, dstrEffectiveDate );

   ReceiveData(DSTC_REQUEST::AMS_FUND_ALLOC_LIST, *pReqFundAlloc, ifds::DSTC0218_VW, 
               DSTCRequestor( getSecurity(), true ) );
   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AmsFundAllocList::initNew(  const BFDataGroupId& idDataGroup,
												 bool bGetDefault,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   FundAllocList::initNew(idDataGroup, bGetDefault, dstrTrack, dstrPageName);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AmsFundAllocList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   AmsFundAlloc *pAllocation = new AmsFundAlloc( *this );
   pAllocation->initNew( idDataGroup );
   pBase = pAllocation;
   getParent()->setFieldValid( ifds::ForeignRelFundClass, idDataGroup, false );
   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************
SEVERITY AmsFundAllocList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new AmsFundAlloc ( *this );
   dynamic_cast< AmsFundAlloc * >( pObjOut )->initExisting( data );
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AmsFundAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
	DString dstrFundAlloc;
   getParent()->getField(ifds::FundAlloc, dstrFundAlloc, idDataGroup, false);
	dstrFundAlloc.strip().upperCase();
	if( dstrFundAlloc == NO ) return NO_CONDITION;


	SEVERITY sev = FundAllocList::doValidateAll(idDataGroup,lValidateGroup );
	if(sev > WARNING ) return sev;
	if( !isNew() )
	{
		if( isUpdated( ) )
		{
				DString dstrAmsCode;
				getParent()->getField(ifds::AMSCode,dstrAmsCode,idDataGroup,false );
				dstrAmsCode.strip();
				DString strTemp;
				addIDITagValue( strTemp, I_("AMSCODE"), dstrAmsCode );
				ADDCONDITIONFROMFILEIDI( CND::ERR_WARNING_AMS_ALLOCATION_CHANGE, strTemp);	
		}	
	}

	// Allocation of different fund currency is not allowed in the AMS fund mix if the system feature Multi-currency = No. 
   if( !isMultiCurrency() )
      validateMulticurrency(idDataGroup);


	return (GETCURRENTHIGHESTSEVERITY());
	
}

//******************************************************************************

SEVERITY AmsFundAllocList::doDeleteObject (const DString &strKey, 
   const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed) 
{ 
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doDeleteObject"));
   getParent()->setFieldValid( ifds::ForeignRelFundClass, idDataGroup, false );

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
//IN2818924 - DSK_AMS Validation for CDIC
bool AmsFundAllocList::isBankruptcyApplied( const BFDataGroupId &idDataGroup)
{
   bool ret(false);

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while( !iter.end() )
   {
	   AmsFundAlloc *pAmsFundAlloc = dynamic_cast<AmsFundAlloc *>(iter.getObject());

	   if(pAmsFundAlloc->getBankruptcyAppliedFlag())
	   {
		   ret = true; 
		   break;
	   }

	   ++iter;
   }


   return ret;
}
//******************************************************************************
//IN2818924 - DSK_AMS Validation for CDIC
bool AmsFundAllocList::isBankruptcyApplied( DString& fundCode,
											DString& classCode,
											const BFDataGroupId &idDataGroup)
{
   bool ret(false);

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while( !iter.end() )
   {
	   AmsFundAlloc *pAmsFundAlloc = dynamic_cast<AmsFundAlloc *>(iter.getObject());

	   if(pAmsFundAlloc->getBankruptcyAppliedFlag())
	   {
		   pAmsFundAlloc->getField (ifds::FundCode, fundCode, BF::HOST);
		   pAmsFundAlloc->getField (ifds::ClassCode, classCode, BF::HOST);
		   classCode.strip().upperCase();
		   classCode.strip().upperCase();	  

		   ret = true; 
		   break;
	   }

	   ++iter;
   }


   return ret;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AmsFundAllocList.cpp-arc  $
// 
//    Rev 1.15   Jan 31 2012 07:38:40   panatcha
// IN2818924 - DSK_AMS Validation for CDIC
// 
//    Rev 1.14   Nov 14 2004 14:25:54   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   Feb 23 2004 10:51:02   HERNANDO
// PTS10026642 - Added setFieldValid to ForeignRelFundClass in doCreateNewObject.
// 
//    Rev 1.12   Feb 22 2004 19:10:24   HERNANDO
// PTS10026642 - Added doDeleteObject.
// 
//    Rev 1.11   Oct 20 2003 11:42:24   linmay
// PTS Ticket #10023032, fix multi-currency issue.
// 
//    Rev 1.10   Aug 11 2003 09:39:04   linmay
// added EffectiveDate
// 
//    Rev 1.9   Jul 30 2003 14:14:34   linmay
// modified initExisting(),..
// 
//    Rev 1.8   Apr 02 2003 17:26:22   HERNANDO
// Added AMSType for the request in getAMSFundAllocList.
// 
//    Rev 1.7   Mar 21 2003 17:59:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Jan 15 2003 13:05:10   YINGBAOL
// if FundAlloc is NO, don't do any validation
// 
//    Rev 1.5   Nov 29 2002 16:52:04   HERNANDO
// Added AMSCode.
// 
//    Rev 1.4   Nov 29 2002 10:11:56   KOVACSRO
// call base class initNew
// 
//    Rev 1.3   Nov 29 2002 08:58:56   KOVACSRO
// made it work globally, rather than just for AMS screens.
// 
//    Rev 1.2   Nov 27 2002 11:47:22   YINGBAOL
// getTotalPercentage
// 
//    Rev 1.1   Nov 19 2002 13:28:34   YINGBAOL
// added business rules
// 
//    Rev 1.0   Nov 13 2002 09:59:54   YINGBAOL
// Initial Revision

 * 
 * 
 */