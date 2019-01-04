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
// ^FILE   : DeductionList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/22/99
//
// ^CLASS    : DeductionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE DeductionList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   DeductionList( BFAbstractCBO &parent );
   virtual ~DeductionList( void );

   // Initialize function
   SEVERITY init( BFData& InstData, DString& currency );


protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   DString _TransId;
   DString _currency;
};

///#endif

