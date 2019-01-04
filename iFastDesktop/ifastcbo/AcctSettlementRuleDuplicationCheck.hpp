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
//    Copyright 2008 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctSettlementRuleDuplicationCheck.hpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : April 2008
//
// ^CLASS    : AcctSettlementRuleDuplicationCheck
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class AcctSettlementRuleDuplicationCheck;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class ErrMsgRulesList;

class IFASTCBO_LINKAGE AcctSettlementRuleDuplicationCheck : public MFCanBFCbo, private boost::noncopyable
{
public:
    static void buildKey(  DString &strKey,
                           const DString &dstrAccountNum,
                           const DString &dstrRuleType,
                           const DString &dstrFundCode,
                           const DString &dstrClassCode,
                           const DString &dstrEffectiveDate,
                           const DString &dstrStopDate,
                           const DString &dstrAcctControlsRID,
						   const DString &dstrFundGroup
                         );
public:
    AcctSettlementRuleDuplicationCheck(BFAbstractCBO &parent);
    virtual ~AcctSettlementRuleDuplicationCheck(void);
    
    SEVERITY init( const DString &dstrAccountNum,
                   const DString &dstrRuleType,
                   const DString &dstrFundCode,
                   const DString &dstrClassCode,
                   const DString &dstrEffectiveDate,
                   const DString &dstrStopDate,
                   const DString &dstrAcctControlsRID,
				   const DString &dstrFundGroup);

protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSettlementRuleDuplicationCheck.hpp-arc  $ */
//
//   Rev 1.0   Apr 16 2008 18:44:08   daechach
//Initial revision.
