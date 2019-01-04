
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
// ^FILE   : RebookProcess.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : June 27, 2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RebookProcess
//   
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "RebookProcess.hpp"
#include "RebookProcessincludes.h"
#include "RebookParamProcessIncludes.h"
#include <bfproc\concreteprocesscreator.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastbp\confirmationprocessincludes.h>



static ConcreteProcessCreator< RebookProcess > processCreator (CMD_BPROC_REBOOK);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_ ("RebookProcess");
   extern CLASS_EXPORT const I_CHAR * const COMMANDCANCEL = I_ ("CANCEL");
   extern CLASS_EXPORT const I_CHAR * const COMMANDOK = I_ ("OK");

};


namespace REBOOK  
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

const I_CHAR* RebookParam_[] = 
{
   TRANS_REBOOK_PARAM::ACCOUNT_NUM,
   TRANS_REBOOK_PARAM::COMMISSION_REBATE,
   TRANS_REBOOK_PARAM::ESTATE_ALLOC,
   TRANS_REBOOK_PARAM::REBOOK_EXIST,
   TRANS_REBOOK_PARAM::TRANS_NUM,
	TRANS_REBOOK_PARAM::FUND_CODE,
	TRANS_REBOOK_PARAM::CLASS_CODE,
   REBOOK::SAMEACCOUNTTRANSTYPE,
   REBOOK::BATCH,
   TRANS_REBOOK_PARAM::REBOOK_COPY,

   '\0'
};

const I_CHAR* ToRebookParam_[] = 
{
   TRANS_REBOOK_PARAM::ACCOUNT_NUM,
   TRANS_REBOOK_PARAM::COMMISSION_REBATE,
   TRANS_REBOOK_PARAM::ESTATE_ALLOC,
   TRANS_REBOOK_PARAM::REBOOK_EXIST,
   TRANS_REBOOK_PARAM::TRANS_NUM,  
	TRANS_REBOOK_PARAM::FUND_CODE,
	TRANS_REBOOK_PARAM::CLASS_CODE,
   REBOOK::SAMEACCOUNTTRANSTYPE,
   REBOOK::BATCH,
   TRANS_REBOOK_PARAM::REBOOK_COPY,
   '\0'
};
const I_CHAR* RebookParamTrade_[] = 
{
   TRANS_REBOOK_PARAM::ACCOUNT_NUM,
   TRANS_REBOOK_PARAM::TRANS_NUM, 
	TRANS_REBOOK_PARAM::FUND_CODE,
	TRANS_REBOOK_PARAM::CLASS_CODE,
   REBOOK::SAMEACCOUNTTRANSTYPE,
   MFCAN_IP_PARAM::CALLER,
   TRANS_REBOOK_PARAM::REBOOK_EXIST,
   REBOOK::BATCH,
   TRANS_REBOOK_PARAM::REBOOK_COPY,
   '\0'
};


const I_CHAR* ConfirmParam_[] = 
{
   REBOOK::SAMEACCOUNTTRANSTYPE,
   '\0'
};

struct REBOOK_PROCESS
{
   const I_CHAR* _command;
   const I_CHAR** _params;
};

//data structures for the new shareholder flow
const struct  REBOOK_PROCESS RebookProcess_[] = 
{
   CMD_BPROC_REBOOK_PARAM, ToRebookParam_, 
   CMD_BPROC_TRADES,RebookParamTrade_,
   CMD_BPROC_CONFIRMATION, ConfirmParam_,  
   '\0', '\0'
};


//******************************************************************************
RebookProcess::RebookProcess (GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess (pGIC, pGIParent, rCommand)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   reboolParam_.AddParam(MFCAN_IP_PARAM::CALLER, I_("Rebook"));
}

//******************************************************************************
RebookProcess::~RebookProcess ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY RebookProcess::doInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      getParamFromParent ( RebookParam_ );
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
E_COMMANDRETURN RebookProcess::doProcess ()
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      const I_CHAR* command = NULL;
      int cmdindx = 0;

      while (cmdindx >= 0 && ( (command = RebookProcess_[ cmdindx ]._command) != '\0'))
      {
         setParamsForChild (RebookProcess_[ cmdindx ]._params);
         if( command == CMD_BPROC_CONFIRMATION )
         {
            setParameter( CONFPROC::PARM_CALLED_FROM, I_("REBOOK") );
         }
         rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            
         getParamFromParent (RebookProcess_[ cmdindx ]._params);
         
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
void RebookProcess::setParamsForChild (const I_CHAR* params[])
{
   const I_CHAR* param = NULL;

   for (int i = 0; (param = params[ i ]) != '\0'; ++i)
   {
      DString value = reboolParam_.getParam( DString (param) );

      if (value != NULL_STRING) //do not clear the params
      {
         setParameter (param, value);
      }
   }
}
//**********************************************************************************
void RebookProcess::getParamFromParent (const I_CHAR* params[])
{
   const I_CHAR* param = NULL;

   for (int i = 0; (param = params[ i ]) != '\0'; ++i)
   {
      DString value;
      //get parameter from parent process
      getParameter (param, value);
      if (value != NULL_STRING) 
      {
         reboolParam_.AddParam(param, value);
      }
   }
}

//******************************************************************************
bool RebookProcess::isflowEnd ( int index)
{
   return RebookProcess_[ index ]._command == '\0';

}

//*******************************************************************************
RebookProcess::RebookParam::RebookParam()
{
}

//*******************************************************************************
RebookProcess::RebookParam::~RebookParam()
{
   rebook_param_.clear();
}

//*******************************************************************************
void RebookProcess::RebookParam::AddParam (const DString &name, const DString &value)
{
   DString tag(name);
   tag.strip();
   if(tag != NULL_STRING )
   {
      REBOOK_PARAM::iterator it = rebook_param_.find (tag);
      //if( it == rebook_param_.end() )
      {
         DString str (value);
         str.stripTrailing();
         rebook_param_ [name] = str;
      }
   }  
}
//*******************************************************************************
void RebookProcess::RebookParam::removeParam (const DString &name )
{
   DString tag (name);
   tag.strip();
   if( tag != NULL_STRING )
   {
      REBOOK_PARAM::iterator it = rebook_param_.find (tag);
      if (it != rebook_param_.end())
      {
         rebook_param_.erase( it );      
      }   
   }
}
//*******************************************************************************
DString RebookProcess::RebookParam::getParam (const DString &name)
{
   REBOOK_PARAM::const_iterator it = rebook_param_.find (name);
   DString valueOut = NULL_STRING;
   if (it != rebook_param_.end())
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





