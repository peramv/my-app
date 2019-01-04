#pragma once

#include <srcprag.h>
#include <commonport.h>
#include <bfutil\bfcritsec.hpp>
#include <assert.h>

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif


class BFBASE_LINKAGE BFDataGroupException
{
};
class BFBASE_LINKAGE BFDataGroupNotFoundException : public BFDataGroupException
{
};


class BFDataGroupId;
class BFNoParentDataGroupId;

class AbstractProcess;

namespace BF
{
   extern BFBASE_LINKAGE const BFDataGroupId HOST;
   extern BFBASE_LINKAGE const BFDataGroupId NullDataGroupId;
}

class BFBASE_LINKAGE BFDataGroupId
{
public:
   friend AbstractProcess;

   BFDataGroupId( long l, const BFDataGroupId& rParent );
//CP20030429   , pParent_( &rParent )
   BFDataGroupId( const BFDataGroupId& rhs )
   { *this = rhs; }

   ~BFDataGroupId() {}

   BFDataGroupId& operator=( const BFDataGroupId& rhs )
   { 
      id_ = rhs.id_;
//CP20030429      pParent_ = rhs.pParent_;
      return( *this );
   }

   bool operator==( const BFDataGroupId& rhs ) const
   { return( id_ == rhs.id_ ); }
   bool operator!=( const BFDataGroupId& rhs ) const
   { return( false == (*this == rhs ) ); }
   bool operator<( const BFDataGroupId& rhs ) const
   { return( id_ < rhs.id_ ); }

   long getId() const
   { 
      assert( id_ >= -1 ); 
      return(id_); 
   }

   bool isAncestorOf( const BFDataGroupId& idDataGroup ) const;

   const BFDataGroupId& getParent() const;

private:
   long id_;
//CP20030429   const BFDataGroupId* pParent_;

   void setParent( const BFDataGroupId* pParent ) const;

public:
   static long getNextDataGroupId();
private:
   static long idNext_;


public:
   BFDataGroupId();
public:
   static const BFDataGroupId& getNoParentInstance();
};
