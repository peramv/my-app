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
// ^FILE   : DSTCRequest.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : September 2000
//
// ^CLASS    : DSTCRequest
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include <win32\platform.h>
#include <DString.hpp>
#include <bfdbrkr\BFRequest.hpp>

// Import/Export resolution
#undef IFASTDBRKR_LINKAGE
#ifdef IFASTDBRKR_DLL
   #define IFASTDBRKR_LINKAGE CLASS_EXPORT
#else
   #define IFASTDBRKR_LINKAGE CLASS_IMPORT
#endif

class IFASTDBRKR_LINKAGE DSTCRequest : public BFRequest
{
public:

   enum Type {
      TYPE_QUERY,
      TYPE_MAINT,
      TYPE_SYSLOAD
   } ;

   DSTCRequest(const DStringA &transType, const DStringA &transId, Type requestType);
   virtual ~DSTCRequest();

   const DStringA &getTransType() const;
   const DStringA &getTransId() const;
   virtual const DString &getId() const;

   virtual bool isSysLoadRequest() const {return (_requestType == TYPE_SYSLOAD);}
   virtual bool isMaintRequest() const {return (_requestType == TYPE_MAINT);}
   bool isQueryRequest() const {return (_requestType != TYPE_MAINT);}

private:
   DSTCRequest(); // not implemented

   const Type _requestType;
   const DStringA _transType;
   const DStringA _transId;
   const DString  _id;

};


///#endif // 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCRequest.hpp-arc  $
//
//   Rev 1.5   Nov 02 2004 18:09:18   SMITHDAV
//Allow DSTRequest instances to be typed as either "maint" or "query" request. This crude form of specialization was chosen so that all of the CBO files would not have to be changed.
//
//   Rev 1.4   Oct 09 2002 23:55:22   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   22 May 2002 18:21:24   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:15:38   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Nov 01 2000 11:55:20   YINGBAOL
//add sysLoad support function
//
//   Rev 1.0   23 Oct 2000 20:34:32   SMITHDAV
//Initial revision.
*/