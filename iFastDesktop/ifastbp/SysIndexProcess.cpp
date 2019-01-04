//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : SysIndexProcess.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 05/01/2001
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SysIndexProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "sysindexprocess.hpp"
#include "sysindexprocessincludes.h"
#include <ifastcbo\sysindexlist.hpp>
#include <ifastcbo\systematic.hpp>
#include <ifastcbo\systematiclist.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastdataimpl\dse_dstc0005_vwrepeat_record.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SYS_INDEX;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SYS_INDEX;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SysIndexProcess > processCreator( CMD_BPROC_SYS_INDEX );

namespace
{
   const I_CHAR * const CLASSNAME             = I_( "SysIndexProcess" );
}

namespace CND
{
   extern const long BP_ERR_CANNOT_DELETE_ACTIVE_INDEX;
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Status;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}


namespace SYSINDEXLIT
{
   const I_CHAR* const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR* const INSTRUCTION = I_( "BankInstrType" );
   const I_CHAR* const DEFAULT     = I_( "Default" );

}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319SysIndexProcess::SysIndexProcess() : 
SysIndexProcess::SysIndexProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI  ( 0 ), 
m_dstPACSWPId( NULL_STRING), 
m_dstAcctNum ( NULL_STRING),
_pSysIndexList ( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addContainer( IFASTBP_PROC::SYS_INDEX_LIST, true, BF::NullContainerId, true );
   addContainer( IFASTBP_PROC::SYSTEMATIC, false );

   addSubstituteList(ifds::IndexType);
   addSubstituteList(ifds::IndexFrequency);

   addFieldDetails( ifds::IndexAmt,        IFASTBP_PROC::SYS_INDEX_LIST );
   addFieldDetails( ifds::IndexType,       IFASTBP_PROC::SYS_INDEX_LIST );
   addFieldDetails( ifds::IndexFrequency,  IFASTBP_PROC::SYS_INDEX_LIST );
   addFieldDetails( ifds::StartDate,       IFASTBP_PROC::SYS_INDEX_LIST );
   addFieldDetails( ifds::EndDate,         IFASTBP_PROC::SYS_INDEX_LIST );
   addFieldDetails( ifds::NextIndexDate,   IFASTBP_PROC::SYS_INDEX_LIST );

   addFieldDetails( ifds::TransNum,        IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::TransType,       IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::PayType,         IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::StatusCode,      IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::FundCode,        IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::EffectiveDate,   IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::StopDate,        IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::Amount,          IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::AmountType,      IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::Frequency,       IFASTBP_PROC::SYSTEMATIC );
   addFieldDetails( ifds::LastProcessDate, IFASTBP_PROC::SYSTEMATIC );
}
//******************************************************************************

SysIndexProcess::~SysIndexProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY SysIndexProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = NO_CONDITION;
   getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstAcctNum  );
   getParameter( MFCAN_IP_PARAM::PAC_SWP_ID,  m_dstPACSWPId );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN SysIndexProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_SYS_INDEX, getProcessType(), isModal(), &m_rpChildGI );
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

bool SysIndexProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      assert( m_rpChildGI && isValidModelessInterface( m_rpChildGI ) );

      // get bank type
      getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstAcctNum  );
      getParameter( MFCAN_IP_PARAM::PAC_SWP_ID,  m_dstPACSWPId );


      if( isValidModelessInterface( m_rpChildGI ) )
      {  // Only if child still exists
         bRtn = m_rpChildGI->refresh( this, NULL );
         bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );
      }
      return(bRtn);
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

   return(false);
}

//******************************************************************************

bool SysIndexProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_SYS_INDEX );
}

