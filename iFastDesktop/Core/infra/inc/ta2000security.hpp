#ifndef TA2000SECURITY_HPP
#define TA2000SECURITY_HPP

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

#pragma message( "including "__FILE__ )

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

#ifdef _WIN32

#ifndef TA2000LOGONAGENT_HPP
   #include "TA2000logonagent.hpp"
#endif

#endif

#ifndef BASEDBSECURITY_HPP
   #include "basedbsecurity.hpp"
#endif



// Forward declaration of implementation class
class TA2000SecurityImpl;

#undef DITA2KDB_LINKAGE
#ifdef DITA2KDB_DLL
   #define DITA2KDB_LINKAGE CLASS_EXPORT
#else
   #define DITA2KDB_LINKAGE CLASS_IMPORT
#endif

class DITA2KDB_LINKAGE TA2000Security : BaseDBSecurity
{
public: //methods

   /**
    * Logs the specified operator on.
    *
    * @param sOperatorId
    *                  - (in) string containing the operator id to
    *                  log on as.
    * @param sPassword - (in) string containing the password.
    * @param sNewPassword
    *                  - (in) string containing the new password,
    *                  if wanted.  Defaults to an empty string.
    * @param fnSendPreprocess
    *                  - set a callback that will be invoked on the data stream
    *                  before it is sent to the host.
    * @param fnExtractOverride
    *                  - set a callback that will be invoked on the data stream
    *                  after it is returned from the host, and before it is parsed.
    * @return true if the log on was successful, false otherwise.
    * @exception ConditionException&
    *                   - if the repeat area data could not be
    *                   retrieved.
    */
   bool logon( const DString &sOperatorId, const DString &sPassword,
               const DString &sNewPassword = NULL_STRING,
               pfnSendPreprocess fnSendPreprocess = NULL,
               pfnExtractOverride fnExtractOverride = NULL );

   /**
    * Logs the current user off.
    *
    * @param fnSendPreprocess
    *                  - set a callback that will be invoked on the data stream
    *                  before it is sent to the host.
    * @param fnExtractOverride
    *                  - set a callback that will be invoked on the data stream
    *                  after it is returned from the host, and before it is parsed.
    * @return true if the log off was successful, false otherwise.
    *
    */
   bool logoff( pfnSendPreprocess fnSendPreprocess = NULL,
                pfnExtractOverride fnExtractOverride = NULL );

   /**
    * Checks of the current user is logged on.
    *
    * @return true if the user is logged on, false otherwise.
    *
    */
   bool isLoggedOn( void ) const;

   /**
    * Gets the signon information for the current user.
    *
    * @return a Data object containing the signon information.
    * @exception ConditionException& - if the operator is not logged on.
    *
    */
   Data getSignOnData( void ) const;

   /**
    * Populate the passed-in Data object with the sigon return data
    * for the passed-in fund sponsor.
    *
    * @param strKey - this can be either a fund sponsor id or a
    *               management company string.
    *
    * @param returnData - this will be filled with the data from one of the sigon
    *                   view's repeat records.
    * @return true if strKey is a valid fund sponsor for the operator,
    *         false otherwise.
    */
   bool getValidFundSponsor( const DString& strKey, Data& returnData );

   /**
    * Gets the id of the current operator.
    *
    * @return the operator id.
    *
    */
   DString getOperatorId( void ) const;

   /**
    * Gets the password of the current operator.
    *
    * @return the password
    */
   DString getPassword( void ) const;

   /**
    * Gets the system that the operator is currently logged on.
    *
    * @return the system that the operator is currently logged on.
    *
    */
   DString getSystem( void ) const;

   /**
    * Gets the management company.
    *
    * @return the management company.
    *
    */
   DString getMgmtCo( void ) const;

   /**
    * Gets the currently active fund sponsor.
    *
    * @return the fund sponsor.
    *
    */
   DString getFundSponsor( void ) const;

   /**
    * Sets the system and management company for the current
    * operator.
    *
    * @param strSystemId
    *                  - (in) string containing the system id to
    *                  authorize the operator for.
    * @param strMgmtCo - (in) string containing the management company
    *                  to authorize the operator for.
    * @return true if the authorization was successfully set, false otherwise.
    */
   bool setActiveAuthorization( const DString& strSystemId,
                         const DString& strMgmtCo );

