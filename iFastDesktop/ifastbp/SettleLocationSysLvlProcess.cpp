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
// ^FILE   : SettleLocationSysLvlProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SettleLocationSysLvlProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "SettleLocationSysLvlProcess.hpp"
#include "SettleLocationSysLvlProcessincludes.h"
#include <ifastcbo\SettleLocationSysLvlList.hpp>
#include <ifastcbo\SettleLocationSysLvl.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "mfcaninterprocparam.hpp"
#include "confirmationprocessincludes.h"

#include <dataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SETTLEMENT_LOCATION_SYSLVL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SETTLEMENT_LOCATION_SYSLVL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SettleLocationSysLvlProcess > processCreator( CMD_BPROC_SETTLEMENT_LOCATION_SYSLVL );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "SettleLocationSysLvlProcess" );
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const STLOC;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
SettleLocationSysLvlProcess::SettleLocationSysLvlProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  m_rpChildGI( NULL  ), m_pSettleLocationSysLvlList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, true, BF::NullContainerId, true, I_("SettleLocationSysLvlList") );

   addSubstituteList( ifds::SettleLocationSysLvlHeading );

   // Settle Location List
   addFieldDetails( ifds::SettleLocationCode, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::SettleLocationDesc, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::SettleAccountNum, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::Active, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::InUseAcct, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::InUseTrade, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::Username, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::RecId, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
}

//******************************************************************************

SettleLocationSysLvlProcess::~SettleLocationSysLvlProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY SettleLocationSysLvlProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );

   const BFDataGroupId& idDataGroup = getDataGroupId();

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   {
      try
      {
         SEVERITY sevRtn = dstcWorkSession->getSettlementLocationSysLvlList( m_pSettleLocationSysLvlList, idDataGroup );
         if( sevRtn <= WARNING && m_pSettleLocationSysLvlList )
         {
            setContainer( IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, m_pSettleLocationSysLvlList );
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

bool SettleLocationSysLvlProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_SETTLEMENT_LOCATION_SYSLVL );
}

//******************************************************************************

bool SettleLocationSysLvlProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
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

E_COMMANDRETURN SettleLocationSysLvlProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_SETTLEMENT_LOCATION_SYSLVL, getProcessType(), isModal(), &m_rpChildGI );
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

void* SettleLocationSysLvlProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
// Stub
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

void SettleLocationSysLvlProcess::doGetField(
                                           const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup,
                                           DString &strValueOut,
                                           bool bFormatted
                                           ) const
{
// Stub
}

//******************************************************************************

bool SettleLocationSysLvlProcess::doOk(GenericInterface *rpGICaller)
{
   setParameter( CONFPROC::PARM_CALLED_FROM, I_("SettleLocationSysLvl") );
   return( true );
}

//******************************************************************************

SEVERITY SettleLocationSysLvlProcess::performSearch( GenericInterface *rpGI, 
                                                     const BFContainerId& idSearch, 
                                                     E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ) );
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      if( m_pSettleLocationSysLvlList != NULL )
      {
         sevRtn = m_pSettleLocationSysLvlList->getMore();
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), 
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return( sevRtn ); 
}

//******************************************************************************

bool SettleLocationSysLvlProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || m_pSettleLocationSysLvlList == NULL ? false : m_pSettleLocationSysLvlList->doMoreRecordsExist());
}

//******************************************************************************

SEVERITY SettleLocationSysLvlProcess::getHistoricalParameters(const BFContainerId& idContainer, 
                                                     BFFieldId &recordIdField, DString& tableId, DString& dstrKey) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );
   
   if (idContainer == IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST)
   {
      recordIdField = ifds::RecId;
      tableId = AUDITTYPE::STLOC;
      dstrKey = NULL_STRING;
   }
   else
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************

SEVERITY SettleLocationSysLvlProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

// ******************************************************************************
// Revision Control Entries
// ******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/SettleLocationSysLvlProcess.cpp-arc  $
// 
//    Rev 1.3   Mar 10 2004 13:20:20   HERNANDO
// PET965 FN11 - Added getHistoricalParameters.
// 
//    Rev 1.2   Nov 24 2003 18:06:10   HERNANDO
// Next revision.
// 
//    Rev 1.1   Nov 21 2003 10:02:24   HERNANDO
// Changed the Audit Type Code.
// 
//    Rev 1.0   Nov 20 2003 11:31:34   HERNANDO
// Initial revision.
// 
