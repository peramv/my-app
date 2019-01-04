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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeLevelOverrideRules.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : May, 2014
//
// ^CLASS    : TradeLevelOverrideRules
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <SrcPrag.h>
#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class IFASTCBO_LINKAGE TradeLevelOverrideRules: public MFCanBFCbo, private boost::noncopyable
{
public:

   TradeLevelOverrideRules( BFAbstractCBO &parent );
   virtual ~TradeLevelOverrideRules();
   SEVERITY init( const DString &_dstrAccountNum, 
                  const DString &_dstrFundCode, 
                  const DString &_dstrClassCode, 
                  const DString &dstrTransType, 
                  const DString &dstrEffectiveDate, 
                  const DString &dstrBrokerCode, 
				  const DString &dstrBranchCode, 
                  const DString &dstrSalesRepCode,
                  bool  bDataNotFounderror = false);   

   SEVERITY addConditions(const BFDataGroupId &idDataGroup);
private:
   DString  _dstrFundCode,
            _dstrClassCode,
	        _dstrAccountNum,
            _dstrTransType,
            _dstrEffectiveDate,
            _dstrBrokerCode, 
            _dstrBranchCode, 
            _dstrSalesRepCode;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeLevelOverrideRules.cpp-arc  $*/
// Rev 1.0   26-May-2014  Robbins
// Initial revision.
