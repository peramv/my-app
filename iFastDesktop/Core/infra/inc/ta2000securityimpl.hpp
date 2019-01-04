#ifndef TA2000SECURITYIMPL_HPP
#define TA2000SECURITYIMPL_HPP

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

/**@pkg DITA2KDB */


#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef VMREQ_HPP
   #include "vmreq.hpp"
#endif

#ifndef DATA_HPP
   #include "data.hpp"
#endif

class TA2000SecurityImpl
{
public:
   /**
    * See ta2000security.hpp
    */
   TA2000SecurityImpl();

   /**
    * See ta2000security.hpp
    */
   ~TA2000SecurityImpl();

   /**
    * See ta2000security.hpp
    */
   bool logon( const DString &sOperatorId,
               const DString &sPassword,
               const DString &sNewPassword = NULL_STRING,
               pfnSendPreprocess fnSendPreprocess = NULL,
               pfnExtractOverride fnExtractOverride = NULL );

   /**
    * See ta2000security.hpp
    */
   bool logoff( pfnSendPreprocess fnSendPreprocess = NULL,
                pfnExtractOverride fnExtractOverride = NULL );

   /**
    * See ta2000security.hpp
    */
   bool isLoggedOn( void ) const{ return _fLoggedOn; };

   /**
    * See ta2000security.hpp
    */
   const Data& getSignOnData( void ) const;

   /**
    * Only for use by the TA2000LogonAgent
    */
   const Data& getSignOn2Data( void ) const;

   /**
    * See ta2000security.hpp
    */
   bool getValidFundSponsor( const DString& strKey, Data& returnData );

   /**
    * See ta2000security.hpp
    */
   bool setActiveAuthorization( const DString& strSystemId,
                         const DString& strMgmtCo );

   /**
    * See ta2000security.hpp
    */
   bool setActiveFundSponsor( const DString& strFundSponsor );

   /**
    * See ta2000security.hpp
    */
   bool isAuthorizedForFacility( const DString& strFacilityName ) const;

   /**
    * See ta2000security.hpp
    */
   void enableAuthorizationByFacility( bool );

   /**
    * See ta2000security.hpp
    */
   bool facilityAuthorizationIsOn( void ) const;

   /**
    * See ta2000security.hpp
    */
   const DString& getOperatorId( void ) const{ return _sOperatorId; };

   /**
    * See ta2000security.hpp
    */
   void setOperatorId( DString & id )
   {
      _sOperatorId = id;
   }

   /**
    * See ta2000security.hpp
    */
   const DString& getPassword( void ) const{ return _sPassword; };

   /**
    * See ta2000security.hpp
    */
   const DString& getSystem( void ) const{ return _sSystem; };

   /**
    * See ta2000security.hpp
    */
   const DString& getMgmtCo( void ) const{ return _sMgmtCo; };

   /**
    * See ta2000security.hpp
    */
   const DString& getFundSponsor( void ) const{ return _sFundSponsor; };

   /**
    * See ta2000security.hpp
    */
   const unsigned short getLogonCode( void ) const;

   /**
    * See ta2000security.hpp
    */
   void setLogonCode( unsigned short );

   /**
    * See ta2000security.hpp
    */
   void setFacilityName( const DString &strFacilityName );

   /**
    * See ta2000security.hpp
    */
   bool isAuthorizedForAdd( const DString &strFuncName );

   /**
    * See ta2000security.hpp
    */
   bool isAuthorizedForBrowse( const DString &strFuncName );

   /**
    * See ta2000security.hpp
    */
   bool isAuthorizedForDelete( const DString &strFuncName );

   /**
    * See ta2000security.hpp
    */
   bool isAuthorizedForUpdate( const DString &strFuncName );

   /**
    * See ta2000security.hpp
    */
   void setPassword( const DString &strPassword )
   {
      _sPassword = strPassword;
   }

   /**
    * See ta2000security.hpp
    */
   DString getCheckDigitStatus() const;

   /**
    * See ta2000security.hpp
    */
   DString getDealerControlCode() const;

   /**
    * See ta2000security.hpp
    */
   DString getSourceDocMicroCode() const;

   /**
    * See ta2000security.hpp
    */
   DString getDealerSecurityCode() const;

   /**
    * See ta2000security.hpp
    */
   DString getDealerBranchSecurityCode() const;

   /**
    * See ta2000security.hpp
    */
   DString getRepSecurityCode() const;

   /**
    * See ta2000security.hpp
    */
   DString getTaxIdSecurityCode() const;

   // Methods to be called by LogonAgent Do NOT expose these through
   //   the interface class.
   void initializeFromLogonAgent( const DString &str,
                                  Data *pData,
                                  bool bSignOn2 = false );

   void loggedOffThroughLogonAgent();

   void setSessionKey( const DString & str )
   {
      _sSessionKey = str;
   }

   const DString & getSessionKey() const
   {
      return ( _sSessionKey );
   }

private: // members
   enum CONSTANTS {  LEN_OPERATOR_ID = 8,
                     LEN_PASSWORD    = 8,
                     LEN_SYSTEM      = 4,
                     LEN_VIEW_NAME   = 8  };

