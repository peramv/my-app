#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_redemption_exceeds_grant_plus_earnings : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_redemption_exceeds_grant_plus_earnings() { }
		~CIFast_IFast_ifastcbo_warn_redemption_exceeds_grant_plus_earnings() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REDEMPTION_EXCEEDS_GRANT_PLUS_EARNINGS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption %PARAM_1% exceeds Grant Plus Earnings %PARAM_2%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%PARAM_1% de rachat excède %PARAM_2% de subvention additionnée des revenus.")); }

        // Actions
	};
}



