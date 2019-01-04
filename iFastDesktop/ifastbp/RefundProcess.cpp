
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
//    Copyright 2005 by IFDS.
//
//******************************************************************************
//
// ^FILE   : RefundProcess.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : June 27, 2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RefundProcess
//   
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "RefundProcess.hpp"
#include "RefundProcessincludes.h"
#include <bfproc\concreteprocesscreator.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastbp\confirmationprocessincludes.h>



static ConcreteProcessCreator< RefundProcess > processCreator (CMD_BPROC_REFUND);

namespace TRANS_REFUND_PARAM
{
   const I_CHAR * const ACCOUNT_NUM             = I_("AccountNum");
   const I_CHAR * const TRANS_NUM               = I_("TransNum");
   const I_CHAR * const ESTATE_ALLOC            = I_("EstateAlloc");
   const I_CHAR * const COMMISSION_REBATE       = I_("CommissionRebate");
   const I_CHAR * const REBOOK_EXIST            = I_("ReboolExist");
   const I_CHAR * const SAMEACCOUNTTRANSTYPE    = I_("SameAccountTransType");
	const I_CHAR * const FUND_CODE               = I_("FromFund");
	const I_CHAR * const CLASS_CODE              = I_("FromClass");
	const I_CHAR * const BATCH                   = I_("Batch");
};

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_ ("RefundProcess");
   extern CLASS_EXPORT const I_CHAR * const COMMANDCANCEL = I_ ("CANCEL");
   extern CLASS_EXPORT const I_CHAR * const COMMANDOK = I_ ("OK");

};


namespace REFUND  
{
   extern CLASS_EXPORT const I_CHAR * const ACCOUNT_NUM           = I_ ("AccountNum");
   extern CLASS_EXPORT const I_CHAR * const SAMEACCOUNTTRANSTYPE  = I_ ("SameAccountTransType");
   extern CLASS_EXPORT const I_CHAR * const TRANSNUM              = I_ ("TransNum");
   extern CLASS_EXPORT const I_CHAR * const BATCH                 = I_ ("Batch");
  };


namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
};

namespace ifds
{
 
};

const I_CHAR* RefundParam_[] = 
{
   TRANS_REFUND_PARAM::ACCOUNT_NUM,
   TRANS_REFUND_PARAM::COMMISSION_REBATE,
   TRANS_REFUND_PARAM::ESTATE_ALLOC,
//   TRANS_REFUND_PARAM::REBOOK_EXIST,
   TRANS_REFUND_PARAM::TRANS_NUM,
	TRANS_REFUND_PARAM::FUND_CODE,
	TRANS_REFUND_PARAM::CLASS_CODE,
//   REFUND::SAMEACCOUNTTRANSTYPE,
   REFUND::BATCH,

   '\0'
};

const I_CHAR* RefundParamTrade_[] = 
{
   TRANS_REFUND_PARAM::ACCOUNT_NUM,
   TRANS_REFUND_PARAM::TRANS_NUM, 
	TRANS_REFUND_PARAM::FUND_CODE,
	TRANS_REFUND_PARAM::CLASS_CODE,
//   REBOOK::SAMEACCOUNTTRANSTYPE,
   MFCAN_IP_PARAM::CALLER,
//   TRANS_REFUND_PARAM::REBOOK_EXIST,
   REFUND::BATCH,
   '\0'
};


const I_CHAR* RefundConfirmParam_[] = 
{
   REFUND::SAMEACCOUNTTRANSTYPE,
   '\0'
};

struct REBOOK_PROCESS
{
   const I_CHAR* _command;
   const I_CHAR** _params;
};

//data structures for the new shareholder flow
const struct  REBOOK_PROCESS RefundProcess_[] = 
{
   CMD_BPROC_TRADES,RefundParamTrade_,
   CMD_BPROC_CONFIRMATION, RefundConfirmParam_,  
   '\0', '\0'
};


//******************************************************************************
RefundProcess::RefundProcess (GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess (pGIC, pGIParent, rCommand)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   refundParam_.AddParam(MFCAN_IP_PARAM::CALLER, I_("Refund"));
}

//******************************************************************************
RefundProcess::~RefundProcess ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY RefundProcess::doInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      getParamFromParent ( RefundParam_ );
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return NO_CONDITION;
}

//******************************************************************************
E_COMMANDRETURN RefundProcess::doProcess ()
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      const I_CHAR* command = NULL;
      int cmdindx = 0;

      while (cmdindx >= 0 && ( (command = RefundProcess_[ cmdindx ]._command) != '\0'))
      {
         setParamsForChild (RefundProcess_[ cmdindx ]._params);
         if( command == CMD_BPROC_CONFIRMATION )
         {
            setParameter( CONFPROC::PARM_CALLED_FROM, I_("REBOOK") );
         }
         rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            
         getParamFromParent (RefundProcess_[ cmdindx ]._params);
         
         if (rtn == CMD_CANCEL) //return to the previous process, if not errors
         {
           --cmdindx;
         }
         else if (rtn == CMD_OK || (rtn == CMD_MODELESS_INPROCESS && !isflowEnd ( cmdindx)))
         {
         // _nasuParams.setParameter (NASULIT::COMMANDRETURN, NASULIT::COMMANDOK);
            ++cmdindx;
         }
         else
         {
            break; 
         }
      }
   }
   catch (ConditionException &ce)
   {
      assert (0);
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return (rtn);
}

//*****************************************************************
void RefundProcess::setParamsForChild (const I_CHAR* params[])
{
   const I_CHAR* param = NULL;

   for (int i = 0; (param = params[ i ]) != '\0'; ++i)
   {
      DString value = refundParam_.getParam( DString (param) );

      if (value != NULL_STRING) //do not clear the params
      {
         setParameter (param, value);
      }
   }
}
//**********************************************************************************
void RefundProcess::getParamFromParent (const I_CHAR* params[])
{
   const I_CHAR* param = NULL;

   for (int i = 0; (param = params[ i ]) != '\0'; ++i)
   {
      DString value;
      //get parameter from parent process
      getParameter (param, value);
      if (value != NULL_STRING) 
      {
         refundParam_.AddParam(param, value);
      }
   }
}

//******************************************************************************
bool RefundProcess::isflowEnd ( int index)
{
   return RefundProcess_[ index ]._command == '\0';

}

//*******************************************************************************
RefundProcess::RefundParam::RefundParam()
{
}

//*******************************************************************************
RefundProcess::RefundParam::~RefundParam()
{
   refund_param_.clear();
}

//*******************************************************************************
void RefundProcess::RefundParam::AddParam (const DString &name, const DString &value)
{
   DString tag(name);
   tag.strip();
   if(tag != NULL_STRING )
   {
      REFUND_PARAM::iterator it = refund_param_.find (tag);
      //if( it == refundParam_.end() )
      {
         DString str (value);
         str.stripTrailing();
         refund_param_ [name] = str;
      }
   }  
}
//*******************************************************************************
void RefundProcess::RefundParam::removeParam (const DString &name )
{
   DString tag (name);
   tag.strip();
   if( tag != NULL_STRING )
   {
      REFUND_PARAM::iterator it = refund_param_.find (tag);
      if (it != refund_param_.end())
      {
         refund_param_.erase( it );      
      }   
   }
}
//*******************************************************************************
DString RefundProcess::RefundParam::getParam (const DString &name)
{
   REFUND_PARAM::const_iterator it = refund_param_.find (name);
   DString valueOut = NULL_STRING;
   if (it != refund_param_.end())
   {
      valueOut = (*it).second;
   }
   return valueOut;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*

 */