//******************************************************************************
void *SysIndexProcess::getPtrForContainer(
                                         const BFContainerId& idContainer,
                                         const BFDataGroupId& idDataGroup
                                         )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MFAccount      * pMFAccount      = NULL;
   SystematicList * pSystematicList = NULL;
   Systematic     * pSystematic     = NULL;   

   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case SYS_INDEX_DEF::SYS_INDEX_LIST :
      if( IFASTBP_PROC::SYS_INDEX_LIST == idContainer )
      {
         {
            if( dstcWorkSession->getMFAccount( idDataGroup, m_dstAcctNum, pMFAccount) <= WARNING &&
                pMFAccount )
            {
               if( pMFAccount->getSystematicList( pSystematicList, idDataGroup) <= WARNING && pSystematicList )
               {
                  pSystematic = dynamic_cast<Systematic*>(pSystematicList->getObject( m_dstPACSWPId, idDataGroup));
                  if( pSystematic )
                  {
                     if( pSystematic->getSystematicIndexList(idDataGroup, _pSysIndexList) <= WARNING )
                        ptr = _pSysIndexList;
                  };
               };
            }; 
         };
//CP20030319            break;
//CP20030319         case SYS_INDEX_DEF::SYSTEMATIC :
      }
      else if( IFASTBP_PROC::SYSTEMATIC == idContainer )
      {
         {
            if( dstcWorkSession->getMFAccount( idDataGroup, m_dstAcctNum, pMFAccount) <= WARNING &&
                pMFAccount )
            {
               if( pMFAccount->getSystematicList( pSystematicList, idDataGroup) <= WARNING && pSystematicList )
               {
                  pSystematic = dynamic_cast<Systematic*>(pSystematicList->getObject( m_dstPACSWPId, idDataGroup));
                  ptr = pSystematic;
               };
            }; 
         };
//CP20030319            break;
//CP20030319         default :
      }
      else
      {
         assert(0);
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

SEVERITY SysIndexProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll") );  
   SEVERITY sev = NO_CONDITION; 
   if( _pSysIndexList )
      sev = _pSysIndexList->validateAll( idDataGroup );
   return(sev);
}

//******************************************************************************

SEVERITY SysIndexProcess::deleteItemFromList( const GenericInterface *rpGICaller, const BFContainerId& idList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("deleteItemFromList") );

   DString dstrLastProcessDate, dstrStartDate, dstrEndDate;

   const_cast <SysIndexProcess*> (this)->getField(rpGICaller, IFASTBP_PROC::SYSTEMATIC, ifds::LastProcessDate, dstrLastProcessDate, false);
   const_cast <SysIndexProcess*> (this)->getField(rpGICaller, IFASTBP_PROC::SYS_INDEX_LIST, ifds::StartDate, dstrStartDate, false);
   const_cast <SysIndexProcess*> (this)->getField(rpGICaller, IFASTBP_PROC::SYS_INDEX_LIST, ifds::EndDate, dstrEndDate, false);

   if( (!isCurrentListItemNew( const_cast < GenericInterface* >( rpGICaller ), idList )) &&
       (DSTCommonFunctions::CompareDates( dstrStartDate, dstrLastProcessDate ) == DSTCommonFunctions::FIRST_EARLIER) &&
       (DSTCommonFunctions::CompareDates( dstrLastProcessDate, dstrEndDate ) == DSTCommonFunctions::FIRST_EARLIER) )
   {
      ADDCONDITIONFROMFILE( CND::BP_ERR_CANNOT_DELETE_ACTIVE_INDEX );
   }
   else
   {
      AbstractProcess::deleteItemFromList( rpGICaller, idList );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SysIndexProcess.cpp-arc  $
// 
//    Rev 1.17   Jun 10 2003 11:48:14   popescu
// change name of the systematic cbo container to be compliant with the standard, re-named the ACCOUNT_DISTRIBUTION_BANK_LIST in ACCOUNT_DISTRIBUTION since nobody was using it, and re-used the id for banking instructions process
// 
//    Rev 1.16   Mar 21 2003 17:48:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.15   Oct 09 2002 23:53:38   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.14   Sep 04 2002 15:45:42   PURDYECH
// Condition, comment and formatting cleanup
// 
//    Rev 1.13   Aug 29 2002 16:45:16   SMITHDAV
// Condition split.
// 
//    Rev 1.12   Jun 03 2002 16:55:34   HSUCHIN
// bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
// 
//    Rev 1.11   22 May 2002 18:25:04   PURDYECH
// BFData Implementation
// 
//    Rev 1.10   27 Mar 2002 19:55:42   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.9   01 Aug 2001 17:37:54   HSUCHIN
// logic change for delete of indexing
// 
//    Rev 1.8   11 Jul 2001 15:10:26   HSUCHIN
// bug fix for deleting item from list
// 
//    Rev 1.7   05 Jul 2001 17:43:40   HSUCHIN
// force validateall to validate only SysIndexList
// 
//    Rev 1.6   11 Jun 2001 10:24:50   HSUCHIN
// allow the deletion of future dated indexing
// 
//    Rev 1.5   06 Jun 2001 13:38:04   HSUCHIN
// code cleanup and additional business logic added
// 
//    Rev 1.4   31 May 2001 19:30:58   HSUCHIN
// code cleanup and enhancements
// 
//    Rev 1.3   15 May 2001 15:38:56   YINGZ
// data group id clean up
// 
//    Rev 1.2   14 May 2001 11:10:08   HSUCHIN
// code sync up
// 
//    Rev 1.1   11 May 2001 16:33:38   YINGZ
// code sync up
// 
//    Rev 1.0   03 May 2001 13:43:12   BUZILAMI
// Initial revision.
 * 
 *
 */

