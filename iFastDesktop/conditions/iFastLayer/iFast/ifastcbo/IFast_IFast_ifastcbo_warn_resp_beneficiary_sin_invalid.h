#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_beneficiary_sin_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_beneficiary_sin_invalid() { }
		~CIFast_IFast_ifastcbo_warn_resp_beneficiary_sin_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_BENEFICIARY_SIN_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Valid SIN is required for RESP accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un NAS valide est requis pour les comptes REEE.")); }

        // Actions
	};
}



