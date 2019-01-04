#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_Fund_class_is_not_linked_to_current_active_AMS_model : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_Fund_class_is_not_linked_to_current_active_AMS_model() { }
		~CIFast_IFast_ifastdbrkr_err_Fund_class_is_not_linked_to_current_active_AMS_model() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_IS_NOT_LINKED_TO_CURRENT_ACTIVE_AMS_MODEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund/class is not linked to current active AMS model.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund/class is not linked to current active AMS model.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund/class is not linked to current active AMS model.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fund/class is not linked to current active AMS model.")); }

        // Actions
	};
}