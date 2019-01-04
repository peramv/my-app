#ifndef AWDDATA_HPP
#define AWDDATA_HPP

#pragma message( "including "__FILE__ )

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

/**@pkg DIAWDI */    

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef AWDKEY_HPP
   #include "awdkey.hpp"
#endif
#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#undef DIAWDI_LINKAGE
#ifdef DIAWDI_DLL
   #define DIAWDI_LINKAGE CLASS_EXPORT
#else
   #define DIAWDI_LINKAGE CLASS_IMPORT
#endif

/**
 * An AwdData object represents the data for an AWD object.  In addition, an
 * AwdData object will hold a pointer to an AwdKey object when the AwdDat object
 * represents an actual AWD object on an AWD server.  To retrieve, update, or
 * create an AWD object on the AWD server, use the AwdInterface class. <br>
 *
 * To keep things simple, AWD fields are also considered LOB data within this
 * class.  The only exception is the begin time and end time.  While methods
 * are provided for specific data [business area, work type, status, object
 * type], they are stored internally as LOB data and will show up if you
 * iterate though the collection.
 */
class DIAWDI_LINKAGE AwdData
{
   // Public enums
   public:
      enum { DATETIME_LEN = 26 };

   // Nested classes
   public:
      /**
       * LobData represents a single line of business (LOB) field for an AWD
       * object.  The LOB data has three parts: the name, the value and a
       * sequence number.  The name is the short name for an AWD Data
       * Dictionary entry and is four characters long.  The value is just that,
       * a value to be stored.  The sequence number allows for a single AWD
       * object to have more than one LOB field with the same name.  For all
       * practicle purposes, let it always default to 1.
       */
      class DIAWDI_LINKAGE LobData
      {
         public:
            /**
             * Constructor
             *
             * @param name - The name of the data
             * @param value - The data value
             * @param seq - The sequence number (Defaults to 1).
             */
            LobData( const DString &name, const DString &value,
                     const int seq = 1 );

            /**
             * Constructor
             *
             * @param copy - LobData object to copy from
             */
            LobData( const LobData &copy );

            /**
             * Constructor
             *
             * @param data - A map of strings to use for initialzation
             */
            LobData( const string_map_type &data );

            /**
             * Destructor
             */
            virtual ~LobData();

         public:
            /**
             * Used to get the name.
             *
             * @return The name.
             */
            const DString getName()  const;

            /**
             * Used to get the value.
             *
             * @return The value.
             */
            const DString & getValue() const;

            /**
             * Used to get the sequence number.
             *
             * @return The sequence number.
             */
            const int getSeqNo() const;

            /**
             * Used to get the sequence number as a DString.
             *
             * @return The sequence number.
             */
            const DString getSeqNoAsString() const;

            /**
             * Assignment operator.
             *
             * @param copy - the LobData object to copy.
             *
             * @return Reference to self.
             */
            LobData & operator=( const LobData &copy );

         private:
            static void setSeqName( DString &seqname,
                                    const int seq,
                                    const DString &name );

         private:
            friend class AwdData;

            string_map_type m_lobData;
      };


      /**
       * The LobIterator class is used to iterate through all the LOB data
       * within an AwdData object.
       */
      class DIAWDI_LINKAGE LobIterator
      {
         // Constructorsand Destructor
         public:

            /**
             * Default constructor
             */
            LobIterator();

            /**
             * Copy constructor
             *
             * @param copy - The LobIterator object to copy.
             */
            LobIterator( const LobIterator &copy );

            /**
             * Destructor
             */
            virtual ~LobIterator();

         // Public methods
         public:
            /**
             * Dereference operator. Dereferencing an LobIterator object will
             * return an LobData object.
             *
             * @return The LobData object referenced by the iterator.
             */
            LobData operator*() const;

            /**
             * Increment operator.
             *
             * @return Reference to self.
             */
            LobIterator & operator++();

            /**
             * Assignment operator.
             *
             * @param copy - The LobIterator object to copy.
             *
             * @return Refernce to self.
             */
            LobIterator & operator=( const LobIterator &copy );

            /**
             * Comparison operator.
             *
             * @param copy - Object to compare with.
             *
             * @return True if they are equal.
             */
            bool operator==( const LobIterator &copy ) const;

            /**
             * Not equals operator.
             *
             * @param copy - Object to compare with.
             *
             * @return True if they are not equal.
             */
            bool operator!=( const LobIterator &copy ) const;

         private:
            friend class AwdData;

            LobIterator( const string_map_iterator &dataPtr,
                         const string_map_iterator &endPtr );

            string_map_iterator m_dataPtr;
            string_map_iterator m_endPtr;
      };

   // Constructors and Destructor
   public:
      /**
       * Default Constructor.
       */
      AwdData();

      /**
       * Constructor with initialization.
       *
       * @param unit - Business area
       * @param wrkt - Work type
       * @param stat - Status
       */
      AwdData( const DString &unit,
               const DString &wrkt,
               const DString &stat );

      /**
       * Copy Constructor.
       *
       * @param copy - copy
       */
      AwdData( const AwdData &copy );

      /**
       * Destructor
       */
      virtual ~AwdData();

   // Public Methods
   public:
      /**
       * Sets AWD line of business (LOB) data.
       *
       * @param name - The name of the data
       * @param value - The data value
       * @param seq - The sequence number (Defaults to 1).
       */
      void setLobData( const DString &name,
                       const DString &value,
                       const int seq = 1 );

      /**
       * Sets AWD line of business (LOB) data.
       *
       * @param lobData - an LobData object
       */
      void setLobData( const LobData &lobData );

      /**
       * Sets the business area
       *
       * @param unit - The business area
       */
      void setUnit( const DString &unit );

