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
// ^FILE   : FTPLogonProcess.cpp
// ^AUTHOR : 
// ^DATE   : Dec 9, 2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FTPLogonProcess
//   
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "ftplogonprocess.hpp"
#include "ftplogonprocessincludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FTP_LOGON;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FTP_LOGON;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FTPLogonProcess > processCreator( CMD_BPROC_FTP_LOGON );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "FTPLogonProcess" );      
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

//CP20030319FTPLogonProcess::FTPLogonProcess() : 
FTPLogonProcess::FTPLogonProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _dstrFTPSite ( NULL_STRING ), 
_dstrPort ( NULL_STRING ),
_dstrUserId ( NULL_STRING ),
_dstrPwd ( NULL_STRING ),
_rpChildGI ( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );    
   addFieldDetails( ifds::FTPSite, BF::NullContainerId, SUBCLASS_PROCESS );   
   addFieldDetails( ifds::FTPPort, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::User_Id, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Password, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************
// Destructor 
//******************************************************************************

FTPLogonProcess::~FTPLogonProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// @returns SEVERITY.
//******************************************************************************

SEVERITY FTPLogonProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );   
   return NO_CONDITION;
}

//******************************************************************************
// Function which tells the generic interface container that the modeless child
// has been destroyed.
// @param   const Command &cmd - cmd indicating the child is destroyed.
// @returns bool - true when successful.
//******************************************************************************

bool FTPLogonProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FTP_LOGON );
}

//******************************************************************************
// This functions starts the Reports Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

E_COMMANDRETURN FTPLogonProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_FTP_LOGON, getProcessType(),
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

SEVERITY FTPLogonProcess::ok2( GenericInterface *rpGI )
{
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, OK2 );
   setParameter ( FTP::FTPSITE, _dstrFTPSite );
   setParameter ( FTP::FTPPORT, _dstrPort );
   setParameter ( FTP::USERID, _dstrUserId );
   setParameter ( FTP::PWD, _dstrPwd );
   return NO_CONDITION;
}

//******************************************************************************

SEVERITY FTPLogonProcess::doSetField(
                                    const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& fieldID,
                                    const BFDataGroupId& idDataGroup,
                                    const DString& strValue,
                                    bool bFormatted
                                    )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOSETFIELD );   
   if ( fieldID == ifds::FTPSite ) 
      _dstrFTPSite = strValue;
   else if ( fieldID == ifds::FTPPort )
      _dstrPort = strValue;
   else if ( fieldID == ifds::User_Id )
      _dstrUserId = strValue;
   else if ( fieldID == ifds::Password )
      _dstrPwd = strValue;
   return NO_CONDITION;
}


void FTPLogonProcess::doGetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted
                                ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );   
   if ( idField == ifds::FTPSite ) 
      strValueOut = _dstrFTPSite;
   else if ( idField == ifds::FTPPort )
      strValueOut = _dstrPort;
   else if ( idField == ifds::User_Id )
      strValueOut = _dstrUserId;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FTPLogonProcess.cpp-arc  $
// 
//    Rev 1.3   Jun 05 2003 15:41:54   HERNANDO
// PTS 10017935 - Replaced container Id with BF::NullContainerId.
// 
//    Rev 1.2   Mar 21 2003 17:40:10   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Dec 10 2002 13:34:16   HSUCHIN
// added functionality
// 
//    Rev 1.0   Dec 10 2002 09:52:10   HSUCHIN
// Initial Revision
 */
