#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_hurdle_between_two_reocrds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_hurdle_between_two_reocrds() { }
		~CIFast_IFast_ifastcbo_warn_hurdle_between_two_reocrds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_HURDLE_BETWEEN_TWO_REOCRDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Hurdle Rate is entered between existing effective dates.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de rendement minimal est saisi entre deux dates en vigueur.")); }

        // Actions
	};
}



