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
// ^FILE   : SavingPlanMaster.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 05/23/2001
//
// ^CLASS    : SavingPlanMaster
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

class IFASTCBO_LINKAGE SavingPlanMaster : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   SavingPlanMaster( BFAbstractCBO &parent );
   virtual ~SavingPlanMaster();

   // Initialize function
   SEVERITY init( const BFData &data );  

private:
   BFData _requestData;

};

