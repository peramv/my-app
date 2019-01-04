#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_total_redemption_exceeds_maximum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_total_redemption_exceeds_maximum() { }
		~CIFast_IFast_ifastcbo_err_warn_total_redemption_exceeds_maximum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_TOTAL_REDEMPTION_EXCEEDS_MAXIMUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total redemption exceeds maximum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("žŠÒ‡Œv‚ªÅ‘å‹K’è’l‚ð’´‚¦‚Ä‚¢‚Ü‚·B")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("žŠÒ‡Œv‚ªÅ‘å‹K’è’l‚ð’´‚¦‚Ä‚¢‚Ü‚·B")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat total excède le maximum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De totale afkoop overschrijdt maximum")); }

        // Actions
	};
}



