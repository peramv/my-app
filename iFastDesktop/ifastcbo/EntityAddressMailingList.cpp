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
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : EntityAddressMailingList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Semptember. 10, 2002
//
// ^CLASS    : EntityAddressMailingList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0214_req.hpp>
#include <ifastdataimpl\dse_dstc0214_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"
#include "EntityAddressMailingList.hpp"
#include "EntityAddressMailingInfo.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITY_ADDRESS_MAILING;   
   extern CLASS_IMPORT const DSTCRequest ENTITY_MAIL_DELIVER_OPTION;
}

namespace  
{
	const I_CHAR * const CLASSNAME = I_( "EntityAddressMailingList" );  
}

namespace CND
{  // Conditions used
      extern const long ERR_DUPLICATED_ENTITY_MAIL;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//*********************************************************************************
EntityAddressMailingList::EntityAddressMailingList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
EntityAddressMailingList::~EntityAddressMailingList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//**********************************************************************************
void EntityAddressMailingList::initNew( const DString& accountNum,
													const DString& entityType,
													const DString& seqNumber,
													const BFDataGroupId& idDataGroup)
{




}
//*********************************************************************************
SEVERITY EntityAddressMailingList::init( const DString& dstrAccountNum, 
													  const DString& dstrEntityType,
													  const DString& dstrEntityTypeSeq,
													  const BFDataGroupId& idDataGroup,
		                                   const DString& dstrTrack,
													  const DString& dstrPageName  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   
   BFData _requestData(ifds::DSTC0214_REQ);
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
	_requestData.setElementValue( ifds::EntityType, dstrEntityType );
	_requestData.setElementValue( ifds::EntityTypeSeq, dstrEntityTypeSeq );
	_requestData.setElementValue( ifds::RequestType, NULL_STRING);

   ReceiveData(DSTC_REQUEST::ENTITY_ADDRESS_MAILING, _requestData, ifds::DSTC0214_VW, DSTCRequestor( getSecurity(), false) );
 	return GETCURRENTHIGHESTSEVERITY();
}
//********************************************************************************
SEVERITY EntityAddressMailingList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
	pObjOut =  new EntityAddressMailingInfo( *this );
	((EntityAddressMailingInfo* )pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY EntityAddressMailingList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   EntityAddressMailingInfo* pEntityAddressMailingInfo = new EntityAddressMailingInfo( *this );
	pEntityAddressMailingInfo->init( idDataGroup  );
	pBase = pEntityAddressMailingInfo;
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY EntityAddressMailingList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
 MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
 //document type should be unique
// yingbao as of Dec. 2, 2004
	BFObjIter iter1( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
	BFObjIter iter2( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
	while( !iter1.end() )
	{
		DString docType1,docType2,docDes;
		BFAbstractCBO* pBase1 = iter1.getObject();
      if( pBase1 )
      {
		   pBase1->getField(ifds::DocumentType,docType1,idDataGroup,false);
		   pBase1->getField(ifds::DocumentType,docDes,idDataGroup,true);
		   docType1.strip();
	      iter2.positionByKey( iter1.getStringKey() ); 
		   ++iter2;
		   while(!iter2.end() )
			   {
				   BFAbstractCBO* pBase2 = iter2.getObject();
               if ( pBase2 )
               {
				      pBase2->getField(ifds::DocumentType,docType2,idDataGroup,false);
				      docType2.strip();
				      if(docType1 == docType2  )
				      {
					      DString idiStr;
					      addIDITagValue( idiStr, I_("DOCTYPE"), docDes );
					      ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATED_ENTITY_MAIL, idiStr.c_str() );  							
				      }
               }
			     ++iter2;
			   }
      }
	 ++iter1;
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
void EntityAddressMailingList::getStrKey( DString &strKey, const BFData *data )
{
   strKey = data->getElementValue(ifds::DocumentType).stripAll();   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EntityAddressMailingList.cpp-arc  $
// 
//    Rev 1.12   Mar 02 2005 16:18:46   porteanm
// PET 1171 FN01 - Fixed getStrKey().
// 
//    Rev 1.11   Dec 03 2004 17:18:18   yingbaol
// PET1137,FN01: fix business rules.
// 
//    Rev 1.10   Nov 14 2004 14:36:36   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Apr 03 2003 17:54:44   FENGYONG
// hardcode requesttype is null
// 
//    Rev 1.8   Mar 21 2003 18:08:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 30 2002 10:10:48   YINGBAOL
// Sync. up from old PVCS database
// 
//    Rev 1.8   Oct 21 2002 11:20:28   YINGBAOL
// more business rules added
// 
//    Rev 1.7   Oct 15 2002 10:37:00   HUANGSHA
// changed the AddrCode to EntityAddrCode in getStrKey(...)
// 
//    Rev 1.6   Oct 10 2002 12:51:04   HUANGSHA
// change getStrKey()
// 
//    Rev 1.4   Oct 09 2002 10:49:58   HUANGSHA
// added getStrKey()
// 
//    Rev 1.3   Sep 27 2002 15:09:20   YINGBAOL
// take off comparing addrcode and suppress
// 
//    Rev 1.2   Sep 24 2002 10:49:50   YINGBAOL
// check duplicate records
// 
//    Rev 1.1   Sep 17 2002 13:43:14   YINGBAOL
// add initNew
// 
//    Rev 1.0   Sep 10 2002 14:03:26   YINGBAOL
// Initial revision.




*/
