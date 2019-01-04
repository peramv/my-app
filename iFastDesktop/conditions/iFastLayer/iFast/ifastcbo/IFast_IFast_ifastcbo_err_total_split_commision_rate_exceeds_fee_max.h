#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_total_split_commision_rate_exceeds_fee_max : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_total_split_commision_rate_exceeds_fee_max() { }
		~CIFast_IFast_ifastcbo_err_total_split_commision_rate_exceeds_fee_max() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TOTAL_SPLIT_COMMISION_RATE_EXCEEDS_FEE_MAX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total commission rate exceeds the max rate of: %MAX%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de commission total excède le taux maximal de %MAX%.")); }

        // Actions
	};
}



