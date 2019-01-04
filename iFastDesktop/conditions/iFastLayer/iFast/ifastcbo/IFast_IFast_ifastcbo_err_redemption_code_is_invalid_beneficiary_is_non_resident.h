#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redemption_code_is_invalid_beneficiary_is_non_resident : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redemption_code_is_invalid_beneficiary_is_non_resident() { }
		~CIFast_IFast_ifastcbo_err_redemption_code_is_invalid_beneficiary_is_non_resident() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPTION_CODE_IS_INVALID_BENEFICIARY_IS_NON_RESIDENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption code is invalid since beneficiary is non-resident.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat est invalide puisque le bénéficiaire est non résident.")); }

        // Actions
	};
}



