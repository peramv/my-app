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
// ^FILE   : SEGTradeEntryValidation.hpp
// ^AUTHOR : 
// ^DATE   : Feb, 2012
//
// ^CLASS    : SEGTradeEntryValidation
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

class IFASTCBO_LINKAGE SEGTradeEntryValidation : public MFCanBFCbo, private boost::noncopyable
{
public:

   SEGTradeEntryValidation( BFAbstractCBO &parent );
   virtual ~SEGTradeEntryValidation();

   SEVERITY init(const DString& dstrAccountNum,
                 const DString& dstrFundCode,
                 const DString& dstrClassCode,
                 const DString& dstrAccountTo,
                 const DString& dstrFundToCode,
                 const DString& dstrClassToCode,
                 const DString& dstrTradeDate,
                 const DString& dstrValidationType,
                 const DString& dstrTransType,
                 const DString& dstrTransID,
                 const DString& strTrack = I_("N"),
                 const DString& strPageName = NULL_STRING);

protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SEGTradeEntryValidation.hpp-arc  $
//
//   Rev 1.1   Mar 05 2012 11:46:52   dchatcha
//P0186484 FN05 - SEG Trade Processing.
//
//   Rev 1.0   Feb 28 2012 20:41:42   dchatcha
//Initial revision.
//

