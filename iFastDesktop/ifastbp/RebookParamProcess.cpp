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
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : RebookParamProcess.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 06/26/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RebookParamProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "RebookParamProcess.hpp"
#include "RebookParamProcessIncludes.h"
#include "RebookProcessincludes.h"

#include <ifastcbo\TransactionLinkList.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RebookParamProcess > processCreator( CMD_BPROC_REBOOK_PARAM );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "RebookParamProcess" );
   const I_CHAR *YES       = I_( "Y" );
};


namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;   
};

namespace TRANS_REBOOK_PARAM
{
   const I_CHAR * const ACCOUNT_NUM             = I_("AccountNum");
   const I_CHAR * const TRANS_NUM               = I_("TransNum");
   const I_CHAR * const ESTATE_ALLOC            = I_("EstateAlloc");
   const I_CHAR * const COMMISSION_REBATE       = I_("CommissionRebate");
   const I_CHAR * const REBOOK_EXIST            = I_("ReboolExist");
   const I_CHAR * const SAMEACCOUNTTRANSTYPE    = I_ ("SameAccountTransType");
	const I_CHAR * const FUND_CODE               = I_("FromFund");
	const I_CHAR * const CLASS_CODE              = I_("FromClass");
	const I_CHAR * const BATCH                   = I_("Batch");
	const I_CHAR * const REBOOK_COPY             = I_("RebookCopy");

};
//******************************************************************************
//              Public Methods
//******************************************************************************

RebookParamProcess::RebookParamProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,_rpChildGI( NULL )
,account_(NULL_STRING)
,transNum_(NULL_STRING)
,useSameAccountTransType_(YES)
,fundCode_(NULL_STRING)
,classCode_(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "RebookParamProcess" ) );
   addFieldDetails( RebookField::UseSameAccountTransType,   BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( RebookField::IsEstateAllocation,        BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( RebookField::IsCommissionRebate,        BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( RebookField::RebookExist,               BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( RebookField::RebookCopy,                BF::NullContainerId, SUBCLASS_PROCESS );
}
//******************************************************************************
RebookParamProcess::~RebookParamProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************
SEVERITY RebookParamProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

  
   try
   {     
      getParent()->getParameter( TRANS_REBOOK_PARAM::ACCOUNT_NUM, account_ );
      getParent()->getParameter( TRANS_REBOOK_PARAM::TRANS_NUM, transNum_ );
      getParent()->getParameter( TRANS_REBOOK_PARAM::ESTATE_ALLOC, estateAlloc_ );
      getParent()->getParameter( TRANS_REBOOK_PARAM::COMMISSION_REBATE, commRebate_ );
      getParent()->getParameter( TRANS_REBOOK_PARAM::REBOOK_EXIST, rebookExist_ );
      getParent()->getParameter( TRANS_REBOOK_PARAM::SAMEACCOUNTTRANSTYPE, useSameAccountTransType_ );
      getParent()->getParameter( TRANS_REBOOK_PARAM::BATCH, batch_ );
	  getParent()->getParameter( TRANS_REBOOK_PARAM::REBOOK_COPY, rebookCopy_ );
		
	  getParameter( TRANS_REBOOK_PARAM::FUND_CODE, fundCode_ );
	  getParameter( TRANS_REBOOK_PARAM::CLASS_CODE, classCode_ );

      if( useSameAccountTransType_.stripAll().upperCase() == NULL_STRING )
      {
         useSameAccountTransType_ = I_("Y");
      
      }
      account_.strip().stripLeading('0');
      transNum_.strip();
     
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
E_COMMANDRETURN RebookParamProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( TRANS_REBOOK_PARAM::ACCOUNT_NUM,   account_ );
      setParameter( TRANS_REBOOK_PARAM::TRANS_NUM,     transNum_ );
      setParameter( TRANS_REBOOK_PARAM::REBOOK_EXIST,  rebookExist_ );
	  setParameter( TRANS_REBOOK_PARAM::FUND_CODE,     fundCode_ );
	  setParameter( TRANS_REBOOK_PARAM::CLASS_CODE,    classCode_ );
	  setParameter( TRANS_REBOOK_PARAM::BATCH,         batch_ );
	  setParameter( TRANS_REBOOK_PARAM::REBOOK_COPY,  rebookCopy_ );

      if( !isXMLAPIContext() )
      {
         rtn = invokeCommand( this, CMD_GUI_REBOOK_PARAM, getProcessType(), isModal(), &_rpChildGI );
      }
      else
      {
         rtn = CMD_MODELESS_INPROCESS;
      }   
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
bool  RebookParamProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
   // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;
   try
   {
      if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
      {
         return(bRtn);  // false
      }
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(bRtn);
}

//******************************************************************************
bool  RebookParamProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_REBOOK_PARAM );
}
//**********************************************************************************
void RebookParamProcess::doGetField( const GenericInterface *rpGICaller, 
                    const BFContainerId& idContainer, const BFFieldId& idField, 
                    const BFDataGroupId& idDataGroup, 
                    DString &strValueOut, 
                    bool bFormatted ) const
{
   if( idField == RebookField::UseSameAccountTransType )
   {
      strValueOut = useSameAccountTransType_;   
   }
   else if ( idField == RebookField::IsEstateAllocation )
   {
      strValueOut = estateAlloc_;
   }
   else if ( idField == RebookField::IsCommissionRebate )
   {
      strValueOut = commRebate_;      
   }
   else if ( idField == RebookField::RebookExist )
   {
      strValueOut = rebookExist_;
   }
   else if ( idField == RebookField::RebookCopy )
   {
      strValueOut = rebookCopy_;
   }
   else
   {
      assert(0);
   }

}
//***********************************************************************************
SEVERITY RebookParamProcess::doSetField( const GenericInterface* rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId &fieldID,
                                const BFDataGroupId& idDataGroup,
                                const DString &strValue,
                                bool bFormatted )
{
   if( fieldID == RebookField::UseSameAccountTransType )
   {
      useSameAccountTransType_ = strValue;   
   }
   else
   {
      assert(0);
   }
   return NO_CONDITION;
}
//*******************************************************************************************
void RebookParamProcess:: doPostOk( GenericInterface* rpGICaller, bool bSuccessFlag )
   {
      if( bSuccessFlag )
      {
         setParameter(REBOOK::SAMEACCOUNTTRANSTYPE,useSameAccountTransType_);      
      }
   }
/*
//******************************************************************************
bool RebookParamProcess::doRefresh( GenericInterface *rpGICaller,
                                const I_CHAR *szOriginalCommand )
{
   return(_rpChildGI->refresh( this, NULL ));
}
*/

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RebookParamProcess.cpp-arc  $
// 
//    Rev 1.4   May 27 2009 15:16:20   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.3   Feb 07 2006 11:29:18   AGUILAAM
// IN 534395 - fixed rebook for management fee (AF91) where multiple trades are linked to one transnum; match exact trade with fund/class.
// 
//    Rev 1.2   Aug 29 2005 10:42:12   popescu
// Incident 390388 - wire order number should be blanked out for multiple rebooks
// 
//    Rev 1.1   Aug 17 2005 14:37:36   Yingbaol
// PEt1235,FN01: minor changes for passing parameters.
// 
//    Rev 1.0   Jul 06 2005 16:35:40   Yingbaol
// Initial revision.
 * 
 *
 */
