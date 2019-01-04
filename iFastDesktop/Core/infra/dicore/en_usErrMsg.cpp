//************************************************************************
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
//************************************************************************
//
// ^FILE   : usaErrMsg.cpp
// ^AUTHOR : Tom Hogan
// ^DATE   : 1-11-99
//

#define DICORE_DLL

#include "srcprag.h"

#ifndef CONDITION_HPP
#include "condition.hpp"
#endif

#undef en_us

MsgPair en_us[] =
{
   {
      Condition::CND_FILE_NOT_FOUND,
      I_( "Could not open the condition file: " ),
      I_( "  Check: 1) the registry, or 2) to see if condition file exists." )
   },
   {
      Condition::CODE_NOT_FOUND,
      I_( "Did not find the code in the condition file." ),
      I_( "  Get the correct condition file which contains the code." )
   },
   {
      Condition::SEVERE_ERROR_IN_FILE,
      I_( "Severe error encountered reading the condition file." ),
      I_( "  Contact the support desk." )
   },
   {
      Condition::ISO_CODE_NOT_FOUND,
      I_( "ISO country code not found in the condition file." ),
      I_( "  Contact the support desk." )
   },
   {
      Condition::INVALID_VERSION,
      I_( "Condition file version is not recognized. " ),
      I_( "Get compatible condition file." )
   },
   {
      Condition::ERROR_ON_NEW,
      I_( "Bad condition file.  " ),
      I_( "Get a new condition file." )
   },
   {
      Condition::NO_CONDITION_CODE,
      NULL_STRING,
      NULL_STRING
   }
};


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

      
      

