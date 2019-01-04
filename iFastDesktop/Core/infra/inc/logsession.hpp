#ifndef LOGSESSION_HPP
#define LOGSESSION_HPP

#pragma message( "including "__FILE__ )

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

/** @pkg DISESSN */

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
#ifndef SESSION_HPP
   #include "session.hpp"
#endif

#undef DISESSN_LINKAGE
#ifdef DISESSN_DLL
   #define DISESSN_LINKAGE CLASS_EXPORT
#else
   #define DISESSN_LINKAGE CLASS_IMPORT
#endif

class Configuration;
class ConfigManager;
class ODBCLink;

/**
 * This class manages ODBC Logging for Session.  Where a Session object
 * represents a span of time, this class does the work of sending update
 * requests (adding rows) to an ODBC Data Source.
 */
class DISESSN_LINKAGE LogSession
{
   public:
      /**
       * Used to determin whether a connection to an ODBC data source has
       * been established.
       *
       * @return True if connected to an ODBC data source.
       */
      bool connectedToDataSource() const { return m_bConnected; }

      /**
       * Used to determine if a Session event has been recorded by adding
       * a row to an ODBC data source.
       *
       * @return True if a row has been added to an ODBC data source.
       */
      bool getEventRecorded() const { return m_bEventRecorded; }

      // Constructors  destructor
   private:
      LogSession( Session *pSession, ConfigManager *pManager, bool master );
      virtual ~LogSession();


   private:
      bool logEvent( const DString &strLogItem,
                     const Configuration &cfgEvent,
                     const data_ptr_map &data );

      void translate( const DString &strTable,
                      const DString &strTableName,
                      const Data *pPrimary,
                      const Data *pDefault,
                      Data &logData );

      void appendKey( DString &strIdi );
      void setEventRecorded( bool recorded );

      LogSession( const LogSession &copy );
      const LogSession &operator=( const LogSession &copy );

   private:
      friend class Session;

      Session       *m_pSession;
      ConfigManager *m_pSessionCfgMgr;
      ODBCLink      *m_pSource;
      bool           m_bMasterSession;
      bool           m_bConnected;
      DString        m_strKeyColumn;
      DString        m_strTable1;
      DString        m_strTable2;
      Data           m_collector;
      bool           m_bEventRecorded;
      bool           m_bSoftColumCheck;
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
// $Log:   Y:/VCS/iFastAWD/inc/logsession.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:14   kovacsro
//Initial revision.
// 
//    Rev 1.6   27 Oct 2000 15:18:34   dt14177
// cleanup
// 
//    Rev 1.5   Apr 17 2000 12:12:06   DMUM
// Comments to JavaDoc
//
//    Rev 1.4   Jun 09 1999 16:21:30   DMUM
// Now supports soft column check to work with an
// ODBC Source that is a text file.
//
//    Rev 1.3   May 18 1999 08:50:20   DMUM
//
//
//    Rev 1.2   Apr 16 1999 17:44:30   DMUM
// Now talks to ODBC again
//
//    Rev 1.1   Apr 09 1999 13:26:26   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.2.0   Mar 31 1999 13:15:00   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0.1.0   Feb 09 1999 10:58:18   DMUM
// Added documentation
//
//    Rev 1.0   Feb 08 1999 14:48:14   DMUM
//
//
//

#endif // LOGSESSION_HPP