   bool setActiveFundSponsor( const DString& strFundSponsor );

   /**
    * Checks if the current operator is authorized for the specified
    * facility.
    *
    * @param strFacilityName - (in) string containing the name of the
    *        facility to check the authorization for.
    * @return true if the operator is authorized for the
    *         specified facility, false otherwise.
    *
    */
   bool isAuthorizedForFacility( const DString& strFacilityName ) const;

   /**
    * Gets a pointer to a TA2000Security object.
    *
    * @return a pointer to a TA2000Security object.
    *
    */
   static TA2000Security * getInstance( void );

   /**
    * Turn on or off checking for security for different facilities.
    * This method should be called before logon().
    *
    * @param opAuth - true is the facility authorization checks should be made,
    *               false otherwise.
    */
   void enableAuthorizationByFacility( bool opAuth );

   /**
    * Check whether facility authorization checking is on.
    *
    * @return true if it is on, false otherwise.
    */
   bool facilityAuthorizationIsOn( void ) const;

   /**
    * Set the facility name to be used in the isAuthorizedFor* methods.
    * This should be called before any of those methods.
    *
    * @param strFacilityName
    *               - the facility name to check (MAINT, NASU, etc.)
    */
   void setFacilityName( const DString &strFacilityName );

   /**
    * Check to see if the current opertaor is allowed to perform
    * adds on the given function.
    *
    * @param strFuncName
    *               - the function to test (this is the
                      Function_Description_Txt in the VIEW0570.VW)
    * @return true if authorized, false otherwise
    */
   bool isAuthorizedForAdd( const DString &strFuncName );

   /**
    * Check to see if the current opertaor is allowed to perform
    * browses on the given function.
    *
    * @param strFuncName
    *               - the function to test (this is the
                      Function_Description_Txt in the VIEW0570.VW)
    * @return true if authorized, false otherwise
    */
   bool isAuthorizedForBrowse( const DString &strFuncName );

   /**
    * Check to see if the current opertaor is allowed to perform
    * deletes on the given function.
    *
    * @param strFuncName
    *               - the function to test (this is the
                      Function_Description_Txt in the VIEW0570.VW)
    * @return true if authorized, false otherwise
    */
   bool isAuthorizedForDelete( const DString &strFuncName );

   /**
    * Check to see if the current opertaor is allowed to perform
    * updates on the given function.
    *
    * @param strFuncName
    *               - the function to test (this is the
                      Function_Description_Txt in the VIEW0570.VW)
    * @return true if authorized, false otherwise
    */
   bool isAuthorizedForUpdate( const DString &strFuncName );

   /**
    * Get the check digit status for the current operator.
    *
    * @return the Operator_Check_Digit_Status from VIEW0060
    */
   DString getCheckDigitStatus() const;

   /**
    * Get the dealer control code for the current operator.
    *
    * @return the Operator_Dealer_Control_Code from VIEW0060
    */
   DString getDealerControlCode() const;

   /**
    * Get the dealer control code for the current operator.
    *
    * @return the Operator_Source_Doc_Micro_Code from VIEW0060
    */
   DString getSourceDocMicroCode() const;

   /**
    * Get the dealer control code for the current operator.
    *
    * @return the Operator_Dealer_Security_Code from VIEW0060
    */
   DString getDealerSecurityCode() const;

   /**
    * Get the dealer control code for the current operator.
    *
    * @return the Operator_Dlr_Brnch_Securty_Cde from VIEW0060
    */
   DString getDealerBranchSecurityCode() const;

   /**
    * Get the dealer control code for the current operator.
    *
    * @return the Operator_Rep_Security_Code from VIEW0060
    */
   DString getRepSecurityCode() const;

   /**
    * Get the dealer control code for the current operator.
    *
    * @return the Operator_Tax_Id_Security_Code from VIEW0060
    */
   DString getTaxIdSecurityCode() const;

