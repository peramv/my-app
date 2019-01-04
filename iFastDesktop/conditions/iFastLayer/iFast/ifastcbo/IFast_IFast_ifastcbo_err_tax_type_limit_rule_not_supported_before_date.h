#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tax_type_limit_rule_not_supported_before_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tax_type_limit_rule_not_supported_before_date() { }
		~CIFast_IFast_ifastcbo_err_tax_type_limit_rule_not_supported_before_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_TYPE_LIMIT_RULE_NOT_SUPPORTED_BEFORE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New account set up for %VAR1% must be after %TAXJURISEFFECTIVEDATE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le réglage d'un nouveau compte pour %VAR1% doit être après le %TAXJURISEFFECTIVEDATE%.")); }

        // Actions
	};
}



