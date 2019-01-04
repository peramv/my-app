#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2012 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundSERVBrokerValidation.hpp
// ^AUTHOR : 
// ^DATE   : Apr, 2012
//
// ^CLASS    : FundSERVBrokerValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE FundSERVBrokerValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   FundSERVBrokerValidation( BFAbstractCBO &parent );
   virtual ~FundSERVBrokerValidation();

   SEVERITY init(const DString& dstrValidationType,
                 const DString& dstrAccountNum,
                 const DString& dstrCurBrokerCode,
                 const DString& dstrCurBranchCode,
                 const DString& dstrCurSlsRep,
                 const DString& dstrNewBrokerCode,
                 const DString& dstrNewBranchCode,
                 const DString& dstrNewSlsRep,
                 const DString& strTrack = I_("N"),
                 const DString& strPageName = NULL_STRING);

protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundSERVBrokerValidation.hpp-arc  $
//
//   Rev 1.1   May 11 2012 18:23:38   dchatcha
//P0186479 FN10 - Gap 14G - Block Service Unit Transfers.
//
//   Rev 1.0   May 03 2012 09:40:22   dchatcha
//Initial revision.
//

