#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_custom_trading_schedule_is_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_custom_trading_schedule_is_missing() { }
		~CIFast_IFast_ifastcbo_warn_custom_trading_schedule_is_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CUSTOM_TRADING_SCHEDULE_IS_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Custom trading schedule is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le tableau d'opérations personnalisées est manquant.")); }

        // Actions
	};
}



