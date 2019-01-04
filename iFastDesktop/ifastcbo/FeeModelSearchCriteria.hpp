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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FeeModelSearchCriteria.hpp
// ^AUTHOR : 
// ^DATE   : Jan 28, 2013
//
// ^CLASS    : FeeModelSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FeeModelSearchCriteria : public MFCanBFCbo, private boost::noncopyable
{
public:
   FeeModelSearchCriteria( BFAbstractCBO &parent );
   virtual ~FeeModelSearchCriteria();

   SEVERITY Init();

};