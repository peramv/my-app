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
// ^FILE   : AvailabilityProcess.cpp
// ^AUTHOR : Cristina Oltean
// ^DATE   : Jan, 2001
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AvailabilityProcess

//******************************************************************************

#include "stdafx.h"
#include "availabilityprocess.hpp"
#include "availabilityprocessincludes.h"
#include <ifastcbo\availability.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AVAILABILITY;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AvailabilityProcess > processCreator( CMD_BPROC_AVAILABILITY );

namespace
{
   // Trace literals
   const I_CHAR*  const CLASSNAME = I_( "AvailabilityProcess" );
   const I_CHAR*  const TRACK = I_("ETRACK");
   const I_CHAR*  const ACTIVITY = I_("ACTIVITY");  
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//***************************************************************************
AvailabilityProcess::AvailabilityProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::AVAILABILITY, false, BF::NullContainerId, false, I_( "Availability" ) );

   addFieldDetails( ifds::Trading, IFASTBP_PROC::AVAILABILITY );
   addFieldDetails( ifds::Inquiry, IFASTBP_PROC::AVAILABILITY );
}

//******************************************************************************
AvailabilityProcess::~AvailabilityProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pAvailability != NULL )
   {
      delete _pAvailability;
      _pAvailability = NULL;
   }
}

//******************************************************************************
SEVERITY AvailabilityProcess::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      DString dstrTrack, dstrActivity;

      getParameter(TRACK, dstrTrack);
      getParameter(ACTIVITY, dstrActivity);

      _pAvailability = new Availability( *getBFWorkSession() );

      if( (sevRtn=_pAvailability->init( dstrTrack, dstrActivity )) > WARNING )
      {
         _pAvailability->doInitWithDefaultValues(BF::HOST);
      }
      setContainer( IFASTBP_PROC::AVAILABILITY, _pAvailability );
   }
   catch( ConditionException &ce )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn);
}
//******************************************************************************
E_COMMANDRETURN AvailabilityProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/AvailabilityProcess.cpp-arc  $
// 
//    Rev 1.12   Apr 02 2003 14:03:10   PURDYECH
// Cleaned up obsolete code.
//
