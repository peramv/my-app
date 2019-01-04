#pragma once

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DICORE */    

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
#include <vector>
#endif

#ifndef DSTRING_HPP
   #include <dstring.hpp>
#endif

#ifndef MUTEXSEMAPHORE_HPP
   #include <mutexsemaphore.hpp>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * Class to be used by Singletons to register themselves.  This will allow a
 * single static method to be called at the end of an application to delete
 * all registered singletons.  Support has been provided so that groups
 * of singletons may be registered and deleted.
 *
 * <b>Example:</b>
 * <pre>
 *
 * class SingleTest
 * {
 * public:
 *    SingleTest()
 *       : m_register()
 *    {
 *       m_register.registerSingleton( deregister, (void *)this );
 *    }
 *
 *    ~SingleTest()
 *    {
 *    }
 *
 * private:
 *    SingletonRegister m_register;
 *
 * private:
 *    static void deregister( void *pObj )
 *    {
 *       SingleTest *pSingleTest = (SingleTest *)pObj;
 *       delete pSingleTest;
 *    }
 * };
 *
 *</pre>
 */
class DICORE_LINKAGE SingletonRegister
{
public:
   typedef void ( far *FN_DEREGISTER )( void * );

public:
   /**
    * Call this method at the end of an application to delete all registered
    * singletons.  All registered singletons or specific groups of singletons
    * may be deleted.
    *
    * @param group  - A string identifying a specific group to be released.  If
    *                 a NULL is passed in, then <i>all</i> registered
    *                 singletons will be released.
    */
   static void releaseSingletons( const I_CHAR *group = NULL );

public:
   /**
    * Default constructor.
    */
   SingletonRegister();

   /**
    * This constructor registers a singleton.
    *
    * @param pfn    - This should be a static method in the singleton's class.
    *
    * @param pObj   - The singleton should pass the "this" pointer.
    *
    * @param group  - A string identifying a specific group.
    */
   SingletonRegister( FN_DEREGISTER pfn, void *pObj,
                      const I_CHAR *group = NULL );

   /**
    * Default constructor.  The registered singleton will be de-registered here.
    */
   virtual ~SingletonRegister();

   /**
    * Call this method to register a singleton if the default SingletonRegister
    * constructor was used.  If the singletons has already been registered,
    * calling the method will re-register the singleton with the parameters
    * passed in.
    *
    * @param pfn    - This should be a static method in the singleton's class.
    *
    * @param pObj   - The singleton should pass the "this" pointer.
    *
    * @param group  - A string identifying a specific group.
    */
   void registerSingleton( FN_DEREGISTER pfn, void *pObj,
                           const I_CHAR *group = NULL );

private:
   SingletonRegister( bool bRegistrar );
   void registerSingleton( SingletonRegister *pSingleton );
   void deRegisterSingleton( SingletonRegister *pSingleton );
   static SingletonRegister *getRegistrar();

private:
   typedef std::vector< SingletonRegister * > SingletonRegistry;

   FN_DEREGISTER m_pfn;
   void *m_pObj;
   DString m_strGroup;
   bool m_bRegistered;
   bool m_bRegistrar;
   MutexSemaphore *m_pMutex;
   SingletonRegistry *m_pRegistry;

   static SingletonRegister *s_pRegistrar;

private:
   /**
    * Not implmented
    *
    * @param copy - object to copy
    */
   SingletonRegister( const SingletonRegister &copy );

   /**
    * Not implmented
    *
    * @param copy - object to copy
    */
   SingletonRegister &operator = ( SingletonRegister &copy );
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/singletonregister.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:16   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:08   SMITHDAV
//Initial revision.
//
//   Rev 1.2   27 Nov 2000 15:48:10   dt14177
//cleanup
//
//   Rev 1.1   Mar 14 2000 13:28:02   DMUM
//Sync up comments with 1.7
//
//   Rev 1.0.1.0   Mar 14 2000 13:18:10   DMUM
//Added example
//
//   Rev 1.0   Mar 14 2000 11:14:40   DMUM
//
//
//    Rev 1.1   Sep 15 1999 15:47:20   DMUM
// Fixed the keywords
//
//    Rev 1.0   Sep 15 1999 15:31:40   DMUM
//
//
//

