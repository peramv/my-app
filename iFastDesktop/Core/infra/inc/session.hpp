#ifndef SESSION_HPP
#define SESSION_HPP

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
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DISESSN */

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef DATA_HPP
   #include "data.hpp"
#endif
#ifndef CONDITION_HPP
   #include "condition.hpp"
#endif
#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#undef DISESSN_LINKAGE
#ifdef DISESSN_DLL
   #define DISESSN_LINKAGE CLASS_EXPORT
#else
   #define DISESSN_LINKAGE CLASS_IMPORT
#endif

class AwdSession;
class LogSession;
//CP20040415class MessageSession;
class ConfigManager;

/**
 * A Session object represents a span of time.  The beginning and end of that
 * time are noted and events may occur in-between.  A Session object created
 * using the default constructor is a 'master' Session object.  Any Session
 * object may have children 'sub' Session objects representing smaller
 * sub-spans of time. <br>
 * <pre>
 *                       T1 E1      E2   T2    E4        T3        E5    T4
 *
 * Master Session object |-----------------------------------------------|
 *
 * Sub Session object 1  |--*-------*----|
 *
 * Sub Session object 2                  |-----*---------|
 *
 * Sub Session object 3                                  |---------*-----|
 *
 * </pre>
 * To notify a Session object of an event, call the method setSessionEvent().
 * Based on configuration entries, Session may record the event in one of two
 * ways:  <b>1</b> Creating / updating AWD work. <b>2</b> Adding a row to
 * an ODBC data source.
 *
 */
class DISESSN_LINKAGE Session
{
   // Constructor & Destructor
   public:
      /**
       * Default constructor
       */
      Session();

      /**
       * Default Destructor
       */
      virtual ~Session();

   // Public methods
   public:

      /**
       * This method is used for generating a timestamp for AWD and ODBC
       * logging purposes.
       *
       * @return
       */
      static const DString getTimeStamp();

      static unsigned long calcDuration( const I_STRING& begin, const I_STRING& end );

      /**
       * Sets data for this session (or sub session) object.
       *
       * @param key    - Tag
       * @param value  - Value
       */
      void setSessionData( const DString &key, const DString &value );

      /**
       * Sets session data for the Master session object.
       *
       * @param key   - Tag
       * @param value - Value
       */
      void setGlobalSessionData( const DString &key, const DString &value );

      /**
       * Returns the value for the specifed tag.  If the tag is not found, an
       * empty string is returned.
       *
       * @param key    - Tag to search for.
       *
       * @return The value requested
       */
      DString getSessionData( const DString &key );

      /**
       * Takes a Data object as input. Sets the element values of the input
       * data object from corresponding keys found in the session object and
       * all parent session objects with the current session object taking
       * precedence over its parents.
       *
       * @param data - Data object to populate.
       */
      void populateData( Data &data );

      /**
       * Informs session of an event.  Session will determine what action to
       * take based on the event identifier and then take action.
       *
       * While this method does not throw an exception, as part of its
       * processing, a ConditionException may be thrown by a member object.
       *
       * @param event - Unique event identifier
       * @param data - Collection of pointers to Data objects.
       *
       * @return Highest severity of all conditions created.
       */
      SEVERITY setSessionEvent( const DString &event, const data_ptr_map &data );

      /**
       * Creates a child (sub)session object and returns it's pointer.
       *
       * @return Pointer to a child session object.
       */
      Session *createSubSession();

      /**
       * Deletes a child session object and cleans up internal pointers.  Only
       * a child session created by this session object should be passed.
       *
       * @param child - Pointer to a child session object.
       *
       * @return True if child session was deleted
       */
      bool endSubSession( Session *child );

      /**
       * Determines whether the option for session to use AWD is turned on
       *
       * @return True if using AWD
       */
      static bool usingAwd() { return s_usingAwd; };

      /**
       * Determines whether the option for session to use ODBC Logging is
       * turned on
       *
       * @return True if logging
       */
      static bool usingLog() { return s_usingLog; };

      static bool usingMessage() { return s_usingMessage; };

      /**
       * Returns a pointer to the member AwdSession object.  This pointer will
       * be NULL if awd is not being used.
       *
       * @return Pointer to member AwdSession object.
       */
      AwdSession *getAwdSession() { return m_pAwdSession; };

