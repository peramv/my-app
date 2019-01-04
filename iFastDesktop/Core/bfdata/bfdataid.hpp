#pragma once

#include <commonport.h>
#include <bfdata\bfdataexception.hpp>
#include <dstring.hpp>
#include <map>

// Import/Export resolution
#undef BFDATA_LINKAGE
#ifdef BFDATA_DLL
   #define BFDATA_LINKAGE CLASS_EXPORT
#else
   #define BFDATA_LINKAGE CLASS_IMPORT
#endif

BF_DECL_BASE_EXCEPTION( BFDataIdException );
BF_DECL_EXCEPTION( BFDataIdOpException, BFDataIdException );
BF_DECL_EXCEPTION( BFDataIdUnknownException, BFDataIdException );


class BFDATA_LINKAGE BFDataId
{
public:
   BFDataId( long idData, const I_CHAR* name );
   BFDataId( long idData ) { id_ = idData;}
   BFDataId( const BFDataId& rhs ) { *this = rhs;}
   operator long() const { return(id_);}
   BFDataId& operator=( const BFDataId& rhs ) 
   {
      id_ = rhs.id_;
      return( *this );
   }
   bool operator==( const BFDataId& rhs )
   {
      return( id_ == rhs.id_ );
   }

   const DString& getName() const;
   inline long getId() const { return(id_);}
   bool isValid() const { return(id_ != 0);}

   static const DString& getName( long id );
   static const BFDataId& getId( const DString& name );

protected:
   static std::map< DString, const BFDataId* >& getDataNameIdXRefMap();
   static std::map< long, DString >& getDataIdNameXRefMap();

private:
   long   id_;
};

namespace ifds
{
   extern BFDATA_LINKAGE const BFDataId NullDataId;
}


