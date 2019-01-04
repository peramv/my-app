#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tax_juris_changed_effective_date_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tax_juris_changed_effective_date_same() { }
		~CIFast_IFast_ifastcbo_warn_tax_juris_changed_effective_date_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TAX_JURIS_CHANGED_EFFECTIVE_DATE_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The effective date for the new tax jurisdiction has not been changed. Please ensure that the effective date is correct.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'effet pour la nouvelle juridiction fiscale n’a pas été modifiée. Vérifiez que la date d’effet est correcte.")); }

        // Actions
	};
}



