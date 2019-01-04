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
// ^FILE   : DSTCMatSweepInstrTrxnBuilder.cpp
// ^AUTHOR : Serban P.
// ^DATE   : December  2011
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCMatSweepInstrTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0429_req.hpp>
#include <ifastdataimpl\dse_dstc0429_vw.hpp>

#include "ifasthosttransactioncontainer.hpp"
#include "dstcmatsweepinstrtrxnbuilder.hpp"
#include "matsweepinstr.hpp"
#include "matsweepinstrlist.hpp"
#include "matsweepinstrdetails.hpp"
#include "matsweepinstrdetailslist.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "trade.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CASHSWEEP_MATURITY_INSTR_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCMatSweepInstrTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId MatInstrLevel;
}

//******************************************************************************
SEVERITY DSTCMatSweepInstrTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pBFCBO, 
                                                          HostTransactionContainer* pTrxnContainer, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   BFCBO *pHolder (NULL);
   MFAccount *pMFAccount = dynamic_cast <MFAccount *> (pBFCBO);
   Trade *pTrade = dynamic_cast <Trade *> (pBFCBO);
   DString tradesTransNum = NULL_STRING;

   if (pMFAccount)
   {
      pHolder = pMFAccount;
   }
   else if (pTrade)
   {
      pHolder = pTrade;
      pTrade->getField (ifds::TransNum, tradesTransNum, BF::HOST, false);
   }

   if (pHolder)
   {
      DString key (I_("MatSweepInstrList"));
      BFObjIter iterHolder (*pHolder, BF::HOST, true);

      iterHolder.positionByKey (key);

      if (!iterHolder.end())
      {
         MatSweepInstrList* pMatSweepInstrList = dynamic_cast <MatSweepInstrList*> (iterHolder.getObject ());

         if (pMatSweepInstrList)
         {
            //int count = 0;
            DString strTrack, 
               strPageName;

            pMatSweepInstrList->getTrackActivity (strTrack, strPageName);
            BFObjIter iterMatSweepInstrList (*pMatSweepInstrList, BF::HOST);

            while (!iterMatSweepInstrList.end ())
            {
               int count = 0;

               BF_OBJ_ACTIVITY objActivityMatSweepInstr =  iterMatSweepInstrList.getKey().getActivity();
               MatSweepInstr *pMatSweepInstr = dynamic_cast <MatSweepInstr*> (iterMatSweepInstrList.getObject ());

               if (pMatSweepInstr && ( objActivityMatSweepInstr == OBJ_ACTIVITY_ADDED    || 
                  objActivityMatSweepInstr == OBJ_ACTIVITY_DELETED  || 
                  pMatSweepInstr->hasTransactionUpdates()))
               {
                  bool bMatSweepInstrDeleted = objActivityMatSweepInstr == OBJ_ACTIVITY_DELETED;
                  DString trnKey, dstrKeyTypes,
                     /*transNum,*/ matSwpInstructionType,
                     fundCode, classCode,
                     accountNum;

                  pMatSweepInstr->getField (ifds::MatSwpInstructionType, matSwpInstructionType, BF::HOST);
                  pMatSweepInstr->getField (ifds::AccountNum, accountNum, BF::HOST);
                  //pMatSweepInstr->getField (ifds::TransNum, transNum, BF::HOST);
                  pMatSweepInstr->getField (ifds::Fund, fundCode, BF::HOST);
                  pMatSweepInstr->getField (ifds::Class, classCode, BF::HOST);

                  DString dstrMatInstrLevel;
                  pMatSweepInstr->getField(ifds::MatInstrLevel, dstrMatInstrLevel, BF::HOST); 
                  if (!tradesTransNum.empty () && dstrMatInstrLevel != I_("A"))
                  {
                     addIDITagValue (trnKey, I_("TransNum"), tradesTransNum);
                  }
                  addIDITagValue (trnKey, I_("AccountNum"), accountNum);
                  addIDITagValue (trnKey, I_("MatSwpInstructionType"), matSwpInstructionType);
                  addIDITagValue (trnKey, I_("FundCode"), fundCode);
                  addIDITagValue (trnKey, I_("ClassCode"), classCode);

                  HostTransactionContainerIterator iterTrxnContainer (pTrxnContainer);

                  iterTrxnContainer.walkStrKey (trnKey);
                  iterTrxnContainer.walkTrxnGroup (NO_GROUP);
                  iterTrxnContainer.walkTrxnSubType (0);
                  iterTrxnContainer.begin();

                  BFData *request = new BFData  (ifds::DSTC0429_REQ);
                  BFData *response = new BFData (ifds::DSTC0429_VW);

                  pMatSweepInstr->getData (*request, BF::HOST);
                  request->setElementValue (ifds::Track, strTrack);
                  request->setElementValue (ifds::Activity, strPageName);
                  if(dstrMatInstrLevel == I_("A"))
                  {
                     request->setElementValue (ifds::TransNum, I_(""));
                     request->setElementValue (ifds::ProcType, I_("Acct"));
                  }
                  else if (!tradesTransNum.empty ())
                  {
                     request->setElementValue (ifds::TransNum, tradesTransNum);
                  }
                  DSTCWorkSession::setRunMode (request, objActivityMatSweepInstr);

                  DString mgmtCoId;

                  workSession.getMgmtCo().getField (ifds::CompanyId, mgmtCoId, BF::HOST);
                  request->setElementValue (ifds::CompanyId, mgmtCoId);

                  JData *jdata = new JData (DSTC_REQUEST::CASHSWEEP_MATURITY_INSTR_UPDATE, request, response);
                  pTrxnContainer->addTransaction (trnKey, jdata, objActivityMatSweepInstr, NOT_PERSISTENT, dstrKeyTypes);
//build the repeats...
                  MatSweepInstrDetailsList *pMatSweepInstrDetailsList (NULL);

                  if (pMatSweepInstr->getMatSweepDetailsList (pMatSweepInstrDetailsList, BF::HOST) <= WARNING && 
                     pMatSweepInstrDetailsList)
                  {
                     BFObjIter iterMatSweepInstrDetailsList (*pMatSweepInstrDetailsList, BF::HOST);

                     while (!iterMatSweepInstrDetailsList.end ())
                     {
                        BF_OBJ_ACTIVITY objActivityMatSweepDetails =  iterMatSweepInstrDetailsList.getKey().getActivity();
                        MatSweepInstrDetails *pMatSweepInstrMatSweepDetails = 
                           dynamic_cast <MatSweepInstrDetails*> (iterMatSweepInstrDetailsList.getObject ());

                        if (pMatSweepInstrMatSweepDetails && ( objActivityMatSweepDetails == OBJ_ACTIVITY_ADDED    || 
                                                               objActivityMatSweepDetails == OBJ_ACTIVITY_DELETED  || 
                                                               pMatSweepInstrMatSweepDetails->hasTransactionUpdates() ||
															   /* When Instruction get update/delete, we need to update them to Instruction allocation details (distrib-detl)*/
                                                               ((bMatSweepInstrDeleted || pMatSweepInstr->hasTransactionUpdates(false)) &&
                                                                 objActivityMatSweepDetails == OBJ_ACTIVITY_NONE)))
                        {
                           BFData dataRepeat (ifds::DSTC0429_REQRepeat_Record);

                           if (bMatSweepInstrDeleted && objActivityMatSweepDetails == OBJ_ACTIVITY_NONE)
                           {
                              DSTCWorkSession::setRunMode (&dataRepeat, OBJ_ACTIVITY_DELETED);
                           }
                           else
                           {
                              DSTCWorkSession::setRunMode (&dataRepeat, objActivityMatSweepDetails);
                           }

                           pMatSweepInstrMatSweepDetails->getData (dataRepeat, BF::HOST);
                           request->addRepeat (dataRepeat);
                           ++count;
                           request->setElementValue(ifds::RepeatCount, DString::asString (count), false, false);
                        }

                        ++iterMatSweepInstrDetailsList;
                     }
                  }
               }
               ++iterMatSweepInstrList;
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* 
 */
