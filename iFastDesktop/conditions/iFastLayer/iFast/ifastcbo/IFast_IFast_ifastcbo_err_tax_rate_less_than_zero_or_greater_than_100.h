#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tax_rate_less_than_zero_or_greater_than_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tax_rate_less_than_zero_or_greater_than_100() { }
		~CIFast_IFast_ifastcbo_err_tax_rate_less_than_zero_or_greater_than_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_RATE_LESS_THAN_ZERO_OR_GREATER_THAN_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Rate must be between 0% and 100%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tax Rate must be between 0% and 100%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux d'imposition doit être situé entre 0 et 100 %.")); }

        // Actions
	};
}



