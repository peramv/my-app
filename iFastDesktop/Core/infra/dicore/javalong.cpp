// JavaLong Class Implementation
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
// ^FILE   : JavaLong.hpp
// ^AUTHOR : Tom Searson
// ^DATE   : 22 March 1999
//
// ^CLASS  : JavaLong
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

#include <stdlib.h>

#ifndef JAVALONG_HPP
   #include "javalong.hpp"
#endif

const DString JavaLong::toString( void )
{
   char buf[ 33 ];

   // Microsoft dependency

   DStringA tmp( _i64toa( m_jlTime, buf, 10 ) );
   return tmp;
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
// $Log:   Y:/VCS/iFastAWD/dicore/javalong.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:20:14   kovacsro
// Initial revision.
// 
//    Rev 1.8   Apr 10 2000 16:38:44   DT14177
// ICU syncup
// 
//    Rev 1.7   Jul 22 1999 11:40:12   DMUM
// Condition re-work
// 
//    Rev 1.6   Jun 27 1999 15:30:14   DT11700
//  
// 
//    Rev 1.5   Jun 17 1999 09:54:58   DT14177
// Added revision control blocks.
// 

