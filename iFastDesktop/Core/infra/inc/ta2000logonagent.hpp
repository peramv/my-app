#ifndef TA2000LOGONAGENT_HPP
#define TA2000LOGONAGENT_HPP

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
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/**@pkg DITA2KDB */

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef SINGLETONREGISTER_HPP
   #include "singletonregister.hpp"
#endif

#ifndef DATA_HPP
   #include "data.hpp"
#endif

#undef DITA2KDB_LINKAGE
#ifdef DITA2KDB_DLL
   #define DITA2KDB_LINKAGE CLASS_EXPORT
#else
   #define DITA2KDB_LINKAGE CLASS_IMPORT
#endif

/**@#-*/
class DString;
class ILogonMgr;
class MutexSemaphore;
class TA2000SecurityImpl;
/**@#+*/

/**
 * Class to simplify interaction with the Logon Manager.
 *
 * This class acts as an agent on behalf of your application when interacting
 * with the TA2000 Logon Manager (TaLogon.exe).  It takes care of necessary
 * steps, updates the TA2000Security singleton, and provides default dialogs
 * for selecting a fund sponsor or a plan/icu.
 */
class DITA2KDB_LINKAGE TA2000LogonAgent
{
////////////////////////
// Interface
public:
   /**
    * This method determines if the TA2000LogonAgent is in use.
    *
    * @return true - if the Logon Agent is in use.
    */
   static bool usingLogonAgent()
   {
      return s_pAgent && s_pAgent->_usingLogonManager();
   }

   /**
    * Use this method to register with a name other than the name passed
    * to ConfigManager::setApplication().  If the Logon Agent has already
    * registered with the Logon manager, this method will return a false.
    * A true will only be returned if the Logon Agent is not already registered
    * and it successfully registers with the Logon Manager.
    *
    * @param name   - The name to use for registration.
    *
    * @return True if registered with the name.  False if already registered.
    */
   static bool registerAs( const DString &dstrName );

   /**
    * This method will determine if it is ok for TA2000SecurityImpl
    * to send the signoff view when it is told to logoff.
    *
    * @param pSecurity Pointer to the TA2000SecurityImpl object
    *
    * @return True if ok to log off
    */
   static bool okToLogOff( const TA2000SecurityImpl *pSecurity );

   /**
    * This method will invoke the Logon Agent if not already present.
    * The Logon Agent will call the IsLoggedOn() method on the Logon Manager
    * (located in TaLogon.exe)
    *
    * @return True if the user had been previously logged on through the
    *         Logon Manager
    */
   static bool isLoggedOn();

   /**
    * This method will attempt to re-establish a logon to
    * the TA2000 Mainframe.
    *
    * @return True if the logon has been re-established
    */
   static bool reEstablishLogon();

   /**
    * This method will invoke the Logon Agent if not already present.
    * The Logon Agent will call the Logon Manager (located in TaLogon.exe)
    * to log a user on to the TA2000 mainframe.
    *
    * @return True if the user is logged on.
    */
   static bool logon();

   /**
    * This method will invoke the Logon Agent if not already present.
    * The Logon Agent will call the Logon Manager (located in TaLogon.exe)
    * to log a user on to the TA2000 mainframe using signon2.
    *
    * @return True if the user is logged on.
    */
   static bool logonSignOn2();

   /**
    * This method will invoke the Logon Agent if not already present
    * and then make sure the user is logged on to the TA2000 mainframe.
    * If the user is logged on, the list of Fund Sponsors will
    * be displayed so the user can select one.
    *
    * @return True if the user is logged on and has successfully selected a
    *         Fund Sponsor.
    */
   static bool selectFundSponsor();

   /**
    * This method will invoke the Logon Agent if not already present
    * and then make sure the user is logged on to the TA2000 mainframe.
    * If the user is logged on, the list of Fund Sponsors will
    * be displayed so the user can select one.
    *
    * @return True if the user is logged on and has successfully selected
    *         an ICU.
    */
   static bool selectICU();

   /**
    * This method will invoke the Logon Agent if not already present.
    * The Logon Agent will then enable the auto logoff feature of the
    * Logon Manager. (This is the Logon Manager's default state).
    *
    * @return True if successfull.
    */
   static bool enableAutoLogoff();

   /**
    * This method will invoke the Logon Agent if not already present.
    * The Logon Agent will then disable the auto logoff feature of the
    * Logon Manager.
    *
    * @return True if successfull.
    */
   static bool disableAutoLogoff();