   void setSessionKey( const DString & str );
   const DString & getSessionKey() const;

private:
   static TA2000Security * _pInstance;
   TA2000SecurityImpl * _pImpl;
   SingletonRegister m_register;

#ifdef _WIN32
   friend void TA2000LogonAgent::_initialize();
#endif

private: //methods
   static void killInstance( void );
   static void deregister( void *pObj )
   {
      TA2000Security *pSecurity = ( TA2000Security * )pObj;
      pSecurity->killInstance();
   }

   TA2000Security();
   ~TA2000Security();
   TA2000Security( const TA2000Security& copy );
   TA2000Security& operator=( const TA2000Security& copy );
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
// $Log:   Y:/VCS/iFastAWD/inc/ta2000security.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:56   kovacsro
//Initial revision.
// 
//    Rev 1.19   Sep 12 2001 16:53:08   DT11159
// Added code to support sending views directly to a
// destination rather than always using host routing.
// 
//
//    Rev 1.18   05 Apr 2001 10:17:02   DT14177
// removed setOperatorId()
//
//    Rev 1.17   28 Mar 2001 14:33:04   DT14177
// added setOperatorId()
//
//    Rev 1.16   28 Nov 2000 11:02:56   dt14177
// cleanup
//
//    Rev 1.15   Mar 28 2000 14:34:20   dtwk
// - Use SingletonRegister to manage lifetime of TA2000DataBroker and TA2000Security
// - Make threadsafe
//
//    Rev 1.14   Mar 16 2000 17:13:00   dtwk
// Fix function level security in 1.9
//
//    Rev 1.13   Jan 16 2000 14:08:34   dtwk
// Update comments in JavaDoc format
//
//    Rev 1.12   Dec 19 1999 09:28:42   dtwk
// Convert comments to JavaDoc format
//
//    Rev 1.11   Dec 14 1999 12:25:06   dtwk
// Setup polymorphic interface
//
//    Rev 1.10   Dec 09 1999 09:10:54   dtwk
// Add V002 Support
//
//    Rev 1.9   Nov 19 1999 17:48:32   DMUM
// Development - Added TA2000LogonAgent
// DITA2KDB.DLL is now an MFC DLL.
//
//    Rev 1.8   Jul 07 1999 14:43:50   DCYK
// Add CBO's checkDigitStatus etc. functions.
//
//
//    Rev 1.7   Apr 21 1999 16:50:02   DCYK
// Updates for Unicode.
//
//
//    Rev 1.6   Mar 05 1999 10:22:02   DCYK
// Changes for I18N.
//
//
//    Rev 1.5   Jan 28 1999 14:07:04   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.4   Dec 09 1998 13:43:32   DMUM
// Check in for DICORE
//
//    Rev 1.3   Sep 29 1998 10:37:10   dcyk
// Synch-up with changes for PlanTrac.
//
//    Rev 1.1   Aug 27 1998 16:32:30   dcyk
// Sync-up with changes from PlanTrac.
// Changes only made to ViewFrame code.
//
//
//    Rev 1.0   29 Jul 1998 20:38:08   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.13   Dec 22 1997 09:19:54   dcyk
// Remove const from getValidFundSponsor.
//
//
//    Rev 1.12   Dec 05 1997 16:42:20   dcyk
// Added fund sponsor stuff for Legal Owner.
//
//
//    Rev 1.11   Nov 10 1997 15:02:46   dcyk
//
//
//    Rev 1.10   16 Sep 1997 08:43:54   dcyk
// Added enableAuthorizationForFacility
// and facilityAuthorizationIsOn.
//
//
//    Rev 1.9   10 Sep 1997 12:11:12   dcyk
// Made changes for PlanTrac.
// Async view calls & more processing.
//
//
//    Rev 1.8   13 Jun 1997 18:25:18   dcyk
// Added condition stuff.
//
//
//    Rev 1.7   May 09 1997 16:45:16   dcyk
// Improved standards compliance.
//
// Added documentation.
//
//
//    Rev 1.6   May 01 1997 08:48:30   dcyk
// Added newPassword parameter to logon
// function.
//
// Added documentation.
//
//
//    Rev 1.5   Mar 17 1997 11:01:36   dlkt
// Created an interface class to allow the public
// use and protect data in the implimentation
// class.
//

#endif
