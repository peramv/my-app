#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_pcg_indiv_sin_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_pcg_indiv_sin_missing() { }
		~CIFast_IFast_ifastcbo_warn_resp_pcg_indiv_sin_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_PCG_INDIV_SIN_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP PCG Individual's SIN is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le NAS individuel du responsable principal REEE est manquant.")); }

        // Actions
	};
}



