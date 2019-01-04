#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_agent_not_found_for_broker_branch : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_agent_not_found_for_broker_branch() { }
		~CIFast_IFast_ifastcbo_err_agent_not_found_for_broker_branch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AGENT_NOT_FOUND_FOR_BROKER_BRANCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No agent code %AGENT% is found for the broker %BROKER% and branch %BRANCH%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun code d'agent %AGENT% n'a été trouvé pour le courtier %BROKER% et l'unité de service %BRANCH%.")); }

        // Actions
	};
}



