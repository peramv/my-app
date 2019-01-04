//
//  CPPostalAddress.hpp
//
//  This header file was automatically generated!
//  **** DO NOT MODIFY THIS FILE!!! ****
//
//  Generation timestamp
//     Date:  
//     Time:  
//

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : CPPostalAddress.hpp
// ^AUTHOR : Cory Root
// ^DATE   :
//
// ^CLASS    : CPPostalAddress
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Represents a mailing address
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ^METHOD      : CPPostalAddress();
//
// ^DESCRIPTION : Public constructor for creating a CPPostalAddress object
//
// ^PARAMETERS  : N/A
//
// ^RETURNS     : Reference to an CPPostalAddress Object
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : CPPostalAddress( const CPPostalAddress& )
//
// ^DESCRIPTION : copy constructor for CPPostalAddress object
//
// ^PARAMETERS  : a const CPPostalAddress whose values are to be copied
//
// ^RETURNS     : Reference to a CPPostalAddress object
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : init()
//
// ^DESCRIPTION : initializes a CPPostalAddress object to its
//                default values
//
// ^PARAMETERS  : N/A
//
// ^RETURNS     : SEVERITY
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : init( const Data&, bool )
//
// ^DESCRIPTION : initializes the CPPostalAddress object to
//                the values held in Data
//
// ^PARAMETERS  : const Data& -- contains values to which
//                      CPPostalAddress should be initialized.
//                bool -- if set to true, CPPostalAddress is
//                     initialized using only CPPostalAddress fields
//                     Default is true.
//
// ^RETURNS     : SEVERITY
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : getAddrLine( int )
//
// ^DESCRIPTION : retrieves the value of the address line requested
//
// ^PARAMETERS  : int -- specifies which address line to retrieve
//
// ^RETURNS     : const DString
//
// ^THROWS      : ERR_INVALID_ADDRESS_LINE -- int passed to function is
//                     less than zero or greater than max allowable lines
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : getCityStateZipLine()
//
// ^DESCRIPTION : returns a DString containing the city, state
//                abbreviation, and 9 digit zip code of a formatted
//                CPPostalAddress.  If address is not formatted, returns
//                a blank DString
//
// ^PARAMETERS  : N/A
//
// ^RETURNS     : const DString
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : getNumCurrentLines()
//
// ^DESCRIPTION : returns number of registration lines currently
//                used by the CPPostalAddress object.  For formatted
//                addresses, it adds one for City/State/Zip line
//
// ^PARAMETERS  : N/A
//
// ^RETURNS     : int
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : getNumStreetAddressLines()
//
// ^DESCRIPTION : returns the current number of address lines in
//                use by the CPPostalAddress object, and also
//                removes any blank lines within the address.
//
// ^PARAMETERS  : N/A
//
// ^RETURNS     : int
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : performIsValidForUpdateEdits()
//
// ^DESCRIPTION : validates all CPPostalAddress fields
//
// ^PARAMETERS  : N/A
//
// ^RETURNS     : SEVERITY
//                   - ERR_INVALID_ADDRESS_LINE
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : setAddrLine( short, const DString& )
//
// ^DESCRIPTION : sets the specified address line with the value
//                passed
//
// ^PARAMETERS  : short -- identifies the address line to change
//                const DString& -- the value to place in the address line
//
// ^RETURNS     : SEVERITY
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : setZipCode( const DString& )
//
// ^DESCRIPTION : Formatted addresses only - sets the zip code
//                to the 5, 9, or 11 digit zip code passed in.
//
// ^PARAMETERS  : const DString& -- zip code.  Can be 5, 9, or 11
//                digits long, and may be hyphenated.
//
// ^RETURNS     : SEVERITY
//                   - ERR_ZIP_CODE_NOT_NUMERIC
//                   - ERR_POSTAL_ADDRESS_NOT_FORMATTED
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------

#ifndef CPPOSTALADDRESS_HPP
#define CPPOSTALADDRESS_HPP

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

#ifndef CONTACTPOINT_HPP
#include "contactpoint.hpp"
#endif

//use namespace std for the Standard C++ library
using namespace std;

//forward declares
// Forward declaration of implementation class
class CPPostalAddressImpl;

//defines for identifying subclasses using substitution at compile time
#undef  $ParentClass$
#define $ParentClass$    ContactPoint

#undef  $ThisClass$
#define $ThisClass$      CPPostalAddress

#undef  $ThisClassImpl$
#define $ThisClassImpl$  CPPostalAddressImpl

#undef  $ParentClassStr$
#define $ParentClassStr$    I_("ContactPoint")

#undef  $ThisClassStr$
#define $ThisClassStr$      I_("CPPostalAddress")

#undef  $ThisClassImplStr$
#define $ThisClassImplStr$  I_("CPPostalAddressImpl")

// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE CPPostalAddress : public ContactPoint
{
   public:
      enum FIELD
      {
         CITY_NAME,
         FORMAT_TYPE_CODE,
         FORMATTED_CERTIFICATION_STATUS_CODE,
         LINE_TEXT_1,
         LINE_TEXT_2,
         LINE_TEXT_3,
         LINE_TEXT_4,
         LINE_TEXT_5,
         LINE_TEXT_6,
         MILITARY_LOCATION_CODE,
         ZIP_CODE_SUFFIX,
         ZIP_DELIVERY_OFFICE_CODE,
         ZIP_DELIVERY_SEQUENCE_NUMBER,
         STATE_COUNTRY_CODE,
         MAX_FIELDS
      };

      enum OBJECT
      {
         UNUSED_OBJECT,
         MAX_OBJECTS
      };

      CPPostalAddress();
      CPPostalAddress( const CPPostalAddress& copy );
      virtual ~CPPostalAddress();
      CPPostalAddress& operator=( const CPPostalAddress& copy );
      SEVERITY init();
      SEVERITY init( const Data& dataPostalAddress, bool bUsingCPPostalFields=true );
      virtual bool operator==( const ContactPoint& compare );
      const DString getAddrLine( int nAddressLine );
      const DString getCityStateZipLine();
      int getNumCurrentLines();
      int getNumMaxLines( void ) const;
      int getNumStreetAddressLines();
      SEVERITY performIsValidForUpdateEdits();
      SEVERITY setAddrLine( short sLineNumber, const DString& strStreetAddressLineText );
      SEVERITY setZipCode( const DString& strZipCode );





   // include common declarations
   #include "Common_Inter_hpp.hpp"

};

#endif
