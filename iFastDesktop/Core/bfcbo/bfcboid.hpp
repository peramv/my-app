#pragma once
#include <srcprag.h>
#include <commonport.h>
#include <windows.h>

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class BFBASE_LINKAGE BF_OBJ_TYPE
{
public:
   BF_OBJ_TYPE();
   BF_OBJ_TYPE( const I_CHAR* pszName );
   BF_OBJ_TYPE( const BF_OBJ_TYPE& rhs )
   {
      id_ = rhs.id_;
   }

   BF_OBJ_TYPE& operator=( const BF_OBJ_TYPE& rhs )
   {
      id_ = rhs.id_;
      return( *this );
   }

   bool operator==( const BF_OBJ_TYPE& rhs ) const
   {
      return( id_ == rhs.id_ );
   }

   operator int() const { return id_; }

private:
   static int s_lastId_;
   int id_;
};

extern BFBASE_LINKAGE BF_OBJ_TYPE OBJ_TYPE_NONE;

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfcbo/bfcboid.hpp-arc  $
//
//   Rev 1.1   Nov 13 2002 11:45:40   PURDYECH
//Change underlying identification mechanics to use a string to identify unique instances of BF_OBJ_TYPE.  The string is converted into an int for quick comparisons.
//
//   Rev 1.0   Nov 08 2002 10:01:56   PURDYECH
//Initial revision.
//
