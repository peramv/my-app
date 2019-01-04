//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : RemarksList.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : March 25, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RemarksList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "remarkslist.hpp"
#include "remarks.hpp"
#include <ifastdataimpl\dse_dstc0005_vw.hpp>
#include <ifastdataimpl\dse_dstc0005_req.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RemarksList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REMARKS;
}

//******************************************************************************
RemarksList::RemarksList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ), 
_requestData(ifds::DSTC0005_REQ),
_bRefresh (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//******************************************************************************
RemarksList::~RemarksList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY RemarksList::initNew(const DString& shrNum, 
   const BFDataGroupId& idDataGroup /*= BF::HOST*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew") );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RemarksList::init(const DString& shrNum, const DString& dstrTrack,
   const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;

   _requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   _requestData.setElementValue(ifds::ShareholderNum, shrNum);
   _requestData.setElementValue(ifds::Track, dstrTrack);
   _requestData.setElementValue(ifds::Activity, dstrPageName);
   ReceiveData(DSTC_REQUEST::REMARKS, _requestData, ifds::DSTC0005_VW, DSTCRequestor(getSecurity(), false));
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RemarksList::doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   Remarks *remarks = new Remarks( *this );

   remarks->init( idDataGroup );
   pBase = remarks;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RemarksList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new Remarks( *this );
   ( ( Remarks* ) ( pObjOut ) )->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RemarksList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::REMARKS, _requestData, ifds::DSTC0005_VW, DSTCRequestor( getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
void  RemarksList::getStrKey(DString &strKey, const BFData *data)  
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSreKey" ) );

	if( data )
	{
		DString  dstrRecId = data->getElementValue(ifds::RemarksDetlRid );
		dstrRecId.strip().upperCase();   	
		strKey = dstrRecId; 
		strKey.stripTrailing();
	}
	else 
	{
		BFCBO::getStrKey( strKey, NULL );
	}
}

//*************************************************************************************
bool RemarksList::needsRefresh (const BFDataGroupId& idDataGroup) const
{
   return _bRefresh ? _bRefresh : hasUpdatedFields (idDataGroup);
}

//*************************************************************************************
void RemarksList::refreshMe (bool bRefreshMe)
{
   _bRefresh = bRefreshMe;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RemarksList.cpp-arc  $
 * 
 *    Rev 1.15   May 21 2012 14:16:36   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
 * 
 *    Rev 1.14   Nov 14 2004 14:51:54   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.13   Sep 24 2004 14:09:46   YINGBAOL
 * PET1145 FN01 add getStrKey(...)
 * 
 *    Rev 1.12   May 22 2003 14:13:04   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.11   Mar 21 2003 18:21:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:54:52   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:56:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:29:42   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   03 May 2001 14:07:00   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Jan 18 2001 16:05:44   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Dec 17 2000 20:24:16   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.4   Dec 06 2000 14:20:34   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.3   01 Nov 2000 14:30:34   SMITHDAV
 * Update to use ne data broker.
 * 
 *    Rev 1.2   Jul 27 2000 13:52:22   BUZILA
 * fix compilation problem
 * 
 *    Rev 1.1   Jul 26 2000 17:36:58   HUDAVID
 * changed remarks screen/CBO
 * 
 *    Rev 1.0   Feb 15 2000 11:00:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Jan 16 2000 16:59:04   POPESCUS
 * chenges for the methods that get the children lists
 * 
 *    Rev 1.7   Jan 05 2000 20:11:02   BUZILA
 * adding list flag
 * 
 *    Rev 1.6   Dec 12 1999 16:25:54   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/