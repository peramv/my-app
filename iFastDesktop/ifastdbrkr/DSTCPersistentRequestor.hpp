#pragma once
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
// ^FILE   : DSTCPersistentRequestor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : DSTCPersistentRequestor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include <win32\platform.h>
#include <ifastdbrkr\dstcrequestor.hpp>
#include <map>

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
   #define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
   #define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class DSTCSecurity;
class BFConnection;

enum DSTCPersistMode
{
   NO_PERSIST = 0,
   START_PERSIST,
   IN_PERSIST,
   END_PERSIST
};

class IFASTDBRKR_LINKAGE DSTCPersistentRequestor : public DSTCRequestor
{
public:
   DSTCPersistentRequestor(const DSTCSecurity *security, const DString &mgmtCoId, const DString &ppType);
   virtual ~DSTCPersistentRequestor();
   void setCommitParams (BFData &commitParams);
   SEVERITY commit(BFData& persistStopResponse);
   SEVERITY rollback();

   virtual BFRequestor *clone() const;

protected:

   virtual BFWriteBuffer *createRequestBuffer(const BFRequest &request) const;
   virtual SEVERITY receiveBuffer( const BFRequest &request, 
                                   const BFWriteBuffer *queryBuffer, 
                                   BFReadBuffer **receivedBuffer, 
                                   const BFData* pQuery = NULL );

   DSTCPersistentRequestor(); // not implemented
   DSTCPersistentRequestor(const DSTCRequestor &copy);// not implemented

private:

   DSTCPersistMode _persistMode;
   DStringA _persistHandle;
   DString _mgmtCoId;
   bool _stale;
   BFData *_commitParams;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCPersistentRequestor.hpp-arc  $
//
//   Rev 1.11   Mar 27 2009 10:20:10   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.10   Feb 06 2009 14:53:02   purdyech
//Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
//
//   Rev 1.9   15 Nov 2007 17:45:10   popescu
//PET 5636/01 Internal audit tracking
//
//   Rev 1.8   Oct 09 2002 23:55:22   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.7   Jun 14 2002 16:50:26   VASILEAD
//Added ppType param to the class constructor
//
//   Rev 1.6   22 May 2002 18:21:24   PURDYECH
//BFData Implementation
//
//   Rev 1.5   19 Mar 2002 13:15:38   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.4   12 Jun 2001 13:49:06   SMITHDAV
//Fix bug -- set mgmtCoId for start and end persist views.
//
//   Rev 1.3   03 May 2001 14:04:02   SMITHDAV
//Session management restructuring.
//
//   Rev 1.2   16 Feb 2001 14:55:40   SMITHDAV
//Fixed Substitution values. ??Some testing required??
//
//   Rev 1.1   18 Jan 2001 11:55:58   SMITHDAV
//Moved PersistMode enum from DSTCRequestBuffer scope to global scope and into file DSTCPersistentRequestor.hpp so that it can be accessed outside of the DstcDbrkr lib.
//
//   Rev 1.0   23 Oct 2000 20:34:32   SMITHDAV
//Initial revision.
 */
