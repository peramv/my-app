#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and programs created
//    and maintained by DST Systems, Inc., are proprietary in nature and
//    as such are confidential. Any unauthorized use or disclosure of such
//    information may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************

// Define which package we belong to
/** @pkg INFRA */

// Summary description for class
/** One line summary for main index package description */

/**
* CLASS_ONE_LINE_DESCRIPTION
*
* CLASS_IN_DEPTH_DESCRIPTION
*
* <b>    Primary   contact:</b>   Michael McGarry
* <br><b>Secondary contact:</b>
* <br><b>Date created:     </b>   9 Sep 1999
*
* <dl>
* <dt><b>   Last Modified:
* </b><tt>
* <dd>         $Author:   PURDYECH  $
* <dd>         $Date:   Oct 09 2002 17:42:14  $
* <dd>         $Revision:   1.1  $
* </tt>
* </dl>
*
* @see MyRelatedClass
* @see MyRelatedClass::related_method
* @see class_name::related_method
*/

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
#include <vector>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class SingletonManager;

class DICORE_LINKAGE SingletonBase
{
////////////////////////
// Destruction
public:
   virtual ~SingletonBase();

////////////////////////
// Interface
public:
   /**
   * This static method will delete all singletons associated with a particular
   * group.  If a NULL is passed in, All singltons will be deleted including
   * the SingletonManager.
   *
   * @param     const I_CHAR * - group of singletons to delete
   * @returns   void
   * @exception none
   */
   static void releaseSingletons( const I_CHAR *group = NULL );

////////////////////////
// Construction
protected:
   SingletonBase( const I_CHAR *group = NULL );

////////////////////////
// Protected Interface
protected:
   /**
   * Call this method is to re-assign the group this singleton is associated
   * with.
   *
   * @param     const I_CHAR * - group with which the singleton belongs.
   * @returns   void
   * @exception none
   */
   void reAssignGroup( const I_CHAR *group );

////////////////////////
// Hidden ctor/assign
//    Prevent accidental use of these methods by restricting access and
//    not providing an implementation (prevent ptr aliasing).
private:
   // Copy constructor, not implemented:
   SingletonBase( const SingletonBase &copy );
   // Assignmernt operator, not implemented:
   const SingletonBase &operator=( const SingletonBase &copy );

////////////////////////
// Data Members
private:
   SingletonManager *m_pManager;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/singletonbase.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:14   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:08   SMITHDAV
//Initial revision.
// 
//    Rev 1.1   Sep 15 1999 15:47:20   DMUM
// Fixed the keywords
//
//    Rev 1.0   Sep 15 1999 15:31:40   DMUM
//
//
//

