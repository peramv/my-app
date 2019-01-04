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
//    Copyright 1999 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : UserDefMatProcess.cpp
// ^CLASS  : UserDefMatProcess
//
//******************************************************************************

#include "stdafx.h"
#include "UserDefMatProcess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\UserDefMatList.hpp>
#include <ifastcbo\UserDefMat.hpp>
#include "UserDefMatProcessIncludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_USERDEFMAT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_USERDEFMAT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< UserDefMatProcess > processCreator( CMD_BPROC_USERDEFMAT );

namespace
{
   const I_CHAR *CLASSNAME = I_( "UserDefMatProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

UserDefMatProcess::UserDefMatProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI( NULL )
, m_pUserDefMatList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::USER_DEF_MAT_LIST, true, BF::NullContainerId, true );

   addFieldDetails( ifds::ContractMaturityDate,    IFASTBP_PROC::USER_DEF_MAT_LIST );
   addFieldDetails( ifds::EffectiveDate,    IFASTBP_PROC::USER_DEF_MAT_LIST );
   addFieldDetails( ifds::StopDate,         IFASTBP_PROC::USER_DEF_MAT_LIST );
   addFieldDetails( ifds::OrigEventType,    IFASTBP_PROC::USER_DEF_MAT_LIST );
   addFieldDetails( ifds::RecId,            IFASTBP_PROC::USER_DEF_MAT_LIST );
   addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::USER_DEF_MAT_LIST );
   addFieldDetails( ifds::ContractType,     IFASTBP_PROC::USER_DEF_MAT_LIST );

   addFieldDetails( ifds::ProcessDate,      IFASTBP_PROC::USER_DEF_MAT_LIST );
   addFieldDetails( ifds::Username,         IFASTBP_PROC::USER_DEF_MAT_LIST );
   addFieldDetails( ifds::ModDate,          IFASTBP_PROC::USER_DEF_MAT_LIST );
   addFieldDetails( ifds::ModUser,          IFASTBP_PROC::USER_DEF_MAT_LIST );
}

//******************************************************************************

UserDefMatProcess::~UserDefMatProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   m_rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void UserDefMatProcess::doGetField( const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& idField,
                                       const BFDataGroupId& idDataGroup,
                                       DString &strValueOut,
                                       bool bFormatted ) const
{
/*
   if( idField == ifds:: )
   {
   }
*/
}

//******************************************************************************

SEVERITY UserDefMatProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

   // Get Parameters
   getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNumber );
   getParameter( MFCAN_IP_PARAM::SHR_NUM, m_dstrShareholderNumber );
   getParameter( I_("LegalMaturityDate"), m_dstrLegalMaturityDate );
   getParameter( I_("IsContract"), m_dstrIsContract );
   getParameter( MFCAN_IP_PARAM::SEG_TRANS_EXIST, m_dstrSegTransExist );
   getParameter( MFCAN_IP_PARAM::CONTRACT_TYPE, m_dstrContractType );
	getParameter( MFCAN_IP_PARAM::MOD_PERM, m_dstrModPerm );

   // Get UserDefMatList from MFAccount.
   SEVERITY sevRtn = NO_CONDITION;
   MFAccount* mfAccount;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( dstcWorkSession->getMFAccount( getDataGroupId(), m_dstrAccountNumber, mfAccount ) <= WARNING )
   {
      if( mfAccount->getUserDefMatList( m_pUserDefMatList, getDataGroupId(), true, m_dstrLegalMaturityDate, m_dstrContractType ) <= WARNING )
      {
         setContainer( IFASTBP_PROC::USER_DEF_MAT_LIST, m_pUserDefMatList );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool UserDefMatProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_USERDEFMAT );
}

//******************************************************************************

bool UserDefMatProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   return( &UserDefMatProcess::doModelessSetFocus );
}

//******************************************************************************

E_COMMANDRETURN UserDefMatProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      // Set Parameters
      setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNumber );
      setParameter( MFCAN_IP_PARAM::SHR_NUM, m_dstrShareholderNumber );
      setParameter( I_("IsContract"), m_dstrIsContract );
      setParameter( MFCAN_IP_PARAM::SEG_TRANS_EXIST, m_dstrSegTransExist );
		setParameter( MFCAN_IP_PARAM::MOD_PERM, m_dstrModPerm );

      rtn = invokeCommand( this, CMD_GUI_USERDEFMAT, getProcessType(), isModal(), &m_rpChildGI );
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

void *UserDefMatProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   return( NULL );
}

//******************************************************************************

SEVERITY UserDefMatProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( m_pUserDefMatList )
      {
         sevRtn = m_pUserDefMatList->getMore();
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************

bool UserDefMatProcess::doMoreRecordsExist( GenericInterface *rpGICaller,  const BFContainerId& idSearch )
{
   return( rpGICaller == NULL || m_pUserDefMatList == NULL ) ? false : m_pUserDefMatList->doMoreRecordsExist();
}

//******************************************************************************

SEVERITY UserDefMatProcess::doValidateAll(BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup)
{
   return( m_pUserDefMatList->validateAll( idDataGroup ) );
}

//******************************************************************************

void UserDefMatProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   if( bSuccessFlag )
   {
      if ( NULL != m_pUserDefMatList )
	  {
		BFObjIter iter( *m_pUserDefMatList, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED );	   
		int numOfItem = iter.getNumberOfItemsInList();
         
        if( numOfItem > 0 )
		{
			DString ContractMaturityDate;
			getField( rpGICaller, IFASTBP_PROC::USER_DEF_MAT_LIST, ifds::ContractMaturityDate, ContractMaturityDate, false );
			setParameter( MFCAN_IP_PARAM::MATURITY_DATE, ContractMaturityDate );
		}
	  }
   }
   return;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/UserDefMatProcess.cpp-arc  $
// 
//    Rev 1.5   Jun 06 2006 17:24:16   porteanm
// PET 2102 FN01 - Fixed crash when we have only a dummy record.
// 
//    Rev 1.4   Feb 14 2006 14:10:14   zhengcon
// Incident #528284 - add one field ModPerm for updatable permission of User Defined Maturity Date of converted account
// 
//    Rev 1.3   Apr 14 2005 10:04:38   hernando
// PET1024 FN02 - Added parameter, Contract Type.
// 
//    Rev 1.2   Mar 21 2005 11:47:34   hernando
// PET1024 FN02 - Added SegTransExist parameter.
// 
//    Rev 1.1   Mar 20 2005 20:10:02   hernando
// PET1024 FN02 - Added doPostOk.
// 
//    Rev 1.0   Mar 20 2005 17:19:26   hernando
// Initial revision.
