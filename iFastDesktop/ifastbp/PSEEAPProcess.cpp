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
//******************************************************************************
//
// ^FILE   : PSEEAPProcess.cpp
// ^AUTHOR : 
// ^DATE   : April, 2010
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : PSEEAPProcess
//    This class manages the RESP Beneficiary Allocation List information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "pseeapprocessincludes.h"
#include "pseeapprocess.hpp"
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\pseeaplist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PSE_EAP;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PSE_EAP;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< PSEEAPProcess > processCreator (CMD_BPROC_PSE_EAP);

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "PSEEAPProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADE_VALIDATION_GROUP
{
   //Clearning method
   extern CLASS_IMPORT const long PSE_EAP; 
}

namespace MFCAN_IP_PARAM
{
//list key
   extern IFASTBP_LINKAGE const I_CHAR * const LIST_KEY;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
PSEEAPProcess::PSEEAPProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_TradeListKey (NULL_STRING)
, m_AccountNum (NULL_STRING)
, m_transId (NULL_STRING)
,_pPSEEAPList (NULL)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	addContainer ( IFASTBP_PROC::TRADE, false, BF::NullContainerId, true, I_("Trade"));
	addContainer ( IFASTBP_PROC::PSE_EAP_LIST, false, BF::NullContainerId, false, I_("PseEapList"));
}

//******************************************************************************
PSEEAPProcess::~PSEEAPProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if (_pPSEEAPList)
   {
      delete _pPSEEAPList;
      _pPSEEAPList = NULL;
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY PSEEAPProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter (CALLER, m_Caller);
   getParameter (ACCOUNT_NUM, m_AccountNum);
   getParameter (MFCAN_IP_PARAM::LIST_KEY, m_TradeListKey);
   getParameter (I_("TransId"), m_transId);
	if (m_Caller == I_("TradeEntry"))
   {
      addFieldDetails( ifds::CourseStart,		   IFASTBP_PROC::TRADE);
	   addFieldDetails( ifds::CourseLen,	      IFASTBP_PROC::TRADE);
	   addFieldDetails( ifds::PSEProgramLen,	   IFASTBP_PROC::TRADE);
	   addFieldDetails( ifds::PSEProgramType,		IFASTBP_PROC::TRADE);
	   addFieldDetails( ifds::PSEProgramYear,	   IFASTBP_PROC::TRADE);
	   addFieldDetails( ifds::EduInstPstl,		   IFASTBP_PROC::TRADE);
   }
   else if (m_Caller == I_("RESPTransactionsDlg"))
   {
      addFieldDetails( ifds::CourseStart,		   IFASTBP_PROC::PSE_EAP_LIST);
	   addFieldDetails( ifds::CourseLen,	      IFASTBP_PROC::PSE_EAP_LIST);
	   addFieldDetails( ifds::PSEProgramLen,	   IFASTBP_PROC::PSE_EAP_LIST);
	   addFieldDetails( ifds::PSEProgramType,		IFASTBP_PROC::PSE_EAP_LIST);
	   addFieldDetails( ifds::PSEProgramYear,	   IFASTBP_PROC::PSE_EAP_LIST);
	   addFieldDetails( ifds::EduInstPstl,		   IFASTBP_PROC::PSE_EAP_LIST);
   }
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PSEEAPProcess::doModelessChildComplete( const Command &cmd )
{
	// End when GUI ends
	return cmd.getKey() == CMD_BPROC_PSE_EAP;
}

//******************************************************************************
E_COMMANDRETURN PSEEAPProcess::doProcess()
{
	MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
	E_COMMANDRETURN rtn = CMD_FAILURE;

	setParameter (CALLER, m_Caller);
   setParameter (ACCOUNT_NUM, m_AccountNum);
   setParameter (I_("TransId"), m_transId);
	try
	{
		rtn = invokeCommand (this, CMD_GUI_PSE_EAP, getProcessType(), isModal(), &_rpChildGI);
	}
	catch( ConditionException &ce )
	{
		assert( 0 );
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
			CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(rtn);
}

//******************************************************************************
void *PSEEAPProcess::getPtrForContainer( const BFContainerId& idContainer,
                                         const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

	void *ptr = NULL;
	DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	try
	{
		if (IFASTBP_PROC::TRADE == idContainer)
		{
			if (m_Caller == I_("TradeEntry"))
         {
			   WorksessionTradesList *pTradesList (NULL);

			   if( pDSTCWorkSession->getTradesList (pTradesList, idDataGroup) <= WARNING && 
                pTradesList)
			   {
				   BFObjIter iter (*pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   			
				   iter.positionByKey (m_TradeListKey);
				   if (!iter.end())
				   {
					   ptr = dynamic_cast <Trade*>(iter.getObject());
				   }										
			   }
         }
		}
      else if (IFASTBP_PROC::PSE_EAP_LIST == idContainer)
      {
         if (m_Caller == I_("RESPTransactionsDlg"))
         {
            if (_pPSEEAPList)
            {
               delete _pPSEEAPList;
               _pPSEEAPList = NULL;
            }
            if (!_pPSEEAPList)
            {
               _pPSEEAPList = new PSEEAPList (*pDSTCWorkSession);

               if (_pPSEEAPList->init (m_transId) <= WARNING)
               {
                  ptr = _pPSEEAPList;
               }
            }
         }
      }
	}
	catch( ConditionException & )
	{
		throw;
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
			CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(ptr);
}

//******************************************************************************
bool PSEEAPProcess::doOk (GenericInterface *rpGICaller)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

	return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//*****************************************************************************
SEVERITY PSEEAPProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
                                        const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOVALIDATEALL);
   
   if (m_Caller == I_("TradeEntry"))
   {
      Trade *pTrade = 
         dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));
      
      if (pTrade)
      {
//validate only the pse eap group
         pTrade->validateAll (idDataGroup, TRADE_VALIDATION_GROUP::PSE_EAP);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PSEEAPProcess::doSend ( GenericInterface *rpGICaller,
                             const I_CHAR  *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSEND);

   DString message (szMessage);
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   Trade *pTrade = 
      dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));
   
   //reset settle location values, only for new trades
   if (m_Caller == I_("TradeEntry") && pTrade)
   {
      if (message == I_("Cancel")) 
      {
         pTrade->resetPSE (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PSEEAPProcess.cpp-arc  $
// 
//    Rev 1.6   Jun 11 2010 06:19:32   kitticha
// PETP0165541 FN02 IN#2123752 - PSE Fix. Remove Previous rev logic.
// 
//    Rev 1.5   Jun 04 2010 03:31:30   kitticha
// IN#2123752 - Additional logic and validation for PSE.
// 
//    Rev 1.4   May 05 2010 15:27:28   popescu
// RES-QESI Trading - PSE/EAP work - fixes for the dialog
// 
//    Rev 1.3   Apr 30 2010 15:31:30   popescu
// RES-QESI Trading - PSE/EAP work
// 
//    Rev 1.2   Apr 29 2010 23:20:30   popescu
// RES-QESI Trading - PSE/EAP work
// 
//    Rev 1.1   Apr 21 2010 17:19:26   popescu
// RESP-QESI Resp transfer screen
// 
//    Rev 1.0   Apr 20 2010 00:59:18   popescu
// Initial revision.
 * 
*/