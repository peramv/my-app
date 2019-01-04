// JavaNumber Class Implementation
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
// ^FILE   : JavaNumber.hpp
// ^AUTHOR : Tom Searson
// ^DATE   : 22 March 1999
//
// ^CLASS  : JavaNumber
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
// ^MEMBER VARIABLES :
//    private:
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#ifndef JAVANUMBER_HPP
   #include "javanumber.hpp"
#endif

MsgPair en_usJavaNumber[] =
{
   {
      JavaNumber::JAVANUMBER_CONFIG_ERROR,
      I_("Exception Occurred in GetElementalConfig method."),
      I_("Check Configuration.")
   }
};


Condition::mapCodePagesToLanguages languagesMapForJavaNumber[] =
{
   {
      I_( "C" ), en_usJavaNumber
   },

   // End slot marger
   {
      NULL, NULL

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
// $Log:   Y:/VCS/iFastAWD/dicore/javanumber.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:14   kovacsro
// Initial revision.
// 
//    Rev 1.9   Apr 17 2001 15:12:46   dt24433
// Removed setICU_Data.
// 
//    Rev 1.8   Apr 13 2000 07:50:28   DMUM
// Fix potential bug
//
//    Rev 1.7   Apr 11 2000 21:55:20   dtwk
// Change to look at DataBroker configuration in registry to get ICU_DATA path
//
//    Rev 1.6   Apr 10 2000 16:38:44   DT14177
// ICU syncup
//
//    Rev 1.5   Jul 22 1999 11:40:16   DMUM
// Condition re-work
//
//    Rev 1.4   Jun 27 1999 15:30:16   DT11700
//
//
//    Rev 1.3   Jun 17 1999 09:55:02   DT14177
// Added revision control blocks.
//

