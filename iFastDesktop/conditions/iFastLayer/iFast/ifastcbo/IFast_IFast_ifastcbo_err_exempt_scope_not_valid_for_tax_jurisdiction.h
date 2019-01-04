#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_exempt_scope_not_valid_for_tax_jurisdiction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_exempt_scope_not_valid_for_tax_jurisdiction() { }
		~CIFast_IFast_ifastcbo_err_exempt_scope_not_valid_for_tax_jurisdiction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXEMPT_SCOPE_NOT_VALID_FOR_TAX_JURISDICTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exempt scope is not valid for the current tax jurisdiction")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La portée des exonérations n’est pas valide sous la juridiction fiscale actuelle.")); }

        // Actions
	};
}



