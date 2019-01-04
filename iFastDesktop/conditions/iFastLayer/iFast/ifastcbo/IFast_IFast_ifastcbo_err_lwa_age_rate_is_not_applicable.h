#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_lwa_age_rate_is_not_applicable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_lwa_age_rate_is_not_applicable() { }
		~CIFast_IFast_ifastcbo_err_lwa_age_rate_is_not_applicable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LWA_AGE_RATE_IS_NOT_APPLICABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("LWA Age Rate is not applicable, event not allowed for the effective date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Taux d'âge MRV non applicable; événement non autorisé pour la date d'entrée en vigueur.")); }

        // Actions
	};
}



