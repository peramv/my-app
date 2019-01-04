#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_redemption_code_applicable_only_for_non_resident_beneficiaries : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_redemption_code_applicable_only_for_non_resident_beneficiaries() { }
		~CIFast_IFast_ifastcbo_warn_redemption_code_applicable_only_for_non_resident_beneficiaries() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REDEMPTION_CODE_APPLICABLE_ONLY_FOR_NON_RESIDENT_BENEFICIARIES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption code '77' applicable only for non-resident beneficiaries.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat 77 n'est applicable qu'aux bénéficiaires non résidents.")); }

        // Actions
	};
}



