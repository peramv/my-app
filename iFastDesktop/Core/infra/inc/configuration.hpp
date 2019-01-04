#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#  pragma message( "including "__FILE__ )

/** 
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
   #include "commonport.h"
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef CONFIGVALUE_HPP
   #include "configvalue.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * This class represents a single configuration.
 *
 * A configuration consists of one or more configuration pairs.  Each pair
 * has a key and a value.
 */
class DICORE_LINKAGE Configuration
{
   // Public typedefs
   public:
      typedef std::map<DString, ConfigValue, std::less<DString> >
              config_map;
      typedef config_map::value_type config_type;
      typedef config_map::const_iterator config_const_iterator;
      typedef config_map::iterator config_iterator;

   // Nested classes
   public:
      /**
       * This class represents a <i>key</i> and <i>value</i> pair.  It is used
       * when iterating over the list of configuration pairs within a
       * Configuration object.  See Configuration::iterator.
       */
      class DICORE_LINKAGE ConfigPair
      {
         // Constructors & Destrucor
         public:
            /**
             * Constructor.
             *
             * @param key    - The key
             *
             * @param value  - The value
             */
            ConfigPair( const DString &key, const ConfigValue &value );

            /**
             * Constructor.
             *
             * @param data - A map::value_type
             */
            ConfigPair( const config_type &data );

            /**
             * Copy constructor
             *
             * @param copy - Object to copy
             */
            ConfigPair( const ConfigPair &copy );

            /**
             * Destructor
             */
            virtual ~ConfigPair();

         // Public methods
         public:
            /**
             * Returns the <i>key</i> part of the pair
             *
             * @return The key.
             */
            const DString & getKey() const;

            /**
             * Returns the <i>value</i> part of the pair
             *
             * @return The value.
             */
            const ConfigValue & getValue() const;

            /**
             * Returns the <i>value</i> part of the pair as an integer.
             *
             * @return The value as an integer.
             */
            int getValueAsInt() const;

            /**
             * Returns the <i>value</i> part of the pair as a string.
             *
             * @return The value as a string.
             */
            DString getValueAsString() const;

            /**
             * Returns the <i>value</i> part of the pair as a long.
             *
             * @return The value as a long.
             */
            long getValueAsLong()   const;

            /**
             * Returns the <i>value</i> part of the pair as a double.
             *
             * @return The value as a double.
             */
            double getValueAsDouble() const;

            /**
             * Assignment operator.  Copies the contents of the copy.
             *
             * @param copy   - The object to copy.
             *
             * @return Refernce to *this.
             */
            ConfigPair & operator=( const ConfigPair &copy );

         // Private members
         private:
            friend class Configuration;
            config_type _pair;
      };

      /**
       * This class in an iterator for a Configuration object.
       * Dereferencing this class returns a ConfigPair object.
       */
      class DICORE_LINKAGE iterator
      {
         // Constructors & Destructor
         public:
            /**
             * Default constructor.
             */
            iterator();

            /**
             * Copy constructor
             *
             * @param copy   - Object to copy
             */
            iterator( const iterator &copy );

            /**
             * Destructor
             */
            virtual ~iterator();

         // Public methods
         public:
            /**
             * Dereference operator.  Used to obtain a ConfigPair object.
             *
             * @return The configuration pair pointed to by this iterator.
             */
            ConfigPair operator*() const;

            /**
             * Pre-increment operator.
             *
             * @return Reference to *this.
             */
            iterator & operator++();

            /**
             * Assignment operator.
             *
             * @param copy   - Object to copy.
             *
             * @return Reference to *this.
             */
            iterator & operator=( const iterator & copy );

            /**
             * Comparison operator.  Returns true if the two Iterator
             * objects point to the same configuration pair.
             *
             * @param compare - Object to compare with.
             *
             * @return True if equal.
             */
            bool operator==( const iterator &compare ) const;

            /**
             * Comparison operator.  Returns true if the two Iterator
             * objects point to different configuration pairs.
             *
             * @param compare - Object to compare with.
             *
             * @return True if not equal.
             */
            bool operator!=( const iterator &compare ) const;

         // Private methods
         private:
            iterator( const config_iterator &configPtr,
                      const config_iterator &endPtr );

         // Private members
         private:
            friend class Configuration;

            config_iterator _configPtr;
            config_iterator _endPtr;
      };

   // Constructors & Destructor
   public:
      /**
       * Default Constructor
       */
      Configuration();

      /**
       * Constructor
       *
       * @param name - Name of the configuraiton object
       */
      Configuration( const DString &name );

