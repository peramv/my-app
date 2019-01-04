#ifndef AWD23INTERFACE_HPP
#define AWD23INTERFACE_HPP

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

/**@pkg DIAWD23 */


// stdafx.h must be included before this header is included

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif
#ifndef AWDBASEINTERFACE_HPP
   #include "awdbaseinterface.hpp"
#endif
#ifndef AWD23KEY_HPP
   #include "awd23key.hpp"
#endif
#ifndef AWDSTRCT_H
   #include "awdstrct.h"
#endif
#ifndef SINGLETONREGISTER_HPP
   #include "singletonregister.hpp"
#endif

#ifndef INCLUDED_AFXMT_H
#define INCLUDED_AFXMT_H
   #include <afxmt.h>
#endif

#undef DIAWD23_LINKAGE
#ifdef DIAWD23_DLL
   #define DIAWD23_LINKAGE CLASS_EXPORT
#else
   #define DIAWD23_LINKAGE CLASS_IMPORT
#endif


/**
 * This class is the AWD 2.3.X implementation of the class AwdInterface
 */

class DIAWD23_LINKAGE Awd23Interface : public AwdBaseInterface
{
   // Constructors & Destructor
   public:
      /**
       * Default constructor
       */
      Awd23Interface();

      /**
       * Destructor
       */
      virtual ~Awd23Interface();

   // Public Methods
   public:
      /**
       * This method implements AwdInterface::getBusinessAreaList()
       */
      virtual string_vector getBusinessAreaList();

      /**
       * This method implements AwdInterface::getWorkTypeList()
       */
      virtual string_vector getWorkTypeList( const DString &busarea );

      /**
       * This method implements AwdInterface::getCaseWorkTypeList()
       */
      virtual string_vector getCaseWorkTypeList( const DString &busarea );

      /**
       * This method implements AwdInterface::getTransWorkTypeList()
       */
      virtual string_vector getTransWorkTypeList( const DString &busarea );

      /**
       * This method implements AwdInterface::getSourceTypeList()
       */
      virtual string_vector getSourceTypeList( const DString &busarea );

      /**
       * This method implements AwdInterface::getStatusList()
       */
      virtual string_vector getStatusList();

      /**
       * This method implements AwdInterface::getStatusList()
       */
      virtual string_vector getStatusList( const AwdKey *pKey );

	  /**
       * This method implements AwdInterface::getStatusList()
       */
      virtual string_vector getStatusList( const AwdKey *pKey, const DString &strBussArea, const DString &strWkType );

      /**
       * This method implements AwdInterface::getQueueList()
       */
      virtual string_vector getQueueList( const I_CHAR type );

      /**
       * This method implements AwdInterface::getAwdFieldList()
       */
      virtual data_obj_map &getAwdFieldList();

      /**
       * This method implements AwdInterface::lookupWork()
       */
      virtual bool lookupWork( const CriteriaVector &criteria );

      /**
       * This method implements AwdInterface::lookupWork()
       */
      virtual ResultVector lookupWork( const CriteriaVector &criteria,
                                       bool &more,
                                       const unsigned long max );

      /**
       * This method implements AwdInterface::lookupSource()
       */
      virtual bool lookupSource( const CriteriaVector &criteria );

      /**
       * This method implements AwdInterface::lookupSource()
       */
      virtual ResultVector lookupSource( const CriteriaVector &criteria,
                                         bool &more,
                                         const unsigned long max );

      /**
       * This method implements AwdInterface::lookupMore()
       */
      virtual ResultVector lookupMore( bool &more );

      /**
       * This method implements AwdInterface::loadCSD()
       */
      virtual bool loadCSD( AwdData &awdData );

