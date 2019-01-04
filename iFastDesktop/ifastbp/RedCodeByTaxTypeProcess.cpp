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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RedCodeByTaxTypeProcess.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/20/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RedCodeByTaxTypeProcess
//    This class manages the Bank Instructions information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "redcodebytaxtypeprocess.hpp"
#include "redcodebytaxtypeprocessincludes.h"
#include <ifastcbo\redcodebytaxtypelist.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_REDCODEBYTAXTYPE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REDCODEBYTAXTYPE;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RedCodeByTaxTypeProcess > processCreator( CMD_BPROC_REDCODEBYTAXTYPE );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RedCodeByTaxTypeProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace REDCODEBYTAXTYPEINFOLIT  
{
   const I_CHAR * const TAXTYPE = I_( "TaxType" );
   const I_CHAR * const CODETYPE = I_( "CodeType" );
}


//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319RedCodeByTaxTypeProcess::RedCodeByTaxTypeProcess() : 
RedCodeByTaxTypeProcess::RedCodeByTaxTypeProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL ),
_pRedCodeByTaxTypeList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::REDCODEBYTAXTYPELIST, false );
   addFieldDetails( ifds::RedCode, IFASTBP_PROC::REDCODEBYTAXTYPELIST );
   addFieldDetails( ifds::RedCodeDesc, IFASTBP_PROC::REDCODEBYTAXTYPELIST );
}

//******************************************************************************

RedCodeByTaxTypeProcess::~RedCodeByTaxTypeProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pRedCodeByTaxTypeList )delete _pRedCodeByTaxTypeList;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************

E_COMMANDRETURN RedCodeByTaxTypeProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_REDCODEBYTAXTYPE, getProcessType(),
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

bool RedCodeByTaxTypeProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_REDCODEBYTAXTYPE );
}

//******************************************************************************
SEVERITY RedCodeByTaxTypeProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      DString TaxType;
      DString CodeType;

      getParameter( REDCODEBYTAXTYPEINFOLIT::TAXTYPE, TaxType );
      getParameter( REDCODEBYTAXTYPEINFOLIT::CODETYPE, CodeType );

      _pRedCodeByTaxTypeList = new RedCodeByTaxTypeList( *getBFWorkSession() );
      sevRtn = _pRedCodeByTaxTypeList->init( TaxType, CodeType );
      if( sevRtn <= WARNING )
         setContainer( IFASTBP_PROC::REDCODEBYTAXTYPELIST, _pRedCodeByTaxTypeList );
      else
         return(sevRtn);
   }

   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(sevRtn);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RedCodeByTaxTypeProcess.cpp-arc  $
// 
//    Rev 1.8   Mar 21 2003 17:46:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:53:32   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 16:45:12   SMITHDAV
// Condition split.
// 
//    Rev 1.5   Aug 29 2002 12:54:36   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   22 May 2002 18:25:00   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   27 Mar 2002 19:55:36   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.2   03 May 2001 14:05:36   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.1   15 Dec 2000 12:43:46   PURDYECH
// Use precompiled header stdafx.h.
// Removed unnecessary header files.
// 
//    Rev 1.0   May 08 2000 17:04:08   YINGZ
// Initial revision.
 */