   /**
    * This method will invoke the Logon Agent if not alreay present and then
    * make sure the user is logged on to AWD.  If the user is not alreay
    * logged on to AWD, the Logon Manager will attempt to log the user on
    * using the ID and password that was used to logon to the TA2000 mainframe.
    *
    * @return True if the user is logged on to AWD.
    */
   static bool logonAWD();

   /**
    * If the Logon Agent is already present, the Logon Agent will request the
    * Logon Manager to logoff.  The Logon Manager will only logoff if there is
    * only one application registered.  If any other application is registered,
    * then this method will return a false, indicating the logoff was not
    * successfull.
    *
    * @return True if logged off.
    */
   static bool logoff();

   /**
    * If the user was signed onto TA2000 with the logonSignOn2() method, this
    * is the method used to retreive the signon data.
    *
    * @return True if logged off.
    */
   static Data getSignOn2Data();

////////////////////////
// Implementation
private:
   static bool _getLogonAgent();
   static bool _affirmLoggedOn();
   static void _deregister( void *pObj );

////////////////////////
// Enumurations
private:
   enum ProcessType
   {
      LA_LOGON,
      LA_RELOGON,
      LA_ENABLE,
      LA_DISABLE,
      LA_LOGON_AWD,
      LA_LOGOFF,
      LA_LOGONSIGNON2,
      LA_ISLOGGEDON
   };

////////////////////////
// Construction
private:
   // default constructor
   TA2000LogonAgent();
   TA2000LogonAgent( const DString &dstrName );
   virtual ~TA2000LogonAgent();

////////////////////////
// Implementation
private:
   void _register( const DString &dstrName );
   void _initialize();
   bool _usingLogonManager() { return 0 != m_registration; }
   bool _processRequest( ProcessType type );
   bool _logon( ILogonMgr &logonMgr );
   bool _logonSignOn2( ILogonMgr &logonMgr );
   bool _makeSelection( int selectionType );

////////////////////////
// Data Members
private:
   SingletonRegister m_register;
   TA2000SecurityImpl *m_pSecurity;
   long m_registration;
   bool m_loggedOn;
   HINSTANCE m_hOle32;
   static TA2000LogonAgent *s_pAgent;
   static MutexSemaphore *s_pMutex;

////////////////////////
// Hidden ctor/assign
//    Prevent accidental use of these methods by restricting access and
//    not providing an implementation (prevent ptr aliasing).
private:
   // Copy constructor, not implemented:
   TA2000LogonAgent( const TA2000LogonAgent &other );

   // Assignmernt operator, not implemented:
   const TA2000LogonAgent & operator=( const TA2000LogonAgent &other );
};


//******************************************************************************
// Inline definitions
//******************************************************************************


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
// $Log:   Y:/VCS/iFastAWD/inc/ta2000logonagent.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:56   kovacsro
//Initial revision.
//
//   Rev 1.10   Feb 12 2001 13:13:06   dt21858
// - Added isLoggedOn() method.
// - Lets TA2000SecurityImpl know when Loggoff was
//   successfully called.
//
//   Rev 1.9   30 Nov 2000 11:27:04   dt14177
//cleanup
//
//   Rev 1.8   Nov 09 2000 16:24:24   dt21858
//Enhancement to support SIGNON2 via TALogon
//
//   Rev 1.7   May 23 2000 13:56:54   DMUM
//Added registgerAs() and made better code re-use
//
//   Rev 1.6   May 22 2000 15:19:16   DMUM
//Added logoff()
//
//   Rev 1.5   Mar 24 2000 12:40:52   DMUM
//Dropped SingletonBase and added SingletonRegister
//
//   Rev 1.1.1.4   Mar 23 2000 09:36:46   DMUM
//Now uses SingletonRegister
//
//   Rev 1.4   Feb 23 2000 17:44:28   DMUM
//Updated comments
//
//   Rev 1.3   Feb 02 2000 12:19:20   DMUM
//Added method to call the LogonMgr::LogonAWD()
//
//   Rev 1.2   Dec 03 1999 13:00:20   DMUM
//Removed argument from reEstablishLogon()
//
//   Rev 1.1   Nov 24 1999 10:09:04   DMUM
//Added / Changed Comments
//
//   Rev 1.0   Nov 19 1999 17:45:08   DMUM
//
//

#endif   // LOGONAGENT_HPP
