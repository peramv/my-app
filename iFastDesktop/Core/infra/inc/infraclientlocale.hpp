#ifndef INFRACLIENTLOCALE_HPP
#define INFRACLIENTLOCALE_HPP

#pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 2000 by DST Systems, Inc.
 */

/** @pkg DICORE */


/**@#-*/  // forward declarations
namespace Infra
{
   class Locale;
   class ClientLocale;
};

class TracerClient;
/**@#+*/

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef BINFILEHEADER_HPP
   #include "binfileheader.hpp"
#endif

#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif



#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif


/**
 *   ClientLocale is a high-level class that provides support
 *   for markets, clients, and locales.
 */

class DICORE_LINKAGE Infra::ClientLocale
{
public:
   // Globals

public:
   
   /**
    * returns the default ClientLocale
    * 
    * @return 
    */
   static ClientLocale & getDefaultClientLocale();
   
   /**
    * returns the default Infra ClientLocale
    * 
    * @return 
    */
   static const ClientLocale & getDefaultInfraClientLocale();

   /**
    * This will set the default ClientLocale.  Note that 
    * this method is not thread-safe, so no objects should be
    * accessing the default ClientLocale object while
    * it is being set.  Essentially, all threads using any
    * infrastructure components should be in wait states while
    * this method is being called.  This method will make a copy
    * of the passed-in object.
    * 
    * @param ClientLocale
    *            The new defaults for locale, market, and client.
    */
   static void setDefaultInfraClientLocale(
                             const ClientLocale & ClientLocale );

   /**
    * This creates a ClientLocale with the default market
    * and default client that are specified in the .bin file
    */
   ClientLocale();

   /**
    * Constructor
    * 
    * Notice that the default for the client is "No Client" rather
    * than the default client in the .bin file.
    * 
    * @param dstrLocale
    * @param ulMarket
    * @param ulClient
    */
   ClientLocale( const DString & dstrLocale, 
                 unsigned long ulMarket =
                BinFileHeader::getInstance()->getDefaultMarket(),
                 unsigned long ulClient =
                    BinFileHeader::s_ulNoClient );

   /**
    * Constructor
    * 
    * Notice that the default for the client is "No Client" rather
    * than the default client in the .bin file.
    * 
    * @param dstrLocale
    * @param dstrMarket
    * @param dstrClient
    */
   ClientLocale( const DString & dstrLocale,
                 const DString & dstrMarket,
     const DString & dstrClient = BinFileHeader::s_achNoClient );

   /**
    * Constructor
    * 
    * Notice that the default for the client is "No Client" rather
    * than the default client in the .bin file.
    * 
    * @param locale
    * @param dstrMarket
    * @param dstrClient
    */
   ClientLocale( Infra::Locale & locale,
                 const DString & dstrMarket = 
            BinFileHeader::getInstance()->getDefaultMarketName(),
     const DString & dstrClient = BinFileHeader::s_achNoClient );

   /**
    * copy constructor
    * 
    * @param orig
    */
   ClientLocale( const ClientLocale & orig );

   /**
    * assignment operator
    * 
    * @param orig
    * @return 
    */
   ClientLocale & operator=( const ClientLocale & orig );

   /**
    * equality operator
    * 
    * @param orig
    * @return 
    */
   bool operator==( const ClientLocale & orig ) const;

   
   /**
    * less than operator
    * 
    * Used so this object can be an index in maps
    * 
    * @param compare
    * @return 
    */
   bool operator<( const ClientLocale & compare ) const;

   /**
    * Sets the market
    * 
    * Will set client to "No Client"
    * 
    * @param lMarket
    */
   void setMarket( unsigned long lMarket );

   /**
    * Sets the client for the market
    * 
    * @param lClient
    */
   void setClient( unsigned long lClient );

   /**
    * Sets the locale for the market/client
    * 
    * @param locale
    */
   void setLocale( Infra::Locale & locale );

   /**
    * Sets the locale for the market/client
    * 
    * @param dstrLocale
    */
   void setLocale( const DString & dstrLocale );

   /**
    * Sets the market
    * 
    * Will set client to "No Client"
    * 
    * @param dstrMarket
    */
   void setMarket( const DString & dstrMarket );

   /**
    * Sets the client for the market
    * 
    * @param dstrClient
    */
   void setClient( const DString & dstrClient );

   /**
    * returns the index of the market
    * 
    * @return 
    */
   unsigned long getMarketIndex() const
   {
      return m_ulMarket;
   }

   /**
    * return the client index
    * 
    * @return 
    */
   unsigned long getClientIndex() const
   {
      return m_ulClient;
   }


   /**
    * return the locale
    * 
    * @return 
    */
   const Infra::Locale * getLocale() const
   {
      return m_pLocale;
   }


   
   /**
    * return the locale string
    * 
    * Trailing space chars are stripped.
    * 
    * @return 
    */
   const DString & getLocaleString() const
   {
      return m_dstrLocale;
   }


   /**
    * return the market string
    * 
    * @return 
    */
   const DString & getMarket() const
   {
      return m_dstrMarket;
   }


   /**
    * return the client string
    * 
    * @return 
    */
   const DString & getClient() const
   {
      return m_dstrClient;
   }


private:

   // These should be put into the SingletonRegister...
   static ClientLocale * s_pDefaultClientLocale;
   static ClientLocale * s_pDefaultInfraClientLocale;


private:

   DString m_dstrLocale;
   DString m_dstrMarket;
   DString m_dstrClient;

   Infra::Locale * m_pLocale;
   unsigned long   m_ulMarket;
   unsigned long   m_ulClient;

   TRACER_CLASS_VARIABLE;
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
// $Log:   Y:/VCS/iFastAWD/inc/infraclientlocale.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:40   kovacsro
//Initial revision.
//
//   Rev 1.1   28 Dec 2000 13:43:08   dt14177
//fixed compile errors
//
//   Rev 1.0   28 Dec 2000 08:58:34   dt14177
// 
//
//   Rev 1.6   Sep 05 2000 06:05:30   dt17817
//- Remove Certificate/Authenticator
//- Fix threadsafety of client/market
//- Add "null" property value support
//
//
//   Rev 1.5   Aug 24 2000 07:29:52   dtwk
//Add in  more support for clients and markets
//
//   Rev 1.4   Aug 09 2000 08:33:18   dtwk
//Add in support for indexes for clients and markets
//
//   Rev 1.3   Jun 14 2000 12:34:00   dtwk
//Add setter method for default ClientLocale
//
//   Rev 1.2   May 30 2000 14:53:40   dtwk
//Static globals will be created on demand to work around
//application startup errors
//
//   Rev 1.1   May 30 2000 09:10:44   dtwk
//Add copy constructor, operator=, operator==
//Add static global instance that is for Infra defaults
//
//   Rev 1.0   May 26 2000 18:02:00   dtwk
// 
//

#endif // INFRACLIENTLOCALE_HPP
