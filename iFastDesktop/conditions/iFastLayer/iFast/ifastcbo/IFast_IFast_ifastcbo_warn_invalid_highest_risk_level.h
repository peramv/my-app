#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_highest_risk_level : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_highest_risk_level() { }
		~CIFast_IFast_ifastcbo_warn_invalid_highest_risk_level() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_HIGHEST_RISK_LEVEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Chosen Risk level has an invalid stop date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The Chosen Risk level has an invalid stop date.")); }

        // Actions
	};
}