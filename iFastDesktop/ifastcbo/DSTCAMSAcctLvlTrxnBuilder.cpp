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
// ^FILE   : DSTCAMSAcctLvlTrxnBuilder.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : June 2007
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAMSAcctLvlTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "dstcamsacctlvltrxnbuilder.hpp"
#include "dstcallocationtrxnbuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "AMSAcctLvl.hpp"
#include "AMSAcctLvllist.hpp"
#include "shralloctype.hpp"
#include "shralloctypelist.hpp"
#include "DefAcctAllocList.hpp"
#include "defacctalloc.hpp"
#include "DefFundAllocList.hpp"
#include "deffundalloc.hpp"
#include "MFAccount.hpp"
#include "DSTCAMSDeltaTrxnBuilder.hpp"

#include <ifastdataimpl\dse_dstc0381_req.hpp>
#include <ifastdataimpl\dse_dstc0381_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0381_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_ACCT_LEVEL_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME         = I_("DSTCAMSAcctLvlTrxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;	
}

namespace ifds
{  
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
}

extern BF_OBJ_TYPE OBJ_TYPE_AMS_ACCT_LEVEL;


//******************************************************************************
void DSTCAMSAcctLvlTrxnBuilder::buildTrxnKey (DString& dstrKey) 
{
}

