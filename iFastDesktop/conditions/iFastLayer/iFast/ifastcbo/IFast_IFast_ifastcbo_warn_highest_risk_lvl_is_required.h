#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_highest_risk_lvl_is_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_highest_risk_lvl_is_required() { }
		~CIFast_IFast_ifastcbo_warn_highest_risk_lvl_is_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_HIGHEST_RISK_LVL_IS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A Chosen Risk level has not been set.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("A Chosen Risk level has not been set.")); }

        // Actions
	};
}