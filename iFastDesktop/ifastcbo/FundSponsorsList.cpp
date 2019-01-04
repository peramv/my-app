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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundSponsorsList.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : Nov 18, 2000
//
// ^CLASS    : FundSponsorsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundsponsorslist.hpp"

#include <ifastdataimpl\dse_dstc0148_vw.hpp>
#include <ifastdataimpl\dse_dstc0148_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_SPONSORS;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME         = I_( "FundSponsorsList" );
   const I_CHAR * const FUND_TO_LIST_NAME = I_( "FundSponsorsList" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

//******************************************************************************
FundSponsorsList::FundSponsorsList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
   setVersionable( false );
}


//******************************************************************************
FundSponsorsList::~FundSponsorsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FundSponsorsList::init( const DString& dstrTrack,const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData( ifds::DSTC0148_REQ );

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   requestData.setElementValue( ifds::SortBySpName, I_("Y") );

   ReceiveData( DSTC_REQUEST::FUND_SPONSORS, requestData, ifds::DSTC0148_VW, DSTCRequestor( getSecurity(), true ) );


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void FundSponsorsList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString dstFundGroup  = data->getElementValue( ifds::FundGroup );
      getStrKey( strKey, dstFundGroup );
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}


//******************************************************************************
void FundSponsorsList::getStrKey( DString& dstKey, const DString& dstFundGroup )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   dstKey = dstFundGroup;
   dstKey.strip();
   dstKey.upperCase();
}

//******************************************************************************
SEVERITY FundSponsorsList::getFundSponsorSubstitutionList( DString &dstrFundSponsorSubstList,														  
																			  bool bMatch /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFundSponsorSubstitutionList"));
   
	dstrFundSponsorSubstList = I_( "" );

	BFObjIter iter( *this, 
		             BF::HOST, 
						 bMatch, 
						 BFObjIter::ITERTYPE::NON_DELETED );

   iter.begin();      
	while( !iter.end() )
   {
		BFAbstractCBO *pFundSponsor = iter.getObject();
      if ( NULL != pFundSponsor )
		{
			DString dstrFundGroup, dstrFundGroupDesc;
			pFundSponsor->getField( ifds::FundGroup,     dstrFundGroup,     BF::HOST );
			pFundSponsor->getField( ifds::FundGroupDesc, dstrFundGroupDesc, BF::HOST );			
			dstrFundSponsorSubstList += dstrFundGroup + I_("=") + dstrFundGroupDesc + I_(";");
		}

		++iter;
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundSponsorsList::getFundSponsorCodeSubstList( DString &dstrFundSponsorCodeSubstList )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getFundSponsorCodeSubstList" ) );
   
	dstrFundSponsorCodeSubstList = I_( "" );

	BFObjIter iter( *this, 
		             BF::HOST, 
						 true, 
						 BFObjIter::ITERTYPE::NON_DELETED );

   iter.begin();      
	while( !iter.end() )
   {
		BFAbstractCBO *pFundSponsor = dynamic_cast<BFAbstractCBO*>( iter.getObject() );
      if ( NULL != pFundSponsor )
		{
			DString dstrFundGroup, dstrFundGroupDesc;
			pFundSponsor->getField( ifds::FundGroup,     dstrFundGroup,     BF::HOST );
			pFundSponsor->getField( ifds::FundGroupDesc, dstrFundGroupDesc, BF::HOST );
			dstrFundSponsorCodeSubstList += dstrFundGroup + I_("=") + dstrFundGroup + I_(";");
		}

		++iter;
	}

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY FundSponsorsList::getFundSponsor( const DString &dstrFundGroup,
														 BFAbstractCBO *&pFundSponsor )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFundSponsor"));
   
	pFundSponsor = NULL;
	BFObjIter iter( *this, BF::HOST, true, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();      

	DString dstrKey;
	getStrKey( dstrKey, dstrFundGroup );
	if ( iter.positionByKey( dstrKey ) )
	{
		pFundSponsor = dynamic_cast<BFAbstractCBO*>( iter.getObject() );
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundSponsorsList.cpp-arc  $
// 
//    Rev 1.17   Dec 10 2004 14:36:06   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.16   Nov 24 2004 10:18:34   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.15   Nov 18 2004 13:28:12   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.14   Nov 14 2004 14:43:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   Jul 27 2004 15:34:18   VADEANUM
// PET1117 FN01 - Added getFundSponsorCodeSubstList(), fixed getFundSponsor().
// 
//    Rev 1.12   Jul 27 2004 09:25:00   YINGBAOL
// PET1117:change getFundSponsorSubstitution list method
// 
//    Rev 1.11   Jul 13 2004 16:32:44   VADEANUM
// PET1117 FN01 - Build substitution set and retrieve a specific record.
// 
//    Rev 1.10   Mar 21 2003 18:12:04   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:54:34   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 12:55:58   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   22 May 2002 18:28:46   PURDYECH
// BFData Implementation
// 
//    Rev 1.6   Jul 18 2001 15:11:44   FENGYONG
// Add SortBySpName
// 
//    Rev 1.5   03 May 2001 14:06:38   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.4   Jan 24 2001 11:12:12   YINGBAOL
// set request
// 
//    Rev 1.3   Jan 18 2001 16:05:12   YINGBAOL
// add eTracker
// 
//    Rev 1.2   Dec 17 2000 20:23:30   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.1   Dec 06 2000 11:33:14   OLTEANCR
// modif. ReceiveData
// 
//    Rev 1.0   Nov 20 2000 17:53:04   VASILEAD
// Initial revision.
 // 
 //    Rev 1.0   Apr 03 2000 08:49:54   BUZILA
 // Initial revision.
 * 
*/