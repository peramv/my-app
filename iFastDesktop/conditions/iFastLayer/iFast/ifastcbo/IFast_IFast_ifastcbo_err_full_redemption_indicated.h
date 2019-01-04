#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_full_redemption_indicated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_full_redemption_indicated() { }
		~CIFast_IFast_ifastcbo_err_full_redemption_indicated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FULL_REDEMPTION_INDICATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full redemption is indicated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Volle Tilgung wird angezeigt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se indica el rescate total")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat total est indiqué.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige aflossing is aangegeven")); }

        // Actions
	};
}