//******************************************************************************
SEVERITY DSTCAMSAcctLvlTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
																		 BFAbstractCBO *pObj, 
																		 HostTransactionContainer *pTrCont, 
																		 BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);

   if (pMFaccount)
   {
      DString dstAccountNum, 
         dstTrnKey, 
         dstKeyTypes;
      
      pMFaccount->getField( ifds::AccountNum, dstAccountNum, BF::HOST, true );

      addIDITagValue (dstTrnKey, TRXNTAG::AMSACCTLVLTAG, dstAccountNum.stripLeading('0').strip());
      addIDITagValue (dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum);

      HostTransactionContainerIterator iterTrxnContList( pTrCont );

      iterTrxnContList.walkStrKey (dstTrnKey);
      iterTrxnContList.walkTrxnGroup (NO_GROUP);
      iterTrxnContList.walkTrxnSubType (0);

      AMSAcctLvlList  *pAMSAcctLvlList = NULL;
      if (pMFaccount->getAMSAcctLvlList(BF::HOST, pAMSAcctLvlList, false) <= WARNING && 
          pAMSAcctLvlList)
      {
         DSTCListTrxnBuilder<AMSAcctLvl*> amsAcctLvlListTrxnBuilder;

         std::vector<BFFieldId> fields;
         fields.push_back(ifds::AccountNum);
         TRXNINFO amsAcctLvlListTrxnInfo( dstTrnKey, 
                                          DSTC_REQUEST::AMS_ACCT_LEVEL_UPDATE,
                                          ifds::DSTC0381_REQ,
                                          ifds::DSTC0381_REQRepeat_Record,
                                          ifds::DSTC0381_VW,
                                          fields);

         amsAcctLvlListTrxnBuilder.buildTransactions( workSession, 
                                                      pTrCont, 
                                                      pAMSAcctLvlList, 
                                                      amsAcctLvlListTrxnInfo,
                                                      OBJ_ACTIVITY_NONE,
                                                      dstKeyTypes);

		 // set the effective date to all level to enable correct allocation setup in the backend		 
		 BFObjIter iterAMSAcctLvlList (*pAMSAcctLvlList, BF::HOST);
		 while (!iterAMSAcctLvlList.end())
		 {
			 AMSAcctLvl *pAMSAcctLvl = dynamic_cast <AMSAcctLvl*> (iterAMSAcctLvlList.getObject());
			 if(pAMSAcctLvl->isNew())
			 {
				 DString deff;
				 pAMSAcctLvl->getField (ifds::Deff, deff, BF::HOST, false);

				 DString strKey = I_("AllocationList");
				 ShrAllocTypeList* pShrAllocationList =   dynamic_cast <ShrAllocTypeList*> (pAMSAcctLvl->getObject (strKey, BF::HOST));
				 if( pShrAllocationList )
				 {
					 BFObjIter iterShrLvlAllocList (*pShrAllocationList, BF::HOST);

					 while (!iterShrLvlAllocList.end())
					 {
						 ShrAllocType* pShrAlloc = dynamic_cast <ShrAllocType*> (iterShrLvlAllocList.getObject());

						 if (pShrAlloc)
						 {
							 DefAcctAllocList* pAcctAllocList (NULL);
							 if ( pShrAlloc->getAccountAllocationList (pAcctAllocList, BF::HOST) <= WARNING && 
								 pAcctAllocList)
							 {
								 BFObjIter iterAcctLvlAllocList (*pAcctAllocList, BF::HOST);

								 while (!iterAcctLvlAllocList.end())
								 {
									 DefAcctAlloc* pAcctAlloc = dynamic_cast<DefAcctAlloc*> (iterAcctLvlAllocList.getObject());

									 DefFundAllocList *fundLvlAllocList (NULL);

									 if (pAcctAlloc->getFundAllocationList (fundLvlAllocList , BF::HOST, false) <= WARNING &&
										 fundLvlAllocList)
									 {
										 //define an iterator on the account level allocation list
										 BFObjIter iterFundLvlAllocList (*fundLvlAllocList , BF::HOST);

										 while (!iterFundLvlAllocList.end() )
										 {
											 DefFundAlloc* pFundAlloc = dynamic_cast <DefFundAlloc*>( iterFundLvlAllocList.getObject() );

											 if( pFundAlloc )
											 {
												 // set effective date
												 pFundAlloc->setField(ifds::EffectiveDate, deff, BF::HOST, false);
											 }

											 ++iterFundLvlAllocList;
										 }
									 }

									 // set effective date
									 pAcctAlloc->setField(ifds::EffectiveDate, deff, BF::HOST, false);

									 ++iterAcctLvlAllocList;
								 }
							 }

							 // set effective date
							 pShrAlloc->setField(ifds::EffectiveDate, deff, BF::HOST, false);
						 }
						 ++iterShrLvlAllocList;
					 }
				 }
				 DSTCAMSDeltaTrxnBuilder::buildTransactions(workSession, pAMSAcctLvl,pTrCont, objActivity);
			 }
			 ++iterAMSAcctLvlList;
		 }
      }
      DSTCAllocationTrxnBuilder::buildTransactions (workSession, pMFaccount, pTrCont, objActivity);
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAMSAcctLvlTrxnBuilder.cpp-arc  $
// 
//    Rev 1.8   09 Dec 2008 17:01:44   popescu
// Incident 1154478 - AMS back-date fix -  send the modify MAS date before deleting the distrib-detl.
// 
//    Rev 1.7   23 Oct 2008 15:11:20   popescu
// Incident 1154478 - AMS back-date fix
// 
//    Rev 1.6   Feb 22 2008 11:28:24   yingz
// incident 1193717 - avoid multiple ams, fund alloc >100%
// 
//    Rev 1.5   14 Sep 2007 10:59:34   popescu
// Incident 1003183 (GAP2360/02) - fixed AMS allocations
// 
//    Rev 1.4   31 Aug 2007 14:07:36   popescu
// PET 2360 FN02 - fixed issue with creating AMS during NASU flow.
// 
//    Rev 1.3   Jul 18 2007 09:35:50   smithdav
// PET2360 FN02
// 
//    Rev 1.2   Jul 11 2007 16:21:24   smithdav
// PET 2360 FN02 - AMS - Interim changes
// 
//    Rev 1.1   Jun 22 2007 14:20:14   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.0   Jun 21 2007 13:16:44   porteanm
// Initial revision.
// 
//
