#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_redemption_code_rules_not_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_redemption_code_rules_not_setup() { }
		~CIFast_IFast_ifastcbo_warn_redemption_code_rules_not_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REDEMPTION_CODE_RULES_NOT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Code Rules not setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Redemption Code Rules not setup.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Redemption Code Rules not setup.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les règles de code de rachat ne sont pas réglées.")); }

        // Actions
	};
}



