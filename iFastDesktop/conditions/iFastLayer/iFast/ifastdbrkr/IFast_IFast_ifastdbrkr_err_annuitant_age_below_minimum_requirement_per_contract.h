#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_annuitant_age_below_minimum_requirement_per_contract : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_annuitant_age_below_minimum_requirement_per_contract() { }
		~CIFast_IFast_ifastdbrkr_err_annuitant_age_below_minimum_requirement_per_contract() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUITANT_AGE_BELOW_MINIMUM_REQUIREMENT_PER_CONTRACT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant’s age is below the minimum age requirement for the contract type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge du rentier est inférieur au minimum exigé pour ce type de contrat.")); }

        // Actions
	};
}