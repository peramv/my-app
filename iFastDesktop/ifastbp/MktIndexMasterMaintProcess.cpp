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
//    Copyright 2003 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : MktIndexMasterMaintProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MktIndexMasterMaintProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "MktIndexMasterMaintProcess.hpp"
#include "MktIndexMasterMaintProcessincludes.h"
#include <ifastcbo\MktIndexMasterList.hpp>
#include <ifastcbo\MktIndexMaster.hpp>
#include <ifastcbo\MktIndexFundsList.hpp>
#include <ifastcbo\MktIndexFunds.hpp>
#include <ifastcbo\FundMasterList.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "mfcaninterprocparam.hpp"
#include "confirmationprocessincludes.h"

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MKT_INDEX_MASTER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MKT_INDEX_MASTER;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MktIndexMasterMaintProcess > processCreator( CMD_BPROC_MKT_INDEX_MASTER );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "MktIndexMasterMaintProcess" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319MktIndexMasterMaintProcess::MktIndexMasterMaintProcess() 
MktIndexMasterMaintProcess::MktIndexMasterMaintProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  m_rpChildGI( NULL  ), m_pMktIndexMasterList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::INDICES_LIST, true, BF::NullContainerId, true, I_("IndicesList") );
   addContainer( IFASTBP_PROC::FUNDS_LIST, true, IFASTBP_PROC::INDICES_LIST, true, I_("FundsList") );

   addSubstituteList(ifds::IndexMasterHeading );
   addSubstituteList(ifds::IndexFundsHeading );

   // Indices List
   addFieldDetails( ifds::IndexCode, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::IndexName, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::Username, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::InputDataType, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::DaysBasis, IFASTBP_PROC::INDICES_LIST );
   // Funds List
   addFieldDetails( ifds::FundCode,  IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUNDS_LIST );

   // SUBCLASS PROCESSED
   addFieldDetails( INDEX_MASTER::FUNDDESC, IFASTBP_PROC::FUNDS_LIST, SUBCLASS_PROCESS );
//   addFieldDetails( ifds::FundNumber, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************

MktIndexMasterMaintProcess::~MktIndexMasterMaintProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MktIndexMasterMaintProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );

   const BFDataGroupId& idDataGroup = getDataGroupId();

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getMgmtCo().getFundMasterList( m_pFundMasterList );

   {
      try
      {
         SEVERITY sevRtn = dstcWorkSession->getMktIndexMasterList( m_pMktIndexMasterList, idDataGroup );
         if( sevRtn <= WARNING && m_pMktIndexMasterList )
         {
            setContainer( IFASTBP_PROC::INDICES_LIST, m_pMktIndexMasterList );      
         }
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
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool MktIndexMasterMaintProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_MKT_INDEX_MASTER );
}

//******************************************************************************

bool MktIndexMasterMaintProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

   bool bRtn = false;
   try
   {
      assert( m_rpChildGI );
      if( isValidModelessInterface( m_rpChildGI ) )
      {
         bRtn = m_rpChildGI->refresh( this, NULL );
         bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );
      }
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

E_COMMANDRETURN MktIndexMasterMaintProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_MKT_INDEX_MASTER, getProcessType(), isModal(), &m_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return( rtn );
}

//******************************************************************************

void* MktIndexMasterMaintProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319		case INDEX_MASTER::FUNDS_LIST:
      if( IFASTBP_PROC::FUNDS_LIST == idContainer )
      {
         {
            MktIndexMaster *pMktIndexMaster = dynamic_cast< MktIndexMaster * >( getCBOItem(IFASTBP_PROC::INDICES_LIST, idDataGroup ) );
            MktIndexFundsList* pMktIndexFundsList = NULL;
            if( pMktIndexMaster->getMktIndexFundsList( pMktIndexFundsList, idDataGroup ) <= WARNING )
            {
               ptr = pMktIndexFundsList;
            }

//CP20030319               break;
         }

//CP20030319         default:
      }
      else
      {
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

void MktIndexMasterMaintProcess::doGetField(
                                           const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup,
                                           DString &strValueOut,
                                           bool bFormatted
                                           ) const
{
   if( idField == ifds::FundNumber )
   {
      DString dstrFundCode, dstrClassCode;
      const_cast< MktIndexMasterMaintProcess* >( this )->getField( rpGICaller, IFASTBP_PROC::FUNDS_LIST, ifds::FundCode, dstrFundCode );
      const_cast< MktIndexMasterMaintProcess* >( this )->getField( rpGICaller, IFASTBP_PROC::FUNDS_LIST, ifds::ClassCode, dstrClassCode );
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFundCode, dstrClassCode, strValueOut );
   }
   else if( idField == INDEX_MASTER::FUNDDESC )
   {
      DString dstrFundCode;
      const_cast<MktIndexMasterMaintProcess*>(this)->getField( rpGICaller, IFASTBP_PROC::FUNDS_LIST, ifds::FundCode, 
                                                               dstrFundCode, false);
      if( !dstrFundCode.empty() )
         m_pFundMasterList->getFundName (dstrFundCode, strValueOut);
      else
         strValueOut = NULL_STRING;
   }
}

//******************************************************************************

bool MktIndexMasterMaintProcess::doOk(GenericInterface *rpGICaller)
{
   setParameter( CONFPROC::PARM_CALLED_FROM, I_("MktIndex") );
   return( true );
}

// ******************************************************************************
// Revision Control Entries
// ******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MktIndexMasterMaintProcess.cpp-arc  $
// 
//    Rev 1.6   Jan 16 2012 14:38:30   wp040027
// P0188394_Performance Fees - Benchmark Upload
// 
//    Rev 1.5   Nov 17 2004 15:18:56   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.4   Mar 21 2003 17:45:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Feb 07 2003 14:13:32   HERNANDO
// Added Fund Description.
// 
//    Rev 1.2   Jan 31 2003 11:26:32   HERNANDO
// Added doOk.
// 
//    Rev 1.1   Jan 25 2003 18:36:48   HERNANDO
// Revised.
// 
//    Rev 1.0   Jan 23 2003 10:26:56   HERNANDO
// Initial Revision
 */
