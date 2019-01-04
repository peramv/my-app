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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundClassHolding.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 04/19/99
//
// ^CLASS    : ACBList
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

class IFASTCBO_LINKAGE FundClassHolding : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FundClassHolding( BFAbstractCBO &parent );
   virtual ~FundClassHolding( void );

   // Initialize function
   SEVERITY init( const BFData& data );

   void getStrKey( DString& dstKey, const DString& dstFund, const DString& dstClass );
   void getStrKey ( DString& strKey, const BFData* data );
   void getPercOfTotal( DString& perc );

private:

};
