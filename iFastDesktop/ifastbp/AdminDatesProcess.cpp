
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
// ^FILE   : AdminDatesProcess.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 06/05/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AdminDatesProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "admindatesprocess.hpp"
#include "admindatesprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ADMINDATES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADMINDATES;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AdminDatesProcess > processCreator( CMD_BPROC_ADMINDATES );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AdminDatesProcess" );
   const I_CHAR *MODUSER = I_( "ModUser" );
   const I_CHAR *MODDATE = I_( "ModDate" );
   const I_CHAR *USERNAME = I_( "Username" );
   const I_CHAR *PROCESSDATE = I_( "ProcessDate" );
   const I_CHAR *PROCESSTIME = I_( "ProcessTime" );
   const I_CHAR *DISPLAYTYPE = I_( "DisplayType" );   // For alt. display of Process Date and Process Time
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************

AdminDatesProcess::AdminDatesProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI(NULL)

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addFieldDetails( MOD_DATE,     BF::NullContainerId, SUBCLASS_PROCESS, I_( "ModDate" ) );
   addFieldDetails( MOD_USER,     BF::NullContainerId, SUBCLASS_PROCESS, I_( "ModUser" ) );
   addFieldDetails( PROCESS_DATE, BF::NullContainerId, SUBCLASS_PROCESS, I_( "ProcessDate" ) );
   addFieldDetails( PROCESS_USER, BF::NullContainerId, SUBCLASS_PROCESS, I_( "Username" ) );
   addFieldDetails( PROCESS_TIME, BF::NullContainerId, SUBCLASS_PROCESS, I_( "ProcessTime" ) );
}

//******************************************************************************

AdminDatesProcess::~AdminDatesProcess()
{
   _rpChildGI = NULL;

}

//******************************************************************************

void AdminDatesProcess::doGetField( const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    DString &strValueOut,
                                    bool bFormatted ) const
{
   if( idField == MOD_DATE )
   {
      strValueOut=strModDate; 
   }
   else if( idField == MOD_USER )
   {
      strValueOut=strModUser;
   }
   else if( idField == PROCESS_DATE )
   {
      strValueOut=strProcessDate;
   }
   else if( idField == PROCESS_USER )
   {
      strValueOut=strProcessUser;
   }
   else if( idField == PROCESS_TIME )
   {
      strValueOut = strProcessTime;
   }
}

//******************************************************************************

SEVERITY AdminDatesProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

   // SEVERITY sevRtn = SEVERE_ERROR, sevRtn1 = SEVERE_ERROR;
   try
   {
      getParameter(MODUSER, strModUser);
      getParameter(MODDATE, strModDate);
      getParameter(USERNAME, strProcessUser);
      getParameter(PROCESSDATE, strProcessDate);
      getParameter(PROCESSTIME, strProcessTime);
      getParameter(DISPLAYTYPE, strDisplayType);
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

bool AdminDatesProcess::doModelessChildComplete( const Command &cmd )
{
   // if AdmindatesDialog is destroyed the process should be destroyed -
   // (return true)
   return( cmd.getKey()==CMD_GUI_ADMINDATES );
}

//******************************************************************************

bool AdminDatesProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );
      getParameter(MODUSER, strModUser);
      getParameter(MODDATE, strModDate);
      getParameter(USERNAME, strProcessUser);
      getParameter(PROCESSDATE, strProcessDate);
      getParameter(PROCESSTIME, strProcessTime);
      getParameter(DISPLAYTYPE, strDisplayType);

      if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
         return(bRtn);// false
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   catch( ConditionException &ce )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
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

E_COMMANDRETURN AdminDatesProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   // Set Display Type
   setParameter( DISPLAYTYPE, strDisplayType );
   try
   {
      rtn = invokeCommand( this, CMD_GUI_ADMINDATES, getProcessType(),
                           isModal(), &_rpChildGI );
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
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AdminDatesProcess.cpp-arc  $
 * 
 *    Rev 1.10   Feb 19 2005 18:17:52   hernando
 * PET1117 FN66-68 - Added alternate display; Process Date and ProcessTime.
 * 
 *    Rev 1.9   Apr 02 2003 12:19:30   PURDYECH
 * Code cleanup
 * 
 *    Rev 1.8   Mar 21 2003 17:35:24   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:00   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 16:42:34   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.5   Aug 29 2002 12:54:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:23:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   27 Mar 2002 19:54:32   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.2   15 Dec 2000 12:43:18   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.1   Aug 02 2000 15:31:58   BUZILA
 * "locale" changes
 * 
 *    Rev 1.0   Feb 15 2000 10:59:30   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   Dec 07 1999 12:30:34   DT24433
 * added idDataGroup to doGetField parms
 * 
 *    Rev 1.5   Oct 28 1999 17:40:56   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.4   Aug 31 1999 11:14:12   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.3   Aug 17 1999 13:09:42   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.2   Jul 20 1999 11:13:32   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:01:50   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
