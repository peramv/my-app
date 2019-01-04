#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_benef_validation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_benef_validation() { }
		~CIFast_IFast_ifastcbo_warn_benef_validation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BENEF_VALIDATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Validations for beneficiary: %BENNAME%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Validations du bénéficiaire : %BENNAME%")); }

        // Actions
	};
}



