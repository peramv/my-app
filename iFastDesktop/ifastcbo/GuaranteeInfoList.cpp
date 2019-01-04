//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : GuaranteeInfoList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/18/2000
//
// ^CLASS    : GuaranteeInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "guaranteeinfolist.hpp"
#include "guaranteeinfo.hpp"
#include <ifastdataimpl\dse_dstc0106_vw.hpp>
#include <ifastdataimpl\dse_dstc0106_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest GUARANTEEINFO;
}

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "GuaranteeInfoList" );
}

// *********************************************************************************
GuaranteeInfoList::GuaranteeInfoList( BFAbstractCBO &parent ) : 
MFCanBFCbo( parent ),
_requestData(ifds::DSTC0106_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

// *********************************************************************************
GuaranteeInfoList::~GuaranteeInfoList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

// *********************************************************************************
SEVERITY GuaranteeInfoList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData( DSTC_REQUEST::GUARANTEEINFO, 
		           _requestData, ifds::DSTC0106_VW, 
				   DSTCRequestor(getSecurity(), 
				   false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY GuaranteeInfoList::init( const DString& dstrGuarSummRecId,
                                  const DString& dstrTrack,
                                  const DString& dstrPageName   )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );      
   DString mgmtCoIdOut, 
      strGuarSummRecId (dstrGuarSummRecId);
   
   strGuarSummRecId.stripLeading ('0');
   if (!strGuarSummRecId.empty())
   {
      _requestData.setElementValue( ifds::CompanyId,       getMgmtCoId( mgmtCoIdOut ) );     
      _requestData.setElementValue( ifds::SegGuarMatRecId, dstrGuarSummRecId ); 
      _requestData.setElementValue( ifds::Track,           dstrTrack );
      _requestData.setElementValue( ifds::Activity,        dstrPageName );

      ReceiveData( DSTC_REQUEST::GUARANTEEINFO, 
	               _requestData, 
   				   ifds::DSTC0106_VW, 
	   			   DSTCRequestor(getSecurity()) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY GuaranteeInfoList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = new GuaranteeInfo ( *this );
   ( ( GuaranteeInfo* ) ( pObjOut ) )->init( data);
   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeInfoList.cpp-arc  $
 * 
 *    Rev 1.18   Jun 28 2006 19:53:08   popescu
 * Incident# 655992 - fixed crash in GuaranteeInfo screen when resizing
 * 
 *    Rev 1.17   Sep 02 2005 12:12:18   porteanm
 * Incident 393611 - Removed getStrKey() in order to keep the view sorting.
 * 
 *    Rev 1.16   Aug 17 2005 16:30:24   porteanm
 * Incident 351033 - Layout change.
 * 
 *    Rev 1.15   Nov 14 2004 14:43:44   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.14   Mar 21 2003 18:12:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:54:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Aug 29 2002 12:56:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   22 May 2002 18:28:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   Dec 13 2001 16:26:10   ZHANGCEL
 * Remove function doCreateNewObject()
 * 
 *    Rev 1.9   11 May 2001 12:54:20   HSUCHIN
 * Session management restructuring
 * 
 *    Rev 1.8   May 11 2001 11:21:02   OLTEANCR
 * unchanged
 * 
 *    Rev 1.7   Jan 18 2001 16:05:14   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.6   Dec 17 2000 20:23:46   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.5   Dec 06 2000 11:41:56   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.4   Nov 06 2000 10:03:36   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.3   Mar 30 2000 15:21:28   ZHANGCEL
 * Modification for getMore
 * 
 *    Rev 1.2   Mar 10 2000 14:51:22   ZHANGCEL
 * Updated
 * 
 *    Rev 1.1   Mar 09 2000 14:08:02   ZHANGCEL
 * Improved revision
 * 
 *    Rev 1.0   Feb 15 2000 11:00:00   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Jan 28 2000 14:36:28   ZHANGCEL
// Initial revision.
 * 
 *
 */