      /**
       * Sets the work type (not used for source data objects)
       *
       * @param unit - The work type
       */
      void setWrkt( const DString &wrkt );

      /**
       * Sets the AWD status (not used for source data objects)
       *
       * @param unit - The status
       */
      void setStat( const DString &stat );

      /**
       * Sets the object type (used only for source data object)
       *
       * @param unit - The source's object type
       */
      void setObjt( const DString &objt );

      /**
       * Returns the LOB data for the given name and
       * sequence number.  If not found, an empty value is returned.
       *
       * @param name - The name of the LOB data to retrieve.
       * @param seq - The sequence number. Defaults to 1
       *
       * @return DString - value
       */
      const DString &getLobValue( const DString &name,
                                  const int seq = 1 ) const;

      /**
       * Returns the business area.
       *
       * @return The business area.
       */
      const DString &getUnit() const;

      /**
       * Returns the work type.
       *
       * @return The work type.
       */
      const DString &getWrkt() const;

      /**
       * Returns the status.
       *
       * @return The status.
       */
      const DString &getStat() const;

      /**
       * Returns the object type.
       *
       * @return The object type.
       */
      const DString &getObjt() const;

      /**
       * Sets the Object's begin time.  The format of the DString should be:
       * CCYY-MM-DD-HH.MM.SS.TTTTTT<br>
       *
       * <b>Example:</b> awdData.setBeginTime( "1998-03-10-07.51.34.775842" );
       *
       * @param dateTime - The begin time.
       *
       * @return SEVERE_ERROR if a valid date/time is not passed in.
       */
      SEVERITY setBeginTime( const DString &dateTime );

      /**
       * Sets the Object's end time.  The format of the DString should be:
       * CCYY-MM-DD-HH.MM.SS.TTTTTT<br>
       *
       * <b>Example:</b> awdData.setEndTime( "1998-03-10-07.51.34.775842" );
       *
       * @param dateTime - The end time.
       *
       * @return SEVERE_ERROR if a valid date/time is not passed in.
       */
      SEVERITY setEndTime( const DString &dateTime );

      /**
       * Returns the begin time.
       *
       * @return The begin time.
       */
      const DString &getBeginTime() const { return m_beginTime; };

      /**
       * Returns the end time.
       *
       * @return The end time.
       */
      const DString &getEndTime() const { return m_endTime; };

      /**
       * Assignment operator
       *
       * @param copy   - AwdData object to copy.
       *
       * @return Reference to self.
       */
      AwdData & operator=( const AwdData &copy );

      /**
       * Sets the AwdKey associated with this object.
       *
       * <b>Note:</b> The instance receiving the key takes the responsibility
       * for deleting it.  The caller should <i>not</i> delete the AwdKey
       * object after calling this method.
       *
       * @param awdKey - Pointer to the key.
       */
      void setKey( AwdKey *awdKey );

      /**
       * Returns the pointer to the AwdKey object associated with this object.
       * If there is no key associated, then a NULL will be returned.
       *
       * @return Pointer to the key.
       */
      const AwdKey * getKey() const;

      /**
       * Returns the iterator to the first LOB data.
       *
       * @return The first LOB data item.
       */
      const LobIterator begin();

      /**
       * Returns the iterator to one past the last LOB data.
       *
       * @return The end of the list.
       */
      const LobIterator end();

      /**
       * Returns the count of LOB data items.
       *
       * @return The count of LOB data.
       */
      unsigned short lobCount() const;

   // Private methods
   private:
      SEVERITY validateAndCopyDateTime( const DString &source,
                                        DString &copy );

   // Private members
   private:
      string_map   m_data;
      DString      m_empty;
      DString      m_beginTime;
      DString      m_endTime;
      AwdKey      *m_pKey;
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
// $Log:   Y:/VCS/iFastAWD/inc/awddata.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:44   kovacsro
//Initial revision.
// 
//    Rev 1.9   23 Oct 2000 11:04:42   dt14177
// more cleanup
// 
//    Rev 1.8   23 Oct 2000 10:53:56   dt14177
// cleanup
// 
//    Rev 1.7   Apr 24 2000 10:38:28   DMUM
// Comments to JavaDoc
//
//    Rev 1.6   Apr 20 2000 07:25:18   DMUM
// Comments to JavaDoc
//
//    Rev 1.5   Aug 26 1999 12:58:48   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of a source.
//
//    Rev 1.4   Apr 09 1999 13:26:14   DMUM
// Sync up with 1.6.x
//
//    Rev 1.3   Mar 09 1999 12:55:24   DT20842
// Changes for internationalization
//
//    Rev 1.2   Jan 28 1999 14:05:16   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:37:52   DMUM
// Check in for DICORE
//
//    Rev 1.9   Mar 16 1998 15:41:56   dmum
// Added begin and end Time methods
//
//    Rev 1.8   Dec 30 1997 11:19:34   dmum
// Changed the get methods to be const
//
//    Rev 1.7   Dec 16 1997 15:58:28   dmum
// Made Enhancements
//
//    Rev 1.6   10 Nov 1997 15:01:26   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.5   02 Sep 1997 15:06:06   dmum
// Added new method getSeqNoAsDString()
//
//    Rev 1.4   24 Jun 1997 12:42:06   dmum
// Documented methods
//
//    Rev 1.3   May 22 1997 10:05:10   dmum
// Now uses commontemplates.h
//
//    Rev 1.2   Apr 28 1997 11:11:58   dmum
// Added support for sequence number
//
//    Rev 1.1   Apr 25 1997 11:21:24   dmum
// Second Iteration
//
//    Rev 1.0   Apr 18 1997 09:20:02   dmum
//
//
//

#endif // AWDDATA_HPP
