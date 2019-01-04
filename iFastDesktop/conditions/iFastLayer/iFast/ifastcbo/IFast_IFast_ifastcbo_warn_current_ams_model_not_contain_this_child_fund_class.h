#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_current_ams_model_not_contain_this_child_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_current_ams_model_not_contain_this_child_fund_class() { }
		~CIFast_IFast_ifastcbo_warn_current_ams_model_not_contain_this_child_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CURRENT_AMS_MODEL_NOT_CONTAIN_THIS_CHILD_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The current global AMS model does not contain this child fund class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The current global AMS model does not contain this child fund class.")); }

        // Actions
	};
}