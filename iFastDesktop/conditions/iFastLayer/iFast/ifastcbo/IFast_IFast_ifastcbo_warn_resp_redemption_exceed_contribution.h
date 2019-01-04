#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_redemption_exceed_contribution : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_redemption_exceed_contribution() { }
		~CIFast_IFast_ifastcbo_warn_resp_redemption_exceed_contribution() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_REDEMPTION_EXCEED_CONTRIBUTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption %PARAM_1% exceeded Remaining Contribution %PARAM_2%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat %PARAM_1% a excédé la cotisation restante %PARAM_2%.")); }

        // Actions
	};
}



