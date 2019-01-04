#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_contr_maturity_red_100_percent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_contr_maturity_red_100_percent() { }
		~CIFast_IFast_ifastcbo_warn_contr_maturity_red_100_percent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CONTR_MATURITY_RED_100_PERCENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation percentage for instructions must sum up to 100%")); }

        // Actions
	};
}



