#ifndef IPCCHANNEL_HPP
#define IPCCHANNEL_HPP

#  pragma message( "including "__FILE__ )

/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

#ifndef DIPORT_H
   #include "diport.h"
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * IPCChannel is an abstract class used in communications
 */
class DICORE_LINKAGE IPCChannel
{
   public:
      enum IPCAction { CREATE, OPEN };
      IPCChannel() {}
      virtual ~IPCChannel() {}
      virtual bool create() = 0;
      virtual bool open() = 0;

      virtual const char * read( unsigned long * pulBytesRead ) = 0;

      virtual bool read( char * pszInBuf,
                         unsigned long ulInBufSize,
                         unsigned long * pulBytesRead ) = 0;

      virtual bool write( const char * pszOutBuf,
                          unsigned long ulOutBufSize,
                          unsigned long * pulBytesWritten ) = 0;

      virtual bool transact( const char * pszOutBuf,
                             unsigned long ulOutBufSize,
                             char * pszInBuf,
                             unsigned long ulInBufSize,
                             unsigned long * pulBytesRead ) = 0;

      virtual bool call( const char * pszServerPort,
                         const char * pszOutBuf,
                         unsigned long ulOutBufSize,
                         char * pszInBuf,
                         unsigned long ulInBufSize,
                         unsigned long * pulBytesRead ) = 0;

      virtual bool listen() = 0;
      virtual bool close() = 0;

      unsigned long getTimeOut() { return ulTimeOut_; }

      void setTimeOut( unsigned long ulTimeOut )
      { ulTimeOut_ = ulTimeOut; }

   private:
      unsigned long ulTimeOut_;
};

#endif


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


