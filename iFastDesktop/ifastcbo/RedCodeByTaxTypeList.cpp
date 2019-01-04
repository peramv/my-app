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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : RedCodeByTaxTypeList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/20/2000
//
// ^CLASS    : RedCodeByTaxTypeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "redcodebytaxtype.hpp"
#include "redcodebytaxtypelist.hpp"
#include <ifastdataimpl\dse_dstc0138_vw.hpp>
#include <ifastdataimpl\dse_dstc0138_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REDCODEBYTAXTYPE;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_( "RedCodeByTaxTypeList" );
}

//******************************************************************************
RedCodeByTaxTypeList::RedCodeByTaxTypeList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
RedCodeByTaxTypeList::~RedCodeByTaxTypeList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY RedCodeByTaxTypeList::init( DString& TaxType, 
                                     DString& CodeType,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData(ifds::DSTC0138_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::TaxType, TaxType ); 
   requestData.setElementValue( ifds::CodeType, CodeType );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::REDCODEBYTAXTYPE, requestData, ifds::DSTC0138_VW, DSTCRequestor( getSecurity(), true) );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RedCodeByTaxTypeList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   RedCodeByTaxType *pRedCode = new RedCodeByTaxType( *this );
   pRedCode->init( data );
   pObjOut = pRedCode;

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
void RedCodeByTaxTypeList::getStrKey ( DString& strKey, const BFData* data )//key by RedCode or DepositType
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      strKey = data->getElementValue( ifds::RedCode );
      strKey.strip();
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}

//******************************************************************************
bool RedCodeByTaxTypeList::getRedCodeByTaxType( DString dstrRedCode, RedCodeByTaxType *&pRedCodeByTaxType,
                                                const BFDataGroupId& idDataGroup ) 
{
   BFData data;
   data.setElementValue( ifds::RedCode, dstrRedCode, true, false );
   DString dstrKey;
   getStrKey( dstrKey, &data );

   BFObjIter iterList( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   if( iterList.positionByKey( dstrKey ) )
   {
      pRedCodeByTaxType = static_cast<RedCodeByTaxType *>( iterList.getObject());
      return(true);
   }
   else
      return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RedCodeByTaxTypeList.cpp-arc  $
// 
//    Rev 1.15   Nov 14 2004 14:51:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.14   Mar 21 2003 18:20:56   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Oct 09 2002 23:54:50   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.12   Aug 29 2002 12:56:26   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.11   22 May 2002 18:29:40   PURDYECH
// BFData Implementation
// 
//    Rev 1.10   Apr 11 2002 13:47:36   JANKAREN
// PTS 10007033 - bug fix for getRedCodeByTaxType()
// 
//    Rev 1.9   Mar 12 2002 16:04:50   JANKAREN
// Added getRedCodeByTaxType()
// 
//    Rev 1.8   03 May 2001 14:06:58   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.7   Jan 18 2001 16:05:42   YINGBAOL
// add eTracker
// 
//    Rev 1.6   Dec 17 2000 20:24:14   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.5   Dec 06 2000 14:15:48   OLTEANCR
// modif. ReceiveData
// 
//    Rev 1.4   Nov 10 2000 14:01:18   VASILEAD
// Fixed using new databroker
// 
//    Rev 1.3   Nov 02 2000 13:22:34   YINGBAOL
// use new databroker
// 
//    Rev 1.2   Oct 27 2000 10:20:58   KOVACSRO
// Implemented doCreateObject and getStrKey.
// 
//    Rev 1.1   May 09 2000 11:36:06   YINGZ
// initial revision

*/
