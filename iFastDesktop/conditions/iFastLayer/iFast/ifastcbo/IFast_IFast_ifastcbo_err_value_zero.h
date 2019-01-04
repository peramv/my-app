#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_value_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_value_zero() { }
		~CIFast_IFast_ifastcbo_err_value_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VALUE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Value cannot be zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur ne peut être nulle.")); }

        // Actions
	};
}



