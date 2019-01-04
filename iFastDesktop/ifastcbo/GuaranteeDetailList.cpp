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
// ^FILE   : GuaranteeDetailList.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : August 2005
//
// ^CLASS    : GuaranteeDetailList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "guaranteedetaillist.hpp"
#include "guaranteedetail.hpp"

#include <ifastdataimpl\dse_dstc0351_vw.hpp>
#include <ifastdataimpl\dse_dstc0351_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest GUARANTEEDETAIL_INQUIRY;
}

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "GuaranteeDetailList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

// *********************************************************************************
GuaranteeDetailList::GuaranteeDetailList( BFAbstractCBO &parent ) : 
MFCanBFCbo( parent ),
_requestData(ifds::DSTC0351_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

// *********************************************************************************
GuaranteeDetailList::~GuaranteeDetailList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY GuaranteeDetailList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData( DSTC_REQUEST::GUARANTEEDETAIL_INQUIRY, 
		             _requestData, 
				      ifds::DSTC0351_VW, 
				      DSTCRequestor(getSecurity(), 
				      false));
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY GuaranteeDetailList::init( const BFDataGroupId &idDataGroup,
                                    const DString &dstrGuarRecId,
                                    const DString &dstrTrack,
                                    const DString &dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );      

   DString mgmtCoIdOut,
      strGuarRecId (dstrGuarRecId),
      transType;
   
   strGuarRecId.stripLeading ('0');
   assert (getParent ());
   if (getParent())
   {
      getParent ()->getField (ifds::TransType, transType, idDataGroup);
   }
   if (!strGuarRecId.empty() && DSTCommonFunctions::codeInList (transType, I_("AF,DF,PW,TO,RS,GA")))
   {
      _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );     
      _requestData.setElementValue( ifds::GuarRecId, dstrGuarRecId ); 
      _requestData.setElementValue( ifds::Track,     dstrTrack );
      _requestData.setElementValue( ifds::Activity,  dstrPageName );

      ReceiveData( DSTC_REQUEST::GUARANTEEDETAIL_INQUIRY, 
	               _requestData, 
	   			   ifds::DSTC0351_VW, 
		   		   DSTCRequestor(getSecurity()) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY GuaranteeDetailList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new GuaranteeDetail ( *this );
   ( ( GuaranteeDetail* ) ( pObjOut ) )->init( data);

   return(GETCURRENTHIGHESTSEVERITY());
}


//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeDetailList.cpp-arc  $
// 
//    Rev 1.2   Jun 29 2006 17:21:18   popescu
// Incident# 655992 - restricted the call to view 351 - GuaranteeInfoDetail to only certain trans types.
// 
//    Rev 1.1   Jun 28 2006 20:06:02   popescu
// Incident# 655992 - fixed crash in GuaranteeInfo screen when resizing
// 
//    Rev 1.1   Jun 28 2006 19:53:06   popescu
// Incident# 655992 - fixed crash in GuaranteeInfo screen when resizing
// 
//    Rev 1.0   Aug 17 2005 16:17:26   porteanm
// Initial revision.
 * 
 */