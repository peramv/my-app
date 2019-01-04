#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sum_of_benef_alloc_percentages_not_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sum_of_benef_alloc_percentages_not_100() { }
		~CIFast_IFast_ifastcbo_err_sum_of_benef_alloc_percentages_not_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SUM_OF_BENEF_ALLOC_PERCENTAGES_NOT_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total of all beneficiary allocations should be 100 %.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le total de toutes les répartitions du bénéficiaire devrait être de 100 %.")); }

        // Actions
	};
}



