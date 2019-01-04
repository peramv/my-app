#pragma once

//CP20030106#define _NEW_BFContainerId_MODEL_

#include <srcprag.h>
#include <commonport.h>
#include <bfutil\bfcritsec.hpp>

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

//CP20030106#ifdef _NEW_BFContainerId_MODEL_

class BPBASE_LINKAGE BFContainerId
{
public:
   BFContainerId()
   : id_( 0 )
   {}
   explicit BFContainerId( long idContainer ) 
   : id_( idContainer )
   {}
   BFContainerId( const BFContainerId& rhs )
   {
      if( this != &rhs )
      {
         *this = rhs;
      }
   }
   virtual ~BFContainerId()
   {}

   BFContainerId& operator=( const BFContainerId& rhs )
   {
      if( this != &rhs )
      {
         id_ = rhs.id_; 
      }
      return( *this );
   }

   bool operator==( const BFContainerId& rhs ) const { return id_ == rhs.id_; }
   bool operator!=( const BFContainerId& rhs ) const { return !(*this == rhs); }
   bool operator<( const BFContainerId& rhs ) const { return id_ < rhs.id_; }

   long getId() const { return id_; }

   bool isValid() const;

private:
   long id_;
};


//CP20030106typedef BFContainerId BFContainerId;
//CP20030106typedef BFContainerId& BFContainerId&;
//CP20030106typedef const BFContainerId const BFContainerId;
//CP20030106typedef const BFContainerId& const BFContainerId&;
//CP20030106typedef BFContainerId& BFContainerId&;
//CP20030106
//CP20030106#define BFContainerId BFContainerId
//CP20030106#define x.isValid() x.isValid()
//CP20030106#define x.getId() x.getId()

namespace BF
{
   extern BPBASE_LINKAGE const BFContainerId NullContainerId;
   extern BPBASE_LINKAGE const BFContainerId AllContainerIds;
   extern BPBASE_LINKAGE const BFContainerId CrapContainerId;
}

//CP20030106#else
//CP20030106
//CP20030106#define BFContainerId long
//CP20030106#define BFContainerId& long
//CP20030106#define const BFContainerId& long
//CP20030106#define const BFContainerId long
//CP20030106#define BFContainerId& long&
//CP20030106
//CP20030106#define BFContainerId
//CP20030106#define x.isValid() ( x > 0 )
//CP20030106#define x.getId() x
//CP20030106
//CP20030106namespace BF
//CP20030106{
//CP20030106   enum { 
//CP20030106      NullContainerId = 0,
//CP20030106      AllContainerIds = -1,
//CP20030106      CrapContainerId = -2
//CP20030106   };
//CP20030106}
//CP20030106
//CP20030106#endif
