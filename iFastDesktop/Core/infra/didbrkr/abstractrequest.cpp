#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef ABSTRACTREQUEST_HPP
   #include "abstractrequest.hpp"
#endif

AbstractRequest::AbstractRequest( const DString & id ) :
   m_id( id )
{

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
// $Log:   Y:/VCS/iFastAWD/didbrkr/abstractrequest.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:08   kovacsro
// Initial revision.
//
//   Rev 1.0   May 18 2001 11:34:02   DT11159
// 
//
//
