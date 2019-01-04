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
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : SavingsDirectiveProcess.cpp
// ^AUTHOR :  
// ^DATE   : 15 Nov 2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SavingsDirectiveProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "SavingsDirectiveProcess.hpp"
#include "SavingsDirectiveProcessincludes.h"
#include <confirmationprocessincludes.h>
#include <ifastcbo\savingsdirective.hpp>

#include <ifastdataimpl\dse_dstc0358_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SAVINGS_DIRECTIVE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SAVINGS_DIRECTIVE;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SavingsDirectiveProcess > processCreator( CMD_BPROC_SAVINGS_DIRECTIVE );


namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "SavingsDirectiveProcess" );  
}

namespace CND
{
	extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SAVINGS_DIRECTIVE;

}

//******************************************************************************
//              Public Methods
//******************************************************************************

SavingsDirectiveProcess::SavingsDirectiveProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pSavingsDirective( NULL )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   
   addContainer( IFASTBP_PROC::SAVINGS_DIRECTIVE, false, BF::NullContainerId, true, I_("SavingsDirective") );
	
   addFieldDetails( ifds::TIS,			IFASTBP_PROC::SAVINGS_DIRECTIVE );
   addFieldDetails( ifds::TISType,		IFASTBP_PROC::SAVINGS_DIRECTIVE );
   addFieldDetails( ifds::Cost,        IFASTBP_PROC::SAVINGS_DIRECTIVE );
   addFieldDetails( ifds::CostType,		IFASTBP_PROC::SAVINGS_DIRECTIVE );

}

//******************************************************************************
SavingsDirectiveProcess::~SavingsDirectiveProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;
	/*
	if (_pSavingsDirective)
	{
		delete _pSavingsDirective;
		_pSavingsDirective = NULL;
	} */
}



//******************************************************************************
SEVERITY SavingsDirectiveProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
 
   try
   {
      processParameters ();
		_accountNum.stripAll();
		_transID.stripAll();
	}
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool SavingsDirectiveProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_SAVINGS_DIRECTIVE );
}


//******************************************************************************
bool SavingsDirectiveProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false; 

	processParameters ();
	setContainer (IFASTBP_PROC::SAVINGS_DIRECTIVE, NULL);
   setParameter( SAVINGS_DIRECTIVE::ACCOUNTNUM, _accountNum );
   setParameter( SAVINGS_DIRECTIVE::TRANSID, _transID );

   if( isValidModelessInterface( _rpChildGI ) )
   {  // Only if child still exists
      bRtn = _rpChildGI->refresh( this, I_("Refresh") );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }

   return(bRtn);
}

//**********************************************************************
SEVERITY SavingsDirectiveProcess::doValidateAll(BFAbstractCBO *rpWSD, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   if ( _pSavingsDirective )
		_pSavingsDirective->validateAll (idDataGroup);
         
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
E_COMMANDRETURN SavingsDirectiveProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (SAVINGS_DIRECTIVE::ACCOUNTNUM, _accountNum);
      setParameter (SAVINGS_DIRECTIVE::TRANSID, _transID);

      rtn = invokeCommand( this, 
									CMD_GUI_SAVINGS_DIRECTIVE, 
									PROC_NO_TYPE, 
									isModal(),
                           &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//*****************************************************************************
bool SavingsDirectiveProcess::doOk (GenericInterface *rpGICaller)
{
	setParameter (CONFPROC::PARM_CALLED_FROM, I_("SavingsDirective"));
	return true;

}

//*****************************************************************************
bool SavingsDirectiveProcess::doSend(
                              GenericInterface *rpGICaller,
                              const I_CHAR *szMessage
                              ) 
{
   DString dstrTag(szMessage);
   if( dstrTag == I_("Reset") )
   {
		if (_pSavingsDirective)
		{
			_pSavingsDirective->doReset(getDataGroupId());
	      _pSavingsDirective->clearUpdateFlags( getDataGroupId() );

		}
	  _rpChildGI->refresh( this, I_("FromdoSend") );

      return(true);
   }
   return(false);
}

//**********************************************************************
void *SavingsDirectiveProcess::getPtrForContainer ( const BFContainerId &idContainer, 
																	 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("getPtrForContainer"));
   
   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
   void *ptr = NULL;
   try
   {
      if (idContainer == IFASTBP_PROC::SAVINGS_DIRECTIVE)
      {
			if (pDSTCWorkSession ->getSavingsDirective ( _transID, _accountNum, _fundCode, _classCode, 
																		_tradeDate, _tisType, _tis, _costType, _cost, 
																		_eusdOverrideVer, _pSavingsDirective, 
																		getDataGroupId(), I_("N"), I_("")) <= WARNING)
         {
            ptr = _pSavingsDirective;
         }
      }
	}
   catch (ConditionException &)
   {
      throw;
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 ( CND::BPBASE_CONDITION, 
                       CLASSNAME, 
                       DOINIT,
                       CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;
}

//******************************************************************************
SEVERITY SavingsDirectiveProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

	_transID = _accountNum = _fundCode = _classCode = _tisType = _tis = _costType 
			= _cost = _eusdOverrideVer = NULL_STRING;
	
   getParameter( SAVINGS_DIRECTIVE::ACCOUNTNUM, _accountNum );
   getParameter( SAVINGS_DIRECTIVE::TRANSID, _transID );
	getParameter( SAVINGS_DIRECTIVE::FUND, _fundCode );
	getParameter( SAVINGS_DIRECTIVE::CLASS, _classCode );
	getParameter( SAVINGS_DIRECTIVE::TIS, _tis );
	getParameter( SAVINGS_DIRECTIVE::TIS_TYPE, _tisType );
	getParameter( SAVINGS_DIRECTIVE::COST_TYPE, _costType );
	getParameter( SAVINGS_DIRECTIVE::COST, _cost );
	getParameter( SAVINGS_DIRECTIVE::VERSION, _eusdOverrideVer);
	getParameter( SAVINGS_DIRECTIVE::TRADEDATE, _tradeDate );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SavingsDirectiveProcess.cpp-arc  $
// 
//    Rev 1.2   Jan 20 2006 11:09:42   AGUILAAM
// IN 512857 - fixed reset functionality
// 
//    Rev 1.1   Jan 10 2006 16:26:38   AGUILAAM
// IN 513452 - refresh Savings Directive screen based on highlighted trade when EUSD button is clicked
// 
//    Rev 1.0   Nov 29 2005 17:02:42   AGUILAAM
// Initial revision.
// 
*/