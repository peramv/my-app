#ifndef CLIENTLOCALE_HPP
#define CLIENTLOCALE_HPP

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

#pragma message( "including "__FILE__ )


#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef JAVALOCALE_HPP
   #include "javalocale.hpp"
#endif

#ifndef BINFILEHEADER_HPP
   #include "binfileheader.hpp"
#endif

#include "singletonregister.hpp"

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif



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
   static ClientLocale& getDefaultClientLocale();
   static const ClientLocale& getDefaultInfraClientLocale();

   /**
    * This will set the default ClientLocale.  Note that this method is not thread
    * safe, so no objects should be accessing the default ClientLocale object while
    * it is being set.  Essentially, all threads using any infrastructure components
    * should be in wait states while this method is being called.
    * This method will make a copy of the passed-in object.
    *
    * @param clientLocale
    *               The new defaults for locale, market, and client.
    */
   static void setDefaultClientLocale( const ClientLocale& clientLocale );

   // This creates a ClientLocale with the default market and default client
   // that are specified in the .bin file
   ClientLocale();

   // Notice that the default for the client is "No Client" rather than the
   // default client in the .bin file.
   ClientLocale( const DString& dstrLocale,
                 unsigned long ulMarket =
                    BinFileHeader::getInstance()->getDefaultMarket(),
                 unsigned long ulClient =
                    BinFileHeader::s_ulNoClient );

   // Notice that the default for the client is "No Client" rather than the
   // default client in the .bin file.
   ClientLocale( const DString& dstrLocale,
                 const DString& dstrMarket,
                 const DString& dstrClient = BinFileHeader::s_achNoClient );

   // Notice that the default for the client is "No Client" rather than the
   // default client in the .bin file.
   ClientLocale( JavaLocale& javaLocale,
                 const DString& dstrMarket =
                    BinFileHeader::getInstance()->getDefaultMarketName(),
                 const DString& dstrClient = BinFileHeader::s_achNoClient );

   ClientLocale( const ClientLocale& orig );

   ClientLocale& operator=( const ClientLocale& orig );

   bool operator==( const ClientLocale& orig ) const;

   // Used so this object can be an index in maps
   bool operator<( const ClientLocale& compare ) const;

   // Will set client to "No Client"
   void setMarket( unsigned long lMarket );

   void setClient( unsigned long lClient );

   void setLocale( JavaLocale& javaLocale );

   void setLocale( const DString& dstrLocale );

   // Will set client to "No Client"
   void setMarket( const DString& dstrMarket );

   void setClient( const DString& dstrClient );

   unsigned long getMarketIndex() const
   {
      return m_ulMarket;
   }

   unsigned long getClientIndex() const
   {
      return m_ulClient;
   }


   const JavaLocale * getJavaLocale() const
   {
      return m_pJavaLocale;
   }


   // Trailing space chars are stripped.
   const DString& getLocale() const
   {
      return m_dstrLocale;
   }


   const DString& getMarket() const
   {
      return m_dstrMarket;
   }


   const DString& getClient() const
   {
      return m_dstrClient;
   }


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

   JavaLocale *m_pJavaLocale;
   unsigned long m_ulMarket;
   unsigned long m_ulClient;
};


class DICORE_LINKAGE ClientLocale_multimap_compare
{
public:
   ClientLocale_multimap_compare() {}
   bool operator() ( const ClientLocale& lhs, const ClientLocale& rhs ) const;
private:
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
// $Log:   Y:/VCS/iFastAWD/inc/clientlocale.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:24   kovacsro
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

#endif
