#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_override_prov_tax_rate_less_then_default : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_override_prov_tax_rate_less_then_default() { }
		~CIFast_IFast_ifastcbo_warn_override_prov_tax_rate_less_then_default() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_OVERRIDE_PROV_TAX_RATE_LESS_THEN_DEFAULT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Override Provincial Tax Rate is lower than default value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Override Provincial Tax Rate is lower than default value.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Override tax rate is less than default value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La modification du taux d'imposition provincial est inférieure à la valeur par défaut.")); }

        // Actions
	};
}



