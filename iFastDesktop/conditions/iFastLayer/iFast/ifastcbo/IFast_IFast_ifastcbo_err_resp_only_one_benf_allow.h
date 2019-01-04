#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_only_one_benf_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_only_one_benf_allow() { }
		~CIFast_IFast_ifastcbo_err_resp_only_one_benf_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_ONLY_ONE_BENF_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one RESP beneficiary is allowed for Individual RESP tax type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only one RESP beneficiary is allowed for Individual RESP tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur ein RESP-Begünstigter ist für die individuelle RESP-Steuerart zulässig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se permite un beneficiario RESP para el tipo tributario REAP individual")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul bénéficiaire REEE est autorisé pour le type d'imposition REEE individuel.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is slechts één RESP-begunstigde toegestaan voor belastingtype Individueel REAP")); }

        // Actions
	};
}



