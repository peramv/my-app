#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_annuitant_for_to_acct_must_be_at_least_50_years : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_annuitant_for_to_acct_must_be_at_least_50_years() { }
		~CIFast_IFast_ifastcbo_err_annuitant_for_to_acct_must_be_at_least_50_years() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUITANT_FOR_TO_ACCT_MUST_BE_AT_LEAST_50_YEARS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The annuitant for the To account must be at least 50 years of age.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The annuitant for the To account must be at least 50 years of age.")); }

        // Actions
	};
}