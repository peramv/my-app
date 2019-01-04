#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_less_then_minimum_initial_buyback_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_less_then_minimum_initial_buyback_amount() { }
		~CIFast_IFast_ifastcbo_err_less_then_minimum_initial_buyback_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LESS_THAN_MINIMUM_INITIAL_BUYBACK_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum Initial Buyback Amount is %MINIMUM_AMT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Minimum Initial Buyback Amount is %MINIMUM_AMT%.")); }

        // Actions
	};
}



