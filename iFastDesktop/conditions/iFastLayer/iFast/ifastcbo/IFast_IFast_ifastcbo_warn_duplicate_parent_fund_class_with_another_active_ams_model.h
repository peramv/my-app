#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_duplicate_parent_fund_class_with_another_active_ams_model : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_duplicate_parent_fund_class_with_another_active_ams_model() { }
		~CIFast_IFast_ifastcbo_warn_duplicate_parent_fund_class_with_another_active_ams_model() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DUPLICATE_PARENT_FUND_CLASS_WITH_ANOTHER_ACTIVE_AMS_MODEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The parent fund class already exists with another AMS Global Model.")); }

        // Actions
	};
}



