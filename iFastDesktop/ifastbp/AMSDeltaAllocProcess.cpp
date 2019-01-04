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
//    Copyright 2002 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AMSDeltaAllocProcess.cpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : Jan 10,2018
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AMSDeltaAllocProcess
//
//******************************************************************************

#include "stdafx.h"
#include "AMSDeltaAllocProcess.hpp"
#include "AMSDeltaAllocProcessIncludes.h"
#include <ifastcbo\AmsFundAllocList.hpp>
#include <ifastcbo\DefFundAllocList.hpp>
#include <ifastcbo\AMSDeltaAllocList.hpp>
#include <ifastcbo\AMSDeltaAlloc.hpp>
#include <ifastcbo\DefFundAlloc.hpp>
#include <ifastcbo\AMSAcctLvl.hpp>
#include <ifastcbo\AMSAcctLvlList.hpp>
#include "mfcaninterprocparam.hpp"
#include "confirmationprocessincludes.h"
#include <ifastcbo\AmsMstrlist.hpp>
#include <ifastcbo\AmsMstrInfo.hpp>
#include <ifastcbo\mfaccount.hpp>

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AMS_DELTA_ALLOC;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AMS_DELTA_ALLOC;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator<AMSDeltaAllocProcess> processCreator(CMD_BPROC_AMS_DELTA_ALLOC);

namespace CND
{
  extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
  const I_CHAR * const CLASSNAME = I_("AMSDeltaAllocProcess");
}

namespace AMS_DELTA_ALLOC_Para
{
  const I_CHAR * const AMS_CODE            = I_("AMSCode");
  const I_CHAR * const AMS_TYPE            = I_("AMSType");
  const I_CHAR * const AMS_EFFECTIVE_DATE  = I_("EffectiveDate");
  const I_CHAR * const ACCOUNT_NUM         = I_("AccountNum");
  const I_CHAR * const AMS_REC_ID          = I_("AMSRecId");
  const I_CHAR * const AMS_SEARCH_DATE     = I_("AMSSearchDate");
  const I_CHAR * const AMS_SEARCH_CODE     = I_("AMSSearchCode");
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AMSDeltaAllocProcess::AMSDeltaAllocProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess(pGIC, pGIParent, rCommand)
,_rpChildGI(NULL)
,_pAMSDeltaAllocList(NULL)
,_pFundAllocList(NULL)
,_pAmsMstrList(NULL)
,_pAmsMstrInfo(NULL) 
,_pAMSAcctLvl(NULL)
{
  TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
  addContainer(IFASTBP_PROC::AMS_DELTA_ALLOC_LIST, true, BF::NullContainerId, true, I_("AMSDeltaAllocList"));

  //AMS_DELTA_ALLOC_LIST  
  addFieldDetails(ifds::Status, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::ToFundNumber, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::FundCode, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::ClassCode, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::AllocPercentage, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::AMSCode, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::AccountNum, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::AMSType, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::AMSAllocDelta, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::ProcessDate, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::Username, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::ModDate, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);
  addFieldDetails(ifds::ModUser, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST);

  addFieldDetails(ifds::TotPercentage, BF::NullContainerId, SUBCLASS_PROCESS);
  addFieldDetails(AMS_DELTA::oldDeltaPrcnt, BF::NullContainerId, SUBCLASS_PROCESS);
  addFieldDetails(ifds::EffectiveDate, IFASTBP_PROC::AMS_DELTA_ALLOC_LIST, SUBCLASS_PROCESS);
}

//******************************************************************************
AMSDeltaAllocProcess::~AMSDeltaAllocProcess()
{
  TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY AMSDeltaAllocProcess::doInit()
{
  MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION,CLASSNAME,I_("doInit"));
  SEVERITY sevRtn = NO_CONDITION;

  getParameter(AMS_DELTA_ALLOC_Para::AMS_EFFECTIVE_DATE, _dstrEffectiveDate);
  getParameter(AMS_DELTA_ALLOC_Para::AMS_CODE, _dstrAmsCode);
  getParameter(AMS_DELTA_ALLOC_Para::AMS_TYPE, _dstrAmsType);
  getParameter(AMS_DELTA_ALLOC_Para::ACCOUNT_NUM, _dstrAccountNum);
  getParameter(AMS_DELTA_ALLOC_Para::AMS_SEARCH_DATE, _dstrCurDeff);
  getParameter(AMS_DELTA_ALLOC_Para::AMS_SEARCH_CODE, _dstrCurAmsCode);
  _dstrEffectiveDate.strip();
  _dstrAmsCode.strip().upperCase();
  _dstrAccountNum.strip();
   
  DString tmp;
  DSTCommonFunctions::UnformatDate(_dstrEffectiveDate, tmp);
  _dstrEffectiveDate = tmp;

  return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool AMSDeltaAllocProcess::doModelessChildComplete(const Command &cmd)
{
  // End when GUI ends
  return(cmd.getKey() == CMD_BPROC_AMS_DELTA_ALLOC);
}

//******************************************************************************
bool AMSDeltaAllocProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  
  // This is implemented to pass set focus on to child dialog.
  bool bRtn = false;
  try
  {
    assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
  }
  catch(ConditionException &ce)
  {
    MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus"));
    SETCONDITIONFROMEXCEPTION(ce);
  }
  catch(...)
  {
    assert(0);
    THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION);
  }

