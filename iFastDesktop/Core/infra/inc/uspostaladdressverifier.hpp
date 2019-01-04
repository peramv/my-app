#ifndef USPOSTALADDRESSVERIFIER_HPP
#define USPOSTALADDRESSVERIFIER_HPP

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

/**@pkg DITABUSCORE */    

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
#include <map>
#endif

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"
#endif

/**@#-*/
//forward declaration of Method arguments
class Name;
class CPPostalAddress;
class Data;

typedef std::pair< DString, DString > string_pair;
typedef std::map< DString, 
                  DString, std::less<DString> > STRING_TO_STRING_MAP;
typedef STRING_TO_STRING_MAP::value_type 
                                       STRING_TO_STRING_MAP_TYPE;
/**@#+*/

// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE USPostalAddressVerifier
{
   public:
      
        // %BEGIN_INTERFACE%
      
      /**
       * Default constructor
       */
      USPostalAddressVerifier();
      
      /**
       * Copy constructor
       */
      USPostalAddressVerifier( 
                          const USPostalAddressVerifier & copy );

      /**
       * Destructor
       */
      virtual ~USPostalAddressVerifier();

      /**
       * Assignment operator
       */
      const USPostalAddressVerifier & operator=( 
                          const USPostalAddressVerifier & copy );

      /**
       * Calls the Finalist view to verify the address.
       * 
       * The address is built in 3 steps:
       * 
       * Step 1. build suggested name
       * Step 2. build suggest postal address
       * Step 3. build zip code
       * 
       * @param name
       * @param postalAddress
       * @param suggestedName
       * @param suggestedPostalAddress
       * @return 
       */
      SEVERITY verifyPostalAddress( const Name & name,
										const CPPostalAddress & postalAddress,
										Name & suggestedName,
										CPPostalAddress & suggestedPostalAddress );


      /**
       * Calls the Finalist view to verify the address.
       * 
       * The address is built in 3 steps:
       * 
       * Step 1. build suggested name
       * Step 2. build suggest postal address
       * Step 3. build zip code
       * 
       * @param name
       * @param postalAddress
       * @param suggestedName
       * @param suggestedPostalAddress
       * @param strS017peErrorText
       * @param strFinalistErrorText
       * @return 
       */
      SEVERITY verifyPostalAddress( const Name& name,
                              const CPPostalAddress& postalAddress,
                              Name& suggestedName,
                              CPPostalAddress& suggestedPostalAddress,
										DString& strS017peErrorText,
										DString& strFinalistErrorText );


      /**
       * Verifies address info using Finalist
       * 
       * @param STRING_TO_STRING_MAP
       *               - (in) controls the format
       * @param enteredData
       *               - (in) the data to verify
       * @param suggestedData
       *               - (out) the suggested data from Finalist
       * @return 
       */
      SEVERITY verifyPostalAddress( const STRING_TO_STRING_MAP &,
                                    const Data & enteredData,
                                    Data & suggestedData );


      /**
       * Calls Finalist to verify the address
       * info for zip code correctness
       * 
       * @param STRING_TO_STRING_MAP
       *                - (in) the address format
       * @param enteredData
       *                - (in) data to verify
       * @param outData
      *               - (out) the suggested data from Finalist
       * @return 
       */
      SEVERITY verifyStateAndZip( const STRING_TO_STRING_MAP &,
                                  const Data & enteredData,
                                  Data & outData );
        // %END_INTERFACE%

   private:

       
       SEVERITY breakLastAddressLine( DString & strLastAddressLine, 
                                      DString & City, 
                                      DString & StateOrCountry, 
                                      DString & Zip, 
                                      DString & StateCountryCode,
                                      bool & bStateOrCountryFound, 
                                      bool & bDomestic );

	    bool _isForeignCountry( DString& strLastAddressLine );
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
// $Log:   Y:/VCS/iFastAWD/inc/uspostaladdressverifier.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:16   kovacsro
//Initial revision.
// 
//    Rev 1.5   Jul 19 2002 15:18:48   dt39990
// TT#15958: Added _isForeignCountry() private 
// method to check if the last address line contains
// foreign country. 
// 
//    Rev 1.4   29 Nov 2000 14:45:56   dt14177
// fixed std namespace compile problem
// 
//    Rev 1.3   29 Nov 2000 11:29:04   dt14177
// cleanup
// 
//    Rev 1.2   Jul 24 2000 15:48:16   DT22388
// Performed infra 1.7 to 1.9  synch-up
// 
//    Rev 1.1   Nov 11 1999 16:32:54   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0.1.0   Jul 22 1999 13:36:18   DT22388
// Performed code clean-up and added #undefs
// for the substitution string i.e. $strParentImplClass$.
// Also, added #includes for test classes.
// 
// 
//    Rev 1.0   Jun 21 1999 17:16:18   DT22388
//  
// 
//    Rev 1.0   29 Jul 1998 23:58:56   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.6   Jan 19 1998 08:33:22   djoo
// Added forward declare of Name.
// 
//    Rev 1.5   Jan 17 1998 08:28:04   ddls
// Added verifyStateAndZip method.
// 
//    Rev 1.4   Jan 16 1998 12:19:40   dmxw
// Changed the verifyPostalAddress method taking a CPPostalAddress
// to return SEVERITY.  It will generate conditions with the Finalist messages.
//
//
#endif // USPOSTALADDRESSVERIFIER_HPP
