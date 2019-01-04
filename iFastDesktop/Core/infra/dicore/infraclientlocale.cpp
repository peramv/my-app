/* 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

// Make sure the linkage is right!

#define DICORE_DLL

// this file should only be included in the .CPP file

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef INFRACLIENTLOCALE_HPP
   #include "infraclientlocale.hpp"
#endif

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef INFRALOCALE_HPP
   #include "infralocale.hpp"
#endif

static CriticalSectionLock s_lock;

Infra::ClientLocale * Infra::ClientLocale::
                                      s_pDefaultClientLocale = 0;
Infra::ClientLocale * Infra::ClientLocale::
                                 s_pDefaultInfraClientLocale = 0;


void Infra::ClientLocale::setDefaultInfraClientLocale( 
                        const Infra::ClientLocale & clientLocale )
{
   TracerClient tracerClient;

   TRACER_METHOD( I_( "setDefaultInfraClientLocale( " )
                  I_( "Infra::ClientLocale & )" ) );
   

   if ( s_pDefaultInfraClientLocale == &clientLocale )
   {
      return;
   }

   if ( s_pDefaultInfraClientLocale )
   {
      delete s_pDefaultInfraClientLocale;
   }

   s_pDefaultInfraClientLocale = new Infra::ClientLocale( 
                                                  clientLocale );
}


Infra::ClientLocale& Infra::ClientLocale::getDefaultClientLocale()
{
   if ( s_pDefaultClientLocale )
   {
      return *s_pDefaultClientLocale;
   }

   Guard crit( &s_lock );

   if ( s_pDefaultClientLocale )
   {
      return *s_pDefaultClientLocale;
   }

   s_pDefaultClientLocale = new Infra::ClientLocale();

   return *s_pDefaultClientLocale;
}


const Infra::ClientLocale & Infra::ClientLocale::
                                    getDefaultInfraClientLocale()
{
   if ( s_pDefaultInfraClientLocale )
   {
      return *s_pDefaultInfraClientLocale;
   }

   Guard crit( &s_lock );

   if ( s_pDefaultInfraClientLocale )
   {
      return *s_pDefaultInfraClientLocale;
   }

   s_pDefaultInfraClientLocale = 
      new Infra::ClientLocale( I_( "enUS" ),
                        BinFileHeader::s_ulNoMarket,
                        BinFileHeader::s_ulNoClient );

   return *s_pDefaultInfraClientLocale;
}


Infra::ClientLocale::ClientLocale() :
   m_pLocale( Infra::Locale::getDefaultInstance() )
{
   Infra::Locale::getLCV( m_dstrLocale );
   m_dstrLocale.stripTrailing();

   BinFileHeader * pBin = BinFileHeader::getInstance();

   m_ulMarket = pBin->getDefaultMarket();
   m_ulClient = pBin->getDefaultClient();

   pBin->getMarketName( m_ulMarket, m_dstrMarket );
   pBin->getClientName( m_ulMarket, m_ulClient, m_dstrClient );
}


Infra::ClientLocale::ClientLocale( const DString& dstrLocale,
                            unsigned long ulMarket,
                            unsigned long ulClient ) :
   m_pLocale( Infra::Locale::getLocaleInstance( dstrLocale ) ),
   m_ulClient( ulClient ),
   m_ulMarket( ulMarket )
{
   m_dstrLocale = m_pLocale->getLCV();
   m_dstrLocale.stripTrailing();

   BinFileHeader * pBin = BinFileHeader::getInstance();

   pBin->getMarketName( m_ulMarket, m_dstrMarket );
   pBin->getClientName( m_ulMarket, m_ulClient, m_dstrClient );
}


Infra::ClientLocale::ClientLocale( const DString& dstrLocale,
                            const DString& dstrMarket,
                            const DString& dstrClient ) :
   m_dstrLocale( dstrLocale ),
   m_dstrMarket( dstrMarket ), 
   m_dstrClient( dstrClient ),
   m_pLocale( Infra::Locale::getLocaleInstance( dstrLocale ) )
{  
   m_dstrLocale.stripTrailing();
   BinFileHeader * pBin = BinFileHeader::getInstance();
   m_ulMarket = pBin->getMarketIndex( m_dstrMarket );
   m_ulClient = pBin->getClientIndex( m_ulMarket, m_dstrClient );
}


Infra::ClientLocale::ClientLocale( Infra::Locale & locale,
                            const DString& dstrMarket,
                            const DString& dstrClient ) :
   m_dstrMarket( dstrMarket ), 
   m_dstrClient( dstrClient ),
   m_pLocale( &locale )
{
   m_dstrLocale = m_pLocale->getLCV();
   m_dstrLocale.stripTrailing();
   BinFileHeader * pBin = BinFileHeader::getInstance();

   m_ulMarket = pBin->getMarketIndex( m_dstrMarket );
   m_ulClient = pBin->getClientIndex( m_ulMarket, m_dstrClient );
}


Infra::ClientLocale::ClientLocale(
                               const Infra::ClientLocale & orig ) 
   :
   m_dstrLocale( orig.m_dstrLocale ),
   m_dstrMarket( orig.m_dstrMarket ), 
   m_dstrClient( orig.m_dstrClient ),
   m_pLocale( orig.m_pLocale ),
   m_ulMarket( orig.m_ulMarket ),
   m_ulClient( orig.m_ulClient )
{
   m_dstrLocale.stripTrailing();
}


Infra::ClientLocale& Infra::ClientLocale::operator=( 
                                const Infra::ClientLocale& orig )
{
   if ( this == &orig )
   {
      return *this;
   }

   m_dstrLocale = orig.m_dstrLocale;
   m_dstrMarket = orig.m_dstrMarket;
   m_dstrClient = orig.m_dstrClient;
   m_pLocale = orig.m_pLocale;

   m_ulMarket = orig.m_ulMarket;
   m_ulClient = orig.m_ulClient;

   return *this;
}


bool Infra::ClientLocale::operator<(
   const Infra::ClientLocale& compare ) const
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


bool Infra::ClientLocale::operator==( const Infra::ClientLocale &
                                                     orig ) const
{
   if ( m_dstrLocale == orig.m_dstrLocale &&
        m_ulMarket == orig.m_ulMarket &&
        m_ulClient == orig.m_ulClient )
   {
      return true;
   }

   return false;
}


void Infra::ClientLocale::setLocale( Infra::Locale & locale )
{
   TRACER_METHOD( I_( "setLocale( Infra::Locale & )" ) );
   m_pLocale = &locale;
   m_dstrLocale = m_pLocale->getLCV();
   m_dstrLocale.stripTrailing();
}


void Infra::ClientLocale::setLocale( const DString & dstrLocale )
{
   TRACER_METHOD( I_( "setLocale( const DString & )" ) );
   m_dstrLocale = dstrLocale;
   m_pLocale = Infra::Locale::getLocaleInstance( m_dstrLocale );
   m_dstrLocale.stripTrailing();
}


void Infra::ClientLocale::setMarket( const DString & dstrMarket )
{
   TRACER_METHOD( I_( "setMarket( const DString & )" ) );
   m_dstrMarket = dstrMarket;
   BinFileHeader * pBin = BinFileHeader::getInstance();
   m_ulMarket = pBin->getMarketIndex( m_dstrMarket );

   m_dstrClient = BinFileHeader::s_achNoClient;
   m_ulClient = BinFileHeader::s_ulNoClient;
}


void Infra::ClientLocale::setClient( const DString & dstrClient )
{
   TRACER_METHOD( I_( "setClient( const DString & )" ) );
   m_dstrClient = dstrClient;
   BinFileHeader * pBin = BinFileHeader::getInstance();
   m_ulClient = pBin->getClientIndex( m_ulMarket, m_dstrClient );
}


void Infra::ClientLocale::setMarket( unsigned long ulMarket )
{
   TRACER_METHOD( I_( "setMarket( unsigned long )" ) );
   m_ulMarket = ulMarket;
   BinFileHeader * pBin = BinFileHeader::getInstance();
   pBin->getMarketName( m_ulMarket, m_dstrMarket );

   m_dstrClient = BinFileHeader::s_achNoClient;
   m_ulClient = BinFileHeader::s_ulNoClient;
}


void Infra::ClientLocale::setClient( unsigned long ulClient )
{
   TRACER_METHOD( I_( "setClient( unsigned long )" ) );
   m_ulClient = ulClient;
   BinFileHeader * pBin = BinFileHeader::getInstance();
   pBin->getClientName( m_ulMarket, m_ulClient, m_dstrClient );
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
// $Log:   Y:/VCS/iFastAWD/dicore/infraclientlocale.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:19:50   kovacsro
// Initial revision.
//
//   Rev 1.2   May 18 2001 14:27:20   dt24433
//Changes to sync with Java* changes for new ICU.
//
//   Rev 1.1   28 Dec 2000 13:43:06   dt14177
//fixed compile errors
//
//   Rev 1.0   28 Dec 2000 08:54:56   dt14177
// 
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
//Add setter method for default Infra::ClientLocale
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


