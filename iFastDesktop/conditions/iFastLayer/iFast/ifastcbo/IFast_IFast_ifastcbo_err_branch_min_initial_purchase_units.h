#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_branch_min_initial_purchase_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_branch_min_initial_purchase_units() { }
		~CIFast_IFast_ifastcbo_err_branch_min_initial_purchase_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BRANCH_LESS_THAN_MINIMUM_INITITAL_PURCHASE_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Branch: Minimum Initial %PUR_BUYBACK% %AMNT_UNITS% is %MINIMUM_AMT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Branch: Minimum Initial %PUR_BUYBACK% %AMNT_UNITS% is %MINIMUM_AMT%.")); }
        // Actions
	};
}



