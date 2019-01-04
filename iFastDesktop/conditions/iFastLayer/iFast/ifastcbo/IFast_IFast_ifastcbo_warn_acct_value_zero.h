#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_value_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_value_zero() { }
		~CIFast_IFast_ifastcbo_warn_acct_value_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_VALUE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Value is zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account Value is zero.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account Value is zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur du compte est de zéro.")); }

        // Actions
	};
}



