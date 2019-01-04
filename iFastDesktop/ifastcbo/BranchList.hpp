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
//******************************************************************************
//
// ^FILE   : BranchList.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : November 07, 1999
//
// ^CLASS  : BranchList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//    Implements View 91.
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


class IFASTCBO_LINKAGE BranchList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   BranchList( BFAbstractCBO &parent );
   virtual ~BranchList( void );

   // Initialize function
   SEVERITY init( const DString&  dstrBrokerCode, 
                  const DString&  dstrBranchCode,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING); 

   SEVERITY getMore();

   SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );

private:
   BFData requestData;
};

///#endif // BRANCHLIST_HPP