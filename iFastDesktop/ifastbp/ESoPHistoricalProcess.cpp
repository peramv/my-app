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
// ^FILE   : ESoPHistoricalProcess.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 09/20/2001
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ESoPHistoricalProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\esophistoricallist.hpp>
#include "esophistoricalprocess.hpp"
#include "esophistoricalprocessincludes.h"
#include <ifastcbo\esopinfo.hpp>
#include <ifastcbo\mfaccount.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ESOP_HISTORICAL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACC_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ESOPINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ESOP_HISTORICAL;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ESoPHistoricalProcess > processCreator( CMD_BPROC_ESOP_HISTORICAL );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "ESoPHistoricalProcess" );

   const I_CHAR * const Y             = I_( "Y" );
   const I_CHAR * const N             = I_( "N" );

}


//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ESoPHistoricalProcess::ESoPHistoricalProcess() : 
ESoPHistoricalProcess::ESoPHistoricalProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   addContainer( IFASTBP_PROC::MFACCOUNT,  false, BF::NullContainerId, false, I_("MFAccount") );
   addContainer( IFASTBP_PROC::ESOP_HISTORICAL_LIST,  true, BF::NullContainerId, false, I_("ESoPHistorical") );

   //MFAccount fields
   addFieldDetails( ifds::ShrNum,         IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::AccountNum,     IFASTBP_PROC::MFACCOUNT );
   addFieldDetails( ifds::Name,           IFASTBP_PROC::MFACCOUNT );


   //ESoPHistorical fields
   addFieldDetails( ifds::ModDate,     IFASTBP_PROC::ESOP_HISTORICAL_LIST );
   addFieldDetails( ifds::FieldName,   IFASTBP_PROC::ESOP_HISTORICAL_LIST );
   addFieldDetails( ifds::ModUser,     IFASTBP_PROC::ESOP_HISTORICAL_LIST );
   addFieldDetails( ifds::OldValue,    IFASTBP_PROC::ESOP_HISTORICAL_LIST );
   addFieldDetails( ifds::NewValue,    IFASTBP_PROC::ESOP_HISTORICAL_LIST );

}

//******************************************************************************

ESoPHistoricalProcess::~ESoPHistoricalProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY ESoPHistoricalProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( ESOP_HISTORICAL::ACCOUNT_NUMBER, _strAccountNum );
      _strAccountNum.strip().stripLeading( '0' );
      if( _strAccountNum.empty() )
      {
         assert(0);
         return(SEVERE_ERROR);
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

E_COMMANDRETURN ESoPHistoricalProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   try
   {
      rtn = invokeCommand( this, CMD_GUI_ESOP_HISTORICAL, getProcessType(),
                           isModal(), &_rpChildGI );
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

void *ESoPHistoricalProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;

   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case ESOP_HISTORICAL::MFACCOUNT:
      if( IFASTBP_PROC::MFACCOUNT == idContainer )
      {
         {
            MFAccount *pMFAccount;
            DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            if( dstcWorkSession->getMFAccount(idDataGroup, _strAccountNum, pMFAccount ) <= WARNING )
               ptr = pMFAccount;
         }
//CP20030319            break;
//CP20030319         case ESOP_HISTORICAL::ESOP_HISTORICAL_LIST:
      }
      else if( IFASTBP_PROC::ESOP_HISTORICAL_LIST == idContainer )
      {
         {
            MFAccount * pMFAccount = dynamic_cast < MFAccount *> (getCBOItem( IFASTBP_PROC::MFACCOUNT, idDataGroup ));

            if( !pMFAccount )
               return(ptr);
            ESoPHistoricalList * pESoPHistoricalList = NULL;
            ESoPInfo *pESoPInfo = NULL;
            if( pMFAccount->getESoPInfo(pESoPInfo, idDataGroup) <= WARNING )
            {
               if( pESoPInfo->getESoPHistoricalList(pESoPHistoricalList, idDataGroup) <= WARNING )
                  ptr = pESoPHistoricalList;
            }
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

bool ESoPHistoricalProcess::doModelessChildComplete( const Command &cmd )
{
// End when GUI ends   
   return( cmd.getKey() == CMD_GUI_ESOP_HISTORICAL );
}
//******************************************************************************

bool ESoPHistoricalProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
   bool bRtn = true;
   DString strAccNum;
   bool bRefresh = false;

   getParameter( ESOP_HISTORICAL::ACCOUNT_NUMBER, strAccNum );
   strAccNum.strip().stripLeading( '0' );
   DString strKey = rpGICaller->getCommand().getKey();

   if( strKey == CMD_BPROC_ACC_DETAILS || strKey == CMD_BPROC_ESOPINFO && strAccNum != _strAccountNum )
   {  //reset the containers
      _strAccountNum = strAccNum;
      setContainer( IFASTBP_PROC::MFACCOUNT, NULL );
      setContainer( IFASTBP_PROC::ESOP_HISTORICAL_LIST, NULL );
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
SEVERITY ESoPHistoricalProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll") );

   //nothing to do here
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ESoPHistoricalProcess.cpp-arc  $
// 
//    Rev 1.8   Mar 21 2003 17:39:10   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:53:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 16:44:52   SMITHDAV
// Condition split.
// 
//    Rev 1.5   Jun 03 2002 16:55:18   HSUCHIN
// bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
// 
//    Rev 1.4   22 May 2002 18:24:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   27 Mar 2002 19:54:50   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.2   07 Dec 2001 17:20:56   KOVACSRO
// more implementation.
// 
//    Rev 1.1   02 Oct 2001 11:49:22   KOVACSRO
// ESoPHistoricalList is under ESoPInfo now.
// 
//    Rev 1.0   24 Sep 2001 12:22:04   KOVACSRO
// Initial revision.
 


  */