#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_to_benef_is_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_to_benef_is_missing() { }
		~CIFast_IFast_ifastcbo_err_to_benef_is_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TO_BENEF_IS_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("To beneficiary is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire cible est manquant.")); }

        // Actions
	};
}



