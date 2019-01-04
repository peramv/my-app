#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : CBOInstanceFieldInfo.hpp
// ^AUTHOR : Paul Dardeau
// ^DATE   : 02/05/97
//
// ^CLASS  : CBOInstanceFieldInfo
// ^PARENT : 
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
//
//******************************************************************************

#include <commonport.h>
#include "instancefieldinfo.hpp"

// Import/Export resolution
#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
    #define BFBASE_LINKAGE CLASS_EXPORT
#else
    #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class BFBASE_LINKAGE CBOInstanceFieldInfo : public InstanceFieldInfo
{
   public:
      CBOInstanceFieldInfo();
      CBOInstanceFieldInfo( int nFields,
                            unsigned long ulGroupFlag = 0x0000 );
      CBOInstanceFieldInfo( const CBOInstanceFieldInfo& copy );
      ~CBOInstanceFieldInfo();

      CBOInstanceFieldInfo& operator=( const CBOInstanceFieldInfo& copy );

   private:
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/DSTCProjects/BusinessComponents/Inc/cboinstancefieldinfo.hpp-arc  $
 * 
 *    Rev 1.1   22 Mar 2002 15:11:48   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
// 
//    Rev 1.0   Feb 15 2000 10:57:46   SMITHDAV
// Initial revision.
// 
//    Rev 1.0   Jul 07 1999 13:47:04   SMITHDAV
// Original revision.
// 
//    Rev 1.0   29 Jul 1998 23:58:10   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.2   Mar 10 1998 14:41:00   DT21815
// Added comment header block and comment revision block.
//
//

