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
//    Copyright 1996 by DST Systems, Inc.
//
//
//******************************************************************************

//
//******************************************************************************

#define DIDBRKR_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef ABSTRACTREQUESTOR_HPP
   #include "abstractrequestor.hpp"
#endif

#ifndef BASECONNECTIONMANAGER_HPP
   #include "baseconnectionmanager.hpp"
#endif

#ifndef ABSTRACTSECURITY_HPP
   #include "abstractsecurity.hpp"
#endif

AbstractRequestor::AbstractRequestor(
                        const AbstractSecurity & abstractSecurity,
                        const DString & connectionName ) :
   _abstractSecurity( abstractSecurity),
   _hostConnectionManagerId( abstractSecurity.getHostConnectionManagerId() ),
   _currentOptions( RequestorOptions::OVERWRITE_FIXED_AREA ),
   _fnIsMoreAvailable( NULL ),
   _fnSetNextKey( NULL ),
   _hwndRecipient( 0 ),
   _ulMsg( 0 ),
   _timeout( 0 ),
   _processingWindowHandle( false )
{
   _connection = BaseConnectionManager::getInstance()->getConnection( _hostConnectionManagerId, connectionName );
}

AbstractRequestor::AbstractRequestor(
                        const AbstractSecurity & abstractSecurity,
                        const DString & hostConnectionManagerId,
                        const DString & connectionName ) :
   _abstractSecurity( abstractSecurity),
   _hostConnectionManagerId( hostConnectionManagerId ),
   _currentOptions( RequestorOptions::OVERWRITE_FIXED_AREA ),
   _fnIsMoreAvailable( NULL ),
   _fnSetNextKey( NULL ),
   _hwndRecipient( 0 ),
   _ulMsg( 0 ),
   _timeout( 0 ),
   _processingWindowHandle( false )
{
   _connection = BaseConnectionManager::getInstance()->getConnection( _hostConnectionManagerId, connectionName );
}

AbstractRequestor::AbstractRequestor(const AbstractRequestor & copy) :
   _abstractSecurity(copy._abstractSecurity),
   _hostConnectionManagerId(copy._hostConnectionManagerId),
   _currentOptions(copy._currentOptions),
   _fnIsMoreAvailable(copy._fnIsMoreAvailable),
   _fnSetNextKey(copy._fnSetNextKey),
   _hwndRecipient( copy._hwndRecipient ),
   _ulMsg( copy._ulMsg ),
   _timeout( copy._timeout ),
   _processingWindowHandle( copy._processingWindowHandle  )
{
   // copy gets its own connection
   _connection = BaseConnectionManager::getInstance()->getConnection( _hostConnectionManagerId );
}

AbstractRequestor::~AbstractRequestor()
{
   BaseConnectionManager::getInstance()->freeConnection(_connection);
}

void AbstractRequestor::setNextProcess( pfnIsMoreAvailable fnIsMoreAvailable,
                                   pfnSetNextKey      fnSetNextKey )
{
   _fnIsMoreAvailable =  fnIsMoreAvailable;
   _fnSetNextKey = fnSetNextKey;
}

void AbstractRequestor::setWindowInfo(
                   DSTWINDOWHANDLE hwndRecipient,
                   unsigned long ulMsg )
{
   _hwndRecipient = hwndRecipient;
   _ulMsg = ulMsg;
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
// $Log:   Y:/VCS/iFastAWD/didbrkr/abstractrequestor.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:21:10   kovacsro
// Initial revision.
//
//   Rev 1.0   May 18 2001 11:34:06   DT11159
// 
//
//
