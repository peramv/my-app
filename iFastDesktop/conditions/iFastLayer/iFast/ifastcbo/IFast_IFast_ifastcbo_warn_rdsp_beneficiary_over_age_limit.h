#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_over_age_limit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_over_age_limit() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_over_age_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_BENEFICIARY_OVER_AGE_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary must be no more than 59 years of age.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Beneficiary must be no more than 59 years of age.")); }

        // Actions
	};
}



