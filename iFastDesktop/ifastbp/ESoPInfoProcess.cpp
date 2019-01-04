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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ESoPInfoProcess.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/29/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ESoPInfoProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\esopinfo.hpp>
#include "esopinfoprocess.hpp"
#include "esopinfoprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ESOPINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACC_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ESOPINFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ESoPInfoProcess > processCreator( CMD_BPROC_ESOPINFO );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "ESoPInfoProcess" );

   const I_CHAR * const Y             = I_( "Y" );
   const I_CHAR * const N             = I_( "N" );

}


//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ESoPInfoProcess::ESoPInfoProcess() : 
ESoPInfoProcess::ESoPInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   addContainer( IFASTBP_PROC::MFACCOUNT,  false, BF::NullContainerId, true, I_("MFAccount") );
   addContainer( IFASTBP_PROC::ESOPINFO,   false, BF::NullContainerId, true, I_("ESoPInfo") );

   //MFAccount fields
   addFieldDetails( ifds::ShrNum,              IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::AccountNum,          IFASTBP_PROC::MFACCOUNT );

   //ESoPInfo fields
   addFieldDetails( ifds::IFASNumber,          IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::ESoPStatus,          IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::InitPurchDate,       IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::InitInvestDate,      IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::BankEffectiveDate,   IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::AutoCreate,          IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::FromFundNumber,      IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::FundCode,            IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::FundName,            IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::ClassCode,           IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::Amount,              IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::Currency,            IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::InterruptDate,       IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::InterruptCode,       IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::ContStartDate,       IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::BlockStartDate,      IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::InactiveDate,        IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::ContEndDate,         IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::BlockEndDate,        IFASTBP_PROC::ESOPINFO );
   addFieldDetails( ifds::ContExpireDate,      IFASTBP_PROC::ESOPINFO );
   //addFieldDetails( DBR::HistoricalInfoExist, ESOP::ESOPINFO );

}

//******************************************************************************

ESoPInfoProcess::~ESoPInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY ESoPInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( ESOP::ACCOUNT_NUMBER, _strAccountNum );
      _strAccountNum.strip().stripLeading( '0' );
      if( _strAccountNum.empty() )
      {
         assert(0);
         return(sevRtn);
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      //assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN ESoPInfoProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   setParameter( ESOP::ACCOUNT_NUMBER, _strAccountNum );
   try
   {
      if( isXMLAPIContext() )
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
         rtn = invokeCommand( this, CMD_GUI_ESOPINFO, getProcessType(),
                              isModal(), &_rpChildGI );
      }
   }
   catch( ConditionException &ce )
   {
      //assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      //assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************

void *ESoPInfoProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;

   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case ESOP::MFACCOUNT:
      if( IFASTBP_PROC::MFACCOUNT == idContainer )
      {
         {
            MFAccount *pMFAccount;
            DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            if( dstcWorkSession->getMFAccount(idDataGroup, _strAccountNum, pMFAccount ) <= WARNING )
               ptr = pMFAccount;
         }
//CP20030319            break;
//CP20030319         case ESOP::ESOPINFO:
      }
      else if( IFASTBP_PROC::ESOPINFO == idContainer )
      {
         {
            MFAccount * pMFAccount = dynamic_cast < MFAccount *> (getCBOItem( IFASTBP_PROC::MFACCOUNT, idDataGroup ));

            if( !pMFAccount )
               return(ptr);
            ESoPInfo * pESoPInfo = NULL;
            if( pMFAccount->getESoPInfo(pESoPInfo, idDataGroup) <= WARNING )
               ptr = pESoPInfo;
         }
//CP20030319            break;
//CP20030319      }
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

bool ESoPInfoProcess::doModelessChildComplete( const Command &cmd )
{
// End when GUI ends   
   return( cmd.getKey() == CMD_GUI_ESOPINFO );
}
//******************************************************************************

bool ESoPInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
   bool bRtn = true;
   DString strAccNum;
   bool bRefresh = false;
   getParameter( ESOP::ACCOUNT_NUMBER, strAccNum );
   strAccNum.strip().stripLeading( '0' );

   if( rpGICaller->getCommand().getKey() == CMD_BPROC_ACC_DETAILS && strAccNum != _strAccountNum )
   {  //reset the containers
      _strAccountNum = strAccNum;
      setContainer( IFASTBP_PROC::MFACCOUNT, NULL );
      setContainer( IFASTBP_PROC::ESOPINFO, NULL );
      bRefresh = true;
   }
   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      if( bRefresh )
         bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}
//******************************************************************************
SEVERITY ESoPInfoProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll") );

   ESoPInfo *pESoPInfo = dynamic_cast < ESoPInfo *> (getCBOItem( IFASTBP_PROC::ESOPINFO, idDataGroup ));
   pESoPInfo->validateAll(idDataGroup);

   MFAccount *pMFAccount;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( dstcWorkSession->getMFAccount(idDataGroup, _strAccountNum, pMFAccount ) <= WARNING )
      pMFAccount->validateAll(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ESoPInfoProcess.cpp-arc  $
// 
//    Rev 1.10   Mar 21 2003 17:39:18   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:53:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 16:44:54   SMITHDAV
// Condition split.
// 
//    Rev 1.7   Jun 03 2002 16:55:28   HSUCHIN
// bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
// 
//    Rev 1.6   Jun 03 2002 16:42:24   FENGYONG
// Add name for API
// 
//    Rev 1.5   22 May 2002 18:24:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   27 Mar 2002 19:54:50   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.3   07 Dec 2001 17:22:20   KOVACSRO
// more implementation.
// 
//    Rev 1.2   19 Sep 2001 15:05:44   KOVACSRO
// Added doValidateAll()
// 
//    Rev 1.1   16 Aug 2001 14:28:10   KOVACSRO
// Added some methods.
// 
//    Rev 1.0   29 Jul 2001 19:08:06   KOVACSRO
// Initial revision.
 * 

  */