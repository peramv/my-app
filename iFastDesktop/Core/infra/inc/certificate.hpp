#ifndef CERTIFICATE_HPP
#define CERTIFICATE_HPP

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

class CertificateImpl;

#undef DICERT_LINKAGE
#ifdef DICERT_DLL
   #define DICERT_LINKAGE CLASS_EXPORT
#else
   #define DICERT_LINKAGE CLASS_IMPORT
#endif

/**
 * This class is made to help implement "certificate
 * authentication" for objects that need it. Each Certificate will
 * contain a unique identifier created for comparison purposes.
 * It is designed to be used in conjunction with the DIAuthentication
 * template class.  You can use the Certificate directly, or use the
 * Authenticator class, which provides a standard interface for
 * authentication.
 * 
 * This class provides the "Cheshire Cat" interface for the
 * CertificateImpl class.
 * 
 * @author DST Systems Inc
 */
class DICERT_LINKAGE Certificate
{
public:
   /**
    * Default constructor
    * 
    * @exception ConditionException (BASE_ALLOC_FAIL if new fails)
    *
    */
   Certificate();

   ~Certificate();

   /**
    * Copy constructor
    * 
    * @param orig
    * @exception ConditionException (BASE_ALLOC_FAIL if new fails)
    *
    */
   Certificate( const Certificate &orig );

   /**
    * basic assignment operator
    * 
    * @exception ConditionException (BASE_ALLOC_FAIL if new fails)
    *
    */
   Certificate & operator=( const Certificate &orig );

   /**
    * Erase the certificate.
    * 
    */
   void erase();

   /**
    * Checks to see if the certificate exists or not.
    * 
    * @return true if the certificate exists, false otherwise
    *
    */
   bool isEmpty() const;

   /**
    * Generates a new, random identifier
    * 
    * @exception ConditionException (BASE_ALLOC_FAIL if new fails)
    *
    */
   void generate();

   /**
    * Compares two certificates
    * 
    * @return true if the certificates are identical, false otherwise
    *
    */
   bool operator==( const Certificate &op2 ) const;

private:

   CertificateImpl         *_pImpl;

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
// $Log:   Y:/VCS/iFastAWD/inc/certificate.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:18   kovacsro
//Initial revision.
// 
//    Rev 1.5   Jan 16 2000 14:07:56   dtwk
// Update comments in JavaDoc format
// 
//    Rev 1.4   Dec 19 1999 09:28:12   dtwk
// Convert comments to JavaDoc format
// 
//    Rev 1.3   Mar 05 1999 10:30:34   DCYK
// Changes for I18N.
// 
// 
//    Rev 1.2   Jan 28 1999 14:05:28   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.1   Dec 09 1998 13:39:56   DMUM
// Check in for DICORE
// 
//    Rev 1.3   Nov 09 1997 15:34:28   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
// 
//    Rev 1.2   Jul 07 1997 15:11:54   DTWK
//  
// 
//    Rev 1.1   Jun 13 1997 14:08:50   DTWK
// Add Condition support
// 
//    Rev 1.0   Jun 05 1997 15:55:16   DTWK
//  
//
//


#endif
