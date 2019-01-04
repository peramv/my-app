#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_hurdle_calculated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_hurdle_calculated() { }
		~CIFast_IFast_ifastcbo_warn_hurdle_calculated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_HURDLE_CALCULATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Hurdle Rate will be calculated between %DATE1% to %DATE2%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de rendement minimal sera calculé entre le %DATE1% et le %DATE2%.")); }

        // Actions
	};
}



