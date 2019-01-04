#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : JData.hpp
// ^AUTHOR : Cristina Oltean
// ^DATE   : Jan 2001
//
//******************************************************************************

#pragma warning( push )
#pragma warning( disable: 4275 )


#include <bfdata\bfdata.hpp>

#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class BFRequest;

class BFBASE_LINKAGE JData
{

   friend class HostTransactionContainerIterator;

public:

   JData( const BFRequest& rbfRequest, BFData* pdataRequest,  BFData* pdataResponse );
   JData( DString& dstrTransId, const BFRequest& rbfRequest, BFData* pdataRequest, BFData* pdataResponse );
   ~JData();
   BFData* getRequestDataObject(){ return(_pdataRequest);}; 
private:

   BFData* _pdataRequest;
   BFData* _pdataResponse; 
   DString _dstrTransId; 
   const BFRequest& _rbfRequest;
   bool _blCommited;

};

#pragma warning( pop )

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF Core/bfcbo/JData.hpp-arc  $
//
//   Rev 1.7   Sep 27 2004 09:40:44   PURDYECH
//Clean up compiler warnings so that there are no complaints about silly things (like truncated debug names...)
//
//   Rev 1.6   Oct 09 2002 17:40:14   PURDYECH
//New PVCS Database
//
//   Rev 1.5   22 May 2002 18:08:58   PURDYECH
//BFData Implementation
//
//   Rev 1.4   22 Mar 2002 15:11:58   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.3   03 May 2001 14:03:30   SMITHDAV
//Session management restructuring.
//
//   Rev 1.2   08 Mar 2001 15:27:18   BUZILAMI
//added getRequestDataObject() accessor method
 * 
*/