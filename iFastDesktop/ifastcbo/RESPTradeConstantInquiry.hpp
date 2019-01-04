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
// Copyright 2010 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPTradeConstantInquiry.hpp
// ^AUTHOR : 
// ^DATE   : Oct, 2010
//
// ^CLASS    : RESPTradeConstantInquiry
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

class IFASTCBO_LINKAGE RESPTradeConstantInquiry : public MFCanBFCbo, private boost::noncopyable
{
public:

   RESPTradeConstantInquiry( BFAbstractCBO &parent );
   virtual ~RESPTradeConstantInquiry();

   SEVERITY init(const DString& strAccountNum,
                 const DString& strTaxYear,
                 const DString& strRESPBenefId,
                 const BFDataGroupId& idDataGroup,
                 const DString& strTrack = I_("N"),
                 const DString& strPageName = NULL_STRING);

protected:

private:
                                       
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPTradeConstantInquiry.hpp-arc  $
//
//   Rev 1.0   Oct 29 2010 04:04:38   kitticha
//Initial revision.
//
*/
