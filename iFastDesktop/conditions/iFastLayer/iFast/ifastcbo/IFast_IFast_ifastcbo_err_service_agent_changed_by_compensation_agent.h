#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_service_agent_changed_by_compensation_agent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_service_agent_changed_by_compensation_agent() { }
		~CIFast_IFast_ifastcbo_err_service_agent_changed_by_compensation_agent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Service Agent Broker\\Branch\\Rep will be changed to the Compensation Agent.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier/l'unité de service/le représentant de l'agent de service sera changé pour celui/celle de l'agent de commission.")); }

        // Actions
	};
}



