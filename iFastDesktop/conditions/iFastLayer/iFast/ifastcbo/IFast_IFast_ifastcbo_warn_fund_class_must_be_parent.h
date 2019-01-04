#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_fund_class_must_be_parent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_fund_class_must_be_parent() { }
		~CIFast_IFast_ifastcbo_warn_fund_class_must_be_parent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FUND_CLASS_MUST_BE_PARENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The fund is not a parent fund class of AMS code %AMSCODE%.")); }

        // Actions
	};
}



