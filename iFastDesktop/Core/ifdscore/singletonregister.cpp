//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and programs created
//    and maintained by DST Systems, Inc., are proprietary in nature and
//    as such are confidential. Any unauthorized use or disclosure of such
//    information may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//    Last Modified:
//
//    $Author:   PURDYECH  $
//    $Date:   Oct 09 2002 17:42:14  $
//    $Revision:   1.1  $
//
//******************************************************************************

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef SINGLETONREGISTER_HPP
   #include "singletonregister.hpp"
#endif

#ifndef CRITICALSECTION_HPP
   #include "criticalsection.hpp"
#endif

SingletonRegister *SingletonRegister::s_pRegistrar = NULL;

//******************************************************************************
//              Public Methods
//******************************************************************************

////////////////////////////////////////////////////////////////////////////////
void SingletonRegister::releaseSingletons( const I_CHAR *group )
{
   if( NULL != s_pRegistrar )
   {
      s_pRegistrar->m_pMutex->wait();

      // Check for ALL
      bool releaseAll = NULL == group;
      const DString strGroup = ( releaseAll ? I_("") : group );

      SingletonRegistry::iterator iter = s_pRegistrar->m_pRegistry->begin();
      SingletonRegistry::iterator end = s_pRegistrar->m_pRegistry->end();

      while( end != iter )
      {
         SingletonRegister *pSingleton = *iter;

         if( releaseAll || 0 == strGroup.compare( pSingleton->m_strGroup ) )
         {
            FN_DEREGISTER pDeregister = pSingleton->m_pfn;
            void *pObj = pSingleton->m_pObj;

            try
            {
               // Call the delete on the singleton.
               pDeregister( pObj );
            }
            catch( ... )
            {
               s_pRegistrar->m_pRegistry->erase( iter );
            }

            /***********************************************************/
            /* Since deleting a singleton will cause it to de-register */
            /* itself, and since it may delete another singleton it    */
            /* depends on, we will re-initialize the iterators.        */
            /***********************************************************/
            iter = s_pRegistrar->m_pRegistry->begin();
            end = s_pRegistrar->m_pRegistry->end();
         }
         else
         {
            ++iter;
         }
      }

      //
      // If releaseAll, carefully remove the Registrar.
      //
      SingletonRegister *pRegistrar = s_pRegistrar;

      if( releaseAll )
      {
         s_pRegistrar = NULL;
      }

      pRegistrar->m_pMutex->post();

      if( releaseAll )
      {
         delete pRegistrar;
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
SingletonRegister::SingletonRegister()
: m_pfn( NULL ),
m_pObj( NULL ),
m_strGroup( NULL ),
m_bRegistered( false ),
m_bRegistrar( false ),
m_pMutex( NULL ),
m_pRegistry( NULL )
{
}

////////////////////////////////////////////////////////////////////////////////
SingletonRegister::SingletonRegister( FN_DEREGISTER pfn, void *pObj,
                                      const I_CHAR *group )
: m_pfn( pfn ),
m_pObj( pObj ),
m_strGroup( group ),
m_bRegistered( false ),
m_bRegistrar( false ),
m_pMutex( NULL ),
m_pRegistry( NULL )
{
   SingletonRegister *pRegistrar = getRegistrar();
   pRegistrar->registerSingleton( this );
}

////////////////////////////////////////////////////////////////////////////////
SingletonRegister::~SingletonRegister()
{
   if( m_bRegistrar )
   {
      delete m_pMutex;
      delete m_pRegistry;
   }
   else
   {
      SingletonRegister *pRegistrar = getRegistrar();
      pRegistrar->deRegisterSingleton( this );
   }
}

////////////////////////////////////////////////////////////////////////////////
void SingletonRegister::registerSingleton( FN_DEREGISTER pfn, void *pObj,
                                           const I_CHAR *group )
{
   SingletonRegister *pRegistrar = getRegistrar();
   CriticalSection crit( *( pRegistrar->m_pMutex ) );

   m_pfn = pfn;
   m_pObj = pObj;
   m_strGroup = ( NULL == group ? I_("") : group );

   if( ! m_bRegistered )
   {
      pRegistrar->registerSingleton( this );
   }
}

//******************************************************************************
//              Private Methods
//******************************************************************************

////////////////////////////////////////////////////////////////////////////////
SingletonRegister::SingletonRegister( bool bRegistrar )
: m_pfn( NULL ),
m_pObj( NULL ),
m_strGroup( NULL ),
m_bRegistered( false ),
m_bRegistrar( bRegistrar ),
m_pMutex( new MutexSemaphore ),
m_pRegistry( new SingletonRegistry )
{
}

////////////////////////////////////////////////////////////////////////////////
void SingletonRegister::registerSingleton( SingletonRegister *pSingleton )
{
   CriticalSection crit( *m_pMutex );
   m_pRegistry->push_back( pSingleton );
   pSingleton->m_bRegistered = true;
}

////////////////////////////////////////////////////////////////////////////////
void SingletonRegister::deRegisterSingleton( SingletonRegister *pSingleton )
{
   CriticalSection crit( *m_pMutex );

   SingletonRegistry::iterator iter = m_pRegistry->begin();
   const SingletonRegistry::iterator end = m_pRegistry->end();

   while( end != iter )
   {
      SingletonRegister *pRegisteredSingleton = *iter;

      if( pSingleton == pRegisteredSingleton )
      {
         pSingleton->m_bRegistered = false;
         m_pRegistry->erase( iter );
         break;
      }

      ++iter;
   }
}

////////////////////////////////////////////////////////////////////////////////
SingletonRegister *SingletonRegister::getRegistrar()
{
   if( NULL == s_pRegistrar )
   {
      s_pRegistrar = new SingletonRegister( true );
   }

   return(s_pRegistrar);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/singletonregister.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:14   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:26   SMITHDAV
// Initial revision.
//
//   Rev 1.1   Mar 24 2000 12:26:06   DMUM
//Sync up fixes made to 1.7
//
//   Rev 1.0   Mar 14 2000 11:14:06   DMUM
//
//
//

