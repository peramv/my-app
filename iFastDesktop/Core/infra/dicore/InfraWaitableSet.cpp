/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2001 by DST Systems, Inc.
 */

#define DICORE_DLL

#ifndef INFRAWAITABLESET_HPP
   #include "infrawaitableset.hpp"
#endif

InfraWaitableSet::InfraWaitableSet() :
   _handlesCount( 0 )
{
}

InfraWaitableSet::~InfraWaitableSet()
{
}

bool InfraWaitableSet::addHandle( HANDLE handle )
{
   bool full = false;
   //make sure we are not full
   if( _handlesCount < MAXIMUM_WAIT_OBJECTS )
   {
      _handles[ _handlesCount++ ] = handle;
   }
   else
   {
      full = true;
   }
   return !full;
}

const int InfraWaitableSet::getCount()
{
   return _handlesCount;
}

DWORD InfraWaitableSet::wait( BOOL bWaitAll, DWORD dwMilliseconds )
{
   DWORD waitResult = WAIT_FAILED;

   if( _handlesCount > 0 )
   {
      waitResult = ::WaitForMultipleObjects( _handlesCount, _handles, bWaitAll, dwMilliseconds );
   }
   return waitResult;
}

bool InfraWaitableSet::shrinkSet( DWORD ndxHandleThatSignaled )
{
   bool bRet = false;

   //we want to keep it between this margins
   if( ndxHandleThatSignaled >= 0 && ndxHandleThatSignaled < (unsigned int)_handlesCount )
   {
      _handles[ ndxHandleThatSignaled ] = _handles[ _handlesCount - 1 ];
      bRet = --_handlesCount > 0;
   }
   return bRet;
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
// $Log:   Y:/VCS/iFastAWD/dicore/InfraWaitableSet.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:08   kovacsro
// Initial revision.
//
//   Rev 1.0   Jun 28 2001 16:22:44   DT11159
// 
//
//
