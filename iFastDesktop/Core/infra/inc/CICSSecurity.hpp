#pragma message( "including "__FILE__ )

#ifndef CICSSECURITY_HPP
#define CICSSECURITY_HPP

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

#ifndef INCLUDED_MAP
   #include <map>
   #define INCLUDED_MAP
#endif

#ifndef INCLUDED_STRING
   #include <string>
   #define INCLUDED_STRING
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef DATA_HPP
   #include "data.hpp"
#endif

#ifndef ABSTRACTSECURITY_HPP
   #include "abstractsecurity.hpp"
#endif

#undef DITA2KDB_LINKAGE
#ifdef DITA2KDB_DLL
   #define DITA2KDB_LINKAGE CLASS_EXPORT
#else
   #define DITA2KDB_LINKAGE CLASS_IMPORT
#endif

/**
 * CICS security class
 *
 * Class is security class for requests made to CICS.
 */
class DITA2KDB_LINKAGE CICSSecurity : public AbstractSecurity
{
public:
   /**
    * Construct a CICSSecurity.
    *
    * @param operatorId operator ID.
    *
    * @param hostConnectionManagerId  contains the name of the host connection
    *                 manager to use for security related requests.
    */
   CICSSecurity( const DString & operatorId, const DString & hostConnectionManagerId );

   ~CICSSecurity();

   /**
    * Logon to the host using the operator ID supplied in the constructor.
    *
    * @param sPassword  contains the password.
    *
    * @param sNewPassword
    *                 contains the new password to change the password and
    *                 logon.  If this parameter is omitted or NULL_STRING is
    *                 passed, the password will not be changed.
    *
    * @return Returns true if successful, otherwise false.
    */
   bool logon( const DString & sPassword,
               const DString & sNewPassword = NULL_STRING );

   /**
    * Logoff the host.
    *
    * @return Returns true if successful, otherwise false.
    */
   bool logoff( );

   /**
    * Get the ID of the host connection manager.
    *
    * @return Returns ID of the host connection manager.
    */
   const DString & getHostConnectionManagerId( void ) const;

   const Data & getSignOnData( void ) const;

   /**
    * Only for use by the TA2000LogonAgent
    */
   const Data & getSignOn2Data( void ) const;

   bool getValidFundSponsor( const DString & strKey, Data & returnData );

   bool setActiveAuthorization( const DString & strSystemId,
                                const DString & strMgmtCo );

   bool setActiveFundSponsor( const DString & strFundSponsor );

   bool isAuthorizedForFacility( const DString & strFacilityName ) const;

   void enableAuthorizationByFacility( bool );

   bool facilityAuthorizationIsOn( void ) const;

   const DString & getOperatorId( void ) const
   {
      return _sOperatorId;
   };

   const DString & getPassword( void ) const
   {
      return _sPassword;
   };

   const DString & getSystem( void ) const
   {
      return _sSystem;
   };

   const DString & getMgmtCo( void ) const
   {
      return _sMgmtCo;
   };

   const DString & getFundSponsor( void ) const
   {
      return _sFundSponsor;
   };

   unsigned short getLogonCode( void ) const;

   void setLogonCode( unsigned short );

   void setFacilityName( const DString & strFacilityName );

   bool isAuthorizedForAdd( const DString & strFuncName );

   bool isAuthorizedForBrowse( const DString & strFuncName );

   bool isAuthorizedForDelete( const DString & strFuncName );

   bool isAuthorizedForUpdate( const DString & strFuncName );

   void setPassword( const DString & strPassword )
   {
      _sPassword = strPassword;
   }

   DString getCheckDigitStatus() const;

   DString getDealerControlCode() const;

   DString getSourceDocMicroCode() const;

   DString getDealerSecurityCode() const;

   DString getDealerBranchSecurityCode() const;

   DString getRepSecurityCode() const;

   DString getTaxIdSecurityCode() const;

#ifdef WIN32

   // Methods to be called by LogonAgent Do NOT expose these through
   //   the interface class.
   void initializeFromLogonAgent( const DString & str,
                                  Data * pData,
                                  bool bSignOn2 = false );
#endif

private: // members
   enum CONSTANTS
   {
      LEN_OPERATOR_ID = 8,
      LEN_PASSWORD    = 8,
      LEN_SYSTEM      = 4,
      LEN_VIEW_NAME   = 8
   };

   typedef std::map< DString, Data *, std::less<DString> > SECURITY_DATA_MAP;
   typedef SECURITY_DATA_MAP::value_type SECURITY_DATA_MAP_TYPE;
   SECURITY_DATA_MAP _operatorSecurityDataMap;

   const DString  _sHostConnectionManagerId;
   bool     _fLoggedOn;
   bool     _fFacilityAuthorizationIsOn;
   unsigned short _usLogonCode;
   DString  _sOperatorId;
   DString  _sPassword;
   DString  _sSystem;
   DString  _sMgmtCo;
   DString  _sFundSponsor;
   DString  _sFacilityName;

   Data  * _pSignOnData;
   Data  * _pSignOn2Data;
   Data  * _pValidFundSponsors;
   Data  * _pFunctionLvlData;

private: //methods
   CICSSecurity( const CICSSecurity & copy );
   CICSSecurity & operator=( const CICSSecurity & copy );

   bool _buildSecurity( unsigned long ulNumRepeats );
   void _checkForErrorCode( long condition );
   bool _cleanUpSecurity( void );
   SEVERITY _getFunctionLvlData();
   bool _isAuthorizedFor( const DString & strFuncName,
                          const DString & strAccess );
   DString _getSignonDataItem( const DString & itemName ) const;
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
// $Log:   Y:/VCS/iFastAWD/inc/CICSSecurity.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:22   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:53:00   DT11159
// 
//
//

#endif
