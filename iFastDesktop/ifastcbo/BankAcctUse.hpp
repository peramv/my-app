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
// ^FILE   : BankAcctUse.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/03/02
//
// ^CLASS    : BankAcctUse
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

class IFASTCBO_LINKAGE BankAcctUse : public MFCanBFCbo, private boost::noncopyable
{
public:
   BankAcctUse( BFAbstractCBO &parent );
   ~BankAcctUse();

   void init(const BFData& data);

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastcbo/BankAcctUse.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 23:54:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Aug 29 2002 12:51:50   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.0   Jul 05 2002 12:03:26   KOVACSRO
//Initial revision.
//

*/