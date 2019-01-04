#pragma once

#include "ConditionObject.h"

namespace CND
{
		class IFast_IFast_ifastcbo_warn_Invalid_australian_business_number_value: public CConditionObject
	{
	public:
		IFast_IFast_ifastcbo_warn_Invalid_australian_business_number_value() { }
		~IFast_IFast_ifastcbo_warn_Invalid_australian_business_number_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_ABN_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid ABN value. Please leave blank and obtain valid ABN prior to next distribution to avoid WHT deduction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Invalid ABN value. Please leave blank and obtain valid ABN prior to next distribution to avoid WHT deduction.")); }

        // Actions
	};
}



