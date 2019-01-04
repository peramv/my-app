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

// Forward declarations
class GenericInterface;

/**
 * Base class for derived factory classes to be registered with dispatchers.
 *
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/01/2000</dd></dl>
 * @version 0.1
 */

// Import/Export resolution
#undef BPBASE_LINKAGE
#ifdef BPBASE_DLL
   #define BPBASE_LINKAGE CLASS_EXPORT
#else
   #define BPBASE_LINKAGE CLASS_IMPORT
#endif

class BPBASE_LINKAGE AbstractFactory
{
public:
   AbstractFactory()
   {}
   virtual ~AbstractFactory()
   {}
   virtual GenericInterface *create(
                                   int commandID
                                   ) = 0;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfproc/AbstractFactory.hpp-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 17:40:48   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   22 Mar 2002 15:11:18   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.0   Mar 02 2000 11:38:28   MCNABBGL
 * Initial revision.
 * 
 */
