#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redemption_total_tax_rate_greater_than_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redemption_total_tax_rate_greater_than_100() { }
		~CIFast_IFast_ifastcbo_err_redemption_total_tax_rate_greater_than_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPTION_TOTAL_TAX_RATE_GREATER_THAN_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total Tax Rate cannot be greater than 100%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Total Tax Rate cannot be greater than 100%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Total Tax Rate cannot be greater than 100%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux d'imposition total ne peut être supérieur à 100 %.")); }

        // Actions
	};
}



