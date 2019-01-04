#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_amount_is_not_allowed_for_custom_payout_swp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_amount_is_not_allowed_for_custom_payout_swp() { }
		~CIFast_IFast_ifastcbo_err_net_amount_is_not_allowed_for_custom_payout_swp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_AMOUNT_IS_NOT_ALLOWED_FOR_CUSTOM_PAYOUT_SWP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net Amount is not allowed for Custom Payout SWP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Net Amount is not allowed for Custom Payout SWP.")); }

        // Actions
	};
}