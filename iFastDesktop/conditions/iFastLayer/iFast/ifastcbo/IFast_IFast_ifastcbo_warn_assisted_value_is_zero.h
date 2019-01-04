#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_assisted_value_is_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_assisted_value_is_zero() { }
		~CIFast_IFast_ifastcbo_warn_assisted_value_is_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ASSISTED_VALUE_IS_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Assisted contributed value is ‘0’.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur cotisée subventionnée est 0.")); }

        // Actions
	};
}



