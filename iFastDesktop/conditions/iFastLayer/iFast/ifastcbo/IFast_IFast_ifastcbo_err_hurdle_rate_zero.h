#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_hurdle_rate_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_hurdle_rate_zero() { }
		~CIFast_IFast_ifastcbo_err_hurdle_rate_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_HURDLE_RATE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Hurdle Rate cannot be zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de rendement minimal ne peut pas être zéro.")); }

        // Actions
	};
}



