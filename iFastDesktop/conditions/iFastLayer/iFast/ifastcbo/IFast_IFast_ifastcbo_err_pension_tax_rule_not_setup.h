#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pension_tax_rule_not_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pension_tax_rule_not_setup() { }
		~CIFast_IFast_ifastcbo_err_pension_tax_rule_not_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENSION_TAX_RULE_NOT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type rules have not yet been set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerarten-Regeln wurden noch nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Aún no se han configurado las reglas de tipo tributario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les règles de type d'imposition n'ont pas encore été réglées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen regels voor het belastingtype ingesteld")); }

        // Actions
	};
}



