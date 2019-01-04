//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial.
//
//******************************************************************************
//
// ^FILE   : FireFighterLogonProcess.cpp
// ^AUTHOR : May Lin
// ^DATE   : Dec 2, 2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FireFighterLogonProcess
//   
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "FireFighterLogonprocess.hpp"
#include <ifastdbrkr\dstchost.hpp>
#include "FireFighterLogonprocessincludes.h"
#include <ifastcbo\firefighterlogoninfo.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FIRE_FIGHTER_LOGON;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FIRE_FIGHTER_LOGON;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FireFighterLogonProcess > processCreator( CMD_BPROC_FIRE_FIGHTER_LOGON );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME       = I_( "FireFighterLogonProcess" );     
   const I_CHAR *YES							 = I_( "Y" );
   const I_CHAR *NO							 = I_( "N" );

}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_USER_CHANGE_PASSWORD;

}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

FireFighterLogonProcess::FireFighterLogonProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,_pFFLogonInfo ( NULL )
,_rpChildGI ( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );    

   addContainer( IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO, false, BF::NullContainerId, true, I_("FireFighterLogonInfo") );

   addFieldDetails( ifds::FireFighterId, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO);   
   addFieldDetails( ifds::FireFighterPassword, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO );
   addFieldDetails( ifds::PTSNumber, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO );
   addFieldDetails( ifds::Description1, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO );
   addFieldDetails( ifds::Description2, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO );
	addFieldDetails( ifds::Description3, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO );
   addFieldDetails( ifds::Description4, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO );
   addFieldDetails( ifds::UpdateStatus, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( FIREFIGHTER::IS_THE_SAME_VERSION, BF::NullContainerId, SUBCLASS_PROCESS );
	addFieldDetails( FIREFIGHTER::IS_ACCESSID_R, BF::NullContainerId, SUBCLASS_PROCESS );
	addFieldDetails( FIREFIGHTER::IS_ACCESSID_F, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************
// Destructor 
//******************************************************************************

FireFighterLogonProcess::~FireFighterLogonProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if ( _pFFLogonInfo )
   {
		delete _pFFLogonInfo;
        _pFFLogonInfo = NULL;
   }

}

//******************************************************************************
// @returns SEVERITY.
//******************************************************************************

SEVERITY FireFighterLogonProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );   
   
   try 
   {
		  _pFFLogonInfo = new FireFighterLogonInfo( getBFSession()->getUserSession() );
		  if( _pFFLogonInfo->init(getDataGroupId()) <= WARNING )
		  {
			 setContainer( IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO, _pFFLogonInfo  );
		  }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Function which tells the generic interface container that the modeless child
// has been destroyed.
// @param   const Command &cmd - cmd indicating the child is destroyed.
// @returns bool - true when successful.
//******************************************************************************

bool FireFighterLogonProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FIRE_FIGHTER_LOGON );
}

//******************************************************************************
// This functions starts the Fire Fighter Logon Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

E_COMMANDRETURN FireFighterLogonProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_FIRE_FIGHTER_LOGON, getProcessType(),
                           isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
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
SEVERITY FireFighterLogonProcess::ok2( GenericInterface *rpGI )
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, OK2 );

	try
	{
		DSTCUserSession &session = dynamic_cast<DSTCUserSession& >(getBFSession()->getUserSession());

		if(_pFFLogonInfo)
		{
			DString dstrFFID, dstrPassword, dstrPTSNum,dstrDesc1, dstrDesc2, dstrDesc3,dstrDesc4;
			BFDataGroupId idDataGroup=getDataGroupId();
			_pFFLogonInfo->getField(ifds::FireFighterId,dstrFFID,idDataGroup,false);
			dstrFFID.strip();
			_pFFLogonInfo->getField(ifds::FireFighterPassword,dstrPassword,idDataGroup,false);
			dstrPassword.strip();
			_pFFLogonInfo->getField(ifds::PTSNumber,dstrPTSNum,idDataGroup,false);
			dstrPTSNum.strip();
			_pFFLogonInfo->getField(ifds::Description1,dstrDesc1,idDataGroup,false);
			dstrDesc1.strip();
			_pFFLogonInfo->getField(ifds::Description2,dstrDesc2,idDataGroup,false);
			dstrDesc2.strip();
			_pFFLogonInfo->getField(ifds::Description3,dstrDesc3,idDataGroup,false);
			dstrDesc3.strip();
			_pFFLogonInfo->getField(ifds::Description4,dstrDesc4,idDataGroup,false);
			dstrDesc4.strip();

			session.setFireFighterLogonInfo(dstrFFID,dstrPassword,dstrPTSNum,
				dstrDesc1,dstrDesc2,dstrDesc3,dstrDesc4);
		}
		else
		{
			DString logoutMessage;

			getBFSession()->getUserSession().logoff( DSTCHost::getPrimaryHost(), logoutMessage );
		}
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK,
			CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************************

void FireFighterLogonProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& idField,
                                   const BFDataGroupId& idDataGroup,
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );   

   if( idField ==  FIREFIGHTER::IS_THE_SAME_VERSION )
   {
      if( _pFFLogonInfo )
      {
         if( _pFFLogonInfo->isSameVersion( idDataGroup ) )
         {
            strValueOut = YES;
         }
         else
         {
            strValueOut = NO;
         }
      }
   }
	if( idField ==  FIREFIGHTER::IS_ACCESSID_R )
   {
      if( _pFFLogonInfo )
      {
         if( _pFFLogonInfo->isAccessIdR( idDataGroup ) )
         {
            strValueOut = YES;
         }
         else
         {
            strValueOut = NO;
         }
      }
   }
	if( idField ==  FIREFIGHTER::IS_ACCESSID_F )
   {
      if( _pFFLogonInfo )
      {
         if( _pFFLogonInfo->isAccessIdF( idDataGroup ) )
         {
            strValueOut = YES;
         }
         else
         {
            strValueOut = NO;
         }
      }
   }

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FireFighterLogonProcess.cpp-arc  $
// 
//    Rev 1.6   Jan 08 2010 11:56:08   yingz
// delay view 276 for inc#1936007
// 
//    Rev 1.5   Sep 12 2005 15:57:36   ZHANGCEL
// PET1235 - FN02 -- Apply same logic for FFID
// 
//    Rev 1.4   Aug 31 2005 16:02:14   ZHANGCEL
// PET1235 - FN02 -- 1).Add two new fields: Descripiton3 and Description4; 2). Add logic to call logoff when validation fail.
// 
//    Rev 1.3   Aug 22 2005 10:47:10   ZHANGCEL
// PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
// 
//    Rev 1.2   Dec 12 2003 16:22:54   linmay
// modified doInit()
// 
//    Rev 1.1   Dec 11 2003 11:59:02   linmay
// added doGetField( )
// 
//    Rev 1.0   Dec 09 2003 09:00:48   linmay
// Initial Revision
// 
 */
