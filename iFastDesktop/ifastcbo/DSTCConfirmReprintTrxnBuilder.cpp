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
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : DSTCConfirmReprintTrxnBuilder.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : May 2005
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCConfirmReprintTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCConfirmReprintTrxnBuilder.hpp"
#include "confirmreprint.hpp"
#include "opcconfirmreprint.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0346_req.hpp>
#include <ifastdataimpl\dse_dstc0346_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CONFIRM_REPRINT_UPDATE;
}

// Fields that are not part of the above views
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId OPCConfirmReprint; 
}

namespace
{
   const I_CHAR* CLASSNAME         = I_( "DSTCConfirmReprintTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

//******************************************************************************
SEVERITY DSTCConfirmReprintTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
														   BFAbstractCBO *pObj, 
														   HostTransactionContainer *pTrCont, 
														   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   ConfirmReprint *pConfirmReprint = dynamic_cast<ConfirmReprint*> (pObj);
   if ( NULL != pConfirmReprint )
   {
		DString dstrRunMode, 
			    dstrTransId, 
				dstrClientCopy, 
				dstrBrokerCopy, 
				dstrSalesRepCopy;
		
		dstrTransId = pConfirmReprint->getTransId();

		pConfirmReprint->getField( ifds::OPCConfirmReprint, dstrRunMode,      BF::HOST );
		pConfirmReprint->getField( ifds::ClientCopy,        dstrClientCopy,   BF::HOST );
		pConfirmReprint->getField( ifds::BrokerCopy,        dstrBrokerCopy,   BF::HOST );
		pConfirmReprint->getField( ifds::SalesRepCopy,      dstrSalesRepCopy, BF::HOST );

		if ( I_( "D" ) == dstrRunMode )
			objActivity = OBJ_ACTIVITY_DELETED;
		else if ( I_( "A" ) == dstrRunMode )
			objActivity = OBJ_ACTIVITY_ADDED;

		BFData* pDataReq = new BFData (ifds::DSTC0346_REQ);
        BFData* pDataRes = new BFData (ifds::DSTC0346_VW);      

		DString dstrMgmtCo, dstrTrack, dstrActivity;		           
        workSession.getMgmtCo().getField(ifds::CompanyId, dstrMgmtCo, BF::HOST);
		pConfirmReprint->getTrackActivity( dstrTrack,  dstrActivity );    

        pDataReq->setElementValue( ifds::CompanyId,    dstrMgmtCo,       false, false);
        pDataReq->setElementValue( ifds::Track,        dstrTrack,        false, false);
        pDataReq->setElementValue( ifds::Activity,     dstrActivity,     false, false);         
		pDataReq->setElementValue( ifds::RunMode,      dstrRunMode,      false, false);
		pDataReq->setElementValue( ifds::TransId,      dstrTransId,      false, false);
        pDataReq->setElementValue( ifds::ClientCopy,   dstrClientCopy,   false, false);
		pDataReq->setElementValue( ifds::BrokerCopy,   dstrBrokerCopy,   false, false);
		pDataReq->setElementValue( ifds::SalesRepCopy, dstrSalesRepCopy, false, false);

		DString dstrKeyTypes;
		JData *jdata = new JData( DSTC_REQUEST::CONFIRM_REPRINT_UPDATE, pDataReq, pDataRes );
        pTrCont->addTransaction( I_( "ConfirmReprint" ), jdata, objActivity, NOT_PERSISTENT, dstrKeyTypes );
			
		DSTCWorkSession::setRunMode( pDataReq, objActivity );	
		//fixed "Aimprod RTS error 9: Extract error for LOGICAL field ClientCopy=''" - IN#1608629
		//this is a 'quick fix' - in my opinion ConfirmReprint should be re-designed to comply with the framework requirements
		workSession.deleteOPCConfirmReprint();
   }
  
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCConfirmReprintTrxnBuilder.cpp-arc  $
// 
//    Rev 1.3   04 Mar 2009 15:53:56   kovacsro
// IN#1608629 - Aimprod RTS error 9
// 
//    Rev 1.2   May 31 2005 16:04:26   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.1   May 25 2005 15:02:54   porteanm
// PET OPC Confirm Reprint update support.
// 
//    Rev 1.0   May 24 2005 12:33:32   porteanm
// Initial revision.
// 