      /**
       * This method implements AwdInterface::stopCSD()
       */
      virtual bool stopCSD( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::showAwdContainer()
       */
      virtual bool showAwdContainer( bool bShow );

      /**
       * This method implements AwdInterface::hasActiveService()
       */
      virtual bool hasActiveService( const AwdKey *pKey,
                                     const DString &serviceName );

      /**
       * This method implements AwdInterface::getAllChildren()
       */
      virtual bool getAllChildren( const AwdKey* pKey,
                                   AwdKeyVector &awdKeyVector );

      /**
       * This method implements AwdInterface::getImmediateChildren()
       */
      virtual bool getImmediateChildren( const AwdKey* pKey,
                                         AwdKeyVector &awdKeyVector );

      /**
       * This method implements AwdInterface::loadCSD()
       */
      virtual bool showAwdServiceWindow( const AwdKey *pKey,
                                         const DString &serviceName,
                                         bool show );

      /**
       * This method implements AwdInterface::openAwdContainer()
       */
      virtual bool openAwdContainer();

      /**
       * This method implements AwdInterface::locateAwdContainer()
       */
      virtual bool locateAwdContainer( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::isLocked()
       */
      virtual bool isLocked( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::insertItemInContainer()
       */
      virtual bool insertItemInContainer( const AwdKey *pKey, bool lock );

      /**
       * This method implements AwdInterface::insertItemInContainer()
       */
      virtual bool insertItemInContainer( const AwdKey *pKey,
                                          const AwdKey *pParent,
                                          bool lock );

      /**
       * This method implements AwdInterface::isItemInContainer()
       */
      virtual bool isItemInContainer( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::isItemInContainer()
       */
      virtual bool selectItemInContainer( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::closeAwdContainer()
       */
      virtual bool closeAwdContainer();

      /**
       * This method implements AwdInterface::clearAwdContainer()
       */
      virtual bool clearAwdContainer();

      /**
       * This method implements AwdInterface::expandContainerItemDown()
       */
      virtual bool expandContainerItemDown( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::createAwdTransaction()
       */
      virtual bool createAwdTransaction( AwdData &awdData, bool lock );

      /**
       * This method implements AwdInterface::createAwdCase()
       */
      virtual bool createAwdCase( AwdData &awdData, bool lock );

      /**
       * This method implements AwdInterface::createAwdSource()
       */
      virtual bool createAwdSource( const AwdData &awdData,
                                    const AwdSource::ObjectFormat format,
                                    const DString &strFile,
                                    AwdSource **ppSource,
                                    bool lock );

      /**
       * This method implements AwdInterface::createRelationship()
       */
      virtual bool createRelationship( const AwdKey *pParent,
                                       const AwdKey *pChild );

      /**
       * This method implements AwdInterface::lockAwdObject()
       */
      virtual bool lockAwdObject( const AwdKey *pKey, bool lock );

      /**
       * This method implements AwdInterface::hasCaseForParent()
       */
      virtual bool hasCaseForParent( const AwdKey * pKey, AwdKey **ppParent );

      /**
       * This method implements AwdInterface::hasSourceForChild()
       */
      virtual bool hasSourceForChild( const AwdKey * pKey, AwdKey **ppChild );

      /**
       * This method implements AwdInterface::hasChildren()
       */
      virtual bool hasChildren( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::addComment()
       */
      virtual bool addComment( const AwdKey * pKey, const DString &comment );

      /**
       * This method implements AwdInterface::beginListenCreateObjects()
       */
      virtual bool beginListenCreateObjects();

      /**
       * This method implements AwdInterface::endListenCreateObjects()
       */
      virtual AwdKeyVector endListenCreateObjects();

      /**
       * This method implements AwdInterface::newAwdKey()
       */
      virtual AwdKey * newAwdKey( const DString &createDateTime,
                                  const DString &recordCode,
                                  const DString &createNode );

      /**
       * This method implements AwdInterface::retrieveData()
       */
      virtual bool retrieveData( const AwdKey * pKey,
                                 AwdData &awdData );

      virtual bool retrieveDataLite( const AwdKey *pKey,
                                     AwdData &awdData );

      /**
       * This method implements AwdInterface::retrieveSource()
       */
      virtual bool retrieveSource( const AwdKey * pKey,
                                   AwdSource **ppSource );

      /**
       * This method implements AwdInterface::startService()
       */
      virtual bool startService( const AwdKey *pKey,
                                 const DString &strServiceName );

      /**
       * This method implements AwdInterface::stopService()
       */
      virtual bool stopService( const AwdKey *pKey,
                                const DString &strServiceName );

      /**
       * This method implements AwdInterface::updateAwdObject()
       */
      virtual bool updateAwdObject( AwdData &awdData );

      /**
       * This method implements AwdInterface::getAwdWork()
       */
      virtual bool getAwdWork( AwdData &awdData );

      /**
       * This method implements AwdInterface::getAwdWorkObjects()
       */
      virtual bool getAwdWorkObjects( AwdKeyVector &awdKeyVector );

      /**
       * This method implements AwdInterface::doubleClickContainerItem()
       */
      virtual bool doubleClickContainerItem( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::getCurrentContainerSelection()
       */
      virtual AwdKey * getCurrentContainerSelection();

      /**
       * This method implements AwdInterface::getQueue()
       */
      virtual DString getQueue( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::setQueue()
       */
      virtual bool setQueue( const AwdKey *pKey, const DString &queue );

      /**
       * This method implements AwdInterface::getOperatorID()
       */
      virtual DString getOperatorID();

      /**
       * This method implements AwdInterface::getCountry()
       */
      virtual unsigned long getCountry();

      /**
       * This method implements AwdInterface::getWorkstationID()
       */
      virtual DString getWorkstationID();

      /**
       * This method implements AwdInterface::getServerDateTime()
       */
      virtual DString getServerDateTime();

      /**
       * This method implements AwdInterface::getSuspendCodeList()
       */
      virtual string_vector getSuspendCodeList();

      /**
       * This method implements AwdInterface::suspendWorkObject()
       */
      virtual bool suspendWorkObject( const AwdKey *pKey,
                                      const DString &activateDateTime,
                                      const DString &suspendCode );

      /**
       * This method implements AwdInterface::unSuspendWorkObject()
       */
      virtual bool unSuspendWorkObject( const AwdKey *pKey );

      /**
       * This method implements AwdInterface::isLoggedOn()
       */
      static bool isLoggedOn();

      /**
       * This method implements AwdInterface::isLoggedOn()
       */
      static bool isLoggedOn( AWDApplication *pApp );

      /**
       * This method implements AwdInterface::logon()
       */
      static long logon( const DString &operatorID,
                         const DString &password,
                         const DString &newPassword );

      /**
       * This method implements AwdInterface::logoff()
       */
      static long logoff();

      /**
       * Deletes the AWD23Static object
       *
       * @param pObj
       */
      static void deregister( void *pObj );

   // Public typedefs
   public:
      typedef SHORT ( __stdcall far * API_INSERT )( HWND hwndCont,
                                          PAWDOBJKEY pParentKey,
                                          PAWDOBJ pAwdObj,
                                          BOOL fUpdateCount,
                                          BOOL fLockFlag,
                                          PVOID pReserved);

   // Private Enumerations & typedefs
   private:
      enum ObjectLockType
      {
         OBJ_NOT_LOCKED,
         OBJ_LOCKED_BY_USER,
         OBJ_LOCKED_BY_OTHER
      };

      typedef std::map<unsigned short, DString > group_seq;
      typedef group_seq::value_type group_seq_type;
      typedef group_seq::iterator group_seq_iterator;

      typedef std::map<DString, group_seq > group_map;
      typedef group_map::value_type group_map_type;
      typedef group_map::iterator group_map_iterator;

      typedef std::vector<AWDBase *> awd_obj_list;
      typedef awd_obj_list::reverse_iterator awd_obj_reverse_iterator;

      typedef std::vector<DStringA> string_vector_a;
      typedef string_vector_a::iterator string_vector_a_iterator;

   // Methods
   private:
      bool retrieveData( const AwdKey* pKey,
                         AwdData &awdData,
                         bool bGetSecondaryFields );

      bool getChildren( const AwdKey* pKey,
                        AwdKeyVector &awdKeyVector,
                        bool grandchildren );

      SHORT smartInsert( const Awd23Key *pKey, const Awd23Key *pParent, bool lock, bool add );

      void buildList( ResultVector &workList,
                      AWDTree *pTree,
                      unsigned long limit,
                      unsigned long last = 0 );

      bool lookup( const CriteriaVector & criteria, unsigned long lookupType );

      ResultVector lookup( const CriteriaVector & criteria,
                           unsigned long lookupType,
                           bool & more,
                           const unsigned long max );

      AWDTree *doLookup( const CriteriaVector &criteria,
                         unsigned long lookupType,
                         bool &more );

      char *getComparison( AwdLookupCriteria::Comparison comp );
      string_vector getWorkTypeList( const DString & busarea, const char type );
      bool createAwdWork( AwdData &awdData, bool lock );

      Awd23Key *copyKeyAndRetrieveObject( const Awd23Key *pKey,
                                          AWDBase **ppObj = NULL );

      AWDBase *retrieveObject( const AWDOBJKEY &objKey );
      bool fillLobArray( AwdData & awdData, AWD_AWDLOBARRAYSTRCT & lobArray );

      void formatLobItem( AwdData &awdData,
                          const Data *pAwdField,
                          const DStringA &name,
                          DStringA &value,
                          const int iSeq = 1 );

      ObjectLockType objectLockStatus( AWDBase *pObj );
      static void populateFieldList( AWDApplication * pApp );
      bool verifyFile( const DString &strFile );
      void determineTakeOwnership();

      // static procs used for listener
      static void listenerCallbackProc( AWDEvent * eventObj,
                                        void * pParam );

      static bool findInLockList( const Awd23Key *pKey,
                                  string_vector_a &list,
                                  string_vector_a_iterator &iter,
                                  DStringA &strKey );

      static void addToLockList( const Awd23Key *pKey );
      static bool checkLockList( const Awd23Key *pKey );

      static bool confirmContainer();
      static void closeAwdContainer( HWND hContainer );
      static const Awd23Key *confirmAndCast( const AwdKey *pKey );

   // Nested classes
   private:
      class Awd23Statics
      {
         public:
            Awd23Statics()
              : m_register()
            {
               m_register.registerSingleton( Awd23Interface::deregister,
                                             this,
                                             AwdBaseInterface::getGroup() );
            }

            ~Awd23Statics()
            {
               m_fieldList.erase( m_fieldList.begin(), m_fieldList.end() );
               m_groupList.erase( m_groupList.begin(), m_groupList.end() );
               m_lockList.erase( m_lockList.begin(), m_lockList.end() );
            }

         public:
            data_obj_map    m_fieldList;
            group_map       m_groupList;
            string_vector_a m_lockList;

         private:
            SingletonRegister m_register;
      };


   // Attributes
   private:
      static Awd23Statics *s_pLists;
      static bool          s_loggedOn;
      static bool          s_interfaceContainer;
      static bool          s_listenerActive;
      static HWND          s_hContainer;
      static HMODULE       s_hAwdApi;
      static API_INSERT    s_pAwdApiInsertItemAndTakeOwnership;

      static CCriticalSection s_csListener;
      static AWDOBJKEY        s_lastKey;

      AWDApplication    *m_pApp;
      AWDListener       *m_pListener;
      AWDTree           *m_pTree;
      HWND               m_lkupContainer;
      AwdKeyVector       m_keyList;
      awd_obj_list       m_objList;
};

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::confirmContainer
//
// ^DESCRIPTION : This will confirm that a container is up if the
//                s_containerActive flag is set.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : bool - True if container is active
//
// ^THROWS      : none
//
//******************************************************************************
inline bool Awd23Interface::confirmContainer()
{
   return NULL != s_hContainer;
}

inline void Awd23Interface::closeAwdContainer( HWND hContainer )
{
   // Close the container.
   //
   // Because of Windows 2000 issues, we no longer use the function
   // AwdApiCloseContainer().
   CWnd *pContainer = CWnd::FromHandle( hContainer );
   pContainer->SendMessage( WM_CLOSE );
}

inline const Awd23Key *Awd23Interface::confirmAndCast( const AwdKey *pKey )
{
   const Awd23Key *p23Key = static_cast<const Awd23Key *>( pKey );

   if ( s_loggedOn && ( NULL != p23Key ) && p23Key->isKey() )
   {
      return p23Key;
   }

   return NULL;
}

//******************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/diawd23/awd23interface.hpp-arc  $
//
//   Rev 1.1   30 Jan 2008 14:16:40   kovacsro
//IN#1118094 - added an overloaded getStatusList method
//
//   Rev 1.0   28 Jan 2008 13:16:24   kovacsro
//Initial revision.
// 
//    Rev 1.19   Oct 16 2001 15:03:10   dt21858
// Added stopCSD()
// Added selectItemInContainer()
//
//    Rev 1.18   Aug 23 2001 16:52:56   DT21858
// - Added overloaded method for insertItemInContainer().
// - Code Cleanup
//
//    Rev 1.17   Aug 13 2001 13:56:52   DT21858
// Added getImmediateChildren()
//
//    Rev 1.16   Aug 06 2001 15:07:14   DT21858
// - Sync up eith 1.7.2.10 branch (comments included below)
// - Added getWorkstationID(), getCountry() and implemented getQueueList()
//
//    Rev 1.15   Jun 04 2001 15:00:08   DT21858
// Sync-up with Infra 1.7
//
//    Rev 1.14   Feb 07 2001 09:14:34   dt21858
// Sync up with 1.7
//
//    Rev 1.13   05 Dec 2000 12:56:40   dt14177
// cleanup and documentation
//
//    Rev 1.12   Mar 24 2000 12:32:42   DMUM
// Dropped SingletonBase and now uses SingletonRegister
//
//    Rev 1.6.1.5   Mar 23 2000 09:33:46   DMUM
// Now uses SingletonRegister
//
//    Rev 1.11   Sep 30 1999 09:23:06   DMUM
// Started using SingletonBase
//
//    Rev 1.10   Aug 26 1999 12:55:38   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of
// a service.
//
//    Rev 1.9   Apr 16 1999 17:38:24   DMUM
// Changes for Unicode compiles
//
//    Rev 1.8   Apr 09 1999 13:50:34   DMUM
// Sync up with 1.6.x
//
//    Rev 1.6.1.0   Mar 31 1999 13:20:50   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.6   Feb 19 1999 07:48:50   DMUM
// Added lookupSource()
//
//    Rev 1.0.1.5   Feb 08 1999 15:18:52   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.0.1.4   Jan 20 1999 16:41:52   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.0.1.3   Dec 30 1998 16:12:48   DMUM
// Fixes - for Kemper & for 3.4
//
//    Rev 1.0.1.2   Dec 11 1998 10:12:42   DMUM
// Added loadCSD()
//
//    Rev 1.0.1.1   Oct 01 1998 11:51:24   DMUM
//
//
//    Rev 1.2   Oct 01 1998 11:35:54   DMUM
// Added expandContainerItemDown()
//
//    Rev 1.1   Sep 11 1998 11:59:18   DMUM
// Added getCaseWorkTypeList and
// getTransWorkTypeList
//
//    Rev 1.0   29 Jul 1998 20:28:10   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.9   Jul 23 1998 07:35:46   dmum
// Clean up
//
//    Rev 1.8   May 13 1998 14:19:46   dmum
// Made changes affecting LOB Groups.
// Fixes tickets 2850 through 2857
//
//    Rev 1.7   Mar 16 1998 15:45:38   dmum
// Added isItemInContainer method
//
//    Rev 1.6   Feb 23 1998 11:09:52   dmum
// Uses more SOM interface and less AWD APIs
//
//    Rev 1.5   Jan 29 1998 16:47:22   dmum
// Now grabs LOB items from Indexed and Grouped LOB items
//
//    Rev 1.4   Jan 19 1998 13:46:44   dmum
// Added methods: insertItemInContainer & hasCaseForParent
//
//    Rev 1.3   Dec 30 1997 12:25:40   dmum
//
//
//    Rev 1.2   Dec 16 1997 11:21:14   dmum
// No longer interfaces with AWD32.EXE
//
// Now uses AWD 2.3.0b directly through SOM and APIs
//
//    Rev 1.1   10 Nov 1997 15:17:10   dmum
//
//
//    Rev 1.0   03 Sep 1997 14:22:02   dmum
//
//
//
//

#endif // AWD23INTERFACE_HPP
