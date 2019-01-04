#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_redemption_exceed_remaining_contrib : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_redemption_exceed_remaining_contrib() { }
		~CIFast_IFast_ifastcbo_warn_redemption_exceed_remaining_contrib() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REDEMPTION_EXCEED_REMAINING_CONTRIB")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption exceeded Remaining Contribution.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat excède la cotisation restante.")); }

        // Actions
	};
}



