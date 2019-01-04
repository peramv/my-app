//
//  Name.hpp
//
//  This header file was automatically generated!
//  **** DO NOT MODIFY THIS FILE!!! ****
//
//  Generation timestamp
//     Date:  
//     Time:  
//

#ifndef NAME_HPP
#define NAME_HPP


#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef CBOBASE_HPP
#include "cbobase.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"
#endif

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

//use namespace std for the Standard C++ library
using namespace std;

//forward declares
// Forward declaration of implementation class
class NameImpl;

//defines for identifying subclasses using substitution at compile time
#undef  $ParentClass$
#define $ParentClass$    CBOBase

#undef  $ThisClass$
#define $ThisClass$      Name

#undef  $ThisClassImpl$
#define $ThisClassImpl$  NameImpl

#undef  $ParentClassStr$
#define $ParentClassStr$    I_("CBOBase")

#undef  $ThisClassStr$
#define $ThisClassStr$      I_("Name")

#undef  $ThisClassImplStr$
#define $ThisClassImplStr$  I_("NameImpl")

// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE Name : public CBOBase
{
   public:
      enum FIELD
      {
         UNUSED,
         MAX_FIELDS
      };

      enum OBJECT
      {
         UNUSED_OBJECT,
         MAX_OBJECTS
      };

      Name();
      Name( const Name& copy );
      ~Name();
      Name& operator=( const Name& copy );
      SEVERITY init( int maxLineCount=5, int maxLineLength=35 );
      bool getLine( int nIndex, DString& strTextLine ) const;
      virtual int getNumCurrentLines( void ) const;
      int getNumMaxLines( void ) const;
      int getMaxLineLength() const;
      bool setLine( int nLineNum, const DString& strTextLine );
      virtual bool operator==( const Name &rhs ) const;
      virtual bool setNumMaxLines( int num );

   // include common declarations
   #include "Common_Inter_hpp.hpp"

};

#endif
