#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1




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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : CommitmentProduct.hpp
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : CommitmentProduct
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

class IFASTCBO_LINKAGE CommitmentProduct : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   CommitmentProduct( BFAbstractCBO &parent );
   virtual ~CommitmentProduct();

   // Initialize function
   SEVERITY init( const BFData &data );  

private:
   BFData _requestData;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CommitmentProduct.hpp-arc  $
//
//   Rev 1.0   Feb 24 2012 18:10:24   if991250
//Initial revision.
// 
*/