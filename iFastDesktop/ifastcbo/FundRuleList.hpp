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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundRuleList.hpp
// ^AUTHOR : 
// ^DATE   : 31 May 2016
//
// ^CLASS    : FundRuleList
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

class IFASTCBO_LINKAGE FundRuleList : public MFCanBFCbo, private boost::noncopyable
{
public:
	FundRuleList(BFAbstractCBO &parent);
	virtual ~FundRuleList();

	//SEVERITY init(const BFData& data);
	SEVERITY init(const DString &dstrRuleType,
                  const DString &dstrTrack = I_("N"), 
		          const DString &dstrPageName = NULL_STRING);

    bool isRuleApplied(const DString &ruleType,
                       const DString &ruleLevel,
                       const DString &fundGroupCode,
                       const DString &fundCode,
                       const DString &classCode,
                       const DString &date);

    DString getRuleDetailByDate(const DString &ruleType,
                                const DString &ruleLevel,
                                const BFFieldId idField,
                                const DString &fundGroupCode,
                                const DString &fundCode,
                                const DString &classCode,
                                const DString &date,
                                const bool formatted = false);

    bool isSoftCapped(const DString &fundCode,
                      const DString &classCode,
                      const DString &fundGroupCode,
                      const DString &date);

    bool isSoftCappedAtFundGroupLvl(const DString &date,
                                    const DString &dstrFundGroupCode);

    bool isSoftCappedAtFundLvl(const DString &date,
                               const DString &dstrFundCode);

    bool isSoftCappedAtFundClassLvl(const DString &date,
                                    const DString &dstrFundCode,
                                    const DString &dstrClassCode);

protected:

private:
};