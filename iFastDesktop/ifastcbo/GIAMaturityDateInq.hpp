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
// Copyright 2011 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : GIAMaturityDateInq.hpp
// ^AUTHOR : 
// ^DATE   : Nov, 2011
//
// ^CLASS    : GIAMaturityDateInq
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

class IFASTCBO_LINKAGE GIAMaturityDateInq : public MFCanBFCbo, private boost::noncopyable
{
public:

   GIAMaturityDateInq( BFAbstractCBO &parent );
   virtual ~GIAMaturityDateInq();

   SEVERITY init(const DString& dstrTradeDate,
                 const DString& dstrInvestTerm,
                 const DString& dstrIntCredFreq,
                 const DString& dstrLastIntCredDate,
                 const DString& strTrack = I_("N"),
                 const DString& strPageName = NULL_STRING);

protected:

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/GIAMaturityDateInq.hpp-arc  $
//
//   Rev 1.0   Nov 30 2011 00:19:56   dchatcha
//Initial revision.
//
//   Rev 1.0   Dec 27 2010 02:11:40   dchatcha
//Initial revision.
//
