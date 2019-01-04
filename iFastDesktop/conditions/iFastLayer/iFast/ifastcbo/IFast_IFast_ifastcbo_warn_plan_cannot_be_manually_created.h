#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_plan_cannot_be_manually_created : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_plan_cannot_be_manually_created() { }
		~CIFast_IFast_ifastcbo_warn_plan_cannot_be_manually_created() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PLAN_CANNOT_BE_MANUALLY_CREATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Plan cannot be manually created.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plan cannot be manually created.")); }

        // Actions
	};
}