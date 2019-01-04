#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_beneficiary_is_over_18 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_beneficiary_is_over_18() { }
		~CIFast_IFast_ifastcbo_err_beneficiary_is_over_18() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BENEFICIARY_IS_OVER_18")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary is greater than 18 years of age.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire est âgé de plus de 18 ans.")); }

        // Actions
	};
}



