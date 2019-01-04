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
// ^FILE   : CurrencyList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 12/09/99
//
// ^CLASS    : CurrencyList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "currencylist.hpp"
#include "currency.hpp"
#include <ifastdataimpl\dse_dstc0101_vw.hpp>
#include <ifastdataimpl\dse_dstc0101_req.hpp>
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CURRENCYLIST;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Currency;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_( "CurrencyList" );

   const I_CHAR *  CURRENCY0 = I_( "Currency" );

}

//******************************************************************************
CurrencyList::CurrencyList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   setVersionable( false );

}

//******************************************************************************
CurrencyList::~CurrencyList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY CurrencyList::init( const DString& dstrTrack,const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData(ifds::DSTC0101_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   AsyncReceiveData (DSTC_REQUEST::CURRENCYLIST, 
                     requestData, 
                     ifds::DSTC0101_VW, 
                     DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void CurrencyList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      strKey = data->getElementValue( CURRENCY0 );
      strKey.strip();
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}


//******************************************************************************
SEVERITY CurrencyList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   Currency * pCurrency = new Currency( *this );
   pCurrency->init( data );
   pObjOut = pCurrency;

   return(GETCURRENTHIGHESTSEVERITY());
}


//*****************************************************************************
bool CurrencyList::getCurrency (DString strCurrency, Currency *&pCurrency, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getIntermediary") );

   bool bCurrencyExist = false;
   pCurrency = NULL;

   BFObjIter iterCurrency( *this, /*idDataGroup*/ BF::HOST );
   iterCurrency.positionByKey( strCurrency );
   if( !iterCurrency.end() )
   // A match was found, get the CBO  
   {
      pCurrency = static_cast<Currency *>( iterCurrency.getObject()); 
      bCurrencyExist = true;
   }
   return(bCurrencyExist);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CurrencyList.cpp-arc  $
 * 
 *    Rev 1.16   24 Jul 2008 12:00:00   popescu
 * Incident - 1190617 - set all the data init calls to be asynch
 * 
 *    Rev 1.15   Dec 10 2004 14:01:58   hernando
 * PET1117 - Recovered version feature.
 * 
 *    Rev 1.14   Nov 24 2004 10:17:08   yingbaol
 * PET1117:temperary take out version features
 * 
 *    Rev 1.13   Nov 18 2004 13:27:56   YINGBAOL
 * PET1117: Perfermance Tunning
 * 
 *    Rev 1.12   Nov 14 2004 14:30:06   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.11   Mar 21 2003 18:02:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:54:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:55:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:26:42   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   03 May 2001 14:06:06   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Jan 18 2001 16:04:32   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Dec 20 2000 16:20:04   WINNIE
 * add getCurrency object method
 * 
 *    Rev 1.4   Dec 17 2000 20:22:52   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 10:54:12   OLTEANCR
 * changed ReceiveData
 * 
 *    Rev 1.2   Nov 02 2000 13:23:18   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.1   May 05 2000 10:32:34   WINNIE
 * Add new class Currency
 * 
 *    Rev 1.0   Feb 15 2000 10:59:52   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 05 2000 20:10:40   BUZILA
// adding list flag
// 
//    Rev 1.4   Dec 23 1999 17:36:44   YINGZ
// use different version of getdataelement
// 
//    Rev 1.3   Dec 14 1999 14:19:00   YINGZ
// add getStrKey
// 
//    Rev 1.2   Dec 12 1999 16:25:16   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
//    Rev 1.1   Dec 12 1999 15:17:58   YINGZ
// ?
 * 
*/