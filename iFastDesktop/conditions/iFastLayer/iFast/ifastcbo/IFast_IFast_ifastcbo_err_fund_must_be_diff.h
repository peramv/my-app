#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_must_be_diff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_must_be_diff() { }
		~CIFast_IFast_ifastcbo_err_fund_must_be_diff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_MUST_BE_DIFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund category must be DIF.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de fonds doit être FIQ.")); }

        // Actions
	};
}



