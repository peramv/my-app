#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dif_fund_only_allow_direct_order : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dif_fund_only_allow_direct_order() { }
		~CIFast_IFast_ifastcbo_err_dif_fund_only_allow_direct_order() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIF_FUND_ONLY_ALLOW_DIRECT_ORDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DIF fund only allows direct order.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls les ordres directs sont acceptés pour le FIJ.")); }

        // Actions
	};
}


