#pragma once
/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999, 2000 by DST Systems, Inc.
 */

/** @pkg DICORE */

/**
 * FILE: javalong.hpp
 *
 * DESCRIPTION :
 *    stores an __int64 and can create a string
 *
 */


#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#ifndef CONFIGMANAGER_HPP
   #include <configmanager.hpp>
#endif

#ifndef CONDITION_HPP
   #include <condition.hpp>
#endif

#ifndef DSTRING_HPP
   #include <dstring.hpp>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE JavaLong
{

// Implementation
public:

   /**
    * constructor
    * 
    * @param jlTime
    */
   JavaLong( DIINT64 jlTime )
   : m_jlTime( jlTime )
   {
   }

   /**
    * destructor
    */
   virtual ~JavaLong()
   {
   }

   /**
    * see NumberFormat's method description in the ICU
    * documentation.
    * 
    * @return 
    */
   const DString toString(void);

private:
   DIINT64 m_jlTime;  // Microsoft-specific

// Attributes
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/javalong.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:06   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:58   SMITHDAV
//Initial revision.
// 
//    Rev 1.6   Jun 06 2000 17:03:00   DT14177
// added javadoc comments
// 
//    Rev 1.5   Apr 10 2000 16:38:52   DT14177
// ICU syncup
// 
//    Rev 1.4   Jun 01 1999 17:22:34   DTWK
//  
//
//    Rev 1.3   May 12 1999 09:23:10   DT20842
// Added elemental conditions
//
//    Rev 1.2   Apr 08 1999 13:02:24   DMUM
// Added import/export macros
//
//    Rev 1.1   Apr 02 1999 11:26:34   DT20842
// Removed java dependancy (compile/link) when using dicore
//
//    Rev 1.0   Mar 23 1999 09:51:54   DTWK
//
//
//
//
