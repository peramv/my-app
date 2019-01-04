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
// ^FILE   : exceptionhandler.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 8 Jan 1999
//
//
// ^DESCRIPTION :
//
//
//
//******************************************************************************

#define DIAWD23_DLL

#include "stdafx.h"
#include <fstream>
#include <sstream>

//******************************************************************************
//
// Inlcude this header before ANYTHING that uses the standard C++ library
//
//    This header includes all the SOM headers for AWD.
//
      #include "sominc.h"

//
//******************************************************************************

#ifndef EXCEPTIONHANDLER_HPP
   #include "exceptionhandler.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif
#ifndef DIAWDCND_H
   #include "diawdcnd.h"
#endif
#ifndef BASE_H
   #include "base.h"
#endif

namespace
{
   // Condition IDI tag names
   const DString AWD_EXCEPTION_MESSAGE = I_("AWD_EXCEPTION_MESSAGE");
   const DString AWD_ERROR_MESSAGE = I_("AWD_ERROR_MESSAGE");

   Environment * ev = NULL;
}

void ConvertAwdExceptionToConditionException( AWDException *pExc,
                                              const I_CHAR *className,
                                              const I_CHAR *methodName,
                                              const char *fileName,
                                              unsigned lineNumber )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("ConvertAwdExceptionToConditionException()" ) )

   DString awdMessage( I_("No Message") );
   DString awdInfo( I_("none") );
   DString strMethod( className );
   strMethod += I_("::");
   strMethod += methodName;

   if ( pExc )
   {
      awdMessage = pExc->message( ev );

      i_ostringstream os;
      os << I_("<");
      os << I_("Return Code = ") << pExc->returnCode( ev );
      os << I_(", File = ") << pExc->file( ev );
      os << I_(", Line = ") << pExc->line( ev );
      os << I_(">") << std::ends;

      awdInfo = os.str();

      delete pExc;
   }

   TRACE_CLASS_MSG( I_("Awd23Interface"),
                    I_("ConvertAwdExceptionToConditionException()"),
                    awdMessage )
   TRACE_CLASS_MSG( I_("Awd23Interface"),
                    I_("ConvertAwdExceptionToConditionException()"),
                    awdInfo )

   DString awdMessageIdi;

   awdMessageIdi = AWD_EXCEPTION_MESSAGE;
   awdMessageIdi += '=';
   awdMessageIdi += awdMessage;
   awdMessageIdi += ';';
   awdMessageIdi += AWD_ERROR_MESSAGE;
   awdMessageIdi += '=';
   awdMessageIdi += awdInfo;


   throw ConditionException( DIAWD23_CONDITION,
                             strMethod,
                             DIAWD23_AWD_EXCEPTION,
							 CM_STRINGIFY(DIAWD23_AWD_EXCEPTION),
                             fileName,
                             lineNumber,
                             0,
                             FALSE,
                             g_conditionManager.getPath(),
                             NO_SEVERITY,
                             awdMessageIdi );
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/diawd23/exceptionhandler.cpp-arc  $
// 
//    Rev 1.1   Nov 02 2011 04:42:24   purdyech
// Registry cleanup
// 
//    Rev 1.2   Jul 22 1999 10:14:44   DMUM
// Condition re-work
//
//    Rev 1.1   Apr 09 1999 13:50:42   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.1.0   Mar 31 1999 13:20:58   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0   Jan 20 1999 09:39:56   DMUM
//
//

