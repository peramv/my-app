#pragma once



//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE      : FundLmtOverride.hpp
// ^AUTHOR    : Winnie Shiu
// ^DATE      : January 09, 2003
//
// ^CLASS     : FundLmtOverride
// ^SUBCLASS  :
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


class IFASTCBO_LINKAGE FundLmtOverride : public MFCanBFCbo, private boost::noncopyable
{
public:
   FundLmtOverride( BFAbstractCBO &parent );
   virtual ~FundLmtOverride();

   SEVERITY init (const BFData& data);
private:

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundLmtOverride.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:42:40   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Jun 25 2004 16:38:12   popescu
//PST 10031525, fund limitation override issues
//
//   Rev 1.0   Jan 12 2003 16:05:32   WINNIE
//Initial revision.
//
*/