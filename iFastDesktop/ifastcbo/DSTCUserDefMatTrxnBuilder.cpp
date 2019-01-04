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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE  : DSTCUserDefMatTrxnBuilder.cpp
// ^CLASS : DSTCUserDefMatTrxnBuilder
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "UserDefMat.hpp"
#include "UserDefMatList.hpp"
#include "DSTCUserDefMatTrxnBuilder.hpp"
#include "contractinfo.hpp"
#include "contractinfolist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0340_req.hpp>
#include <ifastdataimpl\dse_dstc0340_vw.hpp>
#include <ifastdataimpl\dse_dstc0341_req.hpp>  // User Def Mat Update (Single Record)
#include <ifastdataimpl\dse_dstc0341_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest USER_DEF_MAT_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCUserDefMatTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace DBR
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCUserDefMatTrxnBuilder::buildTrxnKey( DString& strKey, 
											  MFAccount* pMFAccount,
											  ContractInfo *pContractInfo )
{
   DString dstrAccountNum;
   pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
   dstrAccountNum.stripLeading( '0' ).strip();
   DString dstrContractType;
	pContractInfo->getField( ifds::ContractType, dstrContractType, BF::HOST );
   addIDITagValue( strKey, I_("UserDefMatAccountNum"), dstrAccountNum );
   addIDITagValue( strKey, I_("ContractType"), dstrContractType);

   // This is how is supposed to work -> Only 1 User Def Mat Dates List for all contracts
   /*
   DString dstrContractType;
   pContractInfo->getField( ifds::ContractType, dstrContractType, BF::HOST );
   dstrContractType.stripAll().upperCase();
   addIDITagValue( strKey, I_("UserDefMatAccountNum"), dstrContractType );	
   */
}

//******************************************************************************

SEVERITY DSTCUserDefMatTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                       BFAbstractCBO* pObj,
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);
   UserDefMatList* pUserDefMatList = NULL;
   UserDefMat* pUserDefMat = NULL;
   BF_OBJ_ACTIVITY listObjActivity;

   if( pMFAccount )
   {
      ContractInfoList *pContractInfoList = NULL;
      if ( pMFAccount->getContractInfoList( pContractInfoList, BF::HOST, false ) <= WARNING &&
		   NULL != pContractInfoList )
	  {
			BFObjIter iterContractList( *pContractInfoList, BF::HOST );
			iterContractList.begin();
			while( !iterContractList.end() )
            {
				ContractInfo *pContractInfo = dynamic_cast< ContractInfo* >( iterContractList.getObject() );
				DString dstrContractType;
				if ( NULL != pContractInfo )
					pContractInfo->getField( ifds::ContractType, dstrContractType, BF::HOST );
	
				severity = pMFAccount->getUserDefMatList( pUserDefMatList, BF::HOST, false, I_( "" ), dstrContractType );

				if( (pUserDefMatList != NULL) && (severity <= WARNING ) && pUserDefMatList->hasTransactionUpdates( ) )
				{
					BFObjIter iterUserDefMatList( *pUserDefMatList, BF::HOST );
					iterUserDefMatList.begin();
					while( !iterUserDefMatList.end() )
					{
						pUserDefMat = dynamic_cast< UserDefMat* >( iterUserDefMatList.getObject() );
						listObjActivity = iterUserDefMatList.getKey().getActivity();
						if( listObjActivity == OBJ_ACTIVITY_ADDED || iterUserDefMatList.hasTransactionUpdates() )
						{
							BFData* request = new BFData( ifds::DSTC0341_REQ );
							BFData* response = new BFData( ifds::DSTC0341_VW );

							pUserDefMat->getData( *request, BF::HOST );
							DString strTrack, strAvtivity;
							pUserDefMatList->getTrackActivity(strTrack, strAvtivity);
							request->setElementValue( ifds::Track, strTrack, false, false );
							request->setElementValue( ifds::Activity, strAvtivity, false, false );
							DSTCWorkSession::setRunMode( request, listObjActivity );
							DString strKey, mgmtCoId, keyTypes, dstrAccountNum;
							workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
							request->setElementValue( ifds::CompanyId, mgmtCoId );

							DSTCUserDefMatTrxnBuilder::buildTrxnKey( strKey, pMFAccount, pContractInfo ); 
							pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
							dstrAccountNum.stripLeading( '0' ).strip();
							request->setElementValue( ifds::AccountNum, dstrAccountNum, false, false );
							addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );							
							JData *jdata = new JData( DSTC_REQUEST::USER_DEF_MAT_LIST_UPDATE, request, response );
							pTrCont->addTransaction( strKey, jdata, objActivity, NOT_PERSISTENT, keyTypes );
						}  // end -- if( listObjActivity == OBJ_ACTIVITY_ADDED )

						++iterUserDefMatList;

					}  // end -- while (!iterUserDefMatList.end())         					
				}  // end -- if( pUserDefMatList != NULL && severity <= WARNING )   
				
				++iterContractList;
            // was checking only the first contract for user defined maturity dates. All need to be checked
				//break;    // This is how is supposed to work -> Only 1 User Def Mat Dates List for all contracts
			}
	  }
   }  // end -- if( pMFAccount != NULL )

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCUserDefMatTrxnBuilder.cpp-arc  $
// 
//    Rev 1.6   Apr 14 2012 09:41:46   dchatcha
// P0186484 FN05 - Contract Information screen, no need to  frequently call view during building of transation builder.
// 
//    Rev 1.5   Mar 29 2012 15:48:22   if991250
// IN 2858958: user def mat dates
// 
//    Rev 1.4   Mar 23 2012 17:10:46   if991250
// IN 2894154 - filling in the contract term
// 
//    Rev 1.3   Dec 13 2005 16:28:22   porteanm
// Incident 492179 - User Def mat Date not saved.
// 
//    Rev 1.2   Apr 14 2005 10:06:08   hernando
// PET1024 FN02 - Support modified/updated list items.
// 
//    Rev 1.1   Mar 30 2005 17:21:36   hernando
// PET1024 FN02 - Changed the key.
// 
//    Rev 1.0   Mar 20 2005 17:13:06   hernando
// Initial revision.
