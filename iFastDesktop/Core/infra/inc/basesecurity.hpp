#ifndef BASESECURITY_HPP
#define BASESECURITY_HPP

#  pragma message( "including "__FILE__ )

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

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

// Import/Export resolution

#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class Data;

/**
 *  Base security class
 *
 *  Class is the common parent for all security classes.  It provides the common functions needed for security
 *
*/
class DIDBRKR_LINKAGE BaseSecurity
{
public:
   virtual ~BaseSecurity() {}

    /**
    * Logs user onto specified server
    *
    * @param sPassword - User password
    * @param sNewPassword - User new password
    *
    * @returns bool - true or false depending on success of logon
    */
   virtual bool logon( const DString &sPassword,
               const DString &sNewPassword = NULL_STRING ) = 0;

   /**
    * Logs user off specified server
    *
    * @returns bool - true or false depending on success of logoff
    */
   virtual bool logoff( ) = 0;

   /**
    * Change password for user on specified server
    *
    * @param sPassword - User password
    * @param sNewPassword - User new password
    *
    * @returns bool - true or false depending on success of password change
    */
   virtual bool changePassword( const DString &sPassword, const DString &sNewPassword ) = 0;

   /**
    * Return Data object that is populated with data returned from logon process
    *
    * @returns Data - Populated with data returned from logon process
    */
   virtual const Data & getSignOnData( void ) const = 0;

   /**
    * Return the host connection manager this object associated with
    *
    * @returns DString - Name of the host connection manager
    */
   virtual const DString & getHostConnectionManagerId( void ) const = 0;

   /**
    * Return the user this object associated with
    *
    * @returns DString - Name of the user
    */
   virtual const DString & getOperatorId( void ) const = 0;

   /**
    * Return the current user password
    *
    * @returns DString - Password of the user
    */
   virtual const DString & getPassword( void ) const = 0;

   /**
    * Return indication of whether the user is logged on
    *
    * @returns bool - true if logged on, otherwise false
    */
   virtual bool isLoggedOn( void ) const = 0;
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
// $Log:   Y:/VCS/iFastAWD/inc/basesecurity.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:06   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:53:50   DT11159
// 
//
//

#endif
