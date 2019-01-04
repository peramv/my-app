#ifndef ABSTRACTSECURITY_HPP
#define ABSTRACTSECURITY_HPP

#pragma message( "including "__FILE__ )

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

#ifndef BASESECURITY_HPP
   #include "basesecurity.hpp"
#endif

#ifndef DATA_HPP
   #include "data.hpp"
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
 *  Abstract security class
 *
 *  Class is the common parent for more DST back ends
 *
*/
class DIDBRKR_LINKAGE AbstractSecurity : public BaseSecurity
{
public:
   AbstractSecurity( const DString & operatorId, const DString & hostConnectionManagerId );
   virtual ~AbstractSecurity()
   {
   }

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
    * Change password for user on specified server.  This method is not supported
    *
    * @param sPassword - User password
    * @param sNewPassword - User new password
    *
    * @returns bool - false - This method is not supported
    *
    * @exception VIRTUAL_BASE_METHOD_NOT_SUPPORTED - This method is not supported
    */
   virtual bool changePassword( const DString &sPassword, const DString &sNewPassword );

   /**
    * Return Data object that is populated with data returned from logon process
    *
    * @returns Data - Populated with data returned from logon process
    */
   virtual const Data & getSignOnData( void ) const
   {
      return *_signOn;
   } ;

   /**
    * Return the host connection manager this object associated with
    *
    * @returns DString - Name of the host connection manager
    */
   virtual const DString & getHostConnectionManagerId( void ) const
   {
      return _hostConnectionManagerId;
   };

   /**
    * Return the user this object associated with
    *
    * @returns DString - Name of the user
    */
   virtual const DString & getOperatorId( void ) const
   {
      return _operatorId;
   };

   /**
    * Return the current user password
    *
    * @returns DString - Password of the user
    */
   virtual const DString & getPassword( void ) const
   {
      return _password;
   };

   /**
    * Return indication of whether the user is logged on
    *
    * @returns bool - true if logged on, otherwise false
    */
   virtual bool isLoggedOn( void ) const
   {
      return _isLoggedOn;
   }

protected:
   DString _operatorId;
   DString _hostConnectionManagerId;
   DString _password;
   bool    _isLoggedOn;

   Data *_signOn;

private:
   AbstractSecurity( const AbstractSecurity & copy );
   AbstractSecurity & operator=( const AbstractSecurity & copy );
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
// $Log:   Y:/VCS/iFastAWD/inc/abstractsecurity.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:42   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:53:24   DT11159
// 
//
//

#endif