  return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN AMSDeltaAllocProcess::doProcess()
{  
  MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
  E_COMMANDRETURN rtn = CMD_FAILURE;

  try
  {
    if(!bfutil::isServerContext())
    {
      setParameter(AMS_DELTA_ALLOC_Para::AMS_CODE, _dstrAmsCode);
      setParameter(AMS_DELTA_ALLOC_Para::AMS_TYPE, _dstrAmsType);
      setParameter(AMS_DELTA_ALLOC_Para::AMS_EFFECTIVE_DATE, _dstrEffectiveDate);
      setParameter(AMS_DELTA_ALLOC_Para::AMS_SEARCH_DATE, _dstrCurDeff);
      setParameter(AMS_DELTA_ALLOC_Para::ACCOUNT_NUM, _dstrAccountNum);
      setParameter(AMS_DELTA_ALLOC_Para::AMS_SEARCH_CODE, _dstrCurAmsCode);

      rtn = invokeCommand(this, CMD_GUI_AMS_DELTA_ALLOC, getProcessType(), isModal(), &_rpChildGI);
    }
    else
    {
      rtn = CMD_MODELESS_INPROCESS;
    }
  }
  catch(ConditionException &ce)
  {
    assert(0);
    SETCONDITIONFROMEXCEPTION(ce);
  }
  catch(...)
  {
    assert(0);
    THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION);
  }

  return(rtn);
}

//******************************************************************************
void AMSDeltaAllocProcess::doGetField(const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      DString &strValueOut,
                                      bool bFormatted ) const
{
  if(idContainer == IFASTBP_PROC::AMS_DELTA_ALLOC_LIST)
  {
    if(idField == ifds::EffectiveDate)
    {
      if(_pAMSDeltaAllocList)
        _pAMSDeltaAllocList->getField(ifds::EffectiveDate, strValueOut, idDataGroup);
    }
  }
  if(idField == ifds::TotPercentage)
  {
    if(_pAMSDeltaAllocList)
      _pAMSDeltaAllocList->getTotalDeltaPrcnt(strValueOut, idDataGroup);
  }
}

//******************************************************************************
void* AMSDeltaAllocProcess::getPtrForContainer(const BFContainerId& idContainer, const BFDataGroupId& idDataGroup)
{
  void *ptr = NULL;
  SEVERITY sevRtn = NO_CONDITION;
  DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession*>(getBFWorkSession());
  MFAccount *pMFAccount = NULL;

  try
  {
    if(IFASTBP_PROC::AMS_DELTA_ALLOC_LIST == idContainer)
    {
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession*>(getBFWorkSession());
      if(_dstrAccountNum != I_("0") && _dstrAmsCode == I_("0001"))
      {
        dstcWorkSession->getMFAccount(idDataGroup, _dstrAccountNum, pMFAccount);
        if (NULL != pMFAccount)
        {
          if(!_pAMSAcctLvl)
          {
            AMSAcctLvlList *pAMSAcctLvlList = NULL;
            if(pMFAccount->getAMSAcctLvlList(idDataGroup, pAMSAcctLvlList, true) && NULL != pAMSAcctLvlList)
            {
              BFObjIter iter(*pAMSAcctLvlList, idDataGroup);
              AMSAcctLvl *pAMSAcctLvl = dynamic_cast <AMSAcctLvl*> (iter.getObject());
              if(pAMSAcctLvl)
                _pAMSAcctLvl = pAMSAcctLvl;
            }
          }
          _pAMSAcctLvl->getAMSDeltaAllocList(_pAMSDeltaAllocList, idDataGroup);
          setContainer(IFASTBP_PROC::AMS_DELTA_ALLOC_LIST, _pAMSDeltaAllocList); 
          ptr = _pAMSDeltaAllocList;
        }
      }
      else
      {
        sevRtn = dstcWorkSession->getAMSMstrList(_pAmsMstrList, _dstrAmsType, _dstrCurAmsCode, _dstrCurDeff, idDataGroup, true, false);
        _pAmsMstrList->getAMSMstrInfo(_dstrAmsType, _dstrAmsCode, _dstrEffectiveDate, _pAmsMstrInfo, idDataGroup);
        _pAmsMstrInfo->getAMSDeltaAllocList(_pAMSDeltaAllocList, idDataGroup);

        setContainer(IFASTBP_PROC::AMS_DELTA_ALLOC_LIST, _pAMSDeltaAllocList); 
        ptr = _pAMSDeltaAllocList;
      }
    }
  }
  catch(ConditionException &)
  {
    throw;
  }
  catch(...)
  {
    assert( 0 );
    THROWFROMFILE2(CND::BPBASE_CONDITION,CLASSNAME,DOINIT,
    CND::BP_ERR_UNKNOWN_EXCEPTION);
  }

  return(ptr);
}

//******************************************************************************
SEVERITY AMSDeltaAllocProcess::doValidateAll(BFAbstractCBO *rpWSD,const BFDataGroupId& idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION,CLASSNAME,I_("doValidateAll"));
  SEVERITY sevReturn = NO_CONDITION;
  if(_pAMSDeltaAllocList)
    sevReturn = _pAMSDeltaAllocList->validateAll( idDataGroup );

  return(GETCURRENTHIGHESTSEVERITY());
}