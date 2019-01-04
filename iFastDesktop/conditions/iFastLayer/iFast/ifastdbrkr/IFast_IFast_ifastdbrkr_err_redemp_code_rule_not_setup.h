#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_redemp_code_rule_not_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_redemp_code_rule_not_setup() { }
		~CIFast_IFast_ifastdbrkr_err_redemp_code_rule_not_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMP_CODE_RULE_NOT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Code Rules not setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgungscode-Regeln nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se han configurado las reglas de código de rescate.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les règles de code de rachat ne sont pas réglées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen regels voor de aflossingscode ingesteld")); }

        // Actions
	};
}