      /**
       * Returns a pointer to the member LogSession object.  This pointer will
       * be NULL if ODBC logging is not being used.
       *
       * @return Pointer to member LogSession object.
       */
      LogSession *getLogSession() { return m_pLogSession; };

//CP20040415      MessageSession *getMessageSession() { return m_pMessageSession; };


      /**
       * Returns whether this session object has recorded an event.  An event
       * may be recorded through either AWD or ODBC logging.
       *
       * @return True if an event was recorded.
       */
      bool getEventRecorded() { return m_eventRecorded; };

      /**
       * Sets whether an event was recorded.  If called multiple times, only
       * one of the calls needs to be true to indicate an event was recorded.
       *
       * @param recorded - Whether an event was recorded.
       */
      void setEventRecorded( bool recorded ) { m_eventRecorded |= recorded; };

      bool setBeginSuspend();

      bool setEndSuspend();

      unsigned long getSuspendDuration() { return m_durationSusp; }

   // Private methods
   private:
      Session( Session *parent );
      bool isMaster() { return ( m_MasterSession == this ); };

      void checkForAwd();
      void checkForLog();
      void checkForMessage();

      void deleteChildren();

      bool removeFromChildList( Session *child );

   // Private members
   private:
      typedef std::vector<Session *> child_list;
      typedef child_list::iterator child_iterator;

      Session        *m_parent;
      Session        *m_MasterSession;
      child_list      m_childList;
      Data            m_data;
      ConfigManager  *m_sessionCfgMgr;
      bool            m_okToDelete;
      AwdSession     *m_pAwdSession;
      LogSession     *m_pLogSession;
//CP20040415      MessageSession *m_pMessageSession;
      bool            m_eventRecorded;
      DString         m_strBeginSusp;
      unsigned long   m_durationSusp;

      static bool     s_usingAwd;
      static bool     s_usingLog;
      static bool     s_usingMessage;
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
// $Log:   Y:/VCS/iFastAWD/inc/session.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:40   kovacsro
//Initial revision.
// 
//    Rev 1.9   May 31 2002 07:44:02   DT21858
//  
//
//    Rev 1.8   27 Nov 2000 14:58:04   dt14177
// Cleanup
//
//    Rev 1.7   May 04 2000 16:23:58   DMUM
// Made Session Thread aware
//
//    Rev 1.6   Apr 17 2000 09:35:24   DMUM
// Comments to JavaDoc
//
//    Rev 1.5   Apr 13 2000 13:56:04   DMUM
// Comments converted to Java Doc
//
//    Rev 1.4   May 18 1999 08:50:22   DMUM
//
//
//    Rev 1.3   Apr 09 1999 13:26:28   DMUM
// Sync up with 1.6.x
//
//    Rev 1.1.1.0   Mar 31 1999 13:15:02   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.0   Feb 08 1999 15:11:20   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.0   29 Jul 1998 20:37:54   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.12   Jul 16 1998 11:45:46   dmum
// More developement
//
//    Rev 1.11   Apr 02 1998 11:25:26   dmum
// Made the usingAwd() method static
//
//    Rev 1.10   Mar 27 1998 11:22:54   dmum
// Replaced the string_map with a Data object
//
//    Rev 1.9   Dec 30 1997 12:44:38   dmum
// Moved AWD Specific methosd to the new class
// AwdSession
//
//    Rev 1.8   10 Nov 1997 15:01:36   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.7   20 Sep 1997 12:05:34   dmum
// Removed private member m_pAwd
// added parameter to private method createAwdWork()
//
//    Rev 1.6   10 Sep 1997 11:13:00   dmum
// setSessionEvent() now returns SEVERITY
//
//    Rev 1.5   07 Aug 1997 15:54:28   dmum
// Inlines should not reference class static variables
//
//    Rev 1.4   07 Aug 1997 12:19:16   dmum
// Removed getAwdInterface, added usingAwd.
// Session now creates an AwdInterface object when needed instead
// of having one that is used all the time.
//
//    Rev 1.3   24 Jul 1997 11:07:22   dmum
// Added isAwdDefined
//
//    Rev 1.2   18 Jul 1997 10:43:20   dmum
// Added method isAwdDefined,
// Method setSessionEvent no longer returns anything.
// It will always create a Condition object.
//
//    Rev 1.1   20 Jun 1997 15:22:46   dmum
// Documentation
//
//    Rev 1.0   13 Jun 1997 18:41:56   dmum
//
//
//

#endif // SESSION_HPP


