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
//    Copyright 1999 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : AddressEntityList.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 09/06/99
//
// ^CLASS    : AddressEntityList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "addressentitylist.hpp"
#include "entityaddress.hpp"
#include <ifastdataimpl\dse_dstc0071_vw.hpp>
#include <ifastdataimpl\dse_dstc0071_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ADDRESSES_ENTITY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AddressEntityList" );
   const I_CHAR * const ENTITY_ID = I_( "EntId" );

}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId SeqNumber;
	extern CLASS_IMPORT const BFTextFieldId EntityType;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,                   State Flags,              Group Flags 
   { ifds::EntityType,                  BFCBO::NOT_ON_HOST,           0 }, 
   { ifds::SeqNumber ,                  BFCBO::NOT_ON_HOST,           0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AddressEntityList::AddressEntityList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}

//******************************************************************************
AddressEntityList::~AddressEntityList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AddressEntityList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AddressEntityList::init( DString& entityID,
                                  const DString& dstrTrack,
                                  const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0071_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::EntityId, entityID ); 
   queryData.setElementValue(  ifds::AddrId, I_("0.0") );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );
   queryData.setElementValue( ifds::SearchType, ENTITY_ID );

   ReceiveData( DSTC_REQUEST::ADDRESSES_ENTITY, queryData, ifds::DSTC0071_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AddressEntityList::initSearch( const DString& strSearchType, 
													const DString& strSearchFirstName, 
													const DString& strSearchLastName, 
													const DString& strAddrId, 
													const DString& strSearchPSTL, 
													const DString& strSearchCountry,
													const DString& dstrTrack,
													const DString& dstrPageName,
													bool  bAddDataNotFoundError )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initSearch" ) );

   queryData = ifds::DSTC0071_REQ;
	DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::SearchType, strSearchType ); 
   queryData.setElementValue( ifds::SearchFirstName, strSearchFirstName);
	queryData.setElementValue( ifds::SearchLastName, strSearchLastName);
	queryData.setElementValue( ifds::AddrId, strAddrId);
	queryData.setElementValue( ifds::SearchPSTL, strSearchPSTL);
	queryData.setElementValue( ifds::SearchCountry, strSearchCountry);
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::ADDRESSES_ENTITY, queryData, ifds::DSTC0071_VW, DSTCRequestor( getSecurity(), false, bAddDataNotFoundError ) );	

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY AddressEntityList::getMore()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
   
	if (doMoreRecordsExist())
   {
		ReceiveData ( DSTC_REQUEST::ADDRESSES_ENTITY, 
                    queryData, 
                    ifds::DSTC0071_VW, 
                    DSTCRequestor (getSecurity(), false ));
	}
	return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************
SEVERITY AddressEntityList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut =  new EntityAddress( *this );
   ((EntityAddress*) pObjOut)->init( data );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AddressEntityList::doCreateNewObject( BFCBO*& pBase, DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new EntityAddress( *this );
   dynamic_cast<EntityAddress*>(pBase)->init( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************
bool AddressEntityList::doesAddressCodeExist(const DString& dstrAddrCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "DoesAddressCodeExist" ) );
   DString dstrAddressCode;
   bool bExists = false;
   EntityAddress *pAddress = NULL;

   BFObjIter iter( *this, idDataGroup );
   while( !iter.end() )
   {
      pAddress = dynamic_cast < EntityAddress * >( iter.getObject());
      if( pAddress )
      {
         pAddress->getField( ifds::AddrCode, dstrAddressCode, idDataGroup );
         if( dstrAddressCode.strip() == dstrAddrCode )
         {
            bExists = true;
            break;
         }
      }
      ++iter;
   }

   return(bExists);
}

//**********************************************************************************
bool AddressEntityList::isDuplicateEntityAddress( EntityAddress *pEntityAddressToCheck,
	                                              const BFDataGroupId& idDataGroup )
{
   bool bExists = false;

   DString dstrAddrCode; 	 
   pEntityAddressToCheck->getField( ifds::AddrCode,      dstrAddrCode,      idDataGroup );   
   
   BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      EntityAddress *pCurrentEntityAddress = dynamic_cast <EntityAddress *>( iter.getObject());
      if( NULL != pCurrentEntityAddress  &&
		  pCurrentEntityAddress != pEntityAddressToCheck )   // Do not check against self
      {
         // we'll have one unique record for each address code 
         DString dstrCurrentAddrCode;           
		 pCurrentEntityAddress->getField( ifds::AddrCode,      dstrCurrentAddrCode, idDataGroup );		 
		 if( dstrCurrentAddrCode.strip().upperCase() == dstrAddrCode.upperCase() )
         {
            bExists = true;
            break;
         }
      }
      ++iter;
   }

   return bExists;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/addressEntityList.cpp-arc  $
 * 
 *    Rev 1.18   Mar 14 2005 16:17:02   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.17   Mar 10 2005 16:36:44   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.16   Mar 10 2005 13:27:26   ZHANGCEL
 * PET  1171 FN1 -- InitSeach should return "Data not found" error
 * 
 *    Rev 1.15   Mar 08 2005 17:06:54   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.14   Mar 07 2005 13:24:14   ZHANGCEL
 * PET 1171 FN1 --Added initSearch function for the EntityAddressSearvhCriteria
 * 
 *    Rev 1.13   Mar 02 2005 16:46:18   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.12   Oct 26 2004 10:53:44   YINGBAOL
 * PET1137:FN01 Add doesAddressCodeExist method.
 * 
 *    Rev 1.11   Aug 21 2003 15:24:34   YINGBAOL
 * make it work after view changes
 * 
 *    Rev 1.10   Mar 21 2003 17:56:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:53:58   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Aug 29 2002 12:55:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:26:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   03 May 2001 14:05:54   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Jan 19 2001 09:24:04   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.4   Dec 17 2000 20:22:26   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   15 Nov 2000 15:30:18   SMITHDAV
 * Use new ReceiveData and do some cleanup.
 * 
 *    Rev 1.2   Nov 07 2000 17:17:22   OLTEANCR
 * bug fix
 * 
 *    Rev 1.1   Nov 03 2000 14:02:40   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.0   Feb 15 2000 10:59:48   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.15   Jan 18 2000 18:18:08   POPESCUS
 * check in for point release
 * 
 *    Rev 1.14   Jan 14 2000 15:08:28   YINGBAOL
 * fix view issues
 * 
 *    Rev 1.13   Dec 12 1999 16:25:08   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
 * 
 *    Rev 1.12   Dec 10 1999 11:50:42   YINGBAOL
 * added validation
 * 
 */





