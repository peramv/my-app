#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_rate_under_0_percent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_rate_under_0_percent() { }
		~CIFast_IFast_ifastcbo_err_fee_rate_under_0_percent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_RATE_UNDER_0_PERCENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%name% under minimum percent of %min%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%name% under minimum percent of %min%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%name% est inférieure à pour cent au minimum de %min%.")); }

        // Actions
	};
}



