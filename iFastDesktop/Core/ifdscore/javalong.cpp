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
   return(tmp);
}

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/javalong.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:06   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:20   SMITHDAV
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

