#pragma once

#include <commonport.h>

#include <dstring.hpp>
#include <map>
#include <vector>

#include <bfdata\bfdataexception.hpp>

BF_DECL_BASE_EXCEPTION( BFSubstitutionException );

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

class BFDATA_LINKAGE BFSubstitutionSet
{
public:
   BFSubstitutionSet( const I_CHAR** aKeys, const I_CHAR** aValues );
   BFSubstitutionSet( const BFSubstitutionSet& src, const std::vector< DString >& vecKeys );
   BFSubstitutionSet( const BFSubstitutionSet& rhs );

   ~BFSubstitutionSet();

   BFSubstitutionSet& operator=( const BFSubstitutionSet& rhs );

private:
   class caseInsensitiveCompare
   {
   public:
      bool operator() ( const DString& lhs, const DString& rhs ) const
      { return(i_stricmp( lhs.c_str(), rhs.c_str() ) < 0);}
   };

public:
   typedef std::vector< DString > KeyVector;
   typedef std::map< DString, DString, caseInsensitiveCompare > KeyMap;
   typedef std::map< DString, DString > ValueMap;

public:
   std::vector< DString >::size_type size() const
   {
      return(pvKeys_->size());
   }

   std::vector< DString >& getKeys( std::vector< DString >& setKeys ) const;
   std::vector< DString >& getValues( std::vector< DString >& setValues ) const;

   const DString& getKey( const DString& strValue ) const;
   const DString& getValue( const DString& strKey ) const;

   const I_CHAR* getKey( const I_CHAR* pszValue ) const;
   const I_CHAR* getValue( const I_CHAR* pszKey ) const;

   bool isKey( const DString& strKey ) const;
   bool isValue( const DString& strValue ) const;

   DString& getAsIDI( DString& idiString, bool bUsePropertiesOrder ) const;

private:
   DString& initIDI( DString& idiString, bool bUsePropertiesOrder );

   KeyMap*     pmKeys_;
   ValueMap*   pmValues_;
   KeyVector*  pvKeys_;
   DString     idiString_;          // tag=value pairs in lexical order by tag
   DString     idiStringOrdered_;   // tag=value pairs in properties order
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfdata/bfsubstitutionset.hpp-arc  $
//
//   Rev 1.6   Oct 09 2002 17:40:34   PURDYECH
//New PVCS Database
//
//   Rev 1.5   Sep 18 2002 14:22:56   PURDYECH
//Make substitution keys case insensitive
//
//   Rev 1.4   Aug 29 2002 12:51:14   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.3   Jun 11 2002 12:04:16   PURDYECH
//Added a const I_CHAR* version of getKey and getValue
//
//   Rev 1.2   22 May 2002 18:08:50   PURDYECH
//BFData Implementation
//
