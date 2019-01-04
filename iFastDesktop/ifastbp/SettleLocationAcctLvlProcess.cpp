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
// ^FILE   : SettleLocationAcctLvlProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SettleLocationAcctLvlProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "SettleLocationAcctLvlProcess.hpp"
#include "SettleLocationAcctLvlProcessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\SettleLocationAcctLvlList.hpp>
#include <ifastcbo\SettleLocationAcctLvl.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mfaccount.hpp>
#include "mfcaninterprocparam.hpp"

#include <dataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SETTLEMENT_LOCATION_ACCTLVL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SETTLEMENT_LOCATION_ACCTLVL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SettleLocationAcctLvlProcess > processCreator( CMD_BPROC_SETTLEMENT_LOCATION_ACCTLVL );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "SettleLocationAcctLvlProcess" );
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const ATLOC;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
SettleLocationAcctLvlProcess::SettleLocationAcctLvlProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  m_rpChildGI( NULL  ), m_pSettleLocationAcctLvlList( NULL ), m_dstrAccountNumber( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, true, BF::NullContainerId, true, I_("SettleLocationAcctLvlList") );
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, true, I_("Account") );

   addSubstituteList(ifds::SettleLocationAcctLvlHeading );

   // Account
   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );

   // Settle Location Account Level List
   addFieldDetails( ifds::SettleLocationCode, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::SettleLocationDesc, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Default, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );

   // Admin/Dates details
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::Username, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
   addFieldDetails( ifds::RecId, IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST );
}

//******************************************************************************

SettleLocationAcctLvlProcess::~SettleLocationAcctLvlProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY SettleLocationAcctLvlProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );

   getParameter(I_("AccountNum"), m_dstrAccountNumber );
   const BFDataGroupId& idDataGroup = getDataGroupId();

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   {
      try
      {
         MFAccount *pMFAccount;
         if( dstcWorkSession->getMFAccount( idDataGroup, m_dstrAccountNumber, pMFAccount ) <= WARNING )
         {
            SEVERITY sevRtn = pMFAccount->getSettlementLocationAcctLvlList( m_pSettleLocationAcctLvlList, idDataGroup );
            if( sevRtn <= WARNING && m_pSettleLocationAcctLvlList )
            {
               setContainer( IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST, m_pSettleLocationAcctLvlList );      
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
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                         CND::BP_ERR_UNKNOWN_EXCEPTION );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool SettleLocationAcctLvlProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_SETTLEMENT_LOCATION_ACCTLVL );
}

//******************************************************************************

bool SettleLocationAcctLvlProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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

   return( bRtn );
}

//******************************************************************************

E_COMMANDRETURN SettleLocationAcctLvlProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_SETTLEMENT_LOCATION_ACCTLVL, getProcessType(), isModal(), &m_rpChildGI );
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

void* SettleLocationAcctLvlProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
      if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
         MFAccount *pMFAccount;
         if( dstcWorkSession->getMFAccount( idDataGroup, m_dstrAccountNumber, pMFAccount ) <= WARNING )
         {
            ptr = pMFAccount;

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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************

bool SettleLocationAcctLvlProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
   return(false);
}

//******************************************************************************

bool SettleLocationAcctLvlProcess::doOk(GenericInterface *rpGICaller)
{
   // Update Account Details Option.
   MFAccount *pMFAccount = NULL;
   DString dstrSettlementLocationFlag = I_( "N" );
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( dstcWorkSession->getMFAccount( idDataGroup, m_dstrAccountNumber, pMFAccount ) <= WARNING )
   {
      SettleLocationAcctLvlList *pSettleLocationAcctLvlList = NULL;
      if( pMFAccount->getSettlementLocationAcctLvlList( pSettleLocationAcctLvlList, idDataGroup ) <= WARNING )
      {
         BFObjIter iter( *pSettleLocationAcctLvlList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         while( !iter.end() )
         {
            if( !iter.isDummy() )
            {
               dstrSettlementLocationFlag = I_( "Y" );
               break;
            }
            ++iter;
         }
         pMFAccount->setField( ifds::SettleLocExist, dstrSettlementLocationFlag, idDataGroup, false );
      }
   }
   return( true );
}

//******************************************************************************

void SettleLocationAcctLvlProcess::doGetField(
                                           const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup,
                                           DString &dstrValueOut,
                                           bool bFormatted
                                           ) const
{
}

//******************************************************************************

SEVERITY SettleLocationAcctLvlProcess::getHistoricalParameters(const BFContainerId& idContainer, 
                                                     BFFieldId &recordIdField, DString& tableId, DString& dstrKey) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );
   
   if (idContainer == IFASTBP_PROC::SETTLEMENT_LOCATIONS_LIST)
   {
      recordIdField = ifds::RecId;
      tableId = AUDITTYPE::ATLOC;
      dstrKey = NULL_STRING;
   }
   else
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************

SEVERITY SettleLocationAcctLvlProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/SettleLocationAcctLvlProcess.cpp-arc  $
// 
//    Rev 1.3   Mar 10 2004 13:20:04   HERNANDO
// PET965 FN11 - Added getHistoricalParameters.
// 
//    Rev 1.2   Nov 24 2003 18:05:12   HERNANDO
// Next revision.
// 
//    Rev 1.1   Nov 21 2003 10:01:58   HERNANDO
// Changed the Audit Type Code.
// 
//    Rev 1.0   Nov 20 2003 11:31:28   HERNANDO
// Initial revision.
