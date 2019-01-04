#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_over_age_of_contribution : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_over_age_of_contribution() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_beneficiary_over_age_of_contribution() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_BENEFICIARY_OVER_AGE_OF_CONTRIBUTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RDSP Beneficiary is over the age of contribution.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("RDSP Beneficiary is over the age of contribution.")); }

        // Actions
	};
}