      /**
       * Constructor - There are three overrides.
       *
       * @param copy - Object to copy
       */
      Configuration( const Configuration &copy );

      /**
       * Destructor
       */
      virtual ~Configuration();

   // Public methods
   public:
      /**
       * Returns the name of the Configuration object.
       *
       * @return The name of the Configuration object.
       */
      const DString & getName() const;

      /**
       * Sets the name of the Configuration object.
       *
       * @param name - Name to use.
       */
      void setName( const DString &name );

      /**
       * Returns a value for the key, as a ConfigValue object.
       * If the key is not found, and empty value is returned.
       *
       * @param key - Value to search for
       *
       * @return Value as a ConfigValue
       */
      ConfigValue getValue( const DString &key ) const;

      /**
       * Returns a value for the key, as a DString
       * If the key is not found, and empty value is returned.
       *
       * @param key - Value to search for
       *
       * @return Value as a DString
       */
      DString getValueAsString( const DString &key ) const;

      /**
       * Returns a value for the key, as an integer.
       * If the key is not found, and empty value is returned.
       *
       * @param key - Value to search for
       *
       * @return Value as an int
       */
      int getValueAsInt( const DString &key ) const;

      /**
       * Returns a value for the key, as an long.
       * If the key is not found, and empty value is returned.
       *
       * @param key - Value to search for
       *
       * @return Value as an long
       */
      long getValueAsLong(  const DString &key ) const;

      /**
       * Returns a value for the key, as an double.
       * If the key is not found, and empty value is returned.
       *
       * @param key - Value to search for
       *
       * @return Value as an double
       */
      double getValueAsDouble(  const DString &key ) const;

      /**
       * Stores a value by the key passed in.
       *
       * @param key - Key for the value
       * @param value - The value
       */
      void set( const DString &key, const ConfigValue &value );

      /**
       * Stores the ConfigPair passed in.
       *
       * @param configPair - Configuration pair to store
       */
      void set( const ConfigPair &configPair );

      /**
       * Stores the "key = value" pair passed in.
       *
       * @param keyEqValue - A string consisting of "key = value"
       */
      bool set( const DString &keyEqValue );

      /**
       * Returns true if the there are no configuration pairs.
       *
       * @return True if the Configuration object is empty.
       */
      bool isEmpty();

      /**
       * Assignment operator.
       *
       * @param copy   - Configuration object to copy
       *
       * @return Reference to *this
       */
      Configuration & operator=( const Configuration &copy );

      /**
       * Returns a Configuration::iterator pointing to the first
       * Configuration::ConfigPair object.
       *
       * @return The iterator to the beginning.
       */
      iterator begin();

      /**
       * Returns a Configuration::iterator pointing to one past the last
       * Configuration::ConfigPair object.
       * <BR>
       * <b>Example:</b>
       * <pre>
       * // Configuration config ...
       *
       * Configuration::iterator cIter = config.begin();
       * const Configuration::iterator cEnd = config.end();
       *
       * while ( cEnd != cIter )
       * {
       *    Configuration::ConfigPair &cPair = *iter;
       *
       *    DString dstrKey = cPair.getKey();
       *    ConfigValue cvValue = cPair.getValue();
       *
       *    ++cIter;
       * } </pre>
       *
       * @return The iterator to the end.
       */
      iterator end();

   // Private members
   private:
      config_map  _data;
      DString _name;

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
// $Log:   Y:/VCS/iFastAWD/inc/configuration.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:42   kovacsro
//Initial revision.
// 
//    Rev 1.6   23 Oct 2000 14:22:42   dt14177
// cleanup
// 
//    Rev 1.5   Feb 24 2000 10:48:04   DMUM
// Converted comments to JavaDoc
//
//    Rev 1.4   22 Feb 1999 11:46:50   DT14177
// fixed DString and const I_CHAR stuff
//
//    Rev 1.3   18 Feb 1999 10:38:54   DT14177
// UNICODE
//
//    Rev 1.2   Jan 28 1999 14:05:46   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:40:16   DMUM
// Check in for DICORE
//
//    Rev 1.3   Jul 11 1998 16:11:42   dmum
// Development - too many changes to describe
//
//    Rev 1.2   Nov 10 1997 12:59:10   DSZD
// Configuration extension. IMPORT/EXPORT.
// MACRO inclusion
//
//    Rev 1.1   24 Jun 1997 13:46:38   dmum
//
//
//    Rev 1.0   02 Jun 1997 12:26:22   dmum
//
//
//

#endif // CONFIGURATION_HPP

