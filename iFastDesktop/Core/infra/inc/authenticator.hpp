#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999 by DST Systems, Inc.
 */

/**@pkg DIDBRKR */ 

#pragma message( "including "__FILE__ )

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

class Certificate;
class AuthenticatorImpl;

#undef DICERT_LINKAGE
#ifdef DICERT_DLL
   #define DICERT_LINKAGE CLASS_EXPORT
#else
   #define DICERT_LINKAGE CLASS_IMPORT
#endif

/**
 * This class is made to help implement "certificate
 * authentication" for objects that need it.  It is designed to be
 * a base class.  If a class inherits from it, that class will be
 * almost fully ready to use certificate processing.  All that the
 * class needs to do is invoke methods in Authenticator to update the
 * certificate as necessary (i.e. eraseCertificate() when the class'
 * data is invalidated).  This class should provide "reasonable"
 * security. It is by no means bulletproof.
 * 
 * This class exports a standard interface wrapped around the Certificate
 * class, and is tightly coupled with the DIAuthentication template
 * class.  You could just use the Certificate directly, but then you'd
 * just end up reimplementing the functionality in Authenticator.
 * 
 * For example TA2000 DataBroker certifies Data objects.  The TA2000
 * DataBroker contains an instance of the DIAuthentiction template class
 * that is instantiated using Data objects as its template.
 * The Data object inherits from Authenticator.  Together, they allow
 * The TA2000 DataBroker to "certify" instances of Data objects as
 * being set by TA2000 DataBroker and no one else.
 * 
 * I know, inheriting for interface is not recommended, but it seems to
 * be a neat solution in this case.
 * 
 * This class provides the "Cheshire Cat" interface for the
 * AuthenticatorImpl class.
 * 
 * @author DST Systems Inc
 */
class DICERT_LINKAGE Authenticator
{
public:
// Constructors & Destructors

   /**
    * Default constructor
    * 
    * @exception ConditionException (BASE_ALLOC_FAIL if new fails)
    *
    */
   Authenticator();

   virtual ~Authenticator();

   /**
    * Copy constructor
    * 
    * @param orig
    * @exception ConditionException (BASE_ALLOC_FAIL if new fails)
    *
    */
   Authenticator( const Authenticator &orig );

   /**
    * Copy operator
    * 
    * @param orig
    * @return Authenticator &
    * @exception ConditionException (BASE_ALLOC_FAIL if new fails)
    *
    */
   Authenticator & operator=( const Authenticator &orig );

// Methods
   /**
    * Compares the Authenticator's certificate with
    * the one passed in.
    * 
    * @param cert
    * @return true if the certificates match, false otherwise
    *
    */
   virtual bool checkCertificate( const Certificate &cert ) const;

   /**
    * Compares the Authenticator's certificate with
    * the one passed in.
    * 
    * @param auth
    * @return true if the certificates match, false otherwise
    *
    */
   virtual bool checkCertificate( const Authenticator &auth ) const;

   /**
    * Erases the Authenticator's certificate.
    * 
    */
   virtual void resetCertificate();

   /**
    * Sets the Authenticator's certificate with
    * the one passed in.
    * 
    * @param cert
    * @exception ConditionException (BASE_ALLOC_FAIL if new fails)
    *
    */
   virtual void setCertificate( const Certificate &cert );

   /**
    * Sets the Authenticator's certificate with
    * the one passed in.
    * 
    * @param auth
    * @exception ConditionException (BASE_ALLOC_FAIL if new fails)
    *
    */
   virtual void setCertificate( const Authenticator &auth );

   /**
    * Compare the Authenticator's certificate with
    * the one passed in, and erases the Authenticator's certificate
    * if they are different.
    * 
    * @param auth - either the Certificate or null
    *
    */
   virtual void updateCertificate( const Certificate *pCert );

   /**
    * Compare the Authenticator's certificate with
    * the one passed in, and erases the Authenticator's certificate
    * if they are different.
    * 
    * @param auth
    *
    */
   virtual void updateCertificate( const Authenticator &auth );

private:
// Data
   AuthenticatorImpl           *_pImpl;

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
// $Log:   Y:/VCS/iFastAWD/inc/authenticator.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:42   kovacsro
//Initial revision.
// 
//    Rev 1.5   Jan 16 2000 14:07:46   dtwk
// Update comments in JavaDoc format
// 
//    Rev 1.4   Dec 19 1999 09:28:04   dtwk
// Convert comments to JavaDoc format
// 
//    Rev 1.3   Mar 05 1999 10:20:46   DCYK
// Changes for I18N.
// 
// 
//    Rev 1.2   Jan 28 1999 14:05:12   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.1   Dec 09 1998 13:37:48   DMUM
// Check in for DICORE
// 
//    Rev 1.3   Nov 09 1997 15:33:06   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
// 
//    Rev 1.2   Jul 07 1997 15:11:54   DTWK
// Add more commenting.
// 
//    Rev 1.1   Jun 13 1997 14:08:46   DTWK
// Add Condition support
// 
//    Rev 1.0   Jun 05 1997 15:55:14   DTWK
//  
//
//



#endif

