//
//  PostalAddress.hpp
//
//  This header file was automatically generated!
//  **** DO NOT MODIFY THIS FILE!!! ****
//
//  Generation timestamp
//     Date:  
//     Time:  
//

#ifndef POSTALADDRESS_HPP
#define POSTALADDRESS_HPP


#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef CBOBASE_HPP
#include "cbobase.hpp"
#endif

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"
#endif

//use namespace std for the Standard C++ library
using namespace std;

//forward declares
// Forward declaration of implementation class
class PostalAddressImpl;

//defines for identifying subclasses using substitution at compile time
#undef  $ParentClass$
#define $ParentClass$    CBOBase

#undef  $ThisClass$
#define $ThisClass$      PostalAddress

#undef  $ThisClassImpl$
#define $ThisClassImpl$  PostalAddressImpl

#undef  $ParentClassStr$
#define $ParentClassStr$    I_("CBOBase")

#undef  $ThisClassStr$
#define $ThisClassStr$      I_("PostalAddress")

#undef  $ThisClassImplStr$
#define $ThisClassImplStr$  I_("PostalAddressImpl")

// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE PostalAddress : public CBOBase
{
   public:
      enum FIELD
      {
         RESIDENT_COUNTRY,
         ZIP_CODE,
         MAX_FIELDS
      };

      enum OBJECT
      {
         UNUSED_OBJECT,
         MAX_OBJECTS
      };

      PostalAddress();
      PostalAddress( const PostalAddress& copy );
      virtual ~PostalAddress();
      PostalAddress& operator=( const PostalAddress& copy );
      SEVERITY init( int maxLineCount=6 );
      const DString& getAddrLine( int nIndex ) const;
      int getNumCurrentLines( void ) const;
      int getNumMaxLines( void ) const;
      bool setAddrLine( int index, const DString& strAddressLine );
      bool validateAddress( void );
      bool getZipCode( DString& strZipCode ) const;
      bool setZipCode( const DString& strZipCode );
      bool shouldUpdateBeBuilt( const DString& strLabel ) const;
      bool isUREGUpdate( void ) const;
      bool isUMASTUpdate( void ) const;
      SEVERITY getData( const DString& strLabel, Data & data, bool fAppendNewTags=false, bool fUseDataObjectOnly=false ) const;
      bool clearUpdateFlags( void );





   // include common declarations
   #include "Common_Inter_hpp.hpp"

};

#endif
