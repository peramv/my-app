#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_currency_not_allowed_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_currency_not_allowed_tax_type() { }
		~CIFast_IFast_ifastdbrkr_err_currency_not_allowed_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CURRENCY_NOT_ALLOWED_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Currency not allowed in this tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Währung für diese Steuerart  nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite la divisa en este tipo tributario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Monnaie non autorisée pour ce type d'imposition")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Valuta is niet toegestaan in dit belastingtype")); }

        // Actions
	};
}



