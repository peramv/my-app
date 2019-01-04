#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_gender_cannot_be_blank_for_nmcr_single_life_contract : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_gender_cannot_be_blank_for_nmcr_single_life_contract() { }
		~CIFast_IFast_ifastcbo_warn_gender_cannot_be_blank_for_nmcr_single_life_contract() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Gender cannot be blank if NMCR Single Life")); }

        // Actions
	};
}



