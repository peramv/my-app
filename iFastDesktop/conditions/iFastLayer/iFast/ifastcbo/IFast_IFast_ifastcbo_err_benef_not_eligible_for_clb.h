#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_benef_not_eligible_for_clb : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_benef_not_eligible_for_clb() { }
		~CIFast_IFast_ifastcbo_err_benef_not_eligible_for_clb() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BENEF_NOT_ELIGIBLE_FOR_CLB")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }
         
		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary %BENNAME% is not eligible for CLB since Date of Birth is earlier than %ELIGDATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire %BENNAME% n'est pas admissible au BEC parce que la date de naissance est antérieure au %ELIGDATE%.")); }

        // Actions
	};
}



