#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_total_split_commision_rate_exceeds_fee_default : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_total_split_commision_rate_exceeds_fee_default() { }
		~CIFast_IFast_ifastcbo_err_total_split_commision_rate_exceeds_fee_default() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TOTAL_SPLIT_COMMISION_RATE_EXCEEDS_FEE_DEFAULT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total commission rate exceeds the default rate of: %DEFAULT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Total split commission rate exceeds the split commission default rate (%DEFAULT%).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Total split commission rate exceeds the split commission default rate (%DEFAULT%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de commission total excède le taux par défaut : %DEFAULT%.")); }

        // Actions
	};
}



