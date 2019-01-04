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
// ^FILE   : DefaultSplitCommList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/05/2001
//
// ^CLASS    : DefaultSplitCommList
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

class IFASTCBO_LINKAGE DefaultSplitCommList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   DefaultSplitCommList( BFAbstractCBO &parent );
   virtual ~DefaultSplitCommList( void );

   // Initialize function
   SEVERITY init( const DString& Account,
                  const DString& AccountTo,
                  const DString& Fund,
                  const DString& FundTo,
                  const DString& Class,
                  const DString& ClassTo,
                  const DString& PUD,
                  const DString& FlatPrcnt,
                  const DString& InPayType,
                  const DString& IAmount,
                  const DString& InTransType,
                  const DString& EffectiveDate,
                  const DString& InGrossNet,
                  const DString& InBrokerCode,
                  const DString& InBranchCode,
                  const DString& InSlsRepCode,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );                                          

   SEVERITY init( const BFData& data );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
};

///#endif

