#ifndef MESSAGESESSION_HPP
#define MESSAGESESSION_HPP

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
 *    Copyright 2002 by DST Systems, Inc.
 */

/**@pkg DISESSN */


#ifndef COMMONPORT_H
   #include "commonport.h"
#endif
#ifndef SESSION_HPP
   #include "session.hpp"
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
#ifndef CONFIGURATION_HPP
   #include "configuration.hpp"
#endif

#include <list>

#undef DISESSN_LINKAGE
#ifdef DISESSN_DLL
   #define DISESSN_LINKAGE CLASS_EXPORT
#else
   #define DISESSN_LINKAGE CLASS_IMPORT
#endif

class ConfigManager;

class DISESSN_LINKAGE MessageSession
{
   // Constructor and destructor are private
   private:
      MessageSession( Session *pSession, ConfigManager *pManager, bool master );

      virtual ~MessageSession();


   // Public methods
   public:
      void useTable( const Configuration &configTable, bool translateTags = true );

      void useTable( const DString &configIdi, bool translateTags = true );

      void translateTags( bool translateTag = true );

      void addListener( const DString &strListener );

      void removeListener( const DString &strListener );

      void setSendAllEvents( bool sendAllEvents );

      bool getSendAllEvents() { return m_sendAllEvents; }

   // Private methods
   private:
      bool messageEvent( const DString   &strMessageItem,
                         const Configuration &eventCfg,
                         const data_ptr_map  &data );

      void preProcess( const Configuration &eventCfg,
                       const data_ptr_map  &data,
                       Data &messageData);

      void getListeners();

      void notifyAllListeners( const DString &strEvent,
                               const DString &strIdi );


   // Private members
   private:
      typedef std::list<DString> string_list;

      friend class Session;

      Session        *m_pSession;
      ConfigManager  *m_sessionCfgMgr;
      bool            m_masterSession;
      bool            m_translateTags;
      Configuration   m_translationTable;
      Configuration   m_messageCfg;
      string_list     m_lstListeners;
      bool            m_sendAllEvents;
      DString         m_strLastTime;
};




#endif // MESSAGESESSION_HPP


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


