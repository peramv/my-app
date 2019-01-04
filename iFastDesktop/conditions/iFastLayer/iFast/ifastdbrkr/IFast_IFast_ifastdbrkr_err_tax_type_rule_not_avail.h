#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_tax_type_rule_not_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_tax_type_rule_not_avail() { }
		~CIFast_IFast_ifastdbrkr_err_tax_type_rule_not_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_TYPE_RULE_NOT_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type Rules not available for account tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart-Regeln für diese Konto-Steuerart nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay reglas de tipo tributario  disponibles para el tipo tributario de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les règles de type d'imposition ne sont pas disponibles pour le type d'imposition du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Regels voor belastingtype zijn niet beschikbaar voor belastingtype van het account")); }

        // Actions
	};
}



