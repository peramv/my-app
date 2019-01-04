#ifndef COMMONPORT_H
#include "commonport.h"
#define COMMONPORT_H
#endif

// Protected constructor called by derived classes
$ThisClass$::$ThisClass$( $ThisClass$::PROTECTED_CREATION protected_creation ) :
   $ParentClass$( $ParentClass$::PROTECTED_CREATE ),
   _fCreatedImpl( false )
{
#ifdef $ThisClassStr$
   TRACE_CONSTRUCTOR( $ThisClassStr$ , $ThisClassStr$ I_("::") $ThisClassStr$ I_("(") $ThisClassStr$ I_("::PROTECTED_CREATION )") );
#else
   TRACE_CONSTRUCTOR( I_("$ThisClass$") , I_("$ThisClass$::$ThisClassStr$( $ThisClassStr$::PROTECTED_CREATION )") );
#endif
}


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//



