#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_gi_net_redemption_can_use_only_one_investment : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_gi_net_redemption_can_use_only_one_investment() { }
		~CIFast_IFast_ifastcbo_err_gi_net_redemption_can_use_only_one_investment() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GI_NET_REDEMPTION_CAN_USE_ONLY_ONE_INVESTMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net GI redemptions can select only one investment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les rachats nets à intérêt garanti  ne peuvent sélectionner qu'un seul investissement.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please correct.")); }
	};
}



