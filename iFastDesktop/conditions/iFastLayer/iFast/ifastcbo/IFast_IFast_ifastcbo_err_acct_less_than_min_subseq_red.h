#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_less_than_min_subseq_red : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_less_than_min_subseq_red() { }
		~CIFast_IFast_ifastcbo_err_acct_less_than_min_subseq_red() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_LESS_THAN_MIN_SUBSEQ_RED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account: Less than Min. Subsequent Redemption")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Account: Less than Min. Subsequent Redemption")); }

        // Actions
	};
}