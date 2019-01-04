#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_hurdle_rate_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_hurdle_rate_zero() { }
		~CIFast_IFast_ifastcbo_warn_hurdle_rate_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_HURDLE_RATE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Hurdle Rate cannot be zero.")); }

        // Actions
	};
}



