#ifndef CHRONOGRAPH_HPP
#define CHRONOGRAPH_HPP

#pragma message( "including "__FILE__ )

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
// ^FILE   : Chronograph.hpp
// ^AUTHOR : Paul Deardeau
// ^DATE   :
//
// ^CLASS  : Chronograph
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
//******************************************************************************


#ifndef INCLUDED_TIME_H
#define INCLUDED_TIME_H
   #include <time.h>
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

class DITEST_LINKAGE Chronograph
{
   private:
      clock_t _start;
      clock_t _stopped;
      clock_t _lastlap;
      double _elapsed;

      double diff( clock_t start, clock_t end );

   public:
      Chronograph();
      ~Chronograph();
      double start( void );
      double stop( void );
      double reset( void );
      double lap( void );
      double split( void );
      int isstopped( void );
      double elapsed( void );
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
// $Log:   Y:/VCS/iFastAWD/inc/chronograph.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:18   kovacsro
//Initial revision.
// 
//    Rev 1.2   Apr 09 1999 13:13:18   DMUM
// added pragma
//
//    Rev 1.0   Dec 09 1998 13:39:58   DMUM
// Check in for DICORE
//
//

#endif // CHRONOGRAPH_HPP

