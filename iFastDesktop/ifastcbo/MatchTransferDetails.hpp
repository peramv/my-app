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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : MatchTransferDetails.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : August 10th, 2001
//
// ^CLASS    : MatchTransferDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

//TODO: add headers that need to be included in the interface class

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class SplitCommissionList;

class IFASTCBO_LINKAGE MatchTransferDetails : public MFCanBFCbo, private boost::noncopyable
{
public:
   static DString getUniqueKey( DString& TransId );

   MatchTransferDetails( BFAbstractCBO &parent );
   virtual ~MatchTransferDetails();

   SEVERITY init( const BFData& data );

   void getField( const BFFieldId& idField, DString& strFieldValue, 
                  const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;

//      SEVERITY getSplitCommissionList(SplitCommissionList *&rpSplitCommissionList,const BFDataGroupId& idDataGroup);
   void getCurrency(const BFDataGroupId& idDataGroup, DString& currency) const;
   SEVERITY getSplitCommissionList(SplitCommissionList *&rpSplitCommissionList,const BFDataGroupId& idDataGroup);

};
