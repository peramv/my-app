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
// ^FILE   : SavingPlanMasterList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 05/23/2001
//
// ^CLASS    : SavingPlanMasterList
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

class IFASTCBO_LINKAGE SavingPlanMasterList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   SavingPlanMasterList( BFAbstractCBO &parent );
   virtual ~SavingPlanMasterList();

   // Initialize function
   SEVERITY init( const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   virtual void getStrKey( DString &strKey, const BFData *data );

};


