#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tax_juris_changed_ensure_rrif_is_followed_new_tax : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tax_juris_changed_ensure_rrif_is_followed_new_tax() { }
		~CIFast_IFast_ifastcbo_warn_tax_juris_changed_ensure_rrif_is_followed_new_tax() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TAX_JURIS_CHANGED_ENSURE_RRIF_IS_FOLLOWED_NEW_TAX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please ensure that the RRIF set-up tax jurisdiction is updated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vérifiez que la juridiction fiscale du FERR est à jour.")); }

        // Actions
	};
}



