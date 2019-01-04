#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_receiving_acct_ams_model_not_contain_this_fund_class_as_child : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_receiving_acct_ams_model_not_contain_this_fund_class_as_child() { }
		~CIFast_IFast_ifastcbo_warn_receiving_acct_ams_model_not_contain_this_fund_class_as_child() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The receiving account's global AMS model does not contain this global AMS model child fund class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The receiving account's global AMS model does not contain this global AMS model child fund class.")); }

        // Actions
	};
}