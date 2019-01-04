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
// ^FILE   : DSTCContractMatInstrTrxnBuilder.cpp
// ^AUTHOR : Chetan Balepur
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCContractMatInstrTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCListTrxnBuilder.hpp"
#include "DSTCWorkSession.hpp"
#include "ContractMaturityInstruction.hpp"
#include "ContractMaturityInstructionList.hpp"
#include "MFAccount.hpp"

#include <ifastdataimpl\dse_dstc0431_req.hpp>
#include <ifastdataimpl\dse_dstc0431_reqrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0431_vw.hpp>
#include "DSTCContractMatInstrTrxnBuilder.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CONTRACT_MATURITY_INSTR_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCContractMatInstrTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFDecimalFieldId BankAcctVer;
	//extern CLASS_IMPORT const BFTextFieldId ContractType;
	//extern CLASS_IMPORT const BFDecimalFieldId ContractTypeId;
}

namespace KEYTYPES
{
	extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
	extern CLASS_IMPORT I_CHAR * const ENTITYID;
}

namespace TRXNTAG
{
	extern const I_CHAR* CONTRACTMATINSTRTAG;
}

//******************************************************************************
SEVERITY DSTCContractMatInstrTrxnBuilder::buildTransactions(	DSTCWorkSession &workSession,
																BFAbstractCBO* pObj,
																HostTransactionContainer* pTrCont, 
																BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));

   SEVERITY severity = SEVERE_ERROR;

   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);
   if( pMFaccount )
   {
	ContractMaturityInstructionList* pContractMaturityInstructionList = NULL;
	ContractMaturityInstruction* pContractMaturityInstruction = NULL;

	DString dstrAccountNum, dstTrnKey, dstKeyTypes;
	pMFaccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );

	addIDITagValue( dstTrnKey,   TRXNTAG::CONTRACTMATINSTRTAG,	dstrAccountNum.stripLeading('0').strip() );
	addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM,			dstrAccountNum );

	HostTransactionContainerIterator iterTrxnContList( pTrCont );
	iterTrxnContList.walkStrKey( dstTrnKey );
	iterTrxnContList.walkTrxnGroup( NO_GROUP );
	iterTrxnContList.walkTrxnSubType( 0 );

	DString dstrCotAcctRid;
	severity = pMFaccount->getContractMaturityInfoList(pContractMaturityInstructionList, dstrAccountNum, dstrCotAcctRid, I_(""), I_(""), BF::HOST, false);

	if ( (severity <= WARNING ) && (pContractMaturityInstructionList != NULL) )
	{
		BFData *pDataReq = NULL;
		BFData *pDataRes = NULL;

		BFObjIter iterContMatInstr( *pContractMaturityInstructionList, BF::HOST );
		ContractMaturityInstruction* pContractMaturityInstruction = NULL;

		iterContMatInstr.begin();
		while( !iterContMatInstr.end() )
		{
			pContractMaturityInstruction = dynamic_cast<ContractMaturityInstruction*>( iterContMatInstr.getObject() );

			if(iterContMatInstr.hasTransactionUpdates() )
			{
				iterTrxnContList.begin();

				//fill in the fixed area
				if( iterTrxnContList.end() )
				{
					pDataReq = new BFData( ifds::DSTC0431_REQ );
					pDataRes = new BFData( ifds::DSTC0431_VW );

					DString mgmtCoId;
					workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

					DString strTrack, strActivity;
					pContractMaturityInstructionList->getTrackActivity(strTrack, strActivity);

					pDataReq->setElementValue( ifds::Track,			strTrack,	 false, false ); //fill in the request update
					pDataReq->setElementValue( ifds::Activity,		strActivity, false, false ); //fill in the request update
					pDataReq->setElementValue( ifds::CompanyId,		mgmtCoId );
					pDataReq->setElementValue( ifds::AccountNum,	dstrAccountNum );			 //Mandatory for update
					pDataReq->setElementValue( ifds::CotAcctRid,	dstrCotAcctRid );			 //Mandatory for update

					const BFObjectKey& bfKey = iterContMatInstr.getKey();

					DString dstrEntityId; 
					pContractMaturityInstruction->getField(ifds::EntityId, dstrEntityId, BF::HOST);
					addIDITagValue (dstKeyTypes, KEYTYPES::ENTITYID, dstrEntityId);

					JData *jdata = new JData( DSTC_REQUEST::CONTRACT_MATURITY_INSTR_UPDATE, pDataReq, pDataRes );

					pTrCont->addTransaction (dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes);

				}
				else {
					pDataRes = (*iterTrxnContList)->getRequestDataObject();
				}

				//create a repeat for the request and fill it in
				BFData repeat( ifds::DSTC0431_REQRepeat_Record);

				//fill in the request update
				pContractMaturityInstruction->getData( repeat, BF::HOST );
            DString dstrBankAcctVer;
            pContractMaturityInstruction->getField(ifds::BankAcctVer, dstrBankAcctVer, BF::HOST, false);
            repeat.setElementValue(ifds::BankAcctVersion, dstrBankAcctVer);
				//set the RunMode field to the address trxn
				DSTCWorkSession::setRunMode( &repeat, iterContMatInstr.getKey().getActivity() );

				//add the lDataRepeat to the request
				pDataReq->addRepeat( repeat );
				DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );
				pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );

			}//end of if( iterContMatInstr.hasTransactionUpdates() )

			//move to the next
			++iterContMatInstr;

		}//end of while( !iterContMatInstr.end() )
	}

   }//end of - if( pMFaccount )

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCContractMatInstrTrxnBuilder.cpp-arc  $
// 
//    Rev 1.4   03 Aug 2012 14:37:32   if991250
// IN3020460 : sending the correct BankAcctVersion in vw431
// 
//    Rev 1.3   Mar 22 2012 18:37:20   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.2   Mar 16 2012 17:45:40   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.1   Mar 02 2012 16:37:26   wp040100
// P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
// 
//    Rev 1.0   Feb 21 2012 15:38:34   wp040100
// Initial revision.
// 
//
*
*
 */
