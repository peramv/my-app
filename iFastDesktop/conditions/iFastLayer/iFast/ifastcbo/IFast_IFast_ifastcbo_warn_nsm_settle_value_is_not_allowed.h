#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_nsm_settle_value_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_nsm_settle_value_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_warn_nsm_settle_value_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NSM_SETTLE_VALUE_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The N$M settle must be Include.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The N$M settle must be Include.")); }

        // Actions
	};
}



