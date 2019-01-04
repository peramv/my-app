#pragma once
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
// ^FILE   : JavaVM.hpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 01 March 1999
//
// ^CLASS  : DSTJavaVM
// ^PARENT : none
//
// ^CLASS DESCRIPTION :  This is the core class used to manage the Java Virtual Machine
//                       construction and destruction.  It serves as a Singleton.
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
// ----------------------------------------------------------
//
// ^METHOD      : getInstance
//
// ^DESCRIPTION : Starts/Returns pointer to running Java VM.
//
// ^PARAMETERS  : void
//
// ^RETURNS     : DSTJavaVM *
//
// ^THROWS      : None
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : getInstance
//
// ^DESCRIPTION : Starts/Returns pointer to running Java VM.
//
// ^PARAMETERS  : const DString *ClassPath
//
// ^RETURNS     : DSTJavaVM *
//
// ^THROWS      : None
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : removeInstance
//
// ^DESCRIPTION : Removes 1 instance of a running Java VM.
//
// ^PARAMETERS  : void
//
// ^RETURNS     : void
//
// ^THROWS      : None
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : getDSTJavaVM
//
// ^DESCRIPTION : Returns a static pointer to the Java VM Object.
//
// ^PARAMETERS  : void
//
// ^RETURNS     : const  DSTJavaVM *
//
// ^THROWS      : None
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : getInstanceCounter
//
// ^DESCRIPTION : Returns value of instanceCounter.
//
// ^PARAMETERS  : void
//
// ^RETURNS     : int
//
// ^THROWS      : None
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : getEnv
//
// ^DESCRIPTION : Returns pointer of type JNIEnv*.
//
// ^PARAMETERS  : void
//
// ^RETURNS     : JNIEnv *
//
// ^THROWS      : None
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
//******************************************************************************

#ifndef SRCPRAG_H
   #include <srcprag.h>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
#include <map>
#endif

#ifndef DSTRING_HPP
   #include <dstring.hpp>
#endif

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#ifndef CONDITIONMANAGER_HPP
   #include <conditionmanager.hpp>
#endif

#ifndef CONFIGMANAGER_HPP
   #include <configmanager.hpp>
#endif

const char PATH_SEPARATOR = ';';
const int CurrentJREVersion = 0x00010002;


struct JNIEnv_;
typedef JNIEnv_ JNIEnv;

struct JavaVM_;
typedef JavaVM_ JavaVM;

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE DSTJavaVM
{
public:

   // Start with 1 (0 reserved)
   enum
   {
      DSTJAVAVM_JNI_EXCEPTION_CREATEJVM = 1
   } ElementalCondition;


   static DSTJavaVM *getInstance( void );
   static DSTJavaVM *getInstance( const DString &strClassPath );
   static void removeInstance( void );
   const static DSTJavaVM *getDSTJavaVM( void );
   static int getInstanceCounter( void );
   static void attachThread( DWORD dwThreadId );
   static void detachThread( DWORD dwThreadId );
   static JNIEnv *getEnv( void );
   static void setEnv( JNIEnv *pEnv );
   static void unsetEnv( void );
   static void setNoVM( bool fNoVm );
   static bool getNoVM();

private:
   DSTJavaVM();
   DSTJavaVM( const DString &strString );
   ~DSTJavaVM();

   bool createJVM( const DString &strClassPath );

private:
   typedef struct
   {
      JNIEnv *pJNIEnv;
      void   *pJNIArgs;
      DWORD  dwThreadId;
   } JNIThreadInfo; // JNI thread information

   typedef std::map< DWORD, JNIThreadInfo*, std::less< DWORD > > JNIThreadInfoMap;
   typedef JNIThreadInfoMap::value_type env_type;
   typedef JNIThreadInfoMap::iterator env_iterator;

   static JNIThreadInfoMap s_jniMap;
   static DSTJavaVM       *s_DSTjavavm;
   static int              s_instanceCounter;
   static JavaVM          *s_pJvm;
   int                     m_value;
   static bool             s_fNoVM;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/javavm.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:06   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:58   SMITHDAV
//Initial revision.
// 
//    Rev 1.8   Sep 16 1999 15:03:28   dtwk
// Add support for being called from apps that start in Java, and don't want a new JVM and will
// manage the lifetime of the Java objects themselves.
// 
//    Rev 1.7   Jun 29 1999 07:16:14   DTWK
// Update to work with JDK 1.2.x
// 
//    Rev 1.6   Jun 27 1999 15:31:12   DT11700
// made java environment stuff private to support
// multi-threaded use of Infrastructure.
// 
//    Rev 1.5   May 12 1999 09:23:22   DT20842
// Added elemental conditions
// 
//    Rev 1.4   Apr 15 1999 16:03:04   DMUM
// Misc 
//
//    Rev 1.3   Apr 08 1999 13:02:30   DMUM
// Added import/export macros
//
//    Rev 1.2   Apr 02 1999 11:26:40   DT20842
// Removed java dependancy (compile/link) when using dicore
//
//    Rev 1.1   Mar 23 1999 09:42:22   DT20842
// Changes for merge dicore and dilocal
//
//    Rev 1.0   Mar 19 1999 14:40:20   DMUM
//
//
//    Rev 1.1   Mar 11 1999 14:17:52   T27036
// Read JRE Env location from Registry.
//
//    Rev 1.0   Mar 01 1999 13:50:48   MarkT
//
//
//
