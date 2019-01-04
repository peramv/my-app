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
// ^FILE   : DSTCOPCConfirmReprintTrxnBuilder.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : May 2005
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCOPCConfirmReprintTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCOPCConfirmReprintTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "opcconfirmreprint.hpp"
#include "opconlineconfirmreprint.hpp"

//#include <dataimpl\dse_dstc0346_req.hpp>
//#include <dataimpl\dse_dstc0346_reqrepeat_record.hpp>
//#include <dataimpl\dse_dstc0346_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest OPC_CONFIRM_REPRINT_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_("DSTCOPCConfirmReprintTrxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}

//extern BF_OBJ_TYPE OBJ_TYPE_SHR_FUND_SPONSOR_AGREEMENT_LIST;


//******************************************************************************
void DSTCOPCConfirmReprintTrxnBuilder::buildTrxnKey (DString& dstrKey) 
{
}

//******************************************************************************
SEVERITY DSTCOPCConfirmReprintTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
															  BFAbstractCBO *pObj, 
															  HostTransactionContainer *pTrCont, 
															  BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   /*
   Shareholder* pShareholder = dynamic_cast<Shareholder*>(pObj);
	
   if( NULL != pShareholder )
   {
      ShrFundSponsorAgreementList *pShrFundSponsorAgreementList = NULL;
      if ( pShareholder->getShrFundSponsorAgreementList( pShrFundSponsorAgreementList, 
																			I_( "" ),
			                                                BF::HOST,
																			false ) <= WARNING &&
			  NULL != pShrFundSponsorAgreementList )
		{
			DString dstrShareholderNum,dstKeyTypes;
			pShrFundSponsorAgreementList->getField( ifds::ShrNum, dstrShareholderNum, BF::HOST );
         addIDITagValue( dstKeyTypes, KEYTYPES::SHRNUM, dstrShareholderNum );

			std::vector<BFFieldId> fields;

			fields.push_back(ifds::ShrNum);
			DSTCListTrxnBuilder<ShrFundSponsorAgreement*> ShrFundSponsorAgreementListTrxnBuilder;
               
         TRXNINFO ShrFundSponsorAgreementTrxnInfo( I_("ShrFundSponsorAgreement"), 																		
																	DSTC_REQUEST::SHR_FUND_SPONSOR_AGREEMENT_LIST_UPDATE,
																	ifds::DSTC0300_REQ,
																	ifds::DSTC0300_REQRepeat_Record,
																	ifds::DSTC0300_VW,
																	fields);

         ShrFundSponsorAgreementListTrxnBuilder.buildTransactions( workSession, 
			  																			 pTrCont, 
																						 pShrFundSponsorAgreementList, 
  																						 ShrFundSponsorAgreementTrxnInfo,
                                                                   objActivity,
                                                                   dstKeyTypes ); 
			
      }
   }	
   */

   return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCOPCConfirmReprintTrxnBuilder.cpp-arc  $
// 
//    Rev 1.0   May 06 2005 14:15:24   porteanm
// Initial revision.
// 
