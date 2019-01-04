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
// ^FILE   :  DSTCRequest.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif

#ifndef DSTCREQUEST_HPP
   #include "DSTCRequest.hpp"
#endif

DSTCRequest::DSTCRequest(const DStringA &transType, const DStringA &transId, DSTCRequest::Type requestType)
: _requestType(requestType)
, _transType(transType)
, _transId(transId)
, _id(DString(_transType + _transId))
{
}

DSTCRequest::~DSTCRequest()
{
}

const DStringA &
DSTCRequest::getTransType() const
{
   return(_transType);
}

const DStringA &
DSTCRequest::getTransId() const
{
   return(_transId);
}

const DString &
DSTCRequest::getId() const
{
   return(_id);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastdbrkr/DSTCRequest.cpp-arc  $
// 
//    Rev 1.3   Nov 02 2004 18:19:38   SMITHDAV
// Allow DSTRequest instances to be typed as either "maint" or "query" request. This crude form of specialization was chosen so that all of the CBO files would not have to be changed.
// 
//    Rev 1.2   Oct 09 2002 23:55:22   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.1   Nov 01 2000 11:56:58   YINGBAOL
// add sysLoad support function
//
//   Rev 1.0   23 Oct 2000 20:34:32   SMITHDAV
//Initial revision.
*/