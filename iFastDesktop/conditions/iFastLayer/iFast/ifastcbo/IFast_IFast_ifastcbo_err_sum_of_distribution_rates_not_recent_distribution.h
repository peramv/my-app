#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sum_of_distribution_rates_not_recent_distribution : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sum_of_distribution_rates_not_recent_distribution() { }
		~CIFast_IFast_ifastcbo_err_sum_of_distribution_rates_not_recent_distribution() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The total sum of the distribution rates does not equal to the most recent distribution amount. Do you want to continue saving the distribution setup?")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le total des taux de distribution n’égale pas le montant de la distribution. Souhaitez-vous poursuivre l’enregistrement de la distribution?")); }

        // Actions
	};
}



