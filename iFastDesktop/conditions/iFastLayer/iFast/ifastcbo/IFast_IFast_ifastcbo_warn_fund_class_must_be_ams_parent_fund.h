#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_fund_class_must_be_ams_parent_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_fund_class_must_be_ams_parent_fund() { }
		~CIFast_IFast_ifastcbo_warn_fund_class_must_be_ams_parent_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FUND_CLASS_MUST_BE_AMS_PARENT_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The fund class is not an AMS Parent Fund.")); }

        // Actions
	};
}



