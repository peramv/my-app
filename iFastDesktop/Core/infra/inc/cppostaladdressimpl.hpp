// %NO_GEN%
// %CBOBASE_DERIVED%
// %BEGIN_INTERFACE%

/** 
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

/**@pkg DICORE */    

//
// ^CLASS DESCRIPTION : Represents a mailing address
// 
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ^METHOD      : CPPostalAddressImpl();
//
// ^DESCRIPTION : Public constructor for creating a CPPostalAddressImpl object
//
// ^PARAMETERS  : N/A
//
// ^RETURNS     : Reference to an CPPostalAddressImpl Object
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : CPPostalAddressImpl( const CPPostalAddressImpl& )
//
// ^DESCRIPTION : copy constructor for CPPostalAddressImpl object
//
// ^PARAMETERS  : a const CPPostalAddressImpl whose values are to be copied
//
// ^RETURNS     : Reference to a CPPostalAddressImpl object
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
//
// ^METHOD      : init()
//
// ^DESCRIPTION : initializes a CPPostalAddressImpl object to its
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
// ^DESCRIPTION : initializes the CPPostalAddressImpl object to
//                the values held in Data
//
// ^PARAMETERS  : const Data& -- contains values to which 
//                      CPPostalAddressImpl should be initialized.
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
// %END_INTERFACE%
// ----------------------------------------------------------
//                PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ^METHOD      : setMaxStreetAddressLines( unsigned short )
//
// ^DESCRIPTION : sets the maximum number of registration lines
//                for the postal address.  Cannot be greater than
//                five.  
//
// ^PARAMETERS  : unsigned short
//
// ^RETURNS     : SEVERITY
//                   - ERR_INVALID_ADDRESS_LINE
//
// ^THROWS      : N/A
//
// ^EXAMPLE     :
// ----------------------------------------------------------
#ifndef CPPOSTALADDRESSIMPL_HPP
#define CPPOSTALADDRESSIMPL_HPP

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

#ifndef CBOINSTANCEFIELDINFO_HPP
#include "cboinstancefieldinfo.hpp"
#endif

#ifndef CONTACTPOINTIMPL_HPP
#include "contactpointimpl.hpp"
#endif

//use namespace std for the Standard C++ library
using namespace std;

//forward declares
class Data;

//defines for identifying subclasses using substitution at compile
// time
#undef  $ParentImplClass$
#define $ParentImplClass$  ContactPointImpl

#undef  $ImplClass$
#define $ImplClass$        CPPostalAddressImpl

// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif


class DITABUSCORE_LINKAGE CPPostalAddressImpl : 
                             public ContactPointImpl
{
   public:
        // %BEGIN_INTERFACE%

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

        /**
         * Default Constructor
         */
        CPPostalAddressImpl();

        /**
         * Copy Constructor
         * 
         * @param copy
         */
        CPPostalAddressImpl( const CPPostalAddressImpl& copy );

        /**
         * Destructor
         */
        virtual ~CPPostalAddressImpl();

        /**
         * assignment operator
         * 
         * @param copy
         * @return 
         */
        CPPostalAddressImpl& operator=( const 
                                     CPPostalAddressImpl& copy );

        /**
         * initializer method
         * 
         * @return highest severity
         */
        SEVERITY init();

        /**
         * initializer method
         * 
         * @param dataPostalAddress
         *               Data object used to initialize the
         *               cppostaladdressimpl object
         * @param bUsingCPPostalFields
         * @return 
         */
        SEVERITY init( const Data & dataPostalAddress, 
                       bool bUsingCPPostalFields = true );
        
        /**
         * equality operator
         * 
         * @param compare
         * @return true, if equal
         */
        virtual bool operator==( const ContactPointImpl& compare );

        /**
         * get the line indexed by the parameter
         * 
         * @param nAddressLine
         * @return 
         */
        const DString getAddrLine( int nAddressLine );

        /**
         * returns a DString containing the city, state
         * abbreviation, and 9 digit zip code of a formatted
         * CPPostalAddress.  If address is not formatted,
         * returns a blank DString
         * 
         * @return 
         */
        const DString getCityStateZipLine();

        /**
         * returns number of registration lines currently
         * used by the CPPostalAddress object.  For formatted
         * addresses, it adds one for City/State/Zip line
         * 
         * @return 
         */
        int getNumCurrentLines();

        /**
         * returns the maximum number of address lines 
         * use by the CPPostalAddress object.
         * 
         * @return 
         */
        int getNumMaxLines( void ) const;

        /**
         * returns the current number of address lines in
         * use by the CPPostalAddress object, and also
         * removes any blank lines within the address.
         * 
         * @return 
         */
        int getNumStreetAddressLines();

        /**
         * validates all CPPostalAddress fields
         * 
         * @return SEVERITY - ERR_INVALID_ADDRESS_LINE
         */
        SEVERITY performIsValidForUpdateEdits();

        /**
         * sets the specified address line with the value
         * passed
         * 
         * @param nLineNumber
         *               index of the line to be assigned the new 
         *               value
         * @param strStreetAddressLineText
         * @return 
         */
        SEVERITY setAddrLine( int nLineNumber, 
                       const DString& strStreetAddressLineText );

        /**
         * Formatted addresses only - sets the zip code
         * to the 5, 9, or 11 digit zip code passed in.
         * 
         * @param strZipCode
         * @return 
         */
        SEVERITY setZipCode( const DString & strZipCode );
        // %END_INTERFACE%
        
private:
        bool _isMilitaryLocationValid( const DString& strStateCountryCode, const DString& strMilitaryLocation );
        SEVERITY _setStateCountryCode( const DString& strValue );
        SEVERITY _validateCertificationStatusCode( const DString& strValue );
        SEVERITY _validateCityName( const DString& strValue );
        SEVERITY _validateMilitaryLocationCode( const DString& strValue );
        SEVERITY _validateStateCountryCode( const DString& strValue );
        SEVERITY _validateZipCodeSuffix( const DString& strValue );
        SEVERITY _validateZipDeliveryOfficeCode( const DString& strValue );
        SEVERITY _validateZipDeliverySequenceNumber( const DString& strValue );
        SEVERITY setField( unsigned short usSubclassId, int nFieldId, const DString& strValue );

protected: // methods
        SEVERITY setMaxStreetAddressLines( int nMaxAddrLines );

protected: //data
        int _nMaxLineCount;


// include common declarations
#include "Common_Impl_hpp.hpp"

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
// $Log:   Y:/VCS/iFastAWD/inc/cppostaladdressimpl.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:46   kovacsro
//Initial revision.
// 
//    Rev 1.4   Nov 28 2001 12:20:44   dt39990
// Added getNumMaxLines() method
// 
//    Rev 1.3   23 Oct 2000 16:35:44   dt14177
// cleanup
// 
//    Rev 1.2   Jul 24 2000 15:48:12   DT22388
// Performed infra 1.7 to 1.9  synch-up
// 


