#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fractional_values_not_allowed_in_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fractional_values_not_allowed_in_currency() { }
		~CIFast_IFast_ifastcbo_err_fractional_values_not_allowed_in_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FRACTIONAL_VALUES_NOT_ALLOWED_IN_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fractional values not allowed in currency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bruchwerte bei Währung nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten valores fraccionarios en divisa")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les valeurs fractionnelles ne sont pas autorisées dans cette monnaie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fractionele waarden zijn niet toegestaan in valuta")); }

        // Actions
	};
}



