#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF Core/bfproc/bfcontainerid.cpp-arc  $", "$Revision:   1.0  $" )

#include <srcprag.h>
#include <commonport.h>
#include <windows.h>
#include <assert.h>

#include "bfcontainerid.hpp"

//CP20030106#ifdef _NEW_BFContainerId_MODEL_

namespace BF
{
   extern BPBASE_LINKAGE const BFContainerId NullContainerId( 0 );
   extern BPBASE_LINKAGE const BFContainerId AllContainerIds( -1 );
   extern BPBASE_LINKAGE const BFContainerId CrapContainerId( -2 );
}


bool BFContainerId::isValid() const 
{ 
   return id_ > 0; 
}

//CP20030106#else
//CP20030106#endif
