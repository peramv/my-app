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
//    Copyright 2000 by DST Systems, Inc.
//
//

#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef CLIENTLOCALE_HPP
   #include "clientlocale.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef JAVALOCALE_HPP
   #include "javalocale.hpp"
#endif

static CriticalSectionLock lockInit;

ClientLocale * ClientLocale::s_pDefaultClientLocale = 0;
ClientLocale * ClientLocale::s_pDefaultInfraClientLocale = 0;
SingletonRegister * ClientLocale::s_pDefaultsRegister = 0;

void ClientLocale::removeDefaults( void *pObj )
{
   delete s_pDefaultClientLocale;
   delete s_pDefaultInfraClientLocale;
   delete s_pDefaultsRegister;

   s_pDefaultClientLocale = 0;
   s_pDefaultInfraClientLocale = 0;
   s_pDefaultsRegister = 0;
}

void ClientLocale::setDefaultClientLocale( const ClientLocale& clientLocale )
{
   if ( s_pDefaultClientLocale == &clientLocale )
   {
      return;
   }

   if ( s_pDefaultClientLocale )
   {
      delete s_pDefaultClientLocale;
   }

   s_pDefaultClientLocale = new ClientLocale( clientLocale );

   if ( 0 == s_pDefaultsRegister )
   {
      s_pDefaultsRegister = new SingletonRegister( removeDefaults, NULL );
   }
}


ClientLocale& ClientLocale::getDefaultClientLocale()
{
   if ( s_pDefaultClientLocale )
   {
      return *s_pDefaultClientLocale;
   }

   Guard crit( &lockInit );

   if ( s_pDefaultClientLocale )
   {
      return *s_pDefaultClientLocale;
   }

   s_pDefaultClientLocale = new ClientLocale();

   if ( 0 == s_pDefaultsRegister )
   {
      s_pDefaultsRegister = new SingletonRegister( removeDefaults, NULL );
   }

   return *s_pDefaultClientLocale;
}


const ClientLocale& ClientLocale::getDefaultInfraClientLocale()
{
   if ( s_pDefaultInfraClientLocale )
   {
      return *s_pDefaultInfraClientLocale;
   }

   Guard crit( &lockInit );

   if ( s_pDefaultInfraClientLocale )
   {
      return *s_pDefaultInfraClientLocale;
   }

   s_pDefaultInfraClientLocale =
      new ClientLocale( I_( "enUS" ),
                        BinFileHeader::s_ulNoMarket,
                        BinFileHeader::s_ulNoClient );

   if ( 0 == s_pDefaultsRegister )
   {
      s_pDefaultsRegister = new SingletonRegister( removeDefaults, NULL );
   }

   return *s_pDefaultInfraClientLocale;
}


ClientLocale::ClientLocale() :
   m_pJavaLocale( JavaLocale::getDefaultInstance() )
{
   JavaLocale::getLCV( m_dstrLocale );
   m_dstrLocale.stripTrailing();

   BinFileHeader *pBin = BinFileHeader::getInstance();

   m_ulMarket = pBin->getDefaultMarket();
   m_ulClient = pBin->getDefaultClient();

   pBin->getMarketName( m_ulMarket, m_dstrMarket );
   pBin->getClientName( m_ulMarket, m_ulClient, m_dstrClient );
}


ClientLocale::ClientLocale( const DString& dstrLocale,
                            unsigned long ulMarket,
                            unsigned long ulClient ) :
   m_pJavaLocale( JavaLocale::getLocaleInstance( dstrLocale ) ),
   m_ulClient( ulClient ),
   m_ulMarket( ulMarket )
{
   m_dstrLocale = m_pJavaLocale->getLCV();
   m_dstrLocale.stripTrailing();

   BinFileHeader *pBin = BinFileHeader::getInstance();

   pBin->getMarketName( m_ulMarket, m_dstrMarket );
   pBin->getClientName( m_ulMarket, m_ulClient, m_dstrClient );
}


ClientLocale::ClientLocale( const DString& dstrLocale,
                            const DString& dstrMarket,
                            const DString& dstrClient ) :
   m_dstrLocale( dstrLocale ),
   m_dstrMarket( dstrMarket ),
   m_dstrClient( dstrClient ),
   m_pJavaLocale( JavaLocale::getLocaleInstance( dstrLocale ) )
{
   m_dstrLocale.stripTrailing();
   BinFileHeader *pBin = BinFileHeader::getInstance();
   m_ulMarket = pBin->getMarketIndex( m_dstrMarket );
   m_ulClient = pBin->getClientIndex( m_ulMarket, m_dstrClient );
}


ClientLocale::ClientLocale( JavaLocale &javaLocale,
                            const DString& dstrMarket,
                            const DString& dstrClient ) :
   m_dstrMarket( dstrMarket ),
   m_dstrClient( dstrClient ),
   m_pJavaLocale( &javaLocale )
{
   m_dstrLocale = m_pJavaLocale->getLCV();
   m_dstrLocale.stripTrailing();
   BinFileHeader *pBin = BinFileHeader::getInstance();

   m_ulMarket = pBin->getMarketIndex( m_dstrMarket );
   m_ulClient = pBin->getClientIndex( m_ulMarket, m_dstrClient );
}


