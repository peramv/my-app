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
// ^FILE   : JAdvisorTrans.hpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 23, 2000
//
// ^CLASS  : JAdvisorTrans
// ^PARENT : ListBase
//
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

class IFASTCBO_LINKAGE JAdvisorTrans : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   JAdvisorTrans( BFAbstractCBO &parent );
   virtual ~JAdvisorTrans();

   // Initialize function
   SEVERITY init( const DString& dstrBrokerCode, 
                  const DString& dstrBranchCode, 
                  const DString& dstrSlsRep, 
                  const DString& dstrFromDate, 
                  const DString& dstrToDate,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY getMore();

private:
   BFData _requestData;

};

///#endif // JADVISORTRANS_HPP