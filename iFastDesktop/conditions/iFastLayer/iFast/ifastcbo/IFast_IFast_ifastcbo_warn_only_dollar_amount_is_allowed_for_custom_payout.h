#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_only_dollar_amount_is_allowed_for_custom_payout : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_only_dollar_amount_is_allowed_for_custom_payout() { }
		~CIFast_IFast_ifastcbo_warn_only_dollar_amount_is_allowed_for_custom_payout() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ONLY_DOLLAR_AMOUNT_IS_ALLOWED_FOR_CUSTOM_PAYOUT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only Dollar Amount is allowed for Custom Payout.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Only Dollar Amount is allowed for Custom Payout.")); }

        // Actions
	};
}