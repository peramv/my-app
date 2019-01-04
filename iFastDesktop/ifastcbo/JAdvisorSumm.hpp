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
// ^FILE   : JAdvisorSumm.hpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 24, 2000
//
// ^CLASS  : JAdvisorSumm
// ^PARENT : ListBase

// ^CLASS DESCRIPTION :
//    Implements View 92.
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

class IFASTCBO_LINKAGE JAdvisorSumm : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   JAdvisorSumm( BFAbstractCBO &parent );
   virtual ~JAdvisorSumm();

   // Initialize function
   SEVERITY init( const DString& dstrBrokerCode, 
                  const DString& dstrBranchCode, 
                  const DString& dstrSlsRep,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY getMore();

private:

   BFData _queryData;

};

///#endif // JADVISORSUMM_HPPP