#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_parent_fund_class_diff_from_ams_model : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_parent_fund_class_diff_from_ams_model() { }
		~CIFast_IFast_ifastcbo_err_parent_fund_class_diff_from_ams_model() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PARENT_FUND_CLASS_DIFF_FROM_AMS_MODEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The parent fund class is different from the parent fund class on the current global AMS model.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The parent fund class is different from the parent fund class on the current global AMS model.")); }

        // Actions
	};
}