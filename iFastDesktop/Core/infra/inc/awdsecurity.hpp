#ifndef AWDSECURITY_HPP
#define AWDSECURITY_HPP

/******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2001 by DST Systems, Inc.
 *
 *
 *******************************************************************************/

#pragma message( "including "__FILE__ )

#ifndef ABSTRACTSECURITY_HPP
   #include "abstractsecurity.hpp"
#endif

#undef DIAWDDB_LINKAGE
#ifdef DIAWDDB_DLL
   #define DIAWDDB_LINKAGE CLASS_EXPORT
#else
   #define DIAWDDB_LINKAGE CLASS_IMPORT
#endif

/**
 *  Class handles the security processing for an AWD server
 *
 */
class DIAWDDB_LINKAGE AWDSecurity : public AbstractSecurity
{
public: //methods

   /**
    * Class matches a user with an AWD server
    *
    * @param operatorId - User Name
    * @param hostConnectionManagerId - Name of the host connection manager
    *
    */
   AWDSecurity( const DString & operatorId, const DString & hostConnectionManagerId );
   virtual ~AWDSecurity();

   /**
    * Logs user onto specified server
    *
    * AWD requests that the logon process be done to all defined connections at once.
    * The logon is done to all defined connections with the number being set via
    * setConnections
    *
    * @param sPassword - User password
    * @param sNewPassword - User new password
    *
    * @returns bool - true if successful, otherwise false
    */
   virtual bool logon( const DString &sPassword,
               const DString &sNewPassword = NULL_STRING );

   /**
    * Logs user off specified server
    *
    * @returns bool - true if successful, otherwise false
    */
   virtual bool logoff( );

   /**
    * Sets the number of connections defined for the AWD server
    *
    * @param numConnections - Number of connections to AWD server
    *
    */
   void setConnections( const int numConnections) { _numConnections = numConnections; }

private: //methods

   AWDSecurity( const AWDSecurity& copy );
   AWDSecurity& operator=( const AWDSecurity& copy );

   enum CONSTANTS {  LEN_OPERATOR_ID = 8,
                     LEN_PASSWORD    = 8,
                     LEN_SYSTEM      = 4,
                     LEN_VIEW_NAME   = 8  };

   Data  * _pSignOnData;

   int     _numConnections;

};

#endif

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
// $Log:   Y:/VCS/iFastAWD/inc/awdsecurity.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:52   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:53:44   DT11159
// 
//
//
