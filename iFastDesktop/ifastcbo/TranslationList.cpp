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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TranslationList.cpp
// ^AUTHOR : Mike Metzger
// ^DATE   : Mar 5, 1999
//
// ^CLASS    : TranslationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "translationlist.hpp"
#include <ifastdataimpl\dse_dstc0136_vw.hpp>
#include <ifastdataimpl\dse_dstc0136_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSLATION_LIST;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "TranslationList" );

   const I_CHAR * const TRANSLATION_LIST_NAME = I_( "TranslationList" );
   const I_CHAR * const MONEY_MARKET = I_("I");
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

//******************************************************************************
TranslationList::TranslationList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
   setVersionable( false );

}

//******************************************************************************
TranslationList::~TranslationList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY TranslationList::init( const DString& dstrTrack,const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0136_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   AsyncReceiveData( DSTC_REQUEST::TRANSLATION_LIST, queryData, ifds::DSTC0136_VW, DSTCRequestor( getSecurity(), true) );

   return(GETCURRENTHIGHESTSEVERITY());

}


//******************************************************************************
void TranslationList::getStrKey( DString& strKey, const DString& strLangCode, const DString& strFundCode )
{
   strKey = strLangCode;
   strKey.strip();
   strKey += I_("  ");
   strKey += strFundCode;
   strKey.strip();
   strKey.upperCase();
}
//******************************************************************************
void TranslationList::getStrKey ( DString &strKey, const BFData *data)
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString strLangCode = data->getElementValue( I_( "LangCode" ) );
      DString strFundCode = data->getElementValue( I_( "FundCode" ) );
      getStrKey( strKey, strLangCode, strFundCode );
   }
   else
   {
      BFCBO::getStrKey( strKey , NULL );
   }

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TranslationList.cpp-arc  $
 // 
 //    Rev 1.15   Dec 10 2004 14:55:20   hernando
 // PET1117 - Recovered version feature.
 // 
 //    Rev 1.14   Nov 24 2004 10:19:58   yingbaol
 // PET1117:take out version feature untill base fully support it.
 // 
 //    Rev 1.13   Nov 18 2004 13:28:40   YINGBAOL
 // PET1117: Perfermance Tunning
 // 
 //    Rev 1.12   Nov 14 2004 14:58:50   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.11   Mar 21 2003 18:28:04   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.10   Oct 09 2002 23:55:14   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.9   Aug 29 2002 12:57:00   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.8   22 May 2002 18:30:12   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.7   03 May 2001 14:07:16   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.6   09 Feb 2001 14:56:14   SMITHDAV
 // Do Async Requests...
 // 
 //    Rev 1.5   Jan 18 2001 16:10:40   YINGBAOL
 // add eTracker
 // 
 //    Rev 1.4   Dec 17 2000 20:24:50   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.3   Dec 08 2000 17:20:04   FENGYONG
 // get the whole list
 // 
 //    Rev 1.2   Dec 06 2000 15:21:24   OLTEANCR
 // modif. ReceiveData
 // 
 //    Rev 1.1   Nov 01 2000 10:10:20   OLTEANCR
 // new data brokering system
 // 
 //    Rev 1.0   Aug 03 2000 08:57:02   BUZILA
 // Initial revision.
 * 
*/