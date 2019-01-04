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
// ^FILE   : PriceAdditional.hpp
// ^AUTHOR : 
// ^DATE   : 03 May 2017
//
// ^CLASS    : PriceAdditional
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

class IFASTCBO_LINKAGE PriceAdditional : public MFCanBFCbo, private boost::noncopyable
{
public:

   PriceAdditional( BFAbstractCBO &parent );
   virtual ~PriceAdditional();

   SEVERITY init(const DString &transType,
                 const DString &unitValue,
                 const DString &chgFactor,
                 const BFDataGroupId &idDataGroup);

protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ACBRecord.hpp-arc  $
//
