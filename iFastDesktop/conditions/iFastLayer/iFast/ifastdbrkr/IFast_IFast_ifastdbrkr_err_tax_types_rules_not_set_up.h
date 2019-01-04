#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_tax_types_rules_not_set_up : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_tax_types_rules_not_set_up() { }
		~CIFast_IFast_ifastdbrkr_err_tax_types_rules_not_set_up() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_TYPES_RULES_NOT_SET_UP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax types rules have not yet been set up.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Tax types rules have not yet been set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerarten-Regeln wurden noch nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Aún no se han configurado las reglas de tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les règles de types d'imposition n'ont pas encore été réglées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen regels voor belastingtypes ingesteld")); }

        // Actions
	};
}



