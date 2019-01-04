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
// ^FILE   : TransactionLinkProcess.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 06/26/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransactionLinkProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "TransactionLinkProcess.hpp"
#include "TransactionLinkProcessIncludes.h"

#include <ifastcbo\TransactionLinkList.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TransactionLinkProcess > processCreator( CMD_BPROC_TRANS_LINK );
//CP20020416

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "TransactionLinkProcess" );
}


namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;   
}

namespace TRANS_LINK_PARAM
{
   const I_CHAR * const ACCOUNT_NUM             = I_("AccountNum");
   const I_CHAR * const TRANS_NUM               = I_("TransNum");
}
//******************************************************************************
//              Public Methods
//******************************************************************************

TransactionLinkProcess::TransactionLinkProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
,pTransactionLinkList_(NULL)
,account_(NULL_STRING)
,transNum_(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "TransactionLinkProcess" ) );

   addContainer( IFASTBP_PROC::TRANSACTION_LINK_LIST, true, BF::NullContainerId, true, I_("TransactionLinkList") );
   addContainer( IFASTBP_PROC::MFACOUNT, false, BF::NullContainerId, false, I_("MFAccount") );
   addFieldDetails( ifds::LinkType,				IFASTBP_PROC::TRANSACTION_LINK_LIST );
   addFieldDetails( ifds::LinkTransNum,		IFASTBP_PROC::TRANSACTION_LINK_LIST );
}

//******************************************************************************
TransactionLinkProcess::~TransactionLinkProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( pTransactionLinkList_ )
   {
      delete pTransactionLinkList_;
   }

}

//******************************************************************************
SEVERITY TransactionLinkProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

  
   try
   {
      DString account,transNum;  
      getParent()->getParameter( TRANS_LINK_PARAM::ACCOUNT_NUM, account_ );
      getParent()->getParameter( TRANS_LINK_PARAM::TRANS_NUM, transNum_ );
      account.strip().stripLeading('0');
      transNum.strip();
      if( !isXMLAPIContext() )
      {
          DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
          MFAccount* pMFAccount = NULL;
          if( dstcWorkSession )
          {
             if( dstcWorkSession->getMFAccount (getDataGroupId(), account_,pMFAccount )<= WARNING && pMFAccount )
             {
                setContainer( IFASTBP_PROC::MFACOUNT, pMFAccount );
             }
          
            if( pTransactionLinkList_ )
            {
               delete pTransactionLinkList_;
               pTransactionLinkList_ = NULL;
            }
            pTransactionLinkList_ = new TransactionLinkList( *dstcWorkSession );      
            if( pTransactionLinkList_->init(transNum_) <= WARNING )
            {
                  setContainer( IFASTBP_PROC::TRANSACTION_LINK_LIST, pTransactionLinkList_ );
                        
            }            
          }
      }
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
E_COMMANDRETURN TransactionLinkProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( TRANS_LINK_PARAM::ACCOUNT_NUM,   account_ );
      setParameter( TRANS_LINK_PARAM::TRANS_NUM,     transNum_ );
      if( !isXMLAPIContext() )
      {
         rtn = invokeCommand( this, CMD_GUI_TRANS_LINK, getProcessType(), isModal(), &_rpChildGI );
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
bool  TransactionLinkProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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
bool  TransactionLinkProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_TRANS_LINK );
}



/*
//******************************************************************************
bool TransactionLinkProcess::doRefresh( GenericInterface *rpGICaller,
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransactionLinkProcess.cpp-arc  $
// 
//    Rev 1.0   Jul 06 2005 16:40:18   Yingbaol
// Initial revision.
 * 
 *
 */
