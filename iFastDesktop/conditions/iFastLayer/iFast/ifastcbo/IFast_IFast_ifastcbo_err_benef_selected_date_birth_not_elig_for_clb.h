#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_benef_selected_date_birth_not_elig_for_clb : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_benef_selected_date_birth_not_elig_for_clb() { }
		~CIFast_IFast_ifastcbo_err_benef_selected_date_birth_not_elig_for_clb() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BENEF_SELECTED_DATE_BIRTH_NOT_ELIG_FOR_CLB")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary selected date of birth is not eligible for CLB.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance sélectionnée pour le bénéficiaire n'est pas admissible au BEC.")); }

        // Actions
	};
}



