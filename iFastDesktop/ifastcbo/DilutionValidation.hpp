#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//  The computer systems, procedures, data bases and
//  programs created and maintained by International Financial Data Services,
//  are proprietary in nature and as such are confidential.
//  Any unauthorized use or disclosure of such information
//  may result in civil liabilities.
//
//  Copyright 2018 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DilutionValidation.hpp
// ^AUTHOR : Nuengruethai Wirojyuti
// ^DATE   : Jan 17, 2018
//
// ^CLASS    : DilutionValidation
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

class IFASTCBO_LINKAGE DilutionValidation : public MFCanBFCbo, private boost::noncopyable
{
public:
  DilutionValidation(BFAbstractCBO &parent);
  virtual ~DilutionValidation();
  
  SEVERITY init(const DString &dstrAccountNum,
                const DString &dstrFundCode,
                const DString &dstrClassCode,
                const DString &strDilutionLinkNum,
				const DString &strMatchingKey = NULL_STRING);
  
  SEVERITY addConditions(DString &dstrDilutionNSM);

private:
  DString _dilutionLinkNum;
};