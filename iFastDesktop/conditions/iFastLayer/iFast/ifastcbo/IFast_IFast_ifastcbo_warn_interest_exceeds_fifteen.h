#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_interest_exceeds_fifteen : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_interest_exceeds_fifteen() { }
		~CIFast_IFast_ifastcbo_warn_interest_exceeds_fifteen() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INTEREST_EXCEEDS_FIFTEEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percentage exceeds max rate of 15 %")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage excède le taux maximal de 15 %.")); }

        // Actions
	};
}



