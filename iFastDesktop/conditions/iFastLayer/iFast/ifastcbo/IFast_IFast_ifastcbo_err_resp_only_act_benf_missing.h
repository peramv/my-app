#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_only_act_benf_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_only_act_benf_missing() { }
		~CIFast_IFast_ifastcbo_err_resp_only_act_benf_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_ONLY_ACT_BENF_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Active RESP Beneficiary entity is missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Active RESP Beneficiary entity is missing.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Active RESP Beneficiary entity is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité bénéficiaire REEE active est manquante.")); }

        // Actions
	};
}



