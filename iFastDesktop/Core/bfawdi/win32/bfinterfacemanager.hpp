#pragma once
/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1997-2000 by DST Systems, Inc.
 */

#include <commonport.h>
#include <singletonregister.hpp>
#include <bfawdi\bfawdbaseinterface.hpp>
#include <tinstancemanager.hpp>
#include <windows.h>

/** 
 *  BFInterfaceManager manages which version of AWD client to 
 *  interface with.  This class is a singleton and uses a global
 *  TInstanceManager object to make sure the BFInterfaceManager
 *  object is deleted when the DIAWDI.DLL dll is unloaded.
 */

class BFInterfaceManager
{
public:
   /**
    * returns a pointer to the BFInterfaceManager singleton
    * 
    * @return 
    */
   static BFInterfaceManager * getManager();

   /**
    * Returns an BFAwd###Interface object as a pointer to 
    * the base class BFAwdBaseInterface.
    * 
    * @return 
    */
   BFAwdBaseInterface * newInterface();

   /**
    * Calls the static method 
    * BFAwd___Interface::isLoggedOn()
    * 
    * @return 
    */
   bool isLoggedOn();

   /**
    * Calls the static method BFAwd__Interface::logon()
    * 
    * @param operatorID
    * @param password
    * @param newPassword
    * @return 
    */
   long logon( const DString &operatorID,
               const DString &password,
               const DString &newPassword );

   /**
    * Calls the static method BFAwd___Interface::logoff()
    * 
    * @return 
    */
   long logoff();

   // Constructor & destructor
private:
   BFInterfaceManager();
   virtual ~BFInterfaceManager();

private:
   typedef BFAwdBaseInterface * ( far * OBJ_FACTORY )();
   typedef bool ( far * IS_LOGGED_ON )();
   typedef long ( far * LOGOFF )();
   typedef long ( far * LOGON )( const DString &operatorID,
                                 const DString &password,
                                 const DString &newPassword );

private:
   static BFInterfaceManager *s_pInterfaceManager;

   SingletonRegister m_register;
   HINSTANCE         m_hInterface;
   OBJ_FACTORY       m_pObjectFactory;
   IS_LOGGED_ON      m_pIsLoggedOn;
   LOGOFF            m_pLogoff;
   LOGON             m_pLogon;
   DString           m_interfaceDll;

private:
   void getAwdType();
   static void deregister( void *pObj );
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfawdi/win32/bfinterfacemanager.hpp-arc  $
//
//   Rev 1.2   Nov 27 2002 14:51:24   PURDYECH
//Documentation Cleanup
//
//   Rev 1.1   Oct 09 2002 17:39:58   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:12   SMITHDAV
//Initial revision.
// 
//    Rev 1.9   07 Dec 2000 09:37:52   dt14177
// removed the package javascript directive
// 
//    Rev 1.8   27 Oct 2000 13:18:02   dt14177
// cleanup
// 
//    Rev 1.7   Mar 27 2000 11:15:14   DMUM
// Replaced SingletonBase with SingletonRegister
//
//    Rev 1.6   Sep 30 1999 09:20:28   DMUM
// Started using SingletonBase
//
//    Rev 1.5   Apr 19 1999 07:51:22   DMUM
// Changes for Unicode
//
//    Rev 1.4   Mar 09 1999 12:56:44   DT20842
// Changes for internationalization
//
//    Rev 1.3   Jan 28 1999 14:02:00   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Jan 28 1999 13:42:36   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 15:29:02   DMUM
//
//
//    Rev 1.2   Dec 30 1997 11:26:02   dmum
//
//
//    Rev 1.1   10 Nov 1997 15:21:34   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.0   20 Sep 1997 11:50:34   dmum
//
//
//