   typedef std::map< DString, Data *, std::less<DString> > SECURITY_DATA_MAP;
   typedef SECURITY_DATA_MAP::value_type SECURITY_DATA_MAP_TYPE;
   SECURITY_DATA_MAP _operatorSecurityDataMap;

   bool    _fLoggedOn;
   bool    _fFacilityAuthorizationIsOn;
   unsigned short _usLogonCode;
   DString  _sOperatorId;
   DString  _sPassword;
   DString  _sSystem;
   DString  _sMgmtCo;
   DString  _sFundSponsor;
   DString  _sFacilityName;
   DString  _sSessionKey;

   Data  * _pSignOnData;
   Data  * _pSignOn2Data;
   Data  * _pValidFundSponsors;
   Data  * _pFunctionLvlData;

private: //methods
   TA2000SecurityImpl( const TA2000SecurityImpl &copy );
   TA2000SecurityImpl &operator=( const TA2000SecurityImpl &copy );

   bool _buildSecurity( unsigned long ulNumRepeats );
   void _checkForErrorCode( unsigned short viewRC );
   bool _cleanUpSecurity( void );
   SEVERITY _getFunctionLvlData();
   bool _isAuthorizedFor( const DString &strFuncName,
                          const DString &strAccess );
   DString _getSignonDataItem( const DString &itemName ) const;
   const Data* getSignOnDataPtr( void ) const;
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
// $Log:   Y:/VCS/iFastAWD/inc/ta2000securityimpl.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:58   kovacsro
//Initial revision.
// 
//    Rev 1.19   Sep 12 2001 16:53:12   DT11159
// Added code to support sending views directly to a
// destination rather than always using host routing.
// 
//
//    Rev 1.18   28 Mar 2001 14:33:08   DT14177
// added setOperatorId()
//
//    Rev 1.17   Feb 12 2001 12:58:08   dt21858
// Added method to be called by TA2000LogonAgent to be called
// when successfully logged off via the Logon Agent
//
//    Rev 1.16   28 Nov 2000 11:15:50   dt14177
// cleanup
//
//    Rev 1.15   Nov 09 2000 16:24:22   dt21858
// Enhancement to support SIGNON2 via TALogon
//
//    Rev 1.14   Mar 28 2000 14:34:34   dtwk
// - Use SingletonRegister to manage lifetime of TA2000DataBroker and TA2000Security
// - Make threadsafe
//
//    Rev 1.13   Jan 16 2000 14:08:36   dtwk
// Update comments in JavaDoc format
//
//    Rev 1.12   Dec 19 1999 09:28:46   dtwk
// Convert comments to JavaDoc format
//
//    Rev 1.11   Dec 09 1999 09:10:56   dtwk
// Add V002 Support
//
//    Rev 1.10   Nov 19 1999 17:48:36   DMUM
//
//
//    Rev 1.9   Jul 07 1999 14:43:32   DCYK
// Add CBO's checkDigitStatus etc. functions.
//
//
//    Rev 1.8   Apr 21 1999 16:49:40   DCYK
// Updates for Unicode.
//
//
//    Rev 1.7   Mar 05 1999 10:22:06   DCYK
// Changes for I18N.
//
//
//    Rev 1.6   Feb 11 1999 15:42:06   DCYK
// Add support for binary DataElements.
//
//
//    Rev 1.5   Jan 28 1999 14:07:06   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.4   Dec 09 1998 13:43:34   DMUM
// Check in for DICORE
//
//    Rev 1.3   Sep 29 1998 10:37:12   dcyk
// Synch-up with changes for PlanTrac.
//
//    Rev 1.1   Aug 27 1998 16:32:30   dcyk
// Sync-up with changes from PlanTrac.
// Changes only made to ViewFrame code.
//
//
//    Rev 1.0   29 Jul 1998 20:38:10   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.13   Dec 22 1997 09:19:54   dcyk
//
//
//    Rev 1.12   Dec 05 1997 16:42:22   dcyk
//
//
//    Rev 1.11   Nov 10 1997 15:02:48   dcyk
//
//
//    Rev 1.10   10 Sep 1997 12:11:28   dcyk
// Made changes for PlanTrac.
// Async view calls & more processing.
//
//
//    Rev 1.9   07 Aug 1997 15:09:38   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.8   24 Jul 1997 10:58:16   dcyk
// Switched to ULONG, UINT, USHORT &
// UCHAR to save space.
//
//
//    Rev 1.7   13 Jun 1997 18:25:22   dcyk
//
//
//    Rev 1.6   May 09 1997 16:45:18   dcyk
//
//
//    Rev 1.5   May 01 1997 08:48:52   dcyk
// Added newPassword parameter to logon
// function.
//
// Added documentation.
//
//
//    Rev 1.4   Apr 08 1997 16:49:14   dcyk
// In-line some functions to improve performance.
//
//
//    Rev 1.3   Mar 26 1997 10:03:14   dcyk
// Added #include "commonport.h"
// to resolve conflicts caused by what order
// you include ta2000securityimpl.hpp and
// ta2000databroker.hpp.
//
//
//    Rev 1.2   Mar 21 1997 15:36:14   DPQD
// Added new private method _buildSecurity
//
//    Rev 1.1   Mar 17 1997 11:00:36   dlkt
// Created an implimentation class to hide from
// users of security.
//
//    Rev 1.0   Mar 17 1997 09:26:30   dlkt
//

#endif