#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef ABSTRACTSECURITY_HPP
   #include "abstractsecurity.hpp"
#endif

#ifndef DIDBRKR_CONDITIONS_HPP
   #include "didbrkr_conditions.hpp"
#endif

#ifndef DICORE_CONDITIONS_HPP
   #include "dicore_conditions.hpp"
#endif

AbstractSecurity::AbstractSecurity( const DString & operatorId, const DString & hostConnectionManagerId ) :
   _operatorId( operatorId ),
   _hostConnectionManagerId( hostConnectionManagerId ),
   _isLoggedOn( false )
{

}

bool AbstractSecurity::changePassword( const DString &sPassword, const DString &sNewPassword )
{
   THROWEXCEPTIONCONDITION(
         DIDBRKR_CONDITION,
         I_( "changePassword( const DString&, const DString&)" ),
         VIRTUAL_BASE_METHOD_NOT_SUPPORTED,
         NULL_STRING,
         NULL);

   return false;
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/abstractsecurity.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:10   kovacsro
// Initial revision.
//
//   Rev 1.0   May 18 2001 11:34:10   DT11159
// 
//
//