ClientLocale::ClientLocale( const ClientLocale& orig ) :
   m_dstrLocale( orig.m_dstrLocale ),
   m_dstrMarket( orig.m_dstrMarket ),
   m_dstrClient( orig.m_dstrClient ),
   m_pJavaLocale( orig.m_pJavaLocale ),
   m_ulMarket( orig.m_ulMarket ),
   m_ulClient( orig.m_ulClient )
{
   m_dstrLocale.stripTrailing();
}


ClientLocale& ClientLocale::operator=( const ClientLocale& orig )
{
   if ( this == &orig )
   {
      return *this;
   }

   m_dstrLocale = orig.m_dstrLocale;
   m_dstrMarket = orig.m_dstrMarket;
   m_dstrClient = orig.m_dstrClient;
   m_pJavaLocale = orig.m_pJavaLocale;

   m_ulMarket = orig.m_ulMarket;
   m_ulClient = orig.m_ulClient;

   return *this;
}


bool ClientLocale::operator<(
   const ClientLocale& compare ) const
{
   if ( m_ulMarket < compare.m_ulMarket )
   {
      return true;
   }

   if ( m_ulMarket > compare.m_ulMarket )
   {
      return false;
   }

   if ( m_ulClient < compare.m_ulClient )
   {
      return true;
   }

   if ( m_ulClient > compare.m_ulClient )
   {
      return false;
   }

   if ( m_dstrLocale < compare.m_dstrLocale )
   {
      return true;
   }

   return false;
}


bool ClientLocale::operator==( const ClientLocale& orig ) const
{
   if ( m_dstrLocale == orig.m_dstrLocale &&
        m_ulMarket == orig.m_ulMarket &&
        m_ulClient == orig.m_ulClient )
   {
      return true;
   }

   return false;
}


void ClientLocale::setLocale( JavaLocale& javaLocale )
{
   m_pJavaLocale = &javaLocale;
   m_dstrLocale = m_pJavaLocale->getLCV();
   m_dstrLocale.stripTrailing();
}


void ClientLocale::setLocale( const DString& dstrLocale )
{
   m_dstrLocale = dstrLocale;
   m_pJavaLocale = JavaLocale::getLocaleInstance( m_dstrLocale );
   m_dstrLocale.stripTrailing();
}


void ClientLocale::setMarket( const DString& dstrMarket )
{
   m_dstrMarket = dstrMarket;
   BinFileHeader *pBin = BinFileHeader::getInstance();
   m_ulMarket = pBin->getMarketIndex( m_dstrMarket );

   m_dstrClient = BinFileHeader::s_achNoClient;
   m_ulClient = BinFileHeader::s_ulNoClient;
}


void ClientLocale::setClient( const DString& dstrClient )
{
   m_dstrClient = dstrClient;
   BinFileHeader *pBin = BinFileHeader::getInstance();
   m_ulClient = pBin->getClientIndex( m_ulMarket, m_dstrClient );
}


void ClientLocale::setMarket( unsigned long ulMarket )
{
   m_ulMarket = ulMarket;
   BinFileHeader *pBin = BinFileHeader::getInstance();
   pBin->getMarketName( m_ulMarket, m_dstrMarket );

   m_dstrClient = BinFileHeader::s_achNoClient;
   m_ulClient = BinFileHeader::s_ulNoClient;
}


void ClientLocale::setClient( unsigned long ulClient )
{
   m_ulClient = ulClient;
   BinFileHeader *pBin = BinFileHeader::getInstance();
   pBin->getClientName( m_ulMarket, m_ulClient, m_dstrClient );
}


bool ClientLocale_multimap_compare::operator()
   ( const ClientLocale& lhs,
     const ClientLocale& rhs ) const
{  // Compare class which only compares locale without extensions
   if ( lhs.getLocale() < rhs.getLocale() )
   {
      return true;
   }

   return false;
}


/*******************************************************************************
//              Revision Control Entries
//******************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/dicore/clientlocale.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:20   kovacsro
// Initial revision.
//
//   Rev 1.9   May 18 2001 14:54:18   dt24433
//Switched to Guard\CriticalSectionLock from CriticalSection\MutexSemaphore.
//
//   Rev 1.8   Mar 24 2001 13:51:24   dt24433
//Added method to support compare of locale only for multimaps.  Market and client are not compared.
//
//   Rev 1.7   Feb 21 2001 16:26:10   DT21858
// - Added SingletonRegister
// - Did some cleanup
//
//   Rev 1.6   Sep 05 2000 06:19:02   dt17817
//- Remove Certificate/Authenticator
//- Fix threadsafety of client/market
//- Add "null" property value support
//
//
//   Rev 1.5   Aug 24 2000 07:28:18   dtwk
//Add in more support for clients and markets
//
//   Rev 1.4   Aug 09 2000 08:32:12   dtwk
//Add in support for indexes for markets and clients
//
//   Rev 1.3   Jun 14 2000 12:33:56   dtwk
//Add setter method for default ClientLocale
//
//   Rev 1.2   May 30 2000 14:53:12   dtwk
//Static globals will be created only on demand to work around application startup errors
//
//   Rev 1.1   May 30 2000 09:10:08   dtwk
//Add copy constructor, operator=, operator==
//Add static global instance that is for Infra defaults
//
//   Rev 1.0   May 26 2000 18:01:30   dtwk
//
//
//
*/


