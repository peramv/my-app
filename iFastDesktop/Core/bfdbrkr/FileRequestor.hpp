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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FileRequestor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : FileRequestor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class implements a data requestor that retrieves data from a file.
//
//******************************************************************************
#include <win32\platform.h>
#include <bfdbrkr\bfabstractrequestor.hpp>
#include <map>
#include <bfutil\bfcritsec.hpp>

// Import/Export resolution
#undef BFDBRKR_LINKAGE
#ifdef BFDBRKR_DLL
   #define BFDBRKR_LINKAGE CLASS_EXPORT
#else
   #define BFDBRKR_LINKAGE CLASS_IMPORT
#endif

class BFData;

class BFDBRKR_LINKAGE FileRequestor : public BFAbstractRequestor
{
public:
   FileRequestor(const DString &pathName, bool keyed=false, bool bOffline=false );
   FileRequestor(const FileRequestor &copy);

   virtual ~FileRequestor();

   const DString &getFileName( const BFRequest &request, const BFData &queryData ) const;
   const DString &getFileName( const BFRequest &request, const BFWriteBuffer *queryBuffer ) const;
   const DString &getFileName( ) const { return(_fileName);}
   bool fileExists( const BFRequest &request, const BFData &queryData ) const;
   void store( const BFRequest &request, const BFData &data ) const;

   virtual BFRequestor *clone() const;

   virtual unsigned long getRequestTime() const;
   virtual unsigned long getConnectionTime() const { return(-1);}
   virtual unsigned long getAssignTime() const { return(-1);}

protected:
   virtual BFWriteBuffer *createRequestBuffer(const BFRequest &request ) const;
   virtual SEVERITY receiveBuffer( const BFRequest &request, const BFWriteBuffer *queryBuffer, BFReadBuffer **receivedBuffer, const BFData* pQuery = NULL );

private:
   void checkPath();
   DStringA genFileName() const;

   SEVERITY getOfflineData( const BFRequest &request, const BFWriteBuffer *queryBuffer, BFReadBuffer **receivedBuffer );

   // get the configured Delay Time to simulate backend txn time.
   unsigned long getDelay( const BFRequest &request ) const;

   DString _pathName;
   mutable DString _fileName;
   mutable DStringA _dstrStubDataIni;      // .ini file specification for the index to the "stub data" files
   mutable DStringA _dstrViewIni;          // .ini file specification for the view control information
   mutable DStringA _dstrGlobalViewIni;    // .ini file specification for the global view control information
   bool _keyed;
   bool _bOffline;
   unsigned long  _requestTime;

   typedef std::map< DStringA, DStringA > MAP_STUBDATA;
   typedef MAP_STUBDATA::iterator ITER_STUBDATA;

   typedef std::map< DStringA, MAP_STUBDATA* > MAP_REQUESTS;
   typedef std::map< DStringA, MAP_STUBDATA* >::iterator ITER_REQUESTS;

   // this map is used only if the requestor is *offline*.  When this is the case
   // the map is loaded, under guard by the s_csInitMapRequests_ CriticalSection,
   // on first use.  All requests to get data are then funnelled through the map.
   static MAP_REQUESTS s_mapRequests_;
   static BFCritSec s_csInitMapRequests_;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/core/bfdbrkr/FileRequestor.hpp-arc  $
//
//   Rev 1.14   Mar 27 2009 10:18:06   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.13   Oct 09 2002 17:40:44   PURDYECH
//New PVCS Database
//
//   Rev 1.12   Aug 29 2002 12:49:28   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.11   22 May 2002 17:56:08   PURDYECH
//BFData Implementation
//
//   Rev 1.10   22 Mar 2002 15:17:12   PURDYECH
//BFData integration
//
//   Rev 1.9   29 Oct 2001 16:21:48   PURDYECH
//Added code to support connectionTime reporting for IPBlast
//
//   Rev 1.8   Oct 05 2001 10:09:22   PURDYECH
//Added the TimeScale .ini entry to alter the delay time for a view by an arbitrary factor.
//
//   Rev 1.7   25 Sep 2001 13:22:48   PURDYECH
//Stub File Fixes.
//
//   Rev 1.6   18 Sep 2001 15:20:44   PURDYECH
//Get STUB_DATA working again.
//
//   Rev 1.5   07 Aug 2001 11:24:44   PURDYECH
//Added code to get timing data for the assignment of incoming data to a Data object.
//
//   Rev 1.4   17 Jul 2001 11:08:26   PURDYECH
//Added getRequestTime method
//
//   Rev 1.3   Jun 26 2001 12:54:40   PURDYECH
//Infrastructure Release 1.9 Integration.
//
//   Rev 1.2   Jun 12 2001 16:35:02   DINACORN
//Sync. up with SSB (1.0.1.0)
//
//   Rev 1.1   03 May 2001 14:03:08   SMITHDAV
//Session management restructuring.
//
//   Rev 1.0   23 Oct 2000 20:21:14   SMITHDAV
//Initial revision.
 */
