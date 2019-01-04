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
// ^FILE   : GuaranteeSummaryList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include "guaranteesummary.hpp"
#include "guaranteesummarylist.hpp"
#include "guaranteeinfolist.hpp"

#include <ifastdataimpl\dse_dstc0170_vw.hpp>
#include <ifastdataimpl\dse_dstc0170_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest GUARANTEE_SUMMARY;
}

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "GuaranteeSummaryList" );
}

// *********************************************************************************
GuaranteeSummaryList::GuaranteeSummaryList( BFAbstractCBO &parent ) : 
MFCanBFCbo( parent ),
_requestData(ifds::DSTC0170_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


// *********************************************************************************
GuaranteeSummaryList::~GuaranteeSummaryList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
SEVERITY GuaranteeSummaryList::init( const DString& dstrAccountNumber,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName   )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );     

   _dstrAccountNum = dstrAccountNumber;

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId,  getMgmtCoId( mgmtCoIdOut ) );     
   _requestData.setElementValue( ifds::AccountNum, dstrAccountNumber ); 
   _requestData.setElementValue( ifds::Track,      dstrTrack );
   _requestData.setElementValue( ifds::Activity,   dstrPageName );

   ReceiveData( DSTC_REQUEST::GUARANTEE_SUMMARY, 
	            _requestData, 
				ifds::DSTC0170_VW, 
				DSTCRequestor(getSecurity()) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY GuaranteeSummaryList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "doCreateObject( const BFData &, BFCBO *& )" ) );  

   pObjOut = new GuaranteeSummary ( *this );
   ( ( GuaranteeSummary* ) ( pObjOut ) )->init( data);

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY GuaranteeSummaryList::doCreateNewObject( BFCBO *& pBase, 
												  DString &strKey, 
												  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
      
   pBase = new GuaranteeSummary( *this );  
   ( ( GuaranteeSummary* ) ( pBase ) )->init( idDataGroup );
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY GuaranteeSummaryList::getGuaranteeInfoListByContract( const DString &dstrContractType,
	                                                           const BFDataGroupId& idDataGroup,
												               GuaranteeInfoList *&pGuaranteeInfoList,												 
                                                               const DString& dstrTrack,
                                                               const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getGuaranteeInfoListByContract" ) );
   
   pGuaranteeInfoList = NULL;
   DString contractType( dstrContractType );
   contractType.strip().upperCase();

   DString dstrkey = I_("GuaranteeInfoList; AccountNum=" ) + _dstrAccountNum 
	               + I_( "ContractType=") + contractType;

   BFObjectKey objKey( dstrkey, idDataGroup, OBJ_ACTIVITY_NONE, I_( "GuaranteeInfoList" ) );
   pGuaranteeInfoList = dynamic_cast<GuaranteeInfoList*>( findObject( objKey ) );

   if( NULL == pGuaranteeInfoList )
   {
      pGuaranteeInfoList = new GuaranteeInfoList( *this ); 

	  BFObjIter iter ( *this, 
					   idDataGroup, 
					   true);
      iter.begin();
	  SEVERITY sev = NO_CONDITION;

	  while (!iter.end())
	  {
			GuaranteeSummary *pGuaranteeSummary = dynamic_cast <GuaranteeSummary *> (iter.getObject());

			if ( NULL != pGuaranteeSummary )
			{
                DString dstrContractType, dstrSegGuarMatRecId;
				pGuaranteeSummary->getField( ifds::ContractType,    dstrContractType,    idDataGroup );				
				pGuaranteeSummary->getField( ifds::SegGuarMatRecId, dstrSegGuarMatRecId, idDataGroup );

				if ( dstrContractType.strip().upperCase() == contractType )
				{					
					sev = pGuaranteeInfoList->init( dstrSegGuarMatRecId );
					if ( sev > WARNING )
						break;
				}
			}
			++iter;
	  }

	  if ( sev <= WARNING )
		setObject( objKey, pGuaranteeInfoList );	  
	  else
	  {
		delete pGuaranteeInfoList;
		pGuaranteeInfoList = NULL;
	  }
   } 
   
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GuaranteeSummaryList.cpp-arc  $
// 
//    Rev 1.8   Jun 05 2006 16:54:18   porteanm
// Incident 635750 - Crash when no record available.
// 
//    Rev 1.7   Sep 02 2005 12:14:12   porteanm
// Incident 393611 - Removed getStrKey() in order to keep the view sorting.
// 
//    Rev 1.6   Aug 17 2005 16:34:38   porteanm
// Incident 351033 - Layout change.
 *  
 */
