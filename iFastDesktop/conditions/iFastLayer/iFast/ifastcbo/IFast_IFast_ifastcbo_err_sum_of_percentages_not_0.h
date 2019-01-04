#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sum_of_percentages_not_0 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sum_of_percentages_not_0() { }
		~CIFast_IFast_ifastcbo_err_sum_of_percentages_not_0() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SUM_OF_PERCENTAGES_NOT_0")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation percentages must sum up to 0%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les pourcentages de répartition doivent totaliser 0 %.")); }

        // Actions
	};
}



