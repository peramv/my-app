#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundGroupType.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/09/02
//
// ^CLASS    : FundGroupType
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

class IFASTCBO_LINKAGE FundGroupType : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundGroupType( BFAbstractCBO &parent );
   ~FundGroupType();

   void init(const BFData& data);

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundGroupType.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:42:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Jan 13 2003 10:15:26   KOVACSRO
//Initial revision.

*/