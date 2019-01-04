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
// ^FILE   : DSTCShrFundSponsorAgrmntTrxnBuilder.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : June 2004
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCShrFundSponsorAgrmntTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "dstcshrfundsponsoragrmnttrxnbuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "shrfundsponsoragreement.hpp"
#include "shrfundsponsoragreementlist.hpp"
#include "shareholder.hpp"

#include <ifastdataimpl\dse_dstc0300_req.hpp>
#include <ifastdataimpl\dse_dstc0300_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0300_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SHR_FUND_SPONSOR_AGREEMENT_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_("DSTCShrFundSponsorAgrmntTrxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;	
}

extern BF_OBJ_TYPE OBJ_TYPE_SHR_FUND_SPONSOR_AGREEMENT_LIST;


//******************************************************************************
void DSTCShrFundSponsorAgrmntTrxnBuilder::buildTrxnKey (DString& dstrKey) 
{
}

//******************************************************************************
SEVERITY DSTCShrFundSponsorAgrmntTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
																					  BFAbstractCBO *pObj, 
																					  HostTransactionContainer *pTrCont, 
																					  BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

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

   return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCShrFundSponsorAgrmntTrxnBuilder.cpp-arc  $
// 
//    Rev 1.4   Apr 27 2005 14:00:32   porteanm
// Incident 283312 - Changed field name from ShareholderNum to ShrNum for 299 req, 300 req in order to support NASU flow.
// 
//    Rev 1.3   Dec 10 2004 19:23:58   vadeanum
// For NASU, setup the TrxnKey so this commit is fired up after we have the ShareholderNum.
// 
//    Rev 1.2   Nov 14 2004 14:33:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Jul 27 2004 15:27:34   VADEANUM
// PET1117 FN01 - Shareholder Static Data update support - first working version.
// 
//    Rev 1.0   Jul 26 2004 10:18:22   VADEANUM
// Initial revision.
//
