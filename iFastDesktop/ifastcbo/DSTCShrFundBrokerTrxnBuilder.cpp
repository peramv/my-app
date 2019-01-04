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
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : DSTCShrFundBrokerTrxnBuilder.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 2004
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCShrFundBrokerTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "dstcshrfundbrokertrxnbuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "shrfundBroker.hpp"
#include "shrfundBrokerlist.hpp"
#include "shareholder.hpp"

#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0328_req.hpp>
#include <ifastdataimpl\dse_dstc0328_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0328_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SHR_FUND_BROKER_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_("DSTCShrFundBrokerTrxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
}

//******************************************************************************
void DSTCShrFundBrokerTrxnBuilder::buildTrxnKey (DString& dstrKey) 
{
}

//******************************************************************************
SEVERITY DSTCShrFundBrokerTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
																			 BFAbstractCBO *pObj, 
																			 HostTransactionContainer *pTrCont, 
																			 BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   Shareholder* pShareholder = dynamic_cast<Shareholder*>(pObj);
	
   if( NULL != pShareholder )
   {
      ShrFundBrokerList *pShrFundBrokerList = NULL;
      
		if ( pShareholder->getShrFundBrokerList( pShrFundBrokerList, 
															  I_( "" ),
                                               I_( "" ),
			                                      BF::HOST,
															  false ) <= WARNING &&                                               
           NULL != pShrFundBrokerList )
		{
			DString dstrShareholderNum, dstKeyTypes;			
         pShareholder->getField( ifds::ShrNum, dstrShareholderNum, BF::HOST );
         addIDITagValue( dstKeyTypes, KEYTYPES::SHRNUM, dstrShareholderNum );


         std::vector<BFFieldId> fields;

			fields.push_back(ifds::ShrNum);
			DSTCListTrxnBuilder<ShrFundBroker*> ShrFundBrokerListTrxnBuilder;
               
         TRXNINFO ShrFundBrokerTrxnInfo( I_("ShrFundBroker"), 																		
													  DSTC_REQUEST::SHR_FUND_BROKER_UPDATE,
													  ifds::DSTC0328_REQ,
													  ifds::DSTC0328_REQRepeat_Record,
													  ifds::DSTC0328_VW,
													  fields );

         ShrFundBrokerListTrxnBuilder.buildTransactions( workSession, 
		 																   pTrCont, 
																			pShrFundBrokerList, 
  																			ShrFundBrokerTrxnInfo,
                                                         objActivity,
                                                         dstKeyTypes ); 			
      }
   }	

   return GETCURRENTHIGHESTSEVERITY();
}



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCShrFundBrokerTrxnBuilder.cpp-arc  $
// 
//    Rev 1.4   Apr 27 2005 14:06:00   porteanm
// Incident 283312 - Changed field name from ShareholderNum to ShrNum for 327 req, 328 req in order to support NASU flow.
// 
//    Rev 1.3   Dec 10 2004 19:22:48   vadeanum
// PET1117_FN21: settlement instructions.
// 
//    Rev 1.2   Nov 28 2004 14:06:20   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support 
// 
//    Rev 1.1   Nov 14 2004 14:33:44   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Nov 04 2004 17:24:44   VADEANUM
// Initial revision.
//
