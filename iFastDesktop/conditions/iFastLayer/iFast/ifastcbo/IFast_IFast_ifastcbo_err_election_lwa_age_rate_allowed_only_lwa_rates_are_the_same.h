#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_election_lwa_age_rate_allowed_only_lwa_rates_are_the_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_election_lwa_age_rate_allowed_only_lwa_rates_are_the_same() { }
		~CIFast_IFast_ifastcbo_err_election_lwa_age_rate_allowed_only_lwa_rates_are_the_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ELECTION_LWA_AGE_RATE_ALLOWED_ONLY_LWA_RATES_ARE_THE_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Election of LWA Age Rate is only allowed When LWA rates between accounts is the same.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le choix du taux d'âge MRV n'est autorisé que lorsque les taux MRV entre les comptes sont les mêmes.")); }

        // Actions
	};
}



