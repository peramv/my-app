#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_benef_is_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_benef_is_missing() { }
		~CIFast_IFast_ifastcbo_err_resp_benef_is_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_BENEF_IS_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary data is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Données du bénéficiaire manquantes")); }

        // Actions
	};
}



