#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_the_maximum_fee_rate_is_greater_than : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_the_maximum_fee_rate_is_greater_than() { }
		~CIFast_IFast_ifastcbo_err_the_maximum_fee_rate_is_greater_than() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_THE_MAXIMUM_FEE_RATE_IS_GREATER_THAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The maximum fee rate is greater than %RATE%%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The maximum fee rate is greater than %RATE%%.")); }

        // Actions
	};
}