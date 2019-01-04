#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_value_between_two_reocrds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_value_between_two_reocrds() { }
		~CIFast_IFast_ifastcbo_warn_value_between_two_reocrds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_VALUE_BETWEEN_TWO_REOCRDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Index Value is entered between existing effective dates. Hurdle Rate will be calculated between %DATE1% to %DATE2% and %DATE3% to %DATE4%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de l'index a été saisie entre des dates d'entrée en vigueur existantes. Le taux de rendement minimal sera calculé entre le %DATE1% et le %DATE2% et entre le %DATE3% et le %DATE4%.")); }

        // Actions
	};
}



