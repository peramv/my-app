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
// ^FILE   : MasterContractList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 03/04/2000
//
// ^CLASS    : MasterContractList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "mastercontractlist.hpp"
#include <ifastdataimpl\dse_dstc0133_req.hpp>
#include <ifastdataimpl\dse_dstc0133_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MASTER_CONTRACT;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "MasterContractList" );
}

namespace ifds
{ 
}

//******************************************************************************
MasterContractList::MasterContractList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   setVersionable( true );
}

//******************************************************************************
MasterContractList::~MasterContractList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY MasterContractList::init( const DString& dstrTrack, const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0133_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::MASTER_CONTRACT, queryData, ifds::DSTC0133_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY MasterContractList::initWithPortfolio (const DString& dstrGroupCode,
                                                const DString& dstrProdPortfolioUUID,
                                                const DString& dstrTrack, 
                                                const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initWithPortfolio" ) );

   BFData queryData(ifds::DSTC0133_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );
   queryData.setElementValue( ifds::ShGroup, dstrGroupCode );
   queryData.setElementValue( ifds::PortfolioCode, dstrProdPortfolioUUID );

   ReceiveData( DSTC_REQUEST::MASTER_CONTRACT, queryData, ifds::DSTC0133_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void MasterContractList::getStrKey( DString &strKey, const BFData *data )  
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString  strGroupCode    = data->getElementValue( ifds::GroupCode  );
      DString  strContractType = data->getElementValue( ifds::ContractType  );
      strKey = strGroupCode;
      strKey.strip();
      strKey += I_(" ");
      strKey += strContractType;
      strKey.strip();

      DString  strDefaultVer = data->getElementValue( ifds::DefaultVer );
      strKey += I_(" ");
      strKey += strDefaultVer;

      strKey.upperCase();
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}

//******************************************************************************
bool MasterContractList::getFieldByGroupAndContractType( DString &GroupCode, DString &ContractType, const BFFieldId &idField, DString &dstrValue, const BFDataGroupId &idDataGroup, bool bFormatted )
{
   bool bFound = false;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

   // Create Key
   DString key( GroupCode );
   key += I_(" ");
   key += ContractType;

   key += I_(" ");
   key += I_("Y");

   key.strip().upperCase();

   bFound = ( iter.positionByKey( key ) );

   if( bFound )
   {
      iter.getObject()->getField( idField, dstrValue, idDataGroup, bFormatted );
   }

   return( bFound );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MasterContractList.cpp-arc  $
 // 
 //    Rev 1.23   Feb 03 2012 16:01:34   dchatcha
 // IN# 2799812 - Contract issues,  fix crahsing when user navigate back to shareholder informaion screen.
 // 
 //    Rev 1.22   Feb 02 2012 00:33:00   dchatcha
 // IN# 2799812 - Contract issues, change the way on working with master contract CBO
 // 
 //    Rev 1.21   Feb 01 2012 18:21:06   dchatcha
 // IN# 2799812 - Contract Screen issues. Fix crashing on no portfolio required environment.
 // 
 //    Rev 1.20   Feb 01 2012 13:25:14   dchatcha
 // IN# 2799812 - Contract Screen issues. Fix crashing on no portfolio required environment.
 // 
 //    Rev 1.19   Jan 09 2012 10:09:08   dchatcha
 // P0186484 - FN 05 - work on Contract Information Screen
 // 
 //    Rev 1.18   Apr 18 2005 13:53:36   hernando
 // PET1024 FN02 - Added getFieldByGroupAndContractType.
 // 
 //    Rev 1.17   Dec 10 2004 14:52:56   hernando
 // PET1117 - Recovered version feature.
 // 
 //    Rev 1.16   Nov 24 2004 10:18:42   yingbaol
 // PET1117:temperary take out version features
 // 
 //    Rev 1.15   Nov 18 2004 13:28:20   YINGBAOL
 // PET1117: Perfermance Tunning
 // 
 //    Rev 1.14   Nov 14 2004 14:49:24   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.13   Mar 21 2003 18:18:02   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.12   Oct 09 2002 23:54:44   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.11   Aug 29 2002 12:56:08   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.10   22 May 2002 18:28:58   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.9   Dec 21 2001 17:35:56   ZHANGCEL
 // Added a new function: getStrKey()
 // 
 //    Rev 1.8   Jul 16 2001 19:19:48   OLTEANCR
 // disabled getStringKey( )
 // 
 //    Rev 1.7   03 May 2001 14:06:44   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.6   Apr 02 2001 10:10:30   OLTEANCR
 // added function getStringKey
 // 
 //    Rev 1.5   Jan 18 2001 16:05:38   YINGBAOL
 // add eTracker
 // 
 //    Rev 1.4   Dec 17 2000 20:24:02   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.3   Dec 06 2000 13:49:22   OLTEANCR
 // modif. ReceiveData
 // 
 //    Rev 1.2   Nov 01 2000 15:29:46   OLTEANCR
 // new data brokering
 // 
 //    Rev 1.1   Apr 14 2000 09:48:40   ZHANGCEL
 // Debug
 // 
 //    Rev 1.0   Apr 11 2000 11:53:08   ZHANGCEL
 // Initial revision.
 * 
 *
*/