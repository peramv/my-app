#pragma once
/**
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

/**@pkg DICORE */

#include <commonport.h>
#include <dstring.hpp>
#include <singletonregister.hpp>

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE AbstractClientLocaleLookup
{
public:
   virtual DString getMarketName( unsigned long ulMarket ) const = 0;
   virtual DString getClientName( unsigned long ulMarket, unsigned long ulClient ) const = 0;
   virtual unsigned long getMarketIndex( const DString& dstrMarket ) const = 0;
   virtual unsigned long getClientIndex( unsigned long ulMarket, const DString& dstrClient ) const = 0;
};

/**
 * This class implements
 *
 * @author DST Systems Inc
 */
class DICORE_LINKAGE ClientLocale
{
public:
   // Globals

   public:
   static const ClientLocale& getDefaultInfraClientLocale();


   // This creates a ClientLocale with the default market and default client
   // that are specified in the .bin file
   ClientLocale();

   // Notice that the default for the client is "No Client" rather than the
   // default client in the .bin file.
   ClientLocale( const DString& dstrLocale,
                 unsigned long ulMarket,
                 unsigned long ulClient );

   // Notice that the default for the client is "No Client" rather than the
   // default client in the .bin file.
   ClientLocale( const DString& dstrLocale,
                 const DString& dstrMarket,
                 const DString& dstrClient );

   ClientLocale( const ClientLocale& orig );

   ClientLocale& operator=( const ClientLocale& orig );

   bool operator==( const ClientLocale& orig ) const;

   // Used so this object can be an index in maps
   bool operator<( const ClientLocale& compare ) const;

   // Will set client to "No Client"
   void setMarket( unsigned long lMarket );

   void setClient( unsigned long lClient );

   void setLocale( const DString& dstrLocale );

   // Will set client to "No Client"
   void setMarket( const DString& dstrMarket );

   void setClient( const DString& dstrClient );

   unsigned long getMarketIndex() const
   {
      return(m_ulMarket);
   }

   unsigned long getClientIndex() const
   {
      return(m_ulClient);
   }

   // Trailing space chars are stripped.
   const DString& getLocale() const
   {
      return(m_dstrLocale);
   }

   const DString& getMarket() const
   {
      return(m_dstrMarket);
   }


   const DString& getClient() const
   {
      return(m_dstrClient);
   }

   LCID getLCID() const;

   static void setLookup( const AbstractClientLocaleLookup* pLookup );

private:

   // These should be put into the SingletonRegister...
   static ClientLocale *s_pDefaultClientLocale;
   static ClientLocale *s_pDefaultInfraClientLocale;
   static SingletonRegister *s_pDefaultsRegister;

   static void removeDefaults( void *pObj );

private:

   DString m_dstrLocale;
   DString m_dstrMarket;
   DString m_dstrClient;

   unsigned long m_ulMarket;
   unsigned long m_ulClient;

   void setLCID();
   LCID lcid_;

   static const AbstractClientLocaleLookup* s_pLookup_;
};


class DICORE_LINKAGE ClientLocale_multimap_compare
{
public:
   ClientLocale_multimap_compare() {}
   bool operator() ( const ClientLocale& lhs, const ClientLocale& rhs ) const;
private:
};


/*******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/clientlocale.hpp-arc  $
//
//   Rev 1.3   Oct 09 2002 17:41:44   PURDYECH
//New PVCS Database
//
//   Rev 1.2   Sep 10 2002 16:20:34   PURDYECH
//ClientLocale aliasing for UK ----> US
//
//   Rev 1.1   Aug 29 2002 13:20:02   PURDYECH
//Removed ClientLocale::getDefaultClientLocale and added context stuff
//
//   Rev 1.0   Jul 05 2002 10:14:34   SMITHDAV
//Initial revision.
//
//   Rev 1.9   Mar 24 2001 13:52:16   dt24433
//Added method to support compare of locale only for multimaps.  Market and client are not compared.
//
//   Rev 1.8   Feb 21 2001 16:28:44   DT21858
// - Added SingletonRegister
// - Some cleanup
//
//   Rev 1.7   23 Oct 2000 12:59:06   dt14177
//cleanup
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
//Static globals will be created on demand to work around application startup errors
//
//   Rev 1.1   May 30 2000 09:10:44   dtwk
//Add copy constructor, operator=, operator==
//Add static global instance that is for Infra defaults
//
//   Rev 1.0   May 26 2000 18:02:00   dtwk
//
//
//
*/
