#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_gender_change_not_allowed_for_elected_single_life_nmcr_contract : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_gender_change_not_allowed_for_elected_single_life_nmcr_contract() { }
		~CIFast_IFast_ifastcbo_err_gender_change_not_allowed_for_elected_single_life_nmcr_contract() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GENDER_CHANGE_NOT_ALLOWED_FOR_ELECTED_SINGLE_LIFE_NMCR_CONTRACT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot change gender on elected NMCR Single Life contract")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier le sexe du contrat d’assurance vie individuelle NMCR.")); }

        // Actions
	};
}



