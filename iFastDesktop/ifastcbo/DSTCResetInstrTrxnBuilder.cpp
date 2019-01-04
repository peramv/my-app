//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : DSTCResetInstrTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : Jan 26, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : DSTCResetInstrTrxnBuilder
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcresetinstrtrxnbuilder.hpp"
#include "resetinstr.hpp"
#include "resetinstrlist.hpp"
#include "resetinstrcriteria.hpp"
#include <ifastcbo\mgmtco.hpp>
#include <ifastdataimpl\dse_dstc0244_req.hpp>
#include <ifastdataimpl\dse_dstc0244_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0244_vw.hpp>
#include <ifastcbo\dstcworksession.hpp>

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCResetInstrTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const REPORT_NAME;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESET_INSTR_UPDATE;
}
/*
const BFFieldId fieldsInReportInstr[]=
{
   ifds::AccountNum,
   ifds::FundCode,
   ifds::ClassCode,
   ifds::ResetDate,
   ifds::ResetType,
   ifds::CanResetId,
   ifds::BatchEffective,   
   ifds::BatchName,   
   ifds::Trace,   
   ifds::Version,   
   ifds::ProtContractRId,
};

static const int numfieldsInReportInstr = sizeof( fieldsInReportInstr ) / sizeof( BFFieldId );
*/

//******************************************************************************
void DSTCResetInstrTrxnBuilder::buildTrxnKey( DString& strKey  )
{   
   strKey = I_("ResetInstr");
}

//******************************************************************************
SEVERITY DSTCResetInstrTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                 BFAbstractCBO* pObj,
                                                 HostTransactionContainer* pTrCont,
                                                 BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{

  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   SEVERITY severity = SEVERE_ERROR;
   ResetInstrList* pResetInstrList = dynamic_cast<ResetInstrList*>(pObj);

   if(pResetInstrList != NULL)
   {
      DString dstTrnKey, dstKeyTypes;

      DSTCResetInstrTrxnBuilder::buildTrxnKey(dstTrnKey);
      HostTransactionContainerIterator iterTrxnContList( pTrCont );
      
      iterTrxnContList.walkStrKey(dstTrnKey);
      iterTrxnContList.walkTrxnGroup(NO_GROUP);
      iterTrxnContList.walkTrxnSubType( 0 );

      //define an interator on the protected fund list
      BFObjIter iter(*pResetInstrList, BF::HOST);
      BFData *pDataReq = NULL;
      BFData *pDataRes = NULL;
      
      iter.begin();
      ResetInstr* pResetInstr;
      while(!iter.end())
      {
         if(iter.hasTransactionUpdates())
         {
            pResetInstr = dynamic_cast <ResetInstr*>(iter.getObject());
            iterTrxnContList.begin();
            //fill in the fixed area, didn't find the request in the container
            if(iterTrxnContList.end())
            {
               DString strTrack, strActivity, mgmtCoId;                  
               //populate the fixed session
               pDataReq = new BFData(ifds::DSTC0244_REQ);
               pDataRes = new BFData(ifds::DSTC0244_VW);
               pResetInstr->getTrackActivity(strTrack, strActivity);
               pDataReq->setElementValue( ifds::Track, strTrack, false, false );
               pDataReq->setElementValue( ifds::Activity, strActivity, false, false );
               //continue to fill in the request update, 
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
            
               JData *jdata = new JData(DSTC_REQUEST::RESET_INSTR_UPDATE, pDataReq, pDataRes);
               pTrCont->addTransaction( dstTrnKey, jdata, objActivity, NOT_PERSISTENT, dstKeyTypes );
            }
            else
            {
               pDataReq = (*iterTrxnContList)->getRequestDataObject();
            }
            //create a repeat for the request and filled it in
            BFData repeat( ifds::DSTC0244_REQRepeat_Record);
            
            //fill in the request update, only the part for which the Remarks is responsible
            pResetInstr->getData( repeat, BF::HOST );
            //set the RunMode field to the trxn
            DSTCWorkSession::setRunMode( &repeat, iter.getKey().getActivity() );

            //add the repeat to the request
            pDataReq->addRepeat( repeat );
         
            DString dstRepeats = DString::asString( pDataReq->getRepeatCount() );

            pDataReq->setElementValue( ifds::RepeatCount, dstRepeats );
         }
         ++iter; //while(!iter.end())
      }  
   } 
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCResetInstrTrxnBuilder.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:33:20   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Mar 21 2003 18:06:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Jan 27 2003 07:39:54   HSUCHIN
// resetinstrlist now belongs to worksession
// 
//    Rev 1.0   Jan 26 2003 15:31:50   HSUCHIN
// Initial Revision
*/