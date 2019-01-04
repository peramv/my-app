#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bene_over_age_of_15 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bene_over_age_of_15() { }
		~CIFast_IFast_ifastcbo_err_bene_over_age_of_15() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BENE_OVER_AGE_OF_15")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary is over fifteen years old.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire est âgé de plus de quinze ans.")); }

        // Actions
	};
}



