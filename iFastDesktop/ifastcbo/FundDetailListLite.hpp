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
//    Copyright 2004 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundDetailListLite.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundDetailListLite
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundDetailListLite : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundDetailListLite( BFAbstractCBO &parent );
   virtual ~FundDetailListLite();

   void AssociateObject( const DString& dstrSearchType, const DString& dstrValue );
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundDetailListLite.hpp-arc  $
//
//   Rev 1.0   Dec 03 2004 16:51:00   hernando
//Initial revision.
